/*
 * Copyright (C) 2019 Tokyo System House co.,ltd.
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
#include "defaults.h"

#include <stdio.h>
#include <string.h>

#ifdef	HAVE_JANSSON_H
#include <jansson.h>
#endif

/* Force symbol exports */
#define	COB_LIB_EXPIMP

#include "libcob.h"
#include "coblocal.h"
#include "lib/gettext.h"

/* Local functions */
static void
cob_hankaku_memcpy (cob_field *dst, unsigned char *src, const int size)
{
	cob_field	temp;
	cob_field_attr	attr;

	COB_ATTR_INIT (COB_TYPE_ALPHANUMERIC, 0, 0, 0, NULL);
	temp.size = size;
	temp.data = src;
	temp.attr = &attr;
	cob_hankaku_move (&temp, dst);
}

int
CBL_JSON_PARSE (unsigned char *b1, unsigned char *json_pointer_buf)
{
#ifdef	HAVE_JANSSON_H
	cob_field		*json_field;
	char			*json_str;
	json_t			*json;
	json_error_t	error;

	COB_CHK_PARMS (CBL_JSON_PARSE, 2);

	if (!cob_current_module->cob_procedure_parameters[0]) {
		// TODO
		return -1;
	}
	if (!cob_current_module->cob_procedure_parameters[1]) {
		// TODO
		return -1;
	}

	json_field = cob_current_module->cob_procedure_parameters[0];

	//parse json
	json_str = cob_malloc (json_field->size + 1);
	cob_field_to_string (json_field, json_str);

	json = json_loads (json_str, 0, &error);
	if (json == NULL) {
		// TODO
		fputs ("COBOL JSON PARSE ERROR\n", stderr);
		fputs (error.text, stderr);
		free(json_str);
		return -1;
	}

	free(json_str);
	memcpy(json_pointer_buf, &json, sizeof(void *));
#endif
	return 0;
}

int
CBL_JSON_FREE (unsigned char *json_pointer_buf)
{
#ifdef	HAVE_JANSSON_H
	json_t			*json;

	COB_CHK_PARMS (CBL_JSON_GET_ARRLEN, 1);

	if (!cob_current_module->cob_procedure_parameters[0]) {
		// TODO
		return -1;
	}

	memcpy(&json, json_pointer_buf, sizeof(void *));

	json_decref(json);
#endif
	return 0;
}

int
CBL_JSON_GET_TYPE (unsigned char *json_pointer_buf)
{
#ifdef HAVE_JANSSON_H
	json_t		*json;

	COB_CHK_PARMS (CBL_JSON_GET_TYPE, 1);

	if (!cob_current_module->cob_procedure_parameters[0]) {
		// TODO
		return -2;
	}

	memcpy(&json, json_pointer_buf, sizeof(void *));
	return json_typeof(json);
#endif
	return -1;
}

int
CBL_JSON_GET_KEY_START (unsigned char *json_pointer_buf,
	unsigned char *iter_pointer_buf)
{
#ifdef HAVE_JANSSON_H

	json_t		*json;
	void		*iter;

	COB_CHK_PARMS (CBL_JSON_GET_KEY_START, 2);

	if (!cob_current_module->cob_procedure_parameters[0]) {
		// TODO
		return -1;
	}
	if (!cob_current_module->cob_procedure_parameters[1]) {
		// TODO
		return -1;
	}

	memcpy(&json, json_pointer_buf, sizeof(void *));

	iter = json_object_iter(json);
	memcpy(iter_pointer_buf, &iter, sizeof(void *));
#endif
	return 0;
}

int
CBL_JSON_GET_KEY_NEXT (unsigned char *json_pointer_buf,
	unsigned char *iter_pointer_buf,
	unsigned char *key_buf)
{

#ifdef HAVE_JANSSON_H
	json_t			*json;
	void			*iter;
	cob_field		*key_field;
	const char		*key;

	COB_CHK_PARMS (CBL_JSON_GET_KEY_NEXT, 3);

	if (!cob_current_module->cob_procedure_parameters[0]) {
		// TODO
		return -1;
	}
	if (!cob_current_module->cob_procedure_parameters[1]) {
		// TODO
		return -1;
	}
	if (!cob_current_module->cob_procedure_parameters[2]) {
		// TODO
		return -1;
	}

	key_field = cob_current_module->cob_procedure_parameters[2];
	
	memcpy(&json, json_pointer_buf, sizeof(void *));
	memcpy(&iter, iter_pointer_buf, sizeof(void *));

	if (iter == NULL) {
		// EOF
		return 10;
	}

	key = json_object_iter_key (iter);
	iter = json_object_iter_next (json, iter);

	cob_hankaku_memcpy (key_field, (ucharptr)key, (int) strlen (key));
	memcpy(iter_pointer_buf, &iter, sizeof(void *));
#endif
	return 0;
}

int
CBL_JSON_GET_ARRLEN (unsigned char *json_pointer_buf)
{
#ifdef HAVE_JANSSON_H
	json_t			*json;

	COB_CHK_PARMS (CBL_JSON_GET_ARRLEN, 1);

	if (!cob_current_module->cob_procedure_parameters[0]) {
		// TODO
		return -1;
	}

	memcpy(&json, json_pointer_buf, sizeof(void *));

	return json_array_size(json);
#endif
	return 0;
}

int
CBL_JSON_GET_VALUE (unsigned char *json_pointer_buf,
	unsigned char *value_buf)
{
#ifdef HAVE_JANSSON_H
	json_t				*json;
	cob_field			*value_filed;
	char		p[COB_SMALL_BUFF];

	COB_CHK_PARMS (CBL_JSON_GET_VALUE, 2);

	if (!cob_current_module->cob_procedure_parameters[0]) {
		// TODO
		return -1;
	}
	if (!cob_current_module->cob_procedure_parameters[1]) {
		// TODO
		return -1;
	} 

	memcpy(&json, json_pointer_buf, sizeof(void *));
	value_filed = cob_current_module->cob_procedure_parameters[1];

	memset (p, 0, COB_SMALL_BUFF);
	if(json_is_string (json)) {
		snprintf (p, COB_SMALL_BUFF, "%s", json_string_value (json));
	} else if (json_is_integer (json)) {
		snprintf (p, COB_SMALL_BUFF, "%g", json_number_value (json));
	}
	cob_hankaku_memcpy (value_filed, (unsigned char *)p, (int) strlen (p));
#endif
	return 0;
}

int
CBL_JSON_GET_OBJECT (unsigned char *json_pointer_buf,
	unsigned char *key_buf,
	unsigned char *new_json_pointer_buf)
{
#ifdef HAVE_JANSSON_H
	json_t		*json;
	json_t		*new_json;
	cob_field	*key_field;
	char		*key;

	COB_CHK_PARMS (CBL_JSON_GET_OBJECT, 3);

	if (!cob_current_module->cob_procedure_parameters[0]) {
		// TODO
		return -1;
	}
	if (!cob_current_module->cob_procedure_parameters[1]) {
		// TODO
		return -1;
	}
	if (!cob_current_module->cob_procedure_parameters[2]) {
		// TODO
		return -1;
	}

	key_field = cob_current_module->cob_procedure_parameters[1];
	key = cob_malloc (key_field->size + 1);
	cob_field_to_string (key_field, key);

	memcpy(&json, json_pointer_buf, sizeof(void *));

	new_json = json_object_get (json, (const char *)key);
	memcpy(new_json_pointer_buf, &new_json, sizeof(void *));
#endif
	return 0;
}

int
CBL_JSON_GET_OBJECT_L (unsigned char *json_pointer_buf,
	unsigned char *key_buf,
	unsigned char *new_json_pointer_buf)
{
#ifdef HAVE_JANSSON_H
	json_t		*json;
	json_t		*new_json;
	cob_field	*key_field;
	char		*key;
	char		*tok;
	char		*start_adr;
	char		*end_adr;
	char		buf[COB_SMALL_BUFF];
	int			array_index;

	COB_CHK_PARMS (CBL_JSON_GET_OBJECT, 3);

	if (!cob_current_module->cob_procedure_parameters[0]) {
		// TODO
		return -1;
	}
	if (!cob_current_module->cob_procedure_parameters[1]) {
		// TODO
		return -1;
	}
	if (!cob_current_module->cob_procedure_parameters[2]) {
		// TODO
		return -1;
	}

	key_field = cob_current_module->cob_procedure_parameters[1];
	key = cob_malloc (key_field->size + 1);
	cob_field_to_string (key_field, key);

	memcpy(&json, json_pointer_buf, sizeof(void *));
	new_json = json;

	tok = strtok (key, ".");

	while (tok != NULL) {
		start_adr = strchr (tok, (int)'[');
		end_adr = strchr (tok, (int)']');
		if (start_adr && end_adr && (start_adr < end_adr)) {
			memset (buf, 0, COB_SMALL_BUFF);
			strncpy (buf, tok, start_adr - tok);
			new_json = json_object_get (new_json, buf);

			if (!json_is_array (new_json)) {
				// TODO
				free (key);
				return -3;
			}

			memset (buf, 0, COB_SMALL_BUFF);
			strncpy (buf, start_adr + 1, end_adr - start_adr - 1);
			array_index = atoi (buf);
			new_json = json_array_get (new_json, array_index);
		} else {
			new_json = json_object_get (new_json, tok);
		}

		tok = strtok(NULL, ".");
	}

	if (!new_json) {
		// TODO
		free (key);
		return -4;
	}

	memcpy(new_json_pointer_buf, &new_json, sizeof(void *));
	free (key);
#endif
	return 0;
}

int
CBL_JSON_GET_OBJECT_A (unsigned char *json_pointer_buf,
	unsigned char *index_buf,
	unsigned char *new_json_pointer_buf)
{
#ifdef HAVE_JANSSON_H
	json_t			*json;
	json_t			*new_json;
	cob_field		*index_field;
	int				index;
	cob_field_attr	attr;
	cob_field		temp;

	COB_CHK_PARMS (CBL_JSON_GET_OBJECT, 3);

	if (!cob_current_module->cob_procedure_parameters[0]) {
		// TODO
		return -1;
	}
	if (!cob_current_module->cob_procedure_parameters[1]) {
		// TODO
		return -1;
	}
	if (!cob_current_module->cob_procedure_parameters[2]) {
		// TODO
		return -1;
	}

	index_field = cob_current_module->cob_procedure_parameters[1];

	COB_ATTR_INIT (COB_TYPE_NUMERIC_BINARY, sizeof(int), 0, 0, NULL);

	temp.size = sizeof(int);
	temp.data = (unsigned char *)&index;
	temp.attr = &attr;
	cob_move (index_field, &temp);

	memcpy(&json, json_pointer_buf, sizeof(void *));

	new_json = json_array_get (json, index);
	memcpy(new_json_pointer_buf, &new_json, sizeof(void *));
#endif
	return 0;
}
