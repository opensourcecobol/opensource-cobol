/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

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

/* Line 268 of yacc.c  */
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



/* Line 268 of yacc.c  */
#line 354 "parser.c"

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
     CLOSE = 312,
     CODE = 313,
     CODE_SET = 314,
     COLLATING = 315,
     COL = 316,
     COLS = 317,
     COLUMN = 318,
     COLUMNS = 319,
     COMMA = 320,
     COMMAND_LINE = 321,
     COMMA_DELIM = 322,
     COMMIT = 323,
     COMMON = 324,
     COMP = 325,
     COMPUTE = 326,
     COMP_1 = 327,
     COMP_2 = 328,
     COMP_3 = 329,
     COMP_4 = 330,
     COMP_5 = 331,
     COMP_X = 332,
     CONCATENATE_FUNC = 333,
     CONFIGURATION = 334,
     CONSTANT = 335,
     CONTAINS = 336,
     CONTENT = 337,
     CONTINUE = 338,
     CONTROL = 339,
     CONTROLS = 340,
     CONTROL_FOOTING = 341,
     CONTROL_HEADING = 342,
     CONVERTING = 343,
     CORRESPONDING = 344,
     COUNT = 345,
     CRT = 346,
     CURRENCY = 347,
     CURRENT_DATE_FUNC = 348,
     CURSOR = 349,
     CYCLE = 350,
     DATA = 351,
     DATE = 352,
     DAY = 353,
     DAY_OF_WEEK = 354,
     DE = 355,
     DEBUGGING = 356,
     DECIMAL_POINT = 357,
     DECLARATIVES = 358,
     DEFAULT = 359,
     DELETE = 360,
     DELIMITED = 361,
     DELIMITER = 362,
     DEPENDING = 363,
     DESCENDING = 364,
     DETAIL = 365,
     DISK = 366,
     DISPLAY = 367,
     DIVIDE = 368,
     DIVISION = 369,
     DOWN = 370,
     DUPLICATES = 371,
     DYNAMIC = 372,
     EBCDIC = 373,
     ELSE = 374,
     END = 375,
     END_ACCEPT = 376,
     END_ADD = 377,
     END_CALL = 378,
     END_COMPUTE = 379,
     END_DELETE = 380,
     END_DISPLAY = 381,
     END_DIVIDE = 382,
     END_EVALUATE = 383,
     END_FUNCTION = 384,
     END_IF = 385,
     END_MULTIPLY = 386,
     END_PERFORM = 387,
     END_PROGRAM = 388,
     END_READ = 389,
     END_RETURN = 390,
     END_REWRITE = 391,
     END_SEARCH = 392,
     END_START = 393,
     END_STRING = 394,
     END_SUBTRACT = 395,
     END_UNSTRING = 396,
     END_WRITE = 397,
     ENTRY = 398,
     ENVIRONMENT = 399,
     ENVIRONMENT_NAME = 400,
     ENVIRONMENT_VALUE = 401,
     EOL = 402,
     EOP = 403,
     EOS = 404,
     EQUAL = 405,
     EQUALS = 406,
     ERASE = 407,
     ERROR = 408,
     ESCAPE = 409,
     EVALUATE = 410,
     EVENT_STATUS = 411,
     EXCEPTION = 412,
     EXCLUSIVE = 413,
     EXIT = 414,
     EXTEND = 415,
     EXTERNAL = 416,
     FD = 417,
     FILE_CONTROL = 418,
     FILE_ID = 419,
     FILLER = 420,
     FINAL = 421,
     FIRST = 422,
     FOOTING = 423,
     FOR = 424,
     FOREGROUND_COLOR = 425,
     FOREVER = 426,
     FREE = 427,
     FROM = 428,
     FULL = 429,
     FUNCTION = 430,
     FUNCTION_ID = 431,
     FUNCTION_NAME = 432,
     GE = 433,
     GENERATE = 434,
     GIVING = 435,
     GLOBAL = 436,
     GO = 437,
     GOBACK = 438,
     GREATER = 439,
     GROUP = 440,
     HEADING = 441,
     HIGHLIGHT = 442,
     HIGH_VALUE = 443,
     IDENTIFICATION = 444,
     IF = 445,
     IGNORE = 446,
     IGNORING = 447,
     IN = 448,
     INDEX = 449,
     INDEXED = 450,
     INDICATE = 451,
     INITIALIZE = 452,
     INITIALIZED = 453,
     INITIATE = 454,
     INPUT = 455,
     INPUT_OUTPUT = 456,
     INSPECT = 457,
     INTO = 458,
     INTRINSIC = 459,
     INVALID = 460,
     INVALID_KEY = 461,
     IS = 462,
     I_O = 463,
     I_O_CONTROL = 464,
     JUSTIFIED = 465,
     KEY = 466,
     LABEL = 467,
     LAST = 468,
     LAST_DETAIL = 469,
     LE = 470,
     LEADING = 471,
     LEFT = 472,
     LENGTH = 473,
     LESS = 474,
     LIMIT = 475,
     LIMITS = 476,
     LINAGE = 477,
     LINAGE_COUNTER = 478,
     LINE = 479,
     LINES = 480,
     LINKAGE = 481,
     LITERAL = 482,
     LOCALE = 483,
     LOCALE_DT_FUNC = 484,
     LOCAL_STORAGE = 485,
     LOCK = 486,
     LOWER_CASE_FUNC = 487,
     LOWLIGHT = 488,
     LOW_VALUE = 489,
     MANUAL = 490,
     MEMORY = 491,
     MERGE = 492,
     MINUS = 493,
     MNEMONIC_NAME = 494,
     MODE = 495,
     MOVE = 496,
     MULTIPLE = 497,
     MULTIPLY = 498,
     NATIONAL = 499,
     NATIONAL_EDITED = 500,
     NATIVE = 501,
     NE = 502,
     NEGATIVE = 503,
     NEXT = 504,
     NEXT_SENTENCE = 505,
     NO = 506,
     NOT = 507,
     NOT_END = 508,
     NOT_EOP = 509,
     NOT_EXCEPTION = 510,
     NOT_INVALID_KEY = 511,
     NOT_OVERFLOW = 512,
     NOT_SIZE_ERROR = 513,
     NO_ADVANCING = 514,
     NUMBER = 515,
     NUMBERS = 516,
     NUMERIC = 517,
     NUMERIC_EDITED = 518,
     NUMVALC_FUNC = 519,
     OBJECT_COMPUTER = 520,
     OCCURS = 521,
     OF = 522,
     OFF = 523,
     OMITTED = 524,
     ON = 525,
     ONLY = 526,
     OPEN = 527,
     OPTIONAL = 528,
     OR = 529,
     ORDER = 530,
     ORGANIZATION = 531,
     OTHER = 532,
     OUTPUT = 533,
     OVERFLOW = 534,
     OVERLINE = 535,
     PACKED_DECIMAL = 536,
     PADDING = 537,
     PAGE = 538,
     PAGE_FOOTING = 539,
     PAGE_HEADING = 540,
     PARAGRAPH = 541,
     PERFORM = 542,
     PICTURE = 543,
     PLUS = 544,
     POINTER = 545,
     POSITION = 546,
     POSITIVE = 547,
     PRESENT = 548,
     PREVIOUS = 549,
     PRINTER = 550,
     PRINTING = 551,
     PROCEDURE = 552,
     PROCEDURES = 553,
     PROCEED = 554,
     PROGRAM = 555,
     PROGRAM_ID = 556,
     PROGRAM_NAME = 557,
     PROGRAM_POINTER = 558,
     PROMPT = 559,
     QUOTE = 560,
     RANDOM = 561,
     RD = 562,
     READ = 563,
     RECORD = 564,
     RECORDING = 565,
     RECORDS = 566,
     RECURSIVE = 567,
     REDEFINES = 568,
     REEL = 569,
     REFERENCE = 570,
     RELATIVE = 571,
     RELEASE = 572,
     REMAINDER = 573,
     REMOVAL = 574,
     RENAMES = 575,
     REPLACING = 576,
     REPORT = 577,
     REPORTING = 578,
     REPORTS = 579,
     REPORT_FOOTING = 580,
     REPORT_HEADING = 581,
     REPOSITORY = 582,
     REQUIRED = 583,
     RESERVE = 584,
     RETURN = 585,
     RETURNING = 586,
     REVERSE_FUNC = 587,
     REVERSE_VIDEO = 588,
     REWIND = 589,
     REWRITE = 590,
     RIGHT = 591,
     ROLLBACK = 592,
     ROUNDED = 593,
     RUN = 594,
     SAME = 595,
     SCREEN = 596,
     SCREEN_CONTROL = 597,
     SCROLL = 598,
     SD = 599,
     SEARCH = 600,
     SECTION = 601,
     SECURE = 602,
     SEGMENT_LIMIT = 603,
     SELECT = 604,
     SEMI_COLON = 605,
     SENTENCE = 606,
     SEPARATE = 607,
     SEQUENCE = 608,
     SEQUENTIAL = 609,
     SET = 610,
     SHARING = 611,
     SIGN = 612,
     SIGNED = 613,
     SIGNED_INT = 614,
     SIGNED_LONG = 615,
     SIGNED_SHORT = 616,
     SIZE = 617,
     SIZE_ERROR = 618,
     SORT = 619,
     SORT_MERGE = 620,
     SOURCE = 621,
     SOURCE_COMPUTER = 622,
     SPACE = 623,
     SPECIAL_NAMES = 624,
     STANDARD = 625,
     STANDARD_1 = 626,
     STANDARD_2 = 627,
     START = 628,
     STATUS = 629,
     STOP = 630,
     STRING = 631,
     SUBSTITUTE_FUNC = 632,
     SUBSTITUTE_CASE_FUNC = 633,
     SUBTRACT = 634,
     SUM = 635,
     SUPPRESS = 636,
     SYMBOLIC = 637,
     SYNCHRONIZED = 638,
     TALLYING = 639,
     TAPE = 640,
     TERMINATE = 641,
     TEST = 642,
     THAN = 643,
     THEN = 644,
     THRU = 645,
     TIME = 646,
     TIMES = 647,
     TO = 648,
     TOK_FALSE = 649,
     TOK_FILE = 650,
     TOK_INITIAL = 651,
     TOK_NULL = 652,
     TOK_TRUE = 653,
     TOP = 654,
     TRAILING = 655,
     TRANSFORM = 656,
     TRIM_FUNCTION = 657,
     TYPE = 658,
     UNDERLINE = 659,
     UNIT = 660,
     UNLOCK = 661,
     UNSIGNED = 662,
     UNSIGNED_INT = 663,
     UNSIGNED_LONG = 664,
     UNSIGNED_SHORT = 665,
     UNSTRING = 666,
     UNTIL = 667,
     UP = 668,
     UPDATE = 669,
     UPON = 670,
     UPON_ARGUMENT_NUMBER = 671,
     UPON_COMMAND_LINE = 672,
     UPON_ENVIRONMENT_NAME = 673,
     UPON_ENVIRONMENT_VALUE = 674,
     UPPER_CASE_FUNC = 675,
     USAGE = 676,
     USE = 677,
     USING = 678,
     VALUE = 679,
     VARYING = 680,
     WAIT = 681,
     WHEN = 682,
     WHEN_COMPILED_FUNC = 683,
     WITH = 684,
     WORD = 685,
     WORDS = 686,
     WORKING_STORAGE = 687,
     WRITE = 688,
     YYYYDDD = 689,
     YYYYMMDD = 690,
     ZERO = 691,
     UNARY_SIGN = 692
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 834 "parser.c"

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   5462

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  451
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  690
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1519
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2240

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   692

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   450,     2,
     445,   446,   439,   437,     2,   438,   443,   440,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   449,     2,
     448,   444,   447,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   442,     2,     2,     2,     2,     2,
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
     435,   436,   441
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
     248,   250,   252,   254,   256,   258,   262,   263,   269,   270,
     276,   278,   280,   281,   287,   289,   291,   293,   295,   297,
     299,   302,   304,   308,   309,   314,   316,   320,   322,   324,
     326,   328,   330,   332,   334,   336,   338,   340,   342,   344,
     348,   352,   354,   357,   359,   362,   367,   369,   372,   374,
     378,   383,   388,   392,   396,   401,   405,   409,   410,   416,
     417,   422,   423,   428,   429,   433,   434,   437,   438,   445,
     446,   449,   451,   453,   455,   457,   459,   461,   463,   465,
     467,   469,   471,   473,   475,   481,   486,   491,   492,   494,
     496,   497,   499,   501,   503,   505,   507,   512,   514,   516,
     518,   525,   529,   535,   536,   538,   540,   545,   548,   551,
     553,   554,   559,   565,   568,   570,   572,   576,   578,   580,
     584,   586,   589,   594,   599,   604,   606,   610,   615,   620,
     624,   628,   631,   634,   637,   638,   642,   643,   646,   648,
     651,   653,   655,   661,   662,   664,   666,   668,   674,   676,
     679,   682,   683,   686,   687,   697,   698,   699,   705,   706,
     710,   711,   714,   718,   721,   724,   726,   728,   729,   734,
     735,   738,   741,   744,   746,   748,   750,   752,   754,   756,
     758,   760,   762,   768,   769,   771,   773,   778,   785,   795,
     796,   800,   801,   804,   805,   808,   812,   814,   816,   822,
     828,   830,   832,   836,   842,   843,   846,   848,   850,   852,
     858,   863,   867,   872,   876,   880,   884,   885,   886,   892,
     893,   895,   896,   899,   903,   908,   911,   913,   914,   919,
     921,   922,   924,   926,   928,   929,   932,   934,   938,   942,
     949,   950,   953,   955,   957,   959,   961,   963,   965,   967,
     969,   971,   973,   975,   977,   979,   981,   984,   988,   989,
     992,   995,   997,   999,  1003,  1005,  1007,  1009,  1011,  1013,
    1015,  1017,  1019,  1021,  1023,  1025,  1027,  1029,  1031,  1033,
    1035,  1037,  1039,  1041,  1044,  1047,  1049,  1052,  1055,  1057,
    1060,  1063,  1065,  1068,  1071,  1073,  1076,  1079,  1081,  1083,
    1087,  1091,  1099,  1100,  1103,  1104,  1108,  1110,  1111,  1117,
    1119,  1121,  1122,  1126,  1128,  1131,  1133,  1136,  1139,  1140,
    1142,  1144,  1148,  1150,  1151,  1160,  1162,  1165,  1167,  1171,
    1172,  1176,  1179,  1184,  1187,  1188,  1189,  1195,  1196,  1197,
    1203,  1204,  1205,  1211,  1212,  1214,  1216,  1219,  1225,  1226,
    1229,  1232,  1236,  1238,  1240,  1243,  1246,  1249,  1250,  1252,
    1254,  1257,  1266,  1267,  1271,  1272,  1277,  1278,  1283,  1284,
    1288,  1289,  1293,  1295,  1300,  1303,  1305,  1307,  1308,  1311,
    1316,  1317,  1320,  1322,  1324,  1326,  1328,  1330,  1332,  1334,
    1336,  1338,  1340,  1342,  1344,  1346,  1348,  1350,  1352,  1356,
    1358,  1360,  1362,  1364,  1366,  1368,  1370,  1375,  1380,  1383,
    1385,  1387,  1390,  1394,  1396,  1400,  1407,  1410,  1414,  1417,
    1419,  1422,  1425,  1427,  1430,  1431,  1433,  1435,  1440,  1443,
    1444,  1446,  1448,  1449,  1450,  1451,  1458,  1459,  1461,  1463,
    1466,  1468,  1469,  1475,  1476,  1479,  1481,  1483,  1485,  1487,
    1490,  1493,  1495,  1497,  1499,  1501,  1503,  1505,  1507,  1509,
    1511,  1513,  1519,  1525,  1529,  1533,  1535,  1537,  1539,  1541,
    1543,  1545,  1547,  1550,  1553,  1556,  1557,  1559,  1561,  1563,
    1565,  1566,  1568,  1570,  1572,  1574,  1578,  1579,  1580,  1581,
    1591,  1592,  1593,  1597,  1598,  1602,  1604,  1607,  1612,  1613,
    1616,  1619,  1620,  1624,  1628,  1633,  1637,  1638,  1640,  1641,
    1644,  1645,  1646,  1654,  1655,  1658,  1660,  1662,  1664,  1667,
    1670,  1672,  1677,  1680,  1682,  1684,  1685,  1687,  1688,  1689,
    1693,  1694,  1697,  1700,  1702,  1704,  1706,  1708,  1710,  1712,
    1714,  1716,  1718,  1720,  1722,  1724,  1726,  1728,  1730,  1732,
    1734,  1736,  1738,  1740,  1742,  1744,  1746,  1748,  1750,  1752,
    1754,  1756,  1758,  1760,  1762,  1764,  1766,  1768,  1770,  1772,
    1774,  1776,  1778,  1780,  1782,  1784,  1786,  1788,  1790,  1792,
    1794,  1796,  1798,  1799,  1804,  1809,  1814,  1818,  1822,  1826,
    1831,  1835,  1840,  1844,  1848,  1852,  1857,  1863,  1867,  1872,
    1876,  1880,  1881,  1885,  1889,  1892,  1895,  1898,  1902,  1906,
    1910,  1911,  1914,  1916,  1919,  1921,  1923,  1925,  1927,  1929,
    1931,  1933,  1937,  1941,  1945,  1949,  1951,  1953,  1955,  1957,
    1959,  1961,  1962,  1964,  1965,  1970,  1975,  1981,  1988,  1989,
    1992,  1993,  1995,  1996,  2000,  2004,  2010,  2011,  2014,  2017,
    2018,  2024,  2025,  2028,  2029,  2038,  2039,  2040,  2044,  2046,
    2049,  2052,  2056,  2057,  2060,  2063,  2066,  2067,  2070,  2073,
    2074,  2075,  2079,  2080,  2081,  2085,  2086,  2088,  2089,  2093,
    2094,  2097,  2098,  2102,  2103,  2107,  2108,  2110,  2114,  2118,
    2121,  2123,  2125,  2126,  2131,  2136,  2137,  2139,  2141,  2143,
    2145,  2147,  2148,  2155,  2156,  2158,  2159,  2164,  2168,  2172,
    2176,  2180,  2186,  2187,  2190,  2193,  2196,  2199,  2200,  2203,
    2206,  2208,  2211,  2213,  2215,  2218,  2221,  2223,  2225,  2227,
    2229,  2231,  2235,  2239,  2243,  2247,  2249,  2251,  2252,  2254,
    2255,  2260,  2265,  2272,  2279,  2288,  2297,  2298,  2300,  2301,
    2306,  2307,  2313,  2315,  2319,  2321,  2323,  2325,  2328,  2330,
    2333,  2334,  2338,  2339,  2340,  2345,  2348,  2352,  2354,  2358,
    2361,  2363,  2365,  2367,  2368,  2371,  2372,  2374,  2375,  2379,
    2380,  2382,  2384,  2387,  2389,  2391,  2392,  2396,  2397,  2401,
    2402,  2408,  2409,  2413,  2414,  2417,  2418,  2419,  2428,  2432,
    2433,  2434,  2438,  2439,  2441,  2442,  2450,  2451,  2454,  2455,
    2459,  2463,  2464,  2467,  2469,  2472,  2477,  2479,  2481,  2483,
    2485,  2487,  2489,  2491,  2492,  2494,  2495,  2499,  2500,  2505,
    2507,  2509,  2511,  2513,  2516,  2518,  2520,  2522,  2523,  2527,
    2529,  2532,  2535,  2538,  2540,  2542,  2544,  2547,  2550,  2552,
    2555,  2560,  2563,  2564,  2566,  2568,  2570,  2572,  2577,  2583,
    2584,  2589,  2590,  2592,  2593,  2597,  2598,  2602,  2606,  2611,
    2612,  2617,  2622,  2629,  2630,  2632,  2633,  2637,  2638,  2644,
    2646,  2648,  2650,  2652,  2653,  2657,  2658,  2662,  2665,  2666,
    2670,  2673,  2674,  2679,  2682,  2683,  2685,  2687,  2691,  2692,
    2694,  2697,  2701,  2705,  2706,  2710,  2712,  2716,  2724,  2725,
    2736,  2737,  2740,  2741,  2744,  2747,  2751,  2755,  2758,  2759,
    2763,  2764,  2766,  2768,  2769,  2771,  2772,  2777,  2778,  2786,
    2787,  2789,  2790,  2798,  2799,  2802,  2806,  2807,  2809,  2811,
    2812,  2817,  2822,  2823,  2831,  2832,  2835,  2836,  2837,  2842,
    2844,  2847,  2848,  2853,  2854,  2856,  2857,  2861,  2863,  2865,
    2867,  2869,  2871,  2876,  2881,  2885,  2890,  2892,  2894,  2896,
    2899,  2903,  2905,  2908,  2912,  2916,  2917,  2921,  2922,  2930,
    2931,  2937,  2938,  2941,  2942,  2945,  2946,  2950,  2951,  2954,
    2959,  2960,  2963,  2968,  2969,  2970,  2978,  2979,  2984,  2987,
    2990,  2993,  2996,  2999,  3000,  3002,  3003,  3008,  3011,  3012,
    3015,  3018,  3019,  3028,  3030,  3033,  3035,  3039,  3043,  3044,
    3048,  3049,  3051,  3052,  3057,  3062,  3069,  3076,  3077,  3079,
    3082,  3083,  3085,  3086,  3090,  3091,  3099,  3100,  3105,  3106,
    3108,  3110,  3111,  3121,  3122,  3126,  3128,  3132,  3135,  3138,
    3141,  3145,  3146,  3150,  3151,  3155,  3156,  3160,  3161,  3163,
    3165,  3167,  3169,  3178,  3179,  3181,  3183,  3185,  3187,  3189,
    3191,  3192,  3194,  3195,  3197,  3199,  3201,  3203,  3205,  3207,
    3209,  3210,  3212,  3218,  3220,  3223,  3229,  3230,  3239,  3240,
    3243,  3244,  3249,  3253,  3257,  3259,  3261,  3262,  3264,  3266,
    3267,  3269,  3272,  3275,  3276,  3277,  3281,  3282,  3283,  3287,
    3290,  3291,  3292,  3296,  3297,  3298,  3302,  3305,  3306,  3307,
    3311,  3312,  3313,  3317,  3319,  3321,  3324,  3325,  3329,  3330,
    3334,  3336,  3338,  3341,  3342,  3346,  3347,  3351,  3352,  3354,
    3356,  3358,  3361,  3362,  3366,  3367,  3371,  3372,  3376,  3378,
    3380,  3381,  3384,  3386,  3389,  3392,  3394,  3396,  3398,  3400,
    3402,  3404,  3406,  3408,  3410,  3412,  3414,  3416,  3418,  3420,
    3422,  3424,  3426,  3428,  3430,  3432,  3434,  3436,  3438,  3440,
    3442,  3445,  3447,  3449,  3452,  3454,  3457,  3459,  3465,  3467,
    3473,  3475,  3479,  3480,  3482,  3484,  3486,  3490,  3494,  3498,
    3502,  3505,  3508,  3512,  3516,  3518,  3522,  3524,  3527,  3530,
    3532,  3534,  3536,  3539,  3541,  3543,  3546,  3548,  3549,  3552,
    3554,  3556,  3558,  3562,  3564,  3566,  3569,  3571,  3572,  3574,
    3576,  3578,  3580,  3582,  3585,  3587,  3591,  3593,  3596,  3598,
    3602,  3606,  3610,  3615,  3619,  3621,  3623,  3625,  3627,  3631,
    3635,  3639,  3641,  3643,  3645,  3647,  3649,  3651,  3653,  3655,
    3657,  3659,  3661,  3663,  3665,  3667,  3669,  3671,  3673,  3675,
    3677,  3679,  3681,  3684,  3687,  3691,  3693,  3697,  3701,  3706,
    3712,  3714,  3716,  3719,  3721,  3725,  3727,  3729,  3731,  3733,
    3735,  3737,  3739,  3742,  3745,  3751,  3757,  3763,  3769,  3775,
    3781,  3787,  3792,  3798,  3801,  3802,  3807,  3813,  3814,  3818,
    3819,  3821,  3823,  3827,  3831,  3833,  3837,  3839,  3843,  3844,
    3845,  3847,  3848,  3850,  3851,  3853,  3854,  3856,  3858,  3859,
    3861,  3862,  3864,  3865,  3867,  3868,  3871,  3873,  3875,  3878,
    3881,  3884,  3886,  3889,  3891,  3892,  3894,  3895,  3897,  3898,
    3900,  3901,  3903,  3904,  3906,  3907,  3909,  3910,  3912,  3913,
    3915,  3916,  3918,  3919,  3921,  3922,  3924,  3925,  3927,  3928,
    3930,  3931,  3933,  3934,  3936,  3937,  3939,  3940,  3942,  3944,
    3945,  3947,  3948,  3950,  3952,  3953,  3955,  3956,  3958,  3959,
    3961,  3962,  3964,  3965,  3967,  3968,  3970,  3973,  3974,  3976,
    3977,  3979,  3980,  3982,  3983,  3985,  3986,  3988,  3989,  3991,
    3992,  3994,  3997,  3998,  4000,  4001,  4003,  4004,  4006,  4007,
    4009,  4010,  4012,  4013,  4015,  4016,  4018,  4019,  4021,  4022
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     452,     0,    -1,    -1,   453,   454,    -1,   455,    -1,   454,
     455,    -1,   456,    -1,   462,    -1,    -1,    -1,   469,   477,
     457,   572,   458,   706,   465,   466,    -1,    -1,    -1,   469,
     477,   460,   572,   461,   706,   465,   467,    -1,    -1,    -1,
     471,   477,   463,   572,   464,   706,   468,    -1,    -1,   459,
      -1,   465,   459,    -1,    -1,   133,   472,   443,    -1,   133,
     472,   443,    -1,   129,   472,   443,    -1,    -1,   301,   443,
     472,   473,   470,   474,   443,    -1,   176,   443,   472,   473,
     443,    -1,   302,    -1,   227,    -1,    -1,    26,   227,    -1,
      -1,  1115,   475,  1126,    -1,    69,    -1,    69,   476,    -1,
     476,    -1,   396,    -1,   312,    -1,    -1,   144,   114,   443,
     478,   529,    -1,    -1,    79,   346,   443,   479,    -1,    -1,
     479,   480,    -1,   481,    -1,   485,    -1,   498,    -1,   493,
      -1,   367,   443,   482,    -1,    -1,   484,   443,    -1,   484,
     483,   443,    -1,   483,   443,    -1,  1140,   101,   240,    -1,
     430,    -1,   265,   443,   486,    -1,    -1,   484,   443,    -1,
     484,   487,   443,    -1,   487,   443,    -1,   488,    -1,   487,
     488,    -1,   489,    -1,   491,    -1,   492,    -1,   236,   362,
    1115,  1076,   490,    -1,    55,    -1,   431,    -1,  1126,  1099,
    1115,  1055,    -1,   348,  1115,  1076,    -1,   327,   443,   494,
      -1,    -1,   495,   443,    -1,   496,    -1,   495,   496,    -1,
     175,   497,   204,    -1,   175,     9,   204,    -1,   227,    -1,
     497,   227,    -1,   369,   443,   499,    -1,    -1,   500,   443,
      -1,   501,    -1,   500,   501,    -1,   502,    -1,   506,    -1,
     515,    -1,   522,    -1,   519,    -1,   523,    -1,   524,    -1,
     525,    -1,   526,    -1,   527,    -1,   528,    -1,   430,  1115,
      91,    -1,    -1,   430,  1115,  1058,   503,   504,    -1,    -1,
     504,   505,  1133,  1115,  1058,    -1,   270,    -1,   268,    -1,
      -1,    11,  1058,   507,  1115,   508,    -1,   246,    -1,   371,
      -1,   372,    -1,   118,    -1,   509,    -1,   510,    -1,   509,
     510,    -1,   513,    -1,   513,   390,   513,    -1,    -1,   513,
      17,   511,   512,    -1,   514,    -1,   512,    17,   514,    -1,
     227,    -1,   368,    -1,   436,    -1,   305,    -1,   188,    -1,
     234,    -1,   227,    -1,   368,    -1,   436,    -1,   305,    -1,
     188,    -1,   234,    -1,   382,  1108,   516,    -1,   517,  1116,
     518,    -1,  1058,    -1,   517,  1058,    -1,  1076,    -1,   518,
    1076,    -1,    56,  1058,  1115,   520,    -1,   521,    -1,   520,
     521,    -1,  1079,    -1,  1079,   390,  1079,    -1,   228,  1058,
    1115,  1055,    -1,    92,  1130,  1115,   227,    -1,   102,  1115,
      65,    -1,    94,  1115,  1055,    -1,    91,   374,  1115,  1055,
      -1,   342,  1115,  1055,    -1,   156,  1115,  1055,    -1,    -1,
     201,   346,   443,   532,   562,    -1,    -1,   163,   443,   530,
     533,    -1,    -1,   209,   443,   531,   563,    -1,    -1,   163,
     443,   533,    -1,    -1,   533,   534,    -1,    -1,   349,  1093,
    1058,   535,   536,   443,    -1,    -1,   536,   537,    -1,   538,
      -1,   542,    -1,   544,    -1,   545,    -1,   546,    -1,   548,
      -1,   552,    -1,   554,    -1,   555,    -1,   556,    -1,   558,
      -1,   559,    -1,   560,    -1,    28,  1138,   540,   539,   541,
      -1,    28,  1138,   540,   111,    -1,    28,  1138,   540,   295,
      -1,    -1,   111,    -1,   295,    -1,    -1,   161,    -1,   117,
      -1,   227,    -1,   112,    -1,  1073,    -1,     4,  1120,  1115,
     543,    -1,   354,    -1,   117,    -1,   306,    -1,    19,   309,
    1117,  1115,   557,  1089,    -1,  1099,  1115,   430,    -1,   547,
     374,  1115,  1055,  1056,    -1,    -1,   395,    -1,   364,    -1,
     231,  1120,  1115,   549,    -1,   235,   550,    -1,    31,   550,
      -1,   158,    -1,    -1,   429,   231,   270,   551,    -1,   429,
     231,   270,   242,   551,    -1,   429,   337,    -1,   309,    -1,
     311,    -1,   276,  1115,   553,    -1,   553,    -1,   195,    -1,
    1127,  1105,   354,    -1,   316,    -1,   224,   354,    -1,   282,
    1107,  1115,  1057,    -1,   309,   107,  1115,   371,    -1,   309,
    1117,  1115,   557,    -1,  1055,    -1,  1055,   444,  1054,    -1,
    1055,   366,  1115,  1054,    -1,   316,  1117,  1115,  1055,    -1,
     329,  1076,  1102,    -1,   356,  1140,   561,    -1,     9,  1125,
      -1,   251,  1125,    -1,   308,   271,    -1,    -1,   209,   443,
     563,    -1,    -1,   564,   443,    -1,   565,    -1,   564,   565,
      -1,   566,    -1,   568,    -1,   340,   567,  1102,  1112,  1046,
      -1,    -1,   309,    -1,   364,    -1,   365,    -1,   242,  1111,
    1134,  1109,   569,    -1,   570,    -1,   569,   570,    -1,  1047,
     571,    -1,    -1,   291,  1076,    -1,    -1,    96,   114,   443,
     573,   604,   649,   651,   653,   694,    -1,    -1,    -1,   395,
     346,   443,   574,   576,    -1,    -1,   579,   575,   578,    -1,
      -1,   576,   577,    -1,   579,   580,   606,    -1,   580,   606,
      -1,   578,   577,    -1,   162,    -1,   344,    -1,    -1,  1047,
     581,   582,   443,    -1,    -1,   582,   583,    -1,  1115,   161,
      -1,  1115,   181,    -1,   584,    -1,   586,    -1,   590,    -1,
     592,    -1,   594,    -1,   595,    -1,   601,    -1,   602,    -1,
     603,    -1,    46,  1109,  1076,   589,   585,    -1,    -1,   311,
      -1,    55,    -1,   309,  1109,  1076,  1108,    -1,   309,  1109,
    1076,   393,  1076,  1108,    -1,   309,  1115,   425,  1114,  1132,
     588,   589,  1108,   587,    -1,    -1,   108,  1123,  1055,    -1,
      -1,  1113,  1076,    -1,    -1,   393,  1076,    -1,   212,  1097,
     591,    -1,   370,    -1,   269,    -1,   424,   267,   430,  1115,
     593,    -1,   424,   267,   164,  1115,   593,    -1,   227,    -1,
    1073,    -1,    96,  1097,  1054,    -1,   222,  1115,  1057,  1119,
     596,    -1,    -1,   596,   597,    -1,   598,    -1,   599,    -1,
     600,    -1,  1140,   168,  1104,  1057,  1119,    -1,  1104,   399,
    1057,  1119,    -1,  1104,    47,  1057,    -1,   310,  1120,  1115,
     430,    -1,    59,  1115,   430,    -1,   322,  1115,   693,    -1,
     324,  1101,   693,    -1,    -1,    -1,   432,   346,   443,   605,
     606,    -1,    -1,   607,    -1,    -1,   608,   609,    -1,  1087,
     610,   443,    -1,   609,  1087,   610,   443,    -1,   609,   443,
      -1,   617,    -1,    -1,   612,   613,   611,   618,    -1,   430,
      -1,    -1,   165,    -1,   430,    -1,   430,    -1,    -1,  1115,
     181,    -1,  1077,    -1,   218,  1122,  1072,    -1,    49,  1122,
    1072,    -1,   612,   614,    80,   615,  1103,   616,    -1,    -1,
     618,   619,    -1,   620,    -1,   621,    -1,   623,    -1,   624,
      -1,   625,    -1,   627,    -1,   628,    -1,   637,    -1,   638,
      -1,   640,    -1,   641,    -1,   642,    -1,   647,    -1,   648,
      -1,   313,  1072,    -1,  1115,   161,   622,    -1,    -1,    26,
     227,    -1,  1115,   181,    -1,   288,    -1,   626,    -1,   421,
    1115,   626,    -1,    36,    -1,    70,    -1,    72,    -1,    73,
      -1,    74,    -1,    75,    -1,    76,    -1,    77,    -1,   112,
      -1,   194,    -1,   281,    -1,   290,    -1,   303,    -1,   361,
      -1,   359,    -1,   360,    -1,   410,    -1,   408,    -1,   409,
      -1,    38,   358,    -1,    38,   407,    -1,    38,    -1,    41,
     358,    -1,    41,   407,    -1,    41,    -1,    40,   358,    -1,
      40,   407,    -1,    40,    -1,    39,   358,    -1,    39,   407,
      -1,    39,    -1,    37,   358,    -1,    37,   407,    -1,    37,
      -1,   244,    -1,  1131,   216,  1095,    -1,  1131,   400,  1095,
      -1,   266,  1076,   629,  1137,   630,   631,   634,    -1,    -1,
     393,  1076,    -1,    -1,   108,  1123,  1055,    -1,   632,    -1,
      -1,   632,   633,  1117,  1115,  1054,    -1,    27,    -1,   109,
      -1,    -1,   195,  1106,   635,    -1,   636,    -1,   635,   636,
      -1,   430,    -1,   210,  1128,    -1,   383,   639,    -1,    -1,
     217,    -1,   336,    -1,    42,  1139,   436,    -1,    33,    -1,
      -1,   424,  1116,   644,   643,  1139,  1129,  1138,   646,    -1,
     645,    -1,   644,   645,    -1,  1077,    -1,  1077,   390,  1077,
      -1,    -1,   394,  1115,  1077,    -1,   320,  1073,    -1,   320,
    1073,   390,  1073,    -1,    21,   218,    -1,    -1,    -1,   230,
     346,   443,   650,   606,    -1,    -1,    -1,   226,   346,   443,
     652,   606,    -1,    -1,    -1,   322,   346,   443,   654,   655,
      -1,    -1,   656,    -1,   657,    -1,   656,   657,    -1,   307,
     693,   658,   443,   672,    -1,    -1,   658,   659,    -1,  1115,
     181,    -1,    58,  1115,  1068,    -1,   660,    -1,   664,    -1,
      84,   661,    -1,    85,   661,    -1,   662,   663,    -1,    -1,
     166,    -1,  1071,    -1,   663,  1071,    -1,   283,  1116,   670,
     665,   666,   667,   668,   669,    -1,    -1,   186,  1115,  1076,
      -1,    -1,   167,   110,  1115,  1076,    -1,    -1,   213,    87,
    1115,  1076,    -1,    -1,   214,  1115,  1076,    -1,    -1,   168,
    1115,  1076,    -1,  1076,    -1,  1076,   671,  1076,    64,    -1,
    1076,   671,    -1,   224,    -1,   225,    -1,    -1,   672,   673,
      -1,   612,   613,   674,   443,    -1,    -1,   674,   675,    -1,
     676,    -1,   678,    -1,   685,    -1,   624,    -1,   625,    -1,
     627,    -1,   637,    -1,   679,    -1,   640,    -1,   690,    -1,
     680,    -1,   642,    -1,   683,    -1,   691,    -1,   628,    -1,
     684,    -1,   403,  1115,   677,    -1,   326,    -1,   285,    -1,
      87,    -1,   110,    -1,    86,    -1,   284,    -1,   325,    -1,
     249,   185,  1115,  1076,    -1,    63,  1121,  1115,  1076,    -1,
      63,   261,    -1,    64,    -1,   681,    -1,   680,   681,    -1,
     380,  1122,   682,    -1,  1055,    -1,   293,   427,  1027,    -1,
     425,  1071,   173,  1062,    48,  1062,    -1,   686,   687,    -1,
     224,   689,  1116,    -1,   225,  1101,    -1,   688,    -1,   687,
     688,    -1,   289,  1076,    -1,  1076,    -1,   249,   283,    -1,
      -1,   260,    -1,   261,    -1,   366,  1115,  1071,  1094,    -1,
     185,   692,    -1,    -1,   196,    -1,   430,    -1,    -1,    -1,
      -1,   341,   346,   443,   695,   696,   697,    -1,    -1,   698,
      -1,   699,    -1,   698,   699,    -1,   617,    -1,    -1,   612,
     613,   700,   701,   443,    -1,    -1,   701,   702,    -1,    43,
      -1,    44,    -1,    35,    -1,    45,    -1,   152,   147,    -1,
     152,   149,    -1,   187,    -1,   233,    -1,   333,    -1,   404,
      -1,   280,    -1,    30,    -1,   347,    -1,   328,    -1,   174,
      -1,   304,    -1,   224,  1121,  1115,   703,  1070,    -1,    63,
    1121,  1115,   704,  1070,    -1,   170,  1115,  1070,    -1,    32,
    1115,  1070,    -1,   625,    -1,   640,    -1,   637,    -1,   627,
      -1,   642,    -1,   624,    -1,   705,    -1,   423,  1071,    -1,
     173,  1069,    -1,   393,  1071,    -1,    -1,   289,    -1,   437,
      -1,   238,    -1,   438,    -1,    -1,   289,    -1,   437,    -1,
     238,    -1,   438,    -1,   266,  1076,  1137,    -1,    -1,    -1,
      -1,   297,   114,   709,   717,   443,   707,   718,   708,   720,
      -1,    -1,    -1,   423,   710,   712,    -1,    -1,    53,   711,
     712,    -1,   713,    -1,   712,   713,    -1,   714,   715,   716,
     430,    -1,    -1,  1106,   315,    -1,  1106,   424,    -1,    -1,
     362,  1115,    30,    -1,   362,  1115,   104,    -1,   407,   362,
    1115,  1076,    -1,   362,  1115,  1076,    -1,    -1,   273,    -1,
      -1,   331,   430,    -1,    -1,    -1,   103,   443,   719,   720,
     120,   103,   443,    -1,    -1,   720,   721,    -1,   722,    -1,
     723,    -1,   724,    -1,   730,   443,    -1,     1,   443,    -1,
     443,    -1,   725,   346,   726,   443,    -1,   430,   443,    -1,
     725,    -1,   430,    -1,    -1,   227,    -1,    -1,    -1,   728,
     729,   730,    -1,    -1,   731,   732,    -1,   730,   732,    -1,
     733,    -1,   743,    -1,   748,    -1,   752,    -1,   755,    -1,
     768,    -1,   771,    -1,   781,    -1,   776,    -1,   782,    -1,
     783,    -1,   786,    -1,   794,    -1,   798,    -1,   800,    -1,
     815,    -1,   818,    -1,   820,    -1,   822,    -1,   825,    -1,
     827,    -1,   833,    -1,   842,    -1,   844,    -1,   861,    -1,
     863,    -1,   866,    -1,   870,    -1,   876,    -1,   886,    -1,
     893,    -1,   895,    -1,   898,    -1,   902,    -1,   903,    -1,
     914,    -1,   925,    -1,   935,    -1,   941,    -1,   944,    -1,
     950,    -1,   954,    -1,   956,    -1,   958,    -1,   960,    -1,
     963,    -1,   974,    -1,   987,    -1,   250,    -1,    -1,     3,
     734,   735,   742,    -1,  1071,   736,   739,   994,    -1,  1071,
     173,   154,   211,    -1,  1071,   173,   225,    -1,  1071,   173,
      64,    -1,  1071,   173,    97,    -1,  1071,   173,    97,   435,
      -1,  1071,   173,    98,    -1,  1071,   173,    98,   434,    -1,
    1071,   173,    99,    -1,  1071,   173,   391,    -1,  1071,   173,
      66,    -1,  1071,   173,   146,   994,    -1,  1071,   173,   144,
    1066,   994,    -1,  1071,   173,    24,    -1,  1071,   173,    25,
     994,    -1,  1071,   173,  1049,    -1,  1071,   173,   430,    -1,
      -1,  1104,   737,   738,    -1,  1104,   738,   737,    -1,  1104,
     737,    -1,  1104,   738,    -1,    29,  1066,    -1,   224,  1121,
    1068,    -1,    63,  1121,  1068,    -1,   291,  1121,  1068,    -1,
      -1,   429,   740,    -1,   741,    -1,   740,   741,    -1,    35,
      -1,    45,    -1,   187,    -1,   233,    -1,   333,    -1,   404,
      -1,   280,    -1,   170,  1115,  1070,    -1,    32,  1115,  1070,
      -1,   343,   413,  1026,    -1,   343,   115,  1026,    -1,    30,
      -1,   174,    -1,   328,    -1,   347,    -1,   414,    -1,   304,
      -1,    -1,   121,    -1,    -1,     5,   744,   745,   747,    -1,
    1061,   393,  1042,  1000,    -1,  1061,   746,   180,  1042,  1000,
      -1,    89,  1071,   393,  1071,  1094,  1000,    -1,    -1,   393,
    1062,    -1,    -1,   122,    -1,    -1,    10,   749,   750,    -1,
     430,  1090,   751,    -1,  1028,    55,  1090,   331,  1060,    -1,
      -1,   331,  1060,    -1,    18,   753,    -1,    -1,   753,  1051,
     393,   754,  1051,    -1,    -1,   299,   393,    -1,    -1,    50,
     756,  1069,   757,   762,   763,   765,   767,    -1,    -1,    -1,
     423,   758,   759,    -1,   760,    -1,   759,   760,    -1,   761,
     269,    -1,   761,   715,  1062,    -1,    -1,  1106,   315,    -1,
    1106,    82,    -1,  1106,   424,    -1,    -1,   331,  1071,    -1,
     180,  1071,    -1,    -1,    -1,   981,   764,   727,    -1,    -1,
      -1,   982,   766,   727,    -1,    -1,   123,    -1,    -1,    51,
     769,   770,    -1,    -1,   770,  1068,    -1,    -1,    57,   772,
     773,    -1,    -1,   773,  1047,   774,    -1,    -1,   775,    -1,
     775,  1112,   319,    -1,  1140,   251,   334,    -1,  1140,   231,
      -1,   314,    -1,   405,    -1,    -1,    71,   777,   778,   779,
      -1,  1042,   780,  1028,  1000,    -1,    -1,   124,    -1,   444,
      -1,   150,    -1,    68,    -1,    83,    -1,    -1,   105,   784,
    1047,  1127,  1020,   785,    -1,    -1,   125,    -1,    -1,   112,
     787,   788,   793,    -1,  1068,   418,   995,    -1,  1068,   419,
     995,    -1,  1068,   416,   995,    -1,  1068,   417,   995,    -1,
    1061,   736,   789,   790,   995,    -1,    -1,   415,  1049,    -1,
     415,   430,    -1,   415,   295,    -1,   415,    91,    -1,    -1,
    1140,   259,    -1,   429,   791,    -1,   792,    -1,   791,   792,
      -1,    35,    -1,    45,    -1,   152,   147,    -1,   152,   149,
      -1,   187,    -1,   233,    -1,   333,    -1,   404,    -1,   280,
      -1,   170,  1115,  1070,    -1,    32,  1115,  1070,    -1,   343,
     413,  1026,    -1,   343,   115,  1026,    -1,    43,    -1,    44,
      -1,    -1,   126,    -1,    -1,   113,   795,   796,   797,    -1,
    1062,   203,  1042,  1000,    -1,  1062,   203,  1062,   180,  1042,
    1000,    -1,  1062,    48,  1062,   180,  1042,  1000,    -1,  1062,
     203,  1062,   180,  1043,   318,  1043,  1000,    -1,  1062,    48,
    1062,   180,  1043,   318,  1043,  1000,    -1,    -1,   127,    -1,
      -1,   143,   799,   227,   757,    -1,    -1,   155,   801,   802,
     804,   814,    -1,   803,    -1,   802,    17,   803,    -1,  1028,
      -1,   398,    -1,   394,    -1,   805,   808,    -1,   806,    -1,
     805,   806,    -1,    -1,   810,   807,   727,    -1,    -1,    -1,
     427,   277,   809,   727,    -1,   427,   811,    -1,   810,   427,
     811,    -1,   812,    -1,   811,    17,   812,    -1,  1029,   813,
      -1,    21,    -1,   398,    -1,   394,    -1,    -1,   390,  1028,
      -1,    -1,   128,    -1,    -1,   159,   816,   817,    -1,    -1,
     300,    -1,   287,    -1,   287,    95,    -1,   346,    -1,   286,
      -1,    -1,   172,   819,  1059,    -1,    -1,   179,   821,  1071,
      -1,    -1,   182,  1138,   823,  1050,   824,    -1,    -1,   108,
    1123,  1071,    -1,    -1,   183,   826,    -1,    -1,    -1,   190,
     828,  1027,  1136,   829,   727,   830,   832,    -1,   190,     1,
     130,    -1,    -1,    -1,   119,   831,   727,    -1,    -1,   130,
      -1,    -1,   197,   834,  1059,   835,   836,   837,   841,    -1,
      -1,  1140,   165,    -1,    -1,     9,  1138,   424,    -1,   840,
    1138,   424,    -1,    -1,   321,   838,    -1,   839,    -1,   838,
     839,    -1,   840,  1110,    48,  1062,    -1,    12,    -1,    15,
      -1,   262,    -1,    16,    -1,   263,    -1,   244,    -1,   245,
      -1,    -1,   104,    -1,    -1,   199,   843,   663,    -1,    -1,
     202,   845,   846,   847,    -1,  1071,    -1,  1077,    -1,  1080,
      -1,   848,    -1,   847,   848,    -1,   849,    -1,   853,    -1,
     858,    -1,    -1,   384,   850,   851,    -1,   852,    -1,   851,
     852,    -1,  1066,   169,    -1,    55,   859,    -1,     9,    -1,
     216,    -1,   400,    -1,  1066,   859,    -1,   321,   854,    -1,
     855,    -1,   854,   855,    -1,    55,    48,  1066,   859,    -1,
     856,   857,    -1,    -1,     9,    -1,   216,    -1,   167,    -1,
     400,    -1,  1066,    48,  1067,   859,    -1,    88,  1066,   393,
    1067,   859,    -1,    -1,   859,   991,   860,  1062,    -1,    -1,
     396,    -1,    -1,   237,   862,   927,    -1,    -1,   241,   864,
     865,    -1,  1062,   393,  1059,    -1,    89,  1062,   393,  1059,
      -1,    -1,   243,   867,   868,   869,    -1,  1062,    48,  1042,
    1000,    -1,  1062,    48,  1062,   180,  1042,  1000,    -1,    -1,
     131,    -1,    -1,   272,   871,   872,    -1,    -1,   872,   873,
     874,  1046,   875,    -1,   200,    -1,   278,    -1,   208,    -1,
     160,    -1,    -1,   356,  1140,   561,    -1,    -1,  1140,   251,
     334,    -1,  1140,   231,    -1,    -1,   287,   877,   878,    -1,
     881,   882,    -1,    -1,   882,   879,   727,   880,    -1,   882,
     132,    -1,    -1,   132,    -1,  1051,    -1,  1051,   390,  1051,
      -1,    -1,   171,    -1,  1069,   392,    -1,   883,   412,  1027,
      -1,   883,   425,   884,    -1,    -1,  1140,   387,   991,    -1,
     885,    -1,   884,     8,   885,    -1,  1071,   173,  1062,    48,
    1062,   412,  1027,    -1,    -1,   308,   887,  1047,  1091,  1127,
     888,   889,   890,   891,   892,    -1,    -1,   203,  1071,    -1,
      -1,   192,   231,    -1,  1140,   231,    -1,  1140,   251,   231,
      -1,  1140,   191,   231,    -1,  1140,   426,    -1,    -1,   211,
    1115,  1071,    -1,    -1,  1010,    -1,  1021,    -1,    -1,   134,
      -1,    -1,   317,   894,  1044,   989,    -1,    -1,   330,   896,
    1047,  1127,   888,  1010,   897,    -1,    -1,   135,    -1,    -1,
     335,   899,  1044,   989,   900,  1020,   901,    -1,    -1,  1140,
     231,    -1,  1140,   251,   231,    -1,    -1,   136,    -1,   337,
      -1,    -1,   345,   904,   905,   913,    -1,  1045,   907,   908,
     910,    -1,    -1,     9,  1045,   908,   427,  1028,   906,   727,
      -1,    -1,   425,  1071,    -1,    -1,    -1,  1104,   120,   909,
     727,    -1,   911,    -1,   911,   910,    -1,    -1,   427,  1027,
     912,   727,    -1,    -1,   137,    -1,    -1,   355,   915,   916,
      -1,   917,    -1,   918,    -1,   919,    -1,   921,    -1,   923,
      -1,   144,  1066,   393,  1066,    -1,  1059,   393,   143,  1065,
      -1,  1059,   393,  1062,    -1,  1059,   920,    48,  1062,    -1,
     413,    -1,   115,    -1,   922,    -1,   921,   922,    -1,  1048,
     393,   505,    -1,   924,    -1,   923,   924,    -1,  1059,   393,
     398,    -1,  1059,   393,   394,    -1,    -1,   364,   926,   927,
      -1,    -1,  1073,   929,   931,   932,   928,   933,   934,    -1,
      -1,   929,  1123,   633,  1117,   930,    -1,    -1,   930,  1073,
      -1,    -1,  1098,  1124,    -1,    -1,  1099,  1115,  1055,    -1,
      -1,   423,  1046,    -1,   200,   297,  1115,   881,    -1,    -1,
     180,  1046,    -1,   278,   297,  1115,   881,    -1,    -1,    -1,
     373,   936,  1047,   937,   938,  1020,   940,    -1,    -1,   211,
    1115,   939,  1062,    -1,  1092,  1033,    -1,  1092,  1034,    -1,
    1092,  1035,    -1,  1092,  1036,    -1,  1092,  1037,    -1,    -1,
     138,    -1,    -1,   375,   339,   942,   943,    -1,   375,   227,
      -1,    -1,   331,  1062,    -1,   180,  1062,    -1,    -1,   376,
     945,   946,   203,  1071,   948,  1005,   949,    -1,   947,    -1,
     946,   947,    -1,  1062,    -1,   106,  1106,   362,    -1,   106,
    1106,  1062,    -1,    -1,  1140,   290,  1071,    -1,    -1,   139,
      -1,    -1,   379,   951,   952,   953,    -1,  1061,   173,  1042,
    1000,    -1,  1061,   173,  1062,   180,  1042,  1000,    -1,    89,
    1071,   173,  1071,  1094,  1000,    -1,    -1,   140,    -1,   381,
     955,    -1,    -1,   296,    -1,    -1,   386,   957,   663,    -1,
      -1,   401,   959,  1071,   173,  1066,   393,  1067,    -1,    -1,
     406,   961,  1047,   962,    -1,    -1,   309,    -1,   311,    -1,
      -1,   411,   964,  1071,   965,   968,   948,   972,  1005,   973,
      -1,    -1,   106,  1106,   966,    -1,   967,    -1,   966,   274,
     967,    -1,  1088,  1066,    -1,   203,   969,    -1,   968,   969,
      -1,  1071,   970,   971,    -1,    -1,   107,  1114,  1071,    -1,
      -1,    90,  1114,  1071,    -1,    -1,   384,  1114,  1071,    -1,
      -1,   141,    -1,   975,    -1,   984,    -1,   986,    -1,   422,
     976,   978,   979,   980,   983,  1123,   977,    -1,    -1,   181,
      -1,  1046,    -1,   200,    -1,   278,    -1,   208,    -1,   160,
      -1,    -1,     8,    -1,    -1,   370,    -1,   157,    -1,   153,
      -1,   157,    -1,   279,    -1,   255,    -1,   257,    -1,    -1,
     297,    -1,   422,  1112,   101,  1123,   985,    -1,  1051,    -1,
       9,   298,    -1,   422,   976,    34,   323,  1071,    -1,    -1,
     433,   988,  1044,   989,   900,   990,   992,   993,    -1,    -1,
     173,  1068,    -1,    -1,   991,  1100,  1070,  1118,    -1,   991,
    1100,  1049,    -1,   991,  1100,   283,    -1,    34,    -1,     8,
      -1,    -1,  1015,    -1,  1021,    -1,    -1,   142,    -1,   996,
     998,    -1,   996,   998,    -1,    -1,    -1,   157,   997,   727,
      -1,    -1,    -1,   255,   999,   727,    -1,  1001,  1003,    -1,
      -1,    -1,   363,  1002,   727,    -1,    -1,    -1,   258,  1004,
     727,    -1,  1006,  1008,    -1,    -1,    -1,   279,  1007,   727,
      -1,    -1,    -1,   257,  1009,   727,    -1,  1011,    -1,  1013,
      -1,  1011,  1013,    -1,    -1,   120,  1012,   727,    -1,    -1,
     253,  1014,   727,    -1,  1016,    -1,  1018,    -1,  1016,  1018,
      -1,    -1,   148,  1017,   727,    -1,    -1,   254,  1019,   727,
      -1,    -1,  1021,    -1,  1022,    -1,  1024,    -1,  1022,  1024,
      -1,    -1,   206,  1023,   727,    -1,    -1,   256,  1025,   727,
      -1,    -1,  1106,  1070,  1118,    -1,  1028,    -1,  1029,    -1,
      -1,  1030,  1031,    -1,  1032,    -1,  1031,   207,    -1,  1031,
    1032,    -1,  1062,    -1,   445,    -1,   446,    -1,   437,    -1,
     438,    -1,   439,    -1,   440,    -1,   442,    -1,  1033,    -1,
    1034,    -1,  1035,    -1,   178,    -1,   215,    -1,   247,    -1,
     252,    -1,    20,    -1,   274,    -1,   269,    -1,   262,    -1,
      12,    -1,    13,    -1,    14,    -1,   292,    -1,   248,    -1,
     444,    -1,   150,  1138,    -1,   151,    -1,   447,    -1,   184,
    1135,    -1,   448,    -1,   219,  1135,    -1,   178,    -1,   184,
    1135,   274,   150,  1138,    -1,   215,    -1,   219,  1135,   274,
     150,  1138,    -1,  1040,    -1,  1038,  1039,  1040,    -1,    -1,
      67,    -1,   350,    -1,  1063,    -1,  1040,   437,  1040,    -1,
    1040,   438,  1040,    -1,  1040,   439,  1040,    -1,  1040,   440,
    1040,    -1,   437,  1040,    -1,   438,  1040,    -1,  1040,   442,
    1040,    -1,   445,  1040,   446,    -1,   223,    -1,   223,  1096,
     430,    -1,  1043,    -1,  1042,  1043,    -1,  1062,  1094,    -1,
    1073,    -1,  1073,    -1,  1047,    -1,  1046,  1047,    -1,   430,
      -1,  1049,    -1,  1048,  1049,    -1,   239,    -1,    -1,  1050,
    1051,    -1,  1052,    -1,  1073,    -1,  1053,    -1,  1053,  1096,
    1053,    -1,   227,    -1,  1055,    -1,  1054,  1055,    -1,  1073,
      -1,    -1,  1055,    -1,  1055,    -1,   227,    -1,   430,    -1,
    1060,    -1,  1059,  1060,    -1,  1071,    -1,     6,  1122,  1072,
      -1,  1062,    -1,  1061,  1062,    -1,  1071,    -1,   218,  1122,
    1072,    -1,   218,  1122,  1078,    -1,   218,  1122,  1080,    -1,
       6,  1122,  1064,  1065,    -1,     6,  1122,  1072,    -1,  1077,
      -1,  1080,    -1,  1041,    -1,  1071,    -1,   218,  1122,  1072,
      -1,   218,  1122,  1078,    -1,   218,  1122,  1080,    -1,  1078,
      -1,  1080,    -1,  1041,    -1,   300,    -1,   143,    -1,  1072,
      -1,   227,    -1,  1071,    -1,  1078,    -1,  1071,    -1,  1077,
      -1,  1071,    -1,   227,    -1,  1071,    -1,   227,    -1,  1080,
      -1,  1071,    -1,  1076,    -1,   436,    -1,  1072,    -1,  1073,
      -1,  1073,  1074,    -1,  1073,  1075,    -1,  1073,  1074,  1075,
      -1,   430,    -1,   430,  1096,  1073,    -1,   445,  1038,   446,
      -1,   445,  1040,   449,   446,    -1,   445,  1040,   449,  1040,
     446,    -1,   227,    -1,  1078,    -1,     9,  1079,    -1,  1079,
      -1,  1078,   450,  1079,    -1,   227,    -1,   368,    -1,   436,
      -1,   305,    -1,   188,    -1,   234,    -1,   397,    -1,    93,
    1081,    -1,   428,  1081,    -1,   420,   445,  1040,   446,  1081,
      -1,   232,   445,  1040,   446,  1081,    -1,   332,   445,  1040,
     446,  1081,    -1,    78,   445,  1038,   446,  1081,    -1,   377,
     445,  1038,   446,  1081,    -1,   378,   445,  1038,   446,  1081,
      -1,   402,   445,  1084,   446,  1081,    -1,   264,   445,  1085,
     446,    -1,   229,   445,  1086,   446,  1081,    -1,   177,  1082,
      -1,    -1,   445,  1040,   449,   446,    -1,   445,  1040,   449,
    1040,   446,    -1,    -1,   445,  1083,   446,    -1,    -1,  1038,
      -1,  1040,    -1,  1040,  1039,   216,    -1,  1040,  1039,   400,
      -1,  1040,    -1,  1040,  1039,  1040,    -1,  1040,    -1,  1040,
    1039,  1055,    -1,    -1,    -1,     9,    -1,    -1,  1098,    -1,
      -1,   198,    -1,    -1,   249,    -1,   294,    -1,    -1,   252,
      -1,    -1,   273,    -1,    -1,   338,    -1,    -1,   352,  1107,
      -1,   193,    -1,   267,    -1,   309,  1115,    -1,   311,  1101,
      -1,   429,   116,    -1,   116,    -1,    60,   353,    -1,   353,
      -1,    -1,     7,    -1,    -1,    22,    -1,    -1,    23,    -1,
      -1,    26,    -1,    -1,    29,    -1,    -1,    36,    -1,    -1,
      48,    -1,    -1,    54,    -1,    -1,    55,    -1,    -1,    81,
      -1,    -1,    96,    -1,    -1,   395,    -1,    -1,   169,    -1,
      -1,   173,    -1,    -1,   193,    -1,    -1,   207,    -1,    -1,
     207,    -1,    22,    -1,    -1,   211,    -1,    -1,   224,    -1,
     225,    -1,    -1,   225,    -1,    -1,   240,    -1,    -1,   260,
      -1,    -1,   267,    -1,    -1,   270,    -1,    -1,   275,    -1,
     193,   275,    -1,    -1,   277,    -1,    -1,   300,    -1,    -1,
     309,    -1,    -1,   336,    -1,    -1,   355,    -1,    -1,   357,
      -1,    -1,   357,    -1,   357,   207,    -1,    -1,   362,    -1,
      -1,   374,    -1,    -1,   385,    -1,    -1,   388,    -1,    -1,
     389,    -1,    -1,   392,    -1,    -1,   393,    -1,    -1,   427,
      -1,    -1,   429,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   757,   757,   757,   799,   800,   804,   805,   810,   811,
     809,   819,   820,   818,   828,   829,   827,   834,   835,   836,
     839,   840,   864,   888,   918,   917,   958,  1002,  1003,  1007,
    1008,  1011,  1012,  1016,  1023,  1030,  1034,  1038,  1050,  1051,
    1061,  1062,  1071,  1072,  1076,  1077,  1078,  1079,  1088,  1091,
    1092,  1093,  1094,  1098,  1105,  1114,  1117,  1118,  1119,  1120,
    1124,  1125,  1129,  1130,  1131,  1135,  1142,  1143,  1147,  1154,
    1166,  1169,  1170,  1174,  1175,  1179,  1183,  1190,  1191,  1201,
    1204,  1205,  1209,  1210,  1214,  1215,  1216,  1217,  1218,  1219,
    1220,  1221,  1222,  1223,  1224,  1231,  1242,  1241,  1254,  1255,
    1263,  1264,  1272,  1271,  1283,  1284,  1285,  1286,  1287,  1295,
    1296,  1301,  1302,  1304,  1303,  1315,  1316,  1320,  1321,  1322,
    1323,  1324,  1325,  1329,  1330,  1331,  1332,  1333,  1334,  1341,
    1352,  1364,  1365,  1369,  1370,  1377,  1386,  1387,  1391,  1392,
    1406,  1421,  1488,  1499,  1506,  1513,  1519,  1526,  1527,  1531,
    1530,  1540,  1539,  1555,  1556,  1559,  1560,  1565,  1564,  1585,
    1586,  1590,  1591,  1592,  1593,  1594,  1595,  1596,  1597,  1598,
    1599,  1600,  1601,  1602,  1609,  1613,  1619,  1627,  1628,  1629,
    1632,  1633,  1637,  1641,  1642,  1649,  1656,  1660,  1661,  1662,
    1669,  1694,  1704,  1713,  1715,  1716,  1722,  1726,  1727,  1728,
    1731,  1732,  1733,  1737,  1741,  1742,  1748,  1749,  1753,  1762,
    1771,  1780,  1795,  1805,  1812,  1819,  1820,  1821,  1827,  1834,
    1841,  1845,  1846,  1847,  1855,  1856,  1859,  1860,  1864,  1865,
    1869,  1870,  1876,  1901,  1902,  1903,  1904,  1910,  1917,  1918,
    1922,  1925,  1926,  1934,  1935,  1949,  1950,  1950,  1953,  1952,
    1965,  1966,  1970,  1982,  1991,  1995,  1996,  2006,  2005,  2023,
    2024,  2028,  2035,  2042,  2043,  2044,  2045,  2046,  2047,  2048,
    2049,  2050,  2057,  2061,  2061,  2061,  2067,  2079,  2104,  2128,
    2129,  2136,  2137,  2141,  2142,  2149,  2156,  2157,  2164,  2168,
    2177,  2178,  2184,  2194,  2212,  2213,  2217,  2218,  2219,  2223,
    2230,  2237,  2247,  2254,  2272,  2276,  2287,  2288,  2288,  2299,
    2300,  2304,  2304,  2321,  2322,  2324,  2328,  2330,  2329,  2361,
    2366,  2371,  2377,  2386,  2394,  2395,  2403,  2404,  2405,  2409,
    2429,  2433,  2442,  2443,  2444,  2445,  2446,  2447,  2448,  2449,
    2450,  2451,  2452,  2453,  2454,  2455,  2462,  2484,  2506,  2507,
    2519,  2539,  2546,  2547,  2551,  2552,  2553,  2554,  2555,  2556,
    2557,  2558,  2559,  2560,  2561,  2562,  2567,  2572,  2573,  2574,
    2575,  2576,  2577,  2578,  2579,  2580,  2581,  2582,  2583,  2584,
    2585,  2586,  2587,  2588,  2589,  2590,  2598,  2606,  2614,  2621,
    2626,  2637,  2654,  2655,  2658,  2659,  2666,  2690,  2691,  2708,
    2709,  2712,  2713,  2720,  2721,  2726,  2736,  2743,  2746,  2747,
    2748,  2755,  2762,  2787,  2787,  2792,  2793,  2797,  2798,  2801,
    2802,  2815,  2827,  2847,  2861,  2863,  2862,  2882,  2883,  2883,
    2896,  2898,  2897,  2909,  2910,  2914,  2915,  2924,  2931,  2934,
    2938,  2942,  2943,  2944,  2951,  2952,  2956,  2959,  2959,  2962,
    2963,  2969,  2974,  2975,  2978,  2979,  2982,  2983,  2986,  2987,
    2990,  2991,  2995,  2996,  2997,  3001,  3002,  3005,  3006,  3010,
    3014,  3015,  3019,  3020,  3021,  3022,  3023,  3024,  3025,  3026,
    3027,  3028,  3029,  3030,  3031,  3032,  3033,  3034,  3038,  3042,
    3043,  3044,  3045,  3046,  3047,  3048,  3052,  3056,  3057,  3058,
    3062,  3063,  3067,  3071,  3076,  3080,  3084,  3088,  3089,  3093,
    3094,  3098,  3099,  3100,  3103,  3103,  3103,  3106,  3110,  3113,
    3113,  3116,  3123,  3124,  3125,  3124,  3142,  3143,  3147,  3148,
    3153,  3155,  3154,  3190,  3191,  3195,  3196,  3197,  3198,  3199,
    3200,  3201,  3202,  3203,  3204,  3205,  3206,  3207,  3208,  3209,
    3210,  3211,  3215,  3219,  3223,  3227,  3228,  3229,  3230,  3231,
    3232,  3233,  3234,  3241,  3245,  3255,  3258,  3262,  3266,  3270,
    3278,  3281,  3285,  3289,  3293,  3301,  3314,  3316,  3326,  3315,
    3353,  3355,  3354,  3361,  3360,  3369,  3370,  3375,  3382,  3384,
    3388,  3398,  3400,  3408,  3416,  3445,  3476,  3478,  3488,  3493,
    3504,  3505,  3505,  3532,  3533,  3537,  3538,  3539,  3540,  3556,
    3560,  3572,  3603,  3640,  3652,  3655,  3656,  3665,  3669,  3665,
    3682,  3682,  3700,  3704,  3705,  3706,  3707,  3708,  3709,  3710,
    3711,  3712,  3713,  3714,  3715,  3716,  3717,  3718,  3719,  3720,
    3721,  3722,  3723,  3724,  3725,  3726,  3727,  3728,  3729,  3730,
    3731,  3732,  3733,  3734,  3735,  3736,  3737,  3738,  3739,  3740,
    3741,  3742,  3743,  3744,  3745,  3746,  3747,  3748,  3749,  3750,
    3751,  3752,  3775,  3774,  3787,  3791,  3795,  3799,  3803,  3807,
    3811,  3815,  3819,  3823,  3827,  3831,  3835,  3839,  3843,  3847,
    3851,  3858,  3859,  3860,  3861,  3862,  3863,  3867,  3871,  3872,
    3875,  3876,  3880,  3881,  3885,  3886,  3887,  3888,  3889,  3890,
    3891,  3892,  3896,  3900,  3904,  3909,  3910,  3911,  3912,  3913,
    3914,  3918,  3919,  3928,  3928,  3934,  3938,  3942,  3948,  3949,
    3953,  3954,  3963,  3963,  3968,  3972,  3979,  3980,  3989,  3995,
    3996,  4000,  4000,  4008,  4008,  4018,  4020,  4019,  4028,  4029,
    4034,  4041,  4048,  4050,  4054,  4062,  4073,  4074,  4075,  4080,
    4084,  4083,  4095,  4099,  4098,  4109,  4110,  4119,  4119,  4123,
    4124,  4136,  4136,  4140,  4141,  4152,  4153,  4154,  4155,  4156,
    4159,  4159,  4167,  4167,  4173,  4180,  4181,  4184,  4184,  4191,
    4204,  4217,  4217,  4228,  4229,  4239,  4238,  4251,  4255,  4259,
    4263,  4267,  4274,  4275,  4276,  4277,  4278,  4282,  4283,  4284,
    4288,  4289,  4294,  4295,  4296,  4297,  4298,  4299,  4300,  4301,
    4302,  4303,  4307,  4311,  4315,  4320,  4321,  4325,  4326,  4335,
    4335,  4341,  4345,  4349,  4353,  4357,  4364,  4365,  4374,  4374,
    4396,  4395,  4414,  4415,  4420,  4429,  4434,  4442,  4452,  4453,
    4459,  4458,  4471,  4475,  4474,  4486,  4487,  4492,  4493,  4498,
    4527,  4528,  4529,  4532,  4533,  4537,  4538,  4547,  4547,  4552,
    4553,  4561,  4578,  4595,  4613,  4638,  4638,  4651,  4651,  4664,
    4664,  4673,  4677,  4690,  4690,  4703,  4705,  4703,  4713,  4718,
    4722,  4721,  4732,  4733,  4742,  4742,  4750,  4751,  4755,  4756,
    4757,  4761,  4762,  4767,  4768,  4773,  4777,  4778,  4779,  4780,
    4781,  4782,  4783,  4787,  4788,  4797,  4797,  4810,  4809,  4819,
    4820,  4821,  4825,  4826,  4830,  4831,  4832,  4838,  4838,  4843,
    4844,  4848,  4849,  4850,  4851,  4852,  4853,  4859,  4863,  4864,
    4868,  4873,  4877,  4878,  4879,  4880,  4881,  4885,  4911,  4922,
    4923,  4927,  4927,  4935,  4935,  4945,  4945,  4950,  4954,  4966,
    4966,  4972,  4976,  4983,  4984,  4993,  4993,  4997,  4998,  5012,
    5013,  5014,  5015,  5019,  5020,  5024,  5025,  5026,  5038,  5038,
    5043,  5048,  5047,  5057,  5064,  5065,  5069,  5074,  5083,  5086,
    5090,  5095,  5102,  5109,  5110,  5114,  5115,  5120,  5132,  5132,
    5155,  5156,  5160,  5161,  5165,  5169,  5173,  5177,  5184,  5185,
    5188,  5189,  5190,  5194,  5195,  5204,  5204,  5219,  5219,  5230,
    5231,  5240,  5240,  5251,  5252,  5256,  5263,  5264,  5273,  5286,
    5286,  5292,  5297,  5296,  5307,  5308,  5312,  5314,  5313,  5324,
    5325,  5330,  5329,  5340,  5341,  5350,  5350,  5355,  5356,  5357,
    5358,  5359,  5365,  5374,  5378,  5387,  5394,  5395,  5401,  5402,
    5406,  5415,  5416,  5420,  5424,  5436,  5436,  5442,  5441,  5458,
    5461,  5477,  5478,  5481,  5482,  5486,  5487,  5492,  5497,  5505,
    5517,  5522,  5530,  5546,  5547,  5546,  5567,  5568,  5572,  5573,
    5574,  5575,  5576,  5580,  5581,  5590,  5590,  5595,  5602,  5603,
    5604,  5613,  5613,  5622,  5623,  5627,  5628,  5629,  5633,  5634,
    5638,  5639,  5648,  5648,  5654,  5658,  5662,  5669,  5670,  5679,
    5686,  5687,  5695,  5695,  5708,  5708,  5724,  5724,  5733,  5735,
    5736,  5745,  5745,  5755,  5756,  5761,  5762,  5767,  5774,  5775,
    5780,  5787,  5788,  5792,  5793,  5797,  5798,  5802,  5803,  5812,
    5813,  5814,  5818,  5842,  5845,  5853,  5863,  5868,  5873,  5878,
    5885,  5886,  5889,  5890,  5894,  5894,  5898,  5898,  5902,  5902,
    5905,  5906,  5910,  5917,  5918,  5922,  5934,  5934,  5945,  5946,
    5951,  5954,  5958,  5962,  5969,  5970,  5973,  5974,  5975,  5979,
    5980,  5993,  6001,  6008,  6010,  6009,  6019,  6021,  6020,  6035,
    6039,  6041,  6040,  6051,  6053,  6052,  6069,  6075,  6077,  6076,
    6086,  6088,  6087,  6103,  6108,  6113,  6123,  6122,  6134,  6133,
    6149,  6154,  6159,  6169,  6168,  6180,  6179,  6194,  6195,  6199,
    6204,  6209,  6219,  6218,  6230,  6229,  6246,  6249,  6261,  6268,
    6275,  6275,  6285,  6286,  6287,  6291,  6293,  6294,  6296,  6297,
    6298,  6299,  6300,  6302,  6303,  6304,  6305,  6306,  6307,  6309,
    6310,  6311,  6313,  6314,  6315,  6316,  6317,  6320,  6321,  6324,
    6324,  6324,  6325,  6325,  6326,  6326,  6327,  6327,  6328,  6328,
    6333,  6334,  6337,  6338,  6339,  6343,  6344,  6345,  6346,  6347,
    6348,  6349,  6350,  6351,  6362,  6374,  6389,  6390,  6395,  6401,
    6407,  6427,  6431,  6447,  6461,  6462,  6467,  6473,  6474,  6479,
    6488,  6489,  6490,  6494,  6505,  6506,  6510,  6518,  6519,  6523,
    6524,  6530,  6550,  6551,  6555,  6556,  6560,  6561,  6565,  6566,
    6567,  6568,  6569,  6570,  6571,  6572,  6573,  6577,  6578,  6579,
    6580,  6581,  6582,  6583,  6587,  6588,  6592,  6593,  6597,  6598,
    6602,  6603,  6614,  6615,  6619,  6620,  6621,  6625,  6626,  6627,
    6635,  6639,  6640,  6641,  6642,  6646,  6647,  6651,  6659,  6675,
    6702,  6714,  6715,  6725,  6726,  6730,  6731,  6732,  6733,  6734,
    6735,  6736,  6744,  6748,  6752,  6756,  6760,  6764,  6768,  6772,
    6776,  6780,  6784,  6788,  6795,  6796,  6797,  6801,  6802,  6806,
    6807,  6812,  6819,  6826,  6836,  6843,  6853,  6860,  6874,  6884,
    6885,  6889,  6890,  6894,  6895,  6899,  6900,  6901,  6905,  6906,
    6910,  6911,  6915,  6916,  6920,  6921,  6928,  6928,  6929,  6929,
    6930,  6930,  6931,  6931,  6933,  6933,  6934,  6934,  6935,  6935,
    6936,  6936,  6937,  6937,  6938,  6938,  6939,  6939,  6940,  6940,
    6941,  6941,  6942,  6942,  6943,  6943,  6944,  6944,  6945,  6945,
    6946,  6946,  6947,  6947,  6948,  6948,  6949,  6949,  6949,  6950,
    6950,  6951,  6951,  6951,  6952,  6952,  6953,  6953,  6954,  6954,
    6955,  6955,  6956,  6956,  6957,  6957,  6957,  6958,  6958,  6959,
    6959,  6960,  6960,  6961,  6961,  6962,  6962,  6963,  6963,  6964,
    6964,  6964,  6965,  6965,  6966,  6966,  6967,  6967,  6968,  6968,
    6969,  6969,  6970,  6970,  6971,  6971,  6973,  6973,  6974,  6974
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
  "CLOSE", "CODE", "\"CODE-SET\"", "COLLATING", "COL", "COLS", "COLUMN",
  "COLUMNS", "COMMA", "\"COMMAND-LINE\"", "\"comma delimiter\"", "COMMIT",
  "COMMON", "COMP", "COMPUTE", "\"COMP-1\"", "\"COMP-2\"", "\"COMP-3\"",
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
  "WAIT", "WHEN", "\"FUNCTION WHEN-COMPILED\"", "WITH", "\"Identifier\"",
  "WORDS", "\"WORKING-STORAGE\"", "WRITE", "YYYYDDD", "YYYYMMDD", "ZERO",
  "'+'", "'-'", "'*'", "'/'", "UNARY_SIGN", "'^'", "'.'", "'='", "'('",
  "')'", "'>'", "'<'", "':'", "'&'", "$accept", "start", "$@1",
  "nested_list", "source_element", "program_definition", "$@2", "$@3",
  "program_mandatory", "$@4", "$@5", "function_definition", "$@6", "$@7",
  "nested_prog", "end_program", "end_mandatory", "end_function",
  "identification_division", "$@8", "function_division", "program_name",
  "as_literal", "program_type", "program_type_clause", "_init_or_recurs",
  "environment_division", "configuration_section", "configuration_list",
  "configuration_paragraph", "source_computer_paragraph",
  "source_computer_entry", "with_debugging_mode", "computer_name",
  "object_computer_paragraph", "object_computer_entry",
  "object_clauses_list", "object_clauses", "object_computer_memory",
  "object_char_or_word", "object_computer_sequence",
  "object_computer_segment", "repository_paragraph", "opt_repository",
  "repository_list", "repository_name", "repository_literal_list",
  "special_names_paragraph", "opt_special_names", "special_name_list",
  "special_name", "mnemonic_name_clause", "$@9",
  "special_name_mnemonic_on_off", "on_or_off", "alphabet_name_clause",
  "$@10", "alphabet_definition", "alphabet_literal_list",
  "alphabet_literal", "@11", "alphabet_also_sequence", "alphabet_lits",
  "alphabet_also_literal", "symbolic_characters_clause",
  "symbolic_characters_list", "char_list", "integer_list",
  "class_name_clause", "class_item_list", "class_item", "locale_clause",
  "currency_sign_clause", "decimal_point_clause", "cursor_clause",
  "crt_status_clause", "screen_control", "event_status",
  "input_output_section", "$@12", "$@13", "file_control_paragraph",
  "file_control_sequence", "file_control_entry", "$@14",
  "select_clause_sequence", "select_clause", "assign_clause", "_device",
  "_ext_clause", "assignment_name", "access_mode_clause", "access_mode",
  "alternative_record_key_clause", "collating_sequence_clause",
  "file_status_clause", "file_or_sort", "lock_mode_clause", "lock_mode",
  "lock_with", "lock_records", "organization_clause", "organization",
  "padding_character_clause", "record_delimiter_clause",
  "record_key_clause", "opt_splitk", "relative_key_clause",
  "reserve_clause", "sharing_clause", "sharing_option",
  "i_o_control_paragraph", "opt_i_o_control", "i_o_control_list",
  "i_o_control_clause", "same_clause", "same_option",
  "multiple_file_tape_clause", "multiple_file_list", "multiple_file",
  "multiple_file_position", "data_division", "file_section", "$@15",
  "$@16", "file_description_sequence", "file_description",
  "file_description_sequence_without_type", "file_type",
  "file_description_entry", "@17", "file_description_clause_sequence",
  "file_description_clause", "block_contains_clause",
  "_records_or_characters", "record_clause", "record_depending",
  "opt_from_integer", "opt_to_integer", "label_records_clause",
  "label_option", "value_of_clause", "valueof_name", "data_records_clause",
  "linage_clause", "linage_sequence", "linage_lines", "linage_footing",
  "linage_top", "linage_bottom", "recording_mode_clause",
  "code_set_clause", "report_clause", "working_storage_section", "$@18",
  "record_description_list", "record_description_list_1", "$@19",
  "record_description_list_2", "data_description", "$@20", "level_number",
  "entry_name", "const_name", "const_global", "lit_or_length",
  "constant_entry", "data_description_clause_sequence",
  "data_description_clause", "redefines_clause", "external_clause",
  "as_extname", "global_clause", "picture_clause", "usage_clause", "usage",
  "sign_clause", "occurs_clause", "occurs_to_integer", "occurs_depending",
  "occurs_keys", "occurs_key_list", "ascending_or_descending",
  "occurs_indexed", "occurs_index_list", "occurs_index",
  "justified_clause", "synchronized_clause", "left_or_right",
  "blank_clause", "based_clause", "value_clause", "$@21",
  "value_item_list", "value_item", "false_is", "renames_clause",
  "any_length_clause", "local_storage_section", "$@22", "linkage_section",
  "$@23", "report_section", "$@24", "opt_report_description_list",
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
  "_indicate", "report_name", "screen_section", "$@25", "$@26",
  "opt_screen_description_list", "screen_description_list",
  "screen_description", "$@27", "screen_options", "screen_option",
  "screen_line_plus_minus", "screen_col_plus_minus",
  "screen_occurs_clause", "procedure_division", "$@28", "$@29",
  "procedure_using_chaining", "$@30", "$@31", "procedure_param_list",
  "procedure_param", "procedure_type", "size_optional",
  "procedure_optional", "procedure_returning", "procedure_declaratives",
  "$@32", "procedure_list", "procedure", "section_header",
  "paragraph_header", "invalid_statement", "section_name", "opt_segment",
  "statement_list", "@33", "@34", "statements", "$@35", "statement",
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
  "display_body", "display_upon", "with_clause", "disp_attrs", "disp_attr",
  "end_display", "divide_statement", "$@48", "divide_body", "end_divide",
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
  "coll_sequence", "_advancing", "_are", "_area", "_as", "_at", "_binary",
  "_by", "_character", "_characters", "_contains", "_data", "_file",
  "_for", "_from", "_in", "_is", "_is_are", "_key", "_line_or_lines",
  "_lines", "_mode", "_number", "_of", "_on", "_in_order", "_other",
  "_program", "_record", "_right", "_set", "_sign", "_sign_is", "_size",
  "_status", "_tape", "_than", "_then", "_times", "_to", "_when", "_with", 0
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
     685,   686,   687,   688,   689,   690,   691,    43,    45,    42,
      47,   692,    94,    46,    61,    40,    41,    62,    60,    58,
      38
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   451,   453,   452,   454,   454,   455,   455,   457,   458,
     456,   460,   461,   459,   463,   464,   462,   465,   465,   465,
     466,   466,   467,   468,   470,   469,   471,   472,   472,   473,
     473,   474,   474,   475,   475,   475,   476,   476,   477,   477,
     478,   478,   479,   479,   480,   480,   480,   480,   481,   482,
     482,   482,   482,   483,   484,   485,   486,   486,   486,   486,
     487,   487,   488,   488,   488,   489,   490,   490,   491,   492,
     493,   494,   494,   495,   495,   496,   496,   497,   497,   498,
     499,   499,   500,   500,   501,   501,   501,   501,   501,   501,
     501,   501,   501,   501,   501,   502,   503,   502,   504,   504,
     505,   505,   507,   506,   508,   508,   508,   508,   508,   509,
     509,   510,   510,   511,   510,   512,   512,   513,   513,   513,
     513,   513,   513,   514,   514,   514,   514,   514,   514,   515,
     516,   517,   517,   518,   518,   519,   520,   520,   521,   521,
     522,   523,   524,   525,   526,   527,   528,   529,   529,   530,
     529,   531,   529,   532,   532,   533,   533,   535,   534,   536,
     536,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   538,   538,   538,   539,   539,   539,
     540,   540,   540,   541,   541,   541,   542,   543,   543,   543,
     544,   545,   546,   547,   547,   547,   548,   549,   549,   549,
     550,   550,   550,   550,   551,   551,   552,   552,   553,   553,
     553,   553,   554,   555,   556,   557,   557,   557,   558,   559,
     560,   561,   561,   561,   562,   562,   563,   563,   564,   564,
     565,   565,   566,   567,   567,   567,   567,   568,   569,   569,
     570,   571,   571,   572,   572,   573,   574,   573,   575,   573,
     576,   576,   577,   578,   578,   579,   579,   581,   580,   582,
     582,   583,   583,   583,   583,   583,   583,   583,   583,   583,
     583,   583,   584,   585,   585,   585,   586,   586,   586,   587,
     587,   588,   588,   589,   589,   590,   591,   591,   592,   592,
     593,   593,   594,   595,   596,   596,   597,   597,   597,   598,
     599,   600,   601,   602,   603,   603,   604,   605,   604,   606,
     606,   608,   607,   609,   609,   609,   610,   611,   610,   612,
     613,   613,   613,   614,   615,   615,   616,   616,   616,   617,
     618,   618,   619,   619,   619,   619,   619,   619,   619,   619,
     619,   619,   619,   619,   619,   619,   620,   621,   622,   622,
     623,   624,   625,   625,   626,   626,   626,   626,   626,   626,
     626,   626,   626,   626,   626,   626,   626,   626,   626,   626,
     626,   626,   626,   626,   626,   626,   626,   626,   626,   626,
     626,   626,   626,   626,   626,   626,   626,   626,   626,   627,
     627,   628,   629,   629,   630,   630,   631,   632,   632,   633,
     633,   634,   634,   635,   635,   636,   637,   638,   639,   639,
     639,   640,   641,   643,   642,   644,   644,   645,   645,   646,
     646,   647,   647,   648,   649,   650,   649,   651,   652,   651,
     653,   654,   653,   655,   655,   656,   656,   657,   658,   658,
     659,   659,   659,   659,   660,   660,   661,   662,   662,   663,
     663,   664,   665,   665,   666,   666,   667,   667,   668,   668,
     669,   669,   670,   670,   670,   671,   671,   672,   672,   673,
     674,   674,   675,   675,   675,   675,   675,   675,   675,   675,
     675,   675,   675,   675,   675,   675,   675,   675,   676,   677,
     677,   677,   677,   677,   677,   677,   678,   679,   679,   679,
     680,   680,   681,   682,   683,   684,   685,   686,   686,   687,
     687,   688,   688,   688,   689,   689,   689,   690,   691,   692,
     692,   693,   694,   695,   696,   694,   697,   697,   698,   698,
     699,   700,   699,   701,   701,   702,   702,   702,   702,   702,
     702,   702,   702,   702,   702,   702,   702,   702,   702,   702,
     702,   702,   702,   702,   702,   702,   702,   702,   702,   702,
     702,   702,   702,   702,   702,   703,   703,   703,   703,   703,
     704,   704,   704,   704,   704,   705,   706,   707,   708,   706,
     709,   710,   709,   711,   709,   712,   712,   713,   714,   714,
     714,   715,   715,   715,   715,   715,   716,   716,   717,   717,
     718,   719,   718,   720,   720,   721,   721,   721,   721,   721,
     721,   722,   723,   724,   725,   726,   726,   728,   729,   727,
     731,   730,   730,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   732,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   732,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   732,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   732,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   734,   733,   735,   735,   735,   735,   735,   735,
     735,   735,   735,   735,   735,   735,   735,   735,   735,   735,
     735,   736,   736,   736,   736,   736,   736,   737,   738,   738,
     739,   739,   740,   740,   741,   741,   741,   741,   741,   741,
     741,   741,   741,   741,   741,   741,   741,   741,   741,   741,
     741,   742,   742,   744,   743,   745,   745,   745,   746,   746,
     747,   747,   749,   748,   750,   750,   751,   751,   752,   753,
     753,   754,   754,   756,   755,   757,   758,   757,   759,   759,
     760,   760,   761,   761,   761,   761,   762,   762,   762,   763,
     764,   763,   765,   766,   765,   767,   767,   769,   768,   770,
     770,   772,   771,   773,   773,   774,   774,   774,   774,   774,
     775,   775,   777,   776,   778,   779,   779,   780,   780,   781,
     782,   784,   783,   785,   785,   787,   786,   788,   788,   788,
     788,   788,   789,   789,   789,   789,   789,   790,   790,   790,
     791,   791,   792,   792,   792,   792,   792,   792,   792,   792,
     792,   792,   792,   792,   792,   792,   792,   793,   793,   795,
     794,   796,   796,   796,   796,   796,   797,   797,   799,   798,
     801,   800,   802,   802,   803,   803,   803,   804,   805,   805,
     807,   806,   808,   809,   808,   810,   810,   811,   811,   812,
     812,   812,   812,   813,   813,   814,   814,   816,   815,   817,
     817,   817,   817,   817,   817,   819,   818,   821,   820,   823,
     822,   824,   824,   826,   825,   828,   829,   827,   827,   830,
     831,   830,   832,   832,   834,   833,   835,   835,   836,   836,
     836,   837,   837,   838,   838,   839,   840,   840,   840,   840,
     840,   840,   840,   841,   841,   843,   842,   845,   844,   846,
     846,   846,   847,   847,   848,   848,   848,   850,   849,   851,
     851,   852,   852,   852,   852,   852,   852,   853,   854,   854,
     855,   855,   856,   856,   856,   856,   856,   857,   858,   859,
     859,   860,   860,   862,   861,   864,   863,   865,   865,   867,
     866,   868,   868,   869,   869,   871,   870,   872,   872,   873,
     873,   873,   873,   874,   874,   875,   875,   875,   877,   876,
     878,   879,   878,   878,   880,   880,   881,   881,   882,   882,
     882,   882,   882,   883,   883,   884,   884,   885,   887,   886,
     888,   888,   889,   889,   889,   889,   889,   889,   890,   890,
     891,   891,   891,   892,   892,   894,   893,   896,   895,   897,
     897,   899,   898,   900,   900,   900,   901,   901,   902,   904,
     903,   905,   906,   905,   907,   907,   908,   909,   908,   910,
     910,   912,   911,   913,   913,   915,   914,   916,   916,   916,
     916,   916,   917,   918,   918,   919,   920,   920,   921,   921,
     922,   923,   923,   924,   924,   926,   925,   928,   927,   929,
     929,   930,   930,   931,   931,   932,   932,   933,   933,   933,
     934,   934,   934,   936,   937,   935,   938,   938,   939,   939,
     939,   939,   939,   940,   940,   942,   941,   941,   943,   943,
     943,   945,   944,   946,   946,   947,   947,   947,   948,   948,
     949,   949,   951,   950,   952,   952,   952,   953,   953,   954,
     955,   955,   957,   956,   959,   958,   961,   960,   962,   962,
     962,   964,   963,   965,   965,   966,   966,   967,   968,   968,
     969,   970,   970,   971,   971,   972,   972,   973,   973,   974,
     974,   974,   975,   976,   976,   977,   977,   977,   977,   977,
     978,   978,   979,   979,   980,   980,   981,   981,   982,   982,
     983,   983,   984,   985,   985,   986,   988,   987,   989,   989,
     990,   990,   990,   990,   991,   991,   992,   992,   992,   993,
     993,   994,   995,   996,   997,   996,   998,   999,   998,  1000,
    1001,  1002,  1001,  1003,  1004,  1003,  1005,  1006,  1007,  1006,
    1008,  1009,  1008,  1010,  1010,  1010,  1012,  1011,  1014,  1013,
    1015,  1015,  1015,  1017,  1016,  1019,  1018,  1020,  1020,  1021,
    1021,  1021,  1023,  1022,  1025,  1024,  1026,  1026,  1027,  1028,
    1030,  1029,  1031,  1031,  1031,  1032,  1032,  1032,  1032,  1032,
    1032,  1032,  1032,  1032,  1032,  1032,  1032,  1032,  1032,  1032,
    1032,  1032,  1032,  1032,  1032,  1032,  1032,  1032,  1032,  1033,
    1033,  1033,  1034,  1034,  1035,  1035,  1036,  1036,  1037,  1037,
    1038,  1038,  1039,  1039,  1039,  1040,  1040,  1040,  1040,  1040,
    1040,  1040,  1040,  1040,  1041,  1041,  1042,  1042,  1043,  1044,
    1045,  1046,  1046,  1047,  1048,  1048,  1049,  1050,  1050,  1051,
    1052,  1052,  1052,  1053,  1054,  1054,  1055,  1056,  1056,  1057,
    1057,  1058,  1059,  1059,  1060,  1060,  1061,  1061,  1062,  1062,
    1062,  1062,  1062,  1062,  1062,  1062,  1062,  1063,  1063,  1063,
    1063,  1063,  1063,  1063,  1064,  1064,  1065,  1065,  1066,  1066,
    1067,  1067,  1068,  1068,  1069,  1069,  1069,  1070,  1070,  1070,
    1071,  1072,  1072,  1072,  1072,  1073,  1073,  1074,  1075,  1075,
    1076,  1077,  1077,  1078,  1078,  1079,  1079,  1079,  1079,  1079,
    1079,  1079,  1080,  1080,  1080,  1080,  1080,  1080,  1080,  1080,
    1080,  1080,  1080,  1080,  1081,  1081,  1081,  1082,  1082,  1083,
    1083,  1084,  1084,  1084,  1085,  1085,  1086,  1086,  1087,  1088,
    1088,  1089,  1089,  1090,  1090,  1091,  1091,  1091,  1092,  1092,
    1093,  1093,  1094,  1094,  1095,  1095,  1096,  1096,  1097,  1097,
    1098,  1098,  1099,  1099,  1100,  1100,  1101,  1101,  1102,  1102,
    1103,  1103,  1104,  1104,  1105,  1105,  1106,  1106,  1107,  1107,
    1108,  1108,  1109,  1109,  1110,  1110,  1111,  1111,  1112,  1112,
    1113,  1113,  1114,  1114,  1115,  1115,  1116,  1116,  1116,  1117,
    1117,  1118,  1118,  1118,  1119,  1119,  1120,  1120,  1121,  1121,
    1122,  1122,  1123,  1123,  1124,  1124,  1124,  1125,  1125,  1126,
    1126,  1127,  1127,  1128,  1128,  1129,  1129,  1130,  1130,  1131,
    1131,  1131,  1132,  1132,  1133,  1133,  1134,  1134,  1135,  1135,
    1136,  1136,  1137,  1137,  1138,  1138,  1139,  1139,  1140,  1140
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
       1,     1,     1,     1,     1,     3,     0,     5,     0,     5,
       1,     1,     0,     5,     1,     1,     1,     1,     1,     1,
       2,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     2,     1,     2,     4,     1,     2,     1,     3,
       4,     4,     3,     3,     4,     3,     3,     0,     5,     0,
       4,     0,     4,     0,     3,     0,     2,     0,     6,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     4,     4,     0,     1,     1,
       0,     1,     1,     1,     1,     1,     4,     1,     1,     1,
       6,     3,     5,     0,     1,     1,     4,     2,     2,     1,
       0,     4,     5,     2,     1,     1,     3,     1,     1,     3,
       1,     2,     4,     4,     4,     1,     3,     4,     4,     3,
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
       1,     4,     2,     1,     1,     0,     1,     0,     0,     3,
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
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
       1,     0,     6,     0,     1,     0,     4,     3,     3,     3,
       3,     5,     0,     2,     2,     2,     2,     0,     2,     2,
       1,     2,     1,     1,     2,     2,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     1,     1,     0,     1,     0,
       4,     4,     6,     6,     8,     8,     0,     1,     0,     4,
       0,     5,     1,     3,     1,     1,     1,     2,     1,     2,
       0,     3,     0,     0,     4,     2,     3,     1,     3,     2,
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
       0,     2,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     2,     1,     2,     1,     5,     1,     5,
       1,     3,     0,     1,     1,     1,     3,     3,     3,     3,
       2,     2,     3,     3,     1,     3,     1,     2,     2,     1,
       1,     1,     2,     1,     1,     2,     1,     0,     2,     1,
       1,     1,     3,     1,     1,     2,     1,     0,     1,     1,
       1,     1,     1,     2,     1,     3,     1,     2,     1,     3,
       3,     3,     4,     3,     1,     1,     1,     1,     3,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     3,     1,     3,     3,     4,     5,
       1,     1,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     5,     5,     5,     5,     5,     5,
       5,     4,     5,     2,     0,     4,     5,     0,     3,     0,
       1,     1,     3,     3,     1,     3,     1,     3,     0,     0,
       1,     0,     1,     0,     1,     0,     1,     1,     0,     1,
       0,     1,     0,     1,     0,     2,     1,     1,     2,     2,
       2,     1,     2,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     1,     0,
       1,     0,     1,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     2,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     2,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     3,     4,     6,     7,
      38,    38,     0,     0,     5,     0,     8,    14,    28,    27,
      29,    29,     0,   243,   243,     0,     0,    24,    40,     0,
       9,    15,    30,    26,  1464,     0,   147,     0,   576,   576,
    1465,     0,     0,     0,     0,     0,     0,    39,   245,     0,
      17,     0,    25,    33,    37,    36,  1489,    35,    42,   149,
       0,   151,   255,   256,     0,   306,   248,   580,    18,    20,
      38,     0,    16,    34,  1490,    32,    41,   155,   153,   226,
       0,     0,   424,     0,   583,   581,   598,     0,    19,    10,
      11,     0,     0,     0,     0,     0,    43,    44,    45,    47,
      46,   150,     0,   224,  1456,   233,   152,     0,   228,   230,
     231,   246,     0,     0,   427,  1303,   249,   309,   257,   588,
     588,     0,     0,     0,   243,    23,    56,    71,    49,    80,
    1420,   156,   155,     0,   148,  1457,  1506,   234,   235,   236,
    1438,   227,   229,   250,   307,     0,     0,   430,   254,     0,
     253,   310,  1408,   259,  1447,   588,   585,   591,     0,   588,
     599,   577,    21,    12,     0,  1464,    54,  1489,    55,  1489,
      60,    62,    63,    64,     0,     0,    70,     0,    73,  1519,
      48,     0,  1518,     0,     0,     0,     0,  1497,  1464,  1464,
    1464,     0,  1464,  1450,  1464,    79,     0,    82,    84,    85,
      86,    88,    87,    89,    90,    91,    92,    93,    94,  1421,
       0,   154,   226,  1507,  1452,  1439,  1458,   247,   309,   425,
       0,     0,   522,   309,   312,     0,  1464,   586,  1464,     0,
     596,   589,   590,   600,   576,  1464,     0,    57,  1489,    59,
      61,     0,  1433,  1464,     0,    77,     0,    72,    74,    52,
      50,     0,     0,  1321,   102,  1464,  1464,  1498,  1464,     0,
       0,     0,  1464,     0,  1451,     0,     0,    81,    83,   157,
     225,  1453,     0,  1459,     0,   251,   308,   309,   428,     0,
       0,   244,   252,   315,     0,   319,     0,   320,   316,  1452,
    1464,     0,     0,  1464,  1452,  1476,  1464,  1436,     0,   258,
     260,   263,   264,   265,   266,   267,   268,   269,   270,   271,
       0,     0,  1464,   597,     0,     0,   578,    17,     0,  1370,
      69,    58,  1432,     0,    76,    75,    78,    51,    53,  1464,
       0,     0,     0,  1365,   143,  1316,   142,   146,     0,   145,
     129,  1466,   131,    95,    96,   159,   237,   238,   241,   232,
    1301,   426,   309,   431,     0,     0,   313,   321,   322,   317,
       0,     0,     0,  1464,  1436,     0,     0,     0,     0,     0,
    1477,  1464,     0,  1437,     0,     0,   261,   262,   592,   593,
     595,     0,   587,   601,   603,     0,     0,    68,     0,  1379,
    1375,  1380,  1378,  1376,  1381,  1377,   135,   136,   138,   144,
     141,  1426,  1427,     0,   140,  1468,  1467,   132,     0,    98,
    1491,   239,     0,   240,  1302,   429,   433,   523,   314,   330,
     324,   283,   303,  1428,  1429,   292,  1314,   287,   286,   285,
    1320,  1319,  1474,  1450,  1462,     0,   521,   304,   305,  1464,
    1464,   594,   603,     0,     0,    13,    66,    67,    65,   107,
     121,   117,   122,   104,   120,   118,   105,   106,   119,   103,
     108,   109,   111,   137,     0,  1366,   130,   133,    97,  1476,
       0,  1514,   208,     0,  1476,  1464,  1448,  1469,   210,     0,
    1518,   195,   194,   158,   160,   161,   162,   163,   164,   165,
       0,   166,   167,   207,   168,   169,   170,   171,   172,   173,
    1464,  1444,   242,     0,   432,   434,   435,   524,  1464,  1440,
       0,     0,   273,  1315,  1475,   294,     0,   276,  1463,  1502,
     302,     0,     0,     0,     0,   614,   610,   604,   605,   606,
     607,   613,     0,     0,     0,   110,   113,     0,   139,   134,
     101,   100,  1504,  1464,  1469,  1515,   180,   211,  1464,  1491,
    1449,  1464,  1464,  1470,  1464,  1464,  1438,     0,  1464,     0,
    1445,     0,   438,   436,   526,     0,   412,   354,   387,   375,
     384,   381,   378,  1516,   355,   356,   357,   358,   359,   360,
     361,   362,   363,  1493,   388,     0,   364,   351,   365,   366,
       0,     0,  1500,   368,   369,   367,   408,   371,   372,   370,
    1464,  1466,   331,   332,   333,   334,   335,   336,   352,   337,
     338,   339,   340,   341,   342,   343,   344,   345,     0,     0,
    1441,     0,   325,   284,   275,   274,   272,   293,  1450,  1503,
     281,   290,   289,   291,   288,     0,   609,   612,   615,   672,
     723,   732,   739,   743,   767,   771,   789,   782,   790,   791,
     795,   829,   838,   840,   867,   875,   877,  1514,   883,     0,
     894,   915,   917,   953,   955,   959,   671,   965,   978,   998,
    1015,  1017,  1021,  1028,  1029,  1045,  1065,  1083,     0,  1101,
    1112,  1120,  1122,  1124,  1126,  1131,  1153,  1176,   608,   622,
     623,   624,   625,   626,   627,   628,   629,   631,   630,   632,
     633,   634,   635,   636,   637,   638,   639,   640,   641,   642,
     643,   644,   645,   646,   647,   648,   649,   650,   651,   652,
     653,   654,   655,   656,   657,   658,   659,   660,   661,   662,
     663,   664,   665,   666,   667,   668,   669,  1149,  1150,  1151,
     670,   621,    22,     0,   112,  1505,  1464,     0,  1464,   182,
     181,   177,     0,  1492,   210,   206,     0,     0,     0,     0,
     219,  1487,  1487,     0,   220,     0,   191,   209,  1464,   320,
     530,   525,   527,   528,   423,   385,   386,   373,   374,   382,
     383,   379,   380,   376,   377,  1517,     0,  1494,   406,   392,
     346,  1361,   421,  1501,   409,   410,   407,     0,     0,   348,
     350,  1424,  1424,     0,  1480,  1480,   329,   326,  1371,  1373,
    1443,   295,   296,   297,   298,     0,     0,   277,  1461,   283,
       0,     0,   616,     0,     0,     0,  1240,   738,     0,   769,
     773,     0,     0,     0,     0,     0,  1240,   869,     0,     0,
     879,   884,     0,  1240,     0,     0,     0,     0,     0,     0,
     967,   988,     0,     0,     0,     0,     0,     0,     0,     0,
    1097,  1095,     0,     0,  1121,  1119,     0,     0,     0,     0,
    1154,  1160,     0,     0,   127,   123,   128,   126,   124,   125,
     114,   115,     0,   188,   189,   187,   186,     0,   175,   176,
       0,   200,   199,   200,   196,   212,   213,   214,   215,   218,
    1488,   221,   222,   223,  1317,  1464,   447,   447,  1466,   467,
     439,   442,   443,     0,   531,   529,   411,     0,  1512,     0,
    1362,  1363,     0,   353,   413,   415,   417,     0,   347,  1448,
     389,   390,  1372,  1481,     0,     0,     0,     0,     0,  1442,
    1450,   282,   602,   611,   721,   691,  1360,  1480,     0,     0,
    1394,  1397,  1480,  1294,     0,     0,     0,     0,     0,     0,
       0,     0,  1394,   730,  1336,   728,  1326,  1328,  1334,  1335,
    1413,   733,     0,  1239,     0,  1313,     0,  1309,  1311,  1310,
    1355,   745,  1354,  1356,   768,   772,   785,     0,  1296,  1422,
    1491,  1375,   827,   691,     0,  1328,   836,     0,   745,   846,
     845,     0,   842,   844,   874,   871,   870,   873,   868,  1480,
     876,  1322,  1324,   878,  1307,   888,  1510,  1238,   896,   916,
     449,     0,   919,   920,   921,   954,  1069,     0,   956,     0,
     963,     0,   966,   989,  1313,   979,   988,   981,     0,   986,
       0,  1310,     0,  1415,  1178,  1299,  1491,  1178,     0,  1043,
    1034,  1300,     0,  1306,  1046,  1047,  1048,  1049,  1050,  1058,
    1051,  1061,     0,  1304,     0,  1066,  1084,  1098,  1446,     0,
    1103,  1105,     0,  1117,     0,  1123,     0,  1128,  1133,  1161,
       0,  1162,  1482,  1178,     0,    99,  1411,   184,   183,   174,
     185,     0,   198,   197,  1464,     0,  1318,   192,     0,   448,
     444,     0,   445,     0,   437,   440,   533,   393,  1513,   394,
    1480,     0,     0,     0,  1282,  1280,  1343,  1285,  1337,  1341,
    1342,     0,  1364,   422,  1516,   416,     0,   349,  1425,   328,
     327,  1374,   301,  1474,     0,   279,   722,   673,  1443,     0,
     700,     0,     0,     0,     0,     0,  1382,  1399,  1393,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1383,
     731,   724,     0,     0,  1327,  1414,   736,  1413,  1264,  1265,
    1266,  1260,  1514,  1271,  1256,  1508,  1257,  1508,  1258,  1268,
    1259,  1263,  1262,  1261,  1267,  1248,  1249,  1250,  1251,  1252,
    1269,  1246,  1247,  1272,  1274,  1241,  1242,  1253,  1254,  1255,
    1245,   741,     0,   746,   756,  1353,   770,  1352,   775,   786,
     783,   788,   787,  1240,  1297,  1423,  1298,  1227,   828,   796,
     802,  1193,  1193,  1193,  1193,   837,   830,     0,     0,   839,
    1240,  1240,   865,   852,   848,   850,   872,     0,  1323,   881,
    1511,   886,   898,     0,   450,     0,   942,   927,   918,   922,
     924,   925,   926,  1073,     0,     0,   964,   960,     0,   972,
     969,   971,   970,   973,   980,   983,   617,  1240,     0,     0,
     990,     0,  1416,  1417,  1491,     0,  1016,  1000,  1023,  1036,
    1044,  1030,     0,  1036,     0,  1348,  1349,  1059,  1062,     0,
       0,  1305,  1057,     0,  1056,     0,  1086,     0,     0,  1096,
       0,     0,  1104,     0,  1118,  1113,     0,     0,  1129,  1130,
    1127,  1446,     0,     0,  1163,     0,  1483,     0,  1023,   116,
    1431,     0,   190,  1412,     0,   203,     0,   216,   441,   446,
     452,   462,   320,   468,  1499,  1482,   397,     0,  1290,  1291,
       0,  1283,  1284,  1367,     0,     0,     0,     0,     0,     0,
       0,     0,  1495,   418,   300,  1474,  1482,   278,   696,   687,
    1193,   677,   684,   678,   680,   682,     0,  1193,     0,   676,
     683,   690,   689,     0,  1193,  1478,  1478,  1478,   694,   695,
    1345,  1344,     0,  1333,  1282,  1280,     0,     0,  1282,     0,
    1329,  1330,  1331,  1295,  1282,     0,     0,  1282,     0,     0,
    1282,  1282,  1282,     0,     0,  1200,  1422,     0,     0,   734,
       0,  1270,  1509,  1273,  1275,  1243,  1244,     0,     0,  1312,
     752,     0,     0,   759,   780,   781,   774,   776,     0,  1200,
    1232,  1234,   793,  1228,  1229,  1230,     0,   807,  1194,   799,
    1196,   800,   797,   798,     0,  1200,  1422,   843,   860,   862,
     861,   855,   857,   863,   866,   841,  1240,   849,   847,  1240,
     617,  1325,  1482,   880,  1308,   617,  1514,   906,   907,   909,
     911,   912,   908,   910,   901,  1514,   897,     0,   943,     0,
     945,   944,   946,   937,   938,     0,     0,   923,  1075,  1484,
       0,     0,   957,  1200,  1422,  1518,     0,   984,   618,   991,
     992,   995,     0,   987,  1185,  1184,   994,  1000,  1179,     0,
       0,  1227,     0,     0,     0,  1035,     0,     0,     0,  1060,
       0,  1064,  1063,  1054,     0,  1464,  1227,  1100,  1099,  1106,
    1107,  1108,     0,  1200,  1422,     0,  1409,     0,  1108,  1175,
    1165,  1164,  1170,     0,  1172,  1173,  1180,  1430,     0,   217,
    1464,   454,   465,   466,   464,   322,   470,   546,  1464,   537,
     535,   536,   538,  1478,     0,  1464,     0,   549,   541,  1478,
     542,     0,   545,   550,   548,   543,   547,     0,   544,     0,
     532,   560,   555,   558,   557,   556,   559,   534,   561,     0,
     401,   396,  1338,  1339,  1340,  1293,  1281,  1286,  1287,  1288,
    1289,  1292,  1368,     0,  1496,  1514,   299,     0,   688,  1196,
     679,   681,  1193,   685,   675,   715,  1464,   704,   705,  1464,
     716,   706,   707,   710,   720,   717,   708,     0,   718,   709,
     719,   701,   702,   674,  1479,     0,     0,     0,   692,   693,
    1347,  1332,  1346,  1394,  1422,     0,  1398,     0,  1394,  1394,
       0,  1391,  1394,  1394,  1394,     0,  1394,  1394,  1201,   725,
    1203,  1200,   737,     0,   742,   740,   747,   748,   591,     0,
     758,   757,  1166,  1167,   762,   760,     0,   779,     0,   784,
     617,   617,   794,   792,  1231,   806,   805,   804,   803,  1519,
    1193,     0,   617,  1197,  1192,     0,   831,     0,  1240,  1240,
     859,   853,   856,   851,     0,   889,     0,     0,   913,     0,
       0,     0,   939,   941,     0,   933,   949,   934,   935,   928,
     929,   949,  1067,  1464,     0,  1485,  1074,   399,   400,  1469,
     958,   961,     0,     0,   975,   985,   982,   620,     0,     0,
    1002,  1001,  1216,  1218,  1019,  1213,  1214,  1026,  1024,     0,
    1240,  1037,  1240,  1031,  1039,  1052,  1053,  1055,  1418,  1093,
    1207,     0,  1422,  1114,     0,     0,  1410,  1134,  1135,     0,
    1138,  1141,  1145,  1139,  1171,  1482,  1174,  1186,  1434,     0,
     204,   205,   201,     0,     0,   456,     0,  1499,     0,  1464,
     539,   540,     0,   563,  1464,  1512,   564,   562,   395,  1446,
     391,  1469,  1369,   419,   280,  1191,   686,     0,     0,  1236,
    1236,   703,   698,   697,   699,  1387,  1200,  1395,     0,  1407,
    1392,  1385,  1405,  1386,  1388,  1389,  1402,  1403,  1390,  1384,
     617,  1204,  1199,   726,   735,   749,   750,     0,   754,   753,
     755,  1168,  1169,   765,   763,   617,   777,   778,  1233,  1235,
    1464,   812,   825,   826,   813,     0,  1464,   816,   817,   820,
     818,     0,   819,   809,   810,   801,   808,  1195,   617,  1200,
    1296,  1200,  1296,   858,   864,   617,   882,   890,   892,   899,
     902,   903,  1454,   914,   895,   900,   949,  1350,  1351,   949,
       0,   932,   930,   931,   936,  1077,     0,  1486,  1071,  1200,
     974,   968,     0,   619,   996,     0,     0,  1008,     0,   617,
     617,  1020,  1018,  1215,  1027,  1022,  1025,  1032,   617,  1041,
    1040,  1419,     0,     0,  1094,  1085,  1208,  1110,  1210,     0,
    1200,  1200,  1125,  1409,  1137,  1462,  1143,  1462,  1207,     0,
    1223,  1225,  1189,  1187,  1220,  1221,  1188,  1435,     0,   202,
     453,  1464,     0,   458,   463,  1478,   499,   519,   514,  1436,
       0,     0,  1464,  1480,  1464,     0,   469,   475,   476,   477,
     486,   478,   480,   483,   471,   472,   473,   479,   482,   500,
     484,   487,   474,     0,   481,   485,  1359,   554,  1357,  1358,
     570,   553,   565,   575,     0,  1464,  1464,   414,   712,   711,
     714,     0,   713,   727,  1396,  1202,   617,   751,   766,   744,
     617,   761,     0,   814,   815,     0,  1236,  1236,   811,  1198,
     833,     0,   832,     0,   854,   617,   893,   887,   904,  1455,
       0,   948,   940,   949,   951,     0,     0,  1080,  1076,  1070,
     962,   977,     0,     0,  1003,  1464,  1010,     0,  1004,     0,
    1007,  1217,  1219,   617,  1038,   617,  1087,  1276,  1508,  1278,
    1508,  1088,  1089,  1090,  1091,  1092,   617,  1111,  1102,  1211,
    1206,  1109,  1116,  1115,  1136,     0,  1462,  1140,     0,  1147,
    1159,  1156,  1158,  1157,  1152,  1155,   617,   617,  1190,  1177,
    1222,  1183,  1182,  1471,     0,  1464,  1464,   460,   498,  1464,
     520,   518,   515,   516,  1466,   508,  1464,  1240,     0,     0,
       0,     0,   501,     0,     0,   506,   509,   512,   573,   571,
     572,   574,     0,   568,   566,   567,   569,     0,   405,   402,
     403,     0,     0,  1471,  1205,   764,   822,   821,   824,   823,
    1200,  1200,   891,     0,   947,   952,     0,  1464,  1078,     0,
       0,  1068,  1072,   976,     0,     0,  1013,  1011,  1012,  1006,
    1005,  1033,  1042,  1273,  1275,  1209,   617,  1142,     0,  1146,
    1148,  1132,  1224,  1226,  1472,  1473,  1181,   455,     0,     0,
    1464,   451,     0,   507,     0,   504,  1422,   502,   503,   493,
     491,   492,   494,   490,   495,   489,   488,     0,   513,   511,
     510,   552,   551,   404,   398,   420,  1237,   835,   834,   905,
     950,     0,  1081,  1464,  1240,  1009,  1014,   999,     0,     0,
    1212,  1144,   457,   459,     0,   497,   496,   517,     0,  1079,
       0,   997,  1514,  1514,   461,     0,  1082,  1277,  1279,   505
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,     7,     8,    23,    38,    68,   124,
     234,     9,    24,    39,    69,    89,   445,    72,    70,    34,
      11,    20,    26,    41,    56,    57,    16,    36,    76,    96,
      97,   180,   181,   167,    98,   168,   169,   170,   171,   448,
     172,   173,    99,   176,   177,   178,   246,   100,   195,   196,
     197,   198,   409,   468,   542,   199,   329,   459,   460,   461,
     743,   880,   462,   881,   200,   340,   341,   466,   201,   396,
     397,   202,   203,   204,   205,   206,   207,   208,    47,    77,
      79,   103,   101,   131,   345,   410,   484,   485,   890,   751,
    1089,   486,   886,   487,   488,   489,   490,   491,   894,  1092,
    1782,   492,   493,   494,   495,   496,   897,   497,   498,   499,
     764,   134,   106,   107,   108,   109,   140,   110,   346,   347,
     413,    30,    65,   143,    83,   217,   148,   116,   149,   117,
     153,   226,   300,   301,   626,   302,  1357,   819,   512,   303,
     429,   304,   632,   305,   306,   627,   811,   812,   813,   814,
     307,   308,   309,    82,   218,   150,   151,   152,   224,   286,
     419,   287,   359,   360,   509,   806,   288,   508,   602,   603,
     604,   928,   605,   606,   607,   608,   609,   610,   918,  1336,
    1590,  1591,  1729,  1800,  2129,  2130,   611,   612,   796,   613,
     614,   615,  1124,   924,   925,  1997,   616,   617,   114,   277,
     147,   352,   222,   416,   504,   505,   506,   768,   910,   911,
    1100,  1101,  1019,   912,  1551,  1785,  1953,  2097,  2181,  1330,
    1554,  1104,  1333,  1787,  1974,  1975,  2196,  1976,  1977,  1978,
    1979,  2187,  1980,  1981,  1982,  1983,  2115,  2116,  2104,  1984,
    1985,  2101,   437,   281,   507,   564,   771,   772,   773,  1106,
    1334,  1587,  2127,  2122,  1588,    50,   233,   384,    86,   120,
     119,   155,   156,   157,   230,   314,   122,   316,   442,   443,
     527,   528,   529,   530,   531,   823,  1497,  1498,  1737,   532,
     533,   689,   690,   824,   944,  1140,  1378,  1379,  1374,  1631,
    1632,  1137,   691,   825,   963,  1163,  1161,   692,   826,   971,
    1409,   693,   827,  1418,   694,   828,  1204,  1420,  1666,  1667,
    1668,  1423,  1674,  1845,  1843,  2010,  2009,   695,   829,   984,
     696,   830,   985,  1426,  1427,   697,   831,   986,  1210,  1213,
     698,   699,   700,   832,  1683,   701,   833,   992,  1437,  1690,
    1863,  1864,  1219,   702,   834,   996,  1226,   703,   835,   704,
     836,  1001,  1002,  1232,  1233,  1234,  1460,  1458,  1875,  1235,
    1451,  1452,  1700,  1455,   705,   837,  1008,   706,   838,   707,
     839,   708,  1014,  1463,   709,   841,   710,   843,  1465,  1878,
    2025,  2027,   711,   844,  1242,  1474,  1708,  1880,  1881,  1882,
    1884,   712,   845,   713,   846,  1021,  1248,  1249,  1250,  1486,
    1719,  1720,  1251,  1483,  1484,  1485,  1713,  1252,  1891,  2146,
     714,   847,   715,   848,  1028,   716,   849,  1030,  1257,   717,
     850,  1032,  1263,  1496,  1901,   718,   851,  1035,  1266,  1736,
    1036,  1037,  1038,  1500,  1501,   719,   852,  1510,  1907,  2046,
    2156,  2217,   720,   853,   721,   854,  1912,   722,   855,  1511,
    1915,   723,   724,   856,  1049,  2053,  1283,  1513,  1918,  1753,
    1754,  2055,  1281,   725,   857,  1054,  1055,  1056,  1057,  1295,
    1058,  1059,  1060,  1061,   726,   858,  1025,  1895,  1253,  2039,
    1488,  1722,  2037,  2151,   727,   859,  1296,  1526,  1922,  1925,
     728,  1067,  1299,   729,   862,  1069,  1070,  1760,  2068,   730,
     863,  1073,  1305,   731,   865,   732,   866,   733,   867,   734,
     868,  1310,   735,   869,  1312,  1767,  1768,  1538,  1770,  1936,
    2077,  1938,  2171,   736,   737,   871,  2084,  1081,  1315,  1542,
    1675,  1844,  1775,   738,  1544,   739,   740,   873,  1276,  1777,
    2034,  1942,  2089,  1608,  1439,  1440,  1692,  1694,  1868,  1659,
    1660,  1830,  1832,  2006,  1927,  1928,  2066,  2070,  2166,  1744,
    1745,  1909,  1746,  1910,  1943,  1944,  2086,  1945,  2087,  1432,
    1433,  1434,  1680,  1435,  1681,  2000,  1016,  1017,   973,   974,
    1195,  1196,  1197,  1198,  1199,  2064,  2065,  1114,  1344,  1385,
     964,   987,  1214,  1044,  1050,   349,   350,  1062,  1063,  1239,
    1039,   977,   978,   425,   431,  1097,   432,   254,  1010,  1011,
     965,   989,  1117,  1382,  1641,  1721,  1886,   994,  1040,  1987,
     967,   946,   791,   920,   921,  1989,   968,   808,   809,   969,
    1146,  1148,  1389,  1403,  1398,  1395,   225,  1769,  1322,  1166,
    1274,  1923,   210,  1216,   930,   403,   365,  1323,   243,  1948,
     374,   216,   621,  1141,   561,   158,   551,   265,   272,  2030,
     136,   274,   820,   519,    42,   408,   554,  2176,   515,   371,
    1635,   934,  1317,  1726,   901,   174,   501,   788,  1605,   258,
     619,   630,   746,   214,  1413,  1241,  1109,   546,   786,   183
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1699
static const yytype_int16 yypact[] =
{
   -1699,   285,   446, -1699,   -96,   196,   446, -1699, -1699, -1699,
     512,   512,   422,   422, -1699,   596, -1699, -1699, -1699, -1699,
     663,   663,   277,   657,   657,   536,   327, -1699,   826,   910,
   -1699, -1699, -1699, -1699,   -54,   594,   882,   528,   681,   681,
   -1699,   589,    53,   605,   615,   719,   631, -1699,    13,   979,
     783,   985, -1699,   -28, -1699, -1699,   808, -1699, -1699, -1699,
     678, -1699, -1699, -1699,   784,   722, -1699,    43, -1699,   473,
     512,   422, -1699, -1699, -1699, -1699,   704, -1699,   998,   427,
     721,   821,   949,   742, -1699, -1699,   854,   422, -1699, -1699,
   -1699,   758,   799,   811,   817,   828, -1699, -1699, -1699, -1699,
   -1699,   920,   834,  1069,   885,   -48, -1699,   402, -1699, -1699,
   -1699, -1699,   838,   937,  1059, -1699,    28,   860, -1699,    86,
      86,   863,   851,   852,   657, -1699,   569,  1122,   169,   747,
    1025, -1699, -1699,   859, -1699, -1699,   922, -1699, -1699, -1699,
    1280, -1699, -1699, -1699, -1699,   862,   964,   991, -1699,   742,
   -1699, -1699, -1699, -1699, -1699,   495, -1699,   392,   -90,   515,
   -1699, -1699, -1699, -1699,   959,  1115, -1699,   468, -1699,   547,
   -1699, -1699, -1699, -1699,    67,   168, -1699,   -38, -1699, -1699,
   -1699,   890,   673,  1224,   909,   909,   968,   987,  1115,  1115,
    1115,   909,  1115,  1290,  1115, -1699,   112, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
     909,   920,   427, -1699,  1269, -1699,  1189,    28,   860, -1699,
     919,  1019,  1027,   860,  -134,   941,  1054, -1699,  1115,  1011,
    1101, -1699, -1699,  1272,   681,  1115,  1150, -1699,   634, -1699,
   -1699,  1026, -1699,  1115,  1176, -1699,   476, -1699, -1699, -1699,
   -1699,   938,  1143, -1699, -1699,  1115,  1115, -1699,  1115,   955,
    1323,   955,  1115,   955, -1699,   909,    16, -1699, -1699, -1699,
   -1699, -1699,   742, -1699,   742, -1699, -1699,   860, -1699,   946,
    1044, -1699, -1699, -1699,   941, -1699,   952,   -19, -1699,  1269,
    1115,   650,   650,  1115,     8,  1152,  1115,  1371,  1136, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
     133,   200,  1115, -1699,   975,   965, -1699,   783,  1150, -1699,
   -1699, -1699, -1699,   955, -1699, -1699, -1699, -1699, -1699,  1115,
     701,   955,  1180,    97, -1699, -1699, -1699, -1699,   955, -1699,
   -1699,    58, -1699, -1699, -1699, -1699,   742, -1699,  1118,   742,
   -1699, -1699,   860, -1699,   971,   973, -1699, -1699,  1331, -1699,
    1333,  1150,   990,  1115,  1371,   955,    -7,   -27,  1150,  1000,
   -1699,  1115,  1001, -1699,  1001,    -8, -1699, -1699, -1699, -1699,
   -1699,  1150, -1699, -1699, -1699,   567,   126, -1699,  1077, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699,   701, -1699,  1038, -1699,
   -1699, -1699, -1699,   955, -1699, -1699, -1699, -1699,  1150, -1699,
     796, -1699,  1150, -1699, -1699, -1699,  1126, -1699, -1699, -1699,
     739,  1042, -1699, -1699, -1699,   955, -1699, -1699, -1699, -1699,
   -1699, -1699,  1211,    62,  1251,  1016, -1699, -1699, -1699,  1115,
    1115, -1699, -1699,  2643,   422, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
     931, -1699,    68, -1699,   701, -1699,  1150, -1699,   732,  1152,
    1142,  1061, -1699,  1102,  1152,  1115,  1403,   262,     2,  1150,
    1037, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
    1093, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
    1115,  1435, -1699,  1001, -1699,  1126, -1699, -1699,  4620,  1448,
    1295,  1150,    85, -1699, -1699, -1699,  1150, -1699, -1699,  1117,
   -1699,   -26,   -26,  2851,  1034,  1040, -1699, -1699, -1699, -1699,
   -1699,  1134,  3560,  3795,  1043, -1699, -1699,   931, -1699, -1699,
   -1699, -1699,  1107,  1115,  1276, -1699,   165, -1699,  1115,   713,
   -1699,  1115,  1115, -1699,  1115,  1115,  1280,   162,  1115,  1063,
   -1699,  1141, -1699, -1699,   941,  1278, -1699, -1699,   302,   316,
     522,   535,   639,  1073, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699,  1168, -1699,  1150, -1699, -1699, -1699, -1699,
     955,   955,  1294, -1699, -1699, -1699,   430, -1699, -1699, -1699,
    1115,   195, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,   918,   442,
   -1699,   376, -1699, -1699, -1699, -1699, -1699,   150,  1290, -1699,
     455, -1699, -1699, -1699, -1699,  1404, -1699, -1699,  1279, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699,  1061, -1699,  2239,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,    14, -1699,
   -1699,  1213, -1699, -1699, -1699, -1699,   154, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699,   981, -1699, -1699,  1115,    74,  1115, -1699,
   -1699,   557,   620, -1699, -1699, -1699,   -27,  1140,   955,   955,
   -1699,  1235,  1235,  1245, -1699,   955, -1699, -1699,    25,   -19,
   -1699, -1699,   941, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699,  1081, -1699, -1699,  1125,
   -1699,  1080,  1137, -1699, -1699, -1699, -1699,  3077,   343,  1500,
   -1699,  1179,  1179,   701,  1265,  1265, -1699, -1699,  1084, -1699,
   -1699, -1699, -1699, -1699, -1699,    57,  1370, -1699, -1699,  1042,
    1150,  1096, -1699,  1098,   955,  3638,  1114,   155,   982, -1699,
   -1699,  4203,   742,  4332,  4203,  1320,   682,   841,   102,   955,
   -1699, -1699,  1420, -1699,   102,   955,  4216,   955,  3821,  4203,
   -1699,  1594,   742,   955,   742,   955,    41,    66,   955,   742,
   -1699, -1699,  2984,  3875, -1699, -1699,   955,   955,   742,   955,
   -1699,   295,  1451,   955, -1699, -1699, -1699, -1699, -1699, -1699,
    1538, -1699,   909, -1699, -1699, -1699, -1699,   955,   122,   159,
     166,  1138, -1699,  1138, -1699, -1699, -1699, -1699,   255, -1699,
   -1699, -1699, -1699, -1699,   955,  1115,  1399,  1399,   195, -1699,
   -1699, -1699, -1699,  1387, -1699, -1699, -1699,  1150,  1177,  4973,
    1129, -1699,   955, -1699,   343, -1699,  1181,  1348, -1699,  1403,
   -1699, -1699, -1699, -1699,   955,   955,   701,   -27,   -27,  1548,
    1290, -1699, -1699, -1699,  1457,   717, -1699,  1265,  1145,   955,
    1147,  1154,  1265,    97,  1155,  1162,  1169,  1170,  1171,  1172,
    1175,  1178,  1147,  1463, -1699,  3887, -1699, -1699, -1699, -1699,
    1389, -1699,  1533, -1699,  3328, -1699,  1208, -1699,    97, -1699,
   -1699,  1190, -1699, -1699,   381,   742,  1487,  1241, -1699,  1283,
    1313,  1024,  1498,  2087,  1104,  1165,  1499,   173,  1190, -1699,
   -1699,    37, -1699, -1699, -1699,  1534, -1699, -1699, -1699,  1265,
     102, -1699, -1699, -1699, -1699, -1699,  1239, -1699,    93,   955,
   -1699,   108, -1699, -1699, -1699, -1699, -1699,  4203, -1699,  1238,
    1501,  1585,   810, -1699,  1242, -1699,  1630,  1504,   472,  1249,
    1250,  -103,  1254,   613,  1471, -1699,  1313,  1471,   955,  1508,
    1221, -1699,   876, -1699, -1699, -1699, -1699, -1699,  1408, -1699,
     102, -1699,   432, -1699,    52, -1699, -1699,   548,  1600,  2357,
   -1699, -1699,   955,  1509,  4056,   955,  1477,   869,  1546, -1699,
    1330,  1286,  1388,  1471,   981, -1699,     9, -1699, -1699, -1699,
   -1699,    -5, -1699, -1699,  1115,   955, -1699, -1699,   381, -1699,
   -1699,   955, -1699,  1150,   941, -1699, -1699, -1699, -1699,  1549,
    1265,  4973,  4973,  4973,    17,   878, -1699, -1699, -1699,  1084,
   -1699,  4973, -1699, -1699,  1073, -1699,   343, -1699, -1699, -1699,
   -1699, -1699, -1699,  1211,   -27,  1551, -1699, -1699,   876,   857,
    1231,   135,   -23,  4973,  1270,  4973, -1699,  4973, -1699,  4529,
    1232,  4973,  4973,  4973,  4973,  4973,  4973,  4973,  4973, -1699,
   -1699, -1699,  4203,  1484, -1699, -1699,  1334,  1389, -1699, -1699,
   -1699, -1699,  1061, -1699, -1699,  1282, -1699,  1282, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699,  3091, -1699, -1699, -1699, -1699,
   -1699,  1367,  1440, -1699,   563, -1699, -1699, -1699,   812, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699,    54, -1699, -1699,
    1253,  1516,  1516,  1516,  1516, -1699, -1699,  4203,  4203, -1699,
     682,   219,  1550,  1247, -1699,  1252, -1699,   955, -1699,   111,
   -1699, -1699,  1240,  1515, -1699,   876,    84, -1699,   108, -1699,
   -1699, -1699, -1699,    50,  1288,   102, -1699, -1699,  4203, -1699,
   -1699, -1699, -1699,  1327, -1699, -1699, -1699, -1699,   955,   155,
   -1699,   999, -1699, -1699,  1313,   381, -1699,  1485,   421,   595,
   -1699, -1699,   955,   595,  1296, -1699,  1084, -1699, -1699,    59,
     732, -1699, -1699,  1910, -1699,  1643,  1482,  4203,  4203, -1699,
    4137,   955, -1699,  1521, -1699, -1699,  4203,   876, -1699, -1699,
   -1699,  1600,  1492,   955, -1699,   967, -1699,    42,   421, -1699,
   -1699,  1580, -1699, -1699,  1427, -1699,   955,   955, -1699,   955,
    1512,   996,   -16, -1699,  4743,  1388, -1699,  4529,  1260,  1260,
     984, -1699, -1699, -1699,  4973,  4973,  4973,  4973,  4973,  4973,
    4781,   878,  1349, -1699, -1699,  1211,  1388, -1699, -1699, -1699,
    1516, -1699, -1699,  1268,  1271, -1699,   876,  1516,  1496, -1699,
   -1699, -1699, -1699,  1402,  1516,  1452,  1452,  1452,   107,  1489,
   -1699, -1699,   384, -1699,    69,   915,   955,   898,    87,  1274,
   -1699,  1084, -1699, -1699,   511,  1275,  1023,   575,  1285,  1052,
      91,    94,   694,  1287,  1124,  4149,   463,  4203,   102, -1699,
    1380, -1699, -1699, -1699, -1699, -1699, -1699,  1321,   155, -1699,
     138,   955,   955,   483, -1699, -1699, -1699,   105,    56,  1352,
   -1699, -1699,  1591, -1699,  1461, -1699,     4,   360, -1699, -1699,
    1467, -1699, -1699, -1699,  1545,  4149,   539, -1699, -1699, -1699,
   -1699,  1701, -1699,  1336, -1699, -1699,   174, -1699, -1699,   219,
   -1699, -1699,  1388, -1699, -1699, -1699,  1061, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699,  1407,  1061, -1699,  1339, -1699,  1686,
   -1699, -1699, -1699,   407, -1699,   876,   789, -1699,    67,    79,
     232,   102,   102,  4149,   545,  1037,   742,  1604, -1699, -1699,
    1729, -1699,  1565, -1699, -1699, -1699, -1699,  1485, -1699,   955,
     460,    54,   864,  1312,  1620, -1699,  1314,   876,   794, -1699,
     384, -1699, -1699, -1699,  4203,  1115,    54, -1699, -1699, -1699,
   -1699,   -79,   955,  4149,   553,  1351,  1738,   955,  -105, -1699,
   -1699, -1699,  1459,  1450, -1699, -1699,   999, -1699,    10,   955,
    1115,  1587, -1699, -1699,  1150, -1699, -1699, -1699,  1115, -1699,
   -1699, -1699, -1699,  1452,  1091,  1115,   982, -1699, -1699,  1452,
   -1699,  1150, -1699, -1699, -1699, -1699, -1699,   955, -1699,   955,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,   955,
    1562,   232, -1699,  1084, -1699, -1699,   915,   795,   795,  1260,
    1260,  1260, -1699,  1156, -1699,  1061, -1699,   955, -1699,  1467,
   -1699, -1699,  1516, -1699, -1699, -1699,  1115, -1699, -1699,  1115,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699,    18, -1699, -1699,
   -1699,  1402, -1699, -1699, -1699,   381,   381,   381, -1699, -1699,
   -1699, -1699, -1699,  1147,  1283,  4893, -1699,   955,  1147,  1147,
    4973, -1699,  1147,  1147,  1147,   474,  1147,  1147, -1699, -1699,
    1502,  4149, -1699,   102, -1699, -1699,  1322, -1699,   -47,   120,
   -1699, -1699, -1699, -1699,   988, -1699,  1442, -1699,  1425, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,  1139,
    1516,  1503, -1699, -1699, -1699,  4203, -1699,  4203,   219, -1699,
   -1699, -1699,  1701, -1699,   955,  1645,  1343,   900,  1664,  1345,
     286,   876, -1699, -1699,  1722, -1699, -1699, -1699, -1699,   789,
   -1699,  1603, -1699,  1115,  1505, -1699, -1699, -1699, -1699,  1276,
     102, -1699,  4203,   162,   406, -1699, -1699, -1699,   955,  4203,
     675, -1699, -1699, -1699,  1638,  1522, -1699,  1640, -1699,  1543,
   -1699, -1699, -1699, -1699,  1314, -1699, -1699, -1699,  1525,  1641,
    1506,  1488,  1283, -1699,  4203,   286, -1699,  1507, -1699,   876,
   -1699,  1675,  1400, -1699, -1699,  1388, -1699,   970,  1776,   942,
   -1699, -1699, -1699,  1150,  1676,  1575,  1726,  5019,   -53,  1115,
   -1699, -1699,   -53, -1699,  1115,  1177, -1699, -1699, -1699,  1600,
   -1699,  1276, -1699,  1397, -1699, -1699, -1699,   -53,   -53,   124,
     124, -1699, -1699, -1699, -1699, -1699,  1352, -1699,  1166, -1699,
   -1699, -1699,   915, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699,  4203, -1699, -1699,
   -1699, -1699, -1699,  1670, -1699, -1699, -1699, -1699, -1699, -1699,
    1115, -1699, -1699, -1699, -1699,  1110,  1115, -1699, -1699, -1699,
   -1699,    27, -1699,  1139, -1699, -1699, -1699, -1699, -1699,  4149,
    1476,  4149,  1478, -1699, -1699, -1699, -1699, -1699,  1665, -1699,
     900, -1699,  1703, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
     286,   999, -1699, -1699,   999,    -6,   955, -1699, -1699,  4149,
   -1699, -1699,   904,  3795, -1699,  1749,  1574,  1597,   414, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699,  4203,   749, -1699, -1699, -1699,  1671,  1552,   955,
    1352,  4149, -1699,  1738, -1699,  1251,  1721,  1251,  1506,   401,
   -1699, -1699,  1672, -1699,  1559, -1699, -1699, -1699,   393, -1699,
   -1699,  1115,  1728,  1606, -1699,  1002, -1699,  1621,  1007,  1371,
    1633,  1395,  1115,  1265,  1115,   955, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,  1444, -1699,
   -1699, -1699, -1699,   683, -1699, -1699, -1699, -1699, -1699, -1699,
     450, -1699,   543, -1699,  1398,  1115,  1115, -1699, -1699, -1699,
   -1699,   -53, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699,   -53, -1699, -1699,   -53,   124,   124, -1699, -1699,
   -1699,  4203, -1699,  4203, -1699, -1699, -1699, -1699, -1699, -1699,
    1777,   999,   999, -1699,  1431,  1536,   742,    70, -1699,   955,
   -1699, -1699,  1517,  4203, -1699,  1115,   950,  1599, -1699,  1608,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,  1282, -1699,
    1282, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699,   955,  1251, -1699,   955,  1694,
   -1699, -1699, -1699, -1699, -1699,   742, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699,  1050,  1150,  1115,  1115,  1669, -1699,  1115,
   -1699, -1699, -1699, -1699,   195, -1699,  1115, -1699,   955,   955,
    1113,  1667, -1699,  1558,  1150,   683, -1699, -1699, -1699, -1699,
   -1699, -1699,   -53, -1699, -1699, -1699, -1699,   -53, -1699,  1398,
   -1699,   955,   343,  1050, -1699, -1699, -1699, -1699, -1699, -1699,
    1352,  1352, -1699,  4203,   999, -1699,  4203,  1115,   742,   742,
    1553, -1699, -1699, -1699,  1441,   955,  1718, -1699, -1699, -1699,
   -1699, -1699, -1699,  1581,  1582, -1699, -1699, -1699,   955, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,  1150,  1150,
    1115, -1699,  1150, -1699,  1150, -1699,  1283, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699,  4203, -1699, -1699,
   -1699, -1699, -1699, -1699,   955, -1699, -1699, -1699, -1699, -1699,
   -1699,   155,   742,  1115, -1699, -1699, -1699, -1699,  1704,  1710,
   -1699, -1699, -1699, -1699,  1150, -1699, -1699, -1699,  1813, -1699,
     155, -1699,  1061,  1061, -1699,  4203, -1699, -1699, -1699, -1699
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1699, -1699, -1699, -1699,  1857, -1699, -1699, -1699,    72, -1699,
   -1699, -1699, -1699, -1699,  1554, -1699, -1699, -1699,  1188, -1699,
   -1699,    34,  1844, -1699, -1699,  1814,   874, -1699, -1699, -1699,
   -1699, -1699,  1684,  1741, -1699, -1699,  1705,   735, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699,  1693, -1699, -1699, -1699, -1699,
    1677, -1699, -1699, -1699,   584, -1699, -1699, -1699, -1699,  1415,
   -1699, -1699,  1340,   792, -1699, -1699, -1699, -1699, -1699, -1699,
    1483, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699,  1746, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,   989,
     101, -1699,  1337, -1699, -1699, -1699,  1004, -1699, -1699, -1699,
     160, -1699,  1680, -1699,  1780, -1699, -1699, -1699, -1699,  1537,
   -1699,   249, -1699, -1699, -1699, -1699,  1678, -1699,  1840,  1747,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,  1078, -1699,
   -1699, -1699,  1376, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699,   930, -1699, -1699, -1699,  1615,
   -1699,  -518,  -735, -1699, -1699, -1699,  -402, -1699, -1699, -1699,
   -1699, -1699, -1699, -1278, -1275,  1103, -1273,   114, -1699, -1699,
   -1699, -1699,   311, -1699, -1699,  -226, -1260, -1699, -1699, -1259,
   -1699, -1258, -1699, -1699,   980, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699,  1401, -1699, -1699, -1699,
    1003, -1699,  -702, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
     -73, -1699, -1699, -1699, -1699, -1699, -1699,  -208, -1699, -1699,
   -1699, -1699,  -158, -1699, -1699, -1699, -1699, -1699,  1146, -1699,
   -1699, -1699, -1699, -1699, -1699,   209, -1699, -1699, -1699, -1699,
   -1699,  1788,  1057, -1699,   241, -1699, -1699, -1699, -1699,  1470,
   -1699, -1699, -1699, -1699, -1699, -1699,  -944, -1699, -1699,   176,
   -1699,  1381, -1699, -1699, -1699,   924,   541,   537, -1699, -1699,
     290, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699,   925, -1699, -1699,   256,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699,    61, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699,   695, -1699, -1699,   696, -1699, -1699, -1699, -1699,
     469,   229, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,    60,   688,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699,   685, -1699, -1699,
   -1699,   215, -1699, -1699,   454, -1699, -1699, -1699, -1468, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1424,   902, -1699, -1699,   201, -1699, -1699,   434, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,   625,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699,   661, -1699,   191,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699,   889, -1699,   891, -1699, -1699,  1092, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699,   884,   417, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699,    23, -1699,   419, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,  -755, -1699,
   -1136, -1699, -1699, -1037, -1155, -1129, -1699,   349, -1699, -1269,
   -1699, -1699, -1699, -1699,    22, -1699, -1699, -1699, -1699,   -85,
   -1699, -1699,   220, -1699, -1699, -1699, -1699,    20, -1699,  -469,
   -1634, -1699, -1699,   533, -1699, -1196, -1254,  -807, -1168, -1699,
   -1699,   773,    46,    47,    51, -1699, -1699,   145,  -184,  -294,
    -117, -1114,  -819,    63,   927, -1463,   -83, -1699, -1039, -1699,
    -792, -1699,   774, -1084,  -241, -1699,  -563,  -153,  -813,  -958,
     146,  -747, -1699, -1699,   457, -1010, -1532,  -929,  -801,  -669,
     691,  -573,  -220, -1699,  1058,  -230,  -618,  -652,  -277,  -361,
    -922, -1699, -1699, -1699, -1699, -1699,  1755, -1699, -1699,   815,
   -1699, -1699, -1699, -1599,  1183,  -287,  1695,   733,  -401, -1699,
    -362,  1433, -1699,  -606, -1699, -1054,  1064,  -384,   879, -1699,
   -1699,  -670, -1699, -1698,  -164,  -596,  -471,  -143,  -925,   677,
   -1340,  -797, -1183, -1699,  1233,  1941,  -707, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1162, -1699,   204,  -653,   877,  -470
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1519
static const yytype_int16 yytable[] =
{
     118,   236,   424,   807,   840,   798,   320,   555,   935,   500,
     557,  1327,   988,  1499,  1300,  1414,   872,   790,   334,   972,
     337,   815,   339,  1291,   259,   260,   261,   981,   263,  1003,
     266,  1018,   255,  1734,   914,   976,  1636,  1637,   262,   335,
    1159,   335,  1284,   335,  1064,  1816,   769,    21,  1405,   517,
    1048,  1543,  1238,   398,  1230,  1206,  1581,   269,  1009,  1582,
    1238,  1583,   310,  1453,   311,  1009,   118,  1441,  1442,  1443,
    1490,   318,  1009,   748,  1584,  1585,  1586, -1482,   966,   323,
     405,   380,   387,   905,  1341,   536,   966,   997,   386,   271,
     399,   330,   331,  1478,   332,  1685,    84,   404,   338,  1009,
    1372,  1029,  1031,   335,   937,    91,  1238,   343,  1009,   906,
     907,   335,   342,   344,  1445,  1071,   966,   264,   335,   398,
    1380,   123,    53,   184,   426,  1320,   362,   241,  1358,   367,
     369,   421,   372,  1809,   154,  1506,  1341,   175,   433,  1479,
     624,    88,  2016,  1946,  1493,   335,   357,   335,   381,   357,
    1142,   441,  1589,    40,  1341,  1149,   439,   816,  1341, -1482,
    1679,  1341,   770,  1930,  1075,   388,  1320,  1292,   185,  1328,
    1375,   761,   154,  1607,   319,    62,  1696,   244,   467,   810,
     926,   446,   502,   465,   513, -1518,   154,   538,   407,   348,
      62,   883,  1533,   895,  2035,  1448,  1245, -1442,  1375,   423,
     430,   631,  1838,   186,   187,   335,   188,   435,  1354, -1469,
    1052, -1518,  1237,   553,   189,    40,   438,   405,  1164,  1462,
   -1446,  1227,  1836,  1789,  1731,   231,  1324,  1200,  1023,  1794,
     378,  1609,    40,  1932,  -178,  1477,   539,  2075,  1609,  2078,
    1448,   860,  1549,  1053,   817,  1609,  1164,  1289,    51,   556,
    2149,  1480,  1779,  1894,   769, -1458,   510,  1536, -1518,  1727,
    1430,   137,   427,   348,  1763,   406,   414,  1119,   190,   975,
   -1518,  -179,  1724,    31,   273,   521,   522,  1381,  1087,  1704,
    1254,   623,   749,  1217,    54,     3,   628,  1677,  1453, -1361,
     401,  1453,  1278,  1661,   376,   803, -1408,  1535, -1492,  1686,
    1481,   633,   633,  1079,   379,  1053,   926,  1678,   908,   283,
    1431,   549,  1103,  1337,   377,   228,   138,   139, -1518,  1780,
    1316,  1781,  1071,   273,   179,   333,   750,  1164,  1318,  1080,
    1613,  1238,  1325,  1134,   232,   870,   559,  1633,   975,  1277,
     191,  1728,   919,   988,   618,   562,  1508,    12,  2150,  -178,
     179, -1446,   803,   861,  1725,   789,  1612,    63,  2033,  1376,
     229,  1129,  1130,   428,   402,    54,  1669,  1342,    55,   552,
     770,   792,    63,   163,  1132,  1133,  1228,   333,  2168,   747,
     884,  1042,   975,  1986,   752,   803,  -179,   756,   757,   -31,
     758,   759,  1833,  1088,   765,   245,   625,  1688,  1377,  1329,
    1286, -1446,   406,   333,   333,   247,  1429,   333,    64,   988,
    1778,   358,  2158,   762,  1555,  1406,  1478,  2036,  2031,  1342,
     242,  2032,   440,  1003, -1458,   804,  1377,   319,   885,  1246,
    1606,  1810, -1469, -1464,  1687,  1839,   797,  1342,  1321,   988,
    2017,  1342,  1492,   317,  1342,  1293,   253,  1464,  1200,    55,
    1662,  1701,  1518, -1446,   192,   516,   938,    88,   537,  1119,
    1119,  1119,  1479,  1343,  1231,  1294,    85,   983,   909,  1119,
     763,   333,   333,   553,   389,  1714,  2085,  1503,   534,  1321,
    1444,  1446,   333,  1609,  1482,  1024,  1286,   988,   253,   333,
     983,  1119,  1247,  1119,   193,  1119,   333,  1391,  1919,  1119,
    1119,  1119,  1119,  1119,  1119,  1119,  1119,  1755,  1353,  1967,
   -1446,  1494,  1968,   390,  1969,  1643,  1703,   898,   899,  1411,
     391,  1705,   179,   333,   904,  1545,   932,  1971,  1972,  1973,
    1453,   389,   333, -1400,  1238,  1865,   335,  1653,   335,   335,
    1654,   333,   194,   154,  1840,   335,  1523,  2003,  1243, -1442,
    1527,  1528,  -178,  1530, -1446,   267,  1135,   447,  1120,  1534,
   -1446,  2080, -1446,   154,   389,  2144,  1042,  1507,  1449,  1383,
     390,  1355,  1450,  2148,  1480,  1806,  1390,   391,  1341,   179,
    1742,  1869,   882,  1871,   887,   333,  1332,  2227,   988,  -179,
     941,   392,  1939,  1286,   805,  -942,   333,  1556,   179,   166,
    2020,  2081,  2022,   390,   913,  2047,    87,   979,  1205,  2082,
     391,  1640,  1669,  1449,  2002,  2099, -1492,  1450,  1899, -1518,
     319,  1094,     4,  1481,   810,  1115,  1665,  1026,   818, -1489,
    2040,  1041,  1053,  1045,  -942,  1045,  1051, -1518,  1026,    13,
    1672,  -942,  1341,  -729,   104,  2048,   898,   794,   392,    18,
    1931,   891, -1518,  1045,   393,  1286,    15, -1518,   801,  1131,
     775,  2072,  2073,  1096,  1461,  2049,  1150,   335,   888,   104,
    1090,  1053, -1518,  1514,   777,   983,  2091,  1514,  1730,  2083,
     325,   392, -1460,   394,   335,  1593,  2212,  1107,  2118,    25,
    1826,  1202,  1119,  1119,  1119,  1119,  1119,  1119,  1119,  1095,
     444,  1889,  1123,   326,   164,  1834,  1812,  1813,  1814,   776,
      22,   393,  -942,  1743,  1286, -1442,   333,   335,   335,  1697,
      28,  1815,   395,   778,    19,  1732,  1820,  1821,  1297,  1085,
    1823,  1824,  1825,  1764,  1828,  1829,  1848,  1849,  1428,  2119,
     394,  1098,   105,  1421,   393,  1994,  1138,     5,  1867,   990,
    1120,  1120,  1120,    29,   228,  2001,  2001,  1676,   184,  1934,
    1120,  1341,  1673,    32,  1592,  1793,   795,   105,    74,  1043,
      33,  1046,  1238,   394,     5,  -942,  1066,  1757,   892,   395,
   -1442,  2123,  1120,   164,  1120,  1077,  1120,  2229,  1392,  1689,
    1120,  1120,  1120,  1120,  1120,  1120,  1120,  1120,  1715,   229,
     469,  1215,  1116,   185,  -942,   164,  2236,  1482,  1512,  1642,
   -1446,   333,   395,  1706,   333,   470,   165,  1338,  1339,  1340,
    2138,  2139,  1709,   333,   471,  1290,  -584,  1351,  1051,  1986,
   -1446,   115,  2124,  1286,  1286,   179,   115,  -942,   186,   187,
    2050,   188,   802,  -942,  1716,   141,  -582,    74,  1512,   189,
     179,  1387,   889,  2185,   426,   893,   241,  1394,  1396,  1397,
    1399,  1342,  1272,  1402,  1404,  1286, -1518,  1906,     5,    74,
     164,  2207,  2208,  1331,  1827,   335,  1870,  1215,  1872,  1298,
     779,  1359,  1360,  1215,  1267,    17,  2005,  2120,  2121,   389,
    1139,  1215,  1874,   781,  1422,   165,  2163,  1268,  2164,  1172,
    1173,  2011,  1208,   190,   240,    35, -1518,  1273,   472,  2092,
     319,   237,  1467,   988,   335,  1468,  1469,   165,  1047, -1446,
   -1464,  1361, -1489,  1362,  2019,  1342, -1518,  2057,   390,   780,
    1326,  2024,  2113,  2058,    74,   391,  1083,   473,  -584, -1446,
      43, -1442,   782,  1917,    90,   988,    40,  1642,  1345,  1346,
    1347,  1348,  1803,  1349,  1363,  1364,  1365, -1406,  -582,   363,
    2231,   364,  2001,  2001,  2059,  2051,  2052,  1691,  2060,    92,
    1259,    48,  2114,   240,  2054,   191,  1594,   389,    49,   993,
    2125,  2126,   165,  1120,  1120,  1120,  1120,  1120,  1120,  1120,
     239,   472,  1905,  1119,  1116,  1116,  1116,   783,  1119,   166,
     540,  1366,   541,  1367,  1116,  1717,   392,  1504, -1442,  1074,
    1260,  1368,  1345,  1346,  1347,  1348,   390,  1349,  1261,   979,
     473, -1404,   753,   391,    37,  1733,  1116,   474,  1116,   754,
    1116,    93,    52,  1505,  1116,  1116,  1116,  1116,  1116,  1116,
    1116,  1116,  1747, -1518,  1342,    44,   784,  2204,    58,   979,
    1596,  1597,  1598,  1599,  1600,  1601,  1603,  1759,    59,  1286,
     948,  1761,  2134, -1518,   389,    60,  2135,  1286,  1761,   393,
    1742,    94,   475,    95,    61,   950,   999,   321,   476,   799,
    1000,  2142,  1369,    45,     5,   426,   513,  1723,  1262,   192,
    2007,    46,  1888,    67,   392,  1748,  1053,   979,   394,   800,
     289, -1518,   179,   390,   179,   477,   335,   335,    74,  2161,
     391,  2162,   478,   290,    71,  1749,   250,  1286,  1940,   450,
    1540,    78,  2165,  1991,  1541,   479,  1424,  1004,  1005,   193,
      80,  1345,  1346,  1347,  1348,  2041,  1349,   395,  1998,  1999,
   -1401,  1006,  2172,  2173,  1470,  1471,   543,  1888,   276,   242,
     291,   548,   480,   282,    81,  2042,  1430,   393,   451,   951,
     481,   102,  1472,  1473,   111,   452,  2109,   112,   361,   874,
    -193,  1850,   115,   368,  1851,  2056,  1430,   194,  1308,   113,
    1309,   392,  1852,  1853,  1854,   121,   394,  1007,  1521,  1718,
      10,   482,  1522,  1190,    10,   449,  1193,  1194,   979,  2189,
    2190,   125,  2140,  1743,  2141,   983,  1431,   351,   875,   980,
    1647,   954,   227,  1650,   955,   876,   227,  1425,  1655,   333,
    1552,  1553,  2220,  2191,  1941,   395,  1431,  1116,  1116,  1116,
    1116,  1116,  1116,  1116,  1347,  1348,   454,  1349,  1790,   483,
    1791,   179,   126,  1841,   393,  1842,   956,   947,  1370,  1466,
     803,  1780,  1467,  1781,   127,  1468,  1469,  2013,  1898,  2014,
     128,    40,  1634,  2098,  1902,   450,   292,  2102,  2103,   130,
    1908,   129,  1888,   394,  2174,  2175,   293,   132,   133,  2093,
     135,   144,   415,   145,  1120,   146,   877,  1371,  1384,  1120,
    -311,  1855,  1388,   160,   161,   162,  2154,   175,   209,   455,
    1400,  1401,   212,   215,   451,   219,   333,   213,   513,  1856,
     220,   452,   395,   221,   957,  1345,  1346,  1347,  1348,   948,
    1349,   235,    40,   453,  1786,   252,  1857,  1350,  -752,   335,
    1995,  -752,  2133,   249,   950,  1345,  1346,  1347,  1348,   253,
    1349,  1795,   256,  2136,   257,   264,  2137,  1645,  1798,   878,
     271,  1818,  1345,  1346,  1347,  1348,  1822,  1349,   273,   958,
     959,  1758,   278,   294,   295,   279,  1804,   458,   280,   335,
     154,   285,  1858,   312,   313,   315,   296,   319,   297,   322,
     324,   327,   454,   328,   960,   333,  1783,   335,   336,   353,
     354,  1211,   370,   373,  1788,   356,  2209,  2192,  2193,  2210,
    -752,  1792,   961,   375, -1446,   382,  1819,   400,   383,   412,
     962,  -323,   333,   420,   417,  -752,   418,   879,   951,  1859,
     422,  1345,  1346,  1347,  1348,   434,  1349,   335,   464,   389,
    1595,   436,  1615,   503,  1616,   511,   514,  1617,  2194,  2195,
   -1353, -1353, -1353, -1353,   518,   455,   520,  1618,   456,   457,
    2228,   544,  1807,  2201,   545,  1808,   547,   550,  2202,   952,
    1345,  1346,  1347,  1348,   953,  1349,   179,   558,   390,  1649,
     954,   560,  1860,   955,   620,   391,   622,   636,   298,   629,
     638,   745,  1861,   637,  1470,  1471,   742,   553,  2239,  1345,
    1346,  1347,  1348,   766,  1349,   767,   774,   299,  1652,  -752,
     785,   793,  1472,  1473,   787,   956,   822,   821,  2183,   864,
    -752,   896,   900,   458,  2205,   945,   903,   916,   917,   982,
    1221,  1222,  1223,  1224,   995,   919,   927,   922,  1116,  1012,
    1013,   929,   933,  1116,   936,  1012,  1020,  1022,   939,   942,
    -752,   943,   982,  1862,   970,  -752,   392,   998,  1012,  -752,
    1015,  -752,  1082,  1950,  -752,  1084,  -752,  1020,  1076,  1896,
    1078,  1345,  1346,  1347,  1348,  1099,  1349,  1091,  1105,  1108,
    1657,  1126,  1619,   957,  1121,  1127,  1620,   810,  1136,  2237,
    2238, -1352, -1352, -1352, -1352,  1160,  -752,  1165,  1167,  1621,
    1143,  -752,  1145,  1345,  1346,  1347,  1348,  2105,  1349,  1147,
    1151,  1201,  1802,  1345,  1346,  1347,  1348,  1152,  1349,   393,
    1118,  1209,  2004,  1203,  1153,  1154,  1155,  1156,   958,   959,
    1157,  1215,   753,  1158,  1218,  1990,  1225,  -752,  1240,  1236,
    1992,  1255,  1256,  1258, -1355,  1622,  1265, -1446,   394,  1269,
    1144,  1271,  1270,   960,  1275,  1280,  1282,  1053,   154,  1304,
    1307,   414,  1311,  1313,  -752,  2038,  1314,  1335,  1316,  1356,
    1373,   961,  1393,  1386,  1407,  1408,  1417,   975,  1436,   962,
    1412,   333,   948,  1438,  1456,  1207,   335,   395,  1454,  1459,
    1476,  1491,  1623,  1495,  -752,  1212,  2012,   950,  1509,  1517,
    -752,  1524,  2015,  1525,  1532,  1537,  1547,  1548,  1550,  -752,
    -752,  1012,  1349,  1610,  1604,  1611,  1624,  1614,   948,  1012,
    1244,  1663,  1634,  1376,  1664,  1658,  1682,  1431,  1698,  -752,
    1646,  1648,  1693,   950,  -752,  1695,  1699,   982,  1707,  -752,
    1625,  1651,  1710,  1656,  1711,  1626,  1735,  1738,  1739,  1750,
    1751,  1752,  -752,  1285,  1765,  1627, -1446,  1766,  1776,  1628,
    -752,  1012,  -752,  2117,  1784,  1012,  1774,  1799,  -752,  1847,
    1831,  1846,  1866,  1303,  1877,  1033,  1244,  1879,  1883,  1885,
    1890,   951,  1893,  1911,  1916,  1743,  1914,  1921,  1929,  1924,
    1897,  1933,  1935,  1947,  1937,  1926,  1951,  2094,  1952,  1207,
    1954,  1996,  1020,  2008,  2021,  2026,  2023,  2043,  2108,  2029,
    2110,  1033,  1118,  1118,  1118,  2044,  1629,   951,  2045,  2069,
    2067,  2076,  1118,  1941,  2088,  2095,  1630,  2100,  2106,  2152,
    2096,  1034,  2107,   954,  1963,  2143,   955,  2145,  2128,  1285,
    2159,  2131,  2132,  2147,  1118,  2170,  1118,  2180,  1118,  2160,
    2197,  2198,  1118,  1118,  1118,  1118,  1118,  1118,  1118,  1118,
    2213,  2153,  2216,  2214,  2232,  2218,  2219,   980,   956,   954,
    2233,  2235,   955,    14,  2177,    27,   251,    73,  2188,   182,
     248,   385,   238,   268,  1519,   535,  1319,   744,   211,   463,
    1949,  2155,  1093,   411,  2199,  2117,   755,   142,    66,   335,
     426,  1086,   270,  1900,   956,   275,   223,   940,   634,   355,
     923,  1970,  1801,  2203,  1125,  2112,   563,  2200,   159,  1837,
    1102,   335,   523,  1903,   741,  1638,   947,  1220,   915,   803,
    1639,  1811,  1835,  1229,  2018,  1447,   957,  1873,  1702,  1457,
    1475,  2178,  2179,  1487,  1892,  2182,  1285,  1712,  1264,  1904,
    2028,  1740,  2184,  1546,  1516,  1920,  1012,  1287,  2222,  2223,
    1065,  1288,  2225,  1302,  2226,  1772,  2074,  1773,  1805,  1502,
    2079,  2157,   957,   513,  2090,  1913,  1207,  1684,  1416,  2061,
    2062,   958,   959,  1515,  2063,  1279,  1419,  1756,  1122,   284,
    1012, -1518,  1410,  2211,   335,   931,  1489,   366,   948,   760,
    2206,   979,  1531,  1128,  2234,   902,   960,    75,  1285,  1993,
       0,  1352,   414,   950,  1539,     0,  -993,   958,   959,     0,
     979,     0,     0,     0,   961,     0,  2224, -1518,     0,  -993,
    1244,     0,   962,   179,   333,     0,     0,     0,     0,     0,
       0,     0,   960,     0,     0,  1118,  1118,  1118,  1118,  1118,
    1118,  1118,  -993,     0,     0,     0,     0,     0,     0,  2230,
     961,     0,     0,  1520,     0,  -993,     0,  1285,   962,   179,
     333,     0,     0,     0,     0,   414,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1644,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   951,     0,     0,
       0,     0,     0,   947,     0,     0,   803,     0,   389,  1012,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1670,  1671,     0,     0,  1138,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   952,   414,
       0,     0,     0,   953,     0,     0,     0,   390,     0,   954,
       0,     0,   955,     0,   391,     0,     0,     0,     0,     0,
   -1442,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   948,     0,     0,     0,     0,
       0,     0,     0,     0,   956,     0,  1285,  1285,     0,     0,
     950,     0,  1012,  1012,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1741,     0,     0,     0,     0,     0,     0,     0,  1285,     0,
       0,     0,     0,     0,     0,   392,     0,     0,     0,     0,
       0,     0,     0,  1762,     0,     0,     0,     0,  1771,  1771,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     842,     0,   957,     0,     0,  -885,     0,     0,  -885,     0,
       0,  -885,  -885,  -885,     0,     0,     0,   982,     0,  -885,
       0,     0,     0,     0,   951,     0,     0,     0,  1796,     0,
    1797,     0,     0,     0,     0,   389,     0,     0,   393,     0,
       0,     0,     0,     0,     0,     0,     0,   958,   959,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1521,   952,     0,   394,  1522,     0,
     953, -1442,   960,     0,   390,     0,   954,  -885,     0,   955,
       0,   391,     0,     0,     0,     0,  1207,  1207,  1207,     0,
     961,     0,  -885,     0,     0,     0,  1118,     0,   962,     0,
     333,  1118,     0,     0,     0,     0,   395,     0,     0,     0,
       0,   956,     0,     0,  1012,     0,     0,     0,     0,     0,
       0,     0,     0,   947,     0,     0,   803,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0, -1442,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -885,
    -885,     0,   392,     0,     0,  1876,     0,     0,     0,     0,
       0,  1887,  1285,     0,     0,     0,     0,     0,     0,     0,
    1285,     0,     0,     0,     0,     0,  -885,  -885,     0,   957,
       0,  1012,     0,  -885,     0,     0,     0,  -885,     0,  1502,
       0,     0,     0,     0,     0,   948,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     950,     0,     0,     0,  -885,   393,  1887,  -885,  -885,     0,
    1285,     0,  -885,  1068,   958,   959,  -885,     0,  -885,     0,
       0,  -885,     0,  -885,     0,     0,     0,     0,     0,  1988,
       0,     0,     0,  1988,   394,     0,  -885,  -885,     0,   960,
       0,  -885,     0,     0,     0,     0,     0,     0,  1988,  1988,
       0,  -885,     0,  -885,     0,     0,     0,   961,  -885,     0,
       0,     0,     0,  -885,     0,   962,     0,   333,     0,     0,
       0,     0,     0,   395,     0,     0,     0,     0,     0,     0,
       0,  -885,     0,     0,   951,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -885,   389,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1301,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -885,     0,     0,     0,   952,     0,     0,     0,     0,
     953,  1887,     0,     0,   390,     0,   954,     0,     0,   955,
       0,   391,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -885,     0,     0,
       0,     0,     0,     0,     0,     0,  -885,  -885,     0,     0,
    2071,   956,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -885,     0,     0,  1988,
       0,  -885,     0,  -579,   524,     0,  -620,     0,  -620,     0,
       0,     0,     0,  -620,     0,     0,  2111,     0,     0,  -885,
       0,  -620,   392,     0,     0,     0,     0,  -885,     0,  -885,
       0,     0,     0,     0,     0,  -885,  -885,  -885,  -885,  -885,
       0,  -885,     0,  -885,  -885,  -885,  -885,  -885,     0,   957,
       0,     0,  1988,  -620,  -620,     0,     0,     0,     0,     0,
    -620,     0,     0,  1988,     0,     0,  1988,     0,     0,     0,
       0,  -620,     0,     0,  -620,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   393,  -620,     0,     0,     0,
       0,     0,     0,     0,   958,   959,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -620,     0,
       0,     0,     0,     0,   394,  -620,  -620,     0,     0,   960,
       0,     0,     0,     0,     0,     0,  2167,     0,     0,  2169,
       0,     0,  -579,     0,     0,     0,  -579,   961,     0,     0,
       0,     0,     0,     0,     0,   962,  -620,   333,     0,     0,
       0,     0,     0,   395,     0,     0,     0,     0,  -620,  2186,
       0,     0,  -620,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1988,     0,  -620,     0,     0,  1988,  -579,
       0,     0,  -620,     0,     0,  -620,  -620,     0,     0,     0,
       0,     0,     0,  -620,     0,     0,     0,     0,     0,     0,
    -620,     0,  -620,     0,     0,  -620,  2215,     0,     0,     0,
       0,     0,   524,     0,  -620,     0,  -620,     0,     0,  2221,
       0,  -620,     0,     0,     0,     0,     0,     0,     0,  -620,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -620,     0,     0,     0,  -620,     0,  -620,     0,     0,     0,
       0,     0,     0,  -620,     0,     0,     0,     0,     0,     0,
       0,  -620,  -620,     0,     0,     0,     0,     0,  -620,     0,
       0,     0,     0,     0,     0,  -620,     0,     0,     0,  -620,
       0,     0,  -620,     0,     0,     0,     0,     0,     0,     0,
    -620,     0,     0,     0,  -620,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -579,     0,     0,     0,     0,     0,
       0,  -620,     0,     0,     0,     0,  -620,     0,     0,     0,
    -620,     0,     0,  -620,  -620,     0,     0,     0,     0,     0,
       0,   635,     0,  -620,     0,     0,     0,     0,  -620,     0,
    -620,     0,     0,     0,     0,     0,     0,     0,  -620,     0,
     947,     0,     0,   803,  -620,     0,     0,     0,  -620,     0,
       0,     0,     0,     0,     0,     0,  -620,  -620,     0,     0,
    -620,     0,     0,     0,     0,     0,  -620,     0,  -620,  -620,
       0,     0,  -620,  -620,  -620,     0,     0,     0,     0,  -620,
    -620,     0,     0,  -620,  -620,     0,     0,     0,     0,     0,
       0,  -620,     0,     0,  -620,     0,     0,     0,  -620,  -620,
    -620,     0,     0,  -620,  -620,     0,     0,     0,     0,     0,
       0,     0,   948,     0,     0,  -620,     0,     0,     0,     0,
       0,     0,     0,   525,     0,     0,  -620,   950,     0,     0,
       0,     0,     0,     0,     0,     0,   526,     0,  -620,     0,
    1068,     0,  -620,     0,  -620,     0,     0,   947,     0,     0,
     803,  -620,     0,  1168,  1169,  1170,     0,     0,     0,     0,
       0,  1171,     0,   567,   568,   569,   570,   571,   572,     0,
       0,     0,     0,  -620,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -620,     0,
       0,     0,     0,     0,     0,     0,     0,   574,     0,   575,
     576,   577,   578,   579,   580,     0,     0,     0,     0,  -620,
       0,   951,     0,     0,     0,     0,     0,     0,  -620,   948,
       0,     0,   389,     0,     0,     0,     0,     0,     0,     0,
       0,  -620,     0,     0,   950,     0,  -620,     0,  -620,   581,
       0,     0,     0,     0,     0,     0,  -620,     0,     0,     0,
       0,     0,   952,     0,     0,     0,  -620,   953,     0,     0,
       0,   390,     0,   954,     0,  -620,   955,     0,   391,     0,
       0,     0,     0,     0,  -620,     0,  -620,  -620,     0,     0,
    -620,     0,  -620,     0,     0,     0,     0,  -620,     0,     0,
       0,  1172,  1173,     0,     0,     0,     0,     0,   956,     0,
       0,     0,  -620,     0,     0,     0,     0,  -620,     0,     0,
       0,     0,  -620,     0,     0,     0,     0,     0,   951,  1174,
       0,   582,     0,  -620,     0,  1175,     0,     0,     0,   389,
       0,   525,     0,     0,  -620,     0,     0,     0,     0,   392,
       0,     0,     0,     0,   526,     0,     0,     0,  1415,     0,
       0,     0,     0,     0,     0,     0,  1176,     0,     0,   952,
    1177,     0,     0,     0,   953,     0,   957,     0,   390,     0,
     954,   584,     0,   955,     0,   391,     0,     0,     0,     0,
       0,     0,     0,     0,   947,     0,     0,   803,  1178,  1179,
    1168,  1169,  1170,  1180,     0,     0,     0,     0,  1171,     0,
       0,     0,   393,  1181,     0,   956,     0,     0,   586,     0,
    1182,   958,   959,     0,     0,  1183,     0,   588,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     589,   394,     0,  1184,     0,     0,   960,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   392,     0,     0,     0,
       0,     0,     0,     0,   961,     0,   948,     0,     0,     0,
       0,     0,   962,     0,   333,     0,     0,     0,     0,     0,
     395,   950,     0,   957,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   593,   594,   595,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   393,
       0,     0,     0,     0,     0,     0,     0,     0,   958,   959,
       0,     0,     0,     0,     0,     0,     0,     0,  1172,  1173,
       0,     0,     0,     0,     0,   597,   598,   599,   394,     0,
       0,     0,     0,   960,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   951,  1174,     0,     0,     0,
       0,   961,  1175,     0,     0,     0,   389,     0,     0,   962,
       0,   333,     0,     0,     0,     0,     0,   395,  1185,  1186,
    1187,  1188,     0,  1189,     0,  1190,  1191,  1192,  1193,  1194,
       0,     0,     0,  1176,     0,     0,   952,  1177,     0,     0,
       0,   953,     0,     0,     0,   390,     0,   954,     0,     0,
     955,     0,   391,   639,     0,   640,     0,     0,     0,     0,
     641,     0,     0,     0,     0,  1178,  1179,     0,   642,     0,
    1180,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1181,     0,   956,     0,     0,     0,     0,  1182,     0,     0,
       0,     0,  1183,     0,     0,     0,     0,     0,     0,     0,
     643,   644,     0,     0,     0,     0,     0,   645,     0,     0,
    1184,     0,     0,     0,     0,     0,     0,     0,   646,     0,
       0,   647,     0,   392,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   648,   947,     0,     0,   803,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     957,     0,     0,     0,     0,   649,     0,     0,     0,     0,
       0,     0,   650,   651,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   393,     0,     0,     0,
       0,     0,     0,   652,     0,   958,   959,     0,     0,     0,
       0,     0,     0,     0,     0,   653,   948,     0,     0,   654,
       0,     0,     0,     0,     0,   394,     0,   949,     0,     0,
     960,   950,   655,     0,     0,     0,     0,     0,     0,   656,
       0,     0,   657,   658,     0,     0,     0,     0,   961,     0,
     659,     0,     0,     0,     0,     0,   962,   660,   333,   661,
       0,     0,   662,     0,   395,  1185,  1186,  1187,  1188,     0,
    1189,     0,  1190,  1191,  1192,  1193,  1194,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   663,   639,     0,
     640,   664,     0,   665,     0,   641,     0,     0,     0,     0,
     666,     0,     0,   642,     0,   951,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   389,   947,     0,     0,
     803,     0,   667,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   643,   644,   668,     0,     0,
       0,     0,   645,     0,     0,     0,   952,     0,     0,     0,
       0,   953,     0,   646,     0,   390,   647,   954,   669,     0,
     955,     0,   391,     0,     0,     0,     0,   670,   648,     0,
       0,   947,     0,     0,   803,     0,     0,     0,     0,     0,
     671,     0,     0,   947,     0,   672,   803,   673,     0,   948,
     649,     0,   956,     0,     0,   674,     0,   650,   651,     0,
    1027,     0,     0,     0,   950,   675,     0,     0,     0,     0,
       0,     0,     0,     0,   676,     0,     0,     0,     0,     0,
       0,     0,     0,   677,     0,   678,   679,     0,   652,   680,
       0,   681,     0,   392,     0,     0,   682,     0,     0,     0,
     653,     0,     0,   948,   654,     0,     0,     0,     0,     0,
       0,   683,     0,     0,  1072,   948,   684,   655,   950,     0,
     957,   685,     0,     0,   656,     0,     0,   657,   658,     0,
     950,     0,   686,     0,     0,   659,     0,     0,     0,     0,
       0,     0,   660,   687,   661,     0,     0,   662,   951,     0,
       0,     0,     0,   688,     0,     0,   393,     0,     0,   389,
       0,     0,     0,     0,     0,   958,   959,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   663,     0,     0,   394,   664,     0,   665,   952,
     960,     0,     0,     0,   953,   666,     0,     0,   390,     0,
     954,     0,   951,   955,     0,   391,     0,     0,   961,     0,
       0,     0,   947,   389,   951,   803,   962,   667,   333,     0,
       0,     0,     0,     0,   395,   389,     0,     0,     0,     0,
       0,     0,   668,     0,     0,   956,     0,     0,     0,     0,
       0,     0,     0,   952,     0,     0,     0,     0,   953,     0,
       0,     0,   390,   669,   954,   952,     0,   955,     0,   391,
     953,     0,   670,     0,   390,     0,   954,     0,     0,   955,
       0,   391,     0,     0,     0,   671,   392,     0,     0,     0,
     672,     0,   673,     0,   948,     0,     0,     0,     0,   956,
     674,     0,     0,   947,     0,     0,   803,     0,     0,   950,
     675,   956,     0,   957,     0,   947,     0,     0,   803,   676,
       0,     0,     0,     0,     0,     0,     0,     0,   677,     0,
     678,   679,     0,     0,   680,     0,   681,     0,     0,     0,
     392,   682,     0,     0,     0,     0,     0,     0,     0,   393,
       0,     0,   392,     0,     0,     0,   683,     0,   958,   959,
       0,   684,     0,     0,     0,     0,   685,   957,     0,   947,
       0,     0,   803,     0,     0,   948,     0,   686,   394,   957,
       0,     0,     0,   960,     0,   803,     0,   948,   687,  1306,
     950,     0,     0,   951,     0,     0,     0,     0,     0,     0,
       0,   961,   950,   393,   389,     0,     0,     0,     0,   962,
       0,   333,   958,   959,     0,   393,     0,   395,     0,     0,
       0,     0,     0,     0,   958,   959,     0,     0,     0,     0,
       0,     0,   394,     0,   952,     0,     0,   960,     0,   953,
    1162,   948,     0,   390,   394,   954,     0,     0,   955,   960,
     391,     0,     0,     0,   948,   961,   950,     0,     0,     0,
       0,     0,     0,   962,     0,   333,     0,   961,     0,   950,
       0,   395,     0,     0,   951,   962,     0,   333,     0,     0,
     956,     0,     0,   395,     0,   389,   951,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   389,   947,     0,
       0,   803,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   952,     0,     0,     0,     0,
     953,   392,     0,     0,   390,     0,   954,   952,     0,   955,
       0,   391,   953,     0,     0,     0,   390,     0,   954,     0,
     951,   955,     0,   391,     0,     0,     0,     0,   957,     0,
       0,   389,     0,   951,     0,     0,     0,     0,     0,     0,
       0,   956,     0,     0,   389,     0,     0,     0,     0,     0,
     948,     0,     0,   956,     0,     0,     0,     0,     0,     0,
       0,   952,     0,     0,   393,   950,   953,     0,     0,     0,
     390,     0,   954,   958,   959,   955,     0,   391,     0,     0,
       0,     0,   392,   390,     0,   954,     0,     0,   955,     0,
     391,     0,     0,   394,   392,     0,     0,     0,   960,     0,
       0,     0,     0,     0,     0,     0,     0,   956,     0,   957,
       0,     0,     0,     0,     0,     0,   961,     0,     0,     0,
     956,   957,     0,     0,   962,     0,   333,     0,     0,     0,
       0,     0,   395,     0,     0,     0,     0,     0,     0,  1529,
       0,     0,     0,     0,     0,   393,     0,     0,   392,   951,
       0,     0,  1658,     0,   958,   959,     0,   393,     0,     0,
     389,   392,     0,     0,     0,     0,   958,   959,     0,     0,
       0,     0,     0,     0,   394,   957,     0,     0,     0,   960,
       0,     0,     0,     0,     0,     0,   394,     0,   957,     0,
     952,   960,     0,     0,     0,   953,     0,   961,     0,   991,
       0,   954,     0,     0,   955,   962,   391,   333,     0,   961,
       0,   393,     0,   395,     0,     0,     0,   962,     0,   333,
     958,   959,     0,     0,   393,   395,     0,     0,     0,     0,
       0,     0,     0,   958,   959,     0,   956,     0,     0,     0,
     394,     0,     0,     0,     0,   960,     0,   948,     0,     0,
       0,     0,     0,   394,     0,     0,     0,     0,   960,     0,
       0,     0,   950,   961,     0,     0,     0,     0,     0,     0,
       0,   962,     0,   333,     0,     0,   961,   392,     0,   395,
       0,   565,     0,     0,   962,     0,   333,     0,     0,     0,
       0,     0,   395,   566,     0,     0,   567,   568,   569,   570,
     571,   572,   573,     0,   957,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     574,     0,   575,   576,   577,   578,   579,   580,     0,     0,
     393,     0,     0,     0,     0,     0,   951,     0,     0,   958,
     959,     0,     0,     0,     0,     0,     0,   389,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   394,
       0,     0,   581,     0,   960,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   961,     0,     0,     0,   390,     0,   954,     0,
     962,   955,   333,   391,     0,     0,     0,     0,   395,     0,
       0,     0,     0,  1557,     0,  1558,     0,     0,  1559,   567,
     568,   569,   570,   571,   572,   573,  1560,  1561,  1562,     0,
       0,     0,     0,   956,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1563,     0,     0,     0,
       0,     0,     0,   574,   582,   575,   576,   577,   578,   579,
     580,     0,     0,     0,     0,     0,     0,    40,     0,     0,
     583,     0,     0,     0,   392,     0, -1499,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   581,     0,     0,     0,   948,
       0,   957,     0,     0,   584,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   950,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   585,     0,     0,     0,
       0,     0,     0,     0,     0,  1564,     0,   393,     0,     0,
       0,   586,     0,     0,     0,     0,   958,   959,   587,     0,
     588,     0,     0,  1565,     0,     0,  1566,  1567,     0,     0,
       0,     0,     0,   589,     0,     0,   394,     0,     0,     0,
    1568,   960,     0,   590,     0,     0,     0,   582,     0,     0,
     591,     0,     0,     0,     0,     0,     0,     0,     0,   961,
       0,     0,     0,   583,     0,     0,     0,   962,   951,   333,
       0,     0,     0,     0,     0,   395,     0,  1569,     0,   389,
       0,   948,     0,     0,     0,     0,  1570,   592,     0,   593,
     594,   595,     0,     0,     0,     0,   950,   584,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1110,
       0,     0,     0,   596,   953,     0,     0,     0,   390,  1571,
     954,     0,     0,   955,     0,   391,     0,     0,     0,     0,
   -1499,     0,     0,  1572,   586,     0,     0,     0,   597,   598,
     599,   587,     0,   588,     0,     0,     0,     0,     0,     0,
       0,   600,     0,     0,   601,   956,   589,  1573,     0,     0,
       0,   948,     0,     0,     0,   567,   568,   569,   570,   571,
     572,   573,     0,  -318,     0,     0,   950,     0,     0,     0,
     951,  1574,     0,     0,     0,     0,  1575,     0,     0,     0,
       0,   389,  1955,  1956,     0,     0,   392,     0,     0,   574,
    1576,   575,   576,   577,   578,   579,   580,     0,     0,     0,
     592,     0,   593,   594,   595,     0,     0,     0,     0,     0,
       0,  1110,     0,   957,     0,     0,   953,     0,     0,     0,
     390,     0,   954,     0,     0,   955,     0,   391,     0,     0,
       0,   581,     0,     0,     0,     0,  1577,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1578,     0,   393,
     951,   597,   598,   599,     0,     0,     0,   956,   958,   959,
       0,   389,     0,     0,   600,     0,  1579,   601,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   394,     0,
       0,     0,     0,   960,     0,     0,  1580,     0,     0,     0,
       0,  1110,     0,     0,     0,     0,   953,     0,   392,     0,
     390,   961,   954,     0,  1957,   955,     0,   391,     0,   962,
       0,   333,     0,   582,     0,     0,     0,   395,  1111,  1112,
       0,     0,     0,     0,     0,   957,  1113,  1602,     0,   583,
       0,     0,     0,     0,     0,     0,     0,   956,     0,     0,
       0,     0,     0,  1958,  1959,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   393,     0,   584,     0,     0,     0,     0,  1960,     0,
     958,   959,     0,     0,     0,     0,     0,     0,   392,     0,
       0,     0,     0,     0,     0,   585,     0,     0,     0,     0,
     394,     0,     0,     0,     0,   960,     0,     0,     0,     0,
     586,     0,     0,     0,     0,   957,     0,   587,     0,   588,
       0,     0,  1961,   961,     0,     0,     0,     0,     0,     0,
       0,   962,   589,   333,     0,     0,     0,     0,     0,   395,
    1111,  1112,     0,     0,     0,     0,     0,     0,  1113,  1817,
       0,   393,     0,     0,     0,     0,     0,     0,     0,     0,
     958,   959,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     394,     0,     0,     0,     0,   960,   592,     0,   593,   594,
     595,     0,     0,     0,     0,  1962,     0,     0,     0,     0,
       0,     0,     0,   961,     0,     0,     0,     0,     0,  1963,
       0,   962,     0,   333,     0,     0,     0,     0,     0,   395,
    1111,  1112,     0,     0,     0,     0,     0,     0,  1113,     0,
       0,     0,  1964,     0,     0,     0,     0,   597,   598,   599,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     600,     0,     0,   601,  1965,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1966
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-1699))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      83,   165,   364,   621,   657,   601,   236,   478,   805,   410,
     480,  1095,   831,  1267,  1068,  1177,   686,   590,   259,   826,
     261,   627,   263,  1062,   188,   189,   190,   828,   192,   836,
     194,   844,   185,  1496,   769,   827,  1376,  1377,   191,   259,
     962,   261,  1052,   263,   857,  1644,   564,    13,  1162,   433,
       9,     9,  1010,   330,    17,   984,  1334,   210,     6,  1334,
    1018,  1334,   226,  1231,   228,     6,   149,  1222,  1223,  1224,
    1253,   235,     6,   544,  1334,  1334,  1334,    27,   825,   243,
      22,   311,   323,    58,    67,    17,   833,   834,   318,    81,
     331,   255,   256,     9,   258,    91,    53,   338,   262,     6,
    1139,   848,   849,   323,    47,    71,  1064,    91,     6,    84,
      85,   331,   265,   266,  1228,   862,   863,    55,   338,   396,
     143,    87,    69,    11,   365,   116,   290,    60,  1138,   293,
     294,   361,   296,   115,    48,  1271,    67,   175,   368,    55,
      55,    69,   115,  1777,  1258,   365,   165,   367,   312,   165,
     947,   381,  1335,   207,    67,   952,   164,   627,    67,   109,
    1429,    67,   564,  1762,   866,   329,   116,   115,    56,  1098,
      63,     9,    48,  1356,   227,   162,  1445,     9,   408,    29,
     798,    55,   412,   403,   425,   290,    48,   464,   341,   272,
     162,   117,  1306,   756,   200,    21,    88,    47,    63,   363,
     227,   227,    82,    91,    92,   425,    94,   371,  1133,   207,
     144,   290,  1009,   211,   102,   207,   374,    22,   965,   108,
      82,    48,   269,  1563,  1493,   315,   231,   974,   846,  1569,
      30,  1360,   207,  1765,   112,  1245,   466,  1935,  1367,  1937,
      21,   227,  1326,   239,   628,  1374,   993,  1060,    39,   479,
     180,   167,   242,  1721,   772,   101,   420,  1311,   165,    27,
     206,   309,   269,   346,  1533,   207,   349,   919,   156,   227,
     101,   112,   193,    24,   169,   439,   440,   300,   112,  1462,
    1027,   511,   117,   990,   312,     0,   516,   231,  1456,   392,
     193,  1459,  1047,  1407,   161,     9,   430,  1307,    36,   295,
     216,   521,   522,     8,   104,   239,   924,   251,   283,   443,
     256,   475,   908,  1110,   181,   362,   364,   365,   168,   309,
     270,   311,  1069,   169,   429,   430,   161,  1074,  1083,    34,
    1367,  1289,   337,   939,   424,   181,   500,  1374,   227,  1046,
     228,   109,   445,  1162,   508,   503,  1275,   443,   278,   227,
     429,   227,     9,   339,   275,   585,  1366,   344,  1890,   224,
     407,   934,   935,   370,   267,   312,  1420,   350,   396,   107,
     772,   591,   344,   124,   937,   938,   203,   430,  2076,   543,
     306,   851,   227,   436,   548,     9,   227,   551,   552,   443,
     554,   555,  1661,   227,   558,   227,   311,  1436,   291,  1101,
    1052,   315,   207,   430,   430,   443,  1213,   430,   395,  1228,
    1546,   430,  2046,   251,   430,  1162,     9,   423,  1886,   350,
     353,  1889,   430,  1230,   319,    49,   291,   227,   354,   321,
    1355,   413,   430,   425,   430,   315,   600,   350,   429,  1258,
     413,   350,  1255,   234,   350,   393,   430,  1239,  1195,   396,
    1408,   277,   393,   315,   342,   393,   399,   385,   390,  1111,
    1112,  1113,    55,   446,   427,   413,   423,   828,   443,  1121,
     308,   430,   430,   211,   188,  1485,  1939,  1269,   444,   429,
    1227,  1228,   430,  1612,   400,   846,  1138,  1306,   430,   430,
     851,  1143,   384,  1145,   382,  1147,   430,  1149,  1752,  1151,
    1152,  1153,  1154,  1155,  1156,  1157,  1158,  1517,  1126,  1787,
     424,  1258,  1787,   227,  1787,   446,  1460,   758,   759,  1172,
     234,  1465,   429,   430,   765,  1317,   803,  1787,  1787,  1787,
    1698,   188,   430,   446,  1492,  1690,   756,   446,   758,   759,
     446,   430,   430,    48,   424,   765,  1293,  1816,  1018,   399,
    1297,  1298,   430,  1300,   430,   443,   940,   431,   919,  1306,
     436,   160,   424,    48,   188,  2033,  1036,  1274,   394,  1142,
     227,  1134,   398,  2036,   167,  1612,  1149,   234,    67,   429,
     120,  1695,   746,  1697,   748,   430,  1104,  2186,  1407,   430,
     820,   305,  1775,  1245,   218,   188,   430,  1332,   429,   430,
    1869,   200,  1871,   227,   768,   191,   133,   827,   227,   208,
     234,   227,  1666,   394,  1810,  1955,   354,   398,  1732,   259,
     227,   366,   176,   216,    29,   919,  1418,   847,   173,    60,
    1899,   851,   239,   853,   227,   855,   856,   231,   858,   443,
     157,   234,    67,   180,   242,   231,   887,   217,   305,   227,
    1764,    31,   231,   873,   368,  1307,   144,   251,   216,   936,
     358,  1930,  1931,   904,  1237,   251,   953,   887,   111,   242,
     890,   239,   251,  1279,   358,  1036,   283,  1283,  1491,   278,
     204,   305,   227,   397,   904,  1337,  2149,   917,   238,    26,
     216,   978,  1344,  1345,  1346,  1347,  1348,  1349,  1350,   444,
     133,  1711,   922,   227,   236,  1663,  1635,  1636,  1637,   407,
     114,   368,   305,   253,  1366,   120,   430,   937,   938,   180,
     443,  1643,   436,   407,   302,   180,  1648,  1649,   180,   882,
    1652,  1653,  1654,   180,  1656,  1657,  1680,  1681,  1208,   289,
     397,   905,   340,   180,   368,  1799,    29,   301,  1692,   832,
    1111,  1112,  1113,    96,   362,  1809,  1810,  1427,    11,  1769,
    1121,    67,   279,   227,  1337,  1566,   336,   340,   300,   852,
     443,   854,  1730,   397,   301,   368,   859,  1524,   158,   436,
      63,   238,  1143,   236,  1145,   868,  1147,  2211,  1149,   429,
    1151,  1152,  1153,  1154,  1155,  1156,  1157,  1158,     9,   407,
       4,   338,   919,    56,   397,   236,  2230,   400,  1278,  1382,
     315,   430,   436,  1466,   430,    19,   348,  1111,  1112,  1113,
    2016,  2017,  1475,   430,    28,   393,   331,  1121,  1048,   436,
     315,   430,   289,  1485,  1486,   429,   430,   430,    91,    92,
     426,    94,   400,   436,    55,   443,   331,   300,  1318,   102,
     429,  1145,   295,  2107,  1095,   235,    60,  1151,  1152,  1153,
    1154,   350,   249,  1157,  1158,  1517,   191,   192,   301,   300,
     236,  2140,  2141,  1103,   400,  1095,  1695,   338,  1697,   331,
     358,    24,    25,   338,   412,    11,  1830,   437,   438,   188,
     173,   338,  1699,   358,   331,   348,  2058,   425,  2060,   150,
     151,  1845,   985,   156,   169,    79,   231,   294,   195,  1948,
     227,   443,    12,  1732,  1134,    15,    16,   348,   855,   424,
     181,    64,   353,    66,  1868,   350,   251,   178,   227,   407,
    1094,  1875,   249,   184,   300,   234,   873,   224,   443,   424,
     346,   224,   407,  1750,    70,  1764,   207,  1520,   437,   438,
     439,   440,  1605,   442,    97,    98,    99,   446,   443,   309,
    2214,   311,  2016,  2017,   215,  1909,  1910,  1437,   219,   265,
     160,   443,   289,   238,  1918,   228,  1337,   188,   297,   833,
     437,   438,   348,  1344,  1345,  1346,  1347,  1348,  1349,  1350,
     443,   195,  1739,  1645,  1111,  1112,  1113,   358,  1650,   430,
     268,   144,   270,   146,  1121,   216,   305,     8,   291,   863,
     200,   154,   437,   438,   439,   440,   227,   442,   208,  1239,
     224,   446,   309,   234,   114,  1495,  1143,   231,  1145,   316,
    1147,   327,   443,    34,  1151,  1152,  1153,  1154,  1155,  1156,
    1157,  1158,  1511,   231,   350,   163,   407,  2131,   443,  1269,
    1344,  1345,  1346,  1347,  1348,  1349,  1350,  1526,   443,  1711,
      78,  1531,  2006,   251,   188,   346,  2010,  1719,  1538,   368,
     120,   367,   276,   369,   443,    93,   394,   443,   282,   161,
     398,  2025,   225,   201,   301,  1326,  1327,  1488,   278,   342,
    1837,   209,  1710,   114,   305,   231,   239,  1317,   397,   181,
      46,   426,   429,   227,   429,   309,  1326,  1327,   300,  2053,
     234,  2055,   316,    59,   129,   251,   443,  1769,   148,   188,
     153,   443,  2066,  1792,   157,   329,   314,   286,   287,   382,
     346,   437,   438,   439,   440,   231,   442,   436,  1807,  1808,
     446,   300,  2086,  2087,   244,   245,   469,  1765,   218,   353,
      96,   474,   356,   223,   432,   251,   206,   368,   227,   177,
     364,   163,   262,   263,   443,   234,  1963,   346,   289,   188,
     374,    32,   430,   294,    35,  1922,   206,   430,   309,   230,
     311,   305,    43,    44,    45,   331,   397,   346,   394,   400,
       2,   395,   398,   444,     6,   118,   447,   448,  1418,    86,
      87,   443,  2021,   253,  2023,  1566,   256,   277,   227,   227,
    1394,   229,   155,  1397,   232,   234,   159,   405,  1402,   430,
     224,   225,  2166,   110,   254,   436,   256,  1344,  1345,  1346,
    1347,  1348,  1349,  1350,   439,   440,   305,   442,   147,   443,
     149,   429,   443,   255,   368,   257,   264,     6,   391,     9,
       9,   309,    12,   311,   443,    15,    16,   147,  1729,   149,
     443,   207,   260,   261,  1734,   188,   212,   260,   261,   349,
    1740,   443,  1890,   397,   224,   225,   222,   443,   209,  1948,
     395,   443,   352,   346,  1645,   226,   305,   430,  1143,  1650,
     430,   152,  1147,   430,   443,   443,  2043,   175,   273,   368,
    1155,  1156,   443,    23,   227,   443,   430,   385,  1549,   170,
     346,   234,   436,   322,   332,   437,   438,   439,   440,    78,
     442,   362,   207,   246,  1554,   101,   187,   449,     6,  1549,
    1801,     9,  2001,   443,    93,   437,   438,   439,   440,   430,
     442,  1571,   374,  2012,   357,    55,  2015,   449,  1589,   368,
      81,  1645,   437,   438,   439,   440,  1650,   442,   169,   377,
     378,  1525,   443,   309,   310,   346,  1607,   436,   341,  1589,
      48,   430,   233,   362,   273,   103,   322,   227,   324,   353,
     204,   443,   305,   240,   402,   430,  1550,  1607,    65,   443,
     346,   150,   240,    22,  1558,   443,  2143,   284,   285,  2146,
      78,  1565,   420,   267,    82,   430,  1647,   227,   443,   291,
     428,    80,   430,    80,   443,    93,   443,   436,   177,   280,
     430,   437,   438,   439,   440,   425,   442,  1647,   390,   188,
     446,   430,    30,   307,    32,   393,   225,    35,   325,   326,
     416,   417,   418,   419,   193,   368,   430,    45,   371,   372,
    2197,   309,  1616,  2122,   393,  1619,   354,    54,  2127,   218,
     437,   438,   439,   440,   223,   442,   429,   374,   227,   446,
     229,    36,   333,   232,    26,   234,   181,   443,   424,   362,
     346,   374,   343,   443,   244,   245,   443,   211,  2235,   437,
     438,   439,   440,   430,   442,   354,   218,   443,   446,   177,
     427,   207,   262,   263,   336,   264,   227,   103,  2104,   296,
     188,   371,   277,   436,  2132,   824,   271,   436,   393,   828,
     416,   417,   418,   419,   833,   445,    26,   390,  1645,   838,
     839,   352,   267,  1650,   450,   844,   845,   846,   168,   443,
     218,   443,   851,   404,   430,   223,   305,   227,   857,   227,
     130,   229,   101,  1783,   232,    17,   234,   866,   867,  1723,
     869,   437,   438,   439,   440,   166,   442,   429,   181,   392,
     446,   390,   170,   332,   445,   227,   174,    29,   121,  2232,
    2233,   416,   417,   418,   419,   122,   264,   198,    55,   187,
     445,   269,   445,   437,   438,   439,   440,  1959,   442,   445,
     445,   393,   446,   437,   438,   439,   440,   445,   442,   368,
     919,   124,   446,   423,   445,   445,   445,   445,   377,   378,
     445,   338,   309,   445,   126,  1789,   127,   305,   389,    95,
    1794,   393,   131,    48,   392,   233,   132,   315,   397,   390,
     949,   387,   392,   402,   173,   137,   425,   239,    48,   140,
     173,  1734,   106,   323,   332,  1896,   370,   108,   270,   108,
     429,   420,   430,   393,   180,   331,   299,   227,   415,   428,
     388,   430,    78,   157,   427,   984,  1896,   436,   128,   427,
     165,   393,   280,   356,   362,   444,  1850,    93,   203,   393,
     368,    48,  1856,   211,   173,   203,   116,   270,   186,   377,
     378,  1010,   442,   435,   355,   434,   304,   211,    78,  1018,
    1019,   331,   260,   224,   393,   363,   125,   256,    17,   397,
     446,   446,   255,    93,   402,   180,   390,  1036,   321,   407,
     328,   446,   393,   446,    48,   333,   132,     8,   173,   427,
     120,   427,   420,  1052,   393,   343,   424,     9,   298,   347,
     428,  1060,   430,  1983,   167,  1064,   297,   195,   436,   334,
     258,   319,   259,  1072,   119,   171,  1075,   424,   104,   424,
      48,   177,   169,   135,   231,   253,   136,   252,   290,   138,
     275,   274,   107,     7,   384,   279,   110,  1951,   213,  1098,
      64,   394,  1101,   123,   318,   130,   318,    48,  1962,    96,
    1964,   171,  1111,  1112,  1113,   231,   404,   177,   211,   257,
     139,    90,  1121,   254,   142,    87,   414,   196,   185,  2039,
     214,   227,   427,   229,   380,    48,   232,   396,   430,  1138,
     231,  1995,  1996,   297,  1143,   141,  1145,   168,  1147,   231,
     173,   283,  1151,  1152,  1153,  1154,  1155,  1156,  1157,  1158,
     297,   334,   134,   412,   150,   274,   274,   227,   264,   229,
     150,    48,   232,     6,  2094,    21,   182,    53,  2109,   128,
     177,   317,   167,   196,  1290,   460,  1084,   537,   132,   396,
    1779,  2045,   893,   346,  2114,  2115,   549,   107,    48,  2109,
    2131,   887,   212,  1733,   264,   217,   149,   819,   522,   284,
     797,  1787,  1591,  2129,   924,  1978,   505,  2115,   120,  1668,
     907,  2131,   442,  1737,   533,  1378,     6,   993,   772,     9,
    1379,  1631,  1666,   998,  1863,  1230,   332,  1698,  1459,  1233,
    1242,  2095,  2096,  1248,  1719,  2099,  1245,  1483,  1036,  1738,
    1880,  1507,  2106,  1318,  1283,  1754,  1255,  1058,  2178,  2179,
     858,  1060,  2182,  1069,  2184,  1538,  1933,  1538,  1609,  1268,
    1938,  2046,   332,  2204,  1944,  1745,  1275,  1434,  1195,  1923,
    1923,   377,   378,  1282,  1923,  1048,  1202,  1520,   920,   224,
    1289,   387,  1167,  2147,  2204,   802,  1253,   292,    78,   556,
    2133,  2211,  1301,   929,  2224,   762,   402,    56,  1307,  1795,
      -1,  1124,  2085,    93,  1313,    -1,   412,   377,   378,    -1,
    2230,    -1,    -1,    -1,   420,    -1,  2180,   387,    -1,   425,
    1329,    -1,   428,   429,   430,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   402,    -1,    -1,  1344,  1345,  1346,  1347,  1348,
    1349,  1350,   412,    -1,    -1,    -1,    -1,    -1,    -1,  2213,
     420,    -1,    -1,   143,    -1,   425,    -1,  1366,   428,   429,
     430,    -1,    -1,    -1,    -1,  2148,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1386,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,
      -1,    -1,    -1,     6,    -1,    -1,     9,    -1,   188,  1408,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1421,  1422,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,  2212,
      -1,    -1,    -1,   223,    -1,    -1,    -1,   227,    -1,   229,
      -1,    -1,   232,    -1,   234,    -1,    -1,    -1,    -1,    -1,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   264,    -1,  1485,  1486,    -1,    -1,
      93,    -1,  1491,  1492,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1509,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1517,    -1,
      -1,    -1,    -1,    -1,    -1,   305,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1532,    -1,    -1,    -1,    -1,  1537,  1538,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,   332,    -1,    -1,     6,    -1,    -1,     9,    -1,
      -1,    12,    13,    14,    -1,    -1,    -1,  1566,    -1,    20,
      -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,  1577,    -1,
    1579,    -1,    -1,    -1,    -1,   188,    -1,    -1,   368,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   377,   378,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   394,   218,    -1,   397,   398,    -1,
     223,   224,   402,    -1,   227,    -1,   229,    78,    -1,   232,
      -1,   234,    -1,    -1,    -1,    -1,  1635,  1636,  1637,    -1,
     420,    -1,    93,    -1,    -1,    -1,  1645,    -1,   428,    -1,
     430,  1650,    -1,    -1,    -1,    -1,   436,    -1,    -1,    -1,
      -1,   264,    -1,    -1,  1663,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     6,    -1,    -1,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   291,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,
     151,    -1,   305,    -1,    -1,  1704,    -1,    -1,    -1,    -1,
      -1,  1710,  1711,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1719,    -1,    -1,    -1,    -1,    -1,   177,   178,    -1,   332,
      -1,  1730,    -1,   184,    -1,    -1,    -1,   188,    -1,  1738,
      -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      93,    -1,    -1,    -1,   215,   368,  1765,   218,   219,    -1,
    1769,    -1,   223,   106,   377,   378,   227,    -1,   229,    -1,
      -1,   232,    -1,   234,    -1,    -1,    -1,    -1,    -1,  1788,
      -1,    -1,    -1,  1792,   397,    -1,   247,   248,    -1,   402,
      -1,   252,    -1,    -1,    -1,    -1,    -1,    -1,  1807,  1808,
      -1,   262,    -1,   264,    -1,    -1,    -1,   420,   269,    -1,
      -1,    -1,    -1,   274,    -1,   428,    -1,   430,    -1,    -1,
      -1,    -1,    -1,   436,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   292,    -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   305,   188,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     203,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   332,    -1,    -1,    -1,   218,    -1,    -1,    -1,    -1,
     223,  1890,    -1,    -1,   227,    -1,   229,    -1,    -1,   232,
      -1,   234,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   368,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   377,   378,    -1,    -1,
    1929,   264,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   397,    -1,    -1,  1948,
      -1,   402,    -1,     0,     1,    -1,     3,    -1,     5,    -1,
      -1,    -1,    -1,    10,    -1,    -1,  1965,    -1,    -1,   420,
      -1,    18,   305,    -1,    -1,    -1,    -1,   428,    -1,   430,
      -1,    -1,    -1,    -1,    -1,   436,   437,   438,   439,   440,
      -1,   442,    -1,   444,   445,   446,   447,   448,    -1,   332,
      -1,    -1,  2001,    50,    51,    -1,    -1,    -1,    -1,    -1,
      57,    -1,    -1,  2012,    -1,    -1,  2015,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    71,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   368,    83,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   377,   378,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,
      -1,    -1,    -1,    -1,   397,   112,   113,    -1,    -1,   402,
      -1,    -1,    -1,    -1,    -1,    -1,  2075,    -1,    -1,  2078,
      -1,    -1,   129,    -1,    -1,    -1,   133,   420,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   428,   143,   430,    -1,    -1,
      -1,    -1,    -1,   436,    -1,    -1,    -1,    -1,   155,  2108,
      -1,    -1,   159,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  2122,    -1,   172,    -1,    -1,  2127,   176,
      -1,    -1,   179,    -1,    -1,   182,   183,    -1,    -1,    -1,
      -1,    -1,    -1,   190,    -1,    -1,    -1,    -1,    -1,    -1,
     197,    -1,   199,    -1,    -1,   202,  2155,    -1,    -1,    -1,
      -1,    -1,     1,    -1,     3,    -1,     5,    -1,    -1,  2168,
      -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     237,    -1,    -1,    -1,   241,    -1,   243,    -1,    -1,    -1,
      -1,    -1,    -1,   250,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    51,    -1,    -1,    -1,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    -1,    -1,   272,    -1,    -1,    -1,    68,
      -1,    -1,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     287,    -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   301,    -1,    -1,    -1,    -1,    -1,
      -1,   308,    -1,    -1,    -1,    -1,   105,    -1,    -1,    -1,
     317,    -1,    -1,   112,   113,    -1,    -1,    -1,    -1,    -1,
      -1,   120,    -1,   330,    -1,    -1,    -1,    -1,   335,    -1,
     337,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   345,    -1,
       6,    -1,    -1,     9,   143,    -1,    -1,    -1,   355,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   155,   364,    -1,    -1,
     159,    -1,    -1,    -1,    -1,    -1,   373,    -1,   375,   376,
      -1,    -1,   379,   172,   381,    -1,    -1,    -1,    -1,   386,
     179,    -1,    -1,   182,   183,    -1,    -1,    -1,    -1,    -1,
      -1,   190,    -1,    -1,   401,    -1,    -1,    -1,   197,   406,
     199,    -1,    -1,   202,   411,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    -1,    -1,   422,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   430,    -1,    -1,   433,    93,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   443,    -1,   237,    -1,
     106,    -1,   241,    -1,   243,    -1,    -1,     6,    -1,    -1,
       9,   250,    -1,    12,    13,    14,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,   272,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   287,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    72,
      73,    74,    75,    76,    77,    -1,    -1,    -1,    -1,   308,
      -1,   177,    -1,    -1,    -1,    -1,    -1,    -1,   317,    78,
      -1,    -1,   188,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   330,    -1,    -1,    93,    -1,   335,    -1,   337,   112,
      -1,    -1,    -1,    -1,    -1,    -1,   345,    -1,    -1,    -1,
      -1,    -1,   218,    -1,    -1,    -1,   355,   223,    -1,    -1,
      -1,   227,    -1,   229,    -1,   364,   232,    -1,   234,    -1,
      -1,    -1,    -1,    -1,   373,    -1,   375,   376,    -1,    -1,
     379,    -1,   381,    -1,    -1,    -1,    -1,   386,    -1,    -1,
      -1,   150,   151,    -1,    -1,    -1,    -1,    -1,   264,    -1,
      -1,    -1,   401,    -1,    -1,    -1,    -1,   406,    -1,    -1,
      -1,    -1,   411,    -1,    -1,    -1,    -1,    -1,   177,   178,
      -1,   194,    -1,   422,    -1,   184,    -1,    -1,    -1,   188,
      -1,   430,    -1,    -1,   433,    -1,    -1,    -1,    -1,   305,
      -1,    -1,    -1,    -1,   443,    -1,    -1,    -1,   207,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   215,    -1,    -1,   218,
     219,    -1,    -1,    -1,   223,    -1,   332,    -1,   227,    -1,
     229,   244,    -1,   232,    -1,   234,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     6,    -1,    -1,     9,   247,   248,
      12,    13,    14,   252,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,   368,   262,    -1,   264,    -1,    -1,   281,    -1,
     269,   377,   378,    -1,    -1,   274,    -1,   290,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     303,   397,    -1,   292,    -1,    -1,   402,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   305,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   420,    -1,    78,    -1,    -1,    -1,
      -1,    -1,   428,    -1,   430,    -1,    -1,    -1,    -1,    -1,
     436,    93,    -1,   332,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   359,   360,   361,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   368,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   377,   378,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,   151,
      -1,    -1,    -1,    -1,    -1,   408,   409,   410,   397,    -1,
      -1,    -1,    -1,   402,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   177,   178,    -1,    -1,    -1,
      -1,   420,   184,    -1,    -1,    -1,   188,    -1,    -1,   428,
      -1,   430,    -1,    -1,    -1,    -1,    -1,   436,   437,   438,
     439,   440,    -1,   442,    -1,   444,   445,   446,   447,   448,
      -1,    -1,    -1,   215,    -1,    -1,   218,   219,    -1,    -1,
      -1,   223,    -1,    -1,    -1,   227,    -1,   229,    -1,    -1,
     232,    -1,   234,     3,    -1,     5,    -1,    -1,    -1,    -1,
      10,    -1,    -1,    -1,    -1,   247,   248,    -1,    18,    -1,
     252,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     262,    -1,   264,    -1,    -1,    -1,    -1,   269,    -1,    -1,
      -1,    -1,   274,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    -1,    -1,    -1,    -1,    -1,    57,    -1,    -1,
     292,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,
      -1,    71,    -1,   305,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    83,     6,    -1,    -1,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     332,    -1,    -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,
      -1,    -1,   112,   113,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   368,    -1,    -1,    -1,
      -1,    -1,    -1,   143,    -1,   377,   378,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   155,    78,    -1,    -1,   159,
      -1,    -1,    -1,    -1,    -1,   397,    -1,    89,    -1,    -1,
     402,    93,   172,    -1,    -1,    -1,    -1,    -1,    -1,   179,
      -1,    -1,   182,   183,    -1,    -1,    -1,    -1,   420,    -1,
     190,    -1,    -1,    -1,    -1,    -1,   428,   197,   430,   199,
      -1,    -1,   202,    -1,   436,   437,   438,   439,   440,    -1,
     442,    -1,   444,   445,   446,   447,   448,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   237,     3,    -1,
       5,   241,    -1,   243,    -1,    10,    -1,    -1,    -1,    -1,
     250,    -1,    -1,    18,    -1,   177,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   188,     6,    -1,    -1,
       9,    -1,   272,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    51,   287,    -1,    -1,
      -1,    -1,    57,    -1,    -1,    -1,   218,    -1,    -1,    -1,
      -1,   223,    -1,    68,    -1,   227,    71,   229,   308,    -1,
     232,    -1,   234,    -1,    -1,    -1,    -1,   317,    83,    -1,
      -1,     6,    -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,
     330,    -1,    -1,     6,    -1,   335,     9,   337,    -1,    78,
     105,    -1,   264,    -1,    -1,   345,    -1,   112,   113,    -1,
      89,    -1,    -1,    -1,    93,   355,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   364,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   373,    -1,   375,   376,    -1,   143,   379,
      -1,   381,    -1,   305,    -1,    -1,   386,    -1,    -1,    -1,
     155,    -1,    -1,    78,   159,    -1,    -1,    -1,    -1,    -1,
      -1,   401,    -1,    -1,    89,    78,   406,   172,    93,    -1,
     332,   411,    -1,    -1,   179,    -1,    -1,   182,   183,    -1,
      93,    -1,   422,    -1,    -1,   190,    -1,    -1,    -1,    -1,
      -1,    -1,   197,   433,   199,    -1,    -1,   202,   177,    -1,
      -1,    -1,    -1,   443,    -1,    -1,   368,    -1,    -1,   188,
      -1,    -1,    -1,    -1,    -1,   377,   378,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   237,    -1,    -1,   397,   241,    -1,   243,   218,
     402,    -1,    -1,    -1,   223,   250,    -1,    -1,   227,    -1,
     229,    -1,   177,   232,    -1,   234,    -1,    -1,   420,    -1,
      -1,    -1,     6,   188,   177,     9,   428,   272,   430,    -1,
      -1,    -1,    -1,    -1,   436,   188,    -1,    -1,    -1,    -1,
      -1,    -1,   287,    -1,    -1,   264,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   218,    -1,    -1,    -1,    -1,   223,    -1,
      -1,    -1,   227,   308,   229,   218,    -1,   232,    -1,   234,
     223,    -1,   317,    -1,   227,    -1,   229,    -1,    -1,   232,
      -1,   234,    -1,    -1,    -1,   330,   305,    -1,    -1,    -1,
     335,    -1,   337,    -1,    78,    -1,    -1,    -1,    -1,   264,
     345,    -1,    -1,     6,    -1,    -1,     9,    -1,    -1,    93,
     355,   264,    -1,   332,    -1,     6,    -1,    -1,     9,   364,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   373,    -1,
     375,   376,    -1,    -1,   379,    -1,   381,    -1,    -1,    -1,
     305,   386,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   368,
      -1,    -1,   305,    -1,    -1,    -1,   401,    -1,   377,   378,
      -1,   406,    -1,    -1,    -1,    -1,   411,   332,    -1,     6,
      -1,    -1,     9,    -1,    -1,    78,    -1,   422,   397,   332,
      -1,    -1,    -1,   402,    -1,     9,    -1,    78,   433,   173,
      93,    -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   420,    93,   368,   188,    -1,    -1,    -1,    -1,   428,
      -1,   430,   377,   378,    -1,   368,    -1,   436,    -1,    -1,
      -1,    -1,    -1,    -1,   377,   378,    -1,    -1,    -1,    -1,
      -1,    -1,   397,    -1,   218,    -1,    -1,   402,    -1,   223,
     393,    78,    -1,   227,   397,   229,    -1,    -1,   232,   402,
     234,    -1,    -1,    -1,    78,   420,    93,    -1,    -1,    -1,
      -1,    -1,    -1,   428,    -1,   430,    -1,   420,    -1,    93,
      -1,   436,    -1,    -1,   177,   428,    -1,   430,    -1,    -1,
     264,    -1,    -1,   436,    -1,   188,   177,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   188,     6,    -1,
      -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   218,    -1,    -1,    -1,    -1,
     223,   305,    -1,    -1,   227,    -1,   229,   218,    -1,   232,
      -1,   234,   223,    -1,    -1,    -1,   227,    -1,   229,    -1,
     177,   232,    -1,   234,    -1,    -1,    -1,    -1,   332,    -1,
      -1,   188,    -1,   177,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   264,    -1,    -1,   188,    -1,    -1,    -1,    -1,    -1,
      78,    -1,    -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   218,    -1,    -1,   368,    93,   223,    -1,    -1,    -1,
     227,    -1,   229,   377,   378,   232,    -1,   234,    -1,    -1,
      -1,    -1,   305,   227,    -1,   229,    -1,    -1,   232,    -1,
     234,    -1,    -1,   397,   305,    -1,    -1,    -1,   402,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   264,    -1,   332,
      -1,    -1,    -1,    -1,    -1,    -1,   420,    -1,    -1,    -1,
     264,   332,    -1,    -1,   428,    -1,   430,    -1,    -1,    -1,
      -1,    -1,   436,    -1,    -1,    -1,    -1,    -1,    -1,   362,
      -1,    -1,    -1,    -1,    -1,   368,    -1,    -1,   305,   177,
      -1,    -1,   363,    -1,   377,   378,    -1,   368,    -1,    -1,
     188,   305,    -1,    -1,    -1,    -1,   377,   378,    -1,    -1,
      -1,    -1,    -1,    -1,   397,   332,    -1,    -1,    -1,   402,
      -1,    -1,    -1,    -1,    -1,    -1,   397,    -1,   332,    -1,
     218,   402,    -1,    -1,    -1,   223,    -1,   420,    -1,   227,
      -1,   229,    -1,    -1,   232,   428,   234,   430,    -1,   420,
      -1,   368,    -1,   436,    -1,    -1,    -1,   428,    -1,   430,
     377,   378,    -1,    -1,   368,   436,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   377,   378,    -1,   264,    -1,    -1,    -1,
     397,    -1,    -1,    -1,    -1,   402,    -1,    78,    -1,    -1,
      -1,    -1,    -1,   397,    -1,    -1,    -1,    -1,   402,    -1,
      -1,    -1,    93,   420,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   428,    -1,   430,    -1,    -1,   420,   305,    -1,   436,
      -1,    21,    -1,    -1,   428,    -1,   430,    -1,    -1,    -1,
      -1,    -1,   436,    33,    -1,    -1,    36,    37,    38,    39,
      40,    41,    42,    -1,   332,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    72,    73,    74,    75,    76,    77,    -1,    -1,
     368,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,   377,
     378,    -1,    -1,    -1,    -1,    -1,    -1,   188,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   397,
      -1,    -1,   112,    -1,   402,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   420,    -1,    -1,    -1,   227,    -1,   229,    -1,
     428,   232,   430,   234,    -1,    -1,    -1,    -1,   436,    -1,
      -1,    -1,    -1,    30,    -1,    32,    -1,    -1,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    70,   194,    72,    73,    74,    75,    76,
      77,    -1,    -1,    -1,    -1,    -1,    -1,   207,    -1,    -1,
     210,    -1,    -1,    -1,   305,    -1,   216,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   112,    -1,    -1,    -1,    78,
      -1,   332,    -1,    -1,   244,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   266,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   152,    -1,   368,    -1,    -1,
      -1,   281,    -1,    -1,    -1,    -1,   377,   378,   288,    -1,
     290,    -1,    -1,   170,    -1,    -1,   173,   174,    -1,    -1,
      -1,    -1,    -1,   303,    -1,    -1,   397,    -1,    -1,    -1,
     187,   402,    -1,   313,    -1,    -1,    -1,   194,    -1,    -1,
     320,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   420,
      -1,    -1,    -1,   210,    -1,    -1,    -1,   428,   177,   430,
      -1,    -1,    -1,    -1,    -1,   436,    -1,   224,    -1,   188,
      -1,    78,    -1,    -1,    -1,    -1,   233,   357,    -1,   359,
     360,   361,    -1,    -1,    -1,    -1,    93,   244,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,
      -1,    -1,    -1,   383,   223,    -1,    -1,    -1,   227,   266,
     229,    -1,    -1,   232,    -1,   234,    -1,    -1,    -1,    -1,
     400,    -1,    -1,   280,   281,    -1,    -1,    -1,   408,   409,
     410,   288,    -1,   290,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   421,    -1,    -1,   424,   264,   303,   304,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      41,    42,    -1,   443,    -1,    -1,    93,    -1,    -1,    -1,
     177,   328,    -1,    -1,    -1,    -1,   333,    -1,    -1,    -1,
      -1,   188,    63,    64,    -1,    -1,   305,    -1,    -1,    70,
     347,    72,    73,    74,    75,    76,    77,    -1,    -1,    -1,
     357,    -1,   359,   360,   361,    -1,    -1,    -1,    -1,    -1,
      -1,   218,    -1,   332,    -1,    -1,   223,    -1,    -1,    -1,
     227,    -1,   229,    -1,    -1,   232,    -1,   234,    -1,    -1,
      -1,   112,    -1,    -1,    -1,    -1,   393,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   404,    -1,   368,
     177,   408,   409,   410,    -1,    -1,    -1,   264,   377,   378,
      -1,   188,    -1,    -1,   421,    -1,   423,   424,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   397,    -1,
      -1,    -1,    -1,   402,    -1,    -1,   443,    -1,    -1,    -1,
      -1,   218,    -1,    -1,    -1,    -1,   223,    -1,   305,    -1,
     227,   420,   229,    -1,   185,   232,    -1,   234,    -1,   428,
      -1,   430,    -1,   194,    -1,    -1,    -1,   436,   437,   438,
      -1,    -1,    -1,    -1,    -1,   332,   445,   446,    -1,   210,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   264,    -1,    -1,
      -1,    -1,    -1,   224,   225,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   368,    -1,   244,    -1,    -1,    -1,    -1,   249,    -1,
     377,   378,    -1,    -1,    -1,    -1,    -1,    -1,   305,    -1,
      -1,    -1,    -1,    -1,    -1,   266,    -1,    -1,    -1,    -1,
     397,    -1,    -1,    -1,    -1,   402,    -1,    -1,    -1,    -1,
     281,    -1,    -1,    -1,    -1,   332,    -1,   288,    -1,   290,
      -1,    -1,   293,   420,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   428,   303,   430,    -1,    -1,    -1,    -1,    -1,   436,
     437,   438,    -1,    -1,    -1,    -1,    -1,    -1,   445,   446,
      -1,   368,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     377,   378,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     397,    -1,    -1,    -1,    -1,   402,   357,    -1,   359,   360,
     361,    -1,    -1,    -1,    -1,   366,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   420,    -1,    -1,    -1,    -1,    -1,   380,
      -1,   428,    -1,   430,    -1,    -1,    -1,    -1,    -1,   436,
     437,   438,    -1,    -1,    -1,    -1,    -1,    -1,   445,    -1,
      -1,    -1,   403,    -1,    -1,    -1,    -1,   408,   409,   410,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     421,    -1,    -1,   424,   425,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   443
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   452,   453,     0,   176,   301,   454,   455,   456,   462,
     469,   471,   443,   443,   455,   144,   477,   477,   227,   302,
     472,   472,   114,   457,   463,    26,   473,   473,   443,    96,
     572,   572,   227,   443,   470,    79,   478,   114,   458,   464,
     207,   474,  1115,   346,   163,   201,   209,   529,   443,   297,
     706,   706,   443,    69,   312,   396,   475,   476,   443,   443,
     346,   443,   162,   344,   395,   573,   579,   114,   459,   465,
     469,   129,   468,   476,   300,  1126,   479,   530,   443,   531,
     346,   432,   604,   575,    53,   423,   709,   133,   459,   466,
     477,   472,   265,   327,   367,   369,   480,   481,   485,   493,
     498,   533,   163,   532,   242,   340,   563,   564,   565,   566,
     568,   443,   346,   230,   649,   430,   578,   580,  1047,   711,
     710,   331,   717,   472,   460,   443,   443,   443,   443,   443,
     349,   534,   443,   209,   562,   395,  1111,   309,   364,   365,
     567,   443,   565,   574,   443,   346,   226,   651,   577,   579,
     606,   607,   608,   581,    48,   712,   713,   714,  1106,   712,
     430,   443,   443,   572,   236,   348,   430,   484,   486,   487,
     488,   489,   491,   492,  1126,   175,   494,   495,   496,   429,
     482,   483,   484,  1140,    11,    56,    91,    92,    94,   102,
     156,   228,   342,   382,   430,   499,   500,   501,   502,   506,
     515,   519,   522,   523,   524,   525,   526,   527,   528,   273,
    1093,   533,   443,   385,  1134,    23,  1102,   576,   605,   443,
     346,   322,   653,   580,   609,  1087,   582,   713,   362,   407,
     715,   315,   424,   707,   461,   362,  1115,   443,   487,   443,
     488,    60,   353,  1099,     9,   227,   497,   443,   496,   443,
     443,   483,   101,   430,  1058,  1058,   374,   357,  1130,  1115,
    1115,  1115,  1058,  1115,    55,  1108,  1115,   443,   501,  1058,
     563,    81,  1109,   169,  1112,   577,   606,   650,   443,   346,
     341,   694,   606,   443,  1087,   430,   610,   612,   617,    46,
      59,    96,   212,   222,   309,   310,   322,   324,   424,   443,
     583,   584,   586,   590,   592,   594,   595,   601,   602,   603,
    1115,  1115,   362,   273,   716,   103,   718,   706,  1115,   227,
    1076,   443,   353,  1115,   204,   204,   227,   443,   240,   507,
    1115,  1115,  1115,   430,  1055,  1073,    65,  1055,  1115,  1055,
     516,   517,  1058,    91,  1058,   535,   569,   570,  1047,  1046,
    1047,   606,   652,   443,   346,   610,   443,   165,   430,   613,
     614,  1109,  1115,   309,   311,  1097,  1097,  1115,  1109,  1115,
     240,  1120,  1115,    22,  1101,   267,   161,   181,    30,   104,
    1076,  1115,   430,   443,   708,   465,  1076,  1055,  1115,   188,
     227,   234,   305,   368,   397,   436,   520,   521,  1079,  1055,
     227,   193,   267,  1096,  1055,    22,   207,  1058,  1116,   503,
     536,   570,   291,   571,  1047,   606,   654,   443,   443,   611,
      80,  1076,   430,  1115,  1101,  1054,  1055,   269,   370,   591,
     227,  1055,  1057,  1076,   425,  1115,   430,   693,   693,   164,
     430,  1076,   719,   720,   133,   467,    55,   431,   490,   118,
     188,   227,   234,   246,   305,   368,   371,   372,   436,   508,
     509,   510,   513,   521,   390,  1073,   518,  1076,   504,     4,
      19,    28,   195,   224,   231,   276,   282,   309,   316,   329,
     356,   364,   395,   443,   537,   538,   542,   544,   545,   546,
     547,   548,   552,   553,   554,   555,   556,   558,   559,   560,
    1099,  1127,  1076,   307,   655,   656,   657,   695,   618,   615,
    1115,   393,   589,  1055,   225,  1119,   393,  1108,   193,  1114,
     430,  1115,  1115,   720,     1,   430,   443,   721,   722,   723,
     724,   725,   730,   731,   472,   510,    17,   390,  1079,  1076,
     268,   270,   505,  1120,   309,   393,  1138,   354,  1120,  1115,
      54,  1107,   107,   211,  1117,  1117,  1076,  1140,   374,  1115,
      36,  1105,   693,   657,   696,    21,    33,    36,    37,    38,
      39,    40,    41,    42,    70,    72,    73,    74,    75,    76,
      77,   112,   194,   210,   244,   266,   281,   288,   290,   303,
     313,   320,   357,   359,   360,   361,   383,   408,   409,   410,
     421,   424,   619,   620,   621,   623,   624,   625,   626,   627,
     628,   637,   638,   640,   641,   642,   647,   648,  1115,  1131,
      26,  1103,   181,  1076,    55,   311,   585,   596,  1076,   362,
    1132,   227,   593,  1073,   593,   120,   443,   443,   346,     3,
       5,    10,    18,    50,    51,    57,    68,    71,    83,   105,
     112,   113,   143,   155,   159,   172,   179,   182,   183,   190,
     197,   199,   202,   237,   241,   243,   250,   272,   287,   308,
     317,   330,   335,   337,   345,   355,   364,   373,   375,   376,
     379,   381,   386,   401,   406,   411,   422,   433,   443,   732,
     733,   743,   748,   752,   755,   768,   771,   776,   781,   782,
     783,   786,   794,   798,   800,   815,   818,   820,   822,   825,
     827,   833,   842,   844,   861,   863,   866,   870,   876,   886,
     893,   895,   898,   902,   903,   914,   925,   935,   941,   944,
     950,   954,   956,   958,   960,   963,   974,   975,   984,   986,
     987,   732,   443,   511,   513,   374,  1133,  1115,  1117,   117,
     161,   540,  1115,   309,   316,   553,  1115,  1115,  1115,  1115,
    1102,     9,   251,   308,   561,  1115,   430,   354,   658,   612,
     617,   697,   698,   699,   218,   358,   407,   358,   407,   358,
     407,   358,   407,   358,   407,   427,  1139,   336,  1128,  1076,
    1072,  1073,  1073,   207,   217,   336,   639,  1115,  1116,   161,
     181,   216,   400,     9,    49,   218,   616,  1077,  1078,  1079,
      29,   597,   598,   599,   600,  1104,  1140,  1108,   173,   588,
    1113,   103,   227,   726,   734,   744,   749,   753,   756,   769,
     772,   777,   784,   787,   795,   799,   801,   816,   819,   821,
    1138,   826,     1,   828,   834,   843,   845,   862,   864,   867,
     871,   877,   887,   894,   896,   899,   904,   915,   926,   936,
     227,   339,   945,   951,   296,   955,   957,   959,   961,   964,
     181,   976,  1112,   988,   188,   227,   234,   305,   368,   436,
     512,   514,  1115,   117,   306,   354,   543,  1115,   111,   295,
     539,    31,   158,   235,   549,  1057,   371,   557,  1055,  1055,
     277,  1125,  1125,   271,  1055,    58,    84,    85,   283,   443,
     659,   660,   664,  1115,   613,   699,   436,   393,   629,   445,
    1074,  1075,   390,   626,   644,   645,  1077,    26,   622,   352,
    1095,  1095,  1079,   267,  1122,  1122,   450,    47,   399,   168,
     589,  1076,   443,   443,   735,  1071,  1072,     6,    78,    89,
      93,   177,   218,   223,   229,   232,   264,   332,   377,   378,
     402,   420,   428,   745,  1041,  1061,  1062,  1071,  1077,  1080,
     430,   750,  1028,  1029,  1030,   227,  1051,  1052,  1053,  1073,
     227,  1069,  1071,  1080,   770,   773,   778,  1042,  1043,  1062,
    1047,   227,   788,  1061,  1068,  1071,   796,  1062,   227,   394,
     398,   802,   803,  1028,   286,   287,   300,   346,   817,     6,
    1059,  1060,  1071,  1071,   823,   130,  1027,  1028,  1059,   663,
    1071,   846,  1071,  1077,  1080,   927,  1073,    89,   865,  1062,
     868,  1062,   872,   171,   227,   878,   881,   882,   883,  1051,
    1069,  1073,  1140,  1047,  1044,  1073,  1047,  1044,     9,   905,
    1045,  1073,   144,   239,   916,   917,   918,   919,   921,   922,
     923,   924,  1048,  1049,  1059,   927,  1047,   942,   106,   946,
     947,  1062,    89,   952,  1061,   663,  1071,  1047,  1071,     8,
      34,   978,   101,  1044,    17,  1058,   557,   112,   227,   541,
    1073,   429,   550,   550,   366,   444,  1055,  1056,  1115,   166,
     661,   662,   661,  1116,   672,   181,   700,  1076,   392,  1137,
     218,   437,   438,   445,  1038,  1040,  1041,  1063,  1071,  1078,
    1080,   445,  1075,  1073,   643,   645,   390,   227,  1107,  1072,
    1072,  1079,  1057,  1057,  1104,  1108,   121,   742,    29,   173,
     736,  1104,  1122,   445,  1071,   445,  1081,   445,  1082,  1122,
    1096,   445,   445,   445,   445,   445,   445,   445,   445,  1081,
     122,   747,   393,   746,  1062,   198,  1090,    55,    12,    13,
      14,    20,   150,   151,   178,   184,   215,   219,   247,   248,
     252,   262,   269,   274,   292,   437,   438,   439,   440,   442,
     444,   445,   446,   447,   448,  1031,  1032,  1033,  1034,  1035,
    1062,   393,  1096,   423,   757,   227,  1068,  1071,  1047,   124,
     779,   150,   444,   780,  1043,   338,  1094,  1127,   126,   793,
     736,   416,   417,   418,   419,   127,   797,    48,   203,   757,
      17,   427,   804,   805,   806,   810,    95,  1122,  1060,  1050,
     389,  1136,   835,  1140,  1071,    88,   321,   384,   847,   848,
     849,   853,   858,   929,  1062,   393,   131,   869,    48,   160,
     200,   208,   278,   873,   882,   132,   879,   412,   425,   390,
     392,   387,   249,   294,  1091,   173,   989,  1127,   989,  1045,
     137,   913,   425,   907,  1066,  1071,  1078,   922,   924,  1059,
     393,  1049,   115,   393,   413,   920,   937,   180,   331,   943,
    1106,   203,   947,  1071,   140,   953,   173,   173,   309,   311,
     962,   106,   965,   323,   370,   979,   270,  1123,   989,   514,
     116,   429,  1089,  1098,   231,   337,  1115,  1054,  1068,   663,
     670,  1076,   612,   673,   701,   108,   630,  1122,  1040,  1040,
    1040,    67,   350,   446,  1039,   437,   438,   439,   440,   442,
     449,  1040,  1139,  1077,  1119,  1057,   108,   587,  1066,    24,
      25,    64,    66,    97,    98,    99,   144,   146,   154,   225,
     391,   430,  1049,   429,   739,    63,   224,   291,   737,   738,
     143,   300,  1064,  1072,  1038,  1040,   393,  1040,  1038,  1083,
    1072,  1078,  1080,   430,  1040,  1086,  1040,  1040,  1085,  1040,
    1038,  1038,  1040,  1084,  1040,  1042,  1062,   180,   331,   751,
    1090,  1138,   388,  1135,  1135,   207,  1032,   299,   754,  1053,
     758,   180,   331,   762,   314,   405,   774,   775,  1140,  1028,
     206,   256,  1020,  1021,  1022,  1024,   415,   789,   157,   995,
     996,   995,   995,   995,  1062,  1042,  1062,   803,    21,   394,
     398,   811,   812,  1029,   128,   814,   427,   806,   808,   427,
     807,  1072,   108,   824,  1051,   829,     9,    12,    15,    16,
     244,   245,   262,   263,   836,   840,   165,  1066,     9,    55,
     167,   216,   400,   854,   855,   856,   850,   848,   931,  1098,
    1123,   393,  1059,  1042,  1062,   356,   874,   727,   728,  1027,
     884,   885,  1071,  1051,     8,    34,   991,  1127,  1068,   203,
     888,   900,  1140,   908,  1104,  1071,   908,   393,   393,   505,
     143,   394,   398,  1062,    48,   211,   938,  1062,  1062,   362,
    1062,  1071,   173,  1042,  1062,  1066,  1106,   203,   968,  1071,
     153,   157,   980,     9,   985,  1051,   900,   116,   270,  1054,
     186,   665,   224,   225,   671,   430,   613,    30,    32,    35,
      43,    44,    45,    63,   152,   170,   173,   174,   187,   224,
     233,   266,   280,   304,   328,   333,   347,   393,   404,   423,
     443,   624,   625,   627,   637,   640,   642,   702,   705,  1123,
     631,   632,  1072,  1078,  1080,   446,  1040,  1040,  1040,  1040,
    1040,  1040,   446,  1040,   355,  1129,  1119,  1123,   994,   996,
     435,   434,  1066,   994,   211,    30,    32,    35,    45,   170,
     174,   187,   233,   280,   304,   328,   333,   343,   347,   404,
     414,   740,   741,   994,   260,  1121,  1121,  1121,   738,   737,
     227,  1065,  1072,   446,  1071,   449,   446,  1039,   446,   446,
    1039,   446,   446,   446,   446,  1039,   446,   446,   363,  1000,
    1001,  1042,  1060,   331,   393,  1051,   759,   760,   761,  1106,
    1071,  1071,   157,   279,   763,   981,  1112,   231,   251,  1000,
    1023,  1025,   125,   785,  1024,    91,   295,   430,  1049,   429,
     790,  1140,   997,   255,   998,   180,  1000,   180,    17,   390,
     813,   277,   811,   727,  1123,   727,  1138,   321,   837,  1138,
     393,    48,   855,   857,  1066,     9,    55,   216,   400,   851,
     852,  1066,   932,  1099,   193,   275,  1124,    27,   109,   633,
    1059,  1000,   180,  1140,  1046,   132,   880,   729,     8,   173,
     888,  1071,   120,   253,  1010,  1011,  1013,  1020,   231,   251,
     427,   120,   427,   910,   911,  1066,  1065,  1062,  1115,  1020,
     948,  1140,  1071,  1000,   180,   393,     9,   966,   967,  1088,
     969,  1071,   948,   969,   297,   983,   298,   990,   991,   242,
     309,   311,   551,  1115,   167,   666,  1076,   674,  1115,  1121,
     147,   149,  1115,  1069,  1121,  1076,  1071,  1071,  1055,   195,
     634,   633,   446,  1138,  1055,   998,   994,  1115,  1115,   115,
     413,   741,  1068,  1068,  1068,  1081,  1094,   446,  1040,  1055,
    1081,  1081,  1040,  1081,  1081,  1081,   216,   400,  1081,  1081,
    1002,   258,  1003,  1000,  1060,   760,   269,   715,    82,   315,
     424,   255,   257,   765,   982,   764,   319,   334,   727,   727,
      32,    35,    43,    44,    45,   152,   170,   187,   233,   280,
     333,   343,   404,   791,   792,   995,   259,   727,   999,  1042,
    1043,  1042,  1043,   812,  1028,   809,  1071,   119,   830,   424,
     838,   839,   840,   104,   841,   424,  1067,  1071,  1077,  1066,
      48,   859,   852,   169,   859,   928,  1115,   275,  1117,  1042,
     561,   875,  1140,   730,   885,  1062,   192,   889,  1140,  1012,
    1014,   135,   897,  1013,   136,   901,   231,  1028,   909,  1027,
     910,   252,   939,  1092,   138,   940,   279,  1005,  1006,   290,
    1094,  1042,  1067,   274,  1066,   107,   970,   384,   972,  1123,
     148,   254,   992,  1015,  1016,  1018,  1021,     7,  1100,   551,
    1076,   110,   213,   667,    64,    63,    64,   185,   224,   225,
     249,   293,   366,   380,   403,   425,   443,   624,   625,   627,
     628,   637,   640,   642,   675,   676,   678,   679,   680,   681,
     683,   684,   685,   686,   690,   691,   436,  1070,  1071,  1076,
    1115,  1070,  1115,  1137,  1106,  1117,   394,   646,  1070,  1070,
    1026,  1106,  1026,  1000,   446,   727,  1004,  1062,   123,   767,
     766,   727,  1115,   147,   149,  1115,   115,   413,   792,   727,
    1000,   318,  1000,   318,   727,   831,   130,   832,   839,    96,
    1110,   859,   859,  1067,   991,   200,   423,   933,  1055,   930,
    1000,   231,   251,    48,   231,   211,   890,   191,   231,   251,
     426,   727,   727,   906,   727,   912,  1062,   178,   184,   215,
     219,  1033,  1034,  1035,  1036,  1037,  1007,   139,   949,   257,
    1008,  1071,  1000,  1000,   967,  1114,    90,   971,  1114,  1005,
     160,   200,   208,   278,   977,  1046,  1017,  1019,   142,   993,
    1018,   283,  1049,  1070,  1115,    87,   214,   668,   261,  1121,
     196,   692,   260,   261,   689,  1101,   185,   427,  1115,  1122,
    1115,  1071,   681,   249,   289,   687,   688,  1076,   238,   289,
     437,   438,   704,   238,   289,   437,   438,   703,   430,   635,
     636,  1115,  1115,  1070,   727,   727,  1070,  1070,  1026,  1026,
    1043,  1043,   727,    48,   859,   396,   860,   297,  1046,   180,
     278,   934,  1073,   334,  1062,  1115,   891,  1010,  1021,   231,
     231,   727,   727,  1135,  1135,   727,  1009,  1071,  1114,  1071,
     141,   973,   727,   727,   224,   225,  1118,  1076,  1115,  1115,
     168,   669,  1115,  1116,  1115,  1027,  1071,   682,  1055,    86,
      87,   110,   284,   285,   325,   326,   677,   173,   283,  1076,
     688,  1070,  1070,   636,  1054,  1077,  1118,  1000,  1000,  1062,
    1062,  1115,  1046,   297,   412,  1071,   134,   892,   274,   274,
     727,  1071,  1076,  1076,  1115,  1076,  1076,  1094,  1062,   881,
    1115,  1027,   150,   150,  1076,    48,   881,  1138,  1138,  1062
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

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/* Line 1806 of yacc.c  */
#line 757 "parser.y"
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

/* Line 1806 of yacc.c  */
#line 781 "parser.y"
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
  }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 810 "parser.y"
    { cb_validate_program_environment (current_program); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 811 "parser.y"
    { cb_validate_program_data (current_program); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 819 "parser.y"
    { cb_validate_program_environment (current_program); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 820 "parser.y"
    { cb_validate_program_data (current_program); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 828 "parser.y"
    { cb_validate_program_environment (current_program); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 829 "parser.y"
    { cb_validate_program_data (current_program); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 841 "parser.y"
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
  }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 865 "parser.y"
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
  }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 889 "parser.y"
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
  }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 918 "parser.y"
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

/* Line 1806 of yacc.c  */
#line 959 "parser.y"
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

/* Line 1806 of yacc.c  */
#line 1007 "parser.y"
    { (yyval) = NULL; }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 1008 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 1017 "parser.y"
    {
	if (!current_program->nested_level) {
		cb_error (_("COMMON may only be used in a nested program"));
	}
	current_program->flag_common = 1;
  }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 1024 "parser.y"
    {
	if (!current_program->nested_level) {
		cb_error (_("COMMON may only be used in a nested program"));
	}
	current_program->flag_common = 1;
  }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 1035 "parser.y"
    {
	current_program->flag_initial = 1;
  }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 1039 "parser.y"
    {
	current_program->flag_recursive = 1;
	current_program->flag_initial = 1;
  }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 1064 "parser.y"
    {
	if (current_program->nested_level) {
		cb_error (_("CONFIGURATION SECTION not allowed in nested programs"));
	}
  }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 1099 "parser.y"
    {
	cb_verify (cb_debugging_line, "DEBUGGING MODE");
  }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 1105 "parser.y"
    { }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 1136 "parser.y"
    {
	cb_verify (cb_memory_size_clause, "MEMORY SIZE");
  }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 1148 "parser.y"
    {
	current_program->collating_sequence = (yyvsp[(4) - (4)]);
  }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 1155 "parser.y"
    {
	/* Ignore */
  }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 1180 "parser.y"
    {
	current_program->function_spec_list = (yyvsp[(2) - (3)]);
  }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 1184 "parser.y"
    {
	functions_are_all = 1;
  }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 1190 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 1192 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 1232 "parser.y"
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

  case 96:

/* Line 1806 of yacc.c  */
#line 1242 "parser.y"
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

/* Line 1806 of yacc.c  */
#line 1257 "parser.y"
    {
	cb_define_switch_name ((yyvsp[(5) - (5)]), save_tree_1, (yyvsp[(2) - (5)]), save_tree_2);
  }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 1263 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 1264 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 1272 "parser.y"
    {
	save_tree_1 = (yyvsp[(2) - (2)]);
  }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1276 "parser.y"
    {
	current_program->alphabet_name_list =
		cb_list_add (current_program->alphabet_name_list, (yyvsp[(5) - (5)]));
  }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 1283 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_NATIVE); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 1284 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_1); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1285 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_2); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1286 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_EBCDIC); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1288 "parser.y"
    {
	(yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_CUSTOM);
	CB_ALPHABET_NAME ((yyval))->custom_list = (yyvsp[(1) - (1)]);
  }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1295 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 1297 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 1301 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1302 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 1304 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (2)]));
	save_tree_2 = (yyval);
  }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 1309 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (4)]);
  }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 1320 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 1321 "parser.y"
    { (yyval) = cb_space; }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 1322 "parser.y"
    { (yyval) = cb_zero; }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 1323 "parser.y"
    { (yyval) = cb_quote; }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 1324 "parser.y"
    { (yyval) = cb_norm_high; }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 1325 "parser.y"
    { (yyval) = cb_norm_low; }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 1329 "parser.y"
    { cb_list_add (save_tree_2, (yyvsp[(1) - (1)])); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 1330 "parser.y"
    { cb_list_add (save_tree_2, cb_space); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 1331 "parser.y"
    { cb_list_add (save_tree_2, cb_zero); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 1332 "parser.y"
    { cb_list_add (save_tree_2, cb_quote); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 1333 "parser.y"
    { cb_list_add (save_tree_2, cb_norm_high); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 1334 "parser.y"
    { cb_list_add (save_tree_2, cb_norm_low); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 1342 "parser.y"
    {
	if ((yyvsp[(3) - (3)])) {
		current_program->symbolic_list =
			cb_list_add (current_program->symbolic_list, (yyvsp[(3) - (3)]));
	}
	PENDING ("SYMBOLIC CHARACTERS");
  }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 1353 "parser.y"
    {
	if (cb_list_length ((yyvsp[(1) - (3)])) != cb_list_length ((yyvsp[(3) - (3)]))) {
		cb_error (_("Invalid SYMBOLIC clause"));
		(yyval) = NULL;
	} else {
		(yyval) = NULL;
	}
  }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 1364 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 1365 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 1369 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 1370 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 1378 "parser.y"
    {
	current_program->class_name_list =
			cb_list_add (current_program->class_name_list,
			cb_build_class_name ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])));
  }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 1386 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 1387 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 1391 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 1393 "parser.y"
    {
	/* if (CB_LITERAL ($1)->data[0] < CB_LITERAL ($3)->data[0]) */
	if (literal_value ((yyvsp[(1) - (3)])) < literal_value ((yyvsp[(3) - (3)]))) {
		(yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	} else {
		(yyval) = cb_build_pair ((yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]));
	}
  }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 1407 "parser.y"
    {
	cb_tree	l;

	l = cb_build_locale_name ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
	if (l != cb_error_node) {
		current_program->locale_list =
			cb_list_add (current_program->locale_list, l);
	}
  }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 1422 "parser.y"
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

  case 142:

/* Line 1806 of yacc.c  */
#line 1489 "parser.y"
    {
	current_program->decimal_point = ',';
	current_program->numeric_separator = '.';
  }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 1499 "parser.y"
    { current_program->cursor_pos = (yyvsp[(3) - (3)]); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 1506 "parser.y"
    { current_program->crt_status = (yyvsp[(4) - (4)]); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 1513 "parser.y"
    {  PENDING ("SCREEN CONTROL"); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 1519 "parser.y"
    {  PENDING ("EVENT STATUS"); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 1531 "parser.y"
    {
	/* hack for MF compatibility */
	if (cb_relaxed_syntax_check) {
		cb_warning (_("INPUT-OUTPUT SECTION header missing - assumed"));
	} else {
		cb_error (_("INPUT-OUTPUT SECTION header missing"));
	}
  }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 1540 "parser.y"
    {
	/* hack for MF compatibility */
	if (cb_relaxed_syntax_check) {
		cb_warning (_("INPUT-OUTPUT SECTION header missing - assumed"));
	} else {
		cb_error (_("INPUT-OUTPUT SECTION header missing"));
	}
  }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 1565 "parser.y"
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

  case 158:

/* Line 1806 of yacc.c  */
#line 1580 "parser.y"
    {
	validate_file (current_file, (yyvsp[(3) - (6)]));
  }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 1610 "parser.y"
    {
	current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
  }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 1614 "parser.y"
    {
	current_file->fileid_assign = 1;
	current_file->assign = cb_build_assignment_name(current_file, cb_build_reference ("DISK"));
	
  }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 1620 "parser.y"
    {
	current_file->fileid_assign = 1;
	current_file->assign = cb_build_assignment_name(current_file, cb_build_reference ("PRINTER"));
	
  }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 1629 "parser.y"
    { current_file->organization = COB_ORG_LINE_SEQUENTIAL; }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 1634 "parser.y"
    {
	current_file->external_assign = 1;
  }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 1643 "parser.y"
    {
	const char	*s;

	s = "$#@DUMMY@#$";
	(yyval) = cb_build_alphanumeric_literal ((unsigned char *)s, strlen (s));
  }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 1660 "parser.y"
    { current_file->access_mode = COB_ACCESS_SEQUENTIAL; }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 1661 "parser.y"
    { current_file->access_mode = COB_ACCESS_DYNAMIC; }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 1662 "parser.y"
    { current_file->access_mode = COB_ACCESS_RANDOM; }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 1670 "parser.y"
    {
	struct cb_alt_key *p;
	struct cb_alt_key *l;

	p = cobc_malloc (sizeof (struct cb_alt_key));
	p->key = (yyvsp[(5) - (6)]);
	p->duplicates = CB_INTEGER ((yyvsp[(6) - (6)]))->val;
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

  case 191:

/* Line 1806 of yacc.c  */
#line 1695 "parser.y"
    {
	PENDING ("COLLATING SEQUENCE");
  }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 1705 "parser.y"
    {
	current_file->file_status = (yyvsp[(4) - (5)]);
	if ((yyvsp[(5) - (5)])) {
		PENDING ("2nd FILE STATUS");
	}
  }
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 1726 "parser.y"
    { current_file->lock_mode = COB_LOCK_MANUAL; }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 1727 "parser.y"
    { current_file->lock_mode = COB_LOCK_AUTOMATIC; }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 1728 "parser.y"
    { current_file->lock_mode = COB_LOCK_EXCLUSIVE; }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 1734 "parser.y"
    {
	current_file->lock_mode |= COB_LOCK_MULTIPLE;
  }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 1737 "parser.y"
    { PENDING ("WITH ROLLBACK"); }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 1754 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_INDEXED;
		organized_seen = 1;
	}
  }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 1763 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_SEQUENTIAL;
		organized_seen = 1;
	}
  }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 1772 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_RELATIVE;
		organized_seen = 1;
	}
  }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 1781 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_LINE_SEQUENTIAL;
		organized_seen = 1;
	}
  }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 1796 "parser.y"
    {
	cb_verify (cb_padding_character_clause, "PADDING CHARACTER");
  }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 1805 "parser.y"
    { /* ignored */ }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 1813 "parser.y"
    {
	current_file->key = (yyvsp[(4) - (4)]);
  }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 1819 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 1820 "parser.y"
    { PENDING ("SPLIT KEYS"); }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 1821 "parser.y"
    { PENDING ("SPLIT KEYS"); }
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 1827 "parser.y"
    { current_file->key = (yyvsp[(4) - (4)]); }
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 1834 "parser.y"
    { /* ignored */ }
    break;

  case 220:

/* Line 1806 of yacc.c  */
#line 1841 "parser.y"
    { current_file->sharing = (yyvsp[(3) - (3)]); }
    break;

  case 221:

/* Line 1806 of yacc.c  */
#line 1845 "parser.y"
    { (yyval) = NULL; PENDING ("SHARING ALL OTHER"); }
    break;

  case 222:

/* Line 1806 of yacc.c  */
#line 1846 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 223:

/* Line 1806 of yacc.c  */
#line 1847 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 1877 "parser.y"
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

  case 233:

/* Line 1806 of yacc.c  */
#line 1901 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 1902 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 1903 "parser.y"
    { (yyval) = cb_int2; }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 1904 "parser.y"
    { (yyval) = cb_int2; }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 1911 "parser.y"
    {
	cb_verify (cb_multiple_file_tape_clause, "MULTIPLE FILE TAPE");
  }
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 1922 "parser.y"
    { }
    break;

  case 246:

/* Line 1806 of yacc.c  */
#line 1950 "parser.y"
    { current_storage = CB_STORAGE_FILE; }
    break;

  case 248:

/* Line 1806 of yacc.c  */
#line 1953 "parser.y"
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

  case 252:

/* Line 1806 of yacc.c  */
#line 1972 "parser.y"
    {
	if ((yyvsp[(3) - (3)]) && (yyvsp[(3) - (3)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(3) - (3)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  }
    break;

  case 253:

/* Line 1806 of yacc.c  */
#line 1984 "parser.y"
    {
	if ((yyvsp[(2) - (2)]) && (yyvsp[(2) - (2)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(2) - (2)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  }
    break;

  case 255:

/* Line 1806 of yacc.c  */
#line 1995 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 256:

/* Line 1806 of yacc.c  */
#line 1996 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 257:

/* Line 1806 of yacc.c  */
#line 2006 "parser.y"
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

  case 258:

/* Line 1806 of yacc.c  */
#line 2017 "parser.y"
    {
	/* Shut up bison */
	dummy_tree = (yyvsp[(2) - (4)]);
  }
    break;

  case 261:

/* Line 1806 of yacc.c  */
#line 2029 "parser.y"
    {
	if (current_file->global) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->external = 1;
  }
    break;

  case 262:

/* Line 1806 of yacc.c  */
#line 2036 "parser.y"
    {
	if (current_file->external) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->global = 1;
  }
    break;

  case 272:

/* Line 1806 of yacc.c  */
#line 2058 "parser.y"
    { /* ignored */ }
    break;

  case 276:

/* Line 1806 of yacc.c  */
#line 2068 "parser.y"
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

  case 277:

/* Line 1806 of yacc.c  */
#line 2080 "parser.y"
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

  case 278:

/* Line 1806 of yacc.c  */
#line 2106 "parser.y"
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

  case 280:

/* Line 1806 of yacc.c  */
#line 2130 "parser.y"
    {
	current_file->record_depending = (yyvsp[(3) - (3)]);
  }
    break;

  case 281:

/* Line 1806 of yacc.c  */
#line 2136 "parser.y"
    { (yyval) = NULL; }
    break;

  case 282:

/* Line 1806 of yacc.c  */
#line 2137 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 283:

/* Line 1806 of yacc.c  */
#line 2141 "parser.y"
    { (yyval) = NULL; }
    break;

  case 284:

/* Line 1806 of yacc.c  */
#line 2142 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 285:

/* Line 1806 of yacc.c  */
#line 2150 "parser.y"
    {
	cb_verify (cb_label_records_clause, "LABEL RECORDS");
  }
    break;

  case 288:

/* Line 1806 of yacc.c  */
#line 2165 "parser.y"
    {
	cb_verify (cb_value_of_clause, "VALUE OF");
  }
    break;

  case 289:

/* Line 1806 of yacc.c  */
#line 2169 "parser.y"
    {
	if (!current_file->assign) {
		current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
	}
  }
    break;

  case 292:

/* Line 1806 of yacc.c  */
#line 2185 "parser.y"
    {
	cb_verify (cb_data_records_clause, "DATA RECORDS");
  }
    break;

  case 293:

/* Line 1806 of yacc.c  */
#line 2196 "parser.y"
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

  case 299:

/* Line 1806 of yacc.c  */
#line 2224 "parser.y"
    {
	current_file->latfoot = (yyvsp[(4) - (5)]);
  }
    break;

  case 300:

/* Line 1806 of yacc.c  */
#line 2231 "parser.y"
    {
	current_file->lattop = (yyvsp[(3) - (4)]);
  }
    break;

  case 301:

/* Line 1806 of yacc.c  */
#line 2238 "parser.y"
    {
	current_file->latbot = (yyvsp[(3) - (3)]);
  }
    break;

  case 302:

/* Line 1806 of yacc.c  */
#line 2247 "parser.y"
    { /* ignore */ }
    break;

  case 303:

/* Line 1806 of yacc.c  */
#line 2255 "parser.y"
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

  case 304:

/* Line 1806 of yacc.c  */
#line 2273 "parser.y"
    {
	cb_warning (_("file descriptor REPORT IS"));
  }
    break;

  case 305:

/* Line 1806 of yacc.c  */
#line 2277 "parser.y"
    {
	cb_warning (_("file descriptor REPORTS ARE"));
  }
    break;

  case 307:

/* Line 1806 of yacc.c  */
#line 2288 "parser.y"
    { current_storage = CB_STORAGE_WORKING; }
    break;

  case 308:

/* Line 1806 of yacc.c  */
#line 2290 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->working_storage =
			cb_field_add (current_program->working_storage, CB_FIELD ((yyvsp[(5) - (5)])));
	}
  }
    break;

  case 309:

/* Line 1806 of yacc.c  */
#line 2299 "parser.y"
    { (yyval) = NULL; }
    break;

  case 310:

/* Line 1806 of yacc.c  */
#line 2300 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 311:

/* Line 1806 of yacc.c  */
#line 2304 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  }
    break;

  case 312:

/* Line 1806 of yacc.c  */
#line 2310 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	(yyval) = CB_TREE (description_field);
  }
    break;

  case 317:

/* Line 1806 of yacc.c  */
#line 2330 "parser.y"
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

  case 318:

/* Line 1806 of yacc.c  */
#line 2341 "parser.y"
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

  case 320:

/* Line 1806 of yacc.c  */
#line 2366 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  }
    break;

  case 321:

/* Line 1806 of yacc.c  */
#line 2372 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  }
    break;

  case 322:

/* Line 1806 of yacc.c  */
#line 2378 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  }
    break;

  case 323:

/* Line 1806 of yacc.c  */
#line 2387 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  }
    break;

  case 325:

/* Line 1806 of yacc.c  */
#line 2396 "parser.y"
    {
	current_field->flag_is_global = 1;
	cb_error (_("CONSTANT with GLOBAL clause is not yet supported"));
  }
    break;

  case 326:

/* Line 1806 of yacc.c  */
#line 2403 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 327:

/* Line 1806 of yacc.c  */
#line 2404 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); }
    break;

  case 328:

/* Line 1806 of yacc.c  */
#line 2405 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); }
    break;

  case 329:

/* Line 1806 of yacc.c  */
#line 2410 "parser.y"
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

  case 330:

/* Line 1806 of yacc.c  */
#line 2429 "parser.y"
    {
	/* required to check redefines */
	(yyval) = NULL;
  }
    break;

  case 331:

/* Line 1806 of yacc.c  */
#line 2435 "parser.y"
    {
	/* required to check redefines */
	(yyval) = cb_true;
  }
    break;

  case 346:

/* Line 1806 of yacc.c  */
#line 2463 "parser.y"
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

  case 347:

/* Line 1806 of yacc.c  */
#line 2485 "parser.y"
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

  case 348:

/* Line 1806 of yacc.c  */
#line 2506 "parser.y"
    { current_field->ename = NULL; }
    break;

  case 349:

/* Line 1806 of yacc.c  */
#line 2508 "parser.y"
    {
	struct cb_field *x;

	x = CB_FIELD(cb_build_field (cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(2) - (2)]))->data))));
	current_field->ename = x->name;
 }
    break;

  case 350:

/* Line 1806 of yacc.c  */
#line 2520 "parser.y"
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

  case 351:

/* Line 1806 of yacc.c  */
#line 2539 "parser.y"
    { current_field->pic = CB_PICTURE ((yyvsp[(1) - (1)])); }
    break;

  case 354:

/* Line 1806 of yacc.c  */
#line 2551 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; }
    break;

  case 355:

/* Line 1806 of yacc.c  */
#line 2552 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; }
    break;

  case 356:

/* Line 1806 of yacc.c  */
#line 2553 "parser.y"
    { current_field->usage = CB_USAGE_FLOAT; }
    break;

  case 357:

/* Line 1806 of yacc.c  */
#line 2554 "parser.y"
    { current_field->usage = CB_USAGE_DOUBLE; }
    break;

  case 358:

/* Line 1806 of yacc.c  */
#line 2555 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; }
    break;

  case 359:

/* Line 1806 of yacc.c  */
#line 2556 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; }
    break;

  case 360:

/* Line 1806 of yacc.c  */
#line 2557 "parser.y"
    { current_field->usage = CB_USAGE_COMP_5; }
    break;

  case 361:

/* Line 1806 of yacc.c  */
#line 2558 "parser.y"
    { current_field->usage = CB_USAGE_COMP_X; }
    break;

  case 362:

/* Line 1806 of yacc.c  */
#line 2559 "parser.y"
    { current_field->usage = CB_USAGE_DISPLAY; }
    break;

  case 363:

/* Line 1806 of yacc.c  */
#line 2560 "parser.y"
    { current_field->usage = CB_USAGE_INDEX; }
    break;

  case 364:

/* Line 1806 of yacc.c  */
#line 2561 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; }
    break;

  case 365:

/* Line 1806 of yacc.c  */
#line 2563 "parser.y"
    {
	current_field->usage = CB_USAGE_POINTER;
	current_field->flag_is_pointer = 1;
  }
    break;

  case 366:

/* Line 1806 of yacc.c  */
#line 2568 "parser.y"
    {
	current_field->usage = CB_USAGE_PROGRAM_POINTER;
	current_field->flag_is_pointer = 1;
  }
    break;

  case 367:

/* Line 1806 of yacc.c  */
#line 2572 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; }
    break;

  case 368:

/* Line 1806 of yacc.c  */
#line 2573 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; }
    break;

  case 369:

/* Line 1806 of yacc.c  */
#line 2574 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; }
    break;

  case 370:

/* Line 1806 of yacc.c  */
#line 2575 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; }
    break;

  case 371:

/* Line 1806 of yacc.c  */
#line 2576 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; }
    break;

  case 372:

/* Line 1806 of yacc.c  */
#line 2577 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; }
    break;

  case 373:

/* Line 1806 of yacc.c  */
#line 2578 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; }
    break;

  case 374:

/* Line 1806 of yacc.c  */
#line 2579 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_CHAR; }
    break;

  case 375:

/* Line 1806 of yacc.c  */
#line 2580 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; }
    break;

  case 376:

/* Line 1806 of yacc.c  */
#line 2581 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; }
    break;

  case 377:

/* Line 1806 of yacc.c  */
#line 2582 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; }
    break;

  case 378:

/* Line 1806 of yacc.c  */
#line 2583 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; }
    break;

  case 379:

/* Line 1806 of yacc.c  */
#line 2584 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; }
    break;

  case 380:

/* Line 1806 of yacc.c  */
#line 2585 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; }
    break;

  case 381:

/* Line 1806 of yacc.c  */
#line 2586 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; }
    break;

  case 382:

/* Line 1806 of yacc.c  */
#line 2587 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; }
    break;

  case 383:

/* Line 1806 of yacc.c  */
#line 2588 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; }
    break;

  case 384:

/* Line 1806 of yacc.c  */
#line 2589 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; }
    break;

  case 385:

/* Line 1806 of yacc.c  */
#line 2591 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  }
    break;

  case 386:

/* Line 1806 of yacc.c  */
#line 2599 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_UNSIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_UNSIGNED_LONG;
	}
  }
    break;

  case 387:

/* Line 1806 of yacc.c  */
#line 2607 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  }
    break;

  case 388:

/* Line 1806 of yacc.c  */
#line 2614 "parser.y"
    { PENDING ("USAGE NATIONAL");}
    break;

  case 389:

/* Line 1806 of yacc.c  */
#line 2622 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 1;
  }
    break;

  case 390:

/* Line 1806 of yacc.c  */
#line 2627 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 0;
  }
    break;

  case 391:

/* Line 1806 of yacc.c  */
#line 2639 "parser.y"
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
  }
    break;

  case 392:

/* Line 1806 of yacc.c  */
#line 2654 "parser.y"
    { (yyval) = NULL; }
    break;

  case 393:

/* Line 1806 of yacc.c  */
#line 2655 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 395:

/* Line 1806 of yacc.c  */
#line 2660 "parser.y"
    {
	current_field->occurs_depending = (yyvsp[(3) - (3)]);
  }
    break;

  case 396:

/* Line 1806 of yacc.c  */
#line 2667 "parser.y"
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

  case 397:

/* Line 1806 of yacc.c  */
#line 2690 "parser.y"
    { (yyval) = NULL; }
    break;

  case 398:

/* Line 1806 of yacc.c  */
#line 2693 "parser.y"
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
  }
    break;

  case 399:

/* Line 1806 of yacc.c  */
#line 2708 "parser.y"
    { (yyval) = cb_int (COB_ASCENDING); }
    break;

  case 400:

/* Line 1806 of yacc.c  */
#line 2709 "parser.y"
    { (yyval) = cb_int (COB_DESCENDING); }
    break;

  case 402:

/* Line 1806 of yacc.c  */
#line 2714 "parser.y"
    {
	current_field->index_list = (yyvsp[(3) - (3)]);
  }
    break;

  case 403:

/* Line 1806 of yacc.c  */
#line 2720 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 404:

/* Line 1806 of yacc.c  */
#line 2722 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 405:

/* Line 1806 of yacc.c  */
#line 2727 "parser.y"
    {
	(yyval) = cb_build_index ((yyvsp[(1) - (1)]), cb_int1, 1, current_field);
  }
    break;

  case 406:

/* Line 1806 of yacc.c  */
#line 2736 "parser.y"
    { current_field->flag_justified = 1; }
    break;

  case 407:

/* Line 1806 of yacc.c  */
#line 2743 "parser.y"
    { current_field->flag_synchronized = 1; }
    break;

  case 411:

/* Line 1806 of yacc.c  */
#line 2755 "parser.y"
    { current_field->flag_blank_zero = 1; }
    break;

  case 412:

/* Line 1806 of yacc.c  */
#line 2763 "parser.y"
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

  case 413:

/* Line 1806 of yacc.c  */
#line 2787 "parser.y"
    { current_field->values = (yyvsp[(3) - (3)]); }
    break;

  case 415:

/* Line 1806 of yacc.c  */
#line 2792 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 416:

/* Line 1806 of yacc.c  */
#line 2793 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 417:

/* Line 1806 of yacc.c  */
#line 2797 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 418:

/* Line 1806 of yacc.c  */
#line 2798 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 420:

/* Line 1806 of yacc.c  */
#line 2803 "parser.y"
    {
	if (current_field->level != 88) {
		cb_error (_("FALSE clause only allowed for 88 level"));
	}
	current_field->false_88 = cb_list_init ((yyvsp[(3) - (3)]));
  }
    break;

  case 421:

/* Line 1806 of yacc.c  */
#line 2816 "parser.y"
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

  case 422:

/* Line 1806 of yacc.c  */
#line 2828 "parser.y"
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

  case 423:

/* Line 1806 of yacc.c  */
#line 2848 "parser.y"
    {
	if (current_field->flag_item_based) {
		cb_error (_("BASED and ANY LENGTH are mutually exclusive"));
	} else {
		current_field->flag_any_length = 1;
	}
  }
    break;

  case 425:

/* Line 1806 of yacc.c  */
#line 2863 "parser.y"
    {
	current_storage = CB_STORAGE_LOCAL;
	if (current_program->nested_level) {
		cb_error (_("LOCAL-STORAGE not allowed in nested programs"));
	}
  }
    break;

  case 426:

/* Line 1806 of yacc.c  */
#line 2870 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->local_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  }
    break;

  case 428:

/* Line 1806 of yacc.c  */
#line 2883 "parser.y"
    { current_storage = CB_STORAGE_LINKAGE; }
    break;

  case 429:

/* Line 1806 of yacc.c  */
#line 2885 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->linkage_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  }
    break;

  case 431:

/* Line 1806 of yacc.c  */
#line 2898 "parser.y"
    {
	cb_error (_("REPORT SECTION not supported"));
	current_storage = CB_STORAGE_REPORT;
  }
    break;

  case 438:

/* Line 1806 of yacc.c  */
#line 2931 "parser.y"
    {
	cb_warning (_("Report description using defaults"));
  }
    break;

  case 440:

/* Line 1806 of yacc.c  */
#line 2939 "parser.y"
    {
	cb_error (_("GLOBAL is not allowed with RD"));
  }
    break;

  case 472:

/* Line 1806 of yacc.c  */
#line 3019 "parser.y"
    { cb_warning (_("looking for Report line TYPE")); }
    break;

  case 523:

/* Line 1806 of yacc.c  */
#line 3124 "parser.y"
    { current_storage = CB_STORAGE_SCREEN; }
    break;

  case 524:

/* Line 1806 of yacc.c  */
#line 3125 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  }
    break;

  case 525:

/* Line 1806 of yacc.c  */
#line 3131 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	current_program->screen_storage = description_field;
	current_program->flag_screen = 1;
  }
    break;

  case 531:

/* Line 1806 of yacc.c  */
#line 3155 "parser.y"
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

  case 532:

/* Line 1806 of yacc.c  */
#line 3171 "parser.y"
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

  case 535:

/* Line 1806 of yacc.c  */
#line 3195 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_LINE; }
    break;

  case 536:

/* Line 1806 of yacc.c  */
#line 3196 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_SCREEN; }
    break;

  case 537:

/* Line 1806 of yacc.c  */
#line 3197 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BELL; }
    break;

  case 538:

/* Line 1806 of yacc.c  */
#line 3198 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLINK; }
    break;

  case 539:

/* Line 1806 of yacc.c  */
#line 3199 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOL; }
    break;

  case 540:

/* Line 1806 of yacc.c  */
#line 3200 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOS; }
    break;

  case 541:

/* Line 1806 of yacc.c  */
#line 3201 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_HIGHLIGHT; }
    break;

  case 542:

/* Line 1806 of yacc.c  */
#line 3202 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_LOWLIGHT; }
    break;

  case 543:

/* Line 1806 of yacc.c  */
#line 3203 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REVERSE; }
    break;

  case 544:

/* Line 1806 of yacc.c  */
#line 3204 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_UNDERLINE; }
    break;

  case 545:

/* Line 1806 of yacc.c  */
#line 3205 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_OVERLINE; }
    break;

  case 546:

/* Line 1806 of yacc.c  */
#line 3206 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_AUTO; }
    break;

  case 547:

/* Line 1806 of yacc.c  */
#line 3207 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_SECURE; }
    break;

  case 548:

/* Line 1806 of yacc.c  */
#line 3208 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REQUIRED; }
    break;

  case 549:

/* Line 1806 of yacc.c  */
#line 3209 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_FULL; }
    break;

  case 550:

/* Line 1806 of yacc.c  */
#line 3210 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_PROMPT; }
    break;

  case 551:

/* Line 1806 of yacc.c  */
#line 3212 "parser.y"
    {
	current_field->screen_line = (yyvsp[(5) - (5)]);
  }
    break;

  case 552:

/* Line 1806 of yacc.c  */
#line 3216 "parser.y"
    {
	current_field->screen_column = (yyvsp[(5) - (5)]);
  }
    break;

  case 553:

/* Line 1806 of yacc.c  */
#line 3220 "parser.y"
    {
	current_field->screen_foreg = (yyvsp[(3) - (3)]);
  }
    break;

  case 554:

/* Line 1806 of yacc.c  */
#line 3224 "parser.y"
    {
	current_field->screen_backg = (yyvsp[(3) - (3)]);
  }
    break;

  case 562:

/* Line 1806 of yacc.c  */
#line 3235 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  }
    break;

  case 563:

/* Line 1806 of yacc.c  */
#line 3242 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
  }
    break;

  case 564:

/* Line 1806 of yacc.c  */
#line 3246 "parser.y"
    {
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  }
    break;

  case 565:

/* Line 1806 of yacc.c  */
#line 3255 "parser.y"
    {
	/* Nothing */
  }
    break;

  case 566:

/* Line 1806 of yacc.c  */
#line 3259 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  }
    break;

  case 567:

/* Line 1806 of yacc.c  */
#line 3263 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  }
    break;

  case 568:

/* Line 1806 of yacc.c  */
#line 3267 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  }
    break;

  case 569:

/* Line 1806 of yacc.c  */
#line 3271 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  }
    break;

  case 570:

/* Line 1806 of yacc.c  */
#line 3278 "parser.y"
    {
	/* Nothing */
  }
    break;

  case 571:

/* Line 1806 of yacc.c  */
#line 3282 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  }
    break;

  case 572:

/* Line 1806 of yacc.c  */
#line 3286 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  }
    break;

  case 573:

/* Line 1806 of yacc.c  */
#line 3290 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  }
    break;

  case 574:

/* Line 1806 of yacc.c  */
#line 3294 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  }
    break;

  case 575:

/* Line 1806 of yacc.c  */
#line 3302 "parser.y"
    {
	current_field->occurs_max = cb_get_int ((yyvsp[(2) - (3)]));
	current_field->occurs_min = current_field->occurs_max;
	current_field->indexes++;
	current_field->flag_occurs = 1;
  }
    break;

  case 577:

/* Line 1806 of yacc.c  */
#line 3316 "parser.y"
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

  case 578:

/* Line 1806 of yacc.c  */
#line 3326 "parser.y"
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

  case 579:

/* Line 1806 of yacc.c  */
#line 3336 "parser.y"
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

  case 580:

/* Line 1806 of yacc.c  */
#line 3353 "parser.y"
    { (yyval) = NULL; }
    break;

  case 581:

/* Line 1806 of yacc.c  */
#line 3355 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  }
    break;

  case 582:

/* Line 1806 of yacc.c  */
#line 3359 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 583:

/* Line 1806 of yacc.c  */
#line 3361 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	current_program->flag_chained = 1;
  }
    break;

  case 584:

/* Line 1806 of yacc.c  */
#line 3365 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 585:

/* Line 1806 of yacc.c  */
#line 3369 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 586:

/* Line 1806 of yacc.c  */
#line 3371 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 587:

/* Line 1806 of yacc.c  */
#line 3376 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), cb_build_identifier ((yyvsp[(4) - (4)])));
	CB_SIZES ((yyval)) = size_mode;
  }
    break;

  case 589:

/* Line 1806 of yacc.c  */
#line 3385 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  }
    break;

  case 590:

/* Line 1806 of yacc.c  */
#line 3389 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  }
    break;

  case 592:

/* Line 1806 of yacc.c  */
#line 3401 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_AUTO;
	}
  }
    break;

  case 593:

/* Line 1806 of yacc.c  */
#line 3409 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_4;
	}
  }
    break;

  case 594:

/* Line 1806 of yacc.c  */
#line 3417 "parser.y"
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

  case 595:

/* Line 1806 of yacc.c  */
#line 3446 "parser.y"
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

  case 597:

/* Line 1806 of yacc.c  */
#line 3479 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OPTIONAL only allowed for BY REFERENCE items"));
	}
  }
    break;

  case 598:

/* Line 1806 of yacc.c  */
#line 3488 "parser.y"
    {
	if (current_program->prog_type == CB_FUNCTION_TYPE) {
		cb_error (_("RETURNING clause is required for a FUNCTION"));
	}
  }
    break;

  case 599:

/* Line 1806 of yacc.c  */
#line 3494 "parser.y"
    {
	if (cb_ref ((yyvsp[(2) - (2)])) != cb_error_node) {
		current_program->returning = (yyvsp[(2) - (2)]);
		if (cb_field ((yyvsp[(2) - (2)]))->storage != CB_STORAGE_LINKAGE) {
			cb_error (_("RETURNING item is not defined in LINKAGE SECTION"));
		}
	}
  }
    break;

  case 601:

/* Line 1806 of yacc.c  */
#line 3505 "parser.y"
    { in_declaratives = 1; }
    break;

  case 602:

/* Line 1806 of yacc.c  */
#line 3508 "parser.y"
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

  case 608:

/* Line 1806 of yacc.c  */
#line 3541 "parser.y"
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
  }
    break;

  case 609:

/* Line 1806 of yacc.c  */
#line 3557 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 610:

/* Line 1806 of yacc.c  */
#line 3561 "parser.y"
    {
	/* check_unreached = 0; */
  }
    break;

  case 611:

/* Line 1806 of yacc.c  */
#line 3573 "parser.y"
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

  case 612:

/* Line 1806 of yacc.c  */
#line 3604 "parser.y"
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

  case 613:

/* Line 1806 of yacc.c  */
#line 3641 "parser.y"
    {
	non_const_word = 0;
	check_unreached = 0;
	if ((yyvsp[(1) - (1)]) != cb_error_node) {
		cb_error_x ((yyvsp[(1) - (1)]), _("Unknown statement '%s'"), CB_NAME ((yyvsp[(1) - (1)])));
	}
	YYERROR;
  }
    break;

  case 614:

/* Line 1806 of yacc.c  */
#line 3652 "parser.y"
    { (yyval) = cb_build_section_name ((yyvsp[(1) - (1)]), 0); }
    break;

  case 616:

/* Line 1806 of yacc.c  */
#line 3656 "parser.y"
    { /* ignore */ }
    break;

  case 617:

/* Line 1806 of yacc.c  */
#line 3665 "parser.y"
    {
	(yyval) = current_program->exec_list;
	current_program->exec_list = NULL;
  }
    break;

  case 618:

/* Line 1806 of yacc.c  */
#line 3669 "parser.y"
    {
	(yyval) = CB_TREE (current_statement);
	current_statement = NULL;
  }
    break;

  case 619:

/* Line 1806 of yacc.c  */
#line 3674 "parser.y"
    {
	(yyval) = cb_list_reverse (current_program->exec_list);
	current_program->exec_list = (yyvsp[(1) - (3)]);
	current_statement = CB_STATEMENT ((yyvsp[(2) - (3)]));
  }
    break;

  case 620:

/* Line 1806 of yacc.c  */
#line 3682 "parser.y"
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

  case 671:

/* Line 1806 of yacc.c  */
#line 3753 "parser.y"
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

  case 672:

/* Line 1806 of yacc.c  */
#line 3775 "parser.y"
    {
	BEGIN_STATEMENT ("ACCEPT", TERM_ACCEPT);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  }
    break;

  case 674:

/* Line 1806 of yacc.c  */
#line 3788 "parser.y"
    {
	cb_emit_accept ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  }
    break;

  case 675:

/* Line 1806 of yacc.c  */
#line 3792 "parser.y"
    {
	PENDING ("ACCEPT .. FROM ESCAPE KEY");
  }
    break;

  case 676:

/* Line 1806 of yacc.c  */
#line 3796 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 0);
  }
    break;

  case 677:

/* Line 1806 of yacc.c  */
#line 3800 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 1);
  }
    break;

  case 678:

/* Line 1806 of yacc.c  */
#line 3804 "parser.y"
    {
	cb_emit_accept_date ((yyvsp[(1) - (3)]));
  }
    break;

  case 679:

/* Line 1806 of yacc.c  */
#line 3808 "parser.y"
    {
	cb_emit_accept_date_yyyymmdd ((yyvsp[(1) - (4)]));
  }
    break;

  case 680:

/* Line 1806 of yacc.c  */
#line 3812 "parser.y"
    {
	cb_emit_accept_day ((yyvsp[(1) - (3)]));
  }
    break;

  case 681:

/* Line 1806 of yacc.c  */
#line 3816 "parser.y"
    {
	cb_emit_accept_day_yyyyddd ((yyvsp[(1) - (4)]));
  }
    break;

  case 682:

/* Line 1806 of yacc.c  */
#line 3820 "parser.y"
    {
	cb_emit_accept_day_of_week ((yyvsp[(1) - (3)]));
  }
    break;

  case 683:

/* Line 1806 of yacc.c  */
#line 3824 "parser.y"
    {
	cb_emit_accept_time ((yyvsp[(1) - (3)]));
  }
    break;

  case 684:

/* Line 1806 of yacc.c  */
#line 3828 "parser.y"
    {
	cb_emit_accept_command_line ((yyvsp[(1) - (3)]));
  }
    break;

  case 685:

/* Line 1806 of yacc.c  */
#line 3832 "parser.y"
    {
	cb_emit_accept_environment ((yyvsp[(1) - (4)]));
  }
    break;

  case 686:

/* Line 1806 of yacc.c  */
#line 3836 "parser.y"
    { 
	cb_emit_get_environment ((yyvsp[(4) - (5)]), (yyvsp[(1) - (5)]));
  }
    break;

  case 687:

/* Line 1806 of yacc.c  */
#line 3840 "parser.y"
    {
	cb_emit_accept_arg_number ((yyvsp[(1) - (3)]));
  }
    break;

  case 688:

/* Line 1806 of yacc.c  */
#line 3844 "parser.y"
    {
	cb_emit_accept_arg_value ((yyvsp[(1) - (4)]));
  }
    break;

  case 689:

/* Line 1806 of yacc.c  */
#line 3848 "parser.y"
    {
	cb_emit_accept_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 690:

/* Line 1806 of yacc.c  */
#line 3852 "parser.y"
    {
	cb_emit_accept_name ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 691:

/* Line 1806 of yacc.c  */
#line 3858 "parser.y"
    { (yyval) = NULL; }
    break;

  case 692:

/* Line 1806 of yacc.c  */
#line 3859 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 693:

/* Line 1806 of yacc.c  */
#line 3860 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 694:

/* Line 1806 of yacc.c  */
#line 3861 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), NULL); }
    break;

  case 695:

/* Line 1806 of yacc.c  */
#line 3862 "parser.y"
    { (yyval) = cb_build_pair (NULL, (yyvsp[(2) - (2)])); }
    break;

  case 696:

/* Line 1806 of yacc.c  */
#line 3863 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 697:

/* Line 1806 of yacc.c  */
#line 3867 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 698:

/* Line 1806 of yacc.c  */
#line 3871 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 699:

/* Line 1806 of yacc.c  */
#line 3872 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 704:

/* Line 1806 of yacc.c  */
#line 3885 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; }
    break;

  case 705:

/* Line 1806 of yacc.c  */
#line 3886 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; }
    break;

  case 706:

/* Line 1806 of yacc.c  */
#line 3887 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; }
    break;

  case 707:

/* Line 1806 of yacc.c  */
#line 3888 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; }
    break;

  case 708:

/* Line 1806 of yacc.c  */
#line 3889 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; }
    break;

  case 709:

/* Line 1806 of yacc.c  */
#line 3890 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; }
    break;

  case 710:

/* Line 1806 of yacc.c  */
#line 3891 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; }
    break;

  case 711:

/* Line 1806 of yacc.c  */
#line 3893 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  }
    break;

  case 712:

/* Line 1806 of yacc.c  */
#line 3897 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  }
    break;

  case 713:

/* Line 1806 of yacc.c  */
#line 3901 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  }
    break;

  case 714:

/* Line 1806 of yacc.c  */
#line 3905 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  }
    break;

  case 715:

/* Line 1806 of yacc.c  */
#line 3909 "parser.y"
    { dispattrs |= COB_SCREEN_AUTO; }
    break;

  case 716:

/* Line 1806 of yacc.c  */
#line 3910 "parser.y"
    { dispattrs |= COB_SCREEN_FULL; }
    break;

  case 717:

/* Line 1806 of yacc.c  */
#line 3911 "parser.y"
    { dispattrs |= COB_SCREEN_REQUIRED; }
    break;

  case 718:

/* Line 1806 of yacc.c  */
#line 3912 "parser.y"
    { dispattrs |= COB_SCREEN_SECURE; }
    break;

  case 719:

/* Line 1806 of yacc.c  */
#line 3913 "parser.y"
    { dispattrs |= COB_SCREEN_UPDATE; }
    break;

  case 720:

/* Line 1806 of yacc.c  */
#line 3914 "parser.y"
    { dispattrs |= COB_SCREEN_PROMPT; }
    break;

  case 721:

/* Line 1806 of yacc.c  */
#line 3918 "parser.y"
    { terminator_warning (TERM_ACCEPT); }
    break;

  case 722:

/* Line 1806 of yacc.c  */
#line 3919 "parser.y"
    { terminator_clear (TERM_ACCEPT); }
    break;

  case 723:

/* Line 1806 of yacc.c  */
#line 3928 "parser.y"
    { BEGIN_STATEMENT ("ADD", TERM_ADD); }
    break;

  case 725:

/* Line 1806 of yacc.c  */
#line 3935 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '+', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  }
    break;

  case 726:

/* Line 1806 of yacc.c  */
#line 3939 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(4) - (5)]), 0, cb_build_binary_list ((yyvsp[(1) - (5)]), '+'));
  }
    break;

  case 727:

/* Line 1806 of yacc.c  */
#line 3943 "parser.y"
    {
	cb_emit_corresponding (cb_build_add, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  }
    break;

  case 729:

/* Line 1806 of yacc.c  */
#line 3949 "parser.y"
    { cb_list_add ((yyvsp[(0) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 730:

/* Line 1806 of yacc.c  */
#line 3953 "parser.y"
    { terminator_warning (TERM_ADD); }
    break;

  case 731:

/* Line 1806 of yacc.c  */
#line 3954 "parser.y"
    { terminator_clear (TERM_ADD); }
    break;

  case 732:

/* Line 1806 of yacc.c  */
#line 3963 "parser.y"
    { BEGIN_STATEMENT ("ALLOCATE", 0); }
    break;

  case 734:

/* Line 1806 of yacc.c  */
#line 3969 "parser.y"
    {
	cb_emit_allocate ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), NULL, (yyvsp[(2) - (3)]));
  }
    break;

  case 735:

/* Line 1806 of yacc.c  */
#line 3973 "parser.y"
    {
	cb_emit_allocate (NULL, (yyvsp[(5) - (5)]), (yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]));
  }
    break;

  case 736:

/* Line 1806 of yacc.c  */
#line 3979 "parser.y"
    { (yyval) = NULL; }
    break;

  case 737:

/* Line 1806 of yacc.c  */
#line 3980 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 738:

/* Line 1806 of yacc.c  */
#line 3990 "parser.y"
    {
	cb_error (_("ALTER statement is obsolete and unsupported"));
  }
    break;

  case 743:

/* Line 1806 of yacc.c  */
#line 4008 "parser.y"
    { BEGIN_STATEMENT ("CALL", TERM_CALL); }
    break;

  case 744:

/* Line 1806 of yacc.c  */
#line 4012 "parser.y"
    {
	cb_emit_call ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  }
    break;

  case 745:

/* Line 1806 of yacc.c  */
#line 4018 "parser.y"
    { (yyval) = NULL; }
    break;

  case 746:

/* Line 1806 of yacc.c  */
#line 4020 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  }
    break;

  case 747:

/* Line 1806 of yacc.c  */
#line 4024 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 748:

/* Line 1806 of yacc.c  */
#line 4028 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 749:

/* Line 1806 of yacc.c  */
#line 4030 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 750:

/* Line 1806 of yacc.c  */
#line 4035 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OMITTED only allowed with BY REFERENCE"));
	}
	(yyval) = cb_build_pair (cb_int (call_mode), cb_null);
  }
    break;

  case 751:

/* Line 1806 of yacc.c  */
#line 4042 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), (yyvsp[(3) - (3)]));
	CB_SIZES ((yyval)) = size_mode;
  }
    break;

  case 753:

/* Line 1806 of yacc.c  */
#line 4051 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  }
    break;

  case 754:

/* Line 1806 of yacc.c  */
#line 4055 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY CONTENT not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_CONTENT;
	}
  }
    break;

  case 755:

/* Line 1806 of yacc.c  */
#line 4063 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  }
    break;

  case 756:

/* Line 1806 of yacc.c  */
#line 4073 "parser.y"
    { (yyval) = NULL; }
    break;

  case 757:

/* Line 1806 of yacc.c  */
#line 4074 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 758:

/* Line 1806 of yacc.c  */
#line 4075 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 759:

/* Line 1806 of yacc.c  */
#line 4080 "parser.y"
    {
	(yyval) = NULL;
  }
    break;

  case 760:

/* Line 1806 of yacc.c  */
#line 4084 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 761:

/* Line 1806 of yacc.c  */
#line 4088 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 762:

/* Line 1806 of yacc.c  */
#line 4095 "parser.y"
    {
	(yyval) = NULL;
  }
    break;

  case 763:

/* Line 1806 of yacc.c  */
#line 4099 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 764:

/* Line 1806 of yacc.c  */
#line 4103 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 765:

/* Line 1806 of yacc.c  */
#line 4109 "parser.y"
    { terminator_warning (TERM_CALL); }
    break;

  case 766:

/* Line 1806 of yacc.c  */
#line 4110 "parser.y"
    { terminator_clear (TERM_CALL); }
    break;

  case 767:

/* Line 1806 of yacc.c  */
#line 4119 "parser.y"
    { BEGIN_STATEMENT ("CANCEL", 0); }
    break;

  case 770:

/* Line 1806 of yacc.c  */
#line 4125 "parser.y"
    {
	cb_emit_cancel ((yyvsp[(2) - (2)]));
  }
    break;

  case 771:

/* Line 1806 of yacc.c  */
#line 4136 "parser.y"
    { BEGIN_STATEMENT ("CLOSE", 0); }
    break;

  case 774:

/* Line 1806 of yacc.c  */
#line 4143 "parser.y"
    {
	BEGIN_IMPLICIT_STATEMENT ();
	if ((yyvsp[(2) - (3)]) != cb_error_node) {
		cb_emit_close ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
	}
  }
    break;

  case 775:

/* Line 1806 of yacc.c  */
#line 4152 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NORMAL); }
    break;

  case 776:

/* Line 1806 of yacc.c  */
#line 4153 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT); }
    break;

  case 777:

/* Line 1806 of yacc.c  */
#line 4154 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT_REMOVAL); }
    break;

  case 778:

/* Line 1806 of yacc.c  */
#line 4155 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NO_REWIND); }
    break;

  case 779:

/* Line 1806 of yacc.c  */
#line 4156 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_LOCK); }
    break;

  case 782:

/* Line 1806 of yacc.c  */
#line 4167 "parser.y"
    { BEGIN_STATEMENT ("COMPUTE", TERM_COMPUTE); }
    break;

  case 784:

/* Line 1806 of yacc.c  */
#line 4174 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(1) - (4)]), 0, (yyvsp[(3) - (4)]));
  }
    break;

  case 785:

/* Line 1806 of yacc.c  */
#line 4180 "parser.y"
    { terminator_warning (TERM_COMPUTE); }
    break;

  case 786:

/* Line 1806 of yacc.c  */
#line 4181 "parser.y"
    { terminator_clear (TERM_COMPUTE); }
    break;

  case 789:

/* Line 1806 of yacc.c  */
#line 4192 "parser.y"
    {
	BEGIN_STATEMENT ("COMMIT", 0);
	cb_emit_commit ();
  }
    break;

  case 790:

/* Line 1806 of yacc.c  */
#line 4205 "parser.y"
    {
	BEGIN_STATEMENT ("CONTINUE", 0);
	cb_emit_continue ();
  }
    break;

  case 791:

/* Line 1806 of yacc.c  */
#line 4217 "parser.y"
    { BEGIN_STATEMENT ("DELETE", TERM_DELETE); }
    break;

  case 792:

/* Line 1806 of yacc.c  */
#line 4220 "parser.y"
    {
	if ((yyvsp[(3) - (6)]) != cb_error_node) {
		cb_emit_delete ((yyvsp[(3) - (6)]));
	}
  }
    break;

  case 793:

/* Line 1806 of yacc.c  */
#line 4228 "parser.y"
    { terminator_warning (TERM_DELETE); }
    break;

  case 794:

/* Line 1806 of yacc.c  */
#line 4229 "parser.y"
    { terminator_clear (TERM_DELETE); }
    break;

  case 795:

/* Line 1806 of yacc.c  */
#line 4239 "parser.y"
    {
	BEGIN_STATEMENT ("DISPLAY", TERM_DISPLAY);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  }
    break;

  case 797:

/* Line 1806 of yacc.c  */
#line 4252 "parser.y"
    {
	cb_emit_env_name ((yyvsp[(1) - (3)]));
  }
    break;

  case 798:

/* Line 1806 of yacc.c  */
#line 4256 "parser.y"
    {
	cb_emit_env_value ((yyvsp[(1) - (3)]));
  }
    break;

  case 799:

/* Line 1806 of yacc.c  */
#line 4260 "parser.y"
    {
	cb_emit_arg_number ((yyvsp[(1) - (3)]));
  }
    break;

  case 800:

/* Line 1806 of yacc.c  */
#line 4264 "parser.y"
    {
	cb_emit_command_line ((yyvsp[(1) - (3)]));
  }
    break;

  case 801:

/* Line 1806 of yacc.c  */
#line 4268 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(2) - (5)]), fgc, bgc, scroll, dispattrs);
  }
    break;

  case 802:

/* Line 1806 of yacc.c  */
#line 4274 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 803:

/* Line 1806 of yacc.c  */
#line 4275 "parser.y"
    { (yyval) = cb_build_display_upon ((yyvsp[(2) - (2)])); }
    break;

  case 804:

/* Line 1806 of yacc.c  */
#line 4276 "parser.y"
    { (yyval) = cb_build_display_upon_direct ((yyvsp[(2) - (2)])); }
    break;

  case 805:

/* Line 1806 of yacc.c  */
#line 4277 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 806:

/* Line 1806 of yacc.c  */
#line 4278 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 807:

/* Line 1806 of yacc.c  */
#line 4282 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 808:

/* Line 1806 of yacc.c  */
#line 4283 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 809:

/* Line 1806 of yacc.c  */
#line 4284 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 812:

/* Line 1806 of yacc.c  */
#line 4294 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; }
    break;

  case 813:

/* Line 1806 of yacc.c  */
#line 4295 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; }
    break;

  case 814:

/* Line 1806 of yacc.c  */
#line 4296 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOL; }
    break;

  case 815:

/* Line 1806 of yacc.c  */
#line 4297 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOS; }
    break;

  case 816:

/* Line 1806 of yacc.c  */
#line 4298 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; }
    break;

  case 817:

/* Line 1806 of yacc.c  */
#line 4299 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; }
    break;

  case 818:

/* Line 1806 of yacc.c  */
#line 4300 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; }
    break;

  case 819:

/* Line 1806 of yacc.c  */
#line 4301 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; }
    break;

  case 820:

/* Line 1806 of yacc.c  */
#line 4302 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; }
    break;

  case 821:

/* Line 1806 of yacc.c  */
#line 4304 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  }
    break;

  case 822:

/* Line 1806 of yacc.c  */
#line 4308 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  }
    break;

  case 823:

/* Line 1806 of yacc.c  */
#line 4312 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  }
    break;

  case 824:

/* Line 1806 of yacc.c  */
#line 4316 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  }
    break;

  case 825:

/* Line 1806 of yacc.c  */
#line 4320 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_LINE; }
    break;

  case 826:

/* Line 1806 of yacc.c  */
#line 4321 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_SCREEN; }
    break;

  case 827:

/* Line 1806 of yacc.c  */
#line 4325 "parser.y"
    { terminator_warning (TERM_DISPLAY); }
    break;

  case 828:

/* Line 1806 of yacc.c  */
#line 4326 "parser.y"
    { terminator_clear (TERM_DISPLAY); }
    break;

  case 829:

/* Line 1806 of yacc.c  */
#line 4335 "parser.y"
    { BEGIN_STATEMENT ("DIVIDE", TERM_DIVIDE); }
    break;

  case 831:

/* Line 1806 of yacc.c  */
#line 4342 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '/', (yyvsp[(1) - (4)]));
  }
    break;

  case 832:

/* Line 1806 of yacc.c  */
#line 4346 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(3) - (6)]), '/', (yyvsp[(1) - (6)])));
  }
    break;

  case 833:

/* Line 1806 of yacc.c  */
#line 4350 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '/', (yyvsp[(3) - (6)])));
  }
    break;

  case 834:

/* Line 1806 of yacc.c  */
#line 4354 "parser.y"
    {
	cb_emit_divide ((yyvsp[(3) - (8)]), (yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  }
    break;

  case 835:

/* Line 1806 of yacc.c  */
#line 4358 "parser.y"
    {
	cb_emit_divide ((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  }
    break;

  case 836:

/* Line 1806 of yacc.c  */
#line 4364 "parser.y"
    { terminator_warning (TERM_DIVIDE); }
    break;

  case 837:

/* Line 1806 of yacc.c  */
#line 4365 "parser.y"
    { terminator_clear (TERM_DIVIDE); }
    break;

  case 838:

/* Line 1806 of yacc.c  */
#line 4374 "parser.y"
    { BEGIN_STATEMENT ("ENTRY", 0); }
    break;

  case 839:

/* Line 1806 of yacc.c  */
#line 4376 "parser.y"
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

  case 840:

/* Line 1806 of yacc.c  */
#line 4396 "parser.y"
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

  case 841:

/* Line 1806 of yacc.c  */
#line 4407 "parser.y"
    {
	cb_emit_evaluate ((yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]));
	eval_level--;
  }
    break;

  case 842:

/* Line 1806 of yacc.c  */
#line 4414 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 843:

/* Line 1806 of yacc.c  */
#line 4416 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 844:

/* Line 1806 of yacc.c  */
#line 4421 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE_P ((yyvsp[(1) - (1)]))) {
		eval_check[eval_level][eval_inc++] = 0;
	} else {
		eval_check[eval_level][eval_inc++] = 1;
	}
  }
    break;

  case 845:

/* Line 1806 of yacc.c  */
#line 4430 "parser.y"
    {
	(yyval) = cb_true;
	eval_check[eval_level][eval_inc++] = 2;
  }
    break;

  case 846:

/* Line 1806 of yacc.c  */
#line 4435 "parser.y"
    {
	(yyval) = cb_false;
	eval_check[eval_level][eval_inc++] = 3;
  }
    break;

  case 847:

/* Line 1806 of yacc.c  */
#line 4443 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (2)]);
	if ((yyvsp[(2) - (2)])) {
		(yyval) = cb_list_add ((yyval), (yyvsp[(2) - (2)]));
	}
  }
    break;

  case 848:

/* Line 1806 of yacc.c  */
#line 4452 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 849:

/* Line 1806 of yacc.c  */
#line 4454 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 850:

/* Line 1806 of yacc.c  */
#line 4459 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 851:

/* Line 1806 of yacc.c  */
#line 4463 "parser.y"
    {
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]));
	eval_inc2 = 0;
  }
    break;

  case 852:

/* Line 1806 of yacc.c  */
#line 4471 "parser.y"
    {
	(yyval) = NULL;
  }
    break;

  case 853:

/* Line 1806 of yacc.c  */
#line 4475 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 854:

/* Line 1806 of yacc.c  */
#line 4479 "parser.y"
    {
	(yyval) = cb_cons ((yyvsp[(4) - (4)]), NULL);
	eval_inc2 = 0;
  }
    break;

  case 855:

/* Line 1806 of yacc.c  */
#line 4486 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); }
    break;

  case 856:

/* Line 1806 of yacc.c  */
#line 4488 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 857:

/* Line 1806 of yacc.c  */
#line 4492 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 858:

/* Line 1806 of yacc.c  */
#line 4494 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 859:

/* Line 1806 of yacc.c  */
#line 4499 "parser.y"
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

  case 860:

/* Line 1806 of yacc.c  */
#line 4527 "parser.y"
    { (yyval) = cb_any; eval_inc2++; }
    break;

  case 861:

/* Line 1806 of yacc.c  */
#line 4528 "parser.y"
    { (yyval) = cb_true; eval_inc2++; }
    break;

  case 862:

/* Line 1806 of yacc.c  */
#line 4529 "parser.y"
    { (yyval) = cb_false; eval_inc2++; }
    break;

  case 863:

/* Line 1806 of yacc.c  */
#line 4532 "parser.y"
    { (yyval) = NULL; }
    break;

  case 864:

/* Line 1806 of yacc.c  */
#line 4533 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 865:

/* Line 1806 of yacc.c  */
#line 4537 "parser.y"
    { terminator_warning (TERM_EVALUATE); }
    break;

  case 866:

/* Line 1806 of yacc.c  */
#line 4538 "parser.y"
    { terminator_clear (TERM_EVALUATE); }
    break;

  case 867:

/* Line 1806 of yacc.c  */
#line 4547 "parser.y"
    { BEGIN_STATEMENT ("EXIT", 0); }
    break;

  case 869:

/* Line 1806 of yacc.c  */
#line 4552 "parser.y"
    { /* nothing */ }
    break;

  case 870:

/* Line 1806 of yacc.c  */
#line 4554 "parser.y"
    {
	if (in_declaratives && use_global_ind) {
		cb_error (_("EXIT PROGRAM is not allowed within a USE GLOBAL procedure"));
	}
	check_unreached = 1;
	cb_emit_exit (0);
  }
    break;

  case 871:

/* Line 1806 of yacc.c  */
#line 4562 "parser.y"
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
  }
    break;

  case 872:

/* Line 1806 of yacc.c  */
#line 4579 "parser.y"
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
  }
    break;

  case 873:

/* Line 1806 of yacc.c  */
#line 4596 "parser.y"
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
  }
    break;

  case 874:

/* Line 1806 of yacc.c  */
#line 4614 "parser.y"
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
  }
    break;

  case 875:

/* Line 1806 of yacc.c  */
#line 4638 "parser.y"
    { BEGIN_STATEMENT ("FREE", 0); }
    break;

  case 876:

/* Line 1806 of yacc.c  */
#line 4640 "parser.y"
    {
	cb_emit_free ((yyvsp[(3) - (3)]))
  ;}
    break;

  case 877:

/* Line 1806 of yacc.c  */
#line 4651 "parser.y"
    { BEGIN_STATEMENT ("GENERATE", 0); }
    break;

  case 878:

/* Line 1806 of yacc.c  */
#line 4653 "parser.y"
    {
	PENDING("GENERATE");
  }
    break;

  case 879:

/* Line 1806 of yacc.c  */
#line 4664 "parser.y"
    { BEGIN_STATEMENT ("GO TO", 0); }
    break;

  case 880:

/* Line 1806 of yacc.c  */
#line 4666 "parser.y"
    {
	cb_emit_goto ((yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
  }
    break;

  case 881:

/* Line 1806 of yacc.c  */
#line 4673 "parser.y"
    {
	check_unreached = 1;
	(yyval) = NULL;
  }
    break;

  case 882:

/* Line 1806 of yacc.c  */
#line 4678 "parser.y"
    {
	check_unreached = 0;
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 883:

/* Line 1806 of yacc.c  */
#line 4690 "parser.y"
    { BEGIN_STATEMENT ("GOBACK", 0); }
    break;

  case 884:

/* Line 1806 of yacc.c  */
#line 4691 "parser.y"
    {
	check_unreached = 1;
	cb_emit_exit (1);
  }
    break;

  case 885:

/* Line 1806 of yacc.c  */
#line 4703 "parser.y"
    { BEGIN_STATEMENT ("IF", TERM_IF); }
    break;

  case 886:

/* Line 1806 of yacc.c  */
#line 4705 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 887:

/* Line 1806 of yacc.c  */
#line 4710 "parser.y"
    {
	cb_emit_if ((yyvsp[(3) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  }
    break;

  case 889:

/* Line 1806 of yacc.c  */
#line 4718 "parser.y"
    {
	(yyval) = NULL;
  }
    break;

  case 890:

/* Line 1806 of yacc.c  */
#line 4722 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 891:

/* Line 1806 of yacc.c  */
#line 4726 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 892:

/* Line 1806 of yacc.c  */
#line 4732 "parser.y"
    { terminator_warning (TERM_IF); }
    break;

  case 893:

/* Line 1806 of yacc.c  */
#line 4733 "parser.y"
    { terminator_clear (TERM_IF); }
    break;

  case 894:

/* Line 1806 of yacc.c  */
#line 4742 "parser.y"
    { BEGIN_STATEMENT ("INITIALIZE", 0); }
    break;

  case 895:

/* Line 1806 of yacc.c  */
#line 4744 "parser.y"
    {
	cb_emit_initialize ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)]));
  }
    break;

  case 896:

/* Line 1806 of yacc.c  */
#line 4750 "parser.y"
    { (yyval) = NULL; }
    break;

  case 897:

/* Line 1806 of yacc.c  */
#line 4751 "parser.y"
    { (yyval) = cb_true; }
    break;

  case 898:

/* Line 1806 of yacc.c  */
#line 4755 "parser.y"
    { (yyval) = NULL; }
    break;

  case 899:

/* Line 1806 of yacc.c  */
#line 4756 "parser.y"
    { (yyval) = cb_true; }
    break;

  case 900:

/* Line 1806 of yacc.c  */
#line 4757 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); }
    break;

  case 901:

/* Line 1806 of yacc.c  */
#line 4761 "parser.y"
    { (yyval) = NULL; }
    break;

  case 902:

/* Line 1806 of yacc.c  */
#line 4763 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 903:

/* Line 1806 of yacc.c  */
#line 4767 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 904:

/* Line 1806 of yacc.c  */
#line 4769 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 905:

/* Line 1806 of yacc.c  */
#line 4773 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); }
    break;

  case 906:

/* Line 1806 of yacc.c  */
#line 4777 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHABETIC); }
    break;

  case 907:

/* Line 1806 of yacc.c  */
#line 4778 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC); }
    break;

  case 908:

/* Line 1806 of yacc.c  */
#line 4779 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC); }
    break;

  case 909:

/* Line 1806 of yacc.c  */
#line 4780 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC_EDITED); }
    break;

  case 910:

/* Line 1806 of yacc.c  */
#line 4781 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC_EDITED); }
    break;

  case 911:

/* Line 1806 of yacc.c  */
#line 4782 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL); }
    break;

  case 912:

/* Line 1806 of yacc.c  */
#line 4783 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL_EDITED); }
    break;

  case 913:

/* Line 1806 of yacc.c  */
#line 4787 "parser.y"
    { (yyval) = NULL; }
    break;

  case 914:

/* Line 1806 of yacc.c  */
#line 4788 "parser.y"
    { (yyval) = cb_true; }
    break;

  case 915:

/* Line 1806 of yacc.c  */
#line 4797 "parser.y"
    { BEGIN_STATEMENT ("INITIATE", 0); }
    break;

  case 916:

/* Line 1806 of yacc.c  */
#line 4799 "parser.y"
    {
	PENDING("INITIATE");
  }
    break;

  case 917:

/* Line 1806 of yacc.c  */
#line 4810 "parser.y"
    {
	BEGIN_STATEMENT ("INSPECT", 0);
	sending_id = 0;
	inspect_keyword = 0;
  }
    break;

  case 919:

/* Line 1806 of yacc.c  */
#line 4819 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 0; }
    break;

  case 920:

/* Line 1806 of yacc.c  */
#line 4820 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; }
    break;

  case 921:

/* Line 1806 of yacc.c  */
#line 4821 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; }
    break;

  case 924:

/* Line 1806 of yacc.c  */
#line 4830 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 0); }
    break;

  case 925:

/* Line 1806 of yacc.c  */
#line 4831 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int1, 1); }
    break;

  case 926:

/* Line 1806 of yacc.c  */
#line 4832 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 2); }
    break;

  case 927:

/* Line 1806 of yacc.c  */
#line 4838 "parser.y"
    { cb_init_tarrying (); }
    break;

  case 928:

/* Line 1806 of yacc.c  */
#line 4839 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 929:

/* Line 1806 of yacc.c  */
#line 4843 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 930:

/* Line 1806 of yacc.c  */
#line 4844 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 931:

/* Line 1806 of yacc.c  */
#line 4848 "parser.y"
    { (yyval) = cb_build_tarrying_data ((yyvsp[(1) - (2)])); }
    break;

  case 932:

/* Line 1806 of yacc.c  */
#line 4849 "parser.y"
    { (yyval) = cb_build_tarrying_characters ((yyvsp[(2) - (2)])); }
    break;

  case 933:

/* Line 1806 of yacc.c  */
#line 4850 "parser.y"
    { (yyval) = cb_build_tarrying_all (); }
    break;

  case 934:

/* Line 1806 of yacc.c  */
#line 4851 "parser.y"
    { (yyval) = cb_build_tarrying_leading (); }
    break;

  case 935:

/* Line 1806 of yacc.c  */
#line 4852 "parser.y"
    { (yyval) = cb_build_tarrying_trailing (); }
    break;

  case 936:

/* Line 1806 of yacc.c  */
#line 4853 "parser.y"
    { (yyval) = cb_build_tarrying_value ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 937:

/* Line 1806 of yacc.c  */
#line 4859 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); inspect_keyword = 0; }
    break;

  case 938:

/* Line 1806 of yacc.c  */
#line 4863 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 939:

/* Line 1806 of yacc.c  */
#line 4864 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 940:

/* Line 1806 of yacc.c  */
#line 4869 "parser.y"
    {
	(yyval) = cb_build_replacing_characters ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]),save_tree_1);
	inspect_keyword = 0;
  }
    break;

  case 941:

/* Line 1806 of yacc.c  */
#line 4873 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 942:

/* Line 1806 of yacc.c  */
#line 4877 "parser.y"
    { /* Nothing */ }
    break;

  case 943:

/* Line 1806 of yacc.c  */
#line 4878 "parser.y"
    { inspect_keyword = 1; }
    break;

  case 944:

/* Line 1806 of yacc.c  */
#line 4879 "parser.y"
    { inspect_keyword = 2; }
    break;

  case 945:

/* Line 1806 of yacc.c  */
#line 4880 "parser.y"
    { inspect_keyword = 3; }
    break;

  case 946:

/* Line 1806 of yacc.c  */
#line 4881 "parser.y"
    { inspect_keyword = 4; }
    break;

  case 947:

/* Line 1806 of yacc.c  */
#line 4886 "parser.y"
    {
	switch (inspect_keyword) {
		case 1:
			(yyval) = cb_build_replacing_all ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]),save_tree_1);
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

  case 948:

/* Line 1806 of yacc.c  */
#line 4912 "parser.y"
    {
          if( cb_validate_inspect(save_tree_1 ,(yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])) < 0 )
			return cb_error_node;
	(yyval) = cb_build_converting ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
  }
    break;

  case 949:

/* Line 1806 of yacc.c  */
#line 4922 "parser.y"
    { (yyval) = cb_build_inspect_region_start (); }
    break;

  case 950:

/* Line 1806 of yacc.c  */
#line 4924 "parser.y"
    { (yyval) = cb_build_inspect_region ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); }
    break;

  case 953:

/* Line 1806 of yacc.c  */
#line 4935 "parser.y"
    { BEGIN_STATEMENT ("MERGE", 0); }
    break;

  case 955:

/* Line 1806 of yacc.c  */
#line 4945 "parser.y"
    { BEGIN_STATEMENT ("MOVE", 0); }
    break;

  case 957:

/* Line 1806 of yacc.c  */
#line 4951 "parser.y"
    {
	cb_emit_move ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 958:

/* Line 1806 of yacc.c  */
#line 4955 "parser.y"
    {
	cb_emit_move_corresponding ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  }
    break;

  case 959:

/* Line 1806 of yacc.c  */
#line 4966 "parser.y"
    { BEGIN_STATEMENT ("MULTIPLY", TERM_MULTIPLY); }
    break;

  case 961:

/* Line 1806 of yacc.c  */
#line 4973 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '*', (yyvsp[(1) - (4)]));
  }
    break;

  case 962:

/* Line 1806 of yacc.c  */
#line 4977 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '*', (yyvsp[(3) - (6)])));
  }
    break;

  case 963:

/* Line 1806 of yacc.c  */
#line 4983 "parser.y"
    { terminator_warning (TERM_MULTIPLY); }
    break;

  case 964:

/* Line 1806 of yacc.c  */
#line 4984 "parser.y"
    { terminator_clear (TERM_MULTIPLY); }
    break;

  case 965:

/* Line 1806 of yacc.c  */
#line 4993 "parser.y"
    { BEGIN_STATEMENT ("OPEN", 0); }
    break;

  case 968:

/* Line 1806 of yacc.c  */
#line 5000 "parser.y"
    {
	cb_tree l;
	for (l = (yyvsp[(4) - (5)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			BEGIN_IMPLICIT_STATEMENT ();
			cb_emit_open (CB_VALUE (l), (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]));
		}
	}
  }
    break;

  case 969:

/* Line 1806 of yacc.c  */
#line 5012 "parser.y"
    { (yyval) = cb_int (COB_OPEN_INPUT); }
    break;

  case 970:

/* Line 1806 of yacc.c  */
#line 5013 "parser.y"
    { (yyval) = cb_int (COB_OPEN_OUTPUT); }
    break;

  case 971:

/* Line 1806 of yacc.c  */
#line 5014 "parser.y"
    { (yyval) = cb_int (COB_OPEN_I_O); }
    break;

  case 972:

/* Line 1806 of yacc.c  */
#line 5015 "parser.y"
    { (yyval) = cb_int (COB_OPEN_EXTEND); }
    break;

  case 973:

/* Line 1806 of yacc.c  */
#line 5019 "parser.y"
    { (yyval) = NULL; }
    break;

  case 974:

/* Line 1806 of yacc.c  */
#line 5020 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 975:

/* Line 1806 of yacc.c  */
#line 5024 "parser.y"
    { (yyval) = NULL; }
    break;

  case 976:

/* Line 1806 of yacc.c  */
#line 5025 "parser.y"
    { (yyval) = NULL; }
    break;

  case 977:

/* Line 1806 of yacc.c  */
#line 5026 "parser.y"
    { PENDING ("OPEN ... WITH LOCK"); }
    break;

  case 978:

/* Line 1806 of yacc.c  */
#line 5038 "parser.y"
    { BEGIN_STATEMENT ("PERFORM", TERM_PERFORM); }
    break;

  case 980:

/* Line 1806 of yacc.c  */
#line 5044 "parser.y"
    {
	cb_emit_perform ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));
  }
    break;

  case 981:

/* Line 1806 of yacc.c  */
#line 5048 "parser.y"
    {
	perform_stack = cb_cons ((yyvsp[(1) - (1)]), perform_stack);
	check_unreached = 0;
  }
    break;

  case 982:

/* Line 1806 of yacc.c  */
#line 5053 "parser.y"
    {
	perform_stack = CB_CHAIN (perform_stack);
	cb_emit_perform ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  }
    break;

  case 983:

/* Line 1806 of yacc.c  */
#line 5058 "parser.y"
    {
	cb_emit_perform ((yyvsp[(1) - (2)]), NULL);
  }
    break;

  case 984:

/* Line 1806 of yacc.c  */
#line 5064 "parser.y"
    { terminator_error (); }
    break;

  case 985:

/* Line 1806 of yacc.c  */
#line 5065 "parser.y"
    { terminator_clear (TERM_PERFORM); }
    break;

  case 986:

/* Line 1806 of yacc.c  */
#line 5070 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(1) - (1)]))->length = cb_true; /* return from $1 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (1)]), (yyvsp[(1) - (1)]));
  }
    break;

  case 987:

/* Line 1806 of yacc.c  */
#line 5075 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(3) - (3)]))->length = cb_true; /* return from $3 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 988:

/* Line 1806 of yacc.c  */
#line 5083 "parser.y"
    {
	(yyval) = cb_build_perform_once (NULL);
  }
    break;

  case 989:

/* Line 1806 of yacc.c  */
#line 5087 "parser.y"
    {
	(yyval) = cb_build_perform_forever (NULL);
  }
    break;

  case 990:

/* Line 1806 of yacc.c  */
#line 5091 "parser.y"
    {
	(yyval) = cb_build_perform_times ((yyvsp[(1) - (2)]));
	current_program->loop_counter++;
  }
    break;

  case 991:

/* Line 1806 of yacc.c  */
#line 5096 "parser.y"
    {
	cb_tree varying;

	varying = cb_list_init (cb_build_perform_varying (NULL, NULL, NULL, (yyvsp[(3) - (3)])));
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), varying);
  }
    break;

  case 992:

/* Line 1806 of yacc.c  */
#line 5103 "parser.y"
    {
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 993:

/* Line 1806 of yacc.c  */
#line 5109 "parser.y"
    { (yyval) = CB_BEFORE; }
    break;

  case 994:

/* Line 1806 of yacc.c  */
#line 5110 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 995:

/* Line 1806 of yacc.c  */
#line 5114 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 996:

/* Line 1806 of yacc.c  */
#line 5116 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 997:

/* Line 1806 of yacc.c  */
#line 5121 "parser.y"
    {
	(yyval) = cb_build_perform_varying ((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  }
    break;

  case 998:

/* Line 1806 of yacc.c  */
#line 5132 "parser.y"
    { BEGIN_STATEMENT ("READ", TERM_READ); }
    break;

  case 999:

/* Line 1806 of yacc.c  */
#line 5135 "parser.y"
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
  }
    break;

  case 1000:

/* Line 1806 of yacc.c  */
#line 5155 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1001:

/* Line 1806 of yacc.c  */
#line 5156 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 1002:

/* Line 1806 of yacc.c  */
#line 5160 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1003:

/* Line 1806 of yacc.c  */
#line 5162 "parser.y"
    {
	(yyval) = cb_int3;
  }
    break;

  case 1004:

/* Line 1806 of yacc.c  */
#line 5166 "parser.y"
    {
	(yyval) = cb_int1;
  }
    break;

  case 1005:

/* Line 1806 of yacc.c  */
#line 5170 "parser.y"
    {
	(yyval) = cb_int2;
  }
    break;

  case 1006:

/* Line 1806 of yacc.c  */
#line 5174 "parser.y"
    {
	(yyval) = cb_int3;
  }
    break;

  case 1007:

/* Line 1806 of yacc.c  */
#line 5178 "parser.y"
    {
	(yyval) = cb_int4;
  }
    break;

  case 1008:

/* Line 1806 of yacc.c  */
#line 5184 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1009:

/* Line 1806 of yacc.c  */
#line 5185 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 1013:

/* Line 1806 of yacc.c  */
#line 5194 "parser.y"
    { terminator_warning (TERM_READ); }
    break;

  case 1014:

/* Line 1806 of yacc.c  */
#line 5195 "parser.y"
    { terminator_clear (TERM_READ); }
    break;

  case 1015:

/* Line 1806 of yacc.c  */
#line 5204 "parser.y"
    { BEGIN_STATEMENT ("RELEASE", 0); }
    break;

  case 1016:

/* Line 1806 of yacc.c  */
#line 5206 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_release ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
	}
  }
    break;

  case 1017:

/* Line 1806 of yacc.c  */
#line 5219 "parser.y"
    { BEGIN_STATEMENT ("RETURN", TERM_RETURN); }
    break;

  case 1018:

/* Line 1806 of yacc.c  */
#line 5222 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_return ((yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]));
	}
  }
    break;

  case 1019:

/* Line 1806 of yacc.c  */
#line 5230 "parser.y"
    { terminator_warning (TERM_RETURN); }
    break;

  case 1020:

/* Line 1806 of yacc.c  */
#line 5231 "parser.y"
    { terminator_clear (TERM_RETURN); }
    break;

  case 1021:

/* Line 1806 of yacc.c  */
#line 5240 "parser.y"
    { BEGIN_STATEMENT ("REWRITE", TERM_REWRITE); }
    break;

  case 1022:

/* Line 1806 of yacc.c  */
#line 5243 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_rewrite ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]));
	}
  }
    break;

  case 1023:

/* Line 1806 of yacc.c  */
#line 5251 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1024:

/* Line 1806 of yacc.c  */
#line 5253 "parser.y"
    {
	(yyval) = cb_int1;
  }
    break;

  case 1025:

/* Line 1806 of yacc.c  */
#line 5257 "parser.y"
    {
	(yyval) = cb_int2;
  }
    break;

  case 1026:

/* Line 1806 of yacc.c  */
#line 5263 "parser.y"
    { terminator_warning (TERM_REWRITE); }
    break;

  case 1027:

/* Line 1806 of yacc.c  */
#line 5264 "parser.y"
    { terminator_clear (TERM_REWRITE); }
    break;

  case 1028:

/* Line 1806 of yacc.c  */
#line 5274 "parser.y"
    {
	BEGIN_STATEMENT ("ROLLBACK", 0);
	cb_emit_rollback ();
  }
    break;

  case 1029:

/* Line 1806 of yacc.c  */
#line 5286 "parser.y"
    { BEGIN_STATEMENT ("SEARCH", TERM_SEARCH); }
    break;

  case 1031:

/* Line 1806 of yacc.c  */
#line 5293 "parser.y"
    {
	cb_emit_search ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
  }
    break;

  case 1032:

/* Line 1806 of yacc.c  */
#line 5297 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1033:

/* Line 1806 of yacc.c  */
#line 5301 "parser.y"
    {
	cb_emit_search_all ((yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  }
    break;

  case 1034:

/* Line 1806 of yacc.c  */
#line 5307 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1035:

/* Line 1806 of yacc.c  */
#line 5308 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 1036:

/* Line 1806 of yacc.c  */
#line 5312 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1037:

/* Line 1806 of yacc.c  */
#line 5314 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1038:

/* Line 1806 of yacc.c  */
#line 5318 "parser.y"
    {
	(yyval) = (yyvsp[(4) - (4)]);
  }
    break;

  case 1039:

/* Line 1806 of yacc.c  */
#line 5324 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1040:

/* Line 1806 of yacc.c  */
#line 5325 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); CB_IF ((yyvsp[(1) - (2)]))->stmt2 = (yyvsp[(2) - (2)]); }
    break;

  case 1041:

/* Line 1806 of yacc.c  */
#line 5330 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1042:

/* Line 1806 of yacc.c  */
#line 5334 "parser.y"
    {
	(yyval) = cb_build_if ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), NULL);
  }
    break;

  case 1043:

/* Line 1806 of yacc.c  */
#line 5340 "parser.y"
    { terminator_warning (TERM_SEARCH); }
    break;

  case 1044:

/* Line 1806 of yacc.c  */
#line 5341 "parser.y"
    { terminator_clear (TERM_SEARCH); }
    break;

  case 1045:

/* Line 1806 of yacc.c  */
#line 5350 "parser.y"
    { BEGIN_STATEMENT ("SET", 0); }
    break;

  case 1052:

/* Line 1806 of yacc.c  */
#line 5366 "parser.y"
    {
	cb_emit_setenv ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  }
    break;

  case 1053:

/* Line 1806 of yacc.c  */
#line 5375 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (4)]), cb_build_ppointer ((yyvsp[(4) - (4)])));
  }
    break;

  case 1054:

/* Line 1806 of yacc.c  */
#line 5379 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 1055:

/* Line 1806 of yacc.c  */
#line 5388 "parser.y"
    {
	cb_emit_set_up_down ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  }
    break;

  case 1056:

/* Line 1806 of yacc.c  */
#line 5394 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 1057:

/* Line 1806 of yacc.c  */
#line 5395 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1060:

/* Line 1806 of yacc.c  */
#line 5407 "parser.y"
    {
	cb_emit_set_on_off ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 1063:

/* Line 1806 of yacc.c  */
#line 5421 "parser.y"
    {
	cb_emit_set_true ((yyvsp[(1) - (3)]));
  }
    break;

  case 1064:

/* Line 1806 of yacc.c  */
#line 5425 "parser.y"
    {
	cb_emit_set_false ((yyvsp[(1) - (3)]));
  }
    break;

  case 1065:

/* Line 1806 of yacc.c  */
#line 5436 "parser.y"
    { BEGIN_STATEMENT ("SORT", 0); }
    break;

  case 1067:

/* Line 1806 of yacc.c  */
#line 5442 "parser.y"
    {
	cb_emit_sort_init ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (4)]))) && (yyvsp[(2) - (4)]) == NULL) {
		cb_error (_("File sort requires KEY phrase"));
	}
	/* used in sort_input/sort_output */
	save_tree_1 = (yyvsp[(1) - (4)]);
  }
    break;

  case 1068:

/* Line 1806 of yacc.c  */
#line 5451 "parser.y"
    {
	cb_emit_sort_finish ((yyvsp[(1) - (7)]));
  }
    break;

  case 1069:

/* Line 1806 of yacc.c  */
#line 5458 "parser.y"
    {
	(yyval) = NULL;
  }
    break;

  case 1070:

/* Line 1806 of yacc.c  */
#line 5463 "parser.y"
    {
	cb_tree l;

	if ((yyvsp[(5) - (5)]) == NULL) {
		(yyvsp[(5) - (5)]) = cb_list_init (NULL);
	}
	for (l = (yyvsp[(5) - (5)]); l; l = CB_CHAIN (l)) {
		CB_PURPOSE (l) = (yyvsp[(3) - (5)]);
	}
	(yyval) = cb_list_append ((yyvsp[(1) - (5)]), (yyvsp[(5) - (5)]));
  }
    break;

  case 1071:

/* Line 1806 of yacc.c  */
#line 5477 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1072:

/* Line 1806 of yacc.c  */
#line 5478 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1074:

/* Line 1806 of yacc.c  */
#line 5482 "parser.y"
    { /* nothing */ }
    break;

  case 1075:

/* Line 1806 of yacc.c  */
#line 5486 "parser.y"
    { (yyval) = cb_null; }
    break;

  case 1076:

/* Line 1806 of yacc.c  */
#line 5487 "parser.y"
    { (yyval) = cb_ref ((yyvsp[(3) - (3)])); }
    break;

  case 1077:

/* Line 1806 of yacc.c  */
#line 5492 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires USING or INPUT PROCEDURE"));
	}
  }
    break;

  case 1078:

/* Line 1806 of yacc.c  */
#line 5498 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("USING invalid with table SORT"));
	} else {
		cb_emit_sort_using (save_tree_1, (yyvsp[(2) - (2)]));
	}
  }
    break;

  case 1079:

/* Line 1806 of yacc.c  */
#line 5506 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("INPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_input ((yyvsp[(4) - (4)]));
	}
  }
    break;

  case 1080:

/* Line 1806 of yacc.c  */
#line 5517 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires GIVING or OUTPUT PROCEDURE"));
	}
  }
    break;

  case 1081:

/* Line 1806 of yacc.c  */
#line 5523 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("GIVING invalid with table SORT"));
	} else {
		cb_emit_sort_giving (save_tree_1, (yyvsp[(2) - (2)]));
	}
  }
    break;

  case 1082:

/* Line 1806 of yacc.c  */
#line 5531 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("OUTPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_output ((yyvsp[(4) - (4)]));
	}
  }
    break;

  case 1083:

/* Line 1806 of yacc.c  */
#line 5546 "parser.y"
    { BEGIN_STATEMENT ("START", TERM_START); }
    break;

  case 1084:

/* Line 1806 of yacc.c  */
#line 5547 "parser.y"
    { (yyval) = cb_int (COB_EQ); }
    break;

  case 1085:

/* Line 1806 of yacc.c  */
#line 5550 "parser.y"
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

  case 1086:

/* Line 1806 of yacc.c  */
#line 5567 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1087:

/* Line 1806 of yacc.c  */
#line 5568 "parser.y"
    { (yyvsp[(0) - (4)]) = (yyvsp[(3) - (4)]); (yyval) = (yyvsp[(4) - (4)]); }
    break;

  case 1088:

/* Line 1806 of yacc.c  */
#line 5572 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_NE : COB_EQ); }
    break;

  case 1089:

/* Line 1806 of yacc.c  */
#line 5573 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LE : COB_GT); }
    break;

  case 1090:

/* Line 1806 of yacc.c  */
#line 5574 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GE : COB_LT); }
    break;

  case 1091:

/* Line 1806 of yacc.c  */
#line 5575 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LT : COB_GE); }
    break;

  case 1092:

/* Line 1806 of yacc.c  */
#line 5576 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GT : COB_LE); }
    break;

  case 1093:

/* Line 1806 of yacc.c  */
#line 5580 "parser.y"
    { terminator_warning (TERM_START); }
    break;

  case 1094:

/* Line 1806 of yacc.c  */
#line 5581 "parser.y"
    { terminator_clear (TERM_START); }
    break;

  case 1095:

/* Line 1806 of yacc.c  */
#line 5590 "parser.y"
    { BEGIN_STATEMENT ("STOP", 0); }
    break;

  case 1096:

/* Line 1806 of yacc.c  */
#line 5592 "parser.y"
    {
	cb_emit_stop_run ((yyvsp[(4) - (4)]));
  }
    break;

  case 1097:

/* Line 1806 of yacc.c  */
#line 5596 "parser.y"
    {
	cb_verify (cb_stop_literal_statement, "STOP literal");
  }
    break;

  case 1098:

/* Line 1806 of yacc.c  */
#line 5602 "parser.y"
    { (yyval) = current_program->cb_return_code; }
    break;

  case 1099:

/* Line 1806 of yacc.c  */
#line 5603 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 1100:

/* Line 1806 of yacc.c  */
#line 5604 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 1101:

/* Line 1806 of yacc.c  */
#line 5613 "parser.y"
    { BEGIN_STATEMENT ("STRING", TERM_STRING); }
    break;

  case 1102:

/* Line 1806 of yacc.c  */
#line 5616 "parser.y"
    {
	cb_emit_string ((yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]));
  }
    break;

  case 1103:

/* Line 1806 of yacc.c  */
#line 5622 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 1104:

/* Line 1806 of yacc.c  */
#line 5623 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1105:

/* Line 1806 of yacc.c  */
#line 5627 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1106:

/* Line 1806 of yacc.c  */
#line 5628 "parser.y"
    { (yyval) = cb_build_pair (cb_int0, NULL); }
    break;

  case 1107:

/* Line 1806 of yacc.c  */
#line 5629 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), NULL); }
    break;

  case 1108:

/* Line 1806 of yacc.c  */
#line 5633 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 1109:

/* Line 1806 of yacc.c  */
#line 5634 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 1110:

/* Line 1806 of yacc.c  */
#line 5638 "parser.y"
    { terminator_warning (TERM_STRING); }
    break;

  case 1111:

/* Line 1806 of yacc.c  */
#line 5639 "parser.y"
    { terminator_clear (TERM_STRING); }
    break;

  case 1112:

/* Line 1806 of yacc.c  */
#line 5648 "parser.y"
    { BEGIN_STATEMENT ("SUBTRACT", TERM_SUBTRACT); }
    break;

  case 1114:

/* Line 1806 of yacc.c  */
#line 5655 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '-', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  }
    break;

  case 1115:

/* Line 1806 of yacc.c  */
#line 5659 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_list (cb_cons ((yyvsp[(3) - (6)]), (yyvsp[(1) - (6)])), '-'));
  }
    break;

  case 1116:

/* Line 1806 of yacc.c  */
#line 5663 "parser.y"
    {
	cb_emit_corresponding (cb_build_sub, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  }
    break;

  case 1117:

/* Line 1806 of yacc.c  */
#line 5669 "parser.y"
    { terminator_warning (TERM_SUBTRACT); }
    break;

  case 1118:

/* Line 1806 of yacc.c  */
#line 5670 "parser.y"
    { terminator_clear (TERM_SUBTRACT); }
    break;

  case 1119:

/* Line 1806 of yacc.c  */
#line 5680 "parser.y"
    {
	BEGIN_STATEMENT ("SUPPRESS", 0);
	PENDING("SUPPRESS");
  }
    break;

  case 1122:

/* Line 1806 of yacc.c  */
#line 5695 "parser.y"
    { BEGIN_STATEMENT ("TERMINATE", 0); }
    break;

  case 1123:

/* Line 1806 of yacc.c  */
#line 5697 "parser.y"
    {
	PENDING("TERMINATE");
  }
    break;

  case 1124:

/* Line 1806 of yacc.c  */
#line 5708 "parser.y"
    { BEGIN_STATEMENT ("TRANSFORM", 0); }
    break;

  case 1125:

/* Line 1806 of yacc.c  */
#line 5710 "parser.y"
    {
	cb_tree		x;

	x = cb_build_converting ((yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]), cb_build_inspect_region_start ());
	cb_emit_inspect ((yyvsp[(3) - (7)]), x, cb_int0, 2);
  }
    break;

  case 1126:

/* Line 1806 of yacc.c  */
#line 5724 "parser.y"
    { BEGIN_STATEMENT ("UNLOCK", 0); }
    break;

  case 1127:

/* Line 1806 of yacc.c  */
#line 5726 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_unlock ((yyvsp[(3) - (4)]));
	}
  }
    break;

  case 1131:

/* Line 1806 of yacc.c  */
#line 5745 "parser.y"
    { BEGIN_STATEMENT ("UNSTRING", TERM_UNSTRING); }
    break;

  case 1132:

/* Line 1806 of yacc.c  */
#line 5749 "parser.y"
    {
	cb_emit_unstring ((yyvsp[(3) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]));
  }
    break;

  case 1133:

/* Line 1806 of yacc.c  */
#line 5755 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1134:

/* Line 1806 of yacc.c  */
#line 5757 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 1135:

/* Line 1806 of yacc.c  */
#line 5761 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 1136:

/* Line 1806 of yacc.c  */
#line 5763 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 1137:

/* Line 1806 of yacc.c  */
#line 5768 "parser.y"
    {
	(yyval) = cb_build_unstring_delimited ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
  }
    break;

  case 1138:

/* Line 1806 of yacc.c  */
#line 5774 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); }
    break;

  case 1139:

/* Line 1806 of yacc.c  */
#line 5776 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1140:

/* Line 1806 of yacc.c  */
#line 5781 "parser.y"
    {
	(yyval) = cb_build_unstring_into ((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 1141:

/* Line 1806 of yacc.c  */
#line 5787 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1142:

/* Line 1806 of yacc.c  */
#line 5788 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 1143:

/* Line 1806 of yacc.c  */
#line 5792 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1144:

/* Line 1806 of yacc.c  */
#line 5793 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 1145:

/* Line 1806 of yacc.c  */
#line 5797 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1146:

/* Line 1806 of yacc.c  */
#line 5798 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); }
    break;

  case 1147:

/* Line 1806 of yacc.c  */
#line 5802 "parser.y"
    { terminator_warning (TERM_UNSTRING); }
    break;

  case 1148:

/* Line 1806 of yacc.c  */
#line 5803 "parser.y"
    { terminator_clear (TERM_UNSTRING); }
    break;

  case 1152:

/* Line 1806 of yacc.c  */
#line 5821 "parser.y"
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

  case 1153:

/* Line 1806 of yacc.c  */
#line 5842 "parser.y"
    {
	use_global_ind = 0;
  }
    break;

  case 1154:

/* Line 1806 of yacc.c  */
#line 5846 "parser.y"
    {
	use_global_ind = 1;
	current_program->flag_global_use = 1;
  }
    break;

  case 1155:

/* Line 1806 of yacc.c  */
#line 5854 "parser.y"
    {
	cb_tree		l;

	for (l = (yyvsp[(1) - (1)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			setup_use_file (CB_FILE (cb_ref (CB_VALUE (l))));
		}
	}
  }
    break;

  case 1156:

/* Line 1806 of yacc.c  */
#line 5864 "parser.y"
    {
	current_program->global_handler[COB_OPEN_INPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_INPUT].handler_prog = current_program;
  }
    break;

  case 1157:

/* Line 1806 of yacc.c  */
#line 5869 "parser.y"
    {
	current_program->global_handler[COB_OPEN_OUTPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_OUTPUT].handler_prog = current_program;
  }
    break;

  case 1158:

/* Line 1806 of yacc.c  */
#line 5874 "parser.y"
    {
	current_program->global_handler[COB_OPEN_I_O].handler_label = current_section;
	current_program->global_handler[COB_OPEN_I_O].handler_prog = current_program;
  }
    break;

  case 1159:

/* Line 1806 of yacc.c  */
#line 5879 "parser.y"
    {
	current_program->global_handler[COB_OPEN_EXTEND].handler_label = current_section;
	current_program->global_handler[COB_OPEN_EXTEND].handler_prog = current_program;
  }
    break;

  case 1172:

/* Line 1806 of yacc.c  */
#line 5911 "parser.y"
    {
	PENDING ("USE FOR DEBUGGING");
  }
    break;

  case 1175:

/* Line 1806 of yacc.c  */
#line 5923 "parser.y"
    {
	PENDING ("USE BEFORE REPORTING");
  }
    break;

  case 1176:

/* Line 1806 of yacc.c  */
#line 5934 "parser.y"
    { BEGIN_STATEMENT ("WRITE", TERM_WRITE); }
    break;

  case 1177:

/* Line 1806 of yacc.c  */
#line 5937 "parser.y"
    {
	if ((yyvsp[(3) - (8)]) != cb_error_node) {
		cb_emit_write ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(5) - (8)]));
	}
  }
    break;

  case 1178:

/* Line 1806 of yacc.c  */
#line 5945 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1179:

/* Line 1806 of yacc.c  */
#line 5946 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 1180:

/* Line 1806 of yacc.c  */
#line 5951 "parser.y"
    {
	(yyval) = cb_int0;
  }
    break;

  case 1181:

/* Line 1806 of yacc.c  */
#line 5955 "parser.y"
    {
	(yyval) = cb_build_write_advancing_lines ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  }
    break;

  case 1182:

/* Line 1806 of yacc.c  */
#line 5959 "parser.y"
    {
	(yyval) = cb_build_write_advancing_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  }
    break;

  case 1183:

/* Line 1806 of yacc.c  */
#line 5963 "parser.y"
    {
	(yyval) = cb_build_write_advancing_page ((yyvsp[(1) - (3)]));
  }
    break;

  case 1184:

/* Line 1806 of yacc.c  */
#line 5969 "parser.y"
    { (yyval) = CB_BEFORE; }
    break;

  case 1185:

/* Line 1806 of yacc.c  */
#line 5970 "parser.y"
    { (yyval) = CB_AFTER; }
    break;

  case 1189:

/* Line 1806 of yacc.c  */
#line 5979 "parser.y"
    { terminator_warning (TERM_WRITE); }
    break;

  case 1190:

/* Line 1806 of yacc.c  */
#line 5980 "parser.y"
    { terminator_clear (TERM_WRITE); }
    break;

  case 1191:

/* Line 1806 of yacc.c  */
#line 5995 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_ACCEPT;
  }
    break;

  case 1192:

/* Line 1806 of yacc.c  */
#line 6003 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_DISPLAY;
  }
    break;

  case 1194:

/* Line 1806 of yacc.c  */
#line 6010 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1195:

/* Line 1806 of yacc.c  */
#line 6014 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  }
    break;

  case 1197:

/* Line 1806 of yacc.c  */
#line 6021 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1198:

/* Line 1806 of yacc.c  */
#line 6025 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  }
    break;

  case 1201:

/* Line 1806 of yacc.c  */
#line 6041 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  }
    break;

  case 1202:

/* Line 1806 of yacc.c  */
#line 6046 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  }
    break;

  case 1204:

/* Line 1806 of yacc.c  */
#line 6053 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  }
    break;

  case 1205:

/* Line 1806 of yacc.c  */
#line 6058 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  }
    break;

  case 1206:

/* Line 1806 of yacc.c  */
#line 6070 "parser.y"
    {
	current_statement->handler_id = COB_EC_OVERFLOW;
  }
    break;

  case 1208:

/* Line 1806 of yacc.c  */
#line 6077 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1209:

/* Line 1806 of yacc.c  */
#line 6081 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  }
    break;

  case 1211:

/* Line 1806 of yacc.c  */
#line 6088 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1212:

/* Line 1806 of yacc.c  */
#line 6092 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  }
    break;

  case 1213:

/* Line 1806 of yacc.c  */
#line 6104 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  }
    break;

  case 1214:

/* Line 1806 of yacc.c  */
#line 6109 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  }
    break;

  case 1215:

/* Line 1806 of yacc.c  */
#line 6114 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  }
    break;

  case 1216:

/* Line 1806 of yacc.c  */
#line 6123 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1217:

/* Line 1806 of yacc.c  */
#line 6127 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 1218:

/* Line 1806 of yacc.c  */
#line 6134 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1219:

/* Line 1806 of yacc.c  */
#line 6138 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 1220:

/* Line 1806 of yacc.c  */
#line 6150 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  }
    break;

  case 1221:

/* Line 1806 of yacc.c  */
#line 6155 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  }
    break;

  case 1222:

/* Line 1806 of yacc.c  */
#line 6160 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  }
    break;

  case 1223:

/* Line 1806 of yacc.c  */
#line 6169 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1224:

/* Line 1806 of yacc.c  */
#line 6173 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 1225:

/* Line 1806 of yacc.c  */
#line 6180 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1226:

/* Line 1806 of yacc.c  */
#line 6184 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 1229:

/* Line 1806 of yacc.c  */
#line 6200 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  }
    break;

  case 1230:

/* Line 1806 of yacc.c  */
#line 6205 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  }
    break;

  case 1231:

/* Line 1806 of yacc.c  */
#line 6210 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  }
    break;

  case 1232:

/* Line 1806 of yacc.c  */
#line 6219 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1233:

/* Line 1806 of yacc.c  */
#line 6223 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 1234:

/* Line 1806 of yacc.c  */
#line 6230 "parser.y"
    {
	check_unreached = 0;
  }
    break;

  case 1235:

/* Line 1806 of yacc.c  */
#line 6234 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  }
    break;

  case 1236:

/* Line 1806 of yacc.c  */
#line 6246 "parser.y"
    {
	(yyval) = cb_one;
  }
    break;

  case 1237:

/* Line 1806 of yacc.c  */
#line 6250 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (3)]);
  }
    break;

  case 1238:

/* Line 1806 of yacc.c  */
#line 6262 "parser.y"
    {
	(yyval) = cb_build_cond ((yyvsp[(1) - (1)]));
  }
    break;

  case 1239:

/* Line 1806 of yacc.c  */
#line 6269 "parser.y"
    {
	(yyval) = cb_build_expr ((yyvsp[(1) - (1)]));
  }
    break;

  case 1240:

/* Line 1806 of yacc.c  */
#line 6275 "parser.y"
    {
	current_expr = NULL;
  }
    break;

  case 1241:

/* Line 1806 of yacc.c  */
#line 6279 "parser.y"
    {
	(yyval) = cb_list_reverse (current_expr);
  }
    break;

  case 1245:

/* Line 1806 of yacc.c  */
#line 6291 "parser.y"
    { push_expr ('x', (yyvsp[(1) - (1)])); }
    break;

  case 1246:

/* Line 1806 of yacc.c  */
#line 6293 "parser.y"
    { push_expr ('(', NULL); }
    break;

  case 1247:

/* Line 1806 of yacc.c  */
#line 6294 "parser.y"
    { push_expr (')', NULL); }
    break;

  case 1248:

/* Line 1806 of yacc.c  */
#line 6296 "parser.y"
    { push_expr ('+', NULL); }
    break;

  case 1249:

/* Line 1806 of yacc.c  */
#line 6297 "parser.y"
    { push_expr ('-', NULL); }
    break;

  case 1250:

/* Line 1806 of yacc.c  */
#line 6298 "parser.y"
    { push_expr ('*', NULL); }
    break;

  case 1251:

/* Line 1806 of yacc.c  */
#line 6299 "parser.y"
    { push_expr ('/', NULL); }
    break;

  case 1252:

/* Line 1806 of yacc.c  */
#line 6300 "parser.y"
    { push_expr ('^', NULL); }
    break;

  case 1253:

/* Line 1806 of yacc.c  */
#line 6302 "parser.y"
    { push_expr ('=', NULL); }
    break;

  case 1254:

/* Line 1806 of yacc.c  */
#line 6303 "parser.y"
    { push_expr ('>', NULL); }
    break;

  case 1255:

/* Line 1806 of yacc.c  */
#line 6304 "parser.y"
    { push_expr ('<', NULL); }
    break;

  case 1256:

/* Line 1806 of yacc.c  */
#line 6305 "parser.y"
    { push_expr (']', NULL); }
    break;

  case 1257:

/* Line 1806 of yacc.c  */
#line 6306 "parser.y"
    { push_expr ('[', NULL); }
    break;

  case 1258:

/* Line 1806 of yacc.c  */
#line 6307 "parser.y"
    { push_expr ('~', NULL); }
    break;

  case 1259:

/* Line 1806 of yacc.c  */
#line 6309 "parser.y"
    { push_expr ('!', NULL); }
    break;

  case 1260:

/* Line 1806 of yacc.c  */
#line 6310 "parser.y"
    { push_expr ('&', NULL); }
    break;

  case 1261:

/* Line 1806 of yacc.c  */
#line 6311 "parser.y"
    { push_expr ('|', NULL); }
    break;

  case 1262:

/* Line 1806 of yacc.c  */
#line 6313 "parser.y"
    { push_expr ('O', NULL); }
    break;

  case 1263:

/* Line 1806 of yacc.c  */
#line 6314 "parser.y"
    { push_expr ('9', NULL); }
    break;

  case 1264:

/* Line 1806 of yacc.c  */
#line 6315 "parser.y"
    { push_expr ('A', NULL); }
    break;

  case 1265:

/* Line 1806 of yacc.c  */
#line 6316 "parser.y"
    { push_expr ('L', NULL); }
    break;

  case 1266:

/* Line 1806 of yacc.c  */
#line 6317 "parser.y"
    { push_expr ('U', NULL); }
    break;

  case 1267:

/* Line 1806 of yacc.c  */
#line 6320 "parser.y"
    { push_expr ('P', NULL); }
    break;

  case 1268:

/* Line 1806 of yacc.c  */
#line 6321 "parser.y"
    { push_expr ('N', NULL); }
    break;

  case 1280:

/* Line 1806 of yacc.c  */
#line 6333 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 1281:

/* Line 1806 of yacc.c  */
#line 6334 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 1285:

/* Line 1806 of yacc.c  */
#line 6343 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1286:

/* Line 1806 of yacc.c  */
#line 6344 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '+', (yyvsp[(3) - (3)])); }
    break;

  case 1287:

/* Line 1806 of yacc.c  */
#line 6345 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '-', (yyvsp[(3) - (3)])); }
    break;

  case 1288:

/* Line 1806 of yacc.c  */
#line 6346 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '*', (yyvsp[(3) - (3)])); }
    break;

  case 1289:

/* Line 1806 of yacc.c  */
#line 6347 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '/', (yyvsp[(3) - (3)])); }
    break;

  case 1290:

/* Line 1806 of yacc.c  */
#line 6348 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 1291:

/* Line 1806 of yacc.c  */
#line 6349 "parser.y"
    { (yyval) = cb_build_binary_op (cb_zero, '-', (yyvsp[(2) - (2)])); }
    break;

  case 1292:

/* Line 1806 of yacc.c  */
#line 6350 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '^', (yyvsp[(3) - (3)])); }
    break;

  case 1293:

/* Line 1806 of yacc.c  */
#line 6351 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 1294:

/* Line 1806 of yacc.c  */
#line 6363 "parser.y"
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

  case 1295:

/* Line 1806 of yacc.c  */
#line 6375 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(3) - (3)])))) {
		(yyval) = CB_FILE (cb_ref ((yyvsp[(3) - (3)])))->linage_ctr;
	} else {
		cb_error_x ((yyvsp[(3) - (3)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(3) - (3)])));
		(yyval) = cb_error_node;
	}
  }
    break;

  case 1296:

/* Line 1806 of yacc.c  */
#line 6389 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1297:

/* Line 1806 of yacc.c  */
#line 6391 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1298:

/* Line 1806 of yacc.c  */
#line 6395 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)])); }
    break;

  case 1299:

/* Line 1806 of yacc.c  */
#line 6401 "parser.y"
    { cb_build_identifier ((yyvsp[(1) - (1)])); }
    break;

  case 1300:

/* Line 1806 of yacc.c  */
#line 6408 "parser.y"
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

  case 1301:

/* Line 1806 of yacc.c  */
#line 6428 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (1)]));
  }
    break;

  case 1302:

/* Line 1806 of yacc.c  */
#line 6432 "parser.y"
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

  case 1303:

/* Line 1806 of yacc.c  */
#line 6448 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (1)])))) {
		(yyval) = (yyvsp[(1) - (1)]);
	} else {
		cb_error_x ((yyvsp[(1) - (1)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(1) - (1)])));
		(yyval) = cb_error_node;
	}
  }
    break;

  case 1304:

/* Line 1806 of yacc.c  */
#line 6461 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 1305:

/* Line 1806 of yacc.c  */
#line 6463 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1306:

/* Line 1806 of yacc.c  */
#line 6467 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1307:

/* Line 1806 of yacc.c  */
#line 6473 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1308:

/* Line 1806 of yacc.c  */
#line 6475 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1309:

/* Line 1806 of yacc.c  */
#line 6480 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	CB_REFERENCE ((yyval))->offset = CB_TREE (current_section);
	current_program->label_list = cb_cons ((yyval), current_program->label_list);
  }
    break;

  case 1313:

/* Line 1806 of yacc.c  */
#line 6495 "parser.y"
    {
	(yyval) = cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(1) - (1)]))->data));
	(yyval)->source_file = (yyvsp[(1) - (1)])->source_file;
	(yyval)->source_line = (yyvsp[(1) - (1)])->source_line;
  }
    break;

  case 1314:

/* Line 1806 of yacc.c  */
#line 6505 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 1315:

/* Line 1806 of yacc.c  */
#line 6506 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1316:

/* Line 1806 of yacc.c  */
#line 6511 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	current_program->reference_list = cb_cons ((yyval), current_program->reference_list);
  }
    break;

  case 1317:

/* Line 1806 of yacc.c  */
#line 6518 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1318:

/* Line 1806 of yacc.c  */
#line 6519 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1321:

/* Line 1806 of yacc.c  */
#line 6531 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE ((yyval))->word->count > 0) {
		redefinition_error ((yyval));
		(yyval) = cb_error_node;
	}
  }
    break;

  case 1322:

/* Line 1806 of yacc.c  */
#line 6550 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 1323:

/* Line 1806 of yacc.c  */
#line 6551 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1325:

/* Line 1806 of yacc.c  */
#line 6556 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); }
    break;

  case 1326:

/* Line 1806 of yacc.c  */
#line 6560 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); }
    break;

  case 1327:

/* Line 1806 of yacc.c  */
#line 6561 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 1329:

/* Line 1806 of yacc.c  */
#line 6566 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); }
    break;

  case 1330:

/* Line 1806 of yacc.c  */
#line 6567 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); }
    break;

  case 1331:

/* Line 1806 of yacc.c  */
#line 6568 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); }
    break;

  case 1332:

/* Line 1806 of yacc.c  */
#line 6569 "parser.y"
    { (yyval) = cb_build_ppointer ((yyvsp[(4) - (4)])); }
    break;

  case 1333:

/* Line 1806 of yacc.c  */
#line 6570 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); }
    break;

  case 1338:

/* Line 1806 of yacc.c  */
#line 6578 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); }
    break;

  case 1339:

/* Line 1806 of yacc.c  */
#line 6579 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); }
    break;

  case 1340:

/* Line 1806 of yacc.c  */
#line 6580 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); }
    break;

  case 1346:

/* Line 1806 of yacc.c  */
#line 6592 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1347:

/* Line 1806 of yacc.c  */
#line 6593 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1359:

/* Line 1806 of yacc.c  */
#line 6627 "parser.y"
    { (yyval) = cb_zero; }
    break;

  case 1360:

/* Line 1806 of yacc.c  */
#line 6635 "parser.y"
    { (yyval) = cb_build_identifier ((yyvsp[(1) - (1)])); }
    break;

  case 1361:

/* Line 1806 of yacc.c  */
#line 6639 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1362:

/* Line 1806 of yacc.c  */
#line 6640 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); }
    break;

  case 1363:

/* Line 1806 of yacc.c  */
#line 6641 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); }
    break;

  case 1364:

/* Line 1806 of yacc.c  */
#line 6642 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); }
    break;

  case 1365:

/* Line 1806 of yacc.c  */
#line 6646 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1366:

/* Line 1806 of yacc.c  */
#line 6647 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); CB_REFERENCE ((yyvsp[(1) - (3)]))->chain = (yyvsp[(3) - (3)]); }
    break;

  case 1367:

/* Line 1806 of yacc.c  */
#line 6652 "parser.y"
    {
	(yyval) = (yyvsp[(0) - (3)]);
	CB_REFERENCE ((yyvsp[(0) - (3)]))->subs = cb_list_reverse ((yyvsp[(2) - (3)]));
  }
    break;

  case 1368:

/* Line 1806 of yacc.c  */
#line 6660 "parser.y"
    {
        CB_REFERENCE ((yyvsp[(0) - (4)]))->value = CB_TREE(cb_field ((yyvsp[(0) - (4)])));
        if(  cb_tree_category((yyvsp[(0) - (4)])) == CB_CATEGORY_NATIONAL || cb_tree_category((yyvsp[(0) - (4)])) == CB_CATEGORY_NATIONAL_EDITED )
	{
	    (yyvsp[(2) - (4)]) = cb_build_binary_op((yyvsp[(2) - (4)]),'*',cb_int2); 
            (yyvsp[(2) - (4)]) = cb_build_binary_op((yyvsp[(2) - (4)]),'-',cb_int1);
	    
               
	}
	else
	{
	      CB_TREE ((yyvsp[(0) - (4)]))->category = CB_CATEGORY_ALPHANUMERIC;
	}
	CB_REFERENCE ((yyvsp[(0) - (4)]))->offset = (yyvsp[(2) - (4)]);
  }
    break;

  case 1369:

/* Line 1806 of yacc.c  */
#line 6676 "parser.y"
    {
       CB_REFERENCE ((yyvsp[(0) - (5)]))->value = CB_TREE(cb_field ((yyvsp[(0) - (5)])));
        if( cb_tree_category((yyvsp[(0) - (5)])) == CB_CATEGORY_NATIONAL ||  cb_tree_category((yyvsp[(0) - (5)])) == CB_CATEGORY_NATIONAL_EDITED)
	{
	  
               (yyvsp[(2) - (5)]) = cb_build_binary_op((yyvsp[(2) - (5)]),'*',cb_int2); 
               (yyvsp[(2) - (5)]) = cb_build_binary_op((yyvsp[(2) - (5)]),'-',cb_int1);
	    
               (yyvsp[(4) - (5)]) = cb_build_binary_op((yyvsp[(4) - (5)]),'*',cb_int2);             
             
	}
	else
	{
	      CB_TREE((yyvsp[(0) - (5)]))->category = CB_CATEGORY_ALPHANUMERIC;
	}
        
	        CB_REFERENCE ((yyvsp[(0) - (5)]))->offset = (yyvsp[(2) - (5)]);
	        CB_REFERENCE ((yyvsp[(0) - (5)]))->length = (yyvsp[(4) - (5)]);
  }
    break;

  case 1370:

/* Line 1806 of yacc.c  */
#line 6703 "parser.y"
    {
	if (cb_tree_category ((yyvsp[(1) - (1)])) != CB_CATEGORY_NUMERIC) {
		cb_error (_("Integer value expected"));
	} else if (CB_LITERAL ((yyvsp[(1) - (1)]))->sign < 0 || CB_LITERAL ((yyvsp[(1) - (1)]))->scale) {
		cb_error (_("Integer value expected"));
	}
	(yyval) = (yyvsp[(1) - (1)]);
  }
    break;

  case 1371:

/* Line 1806 of yacc.c  */
#line 6714 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1372:

/* Line 1806 of yacc.c  */
#line 6716 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (2)]);
	if (CB_LITERAL_P ((yyvsp[(2) - (2)]))) {
		CB_LITERAL ((yyvsp[(2) - (2)]))->all = 1;
	}
  }
    break;

  case 1373:

/* Line 1806 of yacc.c  */
#line 6725 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1374:

/* Line 1806 of yacc.c  */
#line 6726 "parser.y"
    { (yyval) = cb_concat_literals ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 1375:

/* Line 1806 of yacc.c  */
#line 6730 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1376:

/* Line 1806 of yacc.c  */
#line 6731 "parser.y"
    { (yyval) = cb_space; }
    break;

  case 1377:

/* Line 1806 of yacc.c  */
#line 6732 "parser.y"
    { (yyval) = cb_zero; }
    break;

  case 1378:

/* Line 1806 of yacc.c  */
#line 6733 "parser.y"
    { (yyval) = cb_quote; }
    break;

  case 1379:

/* Line 1806 of yacc.c  */
#line 6734 "parser.y"
    { (yyval) = cb_high; }
    break;

  case 1380:

/* Line 1806 of yacc.c  */
#line 6735 "parser.y"
    { (yyval) = cb_low; }
    break;

  case 1381:

/* Line 1806 of yacc.c  */
#line 6736 "parser.y"
    { (yyval) = cb_null; }
    break;

  case 1382:

/* Line 1806 of yacc.c  */
#line 6745 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  }
    break;

  case 1383:

/* Line 1806 of yacc.c  */
#line 6749 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  }
    break;

  case 1384:

/* Line 1806 of yacc.c  */
#line 6753 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  }
    break;

  case 1385:

/* Line 1806 of yacc.c  */
#line 6757 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  }
    break;

  case 1386:

/* Line 1806 of yacc.c  */
#line 6761 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  }
    break;

  case 1387:

/* Line 1806 of yacc.c  */
#line 6765 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  }
    break;

  case 1388:

/* Line 1806 of yacc.c  */
#line 6769 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  }
    break;

  case 1389:

/* Line 1806 of yacc.c  */
#line 6773 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  }
    break;

  case 1390:

/* Line 1806 of yacc.c  */
#line 6777 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  }
    break;

  case 1391:

/* Line 1806 of yacc.c  */
#line 6781 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), NULL);
  }
    break;

  case 1392:

/* Line 1806 of yacc.c  */
#line 6785 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  }
    break;

  case 1393:

/* Line 1806 of yacc.c  */
#line 6789 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), NULL);
  }
    break;

  case 1394:

/* Line 1806 of yacc.c  */
#line 6795 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1395:

/* Line 1806 of yacc.c  */
#line 6796 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (4)]), NULL); }
    break;

  case 1396:

/* Line 1806 of yacc.c  */
#line 6797 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); }
    break;

  case 1397:

/* Line 1806 of yacc.c  */
#line 6801 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1398:

/* Line 1806 of yacc.c  */
#line 6802 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 1399:

/* Line 1806 of yacc.c  */
#line 6806 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1400:

/* Line 1806 of yacc.c  */
#line 6807 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 1401:

/* Line 1806 of yacc.c  */
#line 6813 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_int0);
  }
    break;

  case 1402:

/* Line 1806 of yacc.c  */
#line 6820 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int1);
  }
    break;

  case 1403:

/* Line 1806 of yacc.c  */
#line 6827 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int2);
  }
    break;

  case 1404:

/* Line 1806 of yacc.c  */
#line 6837 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  }
    break;

  case 1405:

/* Line 1806 of yacc.c  */
#line 6844 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, (yyvsp[(3) - (3)]));
  }
    break;

  case 1406:

/* Line 1806 of yacc.c  */
#line 6854 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  }
    break;

  case 1407:

/* Line 1806 of yacc.c  */
#line 6861 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_ref ((yyvsp[(3) - (3)])));
  }
    break;

  case 1408:

/* Line 1806 of yacc.c  */
#line 6874 "parser.y"
    {
	non_const_word = 1;
  }
    break;

  case 1409:

/* Line 1806 of yacc.c  */
#line 6884 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 1410:

/* Line 1806 of yacc.c  */
#line 6885 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1411:

/* Line 1806 of yacc.c  */
#line 6889 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 1412:

/* Line 1806 of yacc.c  */
#line 6890 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1413:

/* Line 1806 of yacc.c  */
#line 6894 "parser.y"
    { (yyval) = NULL; }
    break;

  case 1414:

/* Line 1806 of yacc.c  */
#line 6895 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1415:

/* Line 1806 of yacc.c  */
#line 6899 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 1416:

/* Line 1806 of yacc.c  */
#line 6900 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1417:

/* Line 1806 of yacc.c  */
#line 6901 "parser.y"
    { (yyval) = cb_int2; }
    break;

  case 1418:

/* Line 1806 of yacc.c  */
#line 6905 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 1419:

/* Line 1806 of yacc.c  */
#line 6906 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1420:

/* Line 1806 of yacc.c  */
#line 6910 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 1421:

/* Line 1806 of yacc.c  */
#line 6911 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1422:

/* Line 1806 of yacc.c  */
#line 6915 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 1423:

/* Line 1806 of yacc.c  */
#line 6916 "parser.y"
    { (yyval) = cb_int1; }
    break;

  case 1424:

/* Line 1806 of yacc.c  */
#line 6920 "parser.y"
    { (yyval) = cb_int0; }
    break;

  case 1425:

/* Line 1806 of yacc.c  */
#line 6921 "parser.y"
    { (yyval) = cb_int1; }
    break;



/* Line 1806 of yacc.c  */
#line 14010 "parser.c"
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



/* Line 2067 of yacc.c  */
#line 6977 "parser.y"


