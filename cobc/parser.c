/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 26 "parser.y"

#include "config.h"

#include <stdlib.h>
#include <string.h>

#include "cobc.h"
#include "tree.h"

#define yyerror			cb_error
#define YYDEBUG			1
#define YYERROR_VERBOSE		1

#define PENDING(x)		cb_warning (_("'%s' not implemented"), x)

#define emit_statement(x) \
  current_program->exec_list = cb_cons (x, current_program->exec_list)

#define push_expr(type, node) \
  current_expr = cb_build_list (cb_int (type), node, current_expr)

#define TERM_NONE		0
#define TERM_ACCEPT		1
#define TERM_ADD		2
#define TERM_CALL		3
#define TERM_COMPUTE		4
#define TERM_DELETE		5
#define TERM_DISPLAY		6
#define TERM_DIVIDE		7
#define TERM_EVALUATE		8
#define TERM_IF			9
#define TERM_MULTIPLY		10
#define TERM_PERFORM		11
#define TERM_READ		12
#define TERM_RECEIVE		13
#define TERM_RETURN		14
#define TERM_REWRITE		15
#define TERM_SEARCH		16
#define TERM_START		17
#define TERM_STRING		18
#define TERM_SUBTRACT		19
#define TERM_UNSTRING		20
#define TERM_WRITE		21
#define TERM_MAX		22

/* Global variables */

struct cb_program		*current_program = NULL;
struct cb_statement		*current_statement = NULL;
struct cb_label			*current_section = NULL;
struct cb_label			*current_paragraph = NULL;
size_t				functions_are_all = 0;
int				non_const_word = 0;

/* Local variables */

static struct cb_statement	*main_statement;

static cb_tree			current_expr;
static struct cb_field		*current_field;
static struct cb_field		*description_field;
static struct cb_file		*current_file;
static struct cb_key_component	*key_component_list;
static enum cb_storage		current_storage;

static size_t			check_unreached = 0;
static int			call_mode;
static int			size_mode;

static cb_tree			perform_stack = NULL;
static cb_tree			qualifier = NULL;

static cb_tree			fgc;
static cb_tree			bgc;
static cb_tree			scroll;
static cb_tree			save_tree_1;
static cb_tree			save_tree_2;
static cb_tree			dummy_tree;
static size_t			in_declaratives = 0;
static size_t			current_linage = 0;
static size_t			prog_end = 0;
static size_t			use_global_ind = 0;
static size_t			samearea = 1;
static size_t			organized_seen = 0;
static size_t			inspect_keyword = 0;
static int			next_label_id = 0;
static int			eval_level = 0;
static int			eval_inc = 0;
static int			eval_inc2 = 0;
static int			depth = 0;
static int			dispattrs = 0;
static struct cb_file		*linage_file;
static cb_tree			next_label_list = NULL;
static char			*stack_progid[32];
static int			term_array[TERM_MAX];
static int			eval_check[64][64];

/* Static functions */

static void
BEGIN_STATEMENT (const char *name, const size_t term)
{
	if (cb_warn_unreachable && check_unreached) {
		cb_warning (_("Unreachable statement '%s'"), (char *)name);
	}
	current_statement = cb_build_statement ((char *)name);
	CB_TREE (current_statement)->source_file = (unsigned char *)cb_source_file;
	CB_TREE (current_statement)->source_line = cb_source_line;
	emit_statement (CB_TREE (current_statement));
	if (term) {
		term_array[term]++;
	}
	main_statement = current_statement;
}

static void
BEGIN_IMPLICIT_STATEMENT (cb_tree node)
{
	current_statement = cb_build_statement (NULL);
	CB_TREE (current_statement)->source_file = CB_TREE (node)->source_file;
	CB_TREE (current_statement)->source_line = CB_TREE (node)->source_line;
	main_statement->body = cb_list_add (main_statement->body,
					    CB_TREE (current_statement));
}

static void
emit_entry (const char *name, const int encode, cb_tree using_list)
{
	cb_tree		l;
	cb_tree		label;
	cb_tree		x;
	struct cb_field	*f;
	int		parmnum;
	char		buff[256];

	sprintf (buff, "E$%s", name);
	label = cb_build_label (cb_build_reference (buff), NULL);
	if (encode) {
		CB_LABEL (label)->name = (unsigned char *)(cb_encode_program_id (name));
		CB_LABEL (label)->orig_name = (unsigned char *)name;
	} else {
		CB_LABEL (label)->name = (unsigned char *)name;
		CB_LABEL (label)->orig_name = (unsigned char *)current_program->orig_source_name;
	}
	CB_LABEL (label)->need_begin = 1;
	CB_LABEL (label)->is_entry = 1;
	emit_statement (label);

	parmnum = 1;
	for (l = using_list; l; l = CB_CHAIN (l)) {
		x = CB_VALUE (l);
		if (x != cb_error_node && cb_ref (x) != cb_error_node) {
			f = CB_FIELD (cb_ref (x));
			if (f->level != 01 && f->level != 77) {
				cb_error_x (x, _("'%s' not level 01 or 77"), cb_name (x));
			}
			if (!current_program->flag_chained) {
				if (f->storage != CB_STORAGE_LINKAGE) {
					cb_error_x (x, _("'%s' is not in LINKAGE SECTION"), cb_name (x));
				}
				if (f->flag_item_based || f->flag_external) {
					cb_error_x (x, _("'%s' can not be BASED/EXTERNAL"), cb_name (x));
				}
				f->flag_is_pdiv_parm = 1;
			} else {
				if (f->storage != CB_STORAGE_WORKING) {
					cb_error_x (x, _("'%s' is not in WORKING-STORAGE SECTION"), cb_name (x));
				}
				f->flag_chained = 1;
				f->param_num = parmnum;
				parmnum++;
			}
			if (f->redefines) {
				cb_error_x (x, _("'%s' REDEFINES field not allowed here"), cb_name (x));
			}
		}
	}

	/* Check dangling LINKAGE items */
	if (cb_warn_linkage) {
		for (f = current_program->linkage_storage; f; f = f->sister) {
			for (l = using_list; l; l = CB_CHAIN (l)) {
				x = CB_VALUE (l);
				if (x != cb_error_node && cb_ref (x) != cb_error_node) {
					if (f == CB_FIELD (cb_ref (x))) {
						break;
					}
				}
			}
			if (!l && !f->redefines) {
				cb_warning (_("LINKAGE item '%s' is not a PROCEDURE USING parameter"), f->name);
			}
		}
	}

	for (l = current_program->entry_list; l; l = CB_CHAIN (l)) {
		if (strcmp ((const char *)name, (const char *)(CB_LABEL(CB_PURPOSE(l))->name)) == 0) {
			cb_error_x (CB_TREE (current_statement), _("ENTRY '%s' duplicated"), name);
		}
	}

	current_program->entry_list = cb_list_append (current_program->entry_list,
							cb_build_pair (label, using_list));
}

static void
terminator_warning (const size_t termid)
{
	check_unreached = 0;
	if (cb_warn_terminator && term_array[termid]) {
		cb_warning_x (CB_TREE (current_statement),
			_("%s statement not terminated by END-%s"),
			current_statement->name, current_statement->name);
	}
	if (term_array[termid]) {
		term_array[termid]--;
	}
}

static void
terminator_error (void)
{
	check_unreached = 0;
	cb_error_x (CB_TREE (current_statement),
			_("%s statement not terminated by END-%s"),
			current_statement->name, current_statement->name);
}

static void
terminator_clear (const size_t termid)
{
	check_unreached = 0;
	if (term_array[termid]) {
		term_array[termid]--;
	}
}

static int
literal_value (cb_tree x)
{
	if (x == cb_space) {
		return ' ';
	} else if (x == cb_zero) {
		return '0';
	} else if (x == cb_quote) {
		return '"';
	} else if (x == cb_null) {
		return 0;
	} else if (CB_TREE_CLASS (x) == CB_CLASS_NUMERIC) {
		return cb_get_int (x);
	} else {
		return CB_LITERAL (x)->data[0];
	}
}

static void
setup_use_file (struct cb_file *fileptr)
{
	struct cb_file	*newptr;

	if (fileptr->organization == COB_ORG_SORT) {
		cb_error (_("USE statement invalid for SORT file"));
	}
	if (fileptr->global) {
		newptr = cobc_malloc (sizeof(struct cb_file));
		*newptr = *fileptr;
		newptr->handler = current_section;
		newptr->handler_prog = current_program;
		if (!use_global_ind) {
			current_program->local_file_list =
				cb_list_add (current_program->local_file_list,
					     CB_TREE (newptr));
		} else {
			current_program->global_file_list =
				cb_list_add (current_program->global_file_list,
					     CB_TREE (newptr));
		}
	} else {
		fileptr->handler = current_section;
	}
}


/* Line 371 of yacc.c  */
#line 352 "parser.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKEN_EOF = 0,
     ACCEPT = 258,
     ACCESS = 259,
     ADD = 260,
     ADDRESS = 261,
     ADVANCING = 262,
     AFTER = 263,
     ALL = 264,
     ALLOCATE = 265,
     ALPHABET = 266,
     ALPHABETIC = 267,
     ALPHABETIC_LOWER = 268,
     ALPHABETIC_UPPER = 269,
     ALPHANUMERIC = 270,
     ALPHANUMERIC_EDITED = 271,
     ALSO = 272,
     ALTER = 273,
     ALTERNATE = 274,
     AND = 275,
     ANY = 276,
     APPLY = 277,
     ARE = 278,
     AREA = 279,
     ARGUMENT_NUMBER = 280,
     ARGUMENT_VALUE = 281,
     AS = 282,
     ASCENDING = 283,
     ASSIGN = 284,
     AT = 285,
     AUTO = 286,
     AUTOMATIC = 287,
     BACKGROUND_COLOR = 288,
     BASED = 289,
     BEFORE = 290,
     BELL = 291,
     BINARY = 292,
     BINARY_C_LONG = 293,
     BINARY_CHAR = 294,
     BINARY_DOUBLE = 295,
     BINARY_LONG = 296,
     BINARY_SHORT = 297,
     BLANK = 298,
     BLANK_LINE = 299,
     BLANK_SCREEN = 300,
     BLINK = 301,
     BLOCK = 302,
     BOTTOM = 303,
     BY = 304,
     BYTE_LENGTH = 305,
     CALL = 306,
     CANCEL = 307,
     CH = 308,
     CHAINING = 309,
     CHARACTER = 310,
     CHARACTERS = 311,
     CLASS = 312,
     CLASS_NAME = 313,
     CLOSE = 314,
     CLOSE_NOFEED = 315,
     CODE = 316,
     CODE_SET = 317,
     COLLATING = 318,
     COL = 319,
     COLS = 320,
     COLUMN = 321,
     COLUMNS = 322,
     COMMA = 323,
     COMMAND_LINE = 324,
     COMMA_DELIM = 325,
     COMMIT = 326,
     COMMITMENT_CONTROL = 327,
     COMMON = 328,
     COMP = 329,
     COMPUTE = 330,
     COMP_1 = 331,
     COMP_2 = 332,
     COMP_3 = 333,
     COMP_4 = 334,
     COMP_5 = 335,
     COMP_X = 336,
     CONCATENATE_FUNC = 337,
     CONFIGURATION = 338,
     CONSTANT = 339,
     CONTAINS = 340,
     CONTENT = 341,
     CONTINUE = 342,
     CONTROL = 343,
     CONTROLS = 344,
     CONTROL_FOOTING = 345,
     CONTROL_HEADING = 346,
     CONVERTING = 347,
     CORE_INDEX = 348,
     CORRESPONDING = 349,
     COUNT = 350,
     CRT = 351,
     CURRENCY = 352,
     CURRENT_DATE_FUNC = 353,
     CURSOR = 354,
     CYCLE = 355,
     CYL_OVERFLOW = 356,
     DATA = 357,
     DATE = 358,
     DAY = 359,
     DAY_OF_WEEK = 360,
     DE = 361,
     DEBUGGING = 362,
     DECIMAL_POINT = 363,
     DECLARATIVES = 364,
     DEFAULT = 365,
     DELETE = 366,
     DELIMITED = 367,
     DELIMITER = 368,
     DEPENDING = 369,
     DESCENDING = 370,
     DETAIL = 371,
     DISK = 372,
     DISPLAY = 373,
     DIVIDE = 374,
     DIVISION = 375,
     DOWN = 376,
     DUPLICATES = 377,
     DYNAMIC = 378,
     EBCDIC = 379,
     ELSE = 380,
     END = 381,
     END_ACCEPT = 382,
     END_ADD = 383,
     END_CALL = 384,
     END_COMPUTE = 385,
     END_DELETE = 386,
     END_DISPLAY = 387,
     END_DIVIDE = 388,
     END_EVALUATE = 389,
     END_FUNCTION = 390,
     END_IF = 391,
     END_MULTIPLY = 392,
     END_PERFORM = 393,
     END_PROGRAM = 394,
     END_READ = 395,
     END_RETURN = 396,
     END_REWRITE = 397,
     END_SEARCH = 398,
     END_START = 399,
     END_STRING = 400,
     END_SUBTRACT = 401,
     END_UNSTRING = 402,
     END_WRITE = 403,
     ENTRY = 404,
     ENVIRONMENT = 405,
     ENVIRONMENT_NAME = 406,
     ENVIRONMENT_VALUE = 407,
     EOL = 408,
     EOP = 409,
     EOS = 410,
     EQUAL = 411,
     EQUALS = 412,
     ERASE = 413,
     ERROR = 414,
     ESCAPE = 415,
     EVALUATE = 416,
     EVENT_STATUS = 417,
     EXCEPTION = 418,
     EXCLUSIVE = 419,
     EXIT = 420,
     EXTEND = 421,
     EXTERNAL = 422,
     FD = 423,
     FILE_CONTROL = 424,
     FILE_ID = 425,
     FILLER = 426,
     FINAL = 427,
     FIRST = 428,
     FOOTING = 429,
     FOR = 430,
     FOREGROUND_COLOR = 431,
     FOREVER = 432,
     FORMS_OVERLAY = 433,
     FREE = 434,
     FROM = 435,
     FULL = 436,
     FUNCTION = 437,
     FUNCTION_ID = 438,
     FUNCTION_NAME = 439,
     GE = 440,
     GENERATE = 441,
     GIVING = 442,
     GLOBAL = 443,
     GO = 444,
     GOBACK = 445,
     GREATER = 446,
     GROUP = 447,
     HEADING = 448,
     HIGHLIGHT = 449,
     HIGH_VALUE = 450,
     IDENTIFICATION = 451,
     IF = 452,
     IGNORE = 453,
     IGNORING = 454,
     IN = 455,
     INDEX = 456,
     INDEXED = 457,
     INDICATE = 458,
     INITIALIZE = 459,
     INITIALIZED = 460,
     INITIATE = 461,
     INPUT = 462,
     INPUT_OUTPUT = 463,
     INSPECT = 464,
     INTO = 465,
     INTRINSIC = 466,
     INVALID = 467,
     INVALID_KEY = 468,
     IS = 469,
     I_O = 470,
     I_O_CONTROL = 471,
     JUSTIFIED = 472,
     KEY = 473,
     LABEL = 474,
     LAST = 475,
     LAST_DETAIL = 476,
     LE = 477,
     LEADING = 478,
     LEFT = 479,
     LENGTH = 480,
     LESS = 481,
     LEVEL_NUMBER_WORD = 482,
     LEVEL88_NUMBER_WORD = 483,
     LIMIT = 484,
     LIMITS = 485,
     LINAGE = 486,
     LINAGE_COUNTER = 487,
     LINE = 488,
     LINES = 489,
     LINKAGE = 490,
     LITERAL = 491,
     LOCALE = 492,
     LOCALE_DT_FUNC = 493,
     LOCAL_STORAGE = 494,
     LOCK = 495,
     LOWER_CASE_FUNC = 496,
     LOWLIGHT = 497,
     LOW_VALUE = 498,
     MANUAL = 499,
     MEMORY = 500,
     MERGE = 501,
     MINUS = 502,
     MNEMONIC_NAME = 503,
     MODE = 504,
     MOVE = 505,
     MULTIPLE = 506,
     MULTIPLY = 507,
     NATIONAL = 508,
     NATIONAL_EDITED = 509,
     NATIVE = 510,
     NE = 511,
     NEGATIVE = 512,
     NEXT = 513,
     NEXT_SENTENCE = 514,
     NO = 515,
     NOMINAL = 516,
     NOT = 517,
     NOT_END = 518,
     NOT_EOP = 519,
     NOT_EXCEPTION = 520,
     NOT_INVALID_KEY = 521,
     NOT_OVERFLOW = 522,
     NOT_SIZE_ERROR = 523,
     NO_ADVANCING = 524,
     NUMBER = 525,
     NUMBERS = 526,
     NUMERIC = 527,
     NUMERIC_EDITED = 528,
     NUMVALC_FUNC = 529,
     OBJECT_COMPUTER = 530,
     OCCURS = 531,
     OF = 532,
     OFF = 533,
     OMITTED = 534,
     ON = 535,
     ONLY = 536,
     OPEN = 537,
     OPTIONAL = 538,
     OR = 539,
     ORDER = 540,
     ORGANIZATION = 541,
     OTHER = 542,
     OUTPUT = 543,
     OVERFLOW = 544,
     OVERLINE = 545,
     PACKED_DECIMAL = 546,
     PADDING = 547,
     PAGE = 548,
     PAGE_FOOTING = 549,
     PAGE_HEADING = 550,
     PARAGRAPH = 551,
     PERFORM = 552,
     PICTURE = 553,
     PLUS = 554,
     POINTER = 555,
     POSITION = 556,
     POSITIVE = 557,
     PRESENT = 558,
     PREVIOUS = 559,
     PRINTER = 560,
     PRINTING = 561,
     PROCEDURE = 562,
     PROCEDURES = 563,
     PROCEED = 564,
     PROGRAM = 565,
     PROGRAM_ID = 566,
     PROGRAM_NAME = 567,
     PROGRAM_POINTER = 568,
     PROMPT = 569,
     QUOTE = 570,
     RANDOM = 571,
     RD = 572,
     READ = 573,
     RECORD = 574,
     RECORDING = 575,
     RECORDS = 576,
     RECURSIVE = 577,
     REDEFINES = 578,
     REEL = 579,
     REFERENCE = 580,
     RELATIVE = 581,
     RELEASE = 582,
     REMAINDER = 583,
     REMOVAL = 584,
     RENAMES = 585,
     REPLACING = 586,
     REPORT = 587,
     REPORTING = 588,
     REPORTS = 589,
     REPORT_FOOTING = 590,
     REPORT_HEADING = 591,
     REPOSITORY = 592,
     REQUIRED = 593,
     RESERVE = 594,
     RETURN = 595,
     RETURNING = 596,
     REVERSE_FUNC = 597,
     REVERSE_VIDEO = 598,
     REWIND = 599,
     REWRITE = 600,
     RIGHT = 601,
     ROLLBACK = 602,
     ROUNDED = 603,
     RUN = 604,
     SAME = 605,
     SCREEN = 606,
     SCREEN_CONTROL = 607,
     SCROLL = 608,
     SD = 609,
     SEARCH = 610,
     SECTION = 611,
     SECURE = 612,
     SEGMENT_LIMIT = 613,
     SELECT = 614,
     SEMI_COLON = 615,
     SENTENCE = 616,
     SEPARATE = 617,
     SEQUENCE = 618,
     SEQUENTIAL = 619,
     SET = 620,
     SHARING = 621,
     SIGN = 622,
     SIGNED = 623,
     SIGNED_INT = 624,
     SIGNED_LONG = 625,
     SIGNED_SHORT = 626,
     SIZE = 627,
     SIZE_ERROR = 628,
     SORT = 629,
     SORT_MERGE = 630,
     SOURCE = 631,
     SOURCE_COMPUTER = 632,
     SPACE = 633,
     SPECIAL_NAMES = 634,
     STANDARD = 635,
     STANDARD_1 = 636,
     STANDARD_2 = 637,
     START = 638,
     STATUS = 639,
     STOP = 640,
     STRING = 641,
     SUBSTITUTE_FUNC = 642,
     SUBSTITUTE_CASE_FUNC = 643,
     SUBTRACT = 644,
     SUM = 645,
     SUPPRESS = 646,
     SYMBOLIC = 647,
     SYNCHRONIZED = 648,
     TALLYING = 649,
     TAPE = 650,
     TERMINATE = 651,
     TEST = 652,
     THAN = 653,
     THEN = 654,
     THRU = 655,
     TIME = 656,
     TIMES = 657,
     TO = 658,
     TOK_FALSE = 659,
     TOK_FILE = 660,
     TOK_INITIAL = 661,
     TOK_NULL = 662,
     TOK_TRUE = 663,
     TOP = 664,
     TRACKS = 665,
     TRAILING = 666,
     TRANSFORM = 667,
     TRIM_FUNCTION = 668,
     TYPE = 669,
     UNDERLINE = 670,
     UNIT = 671,
     UNLOCK = 672,
     UNSIGNED = 673,
     UNSIGNED_INT = 674,
     UNSIGNED_LONG = 675,
     UNSIGNED_SHORT = 676,
     UNSTRING = 677,
     UNTIL = 678,
     UP = 679,
     UPDATE = 680,
     UPON = 681,
     UPON_ARGUMENT_NUMBER = 682,
     UPON_COMMAND_LINE = 683,
     UPON_ENVIRONMENT_NAME = 684,
     UPON_ENVIRONMENT_VALUE = 685,
     UPPER_CASE_FUNC = 686,
     USAGE = 687,
     USE = 688,
     USING = 689,
     VALUE = 690,
     VARYING = 691,
     WAIT = 692,
     WHEN = 693,
     WHEN_COMPILED_FUNC = 694,
     WHEN_OTHER = 695,
     WITH = 696,
     WORD = 697,
     WORDS = 698,
     WORKING_STORAGE = 699,
     WRITE = 700,
     YYYYDDD = 701,
     YYYYMMDD = 702,
     ZERO = 703,
     UNARY_SIGN = 704
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 868 "parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   5653

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  463
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  712
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1597
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2351

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   704

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   462,     2,
     458,   457,   451,   449,     2,   450,   455,   452,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   461,     2,
     460,   456,   459,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   454,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   453
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     8,    10,    13,    15,    17,    18,
      19,    28,    29,    30,    39,    40,    41,    49,    50,    52,
      55,    56,    60,    64,    68,    69,    77,    83,    85,    87,
      88,    91,    92,    96,    98,   101,   103,   105,   107,   108,
     114,   115,   120,   121,   124,   126,   128,   130,   132,   136,
     137,   140,   144,   147,   151,   153,   157,   158,   161,   165,
     168,   170,   173,   175,   177,   179,   185,   187,   189,   194,
     198,   202,   203,   206,   208,   211,   215,   219,   221,   224,
     228,   229,   231,   234,   236,   239,   241,   243,   245,   247,
     249,   251,   253,   255,   257,   259,   261,   265,   266,   272,
     273,   278,   282,   286,   290,   294,   295,   298,   300,   303,
     308,   310,   312,   313,   319,   321,   323,   325,   327,   329,
     331,   334,   336,   340,   341,   346,   348,   352,   354,   356,
     358,   360,   362,   364,   366,   368,   370,   372,   374,   376,
     380,   384,   386,   389,   391,   394,   399,   401,   404,   406,
     410,   415,   420,   424,   428,   433,   437,   441,   442,   448,
     449,   454,   455,   460,   461,   465,   466,   469,   470,   477,
     478,   481,   483,   485,   487,   489,   491,   493,   495,   497,
     499,   501,   503,   505,   507,   509,   511,   517,   522,   527,
     528,   530,   532,   533,   535,   537,   539,   541,   544,   546,
     549,   554,   556,   558,   560,   567,   576,   577,   580,   583,
     585,   586,   589,   591,   595,   601,   602,   604,   606,   611,
     614,   617,   619,   620,   625,   631,   634,   636,   638,   642,
     644,   646,   650,   652,   654,   657,   662,   667,   672,   679,
     684,   688,   691,   695,   698,   701,   704,   709,   710,   714,
     715,   718,   720,   722,   724,   727,   729,   731,   737,   738,
     740,   742,   744,   750,   752,   755,   758,   759,   762,   765,
     767,   770,   775,   783,   790,   797,   802,   803,   813,   814,
     815,   821,   822,   826,   827,   830,   834,   837,   840,   842,
     844,   845,   850,   851,   854,   857,   860,   862,   864,   866,
     868,   870,   872,   874,   876,   878,   880,   886,   887,   889,
     891,   896,   903,   913,   914,   918,   919,   922,   923,   926,
     930,   932,   934,   940,   946,   948,   950,   954,   960,   961,
     964,   966,   968,   970,   976,   981,   985,   990,   994,   998,
    1002,  1003,  1004,  1010,  1011,  1013,  1014,  1017,  1020,  1024,
    1027,  1029,  1030,  1036,  1037,  1042,  1044,  1046,  1047,  1049,
    1050,  1052,  1054,  1056,  1057,  1060,  1062,  1066,  1070,  1077,
    1078,  1081,  1083,  1085,  1087,  1089,  1091,  1093,  1095,  1097,
    1099,  1101,  1103,  1105,  1107,  1109,  1111,  1114,  1118,  1119,
    1122,  1125,  1127,  1129,  1133,  1135,  1137,  1139,  1141,  1143,
    1145,  1147,  1149,  1151,  1153,  1155,  1157,  1159,  1161,  1163,
    1165,  1167,  1169,  1171,  1174,  1177,  1179,  1182,  1185,  1187,
    1190,  1193,  1195,  1198,  1201,  1203,  1206,  1209,  1211,  1213,
    1217,  1221,  1222,  1225,  1228,  1235,  1236,  1239,  1240,  1244,
    1245,  1247,  1249,  1254,  1256,  1259,  1261,  1263,  1264,  1266,
    1270,  1272,  1275,  1277,  1280,  1283,  1284,  1286,  1288,  1292,
    1294,  1298,  1299,  1308,  1310,  1313,  1315,  1319,  1320,  1324,
    1327,  1332,  1335,  1336,  1337,  1343,  1344,  1345,  1351,  1352,
    1353,  1359,  1360,  1362,  1364,  1367,  1373,  1374,  1377,  1380,
    1384,  1386,  1388,  1391,  1394,  1397,  1398,  1400,  1402,  1405,
    1414,  1415,  1419,  1420,  1425,  1426,  1431,  1432,  1436,  1437,
    1441,  1443,  1448,  1451,  1453,  1455,  1456,  1459,  1464,  1465,
    1468,  1470,  1472,  1474,  1476,  1478,  1480,  1482,  1484,  1486,
    1488,  1490,  1492,  1494,  1496,  1498,  1500,  1504,  1506,  1508,
    1510,  1512,  1514,  1516,  1518,  1523,  1528,  1531,  1533,  1535,
    1538,  1542,  1544,  1548,  1555,  1558,  1562,  1565,  1567,  1570,
    1573,  1575,  1578,  1579,  1581,  1583,  1588,  1591,  1592,  1594,
    1596,  1597,  1598,  1599,  1606,  1607,  1609,  1611,  1614,  1616,
    1617,  1623,  1624,  1627,  1629,  1631,  1633,  1635,  1638,  1641,
    1643,  1645,  1647,  1649,  1651,  1653,  1655,  1657,  1659,  1661,
    1667,  1673,  1677,  1681,  1683,  1685,  1687,  1689,  1691,  1693,
    1695,  1698,  1701,  1704,  1705,  1707,  1709,  1711,  1713,  1714,
    1716,  1718,  1720,  1722,  1726,  1727,  1728,  1729,  1739,  1740,
    1741,  1745,  1746,  1750,  1752,  1755,  1760,  1761,  1764,  1767,
    1768,  1772,  1776,  1781,  1785,  1786,  1788,  1789,  1792,  1793,
    1794,  1802,  1803,  1806,  1808,  1810,  1812,  1815,  1817,  1822,
    1825,  1827,  1829,  1830,  1832,  1833,  1834,  1838,  1839,  1842,
    1844,  1846,  1848,  1850,  1852,  1854,  1856,  1858,  1860,  1862,
    1864,  1866,  1868,  1870,  1872,  1874,  1876,  1878,  1880,  1882,
    1884,  1886,  1888,  1890,  1892,  1894,  1896,  1898,  1900,  1902,
    1904,  1906,  1908,  1910,  1912,  1914,  1916,  1918,  1920,  1922,
    1924,  1926,  1928,  1930,  1932,  1934,  1936,  1938,  1940,  1942,
    1943,  1948,  1953,  1958,  1962,  1966,  1970,  1975,  1979,  1984,
    1988,  1992,  1996,  2001,  2007,  2011,  2016,  2020,  2024,  2025,
    2029,  2033,  2036,  2039,  2042,  2046,  2050,  2054,  2055,  2058,
    2060,  2063,  2065,  2067,  2069,  2071,  2073,  2075,  2077,  2081,
    2085,  2089,  2093,  2095,  2097,  2099,  2101,  2103,  2105,  2106,
    2108,  2109,  2114,  2119,  2125,  2132,  2133,  2136,  2137,  2139,
    2140,  2144,  2148,  2154,  2155,  2158,  2161,  2162,  2168,  2169,
    2172,  2173,  2182,  2183,  2184,  2188,  2190,  2193,  2196,  2200,
    2201,  2204,  2207,  2210,  2211,  2214,  2217,  2218,  2219,  2223,
    2224,  2225,  2229,  2230,  2232,  2233,  2237,  2238,  2241,  2243,
    2244,  2248,  2249,  2253,  2254,  2256,  2260,  2264,  2267,  2269,
    2271,  2272,  2277,  2282,  2283,  2285,  2287,  2289,  2291,  2293,
    2294,  2301,  2302,  2304,  2305,  2310,  2311,  2316,  2320,  2324,
    2328,  2332,  2337,  2344,  2351,  2358,  2365,  2366,  2369,  2372,
    2374,  2377,  2379,  2381,  2384,  2387,  2389,  2391,  2393,  2395,
    2397,  2401,  2405,  2409,  2413,  2415,  2417,  2418,  2420,  2421,
    2426,  2431,  2438,  2445,  2454,  2463,  2464,  2466,  2467,  2472,
    2473,  2479,  2481,  2485,  2487,  2489,  2491,  2494,  2496,  2499,
    2500,  2504,  2505,  2506,  2510,  2513,  2517,  2519,  2523,  2526,
    2528,  2530,  2532,  2533,  2536,  2537,  2539,  2540,  2544,  2545,
    2547,  2549,  2552,  2554,  2556,  2557,  2561,  2562,  2566,  2567,
    2573,  2574,  2578,  2579,  2582,  2583,  2584,  2593,  2597,  2598,
    2599,  2603,  2604,  2606,  2607,  2615,  2616,  2619,  2620,  2624,
    2628,  2629,  2632,  2634,  2637,  2642,  2644,  2646,  2648,  2650,
    2652,  2654,  2656,  2657,  2659,  2660,  2664,  2665,  2670,  2672,
    2674,  2676,  2678,  2681,  2683,  2685,  2687,  2688,  2692,  2694,
    2697,  2700,  2703,  2705,  2707,  2709,  2712,  2715,  2717,  2720,
    2725,  2728,  2729,  2731,  2733,  2735,  2737,  2742,  2748,  2749,
    2754,  2755,  2757,  2758,  2762,  2763,  2767,  2771,  2776,  2777,
    2782,  2787,  2794,  2795,  2797,  2798,  2802,  2803,  2809,  2811,
    2813,  2815,  2817,  2818,  2822,  2823,  2827,  2830,  2831,  2835,
    2838,  2839,  2844,  2847,  2848,  2850,  2852,  2856,  2857,  2859,
    2862,  2866,  2870,  2871,  2875,  2877,  2881,  2889,  2890,  2901,
    2902,  2905,  2906,  2909,  2912,  2916,  2920,  2923,  2924,  2928,
    2929,  2931,  2933,  2934,  2936,  2937,  2942,  2943,  2951,  2952,
    2954,  2955,  2963,  2964,  2967,  2971,  2972,  2974,  2976,  2977,
    2982,  2987,  2988,  2996,  2997,  3000,  3001,  3002,  3007,  3009,
    3012,  3013,  3018,  3019,  3021,  3022,  3026,  3028,  3030,  3032,
    3034,  3036,  3041,  3046,  3050,  3055,  3057,  3059,  3061,  3064,
    3068,  3070,  3073,  3077,  3081,  3082,  3086,  3087,  3095,  3096,
    3103,  3104,  3107,  3108,  3111,  3112,  3116,  3117,  3120,  3125,
    3126,  3129,  3134,  3135,  3136,  3144,  3145,  3150,  3153,  3156,
    3159,  3162,  3165,  3166,  3168,  3169,  3174,  3175,  3179,  3180,
    3183,  3186,  3187,  3196,  3198,  3201,  3203,  3207,  3211,  3212,
    3216,  3217,  3219,  3220,  3225,  3230,  3237,  3244,  3245,  3247,
    3250,  3251,  3253,  3254,  3258,  3259,  3267,  3268,  3273,  3274,
    3276,  3278,  3279,  3289,  3290,  3294,  3296,  3300,  3303,  3306,
    3309,  3313,  3314,  3318,  3319,  3323,  3324,  3328,  3329,  3331,
    3333,  3335,  3337,  3346,  3347,  3349,  3351,  3353,  3355,  3357,
    3359,  3360,  3362,  3363,  3365,  3367,  3369,  3371,  3373,  3375,
    3377,  3378,  3380,  3386,  3388,  3391,  3397,  3398,  3407,  3408,
    3411,  3412,  3417,  3421,  3425,  3427,  3429,  3430,  3432,  3434,
    3435,  3437,  3440,  3443,  3444,  3445,  3449,  3450,  3451,  3455,
    3458,  3459,  3460,  3464,  3465,  3466,  3470,  3473,  3474,  3475,
    3479,  3480,  3481,  3485,  3487,  3489,  3492,  3493,  3497,  3498,
    3502,  3504,  3506,  3509,  3510,  3514,  3515,  3519,  3520,  3522,
    3524,  3526,  3529,  3530,  3534,  3535,  3539,  3540,  3544,  3546,
    3548,  3549,  3552,  3555,  3558,  3561,  3564,  3567,  3570,  3573,
    3576,  3579,  3582,  3585,  3588,  3591,  3594,  3597,  3600,  3603,
    3606,  3609,  3610,  3613,  3616,  3619,  3622,  3625,  3628,  3631,
    3634,  3637,  3640,  3643,  3646,  3649,  3652,  3655,  3658,  3661,
    3664,  3667,  3670,  3673,  3676,  3679,  3682,  3685,  3688,  3691,
    3693,  3696,  3698,  3700,  3703,  3705,  3708,  3710,  3716,  3721,
    3723,  3729,  3734,  3736,  3740,  3741,  3743,  3745,  3747,  3751,
    3755,  3759,  3763,  3766,  3769,  3773,  3777,  3779,  3783,  3785,
    3788,  3791,  3793,  3795,  3797,  3800,  3802,  3804,  3807,  3809,
    3810,  3813,  3815,  3817,  3819,  3823,  3825,  3827,  3830,  3832,
    3834,  3837,  3838,  3840,  3842,  3844,  3846,  3848,  3851,  3853,
    3857,  3859,  3862,  3864,  3868,  3872,  3876,  3881,  3885,  3887,
    3889,  3891,  3893,  3897,  3901,  3905,  3907,  3909,  3911,  3913,
    3915,  3917,  3919,  3921,  3923,  3925,  3927,  3929,  3931,  3933,
    3935,  3937,  3939,  3941,  3943,  3945,  3947,  3950,  3953,  3957,
    3959,  3963,  3967,  3972,  3978,  3980,  3982,  3985,  3987,  3991,
    3993,  3995,  3997,  3999,  4001,  4003,  4005,  4008,  4011,  4017,
    4023,  4029,  4035,  4041,  4047,  4053,  4058,  4064,  4067,  4068,
    4073,  4079,  4080,  4084,  4085,  4087,  4089,  4093,  4097,  4099,
    4103,  4105,  4109,  4110,  4111,  4113,  4114,  4116,  4117,  4119,
    4120,  4122,  4124,  4125,  4127,  4128,  4130,  4131,  4133,  4134,
    4137,  4139,  4141,  4144,  4147,  4150,  4152,  4155,  4157,  4158,
    4160,  4161,  4163,  4164,  4166,  4167,  4169,  4170,  4172,  4173,
    4175,  4176,  4178,  4179,  4181,  4182,  4184,  4185,  4187,  4188,
    4190,  4191,  4193,  4194,  4196,  4197,  4199,  4200,  4202,  4203,
    4205,  4206,  4208,  4209,  4211,  4213,  4214,  4216,  4217,  4219,
    4221,  4222,  4224,  4225,  4227,  4228,  4230,  4231,  4233,  4234,
    4236,  4237,  4239,  4240,  4242,  4245,  4246,  4248,  4249,  4251,
    4252,  4254,  4255,  4257,  4258,  4260,  4261,  4263,  4264,  4266,
    4269,  4270,  4272,  4273,  4275,  4276,  4278,  4279,  4281,  4282,
    4284,  4285,  4287,  4288,  4290,  4291,  4293,  4294
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     464,     0,    -1,    -1,   465,   466,     0,    -1,   467,    -1,
     466,   467,    -1,   468,    -1,   474,    -1,    -1,    -1,   481,
     489,   469,   594,   470,   736,   477,   478,    -1,    -1,    -1,
     481,   489,   472,   594,   473,   736,   477,   479,    -1,    -1,
      -1,   483,   489,   475,   594,   476,   736,   480,    -1,    -1,
     471,    -1,   477,   471,    -1,    -1,   139,   484,   455,    -1,
     139,   484,   455,    -1,   135,   484,   455,    -1,    -1,   311,
     455,   484,   485,   482,   486,   455,    -1,   183,   455,   484,
     485,   455,    -1,   312,    -1,   236,    -1,    -1,    27,   236,
      -1,    -1,  1148,   487,  1160,    -1,    73,    -1,    73,   488,
      -1,   488,    -1,   406,    -1,   322,    -1,    -1,   150,   120,
     455,   490,   544,    -1,    -1,    83,   356,   455,   491,    -1,
      -1,   491,   492,    -1,   493,    -1,   497,    -1,   510,    -1,
     505,    -1,   377,   455,   494,    -1,    -1,   496,   455,    -1,
     496,   495,   455,    -1,   495,   455,    -1,  1174,   107,   249,
      -1,   442,    -1,   275,   455,   498,    -1,    -1,   496,   455,
      -1,   496,   499,   455,    -1,   499,   455,    -1,   500,    -1,
     499,   500,    -1,   501,    -1,   503,    -1,   504,    -1,   245,
     372,  1148,  1108,   502,    -1,    56,    -1,   443,    -1,  1160,
    1131,  1148,  1086,    -1,   358,  1148,  1108,    -1,   337,   455,
     506,    -1,    -1,   507,   455,    -1,   508,    -1,   507,   508,
      -1,   182,   509,   211,    -1,   182,     9,   211,    -1,   236,
      -1,   509,   236,    -1,   379,   455,   511,    -1,    -1,   512,
      -1,   512,   455,    -1,   513,    -1,   512,   513,    -1,   514,
      -1,   521,    -1,   530,    -1,   537,    -1,   534,    -1,   538,
      -1,   539,    -1,   540,    -1,   541,    -1,   542,    -1,   543,
      -1,   442,  1148,    96,    -1,    -1,   442,  1148,  1090,   515,
     517,    -1,    -1,   442,  1148,   516,   518,    -1,    25,  1148,
    1090,    -1,    26,  1148,  1090,    -1,   151,  1148,  1090,    -1,
     152,  1148,  1090,    -1,    -1,   517,   519,    -1,   519,    -1,
     518,   519,    -1,   520,  1167,  1148,  1090,    -1,   280,    -1,
     278,    -1,    -1,    11,  1090,   522,  1148,   523,    -1,   255,
      -1,   381,    -1,   382,    -1,   124,    -1,   524,    -1,   525,
      -1,   524,   525,    -1,   528,    -1,   528,   400,   528,    -1,
      -1,   528,    17,   526,   527,    -1,   529,    -1,   527,    17,
     529,    -1,   236,    -1,   378,    -1,   448,    -1,   315,    -1,
     195,    -1,   243,    -1,   236,    -1,   378,    -1,   448,    -1,
     315,    -1,   195,    -1,   243,    -1,   392,  1141,   531,    -1,
     532,  1149,   533,    -1,  1090,    -1,   532,  1090,    -1,  1108,
      -1,   533,  1108,    -1,    57,  1090,  1148,   535,    -1,   536,
      -1,   535,   536,    -1,  1111,    -1,  1111,   400,  1111,    -1,
     237,  1090,  1148,  1086,    -1,    97,  1164,  1148,   236,    -1,
     108,  1148,    68,    -1,    99,  1148,  1086,    -1,    96,   384,
    1148,  1086,    -1,   352,  1148,  1086,    -1,   162,  1148,  1086,
      -1,    -1,   208,   356,   455,   547,   582,    -1,    -1,   169,
     455,   545,   548,    -1,    -1,   216,   455,   546,   583,    -1,
      -1,   169,   455,   548,    -1,    -1,   548,   549,    -1,    -1,
     359,  1125,  1090,   550,   551,   455,    -1,    -1,   551,   552,
      -1,   553,    -1,   558,    -1,   560,    -1,   565,    -1,   566,
      -1,   568,    -1,   572,    -1,   574,    -1,   575,    -1,   576,
      -1,   577,    -1,   578,    -1,   579,    -1,     1,    -1,   581,
      -1,    29,  1172,   555,   554,   556,    -1,    29,  1172,   555,
     117,    -1,    29,  1172,   555,   305,    -1,    -1,   117,    -1,
     305,    -1,    -1,   167,    -1,   123,    -1,   236,    -1,   118,
      -1,  1153,   557,    -1,  1105,    -1,   557,  1105,    -1,     4,
    1154,  1148,   559,    -1,   364,    -1,   123,    -1,   316,    -1,
      19,   319,  1150,  1148,  1086,  1121,    -1,    19,   319,  1150,
    1148,  1086,   564,   561,  1121,    -1,    -1,   562,   563,    -1,
     561,   563,    -1,  1086,    -1,    -1,   376,  1148,    -1,   456,
      -1,  1131,  1148,   442,    -1,   567,   384,  1148,  1086,  1088,
      -1,    -1,   405,    -1,   374,    -1,   240,  1154,  1148,   569,
      -1,   244,   570,    -1,    32,   570,    -1,   164,    -1,    -1,
     441,   240,   280,   571,    -1,   441,   240,   280,   251,   571,
      -1,   441,   347,    -1,   319,    -1,   321,    -1,   286,  1148,
     573,    -1,   573,    -1,   202,    -1,   319,  1138,   364,    -1,
     364,    -1,   326,    -1,   233,   364,    -1,   292,  1140,  1148,
    1089,    -1,   319,   113,  1148,   381,    -1,   319,  1150,  1148,
    1086,    -1,   319,  1150,  1148,  1086,   564,   561,    -1,   326,
    1150,  1148,  1086,    -1,   339,  1108,  1135,    -1,   339,   260,
      -1,   366,  1174,   580,    -1,     9,  1159,    -1,   260,  1159,
      -1,   318,   281,    -1,   261,  1150,  1148,  1086,    -1,    -1,
     216,   455,   583,    -1,    -1,   584,   455,    -1,   584,    -1,
     592,    -1,   585,    -1,   584,   585,    -1,   586,    -1,   588,
      -1,   350,   587,  1135,  1145,  1077,    -1,    -1,   319,    -1,
     374,    -1,   375,    -1,   251,  1144,  1168,  1142,   589,    -1,
     590,    -1,   589,   590,    -1,  1078,   591,    -1,    -1,   301,
    1108,    -1,   592,   455,    -1,   593,    -1,   592,   593,    -1,
      22,    72,  1157,  1085,    -1,    22,   101,  1156,   236,   410,
     280,  1085,    -1,    22,    93,   403,  1086,   280,  1085,    -1,
      22,   178,   403,  1086,   280,  1085,    -1,    22,    60,   280,
    1085,    -1,    -1,   102,   120,   455,   595,   626,   679,   681,
     683,   724,    -1,    -1,    -1,   405,   356,   455,   596,   598,
      -1,    -1,   601,   597,   600,    -1,    -1,   598,   599,    -1,
     601,   602,   628,    -1,   602,   628,    -1,   600,   599,    -1,
     168,    -1,   354,    -1,    -1,  1078,   603,   604,   455,    -1,
      -1,   604,   605,    -1,  1148,   167,    -1,  1148,   188,    -1,
     606,    -1,   608,    -1,   612,    -1,   614,    -1,   616,    -1,
     617,    -1,   623,    -1,   624,    -1,   625,    -1,     1,    -1,
      47,  1142,  1108,   611,   607,    -1,    -1,   321,    -1,    56,
      -1,   319,  1142,  1108,  1141,    -1,   319,  1142,  1108,   403,
    1108,  1141,    -1,   319,  1148,   436,  1147,  1166,   610,   611,
    1141,   609,    -1,    -1,   114,  1157,  1086,    -1,    -1,  1146,
    1108,    -1,    -1,   403,  1108,    -1,   219,  1129,   613,    -1,
     380,    -1,   279,    -1,   435,   277,   442,  1148,   615,    -1,
     435,   277,   170,  1148,   615,    -1,   236,    -1,  1105,    -1,
     102,  1129,  1087,    -1,   231,  1148,  1089,  1152,   618,    -1,
      -1,   618,   619,    -1,   620,    -1,   621,    -1,   622,    -1,
    1174,   174,  1137,  1089,  1152,    -1,  1137,   409,  1089,  1152,
      -1,  1137,    48,  1089,    -1,   320,  1154,  1148,   442,    -1,
      62,  1148,   442,    -1,   332,  1148,   723,    -1,   334,  1134,
     723,    -1,    -1,    -1,   444,   356,   455,   627,   628,    -1,
      -1,   629,    -1,    -1,   630,   631,    -1,  1119,   632,    -1,
     631,  1119,   632,    -1,   631,   455,    -1,   642,    -1,    -1,
     635,   638,   633,   643,   637,    -1,    -1,   636,   638,   634,
     672,    -1,   227,    -1,   228,    -1,    -1,   236,    -1,    -1,
     171,    -1,   442,    -1,   442,    -1,    -1,  1148,   188,    -1,
    1109,    -1,   225,  1156,  1104,    -1,    50,  1156,  1104,    -1,
     635,   639,    84,   640,  1136,   641,    -1,    -1,   643,   644,
      -1,   645,    -1,   646,    -1,   648,    -1,   649,    -1,   650,
      -1,   652,    -1,   654,    -1,   666,    -1,   667,    -1,   669,
      -1,   670,    -1,   671,    -1,   677,    -1,   678,    -1,     1,
      -1,   323,  1104,    -1,  1148,   167,   647,    -1,    -1,    27,
     236,    -1,  1148,   188,    -1,   298,    -1,   651,    -1,   432,
    1148,   651,    -1,    37,    -1,    74,    -1,    76,    -1,    77,
      -1,    78,    -1,    79,    -1,    80,    -1,    81,    -1,   118,
      -1,   201,    -1,   291,    -1,   300,    -1,   313,    -1,   371,
      -1,   369,    -1,   370,    -1,   421,    -1,   419,    -1,   420,
      -1,    39,   368,    -1,    39,   418,    -1,    39,    -1,    42,
     368,    -1,    42,   418,    -1,    42,    -1,    41,   368,    -1,
      41,   418,    -1,    41,    -1,    40,   368,    -1,    40,   418,
      -1,    40,    -1,    38,   368,    -1,    38,   418,    -1,    38,
      -1,   253,    -1,  1165,   223,  1127,    -1,  1165,   411,  1127,
      -1,    -1,   658,   662,    -1,   663,   657,    -1,   276,  1108,
     655,  1171,   656,   653,    -1,    -1,   403,  1108,    -1,    -1,
     114,  1157,  1086,    -1,    -1,   658,    -1,   660,    -1,   661,
    1150,  1148,  1085,    -1,   659,    -1,   660,   659,    -1,    28,
      -1,   115,    -1,    -1,   663,    -1,   202,  1139,   664,    -1,
     665,    -1,   664,   665,    -1,   442,    -1,   217,  1162,    -1,
     393,   668,    -1,    -1,   224,    -1,   346,    -1,    43,  1173,
     448,    -1,    34,    -1,   435,  1148,  1109,    -1,    -1,   435,
    1149,   674,   673,  1173,  1163,  1172,   676,    -1,   675,    -1,
     674,   675,    -1,  1109,    -1,  1109,   400,  1109,    -1,    -1,
     404,  1148,  1109,    -1,   330,  1105,    -1,   330,  1105,   400,
    1105,    -1,    21,   225,    -1,    -1,    -1,   239,   356,   455,
     680,   628,    -1,    -1,    -1,   235,   356,   455,   682,   628,
      -1,    -1,    -1,   332,   356,   455,   684,   685,    -1,    -1,
     686,    -1,   687,    -1,   686,   687,    -1,   317,   723,   688,
     455,   702,    -1,    -1,   688,   689,    -1,  1148,   188,    -1,
      61,  1148,  1100,    -1,   690,    -1,   694,    -1,    88,   691,
      -1,    89,   691,    -1,   692,   693,    -1,    -1,   172,    -1,
    1103,    -1,   693,  1103,    -1,   293,  1149,   700,   695,   696,
     697,   698,   699,    -1,    -1,   193,  1148,  1108,    -1,    -1,
     173,   116,  1148,  1108,    -1,    -1,   220,    91,  1148,  1108,
      -1,    -1,   221,  1148,  1108,    -1,    -1,   174,  1148,  1108,
      -1,  1108,    -1,  1108,   701,  1108,    67,    -1,  1108,   701,
      -1,   233,    -1,   234,    -1,    -1,   702,   703,    -1,   635,
     638,   704,   455,    -1,    -1,   704,   705,    -1,   706,    -1,
     708,    -1,   715,    -1,   649,    -1,   650,    -1,   652,    -1,
     666,    -1,   709,    -1,   669,    -1,   720,    -1,   710,    -1,
     671,    -1,   713,    -1,   721,    -1,   654,    -1,   714,    -1,
     414,  1148,   707,    -1,   336,    -1,   295,    -1,    91,    -1,
     116,    -1,    90,    -1,   294,    -1,   335,    -1,   258,   192,
    1148,  1108,    -1,    66,  1155,  1148,  1108,    -1,    66,   271,
      -1,    67,    -1,   711,    -1,   710,   711,    -1,   390,  1156,
     712,    -1,  1086,    -1,   303,   438,  1058,    -1,   436,  1103,
     180,  1094,    49,  1094,    -1,   716,   717,    -1,   233,   719,
    1149,    -1,   234,  1134,    -1,   718,    -1,   717,   718,    -1,
     299,  1108,    -1,  1108,    -1,   258,   293,    -1,    -1,   270,
      -1,   271,    -1,   376,  1148,  1103,  1126,    -1,   192,   722,
      -1,    -1,   203,    -1,   442,    -1,    -1,    -1,    -1,   351,
     356,   455,   725,   726,   727,    -1,    -1,   728,    -1,   729,
      -1,   728,   729,    -1,   642,    -1,    -1,   635,   638,   730,
     731,   455,    -1,    -1,   731,   732,    -1,    44,    -1,    45,
      -1,    36,    -1,    46,    -1,   158,   153,    -1,   158,   155,
      -1,   194,    -1,   242,    -1,   343,    -1,   415,    -1,   290,
      -1,    31,    -1,   357,    -1,   338,    -1,   181,    -1,   314,
      -1,   233,  1155,  1148,   733,  1102,    -1,    66,  1155,  1148,
     734,  1102,    -1,   176,  1148,  1102,    -1,    33,  1148,  1102,
      -1,   650,    -1,   669,    -1,   666,    -1,   652,    -1,   671,
      -1,   649,    -1,   735,    -1,   434,  1103,    -1,   180,  1101,
      -1,   403,  1103,    -1,    -1,   299,    -1,   449,    -1,   247,
      -1,   450,    -1,    -1,   299,    -1,   449,    -1,   247,    -1,
     450,    -1,   276,  1108,  1171,    -1,    -1,    -1,    -1,   307,
     120,   739,   747,   455,   737,   748,   738,   750,    -1,    -1,
      -1,   434,   740,   742,    -1,    -1,    54,   741,   742,    -1,
     743,    -1,   742,   743,    -1,   744,   745,   746,   442,    -1,
      -1,  1139,   325,    -1,  1139,   435,    -1,    -1,   372,  1148,
      31,    -1,   372,  1148,   110,    -1,   418,   372,  1148,  1108,
      -1,   372,  1148,  1108,    -1,    -1,   283,    -1,    -1,   341,
     442,    -1,    -1,    -1,   109,   455,   749,   750,   126,   109,
     455,    -1,    -1,   750,   751,    -1,   752,    -1,   753,    -1,
     754,    -1,   760,   455,    -1,     1,    -1,   755,   356,   756,
     455,    -1,   442,   455,    -1,   755,    -1,   442,    -1,    -1,
     236,    -1,    -1,    -1,   758,   759,   760,    -1,    -1,   760,
     761,    -1,   762,    -1,   772,    -1,   777,    -1,   781,    -1,
     784,    -1,   797,    -1,   800,    -1,   810,    -1,   805,    -1,
     811,    -1,   812,    -1,   815,    -1,   817,    -1,   824,    -1,
     828,    -1,   830,    -1,   845,    -1,   848,    -1,   850,    -1,
     852,    -1,   855,    -1,   857,    -1,   863,    -1,   872,    -1,
     874,    -1,   891,    -1,   893,    -1,   896,    -1,   900,    -1,
     906,    -1,   916,    -1,   923,    -1,   925,    -1,   928,    -1,
     932,    -1,   933,    -1,   944,    -1,   955,    -1,   965,    -1,
     971,    -1,   975,    -1,   981,    -1,   985,    -1,   987,    -1,
     989,    -1,   991,    -1,   994,    -1,  1005,    -1,  1018,    -1,
     259,    -1,    -1,     3,   763,   764,   771,    -1,  1103,   765,
     768,  1025,    -1,  1103,   180,   160,   218,    -1,  1103,   180,
     234,    -1,  1103,   180,    67,    -1,  1103,   180,   103,    -1,
    1103,   180,   103,   447,    -1,  1103,   180,   104,    -1,  1103,
     180,   104,   446,    -1,  1103,   180,   105,    -1,  1103,   180,
     401,    -1,  1103,   180,    69,    -1,  1103,   180,   152,  1025,
      -1,  1103,   180,   150,  1098,  1025,    -1,  1103,   180,    25,
      -1,  1103,   180,    26,  1025,    -1,  1103,   180,  1080,    -1,
    1103,   180,   442,    -1,    -1,  1137,   766,   767,    -1,  1137,
     767,   766,    -1,  1137,   766,    -1,  1137,   767,    -1,    30,
    1098,    -1,   233,  1155,  1100,    -1,    66,  1155,  1100,    -1,
     301,  1155,  1100,    -1,    -1,   441,   769,    -1,   770,    -1,
     769,   770,    -1,    36,    -1,    46,    -1,   194,    -1,   242,
      -1,   343,    -1,   415,    -1,   290,    -1,   176,  1148,  1102,
      -1,    33,  1148,  1102,    -1,   353,   424,  1057,    -1,   353,
     121,  1057,    -1,    31,    -1,   181,    -1,   338,    -1,   357,
      -1,   425,    -1,   314,    -1,    -1,   127,    -1,    -1,     5,
     773,   774,   776,    -1,  1093,   403,  1073,  1031,    -1,  1093,
     775,   187,  1073,  1031,    -1,    94,  1103,   403,  1103,  1126,
    1031,    -1,    -1,   403,  1094,    -1,    -1,   128,    -1,    -1,
      10,   778,   779,    -1,   442,  1122,   780,    -1,  1059,    56,
    1122,   341,  1092,    -1,    -1,   341,  1092,    -1,    18,   782,
      -1,    -1,   782,  1082,   403,   783,  1082,    -1,    -1,   309,
     403,    -1,    -1,    51,   785,  1101,   786,   791,   792,   794,
     796,    -1,    -1,    -1,   434,   787,   788,    -1,   789,    -1,
     788,   789,    -1,   790,   279,    -1,   790,   745,  1094,    -1,
      -1,  1139,   325,    -1,  1139,    86,    -1,  1139,   435,    -1,
      -1,   341,  1103,    -1,   187,  1103,    -1,    -1,    -1,  1012,
     793,   757,    -1,    -1,    -1,  1013,   795,   757,    -1,    -1,
     129,    -1,    -1,    52,   798,   799,    -1,    -1,   799,  1100,
      -1,     9,    -1,    -1,    59,   801,   802,    -1,    -1,   802,
    1078,   803,    -1,    -1,   804,    -1,   804,  1145,   329,    -1,
    1174,   260,   344,    -1,  1174,   240,    -1,   324,    -1,   416,
      -1,    -1,    75,   806,   807,   808,    -1,  1073,   809,  1059,
    1031,    -1,    -1,   130,    -1,   456,    -1,   156,    -1,    71,
      -1,    87,    -1,    -1,   111,   813,  1078,  1161,  1051,   814,
      -1,    -1,   131,    -1,    -1,   111,   816,   405,  1077,    -1,
      -1,   118,   818,   819,   823,    -1,  1100,   429,  1026,    -1,
    1100,   430,  1026,    -1,  1100,   427,  1026,    -1,  1100,   428,
    1026,    -1,  1093,   765,   820,  1026,    -1,  1093,   765,   426,
    1080,   820,  1026,    -1,  1093,   765,   426,   442,   820,  1026,
      -1,  1093,   765,   426,   305,   820,  1026,    -1,  1093,   765,
     426,    96,   820,  1026,    -1,    -1,  1174,   269,    -1,   441,
     821,    -1,   822,    -1,   821,   822,    -1,    36,    -1,    46,
      -1,   158,   153,    -1,   158,   155,    -1,   194,    -1,   242,
      -1,   343,    -1,   415,    -1,   290,    -1,   176,  1148,  1102,
      -1,    33,  1148,  1102,    -1,   353,   424,  1057,    -1,   353,
     121,  1057,    -1,    44,    -1,    45,    -1,    -1,   132,    -1,
      -1,   119,   825,   826,   827,    -1,  1094,   210,  1073,  1031,
      -1,  1094,   210,  1094,   187,  1073,  1031,    -1,  1094,    49,
    1094,   187,  1073,  1031,    -1,  1094,   210,  1094,   187,  1074,
     328,  1074,  1031,    -1,  1094,    49,  1094,   187,  1074,   328,
    1074,  1031,    -1,    -1,   133,    -1,    -1,   149,   829,   236,
     786,    -1,    -1,   161,   831,   832,   834,   844,    -1,   833,
      -1,   832,  1133,   833,    -1,  1059,    -1,   408,    -1,   404,
      -1,   835,   838,    -1,   836,    -1,   835,   836,    -1,    -1,
     840,   837,   757,    -1,    -1,    -1,   440,   839,   757,    -1,
     438,   841,    -1,   840,   438,   841,    -1,   842,    -1,   841,
    1133,   842,    -1,  1060,   843,    -1,    21,    -1,   408,    -1,
     404,    -1,    -1,   400,  1059,    -1,    -1,   134,    -1,    -1,
     165,   846,   847,    -1,    -1,   310,    -1,   297,    -1,   297,
     100,    -1,   356,    -1,   296,    -1,    -1,   179,   849,  1091,
      -1,    -1,   186,   851,  1103,    -1,    -1,   189,  1172,   853,
    1081,   854,    -1,    -1,   114,  1157,  1103,    -1,    -1,   190,
     856,    -1,    -1,    -1,   197,   858,  1058,  1170,   859,   757,
     860,   862,    -1,   197,     1,   136,    -1,    -1,    -1,   125,
     861,   757,    -1,    -1,   136,    -1,    -1,   204,   864,  1091,
     865,   866,   867,   871,    -1,    -1,  1174,   171,    -1,    -1,
       9,  1172,   435,    -1,   870,  1172,   435,    -1,    -1,   331,
     868,    -1,   869,    -1,   868,   869,    -1,   870,  1143,    49,
    1094,    -1,    12,    -1,    15,    -1,   272,    -1,    16,    -1,
     273,    -1,   253,    -1,   254,    -1,    -1,   110,    -1,    -1,
     206,   873,   693,    -1,    -1,   209,   875,   876,   877,    -1,
    1103,    -1,  1109,    -1,  1112,    -1,   878,    -1,   877,   878,
      -1,   879,    -1,   883,    -1,   888,    -1,    -1,   394,   880,
     881,    -1,   882,    -1,   881,   882,    -1,  1098,   175,    -1,
      56,   889,    -1,     9,    -1,   223,    -1,   411,    -1,  1098,
     889,    -1,   331,   884,    -1,   885,    -1,   884,   885,    -1,
      56,    49,  1098,   889,    -1,   886,   887,    -1,    -1,     9,
      -1,   223,    -1,   173,    -1,   411,    -1,  1098,    49,  1099,
     889,    -1,    92,  1098,   403,  1099,   889,    -1,    -1,   889,
    1022,   890,  1094,    -1,    -1,   406,    -1,    -1,   246,   892,
     957,    -1,    -1,   250,   894,   895,    -1,  1094,   403,  1091,
      -1,    94,  1094,   403,  1091,    -1,    -1,   252,   897,   898,
     899,    -1,  1094,    49,  1073,  1031,    -1,  1094,    49,  1094,
     187,  1073,  1031,    -1,    -1,   137,    -1,    -1,   282,   901,
     902,    -1,    -1,   902,   903,   904,  1077,   905,    -1,   207,
      -1,   288,    -1,   215,    -1,   166,    -1,    -1,   366,  1174,
     580,    -1,    -1,  1174,   260,   344,    -1,  1174,   240,    -1,
      -1,   297,   907,   908,    -1,   911,   912,    -1,    -1,   912,
     909,   757,   910,    -1,   912,   138,    -1,    -1,   138,    -1,
    1082,    -1,  1082,   400,  1082,    -1,    -1,   177,    -1,  1101,
     402,    -1,   913,   423,  1058,    -1,   913,   436,   914,    -1,
      -1,  1174,   397,  1022,    -1,   915,    -1,   914,     8,   915,
      -1,  1103,   180,  1094,    49,  1094,   423,  1058,    -1,    -1,
     318,   917,  1078,  1123,  1161,   918,   919,   920,   921,   922,
      -1,    -1,   210,  1103,    -1,    -1,   199,   240,    -1,  1174,
     240,    -1,  1174,   260,   240,    -1,  1174,   198,   240,    -1,
    1174,   437,    -1,    -1,   218,  1148,   693,    -1,    -1,  1041,
      -1,  1052,    -1,    -1,   140,    -1,    -1,   327,   924,  1075,
    1020,    -1,    -1,   340,   926,  1078,  1161,   918,  1041,   927,
      -1,    -1,   141,    -1,    -1,   345,   929,  1075,  1020,   930,
    1051,   931,    -1,    -1,  1174,   240,    -1,  1174,   260,   240,
      -1,    -1,   142,    -1,   347,    -1,    -1,   355,   934,   935,
     943,    -1,  1076,   937,   938,   940,    -1,    -1,     9,  1076,
     938,   438,  1059,   936,   757,    -1,    -1,   436,  1103,    -1,
      -1,    -1,  1137,   126,   939,   757,    -1,   941,    -1,   941,
     940,    -1,    -1,   438,  1058,   942,   757,    -1,    -1,   143,
      -1,    -1,   365,   945,   946,    -1,   947,    -1,   948,    -1,
     949,    -1,   951,    -1,   953,    -1,   150,  1098,   403,  1098,
      -1,  1091,   403,   149,  1097,    -1,  1091,   403,  1094,    -1,
    1091,   950,    49,  1094,    -1,   424,    -1,   121,    -1,   952,
      -1,   951,   952,    -1,  1079,   403,   520,    -1,   954,    -1,
     953,   954,    -1,  1091,   403,   408,    -1,  1091,   403,   404,
      -1,    -1,   374,   956,   957,    -1,    -1,  1105,   959,   961,
     962,   958,   963,   964,    -1,    -1,   959,  1157,   661,  1150,
    1148,   960,    -1,    -1,   960,  1105,    -1,    -1,  1130,  1158,
      -1,    -1,  1131,  1148,  1086,    -1,    -1,   434,  1077,    -1,
     207,   307,  1148,   911,    -1,    -1,   187,  1077,    -1,   288,
     307,  1148,   911,    -1,    -1,    -1,   383,   966,  1078,   967,
     968,  1051,   970,    -1,    -1,   218,  1148,   969,   693,    -1,
    1124,  1064,    -1,  1124,  1065,    -1,  1124,  1066,    -1,  1124,
    1067,    -1,  1124,  1068,    -1,    -1,   144,    -1,    -1,   385,
     349,   972,   974,    -1,    -1,   385,   236,   973,    -1,    -1,
     341,  1094,    -1,   187,  1094,    -1,    -1,   386,   976,   977,
     210,  1103,   979,  1036,   980,    -1,   978,    -1,   977,   978,
      -1,  1094,    -1,   112,  1139,   372,    -1,   112,  1139,  1094,
      -1,    -1,  1174,   300,  1103,    -1,    -1,   145,    -1,    -1,
     389,   982,   983,   984,    -1,  1093,   180,  1073,  1031,    -1,
    1093,   180,  1094,   187,  1073,  1031,    -1,    94,  1103,   180,
    1103,  1126,  1031,    -1,    -1,   146,    -1,   391,   986,    -1,
      -1,   306,    -1,    -1,   396,   988,   693,    -1,    -1,   412,
     990,  1103,   180,  1098,   403,  1099,    -1,    -1,   417,   992,
    1078,   993,    -1,    -1,   319,    -1,   321,    -1,    -1,   422,
     995,  1103,   996,   999,   979,  1003,  1036,  1004,    -1,    -1,
     112,  1139,   997,    -1,   998,    -1,   997,   284,   998,    -1,
    1120,  1098,    -1,   210,  1000,    -1,   999,  1000,    -1,  1103,
    1001,  1002,    -1,    -1,   113,  1147,  1103,    -1,    -1,    95,
    1147,  1103,    -1,    -1,   394,  1147,  1103,    -1,    -1,   147,
      -1,  1006,    -1,  1015,    -1,  1017,    -1,   433,  1007,  1009,
    1010,  1011,  1014,  1157,  1008,    -1,    -1,   188,    -1,  1077,
      -1,   207,    -1,   288,    -1,   215,    -1,   166,    -1,    -1,
       8,    -1,    -1,   380,    -1,   163,    -1,   159,    -1,   163,
      -1,   289,    -1,   265,    -1,   267,    -1,    -1,   307,    -1,
     433,  1145,   107,  1157,  1016,    -1,  1082,    -1,     9,   308,
      -1,   433,  1007,    35,   333,  1103,    -1,    -1,   445,  1019,
    1075,  1020,   930,  1021,  1023,  1024,    -1,    -1,   180,  1100,
      -1,    -1,  1022,  1132,  1102,  1151,    -1,  1022,  1132,  1080,
      -1,  1022,  1132,   293,    -1,    35,    -1,     8,    -1,    -1,
    1046,    -1,  1052,    -1,    -1,   148,    -1,  1027,  1029,    -1,
    1027,  1029,    -1,    -1,    -1,   163,  1028,   757,    -1,    -1,
      -1,   265,  1030,   757,    -1,  1032,  1034,    -1,    -1,    -1,
     373,  1033,   757,    -1,    -1,    -1,   268,  1035,   757,    -1,
    1037,  1039,    -1,    -1,    -1,   289,  1038,   757,    -1,    -1,
      -1,   267,  1040,   757,    -1,  1042,    -1,  1044,    -1,  1042,
    1044,    -1,    -1,   126,  1043,   757,    -1,    -1,   263,  1045,
     757,    -1,  1047,    -1,  1049,    -1,  1047,  1049,    -1,    -1,
     154,  1048,   757,    -1,    -1,   264,  1050,   757,    -1,    -1,
    1052,    -1,  1053,    -1,  1055,    -1,  1053,  1055,    -1,    -1,
     213,  1054,   757,    -1,    -1,   266,  1056,   757,    -1,    -1,
    1139,  1102,  1151,    -1,  1059,    -1,  1060,    -1,    -1,  1061,
    1062,    -1,  1063,  1094,    -1,  1062,   457,    -1,  1063,   279,
      -1,  1063,   272,    -1,  1063,    12,    -1,  1063,    13,    -1,
    1063,    14,    -1,  1063,    58,    -1,  1062,   279,    -1,  1062,
     272,    -1,  1062,    12,    -1,  1062,    13,    -1,  1062,    14,
      -1,  1062,    58,    -1,  1063,   302,    -1,  1063,   257,    -1,
    1062,   302,    -1,  1062,   257,    -1,  1062,   448,    -1,    -1,
    1062,   214,    -1,  1063,   214,    -1,  1063,   458,    -1,  1063,
     449,    -1,  1063,   450,    -1,  1063,   454,    -1,  1063,   262,
      -1,  1062,   262,    -1,  1062,   449,    -1,  1062,   450,    -1,
    1062,   451,    -1,  1062,   452,    -1,  1062,   454,    -1,  1062,
    1064,    -1,  1062,  1065,    -1,  1062,  1066,    -1,  1062,  1067,
      -1,  1062,  1068,    -1,  1062,   256,    -1,  1063,  1064,    -1,
    1063,  1065,    -1,  1063,  1066,    -1,  1063,  1067,    -1,  1063,
    1068,    -1,  1063,   256,    -1,  1062,    20,    -1,  1062,   284,
      -1,   456,    -1,   156,  1172,    -1,   157,    -1,   459,    -1,
     191,  1169,    -1,   460,    -1,   226,  1169,    -1,   185,    -1,
     191,  1169,   284,   156,  1172,    -1,   191,  1169,   156,  1172,
      -1,   222,    -1,   226,  1169,   284,   156,  1172,    -1,   226,
    1169,   156,  1172,    -1,  1071,    -1,  1069,  1070,  1071,    -1,
      -1,    70,    -1,   360,    -1,  1095,    -1,  1071,   449,  1071,
      -1,  1071,   450,  1071,    -1,  1071,   451,  1071,    -1,  1071,
     452,  1071,    -1,   449,  1071,    -1,   450,  1071,    -1,  1071,
     454,  1071,    -1,   458,  1071,   457,    -1,   232,    -1,   232,
    1128,   442,    -1,  1074,    -1,  1073,  1074,    -1,  1094,  1126,
      -1,  1105,    -1,  1105,    -1,  1078,    -1,  1077,  1078,    -1,
     442,    -1,  1080,    -1,  1079,  1080,    -1,   248,    -1,    -1,
    1081,  1082,    -1,  1083,    -1,  1105,    -1,  1084,    -1,  1084,
    1128,  1084,    -1,   236,    -1,  1086,    -1,  1085,  1086,    -1,
    1105,    -1,  1105,    -1,  1087,  1105,    -1,    -1,  1086,    -1,
    1086,    -1,   236,    -1,   442,    -1,  1092,    -1,  1091,  1092,
      -1,  1103,    -1,     6,  1156,  1104,    -1,  1094,    -1,  1093,
    1094,    -1,  1103,    -1,   225,  1156,  1104,    -1,   225,  1156,
    1110,    -1,   225,  1156,  1112,    -1,     6,  1156,  1096,  1097,
      -1,     6,  1156,  1104,    -1,  1109,    -1,  1112,    -1,  1072,
      -1,  1103,    -1,   225,  1156,  1104,    -1,   225,  1156,  1110,
      -1,   225,  1156,  1112,    -1,  1110,    -1,  1112,    -1,  1072,
      -1,   310,    -1,   149,    -1,  1104,    -1,   236,    -1,  1103,
      -1,  1110,    -1,  1103,    -1,  1109,    -1,  1103,    -1,   236,
      -1,  1103,    -1,   236,    -1,  1112,    -1,  1103,    -1,  1108,
      -1,   448,    -1,  1104,    -1,  1105,    -1,  1105,  1106,    -1,
    1105,  1107,    -1,  1105,  1106,  1107,    -1,   442,    -1,   442,
    1128,  1105,    -1,   458,  1069,   457,    -1,   458,  1071,   461,
     457,    -1,   458,  1071,   461,  1071,   457,    -1,   236,    -1,
    1110,    -1,     9,  1111,    -1,  1111,    -1,  1110,   462,  1111,
      -1,   236,    -1,   378,    -1,   448,    -1,   315,    -1,   195,
      -1,   243,    -1,   407,    -1,    98,  1113,    -1,   439,  1113,
      -1,   431,   458,  1071,   457,  1113,    -1,   241,   458,  1071,
     457,  1113,    -1,   342,   458,  1071,   457,  1113,    -1,    82,
     458,  1069,   457,  1113,    -1,   387,   458,  1069,   457,  1113,
      -1,   388,   458,  1069,   457,  1113,    -1,   413,   458,  1116,
     457,  1113,    -1,   274,   458,  1117,   457,    -1,   238,   458,
    1118,   457,  1113,    -1,   184,  1114,    -1,    -1,   458,  1071,
     461,   457,    -1,   458,  1071,   461,  1071,   457,    -1,    -1,
     458,  1115,   457,    -1,    -1,  1069,    -1,  1071,    -1,  1071,
    1070,   223,    -1,  1071,  1070,   411,    -1,  1071,    -1,  1071,
    1070,  1071,    -1,  1071,    -1,  1071,  1070,  1086,    -1,    -1,
      -1,     9,    -1,    -1,  1130,    -1,    -1,   205,    -1,    -1,
     258,    -1,   304,    -1,    -1,   262,    -1,    -1,   283,    -1,
      -1,   348,    -1,    -1,   362,  1140,    -1,   200,    -1,   277,
      -1,   319,  1148,    -1,   321,  1134,    -1,   441,   122,    -1,
     122,    -1,    63,   363,    -1,   363,    -1,    -1,     7,    -1,
      -1,    17,    -1,    -1,    23,    -1,    -1,    24,    -1,    -1,
      27,    -1,    -1,    30,    -1,    -1,    37,    -1,    -1,    49,
      -1,    -1,    55,    -1,    -1,    56,    -1,    -1,    85,    -1,
      -1,   102,    -1,    -1,   405,    -1,    -1,   175,    -1,    -1,
     180,    -1,    -1,   200,    -1,    -1,   214,    -1,    -1,   214,
      -1,    23,    -1,    -1,   218,    -1,    -1,   233,    -1,   234,
      -1,    -1,   234,    -1,    -1,   236,    -1,    -1,   249,    -1,
      -1,   270,    -1,    -1,   277,    -1,    -1,   280,    -1,    -1,
     285,    -1,   200,   285,    -1,    -1,   287,    -1,    -1,   310,
      -1,    -1,   319,    -1,    -1,   346,    -1,    -1,   365,    -1,
      -1,   367,    -1,    -1,   367,    -1,   367,   214,    -1,    -1,
     372,    -1,    -1,   384,    -1,    -1,   395,    -1,    -1,   398,
      -1,    -1,   399,    -1,    -1,   402,    -1,    -1,   403,    -1,
      -1,   438,    -1,    -1,   441,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   771,   771,   771,   815,   816,   820,   821,   826,   827,
     825,   835,   836,   834,   844,   845,   843,   850,   851,   852,
     855,   856,   884,   910,   942,   941,   982,  1026,  1027,  1031,
    1032,  1035,  1036,  1040,  1047,  1054,  1058,  1062,  1074,  1075,
    1085,  1086,  1095,  1096,  1100,  1101,  1102,  1103,  1112,  1115,
    1116,  1117,  1118,  1122,  1129,  1138,  1141,  1142,  1143,  1144,
    1148,  1149,  1153,  1154,  1155,  1159,  1166,  1167,  1171,  1178,
    1190,  1193,  1194,  1198,  1199,  1203,  1207,  1214,  1215,  1225,
    1228,  1229,  1230,  1234,  1235,  1239,  1240,  1241,  1242,  1243,
    1244,  1245,  1246,  1247,  1248,  1249,  1256,  1267,  1266,  1278,
    1277,  1286,  1300,  1314,  1328,  1344,  1345,  1349,  1350,  1354,
    1365,  1366,  1374,  1373,  1385,  1386,  1387,  1388,  1389,  1397,
    1398,  1403,  1404,  1406,  1405,  1417,  1418,  1422,  1423,  1424,
    1425,  1426,  1427,  1431,  1432,  1433,  1434,  1435,  1436,  1443,
    1454,  1466,  1467,  1471,  1472,  1479,  1488,  1489,  1493,  1494,
    1508,  1523,  1590,  1601,  1608,  1615,  1621,  1628,  1629,  1633,
    1632,  1642,  1641,  1657,  1658,  1661,  1662,  1667,  1666,  1687,
    1688,  1692,  1693,  1694,  1695,  1696,  1697,  1698,  1699,  1700,
    1701,  1702,  1703,  1704,  1705,  1706,  1713,  1717,  1722,  1729,
    1730,  1731,  1734,  1735,  1739,  1746,  1747,  1754,  1774,  1775,
    1781,  1785,  1786,  1787,  1794,  1814,  1861,  1861,  1865,  1869,
    1885,  1886,  1887,  1893,  1903,  1912,  1914,  1915,  1921,  1925,
    1926,  1927,  1930,  1931,  1932,  1936,  1940,  1941,  1947,  1948,
    1952,  1961,  1970,  1979,  1988,  2003,  2013,  2020,  2024,  2062,
    2069,  2070,  2077,  2081,  2082,  2083,  2089,  2096,  2097,  2100,
    2101,  2102,  2103,  2107,  2108,  2112,  2113,  2119,  2144,  2145,
    2146,  2147,  2153,  2160,  2161,  2165,  2168,  2169,  2175,  2176,
    2177,  2181,  2185,  2189,  2193,  2197,  2207,  2208,  2222,  2223,
    2223,  2226,  2225,  2238,  2239,  2243,  2255,  2264,  2268,  2269,
    2279,  2278,  2296,  2297,  2301,  2308,  2315,  2316,  2317,  2318,
    2319,  2320,  2321,  2322,  2323,  2324,  2331,  2335,  2335,  2335,
    2341,  2353,  2378,  2402,  2403,  2410,  2411,  2415,  2416,  2423,
    2430,  2431,  2438,  2442,  2451,  2452,  2458,  2468,  2486,  2487,
    2491,  2492,  2493,  2497,  2504,  2511,  2521,  2528,  2546,  2550,
    2561,  2562,  2562,  2573,  2574,  2578,  2578,  2595,  2596,  2598,
    2602,  2604,  2603,  2628,  2627,  2652,  2656,  2663,  2665,  2687,
    2692,  2698,  2707,  2715,  2716,  2724,  2725,  2726,  2730,  2750,
    2754,  2763,  2764,  2765,  2766,  2767,  2768,  2769,  2770,  2771,
    2772,  2773,  2774,  2775,  2776,  2777,  2784,  2806,  2828,  2829,
    2841,  2861,  2868,  2869,  2873,  2874,  2875,  2876,  2877,  2878,
    2879,  2880,  2881,  2882,  2883,  2884,  2889,  2894,  2895,  2896,
    2897,  2898,  2899,  2900,  2901,  2902,  2903,  2904,  2905,  2906,
    2907,  2908,  2909,  2910,  2911,  2912,  2920,  2928,  2936,  2943,
    2948,  2958,  2959,  2960,  2964,  2981,  2982,  2985,  2986,  2992,
    2992,  2995,  3019,  3035,  3036,  3040,  3041,  3044,  3044,  3047,
    3054,  3055,  3060,  3070,  3077,  3080,  3081,  3082,  3089,  3096,
    3121,  3125,  3125,  3130,  3131,  3135,  3136,  3139,  3140,  3153,
    3165,  3185,  3199,  3201,  3200,  3220,  3221,  3221,  3234,  3236,
    3235,  3247,  3248,  3252,  3253,  3262,  3269,  3272,  3276,  3280,
    3281,  3282,  3289,  3290,  3294,  3297,  3297,  3300,  3301,  3307,
    3312,  3313,  3316,  3317,  3320,  3321,  3324,  3325,  3328,  3329,
    3333,  3334,  3335,  3339,  3340,  3343,  3344,  3348,  3352,  3353,
    3357,  3358,  3359,  3360,  3361,  3362,  3363,  3364,  3365,  3366,
    3367,  3368,  3369,  3370,  3371,  3372,  3376,  3380,  3381,  3382,
    3383,  3384,  3385,  3386,  3390,  3394,  3395,  3396,  3400,  3401,
    3405,  3409,  3414,  3418,  3422,  3426,  3427,  3431,  3432,  3436,
    3437,  3438,  3441,  3441,  3441,  3444,  3448,  3451,  3451,  3454,
    3461,  3462,  3463,  3462,  3480,  3481,  3485,  3486,  3491,  3493,
    3492,  3528,  3529,  3533,  3534,  3535,  3536,  3537,  3538,  3539,
    3540,  3541,  3542,  3543,  3544,  3545,  3546,  3547,  3548,  3549,
    3553,  3557,  3561,  3565,  3566,  3567,  3568,  3569,  3570,  3571,
    3572,  3579,  3583,  3593,  3596,  3600,  3604,  3608,  3616,  3619,
    3623,  3627,  3631,  3639,  3652,  3654,  3664,  3653,  3691,  3693,
    3692,  3699,  3698,  3707,  3708,  3713,  3720,  3722,  3726,  3736,
    3738,  3746,  3754,  3783,  3814,  3816,  3826,  3831,  3842,  3843,
    3843,  3870,  3871,  3875,  3876,  3877,  3878,  3894,  3906,  3937,
    3974,  3986,  3989,  3990,  3999,  4003,  3999,  4016,  4034,  4038,
    4039,  4040,  4041,  4042,  4043,  4044,  4045,  4046,  4047,  4048,
    4049,  4050,  4051,  4052,  4053,  4054,  4055,  4056,  4057,  4058,
    4059,  4060,  4061,  4062,  4063,  4064,  4065,  4066,  4067,  4068,
    4069,  4070,  4071,  4072,  4073,  4074,  4075,  4076,  4077,  4078,
    4079,  4080,  4081,  4082,  4083,  4084,  4085,  4086,  4087,  4110,
    4109,  4122,  4126,  4130,  4134,  4138,  4142,  4146,  4150,  4154,
    4158,  4162,  4166,  4170,  4174,  4178,  4182,  4186,  4193,  4194,
    4195,  4196,  4197,  4198,  4202,  4206,  4207,  4210,  4211,  4215,
    4216,  4220,  4221,  4222,  4223,  4224,  4225,  4226,  4227,  4231,
    4235,  4239,  4244,  4245,  4246,  4247,  4248,  4249,  4253,  4254,
    4263,  4263,  4269,  4273,  4277,  4283,  4284,  4288,  4289,  4298,
    4298,  4303,  4307,  4314,  4315,  4324,  4330,  4331,  4335,  4335,
    4343,  4343,  4353,  4355,  4354,  4363,  4364,  4369,  4376,  4383,
    4385,  4389,  4397,  4408,  4409,  4410,  4415,  4419,  4418,  4430,
    4434,  4433,  4444,  4445,  4454,  4454,  4458,  4459,  4463,  4475,
    4475,  4479,  4480,  4491,  4492,  4493,  4494,  4495,  4498,  4498,
    4506,  4506,  4512,  4519,  4520,  4523,  4523,  4530,  4543,  4556,
    4556,  4567,  4568,  4577,  4577,  4597,  4596,  4609,  4613,  4617,
    4621,  4625,  4629,  4633,  4638,  4642,  4649,  4650,  4651,  4655,
    4656,  4661,  4662,  4663,  4664,  4665,  4666,  4667,  4668,  4669,
    4670,  4674,  4678,  4682,  4687,  4688,  4692,  4693,  4702,  4702,
    4708,  4712,  4716,  4720,  4724,  4731,  4732,  4741,  4741,  4763,
    4762,  4781,  4782,  4793,  4802,  4807,  4815,  4844,  4845,  4851,
    4850,  4866,  4870,  4869,  4884,  4885,  4890,  4891,  4902,  4931,
    4932,  4933,  4936,  4937,  4941,  4942,  4951,  4951,  4956,  4957,
    4965,  4982,  4999,  5017,  5042,  5042,  5055,  5055,  5068,  5068,
    5077,  5081,  5094,  5094,  5107,  5109,  5107,  5120,  5125,  5129,
    5128,  5142,  5143,  5152,  5152,  5160,  5161,  5165,  5166,  5167,
    5171,  5172,  5177,  5178,  5183,  5187,  5188,  5189,  5190,  5191,
    5192,  5193,  5197,  5198,  5207,  5207,  5220,  5219,  5229,  5230,
    5231,  5235,  5236,  5240,  5241,  5242,  5248,  5248,  5253,  5254,
    5258,  5259,  5260,  5261,  5262,  5263,  5269,  5273,  5274,  5278,
    5283,  5287,  5288,  5289,  5290,  5291,  5295,  5321,  5334,  5335,
    5339,  5339,  5347,  5347,  5357,  5357,  5362,  5366,  5378,  5378,
    5384,  5388,  5395,  5396,  5405,  5405,  5409,  5410,  5424,  5425,
    5426,  5427,  5431,  5432,  5436,  5437,  5438,  5450,  5450,  5455,
    5460,  5459,  5469,  5476,  5477,  5481,  5486,  5495,  5498,  5502,
    5507,  5514,  5521,  5522,  5526,  5527,  5532,  5544,  5544,  5573,
    5574,  5578,  5579,  5583,  5587,  5591,  5595,  5602,  5603,  5617,
    5618,  5619,  5623,  5624,  5633,  5633,  5648,  5648,  5659,  5660,
    5669,  5669,  5686,  5687,  5691,  5698,  5699,  5708,  5721,  5721,
    5727,  5732,  5731,  5742,  5743,  5747,  5749,  5748,  5759,  5760,
    5765,  5764,  5775,  5776,  5785,  5785,  5790,  5791,  5792,  5793,
    5794,  5800,  5809,  5813,  5822,  5829,  5830,  5836,  5837,  5841,
    5850,  5851,  5855,  5859,  5871,  5871,  5877,  5876,  5893,  5896,
    5917,  5918,  5921,  5922,  5926,  5927,  5932,  5937,  5945,  5957,
    5962,  5970,  5986,  5987,  5986,  6007,  6008,  6024,  6025,  6026,
    6027,  6028,  6032,  6033,  6042,  6042,  6047,  6047,  6054,  6055,
    6056,  6065,  6065,  6074,  6075,  6079,  6080,  6081,  6085,  6086,
    6090,  6091,  6100,  6100,  6106,  6110,  6114,  6121,  6122,  6131,
    6138,  6139,  6147,  6147,  6160,  6160,  6176,  6176,  6185,  6187,
    6188,  6197,  6197,  6207,  6208,  6213,  6214,  6219,  6226,  6227,
    6232,  6239,  6240,  6244,  6245,  6249,  6250,  6254,  6255,  6264,
    6265,  6266,  6270,  6294,  6297,  6305,  6315,  6320,  6325,  6330,
    6337,  6338,  6341,  6342,  6346,  6346,  6350,  6350,  6354,  6354,
    6357,  6358,  6362,  6369,  6370,  6374,  6386,  6386,  6403,  6404,
    6409,  6412,  6416,  6420,  6427,  6428,  6431,  6432,  6433,  6437,
    6438,  6451,  6459,  6466,  6468,  6467,  6477,  6479,  6478,  6493,
    6497,  6499,  6498,  6509,  6511,  6510,  6527,  6533,  6535,  6534,
    6544,  6546,  6545,  6561,  6566,  6571,  6581,  6580,  6592,  6591,
    6607,  6612,  6617,  6627,  6626,  6638,  6637,  6652,  6653,  6657,
    6662,  6667,  6677,  6676,  6688,  6687,  6704,  6707,  6719,  6726,
    6733,  6733,  6743,  6744,  6746,  6747,  6748,  6749,  6750,  6751,
    6753,  6754,  6755,  6756,  6757,  6758,  6760,  6761,  6763,  6764,
    6765,  6768,  6770,  6771,  6772,  6774,  6775,  6776,  6778,  6779,
    6781,  6782,  6783,  6784,  6785,  6787,  6788,  6789,  6790,  6791,
    6792,  6794,  6795,  6796,  6797,  6798,  6799,  6801,  6802,  6805,
    6805,  6805,  6806,  6806,  6807,  6807,  6808,  6808,  6808,  6809,
    6809,  6809,  6814,  6815,  6818,  6819,  6820,  6824,  6825,  6826,
    6827,  6828,  6829,  6830,  6831,  6832,  6843,  6855,  6870,  6871,
    6876,  6882,  6904,  6924,  6928,  6944,  6958,  6959,  6964,  6970,
    6971,  6976,  6985,  6986,  6987,  6991,  7002,  7003,  7007,  7017,
    7018,  7022,  7023,  7027,  7028,  7034,  7054,  7055,  7059,  7060,
    7064,  7065,  7069,  7070,  7071,  7072,  7073,  7074,  7075,  7076,
    7077,  7081,  7082,  7083,  7084,  7085,  7086,  7087,  7091,  7092,
    7096,  7097,  7101,  7102,  7106,  7107,  7118,  7119,  7123,  7124,
    7125,  7129,  7130,  7131,  7139,  7143,  7144,  7145,  7146,  7150,
    7151,  7155,  7165,  7183,  7210,  7222,  7223,  7233,  7234,  7238,
    7239,  7240,  7241,  7242,  7243,  7244,  7252,  7256,  7260,  7264,
    7268,  7272,  7276,  7280,  7284,  7288,  7292,  7296,  7303,  7304,
    7305,  7309,  7310,  7314,  7315,  7320,  7327,  7334,  7344,  7351,
    7361,  7368,  7382,  7392,  7393,  7397,  7398,  7402,  7403,  7407,
    7408,  7409,  7413,  7414,  7418,  7419,  7423,  7424,  7428,  7429,
    7436,  7436,  7437,  7437,  7438,  7438,  7439,  7439,  7441,  7441,
    7442,  7442,  7443,  7443,  7444,  7444,  7445,  7445,  7446,  7446,
    7447,  7447,  7448,  7448,  7449,  7449,  7450,  7450,  7451,  7451,
    7452,  7452,  7453,  7453,  7454,  7454,  7455,  7455,  7456,  7456,
    7457,  7457,  7458,  7458,  7458,  7459,  7459,  7460,  7460,  7460,
    7461,  7461,  7462,  7462,  7463,  7463,  7464,  7464,  7465,  7465,
    7466,  7466,  7467,  7467,  7467,  7468,  7468,  7469,  7469,  7470,
    7470,  7471,  7471,  7472,  7472,  7473,  7473,  7474,  7474,  7474,
    7475,  7475,  7476,  7476,  7477,  7477,  7478,  7478,  7479,  7479,
    7480,  7480,  7481,  7481,  7483,  7483,  7484,  7484
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "ACCEPT", "ACCESS", "ADD",
  "ADDRESS", "ADVANCING", "AFTER", "ALL", "ALLOCATE", "ALPHABET",
  "ALPHABETIC", "\"ALPHABETIC-LOWER\"", "\"ALPHABETIC-UPPER\"",
  "ALPHANUMERIC", "\"ALPHANUMERIC-EDITED\"", "ALSO", "ALTER", "ALTERNATE",
  "AND", "ANY", "APPLY", "ARE", "AREA", "\"ARGUMENT-NUMBER\"",
  "\"ARGUMENT-VALUE\"", "AS", "ASCENDING", "ASSIGN", "AT", "AUTO",
  "AUTOMATIC", "\"BACKGROUND-COLOR\"", "BASED", "BEFORE", "BELL", "BINARY",
  "\"BINARY-C-LONG\"", "\"BINARY-CHAR\"", "\"BINARY-DOUBLE\"",
  "\"BINARY-LONG\"", "\"BINARY-SHORT\"", "BLANK", "\"BLANK-LINE\"",
  "\"BLANK-SCREEN\"", "BLINK", "BLOCK", "BOTTOM", "BY", "\"BYTE-LENGTH\"",
  "CALL", "CANCEL", "CH", "CHAINING", "CHARACTER", "CHARACTERS", "CLASS",
  "CLASS_NAME", "CLOSE", "\"CLOSE-NOFEED\"", "CODE", "\"CODE-SET\"",
  "COLLATING", "COL", "COLS", "COLUMN", "COLUMNS", "COMMA",
  "\"COMMAND-LINE\"", "\"comma delimiter\"", "COMMIT",
  "\"COMMITMENT-CONTROL\"", "COMMON", "COMP", "COMPUTE", "\"COMP-1\"",
  "\"COMP-2\"", "\"COMP-3\"", "\"COMP-4\"", "\"COMP-5\"", "\"COMP-X\"",
  "\"FUNCTION CONCATENATE\"", "CONFIGURATION", "CONSTANT", "CONTAINS",
  "CONTENT", "CONTINUE", "CONTROL", "CONTROLS", "\"CONTROL FOOTING\"",
  "\"CONTROL HEADING\"", "CONVERTING", "\"CORE-INDEX\"", "CORRESPONDING",
  "COUNT", "CRT", "CURRENCY", "\"FUNCTION CURRENT-DATE\"", "CURSOR",
  "CYCLE", "\"CYL-OVERFLOW\"", "DATA", "DATE", "DAY", "\"DAY-OF-WEEK\"",
  "DE", "DEBUGGING", "\"DECIMAL-POINT\"", "DECLARATIVES", "DEFAULT",
  "DELETE", "DELIMITED", "DELIMITER", "DEPENDING", "DESCENDING", "DETAIL",
  "DISK", "DISPLAY", "DIVIDE", "DIVISION", "DOWN", "DUPLICATES", "DYNAMIC",
  "EBCDIC", "ELSE", "END", "\"END-ACCEPT\"", "\"END-ADD\"", "\"END-CALL\"",
  "\"END-COMPUTE\"", "\"END-DELETE\"", "\"END-DISPLAY\"", "\"END-DIVIDE\"",
  "\"END-EVALUATE\"", "\"END FUNCTION\"", "\"END-IF\"", "\"END-MULTIPLY\"",
  "\"END-PERFORM\"", "\"END PROGRAM\"", "\"END-READ\"", "\"END-RETURN\"",
  "\"END-REWRITE\"", "\"END-SEARCH\"", "\"END-START\"", "\"END-STRING\"",
  "\"END-SUBTRACT\"", "\"END-UNSTRING\"", "\"END-WRITE\"", "ENTRY",
  "ENVIRONMENT", "\"ENVIRONMENT-NAME\"", "\"ENVIRONMENT-VALUE\"", "EOL",
  "EOP", "EOS", "EQUAL", "EQUALS", "ERASE", "ERROR", "ESCAPE", "EVALUATE",
  "\"EVENT-STATUS\"", "EXCEPTION", "EXCLUSIVE", "EXIT", "EXTEND",
  "EXTERNAL", "FD", "\"FILE-CONTROL\"", "\"FILE-ID\"", "FILLER", "FINAL",
  "FIRST", "FOOTING", "FOR", "\"FOREGROUND-COLOR\"", "FOREVER",
  "\"FORMS-OVERLAY\"", "FREE", "FROM", "FULL", "FUNCTION",
  "\"FUNCTION-ID\"", "\"FUNCTION\"", "GE", "GENERATE", "GIVING", "GLOBAL",
  "GO", "GOBACK", "GREATER", "GROUP", "HEADING", "HIGHLIGHT",
  "\"HIGH-VALUE\"", "IDENTIFICATION", "IF", "IGNORE", "IGNORING", "IN",
  "INDEX", "INDEXED", "INDICATE", "INITIALIZE", "INITIALIZED", "INITIATE",
  "INPUT", "\"INPUT-OUTPUT\"", "INSPECT", "INTO", "INTRINSIC", "INVALID",
  "\"INVALID KEY\"", "IS", "\"I-O\"", "\"I-O-CONTROL\"", "JUSTIFIED",
  "KEY", "LABEL", "LAST", "\"LAST DETAIL\"", "LE", "LEADING", "LEFT",
  "LENGTH", "LESS", "LEVEL_NUMBER_WORD", "LEVEL88_NUMBER_WORD", "LIMIT",
  "LIMITS", "LINAGE", "\"LINAGE-COUNTER\"", "LINE", "LINES", "LINKAGE",
  "\"Literal\"", "LOCALE", "\"FUNCTION LOCALE\"", "\"LOCAL-STORAGE\"",
  "LOCK", "\"FUNCTION LOWER-CASE\"", "LOWLIGHT", "\"LOW-VALUE\"", "MANUAL",
  "MEMORY", "MERGE", "MINUS", "\"MNEMONIC NAME\"", "MODE", "MOVE",
  "MULTIPLE", "MULTIPLY", "NATIONAL", "\"NATIONAL-EDITED\"", "NATIVE",
  "NE", "NEGATIVE", "NEXT", "\"NEXT SENTENCE\"", "NO", "NOMINAL", "NOT",
  "\"NOT END\"", "\"NOT EOP\"", "\"NOT EXCEPTION\"", "\"NOT INVALID KEY\"",
  "\"NOT OVERFLOW\"", "\"NOT SIZE ERROR\"", "\"NO ADVANCING\"", "NUMBER",
  "NUMBERS", "NUMERIC", "\"NUMERIC-EDITED\"", "\"FUNCTION NUMVALC\"",
  "\"OBJECT-COMPUTER\"", "OCCURS", "OF", "OFF", "OMITTED", "ON", "ONLY",
  "OPEN", "OPTIONAL", "OR", "ORDER", "ORGANIZATION", "OTHER", "OUTPUT",
  "OVERFLOW", "OVERLINE", "\"PACKED-DECIMAL\"", "PADDING", "PAGE",
  "\"PAGE FOOTING\"", "\"PAGE HEADING\"", "PARAGRAPH", "PERFORM",
  "PICTURE", "PLUS", "POINTER", "POSITION", "POSITIVE", "PRESENT",
  "PREVIOUS", "PRINTER", "PRINTING", "PROCEDURE", "PROCEDURES", "PROCEED",
  "PROGRAM", "\"PROGRAM-ID\"", "\"Program name\"", "\"PROGRAM-POINTER\"",
  "PROMPT", "QUOTE", "RANDOM", "RD", "READ", "RECORD", "RECORDING",
  "RECORDS", "RECURSIVE", "REDEFINES", "REEL", "REFERENCE", "RELATIVE",
  "RELEASE", "REMAINDER", "REMOVAL", "RENAMES", "REPLACING", "REPORT",
  "REPORTING", "REPORTS", "\"REPORT FOOTING\"", "\"REPORT HEADING\"",
  "REPOSITORY", "REQUIRED", "RESERVE", "RETURN", "RETURNING",
  "\"FUNCTION REVERSE\"", "\"REVERSE-VIDEO\"", "REWIND", "REWRITE",
  "RIGHT", "ROLLBACK", "ROUNDED", "RUN", "SAME", "SCREEN",
  "\"SCREEN-CONTROL\"", "SCROLL", "SD", "SEARCH", "SECTION", "SECURE",
  "\"SEGMENT-LIMIT\"", "SELECT", "\"semi-colon\"", "SENTENCE", "SEPARATE",
  "SEQUENCE", "SEQUENTIAL", "SET", "SHARING", "SIGN", "SIGNED",
  "\"SIGNED-INT\"", "\"SIGNED-LONG\"", "\"SIGNED-SHORT\"", "SIZE",
  "\"SIZE ERROR\"", "SORT", "\"SORT-MERGE\"", "SOURCE",
  "\"SOURCE-COMPUTER\"", "SPACE", "\"SPECIAL-NAMES\"", "STANDARD",
  "\"STANDARD-1\"", "\"STANDARD-2\"", "START", "STATUS", "STOP", "STRING",
  "\"FUNCTION SUBSTITUTE\"", "\"FUNCTION SUBSTITUTE-CASE\"", "SUBTRACT",
  "SUM", "SUPPRESS", "SYMBOLIC", "SYNCHRONIZED", "TALLYING", "TAPE",
  "TERMINATE", "TEST", "THAN", "THEN", "THRU", "TIME", "TIMES", "TO",
  "\"FALSE\"", "\"FILE\"", "\"INITIAL\"", "\"NULL\"", "\"TRUE\"", "TOP",
  "TRACKS", "TRAILING", "TRANSFORM", "\"FUNCTION TRIM\"", "TYPE",
  "UNDERLINE", "UNIT", "UNLOCK", "UNSIGNED", "\"UNSIGNED-INT\"",
  "\"UNSIGNED-LONG\"", "\"UNSIGNED-SHORT\"", "UNSTRING", "UNTIL", "UP",
  "UPDATE", "UPON", "\"UPON ARGUMENT-NUMBER\"", "\"UPON COMMAND-LINE\"",
  "\"UPON ENVIRONMENT-NAME\"", "\"UPON ENVIRONMENT-VALUE\"",
  "\"FUNCTION UPPER-CASE\"", "USAGE", "USE", "USING", "VALUE", "VARYING",
  "WAIT", "WHEN", "\"FUNCTION WHEN-COMPILED\"", "\"WHEN OTHER\"", "WITH",
  "\"Identifier\"", "WORDS", "\"WORKING-STORAGE\"", "WRITE", "YYYYDDD",
  "YYYYMMDD", "ZERO", "'+'", "'-'", "'*'", "'/'", "UNARY_SIGN", "'^'",
  "'.'", "'='", "')'", "'('", "'>'", "'<'", "':'", "'&'", "$accept",
  "start", "$@1", "nested_list", "source_element", "program_definition",
  "$@2", "$@3", "program_mandatory", "$@4", "$@5", "function_definition",
  "$@6", "$@7", "nested_prog", "end_program", "end_mandatory",
  "end_function", "identification_division", "$@8", "function_division",
  "program_name", "as_literal", "program_type", "program_type_clause",
  "_init_or_recurs", "environment_division", "configuration_section",
  "configuration_list", "configuration_paragraph",
  "source_computer_paragraph", "source_computer_entry",
  "with_debugging_mode", "computer_name", "object_computer_paragraph",
  "object_computer_entry", "object_clauses_list", "object_clauses",
  "object_computer_memory", "object_char_or_word",
  "object_computer_sequence", "object_computer_segment",
  "repository_paragraph", "opt_repository", "repository_list",
  "repository_name", "repository_literal_list", "special_names_paragraph",
  "opt_special_names", "special_name_list", "special_name",
  "mnemonic_name_clause", "$@9", "$@10",
  "special_name_mnemonic_on_off_list",
  "special_name_mnemonic_on_off_list_mandatory",
  "special_name_mnemonic_on_off", "on_or_off", "alphabet_name_clause",
  "$@11", "alphabet_definition", "alphabet_literal_list",
  "alphabet_literal", "@12", "alphabet_also_sequence", "alphabet_lits",
  "alphabet_also_literal", "symbolic_characters_clause",
  "symbolic_characters_list", "char_list", "integer_list",
  "class_name_clause", "class_item_list", "class_item", "locale_clause",
  "currency_sign_clause", "decimal_point_clause", "cursor_clause",
  "crt_status_clause", "screen_control", "event_status",
  "input_output_section", "$@13", "$@14", "file_control_paragraph",
  "file_control_sequence", "file_control_entry", "$@15",
  "select_clause_sequence", "select_clause", "assign_clause", "_device",
  "_ext_clause", "assignment_name", "assignment_device_name_list",
  "access_mode_clause", "access_mode", "alternative_record_key_clause",
  "split_key_list", "$@16", "split_key", "key_is_eq",
  "collating_sequence_clause", "file_status_clause", "file_or_sort",
  "lock_mode_clause", "lock_mode", "lock_with", "lock_records",
  "organization_clause", "organization", "padding_character_clause",
  "record_delimiter_clause", "record_key_clause", "relative_key_clause",
  "reserve_clause", "sharing_clause", "sharing_option",
  "nominal_key_clause", "i_o_control_paragraph", "opt_i_o_control",
  "i_o_control_list", "i_o_control_clause", "same_clause", "same_option",
  "multiple_file_tape_clause", "multiple_file_list", "multiple_file",
  "multiple_file_position", "apply_clause_list", "apply_clause",
  "data_division", "file_section", "$@17", "$@18",
  "file_description_sequence", "file_description",
  "file_description_sequence_without_type", "file_type",
  "file_description_entry", "@19", "file_description_clause_sequence",
  "file_description_clause", "block_contains_clause",
  "_records_or_characters", "record_clause", "record_depending",
  "opt_from_integer", "opt_to_integer", "label_records_clause",
  "label_option", "value_of_clause", "valueof_name", "data_records_clause",
  "linage_clause", "linage_sequence", "linage_lines", "linage_footing",
  "linage_top", "linage_bottom", "recording_mode_clause",
  "code_set_clause", "report_clause", "working_storage_section", "$@20",
  "record_description_list", "record_description_list_1", "$@21",
  "record_description_list_2", "data_description", "$@22", "$@23",
  "level_number", "level_number_88", "_maybe_next_level_number",
  "entry_name", "const_name", "const_global", "lit_or_length",
  "constant_entry", "data_description_clause_sequence",
  "data_description_clause", "redefines_clause", "external_clause",
  "as_extname", "global_clause", "picture_clause", "usage_clause", "usage",
  "sign_clause", "occurs_key_spec", "occurs_clause", "occurs_to_integer",
  "occurs_depending", "_occurs_keys", "occurs_keys", "occurs_key",
  "occurs_key_list", "ascending_or_descending", "_occurs_indexed",
  "occurs_indexed", "occurs_index_list", "occurs_index",
  "justified_clause", "synchronized_clause", "left_or_right",
  "blank_clause", "based_clause", "value_clause", "value_cond_clause",
  "$@24", "value_item_list", "value_item", "false_is", "renames_clause",
  "any_length_clause", "local_storage_section", "$@25", "linkage_section",
  "$@26", "report_section", "$@27", "opt_report_description_list",
  "report_description_list", "report_description_entry",
  "report_description_options", "report_description_option",
  "control_clause", "control_field_list", "_final", "identifier_list",
  "page_limit_clause", "heading_clause", "first_detail", "last_heading",
  "last_detail", "footing_clause", "page_line_column", "line_or_lines",
  "report_group_description_list", "report_group_description_entry",
  "report_group_options", "report_group_option", "type_clause",
  "type_option", "next_group_clause", "column_clause", "sum_clause_list",
  "sum_clause", "ref_id_exp", "present_when_condition", "varying_clause",
  "line_clause", "line_keyword_clause", "report_line_integer_list",
  "line_or_plus", "_numbers", "source_clause", "group_indicate_clause",
  "_indicate", "report_name", "screen_section", "$@28", "$@29",
  "opt_screen_description_list", "screen_description_list",
  "screen_description", "$@30", "screen_options", "screen_option",
  "screen_line_plus_minus", "screen_col_plus_minus",
  "screen_occurs_clause", "procedure_division", "$@31", "$@32",
  "procedure_using_chaining", "$@33", "$@34", "procedure_param_list",
  "procedure_param", "procedure_type", "size_optional",
  "procedure_optional", "procedure_returning", "procedure_declaratives",
  "$@35", "procedure_list", "procedure", "section_header",
  "paragraph_header", "invalid_statement", "section_name", "opt_segment",
  "statement_list", "@36", "@37", "statements", "statement",
  "accept_statement", "$@38", "accept_body", "opt_at_line_column",
  "line_number", "column_number", "opt_accp_attr", "accp_attrs",
  "accp_attr", "end_accept", "add_statement", "$@39", "add_body", "add_to",
  "end_add", "allocate_statement", "$@40", "allocate_body",
  "allocate_returning", "alter_statement", "alter_options", "_proceed_to",
  "call_statement", "$@41", "call_using", "$@42", "call_param_list",
  "call_param", "call_type", "call_returning", "call_on_exception", "$@43",
  "call_not_on_exception", "$@44", "end_call", "cancel_statement", "$@45",
  "cancel_list", "close_statement", "$@46", "close_list", "close_option",
  "reel_or_unit", "compute_statement", "$@47", "compute_body",
  "end_compute", "comp_equal", "commit_statement", "continue_statement",
  "delete_statement", "$@48", "end_delete", "delete_file_statement",
  "$@49", "display_statement", "$@50", "display_body", "with_clause",
  "disp_attrs", "disp_attr", "end_display", "divide_statement", "$@51",
  "divide_body", "end_divide", "entry_statement", "$@52",
  "evaluate_statement", "$@53", "evaluate_subject_list",
  "evaluate_subject", "evaluate_condition_list", "evaluate_case_list",
  "evaluate_case", "$@54", "evaluate_other", "$@55", "evaluate_when_list",
  "evaluate_object_list", "evaluate_object", "opt_evaluate_thru_expr",
  "end_evaluate", "exit_statement", "$@56", "exit_body", "free_statement",
  "$@57", "generate_statement", "$@58", "goto_statement", "$@59",
  "goto_depending", "goback_statement", "$@60", "if_statement", "$@61",
  "$@62", "if_else_sentence", "$@63", "end_if", "initialize_statement",
  "$@64", "initialize_filler", "initialize_value", "initialize_replacing",
  "initialize_replacing_list", "initialize_replacing_item",
  "initialize_category", "initialize_default", "initiate_statement",
  "$@65", "inspect_statement", "$@66", "send_identifier", "inspect_list",
  "inspect_item", "inspect_tallying", "$@67", "tallying_list",
  "tallying_item", "inspect_replacing", "replacing_list", "replacing_item",
  "rep_keyword", "replacing_region", "inspect_converting",
  "inspect_region", "_initial", "merge_statement", "$@68",
  "move_statement", "$@69", "move_body", "multiply_statement", "$@70",
  "multiply_body", "end_multiply", "open_statement", "$@71", "open_list",
  "open_mode", "open_sharing", "open_option", "perform_statement", "$@72",
  "perform_body", "$@73", "end_perform", "perform_procedure",
  "perform_option", "perform_test", "perform_varying_list",
  "perform_varying", "read_statement", "$@74", "read_into", "with_lock",
  "read_key", "read_handler", "end_read", "release_statement", "$@75",
  "return_statement", "$@76", "end_return", "rewrite_statement", "$@77",
  "write_lock", "end_rewrite", "rollback_statement", "search_statement",
  "$@78", "search_body", "$@79", "search_varying", "search_at_end", "$@80",
  "search_whens", "search_when", "$@81", "end_search", "set_statement",
  "$@82", "set_body", "set_environment", "set_to", "set_up_down",
  "up_or_down", "set_to_on_off_sequence", "set_to_on_off",
  "set_to_true_false_sequence", "set_to_true_false", "sort_statement",
  "$@83", "sort_body", "$@84", "sort_key_list", "opt_key_list",
  "sort_duplicates", "sort_collating", "sort_input", "sort_output",
  "start_statement", "$@85", "@86", "start_key", "start_op", "end_start",
  "stop_statement", "$@87", "$@88", "stop_returning", "string_statement",
  "$@89", "string_item_list", "string_item", "opt_with_pointer",
  "end_string", "subtract_statement", "$@90", "subtract_body",
  "end_subtract", "suppress_statement", "_printing", "terminate_statement",
  "$@91", "transform_statement", "$@92", "unlock_statement", "$@93",
  "opt_record", "unstring_statement", "$@94", "unstring_delimited",
  "unstring_delimited_list", "unstring_delimited_item", "unstring_into",
  "unstring_into_item", "unstring_into_delimiter", "unstring_into_count",
  "unstring_tallying", "end_unstring", "use_statement", "use_exception",
  "use_global", "use_exception_target", "_after", "_standard",
  "exception_or_error", "exception_or_overflow",
  "not_exception_or_overflow", "_procedure", "use_debugging",
  "use_debugging_target", "use_reporting", "write_statement", "$@95",
  "write_from", "write_option", "before_or_after", "write_handler",
  "end_write", "on_accp_exception", "on_disp_exception",
  "opt_on_exception", "$@96", "opt_not_on_exception", "$@97",
  "on_size_error", "opt_on_size_error", "$@98", "opt_not_on_size_error",
  "$@99", "on_overflow", "opt_on_overflow", "$@100", "opt_not_on_overflow",
  "$@101", "at_end", "at_end_sentence", "$@102", "not_at_end_sentence",
  "$@103", "at_eop", "at_eop_sentence", "$@104", "not_at_eop_sentence",
  "$@105", "opt_invalid_key", "invalid_key", "invalid_key_sentence",
  "$@106", "not_invalid_key_sentence", "$@107", "_opt_scroll_lines",
  "condition", "expr", "partial_expr", "$@108", "expr_tokens",
  "expr_token", "eq", "gt", "lt", "ge", "le", "exp_list", "e_sep", "exp",
  "linage_counter", "arithmetic_x_list", "arithmetic_x", "record_name",
  "table_name", "file_name_list", "file_name", "mnemonic_name_list",
  "mnemonic_name", "procedure_name_list", "procedure_name", "label",
  "integer_label", "reference_list", "reference", "no_reference_list",
  "opt_reference", "reference_or_literal", "undefined_word",
  "target_x_list", "target_x", "x_list", "x", "arith_x", "prog_or_entry",
  "alnum_or_id", "simple_value", "simple_all_value", "id_or_lit",
  "id_or_lit_or_func", "num_id_or_lit", "identifier", "identifier_1",
  "qualified_word", "subref", "refmod", "integer", "literal",
  "basic_literal", "basic_value", "function", "func_refmod", "func_args",
  "list_func_args", "trim_args", "numvalc_args", "locale_dt_args",
  "not_const_word", "flag_all", "flag_duplicates", "flag_initialized",
  "flag_next", "flag_not", "flag_optional", "flag_rounded",
  "flag_separate", "in_of", "records", "with_dups", "coll_sequence",
  "_advancing", "_also", "_are", "_area", "_as", "_at", "_binary", "_by",
  "_character", "_characters", "_contains", "_data", "_file", "_for",
  "_from", "_in", "_is", "_is_are", "_key", "_line_or_lines", "_lines",
  "_literal", "_mode", "_number", "_of", "_on", "_in_order", "_other",
  "_program", "_record", "_right", "_set", "_sign", "_sign_is", "_size",
  "_status", "_tape", "_than", "_then", "_times", "_to", "_when", "_with", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592,   593,   594,
     595,   596,   597,   598,   599,   600,   601,   602,   603,   604,
     605,   606,   607,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,   618,   619,   620,   621,   622,   623,   624,
     625,   626,   627,   628,   629,   630,   631,   632,   633,   634,
     635,   636,   637,   638,   639,   640,   641,   642,   643,   644,
     645,   646,   647,   648,   649,   650,   651,   652,   653,   654,
     655,   656,   657,   658,   659,   660,   661,   662,   663,   664,
     665,   666,   667,   668,   669,   670,   671,   672,   673,   674,
     675,   676,   677,   678,   679,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   693,   694,
     695,   696,   697,   698,   699,   700,   701,   702,   703,    43,
      45,    42,    47,   704,    94,    46,    61,    41,    40,    62,
      60,    58,    38
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   463,   465,   464,   466,   466,   467,   467,   469,   470,
     468,   472,   473,   471,   475,   476,   474,   477,   477,   477,
     478,   478,   479,   480,   482,   481,   483,   484,   484,   485,
     485,   486,   486,   487,   487,   487,   488,   488,   489,   489,
     490,   490,   491,   491,   492,   492,   492,   492,   493,   494,
     494,   494,   494,   495,   496,   497,   498,   498,   498,   498,
     499,   499,   500,   500,   500,   501,   502,   502,   503,   504,
     505,   506,   506,   507,   507,   508,   508,   509,   509,   510,
     511,   511,   511,   512,   512,   513,   513,   513,   513,   513,
     513,   513,   513,   513,   513,   513,   514,   515,   514,   516,
     514,   514,   514,   514,   514,   517,   517,   518,   518,   519,
     520,   520,   522,   521,   523,   523,   523,   523,   523,   524,
     524,   525,   525,   526,   525,   527,   527,   528,   528,   528,
     528,   528,   528,   529,   529,   529,   529,   529,   529,   530,
     531,   532,   532,   533,   533,   534,   535,   535,   536,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   544,   545,
     544,   546,   544,   547,   547,   548,   548,   550,   549,   551,
     551,   552,   552,   552,   552,   552,   552,   552,   552,   552,
     552,   552,   552,   552,   552,   552,   553,   553,   553,   554,
     554,   554,   555,   555,   555,   556,   556,   556,   557,   557,
     558,   559,   559,   559,   560,   560,   562,   561,   561,   563,
     564,   564,   564,   565,   566,   567,   567,   567,   568,   569,
     569,   569,   570,   570,   570,   570,   571,   571,   572,   572,
     573,   573,   573,   573,   573,   574,   575,   576,   576,   577,
     578,   578,   579,   580,   580,   580,   581,   582,   582,   583,
     583,   583,   583,   584,   584,   585,   585,   586,   587,   587,
     587,   587,   588,   589,   589,   590,   591,   591,   592,   592,
     592,   593,   593,   593,   593,   593,   594,   594,   595,   596,
     595,   597,   595,   598,   598,   599,   600,   600,   601,   601,
     603,   602,   604,   604,   605,   605,   605,   605,   605,   605,
     605,   605,   605,   605,   605,   605,   606,   607,   607,   607,
     608,   608,   608,   609,   609,   610,   610,   611,   611,   612,
     613,   613,   614,   614,   615,   615,   616,   617,   618,   618,
     619,   619,   619,   620,   621,   622,   623,   624,   625,   625,
     626,   627,   626,   628,   628,   630,   629,   631,   631,   631,
     632,   633,   632,   634,   632,   635,   636,   637,   637,   638,
     638,   638,   639,   640,   640,   641,   641,   641,   642,   643,
     643,   644,   644,   644,   644,   644,   644,   644,   644,   644,
     644,   644,   644,   644,   644,   644,   645,   646,   647,   647,
     648,   649,   650,   650,   651,   651,   651,   651,   651,   651,
     651,   651,   651,   651,   651,   651,   651,   651,   651,   651,
     651,   651,   651,   651,   651,   651,   651,   651,   651,   651,
     651,   651,   651,   651,   651,   651,   651,   651,   651,   652,
     652,   653,   653,   653,   654,   655,   655,   656,   656,   657,
     657,   658,   659,   660,   660,   661,   661,   662,   662,   663,
     664,   664,   665,   666,   667,   668,   668,   668,   669,   670,
     671,   673,   672,   674,   674,   675,   675,   676,   676,   677,
     677,   678,   679,   680,   679,   681,   682,   681,   683,   684,
     683,   685,   685,   686,   686,   687,   688,   688,   689,   689,
     689,   689,   690,   690,   691,   692,   692,   693,   693,   694,
     695,   695,   696,   696,   697,   697,   698,   698,   699,   699,
     700,   700,   700,   701,   701,   702,   702,   703,   704,   704,
     705,   705,   705,   705,   705,   705,   705,   705,   705,   705,
     705,   705,   705,   705,   705,   705,   706,   707,   707,   707,
     707,   707,   707,   707,   708,   709,   709,   709,   710,   710,
     711,   712,   713,   714,   715,   716,   716,   717,   717,   718,
     718,   718,   719,   719,   719,   720,   721,   722,   722,   723,
     724,   725,   726,   724,   727,   727,   728,   728,   729,   730,
     729,   731,   731,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   732,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   732,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   732,   733,   733,   733,   733,   733,   734,   734,
     734,   734,   734,   735,   736,   737,   738,   736,   739,   740,
     739,   741,   739,   742,   742,   743,   744,   744,   744,   745,
     745,   745,   745,   745,   746,   746,   747,   747,   748,   749,
     748,   750,   750,   751,   751,   751,   751,   751,   752,   753,
     754,   755,   756,   756,   758,   759,   757,   760,   760,   761,
     761,   761,   761,   761,   761,   761,   761,   761,   761,   761,
     761,   761,   761,   761,   761,   761,   761,   761,   761,   761,
     761,   761,   761,   761,   761,   761,   761,   761,   761,   761,
     761,   761,   761,   761,   761,   761,   761,   761,   761,   761,
     761,   761,   761,   761,   761,   761,   761,   761,   761,   763,
     762,   764,   764,   764,   764,   764,   764,   764,   764,   764,
     764,   764,   764,   764,   764,   764,   764,   764,   765,   765,
     765,   765,   765,   765,   766,   767,   767,   768,   768,   769,
     769,   770,   770,   770,   770,   770,   770,   770,   770,   770,
     770,   770,   770,   770,   770,   770,   770,   770,   771,   771,
     773,   772,   774,   774,   774,   775,   775,   776,   776,   778,
     777,   779,   779,   780,   780,   781,   782,   782,   783,   783,
     785,   784,   786,   787,   786,   788,   788,   789,   789,   790,
     790,   790,   790,   791,   791,   791,   792,   793,   792,   794,
     795,   794,   796,   796,   798,   797,   799,   799,   799,   801,
     800,   802,   802,   803,   803,   803,   803,   803,   804,   804,
     806,   805,   807,   808,   808,   809,   809,   810,   811,   813,
     812,   814,   814,   816,   815,   818,   817,   819,   819,   819,
     819,   819,   819,   819,   819,   819,   820,   820,   820,   821,
     821,   822,   822,   822,   822,   822,   822,   822,   822,   822,
     822,   822,   822,   822,   822,   822,   823,   823,   825,   824,
     826,   826,   826,   826,   826,   827,   827,   829,   828,   831,
     830,   832,   832,   833,   833,   833,   834,   835,   835,   837,
     836,   838,   839,   838,   840,   840,   841,   841,   842,   842,
     842,   842,   843,   843,   844,   844,   846,   845,   847,   847,
     847,   847,   847,   847,   849,   848,   851,   850,   853,   852,
     854,   854,   856,   855,   858,   859,   857,   857,   860,   861,
     860,   862,   862,   864,   863,   865,   865,   866,   866,   866,
     867,   867,   868,   868,   869,   870,   870,   870,   870,   870,
     870,   870,   871,   871,   873,   872,   875,   874,   876,   876,
     876,   877,   877,   878,   878,   878,   880,   879,   881,   881,
     882,   882,   882,   882,   882,   882,   883,   884,   884,   885,
     885,   886,   886,   886,   886,   886,   887,   888,   889,   889,
     890,   890,   892,   891,   894,   893,   895,   895,   897,   896,
     898,   898,   899,   899,   901,   900,   902,   902,   903,   903,
     903,   903,   904,   904,   905,   905,   905,   907,   906,   908,
     909,   908,   908,   910,   910,   911,   911,   912,   912,   912,
     912,   912,   913,   913,   914,   914,   915,   917,   916,   918,
     918,   919,   919,   919,   919,   919,   919,   920,   920,   921,
     921,   921,   922,   922,   924,   923,   926,   925,   927,   927,
     929,   928,   930,   930,   930,   931,   931,   932,   934,   933,
     935,   936,   935,   937,   937,   938,   939,   938,   940,   940,
     942,   941,   943,   943,   945,   944,   946,   946,   946,   946,
     946,   947,   948,   948,   949,   950,   950,   951,   951,   952,
     953,   953,   954,   954,   956,   955,   958,   957,   959,   959,
     960,   960,   961,   961,   962,   962,   963,   963,   963,   964,
     964,   964,   966,   967,   965,   968,   968,   969,   969,   969,
     969,   969,   970,   970,   972,   971,   973,   971,   974,   974,
     974,   976,   975,   977,   977,   978,   978,   978,   979,   979,
     980,   980,   982,   981,   983,   983,   983,   984,   984,   985,
     986,   986,   988,   987,   990,   989,   992,   991,   993,   993,
     993,   995,   994,   996,   996,   997,   997,   998,   999,   999,
    1000,  1001,  1001,  1002,  1002,  1003,  1003,  1004,  1004,  1005,
    1005,  1005,  1006,  1007,  1007,  1008,  1008,  1008,  1008,  1008,
    1009,  1009,  1010,  1010,  1011,  1011,  1012,  1012,  1013,  1013,
    1014,  1014,  1015,  1016,  1016,  1017,  1019,  1018,  1020,  1020,
    1021,  1021,  1021,  1021,  1022,  1022,  1023,  1023,  1023,  1024,
    1024,  1025,  1026,  1027,  1028,  1027,  1029,  1030,  1029,  1031,
    1032,  1033,  1032,  1034,  1035,  1034,  1036,  1037,  1038,  1037,
    1039,  1040,  1039,  1041,  1041,  1041,  1043,  1042,  1045,  1044,
    1046,  1046,  1046,  1048,  1047,  1050,  1049,  1051,  1051,  1052,
    1052,  1052,  1054,  1053,  1056,  1055,  1057,  1057,  1058,  1059,
    1061,  1060,  1062,  1062,  1062,  1062,  1062,  1062,  1062,  1062,
    1062,  1062,  1062,  1062,  1062,  1062,  1062,  1062,  1062,  1062,
    1062,  1063,  1063,  1063,  1063,  1063,  1063,  1063,  1063,  1063,
    1063,  1063,  1063,  1063,  1063,  1063,  1063,  1063,  1063,  1063,
    1063,  1063,  1063,  1063,  1063,  1063,  1063,  1063,  1063,  1064,
    1064,  1064,  1065,  1065,  1066,  1066,  1067,  1067,  1067,  1068,
    1068,  1068,  1069,  1069,  1070,  1070,  1070,  1071,  1071,  1071,
    1071,  1071,  1071,  1071,  1071,  1071,  1072,  1072,  1073,  1073,
    1074,  1075,  1076,  1077,  1077,  1078,  1079,  1079,  1080,  1081,
    1081,  1082,  1083,  1083,  1083,  1084,  1085,  1085,  1086,  1087,
    1087,  1088,  1088,  1089,  1089,  1090,  1091,  1091,  1092,  1092,
    1093,  1093,  1094,  1094,  1094,  1094,  1094,  1094,  1094,  1094,
    1094,  1095,  1095,  1095,  1095,  1095,  1095,  1095,  1096,  1096,
    1097,  1097,  1098,  1098,  1099,  1099,  1100,  1100,  1101,  1101,
    1101,  1102,  1102,  1102,  1103,  1104,  1104,  1104,  1104,  1105,
    1105,  1106,  1107,  1107,  1108,  1109,  1109,  1110,  1110,  1111,
    1111,  1111,  1111,  1111,  1111,  1111,  1112,  1112,  1112,  1112,
    1112,  1112,  1112,  1112,  1112,  1112,  1112,  1112,  1113,  1113,
    1113,  1114,  1114,  1115,  1115,  1116,  1116,  1116,  1117,  1117,
    1118,  1118,  1119,  1120,  1120,  1121,  1121,  1122,  1122,  1123,
    1123,  1123,  1124,  1124,  1125,  1125,  1126,  1126,  1127,  1127,
    1128,  1128,  1129,  1129,  1130,  1130,  1131,  1131,  1132,  1132,
    1133,  1133,  1134,  1134,  1135,  1135,  1136,  1136,  1137,  1137,
    1138,  1138,  1139,  1139,  1140,  1140,  1141,  1141,  1142,  1142,
    1143,  1143,  1144,  1144,  1145,  1145,  1146,  1146,  1147,  1147,
    1148,  1148,  1149,  1149,  1149,  1150,  1150,  1151,  1151,  1151,
    1152,  1152,  1153,  1153,  1154,  1154,  1155,  1155,  1156,  1156,
    1157,  1157,  1158,  1158,  1158,  1159,  1159,  1160,  1160,  1161,
    1161,  1162,  1162,  1163,  1163,  1164,  1164,  1165,  1165,  1165,
    1166,  1166,  1167,  1167,  1168,  1168,  1169,  1169,  1170,  1170,
    1171,  1171,  1172,  1172,  1173,  1173,  1174,  1174
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     1,     2,     1,     1,     0,     0,
       8,     0,     0,     8,     0,     0,     7,     0,     1,     2,
       0,     3,     3,     3,     0,     7,     5,     1,     1,     0,
       2,     0,     3,     1,     2,     1,     1,     1,     0,     5,
       0,     4,     0,     2,     1,     1,     1,     1,     3,     0,
       2,     3,     2,     3,     1,     3,     0,     2,     3,     2,
       1,     2,     1,     1,     1,     5,     1,     1,     4,     3,
       3,     0,     2,     1,     2,     3,     3,     1,     2,     3,
       0,     1,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     5,     0,
       4,     3,     3,     3,     3,     0,     2,     1,     2,     4,
       1,     1,     0,     5,     1,     1,     1,     1,     1,     1,
       2,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     2,     1,     2,     4,     1,     2,     1,     3,
       4,     4,     3,     3,     4,     3,     3,     0,     5,     0,
       4,     0,     4,     0,     3,     0,     2,     0,     6,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     4,     4,     0,
       1,     1,     0,     1,     1,     1,     1,     2,     1,     2,
       4,     1,     1,     1,     6,     8,     0,     2,     2,     1,
       0,     2,     1,     3,     5,     0,     1,     1,     4,     2,
       2,     1,     0,     4,     5,     2,     1,     1,     3,     1,
       1,     3,     1,     1,     2,     4,     4,     4,     6,     4,
       3,     2,     3,     2,     2,     2,     4,     0,     3,     0,
       2,     1,     1,     1,     2,     1,     1,     5,     0,     1,
       1,     1,     5,     1,     2,     2,     0,     2,     2,     1,
       2,     4,     7,     6,     6,     4,     0,     9,     0,     0,
       5,     0,     3,     0,     2,     3,     2,     2,     1,     1,
       0,     4,     0,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     0,     1,     1,
       4,     6,     9,     0,     3,     0,     2,     0,     2,     3,
       1,     1,     5,     5,     1,     1,     3,     5,     0,     2,
       1,     1,     1,     5,     4,     3,     4,     3,     3,     3,
       0,     0,     5,     0,     1,     0,     2,     2,     3,     2,
       1,     0,     5,     0,     4,     1,     1,     0,     1,     0,
       1,     1,     1,     0,     2,     1,     3,     3,     6,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     0,     2,
       2,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     2,     2,     1,     2,
       2,     1,     2,     2,     1,     2,     2,     1,     1,     3,
       3,     0,     2,     2,     6,     0,     2,     0,     3,     0,
       1,     1,     4,     1,     2,     1,     1,     0,     1,     3,
       1,     2,     1,     2,     2,     0,     1,     1,     3,     1,
       3,     0,     8,     1,     2,     1,     3,     0,     3,     2,
       4,     2,     0,     0,     5,     0,     0,     5,     0,     0,
       5,     0,     1,     1,     2,     5,     0,     2,     2,     3,
       1,     1,     2,     2,     2,     0,     1,     1,     2,     8,
       0,     3,     0,     4,     0,     4,     0,     3,     0,     3,
       1,     4,     2,     1,     1,     0,     2,     4,     0,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     4,     4,     2,     1,     1,     2,
       3,     1,     3,     6,     2,     3,     2,     1,     2,     2,
       1,     2,     0,     1,     1,     4,     2,     0,     1,     1,
       0,     0,     0,     6,     0,     1,     1,     2,     1,     0,
       5,     0,     2,     1,     1,     1,     1,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       5,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     0,     1,     1,     1,     1,     0,     1,
       1,     1,     1,     3,     0,     0,     0,     9,     0,     0,
       3,     0,     3,     1,     2,     4,     0,     2,     2,     0,
       3,     3,     4,     3,     0,     1,     0,     2,     0,     0,
       7,     0,     2,     1,     1,     1,     2,     1,     4,     2,
       1,     1,     0,     1,     0,     0,     3,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     4,     4,     3,     3,     3,     4,     3,     4,     3,
       3,     3,     4,     5,     3,     4,     3,     3,     0,     3,
       3,     2,     2,     2,     3,     3,     3,     0,     2,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     1,     1,     1,     1,     1,     1,     0,     1,
       0,     4,     4,     5,     6,     0,     2,     0,     1,     0,
       3,     3,     5,     0,     2,     2,     0,     5,     0,     2,
       0,     8,     0,     0,     3,     1,     2,     2,     3,     0,
       2,     2,     2,     0,     2,     2,     0,     0,     3,     0,
       0,     3,     0,     1,     0,     3,     0,     2,     1,     0,
       3,     0,     3,     0,     1,     3,     3,     2,     1,     1,
       0,     4,     4,     0,     1,     1,     1,     1,     1,     0,
       6,     0,     1,     0,     4,     0,     4,     3,     3,     3,
       3,     4,     6,     6,     6,     6,     0,     2,     2,     1,
       2,     1,     1,     2,     2,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     1,     1,     0,     1,     0,     4,
       4,     6,     6,     8,     8,     0,     1,     0,     4,     0,
       5,     1,     3,     1,     1,     1,     2,     1,     2,     0,
       3,     0,     0,     3,     2,     3,     1,     3,     2,     1,
       1,     1,     0,     2,     0,     1,     0,     3,     0,     1,
       1,     2,     1,     1,     0,     3,     0,     3,     0,     5,
       0,     3,     0,     2,     0,     0,     8,     3,     0,     0,
       3,     0,     1,     0,     7,     0,     2,     0,     3,     3,
       0,     2,     1,     2,     4,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     0,     3,     0,     4,     1,     1,
       1,     1,     2,     1,     1,     1,     0,     3,     1,     2,
       2,     2,     1,     1,     1,     2,     2,     1,     2,     4,
       2,     0,     1,     1,     1,     1,     4,     5,     0,     4,
       0,     1,     0,     3,     0,     3,     3,     4,     0,     4,
       4,     6,     0,     1,     0,     3,     0,     5,     1,     1,
       1,     1,     0,     3,     0,     3,     2,     0,     3,     2,
       0,     4,     2,     0,     1,     1,     3,     0,     1,     2,
       3,     3,     0,     3,     1,     3,     7,     0,    10,     0,
       2,     0,     2,     2,     3,     3,     2,     0,     3,     0,
       1,     1,     0,     1,     0,     4,     0,     7,     0,     1,
       0,     7,     0,     2,     3,     0,     1,     1,     0,     4,
       4,     0,     7,     0,     2,     0,     0,     4,     1,     2,
       0,     4,     0,     1,     0,     3,     1,     1,     1,     1,
       1,     4,     4,     3,     4,     1,     1,     1,     2,     3,
       1,     2,     3,     3,     0,     3,     0,     7,     0,     6,
       0,     2,     0,     2,     0,     3,     0,     2,     4,     0,
       2,     4,     0,     0,     7,     0,     4,     2,     2,     2,
       2,     2,     0,     1,     0,     4,     0,     3,     0,     2,
       2,     0,     8,     1,     2,     1,     3,     3,     0,     3,
       0,     1,     0,     4,     4,     6,     6,     0,     1,     2,
       0,     1,     0,     3,     0,     7,     0,     4,     0,     1,
       1,     0,     9,     0,     3,     1,     3,     2,     2,     2,
       3,     0,     3,     0,     3,     0,     3,     0,     1,     1,
       1,     1,     8,     0,     1,     1,     1,     1,     1,     1,
       0,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       0,     1,     5,     1,     2,     5,     0,     8,     0,     2,
       0,     4,     3,     3,     1,     1,     0,     1,     1,     0,
       1,     2,     2,     0,     0,     3,     0,     0,     3,     2,
       0,     0,     3,     0,     0,     3,     2,     0,     0,     3,
       0,     0,     3,     1,     1,     2,     0,     3,     0,     3,
       1,     1,     2,     0,     3,     0,     3,     0,     1,     1,
       1,     2,     0,     3,     0,     3,     0,     3,     1,     1,
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     0,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       2,     1,     1,     2,     1,     2,     1,     5,     4,     1,
       5,     4,     1,     3,     0,     1,     1,     1,     3,     3,
       3,     3,     2,     2,     3,     3,     1,     3,     1,     2,
       2,     1,     1,     1,     2,     1,     1,     2,     1,     0,
       2,     1,     1,     1,     3,     1,     1,     2,     1,     1,
       2,     0,     1,     1,     1,     1,     1,     2,     1,     3,
       1,     2,     1,     3,     3,     3,     4,     3,     1,     1,
       1,     1,     3,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     3,     1,
       3,     3,     4,     5,     1,     1,     2,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     5,     5,
       5,     5,     5,     5,     5,     4,     5,     2,     0,     4,
       5,     0,     3,     0,     1,     1,     3,     3,     1,     3,
       1,     3,     0,     0,     1,     0,     1,     0,     1,     0,
       1,     1,     0,     1,     0,     1,     0,     1,     0,     2,
       1,     1,     2,     2,     2,     1,     2,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     1,     0,     1,     0,     1,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     2,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     2,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,     4,     6,     7,
      38,    38,     0,     0,     3,     5,     0,     8,    14,    28,
      27,    29,    29,     0,   276,   276,     0,     0,    24,    40,
       0,     9,    15,    30,    26,  1540,     0,   157,     0,   624,
     624,  1541,     0,     0,     0,     0,     0,     0,    39,   278,
       0,    17,     0,    25,    33,    37,    36,  1567,    35,    42,
     159,     0,   161,   288,   289,     0,   340,   281,   628,    18,
      20,    38,     0,    16,    34,  1568,    32,    41,   165,   163,
     249,     0,     0,   472,     0,   631,   629,   646,     0,    19,
      10,    11,     0,     0,     0,     0,     0,    43,    44,    45,
      47,    46,   160,     0,   247,     0,  1532,   258,   162,   251,
     253,   255,   256,   252,   269,   279,     0,     0,   475,  1375,
     282,   343,   290,   636,   636,     0,     0,     0,   276,    23,
      56,    71,    49,    80,  1494,   166,   165,     0,   158,     0,
    1560,     0,  1558,     0,  1533,  1584,   259,   260,   261,  1514,
     250,   254,   268,   270,   283,   341,     0,     0,   478,   287,
       0,   286,   344,  1482,   292,  1523,   636,   633,   639,     0,
     636,   647,   625,    21,    12,     0,  1540,    54,  1567,    55,
    1567,    60,    62,    63,    64,     0,     0,    70,     0,    73,
    1597,    48,     0,  1596,     0,     0,  1540,  1540,     0,     0,
    1575,  1540,  1540,  1540,  1540,  1540,     0,  1540,  1526,  1540,
      79,    81,    83,    85,    86,    87,    89,    88,    90,    91,
      92,    93,    94,    95,  1495,     0,   164,   249,     0,  1561,
       0,     0,  1559,     0,     0,  1585,  1528,  1515,  1534,   280,
     343,   473,     0,     0,   570,   343,   346,     0,     0,   634,
    1540,     0,   644,   637,   638,   648,   624,  1540,     0,    57,
    1567,    59,    61,     0,  1507,  1540,     0,    77,     0,    72,
      74,    52,    50,     0,     0,  1395,   112,     0,     0,  1540,
    1540,  1576,  1540,     0,     0,     0,     0,     0,  1540,     0,
    1527,     0,    99,    82,    84,   167,   248,  1439,   275,  1386,
    1388,   271,     0,     0,     0,  1529,     0,  1535,     0,   284,
     342,   343,   476,     0,     0,   277,   285,   349,     0,   355,
     356,   347,   359,   359,   350,   305,  1528,  1540,     0,     0,
    1540,  1528,  1554,  1540,  1512,     0,   291,   293,   296,   297,
     298,   299,   300,   301,   302,   303,   304,     0,     0,  1540,
     645,     0,     0,   626,    17,     0,  1444,    69,    58,  1506,
       0,    76,    75,    78,    51,    53,  1540,   101,   102,     0,
       0,     0,   153,   152,   103,   104,   156,     0,   155,   139,
    1542,   141,    96,     0,    97,   169,  1500,  1501,     0,  1387,
       0,     0,     0,   262,   263,   266,   257,  1373,   474,   343,
     479,     0,   348,   360,   361,   351,     0,   361,   353,     0,
       0,  1540,  1512,     0,     0,     0,     0,     0,  1555,  1540,
       0,  1513,     0,     0,   294,   295,   640,   641,   643,     0,
     635,   649,   651,     0,     0,    68,     0,  1453,  1449,  1454,
    1452,  1450,  1455,  1451,   145,   146,   148,   154,   151,   150,
    1544,  1543,   142,     0,   111,   110,   100,   107,  1582,   105,
       0,  1440,   273,     0,   274,   264,     0,   265,  1374,   477,
     481,   571,   369,   363,     0,   317,   337,  1502,  1503,   326,
    1389,   321,   320,   319,  1394,  1393,  1550,  1526,  1538,     0,
     569,   338,   339,  1540,  1540,   642,   651,     0,     0,    13,
      66,    67,    65,   117,   131,   127,   132,   114,   130,   128,
     115,   116,   129,   113,   118,   119,   121,   147,     0,   140,
     143,   108,  1583,  1540,    98,   184,  1554,     0,  1592,   230,
       0,  1554,  1545,  1540,  1524,  1545,   233,     0,   232,  1596,
     217,   216,   168,   170,   171,   172,   173,   174,   175,     0,
     176,   177,   229,   178,   179,   180,   181,   182,   183,   185,
    1540,   272,   267,     0,   480,   482,   483,   572,     0,  1516,
       0,  1542,   354,     0,   307,  1390,  1551,   328,     0,   310,
    1539,  1580,   336,     0,     0,     0,   657,   661,   652,   653,
     654,   655,   660,     0,     0,   120,   123,     0,   149,   144,
       0,   106,  1540,  1545,  1593,   192,   234,  1540,  1546,  1540,
       0,  1525,  1540,  1521,  1540,     0,  1540,  1540,   241,  1514,
       0,  1540,     0,   486,   484,   574,   385,     0,   459,   394,
     427,   415,   424,   421,   418,  1594,   395,   396,   397,   398,
     399,   400,   401,   402,   403,  1571,   358,   428,     0,   404,
     391,   405,   406,     0,     0,  1578,   408,   409,   407,   455,
     411,   412,   410,  1540,  1540,   352,   370,   371,   372,   373,
     374,   375,   392,   376,   377,   378,   379,   380,   381,   382,
     383,   384,     0,     0,  1517,     0,   364,     0,   318,   309,
     308,   306,   327,  1526,  1581,   315,   324,   323,   325,   322,
       0,   659,   662,   719,   770,   779,   786,   790,   814,   819,
     837,   830,   838,   839,   845,   878,   887,   889,   916,   924,
     926,  1592,   932,     0,   943,   964,   966,  1002,  1004,  1008,
     718,  1014,  1027,  1047,  1064,  1066,  1070,  1077,  1078,  1094,
    1114,  1132,     0,  1151,  1162,  1170,  1172,  1174,  1176,  1181,
    1203,  1226,   656,   668,   669,   670,   671,   672,   673,   674,
     675,   677,   676,   678,   679,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   693,   694,
     695,   696,   697,   698,   699,   700,   701,   702,   703,   704,
     705,   706,   707,   708,   709,   710,   711,   712,   713,   714,
     715,   716,  1199,  1200,  1201,   717,    22,     0,   122,   109,
       0,  1540,   194,   193,   189,     0,     0,  1520,   233,   228,
       0,     0,   231,     0,     0,   240,  1565,  1565,     0,   242,
       0,   213,  1540,   359,   578,   573,   575,   576,   471,   425,
     426,   413,   414,   422,   423,   419,   420,   416,   417,  1595,
       0,  1572,   453,   435,   386,  1435,   469,  1579,   456,   457,
     454,     0,     0,   388,   390,  1498,  1498,     0,  1558,  1558,
     368,   365,  1445,  1447,   461,   463,   465,  1519,   329,   330,
     331,   332,     0,     0,   311,  1537,   317,     0,     0,   663,
       0,     0,     0,  1290,   785,     0,   816,   821,     0,     0,
       0,     0,     0,     0,  1290,   918,     0,     0,   928,   933,
       0,  1290,     0,     0,     0,     0,     0,     0,  1016,  1037,
       0,     0,     0,     0,     0,     0,     0,     0,  1146,  1144,
       0,     0,  1171,  1169,     0,     0,     0,     0,  1204,  1210,
       0,     0,   137,   133,   138,   136,   134,   135,   124,   125,
     202,   203,   201,   200,     0,   187,   188,  1552,   222,   221,
     222,   218,   246,   235,   236,   237,   239,  1566,   243,   244,
     245,  1391,  1540,   495,   495,  1542,   515,   487,   490,   491,
       0,   579,   577,   458,     0,  1590,     0,  1436,  1437,     0,
     393,   460,     0,   387,  1524,   429,   430,  1446,     0,     0,
       0,  1594,   464,     0,     0,     0,  1518,  1526,   316,   650,
     658,   768,   738,  1434,  1558,     0,     0,  1468,  1471,  1558,
    1366,     0,     0,     0,     0,     0,     0,     0,     0,  1468,
     777,  1410,   775,  1400,  1402,  1408,  1409,  1487,   780,     0,
    1289,  1311,  1385,     0,  1381,  1383,  1382,  1429,   792,  1428,
    1430,   818,   815,   820,   833,     0,  1368,  1496,  1569,     0,
    1449,   876,   738,     0,  1402,   885,     0,   792,   895,   894,
    1510,   891,   893,   923,   920,   919,   922,   917,  1558,   925,
    1396,  1398,   927,  1379,   937,  1588,  1288,   945,   965,   497,
       0,   968,   969,   970,  1003,  1118,     0,  1005,     0,  1012,
       0,  1015,  1038,  1385,  1028,  1037,  1030,     0,  1035,     0,
    1382,     0,  1489,  1228,  1371,  1569,  1228,     0,  1092,  1083,
    1372,     0,  1378,  1095,  1096,  1097,  1098,  1099,  1107,  1100,
    1110,     0,  1376,     0,  1115,  1133,  1147,  1148,  1522,     0,
    1153,  1155,     0,  1167,     0,  1173,     0,  1178,  1183,  1211,
       0,  1212,  1560,  1228,     0,  1485,   196,   195,   186,     0,
       0,   220,   219,  1540,   212,   206,  1392,   214,     0,   496,
     492,     0,   493,     0,   485,   488,   581,   436,  1591,   437,
    1558,     0,     0,     0,  1354,  1352,  1417,  1357,  1411,  1415,
    1416,     0,  1438,   470,   389,  1499,   367,   366,  1448,  1573,
     466,   335,  1550,     0,   313,   769,   720,  1519,     0,   747,
       0,     0,     0,     0,     0,  1456,  1473,  1467,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1457,   778,
     771,     0,     0,  1401,  1488,   783,  1487,  1291,     0,   788,
       0,   793,   803,  1427,   817,  1426,   823,   834,   831,   836,
     835,  1290,  1369,  1497,  1370,  1570,  1277,   844,   877,   846,
     856,  1243,  1243,  1243,  1243,   886,   879,     0,     0,   888,
    1511,  1290,   914,   901,   897,   899,  1290,   921,     0,  1397,
     930,  1589,   935,   947,     0,   498,     0,   991,   976,   967,
     971,   973,   974,   975,  1122,     0,     0,  1013,  1009,     0,
    1021,  1018,  1020,  1019,  1022,  1029,  1032,   664,  1290,     0,
       0,  1039,     0,  1490,  1491,  1569,     0,  1065,  1049,  1072,
    1085,  1093,  1079,     0,  1085,     0,  1422,  1423,  1108,  1111,
       0,     0,  1377,  1106,     0,  1105,     0,  1135,     0,     0,
    1145,     0,     0,  1154,     0,  1168,  1163,     0,     0,  1179,
    1180,  1177,  1522,     0,     0,  1213,     0,     0,  1072,   126,
    1505,     0,   206,   204,  1486,   197,   198,     0,   225,   211,
     238,     0,   489,   494,   500,   510,   359,   516,  1577,  1560,
     431,     0,  1362,  1363,     0,  1355,  1356,  1441,     0,     0,
       0,     0,     0,     0,     0,     0,  1574,  1592,   334,  1550,
    1560,   312,   743,   734,  1243,   724,   731,   725,   727,   729,
       0,  1243,     0,   723,   730,   737,   736,     0,  1243,  1556,
    1556,  1556,   741,   742,  1419,  1418,     0,  1407,  1354,  1352,
       0,     0,  1354,     0,  1403,  1404,  1405,  1367,  1354,     0,
       0,  1354,     0,     0,  1354,  1354,  1354,     0,     0,  1250,
    1496,     0,     0,   781,     0,  1302,  1303,  1304,  1337,  1305,
    1592,  1341,  1346,  1586,  1312,  1349,  1586,  1330,  1309,  1319,
    1301,  1300,  1338,  1308,  1310,  1320,  1321,  1322,  1323,  1324,
    1339,  1293,  1342,  1344,  1325,  1326,  1327,  1328,  1329,  1296,
    1297,  1298,  1299,  1313,  1336,  1307,  1318,  1295,  1294,  1306,
    1315,  1316,  1317,  1314,  1331,  1332,  1333,  1334,  1335,  1292,
       0,     0,  1384,   799,     0,     0,   806,   828,   829,   822,
     824,     0,  1250,  1282,  1284,   841,  1278,  1279,  1280,     0,
    1597,  1243,     0,  1244,   849,  1246,   850,   847,   848,     0,
    1250,  1496,   909,   911,   910,   904,   906,   912,   915,   890,
     902,   898,   896,  1290,   664,   892,  1399,  1560,   929,  1380,
     664,  1592,   955,   956,   958,   960,   961,   957,   959,   950,
    1592,   946,     0,   992,     0,   994,   993,   995,   986,   987,
       0,     0,   972,  1124,  1562,     0,     0,  1006,  1250,  1496,
    1596,     0,  1033,   665,  1040,  1041,  1044,     0,  1036,  1235,
    1234,  1043,  1049,  1229,     0,     0,  1277,     0,     0,     0,
    1084,     0,     0,     0,  1109,     0,  1113,  1112,  1103,     0,
    1540,  1277,  1150,  1149,  1156,  1157,  1158,     0,  1250,  1496,
       0,  1483,     0,  1158,  1225,  1215,  1214,  1220,     0,  1222,
    1223,  1230,  1504,  1485,   199,     0,   208,   209,   207,  1540,
     502,   513,   514,   512,   518,   594,  1540,   585,   583,   584,
     586,  1556,     0,  1540,     0,   597,   589,  1556,   590,     0,
     593,   598,   596,   591,   595,     0,   592,     0,   580,   608,
     603,   606,   605,   604,   607,   582,   609,     0,   445,   446,
    1522,   434,   447,   443,   441,  1545,   439,  1412,  1413,  1414,
    1365,  1353,  1358,  1359,  1360,  1361,  1364,  1442,     0,   467,
     333,     0,   735,  1246,   726,   728,  1243,   732,   722,   762,
    1540,   751,   752,  1540,   763,   753,   754,   757,   767,   764,
     755,     0,   765,   756,   766,   748,   749,   721,  1557,     0,
       0,     0,   739,   740,  1421,  1406,  1420,  1468,  1496,     0,
    1472,     0,  1468,  1468,     0,  1465,  1468,  1468,  1468,     0,
    1468,  1468,  1251,   772,  1253,  1250,   784,     0,  1340,  1587,
    1343,  1345,   789,   787,   794,   795,   639,     0,   805,   804,
    1216,  1217,   809,   807,     0,   827,     0,   832,   664,   664,
     842,   840,  1281,   856,   856,   856,   856,  1540,   861,   874,
     875,   862,     0,  1540,   865,   866,   869,   867,     0,   868,
     858,   859,   851,   857,   664,  1247,  1242,     0,   880,     0,
    1290,  1290,   908,   664,   905,   900,     0,   938,     0,     0,
     962,     0,     0,     0,   988,   990,     0,   982,   998,   983,
     984,   977,   978,   998,  1116,  1540,     0,  1563,  1123,  1545,
    1007,  1010,     0,     0,  1024,  1034,  1031,   667,     0,     0,
    1051,  1050,  1266,  1268,  1068,  1263,  1264,  1075,  1073,     0,
    1290,  1086,  1290,  1080,  1088,  1101,  1102,  1104,  1492,  1142,
    1257,     0,  1496,  1164,     0,     0,  1484,  1184,  1185,     0,
    1188,  1191,  1195,  1189,  1221,  1560,  1224,  1236,  1508,   205,
       0,   226,   227,   223,     0,     0,   504,     0,  1577,     0,
    1540,   587,   588,     0,   611,  1540,  1590,   612,   610,   438,
       0,   432,   448,   444,  1540,   433,   440,  1443,  1540,   462,
     314,  1241,   733,     0,     0,  1286,  1286,   750,   745,   744,
     746,  1461,  1250,  1469,     0,  1481,  1466,  1459,  1479,  1460,
    1462,  1463,  1476,  1477,  1464,  1458,   664,  1254,  1249,   773,
     782,  1592,     0,  1592,     0,   796,   797,     0,   801,   800,
     802,  1218,  1219,   812,   810,   664,   825,   826,  1283,  1285,
    1243,  1243,  1243,  1243,     0,   863,   864,     0,  1286,  1286,
     860,  1245,   664,  1250,  1368,  1250,  1368,   907,   913,   903,
     931,   939,   941,   948,   951,   952,  1530,   963,   944,   949,
     998,  1424,  1425,   998,     0,   981,   979,   980,   985,  1126,
       0,  1564,  1540,  1250,  1023,  1017,     0,   666,  1045,     0,
       0,  1057,     0,   664,   664,  1069,  1067,  1265,  1076,  1071,
    1074,  1081,   664,  1090,  1089,  1493,     0,     0,  1143,  1134,
    1258,  1160,  1260,     0,  1250,  1250,  1175,  1483,  1187,  1538,
    1193,  1538,  1257,     0,  1273,  1275,  1239,  1237,  1270,  1271,
    1238,  1509,     0,   224,   501,  1540,     0,   506,   511,  1556,
     547,   567,   562,  1512,     0,     0,  1540,  1558,  1540,     0,
     517,   523,   524,   525,   534,   526,   528,   531,   519,   520,
     521,   527,   530,   548,   532,   535,   522,     0,   529,   533,
    1433,   602,  1431,  1432,   618,   601,   613,   623,   452,   449,
     450,     0,     0,   759,   758,   761,     0,   760,   774,  1470,
    1252,   664,  1348,  1592,  1351,  1592,   798,   813,   791,   664,
     808,   855,   854,   853,   852,   871,   870,   873,   872,  1248,
     882,     0,   881,     0,   664,   942,   936,   953,  1531,     0,
     997,   989,   998,  1000,     0,     0,  1129,  1125,  1120,  1011,
    1026,     0,     0,  1052,  1540,  1059,     0,  1053,     0,  1056,
    1267,  1269,   664,  1087,   664,  1136,  1137,  1138,  1139,  1140,
    1141,   664,  1161,  1152,  1261,  1256,  1159,  1166,  1165,  1186,
       0,  1538,  1190,     0,  1197,  1209,  1206,  1208,  1207,  1202,
    1205,   664,   664,  1240,  1227,  1272,  1233,  1232,  1547,     0,
    1540,  1540,   508,   546,  1540,   568,   566,   563,   564,  1542,
     556,  1540,  1290,     0,     0,     0,     0,   549,     0,     0,
     554,   557,   560,   621,   619,   620,   622,     0,   616,   614,
     615,   617,     0,   451,   442,   468,  1547,  1255,  1347,  1350,
     811,  1250,  1250,   940,     0,   996,  1001,     0,  1540,  1127,
       0,     0,  1117,  1119,  1025,     0,     0,  1062,  1060,  1061,
    1055,  1054,  1082,  1091,  1259,   664,  1192,     0,  1196,  1198,
    1182,  1274,  1276,  1548,  1549,  1231,   503,     0,     0,  1540,
     499,     0,   555,     0,   552,  1496,   550,   551,   541,   539,
     540,   542,   538,   543,   537,   536,     0,   561,   559,   558,
     600,   599,  1287,   884,   883,   954,   999,     0,  1130,  1540,
    1121,  1290,  1058,  1063,  1048,  1262,  1194,   505,   507,     0,
     545,   544,   565,     0,  1128,     0,  1046,   509,     0,  1131,
     553
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,     7,     8,    24,    39,    69,   128,
     256,     9,    25,    40,    70,    90,   499,    73,    71,    35,
      11,    21,    27,    42,    57,    58,    17,    37,    77,    97,
      98,   191,   192,   178,    99,   179,   180,   181,   182,   502,
     183,   184,   100,   187,   188,   189,   268,   101,   210,   211,
     212,   213,   459,   383,   524,   456,   457,   458,   214,   366,
     513,   514,   515,   807,   948,   516,   949,   215,   379,   380,
     519,   216,   444,   445,   217,   218,   219,   220,   221,   222,
     223,    48,    78,    80,   104,   102,   135,   385,   460,   543,
     544,   957,   814,  1158,  1365,   545,   953,   546,  1370,  1371,
    1646,  1165,   547,   548,   549,   550,   961,  1161,  1903,   551,
     552,   553,   554,   555,   556,   557,   558,   829,   559,   138,
     108,   109,   110,   111,   149,   112,   393,   394,   467,   113,
     114,    31,    66,   154,    84,   239,   159,   120,   160,   121,
     164,   248,   337,   338,   691,   339,  1401,   886,   574,   340,
     483,   341,   697,   342,   343,   692,   878,   879,   880,   881,
     344,   345,   346,    83,   240,   161,   162,   163,   246,   321,
     472,   474,   322,   323,   665,   405,   406,   569,   870,   324,
     568,   666,   667,   668,   993,   669,   670,   671,   672,   673,
    1691,   674,   985,  1380,  1925,  1692,  1693,  1694,  1695,  1921,
    1696,  2119,  2120,   675,   676,   860,   677,   678,   679,   572,
    1001,   874,   875,  1929,   680,   681,   118,   311,   158,   399,
     244,   470,   564,   565,   566,   832,   977,   978,  1170,  1171,
    1088,   979,  1650,  1906,  2077,  2222,  2300,  1374,  1653,  1174,
    1377,  1908,  2098,  2099,  2315,  2100,  2101,  2102,  2103,  2306,
    2104,  2105,  2106,  2107,  2240,  2241,  2229,  2108,  2109,  2226,
     491,   315,   567,   625,   835,   836,   837,  1176,  1378,  1685,
    2252,  2247,  1686,    51,   255,   432,    87,   124,   123,   166,
     167,   168,   252,   351,   126,   353,   496,   497,   588,   589,
     590,   591,   592,   890,  1592,  1593,  1857,   593,   753,   754,
     891,  1011,  1209,  1422,  1423,  1418,  1735,  1736,  1206,   755,
     892,  1030,  1232,  1230,   756,   893,  1038,  1453,   757,   894,
    1511,   758,   895,  1242,  1513,  1774,  1775,  1776,  1516,  1782,
    1975,  1973,  2139,  2138,   759,   896,  1052,   760,   897,  1053,
    1519,  1520,   761,   898,  1054,  1248,  1251,   762,   763,   764,
     899,  1791,   765,   900,   766,   901,  1061,  1531,  1810,  1811,
    1259,   767,   902,  1065,  1266,   768,   903,   769,   904,  1070,
    1071,  1272,  1273,  1274,  1554,  1552,  1823,  1275,  1545,  1546,
    1822,  1549,   770,   905,  1077,   771,   906,   772,   907,   773,
    1083,  1558,   774,   909,   775,   911,  1560,  2002,  2154,  2156,
     776,   912,  1283,  1569,  1830,  2004,  2005,  2006,  2008,   777,
     913,   778,   914,  1090,  1289,  1290,  1291,  1581,  1841,  1842,
    1292,  1578,  1579,  1580,  1835,  1293,  2015,  2267,   779,   915,
     780,   916,  1097,   781,   917,  1099,  1298,   782,   918,  1101,
    1304,  1591,  2025,   783,   919,  1104,  1307,  1856,  1105,  1106,
    1107,  1595,  1596,   784,   920,  1605,  2031,  2175,  2277,  2334,
     785,   921,   786,   922,  2036,   787,   923,  1606,  2039,   788,
     789,   924,  1118,  2182,  1324,  1608,  2042,  1873,  1874,  2184,
    1322,   790,   925,  1123,  1124,  1125,  1126,  1336,  1127,  1128,
    1129,  1130,   791,   926,  1094,  2019,  1294,  2273,  1583,  1844,
    2166,  2272,   792,   927,  1337,  1621,  2046,  2049,   793,  1137,
    1136,  1340,   794,   930,  1139,  1140,  1880,  2193,   795,   931,
    1143,  1346,   796,   933,   797,   934,   798,   935,   799,   936,
    1351,   800,   937,  1353,  1887,  1888,  1633,  1890,  2060,  2202,
    2062,  2290,   801,   802,   939,  2209,  1151,  1356,  1637,  1783,
    1974,  1895,   803,  1639,   804,   805,   941,  1317,  1897,  2163,
    2066,  2214,  1712,  1534,  1535,  1814,  1816,  1992,  1763,  1764,
    1956,  1958,  2131,  2051,  2052,  2191,  2195,  2285,  1864,  1865,
    2033,  1866,  2034,  2067,  2068,  2211,  2069,  2212,  1525,  1526,
    1527,  1788,  1528,  1789,  2125,  1085,  1086,  1040,  1041,  1237,
    1238,  1484,  1485,  1486,  1487,  1488,  1184,  1388,  1429,  1031,
    1055,  1252,  1113,  1119,   396,   397,  1131,  1132,  1280,  1108,
    1044,  1045,   298,   299,   479,  1167,   486,   276,  1079,  1080,
    1032,  1057,  1187,  1426,  1745,  1843,  2010,  1063,  1109,  2111,
    1034,  1013,   855,   987,   988,  2113,  1035,   872,   873,  1036,
    1215,  1217,  1433,  1447,  1442,  1439,   247,  1889,  1363,  1235,
    1315,  2047,   225,  1254,   995,   388,   413,  1364,   265,  2072,
    1820,   422,   238,   685,  1210,   615,   169,   612,   291,   306,
    2159,   145,   308,   887,   581,    43,   453,   609,  2295,   577,
    1159,   419,  1739,   233,   230,  1848,   968,   185,  1256,   852,
    1397,   282,   683,   695,   523,   236,  1770,  1282,  1179,   605,
     850,  1532
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1738
static const yytype_int16 yypact[] =
{
   -1738,   253,    46, -1738,  -150,  -138,   190, -1738, -1738, -1738,
     177,   177,    14,    14, -1738, -1738,   523, -1738, -1738, -1738,
   -1738,   651,   651,   270,   604,   604,   554,   422, -1738,   823,
     817, -1738, -1738, -1738, -1738,   -30,   619,   947,   556,   713,
     713, -1738,   568,    84,   596,   624,   847,   659, -1738,   316,
    1080,   899,  1082, -1738,   -74, -1738, -1738,   920, -1738, -1738,
   -1738,   780, -1738, -1738, -1738,   891,   806, -1738,    77, -1738,
     500,   177,    14, -1738, -1738, -1738, -1738,   707, -1738,  1085,
     131,   818,   932,  1055,   862, -1738, -1738,  1006,    14, -1738,
   -1738, -1738,   902,   911,   916,   918,   922, -1738, -1738, -1738,
   -1738, -1738,  1004,   927,  1168,   917,   985,   758, -1738,   340,
   -1738, -1738, -1738,    24, -1738, -1738,   942,  1042,  1167, -1738,
      57,   926, -1738,    91,    91,   958,   949,   952,   604, -1738,
     324,  1226,   119,  1112,  1128, -1738, -1738,   955, -1738,  1132,
    1134,  1012,  1142,  1019, -1738,  1030, -1738, -1738, -1738,  1405,
   -1738, -1738, -1738, -1738, -1738, -1738,   975,  1077,  1102, -1738,
     862, -1738, -1738, -1738, -1738, -1738,    40, -1738,  -107,   -68,
     132, -1738, -1738, -1738, -1738,  1067,  1232, -1738,   -38, -1738,
     583, -1738, -1738, -1738, -1738,    81,   193, -1738,   -19, -1738,
   -1738, -1738,   995,   723,  1344,  1011,  1232,  1232,  1011,  1081,
    1094,  1232,  1232,  1232,  1232,  1232,  1011,  1232,  1410,  1232,
   -1738,  1486, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738,  1011,  1004,   131,  1025, -1738,
    1025,  1025, -1738,  1234,  1025, -1738,  1386, -1738,  1298,    57,
     926, -1738,  1023,  1123,  1129,   926,   117,  1115,   882, -1738,
    1232,  1110,  1203, -1738, -1738,  1378,   713,  1232,  1253, -1738,
     588, -1738, -1738,  1130, -1738,  1232,  1284, -1738,    71, -1738,
   -1738, -1738, -1738,  1041,  1251, -1738, -1738,  1011,  1011,  1232,
    1232, -1738,  1232,  1025,  1434,  1011,  1011,  1025,  1232,  1025,
   -1738,  1011,    23, -1738, -1738, -1738, -1738,   480,  1025, -1738,
   -1738,  1025,  1223,  1095,  1227, -1738,   862, -1738,   862, -1738,
   -1738,   926, -1738,  1053,  1153, -1738, -1738, -1738,  1115, -1738,
   -1738, -1738,   -12,    12, -1738, -1738,  1386,  1232,   934,   934,
    1232,    42,  1264,  1232,  1492,  1240, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738,   778,   661,  1232,
   -1738,  1078,  1064, -1738,   899,  1253, -1738, -1738, -1738, -1738,
    1025, -1738, -1738, -1738, -1738, -1738,  1232, -1738, -1738,   773,
    1025,  1287, -1738, -1738, -1738, -1738, -1738,  1025, -1738, -1738,
      56, -1738, -1738,   992, -1738, -1738, -1738, -1738,  1025, -1738,
    1025,  1247,  1025,   862, -1738,  1228,   862, -1738, -1738,   926,
   -1738,  1075, -1738, -1738,  1449, -1738,  1456, -1738, -1738,  1253,
    1104,  1232,  1492,  1025,   -67,    27,  1253,  1105, -1738,  1232,
    1107, -1738,  1107,   -16, -1738, -1738, -1738, -1738, -1738,  1253,
   -1738, -1738, -1738,   521,    74, -1738,  1050, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738,   773, -1738,  1147, -1738, -1738, -1738,
   -1738, -1738, -1738,  1253, -1738, -1738,   992, -1738,  1175, -1738,
    1281, -1738,  1025,  1025,  1025, -1738,  1253, -1738, -1738, -1738,
    1248, -1738, -1738,    72,  1131,  1166, -1738, -1738, -1738,  1025,
   -1738, -1738, -1738, -1738, -1738, -1738,  1334,    82,  1374,  1133,
   -1738, -1738, -1738,  1232,  1232, -1738, -1738,  2694,    14, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738,   996, -1738,   109, -1738,   773,  1253,
   -1738, -1738, -1738,  1232,   992, -1738,  1264,  1267,  1184, -1738,
    1224,  1264,  1381,  1232,  1549,   168,   191,   874, -1738,  1176,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,  1222,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
    1232,  1025, -1738,  1107, -1738,  1248, -1738, -1738,  2431,  1581,
    1431,   187, -1738,  1253,   147, -1738, -1738, -1738,  1253, -1738,
   -1738,  1254, -1738,    97,    97,  2836, -1738,  1172, -1738, -1738,
   -1738, -1738,  1273,  3499,  1177, -1738, -1738,   996, -1738, -1738,
    1011, -1738,  1232,  1381, -1738,   164, -1738,  1232, -1738,  1232,
      28, -1738,  1232, -1738,  1232,  1259,  1232,  1232, -1738,  1405,
     142,  1232,  1189, -1738, -1738,  1406, -1738,  1409, -1738, -1738,
     -95,   -94,   575,   632,   679,  1197, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738,  1290, -1738, -1738,  1253, -1738,
   -1738, -1738, -1738,  1025,  1025,  1425, -1738, -1738, -1738,   686,
   -1738, -1738, -1738,  1232,  1232, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738,   979,   -15, -1738,   287, -1738,   524, -1738, -1738,
   -1738, -1738,    88,  1410, -1738,   743, -1738, -1738, -1738, -1738,
    1531, -1738,  1407, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738,  1237, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738,  1184, -1738,  2075, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738,   450, -1738, -1738,  1340, -1738, -1738, -1738, -1738,
     819, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738,  1084, -1738, -1738,
      55,  1232, -1738, -1738,   469,   179,  1025,  1619, -1738, -1738,
      27,  1277, -1738,  1025,  1025, -1738,  1373,  1373,  1382, -1738,
    1025, -1738,   135,   -12, -1738, -1738,  1406, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
    1214, -1738, -1738,  1261, -1738,  1208,  1268, -1738, -1738, -1738,
   -1738,  5061,   524,  1640, -1738,  1307,  1307,   773,  1142,  1142,
   -1738, -1738,  1210, -1738,   524, -1738,  1274, -1738, -1738, -1738,
   -1738, -1738,    63,  1502, -1738, -1738,  1166,  1253,  1225, -1738,
    1233,  1025,  3961,  1239,   114,  1709,  1668, -1738,  4546,   862,
    1278,  4615,  4546,  1443,   781,   909,   111,  1025, -1738, -1738,
    1554, -1738,   111,  1025,  3224,  1025,  4023,  4546, -1738,  1922,
     862,  1025,   862,  1025,    78,    92,  1025,   862, -1738, -1738,
    3983,  4045, -1738, -1738,  1025,  1025,   862,  1025, -1738,  1083,
    1584,  1025, -1738, -1738, -1738, -1738, -1738, -1738,  1676, -1738,
   -1738, -1738, -1738, -1738,  1025,   162,   182,    99,  1255, -1738,
    1255, -1738, -1738, -1738, -1738,   620, -1738, -1738, -1738, -1738,
   -1738,  1025,  1232,  1520,  1520,   187, -1738, -1738, -1738, -1738,
    1506, -1738, -1738, -1738,  1253,  1293,  5171,  1241, -1738,  1025,
   -1738, -1738,  1461, -1738,  1549, -1738, -1738, -1738,  1025,  1025,
     773,  1197, -1738,   524,    27,    27,  1670,  1410, -1738, -1738,
   -1738,  1574,   611, -1738,  1142,  1244,  1025,  1245,  1246,  1142,
     480,  1249,  1252,  1256,  1257,  1258,  1260,  1266,  1270,  1245,
    1585, -1738,  4245, -1738, -1738, -1738, -1738,  1504, -1738,  1661,
   -1738, -1738, -1738,  1319, -1738,   480, -1738, -1738,  1291, -1738,
   -1738, -1738,   115,   862,  1599,  1446, -1738,  1384,  1411,   862,
     966,  1602,  3927,  1029,  1109,  1605,   167,  1291, -1738, -1738,
      80, -1738, -1738, -1738,  1639, -1738, -1738, -1738,  1142,   111,
   -1738, -1738, -1738, -1738, -1738,  1342, -1738,    61,  1025, -1738,
     237, -1738, -1738, -1738, -1738, -1738,  4546, -1738,  1339,  1607,
    1696,   783, -1738,  1345, -1738,  2551,  1608,  -122,  1348,  1349,
    -119,  1353,   844,  1572, -1738,  1411,  1572,  1025,  1611,  1320,
   -1738,  1211, -1738, -1738, -1738, -1738, -1738,  1507, -1738,   111,
   -1738,   -50, -1738,   234, -1738, -1738, -1738,   479,  1708,  2530,
   -1738, -1738,  1025,  1612,  4295,  1025,  1579,   962,  1648, -1738,
    1430,  1387,  1134,  1572,  1084,   203, -1738,  1326, -1738,  1025,
     490, -1738, -1738,  1232, -1738, -1738, -1738, -1738,   115, -1738,
   -1738,  1025, -1738,  1253,  1406, -1738, -1738, -1738, -1738,  1655,
    1142,  5171,  5171,  5171,    64,   808, -1738, -1738, -1738,  1210,
   -1738,  5171, -1738, -1738, -1738, -1738, -1738, -1738, -1738,  1408,
   -1738, -1738,  1334,    27,  1657, -1738, -1738,  1211,  1000,  1333,
     103,    -7,  5171,  1372,  5171, -1738,  5171, -1738,  5205,  1343,
    5171,  5171,  5171,  5171,  5171,  5171,  5171,  5171, -1738, -1738,
   -1738,  4546,  1589, -1738, -1738,  1445,  1504,  1752,  3184,  1475,
    1551, -1738,   558, -1738, -1738, -1738,   695, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738,   715,   862, -1738, -1738,
     339,  1626,  1626,  1626,  1626, -1738, -1738,  4546,  4546, -1738,
   -1738,   120,  1656,   859, -1738,  1354,   781, -1738,  1025, -1738,
       9, -1738, -1738,   971,  1623, -1738,  1211,   105, -1738,   237,
   -1738, -1738, -1738, -1738,    58,  1392,   111, -1738, -1738,  4546,
   -1738, -1738, -1738, -1738,  1432, -1738, -1738, -1738, -1738,  1025,
     114, -1738,  1137, -1738, -1738,  1411,   115, -1738,  1586,   431,
     908, -1738, -1738,  1025,   908,  1394, -1738,  1210, -1738, -1738,
     110,   992, -1738, -1738,  1952, -1738,  1751,  1583,  4546,  4546,
   -1738,  4307,  1025, -1738,  1622, -1738, -1738,  4546,  1211, -1738,
   -1738, -1738,  1708,  1593,  1025, -1738,  1070,    68,   431, -1738,
   -1738,  1682, -1738, -1738, -1738,  1025, -1738,  1525, -1738, -1738,
    1025,  1025, -1738,  1025,  1613,  1044,    12, -1738,  4831,  1134,
     846,  5205,  1355,  1355,   910, -1738, -1738, -1738,  5171,  5171,
    5171,  5171,  5171,  5171,  5084,   808, -1738,  1184, -1738,  1334,
    1134, -1738, -1738, -1738,  1626, -1738, -1738,  1361,  1365, -1738,
    1211,  1626,  1594, -1738, -1738, -1738, -1738,  1675,  1626,  1543,
    1543,  1543,    96,  1582, -1738, -1738,   241, -1738,   101,   929,
    1025,   884,   106,  1357, -1738,  1210, -1738, -1738,   246,  1359,
     986,   304,  1360,  1101,   116,   144,   579,  1363,  1127,  4418,
     425,  4546,   111, -1738,  1477, -1738, -1738, -1738, -1738, -1738,
    1184, -1738, -1738,  1423, -1738, -1738,  1423, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
    1419,   114, -1738,    51,  1025,  1025,    83, -1738, -1738, -1738,
     574,   711,  1450, -1738, -1738,  1695, -1738,  1561, -1738,    16,
    1182,  1626,  1559, -1738, -1738,  1564, -1738, -1738, -1738,  1643,
    4418,   460, -1738, -1738, -1738,  3088, -1738,  1435, -1738, -1738,
   -1738, -1738, -1738,   120, -1738, -1738, -1738,  1134, -1738, -1738,
   -1738,  1184, -1738, -1738, -1738, -1738, -1738, -1738, -1738,  1500,
    1184, -1738,  1429, -1738,  1787, -1738, -1738, -1738,   864, -1738,
    1211,   961, -1738,    81,   716,   647,   111,   111,  4418,   487,
    1176,   862,  1699, -1738, -1738,  1831, -1738,  1660, -1738, -1738,
   -1738, -1738,  1586, -1738,  1025,    93,   715,   849,  1404,  1717,
   -1738,  1412,  1211,   832, -1738,   241, -1738, -1738, -1738,  4546,
    1232,   715, -1738, -1738, -1738, -1738,   -79,  1025,  4418,   520,
    1441,  1836,  1025,   633, -1738, -1738, -1738,  1539,  1540, -1738,
   -1738,  1137, -1738,     7, -1738,   -42, -1738, -1738, -1738,  1232,
    1679, -1738, -1738,  1253, -1738, -1738,  1232, -1738, -1738, -1738,
   -1738,  1543,  1154,  1232,  1709, -1738, -1738,  1543, -1738,  1253,
   -1738, -1738, -1738, -1738, -1738,  1025, -1738,  1025, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738,  1025, -1738, -1738,
    1708, -1738,  1647, -1738,   647,  1381,   647, -1738,  1210, -1738,
   -1738,   929,   878,   878,  1355,  1355,  1355, -1738,  1141,  1451,
   -1738,  1025, -1738,  1564, -1738, -1738,  1626, -1738, -1738, -1738,
    1232, -1738, -1738,  1232, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738,    43, -1738, -1738, -1738,  1675, -1738, -1738, -1738,   115,
     115,   115, -1738, -1738, -1738, -1738, -1738,  1245,  1384,  5124,
   -1738,  1025,  1245,  1245,  5171, -1738,  1245,  1245,  1245,    85,
    1245,  1245, -1738, -1738,  1590,  4418, -1738,   111, -1738, -1738,
     484,   738, -1738, -1738,  3705, -1738,   663,    36, -1738, -1738,
   -1738, -1738,  1048, -1738,  1528, -1738,  1510, -1738, -1738, -1738,
   -1738, -1738, -1738,   472,   472,   472,   472,  1232, -1738, -1738,
   -1738, -1738,  1193,  1232, -1738, -1738, -1738, -1738,   113, -1738,
    1182, -1738, -1738, -1738, -1738, -1738, -1738,  4546, -1738,  4546,
     120, -1738, -1738, -1738,  3088, -1738,  1025,  1735,  1426,   788,
    1753,  1427,   204,  1211, -1738, -1738,  1815, -1738, -1738, -1738,
   -1738,   961, -1738,  1690, -1738,  1232,  1587, -1738, -1738,  1381,
     111, -1738,  4546,   142,   483, -1738, -1738, -1738,  1025,  4546,
     565, -1738, -1738, -1738,  1725,  1604, -1738,  1726, -1738,  1630,
   -1738, -1738, -1738, -1738,  1412, -1738, -1738, -1738,  1609,  1729,
    1591,  1575,  1384, -1738,  4546,   204, -1738,  1592, -1738,  1211,
   -1738,  1761,  1485, -1738, -1738,  1134, -1738,   800,  1874, -1738,
    1032, -1738, -1738, -1738,  1253,  1766,  1663,  1817,  5002,   220,
    1232, -1738, -1738,   220, -1738,  1232,  1293, -1738, -1738, -1738,
    1444, -1738, -1738, -1738,  1232, -1738, -1738, -1738,  1232, -1738,
   -1738, -1738, -1738,   220,   220,    66,    66, -1738, -1738, -1738,
   -1738, -1738,  1450, -1738,  1200, -1738, -1738, -1738,   929, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738,  1184,  1731,  1184,  1733, -1738, -1738,  4546, -1738, -1738,
   -1738, -1738, -1738,  1762, -1738, -1738, -1738, -1738, -1738, -1738,
    1626,  1626,  1626,  1626,   220, -1738, -1738,   220,    66,    66,
   -1738, -1738, -1738,  4418,  1562,  4418,  1567, -1738, -1738, -1738,
   -1738, -1738,  1756, -1738,   788, -1738,  1794, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738,   204,  1137, -1738, -1738,  1137,    -3,
    1025, -1738,  1232,  4418, -1738, -1738,   928,  3713, -1738,  1849,
    1659,  1683,   444, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738,  1025,  1165, -1738, -1738,
   -1738,  1760,  1645,  1025,  1450,  4418, -1738,  1836, -1738,  1374,
    1811,  1374,  1591,   664, -1738, -1738,  1759, -1738,  1646, -1738,
   -1738, -1738,   415, -1738, -1738,  1232,  1823,  1694, -1738,  1099,
   -1738,  1713,  1118,  1492,  1727,  1480,  1232,  1142,  1232,  1025,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738,  1530, -1738, -1738, -1738, -1738,   836, -1738, -1738,
   -1738, -1738, -1738, -1738,   542, -1738,   555, -1738, -1738,  1444,
   -1738,  1025,   524, -1738, -1738, -1738,   220, -1738, -1738, -1738,
   -1738, -1738, -1738,  1184, -1738,  1184, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738,  4546, -1738,  4546, -1738, -1738, -1738, -1738, -1738,  1872,
    1137,  1137, -1738,  1516,  1616,   862,   413, -1738, -1738, -1738,
   -1738,  1580,  4546, -1738,  1232,   895,  1685, -1738,  1687, -1738,
   -1738, -1738, -1738, -1738, -1738,  1025, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
    1025,  1374, -1738,  1025,  1783, -1738, -1738, -1738, -1738, -1738,
     862, -1738, -1738, -1738, -1738, -1738, -1738, -1738,  1121,  1253,
    1232,  1232,  1757, -1738,  1232, -1738, -1738, -1738, -1738,   187,
   -1738,  1232, -1738,  1025,  1025,  1091,  1754, -1738,  1642,  1253,
     836, -1738, -1738, -1738, -1738, -1738, -1738,   220, -1738, -1738,
   -1738, -1738,   220, -1738,  1025, -1738,  1121, -1738, -1738, -1738,
   -1738,  1450,  1450, -1738,  4546,  1137, -1738,  4546,  1232,   862,
     862,  1625, -1738,  1025, -1738,  1513,  1025,  1793, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738,  1025, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738,  1253,  1253,  1232,
   -1738,  1253, -1738,  1253, -1738,  1384, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738,  4546, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738,   114,   862,  1232,
   -1738, -1738,  1025, -1738, -1738, -1738, -1738, -1738, -1738,  1253,
   -1738, -1738, -1738,  1889, -1738,   114, -1738, -1738,  4546, -1738,
   -1738
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1738, -1738, -1738, -1738,  1933, -1738, -1738, -1738,    50, -1738,
   -1738, -1738, -1738, -1738,  1588, -1738, -1738, -1738,  1235, -1738,
   -1738,    37,  1918, -1738, -1738,  1890,   699, -1738, -1738, -1738,
   -1738, -1738,  1755,  1814, -1738, -1738,  1771,   476, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738,  1763, -1738, -1738, -1738, -1738,
    1741, -1738, -1738, -1738, -1738, -1738,   223,   622, -1738, -1738,
   -1738, -1738,  1440, -1738, -1738,  1358,   802, -1738, -1738, -1738,
   -1738, -1738, -1738,  1515, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738,  1821, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,   598, -1738,
     591,   809, -1738, -1738, -1738, -1738, -1738,  1003,    67, -1738,
    1362, -1738, -1738, -1738, -1738, -1738, -1738,   118, -1738, -1738,
    1746, -1738,  1859, -1738, -1738, -1738, -1738,  1595, -1738, -1738,
    1864,   886, -1738, -1738, -1738, -1738,  1740, -1738,  1931,  1822,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,  1098, -1738,
   -1738, -1738,  1397, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738,   548, -1738, -1738, -1738,  1667,
   -1738, -1738,  -547, -1738, -1738,  -308, -1738, -1738, -1738,  -446,
   -1738, -1738, -1738, -1738, -1738, -1738, -1338, -1310,  1125, -1285,
   -1738,    79, -1738, -1738, -1738,   294,   297, -1738,   407, -1738,
     302, -1738,  -124, -1282, -1738, -1738, -1276, -1738, -1270, -1738,
   -1738, -1738,  1122, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738,  1433, -1738, -1738, -1738,  1026, -1738,
    -924, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,  -105, -1738,
   -1738, -1738, -1738, -1738, -1738,  -238, -1738, -1738, -1738, -1738,
     251, -1738, -1738, -1738, -1738, -1738,  1169, -1738, -1738, -1738,
   -1738, -1738, -1738,   152, -1738, -1738, -1738, -1738, -1738,  1879,
    1086, -1738,   230, -1738, -1738, -1738, -1738,  1514, -1738, -1738,
   -1738, -1738, -1738, -1738,  -893, -1738, -1738,   154, -1738, -1738,
   -1738, -1738,   950,   592,   595, -1738, -1738,   284, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738,   956, -1738, -1738,   252, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738,  -232, -1738,   215,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
     753, -1738, -1738,   757, -1738, -1738, -1738, -1738,   482,   213,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738,    33,   755, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738,   751, -1738, -1738, -1738,   201,
   -1738, -1738,   465, -1738, -1738, -1738, -1600, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1247,   939,
   -1738, -1738,   189, -1738, -1738,   446, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738,   694, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738,   731, -1738,   183, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,   931,
   -1738,   936, -1738, -1738,  1143, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738,   921,   430, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738,    10, -1738,   435, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738, -1738,   -70, -1738, -1188,
   -1738, -1738, -1283, -1116, -1152, -1738,   357, -1738, -1401, -1738,
   -1738, -1738, -1738,    11, -1738, -1738, -1738, -1738,  -104, -1738,
   -1738,   207, -1738, -1738, -1738, -1738,     6, -1738,  -435, -1737,
   -1738, -1738,   550, -1738,  -896, -1292,  -873, -1190, -1738, -1738,
   -1738, -1213, -1197, -1196, -1194, -1191,   -29,  -248,  -264,  -607,
    -977,  -885,   198,   963, -1048,   -84, -1738, -1107, -1738,  -830,
   -1738,   835,  -224,  -227, -1738, -1738,  -710,   623,  -853,  -988,
    -199,  -847, -1738, -1738,   464, -1058, -1216, -1001,  -852,  -960,
     389,  -630,  -195, -1738,  1096,  -178,  -673,  -676,  -312,  -336,
    -934, -1738, -1738, -1738, -1738, -1738,  1839, -1738,   439,   850,
   -1738, -1738, -1738, -1710,  1229,    45,  1765,   797,  -452, -1738,
    1022,  -410,  1479, -1738,  -631, -1738, -1119,  1108,  -422,   411,
   -1738, -1738,  -713, -1738, -1309,  -175,  -568,  -518,  -153,  -822,
   -1738,   668, -1368,  -820, -1094, -1738,  1280,  2047,  -860, -1738,
   -1738, -1738, -1738, -1738, -1738, -1738,   639, -1738,   192,  -712,
    1111,  -127
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1597
static const yytype_int16 yytable[] =
{
     122,   258,   478,   687,   302,   194,   301,   304,   560,   908,
    1145,  1257,   871,  1056,   876,   408,  1594,   616,   617,  1341,
    1039,   277,   278,   854,  1332,  1504,   283,   284,   285,   286,
     287,  1072,   289,   300,   292,   300,   300,   940,  1942,   300,
    1679,  1505,  1506,  1048,  1507,  1033,   105,  1508,   998,   999,
      22,  1244,  1740,  1741,  1033,  1066,   372,   446,  1357,  1087,
     376,   882,   378,  1325,  1043,   579,   194,  1078,  1680,  1098,
    1100,   389,  1133,   347,   389,   348,   122,  1638,   833,   450,
     357,  1547,   355,  1141,  1033,   811, -1560,  1117,   300,   165,
     360,  1279,   300,  1681,   300,  1228,  1682,  1270,  1078,  1279,
     165,  1416,  1683,   300,   369,   370,   300,   371,  1684,    92,
     963,  1004,  1793,   377,  1573,   165,  1078,  1078,   877,   382,
      89,  1787,  1968,  1557,  1601,   127,   596,   305,  1717,  1360,
     500,    85,   446,   435,  1385,  1737, -1518, -1522,   290,  1818,
     165,  1542,  1424,   447,   263,  1279,  1536,  1537,  1538,  1402,
     449,   826,   410,   105,   493,   415,   417,    54,   420,   403,
    2070,  1574,  1419,   186,  1935,   300,   462,  1372,   464,  1419,
     428,  1385,  2054, -1560,   429,   300,  1385,   434,   950,   834,
    1360,   165,   300,   403,    41,  1233,  1385,  1851,   485,   991,
      14,   436,    52,   461,  1211,   300,   972,   300,  1122,  1218,
    1585,   876,   266,   689,  2164,   613,   598,   175,   865,  1900,
     450,   958,   481,   867,  1385,  1233,  1267,  1156,   480,  1862,
     300, -1596,   395,   973,   974,    63, -1596,  1883,  1572,     4,
     529,   475, -1596,  1631,  1988,   389,   477,   389,   487,   561,
    1078,  1092,  1121,  2018,   489,  1042,  1780,  1373,    55,  1295,
      19,   495,  1713,     3,  1449,  1318,    41,   253,  1278,  1713,
   -1540,   530, -1596,   484,  1122,   250,  1713,   300,   300,   300,
     451,   884,    75,   839,   841,   520,  1330,  1901,  1575,  1902,
    -190,   614,   362, -1435,   575,  1687,    41,   812,   562,   833,
    1630,  1540,  1141,  1910,  1201,  1202,   867,  1233,   570,  1915,
    -191,  1308, -1522,  1425,  1042,    12,  1711,   363,  1952,   395,
    1189,   251,   468,   482,  1309,  1603,  1385,    13,   583,   584,
     176,  1794,  1588,   840,   842,  1360,    20,    16,  1576,  1286,
    1200,   813,    56,   696,   389,  1157,  1420,   868,   229,   986,
    1122,   599,  1279,   959, -1482, -1482,  1056,   817,   600,    41,
    1042,  1243,  1716,  1331,   818,  1333,  1863,     5,   610,   619,
    1381,  1969,   190,  1547,  1959, -1522,   300,   254,  1196,  1197,
    1628,   951,  1781,     4,  1385,  1203, -1522,  1268,  1522,  1186,
    1398,  -632,   106,  1056,  1450,   622,   608, -1567,   698,   698,
     834,  1509,   538,   682,  1777,   688,   866,  1421,  -190,   437,
     693,   451,   827,  1072,  1421, -1545,    55,  1173,   354,   608,
    2160,    64,   620,  2161,  1056,  1812, -1522,   259,  -191,   952,
    1539,  1541,  1796,   960,  1386,   -31,   494,   810,   975,   267,
     404,  2165,   815,  1932,   816,   297,   269,   820,  2279,   821,
     438,   823,   824,  1587,   264,  1327,   830,   439,  1361,   297,
    1559,   297,  1589,  1898,   407,  1602,   356, -1522,  1795,   856,
     828,  1386,  1056,  1826,  1766,   275,  1386,  1936,   690,   297,
     853,  1970,  1005,  -630,  1765, -1522,  1386,  1744, -1540,   152,
    1598,   107,   437,    89,    63,   578, -1522,  1618,   861,   862,
      56,  1622,  1623,  1399,  1625,  -632,  1953, -1518,   275,  1361,
    1629,     5,   190,   297,  1386,  1189,  1189,  1189, -1522,   597,
     297,    86,   869,  1613, -1522,  1189,  1577,   501,  1271,   440,
     297,  1387,  1836,   438,  1543,   981, -1522,  1640,  1544,   190,
     439,  1327, -1520,   867,   297,   594,  1189,  1989,  1189,   297,
    1189,  2128,  1435,  1854,  1189,  1189,  1189,  1189,  1189,  1189,
    1189,  1189,   297,   297,  1875,   997,   297,   297,  1747,  1050,
     190,   177,  2265, -1474,  1713,   883,  1056, -1522,  1287,   175,
    2091,  1920,   317,  1757,  1186,  1186,  1186,  1710,  1093,  1163,
    2043,  1427,   441,  1050,  1186,  1204,   955,  -630,  1434,   962,
     976,   106,  2150,   485,  2152,  2342,   965,   966,  2092,  1279,
    2270,  1758,   440,   971,  -190,  1186,  1386,  1186, -1596,  1186,
    1327,   442,  -776,  1186,  1186,  1186,  1186,  1186,  1186,  1186,
    1186,   300,  2169,  2093,  -191,   300,  2095,  1376,   300,   300,
    1547,  1288,  2096, -1545,    75,   300,   954,  1334,  2097,    88,
    1961,  1207,  2176,    23,  1361,  -210,   297,  1819,  1556,  1385,
    1190,   356,   443,  2197,  2198,  1777,   262,   980,  1335,  1164,
     498,  1825,   297,  1122,  1386,   441,  1338,  1827,  2110,  2056,
      64, -1596,  1327,   492,  1852,  1688,   297, -1518,    26,   521,
     386,  1773,   176,   297,  2177,  1709,   928, -1567,  1198,  1609,
     107, -1596,   426,  1609,   442,  1389,  1390,  1391,  1392,  1046,
    1393,  2271,  1062, -1480,  2178,  1698,    30,  1884,  2216,  1008,
      18,  2224,  1189,  1189,  1189,  1189,  1189,  1189,  1189,   437,
    1095,    65,  1185, -1596,  1110,    29,  1114,  1155,  1114,  1120,
    1367,  1095,  1144,  1850,  1327,   443,   262,   409,  1938,  1939,
    1940, -1596,   416, -1596,  1166,  1514,  1114,   601,  1768,   307,
    2200,  1697,  2203,  1389,  1390,  1391,  1392,   387,  1393,   300,
     438, -1478,  1689, -1596,  2030,  1529,   177,   439,  1962,  1050,
      91,   427,  1877,  1253,   956,  2013,   300,   485,   485,  1960,
    1530,  1186,  1186,  1186,  1186,  1186,  1186,  1186,   310,  2243,
      33,  1208,  1111,   316,  1193,   150,  1746,  1168,  2162,   929,
    1562,  2063,  2248,  1563,  1564, -1596,  1177,  1784,  1253,   300,
     300,     5,  1914,  1941,   623,  1058,  2126,  2126,  1946,  1947,
    1339,   279,  1949,  1950,  1951, -1596,  1954,  1955,   175,   288,
    2205,  2058,     5,   175,  2186,  1253,  1112,  1368,  1115,   440,
    1993,  2244,  1995,  1135, -1518,  1190,  1190,  1190,   295,  1828,
    2187,  2188,  1147,  2189,  2249,  1190,  2190,   297,  1831,   398,
    2323,  2324,  1279,  2110,  2141,  2142,  2143,  2144,  1253,  2126,
    2126,  2206,   190,  1573,  1688,  2023,  1190,    34,  1190,  2207,
    1190,  2179,  1436,   325,  1190,  1190,  1190,  1190,  1190,  1190,
    1190,  1190,  2287,    75,  1963,  1978,  1979,   356,    75,  1515,
     367,   368,   441, -1534,  1327,  1327,    36,  2055,   374,   375,
     858,    32, -1518,  1530,   381,   384,  1846,  1382,  1383,  1384,
    1574,  1991,  1120,   885,   190,   119, -1534,  1395,  1523,   326,
    1999,   442,  1994, -1596,  1996, -1596,  1327,    38,   877,  1386,
    2304,   176,  1966,   843,   327,   424,   176,   469,  1998,  1300,
    1431,  1785,  2208,  2115,  2064, -1596,  1438,  1440,  1441,  1443,
    1284,  1689,  1446,  1448,  1366,  2217,   425,  1056,   437,  1246,
    1837,  1786,   443,  2123,  2124,    44,   485,   139,  1111, -1536,
    1561,  1524,    93,  1562,   328,  1746,  1563,  1564,  1369,   140,
    1301,  2245,  2246,   844,   307,  1375,  1163,  2041,  1302,  1056,
     845,  1847, -1596,   452,  2250,  2251,   190,   938,   300,   438,
     141,    49,  2029,  1523,   174,  2210,   439,  1838,   142,  1517,
      50,  1862,  1964,    53,  2145,  1403,  1404,  2146,  1389,  1390,
    1391,  1392,   859,  1393, -1518,   250, -1475,  1575,   261,  2346,
    2127,  1565,  1566,   358,    94,  1699,  1319,   847,  1690, -1540,
     846,    59,  1190,  1190,  1190,  1190,  1190,  1190,  1190,  -991,
    1567,  1568,  -210,  2130,  2065,  1219,  1524,  1405,  1654,  1406,
   -1540,  1303,   356,  1189,   190,   297,  1164,   146,  1189,    60,
    2344,   251,  2140,  1358,    95,  1046,    96,  1576,   440,  1868,
    1240,  1149,  2147,  2148,  2238,   143,    41,   848,  2349,  2149,
    -991,   329,  1313,  1407,  1408,  1409,   119,  -991,  1523,  1869,
     356,  1518,  2218,   330,    62,  1046,    45,  2269,  1150,  1521,
    2136,  1116,  2185,   195,  1701,  1702,  1703,  1704,  1705,  1706,
    1708,  1845,   147,   148,   618,  2239,   190,   196,   197,  1153,
    2180,  2181,  1186,  1647,  1647,  1599,   863,  1186,  1314,  2183,
    1410,   441,  1411,  -345,  -345,    46,   437,  1327,  1863,  2012,
    1412,  1524,  1046,    47,   190,  1327,  2256,   864,  2170,   198,
    1644,  1867,  1600,   468,   503,   300,   300,  1924,   272,  -991,
     442,  2308,  2309,  1428,  1839,  1068,  1879,  1432,  2171,  1069,
    1751,   504,  1607,  1754,   602,  1444,  1445,   438,  1759,   607,
      68,   331,   332,    61,   439,  1073,  1074,  2310,   199,   200,
       5,   201,  2012,  1327,   333,  1797,   334,    72,  1798,  1075,
     202,   443,  2328,   809,  1565,  1566,  1799,  1800,  1801,  1635,
      75,  1607,   505,  1636,  1413,    79,  1616,    10,  2257,   506,
    1617,    10,  -991,  1567,  1568,   504,  2260,    81,  1122,  2132,
      82,  2134,   249,   411,   103,   412,   249,  1389,  1390,  1391,
    1392,  2263,  1393,   203,   204,  1076,  2261,  2234,  2262,  1394,
     454,  -991,   455,   115,   205,  1577,   440,  1651,  1652,   942,
    1012,  1349,   525,  1350,  1049,   526,   505,  2320,   116,  2282,
    1064,  2283,  2321,   506,   117,  1081,  1082,  1271,  2284,  1550,
     527,  1081,  1089,  1091,   119,   507,  -991,  1911,  1049,  1912,
     528,   508,  -991,  1971,  1081,  1972,  1046,   335,  2291,  2292,
     943,  1460,  1461,  1089,  1146,  2275,  1148,   944,  1050,  1391,
    1392,  2022,  1393,  1389,  1390,  1391,  1392,   336,  1393,   441,
    1802,  2012,   319,   320,   263,  1749,  1985,   125,  1986,   206,
    1462,  1901,  2332,  1902,  2293,  2294,  1463,   129,  1803,  1389,
    1390,  1391,  1392,   134,  1393,   508,   130,  1700,   442,  1738,
    2223,   131,  1840,   132,   509,  1188,  1804,   133,  1389,  1390,
    1391,  1392,   136,  1393,   137,  2311,  2312,  1465,  2227,  2228,
     144,  1466,  2335, -1427, -1427, -1427, -1427,   155,   156,   945,
     171,  1414,   157,   297,   172,  1213,   437,   173,   186,   443,
     227,   224,   228,  1190,   229,   231,  1647,  2325,  1190,   232,
    2326,  2258,   234,  2259,  1805,   235,  2313,  2314,   509,   237,
     241,   510,   511,   242,   243,  1389,  1390,  1391,  1392,   257,
    1393,  1245,  1415,  1753,   512,  1878,    41,   438,   300,  2255,
     271,   274,  1014,   275,   439,   867,  1261,  1262,  1263,  1264,
    1919,   281,   946,  1853,   207,   280,   290,   297,  1081,  2343,
     303,   305,  1806,   307,  1904,  1907,  1081,  1285,   312,   313,
     314,  1909,   349,   529,  1930,  1944,   350,   352,  1913,   356,
    1948,  1916,   300,   359,  1049,   361,   364,   195,   512,  1881,
     365,  2350,   373,   390,   208,   391,  1881,   392,   400,   401,
    1326,   196,   197,   418,   530,   421,   300,   423,  1081,   431,
     430,   531,  1081,   448,  1945,  1807,   440,   463,  1015,   466,
     471,  1344,   947,  -362,  1285,  1808, -1426, -1426, -1426, -1426,
     473,   488,   532,   198,  1017,  1933,   476,   518,  1934,   490,
    1389,  1390,  1391,  1392,   209,  1393,   300,  1245,  1756,   522,
    1089,  1980,  1981,  1982,  1983,   563,   571,   533,   576,   573,
    1188,  1188,  1188,   534,   580,   582,  1389,  1390,  1391,  1392,
    1188,  1393,   199,   200,  1761,   201,   603,   604,   606,   441,
    1389,  1390,  1391,  1392,   202,  1393,  1326,  1809,  1927,   608,
     535,  1188,  1249,  1188,   611,  1188,   621,   536,   684,  1188,
    1188,  1188,  1188,  1188,  1188,  1188,  1188,   190,   442,   686,
     537,  1480,  1984,   822,  1482,  1483,   694,   701,  1987,   702,
    1018,   831,   806,   319,   838,   849,   851,   203,   204,   857,
     888,   437,  -843,   889,   264,   538,   932,   539,   205,  1389,
    1390,  1391,  1392,   297,  1393,   540,   613,  2129,   964,   443,
     967,  2302,   983,   970,   984,  -215,   986,   992,   989,   994,
    2020,  1019,  1000,  2230,  1003,  1326,  1006,  1051,  1020,  1067,
    1009,  1037,   438,  1059,  1021,  1081,   541,  1022,  1010,   439,
    1084,  1152,  1169,  1154,  1175,  1178,  1160,  1194,  1597,  1191,
     877,  1205,  1212,  1214,  1216,  1245,  1719,  1220,  1720,  1234,
    1221,  1721,  1610,  1229,  1222,  1223,  1224,  1236,  1225,  1081,
    1023,  1722,  1239,   206,  1226,  1241,  2074,  2026,  1227,  1247,
    1255,  1626,  1253,  2032,  1258,  2114,   542,  1326,  1265,  1277,
    2116,  1281,  1296,  1634,  1297,  1299,  1306, -1429,  1310,  2121,
    1312,  1311,  1316,  2122,  1321,  1122,  1323,   165,  1345,  1348,
    1352,   440,  1285,  1354,  1455,  1456,  1457,  1355, -1553,  1379,
     468,  1400,  1458,  1396,  1417,  1430,  1451,  1188,  1188,  1188,
    1188,  1188,  1188,  1188,  1510,  1437,  1452,  1042,  1024,  1533,
    1548,  1015,  1553,  2167,  1571,  1586,  1604,  1612,  1590,  1326,
    1619,  1620,  1627,  1632,  1642,  1645,  1649,  1017,  1714,  1393,
    1459,  1715,  1718,  1738,  1750,  1420,  1752,  1755,  1767,  1748,
    1760,  1769,  1772,  1762,   441,   300,  1790,  1524,  1813,  1815,
    1817,  1829,  1832,  1025,  1026,  1821,  1833,  1855,   207,  1858,
    1859,  1081,  1870,  1871,  1885,  1886,  1894,  2168,  1896,  1690,
    1872,  1723,  1905,   442,  1977,  1928,  1724,  1976,  1957,  1027,
    2001,  2003,  2009,  2007,  2014,  2017,  2035,  1863,  2038,  1725,
    2040,  2045,  2021,  2048,  2059,  2053,  2057,  1028,   208,  2061,
    2050,  2071,  2075,  2076,  2078,  1029,  2118,  2133,   297,  2135,
    2151,  2137,  2155,  1018,   443,  2153,  2158,  2254,  2172,  2173,
    2219,  2174,  1250,  1778,  1779,  2192,  2201,  2213,  1460,  1461,
    2065,  2233,  2194,  2235,  2220,  2221,  2225,  1726,  2232,  2231,
    2087,  2264,  2266,  2268,  2274,  2280,   300,  2281,   209,  2242,
    2289,  2299,  2329,  2333,  2316,  2317,  2331,  1462,  2348,    15,
      28,   293,   433,  1463,    74,  1047,   193,  1021,   273,   260,
    1022,   270,   294,  1614,   595,   808,  1359,   226,  1014,   517,
    1643,   867,  1648,  1162,  1362,  1727,  1464,  2073,   151,  1326,
    1326,  2024,   819,   296,  1465,  1081,  1081,   153,  1466,   309,
      67,   699,   245,  1023,  1007,   402,   990,  2094,   465,  1728,
    1926,  1923,  1849,  1861,  1922,  2253,  1002,  2237,   624,  2276,
    1172,  1326,  2319,   170,  1015,   982,  1967,  2307,  1467,  1468,
     585,  2027,  1260,  1729,  1469,  1743,  1882,  1742,  1730,  1937,
    1017,  1891,  1891,  1269,  1470,  1990,  1965,   389,  1731,  1555,
    1551,  1471,  1732,  1997,  1015,  1824,  1472,  2157,  1570,   300,
    1582,  2296,  2016,  1834,  1305,  2297,  2298,  2028,  1860,  2301,
    1017,  1024,  1641,  1049,  1473,  1611,  2303,  2044,  1328,   300,
    1343,  2318,  2242,  1892,  1917,  1329,  1918,  2199,  1893,  1134,
    1931,  2278,  2037,  2204,  2215,  1512,   910,  1792,  2330,  1876,
    1320,  -934,  1899,  1192,  -934,   318,  1454,  -934,  -934,  -934,
    1733,  1584,  1276,  2327,   414,   996,  1025,  1026,   825,  1102,
    1734,  1615,  1195,  2322,    76,  1771,  1018,   969,  2117,     0,
       0,     0,  1199,     0,     0,     0,     0,     0,     0,  2337,
    2338,     0,  1027,  2340,  2339,  2341,   468,     0,  1245,  1245,
    1245,     0,  1046,  -934,     0,     0,  1018,     0,  1188,     0,
    1028,     0,     0,  1188,     0,     0,     0,   437,  1029,     0,
    1046,   297,     0,     0,  2345,     0,  1081,  -934,  1103,     0,
    1021,  2347,     0,  1022,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -934,     0,     0,     0,  1019,     0,     0,
       0,     0,     0,     0,  1020,   468,     0,     0,   438,     0,
    1021,     0,     0,  1022,     0,   439,  1023,     0,     0,     0,
    1474,  1475,  1476,  1477,  1478,     0,  1479,     0,  1480,  1481,
       0,  1482,  1483,     0,     0,  2000,     0,     0,     0,     0,
       0,  2011,  1326,     0,     0,     0,  1023,     0,     0,     0,
    1326,  -934,  -934,     0,     0,     0,     0,     0,     0,  1081,
       0,     0,     0,     0,   468,     0,     0,  1597,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -934,
    -934,     0,     0,     0,  1024,     0,  -934,   440,     0,     0,
    -934,     0,     0,     0,  2011,     0,     0,     0,  1326,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -934,
       0,     0,     0,     0,  1024,     0,     0,  -934,  2112,     0,
    -934,  -934,  2112,     0,     0,     0,     0,  -934,     0,  1025,
    1026,  -934,     0,  -934,     0,     0,  -934,     0,  -934, -1596,
       0,     0,  2112,  2112,     0,     0,     0,     0,     0,     0,
     441,  -934,  -934,     0,     0,  1027,     0,  -934,     0,  1025,
    1026,     0,     0,     0,     0, -1042,     0,  -934,     0,  -934,
       0,     0,     0,  1028,  -934,     0,  1616,     0, -1042,   442,
    1617,  1029,     0,   190,   297,  1027,     0,     0,     0,     0,
       0,     0,     0,  2112,     0,     0,  2112,  -934,     0,     0,
       0,     0,     0,  1028,     0,     0,     0,     0,     0,     0,
    -934,  1029,     0,     0,   297,     0,     0,     0,     0,     0,
     443,     0,     0,  2011,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -934,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -357,   626,     0,     0,  1089,     0,     0,     0,     0,
       0,     0,  2196,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   627,  -934,     0,     0,     0,     0,     0,     0,
       0,  2112,  -934,  -934,     0,   628,     0,     0,   629,   630,
     631,   632,   633,   634,   635,     0,     0,     0,  2236,     0,
       0,     0,  -934,     0,     0,     0,     0,     0,  -934,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   636,  -934,   637,   638,   639,
     640,   641,   642,     0,  -934,  2112,     0,  -934,     0,     0,
       0,     0,     0,  -934,  -934,  -934,     0,     0,     0,  -934,
       0,  -934,     0,  -934,  -934,  -934,  1014,     0,     0,   867,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   643,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -357,     0,     0,     0,
    -357,     0,     0,     0,  1285,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2286,
       0,     0,  2288,     0,     0,     0,     0,     0, -1540,  -357,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1015,     0,  -357,     0,     0,     0,     0, -1540,
       0,     0,  2305,     0,     0,     0,     0,     0,  1017,     0,
       0,     0,   644,  1015,     0,     0,  2112,     0,     0,     0,
       0,  2112,  1138,     0,     0,    41,     0,     0,   645,  1017,
       0,     0,     0,     0, -1577,     0,     0,     0,  -357,  -357,
       0,     0,     0,     0,     0,  1089,  -357,   646,     0,     0,
    -357,     0,     0,     0,     0,     0,  2336,     0,     0,     0,
       0,     0,     0,     0,   647,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -627,   586,     0,  -667,     0,  -667,
       0,     0,     0,     0,  -667,     0,     0,   648,     0,     0,
       0,     0,  -667,     0,  1018,     0,     0,     0,     0,     0,
       0,  1285,   649,     0,     0,   437,     0,     0,  1102,   650,
       0,   651,     0,     0,     0,  1018,     0,     0,  -357,     0,
    1342,     0,  -357,     0,   652,  -667,  -667,     0,     0,     0,
       0,     0,     0,  -667,   653,  1019,     0,     0,     0,     0,
       0,   654,  1020,  -357,     0,  -667,   438,     0,  1021,  -667,
       0,  1022,     0,   439,     0,     0,     0,     0,     0,     0,
       0,  -667,  -357,     0,     0,  -357,     0,  1047,     0,  1021,
       0,     0,  1022,     0,     0,     0,     0,     0,   655,     0,
     656,   657,   658,     0,  1023,  -667,     0,     0,     0,     0,
       0,     0,  -667,  -667,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   659,  1023,     0,     0,     0,  -627,
       0,     0,     0,  -627,     0,     0,     0,   586,     0,  -667,
       0,  -667, -1577,  -667,     0,   440,  -667,     0,     0,     0,
     660,   661,   662,     0,  -667,  -667,     0,     0,     0,  -667,
       0,     0,     0,   663,     0,     0,   664,     0,     0,     0,
       0,     0,  1024,  -667,     0,  -357,     0,  -627,     0,     0,
    -667,     0,     0,  -667,  -667,     0,  -357,  -667,  -667,     0,
       0,  -667,     0,  1024,     0,  -667,     0,     0,  -667,     0,
    -667,     0,     0,  -667,     0,     0,     0,  -667,   441,     0,
       0,  -667,     0,     0,     0,     0,     0,  1025,  1026,     0,
       0,     0,     0,  -667,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   442,  1025,  1026,
    -667,     0,     0,  1027,  -667,     0,  -667,  -667, -1596,     0,
       0,     0,     0,  -667,  -667,  -667,     0,     0,     0,     0,
       0,  1028,   700,     0,  1027,     0,     0,     0,     0,  1029,
       0,     0,   297,     0, -1042,     0,  -667,     0,   443,     0,
       0,     0,  1028,     0,     0,  -667,     0, -1042,     0,     0,
    1029,  -667,   190,   297,     0,     0,     0,  -667,     0,     0,
       0,  -667,     0,     0,     0,  -627,     0,     0,     0,     0,
       0,     0,  -667,     0,     0,  -667,     0,     0,     0,     0,
       0,  -667,  -667,     0,     0,  -667,  -667,     0,     0,     0,
       0,     0,     0,  -667,  -667,     0,     0,     0,     0,  -667,
    -667,  -667,  -667,     0,     0,  -667,     0,     0,     0,  -667,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -667,
       0,     0,     0,     0,     0,     0,     0,     0,  -667,     0,
       0,     0,     0,     0,     0,     0,     0,  -667,     0,  -667,
    -667,     0,  -667,  -667,     0,  -667,  -667,     0,  -667,     0,
    -667,     0,     0,     0, -1510,  -667,     0, -1510,     0,     0,
   -1510, -1510, -1510,     0,     0,  1270,  -667,     0,     0, -1510,
       0,  -667,     0,     0,     0,     0,  -667,     0,  -667,     0,
       0,     0,     0,     0,     0,     0,     0,  -667,     0,     0,
       0,     0,     0,  -667,     0,     0,   587,     0,     0,  -667,
       0,     0,     0,     0,     0,     0, -1510,     0,     0,  -667,
       0,     0,     0,     0,  -667,     0,     0,     0,     0,     0,
       0,     0,     0,  -667,     0,     0,     0,     0,     0,     0,
   -1510,     0,     0,     0,     0,     0,  -667,     0,     0,     0,
       0,  -667,     0,  -667,     0,     0, -1510,     0,     0,     0,
    1014,  -667,     0,   867,     0,     0,  1489,  1490,  1491,     0,
       0,  -667,     0,     0,     0,     0,     0,     0,     0,     0,
    -667,     0,     0,     0,     0,     0,     0,     0,     0,  -667,
       0,  -667,  -667,     0,     0,  -667,     0,  -667,     0,     0,
       0,     0,  -667,   867,     0,     0,     0,     0,     0,     0,
       0,     0,  1492,     0, -1510, -1510,     0,     0,  -667,     0,
       0,     0,     0,  -667,     0,     0,     0,     0,  -667,     0,
       0,     0,     0,     0,     0,     0,  1015,     0,     0,  -667,
       0,     0, -1510, -1510,     0,     0,     0,     0,   587, -1510,
       0,  -667,  1017, -1510,     0,     0,     0,     0,     0,     0,
       0,  -667,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0, -1510,     0,     0,     0,  1015,     0,     0,     0,
   -1510,     0,     0, -1510, -1510,     0,     0,     0,     0,     0,
   -1510,     0,  1017,     0, -1510,     0, -1510,     0,     0, -1510,
       0, -1510,     0,     0,     0,     0,     0,     0,     0,     0,
    1460,  1461,     0,     0, -1510, -1510,     0,     0,     0,     0,
   -1510,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   -1510,     0, -1510,     0,     0,     0,     0, -1510,  1018,  1462,
       0,     0,     0,     0,     0,  1463,     0,     0,     0,   437,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   -1510,     0,     0,     0,     0,     0,     0,     0,  1493,     0,
       0,     0,     0, -1510,     0,     0,  1465,     0,  1018,  1019,
    1466,     0,     0,     0,     0,     0,  1020,     0,     0,   437,
     438,     0,  1021,     0,     0,  1022,     0,   439,     0,     0,
   -1510,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1494,  1495,     0,     0,     0,     0,  1496,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1497,     0,  1023,     0,
     438,     0,  1021,  1498,     0,  1022, -1510,   439,     0,     0,
       0,     0,     0,     0,     0, -1510, -1510,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1499,     0,     0,     0,
       0,     0, -1510,     0,     0, -1510, -1510,     0,  1023,   440,
       0, -1510,   703,     0,   704,     0,     0,     0,     0,   705,
       0,     0,     0,     0,     0,     0,     0,   706,     0, -1510,
       0,     0,     0,     0,     0,     0,  1024, -1510,     0,     0,
   -1510,     0,     0,     0,     0,     0, -1510, -1510, -1510,   440,
       0,     0, -1510,     0, -1510,     0, -1510, -1510, -1510,     0,
     707,   708,     0,     0,     0,     0,     0,     0,   709,     0,
       0,     0,   441,     0,     0,     0,  1024,     0,     0,     0,
     710,  1025,  1026,     0,   711,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   712,     0,     0,     0,
       0,   442,     0,     0,     0,     0,     0,  1027,     0,     0,
       0,     0,   441,     0,     0,     0,     0,     0,     0,     0,
     713,  1025,  1026,     0,     0,  1028,     0,   714,   715,     0,
       0,     0,     0,  1029,     0,     0,   297,     0,     0,     0,
       0,   442,   443,  1500,  1501,     0,     0,  1027,  1502,     0,
    1480,     0,  1503,  1482,  1483,     0,     0,     0,   716,     0,
       0,     0,     0,     0,     0,  1028,     0,     0,     0,     0,
     717,     0,     0,  1029,   718,     0,   297,     0,     0,     0,
       0,     0,   443,     0,     0,     0,     0,     0,   719,     0,
       0,     0,     0,     0,     0,   720,     0,     0,   721,   722,
       0,     0,     0,     0,     0,     0,   723,     0,     0,     0,
       0,     0,     0,   724,     0,   725,     0,     0,   726,     0,
       0,  -799,     0,     0,  -799,     0,   703,     0,   704,     0,
       0,     0,     0,   705,     0,     0,     0,     0,     0,     0,
       0,   706,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   727,     0,     0,     0,   728,
       0,   729,     0,     0,   165,     0,     0,     0,   730,     0,
       0,     0,     0,     0,   707,   708,     0,     0,     0,     0,
       0,     0,   709,     0,     0,     0,     0,     0,     0,     0,
       0,   731,     0,     0,   710,     0,     0,  -799,   711,     0,
       0, -1522,     0,     0,     0,     0,   732,     0,     0,     0,
     712,     0,     0,  -799,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   733,     0,     0,
       0,     0,     0,     0,   713,     0,   734,     0,     0,     0,
       0,   714,   715,     0,     0,     0,     0,     0,     0,   735,
       0,     0,     0,     0,   736,     0,   737,     0,     0,     0,
       0,     0,     0,     0,   738,     0,     0,     0,     0,     0,
       0,     0,   716,     0,   739,     0,     0,     0,     0,     0,
       0,     0,     0,   740,   717,     0,     0,     0,   718,     0,
       0,     0,   741,     0,   742,   743,     0,     0,   744,  -799,
     745,     0,   719,     0,     0,   746,     0,     0,     0,   720,
    -799,     0,   721,   722,     0,     0,     0,     0,     0,     0,
     723,   747,     0,     0,     0,     0,   748,   724,     0,   725,
       0,   749,   726,     0,     0,     0,     0,     0,     0,     0,
    -799,     0,   750,  1014,     0,     0,   867,  -799,     0,     0,
       0,  -799,     0,  -799,   751,     0,  -799,     0,  -799,     0,
       0,     0,     0,     0,   752,     0,     0,  1207,     0,   727,
       0,     0,     0,   728,     0,   729,     0,  1014,     0,     0,
     867,     0,   730,     0,     0,     0,     0,     0,     0,  -799,
       0,     0,     0,     0,  -799,     0,     0,     0,     0,  1014,
       0,     0,   867, -1518,     0,   731,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1015,
     732,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -799,     0,     0,     0,     0,  1017,     0,     0,     0,  1014,
   -1522,   733,   867,     0,     0,     0,     0,     0,     0,     0,
     734,     0,     0,  1015,     0,     0,     0,  -799,     0,     0,
       0,  1014,     0,   735,   867,  1016,     0,     0,   736,  1017,
     737,     0,     0,     0,     0,  1015,     0,     0,   738,     0,
       0,     0,     0,     0,     0,     0,     0,  -799,   739,     0,
       0,  1017,     0,  -799,     0,     0,     0,   740,     0,     0,
       0,     0,  -799,  -799,     0,  1138,   741,     0,   742,   743,
       0,     0,   744,     0,   745,  1015,     0,     0,     0,   746,
       0,  1018,  -799,     0,     0,     0,     0,  1096,  -799,     0,
       0,  1017,   437,  -799,     0,   747,     0,  1015,     0,     0,
     748,     0,     0,     0,     0,   749,  -799,     0,     0,  1142,
   -1522,     0,     0,  1017,  -799,  1018,   750,  -799,     0,     0,
       0,     0,  1019,  -799,     0,     0,   437,     0,   751,  1020,
   -1518,     0,     0,   438,     0,  1021,     0,  1018,  1022,     0,
     439,     0,     0,     0,     0,     0,     0,     0,   437,     0,
       0,     0,     0,     0,     0,     0,  1019,     0,     0,     0,
       0,     0,     0,  1020,     0,     0,     0,   438,     0,  1021,
       0,  1023,  1022,     0,   439,     0,     0,  1018,  1019,     0,
       0,     0,     0,     0,     0,  1020,     0,     0,   437,   438,
       0,  1021,     0,     0,  1022,     0,   439,     0, -1518,  1018,
       0,     0,     0,     0,     0,  1023,     0,     0,     0,     0,
     437,     0,   440,     0,     0,     0,     0,     0,  1019,     0,
       0,  1014,     0,     0,   867,  1020,     0,  1023,     0,   438,
       0,  1021,     0,     0,  1022,     0,   439,     0,     0,  1024,
    1019,     0,     0,     0,     0,     0,   440,  1020,     0,     0,
       0,   438,     0,  1021,     0,     0,  1022,     0,   439,     0,
       0,     0,     0,     0,     0,     0,     0,  1023,   440,     0,
       0,  1014,     0,  1024,   867,   441,     0,     0,     0,     0,
       0,     0,     0,  1014,  1025,  1026,   867,     0,     0,  1023,
       0,     0,     0,     0,     0,  1024,     0,  1015,     0,     0,
       0,     0,     0,     0,   442,     0,     0,     0,   440,   441,
    1027,     0,     0,  1017,     0,     0,     0,     0,  1025,  1026,
       0,     0,     0,     0,     0,     0,     0,     0,  1028,     0,
     440,   441,     0,     0,     0,  1024,  1029,     0,   442,   297,
    1025,  1026,     0,     0,  1027,   443,     0,  1015,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1024,     0,  1015,
     442,     0,  1028,  1017,     0,     0,  1027,     0,     0,     0,
    1029,   441,     0,   297,     0,  1017,     0,     0,     0,   443,
    1025,  1026,     0,     0,  1028,     0,     0,     0,     0,     0,
       0,     0,  1029,   441,  1014,   297,     0,   867,     0,  1018,
     442,   443,  1025,  1026,     0,     0,  1027,     0,     0,     0,
     437,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   442,     0,  1028,     0,     0,     0,  1027,     0,
       0,     0,  1029,     0,     0,   297,     0,     0,     0,     0,
    1019,   443,     0,     0,     0,  1347,  1028,  1020,     0,  1018,
       0,   438,     0,  1021,  1029,     0,  1022,   297,   439,     0,
     437,  1018,     0,   443,     0,     0,     0,     0,     0,     0,
    1015,     0,   437,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1017,     0,     0,  1023,
    1019,     0,     0,     0,     0,     0,     0,  1020,     0,     0,
       0,   438,  1019,  1021,     0,     0,  1022,     0,   439,  1020,
       0,     0,     0,   438,     0,  1021,     0,     0,  1022,     0,
     439,     0,  1014,     0,     0,   867,     0,     0,     0,     0,
     440,     0,     0,     0,     0,     0,     0,     0,     0,  1023,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1023,     0,     0,     0,     0,     0,  1024,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1018,     0,     0,     0,     0,     0,     0,     0,
     440,     0,     0,   437,     0,     0,     0,     0,     0,     0,
       0,  1014,   440,   441,   867,     0,     0,     0,  1015,     0,
       0,     0,  1025,  1026,     0,     0,     0,  1024,     0,     0,
       0,     0,     0,  1019,  1017,     0,     0,     0,  1231,  1024,
    1020,     0,   442,     0,   438,     0,  1021,     0,  1027,  1022,
       0,   439,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   441,     0,     0,  1028,     0,     0,  1624,
       0,     0,  1025,  1026,  1029,   441,     0,   297,     0,     0,
       0,     0,  1023,   443,  1025,  1026,     0,  1015,     0,     0,
       0,     0,   442,     0,     0,     0,     0,     0,  1027,     0,
       0,     0,     0,  1017,   442,     0,     0,     0,     0,     0,
    1027,     0,     0,     0,     0,     0,  1028,     0,     0,     0,
    1018,     0,     0,   440,  1029,     0,     0,   297,  1028,     0,
       0,   437,     0,   443,     0,     0,  1029,     0,     0,   297,
       0,     0,     0,     0,     0,   443,     0,     0,     0,     0,
    1024,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1019,     0,     0,     0,     0,     0,     0,  1020,     0,
       0,     0,   438,     0,  1021,     0,     0,  1022,     0,   439,
       0,  1762,     0,     0,     0,     0,   441,     0,     0,  1018,
       0,     0,     0,     0,     0,  1025,  1026,     0,     0,     0,
     437,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1023,     0,     0,     0,     0,   442,     0,     0,     0,     0,
       0,  1027,     0,     0,     0,     0,     0,     0,     0,     0,
    1019,     0,     0,     0,     0,     0,     0,  1020,     0,  1028,
       0,  1060,     0,  1021,     0,     0,  1022,  1029,   439,     0,
     297,   440,  1655,     0,  1656,     0,   443,  1657,   629,   630,
     631,   632,   633,   634,   635,  1658,  1659,  1660,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1024,  1023,
       0,     0,     0,     0,     0,     0,     0,  1661,     0,     0,
       0,     0,     0,     0,     0,   636,     0,   637,   638,   639,
     640,   641,   642,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   441,     0,     0,     0,     0,     0,
     440,     0,     0,  1025,  1026,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   643,
       0,     0,     0,   442,     0,     0,     0,  1024,     0,  1027,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1028,     0,     0,
       0,     0,     0,     0,     0,  1029,     0,     0,   297,  1662,
       0,     0,     0,   441,   443,     0,     0,     0,     0,     0,
       0,     0,  1025,  1026,     0,     0,     0,  1663,     0,     0,
       0,  1664,  1665,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   442,     0,     0,  1666,     0,     0,  1027,     0,
       0,     0,   644,     0,     0,     0,     0,     0,     0,   629,
     630,   631,   632,   633,   634,   635,  1028,     0,   645,     0,
       0,     0,     0,     0,  1029,     0,     0,   297,     0,     0,
       0,     0,     0,   443,  1667,     0,     0,     0,  2079,  2080,
       0,     0,     0,  1668,     0,     0,   636,     0,   637,   638,
     639,   640,   641,   642,   647,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   629,   630,
     631,   632,   633,   634,     0,     0,     0,  1669,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     643,  1670,   649,     0,     0,     0,     0,     0,     0,   650,
       0,   651,     0,     0,     0,   636,     0,   637,   638,   639,
     640,   641,   642,     0,   652,  1671,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1015,     0,     0,  1672,
       0,     0,     0,     0,  1673,     0,     0,     0,     0,   643,
       0,     0,  1017,     0,     0,     0,     0,     0,  1674,     0,
       0,     0,     0,     0,  2081,     0,     0,     0,   655,     0,
     656,   657,   658,   644,     0,     0,  1015,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   645,
       0,     0,  1017,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1675,  2082,  2083,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1676,     0,     0,     0,
     660,   661,   662,  1015,     0,   647,     0,     0,     0,     0,
    2084,     0,   644,   663,     0,  1677,   664,     0,  1018,  1017,
       0,     0,     0,     0,     0,     0,     0,     0,   648,   437,
       0,     0,     0,     0,     0,     0,  1678,  1015,     0,     0,
       0,     0,     0,   649,     0,     0,     0,     0,     0,     0,
     650,     0,   651,  1017,     0,  2085,     0,     0,  1018,  1180,
       0,     0,     0,     0,   647,   652,  1020,     0,     0,   437,
     438,     0,  1021,     0,     0,  1022,     0,   439,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1180,
       0,     0,   649,     0,     0,  1018,  1020,     0,  1023,     0,
     438,   651,  1021,     0,     0,  1022,   437,   439,     0,   655,
       0,   656,   657,   658,   652,     0,     0,     0,  2086,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1018,
       0,     0,  2087,     0,     0,     0,  1180,     0,  1023,   440,
     437,     0,     0,  1020,     0,     0,     0,   438,     0,  1021,
       0,     0,  1022,     0,   439,     0,  2088,     0,     0,     0,
       0,   660,   661,   662,     0,     0,  1024,     0,     0,     0,
     656,   657,   658,     0,   663,     0,     0,   664,  2089,   440,
       0,   438,     0,  1021,     0,  1023,  1022,     0,   439,     0,
       0,     0,     0,     0,     0,     0,     0,  2090,     0,     0,
       0,     0,   441,     0,     0,     0,  1024,     0,     0,     0,
       0,  1025,  1026,     0,     0,     0,     0,     0,     0,  1023,
     660,   661,   662,     0,     0,     0,   440,     0,     0,     0,
       0,   442,     0,     0,     0,     0,     0,  1027,     0,     0,
       0,     0,   441,     0,     0,     0,     0,     0,     0,     0,
       0,  1025,  1026,  1024,     0,  1028,     0,     0,     0,     0,
     440,     0,     0,  1029,     0,     0,   297,     0,     0,     0,
       0,   442,   443,  1181,  1182,     0,     0,  1027,     0,     0,
       0,  1707,  1183,     0,     0,     0,     0,  1024,     0,   441,
       0,     0,     0,     0,     0,  1028,     0,     0,  1025,  1026,
       0,     0,     0,  1029,     0,     0,   297,     0,     0,     0,
       0,     0,   443,  1181,  1182,     0,     0,     0,   442,     0,
       0,  1943,  1183,   441,  1027,     0,     0,     0,     0,     0,
       0,     0,  1025,  1026,     0,     0,     0,     0,     0,     0,
       0,     0,  1028,     0,     0,     0,     0,     0,     0,     0,
    1029,     0,   442,   297,     0,     0,     0,     0,  1027,   443,
    1181,  1182,     0,     0,     0,     0,     0,     0,     0,  1183,
       0,     0,     0,     0,     0,     0,  1028,     0,     0,     0,
       0,     0,     0,     0,  1029,     0,     0,   297,     0,     0,
       0,     0,     0,   443
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1738)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      84,   176,   412,   571,   231,   132,   230,   234,   460,   721,
     934,  1059,   685,   898,   687,   323,  1308,   535,   536,  1138,
     893,   196,   197,   653,  1131,  1238,   201,   202,   203,   204,
     205,   904,   207,   228,   209,   230,   231,   750,  1748,   234,
    1378,  1238,  1238,   895,  1238,   892,    22,  1238,   868,   869,
      13,  1052,  1420,  1421,   901,   902,   283,   369,  1152,   912,
     287,   692,   289,  1121,   894,   487,   193,     6,  1378,   916,
     917,   298,   925,   248,   301,   250,   160,     9,   625,    23,
     258,  1271,   257,   930,   931,   603,    28,     9,   283,    49,
     265,  1079,   287,  1378,   289,  1029,  1378,    17,     6,  1087,
      49,  1208,  1378,   298,   279,   280,   301,   282,  1378,    72,
     820,    48,    96,   288,     9,    49,     6,     6,    30,    96,
      70,  1522,    86,   114,  1312,    88,    17,    85,  1411,   122,
      56,    54,   444,   360,    70,  1418,    48,    86,    56,  1540,
      49,    21,   149,   370,    63,  1133,  1262,  1263,  1264,  1207,
     377,     9,   327,    22,   170,   330,   331,    73,   333,   171,
    1897,    56,    66,   182,   121,   360,   390,  1168,   392,    66,
     348,    70,  1882,   115,   349,   370,    70,   355,   123,   625,
     122,    49,   377,   171,   214,  1032,    70,  1588,   415,   862,
       0,   366,    40,   388,  1014,   390,    61,   392,   248,  1019,
    1294,   874,     9,    56,   207,    37,   518,   245,   223,   251,
      23,    32,   279,     9,    70,  1062,    49,   118,   413,   126,
     415,   300,   306,    88,    89,   168,   107,  1628,  1286,   183,
     202,   409,   171,  1352,   121,   462,   411,   464,   416,   463,
       6,   914,   150,  1843,   419,   236,   163,  1171,   322,  1096,
     236,   429,  1404,     0,  1231,  1115,   214,   325,  1078,  1411,
     188,   233,   174,   236,   248,   372,  1418,   462,   463,   464,
     214,   693,   310,   368,   368,   453,  1129,   319,   173,   321,
     118,   113,   211,   402,   479,  1379,   214,   123,   466,   836,
    1348,  1268,  1139,  1661,  1004,  1005,     9,  1144,   473,  1667,
     118,   423,   236,   310,   236,   455,  1400,   236,   223,   393,
     986,   418,   396,   380,   436,  1316,    70,   455,   493,   494,
     358,   305,  1299,   418,   418,   122,   312,   150,   223,    92,
    1003,   167,   406,   236,   561,   236,   233,    50,   280,   458,
     248,   519,  1330,   164,   227,   228,  1231,   319,   523,   214,
     236,   236,  1410,   403,   326,   121,   263,   311,   533,   537,
    1180,   325,   441,  1553,  1765,   325,   561,   435,   998,   999,
    1347,   316,   289,   183,    70,  1006,   325,   210,  1251,   986,
    1202,   341,   251,  1268,  1231,   560,   218,    63,   583,   584,
     836,  1238,   364,   568,  1513,   573,   411,   301,   236,   195,
     578,   214,   260,  1276,   301,   214,   322,   975,   256,   218,
    2010,   354,   539,  2013,  1299,  1531,   325,   455,   236,   364,
    1267,  1268,  1529,   244,   360,   455,   442,   602,   293,   236,
     442,   434,   607,  1716,   609,   442,   455,   612,  2175,   614,
     236,   616,   617,  1296,   363,  1121,   621,   243,   441,   442,
    1280,   442,  1299,  1641,   442,  1315,   236,   325,   442,   654,
     318,   360,  1347,  1557,  1452,   442,   360,   424,   321,   442,
     648,   435,   409,   341,  1451,   435,   360,   236,   436,   455,
    1310,   350,   195,   433,   168,   403,   435,  1334,   663,   664,
     406,  1338,  1339,  1203,  1341,   455,   411,   409,   442,   441,
    1347,   311,   441,   442,   360,  1181,  1182,  1183,   442,   400,
     442,   434,   225,   403,   448,  1191,   411,   443,   438,   315,
     442,   457,  1580,   236,   404,   833,   435,  1357,   408,   441,
     243,  1207,   364,     9,   442,   498,  1212,   424,  1214,   442,
    1216,  1942,  1218,  1591,  1220,  1221,  1222,  1223,  1224,  1225,
    1226,  1227,   442,   442,  1612,   867,   442,   442,   457,   895,
     441,   442,  2162,   457,  1716,   692,  1451,   435,   331,   245,
    1908,  1690,   455,   457,  1181,  1182,  1183,  1399,   914,   376,
    1872,  1211,   378,   919,  1191,  1007,   117,   455,  1218,   816,
     455,   251,  1993,   820,  1995,  2305,   823,   824,  1908,  1587,
     187,   457,   315,   830,   442,  1212,   360,  1214,   269,  1216,
    1286,   407,   187,  1220,  1221,  1222,  1223,  1224,  1225,  1226,
    1227,   816,  2023,  1908,   442,   820,  1908,  1174,   823,   824,
    1820,   394,  1908,   442,   310,   830,   811,   403,  1908,   139,
     156,    30,   198,   120,   441,   442,   442,   187,  1278,    70,
     986,   236,   448,  2054,  2055,  1774,   180,   832,   424,   456,
     139,  1554,   442,   248,   360,   378,   187,  1560,   448,  1885,
     354,   240,  1348,   422,   187,    28,   442,    66,    27,   456,
     200,  1511,   358,   442,   240,  1397,   236,   363,  1000,  1320,
     350,   260,    31,  1324,   407,   449,   450,   451,   452,   894,
     454,   288,   901,   457,   260,  1381,   102,   187,   293,   887,
      11,  2079,  1388,  1389,  1390,  1391,  1392,  1393,  1394,   195,
     915,   405,   986,   240,   919,   455,   921,   954,   923,   924,
     240,   926,   931,  1586,  1410,   448,   260,   326,  1739,  1740,
    1741,   269,   331,   260,   971,   187,   941,   524,  1460,   175,
    2059,  1381,  2061,   449,   450,   451,   452,   277,   454,   954,
     236,   457,   115,   198,   199,   426,   442,   243,   284,  1105,
      71,   110,  1619,   348,   305,  1833,   971,  1004,  1005,  1767,
     441,  1388,  1389,  1390,  1391,  1392,  1393,  1394,   240,   247,
     236,   180,   919,   245,   989,   455,  1426,   972,  2014,   349,
      12,  1895,   247,    15,    16,   240,   984,  1520,   348,  1004,
    1005,   311,  1664,  1747,   563,   899,  1935,  1936,  1752,  1753,
     341,   198,  1756,  1757,  1758,   260,  1760,  1761,   245,   206,
     166,  1889,   311,   245,  2047,   348,   920,   347,   922,   315,
    1817,   299,  1819,   927,   233,  1181,  1182,  1183,   225,  1561,
    2047,  2047,   936,  2047,   299,  1191,  2047,   442,  1570,   311,
    2261,  2262,  1850,   448,  1980,  1981,  1982,  1983,   348,  1988,
    1989,   207,   441,     9,    28,  1852,  1212,   455,  1214,   215,
    1216,   437,  1218,     1,  1220,  1221,  1222,  1223,  1224,  1225,
    1226,  1227,  2201,   310,   156,  1788,  1789,   236,   310,   341,
     277,   278,   378,   329,  1580,  1581,    83,  1884,   285,   286,
     224,    25,   301,   441,   291,   292,   200,  1181,  1182,  1183,
      56,  1814,  1117,   180,   441,   442,   107,  1191,   213,    47,
    1823,   407,  1817,   300,  1819,   240,  1612,   120,    30,   360,
    2232,   358,   279,   368,    62,   167,   358,   399,  1821,   166,
    1214,   240,   288,  1913,   154,   260,  1220,  1221,  1222,  1223,
    1087,   115,  1226,  1227,  1159,  2072,   188,  1852,   195,  1053,
       9,   260,   448,  1933,  1934,   356,  1203,    60,  1105,   236,
       9,   266,   275,    12,   102,  1615,    15,    16,  1163,    72,
     207,   449,   450,   418,   175,  1173,   376,  1870,   215,  1884,
     368,   285,   437,   380,   449,   450,   441,   188,  1203,   236,
      93,   455,  1859,   213,   128,  2063,   243,    56,   101,   324,
     307,   126,   284,   455,  1984,    25,    26,  1987,   449,   450,
     451,   452,   346,   454,   126,   372,   457,   173,   455,  2331,
    1936,   253,   254,   455,   337,  1381,  1116,   368,   202,   167,
     418,   455,  1388,  1389,  1390,  1391,  1392,  1393,  1394,   195,
     272,   273,   442,  1956,   264,  1020,   266,    67,  1376,    69,
     188,   288,   236,  1749,   441,   442,   456,   319,  1754,   455,
    2327,   418,  1975,  1153,   377,  1280,   379,   223,   315,   240,
    1045,     8,  1988,  1989,   258,   178,   214,   418,  2345,  1992,
     236,   219,   258,   103,   104,   105,   442,   243,   213,   260,
     236,   416,  2072,   231,   455,  1310,   169,  2165,    35,  1246,
    1967,   923,  2046,    11,  1388,  1389,  1390,  1391,  1392,  1393,
    1394,  1583,   374,   375,   260,   299,   441,    25,    26,   941,
    2033,  2034,  1749,  1370,  1371,     8,   167,  1754,   304,  2042,
     150,   378,   152,   227,   228,   208,   195,  1833,   263,  1832,
     160,   266,  1357,   216,   441,  1841,  2126,   188,   240,    57,
    1365,  1606,    35,  1257,   124,  1370,  1371,  1695,   455,   315,
     407,    90,    91,  1212,   223,   404,  1621,  1216,   260,   408,
    1438,   195,  1319,  1441,   526,  1224,  1225,   236,  1446,   531,
     120,   319,   320,   356,   243,   296,   297,   116,    96,    97,
     311,    99,  1885,  1889,   332,    33,   334,   135,    36,   310,
     108,   448,  2270,   600,   253,   254,    44,    45,    46,   159,
     310,  1358,   236,   163,   234,   455,   404,     2,  2131,   243,
     408,     6,   378,   272,   273,   195,  2139,   356,   248,  1961,
     444,  1963,   166,   319,   169,   321,   170,   449,   450,   451,
     452,  2154,   454,   151,   152,   356,  2151,  2087,  2153,   461,
     278,   407,   280,   455,   162,   411,   315,   233,   234,   195,
     891,   319,     1,   321,   895,     4,   236,  2247,   356,  2182,
     901,  2184,  2252,   243,   239,   906,   907,   438,  2191,   440,
      19,   912,   913,   914,   442,   255,   442,   153,   919,   155,
      29,   315,   448,   265,   925,   267,  1511,   435,  2211,  2212,
     236,   156,   157,   934,   935,  2172,   937,   243,  1664,   451,
     452,  1849,   454,   449,   450,   451,   452,   455,   454,   378,
     158,  2014,   227,   228,    63,   461,   153,   341,   155,   237,
     185,   319,  2276,   321,   233,   234,   191,   455,   176,   449,
     450,   451,   452,   359,   454,   315,   455,   457,   407,   270,
     271,   455,   411,   455,   378,   986,   194,   455,   449,   450,
     451,   452,   455,   454,   216,   294,   295,   222,   270,   271,
     405,   226,  2285,   427,   428,   429,   430,   455,   356,   315,
     442,   401,   235,   442,   455,  1016,   195,   455,   182,   448,
     455,   283,   280,  1749,   280,   403,  1643,  2264,  1754,   277,
    2267,  2133,   403,  2135,   242,   395,   335,   336,   378,    24,
     455,   381,   382,   356,   332,   449,   450,   451,   452,   372,
     454,  1052,   442,   457,   448,  1620,   214,   236,  1643,  2122,
     455,   107,     6,   442,   243,     9,   427,   428,   429,   430,
    1687,   367,   378,  1590,   352,   384,    56,   442,  1079,  2316,
     236,    85,   290,   175,  1649,  1653,  1087,  1088,   455,   356,
     351,  1656,   372,   202,  1711,  1749,   283,   109,  1663,   236,
    1754,  1669,  1687,   363,  1105,   211,   455,    11,   448,  1626,
     249,  2348,    68,   280,   392,   410,  1633,   280,   455,   356,
    1121,    25,    26,   249,   233,    23,  1711,   277,  1129,   455,
     442,   240,  1133,   236,  1751,   343,   315,   280,    82,   301,
     455,  1142,   448,    84,  1145,   353,   427,   428,   429,   430,
      84,   436,   261,    57,    98,  1720,   442,   400,  1723,   442,
     449,   450,   451,   452,   442,   454,  1751,  1168,   457,   384,
    1171,  1793,  1794,  1795,  1796,   317,   435,   286,   234,   403,
    1181,  1182,  1183,   292,   200,   442,   449,   450,   451,   452,
    1191,   454,    96,    97,   457,    99,   319,   403,   364,   378,
     449,   450,   451,   452,   108,   454,  1207,   415,   457,   218,
     319,  1212,   156,  1214,    55,  1216,   384,   326,    27,  1220,
    1221,  1222,  1223,  1224,  1225,  1226,  1227,   441,   407,   188,
     339,   456,  1797,   364,   459,   460,   372,   455,  1803,   356,
     184,   442,   455,   227,   225,   438,   346,   151,   152,   214,
     109,   195,   405,   236,   363,   364,   306,   366,   162,   449,
     450,   451,   452,   442,   454,   374,    37,   457,   381,   448,
     287,  2229,   448,   281,   403,   384,   458,    27,   400,   362,
    1845,   225,   462,  2083,   400,  1286,   174,     9,   232,   236,
     455,   442,   236,   405,   238,  1296,   405,   241,   455,   243,
     136,   107,   172,    17,   188,   402,   441,   236,  1309,   458,
      30,   127,   458,   458,   458,  1316,    31,   458,    33,   205,
     458,    36,  1323,   128,   458,   458,   458,    56,   458,  1330,
     274,    46,   403,   237,   458,   434,  1904,  1854,   458,   130,
     319,  1342,   348,  1860,   132,  1910,   455,  1348,   133,   100,
    1915,   399,   403,  1354,   137,    49,   138,   402,   400,  1924,
     397,   402,   180,  1928,   143,   248,   436,    49,   146,   180,
     112,   315,  1373,   333,    12,    13,    14,   380,   442,   114,
    1854,   114,    20,   365,   441,   403,   187,  1388,  1389,  1390,
    1391,  1392,  1393,  1394,   309,   442,   341,   236,   342,   163,
     134,    82,   438,  2020,   171,   403,   210,   403,   366,  1410,
      49,   218,   180,   210,   122,   280,   193,    98,   447,   454,
      58,   446,   218,   270,   457,   233,   457,   457,   341,  1430,
     457,   398,   403,   373,   378,  2020,   131,   266,   269,   265,
     187,   331,   403,   387,   388,   400,    49,   138,   352,     8,
     180,  1452,   438,   126,   403,     9,   307,  2022,   308,   202,
     438,   176,   173,   407,   344,   404,   181,   329,   268,   413,
     125,   435,   435,   110,    49,   175,   141,   263,   142,   194,
     240,   262,   285,   144,   113,   300,   284,   431,   392,   394,
     289,     7,   116,   220,    67,   439,   442,   156,   442,   156,
     328,   129,   136,   184,   448,   328,   102,  2121,    49,   240,
    2075,   218,   456,  1514,  1515,   145,    95,   148,   156,   157,
     264,  2086,   267,  2088,    91,   221,   203,   242,   438,   192,
     390,    49,   406,   307,   344,   240,  2121,   240,   442,  2107,
     147,   174,   307,   140,   180,   293,   423,   185,    49,     6,
      22,   455,   354,   191,    54,   236,   132,   238,   193,   178,
     241,   188,   211,  1331,   514,   597,  1154,   136,     6,   444,
    1362,     9,  1371,   960,  1155,   290,   214,  1900,   109,  1580,
    1581,  1853,   610,   227,   222,  1586,  1587,   113,   226,   239,
      49,   584,   160,   274,   886,   318,   861,  1908,   393,   314,
    1696,  1694,  1585,  1604,  1692,  2119,   874,  2102,   565,  2174,
     974,  1612,  2240,   124,    82,   836,  1776,  2234,   256,   257,
     496,  1857,  1062,   338,   262,  1423,  1627,  1422,   343,  1735,
      98,  1632,  1633,  1067,   272,  1810,  1774,  2254,   353,  1276,
    1273,   279,   357,  1820,    82,  1553,   284,  2004,  1283,  2234,
    1289,  2219,  1841,  1578,  1105,  2220,  2221,  1858,  1602,  2224,
      98,   342,  1358,  1664,   302,  1324,  2231,  1874,  1127,  2254,
    1139,  2239,  2240,  1633,  1675,  1129,  1677,  2057,  1633,   926,
    1713,  2175,  1865,  2062,  2068,  1240,     1,  1527,  2273,  1615,
    1117,     6,  1643,   987,     9,   246,  1236,    12,    13,    14,
     415,  1294,  1070,  2268,   329,   866,   387,   388,   619,   177,
     425,   149,   994,  2256,    57,  1466,   184,   827,  1916,    -1,
      -1,    -1,  1001,    -1,    -1,    -1,    -1,    -1,    -1,  2297,
    2298,    -1,   413,  2301,  2299,  2303,  2210,    -1,  1739,  1740,
    1741,    -1,  2327,    58,    -1,    -1,   184,    -1,  1749,    -1,
     431,    -1,    -1,  1754,    -1,    -1,    -1,   195,   439,    -1,
    2345,   442,    -1,    -1,  2329,    -1,  1767,    82,   236,    -1,
     238,  2339,    -1,   241,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    98,    -1,    -1,    -1,   225,    -1,    -1,
      -1,    -1,    -1,    -1,   232,  2269,    -1,    -1,   236,    -1,
     238,    -1,    -1,   241,    -1,   243,   274,    -1,    -1,    -1,
     448,   449,   450,   451,   452,    -1,   454,    -1,   456,   457,
      -1,   459,   460,    -1,    -1,  1826,    -1,    -1,    -1,    -1,
      -1,  1832,  1833,    -1,    -1,    -1,   274,    -1,    -1,    -1,
    1841,   156,   157,    -1,    -1,    -1,    -1,    -1,    -1,  1850,
      -1,    -1,    -1,    -1,  2328,    -1,    -1,  1858,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,
     185,    -1,    -1,    -1,   342,    -1,   191,   315,    -1,    -1,
     195,    -1,    -1,    -1,  1885,    -1,    -1,    -1,  1889,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   214,
      -1,    -1,    -1,    -1,   342,    -1,    -1,   222,  1909,    -1,
     225,   226,  1913,    -1,    -1,    -1,    -1,   232,    -1,   387,
     388,   236,    -1,   238,    -1,    -1,   241,    -1,   243,   397,
      -1,    -1,  1933,  1934,    -1,    -1,    -1,    -1,    -1,    -1,
     378,   256,   257,    -1,    -1,   413,    -1,   262,    -1,   387,
     388,    -1,    -1,    -1,    -1,   423,    -1,   272,    -1,   274,
      -1,    -1,    -1,   431,   279,    -1,   404,    -1,   436,   407,
     408,   439,    -1,   441,   442,   413,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1984,    -1,    -1,  1987,   302,    -1,    -1,
      -1,    -1,    -1,   431,    -1,    -1,    -1,    -1,    -1,    -1,
     315,   439,    -1,    -1,   442,    -1,    -1,    -1,    -1,    -1,
     448,    -1,    -1,  2014,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   342,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     0,     1,    -1,    -1,  2046,    -1,    -1,    -1,    -1,
      -1,    -1,  2053,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,   378,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  2072,   387,   388,    -1,    34,    -1,    -1,    37,    38,
      39,    40,    41,    42,    43,    -1,    -1,    -1,  2089,    -1,
      -1,    -1,   407,    -1,    -1,    -1,    -1,    -1,   413,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,   431,    76,    77,    78,
      79,    80,    81,    -1,   439,  2126,    -1,   442,    -1,    -1,
      -1,    -1,    -1,   448,   449,   450,    -1,    -1,    -1,   454,
      -1,   456,    -1,   458,   459,   460,     6,    -1,    -1,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   135,    -1,    -1,    -1,
     139,    -1,    -1,    -1,  2185,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2200,
      -1,    -1,  2203,    -1,    -1,    -1,    -1,    -1,   167,   168,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,   183,    -1,    -1,    -1,    -1,   188,
      -1,    -1,  2233,    -1,    -1,    -1,    -1,    -1,    98,    -1,
      -1,    -1,   201,    82,    -1,    -1,  2247,    -1,    -1,    -1,
      -1,  2252,   112,    -1,    -1,   214,    -1,    -1,   217,    98,
      -1,    -1,    -1,    -1,   223,    -1,    -1,    -1,   227,   228,
      -1,    -1,    -1,    -1,    -1,  2276,   235,   236,    -1,    -1,
     239,    -1,    -1,    -1,    -1,    -1,  2287,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   253,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     0,     1,    -1,     3,    -1,     5,
      -1,    -1,    -1,    -1,    10,    -1,    -1,   276,    -1,    -1,
      -1,    -1,    18,    -1,   184,    -1,    -1,    -1,    -1,    -1,
      -1,  2332,   291,    -1,    -1,   195,    -1,    -1,   177,   298,
      -1,   300,    -1,    -1,    -1,   184,    -1,    -1,   307,    -1,
     210,    -1,   311,    -1,   313,    51,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    59,   323,   225,    -1,    -1,    -1,    -1,
      -1,   330,   232,   332,    -1,    71,   236,    -1,   238,    75,
      -1,   241,    -1,   243,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    87,   351,    -1,    -1,   354,    -1,   236,    -1,   238,
      -1,    -1,   241,    -1,    -1,    -1,    -1,    -1,   367,    -1,
     369,   370,   371,    -1,   274,   111,    -1,    -1,    -1,    -1,
      -1,    -1,   118,   119,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   393,   274,    -1,    -1,    -1,   135,
      -1,    -1,    -1,   139,    -1,    -1,    -1,     1,    -1,     3,
      -1,     5,   411,   149,    -1,   315,    10,    -1,    -1,    -1,
     419,   420,   421,    -1,    18,   161,    -1,    -1,    -1,   165,
      -1,    -1,    -1,   432,    -1,    -1,   435,    -1,    -1,    -1,
      -1,    -1,   342,   179,    -1,   444,    -1,   183,    -1,    -1,
     186,    -1,    -1,   189,   190,    -1,   455,    51,    52,    -1,
      -1,   197,    -1,   342,    -1,    59,    -1,    -1,   204,    -1,
     206,    -1,    -1,   209,    -1,    -1,    -1,    71,   378,    -1,
      -1,    75,    -1,    -1,    -1,    -1,    -1,   387,   388,    -1,
      -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   407,   387,   388,
     246,    -1,    -1,   413,   250,    -1,   252,   111,   397,    -1,
      -1,    -1,    -1,   259,   118,   119,    -1,    -1,    -1,    -1,
      -1,   431,   126,    -1,   413,    -1,    -1,    -1,    -1,   439,
      -1,    -1,   442,    -1,   423,    -1,   282,    -1,   448,    -1,
      -1,    -1,   431,    -1,    -1,   149,    -1,   436,    -1,    -1,
     439,   297,   441,   442,    -1,    -1,    -1,   161,    -1,    -1,
      -1,   165,    -1,    -1,    -1,   311,    -1,    -1,    -1,    -1,
      -1,    -1,   318,    -1,    -1,   179,    -1,    -1,    -1,    -1,
      -1,   327,   186,    -1,    -1,   189,   190,    -1,    -1,    -1,
      -1,    -1,    -1,   197,   340,    -1,    -1,    -1,    -1,   345,
     204,   347,   206,    -1,    -1,   209,    -1,    -1,    -1,   355,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   365,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   374,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   383,    -1,   385,
     386,    -1,   246,   389,    -1,   391,   250,    -1,   252,    -1,
     396,    -1,    -1,    -1,     6,   259,    -1,     9,    -1,    -1,
      12,    13,    14,    -1,    -1,    17,   412,    -1,    -1,    21,
      -1,   417,    -1,    -1,    -1,    -1,   422,    -1,   282,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   433,    -1,    -1,
      -1,    -1,    -1,   297,    -1,    -1,   442,    -1,    -1,   445,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,   455,
      -1,    -1,    -1,    -1,   318,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    -1,    -1,    -1,   340,    -1,    -1,    -1,
      -1,   345,    -1,   347,    -1,    -1,    98,    -1,    -1,    -1,
       6,   355,    -1,     9,    -1,    -1,    12,    13,    14,    -1,
      -1,   365,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     374,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   383,
      -1,   385,   386,    -1,    -1,   389,    -1,   391,    -1,    -1,
      -1,    -1,   396,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    58,    -1,   156,   157,    -1,    -1,   412,    -1,
      -1,    -1,    -1,   417,    -1,    -1,    -1,    -1,   422,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,   433,
      -1,    -1,   184,   185,    -1,    -1,    -1,    -1,   442,   191,
      -1,   445,    98,   195,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   455,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   214,    -1,    -1,    -1,    82,    -1,    -1,    -1,
     222,    -1,    -1,   225,   226,    -1,    -1,    -1,    -1,    -1,
     232,    -1,    98,    -1,   236,    -1,   238,    -1,    -1,   241,
      -1,   243,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     156,   157,    -1,    -1,   256,   257,    -1,    -1,    -1,    -1,
     262,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     272,    -1,   274,    -1,    -1,    -1,    -1,   279,   184,   185,
      -1,    -1,    -1,    -1,    -1,   191,    -1,    -1,    -1,   195,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     302,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   214,    -1,
      -1,    -1,    -1,   315,    -1,    -1,   222,    -1,   184,   225,
     226,    -1,    -1,    -1,    -1,    -1,   232,    -1,    -1,   195,
     236,    -1,   238,    -1,    -1,   241,    -1,   243,    -1,    -1,
     342,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     256,   257,    -1,    -1,    -1,    -1,   262,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   272,    -1,   274,    -1,
     236,    -1,   238,   279,    -1,   241,   378,   243,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   387,   388,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   302,    -1,    -1,    -1,
      -1,    -1,   404,    -1,    -1,   407,   408,    -1,   274,   315,
      -1,   413,     3,    -1,     5,    -1,    -1,    -1,    -1,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,   431,
      -1,    -1,    -1,    -1,    -1,    -1,   342,   439,    -1,    -1,
     442,    -1,    -1,    -1,    -1,    -1,   448,   449,   450,   315,
      -1,    -1,   454,    -1,   456,    -1,   458,   459,   460,    -1,
      51,    52,    -1,    -1,    -1,    -1,    -1,    -1,    59,    -1,
      -1,    -1,   378,    -1,    -1,    -1,   342,    -1,    -1,    -1,
      71,   387,   388,    -1,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,
      -1,   407,    -1,    -1,    -1,    -1,    -1,   413,    -1,    -1,
      -1,    -1,   378,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     111,   387,   388,    -1,    -1,   431,    -1,   118,   119,    -1,
      -1,    -1,    -1,   439,    -1,    -1,   442,    -1,    -1,    -1,
      -1,   407,   448,   449,   450,    -1,    -1,   413,   454,    -1,
     456,    -1,   458,   459,   460,    -1,    -1,    -1,   149,    -1,
      -1,    -1,    -1,    -1,    -1,   431,    -1,    -1,    -1,    -1,
     161,    -1,    -1,   439,   165,    -1,   442,    -1,    -1,    -1,
      -1,    -1,   448,    -1,    -1,    -1,    -1,    -1,   179,    -1,
      -1,    -1,    -1,    -1,    -1,   186,    -1,    -1,   189,   190,
      -1,    -1,    -1,    -1,    -1,    -1,   197,    -1,    -1,    -1,
      -1,    -1,    -1,   204,    -1,   206,    -1,    -1,   209,    -1,
      -1,     6,    -1,    -1,     9,    -1,     3,    -1,     5,    -1,
      -1,    -1,    -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   246,    -1,    -1,    -1,   250,
      -1,   252,    -1,    -1,    49,    -1,    -1,    -1,   259,    -1,
      -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   282,    -1,    -1,    71,    -1,    -1,    82,    75,    -1,
      -1,    86,    -1,    -1,    -1,    -1,   297,    -1,    -1,    -1,
      87,    -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   318,    -1,    -1,
      -1,    -1,    -1,    -1,   111,    -1,   327,    -1,    -1,    -1,
      -1,   118,   119,    -1,    -1,    -1,    -1,    -1,    -1,   340,
      -1,    -1,    -1,    -1,   345,    -1,   347,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   355,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   149,    -1,   365,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   374,   161,    -1,    -1,    -1,   165,    -1,
      -1,    -1,   383,    -1,   385,   386,    -1,    -1,   389,   184,
     391,    -1,   179,    -1,    -1,   396,    -1,    -1,    -1,   186,
     195,    -1,   189,   190,    -1,    -1,    -1,    -1,    -1,    -1,
     197,   412,    -1,    -1,    -1,    -1,   417,   204,    -1,   206,
      -1,   422,   209,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     225,    -1,   433,     6,    -1,    -1,     9,   232,    -1,    -1,
      -1,   236,    -1,   238,   445,    -1,   241,    -1,   243,    -1,
      -1,    -1,    -1,    -1,   455,    -1,    -1,    30,    -1,   246,
      -1,    -1,    -1,   250,    -1,   252,    -1,     6,    -1,    -1,
       9,    -1,   259,    -1,    -1,    -1,    -1,    -1,    -1,   274,
      -1,    -1,    -1,    -1,   279,    -1,    -1,    -1,    -1,     6,
      -1,    -1,     9,    66,    -1,   282,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
     297,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     315,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,     6,
     325,   318,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     327,    -1,    -1,    82,    -1,    -1,    -1,   342,    -1,    -1,
      -1,     6,    -1,   340,     9,    94,    -1,    -1,   345,    98,
     347,    -1,    -1,    -1,    -1,    82,    -1,    -1,   355,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   372,   365,    -1,
      -1,    98,    -1,   378,    -1,    -1,    -1,   374,    -1,    -1,
      -1,    -1,   387,   388,    -1,   112,   383,    -1,   385,   386,
      -1,    -1,   389,    -1,   391,    82,    -1,    -1,    -1,   396,
      -1,   184,   407,    -1,    -1,    -1,    -1,    94,   413,    -1,
      -1,    98,   195,   418,    -1,   412,    -1,    82,    -1,    -1,
     417,    -1,    -1,    -1,    -1,   422,   431,    -1,    -1,    94,
     435,    -1,    -1,    98,   439,   184,   433,   442,    -1,    -1,
      -1,    -1,   225,   448,    -1,    -1,   195,    -1,   445,   232,
     233,    -1,    -1,   236,    -1,   238,    -1,   184,   241,    -1,
     243,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   195,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   225,    -1,    -1,    -1,
      -1,    -1,    -1,   232,    -1,    -1,    -1,   236,    -1,   238,
      -1,   274,   241,    -1,   243,    -1,    -1,   184,   225,    -1,
      -1,    -1,    -1,    -1,    -1,   232,    -1,    -1,   195,   236,
      -1,   238,    -1,    -1,   241,    -1,   243,    -1,   301,   184,
      -1,    -1,    -1,    -1,    -1,   274,    -1,    -1,    -1,    -1,
     195,    -1,   315,    -1,    -1,    -1,    -1,    -1,   225,    -1,
      -1,     6,    -1,    -1,     9,   232,    -1,   274,    -1,   236,
      -1,   238,    -1,    -1,   241,    -1,   243,    -1,    -1,   342,
     225,    -1,    -1,    -1,    -1,    -1,   315,   232,    -1,    -1,
      -1,   236,    -1,   238,    -1,    -1,   241,    -1,   243,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   274,   315,    -1,
      -1,     6,    -1,   342,     9,   378,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     6,   387,   388,     9,    -1,    -1,   274,
      -1,    -1,    -1,    -1,    -1,   342,    -1,    82,    -1,    -1,
      -1,    -1,    -1,    -1,   407,    -1,    -1,    -1,   315,   378,
     413,    -1,    -1,    98,    -1,    -1,    -1,    -1,   387,   388,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   431,    -1,
     315,   378,    -1,    -1,    -1,   342,   439,    -1,   407,   442,
     387,   388,    -1,    -1,   413,   448,    -1,    82,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   342,    -1,    82,
     407,    -1,   431,    98,    -1,    -1,   413,    -1,    -1,    -1,
     439,   378,    -1,   442,    -1,    98,    -1,    -1,    -1,   448,
     387,   388,    -1,    -1,   431,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   439,   378,     6,   442,    -1,     9,    -1,   184,
     407,   448,   387,   388,    -1,    -1,   413,    -1,    -1,    -1,
     195,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   407,    -1,   431,    -1,    -1,    -1,   413,    -1,
      -1,    -1,   439,    -1,    -1,   442,    -1,    -1,    -1,    -1,
     225,   448,    -1,    -1,    -1,   180,   431,   232,    -1,   184,
      -1,   236,    -1,   238,   439,    -1,   241,   442,   243,    -1,
     195,   184,    -1,   448,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,   195,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,   274,
     225,    -1,    -1,    -1,    -1,    -1,    -1,   232,    -1,    -1,
      -1,   236,   225,   238,    -1,    -1,   241,    -1,   243,   232,
      -1,    -1,    -1,   236,    -1,   238,    -1,    -1,   241,    -1,
     243,    -1,     6,    -1,    -1,     9,    -1,    -1,    -1,    -1,
     315,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   274,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   274,    -1,    -1,    -1,    -1,    -1,   342,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   184,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     315,    -1,    -1,   195,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     6,   315,   378,     9,    -1,    -1,    -1,    82,    -1,
      -1,    -1,   387,   388,    -1,    -1,    -1,   342,    -1,    -1,
      -1,    -1,    -1,   225,    98,    -1,    -1,    -1,   403,   342,
     232,    -1,   407,    -1,   236,    -1,   238,    -1,   413,   241,
      -1,   243,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   378,    -1,    -1,   431,    -1,    -1,   372,
      -1,    -1,   387,   388,   439,   378,    -1,   442,    -1,    -1,
      -1,    -1,   274,   448,   387,   388,    -1,    82,    -1,    -1,
      -1,    -1,   407,    -1,    -1,    -1,    -1,    -1,   413,    -1,
      -1,    -1,    -1,    98,   407,    -1,    -1,    -1,    -1,    -1,
     413,    -1,    -1,    -1,    -1,    -1,   431,    -1,    -1,    -1,
     184,    -1,    -1,   315,   439,    -1,    -1,   442,   431,    -1,
      -1,   195,    -1,   448,    -1,    -1,   439,    -1,    -1,   442,
      -1,    -1,    -1,    -1,    -1,   448,    -1,    -1,    -1,    -1,
     342,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   225,    -1,    -1,    -1,    -1,    -1,    -1,   232,    -1,
      -1,    -1,   236,    -1,   238,    -1,    -1,   241,    -1,   243,
      -1,   373,    -1,    -1,    -1,    -1,   378,    -1,    -1,   184,
      -1,    -1,    -1,    -1,    -1,   387,   388,    -1,    -1,    -1,
     195,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     274,    -1,    -1,    -1,    -1,   407,    -1,    -1,    -1,    -1,
      -1,   413,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     225,    -1,    -1,    -1,    -1,    -1,    -1,   232,    -1,   431,
      -1,   236,    -1,   238,    -1,    -1,   241,   439,   243,    -1,
     442,   315,    31,    -1,    33,    -1,   448,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   342,   274,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    -1,    76,    77,    78,
      79,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   378,    -1,    -1,    -1,    -1,    -1,
     315,    -1,    -1,   387,   388,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
      -1,    -1,    -1,   407,    -1,    -1,    -1,   342,    -1,   413,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   431,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   439,    -1,    -1,   442,   158,
      -1,    -1,    -1,   378,   448,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   387,   388,    -1,    -1,    -1,   176,    -1,    -1,
      -1,   180,   181,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   407,    -1,    -1,   194,    -1,    -1,   413,    -1,
      -1,    -1,   201,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    42,    43,   431,    -1,   217,    -1,
      -1,    -1,    -1,    -1,   439,    -1,    -1,   442,    -1,    -1,
      -1,    -1,    -1,   448,   233,    -1,    -1,    -1,    66,    67,
      -1,    -1,    -1,   242,    -1,    -1,    74,    -1,    76,    77,
      78,    79,    80,    81,   253,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    -1,    -1,    -1,   276,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     118,   290,   291,    -1,    -1,    -1,    -1,    -1,    -1,   298,
      -1,   300,    -1,    -1,    -1,    74,    -1,    76,    77,    78,
      79,    80,    81,    -1,   313,   314,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,   338,
      -1,    -1,    -1,    -1,   343,    -1,    -1,    -1,    -1,   118,
      -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,   357,    -1,
      -1,    -1,    -1,    -1,   192,    -1,    -1,    -1,   367,    -1,
     369,   370,   371,   201,    -1,    -1,    82,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   217,
      -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   403,   233,   234,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   415,    -1,    -1,    -1,
     419,   420,   421,    82,    -1,   253,    -1,    -1,    -1,    -1,
     258,    -1,   201,   432,    -1,   434,   435,    -1,   184,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   276,   195,
      -1,    -1,    -1,    -1,    -1,    -1,   455,    82,    -1,    -1,
      -1,    -1,    -1,   291,    -1,    -1,    -1,    -1,    -1,    -1,
     298,    -1,   300,    98,    -1,   303,    -1,    -1,   184,   225,
      -1,    -1,    -1,    -1,   253,   313,   232,    -1,    -1,   195,
     236,    -1,   238,    -1,    -1,   241,    -1,   243,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,
      -1,    -1,   291,    -1,    -1,   184,   232,    -1,   274,    -1,
     236,   300,   238,    -1,    -1,   241,   195,   243,    -1,   367,
      -1,   369,   370,   371,   313,    -1,    -1,    -1,   376,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,
      -1,    -1,   390,    -1,    -1,    -1,   225,    -1,   274,   315,
     195,    -1,    -1,   232,    -1,    -1,    -1,   236,    -1,   238,
      -1,    -1,   241,    -1,   243,    -1,   414,    -1,    -1,    -1,
      -1,   419,   420,   421,    -1,    -1,   342,    -1,    -1,    -1,
     369,   370,   371,    -1,   432,    -1,    -1,   435,   436,   315,
      -1,   236,    -1,   238,    -1,   274,   241,    -1,   243,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   455,    -1,    -1,
      -1,    -1,   378,    -1,    -1,    -1,   342,    -1,    -1,    -1,
      -1,   387,   388,    -1,    -1,    -1,    -1,    -1,    -1,   274,
     419,   420,   421,    -1,    -1,    -1,   315,    -1,    -1,    -1,
      -1,   407,    -1,    -1,    -1,    -1,    -1,   413,    -1,    -1,
      -1,    -1,   378,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   387,   388,   342,    -1,   431,    -1,    -1,    -1,    -1,
     315,    -1,    -1,   439,    -1,    -1,   442,    -1,    -1,    -1,
      -1,   407,   448,   449,   450,    -1,    -1,   413,    -1,    -1,
      -1,   457,   458,    -1,    -1,    -1,    -1,   342,    -1,   378,
      -1,    -1,    -1,    -1,    -1,   431,    -1,    -1,   387,   388,
      -1,    -1,    -1,   439,    -1,    -1,   442,    -1,    -1,    -1,
      -1,    -1,   448,   449,   450,    -1,    -1,    -1,   407,    -1,
      -1,   457,   458,   378,   413,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   387,   388,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   431,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     439,    -1,   407,   442,    -1,    -1,    -1,    -1,   413,   448,
     449,   450,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   458,
      -1,    -1,    -1,    -1,    -1,    -1,   431,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   439,    -1,    -1,   442,    -1,    -1,
      -1,    -1,    -1,   448
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   464,   465,     0,   183,   311,   466,   467,   468,   474,
     481,   483,   455,   455,     0,   467,   150,   489,   489,   236,
     312,   484,   484,   120,   469,   475,    27,   485,   485,   455,
     102,   594,   594,   236,   455,   482,    83,   490,   120,   470,
     476,   214,   486,  1148,   356,   169,   208,   216,   544,   455,
     307,   736,   736,   455,    73,   322,   406,   487,   488,   455,
     455,   356,   455,   168,   354,   405,   595,   601,   120,   471,
     477,   481,   135,   480,   488,   310,  1160,   491,   545,   455,
     546,   356,   444,   626,   597,    54,   434,   739,   139,   471,
     478,   489,   484,   275,   337,   377,   379,   492,   493,   497,
     505,   510,   548,   169,   547,    22,   251,   350,   583,   584,
     585,   586,   588,   592,   593,   455,   356,   239,   679,   442,
     600,   602,  1078,   741,   740,   341,   747,   484,   472,   455,
     455,   455,   455,   455,   359,   549,   455,   216,   582,    60,
      72,    93,   101,   178,   405,  1144,   319,   374,   375,   587,
     455,   585,   455,   593,   596,   455,   356,   235,   681,   599,
     601,   628,   629,   630,   603,    49,   742,   743,   744,  1139,
     742,   442,   455,   455,   594,   245,   358,   442,   496,   498,
     499,   500,   501,   503,   504,  1160,   182,   506,   507,   508,
     441,   494,   495,   496,  1174,    11,    25,    26,    57,    96,
      97,    99,   108,   151,   152,   162,   237,   352,   392,   442,
     511,   512,   513,   514,   521,   530,   534,   537,   538,   539,
     540,   541,   542,   543,   283,  1125,   548,   455,   280,   280,
    1157,   403,   277,  1156,   403,   395,  1168,    24,  1135,   598,
     627,   455,   356,   332,   683,   602,   631,  1119,   604,   743,
     372,   418,   745,   325,   435,   737,   473,   372,  1148,   455,
     499,   455,   500,    63,   363,  1131,     9,   236,   509,   455,
     508,   455,   455,   495,   107,   442,  1090,  1148,  1148,  1090,
     384,   367,  1164,  1148,  1148,  1148,  1148,  1148,  1090,  1148,
      56,  1141,  1148,   455,   513,  1090,   583,   442,  1085,  1086,
    1105,  1085,  1086,   236,  1086,    85,  1142,   175,  1145,   599,
     628,   680,   455,   356,   351,   724,   628,   455,  1119,   227,
     228,   632,   635,   636,   642,     1,    47,    62,   102,   219,
     231,   319,   320,   332,   334,   435,   455,   605,   606,   608,
     612,   614,   616,   617,   623,   624,   625,  1148,  1148,   372,
     283,   746,   109,   748,   736,  1148,   236,  1108,   455,   363,
    1148,   211,   211,   236,   455,   249,   522,  1090,  1090,  1148,
    1148,  1148,  1086,    68,  1090,  1090,  1086,  1148,  1086,   531,
     532,  1090,    96,   516,  1090,   550,   200,   277,  1128,  1086,
     280,   410,   280,   589,   590,  1078,  1077,  1078,   628,   682,
     455,   356,   632,   171,   442,   638,   639,   442,   638,  1142,
    1148,   319,   321,  1129,  1129,  1148,  1142,  1148,   249,  1154,
    1148,    23,  1134,   277,   167,   188,    31,   110,  1108,  1148,
     442,   455,   738,   477,  1108,  1086,  1148,   195,   236,   243,
     315,   378,   407,   448,   535,   536,  1111,  1086,   236,  1086,
      23,   214,  1090,  1149,   278,   280,   518,   519,   520,   515,
     551,  1105,  1085,   280,  1085,   590,   301,   591,  1078,   628,
     684,   455,   633,    84,   634,  1108,   442,  1148,  1134,  1087,
    1105,   279,   380,   613,   236,  1086,  1089,  1108,   436,  1148,
     442,   723,   723,   170,   442,  1108,   749,   750,   139,   479,
      56,   443,   502,   124,   195,   236,   243,   255,   315,   378,
     381,   382,   448,   523,   524,   525,   528,   536,   400,   533,
    1108,   519,   384,  1167,   517,     1,     4,    19,    29,   202,
     233,   240,   261,   286,   292,   319,   326,   339,   364,   366,
     374,   405,   455,   552,   553,   558,   560,   565,   566,   567,
     568,   572,   573,   574,   575,   576,   577,   578,   579,   581,
    1131,  1085,  1108,   317,   685,   686,   687,   725,   643,   640,
    1148,   435,   672,   403,   611,  1105,   234,  1152,   403,  1141,
     200,  1147,   442,  1148,  1148,   750,     1,   442,   751,   752,
     753,   754,   755,   760,   484,   525,    17,   400,  1111,  1108,
    1148,   519,  1154,   319,   403,  1172,   364,  1154,   218,  1150,
    1148,    55,  1140,    37,   113,  1138,  1150,  1150,   260,  1108,
    1174,   384,  1148,   723,   687,   726,     1,    21,    34,    37,
      38,    39,    40,    41,    42,    43,    74,    76,    77,    78,
      79,    80,    81,   118,   201,   217,   236,   253,   276,   291,
     298,   300,   313,   323,   330,   367,   369,   370,   371,   393,
     419,   420,   421,   432,   435,   637,   644,   645,   646,   648,
     649,   650,   651,   652,   654,   666,   667,   669,   670,   671,
     677,   678,  1148,  1165,    27,  1136,   188,  1149,  1108,    56,
     321,   607,   618,  1108,   372,  1166,   236,   615,  1105,   615,
     126,   455,   356,     3,     5,    10,    18,    51,    52,    59,
      71,    75,    87,   111,   118,   119,   149,   161,   165,   179,
     186,   189,   190,   197,   204,   206,   209,   246,   250,   252,
     259,   282,   297,   318,   327,   340,   345,   347,   355,   365,
     374,   383,   385,   386,   389,   391,   396,   412,   417,   422,
     433,   445,   455,   761,   762,   772,   777,   781,   784,   797,
     800,   805,   810,   811,   812,   815,   817,   824,   828,   830,
     845,   848,   850,   852,   855,   857,   863,   872,   874,   891,
     893,   896,   900,   906,   916,   923,   925,   928,   932,   933,
     944,   955,   965,   971,   975,   981,   985,   987,   989,   991,
     994,  1005,  1006,  1015,  1017,  1018,   455,   526,   528,  1090,
    1148,  1150,   123,   167,   555,  1148,  1148,   319,   326,   573,
    1148,  1148,   364,  1148,  1148,  1135,     9,   260,   318,   580,
    1148,   442,   688,   635,   642,   727,   728,   729,   225,   368,
     418,   368,   418,   368,   418,   368,   418,   368,   418,   438,
    1173,   346,  1162,  1108,  1104,  1105,  1105,   214,   224,   346,
     668,  1148,  1148,   167,   188,   223,   411,     9,    50,   225,
     641,  1109,  1110,  1111,   674,   675,  1109,    30,   619,   620,
     621,   622,  1137,  1174,  1141,   180,   610,  1146,   109,   236,
     756,   763,   773,   778,   782,   785,   798,   801,   806,   813,
     816,   818,   825,   829,   831,   846,   849,   851,  1172,   856,
       1,   858,   864,   873,   875,   892,   894,   897,   901,   907,
     917,   924,   926,   929,   934,   945,   956,   966,   236,   349,
     976,   982,   306,   986,   988,   990,   992,   995,   188,  1007,
    1145,  1019,   195,   236,   243,   315,   378,   448,   527,   529,
     123,   316,   364,   559,  1148,   117,   305,   554,    32,   164,
     244,   569,  1086,  1089,   381,  1086,  1086,   287,  1159,  1159,
     281,  1086,    61,    88,    89,   293,   455,   689,   690,   694,
    1148,   638,   729,   448,   403,   655,   458,  1106,  1107,   400,
     651,  1109,    27,   647,   362,  1127,  1127,  1111,  1156,  1156,
     462,   673,   675,   400,    48,   409,   174,   611,  1108,   455,
     455,   764,  1103,  1104,     6,    82,    94,    98,   184,   225,
     232,   238,   241,   274,   342,   387,   388,   413,   431,   439,
     774,  1072,  1093,  1094,  1103,  1109,  1112,   442,   779,  1059,
    1060,  1061,   236,  1082,  1083,  1084,  1105,   236,  1101,  1103,
    1112,     9,   799,   802,   807,  1073,  1074,  1094,  1078,   405,
     236,   819,  1093,  1100,  1103,   826,  1094,   236,   404,   408,
     832,   833,  1059,   296,   297,   310,   356,   847,     6,  1091,
    1092,  1103,  1103,   853,   136,  1058,  1059,  1091,   693,  1103,
     876,  1103,  1109,  1112,   957,  1105,    94,   895,  1094,   898,
    1094,   902,   177,   236,   908,   911,   912,   913,  1082,  1101,
    1105,  1174,  1078,  1075,  1105,  1078,  1075,     9,   935,  1076,
    1105,   150,   248,   946,   947,   948,   949,   951,   952,   953,
     954,  1079,  1080,  1091,   957,  1078,   973,   972,   112,   977,
     978,  1094,    94,   983,  1093,   693,  1103,  1078,  1103,     8,
      35,  1009,   107,  1075,    17,  1086,   118,   236,   556,  1153,
     441,   570,   570,   376,   456,   564,  1086,  1088,  1148,   172,
     691,   692,   691,  1149,   702,   188,   730,  1108,   402,  1171,
     225,   449,   450,   458,  1069,  1071,  1072,  1095,  1103,  1110,
    1112,   458,  1107,  1105,   236,  1140,  1104,  1104,  1111,  1173,
    1109,  1089,  1089,  1137,  1141,   127,   771,    30,   180,   765,
    1137,  1156,   458,  1103,   458,  1113,   458,  1114,  1156,  1128,
     458,   458,   458,   458,   458,   458,   458,   458,  1113,   128,
     776,   403,   775,  1094,   205,  1122,    56,  1062,  1063,   403,
    1128,   434,   786,   236,  1100,  1103,  1078,   130,   808,   156,
     456,   809,  1074,   348,  1126,   319,  1161,  1077,   132,   823,
     765,   427,   428,   429,   430,   133,   827,    49,   210,   786,
      17,   438,   834,   835,   836,   840,  1133,   100,  1156,  1092,
    1081,   399,  1170,   865,  1174,  1103,    92,   331,   394,   877,
     878,   879,   883,   888,   959,  1094,   403,   137,   899,    49,
     166,   207,   215,   288,   903,   912,   138,   909,   423,   436,
     400,   402,   397,   258,   304,  1123,   180,  1020,  1161,  1020,
    1076,   143,   943,   436,   937,  1098,  1103,  1110,   952,   954,
    1091,   403,  1080,   121,   403,   424,   950,   967,   187,   341,
     974,  1139,   210,   978,  1103,   146,   984,   180,   180,   319,
     321,   993,   112,   996,   333,   380,  1010,  1157,  1020,   529,
     122,   441,   564,  1121,  1130,   557,  1105,   240,   347,  1148,
     561,   562,  1100,   693,   700,  1108,   635,   703,   731,   114,
     656,  1156,  1071,  1071,  1071,    70,   360,   457,  1070,   449,
     450,   451,   452,   454,   461,  1071,   365,  1163,  1152,  1089,
     114,   609,  1098,    25,    26,    67,    69,   103,   104,   105,
     150,   152,   160,   234,   401,   442,  1080,   441,   768,    66,
     233,   301,   766,   767,   149,   310,  1096,  1104,  1069,  1071,
     403,  1071,  1069,  1115,  1104,  1110,  1112,   442,  1071,  1118,
    1071,  1071,  1117,  1071,  1069,  1069,  1071,  1116,  1071,  1073,
    1094,   187,   341,   780,  1122,    12,    13,    14,    20,    58,
     156,   157,   185,   191,   214,   222,   226,   256,   257,   262,
     272,   279,   284,   302,   448,   449,   450,   451,   452,   454,
     456,   457,   459,   460,  1064,  1065,  1066,  1067,  1068,    12,
      13,    14,    58,   214,   256,   257,   262,   272,   279,   302,
     449,   450,   454,   458,  1064,  1065,  1066,  1067,  1068,  1094,
     309,   783,  1084,   787,   187,   341,   791,   324,   416,   803,
     804,  1174,  1059,   213,   266,  1051,  1052,  1053,  1055,   426,
     441,   820,  1174,   163,  1026,  1027,  1026,  1026,  1026,  1094,
    1073,  1094,    21,   404,   408,   841,   842,  1060,   134,   844,
     440,   836,   838,   438,   837,   833,  1104,   114,   854,  1082,
     859,     9,    12,    15,    16,   253,   254,   272,   273,   866,
     870,   171,  1098,     9,    56,   173,   223,   411,   884,   885,
     886,   880,   878,   961,  1130,  1157,   403,  1091,  1073,  1094,
     366,   904,   757,   758,  1058,   914,   915,  1103,  1082,     8,
      35,  1022,  1161,  1100,   210,   918,   930,  1174,   938,  1137,
    1103,   938,   403,   403,   520,   149,   404,   408,  1094,    49,
     218,   968,  1094,  1094,   372,  1094,  1103,   180,  1073,  1094,
    1098,  1139,   210,   999,  1103,   159,   163,  1011,     9,  1016,
    1082,   930,   122,   561,  1105,   280,   563,  1086,   563,   193,
     695,   233,   234,   701,   638,    31,    33,    36,    44,    45,
      46,    66,   158,   176,   180,   181,   194,   233,   242,   276,
     290,   314,   338,   343,   357,   403,   415,   434,   455,   649,
     650,   652,   666,   669,   671,   732,   735,  1157,    28,   115,
     202,   653,   658,   659,   660,   661,   663,  1104,  1110,  1112,
     457,  1071,  1071,  1071,  1071,  1071,  1071,   457,  1071,  1172,
    1152,  1157,  1025,  1027,   447,   446,  1098,  1025,   218,    31,
      33,    36,    46,   176,   181,   194,   242,   290,   314,   338,
     343,   353,   357,   415,   425,   769,   770,  1025,   270,  1155,
    1155,  1155,   767,   766,   236,  1097,  1104,   457,  1103,   461,
     457,  1070,   457,   457,  1070,   457,   457,   457,   457,  1070,
     457,   457,   373,  1031,  1032,  1073,  1092,   341,  1172,   398,
    1169,  1169,   403,  1082,   788,   789,   790,  1139,  1103,  1103,
     163,   289,   792,  1012,  1145,   240,   260,  1031,  1054,  1056,
     131,   814,  1055,    96,   305,   442,  1080,    33,    36,    44,
      45,    46,   158,   176,   194,   242,   290,   343,   353,   415,
     821,   822,  1026,   269,  1028,   265,  1029,   187,  1031,   187,
    1133,   400,   843,   839,   841,   757,  1157,   757,  1172,   331,
     867,  1172,   403,    49,   885,   887,  1098,     9,    56,   223,
     411,   881,   882,  1098,   962,  1131,   200,   285,  1158,   661,
    1091,  1031,   187,  1174,  1077,   138,   910,   759,     8,   180,
     918,  1103,   126,   263,  1041,  1042,  1044,  1051,   240,   260,
     438,   126,   438,   940,   941,  1098,  1097,  1094,  1148,  1051,
     979,  1174,  1103,  1031,   187,   403,     9,   997,   998,  1120,
    1000,  1103,   979,  1000,   307,  1014,   308,  1021,  1022,  1121,
     251,   319,   321,   571,  1148,   173,   696,  1108,   704,  1148,
    1155,   153,   155,  1148,  1101,  1155,  1108,  1103,  1103,  1086,
    1139,   662,   663,   659,  1150,   657,   658,   457,   404,   676,
    1086,  1029,  1025,  1148,  1148,   121,   424,   770,  1100,  1100,
    1100,  1113,  1126,   457,  1071,  1086,  1113,  1113,  1071,  1113,
    1113,  1113,   223,   411,  1113,  1113,  1033,   268,  1034,  1031,
    1092,   156,   284,   156,   284,   789,   279,   745,    86,   325,
     435,   265,   267,   794,  1013,   793,   329,   344,   757,   757,
     820,   820,   820,   820,  1148,   153,   155,  1148,   121,   424,
     822,   757,  1030,  1073,  1074,  1073,  1074,   842,  1059,   757,
    1103,   125,   860,   435,   868,   869,   870,   110,   871,   435,
    1099,  1103,  1109,  1098,    49,   889,   882,   175,   889,   958,
    1148,   285,  1150,  1073,   580,   905,  1174,   760,   915,  1094,
     199,   919,  1174,  1043,  1045,   141,   927,  1044,   142,   931,
     240,  1059,   939,  1058,   940,   262,   969,  1124,   144,   970,
     289,  1036,  1037,   300,  1126,  1073,  1099,   284,  1098,   113,
    1001,   394,  1003,  1157,   154,   264,  1023,  1046,  1047,  1049,
    1052,     7,  1132,   571,  1108,   116,   220,   697,    67,    66,
      67,   192,   233,   234,   258,   303,   376,   390,   414,   436,
     455,   649,   650,   652,   654,   666,   669,   671,   705,   706,
     708,   709,   710,   711,   713,   714,   715,   716,   720,   721,
     448,  1102,  1103,  1108,  1148,  1102,  1148,  1171,   442,   664,
     665,  1148,  1148,  1102,  1102,  1057,  1139,  1057,  1031,   457,
     757,  1035,  1172,   156,  1172,   156,  1094,   129,   796,   795,
     757,  1026,  1026,  1026,  1026,  1102,  1102,  1057,  1057,   757,
    1031,   328,  1031,   328,   861,   136,   862,   869,   102,  1143,
     889,   889,  1099,  1022,   207,   434,   963,  1086,  1148,  1031,
     240,   260,    49,   240,   218,   920,   198,   240,   260,   437,
     757,   757,   936,   757,   942,   693,  1064,  1065,  1066,  1067,
    1068,  1038,   145,   980,   267,  1039,  1103,  1031,  1031,   998,
    1147,    95,  1002,  1147,  1036,   166,   207,   215,   288,  1008,
    1077,  1048,  1050,   148,  1024,  1049,   293,  1080,  1102,  1148,
      91,   221,   698,   271,  1155,   203,   722,   270,   271,   719,
    1134,   192,   438,  1148,  1156,  1148,  1103,   711,   258,   299,
     717,   718,  1108,   247,   299,   449,   450,   734,   247,   299,
     449,   450,   733,   665,  1085,  1109,  1102,   757,  1172,  1172,
     757,  1074,  1074,   757,    49,   889,   406,   890,   307,  1077,
     187,   288,   964,   960,   344,  1094,  1148,   921,  1041,  1052,
     240,   240,   757,   757,   757,  1040,  1103,  1147,  1103,   147,
    1004,   757,   757,   233,   234,  1151,  1108,  1148,  1148,   174,
     699,  1148,  1149,  1148,  1058,  1103,   712,  1086,    90,    91,
     116,   294,   295,   335,   336,   707,   180,   293,  1108,   718,
    1102,  1102,  1151,  1031,  1031,  1094,  1094,  1148,  1077,   307,
    1105,   423,   693,   140,   922,   757,  1103,  1108,  1108,  1148,
    1108,  1108,  1126,  1094,   911,  1148,  1058,  1108,    49,   911,
    1094
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 771 "parser.y"
    {
	perform_stack = NULL;
	current_statement = NULL;
	next_label_id = 0;
	current_linage = 0;
	current_storage = 0;
	eval_level = 0;
	eval_inc = 0;
	eval_inc2 = 0;
	prog_end = 0;
	depth = 0;
	inspect_keyword = 0;
	check_unreached = 0;
	samearea = 1;
	memset ((char *)eval_check, 0, sizeof(eval_check));
	memset ((char *)term_array, 0, sizeof(term_array));
	linage_file = NULL;
	next_label_list = NULL;
	current_program = cb_build_program (NULL, 0);
	cb_build_registers ();
	current_program->flag_main = cb_flag_main;
  }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 795 "parser.y"
    {
	current_section = NULL;
	current_paragraph = NULL;
	if (!current_program->flag_validated) {
		current_program->flag_validated = 1;
		cb_validate_program_body (current_program);
	}
	if (depth > 1) {
		cb_error (_("Multiple PROGRAM-ID's without matching END PROGRAM"));
	}
	if (errorcount > 0) {
		YYABORT;
	}
	if (!current_program->entry_list) {
		emit_entry (current_program->program_id, 0, NULL);
	}
  }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 826 "parser.y"
    { cb_validate_program_environment (current_program); }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 827 "parser.y"
    { cb_validate_program_data (current_program); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 835 "parser.y"
    { cb_validate_program_environment (current_program); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 836 "parser.y"
    { cb_validate_program_data (current_program); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 844 "parser.y"
    { cb_validate_program_environment (current_program); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 845 "parser.y"
    { cb_validate_program_data (current_program); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 857 "parser.y"
    {
	char			*s;

	current_section = NULL;
	current_paragraph = NULL;
	if (CB_LITERAL_P ((yyvsp[(2) - (3)]))) {
		s = (char *)(CB_LITERAL ((yyvsp[(2) - (3)]))->data);
	} else {
		s = (char *)(CB_NAME ((yyvsp[(2) - (3)])));
	}
	if (depth) {
		depth--;
	}
	if (cb_allow_end_program_with_wrong_name) {
		/* ignore wrong program-id. */
	} else if (strcmp (stack_progid[depth], s)) {
		cb_error (_("END PROGRAM '%s' is different to PROGRAM-ID '%s'"),
			s, stack_progid[depth]);
	}
	if (!current_program->flag_validated) {
		current_program->flag_validated = 1;
		cb_validate_program_body (current_program);
	}
  }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 885 "parser.y"
    {
	char			*s;

	current_section = NULL;
	current_paragraph = NULL;
	if (CB_LITERAL_P ((yyvsp[(2) - (3)]))) {
		s = (char *)(CB_LITERAL ((yyvsp[(2) - (3)]))->data);
	} else {
		s = (char *)(CB_NAME ((yyvsp[(2) - (3)])));
	}
	if (depth) {
		depth--;
	}
	if (strcmp (stack_progid[depth], s)) {
		cb_error (_("END PROGRAM '%s' is different to PROGRAM-ID '%s'"),
			s, stack_progid[depth]);
	}
	if (!current_program->flag_validated) {
		current_program->flag_validated = 1;
		cb_validate_program_body (current_program);
	}
  }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 911 "parser.y"
    {
	char			*s;

	current_section = NULL;
	current_paragraph = NULL;
	if (CB_LITERAL_P ((yyvsp[(2) - (3)]))) {
		s = (char *)(CB_LITERAL ((yyvsp[(2) - (3)]))->data);
	} else {
		s = (char *)(CB_NAME ((yyvsp[(2) - (3)])));
	}
	if (depth) {
		depth--;
	}
	if (strcmp (stack_progid[depth], s)) {
		cb_error (_("END FUNCTION '%s' is different to FUNCTION-ID '%s'"),
			s, stack_progid[depth]);
	}
	if (!current_program->flag_validated) {
		current_program->flag_validated = 1;
		cb_validate_program_body (current_program);
	}
  }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 942 "parser.y"
    {
	current_section = NULL;
	current_paragraph = NULL;
	if (CB_LITERAL_P ((yyvsp[(3) - (4)]))) {
		stack_progid[depth] = (char *)(CB_LITERAL ((yyvsp[(3) - (4)]))->data);
	} else {
		stack_progid[depth] = (char *)(CB_NAME ((yyvsp[(3) - (4)])));
	}
	if (prog_end) {
		if (!current_program->flag_validated) {
			current_program->flag_validated = 1;
			cb_validate_program_body (current_program);
		}
		perform_stack = NULL;
		current_statement = NULL;
		next_label_id = 0;
		current_linage = 0;
		current_storage = 0;
		eval_level = 0;
		inspect_keyword = 0;
		check_unreached = 0;
		eval_inc = 0;
		eval_inc2 = 0;
		samearea = 1;
		memset ((char *)eval_check, 0, sizeof(eval_check));
		memset ((char *)term_array, 0, sizeof(term_array));
		linage_file = NULL;
		next_label_list = NULL;
		current_program = cb_build_program (current_program, depth);
		cb_build_registers ();
	} else {
		prog_end = 1;
	}
	depth++;
	current_program->program_id = cb_build_program_id ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
  }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 983 "parser.y"
    {
	cb_error (_("FUNCTION-ID is not yet implemented"));
	current_section = NULL;
	current_paragraph = NULL;
	if (CB_LITERAL_P ((yyvsp[(3) - (5)]))) {
		stack_progid[depth] = (char *)(CB_LITERAL ((yyvsp[(3) - (5)]))->data);
	} else {
		stack_progid[depth] = (char *)(CB_NAME ((yyvsp[(3) - (5)])));
	}
	if (prog_end) {
		if (!current_program->flag_validated) {
			current_program->flag_validated = 1;
			cb_validate_program_body (current_program);
		}
		perform_stack = NULL;
		current_statement = NULL;
		next_label_id = 0;
		current_linage = 0;
		current_storage = 0;
		eval_level = 0;
		inspect_keyword = 0;
		check_unreached = 0;
		eval_inc = 0;
		eval_inc2 = 0;
		samearea = 1;
		memset ((char *)eval_check, 0, sizeof(eval_check));
		memset ((char *)term_array, 0, sizeof(term_array));
		linage_file = NULL;
		next_label_list = NULL;
		current_program = cb_build_program (current_program, depth);
		cb_build_registers ();
	} else {
		prog_end = 1;
	}
	depth++;
	current_program->program_id = cb_build_program_id ((yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]));
	current_program->prog_type = CB_FUNCTION_TYPE;
	current_program->flag_recursive = 1;
	current_program->flag_initial = 1;
  }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 1031 "parser.y"
    { (yyval) = NULL; }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 1032 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 1041 "parser.y"
    {
	if (!current_program->nested_level) {
		cb_error (_("COMMON may only be used in a nested program"));
	}
	current_program->flag_common = 1;
  }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 1048 "parser.y"
    {
	if (!current_program->nested_level) {
		cb_error (_("COMMON may only be used in a nested program"));
	}
	current_program->flag_common = 1;
  }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 1059 "parser.y"
    {
	current_program->flag_initial = 1;
  }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 1063 "parser.y"
    {
	current_program->flag_recursive = 1;
	current_program->flag_initial = 1;
  }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 1088 "parser.y"
    {
	if (current_program->nested_level) {
		cb_error (_("CONFIGURATION SECTION not allowed in nested programs"));
	}
  }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 1123 "parser.y"
    {
	cb_verify (cb_debugging_line, "DEBUGGING MODE");
  }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 1129 "parser.y"
    { }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 1160 "parser.y"
    {
	cb_verify (cb_memory_size_clause, "MEMORY SIZE");
  }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 1172 "parser.y"
    {
	current_program->collating_sequence = (yyvsp[(4) - (4)]);
  }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 1179 "parser.y"
    {
	/* Ignore */
  }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 1204 "parser.y"
    {
	current_program->function_spec_list = (yyvsp[(2) - (3)]);
  }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 1208 "parser.y"
    {
	functions_are_all = 1;
  }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 1214 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 1216 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 1257 "parser.y"
    {
	save_tree_1 = lookup_system_name (CB_NAME ((yyvsp[(1) - (3)])));
	if (save_tree_1 == cb_error_node) {
		cb_error_x ((yyvsp[(1) - (3)]), _("Unknown system-name '%s'"), CB_NAME ((yyvsp[(1) - (3)])));
	} else if (CB_SYSTEM_NAME(save_tree_1)->token != CB_DEVICE_CONSOLE) {
		cb_error_x (save_tree_1, _("Invalid CRT clause"));
	}
	/* current_program->flag_screen = 1; */
  }
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 1267 "parser.y"
    {
	save_tree_1 = lookup_system_name (CB_NAME ((yyvsp[(1) - (3)])));
	if (save_tree_1 == cb_error_node) {
		cb_error_x ((yyvsp[(1) - (3)]), _("Unknown system-name '%s'"), CB_NAME ((yyvsp[(1) - (3)])));
	} else {
		cb_define ((yyvsp[(3) - (3)]), save_tree_1);
	}
	save_tree_2 = (yyvsp[(3) - (3)]);
  }
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 1278 "parser.y"
    {
	save_tree_1 = lookup_system_name (CB_NAME ((yyvsp[(1) - (2)])));
	if (save_tree_1 == cb_error_node) {
		cb_error_x ((yyvsp[(1) - (2)]), _("Unknown system-name '%s'"), CB_NAME ((yyvsp[(1) - (2)])));
	}
	save_tree_2 = NULL;
  }
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 1287 "parser.y"
    {
	if (cb_enable_special_names_argument_clause) {
		save_tree_1 = lookup_system_name ("ARGUMENT-NUMBER");
		if (save_tree_1 == cb_error_node) {
			cb_error_x ((yyvsp[(1) - (3)]), _("Unknown system-name '%s'"), CB_NAME ((yyvsp[(1) - (3)])));
		} else {
			cb_define ((yyvsp[(3) - (3)]), save_tree_1);
		}
		save_tree_2 = (yyvsp[(3) - (3)]);
	} else {
		cb_error (_("SPECIAL-NAMES with ARGUMENT-NUMBER clause is not yet supported"));
	}
  }
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 1301 "parser.y"
    {
	if (cb_enable_special_names_argument_clause) {
		save_tree_1 = lookup_system_name ("ARGUMENT-VALUE");
		if (save_tree_1 == cb_error_node) {
			cb_error_x ((yyvsp[(1) - (3)]), _("Unknown system-name '%s'"), CB_NAME ((yyvsp[(1) - (3)])));
		} else {
			cb_define ((yyvsp[(3) - (3)]), save_tree_1);
		}
		save_tree_2 = (yyvsp[(3) - (3)]);
	} else {
		cb_error (_("SPECIAL-NAMES with ARGUMENT-VALUE clause is not yet supported"));
	}
  }
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 1315 "parser.y"
    {
	if (cb_enable_special_names_environment_clause) {
		save_tree_1 = lookup_system_name ("ENVIRONMENT-NAME");
		if (save_tree_1 == cb_error_node) {
			cb_error_x ((yyvsp[(1) - (3)]), _("Unknown system-name '%s'"), CB_NAME ((yyvsp[(1) - (3)])));
		} else {
			cb_define ((yyvsp[(3) - (3)]), save_tree_1);
		}
		save_tree_2 = (yyvsp[(3) - (3)]);
	} else {
		cb_error (_("SPECIAL-NAMES with ENVIRONMENT-NAME clause is not yet supported"));
	}
  }
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 1329 "parser.y"
    {
	if (cb_enable_special_names_environment_clause) {
		save_tree_1 = lookup_system_name ("ENVIRONMENT-VALUE");
		if (save_tree_1 == cb_error_node) {
			cb_error_x ((yyvsp[(1) - (3)]), _("Unknown system-name '%s'"), CB_NAME ((yyvsp[(1) - (3)])));
		} else {
			cb_define ((yyvsp[(3) - (3)]), save_tree_1);
		}
		save_tree_2 = (yyvsp[(3) - (3)]);
	} else {
		cb_error (_("SPECIAL-NAMES with ENVIRONMENT-VALUE clause is not yet supported"));
	}
  }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 1355 "parser.y"
    {
	if (!save_tree_2 && !cb_switch_no_mnemonic) {
		cb_error_x ((yyvsp[(4) - (4)]), _("'%s' with no mnemonic name"), CB_NAME ((yyvsp[(4) - (4)])));
	} else {
		cb_define_switch_name ((yyvsp[(4) - (4)]), save_tree_1, (yyvsp[(1) - (4)]), save_tree_2);
	}
  }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 1365 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 1366 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 1374 "parser.y"
    {
	save_tree_1 = (yyvsp[(2) - (2)]);
  }
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 1378 "parser.y"
    {
	current_program->alphabet_name_list =
		cb_list_add (current_program->alphabet_name_list, (yyvsp[(5) - (5)]));
  }
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 1385 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_NATIVE); }
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 1386 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_1); }
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 1387 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_2); }
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 1388 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_EBCDIC); }
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 1390 "parser.y"
    {
	(yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_CUSTOM);
	CB_ALPHABET_NAME ((yyval))->custom_list = (yyvsp[(1) - (1)]);
  }
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 1397 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 1399 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 1403 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 1404 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 1406 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (2)]));
	save_tree_2 = (yyval);
  }
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 1411 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (4)]);
  }
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 1422 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 1423 "parser.y"
    { (yyval) = cb_space; }
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 1424 "parser.y"
    { (yyval) = cb_zero; }
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 1425 "parser.y"
    { (yyval) = cb_quote; }
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 1426 "parser.y"
    { (yyval) = cb_norm_high; }
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 1427 "parser.y"
    { (yyval) = cb_norm_low; }
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 1431 "parser.y"
    { cb_list_add (save_tree_2, (yyvsp[(1) - (1)])); }
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 1432 "parser.y"
    { cb_list_add (save_tree_2, cb_space); }
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 1433 "parser.y"
    { cb_list_add (save_tree_2, cb_zero); }
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 1434 "parser.y"
    { cb_list_add (save_tree_2, cb_quote); }
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 1435 "parser.y"
    { cb_list_add (save_tree_2, cb_norm_high); }
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 1436 "parser.y"
    { cb_list_add (save_tree_2, cb_norm_low); }
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 1444 "parser.y"
    {
	if ((yyvsp[(3) - (3)])) {
		current_program->symbolic_list =
			cb_list_add (current_program->symbolic_list, (yyvsp[(3) - (3)]));
	}
	PENDING ("SYMBOLIC CHARACTERS");
  }
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 1455 "parser.y"
    {
	if (cb_list_length ((yyvsp[(1) - (3)])) != cb_list_length ((yyvsp[(3) - (3)]))) {
		cb_error (_("Invalid SYMBOLIC clause"));
		(yyval) = NULL;
	} else {
		(yyval) = NULL;
	}
  }
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 1466 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 1467 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 1471 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 1472 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 1480 "parser.y"
    {
	current_program->class_name_list =
			cb_list_add (current_program->class_name_list,
			cb_build_class_name ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])));
  }
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 1488 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 1489 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 1493 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 1495 "parser.y"
    {
	/* if (CB_LITERAL ($1)->data[0] < CB_LITERAL ($3)->data[0]) */
	if (literal_value ((yyvsp[(1) - (3)])) < literal_value ((yyvsp[(3) - (3)]))) {
		(yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	} else {
		(yyval) = cb_build_pair ((yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]));
	}
  }
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1509 "parser.y"
    {
	cb_tree	l;

	l = cb_build_locale_name ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
	if (l != cb_error_node) {
		current_program->locale_list =
			cb_list_add (current_program->locale_list, l);
	}
  }
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1524 "parser.y"
    {
	unsigned char *s = CB_LITERAL ((yyvsp[(4) - (4)]))->data;

	if (CB_LITERAL ((yyvsp[(4) - (4)]))->size != 1) {
		cb_error_x ((yyvsp[(4) - (4)]), _("Invalid currency sign '%s'"), s);
	}
	switch (*s) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'a':
	case 'A':
	case 'b':
	case 'B':
	case 'c':
	case 'C':
	case 'd':
	case 'D':
	case 'e':
	case 'E':
	case 'n':
	case 'N':
	case 'p':
	case 'P':
	case 'r':
	case 'R':
	case 's':
	case 'S':
	case 'v':
	case 'V':
	case 'x':
	case 'X':
	case 'z':
	case 'Z':
	case '+':
	case '-':
	case ',':
	case '.':
	case '*':
	case '/':
	case ';':
	case '(':
	case ')':
	case '=':
	case '"':
	case ' ':
		cb_error_x ((yyvsp[(4) - (4)]), _("Invalid currency sign '%s'"), s);
		break;
	default:
		break;
	}
	current_program->currency_symbol = s[0];
  }
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1591 "parser.y"
    {
	current_program->decimal_point = ',';
	current_program->numeric_separator = '.';
  }
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1601 "parser.y"
    { current_program->cursor_pos = (yyvsp[(3) - (3)]); }
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1608 "parser.y"
    { current_program->crt_status = (yyvsp[(4) - (4)]); }
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1615 "parser.y"
    {  PENDING ("SCREEN CONTROL"); }
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1621 "parser.y"
    {  PENDING ("EVENT STATUS"); }
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1633 "parser.y"
    {
	/* hack for MF compatibility */
	if (cb_relaxed_syntax_check) {
		cb_warning (_("INPUT-OUTPUT SECTION header missing - assumed"));
	} else {
		cb_error (_("INPUT-OUTPUT SECTION header missing"));
	}
  }
    break;

  case 161:
/* Line 1792 of yacc.c  */
#line 1642 "parser.y"
    {
	/* hack for MF compatibility */
	if (cb_relaxed_syntax_check) {
		cb_warning (_("INPUT-OUTPUT SECTION header missing - assumed"));
	} else {
		cb_error (_("INPUT-OUTPUT SECTION header missing"));
	}
  }
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 1667 "parser.y"
    {
	organized_seen = 0;
	if ((yyvsp[(3) - (3)]) == cb_error_node) {
		YYERROR;
	}

	/* build new file */
	current_file = build_file ((yyvsp[(3) - (3)]));
	current_file->optional = CB_INTEGER ((yyvsp[(2) - (3)]))->val;

	/* register the file */
	current_program->file_list =
		cb_cons (CB_TREE (current_file), current_program->file_list);
  }
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 1682 "parser.y"
    {
	validate_file (current_file, (yyvsp[(3) - (6)]));
  }
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 1714 "parser.y"
    {
	current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
  }
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1718 "parser.y"
    {
	current_file->fileid_assign = 1;
	current_file->assign = cb_build_assignment_name (current_file, cb_build_reference ("DISK"));
  }
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1723 "parser.y"
    {
	current_file->fileid_assign = 1;
	current_file->assign = cb_build_assignment_name (current_file, cb_build_reference ("PRINTER"));
  }
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1731 "parser.y"
    { current_file->organization = COB_ORG_LINE_SEQUENTIAL; }
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1736 "parser.y"
    {
	current_file->external_assign = 1;
  }
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1740 "parser.y"
    {
	current_file->external_assign = 0;
  }
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1748 "parser.y"
    {
	const char	*s;

	s = "$#@DUMMY@#$";
	(yyval) = cb_build_alphanumeric_literal ((unsigned char *)s, strlen (s));
  }
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1755 "parser.y"
    {

	if (!(yyvsp[(1) - (2)]) || ((yyvsp[(1) - (2)]) && CB_TREE_CLASS ((yyvsp[(1) - (2)])) == CB_CLASS_NUMERIC)) {
		if ((yyvsp[(2) - (2)])) {
			if (CB_CHAIN ((yyvsp[(2) - (2)]))) {
				PENDING (_("ASSIGN TO multiple external device names"));
			}
			(yyval) = CB_VALUE ((yyvsp[(2) - (2)]));
		}
	} else {
		if((yyvsp[(2) - (2)])) {
			PENDING (_("ASSIGN TO multiple external device names"));
		}
		(yyval) = (yyvsp[(1) - (2)]);
	}
  }
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 1774 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1775 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1785 "parser.y"
    { current_file->access_mode = COB_ACCESS_SEQUENTIAL; }
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1786 "parser.y"
    { current_file->access_mode = COB_ACCESS_DYNAMIC; }
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 1787 "parser.y"
    { current_file->access_mode = COB_ACCESS_RANDOM; }
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 1795 "parser.y"
    {
	struct cb_alt_key *p;
	struct cb_alt_key *l;

	p = cobc_malloc (sizeof (struct cb_alt_key));
	p->key = (yyvsp[(5) - (6)]);
	p->duplicates = CB_INTEGER ((yyvsp[(6) - (6)]))->val;
	p->component_list = NULL;
	p->next = NULL;

	/* add to the end of list */
	if (current_file->alt_key_list == NULL) {
		current_file->alt_key_list = p;
	} else {
		l = current_file->alt_key_list;
		for (; l->next; l = l->next);
		l->next = p;
	}
  }
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1815 "parser.y"
    {
#if	defined(WITH_CISAM) || defined(WITH_DISAM) || defined(WITH_VBISAM) || defined(WITH_INDEX_EXTFH)
	struct cb_alt_key *p;
	struct cb_alt_key *l;
	cb_tree composite_key;
	struct cb_key_component *comp;

	p = cobc_malloc (sizeof (struct cb_alt_key));
	/* generate field (in w-s) for composite-key */
	if (!(yyvsp[(6) - (8)])) {
		/* dialect */
		composite_key = cb_build_field (cb_build_anonymous ());
		comp = cobc_malloc (sizeof (struct cb_key_component));
		comp->next = key_component_list;
		comp->component = (yyvsp[(5) - (8)]);
		key_component_list = comp;
	} else {
		/* standard or mf syntax */
		composite_key = cb_build_field ((yyvsp[(5) - (8)]));
	}
	if (composite_key == cb_error_node) {
		YYERROR;
	} else {
		composite_key->category = CB_CATEGORY_ALPHANUMERIC;
		((struct cb_field *)composite_key)->count = 1;
		p->key = cb_build_field_reference ((struct cb_field *)composite_key, NULL);
		p->component_list = key_component_list;
		p->duplicates = CB_INTEGER ((yyvsp[(8) - (8)]))->val;
		p->next = NULL;

		/* add to the end of list */
		if (current_file->alt_key_list == NULL) {
			current_file->alt_key_list = p;
		} else {
			l = current_file->alt_key_list;
			for (; l->next; l = l->next);
			l->next = p;
		}
	}
#else
	PENDING ("SPLIT KEYS");
#endif
  }
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 1861 "parser.y"
    {
	key_component_list = NULL;
  }
    break;

  case 209:
/* Line 1792 of yacc.c  */
#line 1870 "parser.y"
    {
	struct cb_key_component *c;
	struct cb_key_component *comp = cobc_malloc (sizeof (struct cb_key_component));
	comp->next = NULL;
	comp->component = (yyvsp[(1) - (1)]);
	if (key_component_list == NULL) {
		key_component_list = comp;
	} else {
		for (c = key_component_list; c->next != NULL; c = c->next);
		c->next = comp;
	}
  }
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 1885 "parser.y"
    { (yyval) = NULL; }
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 1886 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1887 "parser.y"
    { (yyval) = cb_int('='); }
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1894 "parser.y"
    {
	PENDING ("COLLATING SEQUENCE");
  }
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1904 "parser.y"
    {
	current_file->file_status = (yyvsp[(4) - (5)]);
	if ((yyvsp[(5) - (5)])) {
		PENDING ("2nd FILE STATUS");
	}
  }
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1925 "parser.y"
    { current_file->lock_mode = COB_LOCK_MANUAL; }
    break;

  case 220:
/* Line 1792 of yacc.c  */
#line 1926 "parser.y"
    { current_file->lock_mode = COB_LOCK_AUTOMATIC; }
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 1927 "parser.y"
    { current_file->lock_mode = COB_LOCK_EXCLUSIVE; }
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 1933 "parser.y"
    {
	current_file->lock_mode |= COB_LOCK_MULTIPLE;
  }
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 1936 "parser.y"
    { PENDING ("WITH ROLLBACK"); }
    break;

  case 230:
/* Line 1792 of yacc.c  */
#line 1953 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_INDEXED;
		organized_seen = 1;
	}
  }
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 1962 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_SEQUENTIAL;
		organized_seen = 1;
	}
  }
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 1971 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = cb_default_organization;
		organized_seen = 1;
	}
  }
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 1980 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_RELATIVE;
		organized_seen = 1;
	}
  }
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 1989 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_LINE_SEQUENTIAL;
		organized_seen = 1;
	}
  }
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 2004 "parser.y"
    {
	cb_verify (cb_padding_character_clause, "PADDING CHARACTER");
  }
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 2013 "parser.y"
    { /* ignored */ }
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 2021 "parser.y"
    {
	current_file->key = (yyvsp[(4) - (4)]);
  }
    break;

  case 238:
/* Line 1792 of yacc.c  */
#line 2025 "parser.y"
    {
	/* SPLIT KEY use */
#if	defined(WITH_CISAM) || defined(WITH_DISAM) || defined(WITH_VBISAM) || defined(WITH_INDEX_EXTFH)

	cb_tree composite_key;	
	struct cb_key_component *comp;

	/* generate field (in w-s) for composite-key */
	if (!(yyvsp[(5) - (6)])) {
		/* dialect */
		composite_key = cb_build_field (cb_build_anonymous ());
		comp = cobc_malloc (sizeof (struct cb_key_component));
		comp->next = key_component_list;
		comp->component = (yyvsp[(4) - (6)]);
		key_component_list = comp;
	} else {
		/* standard or mf syntax */
		composite_key = cb_build_field ((yyvsp[(4) - (6)]));
	}
	if (composite_key == cb_error_node) {
		YYERROR;
	} else {
		composite_key->category = CB_CATEGORY_ALPHANUMERIC;
		((struct cb_field *)composite_key)->count = 1;
		current_file->key = cb_build_field_reference ((struct cb_field *)composite_key, NULL);
		current_file->component_list = key_component_list;
	}
#else
	PENDING ("SPLIT KEYS");
#endif
  }
    break;

  case 239:
/* Line 1792 of yacc.c  */
#line 2062 "parser.y"
    { current_file->key = (yyvsp[(4) - (4)]); }
    break;

  case 240:
/* Line 1792 of yacc.c  */
#line 2069 "parser.y"
    { /* ignored */ }
    break;

  case 241:
/* Line 1792 of yacc.c  */
#line 2070 "parser.y"
    { /* ignored */ }
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 2077 "parser.y"
    { current_file->sharing = (yyvsp[(3) - (3)]); }
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 2081 "parser.y"
    { (yyval) = NULL; PENDING ("SHARING ALL OTHER"); }
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 2082 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 2083 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 246:
/* Line 1792 of yacc.c  */
#line 2089 "parser.y"
    { PENDING ("NOMINAL KEY"); }
    break;

  case 257:
/* Line 1792 of yacc.c  */
#line 2120 "parser.y"
    {
	cb_tree l;

	switch (CB_INTEGER ((yyvsp[(2) - (5)]))->val) {
	case 0:
		/* SAME AREA */
		break;
	case 1:
		/* SAME RECORD */
		for (l = (yyvsp[(5) - (5)]); l; l = CB_CHAIN (l)) {
			if (CB_VALUE (l) != cb_error_node) {
				CB_FILE (cb_ref (CB_VALUE (l)))->same_clause = samearea;
			}
		}
		samearea++;
		break;
	case 2:
		/* SAME SORT-MERGE */
		break;
	}
  }
    break;

  case 258:
/* Line 1792 of yacc.c  */
#line 2144 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 259:
/* Line 1792 of yacc.c  */
#line 2145 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 260:
/* Line 1792 of yacc.c  */
#line 2146 "parser.y"
    { (yyval) = cb_int2; }
    break;

  case 261:
/* Line 1792 of yacc.c  */
#line 2147 "parser.y"
    { (yyval) = cb_int2; }
    break;

  case 262:
/* Line 1792 of yacc.c  */
#line 2154 "parser.y"
    {
	cb_verify (cb_multiple_file_tape_clause, "MULTIPLE FILE TAPE");
  }
    break;

  case 265:
/* Line 1792 of yacc.c  */
#line 2165 "parser.y"
    { }
    break;

  case 271:
/* Line 1792 of yacc.c  */
#line 2182 "parser.y"
    {
	PENDING ("APPLY COMMITMENT-CONTROL");
  }
    break;

  case 272:
/* Line 1792 of yacc.c  */
#line 2186 "parser.y"
    {
	PENDING ("APPLY CYL-OVERFLOW");
  }
    break;

  case 273:
/* Line 1792 of yacc.c  */
#line 2190 "parser.y"
    {
	PENDING ("APPLY CORE-INDEX");
  }
    break;

  case 274:
/* Line 1792 of yacc.c  */
#line 2194 "parser.y"
    {
	PENDING ("APPLY FORMS-OVERLAY");
  }
    break;

  case 275:
/* Line 1792 of yacc.c  */
#line 2198 "parser.y"
    {
	PENDING ("APPLY CLOSE-NOFEED");
  }
    break;

  case 279:
/* Line 1792 of yacc.c  */
#line 2223 "parser.y"
    { current_storage = CB_STORAGE_FILE; }
    break;

  case 281:
/* Line 1792 of yacc.c  */
#line 2226 "parser.y"
    {
	/* hack for MF compatibility */
	if (cb_relaxed_syntax_check) {
		cb_warning (_("FILE SECTION header missing - assumed"));
	} else {
		cb_error (_("FILE SECTION header missing"));
	}
	current_storage = CB_STORAGE_FILE;
  }
    break;

  case 285:
/* Line 1792 of yacc.c  */
#line 2245 "parser.y"
    {
	if ((yyvsp[(3) - (3)]) && (yyvsp[(3) - (3)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(3) - (3)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  }
    break;

  case 286:
/* Line 1792 of yacc.c  */
#line 2257 "parser.y"
    {
	if ((yyvsp[(2) - (2)]) && (yyvsp[(2) - (2)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(2) - (2)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  }
    break;

  case 288:
/* Line 1792 of yacc.c  */
#line 2268 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 289:
/* Line 1792 of yacc.c  */
#line 2269 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 290:
/* Line 1792 of yacc.c  */
#line 2279 "parser.y"
    {
	if ((yyvsp[(1) - (1)]) == cb_error_node) {
		YYERROR;
	}

	current_file = CB_FILE (cb_ref ((yyvsp[(1) - (1)])));
	if ((yyvsp[(0) - (1)]) == cb_int1) {
		current_file->organization = COB_ORG_SORT;
	}
  }
    break;

  case 291:
/* Line 1792 of yacc.c  */
#line 2290 "parser.y"
    {
	/* Shut up bison */
	dummy_tree = (yyvsp[(2) - (4)]);
  }
    break;

  case 294:
/* Line 1792 of yacc.c  */
#line 2302 "parser.y"
    {
	if (current_file->global) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->external = 1;
  }
    break;

  case 295:
/* Line 1792 of yacc.c  */
#line 2309 "parser.y"
    {
	if (current_file->external) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->global = 1;
  }
    break;

  case 306:
/* Line 1792 of yacc.c  */
#line 2332 "parser.y"
    { /* ignored */ }
    break;

  case 310:
/* Line 1792 of yacc.c  */
#line 2342 "parser.y"
    {
	if (current_file->organization == COB_ORG_LINE_SEQUENTIAL) {
		cb_warning (_("RECORD clause ignored for LINE SEQUENTIAL"));
	} else {
		current_file->record_max = cb_get_int ((yyvsp[(3) - (4)]));
		if (current_file->record_max < 1)  {
			current_file->record_max = 1;
			cb_error (_("RECORD clause invalid"));
		}
	}
  }
    break;

  case 311:
/* Line 1792 of yacc.c  */
#line 2354 "parser.y"
    {
	int	error_ind = 0;

	if (current_file->organization == COB_ORG_LINE_SEQUENTIAL) {
		cb_warning (_("RECORD clause ignored for LINE SEQUENTIAL"));
	} else {
		current_file->record_min = cb_get_int ((yyvsp[(3) - (6)]));
		current_file->record_max = cb_get_int ((yyvsp[(5) - (6)]));
		if (current_file->record_min < 0)  {
			current_file->record_min = 0;
			error_ind = 1;
		}
		if (current_file->record_max < 1)  {
			current_file->record_max = 1;
			error_ind = 1;
		}
		if (current_file->record_max <= current_file->record_min)  {
			error_ind = 1;
		}
		if (error_ind) {
			cb_error (_("RECORD clause invalid"));
		}
	}
  }
    break;

  case 312:
/* Line 1792 of yacc.c  */
#line 2380 "parser.y"
    {
	int	error_ind = 0;

	current_file->record_min = (yyvsp[(6) - (9)]) ? cb_get_int ((yyvsp[(6) - (9)])) : 0;
	current_file->record_max = (yyvsp[(7) - (9)]) ? cb_get_int ((yyvsp[(7) - (9)])) : 0;
	if ((yyvsp[(6) - (9)]) && current_file->record_min < 0)  {
		current_file->record_min = 0;
		error_ind = 1;
	}
	if ((yyvsp[(7) - (9)]) && current_file->record_max < 1)  {
		current_file->record_max = 1;
		error_ind = 1;
	}
	if (((yyvsp[(6) - (9)]) || (yyvsp[(7) - (9)])) && current_file->record_max <= current_file->record_min)  {
		error_ind = 1;
	}
	if (error_ind) {
		cb_error (_("RECORD clause invalid"));
	}
  }
    break;

  case 314:
/* Line 1792 of yacc.c  */
#line 2404 "parser.y"
    {
	current_file->record_depending = (yyvsp[(3) - (3)]);
  }
    break;

  case 315:
/* Line 1792 of yacc.c  */
#line 2410 "parser.y"
    { (yyval) = NULL; }
    break;

  case 316:
/* Line 1792 of yacc.c  */
#line 2411 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 317:
/* Line 1792 of yacc.c  */
#line 2415 "parser.y"
    { (yyval) = NULL; }
    break;

  case 318:
/* Line 1792 of yacc.c  */
#line 2416 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 319:
/* Line 1792 of yacc.c  */
#line 2424 "parser.y"
    {
	cb_verify (cb_label_records_clause, "LABEL RECORDS");
  }
    break;

  case 322:
/* Line 1792 of yacc.c  */
#line 2439 "parser.y"
    {
	cb_verify (cb_value_of_clause, "VALUE OF");
  }
    break;

  case 323:
/* Line 1792 of yacc.c  */
#line 2443 "parser.y"
    {
	if (!current_file->assign) {
		current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
	}
  }
    break;

  case 326:
/* Line 1792 of yacc.c  */
#line 2459 "parser.y"
    {
	cb_verify (cb_data_records_clause, "DATA RECORDS");
  }
    break;

  case 327:
/* Line 1792 of yacc.c  */
#line 2470 "parser.y"
    {
	if (current_file->organization != COB_ORG_LINE_SEQUENTIAL
	    && current_file->organization != COB_ORG_SEQUENTIAL) {
		cb_error (_("LINAGE clause with wrong file type"));
		(yyval) = cb_error_node;
	} else {
		current_file->linage = (yyvsp[(3) - (5)]);
		current_file->organization = COB_ORG_LINE_SEQUENTIAL;
		if (current_linage == 0) {
			linage_file = current_file;
		}
		current_linage++;
	}
  }
    break;

  case 333:
/* Line 1792 of yacc.c  */
#line 2498 "parser.y"
    {
	current_file->latfoot = (yyvsp[(4) - (5)]);
  }
    break;

  case 334:
/* Line 1792 of yacc.c  */
#line 2505 "parser.y"
    {
	current_file->lattop = (yyvsp[(3) - (4)]);
  }
    break;

  case 335:
/* Line 1792 of yacc.c  */
#line 2512 "parser.y"
    {
	current_file->latbot = (yyvsp[(3) - (3)]);
  }
    break;

  case 336:
/* Line 1792 of yacc.c  */
#line 2521 "parser.y"
    { /* ignore */ }
    break;

  case 337:
/* Line 1792 of yacc.c  */
#line 2529 "parser.y"
    {
	if ((yyvsp[(3) - (3)]) != cb_error_node) {
		cb_tree x;

		x = cb_ref ((yyvsp[(3) - (3)]));
		if (!CB_ALPHABET_NAME_P (x)) {
			cb_error_x ((yyvsp[(3) - (3)]), _("Alphabet-name is expected '%s'"), cb_name ((yyvsp[(3) - (3)])));
		} else if (CB_ALPHABET_NAME (x)->custom_list) {
			PENDING ("CODE-SET");
		}
	}
  }
    break;

  case 338:
/* Line 1792 of yacc.c  */
#line 2547 "parser.y"
    {
	cb_warning (_("file descriptor REPORT IS"));
  }
    break;

  case 339:
/* Line 1792 of yacc.c  */
#line 2551 "parser.y"
    {
	cb_warning (_("file descriptor REPORTS ARE"));
  }
    break;

  case 341:
/* Line 1792 of yacc.c  */
#line 2562 "parser.y"
    { current_storage = CB_STORAGE_WORKING; }
    break;

  case 342:
/* Line 1792 of yacc.c  */
#line 2564 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->working_storage =
			cb_field_add (current_program->working_storage, CB_FIELD ((yyvsp[(5) - (5)])));
	}
  }
    break;

  case 343:
/* Line 1792 of yacc.c  */
#line 2573 "parser.y"
    { (yyval) = NULL; }
    break;

  case 344:
/* Line 1792 of yacc.c  */
#line 2574 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 345:
/* Line 1792 of yacc.c  */
#line 2578 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  }
    break;

  case 346:
/* Line 1792 of yacc.c  */
#line 2584 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	(yyval) = CB_TREE (description_field);
  }
    break;

  case 351:
/* Line 1792 of yacc.c  */
#line 2604 "parser.y"
    {
	cb_tree x;

	x = cb_build_field_tree ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), current_field, current_storage, current_file);
	if (x == cb_error_node) {
		YYERROR;
	} else {
		current_field = CB_FIELD (x);
	}
  }
    break;

  case 352:
/* Line 1792 of yacc.c  */
#line 2615 "parser.y"
    {
	if (!qualifier && (current_field->level == 66 || current_field->flag_item_78)) {
		cb_error (_("Item requires a data name"));
	}
	if (current_field->flag_item_78) {
		/* Reset to last non-78 item */
		current_field = cb_validate_78_item (current_field);
	}
	if (!description_field) {
		description_field = current_field;
	}
  }
    break;

  case 353:
/* Line 1792 of yacc.c  */
#line 2628 "parser.y"
    {
	cb_tree x;

	x = cb_build_field_tree ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), current_field, current_storage, current_file);
	if (x == cb_error_node) {
		YYERROR;
	} else {
		current_field = CB_FIELD (x);
	}
  }
    break;

  case 354:
/* Line 1792 of yacc.c  */
#line 2639 "parser.y"
    {
	if (!qualifier) {
		cb_error (_("Item requires a data name"));
	}
	cb_validate_88_item (current_field);
	if (!description_field) {
		description_field = current_field;
	}
	
  }
    break;

  case 358:
/* Line 1792 of yacc.c  */
#line 2666 "parser.y"
    {
	if (CB_TREE_CLASS ((yyvsp[(1) - (1)])) == CB_CLASS_NUMERIC) {
		cb_tree x = cb_build_reference ((char *)CB_LITERAL((yyvsp[(1) - (1)]))->data);
		int lev = cb_get_level (x);
		if (!lev) {
			/* do nothing expecting cb_get_level() had
			 * already given some error message. */
		} else if (lev == 88) {
			cb_unget_token (LEVEL88_NUMBER_WORD, x);
		} else {
			cb_unget_token (LEVEL_NUMBER_WORD, x);		  
		}
	} else {
		/* cause syntax error */
		cb_unget_token (LITERAL, (yyvsp[(1) - (1)]));
	}
  }
    break;

  case 359:
/* Line 1792 of yacc.c  */
#line 2687 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  }
    break;

  case 360:
/* Line 1792 of yacc.c  */
#line 2693 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  }
    break;

  case 361:
/* Line 1792 of yacc.c  */
#line 2699 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  }
    break;

  case 362:
/* Line 1792 of yacc.c  */
#line 2708 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  }
    break;

  case 364:
/* Line 1792 of yacc.c  */
#line 2717 "parser.y"
    {
	current_field->flag_is_global = 1;
	cb_error (_("CONSTANT with GLOBAL clause is not yet supported"));
  }
    break;

  case 365:
/* Line 1792 of yacc.c  */
#line 2724 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 366:
/* Line 1792 of yacc.c  */
#line 2725 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); }
    break;

  case 367:
/* Line 1792 of yacc.c  */
#line 2726 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); }
    break;

  case 368:
/* Line 1792 of yacc.c  */
#line 2731 "parser.y"
    {
	cb_tree x;
	int	level;

	level = cb_get_level ((yyvsp[(1) - (6)]));
	if (level && level != 1) {
		cb_error (_("CONSTANT item not at 01 level"));
	}
	x = cb_build_constant ((yyvsp[(2) - (6)]), (yyvsp[(6) - (6)]));
	CB_FIELD (x)->flag_item_78 = 1;
	CB_FIELD (x)->level = 1;
	cb_needs_01 = 1;
	/* Ignore return value */
	cb_validate_78_item (CB_FIELD (x));
  }
    break;

  case 369:
/* Line 1792 of yacc.c  */
#line 2750 "parser.y"
    {
	/* required to check redefines */
	(yyval) = NULL;
  }
    break;

  case 370:
/* Line 1792 of yacc.c  */
#line 2756 "parser.y"
    {
	/* required to check redefines */
	(yyval) = cb_true;
  }
    break;

  case 386:
/* Line 1792 of yacc.c  */
#line 2785 "parser.y"
    {
	if ((yyvsp[(0) - (2)]) != NULL) {
		/* hack for MF compatibility */
		if (cb_relaxed_syntax_check) {
			cb_warning_x ((yyvsp[(2) - (2)]), _("REDEFINES clause should follow entry-name"));
		} else {
			cb_error_x ((yyvsp[(2) - (2)]), _("REDEFINES clause must follow entry-name"));
		}
	}

	current_field->redefines = cb_resolve_redefines (current_field, (yyvsp[(2) - (2)]));
	if (current_field->redefines == NULL) {
		YYERROR;
	}
  }
    break;

  case 387:
/* Line 1792 of yacc.c  */
#line 2807 "parser.y"
    {
	if (current_storage != CB_STORAGE_WORKING) {
		cb_error (_("EXTERNAL not allowed here"));
	} else if (current_field->level != 1 && current_field->level != 77) {
		cb_error (_("EXTERNAL only allowed at 01/77 level"));
	} else if (!qualifier) {
		cb_error (_("EXTERNAL requires a data name"));
	} else if (current_field->flag_is_global) {
		cb_error (_("GLOBAL and EXTERNAL are mutually exclusive"));
	} else if (current_field->flag_item_based) {
		cb_error (_("BASED and EXTERNAL are mutually exclusive"));
	} else if (current_field->redefines) {
		cb_error (_("EXTERNAL and REDEFINES are mutually exclusive"));
	} else {
		current_field->flag_external = 1;
		has_external = 1;
	}
  }
    break;

  case 388:
/* Line 1792 of yacc.c  */
#line 2828 "parser.y"
    { current_field->ename = NULL; }
    break;

  case 389:
/* Line 1792 of yacc.c  */
#line 2830 "parser.y"
    {
	struct cb_field *x;

	x = CB_FIELD(cb_build_field (cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(2) - (2)]))->data))));
	current_field->ename = x->name;
 }
    break;

  case 390:
/* Line 1792 of yacc.c  */
#line 2842 "parser.y"
    {
	if (current_field->level != 1 && current_field->level != 77) {
		cb_error (_("GLOBAL only allowed at 01/77 level"));
	} else if (!qualifier) {
		cb_error (_("GLOBAL requires a data name"));
	} else if (current_field->flag_external) {
		cb_error (_("GLOBAL and EXTERNAL are mutually exclusive"));
	} else if (current_storage == CB_STORAGE_LOCAL) {
		cb_error (_("GLOBAL not allowed here"));
	} else {
		current_field->flag_is_global = 1;
	}
  }
    break;

  case 391:
/* Line 1792 of yacc.c  */
#line 2861 "parser.y"
    { current_field->pic = CB_PICTURE ((yyvsp[(1) - (1)])); }
    break;

  case 394:
/* Line 1792 of yacc.c  */
#line 2873 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; }
    break;

  case 395:
/* Line 1792 of yacc.c  */
#line 2874 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; }
    break;

  case 396:
/* Line 1792 of yacc.c  */
#line 2875 "parser.y"
    { current_field->usage = CB_USAGE_FLOAT; }
    break;

  case 397:
/* Line 1792 of yacc.c  */
#line 2876 "parser.y"
    { current_field->usage = CB_USAGE_DOUBLE; }
    break;

  case 398:
/* Line 1792 of yacc.c  */
#line 2877 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; }
    break;

  case 399:
/* Line 1792 of yacc.c  */
#line 2878 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; }
    break;

  case 400:
/* Line 1792 of yacc.c  */
#line 2879 "parser.y"
    { current_field->usage = CB_USAGE_COMP_5; }
    break;

  case 401:
/* Line 1792 of yacc.c  */
#line 2880 "parser.y"
    { current_field->usage = CB_USAGE_COMP_X; }
    break;

  case 402:
/* Line 1792 of yacc.c  */
#line 2881 "parser.y"
    { current_field->usage = CB_USAGE_DISPLAY; }
    break;

  case 403:
/* Line 1792 of yacc.c  */
#line 2882 "parser.y"
    { current_field->usage = CB_USAGE_INDEX; }
    break;

  case 404:
/* Line 1792 of yacc.c  */
#line 2883 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; }
    break;

  case 405:
/* Line 1792 of yacc.c  */
#line 2885 "parser.y"
    {
	current_field->usage = CB_USAGE_POINTER;
	current_field->flag_is_pointer = 1;
  }
    break;

  case 406:
/* Line 1792 of yacc.c  */
#line 2890 "parser.y"
    {
	current_field->usage = CB_USAGE_PROGRAM_POINTER;
	current_field->flag_is_pointer = 1;
  }
    break;

  case 407:
/* Line 1792 of yacc.c  */
#line 2894 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; }
    break;

  case 408:
/* Line 1792 of yacc.c  */
#line 2895 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; }
    break;

  case 409:
/* Line 1792 of yacc.c  */
#line 2896 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; }
    break;

  case 410:
/* Line 1792 of yacc.c  */
#line 2897 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; }
    break;

  case 411:
/* Line 1792 of yacc.c  */
#line 2898 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; }
    break;

  case 412:
/* Line 1792 of yacc.c  */
#line 2899 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; }
    break;

  case 413:
/* Line 1792 of yacc.c  */
#line 2900 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; }
    break;

  case 414:
/* Line 1792 of yacc.c  */
#line 2901 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_CHAR; }
    break;

  case 415:
/* Line 1792 of yacc.c  */
#line 2902 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; }
    break;

  case 416:
/* Line 1792 of yacc.c  */
#line 2903 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; }
    break;

  case 417:
/* Line 1792 of yacc.c  */
#line 2904 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; }
    break;

  case 418:
/* Line 1792 of yacc.c  */
#line 2905 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; }
    break;

  case 419:
/* Line 1792 of yacc.c  */
#line 2906 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; }
    break;

  case 420:
/* Line 1792 of yacc.c  */
#line 2907 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; }
    break;

  case 421:
/* Line 1792 of yacc.c  */
#line 2908 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; }
    break;

  case 422:
/* Line 1792 of yacc.c  */
#line 2909 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; }
    break;

  case 423:
/* Line 1792 of yacc.c  */
#line 2910 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; }
    break;

  case 424:
/* Line 1792 of yacc.c  */
#line 2911 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; }
    break;

  case 425:
/* Line 1792 of yacc.c  */
#line 2913 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  }
    break;

  case 426:
/* Line 1792 of yacc.c  */
#line 2921 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_UNSIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_UNSIGNED_LONG;
	}
  }
    break;

  case 427:
/* Line 1792 of yacc.c  */
#line 2929 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  }
    break;

  case 428:
/* Line 1792 of yacc.c  */
#line 2936 "parser.y"
    { PENDING ("USAGE NATIONAL");}
    break;

  case 429:
/* Line 1792 of yacc.c  */
#line 2944 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 1;
  }
    break;

  case 430:
/* Line 1792 of yacc.c  */
#line 2949 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 0;
  }
    break;

  case 434:
/* Line 1792 of yacc.c  */
#line 2966 "parser.y"
    {
	if (current_field->occurs_depending && !((yyvsp[(3) - (6)]))) {
		cb_verify (cb_odo_without_to, "ODO without TO clause");
	}
	current_field->occurs_min = (yyvsp[(3) - (6)]) ? cb_get_int ((yyvsp[(2) - (6)])) : 1;
	current_field->occurs_max = (yyvsp[(3) - (6)]) ? cb_get_int ((yyvsp[(3) - (6)])) : cb_get_int ((yyvsp[(2) - (6)]));
	current_field->indexes++;
	if (current_field->indexes > COB_MAX_SUBSCRIPTS) {
		cb_error (_("Maximum OCCURS depth exceeded"));
	}
	current_field->flag_occurs = 1;
  }
    break;

  case 435:
/* Line 1792 of yacc.c  */
#line 2981 "parser.y"
    { (yyval) = NULL; }
    break;

  case 436:
/* Line 1792 of yacc.c  */
#line 2982 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 438:
/* Line 1792 of yacc.c  */
#line 2987 "parser.y"
    {
	current_field->occurs_depending = (yyvsp[(3) - (3)]);
  }
    break;

  case 441:
/* Line 1792 of yacc.c  */
#line 2996 "parser.y"
    {
	if ((yyvsp[(1) - (1)])) {
		cb_tree		l;
		struct cb_key	*keys;
		int		i;
		int		nkeys;

		l = (yyvsp[(1) - (1)]);
		nkeys = cb_list_length ((yyvsp[(1) - (1)]));
		keys = cobc_malloc (sizeof (struct cb_key) * nkeys);

		for (i = 0; i < nkeys; i++) {
			keys[i].dir = CB_PURPOSE_INT (l);
			keys[i].key = CB_VALUE (l);
			l = CB_CHAIN (l);
		}
		current_field->keys = keys;
		current_field->nkeys = nkeys;
	}
  }
    break;

  case 442:
/* Line 1792 of yacc.c  */
#line 3020 "parser.y"
    {
	cb_tree l;

	for (l = (yyvsp[(4) - (4)]); l; l = CB_CHAIN (l)) {
		CB_PURPOSE (l) = (yyvsp[(1) - (4)]);
		if (qualifier && !CB_REFERENCE(CB_VALUE(l))->chain &&
		    strcasecmp (CB_NAME(CB_VALUE(l)), CB_NAME(qualifier))) {
			CB_REFERENCE(CB_VALUE(l))->chain = qualifier;
		}
	}
	(yyval) = (yyvsp[(4) - (4)]);
  }
    break;

  case 443:
/* Line 1792 of yacc.c  */
#line 3035 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 444:
/* Line 1792 of yacc.c  */
#line 3036 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 445:
/* Line 1792 of yacc.c  */
#line 3040 "parser.y"
    { (yyval) = cb_int (COB_ASCENDING); }
    break;

  case 446:
/* Line 1792 of yacc.c  */
#line 3041 "parser.y"
    { (yyval) = cb_int (COB_DESCENDING); }
    break;

  case 449:
/* Line 1792 of yacc.c  */
#line 3048 "parser.y"
    {
	current_field->index_list = (yyvsp[(3) - (3)]);
  }
    break;

  case 450:
/* Line 1792 of yacc.c  */
#line 3054 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 451:
/* Line 1792 of yacc.c  */
#line 3056 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 452:
/* Line 1792 of yacc.c  */
#line 3061 "parser.y"
    {
	(yyval) = cb_build_index ((yyvsp[(1) - (1)]), cb_int1, 1, current_field);
  }
    break;

  case 453:
/* Line 1792 of yacc.c  */
#line 3070 "parser.y"
    { current_field->flag_justified = 1; }
    break;

  case 454:
/* Line 1792 of yacc.c  */
#line 3077 "parser.y"
    { current_field->flag_synchronized = 1; }
    break;

  case 458:
/* Line 1792 of yacc.c  */
#line 3089 "parser.y"
    { current_field->flag_blank_zero = 1; }
    break;

  case 459:
/* Line 1792 of yacc.c  */
#line 3097 "parser.y"
    {
	if (current_storage != CB_STORAGE_WORKING &&
	    current_storage != CB_STORAGE_LINKAGE &&
	    current_storage != CB_STORAGE_LOCAL) {
		cb_error (_("BASED not allowed here"));
	} else if (current_field->level != 1 && current_field->level != 77) {
		cb_error (_("BASED only allowed at 01/77 level"));
	} else if (!qualifier) {
		cb_error (_("BASED requires a data name"));
	} else if (current_field->flag_external) {
		cb_error (_("BASED and EXTERNAL are mutually exclusive"));
	} else if (current_field->redefines) {
		cb_error (_("BASED and REDEFINES are mutually exclusive"));
	} else if (current_field->flag_any_length) {
		cb_error (_("BASED and ANY LENGTH are mutually exclusive"));
	} else {
		current_field->flag_item_based = 1;
	}
  }
    break;

  case 460:
/* Line 1792 of yacc.c  */
#line 3121 "parser.y"
    { current_field->values = cb_list_init ((yyvsp[(3) - (3)])); }
    break;

  case 461:
/* Line 1792 of yacc.c  */
#line 3125 "parser.y"
    { current_field->values = (yyvsp[(3) - (3)]); }
    break;

  case 463:
/* Line 1792 of yacc.c  */
#line 3130 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 464:
/* Line 1792 of yacc.c  */
#line 3131 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 465:
/* Line 1792 of yacc.c  */
#line 3135 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 466:
/* Line 1792 of yacc.c  */
#line 3136 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 468:
/* Line 1792 of yacc.c  */
#line 3141 "parser.y"
    {
	if (current_field->level != 88) {
		cb_error (_("FALSE clause only allowed for 88 level"));
	}
	current_field->false_88 = cb_list_init ((yyvsp[(3) - (3)]));
  }
    break;

  case 469:
/* Line 1792 of yacc.c  */
#line 3154 "parser.y"
    {
	if (cb_ref ((yyvsp[(2) - (2)])) != cb_error_node) {
		if (CB_FIELD (cb_ref ((yyvsp[(2) - (2)])))->level == 01 ||
		    CB_FIELD (cb_ref ((yyvsp[(2) - (2)])))->level > 50) {
			cb_error (_("RENAMES may not reference a level 01 or > 50"));
		} else {
			current_field->redefines = CB_FIELD (cb_ref ((yyvsp[(2) - (2)])));
			current_field->pic = current_field->redefines->pic;
		}
	}
  }
    break;

  case 470:
/* Line 1792 of yacc.c  */
#line 3166 "parser.y"
    {
	if (cb_ref ((yyvsp[(2) - (4)])) != cb_error_node && cb_ref ((yyvsp[(4) - (4)])) != cb_error_node) {
		if (CB_FIELD (cb_ref ((yyvsp[(2) - (4)])))->level == 01 ||
		    CB_FIELD (cb_ref ((yyvsp[(2) - (4)])))->level > 50) {
			cb_error (_("RENAMES may not reference a level 01 or > 50"));
		} else if (CB_FIELD (cb_ref ((yyvsp[(4) - (4)])))->level == 01 ||
		    CB_FIELD (cb_ref ((yyvsp[(4) - (4)])))->level > 50) {
			cb_error (_("RENAMES may not reference a level 01 or > 50"));
		} else {
			current_field->redefines = CB_FIELD (cb_ref ((yyvsp[(2) - (4)])));
			current_field->rename_thru = CB_FIELD (cb_ref ((yyvsp[(4) - (4)])));
		}
	}
  }
    break;

  case 471:
/* Line 1792 of yacc.c  */
#line 3186 "parser.y"
    {
	if (current_field->flag_item_based) {
		cb_error (_("BASED and ANY LENGTH are mutually exclusive"));
	} else {
		current_field->flag_any_length = 1;
	}
  }
    break;

  case 473:
/* Line 1792 of yacc.c  */
#line 3201 "parser.y"
    {
	current_storage = CB_STORAGE_LOCAL;
	if (current_program->nested_level) {
		cb_error (_("LOCAL-STORAGE not allowed in nested programs"));
	}
  }
    break;

  case 474:
/* Line 1792 of yacc.c  */
#line 3208 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->local_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  }
    break;

  case 476:
/* Line 1792 of yacc.c  */
#line 3221 "parser.y"
    { current_storage = CB_STORAGE_LINKAGE; }
    break;

  case 477:
/* Line 1792 of yacc.c  */
#line 3223 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->linkage_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  }
    break;

  case 479:
/* Line 1792 of yacc.c  */
#line 3236 "parser.y"
    {
	cb_error (_("REPORT SECTION not supported"));
	current_storage = CB_STORAGE_REPORT;
  }
    break;

  case 486:
/* Line 1792 of yacc.c  */
#line 3269 "parser.y"
    {
	cb_warning (_("Report description using defaults"));
  }
    break;

  case 488:
/* Line 1792 of yacc.c  */
#line 3277 "parser.y"
    {
	cb_error (_("GLOBAL is not allowed with RD"));
  }
    break;

  case 497:
/* Line 1792 of yacc.c  */
#line 3300 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 498:
/* Line 1792 of yacc.c  */
#line 3301 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 520:
/* Line 1792 of yacc.c  */
#line 3357 "parser.y"
    { cb_warning (_("looking for Report line TYPE")); }
    break;

  case 571:
/* Line 1792 of yacc.c  */
#line 3462 "parser.y"
    { current_storage = CB_STORAGE_SCREEN; }
    break;

  case 572:
/* Line 1792 of yacc.c  */
#line 3463 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  }
    break;

  case 573:
/* Line 1792 of yacc.c  */
#line 3469 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	current_program->screen_storage = description_field;
	current_program->flag_screen = 1;
  }
    break;

  case 579:
/* Line 1792 of yacc.c  */
#line 3493 "parser.y"
    {
	cb_tree x;

	x = cb_build_field_tree ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), current_field, current_storage, current_file);
	if (x == cb_error_node) {
		YYERROR;
	}

	current_field = CB_FIELD (x);
	if (current_field->parent) {
		current_field->screen_flag |= current_field->parent->screen_flag;
		current_field->screen_foreg = current_field->parent->screen_foreg;
		current_field->screen_backg = current_field->parent->screen_backg;
	}
  }
    break;

  case 580:
/* Line 1792 of yacc.c  */
#line 3509 "parser.y"
    {
	if (!qualifier && (current_field->level == 88 ||
	    current_field->level == 77 || current_field->level == 66 ||
	    current_field->flag_item_78)) {
		cb_error (_("Item requires a data name"));
	}
	if (current_field->level == 88) {
		cb_validate_88_item (current_field);
	}
	if (current_field->flag_item_78) {
		/* Reset to last non-78 item */
		current_field = cb_validate_78_item (current_field);
	}
	if (!description_field) {
		description_field = current_field;
	}
  }
    break;

  case 583:
/* Line 1792 of yacc.c  */
#line 3533 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_LINE; }
    break;

  case 584:
/* Line 1792 of yacc.c  */
#line 3534 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_SCREEN; }
    break;

  case 585:
/* Line 1792 of yacc.c  */
#line 3535 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BELL; }
    break;

  case 586:
/* Line 1792 of yacc.c  */
#line 3536 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLINK; }
    break;

  case 587:
/* Line 1792 of yacc.c  */
#line 3537 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOL; }
    break;

  case 588:
/* Line 1792 of yacc.c  */
#line 3538 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOS; }
    break;

  case 589:
/* Line 1792 of yacc.c  */
#line 3539 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_HIGHLIGHT; }
    break;

  case 590:
/* Line 1792 of yacc.c  */
#line 3540 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_LOWLIGHT; }
    break;

  case 591:
/* Line 1792 of yacc.c  */
#line 3541 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REVERSE; }
    break;

  case 592:
/* Line 1792 of yacc.c  */
#line 3542 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_UNDERLINE; }
    break;

  case 593:
/* Line 1792 of yacc.c  */
#line 3543 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_OVERLINE; }
    break;

  case 594:
/* Line 1792 of yacc.c  */
#line 3544 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_AUTO; }
    break;

  case 595:
/* Line 1792 of yacc.c  */
#line 3545 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_SECURE; }
    break;

  case 596:
/* Line 1792 of yacc.c  */
#line 3546 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REQUIRED; }
    break;

  case 597:
/* Line 1792 of yacc.c  */
#line 3547 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_FULL; }
    break;

  case 598:
/* Line 1792 of yacc.c  */
#line 3548 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_PROMPT; }
    break;

  case 599:
/* Line 1792 of yacc.c  */
#line 3550 "parser.y"
    {
	current_field->screen_line = (yyvsp[(5) - (5)]);
  }
    break;

  case 600:
/* Line 1792 of yacc.c  */
#line 3554 "parser.y"
    {
	current_field->screen_column = (yyvsp[(5) - (5)]);
  }
    break;

  case 601:
/* Line 1792 of yacc.c  */
#line 3558 "parser.y"
    {
	current_field->screen_foreg = (yyvsp[(3) - (3)]);
  }
    break;

  case 602:
/* Line 1792 of yacc.c  */
#line 3562 "parser.y"
    {
	current_field->screen_backg = (yyvsp[(3) - (3)]);
  }
    break;

  case 610:
/* Line 1792 of yacc.c  */
#line 3573 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  }
    break;

  case 611:
/* Line 1792 of yacc.c  */
#line 3580 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
  }
    break;

  case 612:
/* Line 1792 of yacc.c  */
#line 3584 "parser.y"
    {
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  }
    break;

  case 613:
/* Line 1792 of yacc.c  */
#line 3593 "parser.y"
    {
	/* Nothing */
  }
    break;

  case 614:
/* Line 1792 of yacc.c  */
#line 3597 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  }
    break;

  case 615:
/* Line 1792 of yacc.c  */
#line 3601 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  }
    break;

  case 616:
/* Line 1792 of yacc.c  */
#line 3605 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  }
    break;

  case 617:
/* Line 1792 of yacc.c  */
#line 3609 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  }
    break;

  case 618:
/* Line 1792 of yacc.c  */
#line 3616 "parser.y"
    {
	/* Nothing */
  }
    break;

  case 619:
/* Line 1792 of yacc.c  */
#line 3620 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  }
    break;

  case 620:
/* Line 1792 of yacc.c  */
#line 3624 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  }
    break;

  case 621:
/* Line 1792 of yacc.c  */
#line 3628 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  }
    break;

  case 622:
/* Line 1792 of yacc.c  */
#line 3632 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  }
    break;

  case 623:
/* Line 1792 of yacc.c  */
#line 3640 "parser.y"
    {
	current_field->occurs_max = cb_get_int ((yyvsp[(2) - (3)]));
	current_field->occurs_min = current_field->occurs_max;
	current_field->indexes++;
	current_field->flag_occurs = 1;
  }
    break;

  case 625:
/* Line 1792 of yacc.c  */
#line 3654 "parser.y"
    {
	current_section = NULL;
	current_paragraph = NULL;
	cb_define_system_name ("CONSOLE");
	cb_define_system_name ("SYSIN");
	cb_define_system_name ("SYSOUT");
	cb_define_system_name ("SYSERR");
	cb_set_in_procedure ();
  }
    break;

  case 626:
/* Line 1792 of yacc.c  */
#line 3664 "parser.y"
    {
	if (current_program->flag_main && !current_program->flag_chained && (yyvsp[(3) - (7)])) {
		cb_error (_("Executable program requested but PROCEDURE/ENTRY has USING clause"));
	}
	emit_entry (current_program->program_id, 0, (yyvsp[(3) - (7)])); /* main entry point */
	if (current_program->source_name) {
		emit_entry (current_program->source_name, 1, (yyvsp[(3) - (7)]));
	}
  }
    break;

  case 627:
/* Line 1792 of yacc.c  */
#line 3674 "parser.y"
    {
	if (current_paragraph) {
		if (current_paragraph->exit_label) {
			emit_statement (current_paragraph->exit_label);
		}
		emit_statement (cb_build_perform_exit (current_paragraph));
	}
	if (current_section) {
		if (current_section->exit_label) {
			emit_statement (current_section->exit_label);
		}
		emit_statement (cb_build_perform_exit (current_section));
	}
  }
    break;

  case 628:
/* Line 1792 of yacc.c  */
#line 3691 "parser.y"
    { (yyval) = NULL; }
    break;

  case 629:
/* Line 1792 of yacc.c  */
#line 3693 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  }
    break;

  case 630:
/* Line 1792 of yacc.c  */
#line 3697 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 631:
/* Line 1792 of yacc.c  */
#line 3699 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	current_program->flag_chained = 1;
  }
    break;

  case 632:
/* Line 1792 of yacc.c  */
#line 3703 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 633:
/* Line 1792 of yacc.c  */
#line 3707 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 634:
/* Line 1792 of yacc.c  */
#line 3709 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 635:
/* Line 1792 of yacc.c  */
#line 3714 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), cb_build_identifier ((yyvsp[(4) - (4)])));
	CB_SIZES ((yyval)) = size_mode;
  }
    break;

  case 637:
/* Line 1792 of yacc.c  */
#line 3723 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  }
    break;

  case 638:
/* Line 1792 of yacc.c  */
#line 3727 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  }
    break;

  case 640:
/* Line 1792 of yacc.c  */
#line 3739 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_AUTO;
	}
  }
    break;

  case 641:
/* Line 1792 of yacc.c  */
#line 3747 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_4;
	}
  }
    break;

  case 642:
/* Line 1792 of yacc.c  */
#line 3755 "parser.y"
    {
	unsigned char *s = CB_LITERAL ((yyvsp[(4) - (4)]))->data;

	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else if (CB_LITERAL ((yyvsp[(4) - (4)]))->size != 1) {
		cb_error_x ((yyvsp[(4) - (4)]), _("Invalid value for SIZE"));
	} else {
		size_mode = CB_SIZE_UNSIGNED;
		switch (*s) {
		case '1':
			size_mode |= CB_SIZE_1;
			break;
		case '2':
			size_mode |= CB_SIZE_2;
			break;
		case '4':
			size_mode |= CB_SIZE_4;
			break;
		case '8':
			size_mode |= CB_SIZE_8;
			break;
		default:
			cb_error_x ((yyvsp[(4) - (4)]), _("Invalid value for SIZE"));
			break;
		}
	}
  }
    break;

  case 643:
/* Line 1792 of yacc.c  */
#line 3784 "parser.y"
    {
	unsigned char *s = CB_LITERAL ((yyvsp[(3) - (3)]))->data;

	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else if (CB_LITERAL ((yyvsp[(3) - (3)]))->size != 1) {
		cb_error_x ((yyvsp[(3) - (3)]), _("Invalid value for SIZE"));
	} else {
		size_mode = 0;
		switch (*s) {
		case '1':
			size_mode = CB_SIZE_1;
			break;
		case '2':
			size_mode = CB_SIZE_2;
			break;
		case '4':
			size_mode = CB_SIZE_4;
			break;
		case '8':
			size_mode = CB_SIZE_8;
			break;
		default:
			cb_error_x ((yyvsp[(3) - (3)]), _("Invalid value for SIZE"));
			break;
		}
	}
  }
    break;

  case 645:
/* Line 1792 of yacc.c  */
#line 3817 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OPTIONAL only allowed for BY REFERENCE items"));
	}
  }
    break;

  case 646:
/* Line 1792 of yacc.c  */
#line 3826 "parser.y"
    {
	if (current_program->prog_type == CB_FUNCTION_TYPE) {
		cb_error (_("RETURNING clause is required for a FUNCTION"));
	}
  }
    break;

  case 647:
/* Line 1792 of yacc.c  */
#line 3832 "parser.y"
    {
	if (cb_ref ((yyvsp[(2) - (2)])) != cb_error_node) {
		current_program->returning = (yyvsp[(2) - (2)]);
		if (cb_field ((yyvsp[(2) - (2)]))->storage != CB_STORAGE_LINKAGE) {
			cb_error (_("RETURNING item is not defined in LINKAGE SECTION"));
		}
	}
  }
    break;

  case 649:
/* Line 1792 of yacc.c  */
#line 3843 "parser.y"
    { in_declaratives = 1; }
    break;

  case 650:
/* Line 1792 of yacc.c  */
#line 3846 "parser.y"
    {
	in_declaratives = 0;
	if (current_paragraph) {
		if (current_paragraph->exit_label) {
			emit_statement (current_paragraph->exit_label);
		}
		emit_statement (cb_build_perform_exit (current_paragraph));
		current_paragraph = NULL;
	}
	if (current_section) {
		if (current_section->exit_label) {
			emit_statement (current_section->exit_label);
		}
		emit_statement (cb_build_perform_exit (current_section));
		current_section = NULL;
	}
  }
    break;

  case 656:
/* Line 1792 of yacc.c  */
#line 3879 "parser.y"
    {
	if (next_label_list) {
		cb_tree label;
		char name[16];

		sprintf (name, "L$%d", next_label_id);
		label = cb_build_reference (name);
		emit_statement (cb_build_label (label, current_section));
		current_program->label_list =
			cb_list_append (current_program->label_list, next_label_list);
		next_label_list = NULL;
		next_label_id++;
	}
	/* check_unreached = 0; */
  }
    break;

  case 657:
/* Line 1792 of yacc.c  */
#line 3895 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 658:
/* Line 1792 of yacc.c  */
#line 3907 "parser.y"
    {
	non_const_word = 0;
	check_unreached = 0;
	if ((yyvsp[(1) - (4)]) == cb_error_node) {
		YYERROR;
	}

	/* Exit the last section */
	if (current_paragraph) {
		if (current_paragraph->exit_label) {
			emit_statement (current_paragraph->exit_label);
		}
		emit_statement (cb_build_perform_exit (current_paragraph));
	}
	if (current_section) {
		if (current_section->exit_label) {
			emit_statement (current_section->exit_label);
		}
		emit_statement (cb_build_perform_exit (current_section));
	}

	/* Begin a new section */
	current_section = CB_LABEL (cb_build_label ((yyvsp[(1) - (4)]), NULL));
	current_section->is_section = 1;
	current_paragraph = NULL;
	emit_statement (CB_TREE (current_section));
  }
    break;

  case 659:
/* Line 1792 of yacc.c  */
#line 3938 "parser.y"
    {
	cb_tree label;

	non_const_word = 0;
	check_unreached = 0;
	(yyval) = cb_build_section_name ((yyvsp[(1) - (2)]), 1);
	/* if ($1 == cb_error_node) */
	if ((yyval) == cb_error_node) {
		YYERROR;
	}

	/* Exit the last paragraph */
	if (current_paragraph) {
		if (current_paragraph->exit_label) {
			emit_statement (current_paragraph->exit_label);
		}
		emit_statement (cb_build_perform_exit (current_paragraph));
	}

	/* Begin a new paragraph */
	if (!current_section) {
		label = cb_build_reference ("MAIN SECTION");
		current_section = CB_LABEL (cb_build_label (label, NULL));
		current_section->is_section = 1;
		emit_statement (CB_TREE (current_section));
	}
	current_paragraph = CB_LABEL (cb_build_label ((yyval), current_section));
	if (current_section) {
		current_section->children =
			cb_cons (CB_TREE (current_paragraph), current_section->children);
	}
	emit_statement (CB_TREE (current_paragraph));
  }
    break;

  case 660:
/* Line 1792 of yacc.c  */
#line 3975 "parser.y"
    {
	non_const_word = 0;
	check_unreached = 0;
	if ((yyvsp[(1) - (1)]) != cb_error_node) {
		cb_error_x ((yyvsp[(1) - (1)]), _("Unknown statement '%s'"), CB_NAME ((yyvsp[(1) - (1)])));
	}
	YYERROR;
  }
    break;

  case 661:
/* Line 1792 of yacc.c  */
#line 3986 "parser.y"
    { (yyval) = cb_build_section_name ((yyvsp[(1) - (1)]), 0); }
    break;

  case 663:
/* Line 1792 of yacc.c  */
#line 3990 "parser.y"
    { /* ignore */ }
    break;

  case 664:
/* Line 1792 of yacc.c  */
#line 3999 "parser.y"
    {
	(yyval) = current_program->exec_list;
	current_program->exec_list = NULL;
  }
    break;

  case 665:
/* Line 1792 of yacc.c  */
#line 4003 "parser.y"
    {
	(yyval) = CB_TREE (current_statement);
	current_statement = NULL;
  }
    break;

  case 666:
/* Line 1792 of yacc.c  */
#line 4008 "parser.y"
    {
	(yyval) = cb_list_reverse (current_program->exec_list);
	current_program->exec_list = (yyvsp[(1) - (3)]);
	current_statement = CB_STATEMENT ((yyvsp[(2) - (3)]));
  }
    break;

  case 667:
/* Line 1792 of yacc.c  */
#line 4016 "parser.y"
    {
	cb_tree label;

	if (!current_section) {
		label = cb_build_reference ("MAIN SECTION");
		current_section = CB_LABEL (cb_build_label (label, NULL));
		current_section->is_section = 1;
		emit_statement (CB_TREE (current_section));
	}
	if (!current_paragraph) {
		label = cb_build_reference ("MAIN PARAGRAPH");
		current_paragraph = CB_LABEL (cb_build_label (label, NULL));
		emit_statement (CB_TREE (current_paragraph));
		current_section->children =
			cb_cons (CB_TREE (current_paragraph), current_section->children);
	}
  }
    break;

  case 718:
/* Line 1792 of yacc.c  */
#line 4088 "parser.y"
    {
	if (cb_verify (cb_next_sentence_phrase, "NEXT SENTENCE")) {
		cb_tree label;
		char	name[16];

		BEGIN_STATEMENT ("NEXT SENTENCE", 0);
		sprintf (name, "L$%d", next_label_id);
		label = cb_build_reference (name);
		next_label_list = cb_list_add (next_label_list, label);
		emit_statement (cb_build_goto (label, NULL));
	}
	check_unreached = 0;
  }
    break;

  case 719:
/* Line 1792 of yacc.c  */
#line 4110 "parser.y"
    {
	BEGIN_STATEMENT ("ACCEPT", TERM_ACCEPT);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  }
    break;

  case 721:
/* Line 1792 of yacc.c  */
#line 4123 "parser.y"
    {
	cb_emit_accept ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  }
    break;

  case 722:
/* Line 1792 of yacc.c  */
#line 4127 "parser.y"
    {
	PENDING ("ACCEPT .. FROM ESCAPE KEY");
  }
    break;

  case 723:
/* Line 1792 of yacc.c  */
#line 4131 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 0);
  }
    break;

  case 724:
/* Line 1792 of yacc.c  */
#line 4135 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 1);
  }
    break;

  case 725:
/* Line 1792 of yacc.c  */
#line 4139 "parser.y"
    {
	cb_emit_accept_date ((yyvsp[(1) - (3)]));
  }
    break;

  case 726:
/* Line 1792 of yacc.c  */
#line 4143 "parser.y"
    {
	cb_emit_accept_date_yyyymmdd ((yyvsp[(1) - (4)]));
  }
    break;

  case 727:
/* Line 1792 of yacc.c  */
#line 4147 "parser.y"
    {
	cb_emit_accept_day ((yyvsp[(1) - (3)]));
  }
    break;

  case 728:
/* Line 1792 of yacc.c  */
#line 4151 "parser.y"
    {
	cb_emit_accept_day_yyyyddd ((yyvsp[(1) - (4)]));
  }
    break;

  case 729:
/* Line 1792 of yacc.c  */
#line 4155 "parser.y"
    {
	cb_emit_accept_day_of_week ((yyvsp[(1) - (3)]));
  }
    break;

  case 730:
/* Line 1792 of yacc.c  */
#line 4159 "parser.y"
    {
	cb_emit_accept_time ((yyvsp[(1) - (3)]));
  }
    break;

  case 731:
/* Line 1792 of yacc.c  */
#line 4163 "parser.y"
    {
	cb_emit_accept_command_line ((yyvsp[(1) - (3)]));
  }
    break;

  case 732:
/* Line 1792 of yacc.c  */
#line 4167 "parser.y"
    {
	cb_emit_accept_environment ((yyvsp[(1) - (4)]));
  }
    break;

  case 733:
/* Line 1792 of yacc.c  */
#line 4171 "parser.y"
    { 
	cb_emit_get_environment ((yyvsp[(4) - (5)]), (yyvsp[(1) - (5)]));
  }
    break;

  case 734:
/* Line 1792 of yacc.c  */
#line 4175 "parser.y"
    {
	cb_emit_accept_arg_number ((yyvsp[(1) - (3)]));
  }
    break;

  case 735:
/* Line 1792 of yacc.c  */
#line 4179 "parser.y"
    {
	cb_emit_accept_arg_value ((yyvsp[(1) - (4)]));
  }
    break;

  case 736:
/* Line 1792 of yacc.c  */
#line 4183 "parser.y"
    {
	cb_emit_accept_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 737:
/* Line 1792 of yacc.c  */
#line 4187 "parser.y"
    {
	cb_emit_accept_name ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 738:
/* Line 1792 of yacc.c  */
#line 4193 "parser.y"
    { (yyval) = NULL; }
    break;

  case 739:
/* Line 1792 of yacc.c  */
#line 4194 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 740:
/* Line 1792 of yacc.c  */
#line 4195 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 741:
/* Line 1792 of yacc.c  */
#line 4196 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), NULL); }
    break;

  case 742:
/* Line 1792 of yacc.c  */
#line 4197 "parser.y"
    { (yyval) = cb_build_pair (NULL, (yyvsp[(2) - (2)])); }
    break;

  case 743:
/* Line 1792 of yacc.c  */
#line 4198 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 744:
/* Line 1792 of yacc.c  */
#line 4202 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 745:
/* Line 1792 of yacc.c  */
#line 4206 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 746:
/* Line 1792 of yacc.c  */
#line 4207 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 751:
/* Line 1792 of yacc.c  */
#line 4220 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; }
    break;

  case 752:
/* Line 1792 of yacc.c  */
#line 4221 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; }
    break;

  case 753:
/* Line 1792 of yacc.c  */
#line 4222 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; }
    break;

  case 754:
/* Line 1792 of yacc.c  */
#line 4223 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; }
    break;

  case 755:
/* Line 1792 of yacc.c  */
#line 4224 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; }
    break;

  case 756:
/* Line 1792 of yacc.c  */
#line 4225 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; }
    break;

  case 757:
/* Line 1792 of yacc.c  */
#line 4226 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; }
    break;

  case 758:
/* Line 1792 of yacc.c  */
#line 4228 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  }
    break;

  case 759:
/* Line 1792 of yacc.c  */
#line 4232 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  }
    break;

  case 760:
/* Line 1792 of yacc.c  */
#line 4236 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  }
    break;

  case 761:
/* Line 1792 of yacc.c  */
#line 4240 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  }
    break;

  case 762:
/* Line 1792 of yacc.c  */
#line 4244 "parser.y"
    { dispattrs |= COB_SCREEN_AUTO; }
    break;

  case 763:
/* Line 1792 of yacc.c  */
#line 4245 "parser.y"
    { dispattrs |= COB_SCREEN_FULL; }
    break;

  case 764:
/* Line 1792 of yacc.c  */
#line 4246 "parser.y"
    { dispattrs |= COB_SCREEN_REQUIRED; }
    break;

  case 765:
/* Line 1792 of yacc.c  */
#line 4247 "parser.y"
    { dispattrs |= COB_SCREEN_SECURE; }
    break;

  case 766:
/* Line 1792 of yacc.c  */
#line 4248 "parser.y"
    { dispattrs |= COB_SCREEN_UPDATE; }
    break;

  case 767:
/* Line 1792 of yacc.c  */
#line 4249 "parser.y"
    { dispattrs |= COB_SCREEN_PROMPT; }
    break;

  case 768:
/* Line 1792 of yacc.c  */
#line 4253 "parser.y"
    { terminator_warning (TERM_ACCEPT); }
    break;

  case 769:
/* Line 1792 of yacc.c  */
#line 4254 "parser.y"
    { terminator_clear (TERM_ACCEPT); }
    break;

  case 770:
/* Line 1792 of yacc.c  */
#line 4263 "parser.y"
    { BEGIN_STATEMENT ("ADD", TERM_ADD); }
    break;

  case 772:
/* Line 1792 of yacc.c  */
#line 4270 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '+', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  }
    break;

  case 773:
/* Line 1792 of yacc.c  */
#line 4274 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(4) - (5)]), 0, cb_build_binary_list ((yyvsp[(1) - (5)]), '+'));
  }
    break;

  case 774:
/* Line 1792 of yacc.c  */
#line 4278 "parser.y"
    {
	cb_emit_corresponding (cb_build_add, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  }
    break;

  case 776:
/* Line 1792 of yacc.c  */
#line 4284 "parser.y"
    { cb_list_add ((yyvsp[(0) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 777:
/* Line 1792 of yacc.c  */
#line 4288 "parser.y"
    { terminator_warning (TERM_ADD); }
    break;

  case 778:
/* Line 1792 of yacc.c  */
#line 4289 "parser.y"
    { terminator_clear (TERM_ADD); }
    break;

  case 779:
/* Line 1792 of yacc.c  */
#line 4298 "parser.y"
    { BEGIN_STATEMENT ("ALLOCATE", 0); }
    break;

  case 781:
/* Line 1792 of yacc.c  */
#line 4304 "parser.y"
    {
	cb_emit_allocate ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), NULL, (yyvsp[(2) - (3)]));
  }
    break;

  case 782:
/* Line 1792 of yacc.c  */
#line 4308 "parser.y"
    {
	cb_emit_allocate (NULL, (yyvsp[(5) - (5)]), (yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]));
  }
    break;

  case 783:
/* Line 1792 of yacc.c  */
#line 4314 "parser.y"
    { (yyval) = NULL; }
    break;

  case 784:
/* Line 1792 of yacc.c  */
#line 4315 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 785:
/* Line 1792 of yacc.c  */
#line 4325 "parser.y"
    {
	cb_error (_("ALTER statement is obsolete and unsupported"));
  }
    break;

  case 790:
/* Line 1792 of yacc.c  */
#line 4343 "parser.y"
    { BEGIN_STATEMENT ("CALL", TERM_CALL); }
    break;

  case 791:
/* Line 1792 of yacc.c  */
#line 4347 "parser.y"
    {
	cb_emit_call ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  }
    break;

  case 792:
/* Line 1792 of yacc.c  */
#line 4353 "parser.y"
    { (yyval) = NULL; }
    break;

  case 793:
/* Line 1792 of yacc.c  */
#line 4355 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  }
    break;

  case 794:
/* Line 1792 of yacc.c  */
#line 4359 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 795:
/* Line 1792 of yacc.c  */
#line 4363 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 796:
/* Line 1792 of yacc.c  */
#line 4365 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 797:
/* Line 1792 of yacc.c  */
#line 4370 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OMITTED only allowed with BY REFERENCE"));
	}
	(yyval) = cb_build_pair (cb_int (call_mode), cb_null);
  }
    break;

  case 798:
/* Line 1792 of yacc.c  */
#line 4377 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), (yyvsp[(3) - (3)]));
	CB_SIZES ((yyval)) = size_mode;
  }
    break;

  case 800:
/* Line 1792 of yacc.c  */
#line 4386 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  }
    break;

  case 801:
/* Line 1792 of yacc.c  */
#line 4390 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY CONTENT not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_CONTENT;
	}
  }
    break;

  case 802:
/* Line 1792 of yacc.c  */
#line 4398 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  }
    break;

  case 803:
/* Line 1792 of yacc.c  */
#line 4408 "parser.y"
    { (yyval) = NULL; }
    break;

  case 804:
/* Line 1792 of yacc.c  */
#line 4409 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 805:
/* Line 1792 of yacc.c  */
#line 4410 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 806:
/* Line 1792 of yacc.c  */
#line 4415 "parser.y"
    {
	(yyval) = NULL;
  }
    break;

  case 807:
/* Line 1792 of yacc.c  */
#line 4419 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 808:
/* Line 1792 of yacc.c  */
#line 4423 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 809:
/* Line 1792 of yacc.c  */
#line 4430 "parser.y"
    {
	(yyval) = NULL;
  }
    break;

  case 810:
/* Line 1792 of yacc.c  */
#line 4434 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 811:
/* Line 1792 of yacc.c  */
#line 4438 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 812:
/* Line 1792 of yacc.c  */
#line 4444 "parser.y"
    { terminator_warning (TERM_CALL); }
    break;

  case 813:
/* Line 1792 of yacc.c  */
#line 4445 "parser.y"
    { terminator_clear (TERM_CALL); }
    break;

  case 814:
/* Line 1792 of yacc.c  */
#line 4454 "parser.y"
    { BEGIN_STATEMENT ("CANCEL", 0); }
    break;

  case 817:
/* Line 1792 of yacc.c  */
#line 4460 "parser.y"
    {
	cb_emit_cancel ((yyvsp[(2) - (2)]));
  }
    break;

  case 818:
/* Line 1792 of yacc.c  */
#line 4464 "parser.y"
    {
	cb_emit_cancel_all ();
  }
    break;

  case 819:
/* Line 1792 of yacc.c  */
#line 4475 "parser.y"
    { BEGIN_STATEMENT ("CLOSE", 0); }
    break;

  case 822:
/* Line 1792 of yacc.c  */
#line 4482 "parser.y"
    {
	BEGIN_IMPLICIT_STATEMENT ((yyvsp[(2) - (3)]));
	if ((yyvsp[(2) - (3)]) != cb_error_node) {
		cb_emit_close ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
	}
  }
    break;

  case 823:
/* Line 1792 of yacc.c  */
#line 4491 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NORMAL); }
    break;

  case 824:
/* Line 1792 of yacc.c  */
#line 4492 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT); }
    break;

  case 825:
/* Line 1792 of yacc.c  */
#line 4493 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT_REMOVAL); }
    break;

  case 826:
/* Line 1792 of yacc.c  */
#line 4494 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NO_REWIND); }
    break;

  case 827:
/* Line 1792 of yacc.c  */
#line 4495 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_LOCK); }
    break;

  case 830:
/* Line 1792 of yacc.c  */
#line 4506 "parser.y"
    { BEGIN_STATEMENT ("COMPUTE", TERM_COMPUTE); }
    break;

  case 832:
/* Line 1792 of yacc.c  */
#line 4513 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(1) - (4)]), 0, (yyvsp[(3) - (4)]));
  }
    break;

  case 833:
/* Line 1792 of yacc.c  */
#line 4519 "parser.y"
    { terminator_warning (TERM_COMPUTE); }
    break;

  case 834:
/* Line 1792 of yacc.c  */
#line 4520 "parser.y"
    { terminator_clear (TERM_COMPUTE); }
    break;

  case 837:
/* Line 1792 of yacc.c  */
#line 4531 "parser.y"
    {
	BEGIN_STATEMENT ("COMMIT", 0);
	cb_emit_commit ();
  }
    break;

  case 838:
/* Line 1792 of yacc.c  */
#line 4544 "parser.y"
    {
	BEGIN_STATEMENT ("CONTINUE", 0);
	cb_emit_continue ();
  }
    break;

  case 839:
/* Line 1792 of yacc.c  */
#line 4556 "parser.y"
    { BEGIN_STATEMENT ("DELETE", TERM_DELETE); }
    break;

  case 840:
/* Line 1792 of yacc.c  */
#line 4559 "parser.y"
    {
	if ((yyvsp[(3) - (6)]) != cb_error_node) {
		cb_emit_delete ((yyvsp[(3) - (6)]));
	}
  }
    break;

  case 841:
/* Line 1792 of yacc.c  */
#line 4567 "parser.y"
    { terminator_warning (TERM_DELETE); }
    break;

  case 842:
/* Line 1792 of yacc.c  */
#line 4568 "parser.y"
    { terminator_clear (TERM_DELETE); }
    break;

  case 843:
/* Line 1792 of yacc.c  */
#line 4577 "parser.y"
    { BEGIN_STATEMENT ("DELETE-FILE", 0); }
    break;

  case 844:
/* Line 1792 of yacc.c  */
#line 4579 "parser.y"
    {
	cb_tree l;
	for (l = (yyvsp[(4) - (4)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			BEGIN_IMPLICIT_STATEMENT (l);
			cb_emit_delete_file (CB_VALUE (l));
		}
	}
  }
    break;

  case 845:
/* Line 1792 of yacc.c  */
#line 4597 "parser.y"
    {
	BEGIN_STATEMENT ("DISPLAY", TERM_DISPLAY);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  }
    break;

  case 847:
/* Line 1792 of yacc.c  */
#line 4610 "parser.y"
    {
	cb_emit_env_name ((yyvsp[(1) - (3)]));
  }
    break;

  case 848:
/* Line 1792 of yacc.c  */
#line 4614 "parser.y"
    {
	cb_emit_env_value ((yyvsp[(1) - (3)]));
  }
    break;

  case 849:
/* Line 1792 of yacc.c  */
#line 4618 "parser.y"
    {
	cb_emit_arg_number ((yyvsp[(1) - (3)]));
  }
    break;

  case 850:
/* Line 1792 of yacc.c  */
#line 4622 "parser.y"
    {
	cb_emit_command_line ((yyvsp[(1) - (3)]));
  }
    break;

  case 851:
/* Line 1792 of yacc.c  */
#line 4626 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (4)]), cb_int0, (yyvsp[(3) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  }
    break;

  case 852:
/* Line 1792 of yacc.c  */
#line 4630 "parser.y"
    {
	cb_emit_display_mnemonic ((yyvsp[(1) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  }
    break;

  case 853:
/* Line 1792 of yacc.c  */
#line 4634 "parser.y"
    {
	cb_tree word = cb_build_display_upon_direct ((yyvsp[(4) - (6)]));
	cb_emit_display ((yyvsp[(1) - (6)]), word, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  }
    break;

  case 854:
/* Line 1792 of yacc.c  */
#line 4639 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  }
    break;

  case 855:
/* Line 1792 of yacc.c  */
#line 4643 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  }
    break;

  case 856:
/* Line 1792 of yacc.c  */
#line 4649 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 857:
/* Line 1792 of yacc.c  */
#line 4650 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 858:
/* Line 1792 of yacc.c  */
#line 4651 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 861:
/* Line 1792 of yacc.c  */
#line 4661 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; }
    break;

  case 862:
/* Line 1792 of yacc.c  */
#line 4662 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; }
    break;

  case 863:
/* Line 1792 of yacc.c  */
#line 4663 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOL; }
    break;

  case 864:
/* Line 1792 of yacc.c  */
#line 4664 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOS; }
    break;

  case 865:
/* Line 1792 of yacc.c  */
#line 4665 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; }
    break;

  case 866:
/* Line 1792 of yacc.c  */
#line 4666 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; }
    break;

  case 867:
/* Line 1792 of yacc.c  */
#line 4667 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; }
    break;

  case 868:
/* Line 1792 of yacc.c  */
#line 4668 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; }
    break;

  case 869:
/* Line 1792 of yacc.c  */
#line 4669 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; }
    break;

  case 870:
/* Line 1792 of yacc.c  */
#line 4671 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  }
    break;

  case 871:
/* Line 1792 of yacc.c  */
#line 4675 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  }
    break;

  case 872:
/* Line 1792 of yacc.c  */
#line 4679 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  }
    break;

  case 873:
/* Line 1792 of yacc.c  */
#line 4683 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  }
    break;

  case 874:
/* Line 1792 of yacc.c  */
#line 4687 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_LINE; }
    break;

  case 875:
/* Line 1792 of yacc.c  */
#line 4688 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_SCREEN; }
    break;

  case 876:
/* Line 1792 of yacc.c  */
#line 4692 "parser.y"
    { terminator_warning (TERM_DISPLAY); }
    break;

  case 877:
/* Line 1792 of yacc.c  */
#line 4693 "parser.y"
    { terminator_clear (TERM_DISPLAY); }
    break;

  case 878:
/* Line 1792 of yacc.c  */
#line 4702 "parser.y"
    { BEGIN_STATEMENT ("DIVIDE", TERM_DIVIDE); }
    break;

  case 880:
/* Line 1792 of yacc.c  */
#line 4709 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '/', (yyvsp[(1) - (4)]));
  }
    break;

  case 881:
/* Line 1792 of yacc.c  */
#line 4713 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(3) - (6)]), '/', (yyvsp[(1) - (6)])));
  }
    break;

  case 882:
/* Line 1792 of yacc.c  */
#line 4717 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '/', (yyvsp[(3) - (6)])));
  }
    break;

  case 883:
/* Line 1792 of yacc.c  */
#line 4721 "parser.y"
    {
	cb_emit_divide ((yyvsp[(3) - (8)]), (yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  }
    break;

  case 884:
/* Line 1792 of yacc.c  */
#line 4725 "parser.y"
    {
	cb_emit_divide ((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  }
    break;

  case 885:
/* Line 1792 of yacc.c  */
#line 4731 "parser.y"
    { terminator_warning (TERM_DIVIDE); }
    break;

  case 886:
/* Line 1792 of yacc.c  */
#line 4732 "parser.y"
    { terminator_clear (TERM_DIVIDE); }
    break;

  case 887:
/* Line 1792 of yacc.c  */
#line 4741 "parser.y"
    { BEGIN_STATEMENT ("ENTRY", 0); }
    break;

  case 888:
/* Line 1792 of yacc.c  */
#line 4743 "parser.y"
    {
	if (current_program->nested_level) {
		cb_error (_("ENTRY is invalid in nested program"));
	} else if (cb_verify (cb_entry_statement, "ENTRY")) {
		if (cobc_check_valid_name ((char *)(CB_LITERAL ((yyvsp[(3) - (4)]))->data))) {
			cb_error (_("ENTRY '%s' invalid"), (char *)(CB_LITERAL ((yyvsp[(3) - (4)]))->data));
		}
		emit_entry ((char *)(CB_LITERAL ((yyvsp[(3) - (4)]))->data), 1, (yyvsp[(4) - (4)]));
	}
	check_unreached = 0;
  }
    break;

  case 889:
/* Line 1792 of yacc.c  */
#line 4763 "parser.y"
    {
	BEGIN_STATEMENT ("EVALUATE", TERM_EVALUATE);
	eval_level++;
	for (eval_inc = 0; eval_inc < 64; eval_inc++) {
		eval_check[eval_level][eval_inc] = 0;
	}
	eval_inc = 0;
	eval_inc2 = 0;
  }
    break;

  case 890:
/* Line 1792 of yacc.c  */
#line 4774 "parser.y"
    {
	cb_emit_evaluate ((yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]));
	eval_level--;
  }
    break;

  case 891:
/* Line 1792 of yacc.c  */
#line 4781 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 892:
/* Line 1792 of yacc.c  */
#line 4784 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 893:
/* Line 1792 of yacc.c  */
#line 4794 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE_P ((yyvsp[(1) - (1)]))) {
		eval_check[eval_level][eval_inc++] = 0;
	} else {
		eval_check[eval_level][eval_inc++] = 1;
	}
  }
    break;

  case 894:
/* Line 1792 of yacc.c  */
#line 4803 "parser.y"
    {
	(yyval) = cb_true;
	eval_check[eval_level][eval_inc++] = 2;
  }
    break;

  case 895:
/* Line 1792 of yacc.c  */
#line 4808 "parser.y"
    {
	(yyval) = cb_false;
	eval_check[eval_level][eval_inc++] = 3;
  }
    break;

  case 896:
/* Line 1792 of yacc.c  */
#line 4816 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (2)]);
	if ((yyvsp[(2) - (2)])) {
		if (cb_allow_empty_imperative_statement) {
			/*
			 * some compiler implementation allow empty
			 * imperative statements in WHEN phrases, and
			 * treats WHEN OTHER phrase following that
			 * asif the rest part of when_list belonging
			 * to that.
			 */
			cb_tree l, case_item;
			l = (yyval);
			while (CB_CHAIN (l)) {
				l = CB_CHAIN (l);
			}
			case_item = CB_VALUE (l);
			if (!CB_VALUE (case_item)) {
				 /* warning: duplecates ptr. here */
				CB_VALUE (case_item) = CB_VALUE ((yyvsp[(2) - (2)]));
			}
		}
		(yyval) = cb_list_add ((yyval), (yyvsp[(2) - (2)]));
	}
  }
    break;

  case 897:
/* Line 1792 of yacc.c  */
#line 4844 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 898:
/* Line 1792 of yacc.c  */
#line 4846 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 899:
/* Line 1792 of yacc.c  */
#line 4851 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 900:
/* Line 1792 of yacc.c  */
#line 4855 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]));
	eval_inc2 = 0;
  }
    break;

  case 901:
/* Line 1792 of yacc.c  */
#line 4866 "parser.y"
    {
	(yyval) = NULL;
  }
    break;

  case 902:
/* Line 1792 of yacc.c  */
#line 4870 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 903:
/* Line 1792 of yacc.c  */
#line 4874 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), NULL);
	eval_inc2 = 0;
  }
    break;

  case 904:
/* Line 1792 of yacc.c  */
#line 4884 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); }
    break;

  case 905:
/* Line 1792 of yacc.c  */
#line 4886 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 906:
/* Line 1792 of yacc.c  */
#line 4890 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 907:
/* Line 1792 of yacc.c  */
#line 4893 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 908:
/* Line 1792 of yacc.c  */
#line 4903 "parser.y"
    {
	cb_tree not;
	cb_tree e1;
	cb_tree e2;

	not = cb_int0;
	e2 = (yyvsp[(2) - (2)]);
	/* in case the first token is NOT */
	if (CB_PURPOSE_INT ((yyvsp[(1) - (2)])) == '!') {
		if (eval_check[eval_level][eval_inc2] < 2) {
			not = cb_int1;
			(yyvsp[(1) - (2)]) = CB_CHAIN ((yyvsp[(1) - (2)]));
		}
	}

	/* build expr now */
	e1 = cb_build_expr ((yyvsp[(1) - (2)]));

	if (e2 == NULL) {
		/* WHEN expr */
		eval_inc2++;
		(yyval) = cb_build_pair (not, cb_build_pair (e1, NULL));
	} else {
		/* WHEN expr THRU expr */
		(yyval) = cb_build_pair (not, cb_build_pair (e1, e2));
		eval_inc2++;
	}
  }
    break;

  case 909:
/* Line 1792 of yacc.c  */
#line 4931 "parser.y"
    { (yyval) = cb_any; eval_inc2++; }
    break;

  case 910:
/* Line 1792 of yacc.c  */
#line 4932 "parser.y"
    { (yyval) = cb_true; eval_inc2++; }
    break;

  case 911:
/* Line 1792 of yacc.c  */
#line 4933 "parser.y"
    { (yyval) = cb_false; eval_inc2++; }
    break;

  case 912:
/* Line 1792 of yacc.c  */
#line 4936 "parser.y"
    { (yyval) = NULL; }
    break;

  case 913:
/* Line 1792 of yacc.c  */
#line 4937 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 914:
/* Line 1792 of yacc.c  */
#line 4941 "parser.y"
    { terminator_warning (TERM_EVALUATE); }
    break;

  case 915:
/* Line 1792 of yacc.c  */
#line 4942 "parser.y"
    { terminator_clear (TERM_EVALUATE); }
    break;

  case 916:
/* Line 1792 of yacc.c  */
#line 4951 "parser.y"
    { BEGIN_STATEMENT ("EXIT", 0); }
    break;

  case 918:
/* Line 1792 of yacc.c  */
#line 4956 "parser.y"
    { /* nothing */ }
    break;

  case 919:
/* Line 1792 of yacc.c  */
#line 4958 "parser.y"
    {
	if (in_declaratives && use_global_ind) {
		cb_error (_("EXIT PROGRAM is not allowed within a USE GLOBAL procedure"));
	}
	check_unreached = 1;
	cb_emit_exit (0);
  }
    break;

  case 920:
/* Line 1792 of yacc.c  */
#line 4966 "parser.y"
    {
	struct cb_perform	*p;
	char			name[64];

	if (!perform_stack) {
		cb_error (_("EXIT PERFORM is only valid with inline PERFORM"));
	} else {
		p = CB_PERFORM (CB_VALUE (perform_stack));
		if (!p->exit_label) {
			sprintf (name, "EXIT PERFORM %d", cb_id);
			p->exit_label = cb_build_reference (name);
			CB_LABEL (cb_build_label (p->exit_label, current_section))->need_begin = 1;
		}
		cb_emit_goto (cb_list_init (p->exit_label), NULL);
	}
  }
    break;

  case 921:
/* Line 1792 of yacc.c  */
#line 4983 "parser.y"
    {
	struct cb_perform	*p;
	char			name[64];

	if (!perform_stack) {
		cb_error (_("EXIT PERFORM is only valid with inline PERFORM"));
	} else {
		p = CB_PERFORM (CB_VALUE (perform_stack));
		if (!p->cycle_label) {
			sprintf (name, "EXIT PERFORM CYCLE %d", cb_id);
			p->cycle_label = cb_build_reference (name);
			CB_LABEL (cb_build_label (p->cycle_label, current_section))->need_begin = 1;
		}
		cb_emit_goto (cb_list_init (p->cycle_label), NULL);
	}
  }
    break;

  case 922:
/* Line 1792 of yacc.c  */
#line 5000 "parser.y"
    {
	cb_tree	plabel;
	char	name[64];

	if (!current_section) {
		cb_error (_("EXIT SECTION is only valid with an active SECTION"));
	} else {
		if (!current_section->exit_label) {
			sprintf (name, "EXIT SECTION %d", cb_id);
			plabel = cb_build_reference (name);
			current_section->exit_label = cb_build_label (plabel, current_section);
			current_section->exit_label_ref = plabel;
			CB_LABEL (current_section->exit_label)->need_begin = 1;
		}
		cb_emit_goto (cb_list_init (current_section->exit_label_ref), NULL);
	}
  }
    break;

  case 923:
/* Line 1792 of yacc.c  */
#line 5018 "parser.y"
    {
	cb_tree	plabel;
	char	name[64];

	if (!current_paragraph) {
		cb_error (_("EXIT PARAGRAPH is only valid with an active PARAGRAPH"));
	} else {
		if (!current_paragraph->exit_label) {
			sprintf (name, "EXIT PARAGRAPH %d", cb_id);
			plabel = cb_build_reference (name);
			current_paragraph->exit_label = cb_build_label (plabel, current_section);
			current_paragraph->exit_label_ref = plabel;
			CB_LABEL (current_paragraph->exit_label)->need_begin = 1;
		}
		cb_emit_goto (cb_list_init (current_paragraph->exit_label_ref), NULL);
	}
  }
    break;

  case 924:
/* Line 1792 of yacc.c  */
#line 5042 "parser.y"
    { BEGIN_STATEMENT ("FREE", 0); }
    break;

  case 925:
/* Line 1792 of yacc.c  */
#line 5044 "parser.y"
    {
	cb_emit_free ((yyvsp[(3) - (3)]));
  }
    break;

  case 926:
/* Line 1792 of yacc.c  */
#line 5055 "parser.y"
    { BEGIN_STATEMENT ("GENERATE", 0); }
    break;

  case 927:
/* Line 1792 of yacc.c  */
#line 5057 "parser.y"
    {
	PENDING("GENERATE");
  }
    break;

  case 928:
/* Line 1792 of yacc.c  */
#line 5068 "parser.y"
    { BEGIN_STATEMENT ("GO TO", 0); }
    break;

  case 929:
/* Line 1792 of yacc.c  */
#line 5070 "parser.y"
    {
	cb_emit_goto ((yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
  }
    break;

  case 930:
/* Line 1792 of yacc.c  */
#line 5077 "parser.y"
    {
	check_unreached = 1;
	(yyval) = NULL;
  }
    break;

  case 931:
/* Line 1792 of yacc.c  */
#line 5082 "parser.y"
    {
	check_unreached = 0;
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 932:
/* Line 1792 of yacc.c  */
#line 5094 "parser.y"
    { BEGIN_STATEMENT ("GOBACK", 0); }
    break;

  case 933:
/* Line 1792 of yacc.c  */
#line 5095 "parser.y"
    {
	check_unreached = 1;
	cb_emit_exit (1);
  }
    break;

  case 934:
/* Line 1792 of yacc.c  */
#line 5107 "parser.y"
    { BEGIN_STATEMENT ("IF", TERM_IF); }
    break;

  case 935:
/* Line 1792 of yacc.c  */
#line 5109 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 936:
/* Line 1792 of yacc.c  */
#line 5114 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(6) - (8)]) == NULL) {
		cb_error (_("syntax error"));
	}
	cb_emit_if ((yyvsp[(3) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  }
    break;

  case 938:
/* Line 1792 of yacc.c  */
#line 5125 "parser.y"
    {
	(yyval) = NULL;
  }
    break;

  case 939:
/* Line 1792 of yacc.c  */
#line 5129 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 940:
/* Line 1792 of yacc.c  */
#line 5133 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 941:
/* Line 1792 of yacc.c  */
#line 5142 "parser.y"
    { terminator_warning (TERM_IF); }
    break;

  case 942:
/* Line 1792 of yacc.c  */
#line 5143 "parser.y"
    { terminator_clear (TERM_IF); }
    break;

  case 943:
/* Line 1792 of yacc.c  */
#line 5152 "parser.y"
    { BEGIN_STATEMENT ("INITIALIZE", 0); }
    break;

  case 944:
/* Line 1792 of yacc.c  */
#line 5154 "parser.y"
    {
	cb_emit_initialize ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)]));
  }
    break;

  case 945:
/* Line 1792 of yacc.c  */
#line 5160 "parser.y"
    { (yyval) = NULL; }
    break;

  case 946:
/* Line 1792 of yacc.c  */
#line 5161 "parser.y"
    { (yyval) = cb_true; }
    break;

  case 947:
/* Line 1792 of yacc.c  */
#line 5165 "parser.y"
    { (yyval) = NULL; }
    break;

  case 948:
/* Line 1792 of yacc.c  */
#line 5166 "parser.y"
    { (yyval) = cb_true; }
    break;

  case 949:
/* Line 1792 of yacc.c  */
#line 5167 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); }
    break;

  case 950:
/* Line 1792 of yacc.c  */
#line 5171 "parser.y"
    { (yyval) = NULL; }
    break;

  case 951:
/* Line 1792 of yacc.c  */
#line 5173 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 952:
/* Line 1792 of yacc.c  */
#line 5177 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 953:
/* Line 1792 of yacc.c  */
#line 5179 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 954:
/* Line 1792 of yacc.c  */
#line 5183 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); }
    break;

  case 955:
/* Line 1792 of yacc.c  */
#line 5187 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHABETIC); }
    break;

  case 956:
/* Line 1792 of yacc.c  */
#line 5188 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC); }
    break;

  case 957:
/* Line 1792 of yacc.c  */
#line 5189 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC); }
    break;

  case 958:
/* Line 1792 of yacc.c  */
#line 5190 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC_EDITED); }
    break;

  case 959:
/* Line 1792 of yacc.c  */
#line 5191 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC_EDITED); }
    break;

  case 960:
/* Line 1792 of yacc.c  */
#line 5192 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL); }
    break;

  case 961:
/* Line 1792 of yacc.c  */
#line 5193 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL_EDITED); }
    break;

  case 962:
/* Line 1792 of yacc.c  */
#line 5197 "parser.y"
    { (yyval) = NULL; }
    break;

  case 963:
/* Line 1792 of yacc.c  */
#line 5198 "parser.y"
    { (yyval) = cb_true; }
    break;

  case 964:
/* Line 1792 of yacc.c  */
#line 5207 "parser.y"
    { BEGIN_STATEMENT ("INITIATE", 0); }
    break;

  case 965:
/* Line 1792 of yacc.c  */
#line 5209 "parser.y"
    {
	PENDING("INITIATE");
  }
    break;

  case 966:
/* Line 1792 of yacc.c  */
#line 5220 "parser.y"
    {
	BEGIN_STATEMENT ("INSPECT", 0);
	sending_id = 0;
	inspect_keyword = 0;
  }
    break;

  case 968:
/* Line 1792 of yacc.c  */
#line 5229 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 0; }
    break;

  case 969:
/* Line 1792 of yacc.c  */
#line 5230 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; }
    break;

  case 970:
/* Line 1792 of yacc.c  */
#line 5231 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; }
    break;

  case 973:
/* Line 1792 of yacc.c  */
#line 5240 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 0); }
    break;

  case 974:
/* Line 1792 of yacc.c  */
#line 5241 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int1, 1); }
    break;

  case 975:
/* Line 1792 of yacc.c  */
#line 5242 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 2); }
    break;

  case 976:
/* Line 1792 of yacc.c  */
#line 5248 "parser.y"
    { cb_init_tarrying (); }
    break;

  case 977:
/* Line 1792 of yacc.c  */
#line 5249 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 978:
/* Line 1792 of yacc.c  */
#line 5253 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 979:
/* Line 1792 of yacc.c  */
#line 5254 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 980:
/* Line 1792 of yacc.c  */
#line 5258 "parser.y"
    { (yyval) = cb_build_tarrying_data ((yyvsp[(1) - (2)])); }
    break;

  case 981:
/* Line 1792 of yacc.c  */
#line 5259 "parser.y"
    { (yyval) = cb_build_tarrying_characters ((yyvsp[(2) - (2)])); }
    break;

  case 982:
/* Line 1792 of yacc.c  */
#line 5260 "parser.y"
    { (yyval) = cb_build_tarrying_all (); }
    break;

  case 983:
/* Line 1792 of yacc.c  */
#line 5261 "parser.y"
    { (yyval) = cb_build_tarrying_leading (); }
    break;

  case 984:
/* Line 1792 of yacc.c  */
#line 5262 "parser.y"
    { (yyval) = cb_build_tarrying_trailing (); }
    break;

  case 985:
/* Line 1792 of yacc.c  */
#line 5263 "parser.y"
    { (yyval) = cb_build_tarrying_value ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 986:
/* Line 1792 of yacc.c  */
#line 5269 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); inspect_keyword = 0; }
    break;

  case 987:
/* Line 1792 of yacc.c  */
#line 5273 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 988:
/* Line 1792 of yacc.c  */
#line 5274 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 989:
/* Line 1792 of yacc.c  */
#line 5279 "parser.y"
    {
	(yyval) = cb_build_replacing_characters ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]), save_tree_1);
	inspect_keyword = 0;
  }
    break;

  case 990:
/* Line 1792 of yacc.c  */
#line 5283 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 991:
/* Line 1792 of yacc.c  */
#line 5287 "parser.y"
    { /* Nothing */ }
    break;

  case 992:
/* Line 1792 of yacc.c  */
#line 5288 "parser.y"
    { inspect_keyword = 1; }
    break;

  case 993:
/* Line 1792 of yacc.c  */
#line 5289 "parser.y"
    { inspect_keyword = 2; }
    break;

  case 994:
/* Line 1792 of yacc.c  */
#line 5290 "parser.y"
    { inspect_keyword = 3; }
    break;

  case 995:
/* Line 1792 of yacc.c  */
#line 5291 "parser.y"
    { inspect_keyword = 4; }
    break;

  case 996:
/* Line 1792 of yacc.c  */
#line 5296 "parser.y"
    {
	switch (inspect_keyword) {
		case 1:
			(yyval) = cb_build_replacing_all ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]), save_tree_1);
			break;
		case 2:
			(yyval) = cb_build_replacing_leading ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
			break;
		case 3:
			(yyval) = cb_build_replacing_first ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
			break;
		case 4:
			(yyval) = cb_build_replacing_trailing ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
			break;
		default:
			cb_error (_("INSPECT missing a keyword"));
			(yyval) = cb_error_node;
			break;
	}
  }
    break;

  case 997:
/* Line 1792 of yacc.c  */
#line 5322 "parser.y"
    {
	if (cb_validate_inspect (save_tree_1, (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])) < 0 ) {
		(yyval) = cb_error_node;
	} else {
		(yyval) = cb_build_converting ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
	}
  }
    break;

  case 998:
/* Line 1792 of yacc.c  */
#line 5334 "parser.y"
    { (yyval) = cb_build_inspect_region_start (); }
    break;

  case 999:
/* Line 1792 of yacc.c  */
#line 5336 "parser.y"
    { (yyval) = cb_build_inspect_region ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); }
    break;

  case 1002:
/* Line 1792 of yacc.c  */
#line 5347 "parser.y"
    { BEGIN_STATEMENT ("MERGE", 0); }
    break;

  case 1004:
/* Line 1792 of yacc.c  */
#line 5357 "parser.y"
    { BEGIN_STATEMENT ("MOVE", 0); }
    break;

  case 1006:
/* Line 1792 of yacc.c  */
#line 5363 "parser.y"
    {
	cb_emit_move ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 1007:
/* Line 1792 of yacc.c  */
#line 5367 "parser.y"
    {
	cb_emit_move_corresponding ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  }
    break;

  case 1008:
/* Line 1792 of yacc.c  */
#line 5378 "parser.y"
    { BEGIN_STATEMENT ("MULTIPLY", TERM_MULTIPLY); }
    break;

  case 1010:
/* Line 1792 of yacc.c  */
#line 5385 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '*', (yyvsp[(1) - (4)]));
  }
    break;

  case 1011:
/* Line 1792 of yacc.c  */
#line 5389 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '*', (yyvsp[(3) - (6)])));
  }
    break;

  case 1012:
/* Line 1792 of yacc.c  */
#line 5395 "parser.y"
    { terminator_warning (TERM_MULTIPLY); }
    break;

  case 1013:
/* Line 1792 of yacc.c  */
#line 5396 "parser.y"
    { terminator_clear (TERM_MULTIPLY); }
    break;

  case 1014:
/* Line 1792 of yacc.c  */
#line 5405 "parser.y"
    { BEGIN_STATEMENT ("OPEN", 0); }
    break;

  case 1017:
/* Line 1792 of yacc.c  */
#line 5412 "parser.y"
    {
	cb_tree l;
	for (l = (yyvsp[(4) - (5)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			BEGIN_IMPLICIT_STATEMENT (l);
			cb_emit_open (CB_VALUE (l), (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]));
		}
	}
  }
    break;

  case 1018:
/* Line 1792 of yacc.c  */
#line 5424 "parser.y"
    { (yyval) = cb_int (COB_OPEN_INPUT); }
    break;

  case 1019:
/* Line 1792 of yacc.c  */
#line 5425 "parser.y"
    { (yyval) = cb_int (COB_OPEN_OUTPUT); }
    break;

  case 1020:
/* Line 1792 of yacc.c  */
#line 5426 "parser.y"
    { (yyval) = cb_int (COB_OPEN_I_O); }
    break;

  case 1021:
/* Line 1792 of yacc.c  */
#line 5427 "parser.y"
    { (yyval) = cb_int (COB_OPEN_EXTEND); }
    break;

  case 1022:
/* Line 1792 of yacc.c  */
#line 5431 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1023:
/* Line 1792 of yacc.c  */
#line 5432 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 1024:
/* Line 1792 of yacc.c  */
#line 5436 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1025:
/* Line 1792 of yacc.c  */
#line 5437 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1026:
/* Line 1792 of yacc.c  */
#line 5438 "parser.y"
    { PENDING ("OPEN ... WITH LOCK"); }
    break;

  case 1027:
/* Line 1792 of yacc.c  */
#line 5450 "parser.y"
    { BEGIN_STATEMENT ("PERFORM", TERM_PERFORM); }
    break;

  case 1029:
/* Line 1792 of yacc.c  */
#line 5456 "parser.y"
    {
	cb_emit_perform ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));
  }
    break;

  case 1030:
/* Line 1792 of yacc.c  */
#line 5460 "parser.y"
    {
	perform_stack = cb_cons ((yyvsp[(1) - (1)]), perform_stack);
	check_unreached = 0;
  }
    break;

  case 1031:
/* Line 1792 of yacc.c  */
#line 5465 "parser.y"
    {
	perform_stack = CB_CHAIN (perform_stack);
	cb_emit_perform ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  }
    break;

  case 1032:
/* Line 1792 of yacc.c  */
#line 5470 "parser.y"
    {
	cb_emit_perform ((yyvsp[(1) - (2)]), NULL);
  }
    break;

  case 1033:
/* Line 1792 of yacc.c  */
#line 5476 "parser.y"
    { terminator_error (); }
    break;

  case 1034:
/* Line 1792 of yacc.c  */
#line 5477 "parser.y"
    { terminator_clear (TERM_PERFORM); }
    break;

  case 1035:
/* Line 1792 of yacc.c  */
#line 5482 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(1) - (1)]))->length = cb_true; /* return from $1 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (1)]), (yyvsp[(1) - (1)]));
  }
    break;

  case 1036:
/* Line 1792 of yacc.c  */
#line 5487 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(3) - (3)]))->length = cb_true; /* return from $3 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 1037:
/* Line 1792 of yacc.c  */
#line 5495 "parser.y"
    {
	(yyval) = cb_build_perform_once (NULL);
  }
    break;

  case 1038:
/* Line 1792 of yacc.c  */
#line 5499 "parser.y"
    {
	(yyval) = cb_build_perform_forever (NULL);
  }
    break;

  case 1039:
/* Line 1792 of yacc.c  */
#line 5503 "parser.y"
    {
	(yyval) = cb_build_perform_times ((yyvsp[(1) - (2)]));
	current_program->loop_counter++;
  }
    break;

  case 1040:
/* Line 1792 of yacc.c  */
#line 5508 "parser.y"
    {
	cb_tree varying;

	varying = cb_list_init (cb_build_perform_varying (NULL, NULL, NULL, (yyvsp[(3) - (3)])));
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), varying);
  }
    break;

  case 1041:
/* Line 1792 of yacc.c  */
#line 5515 "parser.y"
    {
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 1042:
/* Line 1792 of yacc.c  */
#line 5521 "parser.y"
    { (yyval) = CB_BEFORE; }
    break;

  case 1043:
/* Line 1792 of yacc.c  */
#line 5522 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 1044:
/* Line 1792 of yacc.c  */
#line 5526 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 1045:
/* Line 1792 of yacc.c  */
#line 5528 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 1046:
/* Line 1792 of yacc.c  */
#line 5533 "parser.y"
    {
	(yyval) = cb_build_perform_varying ((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  }
    break;

  case 1047:
/* Line 1792 of yacc.c  */
#line 5544 "parser.y"
    { BEGIN_STATEMENT ("READ", TERM_READ); }
    break;

  case 1048:
/* Line 1792 of yacc.c  */
#line 5547 "parser.y"
    {
	if ((yyvsp[(3) - (10)]) != cb_error_node) {
		if (cb_use_invalidkey_handler_on_status34 &&
		    current_statement->handler_id == COB_EC_I_O_INVALID_KEY &&
		    (CB_FILE(cb_ref ((yyvsp[(3) - (10)])))->organization != COB_ORG_RELATIVE &&
		     CB_FILE(cb_ref ((yyvsp[(3) - (10)])))->organization != COB_ORG_INDEXED)) {
			current_statement->handler_id = COB_EC_I_O_PERMANENT_ERROR;
		}
		if ((yyvsp[(7) - (10)]) && (CB_FILE(cb_ref ((yyvsp[(3) - (10)])))->lock_mode & COB_LOCK_AUTOMATIC)) {
			cb_error (_("LOCK clause invalid with file LOCK AUTOMATIC"));
		} else if ((yyvsp[(8) - (10)]) &&
		      (CB_FILE(cb_ref ((yyvsp[(3) - (10)])))->organization != COB_ORG_RELATIVE &&
		       CB_FILE(cb_ref ((yyvsp[(3) - (10)])))->organization != COB_ORG_INDEXED)) {
			cb_error (_("KEY clause invalid with this file type"));
		} else if (current_statement->handler_id == COB_EC_I_O_INVALID_KEY &&
		      (CB_FILE(cb_ref ((yyvsp[(3) - (10)])))->organization != COB_ORG_RELATIVE &&
		       CB_FILE(cb_ref ((yyvsp[(3) - (10)])))->organization != COB_ORG_INDEXED)) {
			cb_error (_("INVALID KEY clause invalid with this file type"));
		} else {
			cb_emit_read ((yyvsp[(3) - (10)]), (yyvsp[(4) - (10)]), (yyvsp[(6) - (10)]), (yyvsp[(8) - (10)]), (yyvsp[(7) - (10)]));
		}
	}
  }
    break;

  case 1049:
/* Line 1792 of yacc.c  */
#line 5573 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1050:
/* Line 1792 of yacc.c  */
#line 5574 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 1051:
/* Line 1792 of yacc.c  */
#line 5578 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1052:
/* Line 1792 of yacc.c  */
#line 5580 "parser.y"
    {
	(yyval) = cb_int3;
  }
    break;

  case 1053:
/* Line 1792 of yacc.c  */
#line 5584 "parser.y"
    {
	(yyval) = cb_int1;
  }
    break;

  case 1054:
/* Line 1792 of yacc.c  */
#line 5588 "parser.y"
    {
	(yyval) = cb_int2;
  }
    break;

  case 1055:
/* Line 1792 of yacc.c  */
#line 5592 "parser.y"
    {
	(yyval) = cb_int3;
  }
    break;

  case 1056:
/* Line 1792 of yacc.c  */
#line 5596 "parser.y"
    {
	(yyval) = cb_int4;
  }
    break;

  case 1057:
/* Line 1792 of yacc.c  */
#line 5602 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1058:
/* Line 1792 of yacc.c  */
#line 5604 "parser.y"
    {
#if	defined(WITH_CISAM) || defined(WITH_DISAM) || defined(WITH_VBISAM) || defined(WITH_INDEX_EXTFH)
	(yyval) = (yyvsp[(3) - (3)]);
#else
	if (CB_LIST((yyvsp[(3) - (3)]))->chain) {
		PENDING ("SPLIT KEYS");
	} else {
		(yyval) = (yyvsp[(3) - (3)]);
	}
#endif
  }
    break;

  case 1062:
/* Line 1792 of yacc.c  */
#line 5623 "parser.y"
    { terminator_warning (TERM_READ); }
    break;

  case 1063:
/* Line 1792 of yacc.c  */
#line 5624 "parser.y"
    { terminator_clear (TERM_READ); }
    break;

  case 1064:
/* Line 1792 of yacc.c  */
#line 5633 "parser.y"
    { BEGIN_STATEMENT ("RELEASE", 0); }
    break;

  case 1065:
/* Line 1792 of yacc.c  */
#line 5635 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_release ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
	}
  }
    break;

  case 1066:
/* Line 1792 of yacc.c  */
#line 5648 "parser.y"
    { BEGIN_STATEMENT ("RETURN", TERM_RETURN); }
    break;

  case 1067:
/* Line 1792 of yacc.c  */
#line 5651 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_return ((yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]));
	}
  }
    break;

  case 1068:
/* Line 1792 of yacc.c  */
#line 5659 "parser.y"
    { terminator_warning (TERM_RETURN); }
    break;

  case 1069:
/* Line 1792 of yacc.c  */
#line 5660 "parser.y"
    { terminator_clear (TERM_RETURN); }
    break;

  case 1070:
/* Line 1792 of yacc.c  */
#line 5669 "parser.y"
    { BEGIN_STATEMENT ("REWRITE", TERM_REWRITE); }
    break;

  case 1071:
/* Line 1792 of yacc.c  */
#line 5672 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		if (cb_use_invalidkey_handler_on_status34 &&
		    current_statement->handler_id == COB_EC_I_O_INVALID_KEY &&
		    (CB_FIELD(cb_ref ((yyvsp[(3) - (7)])))->file->organization != COB_ORG_RELATIVE &&
		     CB_FIELD(cb_ref ((yyvsp[(3) - (7)])))->file->organization != COB_ORG_INDEXED)) {
			current_statement->handler_id = COB_EC_I_O_PERMANENT_ERROR;
		}
		cb_emit_rewrite ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]));
	}
  }
    break;

  case 1072:
/* Line 1792 of yacc.c  */
#line 5686 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1073:
/* Line 1792 of yacc.c  */
#line 5688 "parser.y"
    {
	(yyval) = cb_int1;
  }
    break;

  case 1074:
/* Line 1792 of yacc.c  */
#line 5692 "parser.y"
    {
	(yyval) = cb_int2;
  }
    break;

  case 1075:
/* Line 1792 of yacc.c  */
#line 5698 "parser.y"
    { terminator_warning (TERM_REWRITE); }
    break;

  case 1076:
/* Line 1792 of yacc.c  */
#line 5699 "parser.y"
    { terminator_clear (TERM_REWRITE); }
    break;

  case 1077:
/* Line 1792 of yacc.c  */
#line 5709 "parser.y"
    {
	BEGIN_STATEMENT ("ROLLBACK", 0);
	cb_emit_rollback ();
  }
    break;

  case 1078:
/* Line 1792 of yacc.c  */
#line 5721 "parser.y"
    { BEGIN_STATEMENT ("SEARCH", TERM_SEARCH); }
    break;

  case 1080:
/* Line 1792 of yacc.c  */
#line 5728 "parser.y"
    {
	cb_emit_search ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
  }
    break;

  case 1081:
/* Line 1792 of yacc.c  */
#line 5732 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1082:
/* Line 1792 of yacc.c  */
#line 5736 "parser.y"
    {
	cb_emit_search_all ((yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  }
    break;

  case 1083:
/* Line 1792 of yacc.c  */
#line 5742 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1084:
/* Line 1792 of yacc.c  */
#line 5743 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 1085:
/* Line 1792 of yacc.c  */
#line 5747 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1086:
/* Line 1792 of yacc.c  */
#line 5749 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1087:
/* Line 1792 of yacc.c  */
#line 5753 "parser.y"
    {
	(yyval) = (yyvsp[(4) - (4)]);
  }
    break;

  case 1088:
/* Line 1792 of yacc.c  */
#line 5759 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1089:
/* Line 1792 of yacc.c  */
#line 5760 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); CB_IF ((yyvsp[(1) - (2)]))->stmt2 = (yyvsp[(2) - (2)]); }
    break;

  case 1090:
/* Line 1792 of yacc.c  */
#line 5765 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1091:
/* Line 1792 of yacc.c  */
#line 5769 "parser.y"
    {
	(yyval) = cb_build_if ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), NULL);
  }
    break;

  case 1092:
/* Line 1792 of yacc.c  */
#line 5775 "parser.y"
    { terminator_warning (TERM_SEARCH); }
    break;

  case 1093:
/* Line 1792 of yacc.c  */
#line 5776 "parser.y"
    { terminator_clear (TERM_SEARCH); }
    break;

  case 1094:
/* Line 1792 of yacc.c  */
#line 5785 "parser.y"
    { BEGIN_STATEMENT ("SET", 0); }
    break;

  case 1101:
/* Line 1792 of yacc.c  */
#line 5801 "parser.y"
    {
	cb_emit_setenv ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  }
    break;

  case 1102:
/* Line 1792 of yacc.c  */
#line 5810 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (4)]), cb_build_ppointer ((yyvsp[(4) - (4)])));
  }
    break;

  case 1103:
/* Line 1792 of yacc.c  */
#line 5814 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 1104:
/* Line 1792 of yacc.c  */
#line 5823 "parser.y"
    {
	cb_emit_set_up_down ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  }
    break;

  case 1105:
/* Line 1792 of yacc.c  */
#line 5829 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 1106:
/* Line 1792 of yacc.c  */
#line 5830 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1109:
/* Line 1792 of yacc.c  */
#line 5842 "parser.y"
    {
	cb_emit_set_on_off ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 1112:
/* Line 1792 of yacc.c  */
#line 5856 "parser.y"
    {
	cb_emit_set_true ((yyvsp[(1) - (3)]));
  }
    break;

  case 1113:
/* Line 1792 of yacc.c  */
#line 5860 "parser.y"
    {
	cb_emit_set_false ((yyvsp[(1) - (3)]));
  }
    break;

  case 1114:
/* Line 1792 of yacc.c  */
#line 5871 "parser.y"
    { BEGIN_STATEMENT ("SORT", 0); }
    break;

  case 1116:
/* Line 1792 of yacc.c  */
#line 5877 "parser.y"
    {
	cb_emit_sort_init ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (4)]))) && (yyvsp[(2) - (4)]) == NULL) {
		cb_error (_("File sort requires KEY phrase"));
	}
	/* used in sort_input/sort_output */
	save_tree_1 = (yyvsp[(1) - (4)]);
  }
    break;

  case 1117:
/* Line 1792 of yacc.c  */
#line 5886 "parser.y"
    {
	cb_emit_sort_finish ((yyvsp[(1) - (7)]));
  }
    break;

  case 1118:
/* Line 1792 of yacc.c  */
#line 5893 "parser.y"
    {
	(yyval) = NULL;
  }
    break;

  case 1119:
/* Line 1792 of yacc.c  */
#line 5898 "parser.y"
    {
	cb_tree l;

	if (!cb_allow_is_in_sort_key_spec && (yyvsp[(5) - (6)]) != NULL) {
		cb_error (_("syntax error"));
		(yyval) = cb_error_node;
	} else {
		if ((yyvsp[(6) - (6)]) == NULL) {
			(yyvsp[(6) - (6)]) = cb_list_init (NULL);
		}
		for (l = (yyvsp[(6) - (6)]); l; l = CB_CHAIN (l)) {
			CB_PURPOSE (l) = (yyvsp[(3) - (6)]);
		}
		(yyval) = cb_list_append ((yyvsp[(1) - (6)]), (yyvsp[(6) - (6)]));
	}
  }
    break;

  case 1120:
/* Line 1792 of yacc.c  */
#line 5917 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1121:
/* Line 1792 of yacc.c  */
#line 5918 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1123:
/* Line 1792 of yacc.c  */
#line 5922 "parser.y"
    { /* nothing */ }
    break;

  case 1124:
/* Line 1792 of yacc.c  */
#line 5926 "parser.y"
    { (yyval) = cb_null; }
    break;

  case 1125:
/* Line 1792 of yacc.c  */
#line 5927 "parser.y"
    { (yyval) = cb_ref ((yyvsp[(3) - (3)])); }
    break;

  case 1126:
/* Line 1792 of yacc.c  */
#line 5932 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires USING or INPUT PROCEDURE"));
	}
  }
    break;

  case 1127:
/* Line 1792 of yacc.c  */
#line 5938 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("USING invalid with table SORT"));
	} else {
		cb_emit_sort_using (save_tree_1, (yyvsp[(2) - (2)]));
	}
  }
    break;

  case 1128:
/* Line 1792 of yacc.c  */
#line 5946 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("INPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_input ((yyvsp[(4) - (4)]), save_tree_1);
	}
  }
    break;

  case 1129:
/* Line 1792 of yacc.c  */
#line 5957 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires GIVING or OUTPUT PROCEDURE"));
	}
  }
    break;

  case 1130:
/* Line 1792 of yacc.c  */
#line 5963 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("GIVING invalid with table SORT"));
	} else {
		cb_emit_sort_giving (save_tree_1, (yyvsp[(2) - (2)]));
	}
  }
    break;

  case 1131:
/* Line 1792 of yacc.c  */
#line 5971 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("OUTPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_output ((yyvsp[(4) - (4)]), save_tree_1);
	}
  }
    break;

  case 1132:
/* Line 1792 of yacc.c  */
#line 5986 "parser.y"
    { BEGIN_STATEMENT ("START", TERM_START); }
    break;

  case 1133:
/* Line 1792 of yacc.c  */
#line 5987 "parser.y"
    { (yyval) = cb_int (COB_EQ); }
    break;

  case 1134:
/* Line 1792 of yacc.c  */
#line 5990 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(3) - (7)])))) {
		if (CB_FILE (cb_ref ((yyvsp[(3) - (7)])))->organization != COB_ORG_INDEXED &&
		     CB_FILE (cb_ref ((yyvsp[(3) - (7)])))->organization != COB_ORG_RELATIVE) {
			cb_error (_("START not allowed on SEQUENTIAL files"));
			(yyval) = cb_error_node;
		} else {
			cb_emit_start ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]));
		}
	} else {
		cb_error_x ((yyvsp[(3) - (7)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(3) - (7)])));
		(yyval) = cb_error_node;
	}
  }
    break;

  case 1135:
/* Line 1792 of yacc.c  */
#line 6007 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1136:
/* Line 1792 of yacc.c  */
#line 6009 "parser.y"
    {
	(yyvsp[(0) - (4)]) = (yyvsp[(3) - (4)]);
#if	defined(WITH_CISAM) || defined(WITH_DISAM) || defined(WITH_VBISAM) || defined(WITH_INDEX_EXTFH)
	(yyval) = (yyvsp[(4) - (4)]);
#else
	if (CB_LIST((yyvsp[(4) - (4)]))->chain) {
		PENDING ("SPLIT KEYS");
	} else {
		(yyval) = (yyvsp[(4) - (4)]);
 	}
#endif
  }
    break;

  case 1137:
/* Line 1792 of yacc.c  */
#line 6024 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_NE : COB_EQ); }
    break;

  case 1138:
/* Line 1792 of yacc.c  */
#line 6025 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LE : COB_GT); }
    break;

  case 1139:
/* Line 1792 of yacc.c  */
#line 6026 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GE : COB_LT); }
    break;

  case 1140:
/* Line 1792 of yacc.c  */
#line 6027 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LT : COB_GE); }
    break;

  case 1141:
/* Line 1792 of yacc.c  */
#line 6028 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GT : COB_LE); }
    break;

  case 1142:
/* Line 1792 of yacc.c  */
#line 6032 "parser.y"
    { terminator_warning (TERM_START); }
    break;

  case 1143:
/* Line 1792 of yacc.c  */
#line 6033 "parser.y"
    { terminator_clear (TERM_START); }
    break;

  case 1144:
/* Line 1792 of yacc.c  */
#line 6042 "parser.y"
    { BEGIN_STATEMENT ("STOP", 0); }
    break;

  case 1145:
/* Line 1792 of yacc.c  */
#line 6044 "parser.y"
    {
	cb_emit_stop_run ((yyvsp[(4) - (4)]));
  }
    break;

  case 1146:
/* Line 1792 of yacc.c  */
#line 6047 "parser.y"
    { BEGIN_STATEMENT ("STOP", 0); }
    break;

  case 1147:
/* Line 1792 of yacc.c  */
#line 6048 "parser.y"
    {
	cb_verify (cb_stop_literal_statement, "STOP literal");
  }
    break;

  case 1148:
/* Line 1792 of yacc.c  */
#line 6054 "parser.y"
    { (yyval) = current_program->cb_return_code; }
    break;

  case 1149:
/* Line 1792 of yacc.c  */
#line 6055 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 1150:
/* Line 1792 of yacc.c  */
#line 6056 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 1151:
/* Line 1792 of yacc.c  */
#line 6065 "parser.y"
    { BEGIN_STATEMENT ("STRING", TERM_STRING); }
    break;

  case 1152:
/* Line 1792 of yacc.c  */
#line 6068 "parser.y"
    {
	cb_emit_string ((yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]));
  }
    break;

  case 1153:
/* Line 1792 of yacc.c  */
#line 6074 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 1154:
/* Line 1792 of yacc.c  */
#line 6075 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1155:
/* Line 1792 of yacc.c  */
#line 6079 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1156:
/* Line 1792 of yacc.c  */
#line 6080 "parser.y"
    { (yyval) = cb_build_pair (cb_int0, NULL); }
    break;

  case 1157:
/* Line 1792 of yacc.c  */
#line 6081 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), NULL); }
    break;

  case 1158:
/* Line 1792 of yacc.c  */
#line 6085 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 1159:
/* Line 1792 of yacc.c  */
#line 6086 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 1160:
/* Line 1792 of yacc.c  */
#line 6090 "parser.y"
    { terminator_warning (TERM_STRING); }
    break;

  case 1161:
/* Line 1792 of yacc.c  */
#line 6091 "parser.y"
    { terminator_clear (TERM_STRING); }
    break;

  case 1162:
/* Line 1792 of yacc.c  */
#line 6100 "parser.y"
    { BEGIN_STATEMENT ("SUBTRACT", TERM_SUBTRACT); }
    break;

  case 1164:
/* Line 1792 of yacc.c  */
#line 6107 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '-', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  }
    break;

  case 1165:
/* Line 1792 of yacc.c  */
#line 6111 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_list (cb_cons ((yyvsp[(3) - (6)]), (yyvsp[(1) - (6)])), '-'));
  }
    break;

  case 1166:
/* Line 1792 of yacc.c  */
#line 6115 "parser.y"
    {
	cb_emit_corresponding (cb_build_sub, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  }
    break;

  case 1167:
/* Line 1792 of yacc.c  */
#line 6121 "parser.y"
    { terminator_warning (TERM_SUBTRACT); }
    break;

  case 1168:
/* Line 1792 of yacc.c  */
#line 6122 "parser.y"
    { terminator_clear (TERM_SUBTRACT); }
    break;

  case 1169:
/* Line 1792 of yacc.c  */
#line 6132 "parser.y"
    {
	BEGIN_STATEMENT ("SUPPRESS", 0);
	PENDING("SUPPRESS");
  }
    break;

  case 1172:
/* Line 1792 of yacc.c  */
#line 6147 "parser.y"
    { BEGIN_STATEMENT ("TERMINATE", 0); }
    break;

  case 1173:
/* Line 1792 of yacc.c  */
#line 6149 "parser.y"
    {
	PENDING("TERMINATE");
  }
    break;

  case 1174:
/* Line 1792 of yacc.c  */
#line 6160 "parser.y"
    { BEGIN_STATEMENT ("TRANSFORM", 0); }
    break;

  case 1175:
/* Line 1792 of yacc.c  */
#line 6162 "parser.y"
    {
	cb_tree		x;

	x = cb_build_converting ((yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]), cb_build_inspect_region_start ());
	cb_emit_inspect ((yyvsp[(3) - (7)]), x, cb_int0, 2);
  }
    break;

  case 1176:
/* Line 1792 of yacc.c  */
#line 6176 "parser.y"
    { BEGIN_STATEMENT ("UNLOCK", 0); }
    break;

  case 1177:
/* Line 1792 of yacc.c  */
#line 6178 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_unlock ((yyvsp[(3) - (4)]));
	}
  }
    break;

  case 1181:
/* Line 1792 of yacc.c  */
#line 6197 "parser.y"
    { BEGIN_STATEMENT ("UNSTRING", TERM_UNSTRING); }
    break;

  case 1182:
/* Line 1792 of yacc.c  */
#line 6201 "parser.y"
    {
	cb_emit_unstring ((yyvsp[(3) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]));
  }
    break;

  case 1183:
/* Line 1792 of yacc.c  */
#line 6207 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1184:
/* Line 1792 of yacc.c  */
#line 6209 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 1185:
/* Line 1792 of yacc.c  */
#line 6213 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 1186:
/* Line 1792 of yacc.c  */
#line 6215 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 1187:
/* Line 1792 of yacc.c  */
#line 6220 "parser.y"
    {
	(yyval) = cb_build_unstring_delimited ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
  }
    break;

  case 1188:
/* Line 1792 of yacc.c  */
#line 6226 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); }
    break;

  case 1189:
/* Line 1792 of yacc.c  */
#line 6228 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1190:
/* Line 1792 of yacc.c  */
#line 6233 "parser.y"
    {
	(yyval) = cb_build_unstring_into ((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 1191:
/* Line 1792 of yacc.c  */
#line 6239 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1192:
/* Line 1792 of yacc.c  */
#line 6240 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 1193:
/* Line 1792 of yacc.c  */
#line 6244 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1194:
/* Line 1792 of yacc.c  */
#line 6245 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 1195:
/* Line 1792 of yacc.c  */
#line 6249 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1196:
/* Line 1792 of yacc.c  */
#line 6250 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 1197:
/* Line 1792 of yacc.c  */
#line 6254 "parser.y"
    { terminator_warning (TERM_UNSTRING); }
    break;

  case 1198:
/* Line 1792 of yacc.c  */
#line 6255 "parser.y"
    { terminator_clear (TERM_UNSTRING); }
    break;

  case 1202:
/* Line 1792 of yacc.c  */
#line 6273 "parser.y"
    {
	if (!in_declaratives) {
		cb_error (_("USE statement must be within DECLARATIVES"));
	} else if (!current_section) {
		cb_error (_("SECTION header missing before USE statement"));
	} else {
		current_section->need_begin = 1;
		current_section->need_return = 1;
		CB_EXCEPTION_ENABLE (COB_EC_I_O) = 1;
		if (use_global_ind) {
			current_section->is_global = 1;
			current_program->global_list =
				cb_list_add (current_program->global_list,
					     CB_TREE (current_section));
		}
	}
  }
    break;

  case 1203:
/* Line 1792 of yacc.c  */
#line 6294 "parser.y"
    {
	use_global_ind = 0;
  }
    break;

  case 1204:
/* Line 1792 of yacc.c  */
#line 6298 "parser.y"
    {
	use_global_ind = 1;
	current_program->flag_global_use = 1;
  }
    break;

  case 1205:
/* Line 1792 of yacc.c  */
#line 6306 "parser.y"
    {
	cb_tree		l;

	for (l = (yyvsp[(1) - (1)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			setup_use_file (CB_FILE (cb_ref (CB_VALUE (l))));
		}
	}
  }
    break;

  case 1206:
/* Line 1792 of yacc.c  */
#line 6316 "parser.y"
    {
	current_program->global_handler[COB_OPEN_INPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_INPUT].handler_prog = current_program;
  }
    break;

  case 1207:
/* Line 1792 of yacc.c  */
#line 6321 "parser.y"
    {
	current_program->global_handler[COB_OPEN_OUTPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_OUTPUT].handler_prog = current_program;
  }
    break;

  case 1208:
/* Line 1792 of yacc.c  */
#line 6326 "parser.y"
    {
	current_program->global_handler[COB_OPEN_I_O].handler_label = current_section;
	current_program->global_handler[COB_OPEN_I_O].handler_prog = current_program;
  }
    break;

  case 1209:
/* Line 1792 of yacc.c  */
#line 6331 "parser.y"
    {
	current_program->global_handler[COB_OPEN_EXTEND].handler_label = current_section;
	current_program->global_handler[COB_OPEN_EXTEND].handler_prog = current_program;
  }
    break;

  case 1222:
/* Line 1792 of yacc.c  */
#line 6363 "parser.y"
    {
	PENDING ("USE FOR DEBUGGING");
  }
    break;

  case 1225:
/* Line 1792 of yacc.c  */
#line 6375 "parser.y"
    {
	PENDING ("USE BEFORE REPORTING");
  }
    break;

  case 1226:
/* Line 1792 of yacc.c  */
#line 6386 "parser.y"
    { BEGIN_STATEMENT ("WRITE", TERM_WRITE); }
    break;

  case 1227:
/* Line 1792 of yacc.c  */
#line 6389 "parser.y"
    {
	if ((yyvsp[(3) - (8)]) != cb_error_node) {
		if (cb_use_invalidkey_handler_on_status34 &&
		    current_statement->handler_id == COB_EC_I_O_INVALID_KEY &&
		    (CB_FIELD(cb_ref ((yyvsp[(3) - (8)])))->file->organization != COB_ORG_RELATIVE &&
		     CB_FIELD(cb_ref ((yyvsp[(3) - (8)])))->file->organization != COB_ORG_INDEXED)) {
			current_statement->handler_id = COB_EC_I_O_PERMANENT_ERROR;
		}
		cb_emit_write ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(5) - (8)]));
	}
  }
    break;

  case 1228:
/* Line 1792 of yacc.c  */
#line 6403 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1229:
/* Line 1792 of yacc.c  */
#line 6404 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 1230:
/* Line 1792 of yacc.c  */
#line 6409 "parser.y"
    {
	(yyval) = cb_int0;
  }
    break;

  case 1231:
/* Line 1792 of yacc.c  */
#line 6413 "parser.y"
    {
	(yyval) = cb_build_write_advancing_lines ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  }
    break;

  case 1232:
/* Line 1792 of yacc.c  */
#line 6417 "parser.y"
    {
	(yyval) = cb_build_write_advancing_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 1233:
/* Line 1792 of yacc.c  */
#line 6421 "parser.y"
    {
	(yyval) = cb_build_write_advancing_page ((yyvsp[(1) - (3)]));
  }
    break;

  case 1234:
/* Line 1792 of yacc.c  */
#line 6427 "parser.y"
    { (yyval) = CB_BEFORE; }
    break;

  case 1235:
/* Line 1792 of yacc.c  */
#line 6428 "parser.y"
    { (yyval) = CB_AFTER; }
    break;

  case 1239:
/* Line 1792 of yacc.c  */
#line 6437 "parser.y"
    { terminator_warning (TERM_WRITE); }
    break;

  case 1240:
/* Line 1792 of yacc.c  */
#line 6438 "parser.y"
    { terminator_clear (TERM_WRITE); }
    break;

  case 1241:
/* Line 1792 of yacc.c  */
#line 6453 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_ACCEPT;
  }
    break;

  case 1242:
/* Line 1792 of yacc.c  */
#line 6461 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_DISPLAY;
  }
    break;

  case 1244:
/* Line 1792 of yacc.c  */
#line 6468 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1245:
/* Line 1792 of yacc.c  */
#line 6472 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  }
    break;

  case 1247:
/* Line 1792 of yacc.c  */
#line 6479 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1248:
/* Line 1792 of yacc.c  */
#line 6483 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  }
    break;

  case 1251:
/* Line 1792 of yacc.c  */
#line 6499 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  }
    break;

  case 1252:
/* Line 1792 of yacc.c  */
#line 6504 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  }
    break;

  case 1254:
/* Line 1792 of yacc.c  */
#line 6511 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  }
    break;

  case 1255:
/* Line 1792 of yacc.c  */
#line 6516 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  }
    break;

  case 1256:
/* Line 1792 of yacc.c  */
#line 6528 "parser.y"
    {
	current_statement->handler_id = COB_EC_OVERFLOW;
  }
    break;

  case 1258:
/* Line 1792 of yacc.c  */
#line 6535 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1259:
/* Line 1792 of yacc.c  */
#line 6539 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  }
    break;

  case 1261:
/* Line 1792 of yacc.c  */
#line 6546 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1262:
/* Line 1792 of yacc.c  */
#line 6550 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  }
    break;

  case 1263:
/* Line 1792 of yacc.c  */
#line 6562 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  }
    break;

  case 1264:
/* Line 1792 of yacc.c  */
#line 6567 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  }
    break;

  case 1265:
/* Line 1792 of yacc.c  */
#line 6572 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  }
    break;

  case 1266:
/* Line 1792 of yacc.c  */
#line 6581 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1267:
/* Line 1792 of yacc.c  */
#line 6585 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 1268:
/* Line 1792 of yacc.c  */
#line 6592 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1269:
/* Line 1792 of yacc.c  */
#line 6596 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 1270:
/* Line 1792 of yacc.c  */
#line 6608 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  }
    break;

  case 1271:
/* Line 1792 of yacc.c  */
#line 6613 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  }
    break;

  case 1272:
/* Line 1792 of yacc.c  */
#line 6618 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  }
    break;

  case 1273:
/* Line 1792 of yacc.c  */
#line 6627 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1274:
/* Line 1792 of yacc.c  */
#line 6631 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 1275:
/* Line 1792 of yacc.c  */
#line 6638 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1276:
/* Line 1792 of yacc.c  */
#line 6642 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 1279:
/* Line 1792 of yacc.c  */
#line 6658 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  }
    break;

  case 1280:
/* Line 1792 of yacc.c  */
#line 6663 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  }
    break;

  case 1281:
/* Line 1792 of yacc.c  */
#line 6668 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  }
    break;

  case 1282:
/* Line 1792 of yacc.c  */
#line 6677 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1283:
/* Line 1792 of yacc.c  */
#line 6681 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 1284:
/* Line 1792 of yacc.c  */
#line 6688 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1285:
/* Line 1792 of yacc.c  */
#line 6692 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 1286:
/* Line 1792 of yacc.c  */
#line 6704 "parser.y"
    {
	(yyval) = cb_one;
  }
    break;

  case 1287:
/* Line 1792 of yacc.c  */
#line 6708 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (3)]);
  }
    break;

  case 1288:
/* Line 1792 of yacc.c  */
#line 6720 "parser.y"
    {
	(yyval) = cb_build_cond ((yyvsp[(1) - (1)]));
  }
    break;

  case 1289:
/* Line 1792 of yacc.c  */
#line 6727 "parser.y"
    {
	(yyval) = cb_build_expr ((yyvsp[(1) - (1)]));
  }
    break;

  case 1290:
/* Line 1792 of yacc.c  */
#line 6733 "parser.y"
    {
	current_expr = NULL;
  }
    break;

  case 1291:
/* Line 1792 of yacc.c  */
#line 6737 "parser.y"
    {
	(yyval) = cb_list_reverse (current_expr);
  }
    break;

  case 1292:
/* Line 1792 of yacc.c  */
#line 6743 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); }
    break;

  case 1293:
/* Line 1792 of yacc.c  */
#line 6744 "parser.y"
    { push_expr (')', NULL); }
    break;

  case 1294:
/* Line 1792 of yacc.c  */
#line 6746 "parser.y"
    { push_expr ('O', NULL); }
    break;

  case 1295:
/* Line 1792 of yacc.c  */
#line 6747 "parser.y"
    { push_expr ('9', NULL); }
    break;

  case 1296:
/* Line 1792 of yacc.c  */
#line 6748 "parser.y"
    { push_expr ('A', NULL); }
    break;

  case 1297:
/* Line 1792 of yacc.c  */
#line 6749 "parser.y"
    { push_expr ('L', NULL); }
    break;

  case 1298:
/* Line 1792 of yacc.c  */
#line 6750 "parser.y"
    { push_expr ('U', NULL); }
    break;

  case 1299:
/* Line 1792 of yacc.c  */
#line 6751 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); }
    break;

  case 1300:
/* Line 1792 of yacc.c  */
#line 6753 "parser.y"
    { push_expr ('O', NULL); }
    break;

  case 1301:
/* Line 1792 of yacc.c  */
#line 6754 "parser.y"
    { push_expr ('9', NULL); }
    break;

  case 1302:
/* Line 1792 of yacc.c  */
#line 6755 "parser.y"
    { push_expr ('A', NULL); }
    break;

  case 1303:
/* Line 1792 of yacc.c  */
#line 6756 "parser.y"
    { push_expr ('L', NULL); }
    break;

  case 1304:
/* Line 1792 of yacc.c  */
#line 6757 "parser.y"
    { push_expr ('U', NULL); }
    break;

  case 1305:
/* Line 1792 of yacc.c  */
#line 6758 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); }
    break;

  case 1306:
/* Line 1792 of yacc.c  */
#line 6760 "parser.y"
    { push_expr ('P', NULL); }
    break;

  case 1307:
/* Line 1792 of yacc.c  */
#line 6761 "parser.y"
    { push_expr ('N', NULL); }
    break;

  case 1308:
/* Line 1792 of yacc.c  */
#line 6763 "parser.y"
    { push_expr ('P', NULL); }
    break;

  case 1309:
/* Line 1792 of yacc.c  */
#line 6764 "parser.y"
    { push_expr ('N', NULL); }
    break;

  case 1310:
/* Line 1792 of yacc.c  */
#line 6765 "parser.y"
    { push_expr ('x', cb_zero); }
    break;

  case 1314:
/* Line 1792 of yacc.c  */
#line 6772 "parser.y"
    { push_expr ('(', NULL); }
    break;

  case 1315:
/* Line 1792 of yacc.c  */
#line 6774 "parser.y"
    { push_expr ('+', NULL); }
    break;

  case 1316:
/* Line 1792 of yacc.c  */
#line 6775 "parser.y"
    { push_expr ('-', NULL); }
    break;

  case 1317:
/* Line 1792 of yacc.c  */
#line 6776 "parser.y"
    { push_expr ('^', NULL); }
    break;

  case 1318:
/* Line 1792 of yacc.c  */
#line 6778 "parser.y"
    { push_expr ('!', NULL); }
    break;

  case 1319:
/* Line 1792 of yacc.c  */
#line 6779 "parser.y"
    { push_expr ('!', NULL); }
    break;

  case 1320:
/* Line 1792 of yacc.c  */
#line 6781 "parser.y"
    { push_expr ('+', NULL); }
    break;

  case 1321:
/* Line 1792 of yacc.c  */
#line 6782 "parser.y"
    { push_expr ('-', NULL); }
    break;

  case 1322:
/* Line 1792 of yacc.c  */
#line 6783 "parser.y"
    { push_expr ('*', NULL); }
    break;

  case 1323:
/* Line 1792 of yacc.c  */
#line 6784 "parser.y"
    { push_expr ('/', NULL); }
    break;

  case 1324:
/* Line 1792 of yacc.c  */
#line 6785 "parser.y"
    { push_expr ('^', NULL); }
    break;

  case 1325:
/* Line 1792 of yacc.c  */
#line 6787 "parser.y"
    { push_expr ('=', NULL); }
    break;

  case 1326:
/* Line 1792 of yacc.c  */
#line 6788 "parser.y"
    { push_expr ('>', NULL); }
    break;

  case 1327:
/* Line 1792 of yacc.c  */
#line 6789 "parser.y"
    { push_expr ('<', NULL); }
    break;

  case 1328:
/* Line 1792 of yacc.c  */
#line 6790 "parser.y"
    { push_expr (']', NULL); }
    break;

  case 1329:
/* Line 1792 of yacc.c  */
#line 6791 "parser.y"
    { push_expr ('[', NULL); }
    break;

  case 1330:
/* Line 1792 of yacc.c  */
#line 6792 "parser.y"
    { push_expr ('~', NULL); }
    break;

  case 1331:
/* Line 1792 of yacc.c  */
#line 6794 "parser.y"
    { push_expr ('=', NULL); }
    break;

  case 1332:
/* Line 1792 of yacc.c  */
#line 6795 "parser.y"
    { push_expr ('>', NULL); }
    break;

  case 1333:
/* Line 1792 of yacc.c  */
#line 6796 "parser.y"
    { push_expr ('<', NULL); }
    break;

  case 1334:
/* Line 1792 of yacc.c  */
#line 6797 "parser.y"
    { push_expr (']', NULL); }
    break;

  case 1335:
/* Line 1792 of yacc.c  */
#line 6798 "parser.y"
    { push_expr ('[', NULL); }
    break;

  case 1336:
/* Line 1792 of yacc.c  */
#line 6799 "parser.y"
    { push_expr ('~', NULL); }
    break;

  case 1337:
/* Line 1792 of yacc.c  */
#line 6801 "parser.y"
    { push_expr ('&', NULL); }
    break;

  case 1338:
/* Line 1792 of yacc.c  */
#line 6802 "parser.y"
    { push_expr ('|', NULL); }
    break;

  case 1352:
/* Line 1792 of yacc.c  */
#line 6814 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 1353:
/* Line 1792 of yacc.c  */
#line 6815 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 1357:
/* Line 1792 of yacc.c  */
#line 6824 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1358:
/* Line 1792 of yacc.c  */
#line 6825 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '+', (yyvsp[(3) - (3)])); }
    break;

  case 1359:
/* Line 1792 of yacc.c  */
#line 6826 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '-', (yyvsp[(3) - (3)])); }
    break;

  case 1360:
/* Line 1792 of yacc.c  */
#line 6827 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '*', (yyvsp[(3) - (3)])); }
    break;

  case 1361:
/* Line 1792 of yacc.c  */
#line 6828 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '/', (yyvsp[(3) - (3)])); }
    break;

  case 1362:
/* Line 1792 of yacc.c  */
#line 6829 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 1363:
/* Line 1792 of yacc.c  */
#line 6830 "parser.y"
    { (yyval) = cb_build_binary_op (cb_zero, '-', (yyvsp[(2) - (2)])); }
    break;

  case 1364:
/* Line 1792 of yacc.c  */
#line 6831 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '^', (yyvsp[(3) - (3)])); }
    break;

  case 1365:
/* Line 1792 of yacc.c  */
#line 6832 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 1366:
/* Line 1792 of yacc.c  */
#line 6844 "parser.y"
    {
	if (current_linage > 1) {
		cb_error (_("LINAGE-COUNTER must be qualified here"));
		(yyval) = cb_error_node;
	} else if (current_linage == 0) {
		cb_error (_("Invalid LINAGE-COUNTER usage"));
		(yyval) = cb_error_node;
	} else {
		(yyval) = linage_file->linage_ctr;
	}
  }
    break;

  case 1367:
/* Line 1792 of yacc.c  */
#line 6856 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(3) - (3)])))) {
		(yyval) = CB_FILE (cb_ref ((yyvsp[(3) - (3)])))->linage_ctr;
	} else {
		cb_error_x ((yyvsp[(3) - (3)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(3) - (3)])));
		(yyval) = cb_error_node;
	}
  }
    break;

  case 1368:
/* Line 1792 of yacc.c  */
#line 6870 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1369:
/* Line 1792 of yacc.c  */
#line 6872 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1370:
/* Line 1792 of yacc.c  */
#line 6876 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)])); }
    break;

  case 1371:
/* Line 1792 of yacc.c  */
#line 6883 "parser.y"
    {
	cb_tree x;
	cb_tree r;

	if ((x = cb_build_identifier ((yyvsp[(1) - (1)]))) != cb_error_node &&
	    (r = cb_ref (x)) != cb_error_node) {
		if (!CB_FIELD_P(r)) {
			cb_error_x (x, _("Field name expected."));
			x = cb_error_node;
		} else if (!CB_FIELD(r)->file) {
			cb_error_x (x, _("Record name expected."));
			x = cb_error_node;
		}
	}
	(yyval) = x;
  }
    break;

  case 1372:
/* Line 1792 of yacc.c  */
#line 6905 "parser.y"
    {
	cb_tree x;

	x = cb_ref ((yyvsp[(1) - (1)]));
	if (!CB_FIELD_P (x)) {
		(yyval) = cb_error_node;
	} else if (!CB_FIELD (x)->index_list) {
		cb_error_x ((yyvsp[(1) - (1)]), _("'%s' not indexed"), cb_name ((yyvsp[(1) - (1)])));
		cb_error_x (x, _("'%s' defined here"), cb_name (x));
		(yyval) = cb_error_node;
	} else {
		(yyval) = (yyvsp[(1) - (1)]);
	}
  }
    break;

  case 1373:
/* Line 1792 of yacc.c  */
#line 6925 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (1)]));
  }
    break;

  case 1374:
/* Line 1792 of yacc.c  */
#line 6929 "parser.y"
    {
	cb_tree		l;

	if ((yyvsp[(2) - (2)]) != cb_error_node) {
		for (l = (yyvsp[(1) - (2)]); l; l = CB_CHAIN (l)) {
			if (!strcasecmp (CB_NAME ((yyvsp[(2) - (2)])), CB_NAME (CB_VALUE (l)))) {
				cb_error_x ((yyvsp[(2) - (2)]), _("Multiple reference to '%s' "), CB_NAME ((yyvsp[(2) - (2)])));
			}
		}
		(yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
	}
  }
    break;

  case 1375:
/* Line 1792 of yacc.c  */
#line 6945 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (1)])))) {
		(yyval) = (yyvsp[(1) - (1)]);
	} else {
		cb_error_x ((yyvsp[(1) - (1)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(1) - (1)])));
		(yyval) = cb_error_node;
	}
  }
    break;

  case 1376:
/* Line 1792 of yacc.c  */
#line 6958 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 1377:
/* Line 1792 of yacc.c  */
#line 6960 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1378:
/* Line 1792 of yacc.c  */
#line 6964 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1379:
/* Line 1792 of yacc.c  */
#line 6970 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1380:
/* Line 1792 of yacc.c  */
#line 6972 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1381:
/* Line 1792 of yacc.c  */
#line 6977 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	CB_REFERENCE ((yyval))->offset = CB_TREE (current_section);
	current_program->label_list = cb_cons ((yyval), current_program->label_list);
  }
    break;

  case 1385:
/* Line 1792 of yacc.c  */
#line 6992 "parser.y"
    {
	(yyval) = cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(1) - (1)]))->data));
	(yyval)->source_file = (yyvsp[(1) - (1)])->source_file;
	(yyval)->source_line = (yyvsp[(1) - (1)])->source_line;
  }
    break;

  case 1386:
/* Line 1792 of yacc.c  */
#line 7002 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 1387:
/* Line 1792 of yacc.c  */
#line 7003 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1388:
/* Line 1792 of yacc.c  */
#line 7008 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	current_program->reference_list = cb_cons ((yyval), current_program->reference_list);
  }
    break;

  case 1389:
/* Line 1792 of yacc.c  */
#line 7017 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 1390:
/* Line 1792 of yacc.c  */
#line 7018 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1391:
/* Line 1792 of yacc.c  */
#line 7022 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1392:
/* Line 1792 of yacc.c  */
#line 7023 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1395:
/* Line 1792 of yacc.c  */
#line 7035 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE ((yyval))->word->count > 0) {
		redefinition_error ((yyval));
		(yyval) = cb_error_node;
	}
  }
    break;

  case 1396:
/* Line 1792 of yacc.c  */
#line 7054 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 1397:
/* Line 1792 of yacc.c  */
#line 7055 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1399:
/* Line 1792 of yacc.c  */
#line 7060 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); }
    break;

  case 1400:
/* Line 1792 of yacc.c  */
#line 7064 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 1401:
/* Line 1792 of yacc.c  */
#line 7065 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1403:
/* Line 1792 of yacc.c  */
#line 7070 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); }
    break;

  case 1404:
/* Line 1792 of yacc.c  */
#line 7071 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); }
    break;

  case 1405:
/* Line 1792 of yacc.c  */
#line 7072 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); }
    break;

  case 1406:
/* Line 1792 of yacc.c  */
#line 7073 "parser.y"
    { (yyval) = cb_build_ppointer ((yyvsp[(4) - (4)])); }
    break;

  case 1407:
/* Line 1792 of yacc.c  */
#line 7074 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); }
    break;

  case 1412:
/* Line 1792 of yacc.c  */
#line 7082 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); }
    break;

  case 1413:
/* Line 1792 of yacc.c  */
#line 7083 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); }
    break;

  case 1414:
/* Line 1792 of yacc.c  */
#line 7084 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); }
    break;

  case 1420:
/* Line 1792 of yacc.c  */
#line 7096 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1421:
/* Line 1792 of yacc.c  */
#line 7097 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1433:
/* Line 1792 of yacc.c  */
#line 7131 "parser.y"
    { (yyval) = cb_zero; }
    break;

  case 1434:
/* Line 1792 of yacc.c  */
#line 7139 "parser.y"
    { (yyval) = cb_build_identifier ((yyvsp[(1) - (1)])); }
    break;

  case 1435:
/* Line 1792 of yacc.c  */
#line 7143 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1436:
/* Line 1792 of yacc.c  */
#line 7144 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); }
    break;

  case 1437:
/* Line 1792 of yacc.c  */
#line 7145 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); }
    break;

  case 1438:
/* Line 1792 of yacc.c  */
#line 7146 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); }
    break;

  case 1439:
/* Line 1792 of yacc.c  */
#line 7150 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1440:
/* Line 1792 of yacc.c  */
#line 7151 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); CB_REFERENCE ((yyvsp[(1) - (3)]))->chain = (yyvsp[(3) - (3)]); }
    break;

  case 1441:
/* Line 1792 of yacc.c  */
#line 7156 "parser.y"
    {
	if (cb_ref ((yyvsp[(0) - (3)])) != cb_error_node) {
		(yyval) = (yyvsp[(0) - (3)]);
		CB_REFERENCE ((yyvsp[(0) - (3)]))->subs = cb_list_reverse ((yyvsp[(2) - (3)]));
	}
  }
    break;

  case 1442:
/* Line 1792 of yacc.c  */
#line 7166 "parser.y"
    {
	if (cb_ref ((yyvsp[(0) - (4)])) != cb_error_node) {
		CB_REFERENCE ((yyvsp[(0) - (4)]))->value = CB_TREE (cb_field ((yyvsp[(0) - (4)])));
		if (cb_tree_category ((yyvsp[(0) - (4)])) == CB_CATEGORY_NATIONAL ||
		    cb_tree_category ((yyvsp[(0) - (4)])) == CB_CATEGORY_NATIONAL_EDITED) {
#ifdef	I18N_UTF8
			/* I18N_UTF8: No wide char support. */
#else /*!I18N_UTF8*/
			(yyvsp[(2) - (4)]) = cb_build_binary_op ((yyvsp[(2) - (4)]), '*', cb_int2);
			(yyvsp[(2) - (4)]) = cb_build_binary_op ((yyvsp[(2) - (4)]), '-', cb_int1);
#endif /*I18N_UTF8*/
		} else {
			CB_TREE ((yyvsp[(0) - (4)]))->category = CB_CATEGORY_ALPHANUMERIC;
		}
		CB_REFERENCE ((yyvsp[(0) - (4)]))->offset = (yyvsp[(2) - (4)]);
	}
  }
    break;

  case 1443:
/* Line 1792 of yacc.c  */
#line 7184 "parser.y"
    {
	if (cb_ref ((yyvsp[(0) - (5)])) != cb_error_node) {
		CB_REFERENCE ((yyvsp[(0) - (5)]))->value = CB_TREE (cb_field ((yyvsp[(0) - (5)])));
		if (cb_tree_category ((yyvsp[(0) - (5)])) == CB_CATEGORY_NATIONAL ||
		    cb_tree_category ((yyvsp[(0) - (5)])) == CB_CATEGORY_NATIONAL_EDITED) {
#ifdef	I18N_UTF8
			/* I18N_UTF8: No wide char support. */
#else /*!I18N_UTF8*/
			(yyvsp[(2) - (5)]) = cb_build_binary_op ((yyvsp[(2) - (5)]), '*', cb_int2);
			(yyvsp[(2) - (5)]) = cb_build_binary_op ((yyvsp[(2) - (5)]), '-', cb_int1);
			(yyvsp[(4) - (5)]) = cb_build_binary_op ((yyvsp[(4) - (5)]), '*', cb_int2);
#endif /*I18N_UTF8*/
		} else {
			CB_TREE ((yyvsp[(0) - (5)]))->category = CB_CATEGORY_ALPHANUMERIC;
		}
		CB_REFERENCE ((yyvsp[(0) - (5)]))->offset = (yyvsp[(2) - (5)]);
		CB_REFERENCE ((yyvsp[(0) - (5)]))->length = (yyvsp[(4) - (5)]);
	}
  }
    break;

  case 1444:
/* Line 1792 of yacc.c  */
#line 7211 "parser.y"
    {
	if (cb_tree_category ((yyvsp[(1) - (1)])) != CB_CATEGORY_NUMERIC) {
		cb_error (_("Integer value expected"));
	} else if (CB_LITERAL ((yyvsp[(1) - (1)]))->sign < 0 || CB_LITERAL ((yyvsp[(1) - (1)]))->scale) {
		cb_error (_("Integer value expected"));
	}
	(yyval) = (yyvsp[(1) - (1)]);
  }
    break;

  case 1445:
/* Line 1792 of yacc.c  */
#line 7222 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1446:
/* Line 1792 of yacc.c  */
#line 7224 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (2)]);
	if (CB_LITERAL_P ((yyvsp[(2) - (2)]))) {
		CB_LITERAL ((yyvsp[(2) - (2)]))->all = 1;
	}
  }
    break;

  case 1447:
/* Line 1792 of yacc.c  */
#line 7233 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1448:
/* Line 1792 of yacc.c  */
#line 7234 "parser.y"
    { (yyval) = cb_concat_literals ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 1449:
/* Line 1792 of yacc.c  */
#line 7238 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1450:
/* Line 1792 of yacc.c  */
#line 7239 "parser.y"
    { (yyval) = cb_space; }
    break;

  case 1451:
/* Line 1792 of yacc.c  */
#line 7240 "parser.y"
    { (yyval) = cb_zero; }
    break;

  case 1452:
/* Line 1792 of yacc.c  */
#line 7241 "parser.y"
    { (yyval) = cb_quote; }
    break;

  case 1453:
/* Line 1792 of yacc.c  */
#line 7242 "parser.y"
    { (yyval) = cb_high; }
    break;

  case 1454:
/* Line 1792 of yacc.c  */
#line 7243 "parser.y"
    { (yyval) = cb_low; }
    break;

  case 1455:
/* Line 1792 of yacc.c  */
#line 7244 "parser.y"
    { (yyval) = cb_null; }
    break;

  case 1456:
/* Line 1792 of yacc.c  */
#line 7253 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  }
    break;

  case 1457:
/* Line 1792 of yacc.c  */
#line 7257 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  }
    break;

  case 1458:
/* Line 1792 of yacc.c  */
#line 7261 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  }
    break;

  case 1459:
/* Line 1792 of yacc.c  */
#line 7265 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  }
    break;

  case 1460:
/* Line 1792 of yacc.c  */
#line 7269 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  }
    break;

  case 1461:
/* Line 1792 of yacc.c  */
#line 7273 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  }
    break;

  case 1462:
/* Line 1792 of yacc.c  */
#line 7277 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  }
    break;

  case 1463:
/* Line 1792 of yacc.c  */
#line 7281 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  }
    break;

  case 1464:
/* Line 1792 of yacc.c  */
#line 7285 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  }
    break;

  case 1465:
/* Line 1792 of yacc.c  */
#line 7289 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), NULL);
  }
    break;

  case 1466:
/* Line 1792 of yacc.c  */
#line 7293 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  }
    break;

  case 1467:
/* Line 1792 of yacc.c  */
#line 7297 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), NULL);
  }
    break;

  case 1468:
/* Line 1792 of yacc.c  */
#line 7303 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1469:
/* Line 1792 of yacc.c  */
#line 7304 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (4)]), NULL); }
    break;

  case 1470:
/* Line 1792 of yacc.c  */
#line 7305 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); }
    break;

  case 1471:
/* Line 1792 of yacc.c  */
#line 7309 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1472:
/* Line 1792 of yacc.c  */
#line 7310 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 1473:
/* Line 1792 of yacc.c  */
#line 7314 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1474:
/* Line 1792 of yacc.c  */
#line 7315 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1475:
/* Line 1792 of yacc.c  */
#line 7321 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_int0);
  }
    break;

  case 1476:
/* Line 1792 of yacc.c  */
#line 7328 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int1);
  }
    break;

  case 1477:
/* Line 1792 of yacc.c  */
#line 7335 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int2);
  }
    break;

  case 1478:
/* Line 1792 of yacc.c  */
#line 7345 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  }
    break;

  case 1479:
/* Line 1792 of yacc.c  */
#line 7352 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, (yyvsp[(3) - (3)]));
  }
    break;

  case 1480:
/* Line 1792 of yacc.c  */
#line 7362 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  }
    break;

  case 1481:
/* Line 1792 of yacc.c  */
#line 7369 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_ref ((yyvsp[(3) - (3)])));
  }
    break;

  case 1482:
/* Line 1792 of yacc.c  */
#line 7382 "parser.y"
    {
	non_const_word = 1;
  }
    break;

  case 1483:
/* Line 1792 of yacc.c  */
#line 7392 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 1484:
/* Line 1792 of yacc.c  */
#line 7393 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1485:
/* Line 1792 of yacc.c  */
#line 7397 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 1486:
/* Line 1792 of yacc.c  */
#line 7398 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1487:
/* Line 1792 of yacc.c  */
#line 7402 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1488:
/* Line 1792 of yacc.c  */
#line 7403 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1489:
/* Line 1792 of yacc.c  */
#line 7407 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 1490:
/* Line 1792 of yacc.c  */
#line 7408 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1491:
/* Line 1792 of yacc.c  */
#line 7409 "parser.y"
    { (yyval) = cb_int2; }
    break;

  case 1492:
/* Line 1792 of yacc.c  */
#line 7413 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 1493:
/* Line 1792 of yacc.c  */
#line 7414 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1494:
/* Line 1792 of yacc.c  */
#line 7418 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 1495:
/* Line 1792 of yacc.c  */
#line 7419 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1496:
/* Line 1792 of yacc.c  */
#line 7423 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 1497:
/* Line 1792 of yacc.c  */
#line 7424 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1498:
/* Line 1792 of yacc.c  */
#line 7428 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 1499:
/* Line 1792 of yacc.c  */
#line 7429 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1511:
/* Line 1792 of yacc.c  */
#line 7442 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1540:
/* Line 1792 of yacc.c  */
#line 7457 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1541:
/* Line 1792 of yacc.c  */
#line 7457 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1552:
/* Line 1792 of yacc.c  */
#line 7462 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1553:
/* Line 1792 of yacc.c  */
#line 7462 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;


/* Line 1792 of yacc.c  */
#line 13899 "parser.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 7487 "parser.y"

