
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



/* Line 189 of yacc.c  */
#line 358 "parser.c"

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
     LEVEL_NUMBER_WORD = 478,
     LEVEL88_NUMBER_WORD = 479,
     LIMIT = 480,
     LIMITS = 481,
     LINAGE = 482,
     LINAGE_COUNTER = 483,
     LINE = 484,
     LINES = 485,
     LINKAGE = 486,
     LITERAL = 487,
     LOCALE = 488,
     LOCALE_DT_FUNC = 489,
     LOCAL_STORAGE = 490,
     LOCK = 491,
     LOWER_CASE_FUNC = 492,
     LOWLIGHT = 493,
     LOW_VALUE = 494,
     MANUAL = 495,
     MEMORY = 496,
     MERGE = 497,
     MINUS = 498,
     MNEMONIC_NAME = 499,
     MODE = 500,
     MOVE = 501,
     MULTIPLE = 502,
     MULTIPLY = 503,
     NATIONAL = 504,
     NATIONAL_EDITED = 505,
     NATIVE = 506,
     NE = 507,
     NEGATIVE = 508,
     NEXT = 509,
     NEXT_SENTENCE = 510,
     NO = 511,
     NOT = 512,
     NOT_END = 513,
     NOT_EOP = 514,
     NOT_EXCEPTION = 515,
     NOT_INVALID_KEY = 516,
     NOT_OVERFLOW = 517,
     NOT_SIZE_ERROR = 518,
     NO_ADVANCING = 519,
     NUMBER = 520,
     NUMBERS = 521,
     NUMERIC = 522,
     NUMERIC_EDITED = 523,
     NUMVALC_FUNC = 524,
     OBJECT_COMPUTER = 525,
     OCCURS = 526,
     OF = 527,
     OFF = 528,
     OMITTED = 529,
     ON = 530,
     ONLY = 531,
     OPEN = 532,
     OPTIONAL = 533,
     OR = 534,
     ORDER = 535,
     ORGANIZATION = 536,
     OTHER = 537,
     OUTPUT = 538,
     OVERFLOW = 539,
     OVERLINE = 540,
     PACKED_DECIMAL = 541,
     PADDING = 542,
     PAGE = 543,
     PAGE_FOOTING = 544,
     PAGE_HEADING = 545,
     PARAGRAPH = 546,
     PERFORM = 547,
     PICTURE = 548,
     PLUS = 549,
     POINTER = 550,
     POSITION = 551,
     POSITIVE = 552,
     PRESENT = 553,
     PREVIOUS = 554,
     PRINTER = 555,
     PRINTING = 556,
     PROCEDURE = 557,
     PROCEDURES = 558,
     PROCEED = 559,
     PROGRAM = 560,
     PROGRAM_ID = 561,
     PROGRAM_NAME = 562,
     PROGRAM_POINTER = 563,
     PROMPT = 564,
     QUOTE = 565,
     RANDOM = 566,
     RD = 567,
     READ = 568,
     RECORD = 569,
     RECORDING = 570,
     RECORDS = 571,
     RECURSIVE = 572,
     REDEFINES = 573,
     REEL = 574,
     REFERENCE = 575,
     RELATIVE = 576,
     RELEASE = 577,
     REMAINDER = 578,
     REMOVAL = 579,
     RENAMES = 580,
     REPLACING = 581,
     REPORT = 582,
     REPORTING = 583,
     REPORTS = 584,
     REPORT_FOOTING = 585,
     REPORT_HEADING = 586,
     REPOSITORY = 587,
     REQUIRED = 588,
     RESERVE = 589,
     RETURN = 590,
     RETURNING = 591,
     REVERSE_FUNC = 592,
     REVERSE_VIDEO = 593,
     REWIND = 594,
     REWRITE = 595,
     RIGHT = 596,
     ROLLBACK = 597,
     ROUNDED = 598,
     RUN = 599,
     SAME = 600,
     SCREEN = 601,
     SCREEN_CONTROL = 602,
     SCROLL = 603,
     SD = 604,
     SEARCH = 605,
     SECTION = 606,
     SECURE = 607,
     SEGMENT_LIMIT = 608,
     SELECT = 609,
     SEMI_COLON = 610,
     SENTENCE = 611,
     SEPARATE = 612,
     SEQUENCE = 613,
     SEQUENTIAL = 614,
     SET = 615,
     SHARING = 616,
     SIGN = 617,
     SIGNED = 618,
     SIGNED_INT = 619,
     SIGNED_LONG = 620,
     SIGNED_SHORT = 621,
     SIZE = 622,
     SIZE_ERROR = 623,
     SORT = 624,
     SORT_MERGE = 625,
     SOURCE = 626,
     SOURCE_COMPUTER = 627,
     SPACE = 628,
     SPECIAL_NAMES = 629,
     STANDARD = 630,
     STANDARD_1 = 631,
     STANDARD_2 = 632,
     START = 633,
     STATUS = 634,
     STOP = 635,
     STRING = 636,
     SUBSTITUTE_FUNC = 637,
     SUBSTITUTE_CASE_FUNC = 638,
     SUBTRACT = 639,
     SUM = 640,
     SUPPRESS = 641,
     SYMBOLIC = 642,
     SYNCHRONIZED = 643,
     TALLYING = 644,
     TAPE = 645,
     TERMINATE = 646,
     TEST = 647,
     THAN = 648,
     THEN = 649,
     THRU = 650,
     TIME = 651,
     TIMES = 652,
     TO = 653,
     TOK_FALSE = 654,
     TOK_FILE = 655,
     TOK_INITIAL = 656,
     TOK_NULL = 657,
     TOK_TRUE = 658,
     TOP = 659,
     TRAILING = 660,
     TRANSFORM = 661,
     TRIM_FUNCTION = 662,
     TYPE = 663,
     UNDERLINE = 664,
     UNIT = 665,
     UNLOCK = 666,
     UNSIGNED = 667,
     UNSIGNED_INT = 668,
     UNSIGNED_LONG = 669,
     UNSIGNED_SHORT = 670,
     UNSTRING = 671,
     UNTIL = 672,
     UP = 673,
     UPDATE = 674,
     UPON = 675,
     UPON_ARGUMENT_NUMBER = 676,
     UPON_COMMAND_LINE = 677,
     UPON_ENVIRONMENT_NAME = 678,
     UPON_ENVIRONMENT_VALUE = 679,
     UPPER_CASE_FUNC = 680,
     USAGE = 681,
     USE = 682,
     USING = 683,
     VALUE = 684,
     VARYING = 685,
     WAIT = 686,
     WHEN = 687,
     WHEN_COMPILED_FUNC = 688,
     WHEN_OTHER = 689,
     WITH = 690,
     WORD = 691,
     WORDS = 692,
     WORKING_STORAGE = 693,
     WRITE = 694,
     YYYYDDD = 695,
     YYYYMMDD = 696,
     ZERO = 697,
     UNARY_SIGN = 698
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
#line 844 "parser.c"

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
#define YYLAST   5488

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  457
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  702
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1563
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2300

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   698

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   456,     2,
     452,   451,   445,   443,     2,   444,   449,   446,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   455,     2,
     454,   450,   453,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   448,     2,     2,     2,     2,     2,
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
     435,   436,   437,   438,   439,   440,   441,   442,   447
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
     499,   501,   503,   505,   507,   509,   515,   520,   525,   526,
     528,   530,   531,   533,   535,   537,   539,   541,   546,   548,
     550,   552,   559,   568,   569,   572,   575,   577,   578,   581,
     583,   587,   593,   594,   596,   598,   603,   606,   609,   611,
     612,   617,   623,   626,   628,   630,   634,   636,   638,   642,
     644,   646,   649,   654,   659,   664,   671,   676,   680,   684,
     687,   690,   693,   694,   698,   699,   702,   704,   707,   709,
     711,   713,   719,   720,   722,   724,   726,   732,   734,   737,
     740,   741,   744,   749,   750,   760,   761,   762,   768,   769,
     773,   774,   777,   781,   784,   787,   789,   791,   792,   797,
     798,   801,   804,   807,   809,   811,   813,   815,   817,   819,
     821,   823,   825,   827,   833,   834,   836,   838,   843,   850,
     860,   861,   865,   866,   869,   870,   873,   877,   879,   881,
     887,   893,   895,   897,   901,   907,   908,   911,   913,   915,
     917,   923,   928,   932,   937,   941,   945,   949,   950,   951,
     957,   958,   960,   961,   964,   967,   971,   974,   976,   977,
     983,   984,   989,   991,   993,   994,   996,   997,   999,  1001,
    1003,  1004,  1007,  1009,  1013,  1017,  1024,  1025,  1028,  1030,
    1032,  1034,  1036,  1038,  1040,  1042,  1044,  1046,  1048,  1050,
    1052,  1054,  1056,  1058,  1061,  1065,  1066,  1069,  1072,  1074,
    1076,  1080,  1082,  1084,  1086,  1088,  1090,  1092,  1094,  1096,
    1098,  1100,  1102,  1104,  1106,  1108,  1110,  1112,  1114,  1116,
    1118,  1121,  1124,  1126,  1129,  1132,  1134,  1137,  1140,  1142,
    1145,  1148,  1150,  1153,  1156,  1158,  1160,  1164,  1168,  1176,
    1177,  1180,  1181,  1185,  1187,  1188,  1194,  1196,  1198,  1199,
    1203,  1205,  1208,  1210,  1213,  1216,  1217,  1219,  1221,  1225,
    1227,  1231,  1232,  1241,  1243,  1246,  1248,  1252,  1253,  1257,
    1260,  1265,  1268,  1269,  1270,  1276,  1277,  1278,  1284,  1285,
    1286,  1292,  1293,  1295,  1297,  1300,  1306,  1307,  1310,  1313,
    1317,  1319,  1321,  1324,  1327,  1330,  1331,  1333,  1335,  1338,
    1347,  1348,  1352,  1353,  1358,  1359,  1364,  1365,  1369,  1370,
    1374,  1376,  1381,  1384,  1386,  1388,  1389,  1392,  1397,  1398,
    1401,  1403,  1405,  1407,  1409,  1411,  1413,  1415,  1417,  1419,
    1421,  1423,  1425,  1427,  1429,  1431,  1433,  1437,  1439,  1441,
    1443,  1445,  1447,  1449,  1451,  1456,  1461,  1464,  1466,  1468,
    1471,  1475,  1477,  1481,  1488,  1491,  1495,  1498,  1500,  1503,
    1506,  1508,  1511,  1512,  1514,  1516,  1521,  1524,  1525,  1527,
    1529,  1530,  1531,  1532,  1539,  1540,  1542,  1544,  1547,  1549,
    1550,  1556,  1557,  1560,  1562,  1564,  1566,  1568,  1571,  1574,
    1576,  1578,  1580,  1582,  1584,  1586,  1588,  1590,  1592,  1594,
    1600,  1606,  1610,  1614,  1616,  1618,  1620,  1622,  1624,  1626,
    1628,  1631,  1634,  1637,  1638,  1640,  1642,  1644,  1646,  1647,
    1649,  1651,  1653,  1655,  1659,  1660,  1661,  1662,  1672,  1673,
    1674,  1678,  1679,  1683,  1685,  1688,  1693,  1694,  1697,  1700,
    1701,  1705,  1709,  1714,  1718,  1719,  1721,  1722,  1725,  1726,
    1727,  1735,  1736,  1739,  1741,  1743,  1745,  1748,  1750,  1755,
    1758,  1760,  1762,  1763,  1765,  1766,  1767,  1771,  1772,  1775,
    1777,  1779,  1781,  1783,  1785,  1787,  1789,  1791,  1793,  1795,
    1797,  1799,  1801,  1803,  1805,  1807,  1809,  1811,  1813,  1815,
    1817,  1819,  1821,  1823,  1825,  1827,  1829,  1831,  1833,  1835,
    1837,  1839,  1841,  1843,  1845,  1847,  1849,  1851,  1853,  1855,
    1857,  1859,  1861,  1863,  1865,  1867,  1869,  1871,  1873,  1875,
    1876,  1881,  1886,  1891,  1895,  1899,  1903,  1908,  1912,  1917,
    1921,  1925,  1929,  1934,  1940,  1944,  1949,  1953,  1957,  1958,
    1962,  1966,  1969,  1972,  1975,  1979,  1983,  1987,  1988,  1991,
    1993,  1996,  1998,  2000,  2002,  2004,  2006,  2008,  2010,  2014,
    2018,  2022,  2026,  2028,  2030,  2032,  2034,  2036,  2038,  2039,
    2041,  2042,  2047,  2052,  2058,  2065,  2066,  2069,  2070,  2072,
    2073,  2077,  2081,  2087,  2088,  2091,  2094,  2095,  2101,  2102,
    2105,  2106,  2115,  2116,  2117,  2121,  2123,  2126,  2129,  2133,
    2134,  2137,  2140,  2143,  2144,  2147,  2150,  2151,  2152,  2156,
    2157,  2158,  2162,  2163,  2165,  2166,  2170,  2171,  2174,  2175,
    2179,  2180,  2184,  2185,  2187,  2191,  2195,  2198,  2200,  2202,
    2203,  2208,  2213,  2214,  2216,  2218,  2220,  2222,  2224,  2225,
    2232,  2233,  2235,  2236,  2241,  2242,  2247,  2251,  2255,  2259,
    2263,  2268,  2275,  2282,  2289,  2296,  2297,  2300,  2303,  2305,
    2308,  2310,  2312,  2315,  2318,  2320,  2322,  2324,  2326,  2328,
    2332,  2336,  2340,  2344,  2346,  2348,  2349,  2351,  2352,  2357,
    2362,  2369,  2376,  2385,  2394,  2395,  2397,  2398,  2403,  2404,
    2410,  2412,  2416,  2418,  2420,  2422,  2425,  2427,  2430,  2431,
    2435,  2436,  2437,  2441,  2444,  2448,  2450,  2454,  2457,  2459,
    2461,  2463,  2464,  2467,  2468,  2470,  2471,  2475,  2476,  2478,
    2480,  2483,  2485,  2487,  2488,  2492,  2493,  2497,  2498,  2504,
    2505,  2509,  2510,  2513,  2514,  2515,  2524,  2528,  2529,  2530,
    2534,  2535,  2537,  2538,  2546,  2547,  2550,  2551,  2555,  2559,
    2560,  2563,  2565,  2568,  2573,  2575,  2577,  2579,  2581,  2583,
    2585,  2587,  2588,  2590,  2591,  2595,  2596,  2601,  2603,  2605,
    2607,  2609,  2612,  2614,  2616,  2618,  2619,  2623,  2625,  2628,
    2631,  2634,  2636,  2638,  2640,  2643,  2646,  2648,  2651,  2656,
    2659,  2660,  2662,  2664,  2666,  2668,  2673,  2679,  2680,  2685,
    2686,  2688,  2689,  2693,  2694,  2698,  2702,  2707,  2708,  2713,
    2718,  2725,  2726,  2728,  2729,  2733,  2734,  2740,  2742,  2744,
    2746,  2748,  2749,  2753,  2754,  2758,  2761,  2762,  2766,  2769,
    2770,  2775,  2778,  2779,  2781,  2783,  2787,  2788,  2790,  2793,
    2797,  2801,  2802,  2806,  2808,  2812,  2820,  2821,  2832,  2833,
    2836,  2837,  2840,  2843,  2847,  2851,  2854,  2855,  2859,  2860,
    2862,  2864,  2865,  2867,  2868,  2873,  2874,  2882,  2883,  2885,
    2886,  2894,  2895,  2898,  2902,  2903,  2905,  2907,  2908,  2913,
    2918,  2919,  2927,  2928,  2931,  2932,  2933,  2938,  2940,  2943,
    2944,  2949,  2950,  2952,  2953,  2957,  2959,  2961,  2963,  2965,
    2967,  2972,  2977,  2981,  2986,  2988,  2990,  2992,  2995,  2999,
    3001,  3004,  3008,  3012,  3013,  3017,  3018,  3026,  3027,  3033,
    3034,  3037,  3038,  3041,  3042,  3046,  3047,  3050,  3055,  3056,
    3059,  3064,  3065,  3066,  3074,  3075,  3080,  3083,  3086,  3089,
    3092,  3095,  3096,  3098,  3099,  3104,  3107,  3108,  3111,  3114,
    3115,  3124,  3126,  3129,  3131,  3135,  3139,  3140,  3144,  3145,
    3147,  3148,  3153,  3158,  3165,  3172,  3173,  3175,  3178,  3179,
    3181,  3182,  3186,  3187,  3195,  3196,  3201,  3202,  3204,  3206,
    3207,  3217,  3218,  3222,  3224,  3228,  3231,  3234,  3237,  3241,
    3242,  3246,  3247,  3251,  3252,  3256,  3257,  3259,  3261,  3263,
    3265,  3274,  3275,  3277,  3279,  3281,  3283,  3285,  3287,  3288,
    3290,  3291,  3293,  3295,  3297,  3299,  3301,  3303,  3305,  3306,
    3308,  3314,  3316,  3319,  3325,  3326,  3335,  3336,  3339,  3340,
    3345,  3349,  3353,  3355,  3357,  3358,  3360,  3362,  3363,  3365,
    3368,  3371,  3372,  3373,  3377,  3378,  3379,  3383,  3386,  3387,
    3388,  3392,  3393,  3394,  3398,  3401,  3402,  3403,  3407,  3408,
    3409,  3413,  3415,  3417,  3420,  3421,  3425,  3426,  3430,  3432,
    3434,  3437,  3438,  3442,  3443,  3447,  3448,  3450,  3452,  3454,
    3457,  3458,  3462,  3463,  3467,  3468,  3472,  3474,  3476,  3477,
    3480,  3483,  3486,  3489,  3492,  3495,  3498,  3501,  3504,  3507,
    3510,  3513,  3516,  3519,  3520,  3523,  3526,  3529,  3532,  3535,
    3538,  3541,  3544,  3547,  3550,  3553,  3556,  3559,  3562,  3565,
    3568,  3571,  3574,  3577,  3580,  3583,  3586,  3589,  3592,  3595,
    3597,  3600,  3602,  3604,  3607,  3609,  3612,  3614,  3620,  3625,
    3627,  3633,  3638,  3640,  3644,  3645,  3647,  3649,  3651,  3655,
    3659,  3663,  3667,  3670,  3673,  3677,  3681,  3683,  3687,  3689,
    3692,  3695,  3697,  3699,  3701,  3704,  3706,  3708,  3711,  3713,
    3714,  3717,  3719,  3721,  3723,  3727,  3729,  3731,  3734,  3736,
    3737,  3739,  3741,  3743,  3745,  3747,  3750,  3752,  3756,  3758,
    3761,  3763,  3767,  3771,  3775,  3780,  3784,  3786,  3788,  3790,
    3792,  3796,  3800,  3804,  3806,  3808,  3810,  3812,  3814,  3816,
    3818,  3820,  3822,  3824,  3826,  3828,  3830,  3832,  3834,  3836,
    3838,  3840,  3842,  3844,  3846,  3849,  3852,  3856,  3858,  3862,
    3866,  3871,  3877,  3879,  3881,  3884,  3886,  3890,  3892,  3894,
    3896,  3898,  3900,  3902,  3904,  3907,  3910,  3916,  3922,  3928,
    3934,  3940,  3946,  3952,  3957,  3963,  3966,  3967,  3972,  3978,
    3979,  3983,  3984,  3986,  3988,  3992,  3996,  3998,  4002,  4004,
    4008,  4009,  4010,  4012,  4013,  4015,  4016,  4018,  4019,  4021,
    4023,  4024,  4026,  4027,  4029,  4030,  4032,  4033,  4036,  4038,
    4040,  4043,  4046,  4049,  4051,  4054,  4056,  4057,  4059,  4060,
    4062,  4063,  4065,  4066,  4068,  4069,  4071,  4072,  4074,  4075,
    4077,  4078,  4080,  4081,  4083,  4084,  4086,  4087,  4089,  4090,
    4092,  4093,  4095,  4096,  4098,  4099,  4101,  4102,  4104,  4105,
    4107,  4108,  4110,  4112,  4113,  4115,  4116,  4118,  4120,  4121,
    4123,  4124,  4126,  4127,  4129,  4130,  4132,  4133,  4135,  4136,
    4138,  4141,  4142,  4144,  4145,  4147,  4148,  4150,  4151,  4153,
    4154,  4156,  4157,  4159,  4160,  4162,  4165,  4166,  4168,  4169,
    4171,  4172,  4174,  4175,  4177,  4178,  4180,  4181,  4183,  4184,
    4186,  4187,  4189,  4190
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     458,     0,    -1,    -1,   459,   460,     0,    -1,   461,    -1,
     460,   461,    -1,   462,    -1,   468,    -1,    -1,    -1,   475,
     483,   463,   585,   464,   723,   471,   472,    -1,    -1,    -1,
     475,   483,   466,   585,   467,   723,   471,   473,    -1,    -1,
      -1,   477,   483,   469,   585,   470,   723,   474,    -1,    -1,
     465,    -1,   471,   465,    -1,    -1,   136,   478,   449,    -1,
     136,   478,   449,    -1,   132,   478,   449,    -1,    -1,   306,
     449,   478,   479,   476,   480,   449,    -1,   179,   449,   478,
     479,   449,    -1,   307,    -1,   232,    -1,    -1,    27,   232,
      -1,    -1,  1133,   481,  1144,    -1,    72,    -1,    72,   482,
      -1,   482,    -1,   401,    -1,   317,    -1,    -1,   147,   117,
     449,   484,   538,    -1,    -1,    82,   351,   449,   485,    -1,
      -1,   485,   486,    -1,   487,    -1,   491,    -1,   504,    -1,
     499,    -1,   372,   449,   488,    -1,    -1,   490,   449,    -1,
     490,   489,   449,    -1,   489,   449,    -1,  1158,   104,   245,
      -1,   436,    -1,   270,   449,   492,    -1,    -1,   490,   449,
      -1,   490,   493,   449,    -1,   493,   449,    -1,   494,    -1,
     493,   494,    -1,   495,    -1,   497,    -1,   498,    -1,   241,
     367,  1133,  1093,   496,    -1,    56,    -1,   437,    -1,  1144,
    1116,  1133,  1072,    -1,   353,  1133,  1093,    -1,   332,   449,
     500,    -1,    -1,   501,   449,    -1,   502,    -1,   501,   502,
      -1,   178,   503,   207,    -1,   178,     9,   207,    -1,   232,
      -1,   503,   232,    -1,   374,   449,   505,    -1,    -1,   506,
      -1,   506,   449,    -1,   507,    -1,   506,   507,    -1,   508,
      -1,   515,    -1,   524,    -1,   531,    -1,   528,    -1,   532,
      -1,   533,    -1,   534,    -1,   535,    -1,   536,    -1,   537,
      -1,   436,  1133,    94,    -1,    -1,   436,  1133,  1075,   509,
     511,    -1,    -1,   436,  1133,   510,   512,    -1,    25,  1133,
    1075,    -1,    26,  1133,  1075,    -1,   148,  1133,  1075,    -1,
     149,  1133,  1075,    -1,    -1,   511,   513,    -1,   513,    -1,
     512,   513,    -1,   514,  1151,  1133,  1075,    -1,   275,    -1,
     273,    -1,    -1,    11,  1075,   516,  1133,   517,    -1,   251,
      -1,   376,    -1,   377,    -1,   121,    -1,   518,    -1,   519,
      -1,   518,   519,    -1,   522,    -1,   522,   395,   522,    -1,
      -1,   522,    17,   520,   521,    -1,   523,    -1,   521,    17,
     523,    -1,   232,    -1,   373,    -1,   442,    -1,   310,    -1,
     191,    -1,   239,    -1,   232,    -1,   373,    -1,   442,    -1,
     310,    -1,   191,    -1,   239,    -1,   387,  1126,   525,    -1,
     526,  1134,   527,    -1,  1075,    -1,   526,  1075,    -1,  1093,
      -1,   527,  1093,    -1,    57,  1075,  1133,   529,    -1,   530,
      -1,   529,   530,    -1,  1096,    -1,  1096,   395,  1096,    -1,
     233,  1075,  1133,  1072,    -1,    95,  1148,  1133,   232,    -1,
     105,  1133,    67,    -1,    97,  1133,  1072,    -1,    94,   379,
    1133,  1072,    -1,   347,  1133,  1072,    -1,   159,  1133,  1072,
      -1,    -1,   204,   351,   449,   541,   574,    -1,    -1,   166,
     449,   539,   542,    -1,    -1,   212,   449,   540,   575,    -1,
      -1,   166,   449,   542,    -1,    -1,   542,   543,    -1,    -1,
     354,  1110,  1075,   544,   545,   449,    -1,    -1,   545,   546,
      -1,   547,    -1,   551,    -1,   553,    -1,   558,    -1,   559,
      -1,   561,    -1,   565,    -1,   567,    -1,   568,    -1,   569,
      -1,   570,    -1,   571,    -1,   572,    -1,     1,    -1,    29,
    1156,   549,   548,   550,    -1,    29,  1156,   549,   114,    -1,
      29,  1156,   549,   300,    -1,    -1,   114,    -1,   300,    -1,
      -1,   164,    -1,   120,    -1,   232,    -1,   115,    -1,  1090,
      -1,     4,  1138,  1133,   552,    -1,   359,    -1,   120,    -1,
     311,    -1,    19,   314,  1135,  1133,  1072,  1106,    -1,    19,
     314,  1135,  1133,  1072,   557,   554,  1106,    -1,    -1,   555,
     556,    -1,   554,   556,    -1,  1072,    -1,    -1,   371,  1133,
      -1,   450,    -1,  1116,  1133,   436,    -1,   560,   379,  1133,
    1072,  1073,    -1,    -1,   400,    -1,   369,    -1,   236,  1138,
    1133,   562,    -1,   240,   563,    -1,    32,   563,    -1,   161,
      -1,    -1,   435,   236,   275,   564,    -1,   435,   236,   275,
     247,   564,    -1,   435,   342,    -1,   314,    -1,   316,    -1,
     281,  1133,   566,    -1,   566,    -1,   198,    -1,   314,  1123,
     359,    -1,   359,    -1,   321,    -1,   229,   359,    -1,   287,
    1125,  1133,  1074,    -1,   314,   110,  1133,   376,    -1,   314,
    1135,  1133,  1072,    -1,   314,  1135,  1133,  1072,   557,   554,
      -1,   321,  1135,  1133,  1072,    -1,   334,  1093,  1120,    -1,
     361,  1158,   573,    -1,     9,  1143,    -1,   256,  1143,    -1,
     313,   276,    -1,    -1,   212,   449,   575,    -1,    -1,   576,
     449,    -1,   577,    -1,   576,   577,    -1,   578,    -1,   580,
      -1,   584,    -1,   345,   579,  1120,  1130,  1063,    -1,    -1,
     314,    -1,   369,    -1,   370,    -1,   247,  1129,  1152,  1127,
     581,    -1,   582,    -1,   581,   582,    -1,  1064,   583,    -1,
      -1,   296,  1093,    -1,    22,    71,  1141,  1071,    -1,    -1,
      99,   117,   449,   586,   617,   666,   668,   670,   711,    -1,
      -1,    -1,   400,   351,   449,   587,   589,    -1,    -1,   592,
     588,   591,    -1,    -1,   589,   590,    -1,   592,   593,   619,
      -1,   593,   619,    -1,   591,   590,    -1,   165,    -1,   349,
      -1,    -1,  1064,   594,   595,   449,    -1,    -1,   595,   596,
      -1,  1133,   164,    -1,  1133,   184,    -1,   597,    -1,   599,
      -1,   603,    -1,   605,    -1,   607,    -1,   608,    -1,   614,
      -1,   615,    -1,   616,    -1,     1,    -1,    47,  1127,  1093,
     602,   598,    -1,    -1,   316,    -1,    56,    -1,   314,  1127,
    1093,  1126,    -1,   314,  1127,  1093,   398,  1093,  1126,    -1,
     314,  1133,   430,  1132,  1150,   601,   602,  1126,   600,    -1,
      -1,   111,  1141,  1072,    -1,    -1,  1131,  1093,    -1,    -1,
     398,  1093,    -1,   215,  1114,   604,    -1,   375,    -1,   274,
      -1,   429,   272,   436,  1133,   606,    -1,   429,   272,   167,
    1133,   606,    -1,   232,    -1,  1090,    -1,    99,  1114,  1071,
      -1,   227,  1133,  1074,  1137,   609,    -1,    -1,   609,   610,
      -1,   611,    -1,   612,    -1,   613,    -1,  1158,   171,  1122,
    1074,  1137,    -1,  1122,   404,  1074,  1137,    -1,  1122,    48,
    1074,    -1,   315,  1138,  1133,   436,    -1,    61,  1133,   436,
      -1,   327,  1133,   710,    -1,   329,  1119,   710,    -1,    -1,
      -1,   438,   351,   449,   618,   619,    -1,    -1,   620,    -1,
      -1,   621,   622,    -1,  1104,   623,    -1,   622,  1104,   623,
      -1,   622,   449,    -1,   633,    -1,    -1,   626,   629,   624,
     634,   628,    -1,    -1,   627,   629,   625,   659,    -1,   223,
      -1,   224,    -1,    -1,   232,    -1,    -1,   168,    -1,   436,
      -1,   436,    -1,    -1,  1133,   184,    -1,  1094,    -1,   221,
    1140,  1089,    -1,    50,  1140,  1089,    -1,   626,   630,    83,
     631,  1121,   632,    -1,    -1,   634,   635,    -1,   636,    -1,
     637,    -1,   639,    -1,   640,    -1,   641,    -1,   643,    -1,
     644,    -1,   653,    -1,   654,    -1,   656,    -1,   657,    -1,
     658,    -1,   664,    -1,   665,    -1,     1,    -1,   318,  1089,
      -1,  1133,   164,   638,    -1,    -1,    27,   232,    -1,  1133,
     184,    -1,   293,    -1,   642,    -1,   426,  1133,   642,    -1,
      37,    -1,    73,    -1,    75,    -1,    76,    -1,    77,    -1,
      78,    -1,    79,    -1,    80,    -1,   115,    -1,   197,    -1,
     286,    -1,   295,    -1,   308,    -1,   366,    -1,   364,    -1,
     365,    -1,   415,    -1,   413,    -1,   414,    -1,    39,   363,
      -1,    39,   412,    -1,    39,    -1,    42,   363,    -1,    42,
     412,    -1,    42,    -1,    41,   363,    -1,    41,   412,    -1,
      41,    -1,    40,   363,    -1,    40,   412,    -1,    40,    -1,
      38,   363,    -1,    38,   412,    -1,    38,    -1,   249,    -1,
    1149,   219,  1112,    -1,  1149,   405,  1112,    -1,   271,  1093,
     645,  1155,   646,   647,   650,    -1,    -1,   398,  1093,    -1,
      -1,   111,  1141,  1072,    -1,   648,    -1,    -1,   648,   649,
    1135,  1133,  1071,    -1,    28,    -1,   112,    -1,    -1,   198,
    1124,   651,    -1,   652,    -1,   651,   652,    -1,   436,    -1,
     213,  1146,    -1,   388,   655,    -1,    -1,   220,    -1,   341,
      -1,    43,  1157,   442,    -1,    34,    -1,   429,  1133,  1094,
      -1,    -1,   429,  1134,   661,   660,  1157,  1147,  1156,   663,
      -1,   662,    -1,   661,   662,    -1,  1094,    -1,  1094,   395,
    1094,    -1,    -1,   399,  1133,  1094,    -1,   325,  1090,    -1,
     325,  1090,   395,  1090,    -1,    21,   221,    -1,    -1,    -1,
     235,   351,   449,   667,   619,    -1,    -1,    -1,   231,   351,
     449,   669,   619,    -1,    -1,    -1,   327,   351,   449,   671,
     672,    -1,    -1,   673,    -1,   674,    -1,   673,   674,    -1,
     312,   710,   675,   449,   689,    -1,    -1,   675,   676,    -1,
    1133,   184,    -1,    60,  1133,  1085,    -1,   677,    -1,   681,
      -1,    87,   678,    -1,    88,   678,    -1,   679,   680,    -1,
      -1,   169,    -1,  1088,    -1,   680,  1088,    -1,   288,  1134,
     687,   682,   683,   684,   685,   686,    -1,    -1,   189,  1133,
    1093,    -1,    -1,   170,   113,  1133,  1093,    -1,    -1,   216,
      90,  1133,  1093,    -1,    -1,   217,  1133,  1093,    -1,    -1,
     171,  1133,  1093,    -1,  1093,    -1,  1093,   688,  1093,    66,
      -1,  1093,   688,    -1,   229,    -1,   230,    -1,    -1,   689,
     690,    -1,   626,   629,   691,   449,    -1,    -1,   691,   692,
      -1,   693,    -1,   695,    -1,   702,    -1,   640,    -1,   641,
      -1,   643,    -1,   653,    -1,   696,    -1,   656,    -1,   707,
      -1,   697,    -1,   658,    -1,   700,    -1,   708,    -1,   644,
      -1,   701,    -1,   408,  1133,   694,    -1,   331,    -1,   290,
      -1,    90,    -1,   113,    -1,    89,    -1,   289,    -1,   330,
      -1,   254,   188,  1133,  1093,    -1,    65,  1139,  1133,  1093,
      -1,    65,   266,    -1,    66,    -1,   698,    -1,   697,   698,
      -1,   385,  1140,   699,    -1,  1072,    -1,   298,   432,  1044,
      -1,   430,  1088,   176,  1079,    49,  1079,    -1,   703,   704,
      -1,   229,   706,  1134,    -1,   230,  1119,    -1,   705,    -1,
     704,   705,    -1,   294,  1093,    -1,  1093,    -1,   254,   288,
      -1,    -1,   265,    -1,   266,    -1,   371,  1133,  1088,  1111,
      -1,   188,   709,    -1,    -1,   199,    -1,   436,    -1,    -1,
      -1,    -1,   346,   351,   449,   712,   713,   714,    -1,    -1,
     715,    -1,   716,    -1,   715,   716,    -1,   633,    -1,    -1,
     626,   629,   717,   718,   449,    -1,    -1,   718,   719,    -1,
      44,    -1,    45,    -1,    36,    -1,    46,    -1,   155,   150,
      -1,   155,   152,    -1,   190,    -1,   238,    -1,   338,    -1,
     409,    -1,   285,    -1,    31,    -1,   352,    -1,   333,    -1,
     177,    -1,   309,    -1,   229,  1139,  1133,   720,  1087,    -1,
      65,  1139,  1133,   721,  1087,    -1,   173,  1133,  1087,    -1,
      33,  1133,  1087,    -1,   641,    -1,   656,    -1,   653,    -1,
     643,    -1,   658,    -1,   640,    -1,   722,    -1,   428,  1088,
      -1,   176,  1086,    -1,   398,  1088,    -1,    -1,   294,    -1,
     443,    -1,   243,    -1,   444,    -1,    -1,   294,    -1,   443,
      -1,   243,    -1,   444,    -1,   271,  1093,  1155,    -1,    -1,
      -1,    -1,   302,   117,   726,   734,   449,   724,   735,   725,
     737,    -1,    -1,    -1,   428,   727,   729,    -1,    -1,    54,
     728,   729,    -1,   730,    -1,   729,   730,    -1,   731,   732,
     733,   436,    -1,    -1,  1124,   320,    -1,  1124,   429,    -1,
      -1,   367,  1133,    31,    -1,   367,  1133,   107,    -1,   412,
     367,  1133,  1093,    -1,   367,  1133,  1093,    -1,    -1,   278,
      -1,    -1,   336,   436,    -1,    -1,    -1,   106,   449,   736,
     737,   123,   106,   449,    -1,    -1,   737,   738,    -1,   739,
      -1,   740,    -1,   741,    -1,   747,   449,    -1,     1,    -1,
     742,   351,   743,   449,    -1,   436,   449,    -1,   742,    -1,
     436,    -1,    -1,   232,    -1,    -1,    -1,   745,   746,   747,
      -1,    -1,   747,   748,    -1,   749,    -1,   759,    -1,   764,
      -1,   768,    -1,   771,    -1,   784,    -1,   787,    -1,   797,
      -1,   792,    -1,   798,    -1,   799,    -1,   802,    -1,   804,
      -1,   811,    -1,   815,    -1,   817,    -1,   832,    -1,   835,
      -1,   837,    -1,   839,    -1,   842,    -1,   844,    -1,   850,
      -1,   859,    -1,   861,    -1,   878,    -1,   880,    -1,   883,
      -1,   887,    -1,   893,    -1,   903,    -1,   910,    -1,   912,
      -1,   915,    -1,   919,    -1,   920,    -1,   931,    -1,   942,
      -1,   952,    -1,   958,    -1,   961,    -1,   967,    -1,   971,
      -1,   973,    -1,   975,    -1,   977,    -1,   980,    -1,   991,
      -1,  1004,    -1,   255,    -1,    -1,     3,   750,   751,   758,
      -1,  1088,   752,   755,  1011,    -1,  1088,   176,   157,   214,
      -1,  1088,   176,   230,    -1,  1088,   176,    66,    -1,  1088,
     176,   100,    -1,  1088,   176,   100,   441,    -1,  1088,   176,
     101,    -1,  1088,   176,   101,   440,    -1,  1088,   176,   102,
      -1,  1088,   176,   396,    -1,  1088,   176,    68,    -1,  1088,
     176,   149,  1011,    -1,  1088,   176,   147,  1083,  1011,    -1,
    1088,   176,    25,    -1,  1088,   176,    26,  1011,    -1,  1088,
     176,  1066,    -1,  1088,   176,   436,    -1,    -1,  1122,   753,
     754,    -1,  1122,   754,   753,    -1,  1122,   753,    -1,  1122,
     754,    -1,    30,  1083,    -1,   229,  1139,  1085,    -1,    65,
    1139,  1085,    -1,   296,  1139,  1085,    -1,    -1,   435,   756,
      -1,   757,    -1,   756,   757,    -1,    36,    -1,    46,    -1,
     190,    -1,   238,    -1,   338,    -1,   409,    -1,   285,    -1,
     173,  1133,  1087,    -1,    33,  1133,  1087,    -1,   348,   418,
    1043,    -1,   348,   118,  1043,    -1,    31,    -1,   177,    -1,
     333,    -1,   352,    -1,   419,    -1,   309,    -1,    -1,   124,
      -1,    -1,     5,   760,   761,   763,    -1,  1078,   398,  1059,
    1017,    -1,  1078,   762,   183,  1059,  1017,    -1,    92,  1088,
     398,  1088,  1111,  1017,    -1,    -1,   398,  1079,    -1,    -1,
     125,    -1,    -1,    10,   765,   766,    -1,   436,  1107,   767,
      -1,  1045,    56,  1107,   336,  1077,    -1,    -1,   336,  1077,
      -1,    18,   769,    -1,    -1,   769,  1068,   398,   770,  1068,
      -1,    -1,   304,   398,    -1,    -1,    51,   772,  1086,   773,
     778,   779,   781,   783,    -1,    -1,    -1,   428,   774,   775,
      -1,   776,    -1,   775,   776,    -1,   777,   274,    -1,   777,
     732,  1079,    -1,    -1,  1124,   320,    -1,  1124,    85,    -1,
    1124,   429,    -1,    -1,   336,  1088,    -1,   183,  1088,    -1,
      -1,    -1,   998,   780,   744,    -1,    -1,    -1,   999,   782,
     744,    -1,    -1,   126,    -1,    -1,    52,   785,   786,    -1,
      -1,   786,  1085,    -1,    -1,    59,   788,   789,    -1,    -1,
     789,  1064,   790,    -1,    -1,   791,    -1,   791,  1130,   324,
      -1,  1158,   256,   339,    -1,  1158,   236,    -1,   319,    -1,
     410,    -1,    -1,    74,   793,   794,   795,    -1,  1059,   796,
    1045,  1017,    -1,    -1,   127,    -1,   450,    -1,   153,    -1,
      70,    -1,    86,    -1,    -1,   108,   800,  1064,  1145,  1037,
     801,    -1,    -1,   128,    -1,    -1,   108,   803,   400,  1063,
      -1,    -1,   115,   805,   806,   810,    -1,  1085,   423,  1012,
      -1,  1085,   424,  1012,    -1,  1085,   421,  1012,    -1,  1085,
     422,  1012,    -1,  1078,   752,   807,  1012,    -1,  1078,   752,
     420,  1066,   807,  1012,    -1,  1078,   752,   420,   436,   807,
    1012,    -1,  1078,   752,   420,   300,   807,  1012,    -1,  1078,
     752,   420,    94,   807,  1012,    -1,    -1,  1158,   264,    -1,
     435,   808,    -1,   809,    -1,   808,   809,    -1,    36,    -1,
      46,    -1,   155,   150,    -1,   155,   152,    -1,   190,    -1,
     238,    -1,   338,    -1,   409,    -1,   285,    -1,   173,  1133,
    1087,    -1,    33,  1133,  1087,    -1,   348,   418,  1043,    -1,
     348,   118,  1043,    -1,    44,    -1,    45,    -1,    -1,   129,
      -1,    -1,   116,   812,   813,   814,    -1,  1079,   206,  1059,
    1017,    -1,  1079,   206,  1079,   183,  1059,  1017,    -1,  1079,
      49,  1079,   183,  1059,  1017,    -1,  1079,   206,  1079,   183,
    1060,   323,  1060,  1017,    -1,  1079,    49,  1079,   183,  1060,
     323,  1060,  1017,    -1,    -1,   130,    -1,    -1,   146,   816,
     232,   773,    -1,    -1,   158,   818,   819,   821,   831,    -1,
     820,    -1,   819,  1118,   820,    -1,  1045,    -1,   403,    -1,
     399,    -1,   822,   825,    -1,   823,    -1,   822,   823,    -1,
      -1,   827,   824,   744,    -1,    -1,    -1,   434,   826,   744,
      -1,   432,   828,    -1,   827,   432,   828,    -1,   829,    -1,
     828,  1118,   829,    -1,  1046,   830,    -1,    21,    -1,   403,
      -1,   399,    -1,    -1,   395,  1045,    -1,    -1,   131,    -1,
      -1,   162,   833,   834,    -1,    -1,   305,    -1,   292,    -1,
     292,    98,    -1,   351,    -1,   291,    -1,    -1,   175,   836,
    1076,    -1,    -1,   182,   838,  1088,    -1,    -1,   185,  1156,
     840,  1067,   841,    -1,    -1,   111,  1141,  1088,    -1,    -1,
     186,   843,    -1,    -1,    -1,   193,   845,  1044,  1154,   846,
     744,   847,   849,    -1,   193,     1,   133,    -1,    -1,    -1,
     122,   848,   744,    -1,    -1,   133,    -1,    -1,   200,   851,
    1076,   852,   853,   854,   858,    -1,    -1,  1158,   168,    -1,
      -1,     9,  1156,   429,    -1,   857,  1156,   429,    -1,    -1,
     326,   855,    -1,   856,    -1,   855,   856,    -1,   857,  1128,
      49,  1079,    -1,    12,    -1,    15,    -1,   267,    -1,    16,
      -1,   268,    -1,   249,    -1,   250,    -1,    -1,   107,    -1,
      -1,   202,   860,   680,    -1,    -1,   205,   862,   863,   864,
      -1,  1088,    -1,  1094,    -1,  1097,    -1,   865,    -1,   864,
     865,    -1,   866,    -1,   870,    -1,   875,    -1,    -1,   389,
     867,   868,    -1,   869,    -1,   868,   869,    -1,  1083,   172,
      -1,    56,   876,    -1,     9,    -1,   219,    -1,   405,    -1,
    1083,   876,    -1,   326,   871,    -1,   872,    -1,   871,   872,
      -1,    56,    49,  1083,   876,    -1,   873,   874,    -1,    -1,
       9,    -1,   219,    -1,   170,    -1,   405,    -1,  1083,    49,
    1084,   876,    -1,    91,  1083,   398,  1084,   876,    -1,    -1,
     876,  1008,   877,  1079,    -1,    -1,   401,    -1,    -1,   242,
     879,   944,    -1,    -1,   246,   881,   882,    -1,  1079,   398,
    1076,    -1,    92,  1079,   398,  1076,    -1,    -1,   248,   884,
     885,   886,    -1,  1079,    49,  1059,  1017,    -1,  1079,    49,
    1079,   183,  1059,  1017,    -1,    -1,   134,    -1,    -1,   277,
     888,   889,    -1,    -1,   889,   890,   891,  1063,   892,    -1,
     203,    -1,   283,    -1,   211,    -1,   163,    -1,    -1,   361,
    1158,   573,    -1,    -1,  1158,   256,   339,    -1,  1158,   236,
      -1,    -1,   292,   894,   895,    -1,   898,   899,    -1,    -1,
     899,   896,   744,   897,    -1,   899,   135,    -1,    -1,   135,
      -1,  1068,    -1,  1068,   395,  1068,    -1,    -1,   174,    -1,
    1086,   397,    -1,   900,   417,  1044,    -1,   900,   430,   901,
      -1,    -1,  1158,   392,  1008,    -1,   902,    -1,   901,     8,
     902,    -1,  1088,   176,  1079,    49,  1079,   417,  1044,    -1,
      -1,   313,   904,  1064,  1108,  1145,   905,   906,   907,   908,
     909,    -1,    -1,   206,  1088,    -1,    -1,   195,   236,    -1,
    1158,   236,    -1,  1158,   256,   236,    -1,  1158,   194,   236,
      -1,  1158,   431,    -1,    -1,   214,  1133,   680,    -1,    -1,
    1027,    -1,  1038,    -1,    -1,   137,    -1,    -1,   322,   911,
    1061,  1006,    -1,    -1,   335,   913,  1064,  1145,   905,  1027,
     914,    -1,    -1,   138,    -1,    -1,   340,   916,  1061,  1006,
     917,  1037,   918,    -1,    -1,  1158,   236,    -1,  1158,   256,
     236,    -1,    -1,   139,    -1,   342,    -1,    -1,   350,   921,
     922,   930,    -1,  1062,   924,   925,   927,    -1,    -1,     9,
    1062,   925,   432,  1045,   923,   744,    -1,    -1,   430,  1088,
      -1,    -1,    -1,  1122,   123,   926,   744,    -1,   928,    -1,
     928,   927,    -1,    -1,   432,  1044,   929,   744,    -1,    -1,
     140,    -1,    -1,   360,   932,   933,    -1,   934,    -1,   935,
      -1,   936,    -1,   938,    -1,   940,    -1,   147,  1083,   398,
    1083,    -1,  1076,   398,   146,  1082,    -1,  1076,   398,  1079,
      -1,  1076,   937,    49,  1079,    -1,   418,    -1,   118,    -1,
     939,    -1,   938,   939,    -1,  1065,   398,   514,    -1,   941,
      -1,   940,   941,    -1,  1076,   398,   403,    -1,  1076,   398,
     399,    -1,    -1,   369,   943,   944,    -1,    -1,  1090,   946,
     948,   949,   945,   950,   951,    -1,    -1,   946,  1141,   649,
    1135,   947,    -1,    -1,   947,  1090,    -1,    -1,  1115,  1142,
      -1,    -1,  1116,  1133,  1072,    -1,    -1,   428,  1063,    -1,
     203,   302,  1133,   898,    -1,    -1,   183,  1063,    -1,   283,
     302,  1133,   898,    -1,    -1,    -1,   378,   953,  1064,   954,
     955,  1037,   957,    -1,    -1,   214,  1133,   956,   680,    -1,
    1109,  1050,    -1,  1109,  1051,    -1,  1109,  1052,    -1,  1109,
    1053,    -1,  1109,  1054,    -1,    -1,   141,    -1,    -1,   380,
     344,   959,   960,    -1,   380,   232,    -1,    -1,   336,  1079,
      -1,   183,  1079,    -1,    -1,   381,   962,   963,   206,  1088,
     965,  1022,   966,    -1,   964,    -1,   963,   964,    -1,  1079,
      -1,   109,  1124,   367,    -1,   109,  1124,  1079,    -1,    -1,
    1158,   295,  1088,    -1,    -1,   142,    -1,    -1,   384,   968,
     969,   970,    -1,  1078,   176,  1059,  1017,    -1,  1078,   176,
    1079,   183,  1059,  1017,    -1,    92,  1088,   176,  1088,  1111,
    1017,    -1,    -1,   143,    -1,   386,   972,    -1,    -1,   301,
      -1,    -1,   391,   974,   680,    -1,    -1,   406,   976,  1088,
     176,  1083,   398,  1084,    -1,    -1,   411,   978,  1064,   979,
      -1,    -1,   314,    -1,   316,    -1,    -1,   416,   981,  1088,
     982,   985,   965,   989,  1022,   990,    -1,    -1,   109,  1124,
     983,    -1,   984,    -1,   983,   279,   984,    -1,  1105,  1083,
      -1,   206,   986,    -1,   985,   986,    -1,  1088,   987,   988,
      -1,    -1,   110,  1132,  1088,    -1,    -1,    93,  1132,  1088,
      -1,    -1,   389,  1132,  1088,    -1,    -1,   144,    -1,   992,
      -1,  1001,    -1,  1003,    -1,   427,   993,   995,   996,   997,
    1000,  1141,   994,    -1,    -1,   184,    -1,  1063,    -1,   203,
      -1,   283,    -1,   211,    -1,   163,    -1,    -1,     8,    -1,
      -1,   375,    -1,   160,    -1,   156,    -1,   160,    -1,   284,
      -1,   260,    -1,   262,    -1,    -1,   302,    -1,   427,  1130,
     104,  1141,  1002,    -1,  1068,    -1,     9,   303,    -1,   427,
     993,    35,   328,  1088,    -1,    -1,   439,  1005,  1061,  1006,
     917,  1007,  1009,  1010,    -1,    -1,   176,  1085,    -1,    -1,
    1008,  1117,  1087,  1136,    -1,  1008,  1117,  1066,    -1,  1008,
    1117,   288,    -1,    35,    -1,     8,    -1,    -1,  1032,    -1,
    1038,    -1,    -1,   145,    -1,  1013,  1015,    -1,  1013,  1015,
      -1,    -1,    -1,   160,  1014,   744,    -1,    -1,    -1,   260,
    1016,   744,    -1,  1018,  1020,    -1,    -1,    -1,   368,  1019,
     744,    -1,    -1,    -1,   263,  1021,   744,    -1,  1023,  1025,
      -1,    -1,    -1,   284,  1024,   744,    -1,    -1,    -1,   262,
    1026,   744,    -1,  1028,    -1,  1030,    -1,  1028,  1030,    -1,
      -1,   123,  1029,   744,    -1,    -1,   258,  1031,   744,    -1,
    1033,    -1,  1035,    -1,  1033,  1035,    -1,    -1,   151,  1034,
     744,    -1,    -1,   259,  1036,   744,    -1,    -1,  1038,    -1,
    1039,    -1,  1041,    -1,  1039,  1041,    -1,    -1,   209,  1040,
     744,    -1,    -1,   261,  1042,   744,    -1,    -1,  1124,  1087,
    1136,    -1,  1045,    -1,  1046,    -1,    -1,  1047,  1048,    -1,
    1048,   210,    -1,  1049,  1079,    -1,  1048,   451,    -1,  1048,
     274,    -1,  1048,   267,    -1,  1048,    12,    -1,  1048,    13,
      -1,  1048,    14,    -1,  1048,    58,    -1,  1048,   297,    -1,
    1048,   253,    -1,  1048,   442,    -1,  1048,   257,    -1,    -1,
    1049,   210,    -1,  1049,   452,    -1,  1049,   443,    -1,  1049,
     444,    -1,  1049,   448,    -1,  1049,   257,    -1,  1048,   443,
      -1,  1048,   444,    -1,  1048,   445,    -1,  1048,   446,    -1,
    1048,   448,    -1,  1048,  1050,    -1,  1048,  1051,    -1,  1048,
    1052,    -1,  1048,  1053,    -1,  1048,  1054,    -1,  1048,   252,
      -1,  1049,  1050,    -1,  1049,  1051,    -1,  1049,  1052,    -1,
    1049,  1053,    -1,  1049,  1054,    -1,  1049,   252,    -1,  1048,
      20,    -1,  1048,   279,    -1,   450,    -1,   153,  1156,    -1,
     154,    -1,   453,    -1,   187,  1153,    -1,   454,    -1,   222,
    1153,    -1,   181,    -1,   187,  1153,   279,   153,  1156,    -1,
     187,  1153,   153,  1156,    -1,   218,    -1,   222,  1153,   279,
     153,  1156,    -1,   222,  1153,   153,  1156,    -1,  1057,    -1,
    1055,  1056,  1057,    -1,    -1,    69,    -1,   355,    -1,  1080,
      -1,  1057,   443,  1057,    -1,  1057,   444,  1057,    -1,  1057,
     445,  1057,    -1,  1057,   446,  1057,    -1,   443,  1057,    -1,
     444,  1057,    -1,  1057,   448,  1057,    -1,   452,  1057,   451,
      -1,   228,    -1,   228,  1113,   436,    -1,  1060,    -1,  1059,
    1060,    -1,  1079,  1111,    -1,  1090,    -1,  1090,    -1,  1064,
      -1,  1063,  1064,    -1,   436,    -1,  1066,    -1,  1065,  1066,
      -1,   244,    -1,    -1,  1067,  1068,    -1,  1069,    -1,  1090,
      -1,  1070,    -1,  1070,  1113,  1070,    -1,   232,    -1,  1072,
      -1,  1071,  1072,    -1,  1090,    -1,    -1,  1072,    -1,  1072,
      -1,   232,    -1,   436,    -1,  1077,    -1,  1076,  1077,    -1,
    1088,    -1,     6,  1140,  1089,    -1,  1079,    -1,  1078,  1079,
      -1,  1088,    -1,   221,  1140,  1089,    -1,   221,  1140,  1095,
      -1,   221,  1140,  1097,    -1,     6,  1140,  1081,  1082,    -1,
       6,  1140,  1089,    -1,  1094,    -1,  1097,    -1,  1058,    -1,
    1088,    -1,   221,  1140,  1089,    -1,   221,  1140,  1095,    -1,
     221,  1140,  1097,    -1,  1095,    -1,  1097,    -1,  1058,    -1,
     305,    -1,   146,    -1,  1089,    -1,   232,    -1,  1088,    -1,
    1095,    -1,  1088,    -1,  1094,    -1,  1088,    -1,   232,    -1,
    1088,    -1,   232,    -1,  1097,    -1,  1088,    -1,  1093,    -1,
     442,    -1,  1089,    -1,  1090,    -1,  1090,  1091,    -1,  1090,
    1092,    -1,  1090,  1091,  1092,    -1,   436,    -1,   436,  1113,
    1090,    -1,   452,  1055,   451,    -1,   452,  1057,   455,   451,
      -1,   452,  1057,   455,  1057,   451,    -1,   232,    -1,  1095,
      -1,     9,  1096,    -1,  1096,    -1,  1095,   456,  1096,    -1,
     232,    -1,   373,    -1,   442,    -1,   310,    -1,   191,    -1,
     239,    -1,   402,    -1,    96,  1098,    -1,   433,  1098,    -1,
     425,   452,  1057,   451,  1098,    -1,   237,   452,  1057,   451,
    1098,    -1,   337,   452,  1057,   451,  1098,    -1,    81,   452,
    1055,   451,  1098,    -1,   382,   452,  1055,   451,  1098,    -1,
     383,   452,  1055,   451,  1098,    -1,   407,   452,  1101,   451,
    1098,    -1,   269,   452,  1102,   451,    -1,   234,   452,  1103,
     451,  1098,    -1,   180,  1099,    -1,    -1,   452,  1057,   455,
     451,    -1,   452,  1057,   455,  1057,   451,    -1,    -1,   452,
    1100,   451,    -1,    -1,  1055,    -1,  1057,    -1,  1057,  1056,
     219,    -1,  1057,  1056,   405,    -1,  1057,    -1,  1057,  1056,
    1057,    -1,  1057,    -1,  1057,  1056,  1072,    -1,    -1,    -1,
       9,    -1,    -1,  1115,    -1,    -1,   201,    -1,    -1,   254,
      -1,   299,    -1,    -1,   257,    -1,    -1,   278,    -1,    -1,
     343,    -1,    -1,   357,  1125,    -1,   196,    -1,   272,    -1,
     314,  1133,    -1,   316,  1119,    -1,   435,   119,    -1,   119,
      -1,    62,   358,    -1,   358,    -1,    -1,     7,    -1,    -1,
      17,    -1,    -1,    23,    -1,    -1,    24,    -1,    -1,    27,
      -1,    -1,    30,    -1,    -1,    37,    -1,    -1,    49,    -1,
      -1,    55,    -1,    -1,    56,    -1,    -1,    84,    -1,    -1,
      99,    -1,    -1,   400,    -1,    -1,   172,    -1,    -1,   176,
      -1,    -1,   196,    -1,    -1,   210,    -1,    -1,   210,    -1,
      23,    -1,    -1,   214,    -1,    -1,   229,    -1,   230,    -1,
      -1,   230,    -1,    -1,   245,    -1,    -1,   265,    -1,    -1,
     272,    -1,    -1,   275,    -1,    -1,   280,    -1,   196,   280,
      -1,    -1,   282,    -1,    -1,   305,    -1,    -1,   314,    -1,
      -1,   341,    -1,    -1,   360,    -1,    -1,   362,    -1,    -1,
     362,    -1,   362,   210,    -1,    -1,   367,    -1,    -1,   379,
      -1,    -1,   390,    -1,    -1,   393,    -1,    -1,   394,    -1,
      -1,   397,    -1,    -1,   398,    -1,    -1,   432,    -1,    -1,
     435,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   765,   765,   765,   807,   808,   812,   813,   818,   819,
     817,   827,   828,   826,   836,   837,   835,   842,   843,   844,
     847,   848,   874,   898,   928,   927,   968,  1012,  1013,  1017,
    1018,  1021,  1022,  1026,  1033,  1040,  1044,  1048,  1060,  1061,
    1071,  1072,  1081,  1082,  1086,  1087,  1088,  1089,  1098,  1101,
    1102,  1103,  1104,  1108,  1115,  1124,  1127,  1128,  1129,  1130,
    1134,  1135,  1139,  1140,  1141,  1145,  1152,  1153,  1157,  1164,
    1176,  1179,  1180,  1184,  1185,  1189,  1193,  1200,  1201,  1211,
    1214,  1215,  1216,  1220,  1221,  1225,  1226,  1227,  1228,  1229,
    1230,  1231,  1232,  1233,  1234,  1235,  1242,  1253,  1252,  1264,
    1263,  1272,  1286,  1300,  1314,  1330,  1331,  1335,  1336,  1340,
    1351,  1352,  1360,  1359,  1371,  1372,  1373,  1374,  1375,  1383,
    1384,  1389,  1390,  1392,  1391,  1403,  1404,  1408,  1409,  1410,
    1411,  1412,  1413,  1417,  1418,  1419,  1420,  1421,  1422,  1429,
    1440,  1452,  1453,  1457,  1458,  1465,  1474,  1475,  1479,  1480,
    1494,  1509,  1576,  1587,  1594,  1601,  1607,  1614,  1615,  1619,
    1618,  1628,  1627,  1643,  1644,  1647,  1648,  1653,  1652,  1673,
    1674,  1678,  1679,  1680,  1681,  1682,  1683,  1684,  1685,  1686,
    1687,  1688,  1689,  1690,  1691,  1698,  1702,  1707,  1714,  1715,
    1716,  1719,  1720,  1724,  1731,  1732,  1739,  1746,  1750,  1751,
    1752,  1759,  1779,  1826,  1826,  1830,  1834,  1850,  1851,  1852,
    1858,  1868,  1877,  1879,  1880,  1886,  1890,  1891,  1892,  1895,
    1896,  1897,  1901,  1905,  1906,  1912,  1913,  1917,  1926,  1935,
    1944,  1953,  1968,  1978,  1985,  1989,  2027,  2034,  2041,  2045,
    2046,  2047,  2055,  2056,  2059,  2060,  2064,  2065,  2069,  2070,
    2071,  2077,  2102,  2103,  2104,  2105,  2111,  2118,  2119,  2123,
    2126,  2127,  2133,  2143,  2144,  2158,  2159,  2159,  2162,  2161,
    2174,  2175,  2179,  2191,  2200,  2204,  2205,  2215,  2214,  2232,
    2233,  2237,  2244,  2251,  2252,  2253,  2254,  2255,  2256,  2257,
    2258,  2259,  2260,  2267,  2271,  2271,  2271,  2277,  2289,  2314,
    2338,  2339,  2346,  2347,  2351,  2352,  2359,  2366,  2367,  2374,
    2378,  2387,  2388,  2394,  2404,  2422,  2423,  2427,  2428,  2429,
    2433,  2440,  2447,  2457,  2464,  2482,  2486,  2497,  2498,  2498,
    2509,  2510,  2514,  2514,  2531,  2532,  2534,  2538,  2540,  2539,
    2564,  2563,  2588,  2592,  2599,  2601,  2623,  2628,  2634,  2643,
    2651,  2652,  2660,  2661,  2662,  2666,  2686,  2690,  2699,  2700,
    2701,  2702,  2703,  2704,  2705,  2706,  2707,  2708,  2709,  2710,
    2711,  2712,  2713,  2720,  2742,  2764,  2765,  2777,  2797,  2804,
    2805,  2809,  2810,  2811,  2812,  2813,  2814,  2815,  2816,  2817,
    2818,  2819,  2820,  2825,  2830,  2831,  2832,  2833,  2834,  2835,
    2836,  2837,  2838,  2839,  2840,  2841,  2842,  2843,  2844,  2845,
    2846,  2847,  2848,  2856,  2864,  2872,  2879,  2884,  2895,  2912,
    2913,  2916,  2917,  2924,  2948,  2949,  2966,  2967,  2970,  2971,
    2978,  2979,  2984,  2994,  3001,  3004,  3005,  3006,  3013,  3020,
    3045,  3049,  3049,  3054,  3055,  3059,  3060,  3063,  3064,  3077,
    3089,  3109,  3123,  3125,  3124,  3144,  3145,  3145,  3158,  3160,
    3159,  3171,  3172,  3176,  3177,  3186,  3193,  3196,  3200,  3204,
    3205,  3206,  3213,  3214,  3218,  3221,  3221,  3224,  3225,  3231,
    3236,  3237,  3240,  3241,  3244,  3245,  3248,  3249,  3252,  3253,
    3257,  3258,  3259,  3263,  3264,  3267,  3268,  3272,  3276,  3277,
    3281,  3282,  3283,  3284,  3285,  3286,  3287,  3288,  3289,  3290,
    3291,  3292,  3293,  3294,  3295,  3296,  3300,  3304,  3305,  3306,
    3307,  3308,  3309,  3310,  3314,  3318,  3319,  3320,  3324,  3325,
    3329,  3333,  3338,  3342,  3346,  3350,  3351,  3355,  3356,  3360,
    3361,  3362,  3365,  3365,  3365,  3368,  3372,  3375,  3375,  3378,
    3385,  3386,  3387,  3386,  3404,  3405,  3409,  3410,  3415,  3417,
    3416,  3452,  3453,  3457,  3458,  3459,  3460,  3461,  3462,  3463,
    3464,  3465,  3466,  3467,  3468,  3469,  3470,  3471,  3472,  3473,
    3477,  3481,  3485,  3489,  3490,  3491,  3492,  3493,  3494,  3495,
    3496,  3503,  3507,  3517,  3520,  3524,  3528,  3532,  3540,  3543,
    3547,  3551,  3555,  3563,  3576,  3578,  3588,  3577,  3615,  3617,
    3616,  3623,  3622,  3631,  3632,  3637,  3644,  3646,  3650,  3660,
    3662,  3670,  3678,  3707,  3738,  3740,  3750,  3755,  3766,  3767,
    3767,  3794,  3795,  3799,  3800,  3801,  3802,  3818,  3830,  3861,
    3898,  3910,  3913,  3914,  3923,  3927,  3923,  3940,  3958,  3962,
    3963,  3964,  3965,  3966,  3967,  3968,  3969,  3970,  3971,  3972,
    3973,  3974,  3975,  3976,  3977,  3978,  3979,  3980,  3981,  3982,
    3983,  3984,  3985,  3986,  3987,  3988,  3989,  3990,  3991,  3992,
    3993,  3994,  3995,  3996,  3997,  3998,  3999,  4000,  4001,  4002,
    4003,  4004,  4005,  4006,  4007,  4008,  4009,  4010,  4011,  4034,
    4033,  4046,  4050,  4054,  4058,  4062,  4066,  4070,  4074,  4078,
    4082,  4086,  4090,  4094,  4098,  4102,  4106,  4110,  4117,  4118,
    4119,  4120,  4121,  4122,  4126,  4130,  4131,  4134,  4135,  4139,
    4140,  4144,  4145,  4146,  4147,  4148,  4149,  4150,  4151,  4155,
    4159,  4163,  4168,  4169,  4170,  4171,  4172,  4173,  4177,  4178,
    4187,  4187,  4193,  4197,  4201,  4207,  4208,  4212,  4213,  4222,
    4222,  4227,  4231,  4238,  4239,  4248,  4254,  4255,  4259,  4259,
    4267,  4267,  4277,  4279,  4278,  4287,  4288,  4293,  4300,  4307,
    4309,  4313,  4321,  4332,  4333,  4334,  4339,  4343,  4342,  4354,
    4358,  4357,  4368,  4369,  4378,  4378,  4382,  4383,  4395,  4395,
    4399,  4400,  4411,  4412,  4413,  4414,  4415,  4418,  4418,  4426,
    4426,  4432,  4439,  4440,  4443,  4443,  4450,  4463,  4476,  4476,
    4487,  4488,  4497,  4497,  4517,  4516,  4529,  4533,  4537,  4541,
    4545,  4549,  4553,  4558,  4562,  4569,  4570,  4571,  4575,  4576,
    4581,  4582,  4583,  4584,  4585,  4586,  4587,  4588,  4589,  4590,
    4594,  4598,  4602,  4607,  4608,  4612,  4613,  4622,  4622,  4628,
    4632,  4636,  4640,  4644,  4651,  4652,  4661,  4661,  4683,  4682,
    4701,  4702,  4713,  4722,  4727,  4735,  4764,  4765,  4771,  4770,
    4786,  4790,  4789,  4804,  4805,  4810,  4811,  4822,  4851,  4852,
    4853,  4856,  4857,  4861,  4862,  4871,  4871,  4876,  4877,  4885,
    4902,  4919,  4937,  4962,  4962,  4975,  4975,  4988,  4988,  4997,
    5001,  5014,  5014,  5027,  5029,  5027,  5040,  5045,  5049,  5048,
    5062,  5063,  5072,  5072,  5080,  5081,  5085,  5086,  5087,  5091,
    5092,  5097,  5098,  5103,  5107,  5108,  5109,  5110,  5111,  5112,
    5113,  5117,  5118,  5127,  5127,  5140,  5139,  5149,  5150,  5151,
    5155,  5156,  5160,  5161,  5162,  5168,  5168,  5173,  5174,  5178,
    5179,  5180,  5181,  5182,  5183,  5189,  5193,  5194,  5198,  5203,
    5207,  5208,  5209,  5210,  5211,  5215,  5241,  5254,  5255,  5259,
    5259,  5267,  5267,  5277,  5277,  5282,  5286,  5298,  5298,  5304,
    5308,  5315,  5316,  5325,  5325,  5329,  5330,  5344,  5345,  5346,
    5347,  5351,  5352,  5356,  5357,  5358,  5370,  5370,  5375,  5380,
    5379,  5389,  5396,  5397,  5401,  5406,  5415,  5418,  5422,  5427,
    5434,  5441,  5442,  5446,  5447,  5452,  5464,  5464,  5493,  5494,
    5498,  5499,  5503,  5507,  5511,  5515,  5522,  5523,  5537,  5538,
    5539,  5543,  5544,  5553,  5553,  5568,  5568,  5579,  5580,  5589,
    5589,  5606,  5607,  5611,  5618,  5619,  5628,  5641,  5641,  5647,
    5652,  5651,  5662,  5663,  5667,  5669,  5668,  5679,  5680,  5685,
    5684,  5695,  5696,  5705,  5705,  5710,  5711,  5712,  5713,  5714,
    5720,  5729,  5733,  5742,  5749,  5750,  5756,  5757,  5761,  5770,
    5771,  5775,  5779,  5791,  5791,  5797,  5796,  5813,  5816,  5832,
    5833,  5836,  5837,  5841,  5842,  5847,  5852,  5860,  5872,  5877,
    5885,  5901,  5902,  5901,  5922,  5923,  5939,  5940,  5941,  5942,
    5943,  5947,  5948,  5957,  5957,  5962,  5969,  5970,  5971,  5980,
    5980,  5989,  5990,  5994,  5995,  5996,  6000,  6001,  6005,  6006,
    6015,  6015,  6021,  6025,  6029,  6036,  6037,  6046,  6053,  6054,
    6062,  6062,  6075,  6075,  6091,  6091,  6100,  6102,  6103,  6112,
    6112,  6122,  6123,  6128,  6129,  6134,  6141,  6142,  6147,  6154,
    6155,  6159,  6160,  6164,  6165,  6169,  6170,  6179,  6180,  6181,
    6185,  6209,  6212,  6220,  6230,  6235,  6240,  6245,  6252,  6253,
    6256,  6257,  6261,  6261,  6265,  6265,  6269,  6269,  6272,  6273,
    6277,  6284,  6285,  6289,  6301,  6301,  6318,  6319,  6324,  6327,
    6331,  6335,  6342,  6343,  6346,  6347,  6348,  6352,  6353,  6366,
    6374,  6381,  6383,  6382,  6392,  6394,  6393,  6408,  6412,  6414,
    6413,  6424,  6426,  6425,  6442,  6448,  6450,  6449,  6459,  6461,
    6460,  6476,  6481,  6486,  6496,  6495,  6507,  6506,  6522,  6527,
    6532,  6542,  6541,  6553,  6552,  6567,  6568,  6572,  6577,  6582,
    6592,  6591,  6603,  6602,  6619,  6622,  6634,  6641,  6648,  6648,
    6658,  6659,  6660,  6662,  6663,  6664,  6665,  6666,  6667,  6669,
    6670,  6671,  6673,  6676,  6678,  6679,  6681,  6682,  6683,  6685,
    6687,  6688,  6689,  6690,  6691,  6693,  6694,  6695,  6696,  6697,
    6698,  6700,  6701,  6702,  6703,  6704,  6705,  6707,  6708,  6711,
    6711,  6711,  6712,  6712,  6713,  6713,  6714,  6714,  6714,  6715,
    6715,  6715,  6720,  6721,  6724,  6725,  6726,  6730,  6731,  6732,
    6733,  6734,  6735,  6736,  6737,  6738,  6749,  6761,  6776,  6777,
    6782,  6788,  6810,  6830,  6834,  6850,  6864,  6865,  6870,  6876,
    6877,  6882,  6891,  6892,  6893,  6897,  6908,  6909,  6913,  6921,
    6922,  6926,  6927,  6933,  6953,  6954,  6958,  6959,  6963,  6964,
    6968,  6969,  6970,  6971,  6972,  6973,  6974,  6975,  6976,  6980,
    6981,  6982,  6983,  6984,  6985,  6986,  6990,  6991,  6995,  6996,
    7000,  7001,  7005,  7006,  7017,  7018,  7022,  7023,  7024,  7028,
    7029,  7030,  7038,  7042,  7043,  7044,  7045,  7049,  7050,  7054,
    7064,  7082,  7109,  7121,  7122,  7132,  7133,  7137,  7138,  7139,
    7140,  7141,  7142,  7143,  7151,  7155,  7159,  7163,  7167,  7171,
    7175,  7179,  7183,  7187,  7191,  7195,  7202,  7203,  7204,  7208,
    7209,  7213,  7214,  7219,  7226,  7233,  7243,  7250,  7260,  7267,
    7281,  7291,  7292,  7296,  7297,  7301,  7302,  7306,  7307,  7308,
    7312,  7313,  7317,  7318,  7322,  7323,  7327,  7328,  7335,  7335,
    7336,  7336,  7337,  7337,  7338,  7338,  7340,  7340,  7341,  7341,
    7342,  7342,  7343,  7343,  7344,  7344,  7345,  7345,  7346,  7346,
    7347,  7347,  7348,  7348,  7349,  7349,  7350,  7350,  7351,  7351,
    7352,  7352,  7353,  7353,  7354,  7354,  7355,  7355,  7356,  7356,
    7357,  7357,  7357,  7358,  7358,  7359,  7359,  7359,  7360,  7360,
    7361,  7361,  7362,  7362,  7363,  7363,  7364,  7364,  7365,  7365,
    7365,  7366,  7366,  7367,  7367,  7368,  7368,  7369,  7369,  7370,
    7370,  7371,  7371,  7372,  7372,  7372,  7373,  7373,  7374,  7374,
    7375,  7375,  7376,  7376,  7377,  7377,  7378,  7378,  7379,  7379,
    7381,  7381,  7382,  7382
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
  "\"LAST DETAIL\"", "LE", "LEADING", "LEFT", "LENGTH", "LESS",
  "LEVEL_NUMBER_WORD", "LEVEL88_NUMBER_WORD", "LIMIT", "LIMITS", "LINAGE",
  "\"LINAGE-COUNTER\"", "LINE", "LINES", "LINKAGE", "\"Literal\"",
  "LOCALE", "\"FUNCTION LOCALE\"", "\"LOCAL-STORAGE\"", "LOCK",
  "\"FUNCTION LOWER-CASE\"", "LOWLIGHT", "\"LOW-VALUE\"", "MANUAL",
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
  "_ext_clause", "assignment_name", "access_mode_clause", "access_mode",
  "alternative_record_key_clause", "split_key_list", "$@16", "split_key",
  "key_is_eq", "collating_sequence_clause", "file_status_clause",
  "file_or_sort", "lock_mode_clause", "lock_mode", "lock_with",
  "lock_records", "organization_clause", "organization",
  "padding_character_clause", "record_delimiter_clause",
  "record_key_clause", "relative_key_clause", "reserve_clause",
  "sharing_clause", "sharing_option", "i_o_control_paragraph",
  "opt_i_o_control", "i_o_control_list", "i_o_control_clause",
  "same_clause", "same_option", "multiple_file_tape_clause",
  "multiple_file_list", "multiple_file", "multiple_file_position",
  "commitment_control_clause", "data_division", "file_section", "$@17",
  "$@18", "file_description_sequence", "file_description",
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
  "sign_clause", "occurs_clause", "occurs_to_integer", "occurs_depending",
  "occurs_keys", "occurs_key_list", "ascending_or_descending",
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
  "stop_statement", "$@87", "stop_returning", "string_statement", "$@88",
  "string_item_list", "string_item", "opt_with_pointer", "end_string",
  "subtract_statement", "$@89", "subtract_body", "end_subtract",
  "suppress_statement", "_printing", "terminate_statement", "$@90",
  "transform_statement", "$@91", "unlock_statement", "$@92", "opt_record",
  "unstring_statement", "$@93", "unstring_delimited",
  "unstring_delimited_list", "unstring_delimited_item", "unstring_into",
  "unstring_into_item", "unstring_into_delimiter", "unstring_into_count",
  "unstring_tallying", "end_unstring", "use_statement", "use_exception",
  "use_global", "use_exception_target", "_after", "_standard",
  "exception_or_error", "exception_or_overflow",
  "not_exception_or_overflow", "_procedure", "use_debugging",
  "use_debugging_target", "use_reporting", "write_statement", "$@94",
  "write_from", "write_option", "before_or_after", "write_handler",
  "end_write", "on_accp_exception", "on_disp_exception",
  "opt_on_exception", "$@95", "opt_not_on_exception", "$@96",
  "on_size_error", "opt_on_size_error", "$@97", "opt_not_on_size_error",
  "$@98", "on_overflow", "opt_on_overflow", "$@99", "opt_not_on_overflow",
  "$@100", "at_end", "at_end_sentence", "$@101", "not_at_end_sentence",
  "$@102", "at_eop", "at_eop_sentence", "$@103", "not_at_eop_sentence",
  "$@104", "opt_invalid_key", "invalid_key", "invalid_key_sentence",
  "$@105", "not_invalid_key_sentence", "$@106", "_opt_scroll_lines",
  "condition", "expr", "partial_expr", "$@107", "expr_tokens",
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
     695,   696,   697,    43,    45,    42,    47,   698,    94,    46,
      61,    41,    40,    62,    60,    58,    38
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   457,   459,   458,   460,   460,   461,   461,   463,   464,
     462,   466,   467,   465,   469,   470,   468,   471,   471,   471,
     472,   472,   473,   474,   476,   475,   477,   478,   478,   479,
     479,   480,   480,   481,   481,   481,   482,   482,   483,   483,
     484,   484,   485,   485,   486,   486,   486,   486,   487,   488,
     488,   488,   488,   489,   490,   491,   492,   492,   492,   492,
     493,   493,   494,   494,   494,   495,   496,   496,   497,   498,
     499,   500,   500,   501,   501,   502,   502,   503,   503,   504,
     505,   505,   505,   506,   506,   507,   507,   507,   507,   507,
     507,   507,   507,   507,   507,   507,   508,   509,   508,   510,
     508,   508,   508,   508,   508,   511,   511,   512,   512,   513,
     514,   514,   516,   515,   517,   517,   517,   517,   517,   518,
     518,   519,   519,   520,   519,   521,   521,   522,   522,   522,
     522,   522,   522,   523,   523,   523,   523,   523,   523,   524,
     525,   526,   526,   527,   527,   528,   529,   529,   530,   530,
     531,   532,   533,   534,   535,   536,   537,   538,   538,   539,
     538,   540,   538,   541,   541,   542,   542,   544,   543,   545,
     545,   546,   546,   546,   546,   546,   546,   546,   546,   546,
     546,   546,   546,   546,   546,   547,   547,   547,   548,   548,
     548,   549,   549,   549,   550,   550,   550,   551,   552,   552,
     552,   553,   553,   555,   554,   554,   556,   557,   557,   557,
     558,   559,   560,   560,   560,   561,   562,   562,   562,   563,
     563,   563,   563,   564,   564,   565,   565,   566,   566,   566,
     566,   566,   567,   568,   569,   569,   570,   571,   572,   573,
     573,   573,   574,   574,   575,   575,   576,   576,   577,   577,
     577,   578,   579,   579,   579,   579,   580,   581,   581,   582,
     583,   583,   584,   585,   585,   586,   587,   586,   588,   586,
     589,   589,   590,   591,   591,   592,   592,   594,   593,   595,
     595,   596,   596,   596,   596,   596,   596,   596,   596,   596,
     596,   596,   596,   597,   598,   598,   598,   599,   599,   599,
     600,   600,   601,   601,   602,   602,   603,   604,   604,   605,
     605,   606,   606,   607,   608,   609,   609,   610,   610,   610,
     611,   612,   613,   614,   615,   616,   616,   617,   618,   617,
     619,   619,   621,   620,   622,   622,   622,   623,   624,   623,
     625,   623,   626,   627,   628,   628,   629,   629,   629,   630,
     631,   631,   632,   632,   632,   633,   634,   634,   635,   635,
     635,   635,   635,   635,   635,   635,   635,   635,   635,   635,
     635,   635,   635,   636,   637,   638,   638,   639,   640,   641,
     641,   642,   642,   642,   642,   642,   642,   642,   642,   642,
     642,   642,   642,   642,   642,   642,   642,   642,   642,   642,
     642,   642,   642,   642,   642,   642,   642,   642,   642,   642,
     642,   642,   642,   642,   642,   642,   643,   643,   644,   645,
     645,   646,   646,   647,   648,   648,   649,   649,   650,   650,
     651,   651,   652,   653,   654,   655,   655,   655,   656,   657,
     658,   660,   659,   661,   661,   662,   662,   663,   663,   664,
     664,   665,   666,   667,   666,   668,   669,   668,   670,   671,
     670,   672,   672,   673,   673,   674,   675,   675,   676,   676,
     676,   676,   677,   677,   678,   679,   679,   680,   680,   681,
     682,   682,   683,   683,   684,   684,   685,   685,   686,   686,
     687,   687,   687,   688,   688,   689,   689,   690,   691,   691,
     692,   692,   692,   692,   692,   692,   692,   692,   692,   692,
     692,   692,   692,   692,   692,   692,   693,   694,   694,   694,
     694,   694,   694,   694,   695,   696,   696,   696,   697,   697,
     698,   699,   700,   701,   702,   703,   703,   704,   704,   705,
     705,   705,   706,   706,   706,   707,   708,   709,   709,   710,
     711,   712,   713,   711,   714,   714,   715,   715,   716,   717,
     716,   718,   718,   719,   719,   719,   719,   719,   719,   719,
     719,   719,   719,   719,   719,   719,   719,   719,   719,   719,
     719,   719,   719,   719,   719,   719,   719,   719,   719,   719,
     719,   719,   719,   720,   720,   720,   720,   720,   721,   721,
     721,   721,   721,   722,   723,   724,   725,   723,   726,   727,
     726,   728,   726,   729,   729,   730,   731,   731,   731,   732,
     732,   732,   732,   732,   733,   733,   734,   734,   735,   736,
     735,   737,   737,   738,   738,   738,   738,   738,   739,   740,
     741,   742,   743,   743,   745,   746,   744,   747,   747,   748,
     748,   748,   748,   748,   748,   748,   748,   748,   748,   748,
     748,   748,   748,   748,   748,   748,   748,   748,   748,   748,
     748,   748,   748,   748,   748,   748,   748,   748,   748,   748,
     748,   748,   748,   748,   748,   748,   748,   748,   748,   748,
     748,   748,   748,   748,   748,   748,   748,   748,   748,   750,
     749,   751,   751,   751,   751,   751,   751,   751,   751,   751,
     751,   751,   751,   751,   751,   751,   751,   751,   752,   752,
     752,   752,   752,   752,   753,   754,   754,   755,   755,   756,
     756,   757,   757,   757,   757,   757,   757,   757,   757,   757,
     757,   757,   757,   757,   757,   757,   757,   757,   758,   758,
     760,   759,   761,   761,   761,   762,   762,   763,   763,   765,
     764,   766,   766,   767,   767,   768,   769,   769,   770,   770,
     772,   771,   773,   774,   773,   775,   775,   776,   776,   777,
     777,   777,   777,   778,   778,   778,   779,   780,   779,   781,
     782,   781,   783,   783,   785,   784,   786,   786,   788,   787,
     789,   789,   790,   790,   790,   790,   790,   791,   791,   793,
     792,   794,   795,   795,   796,   796,   797,   798,   800,   799,
     801,   801,   803,   802,   805,   804,   806,   806,   806,   806,
     806,   806,   806,   806,   806,   807,   807,   807,   808,   808,
     809,   809,   809,   809,   809,   809,   809,   809,   809,   809,
     809,   809,   809,   809,   809,   810,   810,   812,   811,   813,
     813,   813,   813,   813,   814,   814,   816,   815,   818,   817,
     819,   819,   820,   820,   820,   821,   822,   822,   824,   823,
     825,   826,   825,   827,   827,   828,   828,   829,   829,   829,
     829,   830,   830,   831,   831,   833,   832,   834,   834,   834,
     834,   834,   834,   836,   835,   838,   837,   840,   839,   841,
     841,   843,   842,   845,   846,   844,   844,   847,   848,   847,
     849,   849,   851,   850,   852,   852,   853,   853,   853,   854,
     854,   855,   855,   856,   857,   857,   857,   857,   857,   857,
     857,   858,   858,   860,   859,   862,   861,   863,   863,   863,
     864,   864,   865,   865,   865,   867,   866,   868,   868,   869,
     869,   869,   869,   869,   869,   870,   871,   871,   872,   872,
     873,   873,   873,   873,   873,   874,   875,   876,   876,   877,
     877,   879,   878,   881,   880,   882,   882,   884,   883,   885,
     885,   886,   886,   888,   887,   889,   889,   890,   890,   890,
     890,   891,   891,   892,   892,   892,   894,   893,   895,   896,
     895,   895,   897,   897,   898,   898,   899,   899,   899,   899,
     899,   900,   900,   901,   901,   902,   904,   903,   905,   905,
     906,   906,   906,   906,   906,   906,   907,   907,   908,   908,
     908,   909,   909,   911,   910,   913,   912,   914,   914,   916,
     915,   917,   917,   917,   918,   918,   919,   921,   920,   922,
     923,   922,   924,   924,   925,   926,   925,   927,   927,   929,
     928,   930,   930,   932,   931,   933,   933,   933,   933,   933,
     934,   935,   935,   936,   937,   937,   938,   938,   939,   940,
     940,   941,   941,   943,   942,   945,   944,   946,   946,   947,
     947,   948,   948,   949,   949,   950,   950,   950,   951,   951,
     951,   953,   954,   952,   955,   955,   956,   956,   956,   956,
     956,   957,   957,   959,   958,   958,   960,   960,   960,   962,
     961,   963,   963,   964,   964,   964,   965,   965,   966,   966,
     968,   967,   969,   969,   969,   970,   970,   971,   972,   972,
     974,   973,   976,   975,   978,   977,   979,   979,   979,   981,
     980,   982,   982,   983,   983,   984,   985,   985,   986,   987,
     987,   988,   988,   989,   989,   990,   990,   991,   991,   991,
     992,   993,   993,   994,   994,   994,   994,   994,   995,   995,
     996,   996,   997,   997,   998,   998,   999,   999,  1000,  1000,
    1001,  1002,  1002,  1003,  1005,  1004,  1006,  1006,  1007,  1007,
    1007,  1007,  1008,  1008,  1009,  1009,  1009,  1010,  1010,  1011,
    1012,  1013,  1014,  1013,  1015,  1016,  1015,  1017,  1018,  1019,
    1018,  1020,  1021,  1020,  1022,  1023,  1024,  1023,  1025,  1026,
    1025,  1027,  1027,  1027,  1029,  1028,  1031,  1030,  1032,  1032,
    1032,  1034,  1033,  1036,  1035,  1037,  1037,  1038,  1038,  1038,
    1040,  1039,  1042,  1041,  1043,  1043,  1044,  1045,  1047,  1046,
    1048,  1048,  1048,  1048,  1048,  1048,  1048,  1048,  1048,  1048,
    1048,  1048,  1048,  1049,  1049,  1049,  1049,  1049,  1049,  1049,
    1049,  1049,  1049,  1049,  1049,  1049,  1049,  1049,  1049,  1049,
    1049,  1049,  1049,  1049,  1049,  1049,  1049,  1049,  1049,  1050,
    1050,  1050,  1051,  1051,  1052,  1052,  1053,  1053,  1053,  1054,
    1054,  1054,  1055,  1055,  1056,  1056,  1056,  1057,  1057,  1057,
    1057,  1057,  1057,  1057,  1057,  1057,  1058,  1058,  1059,  1059,
    1060,  1061,  1062,  1063,  1063,  1064,  1065,  1065,  1066,  1067,
    1067,  1068,  1069,  1069,  1069,  1070,  1071,  1071,  1072,  1073,
    1073,  1074,  1074,  1075,  1076,  1076,  1077,  1077,  1078,  1078,
    1079,  1079,  1079,  1079,  1079,  1079,  1079,  1079,  1079,  1080,
    1080,  1080,  1080,  1080,  1080,  1080,  1081,  1081,  1082,  1082,
    1083,  1083,  1084,  1084,  1085,  1085,  1086,  1086,  1086,  1087,
    1087,  1087,  1088,  1089,  1089,  1089,  1089,  1090,  1090,  1091,
    1092,  1092,  1093,  1094,  1094,  1095,  1095,  1096,  1096,  1096,
    1096,  1096,  1096,  1096,  1097,  1097,  1097,  1097,  1097,  1097,
    1097,  1097,  1097,  1097,  1097,  1097,  1098,  1098,  1098,  1099,
    1099,  1100,  1100,  1101,  1101,  1101,  1102,  1102,  1103,  1103,
    1104,  1105,  1105,  1106,  1106,  1107,  1107,  1108,  1108,  1108,
    1109,  1109,  1110,  1110,  1111,  1111,  1112,  1112,  1113,  1113,
    1114,  1114,  1115,  1115,  1116,  1116,  1117,  1117,  1118,  1118,
    1119,  1119,  1120,  1120,  1121,  1121,  1122,  1122,  1123,  1123,
    1124,  1124,  1125,  1125,  1126,  1126,  1127,  1127,  1128,  1128,
    1129,  1129,  1130,  1130,  1131,  1131,  1132,  1132,  1133,  1133,
    1134,  1134,  1134,  1135,  1135,  1136,  1136,  1136,  1137,  1137,
    1138,  1138,  1139,  1139,  1140,  1140,  1141,  1141,  1142,  1142,
    1142,  1143,  1143,  1144,  1144,  1145,  1145,  1146,  1146,  1147,
    1147,  1148,  1148,  1149,  1149,  1149,  1150,  1150,  1151,  1151,
    1152,  1152,  1153,  1153,  1154,  1154,  1155,  1155,  1156,  1156,
    1157,  1157,  1158,  1158
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
       1,     1,     1,     1,     1,     5,     4,     4,     0,     1,
       1,     0,     1,     1,     1,     1,     1,     4,     1,     1,
       1,     6,     8,     0,     2,     2,     1,     0,     2,     1,
       3,     5,     0,     1,     1,     4,     2,     2,     1,     0,
       4,     5,     2,     1,     1,     3,     1,     1,     3,     1,
       1,     2,     4,     4,     4,     6,     4,     3,     3,     2,
       2,     2,     0,     3,     0,     2,     1,     2,     1,     1,
       1,     5,     0,     1,     1,     1,     5,     1,     2,     2,
       0,     2,     4,     0,     9,     0,     0,     5,     0,     3,
       0,     2,     3,     2,     2,     1,     1,     0,     4,     0,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     0,     1,     1,     4,     6,     9,
       0,     3,     0,     2,     0,     2,     3,     1,     1,     5,
       5,     1,     1,     3,     5,     0,     2,     1,     1,     1,
       5,     4,     3,     4,     3,     3,     3,     0,     0,     5,
       0,     1,     0,     2,     2,     3,     2,     1,     0,     5,
       0,     4,     1,     1,     0,     1,     0,     1,     1,     1,
       0,     2,     1,     3,     3,     6,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     0,     2,     2,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     1,     2,     2,     1,     2,     2,     1,     2,
       2,     1,     2,     2,     1,     1,     3,     3,     7,     0,
       2,     0,     3,     1,     0,     5,     1,     1,     0,     3,
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
       0,     3,     0,     1,     0,     3,     0,     2,     0,     3,
       0,     3,     0,     1,     3,     3,     2,     1,     1,     0,
       4,     4,     0,     1,     1,     1,     1,     1,     0,     6,
       0,     1,     0,     4,     0,     4,     3,     3,     3,     3,
       4,     6,     6,     6,     6,     0,     2,     2,     1,     2,
       1,     1,     2,     2,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     1,     1,     0,     1,     0,     4,     4,
       6,     6,     8,     8,     0,     1,     0,     4,     0,     5,
       1,     3,     1,     1,     1,     2,     1,     2,     0,     3,
       0,     0,     3,     2,     3,     1,     3,     2,     1,     1,
       1,     0,     2,     0,     1,     0,     3,     0,     1,     1,
       2,     1,     1,     0,     3,     0,     3,     0,     5,     0,
       3,     0,     2,     0,     0,     8,     3,     0,     0,     3,
       0,     1,     0,     7,     0,     2,     0,     3,     3,     0,
       2,     1,     2,     4,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     0,     3,     0,     4,     1,     1,     1,
       1,     2,     1,     1,     1,     0,     3,     1,     2,     2,
       2,     1,     1,     1,     2,     2,     1,     2,     4,     2,
       0,     1,     1,     1,     1,     4,     5,     0,     4,     0,
       1,     0,     3,     0,     3,     3,     4,     0,     4,     4,
       6,     0,     1,     0,     3,     0,     5,     1,     1,     1,
       1,     0,     3,     0,     3,     2,     0,     3,     2,     0,
       4,     2,     0,     1,     1,     3,     0,     1,     2,     3,
       3,     0,     3,     1,     3,     7,     0,    10,     0,     2,
       0,     2,     2,     3,     3,     2,     0,     3,     0,     1,
       1,     0,     1,     0,     4,     0,     7,     0,     1,     0,
       7,     0,     2,     3,     0,     1,     1,     0,     4,     4,
       0,     7,     0,     2,     0,     0,     4,     1,     2,     0,
       4,     0,     1,     0,     3,     1,     1,     1,     1,     1,
       4,     4,     3,     4,     1,     1,     1,     2,     3,     1,
       2,     3,     3,     0,     3,     0,     7,     0,     5,     0,
       2,     0,     2,     0,     3,     0,     2,     4,     0,     2,
       4,     0,     0,     7,     0,     4,     2,     2,     2,     2,
       2,     0,     1,     0,     4,     2,     0,     2,     2,     0,
       8,     1,     2,     1,     3,     3,     0,     3,     0,     1,
       0,     4,     4,     6,     6,     0,     1,     2,     0,     1,
       0,     3,     0,     7,     0,     4,     0,     1,     1,     0,
       9,     0,     3,     1,     3,     2,     2,     2,     3,     0,
       3,     0,     3,     0,     3,     0,     1,     1,     1,     1,
       8,     0,     1,     1,     1,     1,     1,     1,     0,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       5,     1,     2,     5,     0,     8,     0,     2,     0,     4,
       3,     3,     1,     1,     0,     1,     1,     0,     1,     2,
       2,     0,     0,     3,     0,     0,     3,     2,     0,     0,
       3,     0,     0,     3,     2,     0,     0,     3,     0,     0,
       3,     1,     1,     2,     0,     3,     0,     3,     1,     1,
       2,     0,     3,     0,     3,     0,     1,     1,     1,     2,
       0,     3,     0,     3,     0,     3,     1,     1,     0,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     0,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       2,     1,     1,     2,     1,     2,     1,     5,     4,     1,
       5,     4,     1,     3,     0,     1,     1,     1,     3,     3,
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
       2,     0,     0,     1,     0,     0,     0,     4,     6,     7,
      38,    38,     0,     0,     3,     5,     0,     8,    14,    28,
      27,    29,    29,     0,   263,   263,     0,     0,    24,    40,
       0,     9,    15,    30,    26,  1508,     0,   157,     0,   604,
     604,  1509,     0,     0,     0,     0,     0,     0,    39,   265,
       0,    17,     0,    25,    33,    37,    36,  1533,    35,    42,
     159,     0,   161,   275,   276,     0,   327,   268,   608,    18,
      20,    38,     0,    16,    34,  1534,    32,    41,   165,   163,
     244,     0,     0,   452,     0,   611,   609,   626,     0,    19,
      10,    11,     0,     0,     0,     0,     0,    43,    44,    45,
      47,    46,   160,     0,   242,     0,  1500,   252,   162,     0,
     246,   248,   249,   250,   266,     0,     0,   455,  1345,   269,
     330,   277,   616,   616,     0,     0,     0,   263,    23,    56,
      71,    49,    80,  1462,   166,   165,     0,   158,  1526,  1501,
    1550,   253,   254,   255,  1482,   245,   247,   270,   328,     0,
       0,   458,   274,     0,   273,   331,  1450,   279,  1491,   616,
     613,   619,     0,   616,   627,   605,    21,    12,     0,  1508,
      54,  1533,    55,  1533,    60,    62,    63,    64,     0,     0,
      70,     0,    73,  1563,    48,     0,  1562,     0,     0,  1508,
    1508,     0,     0,  1541,  1508,  1508,  1508,  1508,  1508,     0,
    1508,  1494,  1508,    79,    81,    83,    85,    86,    87,    89,
      88,    90,    91,    92,    93,    94,    95,  1463,     0,   164,
     244,  1527,     0,  1551,  1496,  1483,  1502,   267,   330,   453,
       0,     0,   550,   330,   333,     0,     0,   614,  1508,     0,
     624,   617,   618,   628,   604,  1508,     0,    57,  1533,    59,
      61,     0,  1475,  1508,     0,    77,     0,    72,    74,    52,
      50,     0,     0,  1363,   112,     0,     0,  1508,  1508,  1542,
    1508,     0,     0,     0,     0,     0,  1508,     0,  1495,     0,
      99,    82,    84,   167,   243,  1407,   262,  1356,  1358,  1497,
       0,  1503,     0,   271,   329,   330,   456,     0,     0,   264,
     272,   336,     0,   342,   343,   334,   346,   346,   337,   292,
    1496,  1508,     0,     0,  1508,  1496,  1520,  1508,  1480,     0,
     278,   280,   283,   284,   285,   286,   287,   288,   289,   290,
     291,     0,     0,  1508,   625,     0,     0,   606,    17,     0,
    1412,    69,    58,  1474,     0,    76,    75,    78,    51,    53,
    1508,   101,   102,     0,     0,     0,   153,   152,   103,   104,
     156,     0,   155,   139,  1510,   141,    96,     0,    97,   169,
    1468,  1469,     0,  1357,   256,   257,   260,   251,  1343,   454,
     330,   459,     0,   335,   347,   348,   338,     0,   348,   340,
       0,     0,  1508,  1480,     0,     0,     0,     0,     0,  1521,
    1508,     0,  1481,     0,     0,   281,   282,   620,   621,   623,
       0,   615,   629,   631,     0,     0,    68,     0,  1421,  1417,
    1422,  1420,  1418,  1423,  1419,   145,   146,   148,   154,   151,
     150,  1512,  1511,   142,     0,   111,   110,   100,   107,  1548,
     105,     0,  1408,   258,     0,   259,  1344,   457,   461,   551,
     356,   350,     0,   304,   324,  1470,  1471,   313,   308,   307,
     306,  1362,  1361,  1518,  1494,  1506,     0,   549,   325,   326,
    1508,  1508,   622,   631,     0,     0,    13,    66,    67,    65,
     117,   131,   127,   132,   114,   130,   128,   115,   116,   129,
     113,   118,   119,   121,   147,     0,   140,   143,   108,  1549,
    1508,    98,   184,  1520,     0,  1558,   227,     0,  1520,  1508,
    1492,  1513,   230,     0,   229,  1562,   214,   213,   168,   170,
     171,   172,   173,   174,   175,     0,   176,   177,   226,   178,
     179,   180,   181,   182,   183,  1508,   261,     0,   460,   462,
     463,   552,     0,  1484,     0,  1510,   341,     0,   294,  1519,
     315,     0,   297,  1507,  1546,   323,     0,     0,     0,   637,
     641,   632,   633,   634,   635,   640,     0,     0,   120,   123,
       0,   149,   144,     0,   106,  1508,  1513,  1559,   191,   231,
    1508,     0,  1493,  1508,  1489,  1508,  1514,     0,  1508,  1508,
    1482,     0,  1508,     0,   466,   464,   554,   372,     0,   439,
     381,   414,   402,   411,   408,   405,  1560,   382,   383,   384,
     385,   386,   387,   388,   389,   390,  1537,   345,   415,     0,
     391,   378,   392,   393,     0,     0,  1544,   395,   396,   394,
     435,   398,   399,   397,  1508,  1508,   339,   357,   358,   359,
     360,   361,   362,   379,   363,   364,   365,   366,   367,   368,
     369,   370,   371,     0,     0,  1485,     0,   351,     0,   305,
     296,   295,   293,   314,  1494,  1547,   302,   311,   310,   312,
     309,     0,   639,   642,   699,   750,   759,   766,   770,   794,
     798,   816,   809,   817,   818,   824,   857,   866,   868,   895,
     903,   905,  1558,   911,     0,   922,   943,   945,   981,   983,
     987,   698,   993,  1006,  1026,  1043,  1045,  1049,  1056,  1057,
    1073,  1093,  1111,     0,  1129,  1140,  1148,  1150,  1152,  1154,
    1159,  1181,  1204,   636,   648,   649,   650,   651,   652,   653,
     654,   655,   657,   656,   658,   659,   660,   661,   662,   663,
     664,   665,   666,   667,   668,   669,   670,   671,   672,   673,
     674,   675,   676,   677,   678,   679,   680,   681,   682,   683,
     684,   685,   686,   687,   688,   689,   690,   691,   692,   693,
     694,   695,   696,  1177,  1178,  1179,   697,    22,     0,   122,
     109,     0,  1508,   193,   192,   188,     0,  1488,   230,   225,
       0,     0,   228,     0,     0,   237,  1531,  1531,     0,   238,
       0,   210,  1508,   346,   558,   553,   555,   556,   451,   412,
     413,   400,   401,   409,   410,   406,   407,   403,   404,  1561,
       0,  1538,   433,   419,   373,  1403,   449,  1545,   436,   437,
     434,     0,     0,   375,   377,  1466,  1466,     0,  1524,  1524,
     355,   352,  1413,  1415,   441,   443,   445,  1487,   316,   317,
     318,   319,     0,     0,   298,  1505,   304,     0,     0,   643,
       0,     0,     0,  1268,   765,     0,   796,   800,     0,     0,
       0,     0,     0,     0,  1268,   897,     0,     0,   907,   912,
       0,  1268,     0,     0,     0,     0,     0,     0,   995,  1016,
       0,     0,     0,     0,     0,     0,     0,     0,  1125,  1123,
       0,     0,  1149,  1147,     0,     0,     0,     0,  1182,  1188,
       0,     0,   137,   133,   138,   136,   134,   135,   124,   125,
     199,   200,   198,   197,     0,   186,   187,     0,   219,   218,
     219,   215,   232,   233,   234,   236,  1532,   239,   240,   241,
    1359,  1508,   475,   475,  1510,   495,   467,   470,   471,     0,
     559,   557,   438,     0,  1556,     0,  1404,  1405,     0,   380,
     440,     0,   374,  1492,   416,   417,  1414,  1525,     0,     0,
       0,  1560,   444,     0,     0,     0,  1486,  1494,   303,   630,
     638,   748,   718,  1402,  1524,     0,     0,  1436,  1439,  1524,
    1336,     0,     0,     0,     0,     0,     0,     0,     0,  1436,
     757,  1378,   755,  1368,  1370,  1376,  1377,  1455,   760,     0,
    1267,  1283,  1355,     0,  1351,  1353,  1352,  1397,   772,  1396,
    1398,   795,   799,   812,     0,  1338,  1464,  1535,     0,  1417,
     855,   718,     0,  1370,   864,     0,   772,   874,   873,  1478,
     870,   872,   902,   899,   898,   901,   896,  1524,   904,  1364,
    1366,   906,  1349,   916,  1554,  1266,   924,   944,   477,     0,
     947,   948,   949,   982,  1097,     0,   984,     0,   991,     0,
     994,  1017,  1355,  1007,  1016,  1009,     0,  1014,     0,  1352,
       0,  1457,  1206,  1341,  1535,  1206,     0,  1071,  1062,  1342,
       0,  1348,  1074,  1075,  1076,  1077,  1078,  1086,  1079,  1089,
       0,  1346,     0,  1094,  1112,  1126,  1490,     0,  1131,  1133,
       0,  1145,     0,  1151,     0,  1156,  1161,  1189,     0,  1190,
    1526,  1206,     0,  1453,   195,   194,   185,   196,     0,   217,
     216,  1508,   209,   203,  1360,   211,     0,   476,   472,     0,
     473,     0,   465,   468,   561,   420,  1557,   421,  1524,     0,
       0,     0,  1324,  1322,  1385,  1327,  1379,  1383,  1384,     0,
    1406,   450,   376,  1467,   354,   353,  1416,  1539,   446,   322,
    1518,     0,   300,   749,   700,  1487,     0,   727,     0,     0,
       0,     0,     0,  1424,  1441,  1435,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1425,   758,   751,     0,
       0,  1369,  1456,   763,  1455,  1269,     0,   768,     0,   773,
     783,  1395,   797,  1394,   802,   813,   810,   815,   814,  1268,
    1339,  1465,  1340,  1536,  1255,   823,   856,   825,   835,  1221,
    1221,  1221,  1221,   865,   858,     0,     0,   867,  1479,  1268,
     893,   880,   876,   878,  1268,   900,     0,  1365,   909,  1555,
     914,   926,     0,   478,     0,   970,   955,   946,   950,   952,
     953,   954,  1101,     0,     0,   992,   988,     0,  1000,   997,
     999,   998,  1001,  1008,  1011,   644,  1268,     0,     0,  1018,
       0,  1458,  1459,  1535,     0,  1044,  1028,  1051,  1064,  1072,
    1058,     0,  1064,     0,  1390,  1391,  1087,  1090,     0,     0,
    1347,  1085,     0,  1084,     0,  1114,     0,     0,  1124,     0,
       0,  1132,     0,  1146,  1141,     0,     0,  1157,  1158,  1155,
    1490,     0,     0,  1191,     0,     0,  1051,   126,  1473,     0,
     203,   201,  1454,     0,   222,   208,   235,     0,   469,   474,
     480,   490,   346,   496,  1543,  1526,   424,     0,  1332,  1333,
       0,  1325,  1326,  1409,     0,     0,     0,     0,     0,     0,
       0,     0,  1540,  1558,   321,  1518,  1526,   299,   723,   714,
    1221,   704,   711,   705,   707,   709,     0,  1221,     0,   703,
     710,   717,   716,     0,  1221,  1522,  1522,  1522,   721,   722,
    1387,  1386,     0,  1375,  1324,  1322,     0,     0,  1324,     0,
    1371,  1372,  1373,  1337,  1324,     0,     0,  1324,     0,     0,
    1324,  1324,  1324,     0,     0,  1228,  1464,     0,     0,   761,
       0,  1275,  1276,  1277,  1307,  1278,  1558,  1311,  1316,  1552,
    1270,  1319,  1552,  1300,  1280,  1282,  1274,  1273,  1308,  1279,
    1281,  1290,  1291,  1292,  1293,  1294,  1309,  1272,  1312,  1314,
    1295,  1296,  1297,  1298,  1299,  1284,  1306,  1289,  1286,  1287,
    1288,  1285,  1301,  1302,  1303,  1304,  1305,  1271,     0,     0,
    1354,   779,     0,     0,   786,   807,   808,   801,   803,     0,
    1228,  1260,  1262,   820,  1256,  1257,  1258,     0,  1563,  1221,
       0,  1222,   828,  1224,   829,   826,   827,     0,  1228,  1464,
     888,   890,   889,   883,   885,   891,   894,   869,   881,   877,
     875,  1268,   644,   871,  1367,  1526,   908,  1350,   644,  1558,
     934,   935,   937,   939,   940,   936,   938,   929,  1558,   925,
       0,   971,     0,   973,   972,   974,   965,   966,     0,     0,
     951,  1103,  1528,     0,     0,   985,  1228,  1464,  1562,     0,
    1012,   645,  1019,  1020,  1023,     0,  1015,  1213,  1212,  1022,
    1028,  1207,     0,     0,  1255,     0,     0,     0,  1063,     0,
       0,     0,  1088,     0,  1092,  1091,  1082,     0,  1508,  1255,
    1128,  1127,  1134,  1135,  1136,     0,  1228,  1464,     0,  1451,
       0,  1136,  1203,  1193,  1192,  1198,     0,  1200,  1201,  1208,
    1472,  1453,     0,   205,   206,   204,  1508,   482,   493,   494,
     492,   498,   574,  1508,   565,   563,   564,   566,  1522,     0,
    1508,     0,   577,   569,  1522,   570,     0,   573,   578,   576,
     571,   575,     0,   572,     0,   560,   588,   583,   586,   585,
     584,   587,   562,   589,     0,   428,   423,  1380,  1381,  1382,
    1335,  1323,  1328,  1329,  1330,  1331,  1334,  1410,     0,   447,
     320,     0,   715,  1224,   706,   708,  1221,   712,   702,   742,
    1508,   731,   732,  1508,   743,   733,   734,   737,   747,   744,
     735,     0,   745,   736,   746,   728,   729,   701,  1523,     0,
       0,     0,   719,   720,  1389,  1374,  1388,  1436,  1464,     0,
    1440,     0,  1436,  1436,     0,  1433,  1436,  1436,  1436,     0,
    1436,  1436,  1229,   752,  1231,  1228,   764,     0,  1310,  1553,
    1313,  1315,   769,   767,   774,   775,   619,     0,   785,   784,
    1194,  1195,   789,   787,     0,   806,     0,   811,   644,   644,
     821,   819,  1259,   835,   835,   835,   835,  1508,   840,   853,
     854,   841,     0,  1508,   844,   845,   848,   846,     0,   847,
     837,   838,   830,   836,   644,  1225,  1220,     0,   859,     0,
    1268,  1268,   887,   644,   884,   879,     0,   917,     0,     0,
     941,     0,     0,     0,   967,   969,     0,   961,   977,   962,
     963,   956,   957,   977,  1095,  1508,     0,  1529,  1102,   426,
     427,  1513,   986,   989,     0,     0,  1003,  1013,  1010,   647,
       0,     0,  1030,  1029,  1244,  1246,  1047,  1241,  1242,  1054,
    1052,     0,  1268,  1065,  1268,  1059,  1067,  1080,  1081,  1083,
    1460,  1121,  1235,     0,  1464,  1142,     0,     0,  1452,  1162,
    1163,     0,  1166,  1169,  1173,  1167,  1199,  1526,  1202,  1214,
    1476,   202,     0,   223,   224,   220,     0,     0,   484,     0,
    1543,     0,  1508,   567,   568,     0,   591,  1508,  1556,   592,
     590,   422,  1490,   418,  1513,  1411,  1508,   442,   301,  1219,
     713,     0,     0,  1264,  1264,   730,   725,   724,   726,  1429,
    1228,  1437,     0,  1449,  1434,  1427,  1447,  1428,  1430,  1431,
    1444,  1445,  1432,  1426,   644,  1232,  1227,   753,   762,  1558,
       0,  1558,     0,   776,   777,     0,   781,   780,   782,  1196,
    1197,   792,   790,   644,   804,   805,  1261,  1263,  1221,  1221,
    1221,  1221,     0,   842,   843,     0,  1264,  1264,   839,  1223,
     644,  1228,  1338,  1228,  1338,   886,   892,   882,   910,   918,
     920,   927,   930,   931,  1498,   942,   923,   928,   977,  1392,
    1393,   977,     0,   960,   958,   959,   964,  1105,     0,  1530,
    1099,  1228,  1002,   996,     0,   646,  1024,     0,     0,  1036,
       0,   644,   644,  1048,  1046,  1243,  1055,  1050,  1053,  1060,
     644,  1069,  1068,  1461,     0,     0,  1122,  1113,  1236,  1138,
    1238,     0,  1228,  1228,  1153,  1451,  1165,  1506,  1171,  1506,
    1235,     0,  1251,  1253,  1217,  1215,  1248,  1249,  1216,  1477,
       0,   221,   481,  1508,     0,   486,   491,  1522,   527,   547,
     542,  1480,     0,     0,  1508,  1524,  1508,     0,   497,   503,
     504,   505,   514,   506,   508,   511,   499,   500,   501,   507,
     510,   528,   512,   515,   502,     0,   509,   513,  1401,   582,
    1399,  1400,   598,   581,   593,   603,     0,  1508,     0,   739,
     738,   741,     0,   740,   754,  1438,  1230,   644,  1318,  1558,
    1321,  1558,   778,   793,   771,   644,   788,   834,   833,   832,
     831,   850,   849,   852,   851,  1226,   861,     0,   860,     0,
     644,   921,   915,   932,  1499,     0,   976,   968,   977,   979,
       0,     0,  1108,  1104,  1098,   990,  1005,     0,     0,  1031,
    1508,  1038,     0,  1032,     0,  1035,  1245,  1247,   644,  1066,
     644,  1115,  1116,  1117,  1118,  1119,  1120,   644,  1139,  1130,
    1239,  1234,  1137,  1144,  1143,  1164,     0,  1506,  1168,     0,
    1175,  1187,  1184,  1186,  1185,  1180,  1183,   644,   644,  1218,
    1205,  1250,  1211,  1210,  1515,     0,  1508,  1508,   488,   526,
    1508,   548,   546,   543,   544,  1510,   536,  1508,  1268,     0,
       0,     0,     0,   529,     0,     0,   534,   537,   540,   601,
     599,   600,   602,     0,   596,   594,   595,   597,     0,   432,
     429,   430,     0,   448,  1515,  1233,  1317,  1320,   791,  1228,
    1228,   919,     0,   975,   980,     0,  1508,  1106,     0,     0,
    1096,  1100,  1004,     0,     0,  1041,  1039,  1040,  1034,  1033,
    1061,  1070,  1237,   644,  1170,     0,  1174,  1176,  1160,  1252,
    1254,  1516,  1517,  1209,   483,     0,     0,  1508,   479,     0,
     535,     0,   532,  1464,   530,   531,   521,   519,   520,   522,
     518,   523,   517,   516,     0,   541,   539,   538,   580,   579,
     431,   425,  1265,   863,   862,   933,   978,     0,  1109,  1508,
    1268,  1037,  1042,  1027,  1240,  1172,   485,   487,     0,   525,
     524,   545,     0,  1107,     0,  1025,   489,     0,  1110,   533
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,     7,     8,    24,    39,    69,   127,
     244,     9,    25,    40,    70,    90,   476,    73,    71,    35,
      11,    21,    27,    42,    57,    58,    17,    37,    77,    97,
      98,   184,   185,   171,    99,   172,   173,   174,   175,   479,
     176,   177,   100,   180,   181,   182,   256,   101,   203,   204,
     205,   206,   440,   367,   501,   437,   438,   439,   207,   350,
     490,   491,   492,   778,   918,   493,   919,   208,   363,   364,
     496,   209,   425,   426,   210,   211,   212,   213,   214,   215,
     216,    48,    78,    80,   104,   102,   134,   369,   441,   519,
     520,   927,   785,  1126,   521,   923,   522,  1336,  1337,  1603,
    1133,   523,   524,   525,   526,   931,  1129,  1855,   527,   528,
     529,   530,   531,   532,   533,   534,   799,   137,   108,   109,
     110,   111,   144,   112,   374,   375,   445,   113,    31,    66,
     147,    84,   227,   152,   119,   153,   120,   157,   236,   321,
     322,   662,   323,  1367,   856,   548,   324,   460,   325,   668,
     326,   327,   663,   848,   849,   850,   851,   328,   329,   330,
      83,   228,   154,   155,   156,   234,   305,   450,   452,   306,
     307,   636,   386,   387,   543,   840,   308,   542,   637,   638,
     639,   962,   640,   641,   642,   643,   644,   645,   954,  1346,
    1645,  1646,  1801,  1873,  2200,  2201,   646,   647,   830,   648,
     649,   650,   546,   971,   844,   845,  1877,   651,   652,   117,
     295,   151,   380,   232,   448,   538,   539,   540,   802,   946,
     947,  1138,  1139,  1057,   948,  1607,  1858,  2025,  2168,  2248,
    1340,  1610,  1142,  1343,  1860,  2046,  2047,  2263,  2048,  2049,
    2050,  2051,  2254,  2052,  2053,  2054,  2055,  2186,  2187,  2175,
    2056,  2057,  2172,   468,   299,   541,   596,   805,   806,   807,
    1144,  1344,  1642,  2198,  2193,  1643,    51,   243,   413,    87,
     123,   122,   159,   160,   161,   240,   335,   125,   337,   473,
     474,   561,   562,   563,   564,   565,   860,  1550,  1551,  1809,
     566,   724,   725,   861,   981,  1177,  1388,  1389,  1384,  1685,
    1686,  1174,   726,   862,  1000,  1200,  1198,   727,   863,  1008,
    1419,   728,   864,  1469,   729,   865,  1210,  1471,  1724,  1725,
    1726,  1474,  1732,  1923,  1921,  2085,  2084,   730,   866,  1021,
     731,   867,  1022,  1477,  1478,   732,   868,  1023,  1216,  1219,
     733,   734,   735,   869,  1741,   736,   870,   737,   871,  1030,
    1489,  1760,  1761,  1227,   738,   872,  1034,  1234,   739,   873,
     740,   874,  1039,  1040,  1240,  1241,  1242,  1512,  1510,  1773,
    1243,  1503,  1504,  1772,  1507,   741,   875,  1046,   742,   876,
     743,   877,   744,  1052,  1516,   745,   879,   746,   881,  1518,
    1950,  2100,  2102,   747,   882,  1251,  1527,  1780,  1952,  1953,
    1954,  1956,   748,   883,   749,   884,  1059,  1257,  1258,  1259,
    1539,  1791,  1792,  1260,  1536,  1537,  1538,  1785,  1261,  1963,
    2215,   750,   885,   751,   886,  1066,   752,   887,  1068,  1266,
     753,   888,  1070,  1272,  1549,  1973,   754,   889,  1073,  1275,
    1808,  1074,  1075,  1076,  1553,  1554,   755,   890,  1563,  1979,
    2121,  2225,  2283,   756,   891,   757,   892,  1984,   758,   893,
    1564,  1987,   759,   760,   894,  1087,  2128,  1292,  1566,  1990,
    1825,  1826,  2130,  1290,   761,   895,  1092,  1093,  1094,  1095,
    1304,  1096,  1097,  1098,  1099,   762,   896,  1063,  1967,  1262,
    2114,  1541,  1794,  2112,  2220,   763,   897,  1305,  1579,  1994,
    1997,   764,  1105,  1308,   765,   900,  1107,  1108,  1832,  2139,
     766,   901,  1111,  1314,   767,   903,   768,   904,   769,   905,
     770,   906,  1319,   771,   907,  1321,  1839,  1840,  1591,  1842,
    2008,  2148,  2010,  2238,   772,   773,   909,  2155,  1119,  1324,
    1595,  1733,  1922,  1847,   774,  1597,   775,   776,   911,  1285,
    1849,  2109,  2014,  2160,  1662,  1492,  1493,  1764,  1766,  1940,
    1713,  1714,  1904,  1906,  2077,  1999,  2000,  2137,  2141,  2233,
    1816,  1817,  1981,  1818,  1982,  2015,  2016,  2157,  2017,  2158,
    1483,  1484,  1485,  1738,  1486,  1739,  2071,  1054,  1055,  1010,
    1011,  1205,  1206,  1450,  1451,  1452,  1453,  1454,  1152,  1354,
    1395,  1001,  1024,  1220,  1082,  1088,   377,   378,  1100,  1101,
    1248,  1077,  1014,  1015,   286,   462,  1135,   463,   264,  1048,
    1049,  1002,  1026,  1155,  1392,  1695,  1793,  1958,  1032,  1078,
    2059,  1004,   983,   825,   956,   957,  2061,  1005,   842,   843,
    1006,  1183,  1185,  1399,  1413,  1408,  1405,   235,  1841,  1331,
    1203,  1283,  1995,   218,  1222,   964,   372,   394,  1332,   253,
    2020,  1770,   403,   226,   656,  1178,   587,   162,   583,   279,
     290,  2105,   140,   292,   857,   554,    43,   434,   588,  2243,
     550,   400,  1689,   968,   222,  1798,   937,   178,  1224,   822,
    1363,   270,   654,   666,   500,   224,  1720,  1250,  1147,   578,
     820,  1490
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1699
static const yytype_int16 yypact[] =
{
   -1699,   268,   548, -1699,  -170,  -148,   247, -1699, -1699, -1699,
     441,   441,    -7,    -7, -1699, -1699,   474, -1699, -1699, -1699,
   -1699,   774,   774,   253,   669,   669,   684,   477, -1699,  1033,
     845, -1699, -1699, -1699, -1699,   -17,   797,   729,   739,   821,
     821, -1699,   755,    72,   764,   769,   808,   773, -1699,   229,
    1135,   941,  1125, -1699,   -86, -1699, -1699,   966, -1699, -1699,
   -1699,   834, -1699, -1699, -1699,   939,   874, -1699,    96, -1699,
     503,   441,    -7, -1699, -1699, -1699, -1699,   882, -1699,  1153,
     117,   873,   984,  1103,   918, -1699, -1699,  1022,    -7, -1699,
   -1699, -1699,   916,   923,   925,   937,   943, -1699, -1699, -1699,
   -1699, -1699,  1023,   949,  1189,  1333,  1002,   792, -1699,    71,
   -1699, -1699, -1699, -1699, -1699,   956,  1055,  1180, -1699,   210,
    1012, -1699,    77,    77,   977,   965,   974,   669, -1699,   278,
    1249,    11,  1331,  1151, -1699, -1699,   981, -1699,  1158, -1699,
    1045, -1699, -1699, -1699,  1413, -1699, -1699, -1699, -1699,   993,
    1092,  1117, -1699,   918, -1699, -1699, -1699, -1699, -1699,   136,
   -1699,   481,  -108,   209, -1699, -1699, -1699, -1699,  1083,  1236,
   -1699,   396, -1699,   641, -1699, -1699, -1699, -1699,   157,   217,
   -1699,    30, -1699, -1699, -1699,  1006,   675,  1347,  1018,  1236,
    1236,  1018,  1086,  1096,  1236,  1236,  1236,  1236,  1236,  1018,
    1236,  1410,  1236, -1699,  1184, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,  1018,  1023,
     117, -1699,  1038, -1699,  1393, -1699,  1310,   210,  1012, -1699,
    1044,  1141,  1154,  1012,   418,  1076,   286, -1699,  1236,  1132,
    1219, -1699, -1699,  1400,   821,  1236,  1269, -1699,   649, -1699,
   -1699,  1149, -1699,  1236,  1301, -1699,    33, -1699, -1699, -1699,
   -1699,  1061,  1270, -1699, -1699,  1018,  1018,  1236,  1236, -1699,
    1236,  1038,  1444,  1018,  1018,  1038,  1236,  1038, -1699,  1018,
      22, -1699, -1699, -1699, -1699,   706,  1038, -1699, -1699, -1699,
     918, -1699,   918, -1699, -1699,  1012, -1699,  1068,  1174, -1699,
   -1699, -1699,  1076, -1699, -1699, -1699,    27,    91, -1699, -1699,
    1393,  1236,   866,   866,  1236,    38,  1283,  1236,  1507,  1261,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699,   776,   160,  1236, -1699,  1098,  1087, -1699,   941,  1269,
   -1699, -1699, -1699, -1699,  1038, -1699, -1699, -1699, -1699, -1699,
    1236, -1699, -1699,  1014,  1038,  1307, -1699, -1699, -1699, -1699,
   -1699,  1038, -1699, -1699,    66, -1699, -1699,  1001, -1699, -1699,
   -1699, -1699,  1038, -1699,   918, -1699,  1244,   918, -1699, -1699,
    1012, -1699,  1093, -1699, -1699,  1462, -1699,  1470, -1699, -1699,
    1269,  1118,  1236,  1507,  1038,   -51,   -55,  1269,  1127, -1699,
    1236,  1123, -1699,  1123,   114, -1699, -1699, -1699, -1699, -1699,
    1269, -1699, -1699, -1699,   530,    67, -1699,   528, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699,  1014, -1699,  1165, -1699, -1699,
   -1699, -1699, -1699, -1699,  1269, -1699, -1699,  1001, -1699,  1186,
   -1699,   906, -1699, -1699,  1269, -1699, -1699, -1699,  1258, -1699,
   -1699,   867,  1146,  1179, -1699, -1699, -1699,  1038, -1699, -1699,
   -1699, -1699, -1699,  1351,   100,  1387,  1148, -1699, -1699, -1699,
    1236,  1236, -1699, -1699,  2729,    -7, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699,  1005, -1699,   104, -1699,  1014,  1269, -1699, -1699, -1699,
    1236,  1001, -1699,  1283,  1272,  1193, -1699,  1228,  1283,  1236,
    1538,   105,   -26,  1269, -1699,  1159, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699,  1218, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699,  1236, -1699,  1123, -1699,  1258,
   -1699, -1699,  2379,  1571,  1418,   559, -1699,  1269,   111, -1699,
   -1699,  1269, -1699, -1699,  1233, -1699,   -43,   -43,  2895, -1699,
    1163, -1699, -1699, -1699, -1699,  1252,  3431,  1167, -1699, -1699,
    1005, -1699, -1699,  1018, -1699,  1236,  1404, -1699,   536, -1699,
    1236,   880, -1699,  1236, -1699,  1236, -1699,  1255,  1236,  1236,
    1413,   172,  1236,  1183, -1699, -1699,  1399, -1699,  1402, -1699,
   -1699,   294,   533,   579,   648,   728,  1194, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699,  1284, -1699, -1699,  1269,
   -1699, -1699, -1699, -1699,  1038,  1038,  1419, -1699, -1699, -1699,
     580, -1699, -1699, -1699,  1236,  1236, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699,   863,   246, -1699,   170, -1699,   120, -1699,
   -1699, -1699, -1699,    83,  1410, -1699,   758, -1699, -1699, -1699,
   -1699,  1522, -1699,  1398, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699,  1231, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699,  1193, -1699,  1909, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699,   -30, -1699, -1699,  1334, -1699, -1699, -1699,
   -1699,   857, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,  1030, -1699,
   -1699,   236,  1236, -1699, -1699,   478,   526,  1595, -1699, -1699,
     -55,  1263, -1699,  1038,  1038, -1699,  1359,  1359,  1366, -1699,
    1038, -1699,   169,    27, -1699, -1699,  1399, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
    1202, -1699, -1699,  1247, -1699,  1197,  1251, -1699, -1699, -1699,
   -1699,  4897,   120,  1623, -1699,  1294,  1294,  1014,  1385,  1385,
   -1699, -1699,  1203, -1699,   120, -1699,  1265, -1699, -1699, -1699,
   -1699, -1699,    47,  1493, -1699, -1699,  1179,  1269,  1223, -1699,
    1226,  1038,  3815,  1240,   336,   743, -1699, -1699,  4418,   918,
    1286,  4430,  4418,  1448,   682,   838,    80,  1038, -1699, -1699,
    1550, -1699,    80,  1038,  1130,  1038,  3853,  4418, -1699,  2259,
     918,  1038,   918,  1038,   103,    69,  1038,   918, -1699, -1699,
    3900,  3974, -1699, -1699,  1038,  1038,   918,  1038, -1699,   237,
    1580,  1038, -1699, -1699, -1699, -1699, -1699, -1699,  1670, -1699,
   -1699, -1699, -1699, -1699,  1038,    17,    45,   118,  1253, -1699,
    1253, -1699, -1699, -1699,   647, -1699, -1699, -1699, -1699, -1699,
    1038,  1236,  1524,  1524,   559, -1699, -1699, -1699, -1699,  1513,
   -1699, -1699, -1699,  1269,  1303,  2354,  1239, -1699,  1038, -1699,
   -1699,  1466, -1699,  1538, -1699, -1699, -1699, -1699,  1038,  1038,
    1014,  1194, -1699,   120,   -55,   -55,  1671,  1410, -1699, -1699,
   -1699,  1578,   763, -1699,  1385,  1264,  1038,  1267,  1268,  1385,
     706,  1275,  1277,  1278,  1282,  1285,  1287,  1291,  1292,  1267,
    1582, -1699,  4150, -1699, -1699, -1699, -1699,  1502, -1699,  1649,
   -1699, -1699, -1699,  1315, -1699,   706, -1699, -1699,  1293, -1699,
   -1699,   387,   918,  1588,  1102, -1699,  1389,  1421,   918,   904,
    1607,  1367,   929,   961,  1608,   550,  1293, -1699, -1699,    46,
   -1699, -1699, -1699,  1647, -1699, -1699, -1699,  1385,    80, -1699,
   -1699, -1699, -1699, -1699,  1352, -1699,    73,  1038, -1699,   231,
   -1699, -1699, -1699, -1699, -1699,  4418, -1699,  1349,  1617,  1703,
     835, -1699,  1356, -1699,  5052,  1619,   721,  1360,  1361,  -163,
    1364,   813,  1581, -1699,  1421,  1581,  1038,  1620,  1332, -1699,
     646, -1699, -1699, -1699, -1699, -1699,  1517, -1699,    80, -1699,
     377, -1699,    76, -1699, -1699,   -11,  1714,  3722, -1699, -1699,
    1038,  1621,  4172,  1038,  1589,   972,  1657, -1699,  1440,  1396,
    1158,  1581,  1030,   190, -1699, -1699, -1699, -1699,   434, -1699,
   -1699,  1236, -1699, -1699, -1699, -1699,   387, -1699, -1699,  1038,
   -1699,  1269,  1399, -1699, -1699, -1699, -1699,  1659,  1385,  2354,
    2354,  2354,    18,   815, -1699, -1699, -1699,  1203, -1699,  2354,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699,  1412, -1699, -1699,
    1351,   -55,  1662, -1699, -1699,   646,  1394,  1341,   331,    12,
    2354,  1379,  2354, -1699,  2354, -1699,  2099,  1342,  2354,  2354,
    2354,  2354,  2354,  2354,  2354,  2354, -1699, -1699, -1699,  4418,
    1596, -1699, -1699,  1445,  1502,  1395,  3138,  1478,  1552, -1699,
     401, -1699, -1699, -1699,   757, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699,    34,   918, -1699, -1699,   369,  1626,
    1626,  1626,  1626, -1699, -1699,  4418,  4418, -1699, -1699,    89,
    1658,   864, -1699,  1362,   682, -1699,  1038, -1699,    59, -1699,
   -1699,   772,  1625, -1699,   646,   127, -1699,   231, -1699, -1699,
   -1699, -1699,    68,  1390,    80, -1699, -1699,  4418, -1699, -1699,
   -1699, -1699,  1430, -1699, -1699, -1699, -1699,  1038,   336, -1699,
     895, -1699, -1699,  1421,   387, -1699,  1590,   313,   814, -1699,
   -1699,  1038,   814,  1401, -1699,  1203, -1699, -1699,    78,  1001,
   -1699, -1699,  3595, -1699,  1748,  1587,  4418,  4418, -1699,  4194,
    1038, -1699,  1628, -1699, -1699,  4418,   646, -1699, -1699, -1699,
    1714,  1599,  1038, -1699,   574,    74,   313, -1699, -1699,  1683,
   -1699, -1699, -1699,  1531, -1699, -1699,  1038,  1038, -1699,  1038,
    1618,  1079,    91, -1699,  4671,  1158, -1699,  2099,  1365,  1365,
    1025, -1699, -1699, -1699,  2354,  2354,  2354,  2354,  2354,  2354,
    4933,   815, -1699,  1193, -1699,  1351,  1158, -1699, -1699, -1699,
    1626, -1699, -1699,  1369,  1368, -1699,   646,  1626,  1598, -1699,
   -1699, -1699, -1699,  1987,  1626,  1549,  1549,  1549,   138,  1586,
   -1699, -1699,   398, -1699,    32,   859,  1038,  1043,    49,  1371,
   -1699,  1203, -1699, -1699,   216,  1372,  1078,   280,  1374,  1210,
      56,    97,   428,  1375,  1222,  4258,   489,  4418,    80, -1699,
    1480, -1699, -1699, -1699, -1699, -1699,  1193, -1699, -1699,  1424,
   -1699, -1699,  1424, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,  1420,   336,
   -1699,    60,  1038,  1038,   760, -1699, -1699, -1699,    29,   909,
    1451, -1699, -1699,  1699, -1699,  1567, -1699,   119,  1111,  1626,
    1565, -1699, -1699,  1572, -1699, -1699, -1699,  1648,  4258,   538,
   -1699, -1699, -1699,  2979, -1699,  1438, -1699, -1699, -1699, -1699,
   -1699,    89, -1699, -1699, -1699,  1158, -1699, -1699, -1699,  1193,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699,  1516,  1193, -1699,
    1449, -1699,  1801, -1699, -1699, -1699,   875, -1699,   646,   958,
   -1699,   157,    40,   871,    80,    80,  4258,   546,  1159,   918,
    1716, -1699, -1699,  1844, -1699,  1677, -1699, -1699, -1699, -1699,
    1590, -1699,  1038,   112,    34,   910,  1422,  1733, -1699,  1425,
     646,   734, -1699,   398, -1699, -1699, -1699,  4418,  1236,    34,
   -1699, -1699, -1699, -1699,  -105,  1038,  4258,   549,  1460,  1850,
    1038,   476, -1699, -1699, -1699,  1559,  1560, -1699, -1699,   895,
   -1699,    95,   741, -1699, -1699, -1699,  1236,  1692, -1699, -1699,
    1269, -1699, -1699,  1236, -1699, -1699, -1699, -1699,  1549,  1168,
    1236,   743, -1699, -1699,  1549, -1699,  1269, -1699, -1699, -1699,
   -1699, -1699,  1038, -1699,  1038, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699,  1038,  1666,   871, -1699,  1203, -1699,
   -1699,   859,   846,   846,  1365,  1365,  1365, -1699,  1266,  1471,
   -1699,  1038, -1699,  1572, -1699, -1699,  1626, -1699, -1699, -1699,
    1236, -1699, -1699,  1236, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699,    99, -1699, -1699, -1699,  1987, -1699, -1699, -1699,   387,
     387,   387, -1699, -1699, -1699, -1699, -1699,  1267,  1389,  4961,
   -1699,  1038,  1267,  1267,  2354, -1699,  1267,  1267,  1267,   426,
    1267,  1267, -1699, -1699,  1609,  4258, -1699,    80, -1699, -1699,
      75,   471, -1699, -1699,  1876, -1699,   614,    42, -1699, -1699,
   -1699, -1699,  1084, -1699,  1547, -1699,  1542, -1699, -1699, -1699,
   -1699, -1699, -1699,   -91,   -91,   -91,   -91,  1236, -1699, -1699,
   -1699, -1699,  1209,  1236, -1699, -1699, -1699, -1699,   133, -1699,
    1111, -1699, -1699, -1699, -1699, -1699, -1699,  4418, -1699,  4418,
      89, -1699, -1699, -1699,  2979, -1699,  1038,  1761,  1455,   853,
    1779,  1458,   659,   646, -1699, -1699,  1839, -1699, -1699, -1699,
   -1699,   958, -1699,  1717, -1699,  1236,  1610, -1699, -1699, -1699,
   -1699,  1404,    80, -1699,  4418,   172,   696, -1699, -1699, -1699,
    1038,  4418,   658, -1699, -1699, -1699,  1753,  1634, -1699,  1754,
   -1699,  1660, -1699, -1699, -1699, -1699,  1425, -1699, -1699, -1699,
    1638,  1756,  1614,  1605,  1389, -1699,  4418,   659, -1699,  1622,
   -1699,   646, -1699,  1792,  1514, -1699, -1699,  1158, -1699,   825,
    1897, -1699,  1052, -1699, -1699, -1699,  1269,  1793,  1689,  1841,
    4852,   -64,  1236, -1699, -1699,   -64, -1699,  1236,  1303, -1699,
   -1699, -1699,  1714, -1699,  1404, -1699,  1236, -1699, -1699, -1699,
   -1699,   -64,   -64,   110,   110, -1699, -1699, -1699, -1699, -1699,
    1451, -1699,  1280, -1699, -1699, -1699,   859, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,  1193,
    1755,  1193,  1758, -1699, -1699,  4418, -1699, -1699, -1699, -1699,
   -1699,  1783, -1699, -1699, -1699, -1699, -1699, -1699,  1626,  1626,
    1626,  1626,   -64, -1699, -1699,   -64,   110,   110, -1699, -1699,
   -1699,  4258,  1591,  4258,  1593, -1699, -1699, -1699, -1699, -1699,
    1780, -1699,   853, -1699,  1813, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699,   659,   895, -1699, -1699,   895,   -68,  1038, -1699,
   -1699,  4258, -1699, -1699,   928,  3513, -1699,  1868,  1684,  1705,
     486, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699,  1038,   599, -1699, -1699, -1699,  1781,
    1664,  1038,  1451,  4258, -1699,  1850, -1699,  1387,  1828,  1387,
    1614,   192, -1699, -1699,  1777, -1699,  1665, -1699, -1699, -1699,
     507, -1699, -1699,  1236,  1837,  1711, -1699,  1082, -1699,  1730,
    1114,  1507,  1743,  1500,  1236,  1385,  1236,  1038, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
    1548, -1699, -1699, -1699, -1699,    -2, -1699, -1699, -1699, -1699,
   -1699, -1699,   465, -1699,   592, -1699,  1498,  1236,   120, -1699,
   -1699, -1699,   -64, -1699, -1699, -1699, -1699, -1699, -1699,  1193,
   -1699,  1193, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699,  4418, -1699,  4418,
   -1699, -1699, -1699, -1699, -1699,  1886,   895,   895, -1699,  1535,
    1635,   918,   674, -1699,  1038, -1699, -1699,  1601,  4418, -1699,
    1236,   861,  1702, -1699,  1706, -1699, -1699, -1699, -1699, -1699,
   -1699,  1038, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699,  1038,  1387, -1699,  1038,
    1797, -1699, -1699, -1699, -1699, -1699,   918, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699,  1160,  1269,  1236,  1236,  1772, -1699,
    1236, -1699, -1699, -1699, -1699,   559, -1699,  1236, -1699,  1038,
    1038,   983,  1768, -1699,  1667,  1269,    -2, -1699, -1699, -1699,
   -1699, -1699, -1699,   -64, -1699, -1699, -1699, -1699,   -64, -1699,
    1498, -1699,  1038, -1699,  1160, -1699, -1699, -1699, -1699,  1451,
    1451, -1699,  4418,   895, -1699,  4418,  1236,   918,   918,  1643,
   -1699, -1699, -1699,  1529,  1038,  1810, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699,  1038, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699,  1269,  1269,  1236, -1699,  1269,
   -1699,  1269, -1699,  1389, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699,  4418, -1699, -1699, -1699, -1699, -1699,
   -1699,  1038, -1699, -1699, -1699, -1699, -1699,   336,   918,  1236,
   -1699,  1038, -1699, -1699, -1699, -1699, -1699, -1699,  1269, -1699,
   -1699, -1699,  1899, -1699,   336, -1699, -1699,  4418, -1699, -1699
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1699, -1699, -1699, -1699,  1947, -1699, -1699, -1699,    70, -1699,
   -1699, -1699, -1699, -1699,  1616, -1699, -1699, -1699,  1200, -1699,
   -1699,    65,  1934, -1699, -1699,  1904,   211, -1699, -1699, -1699,
   -1699, -1699,  1773,  1832, -1699, -1699,  1794,   710, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699,  1785, -1699, -1699, -1699, -1699,
    1760, -1699, -1699, -1699, -1699, -1699,  -191,   668, -1699, -1699,
   -1699, -1699,  1477, -1699, -1699,  1403,   848, -1699, -1699, -1699,
   -1699, -1699, -1699,  1546, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699,  1840, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699,   644, -1699,   640,
     855, -1699, -1699, -1699, -1699, -1699,  1049,   128, -1699,  1405,
   -1699, -1699, -1699, -1699, -1699, -1699,   176, -1699,  1764, -1699,
    1878, -1699, -1699, -1699, -1699,  1611, -1699, -1699,   180, -1699,
   -1699, -1699, -1699,  1765, -1699,  1939,  1838, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699,  1137, -1699, -1699, -1699,  1437,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699,   691, -1699, -1699, -1699,  1694, -1699, -1699,  -540,
   -1699, -1699,  -292, -1699, -1699, -1699,  -239, -1699, -1699, -1699,
   -1699, -1699, -1699, -1304, -1284,  1169, -1279,   143, -1699, -1699,
   -1699, -1699,   358, -1699, -1699,  -194, -1273, -1699, -1699, -1271,
   -1699, -1270, -1699, -1699, -1699,  1164, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699,  1473, -1699, -1699,
   -1699,  1070, -1699,  -895, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699,   -35, -1699, -1699, -1699, -1699, -1699, -1699,  -169, -1699,
   -1699, -1699, -1699,   306, -1699, -1699, -1699, -1699, -1699,  1215,
   -1699, -1699, -1699, -1699, -1699, -1699,   643, -1699, -1699, -1699,
   -1699, -1699,  1902,  1053, -1699,   296, -1699, -1699, -1699, -1699,
    1553, -1699, -1699, -1699, -1699, -1699, -1699, -1141, -1699, -1699,
     218, -1699, -1699, -1699, -1699,   997,   642,   650, -1699, -1699,
     344, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699,   994, -1699, -1699,   308,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
    -135, -1699,   274, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699,   791, -1699, -1699,   795, -1699, -1699, -1699,
   -1699,   535,   267, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,    98,
     796, -1699, -1699, -1699, -1699, -1699, -1699, -1699,   798, -1699,
   -1699, -1699,   258, -1699, -1699,   516, -1699, -1699, -1699, -1575,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1077,   980, -1699, -1699,   248, -1699, -1699,   499, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
     738, -1699, -1699, -1699, -1699, -1699, -1699, -1699,   768, -1699,
     239, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699,   970, -1699,   971, -1699, -1699,  1172, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699,   963,   480, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699,    79, -1699,   482,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699, -1699,  -822,
   -1699, -1117, -1699, -1699, -1122, -1185, -1019, -1699,   412, -1699,
   -1238, -1699, -1699, -1699, -1699,    81, -1699, -1699, -1699, -1699,
     -45, -1699, -1699,   260, -1699, -1699, -1699, -1699,    62, -1699,
   -1291, -1698, -1699, -1699,   595, -1699,  -809, -1260,  -843, -1177,
   -1699, -1699, -1699, -1188, -1183, -1170, -1169, -1168,    58,  -226,
    -126,  -185, -1119,  -854,  -640,   996, -1011,   -84, -1699, -1065,
   -1699,  -788, -1699,   877,  -391,  -183, -1699,  -636,  1416,  -828,
   -1004,   130,  -781, -1699, -1699,   510, -1047, -1627,  -979,  -824,
   -1035,   685,  -600,  -220, -1699,  1131,  -235,  -646,  -496,  -295,
    -751,  -892, -1699, -1699, -1699, -1699, -1699,  1852, -1699,   491,
     889, -1699, -1699, -1699, -1637,  1259,    64,  1786,   832,  -428,
   -1699,  1059,  -388,  1511, -1699,  -610, -1699, -1081,  1139,  -400,
     612, -1699, -1699,  -688, -1699, -1132,  -168,  -538,  -504,   -99,
    -604,   716, -1338,  -820, -1070, -1699,  1309,  2050,  -509, -1699,
   -1699, -1699, -1699, -1699, -1699, -1699,   677, -1699,   244,  -686,
    1143,  -127
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1563
static const yytype_int16 yytable[] =
{
     121,   246,   288,   457,   187,   456,   878,   658,   589,  1113,
     841,   341,   846,   535,  1025,   389,  1552,  1225,  1462,   969,
    1009,   265,   266,  1463,   824,  1309,   271,   272,   273,   274,
     275,  1041,   277,   910,   280,  1300,  1464,  1465,  1466,   287,
    1636,  1018,  1212,  1293,  1247,  1494,  1495,  1496,  1690,  1691,
    1325,   288,  1247,   852,  1056,   288,   803,   288,   427,   187,
    1637,  1890,  1505,  1238,   552,  1638,   288,  1102,   331,   121,
     332,  1639,   782,  1640,  1641,  1047,  1013,   339,    22,  1047,
    1415,  1003,  1047,  1596,  1047,   344,  1047,  1351,   356,   431,
    1003,  1035,   360,   105,   362,   974, -1526,   409,  1247,   353,
     354,  1351,   355,   373,   415,  1067,  1069,  1196,   361,   158,
    1500,  1382,  1086,   847,  1020, -1562,   366,  1498,  1351,  1109,
    1003,   569,   289,   477,   288,  1351,   158,  1916,  1368,   837,
     427, -1486,  -189,  1062,   288,  2110,  1531,    92,  1020,   105,
      89,   288,   584,   391,    54, -1490,   396,   398,  1546,   401,
      85,  2018,   442,   126,   932,   453,   278,  1338,  1390,   158,
    -190,   416,   464,  1559,  1179,   410,  1351,   660,   340,  1186,
    1515,   428,  1306, -1562,   288,   472,   288,   461,   430,   837,
   -1526,   796,   417,  1532, -1513,   158,   960,  1328,   586,   667,
   -1562,   407,  1543,    41,  1301,   384,  1586,  2002,   846,   497,
     571,   291,   898,  1385,  1158,    32,   376,  1530,   179,   536,
    2004,   287,   241,  1743,  1328,   585,  1090,  1883,  1966,   251,
     838,  1201,    18,   458,   455,    19,   254,  1246,  1909,   941,
     340,    55,   466,  1124, -1403,  1814,  1796,   288,  1061,  1589,
     346, -1562,  1737,  1481,  1339,  1117,   498,    14,    41,  -189,
    1201,  1936,  2184,  1085, -1562,  1667,   942,   943,   158,   384,
    1768,   572,  1687,  1287,   854,   347,   803,   408,     3,  1588,
    1298,  1121,  1118,  1819,   373,  1644,   432,  -190,   590,    12,
    1862,   470,    91,   544,  1263,  1351,  1867,   309,  1831,   955,
     376,  1012,  2185,   446,  1247,  1482,  1661,  1533,  1715,  1326,
      20,    13,   556,   557,  1762,  1561,  1012,   167,  1803,  1328,
     574,   418,   659,  1091,   899,    56,   664,  1391,   106,   586,
    1797,   242,  1254,  1020,   459,  1307,  1109,  1168,  1347,  1666,
     183,  1201,   573,   310,  1505,  2108,   669,   669,  1169,  1170,
   -1533,   581, -1490,   221,  1488,  1025,  1534,   311,  1835,  1351,
    1125,  1663,   419, -1502,  1910,  2151,   920,   804,  1663,   420,
    2111,   418,  1917,  1091,   106,  1663,  1171,   593,  1164,  1165,
    1815,  1775,   285,  1352,   653,    63,  1480,  1777,  2058,    41,
   -1490,   285,  1025,  2106,   823,   312,  2107,  1352,   591,    55,
    1727,   839,   340,   285,    63,  2152,  1385, -1490,  1158,  1158,
    1158,  1041,   419,  2153,  1352,   826,  1141,   781,  1158,   420,
   -1513,  1352,   786,  1025,  1716,   790,   107,   791,  1416,  1744,
     793,   794,  1746,  2227,   800,  1467,     4,   661,   797,  1158,
     421,  1158,   -31,  1158,  1387,  1402,  1545,  1158,  1158,  1158,
    1158,  1158,  1158,  1158,  1158,  1776,   183,   170,   285,   255,
   -1508,   975,  1352,  -189,  1497,  1499, -1490,   944,   263,  1157,
    1517,  1025,   107,   385, -1488,   835,   831,   832, -1508,  1353,
   -1508,  1918,  -612,    56,  1302,  2154,  1571,  1907,  1239,   257,
     421,  -190,  1850,  1697,    89,   798,  1547, -1486,  1501, -1490,
    1556,  1786,  1502,   422,  1303,   285,    41,  1351,   551,   570,
   -1442,   313,   263,  1329,   478,   285, -1490,  1707,   183,   285,
     285,   950,   285,   314,   285,   252,   285,  1884,   183,   168,
     145,  1576,   423,  1827,    86,  1580,  1581,   388,  1583, -1490,
    1329,   285,  1535,  2213,  1587,  1365,   853,  1598,  1806,   285,
     567,  1247,   966,   422,  1880,  -610, -1490,   921,  1708, -1562,
     471,  1937, -1490,     5,   285,  1745,  2039,  1255,   928,    64,
    1386,  1131,   424,  1025,  1991, -1490,  1364,   804,  1012, -1562,
     288,  1352,   423,   288,   288,  1286,  2040,  1172,    64,  1393,
     288,  2041,   431,    75,  1472,  -612,  1400,  2043,    16,  2044,
    2045,    23,   925,  1505,  1295,   922,  1649,  1926,  1927,  1235,
     315,   316,  1342,  1158,  1158,  1158,  1158,  1158,  1158,  1158,
     934,   935,   424,   317,   924,   318,  2291,   940,   945,  1211,
    1256,  1091,   978,  1939,  1911,  1329,  -207,  1387,   118,    65,
    1694,   169,  1947, -1562,   949,  1352, -1533,   168, -1490,    88,
    1132, -1450, -1450,  1727,  1016,  1900,  1514,  1663,  1941,   480,
    1943,   836,  2074,  1157,  1157,  1157,   783,   809,  -610,  1355,
    1356,  1357,  1358,  1157,  1359,  1064,   475, -1448,   837,  1079,
    1333,  1083,  -756,  1083,  1089,  1166,  1064,  1659,  1567,  1295,
    2122,  1723,  1567,    52,  1157,  1971,  1157,   929,  1157,  2170,
    1401,  1083,  1157,  1157,  1157,  1157,  1157,  1157,  1157,  1157,
     784,    75,    29,  2096,   288,  2098,   810,  1127,  2189,   469,
    1886,  1887,  1888,  1908,   170,   319,  1802,  2003,  1145,   481,
     288,  1769,  2123,  1355,  1356,  1357,  1358,     4,  1359,  1804,
    1593, -1446,  1836,  2115,  1594,   320,  1961,  1473,  1161,   340,
    1718,  1123,  2124,  2087,  2088,  2089,  2090,  1647,   183,   169,
    1912,  1091,  1426,  1427,   288,   288,  1236,  1134,  1295,  2190,
     482,  1660,  1080,  2076,  2143,  2144,   930,   483,    30,   432,
    1154, -1562,   285,  1136,  1560,  1299,  1334,  2011,   926,   484,
    1428,  1519,  2086,  1352,  1520,  1027,  1429,  1521,  1522,  1487,
    1734,  2066,  1696,  1175,  2006,  2162,  1829,  1866,  1247,  2095,
     828,    26,  2072,  2072,  1488,  1889,  1081,  2132,  1084,     5,
    1894,  1895,  2133,  1104,  1897,  1898,  1899,  1431,  1902,  1903,
    1295,  1432,  1115,   285,   985,  2134,  2135,  2136, -1486,  1153,
    2063,  1901,  1221,  1778,   285,  2194,     5,   418,   485,   987,
    2126,  2127,  1781,   594,   847,   247,  2069,  2070,   238,  2129,
     418,  1648, -1562,  1978,     5,  2072,  2072,  2218,  1157,  1157,
    1157,  1157,  1157,  1157,  1157,  1520,  1089,   301,  1521,  1522,
    1020,  1355,  1356,  1357,  1358,  2146,  1359,  2149,   419, -1443,
    1295,  1221,   168,   250,  1531,   420,  2195,   338,  1914,  1221,
     168,   419,  1221,   239, -1562,    45,   811,  2091,   420,  1799,
    2092,   486,   370,  1557,   487,   488,  1341,   502,  2191,  2192,
     503,   183,   285,  1942, -1562,  1944,    33,  2125,  2252,   294,
    1730,   829,   390,   988,   300,   504,    34,   397,  1946,  1252,
    1558,  1532, -1562,    46,   855,   505,  2205, -1486,  1214,  1176,
     405,    47,   813,   285,  2208,   812,    75,  1080,  1158,  2058,
    1025,   288, -1562,  1158,    75,  2163,   421,  2219,   250,  2211,
     406, -1502,    38,  1335,  1154,  1154,  1154,  1787,   251,   421,
     489,  2273,  2274,  1696,  1154,  1017,  2012,   991,   371,  1989,
     992,   238,  1025,  1800,  1814,  2164,   379,  2230,  1852,  2231,
   -1504,   814, -1486, -1562,   169,  1154,  2232,  1154,  1268,  1154,
    2156,  1031,   169,  1154,  1154,  1154,  1154,  1154,  1154,  1154,
    1154,   815,   993, -1562,  1788,  2235,  2239,  2240,  1131,   422,
    2295,  1523,  1524,  1348,  1349,  1350,   239,   833,  1016,   291,
    1977,  1112,   422,  1361,  1481,  2196,  2197,  2204,  1269,  1525,
    1526,   908,  1295,  1295,  1731,  1533,  1270,   834,   423,  1446,
    1611, -1508,  1448,  1449,  1187,  1853,  1397,  1854,  1016, -1486,
     816,   423,  1404,  1406,  1407,  1409,  -970,  1281,  1412,  1414,
    1481,   447,  2256,  2257,  1295,  2073,  1475,    41,   506,  1208,
     994,  1037,   285,  -207,  2013,  1038,  1482,  1479,   424, -1562,
     249,   817,  2284,   183,  1534,   285,  2258,  1132,   342,  2131,
    2217,   424,  1523,  1524,   506,  1016,   141,  -970,   984,   507,
     183,   837,  1282,  1795,  -970,    36,   288,   288,  1271,  1815,
    1525,  1526,  1482,    50,   260,   995,   996,  2093,  2094,  1042,
    1043,   183,   118,  1574,  2082,   507,  1960,  1575,  1276,   837,
     818,   446,   508,  1044,  1747,  1735,  1820,  1748,    44,   418,
     997,  1277,    93,  1604,  1604,  1749,  1750,  1751,  2268,    61,
    1565,   142,   143,  2269,  2116,  1736,  1821,  1476,   998,  1154,
    1154,  1154,  1154,  1154,  1154,  1154,   999,  1789,  1701,   285,
     392,  1704,   393,   985,  2117,  -970,  1709,   509,    49,  1045,
     419,  1960,   183,   510,   787,   188,   481,   420,   987,  1565,
    2293,   788,    10,  1157,    53,   418,    10,  2278,  1157,   189,
     190,   985,   237,    59,    94,  2180,   237,  2298,    60,   575,
     511,   912,    62,  2078,   580,  2080,   987,   512,  1651,  1652,
    1653,  1654,  1655,  1656,  1658,  -332,  -332,   482,  1394,   514,
     513,   191,  1398,  2209,   483,  2210,   419,     5,  -970,  1016,
    1410,  1411,    68,   420,    95,  1217,    96,    72,  1355,  1356,
    1357,  1358,   913,  1359,   252,   514,  1752,   515,   421,   914,
    1360,    75,  2259,  2260,   435,   516,   436,  -970,   192,   193,
    1535,   194,   988,    79,  1753,  -212,  1317,  1295,  1318,   195,
      81,  1357,  1358,   418,  1359,  1295,  1239,  1970,  1508,   303,
     304,  1754,  1355,  1356,  1357,  1358,   517,  1359,  1608,  1609,
     988,  -970,    82,  2261,  2262,   485,  1960,  -970,  1863,   103,
    1864,   418,   114,   989,   421, -1395, -1395, -1395, -1395,  2281,
     990,   422,   196,   197,   419,   115,   991,  2223,   116,   992,
     915,   420,   188,   198,  1919,  1295,  1920,  1688,  2169,  1755,
    1229,  1230,  1231,  1232,   118,   518,   189,   190,   124,  1933,
     423,  1934,   419,  1790,   991,   128,  1853,   992,  1854,   420,
    2067,   993,   129,   984,   130,  1859,   837,   133,   486,  2173,
    2174,   288, -1394, -1394, -1394, -1394,   131,   422,   191,  2241,
    2242,  1868,   132,  2206,   285,  2207,  1756,  1175,   135,   993,
     424,   136,   139,   916,   138,   148,   149,  1421,  1422,  1423,
    1830,   150,   421,   164,   165,  1424,   423,   199,  1604,  1369,
    1370,  1805,  2203,   166,   288,   192,   193,   179,   194,   217,
     220,  2275, -1486,   221,  2276,   223,   195,   225,  1856,   994,
     421,   288,   229,   230,   231,  1861,    41,   489,   985,  1757,
     245,   262,  1865,  1425,   263,   259,   424,  1833,   269,  1758,
    1371,  1871,  1372,   987,  1833,   268,   278,   994,  1355,  1356,
    1357,  1358,   917,  1359,   285,   422,  1650,   289,  1878,   196,
     197,   288,   291,  2292,   995,   996,  1355,  1356,  1357,  1358,
     198,  1359,   297,   296,  1373,  1374,  1375,   334,  1699,   333,
     298,   340,  1881,   422,   423,  1882,   336,   343,   345,   997,
     348,   357,   995,   996,  1154,   349,  2299,   381,  1893,  1154,
    1759,  1355,  1356,  1357,  1358,   382,  1359,   998,   399,  1703,
     402,   200,   423,   404,   411,   999,   412,   997,   285,   429,
     444,  1376,   449,  1377,   424,  -349,   982,   988,  1426,  1427,
    1019,  1378,  1218,   451,   454,   998,  1033,   465,   418,   467,
     495,  1050,  1051,   999,   199,   499,   285,  1050,  1058,  1060,
     537,   201,   424,  1892,  1019,   545,  1428,   547,  1896,  1932,
    1050,   549,  1429,   553,   555,  1935,   576,   579,   989,  1058,
    1114,   577,  1116,   582,   183,   990, -1486,   592,   655,   419,
     665,   991,   657,   673,   992,  1430,   420,   267,  1928,  1929,
    1930,  1931,   672,  1431,   792,   276,   777,  1432,   586,   801,
     202,  2022,   303,   808,  1379,   821,   819,  1968,   858,   827,
     859,  -822,   584,   281,   283,   902,   993,  2250,  1091,   933,
    1156,   936,   939,  2176,   952,   953,   958,  1433,  1434,   955,
     961,   963,  1435,  1355,  1356,  1357,  1358,   967,  1359,   970,
     973,  1706,  1436, -1486,   976,  1355,  1356,  1357,  1358,  1437,
    1359,  1181,   979,  1711,  1438,   980,  1007,   421,   200,  1974,
    1036,   351,   352,  1053,  1120,  1980,  1028,  1122,  1128,   358,
     359,  1159,  1439,  1137,  2062,   365,   368,  1143,  1162,  2064,
    1146,   847,  1173,  1202,   994,  1204,  1213,  1197,  2068,  1355,
    1356,  1357,  1358,  1207,  1359,  1215,  1180,  1875,   201,  1182,
    1184,  1209,   446,  1355,  1356,  1357,  1358,  1188,  1359,  1189,
    1190,  2075,  1221,  1050,  1191,  1223,  1226,  1192,  1233,  1193,
     422,  1050,  1253,  1194,  1195,  1245,  1249,  1264,   288,   995,
     996,  1265,  1267, -1397,  1274,  1278,  1280,  1284,  1279,  1019,
    1289,  1091,  1291,   158,  1313,  1316,  1320,   202,  1322,   423,
    1345,  1323,  1362,  1366,   997,  1294,  1383,  1396,  1403,  1417,
     433,  1418,  1468,  1050,  1012,  2113,  1491,  1050,  1544,  1506,
    1380,  1548,   998,  1529,  1511,  1312,  1562,  1577,  1253,  1570,
     999,  1578,  1600,   285,  1585,  1590,  1602,  1606,  1665,   424,
    1664,  2271,  1668,  1359,  1688,  1386,  1717,  1719,  1722,  1712,
    2188,  1213,  1700,  1702,  1058,  1705,  1710,  1740,  1482,  1763,
    1381,  1767,  1765,  1771,  1156,  1156,  1156,  1440,  1441,  1442,
    1443,  1444,  1779,  1445,  1156,  1446,  1447,  1782,  1448,  1449,
    1783,  1807,  1810,  1811,  1822,  2165,  1823,  1824,  1837,  1838,
    1294,  1846,  1857,  1848,  1872,  1156,  2179,  1156,  2181,  1156,
    1876,  1924,  1905,  1156,  1156,  1156,  1156,  1156,  1156,  1156,
    1156,  1925,  -779,  1949,  1951,  -779,  1955,  1957,  1962,  1965,
    1969,  1983,  1815,  1986,  2221,  1993,  1988,  1996,  1998,  2202,
    2001,  2005,  2007,  2009,  2019,  2024,  2023,  2026,  2079,  2083,
     880,  2081,  2104,  2101,  2097,  -913,  2099,  2118,  -913,  2120,
    2119,  2147,  2159,  2138,  2013,   158,  2140,  2166,  2167,  2171,
    2244,  2177,  2178,  2035,  2199,  2212,  2214,  2216,  2228,  1294,
    2222,  2237,  2229,  2247,  2264,  2279,  2280,  2282,  2297,  1050,
    2266,  2188,  2224,    15,   414,  2265,    28,  -779,    74,   261,
     288, -1490,  1555,   186,   282,   248,   258,  1572,   568,  1213,
    1327,   494,  -779,   779,  1601,   219,  1568,  1605,  1330,  1130,
    2021,  1972,   288,  1050,   284,   443,   789,   146,    67,   780,
    -913,   233,   293,   977,   670,  1584,   383,  2255,  2245,  2246,
     959,  1294,  2249,  2042,  1874,  -913,  2270,  1592,   972,  2251,
    2286,  2287,   595,  1140,  2289,  2183,  2290,  2267,  1669,   287,
    1670,   951,  1915,  1671,  1253,   163,   558,  1975,  1228,  1885,
    1237,  1693,  1913,  1672,  1938,  1513,  1509,  1945,  1692,  1156,
    1156,  1156,  1156,  1156,  1156,  1156,  1774,  1528,  2277,  1964,
    2103,   288,  1784,  2296,  1273,  1540,  -779,  1016,  1976,  1812,
    1569,  1294,  -913,  -913,  1599,  1992,  1296,  -779,  1103,  1297,
    1311,  1844,   446,  1845,  1016,  1879,  2226,  1985,  2161,  2288,
    1742,  1698,  1288,  1828,  2145,  1470,   302,  1160,   373,  -913,
    -913,  2150,  1851,  1420,  1542,   965,  -913,  -779,  1244,   395,
    -913,   795,  1163,  1050,  -779,  2272,   938,    76,  -779,  1721,
    -779,  2294,  2065,  -779,  1167,  -779,     0,     0,     0,  -913,
       0,     0,     0,     0,     0,     0,     0,  -913,     0,     0,
    -913,  -913,     0,   446,     0,     0,     0,  -913,     0,     0,
       0,  -913,     0,  -913,     0,  -779,  -913,     0,  -913,     0,
    -779,     0,     0,     0,     0,     0,     0,  1728,  1729,     0,
    1673,  -913,     0,     0,  1674,     0,  -913,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1675,  -913,     0,
     985,     0,     0,     0,     0,     0,  -779,     0,     0,     0,
       0,     0,     0,     0,   446,   987, -1490,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -779,     0,     0,     0,     0,     0,  -913,
       0,     0,     0,  1294,  1294,  1676,     0,     0,     0,  1050,
    1050,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -779,     0,     0,  -913,  1813,     0,  -779,
       0,     0,     0,     0,     0,  1294,     0,     0,  -779,  -779,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1834,     0,  1677,     0,     0,  1843,  1843,     0,  -779,   988,
       0,     0,  -913,  -779,     0,     0,     0,     0,  -779,     0,
     418,  -913,  -913,     0,     0,     0,  1678,     0,     0,     0,
       0,  -779,     0,     0,     0, -1490,  1019,     0,     0,  -779,
       0,  -913,  -779,     0,     0,     0,  -913,  1869,  -779,  1870,
    1679,     0,     0,     0,     0,  1680,     0,     0,     0,     0,
       0,   419,     0,   991,  -913,  1681,   992,     0,   420,  1682,
     985,     0,  -913,     0,     0,  -913,     0,     0,     0,     0,
       0,  -913,  -913,  -913,     0,   987,     0,  -913,     0,  -913,
       0,  -913,  -913,  -913,     0,     0,     0,     0,   993,     0,
       0,     0,     0,     0,  1213,  1213,  1213,     0,     0,  -344,
     597,     0,     0,     0,  1156,     0,     0,     0,     0,  1156,
       0,     0,     0,     0,     0,     0,  1683,     0,     0,     0,
     598,     0,  1050,     0,     0,     0,  1684,     0,     0,   421,
       0,     0,     0,   599,     0,     0,   600,   601,   602,   603,
     604,   605,   606,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1071,     0,   985,   994,     0,     0,   988,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     987,     0,   607,     0,   608,   609,   610,   611,   612,   613,
       0,  1948,     0,     0,     0,     0,     0,  1959,  1294,     0,
       0,     0,   422,     0,     0,     0,  1294,     0,     0,     0,
       0,   995,   996,     0,     0,     0,     0,  1050,     0,     0,
       0,  1072,     0,   991,   614,  1555,   992,     0,     0,     0,
       0,   423,     0,     0,     0,     0,   997,     0,     0,     0,
       0,  -344,     0,     0,     0,  -344,     0,     0,     0,     0,
       0,     0,  1959,     0,   998,     0,  1294,     0,   993,     0,
       0,     0,   999,     0,   988,   285,     0,     0,     0,     0,
       0,   424,     0, -1508,  -344,   418,  2060,     0,     0,     0,
    2060,     0,     0,     0,     0,     0,     0,     0,  -344,     0,
       0,     0,     0, -1508,     0,     0,  2060,  2060,     0,     0,
       0,     0,     0,     0,     0,  1148,   615,     0,     0,     0,
       0,     0,   990,     0,     0,     0,   419,     0,   991,    41,
       0,   992,   616,   420,     0,     0,   994,     0, -1543,     0,
       0,     0,  -344,  -344,     0,     0,     0,     0,     0,     0,
    -344,   617,     0,     0,  -344,     0,     0,  2060,     0,     0,
    2060,     0,     0,   993,     0,     0,     0,     0,   618,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   995,   996,     0,     0,     0,     0,  1959,     0,     0,
     619, -1562,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   421,   620,   997,     0,     0,     0,
       0,     0,   621,     0,   622,     0, -1021,     0,     0,  1058,
       0,  -344,     0,     0,   998,  -344,  2142,   623,     0, -1021,
       0,   994,   999,     0,   183,   285,     0,   624,     0,     0,
       0,     0,     0,     0,   625,  2060,  -344,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2182,     0,     0,  -344,     0,   422,  -344,  -607,
     559,     0,  -647,     0,  -647,     0,   995,   996,     0,  -647,
       0,   626,     0,   627,   628,   629,     0,  -647,     0,     0,
       0,     0,     0,     0,     0,     0,   423,  2060,     0,     0,
       0,   997,     0,     0,     0,     0,     0,   630,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   998,
    -647,  -647,     0,     0, -1543,     0,     0,   999,  -647,     0,
     285,     0,   631,   632,   633,     0,   424,  1149,  1150,  -647,
       0,     0,     0,  -647,     0,   634,  1151,     0,   635,     0,
       0,     0,     0,     0,     0,  -647,  1253,  -344,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -344,     0,
       0,  2234,     0,     0,  2236,     0,     0,  -647,     0,     0,
       0,     0,     0,     0,  -647,  -647,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -607,     0,     0,  2253,  -607,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -647,     0,     0,  2060,     0,
       0,     0,     0,  2060,     0,     0,     0,  -647,     0,     0,
       0,  -647,     0,     0,     0,     0,   559,     0,  -647,     0,
    -647,     0,     0,     0,  -647,  -647,     0,     0,  -607,  1058,
       0,  -647,     0,  -647,  -647,  -647,     0,     0,     0,     0,
    2285,     0,  -647,     0,     0,     0,     0,     0,     0,  -647,
       0,  -647,     0,     0,  -647,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -647,  -647,     0,     0,
       0,     0,     0,     0,  -647,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -647,  1253,     0,     0,  -647,
       0,  -647,     0,     0,     0,  -647,     0,  -647,     0,     0,
       0,  -647,     0,     0,  -647, -1478,     0,     0, -1478,     0,
       0,     0,     0,     0,     0,     0,  1238,     0,     0,     0,
   -1478,     0,     0,  -647,     0,     0,  -647,     0,     0,     0,
    -647,  -647,     0,     0,     0,     0,     0,     0,   671,     0,
       0,  -647,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -607,     0,     0,     0,     0,
       0,  -647,  -647,     0,     0,     0,     0,     0,     0,     0,
       0,  -647,     0,  -647,     0,     0,     0,  -647,     0,     0,
   -1478,     0,     0,     0,  -647,     0,     0,     0,     0,  -647,
    -647,  -647,     0,     0,     0, -1478,     0,  -647,     0,  -647,
    -647,  -647,     0,     0,     0,     0,     0,     0,  -647,  -647,
       0,     0,     0,     0,     0,  -647,     0,  -647,  -647,     0,
    -647,     0,     0,     0,     0,     0,     0,  -647,     0,  -647,
    -647,     0,     0,  -647,     0,  -647,     0,     0,     0,     0,
    -647,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0, -1478, -1478,     0,  -647,     0,  -647,     0,     0,
    -647,  -647,     0,  -647,   984,  -647,     0,   837,     0,     0,
    -647,     0,     0,     0,     0,     0,  -647,     0,     0, -1478,
   -1478,     0,     0,     0,     0,   560, -1478,     0,  -647,     0,
   -1478,     0,  -647,     0,     0,     0,     0,     0,  -647,     0,
       0,     0,     0,     0,     0,     0,     0,  -647,     0, -1478,
       0,     0,     0,     0,     0,     0,     0, -1478,     0,     0,
   -1478, -1478,     0,     0,     0,     0,     0, -1478,  -647,     0,
       0, -1478,     0, -1478,     0,     0, -1478,  -647, -1478,   985,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -647, -1478,     0,     0,   987,  -647, -1478,  -647,     0,     0,
       0,     0,     0,     0,     0,  -647,     0,     0, -1478,     0,
       0,     0,     0,     0,     0,  -647,     0,     0,     0,     0,
       0,     0,     0,     0,  -647,     0,     0,     0,     0,     0,
       0,     0,     0,  -647,     0,  -647,  -647,     0,     0,  -647,
       0,  -647,     0,     0,     0,     0,  -647,     0,     0, -1478,
       0,  1426,  1427,     0,     0,     0,     0,     0,     0,     0,
       0,  -647,     0,     0,     0,     0,  -647,     0,     0,     0,
       0,  -647,     0,     0,     0,     0, -1478,     0,   988,  1428,
       0,     0,  -647,     0,     0,  1429,     0,     0,     0,   418,
       0,   560,     0,     0,  -647,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -647,     0,     0,     0,  1455,     0,
       0,     0, -1478,     0,     0,     0,  1431,     0,     0,   989,
    1432, -1478, -1478,     0,     0,     0,   990,     0,     0,     0,
     419,     0,   991,     0,     0,   992,     0,   420, -1478,     0,
       0, -1478, -1478,     0,     0,     0, -1478,     0,     0,     0,
    1456,     0,     0,     0,     0,  1457,     0,     0,     0,     0,
       0,     0,     0,     0, -1478,     0,     0,   993,     0,     0,
       0,     0, -1478,     0,     0, -1478,     0,     0,     0,     0,
       0, -1478, -1478, -1478,     0,     0,     0, -1478,     0, -1478,
       0, -1478, -1478, -1478,   674,     0,   675,     0,     0,     0,
       0,   676,     0,     0,     0,     0,     0,     0,   421,   677,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   994,     0,     0,     0,     0,
       0,     0,   678,   679,     0,     0,     0,     0,     0,     0,
     680,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   681,     0,     0,     0,   682,     0,     0,     0,     0,
       0,   422,     0,     0,     0,     0,   674,   683,   675,     0,
     995,   996,     0,   676,     0,     0,     0,     0,     0,     0,
       0,   677,     0,     0,     0,     0,     0,     0,     0,   684,
     423,     0,     0,     0,     0,   997,   685,   686,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   998,   678,   679,     0,     0,     0,     0,
       0,   999,   680,     0,   285,     0,     0,   687,     0,     0,
     424,  1458,  1459,   681,     0,     0,  1460,   682,  1446,   688,
    1461,  1448,  1449,   689,     0,     0,     0,     0,     0,   683,
       0,   984,     0,     0,   837,     0,   690,     0,     0,     0,
       0,     0,     0,   691,     0,     0,   692,   693,     0,     0,
       0,   684,     0,     0,   694,     0,     0,     0,   685,   686,
       0,   695,     0,   696,     0,     0,   697,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   687,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   688,     0,   698,     0,   689,   985,   699,     0,   700,
       0,     0,     0,     0,     0,     0,   701,     0,   690,     0,
       0,   987,     0,     0,     0,   691,     0,     0,   692,   693,
       0,     0,     0,     0,     0,     0,   694,     0,   702,     0,
       0,     0,     0,   695,     0,   696,     0,     0,   697,     0,
       0,     0,     0,   703,     0,     0,     0,     0,   984,     0,
       0,   837,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1573,     0,     0,   704,     0,     0,     0,     0,     0,
       0,     0,     0,   705,     0,   698,     0,     0,     0,   699,
       0,   700,     0,     0,     0,     0,   706,     0,   701,     0,
       0,   707,     0,   708,     0,   988,     0,     0,     0,     0,
       0,   709,     0,     0,     0,     0,   418,     0,     0,     0,
     702,   710,     0,     0,     0,     0,     0,     0,     0,     0,
     711,     0,     0,   985,     0,   703,     0,     0,     0,   712,
       0,   713,   714,     0,     0,   715,   989,   716,   987,     0,
       0,   984,   717,   990,   837,     0,   704,   419,     0,   991,
       0,  1106,   992,     0,   420,   705,     0,   718,     0,     0,
       0,     0,   719,     0,     0,     0,     0,   720,   706,     0,
       0,     0,     0,   707,     0,   708,     0,     0,   721,   984,
       0,     0,   837,   709,   993,     0,     0,     0,     0,     0,
     722,     0,     0,   710,     0,     0,     0,     0,     0,     0,
     723,     0,   711,     0,     0,     0,     0,     0,     0,     0,
       0,   712,     0,   713,   714,     0,   985,   715,     0,   716,
       0,     0,   988,     0,   717,   421,   984,   986,     0,   837,
       0,   987,     0,   418,     0,     0,     0,     0,     0,   718,
       0,     0,     0,     0,   719,     0,     0,     0,  1310,   720,
       0,     0,   994,     0,   985,     0,     0,     0,     0,     0,
     721,     0,     0,   989,     0,  1065,     0,     0,     0,   987,
     990,     0,   722,     0,   419,     0,   991,     0,     0,   992,
       0,   420,     0,     0,     0,     0,     0,     0,   422,     0,
       0,     0,     0,     0,     0,     0,     0,   995,   996,     0,
     984,   985,     0,   837,     0,     0,     0,     0,     0,     0,
       0,   993,     0,     0,  1574,   988,   987,   423,  1575,     0,
       0,     0,   997,     0,     0,     0,   418,     0,     0,  1106,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     998,     0,     0,     0,     0,     0,     0,     0,   999,     0,
       0,   285,   421,   988,     0,     0,   989,   424,     0,     0,
       0,     0,     0,   990,   418,     0,     0,   419,     0,   991,
       0,     0,   992,     0,   420,   985,     0,     0,     0,   994,
       0,     0,     0,     0,     0,     0,  1110,     0,     0,     0,
     987,     0,     0,     0,   989,     0,     0,     0,     0,     0,
     988,   990,     0,     0,   993,   419,     0,   991,     0,     0,
     992,   418,   420,     0,     0,   422,     0,     0,     0,     0,
       0,     0,     0,     0,   995,   996,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   989,   993,     0,   423,   421,     0,     0,   990,   997,
       0,     0,   419,     0,   991,     0,     0,   992,     0,   420,
       0,     0,     0,     0,     0,     0,     0,   998,     0,     0,
       0,     0,   994,     0,   988,   999,   984,     0,   285,   837,
       0,     0,     0,   421,   424,   418,     0,     0,     0,   993,
       0,     0,     0,     0,     0,     0,     0,     0,   984,     0,
       0,   837,     0,     0,     0,     0,     0,     0,   422,     0,
     994,     0,     0,     0,     0,   989,     0,   995,   996,     0,
     984,     0,   990,   837,     0,     0,   419,     0,   991,     0,
     421,   992,     0,   420,     0,     0,     0,   423,     0,     0,
       0,     0,   997,     0,     0,     0,   422,     0,     0,     0,
       0,   985,     0,     0,     0,   995,   996,   994,     0,     0,
     998,     0,     0,   993,     0,     0,   987,     0,   999,     0,
       0,   285,     0,   985,     0,   423,     0,   424,     0,     0,
     997,     0,     0,     0,   984,     0,     0,   837,   987,     0,
       0,     0,     0,   422,     0,   985,     0,     0,   998,     0,
       0,     0,   995,   996,   421,     0,   999,     0,     0,   285,
     987,     0,     0,     0,     0,   424,     0,     0,     0,     0,
       0,     0,   423,     0,     0,     0,     0,   997,     0,     0,
       0,   994,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   998,     0,     0,     0,     0,
     988,     0,     0,   999,     0,     0,   285,     0,     0,   985,
       0,   418,   424,     0,     0,     0,     0,   422,  1315,     0,
       0,     0,   988,     0,   987,     0,   995,   996,     0,     0,
       0,     0,     0,   418,     0,     0,     0,     0,     0,     0,
       0,   989,     0,     0,   988,     0,   423,     0,   990,     0,
       0,   997,   419,     0,   991,   418,     0,   992,     0,   420,
       0,     0,     0,   989,     0,     0,     0,     0,     0,   998,
     990,     0,     0,     0,   419,     0,   991,   999,     0,   992,
     285,   420,     0,     0,     0,   989,   424,     0,     0,   993,
       0,     0,   990,     0,   984,     0,   419,   837,   991,     0,
       0,   992,     0,   420,     0,     0,   984,     0,   988,   837,
       0,   993,     0,     0,     0,     0,     0,     0,     0,   418,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     421,     0,     0,   993,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   989,
       0,     0,   421,     0,     0,     0,   990,   994,     0,     0,
     419,     0,   991,     0,     0,   992,     0,   420,     0,   985,
       0,     0,     0,     0,   421,     0,     0,     0,     0,   994,
       0,   985,     0,     0,   987,     0,     0,     0,     0,     0,
       0,     0,     0,   422,     0,     0,   987,   993,     0,     0,
       0,   994,   995,   996,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   422,     0,     0,  1199,     0,
       0,     0,   423,     0,   995,   996,     0,   997,     0,     0,
       0,  1582,     0,     0,     0,     0,     0,   422,   421,     0,
       0,     0,     0,     0,   423,   998,   995,   996,     0,   997,
       0,     0,     0,   999,     0,     0,   285,     0,     0,     0,
       0,     0,   424,     0,     0,   994,   423,   998,   988,     0,
       0,   997,     0,     0,     0,   999,     0,     0,   285,   418,
     988,     0,     0,     0,   424,     0,     0,     0,     0,   998,
       0,   418,     0,     0,     0,     0,  1712,   999,     0,     0,
     285,   422,     0,     0,     0,     0,   424,     0,     0,   989,
     995,   996,     0,     0,     0,     0,   990,     0,     0,     0,
     419,   989,   991,     0,     0,   992,     0,   420,   990,     0,
     423,     0,  1029,     0,   991,   997,     0,   992,     0,   420,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   998,     0,     0,     0,   993,     0,     0,
       0,   999,     0,     0,   285,     0,     0,     0,     0,   993,
     424,     0,  1612,     0,  1613,     0,     0,  1614,   600,   601,
     602,   603,   604,   605,   606,  1615,  1616,  1617,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   421,     0,
       0,     0,     0,     0,     0,     0,  1618,     0,     0,     0,
     421,     0,     0,     0,   607,     0,   608,   609,   610,   611,
     612,   613,     0,     0,     0,   994,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   994,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   614,     0,     0,     0,
       0,   422,     0,     0,     0,     0,     0,     0,     0,     0,
     995,   996,     0,   422,     0,     0,     0,     0,     0,     0,
       0,     0,   995,   996,     0,     0,     0,     0,     0,     0,
     423,     0,     0,     0,     0,   997,  1619,     0,     0,     0,
       0,     0,   423,     0,     0,     0,     0,   997,     0,     0,
       0,     0,     0,   998,  1620,     0,     0,  1621,  1622,     0,
       0,   999,     0,     0,   285,   998,     0,     0,     0,     0,
     424,  1623,     0,   999,     0,     0,   285,     0,   615,     0,
       0,     0,   424,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   616,     0,     0,     0,     0,   600,
     601,   602,   603,   604,   605,   606,     0,     0,     0,     0,
    1624,     0,     0,     0,     0,     0,     0,     0,     0,  1625,
       0,     0,     0,     0,     0,     0,     0,  2027,  2028,     0,
     618,     0,     0,     0,     0,   607,     0,   608,   609,   610,
     611,   612,   613,     0,   600,   601,   602,   603,   604,   605,
       0,     0,  1626,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1627,   620,     0,     0,
       0,     0,     0,     0,   621,     0,   622,   614,     0,     0,
     607,     0,   608,   609,   610,   611,   612,   613,     0,   623,
    1628,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1629,     0,     0,     0,     0,  1630,
       0,     0,   614,     0,   985,     0,     0,     0,     0,     0,
       0,     0,     0,  1631,     0,     0,     0,     0,     0,   987,
       0,     0,     0,   626,     0,   627,   628,   629,     0,     0,
    2029,     0,   985,     0,     0,     0,     0,     0,     0,   615,
       0,     0,     0,     0,     0,     0,     0,   987,     0,     0,
       0,     0,     0,     0,     0,   616,     0,     0,     0,  1632,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1633,  2030,  2031,     0,   631,   632,   633,     0,     0,     0,
       0,     0,     0,     0,   615,     0,     0,   634,     0,  1634,
     635,   618,     0,     0,     0,     0,  2032,     0,     0,     0,
       0,     0,     0,   988,     0,     0,     0,     0,     0,     0,
    1635,     0,     0,   619,   418,     0,     0,     0,     0,     0,
       0,     0,     0,   985,     0,     0,     0,     0,   620,     0,
       0,   988,     0,     0,     0,   621,   618,   622,   987,     0,
    2033,     0,   418,     0,  1148,     0,     0,     0,     0,     0,
     623,   990,     0,     0,     0,   419,     0,   991,     0,     0,
     992,     0,   420,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1148,   620,     0,     0,     0,     0,     0,   990,
       0,     0,   622,   419,     0,   991,     0,     0,   992,     0,
     420,     0,   993,     0,     0,   623,     0,     0,     0,     0,
       0,     0,     0,     0,   626,     0,   627,   628,   629,     0,
       0,     0,     0,  2034,     0,     0,  1071,     0,     0,     0,
     993,     0,   988,     0,     0,     0,     0,  2035,     0,     0,
       0,     0,     0,   421,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2036,   627,   628,   629,     0,   631,   632,   633,     0,     0,
     994,   421,     0,     0,     0,     0,     0,     0,   634,     0,
       0,   635,  2037,     0,  1017,     0,   991,     0,     0,   992,
       0,     0,     0,     0,     0,     0,     0,     0,   994,     0,
       0,  2038,     0,     0,     0,     0,   422,     0,     0,     0,
     631,   632,   633,     0,     0,   995,   996,     0,     0,     0,
       0,   993,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   422,   423,     0,     0,     0,     0,
     997,     0,     0,   995,   996,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   998,     0,
       0,     0,     0,   423,     0,     0,   999,     0,   997,   285,
       0,     0,     0,     0,     0,   424,  1149,  1150,     0,     0,
       0,     0,     0,     0,  1657,  1151,   998,     0,     0,   994,
       0,     0,     0,     0,   999,     0,     0,   285,     0,     0,
       0,     0,     0,   424,  1149,  1150,     0,     0,     0,     0,
       0,     0,  1891,  1151,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   995,   996,     0,     0,     0,     0,
       0,     0,     0,     0, -1562,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   997,
       0,     0,     0,     0,     0,     0,     0,     0,     0, -1021,
       0,     0,     0,     0,     0,     0,     0,   998,     0,     0,
       0,     0, -1021,     0,     0,   999,     0,   183,   285
};

static const yytype_int16 yycheck[] =
{
      84,   169,   222,   394,   131,   393,   692,   545,   512,   904,
     656,   246,   658,   441,   868,   307,  1276,  1028,  1206,   839,
     863,   189,   190,  1206,   624,  1106,   194,   195,   196,   197,
     198,   874,   200,   721,   202,  1100,  1206,  1206,  1206,   222,
    1344,   865,  1021,  1090,  1048,  1230,  1231,  1232,  1386,  1387,
    1120,   271,  1056,   663,   882,   275,   596,   277,   353,   186,
    1344,  1698,  1239,    17,   464,  1344,   286,   895,   236,   153,
     238,  1344,   576,  1344,  1344,     6,   864,   245,    13,     6,
    1199,   862,     6,     9,     6,   253,     6,    69,   271,    23,
     871,   872,   275,    22,   277,    48,    28,   332,  1102,   267,
     268,    69,   270,   286,   339,   886,   887,   999,   276,    49,
      21,  1176,     9,    30,   865,   104,    94,  1236,    69,   900,
     901,    17,    84,    56,   344,    69,    49,    85,  1175,     9,
     425,    48,   115,   884,   354,   203,     9,    72,   889,    22,
      70,   361,    37,   311,    72,    85,   314,   315,  1267,   317,
      54,  1849,   372,    88,   790,   390,    56,  1136,   146,    49,
     115,   344,   397,  1280,   984,   333,    69,    56,   232,   989,
     111,   354,   183,   264,   394,   410,   396,   232,   361,     9,
     112,     9,   350,    56,   210,    49,   832,   119,   214,   232,
     295,    31,  1262,   210,   118,   168,  1315,  1834,   844,   434,
     495,   172,   232,    65,   955,    25,   290,  1254,   178,   444,
    1837,   394,   320,    94,   119,   110,   147,   118,  1793,    62,
      50,  1002,    11,   274,   392,   232,     9,  1047,   153,    60,
     232,   317,   400,   115,   397,   123,   196,   457,   884,  1320,
     207,   168,  1480,   209,  1139,     8,   437,     0,   210,   232,
    1031,   118,   254,   893,   171,  1377,    87,    88,    49,   168,
    1498,   496,  1384,  1085,   664,   232,   806,   107,     0,  1316,
    1098,   911,    35,  1564,   457,  1345,   210,   232,   513,   449,
    1618,   167,    71,   451,  1065,    69,  1624,     1,  1579,   452,
     374,   232,   294,   377,  1298,   261,  1366,   170,  1417,  1121,
     307,   449,   470,   471,  1489,  1284,   232,   127,  1546,   119,
     501,   191,   547,   244,   344,   401,   551,   305,   247,   214,
     280,   429,    91,  1074,   375,   336,  1107,   973,  1148,  1376,
     435,  1112,   500,    47,  1511,  1962,   556,   557,   974,   975,
      62,   509,   232,   275,   435,  1199,   219,    61,  1586,    69,
     232,  1370,   232,   324,   279,   163,   120,   596,  1377,   239,
     428,   191,   320,   244,   247,  1384,   976,   535,   968,   969,
     258,  1512,   436,   355,   542,   165,  1219,  1518,   442,   210,
     320,   436,  1236,  1958,   619,    99,  1961,   355,   515,   317,
    1471,   221,   232,   436,   165,   203,    65,   320,  1149,  1150,
    1151,  1244,   232,   211,   355,   625,   944,   575,  1159,   239,
     436,   355,   580,  1267,  1418,   583,   345,   585,  1199,   300,
     588,   589,  1487,  2121,   592,  1206,   179,   316,   256,  1180,
     310,  1182,   449,  1184,   296,  1186,  1264,  1188,  1189,  1190,
    1191,  1192,  1193,  1194,  1195,  1515,   435,   436,   436,   232,
     164,   404,   355,   436,  1235,  1236,   320,   288,   436,   955,
    1248,  1315,   345,   436,   359,   219,   634,   635,   430,   451,
     184,   429,   336,   401,   398,   283,   398,  1715,   432,   449,
     310,   436,  1599,   451,   414,   313,  1267,   404,   399,   429,
    1278,  1538,   403,   373,   418,   436,   210,    69,   398,   395,
     451,   215,   436,   435,   437,   436,   429,   451,   435,   436,
     436,   803,   436,   227,   436,   358,   436,   418,   435,   241,
     449,  1302,   402,  1570,   428,  1306,  1307,   436,  1309,   320,
     435,   436,   405,  2108,  1315,  1171,   663,  1325,  1549,   436,
     475,  1545,   837,   373,  1666,   336,   436,   311,   451,   236,
     436,   418,   442,   306,   436,   436,  1860,   326,    32,   349,
     229,   371,   442,  1417,  1824,   429,  1170,   806,   232,   256,
     790,   355,   402,   793,   794,  1084,  1860,   977,   349,  1179,
     800,  1860,    23,   305,   183,   449,  1186,  1860,   147,  1860,
    1860,   117,   114,  1770,  1090,   359,  1347,  1738,  1739,    49,
     314,   315,  1142,  1354,  1355,  1356,  1357,  1358,  1359,  1360,
     793,   794,   442,   327,   782,   329,  2253,   800,   449,   232,
     389,   244,   857,  1764,   153,   435,   436,   296,   436,   400,
     232,   353,  1773,   264,   802,   355,   358,   241,   429,   136,
     450,   223,   224,  1724,   864,   219,  1246,  1666,  1767,   121,
    1769,   405,  1890,  1149,  1150,  1151,   120,   363,   449,   443,
     444,   445,   446,  1159,   448,   885,   136,   451,     9,   889,
     236,   891,   183,   893,   894,   970,   896,  1363,  1288,  1175,
     194,  1469,  1292,    40,  1180,  1804,  1182,   161,  1184,  2027,
    1186,   911,  1188,  1189,  1190,  1191,  1192,  1193,  1194,  1195,
     164,   305,   449,  1941,   924,  1943,   412,   927,   243,   403,
    1689,  1690,  1691,  1717,   436,   429,  1544,  1836,   953,   191,
     940,   183,   236,   443,   444,   445,   446,   179,   448,   183,
     156,   451,   183,  1971,   160,   449,  1783,   336,   958,   232,
    1426,   924,   256,  1928,  1929,  1930,  1931,  1347,   435,   353,
     279,   244,   153,   154,   974,   975,   206,   940,  1254,   294,
     232,  1365,   889,  1904,  2002,  2003,   240,   239,    99,   210,
     955,   295,   436,   941,  1283,   398,   342,  1847,   300,   251,
     181,     9,  1923,   355,    12,   869,   187,    15,    16,   420,
    1478,  1872,  1392,    30,  1841,   288,  1577,  1621,  1802,  1940,
     220,    27,  1883,  1884,   435,  1697,   890,  1995,   892,   306,
    1702,  1703,  1995,   897,  1706,  1707,  1708,   218,  1710,  1711,
    1316,   222,   906,   436,    81,  1995,  1995,  1995,    65,   955,
    1865,   405,   343,  1519,   436,   243,   306,   191,   310,    96,
    1981,  1982,  1528,   537,    30,   449,  1881,  1882,   367,  1990,
     191,  1347,   194,   195,   306,  1936,  1937,   183,  1354,  1355,
    1356,  1357,  1358,  1359,  1360,    12,  1086,   449,    15,    16,
    1621,   443,   444,   445,   446,  2007,   448,  2009,   232,   451,
    1376,   343,   241,   173,     9,   239,   294,   244,   274,   343,
     241,   232,   343,   412,   236,   166,   363,  1932,   239,    28,
    1935,   373,   196,     8,   376,   377,  1141,     1,   443,   444,
       4,   435,   436,  1767,   256,  1769,   232,   431,  2178,   228,
     160,   341,   310,   180,   233,    19,   449,   315,  1771,  1056,
      35,    56,   236,   204,   176,    29,  2077,   123,  1022,   176,
     164,   212,   363,   436,  2085,   412,   305,  1074,  1699,   442,
    1804,  1171,   256,  1704,   305,  2020,   310,   283,   248,  2100,
     184,   104,   117,  1131,  1149,  1150,  1151,     9,    62,   310,
     442,  2209,  2210,  1573,  1159,   232,   151,   234,   272,  1822,
     237,   367,  1836,   112,   123,  2020,   295,  2128,   247,  2130,
     232,   412,   229,   236,   353,  1180,  2137,  1182,   163,  1184,
    2011,   871,   353,  1188,  1189,  1190,  1191,  1192,  1193,  1194,
    1195,   363,   269,   256,    56,  2147,  2157,  2158,   371,   373,
    2280,   249,   250,  1149,  1150,  1151,   412,   164,  1248,   172,
    1811,   901,   373,  1159,   209,   443,   444,  2072,   203,   267,
     268,   184,  1538,  1539,   284,   170,   211,   184,   402,   450,
    1342,   184,   453,   454,   990,   314,  1182,   316,  1278,   296,
     412,   402,  1188,  1189,  1190,  1191,   191,   254,  1194,  1195,
     209,   380,    89,    90,  1570,  1884,   319,   210,   198,  1015,
     337,   399,   436,   436,   259,   403,   261,  1214,   442,   431,
     449,   363,  2233,   435,   219,   436,   113,   450,   449,  1994,
    2111,   442,   249,   250,   198,  1325,   314,   232,     6,   229,
     435,     9,   299,  1541,   239,    82,  1336,  1337,   283,   258,
     267,   268,   261,   302,   449,   382,   383,  1936,  1937,   291,
     292,   435,   436,   399,  1915,   229,  1782,   403,   417,     9,
     412,  1225,   236,   305,    33,   236,   236,    36,   351,   191,
     407,   430,   270,  1336,  1337,    44,    45,    46,  2193,   351,
    1287,   369,   370,  2198,   236,   256,   256,   410,   425,  1354,
    1355,  1356,  1357,  1358,  1359,  1360,   433,   219,  1404,   436,
     314,  1407,   316,    81,   256,   310,  1412,   281,   449,   351,
     232,  1837,   435,   287,   314,    11,   191,   239,    96,  1326,
    2277,   321,     2,  1699,   449,   191,     6,  2218,  1704,    25,
      26,    81,   159,   449,   332,  2035,   163,  2294,   449,   503,
     314,   191,   449,  1909,   508,  1911,    96,   321,  1354,  1355,
    1356,  1357,  1358,  1359,  1360,   223,   224,   232,  1180,   359,
     334,    57,  1184,  2097,   239,  2099,   232,   306,   373,  1469,
    1192,  1193,   117,   239,   372,   153,   374,   132,   443,   444,
     445,   446,   232,   448,   358,   359,   155,   361,   310,   239,
     455,   305,   289,   290,   273,   369,   275,   402,    94,    95,
     405,    97,   180,   449,   173,   379,   314,  1783,   316,   105,
     351,   445,   446,   191,   448,  1791,   432,  1801,   434,   223,
     224,   190,   443,   444,   445,   446,   400,   448,   229,   230,
     180,   436,   438,   330,   331,   310,  1962,   442,   150,   166,
     152,   191,   449,   221,   310,   421,   422,   423,   424,  2224,
     228,   373,   148,   149,   232,   351,   234,  2118,   235,   237,
     310,   239,    11,   159,   260,  1841,   262,   265,   266,   238,
     421,   422,   423,   424,   436,   449,    25,    26,   336,   150,
     402,   152,   232,   405,   234,   449,   314,   237,   316,   239,
    1874,   269,   449,     6,   449,  1610,     9,   354,   373,   265,
     266,  1601,   421,   422,   423,   424,   449,   373,    57,   229,
     230,  1626,   449,  2079,   436,  2081,   285,    30,   449,   269,
     442,   212,   400,   373,    71,   449,   351,    12,    13,    14,
    1578,   231,   310,   436,   449,    20,   402,   233,  1601,    25,
      26,  1548,  2068,   449,  1644,    94,    95,   178,    97,   278,
     449,  2212,    65,   275,  2215,   390,   105,    24,  1606,   337,
     310,  1661,   449,   351,   327,  1613,   210,   442,    81,   338,
     367,   104,  1620,    58,   436,   449,   442,  1584,   362,   348,
      66,  1644,    68,    96,  1591,   379,    56,   337,   443,   444,
     445,   446,   442,   448,   436,   373,   451,    84,  1661,   148,
     149,  1701,   172,  2264,   382,   383,   443,   444,   445,   446,
     159,   448,   351,   449,   100,   101,   102,   278,   455,   367,
     346,   232,  1670,   373,   402,  1673,   106,   358,   207,   407,
     449,    67,   382,   383,  1699,   245,  2297,   449,  1701,  1704,
     409,   443,   444,   445,   446,   351,   448,   425,   245,   451,
      23,   347,   402,   272,   436,   433,   449,   407,   436,   232,
     296,   147,   449,   149,   442,    83,   861,   180,   153,   154,
     865,   157,   450,    83,   436,   425,   871,   430,   191,   436,
     395,   876,   877,   433,   233,   379,   436,   882,   883,   884,
     312,   387,   442,  1699,   889,   429,   181,   398,  1704,  1747,
     895,   230,   187,   196,   436,  1753,   314,   359,   221,   904,
     905,   398,   907,    55,   435,   228,   229,   379,    27,   232,
     367,   234,   184,   351,   237,   210,   239,   191,  1743,  1744,
    1745,  1746,   449,   218,   359,   199,   449,   222,   214,   436,
     436,  1856,   223,   221,   230,   341,   432,  1795,   106,   210,
     232,   400,    37,   449,   218,   301,   269,  2175,   244,   376,
     955,   282,   276,  2031,   442,   398,   395,   252,   253,   452,
      27,   357,   257,   443,   444,   445,   446,   272,   448,   456,
     395,   451,   267,   296,   171,   443,   444,   445,   446,   274,
     448,   986,   449,   451,   279,   449,   436,   310,   347,  1806,
     232,   265,   266,   133,   104,  1812,   400,    17,   435,   273,
     274,   452,   297,   169,  1862,   279,   280,   184,   232,  1867,
     397,    30,   124,   201,   337,    56,  1021,   125,  1876,   443,
     444,   445,   446,   398,   448,   127,   452,   451,   387,   452,
     452,   428,  1806,   443,   444,   445,   446,   452,   448,   452,
     452,   451,   343,  1048,   452,   314,   129,   452,   130,   452,
     373,  1056,  1057,   452,   452,    98,   394,   398,  1968,   382,
     383,   134,    49,   397,   135,   395,   392,   176,   397,  1074,
     140,   244,   430,    49,   143,   176,   109,   436,   328,   402,
     111,   375,   360,   111,   407,  1090,   435,   398,   436,   183,
     364,   336,   304,  1098,   232,  1968,   160,  1102,   398,   131,
     396,   361,   425,   168,   432,  1110,   206,    49,  1113,   398,
     433,   214,   119,   436,   176,   206,   275,   189,   440,   442,
     441,  2202,   214,   448,   265,   229,   336,   393,   398,   368,
    2055,  1136,   451,   451,  1139,   451,   451,   128,   261,   264,
     436,   183,   260,   395,  1149,  1150,  1151,   442,   443,   444,
     445,   446,   326,   448,  1159,   450,   451,   398,   453,   454,
      49,   135,     8,   176,   432,  2023,   123,   432,   398,     9,
    1175,   302,   170,   303,   198,  1180,  2034,  1182,  2036,  1184,
     399,   324,   263,  1188,  1189,  1190,  1191,  1192,  1193,  1194,
    1195,   339,     6,   122,   429,     9,   107,   429,    49,   172,
     280,   138,   258,   139,  2114,   257,   236,   141,   284,  2067,
     295,   279,   110,   389,     7,   216,   113,    66,   153,   126,
       1,   153,    99,   133,   323,     6,   323,    49,     9,   214,
     236,    93,   145,   142,   259,    49,   262,    90,   217,   199,
    2165,   188,   432,   385,   436,    49,   401,   302,   236,  1254,
     339,   144,   236,   171,   176,   302,   417,   137,    49,  1264,
    2185,  2186,  2120,     6,   338,   288,    22,    81,    54,   186,
    2180,    85,  1277,   131,   204,   171,   181,  1299,   491,  1284,
    1122,   425,    96,   570,  1330,   135,  1291,  1337,  1123,   930,
    1852,  1805,  2202,  1298,   220,   374,   581,   109,    49,   573,
      81,   153,   227,   856,   557,  1310,   302,  2180,  2166,  2167,
     831,  1316,  2170,  1860,  1646,    96,  2200,  1322,   844,  2177,
    2245,  2246,   539,   943,  2249,  2050,  2251,  2186,    31,  2202,
      33,   806,  1726,    36,  1339,   123,   473,  1809,  1031,  1685,
    1036,  1389,  1724,    46,  1760,  1244,  1241,  1770,  1388,  1354,
    1355,  1356,  1357,  1358,  1359,  1360,  1511,  1251,  2216,  1791,
    1952,  2271,  1536,  2288,  1074,  1257,   180,  2277,  1810,  1560,
    1292,  1376,   153,   154,  1326,  1826,  1096,   191,   896,  1098,
    1107,  1591,  2156,  1591,  2294,  1663,  2121,  1817,  2016,  2247,
    1485,  1396,  1086,  1573,  2005,  1208,   234,   956,  2271,   180,
     181,  2010,  1601,  1204,  1262,   836,   187,   221,  1039,   313,
     191,   590,   963,  1418,   228,  2204,   797,    57,   232,  1432,
     234,  2279,  1868,   237,   971,   239,    -1,    -1,    -1,   210,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,    -1,    -1,
     221,   222,    -1,  2217,    -1,    -1,    -1,   228,    -1,    -1,
      -1,   232,    -1,   234,    -1,   269,   237,    -1,   239,    -1,
     274,    -1,    -1,    -1,    -1,    -1,    -1,  1472,  1473,    -1,
     173,   252,    -1,    -1,   177,    -1,   257,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   190,   269,    -1,
      81,    -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2278,    96,   320,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   337,    -1,    -1,    -1,    -1,    -1,   310,
      -1,    -1,    -1,  1538,  1539,   238,    -1,    -1,    -1,  1544,
    1545,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   367,    -1,    -1,   337,  1562,    -1,   373,
      -1,    -1,    -1,    -1,    -1,  1570,    -1,    -1,   382,   383,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1585,    -1,   285,    -1,    -1,  1590,  1591,    -1,   402,   180,
      -1,    -1,   373,   407,    -1,    -1,    -1,    -1,   412,    -1,
     191,   382,   383,    -1,    -1,    -1,   309,    -1,    -1,    -1,
      -1,   425,    -1,    -1,    -1,   429,  1621,    -1,    -1,   433,
      -1,   402,   436,    -1,    -1,    -1,   407,  1632,   442,  1634,
     333,    -1,    -1,    -1,    -1,   338,    -1,    -1,    -1,    -1,
      -1,   232,    -1,   234,   425,   348,   237,    -1,   239,   352,
      81,    -1,   433,    -1,    -1,   436,    -1,    -1,    -1,    -1,
      -1,   442,   443,   444,    -1,    96,    -1,   448,    -1,   450,
      -1,   452,   453,   454,    -1,    -1,    -1,    -1,   269,    -1,
      -1,    -1,    -1,    -1,  1689,  1690,  1691,    -1,    -1,     0,
       1,    -1,    -1,    -1,  1699,    -1,    -1,    -1,    -1,  1704,
      -1,    -1,    -1,    -1,    -1,    -1,   409,    -1,    -1,    -1,
      21,    -1,  1717,    -1,    -1,    -1,   419,    -1,    -1,   310,
      -1,    -1,    -1,    34,    -1,    -1,    37,    38,    39,    40,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   174,    -1,    81,   337,    -1,    -1,   180,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      96,    -1,    73,    -1,    75,    76,    77,    78,    79,    80,
      -1,  1776,    -1,    -1,    -1,    -1,    -1,  1782,  1783,    -1,
      -1,    -1,   373,    -1,    -1,    -1,  1791,    -1,    -1,    -1,
      -1,   382,   383,    -1,    -1,    -1,    -1,  1802,    -1,    -1,
      -1,   232,    -1,   234,   115,  1810,   237,    -1,    -1,    -1,
      -1,   402,    -1,    -1,    -1,    -1,   407,    -1,    -1,    -1,
      -1,   132,    -1,    -1,    -1,   136,    -1,    -1,    -1,    -1,
      -1,    -1,  1837,    -1,   425,    -1,  1841,    -1,   269,    -1,
      -1,    -1,   433,    -1,   180,   436,    -1,    -1,    -1,    -1,
      -1,   442,    -1,   164,   165,   191,  1861,    -1,    -1,    -1,
    1865,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   179,    -1,
      -1,    -1,    -1,   184,    -1,    -1,  1881,  1882,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   221,   197,    -1,    -1,    -1,
      -1,    -1,   228,    -1,    -1,    -1,   232,    -1,   234,   210,
      -1,   237,   213,   239,    -1,    -1,   337,    -1,   219,    -1,
      -1,    -1,   223,   224,    -1,    -1,    -1,    -1,    -1,    -1,
     231,   232,    -1,    -1,   235,    -1,    -1,  1932,    -1,    -1,
    1935,    -1,    -1,   269,    -1,    -1,    -1,    -1,   249,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   382,   383,    -1,    -1,    -1,    -1,  1962,    -1,    -1,
     271,   392,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   310,   286,   407,    -1,    -1,    -1,
      -1,    -1,   293,    -1,   295,    -1,   417,    -1,    -1,  1994,
      -1,   302,    -1,    -1,   425,   306,  2001,   308,    -1,   430,
      -1,   337,   433,    -1,   435,   436,    -1,   318,    -1,    -1,
      -1,    -1,    -1,    -1,   325,  2020,   327,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  2037,    -1,    -1,   346,    -1,   373,   349,     0,
       1,    -1,     3,    -1,     5,    -1,   382,   383,    -1,    10,
      -1,   362,    -1,   364,   365,   366,    -1,    18,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   402,  2072,    -1,    -1,
      -1,   407,    -1,    -1,    -1,    -1,    -1,   388,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   425,
      51,    52,    -1,    -1,   405,    -1,    -1,   433,    59,    -1,
     436,    -1,   413,   414,   415,    -1,   442,   443,   444,    70,
      -1,    -1,    -1,    74,    -1,   426,   452,    -1,   429,    -1,
      -1,    -1,    -1,    -1,    -1,    86,  2131,   438,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   449,    -1,
      -1,  2146,    -1,    -1,  2149,    -1,    -1,   108,    -1,    -1,
      -1,    -1,    -1,    -1,   115,   116,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   132,    -1,    -1,  2179,   136,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   146,    -1,    -1,  2193,    -1,
      -1,    -1,    -1,  2198,    -1,    -1,    -1,   158,    -1,    -1,
      -1,   162,    -1,    -1,    -1,    -1,     1,    -1,     3,    -1,
       5,    -1,    -1,    -1,   175,    10,    -1,    -1,   179,  2224,
      -1,   182,    -1,    18,   185,   186,    -1,    -1,    -1,    -1,
    2235,    -1,   193,    -1,    -1,    -1,    -1,    -1,    -1,   200,
      -1,   202,    -1,    -1,   205,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,  2281,    -1,    -1,    74,
      -1,   242,    -1,    -1,    -1,   246,    -1,   248,    -1,    -1,
      -1,    86,    -1,    -1,   255,     6,    -1,    -1,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,
      21,    -1,    -1,   108,    -1,    -1,   277,    -1,    -1,    -1,
     115,   116,    -1,    -1,    -1,    -1,    -1,    -1,   123,    -1,
      -1,   292,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   306,    -1,    -1,    -1,    -1,
      -1,   146,   313,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   322,    -1,   158,    -1,    -1,    -1,   162,    -1,    -1,
      81,    -1,    -1,    -1,   335,    -1,    -1,    -1,    -1,   340,
     175,   342,    -1,    -1,    -1,    96,    -1,   182,    -1,   350,
     185,   186,    -1,    -1,    -1,    -1,    -1,    -1,   193,   360,
      -1,    -1,    -1,    -1,    -1,   200,    -1,   202,   369,    -1,
     205,    -1,    -1,    -1,    -1,    -1,    -1,   378,    -1,   380,
     381,    -1,    -1,   384,    -1,   386,    -1,    -1,    -1,    -1,
     391,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   153,   154,    -1,   406,    -1,   242,    -1,    -1,
     411,   246,    -1,   248,     6,   416,    -1,     9,    -1,    -1,
     255,    -1,    -1,    -1,    -1,    -1,   427,    -1,    -1,   180,
     181,    -1,    -1,    -1,    -1,   436,   187,    -1,   439,    -1,
     191,    -1,   277,    -1,    -1,    -1,    -1,    -1,   449,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   292,    -1,   210,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,    -1,    -1,
     221,   222,    -1,    -1,    -1,    -1,    -1,   228,   313,    -1,
      -1,   232,    -1,   234,    -1,    -1,   237,   322,   239,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     335,   252,    -1,    -1,    96,   340,   257,   342,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   350,    -1,    -1,   269,    -1,
      -1,    -1,    -1,    -1,    -1,   360,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   369,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   378,    -1,   380,   381,    -1,    -1,   384,
      -1,   386,    -1,    -1,    -1,    -1,   391,    -1,    -1,   310,
      -1,   153,   154,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   406,    -1,    -1,    -1,    -1,   411,    -1,    -1,    -1,
      -1,   416,    -1,    -1,    -1,    -1,   337,    -1,   180,   181,
      -1,    -1,   427,    -1,    -1,   187,    -1,    -1,    -1,   191,
      -1,   436,    -1,    -1,   439,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   449,    -1,    -1,    -1,   210,    -1,
      -1,    -1,   373,    -1,    -1,    -1,   218,    -1,    -1,   221,
     222,   382,   383,    -1,    -1,    -1,   228,    -1,    -1,    -1,
     232,    -1,   234,    -1,    -1,   237,    -1,   239,   399,    -1,
      -1,   402,   403,    -1,    -1,    -1,   407,    -1,    -1,    -1,
     252,    -1,    -1,    -1,    -1,   257,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   425,    -1,    -1,   269,    -1,    -1,
      -1,    -1,   433,    -1,    -1,   436,    -1,    -1,    -1,    -1,
      -1,   442,   443,   444,    -1,    -1,    -1,   448,    -1,   450,
      -1,   452,   453,   454,     3,    -1,     5,    -1,    -1,    -1,
      -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,   310,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   337,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,
      -1,   373,    -1,    -1,    -1,    -1,     3,    86,     5,    -1,
     382,   383,    -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,
     402,    -1,    -1,    -1,    -1,   407,   115,   116,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   425,    51,    52,    -1,    -1,    -1,    -1,
      -1,   433,    59,    -1,   436,    -1,    -1,   146,    -1,    -1,
     442,   443,   444,    70,    -1,    -1,   448,    74,   450,   158,
     452,   453,   454,   162,    -1,    -1,    -1,    -1,    -1,    86,
      -1,     6,    -1,    -1,     9,    -1,   175,    -1,    -1,    -1,
      -1,    -1,    -1,   182,    -1,    -1,   185,   186,    -1,    -1,
      -1,   108,    -1,    -1,   193,    -1,    -1,    -1,   115,   116,
      -1,   200,    -1,   202,    -1,    -1,   205,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   146,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   158,    -1,   242,    -1,   162,    81,   246,    -1,   248,
      -1,    -1,    -1,    -1,    -1,    -1,   255,    -1,   175,    -1,
      -1,    96,    -1,    -1,    -1,   182,    -1,    -1,   185,   186,
      -1,    -1,    -1,    -1,    -1,    -1,   193,    -1,   277,    -1,
      -1,    -1,    -1,   200,    -1,   202,    -1,    -1,   205,    -1,
      -1,    -1,    -1,   292,    -1,    -1,    -1,    -1,     6,    -1,
      -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   146,    -1,    -1,   313,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   322,    -1,   242,    -1,    -1,    -1,   246,
      -1,   248,    -1,    -1,    -1,    -1,   335,    -1,   255,    -1,
      -1,   340,    -1,   342,    -1,   180,    -1,    -1,    -1,    -1,
      -1,   350,    -1,    -1,    -1,    -1,   191,    -1,    -1,    -1,
     277,   360,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     369,    -1,    -1,    81,    -1,   292,    -1,    -1,    -1,   378,
      -1,   380,   381,    -1,    -1,   384,   221,   386,    96,    -1,
      -1,     6,   391,   228,     9,    -1,   313,   232,    -1,   234,
      -1,   109,   237,    -1,   239,   322,    -1,   406,    -1,    -1,
      -1,    -1,   411,    -1,    -1,    -1,    -1,   416,   335,    -1,
      -1,    -1,    -1,   340,    -1,   342,    -1,    -1,   427,     6,
      -1,    -1,     9,   350,   269,    -1,    -1,    -1,    -1,    -1,
     439,    -1,    -1,   360,    -1,    -1,    -1,    -1,    -1,    -1,
     449,    -1,   369,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   378,    -1,   380,   381,    -1,    81,   384,    -1,   386,
      -1,    -1,   180,    -1,   391,   310,     6,    92,    -1,     9,
      -1,    96,    -1,   191,    -1,    -1,    -1,    -1,    -1,   406,
      -1,    -1,    -1,    -1,   411,    -1,    -1,    -1,   206,   416,
      -1,    -1,   337,    -1,    81,    -1,    -1,    -1,    -1,    -1,
     427,    -1,    -1,   221,    -1,    92,    -1,    -1,    -1,    96,
     228,    -1,   439,    -1,   232,    -1,   234,    -1,    -1,   237,
      -1,   239,    -1,    -1,    -1,    -1,    -1,    -1,   373,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   382,   383,    -1,
       6,    81,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   269,    -1,    -1,   399,   180,    96,   402,   403,    -1,
      -1,    -1,   407,    -1,    -1,    -1,   191,    -1,    -1,   109,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     425,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   433,    -1,
      -1,   436,   310,   180,    -1,    -1,   221,   442,    -1,    -1,
      -1,    -1,    -1,   228,   191,    -1,    -1,   232,    -1,   234,
      -1,    -1,   237,    -1,   239,    81,    -1,    -1,    -1,   337,
      -1,    -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,    -1,
      96,    -1,    -1,    -1,   221,    -1,    -1,    -1,    -1,    -1,
     180,   228,    -1,    -1,   269,   232,    -1,   234,    -1,    -1,
     237,   191,   239,    -1,    -1,   373,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   382,   383,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   221,   269,    -1,   402,   310,    -1,    -1,   228,   407,
      -1,    -1,   232,    -1,   234,    -1,    -1,   237,    -1,   239,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   425,    -1,    -1,
      -1,    -1,   337,    -1,   180,   433,     6,    -1,   436,     9,
      -1,    -1,    -1,   310,   442,   191,    -1,    -1,    -1,   269,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,    -1,
      -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,   373,    -1,
     337,    -1,    -1,    -1,    -1,   221,    -1,   382,   383,    -1,
       6,    -1,   228,     9,    -1,    -1,   232,    -1,   234,    -1,
     310,   237,    -1,   239,    -1,    -1,    -1,   402,    -1,    -1,
      -1,    -1,   407,    -1,    -1,    -1,   373,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    -1,   382,   383,   337,    -1,    -1,
     425,    -1,    -1,   269,    -1,    -1,    96,    -1,   433,    -1,
      -1,   436,    -1,    81,    -1,   402,    -1,   442,    -1,    -1,
     407,    -1,    -1,    -1,     6,    -1,    -1,     9,    96,    -1,
      -1,    -1,    -1,   373,    -1,    81,    -1,    -1,   425,    -1,
      -1,    -1,   382,   383,   310,    -1,   433,    -1,    -1,   436,
      96,    -1,    -1,    -1,    -1,   442,    -1,    -1,    -1,    -1,
      -1,    -1,   402,    -1,    -1,    -1,    -1,   407,    -1,    -1,
      -1,   337,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   425,    -1,    -1,    -1,    -1,
     180,    -1,    -1,   433,    -1,    -1,   436,    -1,    -1,    81,
      -1,   191,   442,    -1,    -1,    -1,    -1,   373,   176,    -1,
      -1,    -1,   180,    -1,    96,    -1,   382,   383,    -1,    -1,
      -1,    -1,    -1,   191,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   221,    -1,    -1,   180,    -1,   402,    -1,   228,    -1,
      -1,   407,   232,    -1,   234,   191,    -1,   237,    -1,   239,
      -1,    -1,    -1,   221,    -1,    -1,    -1,    -1,    -1,   425,
     228,    -1,    -1,    -1,   232,    -1,   234,   433,    -1,   237,
     436,   239,    -1,    -1,    -1,   221,   442,    -1,    -1,   269,
      -1,    -1,   228,    -1,     6,    -1,   232,     9,   234,    -1,
      -1,   237,    -1,   239,    -1,    -1,     6,    -1,   180,     9,
      -1,   269,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   191,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     310,    -1,    -1,   269,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   221,
      -1,    -1,   310,    -1,    -1,    -1,   228,   337,    -1,    -1,
     232,    -1,   234,    -1,    -1,   237,    -1,   239,    -1,    81,
      -1,    -1,    -1,    -1,   310,    -1,    -1,    -1,    -1,   337,
      -1,    81,    -1,    -1,    96,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   373,    -1,    -1,    96,   269,    -1,    -1,
      -1,   337,   382,   383,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   373,    -1,    -1,   398,    -1,
      -1,    -1,   402,    -1,   382,   383,    -1,   407,    -1,    -1,
      -1,   367,    -1,    -1,    -1,    -1,    -1,   373,   310,    -1,
      -1,    -1,    -1,    -1,   402,   425,   382,   383,    -1,   407,
      -1,    -1,    -1,   433,    -1,    -1,   436,    -1,    -1,    -1,
      -1,    -1,   442,    -1,    -1,   337,   402,   425,   180,    -1,
      -1,   407,    -1,    -1,    -1,   433,    -1,    -1,   436,   191,
     180,    -1,    -1,    -1,   442,    -1,    -1,    -1,    -1,   425,
      -1,   191,    -1,    -1,    -1,    -1,   368,   433,    -1,    -1,
     436,   373,    -1,    -1,    -1,    -1,   442,    -1,    -1,   221,
     382,   383,    -1,    -1,    -1,    -1,   228,    -1,    -1,    -1,
     232,   221,   234,    -1,    -1,   237,    -1,   239,   228,    -1,
     402,    -1,   232,    -1,   234,   407,    -1,   237,    -1,   239,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   425,    -1,    -1,    -1,   269,    -1,    -1,
      -1,   433,    -1,    -1,   436,    -1,    -1,    -1,    -1,   269,
     442,    -1,    31,    -1,    33,    -1,    -1,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,
     310,    -1,    -1,    -1,    73,    -1,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,   337,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   115,    -1,    -1,    -1,
      -1,   373,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     382,   383,    -1,   373,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   382,   383,    -1,    -1,    -1,    -1,    -1,    -1,
     402,    -1,    -1,    -1,    -1,   407,   155,    -1,    -1,    -1,
      -1,    -1,   402,    -1,    -1,    -1,    -1,   407,    -1,    -1,
      -1,    -1,    -1,   425,   173,    -1,    -1,   176,   177,    -1,
      -1,   433,    -1,    -1,   436,   425,    -1,    -1,    -1,    -1,
     442,   190,    -1,   433,    -1,    -1,   436,    -1,   197,    -1,
      -1,    -1,   442,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   213,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
     229,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   238,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    -1,
     249,    -1,    -1,    -1,    -1,    73,    -1,    75,    76,    77,
      78,    79,    80,    -1,    37,    38,    39,    40,    41,    42,
      -1,    -1,   271,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   285,   286,    -1,    -1,
      -1,    -1,    -1,    -1,   293,    -1,   295,   115,    -1,    -1,
      73,    -1,    75,    76,    77,    78,    79,    80,    -1,   308,
     309,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   333,    -1,    -1,    -1,    -1,   338,
      -1,    -1,   115,    -1,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   352,    -1,    -1,    -1,    -1,    -1,    96,
      -1,    -1,    -1,   362,    -1,   364,   365,   366,    -1,    -1,
     188,    -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,   197,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   213,    -1,    -1,    -1,   398,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     409,   229,   230,    -1,   413,   414,   415,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   197,    -1,    -1,   426,    -1,   428,
     429,   249,    -1,    -1,    -1,    -1,   254,    -1,    -1,    -1,
      -1,    -1,    -1,   180,    -1,    -1,    -1,    -1,    -1,    -1,
     449,    -1,    -1,   271,   191,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,   286,    -1,
      -1,   180,    -1,    -1,    -1,   293,   249,   295,    96,    -1,
     298,    -1,   191,    -1,   221,    -1,    -1,    -1,    -1,    -1,
     308,   228,    -1,    -1,    -1,   232,    -1,   234,    -1,    -1,
     237,    -1,   239,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   221,   286,    -1,    -1,    -1,    -1,    -1,   228,
      -1,    -1,   295,   232,    -1,   234,    -1,    -1,   237,    -1,
     239,    -1,   269,    -1,    -1,   308,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   362,    -1,   364,   365,   366,    -1,
      -1,    -1,    -1,   371,    -1,    -1,   174,    -1,    -1,    -1,
     269,    -1,   180,    -1,    -1,    -1,    -1,   385,    -1,    -1,
      -1,    -1,    -1,   310,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     408,   364,   365,   366,    -1,   413,   414,   415,    -1,    -1,
     337,   310,    -1,    -1,    -1,    -1,    -1,    -1,   426,    -1,
      -1,   429,   430,    -1,   232,    -1,   234,    -1,    -1,   237,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,    -1,
      -1,   449,    -1,    -1,    -1,    -1,   373,    -1,    -1,    -1,
     413,   414,   415,    -1,    -1,   382,   383,    -1,    -1,    -1,
      -1,   269,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   373,   402,    -1,    -1,    -1,    -1,
     407,    -1,    -1,   382,   383,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   425,    -1,
      -1,    -1,    -1,   402,    -1,    -1,   433,    -1,   407,   436,
      -1,    -1,    -1,    -1,    -1,   442,   443,   444,    -1,    -1,
      -1,    -1,    -1,    -1,   451,   452,   425,    -1,    -1,   337,
      -1,    -1,    -1,    -1,   433,    -1,    -1,   436,    -1,    -1,
      -1,    -1,    -1,   442,   443,   444,    -1,    -1,    -1,    -1,
      -1,    -1,   451,   452,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   382,   383,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   392,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   407,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   417,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   425,    -1,    -1,
      -1,    -1,   430,    -1,    -1,   433,    -1,   435,   436
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   458,   459,     0,   179,   306,   460,   461,   462,   468,
     475,   477,   449,   449,     0,   461,   147,   483,   483,   232,
     307,   478,   478,   117,   463,   469,    27,   479,   479,   449,
      99,   585,   585,   232,   449,   476,    82,   484,   117,   464,
     470,   210,   480,  1133,   351,   166,   204,   212,   538,   449,
     302,   723,   723,   449,    72,   317,   401,   481,   482,   449,
     449,   351,   449,   165,   349,   400,   586,   592,   117,   465,
     471,   475,   132,   474,   482,   305,  1144,   485,   539,   449,
     540,   351,   438,   617,   588,    54,   428,   726,   136,   465,
     472,   483,   478,   270,   332,   372,   374,   486,   487,   491,
     499,   504,   542,   166,   541,    22,   247,   345,   575,   576,
     577,   578,   580,   584,   449,   351,   235,   666,   436,   591,
     593,  1064,   728,   727,   336,   734,   478,   466,   449,   449,
     449,   449,   449,   354,   543,   449,   212,   574,    71,   400,
    1129,   314,   369,   370,   579,   449,   577,   587,   449,   351,
     231,   668,   590,   592,   619,   620,   621,   594,    49,   729,
     730,   731,  1124,   729,   436,   449,   449,   585,   241,   353,
     436,   490,   492,   493,   494,   495,   497,   498,  1144,   178,
     500,   501,   502,   435,   488,   489,   490,  1158,    11,    25,
      26,    57,    94,    95,    97,   105,   148,   149,   159,   233,
     347,   387,   436,   505,   506,   507,   508,   515,   524,   528,
     531,   532,   533,   534,   535,   536,   537,   278,  1110,   542,
     449,   275,  1141,   390,  1152,    24,  1120,   589,   618,   449,
     351,   327,   670,   593,   622,  1104,   595,   730,   367,   412,
     732,   320,   429,   724,   467,   367,  1133,   449,   493,   449,
     494,    62,   358,  1116,     9,   232,   503,   449,   502,   449,
     449,   489,   104,   436,  1075,  1133,  1133,  1075,   379,   362,
    1148,  1133,  1133,  1133,  1133,  1133,  1075,  1133,    56,  1126,
    1133,   449,   507,  1075,   575,   436,  1071,  1072,  1090,    84,
    1127,   172,  1130,   590,   619,   667,   449,   351,   346,   711,
     619,   449,  1104,   223,   224,   623,   626,   627,   633,     1,
      47,    61,    99,   215,   227,   314,   315,   327,   329,   429,
     449,   596,   597,   599,   603,   605,   607,   608,   614,   615,
     616,  1133,  1133,   367,   278,   733,   106,   735,   723,  1133,
     232,  1093,   449,   358,  1133,   207,   207,   232,   449,   245,
     516,  1075,  1075,  1133,  1133,  1133,  1072,    67,  1075,  1075,
    1072,  1133,  1072,   525,   526,  1075,    94,   510,  1075,   544,
     196,   272,  1113,  1072,   581,   582,  1064,  1063,  1064,   619,
     669,   449,   351,   623,   168,   436,   629,   630,   436,   629,
    1127,  1133,   314,   316,  1114,  1114,  1133,  1127,  1133,   245,
    1138,  1133,    23,  1119,   272,   164,   184,    31,   107,  1093,
    1133,   436,   449,   725,   471,  1093,  1072,  1133,   191,   232,
     239,   310,   373,   402,   442,   529,   530,  1096,  1072,   232,
    1072,    23,   210,  1075,  1134,   273,   275,   512,   513,   514,
     509,   545,  1090,   582,   296,   583,  1064,   619,   671,   449,
     624,    83,   625,  1093,   436,  1133,  1119,  1071,   274,   375,
     604,   232,  1072,  1074,  1093,   430,  1133,   436,   710,   710,
     167,   436,  1093,   736,   737,   136,   473,    56,   437,   496,
     121,   191,   232,   239,   251,   310,   373,   376,   377,   442,
     517,   518,   519,   522,   530,   395,   527,  1093,   513,   379,
    1151,   511,     1,     4,    19,    29,   198,   229,   236,   281,
     287,   314,   321,   334,   359,   361,   369,   400,   449,   546,
     547,   551,   553,   558,   559,   560,   561,   565,   566,   567,
     568,   569,   570,   571,   572,  1116,  1093,   312,   672,   673,
     674,   712,   634,   631,  1133,   429,   659,   398,   602,   230,
    1137,   398,  1126,   196,  1132,   436,  1133,  1133,   737,     1,
     436,   738,   739,   740,   741,   742,   747,   478,   519,    17,
     395,  1096,  1093,  1133,   513,  1138,   314,   398,  1156,   359,
    1138,  1133,    55,  1125,    37,   110,   214,  1123,  1135,  1135,
    1093,  1158,   379,  1133,   710,   674,   713,     1,    21,    34,
      37,    38,    39,    40,    41,    42,    43,    73,    75,    76,
      77,    78,    79,    80,   115,   197,   213,   232,   249,   271,
     286,   293,   295,   308,   318,   325,   362,   364,   365,   366,
     388,   413,   414,   415,   426,   429,   628,   635,   636,   637,
     639,   640,   641,   642,   643,   644,   653,   654,   656,   657,
     658,   664,   665,  1133,  1149,    27,  1121,   184,  1134,  1093,
      56,   316,   598,   609,  1093,   367,  1150,   232,   606,  1090,
     606,   123,   449,   351,     3,     5,    10,    18,    51,    52,
      59,    70,    74,    86,   108,   115,   116,   146,   158,   162,
     175,   182,   185,   186,   193,   200,   202,   205,   242,   246,
     248,   255,   277,   292,   313,   322,   335,   340,   342,   350,
     360,   369,   378,   380,   381,   384,   386,   391,   406,   411,
     416,   427,   439,   449,   748,   749,   759,   764,   768,   771,
     784,   787,   792,   797,   798,   799,   802,   804,   811,   815,
     817,   832,   835,   837,   839,   842,   844,   850,   859,   861,
     878,   880,   883,   887,   893,   903,   910,   912,   915,   919,
     920,   931,   942,   952,   958,   961,   967,   971,   973,   975,
     977,   980,   991,   992,  1001,  1003,  1004,   449,   520,   522,
    1075,  1133,  1135,   120,   164,   549,  1133,   314,   321,   566,
    1133,  1133,   359,  1133,  1133,  1120,     9,   256,   313,   573,
    1133,   436,   675,   626,   633,   714,   715,   716,   221,   363,
     412,   363,   412,   363,   412,   363,   412,   363,   412,   432,
    1157,   341,  1146,  1093,  1089,  1090,  1090,   210,   220,   341,
     655,  1133,  1133,   164,   184,   219,   405,     9,    50,   221,
     632,  1094,  1095,  1096,   661,   662,  1094,    30,   610,   611,
     612,   613,  1122,  1158,  1126,   176,   601,  1131,   106,   232,
     743,   750,   760,   765,   769,   772,   785,   788,   793,   800,
     803,   805,   812,   816,   818,   833,   836,   838,  1156,   843,
       1,   845,   851,   860,   862,   879,   881,   884,   888,   894,
     904,   911,   913,   916,   921,   932,   943,   953,   232,   344,
     962,   968,   301,   972,   974,   976,   978,   981,   184,   993,
    1130,  1005,   191,   232,   239,   310,   373,   442,   521,   523,
     120,   311,   359,   552,  1133,   114,   300,   548,    32,   161,
     240,   562,  1074,   376,  1072,  1072,   282,  1143,  1143,   276,
    1072,    60,    87,    88,   288,   449,   676,   677,   681,  1133,
     629,   716,   442,   398,   645,   452,  1091,  1092,   395,   642,
    1094,    27,   638,   357,  1112,  1112,  1096,   272,  1140,  1140,
     456,   660,   662,   395,    48,   404,   171,   602,  1093,   449,
     449,   751,  1088,  1089,     6,    81,    92,    96,   180,   221,
     228,   234,   237,   269,   337,   382,   383,   407,   425,   433,
     761,  1058,  1078,  1079,  1088,  1094,  1097,   436,   766,  1045,
    1046,  1047,   232,  1068,  1069,  1070,  1090,   232,  1086,  1088,
    1097,   786,   789,   794,  1059,  1060,  1079,  1064,   400,   232,
     806,  1078,  1085,  1088,   813,  1079,   232,   399,   403,   819,
     820,  1045,   291,   292,   305,   351,   834,     6,  1076,  1077,
    1088,  1088,   840,   133,  1044,  1045,  1076,   680,  1088,   863,
    1088,  1094,  1097,   944,  1090,    92,   882,  1079,   885,  1079,
     889,   174,   232,   895,   898,   899,   900,  1068,  1086,  1090,
    1158,  1064,  1061,  1090,  1064,  1061,     9,   922,  1062,  1090,
     147,   244,   933,   934,   935,   936,   938,   939,   940,   941,
    1065,  1066,  1076,   944,  1064,   959,   109,   963,   964,  1079,
      92,   969,  1078,   680,  1088,  1064,  1088,     8,    35,   995,
     104,  1061,    17,  1072,   115,   232,   550,  1090,   435,   563,
     563,   371,   450,   557,  1072,  1073,  1133,   169,   678,   679,
     678,  1134,   689,   184,   717,  1093,   397,  1155,   221,   443,
     444,   452,  1055,  1057,  1058,  1080,  1088,  1095,  1097,   452,
    1092,  1090,   232,  1125,  1089,  1089,  1096,  1157,  1094,  1074,
    1074,  1122,  1126,   124,   758,    30,   176,   752,  1122,  1140,
     452,  1088,   452,  1098,   452,  1099,  1140,  1113,   452,   452,
     452,   452,   452,   452,   452,   452,  1098,   125,   763,   398,
     762,  1079,   201,  1107,    56,  1048,  1049,   398,  1113,   428,
     773,   232,  1085,  1088,  1064,   127,   795,   153,   450,   796,
    1060,   343,  1111,   314,  1145,  1063,   129,   810,   752,   421,
     422,   423,   424,   130,   814,    49,   206,   773,    17,   432,
     821,   822,   823,   827,  1118,    98,  1140,  1077,  1067,   394,
    1154,   852,  1158,  1088,    91,   326,   389,   864,   865,   866,
     870,   875,   946,  1079,   398,   134,   886,    49,   163,   203,
     211,   283,   890,   899,   135,   896,   417,   430,   395,   397,
     392,   254,   299,  1108,   176,  1006,  1145,  1006,  1062,   140,
     930,   430,   924,  1083,  1088,  1095,   939,   941,  1076,   398,
    1066,   118,   398,   418,   937,   954,   183,   336,   960,  1124,
     206,   964,  1088,   143,   970,   176,   176,   314,   316,   979,
     109,   982,   328,   375,   996,  1141,  1006,   523,   119,   435,
     557,  1106,  1115,   236,   342,  1133,   554,   555,  1085,   680,
     687,  1093,   626,   690,   718,   111,   646,  1140,  1057,  1057,
    1057,    69,   355,   451,  1056,   443,   444,   445,   446,   448,
     455,  1057,   360,  1147,  1137,  1074,   111,   600,  1083,    25,
      26,    66,    68,   100,   101,   102,   147,   149,   157,   230,
     396,   436,  1066,   435,   755,    65,   229,   296,   753,   754,
     146,   305,  1081,  1089,  1055,  1057,   398,  1057,  1055,  1100,
    1089,  1095,  1097,   436,  1057,  1103,  1057,  1057,  1102,  1057,
    1055,  1055,  1057,  1101,  1057,  1059,  1079,   183,   336,   767,
    1107,    12,    13,    14,    20,    58,   153,   154,   181,   187,
     210,   218,   222,   252,   253,   257,   267,   274,   279,   297,
     442,   443,   444,   445,   446,   448,   450,   451,   453,   454,
    1050,  1051,  1052,  1053,  1054,   210,   252,   257,   443,   444,
     448,   452,  1050,  1051,  1052,  1053,  1054,  1079,   304,   770,
    1070,   774,   183,   336,   778,   319,   410,   790,   791,  1158,
    1045,   209,   261,  1037,  1038,  1039,  1041,   420,   435,   807,
    1158,   160,  1012,  1013,  1012,  1012,  1012,  1079,  1059,  1079,
      21,   399,   403,   828,   829,  1046,   131,   831,   434,   823,
     825,   432,   824,   820,  1089,   111,   841,  1068,   846,     9,
      12,    15,    16,   249,   250,   267,   268,   853,   857,   168,
    1083,     9,    56,   170,   219,   405,   871,   872,   873,   867,
     865,   948,  1115,  1141,   398,  1076,  1059,  1079,   361,   891,
     744,   745,  1044,   901,   902,  1088,  1068,     8,    35,  1008,
    1145,  1085,   206,   905,   917,  1158,   925,  1122,  1088,   925,
     398,   398,   514,   146,   399,   403,  1079,    49,   214,   955,
    1079,  1079,   367,  1079,  1088,   176,  1059,  1079,  1083,  1124,
     206,   985,  1088,   156,   160,   997,     9,  1002,  1068,   917,
     119,   554,   275,   556,  1072,   556,   189,   682,   229,   230,
     688,   629,    31,    33,    36,    44,    45,    46,    65,   155,
     173,   176,   177,   190,   229,   238,   271,   285,   309,   333,
     338,   352,   398,   409,   428,   449,   640,   641,   643,   653,
     656,   658,   719,   722,  1141,   647,   648,  1089,  1095,  1097,
     451,  1057,  1057,  1057,  1057,  1057,  1057,   451,  1057,  1156,
    1137,  1141,  1011,  1013,   441,   440,  1083,  1011,   214,    31,
      33,    36,    46,   173,   177,   190,   238,   285,   309,   333,
     338,   348,   352,   409,   419,   756,   757,  1011,   265,  1139,
    1139,  1139,   754,   753,   232,  1082,  1089,   451,  1088,   455,
     451,  1056,   451,   451,  1056,   451,   451,   451,   451,  1056,
     451,   451,   368,  1017,  1018,  1059,  1077,   336,  1156,   393,
    1153,  1153,   398,  1068,   775,   776,   777,  1124,  1088,  1088,
     160,   284,   779,   998,  1130,   236,   256,  1017,  1040,  1042,
     128,   801,  1041,    94,   300,   436,  1066,    33,    36,    44,
      45,    46,   155,   173,   190,   238,   285,   338,   348,   409,
     808,   809,  1012,   264,  1014,   260,  1015,   183,  1017,   183,
    1118,   395,   830,   826,   828,   744,  1141,   744,  1156,   326,
     854,  1156,   398,    49,   872,   874,  1083,     9,    56,   219,
     405,   868,   869,  1083,   949,  1116,   196,   280,  1142,    28,
     112,   649,  1076,  1017,   183,  1158,  1063,   135,   897,   746,
       8,   176,   905,  1088,   123,   258,  1027,  1028,  1030,  1037,
     236,   256,   432,   123,   432,   927,   928,  1083,  1082,  1079,
    1133,  1037,   965,  1158,  1088,  1017,   183,   398,     9,   983,
     984,  1105,   986,  1088,   965,   986,   302,  1000,   303,  1007,
    1008,  1106,   247,   314,   316,   564,  1133,   170,   683,  1093,
     691,  1133,  1139,   150,   152,  1133,  1086,  1139,  1093,  1088,
    1088,  1072,   198,   650,   649,   451,   399,   663,  1072,  1015,
    1011,  1133,  1133,   118,   418,   757,  1085,  1085,  1085,  1098,
    1111,   451,  1057,  1072,  1098,  1098,  1057,  1098,  1098,  1098,
     219,   405,  1098,  1098,  1019,   263,  1020,  1017,  1077,   153,
     279,   153,   279,   776,   274,   732,    85,   320,   429,   260,
     262,   781,   999,   780,   324,   339,   744,   744,   807,   807,
     807,   807,  1133,   150,   152,  1133,   118,   418,   809,   744,
    1016,  1059,  1060,  1059,  1060,   829,  1045,   744,  1088,   122,
     847,   429,   855,   856,   857,   107,   858,   429,  1084,  1088,
    1094,  1083,    49,   876,   869,   172,   876,   945,  1133,   280,
    1135,  1059,   573,   892,  1158,   747,   902,  1079,   195,   906,
    1158,  1029,  1031,   138,   914,  1030,   139,   918,   236,  1045,
     926,  1044,   927,   257,   956,  1109,   141,   957,   284,  1022,
    1023,   295,  1111,  1059,  1084,   279,  1083,   110,   987,   389,
     989,  1141,   151,   259,  1009,  1032,  1033,  1035,  1038,     7,
    1117,   564,  1093,   113,   216,   684,    66,    65,    66,   188,
     229,   230,   254,   298,   371,   385,   408,   430,   449,   640,
     641,   643,   644,   653,   656,   658,   692,   693,   695,   696,
     697,   698,   700,   701,   702,   703,   707,   708,   442,  1087,
    1088,  1093,  1133,  1087,  1133,  1155,  1124,  1135,  1133,  1087,
    1087,  1043,  1124,  1043,  1017,   451,   744,  1021,  1156,   153,
    1156,   153,  1079,   126,   783,   782,   744,  1012,  1012,  1012,
    1012,  1087,  1087,  1043,  1043,   744,  1017,   323,  1017,   323,
     848,   133,   849,   856,    99,  1128,   876,   876,  1084,  1008,
     203,   428,   950,  1072,   947,  1017,   236,   256,    49,   236,
     214,   907,   194,   236,   256,   431,   744,   744,   923,   744,
     929,   680,  1050,  1051,  1052,  1053,  1054,  1024,   142,   966,
     262,  1025,  1088,  1017,  1017,   984,  1132,    93,   988,  1132,
    1022,   163,   203,   211,   283,   994,  1063,  1034,  1036,   145,
    1010,  1035,   288,  1066,  1087,  1133,    90,   217,   685,   266,
    1139,   199,   709,   265,   266,   706,  1119,   188,   432,  1133,
    1140,  1133,  1088,   698,   254,   294,   704,   705,  1093,   243,
     294,   443,   444,   721,   243,   294,   443,   444,   720,   436,
     651,   652,  1133,  1094,  1087,   744,  1156,  1156,   744,  1060,
    1060,   744,    49,   876,   401,   877,   302,  1063,   183,   283,
     951,  1090,   339,  1079,  1133,   908,  1027,  1038,   236,   236,
     744,   744,   744,  1026,  1088,  1132,  1088,   144,   990,   744,
     744,   229,   230,  1136,  1093,  1133,  1133,   171,   686,  1133,
    1134,  1133,  1044,  1088,   699,  1072,    89,    90,   113,   289,
     290,   330,   331,   694,   176,   288,  1093,   705,  1087,  1087,
     652,  1071,  1136,  1017,  1017,  1079,  1079,  1133,  1063,   302,
     417,   680,   137,   909,   744,  1088,  1093,  1093,  1133,  1093,
    1093,  1111,  1079,   898,  1133,  1044,  1093,    49,   898,  1079
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
#line 765 "parser.y"
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
#line 789 "parser.y"
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
#line 818 "parser.y"
    { cb_validate_program_environment (current_program); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 819 "parser.y"
    { cb_validate_program_data (current_program); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 827 "parser.y"
    { cb_validate_program_environment (current_program); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 828 "parser.y"
    { cb_validate_program_data (current_program); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 836 "parser.y"
    { cb_validate_program_environment (current_program); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 837 "parser.y"
    { cb_validate_program_data (current_program); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 849 "parser.y"
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
#line 875 "parser.y"
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
#line 899 "parser.y"
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
#line 928 "parser.y"
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
#line 969 "parser.y"
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
#line 1017 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 1018 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 1027 "parser.y"
    {
	if (!current_program->nested_level) {
		cb_error (_("COMMON may only be used in a nested program"));
	}
	current_program->flag_common = 1;
  ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 1034 "parser.y"
    {
	if (!current_program->nested_level) {
		cb_error (_("COMMON may only be used in a nested program"));
	}
	current_program->flag_common = 1;
  ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 1045 "parser.y"
    {
	current_program->flag_initial = 1;
  ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 1049 "parser.y"
    {
	current_program->flag_recursive = 1;
	current_program->flag_initial = 1;
  ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 1074 "parser.y"
    {
	if (current_program->nested_level) {
		cb_error (_("CONFIGURATION SECTION not allowed in nested programs"));
	}
  ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 1109 "parser.y"
    {
	cb_verify (cb_debugging_line, "DEBUGGING MODE");
  ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 1115 "parser.y"
    { ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 1146 "parser.y"
    {
	cb_verify (cb_memory_size_clause, "MEMORY SIZE");
  ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 1158 "parser.y"
    {
	current_program->collating_sequence = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1165 "parser.y"
    {
	/* Ignore */
  ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 1190 "parser.y"
    {
	current_program->function_spec_list = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 1194 "parser.y"
    {
	functions_are_all = 1;
  ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1200 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1202 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1243 "parser.y"
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

  case 97:

/* Line 1455 of yacc.c  */
#line 1253 "parser.y"
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

  case 99:

/* Line 1455 of yacc.c  */
#line 1264 "parser.y"
    {
	save_tree_1 = lookup_system_name (CB_NAME ((yyvsp[(1) - (2)])));
	if (save_tree_1 == cb_error_node) {
		cb_error_x ((yyvsp[(1) - (2)]), _("Unknown system-name '%s'"), CB_NAME ((yyvsp[(1) - (2)])));
	}
	save_tree_2 = NULL;
  ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 1273 "parser.y"
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

  case 102:

/* Line 1455 of yacc.c  */
#line 1287 "parser.y"
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

  case 103:

/* Line 1455 of yacc.c  */
#line 1301 "parser.y"
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

  case 104:

/* Line 1455 of yacc.c  */
#line 1315 "parser.y"
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

  case 109:

/* Line 1455 of yacc.c  */
#line 1341 "parser.y"
    {
	if (!save_tree_2 && !cb_switch_no_mnemonic) {
		cb_error_x ((yyvsp[(4) - (4)]), _("'%s' with no mnemonic name"), CB_NAME ((yyvsp[(4) - (4)])));
	} else {
		cb_define_switch_name ((yyvsp[(4) - (4)]), save_tree_1, (yyvsp[(1) - (4)]), save_tree_2);
	}
  ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1351 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1352 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1360 "parser.y"
    {
	save_tree_1 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1364 "parser.y"
    {
	current_program->alphabet_name_list =
		cb_list_add (current_program->alphabet_name_list, (yyvsp[(5) - (5)]));
  ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1371 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_NATIVE); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1372 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_1); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1373 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_2); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1374 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_EBCDIC); ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1376 "parser.y"
    {
	(yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_CUSTOM);
	CB_ALPHABET_NAME ((yyval))->custom_list = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1383 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1385 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1389 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1390 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1392 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (2)]));
	save_tree_2 = (yyval);
  ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1397 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (4)]);
  ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1408 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1409 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1410 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1411 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1412 "parser.y"
    { (yyval) = cb_norm_high; ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1413 "parser.y"
    { (yyval) = cb_norm_low; ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1417 "parser.y"
    { cb_list_add (save_tree_2, (yyvsp[(1) - (1)])); ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1418 "parser.y"
    { cb_list_add (save_tree_2, cb_space); ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1419 "parser.y"
    { cb_list_add (save_tree_2, cb_zero); ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1420 "parser.y"
    { cb_list_add (save_tree_2, cb_quote); ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1421 "parser.y"
    { cb_list_add (save_tree_2, cb_norm_high); ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1422 "parser.y"
    { cb_list_add (save_tree_2, cb_norm_low); ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1430 "parser.y"
    {
	if ((yyvsp[(3) - (3)])) {
		current_program->symbolic_list =
			cb_list_add (current_program->symbolic_list, (yyvsp[(3) - (3)]));
	}
	PENDING ("SYMBOLIC CHARACTERS");
  ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1441 "parser.y"
    {
	if (cb_list_length ((yyvsp[(1) - (3)])) != cb_list_length ((yyvsp[(3) - (3)]))) {
		cb_error (_("Invalid SYMBOLIC clause"));
		(yyval) = NULL;
	} else {
		(yyval) = NULL;
	}
  ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1452 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1453 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1457 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1458 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1466 "parser.y"
    {
	current_program->class_name_list =
			cb_list_add (current_program->class_name_list,
			cb_build_class_name ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])));
  ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1474 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1475 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1479 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1481 "parser.y"
    {
	/* if (CB_LITERAL ($1)->data[0] < CB_LITERAL ($3)->data[0]) */
	if (literal_value ((yyvsp[(1) - (3)])) < literal_value ((yyvsp[(3) - (3)]))) {
		(yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	} else {
		(yyval) = cb_build_pair ((yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]));
	}
  ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1495 "parser.y"
    {
	cb_tree	l;

	l = cb_build_locale_name ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
	if (l != cb_error_node) {
		current_program->locale_list =
			cb_list_add (current_program->locale_list, l);
	}
  ;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 1510 "parser.y"
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

  case 152:

/* Line 1455 of yacc.c  */
#line 1577 "parser.y"
    {
	current_program->decimal_point = ',';
	current_program->numeric_separator = '.';
  ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1587 "parser.y"
    { current_program->cursor_pos = (yyvsp[(3) - (3)]); ;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 1594 "parser.y"
    { current_program->crt_status = (yyvsp[(4) - (4)]); ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1601 "parser.y"
    {  PENDING ("SCREEN CONTROL"); ;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 1607 "parser.y"
    {  PENDING ("EVENT STATUS"); ;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 1619 "parser.y"
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
#line 1628 "parser.y"
    {
	/* hack for MF compatibility */
	if (cb_relaxed_syntax_check) {
		cb_warning (_("INPUT-OUTPUT SECTION header missing - assumed"));
	} else {
		cb_error (_("INPUT-OUTPUT SECTION header missing"));
	}
  ;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1653 "parser.y"
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

  case 168:

/* Line 1455 of yacc.c  */
#line 1668 "parser.y"
    {
	validate_file (current_file, (yyvsp[(3) - (6)]));
  ;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1699 "parser.y"
    {
	current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
  ;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1703 "parser.y"
    {
	current_file->fileid_assign = 1;
	current_file->assign = cb_build_assignment_name (current_file, cb_build_reference ("DISK"));
  ;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1708 "parser.y"
    {
	current_file->fileid_assign = 1;
	current_file->assign = cb_build_assignment_name (current_file, cb_build_reference ("PRINTER"));
  ;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1716 "parser.y"
    { current_file->organization = COB_ORG_LINE_SEQUENTIAL; ;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1721 "parser.y"
    {
	current_file->external_assign = 1;
  ;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1725 "parser.y"
    {
	current_file->external_assign = 0;
  ;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1733 "parser.y"
    {
	const char	*s;

	s = "$#@DUMMY@#$";
	(yyval) = cb_build_alphanumeric_literal ((unsigned char *)s, strlen (s));
  ;}
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 1750 "parser.y"
    { current_file->access_mode = COB_ACCESS_SEQUENTIAL; ;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1751 "parser.y"
    { current_file->access_mode = COB_ACCESS_DYNAMIC; ;}
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 1752 "parser.y"
    { current_file->access_mode = COB_ACCESS_RANDOM; ;}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 1760 "parser.y"
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

  case 202:

/* Line 1455 of yacc.c  */
#line 1780 "parser.y"
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

  case 203:

/* Line 1455 of yacc.c  */
#line 1826 "parser.y"
    {
	key_component_list = NULL;
  ;}
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 1835 "parser.y"
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

  case 207:

/* Line 1455 of yacc.c  */
#line 1850 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 1851 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1852 "parser.y"
    { (yyval) = cb_int('='); ;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1859 "parser.y"
    {
	PENDING ("COLLATING SEQUENCE");
  ;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1869 "parser.y"
    {
	current_file->file_status = (yyvsp[(4) - (5)]);
	if ((yyvsp[(5) - (5)])) {
		PENDING ("2nd FILE STATUS");
	}
  ;}
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 1890 "parser.y"
    { current_file->lock_mode = COB_LOCK_MANUAL; ;}
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 1891 "parser.y"
    { current_file->lock_mode = COB_LOCK_AUTOMATIC; ;}
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 1892 "parser.y"
    { current_file->lock_mode = COB_LOCK_EXCLUSIVE; ;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 1898 "parser.y"
    {
	current_file->lock_mode |= COB_LOCK_MULTIPLE;
  ;}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 1901 "parser.y"
    { PENDING ("WITH ROLLBACK"); ;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1918 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_INDEXED;
		organized_seen = 1;
	}
  ;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 1927 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_SEQUENTIAL;
		organized_seen = 1;
	}
  ;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 1936 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = cb_default_organization;
		organized_seen = 1;
	}
  ;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 1945 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_RELATIVE;
		organized_seen = 1;
	}
  ;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 1954 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_LINE_SEQUENTIAL;
		organized_seen = 1;
	}
  ;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 1969 "parser.y"
    {
	cb_verify (cb_padding_character_clause, "PADDING CHARACTER");
  ;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 1978 "parser.y"
    { /* ignored */ ;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 1986 "parser.y"
    {
	current_file->key = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 1990 "parser.y"
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

  case 236:

/* Line 1455 of yacc.c  */
#line 2027 "parser.y"
    { current_file->key = (yyvsp[(4) - (4)]); ;}
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 2034 "parser.y"
    { /* ignored */ ;}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 2041 "parser.y"
    { current_file->sharing = (yyvsp[(3) - (3)]); ;}
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 2045 "parser.y"
    { (yyval) = NULL; PENDING ("SHARING ALL OTHER"); ;}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 2046 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 2047 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 2078 "parser.y"
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

  case 252:

/* Line 1455 of yacc.c  */
#line 2102 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 2103 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 2104 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 2105 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 2112 "parser.y"
    {
	cb_verify (cb_multiple_file_tape_clause, "MULTIPLE FILE TAPE");
  ;}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 2123 "parser.y"
    { ;}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 2134 "parser.y"
    {
	PENDING ("APPLY COMMITMENT-CONTROL");
  ;}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 2159 "parser.y"
    { current_storage = CB_STORAGE_FILE; ;}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 2162 "parser.y"
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

  case 272:

/* Line 1455 of yacc.c  */
#line 2181 "parser.y"
    {
	if ((yyvsp[(3) - (3)]) && (yyvsp[(3) - (3)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(3) - (3)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 2193 "parser.y"
    {
	if ((yyvsp[(2) - (2)]) && (yyvsp[(2) - (2)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(2) - (2)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 2204 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 2205 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 2215 "parser.y"
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

  case 278:

/* Line 1455 of yacc.c  */
#line 2226 "parser.y"
    {
	/* Shut up bison */
	dummy_tree = (yyvsp[(2) - (4)]);
  ;}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 2238 "parser.y"
    {
	if (current_file->global) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->external = 1;
  ;}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 2245 "parser.y"
    {
	if (current_file->external) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->global = 1;
  ;}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 2268 "parser.y"
    { /* ignored */ ;}
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 2278 "parser.y"
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

  case 298:

/* Line 1455 of yacc.c  */
#line 2290 "parser.y"
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

  case 299:

/* Line 1455 of yacc.c  */
#line 2316 "parser.y"
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

  case 301:

/* Line 1455 of yacc.c  */
#line 2340 "parser.y"
    {
	current_file->record_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 2346 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 2347 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 2351 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 2352 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 2360 "parser.y"
    {
	cb_verify (cb_label_records_clause, "LABEL RECORDS");
  ;}
    break;

  case 309:

/* Line 1455 of yacc.c  */
#line 2375 "parser.y"
    {
	cb_verify (cb_value_of_clause, "VALUE OF");
  ;}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 2379 "parser.y"
    {
	if (!current_file->assign) {
		current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 2395 "parser.y"
    {
	cb_verify (cb_data_records_clause, "DATA RECORDS");
  ;}
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 2406 "parser.y"
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

  case 320:

/* Line 1455 of yacc.c  */
#line 2434 "parser.y"
    {
	current_file->latfoot = (yyvsp[(4) - (5)]);
  ;}
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 2441 "parser.y"
    {
	current_file->lattop = (yyvsp[(3) - (4)]);
  ;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 2448 "parser.y"
    {
	current_file->latbot = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 2457 "parser.y"
    { /* ignore */ ;}
    break;

  case 324:

/* Line 1455 of yacc.c  */
#line 2465 "parser.y"
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

  case 325:

/* Line 1455 of yacc.c  */
#line 2483 "parser.y"
    {
	cb_warning (_("file descriptor REPORT IS"));
  ;}
    break;

  case 326:

/* Line 1455 of yacc.c  */
#line 2487 "parser.y"
    {
	cb_warning (_("file descriptor REPORTS ARE"));
  ;}
    break;

  case 328:

/* Line 1455 of yacc.c  */
#line 2498 "parser.y"
    { current_storage = CB_STORAGE_WORKING; ;}
    break;

  case 329:

/* Line 1455 of yacc.c  */
#line 2500 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->working_storage =
			cb_field_add (current_program->working_storage, CB_FIELD ((yyvsp[(5) - (5)])));
	}
  ;}
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 2509 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 2510 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 2514 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 2520 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	(yyval) = CB_TREE (description_field);
  ;}
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 2540 "parser.y"
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

  case 339:

/* Line 1455 of yacc.c  */
#line 2551 "parser.y"
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
  ;}
    break;

  case 340:

/* Line 1455 of yacc.c  */
#line 2564 "parser.y"
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

  case 341:

/* Line 1455 of yacc.c  */
#line 2575 "parser.y"
    {
	if (!qualifier) {
		cb_error (_("Item requires a data name"));
	}
	cb_validate_88_item (current_field);
	if (!description_field) {
		description_field = current_field;
	}
	
  ;}
    break;

  case 345:

/* Line 1455 of yacc.c  */
#line 2602 "parser.y"
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
  ;}
    break;

  case 346:

/* Line 1455 of yacc.c  */
#line 2623 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 347:

/* Line 1455 of yacc.c  */
#line 2629 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 348:

/* Line 1455 of yacc.c  */
#line 2635 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 349:

/* Line 1455 of yacc.c  */
#line 2644 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 351:

/* Line 1455 of yacc.c  */
#line 2653 "parser.y"
    {
	current_field->flag_is_global = 1;
	cb_error (_("CONSTANT with GLOBAL clause is not yet supported"));
  ;}
    break;

  case 352:

/* Line 1455 of yacc.c  */
#line 2660 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 353:

/* Line 1455 of yacc.c  */
#line 2661 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 354:

/* Line 1455 of yacc.c  */
#line 2662 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 355:

/* Line 1455 of yacc.c  */
#line 2667 "parser.y"
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

  case 356:

/* Line 1455 of yacc.c  */
#line 2686 "parser.y"
    {
	/* required to check redefines */
	(yyval) = NULL;
  ;}
    break;

  case 357:

/* Line 1455 of yacc.c  */
#line 2692 "parser.y"
    {
	/* required to check redefines */
	(yyval) = cb_true;
  ;}
    break;

  case 373:

/* Line 1455 of yacc.c  */
#line 2721 "parser.y"
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

  case 374:

/* Line 1455 of yacc.c  */
#line 2743 "parser.y"
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

  case 375:

/* Line 1455 of yacc.c  */
#line 2764 "parser.y"
    { current_field->ename = NULL; ;}
    break;

  case 376:

/* Line 1455 of yacc.c  */
#line 2766 "parser.y"
    {
	struct cb_field *x;

	x = CB_FIELD(cb_build_field (cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(2) - (2)]))->data))));
	current_field->ename = x->name;
 ;}
    break;

  case 377:

/* Line 1455 of yacc.c  */
#line 2778 "parser.y"
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

  case 378:

/* Line 1455 of yacc.c  */
#line 2797 "parser.y"
    { current_field->pic = CB_PICTURE ((yyvsp[(1) - (1)])); ;}
    break;

  case 381:

/* Line 1455 of yacc.c  */
#line 2809 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 382:

/* Line 1455 of yacc.c  */
#line 2810 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 383:

/* Line 1455 of yacc.c  */
#line 2811 "parser.y"
    { current_field->usage = CB_USAGE_FLOAT; ;}
    break;

  case 384:

/* Line 1455 of yacc.c  */
#line 2812 "parser.y"
    { current_field->usage = CB_USAGE_DOUBLE; ;}
    break;

  case 385:

/* Line 1455 of yacc.c  */
#line 2813 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 386:

/* Line 1455 of yacc.c  */
#line 2814 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 387:

/* Line 1455 of yacc.c  */
#line 2815 "parser.y"
    { current_field->usage = CB_USAGE_COMP_5; ;}
    break;

  case 388:

/* Line 1455 of yacc.c  */
#line 2816 "parser.y"
    { current_field->usage = CB_USAGE_COMP_X; ;}
    break;

  case 389:

/* Line 1455 of yacc.c  */
#line 2817 "parser.y"
    { current_field->usage = CB_USAGE_DISPLAY; ;}
    break;

  case 390:

/* Line 1455 of yacc.c  */
#line 2818 "parser.y"
    { current_field->usage = CB_USAGE_INDEX; ;}
    break;

  case 391:

/* Line 1455 of yacc.c  */
#line 2819 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 392:

/* Line 1455 of yacc.c  */
#line 2821 "parser.y"
    {
	current_field->usage = CB_USAGE_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 393:

/* Line 1455 of yacc.c  */
#line 2826 "parser.y"
    {
	current_field->usage = CB_USAGE_PROGRAM_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 394:

/* Line 1455 of yacc.c  */
#line 2830 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 395:

/* Line 1455 of yacc.c  */
#line 2831 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 396:

/* Line 1455 of yacc.c  */
#line 2832 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 397:

/* Line 1455 of yacc.c  */
#line 2833 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 398:

/* Line 1455 of yacc.c  */
#line 2834 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 399:

/* Line 1455 of yacc.c  */
#line 2835 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 400:

/* Line 1455 of yacc.c  */
#line 2836 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 401:

/* Line 1455 of yacc.c  */
#line 2837 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_CHAR; ;}
    break;

  case 402:

/* Line 1455 of yacc.c  */
#line 2838 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 403:

/* Line 1455 of yacc.c  */
#line 2839 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 404:

/* Line 1455 of yacc.c  */
#line 2840 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 405:

/* Line 1455 of yacc.c  */
#line 2841 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 406:

/* Line 1455 of yacc.c  */
#line 2842 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 407:

/* Line 1455 of yacc.c  */
#line 2843 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 408:

/* Line 1455 of yacc.c  */
#line 2844 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 409:

/* Line 1455 of yacc.c  */
#line 2845 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 410:

/* Line 1455 of yacc.c  */
#line 2846 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 411:

/* Line 1455 of yacc.c  */
#line 2847 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 412:

/* Line 1455 of yacc.c  */
#line 2849 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  ;}
    break;

  case 413:

/* Line 1455 of yacc.c  */
#line 2857 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_UNSIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_UNSIGNED_LONG;
	}
  ;}
    break;

  case 414:

/* Line 1455 of yacc.c  */
#line 2865 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  ;}
    break;

  case 415:

/* Line 1455 of yacc.c  */
#line 2872 "parser.y"
    { PENDING ("USAGE NATIONAL");;}
    break;

  case 416:

/* Line 1455 of yacc.c  */
#line 2880 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 1;
  ;}
    break;

  case 417:

/* Line 1455 of yacc.c  */
#line 2885 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 0;
  ;}
    break;

  case 418:

/* Line 1455 of yacc.c  */
#line 2897 "parser.y"
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

  case 419:

/* Line 1455 of yacc.c  */
#line 2912 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 420:

/* Line 1455 of yacc.c  */
#line 2913 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 422:

/* Line 1455 of yacc.c  */
#line 2918 "parser.y"
    {
	current_field->occurs_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 423:

/* Line 1455 of yacc.c  */
#line 2925 "parser.y"
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

  case 424:

/* Line 1455 of yacc.c  */
#line 2948 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 425:

/* Line 1455 of yacc.c  */
#line 2951 "parser.y"
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

  case 426:

/* Line 1455 of yacc.c  */
#line 2966 "parser.y"
    { (yyval) = cb_int (COB_ASCENDING); ;}
    break;

  case 427:

/* Line 1455 of yacc.c  */
#line 2967 "parser.y"
    { (yyval) = cb_int (COB_DESCENDING); ;}
    break;

  case 429:

/* Line 1455 of yacc.c  */
#line 2972 "parser.y"
    {
	current_field->index_list = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 430:

/* Line 1455 of yacc.c  */
#line 2978 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 431:

/* Line 1455 of yacc.c  */
#line 2980 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 432:

/* Line 1455 of yacc.c  */
#line 2985 "parser.y"
    {
	(yyval) = cb_build_index ((yyvsp[(1) - (1)]), cb_int1, 1, current_field);
  ;}
    break;

  case 433:

/* Line 1455 of yacc.c  */
#line 2994 "parser.y"
    { current_field->flag_justified = 1; ;}
    break;

  case 434:

/* Line 1455 of yacc.c  */
#line 3001 "parser.y"
    { current_field->flag_synchronized = 1; ;}
    break;

  case 438:

/* Line 1455 of yacc.c  */
#line 3013 "parser.y"
    { current_field->flag_blank_zero = 1; ;}
    break;

  case 439:

/* Line 1455 of yacc.c  */
#line 3021 "parser.y"
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

  case 440:

/* Line 1455 of yacc.c  */
#line 3045 "parser.y"
    { current_field->values = cb_list_init ((yyvsp[(3) - (3)])); ;}
    break;

  case 441:

/* Line 1455 of yacc.c  */
#line 3049 "parser.y"
    { current_field->values = (yyvsp[(3) - (3)]); ;}
    break;

  case 443:

/* Line 1455 of yacc.c  */
#line 3054 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 444:

/* Line 1455 of yacc.c  */
#line 3055 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 445:

/* Line 1455 of yacc.c  */
#line 3059 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 446:

/* Line 1455 of yacc.c  */
#line 3060 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 448:

/* Line 1455 of yacc.c  */
#line 3065 "parser.y"
    {
	if (current_field->level != 88) {
		cb_error (_("FALSE clause only allowed for 88 level"));
	}
	current_field->false_88 = cb_list_init ((yyvsp[(3) - (3)]));
  ;}
    break;

  case 449:

/* Line 1455 of yacc.c  */
#line 3078 "parser.y"
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

  case 450:

/* Line 1455 of yacc.c  */
#line 3090 "parser.y"
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

  case 451:

/* Line 1455 of yacc.c  */
#line 3110 "parser.y"
    {
	if (current_field->flag_item_based) {
		cb_error (_("BASED and ANY LENGTH are mutually exclusive"));
	} else {
		current_field->flag_any_length = 1;
	}
  ;}
    break;

  case 453:

/* Line 1455 of yacc.c  */
#line 3125 "parser.y"
    {
	current_storage = CB_STORAGE_LOCAL;
	if (current_program->nested_level) {
		cb_error (_("LOCAL-STORAGE not allowed in nested programs"));
	}
  ;}
    break;

  case 454:

/* Line 1455 of yacc.c  */
#line 3132 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->local_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 456:

/* Line 1455 of yacc.c  */
#line 3145 "parser.y"
    { current_storage = CB_STORAGE_LINKAGE; ;}
    break;

  case 457:

/* Line 1455 of yacc.c  */
#line 3147 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->linkage_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 459:

/* Line 1455 of yacc.c  */
#line 3160 "parser.y"
    {
	cb_error (_("REPORT SECTION not supported"));
	current_storage = CB_STORAGE_REPORT;
  ;}
    break;

  case 466:

/* Line 1455 of yacc.c  */
#line 3193 "parser.y"
    {
	cb_warning (_("Report description using defaults"));
  ;}
    break;

  case 468:

/* Line 1455 of yacc.c  */
#line 3201 "parser.y"
    {
	cb_error (_("GLOBAL is not allowed with RD"));
  ;}
    break;

  case 477:

/* Line 1455 of yacc.c  */
#line 3224 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 478:

/* Line 1455 of yacc.c  */
#line 3225 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 500:

/* Line 1455 of yacc.c  */
#line 3281 "parser.y"
    { cb_warning (_("looking for Report line TYPE")); ;}
    break;

  case 551:

/* Line 1455 of yacc.c  */
#line 3386 "parser.y"
    { current_storage = CB_STORAGE_SCREEN; ;}
    break;

  case 552:

/* Line 1455 of yacc.c  */
#line 3387 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 553:

/* Line 1455 of yacc.c  */
#line 3393 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	current_program->screen_storage = description_field;
	current_program->flag_screen = 1;
  ;}
    break;

  case 559:

/* Line 1455 of yacc.c  */
#line 3417 "parser.y"
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

  case 560:

/* Line 1455 of yacc.c  */
#line 3433 "parser.y"
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

  case 563:

/* Line 1455 of yacc.c  */
#line 3457 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 564:

/* Line 1455 of yacc.c  */
#line 3458 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 565:

/* Line 1455 of yacc.c  */
#line 3459 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BELL; ;}
    break;

  case 566:

/* Line 1455 of yacc.c  */
#line 3460 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLINK; ;}
    break;

  case 567:

/* Line 1455 of yacc.c  */
#line 3461 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 568:

/* Line 1455 of yacc.c  */
#line 3462 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 569:

/* Line 1455 of yacc.c  */
#line 3463 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 570:

/* Line 1455 of yacc.c  */
#line 3464 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 571:

/* Line 1455 of yacc.c  */
#line 3465 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REVERSE; ;}
    break;

  case 572:

/* Line 1455 of yacc.c  */
#line 3466 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 573:

/* Line 1455 of yacc.c  */
#line 3467 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_OVERLINE; ;}
    break;

  case 574:

/* Line 1455 of yacc.c  */
#line 3468 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_AUTO; ;}
    break;

  case 575:

/* Line 1455 of yacc.c  */
#line 3469 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_SECURE; ;}
    break;

  case 576:

/* Line 1455 of yacc.c  */
#line 3470 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REQUIRED; ;}
    break;

  case 577:

/* Line 1455 of yacc.c  */
#line 3471 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_FULL; ;}
    break;

  case 578:

/* Line 1455 of yacc.c  */
#line 3472 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_PROMPT; ;}
    break;

  case 579:

/* Line 1455 of yacc.c  */
#line 3474 "parser.y"
    {
	current_field->screen_line = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 580:

/* Line 1455 of yacc.c  */
#line 3478 "parser.y"
    {
	current_field->screen_column = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 581:

/* Line 1455 of yacc.c  */
#line 3482 "parser.y"
    {
	current_field->screen_foreg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 582:

/* Line 1455 of yacc.c  */
#line 3486 "parser.y"
    {
	current_field->screen_backg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 590:

/* Line 1455 of yacc.c  */
#line 3497 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 591:

/* Line 1455 of yacc.c  */
#line 3504 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 592:

/* Line 1455 of yacc.c  */
#line 3508 "parser.y"
    {
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 593:

/* Line 1455 of yacc.c  */
#line 3517 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 594:

/* Line 1455 of yacc.c  */
#line 3521 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 595:

/* Line 1455 of yacc.c  */
#line 3525 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 596:

/* Line 1455 of yacc.c  */
#line 3529 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 597:

/* Line 1455 of yacc.c  */
#line 3533 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 598:

/* Line 1455 of yacc.c  */
#line 3540 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 599:

/* Line 1455 of yacc.c  */
#line 3544 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 600:

/* Line 1455 of yacc.c  */
#line 3548 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 601:

/* Line 1455 of yacc.c  */
#line 3552 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 602:

/* Line 1455 of yacc.c  */
#line 3556 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 603:

/* Line 1455 of yacc.c  */
#line 3564 "parser.y"
    {
	current_field->occurs_max = cb_get_int ((yyvsp[(2) - (3)]));
	current_field->occurs_min = current_field->occurs_max;
	current_field->indexes++;
	current_field->flag_occurs = 1;
  ;}
    break;

  case 605:

/* Line 1455 of yacc.c  */
#line 3578 "parser.y"
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

  case 606:

/* Line 1455 of yacc.c  */
#line 3588 "parser.y"
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

  case 607:

/* Line 1455 of yacc.c  */
#line 3598 "parser.y"
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

  case 608:

/* Line 1455 of yacc.c  */
#line 3615 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 609:

/* Line 1455 of yacc.c  */
#line 3617 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 610:

/* Line 1455 of yacc.c  */
#line 3621 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 611:

/* Line 1455 of yacc.c  */
#line 3623 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	current_program->flag_chained = 1;
  ;}
    break;

  case 612:

/* Line 1455 of yacc.c  */
#line 3627 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 613:

/* Line 1455 of yacc.c  */
#line 3631 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 614:

/* Line 1455 of yacc.c  */
#line 3633 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 615:

/* Line 1455 of yacc.c  */
#line 3638 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), cb_build_identifier ((yyvsp[(4) - (4)])));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 617:

/* Line 1455 of yacc.c  */
#line 3647 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 618:

/* Line 1455 of yacc.c  */
#line 3651 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 620:

/* Line 1455 of yacc.c  */
#line 3663 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_AUTO;
	}
  ;}
    break;

  case 621:

/* Line 1455 of yacc.c  */
#line 3671 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_4;
	}
  ;}
    break;

  case 622:

/* Line 1455 of yacc.c  */
#line 3679 "parser.y"
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

  case 623:

/* Line 1455 of yacc.c  */
#line 3708 "parser.y"
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

  case 625:

/* Line 1455 of yacc.c  */
#line 3741 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OPTIONAL only allowed for BY REFERENCE items"));
	}
  ;}
    break;

  case 626:

/* Line 1455 of yacc.c  */
#line 3750 "parser.y"
    {
	if (current_program->prog_type == CB_FUNCTION_TYPE) {
		cb_error (_("RETURNING clause is required for a FUNCTION"));
	}
  ;}
    break;

  case 627:

/* Line 1455 of yacc.c  */
#line 3756 "parser.y"
    {
	if (cb_ref ((yyvsp[(2) - (2)])) != cb_error_node) {
		current_program->returning = (yyvsp[(2) - (2)]);
		if (cb_field ((yyvsp[(2) - (2)]))->storage != CB_STORAGE_LINKAGE) {
			cb_error (_("RETURNING item is not defined in LINKAGE SECTION"));
		}
	}
  ;}
    break;

  case 629:

/* Line 1455 of yacc.c  */
#line 3767 "parser.y"
    { in_declaratives = 1; ;}
    break;

  case 630:

/* Line 1455 of yacc.c  */
#line 3770 "parser.y"
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

  case 636:

/* Line 1455 of yacc.c  */
#line 3803 "parser.y"
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
  ;}
    break;

  case 637:

/* Line 1455 of yacc.c  */
#line 3819 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 638:

/* Line 1455 of yacc.c  */
#line 3831 "parser.y"
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

  case 639:

/* Line 1455 of yacc.c  */
#line 3862 "parser.y"
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

  case 640:

/* Line 1455 of yacc.c  */
#line 3899 "parser.y"
    {
	non_const_word = 0;
	check_unreached = 0;
	if ((yyvsp[(1) - (1)]) != cb_error_node) {
		cb_error_x ((yyvsp[(1) - (1)]), _("Unknown statement '%s'"), CB_NAME ((yyvsp[(1) - (1)])));
	}
	YYERROR;
  ;}
    break;

  case 641:

/* Line 1455 of yacc.c  */
#line 3910 "parser.y"
    { (yyval) = cb_build_section_name ((yyvsp[(1) - (1)]), 0); ;}
    break;

  case 643:

/* Line 1455 of yacc.c  */
#line 3914 "parser.y"
    { /* ignore */ ;}
    break;

  case 644:

/* Line 1455 of yacc.c  */
#line 3923 "parser.y"
    {
	(yyval) = current_program->exec_list;
	current_program->exec_list = NULL;
  ;}
    break;

  case 645:

/* Line 1455 of yacc.c  */
#line 3927 "parser.y"
    {
	(yyval) = CB_TREE (current_statement);
	current_statement = NULL;
  ;}
    break;

  case 646:

/* Line 1455 of yacc.c  */
#line 3932 "parser.y"
    {
	(yyval) = cb_list_reverse (current_program->exec_list);
	current_program->exec_list = (yyvsp[(1) - (3)]);
	current_statement = CB_STATEMENT ((yyvsp[(2) - (3)]));
  ;}
    break;

  case 647:

/* Line 1455 of yacc.c  */
#line 3940 "parser.y"
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

  case 698:

/* Line 1455 of yacc.c  */
#line 4012 "parser.y"
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

  case 699:

/* Line 1455 of yacc.c  */
#line 4034 "parser.y"
    {
	BEGIN_STATEMENT ("ACCEPT", TERM_ACCEPT);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 701:

/* Line 1455 of yacc.c  */
#line 4047 "parser.y"
    {
	cb_emit_accept ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 702:

/* Line 1455 of yacc.c  */
#line 4051 "parser.y"
    {
	PENDING ("ACCEPT .. FROM ESCAPE KEY");
  ;}
    break;

  case 703:

/* Line 1455 of yacc.c  */
#line 4055 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 0);
  ;}
    break;

  case 704:

/* Line 1455 of yacc.c  */
#line 4059 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 1);
  ;}
    break;

  case 705:

/* Line 1455 of yacc.c  */
#line 4063 "parser.y"
    {
	cb_emit_accept_date ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 706:

/* Line 1455 of yacc.c  */
#line 4067 "parser.y"
    {
	cb_emit_accept_date_yyyymmdd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 707:

/* Line 1455 of yacc.c  */
#line 4071 "parser.y"
    {
	cb_emit_accept_day ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 708:

/* Line 1455 of yacc.c  */
#line 4075 "parser.y"
    {
	cb_emit_accept_day_yyyyddd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 709:

/* Line 1455 of yacc.c  */
#line 4079 "parser.y"
    {
	cb_emit_accept_day_of_week ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 710:

/* Line 1455 of yacc.c  */
#line 4083 "parser.y"
    {
	cb_emit_accept_time ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 711:

/* Line 1455 of yacc.c  */
#line 4087 "parser.y"
    {
	cb_emit_accept_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 712:

/* Line 1455 of yacc.c  */
#line 4091 "parser.y"
    {
	cb_emit_accept_environment ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 713:

/* Line 1455 of yacc.c  */
#line 4095 "parser.y"
    { 
	cb_emit_get_environment ((yyvsp[(4) - (5)]), (yyvsp[(1) - (5)]));
  ;}
    break;

  case 714:

/* Line 1455 of yacc.c  */
#line 4099 "parser.y"
    {
	cb_emit_accept_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 715:

/* Line 1455 of yacc.c  */
#line 4103 "parser.y"
    {
	cb_emit_accept_arg_value ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 716:

/* Line 1455 of yacc.c  */
#line 4107 "parser.y"
    {
	cb_emit_accept_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 717:

/* Line 1455 of yacc.c  */
#line 4111 "parser.y"
    {
	cb_emit_accept_name ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 718:

/* Line 1455 of yacc.c  */
#line 4117 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 719:

/* Line 1455 of yacc.c  */
#line 4118 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 720:

/* Line 1455 of yacc.c  */
#line 4119 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); ;}
    break;

  case 721:

/* Line 1455 of yacc.c  */
#line 4120 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), NULL); ;}
    break;

  case 722:

/* Line 1455 of yacc.c  */
#line 4121 "parser.y"
    { (yyval) = cb_build_pair (NULL, (yyvsp[(2) - (2)])); ;}
    break;

  case 723:

/* Line 1455 of yacc.c  */
#line 4122 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 724:

/* Line 1455 of yacc.c  */
#line 4126 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 725:

/* Line 1455 of yacc.c  */
#line 4130 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 726:

/* Line 1455 of yacc.c  */
#line 4131 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 731:

/* Line 1455 of yacc.c  */
#line 4144 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 732:

/* Line 1455 of yacc.c  */
#line 4145 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 733:

/* Line 1455 of yacc.c  */
#line 4146 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 734:

/* Line 1455 of yacc.c  */
#line 4147 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 735:

/* Line 1455 of yacc.c  */
#line 4148 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 736:

/* Line 1455 of yacc.c  */
#line 4149 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 737:

/* Line 1455 of yacc.c  */
#line 4150 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 738:

/* Line 1455 of yacc.c  */
#line 4152 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 739:

/* Line 1455 of yacc.c  */
#line 4156 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 740:

/* Line 1455 of yacc.c  */
#line 4160 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 741:

/* Line 1455 of yacc.c  */
#line 4164 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 742:

/* Line 1455 of yacc.c  */
#line 4168 "parser.y"
    { dispattrs |= COB_SCREEN_AUTO; ;}
    break;

  case 743:

/* Line 1455 of yacc.c  */
#line 4169 "parser.y"
    { dispattrs |= COB_SCREEN_FULL; ;}
    break;

  case 744:

/* Line 1455 of yacc.c  */
#line 4170 "parser.y"
    { dispattrs |= COB_SCREEN_REQUIRED; ;}
    break;

  case 745:

/* Line 1455 of yacc.c  */
#line 4171 "parser.y"
    { dispattrs |= COB_SCREEN_SECURE; ;}
    break;

  case 746:

/* Line 1455 of yacc.c  */
#line 4172 "parser.y"
    { dispattrs |= COB_SCREEN_UPDATE; ;}
    break;

  case 747:

/* Line 1455 of yacc.c  */
#line 4173 "parser.y"
    { dispattrs |= COB_SCREEN_PROMPT; ;}
    break;

  case 748:

/* Line 1455 of yacc.c  */
#line 4177 "parser.y"
    { terminator_warning (TERM_ACCEPT); ;}
    break;

  case 749:

/* Line 1455 of yacc.c  */
#line 4178 "parser.y"
    { terminator_clear (TERM_ACCEPT); ;}
    break;

  case 750:

/* Line 1455 of yacc.c  */
#line 4187 "parser.y"
    { BEGIN_STATEMENT ("ADD", TERM_ADD); ;}
    break;

  case 752:

/* Line 1455 of yacc.c  */
#line 4194 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '+', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 753:

/* Line 1455 of yacc.c  */
#line 4198 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(4) - (5)]), 0, cb_build_binary_list ((yyvsp[(1) - (5)]), '+'));
  ;}
    break;

  case 754:

/* Line 1455 of yacc.c  */
#line 4202 "parser.y"
    {
	cb_emit_corresponding (cb_build_add, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 756:

/* Line 1455 of yacc.c  */
#line 4208 "parser.y"
    { cb_list_add ((yyvsp[(0) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 757:

/* Line 1455 of yacc.c  */
#line 4212 "parser.y"
    { terminator_warning (TERM_ADD); ;}
    break;

  case 758:

/* Line 1455 of yacc.c  */
#line 4213 "parser.y"
    { terminator_clear (TERM_ADD); ;}
    break;

  case 759:

/* Line 1455 of yacc.c  */
#line 4222 "parser.y"
    { BEGIN_STATEMENT ("ALLOCATE", 0); ;}
    break;

  case 761:

/* Line 1455 of yacc.c  */
#line 4228 "parser.y"
    {
	cb_emit_allocate ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), NULL, (yyvsp[(2) - (3)]));
  ;}
    break;

  case 762:

/* Line 1455 of yacc.c  */
#line 4232 "parser.y"
    {
	cb_emit_allocate (NULL, (yyvsp[(5) - (5)]), (yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]));
  ;}
    break;

  case 763:

/* Line 1455 of yacc.c  */
#line 4238 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 764:

/* Line 1455 of yacc.c  */
#line 4239 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 765:

/* Line 1455 of yacc.c  */
#line 4249 "parser.y"
    {
	cb_error (_("ALTER statement is obsolete and unsupported"));
  ;}
    break;

  case 770:

/* Line 1455 of yacc.c  */
#line 4267 "parser.y"
    { BEGIN_STATEMENT ("CALL", TERM_CALL); ;}
    break;

  case 771:

/* Line 1455 of yacc.c  */
#line 4271 "parser.y"
    {
	cb_emit_call ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 772:

/* Line 1455 of yacc.c  */
#line 4277 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 773:

/* Line 1455 of yacc.c  */
#line 4279 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 774:

/* Line 1455 of yacc.c  */
#line 4283 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 775:

/* Line 1455 of yacc.c  */
#line 4287 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 776:

/* Line 1455 of yacc.c  */
#line 4289 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 777:

/* Line 1455 of yacc.c  */
#line 4294 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OMITTED only allowed with BY REFERENCE"));
	}
	(yyval) = cb_build_pair (cb_int (call_mode), cb_null);
  ;}
    break;

  case 778:

/* Line 1455 of yacc.c  */
#line 4301 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), (yyvsp[(3) - (3)]));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 780:

/* Line 1455 of yacc.c  */
#line 4310 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 781:

/* Line 1455 of yacc.c  */
#line 4314 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY CONTENT not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_CONTENT;
	}
  ;}
    break;

  case 782:

/* Line 1455 of yacc.c  */
#line 4322 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 783:

/* Line 1455 of yacc.c  */
#line 4332 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 784:

/* Line 1455 of yacc.c  */
#line 4333 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 785:

/* Line 1455 of yacc.c  */
#line 4334 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 786:

/* Line 1455 of yacc.c  */
#line 4339 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 787:

/* Line 1455 of yacc.c  */
#line 4343 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 788:

/* Line 1455 of yacc.c  */
#line 4347 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 789:

/* Line 1455 of yacc.c  */
#line 4354 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 790:

/* Line 1455 of yacc.c  */
#line 4358 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 791:

/* Line 1455 of yacc.c  */
#line 4362 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 792:

/* Line 1455 of yacc.c  */
#line 4368 "parser.y"
    { terminator_warning (TERM_CALL); ;}
    break;

  case 793:

/* Line 1455 of yacc.c  */
#line 4369 "parser.y"
    { terminator_clear (TERM_CALL); ;}
    break;

  case 794:

/* Line 1455 of yacc.c  */
#line 4378 "parser.y"
    { BEGIN_STATEMENT ("CANCEL", 0); ;}
    break;

  case 797:

/* Line 1455 of yacc.c  */
#line 4384 "parser.y"
    {
	cb_emit_cancel ((yyvsp[(2) - (2)]));
  ;}
    break;

  case 798:

/* Line 1455 of yacc.c  */
#line 4395 "parser.y"
    { BEGIN_STATEMENT ("CLOSE", 0); ;}
    break;

  case 801:

/* Line 1455 of yacc.c  */
#line 4402 "parser.y"
    {
	BEGIN_IMPLICIT_STATEMENT ((yyvsp[(2) - (3)]));
	if ((yyvsp[(2) - (3)]) != cb_error_node) {
		cb_emit_close ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
	}
  ;}
    break;

  case 802:

/* Line 1455 of yacc.c  */
#line 4411 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NORMAL); ;}
    break;

  case 803:

/* Line 1455 of yacc.c  */
#line 4412 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT); ;}
    break;

  case 804:

/* Line 1455 of yacc.c  */
#line 4413 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT_REMOVAL); ;}
    break;

  case 805:

/* Line 1455 of yacc.c  */
#line 4414 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NO_REWIND); ;}
    break;

  case 806:

/* Line 1455 of yacc.c  */
#line 4415 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_LOCK); ;}
    break;

  case 809:

/* Line 1455 of yacc.c  */
#line 4426 "parser.y"
    { BEGIN_STATEMENT ("COMPUTE", TERM_COMPUTE); ;}
    break;

  case 811:

/* Line 1455 of yacc.c  */
#line 4433 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(1) - (4)]), 0, (yyvsp[(3) - (4)]));
  ;}
    break;

  case 812:

/* Line 1455 of yacc.c  */
#line 4439 "parser.y"
    { terminator_warning (TERM_COMPUTE); ;}
    break;

  case 813:

/* Line 1455 of yacc.c  */
#line 4440 "parser.y"
    { terminator_clear (TERM_COMPUTE); ;}
    break;

  case 816:

/* Line 1455 of yacc.c  */
#line 4451 "parser.y"
    {
	BEGIN_STATEMENT ("COMMIT", 0);
	cb_emit_commit ();
  ;}
    break;

  case 817:

/* Line 1455 of yacc.c  */
#line 4464 "parser.y"
    {
	BEGIN_STATEMENT ("CONTINUE", 0);
	cb_emit_continue ();
  ;}
    break;

  case 818:

/* Line 1455 of yacc.c  */
#line 4476 "parser.y"
    { BEGIN_STATEMENT ("DELETE", TERM_DELETE); ;}
    break;

  case 819:

/* Line 1455 of yacc.c  */
#line 4479 "parser.y"
    {
	if ((yyvsp[(3) - (6)]) != cb_error_node) {
		cb_emit_delete ((yyvsp[(3) - (6)]));
	}
  ;}
    break;

  case 820:

/* Line 1455 of yacc.c  */
#line 4487 "parser.y"
    { terminator_warning (TERM_DELETE); ;}
    break;

  case 821:

/* Line 1455 of yacc.c  */
#line 4488 "parser.y"
    { terminator_clear (TERM_DELETE); ;}
    break;

  case 822:

/* Line 1455 of yacc.c  */
#line 4497 "parser.y"
    { BEGIN_STATEMENT ("DELETE-FILE", 0); ;}
    break;

  case 823:

/* Line 1455 of yacc.c  */
#line 4499 "parser.y"
    {
	cb_tree l;
	for (l = (yyvsp[(4) - (4)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			BEGIN_IMPLICIT_STATEMENT (l);
			cb_emit_delete_file (CB_VALUE (l));
		}
	}
  ;}
    break;

  case 824:

/* Line 1455 of yacc.c  */
#line 4517 "parser.y"
    {
	BEGIN_STATEMENT ("DISPLAY", TERM_DISPLAY);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 826:

/* Line 1455 of yacc.c  */
#line 4530 "parser.y"
    {
	cb_emit_env_name ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 827:

/* Line 1455 of yacc.c  */
#line 4534 "parser.y"
    {
	cb_emit_env_value ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 828:

/* Line 1455 of yacc.c  */
#line 4538 "parser.y"
    {
	cb_emit_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 829:

/* Line 1455 of yacc.c  */
#line 4542 "parser.y"
    {
	cb_emit_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 830:

/* Line 1455 of yacc.c  */
#line 4546 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (4)]), cb_int0, (yyvsp[(3) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 831:

/* Line 1455 of yacc.c  */
#line 4550 "parser.y"
    {
	cb_emit_display_mnemonic ((yyvsp[(1) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 832:

/* Line 1455 of yacc.c  */
#line 4554 "parser.y"
    {
	cb_tree word = cb_build_display_upon_direct ((yyvsp[(4) - (6)]));
	cb_emit_display ((yyvsp[(1) - (6)]), word, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 833:

/* Line 1455 of yacc.c  */
#line 4559 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 834:

/* Line 1455 of yacc.c  */
#line 4563 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 835:

/* Line 1455 of yacc.c  */
#line 4569 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 836:

/* Line 1455 of yacc.c  */
#line 4570 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 837:

/* Line 1455 of yacc.c  */
#line 4571 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 840:

/* Line 1455 of yacc.c  */
#line 4581 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 841:

/* Line 1455 of yacc.c  */
#line 4582 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 842:

/* Line 1455 of yacc.c  */
#line 4583 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 843:

/* Line 1455 of yacc.c  */
#line 4584 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 844:

/* Line 1455 of yacc.c  */
#line 4585 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 845:

/* Line 1455 of yacc.c  */
#line 4586 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 846:

/* Line 1455 of yacc.c  */
#line 4587 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 847:

/* Line 1455 of yacc.c  */
#line 4588 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 848:

/* Line 1455 of yacc.c  */
#line 4589 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 849:

/* Line 1455 of yacc.c  */
#line 4591 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 850:

/* Line 1455 of yacc.c  */
#line 4595 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 851:

/* Line 1455 of yacc.c  */
#line 4599 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 852:

/* Line 1455 of yacc.c  */
#line 4603 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 853:

/* Line 1455 of yacc.c  */
#line 4607 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 854:

/* Line 1455 of yacc.c  */
#line 4608 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 855:

/* Line 1455 of yacc.c  */
#line 4612 "parser.y"
    { terminator_warning (TERM_DISPLAY); ;}
    break;

  case 856:

/* Line 1455 of yacc.c  */
#line 4613 "parser.y"
    { terminator_clear (TERM_DISPLAY); ;}
    break;

  case 857:

/* Line 1455 of yacc.c  */
#line 4622 "parser.y"
    { BEGIN_STATEMENT ("DIVIDE", TERM_DIVIDE); ;}
    break;

  case 859:

/* Line 1455 of yacc.c  */
#line 4629 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '/', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 860:

/* Line 1455 of yacc.c  */
#line 4633 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(3) - (6)]), '/', (yyvsp[(1) - (6)])));
  ;}
    break;

  case 861:

/* Line 1455 of yacc.c  */
#line 4637 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '/', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 862:

/* Line 1455 of yacc.c  */
#line 4641 "parser.y"
    {
	cb_emit_divide ((yyvsp[(3) - (8)]), (yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 863:

/* Line 1455 of yacc.c  */
#line 4645 "parser.y"
    {
	cb_emit_divide ((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 864:

/* Line 1455 of yacc.c  */
#line 4651 "parser.y"
    { terminator_warning (TERM_DIVIDE); ;}
    break;

  case 865:

/* Line 1455 of yacc.c  */
#line 4652 "parser.y"
    { terminator_clear (TERM_DIVIDE); ;}
    break;

  case 866:

/* Line 1455 of yacc.c  */
#line 4661 "parser.y"
    { BEGIN_STATEMENT ("ENTRY", 0); ;}
    break;

  case 867:

/* Line 1455 of yacc.c  */
#line 4663 "parser.y"
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

  case 868:

/* Line 1455 of yacc.c  */
#line 4683 "parser.y"
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

  case 869:

/* Line 1455 of yacc.c  */
#line 4694 "parser.y"
    {
	cb_emit_evaluate ((yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]));
	eval_level--;
  ;}
    break;

  case 870:

/* Line 1455 of yacc.c  */
#line 4701 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 871:

/* Line 1455 of yacc.c  */
#line 4704 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 872:

/* Line 1455 of yacc.c  */
#line 4714 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE_P ((yyvsp[(1) - (1)]))) {
		eval_check[eval_level][eval_inc++] = 0;
	} else {
		eval_check[eval_level][eval_inc++] = 1;
	}
  ;}
    break;

  case 873:

/* Line 1455 of yacc.c  */
#line 4723 "parser.y"
    {
	(yyval) = cb_true;
	eval_check[eval_level][eval_inc++] = 2;
  ;}
    break;

  case 874:

/* Line 1455 of yacc.c  */
#line 4728 "parser.y"
    {
	(yyval) = cb_false;
	eval_check[eval_level][eval_inc++] = 3;
  ;}
    break;

  case 875:

/* Line 1455 of yacc.c  */
#line 4736 "parser.y"
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

  case 876:

/* Line 1455 of yacc.c  */
#line 4764 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 877:

/* Line 1455 of yacc.c  */
#line 4766 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 878:

/* Line 1455 of yacc.c  */
#line 4771 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 879:

/* Line 1455 of yacc.c  */
#line 4775 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]));
	eval_inc2 = 0;
  ;}
    break;

  case 880:

/* Line 1455 of yacc.c  */
#line 4786 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 881:

/* Line 1455 of yacc.c  */
#line 4790 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 882:

/* Line 1455 of yacc.c  */
#line 4794 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), NULL);
	eval_inc2 = 0;
  ;}
    break;

  case 883:

/* Line 1455 of yacc.c  */
#line 4804 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 884:

/* Line 1455 of yacc.c  */
#line 4806 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 885:

/* Line 1455 of yacc.c  */
#line 4810 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 886:

/* Line 1455 of yacc.c  */
#line 4813 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 887:

/* Line 1455 of yacc.c  */
#line 4823 "parser.y"
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

  case 888:

/* Line 1455 of yacc.c  */
#line 4851 "parser.y"
    { (yyval) = cb_any; eval_inc2++; ;}
    break;

  case 889:

/* Line 1455 of yacc.c  */
#line 4852 "parser.y"
    { (yyval) = cb_true; eval_inc2++; ;}
    break;

  case 890:

/* Line 1455 of yacc.c  */
#line 4853 "parser.y"
    { (yyval) = cb_false; eval_inc2++; ;}
    break;

  case 891:

/* Line 1455 of yacc.c  */
#line 4856 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 892:

/* Line 1455 of yacc.c  */
#line 4857 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 893:

/* Line 1455 of yacc.c  */
#line 4861 "parser.y"
    { terminator_warning (TERM_EVALUATE); ;}
    break;

  case 894:

/* Line 1455 of yacc.c  */
#line 4862 "parser.y"
    { terminator_clear (TERM_EVALUATE); ;}
    break;

  case 895:

/* Line 1455 of yacc.c  */
#line 4871 "parser.y"
    { BEGIN_STATEMENT ("EXIT", 0); ;}
    break;

  case 897:

/* Line 1455 of yacc.c  */
#line 4876 "parser.y"
    { /* nothing */ ;}
    break;

  case 898:

/* Line 1455 of yacc.c  */
#line 4878 "parser.y"
    {
	if (in_declaratives && use_global_ind) {
		cb_error (_("EXIT PROGRAM is not allowed within a USE GLOBAL procedure"));
	}
	check_unreached = 1;
	cb_emit_exit (0);
  ;}
    break;

  case 899:

/* Line 1455 of yacc.c  */
#line 4886 "parser.y"
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
  ;}
    break;

  case 900:

/* Line 1455 of yacc.c  */
#line 4903 "parser.y"
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
  ;}
    break;

  case 901:

/* Line 1455 of yacc.c  */
#line 4920 "parser.y"
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
  ;}
    break;

  case 902:

/* Line 1455 of yacc.c  */
#line 4938 "parser.y"
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
  ;}
    break;

  case 903:

/* Line 1455 of yacc.c  */
#line 4962 "parser.y"
    { BEGIN_STATEMENT ("FREE", 0); ;}
    break;

  case 904:

/* Line 1455 of yacc.c  */
#line 4964 "parser.y"
    {
	cb_emit_free ((yyvsp[(3) - (3)]));
  ;}
    break;

  case 905:

/* Line 1455 of yacc.c  */
#line 4975 "parser.y"
    { BEGIN_STATEMENT ("GENERATE", 0); ;}
    break;

  case 906:

/* Line 1455 of yacc.c  */
#line 4977 "parser.y"
    {
	PENDING("GENERATE");
  ;}
    break;

  case 907:

/* Line 1455 of yacc.c  */
#line 4988 "parser.y"
    { BEGIN_STATEMENT ("GO TO", 0); ;}
    break;

  case 908:

/* Line 1455 of yacc.c  */
#line 4990 "parser.y"
    {
	cb_emit_goto ((yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 909:

/* Line 1455 of yacc.c  */
#line 4997 "parser.y"
    {
	check_unreached = 1;
	(yyval) = NULL;
  ;}
    break;

  case 910:

/* Line 1455 of yacc.c  */
#line 5002 "parser.y"
    {
	check_unreached = 0;
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 911:

/* Line 1455 of yacc.c  */
#line 5014 "parser.y"
    { BEGIN_STATEMENT ("GOBACK", 0); ;}
    break;

  case 912:

/* Line 1455 of yacc.c  */
#line 5015 "parser.y"
    {
	check_unreached = 1;
	cb_emit_exit (1);
  ;}
    break;

  case 913:

/* Line 1455 of yacc.c  */
#line 5027 "parser.y"
    { BEGIN_STATEMENT ("IF", TERM_IF); ;}
    break;

  case 914:

/* Line 1455 of yacc.c  */
#line 5029 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 915:

/* Line 1455 of yacc.c  */
#line 5034 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(6) - (8)]) == NULL) {
		cb_error (_("syntax error"));
	}
	cb_emit_if ((yyvsp[(3) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 917:

/* Line 1455 of yacc.c  */
#line 5045 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 918:

/* Line 1455 of yacc.c  */
#line 5049 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 919:

/* Line 1455 of yacc.c  */
#line 5053 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 920:

/* Line 1455 of yacc.c  */
#line 5062 "parser.y"
    { terminator_warning (TERM_IF); ;}
    break;

  case 921:

/* Line 1455 of yacc.c  */
#line 5063 "parser.y"
    { terminator_clear (TERM_IF); ;}
    break;

  case 922:

/* Line 1455 of yacc.c  */
#line 5072 "parser.y"
    { BEGIN_STATEMENT ("INITIALIZE", 0); ;}
    break;

  case 923:

/* Line 1455 of yacc.c  */
#line 5074 "parser.y"
    {
	cb_emit_initialize ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 924:

/* Line 1455 of yacc.c  */
#line 5080 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 925:

/* Line 1455 of yacc.c  */
#line 5081 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 926:

/* Line 1455 of yacc.c  */
#line 5085 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 927:

/* Line 1455 of yacc.c  */
#line 5086 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 928:

/* Line 1455 of yacc.c  */
#line 5087 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 929:

/* Line 1455 of yacc.c  */
#line 5091 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 930:

/* Line 1455 of yacc.c  */
#line 5093 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 931:

/* Line 1455 of yacc.c  */
#line 5097 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 932:

/* Line 1455 of yacc.c  */
#line 5099 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 933:

/* Line 1455 of yacc.c  */
#line 5103 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 934:

/* Line 1455 of yacc.c  */
#line 5107 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHABETIC); ;}
    break;

  case 935:

/* Line 1455 of yacc.c  */
#line 5108 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC); ;}
    break;

  case 936:

/* Line 1455 of yacc.c  */
#line 5109 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC); ;}
    break;

  case 937:

/* Line 1455 of yacc.c  */
#line 5110 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC_EDITED); ;}
    break;

  case 938:

/* Line 1455 of yacc.c  */
#line 5111 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC_EDITED); ;}
    break;

  case 939:

/* Line 1455 of yacc.c  */
#line 5112 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL); ;}
    break;

  case 940:

/* Line 1455 of yacc.c  */
#line 5113 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL_EDITED); ;}
    break;

  case 941:

/* Line 1455 of yacc.c  */
#line 5117 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 942:

/* Line 1455 of yacc.c  */
#line 5118 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 943:

/* Line 1455 of yacc.c  */
#line 5127 "parser.y"
    { BEGIN_STATEMENT ("INITIATE", 0); ;}
    break;

  case 944:

/* Line 1455 of yacc.c  */
#line 5129 "parser.y"
    {
	PENDING("INITIATE");
  ;}
    break;

  case 945:

/* Line 1455 of yacc.c  */
#line 5140 "parser.y"
    {
	BEGIN_STATEMENT ("INSPECT", 0);
	sending_id = 0;
	inspect_keyword = 0;
  ;}
    break;

  case 947:

/* Line 1455 of yacc.c  */
#line 5149 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 0; ;}
    break;

  case 948:

/* Line 1455 of yacc.c  */
#line 5150 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 949:

/* Line 1455 of yacc.c  */
#line 5151 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 952:

/* Line 1455 of yacc.c  */
#line 5160 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 0); ;}
    break;

  case 953:

/* Line 1455 of yacc.c  */
#line 5161 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int1, 1); ;}
    break;

  case 954:

/* Line 1455 of yacc.c  */
#line 5162 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 2); ;}
    break;

  case 955:

/* Line 1455 of yacc.c  */
#line 5168 "parser.y"
    { cb_init_tarrying (); ;}
    break;

  case 956:

/* Line 1455 of yacc.c  */
#line 5169 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 957:

/* Line 1455 of yacc.c  */
#line 5173 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 958:

/* Line 1455 of yacc.c  */
#line 5174 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 959:

/* Line 1455 of yacc.c  */
#line 5178 "parser.y"
    { (yyval) = cb_build_tarrying_data ((yyvsp[(1) - (2)])); ;}
    break;

  case 960:

/* Line 1455 of yacc.c  */
#line 5179 "parser.y"
    { (yyval) = cb_build_tarrying_characters ((yyvsp[(2) - (2)])); ;}
    break;

  case 961:

/* Line 1455 of yacc.c  */
#line 5180 "parser.y"
    { (yyval) = cb_build_tarrying_all (); ;}
    break;

  case 962:

/* Line 1455 of yacc.c  */
#line 5181 "parser.y"
    { (yyval) = cb_build_tarrying_leading (); ;}
    break;

  case 963:

/* Line 1455 of yacc.c  */
#line 5182 "parser.y"
    { (yyval) = cb_build_tarrying_trailing (); ;}
    break;

  case 964:

/* Line 1455 of yacc.c  */
#line 5183 "parser.y"
    { (yyval) = cb_build_tarrying_value ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 965:

/* Line 1455 of yacc.c  */
#line 5189 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); inspect_keyword = 0; ;}
    break;

  case 966:

/* Line 1455 of yacc.c  */
#line 5193 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 967:

/* Line 1455 of yacc.c  */
#line 5194 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 968:

/* Line 1455 of yacc.c  */
#line 5199 "parser.y"
    {
	(yyval) = cb_build_replacing_characters ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]), save_tree_1);
	inspect_keyword = 0;
  ;}
    break;

  case 969:

/* Line 1455 of yacc.c  */
#line 5203 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 970:

/* Line 1455 of yacc.c  */
#line 5207 "parser.y"
    { /* Nothing */ ;}
    break;

  case 971:

/* Line 1455 of yacc.c  */
#line 5208 "parser.y"
    { inspect_keyword = 1; ;}
    break;

  case 972:

/* Line 1455 of yacc.c  */
#line 5209 "parser.y"
    { inspect_keyword = 2; ;}
    break;

  case 973:

/* Line 1455 of yacc.c  */
#line 5210 "parser.y"
    { inspect_keyword = 3; ;}
    break;

  case 974:

/* Line 1455 of yacc.c  */
#line 5211 "parser.y"
    { inspect_keyword = 4; ;}
    break;

  case 975:

/* Line 1455 of yacc.c  */
#line 5216 "parser.y"
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

  case 976:

/* Line 1455 of yacc.c  */
#line 5242 "parser.y"
    {
	if (cb_validate_inspect (save_tree_1, (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])) < 0 ) {
		(yyval) = cb_error_node;
	} else {
		(yyval) = cb_build_converting ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 977:

/* Line 1455 of yacc.c  */
#line 5254 "parser.y"
    { (yyval) = cb_build_inspect_region_start (); ;}
    break;

  case 978:

/* Line 1455 of yacc.c  */
#line 5256 "parser.y"
    { (yyval) = cb_build_inspect_region ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 981:

/* Line 1455 of yacc.c  */
#line 5267 "parser.y"
    { BEGIN_STATEMENT ("MERGE", 0); ;}
    break;

  case 983:

/* Line 1455 of yacc.c  */
#line 5277 "parser.y"
    { BEGIN_STATEMENT ("MOVE", 0); ;}
    break;

  case 985:

/* Line 1455 of yacc.c  */
#line 5283 "parser.y"
    {
	cb_emit_move ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 986:

/* Line 1455 of yacc.c  */
#line 5287 "parser.y"
    {
	cb_emit_move_corresponding ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 987:

/* Line 1455 of yacc.c  */
#line 5298 "parser.y"
    { BEGIN_STATEMENT ("MULTIPLY", TERM_MULTIPLY); ;}
    break;

  case 989:

/* Line 1455 of yacc.c  */
#line 5305 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '*', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 990:

/* Line 1455 of yacc.c  */
#line 5309 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '*', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 991:

/* Line 1455 of yacc.c  */
#line 5315 "parser.y"
    { terminator_warning (TERM_MULTIPLY); ;}
    break;

  case 992:

/* Line 1455 of yacc.c  */
#line 5316 "parser.y"
    { terminator_clear (TERM_MULTIPLY); ;}
    break;

  case 993:

/* Line 1455 of yacc.c  */
#line 5325 "parser.y"
    { BEGIN_STATEMENT ("OPEN", 0); ;}
    break;

  case 996:

/* Line 1455 of yacc.c  */
#line 5332 "parser.y"
    {
	cb_tree l;
	for (l = (yyvsp[(4) - (5)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			BEGIN_IMPLICIT_STATEMENT (l);
			cb_emit_open (CB_VALUE (l), (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]));
		}
	}
  ;}
    break;

  case 997:

/* Line 1455 of yacc.c  */
#line 5344 "parser.y"
    { (yyval) = cb_int (COB_OPEN_INPUT); ;}
    break;

  case 998:

/* Line 1455 of yacc.c  */
#line 5345 "parser.y"
    { (yyval) = cb_int (COB_OPEN_OUTPUT); ;}
    break;

  case 999:

/* Line 1455 of yacc.c  */
#line 5346 "parser.y"
    { (yyval) = cb_int (COB_OPEN_I_O); ;}
    break;

  case 1000:

/* Line 1455 of yacc.c  */
#line 5347 "parser.y"
    { (yyval) = cb_int (COB_OPEN_EXTEND); ;}
    break;

  case 1001:

/* Line 1455 of yacc.c  */
#line 5351 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1002:

/* Line 1455 of yacc.c  */
#line 5352 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1003:

/* Line 1455 of yacc.c  */
#line 5356 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1004:

/* Line 1455 of yacc.c  */
#line 5357 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1005:

/* Line 1455 of yacc.c  */
#line 5358 "parser.y"
    { PENDING ("OPEN ... WITH LOCK"); ;}
    break;

  case 1006:

/* Line 1455 of yacc.c  */
#line 5370 "parser.y"
    { BEGIN_STATEMENT ("PERFORM", TERM_PERFORM); ;}
    break;

  case 1008:

/* Line 1455 of yacc.c  */
#line 5376 "parser.y"
    {
	cb_emit_perform ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));
  ;}
    break;

  case 1009:

/* Line 1455 of yacc.c  */
#line 5380 "parser.y"
    {
	perform_stack = cb_cons ((yyvsp[(1) - (1)]), perform_stack);
	check_unreached = 0;
  ;}
    break;

  case 1010:

/* Line 1455 of yacc.c  */
#line 5385 "parser.y"
    {
	perform_stack = CB_CHAIN (perform_stack);
	cb_emit_perform ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 1011:

/* Line 1455 of yacc.c  */
#line 5390 "parser.y"
    {
	cb_emit_perform ((yyvsp[(1) - (2)]), NULL);
  ;}
    break;

  case 1012:

/* Line 1455 of yacc.c  */
#line 5396 "parser.y"
    { terminator_error (); ;}
    break;

  case 1013:

/* Line 1455 of yacc.c  */
#line 5397 "parser.y"
    { terminator_clear (TERM_PERFORM); ;}
    break;

  case 1014:

/* Line 1455 of yacc.c  */
#line 5402 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(1) - (1)]))->length = cb_true; /* return from $1 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (1)]), (yyvsp[(1) - (1)]));
  ;}
    break;

  case 1015:

/* Line 1455 of yacc.c  */
#line 5407 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(3) - (3)]))->length = cb_true; /* return from $3 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1016:

/* Line 1455 of yacc.c  */
#line 5415 "parser.y"
    {
	(yyval) = cb_build_perform_once (NULL);
  ;}
    break;

  case 1017:

/* Line 1455 of yacc.c  */
#line 5419 "parser.y"
    {
	(yyval) = cb_build_perform_forever (NULL);
  ;}
    break;

  case 1018:

/* Line 1455 of yacc.c  */
#line 5423 "parser.y"
    {
	(yyval) = cb_build_perform_times ((yyvsp[(1) - (2)]));
	current_program->loop_counter++;
  ;}
    break;

  case 1019:

/* Line 1455 of yacc.c  */
#line 5428 "parser.y"
    {
	cb_tree varying;

	varying = cb_list_init (cb_build_perform_varying (NULL, NULL, NULL, (yyvsp[(3) - (3)])));
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), varying);
  ;}
    break;

  case 1020:

/* Line 1455 of yacc.c  */
#line 5435 "parser.y"
    {
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1021:

/* Line 1455 of yacc.c  */
#line 5441 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1022:

/* Line 1455 of yacc.c  */
#line 5442 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1023:

/* Line 1455 of yacc.c  */
#line 5446 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1024:

/* Line 1455 of yacc.c  */
#line 5448 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1025:

/* Line 1455 of yacc.c  */
#line 5453 "parser.y"
    {
	(yyval) = cb_build_perform_varying ((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1026:

/* Line 1455 of yacc.c  */
#line 5464 "parser.y"
    { BEGIN_STATEMENT ("READ", TERM_READ); ;}
    break;

  case 1027:

/* Line 1455 of yacc.c  */
#line 5467 "parser.y"
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
  ;}
    break;

  case 1028:

/* Line 1455 of yacc.c  */
#line 5493 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1029:

/* Line 1455 of yacc.c  */
#line 5494 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1030:

/* Line 1455 of yacc.c  */
#line 5498 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1031:

/* Line 1455 of yacc.c  */
#line 5500 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1032:

/* Line 1455 of yacc.c  */
#line 5504 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1033:

/* Line 1455 of yacc.c  */
#line 5508 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1034:

/* Line 1455 of yacc.c  */
#line 5512 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1035:

/* Line 1455 of yacc.c  */
#line 5516 "parser.y"
    {
	(yyval) = cb_int4;
  ;}
    break;

  case 1036:

/* Line 1455 of yacc.c  */
#line 5522 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1037:

/* Line 1455 of yacc.c  */
#line 5524 "parser.y"
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

  case 1041:

/* Line 1455 of yacc.c  */
#line 5543 "parser.y"
    { terminator_warning (TERM_READ); ;}
    break;

  case 1042:

/* Line 1455 of yacc.c  */
#line 5544 "parser.y"
    { terminator_clear (TERM_READ); ;}
    break;

  case 1043:

/* Line 1455 of yacc.c  */
#line 5553 "parser.y"
    { BEGIN_STATEMENT ("RELEASE", 0); ;}
    break;

  case 1044:

/* Line 1455 of yacc.c  */
#line 5555 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_release ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
	}
  ;}
    break;

  case 1045:

/* Line 1455 of yacc.c  */
#line 5568 "parser.y"
    { BEGIN_STATEMENT ("RETURN", TERM_RETURN); ;}
    break;

  case 1046:

/* Line 1455 of yacc.c  */
#line 5571 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_return ((yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]));
	}
  ;}
    break;

  case 1047:

/* Line 1455 of yacc.c  */
#line 5579 "parser.y"
    { terminator_warning (TERM_RETURN); ;}
    break;

  case 1048:

/* Line 1455 of yacc.c  */
#line 5580 "parser.y"
    { terminator_clear (TERM_RETURN); ;}
    break;

  case 1049:

/* Line 1455 of yacc.c  */
#line 5589 "parser.y"
    { BEGIN_STATEMENT ("REWRITE", TERM_REWRITE); ;}
    break;

  case 1050:

/* Line 1455 of yacc.c  */
#line 5592 "parser.y"
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
  ;}
    break;

  case 1051:

/* Line 1455 of yacc.c  */
#line 5606 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1052:

/* Line 1455 of yacc.c  */
#line 5608 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1053:

/* Line 1455 of yacc.c  */
#line 5612 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1054:

/* Line 1455 of yacc.c  */
#line 5618 "parser.y"
    { terminator_warning (TERM_REWRITE); ;}
    break;

  case 1055:

/* Line 1455 of yacc.c  */
#line 5619 "parser.y"
    { terminator_clear (TERM_REWRITE); ;}
    break;

  case 1056:

/* Line 1455 of yacc.c  */
#line 5629 "parser.y"
    {
	BEGIN_STATEMENT ("ROLLBACK", 0);
	cb_emit_rollback ();
  ;}
    break;

  case 1057:

/* Line 1455 of yacc.c  */
#line 5641 "parser.y"
    { BEGIN_STATEMENT ("SEARCH", TERM_SEARCH); ;}
    break;

  case 1059:

/* Line 1455 of yacc.c  */
#line 5648 "parser.y"
    {
	cb_emit_search ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1060:

/* Line 1455 of yacc.c  */
#line 5652 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1061:

/* Line 1455 of yacc.c  */
#line 5656 "parser.y"
    {
	cb_emit_search_all ((yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1062:

/* Line 1455 of yacc.c  */
#line 5662 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1063:

/* Line 1455 of yacc.c  */
#line 5663 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1064:

/* Line 1455 of yacc.c  */
#line 5667 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1065:

/* Line 1455 of yacc.c  */
#line 5669 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1066:

/* Line 1455 of yacc.c  */
#line 5673 "parser.y"
    {
	(yyval) = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 1067:

/* Line 1455 of yacc.c  */
#line 5679 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1068:

/* Line 1455 of yacc.c  */
#line 5680 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); CB_IF ((yyvsp[(1) - (2)]))->stmt2 = (yyvsp[(2) - (2)]); ;}
    break;

  case 1069:

/* Line 1455 of yacc.c  */
#line 5685 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1070:

/* Line 1455 of yacc.c  */
#line 5689 "parser.y"
    {
	(yyval) = cb_build_if ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), NULL);
  ;}
    break;

  case 1071:

/* Line 1455 of yacc.c  */
#line 5695 "parser.y"
    { terminator_warning (TERM_SEARCH); ;}
    break;

  case 1072:

/* Line 1455 of yacc.c  */
#line 5696 "parser.y"
    { terminator_clear (TERM_SEARCH); ;}
    break;

  case 1073:

/* Line 1455 of yacc.c  */
#line 5705 "parser.y"
    { BEGIN_STATEMENT ("SET", 0); ;}
    break;

  case 1080:

/* Line 1455 of yacc.c  */
#line 5721 "parser.y"
    {
	cb_emit_setenv ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1081:

/* Line 1455 of yacc.c  */
#line 5730 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (4)]), cb_build_ppointer ((yyvsp[(4) - (4)])));
  ;}
    break;

  case 1082:

/* Line 1455 of yacc.c  */
#line 5734 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1083:

/* Line 1455 of yacc.c  */
#line 5743 "parser.y"
    {
	cb_emit_set_up_down ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1084:

/* Line 1455 of yacc.c  */
#line 5749 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1085:

/* Line 1455 of yacc.c  */
#line 5750 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1088:

/* Line 1455 of yacc.c  */
#line 5762 "parser.y"
    {
	cb_emit_set_on_off ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1091:

/* Line 1455 of yacc.c  */
#line 5776 "parser.y"
    {
	cb_emit_set_true ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1092:

/* Line 1455 of yacc.c  */
#line 5780 "parser.y"
    {
	cb_emit_set_false ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1093:

/* Line 1455 of yacc.c  */
#line 5791 "parser.y"
    { BEGIN_STATEMENT ("SORT", 0); ;}
    break;

  case 1095:

/* Line 1455 of yacc.c  */
#line 5797 "parser.y"
    {
	cb_emit_sort_init ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (4)]))) && (yyvsp[(2) - (4)]) == NULL) {
		cb_error (_("File sort requires KEY phrase"));
	}
	/* used in sort_input/sort_output */
	save_tree_1 = (yyvsp[(1) - (4)]);
  ;}
    break;

  case 1096:

/* Line 1455 of yacc.c  */
#line 5806 "parser.y"
    {
	cb_emit_sort_finish ((yyvsp[(1) - (7)]));
  ;}
    break;

  case 1097:

/* Line 1455 of yacc.c  */
#line 5813 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 1098:

/* Line 1455 of yacc.c  */
#line 5818 "parser.y"
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

  case 1099:

/* Line 1455 of yacc.c  */
#line 5832 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1100:

/* Line 1455 of yacc.c  */
#line 5833 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1102:

/* Line 1455 of yacc.c  */
#line 5837 "parser.y"
    { /* nothing */ ;}
    break;

  case 1103:

/* Line 1455 of yacc.c  */
#line 5841 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1104:

/* Line 1455 of yacc.c  */
#line 5842 "parser.y"
    { (yyval) = cb_ref ((yyvsp[(3) - (3)])); ;}
    break;

  case 1105:

/* Line 1455 of yacc.c  */
#line 5847 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires USING or INPUT PROCEDURE"));
	}
  ;}
    break;

  case 1106:

/* Line 1455 of yacc.c  */
#line 5853 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("USING invalid with table SORT"));
	} else {
		cb_emit_sort_using (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1107:

/* Line 1455 of yacc.c  */
#line 5861 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("INPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_input ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1108:

/* Line 1455 of yacc.c  */
#line 5872 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires GIVING or OUTPUT PROCEDURE"));
	}
  ;}
    break;

  case 1109:

/* Line 1455 of yacc.c  */
#line 5878 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("GIVING invalid with table SORT"));
	} else {
		cb_emit_sort_giving (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1110:

/* Line 1455 of yacc.c  */
#line 5886 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("OUTPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_output ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1111:

/* Line 1455 of yacc.c  */
#line 5901 "parser.y"
    { BEGIN_STATEMENT ("START", TERM_START); ;}
    break;

  case 1112:

/* Line 1455 of yacc.c  */
#line 5902 "parser.y"
    { (yyval) = cb_int (COB_EQ); ;}
    break;

  case 1113:

/* Line 1455 of yacc.c  */
#line 5905 "parser.y"
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

  case 1114:

/* Line 1455 of yacc.c  */
#line 5922 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1115:

/* Line 1455 of yacc.c  */
#line 5924 "parser.y"
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

  case 1116:

/* Line 1455 of yacc.c  */
#line 5939 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_NE : COB_EQ); ;}
    break;

  case 1117:

/* Line 1455 of yacc.c  */
#line 5940 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LE : COB_GT); ;}
    break;

  case 1118:

/* Line 1455 of yacc.c  */
#line 5941 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GE : COB_LT); ;}
    break;

  case 1119:

/* Line 1455 of yacc.c  */
#line 5942 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LT : COB_GE); ;}
    break;

  case 1120:

/* Line 1455 of yacc.c  */
#line 5943 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GT : COB_LE); ;}
    break;

  case 1121:

/* Line 1455 of yacc.c  */
#line 5947 "parser.y"
    { terminator_warning (TERM_START); ;}
    break;

  case 1122:

/* Line 1455 of yacc.c  */
#line 5948 "parser.y"
    { terminator_clear (TERM_START); ;}
    break;

  case 1123:

/* Line 1455 of yacc.c  */
#line 5957 "parser.y"
    { BEGIN_STATEMENT ("STOP", 0); ;}
    break;

  case 1124:

/* Line 1455 of yacc.c  */
#line 5959 "parser.y"
    {
	cb_emit_stop_run ((yyvsp[(4) - (4)]));
  ;}
    break;

  case 1125:

/* Line 1455 of yacc.c  */
#line 5963 "parser.y"
    {
	cb_verify (cb_stop_literal_statement, "STOP literal");
  ;}
    break;

  case 1126:

/* Line 1455 of yacc.c  */
#line 5969 "parser.y"
    { (yyval) = current_program->cb_return_code; ;}
    break;

  case 1127:

/* Line 1455 of yacc.c  */
#line 5970 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1128:

/* Line 1455 of yacc.c  */
#line 5971 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1129:

/* Line 1455 of yacc.c  */
#line 5980 "parser.y"
    { BEGIN_STATEMENT ("STRING", TERM_STRING); ;}
    break;

  case 1130:

/* Line 1455 of yacc.c  */
#line 5983 "parser.y"
    {
	cb_emit_string ((yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]));
  ;}
    break;

  case 1131:

/* Line 1455 of yacc.c  */
#line 5989 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1132:

/* Line 1455 of yacc.c  */
#line 5990 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1133:

/* Line 1455 of yacc.c  */
#line 5994 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1134:

/* Line 1455 of yacc.c  */
#line 5995 "parser.y"
    { (yyval) = cb_build_pair (cb_int0, NULL); ;}
    break;

  case 1135:

/* Line 1455 of yacc.c  */
#line 5996 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), NULL); ;}
    break;

  case 1136:

/* Line 1455 of yacc.c  */
#line 6000 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1137:

/* Line 1455 of yacc.c  */
#line 6001 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1138:

/* Line 1455 of yacc.c  */
#line 6005 "parser.y"
    { terminator_warning (TERM_STRING); ;}
    break;

  case 1139:

/* Line 1455 of yacc.c  */
#line 6006 "parser.y"
    { terminator_clear (TERM_STRING); ;}
    break;

  case 1140:

/* Line 1455 of yacc.c  */
#line 6015 "parser.y"
    { BEGIN_STATEMENT ("SUBTRACT", TERM_SUBTRACT); ;}
    break;

  case 1142:

/* Line 1455 of yacc.c  */
#line 6022 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '-', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 1143:

/* Line 1455 of yacc.c  */
#line 6026 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_list (cb_cons ((yyvsp[(3) - (6)]), (yyvsp[(1) - (6)])), '-'));
  ;}
    break;

  case 1144:

/* Line 1455 of yacc.c  */
#line 6030 "parser.y"
    {
	cb_emit_corresponding (cb_build_sub, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 1145:

/* Line 1455 of yacc.c  */
#line 6036 "parser.y"
    { terminator_warning (TERM_SUBTRACT); ;}
    break;

  case 1146:

/* Line 1455 of yacc.c  */
#line 6037 "parser.y"
    { terminator_clear (TERM_SUBTRACT); ;}
    break;

  case 1147:

/* Line 1455 of yacc.c  */
#line 6047 "parser.y"
    {
	BEGIN_STATEMENT ("SUPPRESS", 0);
	PENDING("SUPPRESS");
  ;}
    break;

  case 1150:

/* Line 1455 of yacc.c  */
#line 6062 "parser.y"
    { BEGIN_STATEMENT ("TERMINATE", 0); ;}
    break;

  case 1151:

/* Line 1455 of yacc.c  */
#line 6064 "parser.y"
    {
	PENDING("TERMINATE");
  ;}
    break;

  case 1152:

/* Line 1455 of yacc.c  */
#line 6075 "parser.y"
    { BEGIN_STATEMENT ("TRANSFORM", 0); ;}
    break;

  case 1153:

/* Line 1455 of yacc.c  */
#line 6077 "parser.y"
    {
	cb_tree		x;

	x = cb_build_converting ((yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]), cb_build_inspect_region_start ());
	cb_emit_inspect ((yyvsp[(3) - (7)]), x, cb_int0, 2);
  ;}
    break;

  case 1154:

/* Line 1455 of yacc.c  */
#line 6091 "parser.y"
    { BEGIN_STATEMENT ("UNLOCK", 0); ;}
    break;

  case 1155:

/* Line 1455 of yacc.c  */
#line 6093 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_unlock ((yyvsp[(3) - (4)]));
	}
  ;}
    break;

  case 1159:

/* Line 1455 of yacc.c  */
#line 6112 "parser.y"
    { BEGIN_STATEMENT ("UNSTRING", TERM_UNSTRING); ;}
    break;

  case 1160:

/* Line 1455 of yacc.c  */
#line 6116 "parser.y"
    {
	cb_emit_unstring ((yyvsp[(3) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]));
  ;}
    break;

  case 1161:

/* Line 1455 of yacc.c  */
#line 6122 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1162:

/* Line 1455 of yacc.c  */
#line 6124 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1163:

/* Line 1455 of yacc.c  */
#line 6128 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1164:

/* Line 1455 of yacc.c  */
#line 6130 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1165:

/* Line 1455 of yacc.c  */
#line 6135 "parser.y"
    {
	(yyval) = cb_build_unstring_delimited ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1166:

/* Line 1455 of yacc.c  */
#line 6141 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 1167:

/* Line 1455 of yacc.c  */
#line 6143 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1168:

/* Line 1455 of yacc.c  */
#line 6148 "parser.y"
    {
	(yyval) = cb_build_unstring_into ((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1169:

/* Line 1455 of yacc.c  */
#line 6154 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1170:

/* Line 1455 of yacc.c  */
#line 6155 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1171:

/* Line 1455 of yacc.c  */
#line 6159 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1172:

/* Line 1455 of yacc.c  */
#line 6160 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1173:

/* Line 1455 of yacc.c  */
#line 6164 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1174:

/* Line 1455 of yacc.c  */
#line 6165 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1175:

/* Line 1455 of yacc.c  */
#line 6169 "parser.y"
    { terminator_warning (TERM_UNSTRING); ;}
    break;

  case 1176:

/* Line 1455 of yacc.c  */
#line 6170 "parser.y"
    { terminator_clear (TERM_UNSTRING); ;}
    break;

  case 1180:

/* Line 1455 of yacc.c  */
#line 6188 "parser.y"
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

  case 1181:

/* Line 1455 of yacc.c  */
#line 6209 "parser.y"
    {
	use_global_ind = 0;
  ;}
    break;

  case 1182:

/* Line 1455 of yacc.c  */
#line 6213 "parser.y"
    {
	use_global_ind = 1;
	current_program->flag_global_use = 1;
  ;}
    break;

  case 1183:

/* Line 1455 of yacc.c  */
#line 6221 "parser.y"
    {
	cb_tree		l;

	for (l = (yyvsp[(1) - (1)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			setup_use_file (CB_FILE (cb_ref (CB_VALUE (l))));
		}
	}
  ;}
    break;

  case 1184:

/* Line 1455 of yacc.c  */
#line 6231 "parser.y"
    {
	current_program->global_handler[COB_OPEN_INPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_INPUT].handler_prog = current_program;
  ;}
    break;

  case 1185:

/* Line 1455 of yacc.c  */
#line 6236 "parser.y"
    {
	current_program->global_handler[COB_OPEN_OUTPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_OUTPUT].handler_prog = current_program;
  ;}
    break;

  case 1186:

/* Line 1455 of yacc.c  */
#line 6241 "parser.y"
    {
	current_program->global_handler[COB_OPEN_I_O].handler_label = current_section;
	current_program->global_handler[COB_OPEN_I_O].handler_prog = current_program;
  ;}
    break;

  case 1187:

/* Line 1455 of yacc.c  */
#line 6246 "parser.y"
    {
	current_program->global_handler[COB_OPEN_EXTEND].handler_label = current_section;
	current_program->global_handler[COB_OPEN_EXTEND].handler_prog = current_program;
  ;}
    break;

  case 1200:

/* Line 1455 of yacc.c  */
#line 6278 "parser.y"
    {
	PENDING ("USE FOR DEBUGGING");
  ;}
    break;

  case 1203:

/* Line 1455 of yacc.c  */
#line 6290 "parser.y"
    {
	PENDING ("USE BEFORE REPORTING");
  ;}
    break;

  case 1204:

/* Line 1455 of yacc.c  */
#line 6301 "parser.y"
    { BEGIN_STATEMENT ("WRITE", TERM_WRITE); ;}
    break;

  case 1205:

/* Line 1455 of yacc.c  */
#line 6304 "parser.y"
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
  ;}
    break;

  case 1206:

/* Line 1455 of yacc.c  */
#line 6318 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1207:

/* Line 1455 of yacc.c  */
#line 6319 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1208:

/* Line 1455 of yacc.c  */
#line 6324 "parser.y"
    {
	(yyval) = cb_int0;
  ;}
    break;

  case 1209:

/* Line 1455 of yacc.c  */
#line 6328 "parser.y"
    {
	(yyval) = cb_build_write_advancing_lines ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 1210:

/* Line 1455 of yacc.c  */
#line 6332 "parser.y"
    {
	(yyval) = cb_build_write_advancing_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1211:

/* Line 1455 of yacc.c  */
#line 6336 "parser.y"
    {
	(yyval) = cb_build_write_advancing_page ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1212:

/* Line 1455 of yacc.c  */
#line 6342 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1213:

/* Line 1455 of yacc.c  */
#line 6343 "parser.y"
    { (yyval) = CB_AFTER; ;}
    break;

  case 1217:

/* Line 1455 of yacc.c  */
#line 6352 "parser.y"
    { terminator_warning (TERM_WRITE); ;}
    break;

  case 1218:

/* Line 1455 of yacc.c  */
#line 6353 "parser.y"
    { terminator_clear (TERM_WRITE); ;}
    break;

  case 1219:

/* Line 1455 of yacc.c  */
#line 6368 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_ACCEPT;
  ;}
    break;

  case 1220:

/* Line 1455 of yacc.c  */
#line 6376 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_DISPLAY;
  ;}
    break;

  case 1222:

/* Line 1455 of yacc.c  */
#line 6383 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1223:

/* Line 1455 of yacc.c  */
#line 6387 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1225:

/* Line 1455 of yacc.c  */
#line 6394 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1226:

/* Line 1455 of yacc.c  */
#line 6398 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1229:

/* Line 1455 of yacc.c  */
#line 6414 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1230:

/* Line 1455 of yacc.c  */
#line 6419 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1232:

/* Line 1455 of yacc.c  */
#line 6426 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1233:

/* Line 1455 of yacc.c  */
#line 6431 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1234:

/* Line 1455 of yacc.c  */
#line 6443 "parser.y"
    {
	current_statement->handler_id = COB_EC_OVERFLOW;
  ;}
    break;

  case 1236:

/* Line 1455 of yacc.c  */
#line 6450 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1237:

/* Line 1455 of yacc.c  */
#line 6454 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1239:

/* Line 1455 of yacc.c  */
#line 6461 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1240:

/* Line 1455 of yacc.c  */
#line 6465 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1241:

/* Line 1455 of yacc.c  */
#line 6477 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1242:

/* Line 1455 of yacc.c  */
#line 6482 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1243:

/* Line 1455 of yacc.c  */
#line 6487 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1244:

/* Line 1455 of yacc.c  */
#line 6496 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1245:

/* Line 1455 of yacc.c  */
#line 6500 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1246:

/* Line 1455 of yacc.c  */
#line 6507 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1247:

/* Line 1455 of yacc.c  */
#line 6511 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1248:

/* Line 1455 of yacc.c  */
#line 6523 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1249:

/* Line 1455 of yacc.c  */
#line 6528 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1250:

/* Line 1455 of yacc.c  */
#line 6533 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1251:

/* Line 1455 of yacc.c  */
#line 6542 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1252:

/* Line 1455 of yacc.c  */
#line 6546 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1253:

/* Line 1455 of yacc.c  */
#line 6553 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1254:

/* Line 1455 of yacc.c  */
#line 6557 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1257:

/* Line 1455 of yacc.c  */
#line 6573 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1258:

/* Line 1455 of yacc.c  */
#line 6578 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1259:

/* Line 1455 of yacc.c  */
#line 6583 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1260:

/* Line 1455 of yacc.c  */
#line 6592 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1261:

/* Line 1455 of yacc.c  */
#line 6596 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1262:

/* Line 1455 of yacc.c  */
#line 6603 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1263:

/* Line 1455 of yacc.c  */
#line 6607 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1264:

/* Line 1455 of yacc.c  */
#line 6619 "parser.y"
    {
	(yyval) = cb_one;
  ;}
    break;

  case 1265:

/* Line 1455 of yacc.c  */
#line 6623 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 1266:

/* Line 1455 of yacc.c  */
#line 6635 "parser.y"
    {
	(yyval) = cb_build_cond ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1267:

/* Line 1455 of yacc.c  */
#line 6642 "parser.y"
    {
	(yyval) = cb_build_expr ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1268:

/* Line 1455 of yacc.c  */
#line 6648 "parser.y"
    {
	current_expr = NULL;
  ;}
    break;

  case 1269:

/* Line 1455 of yacc.c  */
#line 6652 "parser.y"
    {
	(yyval) = cb_list_reverse (current_expr);
  ;}
    break;

  case 1271:

/* Line 1455 of yacc.c  */
#line 6659 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1272:

/* Line 1455 of yacc.c  */
#line 6660 "parser.y"
    { push_expr (')', NULL); ;}
    break;

  case 1273:

/* Line 1455 of yacc.c  */
#line 6662 "parser.y"
    { push_expr ('O', NULL); ;}
    break;

  case 1274:

/* Line 1455 of yacc.c  */
#line 6663 "parser.y"
    { push_expr ('9', NULL); ;}
    break;

  case 1275:

/* Line 1455 of yacc.c  */
#line 6664 "parser.y"
    { push_expr ('A', NULL); ;}
    break;

  case 1276:

/* Line 1455 of yacc.c  */
#line 6665 "parser.y"
    { push_expr ('L', NULL); ;}
    break;

  case 1277:

/* Line 1455 of yacc.c  */
#line 6666 "parser.y"
    { push_expr ('U', NULL); ;}
    break;

  case 1278:

/* Line 1455 of yacc.c  */
#line 6667 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1279:

/* Line 1455 of yacc.c  */
#line 6669 "parser.y"
    { push_expr ('P', NULL); ;}
    break;

  case 1280:

/* Line 1455 of yacc.c  */
#line 6670 "parser.y"
    { push_expr ('N', NULL); ;}
    break;

  case 1281:

/* Line 1455 of yacc.c  */
#line 6671 "parser.y"
    { push_expr ('x', cb_zero); ;}
    break;

  case 1282:

/* Line 1455 of yacc.c  */
#line 6673 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1285:

/* Line 1455 of yacc.c  */
#line 6679 "parser.y"
    { push_expr ('(', NULL); ;}
    break;

  case 1286:

/* Line 1455 of yacc.c  */
#line 6681 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1287:

/* Line 1455 of yacc.c  */
#line 6682 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1288:

/* Line 1455 of yacc.c  */
#line 6683 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1289:

/* Line 1455 of yacc.c  */
#line 6685 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1290:

/* Line 1455 of yacc.c  */
#line 6687 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1291:

/* Line 1455 of yacc.c  */
#line 6688 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1292:

/* Line 1455 of yacc.c  */
#line 6689 "parser.y"
    { push_expr ('*', NULL); ;}
    break;

  case 1293:

/* Line 1455 of yacc.c  */
#line 6690 "parser.y"
    { push_expr ('/', NULL); ;}
    break;

  case 1294:

/* Line 1455 of yacc.c  */
#line 6691 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1295:

/* Line 1455 of yacc.c  */
#line 6693 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1296:

/* Line 1455 of yacc.c  */
#line 6694 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1297:

/* Line 1455 of yacc.c  */
#line 6695 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1298:

/* Line 1455 of yacc.c  */
#line 6696 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1299:

/* Line 1455 of yacc.c  */
#line 6697 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1300:

/* Line 1455 of yacc.c  */
#line 6698 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1301:

/* Line 1455 of yacc.c  */
#line 6700 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1302:

/* Line 1455 of yacc.c  */
#line 6701 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1303:

/* Line 1455 of yacc.c  */
#line 6702 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1304:

/* Line 1455 of yacc.c  */
#line 6703 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1305:

/* Line 1455 of yacc.c  */
#line 6704 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1306:

/* Line 1455 of yacc.c  */
#line 6705 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1307:

/* Line 1455 of yacc.c  */
#line 6707 "parser.y"
    { push_expr ('&', NULL); ;}
    break;

  case 1308:

/* Line 1455 of yacc.c  */
#line 6708 "parser.y"
    { push_expr ('|', NULL); ;}
    break;

  case 1322:

/* Line 1455 of yacc.c  */
#line 6720 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1323:

/* Line 1455 of yacc.c  */
#line 6721 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1327:

/* Line 1455 of yacc.c  */
#line 6730 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1328:

/* Line 1455 of yacc.c  */
#line 6731 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '+', (yyvsp[(3) - (3)])); ;}
    break;

  case 1329:

/* Line 1455 of yacc.c  */
#line 6732 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '-', (yyvsp[(3) - (3)])); ;}
    break;

  case 1330:

/* Line 1455 of yacc.c  */
#line 6733 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '*', (yyvsp[(3) - (3)])); ;}
    break;

  case 1331:

/* Line 1455 of yacc.c  */
#line 6734 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '/', (yyvsp[(3) - (3)])); ;}
    break;

  case 1332:

/* Line 1455 of yacc.c  */
#line 6735 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1333:

/* Line 1455 of yacc.c  */
#line 6736 "parser.y"
    { (yyval) = cb_build_binary_op (cb_zero, '-', (yyvsp[(2) - (2)])); ;}
    break;

  case 1334:

/* Line 1455 of yacc.c  */
#line 6737 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '^', (yyvsp[(3) - (3)])); ;}
    break;

  case 1335:

/* Line 1455 of yacc.c  */
#line 6738 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1336:

/* Line 1455 of yacc.c  */
#line 6750 "parser.y"
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

  case 1337:

/* Line 1455 of yacc.c  */
#line 6762 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(3) - (3)])))) {
		(yyval) = CB_FILE (cb_ref ((yyvsp[(3) - (3)])))->linage_ctr;
	} else {
		cb_error_x ((yyvsp[(3) - (3)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(3) - (3)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1338:

/* Line 1455 of yacc.c  */
#line 6776 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1339:

/* Line 1455 of yacc.c  */
#line 6778 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1340:

/* Line 1455 of yacc.c  */
#line 6782 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)])); ;}
    break;

  case 1341:

/* Line 1455 of yacc.c  */
#line 6789 "parser.y"
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
  ;}
    break;

  case 1342:

/* Line 1455 of yacc.c  */
#line 6811 "parser.y"
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

  case 1343:

/* Line 1455 of yacc.c  */
#line 6831 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1344:

/* Line 1455 of yacc.c  */
#line 6835 "parser.y"
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

  case 1345:

/* Line 1455 of yacc.c  */
#line 6851 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (1)])))) {
		(yyval) = (yyvsp[(1) - (1)]);
	} else {
		cb_error_x ((yyvsp[(1) - (1)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(1) - (1)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1346:

/* Line 1455 of yacc.c  */
#line 6864 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1347:

/* Line 1455 of yacc.c  */
#line 6866 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1348:

/* Line 1455 of yacc.c  */
#line 6870 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1349:

/* Line 1455 of yacc.c  */
#line 6876 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1350:

/* Line 1455 of yacc.c  */
#line 6878 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1351:

/* Line 1455 of yacc.c  */
#line 6883 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	CB_REFERENCE ((yyval))->offset = CB_TREE (current_section);
	current_program->label_list = cb_cons ((yyval), current_program->label_list);
  ;}
    break;

  case 1355:

/* Line 1455 of yacc.c  */
#line 6898 "parser.y"
    {
	(yyval) = cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(1) - (1)]))->data));
	(yyval)->source_file = (yyvsp[(1) - (1)])->source_file;
	(yyval)->source_line = (yyvsp[(1) - (1)])->source_line;
  ;}
    break;

  case 1356:

/* Line 1455 of yacc.c  */
#line 6908 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1357:

/* Line 1455 of yacc.c  */
#line 6909 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1358:

/* Line 1455 of yacc.c  */
#line 6914 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	current_program->reference_list = cb_cons ((yyval), current_program->reference_list);
  ;}
    break;

  case 1359:

/* Line 1455 of yacc.c  */
#line 6921 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1360:

/* Line 1455 of yacc.c  */
#line 6922 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1363:

/* Line 1455 of yacc.c  */
#line 6934 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE ((yyval))->word->count > 0) {
		redefinition_error ((yyval));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1364:

/* Line 1455 of yacc.c  */
#line 6953 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1365:

/* Line 1455 of yacc.c  */
#line 6954 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1367:

/* Line 1455 of yacc.c  */
#line 6959 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1368:

/* Line 1455 of yacc.c  */
#line 6963 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1369:

/* Line 1455 of yacc.c  */
#line 6964 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1371:

/* Line 1455 of yacc.c  */
#line 6969 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1372:

/* Line 1455 of yacc.c  */
#line 6970 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1373:

/* Line 1455 of yacc.c  */
#line 6971 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1374:

/* Line 1455 of yacc.c  */
#line 6972 "parser.y"
    { (yyval) = cb_build_ppointer ((yyvsp[(4) - (4)])); ;}
    break;

  case 1375:

/* Line 1455 of yacc.c  */
#line 6973 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1380:

/* Line 1455 of yacc.c  */
#line 6981 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1381:

/* Line 1455 of yacc.c  */
#line 6982 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1382:

/* Line 1455 of yacc.c  */
#line 6983 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1388:

/* Line 1455 of yacc.c  */
#line 6995 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1389:

/* Line 1455 of yacc.c  */
#line 6996 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1401:

/* Line 1455 of yacc.c  */
#line 7030 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1402:

/* Line 1455 of yacc.c  */
#line 7038 "parser.y"
    { (yyval) = cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1403:

/* Line 1455 of yacc.c  */
#line 7042 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1404:

/* Line 1455 of yacc.c  */
#line 7043 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1405:

/* Line 1455 of yacc.c  */
#line 7044 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1406:

/* Line 1455 of yacc.c  */
#line 7045 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 1407:

/* Line 1455 of yacc.c  */
#line 7049 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1408:

/* Line 1455 of yacc.c  */
#line 7050 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); CB_REFERENCE ((yyvsp[(1) - (3)]))->chain = (yyvsp[(3) - (3)]); ;}
    break;

  case 1409:

/* Line 1455 of yacc.c  */
#line 7055 "parser.y"
    {
	if (cb_ref ((yyvsp[(0) - (3)])) != cb_error_node) {
		(yyval) = (yyvsp[(0) - (3)]);
		CB_REFERENCE ((yyvsp[(0) - (3)]))->subs = cb_list_reverse ((yyvsp[(2) - (3)]));
	}
  ;}
    break;

  case 1410:

/* Line 1455 of yacc.c  */
#line 7065 "parser.y"
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

  case 1411:

/* Line 1455 of yacc.c  */
#line 7083 "parser.y"
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

  case 1412:

/* Line 1455 of yacc.c  */
#line 7110 "parser.y"
    {
	if (cb_tree_category ((yyvsp[(1) - (1)])) != CB_CATEGORY_NUMERIC) {
		cb_error (_("Integer value expected"));
	} else if (CB_LITERAL ((yyvsp[(1) - (1)]))->sign < 0 || CB_LITERAL ((yyvsp[(1) - (1)]))->scale) {
		cb_error (_("Integer value expected"));
	}
	(yyval) = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1413:

/* Line 1455 of yacc.c  */
#line 7121 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1414:

/* Line 1455 of yacc.c  */
#line 7123 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (2)]);
	if (CB_LITERAL_P ((yyvsp[(2) - (2)]))) {
		CB_LITERAL ((yyvsp[(2) - (2)]))->all = 1;
	}
  ;}
    break;

  case 1415:

/* Line 1455 of yacc.c  */
#line 7132 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1416:

/* Line 1455 of yacc.c  */
#line 7133 "parser.y"
    { (yyval) = cb_concat_literals ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1417:

/* Line 1455 of yacc.c  */
#line 7137 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1418:

/* Line 1455 of yacc.c  */
#line 7138 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 1419:

/* Line 1455 of yacc.c  */
#line 7139 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1420:

/* Line 1455 of yacc.c  */
#line 7140 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 1421:

/* Line 1455 of yacc.c  */
#line 7141 "parser.y"
    { (yyval) = cb_high; ;}
    break;

  case 1422:

/* Line 1455 of yacc.c  */
#line 7142 "parser.y"
    { (yyval) = cb_low; ;}
    break;

  case 1423:

/* Line 1455 of yacc.c  */
#line 7143 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1424:

/* Line 1455 of yacc.c  */
#line 7152 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1425:

/* Line 1455 of yacc.c  */
#line 7156 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1426:

/* Line 1455 of yacc.c  */
#line 7160 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1427:

/* Line 1455 of yacc.c  */
#line 7164 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1428:

/* Line 1455 of yacc.c  */
#line 7168 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1429:

/* Line 1455 of yacc.c  */
#line 7172 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1430:

/* Line 1455 of yacc.c  */
#line 7176 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1431:

/* Line 1455 of yacc.c  */
#line 7180 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1432:

/* Line 1455 of yacc.c  */
#line 7184 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1433:

/* Line 1455 of yacc.c  */
#line 7188 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), NULL);
  ;}
    break;

  case 1434:

/* Line 1455 of yacc.c  */
#line 7192 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1435:

/* Line 1455 of yacc.c  */
#line 7196 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), NULL);
  ;}
    break;

  case 1436:

/* Line 1455 of yacc.c  */
#line 7202 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1437:

/* Line 1455 of yacc.c  */
#line 7203 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (4)]), NULL); ;}
    break;

  case 1438:

/* Line 1455 of yacc.c  */
#line 7204 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 1439:

/* Line 1455 of yacc.c  */
#line 7208 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1440:

/* Line 1455 of yacc.c  */
#line 7209 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1441:

/* Line 1455 of yacc.c  */
#line 7213 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1442:

/* Line 1455 of yacc.c  */
#line 7214 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1443:

/* Line 1455 of yacc.c  */
#line 7220 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_int0);
  ;}
    break;

  case 1444:

/* Line 1455 of yacc.c  */
#line 7227 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int1);
  ;}
    break;

  case 1445:

/* Line 1455 of yacc.c  */
#line 7234 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int2);
  ;}
    break;

  case 1446:

/* Line 1455 of yacc.c  */
#line 7244 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1447:

/* Line 1455 of yacc.c  */
#line 7251 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1448:

/* Line 1455 of yacc.c  */
#line 7261 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1449:

/* Line 1455 of yacc.c  */
#line 7268 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_ref ((yyvsp[(3) - (3)])));
  ;}
    break;

  case 1450:

/* Line 1455 of yacc.c  */
#line 7281 "parser.y"
    {
	non_const_word = 1;
  ;}
    break;

  case 1451:

/* Line 1455 of yacc.c  */
#line 7291 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1452:

/* Line 1455 of yacc.c  */
#line 7292 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1453:

/* Line 1455 of yacc.c  */
#line 7296 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1454:

/* Line 1455 of yacc.c  */
#line 7297 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1455:

/* Line 1455 of yacc.c  */
#line 7301 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1456:

/* Line 1455 of yacc.c  */
#line 7302 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1457:

/* Line 1455 of yacc.c  */
#line 7306 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1458:

/* Line 1455 of yacc.c  */
#line 7307 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1459:

/* Line 1455 of yacc.c  */
#line 7308 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 1460:

/* Line 1455 of yacc.c  */
#line 7312 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1461:

/* Line 1455 of yacc.c  */
#line 7313 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1462:

/* Line 1455 of yacc.c  */
#line 7317 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1463:

/* Line 1455 of yacc.c  */
#line 7318 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1464:

/* Line 1455 of yacc.c  */
#line 7322 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1465:

/* Line 1455 of yacc.c  */
#line 7323 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1466:

/* Line 1455 of yacc.c  */
#line 7327 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1467:

/* Line 1455 of yacc.c  */
#line 7328 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1479:

/* Line 1455 of yacc.c  */
#line 7341 "parser.y"
    { (yyval) = cb_int1; ;}
    break;



/* Line 1455 of yacc.c  */
#line 14576 "parser.c"
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
#line 7385 "parser.y"


