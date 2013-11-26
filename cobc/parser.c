
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
#define YYLAST   5272

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  453
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  692
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1540
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2270

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
    1829,  1830,  1835,  1840,  1845,  1849,  1853,  1857,  1862,  1866,
    1871,  1875,  1879,  1883,  1888,  1894,  1898,  1903,  1907,  1911,
    1912,  1916,  1920,  1923,  1926,  1929,  1933,  1937,  1941,  1942,
    1945,  1947,  1950,  1952,  1954,  1956,  1958,  1960,  1962,  1964,
    1968,  1972,  1976,  1980,  1982,  1984,  1986,  1988,  1990,  1992,
    1993,  1995,  1996,  2001,  2006,  2012,  2019,  2020,  2023,  2024,
    2026,  2027,  2031,  2035,  2041,  2042,  2045,  2048,  2049,  2055,
    2056,  2059,  2060,  2069,  2070,  2071,  2075,  2077,  2080,  2083,
    2087,  2088,  2091,  2094,  2097,  2098,  2101,  2104,  2105,  2106,
    2110,  2111,  2112,  2116,  2117,  2119,  2120,  2124,  2125,  2128,
    2129,  2133,  2134,  2138,  2139,  2141,  2145,  2149,  2152,  2154,
    2156,  2157,  2162,  2167,  2168,  2170,  2172,  2174,  2176,  2178,
    2179,  2186,  2187,  2189,  2190,  2195,  2199,  2203,  2207,  2211,
    2216,  2223,  2230,  2237,  2244,  2245,  2248,  2251,  2253,  2256,
    2258,  2260,  2263,  2266,  2268,  2270,  2272,  2274,  2276,  2280,
    2284,  2288,  2292,  2294,  2296,  2297,  2299,  2300,  2305,  2310,
    2317,  2324,  2333,  2342,  2343,  2345,  2346,  2351,  2352,  2358,
    2360,  2364,  2366,  2368,  2370,  2373,  2375,  2378,  2379,  2383,
    2384,  2385,  2389,  2392,  2396,  2398,  2402,  2405,  2407,  2409,
    2411,  2412,  2415,  2416,  2418,  2419,  2423,  2424,  2426,  2428,
    2431,  2433,  2435,  2436,  2440,  2441,  2445,  2446,  2452,  2453,
    2457,  2458,  2461,  2462,  2463,  2472,  2476,  2477,  2478,  2482,
    2483,  2485,  2486,  2494,  2495,  2498,  2499,  2503,  2507,  2508,
    2511,  2513,  2516,  2521,  2523,  2525,  2527,  2529,  2531,  2533,
    2535,  2536,  2538,  2539,  2543,  2544,  2549,  2551,  2553,  2555,
    2557,  2560,  2562,  2564,  2566,  2567,  2571,  2573,  2576,  2579,
    2582,  2584,  2586,  2588,  2591,  2594,  2596,  2599,  2604,  2607,
    2608,  2610,  2612,  2614,  2616,  2621,  2627,  2628,  2633,  2634,
    2636,  2637,  2641,  2642,  2646,  2650,  2655,  2656,  2661,  2666,
    2673,  2674,  2676,  2677,  2681,  2682,  2688,  2690,  2692,  2694,
    2696,  2697,  2701,  2702,  2706,  2709,  2710,  2714,  2717,  2718,
    2723,  2726,  2727,  2729,  2731,  2735,  2736,  2738,  2741,  2745,
    2749,  2750,  2754,  2756,  2760,  2768,  2769,  2780,  2781,  2784,
    2785,  2788,  2791,  2795,  2799,  2802,  2803,  2807,  2808,  2810,
    2812,  2813,  2815,  2816,  2821,  2822,  2830,  2831,  2833,  2834,
    2842,  2843,  2846,  2850,  2851,  2853,  2855,  2856,  2861,  2866,
    2867,  2875,  2876,  2879,  2880,  2881,  2886,  2888,  2891,  2892,
    2897,  2898,  2900,  2901,  2905,  2907,  2909,  2911,  2913,  2915,
    2920,  2925,  2929,  2934,  2936,  2938,  2940,  2943,  2947,  2949,
    2952,  2956,  2960,  2961,  2965,  2966,  2974,  2975,  2981,  2982,
    2985,  2986,  2989,  2990,  2994,  2995,  2998,  3003,  3004,  3007,
    3012,  3013,  3014,  3022,  3023,  3028,  3031,  3034,  3037,  3040,
    3043,  3044,  3046,  3047,  3052,  3055,  3056,  3059,  3062,  3063,
    3072,  3074,  3077,  3079,  3083,  3087,  3088,  3092,  3093,  3095,
    3096,  3101,  3106,  3113,  3120,  3121,  3123,  3126,  3127,  3129,
    3130,  3134,  3135,  3143,  3144,  3149,  3150,  3152,  3154,  3155,
    3165,  3166,  3170,  3172,  3176,  3179,  3182,  3185,  3189,  3190,
    3194,  3195,  3199,  3200,  3204,  3205,  3207,  3209,  3211,  3213,
    3222,  3223,  3225,  3227,  3229,  3231,  3233,  3235,  3236,  3238,
    3239,  3241,  3243,  3245,  3247,  3249,  3251,  3253,  3254,  3256,
    3262,  3264,  3267,  3273,  3274,  3283,  3284,  3287,  3288,  3293,
    3297,  3301,  3303,  3305,  3306,  3308,  3310,  3311,  3313,  3316,
    3319,  3320,  3321,  3325,  3326,  3327,  3331,  3334,  3335,  3336,
    3340,  3341,  3342,  3346,  3349,  3350,  3351,  3355,  3356,  3357,
    3361,  3363,  3365,  3368,  3369,  3373,  3374,  3378,  3380,  3382,
    3385,  3386,  3390,  3391,  3395,  3396,  3398,  3400,  3402,  3405,
    3406,  3410,  3411,  3415,  3416,  3420,  3422,  3424,  3425,  3428,
    3431,  3434,  3437,  3440,  3443,  3446,  3449,  3452,  3455,  3458,
    3461,  3464,  3467,  3468,  3471,  3474,  3477,  3480,  3483,  3486,
    3489,  3492,  3495,  3498,  3501,  3504,  3507,  3510,  3513,  3516,
    3519,  3522,  3525,  3528,  3531,  3534,  3537,  3540,  3543,  3545,
    3548,  3550,  3552,  3555,  3557,  3560,  3562,  3568,  3570,  3576,
    3578,  3582,  3583,  3585,  3587,  3589,  3593,  3597,  3601,  3605,
    3608,  3611,  3615,  3619,  3621,  3625,  3627,  3630,  3633,  3635,
    3637,  3639,  3642,  3644,  3646,  3649,  3651,  3652,  3655,  3657,
    3659,  3661,  3665,  3667,  3669,  3672,  3674,  3675,  3677,  3679,
    3681,  3683,  3685,  3688,  3690,  3694,  3696,  3699,  3701,  3705,
    3709,  3713,  3718,  3722,  3724,  3726,  3728,  3730,  3734,  3738,
    3742,  3744,  3746,  3748,  3750,  3752,  3754,  3756,  3758,  3760,
    3762,  3764,  3766,  3768,  3770,  3772,  3774,  3776,  3778,  3780,
    3782,  3784,  3787,  3790,  3794,  3796,  3800,  3804,  3809,  3815,
    3817,  3819,  3822,  3824,  3828,  3830,  3832,  3834,  3836,  3838,
    3840,  3842,  3845,  3848,  3854,  3860,  3866,  3872,  3878,  3884,
    3890,  3895,  3901,  3904,  3905,  3910,  3916,  3917,  3921,  3922,
    3924,  3926,  3930,  3934,  3936,  3940,  3942,  3946,  3947,  3948,
    3950,  3951,  3953,  3954,  3956,  3957,  3959,  3961,  3962,  3964,
    3965,  3967,  3968,  3970,  3971,  3974,  3976,  3978,  3981,  3984,
    3987,  3989,  3992,  3994,  3995,  3997,  3998,  4000,  4001,  4003,
    4004,  4006,  4007,  4009,  4010,  4012,  4013,  4015,  4016,  4018,
    4019,  4021,  4022,  4024,  4025,  4027,  4028,  4030,  4031,  4033,
    4034,  4036,  4037,  4039,  4040,  4042,  4043,  4045,  4046,  4048,
    4050,  4051,  4053,  4054,  4056,  4058,  4059,  4061,  4062,  4064,
    4065,  4067,  4068,  4070,  4071,  4073,  4074,  4076,  4079,  4080,
    4082,  4083,  4085,  4086,  4088,  4089,  4091,  4092,  4094,  4095,
    4097,  4098,  4100,  4103,  4104,  4106,  4107,  4109,  4110,  4112,
    4113,  4115,  4116,  4118,  4119,  4121,  4122,  4124,  4125,  4127,
    4128
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
    1121,  1119,  1058,    -1,   310,  1121,  1119,  1058,   550,   547,
      -1,   317,  1121,  1119,  1058,    -1,   330,  1079,  1106,    -1,
     357,  1144,   566,    -1,     9,  1129,    -1,   252,  1129,    -1,
     309,   272,    -1,    -1,   210,   445,   568,    -1,    -1,   569,
     445,    -1,   570,    -1,   569,   570,    -1,   571,    -1,   573,
      -1,   341,   572,  1106,  1116,  1049,    -1,    -1,   310,    -1,
     365,    -1,   366,    -1,   243,  1115,  1138,  1113,   574,    -1,
     575,    -1,   574,   575,    -1,  1050,   576,    -1,    -1,   292,
    1079,    -1,    -1,    97,   115,   445,   578,   609,   654,   656,
     658,   699,    -1,    -1,    -1,   396,   347,   445,   579,   581,
      -1,    -1,   584,   580,   583,    -1,    -1,   581,   582,    -1,
     584,   585,   611,    -1,   585,   611,    -1,   583,   582,    -1,
     163,    -1,   345,    -1,    -1,  1050,   586,   587,   445,    -1,
      -1,   587,   588,    -1,  1119,   162,    -1,  1119,   182,    -1,
     589,    -1,   591,    -1,   595,    -1,   597,    -1,   599,    -1,
     600,    -1,   606,    -1,   607,    -1,   608,    -1,    46,  1113,
    1079,   594,   590,    -1,    -1,   312,    -1,    55,    -1,   310,
    1113,  1079,  1112,    -1,   310,  1113,  1079,   394,  1079,  1112,
      -1,   310,  1119,   426,  1118,  1136,   593,   594,  1112,   592,
      -1,    -1,   109,  1127,  1058,    -1,    -1,  1117,  1079,    -1,
      -1,   394,  1079,    -1,   213,  1100,   596,    -1,   371,    -1,
     270,    -1,   425,   268,   432,  1119,   598,    -1,   425,   268,
     165,  1119,   598,    -1,   228,    -1,  1076,    -1,    97,  1100,
    1057,    -1,   223,  1119,  1060,  1123,   601,    -1,    -1,   601,
     602,    -1,   603,    -1,   604,    -1,   605,    -1,  1144,   169,
    1108,  1060,  1123,    -1,  1108,   400,  1060,  1123,    -1,  1108,
      47,  1060,    -1,   311,  1124,  1119,   432,    -1,    60,  1119,
     432,    -1,   323,  1119,   698,    -1,   325,  1105,   698,    -1,
      -1,    -1,   434,   347,   445,   610,   611,    -1,    -1,   612,
      -1,    -1,   613,   614,    -1,  1090,   615,   445,    -1,   614,
    1090,   615,   445,    -1,   614,   445,    -1,   622,    -1,    -1,
     617,   618,   616,   623,    -1,   432,    -1,    -1,   166,    -1,
     432,    -1,   432,    -1,    -1,  1119,   182,    -1,  1080,    -1,
     219,  1126,  1075,    -1,    49,  1126,  1075,    -1,   617,   619,
      81,   620,  1107,   621,    -1,    -1,   623,   624,    -1,   625,
      -1,   626,    -1,   628,    -1,   629,    -1,   630,    -1,   632,
      -1,   633,    -1,   642,    -1,   643,    -1,   645,    -1,   646,
      -1,   647,    -1,   652,    -1,   653,    -1,   314,  1075,    -1,
    1119,   162,   627,    -1,    -1,    26,   228,    -1,  1119,   182,
      -1,   289,    -1,   631,    -1,   422,  1119,   631,    -1,    36,
      -1,    71,    -1,    73,    -1,    74,    -1,    75,    -1,    76,
      -1,    77,    -1,    78,    -1,   113,    -1,   195,    -1,   282,
      -1,   291,    -1,   304,    -1,   362,    -1,   360,    -1,   361,
      -1,   411,    -1,   409,    -1,   410,    -1,    38,   359,    -1,
      38,   408,    -1,    38,    -1,    41,   359,    -1,    41,   408,
      -1,    41,    -1,    40,   359,    -1,    40,   408,    -1,    40,
      -1,    39,   359,    -1,    39,   408,    -1,    39,    -1,    37,
     359,    -1,    37,   408,    -1,    37,    -1,   245,    -1,  1135,
     217,  1098,    -1,  1135,   401,  1098,    -1,   267,  1079,   634,
    1141,   635,   636,   639,    -1,    -1,   394,  1079,    -1,    -1,
     109,  1127,  1058,    -1,   637,    -1,    -1,   637,   638,  1121,
    1119,  1057,    -1,    27,    -1,   110,    -1,    -1,   196,  1110,
     640,    -1,   641,    -1,   640,   641,    -1,   432,    -1,   211,
    1132,    -1,   384,   644,    -1,    -1,   218,    -1,   337,    -1,
      42,  1143,   438,    -1,    33,    -1,    -1,   425,  1120,   649,
     648,  1143,  1133,  1142,   651,    -1,   650,    -1,   649,   650,
      -1,  1080,    -1,  1080,   391,  1080,    -1,    -1,   395,  1119,
    1080,    -1,   321,  1076,    -1,   321,  1076,   391,  1076,    -1,
      21,   219,    -1,    -1,    -1,   231,   347,   445,   655,   611,
      -1,    -1,    -1,   227,   347,   445,   657,   611,    -1,    -1,
      -1,   323,   347,   445,   659,   660,    -1,    -1,   661,    -1,
     662,    -1,   661,   662,    -1,   308,   698,   663,   445,   677,
      -1,    -1,   663,   664,    -1,  1119,   182,    -1,    59,  1119,
    1071,    -1,   665,    -1,   669,    -1,    85,   666,    -1,    86,
     666,    -1,   667,   668,    -1,    -1,   167,    -1,  1074,    -1,
     668,  1074,    -1,   284,  1120,   675,   670,   671,   672,   673,
     674,    -1,    -1,   187,  1119,  1079,    -1,    -1,   168,   111,
    1119,  1079,    -1,    -1,   214,    88,  1119,  1079,    -1,    -1,
     215,  1119,  1079,    -1,    -1,   169,  1119,  1079,    -1,  1079,
      -1,  1079,   676,  1079,    65,    -1,  1079,   676,    -1,   225,
      -1,   226,    -1,    -1,   677,   678,    -1,   617,   618,   679,
     445,    -1,    -1,   679,   680,    -1,   681,    -1,   683,    -1,
     690,    -1,   629,    -1,   630,    -1,   632,    -1,   642,    -1,
     684,    -1,   645,    -1,   695,    -1,   685,    -1,   647,    -1,
     688,    -1,   696,    -1,   633,    -1,   689,    -1,   404,  1119,
     682,    -1,   327,    -1,   286,    -1,    88,    -1,   111,    -1,
      87,    -1,   285,    -1,   326,    -1,   250,   186,  1119,  1079,
      -1,    64,  1125,  1119,  1079,    -1,    64,   262,    -1,    65,
      -1,   686,    -1,   685,   686,    -1,   381,  1126,   687,    -1,
    1058,    -1,   294,   428,  1030,    -1,   426,  1074,   174,  1065,
      48,  1065,    -1,   691,   692,    -1,   225,   694,  1120,    -1,
     226,  1105,    -1,   693,    -1,   692,   693,    -1,   290,  1079,
      -1,  1079,    -1,   250,   284,    -1,    -1,   261,    -1,   262,
      -1,   367,  1119,  1074,  1097,    -1,   186,   697,    -1,    -1,
     197,    -1,   432,    -1,    -1,    -1,    -1,   342,   347,   445,
     700,   701,   702,    -1,    -1,   703,    -1,   704,    -1,   703,
     704,    -1,   622,    -1,    -1,   617,   618,   705,   706,   445,
      -1,    -1,   706,   707,    -1,    43,    -1,    44,    -1,    35,
      -1,    45,    -1,   153,   148,    -1,   153,   150,    -1,   188,
      -1,   234,    -1,   334,    -1,   405,    -1,   281,    -1,    30,
      -1,   348,    -1,   329,    -1,   175,    -1,   305,    -1,   225,
    1125,  1119,   708,  1073,    -1,    64,  1125,  1119,   709,  1073,
      -1,   171,  1119,  1073,    -1,    32,  1119,  1073,    -1,   630,
      -1,   645,    -1,   642,    -1,   632,    -1,   647,    -1,   629,
      -1,   710,    -1,   424,  1074,    -1,   174,  1072,    -1,   394,
    1074,    -1,    -1,   290,    -1,   439,    -1,   239,    -1,   440,
      -1,    -1,   290,    -1,   439,    -1,   239,    -1,   440,    -1,
     267,  1079,  1141,    -1,    -1,    -1,    -1,   298,   115,   714,
     722,   445,   712,   723,   713,   725,    -1,    -1,    -1,   424,
     715,   717,    -1,    -1,    53,   716,   717,    -1,   718,    -1,
     717,   718,    -1,   719,   720,   721,   432,    -1,    -1,  1110,
     316,    -1,  1110,   425,    -1,    -1,   363,  1119,    30,    -1,
     363,  1119,   105,    -1,   408,   363,  1119,  1079,    -1,   363,
    1119,  1079,    -1,    -1,   274,    -1,    -1,   332,   432,    -1,
      -1,    -1,   104,   445,   724,   725,   121,   104,   445,    -1,
      -1,   725,   726,    -1,   727,    -1,   728,    -1,   729,    -1,
     735,   445,    -1,     1,   445,    -1,   730,   347,   731,   445,
      -1,   432,   445,    -1,   730,    -1,   432,    -1,    -1,   228,
      -1,    -1,    -1,   733,   734,   735,    -1,    -1,   735,   736,
      -1,   737,    -1,   747,    -1,   752,    -1,   756,    -1,   759,
      -1,   772,    -1,   775,    -1,   785,    -1,   780,    -1,   786,
      -1,   787,    -1,   790,    -1,   797,    -1,   801,    -1,   803,
      -1,   818,    -1,   821,    -1,   823,    -1,   825,    -1,   828,
      -1,   830,    -1,   836,    -1,   845,    -1,   847,    -1,   864,
      -1,   866,    -1,   869,    -1,   873,    -1,   879,    -1,   889,
      -1,   896,    -1,   898,    -1,   901,    -1,   905,    -1,   906,
      -1,   917,    -1,   928,    -1,   938,    -1,   944,    -1,   947,
      -1,   953,    -1,   957,    -1,   959,    -1,   961,    -1,   963,
      -1,   966,    -1,   977,    -1,   990,    -1,   251,    -1,    -1,
       3,   738,   739,   746,    -1,  1074,   740,   743,   997,    -1,
    1074,   174,   155,   212,    -1,  1074,   174,   226,    -1,  1074,
     174,    65,    -1,  1074,   174,    98,    -1,  1074,   174,    98,
     437,    -1,  1074,   174,    99,    -1,  1074,   174,    99,   436,
      -1,  1074,   174,   100,    -1,  1074,   174,   392,    -1,  1074,
     174,    67,    -1,  1074,   174,   147,   997,    -1,  1074,   174,
     145,  1069,   997,    -1,  1074,   174,    24,    -1,  1074,   174,
      25,   997,    -1,  1074,   174,  1052,    -1,  1074,   174,   432,
      -1,    -1,  1108,   741,   742,    -1,  1108,   742,   741,    -1,
    1108,   741,    -1,  1108,   742,    -1,    29,  1069,    -1,   225,
    1125,  1071,    -1,    64,  1125,  1071,    -1,   292,  1125,  1071,
      -1,    -1,   431,   744,    -1,   745,    -1,   744,   745,    -1,
      35,    -1,    45,    -1,   188,    -1,   234,    -1,   334,    -1,
     405,    -1,   281,    -1,   171,  1119,  1073,    -1,    32,  1119,
    1073,    -1,   344,   414,  1029,    -1,   344,   116,  1029,    -1,
      30,    -1,   175,    -1,   329,    -1,   348,    -1,   415,    -1,
     305,    -1,    -1,   122,    -1,    -1,     5,   748,   749,   751,
      -1,  1064,   394,  1045,  1003,    -1,  1064,   750,   181,  1045,
    1003,    -1,    90,  1074,   394,  1074,  1097,  1003,    -1,    -1,
     394,  1065,    -1,    -1,   123,    -1,    -1,    10,   753,   754,
      -1,   432,  1093,   755,    -1,  1031,    55,  1093,   332,  1063,
      -1,    -1,   332,  1063,    -1,    18,   757,    -1,    -1,   757,
    1054,   394,   758,  1054,    -1,    -1,   300,   394,    -1,    -1,
      50,   760,  1072,   761,   766,   767,   769,   771,    -1,    -1,
      -1,   424,   762,   763,    -1,   764,    -1,   763,   764,    -1,
     765,   270,    -1,   765,   720,  1065,    -1,    -1,  1110,   316,
      -1,  1110,    83,    -1,  1110,   425,    -1,    -1,   332,  1074,
      -1,   181,  1074,    -1,    -1,    -1,   984,   768,   732,    -1,
      -1,    -1,   985,   770,   732,    -1,    -1,   124,    -1,    -1,
      51,   773,   774,    -1,    -1,   774,  1071,    -1,    -1,    58,
     776,   777,    -1,    -1,   777,  1050,   778,    -1,    -1,   779,
      -1,   779,  1116,   320,    -1,  1144,   252,   335,    -1,  1144,
     232,    -1,   315,    -1,   406,    -1,    -1,    72,   781,   782,
     783,    -1,  1045,   784,  1031,  1003,    -1,    -1,   125,    -1,
     446,    -1,   151,    -1,    69,    -1,    84,    -1,    -1,   106,
     788,  1050,  1131,  1023,   789,    -1,    -1,   126,    -1,    -1,
     113,   791,   792,   796,    -1,  1071,   419,   998,    -1,  1071,
     420,   998,    -1,  1071,   417,   998,    -1,  1071,   418,   998,
      -1,  1064,   740,   793,   998,    -1,  1064,   740,   416,  1052,
     793,   998,    -1,  1064,   740,   416,   432,   793,   998,    -1,
    1064,   740,   416,   296,   793,   998,    -1,  1064,   740,   416,
      92,   793,   998,    -1,    -1,  1144,   260,    -1,   431,   794,
      -1,   795,    -1,   794,   795,    -1,    35,    -1,    45,    -1,
     153,   148,    -1,   153,   150,    -1,   188,    -1,   234,    -1,
     334,    -1,   405,    -1,   281,    -1,   171,  1119,  1073,    -1,
      32,  1119,  1073,    -1,   344,   414,  1029,    -1,   344,   116,
    1029,    -1,    43,    -1,    44,    -1,    -1,   127,    -1,    -1,
     114,   798,   799,   800,    -1,  1065,   204,  1045,  1003,    -1,
    1065,   204,  1065,   181,  1045,  1003,    -1,  1065,    48,  1065,
     181,  1045,  1003,    -1,  1065,   204,  1065,   181,  1046,   319,
    1046,  1003,    -1,  1065,    48,  1065,   181,  1046,   319,  1046,
    1003,    -1,    -1,   128,    -1,    -1,   144,   802,   228,   761,
      -1,    -1,   156,   804,   805,   807,   817,    -1,   806,    -1,
     805,  1104,   806,    -1,  1031,    -1,   399,    -1,   395,    -1,
     808,   811,    -1,   809,    -1,   808,   809,    -1,    -1,   813,
     810,   732,    -1,    -1,    -1,   430,   812,   732,    -1,   428,
     814,    -1,   813,   428,   814,    -1,   815,    -1,   814,  1104,
     815,    -1,  1032,   816,    -1,    21,    -1,   399,    -1,   395,
      -1,    -1,   391,  1031,    -1,    -1,   129,    -1,    -1,   160,
     819,   820,    -1,    -1,   301,    -1,   288,    -1,   288,    96,
      -1,   347,    -1,   287,    -1,    -1,   173,   822,  1062,    -1,
      -1,   180,   824,  1074,    -1,    -1,   183,  1142,   826,  1053,
     827,    -1,    -1,   109,  1127,  1074,    -1,    -1,   184,   829,
      -1,    -1,    -1,   191,   831,  1030,  1140,   832,   732,   833,
     835,    -1,   191,     1,   131,    -1,    -1,    -1,   120,   834,
     732,    -1,    -1,   131,    -1,    -1,   198,   837,  1062,   838,
     839,   840,   844,    -1,    -1,  1144,   166,    -1,    -1,     9,
    1142,   425,    -1,   843,  1142,   425,    -1,    -1,   322,   841,
      -1,   842,    -1,   841,   842,    -1,   843,  1114,    48,  1065,
      -1,    12,    -1,    15,    -1,   263,    -1,    16,    -1,   264,
      -1,   245,    -1,   246,    -1,    -1,   105,    -1,    -1,   200,
     846,   668,    -1,    -1,   203,   848,   849,   850,    -1,  1074,
      -1,  1080,    -1,  1083,    -1,   851,    -1,   850,   851,    -1,
     852,    -1,   856,    -1,   861,    -1,    -1,   385,   853,   854,
      -1,   855,    -1,   854,   855,    -1,  1069,   170,    -1,    55,
     862,    -1,     9,    -1,   217,    -1,   401,    -1,  1069,   862,
      -1,   322,   857,    -1,   858,    -1,   857,   858,    -1,    55,
      48,  1069,   862,    -1,   859,   860,    -1,    -1,     9,    -1,
     217,    -1,   168,    -1,   401,    -1,  1069,    48,  1070,   862,
      -1,    89,  1069,   394,  1070,   862,    -1,    -1,   862,   994,
     863,  1065,    -1,    -1,   397,    -1,    -1,   238,   865,   930,
      -1,    -1,   242,   867,   868,    -1,  1065,   394,  1062,    -1,
      90,  1065,   394,  1062,    -1,    -1,   244,   870,   871,   872,
      -1,  1065,    48,  1045,  1003,    -1,  1065,    48,  1065,   181,
    1045,  1003,    -1,    -1,   132,    -1,    -1,   273,   874,   875,
      -1,    -1,   875,   876,   877,  1049,   878,    -1,   201,    -1,
     279,    -1,   209,    -1,   161,    -1,    -1,   357,  1144,   566,
      -1,    -1,  1144,   252,   335,    -1,  1144,   232,    -1,    -1,
     288,   880,   881,    -1,   884,   885,    -1,    -1,   885,   882,
     732,   883,    -1,   885,   133,    -1,    -1,   133,    -1,  1054,
      -1,  1054,   391,  1054,    -1,    -1,   172,    -1,  1072,   393,
      -1,   886,   413,  1030,    -1,   886,   426,   887,    -1,    -1,
    1144,   388,   994,    -1,   888,    -1,   887,     8,   888,    -1,
    1074,   174,  1065,    48,  1065,   413,  1030,    -1,    -1,   309,
     890,  1050,  1094,  1131,   891,   892,   893,   894,   895,    -1,
      -1,   204,  1074,    -1,    -1,   193,   232,    -1,  1144,   232,
      -1,  1144,   252,   232,    -1,  1144,   192,   232,    -1,  1144,
     427,    -1,    -1,   212,  1119,   668,    -1,    -1,  1013,    -1,
    1024,    -1,    -1,   135,    -1,    -1,   318,   897,  1047,   992,
      -1,    -1,   331,   899,  1050,  1131,   891,  1013,   900,    -1,
      -1,   136,    -1,    -1,   336,   902,  1047,   992,   903,  1023,
     904,    -1,    -1,  1144,   232,    -1,  1144,   252,   232,    -1,
      -1,   137,    -1,   338,    -1,    -1,   346,   907,   908,   916,
      -1,  1048,   910,   911,   913,    -1,    -1,     9,  1048,   911,
     428,  1031,   909,   732,    -1,    -1,   426,  1074,    -1,    -1,
      -1,  1108,   121,   912,   732,    -1,   914,    -1,   914,   913,
      -1,    -1,   428,  1030,   915,   732,    -1,    -1,   138,    -1,
      -1,   356,   918,   919,    -1,   920,    -1,   921,    -1,   922,
      -1,   924,    -1,   926,    -1,   145,  1069,   394,  1069,    -1,
    1062,   394,   144,  1068,    -1,  1062,   394,  1065,    -1,  1062,
     923,    48,  1065,    -1,   414,    -1,   116,    -1,   925,    -1,
     924,   925,    -1,  1051,   394,   507,    -1,   927,    -1,   926,
     927,    -1,  1062,   394,   399,    -1,  1062,   394,   395,    -1,
      -1,   365,   929,   930,    -1,    -1,  1076,   932,   934,   935,
     931,   936,   937,    -1,    -1,   932,  1127,   638,  1121,   933,
      -1,    -1,   933,  1076,    -1,    -1,  1101,  1128,    -1,    -1,
    1102,  1119,  1058,    -1,    -1,   424,  1049,    -1,   201,   298,
    1119,   884,    -1,    -1,   181,  1049,    -1,   279,   298,  1119,
     884,    -1,    -1,    -1,   374,   939,  1050,   940,   941,  1023,
     943,    -1,    -1,   212,  1119,   942,  1065,    -1,  1095,  1036,
      -1,  1095,  1037,    -1,  1095,  1038,    -1,  1095,  1039,    -1,
    1095,  1040,    -1,    -1,   139,    -1,    -1,   376,   340,   945,
     946,    -1,   376,   228,    -1,    -1,   332,  1065,    -1,   181,
    1065,    -1,    -1,   377,   948,   949,   204,  1074,   951,  1008,
     952,    -1,   950,    -1,   949,   950,    -1,  1065,    -1,   107,
    1110,   363,    -1,   107,  1110,  1065,    -1,    -1,  1144,   291,
    1074,    -1,    -1,   140,    -1,    -1,   380,   954,   955,   956,
      -1,  1064,   174,  1045,  1003,    -1,  1064,   174,  1065,   181,
    1045,  1003,    -1,    90,  1074,   174,  1074,  1097,  1003,    -1,
      -1,   141,    -1,   382,   958,    -1,    -1,   297,    -1,    -1,
     387,   960,   668,    -1,    -1,   402,   962,  1074,   174,  1069,
     394,  1070,    -1,    -1,   407,   964,  1050,   965,    -1,    -1,
     310,    -1,   312,    -1,    -1,   412,   967,  1074,   968,   971,
     951,   975,  1008,   976,    -1,    -1,   107,  1110,   969,    -1,
     970,    -1,   969,   275,   970,    -1,  1091,  1069,    -1,   204,
     972,    -1,   971,   972,    -1,  1074,   973,   974,    -1,    -1,
     108,  1118,  1074,    -1,    -1,    91,  1118,  1074,    -1,    -1,
     385,  1118,  1074,    -1,    -1,   142,    -1,   978,    -1,   987,
      -1,   989,    -1,   423,   979,   981,   982,   983,   986,  1127,
     980,    -1,    -1,   182,    -1,  1049,    -1,   201,    -1,   279,
      -1,   209,    -1,   161,    -1,    -1,     8,    -1,    -1,   371,
      -1,   158,    -1,   154,    -1,   158,    -1,   280,    -1,   256,
      -1,   258,    -1,    -1,   298,    -1,   423,  1116,   102,  1127,
     988,    -1,  1054,    -1,     9,   299,    -1,   423,   979,    34,
     324,  1074,    -1,    -1,   435,   991,  1047,   992,   903,   993,
     995,   996,    -1,    -1,   174,  1071,    -1,    -1,   994,  1103,
    1073,  1122,    -1,   994,  1103,  1052,    -1,   994,  1103,   284,
      -1,    34,    -1,     8,    -1,    -1,  1018,    -1,  1024,    -1,
      -1,   143,    -1,   999,  1001,    -1,   999,  1001,    -1,    -1,
      -1,   158,  1000,   732,    -1,    -1,    -1,   256,  1002,   732,
      -1,  1004,  1006,    -1,    -1,    -1,   364,  1005,   732,    -1,
      -1,    -1,   259,  1007,   732,    -1,  1009,  1011,    -1,    -1,
      -1,   280,  1010,   732,    -1,    -1,    -1,   258,  1012,   732,
      -1,  1014,    -1,  1016,    -1,  1014,  1016,    -1,    -1,   121,
    1015,   732,    -1,    -1,   254,  1017,   732,    -1,  1019,    -1,
    1021,    -1,  1019,  1021,    -1,    -1,   149,  1020,   732,    -1,
      -1,   255,  1022,   732,    -1,    -1,  1024,    -1,  1025,    -1,
    1027,    -1,  1025,  1027,    -1,    -1,   207,  1026,   732,    -1,
      -1,   257,  1028,   732,    -1,    -1,  1110,  1073,  1122,    -1,
    1031,    -1,  1032,    -1,    -1,  1033,  1034,    -1,  1034,   208,
      -1,  1035,  1065,    -1,  1034,   447,    -1,  1034,   270,    -1,
    1034,   263,    -1,  1034,    12,    -1,  1034,    13,    -1,  1034,
      14,    -1,  1034,    57,    -1,  1034,   293,    -1,  1034,   249,
      -1,  1034,   438,    -1,  1034,   253,    -1,    -1,  1035,   208,
      -1,  1035,   448,    -1,  1035,   439,    -1,  1035,   440,    -1,
    1035,   444,    -1,  1035,   253,    -1,  1034,   439,    -1,  1034,
     440,    -1,  1034,   441,    -1,  1034,   442,    -1,  1034,   444,
      -1,  1034,  1036,    -1,  1034,  1037,    -1,  1034,  1038,    -1,
    1034,  1039,    -1,  1034,  1040,    -1,  1034,   248,    -1,  1035,
    1036,    -1,  1035,  1037,    -1,  1035,  1038,    -1,  1035,  1039,
      -1,  1035,  1040,    -1,  1035,   248,    -1,  1034,    20,    -1,
    1034,   275,    -1,   446,    -1,   151,  1142,    -1,   152,    -1,
     449,    -1,   185,  1139,    -1,   450,    -1,   220,  1139,    -1,
     179,    -1,   185,  1139,   275,   151,  1142,    -1,   216,    -1,
     220,  1139,   275,   151,  1142,    -1,  1043,    -1,  1041,  1042,
    1043,    -1,    -1,    68,    -1,   351,    -1,  1066,    -1,  1043,
     439,  1043,    -1,  1043,   440,  1043,    -1,  1043,   441,  1043,
      -1,  1043,   442,  1043,    -1,   439,  1043,    -1,   440,  1043,
      -1,  1043,   444,  1043,    -1,   448,  1043,   447,    -1,   224,
      -1,   224,  1099,   432,    -1,  1046,    -1,  1045,  1046,    -1,
    1065,  1097,    -1,  1076,    -1,  1076,    -1,  1050,    -1,  1049,
    1050,    -1,   432,    -1,  1052,    -1,  1051,  1052,    -1,   240,
      -1,    -1,  1053,  1054,    -1,  1055,    -1,  1076,    -1,  1056,
      -1,  1056,  1099,  1056,    -1,   228,    -1,  1058,    -1,  1057,
    1058,    -1,  1076,    -1,    -1,  1058,    -1,  1058,    -1,   228,
      -1,   432,    -1,  1063,    -1,  1062,  1063,    -1,  1074,    -1,
       6,  1126,  1075,    -1,  1065,    -1,  1064,  1065,    -1,  1074,
      -1,   219,  1126,  1075,    -1,   219,  1126,  1081,    -1,   219,
    1126,  1083,    -1,     6,  1126,  1067,  1068,    -1,     6,  1126,
    1075,    -1,  1080,    -1,  1083,    -1,  1044,    -1,  1074,    -1,
     219,  1126,  1075,    -1,   219,  1126,  1081,    -1,   219,  1126,
    1083,    -1,  1081,    -1,  1083,    -1,  1044,    -1,   301,    -1,
     144,    -1,  1075,    -1,   228,    -1,  1074,    -1,  1081,    -1,
    1074,    -1,  1080,    -1,  1074,    -1,   228,    -1,  1074,    -1,
     228,    -1,  1083,    -1,  1074,    -1,  1079,    -1,   438,    -1,
    1075,    -1,  1076,    -1,  1076,  1077,    -1,  1076,  1078,    -1,
    1076,  1077,  1078,    -1,   432,    -1,   432,  1099,  1076,    -1,
     448,  1041,   447,    -1,   448,  1043,   451,   447,    -1,   448,
    1043,   451,  1043,   447,    -1,   228,    -1,  1081,    -1,     9,
    1082,    -1,  1082,    -1,  1081,   452,  1082,    -1,   228,    -1,
     369,    -1,   438,    -1,   306,    -1,   189,    -1,   235,    -1,
     398,    -1,    94,  1084,    -1,   429,  1084,    -1,   421,   448,
    1043,   447,  1084,    -1,   233,   448,  1043,   447,  1084,    -1,
     333,   448,  1043,   447,  1084,    -1,    79,   448,  1041,   447,
    1084,    -1,   378,   448,  1041,   447,  1084,    -1,   379,   448,
    1041,   447,  1084,    -1,   403,   448,  1087,   447,  1084,    -1,
     265,   448,  1088,   447,    -1,   230,   448,  1089,   447,  1084,
      -1,   178,  1085,    -1,    -1,   448,  1043,   451,   447,    -1,
     448,  1043,   451,  1043,   447,    -1,    -1,   448,  1086,   447,
      -1,    -1,  1041,    -1,  1043,    -1,  1043,  1042,   217,    -1,
    1043,  1042,   401,    -1,  1043,    -1,  1043,  1042,  1043,    -1,
    1043,    -1,  1043,  1042,  1058,    -1,    -1,    -1,     9,    -1,
      -1,  1101,    -1,    -1,   199,    -1,    -1,   250,    -1,   295,
      -1,    -1,   253,    -1,    -1,   274,    -1,    -1,   339,    -1,
      -1,   353,  1111,    -1,   194,    -1,   268,    -1,   310,  1119,
      -1,   312,  1105,    -1,   431,   117,    -1,   117,    -1,    61,
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
    1679,  1686,  1687,  1688,  1691,  1692,  1696,  1700,  1701,  1708,
    1715,  1719,  1720,  1721,  1728,  1748,  1795,  1795,  1799,  1803,
    1819,  1820,  1821,  1827,  1837,  1846,  1848,  1849,  1855,  1859,
    1860,  1861,  1864,  1865,  1866,  1870,  1874,  1875,  1881,  1882,
    1886,  1895,  1904,  1913,  1928,  1938,  1945,  1949,  1987,  1994,
    2001,  2005,  2006,  2007,  2015,  2016,  2019,  2020,  2024,  2025,
    2029,  2030,  2036,  2061,  2062,  2063,  2064,  2070,  2077,  2078,
    2082,  2085,  2086,  2094,  2095,  2109,  2110,  2110,  2113,  2112,
    2125,  2126,  2130,  2142,  2151,  2155,  2156,  2166,  2165,  2183,
    2184,  2188,  2195,  2202,  2203,  2204,  2205,  2206,  2207,  2208,
    2209,  2210,  2217,  2221,  2221,  2221,  2227,  2239,  2264,  2288,
    2289,  2296,  2297,  2301,  2302,  2309,  2316,  2317,  2324,  2328,
    2337,  2338,  2344,  2354,  2372,  2373,  2377,  2378,  2379,  2383,
    2390,  2397,  2407,  2414,  2432,  2436,  2447,  2448,  2448,  2459,
    2460,  2464,  2464,  2481,  2482,  2484,  2488,  2490,  2489,  2521,
    2526,  2531,  2537,  2546,  2554,  2555,  2563,  2564,  2565,  2569,
    2589,  2593,  2602,  2603,  2604,  2605,  2606,  2607,  2608,  2609,
    2610,  2611,  2612,  2613,  2614,  2615,  2622,  2644,  2666,  2667,
    2679,  2699,  2706,  2707,  2711,  2712,  2713,  2714,  2715,  2716,
    2717,  2718,  2719,  2720,  2721,  2722,  2727,  2732,  2733,  2734,
    2735,  2736,  2737,  2738,  2739,  2740,  2741,  2742,  2743,  2744,
    2745,  2746,  2747,  2748,  2749,  2750,  2758,  2766,  2774,  2781,
    2786,  2797,  2814,  2815,  2818,  2819,  2826,  2850,  2851,  2868,
    2869,  2872,  2873,  2880,  2881,  2886,  2896,  2903,  2906,  2907,
    2908,  2915,  2922,  2947,  2947,  2952,  2953,  2957,  2958,  2961,
    2962,  2975,  2987,  3007,  3021,  3023,  3022,  3042,  3043,  3043,
    3056,  3058,  3057,  3069,  3070,  3074,  3075,  3084,  3091,  3094,
    3098,  3102,  3103,  3104,  3111,  3112,  3116,  3119,  3119,  3122,
    3123,  3129,  3134,  3135,  3138,  3139,  3142,  3143,  3146,  3147,
    3150,  3151,  3155,  3156,  3157,  3161,  3162,  3165,  3166,  3170,
    3174,  3175,  3179,  3180,  3181,  3182,  3183,  3184,  3185,  3186,
    3187,  3188,  3189,  3190,  3191,  3192,  3193,  3194,  3198,  3202,
    3203,  3204,  3205,  3206,  3207,  3208,  3212,  3216,  3217,  3218,
    3222,  3223,  3227,  3231,  3236,  3240,  3244,  3248,  3249,  3253,
    3254,  3258,  3259,  3260,  3263,  3263,  3263,  3266,  3270,  3273,
    3273,  3276,  3283,  3284,  3285,  3284,  3302,  3303,  3307,  3308,
    3313,  3315,  3314,  3350,  3351,  3355,  3356,  3357,  3358,  3359,
    3360,  3361,  3362,  3363,  3364,  3365,  3366,  3367,  3368,  3369,
    3370,  3371,  3375,  3379,  3383,  3387,  3388,  3389,  3390,  3391,
    3392,  3393,  3394,  3401,  3405,  3415,  3418,  3422,  3426,  3430,
    3438,  3441,  3445,  3449,  3453,  3461,  3474,  3476,  3486,  3475,
    3513,  3515,  3514,  3521,  3520,  3529,  3530,  3535,  3542,  3544,
    3548,  3558,  3560,  3568,  3576,  3605,  3636,  3638,  3648,  3653,
    3664,  3665,  3665,  3692,  3693,  3697,  3698,  3699,  3700,  3716,
    3728,  3759,  3796,  3808,  3811,  3812,  3821,  3825,  3821,  3838,
    3856,  3860,  3861,  3862,  3863,  3864,  3865,  3866,  3867,  3868,
    3869,  3870,  3871,  3872,  3873,  3874,  3875,  3876,  3877,  3878,
    3879,  3880,  3881,  3882,  3883,  3884,  3885,  3886,  3887,  3888,
    3889,  3890,  3891,  3892,  3893,  3894,  3895,  3896,  3897,  3898,
    3899,  3900,  3901,  3902,  3903,  3904,  3905,  3906,  3907,  3908,
    3931,  3930,  3943,  3947,  3951,  3955,  3959,  3963,  3967,  3971,
    3975,  3979,  3983,  3987,  3991,  3995,  3999,  4003,  4007,  4014,
    4015,  4016,  4017,  4018,  4019,  4023,  4027,  4028,  4031,  4032,
    4036,  4037,  4041,  4042,  4043,  4044,  4045,  4046,  4047,  4048,
    4052,  4056,  4060,  4065,  4066,  4067,  4068,  4069,  4070,  4074,
    4075,  4084,  4084,  4090,  4094,  4098,  4104,  4105,  4109,  4110,
    4119,  4119,  4124,  4128,  4135,  4136,  4145,  4151,  4152,  4156,
    4156,  4164,  4164,  4174,  4176,  4175,  4184,  4185,  4190,  4197,
    4204,  4206,  4210,  4218,  4229,  4230,  4231,  4236,  4240,  4239,
    4251,  4255,  4254,  4265,  4266,  4275,  4275,  4279,  4280,  4292,
    4292,  4296,  4297,  4308,  4309,  4310,  4311,  4312,  4315,  4315,
    4323,  4323,  4329,  4336,  4337,  4340,  4340,  4347,  4360,  4373,
    4373,  4384,  4385,  4395,  4394,  4407,  4411,  4415,  4419,  4423,
    4427,  4431,  4436,  4440,  4447,  4448,  4449,  4453,  4454,  4459,
    4460,  4461,  4462,  4463,  4464,  4465,  4466,  4467,  4468,  4472,
    4476,  4480,  4485,  4486,  4490,  4491,  4500,  4500,  4506,  4510,
    4514,  4518,  4522,  4529,  4530,  4539,  4539,  4561,  4560,  4579,
    4580,  4591,  4600,  4605,  4613,  4642,  4643,  4649,  4648,  4664,
    4668,  4667,  4682,  4683,  4688,  4689,  4700,  4729,  4730,  4731,
    4734,  4735,  4739,  4740,  4749,  4749,  4754,  4755,  4763,  4780,
    4797,  4815,  4840,  4840,  4853,  4853,  4866,  4866,  4875,  4879,
    4892,  4892,  4905,  4907,  4905,  4918,  4923,  4927,  4926,  4940,
    4941,  4950,  4950,  4958,  4959,  4963,  4964,  4965,  4969,  4970,
    4975,  4976,  4981,  4985,  4986,  4987,  4988,  4989,  4990,  4991,
    4995,  4996,  5005,  5005,  5018,  5017,  5027,  5028,  5029,  5033,
    5034,  5038,  5039,  5040,  5046,  5046,  5051,  5052,  5056,  5057,
    5058,  5059,  5060,  5061,  5067,  5071,  5072,  5076,  5081,  5085,
    5086,  5087,  5088,  5089,  5093,  5119,  5132,  5133,  5137,  5137,
    5145,  5145,  5155,  5155,  5160,  5164,  5176,  5176,  5182,  5186,
    5193,  5194,  5203,  5203,  5207,  5208,  5222,  5223,  5224,  5225,
    5229,  5230,  5234,  5235,  5236,  5248,  5248,  5253,  5258,  5257,
    5267,  5274,  5275,  5279,  5284,  5293,  5296,  5300,  5305,  5312,
    5319,  5320,  5324,  5325,  5330,  5342,  5342,  5365,  5366,  5370,
    5371,  5375,  5379,  5383,  5387,  5394,  5395,  5409,  5410,  5411,
    5415,  5416,  5425,  5425,  5440,  5440,  5451,  5452,  5461,  5461,
    5472,  5473,  5477,  5484,  5485,  5494,  5507,  5507,  5513,  5518,
    5517,  5528,  5529,  5533,  5535,  5534,  5545,  5546,  5551,  5550,
    5561,  5562,  5571,  5571,  5576,  5577,  5578,  5579,  5580,  5586,
    5595,  5599,  5608,  5615,  5616,  5622,  5623,  5627,  5636,  5637,
    5641,  5645,  5657,  5657,  5663,  5662,  5679,  5682,  5698,  5699,
    5702,  5703,  5707,  5708,  5713,  5718,  5726,  5738,  5743,  5751,
    5767,  5768,  5767,  5788,  5789,  5793,  5794,  5795,  5796,  5797,
    5801,  5802,  5811,  5811,  5816,  5823,  5824,  5825,  5834,  5834,
    5843,  5844,  5848,  5849,  5850,  5854,  5855,  5859,  5860,  5869,
    5869,  5875,  5879,  5883,  5890,  5891,  5900,  5907,  5908,  5916,
    5916,  5929,  5929,  5945,  5945,  5954,  5956,  5957,  5966,  5966,
    5976,  5977,  5982,  5983,  5988,  5995,  5996,  6001,  6008,  6009,
    6013,  6014,  6018,  6019,  6023,  6024,  6033,  6034,  6035,  6039,
    6063,  6066,  6074,  6084,  6089,  6094,  6099,  6106,  6107,  6110,
    6111,  6115,  6115,  6119,  6119,  6123,  6123,  6126,  6127,  6131,
    6138,  6139,  6143,  6155,  6155,  6166,  6167,  6172,  6175,  6179,
    6183,  6190,  6191,  6194,  6195,  6196,  6200,  6201,  6214,  6222,
    6229,  6231,  6230,  6240,  6242,  6241,  6256,  6260,  6262,  6261,
    6272,  6274,  6273,  6290,  6296,  6298,  6297,  6307,  6309,  6308,
    6324,  6329,  6334,  6344,  6343,  6355,  6354,  6370,  6375,  6380,
    6390,  6389,  6401,  6400,  6415,  6416,  6420,  6425,  6430,  6440,
    6439,  6451,  6450,  6467,  6470,  6482,  6489,  6496,  6496,  6506,
    6507,  6508,  6510,  6511,  6512,  6513,  6514,  6515,  6517,  6518,
    6519,  6521,  6524,  6526,  6527,  6529,  6530,  6531,  6533,  6535,
    6536,  6537,  6538,  6539,  6541,  6542,  6543,  6544,  6545,  6546,
    6548,  6549,  6550,  6551,  6552,  6553,  6555,  6556,  6559,  6559,
    6559,  6560,  6560,  6561,  6561,  6562,  6562,  6563,  6563,  6568,
    6569,  6572,  6573,  6574,  6578,  6579,  6580,  6581,  6582,  6583,
    6584,  6585,  6586,  6597,  6609,  6624,  6625,  6630,  6636,  6642,
    6662,  6666,  6682,  6696,  6697,  6702,  6708,  6709,  6714,  6723,
    6724,  6725,  6729,  6740,  6741,  6745,  6753,  6754,  6758,  6759,
    6765,  6785,  6786,  6790,  6791,  6795,  6796,  6800,  6801,  6802,
    6803,  6804,  6805,  6806,  6807,  6808,  6812,  6813,  6814,  6815,
    6816,  6817,  6818,  6822,  6823,  6827,  6828,  6832,  6833,  6837,
    6838,  6849,  6850,  6854,  6855,  6856,  6860,  6861,  6862,  6870,
    6874,  6875,  6876,  6877,  6881,  6882,  6886,  6896,  6914,  6941,
    6953,  6954,  6964,  6965,  6969,  6970,  6971,  6972,  6973,  6974,
    6975,  6983,  6987,  6991,  6995,  6999,  7003,  7007,  7011,  7015,
    7019,  7023,  7027,  7034,  7035,  7036,  7040,  7041,  7045,  7046,
    7051,  7058,  7065,  7075,  7082,  7092,  7099,  7113,  7123,  7124,
    7128,  7129,  7133,  7134,  7138,  7139,  7140,  7144,  7145,  7149,
    7150,  7154,  7155,  7159,  7160,  7167,  7167,  7168,  7168,  7169,
    7169,  7170,  7170,  7172,  7172,  7173,  7173,  7174,  7174,  7175,
    7175,  7176,  7176,  7177,  7177,  7178,  7178,  7179,  7179,  7180,
    7180,  7181,  7181,  7182,  7182,  7183,  7183,  7184,  7184,  7185,
    7185,  7186,  7186,  7187,  7187,  7188,  7188,  7189,  7189,  7189,
    7190,  7190,  7191,  7191,  7191,  7192,  7192,  7193,  7193,  7194,
    7194,  7195,  7195,  7196,  7196,  7197,  7197,  7197,  7198,  7198,
    7199,  7199,  7200,  7200,  7201,  7201,  7202,  7202,  7203,  7203,
    7204,  7204,  7204,  7205,  7205,  7206,  7206,  7207,  7207,  7208,
    7208,  7209,  7209,  7210,  7210,  7211,  7211,  7213,  7213,  7214,
    7214
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
     738,   737,   739,   739,   739,   739,   739,   739,   739,   739,
     739,   739,   739,   739,   739,   739,   739,   739,   739,   740,
     740,   740,   740,   740,   740,   741,   742,   742,   743,   743,
     744,   744,   745,   745,   745,   745,   745,   745,   745,   745,
     745,   745,   745,   745,   745,   745,   745,   745,   745,   746,
     746,   748,   747,   749,   749,   749,   750,   750,   751,   751,
     753,   752,   754,   754,   755,   755,   756,   757,   757,   758,
     758,   760,   759,   761,   762,   761,   763,   763,   764,   764,
     765,   765,   765,   765,   766,   766,   766,   767,   768,   767,
     769,   770,   769,   771,   771,   773,   772,   774,   774,   776,
     775,   777,   777,   778,   778,   778,   778,   778,   779,   779,
     781,   780,   782,   783,   783,   784,   784,   785,   786,   788,
     787,   789,   789,   791,   790,   792,   792,   792,   792,   792,
     792,   792,   792,   792,   793,   793,   793,   794,   794,   795,
     795,   795,   795,   795,   795,   795,   795,   795,   795,   795,
     795,   795,   795,   795,   796,   796,   798,   797,   799,   799,
     799,   799,   799,   800,   800,   802,   801,   804,   803,   805,
     805,   806,   806,   806,   807,   808,   808,   810,   809,   811,
     812,   811,   813,   813,   814,   814,   815,   815,   815,   815,
     816,   816,   817,   817,   819,   818,   820,   820,   820,   820,
     820,   820,   822,   821,   824,   823,   826,   825,   827,   827,
     829,   828,   831,   832,   830,   830,   833,   834,   833,   835,
     835,   837,   836,   838,   838,   839,   839,   839,   840,   840,
     841,   841,   842,   843,   843,   843,   843,   843,   843,   843,
     844,   844,   846,   845,   848,   847,   849,   849,   849,   850,
     850,   851,   851,   851,   853,   852,   854,   854,   855,   855,
     855,   855,   855,   855,   856,   857,   857,   858,   858,   859,
     859,   859,   859,   859,   860,   861,   862,   862,   863,   863,
     865,   864,   867,   866,   868,   868,   870,   869,   871,   871,
     872,   872,   874,   873,   875,   875,   876,   876,   876,   876,
     877,   877,   878,   878,   878,   880,   879,   881,   882,   881,
     881,   883,   883,   884,   884,   885,   885,   885,   885,   885,
     886,   886,   887,   887,   888,   890,   889,   891,   891,   892,
     892,   892,   892,   892,   892,   893,   893,   894,   894,   894,
     895,   895,   897,   896,   899,   898,   900,   900,   902,   901,
     903,   903,   903,   904,   904,   905,   907,   906,   908,   909,
     908,   910,   910,   911,   912,   911,   913,   913,   915,   914,
     916,   916,   918,   917,   919,   919,   919,   919,   919,   920,
     921,   921,   922,   923,   923,   924,   924,   925,   926,   926,
     927,   927,   929,   928,   931,   930,   932,   932,   933,   933,
     934,   934,   935,   935,   936,   936,   936,   937,   937,   937,
     939,   940,   938,   941,   941,   942,   942,   942,   942,   942,
     943,   943,   945,   944,   944,   946,   946,   946,   948,   947,
     949,   949,   950,   950,   950,   951,   951,   952,   952,   954,
     953,   955,   955,   955,   956,   956,   957,   958,   958,   960,
     959,   962,   961,   964,   963,   965,   965,   965,   967,   966,
     968,   968,   969,   969,   970,   971,   971,   972,   973,   973,
     974,   974,   975,   975,   976,   976,   977,   977,   977,   978,
     979,   979,   980,   980,   980,   980,   980,   981,   981,   982,
     982,   983,   983,   984,   984,   985,   985,   986,   986,   987,
     988,   988,   989,   991,   990,   992,   992,   993,   993,   993,
     993,   994,   994,   995,   995,   995,   996,   996,   997,   998,
     999,  1000,   999,  1001,  1002,  1001,  1003,  1004,  1005,  1004,
    1006,  1007,  1006,  1008,  1009,  1010,  1009,  1011,  1012,  1011,
    1013,  1013,  1013,  1015,  1014,  1017,  1016,  1018,  1018,  1018,
    1020,  1019,  1022,  1021,  1023,  1023,  1024,  1024,  1024,  1026,
    1025,  1028,  1027,  1029,  1029,  1030,  1031,  1033,  1032,  1034,
    1034,  1034,  1034,  1034,  1034,  1034,  1034,  1034,  1034,  1034,
    1034,  1034,  1035,  1035,  1035,  1035,  1035,  1035,  1035,  1035,
    1035,  1035,  1035,  1035,  1035,  1035,  1035,  1035,  1035,  1035,
    1035,  1035,  1035,  1035,  1035,  1035,  1035,  1035,  1036,  1036,
    1036,  1037,  1037,  1038,  1038,  1039,  1039,  1040,  1040,  1041,
    1041,  1042,  1042,  1042,  1043,  1043,  1043,  1043,  1043,  1043,
    1043,  1043,  1043,  1044,  1044,  1045,  1045,  1046,  1047,  1048,
    1049,  1049,  1050,  1051,  1051,  1052,  1053,  1053,  1054,  1055,
    1055,  1055,  1056,  1057,  1057,  1058,  1059,  1059,  1060,  1060,
    1061,  1062,  1062,  1063,  1063,  1064,  1064,  1065,  1065,  1065,
    1065,  1065,  1065,  1065,  1065,  1065,  1066,  1066,  1066,  1066,
    1066,  1066,  1066,  1067,  1067,  1068,  1068,  1069,  1069,  1070,
    1070,  1071,  1071,  1072,  1072,  1072,  1073,  1073,  1073,  1074,
    1075,  1075,  1075,  1075,  1076,  1076,  1077,  1078,  1078,  1079,
    1080,  1080,  1081,  1081,  1082,  1082,  1082,  1082,  1082,  1082,
    1082,  1083,  1083,  1083,  1083,  1083,  1083,  1083,  1083,  1083,
    1083,  1083,  1083,  1084,  1084,  1084,  1085,  1085,  1086,  1086,
    1087,  1087,  1087,  1088,  1088,  1089,  1089,  1090,  1091,  1091,
    1092,  1092,  1093,  1093,  1094,  1094,  1094,  1095,  1095,  1096,
    1096,  1097,  1097,  1098,  1098,  1099,  1099,  1100,  1100,  1101,
    1101,  1102,  1102,  1103,  1103,  1104,  1104,  1105,  1105,  1106,
    1106,  1107,  1107,  1108,  1108,  1109,  1109,  1110,  1110,  1111,
    1111,  1112,  1112,  1113,  1113,  1114,  1114,  1115,  1115,  1116,
    1116,  1117,  1117,  1118,  1118,  1119,  1119,  1120,  1120,  1120,
    1121,  1121,  1122,  1122,  1122,  1123,  1123,  1124,  1124,  1125,
    1125,  1126,  1126,  1127,  1127,  1128,  1128,  1128,  1129,  1129,
    1130,  1130,  1131,  1131,  1132,  1132,  1133,  1133,  1134,  1134,
    1135,  1135,  1135,  1136,  1136,  1137,  1137,  1138,  1138,  1139,
    1139,  1140,  1140,  1141,  1141,  1142,  1142,  1143,  1143,  1144,
    1144
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
       0,     4,     4,     4,     3,     3,     3,     4,     3,     4,
       3,     3,     3,     4,     5,     3,     4,     3,     3,     0,
       3,     3,     2,     2,     2,     3,     3,     3,     0,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     0,
       1,     0,     4,     4,     5,     6,     0,     2,     0,     1,
       0,     3,     3,     5,     0,     2,     2,     0,     5,     0,
       2,     0,     8,     0,     0,     3,     1,     2,     2,     3,
       0,     2,     2,     2,     0,     2,     2,     0,     0,     3,
       0,     0,     3,     0,     1,     0,     3,     0,     2,     0,
       3,     0,     3,     0,     1,     3,     3,     2,     1,     1,
       0,     4,     4,     0,     1,     1,     1,     1,     1,     0,
       6,     0,     1,     0,     4,     3,     3,     3,     3,     4,
       6,     6,     6,     6,     0,     2,     2,     1,     2,     1,
       1,     2,     2,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     1,     1,     0,     1,     0,     4,     4,     6,
       6,     8,     8,     0,     1,     0,     4,     0,     5,     1,
       3,     1,     1,     1,     2,     1,     2,     0,     3,     0,
       0,     3,     2,     3,     1,     3,     2,     1,     1,     1,
       0,     2,     0,     1,     0,     3,     0,     1,     1,     2,
       1,     1,     0,     3,     0,     3,     0,     5,     0,     3,
       0,     2,     0,     0,     8,     3,     0,     0,     3,     0,
       1,     0,     7,     0,     2,     0,     3,     3,     0,     2,
       1,     2,     4,     1,     1,     1,     1,     1,     1,     1,
       0,     1,     0,     3,     0,     4,     1,     1,     1,     1,
       2,     1,     1,     1,     0,     3,     1,     2,     2,     2,
       1,     1,     1,     2,     2,     1,     2,     4,     2,     0,
       1,     1,     1,     1,     4,     5,     0,     4,     0,     1,
       0,     3,     0,     3,     3,     4,     0,     4,     4,     6,
       0,     1,     0,     3,     0,     5,     1,     1,     1,     1,
       0,     3,     0,     3,     2,     0,     3,     2,     0,     4,
       2,     0,     1,     1,     3,     0,     1,     2,     3,     3,
       0,     3,     1,     3,     7,     0,    10,     0,     2,     0,
       2,     2,     3,     3,     2,     0,     3,     0,     1,     1,
       0,     1,     0,     4,     0,     7,     0,     1,     0,     7,
       0,     2,     3,     0,     1,     1,     0,     4,     4,     0,
       7,     0,     2,     0,     0,     4,     1,     2,     0,     4,
       0,     1,     0,     3,     1,     1,     1,     1,     1,     4,
       4,     3,     4,     1,     1,     1,     2,     3,     1,     2,
       3,     3,     0,     3,     0,     7,     0,     5,     0,     2,
       0,     2,     0,     3,     0,     2,     4,     0,     2,     4,
       0,     0,     7,     0,     4,     2,     2,     2,     2,     2,
       0,     1,     0,     4,     2,     0,     2,     2,     0,     8,
       1,     2,     1,     3,     3,     0,     3,     0,     1,     0,
       4,     4,     6,     6,     0,     1,     2,     0,     1,     0,
       3,     0,     7,     0,     4,     0,     1,     1,     0,     9,
       0,     3,     1,     3,     2,     2,     2,     3,     0,     3,
       0,     3,     0,     3,     0,     1,     1,     1,     1,     8,
       0,     1,     1,     1,     1,     1,     1,     0,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     0,     1,     5,
       1,     2,     5,     0,     8,     0,     2,     0,     4,     3,
       3,     1,     1,     0,     1,     1,     0,     1,     2,     2,
       0,     0,     3,     0,     0,     3,     2,     0,     0,     3,
       0,     0,     3,     2,     0,     0,     3,     0,     0,     3,
       1,     1,     2,     0,     3,     0,     3,     1,     1,     2,
       0,     3,     0,     3,     0,     1,     1,     1,     2,     0,
       3,     0,     3,     0,     3,     1,     1,     0,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     0,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     2,
       1,     1,     2,     1,     2,     1,     5,     1,     5,     1,
       3,     0,     1,     1,     1,     3,     3,     3,     3,     2,
       2,     3,     3,     1,     3,     1,     2,     2,     1,     1,
       1,     2,     1,     1,     2,     1,     0,     2,     1,     1,
       1,     3,     1,     1,     2,     1,     0,     1,     1,     1,
       1,     1,     2,     1,     3,     1,     2,     1,     3,     3,
       3,     4,     3,     1,     1,     1,     1,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     3,     1,     3,     3,     4,     5,     1,
       1,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     5,     5,     5,     5,     5,     5,     5,
       4,     5,     2,     0,     4,     5,     0,     3,     0,     1,
       1,     3,     3,     1,     3,     1,     3,     0,     0,     1,
       0,     1,     0,     1,     0,     1,     1,     0,     1,     0,
       1,     0,     1,     0,     2,     1,     1,     2,     2,     2,
       1,     2,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     1,
       0,     1,     0,     1,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     2,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     2,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     3,     4,     6,     7,
      38,    38,     0,     0,     5,     0,     8,    14,    28,    27,
      29,    29,     0,   253,   253,     0,     0,    24,    40,     0,
       9,    15,    30,    26,  1485,     0,   151,     0,   586,   586,
    1486,     0,     0,     0,     0,     0,     0,    39,   255,     0,
      17,     0,    25,    33,    37,    36,  1510,    35,    42,   153,
       0,   155,   265,   266,     0,   316,   258,   590,    18,    20,
      38,     0,    16,    34,  1511,    32,    41,   159,   157,   236,
       0,     0,   434,     0,   593,   591,   608,     0,    19,    10,
      11,     0,     0,     0,     0,     0,    43,    44,    45,    47,
      46,   154,     0,   234,  1477,   243,   156,     0,   238,   240,
     241,   256,     0,     0,   437,  1322,   259,   319,   267,   598,
     598,     0,     0,     0,   253,    23,    56,    71,    49,    80,
    1439,   160,   159,     0,   152,  1478,  1527,   244,   245,   246,
    1459,   237,   239,   260,   317,     0,     0,   440,   264,     0,
     263,   320,  1427,   269,  1468,   598,   595,   601,     0,   598,
     609,   587,    21,    12,     0,  1485,    54,  1510,    55,  1510,
      60,    62,    63,    64,     0,     0,    70,     0,    73,  1540,
      48,     0,  1539,     0,     0,  1485,  1485,     0,     0,  1518,
    1485,  1485,  1485,  1485,  1485,     0,  1485,  1471,  1485,    79,
       0,    82,    84,    85,    86,    88,    87,    89,    90,    91,
      92,    93,    94,  1440,     0,   158,   236,  1528,  1473,  1460,
    1479,   257,   319,   435,     0,     0,   532,   319,   322,     0,
    1485,   596,  1485,     0,   606,   599,   600,   610,   586,  1485,
       0,    57,  1510,    59,    61,     0,  1452,  1485,     0,    77,
       0,    72,    74,    52,    50,     0,     0,  1340,   106,     0,
       0,  1485,  1485,  1519,  1485,     0,     0,     0,     0,     0,
    1485,     0,  1472,     0,     0,    81,    83,   161,   235,  1474,
       0,  1480,     0,   261,   318,   319,   438,     0,     0,   254,
     262,   325,     0,   329,     0,   330,   326,  1473,  1485,     0,
       0,  1485,  1473,  1497,  1485,  1457,     0,   268,   270,   273,
     274,   275,   276,   277,   278,   279,   280,   281,     0,     0,
    1485,   607,     0,     0,   588,    17,     0,  1389,    69,    58,
    1451,     0,    76,    75,    78,    51,    53,  1485,    98,    99,
       0,     0,     0,  1384,   147,  1335,   146,   100,   101,   150,
       0,   149,   133,  1487,   135,    95,    96,   163,   247,   248,
     251,   242,  1320,   436,   319,   441,     0,     0,   323,   331,
     332,   327,     0,     0,     0,  1485,  1457,     0,     0,     0,
       0,     0,  1498,  1485,     0,  1458,     0,     0,   271,   272,
     602,   603,   605,     0,   597,   611,   613,     0,     0,    68,
       0,  1398,  1394,  1399,  1397,  1395,  1400,  1396,   139,   140,
     142,   148,   145,  1445,  1446,     0,   144,  1489,  1488,   136,
       0,   102,  1512,   249,     0,   250,  1321,   439,   443,   533,
     324,   340,   334,   293,   313,  1447,  1448,   302,  1333,   297,
     296,   295,  1339,  1338,  1495,  1471,  1483,     0,   531,   314,
     315,  1485,  1485,   604,   613,     0,     0,    13,    66,    67,
      65,   111,   125,   121,   126,   108,   124,   122,   109,   110,
     123,   107,   112,   113,   115,   141,     0,  1385,   134,   137,
      97,  1497,     0,  1535,   220,     0,  1497,  1485,  1469,  1490,
     222,     0,  1539,   207,   206,   162,   164,   165,   166,   167,
     168,   169,     0,   170,   171,   219,   172,   173,   174,   175,
     176,   177,  1485,  1465,   252,     0,   442,   444,   445,   534,
    1485,  1461,     0,     0,   283,  1334,  1496,   304,     0,   286,
    1484,  1523,   312,     0,     0,     0,     0,   623,   614,   615,
     616,   617,   622,     0,     0,   114,   117,     0,   143,   138,
     105,   104,  1525,  1485,  1490,  1536,   184,   223,  1485,  1512,
    1470,  1485,  1485,  1491,  1485,  1485,  1459,     0,  1485,     0,
    1466,     0,   448,   446,   536,     0,   422,   364,   397,   385,
     394,   391,   388,  1537,   365,   366,   367,   368,   369,   370,
     371,   372,   373,  1514,   398,     0,   374,   361,   375,   376,
       0,     0,  1521,   378,   379,   377,   418,   381,   382,   380,
    1485,  1487,   341,   342,   343,   344,   345,   346,   362,   347,
     348,   349,   350,   351,   352,   353,   354,   355,     0,     0,
    1462,     0,   335,   294,   285,   284,   282,   303,  1471,  1524,
     291,   300,   299,   301,   298,     0,   619,   621,   624,   680,
     731,   740,   747,   751,   775,   779,   797,   790,   798,   799,
     803,   836,   845,   847,   874,   882,   884,  1535,   890,     0,
     901,   922,   924,   960,   962,   966,   679,   972,   985,  1005,
    1022,  1024,  1028,  1035,  1036,  1052,  1072,  1090,     0,  1108,
    1119,  1127,  1129,  1131,  1133,  1138,  1160,  1183,   618,   630,
     631,   632,   633,   634,   635,   636,   637,   639,   638,   640,
     641,   642,   643,   644,   645,   646,   647,   648,   649,   650,
     651,   652,   653,   654,   655,   656,   657,   658,   659,   660,
     661,   662,   663,   664,   665,   666,   667,   668,   669,   670,
     671,   672,   673,   674,   675,   676,   677,  1156,  1157,  1158,
     678,    22,     0,   116,  1526,  1485,     0,  1485,   186,   185,
     181,     0,  1513,   222,   218,     0,     0,     0,     0,   229,
    1508,  1508,     0,   230,     0,   203,   221,  1485,   330,   540,
     535,   537,   538,   433,   395,   396,   383,   384,   392,   393,
     389,   390,   386,   387,  1538,     0,  1515,   416,   402,   356,
    1380,   431,  1522,   419,   420,   417,     0,     0,   358,   360,
    1443,  1443,     0,  1501,  1501,   339,   336,  1390,  1392,  1464,
     305,   306,   307,   308,     0,     0,   287,  1482,   293,     0,
       0,   625,     0,     0,     0,  1247,   746,     0,   777,   781,
       0,     0,     0,     0,     0,  1247,   876,     0,     0,   886,
     891,     0,  1247,     0,     0,     0,     0,     0,     0,   974,
     995,     0,     0,     0,     0,     0,     0,     0,     0,  1104,
    1102,     0,     0,  1128,  1126,     0,     0,     0,     0,  1161,
    1167,     0,     0,   131,   127,   132,   130,   128,   129,   118,
     119,     0,   192,   193,   191,   190,     0,   179,   180,     0,
     212,   211,   212,   208,   224,   225,   226,   228,  1509,   231,
     232,   233,  1336,  1485,   457,   457,  1487,   477,   449,   452,
     453,     0,   541,   539,   421,     0,  1533,     0,  1381,  1382,
       0,   363,   423,   425,   427,     0,   357,  1469,   399,   400,
    1391,  1502,     0,     0,     0,     0,     0,  1463,  1471,   292,
     612,   620,   729,   699,  1379,  1501,     0,     0,  1413,  1416,
    1501,  1313,     0,     0,     0,     0,     0,     0,     0,     0,
    1413,   738,  1355,   736,  1345,  1347,  1353,  1354,  1432,   741,
       0,  1246,  1262,  1332,     0,  1328,  1330,  1329,  1374,   753,
    1373,  1375,   776,   780,   793,     0,  1315,  1441,  1512,  1394,
     834,   699,     0,  1347,   843,     0,   753,   853,   852,  1455,
     849,   851,   881,   878,   877,   880,   875,  1501,   883,  1341,
    1343,   885,  1326,   895,  1531,  1245,   903,   923,   459,     0,
     926,   927,   928,   961,  1076,     0,   963,     0,   970,     0,
     973,   996,  1332,   986,   995,   988,     0,   993,     0,  1329,
       0,  1434,  1185,  1318,  1512,  1185,     0,  1050,  1041,  1319,
       0,  1325,  1053,  1054,  1055,  1056,  1057,  1065,  1058,  1068,
       0,  1323,     0,  1073,  1091,  1105,  1467,     0,  1110,  1112,
       0,  1124,     0,  1130,     0,  1135,  1140,  1168,     0,  1169,
    1503,  1185,     0,   103,  1430,   188,   187,   178,   189,     0,
     210,   209,  1485,   202,   196,  1337,   204,     0,   458,   454,
       0,   455,     0,   447,   450,   543,   403,  1534,   404,  1501,
       0,     0,     0,  1301,  1299,  1362,  1304,  1356,  1360,  1361,
       0,  1383,   432,  1537,   426,     0,   359,  1444,   338,   337,
    1393,   311,  1495,     0,   289,   730,   681,  1464,     0,   708,
       0,     0,     0,     0,     0,  1401,  1418,  1412,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1402,   739,
     732,     0,     0,  1346,  1433,   744,  1432,  1248,     0,   749,
       0,   754,   764,  1372,   778,  1371,   783,   794,   791,   796,
     795,  1247,  1316,  1442,  1317,  1234,   835,   804,   814,  1200,
    1200,  1200,  1200,   844,   837,     0,     0,   846,  1456,  1247,
     872,   859,   855,   857,  1247,   879,     0,  1342,   888,  1532,
     893,   905,     0,   460,     0,   949,   934,   925,   929,   931,
     932,   933,  1080,     0,     0,   971,   967,     0,   979,   976,
     978,   977,   980,   987,   990,   626,  1247,     0,     0,   997,
       0,  1435,  1436,  1512,     0,  1023,  1007,  1030,  1043,  1051,
    1037,     0,  1043,     0,  1367,  1368,  1066,  1069,     0,     0,
    1324,  1064,     0,  1063,     0,  1093,     0,     0,  1103,     0,
       0,  1111,     0,  1125,  1120,     0,     0,  1136,  1137,  1134,
    1467,     0,     0,  1170,     0,  1504,     0,  1030,   120,  1450,
       0,   196,   194,  1431,     0,   215,   201,   227,     0,   451,
     456,   462,   472,   330,   478,  1520,  1503,   407,     0,  1309,
    1310,     0,  1302,  1303,  1386,     0,     0,     0,     0,     0,
       0,     0,     0,  1516,   428,   310,  1495,  1503,   288,   704,
     695,  1200,   685,   692,   686,   688,   690,     0,  1200,     0,
     684,   691,   698,   697,     0,  1200,  1499,  1499,  1499,   702,
     703,  1364,  1363,     0,  1352,  1301,  1299,     0,     0,  1301,
       0,  1348,  1349,  1350,  1314,  1301,     0,     0,  1301,     0,
       0,  1301,  1301,  1301,     0,     0,  1207,  1441,     0,     0,
     742,     0,  1254,  1255,  1256,  1286,  1257,  1535,  1290,  1295,
    1529,  1249,  1297,  1529,  1279,  1259,  1261,  1253,  1252,  1287,
    1258,  1260,  1269,  1270,  1271,  1272,  1273,  1288,  1251,  1291,
    1293,  1274,  1275,  1276,  1277,  1278,  1263,  1285,  1268,  1265,
    1266,  1267,  1264,  1280,  1281,  1282,  1283,  1284,  1250,     0,
       0,  1331,   760,     0,     0,   767,   788,   789,   782,   784,
       0,  1207,  1239,  1241,   801,  1235,  1236,  1237,     0,  1540,
    1200,     0,  1201,   807,  1203,   808,   805,   806,     0,  1207,
    1441,   867,   869,   868,   862,   864,   870,   873,   848,   860,
     856,   854,  1247,   626,   850,  1344,  1503,   887,  1327,   626,
    1535,   913,   914,   916,   918,   919,   915,   917,   908,  1535,
     904,     0,   950,     0,   952,   951,   953,   944,   945,     0,
       0,   930,  1082,  1505,     0,     0,   964,  1207,  1441,  1539,
       0,   991,   627,   998,   999,  1002,     0,   994,  1192,  1191,
    1001,  1007,  1186,     0,     0,  1234,     0,     0,     0,  1042,
       0,     0,     0,  1067,     0,  1071,  1070,  1061,     0,  1485,
    1234,  1107,  1106,  1113,  1114,  1115,     0,  1207,  1441,     0,
    1428,     0,  1115,  1182,  1172,  1171,  1177,     0,  1179,  1180,
    1187,  1449,  1430,     0,   198,   199,   197,  1485,   464,   475,
     476,   474,   332,   480,   556,  1485,   547,   545,   546,   548,
    1499,     0,  1485,     0,   559,   551,  1499,   552,     0,   555,
     560,   558,   553,   557,     0,   554,     0,   542,   570,   565,
     568,   567,   566,   569,   544,   571,     0,   411,   406,  1357,
    1358,  1359,  1312,  1300,  1305,  1306,  1307,  1308,  1311,  1387,
       0,  1517,  1535,   309,     0,   696,  1203,   687,   689,  1200,
     693,   683,   723,  1485,   712,   713,  1485,   724,   714,   715,
     718,   728,   725,   716,     0,   726,   717,   727,   709,   710,
     682,  1500,     0,     0,     0,   700,   701,  1366,  1351,  1365,
    1413,  1441,     0,  1417,     0,  1413,  1413,     0,  1410,  1413,
    1413,  1413,     0,  1413,  1413,  1208,   733,  1210,  1207,   745,
       0,  1289,  1530,  1292,  1294,   750,   748,   755,   756,   601,
       0,   766,   765,  1173,  1174,   770,   768,     0,   787,     0,
     792,   626,   626,   802,   800,  1238,   814,   814,   814,   814,
    1485,   819,   832,   833,   820,     0,  1485,   823,   824,   827,
     825,     0,   826,   816,   817,   809,   815,   626,  1204,  1199,
       0,   838,     0,  1247,  1247,   866,   626,   863,   858,     0,
     896,     0,     0,   920,     0,     0,     0,   946,   948,     0,
     940,   956,   941,   942,   935,   936,   956,  1074,  1485,     0,
    1506,  1081,   409,   410,  1490,   965,   968,     0,     0,   982,
     992,   989,   629,     0,     0,  1009,  1008,  1223,  1225,  1026,
    1220,  1221,  1033,  1031,     0,  1247,  1044,  1247,  1038,  1046,
    1059,  1060,  1062,  1437,  1100,  1214,     0,  1441,  1121,     0,
       0,  1429,  1141,  1142,     0,  1145,  1148,  1152,  1146,  1178,
    1503,  1181,  1193,  1453,   195,     0,   216,   217,   213,     0,
       0,   466,     0,  1520,     0,  1485,   549,   550,     0,   573,
    1485,  1533,   574,   572,   405,  1467,   401,  1490,  1388,   429,
     290,  1198,   694,     0,     0,  1243,  1243,   711,   706,   705,
     707,  1406,  1207,  1414,     0,  1426,  1411,  1404,  1424,  1405,
    1407,  1408,  1421,  1422,  1409,  1403,   626,  1211,  1206,   734,
     743,     0,     0,   757,   758,     0,   762,   761,   763,  1175,
    1176,   773,   771,   626,   785,   786,  1240,  1242,  1200,  1200,
    1200,  1200,     0,   821,   822,     0,  1243,  1243,   818,  1202,
     626,  1207,  1315,  1207,  1315,   865,   871,   861,   889,   897,
     899,   906,   909,   910,  1475,   921,   902,   907,   956,  1369,
    1370,   956,     0,   939,   937,   938,   943,  1084,     0,  1507,
    1078,  1207,   981,   975,     0,   628,  1003,     0,     0,  1015,
       0,   626,   626,  1027,  1025,  1222,  1034,  1029,  1032,  1039,
     626,  1048,  1047,  1438,     0,     0,  1101,  1092,  1215,  1117,
    1217,     0,  1207,  1207,  1132,  1428,  1144,  1483,  1150,  1483,
    1214,     0,  1230,  1232,  1196,  1194,  1227,  1228,  1195,  1454,
       0,   214,   463,  1485,     0,   468,   473,  1499,   509,   529,
     524,  1457,     0,     0,  1485,  1501,  1485,     0,   479,   485,
     486,   487,   496,   488,   490,   493,   481,   482,   483,   489,
     492,   510,   494,   497,   484,     0,   491,   495,  1378,   564,
    1376,  1377,   580,   563,   575,   585,     0,  1485,  1485,   424,
     720,   719,   722,     0,   721,   735,  1415,  1209,   626,  1535,
    1535,   759,   774,   752,   626,   769,   813,   812,   811,   810,
     829,   828,   831,   830,  1205,   840,     0,   839,     0,   626,
     900,   894,   911,  1476,     0,   955,   947,   956,   958,     0,
       0,  1087,  1083,  1077,   969,   984,     0,     0,  1010,  1485,
    1017,     0,  1011,     0,  1014,  1224,  1226,   626,  1045,   626,
    1094,  1095,  1096,  1097,  1098,  1099,   626,  1118,  1109,  1218,
    1213,  1116,  1123,  1122,  1143,     0,  1483,  1147,     0,  1154,
    1166,  1163,  1165,  1164,  1159,  1162,   626,   626,  1197,  1184,
    1229,  1190,  1189,  1492,     0,  1485,  1485,   470,   508,  1485,
     530,   528,   525,   526,  1487,   518,  1485,  1247,     0,     0,
       0,     0,   511,     0,     0,   516,   519,   522,   583,   581,
     582,   584,     0,   578,   576,   577,   579,     0,   415,   412,
     413,     0,     0,  1492,  1212,  1296,  1298,   772,  1207,  1207,
     898,     0,   954,   959,     0,  1485,  1085,     0,     0,  1075,
    1079,   983,     0,     0,  1020,  1018,  1019,  1013,  1012,  1040,
    1049,  1216,   626,  1149,     0,  1153,  1155,  1139,  1231,  1233,
    1493,  1494,  1188,   465,     0,     0,  1485,   461,     0,   517,
       0,   514,  1441,   512,   513,   503,   501,   502,   504,   500,
     505,   499,   498,     0,   523,   521,   520,   562,   561,   414,
     408,   430,  1244,   842,   841,   912,   957,     0,  1088,  1485,
    1247,  1016,  1021,  1006,  1219,  1151,   467,   469,     0,   507,
     506,   527,     0,  1086,     0,  1004,   471,     0,  1089,   515
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
    1097,   498,   895,   499,  1307,  1308,  1574,  1104,   500,   501,
     502,   503,   903,  1100,  1828,   504,   505,   506,   507,   508,
     509,   510,   511,   773,   134,   106,   107,   108,   109,   140,
     110,   358,   359,   425,    30,    65,   143,    83,   221,   148,
     116,   149,   117,   153,   230,   308,   309,   636,   310,  1338,
     828,   524,   311,   441,   312,   642,   313,   314,   637,   820,
     821,   822,   823,   315,   316,   317,    82,   222,   150,   151,
     152,   228,   294,   431,   295,   371,   372,   521,   815,   296,
     520,   612,   613,   614,   936,   615,   616,   617,   618,   619,
     620,   926,  1317,  1617,  1618,  1774,  1846,  2169,  2170,   621,
     622,   805,   623,   624,   625,  1133,   932,   933,  2039,   626,
     627,   114,   285,   147,   364,   226,   428,   516,   517,   518,
     777,   918,   919,  1109,  1110,  1027,   920,  1578,  1831,  1995,
    2137,  2217,  1311,  1581,  1113,  1314,  1833,  2016,  2017,  2232,
    2018,  2019,  2020,  2021,  2223,  2022,  2023,  2024,  2025,  2155,
    2156,  2144,  2026,  2027,  2141,   449,   289,   519,   574,   780,
     781,   782,  1115,  1315,  1614,  2167,  2162,  1615,    50,   237,
     396,    86,   120,   119,   155,   156,   157,   234,   322,   122,
     324,   454,   455,   538,   539,   540,   541,   542,   832,  1521,
    1522,  1782,   543,   699,   700,   833,   952,  1149,  1359,  1360,
    1355,  1658,  1659,  1146,   701,   834,   971,  1172,  1170,   702,
     835,   979,  1390,   703,   836,  1440,   704,   837,  1182,  1442,
    1697,  1698,  1699,  1445,  1705,  1893,  1891,  2054,  2053,   705,
     838,   992,   706,   839,   993,  1448,  1449,   707,   840,   994,
    1188,  1191,   708,   709,   710,   841,  1714,   711,   842,  1000,
    1460,  1733,  1734,  1197,   712,   843,  1004,  1204,   713,   844,
     714,   845,  1009,  1010,  1210,  1211,  1212,  1483,  1481,  1746,
    1213,  1474,  1475,  1745,  1478,   715,   846,  1016,   716,   847,
     717,   848,   718,  1022,  1487,   719,   850,   720,   852,  1489,
    1920,  2069,  2071,   721,   853,  1221,  1498,  1753,  1922,  1923,
    1924,  1926,   722,   854,   723,   855,  1029,  1227,  1228,  1229,
    1510,  1764,  1765,  1230,  1507,  1508,  1509,  1758,  1231,  1933,
    2184,   724,   856,   725,   857,  1036,   726,   858,  1038,  1236,
     727,   859,  1040,  1242,  1520,  1943,   728,   860,  1043,  1245,
    1781,  1044,  1045,  1046,  1524,  1525,   729,   861,  1534,  1949,
    2090,  2194,  2253,   730,   862,   731,   863,  1954,   732,   864,
    1535,  1957,   733,   734,   865,  1057,  2097,  1262,  1537,  1960,
    1798,  1799,  2099,  1260,   735,   866,  1062,  1063,  1064,  1065,
    1274,  1066,  1067,  1068,  1069,   736,   867,  1033,  1937,  1232,
    2083,  1512,  1767,  2081,  2189,   737,   868,  1275,  1550,  1964,
    1967,   738,  1075,  1278,   739,   871,  1077,  1078,  1805,  2108,
     740,   872,  1081,  1284,   741,   874,   742,   875,   743,   876,
     744,   877,  1289,   745,   878,  1291,  1812,  1813,  1562,  1815,
    1978,  2117,  1980,  2207,   746,   747,   880,  2124,  1089,  1294,
    1566,  1706,  1892,  1820,   748,  1568,   749,   750,   882,  1255,
    1822,  2078,  1984,  2129,  1635,  1463,  1464,  1737,  1739,  1910,
    1686,  1687,  1876,  1878,  2048,  1969,  1970,  2106,  2110,  2202,
    1789,  1790,  1951,  1791,  1952,  1985,  1986,  2126,  1987,  2127,
    1454,  1455,  1456,  1711,  1457,  1712,  2042,  1024,  1025,   981,
     982,  1177,  1178,  1421,  1422,  1423,  1424,  1425,  1123,  1325,
    1366,   972,   995,  1192,  1052,  1058,   361,   362,  1070,  1071,
    1218,  1047,   985,   986,   437,   443,  1106,   444,   258,  1018,
    1019,   973,   997,  1126,  1363,  1668,  1766,  1928,  1002,  1048,
    2029,   975,   954,   800,   928,   929,  2031,   976,   817,   818,
     977,  1155,  1157,  1370,  1384,  1379,  1376,   229,  1814,  1302,
    1175,  1253,  1965,   214,  1194,   938,   415,   377,  1303,   247,
    1990,  1743,   386,   220,   631,  1150,   571,   158,   561,   273,
     280,  2074,   136,   282,   829,   531,    42,   420,   564,  2212,
     527,   383,  1662,   942,  1296,  1771,   909,   174,   513,   797,
    1632,   264,   629,   640,   755,   218,  1693,  1220,  1118,   556,
     795,  1461
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1751
static const yytype_int16 yypact[] =
{
   -1751,   335,   447, -1751,   328,   370,   447, -1751, -1751, -1751,
     685,   685,    37,    37, -1751,   709, -1751, -1751, -1751, -1751,
     868,   868,   457,   913,   913,   726,   589, -1751,   978,   991,
   -1751, -1751, -1751, -1751,   -64,   775,   839,   694,   853,   853,
   -1751,   723,   161,   752,   755,   871,   800, -1751,    19,  1100,
     921,  1102, -1751,   -72, -1751, -1751,   948, -1751, -1751, -1751,
     813, -1751, -1751, -1751,   905,   827, -1751,    79, -1751,   521,
     685,    37, -1751, -1751, -1751, -1751,   725, -1751,  1109,    10,
     858,   919,  1060,   870, -1751, -1751,   993,    37, -1751, -1751,
   -1751,   884,   888,   907,   910,   914, -1751, -1751, -1751, -1751,
   -1751,   996,   918,  1140,   961,   770, -1751,   433, -1751, -1751,
   -1751, -1751,   927,  1015,  1137, -1751,    38,   942, -1751,    77,
      77,   943,   932,   937,   913, -1751,    95,  1211,     2,  1132,
    1117, -1751, -1751,   955, -1751, -1751,  1007, -1751, -1751, -1751,
    1371, -1751, -1751, -1751, -1751,   960,  1048,  1086, -1751,   870,
   -1751, -1751, -1751, -1751, -1751,    44, -1751,   495,   -69,   103,
   -1751, -1751, -1751, -1751,  1053,  1216, -1751,   352, -1751,   374,
   -1751, -1751, -1751, -1751,    91,   154, -1751,   -48, -1751, -1751,
   -1751,   976,  -139,  1325,   999,  1216,  1216,   999,  1058,  1076,
    1216,  1216,  1216,  1216,  1216,   999,  1216,  1381,  1216, -1751,
     952, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751,   999,   996,    10, -1751,  1355, -1751,
    1268,    38,   942, -1751,   994,  1103,  1111,   942,   257,  1027,
     862, -1751,  1216,  1101,  1192, -1751, -1751,  1363,   853,  1216,
    1243, -1751,   382, -1751, -1751,  1119, -1751,  1216,  1269, -1751,
     814, -1751, -1751, -1751, -1751,  1031,  1238, -1751, -1751,   999,
     999,  1216,  1216, -1751,  1216,  1049,  1412,   999,   999,  1049,
    1216,  1049, -1751,   999,    16, -1751, -1751, -1751, -1751, -1751,
     870, -1751,   870, -1751, -1751,   942, -1751,  1037,  1138, -1751,
   -1751, -1751,  1027, -1751,  1041,   -16, -1751,  1355,  1216,   695,
     695,  1216,    31,  1246,  1216,  1468,  1225, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,   912,   590,
    1216, -1751,  1062,  1051, -1751,   921,  1243, -1751, -1751, -1751,
   -1751,  1049, -1751, -1751, -1751, -1751, -1751,  1216, -1751, -1751,
     890,  1049,  1267,   599, -1751, -1751, -1751, -1751, -1751, -1751,
    1049, -1751, -1751,    69, -1751, -1751, -1751, -1751,   870, -1751,
    1207,   870, -1751, -1751,   942, -1751,  1055,  1056, -1751, -1751,
    1421, -1751,  1422,  1243,  1073,  1216,  1468,  1049,   384,   -45,
    1243,  1080, -1751,  1216,  1077, -1751,  1077,   -32, -1751, -1751,
   -1751, -1751, -1751,  1243, -1751, -1751, -1751,   559,    67, -1751,
    1237, -1751, -1751, -1751, -1751, -1751, -1751, -1751,   890, -1751,
    1120, -1751, -1751, -1751, -1751,  1049, -1751, -1751, -1751, -1751,
    1243, -1751,   756, -1751,  1243, -1751, -1751, -1751,  1202, -1751,
   -1751, -1751,   732,  1122, -1751, -1751, -1751,  1049, -1751, -1751,
   -1751, -1751, -1751, -1751,  1288,    57,  1324,  1094, -1751, -1751,
   -1751,  1216,  1216, -1751, -1751,  2314,    37, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751,   477, -1751,    89, -1751,   890, -1751,  1243, -1751,
     425,  1246,  1219,  1139, -1751,  1179,  1246,  1216,  1481,   215,
     -23,  1243,  1113, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751,  1165, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751,  1216,  1511, -1751,  1077, -1751,  1202, -1751, -1751,
    4470,  1523,  1368,  1243,   112, -1751, -1751, -1751,  1243, -1751,
   -1751,  1190, -1751,   -25,   -25,  1348,  1110,  1114, -1751, -1751,
   -1751, -1751,  1215,  3012,  1115, -1751, -1751,   477, -1751, -1751,
   -1751, -1751,  1183,  1216,  1342, -1751,   158, -1751,  1216,   867,
   -1751,  1216,  1216, -1751,  1216,  1216,  1371,   168,  1216,  1133,
   -1751,  1212, -1751, -1751,  1027,  1347, -1751, -1751,   -80,   550,
     560,   585,   591,  1143, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751,  1231, -1751,  1243, -1751, -1751, -1751, -1751,
    1049,  1049,  1362, -1751, -1751, -1751,    80, -1751, -1751, -1751,
    1216,   166, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,   950,   409,
   -1751,   247, -1751, -1751, -1751, -1751, -1751,   175,  1381, -1751,
     697, -1751, -1751, -1751, -1751,  1470, -1751, -1751,  1344, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751,  1139, -1751,  1816,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,   399, -1751,
   -1751,  1278, -1751, -1751, -1751, -1751,   644, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751,   631, -1751, -1751,  1216,   115,  1216, -1751, -1751,
     136,   407, -1751, -1751, -1751,   -45,  1205,  1049,  1049, -1751,
    1300,  1300,  1307, -1751,  1049, -1751, -1751,   110,   -16, -1751,
   -1751,  1027, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751,  1145, -1751, -1751,  1186, -1751,
    1136,  1194, -1751, -1751, -1751, -1751,  2769,   248,  1555, -1751,
    1234,  1234,   890,  1320,  1320, -1751, -1751,  1141, -1751, -1751,
   -1751, -1751, -1751, -1751,    50,  1420, -1751, -1751,  1122,  1243,
    1146, -1751,  1149,  1049,  3602,  1163,   -11,  1659, -1751, -1751,
    4159,   870,  4225,  4159,  1369,   746,   925,   108,  1049, -1751,
   -1751,  1467, -1751,   108,  1049,   872,  1049,  3666,  4159, -1751,
    1567,   870,  1049,   870,  1049,    73,    99,  1049,   870, -1751,
   -1751,  3713,  3760, -1751, -1751,  1049,  1049,   870,  1049, -1751,
    1093,  1498,  1049, -1751, -1751, -1751, -1751, -1751, -1751,  1584,
   -1751,   999, -1751, -1751, -1751, -1751,  1049,    87,   113,   125,
    1171, -1751,  1171, -1751, -1751, -1751,   442, -1751, -1751, -1751,
   -1751, -1751,  1049,  1216,  1437,  1437,   166, -1751, -1751, -1751,
   -1751,  1425, -1751, -1751, -1751,  1243,  1222,  2044,  1160, -1751,
    1049, -1751,   248, -1751,  1221,  1388, -1751,  1481, -1751, -1751,
   -1751, -1751,  1049,  1049,   890,   -45,   -45,  1588,  1381, -1751,
   -1751, -1751,  1496,   578, -1751,  1320,  1174,  1049,  1177,  1178,
    1320,   599,  1182,  1184,  1191,  1195,  1196,  1200,  1201,  1206,
    1177,  1504, -1751,  3889, -1751, -1751, -1751, -1751,  1432, -1751,
    1564, -1751, -1751, -1751,  1256, -1751,   599, -1751, -1751,  1235,
   -1751, -1751,    -9,   870,  1539,  1482, -1751,  1328,  1358,   837,
    1542,  3490,   866,   901,  1545,   187,  1235, -1751, -1751,    39,
   -1751, -1751, -1751,  1574, -1751, -1751, -1751,  1320,   108, -1751,
   -1751, -1751, -1751, -1751,  1284, -1751,    84,  1049, -1751,   238,
   -1751, -1751, -1751, -1751, -1751,  4159, -1751,  1282,  1546,  1632,
     781, -1751,  1290, -1751,  2720,  1548,   729,  1294,  1298,   389,
    1305,   679,  1529, -1751,  1358,  1529,  1049,  1570,  1283, -1751,
     778, -1751, -1751, -1751, -1751, -1751,  1471, -1751,   108, -1751,
      20, -1751,   130, -1751, -1751,   405,  1668,  3372, -1751, -1751,
    1049,  1577,  3936,  1049,  1547,   959,  1612, -1751,  1396,  1352,
    1455,  1529,   631, -1751,    -6, -1751, -1751, -1751, -1751,     5,
   -1751, -1751,  1216, -1751, -1751, -1751, -1751,    -9, -1751, -1751,
    1049, -1751,  1243,  1027, -1751, -1751, -1751, -1751,  1618,  1320,
    2044,  2044,  2044,    21,   873, -1751, -1751, -1751,  1141, -1751,
    2044, -1751, -1751,  1143, -1751,   248, -1751, -1751, -1751, -1751,
   -1751, -1751,  1288,   -45,  1620, -1751, -1751,   778,   828,  1301,
     377,    -2,  2044,  1337,  2044, -1751,  2044, -1751,  1978,  1302,
    2044,  2044,  2044,  2044,  2044,  2044,  2044,  2044, -1751, -1751,
   -1751,  4159,  1552, -1751, -1751,  1404,  1432,  3023,  2671,  1440,
    1509, -1751,   499, -1751, -1751, -1751,   717, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751,   628, -1751, -1751,   -68,  1583,
    1583,  1583,  1583, -1751, -1751,  4159,  4159, -1751, -1751,   152,
    1613,   846, -1751,  1315,   746, -1751,  1049, -1751,    93, -1751,
   -1751,  1392,  1580, -1751,   778,   163, -1751,   238, -1751, -1751,
   -1751, -1751,   132,  1354,   108, -1751, -1751,  4159, -1751, -1751,
   -1751, -1751,  1394, -1751, -1751, -1751, -1751,  1049,   -11, -1751,
    1095, -1751, -1751,  1358,    -9, -1751,  1550,   -27,   258, -1751,
   -1751,  1049,   258,  1364, -1751,  1141, -1751, -1751,    97,   425,
   -1751, -1751,  2057, -1751,  1701,  1540,  4159,  4159, -1751,  3983,
    1049, -1751,  1582, -1751, -1751,  4159,   778, -1751, -1751, -1751,
    1668,  1553,  1049, -1751,  1028, -1751,    55,   -27, -1751, -1751,
    1642, -1751, -1751, -1751,  1490, -1751, -1751,  1049,  1049, -1751,
    1049,  1575,   949,    -4, -1751,  4595,  1455, -1751,  1978,  1319,
    1319,   929, -1751, -1751, -1751,  2044,  2044,  2044,  2044,  2044,
    2044,  4758,   873,  1408, -1751, -1751,  1288,  1455, -1751, -1751,
   -1751,  1583, -1751, -1751,  1329,  1331, -1751,   778,  1583,  1556,
   -1751, -1751, -1751, -1751,  1208,  1583,  1508,  1508,  1508,   172,
    1549, -1751, -1751,   375, -1751,    59,   971,  1049,   903,   122,
    1318, -1751,  1141, -1751, -1751,   277,  1323,  1005,   596,  1326,
    1016,   153,   162,   789,  1330,  1083,  4047,    30,  4159,   108,
   -1751,  1443, -1751, -1751, -1751, -1751, -1751,  1139, -1751, -1751,
    1383, -1751, -1751,  1383, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,  1382,
     -11, -1751,   127,  1049,  1049,    66, -1751, -1751, -1751,     6,
     892,  1414, -1751, -1751,  1655, -1751,  1525, -1751,    26,  1046,
    1583,  1524, -1751, -1751,  1530, -1751, -1751, -1751,  1604,  4047,
     493, -1751, -1751, -1751,  2563, -1751,  1398, -1751, -1751, -1751,
   -1751, -1751,   152, -1751, -1751, -1751,  1455, -1751, -1751, -1751,
    1139, -1751, -1751, -1751, -1751, -1751, -1751, -1751,  1465,  1139,
   -1751,  1397, -1751,  1742, -1751, -1751, -1751,  1213, -1751,   778,
     898, -1751,    91,    60,   754,   108,   108,  4047,   510,  1113,
     870,  1661, -1751, -1751,  1788, -1751,  1624, -1751, -1751, -1751,
   -1751,  1550, -1751,  1049,   119,   628,   906,  1373,  1678, -1751,
    1374,   778,   807, -1751,   375, -1751, -1751, -1751,  4159,  1216,
     628, -1751, -1751, -1751, -1751,   -77,  1049,  4047,   523,  1409,
    1795,  1049,   625, -1751, -1751, -1751,  1510,  1507, -1751, -1751,
    1095, -1751,   145,   736, -1751, -1751, -1751,  1216,  1639, -1751,
   -1751,  1243, -1751, -1751, -1751,  1216, -1751, -1751, -1751, -1751,
    1508,  1142,  1216,  1659, -1751, -1751,  1508, -1751,  1243, -1751,
   -1751, -1751, -1751, -1751,  1049, -1751,  1049, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751,  1049,  1614,   754, -1751,
    1141, -1751, -1751,   971,   821,   821,  1319,  1319,  1319, -1751,
    1248, -1751,  1139, -1751,  1049, -1751,  1530, -1751, -1751,  1583,
   -1751, -1751, -1751,  1216, -1751, -1751,  1216, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751,    49, -1751, -1751, -1751,  1208, -1751,
   -1751, -1751,    -9,    -9,    -9, -1751, -1751, -1751, -1751, -1751,
    1177,  1328,  4824, -1751,  1049,  1177,  1177,  2044, -1751,  1177,
    1177,  1177,   420,  1177,  1177, -1751, -1751,  1557,  4047, -1751,
     108, -1751, -1751,  1534,  1536, -1751, -1751,  3220, -1751,   378,
      34, -1751, -1751, -1751, -1751,  1050, -1751,  1492, -1751,  1483,
   -1751, -1751, -1751, -1751, -1751, -1751,   325,   325,   325,   325,
    1216, -1751, -1751, -1751, -1751,  1161,  1216, -1751, -1751, -1751,
   -1751,   107, -1751,  1046, -1751, -1751, -1751, -1751, -1751, -1751,
    4159, -1751,  4159,   152, -1751, -1751, -1751,  2563, -1751,  1049,
    1699,  1395,   623,  1716,  1399,   140,   778, -1751, -1751,  1775,
   -1751, -1751, -1751, -1751,   898, -1751,  1656, -1751,  1216,  1551,
   -1751, -1751, -1751, -1751,  1342,   108, -1751,  4159,   168,   640,
   -1751, -1751, -1751,  1049,  4159,   584, -1751, -1751, -1751,  1692,
    1579, -1751,  1697, -1751,  1597, -1751, -1751, -1751, -1751,  1374,
   -1751, -1751, -1751,  1585,  1696,  1559,  1554,  1328, -1751,  4159,
     140, -1751,  1561, -1751,   778, -1751,  1732,  1457, -1751, -1751,
    1455, -1751,   757,  1837, -1751,  1022, -1751, -1751, -1751,  1243,
    1735,  1634,  1784,  4740,   363,  1216, -1751, -1751,   363, -1751,
    1216,  1222, -1751, -1751, -1751,  1668, -1751,  1342, -1751,  1458,
   -1751, -1751, -1751,   363,   363,    40,    40, -1751, -1751, -1751,
   -1751, -1751,  1414, -1751,  1258, -1751, -1751, -1751,   971, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751,  1703,  1705, -1751, -1751,  4159, -1751, -1751, -1751, -1751,
   -1751,  1726, -1751, -1751, -1751, -1751, -1751, -1751,  1583,  1583,
    1583,  1583,   363, -1751, -1751,   363,    40,    40, -1751, -1751,
   -1751,  4047,  1538,  4047,  1543, -1751, -1751, -1751, -1751, -1751,
    1727, -1751,   623, -1751,  1766, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751,   140,  1095, -1751, -1751,  1095,   137,  1049, -1751,
   -1751,  4047, -1751, -1751,   917,  3324, -1751,  1817,  1636,  1652,
     438, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751,  4159,   704, -1751, -1751, -1751,  1729,
    1608,  1049,  1414,  4047, -1751,  1795, -1751,  1324,  1780,  1324,
    1559,   443, -1751, -1751,  1730, -1751,  1617, -1751, -1751, -1751,
     444, -1751, -1751,  1216,  1789,  1663, -1751,   700, -1751,  1679,
     946,  1468,  1693,  1453,  1216,  1320,  1216,  1049, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
    1501, -1751, -1751, -1751, -1751,   869, -1751, -1751, -1751, -1751,
   -1751, -1751,   458, -1751,   461, -1751,  1451,  1216,  1216, -1751,
   -1751, -1751, -1751,   363, -1751, -1751, -1751, -1751, -1751,  1139,
    1139, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751,  4159, -1751,  4159, -1751,
   -1751, -1751, -1751, -1751,  1836,  1095,  1095, -1751,  1489,  1590,
     870,   517, -1751,  1049, -1751, -1751,  1563,  4159, -1751,  1216,
     857,  1658, -1751,  1664, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751,  1049,  1324, -1751,  1049,  1749,
   -1751, -1751, -1751, -1751, -1751,   870, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751,  1072,  1243,  1216,  1216,  1733, -1751,  1216,
   -1751, -1751, -1751, -1751,   166, -1751,  1216, -1751,  1049,  1049,
     619,  1725, -1751,  1621,  1243,   869, -1751, -1751, -1751, -1751,
   -1751, -1751,   363, -1751, -1751, -1751, -1751,   363, -1751,  1451,
   -1751,  1049,   248,  1072, -1751, -1751, -1751, -1751,  1414,  1414,
   -1751,  4159,  1095, -1751,  4159,  1216,   870,   870,  1606, -1751,
   -1751, -1751,  1493,  1049,  1777, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751,  1049, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751,  1243,  1243,  1216, -1751,  1243, -1751,
    1243, -1751,  1328, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751,  4159, -1751, -1751, -1751, -1751, -1751, -1751,
    1049, -1751, -1751, -1751, -1751, -1751, -1751,   -11,   870,  1216,
   -1751,  1049, -1751, -1751, -1751, -1751, -1751, -1751,  1243, -1751,
   -1751, -1751,  1865, -1751,   -11, -1751, -1751,  4159, -1751, -1751
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1751, -1751, -1751, -1751,  1910, -1751, -1751, -1751,   129, -1751,
   -1751, -1751, -1751, -1751,  1594, -1751, -1751, -1751,  1240, -1751,
   -1751,    74,  1902, -1751, -1751,  1872,   260, -1751, -1751, -1751,
   -1751, -1751,  1745,  1801, -1751, -1751,  1763,   635, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751,  1754, -1751, -1751, -1751, -1751,
    1736, -1751, -1751, -1751,   663, -1751, -1751, -1751, -1751,  1461,
   -1751, -1751,  1390,   843, -1751, -1751, -1751, -1751, -1751, -1751,
    1558, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751,  1806, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751,   641, -1751,   636,   863, -1751, -1751,
   -1751, -1751, -1751,  1054,   133, -1751,  1400, -1751, -1751, -1751,
   -1751, -1751, -1751,   182, -1751,  1746, -1751,  1854, -1751, -1751,
   -1751, -1751,  1605, -1751,   228, -1751, -1751, -1751, -1751,  1743,
   -1751,  1917,  1820, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751,  1147, -1751, -1751, -1751,  1444, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,   606, -1751,
   -1751, -1751,  1682, -1751,  -520,  -726, -1751, -1751, -1751,  -403,
   -1751, -1751, -1751, -1751, -1751, -1751, -1262, -1250,  1173, -1243,
     138, -1751, -1751, -1751, -1751,   359, -1751, -1751,  -183, -1236,
   -1751, -1751, -1235, -1751, -1234, -1751, -1751,  1057, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,  1473,
   -1751, -1751, -1751,  1082, -1751,  -867, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751,   -29, -1751, -1751, -1751, -1751, -1751, -1751,
    -155, -1751, -1751, -1751, -1751,  -131, -1751, -1751, -1751, -1751,
   -1751,  1223, -1751, -1751, -1751, -1751, -1751, -1751,   308, -1751,
   -1751, -1751, -1751, -1751,  1882,  1089, -1751,   304, -1751, -1751,
   -1751, -1751,  1560, -1751, -1751, -1751, -1751, -1751, -1751,  -629,
   -1751, -1751,   224, -1751, -1751, -1751, -1751,  1006,   648,   651,
   -1751, -1751,   354, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,  1009, -1751,
   -1751,   316, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
    -379, -1751,   284, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751,   804, -1751, -1751,   808, -1751, -1751, -1751,
   -1751,   538,   280, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,   104,
     806, -1751, -1751, -1751, -1751, -1751, -1751, -1751,   801, -1751,
   -1751, -1751,   265, -1751, -1751,   524, -1751, -1751, -1751, -1646,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1384,   986, -1751, -1751,   256, -1751, -1751,   512, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
     748, -1751, -1751, -1751, -1751, -1751, -1751, -1751,   785, -1751,
     251, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751,   988, -1751,   984, -1751, -1751,  1189, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751,   981,   497, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751,    85, -1751,   503,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751, -1751,  -783,
   -1751, -1141, -1751, -1751, -1055, -1156, -1074, -1751,   432, -1751,
   -1391, -1751, -1751, -1751, -1751,    81, -1751, -1751, -1751, -1751,
     -20, -1751, -1751,   281, -1751, -1751, -1751, -1751,    88, -1751,
    -847, -1609, -1751, -1751,   620, -1751,  -884, -1229,  -803, -1148,
   -1751, -1751, -1751, -1159, -1157, -1154, -1153, -1152,    15,  -164,
    -165,  -136, -1069,  -829,   252,  1019, -1458,   -83, -1751, -1052,
   -1751,  -763, -1751,   897,   -93,  -256, -1751,  -682,  -144,  -795,
    -977,  -558,  -664, -1751, -1751,   539,  -992, -1200,  -953,  -801,
   -1100,   787,  -584,  -231, -1751,  1154,  -233,  -627,  -668,  -277,
    -395,  -836, -1751, -1751, -1751, -1751, -1751,  1856, -1751,   513,
     911, -1751, -1751, -1751, -1621,  1279,   -65,  1792,   861,  -408,
   -1751,  1085,  -373,  1532, -1751,  -580, -1751, -1056,  1152,  -368,
      14, -1751, -1751,  -659, -1751, -1750,  -163,  -606,  -480,   -78,
    -757,  -174, -1310,  -802, -1173, -1751,  1333,  2040,  -665, -1751,
   -1751, -1751, -1751, -1751, -1751, -1751,   696, -1751,   259,  -661,
     968,  -127
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1540
static const yytype_int16 yytable[] =
{
     118,   183,   240,   436,   816,   807,   849,   328,  1083,   344,
     565,   996,   943,   349,   512,   351,   799,  1523,  1270,  1433,
    1279,  1434,   259,   260,  1435,  1436,  1437,   265,   266,   267,
     268,   269,   980,   271,   345,   274,   989,   881,   345,  1184,
     345,  1217,  1011,   261,  1465,  1466,  1467,  1663,  1664,  1217,
    1862,   270,   922,  1608,   778,   183,  1208,   824,  1026,  1514,
    1710,  1476,  1779,   410,  1567,  1609,   118,   318,  1263,   319,
     277,  1072,  1610,   984,   757,   399,   326,   529,  1741,  1611,
    1612,  1613,  1056,   904,   331,   411,   392,    21,   154,  1322,
    1017,   417,   154,   398,   416,  1217,  1353,   945,   340,   341,
     345,   342,  1386,  1017, -1539,  1017,   546,   350,   355,  1530,
     345,  1299,   272,   279,  1017,   338,   339,  1886,  1716,   345,
    1936,   438,   458,   347,   348,   154,  1776,  1322,   175,   354,
     356,   410,    84,   451,  1168,   374,  1017,  1469,   379,   381,
     433,   384,  1361,  1616,    40,    91,   345,   445,   345,   812,
     369,   154,   245,  1151,  1309,  1339, -1510,   393,  1158, -1503,
     453,   123,   369,   248,  1634,  1855,  1808,   634,  1517,   913,
     974,   779,  1502,  1471,   400,   154,   281,   770,   974,  1005,
     934,   525,    62,   442,   477, -1490,  1972,   479,   417,   563,
    1322,   514, -1539,  1037,  1039,   914,   915,   360,    88,   548,
    -182,    62,  1486,   641,   819, -1539,   345,  1079,   974,   419,
   -1467,  -737,   435,  1988, -1539,  1216,  1557,   983,  1503,  1183,
     447,  1322, -1463,  1906,  1703, -1539,  -183,  2115,  1031,  2118,
    1322,    53,  1501,   892,  1560,  1205,  1356,  1304,  1095,    40,
    1787,    54, -1503,  1310,  1060,   549,  1271,   235,   897,  1299,
   -1539, -1513,    31,   104,  1769,   450,   812,   812,   566,  1128,
    1061,   778,  1299,  1141,  1142,    18,  1061,  1636, -1467,   522,
     826,    17,  1257,  1268,  1636,   360,   758,   418,   426,   784,
    1835,  1636,  2075,   983,  1001,  2076,  1840,   819,   533,   534,
     633,  1217,   179,  1640,  1559,   638,   813,  1879,   803,  1362,
    1660,  1532,   643,   643,  1735,   934,   254,   553,  1297,  1173,
    1112,   373,   558,  1749,  1082,  -182,   380,  1318,    40,  1688,
     759,   983,  1717,   562,   559,    55, -1479,  1224,   785,   401,
      90,  1504,   164,  1195,  1476,     3,  1770,  1173,  2079,  1061,
      19,  -183,   996,  1305, -1539,  1322,  1704,    51,  1458,   569,
    1887,   105,   163,  1096,   179,  1639,   236,   628,  1138,  1139,
   -1467,  1102,   798,  1459,    63,   567,  2204,  1143,   402,  1193,
     801,  1233,  1323,  1788,   418,   403,  -594,   996,   779, -1463,
    1505,   -31,   249,    63,   572,  1335,  1700,   343,  1451,  1256,
     756,  1206,  1265, -1467,   916,   761,    74,   251,   765,   766,
     452,   767,   768,  1295,   179,   774,  1719,   343,   996, -1490,
    1323,  1011,  1689,  1079,  1269,    64,   370,   804,  1173, -1467,
     771,   343,   893,   343,   635,  1300,  -200,   563,  1582,  1823,
     343,  2182,   898,   179,   166,  -592,   401,   401,   900,  1516,
    1103,  1356,   991, -1467,   165,   246,   404,   806,   257, -1510,
     946,   528,  1128,  1128,  1128,  1488,   996, -1485,  1718,  1888,
    1032,  1336,  1128,  1856,  1358,   991,   814,  1209,  1324, -1467,
     894,  2045, -1467,  1323,    54,   402,   402,   772, -1467,  1265,
     547,  2196,   403,   403,  1128,  1527,  1128,   343,  1128,  -594,
    1372,  1542,  1128,  1128,  1128,  1128,  1128,  1128,  1128,  1128,
     459,   257, -1467,    85,  1323,   343,  1670,  1387,  1334,   405,
     825,   906,   907,  1323,  1438,   179,   343,  1759,   912,  -182,
    2065,  1907,  2067,  2125,  1272,   343,    88,   166, -1467,   343,
     544,   343,  1129,  1569,   345,   940,   345,   345,   406,  1217,
     343,  1468,  1470,   345,  1273,  -183,   325,  1472,  -592,  1800,
    2084,  1473, -1467,   404,   404,   917,  1265,   343,    55,   996,
    1225,  2080,   343,  1300,  1506,  1636,   901,  1364,  1961, -1419,
   -1513,  2009,   343,  1518,  1371, -1463,  1300,   343,   407,  1633,
    1144,  2112,  2113,  2010,  1852, -1539,  1276,  1583,  1531,   164,
    2011,   327,   891,  1313,   896,  1476,   949,  2013,  2014,  2015,
    1680,  2261,  1357,  1667,  2120,   987,   179,  1147,  1547,  1681,
    1974,   164,  1551,  1552,   921,  1554,   405,   405,  1265,   164,
     390,  1558,  2186,  1226,     4,  1034,   810,   869,  1323,  1049,
    2091,  1053,  1485,  1053,  1059,  1491,  1034,  1872,  1492,  1493,
    1094,  1700, -1463,   902,  2121,   406,   406,  1981,  1884,   991,
    1620,  1053,  2122,    74,   439,    87,  1105,  1128,  1128,  1128,
    1128,  1128,  1128,  1128,  1322,   345,   462,  1140,  1098,  1358,
    2092,  1911,   327,  1913,  1742,    74,   104,  1696,  1538,  1265,
    1443,   345,  1538,    74,  1061,   407,   407,  2139,  1792, -1427,
    2093,  1777,  1116,   456,   550,   391,   551,  2158,  2187,  1132,
    2163,   165,   291,  1804,  1809,   463,  2225,  2226,  1941,  1858,
    1859,  1860,   464,  1880,   345,   345,  1326,  1327,  1328,  1329,
    1775,  1330,  2123,   165, -1425,  1129,  1129,  1129,  2131,  2248,
    2227,   165,  2077,  1050,  1619,  1129,  1691,  1277,  2033,   870,
    1973,   232,  2056,  2057,  2058,  2059, -1479,  1093,  2159,     5,
    1107,  2164,  1148,  2040,  2041,   440,  1459,  1129,   998,  1129,
     481,  1129,  1124,  1373,  1931,  1129,  1129,  1129,  1129,  1129,
    1129,  1129,  1129,    12,   105,   482, -1539,  1948,  1051,  1669,
    1054,  1772, -1380,   466,   483,  1074,   233,  2243,  2244,  2036,
    1707,  1125,  1839,   413,  1085,   343,  2188,   241,  1217,  2043,
    2043,  2028,  2060, -1463,   244,  2061,  2101,   343,  2102,  1102,
     811,  2103,  2104,  2105,   281,    13, -1539,   245,   327,   243,
     883,  1873,  1976,     5,    22,  1059,   879,   329,   284,  1751,
      15,  1444,  1193,   290,  1861,  1452, -1539,   927,  1754,  1866,
    1867,  1265,  1265,  1869,  1870,  1871,   467,  1874,  1875,  1193,
    2043,  2043,  1340,  1341,  1748,  1397,  1398,  1322,   232,   884,
    1750,     5,  1193,  2263,  1773,  2094,   885,   414,  1494,  1495,
   -1463,   827, -1539,  1265,  -200,   115,   343,   244,   141,  1312,
    2268,   812,  2028,  1399,  1802,  1453,  1496,  1497,  1103,  1400,
    2133,   363, -1539,  1342,    25,  1343,  1159,  2160,  2161,  1222,
    2165,  2166,    28,   233,  2228,  2229,  1982,  1760,   297,   786,
    1186,  1912,   345,  1914, -1485,   470, -1539,  1050,  2221,   788,
    1402,  1180,   298,  1621,  1403, -1481,  1344,  1345,  1346,  1251,
    1129,  1129,  1129,  1129,  1129,  1129,  1129,   886,  2132,  1306,
      40,  1916,  1238,  2173,   790,  2230,  2231,  1323,   996, -1539,
     792,   956,   484,  1761,    32,  1319,  1320,  1321,   787,   299,
    1669,  1661,  2138,   184,  1452,  1332,   958,   401,   789, -1539,
     427,  1849,  2044,  1347,  1252,  1348,   185,   186,  1787,  1825,
     996,   485,  1239,  1349,  1125,  1125,  1125,   987,   486,  1368,
    1240,    92,  1959,   791,  1125,  1375,  1377,  1378,  1380,   793,
     887,  1383,  1385,    44,  1128,   375,   402,   376,   187,  1128,
      29, -1539,  1983,   403,  1453,   179,  1125,   987,  1125,   333,
    1125,  2265,  2062,  2063,  1125,  1125,  1125,  1125,  1125,  1125,
    1125,  1125,  1446,   487,    33,  1326,  1327,  1328,  1329,   488,
    1330,    45,   334, -1423,   188,   189,  1826,   190,  1827,    46,
     959,  1575,  1575,    93,  1350,   191,   179,   343,    35,  1450,
    1241,   401,  2237,   484,  1452,   987,   489,  2238,  1061,   888,
      40,   179,   115,   490,   388,   300,   345,   345,  1720,   401,
     137,  1721,  1896,  1897,   404,   301,   491,   401,  1265,  1722,
    1723,  1724,   485,    94,   389,    95,  1265,   327,   192,   193,
     402,  1087,   962,  1528,  1768,   963,    37,   403,  1909,   194,
     246,  1788,   808,   492,  1453,  1762,  1055,  1917,   402,  2153,
    1947,   493,    43,  1447,  1708,   403,   402,  1088,  1930,  1529,
    1536,  -205,   809,   403,  1091,   138,   139,   964,  1793,    48,
    1323,  1007,  1246,   184,  1709,  1008,  1265,   405,   179,  2085,
    1417,    49,   494,  1419,  1420,  1247,   185,   186,  1794,  2154,
    1623,  1624,  1625,  1626,  1627,  1628,  1630,  1365,    52,  2086,
    1536,  1369,   302,   303,  1579,  1580,   406,   762,   404,  1381,
    1382,   195,  1564,  1930,   763,   304,  1565,   305,   187,  1125,
    1125,  1125,  1125,  1125,  1125,  1125,   404,    58,   991,  1725,
      59,   495,  1545,  2149,   404,   965,  1546,  2142,  2143,   987,
     343,  1674,  1012,  1013,  1677,    67,   407,  1726,    60,  1682,
    1351,  2051,  1502,     5,   188,   189,  1014,   190,  1326,  1327,
    1328,  1329,    71,  1330,  1727,   191, -1420,  2178,  1642,  2179,
    1643,   405,    10,  1644,   231,    61,    10,  2047,   231,    74,
     966,   967,    80,  1645, -1372, -1372, -1372, -1372,    78,   405,
    1352,    81,  1328,  1329,  2055,  1330,   112,   405,  1503,  1287,
     406,  1288,  1015,   102,  1209,   968,  1479,  1129,   192,   193,
    1728,  2064,  1129,  1199,  1200,  1201,  1202,   306,   406,   194,
    1836,   113,  1837,   969,  1940,   196,   406,  2210,  2211,  1763,
    2100,   970,   115,   111,   343,  1930,  1889,   307,  1890,  1903,
     407,  1904,  1326,  1327,  1328,  1329,  1575,  1330, -1371, -1371,
   -1371, -1371,  2095,  2096,  1331,   121,  2251,  1729,   407,   125,
     343,  2098,  1826,   126,  1827,   197,   407,  1898,  1899,  1900,
    1901,   345,  1326,  1327,  1328,  1329,   130,  1330,  1832,   536,
     133,  -629,   127,  -629,  1672,   128,   461,   135,  -629,   129,
    1844,   195,   145,   132,   146,  1841,  -629,  2037,  1326,  1327,
    1328,  1329,   144,  1330,  -321,   160,  1622,   161,  1850,  1646,
    1730,  1504,   162,  1647,   198,   345,  1803,   175,  2175,  2176,
    1731,   213,  1778,   217,   219,   224,  1648,   275,  -629,  -629,
     216,  1490,  -949,   345,  1491,   223,  -629,  1492,  1493,   225,
    1326,  1327,  1328,  1329,  1829,  1330,   239,  -629,  1865,  2174,
    -629,   253,  1834,  2192,    40,  2177,   462,   256,  1806,  1838,
    1505,   257,  -629,   262,   263,  1806,   272,   279,   281,   286,
    2180,  -949,  1649,   345,  1326,  1327,  1328,  1329,  -949,  1330,
     287,  1732,  1676,   288,  -629,  1326,  1327,  1328,  1329,   293,
    1330,  -629,  -629,  1679,   320,   463,   321,   323,  2199,   645,
    2200,   327,   464,   330,   332,   196,   335,  2201,   346,   336,
    1853,   343,   365,  1854,   465,   366,   368,   382,   955,  1650,
     385,   812,  -629,   387,   394,   412,   395,  2208,  2209,   424,
     429,   430,  -333,   432,  -629,   434,   446,  1864,  -629,   448,
     515,   476,  1868,  1651,   526,   197,   523,  2245,   530,  -949,
    2246,  -629,  1326,  1327,  1328,  1329,   532,  1330,  -629,   554,
    1684,  -629,  -629,   555,   557,   560,  1125,  1652,  2219,  -629,
     568,  1125,  1653,   466,   179,  2241,  -629,   570,  -629,   630,
     632,  -629,  1654,   639,   563,   646,  1655,  1902,   754,   647,
     751,   956,   648,  1905,   198,   775,   783,   776,   796,  2262,
     802,   794,   831,  2254,   830,   873,   958,   905,   908,   911,
     925,   935,  -949,   924,   927,   930,  -629,   937,   941,   947,
    -629,   950,  -629,   944,   951,   978,  1992,  1006,  1023,  -629,
    1090,  1092,  1099,  2269,  1108,  1938,   467,  1114,  1130,   468,
     469,  -949,  1135,  1656,  1506,  1117,  1136,   819,  1145,  1176,
     953,  -629,  1152,  1657,   990,  1154,  1156,  1169,  2145,  1003,
    1160,  1174,  1161,  1189,  1020,  1021,  -629,  1494,  1495,  1162,
    1020,  1028,  1030,  1163,  1164,  -949,   956,   990,  1165,  1166,
    1179,  -949,  1944,  1020,  1167,  1496,  1497,  -629,  1950,  1181,
     959,   958,  1028,  1084,  1187,  1086,  -629,  1193,   762,  1196,
    1215,   401,  2032,  1203,  1219,   470,  1234,  2034,  1235,  -629,
    1237,  1244,  2082, -1374,  -629,  1248,  -629,  1326,  1327,  1328,
    1329,  1249,  1330,  1250,  -629,  1848,   426,  1326,  1327,  1328,
    1329,   960,  1330,  1254,  -629,  2046,   961,   345,  1259,  1261,
     402,  1061,   962,  -629,  1127,   963,   154,   403,  1283,  1290,
    1292,  1286,  -629,  1293,  -629,  -629,  1295,  1316,  -629,  1337,
    -629,  1367,  1354,  1388,  1374,  -629,  1389,   983,   956,  1041,
    1439,  1462,  1477,  1482,  1153,   959,  1500,   964,  1515,  1548,
    -629,  1519,  1549,   958,  1533,  -629,  1556,  1561,  1541,  1571,
    -629,  1573,  1577,  1330,  1631,  1673,  1637,  1638,  1641,  1661,
    1675,  -629,  1692,  1678,  1357,  1690,  1695,  1683,  1685,  1185,
     537,  1713,  1453,  -629,  1736,  1740,  1738,  1752,   404,  1744,
    1756,  1755,  2157,  -629,  1780,  1042,  1783,   962,  1784,  1796,
     963,  1795,  1797,  1810,  1811,  1020,  1821,  1830,  1819,  1881,
    1845,  1882,  1894,  1020,  1223,   965,  1877,   851,  1895,  1919,
    1921,  1925,  -892,  1932,  1927,  -892,  1935,  1939,  1953,  1958,
    2134,   990,   964,  1788,  1956,  1966,  1975,   959,  1963,  1968,
    1977,  2148,  1979,  2150,  1989,  1971,  1993,  1264,  1994,  1996,
    2052,   405,  2190,  2038,  2049,  1020,  2050,  2066,  2070,  1020,
     966,   967,  2068,  2073,  2089,  2087,  2109,  1282,  2088,  2107,
    1223,  2116,  1983,  2128,  2171,  2172,  2140,  2135,  2136,  2146,
     406,  2147,  2005,  2168,  2181,   968,  2183,   988,  2185,   962,
    2197,  2206,   963,  2224,  1185,  -892,  2198,  1028,  2191,  2233,
     965,  2213,  2216,   969,  2249,  2234,  2250,  1127,  1127,  1127,
    -892,   970,  2252,  2267,   343,   438,    14,  1127,   345,   397,
     407,  2235,  2157,    27,   964,    73,  2193,   255,  1190,   182,
     242,   252,  1543,   545,  1264,  1298,   276,   753,   215,  1127,
     345,  1127,  1572,  1127,  1576,   966,   967,  1127,  1127,  1127,
    1127,  1127,  1127,  1127,  1127, -1539,  1101,  1301,  1991,   764,
    1942,   142,   278,   423,   283,    66,   475,  -892,  -892,   227,
     968,  2012,  2214,  2215,   367,   948,  2218,  1847,   644,   931,
   -1000,  2256,  2257,  2220,   525,  2259,  2239,  2260,   969,  1134,
     573,  2152,   965, -1000,  -892,  -892,   970,  1111,   179,   343,
    2236,  -892,   159,  1885,   923,  -892,  1945,  1198,  1666,   345,
    1665,  1264,  1857,  1883,   535,  1207,   987,  1908,  1484,  1480,
    1747,  1020,  2247,  1915,  -892,  2266,  2072,  1499,  1511,  1934,
    1243,  1757,  -892,   987,  1526,  -892,  -892,   966,   967,  1946,
    -892,  1185,   426,  1785,  -892,  1570,  -892,  1540,  1539,  -892,
    1962,  -892,  1267,  2258,  1266,  1020,  1073,   956,  1281,  1817,
    2114,  2119,   968,   955,  -892,  1818,   812,  1555,  1851,  -892,
    2195,  1955,   958,  1264,  2130,  1258,  1715,  1441,  2240,  1563,
     969,  -892,  1131,  1801,   292,  1824,  2264,  1391,   970,  1137,
     939,   343,   378,  1513,  1214,  2242,    75,  1223,   769,  1694,
    2035,  1333,     0,   426,   910,     0,     0,     0,     0,     0,
       0,     0,  1127,  1127,  1127,  1127,  1127,  1127,  1127,     0,
       0,     0,  -892,   956,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1264,     0,   956,     0,   958,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -892,
       0,   958,     0,     0,  1671,     0,   959,     0,     0,     0,
       0,     0,     0,     0,     0,   426,     0,   401,     0,     0,
       0,     0,     0,     0,     0,     0,  1020,     0,     0,     0,
       0,     0,     0,     0,     0,  -892,     0,     0,     0,     0,
       0,     0,     0,     0,  -892,  -892,     0,     0,     0,     0,
       0,  1544,     0,     0,     0,     0,   402,     0,   962,     0,
       0,   963,     0,   403,  -892,     0,     0,     0,     0,  -892,
       0,     0,   959,     0,     0,     0,     0,     0,     0,     0,
    1701,  1702,     0,   401,     0,   959,     0,  -892,     0,     0,
       0,     0,     0,   964,     0,  -892,   401,     0,  -892,     0,
       0,     0,     0,     0,  -892,  -892,  -892,     0,     0,     0,
    -892,     0,  -892,  1119,  -892,  -892,  -892,     0,   961,     0,
       0,     0,   402,     0,   962,     0,   960,   963,     0,   403,
       0,   961,     0,     0,   404,   402,     0,   962,     0,     0,
     963,     0,   403,     0,     0,     0,  1264,  1264,     0,     0,
       0,     0,  1020,  1020,     0,     0,     0,     0,     0,   964,
       0,   965,     0,     0,  -589,   536,     0,  -629,     0,  -629,
    1786,     0,   964,     0,  -629,     0,     0,     0,  1264,     0,
       0,     0,  -629,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1807,     0,     0,     0,   405,  1816,  1816,
     404,     0,     0,     0,     0,     0,   966,   967,     0,     0,
       0,     0,     0,   404,  -629,  -629,     0,     0,     0,     0,
       0,     0,  -629,     0,     0,     0,   406,   965,     0,     0,
     990,   968,     0,  -629,     0,     0,  -629,     0,     0,     0,
     965,  1842,     0,  1843,     0,     0,     0,     0,  -629,   969,
       0,     0,     0,     0,     0,     0,     0,   970,     0,     0,
     343,     0,     0,   405,     0,     0,   407,     0,     0,     0,
    -629,     0,   966,   967,     0,     0,   405,  -629,  -629,     0,
       0,     0,     0,     0,     0,   966,   967,     0,     0,     0,
       0,     0,   406,     0,  -589,     0,     0,   968,  -589,  1185,
    1185,  1185,  1545,     0,     0,   406,  1546,     0,  -629,  1127,
     968,     0,     0,     0,  1127,   969,     0,     0,     0,     0,
    -629,     0,     0,   970,  -629,     0,   343,  1020,   969,     0,
       0,     0,   407,  1120,  1121,     0,   970,  -629,     0,   343,
       0,  -589,  1122,     0,  -629,   407,     0,  -629,  -629,     0,
       0,     0,     0,     0,     0,  -629,     0,     0,     0,     0,
       0,     0,  -629,     0,  -629,     0,     0,  -629,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1918,     0,     0,     0,
       0,     0,  1929,  1264,     0,     0,     0,     0,     0,     0,
       0,  1264,  -629,     0,     0,     0,  -629,     0,  -629,     0,
       0,     0,  1020,     0,     0,  -629,     0,     0,     0, -1455,
    1526,     0, -1455,     0,     0,     0,     0,     0,     0,     0,
    1208,     0,     0,     0, -1455,     0,     0,  -629,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1929,     0,     0,
       0,  1264,  -629,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -589,     0,     0,     0,
       0,  2030,     0,  -629,     0,  2030,     0,     0,     0,     0,
       0,     0,  -629,     0,     0,     0,     0,     0,     0,     0,
    2030,  2030, -1455,     0,     0,  -629,     0,     0,     0,     0,
    -629,     0,  -629,     0,     0,     0,     0, -1455,     0,     0,
    -629,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -629,     0,     0,     0,     0,     0,     0,   955,     0,  -629,
     812,     0,     0,     0,     0,     0,     0,     0,  -629,  2030,
    -629,  -629,  2030,     0,  -629,     0,  -629,     0,     0,     0,
       0,  -629,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0, -1455, -1455,  -629,     0,     0,  1929,
       0,  -629,     0,     0,     0,     0,  -629,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -629,     0,     0,
       0, -1455, -1455,     0,     0,     0,   537,     0, -1455,  -629,
     956,     0, -1455,     0,     0,     0,     0,     0,  2111,  -629,
       0,     0,     0,     0,     0,   958,     0,     0,     0,     0,
       0, -1455,     0,     0,     0,     0,     0,  2030,     0, -1455,
       0,     0, -1455, -1455,     0,     0,     0, -1455,     0,     0,
       0, -1455,     0, -1455,  2151,     0, -1455,     0, -1455,   956,
       0,     0,     0,     0,     0,   577,   578,   579,   580,   581,
     582, -1455,     0,     0,   958,     0, -1455,     0,     0,     0,
       0,     0,  1397,  1398,     0,     0,     0,     0, -1455,     0,
    2030,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     584,     0,   585,   586,   587,   588,   589,   590,     0,   959,
    1399,     0,     0,     0,     0,     0,  1400,     0,     0,     0,
     401,     0,     0,     0,     0,     0,     0,     0,     0, -1455,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1426,
       0,     0,   591,     0,     0,     0,     0,  1402,     0,     0,
     960,  1403,  1041,     0,     0,   961, -1455,     0,   959,   402,
       0,   962,  2203,     0,   963,  2205,   403,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1427,
       0,     0,     0,     0,  1428,     0,     0,     0,     0,     0,
       0,     0, -1455,     0,     0,  2222,   964,     0,     0,     0,
       0, -1455, -1455,     0,     0,     0,     0,     0,   988,  2030,
     962,     0,     0,   963,  2030,     0,     0,     0, -1455,     0,
       0, -1455, -1455,     0,   592,     0, -1455,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   404,     0,     0,
    1028,     0,     0,     0, -1455,   964,     0,     0,     0,     0,
       0,  2255, -1455,     0,     0, -1455,     0,     0,     0,     0,
       0, -1455, -1455, -1455,   965,     0,     0, -1455,     0, -1455,
       0, -1455, -1455, -1455,   594,   649,     0,   650,     0,     0,
       0,     0,   651,     0,     0,     0,     0,     0,     0,     0,
     652,     0,     0,     0,     0,  1392,  1393,  1394,  1223,     0,
     405,     0,     0,  1395,     0,     0,     0,     0,     0,   966,
     967,   596,     0,   965,     0,     0,     0,     0,     0,     0,
     598,     0,   653,   654,     0,     0,     0,     0,     0,   406,
     655,     0,     0,   599,   968,     0,     0,     0,     0,     0,
    1396,   656,     0,     0,   657,     0,     0,     0,     0,     0,
       0,     0,   969,     0,     0,     0,   658,     0,   966,   967,
     970,     0,     0,   343,     0,     0,     0,     0, -1539,   407,
    1429,  1430,     0,     0,     0,  1431,     0,  1417,   659,  1432,
    1419,  1420,     0,   968,     0,   660,   661,     0,     0,   603,
     604,   605,     0, -1000,     0,     0,     0,     0,     0,     0,
       0,   969,     0,     0,     0,     0, -1000,     0,     0,   970,
       0,   179,   343,     0,     0,     0,   662,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   663,     0,
       0,     0,   664,     0,  1397,  1398,     0,     0,   607,   608,
     609,     0,     0,     0,     0,   665,     0,     0,     0,     0,
       0,     0,   666,     0,     0,   667,   668,     0,     0,     0,
       0,     0,  1399,   669,     0,     0,     0,     0,  1400,     0,
     670,     0,   671,     0,     0,   672,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -760,     0,     0,  -760,
       0,  1401,     0,     0,     0,     0,     0,     0,     0,  1402,
       0,     0,     0,  1403,     0,     0,     0,     0,     0,     0,
     673,     0,     0,     0,   674,     0,   675,     0,     0,     0,
       0,     0,     0,   676,     0,     0,     0,     0,   154,     0,
       0,  1404,  1405,     0,     0,     0,  1406,     0,     0,     0,
       0,     0,     0,     0,     0,   677,  1407,     0,     0,     0,
       0,     0,     0,  1408,     0,     0,     0,     0,  1409,  -760,
     678,     0,     0, -1467,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -760,     0,  1410,     0,     0,     0,
       0,   679,     0,     0,     0,     0,     0,   649,     0,   650,
     680,     0,     0,     0,   651,     0,     0,     0,     0,     0,
       0,     0,   652,   681,     0,     0,     0,     0,   682,     0,
     683,     0,     0,     0,     0,     0,     0,     0,   684,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   685,     0,
       0,     0,     0,     0,   653,   654,     0,   686,   955,     0,
       0,   812,   655,     0,     0,     0,   687,     0,   688,   689,
       0,     0,   690,   656,   691,     0,   657,     0,  -760,   692,
       0,     0,     0,     0,     0,     0,     0,     0,   658,  -760,
       0,     0,     0,     0,   693,     0,     0,     0,     0,   694,
       0,     0,     0,     0,   695,     0,     0,     0,     0,     0,
     659,     0,     0,     0,     0,   696,     0,   660,   661,  -760,
       0,     0,     0,     0,  -760,     0,     0,   697,  -760,     0,
    -760,   956,     0,  -760,     0,  -760,     0,   698,     0,     0,
       0,  1411,  1412,  1413,  1414,  1415,   958,  1416,   662,  1417,
    1418,     0,  1419,  1420,     0,     0,     0,     0,     0,  1076,
     663,     0,     0,     0,   664,  -760,     0,     0,     0,     0,
    -760,     0,     0,     0,     0,     0,   955,   665,     0,   812,
       0,     0,     0,     0,   666,     0,     0,   667,   668,     0,
       0,     0,     0,     0,     0,   669,     0,     0,     0,  1147,
       0,     0,   670,     0,   671,     0,  -760,   672,     0,     0,
       0,     0,     0,     0,     0,     0, -1467,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     959,     0,     0,  -760, -1463,     0,     0,     0,     0,     0,
       0,   401,   673,     0,     0,     0,   674,     0,   675,   956,
       0,     0,     0,     0,     0,   676,  1280,     0,     0,     0,
       0,     0,     0,  -760,   958,     0,     0,     0,     0,  -760,
       0,   960,     0,     0,     0,     0,   961,   677,  -760,  -760,
     402,     0,   962,     0,     0,   963,     0,   403,   955,     0,
       0,   812,   678,     0,     0,     0,     0,     0,  -760,     0,
       0,     0,     0,  -760,     0,     0,     0,     0,  -760,     0,
       0,     0,     0,   679,     0,     0,     0,   964,     0,     0,
       0,  -760,   680,     0,     0, -1467,     0,     0,     0,  -760,
       0,     0,  -760,     0,     0,   681,     0,     0,  -760,     0,
     682,     0,   683,     0,     0,     0,     0,     0,   959,     0,
     684,     0,   955,     0,     0,   812,     0,     0,   404,   401,
     685,   956,     0,     0,     0,     0,     0,     0,     0,   686,
       0,     0,   957,     0,     0,     0,   958,     0,   687,     0,
     688,   689,     0,     0,   690,   965,   691,     0,     0,   960,
       0,   692,     0,     0,   961, -1463,     0,     0,   402,   955,
     962,     0,   812,   963,     0,   403,   693,     0,     0,     0,
       0,   694,     0,     0,     0,     0,   695,     0,     0,     0,
       0,   405,     0,     0,     0,   956,     0,   696,     0,     0,
     966,   967,     0,     0,     0,   964,  1035,     0,     0,   697,
     958,     0,     0,     0,     0,     0,   955,     0,     0,   812,
     406,     0,     0,     0,     0,   968,     0,     0,     0,     0,
     959,     0, -1463,     0,     0,     0,     0,     0,     0,     0,
       0,   401,   956,   969,     0,     0,   404,     0,     0,     0,
       0,   970,     0,     0,   343,     0,     0,   958,     0,     0,
     407,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1076,   960,     0,   965,     0,     0,   961,     0,     0,     0,
     402,     0,   962,     0,     0,   963,     0,   403,     0,   956,
       0,     0,     0,     0,   959,     0,     0,     0,     0,     0,
    1080,     0,     0,     0,   958,   401,     0,     0,     0,   405,
       0,     0,     0,     0,     0,     0,     0,   964,   966,   967,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   960,     0,     0,   406,     0,
     961,   959,     0,   968,   402,   955,   962,     0,   812,   963,
       0,   403,   401,     0,     0,     0,     0,     0,   404,     0,
       0,   969,     0,     0,     0,     0,     0,     0,     0,   970,
       0,     0,   343,     0,     0,     0,     0,     0,   407,     0,
       0,   964,   960,     0,     0,   965,     0,   961,   959,     0,
       0,   402,   955,   962,     0,   812,   963,     0,   403,   401,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   956,     0,
       0,   405,   404,     0,     0,     0,     0,     0,   964,   960,
     966,   967,     0,   958,   961,     0,     0,     0,   402,   955,
     962,     0,   812,   963,     0,   403,     0,     0,     0,   965,
     406,     0,     0,     0,     0,   968,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   956,     0,     0,     0,   404,
       0,     0,     0,   969,     0,   964,     0,     0,     0,     0,
     958,   970,     0,     0,   343,   405,     0,     0,     0,     0,
     407,     0,     0,     0,   966,   967,   965,     0,     0,     0,
       0,     0,     0,   955,     0,     0,   812,     0,     0,     0,
       0,     0,   956,     0,   406,     0,   404,   959,     0,   968,
       0,     0,     0,     0,     0,     0,     0,   958,   401,     0,
       0,     0,   405,     0,     0,     0,     0,   969,     0,     0,
       0,   966,   967,   965,     0,   970,     0,     0,   343,     0,
       0,     0,     0,     0,   407,     0,     0,     0,   960,     0,
    1285,   406,     0,   961,   959,     0,   968,   402,     0,   962,
       0,     0,   963,     0,   403,   401,   956,     0,     0,   405,
       0,     0,     0,     0,   969,     0,     0,     0,   966,   967,
       0,   958,   970,     0,     0,   343,     0,     0,     0,     0,
       0,   407,     0,     0,   964,   960,     0,     0,   406,     0,
     961,   959,     0,   968,   402,   955,   962,     0,   812,   963,
       0,   403,   401,     0,     0,     0,     0,     0,     0,     0,
       0,   969,     0,     0,     0,     0,     0,     0,     0,   970,
       0,     0,   343,     0,     0,   404,     0,     0,   407,     0,
       0,   964,   960,     0,     0,     0,     0,   961,     0,     0,
       0,   402,     0,   962,     0,     0,   963,     0,   403,     0,
       0,     0,   965,     0,     0,   959,     0,     0,     0,     0,
       0,   955,     0,     0,   812,     0,   401,     0,   956,     0,
       0,     0,   404,     0,     0,     0,     0,     0,   964,     0,
       0,     0,     0,   958,     0,     0,     0,     0,   405,     0,
       0,     0,     0,     0,     0,     0,   960,   966,   967,   965,
       0,   961,     0,     0,     0,   402,     0,   962,     0,     0,
     963,     0,   403,  1171,     0,     0,     0,   406,     0,   404,
       0,     0,   968,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   956,   405,     0,     0,     0,     0,
     969,     0,   964,     0,   966,   967,   965,     0,   970,   958,
       0,   343,     0,     0,     0,     0,     0,   407,     0,     0,
       0,     0,     0,     0,   406,     0,     0,   959,     0,   968,
       0,     0,     0,     0,     0,     0,  1553,     0,   401,     0,
       0,     0,   405,   404,     0,     0,     0,   969,     0,     0,
       0,   966,   967,     0,     0,   970,     0,     0,   343,     0,
       0,     0,     0,     0,   407,     0,     0,     0,   960,     0,
     965,   406,     0,   961,     0,     0,   968,   402,     0,   962,
       0,     0,   963,     0,   403,     0,     0,     0,     0,     0,
       0,     0,     0,   959,   969,     0,     0,     0,     0,     0,
       0,  1685,   970,     0,   401,   343,   405,     0,     0,     0,
       0,   407,     0,     0,   964,   966,   967,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   960,   406,     0,     0,     0,   961,
     968,     0,     0,   999,     0,   962,     0,     0,   963,     0,
     403,     0,     0,     0,     0,   404,     0,     0,   969,     0,
       0,     0,     0,     0,     0,     0,   970,     0,     0,   343,
       0,     0,     0,     0,     0,   407,     0,     0,     0,     0,
     964,   575,   965,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   576,     0,     0,   577,   578,   579,   580,
     581,   582,   583,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   405,     0,
       0,   404,     0,     0,     0,     0,     0,   966,   967,     0,
       0,   584,     0,   585,   586,   587,   588,   589,   590,     0,
       0,     0,     0,     0,     0,     0,     0,   406,   965,     0,
       0,     0,   968,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     969,     0,     0,   591,     0,     0,     0,     0,   970,     0,
       0,   343,     0,     0,   405,     0,     0,   407,     0,     0,
       0,     0,     0,   966,   967,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   406,     0,  1584,     0,  1585,   968,     0,
    1586,   577,   578,   579,   580,   581,   582,   583,  1587,  1588,
    1589,     0,     0,     0,     0,     0,   969,     0,     0,     0,
       0,     0,     0,     0,   970,     0,     0,   343,     0,  1590,
       0,     0,     0,   407,     0,   592,   584,     0,   585,   586,
     587,   588,   589,   590,     0,     0,     0,     0,    40,     0,
       0,   593,     0,     0,     0,     0,     0, -1520,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   591,     0,
       0,     0,     0,     0,     0,   594,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   595,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1591,     0,
       0,     0,   596,     0,     0,     0,     0,     0,     0,   597,
       0,   598,     0,     0,     0,     0,  1592,     0,     0,  1593,
    1594,     0,     0,     0,   599,     0,   577,   578,   579,   580,
     581,   582,   583,  1595,   600,     0,     0,     0,     0,     0,
     592,   601,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1997,  1998,   593,     0,     0,     0,
       0,   584,     0,   585,   586,   587,   588,   589,   590,     0,
    1596,     0,     0,     0,     0,     0,     0,     0,   602,  1597,
     603,   604,   605,     0,     0,     0,     0,   956,     0,     0,
     594,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   958,   591,   606,     0,     0,     0,     0,     0,
       0,     0,  1598,     0,     0,     0,     0,     0,     0,     0,
       0, -1520,     0,     0,     0,     0,  1599,   596,     0,   607,
     608,   609,     0,     0,   597,     0,   598,     0,     0,     0,
       0,     0,   610,     0,     0,   611,     0,     0,     0,   599,
    1600,     0,     0,   956,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -328,     0,     0,   958,     0,
       0,     0,     0,     0,  1601,     0,  1999,     0,     0,  1602,
       0,     0,     0,     0,     0,   592,   959,     0,     0,     0,
       0,     0,     0,  1603,     0,     0,     0,   401,     0,     0,
       0,   593,     0,   602,     0,   603,   604,   605,     0,     0,
       0,     0,     0,     0,     0,  2000,  2001,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1119,     0,     0,
       0,     0,   961,     0,     0,   594,   402,     0,   962,  1604,
    2002,   963,     0,   403,     0,     0,     0,     0,     0,     0,
    1605,     0,   959,     0,   607,   608,   609,   595,     0,     0,
       0,     0,     0,   401,     0,     0,     0,   610,     0,  1606,
     611,     0,   596,   964,     0,     0,     0,     0,     0,   597,
       0,   598,     0,     0,  2003,     0,     0,     0,     0,     0,
    1607,     0,     0,  1119,   599,     0,     0,     0,   961,     0,
       0,     0,   402,     0,   962,     0,     0,   963,     0,   403,
       0,     0,     0,     0,   404,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   964,
       0,   965,     0,     0,     0,     0,     0,     0,   602,     0,
     603,   604,   605,     0,     0,     0,     0,  2004,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2005,     0,     0,     0,     0,     0,   405,     0,     0,
     404,     0,     0,     0,     0,     0,   966,   967,     0,     0,
       0,     0,     0,     0,  2006,     0,     0,     0,     0,   607,
     608,   609,     0,     0,     0,     0,   406,   965,     0,     0,
       0,   968,   610,     0,     0,   611,  2007,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   969,
       0,     0,     0,     0,     0,  2008,     0,   970,     0,     0,
     343,     0,     0,   405,     0,     0,   407,  1120,  1121,     0,
       0,     0,   966,   967,     0,  1629,  1122,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   406,     0,     0,     0,     0,   968,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   969,     0,     0,     0,     0,
       0,     0,     0,   970,     0,     0,   343,     0,     0,     0,
       0,     0,   407,  1120,  1121,     0,     0,     0,     0,     0,
       0,  1863,  1122
};

static const yytype_int16 yycheck[] =
{
      83,   128,   165,   376,   631,   611,   667,   240,   875,   265,
     490,   840,   814,   269,   422,   271,   600,  1246,  1070,  1178,
    1076,  1178,   185,   186,  1178,  1178,  1178,   190,   191,   192,
     193,   194,   835,   196,   265,   198,   837,   696,   269,   992,
     271,  1018,   845,   187,  1200,  1201,  1202,  1357,  1358,  1026,
    1671,   195,   778,  1315,   574,   182,    17,   637,   853,  1232,
    1451,  1209,  1520,   340,     9,  1315,   149,   230,  1060,   232,
     214,   866,  1315,   836,   554,   331,   239,   445,  1469,  1315,
    1315,  1315,     9,   765,   247,   341,   319,    13,    48,    68,
       6,    22,    48,   326,   350,  1072,  1148,    47,   261,   262,
     331,   264,  1171,     6,   102,     6,    17,   270,    92,  1250,
     341,   117,    55,    82,     6,   259,   260,    83,    92,   350,
    1766,   377,    55,   267,   268,    48,  1517,    68,   176,   273,
     274,   408,    53,   165,   970,   298,     6,  1206,   301,   302,
     373,   304,   144,  1316,   208,    71,   377,   380,   379,     9,
     166,    48,    61,   955,  1107,  1147,    61,   320,   960,    27,
     393,    87,   166,     9,  1337,   116,  1557,    55,  1237,    59,
     834,   574,     9,    21,   337,    48,   170,     9,   842,   843,
     807,   437,   163,   228,   415,   208,  1807,   420,    22,   212,
      68,   424,   260,   857,   858,    85,    86,   280,    69,   476,
     113,   163,   109,   228,    29,   232,   437,   871,   872,   353,
      83,   181,   375,  1822,   291,  1017,  1285,   228,    55,   228,
     383,    68,    47,   116,   158,   252,   113,  1977,   855,  1979,
      68,    70,  1224,   118,  1290,    48,    64,   232,   113,   208,
     121,   313,   110,  1110,   145,   478,   116,   316,   112,   117,
     166,    36,    24,   243,   194,   386,     9,     9,   491,   927,
     240,   781,   117,   945,   946,   228,   240,  1341,   228,   432,
     638,    11,  1055,  1068,  1348,   358,   118,   208,   361,   359,
    1590,  1355,  1928,   228,   842,  1931,  1596,    29,   451,   452,
     523,  1268,   431,  1348,  1286,   528,    49,  1688,   218,   301,
    1355,  1254,   533,   534,  1460,   932,   445,   481,  1091,   973,
     916,   297,   486,  1486,   872,   228,   302,  1119,   208,  1388,
     162,   228,   296,   108,   487,   397,   320,    89,   408,   189,
      70,   168,   237,   998,  1482,     0,   276,  1001,   201,   240,
     303,   228,  1171,   338,   169,    68,   280,    39,   416,   512,
     316,   341,   124,   228,   431,  1347,   425,   520,   942,   943,
     316,   367,   595,   431,   345,   492,  2116,   947,   228,   339,
     601,  1035,   351,   254,   208,   235,   332,  1206,   781,   121,
     217,   445,   228,   345,   515,  1142,  1442,   432,  1191,  1054,
     553,   204,  1060,   316,   284,   558,   301,   445,   561,   562,
     432,   564,   565,   271,   431,   568,  1458,   432,  1237,   432,
     351,  1214,  1389,  1077,   394,   396,   432,   337,  1082,   316,
     252,   432,   307,   432,   312,   431,   432,   212,   432,  1570,
     432,  2077,   296,   431,   432,   332,   189,   189,    31,  1234,
     446,    64,   837,   316,   349,   354,   306,   610,   432,   354,
     400,   394,  1120,  1121,  1122,  1218,  1285,   426,   432,   425,
     855,  1143,  1130,   414,   292,   860,   219,   428,   447,   425,
     355,  1862,   432,   351,   313,   228,   228,   309,   438,  1147,
     391,  2090,   235,   235,  1152,  1248,  1154,   432,  1156,   445,
    1158,   394,  1160,  1161,  1162,  1163,  1164,  1165,  1166,  1167,
     433,   432,   425,   424,   351,   432,   447,  1171,  1135,   369,
     637,   767,   768,   351,  1178,   431,   432,  1509,   774,   432,
    1911,   414,  1913,  1981,   394,   432,   397,   432,   425,   432,
     456,   432,   927,  1296,   765,   812,   767,   768,   398,  1516,
     432,  1205,  1206,   774,   414,   432,   238,   395,   445,  1541,
    1941,   399,   425,   306,   306,   445,  1224,   432,   397,  1388,
     322,   424,   432,   431,   401,  1639,   159,  1151,  1797,   447,
     355,  1833,   432,  1237,  1158,   400,   431,   432,   438,  1336,
     948,  1972,  1973,  1833,  1639,   260,   181,  1313,  1253,   237,
    1833,   228,   755,  1113,   757,  1743,   829,  1833,  1833,  1833,
     447,  2222,   225,   228,   161,   836,   431,    29,  1272,   447,
    1810,   237,  1276,  1277,   777,  1279,   369,   369,  1286,   237,
      30,  1285,  2080,   385,   177,   856,   217,   228,   351,   860,
     192,   862,  1216,   864,   865,    12,   867,   217,    15,    16,
     896,  1697,    64,   236,   201,   398,   398,  1820,   270,  1044,
    1318,   882,   209,   301,   270,   134,   912,  1325,  1326,  1327,
    1328,  1329,  1330,  1331,    68,   896,   189,   944,   899,   292,
     232,  1740,   228,  1742,   181,   301,   243,  1440,  1258,  1347,
     181,   912,  1262,   301,   240,   438,   438,  1997,  1535,   432,
     252,   181,   925,   134,   269,   105,   271,   239,   181,   930,
     239,   349,   445,  1550,   181,   228,    87,    88,  1777,  1662,
    1663,  1664,   235,  1690,   945,   946,   439,   440,   441,   442,
    1515,   444,   279,   349,   447,  1120,  1121,  1122,   284,  2187,
     111,   349,  1932,   860,  1318,  1130,  1397,   332,  1838,   340,
    1809,   363,  1898,  1899,  1900,  1901,   102,   891,   290,   302,
     913,   290,   174,  1853,  1854,   371,   431,  1152,   841,  1154,
       4,  1156,   927,  1158,  1756,  1160,  1161,  1162,  1163,  1164,
    1165,  1166,  1167,   445,   341,    19,   192,   193,   861,  1363,
     863,    27,   393,   306,    28,   868,   408,  2178,  2179,  1845,
    1449,   927,  1593,   194,   877,   432,   279,   445,  1775,  1855,
    1856,   438,  1902,   225,   169,  1905,  1965,   432,  1965,   367,
     401,  1965,  1965,  1965,   170,   445,   232,    61,   228,   445,
     189,   401,  1814,   302,   115,  1056,   182,   445,   222,  1490,
     145,   332,   339,   227,  1670,   207,   252,   448,  1499,  1675,
    1676,  1509,  1510,  1679,  1680,  1681,   369,  1683,  1684,   339,
    1906,  1907,    24,    25,  1483,   151,   152,    68,   363,   228,
    1489,   302,   339,  2247,   110,   427,   235,   268,   245,   246,
     292,   174,   232,  1541,   432,   432,   432,   242,   445,  1112,
    2264,     9,   438,   179,  1548,   257,   263,   264,   446,   185,
    1990,   285,   252,    65,    26,    67,   961,   439,   440,  1026,
     439,   440,   445,   408,   285,   286,   149,     9,    46,   359,
     993,  1740,  1143,  1742,   182,   438,   291,  1044,  2147,   359,
     216,   986,    60,  1318,   220,   228,    98,    99,   100,   250,
    1325,  1326,  1327,  1328,  1329,  1330,  1331,   306,  1990,  1102,
     208,  1744,   161,  2043,   359,   326,   327,   351,  1777,   232,
     359,    79,   196,    55,   228,  1120,  1121,  1122,   408,    97,
    1544,   261,   262,    11,   207,  1130,    94,   189,   408,   252,
     364,  1632,  1856,   145,   295,   147,    24,    25,   121,   243,
    1809,   225,   201,   155,  1120,  1121,  1122,  1218,   232,  1154,
     209,   266,  1795,   408,  1130,  1160,  1161,  1162,  1163,   408,
     369,  1166,  1167,   164,  1672,   310,   228,   312,    56,  1677,
      97,   427,   255,   235,   257,   431,  1152,  1248,  1154,   205,
    1156,  2250,  1906,  1907,  1160,  1161,  1162,  1163,  1164,  1165,
    1166,  1167,   315,   277,   445,   439,   440,   441,   442,   283,
     444,   202,   228,   447,    92,    93,   310,    95,   312,   210,
     178,  1307,  1308,   328,   226,   103,   431,   432,    80,  1186,
     279,   189,  2162,   196,   207,  1296,   310,  2167,   240,   438,
     208,   431,   432,   317,   162,   213,  1307,  1308,    32,   189,
     310,    35,  1711,  1712,   306,   223,   330,   189,  1756,    43,
      44,    45,   225,   368,   182,   370,  1764,   228,   146,   147,
     228,     8,   230,     8,  1512,   233,   115,   235,  1737,   157,
     354,   254,   162,   357,   257,   217,   864,  1746,   228,   250,
    1784,   365,   347,   406,   232,   235,   228,    34,  1755,    34,
    1257,   375,   182,   235,   882,   365,   366,   265,   232,   445,
     351,   395,   413,    11,   252,   399,  1814,   369,   431,   232,
     446,   298,   396,   449,   450,   426,    24,    25,   252,   290,
    1325,  1326,  1327,  1328,  1329,  1330,  1331,  1152,   445,   252,
    1297,  1156,   310,   311,   225,   226,   398,   310,   306,  1164,
    1165,   229,   154,  1810,   317,   323,   158,   325,    56,  1325,
    1326,  1327,  1328,  1329,  1330,  1331,   306,   445,  1593,   153,
     445,   445,   395,  2005,   306,   333,   399,   261,   262,  1440,
     432,  1375,   287,   288,  1378,   115,   438,   171,   347,  1383,
     392,  1885,     9,   302,    92,    93,   301,    95,   439,   440,
     441,   442,   130,   444,   188,   103,   447,  2066,    30,  2068,
      32,   369,     2,    35,   155,   445,     6,  1876,   159,   301,
     378,   379,   347,    45,   417,   418,   419,   420,   445,   369,
     432,   434,   441,   442,  1893,   444,   347,   369,    55,   310,
     398,   312,   347,   164,   428,   403,   430,  1672,   146,   147,
     234,  1910,  1677,   417,   418,   419,   420,   425,   398,   157,
     148,   231,   150,   421,  1774,   343,   398,   225,   226,   401,
    1964,   429,   432,   445,   432,  1932,   256,   445,   258,   148,
     438,   150,   439,   440,   441,   442,  1572,   444,   417,   418,
     419,   420,  1951,  1952,   451,   332,  2193,   281,   438,   445,
     432,  1960,   310,   445,   312,   383,   438,  1716,  1717,  1718,
    1719,  1572,   439,   440,   441,   442,   350,   444,  1581,     1,
     210,     3,   445,     5,   451,   445,   119,   396,    10,   445,
    1616,   229,   347,   445,   227,  1598,    18,  1847,   439,   440,
     441,   442,   445,   444,   432,   432,   447,   445,  1634,   171,
     334,   168,   445,   175,   432,  1616,  1549,   176,  2049,  2050,
     344,   274,  1519,   386,    23,   347,   188,   445,    50,    51,
     445,     9,   189,  1634,    12,   445,    58,    15,    16,   323,
     439,   440,   441,   442,  1577,   444,   363,    69,  1674,  2048,
      72,   445,  1585,  2087,   208,  2054,   189,   102,  1555,  1592,
     217,   432,    84,   375,   358,  1562,    55,    82,   170,   445,
    2069,   228,   234,  1674,   439,   440,   441,   442,   235,   444,
     347,   405,   447,   342,   106,   439,   440,   441,   442,   432,
     444,   113,   114,   447,   363,   228,   274,   104,  2097,   121,
    2099,   228,   235,   354,   205,   343,   445,  2106,    66,   241,
    1643,   432,   445,  1646,   247,   347,   445,   241,     6,   281,
      22,     9,   144,   268,   432,   228,   445,  2126,  2127,   292,
     445,   445,    81,    81,   156,   432,   426,  1672,   160,   432,
     308,   391,  1677,   305,   226,   383,   394,  2181,   194,   306,
    2184,   173,   439,   440,   441,   442,   432,   444,   180,   310,
     447,   183,   184,   394,   355,    54,  1672,   329,  2144,   191,
     375,  1677,   334,   306,   431,  2172,   198,    36,   200,    26,
     182,   203,   344,   363,   212,   445,   348,  1720,   375,   445,
     445,    79,   347,  1726,   432,   432,   219,   355,   337,  2233,
     208,   428,   228,  2202,   104,   297,    94,   372,   278,   272,
     394,    26,   369,   438,   448,   391,   238,   353,   268,   169,
     242,   445,   244,   452,   445,   432,  1829,   228,   131,   251,
     102,    17,   431,  2267,   167,  1768,   369,   182,   448,   372,
     373,   398,   391,   405,   401,   393,   228,    29,   122,    55,
     833,   273,   448,   415,   837,   448,   448,   123,  2001,   842,
     448,   199,   448,   151,   847,   848,   288,   245,   246,   448,
     853,   854,   855,   448,   448,   432,    79,   860,   448,   448,
     394,   438,  1779,   866,   448,   263,   264,   309,  1785,   424,
     178,    94,   875,   876,   125,   878,   318,   339,   310,   127,
      96,   189,  1835,   128,   390,   438,   394,  1840,   132,   331,
      48,   133,  1938,   393,   336,   391,   338,   439,   440,   441,
     442,   393,   444,   388,   346,   447,  1779,   439,   440,   441,
     442,   219,   444,   174,   356,   447,   224,  1938,   138,   426,
     228,   240,   230,   365,   927,   233,    48,   235,   141,   107,
     324,   174,   374,   371,   376,   377,   271,   109,   380,   109,
     382,   394,   431,   181,   432,   387,   332,   228,    79,   172,
     300,   158,   129,   428,   957,   178,   166,   265,   394,    48,
     402,   357,   212,    94,   204,   407,   174,   204,   394,   117,
     412,   271,   187,   444,   356,   447,   437,   436,   212,   261,
     447,   423,   389,   447,   225,   332,   394,   447,   364,   992,
     432,   126,   257,   435,   260,   181,   256,   322,   306,   391,
      48,   394,  2025,   445,   133,   228,     8,   230,   174,   121,
     233,   428,   428,   394,     9,  1018,   299,   168,   298,   275,
     196,   275,   320,  1026,  1027,   333,   259,     1,   335,   120,
     425,   105,     6,    48,   425,     9,   170,   276,   136,   232,
    1993,  1044,   265,   254,   137,   139,   275,   178,   253,   280,
     108,  2004,   385,  2006,     7,   291,   111,  1060,   214,    65,
     124,   369,  2083,   395,   151,  1068,   151,   319,   131,  1072,
     378,   379,   319,    97,   212,    48,   258,  1080,   232,   140,
    1083,    91,   255,   143,  2037,  2038,   197,    88,   215,   186,
     398,   428,   381,   432,    48,   403,   397,   228,   298,   230,
     232,   142,   233,  2149,  1107,    79,   232,  1110,   335,   174,
     333,  2134,   169,   421,   298,   284,   413,  1120,  1121,  1122,
      94,   429,   135,    48,   432,  2171,     6,  1130,  2149,   325,
     438,  2154,  2155,    21,   265,    53,  2089,   182,   446,   128,
     167,   177,  1269,   472,  1147,  1092,   200,   547,   132,  1152,
    2171,  1154,  1301,  1156,  1308,   378,   379,  1160,  1161,  1162,
    1163,  1164,  1165,  1166,  1167,   388,   902,  1094,  1825,   559,
    1778,   107,   216,   358,   221,    48,   408,   151,   152,   149,
     403,  1833,  2135,  2136,   292,   828,  2139,  1618,   534,   806,
     413,  2214,  2215,  2146,  2240,  2218,  2169,  2220,   421,   932,
     517,  2020,   333,   426,   178,   179,   429,   915,   431,   432,
    2155,   185,   120,  1699,   781,   189,  1782,  1001,  1360,  2240,
    1359,  1224,  1658,  1697,   454,  1006,  2247,  1733,  1214,  1211,
    1482,  1234,  2185,  1743,   208,  2258,  1922,  1221,  1227,  1764,
    1044,  1507,   216,  2264,  1247,   219,   220,   378,   379,  1783,
     224,  1254,  2125,  1531,   228,  1297,   230,  1262,  1261,   233,
    1799,   235,  1068,  2216,  1066,  1268,   867,    79,  1077,  1562,
    1975,  1980,   403,     6,   248,  1562,     9,  1280,  1636,   253,
    2090,  1790,    94,  1286,  1986,  1056,  1456,  1180,  2171,  1292,
     421,   265,   928,  1544,   228,  1572,  2249,  1176,   429,   937,
     811,   432,   300,  1232,  1009,  2173,    56,  1310,   566,  1403,
    1841,  1133,    -1,  2186,   771,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1325,  1326,  1327,  1328,  1329,  1330,  1331,    -1,
      -1,    -1,   306,    79,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1347,    -1,    79,    -1,    94,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   333,
      -1,    94,    -1,    -1,  1367,    -1,   178,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  2248,    -1,   189,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1389,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   369,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   378,   379,    -1,    -1,    -1,    -1,
      -1,   144,    -1,    -1,    -1,    -1,   228,    -1,   230,    -1,
      -1,   233,    -1,   235,   398,    -1,    -1,    -1,    -1,   403,
      -1,    -1,   178,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1443,  1444,    -1,   189,    -1,   178,    -1,   421,    -1,    -1,
      -1,    -1,    -1,   265,    -1,   429,   189,    -1,   432,    -1,
      -1,    -1,    -1,    -1,   438,   439,   440,    -1,    -1,    -1,
     444,    -1,   446,   219,   448,   449,   450,    -1,   224,    -1,
      -1,    -1,   228,    -1,   230,    -1,   219,   233,    -1,   235,
      -1,   224,    -1,    -1,   306,   228,    -1,   230,    -1,    -1,
     233,    -1,   235,    -1,    -1,    -1,  1509,  1510,    -1,    -1,
      -1,    -1,  1515,  1516,    -1,    -1,    -1,    -1,    -1,   265,
      -1,   333,    -1,    -1,     0,     1,    -1,     3,    -1,     5,
    1533,    -1,   265,    -1,    10,    -1,    -1,    -1,  1541,    -1,
      -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1556,    -1,    -1,    -1,   369,  1561,  1562,
     306,    -1,    -1,    -1,    -1,    -1,   378,   379,    -1,    -1,
      -1,    -1,    -1,   306,    50,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    58,    -1,    -1,    -1,   398,   333,    -1,    -1,
    1593,   403,    -1,    69,    -1,    -1,    72,    -1,    -1,    -1,
     333,  1604,    -1,  1606,    -1,    -1,    -1,    -1,    84,   421,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   429,    -1,    -1,
     432,    -1,    -1,   369,    -1,    -1,   438,    -1,    -1,    -1,
     106,    -1,   378,   379,    -1,    -1,   369,   113,   114,    -1,
      -1,    -1,    -1,    -1,    -1,   378,   379,    -1,    -1,    -1,
      -1,    -1,   398,    -1,   130,    -1,    -1,   403,   134,  1662,
    1663,  1664,   395,    -1,    -1,   398,   399,    -1,   144,  1672,
     403,    -1,    -1,    -1,  1677,   421,    -1,    -1,    -1,    -1,
     156,    -1,    -1,   429,   160,    -1,   432,  1690,   421,    -1,
      -1,    -1,   438,   439,   440,    -1,   429,   173,    -1,   432,
      -1,   177,   448,    -1,   180,   438,    -1,   183,   184,    -1,
      -1,    -1,    -1,    -1,    -1,   191,    -1,    -1,    -1,    -1,
      -1,    -1,   198,    -1,   200,    -1,    -1,   203,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1749,    -1,    -1,    -1,
      -1,    -1,  1755,  1756,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1764,   238,    -1,    -1,    -1,   242,    -1,   244,    -1,
      -1,    -1,  1775,    -1,    -1,   251,    -1,    -1,    -1,     6,
    1783,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    -1,    -1,    -1,    21,    -1,    -1,   273,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1810,    -1,    -1,
      -1,  1814,   288,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   302,    -1,    -1,    -1,
      -1,  1834,    -1,   309,    -1,  1838,    -1,    -1,    -1,    -1,
      -1,    -1,   318,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1853,  1854,    79,    -1,    -1,   331,    -1,    -1,    -1,    -1,
     336,    -1,   338,    -1,    -1,    -1,    -1,    94,    -1,    -1,
     346,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     356,    -1,    -1,    -1,    -1,    -1,    -1,     6,    -1,   365,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   374,  1902,
     376,   377,  1905,    -1,   380,    -1,   382,    -1,    -1,    -1,
      -1,   387,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   151,   152,   402,    -1,    -1,  1932,
      -1,   407,    -1,    -1,    -1,    -1,   412,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   423,    -1,    -1,
      -1,   178,   179,    -1,    -1,    -1,   432,    -1,   185,   435,
      79,    -1,   189,    -1,    -1,    -1,    -1,    -1,  1971,   445,
      -1,    -1,    -1,    -1,    -1,    94,    -1,    -1,    -1,    -1,
      -1,   208,    -1,    -1,    -1,    -1,    -1,  1990,    -1,   216,
      -1,    -1,   219,   220,    -1,    -1,    -1,   224,    -1,    -1,
      -1,   228,    -1,   230,  2007,    -1,   233,    -1,   235,    79,
      -1,    -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      41,   248,    -1,    -1,    94,    -1,   253,    -1,    -1,    -1,
      -1,    -1,   151,   152,    -1,    -1,    -1,    -1,   265,    -1,
    2043,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    -1,    73,    74,    75,    76,    77,    78,    -1,   178,
     179,    -1,    -1,    -1,    -1,    -1,   185,    -1,    -1,    -1,
     189,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   306,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,
      -1,    -1,   113,    -1,    -1,    -1,    -1,   216,    -1,    -1,
     219,   220,   172,    -1,    -1,   224,   333,    -1,   178,   228,
      -1,   230,  2115,    -1,   233,  2118,   235,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   248,
      -1,    -1,    -1,    -1,   253,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   369,    -1,    -1,  2148,   265,    -1,    -1,    -1,
      -1,   378,   379,    -1,    -1,    -1,    -1,    -1,   228,  2162,
     230,    -1,    -1,   233,  2167,    -1,    -1,    -1,   395,    -1,
      -1,   398,   399,    -1,   195,    -1,   403,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   306,    -1,    -1,
    2193,    -1,    -1,    -1,   421,   265,    -1,    -1,    -1,    -1,
      -1,  2204,   429,    -1,    -1,   432,    -1,    -1,    -1,    -1,
      -1,   438,   439,   440,   333,    -1,    -1,   444,    -1,   446,
      -1,   448,   449,   450,   245,     3,    -1,     5,    -1,    -1,
      -1,    -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      18,    -1,    -1,    -1,    -1,    12,    13,    14,  2251,    -1,
     369,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,   378,
     379,   282,    -1,   333,    -1,    -1,    -1,    -1,    -1,    -1,
     291,    -1,    50,    51,    -1,    -1,    -1,    -1,    -1,   398,
      58,    -1,    -1,   304,   403,    -1,    -1,    -1,    -1,    -1,
      57,    69,    -1,    -1,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   421,    -1,    -1,    -1,    84,    -1,   378,   379,
     429,    -1,    -1,   432,    -1,    -1,    -1,    -1,   388,   438,
     439,   440,    -1,    -1,    -1,   444,    -1,   446,   106,   448,
     449,   450,    -1,   403,    -1,   113,   114,    -1,    -1,   360,
     361,   362,    -1,   413,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   421,    -1,    -1,    -1,    -1,   426,    -1,    -1,   429,
      -1,   431,   432,    -1,    -1,    -1,   144,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,    -1,
      -1,    -1,   160,    -1,   151,   152,    -1,    -1,   409,   410,
     411,    -1,    -1,    -1,    -1,   173,    -1,    -1,    -1,    -1,
      -1,    -1,   180,    -1,    -1,   183,   184,    -1,    -1,    -1,
      -1,    -1,   179,   191,    -1,    -1,    -1,    -1,   185,    -1,
     198,    -1,   200,    -1,    -1,   203,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     6,    -1,    -1,     9,
      -1,   208,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   216,
      -1,    -1,    -1,   220,    -1,    -1,    -1,    -1,    -1,    -1,
     238,    -1,    -1,    -1,   242,    -1,   244,    -1,    -1,    -1,
      -1,    -1,    -1,   251,    -1,    -1,    -1,    -1,    48,    -1,
      -1,   248,   249,    -1,    -1,    -1,   253,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   273,   263,    -1,    -1,    -1,
      -1,    -1,    -1,   270,    -1,    -1,    -1,    -1,   275,    79,
     288,    -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    -1,   293,    -1,    -1,    -1,
      -1,   309,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,
     318,    -1,    -1,    -1,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    18,   331,    -1,    -1,    -1,    -1,   336,    -1,
     338,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   346,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   356,    -1,
      -1,    -1,    -1,    -1,    50,    51,    -1,   365,     6,    -1,
      -1,     9,    58,    -1,    -1,    -1,   374,    -1,   376,   377,
      -1,    -1,   380,    69,   382,    -1,    72,    -1,   178,   387,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,   189,
      -1,    -1,    -1,    -1,   402,    -1,    -1,    -1,    -1,   407,
      -1,    -1,    -1,    -1,   412,    -1,    -1,    -1,    -1,    -1,
     106,    -1,    -1,    -1,    -1,   423,    -1,   113,   114,   219,
      -1,    -1,    -1,    -1,   224,    -1,    -1,   435,   228,    -1,
     230,    79,    -1,   233,    -1,   235,    -1,   445,    -1,    -1,
      -1,   438,   439,   440,   441,   442,    94,   444,   144,   446,
     447,    -1,   449,   450,    -1,    -1,    -1,    -1,    -1,   107,
     156,    -1,    -1,    -1,   160,   265,    -1,    -1,    -1,    -1,
     270,    -1,    -1,    -1,    -1,    -1,     6,   173,    -1,     9,
      -1,    -1,    -1,    -1,   180,    -1,    -1,   183,   184,    -1,
      -1,    -1,    -1,    -1,    -1,   191,    -1,    -1,    -1,    29,
      -1,    -1,   198,    -1,   200,    -1,   306,   203,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   316,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     178,    -1,    -1,   333,    64,    -1,    -1,    -1,    -1,    -1,
      -1,   189,   238,    -1,    -1,    -1,   242,    -1,   244,    79,
      -1,    -1,    -1,    -1,    -1,   251,   204,    -1,    -1,    -1,
      -1,    -1,    -1,   363,    94,    -1,    -1,    -1,    -1,   369,
      -1,   219,    -1,    -1,    -1,    -1,   224,   273,   378,   379,
     228,    -1,   230,    -1,    -1,   233,    -1,   235,     6,    -1,
      -1,     9,   288,    -1,    -1,    -1,    -1,    -1,   398,    -1,
      -1,    -1,    -1,   403,    -1,    -1,    -1,    -1,   408,    -1,
      -1,    -1,    -1,   309,    -1,    -1,    -1,   265,    -1,    -1,
      -1,   421,   318,    -1,    -1,   425,    -1,    -1,    -1,   429,
      -1,    -1,   432,    -1,    -1,   331,    -1,    -1,   438,    -1,
     336,    -1,   338,    -1,    -1,    -1,    -1,    -1,   178,    -1,
     346,    -1,     6,    -1,    -1,     9,    -1,    -1,   306,   189,
     356,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   365,
      -1,    -1,    90,    -1,    -1,    -1,    94,    -1,   374,    -1,
     376,   377,    -1,    -1,   380,   333,   382,    -1,    -1,   219,
      -1,   387,    -1,    -1,   224,   225,    -1,    -1,   228,     6,
     230,    -1,     9,   233,    -1,   235,   402,    -1,    -1,    -1,
      -1,   407,    -1,    -1,    -1,    -1,   412,    -1,    -1,    -1,
      -1,   369,    -1,    -1,    -1,    79,    -1,   423,    -1,    -1,
     378,   379,    -1,    -1,    -1,   265,    90,    -1,    -1,   435,
      94,    -1,    -1,    -1,    -1,    -1,     6,    -1,    -1,     9,
     398,    -1,    -1,    -1,    -1,   403,    -1,    -1,    -1,    -1,
     178,    -1,   292,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   189,    79,   421,    -1,    -1,   306,    -1,    -1,    -1,
      -1,   429,    -1,    -1,   432,    -1,    -1,    94,    -1,    -1,
     438,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     107,   219,    -1,   333,    -1,    -1,   224,    -1,    -1,    -1,
     228,    -1,   230,    -1,    -1,   233,    -1,   235,    -1,    79,
      -1,    -1,    -1,    -1,   178,    -1,    -1,    -1,    -1,    -1,
      90,    -1,    -1,    -1,    94,   189,    -1,    -1,    -1,   369,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   265,   378,   379,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   219,    -1,    -1,   398,    -1,
     224,   178,    -1,   403,   228,     6,   230,    -1,     9,   233,
      -1,   235,   189,    -1,    -1,    -1,    -1,    -1,   306,    -1,
      -1,   421,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   429,
      -1,    -1,   432,    -1,    -1,    -1,    -1,    -1,   438,    -1,
      -1,   265,   219,    -1,    -1,   333,    -1,   224,   178,    -1,
      -1,   228,     6,   230,    -1,     9,   233,    -1,   235,   189,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      -1,   369,   306,    -1,    -1,    -1,    -1,    -1,   265,   219,
     378,   379,    -1,    94,   224,    -1,    -1,    -1,   228,     6,
     230,    -1,     9,   233,    -1,   235,    -1,    -1,    -1,   333,
     398,    -1,    -1,    -1,    -1,   403,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,   306,
      -1,    -1,    -1,   421,    -1,   265,    -1,    -1,    -1,    -1,
      94,   429,    -1,    -1,   432,   369,    -1,    -1,    -1,    -1,
     438,    -1,    -1,    -1,   378,   379,   333,    -1,    -1,    -1,
      -1,    -1,    -1,     6,    -1,    -1,     9,    -1,    -1,    -1,
      -1,    -1,    79,    -1,   398,    -1,   306,   178,    -1,   403,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,   189,    -1,
      -1,    -1,   369,    -1,    -1,    -1,    -1,   421,    -1,    -1,
      -1,   378,   379,   333,    -1,   429,    -1,    -1,   432,    -1,
      -1,    -1,    -1,    -1,   438,    -1,    -1,    -1,   219,    -1,
     174,   398,    -1,   224,   178,    -1,   403,   228,    -1,   230,
      -1,    -1,   233,    -1,   235,   189,    79,    -1,    -1,   369,
      -1,    -1,    -1,    -1,   421,    -1,    -1,    -1,   378,   379,
      -1,    94,   429,    -1,    -1,   432,    -1,    -1,    -1,    -1,
      -1,   438,    -1,    -1,   265,   219,    -1,    -1,   398,    -1,
     224,   178,    -1,   403,   228,     6,   230,    -1,     9,   233,
      -1,   235,   189,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   421,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   429,
      -1,    -1,   432,    -1,    -1,   306,    -1,    -1,   438,    -1,
      -1,   265,   219,    -1,    -1,    -1,    -1,   224,    -1,    -1,
      -1,   228,    -1,   230,    -1,    -1,   233,    -1,   235,    -1,
      -1,    -1,   333,    -1,    -1,   178,    -1,    -1,    -1,    -1,
      -1,     6,    -1,    -1,     9,    -1,   189,    -1,    79,    -1,
      -1,    -1,   306,    -1,    -1,    -1,    -1,    -1,   265,    -1,
      -1,    -1,    -1,    94,    -1,    -1,    -1,    -1,   369,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   219,   378,   379,   333,
      -1,   224,    -1,    -1,    -1,   228,    -1,   230,    -1,    -1,
     233,    -1,   235,   394,    -1,    -1,    -1,   398,    -1,   306,
      -1,    -1,   403,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    79,   369,    -1,    -1,    -1,    -1,
     421,    -1,   265,    -1,   378,   379,   333,    -1,   429,    94,
      -1,   432,    -1,    -1,    -1,    -1,    -1,   438,    -1,    -1,
      -1,    -1,    -1,    -1,   398,    -1,    -1,   178,    -1,   403,
      -1,    -1,    -1,    -1,    -1,    -1,   363,    -1,   189,    -1,
      -1,    -1,   369,   306,    -1,    -1,    -1,   421,    -1,    -1,
      -1,   378,   379,    -1,    -1,   429,    -1,    -1,   432,    -1,
      -1,    -1,    -1,    -1,   438,    -1,    -1,    -1,   219,    -1,
     333,   398,    -1,   224,    -1,    -1,   403,   228,    -1,   230,
      -1,    -1,   233,    -1,   235,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   178,   421,    -1,    -1,    -1,    -1,    -1,
      -1,   364,   429,    -1,   189,   432,   369,    -1,    -1,    -1,
      -1,   438,    -1,    -1,   265,   378,   379,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   219,   398,    -1,    -1,    -1,   224,
     403,    -1,    -1,   228,    -1,   230,    -1,    -1,   233,    -1,
     235,    -1,    -1,    -1,    -1,   306,    -1,    -1,   421,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   429,    -1,    -1,   432,
      -1,    -1,    -1,    -1,    -1,   438,    -1,    -1,    -1,    -1,
     265,    21,   333,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    -1,    -1,    36,    37,    38,    39,
      40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   369,    -1,
      -1,   306,    -1,    -1,    -1,    -1,    -1,   378,   379,    -1,
      -1,    71,    -1,    73,    74,    75,    76,    77,    78,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   398,   333,    -1,
      -1,    -1,   403,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     421,    -1,    -1,   113,    -1,    -1,    -1,    -1,   429,    -1,
      -1,   432,    -1,    -1,   369,    -1,    -1,   438,    -1,    -1,
      -1,    -1,    -1,   378,   379,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   398,    -1,    30,    -1,    32,   403,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,   421,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   429,    -1,    -1,   432,    -1,    64,
      -1,    -1,    -1,   438,    -1,   195,    71,    -1,    73,    74,
      75,    76,    77,    78,    -1,    -1,    -1,    -1,   208,    -1,
      -1,   211,    -1,    -1,    -1,    -1,    -1,   217,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,    -1,
      -1,    -1,    -1,    -1,    -1,   245,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   267,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   153,    -1,
      -1,    -1,   282,    -1,    -1,    -1,    -1,    -1,    -1,   289,
      -1,   291,    -1,    -1,    -1,    -1,   171,    -1,    -1,   174,
     175,    -1,    -1,    -1,   304,    -1,    36,    37,    38,    39,
      40,    41,    42,   188,   314,    -1,    -1,    -1,    -1,    -1,
     195,   321,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    65,   211,    -1,    -1,    -1,
      -1,    71,    -1,    73,    74,    75,    76,    77,    78,    -1,
     225,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   358,   234,
     360,   361,   362,    -1,    -1,    -1,    -1,    79,    -1,    -1,
     245,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    94,   113,   384,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   267,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   401,    -1,    -1,    -1,    -1,   281,   282,    -1,   409,
     410,   411,    -1,    -1,   289,    -1,   291,    -1,    -1,    -1,
      -1,    -1,   422,    -1,    -1,   425,    -1,    -1,    -1,   304,
     305,    -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   445,    -1,    -1,    94,    -1,
      -1,    -1,    -1,    -1,   329,    -1,   186,    -1,    -1,   334,
      -1,    -1,    -1,    -1,    -1,   195,   178,    -1,    -1,    -1,
      -1,    -1,    -1,   348,    -1,    -1,    -1,   189,    -1,    -1,
      -1,   211,    -1,   358,    -1,   360,   361,   362,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   225,   226,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   219,    -1,    -1,
      -1,    -1,   224,    -1,    -1,   245,   228,    -1,   230,   394,
     250,   233,    -1,   235,    -1,    -1,    -1,    -1,    -1,    -1,
     405,    -1,   178,    -1,   409,   410,   411,   267,    -1,    -1,
      -1,    -1,    -1,   189,    -1,    -1,    -1,   422,    -1,   424,
     425,    -1,   282,   265,    -1,    -1,    -1,    -1,    -1,   289,
      -1,   291,    -1,    -1,   294,    -1,    -1,    -1,    -1,    -1,
     445,    -1,    -1,   219,   304,    -1,    -1,    -1,   224,    -1,
      -1,    -1,   228,    -1,   230,    -1,    -1,   233,    -1,   235,
      -1,    -1,    -1,    -1,   306,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   265,
      -1,   333,    -1,    -1,    -1,    -1,    -1,    -1,   358,    -1,
     360,   361,   362,    -1,    -1,    -1,    -1,   367,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   381,    -1,    -1,    -1,    -1,    -1,   369,    -1,    -1,
     306,    -1,    -1,    -1,    -1,    -1,   378,   379,    -1,    -1,
      -1,    -1,    -1,    -1,   404,    -1,    -1,    -1,    -1,   409,
     410,   411,    -1,    -1,    -1,    -1,   398,   333,    -1,    -1,
      -1,   403,   422,    -1,    -1,   425,   426,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   421,
      -1,    -1,    -1,    -1,    -1,   445,    -1,   429,    -1,    -1,
     432,    -1,    -1,   369,    -1,    -1,   438,   439,   440,    -1,
      -1,    -1,   378,   379,    -1,   447,   448,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   398,    -1,    -1,    -1,    -1,   403,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   421,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   429,    -1,    -1,   432,    -1,    -1,    -1,
      -1,    -1,   438,   439,   440,    -1,    -1,    -1,    -1,    -1,
      -1,   447,   448
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
     556,   556,   367,   446,   550,  1058,  1059,  1119,   167,   666,
     667,   666,  1120,   677,   182,   705,  1079,   393,  1141,   219,
     439,   440,   448,  1041,  1043,  1044,  1066,  1074,  1081,  1083,
     448,  1078,  1076,   648,   650,   391,   228,  1111,  1075,  1075,
    1082,  1060,  1060,  1108,  1112,   122,   746,    29,   174,   740,
    1108,  1126,   448,  1074,   448,  1084,   448,  1085,  1126,  1099,
     448,   448,   448,   448,   448,   448,   448,   448,  1084,   123,
     751,   394,   750,  1065,   199,  1093,    55,  1034,  1035,   394,
    1099,   424,   761,   228,  1071,  1074,  1050,   125,   783,   151,
     446,   784,  1046,   339,  1097,  1131,   127,   796,   740,   417,
     418,   419,   420,   128,   800,    48,   204,   761,    17,   428,
     807,   808,   809,   813,  1104,    96,  1126,  1063,  1053,   390,
    1140,   838,  1144,  1074,    89,   322,   385,   850,   851,   852,
     856,   861,   932,  1065,   394,   132,   872,    48,   161,   201,
     209,   279,   876,   885,   133,   882,   413,   426,   391,   393,
     388,   250,   295,  1094,   174,   992,  1131,   992,  1048,   138,
     916,   426,   910,  1069,  1074,  1081,   925,   927,  1062,   394,
    1052,   116,   394,   414,   923,   940,   181,   332,   946,  1110,
     204,   950,  1074,   141,   956,   174,   174,   310,   312,   965,
     107,   968,   324,   371,   982,   271,  1127,   992,   516,   117,
     431,   550,  1092,  1101,   232,   338,  1119,   547,   548,  1071,
     668,   675,  1079,   617,   678,   706,   109,   635,  1126,  1043,
    1043,  1043,    68,   351,   447,  1042,   439,   440,   441,   442,
     444,   451,  1043,  1143,  1080,  1123,  1060,   109,   592,  1069,
      24,    25,    65,    67,    98,    99,   100,   145,   147,   155,
     226,   392,   432,  1052,   431,   743,    64,   225,   292,   741,
     742,   144,   301,  1067,  1075,  1041,  1043,   394,  1043,  1041,
    1086,  1075,  1081,  1083,   432,  1043,  1089,  1043,  1043,  1088,
    1043,  1041,  1041,  1043,  1087,  1043,  1045,  1065,   181,   332,
     755,  1093,    12,    13,    14,    20,    57,   151,   152,   179,
     185,   208,   216,   220,   248,   249,   253,   263,   270,   275,
     293,   438,   439,   440,   441,   442,   444,   446,   447,   449,
     450,  1036,  1037,  1038,  1039,  1040,   208,   248,   253,   439,
     440,   444,   448,  1036,  1037,  1038,  1039,  1040,  1065,   300,
     758,  1056,   762,   181,   332,   766,   315,   406,   778,   779,
    1144,  1031,   207,   257,  1023,  1024,  1025,  1027,   416,   431,
     793,  1144,   158,   998,   999,   998,   998,   998,  1065,  1045,
    1065,    21,   395,   399,   814,   815,  1032,   129,   817,   430,
     809,   811,   428,   810,   806,  1075,   109,   827,  1054,   832,
       9,    12,    15,    16,   245,   246,   263,   264,   839,   843,
     166,  1069,     9,    55,   168,   217,   401,   857,   858,   859,
     853,   851,   934,  1101,  1127,   394,  1062,  1045,  1065,   357,
     877,   732,   733,  1030,   887,   888,  1074,  1054,     8,    34,
     994,  1131,  1071,   204,   891,   903,  1144,   911,  1108,  1074,
     911,   394,   394,   507,   144,   395,   399,  1065,    48,   212,
     941,  1065,  1065,   363,  1065,  1074,   174,  1045,  1065,  1069,
    1110,   204,   971,  1074,   154,   158,   983,     9,   988,  1054,
     903,   117,   547,   271,   549,  1058,   549,   187,   670,   225,
     226,   676,   432,   618,    30,    32,    35,    43,    44,    45,
      64,   153,   171,   174,   175,   188,   225,   234,   267,   281,
     305,   329,   334,   348,   394,   405,   424,   445,   629,   630,
     632,   642,   645,   647,   707,   710,  1127,   636,   637,  1075,
    1081,  1083,   447,  1043,  1043,  1043,  1043,  1043,  1043,   447,
    1043,   356,  1133,  1123,  1127,   997,   999,   437,   436,  1069,
     997,   212,    30,    32,    35,    45,   171,   175,   188,   234,
     281,   305,   329,   334,   344,   348,   405,   415,   744,   745,
     997,   261,  1125,  1125,  1125,   742,   741,   228,  1068,  1075,
     447,  1074,   451,   447,  1042,   447,   447,  1042,   447,   447,
     447,   447,  1042,   447,   447,   364,  1003,  1004,  1045,  1063,
     332,  1142,   389,  1139,  1139,   394,  1054,   763,   764,   765,
    1110,  1074,  1074,   158,   280,   767,   984,  1116,   232,   252,
    1003,  1026,  1028,   126,   789,  1027,    92,   296,   432,  1052,
      32,    35,    43,    44,    45,   153,   171,   188,   234,   281,
     334,   344,   405,   794,   795,   998,   260,  1000,   256,  1001,
     181,  1003,   181,  1104,   391,   816,   812,   814,   732,  1127,
     732,  1142,   322,   840,  1142,   394,    48,   858,   860,  1069,
       9,    55,   217,   401,   854,   855,  1069,   935,  1102,   194,
     276,  1128,    27,   110,   638,  1062,  1003,   181,  1144,  1049,
     133,   883,   734,     8,   174,   891,  1074,   121,   254,  1013,
    1014,  1016,  1023,   232,   252,   428,   121,   428,   913,   914,
    1069,  1068,  1065,  1119,  1023,   951,  1144,  1074,  1003,   181,
     394,     9,   969,   970,  1091,   972,  1074,   951,   972,   298,
     986,   299,   993,   994,  1092,   243,   310,   312,   557,  1119,
     168,   671,  1079,   679,  1119,  1125,   148,   150,  1119,  1072,
    1125,  1079,  1074,  1074,  1058,   196,   639,   638,   447,  1142,
    1058,  1001,   997,  1119,  1119,   116,   414,   745,  1071,  1071,
    1071,  1084,  1097,   447,  1043,  1058,  1084,  1084,  1043,  1084,
    1084,  1084,   217,   401,  1084,  1084,  1005,   259,  1006,  1003,
    1063,   275,   275,   764,   270,   720,    83,   316,   425,   256,
     258,   769,   985,   768,   320,   335,   732,   732,   793,   793,
     793,   793,  1119,   148,   150,  1119,   116,   414,   795,   732,
    1002,  1045,  1046,  1045,  1046,   815,  1031,   732,  1074,   120,
     833,   425,   841,   842,   843,   105,   844,   425,  1070,  1074,
    1080,  1069,    48,   862,   855,   170,   862,   931,  1119,   276,
    1121,  1045,   566,   878,  1144,   735,   888,  1065,   193,   892,
    1144,  1015,  1017,   136,   900,  1016,   137,   904,   232,  1031,
     912,  1030,   913,   253,   942,  1095,   139,   943,   280,  1008,
    1009,   291,  1097,  1045,  1070,   275,  1069,   108,   973,   385,
     975,  1127,   149,   255,   995,  1018,  1019,  1021,  1024,     7,
    1103,   557,  1079,   111,   214,   672,    65,    64,    65,   186,
     225,   226,   250,   294,   367,   381,   404,   426,   445,   629,
     630,   632,   633,   642,   645,   647,   680,   681,   683,   684,
     685,   686,   688,   689,   690,   691,   695,   696,   438,  1073,
    1074,  1079,  1119,  1073,  1119,  1141,  1110,  1121,   395,   651,
    1073,  1073,  1029,  1110,  1029,  1003,   447,   732,  1007,   151,
     151,  1065,   124,   771,   770,   732,   998,   998,   998,   998,
    1073,  1073,  1029,  1029,   732,  1003,   319,  1003,   319,   834,
     131,   835,   842,    97,  1114,   862,   862,  1070,   994,   201,
     424,   936,  1058,   933,  1003,   232,   252,    48,   232,   212,
     893,   192,   232,   252,   427,   732,   732,   909,   732,   915,
    1065,  1036,  1037,  1038,  1039,  1040,  1010,   140,   952,   258,
    1011,  1074,  1003,  1003,   970,  1118,    91,   974,  1118,  1008,
     161,   201,   209,   279,   980,  1049,  1020,  1022,   143,   996,
    1021,   284,  1052,  1073,  1119,    88,   215,   673,   262,  1125,
     197,   697,   261,   262,   694,  1105,   186,   428,  1119,  1126,
    1119,  1074,   686,   250,   290,   692,   693,  1079,   239,   290,
     439,   440,   709,   239,   290,   439,   440,   708,   432,   640,
     641,  1119,  1119,  1073,   732,  1142,  1142,   732,  1046,  1046,
     732,    48,   862,   397,   863,   298,  1049,   181,   279,   937,
    1076,   335,  1065,  1119,   894,  1013,  1024,   232,   232,   732,
     732,   732,  1012,  1074,  1118,  1074,   142,   976,   732,   732,
     225,   226,  1122,  1079,  1119,  1119,   169,   674,  1119,  1120,
    1119,  1030,  1074,   687,  1058,    87,    88,   111,   285,   286,
     326,   327,   682,   174,   284,  1079,   693,  1073,  1073,   641,
    1057,  1080,  1122,  1003,  1003,  1065,  1065,  1119,  1049,   298,
     413,   668,   135,   895,   732,  1074,  1079,  1079,  1119,  1079,
    1079,  1097,  1065,   884,  1119,  1030,  1079,    48,   884,  1065
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
#line 1795 "parser.y"
    {
	key_component_list = NULL;
  ;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1804 "parser.y"
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
#line 1819 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 1820 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 1821 "parser.y"
    { (yyval) = cb_int('='); ;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 1828 "parser.y"
    {
	PENDING ("COLLATING SEQUENCE");
  ;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1838 "parser.y"
    {
	current_file->file_status = (yyvsp[(4) - (5)]);
	if ((yyvsp[(5) - (5)])) {
		PENDING ("2nd FILE STATUS");
	}
  ;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1859 "parser.y"
    { current_file->lock_mode = COB_LOCK_MANUAL; ;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1860 "parser.y"
    { current_file->lock_mode = COB_LOCK_AUTOMATIC; ;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1861 "parser.y"
    { current_file->lock_mode = COB_LOCK_EXCLUSIVE; ;}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1867 "parser.y"
    {
	current_file->lock_mode |= COB_LOCK_MULTIPLE;
  ;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1870 "parser.y"
    { PENDING ("WITH ROLLBACK"); ;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1887 "parser.y"
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
#line 1896 "parser.y"
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
#line 1905 "parser.y"
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
#line 1914 "parser.y"
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
#line 1929 "parser.y"
    {
	cb_verify (cb_padding_character_clause, "PADDING CHARACTER");
  ;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1938 "parser.y"
    { /* ignored */ ;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1946 "parser.y"
    {
	current_file->key = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1950 "parser.y"
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
#line 1987 "parser.y"
    { current_file->key = (yyvsp[(4) - (4)]); ;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 1994 "parser.y"
    { /* ignored */ ;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 2001 "parser.y"
    { current_file->sharing = (yyvsp[(3) - (3)]); ;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 2005 "parser.y"
    { (yyval) = NULL; PENDING ("SHARING ALL OTHER"); ;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 2006 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 2007 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 2037 "parser.y"
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
#line 2061 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 2062 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 2063 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 2064 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 2071 "parser.y"
    {
	cb_verify (cb_multiple_file_tape_clause, "MULTIPLE FILE TAPE");
  ;}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 2082 "parser.y"
    { ;}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 2110 "parser.y"
    { current_storage = CB_STORAGE_FILE; ;}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 2113 "parser.y"
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
#line 2132 "parser.y"
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
#line 2144 "parser.y"
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
#line 2155 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 2156 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 2166 "parser.y"
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
#line 2177 "parser.y"
    {
	/* Shut up bison */
	dummy_tree = (yyvsp[(2) - (4)]);
  ;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 2189 "parser.y"
    {
	if (current_file->global) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->external = 1;
  ;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 2196 "parser.y"
    {
	if (current_file->external) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->global = 1;
  ;}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 2218 "parser.y"
    { /* ignored */ ;}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 2228 "parser.y"
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
#line 2240 "parser.y"
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
#line 2266 "parser.y"
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
#line 2290 "parser.y"
    {
	current_file->record_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 2296 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 2297 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 2301 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 2302 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 2310 "parser.y"
    {
	cb_verify (cb_label_records_clause, "LABEL RECORDS");
  ;}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 2325 "parser.y"
    {
	cb_verify (cb_value_of_clause, "VALUE OF");
  ;}
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 2329 "parser.y"
    {
	if (!current_file->assign) {
		current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 2345 "parser.y"
    {
	cb_verify (cb_data_records_clause, "DATA RECORDS");
  ;}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 2356 "parser.y"
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
#line 2384 "parser.y"
    {
	current_file->latfoot = (yyvsp[(4) - (5)]);
  ;}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 2391 "parser.y"
    {
	current_file->lattop = (yyvsp[(3) - (4)]);
  ;}
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 2398 "parser.y"
    {
	current_file->latbot = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 2407 "parser.y"
    { /* ignore */ ;}
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 2415 "parser.y"
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
#line 2433 "parser.y"
    {
	cb_warning (_("file descriptor REPORT IS"));
  ;}
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 2437 "parser.y"
    {
	cb_warning (_("file descriptor REPORTS ARE"));
  ;}
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 2448 "parser.y"
    { current_storage = CB_STORAGE_WORKING; ;}
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 2450 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->working_storage =
			cb_field_add (current_program->working_storage, CB_FIELD ((yyvsp[(5) - (5)])));
	}
  ;}
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 2459 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 2460 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 2464 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 2470 "parser.y"
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
#line 2490 "parser.y"
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
#line 2501 "parser.y"
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
#line 2526 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 2532 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 2538 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 2547 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 335:

/* Line 1455 of yacc.c  */
#line 2556 "parser.y"
    {
	current_field->flag_is_global = 1;
	cb_error (_("CONSTANT with GLOBAL clause is not yet supported"));
  ;}
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 2563 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 2564 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 2565 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 2570 "parser.y"
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
#line 2589 "parser.y"
    {
	/* required to check redefines */
	(yyval) = NULL;
  ;}
    break;

  case 341:

/* Line 1455 of yacc.c  */
#line 2595 "parser.y"
    {
	/* required to check redefines */
	(yyval) = cb_true;
  ;}
    break;

  case 356:

/* Line 1455 of yacc.c  */
#line 2623 "parser.y"
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
#line 2645 "parser.y"
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
#line 2666 "parser.y"
    { current_field->ename = NULL; ;}
    break;

  case 359:

/* Line 1455 of yacc.c  */
#line 2668 "parser.y"
    {
	struct cb_field *x;

	x = CB_FIELD(cb_build_field (cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(2) - (2)]))->data))));
	current_field->ename = x->name;
 ;}
    break;

  case 360:

/* Line 1455 of yacc.c  */
#line 2680 "parser.y"
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
#line 2699 "parser.y"
    { current_field->pic = CB_PICTURE ((yyvsp[(1) - (1)])); ;}
    break;

  case 364:

/* Line 1455 of yacc.c  */
#line 2711 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 365:

/* Line 1455 of yacc.c  */
#line 2712 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 366:

/* Line 1455 of yacc.c  */
#line 2713 "parser.y"
    { current_field->usage = CB_USAGE_FLOAT; ;}
    break;

  case 367:

/* Line 1455 of yacc.c  */
#line 2714 "parser.y"
    { current_field->usage = CB_USAGE_DOUBLE; ;}
    break;

  case 368:

/* Line 1455 of yacc.c  */
#line 2715 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 369:

/* Line 1455 of yacc.c  */
#line 2716 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 370:

/* Line 1455 of yacc.c  */
#line 2717 "parser.y"
    { current_field->usage = CB_USAGE_COMP_5; ;}
    break;

  case 371:

/* Line 1455 of yacc.c  */
#line 2718 "parser.y"
    { current_field->usage = CB_USAGE_COMP_X; ;}
    break;

  case 372:

/* Line 1455 of yacc.c  */
#line 2719 "parser.y"
    { current_field->usage = CB_USAGE_DISPLAY; ;}
    break;

  case 373:

/* Line 1455 of yacc.c  */
#line 2720 "parser.y"
    { current_field->usage = CB_USAGE_INDEX; ;}
    break;

  case 374:

/* Line 1455 of yacc.c  */
#line 2721 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 375:

/* Line 1455 of yacc.c  */
#line 2723 "parser.y"
    {
	current_field->usage = CB_USAGE_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 376:

/* Line 1455 of yacc.c  */
#line 2728 "parser.y"
    {
	current_field->usage = CB_USAGE_PROGRAM_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 377:

/* Line 1455 of yacc.c  */
#line 2732 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 378:

/* Line 1455 of yacc.c  */
#line 2733 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 379:

/* Line 1455 of yacc.c  */
#line 2734 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 380:

/* Line 1455 of yacc.c  */
#line 2735 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 381:

/* Line 1455 of yacc.c  */
#line 2736 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 382:

/* Line 1455 of yacc.c  */
#line 2737 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 383:

/* Line 1455 of yacc.c  */
#line 2738 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 384:

/* Line 1455 of yacc.c  */
#line 2739 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_CHAR; ;}
    break;

  case 385:

/* Line 1455 of yacc.c  */
#line 2740 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 386:

/* Line 1455 of yacc.c  */
#line 2741 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 387:

/* Line 1455 of yacc.c  */
#line 2742 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 388:

/* Line 1455 of yacc.c  */
#line 2743 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 389:

/* Line 1455 of yacc.c  */
#line 2744 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 390:

/* Line 1455 of yacc.c  */
#line 2745 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 391:

/* Line 1455 of yacc.c  */
#line 2746 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 392:

/* Line 1455 of yacc.c  */
#line 2747 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 393:

/* Line 1455 of yacc.c  */
#line 2748 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 394:

/* Line 1455 of yacc.c  */
#line 2749 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 395:

/* Line 1455 of yacc.c  */
#line 2751 "parser.y"
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
#line 2759 "parser.y"
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
#line 2767 "parser.y"
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
#line 2774 "parser.y"
    { PENDING ("USAGE NATIONAL");;}
    break;

  case 399:

/* Line 1455 of yacc.c  */
#line 2782 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 1;
  ;}
    break;

  case 400:

/* Line 1455 of yacc.c  */
#line 2787 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 0;
  ;}
    break;

  case 401:

/* Line 1455 of yacc.c  */
#line 2799 "parser.y"
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
#line 2814 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 403:

/* Line 1455 of yacc.c  */
#line 2815 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 405:

/* Line 1455 of yacc.c  */
#line 2820 "parser.y"
    {
	current_field->occurs_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 406:

/* Line 1455 of yacc.c  */
#line 2827 "parser.y"
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
#line 2850 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 408:

/* Line 1455 of yacc.c  */
#line 2853 "parser.y"
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
#line 2868 "parser.y"
    { (yyval) = cb_int (COB_ASCENDING); ;}
    break;

  case 410:

/* Line 1455 of yacc.c  */
#line 2869 "parser.y"
    { (yyval) = cb_int (COB_DESCENDING); ;}
    break;

  case 412:

/* Line 1455 of yacc.c  */
#line 2874 "parser.y"
    {
	current_field->index_list = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 413:

/* Line 1455 of yacc.c  */
#line 2880 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 414:

/* Line 1455 of yacc.c  */
#line 2882 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 415:

/* Line 1455 of yacc.c  */
#line 2887 "parser.y"
    {
	(yyval) = cb_build_index ((yyvsp[(1) - (1)]), cb_int1, 1, current_field);
  ;}
    break;

  case 416:

/* Line 1455 of yacc.c  */
#line 2896 "parser.y"
    { current_field->flag_justified = 1; ;}
    break;

  case 417:

/* Line 1455 of yacc.c  */
#line 2903 "parser.y"
    { current_field->flag_synchronized = 1; ;}
    break;

  case 421:

/* Line 1455 of yacc.c  */
#line 2915 "parser.y"
    { current_field->flag_blank_zero = 1; ;}
    break;

  case 422:

/* Line 1455 of yacc.c  */
#line 2923 "parser.y"
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
#line 2947 "parser.y"
    { current_field->values = (yyvsp[(3) - (3)]); ;}
    break;

  case 425:

/* Line 1455 of yacc.c  */
#line 2952 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 426:

/* Line 1455 of yacc.c  */
#line 2953 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 427:

/* Line 1455 of yacc.c  */
#line 2957 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 428:

/* Line 1455 of yacc.c  */
#line 2958 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 430:

/* Line 1455 of yacc.c  */
#line 2963 "parser.y"
    {
	if (current_field->level != 88) {
		cb_error (_("FALSE clause only allowed for 88 level"));
	}
	current_field->false_88 = cb_list_init ((yyvsp[(3) - (3)]));
  ;}
    break;

  case 431:

/* Line 1455 of yacc.c  */
#line 2976 "parser.y"
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
#line 2988 "parser.y"
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
#line 3008 "parser.y"
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
#line 3023 "parser.y"
    {
	current_storage = CB_STORAGE_LOCAL;
	if (current_program->nested_level) {
		cb_error (_("LOCAL-STORAGE not allowed in nested programs"));
	}
  ;}
    break;

  case 436:

/* Line 1455 of yacc.c  */
#line 3030 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->local_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 438:

/* Line 1455 of yacc.c  */
#line 3043 "parser.y"
    { current_storage = CB_STORAGE_LINKAGE; ;}
    break;

  case 439:

/* Line 1455 of yacc.c  */
#line 3045 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->linkage_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 441:

/* Line 1455 of yacc.c  */
#line 3058 "parser.y"
    {
	cb_error (_("REPORT SECTION not supported"));
	current_storage = CB_STORAGE_REPORT;
  ;}
    break;

  case 448:

/* Line 1455 of yacc.c  */
#line 3091 "parser.y"
    {
	cb_warning (_("Report description using defaults"));
  ;}
    break;

  case 450:

/* Line 1455 of yacc.c  */
#line 3099 "parser.y"
    {
	cb_error (_("GLOBAL is not allowed with RD"));
  ;}
    break;

  case 459:

/* Line 1455 of yacc.c  */
#line 3122 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 460:

/* Line 1455 of yacc.c  */
#line 3123 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 482:

/* Line 1455 of yacc.c  */
#line 3179 "parser.y"
    { cb_warning (_("looking for Report line TYPE")); ;}
    break;

  case 533:

/* Line 1455 of yacc.c  */
#line 3284 "parser.y"
    { current_storage = CB_STORAGE_SCREEN; ;}
    break;

  case 534:

/* Line 1455 of yacc.c  */
#line 3285 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 535:

/* Line 1455 of yacc.c  */
#line 3291 "parser.y"
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
#line 3315 "parser.y"
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
#line 3331 "parser.y"
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
#line 3355 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 546:

/* Line 1455 of yacc.c  */
#line 3356 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 547:

/* Line 1455 of yacc.c  */
#line 3357 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BELL; ;}
    break;

  case 548:

/* Line 1455 of yacc.c  */
#line 3358 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLINK; ;}
    break;

  case 549:

/* Line 1455 of yacc.c  */
#line 3359 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 550:

/* Line 1455 of yacc.c  */
#line 3360 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 551:

/* Line 1455 of yacc.c  */
#line 3361 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 552:

/* Line 1455 of yacc.c  */
#line 3362 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 553:

/* Line 1455 of yacc.c  */
#line 3363 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REVERSE; ;}
    break;

  case 554:

/* Line 1455 of yacc.c  */
#line 3364 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 555:

/* Line 1455 of yacc.c  */
#line 3365 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_OVERLINE; ;}
    break;

  case 556:

/* Line 1455 of yacc.c  */
#line 3366 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_AUTO; ;}
    break;

  case 557:

/* Line 1455 of yacc.c  */
#line 3367 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_SECURE; ;}
    break;

  case 558:

/* Line 1455 of yacc.c  */
#line 3368 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REQUIRED; ;}
    break;

  case 559:

/* Line 1455 of yacc.c  */
#line 3369 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_FULL; ;}
    break;

  case 560:

/* Line 1455 of yacc.c  */
#line 3370 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_PROMPT; ;}
    break;

  case 561:

/* Line 1455 of yacc.c  */
#line 3372 "parser.y"
    {
	current_field->screen_line = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 562:

/* Line 1455 of yacc.c  */
#line 3376 "parser.y"
    {
	current_field->screen_column = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 563:

/* Line 1455 of yacc.c  */
#line 3380 "parser.y"
    {
	current_field->screen_foreg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 564:

/* Line 1455 of yacc.c  */
#line 3384 "parser.y"
    {
	current_field->screen_backg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 572:

/* Line 1455 of yacc.c  */
#line 3395 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 573:

/* Line 1455 of yacc.c  */
#line 3402 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 574:

/* Line 1455 of yacc.c  */
#line 3406 "parser.y"
    {
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 575:

/* Line 1455 of yacc.c  */
#line 3415 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 576:

/* Line 1455 of yacc.c  */
#line 3419 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 577:

/* Line 1455 of yacc.c  */
#line 3423 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 578:

/* Line 1455 of yacc.c  */
#line 3427 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 579:

/* Line 1455 of yacc.c  */
#line 3431 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 580:

/* Line 1455 of yacc.c  */
#line 3438 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 581:

/* Line 1455 of yacc.c  */
#line 3442 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 582:

/* Line 1455 of yacc.c  */
#line 3446 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 583:

/* Line 1455 of yacc.c  */
#line 3450 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 584:

/* Line 1455 of yacc.c  */
#line 3454 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 585:

/* Line 1455 of yacc.c  */
#line 3462 "parser.y"
    {
	current_field->occurs_max = cb_get_int ((yyvsp[(2) - (3)]));
	current_field->occurs_min = current_field->occurs_max;
	current_field->indexes++;
	current_field->flag_occurs = 1;
  ;}
    break;

  case 587:

/* Line 1455 of yacc.c  */
#line 3476 "parser.y"
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
#line 3486 "parser.y"
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
#line 3496 "parser.y"
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
#line 3513 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 591:

/* Line 1455 of yacc.c  */
#line 3515 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 592:

/* Line 1455 of yacc.c  */
#line 3519 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 593:

/* Line 1455 of yacc.c  */
#line 3521 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	current_program->flag_chained = 1;
  ;}
    break;

  case 594:

/* Line 1455 of yacc.c  */
#line 3525 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 595:

/* Line 1455 of yacc.c  */
#line 3529 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 596:

/* Line 1455 of yacc.c  */
#line 3531 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 597:

/* Line 1455 of yacc.c  */
#line 3536 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), cb_build_identifier ((yyvsp[(4) - (4)])));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 599:

/* Line 1455 of yacc.c  */
#line 3545 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 600:

/* Line 1455 of yacc.c  */
#line 3549 "parser.y"
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
#line 3561 "parser.y"
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
#line 3569 "parser.y"
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
#line 3577 "parser.y"
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
#line 3606 "parser.y"
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
#line 3639 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OPTIONAL only allowed for BY REFERENCE items"));
	}
  ;}
    break;

  case 608:

/* Line 1455 of yacc.c  */
#line 3648 "parser.y"
    {
	if (current_program->prog_type == CB_FUNCTION_TYPE) {
		cb_error (_("RETURNING clause is required for a FUNCTION"));
	}
  ;}
    break;

  case 609:

/* Line 1455 of yacc.c  */
#line 3654 "parser.y"
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
#line 3665 "parser.y"
    { in_declaratives = 1; ;}
    break;

  case 612:

/* Line 1455 of yacc.c  */
#line 3668 "parser.y"
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
#line 3701 "parser.y"
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
#line 3717 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 620:

/* Line 1455 of yacc.c  */
#line 3729 "parser.y"
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
#line 3760 "parser.y"
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
#line 3797 "parser.y"
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
#line 3808 "parser.y"
    { (yyval) = cb_build_section_name ((yyvsp[(1) - (1)]), 0); ;}
    break;

  case 625:

/* Line 1455 of yacc.c  */
#line 3812 "parser.y"
    { /* ignore */ ;}
    break;

  case 626:

/* Line 1455 of yacc.c  */
#line 3821 "parser.y"
    {
	(yyval) = current_program->exec_list;
	current_program->exec_list = NULL;
  ;}
    break;

  case 627:

/* Line 1455 of yacc.c  */
#line 3825 "parser.y"
    {
	(yyval) = CB_TREE (current_statement);
	current_statement = NULL;
  ;}
    break;

  case 628:

/* Line 1455 of yacc.c  */
#line 3830 "parser.y"
    {
	(yyval) = cb_list_reverse (current_program->exec_list);
	current_program->exec_list = (yyvsp[(1) - (3)]);
	current_statement = CB_STATEMENT ((yyvsp[(2) - (3)]));
  ;}
    break;

  case 629:

/* Line 1455 of yacc.c  */
#line 3838 "parser.y"
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

  case 679:

/* Line 1455 of yacc.c  */
#line 3909 "parser.y"
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

  case 680:

/* Line 1455 of yacc.c  */
#line 3931 "parser.y"
    {
	BEGIN_STATEMENT ("ACCEPT", TERM_ACCEPT);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 682:

/* Line 1455 of yacc.c  */
#line 3944 "parser.y"
    {
	cb_emit_accept ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 683:

/* Line 1455 of yacc.c  */
#line 3948 "parser.y"
    {
	PENDING ("ACCEPT .. FROM ESCAPE KEY");
  ;}
    break;

  case 684:

/* Line 1455 of yacc.c  */
#line 3952 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 0);
  ;}
    break;

  case 685:

/* Line 1455 of yacc.c  */
#line 3956 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 1);
  ;}
    break;

  case 686:

/* Line 1455 of yacc.c  */
#line 3960 "parser.y"
    {
	cb_emit_accept_date ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 687:

/* Line 1455 of yacc.c  */
#line 3964 "parser.y"
    {
	cb_emit_accept_date_yyyymmdd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 688:

/* Line 1455 of yacc.c  */
#line 3968 "parser.y"
    {
	cb_emit_accept_day ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 689:

/* Line 1455 of yacc.c  */
#line 3972 "parser.y"
    {
	cb_emit_accept_day_yyyyddd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 690:

/* Line 1455 of yacc.c  */
#line 3976 "parser.y"
    {
	cb_emit_accept_day_of_week ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 691:

/* Line 1455 of yacc.c  */
#line 3980 "parser.y"
    {
	cb_emit_accept_time ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 692:

/* Line 1455 of yacc.c  */
#line 3984 "parser.y"
    {
	cb_emit_accept_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 693:

/* Line 1455 of yacc.c  */
#line 3988 "parser.y"
    {
	cb_emit_accept_environment ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 694:

/* Line 1455 of yacc.c  */
#line 3992 "parser.y"
    { 
	cb_emit_get_environment ((yyvsp[(4) - (5)]), (yyvsp[(1) - (5)]));
  ;}
    break;

  case 695:

/* Line 1455 of yacc.c  */
#line 3996 "parser.y"
    {
	cb_emit_accept_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 696:

/* Line 1455 of yacc.c  */
#line 4000 "parser.y"
    {
	cb_emit_accept_arg_value ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 697:

/* Line 1455 of yacc.c  */
#line 4004 "parser.y"
    {
	cb_emit_accept_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 698:

/* Line 1455 of yacc.c  */
#line 4008 "parser.y"
    {
	cb_emit_accept_name ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 699:

/* Line 1455 of yacc.c  */
#line 4014 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 700:

/* Line 1455 of yacc.c  */
#line 4015 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 701:

/* Line 1455 of yacc.c  */
#line 4016 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); ;}
    break;

  case 702:

/* Line 1455 of yacc.c  */
#line 4017 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), NULL); ;}
    break;

  case 703:

/* Line 1455 of yacc.c  */
#line 4018 "parser.y"
    { (yyval) = cb_build_pair (NULL, (yyvsp[(2) - (2)])); ;}
    break;

  case 704:

/* Line 1455 of yacc.c  */
#line 4019 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 705:

/* Line 1455 of yacc.c  */
#line 4023 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 706:

/* Line 1455 of yacc.c  */
#line 4027 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 707:

/* Line 1455 of yacc.c  */
#line 4028 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 712:

/* Line 1455 of yacc.c  */
#line 4041 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 713:

/* Line 1455 of yacc.c  */
#line 4042 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 714:

/* Line 1455 of yacc.c  */
#line 4043 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 715:

/* Line 1455 of yacc.c  */
#line 4044 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 716:

/* Line 1455 of yacc.c  */
#line 4045 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 717:

/* Line 1455 of yacc.c  */
#line 4046 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 718:

/* Line 1455 of yacc.c  */
#line 4047 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 719:

/* Line 1455 of yacc.c  */
#line 4049 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 720:

/* Line 1455 of yacc.c  */
#line 4053 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 721:

/* Line 1455 of yacc.c  */
#line 4057 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 722:

/* Line 1455 of yacc.c  */
#line 4061 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 723:

/* Line 1455 of yacc.c  */
#line 4065 "parser.y"
    { dispattrs |= COB_SCREEN_AUTO; ;}
    break;

  case 724:

/* Line 1455 of yacc.c  */
#line 4066 "parser.y"
    { dispattrs |= COB_SCREEN_FULL; ;}
    break;

  case 725:

/* Line 1455 of yacc.c  */
#line 4067 "parser.y"
    { dispattrs |= COB_SCREEN_REQUIRED; ;}
    break;

  case 726:

/* Line 1455 of yacc.c  */
#line 4068 "parser.y"
    { dispattrs |= COB_SCREEN_SECURE; ;}
    break;

  case 727:

/* Line 1455 of yacc.c  */
#line 4069 "parser.y"
    { dispattrs |= COB_SCREEN_UPDATE; ;}
    break;

  case 728:

/* Line 1455 of yacc.c  */
#line 4070 "parser.y"
    { dispattrs |= COB_SCREEN_PROMPT; ;}
    break;

  case 729:

/* Line 1455 of yacc.c  */
#line 4074 "parser.y"
    { terminator_warning (TERM_ACCEPT); ;}
    break;

  case 730:

/* Line 1455 of yacc.c  */
#line 4075 "parser.y"
    { terminator_clear (TERM_ACCEPT); ;}
    break;

  case 731:

/* Line 1455 of yacc.c  */
#line 4084 "parser.y"
    { BEGIN_STATEMENT ("ADD", TERM_ADD); ;}
    break;

  case 733:

/* Line 1455 of yacc.c  */
#line 4091 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '+', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 734:

/* Line 1455 of yacc.c  */
#line 4095 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(4) - (5)]), 0, cb_build_binary_list ((yyvsp[(1) - (5)]), '+'));
  ;}
    break;

  case 735:

/* Line 1455 of yacc.c  */
#line 4099 "parser.y"
    {
	cb_emit_corresponding (cb_build_add, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 737:

/* Line 1455 of yacc.c  */
#line 4105 "parser.y"
    { cb_list_add ((yyvsp[(0) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 738:

/* Line 1455 of yacc.c  */
#line 4109 "parser.y"
    { terminator_warning (TERM_ADD); ;}
    break;

  case 739:

/* Line 1455 of yacc.c  */
#line 4110 "parser.y"
    { terminator_clear (TERM_ADD); ;}
    break;

  case 740:

/* Line 1455 of yacc.c  */
#line 4119 "parser.y"
    { BEGIN_STATEMENT ("ALLOCATE", 0); ;}
    break;

  case 742:

/* Line 1455 of yacc.c  */
#line 4125 "parser.y"
    {
	cb_emit_allocate ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), NULL, (yyvsp[(2) - (3)]));
  ;}
    break;

  case 743:

/* Line 1455 of yacc.c  */
#line 4129 "parser.y"
    {
	cb_emit_allocate (NULL, (yyvsp[(5) - (5)]), (yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]));
  ;}
    break;

  case 744:

/* Line 1455 of yacc.c  */
#line 4135 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 745:

/* Line 1455 of yacc.c  */
#line 4136 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 746:

/* Line 1455 of yacc.c  */
#line 4146 "parser.y"
    {
	cb_error (_("ALTER statement is obsolete and unsupported"));
  ;}
    break;

  case 751:

/* Line 1455 of yacc.c  */
#line 4164 "parser.y"
    { BEGIN_STATEMENT ("CALL", TERM_CALL); ;}
    break;

  case 752:

/* Line 1455 of yacc.c  */
#line 4168 "parser.y"
    {
	cb_emit_call ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 753:

/* Line 1455 of yacc.c  */
#line 4174 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 754:

/* Line 1455 of yacc.c  */
#line 4176 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 755:

/* Line 1455 of yacc.c  */
#line 4180 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 756:

/* Line 1455 of yacc.c  */
#line 4184 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 757:

/* Line 1455 of yacc.c  */
#line 4186 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 758:

/* Line 1455 of yacc.c  */
#line 4191 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OMITTED only allowed with BY REFERENCE"));
	}
	(yyval) = cb_build_pair (cb_int (call_mode), cb_null);
  ;}
    break;

  case 759:

/* Line 1455 of yacc.c  */
#line 4198 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), (yyvsp[(3) - (3)]));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 761:

/* Line 1455 of yacc.c  */
#line 4207 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 762:

/* Line 1455 of yacc.c  */
#line 4211 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY CONTENT not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_CONTENT;
	}
  ;}
    break;

  case 763:

/* Line 1455 of yacc.c  */
#line 4219 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 764:

/* Line 1455 of yacc.c  */
#line 4229 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 765:

/* Line 1455 of yacc.c  */
#line 4230 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 766:

/* Line 1455 of yacc.c  */
#line 4231 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 767:

/* Line 1455 of yacc.c  */
#line 4236 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 768:

/* Line 1455 of yacc.c  */
#line 4240 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 769:

/* Line 1455 of yacc.c  */
#line 4244 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 770:

/* Line 1455 of yacc.c  */
#line 4251 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 771:

/* Line 1455 of yacc.c  */
#line 4255 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 772:

/* Line 1455 of yacc.c  */
#line 4259 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 773:

/* Line 1455 of yacc.c  */
#line 4265 "parser.y"
    { terminator_warning (TERM_CALL); ;}
    break;

  case 774:

/* Line 1455 of yacc.c  */
#line 4266 "parser.y"
    { terminator_clear (TERM_CALL); ;}
    break;

  case 775:

/* Line 1455 of yacc.c  */
#line 4275 "parser.y"
    { BEGIN_STATEMENT ("CANCEL", 0); ;}
    break;

  case 778:

/* Line 1455 of yacc.c  */
#line 4281 "parser.y"
    {
	cb_emit_cancel ((yyvsp[(2) - (2)]));
  ;}
    break;

  case 779:

/* Line 1455 of yacc.c  */
#line 4292 "parser.y"
    { BEGIN_STATEMENT ("CLOSE", 0); ;}
    break;

  case 782:

/* Line 1455 of yacc.c  */
#line 4299 "parser.y"
    {
	BEGIN_IMPLICIT_STATEMENT ();
	if ((yyvsp[(2) - (3)]) != cb_error_node) {
		cb_emit_close ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
	}
  ;}
    break;

  case 783:

/* Line 1455 of yacc.c  */
#line 4308 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NORMAL); ;}
    break;

  case 784:

/* Line 1455 of yacc.c  */
#line 4309 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT); ;}
    break;

  case 785:

/* Line 1455 of yacc.c  */
#line 4310 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT_REMOVAL); ;}
    break;

  case 786:

/* Line 1455 of yacc.c  */
#line 4311 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NO_REWIND); ;}
    break;

  case 787:

/* Line 1455 of yacc.c  */
#line 4312 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_LOCK); ;}
    break;

  case 790:

/* Line 1455 of yacc.c  */
#line 4323 "parser.y"
    { BEGIN_STATEMENT ("COMPUTE", TERM_COMPUTE); ;}
    break;

  case 792:

/* Line 1455 of yacc.c  */
#line 4330 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(1) - (4)]), 0, (yyvsp[(3) - (4)]));
  ;}
    break;

  case 793:

/* Line 1455 of yacc.c  */
#line 4336 "parser.y"
    { terminator_warning (TERM_COMPUTE); ;}
    break;

  case 794:

/* Line 1455 of yacc.c  */
#line 4337 "parser.y"
    { terminator_clear (TERM_COMPUTE); ;}
    break;

  case 797:

/* Line 1455 of yacc.c  */
#line 4348 "parser.y"
    {
	BEGIN_STATEMENT ("COMMIT", 0);
	cb_emit_commit ();
  ;}
    break;

  case 798:

/* Line 1455 of yacc.c  */
#line 4361 "parser.y"
    {
	BEGIN_STATEMENT ("CONTINUE", 0);
	cb_emit_continue ();
  ;}
    break;

  case 799:

/* Line 1455 of yacc.c  */
#line 4373 "parser.y"
    { BEGIN_STATEMENT ("DELETE", TERM_DELETE); ;}
    break;

  case 800:

/* Line 1455 of yacc.c  */
#line 4376 "parser.y"
    {
	if ((yyvsp[(3) - (6)]) != cb_error_node) {
		cb_emit_delete ((yyvsp[(3) - (6)]));
	}
  ;}
    break;

  case 801:

/* Line 1455 of yacc.c  */
#line 4384 "parser.y"
    { terminator_warning (TERM_DELETE); ;}
    break;

  case 802:

/* Line 1455 of yacc.c  */
#line 4385 "parser.y"
    { terminator_clear (TERM_DELETE); ;}
    break;

  case 803:

/* Line 1455 of yacc.c  */
#line 4395 "parser.y"
    {
	BEGIN_STATEMENT ("DISPLAY", TERM_DISPLAY);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 805:

/* Line 1455 of yacc.c  */
#line 4408 "parser.y"
    {
	cb_emit_env_name ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 806:

/* Line 1455 of yacc.c  */
#line 4412 "parser.y"
    {
	cb_emit_env_value ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 807:

/* Line 1455 of yacc.c  */
#line 4416 "parser.y"
    {
	cb_emit_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 808:

/* Line 1455 of yacc.c  */
#line 4420 "parser.y"
    {
	cb_emit_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 809:

/* Line 1455 of yacc.c  */
#line 4424 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (4)]), cb_int0, (yyvsp[(3) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 810:

/* Line 1455 of yacc.c  */
#line 4428 "parser.y"
    {
	cb_emit_display_mnemonic ((yyvsp[(1) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 811:

/* Line 1455 of yacc.c  */
#line 4432 "parser.y"
    {
	cb_tree word = cb_build_display_upon_direct ((yyvsp[(4) - (6)]));
	cb_emit_display ((yyvsp[(1) - (6)]), word, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 812:

/* Line 1455 of yacc.c  */
#line 4437 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 813:

/* Line 1455 of yacc.c  */
#line 4441 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 814:

/* Line 1455 of yacc.c  */
#line 4447 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 815:

/* Line 1455 of yacc.c  */
#line 4448 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 816:

/* Line 1455 of yacc.c  */
#line 4449 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 819:

/* Line 1455 of yacc.c  */
#line 4459 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 820:

/* Line 1455 of yacc.c  */
#line 4460 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 821:

/* Line 1455 of yacc.c  */
#line 4461 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 822:

/* Line 1455 of yacc.c  */
#line 4462 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 823:

/* Line 1455 of yacc.c  */
#line 4463 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 824:

/* Line 1455 of yacc.c  */
#line 4464 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 825:

/* Line 1455 of yacc.c  */
#line 4465 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 826:

/* Line 1455 of yacc.c  */
#line 4466 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 827:

/* Line 1455 of yacc.c  */
#line 4467 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 828:

/* Line 1455 of yacc.c  */
#line 4469 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 829:

/* Line 1455 of yacc.c  */
#line 4473 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 830:

/* Line 1455 of yacc.c  */
#line 4477 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 831:

/* Line 1455 of yacc.c  */
#line 4481 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 832:

/* Line 1455 of yacc.c  */
#line 4485 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 833:

/* Line 1455 of yacc.c  */
#line 4486 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 834:

/* Line 1455 of yacc.c  */
#line 4490 "parser.y"
    { terminator_warning (TERM_DISPLAY); ;}
    break;

  case 835:

/* Line 1455 of yacc.c  */
#line 4491 "parser.y"
    { terminator_clear (TERM_DISPLAY); ;}
    break;

  case 836:

/* Line 1455 of yacc.c  */
#line 4500 "parser.y"
    { BEGIN_STATEMENT ("DIVIDE", TERM_DIVIDE); ;}
    break;

  case 838:

/* Line 1455 of yacc.c  */
#line 4507 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '/', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 839:

/* Line 1455 of yacc.c  */
#line 4511 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(3) - (6)]), '/', (yyvsp[(1) - (6)])));
  ;}
    break;

  case 840:

/* Line 1455 of yacc.c  */
#line 4515 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '/', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 841:

/* Line 1455 of yacc.c  */
#line 4519 "parser.y"
    {
	cb_emit_divide ((yyvsp[(3) - (8)]), (yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 842:

/* Line 1455 of yacc.c  */
#line 4523 "parser.y"
    {
	cb_emit_divide ((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 843:

/* Line 1455 of yacc.c  */
#line 4529 "parser.y"
    { terminator_warning (TERM_DIVIDE); ;}
    break;

  case 844:

/* Line 1455 of yacc.c  */
#line 4530 "parser.y"
    { terminator_clear (TERM_DIVIDE); ;}
    break;

  case 845:

/* Line 1455 of yacc.c  */
#line 4539 "parser.y"
    { BEGIN_STATEMENT ("ENTRY", 0); ;}
    break;

  case 846:

/* Line 1455 of yacc.c  */
#line 4541 "parser.y"
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

  case 847:

/* Line 1455 of yacc.c  */
#line 4561 "parser.y"
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

  case 848:

/* Line 1455 of yacc.c  */
#line 4572 "parser.y"
    {
	cb_emit_evaluate ((yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]));
	eval_level--;
  ;}
    break;

  case 849:

/* Line 1455 of yacc.c  */
#line 4579 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 850:

/* Line 1455 of yacc.c  */
#line 4582 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 851:

/* Line 1455 of yacc.c  */
#line 4592 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE_P ((yyvsp[(1) - (1)]))) {
		eval_check[eval_level][eval_inc++] = 0;
	} else {
		eval_check[eval_level][eval_inc++] = 1;
	}
  ;}
    break;

  case 852:

/* Line 1455 of yacc.c  */
#line 4601 "parser.y"
    {
	(yyval) = cb_true;
	eval_check[eval_level][eval_inc++] = 2;
  ;}
    break;

  case 853:

/* Line 1455 of yacc.c  */
#line 4606 "parser.y"
    {
	(yyval) = cb_false;
	eval_check[eval_level][eval_inc++] = 3;
  ;}
    break;

  case 854:

/* Line 1455 of yacc.c  */
#line 4614 "parser.y"
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

  case 855:

/* Line 1455 of yacc.c  */
#line 4642 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 856:

/* Line 1455 of yacc.c  */
#line 4644 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 857:

/* Line 1455 of yacc.c  */
#line 4649 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 858:

/* Line 1455 of yacc.c  */
#line 4653 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]));
	eval_inc2 = 0;
  ;}
    break;

  case 859:

/* Line 1455 of yacc.c  */
#line 4664 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 860:

/* Line 1455 of yacc.c  */
#line 4668 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 861:

/* Line 1455 of yacc.c  */
#line 4672 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), NULL);
	eval_inc2 = 0;
  ;}
    break;

  case 862:

/* Line 1455 of yacc.c  */
#line 4682 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 863:

/* Line 1455 of yacc.c  */
#line 4684 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 864:

/* Line 1455 of yacc.c  */
#line 4688 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 865:

/* Line 1455 of yacc.c  */
#line 4691 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 866:

/* Line 1455 of yacc.c  */
#line 4701 "parser.y"
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

  case 867:

/* Line 1455 of yacc.c  */
#line 4729 "parser.y"
    { (yyval) = cb_any; eval_inc2++; ;}
    break;

  case 868:

/* Line 1455 of yacc.c  */
#line 4730 "parser.y"
    { (yyval) = cb_true; eval_inc2++; ;}
    break;

  case 869:

/* Line 1455 of yacc.c  */
#line 4731 "parser.y"
    { (yyval) = cb_false; eval_inc2++; ;}
    break;

  case 870:

/* Line 1455 of yacc.c  */
#line 4734 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 871:

/* Line 1455 of yacc.c  */
#line 4735 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 872:

/* Line 1455 of yacc.c  */
#line 4739 "parser.y"
    { terminator_warning (TERM_EVALUATE); ;}
    break;

  case 873:

/* Line 1455 of yacc.c  */
#line 4740 "parser.y"
    { terminator_clear (TERM_EVALUATE); ;}
    break;

  case 874:

/* Line 1455 of yacc.c  */
#line 4749 "parser.y"
    { BEGIN_STATEMENT ("EXIT", 0); ;}
    break;

  case 876:

/* Line 1455 of yacc.c  */
#line 4754 "parser.y"
    { /* nothing */ ;}
    break;

  case 877:

/* Line 1455 of yacc.c  */
#line 4756 "parser.y"
    {
	if (in_declaratives && use_global_ind) {
		cb_error (_("EXIT PROGRAM is not allowed within a USE GLOBAL procedure"));
	}
	check_unreached = 1;
	cb_emit_exit (0);
  ;}
    break;

  case 878:

/* Line 1455 of yacc.c  */
#line 4764 "parser.y"
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

  case 879:

/* Line 1455 of yacc.c  */
#line 4781 "parser.y"
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

  case 880:

/* Line 1455 of yacc.c  */
#line 4798 "parser.y"
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

  case 881:

/* Line 1455 of yacc.c  */
#line 4816 "parser.y"
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

  case 882:

/* Line 1455 of yacc.c  */
#line 4840 "parser.y"
    { BEGIN_STATEMENT ("FREE", 0); ;}
    break;

  case 883:

/* Line 1455 of yacc.c  */
#line 4842 "parser.y"
    {
	cb_emit_free ((yyvsp[(3) - (3)]))
  ;}
    break;

  case 884:

/* Line 1455 of yacc.c  */
#line 4853 "parser.y"
    { BEGIN_STATEMENT ("GENERATE", 0); ;}
    break;

  case 885:

/* Line 1455 of yacc.c  */
#line 4855 "parser.y"
    {
	PENDING("GENERATE");
  ;}
    break;

  case 886:

/* Line 1455 of yacc.c  */
#line 4866 "parser.y"
    { BEGIN_STATEMENT ("GO TO", 0); ;}
    break;

  case 887:

/* Line 1455 of yacc.c  */
#line 4868 "parser.y"
    {
	cb_emit_goto ((yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 888:

/* Line 1455 of yacc.c  */
#line 4875 "parser.y"
    {
	check_unreached = 1;
	(yyval) = NULL;
  ;}
    break;

  case 889:

/* Line 1455 of yacc.c  */
#line 4880 "parser.y"
    {
	check_unreached = 0;
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 890:

/* Line 1455 of yacc.c  */
#line 4892 "parser.y"
    { BEGIN_STATEMENT ("GOBACK", 0); ;}
    break;

  case 891:

/* Line 1455 of yacc.c  */
#line 4893 "parser.y"
    {
	check_unreached = 1;
	cb_emit_exit (1);
  ;}
    break;

  case 892:

/* Line 1455 of yacc.c  */
#line 4905 "parser.y"
    { BEGIN_STATEMENT ("IF", TERM_IF); ;}
    break;

  case 893:

/* Line 1455 of yacc.c  */
#line 4907 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 894:

/* Line 1455 of yacc.c  */
#line 4912 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(6) - (8)]) == NULL) {
		cb_error (_("syntax error"));
	}
	cb_emit_if ((yyvsp[(3) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 896:

/* Line 1455 of yacc.c  */
#line 4923 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 897:

/* Line 1455 of yacc.c  */
#line 4927 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 898:

/* Line 1455 of yacc.c  */
#line 4931 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 899:

/* Line 1455 of yacc.c  */
#line 4940 "parser.y"
    { terminator_warning (TERM_IF); ;}
    break;

  case 900:

/* Line 1455 of yacc.c  */
#line 4941 "parser.y"
    { terminator_clear (TERM_IF); ;}
    break;

  case 901:

/* Line 1455 of yacc.c  */
#line 4950 "parser.y"
    { BEGIN_STATEMENT ("INITIALIZE", 0); ;}
    break;

  case 902:

/* Line 1455 of yacc.c  */
#line 4952 "parser.y"
    {
	cb_emit_initialize ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 903:

/* Line 1455 of yacc.c  */
#line 4958 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 904:

/* Line 1455 of yacc.c  */
#line 4959 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 905:

/* Line 1455 of yacc.c  */
#line 4963 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 906:

/* Line 1455 of yacc.c  */
#line 4964 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 907:

/* Line 1455 of yacc.c  */
#line 4965 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 908:

/* Line 1455 of yacc.c  */
#line 4969 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 909:

/* Line 1455 of yacc.c  */
#line 4971 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 910:

/* Line 1455 of yacc.c  */
#line 4975 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 911:

/* Line 1455 of yacc.c  */
#line 4977 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 912:

/* Line 1455 of yacc.c  */
#line 4981 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 913:

/* Line 1455 of yacc.c  */
#line 4985 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHABETIC); ;}
    break;

  case 914:

/* Line 1455 of yacc.c  */
#line 4986 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC); ;}
    break;

  case 915:

/* Line 1455 of yacc.c  */
#line 4987 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC); ;}
    break;

  case 916:

/* Line 1455 of yacc.c  */
#line 4988 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC_EDITED); ;}
    break;

  case 917:

/* Line 1455 of yacc.c  */
#line 4989 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC_EDITED); ;}
    break;

  case 918:

/* Line 1455 of yacc.c  */
#line 4990 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL); ;}
    break;

  case 919:

/* Line 1455 of yacc.c  */
#line 4991 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL_EDITED); ;}
    break;

  case 920:

/* Line 1455 of yacc.c  */
#line 4995 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 921:

/* Line 1455 of yacc.c  */
#line 4996 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 922:

/* Line 1455 of yacc.c  */
#line 5005 "parser.y"
    { BEGIN_STATEMENT ("INITIATE", 0); ;}
    break;

  case 923:

/* Line 1455 of yacc.c  */
#line 5007 "parser.y"
    {
	PENDING("INITIATE");
  ;}
    break;

  case 924:

/* Line 1455 of yacc.c  */
#line 5018 "parser.y"
    {
	BEGIN_STATEMENT ("INSPECT", 0);
	sending_id = 0;
	inspect_keyword = 0;
  ;}
    break;

  case 926:

/* Line 1455 of yacc.c  */
#line 5027 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 0; ;}
    break;

  case 927:

/* Line 1455 of yacc.c  */
#line 5028 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 928:

/* Line 1455 of yacc.c  */
#line 5029 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 931:

/* Line 1455 of yacc.c  */
#line 5038 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 0); ;}
    break;

  case 932:

/* Line 1455 of yacc.c  */
#line 5039 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int1, 1); ;}
    break;

  case 933:

/* Line 1455 of yacc.c  */
#line 5040 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 2); ;}
    break;

  case 934:

/* Line 1455 of yacc.c  */
#line 5046 "parser.y"
    { cb_init_tarrying (); ;}
    break;

  case 935:

/* Line 1455 of yacc.c  */
#line 5047 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 936:

/* Line 1455 of yacc.c  */
#line 5051 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 937:

/* Line 1455 of yacc.c  */
#line 5052 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 938:

/* Line 1455 of yacc.c  */
#line 5056 "parser.y"
    { (yyval) = cb_build_tarrying_data ((yyvsp[(1) - (2)])); ;}
    break;

  case 939:

/* Line 1455 of yacc.c  */
#line 5057 "parser.y"
    { (yyval) = cb_build_tarrying_characters ((yyvsp[(2) - (2)])); ;}
    break;

  case 940:

/* Line 1455 of yacc.c  */
#line 5058 "parser.y"
    { (yyval) = cb_build_tarrying_all (); ;}
    break;

  case 941:

/* Line 1455 of yacc.c  */
#line 5059 "parser.y"
    { (yyval) = cb_build_tarrying_leading (); ;}
    break;

  case 942:

/* Line 1455 of yacc.c  */
#line 5060 "parser.y"
    { (yyval) = cb_build_tarrying_trailing (); ;}
    break;

  case 943:

/* Line 1455 of yacc.c  */
#line 5061 "parser.y"
    { (yyval) = cb_build_tarrying_value ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 944:

/* Line 1455 of yacc.c  */
#line 5067 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); inspect_keyword = 0; ;}
    break;

  case 945:

/* Line 1455 of yacc.c  */
#line 5071 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 946:

/* Line 1455 of yacc.c  */
#line 5072 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 947:

/* Line 1455 of yacc.c  */
#line 5077 "parser.y"
    {
	(yyval) = cb_build_replacing_characters ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]), save_tree_1);
	inspect_keyword = 0;
  ;}
    break;

  case 948:

/* Line 1455 of yacc.c  */
#line 5081 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 949:

/* Line 1455 of yacc.c  */
#line 5085 "parser.y"
    { /* Nothing */ ;}
    break;

  case 950:

/* Line 1455 of yacc.c  */
#line 5086 "parser.y"
    { inspect_keyword = 1; ;}
    break;

  case 951:

/* Line 1455 of yacc.c  */
#line 5087 "parser.y"
    { inspect_keyword = 2; ;}
    break;

  case 952:

/* Line 1455 of yacc.c  */
#line 5088 "parser.y"
    { inspect_keyword = 3; ;}
    break;

  case 953:

/* Line 1455 of yacc.c  */
#line 5089 "parser.y"
    { inspect_keyword = 4; ;}
    break;

  case 954:

/* Line 1455 of yacc.c  */
#line 5094 "parser.y"
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

  case 955:

/* Line 1455 of yacc.c  */
#line 5120 "parser.y"
    {
	if (cb_validate_inspect (save_tree_1, (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])) < 0 ) {
		(yyval) = cb_error_node;
	} else {
		(yyval) = cb_build_converting ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 956:

/* Line 1455 of yacc.c  */
#line 5132 "parser.y"
    { (yyval) = cb_build_inspect_region_start (); ;}
    break;

  case 957:

/* Line 1455 of yacc.c  */
#line 5134 "parser.y"
    { (yyval) = cb_build_inspect_region ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 960:

/* Line 1455 of yacc.c  */
#line 5145 "parser.y"
    { BEGIN_STATEMENT ("MERGE", 0); ;}
    break;

  case 962:

/* Line 1455 of yacc.c  */
#line 5155 "parser.y"
    { BEGIN_STATEMENT ("MOVE", 0); ;}
    break;

  case 964:

/* Line 1455 of yacc.c  */
#line 5161 "parser.y"
    {
	cb_emit_move ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 965:

/* Line 1455 of yacc.c  */
#line 5165 "parser.y"
    {
	cb_emit_move_corresponding ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 966:

/* Line 1455 of yacc.c  */
#line 5176 "parser.y"
    { BEGIN_STATEMENT ("MULTIPLY", TERM_MULTIPLY); ;}
    break;

  case 968:

/* Line 1455 of yacc.c  */
#line 5183 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '*', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 969:

/* Line 1455 of yacc.c  */
#line 5187 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '*', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 970:

/* Line 1455 of yacc.c  */
#line 5193 "parser.y"
    { terminator_warning (TERM_MULTIPLY); ;}
    break;

  case 971:

/* Line 1455 of yacc.c  */
#line 5194 "parser.y"
    { terminator_clear (TERM_MULTIPLY); ;}
    break;

  case 972:

/* Line 1455 of yacc.c  */
#line 5203 "parser.y"
    { BEGIN_STATEMENT ("OPEN", 0); ;}
    break;

  case 975:

/* Line 1455 of yacc.c  */
#line 5210 "parser.y"
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

  case 976:

/* Line 1455 of yacc.c  */
#line 5222 "parser.y"
    { (yyval) = cb_int (COB_OPEN_INPUT); ;}
    break;

  case 977:

/* Line 1455 of yacc.c  */
#line 5223 "parser.y"
    { (yyval) = cb_int (COB_OPEN_OUTPUT); ;}
    break;

  case 978:

/* Line 1455 of yacc.c  */
#line 5224 "parser.y"
    { (yyval) = cb_int (COB_OPEN_I_O); ;}
    break;

  case 979:

/* Line 1455 of yacc.c  */
#line 5225 "parser.y"
    { (yyval) = cb_int (COB_OPEN_EXTEND); ;}
    break;

  case 980:

/* Line 1455 of yacc.c  */
#line 5229 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 981:

/* Line 1455 of yacc.c  */
#line 5230 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 982:

/* Line 1455 of yacc.c  */
#line 5234 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 983:

/* Line 1455 of yacc.c  */
#line 5235 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 984:

/* Line 1455 of yacc.c  */
#line 5236 "parser.y"
    { PENDING ("OPEN ... WITH LOCK"); ;}
    break;

  case 985:

/* Line 1455 of yacc.c  */
#line 5248 "parser.y"
    { BEGIN_STATEMENT ("PERFORM", TERM_PERFORM); ;}
    break;

  case 987:

/* Line 1455 of yacc.c  */
#line 5254 "parser.y"
    {
	cb_emit_perform ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));
  ;}
    break;

  case 988:

/* Line 1455 of yacc.c  */
#line 5258 "parser.y"
    {
	perform_stack = cb_cons ((yyvsp[(1) - (1)]), perform_stack);
	check_unreached = 0;
  ;}
    break;

  case 989:

/* Line 1455 of yacc.c  */
#line 5263 "parser.y"
    {
	perform_stack = CB_CHAIN (perform_stack);
	cb_emit_perform ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 990:

/* Line 1455 of yacc.c  */
#line 5268 "parser.y"
    {
	cb_emit_perform ((yyvsp[(1) - (2)]), NULL);
  ;}
    break;

  case 991:

/* Line 1455 of yacc.c  */
#line 5274 "parser.y"
    { terminator_error (); ;}
    break;

  case 992:

/* Line 1455 of yacc.c  */
#line 5275 "parser.y"
    { terminator_clear (TERM_PERFORM); ;}
    break;

  case 993:

/* Line 1455 of yacc.c  */
#line 5280 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(1) - (1)]))->length = cb_true; /* return from $1 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (1)]), (yyvsp[(1) - (1)]));
  ;}
    break;

  case 994:

/* Line 1455 of yacc.c  */
#line 5285 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(3) - (3)]))->length = cb_true; /* return from $3 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 995:

/* Line 1455 of yacc.c  */
#line 5293 "parser.y"
    {
	(yyval) = cb_build_perform_once (NULL);
  ;}
    break;

  case 996:

/* Line 1455 of yacc.c  */
#line 5297 "parser.y"
    {
	(yyval) = cb_build_perform_forever (NULL);
  ;}
    break;

  case 997:

/* Line 1455 of yacc.c  */
#line 5301 "parser.y"
    {
	(yyval) = cb_build_perform_times ((yyvsp[(1) - (2)]));
	current_program->loop_counter++;
  ;}
    break;

  case 998:

/* Line 1455 of yacc.c  */
#line 5306 "parser.y"
    {
	cb_tree varying;

	varying = cb_list_init (cb_build_perform_varying (NULL, NULL, NULL, (yyvsp[(3) - (3)])));
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), varying);
  ;}
    break;

  case 999:

/* Line 1455 of yacc.c  */
#line 5313 "parser.y"
    {
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1000:

/* Line 1455 of yacc.c  */
#line 5319 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1001:

/* Line 1455 of yacc.c  */
#line 5320 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1002:

/* Line 1455 of yacc.c  */
#line 5324 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1003:

/* Line 1455 of yacc.c  */
#line 5326 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1004:

/* Line 1455 of yacc.c  */
#line 5331 "parser.y"
    {
	(yyval) = cb_build_perform_varying ((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1005:

/* Line 1455 of yacc.c  */
#line 5342 "parser.y"
    { BEGIN_STATEMENT ("READ", TERM_READ); ;}
    break;

  case 1006:

/* Line 1455 of yacc.c  */
#line 5345 "parser.y"
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

  case 1007:

/* Line 1455 of yacc.c  */
#line 5365 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1008:

/* Line 1455 of yacc.c  */
#line 5366 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1009:

/* Line 1455 of yacc.c  */
#line 5370 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1010:

/* Line 1455 of yacc.c  */
#line 5372 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1011:

/* Line 1455 of yacc.c  */
#line 5376 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1012:

/* Line 1455 of yacc.c  */
#line 5380 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1013:

/* Line 1455 of yacc.c  */
#line 5384 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1014:

/* Line 1455 of yacc.c  */
#line 5388 "parser.y"
    {
	(yyval) = cb_int4;
  ;}
    break;

  case 1015:

/* Line 1455 of yacc.c  */
#line 5394 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1016:

/* Line 1455 of yacc.c  */
#line 5396 "parser.y"
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

  case 1020:

/* Line 1455 of yacc.c  */
#line 5415 "parser.y"
    { terminator_warning (TERM_READ); ;}
    break;

  case 1021:

/* Line 1455 of yacc.c  */
#line 5416 "parser.y"
    { terminator_clear (TERM_READ); ;}
    break;

  case 1022:

/* Line 1455 of yacc.c  */
#line 5425 "parser.y"
    { BEGIN_STATEMENT ("RELEASE", 0); ;}
    break;

  case 1023:

/* Line 1455 of yacc.c  */
#line 5427 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_release ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
	}
  ;}
    break;

  case 1024:

/* Line 1455 of yacc.c  */
#line 5440 "parser.y"
    { BEGIN_STATEMENT ("RETURN", TERM_RETURN); ;}
    break;

  case 1025:

/* Line 1455 of yacc.c  */
#line 5443 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_return ((yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]));
	}
  ;}
    break;

  case 1026:

/* Line 1455 of yacc.c  */
#line 5451 "parser.y"
    { terminator_warning (TERM_RETURN); ;}
    break;

  case 1027:

/* Line 1455 of yacc.c  */
#line 5452 "parser.y"
    { terminator_clear (TERM_RETURN); ;}
    break;

  case 1028:

/* Line 1455 of yacc.c  */
#line 5461 "parser.y"
    { BEGIN_STATEMENT ("REWRITE", TERM_REWRITE); ;}
    break;

  case 1029:

/* Line 1455 of yacc.c  */
#line 5464 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_rewrite ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]));
	}
  ;}
    break;

  case 1030:

/* Line 1455 of yacc.c  */
#line 5472 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1031:

/* Line 1455 of yacc.c  */
#line 5474 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1032:

/* Line 1455 of yacc.c  */
#line 5478 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1033:

/* Line 1455 of yacc.c  */
#line 5484 "parser.y"
    { terminator_warning (TERM_REWRITE); ;}
    break;

  case 1034:

/* Line 1455 of yacc.c  */
#line 5485 "parser.y"
    { terminator_clear (TERM_REWRITE); ;}
    break;

  case 1035:

/* Line 1455 of yacc.c  */
#line 5495 "parser.y"
    {
	BEGIN_STATEMENT ("ROLLBACK", 0);
	cb_emit_rollback ();
  ;}
    break;

  case 1036:

/* Line 1455 of yacc.c  */
#line 5507 "parser.y"
    { BEGIN_STATEMENT ("SEARCH", TERM_SEARCH); ;}
    break;

  case 1038:

/* Line 1455 of yacc.c  */
#line 5514 "parser.y"
    {
	cb_emit_search ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1039:

/* Line 1455 of yacc.c  */
#line 5518 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1040:

/* Line 1455 of yacc.c  */
#line 5522 "parser.y"
    {
	cb_emit_search_all ((yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1041:

/* Line 1455 of yacc.c  */
#line 5528 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1042:

/* Line 1455 of yacc.c  */
#line 5529 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1043:

/* Line 1455 of yacc.c  */
#line 5533 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1044:

/* Line 1455 of yacc.c  */
#line 5535 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1045:

/* Line 1455 of yacc.c  */
#line 5539 "parser.y"
    {
	(yyval) = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 1046:

/* Line 1455 of yacc.c  */
#line 5545 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1047:

/* Line 1455 of yacc.c  */
#line 5546 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); CB_IF ((yyvsp[(1) - (2)]))->stmt2 = (yyvsp[(2) - (2)]); ;}
    break;

  case 1048:

/* Line 1455 of yacc.c  */
#line 5551 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1049:

/* Line 1455 of yacc.c  */
#line 5555 "parser.y"
    {
	(yyval) = cb_build_if ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), NULL);
  ;}
    break;

  case 1050:

/* Line 1455 of yacc.c  */
#line 5561 "parser.y"
    { terminator_warning (TERM_SEARCH); ;}
    break;

  case 1051:

/* Line 1455 of yacc.c  */
#line 5562 "parser.y"
    { terminator_clear (TERM_SEARCH); ;}
    break;

  case 1052:

/* Line 1455 of yacc.c  */
#line 5571 "parser.y"
    { BEGIN_STATEMENT ("SET", 0); ;}
    break;

  case 1059:

/* Line 1455 of yacc.c  */
#line 5587 "parser.y"
    {
	cb_emit_setenv ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1060:

/* Line 1455 of yacc.c  */
#line 5596 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (4)]), cb_build_ppointer ((yyvsp[(4) - (4)])));
  ;}
    break;

  case 1061:

/* Line 1455 of yacc.c  */
#line 5600 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1062:

/* Line 1455 of yacc.c  */
#line 5609 "parser.y"
    {
	cb_emit_set_up_down ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1063:

/* Line 1455 of yacc.c  */
#line 5615 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1064:

/* Line 1455 of yacc.c  */
#line 5616 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1067:

/* Line 1455 of yacc.c  */
#line 5628 "parser.y"
    {
	cb_emit_set_on_off ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1070:

/* Line 1455 of yacc.c  */
#line 5642 "parser.y"
    {
	cb_emit_set_true ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1071:

/* Line 1455 of yacc.c  */
#line 5646 "parser.y"
    {
	cb_emit_set_false ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1072:

/* Line 1455 of yacc.c  */
#line 5657 "parser.y"
    { BEGIN_STATEMENT ("SORT", 0); ;}
    break;

  case 1074:

/* Line 1455 of yacc.c  */
#line 5663 "parser.y"
    {
	cb_emit_sort_init ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (4)]))) && (yyvsp[(2) - (4)]) == NULL) {
		cb_error (_("File sort requires KEY phrase"));
	}
	/* used in sort_input/sort_output */
	save_tree_1 = (yyvsp[(1) - (4)]);
  ;}
    break;

  case 1075:

/* Line 1455 of yacc.c  */
#line 5672 "parser.y"
    {
	cb_emit_sort_finish ((yyvsp[(1) - (7)]));
  ;}
    break;

  case 1076:

/* Line 1455 of yacc.c  */
#line 5679 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 1077:

/* Line 1455 of yacc.c  */
#line 5684 "parser.y"
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

  case 1078:

/* Line 1455 of yacc.c  */
#line 5698 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1079:

/* Line 1455 of yacc.c  */
#line 5699 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1081:

/* Line 1455 of yacc.c  */
#line 5703 "parser.y"
    { /* nothing */ ;}
    break;

  case 1082:

/* Line 1455 of yacc.c  */
#line 5707 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1083:

/* Line 1455 of yacc.c  */
#line 5708 "parser.y"
    { (yyval) = cb_ref ((yyvsp[(3) - (3)])); ;}
    break;

  case 1084:

/* Line 1455 of yacc.c  */
#line 5713 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires USING or INPUT PROCEDURE"));
	}
  ;}
    break;

  case 1085:

/* Line 1455 of yacc.c  */
#line 5719 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("USING invalid with table SORT"));
	} else {
		cb_emit_sort_using (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1086:

/* Line 1455 of yacc.c  */
#line 5727 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("INPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_input ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1087:

/* Line 1455 of yacc.c  */
#line 5738 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires GIVING or OUTPUT PROCEDURE"));
	}
  ;}
    break;

  case 1088:

/* Line 1455 of yacc.c  */
#line 5744 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("GIVING invalid with table SORT"));
	} else {
		cb_emit_sort_giving (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1089:

/* Line 1455 of yacc.c  */
#line 5752 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("OUTPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_output ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1090:

/* Line 1455 of yacc.c  */
#line 5767 "parser.y"
    { BEGIN_STATEMENT ("START", TERM_START); ;}
    break;

  case 1091:

/* Line 1455 of yacc.c  */
#line 5768 "parser.y"
    { (yyval) = cb_int (COB_EQ); ;}
    break;

  case 1092:

/* Line 1455 of yacc.c  */
#line 5771 "parser.y"
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

  case 1093:

/* Line 1455 of yacc.c  */
#line 5788 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1094:

/* Line 1455 of yacc.c  */
#line 5789 "parser.y"
    { (yyvsp[(0) - (4)]) = (yyvsp[(3) - (4)]); (yyval) = (yyvsp[(4) - (4)]); ;}
    break;

  case 1095:

/* Line 1455 of yacc.c  */
#line 5793 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_NE : COB_EQ); ;}
    break;

  case 1096:

/* Line 1455 of yacc.c  */
#line 5794 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LE : COB_GT); ;}
    break;

  case 1097:

/* Line 1455 of yacc.c  */
#line 5795 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GE : COB_LT); ;}
    break;

  case 1098:

/* Line 1455 of yacc.c  */
#line 5796 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LT : COB_GE); ;}
    break;

  case 1099:

/* Line 1455 of yacc.c  */
#line 5797 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GT : COB_LE); ;}
    break;

  case 1100:

/* Line 1455 of yacc.c  */
#line 5801 "parser.y"
    { terminator_warning (TERM_START); ;}
    break;

  case 1101:

/* Line 1455 of yacc.c  */
#line 5802 "parser.y"
    { terminator_clear (TERM_START); ;}
    break;

  case 1102:

/* Line 1455 of yacc.c  */
#line 5811 "parser.y"
    { BEGIN_STATEMENT ("STOP", 0); ;}
    break;

  case 1103:

/* Line 1455 of yacc.c  */
#line 5813 "parser.y"
    {
	cb_emit_stop_run ((yyvsp[(4) - (4)]));
  ;}
    break;

  case 1104:

/* Line 1455 of yacc.c  */
#line 5817 "parser.y"
    {
	cb_verify (cb_stop_literal_statement, "STOP literal");
  ;}
    break;

  case 1105:

/* Line 1455 of yacc.c  */
#line 5823 "parser.y"
    { (yyval) = current_program->cb_return_code; ;}
    break;

  case 1106:

/* Line 1455 of yacc.c  */
#line 5824 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1107:

/* Line 1455 of yacc.c  */
#line 5825 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1108:

/* Line 1455 of yacc.c  */
#line 5834 "parser.y"
    { BEGIN_STATEMENT ("STRING", TERM_STRING); ;}
    break;

  case 1109:

/* Line 1455 of yacc.c  */
#line 5837 "parser.y"
    {
	cb_emit_string ((yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]));
  ;}
    break;

  case 1110:

/* Line 1455 of yacc.c  */
#line 5843 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1111:

/* Line 1455 of yacc.c  */
#line 5844 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1112:

/* Line 1455 of yacc.c  */
#line 5848 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1113:

/* Line 1455 of yacc.c  */
#line 5849 "parser.y"
    { (yyval) = cb_build_pair (cb_int0, NULL); ;}
    break;

  case 1114:

/* Line 1455 of yacc.c  */
#line 5850 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), NULL); ;}
    break;

  case 1115:

/* Line 1455 of yacc.c  */
#line 5854 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1116:

/* Line 1455 of yacc.c  */
#line 5855 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1117:

/* Line 1455 of yacc.c  */
#line 5859 "parser.y"
    { terminator_warning (TERM_STRING); ;}
    break;

  case 1118:

/* Line 1455 of yacc.c  */
#line 5860 "parser.y"
    { terminator_clear (TERM_STRING); ;}
    break;

  case 1119:

/* Line 1455 of yacc.c  */
#line 5869 "parser.y"
    { BEGIN_STATEMENT ("SUBTRACT", TERM_SUBTRACT); ;}
    break;

  case 1121:

/* Line 1455 of yacc.c  */
#line 5876 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '-', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 1122:

/* Line 1455 of yacc.c  */
#line 5880 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_list (cb_cons ((yyvsp[(3) - (6)]), (yyvsp[(1) - (6)])), '-'));
  ;}
    break;

  case 1123:

/* Line 1455 of yacc.c  */
#line 5884 "parser.y"
    {
	cb_emit_corresponding (cb_build_sub, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 1124:

/* Line 1455 of yacc.c  */
#line 5890 "parser.y"
    { terminator_warning (TERM_SUBTRACT); ;}
    break;

  case 1125:

/* Line 1455 of yacc.c  */
#line 5891 "parser.y"
    { terminator_clear (TERM_SUBTRACT); ;}
    break;

  case 1126:

/* Line 1455 of yacc.c  */
#line 5901 "parser.y"
    {
	BEGIN_STATEMENT ("SUPPRESS", 0);
	PENDING("SUPPRESS");
  ;}
    break;

  case 1129:

/* Line 1455 of yacc.c  */
#line 5916 "parser.y"
    { BEGIN_STATEMENT ("TERMINATE", 0); ;}
    break;

  case 1130:

/* Line 1455 of yacc.c  */
#line 5918 "parser.y"
    {
	PENDING("TERMINATE");
  ;}
    break;

  case 1131:

/* Line 1455 of yacc.c  */
#line 5929 "parser.y"
    { BEGIN_STATEMENT ("TRANSFORM", 0); ;}
    break;

  case 1132:

/* Line 1455 of yacc.c  */
#line 5931 "parser.y"
    {
	cb_tree		x;

	x = cb_build_converting ((yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]), cb_build_inspect_region_start ());
	cb_emit_inspect ((yyvsp[(3) - (7)]), x, cb_int0, 2);
  ;}
    break;

  case 1133:

/* Line 1455 of yacc.c  */
#line 5945 "parser.y"
    { BEGIN_STATEMENT ("UNLOCK", 0); ;}
    break;

  case 1134:

/* Line 1455 of yacc.c  */
#line 5947 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_unlock ((yyvsp[(3) - (4)]));
	}
  ;}
    break;

  case 1138:

/* Line 1455 of yacc.c  */
#line 5966 "parser.y"
    { BEGIN_STATEMENT ("UNSTRING", TERM_UNSTRING); ;}
    break;

  case 1139:

/* Line 1455 of yacc.c  */
#line 5970 "parser.y"
    {
	cb_emit_unstring ((yyvsp[(3) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]));
  ;}
    break;

  case 1140:

/* Line 1455 of yacc.c  */
#line 5976 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1141:

/* Line 1455 of yacc.c  */
#line 5978 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1142:

/* Line 1455 of yacc.c  */
#line 5982 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1143:

/* Line 1455 of yacc.c  */
#line 5984 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1144:

/* Line 1455 of yacc.c  */
#line 5989 "parser.y"
    {
	(yyval) = cb_build_unstring_delimited ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1145:

/* Line 1455 of yacc.c  */
#line 5995 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 1146:

/* Line 1455 of yacc.c  */
#line 5997 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1147:

/* Line 1455 of yacc.c  */
#line 6002 "parser.y"
    {
	(yyval) = cb_build_unstring_into ((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1148:

/* Line 1455 of yacc.c  */
#line 6008 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1149:

/* Line 1455 of yacc.c  */
#line 6009 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1150:

/* Line 1455 of yacc.c  */
#line 6013 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1151:

/* Line 1455 of yacc.c  */
#line 6014 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1152:

/* Line 1455 of yacc.c  */
#line 6018 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1153:

/* Line 1455 of yacc.c  */
#line 6019 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1154:

/* Line 1455 of yacc.c  */
#line 6023 "parser.y"
    { terminator_warning (TERM_UNSTRING); ;}
    break;

  case 1155:

/* Line 1455 of yacc.c  */
#line 6024 "parser.y"
    { terminator_clear (TERM_UNSTRING); ;}
    break;

  case 1159:

/* Line 1455 of yacc.c  */
#line 6042 "parser.y"
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

  case 1160:

/* Line 1455 of yacc.c  */
#line 6063 "parser.y"
    {
	use_global_ind = 0;
  ;}
    break;

  case 1161:

/* Line 1455 of yacc.c  */
#line 6067 "parser.y"
    {
	use_global_ind = 1;
	current_program->flag_global_use = 1;
  ;}
    break;

  case 1162:

/* Line 1455 of yacc.c  */
#line 6075 "parser.y"
    {
	cb_tree		l;

	for (l = (yyvsp[(1) - (1)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			setup_use_file (CB_FILE (cb_ref (CB_VALUE (l))));
		}
	}
  ;}
    break;

  case 1163:

/* Line 1455 of yacc.c  */
#line 6085 "parser.y"
    {
	current_program->global_handler[COB_OPEN_INPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_INPUT].handler_prog = current_program;
  ;}
    break;

  case 1164:

/* Line 1455 of yacc.c  */
#line 6090 "parser.y"
    {
	current_program->global_handler[COB_OPEN_OUTPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_OUTPUT].handler_prog = current_program;
  ;}
    break;

  case 1165:

/* Line 1455 of yacc.c  */
#line 6095 "parser.y"
    {
	current_program->global_handler[COB_OPEN_I_O].handler_label = current_section;
	current_program->global_handler[COB_OPEN_I_O].handler_prog = current_program;
  ;}
    break;

  case 1166:

/* Line 1455 of yacc.c  */
#line 6100 "parser.y"
    {
	current_program->global_handler[COB_OPEN_EXTEND].handler_label = current_section;
	current_program->global_handler[COB_OPEN_EXTEND].handler_prog = current_program;
  ;}
    break;

  case 1179:

/* Line 1455 of yacc.c  */
#line 6132 "parser.y"
    {
	PENDING ("USE FOR DEBUGGING");
  ;}
    break;

  case 1182:

/* Line 1455 of yacc.c  */
#line 6144 "parser.y"
    {
	PENDING ("USE BEFORE REPORTING");
  ;}
    break;

  case 1183:

/* Line 1455 of yacc.c  */
#line 6155 "parser.y"
    { BEGIN_STATEMENT ("WRITE", TERM_WRITE); ;}
    break;

  case 1184:

/* Line 1455 of yacc.c  */
#line 6158 "parser.y"
    {
	if ((yyvsp[(3) - (8)]) != cb_error_node) {
		cb_emit_write ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(5) - (8)]));
	}
  ;}
    break;

  case 1185:

/* Line 1455 of yacc.c  */
#line 6166 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1186:

/* Line 1455 of yacc.c  */
#line 6167 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1187:

/* Line 1455 of yacc.c  */
#line 6172 "parser.y"
    {
	(yyval) = cb_int0;
  ;}
    break;

  case 1188:

/* Line 1455 of yacc.c  */
#line 6176 "parser.y"
    {
	(yyval) = cb_build_write_advancing_lines ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 1189:

/* Line 1455 of yacc.c  */
#line 6180 "parser.y"
    {
	(yyval) = cb_build_write_advancing_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1190:

/* Line 1455 of yacc.c  */
#line 6184 "parser.y"
    {
	(yyval) = cb_build_write_advancing_page ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1191:

/* Line 1455 of yacc.c  */
#line 6190 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1192:

/* Line 1455 of yacc.c  */
#line 6191 "parser.y"
    { (yyval) = CB_AFTER; ;}
    break;

  case 1196:

/* Line 1455 of yacc.c  */
#line 6200 "parser.y"
    { terminator_warning (TERM_WRITE); ;}
    break;

  case 1197:

/* Line 1455 of yacc.c  */
#line 6201 "parser.y"
    { terminator_clear (TERM_WRITE); ;}
    break;

  case 1198:

/* Line 1455 of yacc.c  */
#line 6216 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_ACCEPT;
  ;}
    break;

  case 1199:

/* Line 1455 of yacc.c  */
#line 6224 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_DISPLAY;
  ;}
    break;

  case 1201:

/* Line 1455 of yacc.c  */
#line 6231 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1202:

/* Line 1455 of yacc.c  */
#line 6235 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1204:

/* Line 1455 of yacc.c  */
#line 6242 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1205:

/* Line 1455 of yacc.c  */
#line 6246 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1208:

/* Line 1455 of yacc.c  */
#line 6262 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1209:

/* Line 1455 of yacc.c  */
#line 6267 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1211:

/* Line 1455 of yacc.c  */
#line 6274 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1212:

/* Line 1455 of yacc.c  */
#line 6279 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1213:

/* Line 1455 of yacc.c  */
#line 6291 "parser.y"
    {
	current_statement->handler_id = COB_EC_OVERFLOW;
  ;}
    break;

  case 1215:

/* Line 1455 of yacc.c  */
#line 6298 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1216:

/* Line 1455 of yacc.c  */
#line 6302 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1218:

/* Line 1455 of yacc.c  */
#line 6309 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1219:

/* Line 1455 of yacc.c  */
#line 6313 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1220:

/* Line 1455 of yacc.c  */
#line 6325 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1221:

/* Line 1455 of yacc.c  */
#line 6330 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1222:

/* Line 1455 of yacc.c  */
#line 6335 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1223:

/* Line 1455 of yacc.c  */
#line 6344 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1224:

/* Line 1455 of yacc.c  */
#line 6348 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1225:

/* Line 1455 of yacc.c  */
#line 6355 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1226:

/* Line 1455 of yacc.c  */
#line 6359 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1227:

/* Line 1455 of yacc.c  */
#line 6371 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1228:

/* Line 1455 of yacc.c  */
#line 6376 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1229:

/* Line 1455 of yacc.c  */
#line 6381 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1230:

/* Line 1455 of yacc.c  */
#line 6390 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1231:

/* Line 1455 of yacc.c  */
#line 6394 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1232:

/* Line 1455 of yacc.c  */
#line 6401 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1233:

/* Line 1455 of yacc.c  */
#line 6405 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1236:

/* Line 1455 of yacc.c  */
#line 6421 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1237:

/* Line 1455 of yacc.c  */
#line 6426 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1238:

/* Line 1455 of yacc.c  */
#line 6431 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1239:

/* Line 1455 of yacc.c  */
#line 6440 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1240:

/* Line 1455 of yacc.c  */
#line 6444 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1241:

/* Line 1455 of yacc.c  */
#line 6451 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1242:

/* Line 1455 of yacc.c  */
#line 6455 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1243:

/* Line 1455 of yacc.c  */
#line 6467 "parser.y"
    {
	(yyval) = cb_one;
  ;}
    break;

  case 1244:

/* Line 1455 of yacc.c  */
#line 6471 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 1245:

/* Line 1455 of yacc.c  */
#line 6483 "parser.y"
    {
	(yyval) = cb_build_cond ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1246:

/* Line 1455 of yacc.c  */
#line 6490 "parser.y"
    {
	(yyval) = cb_build_expr ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1247:

/* Line 1455 of yacc.c  */
#line 6496 "parser.y"
    {
	current_expr = NULL;
  ;}
    break;

  case 1248:

/* Line 1455 of yacc.c  */
#line 6500 "parser.y"
    {
	(yyval) = cb_list_reverse (current_expr);
  ;}
    break;

  case 1250:

/* Line 1455 of yacc.c  */
#line 6507 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1251:

/* Line 1455 of yacc.c  */
#line 6508 "parser.y"
    { push_expr (')', NULL); ;}
    break;

  case 1252:

/* Line 1455 of yacc.c  */
#line 6510 "parser.y"
    { push_expr ('O', NULL); ;}
    break;

  case 1253:

/* Line 1455 of yacc.c  */
#line 6511 "parser.y"
    { push_expr ('9', NULL); ;}
    break;

  case 1254:

/* Line 1455 of yacc.c  */
#line 6512 "parser.y"
    { push_expr ('A', NULL); ;}
    break;

  case 1255:

/* Line 1455 of yacc.c  */
#line 6513 "parser.y"
    { push_expr ('L', NULL); ;}
    break;

  case 1256:

/* Line 1455 of yacc.c  */
#line 6514 "parser.y"
    { push_expr ('U', NULL); ;}
    break;

  case 1257:

/* Line 1455 of yacc.c  */
#line 6515 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1258:

/* Line 1455 of yacc.c  */
#line 6517 "parser.y"
    { push_expr ('P', NULL); ;}
    break;

  case 1259:

/* Line 1455 of yacc.c  */
#line 6518 "parser.y"
    { push_expr ('N', NULL); ;}
    break;

  case 1260:

/* Line 1455 of yacc.c  */
#line 6519 "parser.y"
    { push_expr ('x', cb_zero); ;}
    break;

  case 1261:

/* Line 1455 of yacc.c  */
#line 6521 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1264:

/* Line 1455 of yacc.c  */
#line 6527 "parser.y"
    { push_expr ('(', NULL); ;}
    break;

  case 1265:

/* Line 1455 of yacc.c  */
#line 6529 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1266:

/* Line 1455 of yacc.c  */
#line 6530 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1267:

/* Line 1455 of yacc.c  */
#line 6531 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1268:

/* Line 1455 of yacc.c  */
#line 6533 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1269:

/* Line 1455 of yacc.c  */
#line 6535 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1270:

/* Line 1455 of yacc.c  */
#line 6536 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1271:

/* Line 1455 of yacc.c  */
#line 6537 "parser.y"
    { push_expr ('*', NULL); ;}
    break;

  case 1272:

/* Line 1455 of yacc.c  */
#line 6538 "parser.y"
    { push_expr ('/', NULL); ;}
    break;

  case 1273:

/* Line 1455 of yacc.c  */
#line 6539 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1274:

/* Line 1455 of yacc.c  */
#line 6541 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1275:

/* Line 1455 of yacc.c  */
#line 6542 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1276:

/* Line 1455 of yacc.c  */
#line 6543 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1277:

/* Line 1455 of yacc.c  */
#line 6544 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1278:

/* Line 1455 of yacc.c  */
#line 6545 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1279:

/* Line 1455 of yacc.c  */
#line 6546 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1280:

/* Line 1455 of yacc.c  */
#line 6548 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1281:

/* Line 1455 of yacc.c  */
#line 6549 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1282:

/* Line 1455 of yacc.c  */
#line 6550 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1283:

/* Line 1455 of yacc.c  */
#line 6551 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1284:

/* Line 1455 of yacc.c  */
#line 6552 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1285:

/* Line 1455 of yacc.c  */
#line 6553 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1286:

/* Line 1455 of yacc.c  */
#line 6555 "parser.y"
    { push_expr ('&', NULL); ;}
    break;

  case 1287:

/* Line 1455 of yacc.c  */
#line 6556 "parser.y"
    { push_expr ('|', NULL); ;}
    break;

  case 1299:

/* Line 1455 of yacc.c  */
#line 6568 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1300:

/* Line 1455 of yacc.c  */
#line 6569 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1304:

/* Line 1455 of yacc.c  */
#line 6578 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1305:

/* Line 1455 of yacc.c  */
#line 6579 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '+', (yyvsp[(3) - (3)])); ;}
    break;

  case 1306:

/* Line 1455 of yacc.c  */
#line 6580 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '-', (yyvsp[(3) - (3)])); ;}
    break;

  case 1307:

/* Line 1455 of yacc.c  */
#line 6581 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '*', (yyvsp[(3) - (3)])); ;}
    break;

  case 1308:

/* Line 1455 of yacc.c  */
#line 6582 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '/', (yyvsp[(3) - (3)])); ;}
    break;

  case 1309:

/* Line 1455 of yacc.c  */
#line 6583 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1310:

/* Line 1455 of yacc.c  */
#line 6584 "parser.y"
    { (yyval) = cb_build_binary_op (cb_zero, '-', (yyvsp[(2) - (2)])); ;}
    break;

  case 1311:

/* Line 1455 of yacc.c  */
#line 6585 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '^', (yyvsp[(3) - (3)])); ;}
    break;

  case 1312:

/* Line 1455 of yacc.c  */
#line 6586 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1313:

/* Line 1455 of yacc.c  */
#line 6598 "parser.y"
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

  case 1314:

/* Line 1455 of yacc.c  */
#line 6610 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(3) - (3)])))) {
		(yyval) = CB_FILE (cb_ref ((yyvsp[(3) - (3)])))->linage_ctr;
	} else {
		cb_error_x ((yyvsp[(3) - (3)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(3) - (3)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1315:

/* Line 1455 of yacc.c  */
#line 6624 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1316:

/* Line 1455 of yacc.c  */
#line 6626 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1317:

/* Line 1455 of yacc.c  */
#line 6630 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)])); ;}
    break;

  case 1318:

/* Line 1455 of yacc.c  */
#line 6636 "parser.y"
    { cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1319:

/* Line 1455 of yacc.c  */
#line 6643 "parser.y"
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

  case 1320:

/* Line 1455 of yacc.c  */
#line 6663 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1321:

/* Line 1455 of yacc.c  */
#line 6667 "parser.y"
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

  case 1322:

/* Line 1455 of yacc.c  */
#line 6683 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (1)])))) {
		(yyval) = (yyvsp[(1) - (1)]);
	} else {
		cb_error_x ((yyvsp[(1) - (1)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(1) - (1)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1323:

/* Line 1455 of yacc.c  */
#line 6696 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1324:

/* Line 1455 of yacc.c  */
#line 6698 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1325:

/* Line 1455 of yacc.c  */
#line 6702 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1326:

/* Line 1455 of yacc.c  */
#line 6708 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1327:

/* Line 1455 of yacc.c  */
#line 6710 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1328:

/* Line 1455 of yacc.c  */
#line 6715 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	CB_REFERENCE ((yyval))->offset = CB_TREE (current_section);
	current_program->label_list = cb_cons ((yyval), current_program->label_list);
  ;}
    break;

  case 1332:

/* Line 1455 of yacc.c  */
#line 6730 "parser.y"
    {
	(yyval) = cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(1) - (1)]))->data));
	(yyval)->source_file = (yyvsp[(1) - (1)])->source_file;
	(yyval)->source_line = (yyvsp[(1) - (1)])->source_line;
  ;}
    break;

  case 1333:

/* Line 1455 of yacc.c  */
#line 6740 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1334:

/* Line 1455 of yacc.c  */
#line 6741 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1335:

/* Line 1455 of yacc.c  */
#line 6746 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	current_program->reference_list = cb_cons ((yyval), current_program->reference_list);
  ;}
    break;

  case 1336:

/* Line 1455 of yacc.c  */
#line 6753 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1337:

/* Line 1455 of yacc.c  */
#line 6754 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1340:

/* Line 1455 of yacc.c  */
#line 6766 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE ((yyval))->word->count > 0) {
		redefinition_error ((yyval));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1341:

/* Line 1455 of yacc.c  */
#line 6785 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1342:

/* Line 1455 of yacc.c  */
#line 6786 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1344:

/* Line 1455 of yacc.c  */
#line 6791 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1345:

/* Line 1455 of yacc.c  */
#line 6795 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1346:

/* Line 1455 of yacc.c  */
#line 6796 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1348:

/* Line 1455 of yacc.c  */
#line 6801 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1349:

/* Line 1455 of yacc.c  */
#line 6802 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1350:

/* Line 1455 of yacc.c  */
#line 6803 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1351:

/* Line 1455 of yacc.c  */
#line 6804 "parser.y"
    { (yyval) = cb_build_ppointer ((yyvsp[(4) - (4)])); ;}
    break;

  case 1352:

/* Line 1455 of yacc.c  */
#line 6805 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1357:

/* Line 1455 of yacc.c  */
#line 6813 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1358:

/* Line 1455 of yacc.c  */
#line 6814 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1359:

/* Line 1455 of yacc.c  */
#line 6815 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1365:

/* Line 1455 of yacc.c  */
#line 6827 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1366:

/* Line 1455 of yacc.c  */
#line 6828 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1378:

/* Line 1455 of yacc.c  */
#line 6862 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1379:

/* Line 1455 of yacc.c  */
#line 6870 "parser.y"
    { (yyval) = cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1380:

/* Line 1455 of yacc.c  */
#line 6874 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1381:

/* Line 1455 of yacc.c  */
#line 6875 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1382:

/* Line 1455 of yacc.c  */
#line 6876 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1383:

/* Line 1455 of yacc.c  */
#line 6877 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 1384:

/* Line 1455 of yacc.c  */
#line 6881 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1385:

/* Line 1455 of yacc.c  */
#line 6882 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); CB_REFERENCE ((yyvsp[(1) - (3)]))->chain = (yyvsp[(3) - (3)]); ;}
    break;

  case 1386:

/* Line 1455 of yacc.c  */
#line 6887 "parser.y"
    {
	if (cb_ref ((yyvsp[(0) - (3)])) != cb_error_node) {
		(yyval) = (yyvsp[(0) - (3)]);
		CB_REFERENCE ((yyvsp[(0) - (3)]))->subs = cb_list_reverse ((yyvsp[(2) - (3)]));
	}
  ;}
    break;

  case 1387:

/* Line 1455 of yacc.c  */
#line 6897 "parser.y"
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

  case 1388:

/* Line 1455 of yacc.c  */
#line 6915 "parser.y"
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

  case 1389:

/* Line 1455 of yacc.c  */
#line 6942 "parser.y"
    {
	if (cb_tree_category ((yyvsp[(1) - (1)])) != CB_CATEGORY_NUMERIC) {
		cb_error (_("Integer value expected"));
	} else if (CB_LITERAL ((yyvsp[(1) - (1)]))->sign < 0 || CB_LITERAL ((yyvsp[(1) - (1)]))->scale) {
		cb_error (_("Integer value expected"));
	}
	(yyval) = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1390:

/* Line 1455 of yacc.c  */
#line 6953 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1391:

/* Line 1455 of yacc.c  */
#line 6955 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (2)]);
	if (CB_LITERAL_P ((yyvsp[(2) - (2)]))) {
		CB_LITERAL ((yyvsp[(2) - (2)]))->all = 1;
	}
  ;}
    break;

  case 1392:

/* Line 1455 of yacc.c  */
#line 6964 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1393:

/* Line 1455 of yacc.c  */
#line 6965 "parser.y"
    { (yyval) = cb_concat_literals ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1394:

/* Line 1455 of yacc.c  */
#line 6969 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1395:

/* Line 1455 of yacc.c  */
#line 6970 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 1396:

/* Line 1455 of yacc.c  */
#line 6971 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1397:

/* Line 1455 of yacc.c  */
#line 6972 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 1398:

/* Line 1455 of yacc.c  */
#line 6973 "parser.y"
    { (yyval) = cb_high; ;}
    break;

  case 1399:

/* Line 1455 of yacc.c  */
#line 6974 "parser.y"
    { (yyval) = cb_low; ;}
    break;

  case 1400:

/* Line 1455 of yacc.c  */
#line 6975 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1401:

/* Line 1455 of yacc.c  */
#line 6984 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1402:

/* Line 1455 of yacc.c  */
#line 6988 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1403:

/* Line 1455 of yacc.c  */
#line 6992 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1404:

/* Line 1455 of yacc.c  */
#line 6996 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1405:

/* Line 1455 of yacc.c  */
#line 7000 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1406:

/* Line 1455 of yacc.c  */
#line 7004 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1407:

/* Line 1455 of yacc.c  */
#line 7008 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1408:

/* Line 1455 of yacc.c  */
#line 7012 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1409:

/* Line 1455 of yacc.c  */
#line 7016 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1410:

/* Line 1455 of yacc.c  */
#line 7020 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), NULL);
  ;}
    break;

  case 1411:

/* Line 1455 of yacc.c  */
#line 7024 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1412:

/* Line 1455 of yacc.c  */
#line 7028 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), NULL);
  ;}
    break;

  case 1413:

/* Line 1455 of yacc.c  */
#line 7034 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1414:

/* Line 1455 of yacc.c  */
#line 7035 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (4)]), NULL); ;}
    break;

  case 1415:

/* Line 1455 of yacc.c  */
#line 7036 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 1416:

/* Line 1455 of yacc.c  */
#line 7040 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1417:

/* Line 1455 of yacc.c  */
#line 7041 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1418:

/* Line 1455 of yacc.c  */
#line 7045 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1419:

/* Line 1455 of yacc.c  */
#line 7046 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1420:

/* Line 1455 of yacc.c  */
#line 7052 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_int0);
  ;}
    break;

  case 1421:

/* Line 1455 of yacc.c  */
#line 7059 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int1);
  ;}
    break;

  case 1422:

/* Line 1455 of yacc.c  */
#line 7066 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int2);
  ;}
    break;

  case 1423:

/* Line 1455 of yacc.c  */
#line 7076 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1424:

/* Line 1455 of yacc.c  */
#line 7083 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1425:

/* Line 1455 of yacc.c  */
#line 7093 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1426:

/* Line 1455 of yacc.c  */
#line 7100 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_ref ((yyvsp[(3) - (3)])));
  ;}
    break;

  case 1427:

/* Line 1455 of yacc.c  */
#line 7113 "parser.y"
    {
	non_const_word = 1;
  ;}
    break;

  case 1428:

/* Line 1455 of yacc.c  */
#line 7123 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1429:

/* Line 1455 of yacc.c  */
#line 7124 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1430:

/* Line 1455 of yacc.c  */
#line 7128 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1431:

/* Line 1455 of yacc.c  */
#line 7129 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1432:

/* Line 1455 of yacc.c  */
#line 7133 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1433:

/* Line 1455 of yacc.c  */
#line 7134 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1434:

/* Line 1455 of yacc.c  */
#line 7138 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1435:

/* Line 1455 of yacc.c  */
#line 7139 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1436:

/* Line 1455 of yacc.c  */
#line 7140 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 1437:

/* Line 1455 of yacc.c  */
#line 7144 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1438:

/* Line 1455 of yacc.c  */
#line 7145 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1439:

/* Line 1455 of yacc.c  */
#line 7149 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1440:

/* Line 1455 of yacc.c  */
#line 7150 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1441:

/* Line 1455 of yacc.c  */
#line 7154 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1442:

/* Line 1455 of yacc.c  */
#line 7155 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1443:

/* Line 1455 of yacc.c  */
#line 7159 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1444:

/* Line 1455 of yacc.c  */
#line 7160 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1456:

/* Line 1455 of yacc.c  */
#line 7173 "parser.y"
    { (yyval) = cb_int1; ;}
    break;



/* Line 1455 of yacc.c  */
#line 14325 "parser.c"
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
#line 7217 "parser.y"


