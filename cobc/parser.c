
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
#define YYLAST   5518

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  453
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  694
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1543
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2274

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
     618,   620,   624,   626,   629,   634,   639,   644,   651,   656,
     660,   664,   667,   670,   673,   674,   678,   679,   682,   684,
     687,   689,   691,   697,   698,   700,   702,   704,   710,   712,
     715,   718,   719,   722,   723,   733,   734,   735,   741,   742,
     746,   747,   750,   754,   757,   760,   762,   764,   765,   770,
     771,   774,   777,   780,   782,   784,   786,   788,   790,   792,
     794,   796,   798,   804,   805,   807,   809,   814,   821,   831,
     832,   836,   837,   840,   841,   844,   848,   850,   852,   858,
     864,   866,   868,   872,   878,   879,   882,   884,   886,   888,
     894,   899,   903,   908,   912,   916,   920,   921,   922,   928,
     929,   931,   932,   935,   939,   944,   947,   949,   950,   955,
     957,   958,   960,   962,   964,   965,   968,   970,   974,   978,
     985,   986,   989,   991,   993,   995,   997,   999,  1001,  1003,
    1005,  1007,  1009,  1011,  1013,  1015,  1017,  1020,  1024,  1025,
    1028,  1031,  1033,  1035,  1039,  1041,  1043,  1045,  1047,  1049,
    1051,  1053,  1055,  1057,  1059,  1061,  1063,  1065,  1067,  1069,
    1071,  1073,  1075,  1077,  1080,  1083,  1085,  1088,  1091,  1093,
    1096,  1099,  1101,  1104,  1107,  1109,  1112,  1115,  1117,  1119,
    1123,  1127,  1135,  1136,  1139,  1140,  1144,  1146,  1147,  1153,
    1155,  1157,  1158,  1162,  1164,  1167,  1169,  1172,  1175,  1176,
    1178,  1180,  1184,  1186,  1187,  1196,  1198,  1201,  1203,  1207,
    1208,  1212,  1215,  1220,  1223,  1224,  1225,  1231,  1232,  1233,
    1239,  1240,  1241,  1247,  1248,  1250,  1252,  1255,  1261,  1262,
    1265,  1268,  1272,  1274,  1276,  1279,  1282,  1285,  1286,  1288,
    1290,  1293,  1302,  1303,  1307,  1308,  1313,  1314,  1319,  1320,
    1324,  1325,  1329,  1331,  1336,  1339,  1341,  1343,  1344,  1347,
    1352,  1353,  1356,  1358,  1360,  1362,  1364,  1366,  1368,  1370,
    1372,  1374,  1376,  1378,  1380,  1382,  1384,  1386,  1388,  1392,
    1394,  1396,  1398,  1400,  1402,  1404,  1406,  1411,  1416,  1419,
    1421,  1423,  1426,  1430,  1432,  1436,  1443,  1446,  1450,  1453,
    1455,  1458,  1461,  1463,  1466,  1467,  1469,  1471,  1476,  1479,
    1480,  1482,  1484,  1485,  1486,  1487,  1494,  1495,  1497,  1499,
    1502,  1504,  1505,  1511,  1512,  1515,  1517,  1519,  1521,  1523,
    1526,  1529,  1531,  1533,  1535,  1537,  1539,  1541,  1543,  1545,
    1547,  1549,  1555,  1561,  1565,  1569,  1571,  1573,  1575,  1577,
    1579,  1581,  1583,  1586,  1589,  1592,  1593,  1595,  1597,  1599,
    1601,  1602,  1604,  1606,  1608,  1610,  1614,  1615,  1616,  1617,
    1627,  1628,  1629,  1633,  1634,  1638,  1640,  1643,  1648,  1649,
    1652,  1655,  1656,  1660,  1664,  1669,  1673,  1674,  1676,  1677,
    1680,  1681,  1682,  1690,  1691,  1694,  1696,  1698,  1700,  1703,
    1706,  1711,  1714,  1716,  1718,  1719,  1721,  1722,  1723,  1727,
    1728,  1731,  1733,  1735,  1737,  1739,  1741,  1743,  1745,  1747,
    1749,  1751,  1753,  1755,  1757,  1759,  1761,  1763,  1765,  1767,
    1769,  1771,  1773,  1775,  1777,  1779,  1781,  1783,  1785,  1787,
    1789,  1791,  1793,  1795,  1797,  1799,  1801,  1803,  1805,  1807,
    1809,  1811,  1813,  1815,  1817,  1819,  1821,  1823,  1825,  1827,
    1829,  1831,  1832,  1837,  1842,  1847,  1851,  1855,  1859,  1864,
    1868,  1873,  1877,  1881,  1885,  1890,  1896,  1900,  1905,  1909,
    1913,  1914,  1918,  1922,  1925,  1928,  1931,  1935,  1939,  1943,
    1944,  1947,  1949,  1952,  1954,  1956,  1958,  1960,  1962,  1964,
    1966,  1970,  1974,  1978,  1982,  1984,  1986,  1988,  1990,  1992,
    1994,  1995,  1997,  1998,  2003,  2008,  2014,  2021,  2022,  2025,
    2026,  2028,  2029,  2033,  2037,  2043,  2044,  2047,  2050,  2051,
    2057,  2058,  2061,  2062,  2071,  2072,  2073,  2077,  2079,  2082,
    2085,  2089,  2090,  2093,  2096,  2099,  2100,  2103,  2106,  2107,
    2108,  2112,  2113,  2114,  2118,  2119,  2121,  2122,  2126,  2127,
    2130,  2131,  2135,  2136,  2140,  2141,  2143,  2147,  2151,  2154,
    2156,  2158,  2159,  2164,  2169,  2170,  2172,  2174,  2176,  2178,
    2180,  2181,  2188,  2189,  2191,  2192,  2197,  2198,  2203,  2207,
    2211,  2215,  2219,  2224,  2231,  2238,  2245,  2252,  2253,  2256,
    2259,  2261,  2264,  2266,  2268,  2271,  2274,  2276,  2278,  2280,
    2282,  2284,  2288,  2292,  2296,  2300,  2302,  2304,  2305,  2307,
    2308,  2313,  2318,  2325,  2332,  2341,  2350,  2351,  2353,  2354,
    2359,  2360,  2366,  2368,  2372,  2374,  2376,  2378,  2381,  2383,
    2386,  2387,  2391,  2392,  2393,  2397,  2400,  2404,  2406,  2410,
    2413,  2415,  2417,  2419,  2420,  2423,  2424,  2426,  2427,  2431,
    2432,  2434,  2436,  2439,  2441,  2443,  2444,  2448,  2449,  2453,
    2454,  2460,  2461,  2465,  2466,  2469,  2470,  2471,  2480,  2484,
    2485,  2486,  2490,  2491,  2493,  2494,  2502,  2503,  2506,  2507,
    2511,  2515,  2516,  2519,  2521,  2524,  2529,  2531,  2533,  2535,
    2537,  2539,  2541,  2543,  2544,  2546,  2547,  2551,  2552,  2557,
    2559,  2561,  2563,  2565,  2568,  2570,  2572,  2574,  2575,  2579,
    2581,  2584,  2587,  2590,  2592,  2594,  2596,  2599,  2602,  2604,
    2607,  2612,  2615,  2616,  2618,  2620,  2622,  2624,  2629,  2635,
    2636,  2641,  2642,  2644,  2645,  2649,  2650,  2654,  2658,  2663,
    2664,  2669,  2674,  2681,  2682,  2684,  2685,  2689,  2690,  2696,
    2698,  2700,  2702,  2704,  2705,  2709,  2710,  2714,  2717,  2718,
    2722,  2725,  2726,  2731,  2734,  2735,  2737,  2739,  2743,  2744,
    2746,  2749,  2753,  2757,  2758,  2762,  2764,  2768,  2776,  2777,
    2788,  2789,  2792,  2793,  2796,  2799,  2803,  2807,  2810,  2811,
    2815,  2816,  2818,  2820,  2821,  2823,  2824,  2829,  2830,  2838,
    2839,  2841,  2842,  2850,  2851,  2854,  2858,  2859,  2861,  2863,
    2864,  2869,  2874,  2875,  2883,  2884,  2887,  2888,  2889,  2894,
    2896,  2899,  2900,  2905,  2906,  2908,  2909,  2913,  2915,  2917,
    2919,  2921,  2923,  2928,  2933,  2937,  2942,  2944,  2946,  2948,
    2951,  2955,  2957,  2960,  2964,  2968,  2969,  2973,  2974,  2982,
    2983,  2989,  2990,  2993,  2994,  2997,  2998,  3002,  3003,  3006,
    3011,  3012,  3015,  3020,  3021,  3022,  3030,  3031,  3036,  3039,
    3042,  3045,  3048,  3051,  3052,  3054,  3055,  3060,  3063,  3064,
    3067,  3070,  3071,  3080,  3082,  3085,  3087,  3091,  3095,  3096,
    3100,  3101,  3103,  3104,  3109,  3114,  3121,  3128,  3129,  3131,
    3134,  3135,  3137,  3138,  3142,  3143,  3151,  3152,  3157,  3158,
    3160,  3162,  3163,  3173,  3174,  3178,  3180,  3184,  3187,  3190,
    3193,  3197,  3198,  3202,  3203,  3207,  3208,  3212,  3213,  3215,
    3217,  3219,  3221,  3230,  3231,  3233,  3235,  3237,  3239,  3241,
    3243,  3244,  3246,  3247,  3249,  3251,  3253,  3255,  3257,  3259,
    3261,  3262,  3264,  3270,  3272,  3275,  3281,  3282,  3291,  3292,
    3295,  3296,  3301,  3305,  3309,  3311,  3313,  3314,  3316,  3318,
    3319,  3321,  3324,  3327,  3328,  3329,  3333,  3334,  3335,  3339,
    3342,  3343,  3344,  3348,  3349,  3350,  3354,  3357,  3358,  3359,
    3363,  3364,  3365,  3369,  3371,  3373,  3376,  3377,  3381,  3382,
    3386,  3388,  3390,  3393,  3394,  3398,  3399,  3403,  3404,  3406,
    3408,  3410,  3413,  3414,  3418,  3419,  3423,  3424,  3428,  3430,
    3432,  3433,  3436,  3439,  3442,  3445,  3448,  3451,  3454,  3457,
    3460,  3463,  3466,  3469,  3472,  3475,  3476,  3479,  3482,  3485,
    3488,  3491,  3494,  3497,  3500,  3503,  3506,  3509,  3512,  3515,
    3518,  3521,  3524,  3527,  3530,  3533,  3536,  3539,  3542,  3545,
    3548,  3551,  3553,  3556,  3558,  3560,  3563,  3565,  3568,  3570,
    3576,  3578,  3584,  3586,  3590,  3591,  3593,  3595,  3597,  3601,
    3605,  3609,  3613,  3616,  3619,  3623,  3627,  3629,  3633,  3635,
    3638,  3641,  3643,  3645,  3647,  3650,  3652,  3654,  3657,  3659,
    3660,  3663,  3665,  3667,  3669,  3673,  3675,  3677,  3680,  3682,
    3683,  3685,  3687,  3689,  3691,  3693,  3696,  3698,  3702,  3704,
    3707,  3709,  3713,  3717,  3721,  3726,  3730,  3732,  3734,  3736,
    3738,  3742,  3746,  3750,  3752,  3754,  3756,  3758,  3760,  3762,
    3764,  3766,  3768,  3770,  3772,  3774,  3776,  3778,  3780,  3782,
    3784,  3786,  3788,  3790,  3792,  3795,  3798,  3802,  3804,  3808,
    3812,  3817,  3823,  3825,  3827,  3830,  3832,  3836,  3838,  3840,
    3842,  3844,  3846,  3848,  3850,  3853,  3856,  3862,  3868,  3874,
    3880,  3886,  3892,  3898,  3903,  3909,  3912,  3913,  3918,  3924,
    3925,  3929,  3930,  3932,  3934,  3938,  3942,  3944,  3948,  3950,
    3954,  3955,  3956,  3958,  3959,  3961,  3962,  3964,  3965,  3967,
    3969,  3970,  3972,  3973,  3975,  3976,  3978,  3979,  3982,  3984,
    3986,  3989,  3992,  3995,  3997,  4000,  4002,  4003,  4005,  4006,
    4008,  4009,  4011,  4012,  4014,  4015,  4017,  4018,  4020,  4021,
    4023,  4024,  4026,  4027,  4029,  4030,  4032,  4033,  4035,  4036,
    4038,  4039,  4041,  4042,  4044,  4045,  4047,  4048,  4050,  4051,
    4053,  4054,  4056,  4058,  4059,  4061,  4062,  4064,  4066,  4067,
    4069,  4070,  4072,  4073,  4075,  4076,  4078,  4079,  4081,  4082,
    4084,  4087,  4088,  4090,  4091,  4093,  4094,  4096,  4097,  4099,
    4100,  4102,  4103,  4105,  4106,  4108,  4111,  4112,  4114,  4115,
    4117,  4118,  4120,  4121,  4123,  4124,  4126,  4127,  4129,  4130,
    4132,  4133,  4135,  4136
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
      -1,  1121,   477,  1132,    -1,    70,    -1,    70,   478,    -1,
     478,    -1,   397,    -1,   313,    -1,    -1,   145,   115,   445,
     480,   531,    -1,    -1,    80,   347,   445,   481,    -1,    -1,
     481,   482,    -1,   483,    -1,   487,    -1,   500,    -1,   495,
      -1,   368,   445,   484,    -1,    -1,   486,   445,    -1,   486,
     485,   445,    -1,   485,   445,    -1,  1146,   102,   241,    -1,
     432,    -1,   266,   445,   488,    -1,    -1,   486,   445,    -1,
     486,   489,   445,    -1,   489,   445,    -1,   490,    -1,   489,
     490,    -1,   491,    -1,   493,    -1,   494,    -1,   237,   363,
    1121,  1081,   492,    -1,    55,    -1,   433,    -1,  1132,  1104,
    1121,  1060,    -1,   349,  1121,  1081,    -1,   328,   445,   496,
      -1,    -1,   497,   445,    -1,   498,    -1,   497,   498,    -1,
     176,   499,   205,    -1,   176,     9,   205,    -1,   228,    -1,
     499,   228,    -1,   370,   445,   501,    -1,    -1,   502,   445,
      -1,   503,    -1,   502,   503,    -1,   504,    -1,   508,    -1,
     517,    -1,   524,    -1,   521,    -1,   525,    -1,   526,    -1,
     527,    -1,   528,    -1,   529,    -1,   530,    -1,   432,  1121,
      92,    -1,    -1,   432,  1121,  1063,   505,   506,    -1,    24,
    1121,  1063,    -1,    25,  1121,  1063,    -1,   146,  1121,  1063,
      -1,   147,  1121,  1063,    -1,    -1,   506,   507,  1139,  1121,
    1063,    -1,   271,    -1,   269,    -1,    -1,    11,  1063,   509,
    1121,   510,    -1,   247,    -1,   372,    -1,   373,    -1,   119,
      -1,   511,    -1,   512,    -1,   511,   512,    -1,   515,    -1,
     515,   391,   515,    -1,    -1,   515,    17,   513,   514,    -1,
     516,    -1,   514,    17,   516,    -1,   228,    -1,   369,    -1,
     438,    -1,   306,    -1,   189,    -1,   235,    -1,   228,    -1,
     369,    -1,   438,    -1,   306,    -1,   189,    -1,   235,    -1,
     383,  1114,   518,    -1,   519,  1122,   520,    -1,  1063,    -1,
     519,  1063,    -1,  1081,    -1,   520,  1081,    -1,    56,  1063,
    1121,   522,    -1,   523,    -1,   522,   523,    -1,  1084,    -1,
    1084,   391,  1084,    -1,   229,  1063,  1121,  1060,    -1,    93,
    1136,  1121,   228,    -1,   103,  1121,    66,    -1,    95,  1121,
    1060,    -1,    92,   375,  1121,  1060,    -1,   343,  1121,  1060,
      -1,   157,  1121,  1060,    -1,    -1,   202,   347,   445,   534,
     567,    -1,    -1,   164,   445,   532,   535,    -1,    -1,   210,
     445,   533,   568,    -1,    -1,   164,   445,   535,    -1,    -1,
     535,   536,    -1,    -1,   350,  1098,  1063,   537,   538,   445,
      -1,    -1,   538,   539,    -1,   540,    -1,   544,    -1,   546,
      -1,   551,    -1,   552,    -1,   554,    -1,   558,    -1,   560,
      -1,   561,    -1,   562,    -1,   563,    -1,   564,    -1,   565,
      -1,    28,  1144,   542,   541,   543,    -1,    28,  1144,   542,
     112,    -1,    28,  1144,   542,   296,    -1,    -1,   112,    -1,
     296,    -1,    -1,   162,    -1,   118,    -1,   228,    -1,   113,
      -1,  1078,    -1,     4,  1126,  1121,   545,    -1,   355,    -1,
     118,    -1,   307,    -1,    19,   310,  1123,  1121,  1060,  1094,
      -1,    19,   310,  1123,  1121,  1060,   550,   547,  1094,    -1,
      -1,   548,   549,    -1,   547,   549,    -1,  1060,    -1,    -1,
     367,  1121,    -1,   446,    -1,  1104,  1121,   432,    -1,   553,
     375,  1121,  1060,  1061,    -1,    -1,   396,    -1,   365,    -1,
     232,  1126,  1121,   555,    -1,   236,   556,    -1,    31,   556,
      -1,   159,    -1,    -1,   431,   232,   271,   557,    -1,   431,
     232,   271,   243,   557,    -1,   431,   338,    -1,   310,    -1,
     312,    -1,   277,  1121,   559,    -1,   559,    -1,   196,    -1,
    1133,  1111,   355,    -1,   317,    -1,   225,   355,    -1,   283,
    1113,  1121,  1062,    -1,   310,   108,  1121,   372,    -1,   310,
    1123,  1121,  1060,    -1,   310,  1123,  1121,  1060,   550,   547,
      -1,   317,  1123,  1121,  1060,    -1,   330,  1081,  1108,    -1,
     357,  1146,   566,    -1,     9,  1131,    -1,   252,  1131,    -1,
     309,   272,    -1,    -1,   210,   445,   568,    -1,    -1,   569,
     445,    -1,   570,    -1,   569,   570,    -1,   571,    -1,   573,
      -1,   341,   572,  1108,  1118,  1051,    -1,    -1,   310,    -1,
     365,    -1,   366,    -1,   243,  1117,  1140,  1115,   574,    -1,
     575,    -1,   574,   575,    -1,  1052,   576,    -1,    -1,   292,
    1081,    -1,    -1,    97,   115,   445,   578,   609,   654,   656,
     658,   699,    -1,    -1,    -1,   396,   347,   445,   579,   581,
      -1,    -1,   584,   580,   583,    -1,    -1,   581,   582,    -1,
     584,   585,   611,    -1,   585,   611,    -1,   583,   582,    -1,
     163,    -1,   345,    -1,    -1,  1052,   586,   587,   445,    -1,
      -1,   587,   588,    -1,  1121,   162,    -1,  1121,   182,    -1,
     589,    -1,   591,    -1,   595,    -1,   597,    -1,   599,    -1,
     600,    -1,   606,    -1,   607,    -1,   608,    -1,    46,  1115,
    1081,   594,   590,    -1,    -1,   312,    -1,    55,    -1,   310,
    1115,  1081,  1114,    -1,   310,  1115,  1081,   394,  1081,  1114,
      -1,   310,  1121,   426,  1120,  1138,   593,   594,  1114,   592,
      -1,    -1,   109,  1129,  1060,    -1,    -1,  1119,  1081,    -1,
      -1,   394,  1081,    -1,   213,  1102,   596,    -1,   371,    -1,
     270,    -1,   425,   268,   432,  1121,   598,    -1,   425,   268,
     165,  1121,   598,    -1,   228,    -1,  1078,    -1,    97,  1102,
    1059,    -1,   223,  1121,  1062,  1125,   601,    -1,    -1,   601,
     602,    -1,   603,    -1,   604,    -1,   605,    -1,  1146,   169,
    1110,  1062,  1125,    -1,  1110,   400,  1062,  1125,    -1,  1110,
      47,  1062,    -1,   311,  1126,  1121,   432,    -1,    60,  1121,
     432,    -1,   323,  1121,   698,    -1,   325,  1107,   698,    -1,
      -1,    -1,   434,   347,   445,   610,   611,    -1,    -1,   612,
      -1,    -1,   613,   614,    -1,  1092,   615,   445,    -1,   614,
    1092,   615,   445,    -1,   614,   445,    -1,   622,    -1,    -1,
     617,   618,   616,   623,    -1,   432,    -1,    -1,   166,    -1,
     432,    -1,   432,    -1,    -1,  1121,   182,    -1,  1082,    -1,
     219,  1128,  1077,    -1,    49,  1128,  1077,    -1,   617,   619,
      81,   620,  1109,   621,    -1,    -1,   623,   624,    -1,   625,
      -1,   626,    -1,   628,    -1,   629,    -1,   630,    -1,   632,
      -1,   633,    -1,   642,    -1,   643,    -1,   645,    -1,   646,
      -1,   647,    -1,   652,    -1,   653,    -1,   314,  1077,    -1,
    1121,   162,   627,    -1,    -1,    26,   228,    -1,  1121,   182,
      -1,   289,    -1,   631,    -1,   422,  1121,   631,    -1,    36,
      -1,    71,    -1,    73,    -1,    74,    -1,    75,    -1,    76,
      -1,    77,    -1,    78,    -1,   113,    -1,   195,    -1,   282,
      -1,   291,    -1,   304,    -1,   362,    -1,   360,    -1,   361,
      -1,   411,    -1,   409,    -1,   410,    -1,    38,   359,    -1,
      38,   408,    -1,    38,    -1,    41,   359,    -1,    41,   408,
      -1,    41,    -1,    40,   359,    -1,    40,   408,    -1,    40,
      -1,    39,   359,    -1,    39,   408,    -1,    39,    -1,    37,
     359,    -1,    37,   408,    -1,    37,    -1,   245,    -1,  1137,
     217,  1100,    -1,  1137,   401,  1100,    -1,   267,  1081,   634,
    1143,   635,   636,   639,    -1,    -1,   394,  1081,    -1,    -1,
     109,  1129,  1060,    -1,   637,    -1,    -1,   637,   638,  1123,
    1121,  1059,    -1,    27,    -1,   110,    -1,    -1,   196,  1112,
     640,    -1,   641,    -1,   640,   641,    -1,   432,    -1,   211,
    1134,    -1,   384,   644,    -1,    -1,   218,    -1,   337,    -1,
      42,  1145,   438,    -1,    33,    -1,    -1,   425,  1122,   649,
     648,  1145,  1135,  1144,   651,    -1,   650,    -1,   649,   650,
      -1,  1082,    -1,  1082,   391,  1082,    -1,    -1,   395,  1121,
    1082,    -1,   321,  1078,    -1,   321,  1078,   391,  1078,    -1,
      21,   219,    -1,    -1,    -1,   231,   347,   445,   655,   611,
      -1,    -1,    -1,   227,   347,   445,   657,   611,    -1,    -1,
      -1,   323,   347,   445,   659,   660,    -1,    -1,   661,    -1,
     662,    -1,   661,   662,    -1,   308,   698,   663,   445,   677,
      -1,    -1,   663,   664,    -1,  1121,   182,    -1,    59,  1121,
    1073,    -1,   665,    -1,   669,    -1,    85,   666,    -1,    86,
     666,    -1,   667,   668,    -1,    -1,   167,    -1,  1076,    -1,
     668,  1076,    -1,   284,  1122,   675,   670,   671,   672,   673,
     674,    -1,    -1,   187,  1121,  1081,    -1,    -1,   168,   111,
    1121,  1081,    -1,    -1,   214,    88,  1121,  1081,    -1,    -1,
     215,  1121,  1081,    -1,    -1,   169,  1121,  1081,    -1,  1081,
      -1,  1081,   676,  1081,    65,    -1,  1081,   676,    -1,   225,
      -1,   226,    -1,    -1,   677,   678,    -1,   617,   618,   679,
     445,    -1,    -1,   679,   680,    -1,   681,    -1,   683,    -1,
     690,    -1,   629,    -1,   630,    -1,   632,    -1,   642,    -1,
     684,    -1,   645,    -1,   695,    -1,   685,    -1,   647,    -1,
     688,    -1,   696,    -1,   633,    -1,   689,    -1,   404,  1121,
     682,    -1,   327,    -1,   286,    -1,    88,    -1,   111,    -1,
      87,    -1,   285,    -1,   326,    -1,   250,   186,  1121,  1081,
      -1,    64,  1127,  1121,  1081,    -1,    64,   262,    -1,    65,
      -1,   686,    -1,   685,   686,    -1,   381,  1128,   687,    -1,
    1060,    -1,   294,   428,  1032,    -1,   426,  1076,   174,  1067,
      48,  1067,    -1,   691,   692,    -1,   225,   694,  1122,    -1,
     226,  1107,    -1,   693,    -1,   692,   693,    -1,   290,  1081,
      -1,  1081,    -1,   250,   284,    -1,    -1,   261,    -1,   262,
      -1,   367,  1121,  1076,  1099,    -1,   186,   697,    -1,    -1,
     197,    -1,   432,    -1,    -1,    -1,    -1,   342,   347,   445,
     700,   701,   702,    -1,    -1,   703,    -1,   704,    -1,   703,
     704,    -1,   622,    -1,    -1,   617,   618,   705,   706,   445,
      -1,    -1,   706,   707,    -1,    43,    -1,    44,    -1,    35,
      -1,    45,    -1,   153,   148,    -1,   153,   150,    -1,   188,
      -1,   234,    -1,   334,    -1,   405,    -1,   281,    -1,    30,
      -1,   348,    -1,   329,    -1,   175,    -1,   305,    -1,   225,
    1127,  1121,   708,  1075,    -1,    64,  1127,  1121,   709,  1075,
      -1,   171,  1121,  1075,    -1,    32,  1121,  1075,    -1,   630,
      -1,   645,    -1,   642,    -1,   632,    -1,   647,    -1,   629,
      -1,   710,    -1,   424,  1076,    -1,   174,  1074,    -1,   394,
    1076,    -1,    -1,   290,    -1,   439,    -1,   239,    -1,   440,
      -1,    -1,   290,    -1,   439,    -1,   239,    -1,   440,    -1,
     267,  1081,  1143,    -1,    -1,    -1,    -1,   298,   115,   714,
     722,   445,   712,   723,   713,   725,    -1,    -1,    -1,   424,
     715,   717,    -1,    -1,    53,   716,   717,    -1,   718,    -1,
     717,   718,    -1,   719,   720,   721,   432,    -1,    -1,  1112,
     316,    -1,  1112,   425,    -1,    -1,   363,  1121,    30,    -1,
     363,  1121,   105,    -1,   408,   363,  1121,  1081,    -1,   363,
    1121,  1081,    -1,    -1,   274,    -1,    -1,   332,   432,    -1,
      -1,    -1,   104,   445,   724,   725,   121,   104,   445,    -1,
      -1,   725,   726,    -1,   727,    -1,   728,    -1,   729,    -1,
     735,   445,    -1,     1,   445,    -1,   730,   347,   731,   445,
      -1,   432,   445,    -1,   730,    -1,   432,    -1,    -1,   228,
      -1,    -1,    -1,   733,   734,   735,    -1,    -1,   735,   736,
      -1,   737,    -1,   747,    -1,   752,    -1,   756,    -1,   759,
      -1,   772,    -1,   775,    -1,   785,    -1,   780,    -1,   786,
      -1,   787,    -1,   790,    -1,   792,    -1,   799,    -1,   803,
      -1,   805,    -1,   820,    -1,   823,    -1,   825,    -1,   827,
      -1,   830,    -1,   832,    -1,   838,    -1,   847,    -1,   849,
      -1,   866,    -1,   868,    -1,   871,    -1,   875,    -1,   881,
      -1,   891,    -1,   898,    -1,   900,    -1,   903,    -1,   907,
      -1,   908,    -1,   919,    -1,   930,    -1,   940,    -1,   946,
      -1,   949,    -1,   955,    -1,   959,    -1,   961,    -1,   963,
      -1,   965,    -1,   968,    -1,   979,    -1,   992,    -1,   251,
      -1,    -1,     3,   738,   739,   746,    -1,  1076,   740,   743,
     999,    -1,  1076,   174,   155,   212,    -1,  1076,   174,   226,
      -1,  1076,   174,    65,    -1,  1076,   174,    98,    -1,  1076,
     174,    98,   437,    -1,  1076,   174,    99,    -1,  1076,   174,
      99,   436,    -1,  1076,   174,   100,    -1,  1076,   174,   392,
      -1,  1076,   174,    67,    -1,  1076,   174,   147,   999,    -1,
    1076,   174,   145,  1071,   999,    -1,  1076,   174,    24,    -1,
    1076,   174,    25,   999,    -1,  1076,   174,  1054,    -1,  1076,
     174,   432,    -1,    -1,  1110,   741,   742,    -1,  1110,   742,
     741,    -1,  1110,   741,    -1,  1110,   742,    -1,    29,  1071,
      -1,   225,  1127,  1073,    -1,    64,  1127,  1073,    -1,   292,
    1127,  1073,    -1,    -1,   431,   744,    -1,   745,    -1,   744,
     745,    -1,    35,    -1,    45,    -1,   188,    -1,   234,    -1,
     334,    -1,   405,    -1,   281,    -1,   171,  1121,  1075,    -1,
      32,  1121,  1075,    -1,   344,   414,  1031,    -1,   344,   116,
    1031,    -1,    30,    -1,   175,    -1,   329,    -1,   348,    -1,
     415,    -1,   305,    -1,    -1,   122,    -1,    -1,     5,   748,
     749,   751,    -1,  1066,   394,  1047,  1005,    -1,  1066,   750,
     181,  1047,  1005,    -1,    90,  1076,   394,  1076,  1099,  1005,
      -1,    -1,   394,  1067,    -1,    -1,   123,    -1,    -1,    10,
     753,   754,    -1,   432,  1095,   755,    -1,  1033,    55,  1095,
     332,  1065,    -1,    -1,   332,  1065,    -1,    18,   757,    -1,
      -1,   757,  1056,   394,   758,  1056,    -1,    -1,   300,   394,
      -1,    -1,    50,   760,  1074,   761,   766,   767,   769,   771,
      -1,    -1,    -1,   424,   762,   763,    -1,   764,    -1,   763,
     764,    -1,   765,   270,    -1,   765,   720,  1067,    -1,    -1,
    1112,   316,    -1,  1112,    83,    -1,  1112,   425,    -1,    -1,
     332,  1076,    -1,   181,  1076,    -1,    -1,    -1,   986,   768,
     732,    -1,    -1,    -1,   987,   770,   732,    -1,    -1,   124,
      -1,    -1,    51,   773,   774,    -1,    -1,   774,  1073,    -1,
      -1,    58,   776,   777,    -1,    -1,   777,  1052,   778,    -1,
      -1,   779,    -1,   779,  1118,   320,    -1,  1146,   252,   335,
      -1,  1146,   232,    -1,   315,    -1,   406,    -1,    -1,    72,
     781,   782,   783,    -1,  1047,   784,  1033,  1005,    -1,    -1,
     125,    -1,   446,    -1,   151,    -1,    69,    -1,    84,    -1,
      -1,   106,   788,  1052,  1133,  1025,   789,    -1,    -1,   126,
      -1,    -1,   106,   791,   396,  1051,    -1,    -1,   113,   793,
     794,   798,    -1,  1073,   419,  1000,    -1,  1073,   420,  1000,
      -1,  1073,   417,  1000,    -1,  1073,   418,  1000,    -1,  1066,
     740,   795,  1000,    -1,  1066,   740,   416,  1054,   795,  1000,
      -1,  1066,   740,   416,   432,   795,  1000,    -1,  1066,   740,
     416,   296,   795,  1000,    -1,  1066,   740,   416,    92,   795,
    1000,    -1,    -1,  1146,   260,    -1,   431,   796,    -1,   797,
      -1,   796,   797,    -1,    35,    -1,    45,    -1,   153,   148,
      -1,   153,   150,    -1,   188,    -1,   234,    -1,   334,    -1,
     405,    -1,   281,    -1,   171,  1121,  1075,    -1,    32,  1121,
    1075,    -1,   344,   414,  1031,    -1,   344,   116,  1031,    -1,
      43,    -1,    44,    -1,    -1,   127,    -1,    -1,   114,   800,
     801,   802,    -1,  1067,   204,  1047,  1005,    -1,  1067,   204,
    1067,   181,  1047,  1005,    -1,  1067,    48,  1067,   181,  1047,
    1005,    -1,  1067,   204,  1067,   181,  1048,   319,  1048,  1005,
      -1,  1067,    48,  1067,   181,  1048,   319,  1048,  1005,    -1,
      -1,   128,    -1,    -1,   144,   804,   228,   761,    -1,    -1,
     156,   806,   807,   809,   819,    -1,   808,    -1,   807,  1106,
     808,    -1,  1033,    -1,   399,    -1,   395,    -1,   810,   813,
      -1,   811,    -1,   810,   811,    -1,    -1,   815,   812,   732,
      -1,    -1,    -1,   430,   814,   732,    -1,   428,   816,    -1,
     815,   428,   816,    -1,   817,    -1,   816,  1106,   817,    -1,
    1034,   818,    -1,    21,    -1,   399,    -1,   395,    -1,    -1,
     391,  1033,    -1,    -1,   129,    -1,    -1,   160,   821,   822,
      -1,    -1,   301,    -1,   288,    -1,   288,    96,    -1,   347,
      -1,   287,    -1,    -1,   173,   824,  1064,    -1,    -1,   180,
     826,  1076,    -1,    -1,   183,  1144,   828,  1055,   829,    -1,
      -1,   109,  1129,  1076,    -1,    -1,   184,   831,    -1,    -1,
      -1,   191,   833,  1032,  1142,   834,   732,   835,   837,    -1,
     191,     1,   131,    -1,    -1,    -1,   120,   836,   732,    -1,
      -1,   131,    -1,    -1,   198,   839,  1064,   840,   841,   842,
     846,    -1,    -1,  1146,   166,    -1,    -1,     9,  1144,   425,
      -1,   845,  1144,   425,    -1,    -1,   322,   843,    -1,   844,
      -1,   843,   844,    -1,   845,  1116,    48,  1067,    -1,    12,
      -1,    15,    -1,   263,    -1,    16,    -1,   264,    -1,   245,
      -1,   246,    -1,    -1,   105,    -1,    -1,   200,   848,   668,
      -1,    -1,   203,   850,   851,   852,    -1,  1076,    -1,  1082,
      -1,  1085,    -1,   853,    -1,   852,   853,    -1,   854,    -1,
     858,    -1,   863,    -1,    -1,   385,   855,   856,    -1,   857,
      -1,   856,   857,    -1,  1071,   170,    -1,    55,   864,    -1,
       9,    -1,   217,    -1,   401,    -1,  1071,   864,    -1,   322,
     859,    -1,   860,    -1,   859,   860,    -1,    55,    48,  1071,
     864,    -1,   861,   862,    -1,    -1,     9,    -1,   217,    -1,
     168,    -1,   401,    -1,  1071,    48,  1072,   864,    -1,    89,
    1071,   394,  1072,   864,    -1,    -1,   864,   996,   865,  1067,
      -1,    -1,   397,    -1,    -1,   238,   867,   932,    -1,    -1,
     242,   869,   870,    -1,  1067,   394,  1064,    -1,    90,  1067,
     394,  1064,    -1,    -1,   244,   872,   873,   874,    -1,  1067,
      48,  1047,  1005,    -1,  1067,    48,  1067,   181,  1047,  1005,
      -1,    -1,   132,    -1,    -1,   273,   876,   877,    -1,    -1,
     877,   878,   879,  1051,   880,    -1,   201,    -1,   279,    -1,
     209,    -1,   161,    -1,    -1,   357,  1146,   566,    -1,    -1,
    1146,   252,   335,    -1,  1146,   232,    -1,    -1,   288,   882,
     883,    -1,   886,   887,    -1,    -1,   887,   884,   732,   885,
      -1,   887,   133,    -1,    -1,   133,    -1,  1056,    -1,  1056,
     391,  1056,    -1,    -1,   172,    -1,  1074,   393,    -1,   888,
     413,  1032,    -1,   888,   426,   889,    -1,    -1,  1146,   388,
     996,    -1,   890,    -1,   889,     8,   890,    -1,  1076,   174,
    1067,    48,  1067,   413,  1032,    -1,    -1,   309,   892,  1052,
    1096,  1133,   893,   894,   895,   896,   897,    -1,    -1,   204,
    1076,    -1,    -1,   193,   232,    -1,  1146,   232,    -1,  1146,
     252,   232,    -1,  1146,   192,   232,    -1,  1146,   427,    -1,
      -1,   212,  1121,   668,    -1,    -1,  1015,    -1,  1026,    -1,
      -1,   135,    -1,    -1,   318,   899,  1049,   994,    -1,    -1,
     331,   901,  1052,  1133,   893,  1015,   902,    -1,    -1,   136,
      -1,    -1,   336,   904,  1049,   994,   905,  1025,   906,    -1,
      -1,  1146,   232,    -1,  1146,   252,   232,    -1,    -1,   137,
      -1,   338,    -1,    -1,   346,   909,   910,   918,    -1,  1050,
     912,   913,   915,    -1,    -1,     9,  1050,   913,   428,  1033,
     911,   732,    -1,    -1,   426,  1076,    -1,    -1,    -1,  1110,
     121,   914,   732,    -1,   916,    -1,   916,   915,    -1,    -1,
     428,  1032,   917,   732,    -1,    -1,   138,    -1,    -1,   356,
     920,   921,    -1,   922,    -1,   923,    -1,   924,    -1,   926,
      -1,   928,    -1,   145,  1071,   394,  1071,    -1,  1064,   394,
     144,  1070,    -1,  1064,   394,  1067,    -1,  1064,   925,    48,
    1067,    -1,   414,    -1,   116,    -1,   927,    -1,   926,   927,
      -1,  1053,   394,   507,    -1,   929,    -1,   928,   929,    -1,
    1064,   394,   399,    -1,  1064,   394,   395,    -1,    -1,   365,
     931,   932,    -1,    -1,  1078,   934,   936,   937,   933,   938,
     939,    -1,    -1,   934,  1129,   638,  1123,   935,    -1,    -1,
     935,  1078,    -1,    -1,  1103,  1130,    -1,    -1,  1104,  1121,
    1060,    -1,    -1,   424,  1051,    -1,   201,   298,  1121,   886,
      -1,    -1,   181,  1051,    -1,   279,   298,  1121,   886,    -1,
      -1,    -1,   374,   941,  1052,   942,   943,  1025,   945,    -1,
      -1,   212,  1121,   944,   668,    -1,  1097,  1038,    -1,  1097,
    1039,    -1,  1097,  1040,    -1,  1097,  1041,    -1,  1097,  1042,
      -1,    -1,   139,    -1,    -1,   376,   340,   947,   948,    -1,
     376,   228,    -1,    -1,   332,  1067,    -1,   181,  1067,    -1,
      -1,   377,   950,   951,   204,  1076,   953,  1010,   954,    -1,
     952,    -1,   951,   952,    -1,  1067,    -1,   107,  1112,   363,
      -1,   107,  1112,  1067,    -1,    -1,  1146,   291,  1076,    -1,
      -1,   140,    -1,    -1,   380,   956,   957,   958,    -1,  1066,
     174,  1047,  1005,    -1,  1066,   174,  1067,   181,  1047,  1005,
      -1,    90,  1076,   174,  1076,  1099,  1005,    -1,    -1,   141,
      -1,   382,   960,    -1,    -1,   297,    -1,    -1,   387,   962,
     668,    -1,    -1,   402,   964,  1076,   174,  1071,   394,  1072,
      -1,    -1,   407,   966,  1052,   967,    -1,    -1,   310,    -1,
     312,    -1,    -1,   412,   969,  1076,   970,   973,   953,   977,
    1010,   978,    -1,    -1,   107,  1112,   971,    -1,   972,    -1,
     971,   275,   972,    -1,  1093,  1071,    -1,   204,   974,    -1,
     973,   974,    -1,  1076,   975,   976,    -1,    -1,   108,  1120,
    1076,    -1,    -1,    91,  1120,  1076,    -1,    -1,   385,  1120,
    1076,    -1,    -1,   142,    -1,   980,    -1,   989,    -1,   991,
      -1,   423,   981,   983,   984,   985,   988,  1129,   982,    -1,
      -1,   182,    -1,  1051,    -1,   201,    -1,   279,    -1,   209,
      -1,   161,    -1,    -1,     8,    -1,    -1,   371,    -1,   158,
      -1,   154,    -1,   158,    -1,   280,    -1,   256,    -1,   258,
      -1,    -1,   298,    -1,   423,  1118,   102,  1129,   990,    -1,
    1056,    -1,     9,   299,    -1,   423,   981,    34,   324,  1076,
      -1,    -1,   435,   993,  1049,   994,   905,   995,   997,   998,
      -1,    -1,   174,  1073,    -1,    -1,   996,  1105,  1075,  1124,
      -1,   996,  1105,  1054,    -1,   996,  1105,   284,    -1,    34,
      -1,     8,    -1,    -1,  1020,    -1,  1026,    -1,    -1,   143,
      -1,  1001,  1003,    -1,  1001,  1003,    -1,    -1,    -1,   158,
    1002,   732,    -1,    -1,    -1,   256,  1004,   732,    -1,  1006,
    1008,    -1,    -1,    -1,   364,  1007,   732,    -1,    -1,    -1,
     259,  1009,   732,    -1,  1011,  1013,    -1,    -1,    -1,   280,
    1012,   732,    -1,    -1,    -1,   258,  1014,   732,    -1,  1016,
      -1,  1018,    -1,  1016,  1018,    -1,    -1,   121,  1017,   732,
      -1,    -1,   254,  1019,   732,    -1,  1021,    -1,  1023,    -1,
    1021,  1023,    -1,    -1,   149,  1022,   732,    -1,    -1,   255,
    1024,   732,    -1,    -1,  1026,    -1,  1027,    -1,  1029,    -1,
    1027,  1029,    -1,    -1,   207,  1028,   732,    -1,    -1,   257,
    1030,   732,    -1,    -1,  1112,  1075,  1124,    -1,  1033,    -1,
    1034,    -1,    -1,  1035,  1036,    -1,  1036,   208,    -1,  1037,
    1067,    -1,  1036,   447,    -1,  1036,   270,    -1,  1036,   263,
      -1,  1036,    12,    -1,  1036,    13,    -1,  1036,    14,    -1,
    1036,    57,    -1,  1036,   293,    -1,  1036,   249,    -1,  1036,
     438,    -1,  1036,   253,    -1,    -1,  1037,   208,    -1,  1037,
     448,    -1,  1037,   439,    -1,  1037,   440,    -1,  1037,   444,
      -1,  1037,   253,    -1,  1036,   439,    -1,  1036,   440,    -1,
    1036,   441,    -1,  1036,   442,    -1,  1036,   444,    -1,  1036,
    1038,    -1,  1036,  1039,    -1,  1036,  1040,    -1,  1036,  1041,
      -1,  1036,  1042,    -1,  1036,   248,    -1,  1037,  1038,    -1,
    1037,  1039,    -1,  1037,  1040,    -1,  1037,  1041,    -1,  1037,
    1042,    -1,  1037,   248,    -1,  1036,    20,    -1,  1036,   275,
      -1,   446,    -1,   151,  1144,    -1,   152,    -1,   449,    -1,
     185,  1141,    -1,   450,    -1,   220,  1141,    -1,   179,    -1,
     185,  1141,   275,   151,  1144,    -1,   216,    -1,   220,  1141,
     275,   151,  1144,    -1,  1045,    -1,  1043,  1044,  1045,    -1,
      -1,    68,    -1,   351,    -1,  1068,    -1,  1045,   439,  1045,
      -1,  1045,   440,  1045,    -1,  1045,   441,  1045,    -1,  1045,
     442,  1045,    -1,   439,  1045,    -1,   440,  1045,    -1,  1045,
     444,  1045,    -1,   448,  1045,   447,    -1,   224,    -1,   224,
    1101,   432,    -1,  1048,    -1,  1047,  1048,    -1,  1067,  1099,
      -1,  1078,    -1,  1078,    -1,  1052,    -1,  1051,  1052,    -1,
     432,    -1,  1054,    -1,  1053,  1054,    -1,   240,    -1,    -1,
    1055,  1056,    -1,  1057,    -1,  1078,    -1,  1058,    -1,  1058,
    1101,  1058,    -1,   228,    -1,  1060,    -1,  1059,  1060,    -1,
    1078,    -1,    -1,  1060,    -1,  1060,    -1,   228,    -1,   432,
      -1,  1065,    -1,  1064,  1065,    -1,  1076,    -1,     6,  1128,
    1077,    -1,  1067,    -1,  1066,  1067,    -1,  1076,    -1,   219,
    1128,  1077,    -1,   219,  1128,  1083,    -1,   219,  1128,  1085,
      -1,     6,  1128,  1069,  1070,    -1,     6,  1128,  1077,    -1,
    1082,    -1,  1085,    -1,  1046,    -1,  1076,    -1,   219,  1128,
    1077,    -1,   219,  1128,  1083,    -1,   219,  1128,  1085,    -1,
    1083,    -1,  1085,    -1,  1046,    -1,   301,    -1,   144,    -1,
    1077,    -1,   228,    -1,  1076,    -1,  1083,    -1,  1076,    -1,
    1082,    -1,  1076,    -1,   228,    -1,  1076,    -1,   228,    -1,
    1085,    -1,  1076,    -1,  1081,    -1,   438,    -1,  1077,    -1,
    1078,    -1,  1078,  1079,    -1,  1078,  1080,    -1,  1078,  1079,
    1080,    -1,   432,    -1,   432,  1101,  1078,    -1,   448,  1043,
     447,    -1,   448,  1045,   451,   447,    -1,   448,  1045,   451,
    1045,   447,    -1,   228,    -1,  1083,    -1,     9,  1084,    -1,
    1084,    -1,  1083,   452,  1084,    -1,   228,    -1,   369,    -1,
     438,    -1,   306,    -1,   189,    -1,   235,    -1,   398,    -1,
      94,  1086,    -1,   429,  1086,    -1,   421,   448,  1045,   447,
    1086,    -1,   233,   448,  1045,   447,  1086,    -1,   333,   448,
    1045,   447,  1086,    -1,    79,   448,  1043,   447,  1086,    -1,
     378,   448,  1043,   447,  1086,    -1,   379,   448,  1043,   447,
    1086,    -1,   403,   448,  1089,   447,  1086,    -1,   265,   448,
    1090,   447,    -1,   230,   448,  1091,   447,  1086,    -1,   178,
    1087,    -1,    -1,   448,  1045,   451,   447,    -1,   448,  1045,
     451,  1045,   447,    -1,    -1,   448,  1088,   447,    -1,    -1,
    1043,    -1,  1045,    -1,  1045,  1044,   217,    -1,  1045,  1044,
     401,    -1,  1045,    -1,  1045,  1044,  1045,    -1,  1045,    -1,
    1045,  1044,  1060,    -1,    -1,    -1,     9,    -1,    -1,  1103,
      -1,    -1,   199,    -1,    -1,   250,    -1,   295,    -1,    -1,
     253,    -1,    -1,   274,    -1,    -1,   339,    -1,    -1,   353,
    1113,    -1,   194,    -1,   268,    -1,   310,  1121,    -1,   312,
    1107,    -1,   431,   117,    -1,   117,    -1,    61,   354,    -1,
     354,    -1,    -1,     7,    -1,    -1,    17,    -1,    -1,    22,
      -1,    -1,    23,    -1,    -1,    26,    -1,    -1,    29,    -1,
      -1,    36,    -1,    -1,    48,    -1,    -1,    54,    -1,    -1,
      55,    -1,    -1,    82,    -1,    -1,    97,    -1,    -1,   396,
      -1,    -1,   170,    -1,    -1,   174,    -1,    -1,   194,    -1,
      -1,   208,    -1,    -1,   208,    -1,    22,    -1,    -1,   212,
      -1,    -1,   225,    -1,   226,    -1,    -1,   226,    -1,    -1,
     241,    -1,    -1,   261,    -1,    -1,   268,    -1,    -1,   271,
      -1,    -1,   276,    -1,   194,   276,    -1,    -1,   278,    -1,
      -1,   301,    -1,    -1,   310,    -1,    -1,   337,    -1,    -1,
     356,    -1,    -1,   358,    -1,    -1,   358,    -1,   358,   208,
      -1,    -1,   363,    -1,    -1,   375,    -1,    -1,   386,    -1,
      -1,   389,    -1,    -1,   390,    -1,    -1,   393,    -1,    -1,
     394,    -1,    -1,   428,    -1,    -1,   431,    -1
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
    1679,  1686,  1687,  1688,  1691,  1692,  1696,  1703,  1704,  1711,
    1718,  1722,  1723,  1724,  1731,  1751,  1798,  1798,  1802,  1806,
    1822,  1823,  1824,  1830,  1840,  1849,  1851,  1852,  1858,  1862,
    1863,  1864,  1867,  1868,  1869,  1873,  1877,  1878,  1884,  1885,
    1889,  1898,  1907,  1916,  1931,  1941,  1948,  1952,  1990,  1997,
    2004,  2008,  2009,  2010,  2018,  2019,  2022,  2023,  2027,  2028,
    2032,  2033,  2039,  2064,  2065,  2066,  2067,  2073,  2080,  2081,
    2085,  2088,  2089,  2097,  2098,  2112,  2113,  2113,  2116,  2115,
    2128,  2129,  2133,  2145,  2154,  2158,  2159,  2169,  2168,  2186,
    2187,  2191,  2198,  2205,  2206,  2207,  2208,  2209,  2210,  2211,
    2212,  2213,  2220,  2224,  2224,  2224,  2230,  2242,  2267,  2291,
    2292,  2299,  2300,  2304,  2305,  2312,  2319,  2320,  2327,  2331,
    2340,  2341,  2347,  2357,  2375,  2376,  2380,  2381,  2382,  2386,
    2393,  2400,  2410,  2417,  2435,  2439,  2450,  2451,  2451,  2462,
    2463,  2467,  2467,  2484,  2485,  2487,  2491,  2493,  2492,  2524,
    2529,  2534,  2540,  2549,  2557,  2558,  2566,  2567,  2568,  2572,
    2592,  2596,  2605,  2606,  2607,  2608,  2609,  2610,  2611,  2612,
    2613,  2614,  2615,  2616,  2617,  2618,  2625,  2647,  2669,  2670,
    2682,  2702,  2709,  2710,  2714,  2715,  2716,  2717,  2718,  2719,
    2720,  2721,  2722,  2723,  2724,  2725,  2730,  2735,  2736,  2737,
    2738,  2739,  2740,  2741,  2742,  2743,  2744,  2745,  2746,  2747,
    2748,  2749,  2750,  2751,  2752,  2753,  2761,  2769,  2777,  2784,
    2789,  2800,  2817,  2818,  2821,  2822,  2829,  2853,  2854,  2871,
    2872,  2875,  2876,  2883,  2884,  2889,  2899,  2906,  2909,  2910,
    2911,  2918,  2925,  2950,  2950,  2955,  2956,  2960,  2961,  2964,
    2965,  2978,  2990,  3010,  3024,  3026,  3025,  3045,  3046,  3046,
    3059,  3061,  3060,  3072,  3073,  3077,  3078,  3087,  3094,  3097,
    3101,  3105,  3106,  3107,  3114,  3115,  3119,  3122,  3122,  3125,
    3126,  3132,  3137,  3138,  3141,  3142,  3145,  3146,  3149,  3150,
    3153,  3154,  3158,  3159,  3160,  3164,  3165,  3168,  3169,  3173,
    3177,  3178,  3182,  3183,  3184,  3185,  3186,  3187,  3188,  3189,
    3190,  3191,  3192,  3193,  3194,  3195,  3196,  3197,  3201,  3205,
    3206,  3207,  3208,  3209,  3210,  3211,  3215,  3219,  3220,  3221,
    3225,  3226,  3230,  3234,  3239,  3243,  3247,  3251,  3252,  3256,
    3257,  3261,  3262,  3263,  3266,  3266,  3266,  3269,  3273,  3276,
    3276,  3279,  3286,  3287,  3288,  3287,  3305,  3306,  3310,  3311,
    3316,  3318,  3317,  3353,  3354,  3358,  3359,  3360,  3361,  3362,
    3363,  3364,  3365,  3366,  3367,  3368,  3369,  3370,  3371,  3372,
    3373,  3374,  3378,  3382,  3386,  3390,  3391,  3392,  3393,  3394,
    3395,  3396,  3397,  3404,  3408,  3418,  3421,  3425,  3429,  3433,
    3441,  3444,  3448,  3452,  3456,  3464,  3477,  3479,  3489,  3478,
    3516,  3518,  3517,  3524,  3523,  3532,  3533,  3538,  3545,  3547,
    3551,  3561,  3563,  3571,  3579,  3608,  3639,  3641,  3651,  3656,
    3667,  3668,  3668,  3695,  3696,  3700,  3701,  3702,  3703,  3719,
    3731,  3762,  3799,  3811,  3814,  3815,  3824,  3828,  3824,  3841,
    3859,  3863,  3864,  3865,  3866,  3867,  3868,  3869,  3870,  3871,
    3872,  3873,  3874,  3875,  3876,  3877,  3878,  3879,  3880,  3881,
    3882,  3883,  3884,  3885,  3886,  3887,  3888,  3889,  3890,  3891,
    3892,  3893,  3894,  3895,  3896,  3897,  3898,  3899,  3900,  3901,
    3902,  3903,  3904,  3905,  3906,  3907,  3908,  3909,  3910,  3911,
    3912,  3935,  3934,  3947,  3951,  3955,  3959,  3963,  3967,  3971,
    3975,  3979,  3983,  3987,  3991,  3995,  3999,  4003,  4007,  4011,
    4018,  4019,  4020,  4021,  4022,  4023,  4027,  4031,  4032,  4035,
    4036,  4040,  4041,  4045,  4046,  4047,  4048,  4049,  4050,  4051,
    4052,  4056,  4060,  4064,  4069,  4070,  4071,  4072,  4073,  4074,
    4078,  4079,  4088,  4088,  4094,  4098,  4102,  4108,  4109,  4113,
    4114,  4123,  4123,  4128,  4132,  4139,  4140,  4149,  4155,  4156,
    4160,  4160,  4168,  4168,  4178,  4180,  4179,  4188,  4189,  4194,
    4201,  4208,  4210,  4214,  4222,  4233,  4234,  4235,  4240,  4244,
    4243,  4255,  4259,  4258,  4269,  4270,  4279,  4279,  4283,  4284,
    4296,  4296,  4300,  4301,  4312,  4313,  4314,  4315,  4316,  4319,
    4319,  4327,  4327,  4333,  4340,  4341,  4344,  4344,  4351,  4364,
    4377,  4377,  4388,  4389,  4398,  4398,  4418,  4417,  4430,  4434,
    4438,  4442,  4446,  4450,  4454,  4459,  4463,  4470,  4471,  4472,
    4476,  4477,  4482,  4483,  4484,  4485,  4486,  4487,  4488,  4489,
    4490,  4491,  4495,  4499,  4503,  4508,  4509,  4513,  4514,  4523,
    4523,  4529,  4533,  4537,  4541,  4545,  4552,  4553,  4562,  4562,
    4584,  4583,  4602,  4603,  4614,  4623,  4628,  4636,  4665,  4666,
    4672,  4671,  4687,  4691,  4690,  4705,  4706,  4711,  4712,  4723,
    4752,  4753,  4754,  4757,  4758,  4762,  4763,  4772,  4772,  4777,
    4778,  4786,  4803,  4820,  4838,  4863,  4863,  4876,  4876,  4889,
    4889,  4898,  4902,  4915,  4915,  4928,  4930,  4928,  4941,  4946,
    4950,  4949,  4963,  4964,  4973,  4973,  4981,  4982,  4986,  4987,
    4988,  4992,  4993,  4998,  4999,  5004,  5008,  5009,  5010,  5011,
    5012,  5013,  5014,  5018,  5019,  5028,  5028,  5041,  5040,  5050,
    5051,  5052,  5056,  5057,  5061,  5062,  5063,  5069,  5069,  5074,
    5075,  5079,  5080,  5081,  5082,  5083,  5084,  5090,  5094,  5095,
    5099,  5104,  5108,  5109,  5110,  5111,  5112,  5116,  5142,  5155,
    5156,  5160,  5160,  5168,  5168,  5178,  5178,  5183,  5187,  5199,
    5199,  5205,  5209,  5216,  5217,  5226,  5226,  5230,  5231,  5245,
    5246,  5247,  5248,  5252,  5253,  5257,  5258,  5259,  5271,  5271,
    5276,  5281,  5280,  5290,  5297,  5298,  5302,  5307,  5316,  5319,
    5323,  5328,  5335,  5342,  5343,  5347,  5348,  5353,  5365,  5365,
    5388,  5389,  5393,  5394,  5398,  5402,  5406,  5410,  5417,  5418,
    5432,  5433,  5434,  5438,  5439,  5448,  5448,  5463,  5463,  5474,
    5475,  5484,  5484,  5495,  5496,  5500,  5507,  5508,  5517,  5530,
    5530,  5536,  5541,  5540,  5551,  5552,  5556,  5558,  5557,  5568,
    5569,  5574,  5573,  5584,  5585,  5594,  5594,  5599,  5600,  5601,
    5602,  5603,  5609,  5618,  5622,  5631,  5638,  5639,  5645,  5646,
    5650,  5659,  5660,  5664,  5668,  5680,  5680,  5686,  5685,  5702,
    5705,  5721,  5722,  5725,  5726,  5730,  5731,  5736,  5741,  5749,
    5761,  5766,  5774,  5790,  5791,  5790,  5811,  5812,  5828,  5829,
    5830,  5831,  5832,  5836,  5837,  5846,  5846,  5851,  5858,  5859,
    5860,  5869,  5869,  5878,  5879,  5883,  5884,  5885,  5889,  5890,
    5894,  5895,  5904,  5904,  5910,  5914,  5918,  5925,  5926,  5935,
    5942,  5943,  5951,  5951,  5964,  5964,  5980,  5980,  5989,  5991,
    5992,  6001,  6001,  6011,  6012,  6017,  6018,  6023,  6030,  6031,
    6036,  6043,  6044,  6048,  6049,  6053,  6054,  6058,  6059,  6068,
    6069,  6070,  6074,  6098,  6101,  6109,  6119,  6124,  6129,  6134,
    6141,  6142,  6145,  6146,  6150,  6150,  6154,  6154,  6158,  6158,
    6161,  6162,  6166,  6173,  6174,  6178,  6190,  6190,  6201,  6202,
    6207,  6210,  6214,  6218,  6225,  6226,  6229,  6230,  6231,  6235,
    6236,  6249,  6257,  6264,  6266,  6265,  6275,  6277,  6276,  6291,
    6295,  6297,  6296,  6307,  6309,  6308,  6325,  6331,  6333,  6332,
    6342,  6344,  6343,  6359,  6364,  6369,  6379,  6378,  6390,  6389,
    6405,  6410,  6415,  6425,  6424,  6436,  6435,  6450,  6451,  6455,
    6460,  6465,  6475,  6474,  6486,  6485,  6502,  6505,  6517,  6524,
    6531,  6531,  6541,  6542,  6543,  6545,  6546,  6547,  6548,  6549,
    6550,  6552,  6553,  6554,  6556,  6559,  6561,  6562,  6564,  6565,
    6566,  6568,  6570,  6571,  6572,  6573,  6574,  6576,  6577,  6578,
    6579,  6580,  6581,  6583,  6584,  6585,  6586,  6587,  6588,  6590,
    6591,  6594,  6594,  6594,  6595,  6595,  6596,  6596,  6597,  6597,
    6598,  6598,  6603,  6604,  6607,  6608,  6609,  6613,  6614,  6615,
    6616,  6617,  6618,  6619,  6620,  6621,  6632,  6644,  6659,  6660,
    6665,  6671,  6677,  6697,  6701,  6717,  6731,  6732,  6737,  6743,
    6744,  6749,  6758,  6759,  6760,  6764,  6775,  6776,  6780,  6788,
    6789,  6793,  6794,  6800,  6820,  6821,  6825,  6826,  6830,  6831,
    6835,  6836,  6837,  6838,  6839,  6840,  6841,  6842,  6843,  6847,
    6848,  6849,  6850,  6851,  6852,  6853,  6857,  6858,  6862,  6863,
    6867,  6868,  6872,  6873,  6884,  6885,  6889,  6890,  6891,  6895,
    6896,  6897,  6905,  6909,  6910,  6911,  6912,  6916,  6917,  6921,
    6931,  6949,  6976,  6988,  6989,  6999,  7000,  7004,  7005,  7006,
    7007,  7008,  7009,  7010,  7018,  7022,  7026,  7030,  7034,  7038,
    7042,  7046,  7050,  7054,  7058,  7062,  7069,  7070,  7071,  7075,
    7076,  7080,  7081,  7086,  7093,  7100,  7110,  7117,  7127,  7134,
    7148,  7158,  7159,  7163,  7164,  7168,  7169,  7173,  7174,  7175,
    7179,  7180,  7184,  7185,  7189,  7190,  7194,  7195,  7202,  7202,
    7203,  7203,  7204,  7204,  7205,  7205,  7207,  7207,  7208,  7208,
    7209,  7209,  7210,  7210,  7211,  7211,  7212,  7212,  7213,  7213,
    7214,  7214,  7215,  7215,  7216,  7216,  7217,  7217,  7218,  7218,
    7219,  7219,  7220,  7220,  7221,  7221,  7222,  7222,  7223,  7223,
    7224,  7224,  7224,  7225,  7225,  7226,  7226,  7226,  7227,  7227,
    7228,  7228,  7229,  7229,  7230,  7230,  7231,  7231,  7232,  7232,
    7232,  7233,  7233,  7234,  7234,  7235,  7235,  7236,  7236,  7237,
    7237,  7238,  7238,  7239,  7239,  7239,  7240,  7240,  7241,  7241,
    7242,  7242,  7243,  7243,  7244,  7244,  7245,  7245,  7246,  7246,
    7248,  7248,  7249,  7249
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
     559,   559,   559,   559,   560,   561,   562,   562,   563,   564,
     565,   566,   566,   566,   567,   567,   568,   568,   569,   569,
     570,   570,   571,   572,   572,   572,   572,   573,   574,   574,
     575,   576,   576,   577,   577,   578,   579,   578,   580,   578,
     581,   581,   582,   583,   583,   584,   584,   586,   585,   587,
     587,   588,   588,   588,   588,   588,   588,   588,   588,   588,
     588,   588,   589,   590,   590,   590,   591,   591,   591,   592,
     592,   593,   593,   594,   594,   595,   596,   596,   597,   597,
     598,   598,   599,   600,   601,   601,   602,   602,   602,   603,
     604,   605,   606,   607,   608,   608,   609,   610,   609,   611,
     611,   613,   612,   614,   614,   614,   615,   616,   615,   617,
     618,   618,   618,   619,   620,   620,   621,   621,   621,   622,
     623,   623,   624,   624,   624,   624,   624,   624,   624,   624,
     624,   624,   624,   624,   624,   624,   625,   626,   627,   627,
     628,   629,   630,   630,   631,   631,   631,   631,   631,   631,
     631,   631,   631,   631,   631,   631,   631,   631,   631,   631,
     631,   631,   631,   631,   631,   631,   631,   631,   631,   631,
     631,   631,   631,   631,   631,   631,   631,   631,   631,   632,
     632,   633,   634,   634,   635,   635,   636,   637,   637,   638,
     638,   639,   639,   640,   640,   641,   642,   643,   644,   644,
     644,   645,   646,   648,   647,   649,   649,   650,   650,   651,
     651,   652,   652,   653,   654,   655,   654,   656,   657,   656,
     658,   659,   658,   660,   660,   661,   661,   662,   663,   663,
     664,   664,   664,   664,   665,   665,   666,   667,   667,   668,
     668,   669,   670,   670,   671,   671,   672,   672,   673,   673,
     674,   674,   675,   675,   675,   676,   676,   677,   677,   678,
     679,   679,   680,   680,   680,   680,   680,   680,   680,   680,
     680,   680,   680,   680,   680,   680,   680,   680,   681,   682,
     682,   682,   682,   682,   682,   682,   683,   684,   684,   684,
     685,   685,   686,   687,   688,   689,   690,   691,   691,   692,
     692,   693,   693,   693,   694,   694,   694,   695,   696,   697,
     697,   698,   699,   700,   701,   699,   702,   702,   703,   703,
     704,   705,   704,   706,   706,   707,   707,   707,   707,   707,
     707,   707,   707,   707,   707,   707,   707,   707,   707,   707,
     707,   707,   707,   707,   707,   707,   707,   707,   707,   707,
     707,   707,   707,   707,   707,   708,   708,   708,   708,   708,
     709,   709,   709,   709,   709,   710,   711,   712,   713,   711,
     714,   715,   714,   716,   714,   717,   717,   718,   719,   719,
     719,   720,   720,   720,   720,   720,   721,   721,   722,   722,
     723,   724,   723,   725,   725,   726,   726,   726,   726,   726,
     727,   728,   729,   730,   731,   731,   733,   734,   732,   735,
     735,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   738,   737,   739,   739,   739,   739,   739,   739,   739,
     739,   739,   739,   739,   739,   739,   739,   739,   739,   739,
     740,   740,   740,   740,   740,   740,   741,   742,   742,   743,
     743,   744,   744,   745,   745,   745,   745,   745,   745,   745,
     745,   745,   745,   745,   745,   745,   745,   745,   745,   745,
     746,   746,   748,   747,   749,   749,   749,   750,   750,   751,
     751,   753,   752,   754,   754,   755,   755,   756,   757,   757,
     758,   758,   760,   759,   761,   762,   761,   763,   763,   764,
     764,   765,   765,   765,   765,   766,   766,   766,   767,   768,
     767,   769,   770,   769,   771,   771,   773,   772,   774,   774,
     776,   775,   777,   777,   778,   778,   778,   778,   778,   779,
     779,   781,   780,   782,   783,   783,   784,   784,   785,   786,
     788,   787,   789,   789,   791,   790,   793,   792,   794,   794,
     794,   794,   794,   794,   794,   794,   794,   795,   795,   795,
     796,   796,   797,   797,   797,   797,   797,   797,   797,   797,
     797,   797,   797,   797,   797,   797,   797,   798,   798,   800,
     799,   801,   801,   801,   801,   801,   802,   802,   804,   803,
     806,   805,   807,   807,   808,   808,   808,   809,   810,   810,
     812,   811,   813,   814,   813,   815,   815,   816,   816,   817,
     817,   817,   817,   818,   818,   819,   819,   821,   820,   822,
     822,   822,   822,   822,   822,   824,   823,   826,   825,   828,
     827,   829,   829,   831,   830,   833,   834,   832,   832,   835,
     836,   835,   837,   837,   839,   838,   840,   840,   841,   841,
     841,   842,   842,   843,   843,   844,   845,   845,   845,   845,
     845,   845,   845,   846,   846,   848,   847,   850,   849,   851,
     851,   851,   852,   852,   853,   853,   853,   855,   854,   856,
     856,   857,   857,   857,   857,   857,   857,   858,   859,   859,
     860,   860,   861,   861,   861,   861,   861,   862,   863,   864,
     864,   865,   865,   867,   866,   869,   868,   870,   870,   872,
     871,   873,   873,   874,   874,   876,   875,   877,   877,   878,
     878,   878,   878,   879,   879,   880,   880,   880,   882,   881,
     883,   884,   883,   883,   885,   885,   886,   886,   887,   887,
     887,   887,   887,   888,   888,   889,   889,   890,   892,   891,
     893,   893,   894,   894,   894,   894,   894,   894,   895,   895,
     896,   896,   896,   897,   897,   899,   898,   901,   900,   902,
     902,   904,   903,   905,   905,   905,   906,   906,   907,   909,
     908,   910,   911,   910,   912,   912,   913,   914,   913,   915,
     915,   917,   916,   918,   918,   920,   919,   921,   921,   921,
     921,   921,   922,   923,   923,   924,   925,   925,   926,   926,
     927,   928,   928,   929,   929,   931,   930,   933,   932,   934,
     934,   935,   935,   936,   936,   937,   937,   938,   938,   938,
     939,   939,   939,   941,   942,   940,   943,   943,   944,   944,
     944,   944,   944,   945,   945,   947,   946,   946,   948,   948,
     948,   950,   949,   951,   951,   952,   952,   952,   953,   953,
     954,   954,   956,   955,   957,   957,   957,   958,   958,   959,
     960,   960,   962,   961,   964,   963,   966,   965,   967,   967,
     967,   969,   968,   970,   970,   971,   971,   972,   973,   973,
     974,   975,   975,   976,   976,   977,   977,   978,   978,   979,
     979,   979,   980,   981,   981,   982,   982,   982,   982,   982,
     983,   983,   984,   984,   985,   985,   986,   986,   987,   987,
     988,   988,   989,   990,   990,   991,   993,   992,   994,   994,
     995,   995,   995,   995,   996,   996,   997,   997,   997,   998,
     998,   999,  1000,  1001,  1002,  1001,  1003,  1004,  1003,  1005,
    1006,  1007,  1006,  1008,  1009,  1008,  1010,  1011,  1012,  1011,
    1013,  1014,  1013,  1015,  1015,  1015,  1017,  1016,  1019,  1018,
    1020,  1020,  1020,  1022,  1021,  1024,  1023,  1025,  1025,  1026,
    1026,  1026,  1028,  1027,  1030,  1029,  1031,  1031,  1032,  1033,
    1035,  1034,  1036,  1036,  1036,  1036,  1036,  1036,  1036,  1036,
    1036,  1036,  1036,  1036,  1036,  1037,  1037,  1037,  1037,  1037,
    1037,  1037,  1037,  1037,  1037,  1037,  1037,  1037,  1037,  1037,
    1037,  1037,  1037,  1037,  1037,  1037,  1037,  1037,  1037,  1037,
    1037,  1038,  1038,  1038,  1039,  1039,  1040,  1040,  1041,  1041,
    1042,  1042,  1043,  1043,  1044,  1044,  1044,  1045,  1045,  1045,
    1045,  1045,  1045,  1045,  1045,  1045,  1046,  1046,  1047,  1047,
    1048,  1049,  1050,  1051,  1051,  1052,  1053,  1053,  1054,  1055,
    1055,  1056,  1057,  1057,  1057,  1058,  1059,  1059,  1060,  1061,
    1061,  1062,  1062,  1063,  1064,  1064,  1065,  1065,  1066,  1066,
    1067,  1067,  1067,  1067,  1067,  1067,  1067,  1067,  1067,  1068,
    1068,  1068,  1068,  1068,  1068,  1068,  1069,  1069,  1070,  1070,
    1071,  1071,  1072,  1072,  1073,  1073,  1074,  1074,  1074,  1075,
    1075,  1075,  1076,  1077,  1077,  1077,  1077,  1078,  1078,  1079,
    1080,  1080,  1081,  1082,  1082,  1083,  1083,  1084,  1084,  1084,
    1084,  1084,  1084,  1084,  1085,  1085,  1085,  1085,  1085,  1085,
    1085,  1085,  1085,  1085,  1085,  1085,  1086,  1086,  1086,  1087,
    1087,  1088,  1088,  1089,  1089,  1089,  1090,  1090,  1091,  1091,
    1092,  1093,  1093,  1094,  1094,  1095,  1095,  1096,  1096,  1096,
    1097,  1097,  1098,  1098,  1099,  1099,  1100,  1100,  1101,  1101,
    1102,  1102,  1103,  1103,  1104,  1104,  1105,  1105,  1106,  1106,
    1107,  1107,  1108,  1108,  1109,  1109,  1110,  1110,  1111,  1111,
    1112,  1112,  1113,  1113,  1114,  1114,  1115,  1115,  1116,  1116,
    1117,  1117,  1118,  1118,  1119,  1119,  1120,  1120,  1121,  1121,
    1122,  1122,  1122,  1123,  1123,  1124,  1124,  1124,  1125,  1125,
    1126,  1126,  1127,  1127,  1128,  1128,  1129,  1129,  1130,  1130,
    1130,  1131,  1131,  1132,  1132,  1133,  1133,  1134,  1134,  1135,
    1135,  1136,  1136,  1137,  1137,  1137,  1138,  1138,  1139,  1139,
    1140,  1140,  1141,  1141,  1142,  1142,  1143,  1143,  1144,  1144,
    1145,  1145,  1146,  1146
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
       1,     3,     1,     2,     4,     4,     4,     6,     4,     3,
       3,     2,     2,     2,     0,     3,     0,     2,     1,     2,
       1,     1,     5,     0,     1,     1,     1,     5,     1,     2,
       2,     0,     2,     0,     9,     0,     0,     5,     0,     3,
       0,     2,     3,     2,     2,     1,     1,     0,     4,     0,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     0,     1,     1,     4,     6,     9,     0,
       3,     0,     2,     0,     2,     3,     1,     1,     5,     5,
       1,     1,     3,     5,     0,     2,     1,     1,     1,     5,
       4,     3,     4,     3,     3,     3,     0,     0,     5,     0,
       1,     0,     2,     3,     4,     2,     1,     0,     4,     1,
       0,     1,     1,     1,     0,     2,     1,     3,     3,     6,
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     0,     2,
       2,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     2,     2,     1,     2,
       2,     1,     2,     2,     1,     2,     2,     1,     1,     3,
       3,     7,     0,     2,     0,     3,     1,     0,     5,     1,
       1,     0,     3,     1,     2,     1,     2,     2,     0,     1,
       1,     3,     1,     0,     8,     1,     2,     1,     3,     0,
       3,     2,     4,     2,     0,     0,     5,     0,     0,     5,
       0,     0,     5,     0,     1,     1,     2,     5,     0,     2,
       2,     3,     1,     1,     2,     2,     2,     0,     1,     1,
       2,     8,     0,     3,     0,     4,     0,     4,     0,     3,
       0,     3,     1,     4,     2,     1,     1,     0,     2,     4,
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     4,     4,     2,     1,
       1,     2,     3,     1,     3,     6,     2,     3,     2,     1,
       2,     2,     1,     2,     0,     1,     1,     4,     2,     0,
       1,     1,     0,     0,     0,     6,     0,     1,     1,     2,
       1,     0,     5,     0,     2,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     5,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     0,     1,     1,     1,     1,
       0,     1,     1,     1,     1,     3,     0,     0,     0,     9,
       0,     0,     3,     0,     3,     1,     2,     4,     0,     2,
       2,     0,     3,     3,     4,     3,     0,     1,     0,     2,
       0,     0,     7,     0,     2,     1,     1,     1,     2,     2,
       4,     2,     1,     1,     0,     1,     0,     0,     3,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     4,     4,     3,     3,     3,     4,     3,
       4,     3,     3,     3,     4,     5,     3,     4,     3,     3,
       0,     3,     3,     2,     2,     2,     3,     3,     3,     0,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       0,     1,     0,     4,     4,     5,     6,     0,     2,     0,
       1,     0,     3,     3,     5,     0,     2,     2,     0,     5,
       0,     2,     0,     8,     0,     0,     3,     1,     2,     2,
       3,     0,     2,     2,     2,     0,     2,     2,     0,     0,
       3,     0,     0,     3,     0,     1,     0,     3,     0,     2,
       0,     3,     0,     3,     0,     1,     3,     3,     2,     1,
       1,     0,     4,     4,     0,     1,     1,     1,     1,     1,
       0,     6,     0,     1,     0,     4,     0,     4,     3,     3,
       3,     3,     4,     6,     6,     6,     6,     0,     2,     2,
       1,     2,     1,     1,     2,     2,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     1,     1,     0,     1,     0,
       4,     4,     6,     6,     8,     8,     0,     1,     0,     4,
       0,     5,     1,     3,     1,     1,     1,     2,     1,     2,
       0,     3,     0,     0,     3,     2,     3,     1,     3,     2,
       1,     1,     1,     0,     2,     0,     1,     0,     3,     0,
       1,     1,     2,     1,     1,     0,     3,     0,     3,     0,
       5,     0,     3,     0,     2,     0,     0,     8,     3,     0,
       0,     3,     0,     1,     0,     7,     0,     2,     0,     3,
       3,     0,     2,     1,     2,     4,     1,     1,     1,     1,
       1,     1,     1,     0,     1,     0,     3,     0,     4,     1,
       1,     1,     1,     2,     1,     1,     1,     0,     3,     1,
       2,     2,     2,     1,     1,     1,     2,     2,     1,     2,
       4,     2,     0,     1,     1,     1,     1,     4,     5,     0,
       4,     0,     1,     0,     3,     0,     3,     3,     4,     0,
       4,     4,     6,     0,     1,     0,     3,     0,     5,     1,
       1,     1,     1,     0,     3,     0,     3,     2,     0,     3,
       2,     0,     4,     2,     0,     1,     1,     3,     0,     1,
       2,     3,     3,     0,     3,     1,     3,     7,     0,    10,
       0,     2,     0,     2,     2,     3,     3,     2,     0,     3,
       0,     1,     1,     0,     1,     0,     4,     0,     7,     0,
       1,     0,     7,     0,     2,     3,     0,     1,     1,     0,
       4,     4,     0,     7,     0,     2,     0,     0,     4,     1,
       2,     0,     4,     0,     1,     0,     3,     1,     1,     1,
       1,     1,     4,     4,     3,     4,     1,     1,     1,     2,
       3,     1,     2,     3,     3,     0,     3,     0,     7,     0,
       5,     0,     2,     0,     2,     0,     3,     0,     2,     4,
       0,     2,     4,     0,     0,     7,     0,     4,     2,     2,
       2,     2,     2,     0,     1,     0,     4,     2,     0,     2,
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
       2,     2,     2,     2,     2,     0,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     1,     2,     1,     1,     2,     1,     2,     1,     5,
       1,     5,     1,     3,     0,     1,     1,     1,     3,     3,
       3,     3,     2,     2,     3,     3,     1,     3,     1,     2,
       2,     1,     1,     1,     2,     1,     1,     2,     1,     0,
       2,     1,     1,     1,     3,     1,     1,     2,     1,     0,
       1,     1,     1,     1,     1,     2,     1,     3,     1,     2,
       1,     3,     3,     3,     4,     3,     1,     1,     1,     1,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     3,     1,     3,     3,
       4,     5,     1,     1,     2,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     5,     5,     5,     5,
       5,     5,     5,     4,     5,     2,     0,     4,     5,     0,
       3,     0,     1,     1,     3,     3,     1,     3,     1,     3,
       0,     0,     1,     0,     1,     0,     1,     0,     1,     1,
       0,     1,     0,     1,     0,     1,     0,     2,     1,     1,
       2,     2,     2,     1,     2,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     1,     0,     1,     0,     1,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       2,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     2,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     3,     4,     6,     7,
      38,    38,     0,     0,     5,     0,     8,    14,    28,    27,
      29,    29,     0,   253,   253,     0,     0,    24,    40,     0,
       9,    15,    30,    26,  1488,     0,   151,     0,   586,   586,
    1489,     0,     0,     0,     0,     0,     0,    39,   255,     0,
      17,     0,    25,    33,    37,    36,  1513,    35,    42,   153,
       0,   155,   265,   266,     0,   316,   258,   590,    18,    20,
      38,     0,    16,    34,  1514,    32,    41,   159,   157,   236,
       0,     0,   434,     0,   593,   591,   608,     0,    19,    10,
      11,     0,     0,     0,     0,     0,    43,    44,    45,    47,
      46,   154,     0,   234,  1480,   243,   156,     0,   238,   240,
     241,   256,     0,     0,   437,  1325,   259,   319,   267,   598,
     598,     0,     0,     0,   253,    23,    56,    71,    49,    80,
    1442,   160,   159,     0,   152,  1481,  1530,   244,   245,   246,
    1462,   237,   239,   260,   317,     0,     0,   440,   264,     0,
     263,   320,  1430,   269,  1471,   598,   595,   601,     0,   598,
     609,   587,    21,    12,     0,  1488,    54,  1513,    55,  1513,
      60,    62,    63,    64,     0,     0,    70,     0,    73,  1543,
      48,     0,  1542,     0,     0,  1488,  1488,     0,     0,  1521,
    1488,  1488,  1488,  1488,  1488,     0,  1488,  1474,  1488,    79,
       0,    82,    84,    85,    86,    88,    87,    89,    90,    91,
      92,    93,    94,  1443,     0,   158,   236,  1531,  1476,  1463,
    1482,   257,   319,   435,     0,     0,   532,   319,   322,     0,
    1488,   596,  1488,     0,   606,   599,   600,   610,   586,  1488,
       0,    57,  1513,    59,    61,     0,  1455,  1488,     0,    77,
       0,    72,    74,    52,    50,     0,     0,  1343,   106,     0,
       0,  1488,  1488,  1522,  1488,     0,     0,     0,     0,     0,
    1488,     0,  1475,     0,     0,    81,    83,   161,   235,  1477,
       0,  1483,     0,   261,   318,   319,   438,     0,     0,   254,
     262,   325,     0,   329,     0,   330,   326,  1476,  1488,     0,
       0,  1488,  1476,  1500,  1488,  1460,     0,   268,   270,   273,
     274,   275,   276,   277,   278,   279,   280,   281,     0,     0,
    1488,   607,     0,     0,   588,    17,     0,  1392,    69,    58,
    1454,     0,    76,    75,    78,    51,    53,  1488,    98,    99,
       0,     0,     0,  1387,   147,  1338,   146,   100,   101,   150,
       0,   149,   133,  1490,   135,    95,    96,   163,   247,   248,
     251,   242,  1323,   436,   319,   441,     0,     0,   323,   331,
     332,   327,     0,     0,     0,  1488,  1460,     0,     0,     0,
       0,     0,  1501,  1488,     0,  1461,     0,     0,   271,   272,
     602,   603,   605,     0,   597,   611,   613,     0,     0,    68,
       0,  1401,  1397,  1402,  1400,  1398,  1403,  1399,   139,   140,
     142,   148,   145,  1448,  1449,     0,   144,  1492,  1491,   136,
       0,   102,  1515,   249,     0,   250,  1324,   439,   443,   533,
     324,   340,   334,   293,   313,  1450,  1451,   302,  1336,   297,
     296,   295,  1342,  1341,  1498,  1474,  1486,     0,   531,   314,
     315,  1488,  1488,   604,   613,     0,     0,    13,    66,    67,
      65,   111,   125,   121,   126,   108,   124,   122,   109,   110,
     123,   107,   112,   113,   115,   141,     0,  1388,   134,   137,
      97,  1500,     0,  1538,   220,     0,  1500,  1488,  1472,  1493,
     222,     0,  1542,   207,   206,   162,   164,   165,   166,   167,
     168,   169,     0,   170,   171,   219,   172,   173,   174,   175,
     176,   177,  1488,  1468,   252,     0,   442,   444,   445,   534,
    1488,  1464,     0,     0,   283,  1337,  1499,   304,     0,   286,
    1487,  1526,   312,     0,     0,     0,     0,   623,   614,   615,
     616,   617,   622,     0,     0,   114,   117,     0,   143,   138,
     105,   104,  1528,  1488,  1493,  1539,   184,   223,  1488,  1515,
    1473,  1488,  1488,  1494,  1488,  1488,  1462,     0,  1488,     0,
    1469,     0,   448,   446,   536,     0,   422,   364,   397,   385,
     394,   391,   388,  1540,   365,   366,   367,   368,   369,   370,
     371,   372,   373,  1517,   398,     0,   374,   361,   375,   376,
       0,     0,  1524,   378,   379,   377,   418,   381,   382,   380,
    1488,  1490,   341,   342,   343,   344,   345,   346,   362,   347,
     348,   349,   350,   351,   352,   353,   354,   355,     0,     0,
    1465,     0,   335,   294,   285,   284,   282,   303,  1474,  1527,
     291,   300,   299,   301,   298,     0,   619,   621,   624,   681,
     732,   741,   748,   752,   776,   780,   798,   791,   799,   800,
     806,   839,   848,   850,   877,   885,   887,  1538,   893,     0,
     904,   925,   927,   963,   965,   969,   680,   975,   988,  1008,
    1025,  1027,  1031,  1038,  1039,  1055,  1075,  1093,     0,  1111,
    1122,  1130,  1132,  1134,  1136,  1141,  1163,  1186,   618,   630,
     631,   632,   633,   634,   635,   636,   637,   639,   638,   640,
     641,   642,   643,   644,   645,   646,   647,   648,   649,   650,
     651,   652,   653,   654,   655,   656,   657,   658,   659,   660,
     661,   662,   663,   664,   665,   666,   667,   668,   669,   670,
     671,   672,   673,   674,   675,   676,   677,   678,  1159,  1160,
    1161,   679,    22,     0,   116,  1529,  1488,     0,  1488,   186,
     185,   181,     0,  1516,   222,   218,     0,     0,     0,     0,
     229,  1511,  1511,     0,   230,     0,   203,   221,  1488,   330,
     540,   535,   537,   538,   433,   395,   396,   383,   384,   392,
     393,   389,   390,   386,   387,  1541,     0,  1518,   416,   402,
     356,  1383,   431,  1525,   419,   420,   417,     0,     0,   358,
     360,  1446,  1446,     0,  1504,  1504,   339,   336,  1393,  1395,
    1467,   305,   306,   307,   308,     0,     0,   287,  1485,   293,
       0,     0,   625,     0,     0,     0,  1250,   747,     0,   778,
     782,     0,     0,     0,     0,     0,     0,  1250,   879,     0,
       0,   889,   894,     0,  1250,     0,     0,     0,     0,     0,
       0,   977,   998,     0,     0,     0,     0,     0,     0,     0,
       0,  1107,  1105,     0,     0,  1131,  1129,     0,     0,     0,
       0,  1164,  1170,     0,     0,   131,   127,   132,   130,   128,
     129,   118,   119,     0,   192,   193,   191,   190,     0,   179,
     180,     0,   212,   211,   212,   208,   224,   225,   226,   228,
    1512,   231,   232,   233,  1339,  1488,   457,   457,  1490,   477,
     449,   452,   453,     0,   541,   539,   421,     0,  1536,     0,
    1384,  1385,     0,   363,   423,   425,   427,     0,   357,  1472,
     399,   400,  1394,  1505,     0,     0,     0,     0,     0,  1466,
    1474,   292,   612,   620,   730,   700,  1382,  1504,     0,     0,
    1416,  1419,  1504,  1316,     0,     0,     0,     0,     0,     0,
       0,     0,  1416,   739,  1358,   737,  1348,  1350,  1356,  1357,
    1435,   742,     0,  1249,  1265,  1335,     0,  1331,  1333,  1332,
    1377,   754,  1376,  1378,   777,   781,   794,     0,  1318,  1444,
    1515,     0,  1397,   837,   700,     0,  1350,   846,     0,   754,
     856,   855,  1458,   852,   854,   884,   881,   880,   883,   878,
    1504,   886,  1344,  1346,   888,  1329,   898,  1534,  1248,   906,
     926,   459,     0,   929,   930,   931,   964,  1079,     0,   966,
       0,   973,     0,   976,   999,  1335,   989,   998,   991,     0,
     996,     0,  1332,     0,  1437,  1188,  1321,  1515,  1188,     0,
    1053,  1044,  1322,     0,  1328,  1056,  1057,  1058,  1059,  1060,
    1068,  1061,  1071,     0,  1326,     0,  1076,  1094,  1108,  1470,
       0,  1113,  1115,     0,  1127,     0,  1133,     0,  1138,  1143,
    1171,     0,  1172,  1506,  1188,     0,   103,  1433,   188,   187,
     178,   189,     0,   210,   209,  1488,   202,   196,  1340,   204,
       0,   458,   454,     0,   455,     0,   447,   450,   543,   403,
    1537,   404,  1504,     0,     0,     0,  1304,  1302,  1365,  1307,
    1359,  1363,  1364,     0,  1386,   432,  1540,   426,     0,   359,
    1447,   338,   337,  1396,   311,  1498,     0,   289,   731,   682,
    1467,     0,   709,     0,     0,     0,     0,     0,  1404,  1421,
    1415,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1405,   740,   733,     0,     0,  1349,  1436,   745,  1435,
    1251,     0,   750,     0,   755,   765,  1375,   779,  1374,   784,
     795,   792,   797,   796,  1250,  1319,  1445,  1320,  1237,   805,
     838,   807,   817,  1203,  1203,  1203,  1203,   847,   840,     0,
       0,   849,  1459,  1250,   875,   862,   858,   860,  1250,   882,
       0,  1345,   891,  1535,   896,   908,     0,   460,     0,   952,
     937,   928,   932,   934,   935,   936,  1083,     0,     0,   974,
     970,     0,   982,   979,   981,   980,   983,   990,   993,   626,
    1250,     0,     0,  1000,     0,  1438,  1439,  1515,     0,  1026,
    1010,  1033,  1046,  1054,  1040,     0,  1046,     0,  1370,  1371,
    1069,  1072,     0,     0,  1327,  1067,     0,  1066,     0,  1096,
       0,     0,  1106,     0,     0,  1114,     0,  1128,  1123,     0,
       0,  1139,  1140,  1137,  1470,     0,     0,  1173,     0,  1507,
       0,  1033,   120,  1453,     0,   196,   194,  1434,     0,   215,
     201,   227,     0,   451,   456,   462,   472,   330,   478,  1523,
    1506,   407,     0,  1312,  1313,     0,  1305,  1306,  1389,     0,
       0,     0,     0,     0,     0,     0,     0,  1519,   428,   310,
    1498,  1506,   288,   705,   696,  1203,   686,   693,   687,   689,
     691,     0,  1203,     0,   685,   692,   699,   698,     0,  1203,
    1502,  1502,  1502,   703,   704,  1367,  1366,     0,  1355,  1304,
    1302,     0,     0,  1304,     0,  1351,  1352,  1353,  1317,  1304,
       0,     0,  1304,     0,     0,  1304,  1304,  1304,     0,     0,
    1210,  1444,     0,     0,   743,     0,  1257,  1258,  1259,  1289,
    1260,  1538,  1293,  1298,  1532,  1252,  1300,  1532,  1282,  1262,
    1264,  1256,  1255,  1290,  1261,  1263,  1272,  1273,  1274,  1275,
    1276,  1291,  1254,  1294,  1296,  1277,  1278,  1279,  1280,  1281,
    1266,  1288,  1271,  1268,  1269,  1270,  1267,  1283,  1284,  1285,
    1286,  1287,  1253,     0,     0,  1334,   761,     0,     0,   768,
     789,   790,   783,   785,     0,  1210,  1242,  1244,   802,  1238,
    1239,  1240,     0,  1543,  1203,     0,  1204,   810,  1206,   811,
     808,   809,     0,  1210,  1444,   870,   872,   871,   865,   867,
     873,   876,   851,   863,   859,   857,  1250,   626,   853,  1347,
    1506,   890,  1330,   626,  1538,   916,   917,   919,   921,   922,
     918,   920,   911,  1538,   907,     0,   953,     0,   955,   954,
     956,   947,   948,     0,     0,   933,  1085,  1508,     0,     0,
     967,  1210,  1444,  1542,     0,   994,   627,  1001,  1002,  1005,
       0,   997,  1195,  1194,  1004,  1010,  1189,     0,     0,  1237,
       0,     0,     0,  1045,     0,     0,     0,  1070,     0,  1074,
    1073,  1064,     0,  1488,  1237,  1110,  1109,  1116,  1117,  1118,
       0,  1210,  1444,     0,  1431,     0,  1118,  1185,  1175,  1174,
    1180,     0,  1182,  1183,  1190,  1452,  1433,     0,   198,   199,
     197,  1488,   464,   475,   476,   474,   332,   480,   556,  1488,
     547,   545,   546,   548,  1502,     0,  1488,     0,   559,   551,
    1502,   552,     0,   555,   560,   558,   553,   557,     0,   554,
       0,   542,   570,   565,   568,   567,   566,   569,   544,   571,
       0,   411,   406,  1360,  1361,  1362,  1315,  1303,  1308,  1309,
    1310,  1311,  1314,  1390,     0,  1520,  1538,   309,     0,   697,
    1206,   688,   690,  1203,   694,   684,   724,  1488,   713,   714,
    1488,   725,   715,   716,   719,   729,   726,   717,     0,   727,
     718,   728,   710,   711,   683,  1503,     0,     0,     0,   701,
     702,  1369,  1354,  1368,  1416,  1444,     0,  1420,     0,  1416,
    1416,     0,  1413,  1416,  1416,  1416,     0,  1416,  1416,  1211,
     734,  1213,  1210,   746,     0,  1292,  1533,  1295,  1297,   751,
     749,   756,   757,   601,     0,   767,   766,  1176,  1177,   771,
     769,     0,   788,     0,   793,   626,   626,   803,   801,  1241,
     817,   817,   817,   817,  1488,   822,   835,   836,   823,     0,
    1488,   826,   827,   830,   828,     0,   829,   819,   820,   812,
     818,   626,  1207,  1202,     0,   841,     0,  1250,  1250,   869,
     626,   866,   861,     0,   899,     0,     0,   923,     0,     0,
       0,   949,   951,     0,   943,   959,   944,   945,   938,   939,
     959,  1077,  1488,     0,  1509,  1084,   409,   410,  1493,   968,
     971,     0,     0,   985,   995,   992,   629,     0,     0,  1012,
    1011,  1226,  1228,  1029,  1223,  1224,  1036,  1034,     0,  1250,
    1047,  1250,  1041,  1049,  1062,  1063,  1065,  1440,  1103,  1217,
       0,  1444,  1124,     0,     0,  1432,  1144,  1145,     0,  1148,
    1151,  1155,  1149,  1181,  1506,  1184,  1196,  1456,   195,     0,
     216,   217,   213,     0,     0,   466,     0,  1523,     0,  1488,
     549,   550,     0,   573,  1488,  1536,   574,   572,   405,  1470,
     401,  1493,  1391,   429,   290,  1201,   695,     0,     0,  1246,
    1246,   712,   707,   706,   708,  1409,  1210,  1417,     0,  1429,
    1414,  1407,  1427,  1408,  1410,  1411,  1424,  1425,  1412,  1406,
     626,  1214,  1209,   735,   744,     0,     0,   758,   759,     0,
     763,   762,   764,  1178,  1179,   774,   772,   626,   786,   787,
    1243,  1245,  1203,  1203,  1203,  1203,     0,   824,   825,     0,
    1246,  1246,   821,  1205,   626,  1210,  1318,  1210,  1318,   868,
     874,   864,   892,   900,   902,   909,   912,   913,  1478,   924,
     905,   910,   959,  1372,  1373,   959,     0,   942,   940,   941,
     946,  1087,     0,  1510,  1081,  1210,   984,   978,     0,   628,
    1006,     0,     0,  1018,     0,   626,   626,  1030,  1028,  1225,
    1037,  1032,  1035,  1042,   626,  1051,  1050,  1441,     0,     0,
    1104,  1095,  1218,  1120,  1220,     0,  1210,  1210,  1135,  1431,
    1147,  1486,  1153,  1486,  1217,     0,  1233,  1235,  1199,  1197,
    1230,  1231,  1198,  1457,     0,   214,   463,  1488,     0,   468,
     473,  1502,   509,   529,   524,  1460,     0,     0,  1488,  1504,
    1488,     0,   479,   485,   486,   487,   496,   488,   490,   493,
     481,   482,   483,   489,   492,   510,   494,   497,   484,     0,
     491,   495,  1381,   564,  1379,  1380,   580,   563,   575,   585,
       0,  1488,  1488,   424,   721,   720,   723,     0,   722,   736,
    1418,  1212,   626,  1538,  1538,   760,   775,   753,   626,   770,
     816,   815,   814,   813,   832,   831,   834,   833,  1208,   843,
       0,   842,     0,   626,   903,   897,   914,  1479,     0,   958,
     950,   959,   961,     0,     0,  1090,  1086,  1080,   972,   987,
       0,     0,  1013,  1488,  1020,     0,  1014,     0,  1017,  1227,
    1229,   626,  1048,   626,  1097,  1098,  1099,  1100,  1101,  1102,
     626,  1121,  1112,  1221,  1216,  1119,  1126,  1125,  1146,     0,
    1486,  1150,     0,  1157,  1169,  1166,  1168,  1167,  1162,  1165,
     626,   626,  1200,  1187,  1232,  1193,  1192,  1495,     0,  1488,
    1488,   470,   508,  1488,   530,   528,   525,   526,  1490,   518,
    1488,  1250,     0,     0,     0,     0,   511,     0,     0,   516,
     519,   522,   583,   581,   582,   584,     0,   578,   576,   577,
     579,     0,   415,   412,   413,     0,     0,  1495,  1215,  1299,
    1301,   773,  1210,  1210,   901,     0,   957,   962,     0,  1488,
    1088,     0,     0,  1078,  1082,   986,     0,     0,  1023,  1021,
    1022,  1016,  1015,  1043,  1052,  1219,   626,  1152,     0,  1156,
    1158,  1142,  1234,  1236,  1496,  1497,  1191,   465,     0,     0,
    1488,   461,     0,   517,     0,   514,  1444,   512,   513,   503,
     501,   502,   504,   500,   505,   499,   498,     0,   523,   521,
     520,   562,   561,   414,   408,   430,  1247,   845,   844,   915,
     960,     0,  1091,  1488,  1250,  1019,  1024,  1009,  1222,  1154,
     467,   469,     0,   507,   506,   527,     0,  1089,     0,  1007,
     471,     0,  1092,   515
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
     753,   891,   474,   892,   204,   352,   353,   478,   205,   408,
     409,   206,   207,   208,   209,   210,   211,   212,    47,    77,
      79,   103,   101,   131,   357,   422,   496,   497,   901,   761,
    1100,   498,   897,   499,  1311,  1312,  1578,  1107,   500,   501,
     502,   503,   905,  1103,  1832,   504,   505,   506,   507,   508,
     509,   510,   511,   774,   134,   106,   107,   108,   109,   140,
     110,   358,   359,   425,    30,    65,   143,    83,   221,   148,
     116,   149,   117,   153,   230,   308,   309,   636,   310,  1342,
     829,   524,   311,   441,   312,   642,   313,   314,   637,   821,
     822,   823,   824,   315,   316,   317,    82,   222,   150,   151,
     152,   228,   294,   431,   295,   371,   372,   521,   816,   296,
     520,   612,   613,   614,   938,   615,   616,   617,   618,   619,
     620,   928,  1321,  1621,  1622,  1778,  1850,  2173,  2174,   621,
     622,   806,   623,   624,   625,  1136,   934,   935,  2043,   626,
     627,   114,   285,   147,   364,   226,   428,   516,   517,   518,
     778,   920,   921,  1112,  1113,  1030,   922,  1582,  1835,  1999,
    2141,  2221,  1315,  1585,  1116,  1318,  1837,  2020,  2021,  2236,
    2022,  2023,  2024,  2025,  2227,  2026,  2027,  2028,  2029,  2159,
    2160,  2148,  2030,  2031,  2145,   449,   289,   519,   574,   781,
     782,   783,  1118,  1319,  1618,  2171,  2166,  1619,    50,   237,
     396,    86,   120,   119,   155,   156,   157,   234,   322,   122,
     324,   454,   455,   538,   539,   540,   541,   542,   833,  1525,
    1526,  1786,   543,   699,   700,   834,   954,  1152,  1363,  1364,
    1359,  1662,  1663,  1149,   701,   835,   973,  1175,  1173,   702,
     836,   981,  1394,   703,   837,  1444,   704,   838,  1185,  1446,
    1701,  1702,  1703,  1449,  1709,  1897,  1895,  2058,  2057,   705,
     839,   994,   706,   840,   995,  1452,  1453,   707,   841,   996,
    1191,  1194,   708,   709,   710,   842,  1718,   711,   843,   712,
     844,  1003,  1464,  1737,  1738,  1201,   713,   845,  1007,  1208,
     714,   846,   715,   847,  1012,  1013,  1214,  1215,  1216,  1487,
    1485,  1750,  1217,  1478,  1479,  1749,  1482,   716,   848,  1019,
     717,   849,   718,   850,   719,  1025,  1491,   720,   852,   721,
     854,  1493,  1924,  2073,  2075,   722,   855,  1225,  1502,  1757,
    1926,  1927,  1928,  1930,   723,   856,   724,   857,  1032,  1231,
    1232,  1233,  1514,  1768,  1769,  1234,  1511,  1512,  1513,  1762,
    1235,  1937,  2188,   725,   858,   726,   859,  1039,   727,   860,
    1041,  1240,   728,   861,  1043,  1246,  1524,  1947,   729,   862,
    1046,  1249,  1785,  1047,  1048,  1049,  1528,  1529,   730,   863,
    1538,  1953,  2094,  2198,  2257,   731,   864,   732,   865,  1958,
     733,   866,  1539,  1961,   734,   735,   867,  1060,  2101,  1266,
    1541,  1964,  1802,  1803,  2103,  1264,   736,   868,  1065,  1066,
    1067,  1068,  1278,  1069,  1070,  1071,  1072,   737,   869,  1036,
    1941,  1236,  2087,  1516,  1771,  2085,  2193,   738,   870,  1279,
    1554,  1968,  1971,   739,  1078,  1282,   740,   873,  1080,  1081,
    1809,  2112,   741,   874,  1084,  1288,   742,   876,   743,   877,
     744,   878,   745,   879,  1293,   746,   880,  1295,  1816,  1817,
    1566,  1819,  1982,  2121,  1984,  2211,   747,   748,   882,  2128,
    1092,  1298,  1570,  1710,  1896,  1824,   749,  1572,   750,   751,
     884,  1259,  1826,  2082,  1988,  2133,  1639,  1467,  1468,  1741,
    1743,  1914,  1690,  1691,  1880,  1882,  2052,  1973,  1974,  2110,
    2114,  2206,  1793,  1794,  1955,  1795,  1956,  1989,  1990,  2130,
    1991,  2131,  1458,  1459,  1460,  1715,  1461,  1716,  2046,  1027,
    1028,   983,   984,  1180,  1181,  1425,  1426,  1427,  1428,  1429,
    1126,  1329,  1370,   974,   997,  1195,  1055,  1061,   361,   362,
    1073,  1074,  1222,  1050,   987,   988,   437,   443,  1109,   444,
     258,  1021,  1022,   975,   999,  1129,  1367,  1672,  1770,  1932,
    1005,  1051,  2033,   977,   956,   801,   930,   931,  2035,   978,
     818,   819,   979,  1158,  1160,  1374,  1388,  1383,  1380,   229,
    1818,  1306,  1178,  1257,  1969,   214,  1197,   940,   415,   377,
    1307,   247,  1994,  1747,   386,   220,   631,  1153,   571,   158,
     561,   273,   280,  2078,   136,   282,   830,   531,    42,   420,
     564,  2216,   527,   383,  1666,   944,  1300,  1775,   911,   174,
     513,   798,  1636,   264,   629,   640,   756,   218,  1697,  1224,
    1121,   556,   796,  1465
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1683
static const yytype_int16 yypact[] =
{
   -1683,   352,   366, -1683,   206,   236,   366, -1683, -1683, -1683,
     548,   548,   619,   619, -1683,   708, -1683, -1683, -1683, -1683,
     803,   803,   495,   798,   798,   695,   507, -1683,   896,   885,
   -1683, -1683, -1683, -1683,   -26,   693,   888,   605,   761,   761,
   -1683,   683,   151,   686,   698,   791,   704, -1683,    26,  1073,
     893,  1068, -1683,   468, -1683, -1683,   902, -1683, -1683, -1683,
     763, -1683, -1683, -1683,   864,   778, -1683,    58, -1683,    85,
     548,   619, -1683, -1683, -1683, -1683,   690, -1683,  1053,   434,
     799,   879,  1012,   815, -1683, -1683,   916,   619, -1683, -1683,
   -1683,   808,   811,   819,   822,   835, -1683, -1683, -1683, -1683,
   -1683,   927,   845,  1078,   900,   565, -1683,   283, -1683, -1683,
   -1683, -1683,   852,   952,  1075, -1683,   223,   868, -1683,   116,
     116,   872,   860,   861,   798, -1683,   531,  1132,    13,  1190,
    1037, -1683, -1683,   870, -1683, -1683,   932, -1683, -1683, -1683,
    1299, -1683, -1683, -1683, -1683,   882,   999,  1025, -1683,   815,
   -1683, -1683, -1683, -1683, -1683,    56, -1683,   -93,   439,   105,
   -1683, -1683, -1683, -1683,   986,  1145, -1683,   371, -1683,   429,
   -1683, -1683, -1683, -1683,    89,   328, -1683,   -51, -1683, -1683,
   -1683,   909,   646,  1253,   928,  1145,  1145,   928,   984,  1005,
    1145,  1145,  1145,  1145,  1145,   928,  1145,  1311,  1145, -1683,
     282, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683,   928,   927,   434, -1683,  1285, -1683,
    1200,   223,   868, -1683,   926,  1026,  1032,   868,   553,   948,
     841, -1683,  1145,  1020,  1120, -1683, -1683,  1291,   761,  1145,
    1169, -1683,   585, -1683, -1683,  1046, -1683,  1145,  1197, -1683,
     759, -1683, -1683, -1683, -1683,   958,  1163, -1683, -1683,   928,
     928,  1145,  1145, -1683,  1145,   974,  1348,   928,   928,   974,
    1145,   974, -1683,   928,    16, -1683, -1683, -1683, -1683, -1683,
     815, -1683,   815, -1683, -1683,   868, -1683,   970,  1070, -1683,
   -1683, -1683,   948, -1683,   975,    42, -1683,  1285,  1145,   755,
     755,  1145,    36,  1180,  1145,  1401,  1156, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,   817,   221,
    1145, -1683,   993,   989, -1683,   893,  1169, -1683, -1683, -1683,
   -1683,   974, -1683, -1683, -1683, -1683, -1683,  1145, -1683, -1683,
    1082,   974,  1203,   609, -1683, -1683, -1683, -1683, -1683, -1683,
     974, -1683, -1683,    57, -1683, -1683, -1683, -1683,   815, -1683,
    1144,   815, -1683, -1683,   868, -1683,   992,  1000, -1683, -1683,
    1357, -1683,  1363,  1169,  1017,  1145,  1401,   974,   -29,   -15,
    1169,  1024, -1683,  1145,  1021, -1683,  1021,    -9, -1683, -1683,
   -1683, -1683, -1683,  1169, -1683, -1683, -1683,   324,    50, -1683,
    1140, -1683, -1683, -1683, -1683, -1683, -1683, -1683,  1082, -1683,
    1061, -1683, -1683, -1683, -1683,   974, -1683, -1683, -1683, -1683,
    1169, -1683,   765, -1683,  1169, -1683, -1683, -1683,  1146, -1683,
   -1683, -1683,   467,  1065, -1683, -1683, -1683,   974, -1683, -1683,
   -1683, -1683, -1683, -1683,  1229,    74,  1266,  1033, -1683, -1683,
   -1683,  1145,  1145, -1683, -1683,  2321,   619, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683,   519, -1683,    70, -1683,  1082, -1683,  1169, -1683,
     849,  1180,  1157,  1074, -1683,  1118,  1180,  1145,  1416,   141,
      48,  1169,  1047, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683,  1106, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683,  1145,  1447, -1683,  1021, -1683,  1146, -1683, -1683,
    4572,  1459,  1304,  1169,   103, -1683, -1683, -1683,  1169, -1683,
   -1683,  1126, -1683,    -5,    -5,  2655,  1045,  1052, -1683, -1683,
   -1683, -1683,  1152,  3267,  1058, -1683, -1683,   519, -1683, -1683,
   -1683, -1683,  1127,  1145,  1293, -1683,   111, -1683,  1145,   671,
   -1683,  1145,  1145, -1683,  1145,  1145,  1299,   164,  1145,  1083,
   -1683,  1151, -1683, -1683,   948,  1288, -1683, -1683,   502,   540,
     618,   664,   665,  1086, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683,  1173, -1683,  1169, -1683, -1683, -1683, -1683,
     974,   974,  1308, -1683, -1683, -1683,    44, -1683, -1683, -1683,
    1145,   183, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,   869,    51,
   -1683,    94, -1683, -1683, -1683, -1683, -1683,   139,  1311, -1683,
     663, -1683, -1683, -1683, -1683,  1414, -1683, -1683,  1294, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,  1123,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683,  1074, -1683,  1823,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,   517, -1683,
   -1683,  1224, -1683, -1683, -1683, -1683,   792, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683,  1066, -1683, -1683,  1145,    27,  1145, -1683,
   -1683,   192,   200, -1683, -1683, -1683,   -15,  1155,   974,   974,
   -1683,  1246,  1246,  1254, -1683,   974, -1683, -1683,   113,    42,
   -1683, -1683,   948, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683,  1091, -1683, -1683,  1136,
   -1683,  1084,  1143, -1683, -1683, -1683, -1683,  5046,   108,  1505,
   -1683,  1185,  1185,  1082,  1271,  1271, -1683, -1683,  1088, -1683,
   -1683, -1683, -1683, -1683, -1683,    67,  1372, -1683, -1683,  1065,
    1169,  1099, -1683,  1103,   974,  3610,  1124,    99,  1385, -1683,
   -1683,  4257,   815,  1162,  4334,  4257,  1331,  -136,   721,    82,
     974, -1683, -1683,  1429, -1683,    82,   974,  1985,   974,  3768,
    4257, -1683,  2359,   815,   974,   815,   974,    55,    77,   974,
     815, -1683, -1683,  3843,  3920, -1683, -1683,   974,   974,   815,
     974, -1683,   297,  1460,   974, -1683, -1683, -1683, -1683, -1683,
   -1683,  1547, -1683,   928, -1683, -1683, -1683, -1683,   974,     9,
      90,   120,  1135, -1683,  1135, -1683, -1683, -1683,   625, -1683,
   -1683, -1683, -1683, -1683,   974,  1145,  1402,  1402,   183, -1683,
   -1683, -1683, -1683,  1388, -1683, -1683, -1683,  1169,  1178,  2051,
    1128, -1683,   974, -1683,   108, -1683,  1181,  1346, -1683,  1416,
   -1683, -1683, -1683, -1683,   974,   974,  1082,   -15,   -15,  1546,
    1311, -1683, -1683, -1683,  1475,   552, -1683,  1271,  1134,   974,
    1158,  1159,  1271,   609,  1160,  1164,  1166,  1168,  1172,  1175,
    1177,  1179,  1158,  1476, -1683,  3899, -1683, -1683, -1683, -1683,
    1404, -1683,  1549, -1683, -1683, -1683,  1211, -1683,   609, -1683,
   -1683,  1186, -1683, -1683,   104,   815,  1486,  1079, -1683,  1282,
    1316,   815,   915,  1502,  3520,   923,  1010,  1503,   546,  1186,
   -1683, -1683,    63, -1683, -1683, -1683,  1534, -1683, -1683, -1683,
    1271,    82, -1683, -1683, -1683, -1683, -1683,  1243, -1683,    66,
     974, -1683,    45, -1683, -1683, -1683, -1683, -1683,  4257, -1683,
    1241,  1504,  1589,   699, -1683,  1245, -1683,  2739,  1508,   466,
    1251,  1250,  -132,  1256,   353,  1474, -1683,  1316,  1474,   974,
    1511,  1227, -1683,   701, -1683, -1683, -1683, -1683, -1683,  1415,
   -1683,    82, -1683,   403, -1683,    76, -1683, -1683,   197,  1606,
    3533, -1683, -1683,   974,  1516,  4021,   974,  1485,   853,  1553,
   -1683,  1337,  1292,  1393,  1474,  1066, -1683,    25, -1683, -1683,
   -1683, -1683,   398, -1683, -1683,  1145, -1683, -1683, -1683, -1683,
     104, -1683, -1683,   974, -1683,  1169,   948, -1683, -1683, -1683,
   -1683,  1557,  1271,  2051,  2051,  2051,    38,   745, -1683, -1683,
   -1683,  1088, -1683,  2051, -1683, -1683,  1086, -1683,   108, -1683,
   -1683, -1683, -1683, -1683, -1683,  1229,   -15,  1560, -1683, -1683,
     701,   929,  1240,   261,    72,  2051,  1278,  2051, -1683,  2051,
   -1683,  4392,  1247,  2051,  2051,  2051,  2051,  2051,  2051,  2051,
    2051, -1683, -1683, -1683,  4257,  1492, -1683, -1683,  1345,  1404,
    1523,  2969,  1378,  1452, -1683,   447, -1683, -1683, -1683,   487,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,   450,   815,
   -1683, -1683,   327,  1524,  1524,  1524,  1524, -1683, -1683,  4257,
    4257, -1683, -1683,   150,  1554,   788, -1683,  1257,  -136, -1683,
     974, -1683,    92, -1683, -1683,   595,  1518, -1683,   701,   124,
   -1683,    45, -1683, -1683, -1683, -1683,    97,  1295,    82, -1683,
   -1683,  4257, -1683, -1683, -1683, -1683,  1330, -1683, -1683, -1683,
   -1683,   974,    99, -1683,   775, -1683, -1683,  1316,   104, -1683,
    1484,   400,   235, -1683, -1683,   974,   235,  1296, -1683,  1088,
   -1683, -1683,    75,   849, -1683, -1683,  2064, -1683,  1643,  1480,
    4257,  4257, -1683,  4156,   974, -1683,  1519, -1683, -1683,  4257,
     701, -1683, -1683, -1683,  1606,  1490,   974, -1683,   767, -1683,
      68,   400, -1683, -1683,  1578, -1683, -1683, -1683,  1425, -1683,
   -1683,   974,   974, -1683,   974,  1510,   807,    62, -1683,  4767,
    1393, -1683,  4392,  1255,  1255,   884, -1683, -1683, -1683,  2051,
    2051,  2051,  2051,  2051,  2051,  4917,   745,  1342, -1683, -1683,
    1229,  1393, -1683, -1683, -1683,  1524, -1683, -1683,  1264,  1267,
   -1683,   701,  1524,  1493, -1683, -1683, -1683, -1683,  1057,  1524,
    1443,  1443,  1443,   114,  1481, -1683, -1683,   123, -1683,    87,
     834,   974,   810,   125,  1260, -1683,  1088, -1683, -1683,   271,
    1262,   937,   685,  1263,   969,   127,   128,   794,  1268,  1054,
    4168,   335,  4257,    82, -1683,  1381, -1683, -1683, -1683, -1683,
   -1683,  1074, -1683, -1683,  1325, -1683, -1683,  1325, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683,  1322,    99, -1683,   117,   974,   974,    80,
   -1683, -1683, -1683,    73,   831,  1353, -1683, -1683,  1594, -1683,
    1464, -1683,    34,  1431,  1524,  1462, -1683, -1683,  1467, -1683,
   -1683, -1683,  1543,  4168,   424, -1683, -1683, -1683,  2861, -1683,
    1334, -1683, -1683, -1683, -1683, -1683,   150, -1683, -1683, -1683,
    1393, -1683, -1683, -1683,  1074, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683,  1405,  1074, -1683,  1332, -1683,  1680, -1683, -1683,
   -1683,   557, -1683,   701,   918, -1683,    89,   453,   628,    82,
      82,  4168,   428,  1047,   815,  1596, -1683, -1683,  1722, -1683,
    1558, -1683, -1683, -1683, -1683,  1484, -1683,   974,   478,   450,
     854,  1305,  1613, -1683,  1307,   701,   722, -1683,   123, -1683,
   -1683, -1683,  4257,  1145,   450, -1683, -1683, -1683, -1683,   -65,
     974,  4168,   433,  1343,  1727,   974,   404, -1683, -1683, -1683,
    1440,  1441, -1683, -1683,   775, -1683,   154,   394, -1683, -1683,
   -1683,  1145,  1573, -1683, -1683,  1169, -1683, -1683, -1683,  1145,
   -1683, -1683, -1683, -1683,  1443,  1081,  1145,  1385, -1683, -1683,
    1443, -1683,  1169, -1683, -1683, -1683, -1683, -1683,   974, -1683,
     974, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
     974,  1550,   628, -1683,  1088, -1683, -1683,   834,   781,   781,
    1255,  1255,  1255, -1683,  1110, -1683,  1074, -1683,   974, -1683,
    1467, -1683, -1683,  1524, -1683, -1683, -1683,  1145, -1683, -1683,
    1145, -1683, -1683, -1683, -1683, -1683, -1683, -1683,    12, -1683,
   -1683, -1683,  1057, -1683, -1683, -1683,   104,   104,   104, -1683,
   -1683, -1683, -1683, -1683,  1158,  1282,  5070, -1683,   974,  1158,
    1158,  2051, -1683,  1158,  1158,  1158,   159,  1158,  1158, -1683,
   -1683,  1483,  4168, -1683,    82, -1683, -1683,  1470,  1472, -1683,
   -1683,  3453, -1683,   503,    30, -1683, -1683, -1683, -1683,   981,
   -1683,  1428, -1683,  1423, -1683, -1683, -1683, -1683, -1683, -1683,
      22,    22,    22,    22,  1145, -1683, -1683, -1683, -1683,  1115,
    1145, -1683, -1683, -1683, -1683,    21, -1683,  1431, -1683, -1683,
   -1683, -1683, -1683, -1683,  4257, -1683,  4257,   150, -1683, -1683,
   -1683,  2861, -1683,   974,  1630,  1335,   833,  1654,  1336,   509,
     701, -1683, -1683,  1714, -1683, -1683, -1683, -1683,   918, -1683,
    1597, -1683,  1145,  1494, -1683, -1683, -1683, -1683,  1293,    82,
   -1683,  4257,   164,   388, -1683, -1683, -1683,   974,  4257,   773,
   -1683, -1683, -1683,  1632,  1512, -1683,  1636, -1683,  1537, -1683,
   -1683, -1683, -1683,  1307, -1683, -1683, -1683,  1521,  1638,  1498,
    1488,  1282, -1683,  4257,   509, -1683,  1506, -1683,   701, -1683,
    1672,  1397, -1683, -1683,  1393, -1683,   786,  1776, -1683,   960,
   -1683, -1683, -1683,  1169,  1674,  1575,  1725,  4949,   181,  1145,
   -1683, -1683,   181, -1683,  1145,  1178, -1683, -1683, -1683,  1606,
   -1683,  1293, -1683,  1392, -1683, -1683, -1683,   181,   181,   119,
     119, -1683, -1683, -1683, -1683, -1683,  1353, -1683,  1154, -1683,
   -1683, -1683,   834, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683,  1640,  1641, -1683, -1683,  4257,
   -1683, -1683, -1683, -1683, -1683,  1670, -1683, -1683, -1683, -1683,
   -1683, -1683,  1524,  1524,  1524,  1524,   181, -1683, -1683,   181,
     119,   119, -1683, -1683, -1683,  4168,  1478,  4168,  1482, -1683,
   -1683, -1683, -1683, -1683,  1664, -1683,   833, -1683,  1702, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683,   509,   775, -1683, -1683,
     775,   -70,   974, -1683, -1683,  4168, -1683, -1683,   871,  3319,
   -1683,  1752,  1570,  1591,    -2, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,   974,  1042,
   -1683, -1683, -1683,  1665,  1551,   974,  1353,  4168, -1683,  1727,
   -1683,  1266,  1713,  1266,  1498,   362, -1683, -1683,  1667, -1683,
    1552, -1683, -1683, -1683,   389, -1683, -1683,  1145,  1720,  1598,
   -1683,   832, -1683,  1615,   843,  1401,  1629,  1390,  1145,  1271,
    1145,   974, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683,  1442, -1683, -1683, -1683, -1683,   678,
   -1683, -1683, -1683, -1683, -1683, -1683,   599, -1683,   607, -1683,
    1389,  1145,  1145, -1683, -1683, -1683, -1683,   181, -1683, -1683,
   -1683, -1683, -1683,  1074,  1074, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
    4257, -1683,  4257, -1683, -1683, -1683, -1683, -1683,  1774,   775,
     775, -1683,  1430,  1527,   815,   522, -1683,   974, -1683, -1683,
    1491,  4257, -1683,  1145,   627,  1599, -1683,  1601, -1683, -1683,
   -1683, -1683, -1683, -1683,   974, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,   974,
    1266, -1683,   974,  1686, -1683, -1683, -1683, -1683, -1683,   815,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683,   946,  1169,  1145,
    1145,  1661, -1683,  1145, -1683, -1683, -1683, -1683,   183, -1683,
    1145, -1683,   974,   974,  1072,  1666, -1683,  1555,  1169,   678,
   -1683, -1683, -1683, -1683, -1683, -1683,   181, -1683, -1683, -1683,
   -1683,   181, -1683,  1389, -1683,   974,   108,   946, -1683, -1683,
   -1683, -1683,  1353,  1353, -1683,  4257,   775, -1683,  4257,  1145,
     815,   815,  1540, -1683, -1683, -1683,  1422,   974,  1706, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,   974, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,  1169,  1169,
    1145, -1683,  1169, -1683,  1169, -1683,  1282, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683,  4257, -1683, -1683,
   -1683, -1683, -1683, -1683,   974, -1683, -1683, -1683, -1683, -1683,
   -1683,    99,   815,  1145, -1683,   974, -1683, -1683, -1683, -1683,
   -1683, -1683,  1169, -1683, -1683, -1683,  1794, -1683,    99, -1683,
   -1683,  4257, -1683, -1683
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1683, -1683, -1683, -1683,  1837, -1683, -1683, -1683,    54, -1683,
   -1683, -1683, -1683, -1683,  1525, -1683, -1683, -1683,  1148, -1683,
   -1683,    65,  1825, -1683, -1683,  1791,   270, -1683, -1683, -1683,
   -1683, -1683,  1669,  1721, -1683, -1683,  1681,   641, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683,  1675, -1683, -1683, -1683, -1683,
    1655, -1683, -1683, -1683,   581, -1683, -1683, -1683, -1683,  1386,
   -1683, -1683,  1310,   764, -1683, -1683, -1683, -1683, -1683, -1683,
    1454, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683,  1728, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683,   558, -1683,   554,   770, -1683, -1683,
   -1683, -1683, -1683,   964,    35, -1683,  1312, -1683, -1683, -1683,
   -1683, -1683, -1683,    88, -1683,  1653, -1683,  1765, -1683, -1683,
   -1683, -1683,  1517, -1683,   578, -1683, -1683, -1683, -1683,  1656,
   -1683,  1826,  1731, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683,  1055, -1683, -1683, -1683,  1347, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,   697, -1683,
   -1683, -1683,  1590, -1683,  -516,  -716, -1683, -1683, -1683,  -386,
   -1683, -1683, -1683, -1683, -1683, -1683, -1268, -1260,  1076, -1259,
      49, -1683, -1683, -1683, -1683,   263, -1683, -1683,  -286, -1254,
   -1683, -1683, -1249, -1683, -1246, -1683, -1683,   954, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,  1373,
   -1683, -1683, -1683,   972, -1683,  -867, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683,  -133, -1683, -1683, -1683, -1683, -1683, -1683,
    -267, -1683, -1683, -1683, -1683,  -107, -1683, -1683, -1683, -1683,
   -1683,  1111, -1683, -1683, -1683, -1683, -1683, -1683,   196, -1683,
   -1683, -1683, -1683, -1683,  1775,  1050, -1683,   191, -1683, -1683,
   -1683, -1683,  1444, -1683, -1683, -1683, -1683, -1683, -1683,  -911,
   -1683, -1683,   110, -1683, -1683, -1683, -1683,   895,   537,   541,
   -1683, -1683,   244, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,   898, -1683,
   -1683,   207, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683,  -280, -1683,   172, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683,   692, -1683, -1683,   696, -1683,
   -1683, -1683, -1683,   426,   169, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683,    -8,   702, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
     689, -1683, -1683, -1683,   156, -1683, -1683,   410, -1683, -1683,
   -1683, -1522, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1589,   881, -1683, -1683,   142, -1683, -1683,
     396, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683,   631, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
     667, -1683,   131, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683,   866, -1683,   865, -1683, -1683,  1069,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,   857,
     373, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,   -38,
   -1683,   376, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683, -1683,
   -1683,  -771, -1683, -1134, -1683, -1683, -1150, -1114, -1141, -1683,
     303, -1683, -1412, -1683, -1683, -1683, -1683,   -36, -1683, -1683,
   -1683, -1683,  -148, -1683, -1683,   157, -1683, -1683, -1683, -1683,
     -40, -1683, -1253, -1682, -1683, -1683,   492, -1683,  -951, -1234,
    -815, -1151, -1683, -1683, -1683, -1161, -1157, -1156, -1155, -1145,
     -11,  -212,  -220,  -153, -1047,  -830,   153,   907,  -984,   -83,
   -1683, -1055, -1683,  -780, -1683,   785,  -204,  -256, -1683,  -671,
     -98,  -814,  -973,  -546,  -620, -1683, -1683,   430, -1018, -1567,
    -944,  -799, -1548,   790,  -581,  -231, -1683,  1049,  -233,  -623,
    -479,  -296,   422,  -923, -1683, -1683, -1683, -1683, -1683,  1753,
   -1683,   406,   804, -1683, -1683, -1683, -1628,  1183,   -90,  1684,
     754,  -408, -1683,   980,  -373,  1427, -1683,  -566, -1683, -1042,
    1059,  -371,   574, -1683, -1683,  -654, -1683, -1250,  -163,  -606,
    -486,  -181,  -909,   656, -1309,  -803, -1190, -1683,  1225,  1943,
    -773, -1683, -1683, -1683, -1683, -1683, -1683, -1683,   593, -1683,
     158,  -661,   873,  -127
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1543
static const yytype_int16 yytable[] =
{
     118,   183,   240,   436,   565,   808,   851,   328,   817,   344,
    1086,   998,   945,   349,   512,   351,  1527,  1199,  1274,   800,
    1437,   982,   259,   260,  1438,  1439,  1440,   265,   266,   267,
     268,   269,  1014,   271,   345,   274,  1441,  1283,   345,   991,
     345,  1029,   883,  1714,   410,  1267,  1518,  1866,  1221,  1171,
    1187,  1612,  1667,  1668,  1075,   183,  1221,   986,   779,  1613,
    1614,  1745,  1480,   924,  1059,  1615,   118,   318,   758,   319,
    1616,   825,  1020,  1617,   529,   399,   326,  1571,    21,   417,
    1212,  1020,  1020,  1020,   331,   411,   392,   546,  1020,   261,
    1469,  1470,  1471,   398,   416,   906,  1357,   270,   340,   341,
     345,   342,  1221,   813,   154,   458,  1326,   350,   355,  1780,
     345,    84,   410,  1890,   947, -1542,   277,   813,   279,   345,
    1534,   438,  -182,    88, -1506,   175,  1720,  1390,  1859,   272,
    1620,  2083,  1343,  1506,  1228,   374,    91,  1910,   379,   381,
     433,   384,  1303,   814,  1992,   894,   345,   445,   345,  1812,
     245,  1638,   123,   154,  1154,  1326,   451,   393,   634,  1161,
     453,   338,   339,  1473,   154,   154,  1313,   154,   820,   347,
     348,  1475,   915,   771,   400,   354,   356, -1516,  1360,  1507,
     548,   525,    40,  1976,   477,   936, -1466,   479,   780,    62,
    2095,   514,  1275,  1326,  1521,  1326,  1326,   360,   916,   917,
   -1470,  1490,  1644,  -183,  1640,   417,   345, -1506,   369,  1664,
    1505,  1640,   435,   442,  1303,   976,  1365,  1220,  1640,    87,
     447,    53,  1063,   641,   976,  1008, -1542,  1198,   369,   759,
    2096,   902, -1542,  1098,  1034,    51,  1339,  -182,  1707,  1040,
    1042,   439,  1561,   281,    40,   549,  1314,  1978,  1940,   562,
    2097,   390,  1564,  1082,   976,   419, -1493,  1272,   566,  1010,
     563, -1383,   804,  1011,   820,   418,   779,   827,   811,   522,
     232,  1303,  1563,   760,  1064,   360,  1144,  1145,   426,   450,
    1883,    17, -1542,   401,  1260,  1839,  1796,  1261,   533,   534,
     633,  1844,  1508,   184,  2037,   638,   985,   401,  1004,  1221,
    1753,  1808,   643,   643,   899,  1090,   185,   186, -1542,  2044,
    2045,   936,  1115,   815,  1536,   233,   929,  1064,  -183,  1322,
     985,    40,   402,  1301,   559,  1360,   391,   985,  1085,   403,
    1721,  1091,  1186,  1643,   895,  1480,   402,   248,   187,  1326,
      90,  1509,   440,   403,   998,  1692,  1891, -1470,  1099,   569,
    1739,  1671,     3,   563,  2084,  1176, -1466,   628,  2064,   903,
    1708,  2065,   799,  1141,  1142,   567,   179,  1229,  1299,  2081,
     802,    63, -1470,  1366,   188,   189,  1876,   190,  1280,  1455,
     998,   805,   896,  1146,  1176,   191,    62,     5,  -594,  1327,
     757,   418,  1105, -1482,   251,   762,   780,   918,   766,   767,
     404,   768,   769,  1014,  1704,   775,  1362,  1723,   572,   327,
    2079,   998,  2200,  2080,   404,   635,   772,   343,  1237,   -31,
    1693, -1470,    64,   452,  1520,  2098,  1860,   343,   192,   193,
    1230,  1637, -1470, -1470,   325,  1911,   904,  -592,  1327,   194,
    1827,  -182,  1492,   246,   179,   166,  2137,   807,   257,   327,
    1131,    88,   812,  1463,  2049,  1892,  1304,  -200,   456,   998,
    1082,   547, -1488,   405,    54,  1176,  1722,   948,   528,  1546,
    1276,  1106,  1531,   773,   370,  1340,  1327,   405,  1327,  1327,
   -1493, -1470,    85,   459,  1535,  1328,  1361,   343,   900,   257,
    1277,  1213,   406,  1856,  1586,  1763, -1516,   179,   343,  2177,
     343,  -594,  1640,  2069,   343,  2071,   406,   343,   343,   343,
     826,   195,   908,   909,   343,  1338,  -738,   942,   813,   914,
    1573,   544,  -183,  2124,   343,  1510,   104,  1804,  1304,  1281,
   -1470,   343,   407,  2088,  1674,   345,   343,   345,   345, -1466,
    1783, -1470, -1470,     4,   345,  1476,   407,  1221,    55,  1477,
    -592, -1470,   343,  1362,  1391,   343,   249, -1470,   919,  2186,
    1877,  1442,   998,  2125,  2116,  2117,  1506,  1965,    63,  2013,
     179,  2126, -1422,  1368,  1684,  1685,  1752,  2014,  2015,  1147,
    1375,  1150,  1754,  2017,  1269,  1304,   343, -1542,  2018,  1472,
    1474,  2019, -1513,   893,  1209,   898,  1480,   951,  2265,  1791,
    1317,  1587,    31,  1255,  1494,  1746,   989,  1495,   164,  1781,
    1496,  1497,  1507,   343,  1813,   923, -1466,   327,  2241,  2032,
   -1542,  1522,  1327,  2242,   105,   196,     5,  1037,  1447,  1064,
    1308,  1052, -1542,  1056,  1985,  1056,  1062,  1829,  1037,  1489,
   -1542,  2127,  1097,  1064,  1131,  1131,  1131,  1773,  1256, -1488,
    1143,    12, -1542,  1056,  1131,  1776,  1551,  1456,  1108,  1704,
    1555,  1556,  2267,  1558,  1700,   197,   164,   345,     5,  1562,
    1101,  1269,    74,  2135,  1196,    40,  1131,   104,  1131,  2272,
    1131,    13,  1376,   345,  1131,  1131,  1131,  1131,  1131,  1131,
    1131,  1131,  2143,    15,  1119, -1542,  1542,  1915,   401,  1917,
    1542,  1135,   163,  2191,  1830,  1779,  1831,  1457,   462,  1127,
    1330,  1331,  1332,  1333,   198,  1334,   345,   345, -1428, -1542,
     165,  1884,  1862,  1863,  1864,  1508,  1151,   275,   141,  1774,
      74,  2119,  1792,  2122,  1945,  1053,  1309,   402,  1777, -1542,
    1695,  1623,  1935,  1462,   403,   871,  -952,   463,  1791,  1269,
    1210,  1865,  1110,  1326,   464,   235,  1870,  1871,  1463,  1000,
    1873,  1874,  1875,  1196,  1878,  1879,  1977,  1196,   164,   481,
    2247,  2248,  1196,  1888,  1509,   105,  1128, -1466,   165,  1448,
    1054,    54,  1057,  1532,   482,  -952,  1673,  1077,  2060,  2061,
    2062,  2063,  -952,   483,   115,  1096,  1088,  1273,  1843,  1711,
    1980,  2192,  1450,   413,  1900,  1901,  1221,  2040,  2105,  1533,
     244,  1269,  2106,  2107,  2108,   404,   241,  2047,  2047,   179,
     115,   343,   164,    22,  2109,   466,   245,  2032,  1062,    25,
    1913,   179,    74,  1755,  1456,   179,   343,   828,  2162,  1921,
    1498,  1499,  1758,  1624, -1466,  1495,  2167,    18,  1496,  1497,
    1131,  1131,  1131,  1131,  1131,  1131,  1131,   872,  1500,  1501,
    1242,   785,  1326,  -952,   236,    55,   232,   484,  2047,  2047,
    2208,   373,  1269,  1162,   243,   137,   380,   414,   405,  1250,
     165,  1792,  1316,   244,  1457, -1513,    74,   297,   467,  2163,
     401, -1484,  1251,  1451, -1482,    29,   485,  2168,  1183,   787,
    1243,   298,  1226,  1323,  1324,  1325,   327,   406,  1244,  2048,
     786,   233,  1189,  1336,  1916,   345,  1918,  2225,   179,   284,
    1053,  1568,    19,    32,   290,  1569,  -952,  1764,  2157,   402,
     138,   139,  1806,  1920,   165,  1986,   403,  1372,   299,  2136,
      28,   343,  1310,  1379,  1381,  1382,  1384,   407,   788,  1387,
    1389,   998,    33,  1344,  1345,  -952,    92,   470,  1510,  2066,
    2067,   484,   281,   166,   333, -1542,  1952,  1673,  2158,  2051,
    1128,  1128,  1128,  1765,   881,  1853,    35,   789,  1245,   388,
    1128,   763,   363,   998,  1963, -1430,  2059,   334,   764,  -952,
     485,   989,  1105,  1456,  1346,  -952,  1347,   486,   291,   389,
      37,  2129,  1128,  2068,  1128, -1542,  1128,   404,  1015,  1016,
    1128,  1128,  1128,  1128,  1128,  1128,  1128,  1128,    93,  1058,
    2269,   989,  1017,   791,   793, -1542,   790,  1348,  1349,  1350,
     329,   809,  1583,  1584,  1269,  1269,  1327,  1094,  2164,  2165,
      43,  1987,   487,  1457,  2099,  2100,  2169,  2170,   488,    40,
      48,   810,    44,  2102,   300,  1579,  1579,  -200,    94,    49,
      95,   427,  1454,  1712,   301,   375,  1269,   376,  1018,   989,
     405,  1106,   792,   794,  1351,   489,  1352,   179,  1498,  1499,
     345,   345,   490,  1713,  1353,   957,  1797,  1646,   813,  1647,
      45,   254,  1648,  1665,  2142,   491,  1500,  1501,    46,   406,
    2190,  2104,  1649,  2089,  2146,  2147,  1798,   401,  1772,  1627,
    1628,  1629,  1630,  1631,  1632,  1634,   426,  1549,   550,   246,
     551,  1550,   492,  2090,  1330,  1331,  1332,  1333,    52,  1334,
     493,    58, -1426,   343,  1540,  1766,  1934,   553,    60,   407,
    -205,  2178,   558,    59,  1369,  1327,   402,  2181,  1373,    61,
      10,   302,   303,   403,    10,  1354,  1385,  1386,   958,  2229,
    2230,   494,  2184,  1291,   304,  1292,   305,  1678,  1951,  1064,
    1681,  2214,  2215,   960,  1540,  1686,  1128,  1128,  1128,  1128,
    1128,  1128,  1128,  2231,  1330,  1331,  1332,  1333,    67,  1334,
    2203,  1934,  2204,  1401,  1402,     5,  1335,  1131,    71,  2205,
   -1542,   184,  1131,    74,   179,   231,  2153,  2252,    78,   231,
     495,    80,    81,   989,   185,   186,  1213,   102,  1483,  2212,
    2213,  1403,  1332,  1333,   404,  1334,   112,  1404,  1650,  1840,
    1192,  1841,  1651,  1330,  1331,  1332,  1333,  1893,  1334,  1894,
    2182, -1423,  2183,   113,   111,  1652,   187,   115,   121,  1330,
    1331,  1332,  1333,   125,  1334,   885,   126,   961,  1406,   461,
     993,  1676,  1407,  1907,   127,  1908,   306,   128,   401,  2055,
    1830,   401,  1831,  1330,  1331,  1332,  1333,   130,  1334,  1035,
     129,  1269,   188,   189,   993,   190,   307,   405,   133,  1269,
     132,  1653,  1944,   191,   886,  2258,   135,   144,   962,   145,
    -321,   887,   146,   963,   160,   161,   162,   402,   175,   964,
     402,   213,   965,  1934,   403,   216,   406,   403,   217,  1767,
    1579,  1355,   219,  1330,  1331,  1332,  1333,   223,  1334,   462,
    2255,  1626, -1375, -1375, -1375, -1375,   192,   193,  1654,  1269,
    1203,  1204,  1205,  1206,   966,   345,   224,   194,   225,   239,
     343,  1132,  1836,    40,   253,   256,   407,  2232,  2233,   262,
     257,  1356,  1655,   263,  1848,  2041,   272,   279,   463,  1845,
     281,   286,   888,   287,   288,   464,  1330,  1331,  1332,  1333,
     293,  1334,  1854,   320,  1680,   404,  1656,   465,   404,   345,
    1807,  1657,  2179,  2180,   321,   323,  1782,   327,  2234,  2235,
     330,  1658,   332,   335,   336,  1659,   343,   345,  1330,  1331,
    1332,  1333,   967,  1334,   346,   365,  1683,   366,  1833,   195,
     368,   382,  1869,   385,   387,   394,  1838, -1374, -1374, -1374,
   -1374,   412,  1810,  1842,   395,   889,   424,   429,  -333,  1810,
    1902,  1903,  1904,  1905,   432,   430,   466,   345,   405,   434,
     446,   405,   476,   448,   515,   526,  1868,   968,   969,   523,
     530,  1872,  1660,  1724,   958,   532,  1725,   554,   555,   993,
     560,  2196,  1661,   557,  1726,  1727,  1728,   406,   179,   960,
     406,   568,   970,   570,  1857,   630,   632,  1858,  1421,   639,
     646,  1423,  1424,  1330,  1331,  1332,  1333,   647,  1334,   648,
     971,  1688,   755,   752,   890,   563,   777,   784,   972,   467,
     797,   343,   468,   469,   795,   776,   803,   407,   831,  -804,
     407,   875,   832,  1128,   910,  1193,   913,   907,  1128,   926,
     927,   937,   929,   196,   932,  1396,  1397,  1398,   939,   943,
     946,   949,  2223,  1399,   952,  1132,  1132,  1132,   953,  1330,
    1331,  1332,  1333,  2245,  1334,  1132,   980,  1852,  1001,  1009,
    1026,  1906,  1093,   961,  1095,  2249,  1102,  1909,  2250,  1111,
    1117,  1120,  1138,   197,  1139,   820,  1133,  1132,   470,  1132,
    1400,  1132,  1155,  1377,  1729,  1132,  1132,  1132,  1132,  1132,
    1132,  1132,  1132,  1330,  1331,  1332,  1333,  1148,  1334,  1172,
    1996,  2050,  1730,  1177,  1179,  1182,  1157,  1159,  1163,  1942,
    1184,  1190,  1164,   990,  1165,   964,  1166,  2266,   965,  1731,
    1167,  1196,   198,  1168,   955,  1169,   763,  1170,   992,  1200,
    1219,  1207,  2149,  1223,  1006,  1238,  1239,  1241, -1377,  1023,
    1024,  1248,  1252,  1253,  1254,  1023,  1031,  1033,  1258,  1263,
     966,  2273,   992,  1265,   154,  1064,  1948,  1287,  1023,  1290,
    1294,  1296,  1954,  1297,  1299,  1732,  1320,  1031,  1087,  1341,
    1089,  1358,  1371,  1392,  1401,  1402,  2036,  1393,  1443,  1378,
     985,  2038,  1466,  1481,  1504,  1486,  2086,  1523,  1537,  1519,
    1545,  1552,  1553,  1560,  1565,  1575,  1577,  1581,  1635,  1334,
     426,  1641,  1403,  1642,  1665,  1645,  1361,  1677,  1404,  1679,
    1682,   345,  1733,  1694,  1696,  1687,  1699,  1689,   967,  1130,
    1717,  1457,  1740,  1742,  1744,  1748,  1759,  1756,  1760,  1784,
    1787,  1405,  1788,  1799,  1800,  1801,  1815,  1814,  1823,  1406,
    1825,  1834,  1881,  1407,  1625,  1885,  1849,  1886,  1898,  1156,
    1923,  1132,  1132,  1132,  1132,  1132,  1132,  1132,  1899,  1929,
    1925,  1931,  1936,   968,   969,  1734,  1792,  1939,  1957,  1962,
    1943,  1408,  1409,  1960,  1967,  1735,  1410,  1970,  1972,  1975,
    1981,  1979,  1983,  1993,  1188,  1997,  1411,  2042,   970,  1998,
    2000,  2053,  2054,  1412,  2056,  2074,  2161,  2070,  1413,  2077,
    2091,  2072,  2092,  2093,  2120,  2111,   971,  1987,  2139,  2113,
    2132,  1023,  2144,  2140,   972,  2150,  1414,   343,  2151,  1023,
    1227,  2172,  2185,  2009,   853,  2189,  2195,  2187,  2210,  -895,
    2220,  2201,  -895,  2202,  2138,  2254,  1736,   992,  2253,  2238,
    2237,  2256,  2271,    14,    73,  2152,    27,  2154,   242,   182,
     397,   255,   252,  1268,  1547,   276,  2194,   754,   545,  1302,
     215,  1023,   475,  1576,  1995,  1023,  1580,  1305,  1104,   278,
    1946,   765,   142,  1286,    66,   423,  1227,   283,  2175,  2176,
     227,   644,   367,   933,   950,  1851,  2016,  2243,  1137,  1114,
     573,  2156,  2240,   925,  1889,   159,  1949,  2228,   535,  1202,
    1188,  1670,  -895,  1031,  1669,  2217,  1861,  1211,  1887,  1912,
    1488,  1484,  1751,  1130,  1130,  1130,  1919,  -895,  2076,   438,
    1515,  1761,   345,  1130,  1938,  2239,  2161,  1503,  1247,  1950,
    2197,  1789,  1574,  1544,  1966,  1270,  1271,  1285,  1076,  1821,
    1268,  2118,  1822,  1855,   345,  1130,  2199,  1130,  2123,  1130,
    2134,  1959,  1719,  1130,  1130,  1130,  1130,  1130,  1130,  1130,
    1130,  1415,  1416,  1417,  1418,  1419,  1262,  1420,  1445,  1421,
    1422,  2244,  1423,  1424,  -895,  -895,  2218,  2219,  1805,  1134,
    2222,   292,  1828,  1395,   378,  2260,  2261,  2224,   525,  2263,
    1517,  2264,  1218,   770,   813,   941,  2246,   912,  1140,    75,
    1698,  -895,  -895,  2039,     0,     0,     0,     0,  -895,  1337,
       0,     0,  -895,   345,     0,     0,     0,     0,  1268,   993,
     989,     0,     0,     0,     0,     0,  2251,     0,  1023,  2270,
       0,  -895,     0,     0,     0,     0,     0,   989,     0,  -895,
       0,  1530,  -895,  -895,     0,     0,   426,  -895,  1188,     0,
       0,  -895,     0,  -895,     0,  1543,  -895,  2262,  -895,     0,
       0,     0,  1023,     0,   958,     0,     0,     0,     0,     0,
     957,  -895,     0,   813,  1559,     0,  -895,     0,     0,   960,
    1268,     0,     0,     0,     0,     0,  1567,     0,  -895,     0,
    2268,     0,     0,     0,     0,     0,     0,     0,  1132,     0,
       0,     0,     0,  1132,  1227,     0,     0,   426,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1130,
    1130,  1130,  1130,  1130,  1130,  1130,     0,     0,     0,  -895,
     958,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1268,     0,   958,     0,   960,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -895,     0,   960,     0,
       0,  1675,     0,   961,     0,     0,     0,     0,     0,   426,
       0,     0,     0,     0,   401,     0,     0,     0,     0,     0,
       0,     0,     0,  1023,     0,     0,     0,     0,     0,     0,
       0,     0,  -895,     0,     0,     0,     0,     0,     0,     0,
       0,  -895,  -895,     0,     0,     0,     0,     0,  1548,     0,
       0,     0,     0,   402,     0,   964,     0,     0,   965,     0,
     403,  -895,     0,     0,     0,     0,  -895,     0,     0,   961,
       0,     0,     0,     0,     0,     0,     0,  1705,  1706,     0,
     401,     0,   961,     0,  -895,     0,     0,     0,     0,     0,
     966,     0,  -895,   401,     0,  -895,     0,     0,     0,     0,
       0,  -895,  -895,  -895,     0,     0,     0,  -895,     0,  -895,
    1122,  -895,  -895,  -895,     0,   963,     0,     0,     0,   402,
       0,   964,     0,   962,   965,     0,   403,     0,   963,     0,
       0,   404,   402,     0,   964,     0,     0,   965,     0,   403,
       0,     0,     0,  1268,  1268,     0,     0,     0,     0,  1023,
    1023,     0,     0,     0,     0,     0,   966,     0,   967,     0,
       0,  -589,   536,     0,  -629,     0,  -629,  1790,     0,   966,
       0,  -629,     0,     0,     0,  1268,     0,     0,     0,  -629,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1811,     0,     0,     0,   405,  1820,  1820,   404,     0,     0,
       0,     0,     0,   968,   969,     0,     0,     0,     0,     0,
     404,  -629,  -629,     0,     0,     0,     0,     0,     0,  -629,
       0,     0,     0,   406,   967,     0,     0,   992,   970,     0,
    -629,     0,     0,  -629,     0,     0,     0,   967,  1846,     0,
    1847,     0,     0,     0,     0,  -629,   971,     0,     0,     0,
       0,     0,     0,     0,   972,     0,     0,   343,     0,     0,
     405,     0,     0,   407,     0,     0,     0,  -629,     0,   968,
     969,     0,     0,   405,  -629,  -629,     0,     0,   958,     0,
       0,     0,   968,   969,     0,     0,     0,     0,     0,   406,
       0,  -589,     0,   960,   970,  -589,  1188,  1188,  1188,  1549,
       0,     0,   406,  1550,     0,  -629,  1130,   970,     0,     0,
       0,  1130,   971,     0,     0,     0,     0,  -629,     0,     0,
     972,  -629,     0,   343,  1023,   971,     0,     0,     0,   407,
    1123,  1124,     0,   972,  -629,     0,   343,     0,  -589,  1125,
       0,  -629,   407,     0,  -629,  -629,     0,     0,     0,     0,
       0,     0,  -629,     0,     0,     0,     0,     0,     0,  -629,
       0,  -629,     0,     0,  -629,     0,     0,     0,     0,     0,
       0,  1044,     0,     0,     0,     0,     0,   961,     0,     0,
       0,     0,     0,  1922,     0,     0,     0,     0,     0,  1933,
    1268,     0,     0,     0,     0,     0,     0,     0,  1268,  -629,
       0,     0,     0,  -629,     0,  -629,     0,     0,     0,  1023,
       0,     0,  -629,     0,     0,     0,     0,  1530,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1045,     0,   964,
       0,     0,   965,     0,  -629,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1933,     0,     0,     0,  1268,  -629,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -589,   966,     0,     0,     0,  2034,     0,
    -629,     0,  2034,     0,     0,     0,     0,     0,     0,  -629,
       0,     0,     0,     0,     0,     0,     0,  2034,  2034,     0,
       0,     0,  -629,     0,     0,     0,   536,  -629,  -629,  -629,
    -629,     0,     0,     0,     0,  -629,     0,  -629,     0,     0,
       0,     0,     0,  -629,     0,     0,     0,  -629,     0,     0,
       0,     0,     0,     0,     0,     0,  -629,     0,     0,     0,
       0,     0,   967,     0,     0,  -629,  2034,  -629,  -629,  2034,
       0,  -629,     0,  -629,     0,  -629,  -629,     0,  -629,     0,
       0,     0,     0,  -629,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -629,  -629,     0,  1933,  -629,  -629,     0,
       0,     0,     0,  -629,     0,     0,     0,   968,   969,  -629,
       0,     0,     0,     0,  -629,     0,     0, -1542,     0,     0,
       0,     0,     0,   537,     0,     0,  -629,     0,  1031,     0,
       0,  -629,   970,     0,     0,  2115,  -629,     0,  -629,  -629,
       0,     0, -1003,     0,     0,     0,   645,     0,     0,     0,
     971,     0,     0,     0,  2034, -1003,     0,     0,   972,     0,
     179,   343,     0,     0,     0,     0,     0,     0,     0,  -629,
       0,  2155,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -629,     0,     0,     0,  -629,     0,     0,   958,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -629,     0,
       0,     0,     0,   960,     0,  -629,     0,  2034,  -629,  -629,
       0,     0,     0,     0,     0,     0,  -629,     0,     0,     0,
       0,     0,     0,  -629,     0,  -629,     0,     0,  -629,     0,
       0,     0,     0,     0,     0,     0,     0, -1458,     0,     0,
   -1458,     0,     0,     0,     0,     0,     0,     0,  1212,     0,
       0,     0, -1458,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -629,  1227,     0,     0,  -629,     0,  -629,
       0,     0,     0,     0,     0,     0,  -629,     0,     0,  2207,
       0,  1044,  2209,     0,     0,     0,     0,   961,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -629,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   -1458,     0,  2226,  -629,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0, -1458,  2034,     0,     0,     0,
       0,  2034,     0,     0,  -629,     0,     0,   990,     0,   964,
       0,     0,   965,  -629,     0,   957,     0,     0,   813,     0,
       0,     0,     0,     0,     0,     0,  -629,  1031,     0,     0,
       0,  -629,     0,  -629,     0,     0,     0,     0,  2259,     0,
       0,  -629,     0,     0,   966,     0,     0,     0,     0,     0,
       0,  -629, -1458, -1458,     0,     0,     0,     0,     0,     0,
    -629,     0,     0,     0,     0,     0,     0,     0,     0,  -629,
       0,  -629,  -629,     0,     0,  -629,     0,  -629,     0, -1458,
   -1458,     0,  -629,     0,     0,  1227, -1458,     0,   958,     0,
   -1458,     0,     0,     0,     0,     0,     0,  -629,     0,     0,
       0,     0,  -629,   960,     0,     0,     0,  -629,     0, -1458,
       0,     0,   967,     0,     0,     0,     0, -1458,  -629,     0,
   -1458, -1458,     0,     0,     0, -1458,     0,   537,     0, -1458,
    -629, -1458,     0,     0, -1458,     0, -1458,     0,     0,     0,
    -629,     0,     0,     0,     0,     0,     0,     0,     0, -1458,
       0,     0,     0,     0, -1458,     0,     0,   968,   969,     0,
    1401,  1402,     0,     0,     0,     0, -1458, -1542,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   970,     0,     0,     0,     0,   961,  1403,     0,
       0,     0, -1003,     0,  1404,     0,     0,     0,   401,     0,
     971,     0,     0,     0,     0, -1003,     0, -1458,   972,     0,
     179,   343,     0,     0,     0,     0,     0,  1430,     0,     0,
       0,     0,     0,     0,     0,  1406,     0,     0,   962,  1407,
       0,     0,     0,   963, -1458,     0,     0,   402,     0,   964,
       0,     0,   965,     0,   403,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1431,     0,     0,
       0,     0,  1432,     0,     0,     0,     0,     0,     0,     0,
   -1458,     0,     0,     0,   966,     0,     0,     0,     0, -1458,
   -1458,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0, -1458,     0,     0, -1458,
   -1458,     0,     0,     0, -1458,     0,     0,     0,     0,     0,
     649,     0,   650,     0,     0,   404,     0,   651,     0,     0,
       0,     0, -1458,     0,     0,   652,     0,     0,     0,     0,
   -1458,     0,     0, -1458,     0,     0,     0,     0,     0, -1458,
   -1458, -1458,   967,     0,     0, -1458,     0, -1458,     0, -1458,
   -1458, -1458,     0,     0,     0,     0,     0,   653,   654,     0,
       0,     0,   649,     0,   650,   655,     0,     0,     0,   651,
       0,     0,     0,     0,     0,     0,   656,   652,   405,   657,
       0,     0,     0,     0,     0,     0,     0,   968,   969,     0,
       0,   658,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   406,     0,   653,
     654,     0,   970,   659,     0,     0,     0,   655,     0,     0,
     660,   661,     0,     0,     0,     0,     0,     0,   656,     0,
     971,   657,     0,     0,     0,     0,     0,     0,   972,     0,
       0,   343,     0,   658,     0,     0,     0,   407,  1433,  1434,
       0,   662,     0,  1435,     0,  1421,     0,  1436,  1423,  1424,
       0,     0,     0,   663,     0,   659,     0,   664,     0,     0,
       0,     0,   660,   661,     0,     0,     0,     0,     0,     0,
     665,     0,     0,     0,     0,     0,     0,   666,     0,     0,
     667,   668,     0,     0,     0,     0,     0,     0,   669,  -761,
       0,     0,  -761,   662,     0,   670,     0,   671,     0,     0,
     672,     0,     0,     0,     0,   663,     0,     0,     0,   664,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   665,     0,     0,     0,     0,     0,     0,   666,
       0,   154,   667,   668,     0,   673,     0,     0,     0,   674,
     669,   675,     0,     0,     0,     0,     0,   670,   676,   671,
       0,     0,   672,     0,     0,     0,   957,     0,     0,   813,
       0,     0,  -761,     0,     0,     0, -1470,     0,     0,   957,
     677,     0,   813,     0,     0,     0,     0,  -761,     0,  1150,
       0,     0,     0,     0,     0,   678,     0,   673,     0,     0,
       0,   674,     0,   675,     0,     0,     0,     0,     0,     0,
     676,     0,     0,     0,     0,     0,   679,     0,     0,     0,
       0,     0,     0,     0, -1466,   680,     0,     0,     0,     0,
       0,     0,   677,     0,     0,     0,     0,     0,   681,   958,
       0,     0,     0,   682,     0,   683,     0,   678,     0,     0,
       0,     0,   958,   684,   960,     0,   957,     0,     0,   813,
       0,     0,     0,   685,     0,     0,     0,   960,   679,     0,
       0,  -761,   686,     0,     0,     0,     0,   680,     0,     0,
    1079,   687,  -761,   688,   689,     0,     0,   690,     0,   691,
     681,     0,     0,     0,   692,   682,     0,   683,     0,     0,
       0,     0,     0,     0,     0,   684,     0,     0,     0,   693,
       0,     0,  -761,     0,   694,   685,     0,  -761,     0,   695,
       0,  -761,     0,  -761,   686,     0,  -761,     0,  -761,   958,
     696,     0,     0,   687,     0,   688,   689,     0,   961,   690,
     959,   691,   697,     0,   960,     0,   692,     0,     0,   401,
       0,   961,   698,     0,     0,     0,     0,     0,  -761,     0,
       0,   693,   401,  -761,     0,     0,   694,     0,     0,     0,
       0,   695,     0,     0,     0,     0,     0,  1284,     0,   962,
       0,     0,   696,     0,   963, -1466,     0,     0,   402,     0,
     964,     0,   962,   965,   697,   403,     0,   963,     0,  -761,
       0,   402,     0,   964,     0,     0,   965,     0,   403, -1470,
       0,     0,     0,     0,   957,     0,     0,   813,     0,     0,
       0,     0,     0,     0,     0,   966,  -761,     0,   961,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   966,   401,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0, -1466,     0,     0,     0,  -761,     0,     0,     0,
       0,     0,  -761,     0,     0,     0,   404,     0,     0,   962,
       0,  -761,  -761,     0,   963,     0,     0,     0,   402,   404,
     964,     0,     0,   965,     0,   403,     0,   958,     0,   957,
       0,  -761,   813,   967,     0,     0,  -761,     0,  1038,     0,
       0,  -761,   960,     0,     0,     0,   967,     0,     0,     0,
       0,     0,     0,     0,  -761,   966,     0,     0, -1470,     0,
       0,     0,  -761,     0,     0,  -761,     0,     0,     0,   405,
       0,  -761,     0,     0,     0,     0,     0,     0,   968,   969,
       0,     0,   405,     0,     0,   957,     0,     0,   813,     0,
       0,   968,   969,     0,     0,     0,   404,     0,   406,     0,
       0,     0,   958,   970,     0,     0,   957,     0,     0,   813,
       0,   406,     0,     0,     0,     0,   970,   960,     0,     0,
       0,   971,     0,   967,     0,     0,   961,     0,     0,   972,
    1079,     0,   343,     0,   971,     0,     0,   401,   407,     0,
       0,     0,   972,     0,     0,   343,     0,     0,     0,     0,
       0,   407,     0,     0,     0,     0,     0,     0,   958,   405,
       0,     0,     0,     0,     0,     0,     0,   962,   968,   969,
       0,     0,   963,   960,     0,     0,   402,     0,   964,   958,
       0,   965,     0,   403,     0,     0,     0,     0,   406,     0,
    1083,     0,     0,   970,   960,     0,     0,     0,     0,     0,
       0,   961,     0,     0,     0,     0,     0,   957,     0,     0,
     813,   971,   401,   966,     0,     0,     0,     0,     0,   972,
       0,     0,   343,     0,     0,     0,     0,     0,   407,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   962,     0,     0,     0,     0,   963,     0,     0,
       0,   402,     0,   964,   404,     0,   965,   961,   403,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   401,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   961,     0,
     958,   967,     0,     0,     0,     0,     0,     0,   966,   401,
       0,     0,     0,     0,     0,   960,     0,     0,   962,     0,
       0,     0,     0,   963,     0,     0,     0,   402,     0,   964,
       0,     0,   965,     0,   403,     0,     0,   405,     0,   962,
       0,     0,     0,     0,   963,     0,   968,   969,   402,   404,
     964,     0,     0,   965,     0,   403,     0,     0,     0,     0,
       0,     0,   957,     0,   966,   813,   406,     0,     0,     0,
       0,   970,     0,     0,   957,     0,   967,   813,     0,     0,
       0,     0,     0,     0,     0,   966,     0,     0,     0,   971,
       0,     0,     0,     0,     0,  1289,     0,   972,     0,   961,
     343,     0,     0,     0,     0,   404,   407,     0,     0,     0,
     401,     0,   405,     0,     0,     0,     0,     0,     0,     0,
       0,   968,   969,     0,     0,     0,   404,     0,     0,     0,
       0,     0,   967,     0,     0,   958,     0,     0,     0,     0,
     962,   406,     0,     0,     0,   963,   970,   958,     0,   402,
     960,   964,     0,   967,   965,     0,   403,     0,     0,     0,
       0,     0,   960,   957,   971,     0,   813,     0,   405,     0,
       0,     0,   972,     0,     0,   343,     0,   968,   969,     0,
       0,   407,     0,     0,     0,     0,   966,     0,     0,   405,
       0,     0,     0,  1174,     0,     0,     0,   406,   968,   969,
       0,     0,   970,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   406,     0,
     971,     0,     0,   970,     0,     0,     0,   404,   972,     0,
       0,   343,     0,     0,   961,     0,   958,   407,     0,     0,
     957,   971,     0,   813,     0,   401,   961,     0,     0,   972,
       0,   960,   343,     0,   967,     0,     0,   401,   407,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   962,     0,     0,     0,     0,
     963,     0,     0,     0,   402,     0,   964,   962,     0,   965,
     405,   403,   963,     0,     0,     0,   402,     0,   964,   968,
     969,   965,     0,   403,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   958,     0,     0,     0,     0,     0,   406,
       0,   966,     0,     0,   970,     0,     0,     0,   960,     0,
       0,     0,     0,   966,     0,   961,     0,     0,     0,     0,
       0,     0,   971,     0,     0,     0,   401,     0,     0,     0,
     972,     0,     0,   343,     0,     0,     0,     0,     0,   407,
       0,     0,   404,     0,     0,     0,     0,     0,     0,     0,
       0,   958,     0,     0,   404,     0,   962,     0,     0,     0,
       0,   963,     0,     0,     0,   402,   960,   964,     0,   967,
     965,     0,   403,     0,     0,     0,     0,     0,     0,     0,
       0,   967,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   961,     0,     0,     0,     0,     0,     0,  1557,
       0,     0,   966,   401,     0,   405,     0,     0,     0,     0,
       0,     0,  1689,     0,   968,   969,     0,   405,     0,     0,
       0,     0,     0,     0,     0,     0,   968,   969,     0,     0,
       0,     0,     0,   962,   406,     0,     0,     0,   963,   970,
       0,     0,  1002,   404,   964,     0,   406,   965,     0,   403,
     961,   970,     0,     0,     0,     0,     0,   971,     0,     0,
       0,   401,     0,     0,     0,   972,     0,     0,   343,   971,
     967,     0,     0,   575,   407,     0,     0,   972,     0,   966,
     343,     0,     0,     0,     0,   576,   407,     0,   577,   578,
     579,   580,   581,   582,   583,     0,     0,     0,     0,     0,
     402,     0,   964,     0,     0,   965,   405,   403,     0,     0,
       0,     0,     0,     0,     0,   968,   969,     0,     0,     0,
     404,     0,     0,   584,     0,   585,   586,   587,   588,   589,
     590,     0,     0,     0,     0,   406,     0,   966,     0,     0,
     970,     0,     0,     0,     0,     0,     0,   967,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   971,     0,
       0,     0,     0,     0,     0,   591,   972,     0,     0,   343,
       0,     0,     0,     0,     0,   407,     0,     0,   404,     0,
       0,     0,     0,   405,     0,     0,     0,     0,     0,     0,
       0,     0,   968,   969,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   967,     0,     0,     0,     0,
       0,     0,   406,     0,     0,     0,     0,   970,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   971,     0,     0,     0,     0,
       0,   405,     0,   972,     0,     0,   343,   592,     0,     0,
     968,   969,   407,     0,     0,     0,     0,     0,     0,     0,
      40,     0,     0,   593,     0,     0,     0,     0,     0, -1523,
     406,     0,     0,     0,     0,   970,     0,  1588,     0,  1589,
       0,     0,  1590,   577,   578,   579,   580,   581,   582,   583,
    1591,  1592,  1593,   971,     0,     0,     0,   594,     0,     0,
       0,   972,     0,     0,   343,     0,     0,     0,     0,     0,
     407,  1594,     0,     0,     0,     0,     0,     0,   584,   595,
     585,   586,   587,   588,   589,   590,     0,     0,     0,     0,
       0,     0,     0,     0,   596,     0,     0,     0,     0,     0,
       0,   597,     0,   598,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   599,     0,     0,     0,
     591,     0,     0,     0,     0,     0,   600,     0,     0,     0,
       0,     0,     0,   601,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1595,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     602,     0,   603,   604,   605,     0,     0,     0,  1596,     0,
       0,  1597,  1598,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1599,   606,     0,     0,     0,
       0,     0,   592,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0, -1523,     0,     0,     0,     0,   593,     0,
       0,   607,   608,   609,     0,   577,   578,   579,   580,   581,
     582,   583,  1600,     0,   610,     0,   958,   611,     0,     0,
       0,  1601,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   960,   594,  2001,  2002,     0,     0,  -328,     0,     0,
     584,     0,   585,   586,   587,   588,   589,   590,     0,     0,
       0,     0,     0,     0,  1602,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1603,   596,
       0,     0,     0,     0,     0,     0,   597,     0,   598,     0,
       0,     0,   591,     0,     0,     0,     0,     0,     0,     0,
       0,   599,  1604,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   577,   578,   579,   580,   581,   582,     0,     0,
       0,     0,     0,     0,     0,   961,  1605,     0,     0,     0,
       0,  1606,     0,     0,     0,     0,   401,     0,     0,     0,
       0,     0,     0,     0,     0,  1607,     0,   584,     0,   585,
     586,   587,   588,   589,   590,   602,     0,   603,   604,   605,
       0,     0,     0,     0,     0,  2003,  1122,     0,     0,     0,
       0,   963,     0,     0,   592,   402,     0,   964,     0,   958,
     965,     0,   403,     0,     0,     0,     0,     0,     0,   591,
     593,  1608,     0,     0,   960,     0,     0,     0,     0,     0,
       0,     0,  1609,     0,  2004,  2005,   607,   608,   609,     0,
       0,     0,   966,     0,     0,     0,     0,     0,     0,   610,
       0,  1610,   611,     0,   594,     0,     0,     0,     0,  2006,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1611,     0,     0,     0,   595,     0,     0,     0,
       0,     0,     0,   404,     0,     0,     0,     0,     0,     0,
       0,   596,     0,     0,     0,     0,     0,     0,   597,     0,
     598,   592,     0,  2007,     0,     0,     0,     0,   961,     0,
     967,     0,     0,   599,     0,     0,     0,     0,     0,   401,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   405,     0,     0,  1122,
       0,   594,     0,     0,   963,   968,   969,     0,   402,     0,
     964,     0,     0,   965,     0,   403,     0,   602,     0,   603,
     604,   605,     0,     0,     0,   406,  2008,     0,     0,     0,
     970,     0,     0,     0,     0,     0,     0,     0,   596,     0,
    2009,     0,     0,     0,     0,   966,     0,   598,   971,     0,
       0,     0,     0,     0,     0,     0,   972,     0,     0,   343,
     599,     0,     0,  2010,     0,   407,  1123,  1124,   607,   608,
     609,     0,     0,     0,  1633,  1125,     0,     0,     0,     0,
       0,   610,     0,     0,   611,  2011,   404,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2012,     0,     0,     0,     0,     0,
       0,     0,     0,   967,     0,     0,   603,   604,   605,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   405,
       0,     0,     0,     0,     0,     0,     0,     0,   968,   969,
       0,     0,     0,     0,     0,   607,   608,   609,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   406,     0,
       0,     0,     0,   970,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   971,     0,     0,     0,     0,     0,     0,     0,   972,
       0,     0,   343,     0,     0,     0,     0,     0,   407,  1123,
    1124,     0,     0,     0,     0,     0,     0,  1867,  1125
};

static const yytype_int16 yycheck[] =
{
      83,   128,   165,   376,   490,   611,   667,   240,   631,   265,
     877,   841,   815,   269,   422,   271,  1250,  1001,  1073,   600,
    1181,   836,   185,   186,  1181,  1181,  1181,   190,   191,   192,
     193,   194,   847,   196,   265,   198,  1181,  1079,   269,   838,
     271,   855,   696,  1455,   340,  1063,  1236,  1675,  1021,   972,
     994,  1319,  1361,  1362,   868,   182,  1029,   837,   574,  1319,
    1319,  1473,  1213,   779,     9,  1319,   149,   230,   554,   232,
    1319,   637,     6,  1319,   445,   331,   239,     9,    13,    22,
      17,     6,     6,     6,   247,   341,   319,    17,     6,   187,
    1204,  1205,  1206,   326,   350,   766,  1151,   195,   261,   262,
     331,   264,  1075,     9,    48,    55,    68,   270,    92,  1521,
     341,    53,   408,    83,    47,   102,   214,     9,    82,   350,
    1254,   377,   113,    69,    27,   176,    92,  1174,   116,    55,
    1320,   201,  1150,     9,    89,   298,    71,   116,   301,   302,
     373,   304,   117,    49,  1826,   118,   377,   380,   379,  1561,
      61,  1341,    87,    48,   957,    68,   165,   320,    55,   962,
     393,   259,   260,  1210,    48,    48,  1110,    48,    29,   267,
     268,    21,    59,     9,   337,   273,   274,    36,    64,    55,
     476,   437,   208,  1811,   415,   808,    47,   420,   574,   163,
     192,   424,   116,    68,  1241,    68,    68,   280,    85,    86,
      83,   109,  1352,   113,  1345,    22,   437,   110,   166,  1359,
    1228,  1352,   375,   228,   117,   835,   144,  1020,  1359,   134,
     383,    70,   145,   228,   844,   845,   291,  1000,   166,   118,
     232,    31,   166,   113,   857,    39,  1145,   228,   158,   859,
     860,   270,  1289,   170,   208,   478,  1113,  1814,  1770,   108,
     252,    30,  1294,   873,   874,   353,   208,  1071,   491,   395,
     212,   393,   218,   399,    29,   208,   782,   638,   217,   432,
     363,   117,  1290,   162,   240,   358,   947,   948,   361,   386,
    1692,    11,   260,   189,  1057,  1594,  1539,  1058,   451,   452,
     523,  1600,   168,    11,  1842,   528,   228,   189,   844,  1272,
    1490,  1554,   533,   534,   112,     8,    24,    25,   169,  1857,
    1858,   934,   918,   219,  1258,   408,   448,   240,   228,  1122,
     228,   208,   228,  1094,   487,    64,   105,   228,   874,   235,
     296,    34,   228,  1351,   307,  1486,   228,     9,    56,    68,
      70,   217,   371,   235,  1174,  1392,   316,   228,   228,   512,
    1464,   228,     0,   212,   424,   975,   121,   520,  1906,   159,
     280,  1909,   595,   944,   945,   492,   431,   322,   271,  1936,
     601,   345,   316,   301,    92,    93,   217,    95,   181,  1194,
    1210,   337,   355,   949,  1004,   103,   163,   302,   332,   351,
     553,   208,   367,   320,   445,   558,   782,   284,   561,   562,
     306,   564,   565,  1218,  1446,   568,   292,  1462,   515,   228,
    1932,  1241,  2094,  1935,   306,   312,   252,   432,  1038,   445,
    1393,   316,   396,   432,  1238,   427,   414,   432,   146,   147,
     385,  1340,   316,   316,   238,   414,   236,   332,   351,   157,
    1574,   432,  1222,   354,   431,   432,  1994,   610,   432,   228,
     929,   397,   401,   431,  1866,   425,   431,   432,   134,  1289,
    1080,   391,   426,   369,   313,  1085,   432,   400,   394,   394,
     394,   446,  1252,   309,   432,  1146,   351,   369,   351,   351,
     432,   425,   424,   433,  1257,   447,   225,   432,   296,   432,
     414,   428,   398,  1643,   432,  1513,   355,   431,   432,  2047,
     432,   445,  1643,  1915,   432,  1917,   398,   432,   432,   432,
     637,   229,   768,   769,   432,  1138,   181,   813,     9,   775,
    1300,   456,   432,   161,   432,   401,   243,  1545,   431,   332,
     425,   432,   438,  1945,   447,   766,   432,   768,   769,   400,
    1524,   425,   425,   177,   775,   395,   438,  1520,   397,   399,
     445,   432,   432,   292,  1174,   432,   228,   438,   445,  2081,
     401,  1181,  1392,   201,  1976,  1977,     9,  1801,   345,  1837,
     431,   209,   447,  1154,   447,   447,  1487,  1837,  1837,   950,
    1161,    29,  1493,  1837,  1063,   431,   432,   260,  1837,  1209,
    1210,  1837,    61,   756,    48,   758,  1747,   830,  2226,   121,
    1116,  1317,    24,   250,     9,   181,   837,    12,   237,   181,
      15,    16,    55,   432,   181,   778,    64,   228,  2166,   438,
     232,  1241,   351,  2171,   341,   343,   302,   858,   181,   240,
     232,   862,   232,   864,  1824,   866,   867,   243,   869,  1220,
     252,   279,   898,   240,  1123,  1124,  1125,   194,   295,   182,
     946,   445,   252,   884,  1133,    27,  1276,   207,   914,  1701,
    1280,  1281,  2251,  1283,  1444,   383,   237,   898,   302,  1289,
     901,  1150,   301,   284,   339,   208,  1155,   243,  1157,  2268,
    1159,   445,  1161,   914,  1163,  1164,  1165,  1166,  1167,  1168,
    1169,  1170,  2001,   145,   927,   291,  1262,  1744,   189,  1746,
    1266,   932,   124,   181,   310,  1519,   312,   257,   189,   929,
     439,   440,   441,   442,   432,   444,   947,   948,   447,   232,
     349,  1694,  1666,  1667,  1668,   168,   174,   445,   445,   276,
     301,  1981,   254,  1983,  1781,   862,   338,   228,   110,   252,
    1401,  1322,  1760,   416,   235,   228,   189,   228,   121,  1228,
     204,  1674,   915,    68,   235,   316,  1679,  1680,   431,   842,
    1683,  1684,  1685,   339,  1687,  1688,  1813,   339,   237,     4,
    2182,  2183,   339,   270,   217,   341,   929,   225,   349,   332,
     863,   313,   865,     8,    19,   228,  1367,   870,  1902,  1903,
    1904,  1905,   235,    28,   432,   893,   879,   394,  1597,  1453,
    1818,   279,   315,   194,  1715,  1716,  1779,  1849,  1969,    34,
     169,  1290,  1969,  1969,  1969,   306,   445,  1859,  1860,   431,
     432,   432,   237,   115,  1969,   306,    61,   438,  1059,    26,
    1741,   431,   301,  1494,   207,   431,   432,   174,   239,  1750,
     245,   246,  1503,  1322,   292,    12,   239,   228,    15,    16,
    1329,  1330,  1331,  1332,  1333,  1334,  1335,   340,   263,   264,
     161,   359,    68,   306,   425,   397,   363,   196,  1910,  1911,
    2120,   297,  1351,   963,   445,   310,   302,   268,   369,   413,
     349,   254,  1115,   242,   257,   354,   301,    46,   369,   290,
     189,   228,   426,   406,   102,    97,   225,   290,   988,   359,
     201,    60,  1029,  1123,  1124,  1125,   228,   398,   209,  1860,
     408,   408,   995,  1133,  1744,  1146,  1746,  2151,   431,   222,
    1047,   154,   303,   228,   227,   158,   369,     9,   250,   228,
     365,   366,  1552,  1748,   349,   149,   235,  1157,    97,  1994,
     445,   432,  1105,  1163,  1164,  1165,  1166,   438,   408,  1169,
    1170,  1781,   445,    24,    25,   398,   266,   438,   401,  1910,
    1911,   196,   170,   432,   205,   192,   193,  1548,   290,  1880,
    1123,  1124,  1125,    55,   182,  1636,    80,   359,   279,   162,
    1133,   310,   285,  1813,  1799,   432,  1897,   228,   317,   432,
     225,  1222,   367,   207,    65,   438,    67,   232,   445,   182,
     115,  1985,  1155,  1914,  1157,   232,  1159,   306,   287,   288,
    1163,  1164,  1165,  1166,  1167,  1168,  1169,  1170,   328,   866,
    2254,  1252,   301,   359,   359,   252,   408,    98,    99,   100,
     445,   162,   225,   226,  1513,  1514,   351,   884,   439,   440,
     347,   255,   277,   257,  1955,  1956,   439,   440,   283,   208,
     445,   182,   164,  1964,   213,  1311,  1312,   432,   368,   298,
     370,   364,  1189,   232,   223,   310,  1545,   312,   347,  1300,
     369,   446,   408,   408,   145,   310,   147,   431,   245,   246,
    1311,  1312,   317,   252,   155,     6,   232,    30,     9,    32,
     202,   445,    35,   261,   262,   330,   263,   264,   210,   398,
    2084,  1968,    45,   232,   261,   262,   252,   189,  1516,  1329,
    1330,  1331,  1332,  1333,  1334,  1335,  1199,   395,   269,   354,
     271,   399,   357,   252,   439,   440,   441,   442,   445,   444,
     365,   445,   447,   432,  1261,   217,  1759,   481,   347,   438,
     375,  2052,   486,   445,  1155,   351,   228,  2058,  1159,   445,
       2,   310,   311,   235,     6,   226,  1167,  1168,    79,    87,
      88,   396,  2073,   310,   323,   312,   325,  1379,  1788,   240,
    1382,   225,   226,    94,  1301,  1387,  1329,  1330,  1331,  1332,
    1333,  1334,  1335,   111,   439,   440,   441,   442,   115,   444,
    2101,  1814,  2103,   151,   152,   302,   451,  1676,   130,  2110,
     427,    11,  1681,   301,   431,   155,  2009,  2191,   445,   159,
     445,   347,   434,  1444,    24,    25,   428,   164,   430,  2130,
    2131,   179,   441,   442,   306,   444,   347,   185,   171,   148,
     151,   150,   175,   439,   440,   441,   442,   256,   444,   258,
    2070,   447,  2072,   231,   445,   188,    56,   432,   332,   439,
     440,   441,   442,   445,   444,   189,   445,   178,   216,   119,
     838,   451,   220,   148,   445,   150,   425,   445,   189,  1889,
     310,   189,   312,   439,   440,   441,   442,   350,   444,   857,
     445,  1760,    92,    93,   862,    95,   445,   369,   210,  1768,
     445,   234,  1778,   103,   228,  2206,   396,   445,   219,   347,
     432,   235,   227,   224,   432,   445,   445,   228,   176,   230,
     228,   274,   233,  1936,   235,   445,   398,   235,   386,   401,
    1576,   392,    23,   439,   440,   441,   442,   445,   444,   189,
    2197,   447,   417,   418,   419,   420,   146,   147,   281,  1818,
     417,   418,   419,   420,   265,  1576,   347,   157,   323,   363,
     432,   929,  1585,   208,   445,   102,   438,   285,   286,   375,
     432,   432,   305,   358,  1620,  1851,    55,    82,   228,  1602,
     170,   445,   306,   347,   342,   235,   439,   440,   441,   442,
     432,   444,  1638,   363,   447,   306,   329,   247,   306,  1620,
    1553,   334,  2053,  2054,   274,   104,  1523,   228,   326,   327,
     354,   344,   205,   445,   241,   348,   432,  1638,   439,   440,
     441,   442,   333,   444,    66,   445,   447,   347,  1581,   229,
     445,   241,  1678,    22,   268,   432,  1589,   417,   418,   419,
     420,   228,  1559,  1596,   445,   369,   292,   445,    81,  1566,
    1720,  1721,  1722,  1723,    81,   445,   306,  1678,   369,   432,
     426,   369,   391,   432,   308,   226,  1676,   378,   379,   394,
     194,  1681,   405,    32,    79,   432,    35,   310,   394,  1047,
      54,  2091,   415,   355,    43,    44,    45,   398,   431,    94,
     398,   375,   403,    36,  1647,    26,   182,  1650,   446,   363,
     445,   449,   450,   439,   440,   441,   442,   445,   444,   347,
     421,   447,   375,   445,   438,   212,   355,   219,   429,   369,
     337,   432,   372,   373,   428,   432,   208,   438,   104,   396,
     438,   297,   228,  1676,   278,   446,   272,   372,  1681,   438,
     394,    26,   448,   343,   391,    12,    13,    14,   353,   268,
     452,   169,  2148,    20,   445,  1123,  1124,  1125,   445,   439,
     440,   441,   442,  2176,   444,  1133,   432,   447,   396,   228,
     131,  1724,   102,   178,    17,  2185,   431,  1730,  2188,   167,
     182,   393,   391,   383,   228,    29,   448,  1155,   438,  1157,
      57,  1159,   448,  1161,   153,  1163,  1164,  1165,  1166,  1167,
    1168,  1169,  1170,   439,   440,   441,   442,   122,   444,   123,
    1833,   447,   171,   199,    55,   394,   448,   448,   448,  1772,
     424,   125,   448,   228,   448,   230,   448,  2237,   233,   188,
     448,   339,   432,   448,   834,   448,   310,   448,   838,   127,
      96,   128,  2005,   390,   844,   394,   132,    48,   393,   849,
     850,   133,   391,   393,   388,   855,   856,   857,   174,   138,
     265,  2271,   862,   426,    48,   240,  1783,   141,   868,   174,
     107,   324,  1789,   371,   271,   234,   109,   877,   878,   109,
     880,   431,   394,   181,   151,   152,  1839,   332,   300,   432,
     228,  1844,   158,   129,   166,   428,  1942,   357,   204,   394,
     394,    48,   212,   174,   204,   117,   271,   187,   356,   444,
    1783,   437,   179,   436,   261,   212,   225,   447,   185,   447,
     447,  1942,   281,   332,   389,   447,   394,   364,   333,   929,
     126,   257,   260,   256,   181,   391,   394,   322,    48,   133,
       8,   208,   174,   428,   121,   428,     9,   394,   298,   216,
     299,   168,   259,   220,  1322,   275,   196,   275,   320,   959,
     120,  1329,  1330,  1331,  1332,  1333,  1334,  1335,   335,   105,
     425,   425,    48,   378,   379,   334,   254,   170,   136,   232,
     276,   248,   249,   137,   253,   344,   253,   139,   280,   291,
     108,   275,   385,     7,   994,   111,   263,   395,   403,   214,
      65,   151,   151,   270,   124,   131,  2029,   319,   275,    97,
      48,   319,   232,   212,    91,   140,   421,   255,    88,   258,
     143,  1021,   197,   215,   429,   186,   293,   432,   428,  1029,
    1030,   432,    48,   381,     1,   298,   335,   397,   142,     6,
     169,   232,     9,   232,  1997,   413,   405,  1047,   298,   284,
     174,   135,    48,     6,    53,  2008,    21,  2010,   167,   128,
     325,   182,   177,  1063,  1273,   200,  2087,   547,   472,  1095,
     132,  1071,   408,  1305,  1829,  1075,  1312,  1097,   904,   216,
    1782,   559,   107,  1083,    48,   358,  1086,   221,  2041,  2042,
     149,   534,   292,   807,   829,  1622,  1837,  2173,   934,   917,
     517,  2024,  2159,   782,  1703,   120,  1786,  2153,   454,  1004,
    1110,  1364,    79,  1113,  1363,  2138,  1662,  1009,  1701,  1737,
    1218,  1215,  1486,  1123,  1124,  1125,  1747,    94,  1926,  2175,
    1231,  1511,  2153,  1133,  1768,  2158,  2159,  1225,  1047,  1787,
    2093,  1535,  1301,  1266,  1803,  1069,  1071,  1080,   869,  1566,
    1150,  1979,  1566,  1640,  2175,  1155,  2094,  1157,  1984,  1159,
    1990,  1794,  1460,  1163,  1164,  1165,  1166,  1167,  1168,  1169,
    1170,   438,   439,   440,   441,   442,  1059,   444,  1183,   446,
     447,  2175,   449,   450,   151,   152,  2139,  2140,  1548,   930,
    2143,   228,  1576,  1179,   300,  2218,  2219,  2150,  2244,  2222,
    1236,  2224,  1012,   566,     9,   812,  2177,   772,   939,    56,
    1407,   178,   179,  1845,    -1,    -1,    -1,    -1,   185,  1136,
      -1,    -1,   189,  2244,    -1,    -1,    -1,    -1,  1228,  1597,
    2251,    -1,    -1,    -1,    -1,    -1,  2189,    -1,  1238,  2262,
      -1,   208,    -1,    -1,    -1,    -1,    -1,  2268,    -1,   216,
      -1,  1251,   219,   220,    -1,    -1,  2129,   224,  1258,    -1,
      -1,   228,    -1,   230,    -1,  1265,   233,  2220,   235,    -1,
      -1,    -1,  1272,    -1,    79,    -1,    -1,    -1,    -1,    -1,
       6,   248,    -1,     9,  1284,    -1,   253,    -1,    -1,    94,
    1290,    -1,    -1,    -1,    -1,    -1,  1296,    -1,   265,    -1,
    2253,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1676,    -1,
      -1,    -1,    -1,  1681,  1314,    -1,    -1,  2190,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1329,
    1330,  1331,  1332,  1333,  1334,  1335,    -1,    -1,    -1,   306,
      79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1351,    -1,    79,    -1,    94,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   333,    -1,    94,    -1,
      -1,  1371,    -1,   178,    -1,    -1,    -1,    -1,    -1,  2252,
      -1,    -1,    -1,    -1,   189,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1393,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   369,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   378,   379,    -1,    -1,    -1,    -1,    -1,   144,    -1,
      -1,    -1,    -1,   228,    -1,   230,    -1,    -1,   233,    -1,
     235,   398,    -1,    -1,    -1,    -1,   403,    -1,    -1,   178,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1447,  1448,    -1,
     189,    -1,   178,    -1,   421,    -1,    -1,    -1,    -1,    -1,
     265,    -1,   429,   189,    -1,   432,    -1,    -1,    -1,    -1,
      -1,   438,   439,   440,    -1,    -1,    -1,   444,    -1,   446,
     219,   448,   449,   450,    -1,   224,    -1,    -1,    -1,   228,
      -1,   230,    -1,   219,   233,    -1,   235,    -1,   224,    -1,
      -1,   306,   228,    -1,   230,    -1,    -1,   233,    -1,   235,
      -1,    -1,    -1,  1513,  1514,    -1,    -1,    -1,    -1,  1519,
    1520,    -1,    -1,    -1,    -1,    -1,   265,    -1,   333,    -1,
      -1,     0,     1,    -1,     3,    -1,     5,  1537,    -1,   265,
      -1,    10,    -1,    -1,    -1,  1545,    -1,    -1,    -1,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1560,    -1,    -1,    -1,   369,  1565,  1566,   306,    -1,    -1,
      -1,    -1,    -1,   378,   379,    -1,    -1,    -1,    -1,    -1,
     306,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      -1,    -1,    -1,   398,   333,    -1,    -1,  1597,   403,    -1,
      69,    -1,    -1,    72,    -1,    -1,    -1,   333,  1608,    -1,
    1610,    -1,    -1,    -1,    -1,    84,   421,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   429,    -1,    -1,   432,    -1,    -1,
     369,    -1,    -1,   438,    -1,    -1,    -1,   106,    -1,   378,
     379,    -1,    -1,   369,   113,   114,    -1,    -1,    79,    -1,
      -1,    -1,   378,   379,    -1,    -1,    -1,    -1,    -1,   398,
      -1,   130,    -1,    94,   403,   134,  1666,  1667,  1668,   395,
      -1,    -1,   398,   399,    -1,   144,  1676,   403,    -1,    -1,
      -1,  1681,   421,    -1,    -1,    -1,    -1,   156,    -1,    -1,
     429,   160,    -1,   432,  1694,   421,    -1,    -1,    -1,   438,
     439,   440,    -1,   429,   173,    -1,   432,    -1,   177,   448,
      -1,   180,   438,    -1,   183,   184,    -1,    -1,    -1,    -1,
      -1,    -1,   191,    -1,    -1,    -1,    -1,    -1,    -1,   198,
      -1,   200,    -1,    -1,   203,    -1,    -1,    -1,    -1,    -1,
      -1,   172,    -1,    -1,    -1,    -1,    -1,   178,    -1,    -1,
      -1,    -1,    -1,  1753,    -1,    -1,    -1,    -1,    -1,  1759,
    1760,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1768,   238,
      -1,    -1,    -1,   242,    -1,   244,    -1,    -1,    -1,  1779,
      -1,    -1,   251,    -1,    -1,    -1,    -1,  1787,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   228,    -1,   230,
      -1,    -1,   233,    -1,   273,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1814,    -1,    -1,    -1,  1818,   288,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   302,   265,    -1,    -1,    -1,  1838,    -1,
     309,    -1,  1842,    -1,    -1,    -1,    -1,    -1,    -1,   318,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1857,  1858,    -1,
      -1,    -1,   331,    -1,    -1,    -1,     1,   336,     3,   338,
       5,    -1,    -1,    -1,    -1,    10,    -1,   346,    -1,    -1,
      -1,    -1,    -1,    18,    -1,    -1,    -1,   356,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   365,    -1,    -1,    -1,
      -1,    -1,   333,    -1,    -1,   374,  1906,   376,   377,  1909,
      -1,   380,    -1,   382,    -1,    50,    51,    -1,   387,    -1,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   402,    69,    -1,  1936,    72,   407,    -1,
      -1,    -1,    -1,   412,    -1,    -1,    -1,   378,   379,    84,
      -1,    -1,    -1,    -1,   423,    -1,    -1,   388,    -1,    -1,
      -1,    -1,    -1,   432,    -1,    -1,   435,    -1,  1968,    -1,
      -1,   106,   403,    -1,    -1,  1975,   445,    -1,   113,   114,
      -1,    -1,   413,    -1,    -1,    -1,   121,    -1,    -1,    -1,
     421,    -1,    -1,    -1,  1994,   426,    -1,    -1,   429,    -1,
     431,   432,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   144,
      -1,  2011,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   156,    -1,    -1,    -1,   160,    -1,    -1,    79,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   173,    -1,
      -1,    -1,    -1,    94,    -1,   180,    -1,  2047,   183,   184,
      -1,    -1,    -1,    -1,    -1,    -1,   191,    -1,    -1,    -1,
      -1,    -1,    -1,   198,    -1,   200,    -1,    -1,   203,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,    -1,    -1,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    -1,
      -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   238,  2104,    -1,    -1,   242,    -1,   244,
      -1,    -1,    -1,    -1,    -1,    -1,   251,    -1,    -1,  2119,
      -1,   172,  2122,    -1,    -1,    -1,    -1,   178,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   273,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    -1,  2152,   288,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    94,  2166,    -1,    -1,    -1,
      -1,  2171,    -1,    -1,   309,    -1,    -1,   228,    -1,   230,
      -1,    -1,   233,   318,    -1,     6,    -1,    -1,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   331,  2197,    -1,    -1,
      -1,   336,    -1,   338,    -1,    -1,    -1,    -1,  2208,    -1,
      -1,   346,    -1,    -1,   265,    -1,    -1,    -1,    -1,    -1,
      -1,   356,   151,   152,    -1,    -1,    -1,    -1,    -1,    -1,
     365,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   374,
      -1,   376,   377,    -1,    -1,   380,    -1,   382,    -1,   178,
     179,    -1,   387,    -1,    -1,  2255,   185,    -1,    79,    -1,
     189,    -1,    -1,    -1,    -1,    -1,    -1,   402,    -1,    -1,
      -1,    -1,   407,    94,    -1,    -1,    -1,   412,    -1,   208,
      -1,    -1,   333,    -1,    -1,    -1,    -1,   216,   423,    -1,
     219,   220,    -1,    -1,    -1,   224,    -1,   432,    -1,   228,
     435,   230,    -1,    -1,   233,    -1,   235,    -1,    -1,    -1,
     445,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   248,
      -1,    -1,    -1,    -1,   253,    -1,    -1,   378,   379,    -1,
     151,   152,    -1,    -1,    -1,    -1,   265,   388,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   403,    -1,    -1,    -1,    -1,   178,   179,    -1,
      -1,    -1,   413,    -1,   185,    -1,    -1,    -1,   189,    -1,
     421,    -1,    -1,    -1,    -1,   426,    -1,   306,   429,    -1,
     431,   432,    -1,    -1,    -1,    -1,    -1,   208,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   216,    -1,    -1,   219,   220,
      -1,    -1,    -1,   224,   333,    -1,    -1,   228,    -1,   230,
      -1,    -1,   233,    -1,   235,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   248,    -1,    -1,
      -1,    -1,   253,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     369,    -1,    -1,    -1,   265,    -1,    -1,    -1,    -1,   378,
     379,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   395,    -1,    -1,   398,
     399,    -1,    -1,    -1,   403,    -1,    -1,    -1,    -1,    -1,
       3,    -1,     5,    -1,    -1,   306,    -1,    10,    -1,    -1,
      -1,    -1,   421,    -1,    -1,    18,    -1,    -1,    -1,    -1,
     429,    -1,    -1,   432,    -1,    -1,    -1,    -1,    -1,   438,
     439,   440,   333,    -1,    -1,   444,    -1,   446,    -1,   448,
     449,   450,    -1,    -1,    -1,    -1,    -1,    50,    51,    -1,
      -1,    -1,     3,    -1,     5,    58,    -1,    -1,    -1,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    69,    18,   369,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   378,   379,    -1,
      -1,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   398,    -1,    50,
      51,    -1,   403,   106,    -1,    -1,    -1,    58,    -1,    -1,
     113,   114,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,
     421,    72,    -1,    -1,    -1,    -1,    -1,    -1,   429,    -1,
      -1,   432,    -1,    84,    -1,    -1,    -1,   438,   439,   440,
      -1,   144,    -1,   444,    -1,   446,    -1,   448,   449,   450,
      -1,    -1,    -1,   156,    -1,   106,    -1,   160,    -1,    -1,
      -1,    -1,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,
     173,    -1,    -1,    -1,    -1,    -1,    -1,   180,    -1,    -1,
     183,   184,    -1,    -1,    -1,    -1,    -1,    -1,   191,     6,
      -1,    -1,     9,   144,    -1,   198,    -1,   200,    -1,    -1,
     203,    -1,    -1,    -1,    -1,   156,    -1,    -1,    -1,   160,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   173,    -1,    -1,    -1,    -1,    -1,    -1,   180,
      -1,    48,   183,   184,    -1,   238,    -1,    -1,    -1,   242,
     191,   244,    -1,    -1,    -1,    -1,    -1,   198,   251,   200,
      -1,    -1,   203,    -1,    -1,    -1,     6,    -1,    -1,     9,
      -1,    -1,    79,    -1,    -1,    -1,    83,    -1,    -1,     6,
     273,    -1,     9,    -1,    -1,    -1,    -1,    94,    -1,    29,
      -1,    -1,    -1,    -1,    -1,   288,    -1,   238,    -1,    -1,
      -1,   242,    -1,   244,    -1,    -1,    -1,    -1,    -1,    -1,
     251,    -1,    -1,    -1,    -1,    -1,   309,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,   318,    -1,    -1,    -1,    -1,
      -1,    -1,   273,    -1,    -1,    -1,    -1,    -1,   331,    79,
      -1,    -1,    -1,   336,    -1,   338,    -1,   288,    -1,    -1,
      -1,    -1,    79,   346,    94,    -1,     6,    -1,    -1,     9,
      -1,    -1,    -1,   356,    -1,    -1,    -1,    94,   309,    -1,
      -1,   178,   365,    -1,    -1,    -1,    -1,   318,    -1,    -1,
     107,   374,   189,   376,   377,    -1,    -1,   380,    -1,   382,
     331,    -1,    -1,    -1,   387,   336,    -1,   338,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   346,    -1,    -1,    -1,   402,
      -1,    -1,   219,    -1,   407,   356,    -1,   224,    -1,   412,
      -1,   228,    -1,   230,   365,    -1,   233,    -1,   235,    79,
     423,    -1,    -1,   374,    -1,   376,   377,    -1,   178,   380,
      90,   382,   435,    -1,    94,    -1,   387,    -1,    -1,   189,
      -1,   178,   445,    -1,    -1,    -1,    -1,    -1,   265,    -1,
      -1,   402,   189,   270,    -1,    -1,   407,    -1,    -1,    -1,
      -1,   412,    -1,    -1,    -1,    -1,    -1,   204,    -1,   219,
      -1,    -1,   423,    -1,   224,   225,    -1,    -1,   228,    -1,
     230,    -1,   219,   233,   435,   235,    -1,   224,    -1,   306,
      -1,   228,    -1,   230,    -1,    -1,   233,    -1,   235,   316,
      -1,    -1,    -1,    -1,     6,    -1,    -1,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   265,   333,    -1,   178,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   265,   189,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   292,    -1,    -1,    -1,   363,    -1,    -1,    -1,
      -1,    -1,   369,    -1,    -1,    -1,   306,    -1,    -1,   219,
      -1,   378,   379,    -1,   224,    -1,    -1,    -1,   228,   306,
     230,    -1,    -1,   233,    -1,   235,    -1,    79,    -1,     6,
      -1,   398,     9,   333,    -1,    -1,   403,    -1,    90,    -1,
      -1,   408,    94,    -1,    -1,    -1,   333,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   421,   265,    -1,    -1,   425,    -1,
      -1,    -1,   429,    -1,    -1,   432,    -1,    -1,    -1,   369,
      -1,   438,    -1,    -1,    -1,    -1,    -1,    -1,   378,   379,
      -1,    -1,   369,    -1,    -1,     6,    -1,    -1,     9,    -1,
      -1,   378,   379,    -1,    -1,    -1,   306,    -1,   398,    -1,
      -1,    -1,    79,   403,    -1,    -1,     6,    -1,    -1,     9,
      -1,   398,    -1,    -1,    -1,    -1,   403,    94,    -1,    -1,
      -1,   421,    -1,   333,    -1,    -1,   178,    -1,    -1,   429,
     107,    -1,   432,    -1,   421,    -1,    -1,   189,   438,    -1,
      -1,    -1,   429,    -1,    -1,   432,    -1,    -1,    -1,    -1,
      -1,   438,    -1,    -1,    -1,    -1,    -1,    -1,    79,   369,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   219,   378,   379,
      -1,    -1,   224,    94,    -1,    -1,   228,    -1,   230,    79,
      -1,   233,    -1,   235,    -1,    -1,    -1,    -1,   398,    -1,
      90,    -1,    -1,   403,    94,    -1,    -1,    -1,    -1,    -1,
      -1,   178,    -1,    -1,    -1,    -1,    -1,     6,    -1,    -1,
       9,   421,   189,   265,    -1,    -1,    -1,    -1,    -1,   429,
      -1,    -1,   432,    -1,    -1,    -1,    -1,    -1,   438,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   219,    -1,    -1,    -1,    -1,   224,    -1,    -1,
      -1,   228,    -1,   230,   306,    -1,   233,   178,   235,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   189,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   178,    -1,
      79,   333,    -1,    -1,    -1,    -1,    -1,    -1,   265,   189,
      -1,    -1,    -1,    -1,    -1,    94,    -1,    -1,   219,    -1,
      -1,    -1,    -1,   224,    -1,    -1,    -1,   228,    -1,   230,
      -1,    -1,   233,    -1,   235,    -1,    -1,   369,    -1,   219,
      -1,    -1,    -1,    -1,   224,    -1,   378,   379,   228,   306,
     230,    -1,    -1,   233,    -1,   235,    -1,    -1,    -1,    -1,
      -1,    -1,     6,    -1,   265,     9,   398,    -1,    -1,    -1,
      -1,   403,    -1,    -1,     6,    -1,   333,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   265,    -1,    -1,    -1,   421,
      -1,    -1,    -1,    -1,    -1,   174,    -1,   429,    -1,   178,
     432,    -1,    -1,    -1,    -1,   306,   438,    -1,    -1,    -1,
     189,    -1,   369,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   378,   379,    -1,    -1,    -1,   306,    -1,    -1,    -1,
      -1,    -1,   333,    -1,    -1,    79,    -1,    -1,    -1,    -1,
     219,   398,    -1,    -1,    -1,   224,   403,    79,    -1,   228,
      94,   230,    -1,   333,   233,    -1,   235,    -1,    -1,    -1,
      -1,    -1,    94,     6,   421,    -1,     9,    -1,   369,    -1,
      -1,    -1,   429,    -1,    -1,   432,    -1,   378,   379,    -1,
      -1,   438,    -1,    -1,    -1,    -1,   265,    -1,    -1,   369,
      -1,    -1,    -1,   394,    -1,    -1,    -1,   398,   378,   379,
      -1,    -1,   403,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   398,    -1,
     421,    -1,    -1,   403,    -1,    -1,    -1,   306,   429,    -1,
      -1,   432,    -1,    -1,   178,    -1,    79,   438,    -1,    -1,
       6,   421,    -1,     9,    -1,   189,   178,    -1,    -1,   429,
      -1,    94,   432,    -1,   333,    -1,    -1,   189,   438,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   219,    -1,    -1,    -1,    -1,
     224,    -1,    -1,    -1,   228,    -1,   230,   219,    -1,   233,
     369,   235,   224,    -1,    -1,    -1,   228,    -1,   230,   378,
     379,   233,    -1,   235,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,   398,
      -1,   265,    -1,    -1,   403,    -1,    -1,    -1,    94,    -1,
      -1,    -1,    -1,   265,    -1,   178,    -1,    -1,    -1,    -1,
      -1,    -1,   421,    -1,    -1,    -1,   189,    -1,    -1,    -1,
     429,    -1,    -1,   432,    -1,    -1,    -1,    -1,    -1,   438,
      -1,    -1,   306,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    -1,    -1,   306,    -1,   219,    -1,    -1,    -1,
      -1,   224,    -1,    -1,    -1,   228,    94,   230,    -1,   333,
     233,    -1,   235,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   333,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   178,    -1,    -1,    -1,    -1,    -1,    -1,   363,
      -1,    -1,   265,   189,    -1,   369,    -1,    -1,    -1,    -1,
      -1,    -1,   364,    -1,   378,   379,    -1,   369,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   378,   379,    -1,    -1,
      -1,    -1,    -1,   219,   398,    -1,    -1,    -1,   224,   403,
      -1,    -1,   228,   306,   230,    -1,   398,   233,    -1,   235,
     178,   403,    -1,    -1,    -1,    -1,    -1,   421,    -1,    -1,
      -1,   189,    -1,    -1,    -1,   429,    -1,    -1,   432,   421,
     333,    -1,    -1,    21,   438,    -1,    -1,   429,    -1,   265,
     432,    -1,    -1,    -1,    -1,    33,   438,    -1,    36,    37,
      38,    39,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,
     228,    -1,   230,    -1,    -1,   233,   369,   235,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   378,   379,    -1,    -1,    -1,
     306,    -1,    -1,    71,    -1,    73,    74,    75,    76,    77,
      78,    -1,    -1,    -1,    -1,   398,    -1,   265,    -1,    -1,
     403,    -1,    -1,    -1,    -1,    -1,    -1,   333,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   421,    -1,
      -1,    -1,    -1,    -1,    -1,   113,   429,    -1,    -1,   432,
      -1,    -1,    -1,    -1,    -1,   438,    -1,    -1,   306,    -1,
      -1,    -1,    -1,   369,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   378,   379,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   333,    -1,    -1,    -1,    -1,
      -1,    -1,   398,    -1,    -1,    -1,    -1,   403,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   421,    -1,    -1,    -1,    -1,
      -1,   369,    -1,   429,    -1,    -1,   432,   195,    -1,    -1,
     378,   379,   438,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     208,    -1,    -1,   211,    -1,    -1,    -1,    -1,    -1,   217,
     398,    -1,    -1,    -1,    -1,   403,    -1,    30,    -1,    32,
      -1,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,   421,    -1,    -1,    -1,   245,    -1,    -1,
      -1,   429,    -1,    -1,   432,    -1,    -1,    -1,    -1,    -1,
     438,    64,    -1,    -1,    -1,    -1,    -1,    -1,    71,   267,
      73,    74,    75,    76,    77,    78,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   282,    -1,    -1,    -1,    -1,    -1,
      -1,   289,    -1,   291,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   304,    -1,    -1,    -1,
     113,    -1,    -1,    -1,    -1,    -1,   314,    -1,    -1,    -1,
      -1,    -1,    -1,   321,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     153,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     358,    -1,   360,   361,   362,    -1,    -1,    -1,   171,    -1,
      -1,   174,   175,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   188,   384,    -1,    -1,    -1,
      -1,    -1,   195,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   401,    -1,    -1,    -1,    -1,   211,    -1,
      -1,   409,   410,   411,    -1,    36,    37,    38,    39,    40,
      41,    42,   225,    -1,   422,    -1,    79,   425,    -1,    -1,
      -1,   234,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    94,   245,    64,    65,    -1,    -1,   445,    -1,    -1,
      71,    -1,    73,    74,    75,    76,    77,    78,    -1,    -1,
      -1,    -1,    -1,    -1,   267,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   281,   282,
      -1,    -1,    -1,    -1,    -1,    -1,   289,    -1,   291,    -1,
      -1,    -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,   305,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   178,   329,    -1,    -1,    -1,
      -1,   334,    -1,    -1,    -1,    -1,   189,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   348,    -1,    71,    -1,    73,
      74,    75,    76,    77,    78,   358,    -1,   360,   361,   362,
      -1,    -1,    -1,    -1,    -1,   186,   219,    -1,    -1,    -1,
      -1,   224,    -1,    -1,   195,   228,    -1,   230,    -1,    79,
     233,    -1,   235,    -1,    -1,    -1,    -1,    -1,    -1,   113,
     211,   394,    -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   405,    -1,   225,   226,   409,   410,   411,    -1,
      -1,    -1,   265,    -1,    -1,    -1,    -1,    -1,    -1,   422,
      -1,   424,   425,    -1,   245,    -1,    -1,    -1,    -1,   250,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   445,    -1,    -1,    -1,   267,    -1,    -1,    -1,
      -1,    -1,    -1,   306,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   282,    -1,    -1,    -1,    -1,    -1,    -1,   289,    -1,
     291,   195,    -1,   294,    -1,    -1,    -1,    -1,   178,    -1,
     333,    -1,    -1,   304,    -1,    -1,    -1,    -1,    -1,   189,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   369,    -1,    -1,   219,
      -1,   245,    -1,    -1,   224,   378,   379,    -1,   228,    -1,
     230,    -1,    -1,   233,    -1,   235,    -1,   358,    -1,   360,
     361,   362,    -1,    -1,    -1,   398,   367,    -1,    -1,    -1,
     403,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   282,    -1,
     381,    -1,    -1,    -1,    -1,   265,    -1,   291,   421,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   429,    -1,    -1,   432,
     304,    -1,    -1,   404,    -1,   438,   439,   440,   409,   410,
     411,    -1,    -1,    -1,   447,   448,    -1,    -1,    -1,    -1,
      -1,   422,    -1,    -1,   425,   426,   306,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   445,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   333,    -1,    -1,   360,   361,   362,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   369,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   378,   379,
      -1,    -1,    -1,    -1,    -1,   409,   410,   411,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   398,    -1,
      -1,    -1,    -1,   403,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   421,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   429,
      -1,    -1,   432,    -1,    -1,    -1,    -1,    -1,   438,   439,
     440,    -1,    -1,    -1,    -1,    -1,    -1,   447,   448
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   454,   455,     0,   177,   302,   456,   457,   458,   464,
     471,   473,   445,   445,   457,   145,   479,   479,   228,   303,
     474,   474,   115,   459,   465,    26,   475,   475,   445,    97,
     577,   577,   228,   445,   472,    80,   480,   115,   460,   466,
     208,   476,  1121,   347,   164,   202,   210,   531,   445,   298,
     711,   711,   445,    70,   313,   397,   477,   478,   445,   445,
     347,   445,   163,   345,   396,   578,   584,   115,   461,   467,
     471,   130,   470,   478,   301,  1132,   481,   532,   445,   533,
     347,   434,   609,   580,    53,   424,   714,   134,   461,   468,
     479,   474,   266,   328,   368,   370,   482,   483,   487,   495,
     500,   535,   164,   534,   243,   341,   568,   569,   570,   571,
     573,   445,   347,   231,   654,   432,   583,   585,  1052,   716,
     715,   332,   722,   474,   462,   445,   445,   445,   445,   445,
     350,   536,   445,   210,   567,   396,  1117,   310,   365,   366,
     572,   445,   570,   579,   445,   347,   227,   656,   582,   584,
     611,   612,   613,   586,    48,   717,   718,   719,  1112,   717,
     432,   445,   445,   577,   237,   349,   432,   486,   488,   489,
     490,   491,   493,   494,  1132,   176,   496,   497,   498,   431,
     484,   485,   486,  1146,    11,    24,    25,    56,    92,    93,
      95,   103,   146,   147,   157,   229,   343,   383,   432,   501,
     502,   503,   504,   508,   517,   521,   524,   525,   526,   527,
     528,   529,   530,   274,  1098,   535,   445,   386,  1140,    23,
    1108,   581,   610,   445,   347,   323,   658,   585,   614,  1092,
     587,   718,   363,   408,   720,   316,   425,   712,   463,   363,
    1121,   445,   489,   445,   490,    61,   354,  1104,     9,   228,
     499,   445,   498,   445,   445,   485,   102,   432,  1063,  1121,
    1121,  1063,   375,   358,  1136,  1121,  1121,  1121,  1121,  1121,
    1063,  1121,    55,  1114,  1121,   445,   503,  1063,   568,    82,
    1115,   170,  1118,   582,   611,   655,   445,   347,   342,   699,
     611,   445,  1092,   432,   615,   617,   622,    46,    60,    97,
     213,   223,   310,   311,   323,   325,   425,   445,   588,   589,
     591,   595,   597,   599,   600,   606,   607,   608,  1121,  1121,
     363,   274,   721,   104,   723,   711,  1121,   228,  1081,   445,
     354,  1121,   205,   205,   228,   445,   241,   509,  1063,  1063,
    1121,  1121,  1121,   432,  1060,  1078,    66,  1063,  1063,  1060,
    1121,  1060,   518,   519,  1063,    92,  1063,   537,   574,   575,
    1052,  1051,  1052,   611,   657,   445,   347,   615,   445,   166,
     432,   618,   619,  1115,  1121,   310,   312,  1102,  1102,  1121,
    1115,  1121,   241,  1126,  1121,    22,  1107,   268,   162,   182,
      30,   105,  1081,  1121,   432,   445,   713,   467,  1081,  1060,
    1121,   189,   228,   235,   306,   369,   398,   438,   522,   523,
    1084,  1060,   228,   194,   268,  1101,  1060,    22,   208,  1063,
    1122,   505,   538,   575,   292,   576,  1052,   611,   659,   445,
     445,   616,    81,  1081,   432,  1121,  1107,  1059,  1060,   270,
     371,   596,   228,  1060,  1062,  1081,   426,  1121,   432,   698,
     698,   165,   432,  1081,   724,   725,   134,   469,    55,   433,
     492,   119,   189,   228,   235,   247,   306,   369,   372,   373,
     438,   510,   511,   512,   515,   523,   391,  1078,   520,  1081,
     506,     4,    19,    28,   196,   225,   232,   277,   283,   310,
     317,   330,   357,   365,   396,   445,   539,   540,   544,   546,
     551,   552,   553,   554,   558,   559,   560,   561,   562,   563,
     564,   565,  1104,  1133,  1081,   308,   660,   661,   662,   700,
     623,   620,  1121,   394,   594,  1060,   226,  1125,   394,  1114,
     194,  1120,   432,  1121,  1121,   725,     1,   432,   726,   727,
     728,   729,   730,   735,   474,   512,    17,   391,  1084,  1081,
     269,   271,   507,  1126,   310,   394,  1144,   355,  1126,  1121,
      54,  1113,   108,   212,  1123,  1123,  1081,  1146,   375,  1121,
      36,  1111,   698,   662,   701,    21,    33,    36,    37,    38,
      39,    40,    41,    42,    71,    73,    74,    75,    76,    77,
      78,   113,   195,   211,   245,   267,   282,   289,   291,   304,
     314,   321,   358,   360,   361,   362,   384,   409,   410,   411,
     422,   425,   624,   625,   626,   628,   629,   630,   631,   632,
     633,   642,   643,   645,   646,   647,   652,   653,  1121,  1137,
      26,  1109,   182,  1081,    55,   312,   590,   601,  1081,   363,
    1138,   228,   598,  1078,   598,   121,   445,   445,   347,     3,
       5,    10,    18,    50,    51,    58,    69,    72,    84,   106,
     113,   114,   144,   156,   160,   173,   180,   183,   184,   191,
     198,   200,   203,   238,   242,   244,   251,   273,   288,   309,
     318,   331,   336,   338,   346,   356,   365,   374,   376,   377,
     380,   382,   387,   402,   407,   412,   423,   435,   445,   736,
     737,   747,   752,   756,   759,   772,   775,   780,   785,   786,
     787,   790,   792,   799,   803,   805,   820,   823,   825,   827,
     830,   832,   838,   847,   849,   866,   868,   871,   875,   881,
     891,   898,   900,   903,   907,   908,   919,   930,   940,   946,
     949,   955,   959,   961,   963,   965,   968,   979,   980,   989,
     991,   992,   445,   513,   515,   375,  1139,  1121,  1123,   118,
     162,   542,  1121,   310,   317,   559,  1121,  1121,  1121,  1121,
    1108,     9,   252,   309,   566,  1121,   432,   355,   663,   617,
     622,   702,   703,   704,   219,   359,   408,   359,   408,   359,
     408,   359,   408,   359,   408,   428,  1145,   337,  1134,  1081,
    1077,  1078,  1078,   208,   218,   337,   644,  1121,  1122,   162,
     182,   217,   401,     9,    49,   219,   621,  1082,  1083,  1084,
      29,   602,   603,   604,   605,  1110,  1146,  1114,   174,   593,
    1119,   104,   228,   731,   738,   748,   753,   757,   760,   773,
     776,   781,   788,   791,   793,   800,   804,   806,   821,   824,
     826,  1144,   831,     1,   833,   839,   848,   850,   867,   869,
     872,   876,   882,   892,   899,   901,   904,   909,   920,   931,
     941,   228,   340,   950,   956,   297,   960,   962,   964,   966,
     969,   182,   981,  1118,   993,   189,   228,   235,   306,   369,
     438,   514,   516,  1121,   118,   307,   355,   545,  1121,   112,
     296,   541,    31,   159,   236,   555,  1062,   372,  1060,  1060,
     278,  1131,  1131,   272,  1060,    59,    85,    86,   284,   445,
     664,   665,   669,  1121,   618,   704,   438,   394,   634,   448,
    1079,  1080,   391,   631,   649,   650,  1082,    26,   627,   353,
    1100,  1100,  1084,   268,  1128,  1128,   452,    47,   400,   169,
     594,  1081,   445,   445,   739,  1076,  1077,     6,    79,    90,
      94,   178,   219,   224,   230,   233,   265,   333,   378,   379,
     403,   421,   429,   749,  1046,  1066,  1067,  1076,  1082,  1085,
     432,   754,  1033,  1034,  1035,   228,  1056,  1057,  1058,  1078,
     228,  1074,  1076,  1085,   774,   777,   782,  1047,  1048,  1067,
    1052,   396,   228,   794,  1066,  1073,  1076,   801,  1067,   228,
     395,   399,   807,   808,  1033,   287,   288,   301,   347,   822,
       6,  1064,  1065,  1076,  1076,   828,   131,  1032,  1033,  1064,
     668,  1076,   851,  1076,  1082,  1085,   932,  1078,    90,   870,
    1067,   873,  1067,   877,   172,   228,   883,   886,   887,   888,
    1056,  1074,  1078,  1146,  1052,  1049,  1078,  1052,  1049,     9,
     910,  1050,  1078,   145,   240,   921,   922,   923,   924,   926,
     927,   928,   929,  1053,  1054,  1064,   932,  1052,   947,   107,
     951,   952,  1067,    90,   957,  1066,   668,  1076,  1052,  1076,
       8,    34,   983,   102,  1049,    17,  1063,  1060,   113,   228,
     543,  1078,   431,   556,   556,   367,   446,   550,  1060,  1061,
    1121,   167,   666,   667,   666,  1122,   677,   182,   705,  1081,
     393,  1143,   219,   439,   440,   448,  1043,  1045,  1046,  1068,
    1076,  1083,  1085,   448,  1080,  1078,   648,   650,   391,   228,
    1113,  1077,  1077,  1084,  1062,  1062,  1110,  1114,   122,   746,
      29,   174,   740,  1110,  1128,   448,  1076,   448,  1086,   448,
    1087,  1128,  1101,   448,   448,   448,   448,   448,   448,   448,
     448,  1086,   123,   751,   394,   750,  1067,   199,  1095,    55,
    1036,  1037,   394,  1101,   424,   761,   228,  1073,  1076,  1052,
     125,   783,   151,   446,   784,  1048,   339,  1099,  1133,  1051,
     127,   798,   740,   417,   418,   419,   420,   128,   802,    48,
     204,   761,    17,   428,   809,   810,   811,   815,  1106,    96,
    1128,  1065,  1055,   390,  1142,   840,  1146,  1076,    89,   322,
     385,   852,   853,   854,   858,   863,   934,  1067,   394,   132,
     874,    48,   161,   201,   209,   279,   878,   887,   133,   884,
     413,   426,   391,   393,   388,   250,   295,  1096,   174,   994,
    1133,   994,  1050,   138,   918,   426,   912,  1071,  1076,  1083,
     927,   929,  1064,   394,  1054,   116,   394,   414,   925,   942,
     181,   332,   948,  1112,   204,   952,  1076,   141,   958,   174,
     174,   310,   312,   967,   107,   970,   324,   371,   984,   271,
    1129,   994,   516,   117,   431,   550,  1094,  1103,   232,   338,
    1121,   547,   548,  1073,   668,   675,  1081,   617,   678,   706,
     109,   635,  1128,  1045,  1045,  1045,    68,   351,   447,  1044,
     439,   440,   441,   442,   444,   451,  1045,  1145,  1082,  1125,
    1062,   109,   592,  1071,    24,    25,    65,    67,    98,    99,
     100,   145,   147,   155,   226,   392,   432,  1054,   431,   743,
      64,   225,   292,   741,   742,   144,   301,  1069,  1077,  1043,
    1045,   394,  1045,  1043,  1088,  1077,  1083,  1085,   432,  1045,
    1091,  1045,  1045,  1090,  1045,  1043,  1043,  1045,  1089,  1045,
    1047,  1067,   181,   332,   755,  1095,    12,    13,    14,    20,
      57,   151,   152,   179,   185,   208,   216,   220,   248,   249,
     253,   263,   270,   275,   293,   438,   439,   440,   441,   442,
     444,   446,   447,   449,   450,  1038,  1039,  1040,  1041,  1042,
     208,   248,   253,   439,   440,   444,   448,  1038,  1039,  1040,
    1041,  1042,  1067,   300,   758,  1058,   762,   181,   332,   766,
     315,   406,   778,   779,  1146,  1033,   207,   257,  1025,  1026,
    1027,  1029,   416,   431,   795,  1146,   158,  1000,  1001,  1000,
    1000,  1000,  1067,  1047,  1067,    21,   395,   399,   816,   817,
    1034,   129,   819,   430,   811,   813,   428,   812,   808,  1077,
     109,   829,  1056,   834,     9,    12,    15,    16,   245,   246,
     263,   264,   841,   845,   166,  1071,     9,    55,   168,   217,
     401,   859,   860,   861,   855,   853,   936,  1103,  1129,   394,
    1064,  1047,  1067,   357,   879,   732,   733,  1032,   889,   890,
    1076,  1056,     8,    34,   996,  1133,  1073,   204,   893,   905,
    1146,   913,  1110,  1076,   913,   394,   394,   507,   144,   395,
     399,  1067,    48,   212,   943,  1067,  1067,   363,  1067,  1076,
     174,  1047,  1067,  1071,  1112,   204,   973,  1076,   154,   158,
     985,     9,   990,  1056,   905,   117,   547,   271,   549,  1060,
     549,   187,   670,   225,   226,   676,   432,   618,    30,    32,
      35,    43,    44,    45,    64,   153,   171,   174,   175,   188,
     225,   234,   267,   281,   305,   329,   334,   348,   394,   405,
     424,   445,   629,   630,   632,   642,   645,   647,   707,   710,
    1129,   636,   637,  1077,  1083,  1085,   447,  1045,  1045,  1045,
    1045,  1045,  1045,   447,  1045,   356,  1135,  1125,  1129,   999,
    1001,   437,   436,  1071,   999,   212,    30,    32,    35,    45,
     171,   175,   188,   234,   281,   305,   329,   334,   344,   348,
     405,   415,   744,   745,   999,   261,  1127,  1127,  1127,   742,
     741,   228,  1070,  1077,   447,  1076,   451,   447,  1044,   447,
     447,  1044,   447,   447,   447,   447,  1044,   447,   447,   364,
    1005,  1006,  1047,  1065,   332,  1144,   389,  1141,  1141,   394,
    1056,   763,   764,   765,  1112,  1076,  1076,   158,   280,   767,
     986,  1118,   232,   252,  1005,  1028,  1030,   126,   789,  1029,
      92,   296,   432,  1054,    32,    35,    43,    44,    45,   153,
     171,   188,   234,   281,   334,   344,   405,   796,   797,  1000,
     260,  1002,   256,  1003,   181,  1005,   181,  1106,   391,   818,
     814,   816,   732,  1129,   732,  1144,   322,   842,  1144,   394,
      48,   860,   862,  1071,     9,    55,   217,   401,   856,   857,
    1071,   937,  1104,   194,   276,  1130,    27,   110,   638,  1064,
    1005,   181,  1146,  1051,   133,   885,   734,     8,   174,   893,
    1076,   121,   254,  1015,  1016,  1018,  1025,   232,   252,   428,
     121,   428,   915,   916,  1071,  1070,  1067,  1121,  1025,   953,
    1146,  1076,  1005,   181,   394,     9,   971,   972,  1093,   974,
    1076,   953,   974,   298,   988,   299,   995,   996,  1094,   243,
     310,   312,   557,  1121,   168,   671,  1081,   679,  1121,  1127,
     148,   150,  1121,  1074,  1127,  1081,  1076,  1076,  1060,   196,
     639,   638,   447,  1144,  1060,  1003,   999,  1121,  1121,   116,
     414,   745,  1073,  1073,  1073,  1086,  1099,   447,  1045,  1060,
    1086,  1086,  1045,  1086,  1086,  1086,   217,   401,  1086,  1086,
    1007,   259,  1008,  1005,  1065,   275,   275,   764,   270,   720,
      83,   316,   425,   256,   258,   769,   987,   768,   320,   335,
     732,   732,   795,   795,   795,   795,  1121,   148,   150,  1121,
     116,   414,   797,   732,  1004,  1047,  1048,  1047,  1048,   817,
    1033,   732,  1076,   120,   835,   425,   843,   844,   845,   105,
     846,   425,  1072,  1076,  1082,  1071,    48,   864,   857,   170,
     864,   933,  1121,   276,  1123,  1047,   566,   880,  1146,   735,
     890,  1067,   193,   894,  1146,  1017,  1019,   136,   902,  1018,
     137,   906,   232,  1033,   914,  1032,   915,   253,   944,  1097,
     139,   945,   280,  1010,  1011,   291,  1099,  1047,  1072,   275,
    1071,   108,   975,   385,   977,  1129,   149,   255,   997,  1020,
    1021,  1023,  1026,     7,  1105,   557,  1081,   111,   214,   672,
      65,    64,    65,   186,   225,   226,   250,   294,   367,   381,
     404,   426,   445,   629,   630,   632,   633,   642,   645,   647,
     680,   681,   683,   684,   685,   686,   688,   689,   690,   691,
     695,   696,   438,  1075,  1076,  1081,  1121,  1075,  1121,  1143,
    1112,  1123,   395,   651,  1075,  1075,  1031,  1112,  1031,  1005,
     447,   732,  1009,   151,   151,  1067,   124,   771,   770,   732,
    1000,  1000,  1000,  1000,  1075,  1075,  1031,  1031,   732,  1005,
     319,  1005,   319,   836,   131,   837,   844,    97,  1116,   864,
     864,  1072,   996,   201,   424,   938,  1060,   935,  1005,   232,
     252,    48,   232,   212,   895,   192,   232,   252,   427,   732,
     732,   911,   732,   917,   668,  1038,  1039,  1040,  1041,  1042,
    1012,   140,   954,   258,  1013,  1076,  1005,  1005,   972,  1120,
      91,   976,  1120,  1010,   161,   201,   209,   279,   982,  1051,
    1022,  1024,   143,   998,  1023,   284,  1054,  1075,  1121,    88,
     215,   673,   262,  1127,   197,   697,   261,   262,   694,  1107,
     186,   428,  1121,  1128,  1121,  1076,   686,   250,   290,   692,
     693,  1081,   239,   290,   439,   440,   709,   239,   290,   439,
     440,   708,   432,   640,   641,  1121,  1121,  1075,   732,  1144,
    1144,   732,  1048,  1048,   732,    48,   864,   397,   865,   298,
    1051,   181,   279,   939,  1078,   335,  1067,  1121,   896,  1015,
    1026,   232,   232,   732,   732,   732,  1014,  1076,  1120,  1076,
     142,   978,   732,   732,   225,   226,  1124,  1081,  1121,  1121,
     169,   674,  1121,  1122,  1121,  1032,  1076,   687,  1060,    87,
      88,   111,   285,   286,   326,   327,   682,   174,   284,  1081,
     693,  1075,  1075,   641,  1059,  1082,  1124,  1005,  1005,  1067,
    1067,  1121,  1051,   298,   413,   668,   135,   897,   732,  1076,
    1081,  1081,  1121,  1081,  1081,  1099,  1067,   886,  1121,  1032,
    1081,    48,   886,  1067
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

  case 186:

/* Line 1455 of yacc.c  */
#line 1697 "parser.y"
    {
	current_file->external_assign = 0;
  ;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1705 "parser.y"
    {
	const char	*s;

	s = "$#@DUMMY@#$";
	(yyval) = cb_build_alphanumeric_literal ((unsigned char *)s, strlen (s));
  ;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1722 "parser.y"
    { current_file->access_mode = COB_ACCESS_SEQUENTIAL; ;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1723 "parser.y"
    { current_file->access_mode = COB_ACCESS_DYNAMIC; ;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1724 "parser.y"
    { current_file->access_mode = COB_ACCESS_RANDOM; ;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1732 "parser.y"
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
#line 1752 "parser.y"
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
#line 1798 "parser.y"
    {
	key_component_list = NULL;
  ;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1807 "parser.y"
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
#line 1822 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 1823 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 1824 "parser.y"
    { (yyval) = cb_int('='); ;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 1831 "parser.y"
    {
	PENDING ("COLLATING SEQUENCE");
  ;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1841 "parser.y"
    {
	current_file->file_status = (yyvsp[(4) - (5)]);
	if ((yyvsp[(5) - (5)])) {
		PENDING ("2nd FILE STATUS");
	}
  ;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1862 "parser.y"
    { current_file->lock_mode = COB_LOCK_MANUAL; ;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1863 "parser.y"
    { current_file->lock_mode = COB_LOCK_AUTOMATIC; ;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1864 "parser.y"
    { current_file->lock_mode = COB_LOCK_EXCLUSIVE; ;}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1870 "parser.y"
    {
	current_file->lock_mode |= COB_LOCK_MULTIPLE;
  ;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1873 "parser.y"
    { PENDING ("WITH ROLLBACK"); ;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1890 "parser.y"
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
#line 1899 "parser.y"
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
#line 1908 "parser.y"
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
#line 1917 "parser.y"
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
#line 1932 "parser.y"
    {
	cb_verify (cb_padding_character_clause, "PADDING CHARACTER");
  ;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1941 "parser.y"
    { /* ignored */ ;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1949 "parser.y"
    {
	current_file->key = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1953 "parser.y"
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

  case 228:

/* Line 1455 of yacc.c  */
#line 1990 "parser.y"
    { current_file->key = (yyvsp[(4) - (4)]); ;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 1997 "parser.y"
    { /* ignored */ ;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 2004 "parser.y"
    { current_file->sharing = (yyvsp[(3) - (3)]); ;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 2008 "parser.y"
    { (yyval) = NULL; PENDING ("SHARING ALL OTHER"); ;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 2009 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 2010 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 2040 "parser.y"
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

  case 243:

/* Line 1455 of yacc.c  */
#line 2064 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 2065 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 2066 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 2067 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 2074 "parser.y"
    {
	cb_verify (cb_multiple_file_tape_clause, "MULTIPLE FILE TAPE");
  ;}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 2085 "parser.y"
    { ;}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 2113 "parser.y"
    { current_storage = CB_STORAGE_FILE; ;}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 2116 "parser.y"
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

  case 262:

/* Line 1455 of yacc.c  */
#line 2135 "parser.y"
    {
	if ((yyvsp[(3) - (3)]) && (yyvsp[(3) - (3)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(3) - (3)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 2147 "parser.y"
    {
	if ((yyvsp[(2) - (2)]) && (yyvsp[(2) - (2)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(2) - (2)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 2158 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 2159 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 2169 "parser.y"
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

  case 268:

/* Line 1455 of yacc.c  */
#line 2180 "parser.y"
    {
	/* Shut up bison */
	dummy_tree = (yyvsp[(2) - (4)]);
  ;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 2192 "parser.y"
    {
	if (current_file->global) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->external = 1;
  ;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 2199 "parser.y"
    {
	if (current_file->external) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->global = 1;
  ;}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 2221 "parser.y"
    { /* ignored */ ;}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 2231 "parser.y"
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

  case 287:

/* Line 1455 of yacc.c  */
#line 2243 "parser.y"
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

  case 288:

/* Line 1455 of yacc.c  */
#line 2269 "parser.y"
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

  case 290:

/* Line 1455 of yacc.c  */
#line 2293 "parser.y"
    {
	current_file->record_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 2299 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 2300 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 2304 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 2305 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 2313 "parser.y"
    {
	cb_verify (cb_label_records_clause, "LABEL RECORDS");
  ;}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 2328 "parser.y"
    {
	cb_verify (cb_value_of_clause, "VALUE OF");
  ;}
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 2332 "parser.y"
    {
	if (!current_file->assign) {
		current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 2348 "parser.y"
    {
	cb_verify (cb_data_records_clause, "DATA RECORDS");
  ;}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 2359 "parser.y"
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

  case 309:

/* Line 1455 of yacc.c  */
#line 2387 "parser.y"
    {
	current_file->latfoot = (yyvsp[(4) - (5)]);
  ;}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 2394 "parser.y"
    {
	current_file->lattop = (yyvsp[(3) - (4)]);
  ;}
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 2401 "parser.y"
    {
	current_file->latbot = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 2410 "parser.y"
    { /* ignore */ ;}
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 2418 "parser.y"
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

  case 314:

/* Line 1455 of yacc.c  */
#line 2436 "parser.y"
    {
	cb_warning (_("file descriptor REPORT IS"));
  ;}
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 2440 "parser.y"
    {
	cb_warning (_("file descriptor REPORTS ARE"));
  ;}
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 2451 "parser.y"
    { current_storage = CB_STORAGE_WORKING; ;}
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 2453 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->working_storage =
			cb_field_add (current_program->working_storage, CB_FIELD ((yyvsp[(5) - (5)])));
	}
  ;}
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 2462 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 2463 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 2467 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 2473 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	(yyval) = CB_TREE (description_field);
  ;}
    break;

  case 327:

/* Line 1455 of yacc.c  */
#line 2493 "parser.y"
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

  case 328:

/* Line 1455 of yacc.c  */
#line 2504 "parser.y"
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

  case 330:

/* Line 1455 of yacc.c  */
#line 2529 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 2535 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 2541 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 2550 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 335:

/* Line 1455 of yacc.c  */
#line 2559 "parser.y"
    {
	current_field->flag_is_global = 1;
	cb_error (_("CONSTANT with GLOBAL clause is not yet supported"));
  ;}
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 2566 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 2567 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 2568 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 2573 "parser.y"
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

  case 340:

/* Line 1455 of yacc.c  */
#line 2592 "parser.y"
    {
	/* required to check redefines */
	(yyval) = NULL;
  ;}
    break;

  case 341:

/* Line 1455 of yacc.c  */
#line 2598 "parser.y"
    {
	/* required to check redefines */
	(yyval) = cb_true;
  ;}
    break;

  case 356:

/* Line 1455 of yacc.c  */
#line 2626 "parser.y"
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

  case 357:

/* Line 1455 of yacc.c  */
#line 2648 "parser.y"
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

  case 358:

/* Line 1455 of yacc.c  */
#line 2669 "parser.y"
    { current_field->ename = NULL; ;}
    break;

  case 359:

/* Line 1455 of yacc.c  */
#line 2671 "parser.y"
    {
	struct cb_field *x;

	x = CB_FIELD(cb_build_field (cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(2) - (2)]))->data))));
	current_field->ename = x->name;
 ;}
    break;

  case 360:

/* Line 1455 of yacc.c  */
#line 2683 "parser.y"
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

  case 361:

/* Line 1455 of yacc.c  */
#line 2702 "parser.y"
    { current_field->pic = CB_PICTURE ((yyvsp[(1) - (1)])); ;}
    break;

  case 364:

/* Line 1455 of yacc.c  */
#line 2714 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 365:

/* Line 1455 of yacc.c  */
#line 2715 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 366:

/* Line 1455 of yacc.c  */
#line 2716 "parser.y"
    { current_field->usage = CB_USAGE_FLOAT; ;}
    break;

  case 367:

/* Line 1455 of yacc.c  */
#line 2717 "parser.y"
    { current_field->usage = CB_USAGE_DOUBLE; ;}
    break;

  case 368:

/* Line 1455 of yacc.c  */
#line 2718 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 369:

/* Line 1455 of yacc.c  */
#line 2719 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 370:

/* Line 1455 of yacc.c  */
#line 2720 "parser.y"
    { current_field->usage = CB_USAGE_COMP_5; ;}
    break;

  case 371:

/* Line 1455 of yacc.c  */
#line 2721 "parser.y"
    { current_field->usage = CB_USAGE_COMP_X; ;}
    break;

  case 372:

/* Line 1455 of yacc.c  */
#line 2722 "parser.y"
    { current_field->usage = CB_USAGE_DISPLAY; ;}
    break;

  case 373:

/* Line 1455 of yacc.c  */
#line 2723 "parser.y"
    { current_field->usage = CB_USAGE_INDEX; ;}
    break;

  case 374:

/* Line 1455 of yacc.c  */
#line 2724 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 375:

/* Line 1455 of yacc.c  */
#line 2726 "parser.y"
    {
	current_field->usage = CB_USAGE_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 376:

/* Line 1455 of yacc.c  */
#line 2731 "parser.y"
    {
	current_field->usage = CB_USAGE_PROGRAM_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 377:

/* Line 1455 of yacc.c  */
#line 2735 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 378:

/* Line 1455 of yacc.c  */
#line 2736 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 379:

/* Line 1455 of yacc.c  */
#line 2737 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 380:

/* Line 1455 of yacc.c  */
#line 2738 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 381:

/* Line 1455 of yacc.c  */
#line 2739 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 382:

/* Line 1455 of yacc.c  */
#line 2740 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 383:

/* Line 1455 of yacc.c  */
#line 2741 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 384:

/* Line 1455 of yacc.c  */
#line 2742 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_CHAR; ;}
    break;

  case 385:

/* Line 1455 of yacc.c  */
#line 2743 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 386:

/* Line 1455 of yacc.c  */
#line 2744 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 387:

/* Line 1455 of yacc.c  */
#line 2745 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 388:

/* Line 1455 of yacc.c  */
#line 2746 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 389:

/* Line 1455 of yacc.c  */
#line 2747 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 390:

/* Line 1455 of yacc.c  */
#line 2748 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 391:

/* Line 1455 of yacc.c  */
#line 2749 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 392:

/* Line 1455 of yacc.c  */
#line 2750 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 393:

/* Line 1455 of yacc.c  */
#line 2751 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 394:

/* Line 1455 of yacc.c  */
#line 2752 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 395:

/* Line 1455 of yacc.c  */
#line 2754 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  ;}
    break;

  case 396:

/* Line 1455 of yacc.c  */
#line 2762 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_UNSIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_UNSIGNED_LONG;
	}
  ;}
    break;

  case 397:

/* Line 1455 of yacc.c  */
#line 2770 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  ;}
    break;

  case 398:

/* Line 1455 of yacc.c  */
#line 2777 "parser.y"
    { PENDING ("USAGE NATIONAL");;}
    break;

  case 399:

/* Line 1455 of yacc.c  */
#line 2785 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 1;
  ;}
    break;

  case 400:

/* Line 1455 of yacc.c  */
#line 2790 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 0;
  ;}
    break;

  case 401:

/* Line 1455 of yacc.c  */
#line 2802 "parser.y"
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

  case 402:

/* Line 1455 of yacc.c  */
#line 2817 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 403:

/* Line 1455 of yacc.c  */
#line 2818 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 405:

/* Line 1455 of yacc.c  */
#line 2823 "parser.y"
    {
	current_field->occurs_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 406:

/* Line 1455 of yacc.c  */
#line 2830 "parser.y"
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

  case 407:

/* Line 1455 of yacc.c  */
#line 2853 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 408:

/* Line 1455 of yacc.c  */
#line 2856 "parser.y"
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

  case 409:

/* Line 1455 of yacc.c  */
#line 2871 "parser.y"
    { (yyval) = cb_int (COB_ASCENDING); ;}
    break;

  case 410:

/* Line 1455 of yacc.c  */
#line 2872 "parser.y"
    { (yyval) = cb_int (COB_DESCENDING); ;}
    break;

  case 412:

/* Line 1455 of yacc.c  */
#line 2877 "parser.y"
    {
	current_field->index_list = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 413:

/* Line 1455 of yacc.c  */
#line 2883 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 414:

/* Line 1455 of yacc.c  */
#line 2885 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 415:

/* Line 1455 of yacc.c  */
#line 2890 "parser.y"
    {
	(yyval) = cb_build_index ((yyvsp[(1) - (1)]), cb_int1, 1, current_field);
  ;}
    break;

  case 416:

/* Line 1455 of yacc.c  */
#line 2899 "parser.y"
    { current_field->flag_justified = 1; ;}
    break;

  case 417:

/* Line 1455 of yacc.c  */
#line 2906 "parser.y"
    { current_field->flag_synchronized = 1; ;}
    break;

  case 421:

/* Line 1455 of yacc.c  */
#line 2918 "parser.y"
    { current_field->flag_blank_zero = 1; ;}
    break;

  case 422:

/* Line 1455 of yacc.c  */
#line 2926 "parser.y"
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

  case 423:

/* Line 1455 of yacc.c  */
#line 2950 "parser.y"
    { current_field->values = (yyvsp[(3) - (3)]); ;}
    break;

  case 425:

/* Line 1455 of yacc.c  */
#line 2955 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 426:

/* Line 1455 of yacc.c  */
#line 2956 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 427:

/* Line 1455 of yacc.c  */
#line 2960 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 428:

/* Line 1455 of yacc.c  */
#line 2961 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 430:

/* Line 1455 of yacc.c  */
#line 2966 "parser.y"
    {
	if (current_field->level != 88) {
		cb_error (_("FALSE clause only allowed for 88 level"));
	}
	current_field->false_88 = cb_list_init ((yyvsp[(3) - (3)]));
  ;}
    break;

  case 431:

/* Line 1455 of yacc.c  */
#line 2979 "parser.y"
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

  case 432:

/* Line 1455 of yacc.c  */
#line 2991 "parser.y"
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

  case 433:

/* Line 1455 of yacc.c  */
#line 3011 "parser.y"
    {
	if (current_field->flag_item_based) {
		cb_error (_("BASED and ANY LENGTH are mutually exclusive"));
	} else {
		current_field->flag_any_length = 1;
	}
  ;}
    break;

  case 435:

/* Line 1455 of yacc.c  */
#line 3026 "parser.y"
    {
	current_storage = CB_STORAGE_LOCAL;
	if (current_program->nested_level) {
		cb_error (_("LOCAL-STORAGE not allowed in nested programs"));
	}
  ;}
    break;

  case 436:

/* Line 1455 of yacc.c  */
#line 3033 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->local_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 438:

/* Line 1455 of yacc.c  */
#line 3046 "parser.y"
    { current_storage = CB_STORAGE_LINKAGE; ;}
    break;

  case 439:

/* Line 1455 of yacc.c  */
#line 3048 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->linkage_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 441:

/* Line 1455 of yacc.c  */
#line 3061 "parser.y"
    {
	cb_error (_("REPORT SECTION not supported"));
	current_storage = CB_STORAGE_REPORT;
  ;}
    break;

  case 448:

/* Line 1455 of yacc.c  */
#line 3094 "parser.y"
    {
	cb_warning (_("Report description using defaults"));
  ;}
    break;

  case 450:

/* Line 1455 of yacc.c  */
#line 3102 "parser.y"
    {
	cb_error (_("GLOBAL is not allowed with RD"));
  ;}
    break;

  case 459:

/* Line 1455 of yacc.c  */
#line 3125 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 460:

/* Line 1455 of yacc.c  */
#line 3126 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 482:

/* Line 1455 of yacc.c  */
#line 3182 "parser.y"
    { cb_warning (_("looking for Report line TYPE")); ;}
    break;

  case 533:

/* Line 1455 of yacc.c  */
#line 3287 "parser.y"
    { current_storage = CB_STORAGE_SCREEN; ;}
    break;

  case 534:

/* Line 1455 of yacc.c  */
#line 3288 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 535:

/* Line 1455 of yacc.c  */
#line 3294 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	current_program->screen_storage = description_field;
	current_program->flag_screen = 1;
  ;}
    break;

  case 541:

/* Line 1455 of yacc.c  */
#line 3318 "parser.y"
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

  case 542:

/* Line 1455 of yacc.c  */
#line 3334 "parser.y"
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

  case 545:

/* Line 1455 of yacc.c  */
#line 3358 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 546:

/* Line 1455 of yacc.c  */
#line 3359 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 547:

/* Line 1455 of yacc.c  */
#line 3360 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BELL; ;}
    break;

  case 548:

/* Line 1455 of yacc.c  */
#line 3361 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLINK; ;}
    break;

  case 549:

/* Line 1455 of yacc.c  */
#line 3362 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 550:

/* Line 1455 of yacc.c  */
#line 3363 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 551:

/* Line 1455 of yacc.c  */
#line 3364 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 552:

/* Line 1455 of yacc.c  */
#line 3365 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 553:

/* Line 1455 of yacc.c  */
#line 3366 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REVERSE; ;}
    break;

  case 554:

/* Line 1455 of yacc.c  */
#line 3367 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 555:

/* Line 1455 of yacc.c  */
#line 3368 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_OVERLINE; ;}
    break;

  case 556:

/* Line 1455 of yacc.c  */
#line 3369 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_AUTO; ;}
    break;

  case 557:

/* Line 1455 of yacc.c  */
#line 3370 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_SECURE; ;}
    break;

  case 558:

/* Line 1455 of yacc.c  */
#line 3371 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REQUIRED; ;}
    break;

  case 559:

/* Line 1455 of yacc.c  */
#line 3372 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_FULL; ;}
    break;

  case 560:

/* Line 1455 of yacc.c  */
#line 3373 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_PROMPT; ;}
    break;

  case 561:

/* Line 1455 of yacc.c  */
#line 3375 "parser.y"
    {
	current_field->screen_line = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 562:

/* Line 1455 of yacc.c  */
#line 3379 "parser.y"
    {
	current_field->screen_column = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 563:

/* Line 1455 of yacc.c  */
#line 3383 "parser.y"
    {
	current_field->screen_foreg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 564:

/* Line 1455 of yacc.c  */
#line 3387 "parser.y"
    {
	current_field->screen_backg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 572:

/* Line 1455 of yacc.c  */
#line 3398 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 573:

/* Line 1455 of yacc.c  */
#line 3405 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 574:

/* Line 1455 of yacc.c  */
#line 3409 "parser.y"
    {
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 575:

/* Line 1455 of yacc.c  */
#line 3418 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 576:

/* Line 1455 of yacc.c  */
#line 3422 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 577:

/* Line 1455 of yacc.c  */
#line 3426 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 578:

/* Line 1455 of yacc.c  */
#line 3430 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 579:

/* Line 1455 of yacc.c  */
#line 3434 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 580:

/* Line 1455 of yacc.c  */
#line 3441 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 581:

/* Line 1455 of yacc.c  */
#line 3445 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 582:

/* Line 1455 of yacc.c  */
#line 3449 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 583:

/* Line 1455 of yacc.c  */
#line 3453 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 584:

/* Line 1455 of yacc.c  */
#line 3457 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 585:

/* Line 1455 of yacc.c  */
#line 3465 "parser.y"
    {
	current_field->occurs_max = cb_get_int ((yyvsp[(2) - (3)]));
	current_field->occurs_min = current_field->occurs_max;
	current_field->indexes++;
	current_field->flag_occurs = 1;
  ;}
    break;

  case 587:

/* Line 1455 of yacc.c  */
#line 3479 "parser.y"
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

  case 588:

/* Line 1455 of yacc.c  */
#line 3489 "parser.y"
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

  case 589:

/* Line 1455 of yacc.c  */
#line 3499 "parser.y"
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

  case 590:

/* Line 1455 of yacc.c  */
#line 3516 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 591:

/* Line 1455 of yacc.c  */
#line 3518 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 592:

/* Line 1455 of yacc.c  */
#line 3522 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 593:

/* Line 1455 of yacc.c  */
#line 3524 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	current_program->flag_chained = 1;
  ;}
    break;

  case 594:

/* Line 1455 of yacc.c  */
#line 3528 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 595:

/* Line 1455 of yacc.c  */
#line 3532 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 596:

/* Line 1455 of yacc.c  */
#line 3534 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 597:

/* Line 1455 of yacc.c  */
#line 3539 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), cb_build_identifier ((yyvsp[(4) - (4)])));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 599:

/* Line 1455 of yacc.c  */
#line 3548 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 600:

/* Line 1455 of yacc.c  */
#line 3552 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 602:

/* Line 1455 of yacc.c  */
#line 3564 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_AUTO;
	}
  ;}
    break;

  case 603:

/* Line 1455 of yacc.c  */
#line 3572 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_4;
	}
  ;}
    break;

  case 604:

/* Line 1455 of yacc.c  */
#line 3580 "parser.y"
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

  case 605:

/* Line 1455 of yacc.c  */
#line 3609 "parser.y"
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

  case 607:

/* Line 1455 of yacc.c  */
#line 3642 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OPTIONAL only allowed for BY REFERENCE items"));
	}
  ;}
    break;

  case 608:

/* Line 1455 of yacc.c  */
#line 3651 "parser.y"
    {
	if (current_program->prog_type == CB_FUNCTION_TYPE) {
		cb_error (_("RETURNING clause is required for a FUNCTION"));
	}
  ;}
    break;

  case 609:

/* Line 1455 of yacc.c  */
#line 3657 "parser.y"
    {
	if (cb_ref ((yyvsp[(2) - (2)])) != cb_error_node) {
		current_program->returning = (yyvsp[(2) - (2)]);
		if (cb_field ((yyvsp[(2) - (2)]))->storage != CB_STORAGE_LINKAGE) {
			cb_error (_("RETURNING item is not defined in LINKAGE SECTION"));
		}
	}
  ;}
    break;

  case 611:

/* Line 1455 of yacc.c  */
#line 3668 "parser.y"
    { in_declaratives = 1; ;}
    break;

  case 612:

/* Line 1455 of yacc.c  */
#line 3671 "parser.y"
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

  case 618:

/* Line 1455 of yacc.c  */
#line 3704 "parser.y"
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

  case 619:

/* Line 1455 of yacc.c  */
#line 3720 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 620:

/* Line 1455 of yacc.c  */
#line 3732 "parser.y"
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

  case 621:

/* Line 1455 of yacc.c  */
#line 3763 "parser.y"
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

  case 622:

/* Line 1455 of yacc.c  */
#line 3800 "parser.y"
    {
	non_const_word = 0;
	check_unreached = 0;
	if ((yyvsp[(1) - (1)]) != cb_error_node) {
		cb_error_x ((yyvsp[(1) - (1)]), _("Unknown statement '%s'"), CB_NAME ((yyvsp[(1) - (1)])));
	}
	YYERROR;
  ;}
    break;

  case 623:

/* Line 1455 of yacc.c  */
#line 3811 "parser.y"
    { (yyval) = cb_build_section_name ((yyvsp[(1) - (1)]), 0); ;}
    break;

  case 625:

/* Line 1455 of yacc.c  */
#line 3815 "parser.y"
    { /* ignore */ ;}
    break;

  case 626:

/* Line 1455 of yacc.c  */
#line 3824 "parser.y"
    {
	(yyval) = current_program->exec_list;
	current_program->exec_list = NULL;
  ;}
    break;

  case 627:

/* Line 1455 of yacc.c  */
#line 3828 "parser.y"
    {
	(yyval) = CB_TREE (current_statement);
	current_statement = NULL;
  ;}
    break;

  case 628:

/* Line 1455 of yacc.c  */
#line 3833 "parser.y"
    {
	(yyval) = cb_list_reverse (current_program->exec_list);
	current_program->exec_list = (yyvsp[(1) - (3)]);
	current_statement = CB_STATEMENT ((yyvsp[(2) - (3)]));
  ;}
    break;

  case 629:

/* Line 1455 of yacc.c  */
#line 3841 "parser.y"
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

  case 680:

/* Line 1455 of yacc.c  */
#line 3913 "parser.y"
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

  case 681:

/* Line 1455 of yacc.c  */
#line 3935 "parser.y"
    {
	BEGIN_STATEMENT ("ACCEPT", TERM_ACCEPT);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 683:

/* Line 1455 of yacc.c  */
#line 3948 "parser.y"
    {
	cb_emit_accept ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 684:

/* Line 1455 of yacc.c  */
#line 3952 "parser.y"
    {
	PENDING ("ACCEPT .. FROM ESCAPE KEY");
  ;}
    break;

  case 685:

/* Line 1455 of yacc.c  */
#line 3956 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 0);
  ;}
    break;

  case 686:

/* Line 1455 of yacc.c  */
#line 3960 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 1);
  ;}
    break;

  case 687:

/* Line 1455 of yacc.c  */
#line 3964 "parser.y"
    {
	cb_emit_accept_date ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 688:

/* Line 1455 of yacc.c  */
#line 3968 "parser.y"
    {
	cb_emit_accept_date_yyyymmdd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 689:

/* Line 1455 of yacc.c  */
#line 3972 "parser.y"
    {
	cb_emit_accept_day ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 690:

/* Line 1455 of yacc.c  */
#line 3976 "parser.y"
    {
	cb_emit_accept_day_yyyyddd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 691:

/* Line 1455 of yacc.c  */
#line 3980 "parser.y"
    {
	cb_emit_accept_day_of_week ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 692:

/* Line 1455 of yacc.c  */
#line 3984 "parser.y"
    {
	cb_emit_accept_time ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 693:

/* Line 1455 of yacc.c  */
#line 3988 "parser.y"
    {
	cb_emit_accept_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 694:

/* Line 1455 of yacc.c  */
#line 3992 "parser.y"
    {
	cb_emit_accept_environment ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 695:

/* Line 1455 of yacc.c  */
#line 3996 "parser.y"
    { 
	cb_emit_get_environment ((yyvsp[(4) - (5)]), (yyvsp[(1) - (5)]));
  ;}
    break;

  case 696:

/* Line 1455 of yacc.c  */
#line 4000 "parser.y"
    {
	cb_emit_accept_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 697:

/* Line 1455 of yacc.c  */
#line 4004 "parser.y"
    {
	cb_emit_accept_arg_value ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 698:

/* Line 1455 of yacc.c  */
#line 4008 "parser.y"
    {
	cb_emit_accept_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 699:

/* Line 1455 of yacc.c  */
#line 4012 "parser.y"
    {
	cb_emit_accept_name ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 700:

/* Line 1455 of yacc.c  */
#line 4018 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 701:

/* Line 1455 of yacc.c  */
#line 4019 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 702:

/* Line 1455 of yacc.c  */
#line 4020 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); ;}
    break;

  case 703:

/* Line 1455 of yacc.c  */
#line 4021 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), NULL); ;}
    break;

  case 704:

/* Line 1455 of yacc.c  */
#line 4022 "parser.y"
    { (yyval) = cb_build_pair (NULL, (yyvsp[(2) - (2)])); ;}
    break;

  case 705:

/* Line 1455 of yacc.c  */
#line 4023 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 706:

/* Line 1455 of yacc.c  */
#line 4027 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 707:

/* Line 1455 of yacc.c  */
#line 4031 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 708:

/* Line 1455 of yacc.c  */
#line 4032 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 713:

/* Line 1455 of yacc.c  */
#line 4045 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 714:

/* Line 1455 of yacc.c  */
#line 4046 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 715:

/* Line 1455 of yacc.c  */
#line 4047 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 716:

/* Line 1455 of yacc.c  */
#line 4048 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 717:

/* Line 1455 of yacc.c  */
#line 4049 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 718:

/* Line 1455 of yacc.c  */
#line 4050 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 719:

/* Line 1455 of yacc.c  */
#line 4051 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 720:

/* Line 1455 of yacc.c  */
#line 4053 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 721:

/* Line 1455 of yacc.c  */
#line 4057 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 722:

/* Line 1455 of yacc.c  */
#line 4061 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 723:

/* Line 1455 of yacc.c  */
#line 4065 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 724:

/* Line 1455 of yacc.c  */
#line 4069 "parser.y"
    { dispattrs |= COB_SCREEN_AUTO; ;}
    break;

  case 725:

/* Line 1455 of yacc.c  */
#line 4070 "parser.y"
    { dispattrs |= COB_SCREEN_FULL; ;}
    break;

  case 726:

/* Line 1455 of yacc.c  */
#line 4071 "parser.y"
    { dispattrs |= COB_SCREEN_REQUIRED; ;}
    break;

  case 727:

/* Line 1455 of yacc.c  */
#line 4072 "parser.y"
    { dispattrs |= COB_SCREEN_SECURE; ;}
    break;

  case 728:

/* Line 1455 of yacc.c  */
#line 4073 "parser.y"
    { dispattrs |= COB_SCREEN_UPDATE; ;}
    break;

  case 729:

/* Line 1455 of yacc.c  */
#line 4074 "parser.y"
    { dispattrs |= COB_SCREEN_PROMPT; ;}
    break;

  case 730:

/* Line 1455 of yacc.c  */
#line 4078 "parser.y"
    { terminator_warning (TERM_ACCEPT); ;}
    break;

  case 731:

/* Line 1455 of yacc.c  */
#line 4079 "parser.y"
    { terminator_clear (TERM_ACCEPT); ;}
    break;

  case 732:

/* Line 1455 of yacc.c  */
#line 4088 "parser.y"
    { BEGIN_STATEMENT ("ADD", TERM_ADD); ;}
    break;

  case 734:

/* Line 1455 of yacc.c  */
#line 4095 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '+', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 735:

/* Line 1455 of yacc.c  */
#line 4099 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(4) - (5)]), 0, cb_build_binary_list ((yyvsp[(1) - (5)]), '+'));
  ;}
    break;

  case 736:

/* Line 1455 of yacc.c  */
#line 4103 "parser.y"
    {
	cb_emit_corresponding (cb_build_add, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 738:

/* Line 1455 of yacc.c  */
#line 4109 "parser.y"
    { cb_list_add ((yyvsp[(0) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 739:

/* Line 1455 of yacc.c  */
#line 4113 "parser.y"
    { terminator_warning (TERM_ADD); ;}
    break;

  case 740:

/* Line 1455 of yacc.c  */
#line 4114 "parser.y"
    { terminator_clear (TERM_ADD); ;}
    break;

  case 741:

/* Line 1455 of yacc.c  */
#line 4123 "parser.y"
    { BEGIN_STATEMENT ("ALLOCATE", 0); ;}
    break;

  case 743:

/* Line 1455 of yacc.c  */
#line 4129 "parser.y"
    {
	cb_emit_allocate ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), NULL, (yyvsp[(2) - (3)]));
  ;}
    break;

  case 744:

/* Line 1455 of yacc.c  */
#line 4133 "parser.y"
    {
	cb_emit_allocate (NULL, (yyvsp[(5) - (5)]), (yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]));
  ;}
    break;

  case 745:

/* Line 1455 of yacc.c  */
#line 4139 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 746:

/* Line 1455 of yacc.c  */
#line 4140 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 747:

/* Line 1455 of yacc.c  */
#line 4150 "parser.y"
    {
	cb_error (_("ALTER statement is obsolete and unsupported"));
  ;}
    break;

  case 752:

/* Line 1455 of yacc.c  */
#line 4168 "parser.y"
    { BEGIN_STATEMENT ("CALL", TERM_CALL); ;}
    break;

  case 753:

/* Line 1455 of yacc.c  */
#line 4172 "parser.y"
    {
	cb_emit_call ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 754:

/* Line 1455 of yacc.c  */
#line 4178 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 755:

/* Line 1455 of yacc.c  */
#line 4180 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 756:

/* Line 1455 of yacc.c  */
#line 4184 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 757:

/* Line 1455 of yacc.c  */
#line 4188 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 758:

/* Line 1455 of yacc.c  */
#line 4190 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 759:

/* Line 1455 of yacc.c  */
#line 4195 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OMITTED only allowed with BY REFERENCE"));
	}
	(yyval) = cb_build_pair (cb_int (call_mode), cb_null);
  ;}
    break;

  case 760:

/* Line 1455 of yacc.c  */
#line 4202 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), (yyvsp[(3) - (3)]));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 762:

/* Line 1455 of yacc.c  */
#line 4211 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 763:

/* Line 1455 of yacc.c  */
#line 4215 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY CONTENT not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_CONTENT;
	}
  ;}
    break;

  case 764:

/* Line 1455 of yacc.c  */
#line 4223 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 765:

/* Line 1455 of yacc.c  */
#line 4233 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 766:

/* Line 1455 of yacc.c  */
#line 4234 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 767:

/* Line 1455 of yacc.c  */
#line 4235 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 768:

/* Line 1455 of yacc.c  */
#line 4240 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 769:

/* Line 1455 of yacc.c  */
#line 4244 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 770:

/* Line 1455 of yacc.c  */
#line 4248 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 771:

/* Line 1455 of yacc.c  */
#line 4255 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 772:

/* Line 1455 of yacc.c  */
#line 4259 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 773:

/* Line 1455 of yacc.c  */
#line 4263 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 774:

/* Line 1455 of yacc.c  */
#line 4269 "parser.y"
    { terminator_warning (TERM_CALL); ;}
    break;

  case 775:

/* Line 1455 of yacc.c  */
#line 4270 "parser.y"
    { terminator_clear (TERM_CALL); ;}
    break;

  case 776:

/* Line 1455 of yacc.c  */
#line 4279 "parser.y"
    { BEGIN_STATEMENT ("CANCEL", 0); ;}
    break;

  case 779:

/* Line 1455 of yacc.c  */
#line 4285 "parser.y"
    {
	cb_emit_cancel ((yyvsp[(2) - (2)]));
  ;}
    break;

  case 780:

/* Line 1455 of yacc.c  */
#line 4296 "parser.y"
    { BEGIN_STATEMENT ("CLOSE", 0); ;}
    break;

  case 783:

/* Line 1455 of yacc.c  */
#line 4303 "parser.y"
    {
	BEGIN_IMPLICIT_STATEMENT ();
	if ((yyvsp[(2) - (3)]) != cb_error_node) {
		cb_emit_close ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
	}
  ;}
    break;

  case 784:

/* Line 1455 of yacc.c  */
#line 4312 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NORMAL); ;}
    break;

  case 785:

/* Line 1455 of yacc.c  */
#line 4313 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT); ;}
    break;

  case 786:

/* Line 1455 of yacc.c  */
#line 4314 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT_REMOVAL); ;}
    break;

  case 787:

/* Line 1455 of yacc.c  */
#line 4315 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NO_REWIND); ;}
    break;

  case 788:

/* Line 1455 of yacc.c  */
#line 4316 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_LOCK); ;}
    break;

  case 791:

/* Line 1455 of yacc.c  */
#line 4327 "parser.y"
    { BEGIN_STATEMENT ("COMPUTE", TERM_COMPUTE); ;}
    break;

  case 793:

/* Line 1455 of yacc.c  */
#line 4334 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(1) - (4)]), 0, (yyvsp[(3) - (4)]));
  ;}
    break;

  case 794:

/* Line 1455 of yacc.c  */
#line 4340 "parser.y"
    { terminator_warning (TERM_COMPUTE); ;}
    break;

  case 795:

/* Line 1455 of yacc.c  */
#line 4341 "parser.y"
    { terminator_clear (TERM_COMPUTE); ;}
    break;

  case 798:

/* Line 1455 of yacc.c  */
#line 4352 "parser.y"
    {
	BEGIN_STATEMENT ("COMMIT", 0);
	cb_emit_commit ();
  ;}
    break;

  case 799:

/* Line 1455 of yacc.c  */
#line 4365 "parser.y"
    {
	BEGIN_STATEMENT ("CONTINUE", 0);
	cb_emit_continue ();
  ;}
    break;

  case 800:

/* Line 1455 of yacc.c  */
#line 4377 "parser.y"
    { BEGIN_STATEMENT ("DELETE", TERM_DELETE); ;}
    break;

  case 801:

/* Line 1455 of yacc.c  */
#line 4380 "parser.y"
    {
	if ((yyvsp[(3) - (6)]) != cb_error_node) {
		cb_emit_delete ((yyvsp[(3) - (6)]));
	}
  ;}
    break;

  case 802:

/* Line 1455 of yacc.c  */
#line 4388 "parser.y"
    { terminator_warning (TERM_DELETE); ;}
    break;

  case 803:

/* Line 1455 of yacc.c  */
#line 4389 "parser.y"
    { terminator_clear (TERM_DELETE); ;}
    break;

  case 804:

/* Line 1455 of yacc.c  */
#line 4398 "parser.y"
    { BEGIN_STATEMENT ("DELETE-FILE", 0); ;}
    break;

  case 805:

/* Line 1455 of yacc.c  */
#line 4400 "parser.y"
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

  case 806:

/* Line 1455 of yacc.c  */
#line 4418 "parser.y"
    {
	BEGIN_STATEMENT ("DISPLAY", TERM_DISPLAY);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 808:

/* Line 1455 of yacc.c  */
#line 4431 "parser.y"
    {
	cb_emit_env_name ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 809:

/* Line 1455 of yacc.c  */
#line 4435 "parser.y"
    {
	cb_emit_env_value ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 810:

/* Line 1455 of yacc.c  */
#line 4439 "parser.y"
    {
	cb_emit_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 811:

/* Line 1455 of yacc.c  */
#line 4443 "parser.y"
    {
	cb_emit_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 812:

/* Line 1455 of yacc.c  */
#line 4447 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (4)]), cb_int0, (yyvsp[(3) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 813:

/* Line 1455 of yacc.c  */
#line 4451 "parser.y"
    {
	cb_emit_display_mnemonic ((yyvsp[(1) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 814:

/* Line 1455 of yacc.c  */
#line 4455 "parser.y"
    {
	cb_tree word = cb_build_display_upon_direct ((yyvsp[(4) - (6)]));
	cb_emit_display ((yyvsp[(1) - (6)]), word, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 815:

/* Line 1455 of yacc.c  */
#line 4460 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 816:

/* Line 1455 of yacc.c  */
#line 4464 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 817:

/* Line 1455 of yacc.c  */
#line 4470 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 818:

/* Line 1455 of yacc.c  */
#line 4471 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 819:

/* Line 1455 of yacc.c  */
#line 4472 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 822:

/* Line 1455 of yacc.c  */
#line 4482 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 823:

/* Line 1455 of yacc.c  */
#line 4483 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 824:

/* Line 1455 of yacc.c  */
#line 4484 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 825:

/* Line 1455 of yacc.c  */
#line 4485 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 826:

/* Line 1455 of yacc.c  */
#line 4486 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 827:

/* Line 1455 of yacc.c  */
#line 4487 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 828:

/* Line 1455 of yacc.c  */
#line 4488 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 829:

/* Line 1455 of yacc.c  */
#line 4489 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 830:

/* Line 1455 of yacc.c  */
#line 4490 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 831:

/* Line 1455 of yacc.c  */
#line 4492 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 832:

/* Line 1455 of yacc.c  */
#line 4496 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 833:

/* Line 1455 of yacc.c  */
#line 4500 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 834:

/* Line 1455 of yacc.c  */
#line 4504 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 835:

/* Line 1455 of yacc.c  */
#line 4508 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 836:

/* Line 1455 of yacc.c  */
#line 4509 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 837:

/* Line 1455 of yacc.c  */
#line 4513 "parser.y"
    { terminator_warning (TERM_DISPLAY); ;}
    break;

  case 838:

/* Line 1455 of yacc.c  */
#line 4514 "parser.y"
    { terminator_clear (TERM_DISPLAY); ;}
    break;

  case 839:

/* Line 1455 of yacc.c  */
#line 4523 "parser.y"
    { BEGIN_STATEMENT ("DIVIDE", TERM_DIVIDE); ;}
    break;

  case 841:

/* Line 1455 of yacc.c  */
#line 4530 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '/', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 842:

/* Line 1455 of yacc.c  */
#line 4534 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(3) - (6)]), '/', (yyvsp[(1) - (6)])));
  ;}
    break;

  case 843:

/* Line 1455 of yacc.c  */
#line 4538 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '/', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 844:

/* Line 1455 of yacc.c  */
#line 4542 "parser.y"
    {
	cb_emit_divide ((yyvsp[(3) - (8)]), (yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 845:

/* Line 1455 of yacc.c  */
#line 4546 "parser.y"
    {
	cb_emit_divide ((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 846:

/* Line 1455 of yacc.c  */
#line 4552 "parser.y"
    { terminator_warning (TERM_DIVIDE); ;}
    break;

  case 847:

/* Line 1455 of yacc.c  */
#line 4553 "parser.y"
    { terminator_clear (TERM_DIVIDE); ;}
    break;

  case 848:

/* Line 1455 of yacc.c  */
#line 4562 "parser.y"
    { BEGIN_STATEMENT ("ENTRY", 0); ;}
    break;

  case 849:

/* Line 1455 of yacc.c  */
#line 4564 "parser.y"
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

  case 850:

/* Line 1455 of yacc.c  */
#line 4584 "parser.y"
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

  case 851:

/* Line 1455 of yacc.c  */
#line 4595 "parser.y"
    {
	cb_emit_evaluate ((yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]));
	eval_level--;
  ;}
    break;

  case 852:

/* Line 1455 of yacc.c  */
#line 4602 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 853:

/* Line 1455 of yacc.c  */
#line 4605 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 854:

/* Line 1455 of yacc.c  */
#line 4615 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE_P ((yyvsp[(1) - (1)]))) {
		eval_check[eval_level][eval_inc++] = 0;
	} else {
		eval_check[eval_level][eval_inc++] = 1;
	}
  ;}
    break;

  case 855:

/* Line 1455 of yacc.c  */
#line 4624 "parser.y"
    {
	(yyval) = cb_true;
	eval_check[eval_level][eval_inc++] = 2;
  ;}
    break;

  case 856:

/* Line 1455 of yacc.c  */
#line 4629 "parser.y"
    {
	(yyval) = cb_false;
	eval_check[eval_level][eval_inc++] = 3;
  ;}
    break;

  case 857:

/* Line 1455 of yacc.c  */
#line 4637 "parser.y"
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

  case 858:

/* Line 1455 of yacc.c  */
#line 4665 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 859:

/* Line 1455 of yacc.c  */
#line 4667 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 860:

/* Line 1455 of yacc.c  */
#line 4672 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 861:

/* Line 1455 of yacc.c  */
#line 4676 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]));
	eval_inc2 = 0;
  ;}
    break;

  case 862:

/* Line 1455 of yacc.c  */
#line 4687 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 863:

/* Line 1455 of yacc.c  */
#line 4691 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 864:

/* Line 1455 of yacc.c  */
#line 4695 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), NULL);
	eval_inc2 = 0;
  ;}
    break;

  case 865:

/* Line 1455 of yacc.c  */
#line 4705 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 866:

/* Line 1455 of yacc.c  */
#line 4707 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 867:

/* Line 1455 of yacc.c  */
#line 4711 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 868:

/* Line 1455 of yacc.c  */
#line 4714 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 869:

/* Line 1455 of yacc.c  */
#line 4724 "parser.y"
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

  case 870:

/* Line 1455 of yacc.c  */
#line 4752 "parser.y"
    { (yyval) = cb_any; eval_inc2++; ;}
    break;

  case 871:

/* Line 1455 of yacc.c  */
#line 4753 "parser.y"
    { (yyval) = cb_true; eval_inc2++; ;}
    break;

  case 872:

/* Line 1455 of yacc.c  */
#line 4754 "parser.y"
    { (yyval) = cb_false; eval_inc2++; ;}
    break;

  case 873:

/* Line 1455 of yacc.c  */
#line 4757 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 874:

/* Line 1455 of yacc.c  */
#line 4758 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 875:

/* Line 1455 of yacc.c  */
#line 4762 "parser.y"
    { terminator_warning (TERM_EVALUATE); ;}
    break;

  case 876:

/* Line 1455 of yacc.c  */
#line 4763 "parser.y"
    { terminator_clear (TERM_EVALUATE); ;}
    break;

  case 877:

/* Line 1455 of yacc.c  */
#line 4772 "parser.y"
    { BEGIN_STATEMENT ("EXIT", 0); ;}
    break;

  case 879:

/* Line 1455 of yacc.c  */
#line 4777 "parser.y"
    { /* nothing */ ;}
    break;

  case 880:

/* Line 1455 of yacc.c  */
#line 4779 "parser.y"
    {
	if (in_declaratives && use_global_ind) {
		cb_error (_("EXIT PROGRAM is not allowed within a USE GLOBAL procedure"));
	}
	check_unreached = 1;
	cb_emit_exit (0);
  ;}
    break;

  case 881:

/* Line 1455 of yacc.c  */
#line 4787 "parser.y"
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

  case 882:

/* Line 1455 of yacc.c  */
#line 4804 "parser.y"
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

  case 883:

/* Line 1455 of yacc.c  */
#line 4821 "parser.y"
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

  case 884:

/* Line 1455 of yacc.c  */
#line 4839 "parser.y"
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

  case 885:

/* Line 1455 of yacc.c  */
#line 4863 "parser.y"
    { BEGIN_STATEMENT ("FREE", 0); ;}
    break;

  case 886:

/* Line 1455 of yacc.c  */
#line 4865 "parser.y"
    {
	cb_emit_free ((yyvsp[(3) - (3)]))
  ;}
    break;

  case 887:

/* Line 1455 of yacc.c  */
#line 4876 "parser.y"
    { BEGIN_STATEMENT ("GENERATE", 0); ;}
    break;

  case 888:

/* Line 1455 of yacc.c  */
#line 4878 "parser.y"
    {
	PENDING("GENERATE");
  ;}
    break;

  case 889:

/* Line 1455 of yacc.c  */
#line 4889 "parser.y"
    { BEGIN_STATEMENT ("GO TO", 0); ;}
    break;

  case 890:

/* Line 1455 of yacc.c  */
#line 4891 "parser.y"
    {
	cb_emit_goto ((yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 891:

/* Line 1455 of yacc.c  */
#line 4898 "parser.y"
    {
	check_unreached = 1;
	(yyval) = NULL;
  ;}
    break;

  case 892:

/* Line 1455 of yacc.c  */
#line 4903 "parser.y"
    {
	check_unreached = 0;
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 893:

/* Line 1455 of yacc.c  */
#line 4915 "parser.y"
    { BEGIN_STATEMENT ("GOBACK", 0); ;}
    break;

  case 894:

/* Line 1455 of yacc.c  */
#line 4916 "parser.y"
    {
	check_unreached = 1;
	cb_emit_exit (1);
  ;}
    break;

  case 895:

/* Line 1455 of yacc.c  */
#line 4928 "parser.y"
    { BEGIN_STATEMENT ("IF", TERM_IF); ;}
    break;

  case 896:

/* Line 1455 of yacc.c  */
#line 4930 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 897:

/* Line 1455 of yacc.c  */
#line 4935 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(6) - (8)]) == NULL) {
		cb_error (_("syntax error"));
	}
	cb_emit_if ((yyvsp[(3) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 899:

/* Line 1455 of yacc.c  */
#line 4946 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 900:

/* Line 1455 of yacc.c  */
#line 4950 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 901:

/* Line 1455 of yacc.c  */
#line 4954 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 902:

/* Line 1455 of yacc.c  */
#line 4963 "parser.y"
    { terminator_warning (TERM_IF); ;}
    break;

  case 903:

/* Line 1455 of yacc.c  */
#line 4964 "parser.y"
    { terminator_clear (TERM_IF); ;}
    break;

  case 904:

/* Line 1455 of yacc.c  */
#line 4973 "parser.y"
    { BEGIN_STATEMENT ("INITIALIZE", 0); ;}
    break;

  case 905:

/* Line 1455 of yacc.c  */
#line 4975 "parser.y"
    {
	cb_emit_initialize ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 906:

/* Line 1455 of yacc.c  */
#line 4981 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 907:

/* Line 1455 of yacc.c  */
#line 4982 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 908:

/* Line 1455 of yacc.c  */
#line 4986 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 909:

/* Line 1455 of yacc.c  */
#line 4987 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 910:

/* Line 1455 of yacc.c  */
#line 4988 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 911:

/* Line 1455 of yacc.c  */
#line 4992 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 912:

/* Line 1455 of yacc.c  */
#line 4994 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 913:

/* Line 1455 of yacc.c  */
#line 4998 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 914:

/* Line 1455 of yacc.c  */
#line 5000 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 915:

/* Line 1455 of yacc.c  */
#line 5004 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 916:

/* Line 1455 of yacc.c  */
#line 5008 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHABETIC); ;}
    break;

  case 917:

/* Line 1455 of yacc.c  */
#line 5009 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC); ;}
    break;

  case 918:

/* Line 1455 of yacc.c  */
#line 5010 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC); ;}
    break;

  case 919:

/* Line 1455 of yacc.c  */
#line 5011 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC_EDITED); ;}
    break;

  case 920:

/* Line 1455 of yacc.c  */
#line 5012 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC_EDITED); ;}
    break;

  case 921:

/* Line 1455 of yacc.c  */
#line 5013 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL); ;}
    break;

  case 922:

/* Line 1455 of yacc.c  */
#line 5014 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL_EDITED); ;}
    break;

  case 923:

/* Line 1455 of yacc.c  */
#line 5018 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 924:

/* Line 1455 of yacc.c  */
#line 5019 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 925:

/* Line 1455 of yacc.c  */
#line 5028 "parser.y"
    { BEGIN_STATEMENT ("INITIATE", 0); ;}
    break;

  case 926:

/* Line 1455 of yacc.c  */
#line 5030 "parser.y"
    {
	PENDING("INITIATE");
  ;}
    break;

  case 927:

/* Line 1455 of yacc.c  */
#line 5041 "parser.y"
    {
	BEGIN_STATEMENT ("INSPECT", 0);
	sending_id = 0;
	inspect_keyword = 0;
  ;}
    break;

  case 929:

/* Line 1455 of yacc.c  */
#line 5050 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 0; ;}
    break;

  case 930:

/* Line 1455 of yacc.c  */
#line 5051 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 931:

/* Line 1455 of yacc.c  */
#line 5052 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 934:

/* Line 1455 of yacc.c  */
#line 5061 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 0); ;}
    break;

  case 935:

/* Line 1455 of yacc.c  */
#line 5062 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int1, 1); ;}
    break;

  case 936:

/* Line 1455 of yacc.c  */
#line 5063 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 2); ;}
    break;

  case 937:

/* Line 1455 of yacc.c  */
#line 5069 "parser.y"
    { cb_init_tarrying (); ;}
    break;

  case 938:

/* Line 1455 of yacc.c  */
#line 5070 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 939:

/* Line 1455 of yacc.c  */
#line 5074 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 940:

/* Line 1455 of yacc.c  */
#line 5075 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 941:

/* Line 1455 of yacc.c  */
#line 5079 "parser.y"
    { (yyval) = cb_build_tarrying_data ((yyvsp[(1) - (2)])); ;}
    break;

  case 942:

/* Line 1455 of yacc.c  */
#line 5080 "parser.y"
    { (yyval) = cb_build_tarrying_characters ((yyvsp[(2) - (2)])); ;}
    break;

  case 943:

/* Line 1455 of yacc.c  */
#line 5081 "parser.y"
    { (yyval) = cb_build_tarrying_all (); ;}
    break;

  case 944:

/* Line 1455 of yacc.c  */
#line 5082 "parser.y"
    { (yyval) = cb_build_tarrying_leading (); ;}
    break;

  case 945:

/* Line 1455 of yacc.c  */
#line 5083 "parser.y"
    { (yyval) = cb_build_tarrying_trailing (); ;}
    break;

  case 946:

/* Line 1455 of yacc.c  */
#line 5084 "parser.y"
    { (yyval) = cb_build_tarrying_value ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 947:

/* Line 1455 of yacc.c  */
#line 5090 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); inspect_keyword = 0; ;}
    break;

  case 948:

/* Line 1455 of yacc.c  */
#line 5094 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 949:

/* Line 1455 of yacc.c  */
#line 5095 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 950:

/* Line 1455 of yacc.c  */
#line 5100 "parser.y"
    {
	(yyval) = cb_build_replacing_characters ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]), save_tree_1);
	inspect_keyword = 0;
  ;}
    break;

  case 951:

/* Line 1455 of yacc.c  */
#line 5104 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 952:

/* Line 1455 of yacc.c  */
#line 5108 "parser.y"
    { /* Nothing */ ;}
    break;

  case 953:

/* Line 1455 of yacc.c  */
#line 5109 "parser.y"
    { inspect_keyword = 1; ;}
    break;

  case 954:

/* Line 1455 of yacc.c  */
#line 5110 "parser.y"
    { inspect_keyword = 2; ;}
    break;

  case 955:

/* Line 1455 of yacc.c  */
#line 5111 "parser.y"
    { inspect_keyword = 3; ;}
    break;

  case 956:

/* Line 1455 of yacc.c  */
#line 5112 "parser.y"
    { inspect_keyword = 4; ;}
    break;

  case 957:

/* Line 1455 of yacc.c  */
#line 5117 "parser.y"
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

  case 958:

/* Line 1455 of yacc.c  */
#line 5143 "parser.y"
    {
	if (cb_validate_inspect (save_tree_1, (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])) < 0 ) {
		(yyval) = cb_error_node;
	} else {
		(yyval) = cb_build_converting ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 959:

/* Line 1455 of yacc.c  */
#line 5155 "parser.y"
    { (yyval) = cb_build_inspect_region_start (); ;}
    break;

  case 960:

/* Line 1455 of yacc.c  */
#line 5157 "parser.y"
    { (yyval) = cb_build_inspect_region ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 963:

/* Line 1455 of yacc.c  */
#line 5168 "parser.y"
    { BEGIN_STATEMENT ("MERGE", 0); ;}
    break;

  case 965:

/* Line 1455 of yacc.c  */
#line 5178 "parser.y"
    { BEGIN_STATEMENT ("MOVE", 0); ;}
    break;

  case 967:

/* Line 1455 of yacc.c  */
#line 5184 "parser.y"
    {
	cb_emit_move ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 968:

/* Line 1455 of yacc.c  */
#line 5188 "parser.y"
    {
	cb_emit_move_corresponding ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 969:

/* Line 1455 of yacc.c  */
#line 5199 "parser.y"
    { BEGIN_STATEMENT ("MULTIPLY", TERM_MULTIPLY); ;}
    break;

  case 971:

/* Line 1455 of yacc.c  */
#line 5206 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '*', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 972:

/* Line 1455 of yacc.c  */
#line 5210 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '*', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 973:

/* Line 1455 of yacc.c  */
#line 5216 "parser.y"
    { terminator_warning (TERM_MULTIPLY); ;}
    break;

  case 974:

/* Line 1455 of yacc.c  */
#line 5217 "parser.y"
    { terminator_clear (TERM_MULTIPLY); ;}
    break;

  case 975:

/* Line 1455 of yacc.c  */
#line 5226 "parser.y"
    { BEGIN_STATEMENT ("OPEN", 0); ;}
    break;

  case 978:

/* Line 1455 of yacc.c  */
#line 5233 "parser.y"
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

  case 979:

/* Line 1455 of yacc.c  */
#line 5245 "parser.y"
    { (yyval) = cb_int (COB_OPEN_INPUT); ;}
    break;

  case 980:

/* Line 1455 of yacc.c  */
#line 5246 "parser.y"
    { (yyval) = cb_int (COB_OPEN_OUTPUT); ;}
    break;

  case 981:

/* Line 1455 of yacc.c  */
#line 5247 "parser.y"
    { (yyval) = cb_int (COB_OPEN_I_O); ;}
    break;

  case 982:

/* Line 1455 of yacc.c  */
#line 5248 "parser.y"
    { (yyval) = cb_int (COB_OPEN_EXTEND); ;}
    break;

  case 983:

/* Line 1455 of yacc.c  */
#line 5252 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 984:

/* Line 1455 of yacc.c  */
#line 5253 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 985:

/* Line 1455 of yacc.c  */
#line 5257 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 986:

/* Line 1455 of yacc.c  */
#line 5258 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 987:

/* Line 1455 of yacc.c  */
#line 5259 "parser.y"
    { PENDING ("OPEN ... WITH LOCK"); ;}
    break;

  case 988:

/* Line 1455 of yacc.c  */
#line 5271 "parser.y"
    { BEGIN_STATEMENT ("PERFORM", TERM_PERFORM); ;}
    break;

  case 990:

/* Line 1455 of yacc.c  */
#line 5277 "parser.y"
    {
	cb_emit_perform ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));
  ;}
    break;

  case 991:

/* Line 1455 of yacc.c  */
#line 5281 "parser.y"
    {
	perform_stack = cb_cons ((yyvsp[(1) - (1)]), perform_stack);
	check_unreached = 0;
  ;}
    break;

  case 992:

/* Line 1455 of yacc.c  */
#line 5286 "parser.y"
    {
	perform_stack = CB_CHAIN (perform_stack);
	cb_emit_perform ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 993:

/* Line 1455 of yacc.c  */
#line 5291 "parser.y"
    {
	cb_emit_perform ((yyvsp[(1) - (2)]), NULL);
  ;}
    break;

  case 994:

/* Line 1455 of yacc.c  */
#line 5297 "parser.y"
    { terminator_error (); ;}
    break;

  case 995:

/* Line 1455 of yacc.c  */
#line 5298 "parser.y"
    { terminator_clear (TERM_PERFORM); ;}
    break;

  case 996:

/* Line 1455 of yacc.c  */
#line 5303 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(1) - (1)]))->length = cb_true; /* return from $1 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (1)]), (yyvsp[(1) - (1)]));
  ;}
    break;

  case 997:

/* Line 1455 of yacc.c  */
#line 5308 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(3) - (3)]))->length = cb_true; /* return from $3 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 998:

/* Line 1455 of yacc.c  */
#line 5316 "parser.y"
    {
	(yyval) = cb_build_perform_once (NULL);
  ;}
    break;

  case 999:

/* Line 1455 of yacc.c  */
#line 5320 "parser.y"
    {
	(yyval) = cb_build_perform_forever (NULL);
  ;}
    break;

  case 1000:

/* Line 1455 of yacc.c  */
#line 5324 "parser.y"
    {
	(yyval) = cb_build_perform_times ((yyvsp[(1) - (2)]));
	current_program->loop_counter++;
  ;}
    break;

  case 1001:

/* Line 1455 of yacc.c  */
#line 5329 "parser.y"
    {
	cb_tree varying;

	varying = cb_list_init (cb_build_perform_varying (NULL, NULL, NULL, (yyvsp[(3) - (3)])));
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), varying);
  ;}
    break;

  case 1002:

/* Line 1455 of yacc.c  */
#line 5336 "parser.y"
    {
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1003:

/* Line 1455 of yacc.c  */
#line 5342 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1004:

/* Line 1455 of yacc.c  */
#line 5343 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1005:

/* Line 1455 of yacc.c  */
#line 5347 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1006:

/* Line 1455 of yacc.c  */
#line 5349 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1007:

/* Line 1455 of yacc.c  */
#line 5354 "parser.y"
    {
	(yyval) = cb_build_perform_varying ((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1008:

/* Line 1455 of yacc.c  */
#line 5365 "parser.y"
    { BEGIN_STATEMENT ("READ", TERM_READ); ;}
    break;

  case 1009:

/* Line 1455 of yacc.c  */
#line 5368 "parser.y"
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

  case 1010:

/* Line 1455 of yacc.c  */
#line 5388 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1011:

/* Line 1455 of yacc.c  */
#line 5389 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1012:

/* Line 1455 of yacc.c  */
#line 5393 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1013:

/* Line 1455 of yacc.c  */
#line 5395 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1014:

/* Line 1455 of yacc.c  */
#line 5399 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1015:

/* Line 1455 of yacc.c  */
#line 5403 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1016:

/* Line 1455 of yacc.c  */
#line 5407 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1017:

/* Line 1455 of yacc.c  */
#line 5411 "parser.y"
    {
	(yyval) = cb_int4;
  ;}
    break;

  case 1018:

/* Line 1455 of yacc.c  */
#line 5417 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1019:

/* Line 1455 of yacc.c  */
#line 5419 "parser.y"
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

  case 1023:

/* Line 1455 of yacc.c  */
#line 5438 "parser.y"
    { terminator_warning (TERM_READ); ;}
    break;

  case 1024:

/* Line 1455 of yacc.c  */
#line 5439 "parser.y"
    { terminator_clear (TERM_READ); ;}
    break;

  case 1025:

/* Line 1455 of yacc.c  */
#line 5448 "parser.y"
    { BEGIN_STATEMENT ("RELEASE", 0); ;}
    break;

  case 1026:

/* Line 1455 of yacc.c  */
#line 5450 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_release ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
	}
  ;}
    break;

  case 1027:

/* Line 1455 of yacc.c  */
#line 5463 "parser.y"
    { BEGIN_STATEMENT ("RETURN", TERM_RETURN); ;}
    break;

  case 1028:

/* Line 1455 of yacc.c  */
#line 5466 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_return ((yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]));
	}
  ;}
    break;

  case 1029:

/* Line 1455 of yacc.c  */
#line 5474 "parser.y"
    { terminator_warning (TERM_RETURN); ;}
    break;

  case 1030:

/* Line 1455 of yacc.c  */
#line 5475 "parser.y"
    { terminator_clear (TERM_RETURN); ;}
    break;

  case 1031:

/* Line 1455 of yacc.c  */
#line 5484 "parser.y"
    { BEGIN_STATEMENT ("REWRITE", TERM_REWRITE); ;}
    break;

  case 1032:

/* Line 1455 of yacc.c  */
#line 5487 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_rewrite ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]));
	}
  ;}
    break;

  case 1033:

/* Line 1455 of yacc.c  */
#line 5495 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1034:

/* Line 1455 of yacc.c  */
#line 5497 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1035:

/* Line 1455 of yacc.c  */
#line 5501 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1036:

/* Line 1455 of yacc.c  */
#line 5507 "parser.y"
    { terminator_warning (TERM_REWRITE); ;}
    break;

  case 1037:

/* Line 1455 of yacc.c  */
#line 5508 "parser.y"
    { terminator_clear (TERM_REWRITE); ;}
    break;

  case 1038:

/* Line 1455 of yacc.c  */
#line 5518 "parser.y"
    {
	BEGIN_STATEMENT ("ROLLBACK", 0);
	cb_emit_rollback ();
  ;}
    break;

  case 1039:

/* Line 1455 of yacc.c  */
#line 5530 "parser.y"
    { BEGIN_STATEMENT ("SEARCH", TERM_SEARCH); ;}
    break;

  case 1041:

/* Line 1455 of yacc.c  */
#line 5537 "parser.y"
    {
	cb_emit_search ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1042:

/* Line 1455 of yacc.c  */
#line 5541 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1043:

/* Line 1455 of yacc.c  */
#line 5545 "parser.y"
    {
	cb_emit_search_all ((yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1044:

/* Line 1455 of yacc.c  */
#line 5551 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1045:

/* Line 1455 of yacc.c  */
#line 5552 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1046:

/* Line 1455 of yacc.c  */
#line 5556 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1047:

/* Line 1455 of yacc.c  */
#line 5558 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1048:

/* Line 1455 of yacc.c  */
#line 5562 "parser.y"
    {
	(yyval) = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 1049:

/* Line 1455 of yacc.c  */
#line 5568 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1050:

/* Line 1455 of yacc.c  */
#line 5569 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); CB_IF ((yyvsp[(1) - (2)]))->stmt2 = (yyvsp[(2) - (2)]); ;}
    break;

  case 1051:

/* Line 1455 of yacc.c  */
#line 5574 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1052:

/* Line 1455 of yacc.c  */
#line 5578 "parser.y"
    {
	(yyval) = cb_build_if ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), NULL);
  ;}
    break;

  case 1053:

/* Line 1455 of yacc.c  */
#line 5584 "parser.y"
    { terminator_warning (TERM_SEARCH); ;}
    break;

  case 1054:

/* Line 1455 of yacc.c  */
#line 5585 "parser.y"
    { terminator_clear (TERM_SEARCH); ;}
    break;

  case 1055:

/* Line 1455 of yacc.c  */
#line 5594 "parser.y"
    { BEGIN_STATEMENT ("SET", 0); ;}
    break;

  case 1062:

/* Line 1455 of yacc.c  */
#line 5610 "parser.y"
    {
	cb_emit_setenv ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1063:

/* Line 1455 of yacc.c  */
#line 5619 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (4)]), cb_build_ppointer ((yyvsp[(4) - (4)])));
  ;}
    break;

  case 1064:

/* Line 1455 of yacc.c  */
#line 5623 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1065:

/* Line 1455 of yacc.c  */
#line 5632 "parser.y"
    {
	cb_emit_set_up_down ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1066:

/* Line 1455 of yacc.c  */
#line 5638 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1067:

/* Line 1455 of yacc.c  */
#line 5639 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1070:

/* Line 1455 of yacc.c  */
#line 5651 "parser.y"
    {
	cb_emit_set_on_off ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1073:

/* Line 1455 of yacc.c  */
#line 5665 "parser.y"
    {
	cb_emit_set_true ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1074:

/* Line 1455 of yacc.c  */
#line 5669 "parser.y"
    {
	cb_emit_set_false ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1075:

/* Line 1455 of yacc.c  */
#line 5680 "parser.y"
    { BEGIN_STATEMENT ("SORT", 0); ;}
    break;

  case 1077:

/* Line 1455 of yacc.c  */
#line 5686 "parser.y"
    {
	cb_emit_sort_init ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (4)]))) && (yyvsp[(2) - (4)]) == NULL) {
		cb_error (_("File sort requires KEY phrase"));
	}
	/* used in sort_input/sort_output */
	save_tree_1 = (yyvsp[(1) - (4)]);
  ;}
    break;

  case 1078:

/* Line 1455 of yacc.c  */
#line 5695 "parser.y"
    {
	cb_emit_sort_finish ((yyvsp[(1) - (7)]));
  ;}
    break;

  case 1079:

/* Line 1455 of yacc.c  */
#line 5702 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 1080:

/* Line 1455 of yacc.c  */
#line 5707 "parser.y"
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

  case 1081:

/* Line 1455 of yacc.c  */
#line 5721 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1082:

/* Line 1455 of yacc.c  */
#line 5722 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1084:

/* Line 1455 of yacc.c  */
#line 5726 "parser.y"
    { /* nothing */ ;}
    break;

  case 1085:

/* Line 1455 of yacc.c  */
#line 5730 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1086:

/* Line 1455 of yacc.c  */
#line 5731 "parser.y"
    { (yyval) = cb_ref ((yyvsp[(3) - (3)])); ;}
    break;

  case 1087:

/* Line 1455 of yacc.c  */
#line 5736 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires USING or INPUT PROCEDURE"));
	}
  ;}
    break;

  case 1088:

/* Line 1455 of yacc.c  */
#line 5742 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("USING invalid with table SORT"));
	} else {
		cb_emit_sort_using (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1089:

/* Line 1455 of yacc.c  */
#line 5750 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("INPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_input ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1090:

/* Line 1455 of yacc.c  */
#line 5761 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires GIVING or OUTPUT PROCEDURE"));
	}
  ;}
    break;

  case 1091:

/* Line 1455 of yacc.c  */
#line 5767 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("GIVING invalid with table SORT"));
	} else {
		cb_emit_sort_giving (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1092:

/* Line 1455 of yacc.c  */
#line 5775 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("OUTPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_output ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1093:

/* Line 1455 of yacc.c  */
#line 5790 "parser.y"
    { BEGIN_STATEMENT ("START", TERM_START); ;}
    break;

  case 1094:

/* Line 1455 of yacc.c  */
#line 5791 "parser.y"
    { (yyval) = cb_int (COB_EQ); ;}
    break;

  case 1095:

/* Line 1455 of yacc.c  */
#line 5794 "parser.y"
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

  case 1096:

/* Line 1455 of yacc.c  */
#line 5811 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1097:

/* Line 1455 of yacc.c  */
#line 5813 "parser.y"
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

  case 1098:

/* Line 1455 of yacc.c  */
#line 5828 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_NE : COB_EQ); ;}
    break;

  case 1099:

/* Line 1455 of yacc.c  */
#line 5829 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LE : COB_GT); ;}
    break;

  case 1100:

/* Line 1455 of yacc.c  */
#line 5830 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GE : COB_LT); ;}
    break;

  case 1101:

/* Line 1455 of yacc.c  */
#line 5831 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LT : COB_GE); ;}
    break;

  case 1102:

/* Line 1455 of yacc.c  */
#line 5832 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GT : COB_LE); ;}
    break;

  case 1103:

/* Line 1455 of yacc.c  */
#line 5836 "parser.y"
    { terminator_warning (TERM_START); ;}
    break;

  case 1104:

/* Line 1455 of yacc.c  */
#line 5837 "parser.y"
    { terminator_clear (TERM_START); ;}
    break;

  case 1105:

/* Line 1455 of yacc.c  */
#line 5846 "parser.y"
    { BEGIN_STATEMENT ("STOP", 0); ;}
    break;

  case 1106:

/* Line 1455 of yacc.c  */
#line 5848 "parser.y"
    {
	cb_emit_stop_run ((yyvsp[(4) - (4)]));
  ;}
    break;

  case 1107:

/* Line 1455 of yacc.c  */
#line 5852 "parser.y"
    {
	cb_verify (cb_stop_literal_statement, "STOP literal");
  ;}
    break;

  case 1108:

/* Line 1455 of yacc.c  */
#line 5858 "parser.y"
    { (yyval) = current_program->cb_return_code; ;}
    break;

  case 1109:

/* Line 1455 of yacc.c  */
#line 5859 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1110:

/* Line 1455 of yacc.c  */
#line 5860 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1111:

/* Line 1455 of yacc.c  */
#line 5869 "parser.y"
    { BEGIN_STATEMENT ("STRING", TERM_STRING); ;}
    break;

  case 1112:

/* Line 1455 of yacc.c  */
#line 5872 "parser.y"
    {
	cb_emit_string ((yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]));
  ;}
    break;

  case 1113:

/* Line 1455 of yacc.c  */
#line 5878 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1114:

/* Line 1455 of yacc.c  */
#line 5879 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1115:

/* Line 1455 of yacc.c  */
#line 5883 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1116:

/* Line 1455 of yacc.c  */
#line 5884 "parser.y"
    { (yyval) = cb_build_pair (cb_int0, NULL); ;}
    break;

  case 1117:

/* Line 1455 of yacc.c  */
#line 5885 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), NULL); ;}
    break;

  case 1118:

/* Line 1455 of yacc.c  */
#line 5889 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1119:

/* Line 1455 of yacc.c  */
#line 5890 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1120:

/* Line 1455 of yacc.c  */
#line 5894 "parser.y"
    { terminator_warning (TERM_STRING); ;}
    break;

  case 1121:

/* Line 1455 of yacc.c  */
#line 5895 "parser.y"
    { terminator_clear (TERM_STRING); ;}
    break;

  case 1122:

/* Line 1455 of yacc.c  */
#line 5904 "parser.y"
    { BEGIN_STATEMENT ("SUBTRACT", TERM_SUBTRACT); ;}
    break;

  case 1124:

/* Line 1455 of yacc.c  */
#line 5911 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '-', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 1125:

/* Line 1455 of yacc.c  */
#line 5915 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_list (cb_cons ((yyvsp[(3) - (6)]), (yyvsp[(1) - (6)])), '-'));
  ;}
    break;

  case 1126:

/* Line 1455 of yacc.c  */
#line 5919 "parser.y"
    {
	cb_emit_corresponding (cb_build_sub, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 1127:

/* Line 1455 of yacc.c  */
#line 5925 "parser.y"
    { terminator_warning (TERM_SUBTRACT); ;}
    break;

  case 1128:

/* Line 1455 of yacc.c  */
#line 5926 "parser.y"
    { terminator_clear (TERM_SUBTRACT); ;}
    break;

  case 1129:

/* Line 1455 of yacc.c  */
#line 5936 "parser.y"
    {
	BEGIN_STATEMENT ("SUPPRESS", 0);
	PENDING("SUPPRESS");
  ;}
    break;

  case 1132:

/* Line 1455 of yacc.c  */
#line 5951 "parser.y"
    { BEGIN_STATEMENT ("TERMINATE", 0); ;}
    break;

  case 1133:

/* Line 1455 of yacc.c  */
#line 5953 "parser.y"
    {
	PENDING("TERMINATE");
  ;}
    break;

  case 1134:

/* Line 1455 of yacc.c  */
#line 5964 "parser.y"
    { BEGIN_STATEMENT ("TRANSFORM", 0); ;}
    break;

  case 1135:

/* Line 1455 of yacc.c  */
#line 5966 "parser.y"
    {
	cb_tree		x;

	x = cb_build_converting ((yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]), cb_build_inspect_region_start ());
	cb_emit_inspect ((yyvsp[(3) - (7)]), x, cb_int0, 2);
  ;}
    break;

  case 1136:

/* Line 1455 of yacc.c  */
#line 5980 "parser.y"
    { BEGIN_STATEMENT ("UNLOCK", 0); ;}
    break;

  case 1137:

/* Line 1455 of yacc.c  */
#line 5982 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_unlock ((yyvsp[(3) - (4)]));
	}
  ;}
    break;

  case 1141:

/* Line 1455 of yacc.c  */
#line 6001 "parser.y"
    { BEGIN_STATEMENT ("UNSTRING", TERM_UNSTRING); ;}
    break;

  case 1142:

/* Line 1455 of yacc.c  */
#line 6005 "parser.y"
    {
	cb_emit_unstring ((yyvsp[(3) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]));
  ;}
    break;

  case 1143:

/* Line 1455 of yacc.c  */
#line 6011 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1144:

/* Line 1455 of yacc.c  */
#line 6013 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1145:

/* Line 1455 of yacc.c  */
#line 6017 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1146:

/* Line 1455 of yacc.c  */
#line 6019 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1147:

/* Line 1455 of yacc.c  */
#line 6024 "parser.y"
    {
	(yyval) = cb_build_unstring_delimited ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1148:

/* Line 1455 of yacc.c  */
#line 6030 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 1149:

/* Line 1455 of yacc.c  */
#line 6032 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1150:

/* Line 1455 of yacc.c  */
#line 6037 "parser.y"
    {
	(yyval) = cb_build_unstring_into ((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1151:

/* Line 1455 of yacc.c  */
#line 6043 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1152:

/* Line 1455 of yacc.c  */
#line 6044 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1153:

/* Line 1455 of yacc.c  */
#line 6048 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1154:

/* Line 1455 of yacc.c  */
#line 6049 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1155:

/* Line 1455 of yacc.c  */
#line 6053 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1156:

/* Line 1455 of yacc.c  */
#line 6054 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1157:

/* Line 1455 of yacc.c  */
#line 6058 "parser.y"
    { terminator_warning (TERM_UNSTRING); ;}
    break;

  case 1158:

/* Line 1455 of yacc.c  */
#line 6059 "parser.y"
    { terminator_clear (TERM_UNSTRING); ;}
    break;

  case 1162:

/* Line 1455 of yacc.c  */
#line 6077 "parser.y"
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

  case 1163:

/* Line 1455 of yacc.c  */
#line 6098 "parser.y"
    {
	use_global_ind = 0;
  ;}
    break;

  case 1164:

/* Line 1455 of yacc.c  */
#line 6102 "parser.y"
    {
	use_global_ind = 1;
	current_program->flag_global_use = 1;
  ;}
    break;

  case 1165:

/* Line 1455 of yacc.c  */
#line 6110 "parser.y"
    {
	cb_tree		l;

	for (l = (yyvsp[(1) - (1)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			setup_use_file (CB_FILE (cb_ref (CB_VALUE (l))));
		}
	}
  ;}
    break;

  case 1166:

/* Line 1455 of yacc.c  */
#line 6120 "parser.y"
    {
	current_program->global_handler[COB_OPEN_INPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_INPUT].handler_prog = current_program;
  ;}
    break;

  case 1167:

/* Line 1455 of yacc.c  */
#line 6125 "parser.y"
    {
	current_program->global_handler[COB_OPEN_OUTPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_OUTPUT].handler_prog = current_program;
  ;}
    break;

  case 1168:

/* Line 1455 of yacc.c  */
#line 6130 "parser.y"
    {
	current_program->global_handler[COB_OPEN_I_O].handler_label = current_section;
	current_program->global_handler[COB_OPEN_I_O].handler_prog = current_program;
  ;}
    break;

  case 1169:

/* Line 1455 of yacc.c  */
#line 6135 "parser.y"
    {
	current_program->global_handler[COB_OPEN_EXTEND].handler_label = current_section;
	current_program->global_handler[COB_OPEN_EXTEND].handler_prog = current_program;
  ;}
    break;

  case 1182:

/* Line 1455 of yacc.c  */
#line 6167 "parser.y"
    {
	PENDING ("USE FOR DEBUGGING");
  ;}
    break;

  case 1185:

/* Line 1455 of yacc.c  */
#line 6179 "parser.y"
    {
	PENDING ("USE BEFORE REPORTING");
  ;}
    break;

  case 1186:

/* Line 1455 of yacc.c  */
#line 6190 "parser.y"
    { BEGIN_STATEMENT ("WRITE", TERM_WRITE); ;}
    break;

  case 1187:

/* Line 1455 of yacc.c  */
#line 6193 "parser.y"
    {
	if ((yyvsp[(3) - (8)]) != cb_error_node) {
		cb_emit_write ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(5) - (8)]));
	}
  ;}
    break;

  case 1188:

/* Line 1455 of yacc.c  */
#line 6201 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1189:

/* Line 1455 of yacc.c  */
#line 6202 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1190:

/* Line 1455 of yacc.c  */
#line 6207 "parser.y"
    {
	(yyval) = cb_int0;
  ;}
    break;

  case 1191:

/* Line 1455 of yacc.c  */
#line 6211 "parser.y"
    {
	(yyval) = cb_build_write_advancing_lines ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 1192:

/* Line 1455 of yacc.c  */
#line 6215 "parser.y"
    {
	(yyval) = cb_build_write_advancing_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1193:

/* Line 1455 of yacc.c  */
#line 6219 "parser.y"
    {
	(yyval) = cb_build_write_advancing_page ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1194:

/* Line 1455 of yacc.c  */
#line 6225 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1195:

/* Line 1455 of yacc.c  */
#line 6226 "parser.y"
    { (yyval) = CB_AFTER; ;}
    break;

  case 1199:

/* Line 1455 of yacc.c  */
#line 6235 "parser.y"
    { terminator_warning (TERM_WRITE); ;}
    break;

  case 1200:

/* Line 1455 of yacc.c  */
#line 6236 "parser.y"
    { terminator_clear (TERM_WRITE); ;}
    break;

  case 1201:

/* Line 1455 of yacc.c  */
#line 6251 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_ACCEPT;
  ;}
    break;

  case 1202:

/* Line 1455 of yacc.c  */
#line 6259 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_DISPLAY;
  ;}
    break;

  case 1204:

/* Line 1455 of yacc.c  */
#line 6266 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1205:

/* Line 1455 of yacc.c  */
#line 6270 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1207:

/* Line 1455 of yacc.c  */
#line 6277 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1208:

/* Line 1455 of yacc.c  */
#line 6281 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1211:

/* Line 1455 of yacc.c  */
#line 6297 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1212:

/* Line 1455 of yacc.c  */
#line 6302 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1214:

/* Line 1455 of yacc.c  */
#line 6309 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1215:

/* Line 1455 of yacc.c  */
#line 6314 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1216:

/* Line 1455 of yacc.c  */
#line 6326 "parser.y"
    {
	current_statement->handler_id = COB_EC_OVERFLOW;
  ;}
    break;

  case 1218:

/* Line 1455 of yacc.c  */
#line 6333 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1219:

/* Line 1455 of yacc.c  */
#line 6337 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1221:

/* Line 1455 of yacc.c  */
#line 6344 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1222:

/* Line 1455 of yacc.c  */
#line 6348 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1223:

/* Line 1455 of yacc.c  */
#line 6360 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1224:

/* Line 1455 of yacc.c  */
#line 6365 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1225:

/* Line 1455 of yacc.c  */
#line 6370 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1226:

/* Line 1455 of yacc.c  */
#line 6379 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1227:

/* Line 1455 of yacc.c  */
#line 6383 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1228:

/* Line 1455 of yacc.c  */
#line 6390 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1229:

/* Line 1455 of yacc.c  */
#line 6394 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1230:

/* Line 1455 of yacc.c  */
#line 6406 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1231:

/* Line 1455 of yacc.c  */
#line 6411 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1232:

/* Line 1455 of yacc.c  */
#line 6416 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1233:

/* Line 1455 of yacc.c  */
#line 6425 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1234:

/* Line 1455 of yacc.c  */
#line 6429 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1235:

/* Line 1455 of yacc.c  */
#line 6436 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1236:

/* Line 1455 of yacc.c  */
#line 6440 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1239:

/* Line 1455 of yacc.c  */
#line 6456 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1240:

/* Line 1455 of yacc.c  */
#line 6461 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1241:

/* Line 1455 of yacc.c  */
#line 6466 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1242:

/* Line 1455 of yacc.c  */
#line 6475 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1243:

/* Line 1455 of yacc.c  */
#line 6479 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1244:

/* Line 1455 of yacc.c  */
#line 6486 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1245:

/* Line 1455 of yacc.c  */
#line 6490 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1246:

/* Line 1455 of yacc.c  */
#line 6502 "parser.y"
    {
	(yyval) = cb_one;
  ;}
    break;

  case 1247:

/* Line 1455 of yacc.c  */
#line 6506 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 1248:

/* Line 1455 of yacc.c  */
#line 6518 "parser.y"
    {
	(yyval) = cb_build_cond ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1249:

/* Line 1455 of yacc.c  */
#line 6525 "parser.y"
    {
	(yyval) = cb_build_expr ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1250:

/* Line 1455 of yacc.c  */
#line 6531 "parser.y"
    {
	current_expr = NULL;
  ;}
    break;

  case 1251:

/* Line 1455 of yacc.c  */
#line 6535 "parser.y"
    {
	(yyval) = cb_list_reverse (current_expr);
  ;}
    break;

  case 1253:

/* Line 1455 of yacc.c  */
#line 6542 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1254:

/* Line 1455 of yacc.c  */
#line 6543 "parser.y"
    { push_expr (')', NULL); ;}
    break;

  case 1255:

/* Line 1455 of yacc.c  */
#line 6545 "parser.y"
    { push_expr ('O', NULL); ;}
    break;

  case 1256:

/* Line 1455 of yacc.c  */
#line 6546 "parser.y"
    { push_expr ('9', NULL); ;}
    break;

  case 1257:

/* Line 1455 of yacc.c  */
#line 6547 "parser.y"
    { push_expr ('A', NULL); ;}
    break;

  case 1258:

/* Line 1455 of yacc.c  */
#line 6548 "parser.y"
    { push_expr ('L', NULL); ;}
    break;

  case 1259:

/* Line 1455 of yacc.c  */
#line 6549 "parser.y"
    { push_expr ('U', NULL); ;}
    break;

  case 1260:

/* Line 1455 of yacc.c  */
#line 6550 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1261:

/* Line 1455 of yacc.c  */
#line 6552 "parser.y"
    { push_expr ('P', NULL); ;}
    break;

  case 1262:

/* Line 1455 of yacc.c  */
#line 6553 "parser.y"
    { push_expr ('N', NULL); ;}
    break;

  case 1263:

/* Line 1455 of yacc.c  */
#line 6554 "parser.y"
    { push_expr ('x', cb_zero); ;}
    break;

  case 1264:

/* Line 1455 of yacc.c  */
#line 6556 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1267:

/* Line 1455 of yacc.c  */
#line 6562 "parser.y"
    { push_expr ('(', NULL); ;}
    break;

  case 1268:

/* Line 1455 of yacc.c  */
#line 6564 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1269:

/* Line 1455 of yacc.c  */
#line 6565 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1270:

/* Line 1455 of yacc.c  */
#line 6566 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1271:

/* Line 1455 of yacc.c  */
#line 6568 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1272:

/* Line 1455 of yacc.c  */
#line 6570 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1273:

/* Line 1455 of yacc.c  */
#line 6571 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1274:

/* Line 1455 of yacc.c  */
#line 6572 "parser.y"
    { push_expr ('*', NULL); ;}
    break;

  case 1275:

/* Line 1455 of yacc.c  */
#line 6573 "parser.y"
    { push_expr ('/', NULL); ;}
    break;

  case 1276:

/* Line 1455 of yacc.c  */
#line 6574 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1277:

/* Line 1455 of yacc.c  */
#line 6576 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1278:

/* Line 1455 of yacc.c  */
#line 6577 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1279:

/* Line 1455 of yacc.c  */
#line 6578 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1280:

/* Line 1455 of yacc.c  */
#line 6579 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1281:

/* Line 1455 of yacc.c  */
#line 6580 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1282:

/* Line 1455 of yacc.c  */
#line 6581 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1283:

/* Line 1455 of yacc.c  */
#line 6583 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1284:

/* Line 1455 of yacc.c  */
#line 6584 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1285:

/* Line 1455 of yacc.c  */
#line 6585 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1286:

/* Line 1455 of yacc.c  */
#line 6586 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1287:

/* Line 1455 of yacc.c  */
#line 6587 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1288:

/* Line 1455 of yacc.c  */
#line 6588 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1289:

/* Line 1455 of yacc.c  */
#line 6590 "parser.y"
    { push_expr ('&', NULL); ;}
    break;

  case 1290:

/* Line 1455 of yacc.c  */
#line 6591 "parser.y"
    { push_expr ('|', NULL); ;}
    break;

  case 1302:

/* Line 1455 of yacc.c  */
#line 6603 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1303:

/* Line 1455 of yacc.c  */
#line 6604 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1307:

/* Line 1455 of yacc.c  */
#line 6613 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1308:

/* Line 1455 of yacc.c  */
#line 6614 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '+', (yyvsp[(3) - (3)])); ;}
    break;

  case 1309:

/* Line 1455 of yacc.c  */
#line 6615 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '-', (yyvsp[(3) - (3)])); ;}
    break;

  case 1310:

/* Line 1455 of yacc.c  */
#line 6616 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '*', (yyvsp[(3) - (3)])); ;}
    break;

  case 1311:

/* Line 1455 of yacc.c  */
#line 6617 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '/', (yyvsp[(3) - (3)])); ;}
    break;

  case 1312:

/* Line 1455 of yacc.c  */
#line 6618 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1313:

/* Line 1455 of yacc.c  */
#line 6619 "parser.y"
    { (yyval) = cb_build_binary_op (cb_zero, '-', (yyvsp[(2) - (2)])); ;}
    break;

  case 1314:

/* Line 1455 of yacc.c  */
#line 6620 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '^', (yyvsp[(3) - (3)])); ;}
    break;

  case 1315:

/* Line 1455 of yacc.c  */
#line 6621 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1316:

/* Line 1455 of yacc.c  */
#line 6633 "parser.y"
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

  case 1317:

/* Line 1455 of yacc.c  */
#line 6645 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(3) - (3)])))) {
		(yyval) = CB_FILE (cb_ref ((yyvsp[(3) - (3)])))->linage_ctr;
	} else {
		cb_error_x ((yyvsp[(3) - (3)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(3) - (3)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1318:

/* Line 1455 of yacc.c  */
#line 6659 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1319:

/* Line 1455 of yacc.c  */
#line 6661 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1320:

/* Line 1455 of yacc.c  */
#line 6665 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)])); ;}
    break;

  case 1321:

/* Line 1455 of yacc.c  */
#line 6671 "parser.y"
    { cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1322:

/* Line 1455 of yacc.c  */
#line 6678 "parser.y"
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

  case 1323:

/* Line 1455 of yacc.c  */
#line 6698 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1324:

/* Line 1455 of yacc.c  */
#line 6702 "parser.y"
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

  case 1325:

/* Line 1455 of yacc.c  */
#line 6718 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (1)])))) {
		(yyval) = (yyvsp[(1) - (1)]);
	} else {
		cb_error_x ((yyvsp[(1) - (1)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(1) - (1)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1326:

/* Line 1455 of yacc.c  */
#line 6731 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1327:

/* Line 1455 of yacc.c  */
#line 6733 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1328:

/* Line 1455 of yacc.c  */
#line 6737 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1329:

/* Line 1455 of yacc.c  */
#line 6743 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1330:

/* Line 1455 of yacc.c  */
#line 6745 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1331:

/* Line 1455 of yacc.c  */
#line 6750 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	CB_REFERENCE ((yyval))->offset = CB_TREE (current_section);
	current_program->label_list = cb_cons ((yyval), current_program->label_list);
  ;}
    break;

  case 1335:

/* Line 1455 of yacc.c  */
#line 6765 "parser.y"
    {
	(yyval) = cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(1) - (1)]))->data));
	(yyval)->source_file = (yyvsp[(1) - (1)])->source_file;
	(yyval)->source_line = (yyvsp[(1) - (1)])->source_line;
  ;}
    break;

  case 1336:

/* Line 1455 of yacc.c  */
#line 6775 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1337:

/* Line 1455 of yacc.c  */
#line 6776 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1338:

/* Line 1455 of yacc.c  */
#line 6781 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	current_program->reference_list = cb_cons ((yyval), current_program->reference_list);
  ;}
    break;

  case 1339:

/* Line 1455 of yacc.c  */
#line 6788 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1340:

/* Line 1455 of yacc.c  */
#line 6789 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1343:

/* Line 1455 of yacc.c  */
#line 6801 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE ((yyval))->word->count > 0) {
		redefinition_error ((yyval));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1344:

/* Line 1455 of yacc.c  */
#line 6820 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1345:

/* Line 1455 of yacc.c  */
#line 6821 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1347:

/* Line 1455 of yacc.c  */
#line 6826 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1348:

/* Line 1455 of yacc.c  */
#line 6830 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1349:

/* Line 1455 of yacc.c  */
#line 6831 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1351:

/* Line 1455 of yacc.c  */
#line 6836 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1352:

/* Line 1455 of yacc.c  */
#line 6837 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1353:

/* Line 1455 of yacc.c  */
#line 6838 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1354:

/* Line 1455 of yacc.c  */
#line 6839 "parser.y"
    { (yyval) = cb_build_ppointer ((yyvsp[(4) - (4)])); ;}
    break;

  case 1355:

/* Line 1455 of yacc.c  */
#line 6840 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1360:

/* Line 1455 of yacc.c  */
#line 6848 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1361:

/* Line 1455 of yacc.c  */
#line 6849 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1362:

/* Line 1455 of yacc.c  */
#line 6850 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1368:

/* Line 1455 of yacc.c  */
#line 6862 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1369:

/* Line 1455 of yacc.c  */
#line 6863 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1381:

/* Line 1455 of yacc.c  */
#line 6897 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1382:

/* Line 1455 of yacc.c  */
#line 6905 "parser.y"
    { (yyval) = cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1383:

/* Line 1455 of yacc.c  */
#line 6909 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1384:

/* Line 1455 of yacc.c  */
#line 6910 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1385:

/* Line 1455 of yacc.c  */
#line 6911 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1386:

/* Line 1455 of yacc.c  */
#line 6912 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 1387:

/* Line 1455 of yacc.c  */
#line 6916 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1388:

/* Line 1455 of yacc.c  */
#line 6917 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); CB_REFERENCE ((yyvsp[(1) - (3)]))->chain = (yyvsp[(3) - (3)]); ;}
    break;

  case 1389:

/* Line 1455 of yacc.c  */
#line 6922 "parser.y"
    {
	if (cb_ref ((yyvsp[(0) - (3)])) != cb_error_node) {
		(yyval) = (yyvsp[(0) - (3)]);
		CB_REFERENCE ((yyvsp[(0) - (3)]))->subs = cb_list_reverse ((yyvsp[(2) - (3)]));
	}
  ;}
    break;

  case 1390:

/* Line 1455 of yacc.c  */
#line 6932 "parser.y"
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

  case 1391:

/* Line 1455 of yacc.c  */
#line 6950 "parser.y"
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

  case 1392:

/* Line 1455 of yacc.c  */
#line 6977 "parser.y"
    {
	if (cb_tree_category ((yyvsp[(1) - (1)])) != CB_CATEGORY_NUMERIC) {
		cb_error (_("Integer value expected"));
	} else if (CB_LITERAL ((yyvsp[(1) - (1)]))->sign < 0 || CB_LITERAL ((yyvsp[(1) - (1)]))->scale) {
		cb_error (_("Integer value expected"));
	}
	(yyval) = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1393:

/* Line 1455 of yacc.c  */
#line 6988 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1394:

/* Line 1455 of yacc.c  */
#line 6990 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (2)]);
	if (CB_LITERAL_P ((yyvsp[(2) - (2)]))) {
		CB_LITERAL ((yyvsp[(2) - (2)]))->all = 1;
	}
  ;}
    break;

  case 1395:

/* Line 1455 of yacc.c  */
#line 6999 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1396:

/* Line 1455 of yacc.c  */
#line 7000 "parser.y"
    { (yyval) = cb_concat_literals ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1397:

/* Line 1455 of yacc.c  */
#line 7004 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1398:

/* Line 1455 of yacc.c  */
#line 7005 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 1399:

/* Line 1455 of yacc.c  */
#line 7006 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1400:

/* Line 1455 of yacc.c  */
#line 7007 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 1401:

/* Line 1455 of yacc.c  */
#line 7008 "parser.y"
    { (yyval) = cb_high; ;}
    break;

  case 1402:

/* Line 1455 of yacc.c  */
#line 7009 "parser.y"
    { (yyval) = cb_low; ;}
    break;

  case 1403:

/* Line 1455 of yacc.c  */
#line 7010 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1404:

/* Line 1455 of yacc.c  */
#line 7019 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1405:

/* Line 1455 of yacc.c  */
#line 7023 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1406:

/* Line 1455 of yacc.c  */
#line 7027 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1407:

/* Line 1455 of yacc.c  */
#line 7031 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1408:

/* Line 1455 of yacc.c  */
#line 7035 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1409:

/* Line 1455 of yacc.c  */
#line 7039 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1410:

/* Line 1455 of yacc.c  */
#line 7043 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1411:

/* Line 1455 of yacc.c  */
#line 7047 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1412:

/* Line 1455 of yacc.c  */
#line 7051 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1413:

/* Line 1455 of yacc.c  */
#line 7055 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), NULL);
  ;}
    break;

  case 1414:

/* Line 1455 of yacc.c  */
#line 7059 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1415:

/* Line 1455 of yacc.c  */
#line 7063 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), NULL);
  ;}
    break;

  case 1416:

/* Line 1455 of yacc.c  */
#line 7069 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1417:

/* Line 1455 of yacc.c  */
#line 7070 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (4)]), NULL); ;}
    break;

  case 1418:

/* Line 1455 of yacc.c  */
#line 7071 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 1419:

/* Line 1455 of yacc.c  */
#line 7075 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1420:

/* Line 1455 of yacc.c  */
#line 7076 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1421:

/* Line 1455 of yacc.c  */
#line 7080 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1422:

/* Line 1455 of yacc.c  */
#line 7081 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1423:

/* Line 1455 of yacc.c  */
#line 7087 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_int0);
  ;}
    break;

  case 1424:

/* Line 1455 of yacc.c  */
#line 7094 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int1);
  ;}
    break;

  case 1425:

/* Line 1455 of yacc.c  */
#line 7101 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int2);
  ;}
    break;

  case 1426:

/* Line 1455 of yacc.c  */
#line 7111 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1427:

/* Line 1455 of yacc.c  */
#line 7118 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1428:

/* Line 1455 of yacc.c  */
#line 7128 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1429:

/* Line 1455 of yacc.c  */
#line 7135 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_ref ((yyvsp[(3) - (3)])));
  ;}
    break;

  case 1430:

/* Line 1455 of yacc.c  */
#line 7148 "parser.y"
    {
	non_const_word = 1;
  ;}
    break;

  case 1431:

/* Line 1455 of yacc.c  */
#line 7158 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1432:

/* Line 1455 of yacc.c  */
#line 7159 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1433:

/* Line 1455 of yacc.c  */
#line 7163 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1434:

/* Line 1455 of yacc.c  */
#line 7164 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1435:

/* Line 1455 of yacc.c  */
#line 7168 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1436:

/* Line 1455 of yacc.c  */
#line 7169 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1437:

/* Line 1455 of yacc.c  */
#line 7173 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1438:

/* Line 1455 of yacc.c  */
#line 7174 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1439:

/* Line 1455 of yacc.c  */
#line 7175 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 1440:

/* Line 1455 of yacc.c  */
#line 7179 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1441:

/* Line 1455 of yacc.c  */
#line 7180 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1442:

/* Line 1455 of yacc.c  */
#line 7184 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1443:

/* Line 1455 of yacc.c  */
#line 7185 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1444:

/* Line 1455 of yacc.c  */
#line 7189 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1445:

/* Line 1455 of yacc.c  */
#line 7190 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1446:

/* Line 1455 of yacc.c  */
#line 7194 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1447:

/* Line 1455 of yacc.c  */
#line 7195 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1459:

/* Line 1455 of yacc.c  */
#line 7208 "parser.y"
    { (yyval) = cb_int1; ;}
    break;



/* Line 1455 of yacc.c  */
#line 14419 "parser.c"
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
#line 7252 "parser.y"


