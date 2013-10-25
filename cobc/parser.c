
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
static struct cb_key_component 	*key_component_list;

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
		cb_warning (_("Unreachable statement"));
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
#line 357 "parser.c"

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
     ARE = 277,
     AREA = 278,
     ARGUMENT_NUMBER = 279,
     ARGUMENT_VALUE = 280,
     AS = 281,
     ASCENDING = 282,
     ASSIGN = 283,
     AT = 284,
     AUTO = 285,
     AUTOMATIC = 286,
     BACKGROUND_COLOR = 287,
     BASED = 288,
     BEFORE = 289,
     BELL = 290,
     BINARY = 291,
     BINARY_C_LONG = 292,
     BINARY_CHAR = 293,
     BINARY_DOUBLE = 294,
     BINARY_LONG = 295,
     BINARY_SHORT = 296,
     BLANK = 297,
     BLANK_LINE = 298,
     BLANK_SCREEN = 299,
     BLINK = 300,
     BLOCK = 301,
     BOTTOM = 302,
     BY = 303,
     BYTE_LENGTH = 304,
     CALL = 305,
     CANCEL = 306,
     CH = 307,
     CHAINING = 308,
     CHARACTER = 309,
     CHARACTERS = 310,
     CLASS = 311,
     CLASS_NAME = 312,
     CLOSE = 313,
     CODE = 314,
     CODE_SET = 315,
     COLLATING = 316,
     COL = 317,
     COLS = 318,
     COLUMN = 319,
     COLUMNS = 320,
     COMMA = 321,
     COMMAND_LINE = 322,
     COMMA_DELIM = 323,
     COMMIT = 324,
     COMMON = 325,
     COMP = 326,
     COMPUTE = 327,
     COMP_1 = 328,
     COMP_2 = 329,
     COMP_3 = 330,
     COMP_4 = 331,
     COMP_5 = 332,
     COMP_X = 333,
     CONCATENATE_FUNC = 334,
     CONFIGURATION = 335,
     CONSTANT = 336,
     CONTAINS = 337,
     CONTENT = 338,
     CONTINUE = 339,
     CONTROL = 340,
     CONTROLS = 341,
     CONTROL_FOOTING = 342,
     CONTROL_HEADING = 343,
     CONVERTING = 344,
     CORRESPONDING = 345,
     COUNT = 346,
     CRT = 347,
     CURRENCY = 348,
     CURRENT_DATE_FUNC = 349,
     CURSOR = 350,
     CYCLE = 351,
     DATA = 352,
     DATE = 353,
     DAY = 354,
     DAY_OF_WEEK = 355,
     DE = 356,
     DEBUGGING = 357,
     DECIMAL_POINT = 358,
     DECLARATIVES = 359,
     DEFAULT = 360,
     DELETE = 361,
     DELIMITED = 362,
     DELIMITER = 363,
     DEPENDING = 364,
     DESCENDING = 365,
     DETAIL = 366,
     DISK = 367,
     DISPLAY = 368,
     DIVIDE = 369,
     DIVISION = 370,
     DOWN = 371,
     DUPLICATES = 372,
     DYNAMIC = 373,
     EBCDIC = 374,
     ELSE = 375,
     END = 376,
     END_ACCEPT = 377,
     END_ADD = 378,
     END_CALL = 379,
     END_COMPUTE = 380,
     END_DELETE = 381,
     END_DISPLAY = 382,
     END_DIVIDE = 383,
     END_EVALUATE = 384,
     END_FUNCTION = 385,
     END_IF = 386,
     END_MULTIPLY = 387,
     END_PERFORM = 388,
     END_PROGRAM = 389,
     END_READ = 390,
     END_RETURN = 391,
     END_REWRITE = 392,
     END_SEARCH = 393,
     END_START = 394,
     END_STRING = 395,
     END_SUBTRACT = 396,
     END_UNSTRING = 397,
     END_WRITE = 398,
     ENTRY = 399,
     ENVIRONMENT = 400,
     ENVIRONMENT_NAME = 401,
     ENVIRONMENT_VALUE = 402,
     EOL = 403,
     EOP = 404,
     EOS = 405,
     EQUAL = 406,
     EQUALS = 407,
     ERASE = 408,
     ERROR = 409,
     ESCAPE = 410,
     EVALUATE = 411,
     EVENT_STATUS = 412,
     EXCEPTION = 413,
     EXCLUSIVE = 414,
     EXIT = 415,
     EXTEND = 416,
     EXTERNAL = 417,
     FD = 418,
     FILE_CONTROL = 419,
     FILE_ID = 420,
     FILLER = 421,
     FINAL = 422,
     FIRST = 423,
     FOOTING = 424,
     FOR = 425,
     FOREGROUND_COLOR = 426,
     FOREVER = 427,
     FREE = 428,
     FROM = 429,
     FULL = 430,
     FUNCTION = 431,
     FUNCTION_ID = 432,
     FUNCTION_NAME = 433,
     GE = 434,
     GENERATE = 435,
     GIVING = 436,
     GLOBAL = 437,
     GO = 438,
     GOBACK = 439,
     GREATER = 440,
     GROUP = 441,
     HEADING = 442,
     HIGHLIGHT = 443,
     HIGH_VALUE = 444,
     IDENTIFICATION = 445,
     IF = 446,
     IGNORE = 447,
     IGNORING = 448,
     IN = 449,
     INDEX = 450,
     INDEXED = 451,
     INDICATE = 452,
     INITIALIZE = 453,
     INITIALIZED = 454,
     INITIATE = 455,
     INPUT = 456,
     INPUT_OUTPUT = 457,
     INSPECT = 458,
     INTO = 459,
     INTRINSIC = 460,
     INVALID = 461,
     INVALID_KEY = 462,
     IS = 463,
     I_O = 464,
     I_O_CONTROL = 465,
     JUSTIFIED = 466,
     KEY = 467,
     LABEL = 468,
     LAST = 469,
     LAST_DETAIL = 470,
     LE = 471,
     LEADING = 472,
     LEFT = 473,
     LENGTH = 474,
     LESS = 475,
     LIMIT = 476,
     LIMITS = 477,
     LINAGE = 478,
     LINAGE_COUNTER = 479,
     LINE = 480,
     LINES = 481,
     LINKAGE = 482,
     LITERAL = 483,
     LOCALE = 484,
     LOCALE_DT_FUNC = 485,
     LOCAL_STORAGE = 486,
     LOCK = 487,
     LOWER_CASE_FUNC = 488,
     LOWLIGHT = 489,
     LOW_VALUE = 490,
     MANUAL = 491,
     MEMORY = 492,
     MERGE = 493,
     MINUS = 494,
     MNEMONIC_NAME = 495,
     MODE = 496,
     MOVE = 497,
     MULTIPLE = 498,
     MULTIPLY = 499,
     NATIONAL = 500,
     NATIONAL_EDITED = 501,
     NATIVE = 502,
     NE = 503,
     NEGATIVE = 504,
     NEXT = 505,
     NEXT_SENTENCE = 506,
     NO = 507,
     NOT = 508,
     NOT_END = 509,
     NOT_EOP = 510,
     NOT_EXCEPTION = 511,
     NOT_INVALID_KEY = 512,
     NOT_OVERFLOW = 513,
     NOT_SIZE_ERROR = 514,
     NO_ADVANCING = 515,
     NUMBER = 516,
     NUMBERS = 517,
     NUMERIC = 518,
     NUMERIC_EDITED = 519,
     NUMVALC_FUNC = 520,
     OBJECT_COMPUTER = 521,
     OCCURS = 522,
     OF = 523,
     OFF = 524,
     OMITTED = 525,
     ON = 526,
     ONLY = 527,
     OPEN = 528,
     OPTIONAL = 529,
     OR = 530,
     ORDER = 531,
     ORGANIZATION = 532,
     OTHER = 533,
     OUTPUT = 534,
     OVERFLOW = 535,
     OVERLINE = 536,
     PACKED_DECIMAL = 537,
     PADDING = 538,
     PAGE = 539,
     PAGE_FOOTING = 540,
     PAGE_HEADING = 541,
     PARAGRAPH = 542,
     PERFORM = 543,
     PICTURE = 544,
     PLUS = 545,
     POINTER = 546,
     POSITION = 547,
     POSITIVE = 548,
     PRESENT = 549,
     PREVIOUS = 550,
     PRINTER = 551,
     PRINTING = 552,
     PROCEDURE = 553,
     PROCEDURES = 554,
     PROCEED = 555,
     PROGRAM = 556,
     PROGRAM_ID = 557,
     PROGRAM_NAME = 558,
     PROGRAM_POINTER = 559,
     PROMPT = 560,
     QUOTE = 561,
     RANDOM = 562,
     RD = 563,
     READ = 564,
     RECORD = 565,
     RECORDING = 566,
     RECORDS = 567,
     RECURSIVE = 568,
     REDEFINES = 569,
     REEL = 570,
     REFERENCE = 571,
     RELATIVE = 572,
     RELEASE = 573,
     REMAINDER = 574,
     REMOVAL = 575,
     RENAMES = 576,
     REPLACING = 577,
     REPORT = 578,
     REPORTING = 579,
     REPORTS = 580,
     REPORT_FOOTING = 581,
     REPORT_HEADING = 582,
     REPOSITORY = 583,
     REQUIRED = 584,
     RESERVE = 585,
     RETURN = 586,
     RETURNING = 587,
     REVERSE_FUNC = 588,
     REVERSE_VIDEO = 589,
     REWIND = 590,
     REWRITE = 591,
     RIGHT = 592,
     ROLLBACK = 593,
     ROUNDED = 594,
     RUN = 595,
     SAME = 596,
     SCREEN = 597,
     SCREEN_CONTROL = 598,
     SCROLL = 599,
     SD = 600,
     SEARCH = 601,
     SECTION = 602,
     SECURE = 603,
     SEGMENT_LIMIT = 604,
     SELECT = 605,
     SEMI_COLON = 606,
     SENTENCE = 607,
     SEPARATE = 608,
     SEQUENCE = 609,
     SEQUENTIAL = 610,
     SET = 611,
     SHARING = 612,
     SIGN = 613,
     SIGNED = 614,
     SIGNED_INT = 615,
     SIGNED_LONG = 616,
     SIGNED_SHORT = 617,
     SIZE = 618,
     SIZE_ERROR = 619,
     SORT = 620,
     SORT_MERGE = 621,
     SOURCE = 622,
     SOURCE_COMPUTER = 623,
     SPACE = 624,
     SPECIAL_NAMES = 625,
     STANDARD = 626,
     STANDARD_1 = 627,
     STANDARD_2 = 628,
     START = 629,
     STATUS = 630,
     STOP = 631,
     STRING = 632,
     SUBSTITUTE_FUNC = 633,
     SUBSTITUTE_CASE_FUNC = 634,
     SUBTRACT = 635,
     SUM = 636,
     SUPPRESS = 637,
     SYMBOLIC = 638,
     SYNCHRONIZED = 639,
     TALLYING = 640,
     TAPE = 641,
     TERMINATE = 642,
     TEST = 643,
     THAN = 644,
     THEN = 645,
     THRU = 646,
     TIME = 647,
     TIMES = 648,
     TO = 649,
     TOK_FALSE = 650,
     TOK_FILE = 651,
     TOK_INITIAL = 652,
     TOK_NULL = 653,
     TOK_TRUE = 654,
     TOP = 655,
     TRAILING = 656,
     TRANSFORM = 657,
     TRIM_FUNCTION = 658,
     TYPE = 659,
     UNDERLINE = 660,
     UNIT = 661,
     UNLOCK = 662,
     UNSIGNED = 663,
     UNSIGNED_INT = 664,
     UNSIGNED_LONG = 665,
     UNSIGNED_SHORT = 666,
     UNSTRING = 667,
     UNTIL = 668,
     UP = 669,
     UPDATE = 670,
     UPON = 671,
     UPON_ARGUMENT_NUMBER = 672,
     UPON_COMMAND_LINE = 673,
     UPON_ENVIRONMENT_NAME = 674,
     UPON_ENVIRONMENT_VALUE = 675,
     UPPER_CASE_FUNC = 676,
     USAGE = 677,
     USE = 678,
     USING = 679,
     VALUE = 680,
     VARYING = 681,
     WAIT = 682,
     WHEN = 683,
     WHEN_COMPILED_FUNC = 684,
     WHEN_OTHER = 685,
     WITH = 686,
     WORD = 687,
     WORDS = 688,
     WORKING_STORAGE = 689,
     WRITE = 690,
     YYYYDDD = 691,
     YYYYMMDD = 692,
     ZERO = 693,
     UNARY_SIGN = 694
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
#line 839 "parser.c"

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
#define YYLAST   5206

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  453
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  692
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1539
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2268

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   694

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   452,     2,
     448,   447,   441,   439,     2,   440,   445,   442,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   451,     2,
     450,   446,   449,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   444,     2,     2,     2,     2,     2,
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
     435,   436,   437,   438,   443
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
     618,   620,   624,   626,   629,   634,   639,   644,   649,   653,
     657,   660,   663,   666,   667,   671,   672,   675,   677,   680,
     682,   684,   690,   691,   693,   695,   697,   703,   705,   708,
     711,   712,   715,   716,   726,   727,   728,   734,   735,   739,
     740,   743,   747,   750,   753,   755,   757,   758,   763,   764,
     767,   770,   773,   775,   777,   779,   781,   783,   785,   787,
     789,   791,   797,   798,   800,   802,   807,   814,   824,   825,
     829,   830,   833,   834,   837,   841,   843,   845,   851,   857,
     859,   861,   865,   871,   872,   875,   877,   879,   881,   887,
     892,   896,   901,   905,   909,   913,   914,   915,   921,   922,
     924,   925,   928,   932,   937,   940,   942,   943,   948,   950,
     951,   953,   955,   957,   958,   961,   963,   967,   971,   978,
     979,   982,   984,   986,   988,   990,   992,   994,   996,   998,
    1000,  1002,  1004,  1006,  1008,  1010,  1013,  1017,  1018,  1021,
    1024,  1026,  1028,  1032,  1034,  1036,  1038,  1040,  1042,  1044,
    1046,  1048,  1050,  1052,  1054,  1056,  1058,  1060,  1062,  1064,
    1066,  1068,  1070,  1073,  1076,  1078,  1081,  1084,  1086,  1089,
    1092,  1094,  1097,  1100,  1102,  1105,  1108,  1110,  1112,  1116,
    1120,  1128,  1129,  1132,  1133,  1137,  1139,  1140,  1146,  1148,
    1150,  1151,  1155,  1157,  1160,  1162,  1165,  1168,  1169,  1171,
    1173,  1177,  1179,  1180,  1189,  1191,  1194,  1196,  1200,  1201,
    1205,  1208,  1213,  1216,  1217,  1218,  1224,  1225,  1226,  1232,
    1233,  1234,  1240,  1241,  1243,  1245,  1248,  1254,  1255,  1258,
    1261,  1265,  1267,  1269,  1272,  1275,  1278,  1279,  1281,  1283,
    1286,  1295,  1296,  1300,  1301,  1306,  1307,  1312,  1313,  1317,
    1318,  1322,  1324,  1329,  1332,  1334,  1336,  1337,  1340,  1345,
    1346,  1349,  1351,  1353,  1355,  1357,  1359,  1361,  1363,  1365,
    1367,  1369,  1371,  1373,  1375,  1377,  1379,  1381,  1385,  1387,
    1389,  1391,  1393,  1395,  1397,  1399,  1404,  1409,  1412,  1414,
    1416,  1419,  1423,  1425,  1429,  1436,  1439,  1443,  1446,  1448,
    1451,  1454,  1456,  1459,  1460,  1462,  1464,  1469,  1472,  1473,
    1475,  1477,  1478,  1479,  1480,  1487,  1488,  1490,  1492,  1495,
    1497,  1498,  1504,  1505,  1508,  1510,  1512,  1514,  1516,  1519,
    1522,  1524,  1526,  1528,  1530,  1532,  1534,  1536,  1538,  1540,
    1542,  1548,  1554,  1558,  1562,  1564,  1566,  1568,  1570,  1572,
    1574,  1576,  1579,  1582,  1585,  1586,  1588,  1590,  1592,  1594,
    1595,  1597,  1599,  1601,  1603,  1607,  1608,  1609,  1610,  1620,
    1621,  1622,  1626,  1627,  1631,  1633,  1636,  1641,  1642,  1645,
    1648,  1649,  1653,  1657,  1662,  1666,  1667,  1669,  1670,  1673,
    1674,  1675,  1683,  1684,  1687,  1689,  1691,  1693,  1696,  1699,
    1704,  1707,  1709,  1711,  1712,  1714,  1715,  1716,  1720,  1721,
    1724,  1726,  1728,  1730,  1732,  1734,  1736,  1738,  1740,  1742,
    1744,  1746,  1748,  1750,  1752,  1754,  1756,  1758,  1760,  1762,
    1764,  1766,  1768,  1770,  1772,  1774,  1776,  1778,  1780,  1782,
    1784,  1786,  1788,  1790,  1792,  1794,  1796,  1798,  1800,  1802,
    1804,  1806,  1808,  1810,  1812,  1814,  1816,  1818,  1820,  1822,
    1823,  1828,  1833,  1838,  1842,  1846,  1850,  1855,  1859,  1864,
    1868,  1872,  1876,  1881,  1887,  1891,  1896,  1900,  1904,  1905,
    1909,  1913,  1916,  1919,  1922,  1926,  1930,  1934,  1935,  1938,
    1940,  1943,  1945,  1947,  1949,  1951,  1953,  1955,  1957,  1961,
    1965,  1969,  1973,  1975,  1977,  1979,  1981,  1983,  1985,  1986,
    1988,  1989,  1994,  1999,  2005,  2012,  2013,  2016,  2017,  2019,
    2020,  2024,  2028,  2034,  2035,  2038,  2041,  2042,  2048,  2049,
    2052,  2053,  2062,  2063,  2064,  2068,  2070,  2073,  2076,  2080,
    2081,  2084,  2087,  2090,  2091,  2094,  2097,  2098,  2099,  2103,
    2104,  2105,  2109,  2110,  2112,  2113,  2117,  2118,  2121,  2122,
    2126,  2127,  2131,  2132,  2134,  2138,  2142,  2145,  2147,  2149,
    2150,  2155,  2160,  2161,  2163,  2165,  2167,  2169,  2171,  2172,
    2179,  2180,  2182,  2183,  2188,  2192,  2196,  2200,  2204,  2209,
    2216,  2223,  2230,  2237,  2238,  2241,  2244,  2246,  2249,  2251,
    2253,  2256,  2259,  2261,  2263,  2265,  2267,  2269,  2273,  2277,
    2281,  2285,  2287,  2289,  2290,  2292,  2293,  2298,  2303,  2310,
    2317,  2326,  2335,  2336,  2338,  2339,  2344,  2345,  2351,  2353,
    2357,  2359,  2361,  2363,  2366,  2368,  2371,  2372,  2376,  2377,
    2378,  2382,  2385,  2389,  2391,  2395,  2398,  2400,  2402,  2404,
    2405,  2408,  2409,  2411,  2412,  2416,  2417,  2419,  2421,  2424,
    2426,  2428,  2429,  2433,  2434,  2438,  2439,  2445,  2446,  2450,
    2451,  2454,  2455,  2456,  2465,  2469,  2470,  2471,  2475,  2476,
    2478,  2479,  2487,  2488,  2491,  2492,  2496,  2500,  2501,  2504,
    2506,  2509,  2514,  2516,  2518,  2520,  2522,  2524,  2526,  2528,
    2529,  2531,  2532,  2536,  2537,  2542,  2544,  2546,  2548,  2550,
    2553,  2555,  2557,  2559,  2560,  2564,  2566,  2569,  2572,  2575,
    2577,  2579,  2581,  2584,  2587,  2589,  2592,  2597,  2600,  2601,
    2603,  2605,  2607,  2609,  2614,  2620,  2621,  2626,  2627,  2629,
    2630,  2634,  2635,  2639,  2643,  2648,  2649,  2654,  2659,  2666,
    2667,  2669,  2670,  2674,  2675,  2681,  2683,  2685,  2687,  2689,
    2690,  2694,  2695,  2699,  2702,  2703,  2707,  2710,  2711,  2716,
    2719,  2720,  2722,  2724,  2728,  2729,  2731,  2734,  2738,  2742,
    2743,  2747,  2749,  2753,  2761,  2762,  2773,  2774,  2777,  2778,
    2781,  2784,  2788,  2792,  2795,  2796,  2800,  2801,  2803,  2805,
    2806,  2808,  2809,  2814,  2815,  2823,  2824,  2826,  2827,  2835,
    2836,  2839,  2843,  2844,  2846,  2848,  2849,  2854,  2859,  2860,
    2868,  2869,  2872,  2873,  2874,  2879,  2881,  2884,  2885,  2890,
    2891,  2893,  2894,  2898,  2900,  2902,  2904,  2906,  2908,  2913,
    2918,  2922,  2927,  2929,  2931,  2933,  2936,  2940,  2942,  2945,
    2949,  2953,  2954,  2958,  2959,  2967,  2968,  2974,  2975,  2978,
    2979,  2982,  2983,  2987,  2988,  2991,  2996,  2997,  3000,  3005,
    3006,  3007,  3015,  3016,  3021,  3024,  3027,  3030,  3033,  3036,
    3037,  3039,  3040,  3045,  3048,  3049,  3052,  3055,  3056,  3065,
    3067,  3070,  3072,  3076,  3080,  3081,  3085,  3086,  3088,  3089,
    3094,  3099,  3106,  3113,  3114,  3116,  3119,  3120,  3122,  3123,
    3127,  3128,  3136,  3137,  3142,  3143,  3145,  3147,  3148,  3158,
    3159,  3163,  3165,  3169,  3172,  3175,  3178,  3182,  3183,  3187,
    3188,  3192,  3193,  3197,  3198,  3200,  3202,  3204,  3206,  3215,
    3216,  3218,  3220,  3222,  3224,  3226,  3228,  3229,  3231,  3232,
    3234,  3236,  3238,  3240,  3242,  3244,  3246,  3247,  3249,  3255,
    3257,  3260,  3266,  3267,  3276,  3277,  3280,  3281,  3286,  3290,
    3294,  3296,  3298,  3299,  3301,  3303,  3304,  3306,  3309,  3312,
    3313,  3314,  3318,  3319,  3320,  3324,  3327,  3328,  3329,  3333,
    3334,  3335,  3339,  3342,  3343,  3344,  3348,  3349,  3350,  3354,
    3356,  3358,  3361,  3362,  3366,  3367,  3371,  3373,  3375,  3378,
    3379,  3383,  3384,  3388,  3389,  3391,  3393,  3395,  3398,  3399,
    3403,  3404,  3408,  3409,  3413,  3415,  3417,  3418,  3421,  3424,
    3427,  3430,  3433,  3436,  3439,  3442,  3445,  3448,  3451,  3454,
    3457,  3460,  3461,  3464,  3467,  3470,  3473,  3476,  3479,  3482,
    3485,  3488,  3491,  3494,  3497,  3500,  3503,  3506,  3509,  3512,
    3515,  3518,  3521,  3524,  3527,  3530,  3533,  3536,  3538,  3541,
    3543,  3545,  3548,  3550,  3553,  3555,  3561,  3563,  3569,  3571,
    3575,  3576,  3578,  3580,  3582,  3586,  3590,  3594,  3598,  3601,
    3604,  3608,  3612,  3614,  3618,  3620,  3623,  3626,  3628,  3630,
    3632,  3635,  3637,  3639,  3642,  3644,  3645,  3648,  3650,  3652,
    3654,  3658,  3660,  3662,  3665,  3667,  3668,  3670,  3672,  3674,
    3676,  3678,  3681,  3683,  3687,  3689,  3692,  3694,  3698,  3702,
    3706,  3711,  3715,  3717,  3719,  3721,  3723,  3727,  3731,  3735,
    3737,  3739,  3741,  3743,  3745,  3747,  3749,  3751,  3753,  3755,
    3757,  3759,  3761,  3763,  3765,  3767,  3769,  3771,  3773,  3775,
    3777,  3780,  3783,  3787,  3789,  3793,  3797,  3802,  3808,  3810,
    3812,  3815,  3817,  3821,  3823,  3825,  3827,  3829,  3831,  3833,
    3835,  3838,  3841,  3847,  3853,  3859,  3865,  3871,  3877,  3883,
    3888,  3894,  3897,  3898,  3903,  3909,  3910,  3914,  3915,  3917,
    3919,  3923,  3927,  3929,  3933,  3935,  3939,  3940,  3941,  3943,
    3944,  3946,  3947,  3949,  3950,  3952,  3954,  3955,  3957,  3958,
    3960,  3961,  3963,  3964,  3967,  3969,  3971,  3974,  3977,  3980,
    3982,  3985,  3987,  3988,  3990,  3991,  3993,  3994,  3996,  3997,
    3999,  4000,  4002,  4003,  4005,  4006,  4008,  4009,  4011,  4012,
    4014,  4015,  4017,  4018,  4020,  4021,  4023,  4024,  4026,  4027,
    4029,  4030,  4032,  4033,  4035,  4036,  4038,  4039,  4041,  4043,
    4044,  4046,  4047,  4049,  4051,  4052,  4054,  4055,  4057,  4058,
    4060,  4061,  4063,  4064,  4066,  4067,  4069,  4072,  4073,  4075,
    4076,  4078,  4079,  4081,  4082,  4084,  4085,  4087,  4088,  4090,
    4091,  4093,  4096,  4097,  4099,  4100,  4102,  4103,  4105,  4106,
    4108,  4109,  4111,  4112,  4114,  4115,  4117,  4118,  4120,  4121
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     454,     0,    -1,    -1,   455,   456,    -1,   457,    -1,   456,
     457,    -1,   458,    -1,   464,    -1,    -1,    -1,   471,   479,
     459,   577,   460,   711,   467,   468,    -1,    -1,    -1,   471,
     479,   462,   577,   463,   711,   467,   469,    -1,    -1,    -1,
     473,   479,   465,   577,   466,   711,   470,    -1,    -1,   461,
      -1,   467,   461,    -1,    -1,   134,   474,   445,    -1,   134,
     474,   445,    -1,   130,   474,   445,    -1,    -1,   302,   445,
     474,   475,   472,   476,   445,    -1,   177,   445,   474,   475,
     445,    -1,   303,    -1,   228,    -1,    -1,    26,   228,    -1,
      -1,  1119,   477,  1130,    -1,    70,    -1,    70,   478,    -1,
     478,    -1,   397,    -1,   313,    -1,    -1,   145,   115,   445,
     480,   531,    -1,    -1,    80,   347,   445,   481,    -1,    -1,
     481,   482,    -1,   483,    -1,   487,    -1,   500,    -1,   495,
      -1,   368,   445,   484,    -1,    -1,   486,   445,    -1,   486,
     485,   445,    -1,   485,   445,    -1,  1144,   102,   241,    -1,
     432,    -1,   266,   445,   488,    -1,    -1,   486,   445,    -1,
     486,   489,   445,    -1,   489,   445,    -1,   490,    -1,   489,
     490,    -1,   491,    -1,   493,    -1,   494,    -1,   237,   363,
    1119,  1079,   492,    -1,    55,    -1,   433,    -1,  1130,  1102,
    1119,  1058,    -1,   349,  1119,  1079,    -1,   328,   445,   496,
      -1,    -1,   497,   445,    -1,   498,    -1,   497,   498,    -1,
     176,   499,   205,    -1,   176,     9,   205,    -1,   228,    -1,
     499,   228,    -1,   370,   445,   501,    -1,    -1,   502,   445,
      -1,   503,    -1,   502,   503,    -1,   504,    -1,   508,    -1,
     517,    -1,   524,    -1,   521,    -1,   525,    -1,   526,    -1,
     527,    -1,   528,    -1,   529,    -1,   530,    -1,   432,  1119,
      92,    -1,    -1,   432,  1119,  1061,   505,   506,    -1,    24,
    1119,  1061,    -1,    25,  1119,  1061,    -1,   146,  1119,  1061,
      -1,   147,  1119,  1061,    -1,    -1,   506,   507,  1137,  1119,
    1061,    -1,   271,    -1,   269,    -1,    -1,    11,  1061,   509,
    1119,   510,    -1,   247,    -1,   372,    -1,   373,    -1,   119,
      -1,   511,    -1,   512,    -1,   511,   512,    -1,   515,    -1,
     515,   391,   515,    -1,    -1,   515,    17,   513,   514,    -1,
     516,    -1,   514,    17,   516,    -1,   228,    -1,   369,    -1,
     438,    -1,   306,    -1,   189,    -1,   235,    -1,   228,    -1,
     369,    -1,   438,    -1,   306,    -1,   189,    -1,   235,    -1,
     383,  1112,   518,    -1,   519,  1120,   520,    -1,  1061,    -1,
     519,  1061,    -1,  1079,    -1,   520,  1079,    -1,    56,  1061,
    1119,   522,    -1,   523,    -1,   522,   523,    -1,  1082,    -1,
    1082,   391,  1082,    -1,   229,  1061,  1119,  1058,    -1,    93,
    1134,  1119,   228,    -1,   103,  1119,    66,    -1,    95,  1119,
    1058,    -1,    92,   375,  1119,  1058,    -1,   343,  1119,  1058,
      -1,   157,  1119,  1058,    -1,    -1,   202,   347,   445,   534,
     567,    -1,    -1,   164,   445,   532,   535,    -1,    -1,   210,
     445,   533,   568,    -1,    -1,   164,   445,   535,    -1,    -1,
     535,   536,    -1,    -1,   350,  1096,  1061,   537,   538,   445,
      -1,    -1,   538,   539,    -1,   540,    -1,   544,    -1,   546,
      -1,   551,    -1,   552,    -1,   554,    -1,   558,    -1,   560,
      -1,   561,    -1,   562,    -1,   563,    -1,   564,    -1,   565,
      -1,    28,  1142,   542,   541,   543,    -1,    28,  1142,   542,
     112,    -1,    28,  1142,   542,   296,    -1,    -1,   112,    -1,
     296,    -1,    -1,   162,    -1,   118,    -1,   228,    -1,   113,
      -1,  1076,    -1,     4,  1124,  1119,   545,    -1,   355,    -1,
     118,    -1,   307,    -1,    19,   310,  1121,  1119,  1058,  1092,
      -1,    19,   310,  1121,  1119,  1058,   550,   547,  1092,    -1,
      -1,   548,   549,    -1,   547,   549,    -1,  1058,    -1,    -1,
     367,  1119,    -1,   446,    -1,  1102,  1119,   432,    -1,   553,
     375,  1119,  1058,  1059,    -1,    -1,   396,    -1,   365,    -1,
     232,  1124,  1119,   555,    -1,   236,   556,    -1,    31,   556,
      -1,   159,    -1,    -1,   431,   232,   271,   557,    -1,   431,
     232,   271,   243,   557,    -1,   431,   338,    -1,   310,    -1,
     312,    -1,   277,  1119,   559,    -1,   559,    -1,   196,    -1,
    1131,  1109,   355,    -1,   317,    -1,   225,   355,    -1,   283,
    1111,  1119,  1060,    -1,   310,   108,  1119,   372,    -1,   310,
    1121,  1119,  1058,    -1,   317,  1121,  1119,  1058,    -1,   330,
    1079,  1106,    -1,   357,  1144,   566,    -1,     9,  1129,    -1,
     252,  1129,    -1,   309,   272,    -1,    -1,   210,   445,   568,
      -1,    -1,   569,   445,    -1,   570,    -1,   569,   570,    -1,
     571,    -1,   573,    -1,   341,   572,  1106,  1116,  1049,    -1,
      -1,   310,    -1,   365,    -1,   366,    -1,   243,  1115,  1138,
    1113,   574,    -1,   575,    -1,   574,   575,    -1,  1050,   576,
      -1,    -1,   292,  1079,    -1,    -1,    97,   115,   445,   578,
     609,   654,   656,   658,   699,    -1,    -1,    -1,   396,   347,
     445,   579,   581,    -1,    -1,   584,   580,   583,    -1,    -1,
     581,   582,    -1,   584,   585,   611,    -1,   585,   611,    -1,
     583,   582,    -1,   163,    -1,   345,    -1,    -1,  1050,   586,
     587,   445,    -1,    -1,   587,   588,    -1,  1119,   162,    -1,
    1119,   182,    -1,   589,    -1,   591,    -1,   595,    -1,   597,
      -1,   599,    -1,   600,    -1,   606,    -1,   607,    -1,   608,
      -1,    46,  1113,  1079,   594,   590,    -1,    -1,   312,    -1,
      55,    -1,   310,  1113,  1079,  1112,    -1,   310,  1113,  1079,
     394,  1079,  1112,    -1,   310,  1119,   426,  1118,  1136,   593,
     594,  1112,   592,    -1,    -1,   109,  1127,  1058,    -1,    -1,
    1117,  1079,    -1,    -1,   394,  1079,    -1,   213,  1100,   596,
      -1,   371,    -1,   270,    -1,   425,   268,   432,  1119,   598,
      -1,   425,   268,   165,  1119,   598,    -1,   228,    -1,  1076,
      -1,    97,  1100,  1057,    -1,   223,  1119,  1060,  1123,   601,
      -1,    -1,   601,   602,    -1,   603,    -1,   604,    -1,   605,
      -1,  1144,   169,  1108,  1060,  1123,    -1,  1108,   400,  1060,
    1123,    -1,  1108,    47,  1060,    -1,   311,  1124,  1119,   432,
      -1,    60,  1119,   432,    -1,   323,  1119,   698,    -1,   325,
    1105,   698,    -1,    -1,    -1,   434,   347,   445,   610,   611,
      -1,    -1,   612,    -1,    -1,   613,   614,    -1,  1090,   615,
     445,    -1,   614,  1090,   615,   445,    -1,   614,   445,    -1,
     622,    -1,    -1,   617,   618,   616,   623,    -1,   432,    -1,
      -1,   166,    -1,   432,    -1,   432,    -1,    -1,  1119,   182,
      -1,  1080,    -1,   219,  1126,  1075,    -1,    49,  1126,  1075,
      -1,   617,   619,    81,   620,  1107,   621,    -1,    -1,   623,
     624,    -1,   625,    -1,   626,    -1,   628,    -1,   629,    -1,
     630,    -1,   632,    -1,   633,    -1,   642,    -1,   643,    -1,
     645,    -1,   646,    -1,   647,    -1,   652,    -1,   653,    -1,
     314,  1075,    -1,  1119,   162,   627,    -1,    -1,    26,   228,
      -1,  1119,   182,    -1,   289,    -1,   631,    -1,   422,  1119,
     631,    -1,    36,    -1,    71,    -1,    73,    -1,    74,    -1,
      75,    -1,    76,    -1,    77,    -1,    78,    -1,   113,    -1,
     195,    -1,   282,    -1,   291,    -1,   304,    -1,   362,    -1,
     360,    -1,   361,    -1,   411,    -1,   409,    -1,   410,    -1,
      38,   359,    -1,    38,   408,    -1,    38,    -1,    41,   359,
      -1,    41,   408,    -1,    41,    -1,    40,   359,    -1,    40,
     408,    -1,    40,    -1,    39,   359,    -1,    39,   408,    -1,
      39,    -1,    37,   359,    -1,    37,   408,    -1,    37,    -1,
     245,    -1,  1135,   217,  1098,    -1,  1135,   401,  1098,    -1,
     267,  1079,   634,  1141,   635,   636,   639,    -1,    -1,   394,
    1079,    -1,    -1,   109,  1127,  1058,    -1,   637,    -1,    -1,
     637,   638,  1121,  1119,  1057,    -1,    27,    -1,   110,    -1,
      -1,   196,  1110,   640,    -1,   641,    -1,   640,   641,    -1,
     432,    -1,   211,  1132,    -1,   384,   644,    -1,    -1,   218,
      -1,   337,    -1,    42,  1143,   438,    -1,    33,    -1,    -1,
     425,  1120,   649,   648,  1143,  1133,  1142,   651,    -1,   650,
      -1,   649,   650,    -1,  1080,    -1,  1080,   391,  1080,    -1,
      -1,   395,  1119,  1080,    -1,   321,  1076,    -1,   321,  1076,
     391,  1076,    -1,    21,   219,    -1,    -1,    -1,   231,   347,
     445,   655,   611,    -1,    -1,    -1,   227,   347,   445,   657,
     611,    -1,    -1,    -1,   323,   347,   445,   659,   660,    -1,
      -1,   661,    -1,   662,    -1,   661,   662,    -1,   308,   698,
     663,   445,   677,    -1,    -1,   663,   664,    -1,  1119,   182,
      -1,    59,  1119,  1071,    -1,   665,    -1,   669,    -1,    85,
     666,    -1,    86,   666,    -1,   667,   668,    -1,    -1,   167,
      -1,  1074,    -1,   668,  1074,    -1,   284,  1120,   675,   670,
     671,   672,   673,   674,    -1,    -1,   187,  1119,  1079,    -1,
      -1,   168,   111,  1119,  1079,    -1,    -1,   214,    88,  1119,
    1079,    -1,    -1,   215,  1119,  1079,    -1,    -1,   169,  1119,
    1079,    -1,  1079,    -1,  1079,   676,  1079,    65,    -1,  1079,
     676,    -1,   225,    -1,   226,    -1,    -1,   677,   678,    -1,
     617,   618,   679,   445,    -1,    -1,   679,   680,    -1,   681,
      -1,   683,    -1,   690,    -1,   629,    -1,   630,    -1,   632,
      -1,   642,    -1,   684,    -1,   645,    -1,   695,    -1,   685,
      -1,   647,    -1,   688,    -1,   696,    -1,   633,    -1,   689,
      -1,   404,  1119,   682,    -1,   327,    -1,   286,    -1,    88,
      -1,   111,    -1,    87,    -1,   285,    -1,   326,    -1,   250,
     186,  1119,  1079,    -1,    64,  1125,  1119,  1079,    -1,    64,
     262,    -1,    65,    -1,   686,    -1,   685,   686,    -1,   381,
    1126,   687,    -1,  1058,    -1,   294,   428,  1030,    -1,   426,
    1074,   174,  1065,    48,  1065,    -1,   691,   692,    -1,   225,
     694,  1120,    -1,   226,  1105,    -1,   693,    -1,   692,   693,
      -1,   290,  1079,    -1,  1079,    -1,   250,   284,    -1,    -1,
     261,    -1,   262,    -1,   367,  1119,  1074,  1097,    -1,   186,
     697,    -1,    -1,   197,    -1,   432,    -1,    -1,    -1,    -1,
     342,   347,   445,   700,   701,   702,    -1,    -1,   703,    -1,
     704,    -1,   703,   704,    -1,   622,    -1,    -1,   617,   618,
     705,   706,   445,    -1,    -1,   706,   707,    -1,    43,    -1,
      44,    -1,    35,    -1,    45,    -1,   153,   148,    -1,   153,
     150,    -1,   188,    -1,   234,    -1,   334,    -1,   405,    -1,
     281,    -1,    30,    -1,   348,    -1,   329,    -1,   175,    -1,
     305,    -1,   225,  1125,  1119,   708,  1073,    -1,    64,  1125,
    1119,   709,  1073,    -1,   171,  1119,  1073,    -1,    32,  1119,
    1073,    -1,   630,    -1,   645,    -1,   642,    -1,   632,    -1,
     647,    -1,   629,    -1,   710,    -1,   424,  1074,    -1,   174,
    1072,    -1,   394,  1074,    -1,    -1,   290,    -1,   439,    -1,
     239,    -1,   440,    -1,    -1,   290,    -1,   439,    -1,   239,
      -1,   440,    -1,   267,  1079,  1141,    -1,    -1,    -1,    -1,
     298,   115,   714,   722,   445,   712,   723,   713,   725,    -1,
      -1,    -1,   424,   715,   717,    -1,    -1,    53,   716,   717,
      -1,   718,    -1,   717,   718,    -1,   719,   720,   721,   432,
      -1,    -1,  1110,   316,    -1,  1110,   425,    -1,    -1,   363,
    1119,    30,    -1,   363,  1119,   105,    -1,   408,   363,  1119,
    1079,    -1,   363,  1119,  1079,    -1,    -1,   274,    -1,    -1,
     332,   432,    -1,    -1,    -1,   104,   445,   724,   725,   121,
     104,   445,    -1,    -1,   725,   726,    -1,   727,    -1,   728,
      -1,   729,    -1,   735,   445,    -1,     1,   445,    -1,   730,
     347,   731,   445,    -1,   432,   445,    -1,   730,    -1,   432,
      -1,    -1,   228,    -1,    -1,    -1,   733,   734,   735,    -1,
      -1,   735,   736,    -1,   737,    -1,   747,    -1,   752,    -1,
     756,    -1,   759,    -1,   772,    -1,   775,    -1,   785,    -1,
     780,    -1,   786,    -1,   787,    -1,   790,    -1,   797,    -1,
     801,    -1,   803,    -1,   818,    -1,   821,    -1,   823,    -1,
     825,    -1,   828,    -1,   830,    -1,   836,    -1,   845,    -1,
     847,    -1,   864,    -1,   866,    -1,   869,    -1,   873,    -1,
     879,    -1,   889,    -1,   896,    -1,   898,    -1,   901,    -1,
     905,    -1,   906,    -1,   917,    -1,   928,    -1,   938,    -1,
     944,    -1,   947,    -1,   953,    -1,   957,    -1,   959,    -1,
     961,    -1,   963,    -1,   966,    -1,   977,    -1,   990,    -1,
     251,    -1,    -1,     3,   738,   739,   746,    -1,  1074,   740,
     743,   997,    -1,  1074,   174,   155,   212,    -1,  1074,   174,
     226,    -1,  1074,   174,    65,    -1,  1074,   174,    98,    -1,
    1074,   174,    98,   437,    -1,  1074,   174,    99,    -1,  1074,
     174,    99,   436,    -1,  1074,   174,   100,    -1,  1074,   174,
     392,    -1,  1074,   174,    67,    -1,  1074,   174,   147,   997,
      -1,  1074,   174,   145,  1069,   997,    -1,  1074,   174,    24,
      -1,  1074,   174,    25,   997,    -1,  1074,   174,  1052,    -1,
    1074,   174,   432,    -1,    -1,  1108,   741,   742,    -1,  1108,
     742,   741,    -1,  1108,   741,    -1,  1108,   742,    -1,    29,
    1069,    -1,   225,  1125,  1071,    -1,    64,  1125,  1071,    -1,
     292,  1125,  1071,    -1,    -1,   431,   744,    -1,   745,    -1,
     744,   745,    -1,    35,    -1,    45,    -1,   188,    -1,   234,
      -1,   334,    -1,   405,    -1,   281,    -1,   171,  1119,  1073,
      -1,    32,  1119,  1073,    -1,   344,   414,  1029,    -1,   344,
     116,  1029,    -1,    30,    -1,   175,    -1,   329,    -1,   348,
      -1,   415,    -1,   305,    -1,    -1,   122,    -1,    -1,     5,
     748,   749,   751,    -1,  1064,   394,  1045,  1003,    -1,  1064,
     750,   181,  1045,  1003,    -1,    90,  1074,   394,  1074,  1097,
    1003,    -1,    -1,   394,  1065,    -1,    -1,   123,    -1,    -1,
      10,   753,   754,    -1,   432,  1093,   755,    -1,  1031,    55,
    1093,   332,  1063,    -1,    -1,   332,  1063,    -1,    18,   757,
      -1,    -1,   757,  1054,   394,   758,  1054,    -1,    -1,   300,
     394,    -1,    -1,    50,   760,  1072,   761,   766,   767,   769,
     771,    -1,    -1,    -1,   424,   762,   763,    -1,   764,    -1,
     763,   764,    -1,   765,   270,    -1,   765,   720,  1065,    -1,
      -1,  1110,   316,    -1,  1110,    83,    -1,  1110,   425,    -1,
      -1,   332,  1074,    -1,   181,  1074,    -1,    -1,    -1,   984,
     768,   732,    -1,    -1,    -1,   985,   770,   732,    -1,    -1,
     124,    -1,    -1,    51,   773,   774,    -1,    -1,   774,  1071,
      -1,    -1,    58,   776,   777,    -1,    -1,   777,  1050,   778,
      -1,    -1,   779,    -1,   779,  1116,   320,    -1,  1144,   252,
     335,    -1,  1144,   232,    -1,   315,    -1,   406,    -1,    -1,
      72,   781,   782,   783,    -1,  1045,   784,  1031,  1003,    -1,
      -1,   125,    -1,   446,    -1,   151,    -1,    69,    -1,    84,
      -1,    -1,   106,   788,  1050,  1131,  1023,   789,    -1,    -1,
     126,    -1,    -1,   113,   791,   792,   796,    -1,  1071,   419,
     998,    -1,  1071,   420,   998,    -1,  1071,   417,   998,    -1,
    1071,   418,   998,    -1,  1064,   740,   793,   998,    -1,  1064,
     740,   416,  1052,   793,   998,    -1,  1064,   740,   416,   432,
     793,   998,    -1,  1064,   740,   416,   296,   793,   998,    -1,
    1064,   740,   416,    92,   793,   998,    -1,    -1,  1144,   260,
      -1,   431,   794,    -1,   795,    -1,   794,   795,    -1,    35,
      -1,    45,    -1,   153,   148,    -1,   153,   150,    -1,   188,
      -1,   234,    -1,   334,    -1,   405,    -1,   281,    -1,   171,
    1119,  1073,    -1,    32,  1119,  1073,    -1,   344,   414,  1029,
      -1,   344,   116,  1029,    -1,    43,    -1,    44,    -1,    -1,
     127,    -1,    -1,   114,   798,   799,   800,    -1,  1065,   204,
    1045,  1003,    -1,  1065,   204,  1065,   181,  1045,  1003,    -1,
    1065,    48,  1065,   181,  1045,  1003,    -1,  1065,   204,  1065,
     181,  1046,   319,  1046,  1003,    -1,  1065,    48,  1065,   181,
    1046,   319,  1046,  1003,    -1,    -1,   128,    -1,    -1,   144,
     802,   228,   761,    -1,    -1,   156,   804,   805,   807,   817,
      -1,   806,    -1,   805,  1104,   806,    -1,  1031,    -1,   399,
      -1,   395,    -1,   808,   811,    -1,   809,    -1,   808,   809,
      -1,    -1,   813,   810,   732,    -1,    -1,    -1,   430,   812,
     732,    -1,   428,   814,    -1,   813,   428,   814,    -1,   815,
      -1,   814,  1104,   815,    -1,  1032,   816,    -1,    21,    -1,
     399,    -1,   395,    -1,    -1,   391,  1031,    -1,    -1,   129,
      -1,    -1,   160,   819,   820,    -1,    -1,   301,    -1,   288,
      -1,   288,    96,    -1,   347,    -1,   287,    -1,    -1,   173,
     822,  1062,    -1,    -1,   180,   824,  1074,    -1,    -1,   183,
    1142,   826,  1053,   827,    -1,    -1,   109,  1127,  1074,    -1,
      -1,   184,   829,    -1,    -1,    -1,   191,   831,  1030,  1140,
     832,   732,   833,   835,    -1,   191,     1,   131,    -1,    -1,
      -1,   120,   834,   732,    -1,    -1,   131,    -1,    -1,   198,
     837,  1062,   838,   839,   840,   844,    -1,    -1,  1144,   166,
      -1,    -1,     9,  1142,   425,    -1,   843,  1142,   425,    -1,
      -1,   322,   841,    -1,   842,    -1,   841,   842,    -1,   843,
    1114,    48,  1065,    -1,    12,    -1,    15,    -1,   263,    -1,
      16,    -1,   264,    -1,   245,    -1,   246,    -1,    -1,   105,
      -1,    -1,   200,   846,   668,    -1,    -1,   203,   848,   849,
     850,    -1,  1074,    -1,  1080,    -1,  1083,    -1,   851,    -1,
     850,   851,    -1,   852,    -1,   856,    -1,   861,    -1,    -1,
     385,   853,   854,    -1,   855,    -1,   854,   855,    -1,  1069,
     170,    -1,    55,   862,    -1,     9,    -1,   217,    -1,   401,
      -1,  1069,   862,    -1,   322,   857,    -1,   858,    -1,   857,
     858,    -1,    55,    48,  1069,   862,    -1,   859,   860,    -1,
      -1,     9,    -1,   217,    -1,   168,    -1,   401,    -1,  1069,
      48,  1070,   862,    -1,    89,  1069,   394,  1070,   862,    -1,
      -1,   862,   994,   863,  1065,    -1,    -1,   397,    -1,    -1,
     238,   865,   930,    -1,    -1,   242,   867,   868,    -1,  1065,
     394,  1062,    -1,    90,  1065,   394,  1062,    -1,    -1,   244,
     870,   871,   872,    -1,  1065,    48,  1045,  1003,    -1,  1065,
      48,  1065,   181,  1045,  1003,    -1,    -1,   132,    -1,    -1,
     273,   874,   875,    -1,    -1,   875,   876,   877,  1049,   878,
      -1,   201,    -1,   279,    -1,   209,    -1,   161,    -1,    -1,
     357,  1144,   566,    -1,    -1,  1144,   252,   335,    -1,  1144,
     232,    -1,    -1,   288,   880,   881,    -1,   884,   885,    -1,
      -1,   885,   882,   732,   883,    -1,   885,   133,    -1,    -1,
     133,    -1,  1054,    -1,  1054,   391,  1054,    -1,    -1,   172,
      -1,  1072,   393,    -1,   886,   413,  1030,    -1,   886,   426,
     887,    -1,    -1,  1144,   388,   994,    -1,   888,    -1,   887,
       8,   888,    -1,  1074,   174,  1065,    48,  1065,   413,  1030,
      -1,    -1,   309,   890,  1050,  1094,  1131,   891,   892,   893,
     894,   895,    -1,    -1,   204,  1074,    -1,    -1,   193,   232,
      -1,  1144,   232,    -1,  1144,   252,   232,    -1,  1144,   192,
     232,    -1,  1144,   427,    -1,    -1,   212,  1119,   668,    -1,
      -1,  1013,    -1,  1024,    -1,    -1,   135,    -1,    -1,   318,
     897,  1047,   992,    -1,    -1,   331,   899,  1050,  1131,   891,
    1013,   900,    -1,    -1,   136,    -1,    -1,   336,   902,  1047,
     992,   903,  1023,   904,    -1,    -1,  1144,   232,    -1,  1144,
     252,   232,    -1,    -1,   137,    -1,   338,    -1,    -1,   346,
     907,   908,   916,    -1,  1048,   910,   911,   913,    -1,    -1,
       9,  1048,   911,   428,  1031,   909,   732,    -1,    -1,   426,
    1074,    -1,    -1,    -1,  1108,   121,   912,   732,    -1,   914,
      -1,   914,   913,    -1,    -1,   428,  1030,   915,   732,    -1,
      -1,   138,    -1,    -1,   356,   918,   919,    -1,   920,    -1,
     921,    -1,   922,    -1,   924,    -1,   926,    -1,   145,  1069,
     394,  1069,    -1,  1062,   394,   144,  1068,    -1,  1062,   394,
    1065,    -1,  1062,   923,    48,  1065,    -1,   414,    -1,   116,
      -1,   925,    -1,   924,   925,    -1,  1051,   394,   507,    -1,
     927,    -1,   926,   927,    -1,  1062,   394,   399,    -1,  1062,
     394,   395,    -1,    -1,   365,   929,   930,    -1,    -1,  1076,
     932,   934,   935,   931,   936,   937,    -1,    -1,   932,  1127,
     638,  1121,   933,    -1,    -1,   933,  1076,    -1,    -1,  1101,
    1128,    -1,    -1,  1102,  1119,  1058,    -1,    -1,   424,  1049,
      -1,   201,   298,  1119,   884,    -1,    -1,   181,  1049,    -1,
     279,   298,  1119,   884,    -1,    -1,    -1,   374,   939,  1050,
     940,   941,  1023,   943,    -1,    -1,   212,  1119,   942,  1065,
      -1,  1095,  1036,    -1,  1095,  1037,    -1,  1095,  1038,    -1,
    1095,  1039,    -1,  1095,  1040,    -1,    -1,   139,    -1,    -1,
     376,   340,   945,   946,    -1,   376,   228,    -1,    -1,   332,
    1065,    -1,   181,  1065,    -1,    -1,   377,   948,   949,   204,
    1074,   951,  1008,   952,    -1,   950,    -1,   949,   950,    -1,
    1065,    -1,   107,  1110,   363,    -1,   107,  1110,  1065,    -1,
      -1,  1144,   291,  1074,    -1,    -1,   140,    -1,    -1,   380,
     954,   955,   956,    -1,  1064,   174,  1045,  1003,    -1,  1064,
     174,  1065,   181,  1045,  1003,    -1,    90,  1074,   174,  1074,
    1097,  1003,    -1,    -1,   141,    -1,   382,   958,    -1,    -1,
     297,    -1,    -1,   387,   960,   668,    -1,    -1,   402,   962,
    1074,   174,  1069,   394,  1070,    -1,    -1,   407,   964,  1050,
     965,    -1,    -1,   310,    -1,   312,    -1,    -1,   412,   967,
    1074,   968,   971,   951,   975,  1008,   976,    -1,    -1,   107,
    1110,   969,    -1,   970,    -1,   969,   275,   970,    -1,  1091,
    1069,    -1,   204,   972,    -1,   971,   972,    -1,  1074,   973,
     974,    -1,    -1,   108,  1118,  1074,    -1,    -1,    91,  1118,
    1074,    -1,    -1,   385,  1118,  1074,    -1,    -1,   142,    -1,
     978,    -1,   987,    -1,   989,    -1,   423,   979,   981,   982,
     983,   986,  1127,   980,    -1,    -1,   182,    -1,  1049,    -1,
     201,    -1,   279,    -1,   209,    -1,   161,    -1,    -1,     8,
      -1,    -1,   371,    -1,   158,    -1,   154,    -1,   158,    -1,
     280,    -1,   256,    -1,   258,    -1,    -1,   298,    -1,   423,
    1116,   102,  1127,   988,    -1,  1054,    -1,     9,   299,    -1,
     423,   979,    34,   324,  1074,    -1,    -1,   435,   991,  1047,
     992,   903,   993,   995,   996,    -1,    -1,   174,  1071,    -1,
      -1,   994,  1103,  1073,  1122,    -1,   994,  1103,  1052,    -1,
     994,  1103,   284,    -1,    34,    -1,     8,    -1,    -1,  1018,
      -1,  1024,    -1,    -1,   143,    -1,   999,  1001,    -1,   999,
    1001,    -1,    -1,    -1,   158,  1000,   732,    -1,    -1,    -1,
     256,  1002,   732,    -1,  1004,  1006,    -1,    -1,    -1,   364,
    1005,   732,    -1,    -1,    -1,   259,  1007,   732,    -1,  1009,
    1011,    -1,    -1,    -1,   280,  1010,   732,    -1,    -1,    -1,
     258,  1012,   732,    -1,  1014,    -1,  1016,    -1,  1014,  1016,
      -1,    -1,   121,  1015,   732,    -1,    -1,   254,  1017,   732,
      -1,  1019,    -1,  1021,    -1,  1019,  1021,    -1,    -1,   149,
    1020,   732,    -1,    -1,   255,  1022,   732,    -1,    -1,  1024,
      -1,  1025,    -1,  1027,    -1,  1025,  1027,    -1,    -1,   207,
    1026,   732,    -1,    -1,   257,  1028,   732,    -1,    -1,  1110,
    1073,  1122,    -1,  1031,    -1,  1032,    -1,    -1,  1033,  1034,
      -1,  1034,   208,    -1,  1035,  1065,    -1,  1034,   447,    -1,
    1034,   270,    -1,  1034,   263,    -1,  1034,    12,    -1,  1034,
      13,    -1,  1034,    14,    -1,  1034,    57,    -1,  1034,   293,
      -1,  1034,   249,    -1,  1034,   438,    -1,  1034,   253,    -1,
      -1,  1035,   208,    -1,  1035,   448,    -1,  1035,   439,    -1,
    1035,   440,    -1,  1035,   444,    -1,  1035,   253,    -1,  1034,
     439,    -1,  1034,   440,    -1,  1034,   441,    -1,  1034,   442,
      -1,  1034,   444,    -1,  1034,  1036,    -1,  1034,  1037,    -1,
    1034,  1038,    -1,  1034,  1039,    -1,  1034,  1040,    -1,  1034,
     248,    -1,  1035,  1036,    -1,  1035,  1037,    -1,  1035,  1038,
      -1,  1035,  1039,    -1,  1035,  1040,    -1,  1035,   248,    -1,
    1034,    20,    -1,  1034,   275,    -1,   446,    -1,   151,  1142,
      -1,   152,    -1,   449,    -1,   185,  1139,    -1,   450,    -1,
     220,  1139,    -1,   179,    -1,   185,  1139,   275,   151,  1142,
      -1,   216,    -1,   220,  1139,   275,   151,  1142,    -1,  1043,
      -1,  1041,  1042,  1043,    -1,    -1,    68,    -1,   351,    -1,
    1066,    -1,  1043,   439,  1043,    -1,  1043,   440,  1043,    -1,
    1043,   441,  1043,    -1,  1043,   442,  1043,    -1,   439,  1043,
      -1,   440,  1043,    -1,  1043,   444,  1043,    -1,   448,  1043,
     447,    -1,   224,    -1,   224,  1099,   432,    -1,  1046,    -1,
    1045,  1046,    -1,  1065,  1097,    -1,  1076,    -1,  1076,    -1,
    1050,    -1,  1049,  1050,    -1,   432,    -1,  1052,    -1,  1051,
    1052,    -1,   240,    -1,    -1,  1053,  1054,    -1,  1055,    -1,
    1076,    -1,  1056,    -1,  1056,  1099,  1056,    -1,   228,    -1,
    1058,    -1,  1057,  1058,    -1,  1076,    -1,    -1,  1058,    -1,
    1058,    -1,   228,    -1,   432,    -1,  1063,    -1,  1062,  1063,
      -1,  1074,    -1,     6,  1126,  1075,    -1,  1065,    -1,  1064,
    1065,    -1,  1074,    -1,   219,  1126,  1075,    -1,   219,  1126,
    1081,    -1,   219,  1126,  1083,    -1,     6,  1126,  1067,  1068,
      -1,     6,  1126,  1075,    -1,  1080,    -1,  1083,    -1,  1044,
      -1,  1074,    -1,   219,  1126,  1075,    -1,   219,  1126,  1081,
      -1,   219,  1126,  1083,    -1,  1081,    -1,  1083,    -1,  1044,
      -1,   301,    -1,   144,    -1,  1075,    -1,   228,    -1,  1074,
      -1,  1081,    -1,  1074,    -1,  1080,    -1,  1074,    -1,   228,
      -1,  1074,    -1,   228,    -1,  1083,    -1,  1074,    -1,  1079,
      -1,   438,    -1,  1075,    -1,  1076,    -1,  1076,  1077,    -1,
    1076,  1078,    -1,  1076,  1077,  1078,    -1,   432,    -1,   432,
    1099,  1076,    -1,   448,  1041,   447,    -1,   448,  1043,   451,
     447,    -1,   448,  1043,   451,  1043,   447,    -1,   228,    -1,
    1081,    -1,     9,  1082,    -1,  1082,    -1,  1081,   452,  1082,
      -1,   228,    -1,   369,    -1,   438,    -1,   306,    -1,   189,
      -1,   235,    -1,   398,    -1,    94,  1084,    -1,   429,  1084,
      -1,   421,   448,  1043,   447,  1084,    -1,   233,   448,  1043,
     447,  1084,    -1,   333,   448,  1043,   447,  1084,    -1,    79,
     448,  1041,   447,  1084,    -1,   378,   448,  1041,   447,  1084,
      -1,   379,   448,  1041,   447,  1084,    -1,   403,   448,  1087,
     447,  1084,    -1,   265,   448,  1088,   447,    -1,   230,   448,
    1089,   447,  1084,    -1,   178,  1085,    -1,    -1,   448,  1043,
     451,   447,    -1,   448,  1043,   451,  1043,   447,    -1,    -1,
     448,  1086,   447,    -1,    -1,  1041,    -1,  1043,    -1,  1043,
    1042,   217,    -1,  1043,  1042,   401,    -1,  1043,    -1,  1043,
    1042,  1043,    -1,  1043,    -1,  1043,  1042,  1058,    -1,    -1,
      -1,     9,    -1,    -1,  1101,    -1,    -1,   199,    -1,    -1,
     250,    -1,   295,    -1,    -1,   253,    -1,    -1,   274,    -1,
      -1,   339,    -1,    -1,   353,  1111,    -1,   194,    -1,   268,
      -1,   310,  1119,    -1,   312,  1105,    -1,   431,   117,    -1,
     117,    -1,    61,   354,    -1,   354,    -1,    -1,     7,    -1,
      -1,    17,    -1,    -1,    22,    -1,    -1,    23,    -1,    -1,
      26,    -1,    -1,    29,    -1,    -1,    36,    -1,    -1,    48,
      -1,    -1,    54,    -1,    -1,    55,    -1,    -1,    82,    -1,
      -1,    97,    -1,    -1,   396,    -1,    -1,   170,    -1,    -1,
     174,    -1,    -1,   194,    -1,    -1,   208,    -1,    -1,   208,
      -1,    22,    -1,    -1,   212,    -1,    -1,   225,    -1,   226,
      -1,    -1,   226,    -1,    -1,   241,    -1,    -1,   261,    -1,
      -1,   268,    -1,    -1,   271,    -1,    -1,   276,    -1,   194,
     276,    -1,    -1,   278,    -1,    -1,   301,    -1,    -1,   310,
      -1,    -1,   337,    -1,    -1,   356,    -1,    -1,   358,    -1,
      -1,   358,    -1,   358,   208,    -1,    -1,   363,    -1,    -1,
     375,    -1,    -1,   386,    -1,    -1,   389,    -1,    -1,   390,
      -1,    -1,   393,    -1,    -1,   394,    -1,    -1,   428,    -1,
      -1,   431,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   760,   760,   760,   802,   803,   807,   808,   813,   814,
     812,   822,   823,   821,   831,   832,   830,   837,   838,   839,
     842,   843,   869,   893,   923,   922,   963,  1007,  1008,  1012,
    1013,  1016,  1017,  1021,  1028,  1035,  1039,  1043,  1055,  1056,
    1066,  1067,  1076,  1077,  1081,  1082,  1083,  1084,  1093,  1096,
    1097,  1098,  1099,  1103,  1110,  1119,  1122,  1123,  1124,  1125,
    1129,  1130,  1134,  1135,  1136,  1140,  1147,  1148,  1152,  1159,
    1171,  1174,  1175,  1179,  1180,  1184,  1188,  1195,  1196,  1206,
    1209,  1210,  1214,  1215,  1219,  1220,  1221,  1222,  1223,  1224,
    1225,  1226,  1227,  1228,  1229,  1236,  1247,  1246,  1257,  1271,
    1285,  1299,  1315,  1316,  1324,  1325,  1333,  1332,  1344,  1345,
    1346,  1347,  1348,  1356,  1357,  1362,  1363,  1365,  1364,  1376,
    1377,  1381,  1382,  1383,  1384,  1385,  1386,  1390,  1391,  1392,
    1393,  1394,  1395,  1402,  1413,  1425,  1426,  1430,  1431,  1438,
    1447,  1448,  1452,  1453,  1467,  1482,  1549,  1560,  1567,  1574,
    1580,  1587,  1588,  1592,  1591,  1601,  1600,  1616,  1617,  1620,
    1621,  1626,  1625,  1646,  1647,  1651,  1652,  1653,  1654,  1655,
    1656,  1657,  1658,  1659,  1660,  1661,  1662,  1663,  1670,  1674,
    1679,  1686,  1687,  1688,  1691,  1692,  1696,  1700,  1701,  1708,
    1715,  1719,  1720,  1721,  1728,  1748,  1791,  1791,  1795,  1799,
    1815,  1816,  1817,  1823,  1833,  1842,  1844,  1845,  1851,  1855,
    1856,  1857,  1860,  1861,  1862,  1866,  1870,  1871,  1877,  1878,
    1882,  1891,  1900,  1909,  1924,  1934,  1941,  1951,  1958,  1965,
    1969,  1970,  1971,  1979,  1980,  1983,  1984,  1988,  1989,  1993,
    1994,  2000,  2025,  2026,  2027,  2028,  2034,  2041,  2042,  2046,
    2049,  2050,  2058,  2059,  2073,  2074,  2074,  2077,  2076,  2089,
    2090,  2094,  2106,  2115,  2119,  2120,  2130,  2129,  2147,  2148,
    2152,  2159,  2166,  2167,  2168,  2169,  2170,  2171,  2172,  2173,
    2174,  2181,  2185,  2185,  2185,  2191,  2203,  2228,  2252,  2253,
    2260,  2261,  2265,  2266,  2273,  2280,  2281,  2288,  2292,  2301,
    2302,  2308,  2318,  2336,  2337,  2341,  2342,  2343,  2347,  2354,
    2361,  2371,  2378,  2396,  2400,  2411,  2412,  2412,  2423,  2424,
    2428,  2428,  2445,  2446,  2448,  2452,  2454,  2453,  2485,  2490,
    2495,  2501,  2510,  2518,  2519,  2527,  2528,  2529,  2533,  2553,
    2557,  2566,  2567,  2568,  2569,  2570,  2571,  2572,  2573,  2574,
    2575,  2576,  2577,  2578,  2579,  2586,  2608,  2630,  2631,  2643,
    2663,  2670,  2671,  2675,  2676,  2677,  2678,  2679,  2680,  2681,
    2682,  2683,  2684,  2685,  2686,  2691,  2696,  2697,  2698,  2699,
    2700,  2701,  2702,  2703,  2704,  2705,  2706,  2707,  2708,  2709,
    2710,  2711,  2712,  2713,  2714,  2722,  2730,  2738,  2745,  2750,
    2761,  2778,  2779,  2782,  2783,  2790,  2814,  2815,  2832,  2833,
    2836,  2837,  2844,  2845,  2850,  2860,  2867,  2870,  2871,  2872,
    2879,  2886,  2911,  2911,  2916,  2917,  2921,  2922,  2925,  2926,
    2939,  2951,  2971,  2985,  2987,  2986,  3006,  3007,  3007,  3020,
    3022,  3021,  3033,  3034,  3038,  3039,  3048,  3055,  3058,  3062,
    3066,  3067,  3068,  3075,  3076,  3080,  3083,  3083,  3086,  3087,
    3093,  3098,  3099,  3102,  3103,  3106,  3107,  3110,  3111,  3114,
    3115,  3119,  3120,  3121,  3125,  3126,  3129,  3130,  3134,  3138,
    3139,  3143,  3144,  3145,  3146,  3147,  3148,  3149,  3150,  3151,
    3152,  3153,  3154,  3155,  3156,  3157,  3158,  3162,  3166,  3167,
    3168,  3169,  3170,  3171,  3172,  3176,  3180,  3181,  3182,  3186,
    3187,  3191,  3195,  3200,  3204,  3208,  3212,  3213,  3217,  3218,
    3222,  3223,  3224,  3227,  3227,  3227,  3230,  3234,  3237,  3237,
    3240,  3247,  3248,  3249,  3248,  3266,  3267,  3271,  3272,  3277,
    3279,  3278,  3314,  3315,  3319,  3320,  3321,  3322,  3323,  3324,
    3325,  3326,  3327,  3328,  3329,  3330,  3331,  3332,  3333,  3334,
    3335,  3339,  3343,  3347,  3351,  3352,  3353,  3354,  3355,  3356,
    3357,  3358,  3365,  3369,  3379,  3382,  3386,  3390,  3394,  3402,
    3405,  3409,  3413,  3417,  3425,  3438,  3440,  3450,  3439,  3477,
    3479,  3478,  3485,  3484,  3493,  3494,  3499,  3506,  3508,  3512,
    3522,  3524,  3532,  3540,  3569,  3600,  3602,  3612,  3617,  3628,
    3629,  3629,  3656,  3657,  3661,  3662,  3663,  3664,  3680,  3692,
    3723,  3760,  3772,  3775,  3776,  3785,  3789,  3785,  3802,  3820,
    3824,  3825,  3826,  3827,  3828,  3829,  3830,  3831,  3832,  3833,
    3834,  3835,  3836,  3837,  3838,  3839,  3840,  3841,  3842,  3843,
    3844,  3845,  3846,  3847,  3848,  3849,  3850,  3851,  3852,  3853,
    3854,  3855,  3856,  3857,  3858,  3859,  3860,  3861,  3862,  3863,
    3864,  3865,  3866,  3867,  3868,  3869,  3870,  3871,  3872,  3895,
    3894,  3907,  3911,  3915,  3919,  3923,  3927,  3931,  3935,  3939,
    3943,  3947,  3951,  3955,  3959,  3963,  3967,  3971,  3978,  3979,
    3980,  3981,  3982,  3983,  3987,  3991,  3992,  3995,  3996,  4000,
    4001,  4005,  4006,  4007,  4008,  4009,  4010,  4011,  4012,  4016,
    4020,  4024,  4029,  4030,  4031,  4032,  4033,  4034,  4038,  4039,
    4048,  4048,  4054,  4058,  4062,  4068,  4069,  4073,  4074,  4083,
    4083,  4088,  4092,  4099,  4100,  4109,  4115,  4116,  4120,  4120,
    4128,  4128,  4138,  4140,  4139,  4148,  4149,  4154,  4161,  4168,
    4170,  4174,  4182,  4193,  4194,  4195,  4200,  4204,  4203,  4215,
    4219,  4218,  4229,  4230,  4239,  4239,  4243,  4244,  4256,  4256,
    4260,  4261,  4272,  4273,  4274,  4275,  4276,  4279,  4279,  4287,
    4287,  4293,  4300,  4301,  4304,  4304,  4311,  4324,  4337,  4337,
    4348,  4349,  4359,  4358,  4371,  4375,  4379,  4383,  4387,  4391,
    4395,  4400,  4404,  4411,  4412,  4413,  4417,  4418,  4423,  4424,
    4425,  4426,  4427,  4428,  4429,  4430,  4431,  4432,  4436,  4440,
    4444,  4449,  4450,  4454,  4455,  4464,  4464,  4470,  4474,  4478,
    4482,  4486,  4493,  4494,  4503,  4503,  4525,  4524,  4543,  4544,
    4555,  4564,  4569,  4577,  4606,  4607,  4613,  4612,  4628,  4632,
    4631,  4646,  4647,  4652,  4653,  4664,  4693,  4694,  4695,  4698,
    4699,  4703,  4704,  4713,  4713,  4718,  4719,  4727,  4744,  4761,
    4779,  4804,  4804,  4817,  4817,  4830,  4830,  4839,  4843,  4856,
    4856,  4869,  4871,  4869,  4882,  4887,  4891,  4890,  4904,  4905,
    4914,  4914,  4922,  4923,  4927,  4928,  4929,  4933,  4934,  4939,
    4940,  4945,  4949,  4950,  4951,  4952,  4953,  4954,  4955,  4959,
    4960,  4969,  4969,  4982,  4981,  4991,  4992,  4993,  4997,  4998,
    5002,  5003,  5004,  5010,  5010,  5015,  5016,  5020,  5021,  5022,
    5023,  5024,  5025,  5031,  5035,  5036,  5040,  5045,  5049,  5050,
    5051,  5052,  5053,  5057,  5083,  5096,  5097,  5101,  5101,  5109,
    5109,  5119,  5119,  5124,  5128,  5140,  5140,  5146,  5150,  5157,
    5158,  5167,  5167,  5171,  5172,  5186,  5187,  5188,  5189,  5193,
    5194,  5198,  5199,  5200,  5212,  5212,  5217,  5222,  5221,  5231,
    5238,  5239,  5243,  5248,  5257,  5260,  5264,  5269,  5276,  5283,
    5284,  5288,  5289,  5294,  5306,  5306,  5329,  5330,  5334,  5335,
    5339,  5343,  5347,  5351,  5358,  5359,  5362,  5363,  5364,  5368,
    5369,  5378,  5378,  5393,  5393,  5404,  5405,  5414,  5414,  5425,
    5426,  5430,  5437,  5438,  5447,  5460,  5460,  5466,  5471,  5470,
    5481,  5482,  5486,  5488,  5487,  5498,  5499,  5504,  5503,  5514,
    5515,  5524,  5524,  5529,  5530,  5531,  5532,  5533,  5539,  5548,
    5552,  5561,  5568,  5569,  5575,  5576,  5580,  5589,  5590,  5594,
    5598,  5610,  5610,  5616,  5615,  5632,  5635,  5651,  5652,  5655,
    5656,  5660,  5661,  5666,  5671,  5679,  5691,  5696,  5704,  5720,
    5721,  5720,  5741,  5742,  5746,  5747,  5748,  5749,  5750,  5754,
    5755,  5764,  5764,  5769,  5776,  5777,  5778,  5787,  5787,  5796,
    5797,  5801,  5802,  5803,  5807,  5808,  5812,  5813,  5822,  5822,
    5828,  5832,  5836,  5843,  5844,  5853,  5860,  5861,  5869,  5869,
    5882,  5882,  5898,  5898,  5907,  5909,  5910,  5919,  5919,  5929,
    5930,  5935,  5936,  5941,  5948,  5949,  5954,  5961,  5962,  5966,
    5967,  5971,  5972,  5976,  5977,  5986,  5987,  5988,  5992,  6016,
    6019,  6027,  6037,  6042,  6047,  6052,  6059,  6060,  6063,  6064,
    6068,  6068,  6072,  6072,  6076,  6076,  6079,  6080,  6084,  6091,
    6092,  6096,  6108,  6108,  6119,  6120,  6125,  6128,  6132,  6136,
    6143,  6144,  6147,  6148,  6149,  6153,  6154,  6167,  6175,  6182,
    6184,  6183,  6193,  6195,  6194,  6209,  6213,  6215,  6214,  6225,
    6227,  6226,  6243,  6249,  6251,  6250,  6260,  6262,  6261,  6277,
    6282,  6287,  6297,  6296,  6308,  6307,  6323,  6328,  6333,  6343,
    6342,  6354,  6353,  6368,  6369,  6373,  6378,  6383,  6393,  6392,
    6404,  6403,  6420,  6423,  6435,  6442,  6449,  6449,  6459,  6460,
    6461,  6463,  6464,  6465,  6466,  6467,  6468,  6470,  6471,  6472,
    6474,  6477,  6479,  6480,  6482,  6483,  6484,  6486,  6488,  6489,
    6490,  6491,  6492,  6494,  6495,  6496,  6497,  6498,  6499,  6501,
    6502,  6503,  6504,  6505,  6506,  6508,  6509,  6512,  6512,  6512,
    6513,  6513,  6514,  6514,  6515,  6515,  6516,  6516,  6521,  6522,
    6525,  6526,  6527,  6531,  6532,  6533,  6534,  6535,  6536,  6537,
    6538,  6539,  6550,  6562,  6577,  6578,  6583,  6589,  6595,  6615,
    6619,  6635,  6649,  6650,  6655,  6661,  6662,  6667,  6676,  6677,
    6678,  6682,  6693,  6694,  6698,  6706,  6707,  6711,  6712,  6718,
    6738,  6739,  6743,  6744,  6748,  6749,  6753,  6754,  6755,  6756,
    6757,  6758,  6759,  6760,  6761,  6765,  6766,  6767,  6768,  6769,
    6770,  6771,  6775,  6776,  6780,  6781,  6785,  6786,  6790,  6791,
    6802,  6803,  6807,  6808,  6809,  6813,  6814,  6815,  6823,  6827,
    6828,  6829,  6830,  6834,  6835,  6839,  6849,  6867,  6894,  6906,
    6907,  6917,  6918,  6922,  6923,  6924,  6925,  6926,  6927,  6928,
    6936,  6940,  6944,  6948,  6952,  6956,  6960,  6964,  6968,  6972,
    6976,  6980,  6987,  6988,  6989,  6993,  6994,  6998,  6999,  7004,
    7011,  7018,  7028,  7035,  7045,  7052,  7066,  7076,  7077,  7081,
    7082,  7086,  7087,  7091,  7092,  7093,  7097,  7098,  7102,  7103,
    7107,  7108,  7112,  7113,  7120,  7120,  7121,  7121,  7122,  7122,
    7123,  7123,  7125,  7125,  7126,  7126,  7127,  7127,  7128,  7128,
    7129,  7129,  7130,  7130,  7131,  7131,  7132,  7132,  7133,  7133,
    7134,  7134,  7135,  7135,  7136,  7136,  7137,  7137,  7138,  7138,
    7139,  7139,  7140,  7140,  7141,  7141,  7142,  7142,  7142,  7143,
    7143,  7144,  7144,  7144,  7145,  7145,  7146,  7146,  7147,  7147,
    7148,  7148,  7149,  7149,  7150,  7150,  7150,  7151,  7151,  7152,
    7152,  7153,  7153,  7154,  7154,  7155,  7155,  7156,  7156,  7157,
    7157,  7157,  7158,  7158,  7159,  7159,  7160,  7160,  7161,  7161,
    7162,  7162,  7163,  7163,  7164,  7164,  7166,  7166,  7167,  7167
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
  "AND", "ANY", "ARE", "AREA", "\"ARGUMENT-NUMBER\"", "\"ARGUMENT-VALUE\"",
  "AS", "ASCENDING", "ASSIGN", "AT", "AUTO", "AUTOMATIC",
  "\"BACKGROUND-COLOR\"", "BASED", "BEFORE", "BELL", "BINARY",
  "\"BINARY-C-LONG\"", "\"BINARY-CHAR\"", "\"BINARY-DOUBLE\"",
  "\"BINARY-LONG\"", "\"BINARY-SHORT\"", "BLANK", "\"BLANK-LINE\"",
  "\"BLANK-SCREEN\"", "BLINK", "BLOCK", "BOTTOM", "BY", "\"BYTE-LENGTH\"",
  "CALL", "CANCEL", "CH", "CHAINING", "CHARACTER", "CHARACTERS", "CLASS",
  "CLASS_NAME", "CLOSE", "CODE", "\"CODE-SET\"", "COLLATING", "COL",
  "COLS", "COLUMN", "COLUMNS", "COMMA", "\"COMMAND-LINE\"",
  "\"comma delimiter\"", "COMMIT", "COMMON", "COMP", "COMPUTE",
  "\"COMP-1\"", "\"COMP-2\"", "\"COMP-3\"", "\"COMP-4\"", "\"COMP-5\"",
  "\"COMP-X\"", "\"FUNCTION CONCATENATE\"", "CONFIGURATION", "CONSTANT",
  "CONTAINS", "CONTENT", "CONTINUE", "CONTROL", "CONTROLS",
  "\"CONTROL FOOTING\"", "\"CONTROL HEADING\"", "CONVERTING",
  "CORRESPONDING", "COUNT", "CRT", "CURRENCY", "\"FUNCTION CURRENT-DATE\"",
  "CURSOR", "CYCLE", "DATA", "DATE", "DAY", "\"DAY-OF-WEEK\"", "DE",
  "DEBUGGING", "\"DECIMAL-POINT\"", "DECLARATIVES", "DEFAULT", "DELETE",
  "DELIMITED", "DELIMITER", "DEPENDING", "DESCENDING", "DETAIL", "DISK",
  "DISPLAY", "DIVIDE", "DIVISION", "DOWN", "DUPLICATES", "DYNAMIC",
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
  "data_division", "file_section", "$@16", "$@17",
  "file_description_sequence", "file_description",
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
  "delete_statement", "$@46", "end_delete", "display_statement", "$@47",
  "display_body", "with_clause", "disp_attrs", "disp_attr", "end_display",
  "divide_statement", "$@48", "divide_body", "end_divide",
  "entry_statement", "$@49", "evaluate_statement", "$@50",
  "evaluate_subject_list", "evaluate_subject", "evaluate_condition_list",
  "evaluate_case_list", "evaluate_case", "$@51", "evaluate_other", "$@52",
  "evaluate_when_list", "evaluate_object_list", "evaluate_object",
  "opt_evaluate_thru_expr", "end_evaluate", "exit_statement", "$@53",
  "exit_body", "free_statement", "$@54", "generate_statement", "$@55",
  "goto_statement", "$@56", "goto_depending", "goback_statement", "$@57",
  "if_statement", "$@58", "$@59", "if_else_sentence", "$@60", "end_if",
  "initialize_statement", "$@61", "initialize_filler", "initialize_value",
  "initialize_replacing", "initialize_replacing_list",
  "initialize_replacing_item", "initialize_category", "initialize_default",
  "initiate_statement", "$@62", "inspect_statement", "$@63",
  "send_identifier", "inspect_list", "inspect_item", "inspect_tallying",
  "$@64", "tallying_list", "tallying_item", "inspect_replacing",
  "replacing_list", "replacing_item", "rep_keyword", "replacing_region",
  "inspect_converting", "inspect_region", "_initial", "merge_statement",
  "$@65", "move_statement", "$@66", "move_body", "multiply_statement",
  "$@67", "multiply_body", "end_multiply", "open_statement", "$@68",
  "open_list", "open_mode", "open_sharing", "open_option",
  "perform_statement", "$@69", "perform_body", "$@70", "end_perform",
  "perform_procedure", "perform_option", "perform_test",
  "perform_varying_list", "perform_varying", "read_statement", "$@71",
  "read_into", "with_lock", "read_key", "read_handler", "end_read",
  "release_statement", "$@72", "return_statement", "$@73", "end_return",
  "rewrite_statement", "$@74", "write_lock", "end_rewrite",
  "rollback_statement", "search_statement", "$@75", "search_body", "$@76",
  "search_varying", "search_at_end", "$@77", "search_whens", "search_when",
  "$@78", "end_search", "set_statement", "$@79", "set_body",
  "set_environment", "set_to", "set_up_down", "up_or_down",
  "set_to_on_off_sequence", "set_to_on_off", "set_to_true_false_sequence",
  "set_to_true_false", "sort_statement", "$@80", "sort_body", "$@81",
  "sort_key_list", "opt_key_list", "sort_duplicates", "sort_collating",
  "sort_input", "sort_output", "start_statement", "$@82", "@83",
  "start_key", "start_op", "end_start", "stop_statement", "$@84",
  "stop_returning", "string_statement", "$@85", "string_item_list",
  "string_item", "opt_with_pointer", "end_string", "subtract_statement",
  "$@86", "subtract_body", "end_subtract", "suppress_statement",
  "_printing", "terminate_statement", "$@87", "transform_statement",
  "$@88", "unlock_statement", "$@89", "opt_record", "unstring_statement",
  "$@90", "unstring_delimited", "unstring_delimited_list",
  "unstring_delimited_item", "unstring_into", "unstring_into_item",
  "unstring_into_delimiter", "unstring_into_count", "unstring_tallying",
  "end_unstring", "use_statement", "use_exception", "use_global",
  "use_exception_target", "_after", "_standard", "exception_or_error",
  "exception_or_overflow", "not_exception_or_overflow", "_procedure",
  "use_debugging", "use_debugging_target", "use_reporting",
  "write_statement", "$@91", "write_from", "write_option",
  "before_or_after", "write_handler", "end_write", "on_accp_exception",
  "on_disp_exception", "opt_on_exception", "$@92", "opt_not_on_exception",
  "$@93", "on_size_error", "opt_on_size_error", "$@94",
  "opt_not_on_size_error", "$@95", "on_overflow", "opt_on_overflow",
  "$@96", "opt_not_on_overflow", "$@97", "at_end", "at_end_sentence",
  "$@98", "not_at_end_sentence", "$@99", "at_eop", "at_eop_sentence",
  "$@100", "not_at_eop_sentence", "$@101", "opt_invalid_key",
  "invalid_key", "invalid_key_sentence", "$@102",
  "not_invalid_key_sentence", "$@103", "_opt_scroll_lines", "condition",
  "expr", "partial_expr", "$@104", "expr_tokens", "expr_token", "eq", "gt",
  "lt", "ge", "le", "exp_list", "e_sep", "exp", "linage_counter",
  "arithmetic_x_list", "arithmetic_x", "record_name", "table_name",
  "file_name_list", "file_name", "mnemonic_name_list", "mnemonic_name",
  "procedure_name_list", "procedure_name", "label", "integer_label",
  "reference_list", "reference", "opt_reference", "reference_or_literal",
  "undefined_word", "target_x_list", "target_x", "x_list", "x", "arith_x",
  "prog_or_entry", "alnum_or_id", "simple_value", "simple_all_value",
  "id_or_lit", "id_or_lit_or_func", "num_id_or_lit", "identifier",
  "identifier_1", "qualified_word", "subref", "refmod", "integer",
  "literal", "basic_literal", "basic_value", "function", "func_refmod",
  "func_args", "list_func_args", "trim_args", "numvalc_args",
  "locale_dt_args", "not_const_word", "flag_all", "flag_duplicates",
  "flag_initialized", "flag_next", "flag_not", "flag_optional",
  "flag_rounded", "flag_separate", "in_of", "records", "with_dups",
  "coll_sequence", "_advancing", "_also", "_are", "_area", "_as", "_at",
  "_binary", "_by", "_character", "_characters", "_contains", "_data",
  "_file", "_for", "_from", "_in", "_is", "_is_are", "_key",
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
     685,   686,   687,   688,   689,   690,   691,   692,   693,    43,
      45,    42,    47,   694,    94,    46,    61,    41,    40,    62,
      60,    58,    38
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   453,   455,   454,   456,   456,   457,   457,   459,   460,
     458,   462,   463,   461,   465,   466,   464,   467,   467,   467,
     468,   468,   469,   470,   472,   471,   473,   474,   474,   475,
     475,   476,   476,   477,   477,   477,   478,   478,   479,   479,
     480,   480,   481,   481,   482,   482,   482,   482,   483,   484,
     484,   484,   484,   485,   486,   487,   488,   488,   488,   488,
     489,   489,   490,   490,   490,   491,   492,   492,   493,   494,
     495,   496,   496,   497,   497,   498,   498,   499,   499,   500,
     501,   501,   502,   502,   503,   503,   503,   503,   503,   503,
     503,   503,   503,   503,   503,   504,   505,   504,   504,   504,
     504,   504,   506,   506,   507,   507,   509,   508,   510,   510,
     510,   510,   510,   511,   511,   512,   512,   513,   512,   514,
     514,   515,   515,   515,   515,   515,   515,   516,   516,   516,
     516,   516,   516,   517,   518,   519,   519,   520,   520,   521,
     522,   522,   523,   523,   524,   525,   526,   527,   528,   529,
     530,   531,   531,   532,   531,   533,   531,   534,   534,   535,
     535,   537,   536,   538,   538,   539,   539,   539,   539,   539,
     539,   539,   539,   539,   539,   539,   539,   539,   540,   540,
     540,   541,   541,   541,   542,   542,   542,   543,   543,   543,
     544,   545,   545,   545,   546,   546,   548,   547,   547,   549,
     550,   550,   550,   551,   552,   553,   553,   553,   554,   555,
     555,   555,   556,   556,   556,   556,   557,   557,   558,   558,
     559,   559,   559,   559,   560,   561,   562,   563,   564,   565,
     566,   566,   566,   567,   567,   568,   568,   569,   569,   570,
     570,   571,   572,   572,   572,   572,   573,   574,   574,   575,
     576,   576,   577,   577,   578,   579,   578,   580,   578,   581,
     581,   582,   583,   583,   584,   584,   586,   585,   587,   587,
     588,   588,   588,   588,   588,   588,   588,   588,   588,   588,
     588,   589,   590,   590,   590,   591,   591,   591,   592,   592,
     593,   593,   594,   594,   595,   596,   596,   597,   597,   598,
     598,   599,   600,   601,   601,   602,   602,   602,   603,   604,
     605,   606,   607,   608,   608,   609,   610,   609,   611,   611,
     613,   612,   614,   614,   614,   615,   616,   615,   617,   618,
     618,   618,   619,   620,   620,   621,   621,   621,   622,   623,
     623,   624,   624,   624,   624,   624,   624,   624,   624,   624,
     624,   624,   624,   624,   624,   625,   626,   627,   627,   628,
     629,   630,   630,   631,   631,   631,   631,   631,   631,   631,
     631,   631,   631,   631,   631,   631,   631,   631,   631,   631,
     631,   631,   631,   631,   631,   631,   631,   631,   631,   631,
     631,   631,   631,   631,   631,   631,   631,   631,   632,   632,
     633,   634,   634,   635,   635,   636,   637,   637,   638,   638,
     639,   639,   640,   640,   641,   642,   643,   644,   644,   644,
     645,   646,   648,   647,   649,   649,   650,   650,   651,   651,
     652,   652,   653,   654,   655,   654,   656,   657,   656,   658,
     659,   658,   660,   660,   661,   661,   662,   663,   663,   664,
     664,   664,   664,   665,   665,   666,   667,   667,   668,   668,
     669,   670,   670,   671,   671,   672,   672,   673,   673,   674,
     674,   675,   675,   675,   676,   676,   677,   677,   678,   679,
     679,   680,   680,   680,   680,   680,   680,   680,   680,   680,
     680,   680,   680,   680,   680,   680,   680,   681,   682,   682,
     682,   682,   682,   682,   682,   683,   684,   684,   684,   685,
     685,   686,   687,   688,   689,   690,   691,   691,   692,   692,
     693,   693,   693,   694,   694,   694,   695,   696,   697,   697,
     698,   699,   700,   701,   699,   702,   702,   703,   703,   704,
     705,   704,   706,   706,   707,   707,   707,   707,   707,   707,
     707,   707,   707,   707,   707,   707,   707,   707,   707,   707,
     707,   707,   707,   707,   707,   707,   707,   707,   707,   707,
     707,   707,   707,   707,   708,   708,   708,   708,   708,   709,
     709,   709,   709,   709,   710,   711,   712,   713,   711,   714,
     715,   714,   716,   714,   717,   717,   718,   719,   719,   719,
     720,   720,   720,   720,   720,   721,   721,   722,   722,   723,
     724,   723,   725,   725,   726,   726,   726,   726,   726,   727,
     728,   729,   730,   731,   731,   733,   734,   732,   735,   735,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   738,
     737,   739,   739,   739,   739,   739,   739,   739,   739,   739,
     739,   739,   739,   739,   739,   739,   739,   739,   740,   740,
     740,   740,   740,   740,   741,   742,   742,   743,   743,   744,
     744,   745,   745,   745,   745,   745,   745,   745,   745,   745,
     745,   745,   745,   745,   745,   745,   745,   745,   746,   746,
     748,   747,   749,   749,   749,   750,   750,   751,   751,   753,
     752,   754,   754,   755,   755,   756,   757,   757,   758,   758,
     760,   759,   761,   762,   761,   763,   763,   764,   764,   765,
     765,   765,   765,   766,   766,   766,   767,   768,   767,   769,
     770,   769,   771,   771,   773,   772,   774,   774,   776,   775,
     777,   777,   778,   778,   778,   778,   778,   779,   779,   781,
     780,   782,   783,   783,   784,   784,   785,   786,   788,   787,
     789,   789,   791,   790,   792,   792,   792,   792,   792,   792,
     792,   792,   792,   793,   793,   793,   794,   794,   795,   795,
     795,   795,   795,   795,   795,   795,   795,   795,   795,   795,
     795,   795,   795,   796,   796,   798,   797,   799,   799,   799,
     799,   799,   800,   800,   802,   801,   804,   803,   805,   805,
     806,   806,   806,   807,   808,   808,   810,   809,   811,   812,
     811,   813,   813,   814,   814,   815,   815,   815,   815,   816,
     816,   817,   817,   819,   818,   820,   820,   820,   820,   820,
     820,   822,   821,   824,   823,   826,   825,   827,   827,   829,
     828,   831,   832,   830,   830,   833,   834,   833,   835,   835,
     837,   836,   838,   838,   839,   839,   839,   840,   840,   841,
     841,   842,   843,   843,   843,   843,   843,   843,   843,   844,
     844,   846,   845,   848,   847,   849,   849,   849,   850,   850,
     851,   851,   851,   853,   852,   854,   854,   855,   855,   855,
     855,   855,   855,   856,   857,   857,   858,   858,   859,   859,
     859,   859,   859,   860,   861,   862,   862,   863,   863,   865,
     864,   867,   866,   868,   868,   870,   869,   871,   871,   872,
     872,   874,   873,   875,   875,   876,   876,   876,   876,   877,
     877,   878,   878,   878,   880,   879,   881,   882,   881,   881,
     883,   883,   884,   884,   885,   885,   885,   885,   885,   886,
     886,   887,   887,   888,   890,   889,   891,   891,   892,   892,
     892,   892,   892,   892,   893,   893,   894,   894,   894,   895,
     895,   897,   896,   899,   898,   900,   900,   902,   901,   903,
     903,   903,   904,   904,   905,   907,   906,   908,   909,   908,
     910,   910,   911,   912,   911,   913,   913,   915,   914,   916,
     916,   918,   917,   919,   919,   919,   919,   919,   920,   921,
     921,   922,   923,   923,   924,   924,   925,   926,   926,   927,
     927,   929,   928,   931,   930,   932,   932,   933,   933,   934,
     934,   935,   935,   936,   936,   936,   937,   937,   937,   939,
     940,   938,   941,   941,   942,   942,   942,   942,   942,   943,
     943,   945,   944,   944,   946,   946,   946,   948,   947,   949,
     949,   950,   950,   950,   951,   951,   952,   952,   954,   953,
     955,   955,   955,   956,   956,   957,   958,   958,   960,   959,
     962,   961,   964,   963,   965,   965,   965,   967,   966,   968,
     968,   969,   969,   970,   971,   971,   972,   973,   973,   974,
     974,   975,   975,   976,   976,   977,   977,   977,   978,   979,
     979,   980,   980,   980,   980,   980,   981,   981,   982,   982,
     983,   983,   984,   984,   985,   985,   986,   986,   987,   988,
     988,   989,   991,   990,   992,   992,   993,   993,   993,   993,
     994,   994,   995,   995,   995,   996,   996,   997,   998,   999,
    1000,   999,  1001,  1002,  1001,  1003,  1004,  1005,  1004,  1006,
    1007,  1006,  1008,  1009,  1010,  1009,  1011,  1012,  1011,  1013,
    1013,  1013,  1015,  1014,  1017,  1016,  1018,  1018,  1018,  1020,
    1019,  1022,  1021,  1023,  1023,  1024,  1024,  1024,  1026,  1025,
    1028,  1027,  1029,  1029,  1030,  1031,  1033,  1032,  1034,  1034,
    1034,  1034,  1034,  1034,  1034,  1034,  1034,  1034,  1034,  1034,
    1034,  1035,  1035,  1035,  1035,  1035,  1035,  1035,  1035,  1035,
    1035,  1035,  1035,  1035,  1035,  1035,  1035,  1035,  1035,  1035,
    1035,  1035,  1035,  1035,  1035,  1035,  1035,  1036,  1036,  1036,
    1037,  1037,  1038,  1038,  1039,  1039,  1040,  1040,  1041,  1041,
    1042,  1042,  1042,  1043,  1043,  1043,  1043,  1043,  1043,  1043,
    1043,  1043,  1044,  1044,  1045,  1045,  1046,  1047,  1048,  1049,
    1049,  1050,  1051,  1051,  1052,  1053,  1053,  1054,  1055,  1055,
    1055,  1056,  1057,  1057,  1058,  1059,  1059,  1060,  1060,  1061,
    1062,  1062,  1063,  1063,  1064,  1064,  1065,  1065,  1065,  1065,
    1065,  1065,  1065,  1065,  1065,  1066,  1066,  1066,  1066,  1066,
    1066,  1066,  1067,  1067,  1068,  1068,  1069,  1069,  1070,  1070,
    1071,  1071,  1072,  1072,  1072,  1073,  1073,  1073,  1074,  1075,
    1075,  1075,  1075,  1076,  1076,  1077,  1078,  1078,  1079,  1080,
    1080,  1081,  1081,  1082,  1082,  1082,  1082,  1082,  1082,  1082,
    1083,  1083,  1083,  1083,  1083,  1083,  1083,  1083,  1083,  1083,
    1083,  1083,  1084,  1084,  1084,  1085,  1085,  1086,  1086,  1087,
    1087,  1087,  1088,  1088,  1089,  1089,  1090,  1091,  1091,  1092,
    1092,  1093,  1093,  1094,  1094,  1094,  1095,  1095,  1096,  1096,
    1097,  1097,  1098,  1098,  1099,  1099,  1100,  1100,  1101,  1101,
    1102,  1102,  1103,  1103,  1104,  1104,  1105,  1105,  1106,  1106,
    1107,  1107,  1108,  1108,  1109,  1109,  1110,  1110,  1111,  1111,
    1112,  1112,  1113,  1113,  1114,  1114,  1115,  1115,  1116,  1116,
    1117,  1117,  1118,  1118,  1119,  1119,  1120,  1120,  1120,  1121,
    1121,  1122,  1122,  1122,  1123,  1123,  1124,  1124,  1125,  1125,
    1126,  1126,  1127,  1127,  1128,  1128,  1128,  1129,  1129,  1130,
    1130,  1131,  1131,  1132,  1132,  1133,  1133,  1134,  1134,  1135,
    1135,  1135,  1136,  1136,  1137,  1137,  1138,  1138,  1139,  1139,
    1140,  1140,  1141,  1141,  1142,  1142,  1143,  1143,  1144,  1144
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
       1,     3,     1,     2,     4,     4,     4,     4,     3,     3,
       2,     2,     2,     0,     3,     0,     2,     1,     2,     1,
       1,     5,     0,     1,     1,     1,     5,     1,     2,     2,
       0,     2,     0,     9,     0,     0,     5,     0,     3,     0,
       2,     3,     2,     2,     1,     1,     0,     4,     0,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     0,     1,     1,     4,     6,     9,     0,     3,
       0,     2,     0,     2,     3,     1,     1,     5,     5,     1,
       1,     3,     5,     0,     2,     1,     1,     1,     5,     4,
       3,     4,     3,     3,     3,     0,     0,     5,     0,     1,
       0,     2,     3,     4,     2,     1,     0,     4,     1,     0,
       1,     1,     1,     0,     2,     1,     3,     3,     6,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     0,     2,     2,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     2,     2,     1,     2,     2,
       1,     2,     2,     1,     2,     2,     1,     1,     3,     3,
       7,     0,     2,     0,     3,     1,     0,     5,     1,     1,
       0,     3,     1,     2,     1,     2,     2,     0,     1,     1,
       3,     1,     0,     8,     1,     2,     1,     3,     0,     3,
       2,     4,     2,     0,     0,     5,     0,     0,     5,     0,
       0,     5,     0,     1,     1,     2,     5,     0,     2,     2,
       3,     1,     1,     2,     2,     2,     0,     1,     1,     2,
       8,     0,     3,     0,     4,     0,     4,     0,     3,     0,
       3,     1,     4,     2,     1,     1,     0,     2,     4,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     4,     4,     2,     1,     1,
       2,     3,     1,     3,     6,     2,     3,     2,     1,     2,
       2,     1,     2,     0,     1,     1,     4,     2,     0,     1,
       1,     0,     0,     0,     6,     0,     1,     1,     2,     1,
       0,     5,     0,     2,     1,     1,     1,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     5,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     0,     1,     1,     1,     1,     0,
       1,     1,     1,     1,     3,     0,     0,     0,     9,     0,
       0,     3,     0,     3,     1,     2,     4,     0,     2,     2,
       0,     3,     3,     4,     3,     0,     1,     0,     2,     0,
       0,     7,     0,     2,     1,     1,     1,     2,     2,     4,
       2,     1,     1,     0,     1,     0,     0,     3,     0,     2,
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
       0,     3,     0,     1,     0,     3,     0,     2,     0,     3,
       0,     3,     0,     1,     3,     3,     2,     1,     1,     0,
       4,     4,     0,     1,     1,     1,     1,     1,     0,     6,
       0,     1,     0,     4,     3,     3,     3,     3,     4,     6,
       6,     6,     6,     0,     2,     2,     1,     2,     1,     1,
       2,     2,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     1,     1,     0,     1,     0,     4,     4,     6,     6,
       8,     8,     0,     1,     0,     4,     0,     5,     1,     3,
       1,     1,     1,     2,     1,     2,     0,     3,     0,     0,
       3,     2,     3,     1,     3,     2,     1,     1,     1,     0,
       2,     0,     1,     0,     3,     0,     1,     1,     2,     1,
       1,     0,     3,     0,     3,     0,     5,     0,     3,     0,
       2,     0,     0,     8,     3,     0,     0,     3,     0,     1,
       0,     7,     0,     2,     0,     3,     3,     0,     2,     1,
       2,     4,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     0,     3,     0,     4,     1,     1,     1,     1,     2,
       1,     1,     1,     0,     3,     1,     2,     2,     2,     1,
       1,     1,     2,     2,     1,     2,     4,     2,     0,     1,
       1,     1,     1,     4,     5,     0,     4,     0,     1,     0,
       3,     0,     3,     3,     4,     0,     4,     4,     6,     0,
       1,     0,     3,     0,     5,     1,     1,     1,     1,     0,
       3,     0,     3,     2,     0,     3,     2,     0,     4,     2,
       0,     1,     1,     3,     0,     1,     2,     3,     3,     0,
       3,     1,     3,     7,     0,    10,     0,     2,     0,     2,
       2,     3,     3,     2,     0,     3,     0,     1,     1,     0,
       1,     0,     4,     0,     7,     0,     1,     0,     7,     0,
       2,     3,     0,     1,     1,     0,     4,     4,     0,     7,
       0,     2,     0,     0,     4,     1,     2,     0,     4,     0,
       1,     0,     3,     1,     1,     1,     1,     1,     4,     4,
       3,     4,     1,     1,     1,     2,     3,     1,     2,     3,
       3,     0,     3,     0,     7,     0,     5,     0,     2,     0,
       2,     0,     3,     0,     2,     4,     0,     2,     4,     0,
       0,     7,     0,     4,     2,     2,     2,     2,     2,     0,
       1,     0,     4,     2,     0,     2,     2,     0,     8,     1,
       2,     1,     3,     3,     0,     3,     0,     1,     0,     4,
       4,     6,     6,     0,     1,     2,     0,     1,     0,     3,
       0,     7,     0,     4,     0,     1,     1,     0,     9,     0,
       3,     1,     3,     2,     2,     2,     3,     0,     3,     0,
       3,     0,     3,     0,     1,     1,     1,     1,     8,     0,
       1,     1,     1,     1,     1,     1,     0,     1,     0,     1,
       1,     1,     1,     1,     1,     1,     0,     1,     5,     1,
       2,     5,     0,     8,     0,     2,     0,     4,     3,     3,
       1,     1,     0,     1,     1,     0,     1,     2,     2,     0,
       0,     3,     0,     0,     3,     2,     0,     0,     3,     0,
       0,     3,     2,     0,     0,     3,     0,     0,     3,     1,
       1,     2,     0,     3,     0,     3,     1,     1,     2,     0,
       3,     0,     3,     0,     1,     1,     1,     2,     0,     3,
       0,     3,     0,     3,     1,     1,     0,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     0,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     1,     2,     1,
       1,     2,     1,     2,     1,     5,     1,     5,     1,     3,
       0,     1,     1,     1,     3,     3,     3,     3,     2,     2,
       3,     3,     1,     3,     1,     2,     2,     1,     1,     1,
       2,     1,     1,     2,     1,     0,     2,     1,     1,     1,
       3,     1,     1,     2,     1,     0,     1,     1,     1,     1,
       1,     2,     1,     3,     1,     2,     1,     3,     3,     3,
       4,     3,     1,     1,     1,     1,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     3,     1,     3,     3,     4,     5,     1,     1,
       2,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     5,     5,     5,     5,     5,     5,     5,     4,
       5,     2,     0,     4,     5,     0,     3,     0,     1,     1,
       3,     3,     1,     3,     1,     3,     0,     0,     1,     0,
       1,     0,     1,     0,     1,     1,     0,     1,     0,     1,
       0,     1,     0,     2,     1,     1,     2,     2,     2,     1,
       2,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     1,     0,
       1,     0,     1,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     2,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     2,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     3,     4,     6,     7,
      38,    38,     0,     0,     5,     0,     8,    14,    28,    27,
      29,    29,     0,   252,   252,     0,     0,    24,    40,     0,
       9,    15,    30,    26,  1484,     0,   151,     0,   585,   585,
    1485,     0,     0,     0,     0,     0,     0,    39,   254,     0,
      17,     0,    25,    33,    37,    36,  1509,    35,    42,   153,
       0,   155,   264,   265,     0,   315,   257,   589,    18,    20,
      38,     0,    16,    34,  1510,    32,    41,   159,   157,   235,
       0,     0,   433,     0,   592,   590,   607,     0,    19,    10,
      11,     0,     0,     0,     0,     0,    43,    44,    45,    47,
      46,   154,     0,   233,  1476,   242,   156,     0,   237,   239,
     240,   255,     0,     0,   436,  1321,   258,   318,   266,   597,
     597,     0,     0,     0,   252,    23,    56,    71,    49,    80,
    1438,   160,   159,     0,   152,  1477,  1526,   243,   244,   245,
    1458,   236,   238,   259,   316,     0,     0,   439,   263,     0,
     262,   319,  1426,   268,  1467,   597,   594,   600,     0,   597,
     608,   586,    21,    12,     0,  1484,    54,  1509,    55,  1509,
      60,    62,    63,    64,     0,     0,    70,     0,    73,  1539,
      48,     0,  1538,     0,     0,  1484,  1484,     0,     0,  1517,
    1484,  1484,  1484,  1484,  1484,     0,  1484,  1470,  1484,    79,
       0,    82,    84,    85,    86,    88,    87,    89,    90,    91,
      92,    93,    94,  1439,     0,   158,   235,  1527,  1472,  1459,
    1478,   256,   318,   434,     0,     0,   531,   318,   321,     0,
    1484,   595,  1484,     0,   605,   598,   599,   609,   585,  1484,
       0,    57,  1509,    59,    61,     0,  1451,  1484,     0,    77,
       0,    72,    74,    52,    50,     0,     0,  1339,   106,     0,
       0,  1484,  1484,  1518,  1484,     0,     0,     0,     0,     0,
    1484,     0,  1471,     0,     0,    81,    83,   161,   234,  1473,
       0,  1479,     0,   260,   317,   318,   437,     0,     0,   253,
     261,   324,     0,   328,     0,   329,   325,  1472,  1484,     0,
       0,  1484,  1472,  1496,  1484,  1456,     0,   267,   269,   272,
     273,   274,   275,   276,   277,   278,   279,   280,     0,     0,
    1484,   606,     0,     0,   587,    17,     0,  1388,    69,    58,
    1450,     0,    76,    75,    78,    51,    53,  1484,    98,    99,
       0,     0,     0,  1383,   147,  1334,   146,   100,   101,   150,
       0,   149,   133,  1486,   135,    95,    96,   163,   246,   247,
     250,   241,  1319,   435,   318,   440,     0,     0,   322,   330,
     331,   326,     0,     0,     0,  1484,  1456,     0,     0,     0,
       0,     0,  1497,  1484,     0,  1457,     0,     0,   270,   271,
     601,   602,   604,     0,   596,   610,   612,     0,     0,    68,
       0,  1397,  1393,  1398,  1396,  1394,  1399,  1395,   139,   140,
     142,   148,   145,  1444,  1445,     0,   144,  1488,  1487,   136,
       0,   102,  1511,   248,     0,   249,  1320,   438,   442,   532,
     323,   339,   333,   292,   312,  1446,  1447,   301,  1332,   296,
     295,   294,  1338,  1337,  1494,  1470,  1482,     0,   530,   313,
     314,  1484,  1484,   603,   612,     0,     0,    13,    66,    67,
      65,   111,   125,   121,   126,   108,   124,   122,   109,   110,
     123,   107,   112,   113,   115,   141,     0,  1384,   134,   137,
      97,  1496,     0,  1534,   220,     0,  1496,  1484,  1468,  1489,
     222,     0,  1538,   207,   206,   162,   164,   165,   166,   167,
     168,   169,     0,   170,   171,   219,   172,   173,   174,   175,
     176,   177,  1484,  1464,   251,     0,   441,   443,   444,   533,
    1484,  1460,     0,     0,   282,  1333,  1495,   303,     0,   285,
    1483,  1522,   311,     0,     0,     0,     0,   622,   613,   614,
     615,   616,   621,     0,     0,   114,   117,     0,   143,   138,
     105,   104,  1524,  1484,  1489,  1535,   184,   223,  1484,  1511,
    1469,  1484,  1484,  1490,  1484,  1484,  1458,     0,  1484,     0,
    1465,     0,   447,   445,   535,     0,   421,   363,   396,   384,
     393,   390,   387,  1536,   364,   365,   366,   367,   368,   369,
     370,   371,   372,  1513,   397,     0,   373,   360,   374,   375,
       0,     0,  1520,   377,   378,   376,   417,   380,   381,   379,
    1484,  1486,   340,   341,   342,   343,   344,   345,   361,   346,
     347,   348,   349,   350,   351,   352,   353,   354,     0,     0,
    1461,     0,   334,   293,   284,   283,   281,   302,  1470,  1523,
     290,   299,   298,   300,   297,     0,   618,   620,   623,   679,
     730,   739,   746,   750,   774,   778,   796,   789,   797,   798,
     802,   835,   844,   846,   873,   881,   883,  1534,   889,     0,
     900,   921,   923,   959,   961,   965,   678,   971,   984,  1004,
    1021,  1023,  1027,  1034,  1035,  1051,  1071,  1089,     0,  1107,
    1118,  1126,  1128,  1130,  1132,  1137,  1159,  1182,   617,   629,
     630,   631,   632,   633,   634,   635,   636,   638,   637,   639,
     640,   641,   642,   643,   644,   645,   646,   647,   648,   649,
     650,   651,   652,   653,   654,   655,   656,   657,   658,   659,
     660,   661,   662,   663,   664,   665,   666,   667,   668,   669,
     670,   671,   672,   673,   674,   675,   676,  1155,  1156,  1157,
     677,    22,     0,   116,  1525,  1484,     0,  1484,   186,   185,
     181,     0,  1512,   222,   218,     0,     0,     0,     0,   228,
    1507,  1507,     0,   229,     0,   203,   221,  1484,   329,   539,
     534,   536,   537,   432,   394,   395,   382,   383,   391,   392,
     388,   389,   385,   386,  1537,     0,  1514,   415,   401,   355,
    1379,   430,  1521,   418,   419,   416,     0,     0,   357,   359,
    1442,  1442,     0,  1500,  1500,   338,   335,  1389,  1391,  1463,
     304,   305,   306,   307,     0,     0,   286,  1481,   292,     0,
       0,   624,     0,     0,     0,  1246,   745,     0,   776,   780,
       0,     0,     0,     0,     0,  1246,   875,     0,     0,   885,
     890,     0,  1246,     0,     0,     0,     0,     0,     0,   973,
     994,     0,     0,     0,     0,     0,     0,     0,     0,  1103,
    1101,     0,     0,  1127,  1125,     0,     0,     0,     0,  1160,
    1166,     0,     0,   131,   127,   132,   130,   128,   129,   118,
     119,     0,   192,   193,   191,   190,     0,   179,   180,     0,
     212,   211,   212,   208,   224,   225,   226,   227,  1508,   230,
     231,   232,  1335,  1484,   456,   456,  1486,   476,   448,   451,
     452,     0,   540,   538,   420,     0,  1532,     0,  1380,  1381,
       0,   362,   422,   424,   426,     0,   356,  1468,   398,   399,
    1390,  1501,     0,     0,     0,     0,     0,  1462,  1470,   291,
     611,   619,   728,   698,  1378,  1500,     0,     0,  1412,  1415,
    1500,  1312,     0,     0,     0,     0,     0,     0,     0,     0,
    1412,   737,  1354,   735,  1344,  1346,  1352,  1353,  1431,   740,
       0,  1245,  1261,  1331,     0,  1327,  1329,  1328,  1373,   752,
    1372,  1374,   775,   779,   792,     0,  1314,  1440,  1511,  1393,
     833,   698,     0,  1346,   842,     0,   752,   852,   851,  1454,
     848,   850,   880,   877,   876,   879,   874,  1500,   882,  1340,
    1342,   884,  1325,   894,  1530,  1244,   902,   922,   458,     0,
     925,   926,   927,   960,  1075,     0,   962,     0,   969,     0,
     972,   995,  1331,   985,   994,   987,     0,   992,     0,  1328,
       0,  1433,  1184,  1317,  1511,  1184,     0,  1049,  1040,  1318,
       0,  1324,  1052,  1053,  1054,  1055,  1056,  1064,  1057,  1067,
       0,  1322,     0,  1072,  1090,  1104,  1466,     0,  1109,  1111,
       0,  1123,     0,  1129,     0,  1134,  1139,  1167,     0,  1168,
    1502,  1184,     0,   103,  1429,   188,   187,   178,   189,     0,
     210,   209,  1336,   204,     0,   457,   453,     0,   454,     0,
     446,   449,   542,   402,  1533,   403,  1500,     0,     0,     0,
    1300,  1298,  1361,  1303,  1355,  1359,  1360,     0,  1382,   431,
    1536,   425,     0,   358,  1443,   337,   336,  1392,   310,  1494,
       0,   288,   729,   680,  1463,     0,   707,     0,     0,     0,
       0,     0,  1400,  1417,  1411,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1401,   738,   731,     0,     0,
    1345,  1432,   743,  1431,  1247,     0,   748,     0,   753,   763,
    1371,   777,  1370,   782,   793,   790,   795,   794,  1246,  1315,
    1441,  1316,  1233,   834,   803,   813,  1199,  1199,  1199,  1199,
     843,   836,     0,     0,   845,  1455,  1246,   871,   858,   854,
     856,  1246,   878,     0,  1341,   887,  1531,   892,   904,     0,
     459,     0,   948,   933,   924,   928,   930,   931,   932,  1079,
       0,     0,   970,   966,     0,   978,   975,   977,   976,   979,
     986,   989,   625,  1246,     0,     0,   996,     0,  1434,  1435,
    1511,     0,  1022,  1006,  1029,  1042,  1050,  1036,     0,  1042,
       0,  1366,  1367,  1065,  1068,     0,     0,  1323,  1063,     0,
    1062,     0,  1092,     0,     0,  1102,     0,     0,  1110,     0,
    1124,  1119,     0,     0,  1135,  1136,  1133,  1466,     0,     0,
    1169,     0,  1503,     0,  1029,   120,  1449,  1484,     0,   202,
     196,   194,  1430,     0,   215,   450,   455,   461,   471,   329,
     477,  1519,  1502,   406,     0,  1308,  1309,     0,  1301,  1302,
    1385,     0,     0,     0,     0,     0,     0,     0,     0,  1515,
     427,   309,  1494,  1502,   287,   703,   694,  1199,   684,   691,
     685,   687,   689,     0,  1199,     0,   683,   690,   697,   696,
       0,  1199,  1498,  1498,  1498,   701,   702,  1363,  1362,     0,
    1351,  1300,  1298,     0,     0,  1300,     0,  1347,  1348,  1349,
    1313,  1300,     0,     0,  1300,     0,     0,  1300,  1300,  1300,
       0,     0,  1206,  1440,     0,     0,   741,     0,  1253,  1254,
    1255,  1285,  1256,  1534,  1289,  1294,  1528,  1248,  1296,  1528,
    1278,  1258,  1260,  1252,  1251,  1286,  1257,  1259,  1268,  1269,
    1270,  1271,  1272,  1287,  1250,  1290,  1292,  1273,  1274,  1275,
    1276,  1277,  1262,  1284,  1267,  1264,  1265,  1266,  1263,  1279,
    1280,  1281,  1282,  1283,  1249,     0,     0,  1330,   759,     0,
       0,   766,   787,   788,   781,   783,     0,  1206,  1238,  1240,
     800,  1234,  1235,  1236,     0,  1539,  1199,     0,  1200,   806,
    1202,   807,   804,   805,     0,  1206,  1440,   866,   868,   867,
     861,   863,   869,   872,   847,   859,   855,   853,  1246,   625,
     849,  1343,  1502,   886,  1326,   625,  1534,   912,   913,   915,
     917,   918,   914,   916,   907,  1534,   903,     0,   949,     0,
     951,   950,   952,   943,   944,     0,     0,   929,  1081,  1504,
       0,     0,   963,  1206,  1440,  1538,     0,   990,   626,   997,
     998,  1001,     0,   993,  1191,  1190,  1000,  1006,  1185,     0,
       0,  1233,     0,     0,     0,  1041,     0,     0,     0,  1066,
       0,  1070,  1069,  1060,     0,  1484,  1233,  1106,  1105,  1112,
    1113,  1114,     0,  1206,  1440,     0,  1427,     0,  1114,  1181,
    1171,  1170,  1176,     0,  1178,  1179,  1186,   201,  1448,  1429,
       0,     0,  1484,   463,   474,   475,   473,   331,   479,   555,
    1484,   546,   544,   545,   547,  1498,     0,  1484,     0,   558,
     550,  1498,   551,     0,   554,   559,   557,   552,   556,     0,
     553,     0,   541,   569,   564,   567,   566,   565,   568,   543,
     570,     0,   410,   405,  1356,  1357,  1358,  1311,  1299,  1304,
    1305,  1306,  1307,  1310,  1386,     0,  1516,  1534,   308,     0,
     695,  1202,   686,   688,  1199,   692,   682,   722,  1484,   711,
     712,  1484,   723,   713,   714,   717,   727,   724,   715,     0,
     725,   716,   726,   708,   709,   681,  1499,     0,     0,     0,
     699,   700,  1365,  1350,  1364,  1412,  1440,     0,  1416,     0,
    1412,  1412,     0,  1409,  1412,  1412,  1412,     0,  1412,  1412,
    1207,   732,  1209,  1206,   744,     0,  1288,  1529,  1291,  1293,
     749,   747,   754,   755,   600,     0,   765,   764,  1172,  1173,
     769,   767,     0,   786,     0,   791,   625,   625,   801,   799,
    1237,   813,   813,   813,   813,  1484,   818,   831,   832,   819,
       0,  1484,   822,   823,   826,   824,     0,   825,   815,   816,
     808,   814,   625,  1203,  1198,     0,   837,     0,  1246,  1246,
     865,   625,   862,   857,     0,   895,     0,     0,   919,     0,
       0,     0,   945,   947,     0,   939,   955,   940,   941,   934,
     935,   955,  1073,  1484,     0,  1505,  1080,   408,   409,  1489,
     964,   967,     0,     0,   981,   991,   988,   628,     0,     0,
    1008,  1007,  1222,  1224,  1025,  1219,  1220,  1032,  1030,     0,
    1246,  1043,  1246,  1037,  1045,  1058,  1059,  1061,  1436,  1099,
    1213,     0,  1440,  1120,     0,     0,  1428,  1140,  1141,     0,
    1144,  1147,  1151,  1145,  1177,  1502,  1180,  1192,  1452,   198,
     199,   195,   197,     0,   216,   217,   213,     0,     0,   465,
       0,  1519,     0,  1484,   548,   549,     0,   572,  1484,  1532,
     573,   571,   404,  1466,   400,  1489,  1387,   428,   289,  1197,
     693,     0,     0,  1242,  1242,   710,   705,   704,   706,  1405,
    1206,  1413,     0,  1425,  1410,  1403,  1423,  1404,  1406,  1407,
    1420,  1421,  1408,  1402,   625,  1210,  1205,   733,   742,     0,
       0,   756,   757,     0,   761,   760,   762,  1174,  1175,   772,
     770,   625,   784,   785,  1239,  1241,  1199,  1199,  1199,  1199,
       0,   820,   821,     0,  1242,  1242,   817,  1201,   625,  1206,
    1314,  1206,  1314,   864,   870,   860,   888,   896,   898,   905,
     908,   909,  1474,   920,   901,   906,   955,  1368,  1369,   955,
       0,   938,   936,   937,   942,  1083,     0,  1506,  1077,  1206,
     980,   974,     0,   627,  1002,     0,     0,  1014,     0,   625,
     625,  1026,  1024,  1221,  1033,  1028,  1031,  1038,   625,  1047,
    1046,  1437,     0,     0,  1100,  1091,  1214,  1116,  1216,     0,
    1206,  1206,  1131,  1427,  1143,  1482,  1149,  1482,  1213,     0,
    1229,  1231,  1195,  1193,  1226,  1227,  1194,  1453,     0,   214,
     462,  1484,     0,   467,   472,  1498,   508,   528,   523,  1456,
       0,     0,  1484,  1500,  1484,     0,   478,   484,   485,   486,
     495,   487,   489,   492,   480,   481,   482,   488,   491,   509,
     493,   496,   483,     0,   490,   494,  1377,   563,  1375,  1376,
     579,   562,   574,   584,     0,  1484,  1484,   423,   719,   718,
     721,     0,   720,   734,  1414,  1208,   625,  1534,  1534,   758,
     773,   751,   625,   768,   812,   811,   810,   809,   828,   827,
     830,   829,  1204,   839,     0,   838,     0,   625,   899,   893,
     910,  1475,     0,   954,   946,   955,   957,     0,     0,  1086,
    1082,  1076,   968,   983,     0,     0,  1009,  1484,  1016,     0,
    1010,     0,  1013,  1223,  1225,   625,  1044,   625,  1093,  1094,
    1095,  1096,  1097,  1098,   625,  1117,  1108,  1217,  1212,  1115,
    1122,  1121,  1142,     0,  1482,  1146,     0,  1153,  1165,  1162,
    1164,  1163,  1158,  1161,   625,   625,  1196,  1183,  1228,  1189,
    1188,  1491,     0,  1484,  1484,   469,   507,  1484,   529,   527,
     524,   525,  1486,   517,  1484,  1246,     0,     0,     0,     0,
     510,     0,     0,   515,   518,   521,   582,   580,   581,   583,
       0,   577,   575,   576,   578,     0,   414,   411,   412,     0,
       0,  1491,  1211,  1295,  1297,   771,  1206,  1206,   897,     0,
     953,   958,     0,  1484,  1084,     0,     0,  1074,  1078,   982,
       0,     0,  1019,  1017,  1018,  1012,  1011,  1039,  1048,  1215,
     625,  1148,     0,  1152,  1154,  1138,  1230,  1232,  1492,  1493,
    1187,   464,     0,     0,  1484,   460,     0,   516,     0,   513,
    1440,   511,   512,   502,   500,   501,   503,   499,   504,   498,
     497,     0,   522,   520,   519,   561,   560,   413,   407,   429,
    1243,   841,   840,   911,   956,     0,  1087,  1484,  1246,  1015,
    1020,  1005,  1218,  1150,   466,   468,     0,   506,   505,   526,
       0,  1085,     0,  1003,   470,     0,  1088,   514
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,     7,     8,    23,    38,    68,   124,
     238,     9,    24,    39,    69,    89,   457,    72,    70,    34,
      11,    20,    26,    41,    56,    57,    16,    36,    76,    96,
      97,   180,   181,   167,    98,   168,   169,   170,   171,   460,
     172,   173,    99,   176,   177,   178,   250,   100,   199,   200,
     201,   202,   421,   480,   552,   203,   337,   471,   472,   473,
     752,   889,   474,   890,   204,   352,   353,   478,   205,   408,
     409,   206,   207,   208,   209,   210,   211,   212,    47,    77,
      79,   103,   101,   131,   357,   422,   496,   497,   899,   760,
    1097,   498,   895,   499,  1569,  1570,  1819,  1300,   500,   501,
     502,   503,   903,  1100,  1826,   504,   505,   506,   507,   508,
     509,   510,   511,   773,   134,   106,   107,   108,   109,   140,
     110,   358,   359,   425,    30,    65,   143,    83,   221,   148,
     116,   149,   117,   153,   230,   308,   309,   636,   310,  1334,
     828,   524,   311,   441,   312,   642,   313,   314,   637,   820,
     821,   822,   823,   315,   316,   317,    82,   222,   150,   151,
     152,   228,   294,   431,   295,   371,   372,   521,   815,   296,
     520,   612,   613,   614,   936,   615,   616,   617,   618,   619,
     620,   926,  1313,  1612,  1613,  1769,  1844,  2167,  2168,   621,
     622,   805,   623,   624,   625,  1130,   932,   933,  2037,   626,
     627,   114,   285,   147,   364,   226,   428,   516,   517,   518,
     777,   918,   919,  1106,  1107,  1027,   920,  1573,  1829,  1993,
    2135,  2215,  1307,  1576,  1110,  1310,  1831,  2014,  2015,  2230,
    2016,  2017,  2018,  2019,  2221,  2020,  2021,  2022,  2023,  2153,
    2154,  2142,  2024,  2025,  2139,   449,   289,   519,   574,   780,
     781,   782,  1112,  1311,  1609,  2165,  2160,  1610,    50,   237,
     396,    86,   120,   119,   155,   156,   157,   234,   322,   122,
     324,   454,   455,   538,   539,   540,   541,   542,   832,  1517,
    1518,  1777,   543,   699,   700,   833,   952,  1146,  1355,  1356,
    1351,  1653,  1654,  1143,   701,   834,   971,  1169,  1167,   702,
     835,   979,  1386,   703,   836,  1436,   704,   837,  1179,  1438,
    1692,  1693,  1694,  1441,  1700,  1891,  1889,  2052,  2051,   705,
     838,   992,   706,   839,   993,  1444,  1445,   707,   840,   994,
    1185,  1188,   708,   709,   710,   841,  1709,   711,   842,  1000,
    1456,  1728,  1729,  1194,   712,   843,  1004,  1201,   713,   844,
     714,   845,  1009,  1010,  1207,  1208,  1209,  1479,  1477,  1741,
    1210,  1470,  1471,  1740,  1474,   715,   846,  1016,   716,   847,
     717,   848,   718,  1022,  1483,   719,   850,   720,   852,  1485,
    1918,  2067,  2069,   721,   853,  1218,  1494,  1748,  1920,  1921,
    1922,  1924,   722,   854,   723,   855,  1029,  1224,  1225,  1226,
    1506,  1759,  1760,  1227,  1503,  1504,  1505,  1753,  1228,  1931,
    2182,   724,   856,   725,   857,  1036,   726,   858,  1038,  1233,
     727,   859,  1040,  1239,  1516,  1941,   728,   860,  1043,  1242,
    1776,  1044,  1045,  1046,  1520,  1521,   729,   861,  1530,  1947,
    2088,  2192,  2251,   730,   862,   731,   863,  1952,   732,   864,
    1531,  1955,   733,   734,   865,  1057,  2095,  1259,  1533,  1958,
    1793,  1794,  2097,  1257,   735,   866,  1062,  1063,  1064,  1065,
    1271,  1066,  1067,  1068,  1069,   736,   867,  1033,  1935,  1229,
    2081,  1508,  1762,  2079,  2187,   737,   868,  1272,  1546,  1962,
    1965,   738,  1075,  1275,   739,   871,  1077,  1078,  1800,  2106,
     740,   872,  1081,  1281,   741,   874,   742,   875,   743,   876,
     744,   877,  1286,   745,   878,  1288,  1807,  1808,  1558,  1810,
    1976,  2115,  1978,  2205,   746,   747,   880,  2122,  1089,  1291,
    1562,  1701,  1890,  1815,   748,  1564,   749,   750,   882,  1252,
    1817,  2076,  1982,  2127,  1630,  1459,  1460,  1732,  1734,  1908,
    1681,  1682,  1874,  1876,  2046,  1967,  1968,  2104,  2108,  2200,
    1784,  1785,  1949,  1786,  1950,  1983,  1984,  2124,  1985,  2125,
    1450,  1451,  1452,  1706,  1453,  1707,  2040,  1024,  1025,   981,
     982,  1174,  1175,  1417,  1418,  1419,  1420,  1421,  1120,  1321,
    1362,   972,   995,  1189,  1052,  1058,   361,   362,  1070,  1071,
    1215,  1047,   985,   986,   437,   443,  1103,   444,   258,  1018,
    1019,   973,   997,  1123,  1359,  1663,  1761,  1926,  1002,  1048,
    2027,   975,   954,   800,   928,   929,  2029,   976,   817,   818,
     977,  1152,  1154,  1366,  1380,  1375,  1372,   229,  1809,  1301,
    1172,  1250,  1963,   214,  1191,   938,   415,   377,  1302,   247,
    1988,  1738,   386,   220,   631,  1147,   571,   158,   561,   273,
     280,  2072,   136,   282,   829,   531,    42,   420,   564,  2210,
     527,   383,  1657,   942,  1293,  1766,   909,   174,   513,   797,
    1627,   264,   629,   640,   755,   218,  1688,  1217,  1115,   556,
     795,  1457
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1750
static const yytype_int16 yypact[] =
{
   -1750,   266,    53, -1750,  -136,  -113,    53, -1750, -1750, -1750,
     475,   475,   531,   531, -1750,   508, -1750, -1750, -1750, -1750,
     760,   760,   292,   967,   967,   727,   630, -1750,   989,   871,
   -1750, -1750, -1750, -1750,   -33,   753,   971,   676,   863,   863,
   -1750,   765,   165,   826,   832,   933,   844, -1750,    32,  1178,
     994,  1167, -1750,   -70, -1750, -1750,  1000, -1750, -1750, -1750,
     860, -1750, -1750, -1750,   964,   878, -1750,    61, -1750,    76,
     475,   531, -1750, -1750, -1750, -1750,   623, -1750,  1155,    -3,
     880,   981,  1098,   909, -1750, -1750,  1022,   531, -1750, -1750,
   -1750,   918,   919,   921,   923,   934, -1750, -1750, -1750, -1750,
   -1750,  1025,   939,  1166,   982,   775, -1750,   376, -1750, -1750,
   -1750, -1750,   940,  1043,  1170, -1750,   335,   968, -1750,   107,
     107,   970,   965,   969,   967, -1750,   200,  1235,    63,  1397,
    1138, -1750, -1750,   973, -1750, -1750,  1029, -1750, -1750, -1750,
    1393, -1750, -1750, -1750, -1750,   974,  1073,  1100, -1750,   909,
   -1750, -1750, -1750, -1750, -1750,    64, -1750,   -87,   541,   119,
   -1750, -1750, -1750, -1750,  1063,  1221, -1750,   378, -1750,   481,
   -1750, -1750, -1750, -1750,    90,   198, -1750,    16, -1750, -1750,
   -1750,   985,   -84,  1329,  1001,  1221,  1221,  1001,  1061,  1081,
    1221,  1221,  1221,  1221,  1221,  1001,  1221,  1377,  1221, -1750,
    1163, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750,  1001,  1025,    -3, -1750,  1373, -1750,
    1286,   335,   968, -1750,  1031,  1119,  1125,   968,   692,  1042,
     731, -1750,  1221,  1118,  1213, -1750, -1750,  1401,   863,  1221,
    1269, -1750,   563, -1750, -1750,  1165, -1750,  1221,  1327, -1750,
     843, -1750, -1750, -1750, -1750,  1092,  1297, -1750, -1750,  1001,
    1001,  1221,  1221, -1750,  1221,  1108,  1481,  1001,  1001,  1108,
    1221,  1108, -1750,  1001,    41, -1750, -1750, -1750, -1750, -1750,
     909, -1750,   909, -1750, -1750,   968, -1750,  1112,  1208, -1750,
   -1750, -1750,  1042, -1750,  1114,     0, -1750,  1373,  1221,   640,
     640,  1221,    48,  1319,  1221,  1540,  1295, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,   835,   757,
    1221, -1750,  1137,  1129, -1750,   994,  1269, -1750, -1750, -1750,
   -1750,  1108, -1750, -1750, -1750, -1750, -1750,  1221, -1750, -1750,
     961,  1108,  1343,   528, -1750, -1750, -1750, -1750, -1750, -1750,
    1108, -1750, -1750,   109, -1750, -1750, -1750, -1750,   909, -1750,
    1285,   909, -1750, -1750,   968, -1750,  1133,  1134, -1750, -1750,
    1500, -1750,  1501,  1269,  1151,  1221,  1540,  1108,   -36,    -7,
    1269,  1161, -1750,  1221,  1158, -1750,  1158,     6, -1750, -1750,
   -1750, -1750, -1750,  1269, -1750, -1750, -1750,   104,    36, -1750,
    1282, -1750, -1750, -1750, -1750, -1750, -1750, -1750,   961, -1750,
    1201, -1750, -1750, -1750, -1750,  1108, -1750, -1750, -1750, -1750,
    1269, -1750,   876, -1750,  1269, -1750, -1750, -1750,  1289, -1750,
   -1750, -1750,   881,  1199, -1750, -1750, -1750,  1108, -1750, -1750,
   -1750, -1750, -1750, -1750,  1372,    71,  1405,  1169, -1750, -1750,
   -1750,  1221,  1221, -1750, -1750,  2126,   531, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750,   689, -1750,    92, -1750,   961, -1750,  1269, -1750,
     931,  1319,  1292,  1209, -1750,  1250,  1319,  1221,  1552,   108,
     441,  1269,  1176, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750,  1236, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750,  1221,  1574, -1750,  1158, -1750,  1289, -1750, -1750,
    4245,  1590,  1441,  1269,   301, -1750, -1750, -1750,  1269, -1750,
   -1750,  1262, -1750,   118,   118,  2339,  1182,  1183, -1750, -1750,
   -1750, -1750,  1287,  2965,  1184, -1750, -1750,   689, -1750, -1750,
   -1750, -1750,  1258,  1221,  1423, -1750,   874, -1750,  1221,   815,
   -1750,  1221,  1221, -1750,  1221,  1221,  1393,   317,  1221,  1204,
   -1750,  1283, -1750, -1750,  1042,  1418, -1750, -1750,   -63,   624,
     631,   696,   711,  1211, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750,  1303, -1750,  1269, -1750, -1750, -1750, -1750,
    1108,  1108,  1433, -1750, -1750, -1750,   550, -1750, -1750, -1750,
    1221,   181, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,   966,   334,
   -1750,   208, -1750, -1750, -1750, -1750, -1750,   147,  1377, -1750,
     747, -1750, -1750, -1750, -1750,  1538, -1750, -1750,  1415, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750,  1209, -1750,  1356,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,    -4, -1750,
   -1750,  1347, -1750, -1750, -1750, -1750,   913, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750,   785, -1750, -1750,  1221,    62,  1221, -1750, -1750,
     526,   182, -1750, -1750, -1750,    -7,  1273,  1108,  1108, -1750,
    1368,  1368,  1375, -1750,  1108, -1750, -1750,   100,     0, -1750,
   -1750,  1042, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750,  1214, -1750, -1750,  1255, -1750,
    1205,  1266, -1750, -1750, -1750, -1750,  4719,    70,  1632, -1750,
    1307,  1307,   961,  1395,  1395, -1750, -1750,  1215, -1750, -1750,
   -1750, -1750, -1750, -1750,    66,  1496, -1750, -1750,  1199,  1269,
    1223, -1750,  1224,  1108,  3296,  1234,   394,  1070, -1750, -1750,
    3872,   909,  4009,  3872,  1443,   814,   884,    91,  1108, -1750,
   -1750,  1542, -1750,    91,  1108,  2172,  1108,  3397,  3872, -1750,
    4682,   909,  1108,   909,  1108,    93,    99,  1108,   909, -1750,
   -1750,  3477,  3614, -1750, -1750,  1108,  1108,   909,  1108, -1750,
     279,  1572,  1108, -1750, -1750, -1750, -1750, -1750, -1750,  1660,
   -1750,  1001, -1750, -1750, -1750, -1750,  1108,    21,   101,   124,
    1247, -1750,  1247, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750,  1108,  1221,  1512,  1512,   181, -1750, -1750, -1750,
   -1750,  1499, -1750, -1750, -1750,  1269,  1290,  4743,  1238, -1750,
    1108, -1750,    70, -1750,  1291,  1460, -1750,  1552, -1750, -1750,
   -1750, -1750,  1108,  1108,   961,    -7,    -7,  1661,  1377, -1750,
   -1750, -1750,  1575,   583, -1750,  1395,  1248,  1108,  1251,  1252,
    1395,   528,  1253,  1254,  1256,  1259,  1261,  1264,  1265,  1267,
    1251,  1580, -1750,  3558, -1750, -1750, -1750, -1750,  1507, -1750,
    1643, -1750, -1750, -1750,  1316, -1750,   528, -1750, -1750,  1293,
   -1750, -1750,   400,   909,  1589,   849, -1750,  1379,  1406,   817,
    1592,  1780,   856,   898,  1596,   170,  1293, -1750, -1750,   110,
   -1750, -1750, -1750,  1630, -1750, -1750, -1750,  1395,    91, -1750,
   -1750, -1750, -1750, -1750,  1337, -1750,    75,  1108, -1750,   254,
   -1750, -1750, -1750, -1750, -1750,  3872, -1750,  1334,  1597,  1682,
     889, -1750,  1339, -1750,  4774,  1600,   781,  1345,  1344,  -133,
    1350,    42,  1568, -1750,  1406,  1568,  1108,  1605,  1318, -1750,
     955, -1750, -1750, -1750, -1750, -1750,  1505, -1750,    91, -1750,
     499, -1750,    56, -1750, -1750,   443,  1698,  1869, -1750, -1750,
    1108,  1606,  3635,  1108,  1576,   912,  1644, -1750,  1428,  1387,
    1489,  1568,   785, -1750,    -1, -1750, -1750, -1750, -1750,   569,
   -1750, -1750, -1750, -1750,   400, -1750, -1750,  1108, -1750,  1269,
    1042, -1750, -1750, -1750, -1750,  1662,  1395,  4743,  4743,  4743,
      43,   930, -1750, -1750, -1750,  1215, -1750,  4743, -1750, -1750,
    1211, -1750,    70, -1750, -1750, -1750, -1750, -1750, -1750,  1372,
      -7,  1663, -1750, -1750,   955,  1594,  1338,   343,   269,  4743,
    1376,  4743, -1750,  4743, -1750,   800,  1341,  4743,  4743,  4743,
    4743,  4743,  4743,  4743,  4743, -1750, -1750, -1750,  3872,  1593,
   -1750, -1750,  1444,  1507,  1074,  2653,  1475,  1550, -1750,   473,
   -1750, -1750, -1750,   645, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750,    77, -1750, -1750,   465,  1621,  1621,  1621,  1621,
   -1750, -1750,  3872,  3872, -1750, -1750,    87,  1652,   906, -1750,
    1354,   814, -1750,  1108, -1750,    55, -1750, -1750,  1087,  1617,
   -1750,   955,   174, -1750,   254, -1750, -1750, -1750, -1750,   122,
    1390,    91, -1750, -1750,  3872, -1750, -1750, -1750, -1750,  1430,
   -1750, -1750, -1750, -1750,  1108,   394, -1750,  1102, -1750, -1750,
    1406,   400, -1750,  1587,   501,   250, -1750, -1750,  1108,   250,
    1398, -1750,  1215, -1750, -1750,    65,   931, -1750, -1750,  3219,
   -1750,  1745,  1585,  3872,  3872, -1750,  3743,  1108, -1750,  1624,
   -1750, -1750,  3872,   955, -1750, -1750, -1750,  1698,  1595,  1108,
   -1750,  1057, -1750,    73,   501, -1750, -1750,  1221,  1684, -1750,
   -1750, -1750, -1750,  1532, -1750, -1750,  1108,  1620,   658,     2,
   -1750,  4440,  1489, -1750,   800,  1364,  1364,  1021, -1750, -1750,
   -1750,  4743,  4743,  4743,  4743,  4743,  4743,  3961,   930,  1454,
   -1750, -1750,  1372,  1489, -1750, -1750, -1750,  1621, -1750, -1750,
    1374,  1378, -1750,   955,  1621,  1601, -1750, -1750, -1750, -1750,
    2534,  1621,  1551,  1551,  1551,   187,  1591, -1750, -1750,   442,
   -1750,    82,  1044,  1108,  1003,    95,  1370, -1750,  1215, -1750,
   -1750,   459,  1371,  1054,   582,  1380,  1086,   105,   140,   605,
    1383,  1109,  3792,   517,  3872,    91, -1750,  1483, -1750, -1750,
   -1750, -1750, -1750,  1209, -1750, -1750,  1432, -1750, -1750,  1432,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750,  1425,   394, -1750,   148,  1108,
    1108,   535, -1750, -1750, -1750,    28,   928,  1458, -1750, -1750,
    1697, -1750,  1567, -1750,    23,  1351,  1621,  1566, -1750, -1750,
    1577, -1750, -1750, -1750,  1650,  3792,   551, -1750, -1750, -1750,
    2559, -1750,  1445, -1750, -1750, -1750, -1750, -1750,    87, -1750,
   -1750, -1750,  1489, -1750, -1750, -1750,  1209, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750,  1510,  1209, -1750,  1446, -1750,  1789,
   -1750, -1750, -1750,   123, -1750,   955,  1071, -1750,    90,    54,
     855,    91,    91,  3792,   575,  1176,   909,  1705, -1750, -1750,
    1834, -1750,  1669, -1750, -1750, -1750, -1750,  1587, -1750,  1108,
     591,    77,   943,  1417,  1725, -1750,  1419,   955,   821, -1750,
     442, -1750, -1750, -1750,  3872,  1221,    77, -1750, -1750, -1750,
   -1750,   -58,  1108,  3792,   614,  1455,  1842,  1108,   454, -1750,
   -1750, -1750,  1554,  1555, -1750, -1750,  1102, -1750, -1750,    44,
    1108,   617,  1221,  1685, -1750, -1750,  1269, -1750, -1750, -1750,
    1221, -1750, -1750, -1750, -1750,  1551,  1095,  1221,  1070, -1750,
   -1750,  1551, -1750,  1269, -1750, -1750, -1750, -1750, -1750,  1108,
   -1750,  1108, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750,  1108,  1664,   855, -1750,  1215, -1750, -1750,  1044,   904,
     904,  1364,  1364,  1364, -1750,  1126, -1750,  1209, -1750,  1108,
   -1750,  1577, -1750, -1750,  1621, -1750, -1750, -1750,  1221, -1750,
   -1750,  1221, -1750, -1750, -1750, -1750, -1750, -1750, -1750,   134,
   -1750, -1750, -1750,  2534, -1750, -1750, -1750,   400,   400,   400,
   -1750, -1750, -1750, -1750, -1750,  1251,  1379,  4590, -1750,  1108,
    1251,  1251,  4743, -1750,  1251,  1251,  1251,   460,  1251,  1251,
   -1750, -1750,  1598,  3792, -1750,    91, -1750, -1750,  1581,  1583,
   -1750, -1750,  2754, -1750,   653,    37, -1750, -1750, -1750, -1750,
    1028, -1750,  1541, -1750,  1528, -1750, -1750, -1750, -1750, -1750,
   -1750,   -59,   -59,   -59,   -59,  1221, -1750, -1750, -1750, -1750,
    1192,  1221, -1750, -1750, -1750, -1750,   152, -1750,  1351, -1750,
   -1750, -1750, -1750, -1750, -1750,  3872, -1750,  3872,    87, -1750,
   -1750, -1750,  2559, -1750,  1108,  1744,  1440,   695,  1761,  1442,
     268,   955, -1750, -1750,  1820, -1750, -1750, -1750, -1750,  1071,
   -1750,  1700, -1750,  1221,  1603, -1750, -1750, -1750, -1750,  1423,
      91, -1750,  3872,   317,   715, -1750, -1750, -1750,  1108,  3872,
     190, -1750, -1750, -1750,  1735,  1622, -1750,  1740, -1750,  1648,
   -1750, -1750, -1750, -1750,  1419, -1750, -1750, -1750,  1629,  1746,
    1604,  1599,  1379, -1750,  3872,   268, -1750,  1608, -1750,   955,
   -1750,  1778,  1503, -1750, -1750,  1489, -1750,   908,  1882, -1750,
   -1750, -1750, -1750,  1046, -1750, -1750, -1750,  1269,  1781,  1680,
    1830,  4622,   -46,  1221, -1750, -1750,   -46, -1750,  1221,  1290,
   -1750, -1750, -1750,  1698, -1750,  1423, -1750,  1502, -1750, -1750,
   -1750,   -46,   -46,    39,    39, -1750, -1750, -1750, -1750, -1750,
    1458, -1750,  1173, -1750, -1750, -1750,  1044, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,  1747,
    1749, -1750, -1750,  3872, -1750, -1750, -1750, -1750, -1750,  1772,
   -1750, -1750, -1750, -1750, -1750, -1750,  1621,  1621,  1621,  1621,
     -46, -1750, -1750,   -46,    39,    39, -1750, -1750, -1750,  3792,
    1582,  3792,  1584, -1750, -1750, -1750, -1750, -1750,  1771, -1750,
     695, -1750,  1807, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
     268,  1102, -1750, -1750,  1102,   -24,  1108, -1750, -1750,  3792,
   -1750, -1750,   952,  3171, -1750,  1857,  1674,  1695,    33, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750,  3872,   858, -1750, -1750, -1750,  1768,  1651,  1108,
    1458,  3792, -1750,  1842, -1750,  1405,  1821,  1405,  1604,   580,
   -1750, -1750,  1774, -1750,  1656, -1750, -1750, -1750,   -29, -1750,
   -1750,  1221,  1826,  1703, -1750,   890, -1750,  1718,   905,  1540,
    1736,  1493,  1221,  1395,  1221,  1108, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,  1553, -1750,
   -1750, -1750, -1750,   803, -1750, -1750, -1750, -1750, -1750, -1750,
     452, -1750,   530, -1750,  1491,  1221,  1221, -1750, -1750, -1750,
   -1750,   -46, -1750, -1750, -1750, -1750, -1750,  1209,  1209, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750,  3872, -1750,  3872, -1750, -1750, -1750,
   -1750, -1750,  1884,  1102,  1102, -1750,  1536,  1637,   909,   532,
   -1750,  1108, -1750, -1750,  1602,  3872, -1750,  1221,   742,  1704,
   -1750,  1707, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750,  1108,  1405, -1750,  1108,  1798, -1750, -1750,
   -1750, -1750, -1750,   909, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750,  1038,  1269,  1221,  1221,  1773, -1750,  1221, -1750, -1750,
   -1750, -1750,   181, -1750,  1221, -1750,  1108,  1108,   831,  1767,
   -1750,  1659,  1269,   803, -1750, -1750, -1750, -1750, -1750, -1750,
     -46, -1750, -1750, -1750, -1750,   -46, -1750,  1491, -1750,  1108,
      70,  1038, -1750, -1750, -1750, -1750,  1458,  1458, -1750,  3872,
    1102, -1750,  3872,  1221,   909,   909,  1646, -1750, -1750, -1750,
    1533,  1108,  1810, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750,  1108, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750,  1269,  1269,  1221, -1750,  1269, -1750,  1269, -1750,
    1379, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750,  3872, -1750, -1750, -1750, -1750, -1750, -1750,  1108, -1750,
   -1750, -1750, -1750, -1750, -1750,   394,   909,  1221, -1750,  1108,
   -1750, -1750, -1750, -1750, -1750, -1750,  1269, -1750, -1750, -1750,
    1901, -1750,   394, -1750, -1750,  3872, -1750, -1750
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1750, -1750, -1750, -1750,  1944, -1750, -1750, -1750,   133, -1750,
   -1750, -1750, -1750, -1750,  1626, -1750, -1750, -1750,  1244, -1750,
   -1750,    83,  1931, -1750, -1750,  1900,   263, -1750, -1750, -1750,
   -1750, -1750,  1775,  1827, -1750, -1750,  1787,   739, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750,  1779, -1750, -1750, -1750, -1750,
    1759, -1750, -1750, -1750,   694, -1750, -1750, -1750, -1750,  1490,
   -1750, -1750,  1414,   872, -1750, -1750, -1750, -1750, -1750, -1750,
    1557, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750,  1836, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750,   396, -1750, -1750, -1750,
   -1750, -1750, -1750,  1075,   149, -1750,  1416, -1750, -1750, -1750,
   -1750, -1750, -1750,   205, -1750,  1757, -1750,  1877, -1750, -1750,
   -1750, -1750,  1633, -1750,   230, -1750, -1750, -1750, -1750,  1766,
   -1750,  1940,  1841, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750,  1164, -1750, -1750, -1750,  1459, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,   749, -1750,
   -1750, -1750,  1702, -1750,  -528,  -723, -1750, -1750, -1750,  -365,
   -1750, -1750, -1750, -1750, -1750, -1750, -1260, -1252,  1189, -1250,
     166, -1750, -1750, -1750, -1750,   383, -1750, -1750,  -169, -1248,
   -1750, -1750, -1246, -1750, -1243, -1750, -1750,  1068, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,  1484,
   -1750, -1750, -1750,  1088, -1750,  -865, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750,   -16, -1750, -1750, -1750, -1750, -1750, -1750,
    -147, -1750, -1750, -1750, -1750,  -140, -1750, -1750, -1750, -1750,
   -1750,  1228, -1750, -1750, -1750, -1750, -1750, -1750,   150, -1750,
   -1750, -1750, -1750, -1750,  1891,  1110, -1750,   318, -1750, -1750,
   -1750, -1750,  1562, -1750, -1750, -1750, -1750, -1750, -1750,  -986,
   -1750, -1750,   240, -1750, -1750, -1750, -1750,  1017,   663,   666,
   -1750, -1750,   369, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,  1018, -1750,
   -1750,   333, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
    -307, -1750,   299, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750,   818, -1750, -1750,   820, -1750, -1750, -1750,
   -1750,   552,   294, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,   113,
     816, -1750, -1750, -1750, -1750, -1750, -1750, -1750,   811, -1750,
   -1750, -1750,   277, -1750, -1750,   534, -1750, -1750, -1750, -1113,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1100,   995, -1750, -1750,   260, -1750, -1750,   514, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
     748, -1750, -1750, -1750, -1750, -1750, -1750, -1750,   787, -1750,
     255, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750,   984, -1750,   980, -1750, -1750,  1185, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750,   976,   496, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750,    84, -1750,   497,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750, -1750,  -130,
   -1750, -1085, -1750, -1750, -1026, -1125, -1044, -1750,   425, -1750,
   -1242, -1750, -1750, -1750, -1750,    81, -1750, -1750, -1750, -1750,
     -28, -1750, -1750,   276, -1750, -1750, -1750, -1750,    78, -1750,
   -1249, -1648, -1750, -1750,   611, -1750,  -762, -1229,  -803, -1128,
   -1750, -1750, -1750, -1157, -1154, -1151, -1149, -1139,   130,  -117,
    -455,  -475, -1078,  -824,   241,  1008, -1469,   -83, -1750, -1050,
   -1750,  -791, -1750,   888,  -103,  -256, -1750,  -673,  -131,  -816,
    -966,   146,  -754, -1750, -1750,   527, -1021, -1065,  -840,  -818,
    -921,   604,  -583,  -231, -1750,  1140,  -233,  -628,  -560,  -286,
    -320,  -927, -1750, -1750, -1750, -1750, -1750,  1843, -1750,   500,
     897, -1750, -1750, -1750, -1609,  1263,    12,  1776,   846,  -411,
   -1750,  1069,  -375,  1511, -1750,  -584, -1750, -1051,  1142,  -368,
     358, -1750, -1750,  -652, -1750, -1749,  -163,  -606,  -484,   -91,
    -951,   298, -1305,  -802, -1188, -1750,  1310,  2026,  -634, -1750,
   -1750, -1750, -1750, -1750, -1750, -1750,   684, -1750,   246,  -659,
     957,  -124
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1539
static const yytype_int16 yytable[] =
{
     118,   436,   240,   816,   183,   807,   565,   328,   849,   344,
    1083,   512,   943,   349,  1519,   351,   996,   799,  1429,   989,
    1267,  1430,   259,   260,  1431,  1276,  1432,   265,   266,   267,
     268,   269,   980,   271,   345,   274,  1433,  1026,   345,  1260,
     345,  1510,  1011,  1165,   881,   984,   778,  1774,  1658,  1659,
    1072,  1603,  1214,   824,   410,   922,   261,  1860,   183,  1604,
    1214,  1605,  1017,  1606,   270,  1607,   118,   318,  1608,   319,
     757,  1017,  1461,  1462,  1463,   399,   326,   529,  1472,   812,
     974,  1017,  1563,   277,   331,   411,   392,   154,   974,  1005,
    1382,   458,   904,   398,   416,  1349,    21,  1017,   340,   341,
     345,   342,  1056,  1037,  1039,  1017,  1214,   350,  1467,   546,
     345,  1318,   154,   945,    84,  1711,  1296,  1079,   974,   345,
    1884,   438,   410,  1335,  1611,  1465,   272,  1205,   338,   339,
     279,   417,  1498,   355,  -182,   374,   347,   348,   379,   381,
     433,   384,   354,   356, -1512,  1629,   345,   445,   345, -1502,
    1318,   245,  1181,  1148,    91,   154,  1513,   393,  1155,   913,
     453,  1296,  1526,  1318,  1482, -1538,   369,   154,   369,  1986,
     123,   451,  1268,  1318,   400,    40,   819,  2077,  1499,   934,
     892,   525,   327,  1498,   477,   914,   915,   479,  1331,    51,
     548,   514,   175,  1970, -1462,    62,   154,   360,   281,   327,
    1497, -1538,    88,   417,  1553,  1705,   345,   248,  1318,   779,
      87,  1061,   435,   900,  -183,  1213,   562,   812,  1202,  1170,
     447,   442,   419,  1736,   869,  2089,  2113,  1031,  2116,  1499,
       4, -1466, -1502, -1538,   439,    53,  1556,  1095,   456,  1296,
     104, -1538,  1306,    54,  1060,   549,   450,  1170,  1764,  -182,
    1853,  1352,  1265,   778,    31,  2129,    40,   813,   566,   401,
   -1379, -1509,  1555,  1061,  1305,  2090,     3, -1466,  1904,   522,
     826,  1771,  1138,  1139,    17,   360,   232,   812,   426,   819,
    1833,  1230,  1787,   983,  1448,  2091,  1838,  1087,   533,   534,
     633,  1500,  1248,  1631,  1744,   638,   784,  1799,   402,  1214,
    1631,   983,   643,   643,   934,   403,  1683,  1631,    40,    12,
    1109,  1803,  -948,  1088,  1314,   927, -1538,   418,  1635,  1712,
     563,   233,  1634,  1079,   559,  1655,   770,    55,  1170,  -183,
    1765,  1730,    13,    90,  1449,   440,   870,  1249,   105,  1061,
    1501,   901,  1500,  1221,   996,   785,   641,   179, -1478,   569,
    1472,  -948,  1096,  1885,   163,     5,   634,   628,  -948,  1135,
    1136,   254,   798,  1140,  1192,  2202,  1297,  1125,   567,   893,
     801, -1462,  1455,   179,  1203,   572,   404,    63,     5,   996,
   -1466,  1628, -1538,  1946,   916,  1447,   343,  1695,   325,   418,
     756,  1501,  2026,  1292,  1319,   761,  -593,   401,   765,   766,
    2078,   767,   768,   343,  1714,   774,     5,  1352,  1011,  2026,
     996,  1528,   -31,  1357,  1383,  1512,   779,   894,   902,  1684,
    1253,  1434, -1538, -1466,  1484,   343,   249,   814,    64,  -948,
    1298,  -200,   370,  1319,  1577, -1466,   402,   164,   452,   405,
    2194,  1877, -1538,   403,   246,  1299,  1319,   806,  1464,  1466,
    1269,  -591,  1122,  -182,  1523,  1713,  1319,   401,   996,  1538,
    2092,   251,  1886, -1512, -1466,   528,   946,  1332,   406,   459,
    1270, -1466,  1121,   257, -1484,  1298,   343, -1466,    54,  1354,
    1514,  1818,  1468,   547,  1754,    85,  1469,   343,   343, -1466,
    1320,  1319,  -948,  1743,   179,   166,   402,   343,    62,  1745,
    1262,    74,  1565,   403,  1330,   343,   179,   343,   407,  -593,
    2123,   906,   907,   825,   404,  1543,  1795,   991,   912,  1547,
    1548,  -948,  1550,   343,  1502,   343,   940,  1318,  1554,  1665,
      88,   343, -1466,  -183,   345,  1032,   345,   345,  1206,   544,
     991,   257, -1418,   345, -1466,   917,  1214, -1462,  1854,   165,
     343,   810,  1675,  1298, -1509,  -948,   343,  1125,  1125,  1125,
     996,  -948,    55,  1959,  -591,  1360,  1905,  1125,  1353,   771,
    1358,  2007,  1367, -1466,   404,  1502,  1222,   405,   179,  2008,
    1141,  2009,  1309,  2011,  1262,  2012,  1578,  1676,  2013,  1125,
    1631,  1125,   891,  1125,   896,  1368,   949,  1125,  1125,  1125,
    1125,  1125,  1125,  1125,  1125,   987,   406,  1126,  1850,  2184,
    1472,  2259,  1144,   635,   921,   164,  1527, -1538,  2043,   104,
      15,   179,   983,    22,  1273,  1034,   772,  1979,  1180,  1049,
    1481,  1053,   166,  1053,  1059,  1354,  1034,   405,   897,  1223,
    1094,  1695,  1122,  1122,  1122,  1691,   407, -1462,  1934, -1489,
    1318,  1053,  1122,   563,  1439,   373,  1102,  1909,  1137,  1911,
     380,  1262,  1315,  1316,  1317,   345,   406,  2063,  1098,  2065,
    1662,  1534,  1328,  1318,  1122,  1534,  1122,  1870,  1122,    74,
      63,   345,  1122,  1122,  1122,  1122,  1122,  1122,  1122,  1122,
    2137,  2156,  1113,  1698,  1939,  1770,  1364,  2082,  -736,  1129,
     343,   343,  1371,  1373,  1374,  1376,   407,  1487,  1379,  1381,
    1488,  1489,  1782,  2185,   345,   345,  2246,   105,   164,  1878,
    1894,  1895,   413,  1262,   991, -1538,  1971,   165,  2110,  2111,
    1929,  1614,  1737, -1538,  1686,   811,  1050,    28,  1859,  1061,
    1972,  2118,  2157,  1864,  1865, -1538,  1907,  1867,  1868,  1869,
    1104,  1872,  1873, -1538,  1615,  1915,  1772,  1145,   998,    18,
    1093,  1125,  1125,  1125,  1125,  1125,  1125,  1125,   803,  2161,
    1837,  2054,  2055,  2056,  2057,  1274,  1664,   297,  1051,   553,
    1054,  2119,    74,  1262,   558,  1074,    25,   390,  1974,  2120,
    1797,   298,  2034,  1702,  1085,  1804,   414,  1126,  1126,  1126,
     164,  1303,  2041,  2041,  1214,  1440,  2099,  1126, -1462,  2100,
    1319,  2186,  2101,  2073,  2102,  1699,  2074,  1856,  1857,  1858,
    2162,   141,   898,   241,  2103,  1059,   343,  1746,   299,  1126,
     165,  1126,   343,  1126,    19,  1369,  1749,  1126,  1126,  1126,
    1126,  1126,  1126,  1126,  1126,  1783,  1122,  1122,  1122,  1122,
    1122,  1122,  1122,  2041,  2041,   955,  1190,   235,   812,  2121,
    1823,  1871,   391,  1782,    74,  2075,  1618,  1619,  1620,  1621,
    1622,  1623,  1625, -1489,   343, -1462,  1308, -1538,   462,   956,
     481,  1454,  1767,  1574,  1575,   179,   343,   804,  2045,    92,
    1190,  2158,  2159,  1266,   958,   482,  1455, -1538,  1322,  1323,
    1324,  1325,  1219,  1326,   483,  2053, -1424,  1304,   244,   345,
    1183,  1910,   165,  1912,  1190,  2031,  2219,   463,  2223,  2224,
    1050,   827,  2062,  1882,   464,  1254,   243,  1824,   956,  1825,
    2038,  2039,   179,  1319,  2241,  2242,  1914,   245,  2130,    40,
    1490,  1491,  2225,   958,   300,  1262,  1262, -1538,   996,  1448,
     375,    93,   376,  1190,   301,    32,  1319,  1664,  1492,  1493,
    1442,  1294,  2180,  2093,  2094,  1768,   236, -1538,  1847,  2163,
    2164,   284,  2096,  1156,   883, -1480,   290,  1262,   959,  2058,
     996,   244,  2059,   786,   987,   327,    37,  1957,  1001,   401,
     788,    94,   758,    95,  1616,   466,  1783,   388,  1177,  1449,
    1186,  1126,  1126,  1126,  1126,  1126,  1126,  1126,   329,  1393,
    1394,   484,   115,   884,   987, -1478,   232,   389,  1082,  2263,
     885,  1322,  1323,  1324,  1325,  1945,  1326,   959,   402, -1422,
     962,   327,   787,   963,   363,   403,   759,  1395,   401,   789,
     485,   302,   303,  1396,  1322,  1323,  1324,  1325,   333,  1326,
    1235,  1443, -1419,  2151,   304,   790,   305,  1980,   467,  1446,
    2172,   233,   987, -1484,    29,   964,  2175,  2131,   960,    35,
     792,   334,   484,   961,  1398,    33,   179,   402,  1399,   962,
    1755,  2178,   963,   281,   403,   137,  1388,  1389,  1390,    40,
    1236,   886,  2042,  2152,  1391,   879,  1486,  1763,  1237,  1487,
      43,   485,  1488,  1489,   791,  1055,   404,  1125,   486,  2197,
    1524,  2198,  1125,   427,   964,  1448,  2226,  2227,  2199,   793,
    2171,    48,  1928,  1091, -1426,   762,  1756,   470,   808,  2049,
    1532,  1392,   763,   965,  1567,    44,  1525,   291,  2206,  2207,
     138,   139,  2060,  2061,   401,  2261,   179,   115,   809,   956,
     401,  1656,  2136,   487,   887,   404,   306,  2228,  2229,   488,
    1703,    49,  2266,  1981,   958,  1449,  2140,  2141,  1238,   405,
    1532,  1012,  1013,    45,   184,  1788,   307,  1928,   966,   967,
    1704,    46,   965,   402,  2083,  1014,   489,   185,   186,   402,
     403,  1262,  1122,   490,  1243,  1789,   403,  1122,   406,  1262,
     550,  2147,   551,   968,  2084,   987,   491,  1244,  2098,  1007,
      52,  1560,  1862,  1008,  2252,  1561,  1541,  1866,   405,   187,
    1542,   969,  1284,   888,  1285,  1393,  1394,   966,   967,   970,
     246,  1015,   343,   492, -1371, -1371, -1371, -1371,   407,  2235,
    2176,   493,  2177,  1834,  2236,  1835,    10,   406,   959,  1262,
      10,  -205,   968,  1395,  1669,   188,   189,  1672,   190,  1396,
     401,   404,  1677,  2208,  2209,   231,   191,   404,   991,   231,
     969,    58,   494,  1196,  1197,  1198,  1199,    59,   970,  1361,
      60,   343,  1397,  1365,  1887,  1938,  1888,   407,  1757,    61,
    1398,  1377,  1378,    67,  1399,  1187,     5,    71,   988,   402,
     962,    74,  1928,   963,  1413,    78,   403,  1415,  1416,   192,
     193,    80,    81,  1820,  1820, -1370, -1370, -1370, -1370,   102,
     194,   495,  1400,  1401,   405,   111,  2249,  1402,   112,   113,
     405,  2190,  1490,  1491,  1206,   964,  1475,  1403,   345,   345,
    1901,   115,  1902,  1830,  1404,  1324,  1325,  1126,  1326,  1405,
    1492,  1493,  1126,   406,   121,  1842,  1824,   851,  1825,   406,
    1839,  2035,  -891,   125,   126,  -891,   127,  1406,   128,  1322,
    1323,  1324,  1325,  1848,  1326,   130,   133,   404,   135,   129,
     345,  1327,  1798,  1715,   132,   144,  1716,   343,  2173,  2174,
     145,  1773,   195,   407,  1717,  1718,  1719,   146,   345,   407,
    -320,   461,   160,   965,  1896,  1897,  1898,  1899,   184,  1827,
     161,   175,   213,  1863,   162,   217,   219,  1832,   216,   223,
     224,   185,   186,   225,  1836,  2243,   239,  1801,  2244,    40,
     253,   256,   272,   257,  1801,  -891,   262,   953,   345,   263,
     405,   990,  1322,  1323,  1324,  1325,  1003,  1326,   966,   967,
    -891,  1020,  1021,   187,  1667,   279,   281,  1020,  1028,  1030,
    1322,  1323,  1324,  1325,   990,  1326,   287,   288,  1617,   406,
    1020,   462,  1758,   968,   293,  1851,   286,  2260,  1852,  1028,
    1084,   320,  1086,  1322,  1323,  1324,  1325,   321,  1326,   188,
     189,   969,   190,  1322,  1323,  1324,  1325,   327,  1326,   970,
     191,  1671,   343,   343,  1720,   323,   196,  -891,  -891,   407,
     463,  2267,  1407,  1408,  1409,  1410,  1411,   464,  1412,   330,
    1413,  1414,  1721,  1415,  1416,  1322,  1323,  1324,  1325,   465,
    1326,  1124,   332,  1674,  -891,  -891,  2217,   335,   336,  1722,
     343,  -891,  2239,   192,   193,  -891,   197,   346,  1322,  1323,
    1324,  1325,  1900,  1326,   194,   366,  1679,   365,  1903,   368,
     382,  1150,   385,   387,  -891,  1322,  1323,  1324,  1325,   394,
    1326,   412,  -891,  1846,   395,  -891,  -891,   424,   429,   430,
    -891,  -332,   432,   434,  -891,  1723,  -891,   446,   466,  -891,
     448,  -891,   476,   523,  1990,   198,  1182,   515,   526,   530,
    1936,   532,   554,   555,  -891,   557,   560,   179,   275,  -891,
     570,   568,  1322,  1323,  1324,  1325,   630,  1326,  1336,  1337,
    2044,  -891,  1020,   632,  2143,   639,   195,   646,   647,   751,
    1020,  1220,  1724,   754,   648,   563,   775,   783,   776,   794,
     796,   802,   830,   831,   873,   905,   908,   911,   990,   925,
    1942,   467,   924,   927,   468,   469,  1948,   930,   935,  1338,
     937,  1339,  -891,   941,  1261,   947,   978,   944,   950,   951,
    2030,  1006,  1020,  1023,  1090,  2032,  1020,  1092,  1099,  1105,
    2080,  1111,  1132,  1114,  1279,  1725,  1127,  1220,  1133,  -891,
     819,   426,  1340,  1341,  1342,  1726,  1149,  1142,  1173,  1151,
    1153,  1157,  1158,  1166,  1159,   345,  1171,  1160,  1182,  1161,
    1176,  1028,  1162,  1163,  1184,  1164,   762,  1178,  1190,  1193,
     470,  1124,  1124,  1124,  1200,  -891,  1212,  1216,  1231,  1232,
    1234,  1124, -1373,  1241,  -891,  -891,  1245,  1246,  1247,  1343,
     196,  1344,  1251,  1256,  1258,  1061,   154,  1280,  1261,  1345,
    1283,  1287,  1289,  1124,  -891,  1124,  1727,  1124,  1290,  -891,
    1292,  1124,  1124,  1124,  1124,  1124,  1124,  1124,  1124,  1350,
    1363,  1312,  1333,  1370,  1384,  1435,  1385,  -891,   983,  1458,
     197,  1473,  1478,  1496,  1511,  -891,   955,  1515,  -891,   812,
    2155,  1529,  1537,  1544,  -891,  -891,  -891,  1545,  1552,  1557,
    -891,  1568,  -891,  1571,  -891,  -891,  -891,  1572,  1326,  1144,
    1626,  1632,  1656,  1636,  1633,  1685,  1353,  1668,  1670,  1690,
    1346,  1687,  1680,  1708,  1449,  1261,  1731,  1673,  2132,   198,
    1678,  1735,  1747,  1733,  1061,  1020,  1739,  1751,  1775,  2146,
    1750,  2148,  1778,  1779, -1462,  1790,  1791,  1792,  1522,  1805,
    2188,  1806,  1814,  1828,  1816,  1182,  1879,  1875,  1880,   956,
    1843,  1892,  1535,  1893,  1917,  1919,  1923,  1925,  1930,  1020,
    1933,  1951,  2169,  2170,   958,   955,  1783,  1954,   812,  1937,
    1956,  1551,  1961,  1973,  1966,  1964,  1975,  1261,  1977,  1987,
    1969,  2222,  1991,  1559,  1992,  1994,  2050,  2036,  2047,  2211,
    2048,  2064,  2068,  2066,  2071,  2085,  2086,  2087,  2105,  2107,
    1220,  1981,  2114,   438,  2133,  2138,   345,  2126,  2134,  2233,
    2155,  2145,  2144,  2166,  2191,  1124,  1124,  1124,  1124,  1124,
    1124,  1124,  2179,  2181,  2003,  2183,  2195,  2189,   345,  2196,
    2204,  2231,  2214,  2232,  2247,  2250,  2248,  1261,   956,  2265,
      14,   397,    27,    73,   242,   182,   252,   255,   959,   276,
    1539,   753,   545,   958,  1295,   475,  1822,  1666,   215,   401,
    2212,  2213,  1989,   278,  2216,   764,  1076,  1101,  1940,  2254,
    2255,  2218,   525,  2257,   142,  2258,  1347,   283,    66,  1020,
     227,   423,   948,   644,   367,   931,  1845,  2010,  2237,   960,
    1131,   573,  2150,  1108,   961, -1462,  2234,   345,   402,   923,
     962,   159,  1883,   963,   987,   403,   535,  1943,  1195,  1661,
    2245,  1660,  1855,  2264,  1204,  1881,  1348,  1906,  1476,  1480,
    1742,   987,  1913,  2070,  1495,  1507,  1932,  1752,  1944,  1240,
     426,  1780,  1566,  1696,  1697,   964,  1536,   959,  1264,  1960,
    1263,  2256,  1073,  1278,  1812,  1813,  1849,  2112,   401,  2117,
    2193,  1953,  2128,  1710,  1255,  1437,  2238,  1796,  1128,  1821,
    1387,   292, -1462,  1277,   939,  1509,   378,   769,  1211,  1134,
    2240,   910,    75,  1689,  2262,  2033,   404,  1329,   960,     0,
       0,     0,     0,   961,     0,     0,     0,   402,     0,   962,
       0,   426,   963,     0,   403,     0,     0,     0,     0,  1261,
    1261,     0,     0,   965,     0,  1020,  1020,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -588,   536,     0,  -628,
       0,  -628,     0,  1781,   964,     0,  -628,     0,     0,     0,
       0,  1261,     0,     0,  -628,     0,     0,     0,     0,   405,
       0,     0,     0,     0,     0,     0,  1802,     0,   966,   967,
       0,  1811,  1811,   426,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   404,  -628,  -628,   406,     0,
       0,   812,     0,   968,  -628,     0,     0,     0,     0,     0,
       0,     0,   990,     0,     0,  -628,     0,     0,  -628,     0,
       0,   969,   965,  1840,     0,  1841,     0,     0,     0,   970,
    -628,     0,   343,     0,     0,     0,     0,     0,   407,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -628,     0,     0,     0,     0,     0,   405,  -628,
    -628,     0,     0,     0,     0,     0,     0,   966,   967,     0,
       0,   956,     0,     0,     0,     0,  -588,     0,     0,     0,
    -588,  1182,  1182,  1182,     0,     0,   958,   406,     0,     0,
    -628,  1124,   968,     0,     0,     0,  1124,     0,     0,     0,
       0,     0,  -628,     0,     0,     0,  -628,     0,     0,  1020,
     969,     0,     0,     0,     0,     0,     0,     0,   970,  -628,
       0,   343,     0,  -588,     0,     0,  -628,   407,     0,  -628,
    -628,     0,     0,     0,     0,     0,     0,  -628,     0,     0,
       0,     0,     0,     0,  -628,     0,  -628,     0,     0,  -628,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     536,     0,  -628,     0,  -628,     0,     0,     0,  1916,  -628,
     959,     0,     0,     0,  1927,  1261,     0,  -628,     0,     0,
       0,   401,     0,  1261,  -628,     0,     0,     0,  -628,     0,
    -628,     0,     0,     0,  1020,     0,     0,  -628,     0,     0,
       0,     0,  1522,     0,     0,     0,     0,     0,     0,  -628,
    -628,     0,     0,     0,     0,     0,     0,  -628,     0,  -628,
     402,     0,   962,     0,     0,   963,     0,   403,  -628,  1927,
       0,  -628,     0,  1261,  -628,     0,     0,     0,     0,     0,
       0,     0,     0,  -628,     0,     0,     0,     0,  -588,     0,
       0,     0,     0,     0,     0,  -628,  2028,   964,     0,     0,
    2028,     0,     0,     0,  -628,  -628,     0,     0,     0,     0,
       0,     0,  -628,  -628,     0,  2028,  2028,  -628,     0,     0,
     645,     0,  -628,     0,  -628,     0,     0,     0,     0,     0,
       0,     0,  -628,     0,     0,     0,     0,     0,   404,     0,
       0,     0,  -628,  -628,     0,     0,     0,     0,     0,     0,
       0,  -628,     0,     0,     0,  -628,     0,     0,     0,  -628,
    -628,     0,  -628,  -628,  2028,   965,  -628,  2028,  -628,     0,
       0,     0,  -628,  -628,     0,     0,     0,     0,     0,  -628,
       0,     0,  -628,  -628,     0,     0,     0,     0,  -628,     0,
    -628,     0,     0,  -628,  1927,     0,     0,  -628,  -628,  -628,
       0,   405,  -628,     0,     0,     0,     0,     0,     0,  -628,
     966,   967,     0,     0,     0,     0,     0,     0,   537,     0,
       0,  -628,     0,     0,  1637, -1454,  1638,     0, -1454,  1639,
     406,  -628,     0,  2109,     0,   968,  1205,  -628,     0,  1640,
   -1454,  -628,     0,  -628,     0,     0,     0,     0,     0,     0,
    -628,     0,  2028,   969,     0,     0,     0,     0,     0,     0,
       0,   970,     0,     0,   343,     0,     0,     0,     0,  2149,
     407,     0,  -628,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -628,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0, -1454,     0,
       0,     0,     0,     0,     0,  2028,     0,     0,  -628,     0,
       0,     0,     0, -1454,     0,     0,     0,  -628,     0,   955,
       0,     0,   812,     0,     0,     0,     0,     0,     0,     0,
    -628,     0,     0,     0,     0,  -628,     0,  -628,     0,     0,
       0,     0,     0,     0,     0,  -628,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -628,     0,     0,     0,     0,
       0,     0,     0,     0,  -628,  1641,     0,     0,     0,  1642,
   -1454, -1454,     0,  -628,     0,  -628,  -628,  2201,     0,  -628,
    2203,  -628,  1643,     0,     0,     0,  -628,     0,     0,     0,
       0,     0,   956,     0,     0,     0,     0, -1454, -1454,     0,
       0,  -628,     0,     0, -1454,     0,  -628,   958, -1454,     0,
    2220,  -628,     0,     0,     0,     0,     0,     0,     0,     0,
    -759,     0,  -628,  -759,  2028,     0,     0, -1454,  1644,  2028,
       0,   537,     0,     0,  -628, -1454,     0,     0, -1454, -1454,
       0,     0,     0, -1454,  -628,     0,     0, -1454,     0, -1454,
       0,     0, -1454,     0, -1454,  1028,     0,     0,     0,     0,
       0,     0,   154,     0,  1393,  1394,  2253, -1454,     0,     0,
       0,     0, -1454,     0,     0,  1645,     0,     0,     0,     0,
       0,     0,     0,     0, -1454,     0,     0,     0,     0,     0,
       0,   959,  1395,  -759,     0,     0,     0, -1466,  1396,  1646,
       0,     0,   401,     0,     0,     0,     0,     0,  -759,     0,
       0,     0,     0,  1220,     0,     0,     0,     0,     0,     0,
       0,  1422,     0,  1647,     0, -1454,     0,     0,  1648,  1398,
       0,     0,   960,  1399,     0,     0,     0,   961,  1649,     0,
       0,   402,  1650,   962,     0,     0,   963,     0,   403,     0,
       0,     0, -1454,     0,     0,     0,     0,     0,     0,     0,
       0,  1423,     0,     0,     0,     0,  1424,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   964,     0,
       0,     0,     0,     0,     0,     0,     0,     0, -1454,     0,
       0,     0,  -759,     0,     0,     0,     0, -1454, -1454,  1651,
       0,     0,     0,  -759,     0,     0,     0,     0,     0,  1652,
       0,     0,     0,     0, -1454,     0,     0, -1454, -1454,   404,
       0,     0, -1454,     0,     0,     0,     0,     0,   649,     0,
     650,     0,     0,  -759,     0,   651,     0,     0,  -759,     0,
   -1454,     0,  -759,   652,  -759,     0,   965,  -759, -1454,  -759,
       0, -1454,     0,     0,     0,     0,     0, -1454, -1454, -1454,
       0,     0,     0, -1454,     0, -1454,     0, -1454, -1454, -1454,
       0,     0,     0,     0,     0,   653,   654,     0,     0,  -759,
       0,     0,   405,   655,  -759,     0,     0,     0,     0,     0,
       0,   966,   967,     0,   656,     0,     0,   657,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   658,
       0,   406,     0,     0,     0,     0,   968,     0,     0,     0,
    -759,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   -1466,   659,     0,     0,   969,     0,     0,     0,   660,   661,
       0,     0,   970,     0,     0,   343,     0,  -759,     0,     0,
       0,   407,  1425,  1426,     0,     0,     0,  1427,     0,  1413,
       0,  1428,  1415,  1416,     0,     0,     0,     0,     0,   662,
       0,     0,     0,     0,     0,     0,     0,  -759,     0,     0,
       0,   663,     0,  -759,     0,   664,     0,     0,     0,     0,
       0,     0,  -759,  -759,     0,     0,     0,     0,   665,     0,
       0,     0,     0,     0,     0,   666,     0,     0,   667,   668,
       0,     0,  -759,     0,     0,     0,   669,  -759,     0,     0,
       0,     0,  -759,   670,     0,   671,     0,     0,   672,     0,
       0,     0,     0,     0,   649,  -759,   650,     0,     0, -1466,
       0,   651,     0,  -759,     0,     0,  -759,     0,     0,   652,
       0,     0,  -759,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   673,     0,     0,     0,   674,     0,   675,
       0,     0,     0,     0,     0,     0,   676,     0,     0,     0,
       0,   653,   654,     0,     0,   955,     0,     0,   812,   655,
       0,     0,     0,     0,     0,     0,     0,     0,   677,     0,
     656,     0,     0,   657,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   678,     0,   658,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   679,     0,     0,   659,     0,     0,
       0,     0,     0,   680,   660,   661,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   681,     0,   956,     0,
       0,   682,   955,   683,     0,   812,     0,     0,     0,     0,
       0,   684,     0,   958,     0,   662,     0,     0,     0,     0,
       0,   685,     0,     0,     0,     0,     0,   663,     0,     0,
     686,   664,     0,     0,     0,     0,     0,     0,     0,   687,
       0,   688,   689,     0,   665,   690,     0,   691,     0,     0,
       0,   666,   692,     0,   667,   668,     0,     0,     0,     0,
       0,     0,   669,  1540,     0,     0,     0,   693,     0,   670,
       0,   671,   694,     0,   672,   956,     0,   695,     0,     0,
       0,     0,     0,     0,     0,     0,   957,     0,   696,     0,
     958,     0,     0,     0,     0,     0,     0,   959,     0,     0,
     697,     0,     0,   955,     0,     0,   812,     0,   401,   673,
     698,     0,     0,   674,     0,   675,     0,     0,     0,     0,
       0,     0,   676,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   960,     0,
       0,     0,     0,   961,   677,     0,     0,   402,     0,   962,
       0,     0,   963,     0,   403,     0,     0,     0,     0,   678,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   959,     0,   956,     0,     0,     0,
     679,     0,     0,   955,   964,   401,   812,  1035,     0,   680,
       0,   958,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   681,     0,     0,     0,     0,   682,     0,   683,
       0,     0,     0,     0,     0,   960,     0,   684,     0,     0,
     961,     0,     0,     0,   402,   404,   962,   685,     0,   963,
       0,   403,     0,     0,     0,     0,   686,     0,     0,     0,
       0,     0,     0,     0,     0,   687,     0,   688,   689,     0,
       0,   690,   965,   691,     0,     0,   956,     0,   692,     0,
       0,   964,     0,     0,   955,     0,     0,   812,     0,     0,
       0,   958,     0,   693,     0,   959,     0,     0,   694,     0,
       0,     0,     0,   695,  1076,     0,   401,     0,   405,     0,
       0,     0,     0,     0,   696,     0,     0,   966,   967,     0,
       0,     0,   404,     0,     0,     0,   697,     0,     0,     0,
       0,     0,     0,     0,  1541,     0,   960,   406,  1542,     0,
     955,   961,   968,   812,     0,   402,     0,   962,     0,   965,
     963,     0,   403,     0,     0,     0,     0,   956,     0,     0,
     969,   955,     0,     0,   812,     0,     0,     0,   970,     0,
       0,   343,   958,     0,     0,   959,     0,   407,     0,     0,
       0,     0,   964,     0,     0,   405,   401,     0,     0,     0,
       0,     0,     0,     0,   966,   967,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   956,   406,     0,   960,     0,     0,   968,
       0,   961,     0,   404,  1080,   402,     0,   962,   958,     0,
     963,     0,   403,     0,   956,     0,     0,   969,     0,     0,
       0,     0,     0,     0,     0,   970,     0,     0,   343,   958,
     965,     0,     0,     0,   407,     0,   959,     0,     0,     0,
       0,     0,   964,     0,     0,     0,     0,   401,     0,   955,
       0,     0,   812,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   405,     0,     0,     0,
       0,     0,     0,     0,     0,   966,   967,   960,     0,     0,
       0,     0,   961,   404,     0,     0,   402,     0,   962,     0,
       0,   963,   959,   403,     0,   406,     0,     0,   955,     0,
     968,   812,     0,   401,     0,     0,     0,     0,     0,  1282,
     965,     0,     0,   959,     0,     0,     0,     0,   969,     0,
       0,     0,   956,   964,   401,     0,   970,     0,     0,   343,
       0,     0,     0,   960,     0,   407,     0,   958,   961,     0,
       0,     0,   402,     0,   962,     0,   405,   963,     0,   403,
       0,     0,     0,     0,   960,   966,   967,     0,     0,   961,
       0,     0,     0,   402,   404,   962,     0,     0,   963,     0,
     403,   956,     0,     0,     0,   406,     0,     0,   955,   964,
     968,   812,     0,     0,     0,     0,   958,     0,     0,     0,
       0,   965,     0,     0,     0,     0,     0,     0,   969,     0,
     964,     0,     0,     0,     0,     0,   970,     0,     0,   343,
       0,     0,     0,     0,     0,   407,     0,     0,     0,     0,
     404,   959,     0,     0,     0,     0,     0,   405,     0,     0,
       0,     0,   401,     0,     0,     0,   966,   967,     0,     0,
       0,   404,     0,     0,     0,     0,     0,   965,     0,     0,
       0,   956,  1168,     0,     0,     0,   406,     0,     0,     0,
       0,   968,   960,     0,     0,     0,   958,   961,   965,     0,
     959,   402,     0,   962,     0,     0,   963,     0,   403,   969,
       0,   401,     0,   405,     0,     0,     0,   970,     0,     0,
     343,     0,   966,   967,     0,     0,   407,     0,     0,     0,
       0,     0,     0,     0,   405,     0,     0,     0,   964,     0,
       0,   960,   406,   966,   967,   955,   961,   968,   812,     0,
     402,     0,   962,     0,     0,   963,     0,   403,     0,     0,
       0,     0,     0,   406,     0,   969,     0,     0,   968,     0,
     956,     0,     0,   970,     0,     0,   343,     0,     0,   404,
     959,     0,   407,     0,     0,   958,   969,   964,     0,     0,
       0,   401,     0,     0,   970,     0,     0,   343,     0,     0,
       0,     0,     0,   407,     0,     0,   965,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   956,     0,
       0,   960,     0,     0,     0,     0,   961,     0,   404,     0,
     402,     0,   962,   958,     0,   963,  1549,   403,     0,     0,
       0,     0,   405,     0,     0,     0,     0,     0,     0,     0,
       0,   966,   967,     0,     0,   965,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   964,     0,   959,
       0,   406,     0,     0,     0,     0,   968,     0,     0,     0,
     401,     0,     0,     0,     0,     0,  1680,     0,     0,     0,
       0,   405,     0,     0,   969,     0,     0,     0,     0,     0,
     966,   967,   970,     0,     0,   343,     0,     0,   404,     0,
    1116,   407,     0,     0,     0,   961,     0,   959,     0,   402,
     406,   962,     0,     0,   963,   968,   403,     0,   401,     0,
       0,     0,     0,     0,     0,   965,     0,     0,     0,     0,
       0,     0,     0,   969,     0,     0,     0,     0,     0,     0,
       0,   970,     0,     0,   343,     0,   964,     0,   960,     0,
     407,     0,     0,   961,     0,     0,     0,   999,     0,   962,
       0,   405,   963,     0,   403,     0,     0,     0,     0,     0,
     966,   967,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   575,   404,     0,     0,
     406,     0,     0,     0,   964,   968,     0,     0,   576,     0,
       0,   577,   578,   579,   580,   581,   582,   583,     0,     0,
       0,     0,     0,   969,   965,     0,     0,     0,     0,     0,
       0,   970,     0,     0,   343,     0,     0,     0,     0,     0,
     407,     0,     0,     0,     0,   404,   584,     0,   585,   586,
     587,   588,   589,   590,     0,     0,     0,     0,     0,     0,
     405,     0,     0,     0,     0,     0,     0,     0,     0,   966,
     967,     0,   965,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   591,   406,
       0,     0,     0,     0,   968,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   405,     0,
       0,     0,   969,     0,     0,     0,     0,   966,   967,     0,
     970,     0,     0,   343,     0,     0,     0,     0,     0,   407,
    1117,  1118,     0,     0,     0,     0,     0,   406,  1624,  1119,
       0,     0,   968,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     969,     0,     0,     0,     0,     0,     0,     0,   970,     0,
     592,   343,     0,     0,     0,     0,     0,   407,     0,     0,
       0,     0,     0,    40,     0,     0,   593,     0,     0,     0,
       0,     0, -1519,     0,     0,     0,     0,     0,     0,     0,
    1579,     0,  1580,     0,     0,  1581,   577,   578,   579,   580,
     581,   582,   583,  1582,  1583,  1584,     0,     0,     0,     0,
     594,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1585,     0,     0,     0,     0,     0,
       0,   584,   595,   585,   586,   587,   588,   589,   590,     0,
       0,     0,     0,     0,     0,     0,     0,   596,     0,     0,
       0,     0,     0,     0,   597,     0,   598,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   599,
       0,     0,     0,   591,     0,     0,     0,     0,     0,   600,
       0,     0,     0,     0,     0,     0,   601,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1586,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   602,     0,   603,   604,   605,     0,     0,
       0,  1587,     0,     0,  1588,  1589,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1590,   606,
       0,     0,     0,     0,     0,   592,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0, -1519,     0,     0,     0,
       0,   593,     0,     0,   607,   608,   609,     0,   577,   578,
     579,   580,   581,   582,   583,  1591,     0,   610,     0,   956,
     611,     0,     0,     0,  1592,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   958,   594,  1995,  1996,     0,     0,
    -327,     0,     0,   584,     0,   585,   586,   587,   588,   589,
     590,     0,     0,     0,     0,     0,     0,  1593,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1594,   596,     0,     0,     0,     0,     0,     0,   597,
       0,   598,     0,     0,     0,   591,     0,     0,     0,     0,
       0,     0,     0,     0,   599,  1595,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   577,   578,   579,   580,   581,
     582,   956,     0,     0,     0,     0,     0,     0,   959,  1596,
       0,     0,     0,     0,  1597,     0,   958,     0,     0,   401,
       0,     0,     0,     0,     0,     0,     0,     0,  1598,     0,
     584,     0,   585,   586,   587,   588,   589,   590,   602,     0,
     603,   604,   605,     0,     0,     0,     0,     0,  1997,  1116,
       0,     0,     0,     0,   961,     0,     0,   592,   402,     0,
     962,     0,   956,   963,     0,   403,     0,     0,     0,     0,
       0,     0,   591,   593,  1599,     0,     0,   958,     0,     0,
       0,     0,     0,     0,     0,  1600,     0,  1998,  1999,   607,
     608,   609,     0,   956,  1041,   964,     0,     0,     0,     0,
     959,     0,   610,     0,  1601,   611,     0,   594,   958,     0,
       0,     0,  2000,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1602,     0,     0,     0,   595,
       0,     0,     0,     0,     0,     0,   404,     0,     0,     0,
       0,     0,     0,     0,   596,     0,     0,     0,     0,     0,
    1042,   597,   962,   598,   592,   963,  2001,     0,     0,     0,
       0,   959,     0,   965,     0,     0,   599,     0,     0,     0,
       0,     0,   401,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1041,   964,     0,     0,
       0,     0,   959,     0,     0,     0,     0,     0,     0,   405,
       0,     0,  1116,     0,   594,     0,     0,   961,   966,   967,
       0,   402,     0,   962,     0,     0,   963,     0,   403,     0,
     602,     0,   603,   604,   605,     0,     0,     0,   406,  2002,
       0,     0,     0,   968,     0,     0,     0,     0,     0,     0,
       0,   596,   988,  2003,   962,     0,     0,   963,   964,     0,
     598,   969,     0,     0,     0,   965,     0,     0,     0,   970,
       0,     0,   343,   599,     0,     0,  2004,     0,   407,  1117,
    1118,   607,   608,   609,     0,     0,     0,  1861,  1119,   964,
       0,     0,     0,     0,   610,     0,     0,   611,  2005,   404,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     966,   967,     0,     0,     0,     0,     0,  2006,     0,     0,
   -1538,     0,     0,     0,     0,     0,   965,     0,     0,   603,
     604,   605,     0,     0,     0,   968,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -999,     0,     0,     0,     0,
       0,     0,     0,   969,     0,     0,     0,   965,  -999,     0,
       0,   970,   405,   179,   343,     0,     0,     0,     0,     0,
       0,   966,   967,     0,     0,     0,     0,     0,   607,   608,
     609,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   406,     0,     0,     0,     0,   968,     0,     0,     0,
       0,     0,   966,   967,     0,     0,     0,     0,     0,     0,
       0,     0, -1538,     0,   969,     0,     0,     0,     0,     0,
       0,     0,   970,     0,     0,   343,     0,   968,     0,     0,
       0,   407,  1117,  1118,     0,     0,     0,  -999,     0,     0,
       0,  1119,     0,     0,     0,   969,     0,     0,     0,     0,
    -999,     0,     0,   970,     0,   179,   343
};

static const yytype_int16 yycheck[] =
{
      83,   376,   165,   631,   128,   611,   490,   240,   667,   265,
     875,   422,   814,   269,  1243,   271,   840,   600,  1175,   837,
    1070,  1175,   185,   186,  1175,  1076,  1175,   190,   191,   192,
     193,   194,   835,   196,   265,   198,  1175,   853,   269,  1060,
     271,  1229,   845,   970,   696,   836,   574,  1516,  1353,  1354,
     866,  1311,  1018,   637,   340,   778,   187,  1666,   182,  1311,
    1026,  1311,     6,  1311,   195,  1311,   149,   230,  1311,   232,
     554,     6,  1197,  1198,  1199,   331,   239,   445,  1206,     9,
     834,     6,     9,   214,   247,   341,   319,    48,   842,   843,
    1168,    55,   765,   326,   350,  1145,    13,     6,   261,   262,
     331,   264,     9,   857,   858,     6,  1072,   270,    21,    17,
     341,    68,    48,    47,    53,    92,   117,   871,   872,   350,
      83,   377,   408,  1144,  1312,  1203,    55,    17,   259,   260,
      82,    22,     9,    92,   113,   298,   267,   268,   301,   302,
     373,   304,   273,   274,    36,  1333,   377,   380,   379,    27,
      68,    61,   992,   955,    71,    48,  1234,   320,   960,    59,
     393,   117,  1247,    68,   109,   102,   166,    48,   166,  1817,
      87,   165,   116,    68,   337,   208,    29,   201,    55,   807,
     118,   437,   228,     9,   415,    85,    86,   420,  1139,    39,
     476,   424,   176,  1802,    47,   163,    48,   280,   170,   228,
    1221,   260,    69,    22,  1282,  1447,   437,     9,    68,   574,
     134,   240,   375,    31,   113,  1017,   108,     9,    48,   973,
     383,   228,   353,  1465,   228,   192,  1975,   855,  1977,    55,
     177,    83,   110,   291,   270,    70,  1287,   113,   134,   117,
     243,   166,  1107,   313,   145,   478,   386,  1001,   194,   228,
     116,    64,  1068,   781,    24,   284,   208,    49,   491,   189,
     393,    61,  1283,   240,  1104,   232,     0,   228,   116,   432,
     638,  1513,   945,   946,    11,   358,   363,     9,   361,    29,
    1585,  1035,  1531,   228,   207,   252,  1591,     8,   451,   452,
     523,   168,   250,  1337,  1482,   528,   359,  1546,   228,  1265,
    1344,   228,   533,   534,   932,   235,  1384,  1351,   208,   445,
     916,  1553,   189,    34,  1116,   448,   169,   208,  1344,   296,
     212,   408,  1343,  1077,   487,  1351,     9,   397,  1082,   228,
     276,  1456,   445,    70,   257,   371,   340,   295,   341,   240,
     217,   159,   168,    89,  1168,   408,   228,   431,   320,   512,
    1478,   228,   228,   316,   124,   302,    55,   520,   235,   942,
     943,   445,   595,   947,   998,  2114,   367,   927,   492,   307,
     601,   121,   431,   431,   204,   515,   306,   345,   302,  1203,
     316,  1332,   192,   193,   284,  1188,   432,  1438,   238,   208,
     553,   217,   438,   271,   351,   558,   332,   189,   561,   562,
     424,   564,   565,   432,  1454,   568,   302,    64,  1211,   438,
    1234,  1251,   445,   144,  1168,  1231,   781,   355,   236,  1385,
    1054,  1175,   232,   316,  1215,   432,   228,   219,   396,   306,
     431,   432,   432,   351,   432,   316,   228,   237,   432,   369,
    2088,  1683,   252,   235,   354,   446,   351,   610,  1202,  1203,
     394,   332,   927,   432,  1245,   432,   351,   189,  1282,   394,
     427,   445,   425,   355,   316,   394,   400,  1140,   398,   433,
     414,   432,   927,   432,   426,   431,   432,   438,   313,   292,
    1234,  1566,   395,   391,  1505,   424,   399,   432,   432,   425,
     447,   351,   369,  1479,   431,   432,   228,   432,   163,  1485,
    1060,   301,  1293,   235,  1132,   432,   431,   432,   438,   445,
    1979,   767,   768,   637,   306,  1269,  1537,   837,   774,  1273,
    1274,   398,  1276,   432,   401,   432,   812,    68,  1282,   447,
     397,   432,   425,   432,   765,   855,   767,   768,   428,   456,
     860,   432,   447,   774,   425,   445,  1512,   400,   414,   349,
     432,   217,   447,   431,   354,   432,   432,  1117,  1118,  1119,
    1384,   438,   397,  1792,   445,  1148,   414,  1127,   225,   252,
     301,  1831,  1155,   425,   306,   401,   322,   369,   431,  1831,
     948,  1831,  1110,  1831,  1144,  1831,  1309,   447,  1831,  1149,
    1634,  1151,   755,  1153,   757,  1155,   829,  1157,  1158,  1159,
    1160,  1161,  1162,  1163,  1164,   836,   398,   927,  1634,  2078,
    1738,  2220,    29,   312,   777,   237,  1250,   427,  1860,   243,
     145,   431,   228,   115,   181,   856,   309,  1815,   228,   860,
    1213,   862,   432,   864,   865,   292,   867,   369,   112,   385,
     896,  1692,  1117,  1118,  1119,  1436,   438,    64,  1761,   208,
      68,   882,  1127,   212,   181,   297,   912,  1735,   944,  1737,
     302,  1221,  1117,  1118,  1119,   896,   398,  1909,   899,  1911,
     228,  1255,  1127,    68,  1149,  1259,  1151,   217,  1153,   301,
     345,   912,  1157,  1158,  1159,  1160,  1161,  1162,  1163,  1164,
    1995,   239,   925,   158,  1772,  1511,  1151,  1939,   181,   930,
     432,   432,  1157,  1158,  1159,  1160,   438,    12,  1163,  1164,
      15,    16,   121,   181,   945,   946,  2185,   341,   237,  1685,
    1706,  1707,   194,  1283,  1044,   260,  1804,   349,  1970,  1971,
    1751,  1314,   181,   232,  1393,   401,   860,   445,  1665,   240,
    1805,   161,   290,  1670,  1671,   291,  1732,  1674,  1675,  1676,
     913,  1678,  1679,   252,  1314,  1741,   181,   174,   841,   228,
     891,  1321,  1322,  1323,  1324,  1325,  1326,  1327,   218,   239,
    1588,  1896,  1897,  1898,  1899,   332,  1359,    46,   861,   481,
     863,   201,   301,  1343,   486,   868,    26,    30,  1809,   209,
    1544,    60,  1843,  1445,   877,   181,   268,  1117,  1118,  1119,
     237,   232,  1853,  1854,  1770,   332,  1963,  1127,   225,  1963,
     351,   279,  1963,  1926,  1963,   280,  1929,  1657,  1658,  1659,
     290,   445,   296,   445,  1963,  1056,   432,  1486,    97,  1149,
     349,  1151,   432,  1153,   303,  1155,  1495,  1157,  1158,  1159,
    1160,  1161,  1162,  1163,  1164,   254,  1321,  1322,  1323,  1324,
    1325,  1326,  1327,  1904,  1905,     6,   339,   316,     9,   279,
     243,   401,   105,   121,   301,  1930,  1321,  1322,  1323,  1324,
    1325,  1326,  1327,   432,   432,   292,  1109,   232,   189,    79,
       4,   416,    27,   225,   226,   431,   432,   337,  1874,   266,
     339,   439,   440,   394,    94,    19,   431,   252,   439,   440,
     441,   442,  1026,   444,    28,  1891,   447,   338,   169,  1140,
     993,  1735,   349,  1737,   339,  1836,  2145,   228,    87,    88,
    1044,   174,  1908,   270,   235,  1055,   445,   310,    79,   312,
    1851,  1852,   431,   351,  2176,  2177,  1739,    61,  1988,   208,
     245,   246,   111,    94,   213,  1505,  1506,   232,  1772,   207,
     310,   328,   312,   339,   223,   228,   351,  1540,   263,   264,
     315,  1091,  2075,  1949,  1950,   110,   425,   252,  1627,   439,
     440,   222,  1958,   961,   189,   228,   227,  1537,   178,  1900,
    1804,   242,  1903,   359,  1215,   228,   115,  1790,   842,   189,
     359,   368,   118,   370,  1314,   306,   254,   162,   986,   257,
     151,  1321,  1322,  1323,  1324,  1325,  1326,  1327,   445,   151,
     152,   196,   432,   228,  1245,   102,   363,   182,   872,  2248,
     235,   439,   440,   441,   442,  1779,   444,   178,   228,   447,
     230,   228,   408,   233,   285,   235,   162,   179,   189,   408,
     225,   310,   311,   185,   439,   440,   441,   442,   205,   444,
     161,   406,   447,   250,   323,   359,   325,   149,   369,  1183,
    2046,   408,  1293,   182,    97,   265,  2052,  1988,   219,    80,
     359,   228,   196,   224,   216,   445,   431,   228,   220,   230,
       9,  2067,   233,   170,   235,   310,    12,    13,    14,   208,
     201,   306,  1854,   290,    20,   182,     9,  1508,   209,    12,
     347,   225,    15,    16,   408,   864,   306,  1667,   232,  2095,
       8,  2097,  1672,   364,   265,   207,   285,   286,  2104,   408,
    2041,   445,  1750,   882,   432,   310,    55,   438,   162,  1883,
    1254,    57,   317,   333,  1297,   164,    34,   445,  2124,  2125,
     365,   366,  1904,  1905,   189,  2245,   431,   432,   182,    79,
     189,   261,   262,   277,   369,   306,   425,   326,   327,   283,
     232,   298,  2262,   255,    94,   257,   261,   262,   279,   369,
    1294,   287,   288,   202,    11,   232,   445,  1805,   378,   379,
     252,   210,   333,   228,   232,   301,   310,    24,    25,   228,
     235,  1751,  1667,   317,   413,   252,   235,  1672,   398,  1759,
     269,  2003,   271,   403,   252,  1436,   330,   426,  1962,   395,
     445,   154,  1667,   399,  2200,   158,   395,  1672,   369,    56,
     399,   421,   310,   438,   312,   151,   152,   378,   379,   429,
     354,   347,   432,   357,   417,   418,   419,   420,   438,  2160,
    2064,   365,  2066,   148,  2165,   150,     2,   398,   178,  1809,
       6,   375,   403,   179,  1371,    92,    93,  1374,    95,   185,
     189,   306,  1379,   225,   226,   155,   103,   306,  1588,   159,
     421,   445,   396,   417,   418,   419,   420,   445,   429,  1149,
     347,   432,   208,  1153,   256,  1769,   258,   438,   217,   445,
     216,  1161,  1162,   115,   220,   446,   302,   130,   228,   228,
     230,   301,  1930,   233,   446,   445,   235,   449,   450,   146,
     147,   347,   434,  1569,  1570,   417,   418,   419,   420,   164,
     157,   445,   248,   249,   369,   445,  2191,   253,   347,   231,
     369,  2085,   245,   246,   428,   265,   430,   263,  1569,  1570,
     148,   432,   150,  1576,   270,   441,   442,  1667,   444,   275,
     263,   264,  1672,   398,   332,  1611,   310,     1,   312,   398,
    1593,  1845,     6,   445,   445,     9,   445,   293,   445,   439,
     440,   441,   442,  1629,   444,   350,   210,   306,   396,   445,
    1611,   451,  1545,    32,   445,   445,    35,   432,  2047,  2048,
     347,  1515,   229,   438,    43,    44,    45,   227,  1629,   438,
     432,   119,   432,   333,  1711,  1712,  1713,  1714,    11,  1572,
     445,   176,   274,  1669,   445,   386,    23,  1580,   445,   445,
     347,    24,    25,   323,  1587,  2179,   363,  1551,  2182,   208,
     445,   102,    55,   432,  1558,    79,   375,   833,  1669,   358,
     369,   837,   439,   440,   441,   442,   842,   444,   378,   379,
      94,   847,   848,    56,   451,    82,   170,   853,   854,   855,
     439,   440,   441,   442,   860,   444,   347,   342,   447,   398,
     866,   189,   401,   403,   432,  1638,   445,  2231,  1641,   875,
     876,   363,   878,   439,   440,   441,   442,   274,   444,    92,
      93,   421,    95,   439,   440,   441,   442,   228,   444,   429,
     103,   447,   432,   432,   153,   104,   343,   151,   152,   438,
     228,  2265,   438,   439,   440,   441,   442,   235,   444,   354,
     446,   447,   171,   449,   450,   439,   440,   441,   442,   247,
     444,   927,   205,   447,   178,   179,  2142,   445,   241,   188,
     432,   185,  2170,   146,   147,   189,   383,    66,   439,   440,
     441,   442,  1715,   444,   157,   347,   447,   445,  1721,   445,
     241,   957,    22,   268,   208,   439,   440,   441,   442,   432,
     444,   228,   216,   447,   445,   219,   220,   292,   445,   445,
     224,    81,    81,   432,   228,   234,   230,   426,   306,   233,
     432,   235,   391,   394,  1827,   432,   992,   308,   226,   194,
    1763,   432,   310,   394,   248,   355,    54,   431,   445,   253,
      36,   375,   439,   440,   441,   442,    26,   444,    24,    25,
     447,   265,  1018,   182,  1999,   363,   229,   445,   445,   445,
    1026,  1027,   281,   375,   347,   212,   432,   219,   355,   428,
     337,   208,   104,   228,   297,   372,   278,   272,  1044,   394,
    1774,   369,   438,   448,   372,   373,  1780,   391,    26,    65,
     353,    67,   306,   268,  1060,   169,   432,   452,   445,   445,
    1833,   228,  1068,   131,   102,  1838,  1072,    17,   431,   167,
    1936,   182,   391,   393,  1080,   334,   448,  1083,   228,   333,
      29,  1774,    98,    99,   100,   344,   448,   122,    55,   448,
     448,   448,   448,   123,   448,  1936,   199,   448,  1104,   448,
     394,  1107,   448,   448,   125,   448,   310,   424,   339,   127,
     438,  1117,  1118,  1119,   128,   369,    96,   390,   394,   132,
      48,  1127,   393,   133,   378,   379,   391,   393,   388,   145,
     343,   147,   174,   138,   426,   240,    48,   141,  1144,   155,
     174,   107,   324,  1149,   398,  1151,   405,  1153,   371,   403,
     271,  1157,  1158,  1159,  1160,  1161,  1162,  1163,  1164,   431,
     394,   109,   109,   432,   181,   300,   332,   421,   228,   158,
     383,   129,   428,   166,   394,   429,     6,   357,   432,     9,
    2023,   204,   394,    48,   438,   439,   440,   212,   174,   204,
     444,   117,   446,   271,   448,   449,   450,   187,   444,    29,
     356,   437,   261,   212,   436,   332,   225,   447,   447,   394,
     226,   389,   364,   126,   257,  1221,   260,   447,  1991,   432,
     447,   181,   322,   256,   240,  1231,   391,    48,   133,  2002,
     394,  2004,     8,   174,    64,   428,   121,   428,  1244,   394,
    2081,     9,   298,   168,   299,  1251,   275,   259,   275,    79,
     196,   320,  1258,   335,   120,   425,   105,   425,    48,  1265,
     170,   136,  2035,  2036,    94,     6,   254,   137,     9,   276,
     232,  1277,   253,   275,   280,   139,   108,  1283,   385,     7,
     291,  2147,   111,  1289,   214,    65,   124,   395,   151,  2132,
     151,   319,   131,   319,    97,    48,   232,   212,   140,   258,
    1306,   255,    91,  2169,    88,   197,  2147,   143,   215,  2152,
    2153,   428,   186,   432,  2087,  1321,  1322,  1323,  1324,  1325,
    1326,  1327,    48,   397,   381,   298,   232,   335,  2169,   232,
     142,   174,   169,   284,   298,   135,   413,  1343,    79,    48,
       6,   325,    21,    53,   167,   128,   177,   182,   178,   200,
    1266,   547,   472,    94,  1092,   408,  1570,  1363,   132,   189,
    2133,  2134,  1823,   216,  2137,   559,   107,   902,  1773,  2212,
    2213,  2144,  2238,  2216,   107,  2218,   392,   221,    48,  1385,
     149,   358,   828,   534,   292,   806,  1613,  1831,  2167,   219,
     932,   517,  2018,   915,   224,   225,  2153,  2238,   228,   781,
     230,   120,  1694,   233,  2245,   235,   454,  1777,  1001,  1356,
    2183,  1355,  1653,  2256,  1006,  1692,   432,  1728,  1208,  1211,
    1478,  2262,  1738,  1920,  1218,  1224,  1759,  1503,  1778,  1044,
    2123,  1527,  1294,  1439,  1440,   265,  1259,   178,  1068,  1794,
    1066,  2214,   867,  1077,  1558,  1558,  1631,  1973,   189,  1978,
    2088,  1785,  1984,  1452,  1056,  1177,  2169,  1540,   928,  1569,
    1173,   228,   292,   204,   811,  1229,   300,   566,  1009,   937,
    2171,   771,    56,  1399,  2247,  1839,   306,  1130,   219,    -1,
      -1,    -1,    -1,   224,    -1,    -1,    -1,   228,    -1,   230,
      -1,  2184,   233,    -1,   235,    -1,    -1,    -1,    -1,  1505,
    1506,    -1,    -1,   333,    -1,  1511,  1512,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     0,     1,    -1,     3,
      -1,     5,    -1,  1529,   265,    -1,    10,    -1,    -1,    -1,
      -1,  1537,    -1,    -1,    18,    -1,    -1,    -1,    -1,   369,
      -1,    -1,    -1,    -1,    -1,    -1,  1552,    -1,   378,   379,
      -1,  1557,  1558,  2246,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   306,    50,    51,   398,    -1,
      -1,     9,    -1,   403,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1588,    -1,    -1,    69,    -1,    -1,    72,    -1,
      -1,   421,   333,  1599,    -1,  1601,    -1,    -1,    -1,   429,
      84,    -1,   432,    -1,    -1,    -1,    -1,    -1,   438,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   106,    -1,    -1,    -1,    -1,    -1,   369,   113,
     114,    -1,    -1,    -1,    -1,    -1,    -1,   378,   379,    -1,
      -1,    79,    -1,    -1,    -1,    -1,   130,    -1,    -1,    -1,
     134,  1657,  1658,  1659,    -1,    -1,    94,   398,    -1,    -1,
     144,  1667,   403,    -1,    -1,    -1,  1672,    -1,    -1,    -1,
      -1,    -1,   156,    -1,    -1,    -1,   160,    -1,    -1,  1685,
     421,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   429,   173,
      -1,   432,    -1,   177,    -1,    -1,   180,   438,    -1,   183,
     184,    -1,    -1,    -1,    -1,    -1,    -1,   191,    -1,    -1,
      -1,    -1,    -1,    -1,   198,    -1,   200,    -1,    -1,   203,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,     3,    -1,     5,    -1,    -1,    -1,  1744,    10,
     178,    -1,    -1,    -1,  1750,  1751,    -1,    18,    -1,    -1,
      -1,   189,    -1,  1759,   238,    -1,    -1,    -1,   242,    -1,
     244,    -1,    -1,    -1,  1770,    -1,    -1,   251,    -1,    -1,
      -1,    -1,  1778,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    58,    -1,   273,
     228,    -1,   230,    -1,    -1,   233,    -1,   235,    69,  1805,
      -1,    72,    -1,  1809,   288,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    -1,    -1,    -1,    -1,   302,    -1,
      -1,    -1,    -1,    -1,    -1,   309,  1832,   265,    -1,    -1,
    1836,    -1,    -1,    -1,   318,   106,    -1,    -1,    -1,    -1,
      -1,    -1,   113,   114,    -1,  1851,  1852,   331,    -1,    -1,
     121,    -1,   336,    -1,   338,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   346,    -1,    -1,    -1,    -1,    -1,   306,    -1,
      -1,    -1,   356,   144,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   365,    -1,    -1,    -1,   156,    -1,    -1,    -1,   160,
     374,    -1,   376,   377,  1900,   333,   380,  1903,   382,    -1,
      -1,    -1,   173,   387,    -1,    -1,    -1,    -1,    -1,   180,
      -1,    -1,   183,   184,    -1,    -1,    -1,    -1,   402,    -1,
     191,    -1,    -1,   407,  1930,    -1,    -1,   198,   412,   200,
      -1,   369,   203,    -1,    -1,    -1,    -1,    -1,    -1,   423,
     378,   379,    -1,    -1,    -1,    -1,    -1,    -1,   432,    -1,
      -1,   435,    -1,    -1,    30,     6,    32,    -1,     9,    35,
     398,   445,    -1,  1969,    -1,   403,    17,   238,    -1,    45,
      21,   242,    -1,   244,    -1,    -1,    -1,    -1,    -1,    -1,
     251,    -1,  1988,   421,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   429,    -1,    -1,   432,    -1,    -1,    -1,    -1,  2005,
     438,    -1,   273,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   288,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      -1,    -1,    -1,    -1,    -1,  2041,    -1,    -1,   309,    -1,
      -1,    -1,    -1,    94,    -1,    -1,    -1,   318,    -1,     6,
      -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     331,    -1,    -1,    -1,    -1,   336,    -1,   338,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   346,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   356,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   365,   171,    -1,    -1,    -1,   175,
     151,   152,    -1,   374,    -1,   376,   377,  2113,    -1,   380,
    2116,   382,   188,    -1,    -1,    -1,   387,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    -1,    -1,    -1,   178,   179,    -1,
      -1,   402,    -1,    -1,   185,    -1,   407,    94,   189,    -1,
    2146,   412,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       6,    -1,   423,     9,  2160,    -1,    -1,   208,   234,  2165,
      -1,   432,    -1,    -1,   435,   216,    -1,    -1,   219,   220,
      -1,    -1,    -1,   224,   445,    -1,    -1,   228,    -1,   230,
      -1,    -1,   233,    -1,   235,  2191,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    -1,   151,   152,  2202,   248,    -1,    -1,
      -1,    -1,   253,    -1,    -1,   281,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   265,    -1,    -1,    -1,    -1,    -1,
      -1,   178,   179,    79,    -1,    -1,    -1,    83,   185,   305,
      -1,    -1,   189,    -1,    -1,    -1,    -1,    -1,    94,    -1,
      -1,    -1,    -1,  2249,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   208,    -1,   329,    -1,   306,    -1,    -1,   334,   216,
      -1,    -1,   219,   220,    -1,    -1,    -1,   224,   344,    -1,
      -1,   228,   348,   230,    -1,    -1,   233,    -1,   235,    -1,
      -1,    -1,   333,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   248,    -1,    -1,    -1,    -1,   253,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   265,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   369,    -1,
      -1,    -1,   178,    -1,    -1,    -1,    -1,   378,   379,   405,
      -1,    -1,    -1,   189,    -1,    -1,    -1,    -1,    -1,   415,
      -1,    -1,    -1,    -1,   395,    -1,    -1,   398,   399,   306,
      -1,    -1,   403,    -1,    -1,    -1,    -1,    -1,     3,    -1,
       5,    -1,    -1,   219,    -1,    10,    -1,    -1,   224,    -1,
     421,    -1,   228,    18,   230,    -1,   333,   233,   429,   235,
      -1,   432,    -1,    -1,    -1,    -1,    -1,   438,   439,   440,
      -1,    -1,    -1,   444,    -1,   446,    -1,   448,   449,   450,
      -1,    -1,    -1,    -1,    -1,    50,    51,    -1,    -1,   265,
      -1,    -1,   369,    58,   270,    -1,    -1,    -1,    -1,    -1,
      -1,   378,   379,    -1,    69,    -1,    -1,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      -1,   398,    -1,    -1,    -1,    -1,   403,    -1,    -1,    -1,
     306,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     316,   106,    -1,    -1,   421,    -1,    -1,    -1,   113,   114,
      -1,    -1,   429,    -1,    -1,   432,    -1,   333,    -1,    -1,
      -1,   438,   439,   440,    -1,    -1,    -1,   444,    -1,   446,
      -1,   448,   449,   450,    -1,    -1,    -1,    -1,    -1,   144,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   363,    -1,    -1,
      -1,   156,    -1,   369,    -1,   160,    -1,    -1,    -1,    -1,
      -1,    -1,   378,   379,    -1,    -1,    -1,    -1,   173,    -1,
      -1,    -1,    -1,    -1,    -1,   180,    -1,    -1,   183,   184,
      -1,    -1,   398,    -1,    -1,    -1,   191,   403,    -1,    -1,
      -1,    -1,   408,   198,    -1,   200,    -1,    -1,   203,    -1,
      -1,    -1,    -1,    -1,     3,   421,     5,    -1,    -1,   425,
      -1,    10,    -1,   429,    -1,    -1,   432,    -1,    -1,    18,
      -1,    -1,   438,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   238,    -1,    -1,    -1,   242,    -1,   244,
      -1,    -1,    -1,    -1,    -1,    -1,   251,    -1,    -1,    -1,
      -1,    50,    51,    -1,    -1,     6,    -1,    -1,     9,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   273,    -1,
      69,    -1,    -1,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   288,    -1,    84,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   309,    -1,    -1,   106,    -1,    -1,
      -1,    -1,    -1,   318,   113,   114,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   331,    -1,    79,    -1,
      -1,   336,     6,   338,    -1,     9,    -1,    -1,    -1,    -1,
      -1,   346,    -1,    94,    -1,   144,    -1,    -1,    -1,    -1,
      -1,   356,    -1,    -1,    -1,    -1,    -1,   156,    -1,    -1,
     365,   160,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   374,
      -1,   376,   377,    -1,   173,   380,    -1,   382,    -1,    -1,
      -1,   180,   387,    -1,   183,   184,    -1,    -1,    -1,    -1,
      -1,    -1,   191,   144,    -1,    -1,    -1,   402,    -1,   198,
      -1,   200,   407,    -1,   203,    79,    -1,   412,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,   423,    -1,
      94,    -1,    -1,    -1,    -1,    -1,    -1,   178,    -1,    -1,
     435,    -1,    -1,     6,    -1,    -1,     9,    -1,   189,   238,
     445,    -1,    -1,   242,    -1,   244,    -1,    -1,    -1,    -1,
      -1,    -1,   251,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   219,    -1,
      -1,    -1,    -1,   224,   273,    -1,    -1,   228,    -1,   230,
      -1,    -1,   233,    -1,   235,    -1,    -1,    -1,    -1,   288,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   178,    -1,    79,    -1,    -1,    -1,
     309,    -1,    -1,     6,   265,   189,     9,    90,    -1,   318,
      -1,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   331,    -1,    -1,    -1,    -1,   336,    -1,   338,
      -1,    -1,    -1,    -1,    -1,   219,    -1,   346,    -1,    -1,
     224,    -1,    -1,    -1,   228,   306,   230,   356,    -1,   233,
      -1,   235,    -1,    -1,    -1,    -1,   365,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   374,    -1,   376,   377,    -1,
      -1,   380,   333,   382,    -1,    -1,    79,    -1,   387,    -1,
      -1,   265,    -1,    -1,     6,    -1,    -1,     9,    -1,    -1,
      -1,    94,    -1,   402,    -1,   178,    -1,    -1,   407,    -1,
      -1,    -1,    -1,   412,   107,    -1,   189,    -1,   369,    -1,
      -1,    -1,    -1,    -1,   423,    -1,    -1,   378,   379,    -1,
      -1,    -1,   306,    -1,    -1,    -1,   435,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   395,    -1,   219,   398,   399,    -1,
       6,   224,   403,     9,    -1,   228,    -1,   230,    -1,   333,
     233,    -1,   235,    -1,    -1,    -1,    -1,    79,    -1,    -1,
     421,     6,    -1,    -1,     9,    -1,    -1,    -1,   429,    -1,
      -1,   432,    94,    -1,    -1,   178,    -1,   438,    -1,    -1,
      -1,    -1,   265,    -1,    -1,   369,   189,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   378,   379,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,   398,    -1,   219,    -1,    -1,   403,
      -1,   224,    -1,   306,    90,   228,    -1,   230,    94,    -1,
     233,    -1,   235,    -1,    79,    -1,    -1,   421,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   429,    -1,    -1,   432,    94,
     333,    -1,    -1,    -1,   438,    -1,   178,    -1,    -1,    -1,
      -1,    -1,   265,    -1,    -1,    -1,    -1,   189,    -1,     6,
      -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   369,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   378,   379,   219,    -1,    -1,
      -1,    -1,   224,   306,    -1,    -1,   228,    -1,   230,    -1,
      -1,   233,   178,   235,    -1,   398,    -1,    -1,     6,    -1,
     403,     9,    -1,   189,    -1,    -1,    -1,    -1,    -1,   174,
     333,    -1,    -1,   178,    -1,    -1,    -1,    -1,   421,    -1,
      -1,    -1,    79,   265,   189,    -1,   429,    -1,    -1,   432,
      -1,    -1,    -1,   219,    -1,   438,    -1,    94,   224,    -1,
      -1,    -1,   228,    -1,   230,    -1,   369,   233,    -1,   235,
      -1,    -1,    -1,    -1,   219,   378,   379,    -1,    -1,   224,
      -1,    -1,    -1,   228,   306,   230,    -1,    -1,   233,    -1,
     235,    79,    -1,    -1,    -1,   398,    -1,    -1,     6,   265,
     403,     9,    -1,    -1,    -1,    -1,    94,    -1,    -1,    -1,
      -1,   333,    -1,    -1,    -1,    -1,    -1,    -1,   421,    -1,
     265,    -1,    -1,    -1,    -1,    -1,   429,    -1,    -1,   432,
      -1,    -1,    -1,    -1,    -1,   438,    -1,    -1,    -1,    -1,
     306,   178,    -1,    -1,    -1,    -1,    -1,   369,    -1,    -1,
      -1,    -1,   189,    -1,    -1,    -1,   378,   379,    -1,    -1,
      -1,   306,    -1,    -1,    -1,    -1,    -1,   333,    -1,    -1,
      -1,    79,   394,    -1,    -1,    -1,   398,    -1,    -1,    -1,
      -1,   403,   219,    -1,    -1,    -1,    94,   224,   333,    -1,
     178,   228,    -1,   230,    -1,    -1,   233,    -1,   235,   421,
      -1,   189,    -1,   369,    -1,    -1,    -1,   429,    -1,    -1,
     432,    -1,   378,   379,    -1,    -1,   438,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   369,    -1,    -1,    -1,   265,    -1,
      -1,   219,   398,   378,   379,     6,   224,   403,     9,    -1,
     228,    -1,   230,    -1,    -1,   233,    -1,   235,    -1,    -1,
      -1,    -1,    -1,   398,    -1,   421,    -1,    -1,   403,    -1,
      79,    -1,    -1,   429,    -1,    -1,   432,    -1,    -1,   306,
     178,    -1,   438,    -1,    -1,    94,   421,   265,    -1,    -1,
      -1,   189,    -1,    -1,   429,    -1,    -1,   432,    -1,    -1,
      -1,    -1,    -1,   438,    -1,    -1,   333,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      -1,   219,    -1,    -1,    -1,    -1,   224,    -1,   306,    -1,
     228,    -1,   230,    94,    -1,   233,   363,   235,    -1,    -1,
      -1,    -1,   369,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   378,   379,    -1,    -1,   333,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   265,    -1,   178,
      -1,   398,    -1,    -1,    -1,    -1,   403,    -1,    -1,    -1,
     189,    -1,    -1,    -1,    -1,    -1,   364,    -1,    -1,    -1,
      -1,   369,    -1,    -1,   421,    -1,    -1,    -1,    -1,    -1,
     378,   379,   429,    -1,    -1,   432,    -1,    -1,   306,    -1,
     219,   438,    -1,    -1,    -1,   224,    -1,   178,    -1,   228,
     398,   230,    -1,    -1,   233,   403,   235,    -1,   189,    -1,
      -1,    -1,    -1,    -1,    -1,   333,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   421,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   429,    -1,    -1,   432,    -1,   265,    -1,   219,    -1,
     438,    -1,    -1,   224,    -1,    -1,    -1,   228,    -1,   230,
      -1,   369,   233,    -1,   235,    -1,    -1,    -1,    -1,    -1,
     378,   379,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,   306,    -1,    -1,
     398,    -1,    -1,    -1,   265,   403,    -1,    -1,    33,    -1,
      -1,    36,    37,    38,    39,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,   421,   333,    -1,    -1,    -1,    -1,    -1,
      -1,   429,    -1,    -1,   432,    -1,    -1,    -1,    -1,    -1,
     438,    -1,    -1,    -1,    -1,   306,    71,    -1,    73,    74,
      75,    76,    77,    78,    -1,    -1,    -1,    -1,    -1,    -1,
     369,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   378,
     379,    -1,   333,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,   398,
      -1,    -1,    -1,    -1,   403,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   369,    -1,
      -1,    -1,   421,    -1,    -1,    -1,    -1,   378,   379,    -1,
     429,    -1,    -1,   432,    -1,    -1,    -1,    -1,    -1,   438,
     439,   440,    -1,    -1,    -1,    -1,    -1,   398,   447,   448,
      -1,    -1,   403,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     421,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   429,    -1,
     195,   432,    -1,    -1,    -1,    -1,    -1,   438,    -1,    -1,
      -1,    -1,    -1,   208,    -1,    -1,   211,    -1,    -1,    -1,
      -1,    -1,   217,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    32,    -1,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,
     245,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    71,   267,    73,    74,    75,    76,    77,    78,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   282,    -1,    -1,
      -1,    -1,    -1,    -1,   289,    -1,   291,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   304,
      -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,    -1,   314,
      -1,    -1,    -1,    -1,    -1,    -1,   321,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   153,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   358,    -1,   360,   361,   362,    -1,    -1,
      -1,   171,    -1,    -1,   174,   175,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   188,   384,
      -1,    -1,    -1,    -1,    -1,   195,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   401,    -1,    -1,    -1,
      -1,   211,    -1,    -1,   409,   410,   411,    -1,    36,    37,
      38,    39,    40,    41,    42,   225,    -1,   422,    -1,    79,
     425,    -1,    -1,    -1,   234,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,   245,    64,    65,    -1,    -1,
     445,    -1,    -1,    71,    -1,    73,    74,    75,    76,    77,
      78,    -1,    -1,    -1,    -1,    -1,    -1,   267,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   281,   282,    -1,    -1,    -1,    -1,    -1,    -1,   289,
      -1,   291,    -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   304,   305,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      41,    79,    -1,    -1,    -1,    -1,    -1,    -1,   178,   329,
      -1,    -1,    -1,    -1,   334,    -1,    94,    -1,    -1,   189,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   348,    -1,
      71,    -1,    73,    74,    75,    76,    77,    78,   358,    -1,
     360,   361,   362,    -1,    -1,    -1,    -1,    -1,   186,   219,
      -1,    -1,    -1,    -1,   224,    -1,    -1,   195,   228,    -1,
     230,    -1,    79,   233,    -1,   235,    -1,    -1,    -1,    -1,
      -1,    -1,   113,   211,   394,    -1,    -1,    94,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   405,    -1,   225,   226,   409,
     410,   411,    -1,    79,   172,   265,    -1,    -1,    -1,    -1,
     178,    -1,   422,    -1,   424,   425,    -1,   245,    94,    -1,
      -1,    -1,   250,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   445,    -1,    -1,    -1,   267,
      -1,    -1,    -1,    -1,    -1,    -1,   306,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   282,    -1,    -1,    -1,    -1,    -1,
     228,   289,   230,   291,   195,   233,   294,    -1,    -1,    -1,
      -1,   178,    -1,   333,    -1,    -1,   304,    -1,    -1,    -1,
      -1,    -1,   189,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   172,   265,    -1,    -1,
      -1,    -1,   178,    -1,    -1,    -1,    -1,    -1,    -1,   369,
      -1,    -1,   219,    -1,   245,    -1,    -1,   224,   378,   379,
      -1,   228,    -1,   230,    -1,    -1,   233,    -1,   235,    -1,
     358,    -1,   360,   361,   362,    -1,    -1,    -1,   398,   367,
      -1,    -1,    -1,   403,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   282,   228,   381,   230,    -1,    -1,   233,   265,    -1,
     291,   421,    -1,    -1,    -1,   333,    -1,    -1,    -1,   429,
      -1,    -1,   432,   304,    -1,    -1,   404,    -1,   438,   439,
     440,   409,   410,   411,    -1,    -1,    -1,   447,   448,   265,
      -1,    -1,    -1,    -1,   422,    -1,    -1,   425,   426,   306,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     378,   379,    -1,    -1,    -1,    -1,    -1,   445,    -1,    -1,
     388,    -1,    -1,    -1,    -1,    -1,   333,    -1,    -1,   360,
     361,   362,    -1,    -1,    -1,   403,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   413,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   421,    -1,    -1,    -1,   333,   426,    -1,
      -1,   429,   369,   431,   432,    -1,    -1,    -1,    -1,    -1,
      -1,   378,   379,    -1,    -1,    -1,    -1,    -1,   409,   410,
     411,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   398,    -1,    -1,    -1,    -1,   403,    -1,    -1,    -1,
      -1,    -1,   378,   379,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   388,    -1,   421,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   429,    -1,    -1,   432,    -1,   403,    -1,    -1,
      -1,   438,   439,   440,    -1,    -1,    -1,   413,    -1,    -1,
      -1,   448,    -1,    -1,    -1,   421,    -1,    -1,    -1,    -1,
     426,    -1,    -1,   429,    -1,   431,   432
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   454,   455,     0,   177,   302,   456,   457,   458,   464,
     471,   473,   445,   445,   457,   145,   479,   479,   228,   303,
     474,   474,   115,   459,   465,    26,   475,   475,   445,    97,
     577,   577,   228,   445,   472,    80,   480,   115,   460,   466,
     208,   476,  1119,   347,   164,   202,   210,   531,   445,   298,
     711,   711,   445,    70,   313,   397,   477,   478,   445,   445,
     347,   445,   163,   345,   396,   578,   584,   115,   461,   467,
     471,   130,   470,   478,   301,  1130,   481,   532,   445,   533,
     347,   434,   609,   580,    53,   424,   714,   134,   461,   468,
     479,   474,   266,   328,   368,   370,   482,   483,   487,   495,
     500,   535,   164,   534,   243,   341,   568,   569,   570,   571,
     573,   445,   347,   231,   654,   432,   583,   585,  1050,   716,
     715,   332,   722,   474,   462,   445,   445,   445,   445,   445,
     350,   536,   445,   210,   567,   396,  1115,   310,   365,   366,
     572,   445,   570,   579,   445,   347,   227,   656,   582,   584,
     611,   612,   613,   586,    48,   717,   718,   719,  1110,   717,
     432,   445,   445,   577,   237,   349,   432,   486,   488,   489,
     490,   491,   493,   494,  1130,   176,   496,   497,   498,   431,
     484,   485,   486,  1144,    11,    24,    25,    56,    92,    93,
      95,   103,   146,   147,   157,   229,   343,   383,   432,   501,
     502,   503,   504,   508,   517,   521,   524,   525,   526,   527,
     528,   529,   530,   274,  1096,   535,   445,   386,  1138,    23,
    1106,   581,   610,   445,   347,   323,   658,   585,   614,  1090,
     587,   718,   363,   408,   720,   316,   425,   712,   463,   363,
    1119,   445,   489,   445,   490,    61,   354,  1102,     9,   228,
     499,   445,   498,   445,   445,   485,   102,   432,  1061,  1119,
    1119,  1061,   375,   358,  1134,  1119,  1119,  1119,  1119,  1119,
    1061,  1119,    55,  1112,  1119,   445,   503,  1061,   568,    82,
    1113,   170,  1116,   582,   611,   655,   445,   347,   342,   699,
     611,   445,  1090,   432,   615,   617,   622,    46,    60,    97,
     213,   223,   310,   311,   323,   325,   425,   445,   588,   589,
     591,   595,   597,   599,   600,   606,   607,   608,  1119,  1119,
     363,   274,   721,   104,   723,   711,  1119,   228,  1079,   445,
     354,  1119,   205,   205,   228,   445,   241,   509,  1061,  1061,
    1119,  1119,  1119,   432,  1058,  1076,    66,  1061,  1061,  1058,
    1119,  1058,   518,   519,  1061,    92,  1061,   537,   574,   575,
    1050,  1049,  1050,   611,   657,   445,   347,   615,   445,   166,
     432,   618,   619,  1113,  1119,   310,   312,  1100,  1100,  1119,
    1113,  1119,   241,  1124,  1119,    22,  1105,   268,   162,   182,
      30,   105,  1079,  1119,   432,   445,   713,   467,  1079,  1058,
    1119,   189,   228,   235,   306,   369,   398,   438,   522,   523,
    1082,  1058,   228,   194,   268,  1099,  1058,    22,   208,  1061,
    1120,   505,   538,   575,   292,   576,  1050,   611,   659,   445,
     445,   616,    81,  1079,   432,  1119,  1105,  1057,  1058,   270,
     371,   596,   228,  1058,  1060,  1079,   426,  1119,   432,   698,
     698,   165,   432,  1079,   724,   725,   134,   469,    55,   433,
     492,   119,   189,   228,   235,   247,   306,   369,   372,   373,
     438,   510,   511,   512,   515,   523,   391,  1076,   520,  1079,
     506,     4,    19,    28,   196,   225,   232,   277,   283,   310,
     317,   330,   357,   365,   396,   445,   539,   540,   544,   546,
     551,   552,   553,   554,   558,   559,   560,   561,   562,   563,
     564,   565,  1102,  1131,  1079,   308,   660,   661,   662,   700,
     623,   620,  1119,   394,   594,  1058,   226,  1123,   394,  1112,
     194,  1118,   432,  1119,  1119,   725,     1,   432,   726,   727,
     728,   729,   730,   735,   474,   512,    17,   391,  1082,  1079,
     269,   271,   507,  1124,   310,   394,  1142,   355,  1124,  1119,
      54,  1111,   108,   212,  1121,  1121,  1079,  1144,   375,  1119,
      36,  1109,   698,   662,   701,    21,    33,    36,    37,    38,
      39,    40,    41,    42,    71,    73,    74,    75,    76,    77,
      78,   113,   195,   211,   245,   267,   282,   289,   291,   304,
     314,   321,   358,   360,   361,   362,   384,   409,   410,   411,
     422,   425,   624,   625,   626,   628,   629,   630,   631,   632,
     633,   642,   643,   645,   646,   647,   652,   653,  1119,  1135,
      26,  1107,   182,  1079,    55,   312,   590,   601,  1079,   363,
    1136,   228,   598,  1076,   598,   121,   445,   445,   347,     3,
       5,    10,    18,    50,    51,    58,    69,    72,    84,   106,
     113,   114,   144,   156,   160,   173,   180,   183,   184,   191,
     198,   200,   203,   238,   242,   244,   251,   273,   288,   309,
     318,   331,   336,   338,   346,   356,   365,   374,   376,   377,
     380,   382,   387,   402,   407,   412,   423,   435,   445,   736,
     737,   747,   752,   756,   759,   772,   775,   780,   785,   786,
     787,   790,   797,   801,   803,   818,   821,   823,   825,   828,
     830,   836,   845,   847,   864,   866,   869,   873,   879,   889,
     896,   898,   901,   905,   906,   917,   928,   938,   944,   947,
     953,   957,   959,   961,   963,   966,   977,   978,   987,   989,
     990,   445,   513,   515,   375,  1137,  1119,  1121,   118,   162,
     542,  1119,   310,   317,   559,  1119,  1119,  1119,  1119,  1106,
       9,   252,   309,   566,  1119,   432,   355,   663,   617,   622,
     702,   703,   704,   219,   359,   408,   359,   408,   359,   408,
     359,   408,   359,   408,   428,  1143,   337,  1132,  1079,  1075,
    1076,  1076,   208,   218,   337,   644,  1119,  1120,   162,   182,
     217,   401,     9,    49,   219,   621,  1080,  1081,  1082,    29,
     602,   603,   604,   605,  1108,  1144,  1112,   174,   593,  1117,
     104,   228,   731,   738,   748,   753,   757,   760,   773,   776,
     781,   788,   791,   798,   802,   804,   819,   822,   824,  1142,
     829,     1,   831,   837,   846,   848,   865,   867,   870,   874,
     880,   890,   897,   899,   902,   907,   918,   929,   939,   228,
     340,   948,   954,   297,   958,   960,   962,   964,   967,   182,
     979,  1116,   991,   189,   228,   235,   306,   369,   438,   514,
     516,  1119,   118,   307,   355,   545,  1119,   112,   296,   541,
      31,   159,   236,   555,  1060,   372,  1058,  1058,   278,  1129,
    1129,   272,  1058,    59,    85,    86,   284,   445,   664,   665,
     669,  1119,   618,   704,   438,   394,   634,   448,  1077,  1078,
     391,   631,   649,   650,  1080,    26,   627,   353,  1098,  1098,
    1082,   268,  1126,  1126,   452,    47,   400,   169,   594,  1079,
     445,   445,   739,  1074,  1075,     6,    79,    90,    94,   178,
     219,   224,   230,   233,   265,   333,   378,   379,   403,   421,
     429,   749,  1044,  1064,  1065,  1074,  1080,  1083,   432,   754,
    1031,  1032,  1033,   228,  1054,  1055,  1056,  1076,   228,  1072,
    1074,  1083,   774,   777,   782,  1045,  1046,  1065,  1050,   228,
     792,  1064,  1071,  1074,   799,  1065,   228,   395,   399,   805,
     806,  1031,   287,   288,   301,   347,   820,     6,  1062,  1063,
    1074,  1074,   826,   131,  1030,  1031,  1062,   668,  1074,   849,
    1074,  1080,  1083,   930,  1076,    90,   868,  1065,   871,  1065,
     875,   172,   228,   881,   884,   885,   886,  1054,  1072,  1076,
    1144,  1050,  1047,  1076,  1050,  1047,     9,   908,  1048,  1076,
     145,   240,   919,   920,   921,   922,   924,   925,   926,   927,
    1051,  1052,  1062,   930,  1050,   945,   107,   949,   950,  1065,
      90,   955,  1064,   668,  1074,  1050,  1074,     8,    34,   981,
     102,  1047,    17,  1061,  1058,   113,   228,   543,  1076,   431,
     556,   556,  1058,  1059,  1119,   167,   666,   667,   666,  1120,
     677,   182,   705,  1079,   393,  1141,   219,   439,   440,   448,
    1041,  1043,  1044,  1066,  1074,  1081,  1083,   448,  1078,  1076,
     648,   650,   391,   228,  1111,  1075,  1075,  1082,  1060,  1060,
    1108,  1112,   122,   746,    29,   174,   740,  1108,  1126,   448,
    1074,   448,  1084,   448,  1085,  1126,  1099,   448,   448,   448,
     448,   448,   448,   448,   448,  1084,   123,   751,   394,   750,
    1065,   199,  1093,    55,  1034,  1035,   394,  1099,   424,   761,
     228,  1071,  1074,  1050,   125,   783,   151,   446,   784,  1046,
     339,  1097,  1131,   127,   796,   740,   417,   418,   419,   420,
     128,   800,    48,   204,   761,    17,   428,   807,   808,   809,
     813,  1104,    96,  1126,  1063,  1053,   390,  1140,   838,  1144,
    1074,    89,   322,   385,   850,   851,   852,   856,   861,   932,
    1065,   394,   132,   872,    48,   161,   201,   209,   279,   876,
     885,   133,   882,   413,   426,   391,   393,   388,   250,   295,
    1094,   174,   992,  1131,   992,  1048,   138,   916,   426,   910,
    1069,  1074,  1081,   925,   927,  1062,   394,  1052,   116,   394,
     414,   923,   940,   181,   332,   946,  1110,   204,   950,  1074,
     141,   956,   174,   174,   310,   312,   965,   107,   968,   324,
     371,   982,   271,  1127,   992,   516,   117,   367,   431,   446,
     550,  1092,  1101,   232,   338,  1071,   668,   675,  1079,   617,
     678,   706,   109,   635,  1126,  1043,  1043,  1043,    68,   351,
     447,  1042,   439,   440,   441,   442,   444,   451,  1043,  1143,
    1080,  1123,  1060,   109,   592,  1069,    24,    25,    65,    67,
      98,    99,   100,   145,   147,   155,   226,   392,   432,  1052,
     431,   743,    64,   225,   292,   741,   742,   144,   301,  1067,
    1075,  1041,  1043,   394,  1043,  1041,  1086,  1075,  1081,  1083,
     432,  1043,  1089,  1043,  1043,  1088,  1043,  1041,  1041,  1043,
    1087,  1043,  1045,  1065,   181,   332,   755,  1093,    12,    13,
      14,    20,    57,   151,   152,   179,   185,   208,   216,   220,
     248,   249,   253,   263,   270,   275,   293,   438,   439,   440,
     441,   442,   444,   446,   447,   449,   450,  1036,  1037,  1038,
    1039,  1040,   208,   248,   253,   439,   440,   444,   448,  1036,
    1037,  1038,  1039,  1040,  1065,   300,   758,  1056,   762,   181,
     332,   766,   315,   406,   778,   779,  1144,  1031,   207,   257,
    1023,  1024,  1025,  1027,   416,   431,   793,  1144,   158,   998,
     999,   998,   998,   998,  1065,  1045,  1065,    21,   395,   399,
     814,   815,  1032,   129,   817,   430,   809,   811,   428,   810,
     806,  1075,   109,   827,  1054,   832,     9,    12,    15,    16,
     245,   246,   263,   264,   839,   843,   166,  1069,     9,    55,
     168,   217,   401,   857,   858,   859,   853,   851,   934,  1101,
    1127,   394,  1062,  1045,  1065,   357,   877,   732,   733,  1030,
     887,   888,  1074,  1054,     8,    34,   994,  1131,  1071,   204,
     891,   903,  1144,   911,  1108,  1074,   911,   394,   394,   507,
     144,   395,   399,  1065,    48,   212,   941,  1065,  1065,   363,
    1065,  1074,   174,  1045,  1065,  1069,  1110,   204,   971,  1074,
     154,   158,   983,     9,   988,  1054,   903,  1119,   117,   547,
     548,   271,   187,   670,   225,   226,   676,   432,   618,    30,
      32,    35,    43,    44,    45,    64,   153,   171,   174,   175,
     188,   225,   234,   267,   281,   305,   329,   334,   348,   394,
     405,   424,   445,   629,   630,   632,   642,   645,   647,   707,
     710,  1127,   636,   637,  1075,  1081,  1083,   447,  1043,  1043,
    1043,  1043,  1043,  1043,   447,  1043,   356,  1133,  1123,  1127,
     997,   999,   437,   436,  1069,   997,   212,    30,    32,    35,
      45,   171,   175,   188,   234,   281,   305,   329,   334,   344,
     348,   405,   415,   744,   745,   997,   261,  1125,  1125,  1125,
     742,   741,   228,  1068,  1075,   447,  1074,   451,   447,  1042,
     447,   447,  1042,   447,   447,   447,   447,  1042,   447,   447,
     364,  1003,  1004,  1045,  1063,   332,  1142,   389,  1139,  1139,
     394,  1054,   763,   764,   765,  1110,  1074,  1074,   158,   280,
     767,   984,  1116,   232,   252,  1003,  1026,  1028,   126,   789,
    1027,    92,   296,   432,  1052,    32,    35,    43,    44,    45,
     153,   171,   188,   234,   281,   334,   344,   405,   794,   795,
     998,   260,  1000,   256,  1001,   181,  1003,   181,  1104,   391,
     816,   812,   814,   732,  1127,   732,  1142,   322,   840,  1142,
     394,    48,   858,   860,  1069,     9,    55,   217,   401,   854,
     855,  1069,   935,  1102,   194,   276,  1128,    27,   110,   638,
    1062,  1003,   181,  1144,  1049,   133,   883,   734,     8,   174,
     891,  1074,   121,   254,  1013,  1014,  1016,  1023,   232,   252,
     428,   121,   428,   913,   914,  1069,  1068,  1065,  1119,  1023,
     951,  1144,  1074,  1003,   181,   394,     9,   969,   970,  1091,
     972,  1074,   951,   972,   298,   986,   299,   993,   994,   549,
    1058,  1092,   549,   243,   310,   312,   557,  1119,   168,   671,
    1079,   679,  1119,  1125,   148,   150,  1119,  1072,  1125,  1079,
    1074,  1074,  1058,   196,   639,   638,   447,  1142,  1058,  1001,
     997,  1119,  1119,   116,   414,   745,  1071,  1071,  1071,  1084,
    1097,   447,  1043,  1058,  1084,  1084,  1043,  1084,  1084,  1084,
     217,   401,  1084,  1084,  1005,   259,  1006,  1003,  1063,   275,
     275,   764,   270,   720,    83,   316,   425,   256,   258,   769,
     985,   768,   320,   335,   732,   732,   793,   793,   793,   793,
    1119,   148,   150,  1119,   116,   414,   795,   732,  1002,  1045,
    1046,  1045,  1046,   815,  1031,   732,  1074,   120,   833,   425,
     841,   842,   843,   105,   844,   425,  1070,  1074,  1080,  1069,
      48,   862,   855,   170,   862,   931,  1119,   276,  1121,  1045,
     566,   878,  1144,   735,   888,  1065,   193,   892,  1144,  1015,
    1017,   136,   900,  1016,   137,   904,   232,  1031,   912,  1030,
     913,   253,   942,  1095,   139,   943,   280,  1008,  1009,   291,
    1097,  1045,  1070,   275,  1069,   108,   973,   385,   975,  1127,
     149,   255,   995,  1018,  1019,  1021,  1024,     7,  1103,   557,
    1079,   111,   214,   672,    65,    64,    65,   186,   225,   226,
     250,   294,   367,   381,   404,   426,   445,   629,   630,   632,
     633,   642,   645,   647,   680,   681,   683,   684,   685,   686,
     688,   689,   690,   691,   695,   696,   438,  1073,  1074,  1079,
    1119,  1073,  1119,  1141,  1110,  1121,   395,   651,  1073,  1073,
    1029,  1110,  1029,  1003,   447,   732,  1007,   151,   151,  1065,
     124,   771,   770,   732,   998,   998,   998,   998,  1073,  1073,
    1029,  1029,   732,  1003,   319,  1003,   319,   834,   131,   835,
     842,    97,  1114,   862,   862,  1070,   994,   201,   424,   936,
    1058,   933,  1003,   232,   252,    48,   232,   212,   893,   192,
     232,   252,   427,   732,   732,   909,   732,   915,  1065,  1036,
    1037,  1038,  1039,  1040,  1010,   140,   952,   258,  1011,  1074,
    1003,  1003,   970,  1118,    91,   974,  1118,  1008,   161,   201,
     209,   279,   980,  1049,  1020,  1022,   143,   996,  1021,   284,
    1052,  1073,  1119,    88,   215,   673,   262,  1125,   197,   697,
     261,   262,   694,  1105,   186,   428,  1119,  1126,  1119,  1074,
     686,   250,   290,   692,   693,  1079,   239,   290,   439,   440,
     709,   239,   290,   439,   440,   708,   432,   640,   641,  1119,
    1119,  1073,   732,  1142,  1142,   732,  1046,  1046,   732,    48,
     862,   397,   863,   298,  1049,   181,   279,   937,  1076,   335,
    1065,  1119,   894,  1013,  1024,   232,   232,   732,   732,   732,
    1012,  1074,  1118,  1074,   142,   976,   732,   732,   225,   226,
    1122,  1079,  1119,  1119,   169,   674,  1119,  1120,  1119,  1030,
    1074,   687,  1058,    87,    88,   111,   285,   286,   326,   327,
     682,   174,   284,  1079,   693,  1073,  1073,   641,  1057,  1080,
    1122,  1003,  1003,  1065,  1065,  1119,  1049,   298,   413,   668,
     135,   895,   732,  1074,  1079,  1079,  1119,  1079,  1079,  1097,
    1065,   884,  1119,  1030,  1079,    48,   884,  1065
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
#line 760 "parser.y"
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
#line 784 "parser.y"
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
#line 813 "parser.y"
    { cb_validate_program_environment (current_program); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 814 "parser.y"
    { cb_validate_program_data (current_program); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 822 "parser.y"
    { cb_validate_program_environment (current_program); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 823 "parser.y"
    { cb_validate_program_data (current_program); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 831 "parser.y"
    { cb_validate_program_environment (current_program); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 832 "parser.y"
    { cb_validate_program_data (current_program); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 844 "parser.y"
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
#line 870 "parser.y"
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
#line 894 "parser.y"
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
#line 923 "parser.y"
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
#line 964 "parser.y"
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
#line 1012 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 1013 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 1022 "parser.y"
    {
	if (!current_program->nested_level) {
		cb_error (_("COMMON may only be used in a nested program"));
	}
	current_program->flag_common = 1;
  ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 1029 "parser.y"
    {
	if (!current_program->nested_level) {
		cb_error (_("COMMON may only be used in a nested program"));
	}
	current_program->flag_common = 1;
  ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 1040 "parser.y"
    {
	current_program->flag_initial = 1;
  ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 1044 "parser.y"
    {
	current_program->flag_recursive = 1;
	current_program->flag_initial = 1;
  ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 1069 "parser.y"
    {
	if (current_program->nested_level) {
		cb_error (_("CONFIGURATION SECTION not allowed in nested programs"));
	}
  ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 1104 "parser.y"
    {
	cb_verify (cb_debugging_line, "DEBUGGING MODE");
  ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 1110 "parser.y"
    { ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 1141 "parser.y"
    {
	cb_verify (cb_memory_size_clause, "MEMORY SIZE");
  ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 1153 "parser.y"
    {
	current_program->collating_sequence = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1160 "parser.y"
    {
	/* Ignore */
  ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 1185 "parser.y"
    {
	current_program->function_spec_list = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 1189 "parser.y"
    {
	functions_are_all = 1;
  ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1195 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1197 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1237 "parser.y"
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
#line 1247 "parser.y"
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
#line 1258 "parser.y"
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
#line 1272 "parser.y"
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
#line 1286 "parser.y"
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
#line 1300 "parser.y"
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
#line 1318 "parser.y"
    {
	cb_define_switch_name ((yyvsp[(5) - (5)]), save_tree_1, (yyvsp[(2) - (5)]), save_tree_2);
  ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 1324 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1325 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1333 "parser.y"
    {
	save_tree_1 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 1337 "parser.y"
    {
	current_program->alphabet_name_list =
		cb_list_add (current_program->alphabet_name_list, (yyvsp[(5) - (5)]));
  ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 1344 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_NATIVE); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1345 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_1); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1346 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_2); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1347 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_EBCDIC); ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1349 "parser.y"
    {
	(yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_CUSTOM);
	CB_ALPHABET_NAME ((yyval))->custom_list = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1356 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1358 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1362 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1363 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1365 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (2)]));
	save_tree_2 = (yyval);
  ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1370 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (4)]);
  ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1381 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1382 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1383 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1384 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1385 "parser.y"
    { (yyval) = cb_norm_high; ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1386 "parser.y"
    { (yyval) = cb_norm_low; ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1390 "parser.y"
    { cb_list_add (save_tree_2, (yyvsp[(1) - (1)])); ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1391 "parser.y"
    { cb_list_add (save_tree_2, cb_space); ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1392 "parser.y"
    { cb_list_add (save_tree_2, cb_zero); ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1393 "parser.y"
    { cb_list_add (save_tree_2, cb_quote); ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1394 "parser.y"
    { cb_list_add (save_tree_2, cb_norm_high); ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1395 "parser.y"
    { cb_list_add (save_tree_2, cb_norm_low); ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1403 "parser.y"
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
#line 1414 "parser.y"
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
#line 1425 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1426 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1430 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1431 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1439 "parser.y"
    {
	current_program->class_name_list =
			cb_list_add (current_program->class_name_list,
			cb_build_class_name ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])));
  ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1447 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1448 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1452 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1454 "parser.y"
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
#line 1468 "parser.y"
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
#line 1483 "parser.y"
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
#line 1550 "parser.y"
    {
	current_program->decimal_point = ',';
	current_program->numeric_separator = '.';
  ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1560 "parser.y"
    { current_program->cursor_pos = (yyvsp[(3) - (3)]); ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1567 "parser.y"
    { current_program->crt_status = (yyvsp[(4) - (4)]); ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1574 "parser.y"
    {  PENDING ("SCREEN CONTROL"); ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1580 "parser.y"
    {  PENDING ("EVENT STATUS"); ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1592 "parser.y"
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
#line 1601 "parser.y"
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
#line 1626 "parser.y"
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
#line 1641 "parser.y"
    {
	validate_file (current_file, (yyvsp[(3) - (6)]));
  ;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 1671 "parser.y"
    {
	current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
  ;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 1675 "parser.y"
    {
	current_file->fileid_assign = 1;
	current_file->assign = cb_build_assignment_name (current_file, cb_build_reference ("DISK"));
  ;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1680 "parser.y"
    {
	current_file->fileid_assign = 1;
	current_file->assign = cb_build_assignment_name (current_file, cb_build_reference ("PRINTER"));
  ;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1688 "parser.y"
    { current_file->organization = COB_ORG_LINE_SEQUENTIAL; ;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1693 "parser.y"
    {
	current_file->external_assign = 1;
  ;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1702 "parser.y"
    {
	const char	*s;

	s = "$#@DUMMY@#$";
	(yyval) = cb_build_alphanumeric_literal ((unsigned char *)s, strlen (s));
  ;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1719 "parser.y"
    { current_file->access_mode = COB_ACCESS_SEQUENTIAL; ;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1720 "parser.y"
    { current_file->access_mode = COB_ACCESS_DYNAMIC; ;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1721 "parser.y"
    { current_file->access_mode = COB_ACCESS_RANDOM; ;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1729 "parser.y"
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
#line 1749 "parser.y"
    {
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
  ;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1791 "parser.y"
    {
	key_component_list = NULL;
  ;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1800 "parser.y"
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
#line 1815 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 1816 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 1817 "parser.y"
    { (yyval) = cb_int('='); ;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 1824 "parser.y"
    {
	PENDING ("COLLATING SEQUENCE");
  ;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1834 "parser.y"
    {
	current_file->file_status = (yyvsp[(4) - (5)]);
	if ((yyvsp[(5) - (5)])) {
		PENDING ("2nd FILE STATUS");
	}
  ;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1855 "parser.y"
    { current_file->lock_mode = COB_LOCK_MANUAL; ;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1856 "parser.y"
    { current_file->lock_mode = COB_LOCK_AUTOMATIC; ;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1857 "parser.y"
    { current_file->lock_mode = COB_LOCK_EXCLUSIVE; ;}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1863 "parser.y"
    {
	current_file->lock_mode |= COB_LOCK_MULTIPLE;
  ;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1866 "parser.y"
    { PENDING ("WITH ROLLBACK"); ;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1883 "parser.y"
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
#line 1892 "parser.y"
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
#line 1901 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_RELATIVE;
		organized_seen = 1;
	}
  ;}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 1910 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_LINE_SEQUENTIAL;
		organized_seen = 1;
	}
  ;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1925 "parser.y"
    {
	cb_verify (cb_padding_character_clause, "PADDING CHARACTER");
  ;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1934 "parser.y"
    { /* ignored */ ;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1942 "parser.y"
    {
	current_file->key = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1951 "parser.y"
    { current_file->key = (yyvsp[(4) - (4)]); ;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 1958 "parser.y"
    { /* ignored */ ;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 1965 "parser.y"
    { current_file->sharing = (yyvsp[(3) - (3)]); ;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 1969 "parser.y"
    { (yyval) = NULL; PENDING ("SHARING ALL OTHER"); ;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 1970 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 1971 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 2001 "parser.y"
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

  case 242:

/* Line 1455 of yacc.c  */
#line 2025 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 2026 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 2027 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 2028 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 2035 "parser.y"
    {
	cb_verify (cb_multiple_file_tape_clause, "MULTIPLE FILE TAPE");
  ;}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 2046 "parser.y"
    { ;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 2074 "parser.y"
    { current_storage = CB_STORAGE_FILE; ;}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 2077 "parser.y"
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

  case 261:

/* Line 1455 of yacc.c  */
#line 2096 "parser.y"
    {
	if ((yyvsp[(3) - (3)]) && (yyvsp[(3) - (3)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(3) - (3)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 2108 "parser.y"
    {
	if ((yyvsp[(2) - (2)]) && (yyvsp[(2) - (2)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(2) - (2)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 2119 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 2120 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 2130 "parser.y"
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

  case 267:

/* Line 1455 of yacc.c  */
#line 2141 "parser.y"
    {
	/* Shut up bison */
	dummy_tree = (yyvsp[(2) - (4)]);
  ;}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 2153 "parser.y"
    {
	if (current_file->global) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->external = 1;
  ;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 2160 "parser.y"
    {
	if (current_file->external) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->global = 1;
  ;}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 2182 "parser.y"
    { /* ignored */ ;}
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 2192 "parser.y"
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

  case 286:

/* Line 1455 of yacc.c  */
#line 2204 "parser.y"
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

  case 287:

/* Line 1455 of yacc.c  */
#line 2230 "parser.y"
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

  case 289:

/* Line 1455 of yacc.c  */
#line 2254 "parser.y"
    {
	current_file->record_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 2260 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 2261 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 2265 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 2266 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 2274 "parser.y"
    {
	cb_verify (cb_label_records_clause, "LABEL RECORDS");
  ;}
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 2289 "parser.y"
    {
	cb_verify (cb_value_of_clause, "VALUE OF");
  ;}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 2293 "parser.y"
    {
	if (!current_file->assign) {
		current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 2309 "parser.y"
    {
	cb_verify (cb_data_records_clause, "DATA RECORDS");
  ;}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 2320 "parser.y"
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

  case 308:

/* Line 1455 of yacc.c  */
#line 2348 "parser.y"
    {
	current_file->latfoot = (yyvsp[(4) - (5)]);
  ;}
    break;

  case 309:

/* Line 1455 of yacc.c  */
#line 2355 "parser.y"
    {
	current_file->lattop = (yyvsp[(3) - (4)]);
  ;}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 2362 "parser.y"
    {
	current_file->latbot = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 2371 "parser.y"
    { /* ignore */ ;}
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 2379 "parser.y"
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

  case 313:

/* Line 1455 of yacc.c  */
#line 2397 "parser.y"
    {
	cb_warning (_("file descriptor REPORT IS"));
  ;}
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 2401 "parser.y"
    {
	cb_warning (_("file descriptor REPORTS ARE"));
  ;}
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 2412 "parser.y"
    { current_storage = CB_STORAGE_WORKING; ;}
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 2414 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->working_storage =
			cb_field_add (current_program->working_storage, CB_FIELD ((yyvsp[(5) - (5)])));
	}
  ;}
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 2423 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 2424 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 2428 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 2434 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	(yyval) = CB_TREE (description_field);
  ;}
    break;

  case 326:

/* Line 1455 of yacc.c  */
#line 2454 "parser.y"
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

  case 327:

/* Line 1455 of yacc.c  */
#line 2465 "parser.y"
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

  case 329:

/* Line 1455 of yacc.c  */
#line 2490 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 2496 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 2502 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 2511 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 334:

/* Line 1455 of yacc.c  */
#line 2520 "parser.y"
    {
	current_field->flag_is_global = 1;
	cb_error (_("CONSTANT with GLOBAL clause is not yet supported"));
  ;}
    break;

  case 335:

/* Line 1455 of yacc.c  */
#line 2527 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 2528 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 2529 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 2534 "parser.y"
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

  case 339:

/* Line 1455 of yacc.c  */
#line 2553 "parser.y"
    {
	/* required to check redefines */
	(yyval) = NULL;
  ;}
    break;

  case 340:

/* Line 1455 of yacc.c  */
#line 2559 "parser.y"
    {
	/* required to check redefines */
	(yyval) = cb_true;
  ;}
    break;

  case 355:

/* Line 1455 of yacc.c  */
#line 2587 "parser.y"
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

  case 356:

/* Line 1455 of yacc.c  */
#line 2609 "parser.y"
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

  case 357:

/* Line 1455 of yacc.c  */
#line 2630 "parser.y"
    { current_field->ename = NULL; ;}
    break;

  case 358:

/* Line 1455 of yacc.c  */
#line 2632 "parser.y"
    {
	struct cb_field *x;

	x = CB_FIELD(cb_build_field (cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(2) - (2)]))->data))));
	current_field->ename = x->name;
 ;}
    break;

  case 359:

/* Line 1455 of yacc.c  */
#line 2644 "parser.y"
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

  case 360:

/* Line 1455 of yacc.c  */
#line 2663 "parser.y"
    { current_field->pic = CB_PICTURE ((yyvsp[(1) - (1)])); ;}
    break;

  case 363:

/* Line 1455 of yacc.c  */
#line 2675 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 364:

/* Line 1455 of yacc.c  */
#line 2676 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 365:

/* Line 1455 of yacc.c  */
#line 2677 "parser.y"
    { current_field->usage = CB_USAGE_FLOAT; ;}
    break;

  case 366:

/* Line 1455 of yacc.c  */
#line 2678 "parser.y"
    { current_field->usage = CB_USAGE_DOUBLE; ;}
    break;

  case 367:

/* Line 1455 of yacc.c  */
#line 2679 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 368:

/* Line 1455 of yacc.c  */
#line 2680 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 369:

/* Line 1455 of yacc.c  */
#line 2681 "parser.y"
    { current_field->usage = CB_USAGE_COMP_5; ;}
    break;

  case 370:

/* Line 1455 of yacc.c  */
#line 2682 "parser.y"
    { current_field->usage = CB_USAGE_COMP_X; ;}
    break;

  case 371:

/* Line 1455 of yacc.c  */
#line 2683 "parser.y"
    { current_field->usage = CB_USAGE_DISPLAY; ;}
    break;

  case 372:

/* Line 1455 of yacc.c  */
#line 2684 "parser.y"
    { current_field->usage = CB_USAGE_INDEX; ;}
    break;

  case 373:

/* Line 1455 of yacc.c  */
#line 2685 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 374:

/* Line 1455 of yacc.c  */
#line 2687 "parser.y"
    {
	current_field->usage = CB_USAGE_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 375:

/* Line 1455 of yacc.c  */
#line 2692 "parser.y"
    {
	current_field->usage = CB_USAGE_PROGRAM_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 376:

/* Line 1455 of yacc.c  */
#line 2696 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 377:

/* Line 1455 of yacc.c  */
#line 2697 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 378:

/* Line 1455 of yacc.c  */
#line 2698 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 379:

/* Line 1455 of yacc.c  */
#line 2699 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 380:

/* Line 1455 of yacc.c  */
#line 2700 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 381:

/* Line 1455 of yacc.c  */
#line 2701 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 382:

/* Line 1455 of yacc.c  */
#line 2702 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 383:

/* Line 1455 of yacc.c  */
#line 2703 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_CHAR; ;}
    break;

  case 384:

/* Line 1455 of yacc.c  */
#line 2704 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 385:

/* Line 1455 of yacc.c  */
#line 2705 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 386:

/* Line 1455 of yacc.c  */
#line 2706 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 387:

/* Line 1455 of yacc.c  */
#line 2707 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 388:

/* Line 1455 of yacc.c  */
#line 2708 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 389:

/* Line 1455 of yacc.c  */
#line 2709 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 390:

/* Line 1455 of yacc.c  */
#line 2710 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 391:

/* Line 1455 of yacc.c  */
#line 2711 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 392:

/* Line 1455 of yacc.c  */
#line 2712 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 393:

/* Line 1455 of yacc.c  */
#line 2713 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 394:

/* Line 1455 of yacc.c  */
#line 2715 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  ;}
    break;

  case 395:

/* Line 1455 of yacc.c  */
#line 2723 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_UNSIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_UNSIGNED_LONG;
	}
  ;}
    break;

  case 396:

/* Line 1455 of yacc.c  */
#line 2731 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  ;}
    break;

  case 397:

/* Line 1455 of yacc.c  */
#line 2738 "parser.y"
    { PENDING ("USAGE NATIONAL");;}
    break;

  case 398:

/* Line 1455 of yacc.c  */
#line 2746 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 1;
  ;}
    break;

  case 399:

/* Line 1455 of yacc.c  */
#line 2751 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 0;
  ;}
    break;

  case 400:

/* Line 1455 of yacc.c  */
#line 2763 "parser.y"
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

  case 401:

/* Line 1455 of yacc.c  */
#line 2778 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 402:

/* Line 1455 of yacc.c  */
#line 2779 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 404:

/* Line 1455 of yacc.c  */
#line 2784 "parser.y"
    {
	current_field->occurs_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 405:

/* Line 1455 of yacc.c  */
#line 2791 "parser.y"
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

  case 406:

/* Line 1455 of yacc.c  */
#line 2814 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 407:

/* Line 1455 of yacc.c  */
#line 2817 "parser.y"
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

  case 408:

/* Line 1455 of yacc.c  */
#line 2832 "parser.y"
    { (yyval) = cb_int (COB_ASCENDING); ;}
    break;

  case 409:

/* Line 1455 of yacc.c  */
#line 2833 "parser.y"
    { (yyval) = cb_int (COB_DESCENDING); ;}
    break;

  case 411:

/* Line 1455 of yacc.c  */
#line 2838 "parser.y"
    {
	current_field->index_list = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 412:

/* Line 1455 of yacc.c  */
#line 2844 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 413:

/* Line 1455 of yacc.c  */
#line 2846 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 414:

/* Line 1455 of yacc.c  */
#line 2851 "parser.y"
    {
	(yyval) = cb_build_index ((yyvsp[(1) - (1)]), cb_int1, 1, current_field);
  ;}
    break;

  case 415:

/* Line 1455 of yacc.c  */
#line 2860 "parser.y"
    { current_field->flag_justified = 1; ;}
    break;

  case 416:

/* Line 1455 of yacc.c  */
#line 2867 "parser.y"
    { current_field->flag_synchronized = 1; ;}
    break;

  case 420:

/* Line 1455 of yacc.c  */
#line 2879 "parser.y"
    { current_field->flag_blank_zero = 1; ;}
    break;

  case 421:

/* Line 1455 of yacc.c  */
#line 2887 "parser.y"
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

  case 422:

/* Line 1455 of yacc.c  */
#line 2911 "parser.y"
    { current_field->values = (yyvsp[(3) - (3)]); ;}
    break;

  case 424:

/* Line 1455 of yacc.c  */
#line 2916 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 425:

/* Line 1455 of yacc.c  */
#line 2917 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 426:

/* Line 1455 of yacc.c  */
#line 2921 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 427:

/* Line 1455 of yacc.c  */
#line 2922 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 429:

/* Line 1455 of yacc.c  */
#line 2927 "parser.y"
    {
	if (current_field->level != 88) {
		cb_error (_("FALSE clause only allowed for 88 level"));
	}
	current_field->false_88 = cb_list_init ((yyvsp[(3) - (3)]));
  ;}
    break;

  case 430:

/* Line 1455 of yacc.c  */
#line 2940 "parser.y"
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

  case 431:

/* Line 1455 of yacc.c  */
#line 2952 "parser.y"
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

  case 432:

/* Line 1455 of yacc.c  */
#line 2972 "parser.y"
    {
	if (current_field->flag_item_based) {
		cb_error (_("BASED and ANY LENGTH are mutually exclusive"));
	} else {
		current_field->flag_any_length = 1;
	}
  ;}
    break;

  case 434:

/* Line 1455 of yacc.c  */
#line 2987 "parser.y"
    {
	current_storage = CB_STORAGE_LOCAL;
	if (current_program->nested_level) {
		cb_error (_("LOCAL-STORAGE not allowed in nested programs"));
	}
  ;}
    break;

  case 435:

/* Line 1455 of yacc.c  */
#line 2994 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->local_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 437:

/* Line 1455 of yacc.c  */
#line 3007 "parser.y"
    { current_storage = CB_STORAGE_LINKAGE; ;}
    break;

  case 438:

/* Line 1455 of yacc.c  */
#line 3009 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->linkage_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 440:

/* Line 1455 of yacc.c  */
#line 3022 "parser.y"
    {
	cb_error (_("REPORT SECTION not supported"));
	current_storage = CB_STORAGE_REPORT;
  ;}
    break;

  case 447:

/* Line 1455 of yacc.c  */
#line 3055 "parser.y"
    {
	cb_warning (_("Report description using defaults"));
  ;}
    break;

  case 449:

/* Line 1455 of yacc.c  */
#line 3063 "parser.y"
    {
	cb_error (_("GLOBAL is not allowed with RD"));
  ;}
    break;

  case 458:

/* Line 1455 of yacc.c  */
#line 3086 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 459:

/* Line 1455 of yacc.c  */
#line 3087 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 481:

/* Line 1455 of yacc.c  */
#line 3143 "parser.y"
    { cb_warning (_("looking for Report line TYPE")); ;}
    break;

  case 532:

/* Line 1455 of yacc.c  */
#line 3248 "parser.y"
    { current_storage = CB_STORAGE_SCREEN; ;}
    break;

  case 533:

/* Line 1455 of yacc.c  */
#line 3249 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 534:

/* Line 1455 of yacc.c  */
#line 3255 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	current_program->screen_storage = description_field;
	current_program->flag_screen = 1;
  ;}
    break;

  case 540:

/* Line 1455 of yacc.c  */
#line 3279 "parser.y"
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

  case 541:

/* Line 1455 of yacc.c  */
#line 3295 "parser.y"
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

  case 544:

/* Line 1455 of yacc.c  */
#line 3319 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 545:

/* Line 1455 of yacc.c  */
#line 3320 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 546:

/* Line 1455 of yacc.c  */
#line 3321 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BELL; ;}
    break;

  case 547:

/* Line 1455 of yacc.c  */
#line 3322 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLINK; ;}
    break;

  case 548:

/* Line 1455 of yacc.c  */
#line 3323 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 549:

/* Line 1455 of yacc.c  */
#line 3324 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 550:

/* Line 1455 of yacc.c  */
#line 3325 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 551:

/* Line 1455 of yacc.c  */
#line 3326 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 552:

/* Line 1455 of yacc.c  */
#line 3327 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REVERSE; ;}
    break;

  case 553:

/* Line 1455 of yacc.c  */
#line 3328 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 554:

/* Line 1455 of yacc.c  */
#line 3329 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_OVERLINE; ;}
    break;

  case 555:

/* Line 1455 of yacc.c  */
#line 3330 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_AUTO; ;}
    break;

  case 556:

/* Line 1455 of yacc.c  */
#line 3331 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_SECURE; ;}
    break;

  case 557:

/* Line 1455 of yacc.c  */
#line 3332 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REQUIRED; ;}
    break;

  case 558:

/* Line 1455 of yacc.c  */
#line 3333 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_FULL; ;}
    break;

  case 559:

/* Line 1455 of yacc.c  */
#line 3334 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_PROMPT; ;}
    break;

  case 560:

/* Line 1455 of yacc.c  */
#line 3336 "parser.y"
    {
	current_field->screen_line = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 561:

/* Line 1455 of yacc.c  */
#line 3340 "parser.y"
    {
	current_field->screen_column = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 562:

/* Line 1455 of yacc.c  */
#line 3344 "parser.y"
    {
	current_field->screen_foreg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 563:

/* Line 1455 of yacc.c  */
#line 3348 "parser.y"
    {
	current_field->screen_backg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 571:

/* Line 1455 of yacc.c  */
#line 3359 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 572:

/* Line 1455 of yacc.c  */
#line 3366 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 573:

/* Line 1455 of yacc.c  */
#line 3370 "parser.y"
    {
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 574:

/* Line 1455 of yacc.c  */
#line 3379 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 575:

/* Line 1455 of yacc.c  */
#line 3383 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 576:

/* Line 1455 of yacc.c  */
#line 3387 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 577:

/* Line 1455 of yacc.c  */
#line 3391 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 578:

/* Line 1455 of yacc.c  */
#line 3395 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 579:

/* Line 1455 of yacc.c  */
#line 3402 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 580:

/* Line 1455 of yacc.c  */
#line 3406 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 581:

/* Line 1455 of yacc.c  */
#line 3410 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 582:

/* Line 1455 of yacc.c  */
#line 3414 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 583:

/* Line 1455 of yacc.c  */
#line 3418 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 584:

/* Line 1455 of yacc.c  */
#line 3426 "parser.y"
    {
	current_field->occurs_max = cb_get_int ((yyvsp[(2) - (3)]));
	current_field->occurs_min = current_field->occurs_max;
	current_field->indexes++;
	current_field->flag_occurs = 1;
  ;}
    break;

  case 586:

/* Line 1455 of yacc.c  */
#line 3440 "parser.y"
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

  case 587:

/* Line 1455 of yacc.c  */
#line 3450 "parser.y"
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

  case 588:

/* Line 1455 of yacc.c  */
#line 3460 "parser.y"
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

  case 589:

/* Line 1455 of yacc.c  */
#line 3477 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 590:

/* Line 1455 of yacc.c  */
#line 3479 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 591:

/* Line 1455 of yacc.c  */
#line 3483 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 592:

/* Line 1455 of yacc.c  */
#line 3485 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	current_program->flag_chained = 1;
  ;}
    break;

  case 593:

/* Line 1455 of yacc.c  */
#line 3489 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 594:

/* Line 1455 of yacc.c  */
#line 3493 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 595:

/* Line 1455 of yacc.c  */
#line 3495 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 596:

/* Line 1455 of yacc.c  */
#line 3500 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), cb_build_identifier ((yyvsp[(4) - (4)])));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 598:

/* Line 1455 of yacc.c  */
#line 3509 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 599:

/* Line 1455 of yacc.c  */
#line 3513 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 601:

/* Line 1455 of yacc.c  */
#line 3525 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_AUTO;
	}
  ;}
    break;

  case 602:

/* Line 1455 of yacc.c  */
#line 3533 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_4;
	}
  ;}
    break;

  case 603:

/* Line 1455 of yacc.c  */
#line 3541 "parser.y"
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

  case 604:

/* Line 1455 of yacc.c  */
#line 3570 "parser.y"
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

  case 606:

/* Line 1455 of yacc.c  */
#line 3603 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OPTIONAL only allowed for BY REFERENCE items"));
	}
  ;}
    break;

  case 607:

/* Line 1455 of yacc.c  */
#line 3612 "parser.y"
    {
	if (current_program->prog_type == CB_FUNCTION_TYPE) {
		cb_error (_("RETURNING clause is required for a FUNCTION"));
	}
  ;}
    break;

  case 608:

/* Line 1455 of yacc.c  */
#line 3618 "parser.y"
    {
	if (cb_ref ((yyvsp[(2) - (2)])) != cb_error_node) {
		current_program->returning = (yyvsp[(2) - (2)]);
		if (cb_field ((yyvsp[(2) - (2)]))->storage != CB_STORAGE_LINKAGE) {
			cb_error (_("RETURNING item is not defined in LINKAGE SECTION"));
		}
	}
  ;}
    break;

  case 610:

/* Line 1455 of yacc.c  */
#line 3629 "parser.y"
    { in_declaratives = 1; ;}
    break;

  case 611:

/* Line 1455 of yacc.c  */
#line 3632 "parser.y"
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

  case 617:

/* Line 1455 of yacc.c  */
#line 3665 "parser.y"
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

  case 618:

/* Line 1455 of yacc.c  */
#line 3681 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 619:

/* Line 1455 of yacc.c  */
#line 3693 "parser.y"
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

  case 620:

/* Line 1455 of yacc.c  */
#line 3724 "parser.y"
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

  case 621:

/* Line 1455 of yacc.c  */
#line 3761 "parser.y"
    {
	non_const_word = 0;
	check_unreached = 0;
	if ((yyvsp[(1) - (1)]) != cb_error_node) {
		cb_error_x ((yyvsp[(1) - (1)]), _("Unknown statement '%s'"), CB_NAME ((yyvsp[(1) - (1)])));
	}
	YYERROR;
  ;}
    break;

  case 622:

/* Line 1455 of yacc.c  */
#line 3772 "parser.y"
    { (yyval) = cb_build_section_name ((yyvsp[(1) - (1)]), 0); ;}
    break;

  case 624:

/* Line 1455 of yacc.c  */
#line 3776 "parser.y"
    { /* ignore */ ;}
    break;

  case 625:

/* Line 1455 of yacc.c  */
#line 3785 "parser.y"
    {
	(yyval) = current_program->exec_list;
	current_program->exec_list = NULL;
  ;}
    break;

  case 626:

/* Line 1455 of yacc.c  */
#line 3789 "parser.y"
    {
	(yyval) = CB_TREE (current_statement);
	current_statement = NULL;
  ;}
    break;

  case 627:

/* Line 1455 of yacc.c  */
#line 3794 "parser.y"
    {
	(yyval) = cb_list_reverse (current_program->exec_list);
	current_program->exec_list = (yyvsp[(1) - (3)]);
	current_statement = CB_STATEMENT ((yyvsp[(2) - (3)]));
  ;}
    break;

  case 628:

/* Line 1455 of yacc.c  */
#line 3802 "parser.y"
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

  case 678:

/* Line 1455 of yacc.c  */
#line 3873 "parser.y"
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

  case 679:

/* Line 1455 of yacc.c  */
#line 3895 "parser.y"
    {
	BEGIN_STATEMENT ("ACCEPT", TERM_ACCEPT);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 681:

/* Line 1455 of yacc.c  */
#line 3908 "parser.y"
    {
	cb_emit_accept ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 682:

/* Line 1455 of yacc.c  */
#line 3912 "parser.y"
    {
	PENDING ("ACCEPT .. FROM ESCAPE KEY");
  ;}
    break;

  case 683:

/* Line 1455 of yacc.c  */
#line 3916 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 0);
  ;}
    break;

  case 684:

/* Line 1455 of yacc.c  */
#line 3920 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 1);
  ;}
    break;

  case 685:

/* Line 1455 of yacc.c  */
#line 3924 "parser.y"
    {
	cb_emit_accept_date ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 686:

/* Line 1455 of yacc.c  */
#line 3928 "parser.y"
    {
	cb_emit_accept_date_yyyymmdd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 687:

/* Line 1455 of yacc.c  */
#line 3932 "parser.y"
    {
	cb_emit_accept_day ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 688:

/* Line 1455 of yacc.c  */
#line 3936 "parser.y"
    {
	cb_emit_accept_day_yyyyddd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 689:

/* Line 1455 of yacc.c  */
#line 3940 "parser.y"
    {
	cb_emit_accept_day_of_week ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 690:

/* Line 1455 of yacc.c  */
#line 3944 "parser.y"
    {
	cb_emit_accept_time ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 691:

/* Line 1455 of yacc.c  */
#line 3948 "parser.y"
    {
	cb_emit_accept_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 692:

/* Line 1455 of yacc.c  */
#line 3952 "parser.y"
    {
	cb_emit_accept_environment ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 693:

/* Line 1455 of yacc.c  */
#line 3956 "parser.y"
    { 
	cb_emit_get_environment ((yyvsp[(4) - (5)]), (yyvsp[(1) - (5)]));
  ;}
    break;

  case 694:

/* Line 1455 of yacc.c  */
#line 3960 "parser.y"
    {
	cb_emit_accept_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 695:

/* Line 1455 of yacc.c  */
#line 3964 "parser.y"
    {
	cb_emit_accept_arg_value ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 696:

/* Line 1455 of yacc.c  */
#line 3968 "parser.y"
    {
	cb_emit_accept_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 697:

/* Line 1455 of yacc.c  */
#line 3972 "parser.y"
    {
	cb_emit_accept_name ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 698:

/* Line 1455 of yacc.c  */
#line 3978 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 699:

/* Line 1455 of yacc.c  */
#line 3979 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 700:

/* Line 1455 of yacc.c  */
#line 3980 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); ;}
    break;

  case 701:

/* Line 1455 of yacc.c  */
#line 3981 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), NULL); ;}
    break;

  case 702:

/* Line 1455 of yacc.c  */
#line 3982 "parser.y"
    { (yyval) = cb_build_pair (NULL, (yyvsp[(2) - (2)])); ;}
    break;

  case 703:

/* Line 1455 of yacc.c  */
#line 3983 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 704:

/* Line 1455 of yacc.c  */
#line 3987 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 705:

/* Line 1455 of yacc.c  */
#line 3991 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 706:

/* Line 1455 of yacc.c  */
#line 3992 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 711:

/* Line 1455 of yacc.c  */
#line 4005 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 712:

/* Line 1455 of yacc.c  */
#line 4006 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 713:

/* Line 1455 of yacc.c  */
#line 4007 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 714:

/* Line 1455 of yacc.c  */
#line 4008 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 715:

/* Line 1455 of yacc.c  */
#line 4009 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 716:

/* Line 1455 of yacc.c  */
#line 4010 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 717:

/* Line 1455 of yacc.c  */
#line 4011 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 718:

/* Line 1455 of yacc.c  */
#line 4013 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 719:

/* Line 1455 of yacc.c  */
#line 4017 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 720:

/* Line 1455 of yacc.c  */
#line 4021 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 721:

/* Line 1455 of yacc.c  */
#line 4025 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 722:

/* Line 1455 of yacc.c  */
#line 4029 "parser.y"
    { dispattrs |= COB_SCREEN_AUTO; ;}
    break;

  case 723:

/* Line 1455 of yacc.c  */
#line 4030 "parser.y"
    { dispattrs |= COB_SCREEN_FULL; ;}
    break;

  case 724:

/* Line 1455 of yacc.c  */
#line 4031 "parser.y"
    { dispattrs |= COB_SCREEN_REQUIRED; ;}
    break;

  case 725:

/* Line 1455 of yacc.c  */
#line 4032 "parser.y"
    { dispattrs |= COB_SCREEN_SECURE; ;}
    break;

  case 726:

/* Line 1455 of yacc.c  */
#line 4033 "parser.y"
    { dispattrs |= COB_SCREEN_UPDATE; ;}
    break;

  case 727:

/* Line 1455 of yacc.c  */
#line 4034 "parser.y"
    { dispattrs |= COB_SCREEN_PROMPT; ;}
    break;

  case 728:

/* Line 1455 of yacc.c  */
#line 4038 "parser.y"
    { terminator_warning (TERM_ACCEPT); ;}
    break;

  case 729:

/* Line 1455 of yacc.c  */
#line 4039 "parser.y"
    { terminator_clear (TERM_ACCEPT); ;}
    break;

  case 730:

/* Line 1455 of yacc.c  */
#line 4048 "parser.y"
    { BEGIN_STATEMENT ("ADD", TERM_ADD); ;}
    break;

  case 732:

/* Line 1455 of yacc.c  */
#line 4055 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '+', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 733:

/* Line 1455 of yacc.c  */
#line 4059 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(4) - (5)]), 0, cb_build_binary_list ((yyvsp[(1) - (5)]), '+'));
  ;}
    break;

  case 734:

/* Line 1455 of yacc.c  */
#line 4063 "parser.y"
    {
	cb_emit_corresponding (cb_build_add, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 736:

/* Line 1455 of yacc.c  */
#line 4069 "parser.y"
    { cb_list_add ((yyvsp[(0) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 737:

/* Line 1455 of yacc.c  */
#line 4073 "parser.y"
    { terminator_warning (TERM_ADD); ;}
    break;

  case 738:

/* Line 1455 of yacc.c  */
#line 4074 "parser.y"
    { terminator_clear (TERM_ADD); ;}
    break;

  case 739:

/* Line 1455 of yacc.c  */
#line 4083 "parser.y"
    { BEGIN_STATEMENT ("ALLOCATE", 0); ;}
    break;

  case 741:

/* Line 1455 of yacc.c  */
#line 4089 "parser.y"
    {
	cb_emit_allocate ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), NULL, (yyvsp[(2) - (3)]));
  ;}
    break;

  case 742:

/* Line 1455 of yacc.c  */
#line 4093 "parser.y"
    {
	cb_emit_allocate (NULL, (yyvsp[(5) - (5)]), (yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]));
  ;}
    break;

  case 743:

/* Line 1455 of yacc.c  */
#line 4099 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 744:

/* Line 1455 of yacc.c  */
#line 4100 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 745:

/* Line 1455 of yacc.c  */
#line 4110 "parser.y"
    {
	cb_error (_("ALTER statement is obsolete and unsupported"));
  ;}
    break;

  case 750:

/* Line 1455 of yacc.c  */
#line 4128 "parser.y"
    { BEGIN_STATEMENT ("CALL", TERM_CALL); ;}
    break;

  case 751:

/* Line 1455 of yacc.c  */
#line 4132 "parser.y"
    {
	cb_emit_call ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 752:

/* Line 1455 of yacc.c  */
#line 4138 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 753:

/* Line 1455 of yacc.c  */
#line 4140 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 754:

/* Line 1455 of yacc.c  */
#line 4144 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 755:

/* Line 1455 of yacc.c  */
#line 4148 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 756:

/* Line 1455 of yacc.c  */
#line 4150 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 757:

/* Line 1455 of yacc.c  */
#line 4155 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OMITTED only allowed with BY REFERENCE"));
	}
	(yyval) = cb_build_pair (cb_int (call_mode), cb_null);
  ;}
    break;

  case 758:

/* Line 1455 of yacc.c  */
#line 4162 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), (yyvsp[(3) - (3)]));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 760:

/* Line 1455 of yacc.c  */
#line 4171 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 761:

/* Line 1455 of yacc.c  */
#line 4175 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY CONTENT not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_CONTENT;
	}
  ;}
    break;

  case 762:

/* Line 1455 of yacc.c  */
#line 4183 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 763:

/* Line 1455 of yacc.c  */
#line 4193 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 764:

/* Line 1455 of yacc.c  */
#line 4194 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 765:

/* Line 1455 of yacc.c  */
#line 4195 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 766:

/* Line 1455 of yacc.c  */
#line 4200 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 767:

/* Line 1455 of yacc.c  */
#line 4204 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 768:

/* Line 1455 of yacc.c  */
#line 4208 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 769:

/* Line 1455 of yacc.c  */
#line 4215 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 770:

/* Line 1455 of yacc.c  */
#line 4219 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 771:

/* Line 1455 of yacc.c  */
#line 4223 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 772:

/* Line 1455 of yacc.c  */
#line 4229 "parser.y"
    { terminator_warning (TERM_CALL); ;}
    break;

  case 773:

/* Line 1455 of yacc.c  */
#line 4230 "parser.y"
    { terminator_clear (TERM_CALL); ;}
    break;

  case 774:

/* Line 1455 of yacc.c  */
#line 4239 "parser.y"
    { BEGIN_STATEMENT ("CANCEL", 0); ;}
    break;

  case 777:

/* Line 1455 of yacc.c  */
#line 4245 "parser.y"
    {
	cb_emit_cancel ((yyvsp[(2) - (2)]));
  ;}
    break;

  case 778:

/* Line 1455 of yacc.c  */
#line 4256 "parser.y"
    { BEGIN_STATEMENT ("CLOSE", 0); ;}
    break;

  case 781:

/* Line 1455 of yacc.c  */
#line 4263 "parser.y"
    {
	BEGIN_IMPLICIT_STATEMENT ();
	if ((yyvsp[(2) - (3)]) != cb_error_node) {
		cb_emit_close ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
	}
  ;}
    break;

  case 782:

/* Line 1455 of yacc.c  */
#line 4272 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NORMAL); ;}
    break;

  case 783:

/* Line 1455 of yacc.c  */
#line 4273 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT); ;}
    break;

  case 784:

/* Line 1455 of yacc.c  */
#line 4274 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT_REMOVAL); ;}
    break;

  case 785:

/* Line 1455 of yacc.c  */
#line 4275 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NO_REWIND); ;}
    break;

  case 786:

/* Line 1455 of yacc.c  */
#line 4276 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_LOCK); ;}
    break;

  case 789:

/* Line 1455 of yacc.c  */
#line 4287 "parser.y"
    { BEGIN_STATEMENT ("COMPUTE", TERM_COMPUTE); ;}
    break;

  case 791:

/* Line 1455 of yacc.c  */
#line 4294 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(1) - (4)]), 0, (yyvsp[(3) - (4)]));
  ;}
    break;

  case 792:

/* Line 1455 of yacc.c  */
#line 4300 "parser.y"
    { terminator_warning (TERM_COMPUTE); ;}
    break;

  case 793:

/* Line 1455 of yacc.c  */
#line 4301 "parser.y"
    { terminator_clear (TERM_COMPUTE); ;}
    break;

  case 796:

/* Line 1455 of yacc.c  */
#line 4312 "parser.y"
    {
	BEGIN_STATEMENT ("COMMIT", 0);
	cb_emit_commit ();
  ;}
    break;

  case 797:

/* Line 1455 of yacc.c  */
#line 4325 "parser.y"
    {
	BEGIN_STATEMENT ("CONTINUE", 0);
	cb_emit_continue ();
  ;}
    break;

  case 798:

/* Line 1455 of yacc.c  */
#line 4337 "parser.y"
    { BEGIN_STATEMENT ("DELETE", TERM_DELETE); ;}
    break;

  case 799:

/* Line 1455 of yacc.c  */
#line 4340 "parser.y"
    {
	if ((yyvsp[(3) - (6)]) != cb_error_node) {
		cb_emit_delete ((yyvsp[(3) - (6)]));
	}
  ;}
    break;

  case 800:

/* Line 1455 of yacc.c  */
#line 4348 "parser.y"
    { terminator_warning (TERM_DELETE); ;}
    break;

  case 801:

/* Line 1455 of yacc.c  */
#line 4349 "parser.y"
    { terminator_clear (TERM_DELETE); ;}
    break;

  case 802:

/* Line 1455 of yacc.c  */
#line 4359 "parser.y"
    {
	BEGIN_STATEMENT ("DISPLAY", TERM_DISPLAY);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 804:

/* Line 1455 of yacc.c  */
#line 4372 "parser.y"
    {
	cb_emit_env_name ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 805:

/* Line 1455 of yacc.c  */
#line 4376 "parser.y"
    {
	cb_emit_env_value ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 806:

/* Line 1455 of yacc.c  */
#line 4380 "parser.y"
    {
	cb_emit_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 807:

/* Line 1455 of yacc.c  */
#line 4384 "parser.y"
    {
	cb_emit_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 808:

/* Line 1455 of yacc.c  */
#line 4388 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (4)]), cb_int0, (yyvsp[(3) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 809:

/* Line 1455 of yacc.c  */
#line 4392 "parser.y"
    {
	cb_emit_display_mnemonic ((yyvsp[(1) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 810:

/* Line 1455 of yacc.c  */
#line 4396 "parser.y"
    {
	cb_tree word = cb_build_display_upon_direct ((yyvsp[(4) - (6)]));
	cb_emit_display ((yyvsp[(1) - (6)]), word, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 811:

/* Line 1455 of yacc.c  */
#line 4401 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 812:

/* Line 1455 of yacc.c  */
#line 4405 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 813:

/* Line 1455 of yacc.c  */
#line 4411 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 814:

/* Line 1455 of yacc.c  */
#line 4412 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 815:

/* Line 1455 of yacc.c  */
#line 4413 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 818:

/* Line 1455 of yacc.c  */
#line 4423 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 819:

/* Line 1455 of yacc.c  */
#line 4424 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 820:

/* Line 1455 of yacc.c  */
#line 4425 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 821:

/* Line 1455 of yacc.c  */
#line 4426 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 822:

/* Line 1455 of yacc.c  */
#line 4427 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 823:

/* Line 1455 of yacc.c  */
#line 4428 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 824:

/* Line 1455 of yacc.c  */
#line 4429 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 825:

/* Line 1455 of yacc.c  */
#line 4430 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 826:

/* Line 1455 of yacc.c  */
#line 4431 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 827:

/* Line 1455 of yacc.c  */
#line 4433 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 828:

/* Line 1455 of yacc.c  */
#line 4437 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 829:

/* Line 1455 of yacc.c  */
#line 4441 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 830:

/* Line 1455 of yacc.c  */
#line 4445 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 831:

/* Line 1455 of yacc.c  */
#line 4449 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 832:

/* Line 1455 of yacc.c  */
#line 4450 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 833:

/* Line 1455 of yacc.c  */
#line 4454 "parser.y"
    { terminator_warning (TERM_DISPLAY); ;}
    break;

  case 834:

/* Line 1455 of yacc.c  */
#line 4455 "parser.y"
    { terminator_clear (TERM_DISPLAY); ;}
    break;

  case 835:

/* Line 1455 of yacc.c  */
#line 4464 "parser.y"
    { BEGIN_STATEMENT ("DIVIDE", TERM_DIVIDE); ;}
    break;

  case 837:

/* Line 1455 of yacc.c  */
#line 4471 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '/', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 838:

/* Line 1455 of yacc.c  */
#line 4475 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(3) - (6)]), '/', (yyvsp[(1) - (6)])));
  ;}
    break;

  case 839:

/* Line 1455 of yacc.c  */
#line 4479 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '/', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 840:

/* Line 1455 of yacc.c  */
#line 4483 "parser.y"
    {
	cb_emit_divide ((yyvsp[(3) - (8)]), (yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 841:

/* Line 1455 of yacc.c  */
#line 4487 "parser.y"
    {
	cb_emit_divide ((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 842:

/* Line 1455 of yacc.c  */
#line 4493 "parser.y"
    { terminator_warning (TERM_DIVIDE); ;}
    break;

  case 843:

/* Line 1455 of yacc.c  */
#line 4494 "parser.y"
    { terminator_clear (TERM_DIVIDE); ;}
    break;

  case 844:

/* Line 1455 of yacc.c  */
#line 4503 "parser.y"
    { BEGIN_STATEMENT ("ENTRY", 0); ;}
    break;

  case 845:

/* Line 1455 of yacc.c  */
#line 4505 "parser.y"
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

  case 846:

/* Line 1455 of yacc.c  */
#line 4525 "parser.y"
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

  case 847:

/* Line 1455 of yacc.c  */
#line 4536 "parser.y"
    {
	cb_emit_evaluate ((yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]));
	eval_level--;
  ;}
    break;

  case 848:

/* Line 1455 of yacc.c  */
#line 4543 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 849:

/* Line 1455 of yacc.c  */
#line 4546 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 850:

/* Line 1455 of yacc.c  */
#line 4556 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE_P ((yyvsp[(1) - (1)]))) {
		eval_check[eval_level][eval_inc++] = 0;
	} else {
		eval_check[eval_level][eval_inc++] = 1;
	}
  ;}
    break;

  case 851:

/* Line 1455 of yacc.c  */
#line 4565 "parser.y"
    {
	(yyval) = cb_true;
	eval_check[eval_level][eval_inc++] = 2;
  ;}
    break;

  case 852:

/* Line 1455 of yacc.c  */
#line 4570 "parser.y"
    {
	(yyval) = cb_false;
	eval_check[eval_level][eval_inc++] = 3;
  ;}
    break;

  case 853:

/* Line 1455 of yacc.c  */
#line 4578 "parser.y"
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

  case 854:

/* Line 1455 of yacc.c  */
#line 4606 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 855:

/* Line 1455 of yacc.c  */
#line 4608 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 856:

/* Line 1455 of yacc.c  */
#line 4613 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 857:

/* Line 1455 of yacc.c  */
#line 4617 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]));
	eval_inc2 = 0;
  ;}
    break;

  case 858:

/* Line 1455 of yacc.c  */
#line 4628 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 859:

/* Line 1455 of yacc.c  */
#line 4632 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 860:

/* Line 1455 of yacc.c  */
#line 4636 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), NULL);
	eval_inc2 = 0;
  ;}
    break;

  case 861:

/* Line 1455 of yacc.c  */
#line 4646 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 862:

/* Line 1455 of yacc.c  */
#line 4648 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 863:

/* Line 1455 of yacc.c  */
#line 4652 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 864:

/* Line 1455 of yacc.c  */
#line 4655 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 865:

/* Line 1455 of yacc.c  */
#line 4665 "parser.y"
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

  case 866:

/* Line 1455 of yacc.c  */
#line 4693 "parser.y"
    { (yyval) = cb_any; eval_inc2++; ;}
    break;

  case 867:

/* Line 1455 of yacc.c  */
#line 4694 "parser.y"
    { (yyval) = cb_true; eval_inc2++; ;}
    break;

  case 868:

/* Line 1455 of yacc.c  */
#line 4695 "parser.y"
    { (yyval) = cb_false; eval_inc2++; ;}
    break;

  case 869:

/* Line 1455 of yacc.c  */
#line 4698 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 870:

/* Line 1455 of yacc.c  */
#line 4699 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 871:

/* Line 1455 of yacc.c  */
#line 4703 "parser.y"
    { terminator_warning (TERM_EVALUATE); ;}
    break;

  case 872:

/* Line 1455 of yacc.c  */
#line 4704 "parser.y"
    { terminator_clear (TERM_EVALUATE); ;}
    break;

  case 873:

/* Line 1455 of yacc.c  */
#line 4713 "parser.y"
    { BEGIN_STATEMENT ("EXIT", 0); ;}
    break;

  case 875:

/* Line 1455 of yacc.c  */
#line 4718 "parser.y"
    { /* nothing */ ;}
    break;

  case 876:

/* Line 1455 of yacc.c  */
#line 4720 "parser.y"
    {
	if (in_declaratives && use_global_ind) {
		cb_error (_("EXIT PROGRAM is not allowed within a USE GLOBAL procedure"));
	}
	check_unreached = 1;
	cb_emit_exit (0);
  ;}
    break;

  case 877:

/* Line 1455 of yacc.c  */
#line 4728 "parser.y"
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

  case 878:

/* Line 1455 of yacc.c  */
#line 4745 "parser.y"
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

  case 879:

/* Line 1455 of yacc.c  */
#line 4762 "parser.y"
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

  case 880:

/* Line 1455 of yacc.c  */
#line 4780 "parser.y"
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

  case 881:

/* Line 1455 of yacc.c  */
#line 4804 "parser.y"
    { BEGIN_STATEMENT ("FREE", 0); ;}
    break;

  case 882:

/* Line 1455 of yacc.c  */
#line 4806 "parser.y"
    {
	cb_emit_free ((yyvsp[(3) - (3)]))
  ;}
    break;

  case 883:

/* Line 1455 of yacc.c  */
#line 4817 "parser.y"
    { BEGIN_STATEMENT ("GENERATE", 0); ;}
    break;

  case 884:

/* Line 1455 of yacc.c  */
#line 4819 "parser.y"
    {
	PENDING("GENERATE");
  ;}
    break;

  case 885:

/* Line 1455 of yacc.c  */
#line 4830 "parser.y"
    { BEGIN_STATEMENT ("GO TO", 0); ;}
    break;

  case 886:

/* Line 1455 of yacc.c  */
#line 4832 "parser.y"
    {
	cb_emit_goto ((yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 887:

/* Line 1455 of yacc.c  */
#line 4839 "parser.y"
    {
	check_unreached = 1;
	(yyval) = NULL;
  ;}
    break;

  case 888:

/* Line 1455 of yacc.c  */
#line 4844 "parser.y"
    {
	check_unreached = 0;
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 889:

/* Line 1455 of yacc.c  */
#line 4856 "parser.y"
    { BEGIN_STATEMENT ("GOBACK", 0); ;}
    break;

  case 890:

/* Line 1455 of yacc.c  */
#line 4857 "parser.y"
    {
	check_unreached = 1;
	cb_emit_exit (1);
  ;}
    break;

  case 891:

/* Line 1455 of yacc.c  */
#line 4869 "parser.y"
    { BEGIN_STATEMENT ("IF", TERM_IF); ;}
    break;

  case 892:

/* Line 1455 of yacc.c  */
#line 4871 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 893:

/* Line 1455 of yacc.c  */
#line 4876 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(6) - (8)]) == NULL) {
		cb_error (_("syntax error"));
	}
	cb_emit_if ((yyvsp[(3) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 895:

/* Line 1455 of yacc.c  */
#line 4887 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 896:

/* Line 1455 of yacc.c  */
#line 4891 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 897:

/* Line 1455 of yacc.c  */
#line 4895 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 898:

/* Line 1455 of yacc.c  */
#line 4904 "parser.y"
    { terminator_warning (TERM_IF); ;}
    break;

  case 899:

/* Line 1455 of yacc.c  */
#line 4905 "parser.y"
    { terminator_clear (TERM_IF); ;}
    break;

  case 900:

/* Line 1455 of yacc.c  */
#line 4914 "parser.y"
    { BEGIN_STATEMENT ("INITIALIZE", 0); ;}
    break;

  case 901:

/* Line 1455 of yacc.c  */
#line 4916 "parser.y"
    {
	cb_emit_initialize ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 902:

/* Line 1455 of yacc.c  */
#line 4922 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 903:

/* Line 1455 of yacc.c  */
#line 4923 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 904:

/* Line 1455 of yacc.c  */
#line 4927 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 905:

/* Line 1455 of yacc.c  */
#line 4928 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 906:

/* Line 1455 of yacc.c  */
#line 4929 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 907:

/* Line 1455 of yacc.c  */
#line 4933 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 908:

/* Line 1455 of yacc.c  */
#line 4935 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 909:

/* Line 1455 of yacc.c  */
#line 4939 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 910:

/* Line 1455 of yacc.c  */
#line 4941 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 911:

/* Line 1455 of yacc.c  */
#line 4945 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 912:

/* Line 1455 of yacc.c  */
#line 4949 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHABETIC); ;}
    break;

  case 913:

/* Line 1455 of yacc.c  */
#line 4950 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC); ;}
    break;

  case 914:

/* Line 1455 of yacc.c  */
#line 4951 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC); ;}
    break;

  case 915:

/* Line 1455 of yacc.c  */
#line 4952 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC_EDITED); ;}
    break;

  case 916:

/* Line 1455 of yacc.c  */
#line 4953 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC_EDITED); ;}
    break;

  case 917:

/* Line 1455 of yacc.c  */
#line 4954 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL); ;}
    break;

  case 918:

/* Line 1455 of yacc.c  */
#line 4955 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL_EDITED); ;}
    break;

  case 919:

/* Line 1455 of yacc.c  */
#line 4959 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 920:

/* Line 1455 of yacc.c  */
#line 4960 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 921:

/* Line 1455 of yacc.c  */
#line 4969 "parser.y"
    { BEGIN_STATEMENT ("INITIATE", 0); ;}
    break;

  case 922:

/* Line 1455 of yacc.c  */
#line 4971 "parser.y"
    {
	PENDING("INITIATE");
  ;}
    break;

  case 923:

/* Line 1455 of yacc.c  */
#line 4982 "parser.y"
    {
	BEGIN_STATEMENT ("INSPECT", 0);
	sending_id = 0;
	inspect_keyword = 0;
  ;}
    break;

  case 925:

/* Line 1455 of yacc.c  */
#line 4991 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 0; ;}
    break;

  case 926:

/* Line 1455 of yacc.c  */
#line 4992 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 927:

/* Line 1455 of yacc.c  */
#line 4993 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 930:

/* Line 1455 of yacc.c  */
#line 5002 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 0); ;}
    break;

  case 931:

/* Line 1455 of yacc.c  */
#line 5003 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int1, 1); ;}
    break;

  case 932:

/* Line 1455 of yacc.c  */
#line 5004 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 2); ;}
    break;

  case 933:

/* Line 1455 of yacc.c  */
#line 5010 "parser.y"
    { cb_init_tarrying (); ;}
    break;

  case 934:

/* Line 1455 of yacc.c  */
#line 5011 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 935:

/* Line 1455 of yacc.c  */
#line 5015 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 936:

/* Line 1455 of yacc.c  */
#line 5016 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 937:

/* Line 1455 of yacc.c  */
#line 5020 "parser.y"
    { (yyval) = cb_build_tarrying_data ((yyvsp[(1) - (2)])); ;}
    break;

  case 938:

/* Line 1455 of yacc.c  */
#line 5021 "parser.y"
    { (yyval) = cb_build_tarrying_characters ((yyvsp[(2) - (2)])); ;}
    break;

  case 939:

/* Line 1455 of yacc.c  */
#line 5022 "parser.y"
    { (yyval) = cb_build_tarrying_all (); ;}
    break;

  case 940:

/* Line 1455 of yacc.c  */
#line 5023 "parser.y"
    { (yyval) = cb_build_tarrying_leading (); ;}
    break;

  case 941:

/* Line 1455 of yacc.c  */
#line 5024 "parser.y"
    { (yyval) = cb_build_tarrying_trailing (); ;}
    break;

  case 942:

/* Line 1455 of yacc.c  */
#line 5025 "parser.y"
    { (yyval) = cb_build_tarrying_value ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 943:

/* Line 1455 of yacc.c  */
#line 5031 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); inspect_keyword = 0; ;}
    break;

  case 944:

/* Line 1455 of yacc.c  */
#line 5035 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 945:

/* Line 1455 of yacc.c  */
#line 5036 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 946:

/* Line 1455 of yacc.c  */
#line 5041 "parser.y"
    {
	(yyval) = cb_build_replacing_characters ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]), save_tree_1);
	inspect_keyword = 0;
  ;}
    break;

  case 947:

/* Line 1455 of yacc.c  */
#line 5045 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 948:

/* Line 1455 of yacc.c  */
#line 5049 "parser.y"
    { /* Nothing */ ;}
    break;

  case 949:

/* Line 1455 of yacc.c  */
#line 5050 "parser.y"
    { inspect_keyword = 1; ;}
    break;

  case 950:

/* Line 1455 of yacc.c  */
#line 5051 "parser.y"
    { inspect_keyword = 2; ;}
    break;

  case 951:

/* Line 1455 of yacc.c  */
#line 5052 "parser.y"
    { inspect_keyword = 3; ;}
    break;

  case 952:

/* Line 1455 of yacc.c  */
#line 5053 "parser.y"
    { inspect_keyword = 4; ;}
    break;

  case 953:

/* Line 1455 of yacc.c  */
#line 5058 "parser.y"
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

  case 954:

/* Line 1455 of yacc.c  */
#line 5084 "parser.y"
    {
	if (cb_validate_inspect (save_tree_1, (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])) < 0 ) {
		(yyval) = cb_error_node;
	} else {
		(yyval) = cb_build_converting ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 955:

/* Line 1455 of yacc.c  */
#line 5096 "parser.y"
    { (yyval) = cb_build_inspect_region_start (); ;}
    break;

  case 956:

/* Line 1455 of yacc.c  */
#line 5098 "parser.y"
    { (yyval) = cb_build_inspect_region ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 959:

/* Line 1455 of yacc.c  */
#line 5109 "parser.y"
    { BEGIN_STATEMENT ("MERGE", 0); ;}
    break;

  case 961:

/* Line 1455 of yacc.c  */
#line 5119 "parser.y"
    { BEGIN_STATEMENT ("MOVE", 0); ;}
    break;

  case 963:

/* Line 1455 of yacc.c  */
#line 5125 "parser.y"
    {
	cb_emit_move ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 964:

/* Line 1455 of yacc.c  */
#line 5129 "parser.y"
    {
	cb_emit_move_corresponding ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 965:

/* Line 1455 of yacc.c  */
#line 5140 "parser.y"
    { BEGIN_STATEMENT ("MULTIPLY", TERM_MULTIPLY); ;}
    break;

  case 967:

/* Line 1455 of yacc.c  */
#line 5147 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '*', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 968:

/* Line 1455 of yacc.c  */
#line 5151 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '*', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 969:

/* Line 1455 of yacc.c  */
#line 5157 "parser.y"
    { terminator_warning (TERM_MULTIPLY); ;}
    break;

  case 970:

/* Line 1455 of yacc.c  */
#line 5158 "parser.y"
    { terminator_clear (TERM_MULTIPLY); ;}
    break;

  case 971:

/* Line 1455 of yacc.c  */
#line 5167 "parser.y"
    { BEGIN_STATEMENT ("OPEN", 0); ;}
    break;

  case 974:

/* Line 1455 of yacc.c  */
#line 5174 "parser.y"
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

  case 975:

/* Line 1455 of yacc.c  */
#line 5186 "parser.y"
    { (yyval) = cb_int (COB_OPEN_INPUT); ;}
    break;

  case 976:

/* Line 1455 of yacc.c  */
#line 5187 "parser.y"
    { (yyval) = cb_int (COB_OPEN_OUTPUT); ;}
    break;

  case 977:

/* Line 1455 of yacc.c  */
#line 5188 "parser.y"
    { (yyval) = cb_int (COB_OPEN_I_O); ;}
    break;

  case 978:

/* Line 1455 of yacc.c  */
#line 5189 "parser.y"
    { (yyval) = cb_int (COB_OPEN_EXTEND); ;}
    break;

  case 979:

/* Line 1455 of yacc.c  */
#line 5193 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 980:

/* Line 1455 of yacc.c  */
#line 5194 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 981:

/* Line 1455 of yacc.c  */
#line 5198 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 982:

/* Line 1455 of yacc.c  */
#line 5199 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 983:

/* Line 1455 of yacc.c  */
#line 5200 "parser.y"
    { PENDING ("OPEN ... WITH LOCK"); ;}
    break;

  case 984:

/* Line 1455 of yacc.c  */
#line 5212 "parser.y"
    { BEGIN_STATEMENT ("PERFORM", TERM_PERFORM); ;}
    break;

  case 986:

/* Line 1455 of yacc.c  */
#line 5218 "parser.y"
    {
	cb_emit_perform ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));
  ;}
    break;

  case 987:

/* Line 1455 of yacc.c  */
#line 5222 "parser.y"
    {
	perform_stack = cb_cons ((yyvsp[(1) - (1)]), perform_stack);
	check_unreached = 0;
  ;}
    break;

  case 988:

/* Line 1455 of yacc.c  */
#line 5227 "parser.y"
    {
	perform_stack = CB_CHAIN (perform_stack);
	cb_emit_perform ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 989:

/* Line 1455 of yacc.c  */
#line 5232 "parser.y"
    {
	cb_emit_perform ((yyvsp[(1) - (2)]), NULL);
  ;}
    break;

  case 990:

/* Line 1455 of yacc.c  */
#line 5238 "parser.y"
    { terminator_error (); ;}
    break;

  case 991:

/* Line 1455 of yacc.c  */
#line 5239 "parser.y"
    { terminator_clear (TERM_PERFORM); ;}
    break;

  case 992:

/* Line 1455 of yacc.c  */
#line 5244 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(1) - (1)]))->length = cb_true; /* return from $1 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (1)]), (yyvsp[(1) - (1)]));
  ;}
    break;

  case 993:

/* Line 1455 of yacc.c  */
#line 5249 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(3) - (3)]))->length = cb_true; /* return from $3 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 994:

/* Line 1455 of yacc.c  */
#line 5257 "parser.y"
    {
	(yyval) = cb_build_perform_once (NULL);
  ;}
    break;

  case 995:

/* Line 1455 of yacc.c  */
#line 5261 "parser.y"
    {
	(yyval) = cb_build_perform_forever (NULL);
  ;}
    break;

  case 996:

/* Line 1455 of yacc.c  */
#line 5265 "parser.y"
    {
	(yyval) = cb_build_perform_times ((yyvsp[(1) - (2)]));
	current_program->loop_counter++;
  ;}
    break;

  case 997:

/* Line 1455 of yacc.c  */
#line 5270 "parser.y"
    {
	cb_tree varying;

	varying = cb_list_init (cb_build_perform_varying (NULL, NULL, NULL, (yyvsp[(3) - (3)])));
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), varying);
  ;}
    break;

  case 998:

/* Line 1455 of yacc.c  */
#line 5277 "parser.y"
    {
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 999:

/* Line 1455 of yacc.c  */
#line 5283 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1000:

/* Line 1455 of yacc.c  */
#line 5284 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1001:

/* Line 1455 of yacc.c  */
#line 5288 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1002:

/* Line 1455 of yacc.c  */
#line 5290 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1003:

/* Line 1455 of yacc.c  */
#line 5295 "parser.y"
    {
	(yyval) = cb_build_perform_varying ((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1004:

/* Line 1455 of yacc.c  */
#line 5306 "parser.y"
    { BEGIN_STATEMENT ("READ", TERM_READ); ;}
    break;

  case 1005:

/* Line 1455 of yacc.c  */
#line 5309 "parser.y"
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

  case 1006:

/* Line 1455 of yacc.c  */
#line 5329 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1007:

/* Line 1455 of yacc.c  */
#line 5330 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1008:

/* Line 1455 of yacc.c  */
#line 5334 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1009:

/* Line 1455 of yacc.c  */
#line 5336 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1010:

/* Line 1455 of yacc.c  */
#line 5340 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1011:

/* Line 1455 of yacc.c  */
#line 5344 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1012:

/* Line 1455 of yacc.c  */
#line 5348 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1013:

/* Line 1455 of yacc.c  */
#line 5352 "parser.y"
    {
	(yyval) = cb_int4;
  ;}
    break;

  case 1014:

/* Line 1455 of yacc.c  */
#line 5358 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1015:

/* Line 1455 of yacc.c  */
#line 5359 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1019:

/* Line 1455 of yacc.c  */
#line 5368 "parser.y"
    { terminator_warning (TERM_READ); ;}
    break;

  case 1020:

/* Line 1455 of yacc.c  */
#line 5369 "parser.y"
    { terminator_clear (TERM_READ); ;}
    break;

  case 1021:

/* Line 1455 of yacc.c  */
#line 5378 "parser.y"
    { BEGIN_STATEMENT ("RELEASE", 0); ;}
    break;

  case 1022:

/* Line 1455 of yacc.c  */
#line 5380 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_release ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
	}
  ;}
    break;

  case 1023:

/* Line 1455 of yacc.c  */
#line 5393 "parser.y"
    { BEGIN_STATEMENT ("RETURN", TERM_RETURN); ;}
    break;

  case 1024:

/* Line 1455 of yacc.c  */
#line 5396 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_return ((yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]));
	}
  ;}
    break;

  case 1025:

/* Line 1455 of yacc.c  */
#line 5404 "parser.y"
    { terminator_warning (TERM_RETURN); ;}
    break;

  case 1026:

/* Line 1455 of yacc.c  */
#line 5405 "parser.y"
    { terminator_clear (TERM_RETURN); ;}
    break;

  case 1027:

/* Line 1455 of yacc.c  */
#line 5414 "parser.y"
    { BEGIN_STATEMENT ("REWRITE", TERM_REWRITE); ;}
    break;

  case 1028:

/* Line 1455 of yacc.c  */
#line 5417 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_rewrite ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]));
	}
  ;}
    break;

  case 1029:

/* Line 1455 of yacc.c  */
#line 5425 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1030:

/* Line 1455 of yacc.c  */
#line 5427 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1031:

/* Line 1455 of yacc.c  */
#line 5431 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1032:

/* Line 1455 of yacc.c  */
#line 5437 "parser.y"
    { terminator_warning (TERM_REWRITE); ;}
    break;

  case 1033:

/* Line 1455 of yacc.c  */
#line 5438 "parser.y"
    { terminator_clear (TERM_REWRITE); ;}
    break;

  case 1034:

/* Line 1455 of yacc.c  */
#line 5448 "parser.y"
    {
	BEGIN_STATEMENT ("ROLLBACK", 0);
	cb_emit_rollback ();
  ;}
    break;

  case 1035:

/* Line 1455 of yacc.c  */
#line 5460 "parser.y"
    { BEGIN_STATEMENT ("SEARCH", TERM_SEARCH); ;}
    break;

  case 1037:

/* Line 1455 of yacc.c  */
#line 5467 "parser.y"
    {
	cb_emit_search ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1038:

/* Line 1455 of yacc.c  */
#line 5471 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1039:

/* Line 1455 of yacc.c  */
#line 5475 "parser.y"
    {
	cb_emit_search_all ((yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1040:

/* Line 1455 of yacc.c  */
#line 5481 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1041:

/* Line 1455 of yacc.c  */
#line 5482 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1042:

/* Line 1455 of yacc.c  */
#line 5486 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1043:

/* Line 1455 of yacc.c  */
#line 5488 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1044:

/* Line 1455 of yacc.c  */
#line 5492 "parser.y"
    {
	(yyval) = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 1045:

/* Line 1455 of yacc.c  */
#line 5498 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1046:

/* Line 1455 of yacc.c  */
#line 5499 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); CB_IF ((yyvsp[(1) - (2)]))->stmt2 = (yyvsp[(2) - (2)]); ;}
    break;

  case 1047:

/* Line 1455 of yacc.c  */
#line 5504 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1048:

/* Line 1455 of yacc.c  */
#line 5508 "parser.y"
    {
	(yyval) = cb_build_if ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), NULL);
  ;}
    break;

  case 1049:

/* Line 1455 of yacc.c  */
#line 5514 "parser.y"
    { terminator_warning (TERM_SEARCH); ;}
    break;

  case 1050:

/* Line 1455 of yacc.c  */
#line 5515 "parser.y"
    { terminator_clear (TERM_SEARCH); ;}
    break;

  case 1051:

/* Line 1455 of yacc.c  */
#line 5524 "parser.y"
    { BEGIN_STATEMENT ("SET", 0); ;}
    break;

  case 1058:

/* Line 1455 of yacc.c  */
#line 5540 "parser.y"
    {
	cb_emit_setenv ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1059:

/* Line 1455 of yacc.c  */
#line 5549 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (4)]), cb_build_ppointer ((yyvsp[(4) - (4)])));
  ;}
    break;

  case 1060:

/* Line 1455 of yacc.c  */
#line 5553 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1061:

/* Line 1455 of yacc.c  */
#line 5562 "parser.y"
    {
	cb_emit_set_up_down ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1062:

/* Line 1455 of yacc.c  */
#line 5568 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1063:

/* Line 1455 of yacc.c  */
#line 5569 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1066:

/* Line 1455 of yacc.c  */
#line 5581 "parser.y"
    {
	cb_emit_set_on_off ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1069:

/* Line 1455 of yacc.c  */
#line 5595 "parser.y"
    {
	cb_emit_set_true ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1070:

/* Line 1455 of yacc.c  */
#line 5599 "parser.y"
    {
	cb_emit_set_false ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1071:

/* Line 1455 of yacc.c  */
#line 5610 "parser.y"
    { BEGIN_STATEMENT ("SORT", 0); ;}
    break;

  case 1073:

/* Line 1455 of yacc.c  */
#line 5616 "parser.y"
    {
	cb_emit_sort_init ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (4)]))) && (yyvsp[(2) - (4)]) == NULL) {
		cb_error (_("File sort requires KEY phrase"));
	}
	/* used in sort_input/sort_output */
	save_tree_1 = (yyvsp[(1) - (4)]);
  ;}
    break;

  case 1074:

/* Line 1455 of yacc.c  */
#line 5625 "parser.y"
    {
	cb_emit_sort_finish ((yyvsp[(1) - (7)]));
  ;}
    break;

  case 1075:

/* Line 1455 of yacc.c  */
#line 5632 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 1076:

/* Line 1455 of yacc.c  */
#line 5637 "parser.y"
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

  case 1077:

/* Line 1455 of yacc.c  */
#line 5651 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1078:

/* Line 1455 of yacc.c  */
#line 5652 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1080:

/* Line 1455 of yacc.c  */
#line 5656 "parser.y"
    { /* nothing */ ;}
    break;

  case 1081:

/* Line 1455 of yacc.c  */
#line 5660 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1082:

/* Line 1455 of yacc.c  */
#line 5661 "parser.y"
    { (yyval) = cb_ref ((yyvsp[(3) - (3)])); ;}
    break;

  case 1083:

/* Line 1455 of yacc.c  */
#line 5666 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires USING or INPUT PROCEDURE"));
	}
  ;}
    break;

  case 1084:

/* Line 1455 of yacc.c  */
#line 5672 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("USING invalid with table SORT"));
	} else {
		cb_emit_sort_using (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1085:

/* Line 1455 of yacc.c  */
#line 5680 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("INPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_input ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1086:

/* Line 1455 of yacc.c  */
#line 5691 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires GIVING or OUTPUT PROCEDURE"));
	}
  ;}
    break;

  case 1087:

/* Line 1455 of yacc.c  */
#line 5697 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("GIVING invalid with table SORT"));
	} else {
		cb_emit_sort_giving (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1088:

/* Line 1455 of yacc.c  */
#line 5705 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("OUTPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_output ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1089:

/* Line 1455 of yacc.c  */
#line 5720 "parser.y"
    { BEGIN_STATEMENT ("START", TERM_START); ;}
    break;

  case 1090:

/* Line 1455 of yacc.c  */
#line 5721 "parser.y"
    { (yyval) = cb_int (COB_EQ); ;}
    break;

  case 1091:

/* Line 1455 of yacc.c  */
#line 5724 "parser.y"
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

  case 1092:

/* Line 1455 of yacc.c  */
#line 5741 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1093:

/* Line 1455 of yacc.c  */
#line 5742 "parser.y"
    { (yyvsp[(0) - (4)]) = (yyvsp[(3) - (4)]); (yyval) = (yyvsp[(4) - (4)]); ;}
    break;

  case 1094:

/* Line 1455 of yacc.c  */
#line 5746 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_NE : COB_EQ); ;}
    break;

  case 1095:

/* Line 1455 of yacc.c  */
#line 5747 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LE : COB_GT); ;}
    break;

  case 1096:

/* Line 1455 of yacc.c  */
#line 5748 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GE : COB_LT); ;}
    break;

  case 1097:

/* Line 1455 of yacc.c  */
#line 5749 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LT : COB_GE); ;}
    break;

  case 1098:

/* Line 1455 of yacc.c  */
#line 5750 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GT : COB_LE); ;}
    break;

  case 1099:

/* Line 1455 of yacc.c  */
#line 5754 "parser.y"
    { terminator_warning (TERM_START); ;}
    break;

  case 1100:

/* Line 1455 of yacc.c  */
#line 5755 "parser.y"
    { terminator_clear (TERM_START); ;}
    break;

  case 1101:

/* Line 1455 of yacc.c  */
#line 5764 "parser.y"
    { BEGIN_STATEMENT ("STOP", 0); ;}
    break;

  case 1102:

/* Line 1455 of yacc.c  */
#line 5766 "parser.y"
    {
	cb_emit_stop_run ((yyvsp[(4) - (4)]));
  ;}
    break;

  case 1103:

/* Line 1455 of yacc.c  */
#line 5770 "parser.y"
    {
	cb_verify (cb_stop_literal_statement, "STOP literal");
  ;}
    break;

  case 1104:

/* Line 1455 of yacc.c  */
#line 5776 "parser.y"
    { (yyval) = current_program->cb_return_code; ;}
    break;

  case 1105:

/* Line 1455 of yacc.c  */
#line 5777 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1106:

/* Line 1455 of yacc.c  */
#line 5778 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1107:

/* Line 1455 of yacc.c  */
#line 5787 "parser.y"
    { BEGIN_STATEMENT ("STRING", TERM_STRING); ;}
    break;

  case 1108:

/* Line 1455 of yacc.c  */
#line 5790 "parser.y"
    {
	cb_emit_string ((yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]));
  ;}
    break;

  case 1109:

/* Line 1455 of yacc.c  */
#line 5796 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1110:

/* Line 1455 of yacc.c  */
#line 5797 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1111:

/* Line 1455 of yacc.c  */
#line 5801 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1112:

/* Line 1455 of yacc.c  */
#line 5802 "parser.y"
    { (yyval) = cb_build_pair (cb_int0, NULL); ;}
    break;

  case 1113:

/* Line 1455 of yacc.c  */
#line 5803 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), NULL); ;}
    break;

  case 1114:

/* Line 1455 of yacc.c  */
#line 5807 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1115:

/* Line 1455 of yacc.c  */
#line 5808 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1116:

/* Line 1455 of yacc.c  */
#line 5812 "parser.y"
    { terminator_warning (TERM_STRING); ;}
    break;

  case 1117:

/* Line 1455 of yacc.c  */
#line 5813 "parser.y"
    { terminator_clear (TERM_STRING); ;}
    break;

  case 1118:

/* Line 1455 of yacc.c  */
#line 5822 "parser.y"
    { BEGIN_STATEMENT ("SUBTRACT", TERM_SUBTRACT); ;}
    break;

  case 1120:

/* Line 1455 of yacc.c  */
#line 5829 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '-', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 1121:

/* Line 1455 of yacc.c  */
#line 5833 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_list (cb_cons ((yyvsp[(3) - (6)]), (yyvsp[(1) - (6)])), '-'));
  ;}
    break;

  case 1122:

/* Line 1455 of yacc.c  */
#line 5837 "parser.y"
    {
	cb_emit_corresponding (cb_build_sub, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 1123:

/* Line 1455 of yacc.c  */
#line 5843 "parser.y"
    { terminator_warning (TERM_SUBTRACT); ;}
    break;

  case 1124:

/* Line 1455 of yacc.c  */
#line 5844 "parser.y"
    { terminator_clear (TERM_SUBTRACT); ;}
    break;

  case 1125:

/* Line 1455 of yacc.c  */
#line 5854 "parser.y"
    {
	BEGIN_STATEMENT ("SUPPRESS", 0);
	PENDING("SUPPRESS");
  ;}
    break;

  case 1128:

/* Line 1455 of yacc.c  */
#line 5869 "parser.y"
    { BEGIN_STATEMENT ("TERMINATE", 0); ;}
    break;

  case 1129:

/* Line 1455 of yacc.c  */
#line 5871 "parser.y"
    {
	PENDING("TERMINATE");
  ;}
    break;

  case 1130:

/* Line 1455 of yacc.c  */
#line 5882 "parser.y"
    { BEGIN_STATEMENT ("TRANSFORM", 0); ;}
    break;

  case 1131:

/* Line 1455 of yacc.c  */
#line 5884 "parser.y"
    {
	cb_tree		x;

	x = cb_build_converting ((yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]), cb_build_inspect_region_start ());
	cb_emit_inspect ((yyvsp[(3) - (7)]), x, cb_int0, 2);
  ;}
    break;

  case 1132:

/* Line 1455 of yacc.c  */
#line 5898 "parser.y"
    { BEGIN_STATEMENT ("UNLOCK", 0); ;}
    break;

  case 1133:

/* Line 1455 of yacc.c  */
#line 5900 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_unlock ((yyvsp[(3) - (4)]));
	}
  ;}
    break;

  case 1137:

/* Line 1455 of yacc.c  */
#line 5919 "parser.y"
    { BEGIN_STATEMENT ("UNSTRING", TERM_UNSTRING); ;}
    break;

  case 1138:

/* Line 1455 of yacc.c  */
#line 5923 "parser.y"
    {
	cb_emit_unstring ((yyvsp[(3) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]));
  ;}
    break;

  case 1139:

/* Line 1455 of yacc.c  */
#line 5929 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1140:

/* Line 1455 of yacc.c  */
#line 5931 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1141:

/* Line 1455 of yacc.c  */
#line 5935 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1142:

/* Line 1455 of yacc.c  */
#line 5937 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1143:

/* Line 1455 of yacc.c  */
#line 5942 "parser.y"
    {
	(yyval) = cb_build_unstring_delimited ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1144:

/* Line 1455 of yacc.c  */
#line 5948 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 1145:

/* Line 1455 of yacc.c  */
#line 5950 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1146:

/* Line 1455 of yacc.c  */
#line 5955 "parser.y"
    {
	(yyval) = cb_build_unstring_into ((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1147:

/* Line 1455 of yacc.c  */
#line 5961 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1148:

/* Line 1455 of yacc.c  */
#line 5962 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1149:

/* Line 1455 of yacc.c  */
#line 5966 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1150:

/* Line 1455 of yacc.c  */
#line 5967 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1151:

/* Line 1455 of yacc.c  */
#line 5971 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1152:

/* Line 1455 of yacc.c  */
#line 5972 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1153:

/* Line 1455 of yacc.c  */
#line 5976 "parser.y"
    { terminator_warning (TERM_UNSTRING); ;}
    break;

  case 1154:

/* Line 1455 of yacc.c  */
#line 5977 "parser.y"
    { terminator_clear (TERM_UNSTRING); ;}
    break;

  case 1158:

/* Line 1455 of yacc.c  */
#line 5995 "parser.y"
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

  case 1159:

/* Line 1455 of yacc.c  */
#line 6016 "parser.y"
    {
	use_global_ind = 0;
  ;}
    break;

  case 1160:

/* Line 1455 of yacc.c  */
#line 6020 "parser.y"
    {
	use_global_ind = 1;
	current_program->flag_global_use = 1;
  ;}
    break;

  case 1161:

/* Line 1455 of yacc.c  */
#line 6028 "parser.y"
    {
	cb_tree		l;

	for (l = (yyvsp[(1) - (1)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			setup_use_file (CB_FILE (cb_ref (CB_VALUE (l))));
		}
	}
  ;}
    break;

  case 1162:

/* Line 1455 of yacc.c  */
#line 6038 "parser.y"
    {
	current_program->global_handler[COB_OPEN_INPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_INPUT].handler_prog = current_program;
  ;}
    break;

  case 1163:

/* Line 1455 of yacc.c  */
#line 6043 "parser.y"
    {
	current_program->global_handler[COB_OPEN_OUTPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_OUTPUT].handler_prog = current_program;
  ;}
    break;

  case 1164:

/* Line 1455 of yacc.c  */
#line 6048 "parser.y"
    {
	current_program->global_handler[COB_OPEN_I_O].handler_label = current_section;
	current_program->global_handler[COB_OPEN_I_O].handler_prog = current_program;
  ;}
    break;

  case 1165:

/* Line 1455 of yacc.c  */
#line 6053 "parser.y"
    {
	current_program->global_handler[COB_OPEN_EXTEND].handler_label = current_section;
	current_program->global_handler[COB_OPEN_EXTEND].handler_prog = current_program;
  ;}
    break;

  case 1178:

/* Line 1455 of yacc.c  */
#line 6085 "parser.y"
    {
	PENDING ("USE FOR DEBUGGING");
  ;}
    break;

  case 1181:

/* Line 1455 of yacc.c  */
#line 6097 "parser.y"
    {
	PENDING ("USE BEFORE REPORTING");
  ;}
    break;

  case 1182:

/* Line 1455 of yacc.c  */
#line 6108 "parser.y"
    { BEGIN_STATEMENT ("WRITE", TERM_WRITE); ;}
    break;

  case 1183:

/* Line 1455 of yacc.c  */
#line 6111 "parser.y"
    {
	if ((yyvsp[(3) - (8)]) != cb_error_node) {
		cb_emit_write ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(5) - (8)]));
	}
  ;}
    break;

  case 1184:

/* Line 1455 of yacc.c  */
#line 6119 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1185:

/* Line 1455 of yacc.c  */
#line 6120 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1186:

/* Line 1455 of yacc.c  */
#line 6125 "parser.y"
    {
	(yyval) = cb_int0;
  ;}
    break;

  case 1187:

/* Line 1455 of yacc.c  */
#line 6129 "parser.y"
    {
	(yyval) = cb_build_write_advancing_lines ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 1188:

/* Line 1455 of yacc.c  */
#line 6133 "parser.y"
    {
	(yyval) = cb_build_write_advancing_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1189:

/* Line 1455 of yacc.c  */
#line 6137 "parser.y"
    {
	(yyval) = cb_build_write_advancing_page ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1190:

/* Line 1455 of yacc.c  */
#line 6143 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1191:

/* Line 1455 of yacc.c  */
#line 6144 "parser.y"
    { (yyval) = CB_AFTER; ;}
    break;

  case 1195:

/* Line 1455 of yacc.c  */
#line 6153 "parser.y"
    { terminator_warning (TERM_WRITE); ;}
    break;

  case 1196:

/* Line 1455 of yacc.c  */
#line 6154 "parser.y"
    { terminator_clear (TERM_WRITE); ;}
    break;

  case 1197:

/* Line 1455 of yacc.c  */
#line 6169 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_ACCEPT;
  ;}
    break;

  case 1198:

/* Line 1455 of yacc.c  */
#line 6177 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_DISPLAY;
  ;}
    break;

  case 1200:

/* Line 1455 of yacc.c  */
#line 6184 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1201:

/* Line 1455 of yacc.c  */
#line 6188 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1203:

/* Line 1455 of yacc.c  */
#line 6195 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1204:

/* Line 1455 of yacc.c  */
#line 6199 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1207:

/* Line 1455 of yacc.c  */
#line 6215 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1208:

/* Line 1455 of yacc.c  */
#line 6220 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1210:

/* Line 1455 of yacc.c  */
#line 6227 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1211:

/* Line 1455 of yacc.c  */
#line 6232 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1212:

/* Line 1455 of yacc.c  */
#line 6244 "parser.y"
    {
	current_statement->handler_id = COB_EC_OVERFLOW;
  ;}
    break;

  case 1214:

/* Line 1455 of yacc.c  */
#line 6251 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1215:

/* Line 1455 of yacc.c  */
#line 6255 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1217:

/* Line 1455 of yacc.c  */
#line 6262 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1218:

/* Line 1455 of yacc.c  */
#line 6266 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1219:

/* Line 1455 of yacc.c  */
#line 6278 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1220:

/* Line 1455 of yacc.c  */
#line 6283 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1221:

/* Line 1455 of yacc.c  */
#line 6288 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1222:

/* Line 1455 of yacc.c  */
#line 6297 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1223:

/* Line 1455 of yacc.c  */
#line 6301 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1224:

/* Line 1455 of yacc.c  */
#line 6308 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1225:

/* Line 1455 of yacc.c  */
#line 6312 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1226:

/* Line 1455 of yacc.c  */
#line 6324 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1227:

/* Line 1455 of yacc.c  */
#line 6329 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1228:

/* Line 1455 of yacc.c  */
#line 6334 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1229:

/* Line 1455 of yacc.c  */
#line 6343 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1230:

/* Line 1455 of yacc.c  */
#line 6347 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1231:

/* Line 1455 of yacc.c  */
#line 6354 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1232:

/* Line 1455 of yacc.c  */
#line 6358 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1235:

/* Line 1455 of yacc.c  */
#line 6374 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1236:

/* Line 1455 of yacc.c  */
#line 6379 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1237:

/* Line 1455 of yacc.c  */
#line 6384 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1238:

/* Line 1455 of yacc.c  */
#line 6393 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1239:

/* Line 1455 of yacc.c  */
#line 6397 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1240:

/* Line 1455 of yacc.c  */
#line 6404 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1241:

/* Line 1455 of yacc.c  */
#line 6408 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1242:

/* Line 1455 of yacc.c  */
#line 6420 "parser.y"
    {
	(yyval) = cb_one;
  ;}
    break;

  case 1243:

/* Line 1455 of yacc.c  */
#line 6424 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 1244:

/* Line 1455 of yacc.c  */
#line 6436 "parser.y"
    {
	(yyval) = cb_build_cond ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1245:

/* Line 1455 of yacc.c  */
#line 6443 "parser.y"
    {
	(yyval) = cb_build_expr ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1246:

/* Line 1455 of yacc.c  */
#line 6449 "parser.y"
    {
	current_expr = NULL;
  ;}
    break;

  case 1247:

/* Line 1455 of yacc.c  */
#line 6453 "parser.y"
    {
	(yyval) = cb_list_reverse (current_expr);
  ;}
    break;

  case 1249:

/* Line 1455 of yacc.c  */
#line 6460 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1250:

/* Line 1455 of yacc.c  */
#line 6461 "parser.y"
    { push_expr (')', NULL); ;}
    break;

  case 1251:

/* Line 1455 of yacc.c  */
#line 6463 "parser.y"
    { push_expr ('O', NULL); ;}
    break;

  case 1252:

/* Line 1455 of yacc.c  */
#line 6464 "parser.y"
    { push_expr ('9', NULL); ;}
    break;

  case 1253:

/* Line 1455 of yacc.c  */
#line 6465 "parser.y"
    { push_expr ('A', NULL); ;}
    break;

  case 1254:

/* Line 1455 of yacc.c  */
#line 6466 "parser.y"
    { push_expr ('L', NULL); ;}
    break;

  case 1255:

/* Line 1455 of yacc.c  */
#line 6467 "parser.y"
    { push_expr ('U', NULL); ;}
    break;

  case 1256:

/* Line 1455 of yacc.c  */
#line 6468 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1257:

/* Line 1455 of yacc.c  */
#line 6470 "parser.y"
    { push_expr ('P', NULL); ;}
    break;

  case 1258:

/* Line 1455 of yacc.c  */
#line 6471 "parser.y"
    { push_expr ('N', NULL); ;}
    break;

  case 1259:

/* Line 1455 of yacc.c  */
#line 6472 "parser.y"
    { push_expr ('x', cb_zero); ;}
    break;

  case 1260:

/* Line 1455 of yacc.c  */
#line 6474 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1263:

/* Line 1455 of yacc.c  */
#line 6480 "parser.y"
    { push_expr ('(', NULL); ;}
    break;

  case 1264:

/* Line 1455 of yacc.c  */
#line 6482 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1265:

/* Line 1455 of yacc.c  */
#line 6483 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1266:

/* Line 1455 of yacc.c  */
#line 6484 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1267:

/* Line 1455 of yacc.c  */
#line 6486 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1268:

/* Line 1455 of yacc.c  */
#line 6488 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1269:

/* Line 1455 of yacc.c  */
#line 6489 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1270:

/* Line 1455 of yacc.c  */
#line 6490 "parser.y"
    { push_expr ('*', NULL); ;}
    break;

  case 1271:

/* Line 1455 of yacc.c  */
#line 6491 "parser.y"
    { push_expr ('/', NULL); ;}
    break;

  case 1272:

/* Line 1455 of yacc.c  */
#line 6492 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1273:

/* Line 1455 of yacc.c  */
#line 6494 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1274:

/* Line 1455 of yacc.c  */
#line 6495 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1275:

/* Line 1455 of yacc.c  */
#line 6496 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1276:

/* Line 1455 of yacc.c  */
#line 6497 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1277:

/* Line 1455 of yacc.c  */
#line 6498 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1278:

/* Line 1455 of yacc.c  */
#line 6499 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1279:

/* Line 1455 of yacc.c  */
#line 6501 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1280:

/* Line 1455 of yacc.c  */
#line 6502 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1281:

/* Line 1455 of yacc.c  */
#line 6503 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1282:

/* Line 1455 of yacc.c  */
#line 6504 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1283:

/* Line 1455 of yacc.c  */
#line 6505 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1284:

/* Line 1455 of yacc.c  */
#line 6506 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1285:

/* Line 1455 of yacc.c  */
#line 6508 "parser.y"
    { push_expr ('&', NULL); ;}
    break;

  case 1286:

/* Line 1455 of yacc.c  */
#line 6509 "parser.y"
    { push_expr ('|', NULL); ;}
    break;

  case 1298:

/* Line 1455 of yacc.c  */
#line 6521 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1299:

/* Line 1455 of yacc.c  */
#line 6522 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1303:

/* Line 1455 of yacc.c  */
#line 6531 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1304:

/* Line 1455 of yacc.c  */
#line 6532 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '+', (yyvsp[(3) - (3)])); ;}
    break;

  case 1305:

/* Line 1455 of yacc.c  */
#line 6533 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '-', (yyvsp[(3) - (3)])); ;}
    break;

  case 1306:

/* Line 1455 of yacc.c  */
#line 6534 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '*', (yyvsp[(3) - (3)])); ;}
    break;

  case 1307:

/* Line 1455 of yacc.c  */
#line 6535 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '/', (yyvsp[(3) - (3)])); ;}
    break;

  case 1308:

/* Line 1455 of yacc.c  */
#line 6536 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1309:

/* Line 1455 of yacc.c  */
#line 6537 "parser.y"
    { (yyval) = cb_build_binary_op (cb_zero, '-', (yyvsp[(2) - (2)])); ;}
    break;

  case 1310:

/* Line 1455 of yacc.c  */
#line 6538 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '^', (yyvsp[(3) - (3)])); ;}
    break;

  case 1311:

/* Line 1455 of yacc.c  */
#line 6539 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1312:

/* Line 1455 of yacc.c  */
#line 6551 "parser.y"
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

  case 1313:

/* Line 1455 of yacc.c  */
#line 6563 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(3) - (3)])))) {
		(yyval) = CB_FILE (cb_ref ((yyvsp[(3) - (3)])))->linage_ctr;
	} else {
		cb_error_x ((yyvsp[(3) - (3)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(3) - (3)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1314:

/* Line 1455 of yacc.c  */
#line 6577 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1315:

/* Line 1455 of yacc.c  */
#line 6579 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1316:

/* Line 1455 of yacc.c  */
#line 6583 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)])); ;}
    break;

  case 1317:

/* Line 1455 of yacc.c  */
#line 6589 "parser.y"
    { cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1318:

/* Line 1455 of yacc.c  */
#line 6596 "parser.y"
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

  case 1319:

/* Line 1455 of yacc.c  */
#line 6616 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1320:

/* Line 1455 of yacc.c  */
#line 6620 "parser.y"
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

  case 1321:

/* Line 1455 of yacc.c  */
#line 6636 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (1)])))) {
		(yyval) = (yyvsp[(1) - (1)]);
	} else {
		cb_error_x ((yyvsp[(1) - (1)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(1) - (1)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1322:

/* Line 1455 of yacc.c  */
#line 6649 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1323:

/* Line 1455 of yacc.c  */
#line 6651 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1324:

/* Line 1455 of yacc.c  */
#line 6655 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1325:

/* Line 1455 of yacc.c  */
#line 6661 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1326:

/* Line 1455 of yacc.c  */
#line 6663 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1327:

/* Line 1455 of yacc.c  */
#line 6668 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	CB_REFERENCE ((yyval))->offset = CB_TREE (current_section);
	current_program->label_list = cb_cons ((yyval), current_program->label_list);
  ;}
    break;

  case 1331:

/* Line 1455 of yacc.c  */
#line 6683 "parser.y"
    {
	(yyval) = cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(1) - (1)]))->data));
	(yyval)->source_file = (yyvsp[(1) - (1)])->source_file;
	(yyval)->source_line = (yyvsp[(1) - (1)])->source_line;
  ;}
    break;

  case 1332:

/* Line 1455 of yacc.c  */
#line 6693 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1333:

/* Line 1455 of yacc.c  */
#line 6694 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1334:

/* Line 1455 of yacc.c  */
#line 6699 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	current_program->reference_list = cb_cons ((yyval), current_program->reference_list);
  ;}
    break;

  case 1335:

/* Line 1455 of yacc.c  */
#line 6706 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1336:

/* Line 1455 of yacc.c  */
#line 6707 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1339:

/* Line 1455 of yacc.c  */
#line 6719 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE ((yyval))->word->count > 0) {
		redefinition_error ((yyval));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1340:

/* Line 1455 of yacc.c  */
#line 6738 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1341:

/* Line 1455 of yacc.c  */
#line 6739 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1343:

/* Line 1455 of yacc.c  */
#line 6744 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1344:

/* Line 1455 of yacc.c  */
#line 6748 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1345:

/* Line 1455 of yacc.c  */
#line 6749 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1347:

/* Line 1455 of yacc.c  */
#line 6754 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1348:

/* Line 1455 of yacc.c  */
#line 6755 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1349:

/* Line 1455 of yacc.c  */
#line 6756 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1350:

/* Line 1455 of yacc.c  */
#line 6757 "parser.y"
    { (yyval) = cb_build_ppointer ((yyvsp[(4) - (4)])); ;}
    break;

  case 1351:

/* Line 1455 of yacc.c  */
#line 6758 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1356:

/* Line 1455 of yacc.c  */
#line 6766 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1357:

/* Line 1455 of yacc.c  */
#line 6767 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1358:

/* Line 1455 of yacc.c  */
#line 6768 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1364:

/* Line 1455 of yacc.c  */
#line 6780 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1365:

/* Line 1455 of yacc.c  */
#line 6781 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1377:

/* Line 1455 of yacc.c  */
#line 6815 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1378:

/* Line 1455 of yacc.c  */
#line 6823 "parser.y"
    { (yyval) = cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1379:

/* Line 1455 of yacc.c  */
#line 6827 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1380:

/* Line 1455 of yacc.c  */
#line 6828 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1381:

/* Line 1455 of yacc.c  */
#line 6829 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1382:

/* Line 1455 of yacc.c  */
#line 6830 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 1383:

/* Line 1455 of yacc.c  */
#line 6834 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1384:

/* Line 1455 of yacc.c  */
#line 6835 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); CB_REFERENCE ((yyvsp[(1) - (3)]))->chain = (yyvsp[(3) - (3)]); ;}
    break;

  case 1385:

/* Line 1455 of yacc.c  */
#line 6840 "parser.y"
    {
	if (cb_ref ((yyvsp[(0) - (3)])) != cb_error_node) {
		(yyval) = (yyvsp[(0) - (3)]);
		CB_REFERENCE ((yyvsp[(0) - (3)]))->subs = cb_list_reverse ((yyvsp[(2) - (3)]));
	}
  ;}
    break;

  case 1386:

/* Line 1455 of yacc.c  */
#line 6850 "parser.y"
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

  case 1387:

/* Line 1455 of yacc.c  */
#line 6868 "parser.y"
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

  case 1388:

/* Line 1455 of yacc.c  */
#line 6895 "parser.y"
    {
	if (cb_tree_category ((yyvsp[(1) - (1)])) != CB_CATEGORY_NUMERIC) {
		cb_error (_("Integer value expected"));
	} else if (CB_LITERAL ((yyvsp[(1) - (1)]))->sign < 0 || CB_LITERAL ((yyvsp[(1) - (1)]))->scale) {
		cb_error (_("Integer value expected"));
	}
	(yyval) = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1389:

/* Line 1455 of yacc.c  */
#line 6906 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1390:

/* Line 1455 of yacc.c  */
#line 6908 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (2)]);
	if (CB_LITERAL_P ((yyvsp[(2) - (2)]))) {
		CB_LITERAL ((yyvsp[(2) - (2)]))->all = 1;
	}
  ;}
    break;

  case 1391:

/* Line 1455 of yacc.c  */
#line 6917 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1392:

/* Line 1455 of yacc.c  */
#line 6918 "parser.y"
    { (yyval) = cb_concat_literals ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1393:

/* Line 1455 of yacc.c  */
#line 6922 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1394:

/* Line 1455 of yacc.c  */
#line 6923 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 1395:

/* Line 1455 of yacc.c  */
#line 6924 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1396:

/* Line 1455 of yacc.c  */
#line 6925 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 1397:

/* Line 1455 of yacc.c  */
#line 6926 "parser.y"
    { (yyval) = cb_high; ;}
    break;

  case 1398:

/* Line 1455 of yacc.c  */
#line 6927 "parser.y"
    { (yyval) = cb_low; ;}
    break;

  case 1399:

/* Line 1455 of yacc.c  */
#line 6928 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1400:

/* Line 1455 of yacc.c  */
#line 6937 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1401:

/* Line 1455 of yacc.c  */
#line 6941 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1402:

/* Line 1455 of yacc.c  */
#line 6945 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1403:

/* Line 1455 of yacc.c  */
#line 6949 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1404:

/* Line 1455 of yacc.c  */
#line 6953 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1405:

/* Line 1455 of yacc.c  */
#line 6957 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1406:

/* Line 1455 of yacc.c  */
#line 6961 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1407:

/* Line 1455 of yacc.c  */
#line 6965 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1408:

/* Line 1455 of yacc.c  */
#line 6969 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1409:

/* Line 1455 of yacc.c  */
#line 6973 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), NULL);
  ;}
    break;

  case 1410:

/* Line 1455 of yacc.c  */
#line 6977 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1411:

/* Line 1455 of yacc.c  */
#line 6981 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), NULL);
  ;}
    break;

  case 1412:

/* Line 1455 of yacc.c  */
#line 6987 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1413:

/* Line 1455 of yacc.c  */
#line 6988 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (4)]), NULL); ;}
    break;

  case 1414:

/* Line 1455 of yacc.c  */
#line 6989 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 1415:

/* Line 1455 of yacc.c  */
#line 6993 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1416:

/* Line 1455 of yacc.c  */
#line 6994 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1417:

/* Line 1455 of yacc.c  */
#line 6998 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1418:

/* Line 1455 of yacc.c  */
#line 6999 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1419:

/* Line 1455 of yacc.c  */
#line 7005 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_int0);
  ;}
    break;

  case 1420:

/* Line 1455 of yacc.c  */
#line 7012 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int1);
  ;}
    break;

  case 1421:

/* Line 1455 of yacc.c  */
#line 7019 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int2);
  ;}
    break;

  case 1422:

/* Line 1455 of yacc.c  */
#line 7029 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1423:

/* Line 1455 of yacc.c  */
#line 7036 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1424:

/* Line 1455 of yacc.c  */
#line 7046 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1425:

/* Line 1455 of yacc.c  */
#line 7053 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_ref ((yyvsp[(3) - (3)])));
  ;}
    break;

  case 1426:

/* Line 1455 of yacc.c  */
#line 7066 "parser.y"
    {
	non_const_word = 1;
  ;}
    break;

  case 1427:

/* Line 1455 of yacc.c  */
#line 7076 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1428:

/* Line 1455 of yacc.c  */
#line 7077 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1429:

/* Line 1455 of yacc.c  */
#line 7081 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1430:

/* Line 1455 of yacc.c  */
#line 7082 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1431:

/* Line 1455 of yacc.c  */
#line 7086 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1432:

/* Line 1455 of yacc.c  */
#line 7087 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1433:

/* Line 1455 of yacc.c  */
#line 7091 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1434:

/* Line 1455 of yacc.c  */
#line 7092 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1435:

/* Line 1455 of yacc.c  */
#line 7093 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 1436:

/* Line 1455 of yacc.c  */
#line 7097 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1437:

/* Line 1455 of yacc.c  */
#line 7098 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1438:

/* Line 1455 of yacc.c  */
#line 7102 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1439:

/* Line 1455 of yacc.c  */
#line 7103 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1440:

/* Line 1455 of yacc.c  */
#line 7107 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1441:

/* Line 1455 of yacc.c  */
#line 7108 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1442:

/* Line 1455 of yacc.c  */
#line 7112 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1443:

/* Line 1455 of yacc.c  */
#line 7113 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1455:

/* Line 1455 of yacc.c  */
#line 7126 "parser.y"
    { (yyval) = cb_int1; ;}
    break;



/* Line 1455 of yacc.c  */
#line 14256 "parser.c"
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
#line 7170 "parser.y"


