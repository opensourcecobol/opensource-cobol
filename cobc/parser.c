
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
#define YYLAST   5293

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  453
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  694
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1544
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2275

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
     618,   620,   624,   626,   628,   631,   636,   641,   646,   653,
     658,   662,   666,   669,   672,   675,   676,   680,   681,   684,
     686,   689,   691,   693,   699,   700,   702,   704,   706,   712,
     714,   717,   720,   721,   724,   725,   735,   736,   737,   743,
     744,   748,   749,   752,   756,   759,   762,   764,   766,   767,
     772,   773,   776,   779,   782,   784,   786,   788,   790,   792,
     794,   796,   798,   800,   806,   807,   809,   811,   816,   823,
     833,   834,   838,   839,   842,   843,   846,   850,   852,   854,
     860,   866,   868,   870,   874,   880,   881,   884,   886,   888,
     890,   896,   901,   905,   910,   914,   918,   922,   923,   924,
     930,   931,   933,   934,   937,   941,   946,   949,   951,   952,
     957,   959,   960,   962,   964,   966,   967,   970,   972,   976,
     980,   987,   988,   991,   993,   995,   997,   999,  1001,  1003,
    1005,  1007,  1009,  1011,  1013,  1015,  1017,  1019,  1022,  1026,
    1027,  1030,  1033,  1035,  1037,  1041,  1043,  1045,  1047,  1049,
    1051,  1053,  1055,  1057,  1059,  1061,  1063,  1065,  1067,  1069,
    1071,  1073,  1075,  1077,  1079,  1082,  1085,  1087,  1090,  1093,
    1095,  1098,  1101,  1103,  1106,  1109,  1111,  1114,  1117,  1119,
    1121,  1125,  1129,  1137,  1138,  1141,  1142,  1146,  1148,  1149,
    1155,  1157,  1159,  1160,  1164,  1166,  1169,  1171,  1174,  1177,
    1178,  1180,  1182,  1186,  1188,  1189,  1198,  1200,  1203,  1205,
    1209,  1210,  1214,  1217,  1222,  1225,  1226,  1227,  1233,  1234,
    1235,  1241,  1242,  1243,  1249,  1250,  1252,  1254,  1257,  1263,
    1264,  1267,  1270,  1274,  1276,  1278,  1281,  1284,  1287,  1288,
    1290,  1292,  1295,  1304,  1305,  1309,  1310,  1315,  1316,  1321,
    1322,  1326,  1327,  1331,  1333,  1338,  1341,  1343,  1345,  1346,
    1349,  1354,  1355,  1358,  1360,  1362,  1364,  1366,  1368,  1370,
    1372,  1374,  1376,  1378,  1380,  1382,  1384,  1386,  1388,  1390,
    1394,  1396,  1398,  1400,  1402,  1404,  1406,  1408,  1413,  1418,
    1421,  1423,  1425,  1428,  1432,  1434,  1438,  1445,  1448,  1452,
    1455,  1457,  1460,  1463,  1465,  1468,  1469,  1471,  1473,  1478,
    1481,  1482,  1484,  1486,  1487,  1488,  1489,  1496,  1497,  1499,
    1501,  1504,  1506,  1507,  1513,  1514,  1517,  1519,  1521,  1523,
    1525,  1528,  1531,  1533,  1535,  1537,  1539,  1541,  1543,  1545,
    1547,  1549,  1551,  1557,  1563,  1567,  1571,  1573,  1575,  1577,
    1579,  1581,  1583,  1585,  1588,  1591,  1594,  1595,  1597,  1599,
    1601,  1603,  1604,  1606,  1608,  1610,  1612,  1616,  1617,  1618,
    1619,  1629,  1630,  1631,  1635,  1636,  1640,  1642,  1645,  1650,
    1651,  1654,  1657,  1658,  1662,  1666,  1671,  1675,  1676,  1678,
    1679,  1682,  1683,  1684,  1692,  1693,  1696,  1698,  1700,  1702,
    1705,  1708,  1713,  1716,  1718,  1720,  1721,  1723,  1724,  1725,
    1729,  1730,  1733,  1735,  1737,  1739,  1741,  1743,  1745,  1747,
    1749,  1751,  1753,  1755,  1757,  1759,  1761,  1763,  1765,  1767,
    1769,  1771,  1773,  1775,  1777,  1779,  1781,  1783,  1785,  1787,
    1789,  1791,  1793,  1795,  1797,  1799,  1801,  1803,  1805,  1807,
    1809,  1811,  1813,  1815,  1817,  1819,  1821,  1823,  1825,  1827,
    1829,  1831,  1833,  1834,  1839,  1844,  1849,  1853,  1857,  1861,
    1866,  1870,  1875,  1879,  1883,  1887,  1892,  1898,  1902,  1907,
    1911,  1915,  1916,  1920,  1924,  1927,  1930,  1933,  1937,  1941,
    1945,  1946,  1949,  1951,  1954,  1956,  1958,  1960,  1962,  1964,
    1966,  1968,  1972,  1976,  1980,  1984,  1986,  1988,  1990,  1992,
    1994,  1996,  1997,  1999,  2000,  2005,  2010,  2016,  2023,  2024,
    2027,  2028,  2030,  2031,  2035,  2039,  2045,  2046,  2049,  2052,
    2053,  2059,  2060,  2063,  2064,  2073,  2074,  2075,  2079,  2081,
    2084,  2087,  2091,  2092,  2095,  2098,  2101,  2102,  2105,  2108,
    2109,  2110,  2114,  2115,  2116,  2120,  2121,  2123,  2124,  2128,
    2129,  2132,  2133,  2137,  2138,  2142,  2143,  2145,  2149,  2153,
    2156,  2158,  2160,  2161,  2166,  2171,  2172,  2174,  2176,  2178,
    2180,  2182,  2183,  2190,  2191,  2193,  2194,  2199,  2200,  2205,
    2209,  2213,  2217,  2221,  2226,  2233,  2240,  2247,  2254,  2255,
    2258,  2261,  2263,  2266,  2268,  2270,  2273,  2276,  2278,  2280,
    2282,  2284,  2286,  2290,  2294,  2298,  2302,  2304,  2306,  2307,
    2309,  2310,  2315,  2320,  2327,  2334,  2343,  2352,  2353,  2355,
    2356,  2361,  2362,  2368,  2370,  2374,  2376,  2378,  2380,  2383,
    2385,  2388,  2389,  2393,  2394,  2395,  2399,  2402,  2406,  2408,
    2412,  2415,  2417,  2419,  2421,  2422,  2425,  2426,  2428,  2429,
    2433,  2434,  2436,  2438,  2441,  2443,  2445,  2446,  2450,  2451,
    2455,  2456,  2462,  2463,  2467,  2468,  2471,  2472,  2473,  2482,
    2486,  2487,  2488,  2492,  2493,  2495,  2496,  2504,  2505,  2508,
    2509,  2513,  2517,  2518,  2521,  2523,  2526,  2531,  2533,  2535,
    2537,  2539,  2541,  2543,  2545,  2546,  2548,  2549,  2553,  2554,
    2559,  2561,  2563,  2565,  2567,  2570,  2572,  2574,  2576,  2577,
    2581,  2583,  2586,  2589,  2592,  2594,  2596,  2598,  2601,  2604,
    2606,  2609,  2614,  2617,  2618,  2620,  2622,  2624,  2626,  2631,
    2637,  2638,  2643,  2644,  2646,  2647,  2651,  2652,  2656,  2660,
    2665,  2666,  2671,  2676,  2683,  2684,  2686,  2687,  2691,  2692,
    2698,  2700,  2702,  2704,  2706,  2707,  2711,  2712,  2716,  2719,
    2720,  2724,  2727,  2728,  2733,  2736,  2737,  2739,  2741,  2745,
    2746,  2748,  2751,  2755,  2759,  2760,  2764,  2766,  2770,  2778,
    2779,  2790,  2791,  2794,  2795,  2798,  2801,  2805,  2809,  2812,
    2813,  2817,  2818,  2820,  2822,  2823,  2825,  2826,  2831,  2832,
    2840,  2841,  2843,  2844,  2852,  2853,  2856,  2860,  2861,  2863,
    2865,  2866,  2871,  2876,  2877,  2885,  2886,  2889,  2890,  2891,
    2896,  2898,  2901,  2902,  2907,  2908,  2910,  2911,  2915,  2917,
    2919,  2921,  2923,  2925,  2930,  2935,  2939,  2944,  2946,  2948,
    2950,  2953,  2957,  2959,  2962,  2966,  2970,  2971,  2975,  2976,
    2984,  2985,  2991,  2992,  2995,  2996,  2999,  3000,  3004,  3005,
    3008,  3013,  3014,  3017,  3022,  3023,  3024,  3032,  3033,  3038,
    3041,  3044,  3047,  3050,  3053,  3054,  3056,  3057,  3062,  3065,
    3066,  3069,  3072,  3073,  3082,  3084,  3087,  3089,  3093,  3097,
    3098,  3102,  3103,  3105,  3106,  3111,  3116,  3123,  3130,  3131,
    3133,  3136,  3137,  3139,  3140,  3144,  3145,  3153,  3154,  3159,
    3160,  3162,  3164,  3165,  3175,  3176,  3180,  3182,  3186,  3189,
    3192,  3195,  3199,  3200,  3204,  3205,  3209,  3210,  3214,  3215,
    3217,  3219,  3221,  3223,  3232,  3233,  3235,  3237,  3239,  3241,
    3243,  3245,  3246,  3248,  3249,  3251,  3253,  3255,  3257,  3259,
    3261,  3263,  3264,  3266,  3272,  3274,  3277,  3283,  3284,  3293,
    3294,  3297,  3298,  3303,  3307,  3311,  3313,  3315,  3316,  3318,
    3320,  3321,  3323,  3326,  3329,  3330,  3331,  3335,  3336,  3337,
    3341,  3344,  3345,  3346,  3350,  3351,  3352,  3356,  3359,  3360,
    3361,  3365,  3366,  3367,  3371,  3373,  3375,  3378,  3379,  3383,
    3384,  3388,  3390,  3392,  3395,  3396,  3400,  3401,  3405,  3406,
    3408,  3410,  3412,  3415,  3416,  3420,  3421,  3425,  3426,  3430,
    3432,  3434,  3435,  3438,  3441,  3444,  3447,  3450,  3453,  3456,
    3459,  3462,  3465,  3468,  3471,  3474,  3477,  3478,  3481,  3484,
    3487,  3490,  3493,  3496,  3499,  3502,  3505,  3508,  3511,  3514,
    3517,  3520,  3523,  3526,  3529,  3532,  3535,  3538,  3541,  3544,
    3547,  3550,  3553,  3555,  3558,  3560,  3562,  3565,  3567,  3570,
    3572,  3578,  3580,  3586,  3588,  3592,  3593,  3595,  3597,  3599,
    3603,  3607,  3611,  3615,  3618,  3621,  3625,  3629,  3631,  3635,
    3637,  3640,  3643,  3645,  3647,  3649,  3652,  3654,  3656,  3659,
    3661,  3662,  3665,  3667,  3669,  3671,  3675,  3677,  3679,  3682,
    3684,  3685,  3687,  3689,  3691,  3693,  3695,  3698,  3700,  3704,
    3706,  3709,  3711,  3715,  3719,  3723,  3728,  3732,  3734,  3736,
    3738,  3740,  3744,  3748,  3752,  3754,  3756,  3758,  3760,  3762,
    3764,  3766,  3768,  3770,  3772,  3774,  3776,  3778,  3780,  3782,
    3784,  3786,  3788,  3790,  3792,  3794,  3797,  3800,  3804,  3806,
    3810,  3814,  3819,  3825,  3827,  3829,  3832,  3834,  3838,  3840,
    3842,  3844,  3846,  3848,  3850,  3852,  3855,  3858,  3864,  3870,
    3876,  3882,  3888,  3894,  3900,  3905,  3911,  3914,  3915,  3920,
    3926,  3927,  3931,  3932,  3934,  3936,  3940,  3944,  3946,  3950,
    3952,  3956,  3957,  3958,  3960,  3961,  3963,  3964,  3966,  3967,
    3969,  3971,  3972,  3974,  3975,  3977,  3978,  3980,  3981,  3984,
    3986,  3988,  3991,  3994,  3997,  3999,  4002,  4004,  4005,  4007,
    4008,  4010,  4011,  4013,  4014,  4016,  4017,  4019,  4020,  4022,
    4023,  4025,  4026,  4028,  4029,  4031,  4032,  4034,  4035,  4037,
    4038,  4040,  4041,  4043,  4044,  4046,  4047,  4049,  4050,  4052,
    4053,  4055,  4056,  4058,  4060,  4061,  4063,  4064,  4066,  4068,
    4069,  4071,  4072,  4074,  4075,  4077,  4078,  4080,  4081,  4083,
    4084,  4086,  4089,  4090,  4092,  4093,  4095,  4096,  4098,  4099,
    4101,  4102,  4104,  4105,  4107,  4108,  4110,  4113,  4114,  4116,
    4117,  4119,  4120,  4122,  4123,  4125,  4126,  4128,  4129,  4131,
    4132,  4134,  4135,  4137,  4138
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
     310,  1111,   355,    -1,   355,    -1,   317,    -1,   225,   355,
      -1,   283,  1113,  1121,  1062,    -1,   310,   108,  1121,   372,
      -1,   310,  1123,  1121,  1060,    -1,   310,  1123,  1121,  1060,
     550,   547,    -1,   317,  1123,  1121,  1060,    -1,   330,  1081,
    1108,    -1,   357,  1146,   566,    -1,     9,  1131,    -1,   252,
    1131,    -1,   309,   272,    -1,    -1,   210,   445,   568,    -1,
      -1,   569,   445,    -1,   570,    -1,   569,   570,    -1,   571,
      -1,   573,    -1,   341,   572,  1108,  1118,  1051,    -1,    -1,
     310,    -1,   365,    -1,   366,    -1,   243,  1117,  1140,  1115,
     574,    -1,   575,    -1,   574,   575,    -1,  1052,   576,    -1,
      -1,   292,  1081,    -1,    -1,    97,   115,   445,   578,   609,
     654,   656,   658,   699,    -1,    -1,    -1,   396,   347,   445,
     579,   581,    -1,    -1,   584,   580,   583,    -1,    -1,   581,
     582,    -1,   584,   585,   611,    -1,   585,   611,    -1,   583,
     582,    -1,   163,    -1,   345,    -1,    -1,  1052,   586,   587,
     445,    -1,    -1,   587,   588,    -1,  1121,   162,    -1,  1121,
     182,    -1,   589,    -1,   591,    -1,   595,    -1,   597,    -1,
     599,    -1,   600,    -1,   606,    -1,   607,    -1,   608,    -1,
      46,  1115,  1081,   594,   590,    -1,    -1,   312,    -1,    55,
      -1,   310,  1115,  1081,  1114,    -1,   310,  1115,  1081,   394,
    1081,  1114,    -1,   310,  1121,   426,  1120,  1138,   593,   594,
    1114,   592,    -1,    -1,   109,  1129,  1060,    -1,    -1,  1119,
    1081,    -1,    -1,   394,  1081,    -1,   213,  1102,   596,    -1,
     371,    -1,   270,    -1,   425,   268,   432,  1121,   598,    -1,
     425,   268,   165,  1121,   598,    -1,   228,    -1,  1078,    -1,
      97,  1102,  1059,    -1,   223,  1121,  1062,  1125,   601,    -1,
      -1,   601,   602,    -1,   603,    -1,   604,    -1,   605,    -1,
    1146,   169,  1110,  1062,  1125,    -1,  1110,   400,  1062,  1125,
      -1,  1110,    47,  1062,    -1,   311,  1126,  1121,   432,    -1,
      60,  1121,   432,    -1,   323,  1121,   698,    -1,   325,  1107,
     698,    -1,    -1,    -1,   434,   347,   445,   610,   611,    -1,
      -1,   612,    -1,    -1,   613,   614,    -1,  1092,   615,   445,
      -1,   614,  1092,   615,   445,    -1,   614,   445,    -1,   622,
      -1,    -1,   617,   618,   616,   623,    -1,   432,    -1,    -1,
     166,    -1,   432,    -1,   432,    -1,    -1,  1121,   182,    -1,
    1082,    -1,   219,  1128,  1077,    -1,    49,  1128,  1077,    -1,
     617,   619,    81,   620,  1109,   621,    -1,    -1,   623,   624,
      -1,   625,    -1,   626,    -1,   628,    -1,   629,    -1,   630,
      -1,   632,    -1,   633,    -1,   642,    -1,   643,    -1,   645,
      -1,   646,    -1,   647,    -1,   652,    -1,   653,    -1,   314,
    1077,    -1,  1121,   162,   627,    -1,    -1,    26,   228,    -1,
    1121,   182,    -1,   289,    -1,   631,    -1,   422,  1121,   631,
      -1,    36,    -1,    71,    -1,    73,    -1,    74,    -1,    75,
      -1,    76,    -1,    77,    -1,    78,    -1,   113,    -1,   195,
      -1,   282,    -1,   291,    -1,   304,    -1,   362,    -1,   360,
      -1,   361,    -1,   411,    -1,   409,    -1,   410,    -1,    38,
     359,    -1,    38,   408,    -1,    38,    -1,    41,   359,    -1,
      41,   408,    -1,    41,    -1,    40,   359,    -1,    40,   408,
      -1,    40,    -1,    39,   359,    -1,    39,   408,    -1,    39,
      -1,    37,   359,    -1,    37,   408,    -1,    37,    -1,   245,
      -1,  1137,   217,  1100,    -1,  1137,   401,  1100,    -1,   267,
    1081,   634,  1143,   635,   636,   639,    -1,    -1,   394,  1081,
      -1,    -1,   109,  1129,  1060,    -1,   637,    -1,    -1,   637,
     638,  1123,  1121,  1059,    -1,    27,    -1,   110,    -1,    -1,
     196,  1112,   640,    -1,   641,    -1,   640,   641,    -1,   432,
      -1,   211,  1134,    -1,   384,   644,    -1,    -1,   218,    -1,
     337,    -1,    42,  1145,   438,    -1,    33,    -1,    -1,   425,
    1122,   649,   648,  1145,  1135,  1144,   651,    -1,   650,    -1,
     649,   650,    -1,  1082,    -1,  1082,   391,  1082,    -1,    -1,
     395,  1121,  1082,    -1,   321,  1078,    -1,   321,  1078,   391,
    1078,    -1,    21,   219,    -1,    -1,    -1,   231,   347,   445,
     655,   611,    -1,    -1,    -1,   227,   347,   445,   657,   611,
      -1,    -1,    -1,   323,   347,   445,   659,   660,    -1,    -1,
     661,    -1,   662,    -1,   661,   662,    -1,   308,   698,   663,
     445,   677,    -1,    -1,   663,   664,    -1,  1121,   182,    -1,
      59,  1121,  1073,    -1,   665,    -1,   669,    -1,    85,   666,
      -1,    86,   666,    -1,   667,   668,    -1,    -1,   167,    -1,
    1076,    -1,   668,  1076,    -1,   284,  1122,   675,   670,   671,
     672,   673,   674,    -1,    -1,   187,  1121,  1081,    -1,    -1,
     168,   111,  1121,  1081,    -1,    -1,   214,    88,  1121,  1081,
      -1,    -1,   215,  1121,  1081,    -1,    -1,   169,  1121,  1081,
      -1,  1081,    -1,  1081,   676,  1081,    65,    -1,  1081,   676,
      -1,   225,    -1,   226,    -1,    -1,   677,   678,    -1,   617,
     618,   679,   445,    -1,    -1,   679,   680,    -1,   681,    -1,
     683,    -1,   690,    -1,   629,    -1,   630,    -1,   632,    -1,
     642,    -1,   684,    -1,   645,    -1,   695,    -1,   685,    -1,
     647,    -1,   688,    -1,   696,    -1,   633,    -1,   689,    -1,
     404,  1121,   682,    -1,   327,    -1,   286,    -1,    88,    -1,
     111,    -1,    87,    -1,   285,    -1,   326,    -1,   250,   186,
    1121,  1081,    -1,    64,  1127,  1121,  1081,    -1,    64,   262,
      -1,    65,    -1,   686,    -1,   685,   686,    -1,   381,  1128,
     687,    -1,  1060,    -1,   294,   428,  1032,    -1,   426,  1076,
     174,  1067,    48,  1067,    -1,   691,   692,    -1,   225,   694,
    1122,    -1,   226,  1107,    -1,   693,    -1,   692,   693,    -1,
     290,  1081,    -1,  1081,    -1,   250,   284,    -1,    -1,   261,
      -1,   262,    -1,   367,  1121,  1076,  1099,    -1,   186,   697,
      -1,    -1,   197,    -1,   432,    -1,    -1,    -1,    -1,   342,
     347,   445,   700,   701,   702,    -1,    -1,   703,    -1,   704,
      -1,   703,   704,    -1,   622,    -1,    -1,   617,   618,   705,
     706,   445,    -1,    -1,   706,   707,    -1,    43,    -1,    44,
      -1,    35,    -1,    45,    -1,   153,   148,    -1,   153,   150,
      -1,   188,    -1,   234,    -1,   334,    -1,   405,    -1,   281,
      -1,    30,    -1,   348,    -1,   329,    -1,   175,    -1,   305,
      -1,   225,  1127,  1121,   708,  1075,    -1,    64,  1127,  1121,
     709,  1075,    -1,   171,  1121,  1075,    -1,    32,  1121,  1075,
      -1,   630,    -1,   645,    -1,   642,    -1,   632,    -1,   647,
      -1,   629,    -1,   710,    -1,   424,  1076,    -1,   174,  1074,
      -1,   394,  1076,    -1,    -1,   290,    -1,   439,    -1,   239,
      -1,   440,    -1,    -1,   290,    -1,   439,    -1,   239,    -1,
     440,    -1,   267,  1081,  1143,    -1,    -1,    -1,    -1,   298,
     115,   714,   722,   445,   712,   723,   713,   725,    -1,    -1,
      -1,   424,   715,   717,    -1,    -1,    53,   716,   717,    -1,
     718,    -1,   717,   718,    -1,   719,   720,   721,   432,    -1,
      -1,  1112,   316,    -1,  1112,   425,    -1,    -1,   363,  1121,
      30,    -1,   363,  1121,   105,    -1,   408,   363,  1121,  1081,
      -1,   363,  1121,  1081,    -1,    -1,   274,    -1,    -1,   332,
     432,    -1,    -1,    -1,   104,   445,   724,   725,   121,   104,
     445,    -1,    -1,   725,   726,    -1,   727,    -1,   728,    -1,
     729,    -1,   735,   445,    -1,     1,   445,    -1,   730,   347,
     731,   445,    -1,   432,   445,    -1,   730,    -1,   432,    -1,
      -1,   228,    -1,    -1,    -1,   733,   734,   735,    -1,    -1,
     735,   736,    -1,   737,    -1,   747,    -1,   752,    -1,   756,
      -1,   759,    -1,   772,    -1,   775,    -1,   785,    -1,   780,
      -1,   786,    -1,   787,    -1,   790,    -1,   792,    -1,   799,
      -1,   803,    -1,   805,    -1,   820,    -1,   823,    -1,   825,
      -1,   827,    -1,   830,    -1,   832,    -1,   838,    -1,   847,
      -1,   849,    -1,   866,    -1,   868,    -1,   871,    -1,   875,
      -1,   881,    -1,   891,    -1,   898,    -1,   900,    -1,   903,
      -1,   907,    -1,   908,    -1,   919,    -1,   930,    -1,   940,
      -1,   946,    -1,   949,    -1,   955,    -1,   959,    -1,   961,
      -1,   963,    -1,   965,    -1,   968,    -1,   979,    -1,   992,
      -1,   251,    -1,    -1,     3,   738,   739,   746,    -1,  1076,
     740,   743,   999,    -1,  1076,   174,   155,   212,    -1,  1076,
     174,   226,    -1,  1076,   174,    65,    -1,  1076,   174,    98,
      -1,  1076,   174,    98,   437,    -1,  1076,   174,    99,    -1,
    1076,   174,    99,   436,    -1,  1076,   174,   100,    -1,  1076,
     174,   392,    -1,  1076,   174,    67,    -1,  1076,   174,   147,
     999,    -1,  1076,   174,   145,  1071,   999,    -1,  1076,   174,
      24,    -1,  1076,   174,    25,   999,    -1,  1076,   174,  1054,
      -1,  1076,   174,   432,    -1,    -1,  1110,   741,   742,    -1,
    1110,   742,   741,    -1,  1110,   741,    -1,  1110,   742,    -1,
      29,  1071,    -1,   225,  1127,  1073,    -1,    64,  1127,  1073,
      -1,   292,  1127,  1073,    -1,    -1,   431,   744,    -1,   745,
      -1,   744,   745,    -1,    35,    -1,    45,    -1,   188,    -1,
     234,    -1,   334,    -1,   405,    -1,   281,    -1,   171,  1121,
    1075,    -1,    32,  1121,  1075,    -1,   344,   414,  1031,    -1,
     344,   116,  1031,    -1,    30,    -1,   175,    -1,   329,    -1,
     348,    -1,   415,    -1,   305,    -1,    -1,   122,    -1,    -1,
       5,   748,   749,   751,    -1,  1066,   394,  1047,  1005,    -1,
    1066,   750,   181,  1047,  1005,    -1,    90,  1076,   394,  1076,
    1099,  1005,    -1,    -1,   394,  1067,    -1,    -1,   123,    -1,
      -1,    10,   753,   754,    -1,   432,  1095,   755,    -1,  1033,
      55,  1095,   332,  1065,    -1,    -1,   332,  1065,    -1,    18,
     757,    -1,    -1,   757,  1056,   394,   758,  1056,    -1,    -1,
     300,   394,    -1,    -1,    50,   760,  1074,   761,   766,   767,
     769,   771,    -1,    -1,    -1,   424,   762,   763,    -1,   764,
      -1,   763,   764,    -1,   765,   270,    -1,   765,   720,  1067,
      -1,    -1,  1112,   316,    -1,  1112,    83,    -1,  1112,   425,
      -1,    -1,   332,  1076,    -1,   181,  1076,    -1,    -1,    -1,
     986,   768,   732,    -1,    -1,    -1,   987,   770,   732,    -1,
      -1,   124,    -1,    -1,    51,   773,   774,    -1,    -1,   774,
    1073,    -1,    -1,    58,   776,   777,    -1,    -1,   777,  1052,
     778,    -1,    -1,   779,    -1,   779,  1118,   320,    -1,  1146,
     252,   335,    -1,  1146,   232,    -1,   315,    -1,   406,    -1,
      -1,    72,   781,   782,   783,    -1,  1047,   784,  1033,  1005,
      -1,    -1,   125,    -1,   446,    -1,   151,    -1,    69,    -1,
      84,    -1,    -1,   106,   788,  1052,  1133,  1025,   789,    -1,
      -1,   126,    -1,    -1,   106,   791,   396,  1051,    -1,    -1,
     113,   793,   794,   798,    -1,  1073,   419,  1000,    -1,  1073,
     420,  1000,    -1,  1073,   417,  1000,    -1,  1073,   418,  1000,
      -1,  1066,   740,   795,  1000,    -1,  1066,   740,   416,  1054,
     795,  1000,    -1,  1066,   740,   416,   432,   795,  1000,    -1,
    1066,   740,   416,   296,   795,  1000,    -1,  1066,   740,   416,
      92,   795,  1000,    -1,    -1,  1146,   260,    -1,   431,   796,
      -1,   797,    -1,   796,   797,    -1,    35,    -1,    45,    -1,
     153,   148,    -1,   153,   150,    -1,   188,    -1,   234,    -1,
     334,    -1,   405,    -1,   281,    -1,   171,  1121,  1075,    -1,
      32,  1121,  1075,    -1,   344,   414,  1031,    -1,   344,   116,
    1031,    -1,    43,    -1,    44,    -1,    -1,   127,    -1,    -1,
     114,   800,   801,   802,    -1,  1067,   204,  1047,  1005,    -1,
    1067,   204,  1067,   181,  1047,  1005,    -1,  1067,    48,  1067,
     181,  1047,  1005,    -1,  1067,   204,  1067,   181,  1048,   319,
    1048,  1005,    -1,  1067,    48,  1067,   181,  1048,   319,  1048,
    1005,    -1,    -1,   128,    -1,    -1,   144,   804,   228,   761,
      -1,    -1,   156,   806,   807,   809,   819,    -1,   808,    -1,
     807,  1106,   808,    -1,  1033,    -1,   399,    -1,   395,    -1,
     810,   813,    -1,   811,    -1,   810,   811,    -1,    -1,   815,
     812,   732,    -1,    -1,    -1,   430,   814,   732,    -1,   428,
     816,    -1,   815,   428,   816,    -1,   817,    -1,   816,  1106,
     817,    -1,  1034,   818,    -1,    21,    -1,   399,    -1,   395,
      -1,    -1,   391,  1033,    -1,    -1,   129,    -1,    -1,   160,
     821,   822,    -1,    -1,   301,    -1,   288,    -1,   288,    96,
      -1,   347,    -1,   287,    -1,    -1,   173,   824,  1064,    -1,
      -1,   180,   826,  1076,    -1,    -1,   183,  1144,   828,  1055,
     829,    -1,    -1,   109,  1129,  1076,    -1,    -1,   184,   831,
      -1,    -1,    -1,   191,   833,  1032,  1142,   834,   732,   835,
     837,    -1,   191,     1,   131,    -1,    -1,    -1,   120,   836,
     732,    -1,    -1,   131,    -1,    -1,   198,   839,  1064,   840,
     841,   842,   846,    -1,    -1,  1146,   166,    -1,    -1,     9,
    1144,   425,    -1,   845,  1144,   425,    -1,    -1,   322,   843,
      -1,   844,    -1,   843,   844,    -1,   845,  1116,    48,  1067,
      -1,    12,    -1,    15,    -1,   263,    -1,    16,    -1,   264,
      -1,   245,    -1,   246,    -1,    -1,   105,    -1,    -1,   200,
     848,   668,    -1,    -1,   203,   850,   851,   852,    -1,  1076,
      -1,  1082,    -1,  1085,    -1,   853,    -1,   852,   853,    -1,
     854,    -1,   858,    -1,   863,    -1,    -1,   385,   855,   856,
      -1,   857,    -1,   856,   857,    -1,  1071,   170,    -1,    55,
     864,    -1,     9,    -1,   217,    -1,   401,    -1,  1071,   864,
      -1,   322,   859,    -1,   860,    -1,   859,   860,    -1,    55,
      48,  1071,   864,    -1,   861,   862,    -1,    -1,     9,    -1,
     217,    -1,   168,    -1,   401,    -1,  1071,    48,  1072,   864,
      -1,    89,  1071,   394,  1072,   864,    -1,    -1,   864,   996,
     865,  1067,    -1,    -1,   397,    -1,    -1,   238,   867,   932,
      -1,    -1,   242,   869,   870,    -1,  1067,   394,  1064,    -1,
      90,  1067,   394,  1064,    -1,    -1,   244,   872,   873,   874,
      -1,  1067,    48,  1047,  1005,    -1,  1067,    48,  1067,   181,
    1047,  1005,    -1,    -1,   132,    -1,    -1,   273,   876,   877,
      -1,    -1,   877,   878,   879,  1051,   880,    -1,   201,    -1,
     279,    -1,   209,    -1,   161,    -1,    -1,   357,  1146,   566,
      -1,    -1,  1146,   252,   335,    -1,  1146,   232,    -1,    -1,
     288,   882,   883,    -1,   886,   887,    -1,    -1,   887,   884,
     732,   885,    -1,   887,   133,    -1,    -1,   133,    -1,  1056,
      -1,  1056,   391,  1056,    -1,    -1,   172,    -1,  1074,   393,
      -1,   888,   413,  1032,    -1,   888,   426,   889,    -1,    -1,
    1146,   388,   996,    -1,   890,    -1,   889,     8,   890,    -1,
    1076,   174,  1067,    48,  1067,   413,  1032,    -1,    -1,   309,
     892,  1052,  1096,  1133,   893,   894,   895,   896,   897,    -1,
      -1,   204,  1076,    -1,    -1,   193,   232,    -1,  1146,   232,
      -1,  1146,   252,   232,    -1,  1146,   192,   232,    -1,  1146,
     427,    -1,    -1,   212,  1121,   668,    -1,    -1,  1015,    -1,
    1026,    -1,    -1,   135,    -1,    -1,   318,   899,  1049,   994,
      -1,    -1,   331,   901,  1052,  1133,   893,  1015,   902,    -1,
      -1,   136,    -1,    -1,   336,   904,  1049,   994,   905,  1025,
     906,    -1,    -1,  1146,   232,    -1,  1146,   252,   232,    -1,
      -1,   137,    -1,   338,    -1,    -1,   346,   909,   910,   918,
      -1,  1050,   912,   913,   915,    -1,    -1,     9,  1050,   913,
     428,  1033,   911,   732,    -1,    -1,   426,  1076,    -1,    -1,
      -1,  1110,   121,   914,   732,    -1,   916,    -1,   916,   915,
      -1,    -1,   428,  1032,   917,   732,    -1,    -1,   138,    -1,
      -1,   356,   920,   921,    -1,   922,    -1,   923,    -1,   924,
      -1,   926,    -1,   928,    -1,   145,  1071,   394,  1071,    -1,
    1064,   394,   144,  1070,    -1,  1064,   394,  1067,    -1,  1064,
     925,    48,  1067,    -1,   414,    -1,   116,    -1,   927,    -1,
     926,   927,    -1,  1053,   394,   507,    -1,   929,    -1,   928,
     929,    -1,  1064,   394,   399,    -1,  1064,   394,   395,    -1,
      -1,   365,   931,   932,    -1,    -1,  1078,   934,   936,   937,
     933,   938,   939,    -1,    -1,   934,  1129,   638,  1123,   935,
      -1,    -1,   935,  1078,    -1,    -1,  1103,  1130,    -1,    -1,
    1104,  1121,  1060,    -1,    -1,   424,  1051,    -1,   201,   298,
    1121,   886,    -1,    -1,   181,  1051,    -1,   279,   298,  1121,
     886,    -1,    -1,    -1,   374,   941,  1052,   942,   943,  1025,
     945,    -1,    -1,   212,  1121,   944,   668,    -1,  1097,  1038,
      -1,  1097,  1039,    -1,  1097,  1040,    -1,  1097,  1041,    -1,
    1097,  1042,    -1,    -1,   139,    -1,    -1,   376,   340,   947,
     948,    -1,   376,   228,    -1,    -1,   332,  1067,    -1,   181,
    1067,    -1,    -1,   377,   950,   951,   204,  1076,   953,  1010,
     954,    -1,   952,    -1,   951,   952,    -1,  1067,    -1,   107,
    1112,   363,    -1,   107,  1112,  1067,    -1,    -1,  1146,   291,
    1076,    -1,    -1,   140,    -1,    -1,   380,   956,   957,   958,
      -1,  1066,   174,  1047,  1005,    -1,  1066,   174,  1067,   181,
    1047,  1005,    -1,    90,  1076,   174,  1076,  1099,  1005,    -1,
      -1,   141,    -1,   382,   960,    -1,    -1,   297,    -1,    -1,
     387,   962,   668,    -1,    -1,   402,   964,  1076,   174,  1071,
     394,  1072,    -1,    -1,   407,   966,  1052,   967,    -1,    -1,
     310,    -1,   312,    -1,    -1,   412,   969,  1076,   970,   973,
     953,   977,  1010,   978,    -1,    -1,   107,  1112,   971,    -1,
     972,    -1,   971,   275,   972,    -1,  1093,  1071,    -1,   204,
     974,    -1,   973,   974,    -1,  1076,   975,   976,    -1,    -1,
     108,  1120,  1076,    -1,    -1,    91,  1120,  1076,    -1,    -1,
     385,  1120,  1076,    -1,    -1,   142,    -1,   980,    -1,   989,
      -1,   991,    -1,   423,   981,   983,   984,   985,   988,  1129,
     982,    -1,    -1,   182,    -1,  1051,    -1,   201,    -1,   279,
      -1,   209,    -1,   161,    -1,    -1,     8,    -1,    -1,   371,
      -1,   158,    -1,   154,    -1,   158,    -1,   280,    -1,   256,
      -1,   258,    -1,    -1,   298,    -1,   423,  1118,   102,  1129,
     990,    -1,  1056,    -1,     9,   299,    -1,   423,   981,    34,
     324,  1076,    -1,    -1,   435,   993,  1049,   994,   905,   995,
     997,   998,    -1,    -1,   174,  1073,    -1,    -1,   996,  1105,
    1075,  1124,    -1,   996,  1105,  1054,    -1,   996,  1105,   284,
      -1,    34,    -1,     8,    -1,    -1,  1020,    -1,  1026,    -1,
      -1,   143,    -1,  1001,  1003,    -1,  1001,  1003,    -1,    -1,
      -1,   158,  1002,   732,    -1,    -1,    -1,   256,  1004,   732,
      -1,  1006,  1008,    -1,    -1,    -1,   364,  1007,   732,    -1,
      -1,    -1,   259,  1009,   732,    -1,  1011,  1013,    -1,    -1,
      -1,   280,  1012,   732,    -1,    -1,    -1,   258,  1014,   732,
      -1,  1016,    -1,  1018,    -1,  1016,  1018,    -1,    -1,   121,
    1017,   732,    -1,    -1,   254,  1019,   732,    -1,  1021,    -1,
    1023,    -1,  1021,  1023,    -1,    -1,   149,  1022,   732,    -1,
      -1,   255,  1024,   732,    -1,    -1,  1026,    -1,  1027,    -1,
    1029,    -1,  1027,  1029,    -1,    -1,   207,  1028,   732,    -1,
      -1,   257,  1030,   732,    -1,    -1,  1112,  1075,  1124,    -1,
    1033,    -1,  1034,    -1,    -1,  1035,  1036,    -1,  1036,   208,
      -1,  1037,  1067,    -1,  1036,   447,    -1,  1036,   270,    -1,
    1036,   263,    -1,  1036,    12,    -1,  1036,    13,    -1,  1036,
      14,    -1,  1036,    57,    -1,  1036,   293,    -1,  1036,   249,
      -1,  1036,   438,    -1,  1036,   253,    -1,    -1,  1037,   208,
      -1,  1037,   448,    -1,  1037,   439,    -1,  1037,   440,    -1,
    1037,   444,    -1,  1037,   253,    -1,  1036,   439,    -1,  1036,
     440,    -1,  1036,   441,    -1,  1036,   442,    -1,  1036,   444,
      -1,  1036,  1038,    -1,  1036,  1039,    -1,  1036,  1040,    -1,
    1036,  1041,    -1,  1036,  1042,    -1,  1036,   248,    -1,  1037,
    1038,    -1,  1037,  1039,    -1,  1037,  1040,    -1,  1037,  1041,
      -1,  1037,  1042,    -1,  1037,   248,    -1,  1036,    20,    -1,
    1036,   275,    -1,   446,    -1,   151,  1144,    -1,   152,    -1,
     449,    -1,   185,  1141,    -1,   450,    -1,   220,  1141,    -1,
     179,    -1,   185,  1141,   275,   151,  1144,    -1,   216,    -1,
     220,  1141,   275,   151,  1144,    -1,  1045,    -1,  1043,  1044,
    1045,    -1,    -1,    68,    -1,   351,    -1,  1068,    -1,  1045,
     439,  1045,    -1,  1045,   440,  1045,    -1,  1045,   441,  1045,
      -1,  1045,   442,  1045,    -1,   439,  1045,    -1,   440,  1045,
      -1,  1045,   444,  1045,    -1,   448,  1045,   447,    -1,   224,
      -1,   224,  1101,   432,    -1,  1048,    -1,  1047,  1048,    -1,
    1067,  1099,    -1,  1078,    -1,  1078,    -1,  1052,    -1,  1051,
    1052,    -1,   432,    -1,  1054,    -1,  1053,  1054,    -1,   240,
      -1,    -1,  1055,  1056,    -1,  1057,    -1,  1078,    -1,  1058,
      -1,  1058,  1101,  1058,    -1,   228,    -1,  1060,    -1,  1059,
    1060,    -1,  1078,    -1,    -1,  1060,    -1,  1060,    -1,   228,
      -1,   432,    -1,  1065,    -1,  1064,  1065,    -1,  1076,    -1,
       6,  1128,  1077,    -1,  1067,    -1,  1066,  1067,    -1,  1076,
      -1,   219,  1128,  1077,    -1,   219,  1128,  1083,    -1,   219,
    1128,  1085,    -1,     6,  1128,  1069,  1070,    -1,     6,  1128,
    1077,    -1,  1082,    -1,  1085,    -1,  1046,    -1,  1076,    -1,
     219,  1128,  1077,    -1,   219,  1128,  1083,    -1,   219,  1128,
    1085,    -1,  1083,    -1,  1085,    -1,  1046,    -1,   301,    -1,
     144,    -1,  1077,    -1,   228,    -1,  1076,    -1,  1083,    -1,
    1076,    -1,  1082,    -1,  1076,    -1,   228,    -1,  1076,    -1,
     228,    -1,  1085,    -1,  1076,    -1,  1081,    -1,   438,    -1,
    1077,    -1,  1078,    -1,  1078,  1079,    -1,  1078,  1080,    -1,
    1078,  1079,  1080,    -1,   432,    -1,   432,  1101,  1078,    -1,
     448,  1043,   447,    -1,   448,  1045,   451,   447,    -1,   448,
    1045,   451,  1045,   447,    -1,   228,    -1,  1083,    -1,     9,
    1084,    -1,  1084,    -1,  1083,   452,  1084,    -1,   228,    -1,
     369,    -1,   438,    -1,   306,    -1,   189,    -1,   235,    -1,
     398,    -1,    94,  1086,    -1,   429,  1086,    -1,   421,   448,
    1045,   447,  1086,    -1,   233,   448,  1045,   447,  1086,    -1,
     333,   448,  1045,   447,  1086,    -1,    79,   448,  1043,   447,
    1086,    -1,   378,   448,  1043,   447,  1086,    -1,   379,   448,
    1043,   447,  1086,    -1,   403,   448,  1089,   447,  1086,    -1,
     265,   448,  1090,   447,    -1,   230,   448,  1091,   447,  1086,
      -1,   178,  1087,    -1,    -1,   448,  1045,   451,   447,    -1,
     448,  1045,   451,  1045,   447,    -1,    -1,   448,  1088,   447,
      -1,    -1,  1043,    -1,  1045,    -1,  1045,  1044,   217,    -1,
    1045,  1044,   401,    -1,  1045,    -1,  1045,  1044,  1045,    -1,
    1045,    -1,  1045,  1044,  1060,    -1,    -1,    -1,     9,    -1,
      -1,  1103,    -1,    -1,   199,    -1,    -1,   250,    -1,   295,
      -1,    -1,   253,    -1,    -1,   274,    -1,    -1,   339,    -1,
      -1,   353,  1113,    -1,   194,    -1,   268,    -1,   310,  1121,
      -1,   312,  1107,    -1,   431,   117,    -1,   117,    -1,    61,
     354,    -1,   354,    -1,    -1,     7,    -1,    -1,    17,    -1,
      -1,    22,    -1,    -1,    23,    -1,    -1,    26,    -1,    -1,
      29,    -1,    -1,    36,    -1,    -1,    48,    -1,    -1,    54,
      -1,    -1,    55,    -1,    -1,    82,    -1,    -1,    97,    -1,
      -1,   396,    -1,    -1,   170,    -1,    -1,   174,    -1,    -1,
     194,    -1,    -1,   208,    -1,    -1,   208,    -1,    22,    -1,
      -1,   212,    -1,    -1,   225,    -1,   226,    -1,    -1,   226,
      -1,    -1,   241,    -1,    -1,   261,    -1,    -1,   268,    -1,
      -1,   271,    -1,    -1,   276,    -1,   194,   276,    -1,    -1,
     278,    -1,    -1,   301,    -1,    -1,   310,    -1,    -1,   337,
      -1,    -1,   356,    -1,    -1,   358,    -1,    -1,   358,    -1,
     358,   208,    -1,    -1,   363,    -1,    -1,   375,    -1,    -1,
     386,    -1,    -1,   389,    -1,    -1,   390,    -1,    -1,   393,
      -1,    -1,   394,    -1,    -1,   428,    -1,    -1,   431,    -1
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
    1889,  1898,  1907,  1916,  1925,  1940,  1950,  1957,  1961,  1999,
    2006,  2013,  2017,  2018,  2019,  2027,  2028,  2031,  2032,  2036,
    2037,  2041,  2042,  2048,  2073,  2074,  2075,  2076,  2082,  2089,
    2090,  2094,  2097,  2098,  2106,  2107,  2121,  2122,  2122,  2125,
    2124,  2137,  2138,  2142,  2154,  2163,  2167,  2168,  2178,  2177,
    2195,  2196,  2200,  2207,  2214,  2215,  2216,  2217,  2218,  2219,
    2220,  2221,  2222,  2229,  2233,  2233,  2233,  2239,  2251,  2276,
    2300,  2301,  2308,  2309,  2313,  2314,  2321,  2328,  2329,  2336,
    2340,  2349,  2350,  2356,  2366,  2384,  2385,  2389,  2390,  2391,
    2395,  2402,  2409,  2419,  2426,  2444,  2448,  2459,  2460,  2460,
    2471,  2472,  2476,  2476,  2493,  2494,  2496,  2500,  2502,  2501,
    2532,  2537,  2542,  2548,  2557,  2565,  2566,  2574,  2575,  2576,
    2580,  2600,  2604,  2613,  2614,  2615,  2616,  2617,  2618,  2619,
    2620,  2621,  2622,  2623,  2624,  2625,  2626,  2633,  2655,  2677,
    2678,  2690,  2710,  2717,  2718,  2722,  2723,  2724,  2725,  2726,
    2727,  2728,  2729,  2730,  2731,  2732,  2733,  2738,  2743,  2744,
    2745,  2746,  2747,  2748,  2749,  2750,  2751,  2752,  2753,  2754,
    2755,  2756,  2757,  2758,  2759,  2760,  2761,  2769,  2777,  2785,
    2792,  2797,  2808,  2825,  2826,  2829,  2830,  2837,  2861,  2862,
    2879,  2880,  2883,  2884,  2891,  2892,  2897,  2907,  2914,  2917,
    2918,  2919,  2926,  2933,  2958,  2958,  2963,  2964,  2968,  2969,
    2972,  2973,  2986,  2998,  3018,  3032,  3034,  3033,  3053,  3054,
    3054,  3067,  3069,  3068,  3080,  3081,  3085,  3086,  3095,  3102,
    3105,  3109,  3113,  3114,  3115,  3122,  3123,  3127,  3130,  3130,
    3133,  3134,  3140,  3145,  3146,  3149,  3150,  3153,  3154,  3157,
    3158,  3161,  3162,  3166,  3167,  3168,  3172,  3173,  3176,  3177,
    3181,  3185,  3186,  3190,  3191,  3192,  3193,  3194,  3195,  3196,
    3197,  3198,  3199,  3200,  3201,  3202,  3203,  3204,  3205,  3209,
    3213,  3214,  3215,  3216,  3217,  3218,  3219,  3223,  3227,  3228,
    3229,  3233,  3234,  3238,  3242,  3247,  3251,  3255,  3259,  3260,
    3264,  3265,  3269,  3270,  3271,  3274,  3274,  3274,  3277,  3281,
    3284,  3284,  3287,  3294,  3295,  3296,  3295,  3313,  3314,  3318,
    3319,  3324,  3326,  3325,  3361,  3362,  3366,  3367,  3368,  3369,
    3370,  3371,  3372,  3373,  3374,  3375,  3376,  3377,  3378,  3379,
    3380,  3381,  3382,  3386,  3390,  3394,  3398,  3399,  3400,  3401,
    3402,  3403,  3404,  3405,  3412,  3416,  3426,  3429,  3433,  3437,
    3441,  3449,  3452,  3456,  3460,  3464,  3472,  3485,  3487,  3497,
    3486,  3524,  3526,  3525,  3532,  3531,  3540,  3541,  3546,  3553,
    3555,  3559,  3569,  3571,  3579,  3587,  3616,  3647,  3649,  3659,
    3664,  3675,  3676,  3676,  3703,  3704,  3708,  3709,  3710,  3711,
    3727,  3739,  3770,  3807,  3819,  3822,  3823,  3832,  3836,  3832,
    3849,  3867,  3871,  3872,  3873,  3874,  3875,  3876,  3877,  3878,
    3879,  3880,  3881,  3882,  3883,  3884,  3885,  3886,  3887,  3888,
    3889,  3890,  3891,  3892,  3893,  3894,  3895,  3896,  3897,  3898,
    3899,  3900,  3901,  3902,  3903,  3904,  3905,  3906,  3907,  3908,
    3909,  3910,  3911,  3912,  3913,  3914,  3915,  3916,  3917,  3918,
    3919,  3920,  3943,  3942,  3955,  3959,  3963,  3967,  3971,  3975,
    3979,  3983,  3987,  3991,  3995,  3999,  4003,  4007,  4011,  4015,
    4019,  4026,  4027,  4028,  4029,  4030,  4031,  4035,  4039,  4040,
    4043,  4044,  4048,  4049,  4053,  4054,  4055,  4056,  4057,  4058,
    4059,  4060,  4064,  4068,  4072,  4077,  4078,  4079,  4080,  4081,
    4082,  4086,  4087,  4096,  4096,  4102,  4106,  4110,  4116,  4117,
    4121,  4122,  4131,  4131,  4136,  4140,  4147,  4148,  4157,  4163,
    4164,  4168,  4168,  4176,  4176,  4186,  4188,  4187,  4196,  4197,
    4202,  4209,  4216,  4218,  4222,  4230,  4241,  4242,  4243,  4248,
    4252,  4251,  4263,  4267,  4266,  4277,  4278,  4287,  4287,  4291,
    4292,  4304,  4304,  4308,  4309,  4320,  4321,  4322,  4323,  4324,
    4327,  4327,  4335,  4335,  4341,  4348,  4349,  4352,  4352,  4359,
    4372,  4385,  4385,  4396,  4397,  4406,  4406,  4426,  4425,  4438,
    4442,  4446,  4450,  4454,  4458,  4462,  4467,  4471,  4478,  4479,
    4480,  4484,  4485,  4490,  4491,  4492,  4493,  4494,  4495,  4496,
    4497,  4498,  4499,  4503,  4507,  4511,  4516,  4517,  4521,  4522,
    4531,  4531,  4537,  4541,  4545,  4549,  4553,  4560,  4561,  4570,
    4570,  4592,  4591,  4610,  4611,  4622,  4631,  4636,  4644,  4673,
    4674,  4680,  4679,  4695,  4699,  4698,  4713,  4714,  4719,  4720,
    4731,  4760,  4761,  4762,  4765,  4766,  4770,  4771,  4780,  4780,
    4785,  4786,  4794,  4811,  4828,  4846,  4871,  4871,  4884,  4884,
    4897,  4897,  4906,  4910,  4923,  4923,  4936,  4938,  4936,  4949,
    4954,  4958,  4957,  4971,  4972,  4981,  4981,  4989,  4990,  4994,
    4995,  4996,  5000,  5001,  5006,  5007,  5012,  5016,  5017,  5018,
    5019,  5020,  5021,  5022,  5026,  5027,  5036,  5036,  5049,  5048,
    5058,  5059,  5060,  5064,  5065,  5069,  5070,  5071,  5077,  5077,
    5082,  5083,  5087,  5088,  5089,  5090,  5091,  5092,  5098,  5102,
    5103,  5107,  5112,  5116,  5117,  5118,  5119,  5120,  5124,  5150,
    5163,  5164,  5168,  5168,  5176,  5176,  5186,  5186,  5191,  5195,
    5207,  5207,  5213,  5217,  5224,  5225,  5234,  5234,  5238,  5239,
    5253,  5254,  5255,  5256,  5260,  5261,  5265,  5266,  5267,  5279,
    5279,  5284,  5289,  5288,  5298,  5305,  5306,  5310,  5315,  5324,
    5327,  5331,  5336,  5343,  5350,  5351,  5355,  5356,  5361,  5373,
    5373,  5396,  5397,  5401,  5402,  5406,  5410,  5414,  5418,  5425,
    5426,  5440,  5441,  5442,  5446,  5447,  5456,  5456,  5471,  5471,
    5482,  5483,  5492,  5492,  5503,  5504,  5508,  5515,  5516,  5525,
    5538,  5538,  5544,  5549,  5548,  5559,  5560,  5564,  5566,  5565,
    5576,  5577,  5582,  5581,  5592,  5593,  5602,  5602,  5607,  5608,
    5609,  5610,  5611,  5617,  5626,  5630,  5639,  5646,  5647,  5653,
    5654,  5658,  5667,  5668,  5672,  5676,  5688,  5688,  5694,  5693,
    5710,  5713,  5729,  5730,  5733,  5734,  5738,  5739,  5744,  5749,
    5757,  5769,  5774,  5782,  5798,  5799,  5798,  5819,  5820,  5836,
    5837,  5838,  5839,  5840,  5844,  5845,  5854,  5854,  5859,  5866,
    5867,  5868,  5877,  5877,  5886,  5887,  5891,  5892,  5893,  5897,
    5898,  5902,  5903,  5912,  5912,  5918,  5922,  5926,  5933,  5934,
    5943,  5950,  5951,  5959,  5959,  5972,  5972,  5988,  5988,  5997,
    5999,  6000,  6009,  6009,  6019,  6020,  6025,  6026,  6031,  6038,
    6039,  6044,  6051,  6052,  6056,  6057,  6061,  6062,  6066,  6067,
    6076,  6077,  6078,  6082,  6106,  6109,  6117,  6127,  6132,  6137,
    6142,  6149,  6150,  6153,  6154,  6158,  6158,  6162,  6162,  6166,
    6166,  6169,  6170,  6174,  6181,  6182,  6186,  6198,  6198,  6209,
    6210,  6215,  6218,  6222,  6226,  6233,  6234,  6237,  6238,  6239,
    6243,  6244,  6257,  6265,  6272,  6274,  6273,  6283,  6285,  6284,
    6299,  6303,  6305,  6304,  6315,  6317,  6316,  6333,  6339,  6341,
    6340,  6350,  6352,  6351,  6367,  6372,  6377,  6387,  6386,  6398,
    6397,  6413,  6418,  6423,  6433,  6432,  6444,  6443,  6458,  6459,
    6463,  6468,  6473,  6483,  6482,  6494,  6493,  6510,  6513,  6525,
    6532,  6539,  6539,  6549,  6550,  6551,  6553,  6554,  6555,  6556,
    6557,  6558,  6560,  6561,  6562,  6564,  6567,  6569,  6570,  6572,
    6573,  6574,  6576,  6578,  6579,  6580,  6581,  6582,  6584,  6585,
    6586,  6587,  6588,  6589,  6591,  6592,  6593,  6594,  6595,  6596,
    6598,  6599,  6602,  6602,  6602,  6603,  6603,  6604,  6604,  6605,
    6605,  6606,  6606,  6611,  6612,  6615,  6616,  6617,  6621,  6622,
    6623,  6624,  6625,  6626,  6627,  6628,  6629,  6640,  6652,  6667,
    6668,  6673,  6679,  6685,  6705,  6709,  6725,  6739,  6740,  6745,
    6751,  6752,  6757,  6766,  6767,  6768,  6772,  6783,  6784,  6788,
    6796,  6797,  6801,  6802,  6808,  6828,  6829,  6833,  6834,  6838,
    6839,  6843,  6844,  6845,  6846,  6847,  6848,  6849,  6850,  6851,
    6855,  6856,  6857,  6858,  6859,  6860,  6861,  6865,  6866,  6870,
    6871,  6875,  6876,  6880,  6881,  6892,  6893,  6897,  6898,  6899,
    6903,  6904,  6905,  6913,  6917,  6918,  6919,  6920,  6924,  6925,
    6929,  6939,  6957,  6984,  6996,  6997,  7007,  7008,  7012,  7013,
    7014,  7015,  7016,  7017,  7018,  7026,  7030,  7034,  7038,  7042,
    7046,  7050,  7054,  7058,  7062,  7066,  7070,  7077,  7078,  7079,
    7083,  7084,  7088,  7089,  7094,  7101,  7108,  7118,  7125,  7135,
    7142,  7156,  7166,  7167,  7171,  7172,  7176,  7177,  7181,  7182,
    7183,  7187,  7188,  7192,  7193,  7197,  7198,  7202,  7203,  7210,
    7210,  7211,  7211,  7212,  7212,  7213,  7213,  7215,  7215,  7216,
    7216,  7217,  7217,  7218,  7218,  7219,  7219,  7220,  7220,  7221,
    7221,  7222,  7222,  7223,  7223,  7224,  7224,  7225,  7225,  7226,
    7226,  7227,  7227,  7228,  7228,  7229,  7229,  7230,  7230,  7231,
    7231,  7232,  7232,  7232,  7233,  7233,  7234,  7234,  7234,  7235,
    7235,  7236,  7236,  7237,  7237,  7238,  7238,  7239,  7239,  7240,
    7240,  7240,  7241,  7241,  7242,  7242,  7243,  7243,  7244,  7244,
    7245,  7245,  7246,  7246,  7247,  7247,  7247,  7248,  7248,  7249,
    7249,  7250,  7250,  7251,  7251,  7252,  7252,  7253,  7253,  7254,
    7254,  7256,  7256,  7257,  7257
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
     559,   559,   559,   559,   559,   560,   561,   562,   562,   563,
     564,   565,   566,   566,   566,   567,   567,   568,   568,   569,
     569,   570,   570,   571,   572,   572,   572,   572,   573,   574,
     574,   575,   576,   576,   577,   577,   578,   579,   578,   580,
     578,   581,   581,   582,   583,   583,   584,   584,   586,   585,
     587,   587,   588,   588,   588,   588,   588,   588,   588,   588,
     588,   588,   588,   589,   590,   590,   590,   591,   591,   591,
     592,   592,   593,   593,   594,   594,   595,   596,   596,   597,
     597,   598,   598,   599,   600,   601,   601,   602,   602,   602,
     603,   604,   605,   606,   607,   608,   608,   609,   610,   609,
     611,   611,   613,   612,   614,   614,   614,   615,   616,   615,
     617,   618,   618,   618,   619,   620,   620,   621,   621,   621,
     622,   623,   623,   624,   624,   624,   624,   624,   624,   624,
     624,   624,   624,   624,   624,   624,   624,   625,   626,   627,
     627,   628,   629,   630,   630,   631,   631,   631,   631,   631,
     631,   631,   631,   631,   631,   631,   631,   631,   631,   631,
     631,   631,   631,   631,   631,   631,   631,   631,   631,   631,
     631,   631,   631,   631,   631,   631,   631,   631,   631,   631,
     632,   632,   633,   634,   634,   635,   635,   636,   637,   637,
     638,   638,   639,   639,   640,   640,   641,   642,   643,   644,
     644,   644,   645,   646,   648,   647,   649,   649,   650,   650,
     651,   651,   652,   652,   653,   654,   655,   654,   656,   657,
     656,   658,   659,   658,   660,   660,   661,   661,   662,   663,
     663,   664,   664,   664,   664,   665,   665,   666,   667,   667,
     668,   668,   669,   670,   670,   671,   671,   672,   672,   673,
     673,   674,   674,   675,   675,   675,   676,   676,   677,   677,
     678,   679,   679,   680,   680,   680,   680,   680,   680,   680,
     680,   680,   680,   680,   680,   680,   680,   680,   680,   681,
     682,   682,   682,   682,   682,   682,   682,   683,   684,   684,
     684,   685,   685,   686,   687,   688,   689,   690,   691,   691,
     692,   692,   693,   693,   693,   694,   694,   694,   695,   696,
     697,   697,   698,   699,   700,   701,   699,   702,   702,   703,
     703,   704,   705,   704,   706,   706,   707,   707,   707,   707,
     707,   707,   707,   707,   707,   707,   707,   707,   707,   707,
     707,   707,   707,   707,   707,   707,   707,   707,   707,   707,
     707,   707,   707,   707,   707,   707,   708,   708,   708,   708,
     708,   709,   709,   709,   709,   709,   710,   711,   712,   713,
     711,   714,   715,   714,   716,   714,   717,   717,   718,   719,
     719,   719,   720,   720,   720,   720,   720,   721,   721,   722,
     722,   723,   724,   723,   725,   725,   726,   726,   726,   726,
     726,   727,   728,   729,   730,   731,   731,   733,   734,   732,
     735,   735,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   738,   737,   739,   739,   739,   739,   739,   739,
     739,   739,   739,   739,   739,   739,   739,   739,   739,   739,
     739,   740,   740,   740,   740,   740,   740,   741,   742,   742,
     743,   743,   744,   744,   745,   745,   745,   745,   745,   745,
     745,   745,   745,   745,   745,   745,   745,   745,   745,   745,
     745,   746,   746,   748,   747,   749,   749,   749,   750,   750,
     751,   751,   753,   752,   754,   754,   755,   755,   756,   757,
     757,   758,   758,   760,   759,   761,   762,   761,   763,   763,
     764,   764,   765,   765,   765,   765,   766,   766,   766,   767,
     768,   767,   769,   770,   769,   771,   771,   773,   772,   774,
     774,   776,   775,   777,   777,   778,   778,   778,   778,   778,
     779,   779,   781,   780,   782,   783,   783,   784,   784,   785,
     786,   788,   787,   789,   789,   791,   790,   793,   792,   794,
     794,   794,   794,   794,   794,   794,   794,   794,   795,   795,
     795,   796,   796,   797,   797,   797,   797,   797,   797,   797,
     797,   797,   797,   797,   797,   797,   797,   797,   798,   798,
     800,   799,   801,   801,   801,   801,   801,   802,   802,   804,
     803,   806,   805,   807,   807,   808,   808,   808,   809,   810,
     810,   812,   811,   813,   814,   813,   815,   815,   816,   816,
     817,   817,   817,   817,   818,   818,   819,   819,   821,   820,
     822,   822,   822,   822,   822,   822,   824,   823,   826,   825,
     828,   827,   829,   829,   831,   830,   833,   834,   832,   832,
     835,   836,   835,   837,   837,   839,   838,   840,   840,   841,
     841,   841,   842,   842,   843,   843,   844,   845,   845,   845,
     845,   845,   845,   845,   846,   846,   848,   847,   850,   849,
     851,   851,   851,   852,   852,   853,   853,   853,   855,   854,
     856,   856,   857,   857,   857,   857,   857,   857,   858,   859,
     859,   860,   860,   861,   861,   861,   861,   861,   862,   863,
     864,   864,   865,   865,   867,   866,   869,   868,   870,   870,
     872,   871,   873,   873,   874,   874,   876,   875,   877,   877,
     878,   878,   878,   878,   879,   879,   880,   880,   880,   882,
     881,   883,   884,   883,   883,   885,   885,   886,   886,   887,
     887,   887,   887,   887,   888,   888,   889,   889,   890,   892,
     891,   893,   893,   894,   894,   894,   894,   894,   894,   895,
     895,   896,   896,   896,   897,   897,   899,   898,   901,   900,
     902,   902,   904,   903,   905,   905,   905,   906,   906,   907,
     909,   908,   910,   911,   910,   912,   912,   913,   914,   913,
     915,   915,   917,   916,   918,   918,   920,   919,   921,   921,
     921,   921,   921,   922,   923,   923,   924,   925,   925,   926,
     926,   927,   928,   928,   929,   929,   931,   930,   933,   932,
     934,   934,   935,   935,   936,   936,   937,   937,   938,   938,
     938,   939,   939,   939,   941,   942,   940,   943,   943,   944,
     944,   944,   944,   944,   945,   945,   947,   946,   946,   948,
     948,   948,   950,   949,   951,   951,   952,   952,   952,   953,
     953,   954,   954,   956,   955,   957,   957,   957,   958,   958,
     959,   960,   960,   962,   961,   964,   963,   966,   965,   967,
     967,   967,   969,   968,   970,   970,   971,   971,   972,   973,
     973,   974,   975,   975,   976,   976,   977,   977,   978,   978,
     979,   979,   979,   980,   981,   981,   982,   982,   982,   982,
     982,   983,   983,   984,   984,   985,   985,   986,   986,   987,
     987,   988,   988,   989,   990,   990,   991,   993,   992,   994,
     994,   995,   995,   995,   995,   996,   996,   997,   997,   997,
     998,   998,   999,  1000,  1001,  1002,  1001,  1003,  1004,  1003,
    1005,  1006,  1007,  1006,  1008,  1009,  1008,  1010,  1011,  1012,
    1011,  1013,  1014,  1013,  1015,  1015,  1015,  1017,  1016,  1019,
    1018,  1020,  1020,  1020,  1022,  1021,  1024,  1023,  1025,  1025,
    1026,  1026,  1026,  1028,  1027,  1030,  1029,  1031,  1031,  1032,
    1033,  1035,  1034,  1036,  1036,  1036,  1036,  1036,  1036,  1036,
    1036,  1036,  1036,  1036,  1036,  1036,  1037,  1037,  1037,  1037,
    1037,  1037,  1037,  1037,  1037,  1037,  1037,  1037,  1037,  1037,
    1037,  1037,  1037,  1037,  1037,  1037,  1037,  1037,  1037,  1037,
    1037,  1037,  1038,  1038,  1038,  1039,  1039,  1040,  1040,  1041,
    1041,  1042,  1042,  1043,  1043,  1044,  1044,  1044,  1045,  1045,
    1045,  1045,  1045,  1045,  1045,  1045,  1045,  1046,  1046,  1047,
    1047,  1048,  1049,  1050,  1051,  1051,  1052,  1053,  1053,  1054,
    1055,  1055,  1056,  1057,  1057,  1057,  1058,  1059,  1059,  1060,
    1061,  1061,  1062,  1062,  1063,  1064,  1064,  1065,  1065,  1066,
    1066,  1067,  1067,  1067,  1067,  1067,  1067,  1067,  1067,  1067,
    1068,  1068,  1068,  1068,  1068,  1068,  1068,  1069,  1069,  1070,
    1070,  1071,  1071,  1072,  1072,  1073,  1073,  1074,  1074,  1074,
    1075,  1075,  1075,  1076,  1077,  1077,  1077,  1077,  1078,  1078,
    1079,  1080,  1080,  1081,  1082,  1082,  1083,  1083,  1084,  1084,
    1084,  1084,  1084,  1084,  1084,  1085,  1085,  1085,  1085,  1085,
    1085,  1085,  1085,  1085,  1085,  1085,  1085,  1086,  1086,  1086,
    1087,  1087,  1088,  1088,  1089,  1089,  1089,  1090,  1090,  1091,
    1091,  1092,  1093,  1093,  1094,  1094,  1095,  1095,  1096,  1096,
    1096,  1097,  1097,  1098,  1098,  1099,  1099,  1100,  1100,  1101,
    1101,  1102,  1102,  1103,  1103,  1104,  1104,  1105,  1105,  1106,
    1106,  1107,  1107,  1108,  1108,  1109,  1109,  1110,  1110,  1111,
    1111,  1112,  1112,  1113,  1113,  1114,  1114,  1115,  1115,  1116,
    1116,  1117,  1117,  1118,  1118,  1119,  1119,  1120,  1120,  1121,
    1121,  1122,  1122,  1122,  1123,  1123,  1124,  1124,  1124,  1125,
    1125,  1126,  1126,  1127,  1127,  1128,  1128,  1129,  1129,  1130,
    1130,  1130,  1131,  1131,  1132,  1132,  1133,  1133,  1134,  1134,
    1135,  1135,  1136,  1136,  1137,  1137,  1137,  1138,  1138,  1139,
    1139,  1140,  1140,  1141,  1141,  1142,  1142,  1143,  1143,  1144,
    1144,  1145,  1145,  1146,  1146
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
       2,     1,     1,     5,     0,     1,     1,     1,     5,     1,
       2,     2,     0,     2,     0,     9,     0,     0,     5,     0,
       3,     0,     2,     3,     2,     2,     1,     1,     0,     4,
       0,     2,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     0,     1,     1,     4,     6,     9,
       0,     3,     0,     2,     0,     2,     3,     1,     1,     5,
       5,     1,     1,     3,     5,     0,     2,     1,     1,     1,
       5,     4,     3,     4,     3,     3,     3,     0,     0,     5,
       0,     1,     0,     2,     3,     4,     2,     1,     0,     4,
       1,     0,     1,     1,     1,     0,     2,     1,     3,     3,
       6,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     0,
       2,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     2,     2,     1,
       2,     2,     1,     2,     2,     1,     2,     2,     1,     1,
       3,     3,     7,     0,     2,     0,     3,     1,     0,     5,
       1,     1,     0,     3,     1,     2,     1,     2,     2,     0,
       1,     1,     3,     1,     0,     8,     1,     2,     1,     3,
       0,     3,     2,     4,     2,     0,     0,     5,     0,     0,
       5,     0,     0,     5,     0,     1,     1,     2,     5,     0,
       2,     2,     3,     1,     1,     2,     2,     2,     0,     1,
       1,     2,     8,     0,     3,     0,     4,     0,     4,     0,
       3,     0,     3,     1,     4,     2,     1,     1,     0,     2,
       4,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     4,     4,     2,
       1,     1,     2,     3,     1,     3,     6,     2,     3,     2,
       1,     2,     2,     1,     2,     0,     1,     1,     4,     2,
       0,     1,     1,     0,     0,     0,     6,     0,     1,     1,
       2,     1,     0,     5,     0,     2,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     5,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     0,     1,     1,     1,
       1,     0,     1,     1,     1,     1,     3,     0,     0,     0,
       9,     0,     0,     3,     0,     3,     1,     2,     4,     0,
       2,     2,     0,     3,     3,     4,     3,     0,     1,     0,
       2,     0,     0,     7,     0,     2,     1,     1,     1,     2,
       2,     4,     2,     1,     1,     0,     1,     0,     0,     3,
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     4,     4,     3,     3,     3,     4,
       3,     4,     3,     3,     3,     4,     5,     3,     4,     3,
       3,     0,     3,     3,     2,     2,     2,     3,     3,     3,
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     1,     1,     1,     1,     1,
       1,     0,     1,     0,     4,     4,     5,     6,     0,     2,
       0,     1,     0,     3,     3,     5,     0,     2,     2,     0,
       5,     0,     2,     0,     8,     0,     0,     3,     1,     2,
       2,     3,     0,     2,     2,     2,     0,     2,     2,     0,
       0,     3,     0,     0,     3,     0,     1,     0,     3,     0,
       2,     0,     3,     0,     3,     0,     1,     3,     3,     2,
       1,     1,     0,     4,     4,     0,     1,     1,     1,     1,
       1,     0,     6,     0,     1,     0,     4,     0,     4,     3,
       3,     3,     3,     4,     6,     6,     6,     6,     0,     2,
       2,     1,     2,     1,     1,     2,     2,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     1,     1,     0,     1,
       0,     4,     4,     6,     6,     8,     8,     0,     1,     0,
       4,     0,     5,     1,     3,     1,     1,     1,     2,     1,
       2,     0,     3,     0,     0,     3,     2,     3,     1,     3,
       2,     1,     1,     1,     0,     2,     0,     1,     0,     3,
       0,     1,     1,     2,     1,     1,     0,     3,     0,     3,
       0,     5,     0,     3,     0,     2,     0,     0,     8,     3,
       0,     0,     3,     0,     1,     0,     7,     0,     2,     0,
       3,     3,     0,     2,     1,     2,     4,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     0,     3,     0,     4,
       1,     1,     1,     1,     2,     1,     1,     1,     0,     3,
       1,     2,     2,     2,     1,     1,     1,     2,     2,     1,
       2,     4,     2,     0,     1,     1,     1,     1,     4,     5,
       0,     4,     0,     1,     0,     3,     0,     3,     3,     4,
       0,     4,     4,     6,     0,     1,     0,     3,     0,     5,
       1,     1,     1,     1,     0,     3,     0,     3,     2,     0,
       3,     2,     0,     4,     2,     0,     1,     1,     3,     0,
       1,     2,     3,     3,     0,     3,     1,     3,     7,     0,
      10,     0,     2,     0,     2,     2,     3,     3,     2,     0,
       3,     0,     1,     1,     0,     1,     0,     4,     0,     7,
       0,     1,     0,     7,     0,     2,     3,     0,     1,     1,
       0,     4,     4,     0,     7,     0,     2,     0,     0,     4,
       1,     2,     0,     4,     0,     1,     0,     3,     1,     1,
       1,     1,     1,     4,     4,     3,     4,     1,     1,     1,
       2,     3,     1,     2,     3,     3,     0,     3,     0,     7,
       0,     5,     0,     2,     0,     2,     0,     3,     0,     2,
       4,     0,     2,     4,     0,     0,     7,     0,     4,     2,
       2,     2,     2,     2,     0,     1,     0,     4,     2,     0,
       2,     2,     0,     8,     1,     2,     1,     3,     3,     0,
       3,     0,     1,     0,     4,     4,     6,     6,     0,     1,
       2,     0,     1,     0,     3,     0,     7,     0,     4,     0,
       1,     1,     0,     9,     0,     3,     1,     3,     2,     2,
       2,     3,     0,     3,     0,     3,     0,     3,     0,     1,
       1,     1,     1,     8,     0,     1,     1,     1,     1,     1,
       1,     0,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     5,     1,     2,     5,     0,     8,     0,
       2,     0,     4,     3,     3,     1,     1,     0,     1,     1,
       0,     1,     2,     2,     0,     0,     3,     0,     0,     3,
       2,     0,     0,     3,     0,     0,     3,     2,     0,     0,
       3,     0,     0,     3,     1,     1,     2,     0,     3,     0,
       3,     1,     1,     2,     0,     3,     0,     3,     0,     1,
       1,     1,     2,     0,     3,     0,     3,     0,     3,     1,
       1,     0,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     0,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     1,     2,     1,     1,     2,     1,     2,     1,
       5,     1,     5,     1,     3,     0,     1,     1,     1,     3,
       3,     3,     3,     2,     2,     3,     3,     1,     3,     1,
       2,     2,     1,     1,     1,     2,     1,     1,     2,     1,
       0,     2,     1,     1,     1,     3,     1,     1,     2,     1,
       0,     1,     1,     1,     1,     1,     2,     1,     3,     1,
       2,     1,     3,     3,     3,     4,     3,     1,     1,     1,
       1,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     3,     1,     3,
       3,     4,     5,     1,     1,     2,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     5,     5,     5,
       5,     5,     5,     5,     4,     5,     2,     0,     4,     5,
       0,     3,     0,     1,     1,     3,     3,     1,     3,     1,
       3,     0,     0,     1,     0,     1,     0,     1,     0,     1,
       1,     0,     1,     0,     1,     0,     1,     0,     2,     1,
       1,     2,     2,     2,     1,     2,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     1,     0,     1,     0,     1,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     2,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     2,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     3,     4,     6,     7,
      38,    38,     0,     0,     5,     0,     8,    14,    28,    27,
      29,    29,     0,   254,   254,     0,     0,    24,    40,     0,
       9,    15,    30,    26,  1489,     0,   151,     0,   587,   587,
    1490,     0,     0,     0,     0,     0,     0,    39,   256,     0,
      17,     0,    25,    33,    37,    36,  1514,    35,    42,   153,
       0,   155,   266,   267,     0,   317,   259,   591,    18,    20,
      38,     0,    16,    34,  1515,    32,    41,   159,   157,   237,
       0,     0,   435,     0,   594,   592,   609,     0,    19,    10,
      11,     0,     0,     0,     0,     0,    43,    44,    45,    47,
      46,   154,     0,   235,  1481,   244,   156,     0,   239,   241,
     242,   257,     0,     0,   438,  1326,   260,   320,   268,   599,
     599,     0,     0,     0,   254,    23,    56,    71,    49,    80,
    1443,   160,   159,     0,   152,  1482,  1531,   245,   246,   247,
    1463,   238,   240,   261,   318,     0,     0,   441,   265,     0,
     264,   321,  1431,   270,  1472,   599,   596,   602,     0,   599,
     610,   588,    21,    12,     0,  1489,    54,  1514,    55,  1514,
      60,    62,    63,    64,     0,     0,    70,     0,    73,  1544,
      48,     0,  1543,     0,     0,  1489,  1489,     0,     0,  1522,
    1489,  1489,  1489,  1489,  1489,     0,  1489,  1475,  1489,    79,
       0,    82,    84,    85,    86,    88,    87,    89,    90,    91,
      92,    93,    94,  1444,     0,   158,   237,  1532,  1477,  1464,
    1483,   258,   320,   436,     0,     0,   533,   320,   323,     0,
    1489,   597,  1489,     0,   607,   600,   601,   611,   587,  1489,
       0,    57,  1514,    59,    61,     0,  1456,  1489,     0,    77,
       0,    72,    74,    52,    50,     0,     0,  1344,   106,     0,
       0,  1489,  1489,  1523,  1489,     0,     0,     0,     0,     0,
    1489,     0,  1476,     0,     0,    81,    83,   161,   236,  1478,
       0,  1484,     0,   262,   319,   320,   439,     0,     0,   255,
     263,   326,     0,   330,     0,   331,   327,  1477,  1489,     0,
       0,  1489,  1477,  1501,  1489,  1461,     0,   269,   271,   274,
     275,   276,   277,   278,   279,   280,   281,   282,     0,     0,
    1489,   608,     0,     0,   589,    17,     0,  1393,    69,    58,
    1455,     0,    76,    75,    78,    51,    53,  1489,    98,    99,
       0,     0,     0,  1388,   147,  1339,   146,   100,   101,   150,
       0,   149,   133,  1491,   135,    95,    96,   163,   248,   249,
     252,   243,  1324,   437,   320,   442,     0,     0,   324,   332,
     333,   328,     0,     0,     0,  1489,  1461,     0,     0,     0,
       0,     0,  1502,  1489,     0,  1462,     0,     0,   272,   273,
     603,   604,   606,     0,   598,   612,   614,     0,     0,    68,
       0,  1402,  1398,  1403,  1401,  1399,  1404,  1400,   139,   140,
     142,   148,   145,  1449,  1450,     0,   144,  1493,  1492,   136,
       0,   102,   205,   250,     0,   251,  1325,   440,   444,   534,
     325,   341,   335,   294,   314,  1451,  1452,   303,  1337,   298,
     297,   296,  1343,  1342,  1499,  1475,  1487,     0,   532,   315,
     316,  1489,  1489,   605,   614,     0,     0,    13,    66,    67,
      65,   111,   125,   121,   126,   108,   124,   122,   109,   110,
     123,   107,   112,   113,   115,   141,     0,  1389,   134,   137,
      97,  1501,     0,  1539,   220,     0,  1501,  1489,  1473,  1494,
     223,     0,   222,  1543,   207,   206,   162,   164,   165,   166,
     167,   168,   169,     0,   170,   171,   219,   172,   173,   174,
     175,   176,   177,  1489,   253,     0,   443,   445,   446,   535,
    1489,  1465,     0,     0,   284,  1338,  1500,   305,     0,   287,
    1488,  1527,   313,     0,     0,     0,     0,   624,   615,   616,
     617,   618,   623,     0,     0,   114,   117,     0,   143,   138,
     105,   104,  1529,  1489,  1494,  1540,   184,   224,  1489,     0,
    1474,  1489,  1470,  1489,  1495,     0,  1489,  1489,  1463,     0,
    1489,     0,   449,   447,   537,     0,   423,   365,   398,   386,
     395,   392,   389,  1541,   366,   367,   368,   369,   370,   371,
     372,   373,   374,  1518,   399,     0,   375,   362,   376,   377,
       0,     0,  1525,   379,   380,   378,   419,   382,   383,   381,
    1489,  1491,   342,   343,   344,   345,   346,   347,   363,   348,
     349,   350,   351,   352,   353,   354,   355,   356,     0,     0,
    1466,     0,   336,   295,   286,   285,   283,   304,  1475,  1528,
     292,   301,   300,   302,   299,     0,   620,   622,   625,   682,
     733,   742,   749,   753,   777,   781,   799,   792,   800,   801,
     807,   840,   849,   851,   878,   886,   888,  1539,   894,     0,
     905,   926,   928,   964,   966,   970,   681,   976,   989,  1009,
    1026,  1028,  1032,  1039,  1040,  1056,  1076,  1094,     0,  1112,
    1123,  1131,  1133,  1135,  1137,  1142,  1164,  1187,   619,   631,
     632,   633,   634,   635,   636,   637,   638,   640,   639,   641,
     642,   643,   644,   645,   646,   647,   648,   649,   650,   651,
     652,   653,   654,   655,   656,   657,   658,   659,   660,   661,
     662,   663,   664,   665,   666,   667,   668,   669,   670,   671,
     672,   673,   674,   675,   676,   677,   678,   679,  1160,  1161,
    1162,   680,    22,     0,   116,  1530,  1489,     0,  1489,   186,
     185,   181,     0,  1469,   223,   218,     0,     0,   221,     0,
       0,   230,  1512,  1512,     0,   231,     0,   203,  1489,   331,
     541,   536,   538,   539,   434,   396,   397,   384,   385,   393,
     394,   390,   391,   387,   388,  1542,     0,  1519,   417,   403,
     357,  1384,   432,  1526,   420,   421,   418,     0,     0,   359,
     361,  1447,  1447,     0,  1505,  1505,   340,   337,  1394,  1396,
    1468,   306,   307,   308,   309,     0,     0,   288,  1486,   294,
       0,     0,   626,     0,     0,     0,  1251,   748,     0,   779,
     783,     0,     0,     0,     0,     0,     0,  1251,   880,     0,
       0,   890,   895,     0,  1251,     0,     0,     0,     0,     0,
       0,   978,   999,     0,     0,     0,     0,     0,     0,     0,
       0,  1108,  1106,     0,     0,  1132,  1130,     0,     0,     0,
       0,  1165,  1171,     0,     0,   131,   127,   132,   130,   128,
     129,   118,   119,     0,   192,   193,   191,   190,     0,   179,
     180,     0,   212,   211,   212,   208,   225,   226,   227,   229,
    1513,   232,   233,   234,  1340,  1489,   458,   458,  1491,   478,
     450,   453,   454,     0,   542,   540,   422,     0,  1537,     0,
    1385,  1386,     0,   364,   424,   426,   428,     0,   358,  1473,
     400,   401,  1395,  1506,     0,     0,     0,     0,     0,  1467,
    1475,   293,   613,   621,   731,   701,  1383,  1505,     0,     0,
    1417,  1420,  1505,  1317,     0,     0,     0,     0,     0,     0,
       0,     0,  1417,   740,  1359,   738,  1349,  1351,  1357,  1358,
    1436,   743,     0,  1250,  1266,  1336,     0,  1332,  1334,  1333,
    1378,   755,  1377,  1379,   778,   782,   795,     0,  1319,  1445,
    1516,     0,  1398,   838,   701,     0,  1351,   847,     0,   755,
     857,   856,  1459,   853,   855,   885,   882,   881,   884,   879,
    1505,   887,  1345,  1347,   889,  1330,   899,  1535,  1249,   907,
     927,   460,     0,   930,   931,   932,   965,  1080,     0,   967,
       0,   974,     0,   977,  1000,  1336,   990,   999,   992,     0,
     997,     0,  1333,     0,  1438,  1189,  1322,  1516,  1189,     0,
    1054,  1045,  1323,     0,  1329,  1057,  1058,  1059,  1060,  1061,
    1069,  1062,  1072,     0,  1327,     0,  1077,  1095,  1109,  1471,
       0,  1114,  1116,     0,  1128,     0,  1134,     0,  1139,  1144,
    1172,     0,  1173,  1507,  1189,     0,   103,  1434,   188,   187,
     178,   189,     0,   210,   209,  1489,   202,   196,  1341,   204,
       0,   459,   455,     0,   456,     0,   448,   451,   544,   404,
    1538,   405,  1505,     0,     0,     0,  1305,  1303,  1366,  1308,
    1360,  1364,  1365,     0,  1387,   433,  1541,   427,     0,   360,
    1448,   339,   338,  1397,   312,  1499,     0,   290,   732,   683,
    1468,     0,   710,     0,     0,     0,     0,     0,  1405,  1422,
    1416,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1406,   741,   734,     0,     0,  1350,  1437,   746,  1436,
    1252,     0,   751,     0,   756,   766,  1376,   780,  1375,   785,
     796,   793,   798,   797,  1251,  1320,  1446,  1321,  1517,  1238,
     806,   839,   808,   818,  1204,  1204,  1204,  1204,   848,   841,
       0,     0,   850,  1460,  1251,   876,   863,   859,   861,  1251,
     883,     0,  1346,   892,  1536,   897,   909,     0,   461,     0,
     953,   938,   929,   933,   935,   936,   937,  1084,     0,     0,
     975,   971,     0,   983,   980,   982,   981,   984,   991,   994,
     627,  1251,     0,     0,  1001,     0,  1439,  1440,  1516,     0,
    1027,  1011,  1034,  1047,  1055,  1041,     0,  1047,     0,  1371,
    1372,  1070,  1073,     0,     0,  1328,  1068,     0,  1067,     0,
    1097,     0,     0,  1107,     0,     0,  1115,     0,  1129,  1124,
       0,     0,  1140,  1141,  1138,  1471,     0,     0,  1174,     0,
    1508,     0,  1034,   120,  1454,     0,   196,   194,  1435,     0,
     215,   201,   228,     0,   452,   457,   463,   473,   331,   479,
    1524,  1507,   408,     0,  1313,  1314,     0,  1306,  1307,  1390,
       0,     0,     0,     0,     0,     0,     0,     0,  1520,   429,
     311,  1499,  1507,   289,   706,   697,  1204,   687,   694,   688,
     690,   692,     0,  1204,     0,   686,   693,   700,   699,     0,
    1204,  1503,  1503,  1503,   704,   705,  1368,  1367,     0,  1356,
    1305,  1303,     0,     0,  1305,     0,  1352,  1353,  1354,  1318,
    1305,     0,     0,  1305,     0,     0,  1305,  1305,  1305,     0,
       0,  1211,  1445,     0,     0,   744,     0,  1258,  1259,  1260,
    1290,  1261,  1539,  1294,  1299,  1533,  1253,  1301,  1533,  1283,
    1263,  1265,  1257,  1256,  1291,  1262,  1264,  1273,  1274,  1275,
    1276,  1277,  1292,  1255,  1295,  1297,  1278,  1279,  1280,  1281,
    1282,  1267,  1289,  1272,  1269,  1270,  1271,  1268,  1284,  1285,
    1286,  1287,  1288,  1254,     0,     0,  1335,   762,     0,     0,
     769,   790,   791,   784,   786,     0,  1211,  1243,  1245,   803,
    1239,  1240,  1241,     0,  1544,  1204,     0,  1205,   811,  1207,
     812,   809,   810,     0,  1211,  1445,   871,   873,   872,   866,
     868,   874,   877,   852,   864,   860,   858,  1251,   627,   854,
    1348,  1507,   891,  1331,   627,  1539,   917,   918,   920,   922,
     923,   919,   921,   912,  1539,   908,     0,   954,     0,   956,
     955,   957,   948,   949,     0,     0,   934,  1086,  1509,     0,
       0,   968,  1211,  1445,  1543,     0,   995,   628,  1002,  1003,
    1006,     0,   998,  1196,  1195,  1005,  1011,  1190,     0,     0,
    1238,     0,     0,     0,  1046,     0,     0,     0,  1071,     0,
    1075,  1074,  1065,     0,  1489,  1238,  1111,  1110,  1117,  1118,
    1119,     0,  1211,  1445,     0,  1432,     0,  1119,  1186,  1176,
    1175,  1181,     0,  1183,  1184,  1191,  1453,  1434,     0,   198,
     199,   197,  1489,   465,   476,   477,   475,   333,   481,   557,
    1489,   548,   546,   547,   549,  1503,     0,  1489,     0,   560,
     552,  1503,   553,     0,   556,   561,   559,   554,   558,     0,
     555,     0,   543,   571,   566,   569,   568,   567,   570,   545,
     572,     0,   412,   407,  1361,  1362,  1363,  1316,  1304,  1309,
    1310,  1311,  1312,  1315,  1391,     0,  1521,  1539,   310,     0,
     698,  1207,   689,   691,  1204,   695,   685,   725,  1489,   714,
     715,  1489,   726,   716,   717,   720,   730,   727,   718,     0,
     728,   719,   729,   711,   712,   684,  1504,     0,     0,     0,
     702,   703,  1370,  1355,  1369,  1417,  1445,     0,  1421,     0,
    1417,  1417,     0,  1414,  1417,  1417,  1417,     0,  1417,  1417,
    1212,   735,  1214,  1211,   747,     0,  1293,  1534,  1296,  1298,
     752,   750,   757,   758,   602,     0,   768,   767,  1177,  1178,
     772,   770,     0,   789,     0,   794,   627,   627,   804,   802,
    1242,   818,   818,   818,   818,  1489,   823,   836,   837,   824,
       0,  1489,   827,   828,   831,   829,     0,   830,   820,   821,
     813,   819,   627,  1208,  1203,     0,   842,     0,  1251,  1251,
     870,   627,   867,   862,     0,   900,     0,     0,   924,     0,
       0,     0,   950,   952,     0,   944,   960,   945,   946,   939,
     940,   960,  1078,  1489,     0,  1510,  1085,   410,   411,  1494,
     969,   972,     0,     0,   986,   996,   993,   630,     0,     0,
    1013,  1012,  1227,  1229,  1030,  1224,  1225,  1037,  1035,     0,
    1251,  1048,  1251,  1042,  1050,  1063,  1064,  1066,  1441,  1104,
    1218,     0,  1445,  1125,     0,     0,  1433,  1145,  1146,     0,
    1149,  1152,  1156,  1150,  1182,  1507,  1185,  1197,  1457,   195,
       0,   216,   217,   213,     0,     0,   467,     0,  1524,     0,
    1489,   550,   551,     0,   574,  1489,  1537,   575,   573,   406,
    1471,   402,  1494,  1392,   430,   291,  1202,   696,     0,     0,
    1247,  1247,   713,   708,   707,   709,  1410,  1211,  1418,     0,
    1430,  1415,  1408,  1428,  1409,  1411,  1412,  1425,  1426,  1413,
    1407,   627,  1215,  1210,   736,   745,     0,     0,   759,   760,
       0,   764,   763,   765,  1179,  1180,   775,   773,   627,   787,
     788,  1244,  1246,  1204,  1204,  1204,  1204,     0,   825,   826,
       0,  1247,  1247,   822,  1206,   627,  1211,  1319,  1211,  1319,
     869,   875,   865,   893,   901,   903,   910,   913,   914,  1479,
     925,   906,   911,   960,  1373,  1374,   960,     0,   943,   941,
     942,   947,  1088,     0,  1511,  1082,  1211,   985,   979,     0,
     629,  1007,     0,     0,  1019,     0,   627,   627,  1031,  1029,
    1226,  1038,  1033,  1036,  1043,   627,  1052,  1051,  1442,     0,
       0,  1105,  1096,  1219,  1121,  1221,     0,  1211,  1211,  1136,
    1432,  1148,  1487,  1154,  1487,  1218,     0,  1234,  1236,  1200,
    1198,  1231,  1232,  1199,  1458,     0,   214,   464,  1489,     0,
     469,   474,  1503,   510,   530,   525,  1461,     0,     0,  1489,
    1505,  1489,     0,   480,   486,   487,   488,   497,   489,   491,
     494,   482,   483,   484,   490,   493,   511,   495,   498,   485,
       0,   492,   496,  1382,   565,  1380,  1381,   581,   564,   576,
     586,     0,  1489,  1489,   425,   722,   721,   724,     0,   723,
     737,  1419,  1213,   627,  1539,  1539,   761,   776,   754,   627,
     771,   817,   816,   815,   814,   833,   832,   835,   834,  1209,
     844,     0,   843,     0,   627,   904,   898,   915,  1480,     0,
     959,   951,   960,   962,     0,     0,  1091,  1087,  1081,   973,
     988,     0,     0,  1014,  1489,  1021,     0,  1015,     0,  1018,
    1228,  1230,   627,  1049,   627,  1098,  1099,  1100,  1101,  1102,
    1103,   627,  1122,  1113,  1222,  1217,  1120,  1127,  1126,  1147,
       0,  1487,  1151,     0,  1158,  1170,  1167,  1169,  1168,  1163,
    1166,   627,   627,  1201,  1188,  1233,  1194,  1193,  1496,     0,
    1489,  1489,   471,   509,  1489,   531,   529,   526,   527,  1491,
     519,  1489,  1251,     0,     0,     0,     0,   512,     0,     0,
     517,   520,   523,   584,   582,   583,   585,     0,   579,   577,
     578,   580,     0,   416,   413,   414,     0,     0,  1496,  1216,
    1300,  1302,   774,  1211,  1211,   902,     0,   958,   963,     0,
    1489,  1089,     0,     0,  1079,  1083,   987,     0,     0,  1024,
    1022,  1023,  1017,  1016,  1044,  1053,  1220,   627,  1153,     0,
    1157,  1159,  1143,  1235,  1237,  1497,  1498,  1192,   466,     0,
       0,  1489,   462,     0,   518,     0,   515,  1445,   513,   514,
     504,   502,   503,   505,   501,   506,   500,   499,     0,   524,
     522,   521,   563,   562,   415,   409,   431,  1248,   846,   845,
     916,   961,     0,  1092,  1489,  1251,  1020,  1025,  1010,  1223,
    1155,   468,   470,     0,   508,   507,   528,     0,  1090,     0,
    1008,   472,     0,  1093,   516
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
      79,   103,   101,   131,   357,   422,   497,   498,   901,   761,
    1100,   499,   897,   500,  1312,  1313,  1579,  1107,   501,   502,
     503,   504,   905,  1103,  1833,   505,   506,   507,   508,   509,
     510,   511,   512,   775,   134,   106,   107,   108,   109,   140,
     110,   358,   359,   425,    30,    65,   143,    83,   221,   148,
     116,   149,   117,   153,   230,   308,   309,   636,   310,  1343,
     829,   524,   311,   441,   312,   642,   313,   314,   637,   821,
     822,   823,   824,   315,   316,   317,    82,   222,   150,   151,
     152,   228,   294,   431,   295,   371,   372,   521,   816,   296,
     520,   612,   613,   614,   938,   615,   616,   617,   618,   619,
     620,   928,  1322,  1622,  1623,  1779,  1851,  2174,  2175,   621,
     622,   806,   623,   624,   625,  1136,   934,   935,  2044,   626,
     627,   114,   285,   147,   364,   226,   428,   516,   517,   518,
     778,   920,   921,  1112,  1113,  1030,   922,  1583,  1836,  2000,
    2142,  2222,  1316,  1586,  1116,  1319,  1838,  2021,  2022,  2237,
    2023,  2024,  2025,  2026,  2228,  2027,  2028,  2029,  2030,  2160,
    2161,  2149,  2031,  2032,  2146,   449,   289,   519,   574,   781,
     782,   783,  1118,  1320,  1619,  2172,  2167,  1620,    50,   237,
     396,    86,   120,   119,   155,   156,   157,   234,   322,   122,
     324,   454,   455,   538,   539,   540,   541,   542,   833,  1526,
    1527,  1787,   543,   699,   700,   834,   954,  1152,  1364,  1365,
    1360,  1663,  1664,  1149,   701,   835,   973,  1175,  1173,   702,
     836,   981,  1395,   703,   837,  1445,   704,   838,  1185,  1447,
    1702,  1703,  1704,  1450,  1710,  1898,  1896,  2059,  2058,   705,
     839,   994,   706,   840,   995,  1453,  1454,   707,   841,   996,
    1191,  1194,   708,   709,   710,   842,  1719,   711,   843,   712,
     844,  1003,  1465,  1738,  1739,  1202,   713,   845,  1007,  1209,
     714,   846,   715,   847,  1012,  1013,  1215,  1216,  1217,  1488,
    1486,  1751,  1218,  1479,  1480,  1750,  1483,   716,   848,  1019,
     717,   849,   718,   850,   719,  1025,  1492,   720,   852,   721,
     854,  1494,  1925,  2074,  2076,   722,   855,  1226,  1503,  1758,
    1927,  1928,  1929,  1931,   723,   856,   724,   857,  1032,  1232,
    1233,  1234,  1515,  1769,  1770,  1235,  1512,  1513,  1514,  1763,
    1236,  1938,  2189,   725,   858,   726,   859,  1039,   727,   860,
    1041,  1241,   728,   861,  1043,  1247,  1525,  1948,   729,   862,
    1046,  1250,  1786,  1047,  1048,  1049,  1529,  1530,   730,   863,
    1539,  1954,  2095,  2199,  2258,   731,   864,   732,   865,  1959,
     733,   866,  1540,  1962,   734,   735,   867,  1060,  2102,  1267,
    1542,  1965,  1803,  1804,  2104,  1265,   736,   868,  1065,  1066,
    1067,  1068,  1279,  1069,  1070,  1071,  1072,   737,   869,  1036,
    1942,  1237,  2088,  1517,  1772,  2086,  2194,   738,   870,  1280,
    1555,  1969,  1972,   739,  1078,  1283,   740,   873,  1080,  1081,
    1810,  2113,   741,   874,  1084,  1289,   742,   876,   743,   877,
     744,   878,   745,   879,  1294,   746,   880,  1296,  1817,  1818,
    1567,  1820,  1983,  2122,  1985,  2212,   747,   748,   882,  2129,
    1092,  1299,  1571,  1711,  1897,  1825,   749,  1573,   750,   751,
     884,  1260,  1827,  2083,  1989,  2134,  1640,  1468,  1469,  1742,
    1744,  1915,  1691,  1692,  1881,  1883,  2053,  1974,  1975,  2111,
    2115,  2207,  1794,  1795,  1956,  1796,  1957,  1990,  1991,  2131,
    1992,  2132,  1459,  1460,  1461,  1716,  1462,  1717,  2047,  1027,
    1028,   983,   984,  1180,  1181,  1426,  1427,  1428,  1429,  1430,
    1126,  1330,  1371,   974,   997,  1195,  1055,  1061,   361,   362,
    1073,  1074,  1223,  1050,   987,   988,   437,   443,  1109,   444,
     258,  1021,  1022,   975,   999,  1129,  1368,  1673,  1771,  1933,
    1005,  1051,  2034,   977,   956,   801,   930,   931,  2036,   978,
     818,   819,   979,  1158,  1160,  1375,  1389,  1384,  1381,   229,
    1819,  1307,  1178,  1258,  1970,   214,  1197,   940,   415,   377,
    1308,   247,  1995,  1748,   386,   220,   631,  1153,   565,   158,
     561,   273,   280,  2079,   136,   282,   830,   531,    42,   420,
     566,  2217,   527,   383,  1667,   944,  1301,  1776,   911,   174,
    1199,   798,  1637,   264,   629,   640,   756,   218,  1698,  1225,
    1121,   556,   796,  1466
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1695
static const yytype_int16 yypact[] =
{
   -1695,   276,    69, -1695,  -166,  -154,    69, -1695, -1695, -1695,
     173,   173,   415,   415, -1695,   522, -1695, -1695, -1695, -1695,
     645,   645,   234,   598,   598,   497,   311, -1695,   812,   784,
   -1695, -1695, -1695, -1695,   -28,   609,   873,   530,   721,   721,
   -1695,   628,    84,   646,   670,   771,   710, -1695,   211,  1043,
     875,  1040, -1695,   -74, -1695, -1695,   915, -1695, -1695, -1695,
     774, -1695, -1695, -1695,   881,   801, -1695,    59, -1695,   489,
     173,   415, -1695, -1695, -1695, -1695,   565, -1695,  1074,   700,
     798,   904,  1015,   830, -1695, -1695,   935,   415, -1695, -1695,
   -1695,   824,   839,   842,   847,   855, -1695, -1695, -1695, -1695,
   -1695,   925,   857,  1097,   917,   640, -1695,   429, -1695, -1695,
   -1695, -1695,   870,   972,  1089, -1695,   445,   888, -1695,    42,
      42,   890,   882,   883,   598, -1695,   111,  1147,   101,  1418,
    1050, -1695, -1695,   896, -1695, -1695,   940, -1695, -1695, -1695,
    1326, -1695, -1695, -1695, -1695,   907,  1010,  1035, -1695,   830,
   -1695, -1695, -1695, -1695, -1695,   287, -1695,   602,   -60,   288,
   -1695, -1695, -1695, -1695,   999,  1155, -1695,   380, -1695,   418,
   -1695, -1695, -1695, -1695,   149,   153, -1695,   -39, -1695, -1695,
   -1695,   919,   677,  1265,   936,  1155,  1155,   936,  1004,  1024,
    1155,  1155,  1155,  1155,  1155,   936,  1155,  1329,  1155, -1695,
    1413, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695,   936,   925,   700, -1695,  1303, -1695,
    1217,   445,   888, -1695,   943,  1042,  1053,   888,   618,   960,
     329, -1695,  1155,  1041,  1122, -1695, -1695,  1301,   721,  1155,
    1187, -1695,   546, -1695, -1695,  1062, -1695,  1155,  1213, -1695,
      52, -1695, -1695, -1695, -1695,   977,  1185, -1695, -1695,   936,
     936,  1155,  1155, -1695,  1155,   996,  1364,   936,   936,   996,
    1155,   996, -1695,   936,    32, -1695, -1695, -1695, -1695, -1695,
     830, -1695,   830, -1695, -1695,   888, -1695,   990,  1092, -1695,
   -1695, -1695,   960, -1695,  1000,    -1, -1695,  1303,  1155,   866,
     866,  1155,    33,  1200,  1155,  1424,  1179, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,    99,   718,
    1155, -1695,  1017,  1006, -1695,   875,  1187, -1695, -1695, -1695,
   -1695,   996, -1695, -1695, -1695, -1695, -1695,  1155, -1695, -1695,
    1197,   996,  1224,   556, -1695, -1695, -1695, -1695, -1695, -1695,
     996, -1695, -1695,    89, -1695, -1695, -1695, -1695,   830, -1695,
    1161,   830, -1695, -1695,   888, -1695,  1011,  1016, -1695, -1695,
    1376, -1695,  1378,  1187,  1028,  1155,  1424,   996,   -46,   -53,
    1187,  1037, -1695,  1155,  1032, -1695,  1032,   155, -1695, -1695,
   -1695, -1695, -1695,  1187, -1695, -1695, -1695,   492,    53, -1695,
    1302, -1695, -1695, -1695, -1695, -1695, -1695, -1695,  1197, -1695,
    1075, -1695, -1695, -1695, -1695,   996, -1695, -1695, -1695, -1695,
    1187, -1695,   869, -1695,  1187, -1695, -1695, -1695,  1160, -1695,
   -1695, -1695,    78,  1081, -1695, -1695, -1695,   996, -1695, -1695,
   -1695, -1695, -1695, -1695,  1250,    79,  1284,  1048, -1695, -1695,
   -1695,  1155,  1155, -1695, -1695,  2252,   415, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695,   742, -1695,   135, -1695,  1197, -1695,  1187, -1695,
     879,  1200,  1174,  1093, -1695,  1131,  1200,  1155,  1435,    94,
       7,  1187, -1695,  1059, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695,  1117, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695,  1155, -1695,  1032, -1695,  1160, -1695, -1695,
    4384,  1467,  1312,  1187,   112, -1695, -1695, -1695,  1187, -1695,
   -1695,  1133, -1695,    -2,    -2,  1535,  1052,  1055, -1695, -1695,
   -1695, -1695,  1151,  3058,  1056, -1695, -1695,   742, -1695, -1695,
   -1695, -1695,  1127,  1155,  1292, -1695,   851, -1695,  1155,   641,
   -1695,  1155, -1695,  1155, -1695,  1154,  1155,  1155,  1326,   168,
    1155,  1082, -1695, -1695,   960,  1298, -1695, -1695,   -95,   300,
     502,   627,   643,  1094, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695,  1183, -1695,  1187, -1695, -1695, -1695, -1695,
     996,   996,  1320, -1695, -1695, -1695,   416, -1695, -1695, -1695,
    1155,   179, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,   790,   362,
   -1695,   213, -1695, -1695, -1695, -1695, -1695,   129,  1329, -1695,
      68, -1695, -1695, -1695, -1695,  1429, -1695, -1695,  1315, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,  1148,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695,  1093, -1695,  1033,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,    20, -1695,
   -1695,  1249, -1695, -1695, -1695, -1695,   134, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695,  1101, -1695, -1695,  1155,   229,  1155, -1695,
   -1695,   488,   187,  1511, -1695, -1695,   -53,  1176, -1695,   996,
     996, -1695,  1272,  1272,  1280, -1695,   996, -1695,   109,    -1,
   -1695, -1695,   960, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695,  1123, -1695, -1695,  1169,
   -1695,  1119,  1178, -1695, -1695, -1695, -1695,  2798,   496,  1551,
   -1695,  1225,  1225,  1197,  1328,  1328, -1695, -1695,  1136, -1695,
   -1695, -1695, -1695, -1695, -1695,    45,  1430, -1695, -1695,  1081,
    1187,  1153, -1695,  1157,   996,  3569,  1168,    12,  2081, -1695,
   -1695,  4075,   830,  1207,  4131,  4075,  1381,   752,   791,    77,
     996, -1695, -1695,  1475, -1695,    77,   996,  2085,   996,  3635,
    4075, -1695,  1671,   830,   996,   830,   996,    50,    90,   996,
     830, -1695, -1695,  3691,  3747, -1695, -1695,   996,   996,   830,
     996, -1695,   260,  1509,   996, -1695, -1695, -1695, -1695, -1695,
   -1695,  1599, -1695,   936, -1695, -1695, -1695, -1695,   996,    10,
      43,    46,  1190, -1695,  1190, -1695, -1695, -1695,   282, -1695,
   -1695, -1695, -1695, -1695,   996,  1155,  1451,  1451,   179, -1695,
   -1695, -1695, -1695,  1440, -1695, -1695, -1695,  1187,  1239,  4845,
    1186, -1695,   996, -1695,   496, -1695,  1245,  1409, -1695,  1435,
   -1695, -1695, -1695, -1695,   996,   996,  1197,   -53,   -53,  1614,
    1329, -1695, -1695, -1695,  1522,   159, -1695,  1328,  1198,   996,
    1202,  1203,  1328,   556,  1204,  1206,  1211,  1212,  1214,  1216,
    1218,  1219,  1202,  1532, -1695,  3811, -1695, -1695, -1695, -1695,
    1446, -1695,  1606, -1695, -1695, -1695,  1271, -1695,   556, -1695,
   -1695,  1246, -1695, -1695,   123,   830,  1544,  2002, -1695,  1334,
    1366,   830,   778,  1553,  3334,   877,   956,  1550,   554,  1246,
   -1695, -1695,    56, -1695, -1695, -1695,  1585, -1695, -1695, -1695,
    1328,    77, -1695, -1695, -1695, -1695, -1695,  1293, -1695,    85,
     996, -1695,    55, -1695, -1695, -1695, -1695, -1695,  4075, -1695,
    1290,  1554,  1637,   735, -1695,  1295, -1695,  1966,  1556,   707,
    1299,  1300,   469,  1304,   737,  1520, -1695,  1366,  1520,   996,
    1558,  1273, -1695,   982, -1695, -1695, -1695, -1695, -1695,  1457,
   -1695,    77, -1695,   385, -1695,    76, -1695, -1695,   495,  1650,
    3453, -1695, -1695,   996,  1559,  3953,   996,  1528,   878,  1596,
   -1695,  1380,  1335,  1434,  1520,  1101, -1695,   167, -1695, -1695,
   -1695, -1695,     0, -1695, -1695,  1155, -1695, -1695, -1695, -1695,
     123, -1695, -1695,   996, -1695,  1187,   960, -1695, -1695, -1695,
   -1695,  1598,  1328,  4845,  4845,  4845,    21,   832, -1695, -1695,
   -1695,  1136, -1695,  4845, -1695, -1695,  1094, -1695,   496, -1695,
   -1695, -1695, -1695, -1695, -1695,  1250,   -53,  1600, -1695, -1695,
     982,   899,  1279,   501,    39,  4845,  1317,  4845, -1695,  4845,
   -1695,  3222,  1281,  4845,  4845,  4845,  4845,  4845,  4845,  4845,
    4845, -1695, -1695, -1695,  4075,  1533, -1695, -1695,  1384,  1446,
    1085,  2834,  1417,  1492, -1695,   553, -1695, -1695, -1695,   -15,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,   470,
     830, -1695, -1695,   -64,  1563,  1563,  1563,  1563, -1695, -1695,
    4075,  4075, -1695, -1695,   128,  1593,   776, -1695,  1296,   752,
   -1695,   996, -1695,   116, -1695, -1695,   823,  1557, -1695,   982,
     161, -1695,    55, -1695, -1695, -1695, -1695,    61,  1331,    77,
   -1695, -1695,  4075, -1695, -1695, -1695, -1695,  1370, -1695, -1695,
   -1695, -1695,   996,    12, -1695,  1019, -1695, -1695,  1366,   123,
   -1695,  1524,   616,   804, -1695, -1695,   996,   804,  1336, -1695,
    1136, -1695, -1695,    75,   879, -1695, -1695,  3362, -1695,  1683,
    1525,  4075,  4075, -1695,  3833,   996, -1695,  1560, -1695, -1695,
    4075,   982, -1695, -1695, -1695,  1650,  1537,   996, -1695,  1003,
   -1695,    86,   616, -1695, -1695,  1615, -1695, -1695, -1695,  1465,
   -1695, -1695,   996,   996, -1695,   996,  1555,   957,     3, -1695,
    4546,  1434, -1695,  3222,  1305,  1305,   903, -1695, -1695, -1695,
    4845,  4845,  4845,  4845,  4845,  4845,  4660,   832,  1387, -1695,
   -1695,  1250,  1434, -1695, -1695, -1695,  1563, -1695, -1695,  1307,
    1309, -1695,   982,  1563,  1534, -1695, -1695, -1695, -1695,  1324,
    1563,  1486,  1486,  1486,   145,  1526, -1695, -1695,   160, -1695,
      41,   838,   996,  1132,    54,  1306, -1695,  1136, -1695, -1695,
     263,  1308,   959,   576,  1310,  1140,   121,   125,   589,  1311,
    1150,  4009,    24,  4075,    77, -1695,  1420, -1695, -1695, -1695,
   -1695, -1695,  1093, -1695, -1695,  1365, -1695, -1695,  1365, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695,  1368,    12, -1695,   150,   996,   996,
      63, -1695, -1695, -1695,    44,   858,  1395, -1695, -1695,  1634,
   -1695,  1506, -1695,    14,  1595,  1563,  1504, -1695, -1695,  1512,
   -1695, -1695, -1695,  1586,  4009,   293, -1695, -1695, -1695,  2576,
   -1695,  1379, -1695, -1695, -1695, -1695, -1695,   128, -1695, -1695,
   -1695,  1434, -1695, -1695, -1695,  1093, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695,  1447,  1093, -1695,  1377, -1695,  1724, -1695,
   -1695, -1695,   939, -1695,   982,  1012, -1695,   149,   678,   837,
      77,    77,  4009,   449,  1059,   830,  1641, -1695, -1695,  1767,
   -1695,  1602, -1695, -1695, -1695, -1695,  1524, -1695,   996,    87,
     470,   874,  1350,  1659, -1695,  1353,   982,   765, -1695,   160,
   -1695, -1695, -1695,  4075,  1155,   470, -1695, -1695, -1695, -1695,
     -92,   996,  4009,   528,  1388,  1775,   996,   455, -1695, -1695,
   -1695,  1487,  1488, -1695, -1695,  1019, -1695,   126,   683, -1695,
   -1695, -1695,  1155,  1621, -1695, -1695,  1187, -1695, -1695, -1695,
    1155, -1695, -1695, -1695, -1695,  1486,  1065,  1155,  2081, -1695,
   -1695,  1486, -1695,  1187, -1695, -1695, -1695, -1695, -1695,   996,
   -1695,   996, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695,   996,  1594,   837, -1695,  1136, -1695, -1695,   838,   862,
     862,  1305,  1305,  1305, -1695,  1173, -1695,  1093, -1695,   996,
   -1695,  1512, -1695, -1695,  1563, -1695, -1695, -1695,  1155, -1695,
   -1695,  1155, -1695, -1695, -1695, -1695, -1695, -1695, -1695,     4,
   -1695, -1695, -1695,  1324, -1695, -1695, -1695,   123,   123,   123,
   -1695, -1695, -1695, -1695, -1695,  1202,  1334,  4797, -1695,   996,
    1202,  1202,  4845, -1695,  1202,  1202,  1202,   384,  1202,  1202,
   -1695, -1695,  1536,  4009, -1695,    77, -1695, -1695,  1516,  1518,
   -1695, -1695,  3301, -1695,   566,   103, -1695, -1695, -1695, -1695,
     969, -1695,  1474, -1695,  1464, -1695, -1695, -1695, -1695, -1695,
   -1695,   313,   313,   313,   313,  1155, -1695, -1695, -1695, -1695,
    1083,  1155, -1695, -1695, -1695, -1695,    11, -1695,  1595, -1695,
   -1695, -1695, -1695, -1695, -1695,  4075, -1695,  4075,   128, -1695,
   -1695, -1695,  2576, -1695,   996,  1680,  1382,   868,  1697,  1389,
      93,   982, -1695, -1695,  1757, -1695, -1695, -1695, -1695,  1012,
   -1695,  1636, -1695,  1155,  1539, -1695, -1695, -1695, -1695,  1292,
      77, -1695,  4075,   168,   705, -1695, -1695, -1695,   996,  4075,
     649, -1695, -1695, -1695,  1676,  1564, -1695,  1682, -1695,  1581,
   -1695, -1695, -1695, -1695,  1353, -1695, -1695, -1695,  1567,  1678,
    1541,  1542,  1334, -1695,  4075,    93, -1695,  1549, -1695,   982,
   -1695,  1717,  1441, -1695, -1695,  1434, -1695,   783,  1820, -1695,
     946, -1695, -1695, -1695,  1187,  1719,  1622,  1763,  4783,   186,
    1155, -1695, -1695,   186, -1695,  1155,  1239, -1695, -1695, -1695,
    1650, -1695,  1292, -1695,  1442, -1695, -1695, -1695,   186,   186,
     131,   131, -1695, -1695, -1695, -1695, -1695,  1395, -1695,  1184,
   -1695, -1695, -1695,   838, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695,  1687,  1688, -1695, -1695,
    4075, -1695, -1695, -1695, -1695, -1695,  1716, -1695, -1695, -1695,
   -1695, -1695, -1695,  1563,  1563,  1563,  1563,   186, -1695, -1695,
     186,   131,   131, -1695, -1695, -1695,  4009,  1523,  4009,  1540,
   -1695, -1695, -1695, -1695, -1695,  1710, -1695,   868, -1695,  1750,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695,    93,  1019, -1695,
   -1695,  1019,   -48,   996, -1695, -1695,  4009, -1695, -1695,   891,
    3115, -1695,  1803,  1620,  1642,   637, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,   996,
    1069, -1695, -1695, -1695,  1715,  1603,   996,  1395,  4009, -1695,
    1775, -1695,  1284,  1765,  1284,  1541,   420, -1695, -1695,  1720,
   -1695,  1605, -1695, -1695, -1695,   517, -1695, -1695,  1155,  1774,
    1649, -1695,   930, -1695,  1668,   947,  1424,  1681,  1444,  1155,
    1328,  1155,   996, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695,  1489, -1695, -1695, -1695, -1695,
      37, -1695, -1695, -1695, -1695, -1695, -1695,   621, -1695,   632,
   -1695,  1436,  1155,  1155, -1695, -1695, -1695, -1695,   186, -1695,
   -1695, -1695, -1695, -1695,  1093,  1093, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695,  4075, -1695,  4075, -1695, -1695, -1695, -1695, -1695,  1821,
    1019,  1019, -1695,  1477,  1577,   830,    47, -1695,   996, -1695,
   -1695,  1543,  4075, -1695,  1155,   754,  1645, -1695,  1652, -1695,
   -1695, -1695, -1695, -1695, -1695,   996, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
     996,  1284, -1695,   996,  1740, -1695, -1695, -1695, -1695, -1695,
     830, -1695, -1695, -1695, -1695, -1695, -1695, -1695,  1084,  1187,
    1155,  1155,  1718, -1695,  1155, -1695, -1695, -1695, -1695,   179,
   -1695,  1155, -1695,   996,   996,   803,  1711, -1695,  1604,  1187,
      37, -1695, -1695, -1695, -1695, -1695, -1695,   186, -1695, -1695,
   -1695, -1695,   186, -1695,  1436, -1695,   996,   496,  1084, -1695,
   -1695, -1695, -1695,  1395,  1395, -1695,  4075,  1019, -1695,  4075,
    1155,   830,   830,  1588, -1695, -1695, -1695,  1476,   996,  1755,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,   996,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,  1187,
    1187,  1155, -1695,  1187, -1695,  1187, -1695,  1334, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,  4075, -1695,
   -1695, -1695, -1695, -1695, -1695,   996, -1695, -1695, -1695, -1695,
   -1695, -1695,    12,   830,  1155, -1695,   996, -1695, -1695, -1695,
   -1695, -1695, -1695,  1187, -1695, -1695, -1695,  1844, -1695,    12,
   -1695, -1695,  4075, -1695, -1695
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1695, -1695, -1695, -1695,  1887, -1695, -1695, -1695,    36, -1695,
   -1695, -1695, -1695, -1695,  1569, -1695, -1695, -1695,  1166, -1695,
   -1695,    74,  1874, -1695, -1695,  1843,   239, -1695, -1695, -1695,
   -1695, -1695,  1721,  1769, -1695, -1695,  1735,    80, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695,  1728, -1695, -1695, -1695, -1695,
    1707, -1695, -1695, -1695,   634, -1695, -1695, -1695, -1695,  1438,
   -1695, -1695,  1367,   821, -1695, -1695, -1695, -1695, -1695, -1695,
    1510, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695,  1787, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695,   615, -1695,   611,   828, -1695, -1695,
   -1695, -1695, -1695,  1026,    98, -1695,  1373, -1695, -1695, -1695,
   -1695, -1695, -1695,   151, -1695,  1722, -1695,  1826, -1695, -1695,
   -1695, -1695,  1582, -1695,   795, -1695, -1695, -1695, -1695,  1714,
   -1695,  1893,  1794, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695,  1115, -1695, -1695, -1695,  1412, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,   740, -1695,
   -1695, -1695,  1657, -1695,  -530,  -728, -1695, -1695, -1695,  -367,
   -1695, -1695, -1695, -1695, -1695, -1695, -1272, -1264,  1143, -1262,
     113, -1695, -1695, -1695, -1695,   330, -1695, -1695,  -222, -1255,
   -1695, -1695, -1250, -1695, -1249, -1695, -1695,  1020, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,  1439,
   -1695, -1695, -1695,  1038, -1695,  -866, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695,   -68, -1695, -1695, -1695, -1695, -1695, -1695,
    -201, -1695, -1695, -1695, -1695,  -159, -1695, -1695, -1695, -1695,
   -1695,  1180, -1695, -1695, -1695, -1695, -1695, -1695,   557, -1695,
   -1695, -1695, -1695, -1695,  1840,  1014, -1695,   257, -1695, -1695,
   -1695, -1695,  1514, -1695, -1695, -1695, -1695, -1695, -1695,  -872,
   -1695, -1695,   176, -1695, -1695, -1695, -1695,   961,   599,   605,
   -1695, -1695,   303, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,   962, -1695,
   -1695,   270, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695,  -167, -1695,   235, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695,   755, -1695, -1695,   760, -1695,
   -1695, -1695, -1695,   498,   231, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695,    64,   756, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
     761, -1695, -1695, -1695,   225, -1695, -1695,   483, -1695, -1695,
   -1695, -1342, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1203,   949, -1695, -1695,   209, -1695, -1695,
     462, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695,   697, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
     736, -1695,   198, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695,   937, -1695,   934, -1695, -1695,  1138,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,   929,
     443, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,    35,
   -1695,   446, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695, -1695,
   -1695,  -254, -1695, -1139, -1695, -1695, -1187, -1128, -1083, -1695,
     371, -1695, -1018, -1695, -1695, -1695, -1695,    31, -1695, -1695,
   -1695, -1695,   -77, -1695, -1695,   224, -1695, -1695, -1695, -1695,
      29, -1695,  -481, -1694, -1695, -1695,   561, -1695,  -816, -1231,
    -811, -1168, -1695, -1695, -1695, -1164, -1160, -1149, -1144, -1140,
     -14,  -264,  -427,  -670,  -869,  -829,  -599,   964,  -985,   -83,
   -1695, -1054, -1695,  -795, -1695,   841,  -150,  -256, -1695,  -537,
    -142,  -805,  -972,  -591,  -731, -1695, -1695,   479,  -999, -1543,
    -947,  -812,  -855,   954,  -576,  -231, -1695,  1102,  -233,  -626,
    -352,  -272,  -477,  -920, -1695, -1695, -1695, -1695, -1695,  1805,
   -1695,   454,   856, -1695, -1695, -1695, -1622,  1222,   114,  1736,
     802,  -408, -1695,  1029,  -373,  1478, -1695,  -594, -1695, -1061,
    1103,  -383,   666, -1695, -1695,  -657, -1695, -1372,  -163,  -607,
    -480,  -135,  -945,   663, -1302,  -807, -1157, -1695,  1275,  1988,
    -630, -1695, -1695, -1695, -1695, -1695, -1695, -1695,   644, -1695,
     205,  -661,   918,  -127
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1544
static const yytype_int16 yytable[] =
{
     118,   183,   240,   436,   808,   817,   851,   328,   945,   344,
     567,  1086,   998,   349,   513,   351,  1200,  1438,  1284,  1275,
    1528,  1439,   259,   260,   800,   982,   991,   265,   266,   267,
     268,   269,  1440,   271,   345,   274,  1014,  1441,   345,   883,
     345,  1442,   986,   825,   779,   261,  1481,  1187,  1613,  1222,
    1029,   924,  1171,   270,  1867,   183,  1614,  1222,  1615,  1059,
    1668,  1669,   529,  1075,  1268,  1616,   118,   318,   410,   319,
    1617,  1618,   277,  1213,   758,   399,   326,  1470,  1471,  1472,
    1519,  1020,  1020,  1020,   331,   411,   392,    21, -1507,  1327,
     154,  1020,   947,   398,   416,  1572,  1020,  1358,   340,   341,
     345,   342,   813,  1222,   976,    88,  1721,   350,   458,  1327,
     345,   417,    84,   976,  1008,   279,  1535,   338,   339,   345,
    1860,   438,  1327,  -182,   355,   347,   348,  1911,  1040,  1042,
     562,   354,   356,  1993,   272,   374,   410,   175,   379,   381,
     433,   384,  1082,   976,  1229,    91,   345,   445,   345,  1476,
    1154,  1344,   546,  2084,    53,  1161,  -183,   393,   820,  1098,
     453,   123,   248,  1314,  1621,   369,  1645,   634,   915,   369,
    1507, -1507, -1514,  1665,   400,   442, -1467,   772,  1304,   154,
      40,   525,   936,  1366,   477,  1639,  1891,   479,  1150,  1327,
    1977,   514,  1276,  1327,   916,   917, -1543,   360,   154, -1543,
    1340,   417,   563, -1543,   548,  -739,   345,   780,  1792,  1361,
     245,   419,   435,  1221,   281, -1494,  1508, -1543,   902,   564,
     447,  1708,   813, -1467,   439,  1491,   641,   450,  2192,   906,
    1506,  1034,  1309, -1471,  1565,  1063, -1483, -1543,  -182,    54,
     985,    40,   828,  1304,  1176,   549,     4,  1315,   871,   244,
      17, -1543,   779,  1004,  1064,   827,   235,   333,   568,  1128,
   -1489,   388,   814,  1641,   785,   327,  1273,  1058,  1090,   522,
    1641,  -183,  1979,  1176,  1099,   360,     3,  1641,   426,    12,
     334,   389,   401,  1085,  1304,  1094,    40,  2158,   533,   534,
     633,    13,  1564,  1840,  1091,   638, -1485,   418, -1543,  1845,
    1451,  1222,   643,   643,   281,  1391,   564,  1238,   936,    90,
    1722,  1115,  1537,   786,   985,  1323,   881,    40,    15,  1481,
     451,   402,   244,    55,   559,   440,  2193,  2159,   403,  1509,
    1064,  1327,  1300,  1151,  1754,   154,   154,  1740,  1310,   179,
    1367,  1793,  1474,  1709,   985,   998,   903,   894,   164,  1082,
     571,  1186,  1463,  1644,  1176,  1146,   572,   628, -1471, -1471,
     872,   993,   799,  1196, -1483,   236,   569,  1464,  1141,  1142,
     802,     5,  1328,  1522,    62,   297,  2085,  1230,  1510,   343,
    1035,   249,   998,  1456, -1467,   993,  1705,   418,  1672,   298,
     757,  1452,  1328,   918,  2082,   762,  1638,    54,   766,   404,
     767,  2201,   401,   769,   770,  1328,   251,   776,  1014,  1724,
    1144,  1145,    74,   998,   327,   780,   179,   -31,  1861,  1892,
     773,  1562,  1694,   904,   635,  1912,   299,  1261,  1493,  1941,
     343,   370,   815,    88,  1521,  1587,  1828,  1363,  1715, -1494,
    1231,   402,  -182,  1392,   343,   948,  1723,   807,   403, -1469,
    1443, -1467,  1132,  1128,  1128,  1128,  1746,  1857,  1532, -1489,
     165,   998,   405,  1128,   257, -1514, -1471, -1471,  1329,  1547,
    1277,   343,  1328,   528,  1747,  -183,  1328,   774,   343,  1473,
    1475,    55,   343,    85,  1214,  1128,   459,  1128,  1675,  1128,
    1278,   406,  1305,  1128,  1128,  1128,  1128,  1128,  1128,  1128,
    1128, -1423,  1127,   246,  1781,   813,  1574,   343,   343,   343,
     826,  1523,  1339,   908,   909,  1764,   179,   343,   343,   404,
     914,   257,   343,  1477,  1693,   343,   547,  1478,  1893, -1467,
     544,   407,   179,   166,  1105,   345,   895,    40,   345,   345,
    1784,   942,   300,   166,  1813,   345,  1552,  1805,   343,  1222,
    1556,  1557,   301,  1559,   919,   343,    63,  1305,   343,  1563,
     179,  1641,  1511, -1471,   998,  1361,  2014,  1147,  1685, -1471,
     993,  1966,  1686, -1543,  2015, -1471,  2016,  1131,  1369,   811,
    1481,  2125,   405,  2018,   896,  1376,  1318,   452,  2019,  2020,
    1588,  2080,   343,   893,  2081,   898,    51,   951,  1305,  -200,
     899,  1877,  1210, -1471, -1471,  2266,   989,    64,    62,  1341,
    2120,   406,  2123,  1106,  1328,   923,  1753,   164,   343,  -595,
    -593,  2126,  1755,    87,  2033,  1064,   456,  1037,  1536,  2127,
    1782,  1052,  1196,  1056,   804,  1056,  1062,    22,  1037,   302,
     303,  1705,  1097,    18,  1327,  1490,  1132,  1132,  1132,  1105,
    1701,   407,   304,  1056,   305,   164,  1132,  1327,  1108,   787,
    1128,  1128,  1128,  1128,  1128,  1128,  1128,   345,  1986,  1543,
    1101,    25,   104,  1543,  1143,  1884,  1281,  1457,  1132,    28,
    1132,    74,  1132,   345,  1378,   401,  1132,  1132,  1132,  1132,
    1132,  1132,  1132,  1132,  1119,    29,  1324,  1325,  1326,  2128,
    2144,  1135,  1331,  1332,  1333,  1334,  1337,  1335,   788,  1814,
   -1429,  1270, -1471, -1471,  -200,  1780,   345,   345,    19,    74,
    1863,  1864,  1865,  1885,   402,    32,  1362,  1458,  1106,   165,
    1373,   403,  -595,  -593,  1448,  1053,  1380,  1382,  1383,  1385,
    2187,  1696,  1388,  1390,  1464,   327, -1543,  1624,   390,  2209,
     413,  1096,  1110,   805,   306,  1866,    33,  1064,  1211,  1000,
    1871,  1872,  1936,   812,  1874,  1875,  1876,   165,  1879,  1880,
     105,  1131,  1131,  1131,   307,  2061,  2062,  2063,  2064,  1274,
    1054,  1131,  1057,   164,   900,  1878,  1844,  1077,  1196,  2041,
      63,     5,  1674,  1363,     5,   325,  1088,  1712,  1270,  2048,
    2048,  2136,   404,  1131,  1262,  1131,  2106,  1131,  1222,  1377,
    2107,  1131,  1131,  1131,  1131,  1131,  1131,  1131,  1131,    31,
    1981,  2108,  1807,   391,   414,   241,  2109,  1282,  1062,  2096,
    2110,    92,  1495,   820,  1756,  1496,  1889,   484,  1497,  1498,
    1302, -1543,  1953,  1759,  1901,  1902,  1626,    74, -1543,  2050,
    2048,  2048,   115,  1132,  1132,  1132,  1132,  1132,  1132,  1132,
    2163,   789, -1384,   243,  1777,   405,   485,  1196, -1543,  2097,
    1914,  2168,  1774,   481,   141,  1792,  1916,  1270,  1918,  1922,
    1496, -1543,  1317,  1497,  1498,  1449,   179,   343,   482,  2098,
    2230,  2231,    35,    93,   406,   165,  1243,   483,  2070,    37,
    2072, -1543,  1227,  1628,  1629,  1630,  1631,  1632,  1633,  1635,
     790,  2164,  1189,  1946,  2232,   345,  1917,   929,  1919,   163,
    1053,  2226,  2169,  1345,  1346, -1467,  1830,  1328,  2089,   232,
     245,   462,  1987,    94,   407,    95,  1244, -1543,  1921,  1270,
    1328,  2137,  1311,   104,  1245,  1978,   327,  1778,  1507,   343,
     137,   763,   809,   998,  1775,  2033,    43, -1543,   764,  2117,
    2118,  1457,   284,   373,  1347,   232,  1348,   290,   380,   759,
     463,  1625,   810,  1674,   233,    48,  1854,   464,  1131,  1131,
    1131,  1131,  1131,  1131,  1131,   998,   791,  1256,  2038,  1964,
    1457,   329,   989,  1831,  1508,  1832,   492,  1349,  1350,  1351,
    1270,  2130,   793,  2045,  2046,   138,   139,  1128,  1793,  2052,
     233,  1458,  1128,   760,  1246,  1331,  1332,  1333,  1334,    49,
    1335,  1765,   989, -1427,  2270,   363,  2060,  1533,  1331,  1332,
    1333,  1334,  1257,  1335,   853,   792, -1424,    44,  1988,  -896,
    1458,   105,  -896,  2069,  1352,  2049,  1353,   179,   466,  2268,
   -1431,   794,  2065,  1534,  1354,  2066,  1580,  1580,  1952,  1797,
    2165,  2166,  1455,   291,  2099,   484,  2273,  1766,  1499,  1500,
     989,  2170,  2171,    52,  1809,    45, -1543,  1162,  1015,  1016,
     179,   345,   345,    46,  2100,  2101,  1501,  1502,  2233,  2234,
    1713,    58,  1017,  2103,   485,  2067,  2068,  1397,  1398,  1399,
    2191,   486,  1183,  2105,   427,  1400,  1798,  1509,   179,  1773,
    1714,   467,  -896,  1499,  1500,    59,  1679,   426,    60,  1682,
    1251,   993,   254,  2090,  1687,  1355,  1799,  -896,  -953,  2235,
    2236,  1501,  1502,  1252,  1935,  1541,   179,   115,  1018,  1064,
    2138,  1370,  1401,  2091,   553,  1374,   487,  1010,   550,   558,
     551,  1011,   488,  1386,  1387,    61,  1510,  1569,    67,  2056,
    1550,  1570,  1270,  1270,  1551,  2248,  2249,  -953,    10,   231,
      71,   401,    10,   231,  -953,  1541,   375,     5,   376,   489,
     470,  2179,  1584,  1585,  -896,  -896,   490,  2182,  1292,  1935,
    1293,  1666,  2143,  2178,  1270, -1376, -1376, -1376, -1376,   491,
    1132,   401,  2185,  2154,  1214,  1132,  1484,  2253,  2147,  2148,
     402,  -896,  -896,  1841,   989,  1842,    74,   403,  -896,    78,
    1402,  1403,  -896,   246,   492,  1894,   493,  1895,    80,  1767,
    2204,  1908,  2205,  1909,   494,    81,  1402,  1403,   102,  2206,
     402,  -896,  2183,   111,  2184,  -953,   113,   403,  1404,  -896,
    1869,   112,  -896,  -896,  1405,  1873,  1831,  -896,  1832,  2213,
    2214,  -896,   115,  -896,  1404,   495,  -896,   121,  -896,   125,
    1405,  1331,  1332,  1333,  1334,   130,  1335,  1331,  1332,  1333,
    1334,  -896,  1335,  1336,   126,  1407,  -896,   127,   404,  1408,
     885,  1356,   128,  1406,  1204,  1205,  1206,  1207,  -896,  1945,
     129,  1407,   132,  1333,  1334,  1408,  1335,   133,  -953,  2215,
    2216,  1935,  2242,   135,   496,   144,   146,  2243,   404,   145,
    -322,  1580,   160,   175,   213,  1131,   217,   161,   162,   886,
    1131,  1357,  2256,  1409,  1410,  2259,   887,  -953,  1411,  -896,
    1511,   216,  1331,  1332,  1333,  1334,   345,  1335,  1412,   219,
    1627,   405,   223,  1837,  1647,  1413,  1648,   224,   225,  1649,
    1414,  2197,   239,    40,   253,  1849,  -896,   256,   257,  1650,
    1846,  -953,  2042, -1375, -1375, -1375, -1375,  -953,  1415,   262,
     406,   405,   263,  1855,   272,   279,   401,   281,   286,   287,
     345,  1808,   293,  2180,  2181,   288,   321,  1783,  1331,  1332,
    1333,  1334,  -896,  1335,   320,   323,  1681,   888,   345,  1270,
     406,  -896,  -896,  1768,   343,   327,   330,  1270,   332,  1834,
     407,   461,   335,  1870,   184,   402,   336,  1839,   343,   184,
     346,  -896,   403,  1811,  1843,   365,  -896,   185,   186,   366,
    1811,   382,   185,   186,   343,   368,   385,   387,   345,   394,
     407,   395,   412,   424,  -896,  2250,   429,  -334,  2251,   432,
     434,   430,  -896,   446,   448,  -896,   476,  1270,   515,   187,
     889,  -896,  -896,  -896,   187,   523,   526,  -896,   530,  -896,
     532,  -896,  -896,  -896,   554,  1858,   557,   555,  1859,   560,
     179,   462,   570,   630,   632,  1651,   639,   646,   648,  1652,
     647,   752,   755,   404,   564,   188,   189,  2267,   190,   768,
     188,   189,  1653,   190,   777,  1422,   191,   784,  1424,  1425,
     797,   191,   795,  1416,  1417,  1418,  1419,  1420,   803,  1421,
     463,  1422,  1423,   831,  1424,  1425,   536,   464,  -630,   890,
    -630,  2274,  2224,   832,  -805,  -630,   875,   562,   907,   465,
     910,  2246,   913,  -630,  1903,  1904,  1905,  1906,  1654,   192,
     193,   926,  1907,   927,   192,   193,   405,   929,  1910,   932,
     194,  1331,  1332,  1333,  1334,   194,  1335,   937,   939,  1331,
    1332,  1333,  1334,  1677,  1335,  -630,  -630,  1684,   946,  1331,
    1332,  1333,  1334,  -630,  1335,   406,   943,  1689,   952,   949,
     980,  1997,   953,  1001,  -630,  1655,  1026,  -630,   466,  1009,
    1943,  1093,  1331,  1332,  1333,  1334,  1095,  1335,  1111,  -630,
    1853,  1102,  1117,  1331,  1332,  1333,  1334,  1725,  1335,  1656,
    1726,  2051,  1120,  2150,  1133,   407,  1138,  1139,  1727,  1728,
    1729,  -630,   195,   820,  1148,  1177,  1155,   195,  -630,  -630,
    1157,  1159,  1163,  1657,  1164,  1172,   645,  1949,  1658,  1165,
    1166,  1179,  1167,  1955,  1168,  1182,  1169,  1170,  1659,  1190,
    1184,   467,  1660,  1196,   468,   469,  1198,  2037,  1208,  -630,
    1201,  1220,  2039,  1224,  1239,  1242,  1240,  2087, -1378,  1249,
    1253,  -630,  1255,  1254,  1259,  -630,  1264,  1064,   154,  1266,
    1288,   426,  1291,  1295,  1297,  1300,  1298,  1321,  -630,  1342,
    1359,  1372,   345,  1379,  1393,  -630,  1394,  1444,  -630,  -630,
     985,  1467,  1482,  1505,  1487,  1520,  -630,  1524,  1538,  1661,
    1546,  1553,  1576,  -630,  1561,  -630,  1578,  1554,  -630,  1662,
     470,  1566,  1582,  1636,  1642,  1643,  1646,  1666,  1730,  1335,
     958,  1362,  1695,  1678,  1697,  1680,   196,  1683,  1688,  1690,
    1718,   196,  1700,  1458,  1741,   960,  1731,  1745,  1743,  1757,
    1749,  1760,  1761,  -630,  1785,  1788,  1789,  -630,  1800,  -630,
    1801,  1802,  1815,  1732,  1816,  1824,  -630,  1826,   955,  1835,
    1850,  1886,   992,  1887,  1899,  1882,   197,  2162,  1006,  1900,
    1924,   197,  1930,  1023,  1024,  1937,  1940,  1926,  -630,  1023,
    1031,  1033,  1958,  1963,  1932,  1944,   992,  1971,  1793,  1961,
    1968,  1973,  1023,  -630,  1980,  1982,  1984,  1994,  2001,  1733,
    1998,  1031,  1087,  1976,  1089,  2139,  1999,  2043,  2054,  2055,
    2057,  2075,  2071,  1044,  -630,   198,  2153,  2078,  2155,   961,
     198,  2092,  2093,  -630,  2094,  2112,  2121,  2195,   275,  2073,
    1988,  2114,  2140,  2133,  2141,  2145,  -630,  2151,  2173,  2186,
    2010,  -630,  2152,  -630,  2188,  2190,  1734,  2202,  2196,  2176,
    2177,  -630,  2211,  1130,  2203,  2238,  2254,  2221,  2239,  2255,
    2257,  -630,  2272,    14,   397,    27,    73,   182,  2229,  1045,
    -630,   964,   242,   255,   965,   252,  2218,   276,  1548,  -630,
     545,  -630,  -630,  1156,   754,  -630,  1303,  -630,   475,   215,
     438,  1577,  -630,   345,  1581,  1306,  2240,  2162,  1996,  1735,
    1104,  2198,   765,   142,  1947,   283,   966,  -630,   278,  1736,
     423,    66,  -630,   227,   950,   345,   644,  -630,  1188,   367,
     933,  2017,  2244,  1852,  1137,  1114,   573,  2157,  -630,  2241,
     159,  1890,   925,  1950,  1671,  1203,  1862,   537,   535,  1670,
    -630,  1212,  1888,  1913,  1489,  1023,  1485,  2219,  2220,  1920,
    -630,  2223,  1504,  1023,  1228,  1752,  2261,  2262,  2225,   525,
    2264,  2077,  2265,  1516,  1939,  1762,  1248,  1951,  1790,  1575,
    1737,   992,  1967,  1545,   967,  1272,  1271,  1076,   957,  1286,
    1822,   813,  1856,  1823,   345,  2119,  2124,  1269,  2200,  1960,
    2135,   989,  1720,  1263,  1446,  1023,  2245,  2252,  1806,  1023,
    2271,  1829,  1134,   292,   941,  1396,   378,  1287,   989,  1518,
    1228,  1219,  1140,  2247,    75,   958,   771,   426,   912,   968,
     969,  2040,  1699,     0,  1338,     0,     0,     0,  2263, -1543,
     960,     0,     0,     0,  1188,     0,     0,  1031,     0,     0,
       0,     0,     0,     0,   970,     0,     0,  1130,  1130,  1130,
       0,   958,     0,     0, -1004,     0,     0,  1130,     0,     0,
       0,  2269,   971,     0,   813,     0,   960, -1004,     0,     0,
     972,     0,   179,   343,  1269,     0,     0,     0,   426,  1130,
       0,  1130,     0,  1130,     0,     0,     0,  1130,  1130,  1130,
    1130,  1130,  1130,  1130,  1130,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1044,     0,
       0,     0,     0,     0,   961,     0,     0,     0,     0,     0,
       0,     0,     0,  1192,     0,     0,     0,     0,     0,     0,
     958,     0,     0,     0,   958,     0,     0,     0,     0,     0,
     426,     0,     0,     0,     0,   960,     0,     0,     0,   960,
     961,     0,     0,  1269,     0,     0,     0,     0,     0,     0,
       0,   401,     0,  1023,   990,     0,   964,     0,     0,   965,
       0,     0,     0,     0,     0,     0,  1531,     0,     0,     0,
       0,     0,     0,  1188,     0,     0,     0,     0,     0,     0,
    1544,   962,     0,     0,     0,     0,   963,  1023,     0,     0,
     402,   966,   964,     0,     0,   965,     0,   403,     0,  1560,
       0,     0,     0,     0,     0,  1269,     0,     0,     0,     0,
       0,  1568,  -590,   536,     0,  -630,     0,  -630,     0,   961,
       0,     0,  -630,   961,     0,     0,     0,   966,     0,  1228,
    -630,     0,     0,     0,   401,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1130,  1130,  1130,  1130,  1130,  1130,
    1130,     0,     0,     0,     0,     0,     0,     0,     0,   967,
       0,     0,  -630,  -630,     0,     0,  1269,     0,   404,   990,
    -630,   964,     0,   402,   965,   964,     0,     0,   965,     0,
     403,  -630,     0,     0,  -630,     0,  1676,     0,     0,     0,
       0,     0,     0,     0,     0,   967,  -630,     0,     0,     0,
       0,     0,     0,     0,   968,   969,   966,     0,  1023,     0,
     966,     0,     0,     0, -1543,     0,     0,     0,  -630,     0,
       0,     0,     0,     0,     0,  -630,  -630,     0,     0,   970,
       0,   405,     0,     0,     0,     0,     0,     0,     0, -1004,
     968,   969,  -590,     0,     0,     0,  -590,   971,     0,     0,
       0,   404, -1004,     0,     0,   972,  -630,   179,   343,     0,
     406,     0,  1706,  1707,     0,   970,     0,     0,  -630,     0,
       0,     0,  -630,     0,   967,     0,     0,     0,   967,     0,
       0,     0,     0,   971,     0,  -630,     0,     0,     0,  -590,
       0,   972,  -630,     0,   343,  -630,  -630,     0,     0,     0,
     407,     0,     0,  -630,     0,     0,     0,     0,  1193,     0,
    -630,     0,  -630,     0,   405,  -630,     0,     0,     0,   968,
     969,     0,     0,   968,   969,     0,     0,     0,  1269,  1269,
       0,     0,     0,     0,  1023,  1023,     0,     0,     0,     0,
       0,     0,     0,   406,   970,     0,     0,     0,   970,     0,
    -630,     0,  1791,     0,  -630,     0,  -630,     0,     0,     0,
    1269,     0,   971,  -630,     0,     0,   971,     0,     0,     0,
     972,     0,     0,   343,   972,  1812,     0,   343,     0,     0,
    1821,  1821,     0,   407,     0,  -630,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -630,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   992,     0,  -590,     0,     0,     0,     0,     0,
       0,  -630,     0,  1847,     0,  1848,     0,     0,     0,     0,
    -630,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0, -1459,  -630,     0, -1459,     0,     0,  -630,     0,
    -630,     0,     0,  1213,     0,     0,     0, -1459,  -630,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -630,     0,
       0,     0,     0,     0,     0,     0,     0,  -630,     0,     0,
       0,  1188,  1188,  1188,     0,     0,  -630,     0,  -630,  -630,
       0,  1130,  -630,     0,  -630,     0,  1130,     0,     0,  -630,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1023,
       0,     0,     0,     0,  -630, -1459,     0,     0,     0,  -630,
       0,     0,     0,     0,  -630,     0,     0,     0,     0,     0,
   -1459,     0,     0,     0,     0,  -630,     0,     0,     0,     0,
       0,     0,     0,     0,   537,     0,     0,  -630,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -630,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1923,     0,
       0,     0,     0,     0,  1934,  1269,     0,     0,     0,     0,
       0,     0,     0,  1269,     0,     0,     0, -1459, -1459,     0,
       0,     0,     0,     0,  1023,     0,     0,     0,     0,     0,
       0,     0,  1531,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0, -1459, -1459,     0,     0,     0,     0,
       0, -1459,     0,     0,     0, -1459,     0,     0,     0,  1934,
       0,     0,     0,  1269,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0, -1459,     0,     0,     0,     0,     0,
       0,     0, -1459,  2035,     0, -1459, -1459,  2035,     0,     0,
   -1459,     0,     0,     0, -1459,     0, -1459,     0,     0, -1459,
       0, -1459,  2035,  2035,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0, -1459,     0,     0,     0,     0, -1459,
       0,     0,     0,     0,   577,   578,   579,   580,   581,   582,
     957, -1459,     0,   813,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2035,     0,     0,  2035,     0,     0,     0,     0,   584,
       0,   585,   586,   587,   588,   589,   590,     0,     0,     0,
       0,     0, -1459,     0,     0,     0,     0,     0,     0,     0,
       0,  1934,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0, -1459,
       0,   591,     0,   958,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1031,     0,     0,     0,     0,   960,     0,
    2116,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0, -1459,     0,     0,     0,  2035,
       0,     0,     0,     0, -1459, -1459,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2156,     0,     0,     0,
       0, -1459,     0,     0, -1459, -1459,     0,     0,     0, -1459,
       0,     0,     0,     0,     0,  1402,  1403,     0,     0,     0,
       0,     0,     0,   592,     0,     0,     0, -1459,     0,     0,
       0,     0,  2035,     0,     0, -1459,     0,     0, -1459,     0,
       0,     0,   961,  1404, -1459, -1459, -1459,     0,     0,  1405,
   -1459,     0, -1459,   401, -1459, -1459, -1459,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1431,   594,     0,     0,     0,     0,     0,     0,
    1407,     0,     0,   962,  1408,     0,     0,     0,   963,  1228,
       0,   649,   402,   650,   964,     0,     0,   965,   651,   403,
       0,     0,     0,     0,  2208,     0,   652,  2210,     0,     0,
     596,     0,  1432,     0,     0,     0,     0,  1433,     0,   598,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   966,
       0,     0,   599,     0,     0,     0,     0,  2227,   653,   654,
       0,     0,     0,     0,     0,     0,   655,     0,   649,     0,
     650,  2035,     0,     0,     0,   651,  2035,   656,     0,     0,
     657,     0,     0,   652,     0,     0,     0,     0,     0,     0,
     404,     0,   658,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1031,     0,     0,     0,     0,     0,   603,   604,
     605,     0,     0,  2260,   659,   653,   654,   967,     0,     0,
       0,   660,   661,   655,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   656,     0,     0,   657,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   658,
       0,     0,   662,   405,     0,     0,     0,   607,   608,   609,
    1228,     0,   968,   969,   663,     0,     0,     0,   664,     0,
       0,   659,     0,     0,     0,     0,     0,     0,   660,   661,
       0,   665,   406,     0,     0,     0,     0,   970,   666,     0,
       0,   667,   668,     0,     0,     0,     0,     0,     0,   669,
       0,     0,     0,     0,     0,   971,   670,     0,   671,   662,
       0,   672,     0,   972,     0,     0,   343,     0,     0,     0,
       0,   663,   407,  1434,  1435,   664,     0,     0,  1436,     0,
    1422,     0,  1437,  1424,  1425,     0,     0,     0,   665,     0,
       0,     0,     0,     0,     0,   666,   673,     0,   667,   668,
     674,   958,   675,     0,     0,     0,   669,  -762,     0,   676,
    -762,     0,     0,   670,     0,   671,   960,     0,   672,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   677,     0,     0,     0,     0,     0,     0,     0,     0,
     957,     0,     0,   813,     0,     0,   678,     0,     0,   154,
       0,     0,     0,   673,     0,     0,     0,   674,     0,   675,
       0,     0,     0,  1150,     0,     0,   676,   679,   957,     0,
       0,   813,     0,     0,     0,     0,   680,     0,     0,     0,
    -762,     0,     0,     0, -1471,     0,     0,     0,   677,   681,
       0,     0,     0,     0,   682,  -762,   683,     0, -1467,     0,
     961,     0,     0,   678,   684,     0,     0,     0,     0,     0,
       0,   401,     0,   958,   685,     0,     0,     0,     0,     0,
       0,     0,     0,   686,   679,     0,     0,     0,   960,     0,
       0,     0,   687,   680,   688,   689,     0,     0,   690,     0,
     691,   958,     0,     0,     0,   692,   681,     0,     0,     0,
     402,   682,   964,   683,     0,   965,   960,   403,     0,   957,
     693,   684,   813,     0,     0,   694,     0,     0,     0,     0,
     695,   685,     0,     0,     0,     0,     0,     0,     0,  -762,
     686,   696,     0,     0,     0,     0,     0,   966,     0,   687,
    -762,   688,   689,   697,     0,   690,     0,   691,     0,     0,
       0,     0,   692,   698,     0,     0,  1549,     0,     0,     0,
       0,     0,   961,     0,     0,     0,     0,   693,     0,     0,
    -762,     0,   694,   401,     0,  -762,     0,   695,   404,  -762,
       0,  -762,   958,     0,  -762,     0,  -762,     0,   696,     0,
     961,     0,     0,     0,     0,     0,     0,   960,     0,     0,
     697,   401,     0,   962,     0,   967,     0,     0,   963, -1467,
    1079,     0,   402,     0,   964,     0,  -762,   965,     0,   403,
       0,  -762,     0,     0,     0,   957,     0,     0,   813,     0,
       0,   962,     0,     0,     0,     0,   963,     0,     0,     0,
     402,   405,   964,     0,     0,   965,     0,   403,     0,   966,
     968,   969,     0,     0,     0,     0,     0,  -762,     0,     0,
       0,     0,     0,     0,     0,     0,     0, -1471,     0,     0,
     406,     0,     0,     0,     0,   970, -1467,   966,     0,     0,
       0,   961,     0,     0,  -762,     0,     0,     0,     0,     0,
     404,   957,   401,   971,   813,     0,     0,     0,   958,     0,
       0,   972,     0,     0,   343,     0,     0,  1285,     0,   959,
     407,     0,     0,   960,  -762,     0,     0,   967,   404,     0,
    -762,     0,   962,     0,     0,     0,     0,   963,     0,  -762,
    -762,   402,     0,   964,     0,     0,   965,     0,   403,     0,
       0,     0,     0,     0,     0,   967,     0,   957,     0,  -762,
     813,     0,     0,   405,  -762,     0,     0,     0,     0,  -762,
       0,     0,   968,   969,   958,     0,     0,     0,   966,     0,
       0,     0,  -762,     0,     0,  1038, -1471,     0,     0,   960,
    -762,   405,   406,  -762,     0,     0,     0,   970,     0,  -762,
     968,   969,     0,     0,     0,     0,     0,   961,     0,     0,
       0,     0,     0,   957,     0,   971,   813,  1550,   401,   404,
     406,  1551,     0,   972,     0,   970,   343,     0,     0,     0,
     958,     0,   407,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   971,     0,   960,   967,     0,   962,     0,
       0,   972,     0,   963,   343,     0,     0,   402,  1079,   964,
     407,     0,   965,     0,   403,     0,     0,     0,     0,     0,
       0,     0,     0,   961,     0,     0,     0,   957,     0,     0,
     813,     0,   405,     0,   401,     0,   958,     0,     0,     0,
       0,   968,   969,     0,   966,     0,     0,  1083,     0,   957,
       0,   960,   813,     0,     0,     0,     0,     0,     0,     0,
       0,   406,     0,     0,   962,     0,   970,     0,     0,   963,
       0,     0,     0,   402,     0,   964,     0,     0,   965,   961,
     403,     0,     0,     0,   971,   404,     0,     0,     0,     0,
     401,     0,   972,     0,     0,   343,     0,     0,     0,     0,
     958,   407,     0,     0,     0,     0,     0,     0,     0,     0,
     966,     0,   967,     0,     0,   960,     0,     0,     0,     0,
     962,     0,   958,     0,     0,   963,     0,     0,     0,   402,
       0,   964,     0,     0,   965,   961,   403,   960,     0,     0,
       0,     0,     0,     0,     0,     0,   401,     0,   405,     0,
       0,   404,     0,     0,     0,     0,     0,   968,   969,     0,
       0,     0,     0,     0,     0,     0,   966,     0,     0,   957,
       0,     0,   813,     0,     0,     0,   962,   406,   967,     0,
       0,   963,   970,     0,     0,   402,     0,   964,     0,     0,
     965,     0,   403,     0,     0,     0,     0,     0,     0,   961,
     971,     0,     0,     0,     0,     0,     0,   404,   972,     0,
     401,   343,     0,     0,   405,     0,     0,   407,     0,     0,
       0,   961,   966,   968,   969,   957,     0,     0,   813,     0,
       0,     0,   401,     0,   967,     0,     0,     0,     0,     0,
     962,     0,   958,   406,     0,   963,     0,     0,   970,   402,
       0,   964,     0,     0,   965,     0,   403,   960,     0,     0,
       0,     0,   962,   404,     0,     0,   971,   963,     0,     0,
     405,   402,     0,   964,   972,     0,   965,   343,   403,   968,
     969,     0,     0,   407,     0,     0,   966,     0,     0,     0,
     967,   957,     0,     0,   813,     0,     0,     0,   958,   406,
       0,     0,     0,     0,   970,     0,     0,     0,   966,     0,
       0,     0,     0,   960,     0,     0,     0,     0,     0,     0,
       0,     0,   971,     0,     0,     0,   405,   404,     0,     0,
     972,     0,     0,   343,     0,   968,   969,  1290,     0,   407,
       0,   961,     0,     0,     0,     0,     0,   957,     0,   404,
     813,     0,   401,     0,   967,   406,     0,     0,     0,     0,
     970,     0,     0,     0,   958,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   967,     0,   971,   960,
       0,     0,   962,     0,     0,     0,   972,   963,     0,   343,
     405,   402,     0,   964,     0,   407,   965,   961,   403,   968,
     969,     0,     0,     0,     0,     0,  1558,     0,   401,     0,
       0,     0,   405,     0,     0,  1174,     0,     0,     0,   406,
     958,   968,   969,     0,   970,     0,     0,     0,   966,     0,
       0,     0,     0,     0,     0,   960,     0,     0,   962,     0,
       0,   406,   971,   963,     0,     0,   970,   402,     0,   964,
     972,     0,   965,   343,   403,     0,     0,     0,     0,   407,
       0,     0,     0,   961,   971,     0,     0,     0,     0,   404,
       0,     0,   972,     0,   401,   343,     0,     0,     0,     0,
       0,   407,     0,     0,   966,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   967,     0,     0,     0,
       0,     0,     0,     0,   962,     0,     0,     0,     0,   963,
       0,     0,     0,   402,     0,   964,     0,     0,   965,   961,
     403,     0,     0,     0,     0,   404,     0,     0,     0,     0,
     401,     0,   405,     0,     0,     0,     0,     0,     0,     0,
       0,   968,   969,     0,     0,     0,     0,     0,     0,     0,
     966,     0,   967,     0,     0,     0,     0,     0,     0,     0,
     962,   406,     0,     0,     0,   963,   970,     0,     0,  1002,
       0,   964,     0,     0,   965,     0,   403,     0,     0,     0,
       0,     0,     0,  1690,   971,     0,     0,     0,   405,     0,
       0,   404,   972,     0,     0,   343,     0,   968,   969,     0,
       0,   407,     0,     0,     0,     0,   966,     0,     0,     0,
       0,     0,     0,     0,     0,   575,     0,   406,   967,     0,
       0,     0,   970,     0,     0,     0,     0,   576,     0,     0,
     577,   578,   579,   580,   581,   582,   583,     0,     0,     0,
     971,     0,     0,     0,     0,     0,     0,   404,   972,     0,
       0,   343,     0,     0,   405,     0,     0,   407,     0,     0,
       0,     0,     0,   968,   969,   584,     0,   585,   586,   587,
     588,   589,   590,     0,   967,     0,     0,     0,     0,     0,
       0,     0,     0,   406,     0,     0,     0,     0,   970,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   971,   591,     0,     0,
     405,     0,     0,     0,   972,     0,     0,   343,     0,   968,
     969,     0,     0,   407,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   406,
       0,     0,     0,     0,   970,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   971,     0,     0,     0,     0,     0,     0,     0,
     972,     0,     0,   343,     0,     0,     0,     0,     0,   407,
       0,     0,     0,     0,     0,     0,  1589,     0,  1590,   592,
       0,  1591,   577,   578,   579,   580,   581,   582,   583,  1592,
    1593,  1594,    40,     0,     0,   593,     0,     0,     0,     0,
       0, -1524,     0,     0,     0,     0,     0,     0,     0,     0,
    1595,     0,     0,     0,     0,     0,     0,   584,     0,   585,
     586,   587,   588,   589,   590,     0,     0,     0,     0,   594,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   595,     0,     0,     0,     0,     0,     0,     0,   591,
       0,     0,     0,     0,     0,     0,   596,     0,     0,     0,
       0,     0,     0,   597,     0,   598,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   599,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   600,  1596,
       0,     0,     0,     0,     0,   601,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1597,     0,     0,
    1598,  1599,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1600,     0,     0,     0,     0,   958,
       0,   592,   602,     0,   603,   604,   605,     0,     0,     0,
       0,     0,     0,     0,   960,     0,     0,   593,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   606,     0,
       0,  1601,     0,     0,     0,     0,     0,     0,     0,     0,
    1602,     0,     0,     0,     0, -1524,     0,     0,     0,     0,
       0,   594,     0,   607,   608,   609,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   610,     0,     0,   611,
       0,     0,     0,  1603,     0,     0,     0,     0,     0,   577,
     578,   579,   580,   581,   582,   583,     0,  1604,   596,  -329,
       0,     0,     0,     0,     0,   597,     0,   598,   961,     0,
       0,     0,     0,     0,     0,     0,     0,  2002,  2003,   401,
     599,  1605,     0,     0,   584,     0,   585,   586,   587,   588,
     589,   590,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1606,   958,     0,     0,  1122,
    1607,     0,     0,     0,   963,     0,     0,     0,   402,     0,
     964,   960,     0,   965,  1608,   403,   591,     0,     0,     0,
       0,     0,     0,     0,   602,     0,   603,   604,   605,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   958,   966,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   960,
    1609,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1610,     0,     0,     0,   607,   608,   609,     0,     0,
       0,     0,     0,     0,     0,     0,   404,     0,   610,  2004,
    1611,   611,     0,     0,     0,   961,     0,     0,   592,     0,
       0,     0,     0,     0,     0,     0,   401,     0,     0,     0,
       0,  1612,     0,   967,   593,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2005,  2006,
       0,     0,     0,     0,     0,     0,  1122,     0,     0,     0,
       0,   963,     0,   961,     0,   402,     0,   964,   594,   405,
     965,     0,   403,  2007,   401,     0,     0,     0,   968,   969,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     595,     0,     0,     0,     0,     0,     0,     0,   406,     0,
       0,     0,   966,   970,  1122,   596,     0,     0,     0,   963,
       0,     0,   597,   402,   598,   964,     0,  2008,   965,     0,
     403,   971,     0,     0,     0,     0,     0,   599,     0,   972,
       0,     0,   343,     0,     0,     0,     0,     0,   407,  1123,
    1124,     0,     0,   404,     0,     0,     0,  1634,  1125,     0,
     966,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     967,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   602,     0,   603,   604,   605,     0,     0,     0,     0,
    2009,   404,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2010,     0,   405,     0,     0,     0,
       0,     0,     0,     0,     0,   968,   969,     0,   967,     0,
       0,     0,     0,     0,     0,     0,     0,  2011,     0,     0,
       0,     0,   607,   608,   609,   406,     0,     0,     0,     0,
     970,     0,     0,     0,     0,   610,     0,     0,   611,  2012,
       0,     0,     0,     0,   405,     0,     0,     0,   971,     0,
       0,     0,     0,   968,   969,     0,   972,     0,  2013,   343,
       0,     0,     0,     0,     0,   407,  1123,  1124,     0,     0,
       0,     0,     0,   406,  1868,  1125,     0,     0,   970,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   971,     0,     0,     0,
       0,     0,     0,     0,   972,     0,     0,   343,     0,     0,
       0,     0,     0,   407,  1123,  1124,     0,     0,     0,     0,
       0,     0,     0,  1125
};

static const yytype_int16 yycheck[] =
{
      83,   128,   165,   376,   611,   631,   667,   240,   815,   265,
     490,   877,   841,   269,   422,   271,  1001,  1181,  1079,  1073,
    1251,  1181,   185,   186,   600,   836,   838,   190,   191,   192,
     193,   194,  1181,   196,   265,   198,   847,  1181,   269,   696,
     271,  1181,   837,   637,   574,   187,  1214,   994,  1320,  1021,
     855,   779,   972,   195,  1676,   182,  1320,  1029,  1320,     9,
    1362,  1363,   445,   868,  1063,  1320,   149,   230,   340,   232,
    1320,  1320,   214,    17,   554,   331,   239,  1205,  1206,  1207,
    1237,     6,     6,     6,   247,   341,   319,    13,    27,    68,
      48,     6,    47,   326,   350,     9,     6,  1151,   261,   262,
     331,   264,     9,  1075,   835,    69,    92,   270,    55,    68,
     341,    22,    53,   844,   845,    82,  1255,   259,   260,   350,
     116,   377,    68,   113,    92,   267,   268,   116,   859,   860,
      36,   273,   274,  1827,    55,   298,   408,   176,   301,   302,
     373,   304,   873,   874,    89,    71,   377,   380,   379,    21,
     957,  1150,    17,   201,    70,   962,   113,   320,    29,   113,
     393,    87,     9,  1110,  1321,   166,  1353,    55,    59,   166,
       9,   110,    61,  1360,   337,   228,    47,     9,   117,    48,
     208,   437,   808,   144,   415,  1342,    83,   420,    29,    68,
    1812,   424,   116,    68,    85,    86,   260,   280,    48,   291,
    1145,    22,   108,   102,   476,   181,   437,   574,   121,    64,
      61,   353,   375,  1020,   170,   208,    55,   232,    31,   212,
     383,   158,     9,    64,   270,   109,   228,   386,   181,   766,
    1229,   857,   232,    83,  1295,   145,   102,   252,   228,   313,
     228,   208,   174,   117,   975,   478,   177,  1113,   228,   169,
      11,   166,   782,   844,   240,   638,   316,   205,   491,   929,
     182,   162,    49,  1346,   359,   228,  1071,   866,     8,   432,
    1353,   228,  1815,  1004,   228,   358,     0,  1360,   361,   445,
     228,   182,   189,   874,   117,   884,   208,   250,   451,   452,
     523,   445,  1291,  1595,    34,   528,   228,   208,   169,  1601,
     315,  1273,   533,   534,   170,  1174,   212,  1038,   934,    70,
     296,   918,  1259,   408,   228,  1122,   182,   208,   145,  1487,
     165,   228,   242,   397,   487,   371,   279,   290,   235,   168,
     240,    68,   271,   174,  1491,    48,    48,  1465,   338,   431,
     301,   254,  1211,   280,   228,  1174,   159,   118,   237,  1080,
     513,   228,   416,  1352,  1085,   949,   515,   520,   316,   228,
     340,   838,   595,   339,   320,   425,   493,   431,   944,   945,
     601,   302,   351,  1242,   163,    46,   424,   322,   217,   432,
     857,   228,  1211,  1194,   225,   862,  1447,   208,   228,    60,
     553,   406,   351,   284,  1937,   558,  1341,   313,   561,   306,
     563,  2095,   189,   566,   567,   351,   445,   570,  1219,  1463,
     947,   948,   301,  1242,   228,   782,   431,   445,   414,   316,
     252,  1290,  1394,   236,   312,   414,    97,  1057,  1223,  1771,
     432,   432,   219,   397,  1239,   432,  1575,   292,  1456,   432,
     385,   228,   432,  1174,   432,   400,   432,   610,   235,   355,
    1181,   292,   929,  1123,  1124,  1125,  1474,  1644,  1253,   426,
     349,  1290,   369,  1133,   432,   354,   316,   425,   447,   394,
     394,   432,   351,   394,   181,   432,   351,   309,   432,  1210,
    1211,   397,   432,   424,   428,  1155,   433,  1157,   447,  1159,
     414,   398,   431,  1163,  1164,  1165,  1166,  1167,  1168,  1169,
    1170,   447,   929,   354,  1522,     9,  1301,   432,   432,   432,
     637,  1242,  1138,   769,   770,  1514,   431,   432,   432,   306,
     776,   432,   432,   395,  1393,   432,   391,   399,   425,   400,
     456,   438,   431,   432,   367,   766,   307,   208,   769,   770,
    1525,   813,   213,   432,  1562,   776,  1277,  1546,   432,  1521,
    1281,  1282,   223,  1284,   445,   432,   345,   431,   432,  1290,
     431,  1644,   401,   432,  1393,    64,  1838,   950,   447,   438,
    1047,  1802,   447,   260,  1838,   425,  1838,   929,  1154,   217,
    1748,   161,   369,  1838,   355,  1161,  1116,   432,  1838,  1838,
    1318,  1933,   432,   756,  1936,   758,    39,   830,   431,   432,
     112,   217,    48,   316,   316,  2227,   837,   396,   163,  1146,
    1982,   398,  1984,   446,   351,   778,  1488,   237,   432,   332,
     332,   201,  1494,   134,   438,   240,   134,   858,  1258,   209,
     181,   862,   339,   864,   218,   866,   867,   115,   869,   310,
     311,  1702,   898,   228,    68,  1221,  1123,  1124,  1125,   367,
    1445,   438,   323,   884,   325,   237,  1133,    68,   914,   359,
    1330,  1331,  1332,  1333,  1334,  1335,  1336,   898,  1825,  1263,
     901,    26,   243,  1267,   946,  1693,   181,   207,  1155,   445,
    1157,   301,  1159,   914,  1161,   189,  1163,  1164,  1165,  1166,
    1167,  1168,  1169,  1170,   927,    97,  1123,  1124,  1125,   279,
    2002,   932,   439,   440,   441,   442,  1133,   444,   408,   181,
     447,  1063,   425,   425,   432,  1520,   947,   948,   303,   301,
    1667,  1668,  1669,  1695,   228,   228,   225,   257,   446,   349,
    1157,   235,   445,   445,   181,   862,  1163,  1164,  1165,  1166,
    2082,  1402,  1169,  1170,   431,   228,   291,  1323,    30,  2121,
     194,   893,   915,   337,   425,  1675,   445,   240,   204,   842,
    1680,  1681,  1761,   401,  1684,  1685,  1686,   349,  1688,  1689,
     341,  1123,  1124,  1125,   445,  1903,  1904,  1905,  1906,   394,
     863,  1133,   865,   237,   296,   401,  1598,   870,   339,  1850,
     345,   302,  1368,   292,   302,   238,   879,  1454,  1150,  1860,
    1861,   284,   306,  1155,  1058,  1157,  1970,  1159,  1780,  1161,
    1970,  1163,  1164,  1165,  1166,  1167,  1168,  1169,  1170,    24,
    1819,  1970,  1553,   105,   268,   445,  1970,   332,  1059,   192,
    1970,   266,     9,    29,  1495,    12,   270,   196,    15,    16,
    1094,   192,   193,  1504,  1716,  1717,  1323,   301,   232,  1867,
    1911,  1912,   432,  1330,  1331,  1332,  1333,  1334,  1335,  1336,
     239,   359,   393,   445,    27,   369,   225,   339,   252,   232,
    1742,   239,   194,     4,   445,   121,  1745,  1229,  1747,  1751,
      12,   232,  1115,    15,    16,   332,   431,   432,    19,   252,
      87,    88,    80,   328,   398,   349,   161,    28,  1916,   115,
    1918,   252,  1029,  1330,  1331,  1332,  1333,  1334,  1335,  1336,
     408,   290,   995,  1782,   111,  1146,  1745,   448,  1747,   124,
    1047,  2152,   290,    24,    25,   121,   243,   351,  1946,   363,
      61,   189,   149,   368,   438,   370,   201,   232,  1749,  1291,
     351,  1995,  1105,   243,   209,  1814,   228,   110,     9,   432,
     310,   310,   162,  1782,   276,   438,   347,   252,   317,  1977,
    1978,   207,   222,   297,    65,   363,    67,   227,   302,   118,
     228,  1323,   182,  1549,   408,   445,  1637,   235,  1330,  1331,
    1332,  1333,  1334,  1335,  1336,  1814,   359,   250,  1843,  1800,
     207,   445,  1223,   310,    55,   312,   355,    98,    99,   100,
    1352,  1986,   359,  1858,  1859,   365,   366,  1677,   254,  1881,
     408,   257,  1682,   162,   279,   439,   440,   441,   442,   298,
     444,     9,  1253,   447,  2255,   285,  1898,     8,   439,   440,
     441,   442,   295,   444,     1,   408,   447,   164,   255,     6,
     257,   341,     9,  1915,   145,  1861,   147,   431,   306,  2252,
     432,   408,  1907,    34,   155,  1910,  1312,  1313,  1789,  1540,
     439,   440,  1189,   445,   427,   196,  2269,    55,   245,   246,
    1301,   439,   440,   445,  1555,   202,   427,   963,   287,   288,
     431,  1312,  1313,   210,  1956,  1957,   263,   264,   285,   286,
     232,   445,   301,  1965,   225,  1911,  1912,    12,    13,    14,
    2085,   232,   988,  1969,   364,    20,   232,   168,   431,  1517,
     252,   369,    79,   245,   246,   445,  1380,  1200,   347,  1383,
     413,  1598,   445,   232,  1388,   226,   252,    94,   189,   326,
     327,   263,   264,   426,  1760,  1262,   431,   432,   347,   240,
    1995,  1155,    57,   252,   481,  1159,   277,   395,   269,   486,
     271,   399,   283,  1167,  1168,   445,   217,   154,   115,  1890,
     395,   158,  1514,  1515,   399,  2183,  2184,   228,     2,   155,
     130,   189,     6,   159,   235,  1302,   310,   302,   312,   310,
     438,  2053,   225,   226,   151,   152,   317,  2059,   310,  1815,
     312,   261,   262,  2048,  1546,   417,   418,   419,   420,   330,
    1677,   189,  2074,  2010,   428,  1682,   430,  2192,   261,   262,
     228,   178,   179,   148,  1445,   150,   301,   235,   185,   445,
     151,   152,   189,   354,   355,   256,   357,   258,   347,   217,
    2102,   148,  2104,   150,   365,   434,   151,   152,   164,  2111,
     228,   208,  2071,   445,  2073,   306,   231,   235,   179,   216,
    1677,   347,   219,   220,   185,  1682,   310,   224,   312,  2131,
    2132,   228,   432,   230,   179,   396,   233,   332,   235,   445,
     185,   439,   440,   441,   442,   350,   444,   439,   440,   441,
     442,   248,   444,   451,   445,   216,   253,   445,   306,   220,
     189,   392,   445,   208,   417,   418,   419,   420,   265,  1779,
     445,   216,   445,   441,   442,   220,   444,   210,   369,   225,
     226,  1937,  2167,   396,   445,   445,   227,  2172,   306,   347,
     432,  1577,   432,   176,   274,  1677,   386,   445,   445,   228,
    1682,   432,  2198,   248,   249,  2207,   235,   398,   253,   306,
     401,   445,   439,   440,   441,   442,  1577,   444,   263,    23,
     447,   369,   445,  1586,    30,   270,    32,   347,   323,    35,
     275,  2092,   363,   208,   445,  1621,   333,   102,   432,    45,
    1603,   432,  1852,   417,   418,   419,   420,   438,   293,   375,
     398,   369,   358,  1639,    55,    82,   189,   170,   445,   347,
    1621,  1554,   432,  2054,  2055,   342,   274,  1524,   439,   440,
     441,   442,   369,   444,   363,   104,   447,   306,  1639,  1761,
     398,   378,   379,   401,   432,   228,   354,  1769,   205,  1582,
     438,   119,   445,  1679,    11,   228,   241,  1590,   432,    11,
      66,   398,   235,  1560,  1597,   445,   403,    24,    25,   347,
    1567,   241,    24,    25,   432,   445,    22,   268,  1679,   432,
     438,   445,   228,   292,   421,  2186,   445,    81,  2189,    81,
     432,   445,   429,   426,   432,   432,   391,  1819,   308,    56,
     369,   438,   439,   440,    56,   394,   226,   444,   194,   446,
     432,   448,   449,   450,   310,  1648,   355,   394,  1651,    54,
     431,   189,   375,    26,   182,   171,   363,   445,   347,   175,
     445,   445,   375,   306,   212,    92,    93,  2238,    95,   355,
      92,    93,   188,    95,   432,   446,   103,   219,   449,   450,
     337,   103,   428,   438,   439,   440,   441,   442,   208,   444,
     228,   446,   447,   104,   449,   450,     1,   235,     3,   438,
       5,  2272,  2149,   228,   396,    10,   297,    36,   372,   247,
     278,  2177,   272,    18,  1721,  1722,  1723,  1724,   234,   146,
     147,   438,  1725,   394,   146,   147,   369,   448,  1731,   391,
     157,   439,   440,   441,   442,   157,   444,    26,   353,   439,
     440,   441,   442,   451,   444,    50,    51,   447,   452,   439,
     440,   441,   442,    58,   444,   398,   268,   447,   445,   169,
     432,  1834,   445,   396,    69,   281,   131,    72,   306,   228,
    1773,   102,   439,   440,   441,   442,    17,   444,   167,    84,
     447,   431,   182,   439,   440,   441,   442,    32,   444,   305,
      35,   447,   393,  2006,   448,   438,   391,   228,    43,    44,
      45,   106,   229,    29,   122,   199,   448,   229,   113,   114,
     448,   448,   448,   329,   448,   123,   121,  1784,   334,   448,
     448,    55,   448,  1790,   448,   394,   448,   448,   344,   125,
     424,   369,   348,   339,   372,   373,   310,  1840,   128,   144,
     127,    96,  1845,   390,   394,    48,   132,  1943,   393,   133,
     391,   156,   388,   393,   174,   160,   138,   240,    48,   426,
     141,  1784,   174,   107,   324,   271,   371,   109,   173,   109,
     431,   394,  1943,   432,   181,   180,   332,   300,   183,   184,
     228,   158,   129,   166,   428,   394,   191,   357,   204,   405,
     394,    48,   117,   198,   174,   200,   271,   212,   203,   415,
     438,   204,   187,   356,   437,   436,   212,   261,   153,   444,
      79,   225,   332,   447,   389,   447,   343,   447,   447,   364,
     126,   343,   394,   257,   260,    94,   171,   181,   256,   322,
     391,   394,    48,   238,   133,     8,   174,   242,   428,   244,
     121,   428,   394,   188,     9,   298,   251,   299,   834,   168,
     196,   275,   838,   275,   320,   259,   383,  2030,   844,   335,
     120,   383,   105,   849,   850,    48,   170,   425,   273,   855,
     856,   857,   136,   232,   425,   276,   862,   139,   254,   137,
     253,   280,   868,   288,   275,   108,   385,     7,    65,   234,
     111,   877,   878,   291,   880,  1998,   214,   395,   151,   151,
     124,   131,   319,   172,   309,   432,  2009,    97,  2011,   178,
     432,    48,   232,   318,   212,   140,    91,  2088,   445,   319,
     255,   258,    88,   143,   215,   197,   331,   186,   432,    48,
     381,   336,   428,   338,   397,   298,   281,   232,   335,  2042,
    2043,   346,   142,   929,   232,   174,   298,   169,   284,   413,
     135,   356,    48,     6,   325,    21,    53,   128,  2154,   228,
     365,   230,   167,   182,   233,   177,  2139,   200,  1274,   374,
     472,   376,   377,   959,   547,   380,  1095,   382,   408,   132,
    2176,  1306,   387,  2154,  1313,  1097,  2159,  2160,  1830,   334,
     904,  2094,   559,   107,  1783,   221,   265,   402,   216,   344,
     358,    48,   407,   149,   829,  2176,   534,   412,   994,   292,
     807,  1838,  2174,  1623,   934,   917,   517,  2025,   423,  2160,
     120,  1704,   782,  1787,  1365,  1004,  1663,   432,   454,  1364,
     435,  1009,  1702,  1738,  1219,  1021,  1216,  2140,  2141,  1748,
     445,  2144,  1226,  1029,  1030,  1487,  2219,  2220,  2151,  2245,
    2223,  1927,  2225,  1232,  1769,  1512,  1047,  1788,  1536,  1302,
     405,  1047,  1804,  1267,   333,  1071,  1069,   869,     6,  1080,
    1567,     9,  1641,  1567,  2245,  1980,  1985,  1063,  2095,  1795,
    1991,  2252,  1461,  1059,  1183,  1071,  2176,  2190,  1549,  1075,
    2263,  1577,   930,   228,   812,  1179,   300,  1083,  2269,  1237,
    1086,  1012,   939,  2178,    56,    79,   568,  2130,   773,   378,
     379,  1846,  1408,    -1,  1136,    -1,    -1,    -1,  2221,   388,
      94,    -1,    -1,    -1,  1110,    -1,    -1,  1113,    -1,    -1,
      -1,    -1,    -1,    -1,   403,    -1,    -1,  1123,  1124,  1125,
      -1,    79,    -1,    -1,   413,    -1,    -1,  1133,    -1,    -1,
      -1,  2254,   421,    -1,     9,    -1,    94,   426,    -1,    -1,
     429,    -1,   431,   432,  1150,    -1,    -1,    -1,  2191,  1155,
      -1,  1157,    -1,  1159,    -1,    -1,    -1,  1163,  1164,  1165,
    1166,  1167,  1168,  1169,  1170,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   172,    -1,
      -1,    -1,    -1,    -1,   178,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   151,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,
    2253,    -1,    -1,    -1,    -1,    94,    -1,    -1,    -1,    94,
     178,    -1,    -1,  1229,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   189,    -1,  1239,   228,    -1,   230,    -1,    -1,   233,
      -1,    -1,    -1,    -1,    -1,    -1,  1252,    -1,    -1,    -1,
      -1,    -1,    -1,  1259,    -1,    -1,    -1,    -1,    -1,    -1,
    1266,   219,    -1,    -1,    -1,    -1,   224,  1273,    -1,    -1,
     228,   265,   230,    -1,    -1,   233,    -1,   235,    -1,  1285,
      -1,    -1,    -1,    -1,    -1,  1291,    -1,    -1,    -1,    -1,
      -1,  1297,     0,     1,    -1,     3,    -1,     5,    -1,   178,
      -1,    -1,    10,   178,    -1,    -1,    -1,   265,    -1,  1315,
      18,    -1,    -1,    -1,   189,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1330,  1331,  1332,  1333,  1334,  1335,
    1336,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   333,
      -1,    -1,    50,    51,    -1,    -1,  1352,    -1,   306,   228,
      58,   230,    -1,   228,   233,   230,    -1,    -1,   233,    -1,
     235,    69,    -1,    -1,    72,    -1,  1372,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   333,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   378,   379,   265,    -1,  1394,    -1,
     265,    -1,    -1,    -1,   388,    -1,    -1,    -1,   106,    -1,
      -1,    -1,    -1,    -1,    -1,   113,   114,    -1,    -1,   403,
      -1,   369,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   413,
     378,   379,   130,    -1,    -1,    -1,   134,   421,    -1,    -1,
      -1,   306,   426,    -1,    -1,   429,   144,   431,   432,    -1,
     398,    -1,  1448,  1449,    -1,   403,    -1,    -1,   156,    -1,
      -1,    -1,   160,    -1,   333,    -1,    -1,    -1,   333,    -1,
      -1,    -1,    -1,   421,    -1,   173,    -1,    -1,    -1,   177,
      -1,   429,   180,    -1,   432,   183,   184,    -1,    -1,    -1,
     438,    -1,    -1,   191,    -1,    -1,    -1,    -1,   446,    -1,
     198,    -1,   200,    -1,   369,   203,    -1,    -1,    -1,   378,
     379,    -1,    -1,   378,   379,    -1,    -1,    -1,  1514,  1515,
      -1,    -1,    -1,    -1,  1520,  1521,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   398,   403,    -1,    -1,    -1,   403,    -1,
     238,    -1,  1538,    -1,   242,    -1,   244,    -1,    -1,    -1,
    1546,    -1,   421,   251,    -1,    -1,   421,    -1,    -1,    -1,
     429,    -1,    -1,   432,   429,  1561,    -1,   432,    -1,    -1,
    1566,  1567,    -1,   438,    -1,   273,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     288,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1598,    -1,   302,    -1,    -1,    -1,    -1,    -1,
      -1,   309,    -1,  1609,    -1,  1611,    -1,    -1,    -1,    -1,
     318,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     6,   331,    -1,     9,    -1,    -1,   336,    -1,
     338,    -1,    -1,    17,    -1,    -1,    -1,    21,   346,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   356,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   365,    -1,    -1,
      -1,  1667,  1668,  1669,    -1,    -1,   374,    -1,   376,   377,
      -1,  1677,   380,    -1,   382,    -1,  1682,    -1,    -1,   387,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1695,
      -1,    -1,    -1,    -1,   402,    79,    -1,    -1,    -1,   407,
      -1,    -1,    -1,    -1,   412,    -1,    -1,    -1,    -1,    -1,
      94,    -1,    -1,    -1,    -1,   423,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   432,    -1,    -1,   435,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   445,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1754,    -1,
      -1,    -1,    -1,    -1,  1760,  1761,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1769,    -1,    -1,    -1,   151,   152,    -1,
      -1,    -1,    -1,    -1,  1780,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1788,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   178,   179,    -1,    -1,    -1,    -1,
      -1,   185,    -1,    -1,    -1,   189,    -1,    -1,    -1,  1815,
      -1,    -1,    -1,  1819,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   208,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   216,  1839,    -1,   219,   220,  1843,    -1,    -1,
     224,    -1,    -1,    -1,   228,    -1,   230,    -1,    -1,   233,
      -1,   235,  1858,  1859,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   248,    -1,    -1,    -1,    -1,   253,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
       6,   265,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1907,    -1,    -1,  1910,    -1,    -1,    -1,    -1,    71,
      -1,    73,    74,    75,    76,    77,    78,    -1,    -1,    -1,
      -1,    -1,   306,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1937,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   333,
      -1,   113,    -1,    79,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1969,    -1,    -1,    -1,    -1,    94,    -1,
    1976,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   369,    -1,    -1,    -1,  1995,
      -1,    -1,    -1,    -1,   378,   379,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2012,    -1,    -1,    -1,
      -1,   395,    -1,    -1,   398,   399,    -1,    -1,    -1,   403,
      -1,    -1,    -1,    -1,    -1,   151,   152,    -1,    -1,    -1,
      -1,    -1,    -1,   195,    -1,    -1,    -1,   421,    -1,    -1,
      -1,    -1,  2048,    -1,    -1,   429,    -1,    -1,   432,    -1,
      -1,    -1,   178,   179,   438,   439,   440,    -1,    -1,   185,
     444,    -1,   446,   189,   448,   449,   450,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   208,   245,    -1,    -1,    -1,    -1,    -1,    -1,
     216,    -1,    -1,   219,   220,    -1,    -1,    -1,   224,  2105,
      -1,     3,   228,     5,   230,    -1,    -1,   233,    10,   235,
      -1,    -1,    -1,    -1,  2120,    -1,    18,  2123,    -1,    -1,
     282,    -1,   248,    -1,    -1,    -1,    -1,   253,    -1,   291,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   265,
      -1,    -1,   304,    -1,    -1,    -1,    -1,  2153,    50,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    -1,     3,    -1,
       5,  2167,    -1,    -1,    -1,    10,  2172,    69,    -1,    -1,
      72,    -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,
     306,    -1,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  2198,    -1,    -1,    -1,    -1,    -1,   360,   361,
     362,    -1,    -1,  2209,   106,    50,    51,   333,    -1,    -1,
      -1,   113,   114,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      -1,    -1,   144,   369,    -1,    -1,    -1,   409,   410,   411,
    2256,    -1,   378,   379,   156,    -1,    -1,    -1,   160,    -1,
      -1,   106,    -1,    -1,    -1,    -1,    -1,    -1,   113,   114,
      -1,   173,   398,    -1,    -1,    -1,    -1,   403,   180,    -1,
      -1,   183,   184,    -1,    -1,    -1,    -1,    -1,    -1,   191,
      -1,    -1,    -1,    -1,    -1,   421,   198,    -1,   200,   144,
      -1,   203,    -1,   429,    -1,    -1,   432,    -1,    -1,    -1,
      -1,   156,   438,   439,   440,   160,    -1,    -1,   444,    -1,
     446,    -1,   448,   449,   450,    -1,    -1,    -1,   173,    -1,
      -1,    -1,    -1,    -1,    -1,   180,   238,    -1,   183,   184,
     242,    79,   244,    -1,    -1,    -1,   191,     6,    -1,   251,
       9,    -1,    -1,   198,    -1,   200,    94,    -1,   203,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   273,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       6,    -1,    -1,     9,    -1,    -1,   288,    -1,    -1,    48,
      -1,    -1,    -1,   238,    -1,    -1,    -1,   242,    -1,   244,
      -1,    -1,    -1,    29,    -1,    -1,   251,   309,     6,    -1,
      -1,     9,    -1,    -1,    -1,    -1,   318,    -1,    -1,    -1,
      79,    -1,    -1,    -1,    83,    -1,    -1,    -1,   273,   331,
      -1,    -1,    -1,    -1,   336,    94,   338,    -1,    64,    -1,
     178,    -1,    -1,   288,   346,    -1,    -1,    -1,    -1,    -1,
      -1,   189,    -1,    79,   356,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   365,   309,    -1,    -1,    -1,    94,    -1,
      -1,    -1,   374,   318,   376,   377,    -1,    -1,   380,    -1,
     382,    79,    -1,    -1,    -1,   387,   331,    -1,    -1,    -1,
     228,   336,   230,   338,    -1,   233,    94,   235,    -1,     6,
     402,   346,     9,    -1,    -1,   407,    -1,    -1,    -1,    -1,
     412,   356,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   178,
     365,   423,    -1,    -1,    -1,    -1,    -1,   265,    -1,   374,
     189,   376,   377,   435,    -1,   380,    -1,   382,    -1,    -1,
      -1,    -1,   387,   445,    -1,    -1,   144,    -1,    -1,    -1,
      -1,    -1,   178,    -1,    -1,    -1,    -1,   402,    -1,    -1,
     219,    -1,   407,   189,    -1,   224,    -1,   412,   306,   228,
      -1,   230,    79,    -1,   233,    -1,   235,    -1,   423,    -1,
     178,    -1,    -1,    -1,    -1,    -1,    -1,    94,    -1,    -1,
     435,   189,    -1,   219,    -1,   333,    -1,    -1,   224,   225,
     107,    -1,   228,    -1,   230,    -1,   265,   233,    -1,   235,
      -1,   270,    -1,    -1,    -1,     6,    -1,    -1,     9,    -1,
      -1,   219,    -1,    -1,    -1,    -1,   224,    -1,    -1,    -1,
     228,   369,   230,    -1,    -1,   233,    -1,   235,    -1,   265,
     378,   379,    -1,    -1,    -1,    -1,    -1,   306,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   316,    -1,    -1,
     398,    -1,    -1,    -1,    -1,   403,   292,   265,    -1,    -1,
      -1,   178,    -1,    -1,   333,    -1,    -1,    -1,    -1,    -1,
     306,     6,   189,   421,     9,    -1,    -1,    -1,    79,    -1,
      -1,   429,    -1,    -1,   432,    -1,    -1,   204,    -1,    90,
     438,    -1,    -1,    94,   363,    -1,    -1,   333,   306,    -1,
     369,    -1,   219,    -1,    -1,    -1,    -1,   224,    -1,   378,
     379,   228,    -1,   230,    -1,    -1,   233,    -1,   235,    -1,
      -1,    -1,    -1,    -1,    -1,   333,    -1,     6,    -1,   398,
       9,    -1,    -1,   369,   403,    -1,    -1,    -1,    -1,   408,
      -1,    -1,   378,   379,    79,    -1,    -1,    -1,   265,    -1,
      -1,    -1,   421,    -1,    -1,    90,   425,    -1,    -1,    94,
     429,   369,   398,   432,    -1,    -1,    -1,   403,    -1,   438,
     378,   379,    -1,    -1,    -1,    -1,    -1,   178,    -1,    -1,
      -1,    -1,    -1,     6,    -1,   421,     9,   395,   189,   306,
     398,   399,    -1,   429,    -1,   403,   432,    -1,    -1,    -1,
      79,    -1,   438,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   421,    -1,    94,   333,    -1,   219,    -1,
      -1,   429,    -1,   224,   432,    -1,    -1,   228,   107,   230,
     438,    -1,   233,    -1,   235,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   178,    -1,    -1,    -1,     6,    -1,    -1,
       9,    -1,   369,    -1,   189,    -1,    79,    -1,    -1,    -1,
      -1,   378,   379,    -1,   265,    -1,    -1,    90,    -1,     6,
      -1,    94,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   398,    -1,    -1,   219,    -1,   403,    -1,    -1,   224,
      -1,    -1,    -1,   228,    -1,   230,    -1,    -1,   233,   178,
     235,    -1,    -1,    -1,   421,   306,    -1,    -1,    -1,    -1,
     189,    -1,   429,    -1,    -1,   432,    -1,    -1,    -1,    -1,
      79,   438,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     265,    -1,   333,    -1,    -1,    94,    -1,    -1,    -1,    -1,
     219,    -1,    79,    -1,    -1,   224,    -1,    -1,    -1,   228,
      -1,   230,    -1,    -1,   233,   178,   235,    94,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   189,    -1,   369,    -1,
      -1,   306,    -1,    -1,    -1,    -1,    -1,   378,   379,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   265,    -1,    -1,     6,
      -1,    -1,     9,    -1,    -1,    -1,   219,   398,   333,    -1,
      -1,   224,   403,    -1,    -1,   228,    -1,   230,    -1,    -1,
     233,    -1,   235,    -1,    -1,    -1,    -1,    -1,    -1,   178,
     421,    -1,    -1,    -1,    -1,    -1,    -1,   306,   429,    -1,
     189,   432,    -1,    -1,   369,    -1,    -1,   438,    -1,    -1,
      -1,   178,   265,   378,   379,     6,    -1,    -1,     9,    -1,
      -1,    -1,   189,    -1,   333,    -1,    -1,    -1,    -1,    -1,
     219,    -1,    79,   398,    -1,   224,    -1,    -1,   403,   228,
      -1,   230,    -1,    -1,   233,    -1,   235,    94,    -1,    -1,
      -1,    -1,   219,   306,    -1,    -1,   421,   224,    -1,    -1,
     369,   228,    -1,   230,   429,    -1,   233,   432,   235,   378,
     379,    -1,    -1,   438,    -1,    -1,   265,    -1,    -1,    -1,
     333,     6,    -1,    -1,     9,    -1,    -1,    -1,    79,   398,
      -1,    -1,    -1,    -1,   403,    -1,    -1,    -1,   265,    -1,
      -1,    -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   421,    -1,    -1,    -1,   369,   306,    -1,    -1,
     429,    -1,    -1,   432,    -1,   378,   379,   174,    -1,   438,
      -1,   178,    -1,    -1,    -1,    -1,    -1,     6,    -1,   306,
       9,    -1,   189,    -1,   333,   398,    -1,    -1,    -1,    -1,
     403,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   333,    -1,   421,    94,
      -1,    -1,   219,    -1,    -1,    -1,   429,   224,    -1,   432,
     369,   228,    -1,   230,    -1,   438,   233,   178,   235,   378,
     379,    -1,    -1,    -1,    -1,    -1,   363,    -1,   189,    -1,
      -1,    -1,   369,    -1,    -1,   394,    -1,    -1,    -1,   398,
      79,   378,   379,    -1,   403,    -1,    -1,    -1,   265,    -1,
      -1,    -1,    -1,    -1,    -1,    94,    -1,    -1,   219,    -1,
      -1,   398,   421,   224,    -1,    -1,   403,   228,    -1,   230,
     429,    -1,   233,   432,   235,    -1,    -1,    -1,    -1,   438,
      -1,    -1,    -1,   178,   421,    -1,    -1,    -1,    -1,   306,
      -1,    -1,   429,    -1,   189,   432,    -1,    -1,    -1,    -1,
      -1,   438,    -1,    -1,   265,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   333,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   219,    -1,    -1,    -1,    -1,   224,
      -1,    -1,    -1,   228,    -1,   230,    -1,    -1,   233,   178,
     235,    -1,    -1,    -1,    -1,   306,    -1,    -1,    -1,    -1,
     189,    -1,   369,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   378,   379,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     265,    -1,   333,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     219,   398,    -1,    -1,    -1,   224,   403,    -1,    -1,   228,
      -1,   230,    -1,    -1,   233,    -1,   235,    -1,    -1,    -1,
      -1,    -1,    -1,   364,   421,    -1,    -1,    -1,   369,    -1,
      -1,   306,   429,    -1,    -1,   432,    -1,   378,   379,    -1,
      -1,   438,    -1,    -1,    -1,    -1,   265,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,   398,   333,    -1,
      -1,    -1,   403,    -1,    -1,    -1,    -1,    33,    -1,    -1,
      36,    37,    38,    39,    40,    41,    42,    -1,    -1,    -1,
     421,    -1,    -1,    -1,    -1,    -1,    -1,   306,   429,    -1,
      -1,   432,    -1,    -1,   369,    -1,    -1,   438,    -1,    -1,
      -1,    -1,    -1,   378,   379,    71,    -1,    73,    74,    75,
      76,    77,    78,    -1,   333,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   398,    -1,    -1,    -1,    -1,   403,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   421,   113,    -1,    -1,
     369,    -1,    -1,    -1,   429,    -1,    -1,   432,    -1,   378,
     379,    -1,    -1,   438,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   398,
      -1,    -1,    -1,    -1,   403,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   421,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     429,    -1,    -1,   432,    -1,    -1,    -1,    -1,    -1,   438,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,   195,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,   208,    -1,    -1,   211,    -1,    -1,    -1,    -1,
      -1,   217,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,    73,
      74,    75,    76,    77,    78,    -1,    -1,    -1,    -1,   245,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   267,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,
      -1,    -1,    -1,    -1,    -1,    -1,   282,    -1,    -1,    -1,
      -1,    -1,    -1,   289,    -1,   291,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   304,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   314,   153,
      -1,    -1,    -1,    -1,    -1,   321,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   171,    -1,    -1,
     174,   175,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   188,    -1,    -1,    -1,    -1,    79,
      -1,   195,   358,    -1,   360,   361,   362,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    -1,    -1,   211,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   384,    -1,
      -1,   225,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     234,    -1,    -1,    -1,    -1,   401,    -1,    -1,    -1,    -1,
      -1,   245,    -1,   409,   410,   411,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   422,    -1,    -1,   425,
      -1,    -1,    -1,   267,    -1,    -1,    -1,    -1,    -1,    36,
      37,    38,    39,    40,    41,    42,    -1,   281,   282,   445,
      -1,    -1,    -1,    -1,    -1,   289,    -1,   291,   178,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,   189,
     304,   305,    -1,    -1,    71,    -1,    73,    74,    75,    76,
      77,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   329,    79,    -1,    -1,   219,
     334,    -1,    -1,    -1,   224,    -1,    -1,    -1,   228,    -1,
     230,    94,    -1,   233,   348,   235,   113,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   358,    -1,   360,   361,   362,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    79,   265,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,
     394,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   405,    -1,    -1,    -1,   409,   410,   411,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   306,    -1,   422,   186,
     424,   425,    -1,    -1,    -1,   178,    -1,    -1,   195,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   189,    -1,    -1,    -1,
      -1,   445,    -1,   333,   211,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,
      -1,    -1,    -1,    -1,    -1,    -1,   219,    -1,    -1,    -1,
      -1,   224,    -1,   178,    -1,   228,    -1,   230,   245,   369,
     233,    -1,   235,   250,   189,    -1,    -1,    -1,   378,   379,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     267,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   398,    -1,
      -1,    -1,   265,   403,   219,   282,    -1,    -1,    -1,   224,
      -1,    -1,   289,   228,   291,   230,    -1,   294,   233,    -1,
     235,   421,    -1,    -1,    -1,    -1,    -1,   304,    -1,   429,
      -1,    -1,   432,    -1,    -1,    -1,    -1,    -1,   438,   439,
     440,    -1,    -1,   306,    -1,    -1,    -1,   447,   448,    -1,
     265,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     333,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   358,    -1,   360,   361,   362,    -1,    -1,    -1,    -1,
     367,   306,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   381,    -1,   369,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   378,   379,    -1,   333,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   404,    -1,    -1,
      -1,    -1,   409,   410,   411,   398,    -1,    -1,    -1,    -1,
     403,    -1,    -1,    -1,    -1,   422,    -1,    -1,   425,   426,
      -1,    -1,    -1,    -1,   369,    -1,    -1,    -1,   421,    -1,
      -1,    -1,    -1,   378,   379,    -1,   429,    -1,   445,   432,
      -1,    -1,    -1,    -1,    -1,   438,   439,   440,    -1,    -1,
      -1,    -1,    -1,   398,   447,   448,    -1,    -1,   403,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   421,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   429,    -1,    -1,   432,    -1,    -1,
      -1,    -1,    -1,   438,   439,   440,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   448
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
     317,   330,   355,   357,   365,   396,   445,   539,   540,   544,
     546,   551,   552,   553,   554,   558,   559,   560,   561,   562,
     563,   564,   565,  1104,  1081,   308,   660,   661,   662,   700,
     623,   620,  1121,   394,   594,  1060,   226,  1125,   394,  1114,
     194,  1120,   432,  1121,  1121,   725,     1,   432,   726,   727,
     728,   729,   730,   735,   474,   512,    17,   391,  1084,  1081,
     269,   271,   507,  1126,   310,   394,  1144,   355,  1126,  1121,
      54,  1113,    36,   108,   212,  1111,  1123,  1123,  1081,  1146,
     375,  1121,   698,   662,   701,    21,    33,    36,    37,    38,
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
     162,   542,  1121,   310,   317,   559,  1121,  1121,   355,  1121,
    1121,  1108,     9,   252,   309,   566,  1121,   432,   663,   617,
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
     125,   783,   151,   446,   784,  1048,   339,  1099,   310,  1133,
    1051,   127,   798,   740,   417,   418,   419,   420,   128,   802,
      48,   204,   761,    17,   428,   809,   810,   811,   815,  1106,
      96,  1128,  1065,  1055,   390,  1142,   840,  1146,  1076,    89,
     322,   385,   852,   853,   854,   858,   863,   934,  1067,   394,
     132,   874,    48,   161,   201,   209,   279,   878,   887,   133,
     884,   413,   426,   391,   393,   388,   250,   295,  1096,   174,
     994,  1133,   994,  1050,   138,   918,   426,   912,  1071,  1076,
    1083,   927,   929,  1064,   394,  1054,   116,   394,   414,   925,
     942,   181,   332,   948,  1112,   204,   952,  1076,   141,   958,
     174,   174,   310,   312,   967,   107,   970,   324,   371,   984,
     271,  1129,   994,   516,   117,   431,   550,  1094,  1103,   232,
     338,  1121,   547,   548,  1073,   668,   675,  1081,   617,   678,
     706,   109,   635,  1128,  1045,  1045,  1045,    68,   351,   447,
    1044,   439,   440,   441,   442,   444,   451,  1045,  1145,  1082,
    1125,  1062,   109,   592,  1071,    24,    25,    65,    67,    98,
      99,   100,   145,   147,   155,   226,   392,   432,  1054,   431,
     743,    64,   225,   292,   741,   742,   144,   301,  1069,  1077,
    1043,  1045,   394,  1045,  1043,  1088,  1077,  1083,  1085,   432,
    1045,  1091,  1045,  1045,  1090,  1045,  1043,  1043,  1045,  1089,
    1045,  1047,  1067,   181,   332,   755,  1095,    12,    13,    14,
      20,    57,   151,   152,   179,   185,   208,   216,   220,   248,
     249,   253,   263,   270,   275,   293,   438,   439,   440,   441,
     442,   444,   446,   447,   449,   450,  1038,  1039,  1040,  1041,
    1042,   208,   248,   253,   439,   440,   444,   448,  1038,  1039,
    1040,  1041,  1042,  1067,   300,   758,  1058,   762,   181,   332,
     766,   315,   406,   778,   779,  1146,  1033,   207,   257,  1025,
    1026,  1027,  1029,   416,   431,   795,  1146,   158,  1000,  1001,
    1000,  1000,  1000,  1067,  1047,  1067,    21,   395,   399,   816,
     817,  1034,   129,   819,   430,   811,   813,   428,   812,   808,
    1077,   109,   829,  1056,   834,     9,    12,    15,    16,   245,
     246,   263,   264,   841,   845,   166,  1071,     9,    55,   168,
     217,   401,   859,   860,   861,   855,   853,   936,  1103,  1129,
     394,  1064,  1047,  1067,   357,   879,   732,   733,  1032,   889,
     890,  1076,  1056,     8,    34,   996,  1133,  1073,   204,   893,
     905,  1146,   913,  1110,  1076,   913,   394,   394,   507,   144,
     395,   399,  1067,    48,   212,   943,  1067,  1067,   363,  1067,
    1076,   174,  1047,  1067,  1071,  1112,   204,   973,  1076,   154,
     158,   985,     9,   990,  1056,   905,   117,   547,   271,   549,
    1060,   549,   187,   670,   225,   226,   676,   432,   618,    30,
      32,    35,    43,    44,    45,    64,   153,   171,   174,   175,
     188,   225,   234,   267,   281,   305,   329,   334,   348,   394,
     405,   424,   445,   629,   630,   632,   642,   645,   647,   707,
     710,  1129,   636,   637,  1077,  1083,  1085,   447,  1045,  1045,
    1045,  1045,  1045,  1045,   447,  1045,   356,  1135,  1125,  1129,
     999,  1001,   437,   436,  1071,   999,   212,    30,    32,    35,
      45,   171,   175,   188,   234,   281,   305,   329,   334,   344,
     348,   405,   415,   744,   745,   999,   261,  1127,  1127,  1127,
     742,   741,   228,  1070,  1077,   447,  1076,   451,   447,  1044,
     447,   447,  1044,   447,   447,   447,   447,  1044,   447,   447,
     364,  1005,  1006,  1047,  1065,   332,  1144,   389,  1141,  1141,
     394,  1056,   763,   764,   765,  1112,  1076,  1076,   158,   280,
     767,   986,  1118,   232,   252,  1005,  1028,  1030,   126,   789,
    1029,    92,   296,   432,  1054,    32,    35,    43,    44,    45,
     153,   171,   188,   234,   281,   334,   344,   405,   796,   797,
    1000,   260,  1002,   256,  1003,   181,  1005,   181,  1106,   391,
     818,   814,   816,   732,  1129,   732,  1144,   322,   842,  1144,
     394,    48,   860,   862,  1071,     9,    55,   217,   401,   856,
     857,  1071,   937,  1104,   194,   276,  1130,    27,   110,   638,
    1064,  1005,   181,  1146,  1051,   133,   885,   734,     8,   174,
     893,  1076,   121,   254,  1015,  1016,  1018,  1025,   232,   252,
     428,   121,   428,   915,   916,  1071,  1070,  1067,  1121,  1025,
     953,  1146,  1076,  1005,   181,   394,     9,   971,   972,  1093,
     974,  1076,   953,   974,   298,   988,   299,   995,   996,  1094,
     243,   310,   312,   557,  1121,   168,   671,  1081,   679,  1121,
    1127,   148,   150,  1121,  1074,  1127,  1081,  1076,  1076,  1060,
     196,   639,   638,   447,  1144,  1060,  1003,   999,  1121,  1121,
     116,   414,   745,  1073,  1073,  1073,  1086,  1099,   447,  1045,
    1060,  1086,  1086,  1045,  1086,  1086,  1086,   217,   401,  1086,
    1086,  1007,   259,  1008,  1005,  1065,   275,   275,   764,   270,
     720,    83,   316,   425,   256,   258,   769,   987,   768,   320,
     335,   732,   732,   795,   795,   795,   795,  1121,   148,   150,
    1121,   116,   414,   797,   732,  1004,  1047,  1048,  1047,  1048,
     817,  1033,   732,  1076,   120,   835,   425,   843,   844,   845,
     105,   846,   425,  1072,  1076,  1082,  1071,    48,   864,   857,
     170,   864,   933,  1121,   276,  1123,  1047,   566,   880,  1146,
     735,   890,  1067,   193,   894,  1146,  1017,  1019,   136,   902,
    1018,   137,   906,   232,  1033,   914,  1032,   915,   253,   944,
    1097,   139,   945,   280,  1010,  1011,   291,  1099,  1047,  1072,
     275,  1071,   108,   975,   385,   977,  1129,   149,   255,   997,
    1020,  1021,  1023,  1026,     7,  1105,   557,  1081,   111,   214,
     672,    65,    64,    65,   186,   225,   226,   250,   294,   367,
     381,   404,   426,   445,   629,   630,   632,   633,   642,   645,
     647,   680,   681,   683,   684,   685,   686,   688,   689,   690,
     691,   695,   696,   438,  1075,  1076,  1081,  1121,  1075,  1121,
    1143,  1112,  1123,   395,   651,  1075,  1075,  1031,  1112,  1031,
    1005,   447,   732,  1009,   151,   151,  1067,   124,   771,   770,
     732,  1000,  1000,  1000,  1000,  1075,  1075,  1031,  1031,   732,
    1005,   319,  1005,   319,   836,   131,   837,   844,    97,  1116,
     864,   864,  1072,   996,   201,   424,   938,  1060,   935,  1005,
     232,   252,    48,   232,   212,   895,   192,   232,   252,   427,
     732,   732,   911,   732,   917,   668,  1038,  1039,  1040,  1041,
    1042,  1012,   140,   954,   258,  1013,  1076,  1005,  1005,   972,
    1120,    91,   976,  1120,  1010,   161,   201,   209,   279,   982,
    1051,  1022,  1024,   143,   998,  1023,   284,  1054,  1075,  1121,
      88,   215,   673,   262,  1127,   197,   697,   261,   262,   694,
    1107,   186,   428,  1121,  1128,  1121,  1076,   686,   250,   290,
     692,   693,  1081,   239,   290,   439,   440,   709,   239,   290,
     439,   440,   708,   432,   640,   641,  1121,  1121,  1075,   732,
    1144,  1144,   732,  1048,  1048,   732,    48,   864,   397,   865,
     298,  1051,   181,   279,   939,  1078,   335,  1067,  1121,   896,
    1015,  1026,   232,   232,   732,   732,   732,  1014,  1076,  1120,
    1076,   142,   978,   732,   732,   225,   226,  1124,  1081,  1121,
    1121,   169,   674,  1121,  1122,  1121,  1032,  1076,   687,  1060,
      87,    88,   111,   285,   286,   326,   327,   682,   174,   284,
    1081,   693,  1075,  1075,   641,  1059,  1082,  1124,  1005,  1005,
    1067,  1067,  1121,  1051,   298,   413,   668,   135,   897,   732,
    1076,  1081,  1081,  1121,  1081,  1081,  1099,  1067,   886,  1121,
    1032,  1081,    48,   886,  1067
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
		current_file->organization = cb_default_organization;
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
		current_file->organization = COB_ORG_RELATIVE;
		organized_seen = 1;
	}
  ;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1926 "parser.y"
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
#line 1941 "parser.y"
    {
	cb_verify (cb_padding_character_clause, "PADDING CHARACTER");
  ;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1950 "parser.y"
    { /* ignored */ ;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1958 "parser.y"
    {
	current_file->key = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 1962 "parser.y"
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
#line 1999 "parser.y"
    { current_file->key = (yyvsp[(4) - (4)]); ;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 2006 "parser.y"
    { /* ignored */ ;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 2013 "parser.y"
    { current_file->sharing = (yyvsp[(3) - (3)]); ;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 2017 "parser.y"
    { (yyval) = NULL; PENDING ("SHARING ALL OTHER"); ;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 2018 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 2019 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 2049 "parser.y"
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

  case 244:

/* Line 1455 of yacc.c  */
#line 2073 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 2074 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 2075 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 2076 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 2083 "parser.y"
    {
	cb_verify (cb_multiple_file_tape_clause, "MULTIPLE FILE TAPE");
  ;}
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 2094 "parser.y"
    { ;}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 2122 "parser.y"
    { current_storage = CB_STORAGE_FILE; ;}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 2125 "parser.y"
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

  case 263:

/* Line 1455 of yacc.c  */
#line 2144 "parser.y"
    {
	if ((yyvsp[(3) - (3)]) && (yyvsp[(3) - (3)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(3) - (3)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 2156 "parser.y"
    {
	if ((yyvsp[(2) - (2)]) && (yyvsp[(2) - (2)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(2) - (2)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 2167 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 2168 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 2178 "parser.y"
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

  case 269:

/* Line 1455 of yacc.c  */
#line 2189 "parser.y"
    {
	/* Shut up bison */
	dummy_tree = (yyvsp[(2) - (4)]);
  ;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 2201 "parser.y"
    {
	if (current_file->global) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->external = 1;
  ;}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 2208 "parser.y"
    {
	if (current_file->external) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->global = 1;
  ;}
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 2230 "parser.y"
    { /* ignored */ ;}
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 2240 "parser.y"
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

  case 288:

/* Line 1455 of yacc.c  */
#line 2252 "parser.y"
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

  case 289:

/* Line 1455 of yacc.c  */
#line 2278 "parser.y"
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

  case 291:

/* Line 1455 of yacc.c  */
#line 2302 "parser.y"
    {
	current_file->record_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 2308 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 2309 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 2313 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 2314 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 2322 "parser.y"
    {
	cb_verify (cb_label_records_clause, "LABEL RECORDS");
  ;}
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 2337 "parser.y"
    {
	cb_verify (cb_value_of_clause, "VALUE OF");
  ;}
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 2341 "parser.y"
    {
	if (!current_file->assign) {
		current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 2357 "parser.y"
    {
	cb_verify (cb_data_records_clause, "DATA RECORDS");
  ;}
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 2368 "parser.y"
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

  case 310:

/* Line 1455 of yacc.c  */
#line 2396 "parser.y"
    {
	current_file->latfoot = (yyvsp[(4) - (5)]);
  ;}
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 2403 "parser.y"
    {
	current_file->lattop = (yyvsp[(3) - (4)]);
  ;}
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 2410 "parser.y"
    {
	current_file->latbot = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 2419 "parser.y"
    { /* ignore */ ;}
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 2427 "parser.y"
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

  case 315:

/* Line 1455 of yacc.c  */
#line 2445 "parser.y"
    {
	cb_warning (_("file descriptor REPORT IS"));
  ;}
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 2449 "parser.y"
    {
	cb_warning (_("file descriptor REPORTS ARE"));
  ;}
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 2460 "parser.y"
    { current_storage = CB_STORAGE_WORKING; ;}
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 2462 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->working_storage =
			cb_field_add (current_program->working_storage, CB_FIELD ((yyvsp[(5) - (5)])));
	}
  ;}
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 2471 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 2472 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 2476 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 2482 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	(yyval) = CB_TREE (description_field);
  ;}
    break;

  case 328:

/* Line 1455 of yacc.c  */
#line 2502 "parser.y"
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

  case 329:

/* Line 1455 of yacc.c  */
#line 2513 "parser.y"
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

  case 331:

/* Line 1455 of yacc.c  */
#line 2537 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 2543 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 2549 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 334:

/* Line 1455 of yacc.c  */
#line 2558 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 2567 "parser.y"
    {
	current_field->flag_is_global = 1;
	cb_error (_("CONSTANT with GLOBAL clause is not yet supported"));
  ;}
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 2574 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 2575 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 2576 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 340:

/* Line 1455 of yacc.c  */
#line 2581 "parser.y"
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

  case 341:

/* Line 1455 of yacc.c  */
#line 2600 "parser.y"
    {
	/* required to check redefines */
	(yyval) = NULL;
  ;}
    break;

  case 342:

/* Line 1455 of yacc.c  */
#line 2606 "parser.y"
    {
	/* required to check redefines */
	(yyval) = cb_true;
  ;}
    break;

  case 357:

/* Line 1455 of yacc.c  */
#line 2634 "parser.y"
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

  case 358:

/* Line 1455 of yacc.c  */
#line 2656 "parser.y"
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

  case 359:

/* Line 1455 of yacc.c  */
#line 2677 "parser.y"
    { current_field->ename = NULL; ;}
    break;

  case 360:

/* Line 1455 of yacc.c  */
#line 2679 "parser.y"
    {
	struct cb_field *x;

	x = CB_FIELD(cb_build_field (cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(2) - (2)]))->data))));
	current_field->ename = x->name;
 ;}
    break;

  case 361:

/* Line 1455 of yacc.c  */
#line 2691 "parser.y"
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

  case 362:

/* Line 1455 of yacc.c  */
#line 2710 "parser.y"
    { current_field->pic = CB_PICTURE ((yyvsp[(1) - (1)])); ;}
    break;

  case 365:

/* Line 1455 of yacc.c  */
#line 2722 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 366:

/* Line 1455 of yacc.c  */
#line 2723 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 367:

/* Line 1455 of yacc.c  */
#line 2724 "parser.y"
    { current_field->usage = CB_USAGE_FLOAT; ;}
    break;

  case 368:

/* Line 1455 of yacc.c  */
#line 2725 "parser.y"
    { current_field->usage = CB_USAGE_DOUBLE; ;}
    break;

  case 369:

/* Line 1455 of yacc.c  */
#line 2726 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 370:

/* Line 1455 of yacc.c  */
#line 2727 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 371:

/* Line 1455 of yacc.c  */
#line 2728 "parser.y"
    { current_field->usage = CB_USAGE_COMP_5; ;}
    break;

  case 372:

/* Line 1455 of yacc.c  */
#line 2729 "parser.y"
    { current_field->usage = CB_USAGE_COMP_X; ;}
    break;

  case 373:

/* Line 1455 of yacc.c  */
#line 2730 "parser.y"
    { current_field->usage = CB_USAGE_DISPLAY; ;}
    break;

  case 374:

/* Line 1455 of yacc.c  */
#line 2731 "parser.y"
    { current_field->usage = CB_USAGE_INDEX; ;}
    break;

  case 375:

/* Line 1455 of yacc.c  */
#line 2732 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 376:

/* Line 1455 of yacc.c  */
#line 2734 "parser.y"
    {
	current_field->usage = CB_USAGE_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 377:

/* Line 1455 of yacc.c  */
#line 2739 "parser.y"
    {
	current_field->usage = CB_USAGE_PROGRAM_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 378:

/* Line 1455 of yacc.c  */
#line 2743 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 379:

/* Line 1455 of yacc.c  */
#line 2744 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 380:

/* Line 1455 of yacc.c  */
#line 2745 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 381:

/* Line 1455 of yacc.c  */
#line 2746 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 382:

/* Line 1455 of yacc.c  */
#line 2747 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 383:

/* Line 1455 of yacc.c  */
#line 2748 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 384:

/* Line 1455 of yacc.c  */
#line 2749 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 385:

/* Line 1455 of yacc.c  */
#line 2750 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_CHAR; ;}
    break;

  case 386:

/* Line 1455 of yacc.c  */
#line 2751 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 387:

/* Line 1455 of yacc.c  */
#line 2752 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 388:

/* Line 1455 of yacc.c  */
#line 2753 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 389:

/* Line 1455 of yacc.c  */
#line 2754 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 390:

/* Line 1455 of yacc.c  */
#line 2755 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 391:

/* Line 1455 of yacc.c  */
#line 2756 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 392:

/* Line 1455 of yacc.c  */
#line 2757 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 393:

/* Line 1455 of yacc.c  */
#line 2758 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 394:

/* Line 1455 of yacc.c  */
#line 2759 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 395:

/* Line 1455 of yacc.c  */
#line 2760 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 396:

/* Line 1455 of yacc.c  */
#line 2762 "parser.y"
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
#line 2770 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_UNSIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_UNSIGNED_LONG;
	}
  ;}
    break;

  case 398:

/* Line 1455 of yacc.c  */
#line 2778 "parser.y"
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
#line 2785 "parser.y"
    { PENDING ("USAGE NATIONAL");;}
    break;

  case 400:

/* Line 1455 of yacc.c  */
#line 2793 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 1;
  ;}
    break;

  case 401:

/* Line 1455 of yacc.c  */
#line 2798 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 0;
  ;}
    break;

  case 402:

/* Line 1455 of yacc.c  */
#line 2810 "parser.y"
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

  case 403:

/* Line 1455 of yacc.c  */
#line 2825 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 404:

/* Line 1455 of yacc.c  */
#line 2826 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 406:

/* Line 1455 of yacc.c  */
#line 2831 "parser.y"
    {
	current_field->occurs_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 407:

/* Line 1455 of yacc.c  */
#line 2838 "parser.y"
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

  case 408:

/* Line 1455 of yacc.c  */
#line 2861 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 409:

/* Line 1455 of yacc.c  */
#line 2864 "parser.y"
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

  case 410:

/* Line 1455 of yacc.c  */
#line 2879 "parser.y"
    { (yyval) = cb_int (COB_ASCENDING); ;}
    break;

  case 411:

/* Line 1455 of yacc.c  */
#line 2880 "parser.y"
    { (yyval) = cb_int (COB_DESCENDING); ;}
    break;

  case 413:

/* Line 1455 of yacc.c  */
#line 2885 "parser.y"
    {
	current_field->index_list = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 414:

/* Line 1455 of yacc.c  */
#line 2891 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 415:

/* Line 1455 of yacc.c  */
#line 2893 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 416:

/* Line 1455 of yacc.c  */
#line 2898 "parser.y"
    {
	(yyval) = cb_build_index ((yyvsp[(1) - (1)]), cb_int1, 1, current_field);
  ;}
    break;

  case 417:

/* Line 1455 of yacc.c  */
#line 2907 "parser.y"
    { current_field->flag_justified = 1; ;}
    break;

  case 418:

/* Line 1455 of yacc.c  */
#line 2914 "parser.y"
    { current_field->flag_synchronized = 1; ;}
    break;

  case 422:

/* Line 1455 of yacc.c  */
#line 2926 "parser.y"
    { current_field->flag_blank_zero = 1; ;}
    break;

  case 423:

/* Line 1455 of yacc.c  */
#line 2934 "parser.y"
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

  case 424:

/* Line 1455 of yacc.c  */
#line 2958 "parser.y"
    { current_field->values = (yyvsp[(3) - (3)]); ;}
    break;

  case 426:

/* Line 1455 of yacc.c  */
#line 2963 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 427:

/* Line 1455 of yacc.c  */
#line 2964 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 428:

/* Line 1455 of yacc.c  */
#line 2968 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 429:

/* Line 1455 of yacc.c  */
#line 2969 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 431:

/* Line 1455 of yacc.c  */
#line 2974 "parser.y"
    {
	if (current_field->level != 88) {
		cb_error (_("FALSE clause only allowed for 88 level"));
	}
	current_field->false_88 = cb_list_init ((yyvsp[(3) - (3)]));
  ;}
    break;

  case 432:

/* Line 1455 of yacc.c  */
#line 2987 "parser.y"
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

  case 433:

/* Line 1455 of yacc.c  */
#line 2999 "parser.y"
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

  case 434:

/* Line 1455 of yacc.c  */
#line 3019 "parser.y"
    {
	if (current_field->flag_item_based) {
		cb_error (_("BASED and ANY LENGTH are mutually exclusive"));
	} else {
		current_field->flag_any_length = 1;
	}
  ;}
    break;

  case 436:

/* Line 1455 of yacc.c  */
#line 3034 "parser.y"
    {
	current_storage = CB_STORAGE_LOCAL;
	if (current_program->nested_level) {
		cb_error (_("LOCAL-STORAGE not allowed in nested programs"));
	}
  ;}
    break;

  case 437:

/* Line 1455 of yacc.c  */
#line 3041 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->local_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 439:

/* Line 1455 of yacc.c  */
#line 3054 "parser.y"
    { current_storage = CB_STORAGE_LINKAGE; ;}
    break;

  case 440:

/* Line 1455 of yacc.c  */
#line 3056 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->linkage_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 442:

/* Line 1455 of yacc.c  */
#line 3069 "parser.y"
    {
	cb_error (_("REPORT SECTION not supported"));
	current_storage = CB_STORAGE_REPORT;
  ;}
    break;

  case 449:

/* Line 1455 of yacc.c  */
#line 3102 "parser.y"
    {
	cb_warning (_("Report description using defaults"));
  ;}
    break;

  case 451:

/* Line 1455 of yacc.c  */
#line 3110 "parser.y"
    {
	cb_error (_("GLOBAL is not allowed with RD"));
  ;}
    break;

  case 460:

/* Line 1455 of yacc.c  */
#line 3133 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 461:

/* Line 1455 of yacc.c  */
#line 3134 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 483:

/* Line 1455 of yacc.c  */
#line 3190 "parser.y"
    { cb_warning (_("looking for Report line TYPE")); ;}
    break;

  case 534:

/* Line 1455 of yacc.c  */
#line 3295 "parser.y"
    { current_storage = CB_STORAGE_SCREEN; ;}
    break;

  case 535:

/* Line 1455 of yacc.c  */
#line 3296 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 536:

/* Line 1455 of yacc.c  */
#line 3302 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	current_program->screen_storage = description_field;
	current_program->flag_screen = 1;
  ;}
    break;

  case 542:

/* Line 1455 of yacc.c  */
#line 3326 "parser.y"
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

  case 543:

/* Line 1455 of yacc.c  */
#line 3342 "parser.y"
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

  case 546:

/* Line 1455 of yacc.c  */
#line 3366 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 547:

/* Line 1455 of yacc.c  */
#line 3367 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 548:

/* Line 1455 of yacc.c  */
#line 3368 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BELL; ;}
    break;

  case 549:

/* Line 1455 of yacc.c  */
#line 3369 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLINK; ;}
    break;

  case 550:

/* Line 1455 of yacc.c  */
#line 3370 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 551:

/* Line 1455 of yacc.c  */
#line 3371 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 552:

/* Line 1455 of yacc.c  */
#line 3372 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 553:

/* Line 1455 of yacc.c  */
#line 3373 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 554:

/* Line 1455 of yacc.c  */
#line 3374 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REVERSE; ;}
    break;

  case 555:

/* Line 1455 of yacc.c  */
#line 3375 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 556:

/* Line 1455 of yacc.c  */
#line 3376 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_OVERLINE; ;}
    break;

  case 557:

/* Line 1455 of yacc.c  */
#line 3377 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_AUTO; ;}
    break;

  case 558:

/* Line 1455 of yacc.c  */
#line 3378 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_SECURE; ;}
    break;

  case 559:

/* Line 1455 of yacc.c  */
#line 3379 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REQUIRED; ;}
    break;

  case 560:

/* Line 1455 of yacc.c  */
#line 3380 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_FULL; ;}
    break;

  case 561:

/* Line 1455 of yacc.c  */
#line 3381 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_PROMPT; ;}
    break;

  case 562:

/* Line 1455 of yacc.c  */
#line 3383 "parser.y"
    {
	current_field->screen_line = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 563:

/* Line 1455 of yacc.c  */
#line 3387 "parser.y"
    {
	current_field->screen_column = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 564:

/* Line 1455 of yacc.c  */
#line 3391 "parser.y"
    {
	current_field->screen_foreg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 565:

/* Line 1455 of yacc.c  */
#line 3395 "parser.y"
    {
	current_field->screen_backg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 573:

/* Line 1455 of yacc.c  */
#line 3406 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 574:

/* Line 1455 of yacc.c  */
#line 3413 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 575:

/* Line 1455 of yacc.c  */
#line 3417 "parser.y"
    {
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 576:

/* Line 1455 of yacc.c  */
#line 3426 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 577:

/* Line 1455 of yacc.c  */
#line 3430 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 578:

/* Line 1455 of yacc.c  */
#line 3434 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 579:

/* Line 1455 of yacc.c  */
#line 3438 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 580:

/* Line 1455 of yacc.c  */
#line 3442 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 581:

/* Line 1455 of yacc.c  */
#line 3449 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 582:

/* Line 1455 of yacc.c  */
#line 3453 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 583:

/* Line 1455 of yacc.c  */
#line 3457 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 584:

/* Line 1455 of yacc.c  */
#line 3461 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 585:

/* Line 1455 of yacc.c  */
#line 3465 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 586:

/* Line 1455 of yacc.c  */
#line 3473 "parser.y"
    {
	current_field->occurs_max = cb_get_int ((yyvsp[(2) - (3)]));
	current_field->occurs_min = current_field->occurs_max;
	current_field->indexes++;
	current_field->flag_occurs = 1;
  ;}
    break;

  case 588:

/* Line 1455 of yacc.c  */
#line 3487 "parser.y"
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

  case 589:

/* Line 1455 of yacc.c  */
#line 3497 "parser.y"
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

  case 590:

/* Line 1455 of yacc.c  */
#line 3507 "parser.y"
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

  case 591:

/* Line 1455 of yacc.c  */
#line 3524 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 592:

/* Line 1455 of yacc.c  */
#line 3526 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 593:

/* Line 1455 of yacc.c  */
#line 3530 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 594:

/* Line 1455 of yacc.c  */
#line 3532 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	current_program->flag_chained = 1;
  ;}
    break;

  case 595:

/* Line 1455 of yacc.c  */
#line 3536 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 596:

/* Line 1455 of yacc.c  */
#line 3540 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 597:

/* Line 1455 of yacc.c  */
#line 3542 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 598:

/* Line 1455 of yacc.c  */
#line 3547 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), cb_build_identifier ((yyvsp[(4) - (4)])));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 600:

/* Line 1455 of yacc.c  */
#line 3556 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 601:

/* Line 1455 of yacc.c  */
#line 3560 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
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
		size_mode = CB_SIZE_AUTO;
	}
  ;}
    break;

  case 604:

/* Line 1455 of yacc.c  */
#line 3580 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_4;
	}
  ;}
    break;

  case 605:

/* Line 1455 of yacc.c  */
#line 3588 "parser.y"
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

  case 606:

/* Line 1455 of yacc.c  */
#line 3617 "parser.y"
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

  case 608:

/* Line 1455 of yacc.c  */
#line 3650 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OPTIONAL only allowed for BY REFERENCE items"));
	}
  ;}
    break;

  case 609:

/* Line 1455 of yacc.c  */
#line 3659 "parser.y"
    {
	if (current_program->prog_type == CB_FUNCTION_TYPE) {
		cb_error (_("RETURNING clause is required for a FUNCTION"));
	}
  ;}
    break;

  case 610:

/* Line 1455 of yacc.c  */
#line 3665 "parser.y"
    {
	if (cb_ref ((yyvsp[(2) - (2)])) != cb_error_node) {
		current_program->returning = (yyvsp[(2) - (2)]);
		if (cb_field ((yyvsp[(2) - (2)]))->storage != CB_STORAGE_LINKAGE) {
			cb_error (_("RETURNING item is not defined in LINKAGE SECTION"));
		}
	}
  ;}
    break;

  case 612:

/* Line 1455 of yacc.c  */
#line 3676 "parser.y"
    { in_declaratives = 1; ;}
    break;

  case 613:

/* Line 1455 of yacc.c  */
#line 3679 "parser.y"
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

  case 619:

/* Line 1455 of yacc.c  */
#line 3712 "parser.y"
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

  case 620:

/* Line 1455 of yacc.c  */
#line 3728 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 621:

/* Line 1455 of yacc.c  */
#line 3740 "parser.y"
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

  case 622:

/* Line 1455 of yacc.c  */
#line 3771 "parser.y"
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

  case 623:

/* Line 1455 of yacc.c  */
#line 3808 "parser.y"
    {
	non_const_word = 0;
	check_unreached = 0;
	if ((yyvsp[(1) - (1)]) != cb_error_node) {
		cb_error_x ((yyvsp[(1) - (1)]), _("Unknown statement '%s'"), CB_NAME ((yyvsp[(1) - (1)])));
	}
	YYERROR;
  ;}
    break;

  case 624:

/* Line 1455 of yacc.c  */
#line 3819 "parser.y"
    { (yyval) = cb_build_section_name ((yyvsp[(1) - (1)]), 0); ;}
    break;

  case 626:

/* Line 1455 of yacc.c  */
#line 3823 "parser.y"
    { /* ignore */ ;}
    break;

  case 627:

/* Line 1455 of yacc.c  */
#line 3832 "parser.y"
    {
	(yyval) = current_program->exec_list;
	current_program->exec_list = NULL;
  ;}
    break;

  case 628:

/* Line 1455 of yacc.c  */
#line 3836 "parser.y"
    {
	(yyval) = CB_TREE (current_statement);
	current_statement = NULL;
  ;}
    break;

  case 629:

/* Line 1455 of yacc.c  */
#line 3841 "parser.y"
    {
	(yyval) = cb_list_reverse (current_program->exec_list);
	current_program->exec_list = (yyvsp[(1) - (3)]);
	current_statement = CB_STATEMENT ((yyvsp[(2) - (3)]));
  ;}
    break;

  case 630:

/* Line 1455 of yacc.c  */
#line 3849 "parser.y"
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

  case 681:

/* Line 1455 of yacc.c  */
#line 3921 "parser.y"
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

  case 682:

/* Line 1455 of yacc.c  */
#line 3943 "parser.y"
    {
	BEGIN_STATEMENT ("ACCEPT", TERM_ACCEPT);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 684:

/* Line 1455 of yacc.c  */
#line 3956 "parser.y"
    {
	cb_emit_accept ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 685:

/* Line 1455 of yacc.c  */
#line 3960 "parser.y"
    {
	PENDING ("ACCEPT .. FROM ESCAPE KEY");
  ;}
    break;

  case 686:

/* Line 1455 of yacc.c  */
#line 3964 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 0);
  ;}
    break;

  case 687:

/* Line 1455 of yacc.c  */
#line 3968 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 1);
  ;}
    break;

  case 688:

/* Line 1455 of yacc.c  */
#line 3972 "parser.y"
    {
	cb_emit_accept_date ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 689:

/* Line 1455 of yacc.c  */
#line 3976 "parser.y"
    {
	cb_emit_accept_date_yyyymmdd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 690:

/* Line 1455 of yacc.c  */
#line 3980 "parser.y"
    {
	cb_emit_accept_day ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 691:

/* Line 1455 of yacc.c  */
#line 3984 "parser.y"
    {
	cb_emit_accept_day_yyyyddd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 692:

/* Line 1455 of yacc.c  */
#line 3988 "parser.y"
    {
	cb_emit_accept_day_of_week ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 693:

/* Line 1455 of yacc.c  */
#line 3992 "parser.y"
    {
	cb_emit_accept_time ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 694:

/* Line 1455 of yacc.c  */
#line 3996 "parser.y"
    {
	cb_emit_accept_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 695:

/* Line 1455 of yacc.c  */
#line 4000 "parser.y"
    {
	cb_emit_accept_environment ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 696:

/* Line 1455 of yacc.c  */
#line 4004 "parser.y"
    { 
	cb_emit_get_environment ((yyvsp[(4) - (5)]), (yyvsp[(1) - (5)]));
  ;}
    break;

  case 697:

/* Line 1455 of yacc.c  */
#line 4008 "parser.y"
    {
	cb_emit_accept_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 698:

/* Line 1455 of yacc.c  */
#line 4012 "parser.y"
    {
	cb_emit_accept_arg_value ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 699:

/* Line 1455 of yacc.c  */
#line 4016 "parser.y"
    {
	cb_emit_accept_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 700:

/* Line 1455 of yacc.c  */
#line 4020 "parser.y"
    {
	cb_emit_accept_name ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 701:

/* Line 1455 of yacc.c  */
#line 4026 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 702:

/* Line 1455 of yacc.c  */
#line 4027 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 703:

/* Line 1455 of yacc.c  */
#line 4028 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); ;}
    break;

  case 704:

/* Line 1455 of yacc.c  */
#line 4029 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), NULL); ;}
    break;

  case 705:

/* Line 1455 of yacc.c  */
#line 4030 "parser.y"
    { (yyval) = cb_build_pair (NULL, (yyvsp[(2) - (2)])); ;}
    break;

  case 706:

/* Line 1455 of yacc.c  */
#line 4031 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 707:

/* Line 1455 of yacc.c  */
#line 4035 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 708:

/* Line 1455 of yacc.c  */
#line 4039 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 709:

/* Line 1455 of yacc.c  */
#line 4040 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 714:

/* Line 1455 of yacc.c  */
#line 4053 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 715:

/* Line 1455 of yacc.c  */
#line 4054 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 716:

/* Line 1455 of yacc.c  */
#line 4055 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 717:

/* Line 1455 of yacc.c  */
#line 4056 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 718:

/* Line 1455 of yacc.c  */
#line 4057 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 719:

/* Line 1455 of yacc.c  */
#line 4058 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 720:

/* Line 1455 of yacc.c  */
#line 4059 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 721:

/* Line 1455 of yacc.c  */
#line 4061 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 722:

/* Line 1455 of yacc.c  */
#line 4065 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 723:

/* Line 1455 of yacc.c  */
#line 4069 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 724:

/* Line 1455 of yacc.c  */
#line 4073 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 725:

/* Line 1455 of yacc.c  */
#line 4077 "parser.y"
    { dispattrs |= COB_SCREEN_AUTO; ;}
    break;

  case 726:

/* Line 1455 of yacc.c  */
#line 4078 "parser.y"
    { dispattrs |= COB_SCREEN_FULL; ;}
    break;

  case 727:

/* Line 1455 of yacc.c  */
#line 4079 "parser.y"
    { dispattrs |= COB_SCREEN_REQUIRED; ;}
    break;

  case 728:

/* Line 1455 of yacc.c  */
#line 4080 "parser.y"
    { dispattrs |= COB_SCREEN_SECURE; ;}
    break;

  case 729:

/* Line 1455 of yacc.c  */
#line 4081 "parser.y"
    { dispattrs |= COB_SCREEN_UPDATE; ;}
    break;

  case 730:

/* Line 1455 of yacc.c  */
#line 4082 "parser.y"
    { dispattrs |= COB_SCREEN_PROMPT; ;}
    break;

  case 731:

/* Line 1455 of yacc.c  */
#line 4086 "parser.y"
    { terminator_warning (TERM_ACCEPT); ;}
    break;

  case 732:

/* Line 1455 of yacc.c  */
#line 4087 "parser.y"
    { terminator_clear (TERM_ACCEPT); ;}
    break;

  case 733:

/* Line 1455 of yacc.c  */
#line 4096 "parser.y"
    { BEGIN_STATEMENT ("ADD", TERM_ADD); ;}
    break;

  case 735:

/* Line 1455 of yacc.c  */
#line 4103 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '+', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 736:

/* Line 1455 of yacc.c  */
#line 4107 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(4) - (5)]), 0, cb_build_binary_list ((yyvsp[(1) - (5)]), '+'));
  ;}
    break;

  case 737:

/* Line 1455 of yacc.c  */
#line 4111 "parser.y"
    {
	cb_emit_corresponding (cb_build_add, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 739:

/* Line 1455 of yacc.c  */
#line 4117 "parser.y"
    { cb_list_add ((yyvsp[(0) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 740:

/* Line 1455 of yacc.c  */
#line 4121 "parser.y"
    { terminator_warning (TERM_ADD); ;}
    break;

  case 741:

/* Line 1455 of yacc.c  */
#line 4122 "parser.y"
    { terminator_clear (TERM_ADD); ;}
    break;

  case 742:

/* Line 1455 of yacc.c  */
#line 4131 "parser.y"
    { BEGIN_STATEMENT ("ALLOCATE", 0); ;}
    break;

  case 744:

/* Line 1455 of yacc.c  */
#line 4137 "parser.y"
    {
	cb_emit_allocate ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), NULL, (yyvsp[(2) - (3)]));
  ;}
    break;

  case 745:

/* Line 1455 of yacc.c  */
#line 4141 "parser.y"
    {
	cb_emit_allocate (NULL, (yyvsp[(5) - (5)]), (yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]));
  ;}
    break;

  case 746:

/* Line 1455 of yacc.c  */
#line 4147 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 747:

/* Line 1455 of yacc.c  */
#line 4148 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 748:

/* Line 1455 of yacc.c  */
#line 4158 "parser.y"
    {
	cb_error (_("ALTER statement is obsolete and unsupported"));
  ;}
    break;

  case 753:

/* Line 1455 of yacc.c  */
#line 4176 "parser.y"
    { BEGIN_STATEMENT ("CALL", TERM_CALL); ;}
    break;

  case 754:

/* Line 1455 of yacc.c  */
#line 4180 "parser.y"
    {
	cb_emit_call ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 755:

/* Line 1455 of yacc.c  */
#line 4186 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 756:

/* Line 1455 of yacc.c  */
#line 4188 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 757:

/* Line 1455 of yacc.c  */
#line 4192 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 758:

/* Line 1455 of yacc.c  */
#line 4196 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 759:

/* Line 1455 of yacc.c  */
#line 4198 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 760:

/* Line 1455 of yacc.c  */
#line 4203 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OMITTED only allowed with BY REFERENCE"));
	}
	(yyval) = cb_build_pair (cb_int (call_mode), cb_null);
  ;}
    break;

  case 761:

/* Line 1455 of yacc.c  */
#line 4210 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), (yyvsp[(3) - (3)]));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 763:

/* Line 1455 of yacc.c  */
#line 4219 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 764:

/* Line 1455 of yacc.c  */
#line 4223 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY CONTENT not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_CONTENT;
	}
  ;}
    break;

  case 765:

/* Line 1455 of yacc.c  */
#line 4231 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 766:

/* Line 1455 of yacc.c  */
#line 4241 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 767:

/* Line 1455 of yacc.c  */
#line 4242 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 768:

/* Line 1455 of yacc.c  */
#line 4243 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 769:

/* Line 1455 of yacc.c  */
#line 4248 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 770:

/* Line 1455 of yacc.c  */
#line 4252 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 771:

/* Line 1455 of yacc.c  */
#line 4256 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 772:

/* Line 1455 of yacc.c  */
#line 4263 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 773:

/* Line 1455 of yacc.c  */
#line 4267 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 774:

/* Line 1455 of yacc.c  */
#line 4271 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 775:

/* Line 1455 of yacc.c  */
#line 4277 "parser.y"
    { terminator_warning (TERM_CALL); ;}
    break;

  case 776:

/* Line 1455 of yacc.c  */
#line 4278 "parser.y"
    { terminator_clear (TERM_CALL); ;}
    break;

  case 777:

/* Line 1455 of yacc.c  */
#line 4287 "parser.y"
    { BEGIN_STATEMENT ("CANCEL", 0); ;}
    break;

  case 780:

/* Line 1455 of yacc.c  */
#line 4293 "parser.y"
    {
	cb_emit_cancel ((yyvsp[(2) - (2)]));
  ;}
    break;

  case 781:

/* Line 1455 of yacc.c  */
#line 4304 "parser.y"
    { BEGIN_STATEMENT ("CLOSE", 0); ;}
    break;

  case 784:

/* Line 1455 of yacc.c  */
#line 4311 "parser.y"
    {
	BEGIN_IMPLICIT_STATEMENT ();
	if ((yyvsp[(2) - (3)]) != cb_error_node) {
		cb_emit_close ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
	}
  ;}
    break;

  case 785:

/* Line 1455 of yacc.c  */
#line 4320 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NORMAL); ;}
    break;

  case 786:

/* Line 1455 of yacc.c  */
#line 4321 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT); ;}
    break;

  case 787:

/* Line 1455 of yacc.c  */
#line 4322 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT_REMOVAL); ;}
    break;

  case 788:

/* Line 1455 of yacc.c  */
#line 4323 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NO_REWIND); ;}
    break;

  case 789:

/* Line 1455 of yacc.c  */
#line 4324 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_LOCK); ;}
    break;

  case 792:

/* Line 1455 of yacc.c  */
#line 4335 "parser.y"
    { BEGIN_STATEMENT ("COMPUTE", TERM_COMPUTE); ;}
    break;

  case 794:

/* Line 1455 of yacc.c  */
#line 4342 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(1) - (4)]), 0, (yyvsp[(3) - (4)]));
  ;}
    break;

  case 795:

/* Line 1455 of yacc.c  */
#line 4348 "parser.y"
    { terminator_warning (TERM_COMPUTE); ;}
    break;

  case 796:

/* Line 1455 of yacc.c  */
#line 4349 "parser.y"
    { terminator_clear (TERM_COMPUTE); ;}
    break;

  case 799:

/* Line 1455 of yacc.c  */
#line 4360 "parser.y"
    {
	BEGIN_STATEMENT ("COMMIT", 0);
	cb_emit_commit ();
  ;}
    break;

  case 800:

/* Line 1455 of yacc.c  */
#line 4373 "parser.y"
    {
	BEGIN_STATEMENT ("CONTINUE", 0);
	cb_emit_continue ();
  ;}
    break;

  case 801:

/* Line 1455 of yacc.c  */
#line 4385 "parser.y"
    { BEGIN_STATEMENT ("DELETE", TERM_DELETE); ;}
    break;

  case 802:

/* Line 1455 of yacc.c  */
#line 4388 "parser.y"
    {
	if ((yyvsp[(3) - (6)]) != cb_error_node) {
		cb_emit_delete ((yyvsp[(3) - (6)]));
	}
  ;}
    break;

  case 803:

/* Line 1455 of yacc.c  */
#line 4396 "parser.y"
    { terminator_warning (TERM_DELETE); ;}
    break;

  case 804:

/* Line 1455 of yacc.c  */
#line 4397 "parser.y"
    { terminator_clear (TERM_DELETE); ;}
    break;

  case 805:

/* Line 1455 of yacc.c  */
#line 4406 "parser.y"
    { BEGIN_STATEMENT ("DELETE-FILE", 0); ;}
    break;

  case 806:

/* Line 1455 of yacc.c  */
#line 4408 "parser.y"
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

  case 807:

/* Line 1455 of yacc.c  */
#line 4426 "parser.y"
    {
	BEGIN_STATEMENT ("DISPLAY", TERM_DISPLAY);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 809:

/* Line 1455 of yacc.c  */
#line 4439 "parser.y"
    {
	cb_emit_env_name ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 810:

/* Line 1455 of yacc.c  */
#line 4443 "parser.y"
    {
	cb_emit_env_value ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 811:

/* Line 1455 of yacc.c  */
#line 4447 "parser.y"
    {
	cb_emit_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 812:

/* Line 1455 of yacc.c  */
#line 4451 "parser.y"
    {
	cb_emit_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 813:

/* Line 1455 of yacc.c  */
#line 4455 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (4)]), cb_int0, (yyvsp[(3) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 814:

/* Line 1455 of yacc.c  */
#line 4459 "parser.y"
    {
	cb_emit_display_mnemonic ((yyvsp[(1) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 815:

/* Line 1455 of yacc.c  */
#line 4463 "parser.y"
    {
	cb_tree word = cb_build_display_upon_direct ((yyvsp[(4) - (6)]));
	cb_emit_display ((yyvsp[(1) - (6)]), word, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 816:

/* Line 1455 of yacc.c  */
#line 4468 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 817:

/* Line 1455 of yacc.c  */
#line 4472 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 818:

/* Line 1455 of yacc.c  */
#line 4478 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 819:

/* Line 1455 of yacc.c  */
#line 4479 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 820:

/* Line 1455 of yacc.c  */
#line 4480 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 823:

/* Line 1455 of yacc.c  */
#line 4490 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 824:

/* Line 1455 of yacc.c  */
#line 4491 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 825:

/* Line 1455 of yacc.c  */
#line 4492 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 826:

/* Line 1455 of yacc.c  */
#line 4493 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 827:

/* Line 1455 of yacc.c  */
#line 4494 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 828:

/* Line 1455 of yacc.c  */
#line 4495 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 829:

/* Line 1455 of yacc.c  */
#line 4496 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 830:

/* Line 1455 of yacc.c  */
#line 4497 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 831:

/* Line 1455 of yacc.c  */
#line 4498 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 832:

/* Line 1455 of yacc.c  */
#line 4500 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 833:

/* Line 1455 of yacc.c  */
#line 4504 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 834:

/* Line 1455 of yacc.c  */
#line 4508 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 835:

/* Line 1455 of yacc.c  */
#line 4512 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 836:

/* Line 1455 of yacc.c  */
#line 4516 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 837:

/* Line 1455 of yacc.c  */
#line 4517 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 838:

/* Line 1455 of yacc.c  */
#line 4521 "parser.y"
    { terminator_warning (TERM_DISPLAY); ;}
    break;

  case 839:

/* Line 1455 of yacc.c  */
#line 4522 "parser.y"
    { terminator_clear (TERM_DISPLAY); ;}
    break;

  case 840:

/* Line 1455 of yacc.c  */
#line 4531 "parser.y"
    { BEGIN_STATEMENT ("DIVIDE", TERM_DIVIDE); ;}
    break;

  case 842:

/* Line 1455 of yacc.c  */
#line 4538 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '/', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 843:

/* Line 1455 of yacc.c  */
#line 4542 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(3) - (6)]), '/', (yyvsp[(1) - (6)])));
  ;}
    break;

  case 844:

/* Line 1455 of yacc.c  */
#line 4546 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '/', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 845:

/* Line 1455 of yacc.c  */
#line 4550 "parser.y"
    {
	cb_emit_divide ((yyvsp[(3) - (8)]), (yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 846:

/* Line 1455 of yacc.c  */
#line 4554 "parser.y"
    {
	cb_emit_divide ((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 847:

/* Line 1455 of yacc.c  */
#line 4560 "parser.y"
    { terminator_warning (TERM_DIVIDE); ;}
    break;

  case 848:

/* Line 1455 of yacc.c  */
#line 4561 "parser.y"
    { terminator_clear (TERM_DIVIDE); ;}
    break;

  case 849:

/* Line 1455 of yacc.c  */
#line 4570 "parser.y"
    { BEGIN_STATEMENT ("ENTRY", 0); ;}
    break;

  case 850:

/* Line 1455 of yacc.c  */
#line 4572 "parser.y"
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

  case 851:

/* Line 1455 of yacc.c  */
#line 4592 "parser.y"
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

  case 852:

/* Line 1455 of yacc.c  */
#line 4603 "parser.y"
    {
	cb_emit_evaluate ((yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]));
	eval_level--;
  ;}
    break;

  case 853:

/* Line 1455 of yacc.c  */
#line 4610 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 854:

/* Line 1455 of yacc.c  */
#line 4613 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 855:

/* Line 1455 of yacc.c  */
#line 4623 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE_P ((yyvsp[(1) - (1)]))) {
		eval_check[eval_level][eval_inc++] = 0;
	} else {
		eval_check[eval_level][eval_inc++] = 1;
	}
  ;}
    break;

  case 856:

/* Line 1455 of yacc.c  */
#line 4632 "parser.y"
    {
	(yyval) = cb_true;
	eval_check[eval_level][eval_inc++] = 2;
  ;}
    break;

  case 857:

/* Line 1455 of yacc.c  */
#line 4637 "parser.y"
    {
	(yyval) = cb_false;
	eval_check[eval_level][eval_inc++] = 3;
  ;}
    break;

  case 858:

/* Line 1455 of yacc.c  */
#line 4645 "parser.y"
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

  case 859:

/* Line 1455 of yacc.c  */
#line 4673 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 860:

/* Line 1455 of yacc.c  */
#line 4675 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 861:

/* Line 1455 of yacc.c  */
#line 4680 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 862:

/* Line 1455 of yacc.c  */
#line 4684 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]));
	eval_inc2 = 0;
  ;}
    break;

  case 863:

/* Line 1455 of yacc.c  */
#line 4695 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 864:

/* Line 1455 of yacc.c  */
#line 4699 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 865:

/* Line 1455 of yacc.c  */
#line 4703 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), NULL);
	eval_inc2 = 0;
  ;}
    break;

  case 866:

/* Line 1455 of yacc.c  */
#line 4713 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 867:

/* Line 1455 of yacc.c  */
#line 4715 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 868:

/* Line 1455 of yacc.c  */
#line 4719 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 869:

/* Line 1455 of yacc.c  */
#line 4722 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 870:

/* Line 1455 of yacc.c  */
#line 4732 "parser.y"
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

  case 871:

/* Line 1455 of yacc.c  */
#line 4760 "parser.y"
    { (yyval) = cb_any; eval_inc2++; ;}
    break;

  case 872:

/* Line 1455 of yacc.c  */
#line 4761 "parser.y"
    { (yyval) = cb_true; eval_inc2++; ;}
    break;

  case 873:

/* Line 1455 of yacc.c  */
#line 4762 "parser.y"
    { (yyval) = cb_false; eval_inc2++; ;}
    break;

  case 874:

/* Line 1455 of yacc.c  */
#line 4765 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 875:

/* Line 1455 of yacc.c  */
#line 4766 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 876:

/* Line 1455 of yacc.c  */
#line 4770 "parser.y"
    { terminator_warning (TERM_EVALUATE); ;}
    break;

  case 877:

/* Line 1455 of yacc.c  */
#line 4771 "parser.y"
    { terminator_clear (TERM_EVALUATE); ;}
    break;

  case 878:

/* Line 1455 of yacc.c  */
#line 4780 "parser.y"
    { BEGIN_STATEMENT ("EXIT", 0); ;}
    break;

  case 880:

/* Line 1455 of yacc.c  */
#line 4785 "parser.y"
    { /* nothing */ ;}
    break;

  case 881:

/* Line 1455 of yacc.c  */
#line 4787 "parser.y"
    {
	if (in_declaratives && use_global_ind) {
		cb_error (_("EXIT PROGRAM is not allowed within a USE GLOBAL procedure"));
	}
	check_unreached = 1;
	cb_emit_exit (0);
  ;}
    break;

  case 882:

/* Line 1455 of yacc.c  */
#line 4795 "parser.y"
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

  case 883:

/* Line 1455 of yacc.c  */
#line 4812 "parser.y"
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

  case 884:

/* Line 1455 of yacc.c  */
#line 4829 "parser.y"
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

  case 885:

/* Line 1455 of yacc.c  */
#line 4847 "parser.y"
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

  case 886:

/* Line 1455 of yacc.c  */
#line 4871 "parser.y"
    { BEGIN_STATEMENT ("FREE", 0); ;}
    break;

  case 887:

/* Line 1455 of yacc.c  */
#line 4873 "parser.y"
    {
	cb_emit_free ((yyvsp[(3) - (3)]))
  ;}
    break;

  case 888:

/* Line 1455 of yacc.c  */
#line 4884 "parser.y"
    { BEGIN_STATEMENT ("GENERATE", 0); ;}
    break;

  case 889:

/* Line 1455 of yacc.c  */
#line 4886 "parser.y"
    {
	PENDING("GENERATE");
  ;}
    break;

  case 890:

/* Line 1455 of yacc.c  */
#line 4897 "parser.y"
    { BEGIN_STATEMENT ("GO TO", 0); ;}
    break;

  case 891:

/* Line 1455 of yacc.c  */
#line 4899 "parser.y"
    {
	cb_emit_goto ((yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 892:

/* Line 1455 of yacc.c  */
#line 4906 "parser.y"
    {
	check_unreached = 1;
	(yyval) = NULL;
  ;}
    break;

  case 893:

/* Line 1455 of yacc.c  */
#line 4911 "parser.y"
    {
	check_unreached = 0;
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 894:

/* Line 1455 of yacc.c  */
#line 4923 "parser.y"
    { BEGIN_STATEMENT ("GOBACK", 0); ;}
    break;

  case 895:

/* Line 1455 of yacc.c  */
#line 4924 "parser.y"
    {
	check_unreached = 1;
	cb_emit_exit (1);
  ;}
    break;

  case 896:

/* Line 1455 of yacc.c  */
#line 4936 "parser.y"
    { BEGIN_STATEMENT ("IF", TERM_IF); ;}
    break;

  case 897:

/* Line 1455 of yacc.c  */
#line 4938 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 898:

/* Line 1455 of yacc.c  */
#line 4943 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(6) - (8)]) == NULL) {
		cb_error (_("syntax error"));
	}
	cb_emit_if ((yyvsp[(3) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 900:

/* Line 1455 of yacc.c  */
#line 4954 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 901:

/* Line 1455 of yacc.c  */
#line 4958 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 902:

/* Line 1455 of yacc.c  */
#line 4962 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 903:

/* Line 1455 of yacc.c  */
#line 4971 "parser.y"
    { terminator_warning (TERM_IF); ;}
    break;

  case 904:

/* Line 1455 of yacc.c  */
#line 4972 "parser.y"
    { terminator_clear (TERM_IF); ;}
    break;

  case 905:

/* Line 1455 of yacc.c  */
#line 4981 "parser.y"
    { BEGIN_STATEMENT ("INITIALIZE", 0); ;}
    break;

  case 906:

/* Line 1455 of yacc.c  */
#line 4983 "parser.y"
    {
	cb_emit_initialize ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 907:

/* Line 1455 of yacc.c  */
#line 4989 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 908:

/* Line 1455 of yacc.c  */
#line 4990 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 909:

/* Line 1455 of yacc.c  */
#line 4994 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 910:

/* Line 1455 of yacc.c  */
#line 4995 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 911:

/* Line 1455 of yacc.c  */
#line 4996 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 912:

/* Line 1455 of yacc.c  */
#line 5000 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 913:

/* Line 1455 of yacc.c  */
#line 5002 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 914:

/* Line 1455 of yacc.c  */
#line 5006 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 915:

/* Line 1455 of yacc.c  */
#line 5008 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 916:

/* Line 1455 of yacc.c  */
#line 5012 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 917:

/* Line 1455 of yacc.c  */
#line 5016 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHABETIC); ;}
    break;

  case 918:

/* Line 1455 of yacc.c  */
#line 5017 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC); ;}
    break;

  case 919:

/* Line 1455 of yacc.c  */
#line 5018 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC); ;}
    break;

  case 920:

/* Line 1455 of yacc.c  */
#line 5019 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC_EDITED); ;}
    break;

  case 921:

/* Line 1455 of yacc.c  */
#line 5020 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC_EDITED); ;}
    break;

  case 922:

/* Line 1455 of yacc.c  */
#line 5021 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL); ;}
    break;

  case 923:

/* Line 1455 of yacc.c  */
#line 5022 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL_EDITED); ;}
    break;

  case 924:

/* Line 1455 of yacc.c  */
#line 5026 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 925:

/* Line 1455 of yacc.c  */
#line 5027 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 926:

/* Line 1455 of yacc.c  */
#line 5036 "parser.y"
    { BEGIN_STATEMENT ("INITIATE", 0); ;}
    break;

  case 927:

/* Line 1455 of yacc.c  */
#line 5038 "parser.y"
    {
	PENDING("INITIATE");
  ;}
    break;

  case 928:

/* Line 1455 of yacc.c  */
#line 5049 "parser.y"
    {
	BEGIN_STATEMENT ("INSPECT", 0);
	sending_id = 0;
	inspect_keyword = 0;
  ;}
    break;

  case 930:

/* Line 1455 of yacc.c  */
#line 5058 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 0; ;}
    break;

  case 931:

/* Line 1455 of yacc.c  */
#line 5059 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 932:

/* Line 1455 of yacc.c  */
#line 5060 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 935:

/* Line 1455 of yacc.c  */
#line 5069 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 0); ;}
    break;

  case 936:

/* Line 1455 of yacc.c  */
#line 5070 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int1, 1); ;}
    break;

  case 937:

/* Line 1455 of yacc.c  */
#line 5071 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 2); ;}
    break;

  case 938:

/* Line 1455 of yacc.c  */
#line 5077 "parser.y"
    { cb_init_tarrying (); ;}
    break;

  case 939:

/* Line 1455 of yacc.c  */
#line 5078 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 940:

/* Line 1455 of yacc.c  */
#line 5082 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 941:

/* Line 1455 of yacc.c  */
#line 5083 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 942:

/* Line 1455 of yacc.c  */
#line 5087 "parser.y"
    { (yyval) = cb_build_tarrying_data ((yyvsp[(1) - (2)])); ;}
    break;

  case 943:

/* Line 1455 of yacc.c  */
#line 5088 "parser.y"
    { (yyval) = cb_build_tarrying_characters ((yyvsp[(2) - (2)])); ;}
    break;

  case 944:

/* Line 1455 of yacc.c  */
#line 5089 "parser.y"
    { (yyval) = cb_build_tarrying_all (); ;}
    break;

  case 945:

/* Line 1455 of yacc.c  */
#line 5090 "parser.y"
    { (yyval) = cb_build_tarrying_leading (); ;}
    break;

  case 946:

/* Line 1455 of yacc.c  */
#line 5091 "parser.y"
    { (yyval) = cb_build_tarrying_trailing (); ;}
    break;

  case 947:

/* Line 1455 of yacc.c  */
#line 5092 "parser.y"
    { (yyval) = cb_build_tarrying_value ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 948:

/* Line 1455 of yacc.c  */
#line 5098 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); inspect_keyword = 0; ;}
    break;

  case 949:

/* Line 1455 of yacc.c  */
#line 5102 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 950:

/* Line 1455 of yacc.c  */
#line 5103 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 951:

/* Line 1455 of yacc.c  */
#line 5108 "parser.y"
    {
	(yyval) = cb_build_replacing_characters ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]), save_tree_1);
	inspect_keyword = 0;
  ;}
    break;

  case 952:

/* Line 1455 of yacc.c  */
#line 5112 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 953:

/* Line 1455 of yacc.c  */
#line 5116 "parser.y"
    { /* Nothing */ ;}
    break;

  case 954:

/* Line 1455 of yacc.c  */
#line 5117 "parser.y"
    { inspect_keyword = 1; ;}
    break;

  case 955:

/* Line 1455 of yacc.c  */
#line 5118 "parser.y"
    { inspect_keyword = 2; ;}
    break;

  case 956:

/* Line 1455 of yacc.c  */
#line 5119 "parser.y"
    { inspect_keyword = 3; ;}
    break;

  case 957:

/* Line 1455 of yacc.c  */
#line 5120 "parser.y"
    { inspect_keyword = 4; ;}
    break;

  case 958:

/* Line 1455 of yacc.c  */
#line 5125 "parser.y"
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

  case 959:

/* Line 1455 of yacc.c  */
#line 5151 "parser.y"
    {
	if (cb_validate_inspect (save_tree_1, (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])) < 0 ) {
		(yyval) = cb_error_node;
	} else {
		(yyval) = cb_build_converting ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 960:

/* Line 1455 of yacc.c  */
#line 5163 "parser.y"
    { (yyval) = cb_build_inspect_region_start (); ;}
    break;

  case 961:

/* Line 1455 of yacc.c  */
#line 5165 "parser.y"
    { (yyval) = cb_build_inspect_region ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 964:

/* Line 1455 of yacc.c  */
#line 5176 "parser.y"
    { BEGIN_STATEMENT ("MERGE", 0); ;}
    break;

  case 966:

/* Line 1455 of yacc.c  */
#line 5186 "parser.y"
    { BEGIN_STATEMENT ("MOVE", 0); ;}
    break;

  case 968:

/* Line 1455 of yacc.c  */
#line 5192 "parser.y"
    {
	cb_emit_move ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 969:

/* Line 1455 of yacc.c  */
#line 5196 "parser.y"
    {
	cb_emit_move_corresponding ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 970:

/* Line 1455 of yacc.c  */
#line 5207 "parser.y"
    { BEGIN_STATEMENT ("MULTIPLY", TERM_MULTIPLY); ;}
    break;

  case 972:

/* Line 1455 of yacc.c  */
#line 5214 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '*', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 973:

/* Line 1455 of yacc.c  */
#line 5218 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '*', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 974:

/* Line 1455 of yacc.c  */
#line 5224 "parser.y"
    { terminator_warning (TERM_MULTIPLY); ;}
    break;

  case 975:

/* Line 1455 of yacc.c  */
#line 5225 "parser.y"
    { terminator_clear (TERM_MULTIPLY); ;}
    break;

  case 976:

/* Line 1455 of yacc.c  */
#line 5234 "parser.y"
    { BEGIN_STATEMENT ("OPEN", 0); ;}
    break;

  case 979:

/* Line 1455 of yacc.c  */
#line 5241 "parser.y"
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

  case 980:

/* Line 1455 of yacc.c  */
#line 5253 "parser.y"
    { (yyval) = cb_int (COB_OPEN_INPUT); ;}
    break;

  case 981:

/* Line 1455 of yacc.c  */
#line 5254 "parser.y"
    { (yyval) = cb_int (COB_OPEN_OUTPUT); ;}
    break;

  case 982:

/* Line 1455 of yacc.c  */
#line 5255 "parser.y"
    { (yyval) = cb_int (COB_OPEN_I_O); ;}
    break;

  case 983:

/* Line 1455 of yacc.c  */
#line 5256 "parser.y"
    { (yyval) = cb_int (COB_OPEN_EXTEND); ;}
    break;

  case 984:

/* Line 1455 of yacc.c  */
#line 5260 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 985:

/* Line 1455 of yacc.c  */
#line 5261 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 986:

/* Line 1455 of yacc.c  */
#line 5265 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 987:

/* Line 1455 of yacc.c  */
#line 5266 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 988:

/* Line 1455 of yacc.c  */
#line 5267 "parser.y"
    { PENDING ("OPEN ... WITH LOCK"); ;}
    break;

  case 989:

/* Line 1455 of yacc.c  */
#line 5279 "parser.y"
    { BEGIN_STATEMENT ("PERFORM", TERM_PERFORM); ;}
    break;

  case 991:

/* Line 1455 of yacc.c  */
#line 5285 "parser.y"
    {
	cb_emit_perform ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));
  ;}
    break;

  case 992:

/* Line 1455 of yacc.c  */
#line 5289 "parser.y"
    {
	perform_stack = cb_cons ((yyvsp[(1) - (1)]), perform_stack);
	check_unreached = 0;
  ;}
    break;

  case 993:

/* Line 1455 of yacc.c  */
#line 5294 "parser.y"
    {
	perform_stack = CB_CHAIN (perform_stack);
	cb_emit_perform ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 994:

/* Line 1455 of yacc.c  */
#line 5299 "parser.y"
    {
	cb_emit_perform ((yyvsp[(1) - (2)]), NULL);
  ;}
    break;

  case 995:

/* Line 1455 of yacc.c  */
#line 5305 "parser.y"
    { terminator_error (); ;}
    break;

  case 996:

/* Line 1455 of yacc.c  */
#line 5306 "parser.y"
    { terminator_clear (TERM_PERFORM); ;}
    break;

  case 997:

/* Line 1455 of yacc.c  */
#line 5311 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(1) - (1)]))->length = cb_true; /* return from $1 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (1)]), (yyvsp[(1) - (1)]));
  ;}
    break;

  case 998:

/* Line 1455 of yacc.c  */
#line 5316 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(3) - (3)]))->length = cb_true; /* return from $3 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 999:

/* Line 1455 of yacc.c  */
#line 5324 "parser.y"
    {
	(yyval) = cb_build_perform_once (NULL);
  ;}
    break;

  case 1000:

/* Line 1455 of yacc.c  */
#line 5328 "parser.y"
    {
	(yyval) = cb_build_perform_forever (NULL);
  ;}
    break;

  case 1001:

/* Line 1455 of yacc.c  */
#line 5332 "parser.y"
    {
	(yyval) = cb_build_perform_times ((yyvsp[(1) - (2)]));
	current_program->loop_counter++;
  ;}
    break;

  case 1002:

/* Line 1455 of yacc.c  */
#line 5337 "parser.y"
    {
	cb_tree varying;

	varying = cb_list_init (cb_build_perform_varying (NULL, NULL, NULL, (yyvsp[(3) - (3)])));
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), varying);
  ;}
    break;

  case 1003:

/* Line 1455 of yacc.c  */
#line 5344 "parser.y"
    {
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1004:

/* Line 1455 of yacc.c  */
#line 5350 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1005:

/* Line 1455 of yacc.c  */
#line 5351 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1006:

/* Line 1455 of yacc.c  */
#line 5355 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1007:

/* Line 1455 of yacc.c  */
#line 5357 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1008:

/* Line 1455 of yacc.c  */
#line 5362 "parser.y"
    {
	(yyval) = cb_build_perform_varying ((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1009:

/* Line 1455 of yacc.c  */
#line 5373 "parser.y"
    { BEGIN_STATEMENT ("READ", TERM_READ); ;}
    break;

  case 1010:

/* Line 1455 of yacc.c  */
#line 5376 "parser.y"
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

  case 1011:

/* Line 1455 of yacc.c  */
#line 5396 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1012:

/* Line 1455 of yacc.c  */
#line 5397 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1013:

/* Line 1455 of yacc.c  */
#line 5401 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1014:

/* Line 1455 of yacc.c  */
#line 5403 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1015:

/* Line 1455 of yacc.c  */
#line 5407 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1016:

/* Line 1455 of yacc.c  */
#line 5411 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1017:

/* Line 1455 of yacc.c  */
#line 5415 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1018:

/* Line 1455 of yacc.c  */
#line 5419 "parser.y"
    {
	(yyval) = cb_int4;
  ;}
    break;

  case 1019:

/* Line 1455 of yacc.c  */
#line 5425 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1020:

/* Line 1455 of yacc.c  */
#line 5427 "parser.y"
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

  case 1024:

/* Line 1455 of yacc.c  */
#line 5446 "parser.y"
    { terminator_warning (TERM_READ); ;}
    break;

  case 1025:

/* Line 1455 of yacc.c  */
#line 5447 "parser.y"
    { terminator_clear (TERM_READ); ;}
    break;

  case 1026:

/* Line 1455 of yacc.c  */
#line 5456 "parser.y"
    { BEGIN_STATEMENT ("RELEASE", 0); ;}
    break;

  case 1027:

/* Line 1455 of yacc.c  */
#line 5458 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_release ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
	}
  ;}
    break;

  case 1028:

/* Line 1455 of yacc.c  */
#line 5471 "parser.y"
    { BEGIN_STATEMENT ("RETURN", TERM_RETURN); ;}
    break;

  case 1029:

/* Line 1455 of yacc.c  */
#line 5474 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_return ((yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]));
	}
  ;}
    break;

  case 1030:

/* Line 1455 of yacc.c  */
#line 5482 "parser.y"
    { terminator_warning (TERM_RETURN); ;}
    break;

  case 1031:

/* Line 1455 of yacc.c  */
#line 5483 "parser.y"
    { terminator_clear (TERM_RETURN); ;}
    break;

  case 1032:

/* Line 1455 of yacc.c  */
#line 5492 "parser.y"
    { BEGIN_STATEMENT ("REWRITE", TERM_REWRITE); ;}
    break;

  case 1033:

/* Line 1455 of yacc.c  */
#line 5495 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_rewrite ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]));
	}
  ;}
    break;

  case 1034:

/* Line 1455 of yacc.c  */
#line 5503 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1035:

/* Line 1455 of yacc.c  */
#line 5505 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1036:

/* Line 1455 of yacc.c  */
#line 5509 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1037:

/* Line 1455 of yacc.c  */
#line 5515 "parser.y"
    { terminator_warning (TERM_REWRITE); ;}
    break;

  case 1038:

/* Line 1455 of yacc.c  */
#line 5516 "parser.y"
    { terminator_clear (TERM_REWRITE); ;}
    break;

  case 1039:

/* Line 1455 of yacc.c  */
#line 5526 "parser.y"
    {
	BEGIN_STATEMENT ("ROLLBACK", 0);
	cb_emit_rollback ();
  ;}
    break;

  case 1040:

/* Line 1455 of yacc.c  */
#line 5538 "parser.y"
    { BEGIN_STATEMENT ("SEARCH", TERM_SEARCH); ;}
    break;

  case 1042:

/* Line 1455 of yacc.c  */
#line 5545 "parser.y"
    {
	cb_emit_search ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1043:

/* Line 1455 of yacc.c  */
#line 5549 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1044:

/* Line 1455 of yacc.c  */
#line 5553 "parser.y"
    {
	cb_emit_search_all ((yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1045:

/* Line 1455 of yacc.c  */
#line 5559 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1046:

/* Line 1455 of yacc.c  */
#line 5560 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1047:

/* Line 1455 of yacc.c  */
#line 5564 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1048:

/* Line 1455 of yacc.c  */
#line 5566 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1049:

/* Line 1455 of yacc.c  */
#line 5570 "parser.y"
    {
	(yyval) = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 1050:

/* Line 1455 of yacc.c  */
#line 5576 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1051:

/* Line 1455 of yacc.c  */
#line 5577 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); CB_IF ((yyvsp[(1) - (2)]))->stmt2 = (yyvsp[(2) - (2)]); ;}
    break;

  case 1052:

/* Line 1455 of yacc.c  */
#line 5582 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1053:

/* Line 1455 of yacc.c  */
#line 5586 "parser.y"
    {
	(yyval) = cb_build_if ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), NULL);
  ;}
    break;

  case 1054:

/* Line 1455 of yacc.c  */
#line 5592 "parser.y"
    { terminator_warning (TERM_SEARCH); ;}
    break;

  case 1055:

/* Line 1455 of yacc.c  */
#line 5593 "parser.y"
    { terminator_clear (TERM_SEARCH); ;}
    break;

  case 1056:

/* Line 1455 of yacc.c  */
#line 5602 "parser.y"
    { BEGIN_STATEMENT ("SET", 0); ;}
    break;

  case 1063:

/* Line 1455 of yacc.c  */
#line 5618 "parser.y"
    {
	cb_emit_setenv ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1064:

/* Line 1455 of yacc.c  */
#line 5627 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (4)]), cb_build_ppointer ((yyvsp[(4) - (4)])));
  ;}
    break;

  case 1065:

/* Line 1455 of yacc.c  */
#line 5631 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1066:

/* Line 1455 of yacc.c  */
#line 5640 "parser.y"
    {
	cb_emit_set_up_down ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1067:

/* Line 1455 of yacc.c  */
#line 5646 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1068:

/* Line 1455 of yacc.c  */
#line 5647 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1071:

/* Line 1455 of yacc.c  */
#line 5659 "parser.y"
    {
	cb_emit_set_on_off ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1074:

/* Line 1455 of yacc.c  */
#line 5673 "parser.y"
    {
	cb_emit_set_true ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1075:

/* Line 1455 of yacc.c  */
#line 5677 "parser.y"
    {
	cb_emit_set_false ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1076:

/* Line 1455 of yacc.c  */
#line 5688 "parser.y"
    { BEGIN_STATEMENT ("SORT", 0); ;}
    break;

  case 1078:

/* Line 1455 of yacc.c  */
#line 5694 "parser.y"
    {
	cb_emit_sort_init ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (4)]))) && (yyvsp[(2) - (4)]) == NULL) {
		cb_error (_("File sort requires KEY phrase"));
	}
	/* used in sort_input/sort_output */
	save_tree_1 = (yyvsp[(1) - (4)]);
  ;}
    break;

  case 1079:

/* Line 1455 of yacc.c  */
#line 5703 "parser.y"
    {
	cb_emit_sort_finish ((yyvsp[(1) - (7)]));
  ;}
    break;

  case 1080:

/* Line 1455 of yacc.c  */
#line 5710 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 1081:

/* Line 1455 of yacc.c  */
#line 5715 "parser.y"
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

  case 1082:

/* Line 1455 of yacc.c  */
#line 5729 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1083:

/* Line 1455 of yacc.c  */
#line 5730 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1085:

/* Line 1455 of yacc.c  */
#line 5734 "parser.y"
    { /* nothing */ ;}
    break;

  case 1086:

/* Line 1455 of yacc.c  */
#line 5738 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1087:

/* Line 1455 of yacc.c  */
#line 5739 "parser.y"
    { (yyval) = cb_ref ((yyvsp[(3) - (3)])); ;}
    break;

  case 1088:

/* Line 1455 of yacc.c  */
#line 5744 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires USING or INPUT PROCEDURE"));
	}
  ;}
    break;

  case 1089:

/* Line 1455 of yacc.c  */
#line 5750 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("USING invalid with table SORT"));
	} else {
		cb_emit_sort_using (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1090:

/* Line 1455 of yacc.c  */
#line 5758 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("INPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_input ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1091:

/* Line 1455 of yacc.c  */
#line 5769 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires GIVING or OUTPUT PROCEDURE"));
	}
  ;}
    break;

  case 1092:

/* Line 1455 of yacc.c  */
#line 5775 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("GIVING invalid with table SORT"));
	} else {
		cb_emit_sort_giving (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1093:

/* Line 1455 of yacc.c  */
#line 5783 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("OUTPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_output ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1094:

/* Line 1455 of yacc.c  */
#line 5798 "parser.y"
    { BEGIN_STATEMENT ("START", TERM_START); ;}
    break;

  case 1095:

/* Line 1455 of yacc.c  */
#line 5799 "parser.y"
    { (yyval) = cb_int (COB_EQ); ;}
    break;

  case 1096:

/* Line 1455 of yacc.c  */
#line 5802 "parser.y"
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

  case 1097:

/* Line 1455 of yacc.c  */
#line 5819 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1098:

/* Line 1455 of yacc.c  */
#line 5821 "parser.y"
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

  case 1099:

/* Line 1455 of yacc.c  */
#line 5836 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_NE : COB_EQ); ;}
    break;

  case 1100:

/* Line 1455 of yacc.c  */
#line 5837 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LE : COB_GT); ;}
    break;

  case 1101:

/* Line 1455 of yacc.c  */
#line 5838 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GE : COB_LT); ;}
    break;

  case 1102:

/* Line 1455 of yacc.c  */
#line 5839 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LT : COB_GE); ;}
    break;

  case 1103:

/* Line 1455 of yacc.c  */
#line 5840 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GT : COB_LE); ;}
    break;

  case 1104:

/* Line 1455 of yacc.c  */
#line 5844 "parser.y"
    { terminator_warning (TERM_START); ;}
    break;

  case 1105:

/* Line 1455 of yacc.c  */
#line 5845 "parser.y"
    { terminator_clear (TERM_START); ;}
    break;

  case 1106:

/* Line 1455 of yacc.c  */
#line 5854 "parser.y"
    { BEGIN_STATEMENT ("STOP", 0); ;}
    break;

  case 1107:

/* Line 1455 of yacc.c  */
#line 5856 "parser.y"
    {
	cb_emit_stop_run ((yyvsp[(4) - (4)]));
  ;}
    break;

  case 1108:

/* Line 1455 of yacc.c  */
#line 5860 "parser.y"
    {
	cb_verify (cb_stop_literal_statement, "STOP literal");
  ;}
    break;

  case 1109:

/* Line 1455 of yacc.c  */
#line 5866 "parser.y"
    { (yyval) = current_program->cb_return_code; ;}
    break;

  case 1110:

/* Line 1455 of yacc.c  */
#line 5867 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1111:

/* Line 1455 of yacc.c  */
#line 5868 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1112:

/* Line 1455 of yacc.c  */
#line 5877 "parser.y"
    { BEGIN_STATEMENT ("STRING", TERM_STRING); ;}
    break;

  case 1113:

/* Line 1455 of yacc.c  */
#line 5880 "parser.y"
    {
	cb_emit_string ((yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]));
  ;}
    break;

  case 1114:

/* Line 1455 of yacc.c  */
#line 5886 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1115:

/* Line 1455 of yacc.c  */
#line 5887 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1116:

/* Line 1455 of yacc.c  */
#line 5891 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1117:

/* Line 1455 of yacc.c  */
#line 5892 "parser.y"
    { (yyval) = cb_build_pair (cb_int0, NULL); ;}
    break;

  case 1118:

/* Line 1455 of yacc.c  */
#line 5893 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), NULL); ;}
    break;

  case 1119:

/* Line 1455 of yacc.c  */
#line 5897 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1120:

/* Line 1455 of yacc.c  */
#line 5898 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1121:

/* Line 1455 of yacc.c  */
#line 5902 "parser.y"
    { terminator_warning (TERM_STRING); ;}
    break;

  case 1122:

/* Line 1455 of yacc.c  */
#line 5903 "parser.y"
    { terminator_clear (TERM_STRING); ;}
    break;

  case 1123:

/* Line 1455 of yacc.c  */
#line 5912 "parser.y"
    { BEGIN_STATEMENT ("SUBTRACT", TERM_SUBTRACT); ;}
    break;

  case 1125:

/* Line 1455 of yacc.c  */
#line 5919 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '-', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 1126:

/* Line 1455 of yacc.c  */
#line 5923 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_list (cb_cons ((yyvsp[(3) - (6)]), (yyvsp[(1) - (6)])), '-'));
  ;}
    break;

  case 1127:

/* Line 1455 of yacc.c  */
#line 5927 "parser.y"
    {
	cb_emit_corresponding (cb_build_sub, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 1128:

/* Line 1455 of yacc.c  */
#line 5933 "parser.y"
    { terminator_warning (TERM_SUBTRACT); ;}
    break;

  case 1129:

/* Line 1455 of yacc.c  */
#line 5934 "parser.y"
    { terminator_clear (TERM_SUBTRACT); ;}
    break;

  case 1130:

/* Line 1455 of yacc.c  */
#line 5944 "parser.y"
    {
	BEGIN_STATEMENT ("SUPPRESS", 0);
	PENDING("SUPPRESS");
  ;}
    break;

  case 1133:

/* Line 1455 of yacc.c  */
#line 5959 "parser.y"
    { BEGIN_STATEMENT ("TERMINATE", 0); ;}
    break;

  case 1134:

/* Line 1455 of yacc.c  */
#line 5961 "parser.y"
    {
	PENDING("TERMINATE");
  ;}
    break;

  case 1135:

/* Line 1455 of yacc.c  */
#line 5972 "parser.y"
    { BEGIN_STATEMENT ("TRANSFORM", 0); ;}
    break;

  case 1136:

/* Line 1455 of yacc.c  */
#line 5974 "parser.y"
    {
	cb_tree		x;

	x = cb_build_converting ((yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]), cb_build_inspect_region_start ());
	cb_emit_inspect ((yyvsp[(3) - (7)]), x, cb_int0, 2);
  ;}
    break;

  case 1137:

/* Line 1455 of yacc.c  */
#line 5988 "parser.y"
    { BEGIN_STATEMENT ("UNLOCK", 0); ;}
    break;

  case 1138:

/* Line 1455 of yacc.c  */
#line 5990 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_unlock ((yyvsp[(3) - (4)]));
	}
  ;}
    break;

  case 1142:

/* Line 1455 of yacc.c  */
#line 6009 "parser.y"
    { BEGIN_STATEMENT ("UNSTRING", TERM_UNSTRING); ;}
    break;

  case 1143:

/* Line 1455 of yacc.c  */
#line 6013 "parser.y"
    {
	cb_emit_unstring ((yyvsp[(3) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]));
  ;}
    break;

  case 1144:

/* Line 1455 of yacc.c  */
#line 6019 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1145:

/* Line 1455 of yacc.c  */
#line 6021 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1146:

/* Line 1455 of yacc.c  */
#line 6025 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1147:

/* Line 1455 of yacc.c  */
#line 6027 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1148:

/* Line 1455 of yacc.c  */
#line 6032 "parser.y"
    {
	(yyval) = cb_build_unstring_delimited ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1149:

/* Line 1455 of yacc.c  */
#line 6038 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 1150:

/* Line 1455 of yacc.c  */
#line 6040 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1151:

/* Line 1455 of yacc.c  */
#line 6045 "parser.y"
    {
	(yyval) = cb_build_unstring_into ((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1152:

/* Line 1455 of yacc.c  */
#line 6051 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1153:

/* Line 1455 of yacc.c  */
#line 6052 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1154:

/* Line 1455 of yacc.c  */
#line 6056 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1155:

/* Line 1455 of yacc.c  */
#line 6057 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1156:

/* Line 1455 of yacc.c  */
#line 6061 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1157:

/* Line 1455 of yacc.c  */
#line 6062 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1158:

/* Line 1455 of yacc.c  */
#line 6066 "parser.y"
    { terminator_warning (TERM_UNSTRING); ;}
    break;

  case 1159:

/* Line 1455 of yacc.c  */
#line 6067 "parser.y"
    { terminator_clear (TERM_UNSTRING); ;}
    break;

  case 1163:

/* Line 1455 of yacc.c  */
#line 6085 "parser.y"
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

  case 1164:

/* Line 1455 of yacc.c  */
#line 6106 "parser.y"
    {
	use_global_ind = 0;
  ;}
    break;

  case 1165:

/* Line 1455 of yacc.c  */
#line 6110 "parser.y"
    {
	use_global_ind = 1;
	current_program->flag_global_use = 1;
  ;}
    break;

  case 1166:

/* Line 1455 of yacc.c  */
#line 6118 "parser.y"
    {
	cb_tree		l;

	for (l = (yyvsp[(1) - (1)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			setup_use_file (CB_FILE (cb_ref (CB_VALUE (l))));
		}
	}
  ;}
    break;

  case 1167:

/* Line 1455 of yacc.c  */
#line 6128 "parser.y"
    {
	current_program->global_handler[COB_OPEN_INPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_INPUT].handler_prog = current_program;
  ;}
    break;

  case 1168:

/* Line 1455 of yacc.c  */
#line 6133 "parser.y"
    {
	current_program->global_handler[COB_OPEN_OUTPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_OUTPUT].handler_prog = current_program;
  ;}
    break;

  case 1169:

/* Line 1455 of yacc.c  */
#line 6138 "parser.y"
    {
	current_program->global_handler[COB_OPEN_I_O].handler_label = current_section;
	current_program->global_handler[COB_OPEN_I_O].handler_prog = current_program;
  ;}
    break;

  case 1170:

/* Line 1455 of yacc.c  */
#line 6143 "parser.y"
    {
	current_program->global_handler[COB_OPEN_EXTEND].handler_label = current_section;
	current_program->global_handler[COB_OPEN_EXTEND].handler_prog = current_program;
  ;}
    break;

  case 1183:

/* Line 1455 of yacc.c  */
#line 6175 "parser.y"
    {
	PENDING ("USE FOR DEBUGGING");
  ;}
    break;

  case 1186:

/* Line 1455 of yacc.c  */
#line 6187 "parser.y"
    {
	PENDING ("USE BEFORE REPORTING");
  ;}
    break;

  case 1187:

/* Line 1455 of yacc.c  */
#line 6198 "parser.y"
    { BEGIN_STATEMENT ("WRITE", TERM_WRITE); ;}
    break;

  case 1188:

/* Line 1455 of yacc.c  */
#line 6201 "parser.y"
    {
	if ((yyvsp[(3) - (8)]) != cb_error_node) {
		cb_emit_write ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(5) - (8)]));
	}
  ;}
    break;

  case 1189:

/* Line 1455 of yacc.c  */
#line 6209 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1190:

/* Line 1455 of yacc.c  */
#line 6210 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1191:

/* Line 1455 of yacc.c  */
#line 6215 "parser.y"
    {
	(yyval) = cb_int0;
  ;}
    break;

  case 1192:

/* Line 1455 of yacc.c  */
#line 6219 "parser.y"
    {
	(yyval) = cb_build_write_advancing_lines ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 1193:

/* Line 1455 of yacc.c  */
#line 6223 "parser.y"
    {
	(yyval) = cb_build_write_advancing_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1194:

/* Line 1455 of yacc.c  */
#line 6227 "parser.y"
    {
	(yyval) = cb_build_write_advancing_page ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1195:

/* Line 1455 of yacc.c  */
#line 6233 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1196:

/* Line 1455 of yacc.c  */
#line 6234 "parser.y"
    { (yyval) = CB_AFTER; ;}
    break;

  case 1200:

/* Line 1455 of yacc.c  */
#line 6243 "parser.y"
    { terminator_warning (TERM_WRITE); ;}
    break;

  case 1201:

/* Line 1455 of yacc.c  */
#line 6244 "parser.y"
    { terminator_clear (TERM_WRITE); ;}
    break;

  case 1202:

/* Line 1455 of yacc.c  */
#line 6259 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_ACCEPT;
  ;}
    break;

  case 1203:

/* Line 1455 of yacc.c  */
#line 6267 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_DISPLAY;
  ;}
    break;

  case 1205:

/* Line 1455 of yacc.c  */
#line 6274 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1206:

/* Line 1455 of yacc.c  */
#line 6278 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1208:

/* Line 1455 of yacc.c  */
#line 6285 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1209:

/* Line 1455 of yacc.c  */
#line 6289 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1212:

/* Line 1455 of yacc.c  */
#line 6305 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1213:

/* Line 1455 of yacc.c  */
#line 6310 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1215:

/* Line 1455 of yacc.c  */
#line 6317 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1216:

/* Line 1455 of yacc.c  */
#line 6322 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1217:

/* Line 1455 of yacc.c  */
#line 6334 "parser.y"
    {
	current_statement->handler_id = COB_EC_OVERFLOW;
  ;}
    break;

  case 1219:

/* Line 1455 of yacc.c  */
#line 6341 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1220:

/* Line 1455 of yacc.c  */
#line 6345 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1222:

/* Line 1455 of yacc.c  */
#line 6352 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1223:

/* Line 1455 of yacc.c  */
#line 6356 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1224:

/* Line 1455 of yacc.c  */
#line 6368 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1225:

/* Line 1455 of yacc.c  */
#line 6373 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1226:

/* Line 1455 of yacc.c  */
#line 6378 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1227:

/* Line 1455 of yacc.c  */
#line 6387 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1228:

/* Line 1455 of yacc.c  */
#line 6391 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1229:

/* Line 1455 of yacc.c  */
#line 6398 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1230:

/* Line 1455 of yacc.c  */
#line 6402 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1231:

/* Line 1455 of yacc.c  */
#line 6414 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1232:

/* Line 1455 of yacc.c  */
#line 6419 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1233:

/* Line 1455 of yacc.c  */
#line 6424 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1234:

/* Line 1455 of yacc.c  */
#line 6433 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1235:

/* Line 1455 of yacc.c  */
#line 6437 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1236:

/* Line 1455 of yacc.c  */
#line 6444 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1237:

/* Line 1455 of yacc.c  */
#line 6448 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1240:

/* Line 1455 of yacc.c  */
#line 6464 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1241:

/* Line 1455 of yacc.c  */
#line 6469 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1242:

/* Line 1455 of yacc.c  */
#line 6474 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1243:

/* Line 1455 of yacc.c  */
#line 6483 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1244:

/* Line 1455 of yacc.c  */
#line 6487 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1245:

/* Line 1455 of yacc.c  */
#line 6494 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1246:

/* Line 1455 of yacc.c  */
#line 6498 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1247:

/* Line 1455 of yacc.c  */
#line 6510 "parser.y"
    {
	(yyval) = cb_one;
  ;}
    break;

  case 1248:

/* Line 1455 of yacc.c  */
#line 6514 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 1249:

/* Line 1455 of yacc.c  */
#line 6526 "parser.y"
    {
	(yyval) = cb_build_cond ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1250:

/* Line 1455 of yacc.c  */
#line 6533 "parser.y"
    {
	(yyval) = cb_build_expr ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1251:

/* Line 1455 of yacc.c  */
#line 6539 "parser.y"
    {
	current_expr = NULL;
  ;}
    break;

  case 1252:

/* Line 1455 of yacc.c  */
#line 6543 "parser.y"
    {
	(yyval) = cb_list_reverse (current_expr);
  ;}
    break;

  case 1254:

/* Line 1455 of yacc.c  */
#line 6550 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1255:

/* Line 1455 of yacc.c  */
#line 6551 "parser.y"
    { push_expr (')', NULL); ;}
    break;

  case 1256:

/* Line 1455 of yacc.c  */
#line 6553 "parser.y"
    { push_expr ('O', NULL); ;}
    break;

  case 1257:

/* Line 1455 of yacc.c  */
#line 6554 "parser.y"
    { push_expr ('9', NULL); ;}
    break;

  case 1258:

/* Line 1455 of yacc.c  */
#line 6555 "parser.y"
    { push_expr ('A', NULL); ;}
    break;

  case 1259:

/* Line 1455 of yacc.c  */
#line 6556 "parser.y"
    { push_expr ('L', NULL); ;}
    break;

  case 1260:

/* Line 1455 of yacc.c  */
#line 6557 "parser.y"
    { push_expr ('U', NULL); ;}
    break;

  case 1261:

/* Line 1455 of yacc.c  */
#line 6558 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1262:

/* Line 1455 of yacc.c  */
#line 6560 "parser.y"
    { push_expr ('P', NULL); ;}
    break;

  case 1263:

/* Line 1455 of yacc.c  */
#line 6561 "parser.y"
    { push_expr ('N', NULL); ;}
    break;

  case 1264:

/* Line 1455 of yacc.c  */
#line 6562 "parser.y"
    { push_expr ('x', cb_zero); ;}
    break;

  case 1265:

/* Line 1455 of yacc.c  */
#line 6564 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1268:

/* Line 1455 of yacc.c  */
#line 6570 "parser.y"
    { push_expr ('(', NULL); ;}
    break;

  case 1269:

/* Line 1455 of yacc.c  */
#line 6572 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1270:

/* Line 1455 of yacc.c  */
#line 6573 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1271:

/* Line 1455 of yacc.c  */
#line 6574 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1272:

/* Line 1455 of yacc.c  */
#line 6576 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1273:

/* Line 1455 of yacc.c  */
#line 6578 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1274:

/* Line 1455 of yacc.c  */
#line 6579 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1275:

/* Line 1455 of yacc.c  */
#line 6580 "parser.y"
    { push_expr ('*', NULL); ;}
    break;

  case 1276:

/* Line 1455 of yacc.c  */
#line 6581 "parser.y"
    { push_expr ('/', NULL); ;}
    break;

  case 1277:

/* Line 1455 of yacc.c  */
#line 6582 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1278:

/* Line 1455 of yacc.c  */
#line 6584 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1279:

/* Line 1455 of yacc.c  */
#line 6585 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1280:

/* Line 1455 of yacc.c  */
#line 6586 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1281:

/* Line 1455 of yacc.c  */
#line 6587 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1282:

/* Line 1455 of yacc.c  */
#line 6588 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1283:

/* Line 1455 of yacc.c  */
#line 6589 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1284:

/* Line 1455 of yacc.c  */
#line 6591 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1285:

/* Line 1455 of yacc.c  */
#line 6592 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1286:

/* Line 1455 of yacc.c  */
#line 6593 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1287:

/* Line 1455 of yacc.c  */
#line 6594 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1288:

/* Line 1455 of yacc.c  */
#line 6595 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1289:

/* Line 1455 of yacc.c  */
#line 6596 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1290:

/* Line 1455 of yacc.c  */
#line 6598 "parser.y"
    { push_expr ('&', NULL); ;}
    break;

  case 1291:

/* Line 1455 of yacc.c  */
#line 6599 "parser.y"
    { push_expr ('|', NULL); ;}
    break;

  case 1303:

/* Line 1455 of yacc.c  */
#line 6611 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1304:

/* Line 1455 of yacc.c  */
#line 6612 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1308:

/* Line 1455 of yacc.c  */
#line 6621 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1309:

/* Line 1455 of yacc.c  */
#line 6622 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '+', (yyvsp[(3) - (3)])); ;}
    break;

  case 1310:

/* Line 1455 of yacc.c  */
#line 6623 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '-', (yyvsp[(3) - (3)])); ;}
    break;

  case 1311:

/* Line 1455 of yacc.c  */
#line 6624 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '*', (yyvsp[(3) - (3)])); ;}
    break;

  case 1312:

/* Line 1455 of yacc.c  */
#line 6625 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '/', (yyvsp[(3) - (3)])); ;}
    break;

  case 1313:

/* Line 1455 of yacc.c  */
#line 6626 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1314:

/* Line 1455 of yacc.c  */
#line 6627 "parser.y"
    { (yyval) = cb_build_binary_op (cb_zero, '-', (yyvsp[(2) - (2)])); ;}
    break;

  case 1315:

/* Line 1455 of yacc.c  */
#line 6628 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '^', (yyvsp[(3) - (3)])); ;}
    break;

  case 1316:

/* Line 1455 of yacc.c  */
#line 6629 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1317:

/* Line 1455 of yacc.c  */
#line 6641 "parser.y"
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

  case 1318:

/* Line 1455 of yacc.c  */
#line 6653 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(3) - (3)])))) {
		(yyval) = CB_FILE (cb_ref ((yyvsp[(3) - (3)])))->linage_ctr;
	} else {
		cb_error_x ((yyvsp[(3) - (3)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(3) - (3)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1319:

/* Line 1455 of yacc.c  */
#line 6667 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1320:

/* Line 1455 of yacc.c  */
#line 6669 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1321:

/* Line 1455 of yacc.c  */
#line 6673 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)])); ;}
    break;

  case 1322:

/* Line 1455 of yacc.c  */
#line 6679 "parser.y"
    { cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1323:

/* Line 1455 of yacc.c  */
#line 6686 "parser.y"
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

  case 1324:

/* Line 1455 of yacc.c  */
#line 6706 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1325:

/* Line 1455 of yacc.c  */
#line 6710 "parser.y"
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

  case 1326:

/* Line 1455 of yacc.c  */
#line 6726 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (1)])))) {
		(yyval) = (yyvsp[(1) - (1)]);
	} else {
		cb_error_x ((yyvsp[(1) - (1)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(1) - (1)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1327:

/* Line 1455 of yacc.c  */
#line 6739 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1328:

/* Line 1455 of yacc.c  */
#line 6741 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1329:

/* Line 1455 of yacc.c  */
#line 6745 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1330:

/* Line 1455 of yacc.c  */
#line 6751 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1331:

/* Line 1455 of yacc.c  */
#line 6753 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1332:

/* Line 1455 of yacc.c  */
#line 6758 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	CB_REFERENCE ((yyval))->offset = CB_TREE (current_section);
	current_program->label_list = cb_cons ((yyval), current_program->label_list);
  ;}
    break;

  case 1336:

/* Line 1455 of yacc.c  */
#line 6773 "parser.y"
    {
	(yyval) = cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(1) - (1)]))->data));
	(yyval)->source_file = (yyvsp[(1) - (1)])->source_file;
	(yyval)->source_line = (yyvsp[(1) - (1)])->source_line;
  ;}
    break;

  case 1337:

/* Line 1455 of yacc.c  */
#line 6783 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1338:

/* Line 1455 of yacc.c  */
#line 6784 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1339:

/* Line 1455 of yacc.c  */
#line 6789 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	current_program->reference_list = cb_cons ((yyval), current_program->reference_list);
  ;}
    break;

  case 1340:

/* Line 1455 of yacc.c  */
#line 6796 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1341:

/* Line 1455 of yacc.c  */
#line 6797 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1344:

/* Line 1455 of yacc.c  */
#line 6809 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE ((yyval))->word->count > 0) {
		redefinition_error ((yyval));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1345:

/* Line 1455 of yacc.c  */
#line 6828 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1346:

/* Line 1455 of yacc.c  */
#line 6829 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1348:

/* Line 1455 of yacc.c  */
#line 6834 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
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
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1353:

/* Line 1455 of yacc.c  */
#line 6845 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1354:

/* Line 1455 of yacc.c  */
#line 6846 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1355:

/* Line 1455 of yacc.c  */
#line 6847 "parser.y"
    { (yyval) = cb_build_ppointer ((yyvsp[(4) - (4)])); ;}
    break;

  case 1356:

/* Line 1455 of yacc.c  */
#line 6848 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1361:

/* Line 1455 of yacc.c  */
#line 6856 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1362:

/* Line 1455 of yacc.c  */
#line 6857 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1363:

/* Line 1455 of yacc.c  */
#line 6858 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1369:

/* Line 1455 of yacc.c  */
#line 6870 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1370:

/* Line 1455 of yacc.c  */
#line 6871 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1382:

/* Line 1455 of yacc.c  */
#line 6905 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1383:

/* Line 1455 of yacc.c  */
#line 6913 "parser.y"
    { (yyval) = cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1384:

/* Line 1455 of yacc.c  */
#line 6917 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1385:

/* Line 1455 of yacc.c  */
#line 6918 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1386:

/* Line 1455 of yacc.c  */
#line 6919 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1387:

/* Line 1455 of yacc.c  */
#line 6920 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 1388:

/* Line 1455 of yacc.c  */
#line 6924 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1389:

/* Line 1455 of yacc.c  */
#line 6925 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); CB_REFERENCE ((yyvsp[(1) - (3)]))->chain = (yyvsp[(3) - (3)]); ;}
    break;

  case 1390:

/* Line 1455 of yacc.c  */
#line 6930 "parser.y"
    {
	if (cb_ref ((yyvsp[(0) - (3)])) != cb_error_node) {
		(yyval) = (yyvsp[(0) - (3)]);
		CB_REFERENCE ((yyvsp[(0) - (3)]))->subs = cb_list_reverse ((yyvsp[(2) - (3)]));
	}
  ;}
    break;

  case 1391:

/* Line 1455 of yacc.c  */
#line 6940 "parser.y"
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

  case 1392:

/* Line 1455 of yacc.c  */
#line 6958 "parser.y"
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

  case 1393:

/* Line 1455 of yacc.c  */
#line 6985 "parser.y"
    {
	if (cb_tree_category ((yyvsp[(1) - (1)])) != CB_CATEGORY_NUMERIC) {
		cb_error (_("Integer value expected"));
	} else if (CB_LITERAL ((yyvsp[(1) - (1)]))->sign < 0 || CB_LITERAL ((yyvsp[(1) - (1)]))->scale) {
		cb_error (_("Integer value expected"));
	}
	(yyval) = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1394:

/* Line 1455 of yacc.c  */
#line 6996 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1395:

/* Line 1455 of yacc.c  */
#line 6998 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (2)]);
	if (CB_LITERAL_P ((yyvsp[(2) - (2)]))) {
		CB_LITERAL ((yyvsp[(2) - (2)]))->all = 1;
	}
  ;}
    break;

  case 1396:

/* Line 1455 of yacc.c  */
#line 7007 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1397:

/* Line 1455 of yacc.c  */
#line 7008 "parser.y"
    { (yyval) = cb_concat_literals ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1398:

/* Line 1455 of yacc.c  */
#line 7012 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1399:

/* Line 1455 of yacc.c  */
#line 7013 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 1400:

/* Line 1455 of yacc.c  */
#line 7014 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1401:

/* Line 1455 of yacc.c  */
#line 7015 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 1402:

/* Line 1455 of yacc.c  */
#line 7016 "parser.y"
    { (yyval) = cb_high; ;}
    break;

  case 1403:

/* Line 1455 of yacc.c  */
#line 7017 "parser.y"
    { (yyval) = cb_low; ;}
    break;

  case 1404:

/* Line 1455 of yacc.c  */
#line 7018 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1405:

/* Line 1455 of yacc.c  */
#line 7027 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1406:

/* Line 1455 of yacc.c  */
#line 7031 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1407:

/* Line 1455 of yacc.c  */
#line 7035 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1408:

/* Line 1455 of yacc.c  */
#line 7039 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1409:

/* Line 1455 of yacc.c  */
#line 7043 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1410:

/* Line 1455 of yacc.c  */
#line 7047 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1411:

/* Line 1455 of yacc.c  */
#line 7051 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1412:

/* Line 1455 of yacc.c  */
#line 7055 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1413:

/* Line 1455 of yacc.c  */
#line 7059 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1414:

/* Line 1455 of yacc.c  */
#line 7063 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), NULL);
  ;}
    break;

  case 1415:

/* Line 1455 of yacc.c  */
#line 7067 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1416:

/* Line 1455 of yacc.c  */
#line 7071 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), NULL);
  ;}
    break;

  case 1417:

/* Line 1455 of yacc.c  */
#line 7077 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1418:

/* Line 1455 of yacc.c  */
#line 7078 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (4)]), NULL); ;}
    break;

  case 1419:

/* Line 1455 of yacc.c  */
#line 7079 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 1420:

/* Line 1455 of yacc.c  */
#line 7083 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1421:

/* Line 1455 of yacc.c  */
#line 7084 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1422:

/* Line 1455 of yacc.c  */
#line 7088 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1423:

/* Line 1455 of yacc.c  */
#line 7089 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1424:

/* Line 1455 of yacc.c  */
#line 7095 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_int0);
  ;}
    break;

  case 1425:

/* Line 1455 of yacc.c  */
#line 7102 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int1);
  ;}
    break;

  case 1426:

/* Line 1455 of yacc.c  */
#line 7109 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int2);
  ;}
    break;

  case 1427:

/* Line 1455 of yacc.c  */
#line 7119 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1428:

/* Line 1455 of yacc.c  */
#line 7126 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1429:

/* Line 1455 of yacc.c  */
#line 7136 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1430:

/* Line 1455 of yacc.c  */
#line 7143 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_ref ((yyvsp[(3) - (3)])));
  ;}
    break;

  case 1431:

/* Line 1455 of yacc.c  */
#line 7156 "parser.y"
    {
	non_const_word = 1;
  ;}
    break;

  case 1432:

/* Line 1455 of yacc.c  */
#line 7166 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1433:

/* Line 1455 of yacc.c  */
#line 7167 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1434:

/* Line 1455 of yacc.c  */
#line 7171 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1435:

/* Line 1455 of yacc.c  */
#line 7172 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1436:

/* Line 1455 of yacc.c  */
#line 7176 "parser.y"
    { (yyval) = NULL; ;}
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
#line 7183 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 1441:

/* Line 1455 of yacc.c  */
#line 7187 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1442:

/* Line 1455 of yacc.c  */
#line 7188 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1443:

/* Line 1455 of yacc.c  */
#line 7192 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1444:

/* Line 1455 of yacc.c  */
#line 7193 "parser.y"
    { (yyval) = cb_int1; ;}
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

  case 1460:

/* Line 1455 of yacc.c  */
#line 7216 "parser.y"
    { (yyval) = cb_int1; ;}
    break;



/* Line 1455 of yacc.c  */
#line 14388 "parser.c"
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
#line 7260 "parser.y"


