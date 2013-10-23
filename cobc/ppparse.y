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

%expect 0

%defines
%name-prefix="pp"

%{
#include "config.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cobc.h"

#define YYDEBUG		1
#define YYERROR_VERBOSE	1
#define pperror cb_error

static char *fix_filename (char *name);
static char *fold_lower (char *name);
static char *fold_upper (char *name);

static struct cb_replace_list *cb_replace_list_add (struct cb_replace_list *replace_list, struct cb_text_list *old_text, struct cb_text_list *new_text);
%}

%union {
	char			*s;
	struct cb_text_list	*l;
	struct cb_replace_list	*r;
}

%token TOKEN_EOF 0 "end of file"
%token COPY REPLACE SUPPRESS PRINTING REPLACING OFF IN OF BY EQEQ
%token <s> TOKEN
%type <s> copy_in
%type <l> text pseudo_text token_list identifier subscripts
%type <r> copy_replacing replacing_list

%%

statement_list: | statement_list statement ;
statement: copy_statement | replace_statement ;

copy_statement:
  COPY TOKEN copy_in copy_suppress copy_replacing '.'
  {
	fputc ('\n', ppout);
	$2 = fix_filename ($2);
	if (cb_flag_fold_copy_lower) {
		$2 = fold_lower ($2);
	} else if (cb_flag_fold_copy_upper) {
		$2 = fold_upper ($2);
	}
	if ($3) {
		$3 = fix_filename ($3);
		if (cb_flag_fold_copy_lower) {
			$3 = fold_lower ($3);
		} else if (cb_flag_fold_copy_upper) {
			$3 = fold_upper ($3);
		}
	}
	ppcopy ($2, $3, $5);
  }
;

copy_in:
  /* nothing */			{ $$ = NULL; }
| IN TOKEN			{ $$ = $2; }
| OF TOKEN			{ $$ = $2; }
;

copy_suppress:
| SUPPRESS _printing
;

copy_replacing:
  /* nothing */			{ $$ = NULL; }
| REPLACING replacing_list	{ $$ = $2; }
;

replace_statement:
  REPLACE replacing_list '.'	{ pp_set_replace_list ($2); }
| REPLACE OFF '.'		{ pp_set_replace_list (NULL); }
;

replacing_list:
  text BY text			{ $$ = cb_replace_list_add (NULL, $1, $3); }
| replacing_list text BY text	{ $$ = cb_replace_list_add ($1, $2, $4); }
;

text:
  pseudo_text			{ $$ = $1; }
| identifier			{ $$ = $1; }
;

pseudo_text:
  EQEQ EQEQ			{ $$ = NULL; }
| EQEQ token_list EQEQ		{ $$ = $2; }
;

token_list:
  TOKEN				{ $$ = cb_text_list_add (NULL, $1); }
| token_list TOKEN		{ $$ = cb_text_list_add ($1, $2); }
;

identifier:
  TOKEN				{ $$ = cb_text_list_add (NULL, $1); }
| identifier IN TOKEN
  {
	$$ = cb_text_list_add ($1, " ");
	$$ = cb_text_list_add ($$, "IN");
	$$ = cb_text_list_add ($$, " ");
	$$ = cb_text_list_add ($$, $3);
  }
| identifier OF TOKEN
  {
	$$ = cb_text_list_add ($1, " ");
	$$ = cb_text_list_add ($$, "OF");
	$$ = cb_text_list_add ($$, " ");
	$$ = cb_text_list_add ($$, $3);
  }
| identifier '(' subscripts ')'
  {
	struct cb_text_list *l;

	$$ = cb_text_list_add ($1, " ");
	$$ = cb_text_list_add ($$, "(");
	$3 = cb_text_list_add ($3, ")");
	for (l = $$; l->next; l = l->next);
	l->next = $3;
  }
;

subscripts:
  TOKEN				{ $$ = cb_text_list_add (NULL, $1); }
| subscripts TOKEN
  {
	$$ = cb_text_list_add ($1, " ");
	$$ = cb_text_list_add ($$, $2);
  }
;

_printing: | PRINTING ;

%%
static char *
fix_filename (char *name)
{
	/* remove quotation from alphanumeric literals */
	if (name[0] == '\'' || name[0] == '\"') {
		name++;
		name[strlen (name) - 1] = 0;
	}
	return name;
}

static char *
fold_lower (char *name)
{
	unsigned char	*p;

	for (p = (unsigned char *)name; *p; p++) {
		if (isupper (*p)) {
			*p = tolower (*p);
		}
	}
	return name;
}

static char *
fold_upper (char *name)
{
	unsigned char	*p;

	for (p = (unsigned char *)name; *p; p++) {
		if (islower (*p)) {
			*p = toupper (*p);
		}
	}
	return name;
}

static struct cb_replace_list *
cb_replace_list_add (struct cb_replace_list *list,
		     struct cb_text_list *old_text,
		     struct cb_text_list *new_text)
{
	struct cb_replace_list *p;
	struct cb_replace_list *l;

	p = cobc_malloc (sizeof (struct cb_replace_list));
	p->old_text = old_text;
	p->new_text = new_text;
	p->next = NULL;
	if (!list) {
		return p;
	} else {
		for (l = list; l->next; l = l->next) ;
		l->next = p;
		return list;
	}
}
