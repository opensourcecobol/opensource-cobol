/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKEN_EOF = 0,
     COPY = 258,
     REPLACE = 259,
     SUPPRESS = 260,
     PRINTING = 261,
     REPLACING = 262,
     OFF = 263,
     IN = 264,
     OF = 265,
     BY = 266,
     EQEQ = 267,
     TOKEN = 268
   };
#endif
#define TOKEN_EOF 0
#define COPY 258
#define REPLACE 259
#define SUPPRESS 260
#define PRINTING 261
#define REPLACING 262
#define OFF 263
#define IN 264
#define OF 265
#define BY 266
#define EQEQ 267
#define TOKEN 268




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 48 "ppparse.y"
typedef union YYSTYPE {
	char			*s;
	struct cb_text_list	*l;
	struct cb_replace_list	*r;
} YYSTYPE;
/* Line 1249 of yacc.c.  */
#line 70 "ppparse.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE pplval;



