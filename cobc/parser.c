
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
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
BEGIN_IMPLICIT_STATEMENT (void)
{
	current_statement = cb_build_statement (NULL);
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



/* Line 189 of yacc.c  */
#line 356 "parser.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
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
     CODE = 315,
     CODE_SET = 316,
     COLLATING = 317,
     COL = 318,
     COLS = 319,
     COLUMN = 320,
     COLUMNS = 321,
     COMMA = 322,
     COMMAND_LINE = 323,
     COMMA_DELIM = 324,
     COMMIT = 325,
     COMMITMENT_CONTROL = 326,
     COMMON = 327,
     COMP = 328,
     COMPUTE = 329,
     COMP_1 = 330,
     COMP_2 = 331,
     COMP_3 = 332,
     COMP_4 = 333,
     COMP_5 = 334,
     COMP_X = 335,
     CONCATENATE_FUNC = 336,
     CONFIGURATION = 337,
     CONSTANT = 338,
     CONTAINS = 339,
     CONTENT = 340,
     CONTINUE = 341,
     CONTROL = 342,
     CONTROLS = 343,
     CONTROL_FOOTING = 344,
     CONTROL_HEADING = 345,
     CONVERTING = 346,
     CORRESPONDING = 347,
     COUNT = 348,
     CRT = 349,
     CURRENCY = 350,
     CURRENT_DATE_FUNC = 351,
     CURSOR = 352,
     CYCLE = 353,
     DATA = 354,
     DATE = 355,
     DAY = 356,
     DAY_OF_WEEK = 357,
     DE = 358,
     DEBUGGING = 359,
     DECIMAL_POINT = 360,
     DECLARATIVES = 361,
     DEFAULT = 362,
     DELETE = 363,
     DELIMITED = 364,
     DELIMITER = 365,
     DEPENDING = 366,
     DESCENDING = 367,
     DETAIL = 368,
     DISK = 369,
     DISPLAY = 370,
     DIVIDE = 371,
     DIVISION = 372,
     DOWN = 373,
     DUPLICATES = 374,
     DYNAMIC = 375,
     EBCDIC = 376,
     ELSE = 377,
     END = 378,
     END_ACCEPT = 379,
     END_ADD = 380,
     END_CALL = 381,
     END_COMPUTE = 382,
     END_DELETE = 383,
     END_DISPLAY = 384,
     END_DIVIDE = 385,
     END_EVALUATE = 386,
     END_FUNCTION = 387,
     END_IF = 388,
     END_MULTIPLY = 389,
     END_PERFORM = 390,
     END_PROGRAM = 391,
     END_READ = 392,
     END_RETURN = 393,
     END_REWRITE = 394,
     END_SEARCH = 395,
     END_START = 396,
     END_STRING = 397,
     END_SUBTRACT = 398,
     END_UNSTRING = 399,
     END_WRITE = 400,
     ENTRY = 401,
     ENVIRONMENT = 402,
     ENVIRONMENT_NAME = 403,
     ENVIRONMENT_VALUE = 404,
     EOL = 405,
     EOP = 406,
     EOS = 407,
     EQUAL = 408,
     EQUALS = 409,
     ERASE = 410,
     ERROR = 411,
     ESCAPE = 412,
     EVALUATE = 413,
     EVENT_STATUS = 414,
     EXCEPTION = 415,
     EXCLUSIVE = 416,
     EXIT = 417,
     EXTEND = 418,
     EXTERNAL = 419,
     FD = 420,
     FILE_CONTROL = 421,
     FILE_ID = 422,
     FILLER = 423,
     FINAL = 424,
     FIRST = 425,
     FOOTING = 426,
     FOR = 427,
     FOREGROUND_COLOR = 428,
     FOREVER = 429,
     FREE = 430,
     FROM = 431,
     FULL = 432,
     FUNCTION = 433,
     FUNCTION_ID = 434,
     FUNCTION_NAME = 435,
     GE = 436,
     GENERATE = 437,
     GIVING = 438,
     GLOBAL = 439,
     GO = 440,
     GOBACK = 441,
     GREATER = 442,
     GROUP = 443,
     HEADING = 444,
     HIGHLIGHT = 445,
     HIGH_VALUE = 446,
     IDENTIFICATION = 447,
     IF = 448,
     IGNORE = 449,
     IGNORING = 450,
     IN = 451,
     INDEX = 452,
     INDEXED = 453,
     INDICATE = 454,
     INITIALIZE = 455,
     INITIALIZED = 456,
     INITIATE = 457,
     INPUT = 458,
     INPUT_OUTPUT = 459,
     INSPECT = 460,
     INTO = 461,
     INTRINSIC = 462,
     INVALID = 463,
     INVALID_KEY = 464,
     IS = 465,
     I_O = 466,
     I_O_CONTROL = 467,
     JUSTIFIED = 468,
     KEY = 469,
     LABEL = 470,
     LAST = 471,
     LAST_DETAIL = 472,
     LE = 473,
     LEADING = 474,
     LEFT = 475,
     LENGTH = 476,
     LESS = 477,
     LIMIT = 478,
     LIMITS = 479,
     LINAGE = 480,
     LINAGE_COUNTER = 481,
     LINE = 482,
     LINES = 483,
     LINKAGE = 484,
     LITERAL = 485,
     LOCALE = 486,
     LOCALE_DT_FUNC = 487,
     LOCAL_STORAGE = 488,
     LOCK = 489,
     LOWER_CASE_FUNC = 490,
     LOWLIGHT = 491,
     LOW_VALUE = 492,
     MANUAL = 493,
     MEMORY = 494,
     MERGE = 495,
     MINUS = 496,
     MNEMONIC_NAME = 497,
     MODE = 498,
     MOVE = 499,
     MULTIPLE = 500,
     MULTIPLY = 501,
     NATIONAL = 502,
     NATIONAL_EDITED = 503,
     NATIVE = 504,
     NE = 505,
     NEGATIVE = 506,
     NEXT = 507,
     NEXT_SENTENCE = 508,
     NO = 509,
     NOT = 510,
     NOT_END = 511,
     NOT_EOP = 512,
     NOT_EXCEPTION = 513,
     NOT_INVALID_KEY = 514,
     NOT_OVERFLOW = 515,
     NOT_SIZE_ERROR = 516,
     NO_ADVANCING = 517,
     NUMBER = 518,
     NUMBERS = 519,
     NUMERIC = 520,
     NUMERIC_EDITED = 521,
     NUMVALC_FUNC = 522,
     OBJECT_COMPUTER = 523,
     OCCURS = 524,
     OF = 525,
     OFF = 526,
     OMITTED = 527,
     ON = 528,
     ONLY = 529,
     OPEN = 530,
     OPTIONAL = 531,
     OR = 532,
     ORDER = 533,
     ORGANIZATION = 534,
     OTHER = 535,
     OUTPUT = 536,
     OVERFLOW = 537,
     OVERLINE = 538,
     PACKED_DECIMAL = 539,
     PADDING = 540,
     PAGE = 541,
     PAGE_FOOTING = 542,
     PAGE_HEADING = 543,
     PARAGRAPH = 544,
     PERFORM = 545,
     PICTURE = 546,
     PLUS = 547,
     POINTER = 548,
     POSITION = 549,
     POSITIVE = 550,
     PRESENT = 551,
     PREVIOUS = 552,
     PRINTER = 553,
     PRINTING = 554,
     PROCEDURE = 555,
     PROCEDURES = 556,
     PROCEED = 557,
     PROGRAM = 558,
     PROGRAM_ID = 559,
     PROGRAM_NAME = 560,
     PROGRAM_POINTER = 561,
     PROMPT = 562,
     QUOTE = 563,
     RANDOM = 564,
     RD = 565,
     READ = 566,
     RECORD = 567,
     RECORDING = 568,
     RECORDS = 569,
     RECURSIVE = 570,
     REDEFINES = 571,
     REEL = 572,
     REFERENCE = 573,
     RELATIVE = 574,
     RELEASE = 575,
     REMAINDER = 576,
     REMOVAL = 577,
     RENAMES = 578,
     REPLACING = 579,
     REPORT = 580,
     REPORTING = 581,
     REPORTS = 582,
     REPORT_FOOTING = 583,
     REPORT_HEADING = 584,
     REPOSITORY = 585,
     REQUIRED = 586,
     RESERVE = 587,
     RETURN = 588,
     RETURNING = 589,
     REVERSE_FUNC = 590,
     REVERSE_VIDEO = 591,
     REWIND = 592,
     REWRITE = 593,
     RIGHT = 594,
     ROLLBACK = 595,
     ROUNDED = 596,
     RUN = 597,
     SAME = 598,
     SCREEN = 599,
     SCREEN_CONTROL = 600,
     SCROLL = 601,
     SD = 602,
     SEARCH = 603,
     SECTION = 604,
     SECURE = 605,
     SEGMENT_LIMIT = 606,
     SELECT = 607,
     SEMI_COLON = 608,
     SENTENCE = 609,
     SEPARATE = 610,
     SEQUENCE = 611,
     SEQUENTIAL = 612,
     SET = 613,
     SHARING = 614,
     SIGN = 615,
     SIGNED = 616,
     SIGNED_INT = 617,
     SIGNED_LONG = 618,
     SIGNED_SHORT = 619,
     SIZE = 620,
     SIZE_ERROR = 621,
     SORT = 622,
     SORT_MERGE = 623,
     SOURCE = 624,
     SOURCE_COMPUTER = 625,
     SPACE = 626,
     SPECIAL_NAMES = 627,
     STANDARD = 628,
     STANDARD_1 = 629,
     STANDARD_2 = 630,
     START = 631,
     STATUS = 632,
     STOP = 633,
     STRING = 634,
     SUBSTITUTE_FUNC = 635,
     SUBSTITUTE_CASE_FUNC = 636,
     SUBTRACT = 637,
     SUM = 638,
     SUPPRESS = 639,
     SYMBOLIC = 640,
     SYNCHRONIZED = 641,
     TALLYING = 642,
     TAPE = 643,
     TERMINATE = 644,
     TEST = 645,
     THAN = 646,
     THEN = 647,
     THRU = 648,
     TIME = 649,
     TIMES = 650,
     TO = 651,
     TOK_FALSE = 652,
     TOK_FILE = 653,
     TOK_INITIAL = 654,
     TOK_NULL = 655,
     TOK_TRUE = 656,
     TOP = 657,
     TRAILING = 658,
     TRANSFORM = 659,
     TRIM_FUNCTION = 660,
     TYPE = 661,
     UNDERLINE = 662,
     UNIT = 663,
     UNLOCK = 664,
     UNSIGNED = 665,
     UNSIGNED_INT = 666,
     UNSIGNED_LONG = 667,
     UNSIGNED_SHORT = 668,
     UNSTRING = 669,
     UNTIL = 670,
     UP = 671,
     UPDATE = 672,
     UPON = 673,
     UPON_ARGUMENT_NUMBER = 674,
     UPON_COMMAND_LINE = 675,
     UPON_ENVIRONMENT_NAME = 676,
     UPON_ENVIRONMENT_VALUE = 677,
     UPPER_CASE_FUNC = 678,
     USAGE = 679,
     USE = 680,
     USING = 681,
     VALUE = 682,
     VARYING = 683,
     WAIT = 684,
     WHEN = 685,
     WHEN_COMPILED_FUNC = 686,
     WHEN_OTHER = 687,
     WITH = 688,
     WORD = 689,
     WORDS = 690,
     WORKING_STORAGE = 691,
     WRITE = 692,
     YYYYDDD = 693,
     YYYYMMDD = 694,
     ZERO = 695,
     UNARY_SIGN = 696
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 840 "parser.c"

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
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   5482

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  455
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  695
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1548
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2284

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   696

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   454,     2,
     450,   449,   443,   441,     2,   442,   447,   444,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   453,     2,
     452,   448,   451,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   446,     2,     2,     2,     2,     2,
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
     435,   436,   437,   438,   439,   440,   445
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    12,    14,    16,    17,
      18,    27,    28,    29,    38,    39,    40,    48,    49,    51,
      54,    55,    59,    63,    67,    68,    76,    82,    84,    86,
      87,    90,    91,    95,    97,   100,   102,   104,   106,   107,
     113,   114,   119,   120,   123,   125,   127,   129,   131,   135,
     136,   139,   143,   146,   150,   152,   156,   157,   160,   164,
     167,   169,   172,   174,   176,   178,   184,   186,   188,   193,
     197,   201,   202,   205,   207,   210,   214,   218,   220,   223,
     227,   228,   231,   233,   236,   238,   240,   242,   244,   246,
     248,   250,   252,   254,   256,   258,   262,   263,   269,   273,
     277,   281,   285,   286,   292,   294,   296,   297,   303,   305,
     307,   309,   311,   313,   315,   318,   320,   324,   325,   330,
     332,   336,   338,   340,   342,   344,   346,   348,   350,   352,
     354,   356,   358,   360,   364,   368,   370,   373,   375,   378,
     383,   385,   388,   390,   394,   399,   404,   408,   412,   417,
     421,   425,   426,   432,   433,   438,   439,   444,   445,   449,
     450,   453,   454,   461,   462,   465,   467,   469,   471,   473,
     475,   477,   479,   481,   483,   485,   487,   489,   491,   497,
     502,   507,   508,   510,   512,   513,   515,   517,   519,   521,
     523,   528,   530,   532,   534,   541,   550,   551,   554,   557,
     559,   560,   563,   565,   569,   575,   576,   578,   580,   585,
     588,   591,   593,   594,   599,   605,   608,   610,   612,   616,
     618,   620,   624,   626,   628,   631,   636,   641,   646,   653,
     658,   662,   666,   669,   672,   675,   676,   680,   681,   684,
     686,   689,   691,   693,   695,   701,   702,   704,   706,   708,
     714,   716,   719,   722,   723,   726,   731,   732,   742,   743,
     744,   750,   751,   755,   756,   759,   763,   766,   769,   771,
     773,   774,   779,   780,   783,   786,   789,   791,   793,   795,
     797,   799,   801,   803,   805,   807,   813,   814,   816,   818,
     823,   830,   840,   841,   845,   846,   849,   850,   853,   857,
     859,   861,   867,   873,   875,   877,   881,   887,   888,   891,
     893,   895,   897,   903,   908,   912,   917,   921,   925,   929,
     930,   931,   937,   938,   940,   941,   944,   948,   953,   956,
     958,   959,   964,   966,   967,   969,   971,   973,   974,   977,
     979,   983,   987,   994,   995,   998,  1000,  1002,  1004,  1006,
    1008,  1010,  1012,  1014,  1016,  1018,  1020,  1022,  1024,  1026,
    1029,  1033,  1034,  1037,  1040,  1042,  1044,  1048,  1050,  1052,
    1054,  1056,  1058,  1060,  1062,  1064,  1066,  1068,  1070,  1072,
    1074,  1076,  1078,  1080,  1082,  1084,  1086,  1089,  1092,  1094,
    1097,  1100,  1102,  1105,  1108,  1110,  1113,  1116,  1118,  1121,
    1124,  1126,  1128,  1132,  1136,  1144,  1145,  1148,  1149,  1153,
    1155,  1156,  1162,  1164,  1166,  1167,  1171,  1173,  1176,  1178,
    1181,  1184,  1185,  1187,  1189,  1193,  1195,  1196,  1205,  1207,
    1210,  1212,  1216,  1217,  1221,  1224,  1229,  1232,  1233,  1234,
    1240,  1241,  1242,  1248,  1249,  1250,  1256,  1257,  1259,  1261,
    1264,  1270,  1271,  1274,  1277,  1281,  1283,  1285,  1288,  1291,
    1294,  1295,  1297,  1299,  1302,  1311,  1312,  1316,  1317,  1322,
    1323,  1328,  1329,  1333,  1334,  1338,  1340,  1345,  1348,  1350,
    1352,  1353,  1356,  1361,  1362,  1365,  1367,  1369,  1371,  1373,
    1375,  1377,  1379,  1381,  1383,  1385,  1387,  1389,  1391,  1393,
    1395,  1397,  1401,  1403,  1405,  1407,  1409,  1411,  1413,  1415,
    1420,  1425,  1428,  1430,  1432,  1435,  1439,  1441,  1445,  1452,
    1455,  1459,  1462,  1464,  1467,  1470,  1472,  1475,  1476,  1478,
    1480,  1485,  1488,  1489,  1491,  1493,  1494,  1495,  1496,  1503,
    1504,  1506,  1508,  1511,  1513,  1514,  1520,  1521,  1524,  1526,
    1528,  1530,  1532,  1535,  1538,  1540,  1542,  1544,  1546,  1548,
    1550,  1552,  1554,  1556,  1558,  1564,  1570,  1574,  1578,  1580,
    1582,  1584,  1586,  1588,  1590,  1592,  1595,  1598,  1601,  1602,
    1604,  1606,  1608,  1610,  1611,  1613,  1615,  1617,  1619,  1623,
    1624,  1625,  1626,  1636,  1637,  1638,  1642,  1643,  1647,  1649,
    1652,  1657,  1658,  1661,  1664,  1665,  1669,  1673,  1678,  1682,
    1683,  1685,  1686,  1689,  1690,  1691,  1699,  1700,  1703,  1705,
    1707,  1709,  1712,  1715,  1720,  1723,  1725,  1727,  1728,  1730,
    1731,  1732,  1736,  1737,  1740,  1742,  1744,  1746,  1748,  1750,
    1752,  1754,  1756,  1758,  1760,  1762,  1764,  1766,  1768,  1770,
    1772,  1774,  1776,  1778,  1780,  1782,  1784,  1786,  1788,  1790,
    1792,  1794,  1796,  1798,  1800,  1802,  1804,  1806,  1808,  1810,
    1812,  1814,  1816,  1818,  1820,  1822,  1824,  1826,  1828,  1830,
    1832,  1834,  1836,  1838,  1840,  1841,  1846,  1851,  1856,  1860,
    1864,  1868,  1873,  1877,  1882,  1886,  1890,  1894,  1899,  1905,
    1909,  1914,  1918,  1922,  1923,  1927,  1931,  1934,  1937,  1940,
    1944,  1948,  1952,  1953,  1956,  1958,  1961,  1963,  1965,  1967,
    1969,  1971,  1973,  1975,  1979,  1983,  1987,  1991,  1993,  1995,
    1997,  1999,  2001,  2003,  2004,  2006,  2007,  2012,  2017,  2023,
    2030,  2031,  2034,  2035,  2037,  2038,  2042,  2046,  2052,  2053,
    2056,  2059,  2060,  2066,  2067,  2070,  2071,  2080,  2081,  2082,
    2086,  2088,  2091,  2094,  2098,  2099,  2102,  2105,  2108,  2109,
    2112,  2115,  2116,  2117,  2121,  2122,  2123,  2127,  2128,  2130,
    2131,  2135,  2136,  2139,  2140,  2144,  2145,  2149,  2150,  2152,
    2156,  2160,  2163,  2165,  2167,  2168,  2173,  2178,  2179,  2181,
    2183,  2185,  2187,  2189,  2190,  2197,  2198,  2200,  2201,  2206,
    2207,  2212,  2216,  2220,  2224,  2228,  2233,  2240,  2247,  2254,
    2261,  2262,  2265,  2268,  2270,  2273,  2275,  2277,  2280,  2283,
    2285,  2287,  2289,  2291,  2293,  2297,  2301,  2305,  2309,  2311,
    2313,  2314,  2316,  2317,  2322,  2327,  2334,  2341,  2350,  2359,
    2360,  2362,  2363,  2368,  2369,  2375,  2377,  2381,  2383,  2385,
    2387,  2390,  2392,  2395,  2396,  2400,  2401,  2402,  2406,  2409,
    2413,  2415,  2419,  2422,  2424,  2426,  2428,  2429,  2432,  2433,
    2435,  2436,  2440,  2441,  2443,  2445,  2448,  2450,  2452,  2453,
    2457,  2458,  2462,  2463,  2469,  2470,  2474,  2475,  2478,  2479,
    2480,  2489,  2493,  2494,  2495,  2499,  2500,  2502,  2503,  2511,
    2512,  2515,  2516,  2520,  2524,  2525,  2528,  2530,  2533,  2538,
    2540,  2542,  2544,  2546,  2548,  2550,  2552,  2553,  2555,  2556,
    2560,  2561,  2566,  2568,  2570,  2572,  2574,  2577,  2579,  2581,
    2583,  2584,  2588,  2590,  2593,  2596,  2599,  2601,  2603,  2605,
    2608,  2611,  2613,  2616,  2621,  2624,  2625,  2627,  2629,  2631,
    2633,  2638,  2644,  2645,  2650,  2651,  2653,  2654,  2658,  2659,
    2663,  2667,  2672,  2673,  2678,  2683,  2690,  2691,  2693,  2694,
    2698,  2699,  2705,  2707,  2709,  2711,  2713,  2714,  2718,  2719,
    2723,  2726,  2727,  2731,  2734,  2735,  2740,  2743,  2744,  2746,
    2748,  2752,  2753,  2755,  2758,  2762,  2766,  2767,  2771,  2773,
    2777,  2785,  2786,  2797,  2798,  2801,  2802,  2805,  2808,  2812,
    2816,  2819,  2820,  2824,  2825,  2827,  2829,  2830,  2832,  2833,
    2838,  2839,  2847,  2848,  2850,  2851,  2859,  2860,  2863,  2867,
    2868,  2870,  2872,  2873,  2878,  2883,  2884,  2892,  2893,  2896,
    2897,  2898,  2903,  2905,  2908,  2909,  2914,  2915,  2917,  2918,
    2922,  2924,  2926,  2928,  2930,  2932,  2937,  2942,  2946,  2951,
    2953,  2955,  2957,  2960,  2964,  2966,  2969,  2973,  2977,  2978,
    2982,  2983,  2991,  2992,  2998,  2999,  3002,  3003,  3006,  3007,
    3011,  3012,  3015,  3020,  3021,  3024,  3029,  3030,  3031,  3039,
    3040,  3045,  3048,  3051,  3054,  3057,  3060,  3061,  3063,  3064,
    3069,  3072,  3073,  3076,  3079,  3080,  3089,  3091,  3094,  3096,
    3100,  3104,  3105,  3109,  3110,  3112,  3113,  3118,  3123,  3130,
    3137,  3138,  3140,  3143,  3144,  3146,  3147,  3151,  3152,  3160,
    3161,  3166,  3167,  3169,  3171,  3172,  3182,  3183,  3187,  3189,
    3193,  3196,  3199,  3202,  3206,  3207,  3211,  3212,  3216,  3217,
    3221,  3222,  3224,  3226,  3228,  3230,  3239,  3240,  3242,  3244,
    3246,  3248,  3250,  3252,  3253,  3255,  3256,  3258,  3260,  3262,
    3264,  3266,  3268,  3270,  3271,  3273,  3279,  3281,  3284,  3290,
    3291,  3300,  3301,  3304,  3305,  3310,  3314,  3318,  3320,  3322,
    3323,  3325,  3327,  3328,  3330,  3333,  3336,  3337,  3338,  3342,
    3343,  3344,  3348,  3351,  3352,  3353,  3357,  3358,  3359,  3363,
    3366,  3367,  3368,  3372,  3373,  3374,  3378,  3380,  3382,  3385,
    3386,  3390,  3391,  3395,  3397,  3399,  3402,  3403,  3407,  3408,
    3412,  3413,  3415,  3417,  3419,  3422,  3423,  3427,  3428,  3432,
    3433,  3437,  3439,  3441,  3442,  3445,  3448,  3451,  3454,  3457,
    3460,  3463,  3466,  3469,  3472,  3475,  3478,  3481,  3484,  3485,
    3488,  3491,  3494,  3497,  3500,  3503,  3506,  3509,  3512,  3515,
    3518,  3521,  3524,  3527,  3530,  3533,  3536,  3539,  3542,  3545,
    3548,  3551,  3554,  3557,  3560,  3562,  3565,  3567,  3569,  3572,
    3574,  3577,  3579,  3585,  3590,  3592,  3598,  3603,  3605,  3609,
    3610,  3612,  3614,  3616,  3620,  3624,  3628,  3632,  3635,  3638,
    3642,  3646,  3648,  3652,  3654,  3657,  3660,  3662,  3664,  3666,
    3669,  3671,  3673,  3676,  3678,  3679,  3682,  3684,  3686,  3688,
    3692,  3694,  3696,  3699,  3701,  3702,  3704,  3706,  3708,  3710,
    3712,  3715,  3717,  3721,  3723,  3726,  3728,  3732,  3736,  3740,
    3745,  3749,  3751,  3753,  3755,  3757,  3761,  3765,  3769,  3771,
    3773,  3775,  3777,  3779,  3781,  3783,  3785,  3787,  3789,  3791,
    3793,  3795,  3797,  3799,  3801,  3803,  3805,  3807,  3809,  3811,
    3814,  3817,  3821,  3823,  3827,  3831,  3836,  3842,  3844,  3846,
    3849,  3851,  3855,  3857,  3859,  3861,  3863,  3865,  3867,  3869,
    3872,  3875,  3881,  3887,  3893,  3899,  3905,  3911,  3917,  3922,
    3928,  3931,  3932,  3937,  3943,  3944,  3948,  3949,  3951,  3953,
    3957,  3961,  3963,  3967,  3969,  3973,  3974,  3975,  3977,  3978,
    3980,  3981,  3983,  3984,  3986,  3988,  3989,  3991,  3992,  3994,
    3995,  3997,  3998,  4001,  4003,  4005,  4008,  4011,  4014,  4016,
    4019,  4021,  4022,  4024,  4025,  4027,  4028,  4030,  4031,  4033,
    4034,  4036,  4037,  4039,  4040,  4042,  4043,  4045,  4046,  4048,
    4049,  4051,  4052,  4054,  4055,  4057,  4058,  4060,  4061,  4063,
    4064,  4066,  4067,  4069,  4070,  4072,  4073,  4075,  4077,  4078,
    4080,  4081,  4083,  4085,  4086,  4088,  4089,  4091,  4092,  4094,
    4095,  4097,  4098,  4100,  4101,  4103,  4106,  4107,  4109,  4110,
    4112,  4113,  4115,  4116,  4118,  4119,  4121,  4122,  4124,  4125,
    4127,  4130,  4131,  4133,  4134,  4136,  4137,  4139,  4140,  4142,
    4143,  4145,  4146,  4148,  4149,  4151,  4152,  4154,  4155
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     456,     0,    -1,    -1,   457,   458,    -1,   459,    -1,   458,
     459,    -1,   460,    -1,   466,    -1,    -1,    -1,   473,   481,
     461,   580,   462,   714,   469,   470,    -1,    -1,    -1,   473,
     481,   464,   580,   465,   714,   469,   471,    -1,    -1,    -1,
     475,   481,   467,   580,   468,   714,   472,    -1,    -1,   463,
      -1,   469,   463,    -1,    -1,   136,   476,   447,    -1,   136,
     476,   447,    -1,   132,   476,   447,    -1,    -1,   304,   447,
     476,   477,   474,   478,   447,    -1,   179,   447,   476,   477,
     447,    -1,   305,    -1,   230,    -1,    -1,    27,   230,    -1,
      -1,  1124,   479,  1135,    -1,    72,    -1,    72,   480,    -1,
     480,    -1,   399,    -1,   315,    -1,    -1,   147,   117,   447,
     482,   533,    -1,    -1,    82,   349,   447,   483,    -1,    -1,
     483,   484,    -1,   485,    -1,   489,    -1,   502,    -1,   497,
      -1,   370,   447,   486,    -1,    -1,   488,   447,    -1,   488,
     487,   447,    -1,   487,   447,    -1,  1149,   104,   243,    -1,
     434,    -1,   268,   447,   490,    -1,    -1,   488,   447,    -1,
     488,   491,   447,    -1,   491,   447,    -1,   492,    -1,   491,
     492,    -1,   493,    -1,   495,    -1,   496,    -1,   239,   365,
    1124,  1084,   494,    -1,    56,    -1,   435,    -1,  1135,  1107,
    1124,  1063,    -1,   351,  1124,  1084,    -1,   330,   447,   498,
      -1,    -1,   499,   447,    -1,   500,    -1,   499,   500,    -1,
     178,   501,   207,    -1,   178,     9,   207,    -1,   230,    -1,
     501,   230,    -1,   372,   447,   503,    -1,    -1,   504,   447,
      -1,   505,    -1,   504,   505,    -1,   506,    -1,   510,    -1,
     519,    -1,   526,    -1,   523,    -1,   527,    -1,   528,    -1,
     529,    -1,   530,    -1,   531,    -1,   532,    -1,   434,  1124,
      94,    -1,    -1,   434,  1124,  1066,   507,   508,    -1,    25,
    1124,  1066,    -1,    26,  1124,  1066,    -1,   148,  1124,  1066,
      -1,   149,  1124,  1066,    -1,    -1,   508,   509,  1142,  1124,
    1066,    -1,   273,    -1,   271,    -1,    -1,    11,  1066,   511,
    1124,   512,    -1,   249,    -1,   374,    -1,   375,    -1,   121,
      -1,   513,    -1,   514,    -1,   513,   514,    -1,   517,    -1,
     517,   393,   517,    -1,    -1,   517,    17,   515,   516,    -1,
     518,    -1,   516,    17,   518,    -1,   230,    -1,   371,    -1,
     440,    -1,   308,    -1,   191,    -1,   237,    -1,   230,    -1,
     371,    -1,   440,    -1,   308,    -1,   191,    -1,   237,    -1,
     385,  1117,   520,    -1,   521,  1125,   522,    -1,  1066,    -1,
     521,  1066,    -1,  1084,    -1,   522,  1084,    -1,    57,  1066,
    1124,   524,    -1,   525,    -1,   524,   525,    -1,  1087,    -1,
    1087,   393,  1087,    -1,   231,  1066,  1124,  1063,    -1,    95,
    1139,  1124,   230,    -1,   105,  1124,    67,    -1,    97,  1124,
    1063,    -1,    94,   377,  1124,  1063,    -1,   345,  1124,  1063,
      -1,   159,  1124,  1063,    -1,    -1,   204,   349,   447,   536,
     569,    -1,    -1,   166,   447,   534,   537,    -1,    -1,   212,
     447,   535,   570,    -1,    -1,   166,   447,   537,    -1,    -1,
     537,   538,    -1,    -1,   352,  1101,  1066,   539,   540,   447,
      -1,    -1,   540,   541,    -1,   542,    -1,   546,    -1,   548,
      -1,   553,    -1,   554,    -1,   556,    -1,   560,    -1,   562,
      -1,   563,    -1,   564,    -1,   565,    -1,   566,    -1,   567,
      -1,    29,  1147,   544,   543,   545,    -1,    29,  1147,   544,
     114,    -1,    29,  1147,   544,   298,    -1,    -1,   114,    -1,
     298,    -1,    -1,   164,    -1,   120,    -1,   230,    -1,   115,
      -1,  1081,    -1,     4,  1129,  1124,   547,    -1,   357,    -1,
     120,    -1,   309,    -1,    19,   312,  1126,  1124,  1063,  1097,
      -1,    19,   312,  1126,  1124,  1063,   552,   549,  1097,    -1,
      -1,   550,   551,    -1,   549,   551,    -1,  1063,    -1,    -1,
     369,  1124,    -1,   448,    -1,  1107,  1124,   434,    -1,   555,
     377,  1124,  1063,  1064,    -1,    -1,   398,    -1,   367,    -1,
     234,  1129,  1124,   557,    -1,   238,   558,    -1,    32,   558,
      -1,   161,    -1,    -1,   433,   234,   273,   559,    -1,   433,
     234,   273,   245,   559,    -1,   433,   340,    -1,   312,    -1,
     314,    -1,   279,  1124,   561,    -1,   561,    -1,   198,    -1,
     312,  1114,   357,    -1,   357,    -1,   319,    -1,   227,   357,
      -1,   285,  1116,  1124,  1065,    -1,   312,   110,  1124,   374,
      -1,   312,  1126,  1124,  1063,    -1,   312,  1126,  1124,  1063,
     552,   549,    -1,   319,  1126,  1124,  1063,    -1,   332,  1084,
    1111,    -1,   359,  1149,   568,    -1,     9,  1134,    -1,   254,
    1134,    -1,   311,   274,    -1,    -1,   212,   447,   570,    -1,
      -1,   571,   447,    -1,   572,    -1,   571,   572,    -1,   573,
      -1,   575,    -1,   579,    -1,   343,   574,  1111,  1121,  1054,
      -1,    -1,   312,    -1,   367,    -1,   368,    -1,   245,  1120,
    1143,  1118,   576,    -1,   577,    -1,   576,   577,    -1,  1055,
     578,    -1,    -1,   294,  1084,    -1,    22,    71,  1132,  1062,
      -1,    -1,    99,   117,   447,   581,   612,   657,   659,   661,
     702,    -1,    -1,    -1,   398,   349,   447,   582,   584,    -1,
      -1,   587,   583,   586,    -1,    -1,   584,   585,    -1,   587,
     588,   614,    -1,   588,   614,    -1,   586,   585,    -1,   165,
      -1,   347,    -1,    -1,  1055,   589,   590,   447,    -1,    -1,
     590,   591,    -1,  1124,   164,    -1,  1124,   184,    -1,   592,
      -1,   594,    -1,   598,    -1,   600,    -1,   602,    -1,   603,
      -1,   609,    -1,   610,    -1,   611,    -1,    47,  1118,  1084,
     597,   593,    -1,    -1,   314,    -1,    56,    -1,   312,  1118,
    1084,  1117,    -1,   312,  1118,  1084,   396,  1084,  1117,    -1,
     312,  1124,   428,  1123,  1141,   596,   597,  1117,   595,    -1,
      -1,   111,  1132,  1063,    -1,    -1,  1122,  1084,    -1,    -1,
     396,  1084,    -1,   215,  1105,   599,    -1,   373,    -1,   272,
      -1,   427,   270,   434,  1124,   601,    -1,   427,   270,   167,
    1124,   601,    -1,   230,    -1,  1081,    -1,    99,  1105,  1062,
      -1,   225,  1124,  1065,  1128,   604,    -1,    -1,   604,   605,
      -1,   606,    -1,   607,    -1,   608,    -1,  1149,   171,  1113,
    1065,  1128,    -1,  1113,   402,  1065,  1128,    -1,  1113,    48,
    1065,    -1,   313,  1129,  1124,   434,    -1,    61,  1124,   434,
      -1,   325,  1124,   701,    -1,   327,  1110,   701,    -1,    -1,
      -1,   436,   349,   447,   613,   614,    -1,    -1,   615,    -1,
      -1,   616,   617,    -1,  1095,   618,   447,    -1,   617,  1095,
     618,   447,    -1,   617,   447,    -1,   625,    -1,    -1,   620,
     621,   619,   626,    -1,   434,    -1,    -1,   168,    -1,   434,
      -1,   434,    -1,    -1,  1124,   184,    -1,  1085,    -1,   221,
    1131,  1080,    -1,    50,  1131,  1080,    -1,   620,   622,    83,
     623,  1112,   624,    -1,    -1,   626,   627,    -1,   628,    -1,
     629,    -1,   631,    -1,   632,    -1,   633,    -1,   635,    -1,
     636,    -1,   645,    -1,   646,    -1,   648,    -1,   649,    -1,
     650,    -1,   655,    -1,   656,    -1,   316,  1080,    -1,  1124,
     164,   630,    -1,    -1,    27,   230,    -1,  1124,   184,    -1,
     291,    -1,   634,    -1,   424,  1124,   634,    -1,    37,    -1,
      73,    -1,    75,    -1,    76,    -1,    77,    -1,    78,    -1,
      79,    -1,    80,    -1,   115,    -1,   197,    -1,   284,    -1,
     293,    -1,   306,    -1,   364,    -1,   362,    -1,   363,    -1,
     413,    -1,   411,    -1,   412,    -1,    39,   361,    -1,    39,
     410,    -1,    39,    -1,    42,   361,    -1,    42,   410,    -1,
      42,    -1,    41,   361,    -1,    41,   410,    -1,    41,    -1,
      40,   361,    -1,    40,   410,    -1,    40,    -1,    38,   361,
      -1,    38,   410,    -1,    38,    -1,   247,    -1,  1140,   219,
    1103,    -1,  1140,   403,  1103,    -1,   269,  1084,   637,  1146,
     638,   639,   642,    -1,    -1,   396,  1084,    -1,    -1,   111,
    1132,  1063,    -1,   640,    -1,    -1,   640,   641,  1126,  1124,
    1062,    -1,    28,    -1,   112,    -1,    -1,   198,  1115,   643,
      -1,   644,    -1,   643,   644,    -1,   434,    -1,   213,  1137,
      -1,   386,   647,    -1,    -1,   220,    -1,   339,    -1,    43,
    1148,   440,    -1,    34,    -1,    -1,   427,  1125,   652,   651,
    1148,  1138,  1147,   654,    -1,   653,    -1,   652,   653,    -1,
    1085,    -1,  1085,   393,  1085,    -1,    -1,   397,  1124,  1085,
      -1,   323,  1081,    -1,   323,  1081,   393,  1081,    -1,    21,
     221,    -1,    -1,    -1,   233,   349,   447,   658,   614,    -1,
      -1,    -1,   229,   349,   447,   660,   614,    -1,    -1,    -1,
     325,   349,   447,   662,   663,    -1,    -1,   664,    -1,   665,
      -1,   664,   665,    -1,   310,   701,   666,   447,   680,    -1,
      -1,   666,   667,    -1,  1124,   184,    -1,    60,  1124,  1076,
      -1,   668,    -1,   672,    -1,    87,   669,    -1,    88,   669,
      -1,   670,   671,    -1,    -1,   169,    -1,  1079,    -1,   671,
    1079,    -1,   286,  1125,   678,   673,   674,   675,   676,   677,
      -1,    -1,   189,  1124,  1084,    -1,    -1,   170,   113,  1124,
    1084,    -1,    -1,   216,    90,  1124,  1084,    -1,    -1,   217,
    1124,  1084,    -1,    -1,   171,  1124,  1084,    -1,  1084,    -1,
    1084,   679,  1084,    66,    -1,  1084,   679,    -1,   227,    -1,
     228,    -1,    -1,   680,   681,    -1,   620,   621,   682,   447,
      -1,    -1,   682,   683,    -1,   684,    -1,   686,    -1,   693,
      -1,   632,    -1,   633,    -1,   635,    -1,   645,    -1,   687,
      -1,   648,    -1,   698,    -1,   688,    -1,   650,    -1,   691,
      -1,   699,    -1,   636,    -1,   692,    -1,   406,  1124,   685,
      -1,   329,    -1,   288,    -1,    90,    -1,   113,    -1,    89,
      -1,   287,    -1,   328,    -1,   252,   188,  1124,  1084,    -1,
      65,  1130,  1124,  1084,    -1,    65,   264,    -1,    66,    -1,
     689,    -1,   688,   689,    -1,   383,  1131,   690,    -1,  1063,
      -1,   296,   430,  1035,    -1,   428,  1079,   176,  1070,    49,
    1070,    -1,   694,   695,    -1,   227,   697,  1125,    -1,   228,
    1110,    -1,   696,    -1,   695,   696,    -1,   292,  1084,    -1,
    1084,    -1,   252,   286,    -1,    -1,   263,    -1,   264,    -1,
     369,  1124,  1079,  1102,    -1,   188,   700,    -1,    -1,   199,
      -1,   434,    -1,    -1,    -1,    -1,   344,   349,   447,   703,
     704,   705,    -1,    -1,   706,    -1,   707,    -1,   706,   707,
      -1,   625,    -1,    -1,   620,   621,   708,   709,   447,    -1,
      -1,   709,   710,    -1,    44,    -1,    45,    -1,    36,    -1,
      46,    -1,   155,   150,    -1,   155,   152,    -1,   190,    -1,
     236,    -1,   336,    -1,   407,    -1,   283,    -1,    31,    -1,
     350,    -1,   331,    -1,   177,    -1,   307,    -1,   227,  1130,
    1124,   711,  1078,    -1,    65,  1130,  1124,   712,  1078,    -1,
     173,  1124,  1078,    -1,    33,  1124,  1078,    -1,   633,    -1,
     648,    -1,   645,    -1,   635,    -1,   650,    -1,   632,    -1,
     713,    -1,   426,  1079,    -1,   176,  1077,    -1,   396,  1079,
      -1,    -1,   292,    -1,   441,    -1,   241,    -1,   442,    -1,
      -1,   292,    -1,   441,    -1,   241,    -1,   442,    -1,   269,
    1084,  1146,    -1,    -1,    -1,    -1,   300,   117,   717,   725,
     447,   715,   726,   716,   728,    -1,    -1,    -1,   426,   718,
     720,    -1,    -1,    54,   719,   720,    -1,   721,    -1,   720,
     721,    -1,   722,   723,   724,   434,    -1,    -1,  1115,   318,
      -1,  1115,   427,    -1,    -1,   365,  1124,    31,    -1,   365,
    1124,   107,    -1,   410,   365,  1124,  1084,    -1,   365,  1124,
    1084,    -1,    -1,   276,    -1,    -1,   334,   434,    -1,    -1,
      -1,   106,   447,   727,   728,   123,   106,   447,    -1,    -1,
     728,   729,    -1,   730,    -1,   731,    -1,   732,    -1,   738,
     447,    -1,     1,   447,    -1,   733,   349,   734,   447,    -1,
     434,   447,    -1,   733,    -1,   434,    -1,    -1,   230,    -1,
      -1,    -1,   736,   737,   738,    -1,    -1,   738,   739,    -1,
     740,    -1,   750,    -1,   755,    -1,   759,    -1,   762,    -1,
     775,    -1,   778,    -1,   788,    -1,   783,    -1,   789,    -1,
     790,    -1,   793,    -1,   795,    -1,   802,    -1,   806,    -1,
     808,    -1,   823,    -1,   826,    -1,   828,    -1,   830,    -1,
     833,    -1,   835,    -1,   841,    -1,   850,    -1,   852,    -1,
     869,    -1,   871,    -1,   874,    -1,   878,    -1,   884,    -1,
     894,    -1,   901,    -1,   903,    -1,   906,    -1,   910,    -1,
     911,    -1,   922,    -1,   933,    -1,   943,    -1,   949,    -1,
     952,    -1,   958,    -1,   962,    -1,   964,    -1,   966,    -1,
     968,    -1,   971,    -1,   982,    -1,   995,    -1,   253,    -1,
      -1,     3,   741,   742,   749,    -1,  1079,   743,   746,  1002,
      -1,  1079,   176,   157,   214,    -1,  1079,   176,   228,    -1,
    1079,   176,    66,    -1,  1079,   176,   100,    -1,  1079,   176,
     100,   439,    -1,  1079,   176,   101,    -1,  1079,   176,   101,
     438,    -1,  1079,   176,   102,    -1,  1079,   176,   394,    -1,
    1079,   176,    68,    -1,  1079,   176,   149,  1002,    -1,  1079,
     176,   147,  1074,  1002,    -1,  1079,   176,    25,    -1,  1079,
     176,    26,  1002,    -1,  1079,   176,  1057,    -1,  1079,   176,
     434,    -1,    -1,  1113,   744,   745,    -1,  1113,   745,   744,
      -1,  1113,   744,    -1,  1113,   745,    -1,    30,  1074,    -1,
     227,  1130,  1076,    -1,    65,  1130,  1076,    -1,   294,  1130,
    1076,    -1,    -1,   433,   747,    -1,   748,    -1,   747,   748,
      -1,    36,    -1,    46,    -1,   190,    -1,   236,    -1,   336,
      -1,   407,    -1,   283,    -1,   173,  1124,  1078,    -1,    33,
    1124,  1078,    -1,   346,   416,  1034,    -1,   346,   118,  1034,
      -1,    31,    -1,   177,    -1,   331,    -1,   350,    -1,   417,
      -1,   307,    -1,    -1,   124,    -1,    -1,     5,   751,   752,
     754,    -1,  1069,   396,  1050,  1008,    -1,  1069,   753,   183,
    1050,  1008,    -1,    92,  1079,   396,  1079,  1102,  1008,    -1,
      -1,   396,  1070,    -1,    -1,   125,    -1,    -1,    10,   756,
     757,    -1,   434,  1098,   758,    -1,  1036,    56,  1098,   334,
    1068,    -1,    -1,   334,  1068,    -1,    18,   760,    -1,    -1,
     760,  1059,   396,   761,  1059,    -1,    -1,   302,   396,    -1,
      -1,    51,   763,  1077,   764,   769,   770,   772,   774,    -1,
      -1,    -1,   426,   765,   766,    -1,   767,    -1,   766,   767,
      -1,   768,   272,    -1,   768,   723,  1070,    -1,    -1,  1115,
     318,    -1,  1115,    85,    -1,  1115,   427,    -1,    -1,   334,
    1079,    -1,   183,  1079,    -1,    -1,    -1,   989,   771,   735,
      -1,    -1,    -1,   990,   773,   735,    -1,    -1,   126,    -1,
      -1,    52,   776,   777,    -1,    -1,   777,  1076,    -1,    -1,
      59,   779,   780,    -1,    -1,   780,  1055,   781,    -1,    -1,
     782,    -1,   782,  1121,   322,    -1,  1149,   254,   337,    -1,
    1149,   234,    -1,   317,    -1,   408,    -1,    -1,    74,   784,
     785,   786,    -1,  1050,   787,  1036,  1008,    -1,    -1,   127,
      -1,   448,    -1,   153,    -1,    70,    -1,    86,    -1,    -1,
     108,   791,  1055,  1136,  1028,   792,    -1,    -1,   128,    -1,
      -1,   108,   794,   398,  1054,    -1,    -1,   115,   796,   797,
     801,    -1,  1076,   421,  1003,    -1,  1076,   422,  1003,    -1,
    1076,   419,  1003,    -1,  1076,   420,  1003,    -1,  1069,   743,
     798,  1003,    -1,  1069,   743,   418,  1057,   798,  1003,    -1,
    1069,   743,   418,   434,   798,  1003,    -1,  1069,   743,   418,
     298,   798,  1003,    -1,  1069,   743,   418,    94,   798,  1003,
      -1,    -1,  1149,   262,    -1,   433,   799,    -1,   800,    -1,
     799,   800,    -1,    36,    -1,    46,    -1,   155,   150,    -1,
     155,   152,    -1,   190,    -1,   236,    -1,   336,    -1,   407,
      -1,   283,    -1,   173,  1124,  1078,    -1,    33,  1124,  1078,
      -1,   346,   416,  1034,    -1,   346,   118,  1034,    -1,    44,
      -1,    45,    -1,    -1,   129,    -1,    -1,   116,   803,   804,
     805,    -1,  1070,   206,  1050,  1008,    -1,  1070,   206,  1070,
     183,  1050,  1008,    -1,  1070,    49,  1070,   183,  1050,  1008,
      -1,  1070,   206,  1070,   183,  1051,   321,  1051,  1008,    -1,
    1070,    49,  1070,   183,  1051,   321,  1051,  1008,    -1,    -1,
     130,    -1,    -1,   146,   807,   230,   764,    -1,    -1,   158,
     809,   810,   812,   822,    -1,   811,    -1,   810,  1109,   811,
      -1,  1036,    -1,   401,    -1,   397,    -1,   813,   816,    -1,
     814,    -1,   813,   814,    -1,    -1,   818,   815,   735,    -1,
      -1,    -1,   432,   817,   735,    -1,   430,   819,    -1,   818,
     430,   819,    -1,   820,    -1,   819,  1109,   820,    -1,  1037,
     821,    -1,    21,    -1,   401,    -1,   397,    -1,    -1,   393,
    1036,    -1,    -1,   131,    -1,    -1,   162,   824,   825,    -1,
      -1,   303,    -1,   290,    -1,   290,    98,    -1,   349,    -1,
     289,    -1,    -1,   175,   827,  1067,    -1,    -1,   182,   829,
    1079,    -1,    -1,   185,  1147,   831,  1058,   832,    -1,    -1,
     111,  1132,  1079,    -1,    -1,   186,   834,    -1,    -1,    -1,
     193,   836,  1035,  1145,   837,   735,   838,   840,    -1,   193,
       1,   133,    -1,    -1,    -1,   122,   839,   735,    -1,    -1,
     133,    -1,    -1,   200,   842,  1067,   843,   844,   845,   849,
      -1,    -1,  1149,   168,    -1,    -1,     9,  1147,   427,    -1,
     848,  1147,   427,    -1,    -1,   324,   846,    -1,   847,    -1,
     846,   847,    -1,   848,  1119,    49,  1070,    -1,    12,    -1,
      15,    -1,   265,    -1,    16,    -1,   266,    -1,   247,    -1,
     248,    -1,    -1,   107,    -1,    -1,   202,   851,   671,    -1,
      -1,   205,   853,   854,   855,    -1,  1079,    -1,  1085,    -1,
    1088,    -1,   856,    -1,   855,   856,    -1,   857,    -1,   861,
      -1,   866,    -1,    -1,   387,   858,   859,    -1,   860,    -1,
     859,   860,    -1,  1074,   172,    -1,    56,   867,    -1,     9,
      -1,   219,    -1,   403,    -1,  1074,   867,    -1,   324,   862,
      -1,   863,    -1,   862,   863,    -1,    56,    49,  1074,   867,
      -1,   864,   865,    -1,    -1,     9,    -1,   219,    -1,   170,
      -1,   403,    -1,  1074,    49,  1075,   867,    -1,    91,  1074,
     396,  1075,   867,    -1,    -1,   867,   999,   868,  1070,    -1,
      -1,   399,    -1,    -1,   240,   870,   935,    -1,    -1,   244,
     872,   873,    -1,  1070,   396,  1067,    -1,    92,  1070,   396,
    1067,    -1,    -1,   246,   875,   876,   877,    -1,  1070,    49,
    1050,  1008,    -1,  1070,    49,  1070,   183,  1050,  1008,    -1,
      -1,   134,    -1,    -1,   275,   879,   880,    -1,    -1,   880,
     881,   882,  1054,   883,    -1,   203,    -1,   281,    -1,   211,
      -1,   163,    -1,    -1,   359,  1149,   568,    -1,    -1,  1149,
     254,   337,    -1,  1149,   234,    -1,    -1,   290,   885,   886,
      -1,   889,   890,    -1,    -1,   890,   887,   735,   888,    -1,
     890,   135,    -1,    -1,   135,    -1,  1059,    -1,  1059,   393,
    1059,    -1,    -1,   174,    -1,  1077,   395,    -1,   891,   415,
    1035,    -1,   891,   428,   892,    -1,    -1,  1149,   390,   999,
      -1,   893,    -1,   892,     8,   893,    -1,  1079,   176,  1070,
      49,  1070,   415,  1035,    -1,    -1,   311,   895,  1055,  1099,
    1136,   896,   897,   898,   899,   900,    -1,    -1,   206,  1079,
      -1,    -1,   195,   234,    -1,  1149,   234,    -1,  1149,   254,
     234,    -1,  1149,   194,   234,    -1,  1149,   429,    -1,    -1,
     214,  1124,   671,    -1,    -1,  1018,    -1,  1029,    -1,    -1,
     137,    -1,    -1,   320,   902,  1052,   997,    -1,    -1,   333,
     904,  1055,  1136,   896,  1018,   905,    -1,    -1,   138,    -1,
      -1,   338,   907,  1052,   997,   908,  1028,   909,    -1,    -1,
    1149,   234,    -1,  1149,   254,   234,    -1,    -1,   139,    -1,
     340,    -1,    -1,   348,   912,   913,   921,    -1,  1053,   915,
     916,   918,    -1,    -1,     9,  1053,   916,   430,  1036,   914,
     735,    -1,    -1,   428,  1079,    -1,    -1,    -1,  1113,   123,
     917,   735,    -1,   919,    -1,   919,   918,    -1,    -1,   430,
    1035,   920,   735,    -1,    -1,   140,    -1,    -1,   358,   923,
     924,    -1,   925,    -1,   926,    -1,   927,    -1,   929,    -1,
     931,    -1,   147,  1074,   396,  1074,    -1,  1067,   396,   146,
    1073,    -1,  1067,   396,  1070,    -1,  1067,   928,    49,  1070,
      -1,   416,    -1,   118,    -1,   930,    -1,   929,   930,    -1,
    1056,   396,   509,    -1,   932,    -1,   931,   932,    -1,  1067,
     396,   401,    -1,  1067,   396,   397,    -1,    -1,   367,   934,
     935,    -1,    -1,  1081,   937,   939,   940,   936,   941,   942,
      -1,    -1,   937,  1132,   641,  1126,   938,    -1,    -1,   938,
    1081,    -1,    -1,  1106,  1133,    -1,    -1,  1107,  1124,  1063,
      -1,    -1,   426,  1054,    -1,   203,   300,  1124,   889,    -1,
      -1,   183,  1054,    -1,   281,   300,  1124,   889,    -1,    -1,
      -1,   376,   944,  1055,   945,   946,  1028,   948,    -1,    -1,
     214,  1124,   947,   671,    -1,  1100,  1041,    -1,  1100,  1042,
      -1,  1100,  1043,    -1,  1100,  1044,    -1,  1100,  1045,    -1,
      -1,   141,    -1,    -1,   378,   342,   950,   951,    -1,   378,
     230,    -1,    -1,   334,  1070,    -1,   183,  1070,    -1,    -1,
     379,   953,   954,   206,  1079,   956,  1013,   957,    -1,   955,
      -1,   954,   955,    -1,  1070,    -1,   109,  1115,   365,    -1,
     109,  1115,  1070,    -1,    -1,  1149,   293,  1079,    -1,    -1,
     142,    -1,    -1,   382,   959,   960,   961,    -1,  1069,   176,
    1050,  1008,    -1,  1069,   176,  1070,   183,  1050,  1008,    -1,
      92,  1079,   176,  1079,  1102,  1008,    -1,    -1,   143,    -1,
     384,   963,    -1,    -1,   299,    -1,    -1,   389,   965,   671,
      -1,    -1,   404,   967,  1079,   176,  1074,   396,  1075,    -1,
      -1,   409,   969,  1055,   970,    -1,    -1,   312,    -1,   314,
      -1,    -1,   414,   972,  1079,   973,   976,   956,   980,  1013,
     981,    -1,    -1,   109,  1115,   974,    -1,   975,    -1,   974,
     277,   975,    -1,  1096,  1074,    -1,   206,   977,    -1,   976,
     977,    -1,  1079,   978,   979,    -1,    -1,   110,  1123,  1079,
      -1,    -1,    93,  1123,  1079,    -1,    -1,   387,  1123,  1079,
      -1,    -1,   144,    -1,   983,    -1,   992,    -1,   994,    -1,
     425,   984,   986,   987,   988,   991,  1132,   985,    -1,    -1,
     184,    -1,  1054,    -1,   203,    -1,   281,    -1,   211,    -1,
     163,    -1,    -1,     8,    -1,    -1,   373,    -1,   160,    -1,
     156,    -1,   160,    -1,   282,    -1,   258,    -1,   260,    -1,
      -1,   300,    -1,   425,  1121,   104,  1132,   993,    -1,  1059,
      -1,     9,   301,    -1,   425,   984,    35,   326,  1079,    -1,
      -1,   437,   996,  1052,   997,   908,   998,  1000,  1001,    -1,
      -1,   176,  1076,    -1,    -1,   999,  1108,  1078,  1127,    -1,
     999,  1108,  1057,    -1,   999,  1108,   286,    -1,    35,    -1,
       8,    -1,    -1,  1023,    -1,  1029,    -1,    -1,   145,    -1,
    1004,  1006,    -1,  1004,  1006,    -1,    -1,    -1,   160,  1005,
     735,    -1,    -1,    -1,   258,  1007,   735,    -1,  1009,  1011,
      -1,    -1,    -1,   366,  1010,   735,    -1,    -1,    -1,   261,
    1012,   735,    -1,  1014,  1016,    -1,    -1,    -1,   282,  1015,
     735,    -1,    -1,    -1,   260,  1017,   735,    -1,  1019,    -1,
    1021,    -1,  1019,  1021,    -1,    -1,   123,  1020,   735,    -1,
      -1,   256,  1022,   735,    -1,  1024,    -1,  1026,    -1,  1024,
    1026,    -1,    -1,   151,  1025,   735,    -1,    -1,   257,  1027,
     735,    -1,    -1,  1029,    -1,  1030,    -1,  1032,    -1,  1030,
    1032,    -1,    -1,   209,  1031,   735,    -1,    -1,   259,  1033,
     735,    -1,    -1,  1115,  1078,  1127,    -1,  1036,    -1,  1037,
      -1,    -1,  1038,  1039,    -1,  1039,   210,    -1,  1040,  1070,
      -1,  1039,   449,    -1,  1039,   272,    -1,  1039,   265,    -1,
    1039,    12,    -1,  1039,    13,    -1,  1039,    14,    -1,  1039,
      58,    -1,  1039,   295,    -1,  1039,   251,    -1,  1039,   440,
      -1,  1039,   255,    -1,    -1,  1040,   210,    -1,  1040,   450,
      -1,  1040,   441,    -1,  1040,   442,    -1,  1040,   446,    -1,
    1040,   255,    -1,  1039,   441,    -1,  1039,   442,    -1,  1039,
     443,    -1,  1039,   444,    -1,  1039,   446,    -1,  1039,  1041,
      -1,  1039,  1042,    -1,  1039,  1043,    -1,  1039,  1044,    -1,
    1039,  1045,    -1,  1039,   250,    -1,  1040,  1041,    -1,  1040,
    1042,    -1,  1040,  1043,    -1,  1040,  1044,    -1,  1040,  1045,
      -1,  1040,   250,    -1,  1039,    20,    -1,  1039,   277,    -1,
     448,    -1,   153,  1147,    -1,   154,    -1,   451,    -1,   187,
    1144,    -1,   452,    -1,   222,  1144,    -1,   181,    -1,   187,
    1144,   277,   153,  1147,    -1,   187,  1144,   153,  1147,    -1,
     218,    -1,   222,  1144,   277,   153,  1147,    -1,   222,  1144,
     153,  1147,    -1,  1048,    -1,  1046,  1047,  1048,    -1,    -1,
      69,    -1,   353,    -1,  1071,    -1,  1048,   441,  1048,    -1,
    1048,   442,  1048,    -1,  1048,   443,  1048,    -1,  1048,   444,
    1048,    -1,   441,  1048,    -1,   442,  1048,    -1,  1048,   446,
    1048,    -1,   450,  1048,   449,    -1,   226,    -1,   226,  1104,
     434,    -1,  1051,    -1,  1050,  1051,    -1,  1070,  1102,    -1,
    1081,    -1,  1081,    -1,  1055,    -1,  1054,  1055,    -1,   434,
      -1,  1057,    -1,  1056,  1057,    -1,   242,    -1,    -1,  1058,
    1059,    -1,  1060,    -1,  1081,    -1,  1061,    -1,  1061,  1104,
    1061,    -1,   230,    -1,  1063,    -1,  1062,  1063,    -1,  1081,
      -1,    -1,  1063,    -1,  1063,    -1,   230,    -1,   434,    -1,
    1068,    -1,  1067,  1068,    -1,  1079,    -1,     6,  1131,  1080,
      -1,  1070,    -1,  1069,  1070,    -1,  1079,    -1,   221,  1131,
    1080,    -1,   221,  1131,  1086,    -1,   221,  1131,  1088,    -1,
       6,  1131,  1072,  1073,    -1,     6,  1131,  1080,    -1,  1085,
      -1,  1088,    -1,  1049,    -1,  1079,    -1,   221,  1131,  1080,
      -1,   221,  1131,  1086,    -1,   221,  1131,  1088,    -1,  1086,
      -1,  1088,    -1,  1049,    -1,   303,    -1,   146,    -1,  1080,
      -1,   230,    -1,  1079,    -1,  1086,    -1,  1079,    -1,  1085,
      -1,  1079,    -1,   230,    -1,  1079,    -1,   230,    -1,  1088,
      -1,  1079,    -1,  1084,    -1,   440,    -1,  1080,    -1,  1081,
      -1,  1081,  1082,    -1,  1081,  1083,    -1,  1081,  1082,  1083,
      -1,   434,    -1,   434,  1104,  1081,    -1,   450,  1046,   449,
      -1,   450,  1048,   453,   449,    -1,   450,  1048,   453,  1048,
     449,    -1,   230,    -1,  1086,    -1,     9,  1087,    -1,  1087,
      -1,  1086,   454,  1087,    -1,   230,    -1,   371,    -1,   440,
      -1,   308,    -1,   191,    -1,   237,    -1,   400,    -1,    96,
    1089,    -1,   431,  1089,    -1,   423,   450,  1048,   449,  1089,
      -1,   235,   450,  1048,   449,  1089,    -1,   335,   450,  1048,
     449,  1089,    -1,    81,   450,  1046,   449,  1089,    -1,   380,
     450,  1046,   449,  1089,    -1,   381,   450,  1046,   449,  1089,
      -1,   405,   450,  1092,   449,  1089,    -1,   267,   450,  1093,
     449,    -1,   232,   450,  1094,   449,  1089,    -1,   180,  1090,
      -1,    -1,   450,  1048,   453,   449,    -1,   450,  1048,   453,
    1048,   449,    -1,    -1,   450,  1091,   449,    -1,    -1,  1046,
      -1,  1048,    -1,  1048,  1047,   219,    -1,  1048,  1047,   403,
      -1,  1048,    -1,  1048,  1047,  1048,    -1,  1048,    -1,  1048,
    1047,  1063,    -1,    -1,    -1,     9,    -1,    -1,  1106,    -1,
      -1,   201,    -1,    -1,   252,    -1,   297,    -1,    -1,   255,
      -1,    -1,   276,    -1,    -1,   341,    -1,    -1,   355,  1116,
      -1,   196,    -1,   270,    -1,   312,  1124,    -1,   314,  1110,
      -1,   433,   119,    -1,   119,    -1,    62,   356,    -1,   356,
      -1,    -1,     7,    -1,    -1,    17,    -1,    -1,    23,    -1,
      -1,    24,    -1,    -1,    27,    -1,    -1,    30,    -1,    -1,
      37,    -1,    -1,    49,    -1,    -1,    55,    -1,    -1,    56,
      -1,    -1,    84,    -1,    -1,    99,    -1,    -1,   398,    -1,
      -1,   172,    -1,    -1,   176,    -1,    -1,   196,    -1,    -1,
     210,    -1,    -1,   210,    -1,    23,    -1,    -1,   214,    -1,
      -1,   227,    -1,   228,    -1,    -1,   228,    -1,    -1,   243,
      -1,    -1,   263,    -1,    -1,   270,    -1,    -1,   273,    -1,
      -1,   278,    -1,   196,   278,    -1,    -1,   280,    -1,    -1,
     303,    -1,    -1,   312,    -1,    -1,   339,    -1,    -1,   358,
      -1,    -1,   360,    -1,    -1,   360,    -1,   360,   210,    -1,
      -1,   365,    -1,    -1,   377,    -1,    -1,   388,    -1,    -1,
     391,    -1,    -1,   392,    -1,    -1,   395,    -1,    -1,   396,
      -1,    -1,   430,    -1,    -1,   433,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   761,   761,   761,   803,   804,   808,   809,   814,   815,
     813,   823,   824,   822,   832,   833,   831,   838,   839,   840,
     843,   844,   870,   894,   924,   923,   964,  1008,  1009,  1013,
    1014,  1017,  1018,  1022,  1029,  1036,  1040,  1044,  1056,  1057,
    1067,  1068,  1077,  1078,  1082,  1083,  1084,  1085,  1094,  1097,
    1098,  1099,  1100,  1104,  1111,  1120,  1123,  1124,  1125,  1126,
    1130,  1131,  1135,  1136,  1137,  1141,  1148,  1149,  1153,  1160,
    1172,  1175,  1176,  1180,  1181,  1185,  1189,  1196,  1197,  1207,
    1210,  1211,  1215,  1216,  1220,  1221,  1222,  1223,  1224,  1225,
    1226,  1227,  1228,  1229,  1230,  1237,  1248,  1247,  1258,  1272,
    1286,  1300,  1316,  1317,  1325,  1326,  1334,  1333,  1345,  1346,
    1347,  1348,  1349,  1357,  1358,  1363,  1364,  1366,  1365,  1377,
    1378,  1382,  1383,  1384,  1385,  1386,  1387,  1391,  1392,  1393,
    1394,  1395,  1396,  1403,  1414,  1426,  1427,  1431,  1432,  1439,
    1448,  1449,  1453,  1454,  1468,  1483,  1550,  1561,  1568,  1575,
    1581,  1588,  1589,  1593,  1592,  1602,  1601,  1617,  1618,  1621,
    1622,  1627,  1626,  1647,  1648,  1652,  1653,  1654,  1655,  1656,
    1657,  1658,  1659,  1660,  1661,  1662,  1663,  1664,  1671,  1675,
    1680,  1687,  1688,  1689,  1692,  1693,  1697,  1704,  1705,  1712,
    1719,  1723,  1724,  1725,  1732,  1752,  1799,  1799,  1803,  1807,
    1823,  1824,  1825,  1831,  1841,  1850,  1852,  1853,  1859,  1863,
    1864,  1865,  1868,  1869,  1870,  1874,  1878,  1879,  1885,  1886,
    1890,  1899,  1908,  1917,  1926,  1941,  1951,  1958,  1962,  2000,
    2007,  2014,  2018,  2019,  2020,  2028,  2029,  2032,  2033,  2037,
    2038,  2042,  2043,  2044,  2050,  2075,  2076,  2077,  2078,  2084,
    2091,  2092,  2096,  2099,  2100,  2106,  2116,  2117,  2131,  2132,
    2132,  2135,  2134,  2147,  2148,  2152,  2164,  2173,  2177,  2178,
    2188,  2187,  2205,  2206,  2210,  2217,  2224,  2225,  2226,  2227,
    2228,  2229,  2230,  2231,  2232,  2239,  2243,  2243,  2243,  2249,
    2261,  2286,  2310,  2311,  2318,  2319,  2323,  2324,  2331,  2338,
    2339,  2346,  2350,  2359,  2360,  2366,  2376,  2394,  2395,  2399,
    2400,  2401,  2405,  2412,  2419,  2429,  2436,  2454,  2458,  2469,
    2470,  2470,  2481,  2482,  2486,  2486,  2503,  2504,  2506,  2510,
    2512,  2511,  2542,  2547,  2552,  2558,  2567,  2575,  2576,  2584,
    2585,  2586,  2590,  2610,  2614,  2623,  2624,  2625,  2626,  2627,
    2628,  2629,  2630,  2631,  2632,  2633,  2634,  2635,  2636,  2643,
    2665,  2687,  2688,  2700,  2720,  2727,  2728,  2732,  2733,  2734,
    2735,  2736,  2737,  2738,  2739,  2740,  2741,  2742,  2743,  2748,
    2753,  2754,  2755,  2756,  2757,  2758,  2759,  2760,  2761,  2762,
    2763,  2764,  2765,  2766,  2767,  2768,  2769,  2770,  2771,  2779,
    2787,  2795,  2802,  2807,  2818,  2835,  2836,  2839,  2840,  2847,
    2871,  2872,  2889,  2890,  2893,  2894,  2901,  2902,  2907,  2917,
    2924,  2927,  2928,  2929,  2936,  2943,  2968,  2968,  2973,  2974,
    2978,  2979,  2982,  2983,  2996,  3008,  3028,  3042,  3044,  3043,
    3063,  3064,  3064,  3077,  3079,  3078,  3090,  3091,  3095,  3096,
    3105,  3112,  3115,  3119,  3123,  3124,  3125,  3132,  3133,  3137,
    3140,  3140,  3143,  3144,  3150,  3155,  3156,  3159,  3160,  3163,
    3164,  3167,  3168,  3171,  3172,  3176,  3177,  3178,  3182,  3183,
    3186,  3187,  3191,  3195,  3196,  3200,  3201,  3202,  3203,  3204,
    3205,  3206,  3207,  3208,  3209,  3210,  3211,  3212,  3213,  3214,
    3215,  3219,  3223,  3224,  3225,  3226,  3227,  3228,  3229,  3233,
    3237,  3238,  3239,  3243,  3244,  3248,  3252,  3257,  3261,  3265,
    3269,  3270,  3274,  3275,  3279,  3280,  3281,  3284,  3284,  3284,
    3287,  3291,  3294,  3294,  3297,  3304,  3305,  3306,  3305,  3323,
    3324,  3328,  3329,  3334,  3336,  3335,  3371,  3372,  3376,  3377,
    3378,  3379,  3380,  3381,  3382,  3383,  3384,  3385,  3386,  3387,
    3388,  3389,  3390,  3391,  3392,  3396,  3400,  3404,  3408,  3409,
    3410,  3411,  3412,  3413,  3414,  3415,  3422,  3426,  3436,  3439,
    3443,  3447,  3451,  3459,  3462,  3466,  3470,  3474,  3482,  3495,
    3497,  3507,  3496,  3534,  3536,  3535,  3542,  3541,  3550,  3551,
    3556,  3563,  3565,  3569,  3579,  3581,  3589,  3597,  3626,  3657,
    3659,  3669,  3674,  3685,  3686,  3686,  3713,  3714,  3718,  3719,
    3720,  3721,  3737,  3749,  3780,  3817,  3829,  3832,  3833,  3842,
    3846,  3842,  3859,  3877,  3881,  3882,  3883,  3884,  3885,  3886,
    3887,  3888,  3889,  3890,  3891,  3892,  3893,  3894,  3895,  3896,
    3897,  3898,  3899,  3900,  3901,  3902,  3903,  3904,  3905,  3906,
    3907,  3908,  3909,  3910,  3911,  3912,  3913,  3914,  3915,  3916,
    3917,  3918,  3919,  3920,  3921,  3922,  3923,  3924,  3925,  3926,
    3927,  3928,  3929,  3930,  3953,  3952,  3965,  3969,  3973,  3977,
    3981,  3985,  3989,  3993,  3997,  4001,  4005,  4009,  4013,  4017,
    4021,  4025,  4029,  4036,  4037,  4038,  4039,  4040,  4041,  4045,
    4049,  4050,  4053,  4054,  4058,  4059,  4063,  4064,  4065,  4066,
    4067,  4068,  4069,  4070,  4074,  4078,  4082,  4087,  4088,  4089,
    4090,  4091,  4092,  4096,  4097,  4106,  4106,  4112,  4116,  4120,
    4126,  4127,  4131,  4132,  4141,  4141,  4146,  4150,  4157,  4158,
    4167,  4173,  4174,  4178,  4178,  4186,  4186,  4196,  4198,  4197,
    4206,  4207,  4212,  4219,  4226,  4228,  4232,  4240,  4251,  4252,
    4253,  4258,  4262,  4261,  4273,  4277,  4276,  4287,  4288,  4297,
    4297,  4301,  4302,  4314,  4314,  4318,  4319,  4330,  4331,  4332,
    4333,  4334,  4337,  4337,  4345,  4345,  4351,  4358,  4359,  4362,
    4362,  4369,  4382,  4395,  4395,  4406,  4407,  4416,  4416,  4436,
    4435,  4448,  4452,  4456,  4460,  4464,  4468,  4472,  4477,  4481,
    4488,  4489,  4490,  4494,  4495,  4500,  4501,  4502,  4503,  4504,
    4505,  4506,  4507,  4508,  4509,  4513,  4517,  4521,  4526,  4527,
    4531,  4532,  4541,  4541,  4547,  4551,  4555,  4559,  4563,  4570,
    4571,  4580,  4580,  4602,  4601,  4620,  4621,  4632,  4641,  4646,
    4654,  4683,  4684,  4690,  4689,  4705,  4709,  4708,  4723,  4724,
    4729,  4730,  4741,  4770,  4771,  4772,  4775,  4776,  4780,  4781,
    4790,  4790,  4795,  4796,  4804,  4821,  4838,  4856,  4881,  4881,
    4894,  4894,  4907,  4907,  4916,  4920,  4933,  4933,  4946,  4948,
    4946,  4959,  4964,  4968,  4967,  4981,  4982,  4991,  4991,  4999,
    5000,  5004,  5005,  5006,  5010,  5011,  5016,  5017,  5022,  5026,
    5027,  5028,  5029,  5030,  5031,  5032,  5036,  5037,  5046,  5046,
    5059,  5058,  5068,  5069,  5070,  5074,  5075,  5079,  5080,  5081,
    5087,  5087,  5092,  5093,  5097,  5098,  5099,  5100,  5101,  5102,
    5108,  5112,  5113,  5117,  5122,  5126,  5127,  5128,  5129,  5130,
    5134,  5160,  5173,  5174,  5178,  5178,  5186,  5186,  5196,  5196,
    5201,  5205,  5217,  5217,  5223,  5227,  5234,  5235,  5244,  5244,
    5248,  5249,  5263,  5264,  5265,  5266,  5270,  5271,  5275,  5276,
    5277,  5289,  5289,  5294,  5299,  5298,  5308,  5315,  5316,  5320,
    5325,  5334,  5337,  5341,  5346,  5353,  5360,  5361,  5365,  5366,
    5371,  5383,  5383,  5406,  5407,  5411,  5412,  5416,  5420,  5424,
    5428,  5435,  5436,  5450,  5451,  5452,  5456,  5457,  5466,  5466,
    5481,  5481,  5492,  5493,  5502,  5502,  5513,  5514,  5518,  5525,
    5526,  5535,  5548,  5548,  5554,  5559,  5558,  5569,  5570,  5574,
    5576,  5575,  5586,  5587,  5592,  5591,  5602,  5603,  5612,  5612,
    5617,  5618,  5619,  5620,  5621,  5627,  5636,  5640,  5649,  5656,
    5657,  5663,  5664,  5668,  5677,  5678,  5682,  5686,  5698,  5698,
    5704,  5703,  5720,  5723,  5739,  5740,  5743,  5744,  5748,  5749,
    5754,  5759,  5767,  5779,  5784,  5792,  5808,  5809,  5808,  5829,
    5830,  5846,  5847,  5848,  5849,  5850,  5854,  5855,  5864,  5864,
    5869,  5876,  5877,  5878,  5887,  5887,  5896,  5897,  5901,  5902,
    5903,  5907,  5908,  5912,  5913,  5922,  5922,  5928,  5932,  5936,
    5943,  5944,  5953,  5960,  5961,  5969,  5969,  5982,  5982,  5998,
    5998,  6007,  6009,  6010,  6019,  6019,  6029,  6030,  6035,  6036,
    6041,  6048,  6049,  6054,  6061,  6062,  6066,  6067,  6071,  6072,
    6076,  6077,  6086,  6087,  6088,  6092,  6116,  6119,  6127,  6137,
    6142,  6147,  6152,  6159,  6160,  6163,  6164,  6168,  6168,  6172,
    6172,  6176,  6176,  6179,  6180,  6184,  6191,  6192,  6196,  6208,
    6208,  6219,  6220,  6225,  6228,  6232,  6236,  6243,  6244,  6247,
    6248,  6249,  6253,  6254,  6267,  6275,  6282,  6284,  6283,  6293,
    6295,  6294,  6309,  6313,  6315,  6314,  6325,  6327,  6326,  6343,
    6349,  6351,  6350,  6360,  6362,  6361,  6377,  6382,  6387,  6397,
    6396,  6408,  6407,  6423,  6428,  6433,  6443,  6442,  6454,  6453,
    6468,  6469,  6473,  6478,  6483,  6493,  6492,  6504,  6503,  6520,
    6523,  6535,  6542,  6549,  6549,  6559,  6560,  6561,  6563,  6564,
    6565,  6566,  6567,  6568,  6570,  6571,  6572,  6574,  6577,  6579,
    6580,  6582,  6583,  6584,  6586,  6588,  6589,  6590,  6591,  6592,
    6594,  6595,  6596,  6597,  6598,  6599,  6601,  6602,  6603,  6604,
    6605,  6606,  6608,  6609,  6612,  6612,  6612,  6613,  6613,  6614,
    6614,  6615,  6615,  6615,  6616,  6616,  6616,  6621,  6622,  6625,
    6626,  6627,  6631,  6632,  6633,  6634,  6635,  6636,  6637,  6638,
    6639,  6650,  6662,  6677,  6678,  6683,  6689,  6695,  6715,  6719,
    6735,  6749,  6750,  6755,  6761,  6762,  6767,  6776,  6777,  6778,
    6782,  6793,  6794,  6798,  6806,  6807,  6811,  6812,  6818,  6838,
    6839,  6843,  6844,  6848,  6849,  6853,  6854,  6855,  6856,  6857,
    6858,  6859,  6860,  6861,  6865,  6866,  6867,  6868,  6869,  6870,
    6871,  6875,  6876,  6880,  6881,  6885,  6886,  6890,  6891,  6902,
    6903,  6907,  6908,  6909,  6913,  6914,  6915,  6923,  6927,  6928,
    6929,  6930,  6934,  6935,  6939,  6949,  6967,  6994,  7006,  7007,
    7017,  7018,  7022,  7023,  7024,  7025,  7026,  7027,  7028,  7036,
    7040,  7044,  7048,  7052,  7056,  7060,  7064,  7068,  7072,  7076,
    7080,  7087,  7088,  7089,  7093,  7094,  7098,  7099,  7104,  7111,
    7118,  7128,  7135,  7145,  7152,  7166,  7176,  7177,  7181,  7182,
    7186,  7187,  7191,  7192,  7193,  7197,  7198,  7202,  7203,  7207,
    7208,  7212,  7213,  7220,  7220,  7221,  7221,  7222,  7222,  7223,
    7223,  7225,  7225,  7226,  7226,  7227,  7227,  7228,  7228,  7229,
    7229,  7230,  7230,  7231,  7231,  7232,  7232,  7233,  7233,  7234,
    7234,  7235,  7235,  7236,  7236,  7237,  7237,  7238,  7238,  7239,
    7239,  7240,  7240,  7241,  7241,  7242,  7242,  7242,  7243,  7243,
    7244,  7244,  7244,  7245,  7245,  7246,  7246,  7247,  7247,  7248,
    7248,  7249,  7249,  7250,  7250,  7250,  7251,  7251,  7252,  7252,
    7253,  7253,  7254,  7254,  7255,  7255,  7256,  7256,  7257,  7257,
    7257,  7258,  7258,  7259,  7259,  7260,  7260,  7261,  7261,  7262,
    7262,  7263,  7263,  7264,  7264,  7266,  7266,  7267,  7267
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
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
  "CLASS_NAME", "CLOSE", "CODE", "\"CODE-SET\"", "COLLATING", "COL",
  "COLS", "COLUMN", "COLUMNS", "COMMA", "\"COMMAND-LINE\"",
  "\"comma delimiter\"", "COMMIT", "\"COMMITMENT-CONTROL\"", "COMMON",
  "COMP", "COMPUTE", "\"COMP-1\"", "\"COMP-2\"", "\"COMP-3\"",
  "\"COMP-4\"", "\"COMP-5\"", "\"COMP-X\"", "\"FUNCTION CONCATENATE\"",
  "CONFIGURATION", "CONSTANT", "CONTAINS", "CONTENT", "CONTINUE",
  "CONTROL", "CONTROLS", "\"CONTROL FOOTING\"", "\"CONTROL HEADING\"",
  "CONVERTING", "CORRESPONDING", "COUNT", "CRT", "CURRENCY",
  "\"FUNCTION CURRENT-DATE\"", "CURSOR", "CYCLE", "DATA", "DATE", "DAY",
  "\"DAY-OF-WEEK\"", "DE", "DEBUGGING", "\"DECIMAL-POINT\"",
  "DECLARATIVES", "DEFAULT", "DELETE", "DELIMITED", "DELIMITER",
  "DEPENDING", "DESCENDING", "DETAIL", "DISK", "DISPLAY", "DIVIDE",
  "DIVISION", "DOWN", "DUPLICATES", "DYNAMIC", "EBCDIC", "ELSE", "END",
  "\"END-ACCEPT\"", "\"END-ADD\"", "\"END-CALL\"", "\"END-COMPUTE\"",
  "\"END-DELETE\"", "\"END-DISPLAY\"", "\"END-DIVIDE\"",
  "\"END-EVALUATE\"", "\"END FUNCTION\"", "\"END-IF\"", "\"END-MULTIPLY\"",
  "\"END-PERFORM\"", "\"END PROGRAM\"", "\"END-READ\"", "\"END-RETURN\"",
  "\"END-REWRITE\"", "\"END-SEARCH\"", "\"END-START\"", "\"END-STRING\"",
  "\"END-SUBTRACT\"", "\"END-UNSTRING\"", "\"END-WRITE\"", "ENTRY",
  "ENVIRONMENT", "\"ENVIRONMENT-NAME\"", "\"ENVIRONMENT-VALUE\"", "EOL",
  "EOP", "EOS", "EQUAL", "EQUALS", "ERASE", "ERROR", "ESCAPE", "EVALUATE",
  "\"EVENT-STATUS\"", "EXCEPTION", "EXCLUSIVE", "EXIT", "EXTEND",
  "EXTERNAL", "FD", "\"FILE-CONTROL\"", "\"FILE-ID\"", "FILLER", "FINAL",
  "FIRST", "FOOTING", "FOR", "\"FOREGROUND-COLOR\"", "FOREVER", "FREE",
  "FROM", "FULL", "FUNCTION", "\"FUNCTION-ID\"", "\"FUNCTION\"", "GE",
  "GENERATE", "GIVING", "GLOBAL", "GO", "GOBACK", "GREATER", "GROUP",
  "HEADING", "HIGHLIGHT", "\"HIGH-VALUE\"", "IDENTIFICATION", "IF",
  "IGNORE", "IGNORING", "IN", "INDEX", "INDEXED", "INDICATE", "INITIALIZE",
  "INITIALIZED", "INITIATE", "INPUT", "\"INPUT-OUTPUT\"", "INSPECT",
  "INTO", "INTRINSIC", "INVALID", "\"INVALID KEY\"", "IS", "\"I-O\"",
  "\"I-O-CONTROL\"", "JUSTIFIED", "KEY", "LABEL", "LAST",
  "\"LAST DETAIL\"", "LE", "LEADING", "LEFT", "LENGTH", "LESS", "LIMIT",
  "LIMITS", "LINAGE", "\"LINAGE-COUNTER\"", "LINE", "LINES", "LINKAGE",
  "\"Literal\"", "LOCALE", "\"FUNCTION LOCALE\"", "\"LOCAL-STORAGE\"",
  "LOCK", "\"FUNCTION LOWER-CASE\"", "LOWLIGHT", "\"LOW-VALUE\"", "MANUAL",
  "MEMORY", "MERGE", "MINUS", "\"MNEMONIC NAME\"", "MODE", "MOVE",
  "MULTIPLE", "MULTIPLY", "NATIONAL", "\"NATIONAL-EDITED\"", "NATIVE",
  "NE", "NEGATIVE", "NEXT", "\"NEXT SENTENCE\"", "NO", "NOT",
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
  "TRAILING", "TRANSFORM", "\"FUNCTION TRIM\"", "TYPE", "UNDERLINE",
  "UNIT", "UNLOCK", "UNSIGNED", "\"UNSIGNED-INT\"", "\"UNSIGNED-LONG\"",
  "\"UNSIGNED-SHORT\"", "UNSTRING", "UNTIL", "UP", "UPDATE", "UPON",
  "\"UPON ARGUMENT-NUMBER\"", "\"UPON COMMAND-LINE\"",
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
  "mnemonic_name_clause", "$@9", "special_name_mnemonic_on_off",
  "on_or_off", "alphabet_name_clause", "$@10", "alphabet_definition",
  "alphabet_literal_list", "alphabet_literal", "@11",
  "alphabet_also_sequence", "alphabet_lits", "alphabet_also_literal",
  "symbolic_characters_clause", "symbolic_characters_list", "char_list",
  "integer_list", "class_name_clause", "class_item_list", "class_item",
  "locale_clause", "currency_sign_clause", "decimal_point_clause",
  "cursor_clause", "crt_status_clause", "screen_control", "event_status",
  "input_output_section", "$@12", "$@13", "file_control_paragraph",
  "file_control_sequence", "file_control_entry", "$@14",
  "select_clause_sequence", "select_clause", "assign_clause", "_device",
  "_ext_clause", "assignment_name", "access_mode_clause", "access_mode",
  "alternative_record_key_clause", "split_key_list", "$@15", "split_key",
  "key_is_eq", "collating_sequence_clause", "file_status_clause",
  "file_or_sort", "lock_mode_clause", "lock_mode", "lock_with",
  "lock_records", "organization_clause", "organization",
  "padding_character_clause", "record_delimiter_clause",
  "record_key_clause", "relative_key_clause", "reserve_clause",
  "sharing_clause", "sharing_option", "i_o_control_paragraph",
  "opt_i_o_control", "i_o_control_list", "i_o_control_clause",
  "same_clause", "same_option", "multiple_file_tape_clause",
  "multiple_file_list", "multiple_file", "multiple_file_position",
  "commitment_control_clause", "data_division", "file_section", "$@16",
  "$@17", "file_description_sequence", "file_description",
  "file_description_sequence_without_type", "file_type",
  "file_description_entry", "@18", "file_description_clause_sequence",
  "file_description_clause", "block_contains_clause",
  "_records_or_characters", "record_clause", "record_depending",
  "opt_from_integer", "opt_to_integer", "label_records_clause",
  "label_option", "value_of_clause", "valueof_name", "data_records_clause",
  "linage_clause", "linage_sequence", "linage_lines", "linage_footing",
  "linage_top", "linage_bottom", "recording_mode_clause",
  "code_set_clause", "report_clause", "working_storage_section", "$@19",
  "record_description_list", "record_description_list_1", "$@20",
  "record_description_list_2", "data_description", "$@21", "level_number",
  "entry_name", "const_name", "const_global", "lit_or_length",
  "constant_entry", "data_description_clause_sequence",
  "data_description_clause", "redefines_clause", "external_clause",
  "as_extname", "global_clause", "picture_clause", "usage_clause", "usage",
  "sign_clause", "occurs_clause", "occurs_to_integer", "occurs_depending",
  "occurs_keys", "occurs_key_list", "ascending_or_descending",
  "occurs_indexed", "occurs_index_list", "occurs_index",
  "justified_clause", "synchronized_clause", "left_or_right",
  "blank_clause", "based_clause", "value_clause", "$@22",
  "value_item_list", "value_item", "false_is", "renames_clause",
  "any_length_clause", "local_storage_section", "$@23", "linkage_section",
  "$@24", "report_section", "$@25", "opt_report_description_list",
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
  "_indicate", "report_name", "screen_section", "$@26", "$@27",
  "opt_screen_description_list", "screen_description_list",
  "screen_description", "$@28", "screen_options", "screen_option",
  "screen_line_plus_minus", "screen_col_plus_minus",
  "screen_occurs_clause", "procedure_division", "$@29", "$@30",
  "procedure_using_chaining", "$@31", "$@32", "procedure_param_list",
  "procedure_param", "procedure_type", "size_optional",
  "procedure_optional", "procedure_returning", "procedure_declaratives",
  "$@33", "procedure_list", "procedure", "section_header",
  "paragraph_header", "invalid_statement", "section_name", "opt_segment",
  "statement_list", "@34", "@35", "statements", "statement",
  "accept_statement", "$@36", "accept_body", "opt_at_line_column",
  "line_number", "column_number", "opt_accp_attr", "accp_attrs",
  "accp_attr", "end_accept", "add_statement", "$@37", "add_body", "add_to",
  "end_add", "allocate_statement", "$@38", "allocate_body",
  "allocate_returning", "alter_statement", "alter_options", "_proceed_to",
  "call_statement", "$@39", "call_using", "$@40", "call_param_list",
  "call_param", "call_type", "call_returning", "call_on_exception", "$@41",
  "call_not_on_exception", "$@42", "end_call", "cancel_statement", "$@43",
  "cancel_list", "close_statement", "$@44", "close_list", "close_option",
  "reel_or_unit", "compute_statement", "$@45", "compute_body",
  "end_compute", "comp_equal", "commit_statement", "continue_statement",
  "delete_statement", "$@46", "end_delete", "delete_file_statement",
  "$@47", "display_statement", "$@48", "display_body", "with_clause",
  "disp_attrs", "disp_attr", "end_display", "divide_statement", "$@49",
  "divide_body", "end_divide", "entry_statement", "$@50",
  "evaluate_statement", "$@51", "evaluate_subject_list",
  "evaluate_subject", "evaluate_condition_list", "evaluate_case_list",
  "evaluate_case", "$@52", "evaluate_other", "$@53", "evaluate_when_list",
  "evaluate_object_list", "evaluate_object", "opt_evaluate_thru_expr",
  "end_evaluate", "exit_statement", "$@54", "exit_body", "free_statement",
  "$@55", "generate_statement", "$@56", "goto_statement", "$@57",
  "goto_depending", "goback_statement", "$@58", "if_statement", "$@59",
  "$@60", "if_else_sentence", "$@61", "end_if", "initialize_statement",
  "$@62", "initialize_filler", "initialize_value", "initialize_replacing",
  "initialize_replacing_list", "initialize_replacing_item",
  "initialize_category", "initialize_default", "initiate_statement",
  "$@63", "inspect_statement", "$@64", "send_identifier", "inspect_list",
  "inspect_item", "inspect_tallying", "$@65", "tallying_list",
  "tallying_item", "inspect_replacing", "replacing_list", "replacing_item",
  "rep_keyword", "replacing_region", "inspect_converting",
  "inspect_region", "_initial", "merge_statement", "$@66",
  "move_statement", "$@67", "move_body", "multiply_statement", "$@68",
  "multiply_body", "end_multiply", "open_statement", "$@69", "open_list",
  "open_mode", "open_sharing", "open_option", "perform_statement", "$@70",
  "perform_body", "$@71", "end_perform", "perform_procedure",
  "perform_option", "perform_test", "perform_varying_list",
  "perform_varying", "read_statement", "$@72", "read_into", "with_lock",
  "read_key", "read_handler", "end_read", "release_statement", "$@73",
  "return_statement", "$@74", "end_return", "rewrite_statement", "$@75",
  "write_lock", "end_rewrite", "rollback_statement", "search_statement",
  "$@76", "search_body", "$@77", "search_varying", "search_at_end", "$@78",
  "search_whens", "search_when", "$@79", "end_search", "set_statement",
  "$@80", "set_body", "set_environment", "set_to", "set_up_down",
  "up_or_down", "set_to_on_off_sequence", "set_to_on_off",
  "set_to_true_false_sequence", "set_to_true_false", "sort_statement",
  "$@81", "sort_body", "$@82", "sort_key_list", "opt_key_list",
  "sort_duplicates", "sort_collating", "sort_input", "sort_output",
  "start_statement", "$@83", "@84", "start_key", "start_op", "end_start",
  "stop_statement", "$@85", "stop_returning", "string_statement", "$@86",
  "string_item_list", "string_item", "opt_with_pointer", "end_string",
  "subtract_statement", "$@87", "subtract_body", "end_subtract",
  "suppress_statement", "_printing", "terminate_statement", "$@88",
  "transform_statement", "$@89", "unlock_statement", "$@90", "opt_record",
  "unstring_statement", "$@91", "unstring_delimited",
  "unstring_delimited_list", "unstring_delimited_item", "unstring_into",
  "unstring_into_item", "unstring_into_delimiter", "unstring_into_count",
  "unstring_tallying", "end_unstring", "use_statement", "use_exception",
  "use_global", "use_exception_target", "_after", "_standard",
  "exception_or_error", "exception_or_overflow",
  "not_exception_or_overflow", "_procedure", "use_debugging",
  "use_debugging_target", "use_reporting", "write_statement", "$@92",
  "write_from", "write_option", "before_or_after", "write_handler",
  "end_write", "on_accp_exception", "on_disp_exception",
  "opt_on_exception", "$@93", "opt_not_on_exception", "$@94",
  "on_size_error", "opt_on_size_error", "$@95", "opt_not_on_size_error",
  "$@96", "on_overflow", "opt_on_overflow", "$@97", "opt_not_on_overflow",
  "$@98", "at_end", "at_end_sentence", "$@99", "not_at_end_sentence",
  "$@100", "at_eop", "at_eop_sentence", "$@101", "not_at_eop_sentence",
  "$@102", "opt_invalid_key", "invalid_key", "invalid_key_sentence",
  "$@103", "not_invalid_key_sentence", "$@104", "_opt_scroll_lines",
  "condition", "expr", "partial_expr", "$@105", "expr_tokens",
  "expr_token", "eq", "gt", "lt", "ge", "le", "exp_list", "e_sep", "exp",
  "linage_counter", "arithmetic_x_list", "arithmetic_x", "record_name",
  "table_name", "file_name_list", "file_name", "mnemonic_name_list",
  "mnemonic_name", "procedure_name_list", "procedure_name", "label",
  "integer_label", "reference_list", "reference", "opt_reference",
  "reference_or_literal", "undefined_word", "target_x_list", "target_x",
  "x_list", "x", "arith_x", "prog_or_entry", "alnum_or_id", "simple_value",
  "simple_all_value", "id_or_lit", "id_or_lit_or_func", "num_id_or_lit",
  "identifier", "identifier_1", "qualified_word", "subref", "refmod",
  "integer", "literal", "basic_literal", "basic_value", "function",
  "func_refmod", "func_args", "list_func_args", "trim_args",
  "numvalc_args", "locale_dt_args", "not_const_word", "flag_all",
  "flag_duplicates", "flag_initialized", "flag_next", "flag_not",
  "flag_optional", "flag_rounded", "flag_separate", "in_of", "records",
  "with_dups", "coll_sequence", "_advancing", "_also", "_are", "_area",
  "_as", "_at", "_binary", "_by", "_character", "_characters", "_contains",
  "_data", "_file", "_for", "_from", "_in", "_is", "_is_are", "_key",
  "_line_or_lines", "_lines", "_mode", "_number", "_of", "_on",
  "_in_order", "_other", "_program", "_record", "_right", "_set", "_sign",
  "_sign_is", "_size", "_status", "_tape", "_than", "_then", "_times",
  "_to", "_when", "_with", 0
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
     695,    43,    45,    42,    47,   696,    94,    46,    61,    41,
      40,    62,    60,    58,    38
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   455,   457,   456,   458,   458,   459,   459,   461,   462,
     460,   464,   465,   463,   467,   468,   466,   469,   469,   469,
     470,   470,   471,   472,   474,   473,   475,   476,   476,   477,
     477,   478,   478,   479,   479,   479,   480,   480,   481,   481,
     482,   482,   483,   483,   484,   484,   484,   484,   485,   486,
     486,   486,   486,   487,   488,   489,   490,   490,   490,   490,
     491,   491,   492,   492,   492,   493,   494,   494,   495,   496,
     497,   498,   498,   499,   499,   500,   500,   501,   501,   502,
     503,   503,   504,   504,   505,   505,   505,   505,   505,   505,
     505,   505,   505,   505,   505,   506,   507,   506,   506,   506,
     506,   506,   508,   508,   509,   509,   511,   510,   512,   512,
     512,   512,   512,   513,   513,   514,   514,   515,   514,   516,
     516,   517,   517,   517,   517,   517,   517,   518,   518,   518,
     518,   518,   518,   519,   520,   521,   521,   522,   522,   523,
     524,   524,   525,   525,   526,   527,   528,   529,   530,   531,
     532,   533,   533,   534,   533,   535,   533,   536,   536,   537,
     537,   539,   538,   540,   540,   541,   541,   541,   541,   541,
     541,   541,   541,   541,   541,   541,   541,   541,   542,   542,
     542,   543,   543,   543,   544,   544,   544,   545,   545,   545,
     546,   547,   547,   547,   548,   548,   550,   549,   549,   551,
     552,   552,   552,   553,   554,   555,   555,   555,   556,   557,
     557,   557,   558,   558,   558,   558,   559,   559,   560,   560,
     561,   561,   561,   561,   561,   562,   563,   564,   564,   565,
     566,   567,   568,   568,   568,   569,   569,   570,   570,   571,
     571,   572,   572,   572,   573,   574,   574,   574,   574,   575,
     576,   576,   577,   578,   578,   579,   580,   580,   581,   582,
     581,   583,   581,   584,   584,   585,   586,   586,   587,   587,
     589,   588,   590,   590,   591,   591,   591,   591,   591,   591,
     591,   591,   591,   591,   591,   592,   593,   593,   593,   594,
     594,   594,   595,   595,   596,   596,   597,   597,   598,   599,
     599,   600,   600,   601,   601,   602,   603,   604,   604,   605,
     605,   605,   606,   607,   608,   609,   610,   611,   611,   612,
     613,   612,   614,   614,   616,   615,   617,   617,   617,   618,
     619,   618,   620,   621,   621,   621,   622,   623,   623,   624,
     624,   624,   625,   626,   626,   627,   627,   627,   627,   627,
     627,   627,   627,   627,   627,   627,   627,   627,   627,   628,
     629,   630,   630,   631,   632,   633,   633,   634,   634,   634,
     634,   634,   634,   634,   634,   634,   634,   634,   634,   634,
     634,   634,   634,   634,   634,   634,   634,   634,   634,   634,
     634,   634,   634,   634,   634,   634,   634,   634,   634,   634,
     634,   634,   635,   635,   636,   637,   637,   638,   638,   639,
     640,   640,   641,   641,   642,   642,   643,   643,   644,   645,
     646,   647,   647,   647,   648,   649,   651,   650,   652,   652,
     653,   653,   654,   654,   655,   655,   656,   657,   658,   657,
     659,   660,   659,   661,   662,   661,   663,   663,   664,   664,
     665,   666,   666,   667,   667,   667,   667,   668,   668,   669,
     670,   670,   671,   671,   672,   673,   673,   674,   674,   675,
     675,   676,   676,   677,   677,   678,   678,   678,   679,   679,
     680,   680,   681,   682,   682,   683,   683,   683,   683,   683,
     683,   683,   683,   683,   683,   683,   683,   683,   683,   683,
     683,   684,   685,   685,   685,   685,   685,   685,   685,   686,
     687,   687,   687,   688,   688,   689,   690,   691,   692,   693,
     694,   694,   695,   695,   696,   696,   696,   697,   697,   697,
     698,   699,   700,   700,   701,   702,   703,   704,   702,   705,
     705,   706,   706,   707,   708,   707,   709,   709,   710,   710,
     710,   710,   710,   710,   710,   710,   710,   710,   710,   710,
     710,   710,   710,   710,   710,   710,   710,   710,   710,   710,
     710,   710,   710,   710,   710,   710,   710,   710,   711,   711,
     711,   711,   711,   712,   712,   712,   712,   712,   713,   714,
     715,   716,   714,   717,   718,   717,   719,   717,   720,   720,
     721,   722,   722,   722,   723,   723,   723,   723,   723,   724,
     724,   725,   725,   726,   727,   726,   728,   728,   729,   729,
     729,   729,   729,   730,   731,   732,   733,   734,   734,   736,
     737,   735,   738,   738,   739,   739,   739,   739,   739,   739,
     739,   739,   739,   739,   739,   739,   739,   739,   739,   739,
     739,   739,   739,   739,   739,   739,   739,   739,   739,   739,
     739,   739,   739,   739,   739,   739,   739,   739,   739,   739,
     739,   739,   739,   739,   739,   739,   739,   739,   739,   739,
     739,   739,   739,   739,   741,   740,   742,   742,   742,   742,
     742,   742,   742,   742,   742,   742,   742,   742,   742,   742,
     742,   742,   742,   743,   743,   743,   743,   743,   743,   744,
     745,   745,   746,   746,   747,   747,   748,   748,   748,   748,
     748,   748,   748,   748,   748,   748,   748,   748,   748,   748,
     748,   748,   748,   749,   749,   751,   750,   752,   752,   752,
     753,   753,   754,   754,   756,   755,   757,   757,   758,   758,
     759,   760,   760,   761,   761,   763,   762,   764,   765,   764,
     766,   766,   767,   767,   768,   768,   768,   768,   769,   769,
     769,   770,   771,   770,   772,   773,   772,   774,   774,   776,
     775,   777,   777,   779,   778,   780,   780,   781,   781,   781,
     781,   781,   782,   782,   784,   783,   785,   786,   786,   787,
     787,   788,   789,   791,   790,   792,   792,   794,   793,   796,
     795,   797,   797,   797,   797,   797,   797,   797,   797,   797,
     798,   798,   798,   799,   799,   800,   800,   800,   800,   800,
     800,   800,   800,   800,   800,   800,   800,   800,   800,   800,
     801,   801,   803,   802,   804,   804,   804,   804,   804,   805,
     805,   807,   806,   809,   808,   810,   810,   811,   811,   811,
     812,   813,   813,   815,   814,   816,   817,   816,   818,   818,
     819,   819,   820,   820,   820,   820,   821,   821,   822,   822,
     824,   823,   825,   825,   825,   825,   825,   825,   827,   826,
     829,   828,   831,   830,   832,   832,   834,   833,   836,   837,
     835,   835,   838,   839,   838,   840,   840,   842,   841,   843,
     843,   844,   844,   844,   845,   845,   846,   846,   847,   848,
     848,   848,   848,   848,   848,   848,   849,   849,   851,   850,
     853,   852,   854,   854,   854,   855,   855,   856,   856,   856,
     858,   857,   859,   859,   860,   860,   860,   860,   860,   860,
     861,   862,   862,   863,   863,   864,   864,   864,   864,   864,
     865,   866,   867,   867,   868,   868,   870,   869,   872,   871,
     873,   873,   875,   874,   876,   876,   877,   877,   879,   878,
     880,   880,   881,   881,   881,   881,   882,   882,   883,   883,
     883,   885,   884,   886,   887,   886,   886,   888,   888,   889,
     889,   890,   890,   890,   890,   890,   891,   891,   892,   892,
     893,   895,   894,   896,   896,   897,   897,   897,   897,   897,
     897,   898,   898,   899,   899,   899,   900,   900,   902,   901,
     904,   903,   905,   905,   907,   906,   908,   908,   908,   909,
     909,   910,   912,   911,   913,   914,   913,   915,   915,   916,
     917,   916,   918,   918,   920,   919,   921,   921,   923,   922,
     924,   924,   924,   924,   924,   925,   926,   926,   927,   928,
     928,   929,   929,   930,   931,   931,   932,   932,   934,   933,
     936,   935,   937,   937,   938,   938,   939,   939,   940,   940,
     941,   941,   941,   942,   942,   942,   944,   945,   943,   946,
     946,   947,   947,   947,   947,   947,   948,   948,   950,   949,
     949,   951,   951,   951,   953,   952,   954,   954,   955,   955,
     955,   956,   956,   957,   957,   959,   958,   960,   960,   960,
     961,   961,   962,   963,   963,   965,   964,   967,   966,   969,
     968,   970,   970,   970,   972,   971,   973,   973,   974,   974,
     975,   976,   976,   977,   978,   978,   979,   979,   980,   980,
     981,   981,   982,   982,   982,   983,   984,   984,   985,   985,
     985,   985,   985,   986,   986,   987,   987,   988,   988,   989,
     989,   990,   990,   991,   991,   992,   993,   993,   994,   996,
     995,   997,   997,   998,   998,   998,   998,   999,   999,  1000,
    1000,  1000,  1001,  1001,  1002,  1003,  1004,  1005,  1004,  1006,
    1007,  1006,  1008,  1009,  1010,  1009,  1011,  1012,  1011,  1013,
    1014,  1015,  1014,  1016,  1017,  1016,  1018,  1018,  1018,  1020,
    1019,  1022,  1021,  1023,  1023,  1023,  1025,  1024,  1027,  1026,
    1028,  1028,  1029,  1029,  1029,  1031,  1030,  1033,  1032,  1034,
    1034,  1035,  1036,  1038,  1037,  1039,  1039,  1039,  1039,  1039,
    1039,  1039,  1039,  1039,  1039,  1039,  1039,  1039,  1040,  1040,
    1040,  1040,  1040,  1040,  1040,  1040,  1040,  1040,  1040,  1040,
    1040,  1040,  1040,  1040,  1040,  1040,  1040,  1040,  1040,  1040,
    1040,  1040,  1040,  1040,  1041,  1041,  1041,  1042,  1042,  1043,
    1043,  1044,  1044,  1044,  1045,  1045,  1045,  1046,  1046,  1047,
    1047,  1047,  1048,  1048,  1048,  1048,  1048,  1048,  1048,  1048,
    1048,  1049,  1049,  1050,  1050,  1051,  1052,  1053,  1054,  1054,
    1055,  1056,  1056,  1057,  1058,  1058,  1059,  1060,  1060,  1060,
    1061,  1062,  1062,  1063,  1064,  1064,  1065,  1065,  1066,  1067,
    1067,  1068,  1068,  1069,  1069,  1070,  1070,  1070,  1070,  1070,
    1070,  1070,  1070,  1070,  1071,  1071,  1071,  1071,  1071,  1071,
    1071,  1072,  1072,  1073,  1073,  1074,  1074,  1075,  1075,  1076,
    1076,  1077,  1077,  1077,  1078,  1078,  1078,  1079,  1080,  1080,
    1080,  1080,  1081,  1081,  1082,  1083,  1083,  1084,  1085,  1085,
    1086,  1086,  1087,  1087,  1087,  1087,  1087,  1087,  1087,  1088,
    1088,  1088,  1088,  1088,  1088,  1088,  1088,  1088,  1088,  1088,
    1088,  1089,  1089,  1089,  1090,  1090,  1091,  1091,  1092,  1092,
    1092,  1093,  1093,  1094,  1094,  1095,  1096,  1096,  1097,  1097,
    1098,  1098,  1099,  1099,  1099,  1100,  1100,  1101,  1101,  1102,
    1102,  1103,  1103,  1104,  1104,  1105,  1105,  1106,  1106,  1107,
    1107,  1108,  1108,  1109,  1109,  1110,  1110,  1111,  1111,  1112,
    1112,  1113,  1113,  1114,  1114,  1115,  1115,  1116,  1116,  1117,
    1117,  1118,  1118,  1119,  1119,  1120,  1120,  1121,  1121,  1122,
    1122,  1123,  1123,  1124,  1124,  1125,  1125,  1125,  1126,  1126,
    1127,  1127,  1127,  1128,  1128,  1129,  1129,  1130,  1130,  1131,
    1131,  1132,  1132,  1133,  1133,  1133,  1134,  1134,  1135,  1135,
    1136,  1136,  1137,  1137,  1138,  1138,  1139,  1139,  1140,  1140,
    1140,  1141,  1141,  1142,  1142,  1143,  1143,  1144,  1144,  1145,
    1145,  1146,  1146,  1147,  1147,  1148,  1148,  1149,  1149
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     1,     1,     0,     0,
       8,     0,     0,     8,     0,     0,     7,     0,     1,     2,
       0,     3,     3,     3,     0,     7,     5,     1,     1,     0,
       2,     0,     3,     1,     2,     1,     1,     1,     0,     5,
       0,     4,     0,     2,     1,     1,     1,     1,     3,     0,
       2,     3,     2,     3,     1,     3,     0,     2,     3,     2,
       1,     2,     1,     1,     1,     5,     1,     1,     4,     3,
       3,     0,     2,     1,     2,     3,     3,     1,     2,     3,
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     5,     3,     3,
       3,     3,     0,     5,     1,     1,     0,     5,     1,     1,
       1,     1,     1,     1,     2,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     2,     1,     2,     4,
       1,     2,     1,     3,     4,     4,     3,     3,     4,     3,
       3,     0,     5,     0,     4,     0,     4,     0,     3,     0,
       2,     0,     6,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     4,
       4,     0,     1,     1,     0,     1,     1,     1,     1,     1,
       4,     1,     1,     1,     6,     8,     0,     2,     2,     1,
       0,     2,     1,     3,     5,     0,     1,     1,     4,     2,
       2,     1,     0,     4,     5,     2,     1,     1,     3,     1,
       1,     3,     1,     1,     2,     4,     4,     4,     6,     4,
       3,     3,     2,     2,     2,     0,     3,     0,     2,     1,
       2,     1,     1,     1,     5,     0,     1,     1,     1,     5,
       1,     2,     2,     0,     2,     4,     0,     9,     0,     0,
       5,     0,     3,     0,     2,     3,     2,     2,     1,     1,
       0,     4,     0,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     0,     1,     1,     4,
       6,     9,     0,     3,     0,     2,     0,     2,     3,     1,
       1,     5,     5,     1,     1,     3,     5,     0,     2,     1,
       1,     1,     5,     4,     3,     4,     3,     3,     3,     0,
       0,     5,     0,     1,     0,     2,     3,     4,     2,     1,
       0,     4,     1,     0,     1,     1,     1,     0,     2,     1,
       3,     3,     6,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     0,     2,     2,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     1,     2,
       2,     1,     2,     2,     1,     2,     2,     1,     2,     2,
       1,     1,     3,     3,     7,     0,     2,     0,     3,     1,
       0,     5,     1,     1,     0,     3,     1,     2,     1,     2,
       2,     0,     1,     1,     3,     1,     0,     8,     1,     2,
       1,     3,     0,     3,     2,     4,     2,     0,     0,     5,
       0,     0,     5,     0,     0,     5,     0,     1,     1,     2,
       5,     0,     2,     2,     3,     1,     1,     2,     2,     2,
       0,     1,     1,     2,     8,     0,     3,     0,     4,     0,
       4,     0,     3,     0,     3,     1,     4,     2,     1,     1,
       0,     2,     4,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     4,
       4,     2,     1,     1,     2,     3,     1,     3,     6,     2,
       3,     2,     1,     2,     2,     1,     2,     0,     1,     1,
       4,     2,     0,     1,     1,     0,     0,     0,     6,     0,
       1,     1,     2,     1,     0,     5,     0,     2,     1,     1,
       1,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     5,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     0,     1,
       1,     1,     1,     0,     1,     1,     1,     1,     3,     0,
       0,     0,     9,     0,     0,     3,     0,     3,     1,     2,
       4,     0,     2,     2,     0,     3,     3,     4,     3,     0,
       1,     0,     2,     0,     0,     7,     0,     2,     1,     1,
       1,     2,     2,     4,     2,     1,     1,     0,     1,     0,
       0,     3,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     4,     4,     3,     3,
       3,     4,     3,     4,     3,     3,     3,     4,     5,     3,
       4,     3,     3,     0,     3,     3,     2,     2,     2,     3,
       3,     3,     0,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     0,     1,     0,     4,     4,     5,     6,
       0,     2,     0,     1,     0,     3,     3,     5,     0,     2,
       2,     0,     5,     0,     2,     0,     8,     0,     0,     3,
       1,     2,     2,     3,     0,     2,     2,     2,     0,     2,
       2,     0,     0,     3,     0,     0,     3,     0,     1,     0,
       3,     0,     2,     0,     3,     0,     3,     0,     1,     3,
       3,     2,     1,     1,     0,     4,     4,     0,     1,     1,
       1,     1,     1,     0,     6,     0,     1,     0,     4,     0,
       4,     3,     3,     3,     3,     4,     6,     6,     6,     6,
       0,     2,     2,     1,     2,     1,     1,     2,     2,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     1,     1,
       0,     1,     0,     4,     4,     6,     6,     8,     8,     0,
       1,     0,     4,     0,     5,     1,     3,     1,     1,     1,
       2,     1,     2,     0,     3,     0,     0,     3,     2,     3,
       1,     3,     2,     1,     1,     1,     0,     2,     0,     1,
       0,     3,     0,     1,     1,     2,     1,     1,     0,     3,
       0,     3,     0,     5,     0,     3,     0,     2,     0,     0,
       8,     3,     0,     0,     3,     0,     1,     0,     7,     0,
       2,     0,     3,     3,     0,     2,     1,     2,     4,     1,
       1,     1,     1,     1,     1,     1,     0,     1,     0,     3,
       0,     4,     1,     1,     1,     1,     2,     1,     1,     1,
       0,     3,     1,     2,     2,     2,     1,     1,     1,     2,
       2,     1,     2,     4,     2,     0,     1,     1,     1,     1,
       4,     5,     0,     4,     0,     1,     0,     3,     0,     3,
       3,     4,     0,     4,     4,     6,     0,     1,     0,     3,
       0,     5,     1,     1,     1,     1,     0,     3,     0,     3,
       2,     0,     3,     2,     0,     4,     2,     0,     1,     1,
       3,     0,     1,     2,     3,     3,     0,     3,     1,     3,
       7,     0,    10,     0,     2,     0,     2,     2,     3,     3,
       2,     0,     3,     0,     1,     1,     0,     1,     0,     4,
       0,     7,     0,     1,     0,     7,     0,     2,     3,     0,
       1,     1,     0,     4,     4,     0,     7,     0,     2,     0,
       0,     4,     1,     2,     0,     4,     0,     1,     0,     3,
       1,     1,     1,     1,     1,     4,     4,     3,     4,     1,
       1,     1,     2,     3,     1,     2,     3,     3,     0,     3,
       0,     7,     0,     5,     0,     2,     0,     2,     0,     3,
       0,     2,     4,     0,     2,     4,     0,     0,     7,     0,
       4,     2,     2,     2,     2,     2,     0,     1,     0,     4,
       2,     0,     2,     2,     0,     8,     1,     2,     1,     3,
       3,     0,     3,     0,     1,     0,     4,     4,     6,     6,
       0,     1,     2,     0,     1,     0,     3,     0,     7,     0,
       4,     0,     1,     1,     0,     9,     0,     3,     1,     3,
       2,     2,     2,     3,     0,     3,     0,     3,     0,     3,
       0,     1,     1,     1,     1,     8,     0,     1,     1,     1,
       1,     1,     1,     0,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     0,     1,     5,     1,     2,     5,     0,
       8,     0,     2,     0,     4,     3,     3,     1,     1,     0,
       1,     1,     0,     1,     2,     2,     0,     0,     3,     0,
       0,     3,     2,     0,     0,     3,     0,     0,     3,     2,
       0,     0,     3,     0,     0,     3,     1,     1,     2,     0,
       3,     0,     3,     1,     1,     2,     0,     3,     0,     3,
       0,     1,     1,     1,     2,     0,     3,     0,     3,     0,
       3,     1,     1,     0,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     0,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     1,     2,     1,     1,     2,     1,
       2,     1,     5,     4,     1,     5,     4,     1,     3,     0,
       1,     1,     1,     3,     3,     3,     3,     2,     2,     3,
       3,     1,     3,     1,     2,     2,     1,     1,     1,     2,
       1,     1,     2,     1,     0,     2,     1,     1,     1,     3,
       1,     1,     2,     1,     0,     1,     1,     1,     1,     1,
       2,     1,     3,     1,     2,     1,     3,     3,     3,     4,
       3,     1,     1,     1,     1,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     3,     1,     3,     3,     4,     5,     1,     1,     2,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     5,     5,     5,     5,     5,     5,     5,     4,     5,
       2,     0,     4,     5,     0,     3,     0,     1,     1,     3,
       3,     1,     3,     1,     3,     0,     0,     1,     0,     1,
       0,     1,     0,     1,     1,     0,     1,     0,     1,     0,
       1,     0,     2,     1,     1,     2,     2,     2,     1,     2,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     1,     0,     1,
       0,     1,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     2,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       2,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     3,     4,     6,     7,
      38,    38,     0,     0,     5,     0,     8,    14,    28,    27,
      29,    29,     0,   256,   256,     0,     0,    24,    40,     0,
       9,    15,    30,    26,  1493,     0,   151,     0,   589,   589,
    1494,     0,     0,     0,     0,     0,     0,    39,   258,     0,
      17,     0,    25,    33,    37,    36,  1518,    35,    42,   153,
       0,   155,   268,   269,     0,   319,   261,   593,    18,    20,
      38,     0,    16,    34,  1519,    32,    41,   159,   157,   237,
       0,     0,   437,     0,   596,   594,   611,     0,    19,    10,
      11,     0,     0,     0,     0,     0,    43,    44,    45,    47,
      46,   154,     0,   235,     0,  1485,   245,   156,     0,   239,
     241,   242,   243,   259,     0,     0,   440,  1330,   262,   322,
     270,   601,   601,     0,     0,     0,   256,    23,    56,    71,
      49,    80,  1447,   160,   159,     0,   152,  1511,  1486,  1535,
     246,   247,   248,  1467,   238,   240,   263,   320,     0,     0,
     443,   267,     0,   266,   323,  1435,   272,  1476,   601,   598,
     604,     0,   601,   612,   590,    21,    12,     0,  1493,    54,
    1518,    55,  1518,    60,    62,    63,    64,     0,     0,    70,
       0,    73,  1548,    48,     0,  1547,     0,     0,  1493,  1493,
       0,     0,  1526,  1493,  1493,  1493,  1493,  1493,     0,  1493,
    1479,  1493,    79,     0,    82,    84,    85,    86,    88,    87,
      89,    90,    91,    92,    93,    94,  1448,     0,   158,   237,
    1512,     0,  1536,  1481,  1468,  1487,   260,   322,   438,     0,
       0,   535,   322,   325,     0,  1493,   599,  1493,     0,   609,
     602,   603,   613,   589,  1493,     0,    57,  1518,    59,    61,
       0,  1460,  1493,     0,    77,     0,    72,    74,    52,    50,
       0,     0,  1348,   106,     0,     0,  1493,  1493,  1527,  1493,
       0,     0,     0,     0,     0,  1493,     0,  1480,     0,     0,
      81,    83,   161,   236,  1392,   255,  1341,  1343,  1482,     0,
    1488,     0,   264,   321,   322,   441,     0,     0,   257,   265,
     328,     0,   332,     0,   333,   329,  1481,  1493,     0,     0,
    1493,  1481,  1505,  1493,  1465,     0,   271,   273,   276,   277,
     278,   279,   280,   281,   282,   283,   284,     0,     0,  1493,
     610,     0,     0,   591,    17,     0,  1397,    69,    58,  1459,
       0,    76,    75,    78,    51,    53,  1493,    98,    99,     0,
       0,     0,   147,   146,   100,   101,   150,     0,   149,   133,
    1495,   135,    95,    96,   163,  1453,  1454,     0,  1342,   249,
     250,   253,   244,  1328,   439,   322,   444,     0,     0,   326,
     334,   335,   330,     0,     0,     0,  1493,  1465,     0,     0,
       0,     0,     0,  1506,  1493,     0,  1466,     0,     0,   274,
     275,   605,   606,   608,     0,   600,   614,   616,     0,     0,
      68,     0,  1406,  1402,  1407,  1405,  1403,  1408,  1404,   139,
     140,   142,   148,   145,   144,  1497,  1496,   136,     0,   102,
     205,  1393,   251,     0,   252,  1329,   442,   446,   536,   327,
     343,   337,   296,   316,  1455,  1456,   305,   300,   299,   298,
    1347,  1346,  1503,  1479,  1491,     0,   534,   317,   318,  1493,
    1493,   607,   616,     0,     0,    13,    66,    67,    65,   111,
     125,   121,   126,   108,   124,   122,   109,   110,   123,   107,
     112,   113,   115,   141,     0,   134,   137,    97,  1505,     0,
    1543,   220,     0,  1505,  1493,  1477,  1498,   223,     0,   222,
    1547,   207,   206,   162,   164,   165,   166,   167,   168,   169,
       0,   170,   171,   219,   172,   173,   174,   175,   176,   177,
    1493,   254,     0,   445,   447,   448,   537,  1493,  1469,     0,
       0,   286,  1504,   307,     0,   289,  1492,  1531,   315,     0,
       0,     0,     0,   626,   617,   618,   619,   620,   625,     0,
       0,   114,   117,     0,   143,   138,   105,   104,  1533,  1493,
    1498,  1544,   184,   224,  1493,     0,  1478,  1493,  1474,  1493,
    1499,     0,  1493,  1493,  1467,     0,  1493,     0,   451,   449,
     539,     0,   425,   367,   400,   388,   397,   394,   391,  1545,
     368,   369,   370,   371,   372,   373,   374,   375,   376,  1522,
     401,     0,   377,   364,   378,   379,     0,     0,  1529,   381,
     382,   380,   421,   384,   385,   383,  1493,  1495,   344,   345,
     346,   347,   348,   349,   365,   350,   351,   352,   353,   354,
     355,   356,   357,   358,     0,     0,  1470,     0,   338,   297,
     288,   287,   285,   306,  1479,  1532,   294,   303,   302,   304,
     301,     0,   622,   624,   627,   684,   735,   744,   751,   755,
     779,   783,   801,   794,   802,   803,   809,   842,   851,   853,
     880,   888,   890,  1543,   896,     0,   907,   928,   930,   966,
     968,   972,   683,   978,   991,  1011,  1028,  1030,  1034,  1041,
    1042,  1058,  1078,  1096,     0,  1114,  1125,  1133,  1135,  1137,
    1139,  1144,  1166,  1189,   621,   633,   634,   635,   636,   637,
     638,   639,   640,   642,   641,   643,   644,   645,   646,   647,
     648,   649,   650,   651,   652,   653,   654,   655,   656,   657,
     658,   659,   660,   661,   662,   663,   664,   665,   666,   667,
     668,   669,   670,   671,   672,   673,   674,   675,   676,   677,
     678,   679,   680,   681,  1162,  1163,  1164,   682,    22,     0,
     116,  1534,  1493,     0,  1493,   186,   185,   181,     0,  1473,
     223,   218,     0,     0,   221,     0,     0,   230,  1516,  1516,
       0,   231,     0,   203,  1493,   333,   543,   538,   540,   541,
     436,   398,   399,   386,   387,   395,   396,   392,   393,   389,
     390,  1546,     0,  1523,   419,   405,   359,  1388,   434,  1530,
     422,   423,   420,     0,     0,   361,   363,  1451,  1451,     0,
    1509,  1509,   342,   339,  1398,  1400,  1472,   308,   309,   310,
     311,     0,     0,   290,  1490,   296,     0,     0,   628,     0,
       0,     0,  1253,   750,     0,   781,   785,     0,     0,     0,
       0,     0,     0,  1253,   882,     0,     0,   892,   897,     0,
    1253,     0,     0,     0,     0,     0,     0,   980,  1001,     0,
       0,     0,     0,     0,     0,     0,     0,  1110,  1108,     0,
       0,  1134,  1132,     0,     0,     0,     0,  1167,  1173,     0,
       0,   131,   127,   132,   130,   128,   129,   118,   119,     0,
     192,   193,   191,   190,     0,   179,   180,     0,   212,   211,
     212,   208,   225,   226,   227,   229,  1517,   232,   233,   234,
    1344,  1493,   460,   460,  1495,   480,   452,   455,   456,     0,
     544,   542,   424,     0,  1541,     0,  1389,  1390,     0,   366,
     426,   428,   430,     0,   360,  1477,   402,   403,  1399,  1510,
       0,     0,     0,     0,     0,  1471,  1479,   295,   615,   623,
     733,   703,  1387,  1509,     0,     0,  1421,  1424,  1509,  1321,
       0,     0,     0,     0,     0,     0,     0,     0,  1421,   742,
    1363,   740,  1353,  1355,  1361,  1362,  1440,   745,     0,  1252,
    1268,  1340,     0,  1336,  1338,  1337,  1382,   757,  1381,  1383,
     780,   784,   797,     0,  1323,  1449,  1520,     0,  1402,   840,
     703,     0,  1355,   849,     0,   757,   859,   858,  1463,   855,
     857,   887,   884,   883,   886,   881,  1509,   889,  1349,  1351,
     891,  1334,   901,  1539,  1251,   909,   929,   462,     0,   932,
     933,   934,   967,  1082,     0,   969,     0,   976,     0,   979,
    1002,  1340,   992,  1001,   994,     0,   999,     0,  1337,     0,
    1442,  1191,  1326,  1520,  1191,     0,  1056,  1047,  1327,     0,
    1333,  1059,  1060,  1061,  1062,  1063,  1071,  1064,  1074,     0,
    1331,     0,  1079,  1097,  1111,  1475,     0,  1116,  1118,     0,
    1130,     0,  1136,     0,  1141,  1146,  1174,     0,  1175,  1511,
    1191,     0,   103,  1438,   188,   187,   178,   189,     0,   210,
     209,  1493,   202,   196,  1345,   204,     0,   461,   457,     0,
     458,     0,   450,   453,   546,   406,  1542,   407,  1509,     0,
       0,     0,  1309,  1307,  1370,  1312,  1364,  1368,  1369,     0,
    1391,   435,  1545,   429,     0,   362,  1452,   341,   340,  1401,
     314,  1503,     0,   292,   734,   685,  1472,     0,   712,     0,
       0,     0,     0,     0,  1409,  1426,  1420,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1410,   743,   736,
       0,     0,  1354,  1441,   748,  1440,  1254,     0,   753,     0,
     758,   768,  1380,   782,  1379,   787,   798,   795,   800,   799,
    1253,  1324,  1450,  1325,  1521,  1240,   808,   841,   810,   820,
    1206,  1206,  1206,  1206,   850,   843,     0,     0,   852,  1464,
    1253,   878,   865,   861,   863,  1253,   885,     0,  1350,   894,
    1540,   899,   911,     0,   463,     0,   955,   940,   931,   935,
     937,   938,   939,  1086,     0,     0,   977,   973,     0,   985,
     982,   984,   983,   986,   993,   996,   629,  1253,     0,     0,
    1003,     0,  1443,  1444,  1520,     0,  1029,  1013,  1036,  1049,
    1057,  1043,     0,  1049,     0,  1375,  1376,  1072,  1075,     0,
       0,  1332,  1070,     0,  1069,     0,  1099,     0,     0,  1109,
       0,     0,  1117,     0,  1131,  1126,     0,     0,  1142,  1143,
    1140,  1475,     0,     0,  1176,     0,     0,  1036,   120,  1458,
       0,   196,   194,  1439,     0,   215,   201,   228,     0,   454,
     459,   465,   475,   333,   481,  1528,  1511,   410,     0,  1317,
    1318,     0,  1310,  1311,  1394,     0,     0,     0,     0,     0,
       0,     0,     0,  1524,   431,   313,  1503,  1511,   291,   708,
     699,  1206,   689,   696,   690,   692,   694,     0,  1206,     0,
     688,   695,   702,   701,     0,  1206,  1507,  1507,  1507,   706,
     707,  1372,  1371,     0,  1360,  1309,  1307,     0,     0,  1309,
       0,  1356,  1357,  1358,  1322,  1309,     0,     0,  1309,     0,
       0,  1309,  1309,  1309,     0,     0,  1213,  1449,     0,     0,
     746,     0,  1260,  1261,  1262,  1292,  1263,  1543,  1296,  1301,
    1537,  1255,  1304,  1537,  1285,  1265,  1267,  1259,  1258,  1293,
    1264,  1266,  1275,  1276,  1277,  1278,  1279,  1294,  1257,  1297,
    1299,  1280,  1281,  1282,  1283,  1284,  1269,  1291,  1274,  1271,
    1272,  1273,  1270,  1286,  1287,  1288,  1289,  1290,  1256,     0,
       0,  1339,   764,     0,     0,   771,   792,   793,   786,   788,
       0,  1213,  1245,  1247,   805,  1241,  1242,  1243,     0,  1548,
    1206,     0,  1207,   813,  1209,   814,   811,   812,     0,  1213,
    1449,   873,   875,   874,   868,   870,   876,   879,   854,   866,
     862,   860,  1253,   629,   856,  1352,  1511,   893,  1335,   629,
    1543,   919,   920,   922,   924,   925,   921,   923,   914,  1543,
     910,     0,   956,     0,   958,   957,   959,   950,   951,     0,
       0,   936,  1088,  1513,     0,     0,   970,  1213,  1449,  1547,
       0,   997,   630,  1004,  1005,  1008,     0,  1000,  1198,  1197,
    1007,  1013,  1192,     0,     0,  1240,     0,     0,     0,  1048,
       0,     0,     0,  1073,     0,  1077,  1076,  1067,     0,  1493,
    1240,  1113,  1112,  1119,  1120,  1121,     0,  1213,  1449,     0,
    1436,     0,  1121,  1188,  1178,  1177,  1183,     0,  1185,  1186,
    1193,  1457,  1438,     0,   198,   199,   197,  1493,   467,   478,
     479,   477,   335,   483,   559,  1493,   550,   548,   549,   551,
    1507,     0,  1493,     0,   562,   554,  1507,   555,     0,   558,
     563,   561,   556,   560,     0,   557,     0,   545,   573,   568,
     571,   570,   569,   572,   547,   574,     0,   414,   409,  1365,
    1366,  1367,  1320,  1308,  1313,  1314,  1315,  1316,  1319,  1395,
       0,  1525,  1543,   312,     0,   700,  1209,   691,   693,  1206,
     697,   687,   727,  1493,   716,   717,  1493,   728,   718,   719,
     722,   732,   729,   720,     0,   730,   721,   731,   713,   714,
     686,  1508,     0,     0,     0,   704,   705,  1374,  1359,  1373,
    1421,  1449,     0,  1425,     0,  1421,  1421,     0,  1418,  1421,
    1421,  1421,     0,  1421,  1421,  1214,   737,  1216,  1213,   749,
       0,  1295,  1538,  1298,  1300,   754,   752,   759,   760,   604,
       0,   770,   769,  1179,  1180,   774,   772,     0,   791,     0,
     796,   629,   629,   806,   804,  1244,   820,   820,   820,   820,
    1493,   825,   838,   839,   826,     0,  1493,   829,   830,   833,
     831,     0,   832,   822,   823,   815,   821,   629,  1210,  1205,
       0,   844,     0,  1253,  1253,   872,   629,   869,   864,     0,
     902,     0,     0,   926,     0,     0,     0,   952,   954,     0,
     946,   962,   947,   948,   941,   942,   962,  1080,  1493,     0,
    1514,  1087,   412,   413,  1498,   971,   974,     0,     0,   988,
     998,   995,   632,     0,     0,  1015,  1014,  1229,  1231,  1032,
    1226,  1227,  1039,  1037,     0,  1253,  1050,  1253,  1044,  1052,
    1065,  1066,  1068,  1445,  1106,  1220,     0,  1449,  1127,     0,
       0,  1437,  1147,  1148,     0,  1151,  1154,  1158,  1152,  1184,
    1511,  1187,  1199,  1461,   195,     0,   216,   217,   213,     0,
       0,   469,     0,  1528,     0,  1493,   552,   553,     0,   576,
    1493,  1541,   577,   575,   408,  1475,   404,  1498,  1396,   432,
     293,  1204,   698,     0,     0,  1249,  1249,   715,   710,   709,
     711,  1414,  1213,  1422,     0,  1434,  1419,  1412,  1432,  1413,
    1415,  1416,  1429,  1430,  1417,  1411,   629,  1217,  1212,   738,
     747,  1543,     0,  1543,     0,   761,   762,     0,   766,   765,
     767,  1181,  1182,   777,   775,   629,   789,   790,  1246,  1248,
    1206,  1206,  1206,  1206,     0,   827,   828,     0,  1249,  1249,
     824,  1208,   629,  1213,  1323,  1213,  1323,   871,   877,   867,
     895,   903,   905,   912,   915,   916,  1483,   927,   908,   913,
     962,  1377,  1378,   962,     0,   945,   943,   944,   949,  1090,
       0,  1515,  1084,  1213,   987,   981,     0,   631,  1009,     0,
       0,  1021,     0,   629,   629,  1033,  1031,  1228,  1040,  1035,
    1038,  1045,   629,  1054,  1053,  1446,     0,     0,  1107,  1098,
    1221,  1123,  1223,     0,  1213,  1213,  1138,  1436,  1150,  1491,
    1156,  1491,  1220,     0,  1236,  1238,  1202,  1200,  1233,  1234,
    1201,  1462,     0,   214,   466,  1493,     0,   471,   476,  1507,
     512,   532,   527,  1465,     0,     0,  1493,  1509,  1493,     0,
     482,   488,   489,   490,   499,   491,   493,   496,   484,   485,
     486,   492,   495,   513,   497,   500,   487,     0,   494,   498,
    1386,   567,  1384,  1385,   583,   566,   578,   588,     0,  1493,
    1493,   427,   724,   723,   726,     0,   725,   739,  1423,  1215,
     629,  1303,  1543,  1306,  1543,   763,   778,   756,   629,   773,
     819,   818,   817,   816,   835,   834,   837,   836,  1211,   846,
       0,   845,     0,   629,   906,   900,   917,  1484,     0,   961,
     953,   962,   964,     0,     0,  1093,  1089,  1083,   975,   990,
       0,     0,  1016,  1493,  1023,     0,  1017,     0,  1020,  1230,
    1232,   629,  1051,   629,  1100,  1101,  1102,  1103,  1104,  1105,
     629,  1124,  1115,  1224,  1219,  1122,  1129,  1128,  1149,     0,
    1491,  1153,     0,  1160,  1172,  1169,  1171,  1170,  1165,  1168,
     629,   629,  1203,  1190,  1235,  1196,  1195,  1500,     0,  1493,
    1493,   473,   511,  1493,   533,   531,   528,   529,  1495,   521,
    1493,  1253,     0,     0,     0,     0,   514,     0,     0,   519,
     522,   525,   586,   584,   585,   587,     0,   581,   579,   580,
     582,     0,   418,   415,   416,     0,     0,  1500,  1218,  1302,
    1305,   776,  1213,  1213,   904,     0,   960,   965,     0,  1493,
    1091,     0,     0,  1081,  1085,   989,     0,     0,  1026,  1024,
    1025,  1019,  1018,  1046,  1055,  1222,   629,  1155,     0,  1159,
    1161,  1145,  1237,  1239,  1501,  1502,  1194,   468,     0,     0,
    1493,   464,     0,   520,     0,   517,  1449,   515,   516,   506,
     504,   505,   507,   503,   508,   502,   501,     0,   526,   524,
     523,   565,   564,   417,   411,   433,  1250,   848,   847,   918,
     963,     0,  1094,  1493,  1253,  1022,  1027,  1012,  1225,  1157,
     470,   472,     0,   510,   509,   530,     0,  1092,     0,  1010,
     474,     0,  1095,   518
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,     7,     8,    23,    38,    68,   126,
     243,     9,    24,    39,    69,    89,   465,    72,    70,    34,
      11,    20,    26,    41,    56,    57,    16,    36,    76,    96,
      97,   183,   184,   170,    98,   171,   172,   173,   174,   468,
     175,   176,    99,   179,   180,   181,   255,   100,   202,   203,
     204,   205,   429,   487,   558,   206,   346,   479,   480,   481,
     759,   897,   482,   898,   207,   359,   360,   485,   208,   419,
     420,   209,   210,   211,   212,   213,   214,   215,    47,    77,
      79,   103,   101,   133,   364,   430,   504,   505,   907,   767,
    1106,   506,   903,   507,  1317,  1318,  1584,  1113,   508,   509,
     510,   511,   911,  1109,  1838,   512,   513,   514,   515,   516,
     517,   518,   519,   781,   136,   107,   108,   109,   110,   143,
     111,   369,   370,   434,   112,    30,    65,   146,    83,   226,
     151,   118,   152,   119,   156,   235,   317,   318,   642,   319,
    1348,   835,   531,   320,   449,   321,   648,   322,   323,   643,
     827,   828,   829,   830,   324,   325,   326,    82,   227,   153,
     154,   155,   233,   303,   440,   304,   382,   383,   528,   822,
     305,   527,   618,   619,   620,   944,   621,   622,   623,   624,
     625,   626,   934,  1327,  1627,  1628,  1784,  1856,  2183,  2184,
     627,   628,   812,   629,   630,   631,  1142,   940,   941,  2051,
     632,   633,   116,   294,   150,   375,   231,   437,   523,   524,
     525,   784,   926,   927,  1118,  1119,  1036,   928,  1588,  1841,
    2007,  2151,  2231,  1321,  1591,  1122,  1324,  1843,  2028,  2029,
    2246,  2030,  2031,  2032,  2033,  2237,  2034,  2035,  2036,  2037,
    2169,  2170,  2158,  2038,  2039,  2155,   457,   298,   526,   580,
     787,   788,   789,  1124,  1325,  1624,  2181,  2176,  1625,    50,
     242,   407,    86,   122,   121,   158,   159,   160,   239,   331,
     124,   333,   462,   463,   544,   545,   546,   547,   548,   839,
    1531,  1532,  1792,   549,   705,   706,   840,   960,  1158,  1369,
    1370,  1365,  1668,  1669,  1155,   707,   841,   979,  1181,  1179,
     708,   842,   987,  1400,   709,   843,  1450,   710,   844,  1191,
    1452,  1707,  1708,  1709,  1455,  1715,  1905,  1903,  2068,  2067,
     711,   845,  1000,   712,   846,  1001,  1458,  1459,   713,   847,
    1002,  1197,  1200,   714,   715,   716,   848,  1724,   717,   849,
     718,   850,  1009,  1470,  1743,  1744,  1208,   719,   851,  1013,
    1215,   720,   852,   721,   853,  1018,  1019,  1221,  1222,  1223,
    1493,  1491,  1756,  1224,  1484,  1485,  1755,  1488,   722,   854,
    1025,   723,   855,   724,   856,   725,  1031,  1497,   726,   858,
     727,   860,  1499,  1932,  2083,  2085,   728,   861,  1232,  1508,
    1763,  1934,  1935,  1936,  1938,   729,   862,   730,   863,  1038,
    1238,  1239,  1240,  1520,  1774,  1775,  1241,  1517,  1518,  1519,
    1768,  1242,  1945,  2198,   731,   864,   732,   865,  1045,   733,
     866,  1047,  1247,   734,   867,  1049,  1253,  1530,  1955,   735,
     868,  1052,  1256,  1791,  1053,  1054,  1055,  1534,  1535,   736,
     869,  1544,  1961,  2104,  2208,  2267,   737,   870,   738,   871,
    1966,   739,   872,  1545,  1969,   740,   741,   873,  1066,  2111,
    1273,  1547,  1972,  1808,  1809,  2113,  1271,   742,   874,  1071,
    1072,  1073,  1074,  1285,  1075,  1076,  1077,  1078,   743,   875,
    1042,  1949,  1243,  2097,  1522,  1777,  2095,  2203,   744,   876,
    1286,  1560,  1976,  1979,   745,  1084,  1289,   746,   879,  1086,
    1087,  1815,  2122,   747,   880,  1090,  1295,   748,   882,   749,
     883,   750,   884,   751,   885,  1300,   752,   886,  1302,  1822,
    1823,  1572,  1825,  1990,  2131,  1992,  2221,   753,   754,   888,
    2138,  1098,  1305,  1576,  1716,  1904,  1830,   755,  1578,   756,
     757,   890,  1266,  1832,  2092,  1996,  2143,  1645,  1473,  1474,
    1747,  1749,  1922,  1696,  1697,  1886,  1888,  2060,  1981,  1982,
    2120,  2124,  2216,  1799,  1800,  1963,  1801,  1964,  1997,  1998,
    2140,  1999,  2141,  1464,  1465,  1466,  1721,  1467,  1722,  2054,
    1033,  1034,   989,   990,  1186,  1187,  1431,  1432,  1433,  1434,
    1435,  1132,  1335,  1376,   980,  1003,  1201,  1061,  1067,   372,
     373,  1079,  1080,  1229,  1056,   993,   994,   285,   451,  1115,
     452,   263,  1027,  1028,   981,  1005,  1135,  1373,  1678,  1776,
    1940,  1011,  1057,  2041,   983,   962,   807,   936,   937,  2043,
     984,   824,   825,   985,  1164,  1166,  1380,  1394,  1389,  1386,
     234,  1824,  1312,  1184,  1264,  1977,   217,  1203,   946,   367,
     388,  1313,   252,  2002,  1753,   397,   225,   637,  1159,   571,
     161,   567,   278,   289,  2088,   139,   291,   836,   537,    42,
     428,   572,  2226,   533,   394,  1672,   950,   221,  1781,   917,
     177,  1205,   804,  1642,   269,   635,   646,   762,   223,  1703,
    1231,  1127,   562,   802,  1471
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1715
static const yytype_int16 yypact[] =
{
   -1715,   298,   425, -1715,  -140,   168,   425, -1715, -1715, -1715,
     524,   524,   538,   538, -1715,   526, -1715, -1715, -1715, -1715,
     717,   717,   294,   677,   677,   610,   404, -1715,   787,   763,
   -1715, -1715, -1715, -1715,   -79,   534,   816,   484,   657,   657,
   -1715,   551,    43,   566,   613,   745,   655, -1715,   -32,   988,
     811,   995, -1715,   -53, -1715, -1715,   821, -1715, -1715, -1715,
     748, -1715, -1715, -1715,   874,   788, -1715,    32, -1715,   457,
     524,   538, -1715, -1715, -1715, -1715,   -27, -1715,  1062,   180,
     798,   925,  1039,   846, -1715, -1715,   948,   538, -1715, -1715,
   -1715,   838,   840,   842,   858,   859, -1715, -1715, -1715, -1715,
   -1715,   941,   860,  1088,  1239,   916,   578, -1715,    42, -1715,
   -1715, -1715, -1715, -1715,   871,   973,  1095, -1715,   458,   892,
   -1715,    98,    98,   893,   881,   883,   677, -1715,   621,  1145,
      22,  1425,  1056, -1715, -1715,   886, -1715,  1064, -1715,   947,
   -1715, -1715, -1715,  1323, -1715, -1715, -1715, -1715,   908,  1008,
    1037, -1715,   846, -1715, -1715, -1715, -1715, -1715,    16, -1715,
    -111,   311,   114, -1715, -1715, -1715, -1715,  1002,  1159, -1715,
     -18, -1715,   381, -1715, -1715, -1715, -1715,    62,   187, -1715,
     -49, -1715, -1715, -1715,   927,   684,  1266,   945,  1159,  1159,
     945,   999,  1012,  1159,  1159,  1159,  1159,  1159,   945,  1159,
    1324,  1159, -1715,   744, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715,   945,   941,   180,
   -1715,   956, -1715,  1297, -1715,  1219,   458,   892, -1715,   946,
    1048,  1050,   892,   276,   968,  1150, -1715,  1159,  1040,  1130,
   -1715, -1715,  1305,   657,  1159,  1189, -1715,   453, -1715, -1715,
    1067, -1715,  1159,  1217, -1715,   101, -1715, -1715, -1715, -1715,
     980,  1182, -1715, -1715,   945,   945,  1159,  1159, -1715,  1159,
     956,  1362,   945,   945,   956,  1159,   956, -1715,   945,    17,
   -1715, -1715, -1715, -1715,   624,   956, -1715, -1715, -1715,   846,
   -1715,   846, -1715, -1715,   892, -1715,   985,  1084, -1715, -1715,
   -1715,   968, -1715,   987,   -12, -1715,  1297,  1159,   834,   834,
    1159,    29,  1194,  1159,  1415,  1174, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715,   912,   541,  1159,
   -1715,  1013,  1001, -1715,   811,  1189, -1715, -1715, -1715, -1715,
     956, -1715, -1715, -1715, -1715, -1715,  1159, -1715, -1715,   782,
     956,  1222, -1715, -1715, -1715, -1715, -1715,   956, -1715, -1715,
      71, -1715, -1715, -1715, -1715, -1715, -1715,   956, -1715,   846,
   -1715,  1155,   846, -1715, -1715,   892, -1715,  1007,  1009, -1715,
   -1715,  1372, -1715,  1376,  1189,  1026,  1159,  1415,   956,   360,
       0,  1189,  1033, -1715,  1159,  1031, -1715,  1031,    25, -1715,
   -1715, -1715, -1715, -1715,  1189, -1715, -1715, -1715,   488,    97,
   -1715,  1099, -1715, -1715, -1715, -1715, -1715, -1715, -1715,   782,
   -1715,  1074, -1715, -1715, -1715, -1715, -1715, -1715,  1189, -1715,
     952, -1715, -1715,  1189, -1715, -1715, -1715,  1162, -1715, -1715,
   -1715,   498,  1073, -1715, -1715, -1715,   956, -1715, -1715, -1715,
   -1715, -1715,  1248,    54,  1282,  1049, -1715, -1715, -1715,  1159,
    1159, -1715, -1715,  2131,   538, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
     891, -1715,    89, -1715,   782,  1189, -1715,   901,  1194,  1167,
    1089, -1715,  1131,  1194,  1159,  1439,   265,    -6,  1189, -1715,
    1063, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
    1120, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
    1159, -1715,  1031, -1715,  1162, -1715, -1715,  4626,  1473,  1317,
    1189,    69, -1715, -1715,  1189, -1715, -1715,  1137, -1715,   133,
     133,  2414,  1057,  1058, -1715, -1715, -1715, -1715,  1157,  2919,
    1061, -1715, -1715,   891, -1715, -1715, -1715, -1715,  1133,  1159,
    1299, -1715,   171, -1715,  1159,   623, -1715,  1159, -1715,  1159,
   -1715,  1164,  1159,  1159,  1323,   207,  1159,  1090, -1715, -1715,
     968,  1304, -1715, -1715,   -78,   668,   750,   761,   765,  1096,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,  1190,
   -1715,  1189, -1715, -1715, -1715, -1715,   956,   956,  1318, -1715,
   -1715, -1715,   598, -1715, -1715, -1715,  1159,   191, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715,   934,   -25, -1715,   625, -1715, -1715,
   -1715, -1715, -1715,   183,  1324, -1715,   772, -1715, -1715, -1715,
   -1715,  1441, -1715, -1715,  1301, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715,  1158, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715,  1089, -1715,  1277, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715,   388, -1715, -1715,  1254, -1715, -1715,
   -1715, -1715,   535, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,   902,
   -1715, -1715,  1159,    58,  1159, -1715, -1715,   316,   435,  1523,
   -1715, -1715,     0,  1187, -1715,   956,   956, -1715,  1285,  1285,
    1292, -1715,   956, -1715,   113,   -12, -1715, -1715,   968, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715,  1128, -1715, -1715,  1176, -1715,  1126,  1177, -1715,
   -1715, -1715, -1715,  4634,   119,  1551, -1715,  1224,  1224,   782,
    1310,  1310, -1715, -1715,  1129, -1715, -1715, -1715, -1715, -1715,
   -1715,    39,  1411, -1715, -1715,  1073,  1189,  1141, -1715,  1142,
     956,  3643,  1156,   154,  1574, -1715, -1715,  4209,   846,  1193,
    4317,  4209,  1365,   642,   714,    77,   956, -1715, -1715,  1463,
   -1715,    77,   956,  1684,   956,  3710,  4209, -1715,  1963,   846,
     956,   846,   956,    80,    87,   956,   846, -1715, -1715,  3790,
    3879, -1715, -1715,   956,   956,   846,   956, -1715,   960,  1494,
     956, -1715, -1715, -1715, -1715, -1715, -1715,  1583, -1715,   945,
   -1715, -1715, -1715, -1715,   956,    -1,    49,    96,  1170, -1715,
    1170, -1715, -1715, -1715,   492, -1715, -1715, -1715, -1715, -1715,
     956,  1159,  1432,  1432,   191, -1715, -1715, -1715, -1715,  1422,
   -1715, -1715, -1715,  1189,  1212,  5032,  1160, -1715,   956, -1715,
     119, -1715,  1215,  1383, -1715,  1439, -1715, -1715, -1715, -1715,
     956,   956,   782,     0,     0,  1586,  1324, -1715, -1715, -1715,
    1501,   605, -1715,  1310,  1178,   956,  1195,  1196,  1310,   624,
    1197,  1199,  1203,  1204,  1209,  1214,  1218,  1225,  1195,  1493,
   -1715,  3956, -1715, -1715, -1715, -1715,  1426, -1715,  1576, -1715,
   -1715, -1715,  1234, -1715,   624, -1715, -1715,  1236, -1715, -1715,
     157,   846,  1513,  3100, -1715,  1302,  1338,   846,   996,  1515,
    3460,  1021,  1071,  1535,   627,  1236, -1715, -1715,    46, -1715,
   -1715, -1715,  1569, -1715, -1715, -1715,  1310,    77, -1715, -1715,
   -1715, -1715, -1715,  1288, -1715,    44,   956, -1715,   156, -1715,
   -1715, -1715, -1715, -1715,  4209, -1715,  1294,  1547,  1639,   756,
   -1715,  1296, -1715,  2269,  1559,   594,  1306,  1300,   461,  1307,
     575,  1522, -1715,  1338,  1522,   956,  1561,  1274, -1715,   764,
   -1715, -1715, -1715, -1715, -1715,  1461, -1715,    77, -1715,   -60,
   -1715,    75, -1715, -1715,   448,  1656,  3549, -1715, -1715,   956,
    1564,  4062,   956,  1533,   876,  1601, -1715,  1386,  1340,  1064,
    1522,   902, -1715,   194, -1715, -1715, -1715, -1715,   406, -1715,
   -1715,  1159, -1715, -1715, -1715, -1715,   157, -1715, -1715,   956,
   -1715,  1189,   968, -1715, -1715, -1715, -1715,  1604,  1310,  5032,
    5032,  5032,    38,   910, -1715, -1715, -1715,  1129, -1715,  5032,
   -1715, -1715,  1096, -1715,   119, -1715, -1715, -1715, -1715, -1715,
   -1715,  1248,     0,  1605, -1715, -1715,   764,  1168,  1287,   304,
       2,  5032,  1325,  5032, -1715,  5032, -1715,  1740,  1290,  5032,
    5032,  5032,  5032,  5032,  5032,  5032,  5032, -1715, -1715, -1715,
    4209,  1539, -1715, -1715,  1392,  1426,  1094,  2865,  1428,  1503,
   -1715,   485, -1715, -1715, -1715,   653, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715,   436,   846, -1715, -1715,   339,
    1575,  1575,  1575,  1575, -1715, -1715,  4209,  4209, -1715, -1715,
      67,  1603,   789, -1715,  1308,   642, -1715,   956, -1715,     6,
   -1715, -1715,   889,  1568, -1715,   764,    82, -1715,   156, -1715,
   -1715, -1715, -1715,    68,  1341,    77, -1715, -1715,  4209, -1715,
   -1715, -1715, -1715,  1380, -1715, -1715, -1715, -1715,   956,   154,
   -1715,  1046, -1715, -1715,  1338,   157, -1715,  1534,    -9,   247,
   -1715, -1715,   956,   247,  1345, -1715,  1129, -1715, -1715,    76,
     901, -1715, -1715,  3527, -1715,  1693,  1529,  4209,  4209, -1715,
    4148,   956, -1715,  1570, -1715, -1715,  4209,   764, -1715, -1715,
   -1715,  1656,  1538,   956, -1715,   923,    95,    -9, -1715, -1715,
    1626, -1715, -1715, -1715,  1474, -1715, -1715,   956,   956, -1715,
     956,  1560,   929,    13, -1715,  4725,  1064, -1715,  1740,  1309,
    1309,   897, -1715, -1715, -1715,  5032,  5032,  5032,  5032,  5032,
    5032,  4875,   910,  1390, -1715, -1715,  1248,  1064, -1715, -1715,
   -1715,  1575, -1715, -1715,  1311,  1313, -1715,   764,  1575,  1542,
   -1715, -1715, -1715, -1715,  1606,  1575,  1489,  1489,  1489,    94,
    1526, -1715, -1715,   165, -1715,    51,   855,   956,   942,    73,
    1312, -1715,  1129, -1715, -1715,   255,  1314,  1108,   520,  1315,
    1180,   121,   128,   817,  1319,  1192,  4197,    24,  4209,    77,
   -1715,  1423, -1715, -1715, -1715, -1715, -1715,  1089, -1715, -1715,
    1369, -1715, -1715,  1369, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,  1363,
     154, -1715,   210,   956,   956,   540, -1715, -1715, -1715,    88,
     879,  1396, -1715, -1715,  1641, -1715,  1512, -1715,   105,  1368,
    1575,  1510, -1715, -1715,  1516, -1715, -1715, -1715,  1590,  4197,
     470, -1715, -1715, -1715,  2620, -1715,  1385, -1715, -1715, -1715,
   -1715, -1715,    67, -1715, -1715, -1715,  1064, -1715, -1715, -1715,
    1089, -1715, -1715, -1715, -1715, -1715, -1715, -1715,  1452,  1089,
   -1715,  1389, -1715,  1732, -1715, -1715, -1715,   854, -1715,   764,
     414, -1715,    62,    74,   252,    77,    77,  4197,   494,  1063,
     846,  1647, -1715, -1715,  1778, -1715,  1611, -1715, -1715, -1715,
   -1715,  1534, -1715,   956,    99,   436,   907,  1358,  1666, -1715,
    1360,   764,   799, -1715,   165, -1715, -1715, -1715,  4209,  1159,
     436, -1715, -1715, -1715, -1715,   -76,   956,  4197,   496,  1395,
    1783,   956,   373, -1715, -1715, -1715,  1495,  1492, -1715, -1715,
    1046, -1715,   153,   672, -1715, -1715, -1715,  1159,  1624, -1715,
   -1715,  1189, -1715, -1715, -1715,  1159, -1715, -1715, -1715, -1715,
    1489,  1083,  1159,  1574, -1715, -1715,  1489, -1715,  1189, -1715,
   -1715, -1715, -1715, -1715,   956, -1715,   956, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715,   956,  1599,   252, -1715,
    1129, -1715, -1715,   855,   833,   833,  1309,  1309,  1309, -1715,
    1230, -1715,  1089, -1715,   956, -1715,  1516, -1715, -1715,  1575,
   -1715, -1715, -1715,  1159, -1715, -1715,  1159, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715,    -2, -1715, -1715, -1715,  1606, -1715,
   -1715, -1715,   157,   157,   157, -1715, -1715, -1715, -1715, -1715,
    1195,  1302,  4968, -1715,   956,  1195,  1195,  5032, -1715,  1195,
    1195,  1195,   392,  1195,  1195, -1715, -1715,  1537,  4197, -1715,
      77, -1715, -1715,   460,   553, -1715, -1715,  3179, -1715,   519,
      10, -1715, -1715, -1715, -1715,   992, -1715,  1479, -1715,  1465,
   -1715, -1715, -1715, -1715, -1715, -1715,   -57,   -57,   -57,   -57,
    1159, -1715, -1715, -1715, -1715,  1103,  1159, -1715, -1715, -1715,
   -1715,     5, -1715,  1368, -1715, -1715, -1715, -1715, -1715, -1715,
    4209, -1715,  4209,    67, -1715, -1715, -1715,  2620, -1715,   956,
    1681,  1378,  1055,  1704,  1387,   685,   764, -1715, -1715,  1764,
   -1715, -1715, -1715, -1715,   414, -1715,  1643, -1715,  1159,  1540,
   -1715, -1715, -1715, -1715,  1299,    77, -1715,  4209,   207,   641,
   -1715, -1715, -1715,   956,  4209,   687, -1715, -1715, -1715,  1678,
    1563, -1715,  1683, -1715,  1591, -1715, -1715, -1715, -1715,  1360,
   -1715, -1715, -1715,  1562,  1685,  1545,  1531,  1302, -1715,  4209,
     685, -1715,  1552, -1715,   764, -1715,  1718,  1443, -1715, -1715,
    1064, -1715,   809,  1824, -1715,   953, -1715, -1715, -1715,  1189,
    1719,  1617,  1768,  4813,   -21,  1159, -1715, -1715,   -21, -1715,
    1159,  1212, -1715, -1715, -1715,  1656, -1715,  1299, -1715,  1438,
   -1715, -1715, -1715,   -21,   -21,    35,    35, -1715, -1715, -1715,
   -1715, -1715,  1396, -1715,  1243, -1715, -1715, -1715,   855, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715,  1089,  1686,  1089,  1687, -1715, -1715,  4209, -1715, -1715,
   -1715, -1715, -1715,  1711, -1715, -1715, -1715, -1715, -1715, -1715,
    1575,  1575,  1575,  1575,   -21, -1715, -1715,   -21,    35,    35,
   -1715, -1715, -1715,  4197,  1524,  4197,  1525, -1715, -1715, -1715,
   -1715, -1715,  1710, -1715,  1055, -1715,  1745, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715,   685,  1046, -1715, -1715,  1046,   -15,
     956, -1715, -1715,  4197, -1715, -1715,   915,  3324, -1715,  1799,
    1618,  1640,   413, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715,   956,   725, -1715, -1715,
   -1715,  1713,  1593,   956,  1396,  4197, -1715,  1783, -1715,  1282,
    1763,  1282,  1545,   587, -1715, -1715,  1712, -1715,  1608, -1715,
   -1715, -1715,   545, -1715, -1715,  1159,  1773,  1649, -1715,   978,
   -1715,  1659,  1028,  1415,  1679,  1442,  1159,  1310,  1159,   956,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715,  1485, -1715, -1715, -1715, -1715,    14, -1715, -1715,
   -1715, -1715, -1715, -1715,   511, -1715,   616, -1715,  1435,  1159,
    1159, -1715, -1715, -1715, -1715,   -21, -1715, -1715, -1715, -1715,
   -1715, -1715,  1089, -1715,  1089, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
    4209, -1715,  4209, -1715, -1715, -1715, -1715, -1715,  1822,  1046,
    1046, -1715,  1475,  1573,   846,    78, -1715,   956, -1715, -1715,
    1541,  4209, -1715,  1159,   853,  1642, -1715,  1646, -1715, -1715,
   -1715, -1715, -1715, -1715,   956, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,   956,
    1282, -1715,   956,  1733, -1715, -1715, -1715, -1715, -1715,   846,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715,   938,  1189,  1159,
    1159,  1714, -1715,  1159, -1715, -1715, -1715, -1715,   191, -1715,
    1159, -1715,   956,   956,  1332,  1705, -1715,  1598,  1189,    14,
   -1715, -1715, -1715, -1715, -1715, -1715,   -21, -1715, -1715, -1715,
   -1715,   -21, -1715,  1435, -1715,   956,   119,   938, -1715, -1715,
   -1715, -1715,  1396,  1396, -1715,  4209,  1046, -1715,  4209,  1159,
     846,   846,  1588, -1715, -1715, -1715,  1471,   956,  1753, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,   956, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,  1189,  1189,
    1159, -1715,  1189, -1715,  1189, -1715,  1302, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715,  4209, -1715, -1715,
   -1715, -1715, -1715, -1715,   956, -1715, -1715, -1715, -1715, -1715,
   -1715,   154,   846,  1159, -1715,   956, -1715, -1715, -1715, -1715,
   -1715, -1715,  1189, -1715, -1715, -1715,  1842, -1715,   154, -1715,
   -1715,  4209, -1715, -1715
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1715, -1715, -1715, -1715,  1887, -1715, -1715, -1715,    23, -1715,
   -1715, -1715, -1715, -1715,  1565, -1715, -1715, -1715,  1200, -1715,
   -1715,    63,  1874, -1715, -1715,  1844,   615, -1715, -1715, -1715,
   -1715, -1715,  1723,  1780, -1715, -1715,  1728,   464, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715,  1731, -1715, -1715, -1715, -1715,
    1709, -1715, -1715, -1715,   635, -1715, -1715, -1715, -1715,  1437,
   -1715, -1715,  1370,   823, -1715, -1715, -1715, -1715, -1715, -1715,
    1506, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715,  1788, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715,   617, -1715,   608,   824, -1715, -1715,
   -1715, -1715, -1715,  1019,   100, -1715,  1367, -1715, -1715, -1715,
   -1715, -1715, -1715,   142, -1715,  1715, -1715,  1825, -1715, -1715,
   -1715, -1715,  1571, -1715, -1715,   214, -1715, -1715, -1715, -1715,
    1717, -1715,  1893,  1792, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715,  1111, -1715, -1715, -1715,  1407, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,   865,
   -1715, -1715, -1715,  1648, -1715,  -539,  -742, -1715, -1715, -1715,
    -409, -1715, -1715, -1715, -1715, -1715, -1715, -1287, -1268,  1135,
   -1264,   107, -1715, -1715, -1715, -1715,   325, -1715, -1715,  -226,
   -1259, -1715, -1715, -1253, -1715, -1251, -1715, -1715,  1018, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
    1436, -1715, -1715, -1715,  1036, -1715,  -873, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715,   -71, -1715, -1715, -1715, -1715, -1715,
   -1715,  -207, -1715, -1715, -1715, -1715,  -149, -1715, -1715, -1715,
   -1715, -1715,  1175, -1715, -1715, -1715, -1715, -1715, -1715,   357,
   -1715, -1715, -1715, -1715, -1715,  1843,  1045, -1715,   259, -1715,
   -1715, -1715, -1715,  1502, -1715, -1715, -1715, -1715, -1715, -1715,
    -973, -1715, -1715,   177, -1715, -1715, -1715, -1715,   961,   603,
     609, -1715, -1715,   306, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,   965,
   -1715, -1715,   274, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715,  -211, -1715,   241, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715,   760, -1715, -1715,   766,
   -1715, -1715, -1715, -1715,   495,   238, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715,    60,   768, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715,   757, -1715, -1715, -1715,   227, -1715, -1715,   489, -1715,
   -1715, -1715, -1646, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1376,   958, -1715, -1715,   216, -1715,
   -1715,   473, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715,   708, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715,   743, -1715,   208, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715,   943, -1715,   944, -1715, -1715,
    1149, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
     939,   454, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
      33, -1715,   455, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715, -1715,
   -1715, -1715,  -789, -1715, -1142, -1715, -1715, -1094, -1133, -1125,
   -1715,   383, -1715, -1304, -1715, -1715, -1715, -1715,    41, -1715,
   -1715, -1715, -1715,   -74, -1715, -1715,   231, -1715, -1715, -1715,
   -1715,    37, -1715,  -686, -1714, -1715, -1715,   571, -1715,  -892,
   -1241,  -818, -1173, -1715, -1715, -1715, -1169, -1167, -1164, -1162,
   -1154,    65,  -201,  -305,  -677, -1059,  -836,   125,   974,  -993,
     -83, -1715, -1048, -1715,  -794, -1715,   849,  -386,  -173, -1715,
    -637,   -22,  -801,  -991,   108,  -714, -1715, -1715,   486, -1015,
   -1596,  -947,  -807,  -925,   731,  -589,  -218, -1715,  1105,  -230,
    -631,  -623,  -274,  -123,  -927, -1715, -1715, -1715, -1715, -1715,
    1812, -1715,   465,   861, -1715, -1715, -1715, -1626,  1231,   -44,
    1741,   810,  -418, -1715,  1034,  -382,  1480, -1715,  -604, -1715,
   -1066,  1112,  -391,   852, -1715, -1715,  -662, -1715, -1301,  -167,
    -610,  -489,  -129,  -966,   692, -1322,  -808, -1057, -1715,  1283,
    2005,  -670, -1715, -1715, -1715, -1715, -1715, -1715, -1715,   660,
   -1715,   223,  -664,   935,  -126
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1548
static const yytype_int16 yytable[] =
{
     120,   245,   446,   287,   186,   445,   823,   814,   573,   857,
    1092,  1004,   520,   951,  1206,   337,  1533,   806,  1443,  1290,
    1444,   264,   265,  1445,   988,  1446,   270,   271,   272,   273,
     274,  1281,   276,  1447,   279,  1020,  1228,   997,  1618,   831,
     889,   785,  1306,   930,  1228,  1673,  1674,  1486,   286,   992,
    1026,  1177,   287,  1193,  1274,  1872,   287,  1619,   287,   186,
    1035,  1620,   535,  1219,   104,   157,  1621,   287,   327,   120,
     328,   764,  1622,  1081,  1623,   421,    21,   335,  1475,  1476,
    1477,  1026,  1026,  1026,   157,   340,    84,   953,  1481,  1065,
    1228,  1512,    88,  1026,   425,  1898, -1511,   352,   403,   349,
     350,   356,   351,   358,  1577,   409,   552,  1332,   357,  1363,
     277,   362,   368,   288,  -182,    53,  1865,  1496,  2000,  1540,
    1332,  1396,   287,  1918,   250,   640, -1547,   982,   819,   178,
    1948,    40,   287,    62,    91,   912,   982,  1014,  1513,   287,
     385,  1349,  1332,   390,   392,   421,   395,   157,  1371,   431,
     125,  1046,  1048,   466,   442,  1160,   380,  1720,  1479,  1366,
    1167,   453,   404,   157,  -183,  1088,   982,   410,   266,  1319,
     287,   786,   287,   921,   461,  1751,   275,   422,   900,   411,
   -1511,   380,  1070,   942,   424,  1345,  1524,  1309,  2093,  1527,
    1332,  1984,   459,  1282,   817,   282,   253,  1332,   486,  1726,
     922,   923,   104,   521, -1498, -1547,   371,  -741,   570,   336,
     554,  1104, -1547,   826,   425,   286,   778, -1547,  1227,   444,
    1511,   167,  1797,  1786,  1986, -1547,  1646,   455,   287,  -182,
     450, -1471,  1040,  1646,  1069,  1570,   991,  1567,    31,    40,
    1646,    92,   347,   348,   336, -1547,  1320,  1235,   458,   785,
     354,   355,  1514,   833,   237,   555,   361,   363,  1134,   157,
     290,  2201,    54,  1818,  1650, -1475,  2167,  1182,   574,  1626,
    1779,  1670,  1309,   368,   529,  1268,  1279,   826,  1845,  -183,
    1782,   426,  1569,   791,  1850,    74,   371,   105,  1228,   435,
    1644,   765,   539,   540,  2089, -1475,  1182,  2090,     3,   238,
     639,  1515,   568,    93,   644,  1372,  2168,    12,   342,   942,
     412,  1307,  1137,  1309,  1121,    63,  1150,  1151,  1542,  1486,
    1328,   649,   649,    40,  1332,   991,  1105,   565,  1899,  1070,
    1244,   343,   792,   168, -1475,   766,  1280,  1745,   427,  1698,
     166,   220,  1649,    94,  1004,    95,    55,  1070,  2091,   413,
    -597,  1152,  1780,   577, -1547,  1798,   414,   182,    54,  2202,
     634,  1147,  1148,   647,  1783,  1202,    64,   901,   -31,  1366,
   -1471,   805,  1088,   578,   575,   569,  1469,  1182,   818,   786,
    1643,  1004,  1461,   641,   991,   106,  1710,  1192,  1368,   808,
    2210,  1333,   763,  1267,  1889,  1677,    51,   768,   256,   924,
     772,   426,   773,  1727,  1333,   775,   776,  1020,  1699,   782,
   -1487,  2094,  1004,   284,  1866,   902, -1475,   254,   251,  2040,
    1729,  1919,   381,  1770,   182,   105,  1333,   415, -1498,   246,
     905,    88, -1475,  -182,   284,  1498,   284,  1900,  1833,  1759,
     284,   954,    55, -1475,  1526,  2196,  1276,  1592,  -595,   813,
     534,   262,  1134,  1134,  1134,   182,   169, -1493,    85,   460,
    1004,   779,  1134,  -597,  1482,  1537,  1397,   908,  1483, -1475,
    1771,  1283,  1552,  1448,  1333, -1475,  1220,   182,   284,   570,
    1236,  1333,   553,  -183,  1134,  1516,  1134,  1334,  1134,   144,
     416,  1284,  1134,  1134,  1134,  1134,  1134,  1134,  1134,  1134,
    1680,  1310,  1478,  1480,  1769,   262,  1137,  1137,  1137,   284,
     284,   284,  1579,  1344,   284,  1346,  1137,   832,   780,   417,
    1758,   284, -1427,   106,  1646, -1475,  1760,   550, -1475,   284,
     284,  1367,   467,  1276,  1528,  1228,  1810,  1789,  1137,  1728,
    1137, -1475,  1137,  1237,  1382,   948,  1137,  1137,  1137,  1137,
    1137,  1137,  1137,  1137,   287,  1862,  2021,   287,   287,   418,
     925,  -595,  1004,  1111,   287,  1153,  1973,   284,  2057,  1557,
    1690,  1374,   401,  1561,  1562,  2022,  1564,  1691,  1381,  2023,
    1486,  1593,  1568,  1323,  2025, -1471,  1310,   284,   284,  1332,
    2026,   284,  2027,    87,  1541,   899,   909,   904,  1368,   284,
     334, -1547,   914,   915,     4,   412,   957,  2105,  1333,   920,
    2275,  1882,  1276,  1891,   906,    13,   182,   929,   877,  2079,
     167,  2081, -1473,    62,   464,   995,    17,  1310,  -200,   240,
    1133,  1287,   447,  1772,   819,  1156,   249, -1475,  1495, -1487,
    1314,  1710,  1112,    22,   413,  1462,  1043,  2106,   402,  2098,
    1058,   414,  1062,  1752,  1062,  1068,  1706,  1043,  1134,  1134,
    1134,  1134,  1134,  1134,  1134,  1548, -1547,  2107,  1453,  1548,
   -1471,    15,  1062,   910,  1276,   820,  1216,  1787,  1149,  1819,
    2126,  2127, -1493, -1518,    74,    90,   287,  2153,  2129,  1107,
    2132,  1923,   167,  1925,   819,  1463,  1336,  1337,  1338,  1339,
    1713,  1340,   287,  1125, -1433,  1630,  1893,   290,    40,  1890,
   -1435,   249,  1137,  1137,  1137,  1137,  1137,  1137,  1137,   887,
    1141,   999,   415,   300,  1785,  1868,  1869,  1870,  1953,     5,
     878,  1103,   168,   448,  1276,   287,   287,  1892,   241,  1629,
    1041,    28,  1059,  1701,    25,   999,  1315,  1114,  1908,  1909,
    2134,  1943,  2172,  1871,  1116,   187,    74,  1468,  1876,  1877,
    1985,     5,  1879,  1880,  1881,  1006,  1884,  1885,    18,   188,
     189,   336,  1469,  1993,  1921,   336,    29,  2070,  2071,  2072,
    2073,  1157,  1288,  1929,  1679,   416,  1060,  1070,  1063,  2048,
    2135,  1896,     5,  1083,  1228,  1883,  1849,  1717,  2136,  2055,
    2055,   190,  1094,  2173,   168,    63,   182,   284,  2115,  1988,
    2116,  1202,  1138,  2117,   417,  2118,   412,  1773,   810,  1454,
     365,   491,  1714,  2119,  1329,  1330,  1331,  1262,   248,  2218,
    1894,  2145, -1471,  1217,  1342,  1202,  1761,  1202,   191,   192,
      32,   193,  2108,    19,  1812,  1764,   821,  1068,   284,   194,
     492,    33,  2055,  2055,   418,   413, -1388,  2177,  1378,  1802,
     167,  1111,   414,  1512,  1385,  1387,  1388,  1390,  2137,    35,
    1393,  1395,  1263,  1333,  1814, -1547,   412,  1102,  1407,  1408,
      37, -1547,  1960,    43,   237,  2277,  1332, -1547,  2257,  2258,
     140,  1322,   195,   196,   366, -1547,  1276,  1276,  1500, -1471,
     338,  1501,  2282,   197,  1502,  1503,  1409, -1547,  2178,  1233,
    1513,   935,  1410,  2059,  1924,   413,  1926,  1835,  1195,  1249,
    2235, -1547,   414,  2045,    74,  1168,  -200,  1059,  1276,   238,
     999,    48,  2069,   415,   287,   769,  1928,   811,  2052,  2053,
    1112, -1547,   770,  1412,  1316,   141,   142,  1413,   834,  2078,
    1189,  1004,  2174,  2175,  2146,   412,   488,    49,  1010,  1250,
    1994,  1336,  1337,  1338,  1339,  1679,  1340,  1251,  1096, -1431,
    1456,   489,   168,   412,  2056,   198,  1797, -1518,  1859,   284,
     499,   490,    44,  1004,  1836,  2040,  1837,  1971,  1091,  2074,
    2109,  2110,  2075,   415,   413,  1097,   416,  1064,    52,  2112,
    2139,   414, -1489,  1021,  1022,  1134,  1138,  1138,  1138,  1257,
    1134,   995,   413,    58,   250,  1100,  1138,  1023,  1462,   414,
      45,   117,  1258,  2279,  1514,   417,  2076,  2077,    46,   793,
    1633,  1634,  1635,  1636,  1637,  1638,  1640,  1252,  1138,  1016,
    1138,   995,  1138,  1017,  1383,  -955,  1138,  1138,  1138,  1138,
    1138,  1138,  1138,  1138,  1538,   169,   416,  2179,  2180,  1137,
      59,  1457,  1462,  1024,  1137,   418,  1995,  1501,  1463,  1460,
    1502,  1503,   415,  1515,   182,   117,   399,  2147,   794,  1574,
    1959,  1539,   470,  1575,  -955,   417,   182,  2188,   995,   199,
     415,  -955,   293,   891,    60,  2191,   400,   299,   815,   287,
     287,  2200,    61,  2114,  1778,    67,  1402,  1403,  1404,  1798,
    2194,   795,  1463,  1718,  1405,     5, -1547,   182,   816,   284,
     182,   471,   797,   435,    74,   418,   799,    71,   472,   200,
    2187,   259,   892,  1719,  1942,   416,  1504,  1505,  2213,   893,
    2214,  1803,  1546,  1276,  1585,  1585,   386,  2215,   387,  2099,
     491,  1276,  1406,   416,  1506,  1507,  1589,  1590,   384,   374,
     796,  1804,  -955,   391,   417,  2224,  2225,  2222,  2223,  2100,
    1333,   798,   556,  1427,   557,   800,  1429,  1430,   201,   492,
     559,  1546,   417,  2065,  1684,   564,   493,  1687,  1298,  1942,
    1299,   280,  1692,  1350,  1351,    78,  1555,   306,   284,   474,
    1556,  1276,    10,   236,   418,  1631,    10,   236,  2262,  2163,
     894,   307,  1138,  1138,  1138,  1138,  1138,  1138,  1138,  1220,
     469,  1489,   418,    80,    81,  -955,  1375,  2061,   102,  2063,
    1379,   494,   995,  1846,  1352,  1847,  1353,   495,  1391,  1392,
     436,  1671,  2152,  2268,  2192,   113,  2193,  1407,  1408,   308,
    1901,  2251,  1902,  1915,  -955,  1916,  2252,  1516,  1336,  1337,
    1338,  1339,   475,  1340,   496,  1836, -1428,  1837,  1354,  1355,
    1356,   497,   115,   895,   114,  1409,  1338,  1339,   859,  1340,
     117,  1410,   123,  -898,   498,   127,  -898,   128,  -955,   129,
     470,  2156,  2157,   132,  -955,  1952,  1336,  1337,  1338,  1339,
     135,  1340,  1504,  1505,  1411,   130,   131,   134,   251,   499,
     137,   500,  1412,  1942,   138,  1357,  1413,  1358,   147,   501,
    1506,  1507,   148,   178,   149,  1359,  -324,   163,   164,   471,
     165,   478,   216,   219,  2265,   222,   472,   220,  1336,  1337,
    1338,  1339,   896,  1340,  1414,  1415,  1632,   224,   473,  1416,
     502,  1336,  1337,  1338,  1339,   228,  1340,   229,  -898,  1417,
      40,  1842,   230,  1341,   287,   309,  1418,   244,  2049,    40,
     261,  1419,   268,  -898,   258,   310,   267,  1874,  1851,   262,
     277,   288,  1878,  1336,  1337,  1338,  1339,  2206,  1340,  1420,
     284,   290,  1813,   295,   297,  1682,  1360,   296,  2189,   503,
    2190,  1730,   302,  1788,  1731,   329,   330,   474,   287,  1585,
    1070,   332,  1732,  1733,  1734, -1380, -1380, -1380, -1380,   336,
    1839,  2239,  2240,   339,   341,   345,   287,   344,  1844,   353,
    -898,  -898,   376,   377,   379,  1848,   187,   393,   396,  1816,
    1210,  1211,  1212,  1213,   398,  2241,  1816,   405,   406,   433,
     188,   189,   423,  1854,   438,  -336,   439,  -898,  -898,   441,
     443,   454,   311,   312,  -898,   456,   287,   484,  -898,   530,
     475,  1860,   522,   476,   477,   313,   532,   314,   536,   560,
     999,  2259,   190,   538,  2260,   561,  1863,  -898,   563,  1864,
   -1379, -1379, -1379, -1379,   566,  -898,   182,   576,  -898,  -898,
     636,   638,   645,  -898,   652,   653,   654,  -898,   758,  -898,
     761,  1875,  -898,   570,  -898,  1910,  1911,  1912,  1913,   191,
     192,   774,   193,  1735,   783,   790,   801,  -898,   809,   803,
     194,   838,  -898,  2276,  1421,  1422,  1423,  1424,  1425,   478,
    1426,  1736,  1427,  1428,  -898,  1429,  1430,   837,  2233,  1336,
    1337,  1338,  1339,   881,  1340,  2255,  -807,  1686,  1737,  1138,
     568,   913,  1361,  1914,  1138,   916,   919,  2283,   932,  1917,
     938,   961,   933,   195,   196,   998,   935,   315,   943,   945,
     949,  1012,   955,   952,   197,  -898,  1029,  1030,   958,   959,
     986,  1007,  1029,  1037,  1039,  1015,  1032,   316,  1099,   998,
    1101,  1117,  1362,  1108,  1738,  1029,  1123,  1126,  1144,  2004,
    1139,  1950,  -898,  1145,  1037,  1093,   826,  1095,  1178,  2242,
    2243,  1336,  1337,  1338,  1339,  1154,  1340,  1183,  1161,  1689,
    1188,  2159,  1185,  1336,  1337,  1338,  1339,  1652,  1340,  1653,
    1196,  1694,  1654,  1202,  1207,  1163,  1165,  1169,  -898,  1170,
    1204,  1739,  1655,  1171,  1172,   964,   198,  -898,  -898,  1173,
    2244,  2245,  1190,  1956,  1174,  1214,  1136,  1226,  1175,  1962,
     966,  1336,  1337,  1338,  1339,  1176,  1340,  -898,  2044,  1858,
    1230,  1246,  -898,  2046,  1336,  1337,  1338,  1339,  1248,  1340,
    1245, -1382,  2058,   819,  1255,  1260,  1162,  1261,  1265,  1259,
    -898,  1270,  1272,  1070,  1740,   157,   435,  1294,  -898,  1297,
    1301,  -898,  1303,  1304,  1741,  1326,  1347,  -898,  -898,  -898,
    1364,  1377,  1398,  -898,  1384,  -898,  1399,  -898,  -898,  -898,
    1449,  1194,   287,   991,  1487,  1472,  1510,  1525,  1492,  1529,
    1543,  1551,  1558,  1559,  1571,  1581,  1566,  1583,  1641,  1587,
    1647,  1648,  1671,  1367,   967,  1340,  1651,  1700,  1029,  1705,
    1702,  1683,  1695,  1685,  1688,   964,  1029,  1234,  1693,  1723,
     199,  1463,  1746,  1750,  1748,  1742,  1762,  2096,  1754,  1656,
     966,  1766,  1790,  1657,   998,  1765,  1793,  1794,  1805,  1806,
    1807,  1820,  1821,  1831,  1840,  1829,  1658,  1855,  1887,  2254,
    1275,  1906,  1907,  1931,   996,  1933,   970,  2171,  1029,   971,
     200,  1937,  1029,  1944,  1939,  1947,  1965,  1975,  1951,  1798,
    1293,   964,  1968,  1234,  1983,  1970,  1978,  1980,  1989,  1987,
    1991,  2001,  2005,  2006,  2008,  2050,   966,  2066,  2148,  2062,
    2064,   972,  1659,  2084,  2087,  2080,  2082,  1194,  2101,  2162,
    1037,  2164,  2102,  2123,  2103,  2121,  2130,  2142,  2154,   201,
    1136,  1136,  1136,  2149,   967,  1995,  2150,  2160,  2017,  2182,
    1136,  2195,  2161,  2199,  2197,   412,  2211,  2220,  2205,  2204,
    2212,  2247,  2185,  2186,  2248,  2230,  2264,  1275,  2263,  1660,
    2266,  2281,  1136,    14,  1136,    27,  1136,    73,   247,   408,
    1136,  1136,  1136,  1136,  1136,  1136,  1136,  1136,   260,   973,
     185,   257,   281,  1661,   413,  1553,   970,   551,  2227,   971,
     967,   414,   218,   760,  1308,   483,  1586,  1311,  1582,  1110,
    1954,   412,   771,   145,   283,  2003,  2207,  1662,  2249,  2171,
     432,    66,  1663,   292,   232,   287,   956,   650,   939,   378,
    2024,   972,  1664,  1857,   974,   975,  1665,  2253,  1143,  1120,
     579,  2166,  2250,   931,   541,   162,  1275,   287,  1897,  1957,
     413,  1209,   970,  1676,  1867,   971,  1029,   414,  1675,   976,
    1218,  1895,  2228,  2229,  1920,  1494,  2232,  1757,  1490,  1536,
    2238,  1927,   415,  2234,  2086,  1521,  1194,   977,  2270,  2271,
    1509,  1946,  2273,  1549,  2274,   978,  1767,   972,   284,  1958,
    1029,  1254,   286,  1666,  1795,  1580,  1550,  1974,  1277,   973,
    2128,  1278,  1565,  1667,  1082,  1292,  1827,  1828,  1275,  1861,
    2209,  1967,  2261,  2133,  1573,  2144,   287,  1725,  1451,  1269,
    1811,  1140,  2280,   995,   964,   301,  1401,  1834,   415,   947,
     389,  1234,  1225,  1523,   777,   416,   435,  1146,  2256,   966,
     995,    75,   918,  2272,   974,   975,  1136,  1136,  1136,  1136,
    1136,  1136,  1136,  1704,  2047,   973,     0,  1343,     0,     0,
       0,   368,     0,     0,   417,     0,     0,     0,  1275,   976,
       0,     0,     0,     0,     0,     0,  2278,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   977,  1681,     0,
       0,   416,     0,     0,     0,   978,     0,   435,   284,     0,
     974,   975,     0,     0,   418,     0,     0,     0,     0,     0,
    1029,  -592,   542,     0,  -632,     0,  -632,  1050,     0,     0,
     417,  -632,     0,   967,     0,   976,     0,     0,     0,  -632,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   977,     0,     0,     0,     0,     0,     0,
       0,   978,     0,     0,   284,     0,     0,     0,     0,   435,
     418,     0,  -632,  -632,  1711,  1712,     0,     0,     0,     0,
    -632,     0,     0,  1051,     0,   970,     0,     0,   971,     0,
       0,  -632,     0,     0,     0,  -632,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -632,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     972,     0,     0,     0,     0,     0,     0,     0,     0,  -632,
       0,     0,     0,     0,     0,     0,  -632,  -632,     0,     0,
    1275,  1275,     0,     0,     0,     0,  1029,  1029,     0,     0,
       0,     0,     0,  -592,     0,     0,     0,  -592,     0,     0,
       0,     0,     0,     0,  1796,     0,     0,  -632,     0,     0,
       0,     0,  1275,     0,     0,     0,     0,     0,     0,  -632,
       0,     0,     0,  -632,     0,     0,     0,  1817,   973,     0,
       0,     0,  1826,  1826,     0,     0,  -632,     0,     0,     0,
    -592,     0,     0,  -632,     0,     0,  -632,  -632,     0,     0,
       0,     0,     0,     0,  -632,     0,     0,     0,     0,     0,
       0,  -632,     0,  -632,   998,     0,  -632,     0,     0,     0,
       0,     0,     0,   974,   975,  1852,     0,  1853,     0,     0,
     964,     0,     0, -1547,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   966,     0,     0,   976,     0,
       0,  -632,     0,     0,     0,  -632,     0,  -632, -1006,     0,
       0,     0,     0,     0,  -632,     0,   977,     0,     0,     0,
       0, -1006,     0,     0,   978,     0,   182,   284,     0,     0,
       0,     0,     0,  1194,  1194,  1194,  -632,     0,     0,     0,
       0,     0,     0,  1136,     0,   542,     0,  -632,  1136,  -632,
       0,  -632,     0,     0,  -632,     0,     0,     0,     0,     0,
       0,  1029,  -632,     0,     0,  -592,     0,     0,     0,     0,
       0,     0,  -632,  1050,     0,     0,     0,     0,     0,   967,
       0,  -632,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -632,  -632,  -632,     0,     0,  -632,
       0,  -632,     0,  -632,     0,     0,     0,     0,     0,  -632,
       0,     0,     0,     0,  -632,     0,     0,     0,  -632,  -632,
    1930,     0,     0,     0,     0,     0,  1941,  1275,  -632,   996,
    -632,   970,     0,     0,   971,  1275,     0,  -632,     0,  -632,
    -632,     0,     0,  -632,     0,  -632,  1029,     0,     0,     0,
    -632,     0,  -632,     0,  1536,     0,     0,     0,     0,  -632,
    -632,     0,     0,     0,     0,  -632,   972,   651,     0,     0,
    -632,     0,     0,     0,     0,  -632,     0,     0,     0,     0,
       0,  1941,     0,     0,     0,  1275,  -632,     0,     0,     0,
    -632,     0,     0,     0,     0,   543,     0,     0,  -632,     0,
       0,     0,  -632,     0,     0,  2042,  -632,     0,  -632,  2042,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -632,
       0,     0,     0,     0,  2042,  2042,  -632,     0,     0,  -632,
    -632,     0,     0,     0,   973,     0,     0,  -632,     0,     0,
       0,     0,     0,     0,  -632,     0,  -632,     0,     0,  -632,
       0,     0,     0,     0,     0,     0, -1463,     0,     0, -1463,
       0,     0,     0,     0,     0,     0,     0,  1219,     0,     0,
       0, -1463,     0,     0,     0,  2042,     0,     0,  2042,   974,
     975,     0,     0,     0,  -632,     0,     0,     0,  -632, -1547,
    -632,     0,     0,     0,     0,     0,     0,  -632,     0,     0,
       0,     0,     0,     0,   976,  1941,     0,     0,     0,     0,
       0,     0,     0,     0, -1006,     0,     0,     0,     0,  -632,
       0,     0,   977,     0,     0,     0,     0, -1006,     0,     0,
     978, -1463,   182,   284,  -632,     0,     0,  1037,     0,     0,
       0,     0,     0,     0,  2125,     0, -1463,     0,     0,     0,
       0,     0,     0,     0,     0,  -632,     0,     0,     0,     0,
       0,     0,     0,  2042,  -632,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -632,     0,     0,
    2165,     0,  -632,     0,  -632,     0,     0,     0,     0,     0,
       0,     0,  -632,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -632, -1463, -1463,     0,     0,     0,     0,     0,
       0,  -632,     0,     0,     0,     0,  2042,     0,     0,     0,
    -632,     0,  -632,  -632,     0,     0,  -632,     0,  -632,     0,
   -1463, -1463,     0,  -632,     0,     0,     0, -1463,     0,     0,
       0, -1463,     0,     0,     0,     0,     0,     0,  -632,     0,
       0,     0,     0,  -632,     0,     0,     0,     0,  -632,     0,
   -1463,     0,     0,     0,     0,     0,     0,     0, -1463,  -632,
       0, -1463, -1463,     0,     0,  1234, -1463,     0,   543,     0,
   -1463,  -632, -1463,     0,     0, -1463,     0, -1463,     0,     0,
    2217,  -632,     0,  2219,     0,     0,     0,     0,     0,     0,
   -1463,   963,     0,     0,   819, -1463,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0, -1463,     0,     0,
       0,     0,     0,  2236,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2042,     0,     0,
       0,     0,  2042,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   655,     0,   656,     0,     0,     0, -1463,   657,
       0,     0,     0,     0,     0,     0,     0,   658,  1037,     0,
       0,     0,     0,     0,     0,     0,   964,     0,     0,  2269,
       0,     0,     0,     0,     0, -1463,     0,     0,     0,     0,
       0,   966,     0,     0,     0,     0,     0,     0,     0,     0,
     659,   660,     0,     0,     0,     0,     0,     0,   661,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   662,
       0, -1463,     0,   663,     0,     0,  1234,     0,     0,     0,
   -1463, -1463,     0,     0,     0,   664,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0, -1463,  1407,  1408,
   -1463, -1463,     0,     0,     0, -1463,     0,   665,     0,     0,
       0,     0,     0,     0,   666,   667,     0,     0,     0,     0,
       0,     0,     0, -1463,     0,   967,  1409,     0,     0,     0,
       0, -1463,  1410,     0, -1463,     0,   412,     0,     0,     0,
   -1463, -1463, -1463,     0,     0,   668, -1463,     0, -1463,     0,
   -1463, -1463, -1463,     0,     0,  1436,     0,   669,     0,     0,
       0,   670,     0,  1412,     0,     0,   968,  1413,     0,     0,
       0,   969,     0,     0,   671,   413,     0,   970,     0,     0,
     971,   672,   414,     0,   673,   674,   963,     0,     0,   819,
       0,     0,   675,     0,     0,  1437,     0,     0,     0,   676,
    1438,   677,     0,     0,   678,     0,     0,     0,     0,     0,
       0,     0,   972,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   679,
       0,     0,     0,   680,     0,   681,     0,     0,     0,     0,
       0,     0,   682,   415,     0,     0,     0,     0,     0,     0,
       0,   964,     0,     0,     0,  -764,     0,     0,  -764,     0,
       0,     0,     0,     0,   683,     0,   966,     0,     0,     0,
     973,     0,     0,     0,     0,     0,     0,     0,     0,   684,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   157,     0,
     685,     0,     0,     0,     0,     0,   416,     0,     0,   686,
       0,     0,     0,     0,     0,   974,   975,     0,     0,     0,
       0,     0,   687,  1198,     0,     0,     0,   688,     0,   689,
    -764,     0,     0,     0, -1475,   417,     0,   690,     0,     0,
     976,     0,     0,     0,     0,  -764,     0,   691,     0,     0,
     967,     0,     0,     0,     0,     0,   692,     0,   977,     0,
       0,   412,     0,     0,     0,   693,   978,   694,   695,   284,
       0,   696,     0,   697,     0,   418,  1439,  1440,   698,     0,
       0,  1441,     0,  1427,     0,  1442,  1429,  1430,     0,     0,
       0,   968,     0,   699,     0,     0,   969,   655,   700,   656,
     413,     0,   970,   701,   657,   971,     0,   414,     0,     0,
       0,     0,   658,     0,   702,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   703,     0,     0,  -764,
       0,     0,     0,     0,     0,     0,   704,   972,     0,     0,
    -764,     0,     0,     0,     0,   659,   660,     0,     0,     0,
       0,     0,     0,   661,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   662,     0,     0,     0,   663,     0,
    -764,     0,     0,     0,     0,  -764,     0,     0,   415,  -764,
     664,  -764,     0,     0,  -764,     0,  -764,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   665,     0,     0,   973,     0,     0,     0,   666,
     667,     0,     0,     0,     0,     0,  -764,     0,     0,     0,
       0,  -764,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   963,     0,     0,   819,
     668,   416,     0,     0,     0,     0,     0,     0,     0,     0,
     974,   975,   669,     0,     0,     0,   670,  -764,     0,     0,
    1156,     0,     0,     0,     0,     0,     0, -1475,     0,   671,
     417,     0,     0,     0,     0,   976,   672,     0,     0,   673,
     674,     0,     0,     0,  -764,     0,     0,   675,     0,     0,
       0,     0,     0,   977,   676, -1471,   677,     0,     0,   678,
       0,   978,     0,   963,   284,     0,   819,     0,     0,     0,
     418,   964,     0,     0,  -764,     0,     0,     0,  1199,     0,
    -764,     0,     0,     0,     0,   963,   966,     0,   819,  -764,
    -764,     0,     0,     0,   679,     0,     0,     0,   680,     0,
     681,     0,     0,     0,     0,     0,     0,   682,     0,  -764,
       0,     0,     0,     0,  -764,     0,     0,     0,     0,  -764,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   683,
       0,     0,  -764,     0,     0,     0, -1475,     0,   964,     0,
    -764,     0,     0,  -764,   684,     0,     0,     0,     0,  -764,
       0,     0,     0,   966,     0,     0,     0,     0,     0,     0,
     964,     0,     0,     0,     0,   685,     0,     0,     0,     0,
     967,     0,     0,     0,   686,   966,     0,     0,     0,   963,
       0,   412,   819,     0,     0,     0,     0,   687,  1085,     0,
       0,     0,   688,     0,   689,     0,     0,     0,     0,     0,
       0,     0,   690,  1554,     0,     0,     0,     0,     0,     0,
       0,   968,   691,     0,     0,     0,   969, -1471,     0,     0,
     413,   692,   970,     0,     0,   971,     0,   414,     0,     0,
     693,     0,   694,   695,     0,     0,   696,   967,   697,     0,
       0,     0,     0,   698,     0,     0,   963,     0,   412,   819,
       0,     0,     0,     0,   964,     0,     0,   972,   699,   967,
       0,     0,     0,   700,     0,   965,     0,     0,   701,   966,
     412,     0,     0,     0,     0,     0,     0,     0,   968,   702,
       0,     0,     0,   969, -1471,  1291,     0,   413,     0,   970,
       0,   703,   971,     0,   414,     0,     0,     0,   415,     0,
     968,     0,     0,     0,     0,   969,     0,     0,     0,   413,
       0,   970,     0,     0,   971,     0,   414,     0,     0,     0,
       0,   964,     0,     0,   972,   973,   963,     0,     0,   819,
       0,     0,  1044,     0,     0,     0,   966,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   972,     0,     0,     0,
       0,     0,     0,   967,     0,     0,     0,     0,     0,     0,
       0,   416,     0,     0,   412,   415,     0,     0,     0,     0,
     974,   975,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   415,     0,     0,
     417,     0,   973,     0,   968,   976,     0,     0,     0,   969,
       0,   964,     0,   413,     0,   970,     0,     0,   971,     0,
     414,     0,     0,   977,   973,   963,   966,     0,   819,     0,
     967,   978,     0,     0,   284,     0,     0,     0,   416,  1085,
     418,   412,     0,     0,     0,     0,     0,   974,   975,     0,
     972,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     416,     0,     0,     0,  1555,     0,     0,   417,  1556,   974,
     975,   968,   976,     0,     0,     0,   969,     0,     0,     0,
     413,     0,   970,     0,     0,   971,     0,   414,     0,   417,
     977,   415,     0,     0,   976,     0,     0,     0,   978,     0,
     964,   284,   963,     0,     0,   819,     0,   418,     0,     0,
     967,  1089,   977,     0,     0,   966,     0,   972,   973,     0,
     978,   412,     0,   284,     0,     0,     0,     0,     0,   418,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   968,     0,     0,   416,     0,   969,     0,   415,     0,
     413,     0,   970,   974,   975,   971,     0,   414,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   964,     0,     0,
       0,     0,     0,   417,     0,   973,     0,     0,   976,     0,
       0,     0,   966,     0,     0,     0,     0,   972,     0,   967,
       0,     0,     0,     0,     0,     0,   977,     0,   963,     0,
     412,   819,     0,     0,   978,     0,     0,   284,     0,     0,
       0,   416,     0,   418,     0,     0,     0,     0,     0,     0,
     974,   975,     0,     0,     0,     0,     0,     0,   415,     0,
     968,     0,     0,     0,     0,   969,     0,     0,     0,   413,
     417,   970,     0,     0,   971,   976,   414,     0,     0,     0,
       0,     0,     0,     0,     0,   973,     0,     0,     0,     0,
       0,     0,     0,   977,     0,     0,   967,     0,     0,     0,
       0,   978,     0,   964,   284,     0,   972,   412,     0,     0,
     418,     0,     0,     0,   963,     0,     0,   819,   966,     0,
       0,   416,     0,     0,     0,     0,     0,     0,     0,     0,
     974,   975,     0,     0,     0,     0,     0,   968,     0,     0,
       0,     0,   969,     0,     0,     0,   413,   415,   970,     0,
     417,   971,     0,   414,     0,   976,     0,     0,     0,     0,
       0,     0,     0,   963,     0,     0,   819,     0,     0,     0,
       0,     0,     0,   977,   973,   963,     0,     0,   819,     0,
       0,   978,     0,   972,   284,     0,     0,     0,     0,   964,
     418,     0,     0,     0,     0,     0,     0,     0,  1296,     0,
       0,     0,   967,     0,   966,     0,     0,     0,     0,     0,
     416,     0,     0,   412,     0,     0,     0,     0,     0,   974,
     975,     0,     0,     0,   415,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   964,   417,
       0,     0,     0,   968,   976,     0,     0,     0,   969,     0,
     964,   973,   413,   966,   970,     0,     0,   971,     0,   414,
       0,     0,   977,     0,     0,   966,     0,     0,     0,     0,
     978,     0,     0,   284,     0,     0,     0,     0,     0,   418,
       0,     0,     0,   963,     0,     0,   819,   416,   967,   972,
       0,     0,     0,     0,     0,     0,   974,   975,     0,   412,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1180,     0,     0,     0,   417,     0,     0,     0,
       0,   976,     0,     0,     0,     0,     0,     0,     0,   968,
     415,     0,     0,     0,   969,     0,     0,   967,   413,   977,
     970,     0,     0,   971,     0,   414,     0,   978,   412,   967,
     284,     0,     0,     0,     0,     0,   418,   973,   964,     0,
     412,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   966,     0,   972,     0,     0,   968,     0,
       0,     0,     0,   969,     0,     0,     0,   413,     0,   970,
     968,     0,   971,   416,   414,   969,     0,     0,     0,   413,
       0,   970,   974,   975,   971,     0,   414,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   415,     0,     0,     0,
       0,     0,   417,     0,   972,     0,     0,   976,     0,     0,
       0,     0,     0,     0,     0,     0,   972,     0,     0,     0,
       0,     0,     0,   973,     0,   977,     0,     0,     0,     0,
       0,     0,     0,   978,     0,     0,   284,   967,     0,     0,
       0,     0,   418,     0,     0,   415,     0,     0,   412,     0,
       0,     0,     0,  1563,     0,     0,     0,   415,     0,   416,
       0,     0,     0,     0,     0,     0,     0,     0,   974,   975,
       0,     0,   973,     0,     0,     0,     0,     0,   968,     0,
       0,     0,     0,   969,   973,     0,     0,  1008,   417,   970,
       0,     0,   971,   976,   414,     0,     0,     0,     0,     0,
       0,     0,     0,  1695,     0,     0,     0,     0,   416,     0,
       0,   977,     0,     0,     0,     0,     0,   974,   975,   978,
     416,     0,   284,     0,   972,     0,     0,     0,   418,   974,
     975,     0,     0,     0,     0,     0,     0,   417,     0,     0,
       0,     0,   976,     0,     0,     0,     0,     0,     0,   417,
       0,     0,     0,     0,   976,     0,     0,     0,     0,     0,
     977,     0,     0,     0,     0,   415,     0,     0,   978,     0,
       0,   284,   977,     0,     0,     0,     0,   418,     0,     0,
     978,     0,     0,   284,     0,     0,     0,   581,     0,   418,
       0,     0,   973,     0,     0,     0,     0,     0,     0,     0,
     582,     0,     0,   583,   584,   585,   586,   587,   588,   589,
       0,   583,   584,   585,   586,   587,   588,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   416,     0,
       0,     0,     0,     0,     0,     0,     0,   974,   975,   590,
       0,   591,   592,   593,   594,   595,   596,   590,     0,   591,
     592,   593,   594,   595,   596,     0,     0,   417,     0,     0,
       0,     0,   976,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     977,   597,     0,     0,     0,     0,     0,     0,   978,   597,
       0,   284,     0,     0,     0,     0,  1594,   418,  1595,     0,
       0,  1596,   583,   584,   585,   586,   587,   588,   589,  1597,
    1598,  1599,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1600,     0,     0,     0,     0,     0,     0,     0,   590,     0,
     591,   592,   593,   594,   595,   596,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   598,     0,     0,     0,     0,     0,     0,
       0,   598,     0,     0,     0,     0,    40,     0,     0,   599,
     597,     0,     0,     0,     0, -1528,     0,     0,     0,     0,
     583,   584,   585,   586,   587,   588,   589,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   600,     0,     0,     0,     0,  2009,  2010,
    1601,   600,     0,     0,     0,     0,   590,     0,   591,   592,
     593,   594,   595,   596,     0,   601,     0,     0,  1602,     0,
       0,  1603,  1604,     0,     0,     0,     0,     0,     0,     0,
     602,     0,     0,     0,     0,  1605,     0,   603,   602,   604,
       0,     0,   598,     0,     0,     0,     0,   604,   597,     0,
       0,     0,   605,     0,     0,     0,     0,     0,   599,     0,
     605,     0,   606,     0,     0,     0,     0,     0,     0,   607,
       0,     0,  1606,     0,     0,     0,   964,     0,     0,     0,
       0,  1607,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   966,   600,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   608,     0,   609,   610,
     611,     0,     0,     0,  1608,     0,   609,   610,   611,     0,
       0,  2011,     0,     0,     0,     0,     0,     0,  1609,   602,
     598,     0,   612,     0,     0,     0,   603,     0,   604,     0,
       0,     0,     0,     0,     0,     0,   599,     0,     0, -1528,
       0,   605,  1610,     0,     0,     0,     0,   613,   614,   615,
    2012,  2013,     0,     0,     0,   613,   614,   615,     0,   964,
     616,     0,     0,   617,     0,   967,  1611,     0,     0,     0,
     600,  1612,     0,     0,   966,  2014,   412,     0,     0,     0,
       0,     0,     0,  -331,     0,  1613,     0,     0,     0,     0,
       0,     0,   601,     0,     0,   608,     0,   609,   610,   611,
       0,     0,     0,     0,     0,     0,  1128,   602,     0,     0,
       0,   969,     0,     0,   603,   413,   604,   970,     0,  2015,
     971,     0,   414,   964,     0,     0,     0,     0,     0,   605,
       0,  1614,     0,     0,     0,     0,     0,     0,   966,     0,
       0,     0,  1615,     0,     0,     0,   613,   614,   615,     0,
       0,     0,   972,     0,     0,     0,     0,     0,   967,   616,
       0,  1616,   617,     0,     0,     0,     0,     0,     0,   412,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1617,   608,     0,   609,   610,   611,     0,     0,
       0,     0,  2016,   415,     0,     0,     0,     0,     0,  1128,
       0,     0,     0,     0,   969,     0,  2017,     0,   413,     0,
     970,     0,     0,   971,     0,   414,     0,     0,     0,     0,
     973,     0,   967,     0,     0,     0,     0,     0,     0,  2018,
       0,     0,     0,   412,   613,   614,   615,     0,     0,     0,
       0,     0,     0,     0,     0,   972,     0,   616,     0,     0,
     617,  2019,     0,     0,     0,     0,   416,     0,     0,     0,
       0,     0,     0,  1128,     0,   974,   975,     0,   969,     0,
    2020,     0,   413,     0,   970,     0,     0,   971,     0,   414,
       0,     0,     0,     0,     0,   417,   415,     0,     0,     0,
     976,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   977,   972,
       0,     0,     0,   973,     0,     0,   978,     0,     0,   284,
       0,     0,     0,     0,     0,   418,  1129,  1130,     0,     0,
       0,     0,     0,     0,  1639,  1131,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   416,
     415,     0,     0,     0,     0,     0,     0,     0,   974,   975,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   973,   417,     0,
       0,     0,     0,   976,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   977,     0,     0,     0,     0,     0,     0,     0,   978,
       0,     0,   284,   416,     0,     0,     0,     0,   418,  1129,
    1130,     0,   974,   975,     0,     0,     0,  1873,  1131,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   417,     0,     0,     0,     0,   976,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   977,     0,     0,     0,     0,
       0,     0,     0,   978,     0,     0,   284,     0,     0,     0,
       0,     0,   418,  1129,  1130,     0,     0,     0,     0,     0,
       0,     0,  1131
};

static const yytype_int16 yycheck[] =
{
      83,   168,   388,   221,   130,   387,   637,   617,   497,   673,
     883,   847,   430,   821,  1007,   245,  1257,   606,  1187,  1085,
    1187,   188,   189,  1187,   842,  1187,   193,   194,   195,   196,
     197,  1079,   199,  1187,   201,   853,  1027,   844,  1325,   643,
     702,   580,  1099,   785,  1035,  1367,  1368,  1220,   221,   843,
       6,   978,   270,  1000,  1069,  1681,   274,  1325,   276,   185,
     861,  1325,   453,    17,    22,    49,  1325,   285,   235,   152,
     237,   560,  1325,   874,  1325,   349,    13,   244,  1211,  1212,
    1213,     6,     6,     6,    49,   252,    54,    48,    21,     9,
    1081,     9,    69,     6,    23,    85,    28,   270,   328,   266,
     267,   274,   269,   276,     9,   335,    17,    69,   275,  1157,
      56,    94,   285,    84,   115,    72,   118,   111,  1832,  1261,
      69,  1180,   340,   118,    62,    56,   104,   841,     9,   178,
    1776,   210,   350,   165,    71,   772,   850,   851,    56,   357,
     307,  1156,    69,   310,   311,   419,   313,    49,   146,   367,
      87,   865,   866,    56,   384,   963,   168,  1461,  1217,    65,
     968,   391,   329,    49,   115,   879,   880,   340,   190,  1116,
     388,   580,   390,    60,   404,  1479,   198,   350,   120,   346,
     112,   168,   242,   814,   357,  1151,  1243,   119,   203,  1248,
      69,  1817,   167,   118,   219,   217,     9,    69,   428,    94,
      87,    88,    22,   433,   210,   262,   289,   183,   214,   230,
     484,   115,   168,    30,    23,   388,     9,   293,  1026,   386,
    1235,   239,   123,  1527,  1820,   234,  1351,   394,   446,   230,
     230,    48,   863,  1358,   147,  1301,   230,  1296,    24,   210,
    1365,   268,   264,   265,   230,   254,  1119,    91,   397,   788,
     272,   273,   170,   644,   365,   485,   278,   279,   935,    49,
     172,   183,   315,  1567,  1358,   230,   252,   981,   498,  1326,
     196,  1365,   119,   446,   441,  1064,  1077,    30,  1600,   230,
      28,   210,  1297,   361,  1606,   303,   369,   245,  1279,   372,
    1347,   120,   459,   460,  1940,    85,  1010,  1943,     0,   410,
     530,   219,    37,   330,   534,   303,   292,   447,   207,   940,
     191,  1100,   935,   119,   924,   347,   953,   954,  1265,  1492,
    1128,   539,   540,   210,    69,   230,   230,   494,   318,   242,
    1044,   230,   410,   351,   318,   164,   396,  1470,   360,  1398,
     126,   273,  1357,   370,  1180,   372,   399,   242,  1944,   230,
     334,   955,   278,   520,   171,   256,   237,   433,   315,   281,
     527,   950,   951,   230,   112,   341,   398,   309,   447,    65,
     123,   601,  1086,   522,   500,   110,   433,  1091,   403,   788,
    1346,  1217,  1200,   314,   230,   343,  1452,   230,   294,   607,
    2104,   353,   559,  1063,  1698,   230,    39,   564,   447,   286,
     567,   210,   569,   298,   353,   572,   573,  1225,  1399,   576,
     322,   426,  1248,   434,   416,   357,   318,   230,   356,   440,
    1468,   416,   434,     9,   433,   245,   353,   308,   434,   447,
     114,   408,   318,   434,   434,  1229,   434,   427,  1580,  1496,
     434,   402,   399,   427,  1245,  2091,  1069,   434,   334,   616,
     396,   434,  1129,  1130,  1131,   433,   434,   428,   426,   434,
    1296,   254,  1139,   447,   397,  1259,  1180,    32,   401,   434,
      56,   396,   396,  1187,   353,   440,   430,   433,   434,   214,
     324,   353,   393,   434,  1161,   403,  1163,   449,  1165,   447,
     371,   416,  1169,  1170,  1171,  1172,  1173,  1174,  1175,  1176,
     449,   433,  1216,  1217,  1519,   434,  1129,  1130,  1131,   434,
     434,   434,  1306,  1144,   434,  1152,  1139,   643,   311,   400,
    1493,   434,   449,   343,  1649,   427,  1499,   464,   318,   434,
     434,   227,   435,  1156,  1248,  1526,  1551,  1530,  1161,   434,
    1163,   427,  1165,   387,  1167,   819,  1169,  1170,  1171,  1172,
    1173,  1174,  1175,  1176,   772,  1649,  1843,   775,   776,   440,
     447,   447,  1398,   369,   782,   956,  1807,   434,  1872,  1283,
     449,  1160,    31,  1287,  1288,  1843,  1290,   449,  1167,  1843,
    1753,  1323,  1296,  1122,  1843,   402,   433,   434,   434,    69,
    1843,   434,  1843,   136,  1264,   762,   161,   764,   294,   434,
     243,   262,   775,   776,   179,   191,   836,   194,   353,   782,
    2236,   219,  1235,   153,   298,   447,   433,   784,   230,  1923,
     239,  1925,   357,   165,   136,   843,    11,   433,   434,   318,
     935,   183,   272,   219,     9,    30,   172,   427,  1227,   104,
     234,  1707,   448,   117,   230,   209,   864,   234,   107,  1953,
     868,   237,   870,   183,   872,   873,  1450,   875,  1335,  1336,
    1337,  1338,  1339,  1340,  1341,  1269,   293,   254,   183,  1273,
      65,   147,   890,   238,  1297,    50,    49,   183,   952,   183,
    1984,  1985,   184,    62,   303,    70,   904,  2009,  1989,   907,
    1991,  1750,   239,  1752,     9,   259,   441,   442,   443,   444,
     160,   446,   920,   933,   449,  1328,   153,   172,   210,  1700,
     434,   247,  1335,  1336,  1337,  1338,  1339,  1340,  1341,   184,
     938,   844,   308,   447,  1525,  1672,  1673,  1674,  1787,   304,
     342,   904,   351,   373,  1357,   953,   954,   277,   427,  1328,
     863,   447,   868,  1407,    27,   868,   340,   920,  1721,  1722,
     163,  1766,   241,  1680,   921,    11,   303,   418,  1685,  1686,
    1819,   304,  1689,  1690,  1691,   848,  1693,  1694,   230,    25,
      26,   230,   433,  1830,  1747,   230,    99,  1910,  1911,  1912,
    1913,   176,   334,  1756,  1373,   371,   869,   242,   871,  1855,
     203,   272,   304,   876,  1785,   403,  1603,  1459,   211,  1865,
    1866,    57,   885,   292,   351,   347,   433,   434,  1977,  1824,
    1977,   341,   935,  1977,   400,  1977,   191,   403,   220,   334,
     196,   198,   282,  1977,  1129,  1130,  1131,   252,   447,  2130,
     277,   286,   227,   206,  1139,   341,  1500,   341,    94,    95,
     230,    97,   429,   305,  1558,  1509,   221,  1065,   434,   105,
     227,   447,  1918,  1919,   440,   230,   395,   241,  1163,  1545,
     239,   369,   237,     9,  1169,  1170,  1171,  1172,   281,    82,
    1175,  1176,   297,   353,  1560,   234,   191,   899,   153,   154,
     117,   194,   195,   349,   365,  2261,    69,   234,  2192,  2193,
     312,  1121,   148,   149,   270,   254,  1519,  1520,     9,   294,
     447,    12,  2278,   159,    15,    16,   181,   254,   292,  1035,
      56,   450,   187,  1886,  1750,   230,  1752,   245,  1001,   163,
    2161,   234,   237,  1848,   303,   969,   434,  1053,  1551,   410,
    1053,   447,  1905,   308,  1152,   312,  1754,   339,  1863,  1864,
     448,   254,   319,   218,  1111,   367,   368,   222,   176,  1922,
     994,  1787,   441,   442,  2002,   191,     4,   300,   850,   203,
     151,   441,   442,   443,   444,  1554,   446,   211,     8,   449,
     317,    19,   351,   191,  1866,   231,   123,   356,  1642,   434,
     357,    29,   166,  1819,   312,   440,   314,  1805,   880,  1914,
    1963,  1964,  1917,   308,   230,    35,   371,   872,   447,  1972,
    1993,   237,   230,   289,   290,  1682,  1129,  1130,  1131,   415,
    1687,  1229,   230,   447,    62,   890,  1139,   303,   209,   237,
     204,   434,   428,  2264,   170,   400,  1918,  1919,   212,   361,
    1335,  1336,  1337,  1338,  1339,  1340,  1341,   281,  1161,   397,
    1163,  1259,  1165,   401,  1167,   191,  1169,  1170,  1171,  1172,
    1173,  1174,  1175,  1176,     8,   434,   371,   441,   442,  1682,
     447,   408,   209,   349,  1687,   440,   257,    12,   259,  1195,
      15,    16,   308,   219,   433,   434,   164,  2002,   410,   156,
    1794,    35,   191,   160,   230,   400,   433,  2060,  1306,   345,
     308,   237,   227,   191,   349,  2068,   184,   232,   164,  1317,
    1318,  2094,   447,  1976,  1522,   117,    12,    13,    14,   256,
    2083,   361,   259,   234,    20,   304,   429,   433,   184,   434,
     433,   230,   361,  1206,   303,   440,   361,   132,   237,   385,
    2055,   447,   230,   254,  1765,   371,   247,   248,  2111,   237,
    2113,   234,  1268,  1766,  1317,  1318,   312,  2120,   314,   234,
     198,  1774,    58,   371,   265,   266,   227,   228,   306,   294,
     410,   254,   308,   311,   400,   227,   228,  2140,  2141,   254,
     353,   410,   271,   448,   273,   410,   451,   452,   434,   227,
     488,  1307,   400,  1897,  1385,   493,   234,  1388,   312,  1820,
     314,   447,  1393,    25,    26,   447,   397,    47,   434,   308,
     401,  1824,     2,   158,   440,  1328,     6,   162,  2201,  2017,
     308,    61,  1335,  1336,  1337,  1338,  1339,  1340,  1341,   430,
     121,   432,   440,   349,   436,   371,  1161,  1891,   166,  1893,
    1165,   279,  1450,   150,    66,   152,    68,   285,  1173,  1174,
     375,   263,   264,  2216,  2080,   447,  2082,   153,   154,    99,
     258,  2176,   260,   150,   400,   152,  2181,   403,   441,   442,
     443,   444,   371,   446,   312,   312,   449,   314,   100,   101,
     102,   319,   233,   371,   349,   181,   443,   444,     1,   446,
     434,   187,   334,     6,   332,   447,     9,   447,   434,   447,
     191,   263,   264,   352,   440,  1784,   441,   442,   443,   444,
     212,   446,   247,   248,   210,   447,   447,   447,   356,   357,
      71,   359,   218,  1944,   398,   147,   222,   149,   447,   367,
     265,   266,   349,   178,   229,   157,   434,   434,   447,   230,
     447,   440,   276,   447,  2207,   388,   237,   273,   441,   442,
     443,   444,   440,   446,   250,   251,   449,    24,   249,   255,
     398,   441,   442,   443,   444,   447,   446,   349,    81,   265,
     210,  1591,   325,   453,  1582,   215,   272,   365,  1857,   210,
     104,   277,   360,    96,   447,   225,   377,  1682,  1608,   434,
      56,    84,  1687,   441,   442,   443,   444,  2101,   446,   295,
     434,   172,  1559,   447,   344,   453,   228,   349,  2062,   447,
    2064,    33,   434,  1529,    36,   365,   276,   308,  1626,  1582,
     242,   106,    44,    45,    46,   419,   420,   421,   422,   230,
    1587,    89,    90,   356,   207,   243,  1644,   447,  1595,    67,
     153,   154,   447,   349,   447,  1602,    11,   243,    23,  1565,
     419,   420,   421,   422,   270,   113,  1572,   434,   447,   294,
      25,    26,   230,  1626,   447,    83,   447,   180,   181,    83,
     434,   428,   312,   313,   187,   434,  1684,   393,   191,   396,
     371,  1644,   310,   374,   375,   325,   228,   327,   196,   312,
    1603,  2195,    57,   434,  2198,   396,  1653,   210,   357,  1656,
     419,   420,   421,   422,    55,   218,   433,   377,   221,   222,
      27,   184,   365,   226,   447,   447,   349,   230,   447,   232,
     377,  1684,   235,   214,   237,  1726,  1727,  1728,  1729,    94,
      95,   357,    97,   155,   434,   221,   430,   250,   210,   339,
     105,   230,   255,  2247,   440,   441,   442,   443,   444,   440,
     446,   173,   448,   449,   267,   451,   452,   106,  2158,   441,
     442,   443,   444,   299,   446,  2186,   398,   449,   190,  1682,
      37,   374,   394,  1730,  1687,   280,   274,  2281,   440,  1736,
     393,   840,   396,   148,   149,   844,   450,   427,    27,   355,
     270,   850,   171,   454,   159,   308,   855,   856,   447,   447,
     434,   398,   861,   862,   863,   230,   133,   447,   104,   868,
      17,   169,   434,   433,   236,   874,   184,   395,   393,  1839,
     450,  1778,   335,   230,   883,   884,    30,   886,   125,   287,
     288,   441,   442,   443,   444,   124,   446,   201,   450,   449,
     396,  2013,    56,   441,   442,   443,   444,    31,   446,    33,
     127,   449,    36,   341,   129,   450,   450,   450,   371,   450,
     312,   283,    46,   450,   450,    81,   231,   380,   381,   450,
     328,   329,   426,  1789,   450,   130,   935,    98,   450,  1795,
      96,   441,   442,   443,   444,   450,   446,   400,  1845,   449,
     392,   134,   405,  1850,   441,   442,   443,   444,    49,   446,
     396,   395,   449,     9,   135,   395,   965,   390,   176,   393,
     423,   140,   428,   242,   336,    49,  1789,   143,   431,   176,
     109,   434,   326,   373,   346,   111,   111,   440,   441,   442,
     433,   396,   183,   446,   434,   448,   334,   450,   451,   452,
     302,  1000,  1950,   230,   131,   160,   168,   396,   430,   359,
     206,   396,    49,   214,   206,   119,   176,   273,   358,   189,
     439,   438,   263,   227,   180,   446,   214,   334,  1027,   396,
     391,   449,   366,   449,   449,    81,  1035,  1036,   449,   128,
     345,   259,   262,   183,   258,   407,   324,  1950,   393,   173,
      96,    49,   135,   177,  1053,   396,     8,   176,   430,   123,
     430,   396,     9,   301,   170,   300,   190,   198,   261,  2185,
    1069,   322,   337,   122,   230,   427,   232,  2037,  1077,   235,
     385,   107,  1081,    49,   427,   172,   138,   255,   278,   256,
    1089,    81,   139,  1092,   293,   234,   141,   282,   110,   277,
     387,     7,   113,   216,    66,   397,    96,   126,  2005,   153,
     153,   267,   236,   133,    99,   321,   321,  1116,    49,  2016,
    1119,  2018,   234,   260,   214,   142,    93,   145,   199,   434,
    1129,  1130,  1131,    90,   180,   257,   217,   188,   383,   434,
    1139,    49,   430,   300,   399,   191,   234,   144,   337,  2097,
     234,   176,  2049,  2050,   286,   171,   415,  1156,   300,   283,
     137,    49,  1161,     6,  1163,    21,  1165,    53,   170,   334,
    1169,  1170,  1171,  1172,  1173,  1174,  1175,  1176,   185,   335,
     130,   180,   203,   307,   230,  1280,   232,   480,  2148,   235,
     180,   237,   134,   553,  1101,   419,  1318,  1103,  1311,   910,
    1788,   191,   565,   108,   219,  1835,  2103,   331,  2168,  2169,
     369,    48,   336,   226,   152,  2163,   835,   540,   813,   301,
    1843,   267,   346,  1628,   380,   381,   350,  2183,   940,   923,
     524,  2032,  2169,   788,   462,   122,  1235,  2185,  1709,  1792,
     230,  1010,   232,  1370,  1668,   235,  1245,   237,  1369,   405,
    1015,  1707,  2149,  2150,  1743,  1225,  2153,  1492,  1222,  1258,
    2163,  1753,   308,  2160,  1934,  1238,  1265,   423,  2228,  2229,
    1232,  1774,  2232,  1272,  2234,   431,  1517,   267,   434,  1793,
    1279,  1053,  2185,   407,  1541,  1307,  1273,  1809,  1075,   335,
    1987,  1077,  1291,   417,   875,  1086,  1572,  1572,  1297,  1646,
    2104,  1800,  2199,  1992,  1303,  1998,  2254,  1466,  1189,  1065,
    1554,   936,  2272,  2261,    81,   233,  1185,  1582,   308,   818,
     309,  1320,  1018,  1243,   574,   371,  2139,   945,  2187,    96,
    2278,    56,   779,  2230,   380,   381,  1335,  1336,  1337,  1338,
    1339,  1340,  1341,  1413,  1851,   335,    -1,  1142,    -1,    -1,
      -1,  2254,    -1,    -1,   400,    -1,    -1,    -1,  1357,   405,
      -1,    -1,    -1,    -1,    -1,    -1,  2263,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   423,  1377,    -1,
      -1,   371,    -1,    -1,    -1,   431,    -1,  2200,   434,    -1,
     380,   381,    -1,    -1,   440,    -1,    -1,    -1,    -1,    -1,
    1399,     0,     1,    -1,     3,    -1,     5,   174,    -1,    -1,
     400,    10,    -1,   180,    -1,   405,    -1,    -1,    -1,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   423,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   431,    -1,    -1,   434,    -1,    -1,    -1,    -1,  2262,
     440,    -1,    51,    52,  1453,  1454,    -1,    -1,    -1,    -1,
      59,    -1,    -1,   230,    -1,   232,    -1,    -1,   235,    -1,
      -1,    70,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     267,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,
      -1,    -1,    -1,    -1,    -1,    -1,   115,   116,    -1,    -1,
    1519,  1520,    -1,    -1,    -1,    -1,  1525,  1526,    -1,    -1,
      -1,    -1,    -1,   132,    -1,    -1,    -1,   136,    -1,    -1,
      -1,    -1,    -1,    -1,  1543,    -1,    -1,   146,    -1,    -1,
      -1,    -1,  1551,    -1,    -1,    -1,    -1,    -1,    -1,   158,
      -1,    -1,    -1,   162,    -1,    -1,    -1,  1566,   335,    -1,
      -1,    -1,  1571,  1572,    -1,    -1,   175,    -1,    -1,    -1,
     179,    -1,    -1,   182,    -1,    -1,   185,   186,    -1,    -1,
      -1,    -1,    -1,    -1,   193,    -1,    -1,    -1,    -1,    -1,
      -1,   200,    -1,   202,  1603,    -1,   205,    -1,    -1,    -1,
      -1,    -1,    -1,   380,   381,  1614,    -1,  1616,    -1,    -1,
      81,    -1,    -1,   390,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,   405,    -1,
      -1,   240,    -1,    -1,    -1,   244,    -1,   246,   415,    -1,
      -1,    -1,    -1,    -1,   253,    -1,   423,    -1,    -1,    -1,
      -1,   428,    -1,    -1,   431,    -1,   433,   434,    -1,    -1,
      -1,    -1,    -1,  1672,  1673,  1674,   275,    -1,    -1,    -1,
      -1,    -1,    -1,  1682,    -1,     1,    -1,     3,  1687,     5,
      -1,   290,    -1,    -1,    10,    -1,    -1,    -1,    -1,    -1,
      -1,  1700,    18,    -1,    -1,   304,    -1,    -1,    -1,    -1,
      -1,    -1,   311,   174,    -1,    -1,    -1,    -1,    -1,   180,
      -1,   320,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   333,    51,    52,    -1,    -1,   338,
      -1,   340,    -1,    59,    -1,    -1,    -1,    -1,    -1,   348,
      -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    74,   358,
    1759,    -1,    -1,    -1,    -1,    -1,  1765,  1766,   367,   230,
      86,   232,    -1,    -1,   235,  1774,    -1,   376,    -1,   378,
     379,    -1,    -1,   382,    -1,   384,  1785,    -1,    -1,    -1,
     389,    -1,   108,    -1,  1793,    -1,    -1,    -1,    -1,   115,
     116,    -1,    -1,    -1,    -1,   404,   267,   123,    -1,    -1,
     409,    -1,    -1,    -1,    -1,   414,    -1,    -1,    -1,    -1,
      -1,  1820,    -1,    -1,    -1,  1824,   425,    -1,    -1,    -1,
     146,    -1,    -1,    -1,    -1,   434,    -1,    -1,   437,    -1,
      -1,    -1,   158,    -1,    -1,  1844,   162,    -1,   447,  1848,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   175,
      -1,    -1,    -1,    -1,  1863,  1864,   182,    -1,    -1,   185,
     186,    -1,    -1,    -1,   335,    -1,    -1,   193,    -1,    -1,
      -1,    -1,    -1,    -1,   200,    -1,   202,    -1,    -1,   205,
      -1,    -1,    -1,    -1,    -1,    -1,     6,    -1,    -1,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    -1,    -1,
      -1,    21,    -1,    -1,    -1,  1914,    -1,    -1,  1917,   380,
     381,    -1,    -1,    -1,   240,    -1,    -1,    -1,   244,   390,
     246,    -1,    -1,    -1,    -1,    -1,    -1,   253,    -1,    -1,
      -1,    -1,    -1,    -1,   405,  1944,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   415,    -1,    -1,    -1,    -1,   275,
      -1,    -1,   423,    -1,    -1,    -1,    -1,   428,    -1,    -1,
     431,    81,   433,   434,   290,    -1,    -1,  1976,    -1,    -1,
      -1,    -1,    -1,    -1,  1983,    -1,    96,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   311,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  2002,   320,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   333,    -1,    -1,
    2019,    -1,   338,    -1,   340,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   348,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   358,   153,   154,    -1,    -1,    -1,    -1,    -1,
      -1,   367,    -1,    -1,    -1,    -1,  2055,    -1,    -1,    -1,
     376,    -1,   378,   379,    -1,    -1,   382,    -1,   384,    -1,
     180,   181,    -1,   389,    -1,    -1,    -1,   187,    -1,    -1,
      -1,   191,    -1,    -1,    -1,    -1,    -1,    -1,   404,    -1,
      -1,    -1,    -1,   409,    -1,    -1,    -1,    -1,   414,    -1,
     210,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,   425,
      -1,   221,   222,    -1,    -1,  2114,   226,    -1,   434,    -1,
     230,   437,   232,    -1,    -1,   235,    -1,   237,    -1,    -1,
    2129,   447,    -1,  2132,    -1,    -1,    -1,    -1,    -1,    -1,
     250,     6,    -1,    -1,     9,   255,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   267,    -1,    -1,
      -1,    -1,    -1,  2162,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  2176,    -1,    -1,
      -1,    -1,  2181,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,    -1,     5,    -1,    -1,    -1,   308,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,  2207,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,  2218,
      -1,    -1,    -1,    -1,    -1,   335,    -1,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    52,    -1,    -1,    -1,    -1,    -1,    -1,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      -1,   371,    -1,    74,    -1,    -1,  2265,    -1,    -1,    -1,
     380,   381,    -1,    -1,    -1,    86,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   397,   153,   154,
     400,   401,    -1,    -1,    -1,   405,    -1,   108,    -1,    -1,
      -1,    -1,    -1,    -1,   115,   116,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   423,    -1,   180,   181,    -1,    -1,    -1,
      -1,   431,   187,    -1,   434,    -1,   191,    -1,    -1,    -1,
     440,   441,   442,    -1,    -1,   146,   446,    -1,   448,    -1,
     450,   451,   452,    -1,    -1,   210,    -1,   158,    -1,    -1,
      -1,   162,    -1,   218,    -1,    -1,   221,   222,    -1,    -1,
      -1,   226,    -1,    -1,   175,   230,    -1,   232,    -1,    -1,
     235,   182,   237,    -1,   185,   186,     6,    -1,    -1,     9,
      -1,    -1,   193,    -1,    -1,   250,    -1,    -1,    -1,   200,
     255,   202,    -1,    -1,   205,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   267,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   240,
      -1,    -1,    -1,   244,    -1,   246,    -1,    -1,    -1,    -1,
      -1,    -1,   253,   308,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    -1,     6,    -1,    -1,     9,    -1,
      -1,    -1,    -1,    -1,   275,    -1,    96,    -1,    -1,    -1,
     335,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   290,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,
     311,    -1,    -1,    -1,    -1,    -1,   371,    -1,    -1,   320,
      -1,    -1,    -1,    -1,    -1,   380,   381,    -1,    -1,    -1,
      -1,    -1,   333,   153,    -1,    -1,    -1,   338,    -1,   340,
      81,    -1,    -1,    -1,    85,   400,    -1,   348,    -1,    -1,
     405,    -1,    -1,    -1,    -1,    96,    -1,   358,    -1,    -1,
     180,    -1,    -1,    -1,    -1,    -1,   367,    -1,   423,    -1,
      -1,   191,    -1,    -1,    -1,   376,   431,   378,   379,   434,
      -1,   382,    -1,   384,    -1,   440,   441,   442,   389,    -1,
      -1,   446,    -1,   448,    -1,   450,   451,   452,    -1,    -1,
      -1,   221,    -1,   404,    -1,    -1,   226,     3,   409,     5,
     230,    -1,   232,   414,    10,   235,    -1,   237,    -1,    -1,
      -1,    -1,    18,    -1,   425,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   437,    -1,    -1,   180,
      -1,    -1,    -1,    -1,    -1,    -1,   447,   267,    -1,    -1,
     191,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    74,    -1,
     221,    -1,    -1,    -1,    -1,   226,    -1,    -1,   308,   230,
      86,   232,    -1,    -1,   235,    -1,   237,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   108,    -1,    -1,   335,    -1,    -1,    -1,   115,
     116,    -1,    -1,    -1,    -1,    -1,   267,    -1,    -1,    -1,
      -1,   272,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     6,    -1,    -1,     9,
     146,   371,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     380,   381,   158,    -1,    -1,    -1,   162,   308,    -1,    -1,
      30,    -1,    -1,    -1,    -1,    -1,    -1,   318,    -1,   175,
     400,    -1,    -1,    -1,    -1,   405,   182,    -1,    -1,   185,
     186,    -1,    -1,    -1,   335,    -1,    -1,   193,    -1,    -1,
      -1,    -1,    -1,   423,   200,    65,   202,    -1,    -1,   205,
      -1,   431,    -1,     6,   434,    -1,     9,    -1,    -1,    -1,
     440,    81,    -1,    -1,   365,    -1,    -1,    -1,   448,    -1,
     371,    -1,    -1,    -1,    -1,     6,    96,    -1,     9,   380,
     381,    -1,    -1,    -1,   240,    -1,    -1,    -1,   244,    -1,
     246,    -1,    -1,    -1,    -1,    -1,    -1,   253,    -1,   400,
      -1,    -1,    -1,    -1,   405,    -1,    -1,    -1,    -1,   410,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   275,
      -1,    -1,   423,    -1,    -1,    -1,   427,    -1,    81,    -1,
     431,    -1,    -1,   434,   290,    -1,    -1,    -1,    -1,   440,
      -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    -1,    -1,    -1,    -1,   311,    -1,    -1,    -1,    -1,
     180,    -1,    -1,    -1,   320,    96,    -1,    -1,    -1,     6,
      -1,   191,     9,    -1,    -1,    -1,    -1,   333,   109,    -1,
      -1,    -1,   338,    -1,   340,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   348,   146,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   221,   358,    -1,    -1,    -1,   226,   227,    -1,    -1,
     230,   367,   232,    -1,    -1,   235,    -1,   237,    -1,    -1,
     376,    -1,   378,   379,    -1,    -1,   382,   180,   384,    -1,
      -1,    -1,    -1,   389,    -1,    -1,     6,    -1,   191,     9,
      -1,    -1,    -1,    -1,    81,    -1,    -1,   267,   404,   180,
      -1,    -1,    -1,   409,    -1,    92,    -1,    -1,   414,    96,
     191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   221,   425,
      -1,    -1,    -1,   226,   294,   206,    -1,   230,    -1,   232,
      -1,   437,   235,    -1,   237,    -1,    -1,    -1,   308,    -1,
     221,    -1,    -1,    -1,    -1,   226,    -1,    -1,    -1,   230,
      -1,   232,    -1,    -1,   235,    -1,   237,    -1,    -1,    -1,
      -1,    81,    -1,    -1,   267,   335,     6,    -1,    -1,     9,
      -1,    -1,    92,    -1,    -1,    -1,    96,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   267,    -1,    -1,    -1,
      -1,    -1,    -1,   180,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   371,    -1,    -1,   191,   308,    -1,    -1,    -1,    -1,
     380,   381,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   308,    -1,    -1,
     400,    -1,   335,    -1,   221,   405,    -1,    -1,    -1,   226,
      -1,    81,    -1,   230,    -1,   232,    -1,    -1,   235,    -1,
     237,    -1,    -1,   423,   335,     6,    96,    -1,     9,    -1,
     180,   431,    -1,    -1,   434,    -1,    -1,    -1,   371,   109,
     440,   191,    -1,    -1,    -1,    -1,    -1,   380,   381,    -1,
     267,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     371,    -1,    -1,    -1,   397,    -1,    -1,   400,   401,   380,
     381,   221,   405,    -1,    -1,    -1,   226,    -1,    -1,    -1,
     230,    -1,   232,    -1,    -1,   235,    -1,   237,    -1,   400,
     423,   308,    -1,    -1,   405,    -1,    -1,    -1,   431,    -1,
      81,   434,     6,    -1,    -1,     9,    -1,   440,    -1,    -1,
     180,    92,   423,    -1,    -1,    96,    -1,   267,   335,    -1,
     431,   191,    -1,   434,    -1,    -1,    -1,    -1,    -1,   440,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   221,    -1,    -1,   371,    -1,   226,    -1,   308,    -1,
     230,    -1,   232,   380,   381,   235,    -1,   237,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    -1,    -1,   400,    -1,   335,    -1,    -1,   405,    -1,
      -1,    -1,    96,    -1,    -1,    -1,    -1,   267,    -1,   180,
      -1,    -1,    -1,    -1,    -1,    -1,   423,    -1,     6,    -1,
     191,     9,    -1,    -1,   431,    -1,    -1,   434,    -1,    -1,
      -1,   371,    -1,   440,    -1,    -1,    -1,    -1,    -1,    -1,
     380,   381,    -1,    -1,    -1,    -1,    -1,    -1,   308,    -1,
     221,    -1,    -1,    -1,    -1,   226,    -1,    -1,    -1,   230,
     400,   232,    -1,    -1,   235,   405,   237,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   335,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   423,    -1,    -1,   180,    -1,    -1,    -1,
      -1,   431,    -1,    81,   434,    -1,   267,   191,    -1,    -1,
     440,    -1,    -1,    -1,     6,    -1,    -1,     9,    96,    -1,
      -1,   371,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     380,   381,    -1,    -1,    -1,    -1,    -1,   221,    -1,    -1,
      -1,    -1,   226,    -1,    -1,    -1,   230,   308,   232,    -1,
     400,   235,    -1,   237,    -1,   405,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     6,    -1,    -1,     9,    -1,    -1,    -1,
      -1,    -1,    -1,   423,   335,     6,    -1,    -1,     9,    -1,
      -1,   431,    -1,   267,   434,    -1,    -1,    -1,    -1,    81,
     440,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   176,    -1,
      -1,    -1,   180,    -1,    96,    -1,    -1,    -1,    -1,    -1,
     371,    -1,    -1,   191,    -1,    -1,    -1,    -1,    -1,   380,
     381,    -1,    -1,    -1,   308,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,   400,
      -1,    -1,    -1,   221,   405,    -1,    -1,    -1,   226,    -1,
      81,   335,   230,    96,   232,    -1,    -1,   235,    -1,   237,
      -1,    -1,   423,    -1,    -1,    96,    -1,    -1,    -1,    -1,
     431,    -1,    -1,   434,    -1,    -1,    -1,    -1,    -1,   440,
      -1,    -1,    -1,     6,    -1,    -1,     9,   371,   180,   267,
      -1,    -1,    -1,    -1,    -1,    -1,   380,   381,    -1,   191,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   396,    -1,    -1,    -1,   400,    -1,    -1,    -1,
      -1,   405,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   221,
     308,    -1,    -1,    -1,   226,    -1,    -1,   180,   230,   423,
     232,    -1,    -1,   235,    -1,   237,    -1,   431,   191,   180,
     434,    -1,    -1,    -1,    -1,    -1,   440,   335,    81,    -1,
     191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    96,    -1,   267,    -1,    -1,   221,    -1,
      -1,    -1,    -1,   226,    -1,    -1,    -1,   230,    -1,   232,
     221,    -1,   235,   371,   237,   226,    -1,    -1,    -1,   230,
      -1,   232,   380,   381,   235,    -1,   237,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   308,    -1,    -1,    -1,
      -1,    -1,   400,    -1,   267,    -1,    -1,   405,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   267,    -1,    -1,    -1,
      -1,    -1,    -1,   335,    -1,   423,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   431,    -1,    -1,   434,   180,    -1,    -1,
      -1,    -1,   440,    -1,    -1,   308,    -1,    -1,   191,    -1,
      -1,    -1,    -1,   365,    -1,    -1,    -1,   308,    -1,   371,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   380,   381,
      -1,    -1,   335,    -1,    -1,    -1,    -1,    -1,   221,    -1,
      -1,    -1,    -1,   226,   335,    -1,    -1,   230,   400,   232,
      -1,    -1,   235,   405,   237,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   366,    -1,    -1,    -1,    -1,   371,    -1,
      -1,   423,    -1,    -1,    -1,    -1,    -1,   380,   381,   431,
     371,    -1,   434,    -1,   267,    -1,    -1,    -1,   440,   380,
     381,    -1,    -1,    -1,    -1,    -1,    -1,   400,    -1,    -1,
      -1,    -1,   405,    -1,    -1,    -1,    -1,    -1,    -1,   400,
      -1,    -1,    -1,    -1,   405,    -1,    -1,    -1,    -1,    -1,
     423,    -1,    -1,    -1,    -1,   308,    -1,    -1,   431,    -1,
      -1,   434,   423,    -1,    -1,    -1,    -1,   440,    -1,    -1,
     431,    -1,    -1,   434,    -1,    -1,    -1,    21,    -1,   440,
      -1,    -1,   335,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    -1,    -1,    37,    38,    39,    40,    41,    42,    43,
      -1,    37,    38,    39,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   371,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   380,   381,    73,
      -1,    75,    76,    77,    78,    79,    80,    73,    -1,    75,
      76,    77,    78,    79,    80,    -1,    -1,   400,    -1,    -1,
      -1,    -1,   405,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     423,   115,    -1,    -1,    -1,    -1,    -1,    -1,   431,   115,
      -1,   434,    -1,    -1,    -1,    -1,    31,   440,    33,    -1,
      -1,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    -1,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   197,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   197,    -1,    -1,    -1,    -1,   210,    -1,    -1,   213,
     115,    -1,    -1,    -1,    -1,   219,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    65,    66,
     155,   247,    -1,    -1,    -1,    -1,    73,    -1,    75,    76,
      77,    78,    79,    80,    -1,   269,    -1,    -1,   173,    -1,
      -1,   176,   177,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     284,    -1,    -1,    -1,    -1,   190,    -1,   291,   284,   293,
      -1,    -1,   197,    -1,    -1,    -1,    -1,   293,   115,    -1,
      -1,    -1,   306,    -1,    -1,    -1,    -1,    -1,   213,    -1,
     306,    -1,   316,    -1,    -1,    -1,    -1,    -1,    -1,   323,
      -1,    -1,   227,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      -1,   236,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    96,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   360,    -1,   362,   363,
     364,    -1,    -1,    -1,   269,    -1,   362,   363,   364,    -1,
      -1,   188,    -1,    -1,    -1,    -1,    -1,    -1,   283,   284,
     197,    -1,   386,    -1,    -1,    -1,   291,    -1,   293,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   213,    -1,    -1,   403,
      -1,   306,   307,    -1,    -1,    -1,    -1,   411,   412,   413,
     227,   228,    -1,    -1,    -1,   411,   412,   413,    -1,    81,
     424,    -1,    -1,   427,    -1,   180,   331,    -1,    -1,    -1,
     247,   336,    -1,    -1,    96,   252,   191,    -1,    -1,    -1,
      -1,    -1,    -1,   447,    -1,   350,    -1,    -1,    -1,    -1,
      -1,    -1,   269,    -1,    -1,   360,    -1,   362,   363,   364,
      -1,    -1,    -1,    -1,    -1,    -1,   221,   284,    -1,    -1,
      -1,   226,    -1,    -1,   291,   230,   293,   232,    -1,   296,
     235,    -1,   237,    81,    -1,    -1,    -1,    -1,    -1,   306,
      -1,   396,    -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,
      -1,    -1,   407,    -1,    -1,    -1,   411,   412,   413,    -1,
      -1,    -1,   267,    -1,    -1,    -1,    -1,    -1,   180,   424,
      -1,   426,   427,    -1,    -1,    -1,    -1,    -1,    -1,   191,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   447,   360,    -1,   362,   363,   364,    -1,    -1,
      -1,    -1,   369,   308,    -1,    -1,    -1,    -1,    -1,   221,
      -1,    -1,    -1,    -1,   226,    -1,   383,    -1,   230,    -1,
     232,    -1,    -1,   235,    -1,   237,    -1,    -1,    -1,    -1,
     335,    -1,   180,    -1,    -1,    -1,    -1,    -1,    -1,   406,
      -1,    -1,    -1,   191,   411,   412,   413,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   267,    -1,   424,    -1,    -1,
     427,   428,    -1,    -1,    -1,    -1,   371,    -1,    -1,    -1,
      -1,    -1,    -1,   221,    -1,   380,   381,    -1,   226,    -1,
     447,    -1,   230,    -1,   232,    -1,    -1,   235,    -1,   237,
      -1,    -1,    -1,    -1,    -1,   400,   308,    -1,    -1,    -1,
     405,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   423,   267,
      -1,    -1,    -1,   335,    -1,    -1,   431,    -1,    -1,   434,
      -1,    -1,    -1,    -1,    -1,   440,   441,   442,    -1,    -1,
      -1,    -1,    -1,    -1,   449,   450,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   371,
     308,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   380,   381,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   335,   400,    -1,
      -1,    -1,    -1,   405,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   423,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   431,
      -1,    -1,   434,   371,    -1,    -1,    -1,    -1,   440,   441,
     442,    -1,   380,   381,    -1,    -1,    -1,   449,   450,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   400,    -1,    -1,    -1,    -1,   405,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   423,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   431,    -1,    -1,   434,    -1,    -1,    -1,
      -1,    -1,   440,   441,   442,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   450
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   456,   457,     0,   179,   304,   458,   459,   460,   466,
     473,   475,   447,   447,   459,   147,   481,   481,   230,   305,
     476,   476,   117,   461,   467,    27,   477,   477,   447,    99,
     580,   580,   230,   447,   474,    82,   482,   117,   462,   468,
     210,   478,  1124,   349,   166,   204,   212,   533,   447,   300,
     714,   714,   447,    72,   315,   399,   479,   480,   447,   447,
     349,   447,   165,   347,   398,   581,   587,   117,   463,   469,
     473,   132,   472,   480,   303,  1135,   483,   534,   447,   535,
     349,   436,   612,   583,    54,   426,   717,   136,   463,   470,
     481,   476,   268,   330,   370,   372,   484,   485,   489,   497,
     502,   537,   166,   536,    22,   245,   343,   570,   571,   572,
     573,   575,   579,   447,   349,   233,   657,   434,   586,   588,
    1055,   719,   718,   334,   725,   476,   464,   447,   447,   447,
     447,   447,   352,   538,   447,   212,   569,    71,   398,  1120,
     312,   367,   368,   574,   447,   572,   582,   447,   349,   229,
     659,   585,   587,   614,   615,   616,   589,    49,   720,   721,
     722,  1115,   720,   434,   447,   447,   580,   239,   351,   434,
     488,   490,   491,   492,   493,   495,   496,  1135,   178,   498,
     499,   500,   433,   486,   487,   488,  1149,    11,    25,    26,
      57,    94,    95,    97,   105,   148,   149,   159,   231,   345,
     385,   434,   503,   504,   505,   506,   510,   519,   523,   526,
     527,   528,   529,   530,   531,   532,   276,  1101,   537,   447,
     273,  1132,   388,  1143,    24,  1111,   584,   613,   447,   349,
     325,   661,   588,   617,  1095,   590,   721,   365,   410,   723,
     318,   427,   715,   465,   365,  1124,   447,   491,   447,   492,
      62,   356,  1107,     9,   230,   501,   447,   500,   447,   447,
     487,   104,   434,  1066,  1124,  1124,  1066,   377,   360,  1139,
    1124,  1124,  1124,  1124,  1124,  1066,  1124,    56,  1117,  1124,
     447,   505,  1066,   570,   434,  1062,  1063,  1081,    84,  1118,
     172,  1121,   585,   614,   658,   447,   349,   344,   702,   614,
     447,  1095,   434,   618,   620,   625,    47,    61,    99,   215,
     225,   312,   313,   325,   327,   427,   447,   591,   592,   594,
     598,   600,   602,   603,   609,   610,   611,  1124,  1124,   365,
     276,   724,   106,   726,   714,  1124,   230,  1084,   447,   356,
    1124,   207,   207,   230,   447,   243,   511,  1066,  1066,  1124,
    1124,  1124,  1063,    67,  1066,  1066,  1063,  1124,  1063,   520,
     521,  1066,    94,  1066,   539,   196,   270,  1104,  1063,   576,
     577,  1055,  1054,  1055,   614,   660,   447,   349,   618,   447,
     168,   434,   621,   622,  1118,  1124,   312,   314,  1105,  1105,
    1124,  1118,  1124,   243,  1129,  1124,    23,  1110,   270,   164,
     184,    31,   107,  1084,  1124,   434,   447,   716,   469,  1084,
    1063,  1124,   191,   230,   237,   308,   371,   400,   440,   524,
     525,  1087,  1063,   230,  1063,    23,   210,  1066,  1125,   507,
     540,  1081,   577,   294,   578,  1055,   614,   662,   447,   447,
     619,    83,  1084,   434,  1124,  1110,  1062,   272,   373,   599,
     230,  1063,  1065,  1084,   428,  1124,   434,   701,   701,   167,
     434,  1084,   727,   728,   136,   471,    56,   435,   494,   121,
     191,   230,   237,   249,   308,   371,   374,   375,   440,   512,
     513,   514,   517,   525,   393,   522,  1084,   508,     4,    19,
      29,   198,   227,   234,   279,   285,   312,   319,   332,   357,
     359,   367,   398,   447,   541,   542,   546,   548,   553,   554,
     555,   556,   560,   561,   562,   563,   564,   565,   566,   567,
    1107,  1084,   310,   663,   664,   665,   703,   626,   623,  1124,
     396,   597,   228,  1128,   396,  1117,   196,  1123,   434,  1124,
    1124,   728,     1,   434,   729,   730,   731,   732,   733,   738,
     476,   514,    17,   393,  1087,  1084,   271,   273,   509,  1129,
     312,   396,  1147,   357,  1129,  1124,    55,  1116,    37,   110,
     214,  1114,  1126,  1126,  1084,  1149,   377,  1124,   701,   665,
     704,    21,    34,    37,    38,    39,    40,    41,    42,    43,
      73,    75,    76,    77,    78,    79,    80,   115,   197,   213,
     247,   269,   284,   291,   293,   306,   316,   323,   360,   362,
     363,   364,   386,   411,   412,   413,   424,   427,   627,   628,
     629,   631,   632,   633,   634,   635,   636,   645,   646,   648,
     649,   650,   655,   656,  1124,  1140,    27,  1112,   184,  1084,
      56,   314,   593,   604,  1084,   365,  1141,   230,   601,  1081,
     601,   123,   447,   447,   349,     3,     5,    10,    18,    51,
      52,    59,    70,    74,    86,   108,   115,   116,   146,   158,
     162,   175,   182,   185,   186,   193,   200,   202,   205,   240,
     244,   246,   253,   275,   290,   311,   320,   333,   338,   340,
     348,   358,   367,   376,   378,   379,   382,   384,   389,   404,
     409,   414,   425,   437,   447,   739,   740,   750,   755,   759,
     762,   775,   778,   783,   788,   789,   790,   793,   795,   802,
     806,   808,   823,   826,   828,   830,   833,   835,   841,   850,
     852,   869,   871,   874,   878,   884,   894,   901,   903,   906,
     910,   911,   922,   933,   943,   949,   952,   958,   962,   964,
     966,   968,   971,   982,   983,   992,   994,   995,   447,   515,
     517,   377,  1142,  1124,  1126,   120,   164,   544,  1124,   312,
     319,   561,  1124,  1124,   357,  1124,  1124,  1111,     9,   254,
     311,   568,  1124,   434,   666,   620,   625,   705,   706,   707,
     221,   361,   410,   361,   410,   361,   410,   361,   410,   361,
     410,   430,  1148,   339,  1137,  1084,  1080,  1081,  1081,   210,
     220,   339,   647,  1124,  1125,   164,   184,   219,   403,     9,
      50,   221,   624,  1085,  1086,  1087,    30,   605,   606,   607,
     608,  1113,  1149,  1117,   176,   596,  1122,   106,   230,   734,
     741,   751,   756,   760,   763,   776,   779,   784,   791,   794,
     796,   803,   807,   809,   824,   827,   829,  1147,   834,     1,
     836,   842,   851,   853,   870,   872,   875,   879,   885,   895,
     902,   904,   907,   912,   923,   934,   944,   230,   342,   953,
     959,   299,   963,   965,   967,   969,   972,   184,   984,  1121,
     996,   191,   230,   237,   308,   371,   440,   516,   518,  1124,
     120,   309,   357,   547,  1124,   114,   298,   543,    32,   161,
     238,   557,  1065,   374,  1063,  1063,   280,  1134,  1134,   274,
    1063,    60,    87,    88,   286,   447,   667,   668,   672,  1124,
     621,   707,   440,   396,   637,   450,  1082,  1083,   393,   634,
     652,   653,  1085,    27,   630,   355,  1103,  1103,  1087,   270,
    1131,  1131,   454,    48,   402,   171,   597,  1084,   447,   447,
     742,  1079,  1080,     6,    81,    92,    96,   180,   221,   226,
     232,   235,   267,   335,   380,   381,   405,   423,   431,   752,
    1049,  1069,  1070,  1079,  1085,  1088,   434,   757,  1036,  1037,
    1038,   230,  1059,  1060,  1061,  1081,   230,  1077,  1079,  1088,
     777,   780,   785,  1050,  1051,  1070,  1055,   398,   230,   797,
    1069,  1076,  1079,   804,  1070,   230,   397,   401,   810,   811,
    1036,   289,   290,   303,   349,   825,     6,  1067,  1068,  1079,
    1079,   831,   133,  1035,  1036,  1067,   671,  1079,   854,  1079,
    1085,  1088,   935,  1081,    92,   873,  1070,   876,  1070,   880,
     174,   230,   886,   889,   890,   891,  1059,  1077,  1081,  1149,
    1055,  1052,  1081,  1055,  1052,     9,   913,  1053,  1081,   147,
     242,   924,   925,   926,   927,   929,   930,   931,   932,  1056,
    1057,  1067,   935,  1055,   950,   109,   954,   955,  1070,    92,
     960,  1069,   671,  1079,  1055,  1079,     8,    35,   986,   104,
    1052,    17,  1066,  1063,   115,   230,   545,  1081,   433,   558,
     558,   369,   448,   552,  1063,  1064,  1124,   169,   669,   670,
     669,  1125,   680,   184,   708,  1084,   395,  1146,   221,   441,
     442,   450,  1046,  1048,  1049,  1071,  1079,  1086,  1088,   450,
    1083,  1081,   651,   653,   393,   230,  1116,  1080,  1080,  1087,
    1065,  1065,  1113,  1117,   124,   749,    30,   176,   743,  1113,
    1131,   450,  1079,   450,  1089,   450,  1090,  1131,  1104,   450,
     450,   450,   450,   450,   450,   450,   450,  1089,   125,   754,
     396,   753,  1070,   201,  1098,    56,  1039,  1040,   396,  1104,
     426,   764,   230,  1076,  1079,  1055,   127,   786,   153,   448,
     787,  1051,   341,  1102,   312,  1136,  1054,   129,   801,   743,
     419,   420,   421,   422,   130,   805,    49,   206,   764,    17,
     430,   812,   813,   814,   818,  1109,    98,  1131,  1068,  1058,
     392,  1145,   843,  1149,  1079,    91,   324,   387,   855,   856,
     857,   861,   866,   937,  1070,   396,   134,   877,    49,   163,
     203,   211,   281,   881,   890,   135,   887,   415,   428,   393,
     395,   390,   252,   297,  1099,   176,   997,  1136,   997,  1053,
     140,   921,   428,   915,  1074,  1079,  1086,   930,   932,  1067,
     396,  1057,   118,   396,   416,   928,   945,   183,   334,   951,
    1115,   206,   955,  1079,   143,   961,   176,   176,   312,   314,
     970,   109,   973,   326,   373,   987,  1132,   997,   518,   119,
     433,   552,  1097,  1106,   234,   340,  1124,   549,   550,  1076,
     671,   678,  1084,   620,   681,   709,   111,   638,  1131,  1048,
    1048,  1048,    69,   353,   449,  1047,   441,   442,   443,   444,
     446,   453,  1048,  1148,  1085,  1128,  1065,   111,   595,  1074,
      25,    26,    66,    68,   100,   101,   102,   147,   149,   157,
     228,   394,   434,  1057,   433,   746,    65,   227,   294,   744,
     745,   146,   303,  1072,  1080,  1046,  1048,   396,  1048,  1046,
    1091,  1080,  1086,  1088,   434,  1048,  1094,  1048,  1048,  1093,
    1048,  1046,  1046,  1048,  1092,  1048,  1050,  1070,   183,   334,
     758,  1098,    12,    13,    14,    20,    58,   153,   154,   181,
     187,   210,   218,   222,   250,   251,   255,   265,   272,   277,
     295,   440,   441,   442,   443,   444,   446,   448,   449,   451,
     452,  1041,  1042,  1043,  1044,  1045,   210,   250,   255,   441,
     442,   446,   450,  1041,  1042,  1043,  1044,  1045,  1070,   302,
     761,  1061,   765,   183,   334,   769,   317,   408,   781,   782,
    1149,  1036,   209,   259,  1028,  1029,  1030,  1032,   418,   433,
     798,  1149,   160,  1003,  1004,  1003,  1003,  1003,  1070,  1050,
    1070,    21,   397,   401,   819,   820,  1037,   131,   822,   432,
     814,   816,   430,   815,   811,  1080,   111,   832,  1059,   837,
       9,    12,    15,    16,   247,   248,   265,   266,   844,   848,
     168,  1074,     9,    56,   170,   219,   403,   862,   863,   864,
     858,   856,   939,  1106,  1132,   396,  1067,  1050,  1070,   359,
     882,   735,   736,  1035,   892,   893,  1079,  1059,     8,    35,
     999,  1136,  1076,   206,   896,   908,  1149,   916,  1113,  1079,
     916,   396,   396,   509,   146,   397,   401,  1070,    49,   214,
     946,  1070,  1070,   365,  1070,  1079,   176,  1050,  1070,  1074,
    1115,   206,   976,  1079,   156,   160,   988,     9,   993,  1059,
     908,   119,   549,   273,   551,  1063,   551,   189,   673,   227,
     228,   679,   434,   621,    31,    33,    36,    44,    45,    46,
      65,   155,   173,   176,   177,   190,   227,   236,   269,   283,
     307,   331,   336,   350,   396,   407,   426,   447,   632,   633,
     635,   645,   648,   650,   710,   713,  1132,   639,   640,  1080,
    1086,  1088,   449,  1048,  1048,  1048,  1048,  1048,  1048,   449,
    1048,   358,  1138,  1128,  1132,  1002,  1004,   439,   438,  1074,
    1002,   214,    31,    33,    36,    46,   173,   177,   190,   236,
     283,   307,   331,   336,   346,   350,   407,   417,   747,   748,
    1002,   263,  1130,  1130,  1130,   745,   744,   230,  1073,  1080,
     449,  1079,   453,   449,  1047,   449,   449,  1047,   449,   449,
     449,   449,  1047,   449,   449,   366,  1008,  1009,  1050,  1068,
     334,  1147,   391,  1144,  1144,   396,  1059,   766,   767,   768,
    1115,  1079,  1079,   160,   282,   770,   989,  1121,   234,   254,
    1008,  1031,  1033,   128,   792,  1032,    94,   298,   434,  1057,
      33,    36,    44,    45,    46,   155,   173,   190,   236,   283,
     336,   346,   407,   799,   800,  1003,   262,  1005,   258,  1006,
     183,  1008,   183,  1109,   393,   821,   817,   819,   735,  1132,
     735,  1147,   324,   845,  1147,   396,    49,   863,   865,  1074,
       9,    56,   219,   403,   859,   860,  1074,   940,  1107,   196,
     278,  1133,    28,   112,   641,  1067,  1008,   183,  1149,  1054,
     135,   888,   737,     8,   176,   896,  1079,   123,   256,  1018,
    1019,  1021,  1028,   234,   254,   430,   123,   430,   918,   919,
    1074,  1073,  1070,  1124,  1028,   956,  1149,  1079,  1008,   183,
     396,     9,   974,   975,  1096,   977,  1079,   956,   977,   300,
     991,   301,   998,   999,  1097,   245,   312,   314,   559,  1124,
     170,   674,  1084,   682,  1124,  1130,   150,   152,  1124,  1077,
    1130,  1084,  1079,  1079,  1063,   198,   642,   641,   449,  1147,
    1063,  1006,  1002,  1124,  1124,   118,   416,   748,  1076,  1076,
    1076,  1089,  1102,   449,  1048,  1063,  1089,  1089,  1048,  1089,
    1089,  1089,   219,   403,  1089,  1089,  1010,   261,  1011,  1008,
    1068,   153,   277,   153,   277,   767,   272,   723,    85,   318,
     427,   258,   260,   772,   990,   771,   322,   337,   735,   735,
     798,   798,   798,   798,  1124,   150,   152,  1124,   118,   416,
     800,   735,  1007,  1050,  1051,  1050,  1051,   820,  1036,   735,
    1079,   122,   838,   427,   846,   847,   848,   107,   849,   427,
    1075,  1079,  1085,  1074,    49,   867,   860,   172,   867,   936,
    1124,   278,  1126,  1050,   568,   883,  1149,   738,   893,  1070,
     195,   897,  1149,  1020,  1022,   138,   905,  1021,   139,   909,
     234,  1036,   917,  1035,   918,   255,   947,  1100,   141,   948,
     282,  1013,  1014,   293,  1102,  1050,  1075,   277,  1074,   110,
     978,   387,   980,  1132,   151,   257,  1000,  1023,  1024,  1026,
    1029,     7,  1108,   559,  1084,   113,   216,   675,    66,    65,
      66,   188,   227,   228,   252,   296,   369,   383,   406,   428,
     447,   632,   633,   635,   636,   645,   648,   650,   683,   684,
     686,   687,   688,   689,   691,   692,   693,   694,   698,   699,
     440,  1078,  1079,  1084,  1124,  1078,  1124,  1146,  1115,  1126,
     397,   654,  1078,  1078,  1034,  1115,  1034,  1008,   449,   735,
    1012,  1147,   153,  1147,   153,  1070,   126,   774,   773,   735,
    1003,  1003,  1003,  1003,  1078,  1078,  1034,  1034,   735,  1008,
     321,  1008,   321,   839,   133,   840,   847,    99,  1119,   867,
     867,  1075,   999,   203,   426,   941,  1063,   938,  1008,   234,
     254,    49,   234,   214,   898,   194,   234,   254,   429,   735,
     735,   914,   735,   920,   671,  1041,  1042,  1043,  1044,  1045,
    1015,   142,   957,   260,  1016,  1079,  1008,  1008,   975,  1123,
      93,   979,  1123,  1013,   163,   203,   211,   281,   985,  1054,
    1025,  1027,   145,  1001,  1026,   286,  1057,  1078,  1124,    90,
     217,   676,   264,  1130,   199,   700,   263,   264,   697,  1110,
     188,   430,  1124,  1131,  1124,  1079,   689,   252,   292,   695,
     696,  1084,   241,   292,   441,   442,   712,   241,   292,   441,
     442,   711,   434,   643,   644,  1124,  1124,  1078,   735,  1147,
    1147,   735,  1051,  1051,   735,    49,   867,   399,   868,   300,
    1054,   183,   281,   942,  1081,   337,  1070,  1124,   899,  1018,
    1029,   234,   234,   735,   735,   735,  1017,  1079,  1123,  1079,
     144,   981,   735,   735,   227,   228,  1127,  1084,  1124,  1124,
     171,   677,  1124,  1125,  1124,  1035,  1079,   690,  1063,    89,
      90,   113,   287,   288,   328,   329,   685,   176,   286,  1084,
     696,  1078,  1078,   644,  1062,  1085,  1127,  1008,  1008,  1070,
    1070,  1124,  1054,   300,   415,   671,   137,   900,   735,  1079,
    1084,  1084,  1124,  1084,  1084,  1102,  1070,   889,  1124,  1035,
    1084,    49,   889,  1070
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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

/* Prevent warnings from -Wmissing-prototypes.  */
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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

/* Line 1455 of yacc.c  */
#line 761 "parser.y"
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
  ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 785 "parser.y"
    {
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
  ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 814 "parser.y"
    { cb_validate_program_environment (current_program); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 815 "parser.y"
    { cb_validate_program_data (current_program); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 823 "parser.y"
    { cb_validate_program_environment (current_program); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 824 "parser.y"
    { cb_validate_program_data (current_program); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 832 "parser.y"
    { cb_validate_program_environment (current_program); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 833 "parser.y"
    { cb_validate_program_data (current_program); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 845 "parser.y"
    {
	char			*s;

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
  ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 871 "parser.y"
    {
	char			*s;

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
  ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 895 "parser.y"
    {
	char			*s;

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
  ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 924 "parser.y"
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
  ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 965 "parser.y"
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
  ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 1013 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 1014 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 1023 "parser.y"
    {
	if (!current_program->nested_level) {
		cb_error (_("COMMON may only be used in a nested program"));
	}
	current_program->flag_common = 1;
  ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 1030 "parser.y"
    {
	if (!current_program->nested_level) {
		cb_error (_("COMMON may only be used in a nested program"));
	}
	current_program->flag_common = 1;
  ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 1041 "parser.y"
    {
	current_program->flag_initial = 1;
  ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 1045 "parser.y"
    {
	current_program->flag_recursive = 1;
	current_program->flag_initial = 1;
  ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 1070 "parser.y"
    {
	if (current_program->nested_level) {
		cb_error (_("CONFIGURATION SECTION not allowed in nested programs"));
	}
  ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 1105 "parser.y"
    {
	cb_verify (cb_debugging_line, "DEBUGGING MODE");
  ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 1111 "parser.y"
    { ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 1142 "parser.y"
    {
	cb_verify (cb_memory_size_clause, "MEMORY SIZE");
  ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 1154 "parser.y"
    {
	current_program->collating_sequence = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1161 "parser.y"
    {
	/* Ignore */
  ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 1186 "parser.y"
    {
	current_program->function_spec_list = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 1190 "parser.y"
    {
	functions_are_all = 1;
  ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1196 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1198 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1238 "parser.y"
    {
	save_tree_1 = lookup_system_name (CB_NAME ((yyvsp[(1) - (3)])));
	if (save_tree_1 == cb_error_node) {
		cb_error_x ((yyvsp[(1) - (3)]), _("Unknown system-name '%s'"), CB_NAME ((yyvsp[(1) - (3)])));
	} else if (CB_SYSTEM_NAME(save_tree_1)->token != CB_DEVICE_CONSOLE) {
		cb_error_x (save_tree_1, _("Invalid CRT clause"));
	}
	/* current_program->flag_screen = 1; */
  ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1248 "parser.y"
    {
	save_tree_1 = lookup_system_name (CB_NAME ((yyvsp[(1) - (3)])));
	if (save_tree_1 == cb_error_node) {
		cb_error_x ((yyvsp[(1) - (3)]), _("Unknown system-name '%s'"), CB_NAME ((yyvsp[(1) - (3)])));
	} else {
		cb_define ((yyvsp[(3) - (3)]), save_tree_1);
	}
	save_tree_2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 1259 "parser.y"
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
  ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 1273 "parser.y"
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
  ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 1287 "parser.y"
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
  ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 1301 "parser.y"
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
  ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 1319 "parser.y"
    {
	cb_define_switch_name ((yyvsp[(5) - (5)]), save_tree_1, (yyvsp[(2) - (5)]), save_tree_2);
  ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 1325 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1326 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1334 "parser.y"
    {
	save_tree_1 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 1338 "parser.y"
    {
	current_program->alphabet_name_list =
		cb_list_add (current_program->alphabet_name_list, (yyvsp[(5) - (5)]));
  ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 1345 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_NATIVE); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1346 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_1); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1347 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_2); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1348 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_EBCDIC); ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1350 "parser.y"
    {
	(yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_CUSTOM);
	CB_ALPHABET_NAME ((yyval))->custom_list = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1357 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1359 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1363 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1364 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1366 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (2)]));
	save_tree_2 = (yyval);
  ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1371 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (4)]);
  ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1382 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1383 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1384 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1385 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1386 "parser.y"
    { (yyval) = cb_norm_high; ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1387 "parser.y"
    { (yyval) = cb_norm_low; ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1391 "parser.y"
    { cb_list_add (save_tree_2, (yyvsp[(1) - (1)])); ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1392 "parser.y"
    { cb_list_add (save_tree_2, cb_space); ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1393 "parser.y"
    { cb_list_add (save_tree_2, cb_zero); ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1394 "parser.y"
    { cb_list_add (save_tree_2, cb_quote); ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1395 "parser.y"
    { cb_list_add (save_tree_2, cb_norm_high); ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1396 "parser.y"
    { cb_list_add (save_tree_2, cb_norm_low); ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1404 "parser.y"
    {
	if ((yyvsp[(3) - (3)])) {
		current_program->symbolic_list =
			cb_list_add (current_program->symbolic_list, (yyvsp[(3) - (3)]));
	}
	PENDING ("SYMBOLIC CHARACTERS");
  ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1415 "parser.y"
    {
	if (cb_list_length ((yyvsp[(1) - (3)])) != cb_list_length ((yyvsp[(3) - (3)]))) {
		cb_error (_("Invalid SYMBOLIC clause"));
		(yyval) = NULL;
	} else {
		(yyval) = NULL;
	}
  ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1426 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1427 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1431 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1432 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1440 "parser.y"
    {
	current_program->class_name_list =
			cb_list_add (current_program->class_name_list,
			cb_build_class_name ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])));
  ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1448 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1449 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1453 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1455 "parser.y"
    {
	/* if (CB_LITERAL ($1)->data[0] < CB_LITERAL ($3)->data[0]) */
	if (literal_value ((yyvsp[(1) - (3)])) < literal_value ((yyvsp[(3) - (3)]))) {
		(yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	} else {
		(yyval) = cb_build_pair ((yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]));
	}
  ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1469 "parser.y"
    {
	cb_tree	l;

	l = cb_build_locale_name ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
	if (l != cb_error_node) {
		current_program->locale_list =
			cb_list_add (current_program->locale_list, l);
	}
  ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1484 "parser.y"
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
  ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1551 "parser.y"
    {
	current_program->decimal_point = ',';
	current_program->numeric_separator = '.';
  ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1561 "parser.y"
    { current_program->cursor_pos = (yyvsp[(3) - (3)]); ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1568 "parser.y"
    { current_program->crt_status = (yyvsp[(4) - (4)]); ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1575 "parser.y"
    {  PENDING ("SCREEN CONTROL"); ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1581 "parser.y"
    {  PENDING ("EVENT STATUS"); ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1593 "parser.y"
    {
	/* hack for MF compatibility */
	if (cb_relaxed_syntax_check) {
		cb_warning (_("INPUT-OUTPUT SECTION header missing - assumed"));
	} else {
		cb_error (_("INPUT-OUTPUT SECTION header missing"));
	}
  ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1602 "parser.y"
    {
	/* hack for MF compatibility */
	if (cb_relaxed_syntax_check) {
		cb_warning (_("INPUT-OUTPUT SECTION header missing - assumed"));
	} else {
		cb_error (_("INPUT-OUTPUT SECTION header missing"));
	}
  ;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1627 "parser.y"
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
  ;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 1642 "parser.y"
    {
	validate_file (current_file, (yyvsp[(3) - (6)]));
  ;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 1672 "parser.y"
    {
	current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
  ;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 1676 "parser.y"
    {
	current_file->fileid_assign = 1;
	current_file->assign = cb_build_assignment_name (current_file, cb_build_reference ("DISK"));
  ;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1681 "parser.y"
    {
	current_file->fileid_assign = 1;
	current_file->assign = cb_build_assignment_name (current_file, cb_build_reference ("PRINTER"));
  ;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1689 "parser.y"
    { current_file->organization = COB_ORG_LINE_SEQUENTIAL; ;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1694 "parser.y"
    {
	current_file->external_assign = 1;
  ;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1698 "parser.y"
    {
	current_file->external_assign = 0;
  ;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1706 "parser.y"
    {
	const char	*s;

	s = "$#@DUMMY@#$";
	(yyval) = cb_build_alphanumeric_literal ((unsigned char *)s, strlen (s));
  ;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1723 "parser.y"
    { current_file->access_mode = COB_ACCESS_SEQUENTIAL; ;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1724 "parser.y"
    { current_file->access_mode = COB_ACCESS_DYNAMIC; ;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1725 "parser.y"
    { current_file->access_mode = COB_ACCESS_RANDOM; ;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1733 "parser.y"
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
  ;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1753 "parser.y"
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
  ;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1799 "parser.y"
    {
	key_component_list = NULL;
  ;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1808 "parser.y"
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
  ;}
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 1823 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 1824 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 1825 "parser.y"
    { (yyval) = cb_int('='); ;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 1832 "parser.y"
    {
	PENDING ("COLLATING SEQUENCE");
  ;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1842 "parser.y"
    {
	current_file->file_status = (yyvsp[(4) - (5)]);
	if ((yyvsp[(5) - (5)])) {
		PENDING ("2nd FILE STATUS");
	}
  ;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1863 "parser.y"
    { current_file->lock_mode = COB_LOCK_MANUAL; ;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1864 "parser.y"
    { current_file->lock_mode = COB_LOCK_AUTOMATIC; ;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1865 "parser.y"
    { current_file->lock_mode = COB_LOCK_EXCLUSIVE; ;}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1871 "parser.y"
    {
	current_file->lock_mode |= COB_LOCK_MULTIPLE;
  ;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1874 "parser.y"
    { PENDING ("WITH ROLLBACK"); ;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1891 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_INDEXED;
		organized_seen = 1;
	}
  ;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 1900 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_SEQUENTIAL;
		organized_seen = 1;
	}
  ;}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 1909 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = cb_default_organization;
		organized_seen = 1;
	}
  ;}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 1918 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_RELATIVE;
		organized_seen = 1;
	}
  ;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1927 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_LINE_SEQUENTIAL;
		organized_seen = 1;
	}
  ;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1942 "parser.y"
    {
	cb_verify (cb_padding_character_clause, "PADDING CHARACTER");
  ;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1951 "parser.y"
    { /* ignored */ ;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1959 "parser.y"
    {
	current_file->key = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 1963 "parser.y"
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
  ;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 2000 "parser.y"
    { current_file->key = (yyvsp[(4) - (4)]); ;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 2007 "parser.y"
    { /* ignored */ ;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 2014 "parser.y"
    { current_file->sharing = (yyvsp[(3) - (3)]); ;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 2018 "parser.y"
    { (yyval) = NULL; PENDING ("SHARING ALL OTHER"); ;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 2019 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 2020 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 2051 "parser.y"
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
  ;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 2075 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 2076 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 2077 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 2078 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 2085 "parser.y"
    {
	cb_verify (cb_multiple_file_tape_clause, "MULTIPLE FILE TAPE");
  ;}
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 2096 "parser.y"
    { ;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 2107 "parser.y"
    {
	PENDING ("APPLY COMMITMENT-CONTROL");
  ;}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 2132 "parser.y"
    { current_storage = CB_STORAGE_FILE; ;}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 2135 "parser.y"
    {
	/* hack for MF compatibility */
	if (cb_relaxed_syntax_check) {
		cb_warning (_("FILE SECTION header missing - assumed"));
	} else {
		cb_error (_("FILE SECTION header missing"));
	}
	current_storage = CB_STORAGE_FILE;
  ;}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 2154 "parser.y"
    {
	if ((yyvsp[(3) - (3)]) && (yyvsp[(3) - (3)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(3) - (3)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 2166 "parser.y"
    {
	if ((yyvsp[(2) - (2)]) && (yyvsp[(2) - (2)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(2) - (2)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 2177 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 2178 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 2188 "parser.y"
    {
	if ((yyvsp[(1) - (1)]) == cb_error_node) {
		YYERROR;
	}

	current_file = CB_FILE (cb_ref ((yyvsp[(1) - (1)])));
	if ((yyvsp[(0) - (1)]) == cb_int1) {
		current_file->organization = COB_ORG_SORT;
	}
  ;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 2199 "parser.y"
    {
	/* Shut up bison */
	dummy_tree = (yyvsp[(2) - (4)]);
  ;}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 2211 "parser.y"
    {
	if (current_file->global) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->external = 1;
  ;}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 2218 "parser.y"
    {
	if (current_file->external) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->global = 1;
  ;}
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 2240 "parser.y"
    { /* ignored */ ;}
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 2250 "parser.y"
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
  ;}
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 2262 "parser.y"
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
  ;}
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 2288 "parser.y"
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
  ;}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 2312 "parser.y"
    {
	current_file->record_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 2318 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 2319 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 2323 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 2324 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 2332 "parser.y"
    {
	cb_verify (cb_label_records_clause, "LABEL RECORDS");
  ;}
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 2347 "parser.y"
    {
	cb_verify (cb_value_of_clause, "VALUE OF");
  ;}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 2351 "parser.y"
    {
	if (!current_file->assign) {
		current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 2367 "parser.y"
    {
	cb_verify (cb_data_records_clause, "DATA RECORDS");
  ;}
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 2378 "parser.y"
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
  ;}
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 2406 "parser.y"
    {
	current_file->latfoot = (yyvsp[(4) - (5)]);
  ;}
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 2413 "parser.y"
    {
	current_file->lattop = (yyvsp[(3) - (4)]);
  ;}
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 2420 "parser.y"
    {
	current_file->latbot = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 2429 "parser.y"
    { /* ignore */ ;}
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 2437 "parser.y"
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
  ;}
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 2455 "parser.y"
    {
	cb_warning (_("file descriptor REPORT IS"));
  ;}
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 2459 "parser.y"
    {
	cb_warning (_("file descriptor REPORTS ARE"));
  ;}
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 2470 "parser.y"
    { current_storage = CB_STORAGE_WORKING; ;}
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 2472 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->working_storage =
			cb_field_add (current_program->working_storage, CB_FIELD ((yyvsp[(5) - (5)])));
	}
  ;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 2481 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 2482 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 324:

/* Line 1455 of yacc.c  */
#line 2486 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 325:

/* Line 1455 of yacc.c  */
#line 2492 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	(yyval) = CB_TREE (description_field);
  ;}
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 2512 "parser.y"
    {
	cb_tree x;

	x = cb_build_field_tree ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), current_field, current_storage, current_file);
	if (x == cb_error_node) {
		YYERROR;
	} else {
		current_field = CB_FIELD (x);
	}
  ;}
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 2523 "parser.y"
    {
	if (!qualifier && (current_field->level == 88 ||
		current_field->level == 66 || current_field->flag_item_78)) {
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
  ;}
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 2547 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 334:

/* Line 1455 of yacc.c  */
#line 2553 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 335:

/* Line 1455 of yacc.c  */
#line 2559 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 2568 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 2577 "parser.y"
    {
	current_field->flag_is_global = 1;
	cb_error (_("CONSTANT with GLOBAL clause is not yet supported"));
  ;}
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 2584 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 340:

/* Line 1455 of yacc.c  */
#line 2585 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 341:

/* Line 1455 of yacc.c  */
#line 2586 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 342:

/* Line 1455 of yacc.c  */
#line 2591 "parser.y"
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
  ;}
    break;

  case 343:

/* Line 1455 of yacc.c  */
#line 2610 "parser.y"
    {
	/* required to check redefines */
	(yyval) = NULL;
  ;}
    break;

  case 344:

/* Line 1455 of yacc.c  */
#line 2616 "parser.y"
    {
	/* required to check redefines */
	(yyval) = cb_true;
  ;}
    break;

  case 359:

/* Line 1455 of yacc.c  */
#line 2644 "parser.y"
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
  ;}
    break;

  case 360:

/* Line 1455 of yacc.c  */
#line 2666 "parser.y"
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
  ;}
    break;

  case 361:

/* Line 1455 of yacc.c  */
#line 2687 "parser.y"
    { current_field->ename = NULL; ;}
    break;

  case 362:

/* Line 1455 of yacc.c  */
#line 2689 "parser.y"
    {
	struct cb_field *x;

	x = CB_FIELD(cb_build_field (cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(2) - (2)]))->data))));
	current_field->ename = x->name;
 ;}
    break;

  case 363:

/* Line 1455 of yacc.c  */
#line 2701 "parser.y"
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
  ;}
    break;

  case 364:

/* Line 1455 of yacc.c  */
#line 2720 "parser.y"
    { current_field->pic = CB_PICTURE ((yyvsp[(1) - (1)])); ;}
    break;

  case 367:

/* Line 1455 of yacc.c  */
#line 2732 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 368:

/* Line 1455 of yacc.c  */
#line 2733 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 369:

/* Line 1455 of yacc.c  */
#line 2734 "parser.y"
    { current_field->usage = CB_USAGE_FLOAT; ;}
    break;

  case 370:

/* Line 1455 of yacc.c  */
#line 2735 "parser.y"
    { current_field->usage = CB_USAGE_DOUBLE; ;}
    break;

  case 371:

/* Line 1455 of yacc.c  */
#line 2736 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 372:

/* Line 1455 of yacc.c  */
#line 2737 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 373:

/* Line 1455 of yacc.c  */
#line 2738 "parser.y"
    { current_field->usage = CB_USAGE_COMP_5; ;}
    break;

  case 374:

/* Line 1455 of yacc.c  */
#line 2739 "parser.y"
    { current_field->usage = CB_USAGE_COMP_X; ;}
    break;

  case 375:

/* Line 1455 of yacc.c  */
#line 2740 "parser.y"
    { current_field->usage = CB_USAGE_DISPLAY; ;}
    break;

  case 376:

/* Line 1455 of yacc.c  */
#line 2741 "parser.y"
    { current_field->usage = CB_USAGE_INDEX; ;}
    break;

  case 377:

/* Line 1455 of yacc.c  */
#line 2742 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 378:

/* Line 1455 of yacc.c  */
#line 2744 "parser.y"
    {
	current_field->usage = CB_USAGE_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 379:

/* Line 1455 of yacc.c  */
#line 2749 "parser.y"
    {
	current_field->usage = CB_USAGE_PROGRAM_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 380:

/* Line 1455 of yacc.c  */
#line 2753 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 381:

/* Line 1455 of yacc.c  */
#line 2754 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 382:

/* Line 1455 of yacc.c  */
#line 2755 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 383:

/* Line 1455 of yacc.c  */
#line 2756 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 384:

/* Line 1455 of yacc.c  */
#line 2757 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 385:

/* Line 1455 of yacc.c  */
#line 2758 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 386:

/* Line 1455 of yacc.c  */
#line 2759 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 387:

/* Line 1455 of yacc.c  */
#line 2760 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_CHAR; ;}
    break;

  case 388:

/* Line 1455 of yacc.c  */
#line 2761 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 389:

/* Line 1455 of yacc.c  */
#line 2762 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 390:

/* Line 1455 of yacc.c  */
#line 2763 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 391:

/* Line 1455 of yacc.c  */
#line 2764 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 392:

/* Line 1455 of yacc.c  */
#line 2765 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 393:

/* Line 1455 of yacc.c  */
#line 2766 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 394:

/* Line 1455 of yacc.c  */
#line 2767 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 395:

/* Line 1455 of yacc.c  */
#line 2768 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 396:

/* Line 1455 of yacc.c  */
#line 2769 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 397:

/* Line 1455 of yacc.c  */
#line 2770 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 398:

/* Line 1455 of yacc.c  */
#line 2772 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  ;}
    break;

  case 399:

/* Line 1455 of yacc.c  */
#line 2780 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_UNSIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_UNSIGNED_LONG;
	}
  ;}
    break;

  case 400:

/* Line 1455 of yacc.c  */
#line 2788 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  ;}
    break;

  case 401:

/* Line 1455 of yacc.c  */
#line 2795 "parser.y"
    { PENDING ("USAGE NATIONAL");;}
    break;

  case 402:

/* Line 1455 of yacc.c  */
#line 2803 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 1;
  ;}
    break;

  case 403:

/* Line 1455 of yacc.c  */
#line 2808 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 0;
  ;}
    break;

  case 404:

/* Line 1455 of yacc.c  */
#line 2820 "parser.y"
    {
	if (current_field->occurs_depending && !((yyvsp[(3) - (7)]))) {
		cb_verify (cb_odo_without_to, "ODO without TO clause");
	}
	current_field->occurs_min = (yyvsp[(3) - (7)]) ? cb_get_int ((yyvsp[(2) - (7)])) : 1;
	current_field->occurs_max = (yyvsp[(3) - (7)]) ? cb_get_int ((yyvsp[(3) - (7)])) : cb_get_int ((yyvsp[(2) - (7)]));
	current_field->indexes++;
	if (current_field->indexes > COB_MAX_SUBSCRIPTS) {
		cb_error (_("Maximum OCCURS depth exceeded"));
	}
	current_field->flag_occurs = 1;
  ;}
    break;

  case 405:

/* Line 1455 of yacc.c  */
#line 2835 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 406:

/* Line 1455 of yacc.c  */
#line 2836 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 408:

/* Line 1455 of yacc.c  */
#line 2841 "parser.y"
    {
	current_field->occurs_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 409:

/* Line 1455 of yacc.c  */
#line 2848 "parser.y"
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
  ;}
    break;

  case 410:

/* Line 1455 of yacc.c  */
#line 2871 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 411:

/* Line 1455 of yacc.c  */
#line 2874 "parser.y"
    {
	cb_tree l;

	for (l = (yyvsp[(5) - (5)]); l; l = CB_CHAIN (l)) {
		CB_PURPOSE (l) = (yyvsp[(2) - (5)]);
		if (qualifier && !CB_REFERENCE(CB_VALUE(l))->chain &&
		    strcasecmp (CB_NAME(CB_VALUE(l)), CB_NAME(qualifier))) {
			CB_REFERENCE(CB_VALUE(l))->chain = qualifier;
		}
	}
	(yyval) = cb_list_append ((yyvsp[(1) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 412:

/* Line 1455 of yacc.c  */
#line 2889 "parser.y"
    { (yyval) = cb_int (COB_ASCENDING); ;}
    break;

  case 413:

/* Line 1455 of yacc.c  */
#line 2890 "parser.y"
    { (yyval) = cb_int (COB_DESCENDING); ;}
    break;

  case 415:

/* Line 1455 of yacc.c  */
#line 2895 "parser.y"
    {
	current_field->index_list = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 416:

/* Line 1455 of yacc.c  */
#line 2901 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 417:

/* Line 1455 of yacc.c  */
#line 2903 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 418:

/* Line 1455 of yacc.c  */
#line 2908 "parser.y"
    {
	(yyval) = cb_build_index ((yyvsp[(1) - (1)]), cb_int1, 1, current_field);
  ;}
    break;

  case 419:

/* Line 1455 of yacc.c  */
#line 2917 "parser.y"
    { current_field->flag_justified = 1; ;}
    break;

  case 420:

/* Line 1455 of yacc.c  */
#line 2924 "parser.y"
    { current_field->flag_synchronized = 1; ;}
    break;

  case 424:

/* Line 1455 of yacc.c  */
#line 2936 "parser.y"
    { current_field->flag_blank_zero = 1; ;}
    break;

  case 425:

/* Line 1455 of yacc.c  */
#line 2944 "parser.y"
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
  ;}
    break;

  case 426:

/* Line 1455 of yacc.c  */
#line 2968 "parser.y"
    { current_field->values = (yyvsp[(3) - (3)]); ;}
    break;

  case 428:

/* Line 1455 of yacc.c  */
#line 2973 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 429:

/* Line 1455 of yacc.c  */
#line 2974 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 430:

/* Line 1455 of yacc.c  */
#line 2978 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 431:

/* Line 1455 of yacc.c  */
#line 2979 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 433:

/* Line 1455 of yacc.c  */
#line 2984 "parser.y"
    {
	if (current_field->level != 88) {
		cb_error (_("FALSE clause only allowed for 88 level"));
	}
	current_field->false_88 = cb_list_init ((yyvsp[(3) - (3)]));
  ;}
    break;

  case 434:

/* Line 1455 of yacc.c  */
#line 2997 "parser.y"
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
  ;}
    break;

  case 435:

/* Line 1455 of yacc.c  */
#line 3009 "parser.y"
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
  ;}
    break;

  case 436:

/* Line 1455 of yacc.c  */
#line 3029 "parser.y"
    {
	if (current_field->flag_item_based) {
		cb_error (_("BASED and ANY LENGTH are mutually exclusive"));
	} else {
		current_field->flag_any_length = 1;
	}
  ;}
    break;

  case 438:

/* Line 1455 of yacc.c  */
#line 3044 "parser.y"
    {
	current_storage = CB_STORAGE_LOCAL;
	if (current_program->nested_level) {
		cb_error (_("LOCAL-STORAGE not allowed in nested programs"));
	}
  ;}
    break;

  case 439:

/* Line 1455 of yacc.c  */
#line 3051 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->local_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 441:

/* Line 1455 of yacc.c  */
#line 3064 "parser.y"
    { current_storage = CB_STORAGE_LINKAGE; ;}
    break;

  case 442:

/* Line 1455 of yacc.c  */
#line 3066 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->linkage_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 444:

/* Line 1455 of yacc.c  */
#line 3079 "parser.y"
    {
	cb_error (_("REPORT SECTION not supported"));
	current_storage = CB_STORAGE_REPORT;
  ;}
    break;

  case 451:

/* Line 1455 of yacc.c  */
#line 3112 "parser.y"
    {
	cb_warning (_("Report description using defaults"));
  ;}
    break;

  case 453:

/* Line 1455 of yacc.c  */
#line 3120 "parser.y"
    {
	cb_error (_("GLOBAL is not allowed with RD"));
  ;}
    break;

  case 462:

/* Line 1455 of yacc.c  */
#line 3143 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 463:

/* Line 1455 of yacc.c  */
#line 3144 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 485:

/* Line 1455 of yacc.c  */
#line 3200 "parser.y"
    { cb_warning (_("looking for Report line TYPE")); ;}
    break;

  case 536:

/* Line 1455 of yacc.c  */
#line 3305 "parser.y"
    { current_storage = CB_STORAGE_SCREEN; ;}
    break;

  case 537:

/* Line 1455 of yacc.c  */
#line 3306 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 538:

/* Line 1455 of yacc.c  */
#line 3312 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	current_program->screen_storage = description_field;
	current_program->flag_screen = 1;
  ;}
    break;

  case 544:

/* Line 1455 of yacc.c  */
#line 3336 "parser.y"
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
  ;}
    break;

  case 545:

/* Line 1455 of yacc.c  */
#line 3352 "parser.y"
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
  ;}
    break;

  case 548:

/* Line 1455 of yacc.c  */
#line 3376 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 549:

/* Line 1455 of yacc.c  */
#line 3377 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 550:

/* Line 1455 of yacc.c  */
#line 3378 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BELL; ;}
    break;

  case 551:

/* Line 1455 of yacc.c  */
#line 3379 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLINK; ;}
    break;

  case 552:

/* Line 1455 of yacc.c  */
#line 3380 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 553:

/* Line 1455 of yacc.c  */
#line 3381 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 554:

/* Line 1455 of yacc.c  */
#line 3382 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 555:

/* Line 1455 of yacc.c  */
#line 3383 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 556:

/* Line 1455 of yacc.c  */
#line 3384 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REVERSE; ;}
    break;

  case 557:

/* Line 1455 of yacc.c  */
#line 3385 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 558:

/* Line 1455 of yacc.c  */
#line 3386 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_OVERLINE; ;}
    break;

  case 559:

/* Line 1455 of yacc.c  */
#line 3387 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_AUTO; ;}
    break;

  case 560:

/* Line 1455 of yacc.c  */
#line 3388 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_SECURE; ;}
    break;

  case 561:

/* Line 1455 of yacc.c  */
#line 3389 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REQUIRED; ;}
    break;

  case 562:

/* Line 1455 of yacc.c  */
#line 3390 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_FULL; ;}
    break;

  case 563:

/* Line 1455 of yacc.c  */
#line 3391 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_PROMPT; ;}
    break;

  case 564:

/* Line 1455 of yacc.c  */
#line 3393 "parser.y"
    {
	current_field->screen_line = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 565:

/* Line 1455 of yacc.c  */
#line 3397 "parser.y"
    {
	current_field->screen_column = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 566:

/* Line 1455 of yacc.c  */
#line 3401 "parser.y"
    {
	current_field->screen_foreg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 567:

/* Line 1455 of yacc.c  */
#line 3405 "parser.y"
    {
	current_field->screen_backg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 575:

/* Line 1455 of yacc.c  */
#line 3416 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 576:

/* Line 1455 of yacc.c  */
#line 3423 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 577:

/* Line 1455 of yacc.c  */
#line 3427 "parser.y"
    {
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 578:

/* Line 1455 of yacc.c  */
#line 3436 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 579:

/* Line 1455 of yacc.c  */
#line 3440 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 580:

/* Line 1455 of yacc.c  */
#line 3444 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 581:

/* Line 1455 of yacc.c  */
#line 3448 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 582:

/* Line 1455 of yacc.c  */
#line 3452 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 583:

/* Line 1455 of yacc.c  */
#line 3459 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 584:

/* Line 1455 of yacc.c  */
#line 3463 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 585:

/* Line 1455 of yacc.c  */
#line 3467 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 586:

/* Line 1455 of yacc.c  */
#line 3471 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 587:

/* Line 1455 of yacc.c  */
#line 3475 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 588:

/* Line 1455 of yacc.c  */
#line 3483 "parser.y"
    {
	current_field->occurs_max = cb_get_int ((yyvsp[(2) - (3)]));
	current_field->occurs_min = current_field->occurs_max;
	current_field->indexes++;
	current_field->flag_occurs = 1;
  ;}
    break;

  case 590:

/* Line 1455 of yacc.c  */
#line 3497 "parser.y"
    {
	current_section = NULL;
	current_paragraph = NULL;
	cb_define_system_name ("CONSOLE");
	cb_define_system_name ("SYSIN");
	cb_define_system_name ("SYSOUT");
	cb_define_system_name ("SYSERR");
	cb_set_in_procedure ();
  ;}
    break;

  case 591:

/* Line 1455 of yacc.c  */
#line 3507 "parser.y"
    {
	if (current_program->flag_main && !current_program->flag_chained && (yyvsp[(3) - (7)])) {
		cb_error (_("Executable program requested but PROCEDURE/ENTRY has USING clause"));
	}
	emit_entry (current_program->program_id, 0, (yyvsp[(3) - (7)])); /* main entry point */
	if (current_program->source_name) {
		emit_entry (current_program->source_name, 1, (yyvsp[(3) - (7)]));
	}
  ;}
    break;

  case 592:

/* Line 1455 of yacc.c  */
#line 3517 "parser.y"
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
  ;}
    break;

  case 593:

/* Line 1455 of yacc.c  */
#line 3534 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 594:

/* Line 1455 of yacc.c  */
#line 3536 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 595:

/* Line 1455 of yacc.c  */
#line 3540 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 596:

/* Line 1455 of yacc.c  */
#line 3542 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	current_program->flag_chained = 1;
  ;}
    break;

  case 597:

/* Line 1455 of yacc.c  */
#line 3546 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 598:

/* Line 1455 of yacc.c  */
#line 3550 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 599:

/* Line 1455 of yacc.c  */
#line 3552 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 600:

/* Line 1455 of yacc.c  */
#line 3557 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), cb_build_identifier ((yyvsp[(4) - (4)])));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 602:

/* Line 1455 of yacc.c  */
#line 3566 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 603:

/* Line 1455 of yacc.c  */
#line 3570 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 605:

/* Line 1455 of yacc.c  */
#line 3582 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_AUTO;
	}
  ;}
    break;

  case 606:

/* Line 1455 of yacc.c  */
#line 3590 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_4;
	}
  ;}
    break;

  case 607:

/* Line 1455 of yacc.c  */
#line 3598 "parser.y"
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
  ;}
    break;

  case 608:

/* Line 1455 of yacc.c  */
#line 3627 "parser.y"
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
  ;}
    break;

  case 610:

/* Line 1455 of yacc.c  */
#line 3660 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OPTIONAL only allowed for BY REFERENCE items"));
	}
  ;}
    break;

  case 611:

/* Line 1455 of yacc.c  */
#line 3669 "parser.y"
    {
	if (current_program->prog_type == CB_FUNCTION_TYPE) {
		cb_error (_("RETURNING clause is required for a FUNCTION"));
	}
  ;}
    break;

  case 612:

/* Line 1455 of yacc.c  */
#line 3675 "parser.y"
    {
	if (cb_ref ((yyvsp[(2) - (2)])) != cb_error_node) {
		current_program->returning = (yyvsp[(2) - (2)]);
		if (cb_field ((yyvsp[(2) - (2)]))->storage != CB_STORAGE_LINKAGE) {
			cb_error (_("RETURNING item is not defined in LINKAGE SECTION"));
		}
	}
  ;}
    break;

  case 614:

/* Line 1455 of yacc.c  */
#line 3686 "parser.y"
    { in_declaratives = 1; ;}
    break;

  case 615:

/* Line 1455 of yacc.c  */
#line 3689 "parser.y"
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
  ;}
    break;

  case 621:

/* Line 1455 of yacc.c  */
#line 3722 "parser.y"
    {
	if (next_label_list) {
		cb_tree label;
		char name[16];

		sprintf (name, "L$%d", next_label_id);
		label = cb_build_reference (name);
		emit_statement (cb_build_label (label, NULL));
		current_program->label_list =
			cb_list_append (current_program->label_list, next_label_list);
		next_label_list = NULL;
		next_label_id++;
	}
	/* check_unreached = 0; */
  ;}
    break;

  case 622:

/* Line 1455 of yacc.c  */
#line 3738 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 623:

/* Line 1455 of yacc.c  */
#line 3750 "parser.y"
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
  ;}
    break;

  case 624:

/* Line 1455 of yacc.c  */
#line 3781 "parser.y"
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
  ;}
    break;

  case 625:

/* Line 1455 of yacc.c  */
#line 3818 "parser.y"
    {
	non_const_word = 0;
	check_unreached = 0;
	if ((yyvsp[(1) - (1)]) != cb_error_node) {
		cb_error_x ((yyvsp[(1) - (1)]), _("Unknown statement '%s'"), CB_NAME ((yyvsp[(1) - (1)])));
	}
	YYERROR;
  ;}
    break;

  case 626:

/* Line 1455 of yacc.c  */
#line 3829 "parser.y"
    { (yyval) = cb_build_section_name ((yyvsp[(1) - (1)]), 0); ;}
    break;

  case 628:

/* Line 1455 of yacc.c  */
#line 3833 "parser.y"
    { /* ignore */ ;}
    break;

  case 629:

/* Line 1455 of yacc.c  */
#line 3842 "parser.y"
    {
	(yyval) = current_program->exec_list;
	current_program->exec_list = NULL;
  ;}
    break;

  case 630:

/* Line 1455 of yacc.c  */
#line 3846 "parser.y"
    {
	(yyval) = CB_TREE (current_statement);
	current_statement = NULL;
  ;}
    break;

  case 631:

/* Line 1455 of yacc.c  */
#line 3851 "parser.y"
    {
	(yyval) = cb_list_reverse (current_program->exec_list);
	current_program->exec_list = (yyvsp[(1) - (3)]);
	current_statement = CB_STATEMENT ((yyvsp[(2) - (3)]));
  ;}
    break;

  case 632:

/* Line 1455 of yacc.c  */
#line 3859 "parser.y"
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
  ;}
    break;

  case 683:

/* Line 1455 of yacc.c  */
#line 3931 "parser.y"
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
  ;}
    break;

  case 684:

/* Line 1455 of yacc.c  */
#line 3953 "parser.y"
    {
	BEGIN_STATEMENT ("ACCEPT", TERM_ACCEPT);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 686:

/* Line 1455 of yacc.c  */
#line 3966 "parser.y"
    {
	cb_emit_accept ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 687:

/* Line 1455 of yacc.c  */
#line 3970 "parser.y"
    {
	PENDING ("ACCEPT .. FROM ESCAPE KEY");
  ;}
    break;

  case 688:

/* Line 1455 of yacc.c  */
#line 3974 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 0);
  ;}
    break;

  case 689:

/* Line 1455 of yacc.c  */
#line 3978 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 1);
  ;}
    break;

  case 690:

/* Line 1455 of yacc.c  */
#line 3982 "parser.y"
    {
	cb_emit_accept_date ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 691:

/* Line 1455 of yacc.c  */
#line 3986 "parser.y"
    {
	cb_emit_accept_date_yyyymmdd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 692:

/* Line 1455 of yacc.c  */
#line 3990 "parser.y"
    {
	cb_emit_accept_day ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 693:

/* Line 1455 of yacc.c  */
#line 3994 "parser.y"
    {
	cb_emit_accept_day_yyyyddd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 694:

/* Line 1455 of yacc.c  */
#line 3998 "parser.y"
    {
	cb_emit_accept_day_of_week ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 695:

/* Line 1455 of yacc.c  */
#line 4002 "parser.y"
    {
	cb_emit_accept_time ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 696:

/* Line 1455 of yacc.c  */
#line 4006 "parser.y"
    {
	cb_emit_accept_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 697:

/* Line 1455 of yacc.c  */
#line 4010 "parser.y"
    {
	cb_emit_accept_environment ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 698:

/* Line 1455 of yacc.c  */
#line 4014 "parser.y"
    { 
	cb_emit_get_environment ((yyvsp[(4) - (5)]), (yyvsp[(1) - (5)]));
  ;}
    break;

  case 699:

/* Line 1455 of yacc.c  */
#line 4018 "parser.y"
    {
	cb_emit_accept_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 700:

/* Line 1455 of yacc.c  */
#line 4022 "parser.y"
    {
	cb_emit_accept_arg_value ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 701:

/* Line 1455 of yacc.c  */
#line 4026 "parser.y"
    {
	cb_emit_accept_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 702:

/* Line 1455 of yacc.c  */
#line 4030 "parser.y"
    {
	cb_emit_accept_name ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 703:

/* Line 1455 of yacc.c  */
#line 4036 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 704:

/* Line 1455 of yacc.c  */
#line 4037 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 705:

/* Line 1455 of yacc.c  */
#line 4038 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); ;}
    break;

  case 706:

/* Line 1455 of yacc.c  */
#line 4039 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), NULL); ;}
    break;

  case 707:

/* Line 1455 of yacc.c  */
#line 4040 "parser.y"
    { (yyval) = cb_build_pair (NULL, (yyvsp[(2) - (2)])); ;}
    break;

  case 708:

/* Line 1455 of yacc.c  */
#line 4041 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 709:

/* Line 1455 of yacc.c  */
#line 4045 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 710:

/* Line 1455 of yacc.c  */
#line 4049 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 711:

/* Line 1455 of yacc.c  */
#line 4050 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 716:

/* Line 1455 of yacc.c  */
#line 4063 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 717:

/* Line 1455 of yacc.c  */
#line 4064 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 718:

/* Line 1455 of yacc.c  */
#line 4065 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 719:

/* Line 1455 of yacc.c  */
#line 4066 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 720:

/* Line 1455 of yacc.c  */
#line 4067 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 721:

/* Line 1455 of yacc.c  */
#line 4068 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 722:

/* Line 1455 of yacc.c  */
#line 4069 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 723:

/* Line 1455 of yacc.c  */
#line 4071 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 724:

/* Line 1455 of yacc.c  */
#line 4075 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 725:

/* Line 1455 of yacc.c  */
#line 4079 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 726:

/* Line 1455 of yacc.c  */
#line 4083 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 727:

/* Line 1455 of yacc.c  */
#line 4087 "parser.y"
    { dispattrs |= COB_SCREEN_AUTO; ;}
    break;

  case 728:

/* Line 1455 of yacc.c  */
#line 4088 "parser.y"
    { dispattrs |= COB_SCREEN_FULL; ;}
    break;

  case 729:

/* Line 1455 of yacc.c  */
#line 4089 "parser.y"
    { dispattrs |= COB_SCREEN_REQUIRED; ;}
    break;

  case 730:

/* Line 1455 of yacc.c  */
#line 4090 "parser.y"
    { dispattrs |= COB_SCREEN_SECURE; ;}
    break;

  case 731:

/* Line 1455 of yacc.c  */
#line 4091 "parser.y"
    { dispattrs |= COB_SCREEN_UPDATE; ;}
    break;

  case 732:

/* Line 1455 of yacc.c  */
#line 4092 "parser.y"
    { dispattrs |= COB_SCREEN_PROMPT; ;}
    break;

  case 733:

/* Line 1455 of yacc.c  */
#line 4096 "parser.y"
    { terminator_warning (TERM_ACCEPT); ;}
    break;

  case 734:

/* Line 1455 of yacc.c  */
#line 4097 "parser.y"
    { terminator_clear (TERM_ACCEPT); ;}
    break;

  case 735:

/* Line 1455 of yacc.c  */
#line 4106 "parser.y"
    { BEGIN_STATEMENT ("ADD", TERM_ADD); ;}
    break;

  case 737:

/* Line 1455 of yacc.c  */
#line 4113 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '+', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 738:

/* Line 1455 of yacc.c  */
#line 4117 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(4) - (5)]), 0, cb_build_binary_list ((yyvsp[(1) - (5)]), '+'));
  ;}
    break;

  case 739:

/* Line 1455 of yacc.c  */
#line 4121 "parser.y"
    {
	cb_emit_corresponding (cb_build_add, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 741:

/* Line 1455 of yacc.c  */
#line 4127 "parser.y"
    { cb_list_add ((yyvsp[(0) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 742:

/* Line 1455 of yacc.c  */
#line 4131 "parser.y"
    { terminator_warning (TERM_ADD); ;}
    break;

  case 743:

/* Line 1455 of yacc.c  */
#line 4132 "parser.y"
    { terminator_clear (TERM_ADD); ;}
    break;

  case 744:

/* Line 1455 of yacc.c  */
#line 4141 "parser.y"
    { BEGIN_STATEMENT ("ALLOCATE", 0); ;}
    break;

  case 746:

/* Line 1455 of yacc.c  */
#line 4147 "parser.y"
    {
	cb_emit_allocate ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), NULL, (yyvsp[(2) - (3)]));
  ;}
    break;

  case 747:

/* Line 1455 of yacc.c  */
#line 4151 "parser.y"
    {
	cb_emit_allocate (NULL, (yyvsp[(5) - (5)]), (yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]));
  ;}
    break;

  case 748:

/* Line 1455 of yacc.c  */
#line 4157 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 749:

/* Line 1455 of yacc.c  */
#line 4158 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 750:

/* Line 1455 of yacc.c  */
#line 4168 "parser.y"
    {
	cb_error (_("ALTER statement is obsolete and unsupported"));
  ;}
    break;

  case 755:

/* Line 1455 of yacc.c  */
#line 4186 "parser.y"
    { BEGIN_STATEMENT ("CALL", TERM_CALL); ;}
    break;

  case 756:

/* Line 1455 of yacc.c  */
#line 4190 "parser.y"
    {
	cb_emit_call ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 757:

/* Line 1455 of yacc.c  */
#line 4196 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 758:

/* Line 1455 of yacc.c  */
#line 4198 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 759:

/* Line 1455 of yacc.c  */
#line 4202 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 760:

/* Line 1455 of yacc.c  */
#line 4206 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 761:

/* Line 1455 of yacc.c  */
#line 4208 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 762:

/* Line 1455 of yacc.c  */
#line 4213 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OMITTED only allowed with BY REFERENCE"));
	}
	(yyval) = cb_build_pair (cb_int (call_mode), cb_null);
  ;}
    break;

  case 763:

/* Line 1455 of yacc.c  */
#line 4220 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), (yyvsp[(3) - (3)]));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 765:

/* Line 1455 of yacc.c  */
#line 4229 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 766:

/* Line 1455 of yacc.c  */
#line 4233 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY CONTENT not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_CONTENT;
	}
  ;}
    break;

  case 767:

/* Line 1455 of yacc.c  */
#line 4241 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 768:

/* Line 1455 of yacc.c  */
#line 4251 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 769:

/* Line 1455 of yacc.c  */
#line 4252 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 770:

/* Line 1455 of yacc.c  */
#line 4253 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 771:

/* Line 1455 of yacc.c  */
#line 4258 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 772:

/* Line 1455 of yacc.c  */
#line 4262 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 773:

/* Line 1455 of yacc.c  */
#line 4266 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 774:

/* Line 1455 of yacc.c  */
#line 4273 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 775:

/* Line 1455 of yacc.c  */
#line 4277 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 776:

/* Line 1455 of yacc.c  */
#line 4281 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 777:

/* Line 1455 of yacc.c  */
#line 4287 "parser.y"
    { terminator_warning (TERM_CALL); ;}
    break;

  case 778:

/* Line 1455 of yacc.c  */
#line 4288 "parser.y"
    { terminator_clear (TERM_CALL); ;}
    break;

  case 779:

/* Line 1455 of yacc.c  */
#line 4297 "parser.y"
    { BEGIN_STATEMENT ("CANCEL", 0); ;}
    break;

  case 782:

/* Line 1455 of yacc.c  */
#line 4303 "parser.y"
    {
	cb_emit_cancel ((yyvsp[(2) - (2)]));
  ;}
    break;

  case 783:

/* Line 1455 of yacc.c  */
#line 4314 "parser.y"
    { BEGIN_STATEMENT ("CLOSE", 0); ;}
    break;

  case 786:

/* Line 1455 of yacc.c  */
#line 4321 "parser.y"
    {
	BEGIN_IMPLICIT_STATEMENT ();
	if ((yyvsp[(2) - (3)]) != cb_error_node) {
		cb_emit_close ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
	}
  ;}
    break;

  case 787:

/* Line 1455 of yacc.c  */
#line 4330 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NORMAL); ;}
    break;

  case 788:

/* Line 1455 of yacc.c  */
#line 4331 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT); ;}
    break;

  case 789:

/* Line 1455 of yacc.c  */
#line 4332 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT_REMOVAL); ;}
    break;

  case 790:

/* Line 1455 of yacc.c  */
#line 4333 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NO_REWIND); ;}
    break;

  case 791:

/* Line 1455 of yacc.c  */
#line 4334 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_LOCK); ;}
    break;

  case 794:

/* Line 1455 of yacc.c  */
#line 4345 "parser.y"
    { BEGIN_STATEMENT ("COMPUTE", TERM_COMPUTE); ;}
    break;

  case 796:

/* Line 1455 of yacc.c  */
#line 4352 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(1) - (4)]), 0, (yyvsp[(3) - (4)]));
  ;}
    break;

  case 797:

/* Line 1455 of yacc.c  */
#line 4358 "parser.y"
    { terminator_warning (TERM_COMPUTE); ;}
    break;

  case 798:

/* Line 1455 of yacc.c  */
#line 4359 "parser.y"
    { terminator_clear (TERM_COMPUTE); ;}
    break;

  case 801:

/* Line 1455 of yacc.c  */
#line 4370 "parser.y"
    {
	BEGIN_STATEMENT ("COMMIT", 0);
	cb_emit_commit ();
  ;}
    break;

  case 802:

/* Line 1455 of yacc.c  */
#line 4383 "parser.y"
    {
	BEGIN_STATEMENT ("CONTINUE", 0);
	cb_emit_continue ();
  ;}
    break;

  case 803:

/* Line 1455 of yacc.c  */
#line 4395 "parser.y"
    { BEGIN_STATEMENT ("DELETE", TERM_DELETE); ;}
    break;

  case 804:

/* Line 1455 of yacc.c  */
#line 4398 "parser.y"
    {
	if ((yyvsp[(3) - (6)]) != cb_error_node) {
		cb_emit_delete ((yyvsp[(3) - (6)]));
	}
  ;}
    break;

  case 805:

/* Line 1455 of yacc.c  */
#line 4406 "parser.y"
    { terminator_warning (TERM_DELETE); ;}
    break;

  case 806:

/* Line 1455 of yacc.c  */
#line 4407 "parser.y"
    { terminator_clear (TERM_DELETE); ;}
    break;

  case 807:

/* Line 1455 of yacc.c  */
#line 4416 "parser.y"
    { BEGIN_STATEMENT ("DELETE-FILE", 0); ;}
    break;

  case 808:

/* Line 1455 of yacc.c  */
#line 4418 "parser.y"
    {
	cb_tree l;
	for (l = (yyvsp[(4) - (4)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			BEGIN_IMPLICIT_STATEMENT ();
			cb_emit_delete_file (CB_VALUE (l));
		}
	}
  ;}
    break;

  case 809:

/* Line 1455 of yacc.c  */
#line 4436 "parser.y"
    {
	BEGIN_STATEMENT ("DISPLAY", TERM_DISPLAY);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 811:

/* Line 1455 of yacc.c  */
#line 4449 "parser.y"
    {
	cb_emit_env_name ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 812:

/* Line 1455 of yacc.c  */
#line 4453 "parser.y"
    {
	cb_emit_env_value ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 813:

/* Line 1455 of yacc.c  */
#line 4457 "parser.y"
    {
	cb_emit_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 814:

/* Line 1455 of yacc.c  */
#line 4461 "parser.y"
    {
	cb_emit_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 815:

/* Line 1455 of yacc.c  */
#line 4465 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (4)]), cb_int0, (yyvsp[(3) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 816:

/* Line 1455 of yacc.c  */
#line 4469 "parser.y"
    {
	cb_emit_display_mnemonic ((yyvsp[(1) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 817:

/* Line 1455 of yacc.c  */
#line 4473 "parser.y"
    {
	cb_tree word = cb_build_display_upon_direct ((yyvsp[(4) - (6)]));
	cb_emit_display ((yyvsp[(1) - (6)]), word, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 818:

/* Line 1455 of yacc.c  */
#line 4478 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 819:

/* Line 1455 of yacc.c  */
#line 4482 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 820:

/* Line 1455 of yacc.c  */
#line 4488 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 821:

/* Line 1455 of yacc.c  */
#line 4489 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 822:

/* Line 1455 of yacc.c  */
#line 4490 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 825:

/* Line 1455 of yacc.c  */
#line 4500 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 826:

/* Line 1455 of yacc.c  */
#line 4501 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 827:

/* Line 1455 of yacc.c  */
#line 4502 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 828:

/* Line 1455 of yacc.c  */
#line 4503 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 829:

/* Line 1455 of yacc.c  */
#line 4504 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 830:

/* Line 1455 of yacc.c  */
#line 4505 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 831:

/* Line 1455 of yacc.c  */
#line 4506 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 832:

/* Line 1455 of yacc.c  */
#line 4507 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 833:

/* Line 1455 of yacc.c  */
#line 4508 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 834:

/* Line 1455 of yacc.c  */
#line 4510 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 835:

/* Line 1455 of yacc.c  */
#line 4514 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 836:

/* Line 1455 of yacc.c  */
#line 4518 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 837:

/* Line 1455 of yacc.c  */
#line 4522 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 838:

/* Line 1455 of yacc.c  */
#line 4526 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 839:

/* Line 1455 of yacc.c  */
#line 4527 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 840:

/* Line 1455 of yacc.c  */
#line 4531 "parser.y"
    { terminator_warning (TERM_DISPLAY); ;}
    break;

  case 841:

/* Line 1455 of yacc.c  */
#line 4532 "parser.y"
    { terminator_clear (TERM_DISPLAY); ;}
    break;

  case 842:

/* Line 1455 of yacc.c  */
#line 4541 "parser.y"
    { BEGIN_STATEMENT ("DIVIDE", TERM_DIVIDE); ;}
    break;

  case 844:

/* Line 1455 of yacc.c  */
#line 4548 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '/', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 845:

/* Line 1455 of yacc.c  */
#line 4552 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(3) - (6)]), '/', (yyvsp[(1) - (6)])));
  ;}
    break;

  case 846:

/* Line 1455 of yacc.c  */
#line 4556 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '/', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 847:

/* Line 1455 of yacc.c  */
#line 4560 "parser.y"
    {
	cb_emit_divide ((yyvsp[(3) - (8)]), (yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 848:

/* Line 1455 of yacc.c  */
#line 4564 "parser.y"
    {
	cb_emit_divide ((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 849:

/* Line 1455 of yacc.c  */
#line 4570 "parser.y"
    { terminator_warning (TERM_DIVIDE); ;}
    break;

  case 850:

/* Line 1455 of yacc.c  */
#line 4571 "parser.y"
    { terminator_clear (TERM_DIVIDE); ;}
    break;

  case 851:

/* Line 1455 of yacc.c  */
#line 4580 "parser.y"
    { BEGIN_STATEMENT ("ENTRY", 0); ;}
    break;

  case 852:

/* Line 1455 of yacc.c  */
#line 4582 "parser.y"
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
  ;}
    break;

  case 853:

/* Line 1455 of yacc.c  */
#line 4602 "parser.y"
    {
	BEGIN_STATEMENT ("EVALUATE", TERM_EVALUATE);
	eval_level++;
	for (eval_inc = 0; eval_inc < 64; eval_inc++) {
		eval_check[eval_level][eval_inc] = 0;
	}
	eval_inc = 0;
	eval_inc2 = 0;
  ;}
    break;

  case 854:

/* Line 1455 of yacc.c  */
#line 4613 "parser.y"
    {
	cb_emit_evaluate ((yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]));
	eval_level--;
  ;}
    break;

  case 855:

/* Line 1455 of yacc.c  */
#line 4620 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 856:

/* Line 1455 of yacc.c  */
#line 4623 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 857:

/* Line 1455 of yacc.c  */
#line 4633 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE_P ((yyvsp[(1) - (1)]))) {
		eval_check[eval_level][eval_inc++] = 0;
	} else {
		eval_check[eval_level][eval_inc++] = 1;
	}
  ;}
    break;

  case 858:

/* Line 1455 of yacc.c  */
#line 4642 "parser.y"
    {
	(yyval) = cb_true;
	eval_check[eval_level][eval_inc++] = 2;
  ;}
    break;

  case 859:

/* Line 1455 of yacc.c  */
#line 4647 "parser.y"
    {
	(yyval) = cb_false;
	eval_check[eval_level][eval_inc++] = 3;
  ;}
    break;

  case 860:

/* Line 1455 of yacc.c  */
#line 4655 "parser.y"
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
  ;}
    break;

  case 861:

/* Line 1455 of yacc.c  */
#line 4683 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 862:

/* Line 1455 of yacc.c  */
#line 4685 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 863:

/* Line 1455 of yacc.c  */
#line 4690 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 864:

/* Line 1455 of yacc.c  */
#line 4694 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]));
	eval_inc2 = 0;
  ;}
    break;

  case 865:

/* Line 1455 of yacc.c  */
#line 4705 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 866:

/* Line 1455 of yacc.c  */
#line 4709 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 867:

/* Line 1455 of yacc.c  */
#line 4713 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), NULL);
	eval_inc2 = 0;
  ;}
    break;

  case 868:

/* Line 1455 of yacc.c  */
#line 4723 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 869:

/* Line 1455 of yacc.c  */
#line 4725 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 870:

/* Line 1455 of yacc.c  */
#line 4729 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 871:

/* Line 1455 of yacc.c  */
#line 4732 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 872:

/* Line 1455 of yacc.c  */
#line 4742 "parser.y"
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
  ;}
    break;

  case 873:

/* Line 1455 of yacc.c  */
#line 4770 "parser.y"
    { (yyval) = cb_any; eval_inc2++; ;}
    break;

  case 874:

/* Line 1455 of yacc.c  */
#line 4771 "parser.y"
    { (yyval) = cb_true; eval_inc2++; ;}
    break;

  case 875:

/* Line 1455 of yacc.c  */
#line 4772 "parser.y"
    { (yyval) = cb_false; eval_inc2++; ;}
    break;

  case 876:

/* Line 1455 of yacc.c  */
#line 4775 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 877:

/* Line 1455 of yacc.c  */
#line 4776 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 878:

/* Line 1455 of yacc.c  */
#line 4780 "parser.y"
    { terminator_warning (TERM_EVALUATE); ;}
    break;

  case 879:

/* Line 1455 of yacc.c  */
#line 4781 "parser.y"
    { terminator_clear (TERM_EVALUATE); ;}
    break;

  case 880:

/* Line 1455 of yacc.c  */
#line 4790 "parser.y"
    { BEGIN_STATEMENT ("EXIT", 0); ;}
    break;

  case 882:

/* Line 1455 of yacc.c  */
#line 4795 "parser.y"
    { /* nothing */ ;}
    break;

  case 883:

/* Line 1455 of yacc.c  */
#line 4797 "parser.y"
    {
	if (in_declaratives && use_global_ind) {
		cb_error (_("EXIT PROGRAM is not allowed within a USE GLOBAL procedure"));
	}
	check_unreached = 1;
	cb_emit_exit (0);
  ;}
    break;

  case 884:

/* Line 1455 of yacc.c  */
#line 4805 "parser.y"
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
			CB_LABEL (cb_build_label (p->exit_label, NULL))->need_begin = 1;
		}
		cb_emit_goto (cb_list_init (p->exit_label), NULL);
	}
  ;}
    break;

  case 885:

/* Line 1455 of yacc.c  */
#line 4822 "parser.y"
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
			CB_LABEL (cb_build_label (p->cycle_label, NULL))->need_begin = 1;
		}
		cb_emit_goto (cb_list_init (p->cycle_label), NULL);
	}
  ;}
    break;

  case 886:

/* Line 1455 of yacc.c  */
#line 4839 "parser.y"
    {
	cb_tree	plabel;
	char	name[64];

	if (!current_section) {
		cb_error (_("EXIT SECTION is only valid with an active SECTION"));
	} else {
		if (!current_section->exit_label) {
			sprintf (name, "EXIT SECTION %d", cb_id);
			plabel = cb_build_reference (name);
			current_section->exit_label = cb_build_label (plabel, NULL);
			current_section->exit_label_ref = plabel;
			CB_LABEL (current_section->exit_label)->need_begin = 1;
		}
		cb_emit_goto (cb_list_init (current_section->exit_label_ref), NULL);
	}
  ;}
    break;

  case 887:

/* Line 1455 of yacc.c  */
#line 4857 "parser.y"
    {
	cb_tree	plabel;
	char	name[64];

	if (!current_paragraph) {
		cb_error (_("EXIT PARAGRAPH is only valid with an active PARAGRAPH"));
	} else {
		if (!current_paragraph->exit_label) {
			sprintf (name, "EXIT PARAGRAPH %d", cb_id);
			plabel = cb_build_reference (name);
			current_paragraph->exit_label = cb_build_label (plabel, NULL);
			current_paragraph->exit_label_ref = plabel;
			CB_LABEL (current_paragraph->exit_label)->need_begin = 1;
		}
		cb_emit_goto (cb_list_init (current_paragraph->exit_label_ref), NULL);
	}
  ;}
    break;

  case 888:

/* Line 1455 of yacc.c  */
#line 4881 "parser.y"
    { BEGIN_STATEMENT ("FREE", 0); ;}
    break;

  case 889:

/* Line 1455 of yacc.c  */
#line 4883 "parser.y"
    {
	cb_emit_free ((yyvsp[(3) - (3)]));
  ;}
    break;

  case 890:

/* Line 1455 of yacc.c  */
#line 4894 "parser.y"
    { BEGIN_STATEMENT ("GENERATE", 0); ;}
    break;

  case 891:

/* Line 1455 of yacc.c  */
#line 4896 "parser.y"
    {
	PENDING("GENERATE");
  ;}
    break;

  case 892:

/* Line 1455 of yacc.c  */
#line 4907 "parser.y"
    { BEGIN_STATEMENT ("GO TO", 0); ;}
    break;

  case 893:

/* Line 1455 of yacc.c  */
#line 4909 "parser.y"
    {
	cb_emit_goto ((yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 894:

/* Line 1455 of yacc.c  */
#line 4916 "parser.y"
    {
	check_unreached = 1;
	(yyval) = NULL;
  ;}
    break;

  case 895:

/* Line 1455 of yacc.c  */
#line 4921 "parser.y"
    {
	check_unreached = 0;
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 896:

/* Line 1455 of yacc.c  */
#line 4933 "parser.y"
    { BEGIN_STATEMENT ("GOBACK", 0); ;}
    break;

  case 897:

/* Line 1455 of yacc.c  */
#line 4934 "parser.y"
    {
	check_unreached = 1;
	cb_emit_exit (1);
  ;}
    break;

  case 898:

/* Line 1455 of yacc.c  */
#line 4946 "parser.y"
    { BEGIN_STATEMENT ("IF", TERM_IF); ;}
    break;

  case 899:

/* Line 1455 of yacc.c  */
#line 4948 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 900:

/* Line 1455 of yacc.c  */
#line 4953 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(6) - (8)]) == NULL) {
		cb_error (_("syntax error"));
	}
	cb_emit_if ((yyvsp[(3) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 902:

/* Line 1455 of yacc.c  */
#line 4964 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 903:

/* Line 1455 of yacc.c  */
#line 4968 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 904:

/* Line 1455 of yacc.c  */
#line 4972 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 905:

/* Line 1455 of yacc.c  */
#line 4981 "parser.y"
    { terminator_warning (TERM_IF); ;}
    break;

  case 906:

/* Line 1455 of yacc.c  */
#line 4982 "parser.y"
    { terminator_clear (TERM_IF); ;}
    break;

  case 907:

/* Line 1455 of yacc.c  */
#line 4991 "parser.y"
    { BEGIN_STATEMENT ("INITIALIZE", 0); ;}
    break;

  case 908:

/* Line 1455 of yacc.c  */
#line 4993 "parser.y"
    {
	cb_emit_initialize ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 909:

/* Line 1455 of yacc.c  */
#line 4999 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 910:

/* Line 1455 of yacc.c  */
#line 5000 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 911:

/* Line 1455 of yacc.c  */
#line 5004 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 912:

/* Line 1455 of yacc.c  */
#line 5005 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 913:

/* Line 1455 of yacc.c  */
#line 5006 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 914:

/* Line 1455 of yacc.c  */
#line 5010 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 915:

/* Line 1455 of yacc.c  */
#line 5012 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 916:

/* Line 1455 of yacc.c  */
#line 5016 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 917:

/* Line 1455 of yacc.c  */
#line 5018 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 918:

/* Line 1455 of yacc.c  */
#line 5022 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 919:

/* Line 1455 of yacc.c  */
#line 5026 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHABETIC); ;}
    break;

  case 920:

/* Line 1455 of yacc.c  */
#line 5027 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC); ;}
    break;

  case 921:

/* Line 1455 of yacc.c  */
#line 5028 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC); ;}
    break;

  case 922:

/* Line 1455 of yacc.c  */
#line 5029 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC_EDITED); ;}
    break;

  case 923:

/* Line 1455 of yacc.c  */
#line 5030 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC_EDITED); ;}
    break;

  case 924:

/* Line 1455 of yacc.c  */
#line 5031 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL); ;}
    break;

  case 925:

/* Line 1455 of yacc.c  */
#line 5032 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL_EDITED); ;}
    break;

  case 926:

/* Line 1455 of yacc.c  */
#line 5036 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 927:

/* Line 1455 of yacc.c  */
#line 5037 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 928:

/* Line 1455 of yacc.c  */
#line 5046 "parser.y"
    { BEGIN_STATEMENT ("INITIATE", 0); ;}
    break;

  case 929:

/* Line 1455 of yacc.c  */
#line 5048 "parser.y"
    {
	PENDING("INITIATE");
  ;}
    break;

  case 930:

/* Line 1455 of yacc.c  */
#line 5059 "parser.y"
    {
	BEGIN_STATEMENT ("INSPECT", 0);
	sending_id = 0;
	inspect_keyword = 0;
  ;}
    break;

  case 932:

/* Line 1455 of yacc.c  */
#line 5068 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 0; ;}
    break;

  case 933:

/* Line 1455 of yacc.c  */
#line 5069 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 934:

/* Line 1455 of yacc.c  */
#line 5070 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 937:

/* Line 1455 of yacc.c  */
#line 5079 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 0); ;}
    break;

  case 938:

/* Line 1455 of yacc.c  */
#line 5080 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int1, 1); ;}
    break;

  case 939:

/* Line 1455 of yacc.c  */
#line 5081 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 2); ;}
    break;

  case 940:

/* Line 1455 of yacc.c  */
#line 5087 "parser.y"
    { cb_init_tarrying (); ;}
    break;

  case 941:

/* Line 1455 of yacc.c  */
#line 5088 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 942:

/* Line 1455 of yacc.c  */
#line 5092 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 943:

/* Line 1455 of yacc.c  */
#line 5093 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 944:

/* Line 1455 of yacc.c  */
#line 5097 "parser.y"
    { (yyval) = cb_build_tarrying_data ((yyvsp[(1) - (2)])); ;}
    break;

  case 945:

/* Line 1455 of yacc.c  */
#line 5098 "parser.y"
    { (yyval) = cb_build_tarrying_characters ((yyvsp[(2) - (2)])); ;}
    break;

  case 946:

/* Line 1455 of yacc.c  */
#line 5099 "parser.y"
    { (yyval) = cb_build_tarrying_all (); ;}
    break;

  case 947:

/* Line 1455 of yacc.c  */
#line 5100 "parser.y"
    { (yyval) = cb_build_tarrying_leading (); ;}
    break;

  case 948:

/* Line 1455 of yacc.c  */
#line 5101 "parser.y"
    { (yyval) = cb_build_tarrying_trailing (); ;}
    break;

  case 949:

/* Line 1455 of yacc.c  */
#line 5102 "parser.y"
    { (yyval) = cb_build_tarrying_value ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 950:

/* Line 1455 of yacc.c  */
#line 5108 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); inspect_keyword = 0; ;}
    break;

  case 951:

/* Line 1455 of yacc.c  */
#line 5112 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 952:

/* Line 1455 of yacc.c  */
#line 5113 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 953:

/* Line 1455 of yacc.c  */
#line 5118 "parser.y"
    {
	(yyval) = cb_build_replacing_characters ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]), save_tree_1);
	inspect_keyword = 0;
  ;}
    break;

  case 954:

/* Line 1455 of yacc.c  */
#line 5122 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 955:

/* Line 1455 of yacc.c  */
#line 5126 "parser.y"
    { /* Nothing */ ;}
    break;

  case 956:

/* Line 1455 of yacc.c  */
#line 5127 "parser.y"
    { inspect_keyword = 1; ;}
    break;

  case 957:

/* Line 1455 of yacc.c  */
#line 5128 "parser.y"
    { inspect_keyword = 2; ;}
    break;

  case 958:

/* Line 1455 of yacc.c  */
#line 5129 "parser.y"
    { inspect_keyword = 3; ;}
    break;

  case 959:

/* Line 1455 of yacc.c  */
#line 5130 "parser.y"
    { inspect_keyword = 4; ;}
    break;

  case 960:

/* Line 1455 of yacc.c  */
#line 5135 "parser.y"
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
  ;}
    break;

  case 961:

/* Line 1455 of yacc.c  */
#line 5161 "parser.y"
    {
	if (cb_validate_inspect (save_tree_1, (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])) < 0 ) {
		(yyval) = cb_error_node;
	} else {
		(yyval) = cb_build_converting ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 962:

/* Line 1455 of yacc.c  */
#line 5173 "parser.y"
    { (yyval) = cb_build_inspect_region_start (); ;}
    break;

  case 963:

/* Line 1455 of yacc.c  */
#line 5175 "parser.y"
    { (yyval) = cb_build_inspect_region ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 966:

/* Line 1455 of yacc.c  */
#line 5186 "parser.y"
    { BEGIN_STATEMENT ("MERGE", 0); ;}
    break;

  case 968:

/* Line 1455 of yacc.c  */
#line 5196 "parser.y"
    { BEGIN_STATEMENT ("MOVE", 0); ;}
    break;

  case 970:

/* Line 1455 of yacc.c  */
#line 5202 "parser.y"
    {
	cb_emit_move ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 971:

/* Line 1455 of yacc.c  */
#line 5206 "parser.y"
    {
	cb_emit_move_corresponding ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 972:

/* Line 1455 of yacc.c  */
#line 5217 "parser.y"
    { BEGIN_STATEMENT ("MULTIPLY", TERM_MULTIPLY); ;}
    break;

  case 974:

/* Line 1455 of yacc.c  */
#line 5224 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '*', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 975:

/* Line 1455 of yacc.c  */
#line 5228 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '*', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 976:

/* Line 1455 of yacc.c  */
#line 5234 "parser.y"
    { terminator_warning (TERM_MULTIPLY); ;}
    break;

  case 977:

/* Line 1455 of yacc.c  */
#line 5235 "parser.y"
    { terminator_clear (TERM_MULTIPLY); ;}
    break;

  case 978:

/* Line 1455 of yacc.c  */
#line 5244 "parser.y"
    { BEGIN_STATEMENT ("OPEN", 0); ;}
    break;

  case 981:

/* Line 1455 of yacc.c  */
#line 5251 "parser.y"
    {
	cb_tree l;
	for (l = (yyvsp[(4) - (5)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			BEGIN_IMPLICIT_STATEMENT ();
			cb_emit_open (CB_VALUE (l), (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]));
		}
	}
  ;}
    break;

  case 982:

/* Line 1455 of yacc.c  */
#line 5263 "parser.y"
    { (yyval) = cb_int (COB_OPEN_INPUT); ;}
    break;

  case 983:

/* Line 1455 of yacc.c  */
#line 5264 "parser.y"
    { (yyval) = cb_int (COB_OPEN_OUTPUT); ;}
    break;

  case 984:

/* Line 1455 of yacc.c  */
#line 5265 "parser.y"
    { (yyval) = cb_int (COB_OPEN_I_O); ;}
    break;

  case 985:

/* Line 1455 of yacc.c  */
#line 5266 "parser.y"
    { (yyval) = cb_int (COB_OPEN_EXTEND); ;}
    break;

  case 986:

/* Line 1455 of yacc.c  */
#line 5270 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 987:

/* Line 1455 of yacc.c  */
#line 5271 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 988:

/* Line 1455 of yacc.c  */
#line 5275 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 989:

/* Line 1455 of yacc.c  */
#line 5276 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 990:

/* Line 1455 of yacc.c  */
#line 5277 "parser.y"
    { PENDING ("OPEN ... WITH LOCK"); ;}
    break;

  case 991:

/* Line 1455 of yacc.c  */
#line 5289 "parser.y"
    { BEGIN_STATEMENT ("PERFORM", TERM_PERFORM); ;}
    break;

  case 993:

/* Line 1455 of yacc.c  */
#line 5295 "parser.y"
    {
	cb_emit_perform ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));
  ;}
    break;

  case 994:

/* Line 1455 of yacc.c  */
#line 5299 "parser.y"
    {
	perform_stack = cb_cons ((yyvsp[(1) - (1)]), perform_stack);
	check_unreached = 0;
  ;}
    break;

  case 995:

/* Line 1455 of yacc.c  */
#line 5304 "parser.y"
    {
	perform_stack = CB_CHAIN (perform_stack);
	cb_emit_perform ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 996:

/* Line 1455 of yacc.c  */
#line 5309 "parser.y"
    {
	cb_emit_perform ((yyvsp[(1) - (2)]), NULL);
  ;}
    break;

  case 997:

/* Line 1455 of yacc.c  */
#line 5315 "parser.y"
    { terminator_error (); ;}
    break;

  case 998:

/* Line 1455 of yacc.c  */
#line 5316 "parser.y"
    { terminator_clear (TERM_PERFORM); ;}
    break;

  case 999:

/* Line 1455 of yacc.c  */
#line 5321 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(1) - (1)]))->length = cb_true; /* return from $1 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (1)]), (yyvsp[(1) - (1)]));
  ;}
    break;

  case 1000:

/* Line 1455 of yacc.c  */
#line 5326 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(3) - (3)]))->length = cb_true; /* return from $3 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1001:

/* Line 1455 of yacc.c  */
#line 5334 "parser.y"
    {
	(yyval) = cb_build_perform_once (NULL);
  ;}
    break;

  case 1002:

/* Line 1455 of yacc.c  */
#line 5338 "parser.y"
    {
	(yyval) = cb_build_perform_forever (NULL);
  ;}
    break;

  case 1003:

/* Line 1455 of yacc.c  */
#line 5342 "parser.y"
    {
	(yyval) = cb_build_perform_times ((yyvsp[(1) - (2)]));
	current_program->loop_counter++;
  ;}
    break;

  case 1004:

/* Line 1455 of yacc.c  */
#line 5347 "parser.y"
    {
	cb_tree varying;

	varying = cb_list_init (cb_build_perform_varying (NULL, NULL, NULL, (yyvsp[(3) - (3)])));
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), varying);
  ;}
    break;

  case 1005:

/* Line 1455 of yacc.c  */
#line 5354 "parser.y"
    {
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1006:

/* Line 1455 of yacc.c  */
#line 5360 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1007:

/* Line 1455 of yacc.c  */
#line 5361 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1008:

/* Line 1455 of yacc.c  */
#line 5365 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1009:

/* Line 1455 of yacc.c  */
#line 5367 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1010:

/* Line 1455 of yacc.c  */
#line 5372 "parser.y"
    {
	(yyval) = cb_build_perform_varying ((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1011:

/* Line 1455 of yacc.c  */
#line 5383 "parser.y"
    { BEGIN_STATEMENT ("READ", TERM_READ); ;}
    break;

  case 1012:

/* Line 1455 of yacc.c  */
#line 5386 "parser.y"
    {
	if ((yyvsp[(3) - (10)]) != cb_error_node) {
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
  ;}
    break;

  case 1013:

/* Line 1455 of yacc.c  */
#line 5406 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1014:

/* Line 1455 of yacc.c  */
#line 5407 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1015:

/* Line 1455 of yacc.c  */
#line 5411 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1016:

/* Line 1455 of yacc.c  */
#line 5413 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1017:

/* Line 1455 of yacc.c  */
#line 5417 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1018:

/* Line 1455 of yacc.c  */
#line 5421 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1019:

/* Line 1455 of yacc.c  */
#line 5425 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1020:

/* Line 1455 of yacc.c  */
#line 5429 "parser.y"
    {
	(yyval) = cb_int4;
  ;}
    break;

  case 1021:

/* Line 1455 of yacc.c  */
#line 5435 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1022:

/* Line 1455 of yacc.c  */
#line 5437 "parser.y"
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
  ;}
    break;

  case 1026:

/* Line 1455 of yacc.c  */
#line 5456 "parser.y"
    { terminator_warning (TERM_READ); ;}
    break;

  case 1027:

/* Line 1455 of yacc.c  */
#line 5457 "parser.y"
    { terminator_clear (TERM_READ); ;}
    break;

  case 1028:

/* Line 1455 of yacc.c  */
#line 5466 "parser.y"
    { BEGIN_STATEMENT ("RELEASE", 0); ;}
    break;

  case 1029:

/* Line 1455 of yacc.c  */
#line 5468 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_release ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
	}
  ;}
    break;

  case 1030:

/* Line 1455 of yacc.c  */
#line 5481 "parser.y"
    { BEGIN_STATEMENT ("RETURN", TERM_RETURN); ;}
    break;

  case 1031:

/* Line 1455 of yacc.c  */
#line 5484 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_return ((yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]));
	}
  ;}
    break;

  case 1032:

/* Line 1455 of yacc.c  */
#line 5492 "parser.y"
    { terminator_warning (TERM_RETURN); ;}
    break;

  case 1033:

/* Line 1455 of yacc.c  */
#line 5493 "parser.y"
    { terminator_clear (TERM_RETURN); ;}
    break;

  case 1034:

/* Line 1455 of yacc.c  */
#line 5502 "parser.y"
    { BEGIN_STATEMENT ("REWRITE", TERM_REWRITE); ;}
    break;

  case 1035:

/* Line 1455 of yacc.c  */
#line 5505 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_rewrite ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]));
	}
  ;}
    break;

  case 1036:

/* Line 1455 of yacc.c  */
#line 5513 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1037:

/* Line 1455 of yacc.c  */
#line 5515 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1038:

/* Line 1455 of yacc.c  */
#line 5519 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1039:

/* Line 1455 of yacc.c  */
#line 5525 "parser.y"
    { terminator_warning (TERM_REWRITE); ;}
    break;

  case 1040:

/* Line 1455 of yacc.c  */
#line 5526 "parser.y"
    { terminator_clear (TERM_REWRITE); ;}
    break;

  case 1041:

/* Line 1455 of yacc.c  */
#line 5536 "parser.y"
    {
	BEGIN_STATEMENT ("ROLLBACK", 0);
	cb_emit_rollback ();
  ;}
    break;

  case 1042:

/* Line 1455 of yacc.c  */
#line 5548 "parser.y"
    { BEGIN_STATEMENT ("SEARCH", TERM_SEARCH); ;}
    break;

  case 1044:

/* Line 1455 of yacc.c  */
#line 5555 "parser.y"
    {
	cb_emit_search ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1045:

/* Line 1455 of yacc.c  */
#line 5559 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1046:

/* Line 1455 of yacc.c  */
#line 5563 "parser.y"
    {
	cb_emit_search_all ((yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1047:

/* Line 1455 of yacc.c  */
#line 5569 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1048:

/* Line 1455 of yacc.c  */
#line 5570 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1049:

/* Line 1455 of yacc.c  */
#line 5574 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1050:

/* Line 1455 of yacc.c  */
#line 5576 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1051:

/* Line 1455 of yacc.c  */
#line 5580 "parser.y"
    {
	(yyval) = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 1052:

/* Line 1455 of yacc.c  */
#line 5586 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1053:

/* Line 1455 of yacc.c  */
#line 5587 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); CB_IF ((yyvsp[(1) - (2)]))->stmt2 = (yyvsp[(2) - (2)]); ;}
    break;

  case 1054:

/* Line 1455 of yacc.c  */
#line 5592 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1055:

/* Line 1455 of yacc.c  */
#line 5596 "parser.y"
    {
	(yyval) = cb_build_if ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), NULL);
  ;}
    break;

  case 1056:

/* Line 1455 of yacc.c  */
#line 5602 "parser.y"
    { terminator_warning (TERM_SEARCH); ;}
    break;

  case 1057:

/* Line 1455 of yacc.c  */
#line 5603 "parser.y"
    { terminator_clear (TERM_SEARCH); ;}
    break;

  case 1058:

/* Line 1455 of yacc.c  */
#line 5612 "parser.y"
    { BEGIN_STATEMENT ("SET", 0); ;}
    break;

  case 1065:

/* Line 1455 of yacc.c  */
#line 5628 "parser.y"
    {
	cb_emit_setenv ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1066:

/* Line 1455 of yacc.c  */
#line 5637 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (4)]), cb_build_ppointer ((yyvsp[(4) - (4)])));
  ;}
    break;

  case 1067:

/* Line 1455 of yacc.c  */
#line 5641 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1068:

/* Line 1455 of yacc.c  */
#line 5650 "parser.y"
    {
	cb_emit_set_up_down ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1069:

/* Line 1455 of yacc.c  */
#line 5656 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1070:

/* Line 1455 of yacc.c  */
#line 5657 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1073:

/* Line 1455 of yacc.c  */
#line 5669 "parser.y"
    {
	cb_emit_set_on_off ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1076:

/* Line 1455 of yacc.c  */
#line 5683 "parser.y"
    {
	cb_emit_set_true ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1077:

/* Line 1455 of yacc.c  */
#line 5687 "parser.y"
    {
	cb_emit_set_false ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1078:

/* Line 1455 of yacc.c  */
#line 5698 "parser.y"
    { BEGIN_STATEMENT ("SORT", 0); ;}
    break;

  case 1080:

/* Line 1455 of yacc.c  */
#line 5704 "parser.y"
    {
	cb_emit_sort_init ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (4)]))) && (yyvsp[(2) - (4)]) == NULL) {
		cb_error (_("File sort requires KEY phrase"));
	}
	/* used in sort_input/sort_output */
	save_tree_1 = (yyvsp[(1) - (4)]);
  ;}
    break;

  case 1081:

/* Line 1455 of yacc.c  */
#line 5713 "parser.y"
    {
	cb_emit_sort_finish ((yyvsp[(1) - (7)]));
  ;}
    break;

  case 1082:

/* Line 1455 of yacc.c  */
#line 5720 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 1083:

/* Line 1455 of yacc.c  */
#line 5725 "parser.y"
    {
	cb_tree l;

	if ((yyvsp[(5) - (5)]) == NULL) {
		(yyvsp[(5) - (5)]) = cb_list_init (NULL);
	}
	for (l = (yyvsp[(5) - (5)]); l; l = CB_CHAIN (l)) {
		CB_PURPOSE (l) = (yyvsp[(3) - (5)]);
	}
	(yyval) = cb_list_append ((yyvsp[(1) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1084:

/* Line 1455 of yacc.c  */
#line 5739 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1085:

/* Line 1455 of yacc.c  */
#line 5740 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1087:

/* Line 1455 of yacc.c  */
#line 5744 "parser.y"
    { /* nothing */ ;}
    break;

  case 1088:

/* Line 1455 of yacc.c  */
#line 5748 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1089:

/* Line 1455 of yacc.c  */
#line 5749 "parser.y"
    { (yyval) = cb_ref ((yyvsp[(3) - (3)])); ;}
    break;

  case 1090:

/* Line 1455 of yacc.c  */
#line 5754 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires USING or INPUT PROCEDURE"));
	}
  ;}
    break;

  case 1091:

/* Line 1455 of yacc.c  */
#line 5760 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("USING invalid with table SORT"));
	} else {
		cb_emit_sort_using (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1092:

/* Line 1455 of yacc.c  */
#line 5768 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("INPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_input ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1093:

/* Line 1455 of yacc.c  */
#line 5779 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires GIVING or OUTPUT PROCEDURE"));
	}
  ;}
    break;

  case 1094:

/* Line 1455 of yacc.c  */
#line 5785 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("GIVING invalid with table SORT"));
	} else {
		cb_emit_sort_giving (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1095:

/* Line 1455 of yacc.c  */
#line 5793 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("OUTPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_output ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1096:

/* Line 1455 of yacc.c  */
#line 5808 "parser.y"
    { BEGIN_STATEMENT ("START", TERM_START); ;}
    break;

  case 1097:

/* Line 1455 of yacc.c  */
#line 5809 "parser.y"
    { (yyval) = cb_int (COB_EQ); ;}
    break;

  case 1098:

/* Line 1455 of yacc.c  */
#line 5812 "parser.y"
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
  ;}
    break;

  case 1099:

/* Line 1455 of yacc.c  */
#line 5829 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1100:

/* Line 1455 of yacc.c  */
#line 5831 "parser.y"
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
  ;}
    break;

  case 1101:

/* Line 1455 of yacc.c  */
#line 5846 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_NE : COB_EQ); ;}
    break;

  case 1102:

/* Line 1455 of yacc.c  */
#line 5847 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LE : COB_GT); ;}
    break;

  case 1103:

/* Line 1455 of yacc.c  */
#line 5848 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GE : COB_LT); ;}
    break;

  case 1104:

/* Line 1455 of yacc.c  */
#line 5849 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LT : COB_GE); ;}
    break;

  case 1105:

/* Line 1455 of yacc.c  */
#line 5850 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GT : COB_LE); ;}
    break;

  case 1106:

/* Line 1455 of yacc.c  */
#line 5854 "parser.y"
    { terminator_warning (TERM_START); ;}
    break;

  case 1107:

/* Line 1455 of yacc.c  */
#line 5855 "parser.y"
    { terminator_clear (TERM_START); ;}
    break;

  case 1108:

/* Line 1455 of yacc.c  */
#line 5864 "parser.y"
    { BEGIN_STATEMENT ("STOP", 0); ;}
    break;

  case 1109:

/* Line 1455 of yacc.c  */
#line 5866 "parser.y"
    {
	cb_emit_stop_run ((yyvsp[(4) - (4)]));
  ;}
    break;

  case 1110:

/* Line 1455 of yacc.c  */
#line 5870 "parser.y"
    {
	cb_verify (cb_stop_literal_statement, "STOP literal");
  ;}
    break;

  case 1111:

/* Line 1455 of yacc.c  */
#line 5876 "parser.y"
    { (yyval) = current_program->cb_return_code; ;}
    break;

  case 1112:

/* Line 1455 of yacc.c  */
#line 5877 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1113:

/* Line 1455 of yacc.c  */
#line 5878 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1114:

/* Line 1455 of yacc.c  */
#line 5887 "parser.y"
    { BEGIN_STATEMENT ("STRING", TERM_STRING); ;}
    break;

  case 1115:

/* Line 1455 of yacc.c  */
#line 5890 "parser.y"
    {
	cb_emit_string ((yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]));
  ;}
    break;

  case 1116:

/* Line 1455 of yacc.c  */
#line 5896 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1117:

/* Line 1455 of yacc.c  */
#line 5897 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1118:

/* Line 1455 of yacc.c  */
#line 5901 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1119:

/* Line 1455 of yacc.c  */
#line 5902 "parser.y"
    { (yyval) = cb_build_pair (cb_int0, NULL); ;}
    break;

  case 1120:

/* Line 1455 of yacc.c  */
#line 5903 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), NULL); ;}
    break;

  case 1121:

/* Line 1455 of yacc.c  */
#line 5907 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1122:

/* Line 1455 of yacc.c  */
#line 5908 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1123:

/* Line 1455 of yacc.c  */
#line 5912 "parser.y"
    { terminator_warning (TERM_STRING); ;}
    break;

  case 1124:

/* Line 1455 of yacc.c  */
#line 5913 "parser.y"
    { terminator_clear (TERM_STRING); ;}
    break;

  case 1125:

/* Line 1455 of yacc.c  */
#line 5922 "parser.y"
    { BEGIN_STATEMENT ("SUBTRACT", TERM_SUBTRACT); ;}
    break;

  case 1127:

/* Line 1455 of yacc.c  */
#line 5929 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '-', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 1128:

/* Line 1455 of yacc.c  */
#line 5933 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_list (cb_cons ((yyvsp[(3) - (6)]), (yyvsp[(1) - (6)])), '-'));
  ;}
    break;

  case 1129:

/* Line 1455 of yacc.c  */
#line 5937 "parser.y"
    {
	cb_emit_corresponding (cb_build_sub, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 1130:

/* Line 1455 of yacc.c  */
#line 5943 "parser.y"
    { terminator_warning (TERM_SUBTRACT); ;}
    break;

  case 1131:

/* Line 1455 of yacc.c  */
#line 5944 "parser.y"
    { terminator_clear (TERM_SUBTRACT); ;}
    break;

  case 1132:

/* Line 1455 of yacc.c  */
#line 5954 "parser.y"
    {
	BEGIN_STATEMENT ("SUPPRESS", 0);
	PENDING("SUPPRESS");
  ;}
    break;

  case 1135:

/* Line 1455 of yacc.c  */
#line 5969 "parser.y"
    { BEGIN_STATEMENT ("TERMINATE", 0); ;}
    break;

  case 1136:

/* Line 1455 of yacc.c  */
#line 5971 "parser.y"
    {
	PENDING("TERMINATE");
  ;}
    break;

  case 1137:

/* Line 1455 of yacc.c  */
#line 5982 "parser.y"
    { BEGIN_STATEMENT ("TRANSFORM", 0); ;}
    break;

  case 1138:

/* Line 1455 of yacc.c  */
#line 5984 "parser.y"
    {
	cb_tree		x;

	x = cb_build_converting ((yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]), cb_build_inspect_region_start ());
	cb_emit_inspect ((yyvsp[(3) - (7)]), x, cb_int0, 2);
  ;}
    break;

  case 1139:

/* Line 1455 of yacc.c  */
#line 5998 "parser.y"
    { BEGIN_STATEMENT ("UNLOCK", 0); ;}
    break;

  case 1140:

/* Line 1455 of yacc.c  */
#line 6000 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_unlock ((yyvsp[(3) - (4)]));
	}
  ;}
    break;

  case 1144:

/* Line 1455 of yacc.c  */
#line 6019 "parser.y"
    { BEGIN_STATEMENT ("UNSTRING", TERM_UNSTRING); ;}
    break;

  case 1145:

/* Line 1455 of yacc.c  */
#line 6023 "parser.y"
    {
	cb_emit_unstring ((yyvsp[(3) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]));
  ;}
    break;

  case 1146:

/* Line 1455 of yacc.c  */
#line 6029 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1147:

/* Line 1455 of yacc.c  */
#line 6031 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1148:

/* Line 1455 of yacc.c  */
#line 6035 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1149:

/* Line 1455 of yacc.c  */
#line 6037 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1150:

/* Line 1455 of yacc.c  */
#line 6042 "parser.y"
    {
	(yyval) = cb_build_unstring_delimited ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1151:

/* Line 1455 of yacc.c  */
#line 6048 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 1152:

/* Line 1455 of yacc.c  */
#line 6050 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1153:

/* Line 1455 of yacc.c  */
#line 6055 "parser.y"
    {
	(yyval) = cb_build_unstring_into ((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1154:

/* Line 1455 of yacc.c  */
#line 6061 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1155:

/* Line 1455 of yacc.c  */
#line 6062 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1156:

/* Line 1455 of yacc.c  */
#line 6066 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1157:

/* Line 1455 of yacc.c  */
#line 6067 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1158:

/* Line 1455 of yacc.c  */
#line 6071 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1159:

/* Line 1455 of yacc.c  */
#line 6072 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1160:

/* Line 1455 of yacc.c  */
#line 6076 "parser.y"
    { terminator_warning (TERM_UNSTRING); ;}
    break;

  case 1161:

/* Line 1455 of yacc.c  */
#line 6077 "parser.y"
    { terminator_clear (TERM_UNSTRING); ;}
    break;

  case 1165:

/* Line 1455 of yacc.c  */
#line 6095 "parser.y"
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
  ;}
    break;

  case 1166:

/* Line 1455 of yacc.c  */
#line 6116 "parser.y"
    {
	use_global_ind = 0;
  ;}
    break;

  case 1167:

/* Line 1455 of yacc.c  */
#line 6120 "parser.y"
    {
	use_global_ind = 1;
	current_program->flag_global_use = 1;
  ;}
    break;

  case 1168:

/* Line 1455 of yacc.c  */
#line 6128 "parser.y"
    {
	cb_tree		l;

	for (l = (yyvsp[(1) - (1)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			setup_use_file (CB_FILE (cb_ref (CB_VALUE (l))));
		}
	}
  ;}
    break;

  case 1169:

/* Line 1455 of yacc.c  */
#line 6138 "parser.y"
    {
	current_program->global_handler[COB_OPEN_INPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_INPUT].handler_prog = current_program;
  ;}
    break;

  case 1170:

/* Line 1455 of yacc.c  */
#line 6143 "parser.y"
    {
	current_program->global_handler[COB_OPEN_OUTPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_OUTPUT].handler_prog = current_program;
  ;}
    break;

  case 1171:

/* Line 1455 of yacc.c  */
#line 6148 "parser.y"
    {
	current_program->global_handler[COB_OPEN_I_O].handler_label = current_section;
	current_program->global_handler[COB_OPEN_I_O].handler_prog = current_program;
  ;}
    break;

  case 1172:

/* Line 1455 of yacc.c  */
#line 6153 "parser.y"
    {
	current_program->global_handler[COB_OPEN_EXTEND].handler_label = current_section;
	current_program->global_handler[COB_OPEN_EXTEND].handler_prog = current_program;
  ;}
    break;

  case 1185:

/* Line 1455 of yacc.c  */
#line 6185 "parser.y"
    {
	PENDING ("USE FOR DEBUGGING");
  ;}
    break;

  case 1188:

/* Line 1455 of yacc.c  */
#line 6197 "parser.y"
    {
	PENDING ("USE BEFORE REPORTING");
  ;}
    break;

  case 1189:

/* Line 1455 of yacc.c  */
#line 6208 "parser.y"
    { BEGIN_STATEMENT ("WRITE", TERM_WRITE); ;}
    break;

  case 1190:

/* Line 1455 of yacc.c  */
#line 6211 "parser.y"
    {
	if ((yyvsp[(3) - (8)]) != cb_error_node) {
		cb_emit_write ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(5) - (8)]));
	}
  ;}
    break;

  case 1191:

/* Line 1455 of yacc.c  */
#line 6219 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1192:

/* Line 1455 of yacc.c  */
#line 6220 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1193:

/* Line 1455 of yacc.c  */
#line 6225 "parser.y"
    {
	(yyval) = cb_int0;
  ;}
    break;

  case 1194:

/* Line 1455 of yacc.c  */
#line 6229 "parser.y"
    {
	(yyval) = cb_build_write_advancing_lines ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 1195:

/* Line 1455 of yacc.c  */
#line 6233 "parser.y"
    {
	(yyval) = cb_build_write_advancing_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1196:

/* Line 1455 of yacc.c  */
#line 6237 "parser.y"
    {
	(yyval) = cb_build_write_advancing_page ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1197:

/* Line 1455 of yacc.c  */
#line 6243 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1198:

/* Line 1455 of yacc.c  */
#line 6244 "parser.y"
    { (yyval) = CB_AFTER; ;}
    break;

  case 1202:

/* Line 1455 of yacc.c  */
#line 6253 "parser.y"
    { terminator_warning (TERM_WRITE); ;}
    break;

  case 1203:

/* Line 1455 of yacc.c  */
#line 6254 "parser.y"
    { terminator_clear (TERM_WRITE); ;}
    break;

  case 1204:

/* Line 1455 of yacc.c  */
#line 6269 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_ACCEPT;
  ;}
    break;

  case 1205:

/* Line 1455 of yacc.c  */
#line 6277 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_DISPLAY;
  ;}
    break;

  case 1207:

/* Line 1455 of yacc.c  */
#line 6284 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1208:

/* Line 1455 of yacc.c  */
#line 6288 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1210:

/* Line 1455 of yacc.c  */
#line 6295 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1211:

/* Line 1455 of yacc.c  */
#line 6299 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1214:

/* Line 1455 of yacc.c  */
#line 6315 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1215:

/* Line 1455 of yacc.c  */
#line 6320 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1217:

/* Line 1455 of yacc.c  */
#line 6327 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1218:

/* Line 1455 of yacc.c  */
#line 6332 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1219:

/* Line 1455 of yacc.c  */
#line 6344 "parser.y"
    {
	current_statement->handler_id = COB_EC_OVERFLOW;
  ;}
    break;

  case 1221:

/* Line 1455 of yacc.c  */
#line 6351 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1222:

/* Line 1455 of yacc.c  */
#line 6355 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1224:

/* Line 1455 of yacc.c  */
#line 6362 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1225:

/* Line 1455 of yacc.c  */
#line 6366 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1226:

/* Line 1455 of yacc.c  */
#line 6378 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1227:

/* Line 1455 of yacc.c  */
#line 6383 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1228:

/* Line 1455 of yacc.c  */
#line 6388 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1229:

/* Line 1455 of yacc.c  */
#line 6397 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1230:

/* Line 1455 of yacc.c  */
#line 6401 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1231:

/* Line 1455 of yacc.c  */
#line 6408 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1232:

/* Line 1455 of yacc.c  */
#line 6412 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1233:

/* Line 1455 of yacc.c  */
#line 6424 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1234:

/* Line 1455 of yacc.c  */
#line 6429 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1235:

/* Line 1455 of yacc.c  */
#line 6434 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1236:

/* Line 1455 of yacc.c  */
#line 6443 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1237:

/* Line 1455 of yacc.c  */
#line 6447 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1238:

/* Line 1455 of yacc.c  */
#line 6454 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1239:

/* Line 1455 of yacc.c  */
#line 6458 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1242:

/* Line 1455 of yacc.c  */
#line 6474 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1243:

/* Line 1455 of yacc.c  */
#line 6479 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1244:

/* Line 1455 of yacc.c  */
#line 6484 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1245:

/* Line 1455 of yacc.c  */
#line 6493 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1246:

/* Line 1455 of yacc.c  */
#line 6497 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1247:

/* Line 1455 of yacc.c  */
#line 6504 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1248:

/* Line 1455 of yacc.c  */
#line 6508 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1249:

/* Line 1455 of yacc.c  */
#line 6520 "parser.y"
    {
	(yyval) = cb_one;
  ;}
    break;

  case 1250:

/* Line 1455 of yacc.c  */
#line 6524 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 1251:

/* Line 1455 of yacc.c  */
#line 6536 "parser.y"
    {
	(yyval) = cb_build_cond ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1252:

/* Line 1455 of yacc.c  */
#line 6543 "parser.y"
    {
	(yyval) = cb_build_expr ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1253:

/* Line 1455 of yacc.c  */
#line 6549 "parser.y"
    {
	current_expr = NULL;
  ;}
    break;

  case 1254:

/* Line 1455 of yacc.c  */
#line 6553 "parser.y"
    {
	(yyval) = cb_list_reverse (current_expr);
  ;}
    break;

  case 1256:

/* Line 1455 of yacc.c  */
#line 6560 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1257:

/* Line 1455 of yacc.c  */
#line 6561 "parser.y"
    { push_expr (')', NULL); ;}
    break;

  case 1258:

/* Line 1455 of yacc.c  */
#line 6563 "parser.y"
    { push_expr ('O', NULL); ;}
    break;

  case 1259:

/* Line 1455 of yacc.c  */
#line 6564 "parser.y"
    { push_expr ('9', NULL); ;}
    break;

  case 1260:

/* Line 1455 of yacc.c  */
#line 6565 "parser.y"
    { push_expr ('A', NULL); ;}
    break;

  case 1261:

/* Line 1455 of yacc.c  */
#line 6566 "parser.y"
    { push_expr ('L', NULL); ;}
    break;

  case 1262:

/* Line 1455 of yacc.c  */
#line 6567 "parser.y"
    { push_expr ('U', NULL); ;}
    break;

  case 1263:

/* Line 1455 of yacc.c  */
#line 6568 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1264:

/* Line 1455 of yacc.c  */
#line 6570 "parser.y"
    { push_expr ('P', NULL); ;}
    break;

  case 1265:

/* Line 1455 of yacc.c  */
#line 6571 "parser.y"
    { push_expr ('N', NULL); ;}
    break;

  case 1266:

/* Line 1455 of yacc.c  */
#line 6572 "parser.y"
    { push_expr ('x', cb_zero); ;}
    break;

  case 1267:

/* Line 1455 of yacc.c  */
#line 6574 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1270:

/* Line 1455 of yacc.c  */
#line 6580 "parser.y"
    { push_expr ('(', NULL); ;}
    break;

  case 1271:

/* Line 1455 of yacc.c  */
#line 6582 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1272:

/* Line 1455 of yacc.c  */
#line 6583 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1273:

/* Line 1455 of yacc.c  */
#line 6584 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1274:

/* Line 1455 of yacc.c  */
#line 6586 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1275:

/* Line 1455 of yacc.c  */
#line 6588 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1276:

/* Line 1455 of yacc.c  */
#line 6589 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1277:

/* Line 1455 of yacc.c  */
#line 6590 "parser.y"
    { push_expr ('*', NULL); ;}
    break;

  case 1278:

/* Line 1455 of yacc.c  */
#line 6591 "parser.y"
    { push_expr ('/', NULL); ;}
    break;

  case 1279:

/* Line 1455 of yacc.c  */
#line 6592 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1280:

/* Line 1455 of yacc.c  */
#line 6594 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1281:

/* Line 1455 of yacc.c  */
#line 6595 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1282:

/* Line 1455 of yacc.c  */
#line 6596 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1283:

/* Line 1455 of yacc.c  */
#line 6597 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1284:

/* Line 1455 of yacc.c  */
#line 6598 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1285:

/* Line 1455 of yacc.c  */
#line 6599 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1286:

/* Line 1455 of yacc.c  */
#line 6601 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1287:

/* Line 1455 of yacc.c  */
#line 6602 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1288:

/* Line 1455 of yacc.c  */
#line 6603 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1289:

/* Line 1455 of yacc.c  */
#line 6604 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1290:

/* Line 1455 of yacc.c  */
#line 6605 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1291:

/* Line 1455 of yacc.c  */
#line 6606 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1292:

/* Line 1455 of yacc.c  */
#line 6608 "parser.y"
    { push_expr ('&', NULL); ;}
    break;

  case 1293:

/* Line 1455 of yacc.c  */
#line 6609 "parser.y"
    { push_expr ('|', NULL); ;}
    break;

  case 1307:

/* Line 1455 of yacc.c  */
#line 6621 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1308:

/* Line 1455 of yacc.c  */
#line 6622 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1312:

/* Line 1455 of yacc.c  */
#line 6631 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1313:

/* Line 1455 of yacc.c  */
#line 6632 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '+', (yyvsp[(3) - (3)])); ;}
    break;

  case 1314:

/* Line 1455 of yacc.c  */
#line 6633 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '-', (yyvsp[(3) - (3)])); ;}
    break;

  case 1315:

/* Line 1455 of yacc.c  */
#line 6634 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '*', (yyvsp[(3) - (3)])); ;}
    break;

  case 1316:

/* Line 1455 of yacc.c  */
#line 6635 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '/', (yyvsp[(3) - (3)])); ;}
    break;

  case 1317:

/* Line 1455 of yacc.c  */
#line 6636 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1318:

/* Line 1455 of yacc.c  */
#line 6637 "parser.y"
    { (yyval) = cb_build_binary_op (cb_zero, '-', (yyvsp[(2) - (2)])); ;}
    break;

  case 1319:

/* Line 1455 of yacc.c  */
#line 6638 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '^', (yyvsp[(3) - (3)])); ;}
    break;

  case 1320:

/* Line 1455 of yacc.c  */
#line 6639 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1321:

/* Line 1455 of yacc.c  */
#line 6651 "parser.y"
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
  ;}
    break;

  case 1322:

/* Line 1455 of yacc.c  */
#line 6663 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(3) - (3)])))) {
		(yyval) = CB_FILE (cb_ref ((yyvsp[(3) - (3)])))->linage_ctr;
	} else {
		cb_error_x ((yyvsp[(3) - (3)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(3) - (3)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1323:

/* Line 1455 of yacc.c  */
#line 6677 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1324:

/* Line 1455 of yacc.c  */
#line 6679 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1325:

/* Line 1455 of yacc.c  */
#line 6683 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)])); ;}
    break;

  case 1326:

/* Line 1455 of yacc.c  */
#line 6689 "parser.y"
    { cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1327:

/* Line 1455 of yacc.c  */
#line 6696 "parser.y"
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
  ;}
    break;

  case 1328:

/* Line 1455 of yacc.c  */
#line 6716 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1329:

/* Line 1455 of yacc.c  */
#line 6720 "parser.y"
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
  ;}
    break;

  case 1330:

/* Line 1455 of yacc.c  */
#line 6736 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (1)])))) {
		(yyval) = (yyvsp[(1) - (1)]);
	} else {
		cb_error_x ((yyvsp[(1) - (1)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(1) - (1)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1331:

/* Line 1455 of yacc.c  */
#line 6749 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1332:

/* Line 1455 of yacc.c  */
#line 6751 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1333:

/* Line 1455 of yacc.c  */
#line 6755 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1334:

/* Line 1455 of yacc.c  */
#line 6761 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1335:

/* Line 1455 of yacc.c  */
#line 6763 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1336:

/* Line 1455 of yacc.c  */
#line 6768 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	CB_REFERENCE ((yyval))->offset = CB_TREE (current_section);
	current_program->label_list = cb_cons ((yyval), current_program->label_list);
  ;}
    break;

  case 1340:

/* Line 1455 of yacc.c  */
#line 6783 "parser.y"
    {
	(yyval) = cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(1) - (1)]))->data));
	(yyval)->source_file = (yyvsp[(1) - (1)])->source_file;
	(yyval)->source_line = (yyvsp[(1) - (1)])->source_line;
  ;}
    break;

  case 1341:

/* Line 1455 of yacc.c  */
#line 6793 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1342:

/* Line 1455 of yacc.c  */
#line 6794 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1343:

/* Line 1455 of yacc.c  */
#line 6799 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	current_program->reference_list = cb_cons ((yyval), current_program->reference_list);
  ;}
    break;

  case 1344:

/* Line 1455 of yacc.c  */
#line 6806 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1345:

/* Line 1455 of yacc.c  */
#line 6807 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1348:

/* Line 1455 of yacc.c  */
#line 6819 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE ((yyval))->word->count > 0) {
		redefinition_error ((yyval));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1349:

/* Line 1455 of yacc.c  */
#line 6838 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1350:

/* Line 1455 of yacc.c  */
#line 6839 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1352:

/* Line 1455 of yacc.c  */
#line 6844 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1353:

/* Line 1455 of yacc.c  */
#line 6848 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1354:

/* Line 1455 of yacc.c  */
#line 6849 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1356:

/* Line 1455 of yacc.c  */
#line 6854 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1357:

/* Line 1455 of yacc.c  */
#line 6855 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1358:

/* Line 1455 of yacc.c  */
#line 6856 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1359:

/* Line 1455 of yacc.c  */
#line 6857 "parser.y"
    { (yyval) = cb_build_ppointer ((yyvsp[(4) - (4)])); ;}
    break;

  case 1360:

/* Line 1455 of yacc.c  */
#line 6858 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1365:

/* Line 1455 of yacc.c  */
#line 6866 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1366:

/* Line 1455 of yacc.c  */
#line 6867 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1367:

/* Line 1455 of yacc.c  */
#line 6868 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1373:

/* Line 1455 of yacc.c  */
#line 6880 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1374:

/* Line 1455 of yacc.c  */
#line 6881 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1386:

/* Line 1455 of yacc.c  */
#line 6915 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1387:

/* Line 1455 of yacc.c  */
#line 6923 "parser.y"
    { (yyval) = cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1388:

/* Line 1455 of yacc.c  */
#line 6927 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1389:

/* Line 1455 of yacc.c  */
#line 6928 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1390:

/* Line 1455 of yacc.c  */
#line 6929 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1391:

/* Line 1455 of yacc.c  */
#line 6930 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 1392:

/* Line 1455 of yacc.c  */
#line 6934 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1393:

/* Line 1455 of yacc.c  */
#line 6935 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); CB_REFERENCE ((yyvsp[(1) - (3)]))->chain = (yyvsp[(3) - (3)]); ;}
    break;

  case 1394:

/* Line 1455 of yacc.c  */
#line 6940 "parser.y"
    {
	if (cb_ref ((yyvsp[(0) - (3)])) != cb_error_node) {
		(yyval) = (yyvsp[(0) - (3)]);
		CB_REFERENCE ((yyvsp[(0) - (3)]))->subs = cb_list_reverse ((yyvsp[(2) - (3)]));
	}
  ;}
    break;

  case 1395:

/* Line 1455 of yacc.c  */
#line 6950 "parser.y"
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
  ;}
    break;

  case 1396:

/* Line 1455 of yacc.c  */
#line 6968 "parser.y"
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
  ;}
    break;

  case 1397:

/* Line 1455 of yacc.c  */
#line 6995 "parser.y"
    {
	if (cb_tree_category ((yyvsp[(1) - (1)])) != CB_CATEGORY_NUMERIC) {
		cb_error (_("Integer value expected"));
	} else if (CB_LITERAL ((yyvsp[(1) - (1)]))->sign < 0 || CB_LITERAL ((yyvsp[(1) - (1)]))->scale) {
		cb_error (_("Integer value expected"));
	}
	(yyval) = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1398:

/* Line 1455 of yacc.c  */
#line 7006 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1399:

/* Line 1455 of yacc.c  */
#line 7008 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (2)]);
	if (CB_LITERAL_P ((yyvsp[(2) - (2)]))) {
		CB_LITERAL ((yyvsp[(2) - (2)]))->all = 1;
	}
  ;}
    break;

  case 1400:

/* Line 1455 of yacc.c  */
#line 7017 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1401:

/* Line 1455 of yacc.c  */
#line 7018 "parser.y"
    { (yyval) = cb_concat_literals ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1402:

/* Line 1455 of yacc.c  */
#line 7022 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1403:

/* Line 1455 of yacc.c  */
#line 7023 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 1404:

/* Line 1455 of yacc.c  */
#line 7024 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1405:

/* Line 1455 of yacc.c  */
#line 7025 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 1406:

/* Line 1455 of yacc.c  */
#line 7026 "parser.y"
    { (yyval) = cb_high; ;}
    break;

  case 1407:

/* Line 1455 of yacc.c  */
#line 7027 "parser.y"
    { (yyval) = cb_low; ;}
    break;

  case 1408:

/* Line 1455 of yacc.c  */
#line 7028 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1409:

/* Line 1455 of yacc.c  */
#line 7037 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1410:

/* Line 1455 of yacc.c  */
#line 7041 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1411:

/* Line 1455 of yacc.c  */
#line 7045 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1412:

/* Line 1455 of yacc.c  */
#line 7049 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1413:

/* Line 1455 of yacc.c  */
#line 7053 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1414:

/* Line 1455 of yacc.c  */
#line 7057 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1415:

/* Line 1455 of yacc.c  */
#line 7061 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1416:

/* Line 1455 of yacc.c  */
#line 7065 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1417:

/* Line 1455 of yacc.c  */
#line 7069 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1418:

/* Line 1455 of yacc.c  */
#line 7073 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), NULL);
  ;}
    break;

  case 1419:

/* Line 1455 of yacc.c  */
#line 7077 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1420:

/* Line 1455 of yacc.c  */
#line 7081 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), NULL);
  ;}
    break;

  case 1421:

/* Line 1455 of yacc.c  */
#line 7087 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1422:

/* Line 1455 of yacc.c  */
#line 7088 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (4)]), NULL); ;}
    break;

  case 1423:

/* Line 1455 of yacc.c  */
#line 7089 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 1424:

/* Line 1455 of yacc.c  */
#line 7093 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1425:

/* Line 1455 of yacc.c  */
#line 7094 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1426:

/* Line 1455 of yacc.c  */
#line 7098 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1427:

/* Line 1455 of yacc.c  */
#line 7099 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1428:

/* Line 1455 of yacc.c  */
#line 7105 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_int0);
  ;}
    break;

  case 1429:

/* Line 1455 of yacc.c  */
#line 7112 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int1);
  ;}
    break;

  case 1430:

/* Line 1455 of yacc.c  */
#line 7119 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int2);
  ;}
    break;

  case 1431:

/* Line 1455 of yacc.c  */
#line 7129 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1432:

/* Line 1455 of yacc.c  */
#line 7136 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1433:

/* Line 1455 of yacc.c  */
#line 7146 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1434:

/* Line 1455 of yacc.c  */
#line 7153 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_ref ((yyvsp[(3) - (3)])));
  ;}
    break;

  case 1435:

/* Line 1455 of yacc.c  */
#line 7166 "parser.y"
    {
	non_const_word = 1;
  ;}
    break;

  case 1436:

/* Line 1455 of yacc.c  */
#line 7176 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1437:

/* Line 1455 of yacc.c  */
#line 7177 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1438:

/* Line 1455 of yacc.c  */
#line 7181 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1439:

/* Line 1455 of yacc.c  */
#line 7182 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1440:

/* Line 1455 of yacc.c  */
#line 7186 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1441:

/* Line 1455 of yacc.c  */
#line 7187 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1442:

/* Line 1455 of yacc.c  */
#line 7191 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1443:

/* Line 1455 of yacc.c  */
#line 7192 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1444:

/* Line 1455 of yacc.c  */
#line 7193 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 1445:

/* Line 1455 of yacc.c  */
#line 7197 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1446:

/* Line 1455 of yacc.c  */
#line 7198 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1447:

/* Line 1455 of yacc.c  */
#line 7202 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1448:

/* Line 1455 of yacc.c  */
#line 7203 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1449:

/* Line 1455 of yacc.c  */
#line 7207 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1450:

/* Line 1455 of yacc.c  */
#line 7208 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1451:

/* Line 1455 of yacc.c  */
#line 7212 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1452:

/* Line 1455 of yacc.c  */
#line 7213 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1464:

/* Line 1455 of yacc.c  */
#line 7226 "parser.y"
    { (yyval) = cb_int1; ;}
    break;



/* Line 1455 of yacc.c  */
#line 14442 "parser.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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



/* Line 1675 of yacc.c  */
#line 7270 "parser.y"


