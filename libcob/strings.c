/*
 * Copyright (C) 2002-2009 Keisuke Nishida
 * Copyright (C) 2007-2009 Roger While
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1,
 * or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see the file COPYING.LIB.  If
 * not, write to the Free Software Foundation, 51 Franklin Street, Fifth Floor
 * Boston, MA 02110-1301 USA
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>

#include "move.h"
#include "coblocal.h"
#include "numeric.h"
#include "strings.h"

#define INSPECT_ALL		0
#define INSPECT_LEADING		1
#define INSPECT_FIRST		2
#define INSPECT_TRAILING	3

#define DLM_DEFAULT_NUM		8

struct dlm_struct {
	cob_field	*uns_dlm;
	int		uns_all;
};

static cob_field		*inspect_var;
static unsigned char		*inspect_data;
static unsigned char		*inspect_start;
static unsigned char		*inspect_end;
static int			*inspect_mark = NULL;
static size_t			lastsize = 0;
static size_t			inspect_size;
static int			inspect_replacing;
static int			inspect_sign;
static cob_field		inspect_var_copy;

static cob_field		*string_dst;
static cob_field		*string_ptr;
static cob_field		*string_dlm;
static cob_field		string_dst_copy;
static cob_field		string_ptr_copy;
static cob_field		string_dlm_copy;
static int			string_offset;

static struct dlm_struct	*dlm_list = NULL;
static cob_field		*unstring_src;
static cob_field		*unstring_ptr;
static cob_field		unstring_src_copy;
static cob_field		unstring_ptr_copy;
static int			unstring_offset;
static int			unstring_count;
static int			unstring_ndlms;

static cob_field_attr		alpha_attr;
static cob_field		alpha_fld;

static COB_INLINE int
cob_min_int (const int x, const int y)
{
	if (x < y) {
		return x;
	}
	return y;
}

static void
alloc_figurative (const cob_field *f1, const cob_field *f2)
{
	static unsigned char	*figptr = NULL;
	static size_t		figsize = 0;

	unsigned char		*s;
	size_t			size1;
	size_t			size2;
	size_t			n;

	size2 = f2->size;
	if (size2 > figsize) {
		if (figptr) {
			free (figptr);
		}
		figptr = cob_malloc (size2);
		figsize = size2;
	}
	size1 = 0;
	s = figptr;
	for (n = 0; n < size2; n++, s++) {
		*s = f1->data[size1];
		size1++;
		if (size1 >= f1->size) {
			size1 = 0;
		}
	}
	alpha_fld.size = size2;
	alpha_fld.data = figptr;
}

static void
inspect_common (cob_field *f1, cob_field *f2, const int type)
{
	int		*mark;
	size_t		n = 0;
	size_t		j;
	int		i;
	int		len;

	if (unlikely(!f1)) {
		f1 = &cob_low;
	}
	if (unlikely(!f2)) {
		f2 = &cob_low;
	}

	if (inspect_replacing && f1->size != f2->size) {
		if (COB_FIELD_TYPE (f1) == COB_TYPE_ALPHANUMERIC_ALL) {
			alloc_figurative (f1, f2);
			f1 = &alpha_fld;
		} else {
			cob_set_exception (COB_EC_RANGE_INSPECT_SIZE);
			return;
		}
	}

	mark = &inspect_mark[inspect_start - inspect_data];
	len = (int)(inspect_end - inspect_start);
	if (type == INSPECT_TRAILING) {
		for (i = len - f2->size; i >= 0; i--) {
			/* find matching substring */
			if (memcmp (inspect_start + i, f2->data, f2->size) == 0) {
				/* check if it is already marked */
				for (j = 0; j < f2->size; j++) {
					if (mark[i + j] != -1) {
						break;
					}
				}
				/* if not, mark and count it */
				if (j == f2->size) {
					for (j = 0; j < f2->size; j++) {
						mark[i + j] = inspect_replacing ? f1->data[j] : 1;
					}
					i -= f2->size - 1;
					n++;
				}
			} else {
				break;
			}
		}
	} else {
		for (i = 0; i < (int)(len - f2->size + 1); i++) {
			/* find matching substring */
			if (memcmp (inspect_start + i, f2->data, f2->size) == 0) {
				/* check if it is already marked */
				for (j = 0; j < f2->size; j++) {
					if (mark[i + j] != -1) {
						break;
					}
				}
				/* if not, mark and count it */
				if (j == f2->size) {
					for (j = 0; j < f2->size; j++) {
						mark[i + j] = inspect_replacing ? f1->data[j] : 1;
					}
					i += f2->size - 1;
					n++;
					if (type == INSPECT_FIRST) {
						break;
					}
				}
			} else if (type == INSPECT_LEADING) {
				break;
			}
		}
	}

	if (n > 0 && !inspect_replacing) {
		cob_add_int (f1, (int) n);
	}
}

/*
 * INSPECT
 */

void
cob_inspect_init (cob_field *var, const int replacing)
{
	size_t		i;
	size_t		digcount;

	inspect_var_copy = *var;
	inspect_var = &inspect_var_copy;
	inspect_replacing = replacing;
	inspect_sign = cob_get_sign (var);
	inspect_size = COB_FIELD_SIZE (var);
	inspect_data = COB_FIELD_DATA (var);
	inspect_start = NULL;
	inspect_end = NULL;
	digcount = inspect_size * sizeof (int);
	if (digcount > lastsize) {
		free (inspect_mark);
		inspect_mark = cob_malloc (digcount);
		lastsize = digcount;
	}
	for (i = 0; i < inspect_size; i++) {
		inspect_mark[i] = -1;
	}
	cob_exception_code = 0;
}

void
cob_inspect_start (void)
{
	inspect_start = inspect_data;
	inspect_end = inspect_data + inspect_size;
}

void
cob_inspect_before (const cob_field *str)
{
	unsigned char	*p;

	for (p = inspect_start; p < inspect_end - str->size + 1; p++) {
		if (memcmp (p, str->data, str->size) == 0) {
			inspect_end = p;
			return;
		}
	}
}

void
cob_inspect_after (const cob_field *str)
{
	unsigned char	*p;

	for (p = inspect_start; p < inspect_end - str->size + 1; p++) {
		if (memcmp (p, str->data, str->size) == 0) {
			inspect_start = p + str->size;
			return;
		}
	}
	inspect_start = inspect_end;
}

void
cob_inspect_characters (cob_field *f1)
{
	int	*mark;
	int	i;
	int	n;
	int	len;

	mark = &inspect_mark[inspect_start - inspect_data];
	len = (int)(inspect_end - inspect_start);
	if (inspect_replacing) {
		/* INSPECT REPLACING CHARACTERS f1 */
		for (i = 0; i < len; i++) {
			if (mark[i] == -1) {
				mark[i] = f1->data[0];
			}
		}
	} else {
		/* INSPECT TALLYING f1 CHARACTERS */
		n = 0;
		for (i = 0; i < len; i++) {
			if (mark[i] == -1) {
				mark[i] = 1;
				n++;
			}
		}
		if (n > 0) {
			cob_add_int (f1, n);
		}
	}
}

void
cob_inspect_all (cob_field *f1, cob_field *f2)
{
	inspect_common (f1, f2, INSPECT_ALL);
}

void
cob_inspect_leading (cob_field *f1, cob_field *f2)
{
	inspect_common (f1, f2, INSPECT_LEADING);
}

void
cob_inspect_first (cob_field *f1, cob_field *f2)
{
	inspect_common (f1, f2, INSPECT_FIRST);
}

void
cob_inspect_trailing (cob_field *f1, cob_field *f2)
{
	inspect_common (f1, f2, INSPECT_TRAILING);
}

void
cob_inspect_converting (cob_field *f1, cob_field *f2)
{
	size_t	i;
	size_t	j;
	size_t	len;

	len = (size_t)(inspect_end - inspect_start);
	for (j = 0; j < f1->size; j++) {
		for (i = 0; i < len; i++) {
			if (inspect_mark[i] == -1 && inspect_start[i] == f1->data[j]) {
				inspect_start[i] = f2->data[j];
				inspect_mark[i] = 1;
			}
		}
	}
}

void
cob_inspect_finish (void)
{
	size_t	i;

	if (inspect_replacing) {
		for (i = 0; i < inspect_size; i++) {
			if (inspect_mark[i] != -1) {
				inspect_data[i] = inspect_mark[i];
			}
		}
	}

	cob_put_sign (inspect_var, inspect_sign);
}

/*
 * STRING
 */

void
cob_string_init (cob_field *dst, cob_field *ptr)
{
	string_dst_copy = *dst;
	string_dst = &string_dst_copy;
	string_ptr = NULL;
	if (ptr) {
		string_ptr_copy = *ptr;
		string_ptr = &string_ptr_copy;
	}
	string_offset = 0;
	cob_exception_code = 0;

	if (string_ptr) {
		string_offset = cob_get_int (string_ptr) - 1;
		if (string_offset < 0 || string_offset >= (int)string_dst->size) {
			cob_set_exception (COB_EC_OVERFLOW_STRING);
		}
	}
}

void
cob_string_delimited (cob_field *dlm)
{
	string_dlm = NULL;
	if (dlm) {
		string_dlm_copy = *dlm;
		string_dlm = &string_dlm_copy;
	}
}

void
cob_string_append (cob_field *src)
{
	size_t	src_size;
	int	i;
	int	size;

	if (cob_exception_code) {
		return;
	}

	src_size = src->size;
	if (string_dlm) {
		size = (int)(src_size - string_dlm->size + 1);
		for (i = 0; i < size; i++) {
			if (memcmp (src->data + i, string_dlm->data, string_dlm->size) == 0) {
				src_size = i;
				break;
			}
		}
	}

	if (src_size <= string_dst->size - string_offset) {
		memcpy (string_dst->data + string_offset, src->data, src_size);
		string_offset += (int) src_size;
	} else {
		size = (int)(string_dst->size - string_offset);
		memcpy (string_dst->data + string_offset, src->data, (size_t)size);
		string_offset += size;
		cob_set_exception (COB_EC_OVERFLOW_STRING);
	}
}

void
cob_string_finish (void)
{
	if (string_ptr) {
		cob_set_int (string_ptr, string_offset + 1);
	}
}

/*
 * UNSTRING
 */

void
cob_unstring_init (cob_field *src, cob_field *ptr, const size_t num_dlm)
{
	static size_t	udlmcount = 0;

	unstring_src_copy = *src;
	unstring_src = &unstring_src_copy;
	unstring_ptr = NULL;
	if (ptr) {
		unstring_ptr_copy = *ptr;
		unstring_ptr = &unstring_ptr_copy;
	}

	unstring_offset = 0;
	unstring_count = 0;
	unstring_ndlms = 0;
	cob_exception_code = 0;
	if (!dlm_list) {
		if (num_dlm <= DLM_DEFAULT_NUM) {
			dlm_list = cob_malloc (DLM_DEFAULT_NUM * sizeof(struct dlm_struct));
			udlmcount = DLM_DEFAULT_NUM;
		} else {
			dlm_list = cob_malloc (num_dlm * sizeof(struct dlm_struct));
			udlmcount = num_dlm;
		}
	} else {
		if (num_dlm > udlmcount) {
			free (dlm_list);
			dlm_list = cob_malloc (num_dlm * sizeof(struct dlm_struct));
			udlmcount = num_dlm;
		}
	}

	if (unstring_ptr) {
		unstring_offset = cob_get_int (unstring_ptr) - 1;
		if (unstring_offset < 0 || unstring_offset >= (int)unstring_src->size) {
			cob_set_exception (COB_EC_OVERFLOW_UNSTRING);
		}
	}
}

void
cob_unstring_delimited (cob_field *dlm, const int all)
{
	dlm_list[unstring_ndlms].uns_dlm = dlm;
	dlm_list[unstring_ndlms].uns_all = all;
	unstring_ndlms++;
}

void
cob_unstring_into (cob_field *dst, cob_field *dlm, cob_field *cnt)
{
	unsigned char	*p;
	unsigned char	*dp;
	unsigned char	*s;
	unsigned char	*dlm_data;
	unsigned char	*start;
	size_t		dlm_size = 0;
	int		i;
	int		srsize;
	int		dlsize;
	int		match_size = 0;
	int		brkpt = 0;

	if (cob_exception_code) {
		return;
	}

	if (unstring_offset >= (int)unstring_src->size) {
		return;
	}

	start = unstring_src->data + unstring_offset;
	dlm_data = NULL;
	if (unstring_ndlms == 0) {
		match_size = cob_min_int ((int)COB_FIELD_SIZE (dst),
					  (int)unstring_src->size - unstring_offset);
		cob_memcpy (dst, start, match_size);
		unstring_offset += match_size;
	} else {

		srsize = (int) unstring_src->size;
		s = unstring_src->data + srsize;
		for (p = start; p < s; p++) {
			for (i = 0; i < unstring_ndlms; i++) {
				dlsize = (int) dlm_list[i].uns_dlm->size;
				dp = dlm_list[i].uns_dlm->data;
				if (p + dlsize > s) {
					break;
				}
				if (!memcmp (p, dp, (size_t)dlsize)) {
					match_size = (int)(p - start);
					cob_memcpy (dst, start, match_size);
					unstring_offset += match_size + dlsize;
					dlm_data = dp;
					dlm_size = dlsize;
					if (dlm_list[i].uns_all) {
						for (p++ ; p < s; p++) {
							if (p + dlsize > s) {
								break;
							}
							if (memcmp (p, dp, (size_t)dlsize)) {
								break;
							}
							unstring_offset += dlsize;
						}
					}
					brkpt = 1;
					break;
				}
			}
			if (brkpt) {
				break;
			}
		}
		if (!brkpt) {
			/* no match */
			match_size = (int)(unstring_src->size - unstring_offset);
			cob_memcpy (dst, start, match_size);
			unstring_offset = (int) unstring_src->size;
			dlm_data = NULL;
		}
	}
	unstring_count++;

	if (dlm) {
		if (dlm_data) {
			cob_memcpy (dlm, dlm_data, (int) dlm_size);
		} else if (COB_FIELD_IS_NUMERIC (dlm)) {
			cob_move (&cob_zero, dlm);
		} else {
			cob_move (&cob_space, dlm);
		}
	}

	if (cnt) {
		cob_set_int (cnt, match_size);
	}
}

void
cob_unstring_tallying (cob_field *f)
{
	cob_add_int (f, unstring_count);
}

void
cob_unstring_finish (void)
{
	if (unstring_offset < (int)unstring_src->size) {
		cob_set_exception (COB_EC_OVERFLOW_UNSTRING);
	}

	if (unstring_ptr) {
		cob_set_int (unstring_ptr, unstring_offset + 1);
	}
}

/* Initialization */

void
cob_init_strings (void)
{
	inspect_mark = cob_malloc (COB_MEDIUM_BUFF);
	lastsize = COB_MEDIUM_BUFF;
	alpha_attr.type = COB_TYPE_ALPHANUMERIC;
	alpha_attr.digits = 0;
	alpha_attr.scale = 0;
	alpha_attr.flags = 0;
	alpha_attr.pic = NULL;
	alpha_fld.size = 0;
	alpha_fld.data = NULL;
	alpha_fld.attr = &alpha_attr;
}
