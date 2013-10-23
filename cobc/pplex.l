/*							-*- c -*-
 * Copyright (C) 2001-2009 Keisuke Nishida
 * Copyright (C) 2007-2009 Roger While
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, 51 Franklin Street, Fifth Floor
 * Boston, MA 02110-1301 USA
 */

%option 8bit
%option caseless
%option noyywrap
%option never-interactive
%option prefix="pp"

%{

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef	HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "cobc.h"
#include "ppparse.h"

static char	*plexbuff1 = NULL;
static char	*plexbuff2 = NULL;
static size_t	newline_count = 0;
static size_t	within_comment = 0;
static size_t	inside_bracket = 0;
static size_t	consecutive_quotation = 0;
static int	quotation_mark = 0;
static int	last_line_1 = -1;
static int	last_line_2 = -1;

static struct cb_replace_list	*current_replace_list = NULL;

static struct cb_text_list	*text_queue = NULL;

static struct copy_info {
	struct copy_info	*next;
	char			*file;
	int			line;
	int			replacing;
	int			quotation_mark;
	YY_BUFFER_STATE		buffer;
} *copy_stack = NULL;

#define YY_INPUT(buf,result,max_size) result = ppinput (buf, max_size);

static int ppinput (char *buf, int max_size);
static void ppecho (const char *text);

static void switch_to_buffer (const int lineno, const char *filename,
			      YY_BUFFER_STATE buffer);

%}

WORD		[_0-9A-Z-]+
NUMRIC_LITERAL	[+-]?[0-9,.]*[0-9]
ALNUM_LITERAL	\"[^\"\n]*\"|\'[^\'\n]*\'

%x PROCESS_STATE COPY_STATE PSEUDO_STATE

%%

%{
%}

<*>"*>".* {
	ppecho (" ");
}

<*>^"*".* |
<*>^"/".* {
	ppecho (" ");
	if (cb_source_format != CB_FORMAT_FIXED) {
		ppecho (yytext);
	}
}

"PROCESS"		{ BEGIN PROCESS_STATE; }

<PROCESS_STATE>{
  \n			{ BEGIN INITIAL; unput ('\n'); }
  .*			{ cb_warning (_("PROCESS statement is ignored")); }
}

"COPY"			{ BEGIN COPY_STATE; return COPY; }
"INCLUDE"		{ BEGIN COPY_STATE; return COPY; }
"REPLACE"		{ BEGIN COPY_STATE; return REPLACE; }

<COPY_STATE>{
  [,;]?\n		{ ECHO; cb_source_line++; }
  [,;]?[ ]+		{ /* ignore */ }
  "."			{ BEGIN INITIAL; return '.'; }
  "=="			{ BEGIN PSEUDO_STATE; return EQEQ; }
  "("			{ return '('; }
  ")"			{ return ')'; }
  "BY"			{ return BY; }
  "IN"			{ return IN; }
  "OF"			{ return OF; }
  "OFF"			{ return OFF; }
  "SUPPRESS"		{ return SUPPRESS; }
  "PRINTING"		{ return PRINTING; }
  "REPLACING"		{ return REPLACING; }
  {WORD} |
  {NUMRIC_LITERAL} |
  {ALNUM_LITERAL} |
  .			{ pplval.s = strdup (yytext); return TOKEN; }
}

<PSEUDO_STATE>{
  [,;]?\n		{ ECHO; cb_source_line++; }
  [,;]?[ ]+		{ pplval.s = strdup (" "); return TOKEN; }
  "=="			{ BEGIN COPY_STATE; return EQEQ; }
  {WORD} |
  {NUMRIC_LITERAL} |
  {ALNUM_LITERAL} |
  .			{ pplval.s = strdup (yytext); return TOKEN; }
}

"AUTHOR" |
"DATE-WRITTEN" |
"DATE-MODIFIED" |
"DATE-COMPILED" |
"INSTALLATION" |
"REMARKS" |
"SECURITY" {
	/* these words are treated as comments */
	if (cb_verify (cb_author_paragraph, yytext)) {
		/* skip comments until the end of line */
		int c;

		within_comment = 1;
		while ((c = input ()) != EOF) {
			if (c == '\n') {
				break;
			}
		}
		unput (c);
	}
}

"EJECT"\.? |
"SKIP1"\.? |
"SKIP2"\.? |
"SKIP3"\.? {
	/* these words are comments in IBM COBOL */
	if (cb_verify (cb_eject_statement, yytext)) {
		/* do nothing for now */
	} else {
		ECHO;
	}
}

[,;]?\n			{ ppecho ("\n"); cb_source_line++; }

[;]?[ ]+		{ ppecho (" "); }

[,]?[ ]+ {
	if (inside_bracket) {
		ppecho (", ");
	} else {
		ppecho (" ");
	}
}

"(" {
	inside_bracket++;
	ppecho ("(");
}

")" {
	if (inside_bracket) {
		inside_bracket--;
	}
	ppecho (")");
}

{WORD} |
{NUMRIC_LITERAL} |
{ALNUM_LITERAL} |
.			{ ppecho (yytext); }

<<EOF>> {
	struct copy_info *p;

	p = copy_stack;

	yy_delete_buffer (YY_CURRENT_BUFFER);

	/* Terminate at the end of all input */
	if (p->next == NULL) {
		within_comment = 0;
		newline_count = 0;
		inside_bracket = 0;
		current_replace_list = NULL;
		text_queue = NULL;
		copy_stack = NULL;
		quotation_mark = 0;
		consecutive_quotation = 0;
		last_line_1 = -1;
		last_line_2 = -1;
		yyterminate ();
	}

	/* Close the current file */
	fclose (ppin);

	/* Switch to the last buffer */
	if (p->replacing) {
		pp_set_replace_list (NULL);
	}
	switch_to_buffer (p->line, p->file, p->buffer);
	quotation_mark = p->quotation_mark;

	copy_stack = p->next;
	free (p);
}

%%

void
pp_set_replace_list (struct cb_replace_list *list)
{
	current_replace_list = list;
}

static void
switch_to_buffer (const int line, const char *file, YY_BUFFER_STATE buffer)
{
	char	*p;

	cb_source_line = line;
	cb_source_file = strdup (file);
	for (p = cb_source_file; *p; p++) {
		if (*p == '\\') {
			*p = '/';
		}
	}
	yy_switch_to_buffer (buffer);
	fprintf (yyout, "# %d \"%s\"\n", line, cb_source_file);
}

int
ppopen (const char *name, struct cb_replace_list *replace_list)
{
	struct copy_info *p;

	for (; newline_count > 0; newline_count--) {
		ungetc ('\n', ppin);
	}

	/* Open the copy file */
	ppin = fopen (name, "rb");
	if (!ppin) {
		if (cb_source_file) {
			cb_error (_("%s: %s"), name, strerror (errno));
		} else {
			perror (name);
		}
		return -1;
	}

	/* Add to dependency list */
	if (cb_depend_file) {
		cb_depend_list = cb_text_list_add (cb_depend_list, name);
	}

	/* Preserve the current buffer */
	p = cobc_malloc (sizeof (struct copy_info));
	p->line = cb_source_line;
	p->file = cb_source_file;
	p->replacing = replace_list ? 1 : 0;
	p->buffer = YY_CURRENT_BUFFER;
	p->quotation_mark = quotation_mark;
	p->next = copy_stack;
	copy_stack = p;

	/* Switch to new buffer */
	if (replace_list) {
		pp_set_replace_list (replace_list);
	}
	switch_to_buffer (1, name, yy_create_buffer (ppin, YY_BUF_SIZE));
	return 0;
}

int
ppcopy (const char *name, const char *lib, struct cb_replace_list *replace_list)
{
	struct cb_text_list	*il;
	struct cb_text_list	*el;
	char			*s;
	struct stat		st;

	if (lib) {
		if (!plexbuff1) {
			plexbuff1 = cobc_malloc (COB_SMALL_BUFF);
		}
		snprintf (plexbuff1, COB_SMALL_MAX, "%s/%s", lib, name);
		s = plexbuff1;
	} else {
		s = (char *)name;
	}

	/* Find the file */
	if (stat (s, &st) == 0) {
		return ppopen (s, replace_list);
	}
	if (!plexbuff2) {
		plexbuff2 = cobc_malloc (COB_SMALL_BUFF);
	}
	for (el = cb_extension_list; el; el = el->next) {
		snprintf (plexbuff2, COB_SMALL_MAX, "%s%s", s, el->text);
		if (stat (plexbuff2, &st) == 0) {
			return ppopen (plexbuff2, replace_list);
		}
	}
	if (*s != '/') {
		for (il = cb_include_list; il; il = il->next) {
			for (el = cb_extension_list; el; el = el->next) {
				snprintf (plexbuff2, COB_SMALL_MAX, "%s/%s%s",
					  il->text, name, el->text);
				if (stat (plexbuff2, &st) == 0) {
					return ppopen (plexbuff2, replace_list);
				}
			}
		}
	}
	cb_error (_("%s: %s"), name, strerror (errno));
	return -1;
}

/* Check directives */
/* This is horrible but we have to parse directives directly after the read */
/* as flex buffers up input and it is then too late to use the flex parser */

static void
check_directive (char *buff, int *line_size)
{
	char	*s;
	char	*dirptr;
	size_t	cnt;
	int	n;
	char	sbuff[5][256];

	if (cb_source_format == CB_FORMAT_FIXED) {
		if (*line_size < 8) {
			return;
		}
		if (buff[6] != ' ') {
			return;
		}
		s = &buff[7];
	} else {
		s = buff;
	}
	for (; *s == ' '; s++) {
		;
	}
	dirptr = s;
	if (*s != '>') {
		return;
	}
	s++;
	if (*s != '>') {
		return;
	}
	s++;
	if (*s == 'D') {
		if (cb_flag_debugging_line) {
			memset (dirptr, ' ', 3);
		} else {
			for (cnt = 0; cnt < newline_count; cnt++) {
				buff[cnt] = '\n';
			}
			buff[cnt] = 0;
			strcat (buff, "      *> DEBUG\n");
			*line_size = strlen (buff);
			newline_count = 0;
		}
		return;
	}
	memset (sbuff[0], 0, sizeof (sbuff));
	n = sscanf (s, "%255s %255s %255s %255s %255s",
			sbuff[0], sbuff[1], sbuff[2], sbuff[3], sbuff[4]);
	for (cnt = 0; cnt < newline_count; cnt++) {
		buff[cnt] = '\n';
	}
	buff[cnt] = 0;
	newline_count = 0;
	strcat (buff, "      *> DIRECTIVE\n");
	*line_size = strlen (buff);
	if (n < 2 || strcasecmp (sbuff[0], "SOURCE")) {
		cb_warning (_("Invalid directive - ignored"));
		return;
	}
	switch (n) {
	case 2:
		if (!strcasecmp (sbuff[1], "FIXED")) {
			cb_source_format = CB_FORMAT_FIXED;
			return;
		}
		if (!strcasecmp (sbuff[1], "FREE")) {
			cb_source_format = CB_FORMAT_FREE;
			return;
		}
		break;
	case 3:
		if (strcasecmp (sbuff[1], "FORMAT") &&
		    strcasecmp (sbuff[1], "IS")) {
			break;
		}
		if (!strcasecmp (sbuff[2], "FIXED")) {
			cb_source_format = CB_FORMAT_FIXED;
			return;
		}
		if (!strcasecmp (sbuff[2], "FREE")) {
			cb_source_format = CB_FORMAT_FREE;
			return;
		}
		break;
	default:
		if (strcasecmp (sbuff[1], "FORMAT")) {
			break;
		}
		if (strcasecmp (sbuff[2], "IS")) {
			break;
		}
		if (!strcasecmp (sbuff[3], "FIXED")) {
			cb_source_format = CB_FORMAT_FIXED;
			return;
		}
		if (!strcasecmp (sbuff[3], "FREE")) {
			cb_source_format = CB_FORMAT_FREE;
			return;
		}
		break;
	}
	cb_warning (_("Invalid directive - ignored"));
}

/*
 * Read line
 */

static int
ppinput (char *buff, int max_size)
{

	char	*bp;
	size_t	gotcr;
	size_t	continuation = 0;
	int	ipchar;
	int	i;
	int	n;
	int	coln;

start:
	/* read a line */
	gotcr = 0;
	ipchar = 0;
	for (n = 0; n < 256 && ipchar != '\n';) {
		ipchar = getc (ppin);
		if (ipchar == EOF) {
			if (newline_count == 0) {
				return 0;
			}
			memset (buff, '\n', newline_count);
			buff[newline_count] = 0;
			newline_count = 0;
			return strlen (buff);
		}
		if (n == 0 && cb_source_format != CB_FORMAT_FIXED) {
			if (ipchar != ' ' && ipchar != '\n') {
				buff[n++] = ' ';
			}
		}
		if (gotcr) {
			if (ipchar != '\n') {
				buff[n++] = '\r';
			}
			gotcr = 0;
		}
		if (ipchar == '\r') {
			gotcr = 1;
		} else if (ipchar == '\t') {
			buff[n++] = ' ';
			while (n % cb_tab_width != 0) {
				buff[n++] = ' ';
			}
		} else {
			buff[n++] = ipchar;
		}
	}

	if (buff[n - 1] != '\n') {
		cb_warning (_("Line not terminated by a newline"));
		buff[n++] = '\n';
	}
	buff[n] = 0;

	check_directive (buff, &n);

	/* nothing more to do with free format */
	if (cb_source_format != CB_FORMAT_FIXED) {
		return n;
	}

	/* line too short */
	if (n < 8) {
		newline_count++;
		goto start;
	}

	if (cb_flag_mfcomment) {
		if (buff[0] == '*' || buff[0] == '/') {
			newline_count++;
			goto start;
		}
	}
	/* check the indicator (column 7) */
	bp = buff + 7;
	switch (buff[6]) {
	case ' ':
		break;
	case '-':
		continuation = 1;
		break;
	case 'd':
	case 'D':
		/* debugging line */
		if (cb_flag_debugging_line) {
			break;
		}
		newline_count++;
		goto start;
	case '*':
	case '/':
		/* comment line */
		newline_count++;
		goto start;
	default:
		/* invalid indicator */
		cb_error (_("Invalid indicator '%c' at column 7"), buff[6]);
		return YY_NULL;
	}

	/* skip comments that follow after AUTHORS, etc. */
	if (within_comment) {
		/* Check all of "Area A" */
		switch (n) {
		case 8:
			if (buff[7] == ' ') {
				newline_count++;
				goto start;
			}
			break;
		case 9:
			if (!memcmp (&buff[7], "  ", 2)) {
				newline_count++;
				goto start;
			}
			break;
		case 10:
			if (!memcmp (&buff[7], "   ", 3)) {
				newline_count++;
				goto start;
			}
			break;
		default:
			if (!memcmp (&buff[7], "    ", 4)) {
				newline_count++;
				goto start;
			}
			break;
		}
		within_comment = 0;
	}

	/* check the text that is longer than cb_text_column */
	if (n > cb_text_column + 1) {

		/* show warning if it is not whitespaces */
		if (cb_warn_column_overflow && last_line_2 < cb_source_line - 1) {
			for (coln = cb_text_column; coln < n; coln++) {
				if (buff[coln] != ' ' && buff[coln] != '\n') {
					cb_warning (_("Source text after column %d"),
						    cb_text_column);
					break;
				}
			}
		}

		/* remove it */
		strcpy (buff + cb_text_column, "\n");
		last_line_2 = cb_source_line;
		n = cb_text_column + 1;
	}

	/* skip blank lines */
	for (i = 7; buff[i] == ' '; i++) ;
	if (buff[i] == '\n') {
		newline_count++;
		goto start;
	}

	if (continuation) {
		/* line continuation */
		for (; *bp == ' '; bp++) ;

		/* validate concatenation */
		if (consecutive_quotation) {
			if (bp[0] == quotation_mark && bp[1] == quotation_mark) {
				bp++;
			} else {
				cb_error (_("Invalid line continuation"));
				return YY_NULL;
			}
			quotation_mark = 0;
			consecutive_quotation = 0;
		} else if (quotation_mark) {
			/* literal concatenation */
			if (*bp == quotation_mark) {
				bp++;
			} else {
				cb_error (_("Invalid line continuation"));
				return YY_NULL;
			}
		}
	} else {
		/* normal line */
		quotation_mark = 0;
		consecutive_quotation = 0;
	}

	/* check if string literal is to be continued */
	for (i = bp - buff; buff[i] != '\n'; i++) {
		if (buff[i] == '\'' || buff[i] == '\"') {
			if (quotation_mark == 0) {
				/* literal start */
				quotation_mark = buff[i];
			} else if (quotation_mark == buff[i]) {
				if (i == cb_text_column - 1) {
					/* consecutive quotation */
					consecutive_quotation = 1;
				} else {
					/* literal end */
					quotation_mark = 0;
				}
			}
		}
	}

	/* truncate trailing spaces, including the newline */
	if (quotation_mark) {
		for (; i < 72;) {
			buff[i++] = ' ';
		}
		buff[i] = 0;
	} else {
		for (i--; buff[i] == ' '; i--) ;
		if (buff[i] == '\'' || buff[i] == '\"') {
			buff[++i] = ' ';
		}
		buff[i + 1] = 0;
	}

	if (continuation) {
		memmove (buff, bp, strlen (bp) + 1);
		newline_count++;
	} else {
		/* insert newlines at the start of the buffer */
		memmove (buff + newline_count, bp, strlen (bp) + 1);
		memset (buff, '\n', newline_count);
		newline_count = 1;
	}
	return strlen (buff);
}

static void
ppecho (const char *text)
{
	struct cb_replace_list	*r;
	struct cb_text_list	*l;
	struct cb_text_list	*queue;

	if (text_queue == NULL && (text[0] == ' ' || text[0] == '\n')) {
		fputs (text, ppout);
	} else if (!current_replace_list) {
		for (; text_queue; text_queue = text_queue->next) {
			fputs (text_queue->text, ppout);
		}
		fputs (text, ppout);
	} else {
		/* Do replacement */

		text_queue = cb_text_list_add (text_queue, text);

		for (r = current_replace_list; r; r = r->next) {
			queue = text_queue;
			for (l = r->old_text; l; l = l->next) {
				while (l && (l->text[0] == ' ' || l->text[0] == '\n')) {
					l = l->next;
				}
				if (l == NULL) {
					break;
				}
				while (queue && (queue->text[0] == ' ' ||
				       queue->text[0] == '\n')) {
					queue = queue->next;
				}
				if (queue == NULL) {
					return;	/* partial match */
				}
				if (strcasecmp (l->text, queue->text) != 0) {
					break;
				}
				queue = queue->next;
			}
			if (l == NULL) {
				/* match */
				for (l = r->new_text; l; l = l->next) {
					fputs (l->text, ppout);
				}
/*
				text_queue = queue ? queue->next : NULL;
*/
				text_queue = queue;
				continue;
			}
		}

		/* no match */
		for (; text_queue; text_queue = text_queue->next) {
			fputs (text_queue->text, ppout);
		}
	}
}
