/*
 * Copyright (C) 2001-2009 Keisuke Nishida
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
#include "defaults.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#ifdef	HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <time.h>
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#ifdef	_WIN32
#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#undef	HAVE_SIGNAL_H
#endif

#ifdef	HAVE_SIGNAL_H
#include <signal.h>
#endif

#ifdef	HAVE_LOCALE_H
#include <locale.h>
#endif

#include "common.h"
#include "coblocal.h"
#include "move.h"
#include "numeric.h"
#include "termio.h"
#include "fileio.h"
#include "call.h"
#include "screenio.h"
#include "intrinsic.h"
#include "lib/gettext.h"

struct cob_exception {
	const char	*name;
	const int	code;
	const int	critical;
};

struct cob_alloc_cache {
	struct cob_alloc_cache	*next;
	void			*cob_pointer;
	size_t			size;
};

#define COB_ERRBUF_SIZE	256

/* Local variables */

static int			cob_argc = 0;
static char			**cob_argv = NULL;
static struct cob_alloc_cache	*cob_alloc_base = NULL;

static char			*cob_local_env = NULL;
static int			current_arg = 1;
static unsigned char		*commlnptr = NULL;
static size_t			commlncnt = 0;

static char			*locale_save = NULL;

static size_t			sort_nkeys;
static struct cob_file_key	*sort_keys;
static const unsigned char	*sort_collate;

static const char		*cob_current_program_id = NULL;
static const char		*cob_current_section = NULL;
static const char		*cob_current_paragraph = NULL;
static const char		*cob_source_file = NULL;
static const char		*cob_source_statement = NULL;
static unsigned int		cob_source_line = 0;
static size_t			cob_line_trace = 0;

#ifdef	HAVE_SIGNAL_H
typedef void (*cob_sighandler_t) (int);
static cob_sighandler_t		hupsig = NULL;
static cob_sighandler_t		intsig = NULL;
static cob_sighandler_t		qutsig = NULL;
#endif

#ifdef	COB_PARAM_CHECK
static const char	parm_msg[] = "CALL to %s requires %d parameters";
#endif

#undef	COB_EXCEPTION
#define COB_EXCEPTION(code,tag,name,critical)	name,
static const char		* const cob_exception_tab_name[] = {
	NULL,		/* COB_EC_ZERO */
#include "exception.def"
	NULL		/* COB_EC_MAX */
};

#undef	COB_EXCEPTION
#define COB_EXCEPTION(code,tag,name,critical)	0x##code,
static const int		cob_exception_tab_code[] = {
	0,		/* COB_EC_ZERO */
#include "exception.def"
	0		/* COB_EC_MAX */
};

#undef	COB_EXCEPTION

#define EXCEPTION_TAB_SIZE	sizeof(cob_exception_tab_code) / sizeof(int)

/*
#define EXCEPTION_TAB_SIZE	sizeof(cob_exception_table) / sizeof(struct cob_exception)
*/

static int		cob_switch[8];

/* Runtime exit handling */
static struct exit_handlerlist {
	struct exit_handlerlist	*next;
	int			(*proc)(void);
} *exit_hdlrs = NULL;

/* Runtime error handling */
static struct handlerlist {
	struct handlerlist	*next;
	int			(*proc)(char *s);
} *hdlrs = NULL;

static char			*runtime_err_str;

static cob_field_attr	all_attr = { COB_TYPE_ALPHANUMERIC_ALL, 0, 0, 0, NULL };
static cob_field_attr	one_attr = { COB_TYPE_NUMERIC, 1, 0, 0, NULL };

/* Global variables */

struct cob_module	*cob_current_module = NULL;

int			cob_initialized = 0;
int			cob_exception_code = 0;

int			cob_call_params = 0;
int			cob_save_call_params = 0;
int			cob_initial_external = 0;
int			cob_got_exception = 0;

const char		*cob_orig_statement = NULL;
const char		*cob_orig_program_id = NULL;
const char		*cob_orig_section = NULL;
const char		*cob_orig_paragraph = NULL;
unsigned int		cob_orig_line = 0;

cob_field		cob_zero = { 1, (ucharptr)"0", &all_attr };
cob_field		cob_space = { 1, (ucharptr)" ", &all_attr };
cob_field		cob_high = { 1, (ucharptr)"\xff", &all_attr };
cob_field		cob_low = { 1, (ucharptr)"\0", &all_attr };
cob_field		cob_quote = { 1, (ucharptr)"\"", &all_attr };
cob_field		cob_one = { 1, (ucharptr)"1", &one_attr };

/* Local functions */

#ifdef	HAVE_SIGNAL_H
static void COB_NOINLINE
cob_sig_handler (int sig)
{
#ifdef	SIGSEGV
	if (sig == SIGSEGV) {
		if (cob_source_file) {
			fprintf (stderr, "%s:%d: ", cob_source_file, cob_source_line);
		}
		fprintf (stderr, "Attempt to reference unallocated memory (Signal SIGSEGV)\n");
		fprintf (stderr, "Abnormal termination - File contents may be incorrect\n");
		fflush (stderr);
		exit (SIGSEGV);
	}
#endif
	if (cob_initialized) {
		cob_screen_terminate ();
		cob_exit_fileio ();
		fprintf (stderr, "Abnormal termination - File contents may not be correct\n");
		fflush (stderr);
	}
	switch (sig) {
#ifdef	SIGHUP
	case SIGHUP:
		if ((hupsig != SIG_IGN) && (hupsig != SIG_DFL)) {
			(*hupsig) (SIGHUP);
		}
		break;
#endif
#ifdef	SIGINT
	case SIGINT:
		if ((intsig != SIG_IGN) && (intsig != SIG_DFL)) {
			(*intsig) (SIGINT);
		}
		break;
#endif
#ifdef	SIGQUIT
	case SIGQUIT:
		if ((qutsig != SIG_IGN) && (qutsig != SIG_DFL)) {
			(*qutsig) (SIGQUIT);
		}
		break;
	}
#endif
	exit (sig);
}
#endif

static void
cob_set_signal (void)
{
#ifdef	HAVE_SIGNAL_H
#ifdef	SIGINT
	if ((intsig = signal (SIGINT, cob_sig_handler)) == SIG_IGN) {
		(void)signal (SIGINT, SIG_IGN);
	}
#endif
#ifdef	SIGHUP
	if ((hupsig = signal (SIGHUP, cob_sig_handler)) == SIG_IGN) {
		(void)signal (SIGHUP, SIG_IGN);
	}
#endif
#ifdef	SIGQUIT
	if ((qutsig = signal (SIGQUIT, cob_sig_handler)) == SIG_IGN) {
		(void)signal (SIGQUIT, SIG_IGN);
	}
#endif
	/* Take direct control of segementation violation */
#ifdef	SIGSEGV
	(void)signal (SIGSEGV, cob_sig_handler);
#endif
#endif
}

#ifdef	COB_EBCDIC_MACHINE
static void
cob_get_sign_ascii (unsigned char *p)
{
	switch (*p) {
	case 'p':
		*p = (unsigned char)'0';
		return;
	case 'q':
		*p = (unsigned char)'1';
		return;
	case 'r':
		*p = (unsigned char)'2';
		return;
	case 's':
		*p = (unsigned char)'3';
		return;
	case 't':
		*p = (unsigned char)'4';
		return;
	case 'u':
		*p = (unsigned char)'5';
		return;
	case 'v':
		*p = (unsigned char)'6';
		return;
	case 'w':
		*p = (unsigned char)'7';
		return;
	case 'x':
		*p = (unsigned char)'8';
		return;
	case 'y':
		*p = (unsigned char)'9';
		return;
	}
}
#endif

static int COB_NOINLINE
cob_get_sign_ebcdic (unsigned char *p)
{
	switch (*p) {
	case '{':
		*p = (unsigned char)'0';
		return 1;
	case 'A':
		*p = (unsigned char)'1';
		return 1;
	case 'B':
		*p = (unsigned char)'2';
		return 1;
	case 'C':
		*p = (unsigned char)'3';
		return 1;
	case 'D':
		*p = (unsigned char)'4';
		return 1;
	case 'E':
		*p = (unsigned char)'5';
		return 1;
	case 'F':
		*p = (unsigned char)'6';
		return 1;
	case 'G':
		*p = (unsigned char)'7';
		return 1;
	case 'H':
		*p = (unsigned char)'8';
		return 1;
	case 'I':
		*p = (unsigned char)'9';
		return 1;
	case '}':
		*p = (unsigned char)'0';
		return -1;
	case 'J':
		*p = (unsigned char)'1';
		return -1;
	case 'K':
		*p = (unsigned char)'2';
		return -1;
	case 'L':
		*p = (unsigned char)'3';
		return -1;
	case 'M':
		*p = (unsigned char)'4';
		return -1;
	case 'N':
		*p = (unsigned char)'5';
		return -1;
	case 'O':
		*p = (unsigned char)'6';
		return -1;
	case 'P':
		*p = (unsigned char)'7';
		return -1;
	case 'Q':
		*p = (unsigned char)'8';
		return -1;
	case 'R':
		*p = (unsigned char)'9';
		return -1;
	default:
		/* What to do here */
		*p = (unsigned char)'0';
		return 1;
	}
/* NOT REACHED */
	return 1;
}

static void COB_NOINLINE
cob_put_sign_ebcdic (unsigned char *p, const int sign)
{
	if (sign < 0) {
		switch (*p) {
		case '0':
			*p = (unsigned char)'}';
			return;
		case '1':
			*p = (unsigned char)'J';
			return;
		case '2':
			*p = (unsigned char)'K';
			return;
		case '3':
			*p = (unsigned char)'L';
			return;
		case '4':
			*p = (unsigned char)'M';
			return;
		case '5':
			*p = (unsigned char)'N';
			return;
		case '6':
			*p = (unsigned char)'O';
			return;
		case '7':
			*p = (unsigned char)'P';
			return;
		case '8':
			*p = (unsigned char)'Q';
			return;
		case '9':
			*p = (unsigned char)'R';
			return;
		default:
			/* What to do here */
			*p = (unsigned char)'}';
			return;
		}
	}
	switch (*p) {
	case '0':
		*p = (unsigned char)'{';
		return;
	case '1':
		*p = (unsigned char)'A';
		return;
	case '2':
		*p = (unsigned char)'B';
		return;
	case '3':
		*p = (unsigned char)'C';
		return;
	case '4':
		*p = (unsigned char)'D';
		return;
	case '5':
		*p = (unsigned char)'E';
		return;
	case '6':
		*p = (unsigned char)'F';
		return;
	case '7':
		*p = (unsigned char)'G';
		return;
	case '8':
		*p = (unsigned char)'H';
		return;
	case '9':
		*p = (unsigned char)'I';
		return;
	default:
		/* What to do here */
		*p = (unsigned char)'{';
		return;
	}
/* NOT REACHED */
}

static int
common_cmpc (const unsigned char *s1, const unsigned int c, const size_t size)
{
	const unsigned char	*s;
	size_t			i;
	int			ret;

	s = cob_current_module->collating_sequence;
	if (unlikely(s)) {
		for (i = 0; i < size; ++i) {
			if ((ret = s[s1[i]] - s[c]) != 0) {
				return ret;
			}
		}
	} else {
		for (i = 0; i < size; ++i) {
			if ((ret = s1[i] - c) != 0) {
				return ret;
			}
		}
	}
	return 0;
}

static int
common_cmps (const unsigned char *s1, const unsigned char *s2, const size_t size,
	     const unsigned char *col)
{
	size_t			i;
	int			ret;

	if (unlikely(col)) {
		for (i = 0; i < size; ++i) {
			if ((ret = col[s1[i]] - col[s2[i]]) != 0) {
				return ret;
			}
		}
	} else {
		for (i = 0; i < size; ++i) {
			if ((ret = s1[i] - s2[i]) != 0) {
				return ret;
			}
		}
	}
	return 0;
}

static int
cob_cmp_char (cob_field *f, const unsigned int c)
{
	int	sign;
	int	ret;

	sign = cob_get_sign (f);
	ret = common_cmpc (f->data, c, f->size);
	if (COB_FIELD_TYPE (f) != COB_TYPE_NUMERIC_PACKED) {
		cob_put_sign (f, sign);
	}
	return ret;
}

static int
cob_cmp_all (cob_field *f1, cob_field *f2)
{
	unsigned char		*data;
	const unsigned char	*s;
	size_t			size;
	int			ret;
	int			sign;

	size = f1->size;
	data = f1->data;
	sign = cob_get_sign (f1);
	ret = 0;
	s = cob_current_module->collating_sequence;
	while (size >= f2->size) {
		if ((ret = common_cmps (data, f2->data, f2->size, s)) != 0) {
			goto end;
		}
		size -= f2->size;
		data += f2->size;
	}
	if (size > 0) {
		ret = common_cmps (data, f2->data, size, s);
	}

end:
	if (COB_FIELD_TYPE (f1) != COB_TYPE_NUMERIC_PACKED) {
		cob_put_sign (f1, sign);
	}
	return ret;
}

static int
cob_cmp_alnum (cob_field *f1, cob_field *f2)
{
	const unsigned char	*s;
	size_t			min;
	int			ret;
	int			sign1;
	int			sign2;

	sign1 = cob_get_sign (f1);
	sign2 = cob_get_sign (f2);
	min = (f1->size < f2->size) ? f1->size : f2->size;
	s = cob_current_module->collating_sequence;
	/* compare common substring */
	if ((ret = common_cmps (f1->data, f2->data, min, s)) != 0) {
		goto end;
	}

	/* compare the rest (if any) with spaces */
	if (f1->size > f2->size) {
		ret = common_cmpc (f1->data + min, ' ', f1->size - min);
	} else if (f1->size < f2->size) {
		ret = -common_cmpc (f2->data + min, ' ', f2->size - min);
	}

end:
	if (COB_FIELD_TYPE (f1) != COB_TYPE_NUMERIC_PACKED) {
		cob_put_sign (f1, sign1);
	}
	if (COB_FIELD_TYPE (f2) != COB_TYPE_NUMERIC_PACKED) {
		cob_put_sign (f2, sign2);
	}
	return ret;
}

static int
sort_compare (const void *data1, const void *data2)
{
	size_t		i;
	int		cmp;
	cob_field	f1;
	cob_field	f2;

	for (i = 0; i < sort_nkeys; ++i) {
		f1 = f2 = *sort_keys[i].field;
		f1.data = (unsigned char *)data1 + sort_keys[i].offset;
		f2.data = (unsigned char *)data2 + sort_keys[i].offset;
		if (COB_FIELD_IS_NUMERIC(&f1)) {
			cmp = cob_numeric_cmp (&f1, &f2);
		} else {
			cmp = common_cmps (f1.data, f2.data, f1.size, sort_collate);
		}
		if (cmp != 0) {
			return (sort_keys[i].flag == COB_ASCENDING) ? cmp : -cmp;
		}
	}
	return 0;
}

/*
 * Global functions
 */

void *
cob_malloc (const size_t size)
{
	void *mptr;

	mptr = calloc (1, size);
	if (unlikely(!mptr)) {
		cob_runtime_error ("Cannot acquire %d bytes of memory - Aborting", size);
		cob_stop_run (1);
	}
	return mptr;
}

void
cob_set_location (const char *progid, const char *sfile, const unsigned int sline,
		  const char *csect, const char *cpara, const char *cstatement)
{
	cob_current_program_id = progid;
	cob_source_file = sfile;
	cob_source_line = sline;
	cob_current_section = csect;
	cob_current_paragraph = cpara;
	if (cstatement) {
		cob_source_statement = cstatement;
	}
	if (cob_line_trace) {
		fprintf (stderr, "PROGRAM-ID: %s \tLine: %d \tStatement: %s\n",
			(char *)progid, sline, cstatement ? (char *)cstatement : "Unknown");
		fflush (stderr);
	}
}

void
cob_ready_trace (void)
{
	cob_line_trace = 1;
}

void
cob_reset_trace (void)
{
	cob_line_trace = 0;
}

unsigned char *
cob_get_pointer (const unsigned char *srcptr)
{
	unsigned char	*tmptr;

	memcpy (&tmptr, srcptr, sizeof (void *));
	return tmptr;
}

void *
cob_get_prog_pointer (const unsigned char *srcptr)
{
	void	*tmptr;

	memcpy (&tmptr, srcptr, sizeof (void *));
	return tmptr;
}

void
cob_memcpy (cob_field *dst, unsigned char *src, const int size)
{
	cob_field	temp;
	cob_field_attr	attr;

	COB_ATTR_INIT (COB_TYPE_ALPHANUMERIC, 0, 0, 0, NULL);
	temp.size = size;
	temp.data = src;
	temp.attr = &attr;
	cob_move (&temp, dst);
}

const char *
cob_get_exception_name (const int exception_code)
{
	size_t	n;

	for (n = 0; n < EXCEPTION_TAB_SIZE; ++n) {
		if (exception_code == cob_exception_tab_code[n]) {
			return cob_exception_tab_name[n];
		}
	}
	return NULL;
}

void
cob_set_exception (const int id)
{
	cob_exception_code = cob_exception_tab_code[id];
	if (cob_exception_code) {
		cob_got_exception = 1;
		cob_orig_statement = cob_source_statement;
		cob_orig_line = cob_source_line;
		cob_orig_program_id = cob_current_program_id;
		cob_orig_section = cob_current_section;
		cob_orig_paragraph = cob_current_paragraph;
	}
}

void
cob_init (int argc, char **argv)
{
	char	*s;
	size_t	i;
	char	buff[32];

	if (!cob_initialized) {
		cob_set_signal ();

		cob_argc = argc;
		cob_argv = argv;

		/* Get emergency buffer */
		runtime_err_str = cob_malloc (COB_ERRBUF_SIZE);

#ifdef	HAVE_SETLOCALE
		setlocale (LC_ALL, "");
		setlocale (LC_NUMERIC, "C");
		s = setlocale (LC_ALL, NULL);
		if (s) {
			locale_save = strdup (s);
		}
#endif
#ifdef	ENABLE_NLS
		bindtextdomain (PACKAGE, LOCALEDIR);
		textdomain (PACKAGE);
#endif

/* Dirty hack until we implement something better */
#if defined(_WIN32) && !defined(_MSC_VER)
		_setmode (_fileno (stdin), _O_BINARY);
		_setmode (_fileno (stdout), _O_BINARY);
		_setmode (_fileno (stderr), _O_BINARY);
#endif

		cob_init_numeric ();
		cob_init_strings ();
		cob_init_move ();
		cob_init_intrinsic ();
		cob_init_fileio ();
		cob_init_termio ();
		cob_init_call ();

		for (i = 0; i < 8; ++i) {
			memset (buff, 0, sizeof (buff));
			snprintf (buff, 31, "COB_SWITCH_%d", (int)(i + 1));
			s = getenv (buff);
			if (s && strcasecmp (s, "ON") == 0) {
				cob_switch[i] = 1;
			} else {
				cob_switch[i] = 0;
			}
		}

		s = getenv ("COB_LINE_TRACE");
		if (s && (*s == 'Y' || *s == 'y')) {
			cob_line_trace = 1;
		}

		cob_initialized = 1;
	}
}

void
cob_module_enter (struct cob_module *module)
{
	if (unlikely(!cob_initialized)) {
		fputs ("Warning: cob_init expected in the main program\n", stderr);
		cob_init (0, NULL);
	}

	module->next = cob_current_module;
	cob_current_module = module;
}

void
cob_module_leave (struct cob_module *module)
{
	cob_current_module = cob_current_module->next;
}

void
cob_stop_run (const int status)
{
	struct exit_handlerlist	*h;

	if (exit_hdlrs != NULL) {
		h = exit_hdlrs;
		while (h != NULL) {
			h->proc ();
			h = h->next;
		}
	}
	cob_screen_terminate ();
	cob_exit_fileio ();
	exit (status);
}

void COB_NOINLINE
cob_runtime_error (const char *fmt, ...)
{
	struct handlerlist	*h;
	char			*p;
	va_list			ap;

	if (hdlrs != NULL) {
		h = hdlrs;
		if (runtime_err_str) {
			p = runtime_err_str;
			if (cob_source_file) {
				sprintf (runtime_err_str, "%s:%d: ",
					 cob_source_file, cob_source_line);
				p = runtime_err_str + strlen (runtime_err_str);
			}
			va_start (ap, fmt);
			vsprintf (p, fmt, ap);
			va_end (ap);
		}
		while (h != NULL) {
			if (runtime_err_str) {
				h->proc (runtime_err_str);
			} else {
				h->proc ((char *)"Malloc error");
			}
			h = h->next;
		}
		hdlrs = NULL;
	}

	/* prefix */
	if (cob_source_file) {
		fprintf (stderr, "%s:%d: ", cob_source_file, cob_source_line);
	}
	fputs ("libcob: ", stderr);

	/* body */
	va_start (ap, fmt);
	vfprintf (stderr, fmt, ap);
	va_end (ap);

	/* postfix */
	fputs ("\n", stderr);
	fflush (stderr);
}

void
cob_fatal_error (const unsigned int fatal_error)
{
	switch (fatal_error) {
	case COB_FERROR_INITIALIZED:
		cob_runtime_error ("cob_init() has not been called");
		break;
	case COB_FERROR_CODEGEN:
		cob_runtime_error ("Codegen error - Please report this");
		break;
	case COB_FERROR_CHAINING:
		cob_runtime_error ("ERROR - Recursive call of chained program");
		break;
	case COB_FERROR_STACK:
		cob_runtime_error ("Stack overflow, possible PERFORM depth exceeded");
		break;
	default:
		cob_runtime_error ("Unknown failure : %d", (int)fatal_error);
		break;
	}
	cob_stop_run (1);
}

void
cob_check_version (const char *prog, const char *packver, const int patchlev)
{
	if (strcmp (packver, PACKAGE_VERSION) || patchlev > PATCH_LEVEL) {
		cob_runtime_error ("Error - Version mismatch");
		cob_runtime_error ("%s has version/patch level %s/%d", prog, packver,
				   patchlev);
		cob_runtime_error ("Library has version/patch level %s/%d", PACKAGE_VERSION,
				   PATCH_LEVEL);
		cob_stop_run (1);
	}
}

/*
 * Sign
 */

int
cob_real_get_sign (cob_field *f)
{
	unsigned char	*p;

	switch (COB_FIELD_TYPE (f)) {
	case COB_TYPE_NUMERIC_DISPLAY:
		/* locate sign */
		if (unlikely(COB_FIELD_SIGN_LEADING (f))) {
			p = f->data;
		} else {
			p = f->data + f->size - 1;
		}

		/* get sign */
		if (unlikely(COB_FIELD_SIGN_SEPARATE (f))) {
			return (*p == '+') ? 1 : -1;
		} else {
			if (*p >= '0' && *p <= '9') {
				return 1;
			}
			if (*p == ' ') {
				*p = (unsigned char)'0';
				return 1;
			}
			if (unlikely(cob_current_module->display_sign)) {
				return cob_get_sign_ebcdic (p);
			} else {
#ifdef	COB_EBCDIC_MACHINE
				cob_get_sign_ascii (p);
#else
				GET_SIGN_ASCII (*p);
#endif
				return -1;
			}
		}
	case COB_TYPE_NUMERIC_PACKED:
		p = f->data + f->size - 1;
		return ((*p & 0x0f) == 0x0d) ? -1 : 1;
	default:
		return 0;
	}
}

void
cob_real_put_sign (cob_field *f, const int sign)
{
	unsigned char	*p;
	int		c;

	switch (COB_FIELD_TYPE (f)) {
	case COB_TYPE_NUMERIC_DISPLAY:
		/* locate sign */
		if (unlikely(COB_FIELD_SIGN_LEADING (f))) {
			p = f->data;
		} else {
			p = f->data + f->size - 1;
		}

		/* put sign */
		if (unlikely(COB_FIELD_SIGN_SEPARATE (f))) {
			c = (sign < 0) ? '-' : '+';
			if (*p != c) {
				*p = c;
			}
		} else if (unlikely(cob_current_module->display_sign)) {
			cob_put_sign_ebcdic (p, sign);
		} else if (sign < 0) {
#ifdef	COB_EBCDIC_MACHINE
			cob_put_sign_ascii (p);
#else
			PUT_SIGN_ASCII (*p);
#endif
		}
		return;
	case COB_TYPE_NUMERIC_PACKED:
		p = f->data + f->size - 1;
		if (sign < 0) {
			*p = (*p & 0xf0) | 0x0d;
		} else {
			*p = (*p & 0xf0) | 0x0c;
		}
		return;
	default:
		return;
	}
}

void
cob_field_to_string (const cob_field *f, char *s)
{
	int	i;

	memcpy (s, f->data, f->size);
	for (i = (int) f->size - 1; i >= 0; i--) {
		if (s[i] != ' ' && s[i] != 0) {
			break;
		}
	}
	s[i + 1] = '\0';
}

/*
 * Switch
 */

int
cob_get_switch (const int n)
{
	return cob_switch[n];
}

void
cob_set_switch (const int n, const int flag)
{
	if (flag == 0) {
		cob_switch[n] = 0;
	} else if (flag == 1) {
		cob_switch[n] = 1;
	}
}

int
cob_cmp (cob_field *f1, cob_field *f2)
{
	cob_field	temp;
	cob_field_attr	attr;
	unsigned char	buff[48];

	if (COB_FIELD_IS_NUMERIC (f1) && COB_FIELD_IS_NUMERIC (f2)) {
		return cob_numeric_cmp (f1, f2);
	}
	if (COB_FIELD_TYPE (f2) == COB_TYPE_ALPHANUMERIC_ALL) {
		if (f2 == &cob_zero && COB_FIELD_IS_NUMERIC (f1)) {
			return cob_cmp_int (f1, 0);
		} else if (f2->size == 1) {
			return cob_cmp_char (f1, f2->data[0]);
		} else {
			return cob_cmp_all (f1, f2);
		}
	} else if (COB_FIELD_TYPE (f1) == COB_TYPE_ALPHANUMERIC_ALL) {
		if (f1 == &cob_zero && COB_FIELD_IS_NUMERIC (f2)) {
			return -cob_cmp_int (f2, 0);
		} else if (f1->size == 1) {
			return -cob_cmp_char (f2, f1->data[0]);
		} else {
			return -cob_cmp_all (f2, f1);
		}
	} else {
		if (COB_FIELD_IS_NUMERIC (f1)
		    && COB_FIELD_TYPE (f1) != COB_TYPE_NUMERIC_DISPLAY) {
			temp.size = COB_FIELD_DIGITS(f1);
			temp.data = buff;
			temp.attr = &attr;
			attr = *f1->attr;
			attr.type = COB_TYPE_NUMERIC_DISPLAY;
			attr.flags &= ~COB_FLAG_HAVE_SIGN;
			cob_move (f1, &temp);
			f1 = &temp;
		}
		if (COB_FIELD_IS_NUMERIC (f2)
		    && COB_FIELD_TYPE (f2) != COB_TYPE_NUMERIC_DISPLAY) {
			temp.size = COB_FIELD_DIGITS(f2);
			temp.data = buff;
			temp.attr = &attr;
			attr = *f2->attr;
			attr.type = COB_TYPE_NUMERIC_DISPLAY;
			attr.flags &= ~COB_FLAG_HAVE_SIGN;
			cob_move (f2, &temp);
			f2 = &temp;
		}
		return cob_cmp_alnum (f1, f2);
	}
}

/*
 * Class check
 */

int
cob_is_omitted (const cob_field *f)
{
	return f->data == NULL;
}

int
cob_is_numeric (cob_field *f)
{
	unsigned char	*data;
	size_t		size;
	size_t		i;
	int		sign;

	switch (COB_FIELD_TYPE (f)) {
	case COB_TYPE_NUMERIC_BINARY:
	case COB_TYPE_NUMERIC_FLOAT:
	case COB_TYPE_NUMERIC_DOUBLE:
		return 1;
	case COB_TYPE_NUMERIC_PACKED:
		/* check digits */
		for (i = 0; i < f->size - 1; ++i) {
			if ((f->data[i] & 0xf0) > 0x90 || (f->data[i] & 0x0f) > 0x09) {
				return 0;
			}
		}
		if ((f->data[i] & 0xf0) > 0x90) {
			return 0;
		}
		/* check sign */
		sign = f->data[i] & 0x0f;
		if (sign == 0x0f) {
			return 1;
		}
		if (COB_FIELD_HAVE_SIGN (f)) {
			if (sign == 0x0c || sign == 0x0d) {
				return 1;
			}
		}
		return 0;
	case COB_TYPE_NUMERIC_DISPLAY:
		data = COB_FIELD_DATA (f);
		size = COB_FIELD_SIZE (f);
		sign = cob_get_sign (f);
		for (i = 0; i < size; ++i) {
			if (!isdigit (data[i])) {
				cob_put_sign (f, sign);
				return 0;
			}
		}
		cob_put_sign (f, sign);
		return 1;
	default:
		for (i = 0; i < f->size; ++i) {
			if (!isdigit (f->data[i])) {
				return 0;
			}
		}
		return 1;
	}
}

int
cob_is_alpha (const cob_field *f)
{
	size_t	i;

	for (i = 0; i < f->size; ++i) {
		if (!isspace (f->data[i]) && !isalpha (f->data[i])) {
			return 0;
		}
	}
	return 1;
}

int
cob_is_upper (const cob_field *f)
{
	size_t	i;

	for (i = 0; i < f->size; ++i) {
		if (!isspace (f->data[i]) && !isupper (f->data[i])) {
			return 0;
		}
	}
	return 1;
}

int
cob_is_lower (const cob_field *f)
{
	size_t	i;

	for (i = 0; i < f->size; ++i) {
		if (!isspace (f->data[i]) && !islower (f->data[i])) {
			return 0;
		}
	}
	return 1;
}

/*
 * Table sort
 */

void
cob_table_sort_init (const int nkeys, const unsigned char *collating_sequence)
{
	sort_nkeys = 0;
	sort_keys = cob_malloc (nkeys * sizeof (struct cob_file_key));
	if (collating_sequence) {
		sort_collate = collating_sequence;
	} else {
		sort_collate = cob_current_module->collating_sequence;
	}
}

void
cob_table_sort_init_key (const int flag, cob_field *field, size_t offset)
{
	sort_keys[sort_nkeys].flag = flag;
	sort_keys[sort_nkeys].field = field;
	sort_keys[sort_nkeys].offset = offset;
	sort_nkeys++;
}

void
cob_table_sort (cob_field *f, const int n)
{
	qsort (f->data, (size_t) n, f->size, sort_compare);
	free (sort_keys);
}

/*
 * Run-time error checking
 */

void
cob_check_based (const unsigned char *x, const char *name)
{
	if (!x) {
		cob_runtime_error ("BASED/LINKAGE item '%s' has NULL address", name);
		cob_stop_run (1);
	}
}

void
cob_check_numeric (cob_field *f, const char *name)
{
	unsigned char	*data;
	char		*p;
	char		*buff;
	size_t		i;

	if (!cob_is_numeric (f)) {
		buff = cob_malloc (COB_SMALL_BUFF);
		p = buff;
		data = f->data;
		for (i = 0; i < f->size; ++i) {
			if (isprint (data[i])) {
				*p++ = data[i];
			} else {
				p += sprintf (p, "\\%03o", data[i]);
			}
		}
		*p = '\0';
		cob_runtime_error ("'%s' not numeric: '%s'", name, buff);
		cob_stop_run (1);
	}
}

void
cob_check_odo (const int i, const int min, const int max, const char *name)
{
	/* check the OCCURS DEPENDING ON item */
	if (i < min || max < i) {
		cob_set_exception (COB_EC_BOUND_ODO);
		cob_runtime_error ("OCCURS DEPENDING ON '%s' out of bounds: %d", name, i);
		cob_stop_run (1);
	}
}

void
cob_check_subscript (const int i, const int min, const int max, const char *name)
{
	/* check the subscript */
	if (i < min || max < i) {
		cob_set_exception (COB_EC_BOUND_SUBSCRIPT);
		cob_runtime_error ("Subscript of '%s' out of bounds: %d", name, i);
		cob_stop_run (1);
	}
}

void
cob_check_ref_mod (const int offset, const int length, const int size, const char *name)
{
	/* check the offset */
	if (offset < 1 || offset > size) {
		cob_set_exception (COB_EC_BOUND_REF_MOD);
		cob_runtime_error ("Offset of '%s' out of bounds: %d", name, offset);
		cob_stop_run (1);
	}

	/* check the length */
	if (length < 1 || offset + length - 1 > size) {
		cob_set_exception (COB_EC_BOUND_REF_MOD);
		cob_runtime_error ("Length of '%s' out of bounds: %d", name, length);
		cob_stop_run (1);
	}
}

unsigned char *
cob_external_addr (const char *exname, const int exlength)
{
	static struct cob_external *basext = NULL;

	struct cob_external *eptr;

	for (eptr = basext; eptr; eptr = eptr->next) {
		if (!strcmp (exname, eptr->ename)) {
			if (exlength > eptr->esize) {
				cob_runtime_error ("EXTERNAL item '%s' has size > %d",
						   exname, exlength);
				cob_stop_run (1);
			}
			cob_initial_external = 0;
			return (ucharptr)eptr->ext_alloc;
		}
	}
	eptr = cob_malloc (sizeof (struct cob_external));
	eptr->next = basext;
	eptr->esize = exlength;
	eptr->ename = cob_malloc (strlen (exname) + 1);
	strcpy (eptr->ename, exname);
	eptr->ext_alloc = cob_malloc ((size_t)exlength);
	basext = eptr;
	cob_initial_external = 1;
	return (ucharptr)eptr->ext_alloc;
}

/* Extended ACCEPT/DISPLAY */

void
cob_accept_date (cob_field *f)
{
	time_t	t;
	char	s[8];

	t = time (NULL);
	strftime (s, 7, "%y%m%d", localtime (&t));
	cob_memcpy (f, (ucharptr)s, 6);
}

void
cob_accept_date_yyyymmdd (cob_field *f)
{
	time_t	t;
	char	s[12];

	t = time (NULL);
	strftime (s, 9, "%Y%m%d", localtime (&t));
	cob_memcpy (f, (ucharptr)s, 8);
}

void
cob_accept_day (cob_field *f)
{
	time_t	t;
	char	s[8];

	t = time (NULL);
	strftime (s, 6, "%y%j", localtime (&t));
	cob_memcpy (f, (ucharptr)s, 5);
}

void
cob_accept_day_yyyyddd (cob_field *f)
{
	time_t	t;
	char	s[12];

	t = time (NULL);
	strftime (s, 8, "%Y%j", localtime (&t));
	cob_memcpy (f, (ucharptr)s, 7);
}

void
cob_accept_day_of_week (cob_field *f)
{
	time_t	t;
	char	s[4];

	t = time (NULL);
#if defined(_MSC_VER)
	sprintf(s, "%d", localtime(&t)->tm_wday + 1);
#else
	strftime (s, 2, "%u", localtime (&t));
#endif
	cob_memcpy (f, (ucharptr)s, 1);
}

void
cob_accept_time (cob_field *f)
{
#ifdef _WIN32
	SYSTEMTIME	syst;
#else
	time_t		t;
#if defined(HAVE_SYS_TIME_H) && defined(HAVE_GETTIMEOFDAY)
	struct timeval	tmv;
	char		buff2[8];
#endif
#endif
	char		s[12];

#ifdef _WIN32
	GetLocalTime (&syst);
	sprintf (s, "%2.2d%2.2d%2.2d%2.2d", syst.wHour, syst.wMinute,
		syst.wSecond, syst.wMilliseconds / 10);
#else
#if defined(HAVE_SYS_TIME_H) && defined(HAVE_GETTIMEOFDAY)
	gettimeofday (&tmv, NULL);
	t = tmv.tv_sec;
#else
	t = time (NULL);
#endif
	strftime (s, 9, "%H%M%S00", localtime (&t));
#if defined(HAVE_SYS_TIME_H) && defined(HAVE_GETTIMEOFDAY)
	sprintf(buff2, "%2.2ld", tmv.tv_usec / 10000);
	memcpy (&s[6], buff2, 2);
#endif
#endif
	cob_memcpy (f, (ucharptr)s, 8);
}

void
cob_display_command_line (cob_field *f)
{
	if (commlnptr) {
		free (commlnptr);
	}
	commlnptr = cob_malloc (f->size);
	commlncnt = f->size;
	memcpy (commlnptr, f->data, commlncnt);
}

void
cob_accept_command_line (cob_field *f)
{
	char	*buff;
	size_t	i;
	size_t	size;
	size_t	len;

	if (commlncnt) {
		cob_memcpy (f, commlnptr, (int)commlncnt);
		return;
	}
	buff = cob_malloc (COB_MEDIUM_BUFF);
	size = 0;
	for (i = 1; i < (size_t)cob_argc; ++i) {
		len = strlen (cob_argv[i]);
		if (size + len >= COB_MEDIUM_BUFF) {
			/* overflow */
			break;
		}
		memcpy (buff + size, cob_argv[i], len);
		size += len;
		buff[size++] = ' ';
	}
	cob_memcpy (f, (ucharptr)buff, (int)size);
	free (buff);
}

/*
 * Argument number
 */

void
cob_display_arg_number (cob_field *f)
{
	int		n;
	cob_field_attr	attr;
	cob_field	temp;

	temp.size = 4;
	temp.data = (unsigned char *)&n;
	temp.attr = &attr;
	COB_ATTR_INIT (COB_TYPE_NUMERIC_BINARY, 9, 0, 0, NULL);
	cob_move (f, &temp);
	if (n < 0 || n >= cob_argc) {
		cob_set_exception (COB_EC_IMP_DISPLAY);
		return;
	}
	current_arg = n;
}

void
cob_accept_arg_number (cob_field *f)
{
	int		n = cob_argc - 1;
	cob_field_attr	attr;
	cob_field	temp;

	temp.size = 4;
	temp.data = (unsigned char *)&n;
	temp.attr = &attr;
	COB_ATTR_INIT (COB_TYPE_NUMERIC_BINARY, 9, 0, 0, NULL);
	cob_move (&temp, f);
}

void
cob_accept_arg_value (cob_field *f)
{
	if (current_arg >= cob_argc) {
		cob_set_exception (COB_EC_IMP_ACCEPT);
		return;
	}
	cob_memcpy (f, (ucharptr)cob_argv[current_arg], (int) strlen (cob_argv[current_arg]));
	current_arg++;
}

/*
 * Environment variable
 */

void
cob_display_environment (cob_field *f)
{
	if (!cob_local_env) {
		cob_local_env = cob_malloc (COB_SMALL_BUFF);
	}
	if (f->size > COB_SMALL_MAX) {
		cob_set_exception (COB_EC_IMP_DISPLAY);
		return;
	}
	cob_field_to_string (f, cob_local_env);
}

void
cob_display_env_value (cob_field *f)
{
	char	*p;
	char	*env2;
	size_t	len;

	if (!cob_local_env) {
		cob_set_exception (COB_EC_IMP_DISPLAY);
		return;
	}
	if (!*cob_local_env) {
		cob_set_exception (COB_EC_IMP_DISPLAY);
		return;
	}
	env2 = cob_malloc (f->size + 1);
	cob_field_to_string (f, env2);
	len = strlen (cob_local_env) + strlen (env2) + 3;
	p = cob_malloc (len);
	sprintf (p, "%s=%s", cob_local_env, env2);
	if (putenv (p) != 0) {
		cob_set_exception (COB_EC_IMP_DISPLAY);
	}
	free (env2);
}

void
cob_set_environment (cob_field *f1, cob_field *f2)
{
	cob_display_environment (f1);
	cob_display_env_value (f2);
}

void
cob_get_environment (cob_field *envname, cob_field *envval)
{
	const char	*p;
	char		*buff;

	if (envname->size < COB_SMALL_BUFF) {
		buff = cob_malloc (COB_SMALL_BUFF);
		cob_field_to_string (envname, buff);
		p = getenv (buff);
		if (!p) {
			cob_set_exception (COB_EC_IMP_ACCEPT);
			p = " ";
		}
		cob_memcpy (envval, (ucharptr)p, (int) strlen (p));
		free (buff);
	} else {
		cob_set_exception (COB_EC_IMP_ACCEPT);
		p = " ";
		cob_memcpy (envval, (ucharptr)p, (int) strlen (p));
	}
}

void
cob_accept_environment (cob_field *f)
{
	const char *p = NULL;

	if (cob_local_env) {
		p = getenv (cob_local_env);
	}
	if (!p) {
		cob_set_exception (COB_EC_IMP_ACCEPT);
		p = " ";
	}
	cob_memcpy (f, (ucharptr)p, (int) strlen (p));
}

void
cob_chain_setup (void *data, const size_t parm, const size_t size)
{
	size_t	len;

	memset (data, ' ', size);
	if (parm <= (size_t)cob_argc - 1) {
		len = strlen (cob_argv[parm]);
		if (len <= size) {
			memcpy (data, cob_argv[parm], len);
		} else {
			memcpy (data, cob_argv[parm], size);
		}
	} else {
		memset (data, ' ', size);
	}
	cob_call_params = cob_argc - 1;
}

void
cob_allocate (unsigned char **dataptr, cob_field *retptr, cob_field *sizefld)
{
	void			*mptr = NULL;
	struct cob_alloc_cache	*cache_ptr;
	int			fsize;

	cob_exception_code = 0;
	fsize = cob_get_int (sizefld);
	if (fsize > 0) {
		cache_ptr = cob_malloc (sizeof (struct cob_alloc_cache));
		mptr = malloc ((size_t)fsize);
		if (!mptr) {
			cob_set_exception (COB_EC_STORAGE_NOT_AVAIL);
			free (cache_ptr);
		} else {
			memset (mptr, 0, (size_t)fsize);
			cache_ptr->cob_pointer = mptr;
			cache_ptr->size = (size_t)fsize;
			cache_ptr->next = cob_alloc_base;
			cob_alloc_base = cache_ptr;
		}
	}
	if (dataptr) {
		*dataptr = (unsigned char *)mptr;
	}
	if (retptr) {
		*(void **)(retptr->data) = mptr;
	}
}

void
cob_free_alloc (unsigned char **ptr1, unsigned char *ptr2)
{
	struct cob_alloc_cache	*cache_ptr;

	cob_exception_code = 0;
	if (ptr1 && *ptr1) {
		for (cache_ptr = cob_alloc_base; cache_ptr; cache_ptr = cache_ptr->next) {
			if (*(void **)ptr1 == cache_ptr->cob_pointer) {
				cache_ptr->cob_pointer = NULL;
				free (*ptr1);
				*ptr1 = NULL;
				return;
			}
		}
		cob_set_exception (COB_EC_STORAGE_NOT_ALLOC);
		return;
	}
	if (ptr2 && *(void **)ptr2) {
		for (cache_ptr = cob_alloc_base; cache_ptr; cache_ptr = cache_ptr->next) {
			if (*(void **)ptr2 == cache_ptr->cob_pointer) {
				cache_ptr->cob_pointer = NULL;
				free (*(void **)ptr2);
				*(void **)ptr2 = NULL;
				return;
			}
		}
		cob_set_exception (COB_EC_STORAGE_NOT_ALLOC);
		return;
	}
}

char *
cobgetenv (const char *name)
{
	if (name) {
		return getenv (name);
	}
	return NULL;
}

int
cobputenv (char *name)
{
	if (name) {
		return putenv (name);
	}
	return -1;
}

int
cobinit (void)
{
	cob_init (0, NULL);
	return 0;
}

void *
cobcommandline (int flags, int *pargc, char ***pargv, char ***penvp, char **pname)
{
	char		**spenvp;
	char		*spname;
	int		sflags;

	if (!cob_initialized) {
		cob_runtime_error ("'cobcommandline' - Runtime has not been initialized");
		cob_stop_run (1);
	}
	if (pargc && pargv) {
		cob_argc = *pargc;
		cob_argv = *pargv;
	}
	/* Shut up the compiler */
	sflags = flags;
	if (penvp) {
		spenvp = *penvp;
	}
	if (pname) {
		spname = *pname;
	}
	/* What are we supposed to return here? */
	return NULL;
}

void
cobexit (const int status)
{
	cob_stop_run (status);
}

int
cobtidy (void)
{
	struct exit_handlerlist	*h;

	if (exit_hdlrs != NULL) {
		h = exit_hdlrs;
		while (h != NULL) {
			h->proc ();
			h = h->next;
		}
	}
	cob_screen_terminate ();
	cob_exit_fileio ();
	return 0;
}

/* System routines */

int
CBL_EXIT_PROC (unsigned char *x, unsigned char *pptr)
{
	struct exit_handlerlist *hp = NULL;
	struct exit_handlerlist *h = exit_hdlrs;
	int			(**p)(void) = NULL;

	COB_CHK_PARMS (CBL_EXIT_PROC, 2);

	memcpy (&p, &pptr, sizeof (void *));
	if (!p || !*p) {
		return -1;
	}
	/* remove handler anyway */
	while (h != NULL) {
		if (h->proc == *p) {
			if (hp != NULL) {
				hp->next = h->next;
			} else {
				exit_hdlrs = h->next;
			}
			if (hp) {
				free (hp);
			}
			break;
		}
		hp = h;
		h = h->next;
	}
	if   (*x != 0 && *x != 2 && *x != 3) {	/* remove handler */
		return 0;
	}
	h = cob_malloc (sizeof(struct exit_handlerlist));
	h->next = exit_hdlrs;
	h->proc = *p;
	exit_hdlrs = h;
	return 0;
}

int
CBL_ERROR_PROC (unsigned char *x, unsigned char *pptr)
{
	struct handlerlist	*hp = NULL;
	struct handlerlist	*h = hdlrs;
	int			(**p)(char *s) = NULL;

	COB_CHK_PARMS (CBL_ERROR_PROC, 2);

	memcpy (&p, &pptr, sizeof (void *));
	if (!p || !*p) {
		return -1;
	}
	/* remove handler anyway */
	while (h != NULL) {
		if (h->proc == *p) {
			if (hp != NULL) {
				hp->next = h->next;
			} else {
				hdlrs = h->next;
			}
			if (hp) {
				free (hp);
			}
			break;
		}
		hp = h;
		h = h->next;
	}
	if (*x != 0) {	/* remove handler */
		return 0;
	}
	h = cob_malloc (sizeof(struct handlerlist));
	h->next = hdlrs;
	h->proc = *p;
	hdlrs = h;
	return 0;
}

int
SYSTEM (const unsigned char *cmd)
{
	char	*buff;
	int	i;

	COB_CHK_PARMS (SYSTEM, 1);

	if (cob_current_module->cob_procedure_parameters[0]) {
		i = (int)cob_current_module->cob_procedure_parameters[0]->size;
		if (i > COB_MEDIUM_MAX) {
			cob_runtime_error ("Parameter to SYSTEM call is larger than 8192 characters");
			cob_stop_run (1);
		}
		i--;
		for (; i >= 0; i--) {
			if (cmd[i] != ' ' && cmd[i] != 0) {
				break;
			}
		}
		if (i >= 0) {
			buff = cob_malloc ((size_t)(i + 2));
			memcpy (buff, cmd, (size_t)(i + 1));
			if (cob_screen_initialized) {
				cob_screen_set_mode (0);
			}
			i = system (buff);
			free (buff);
			if (cob_screen_initialized) {
				cob_screen_set_mode (1);
			}
			return i;
		}
	}
	return 1;
}

int
CBL_AND (unsigned char *data_1, unsigned char *data_2, const int length)
{
	size_t	n;

	COB_CHK_PARMS (CBL_AND, 3);

	if (length <= 0) {
		return 0;
	}
	for (n = 0; n < (size_t)length; ++n) {
		data_2[n] &= data_1[n];
	}
	return 0;
}

int
CBL_OR (unsigned char *data_1, unsigned char *data_2, const int length)
{
	size_t	n;

	COB_CHK_PARMS (CBL_OR, 3);

	if (length <= 0) {
		return 0;
	}
	for (n = 0; n < (size_t)length; ++n) {
		data_2[n] |= data_1[n];
	}
	return 0;
}

int
CBL_NOR (unsigned char *data_1, unsigned char *data_2, const int length)
{
	size_t	n;

	COB_CHK_PARMS (CBL_NOR, 3);

	if (length <= 0) {
		return 0;
	}
	for (n = 0; n < (size_t)length; ++n) {
		data_2[n] = ~(data_1[n] | data_2[n]);
	}
	return 0;
}

int
CBL_XOR (unsigned char *data_1, unsigned char *data_2, const int length)
{
	size_t	n;

	COB_CHK_PARMS (CBL_XOR, 3);

	if (length <= 0) {
		return 0;
	}
	for (n = 0; n < (size_t)length; ++n) {
		data_2[n] ^= data_1[n];
	}
	return 0;
}

int
CBL_IMP (unsigned char *data_1, unsigned char *data_2, const int length)
{
	size_t	n;

	COB_CHK_PARMS (CBL_IMP, 3);

	if (length <= 0) {
		return 0;
	}
	for (n = 0; n < (size_t)length; ++n) {
		data_2[n] = (~data_1[n]) | data_2[n];
	}
	return 0;
}

int
CBL_NIMP (unsigned char *data_1, unsigned char *data_2, const int length)
{
	size_t	n;

	COB_CHK_PARMS (CBL_NIMP, 3);

	if (length <= 0) {
		return 0;
	}
	for (n = 0; n < (size_t)length; ++n) {
		data_2[n] = data_1[n] & (~data_2[n]);
	}
	return 0;
}

int
CBL_EQ (unsigned char *data_1, unsigned char *data_2, const int length)
{
	size_t	n;

	COB_CHK_PARMS (CBL_EQ, 3);

	if (length <= 0) {
		return 0;
	}
	for (n = 0; n < (size_t)length; ++n) {
		data_2[n] = ~(data_1[n] ^ data_2[n]);
	}
	return 0;
}

int
CBL_NOT (unsigned char *data_1, const int length)
{
	size_t	n;

	COB_CHK_PARMS (CBL_NOT, 2);

	if (length <= 0) {
		return 0;
	}
	for (n = 0; n < (size_t)length; ++n) {
		data_1[n] = ~data_1[n];
	}
	return 0;
}

int
CBL_XF4 (unsigned char *data_1, unsigned char *data_2)
{
	size_t	n;

	COB_CHK_PARMS (CBL_XF4, 2);

	*data_1 = 0;
	for (n = 0; n < 8; ++n) {
		*data_1 |= (data_2[n] & 1) << (7 - n);
	}
	return 0;
}

int
CBL_XF5 (unsigned char *data_1, unsigned char *data_2)
{
	size_t	n;

	COB_CHK_PARMS (CBL_XF5, 2);

	for (n = 0; n < 8; ++n) {
		data_2[n] = (*data_1 & (1 << (7 - n))) ? 1 : 0;
	}
	return 0;
}

int
CBL_X91 (unsigned char *result, const unsigned char *func, unsigned char *parm)
{
	unsigned char	*p;
	size_t		i;

	switch (*func) {
	case 11:
		/* Set switches */
		p = parm;
		for (i = 0; i < 8; ++i, ++p) {
			if (*p == 0) {
				cob_switch[i] = 0;
			} else if (*p == 1) {
				cob_switch[i] = 1;
			}
		}
		*result = 0;
		break;
	case 12:
		/* Get switches */
		p = parm;
		for (i = 0; i < 8; ++i, ++p) {
			*p = cob_switch[i];
		}
		*result = 0;
		break;
	case 16:
		/* Return number of call parameters */
		*parm = cob_save_call_params;
		*result = 0;
		break;
	default:
		*result = 1;
		break;
	}
	return 0;
}

int
CBL_TOUPPER (unsigned char *data, const int length)
{
	size_t	n;

	COB_CHK_PARMS (CBL_TOUPPER, 2);

	if (length > 0) {
		for (n = 0; n < (size_t)length; ++n) {
			if (islower (data[n])) {
				data[n] = toupper (data[n]);
			}
		}
	}
	return 0;
}

int
CBL_TOLOWER (unsigned char *data, const int length)
{
	size_t	n;

	COB_CHK_PARMS (CBL_TOLOWER, 2);

	if (length > 0) {
		for (n = 0; n < (size_t)length; ++n) {
			if (isupper (data[n])) {
				data[n] = tolower (data[n]);
			}
		}
	}
	return 0;
}

int
CBL_OC_NANOSLEEP (unsigned char *data)
{
	long long	nsecs;
#ifdef	_WIN32
#if 0
	struct timeval	tv;
#else
	unsigned int	msecs;
#endif
#else
	struct timespec	tsec;
#endif

	COB_CHK_PARMS (CBL_OC_NANOSLEEP, 1);

	if (cob_current_module->cob_procedure_parameters[0]) {
		nsecs = cob_get_long_long (cob_current_module->cob_procedure_parameters[0]);
		if (nsecs > 0) {
#ifdef	_WIN32
#if 0
			nsecs /= 1000;
			if (nsecs > 0) {
				tv.tv_sec = (long)(nsecs / 1000000);
				tv.tv_usec = (long)(nsecs % 1000000);
				select (0, (void *)0, (void *)0, (void *)0, &tv);
			}
#else
			msecs = (unsigned int)(nsecs / 1000000);
			if (msecs > 0) {
				Sleep (msecs);
			}
#endif
#else
			tsec.tv_sec = nsecs / 1000000000;
			tsec.tv_nsec = nsecs % 1000000000;
			nanosleep (&tsec, NULL);
#endif
		}
	}
	return 0;
}

int
cob_return_args (unsigned char *data)
{
	COB_CHK_PARMS (C$NARG, 1);

	if (cob_current_module->cob_procedure_parameters[0]) {
		cob_set_int (cob_current_module->cob_procedure_parameters[0], cob_save_call_params);
	}
	return 0;
}

int
cob_parameter_size (unsigned char *data)
{
	int	n;

	COB_CHK_PARMS (C$PARAMSIZE, 1);

	if (cob_current_module->cob_procedure_parameters[0]) {
		n = cob_get_int (cob_current_module->cob_procedure_parameters[0]);
		if (n > 0 && n <= cob_save_call_params) {
			n--;
			if (cob_current_module->next &&
			    cob_current_module->next->cob_procedure_parameters[n]) {
				return cob_current_module->next->cob_procedure_parameters[n]->size;
			}
		}
	}
	return 0;
}

int
cob_acuw_sleep (unsigned char *data)
{
	int	n;

	COB_CHK_PARMS (C$SLEEP, 1);

	if (cob_current_module->cob_procedure_parameters[0]) {
		n = cob_get_int (cob_current_module->cob_procedure_parameters[0]);
		if (n > 0 && n < 3600*24*7) {
#ifdef	_WIN32
			Sleep (n*1000);
#else
			sleep ((unsigned int)n);
#endif
		}
	}
	return 0;
}

int
cob_acuw_justify (unsigned char *data, ...)
{
	unsigned char	*direction;
	size_t		datalen;
	int		n;
	int		shifting = 0;
	size_t		left = 0;
	size_t		right = 0;
	size_t		movelen;
	size_t		centrelen;
	va_list		args;

	COB_CHK_PARMS (C$JUSTIFY, 1);

	datalen = cob_current_module->cob_procedure_parameters[0]->size;
	if (datalen < 2) {
		return 0;
	}
	if (data[0] != ' ' && data[datalen - 1] != ' ') {
		return 0;
	}
	for (n = 0; n < (int)datalen; ++n, ++left) {
		if (data[n] != ' ') {
			break;
		}
	}
	if (n == (int)datalen) {
		return 0;
	}
	left = n;
	for (n = (int)datalen - 1; n >= 0; --n, ++right) {
		if (data[n] != ' ') {
			break;
		}
	}
	movelen = datalen - left - right;
	if (cob_call_params > 1) {
		va_start (args, data);
		direction = va_arg (args, unsigned char *);
		va_end (args);
		if (*direction == 'L') {
			shifting = 1;
		} else if (*direction == 'C') {
			shifting = 2;
		}
	}
	switch (shifting) {
	case 1:
		memmove (data, &data[left], movelen);
		memset (&data[movelen], ' ', datalen - movelen);
		break;
	case 2:
		centrelen = (left + right) / 2;
		memmove (&data[centrelen], &data[left], movelen);
		memset (data, ' ', centrelen);
		if ((left + right) % 2) {
			memset (&data[centrelen + movelen], ' ', centrelen + 1);
		} else {
			memset (&data[centrelen + movelen], ' ', centrelen);
		}
		break;
	default:
		memmove (&data[left + right], &data[left], movelen);
		memset (data, ' ', datalen - movelen);
		break;
	}
	return 0;
}
