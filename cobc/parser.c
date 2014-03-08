
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
#define YYLAST   5659

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  457
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  707
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1581
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2317

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
     687,   690,   693,   694,   698,   699,   702,   704,   706,   709,
     711,   713,   715,   721,   722,   724,   726,   728,   734,   736,
     739,   742,   743,   746,   751,   752,   762,   763,   764,   770,
     771,   775,   776,   779,   783,   786,   789,   791,   793,   794,
     799,   800,   803,   806,   809,   811,   813,   815,   817,   819,
     821,   823,   825,   827,   829,   835,   836,   838,   840,   845,
     852,   862,   863,   867,   868,   871,   872,   875,   879,   881,
     883,   889,   895,   897,   899,   903,   909,   910,   913,   915,
     917,   919,   925,   930,   934,   939,   943,   947,   951,   952,
     953,   959,   960,   962,   963,   966,   969,   973,   976,   978,
     979,   985,   986,   991,   993,   995,   996,   998,   999,  1001,
    1003,  1005,  1006,  1009,  1011,  1015,  1019,  1026,  1027,  1030,
    1032,  1034,  1036,  1038,  1040,  1042,  1044,  1046,  1048,  1050,
    1052,  1054,  1056,  1058,  1060,  1063,  1067,  1068,  1071,  1074,
    1076,  1078,  1082,  1084,  1086,  1088,  1090,  1092,  1094,  1096,
    1098,  1100,  1102,  1104,  1106,  1108,  1110,  1112,  1114,  1116,
    1118,  1120,  1123,  1126,  1128,  1131,  1134,  1136,  1139,  1142,
    1144,  1147,  1150,  1152,  1155,  1158,  1160,  1162,  1166,  1170,
    1171,  1174,  1177,  1184,  1185,  1188,  1189,  1193,  1194,  1196,
    1198,  1203,  1205,  1208,  1210,  1212,  1213,  1215,  1219,  1221,
    1224,  1226,  1229,  1232,  1233,  1235,  1237,  1241,  1243,  1247,
    1248,  1257,  1259,  1262,  1264,  1268,  1269,  1273,  1276,  1281,
    1284,  1285,  1286,  1292,  1293,  1294,  1300,  1301,  1302,  1308,
    1309,  1311,  1313,  1316,  1322,  1323,  1326,  1329,  1333,  1335,
    1337,  1340,  1343,  1346,  1347,  1349,  1351,  1354,  1363,  1364,
    1368,  1369,  1374,  1375,  1380,  1381,  1385,  1386,  1390,  1392,
    1397,  1400,  1402,  1404,  1405,  1408,  1413,  1414,  1417,  1419,
    1421,  1423,  1425,  1427,  1429,  1431,  1433,  1435,  1437,  1439,
    1441,  1443,  1445,  1447,  1449,  1453,  1455,  1457,  1459,  1461,
    1463,  1465,  1467,  1472,  1477,  1480,  1482,  1484,  1487,  1491,
    1493,  1497,  1504,  1507,  1511,  1514,  1516,  1519,  1522,  1524,
    1527,  1528,  1530,  1532,  1537,  1540,  1541,  1543,  1545,  1546,
    1547,  1548,  1555,  1556,  1558,  1560,  1563,  1565,  1566,  1572,
    1573,  1576,  1578,  1580,  1582,  1584,  1587,  1590,  1592,  1594,
    1596,  1598,  1600,  1602,  1604,  1606,  1608,  1610,  1616,  1622,
    1626,  1630,  1632,  1634,  1636,  1638,  1640,  1642,  1644,  1647,
    1650,  1653,  1654,  1656,  1658,  1660,  1662,  1663,  1665,  1667,
    1669,  1671,  1675,  1676,  1677,  1678,  1688,  1689,  1690,  1694,
    1695,  1699,  1701,  1704,  1709,  1710,  1713,  1716,  1717,  1721,
    1725,  1730,  1734,  1735,  1737,  1738,  1741,  1742,  1743,  1751,
    1752,  1755,  1757,  1759,  1761,  1764,  1766,  1771,  1774,  1776,
    1778,  1779,  1781,  1782,  1783,  1787,  1788,  1791,  1793,  1795,
    1797,  1799,  1801,  1803,  1805,  1807,  1809,  1811,  1813,  1815,
    1817,  1819,  1821,  1823,  1825,  1827,  1829,  1831,  1833,  1835,
    1837,  1839,  1841,  1843,  1845,  1847,  1849,  1851,  1853,  1855,
    1857,  1859,  1861,  1863,  1865,  1867,  1869,  1871,  1873,  1875,
    1877,  1879,  1881,  1883,  1885,  1887,  1889,  1891,  1892,  1897,
    1902,  1907,  1911,  1915,  1919,  1924,  1928,  1933,  1937,  1941,
    1945,  1950,  1956,  1960,  1965,  1969,  1973,  1974,  1978,  1982,
    1985,  1988,  1991,  1995,  1999,  2003,  2004,  2007,  2009,  2012,
    2014,  2016,  2018,  2020,  2022,  2024,  2026,  2030,  2034,  2038,
    2042,  2044,  2046,  2048,  2050,  2052,  2054,  2055,  2057,  2058,
    2063,  2068,  2074,  2081,  2082,  2085,  2086,  2088,  2089,  2093,
    2097,  2103,  2104,  2107,  2110,  2111,  2117,  2118,  2121,  2122,
    2131,  2132,  2133,  2137,  2139,  2142,  2145,  2149,  2150,  2153,
    2156,  2159,  2160,  2163,  2166,  2167,  2168,  2172,  2173,  2174,
    2178,  2179,  2181,  2182,  2186,  2187,  2190,  2191,  2195,  2196,
    2200,  2201,  2203,  2207,  2211,  2214,  2216,  2218,  2219,  2224,
    2229,  2230,  2232,  2234,  2236,  2238,  2240,  2241,  2248,  2249,
    2251,  2252,  2257,  2258,  2263,  2267,  2271,  2275,  2279,  2284,
    2291,  2298,  2305,  2312,  2313,  2316,  2319,  2321,  2324,  2326,
    2328,  2331,  2334,  2336,  2338,  2340,  2342,  2344,  2348,  2352,
    2356,  2360,  2362,  2364,  2365,  2367,  2368,  2373,  2378,  2385,
    2392,  2401,  2410,  2411,  2413,  2414,  2419,  2420,  2426,  2428,
    2432,  2434,  2436,  2438,  2441,  2443,  2446,  2447,  2451,  2452,
    2453,  2457,  2460,  2464,  2466,  2470,  2473,  2475,  2477,  2479,
    2480,  2483,  2484,  2486,  2487,  2491,  2492,  2494,  2496,  2499,
    2501,  2503,  2504,  2508,  2509,  2513,  2514,  2520,  2521,  2525,
    2526,  2529,  2530,  2531,  2540,  2544,  2545,  2546,  2550,  2551,
    2553,  2554,  2562,  2563,  2566,  2567,  2571,  2575,  2576,  2579,
    2581,  2584,  2589,  2591,  2593,  2595,  2597,  2599,  2601,  2603,
    2604,  2606,  2607,  2611,  2612,  2617,  2619,  2621,  2623,  2625,
    2628,  2630,  2632,  2634,  2635,  2639,  2641,  2644,  2647,  2650,
    2652,  2654,  2656,  2659,  2662,  2664,  2667,  2672,  2675,  2676,
    2678,  2680,  2682,  2684,  2689,  2695,  2696,  2701,  2702,  2704,
    2705,  2709,  2710,  2714,  2718,  2723,  2724,  2729,  2734,  2741,
    2742,  2744,  2745,  2749,  2750,  2756,  2758,  2760,  2762,  2764,
    2765,  2769,  2770,  2774,  2777,  2778,  2782,  2785,  2786,  2791,
    2794,  2795,  2797,  2799,  2803,  2804,  2806,  2809,  2813,  2817,
    2818,  2822,  2824,  2828,  2836,  2837,  2848,  2849,  2852,  2853,
    2856,  2859,  2863,  2867,  2870,  2871,  2875,  2876,  2878,  2880,
    2881,  2883,  2884,  2889,  2890,  2898,  2899,  2901,  2902,  2910,
    2911,  2914,  2918,  2919,  2921,  2923,  2924,  2929,  2934,  2935,
    2943,  2944,  2947,  2948,  2949,  2954,  2956,  2959,  2960,  2965,
    2966,  2968,  2969,  2973,  2975,  2977,  2979,  2981,  2983,  2988,
    2993,  2997,  3002,  3004,  3006,  3008,  3011,  3015,  3017,  3020,
    3024,  3028,  3029,  3033,  3034,  3042,  3043,  3049,  3050,  3053,
    3054,  3057,  3058,  3062,  3063,  3066,  3071,  3072,  3075,  3080,
    3081,  3082,  3090,  3091,  3096,  3099,  3102,  3105,  3108,  3111,
    3112,  3114,  3115,  3120,  3123,  3124,  3127,  3130,  3131,  3140,
    3142,  3145,  3147,  3151,  3155,  3156,  3160,  3161,  3163,  3164,
    3169,  3174,  3181,  3188,  3189,  3191,  3194,  3195,  3197,  3198,
    3202,  3203,  3211,  3212,  3217,  3218,  3220,  3222,  3223,  3233,
    3234,  3238,  3240,  3244,  3247,  3250,  3253,  3257,  3258,  3262,
    3263,  3267,  3268,  3272,  3273,  3275,  3277,  3279,  3281,  3290,
    3291,  3293,  3295,  3297,  3299,  3301,  3303,  3304,  3306,  3307,
    3309,  3311,  3313,  3315,  3317,  3319,  3321,  3322,  3324,  3330,
    3332,  3335,  3341,  3342,  3351,  3352,  3355,  3356,  3361,  3365,
    3369,  3371,  3373,  3374,  3376,  3378,  3379,  3381,  3384,  3387,
    3388,  3389,  3393,  3394,  3395,  3399,  3402,  3403,  3404,  3408,
    3409,  3410,  3414,  3417,  3418,  3419,  3423,  3424,  3425,  3429,
    3431,  3433,  3436,  3437,  3441,  3442,  3446,  3448,  3450,  3453,
    3454,  3458,  3459,  3463,  3464,  3466,  3468,  3470,  3473,  3474,
    3478,  3479,  3483,  3484,  3488,  3490,  3492,  3493,  3496,  3499,
    3502,  3505,  3508,  3511,  3514,  3517,  3520,  3523,  3526,  3529,
    3532,  3535,  3538,  3541,  3544,  3547,  3550,  3553,  3554,  3557,
    3560,  3563,  3566,  3569,  3572,  3575,  3578,  3581,  3584,  3587,
    3590,  3593,  3596,  3599,  3602,  3605,  3608,  3611,  3614,  3617,
    3620,  3623,  3626,  3629,  3632,  3635,  3637,  3640,  3642,  3644,
    3647,  3649,  3652,  3654,  3660,  3665,  3667,  3673,  3678,  3680,
    3684,  3685,  3687,  3689,  3691,  3695,  3699,  3703,  3707,  3710,
    3713,  3717,  3721,  3723,  3727,  3729,  3732,  3735,  3737,  3739,
    3741,  3744,  3746,  3748,  3751,  3753,  3754,  3757,  3759,  3761,
    3763,  3767,  3769,  3771,  3774,  3776,  3778,  3781,  3782,  3784,
    3786,  3788,  3790,  3792,  3795,  3797,  3801,  3803,  3806,  3808,
    3812,  3816,  3820,  3825,  3829,  3831,  3833,  3835,  3837,  3841,
    3845,  3849,  3851,  3853,  3855,  3857,  3859,  3861,  3863,  3865,
    3867,  3869,  3871,  3873,  3875,  3877,  3879,  3881,  3883,  3885,
    3887,  3889,  3891,  3894,  3897,  3901,  3903,  3907,  3911,  3916,
    3922,  3924,  3926,  3929,  3931,  3935,  3937,  3939,  3941,  3943,
    3945,  3947,  3949,  3952,  3955,  3961,  3967,  3973,  3979,  3985,
    3991,  3997,  4002,  4008,  4011,  4012,  4017,  4023,  4024,  4028,
    4029,  4031,  4033,  4037,  4041,  4043,  4047,  4049,  4053,  4054,
    4055,  4057,  4058,  4060,  4061,  4063,  4064,  4066,  4068,  4069,
    4071,  4072,  4074,  4075,  4077,  4078,  4081,  4083,  4085,  4088,
    4091,  4094,  4096,  4099,  4101,  4102,  4104,  4105,  4107,  4108,
    4110,  4111,  4113,  4114,  4116,  4117,  4119,  4120,  4122,  4123,
    4125,  4126,  4128,  4129,  4131,  4132,  4134,  4135,  4137,  4138,
    4140,  4141,  4143,  4144,  4146,  4147,  4149,  4150,  4152,  4153,
    4155,  4157,  4158,  4160,  4161,  4163,  4165,  4166,  4168,  4169,
    4171,  4172,  4174,  4175,  4177,  4178,  4180,  4181,  4183,  4186,
    4187,  4189,  4190,  4192,  4193,  4195,  4196,  4198,  4199,  4201,
    4202,  4204,  4205,  4207,  4210,  4211,  4213,  4214,  4216,  4217,
    4219,  4220,  4222,  4223,  4225,  4226,  4228,  4229,  4231,  4232,
    4234,  4235
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     458,     0,    -1,    -1,   459,   460,     0,    -1,   461,    -1,
     460,   461,    -1,   462,    -1,   468,    -1,    -1,    -1,   475,
     483,   463,   585,   464,   727,   471,   472,    -1,    -1,    -1,
     475,   483,   466,   585,   467,   727,   471,   473,    -1,    -1,
      -1,   477,   483,   469,   585,   470,   727,   474,    -1,    -1,
     465,    -1,   471,   465,    -1,    -1,   136,   478,   449,    -1,
     136,   478,   449,    -1,   132,   478,   449,    -1,    -1,   306,
     449,   478,   479,   476,   480,   449,    -1,   179,   449,   478,
     479,   449,    -1,   307,    -1,   232,    -1,    -1,    27,   232,
      -1,    -1,  1138,   481,  1149,    -1,    72,    -1,    72,   482,
      -1,   482,    -1,   401,    -1,   317,    -1,    -1,   147,   117,
     449,   484,   538,    -1,    -1,    82,   351,   449,   485,    -1,
      -1,   485,   486,    -1,   487,    -1,   491,    -1,   504,    -1,
     499,    -1,   372,   449,   488,    -1,    -1,   490,   449,    -1,
     490,   489,   449,    -1,   489,   449,    -1,  1163,   104,   245,
      -1,   436,    -1,   270,   449,   492,    -1,    -1,   490,   449,
      -1,   490,   493,   449,    -1,   493,   449,    -1,   494,    -1,
     493,   494,    -1,   495,    -1,   497,    -1,   498,    -1,   241,
     367,  1138,  1098,   496,    -1,    56,    -1,   437,    -1,  1149,
    1121,  1138,  1076,    -1,   353,  1138,  1098,    -1,   332,   449,
     500,    -1,    -1,   501,   449,    -1,   502,    -1,   501,   502,
      -1,   178,   503,   207,    -1,   178,     9,   207,    -1,   232,
      -1,   503,   232,    -1,   374,   449,   505,    -1,    -1,   506,
      -1,   506,   449,    -1,   507,    -1,   506,   507,    -1,   508,
      -1,   515,    -1,   524,    -1,   531,    -1,   528,    -1,   532,
      -1,   533,    -1,   534,    -1,   535,    -1,   536,    -1,   537,
      -1,   436,  1138,    94,    -1,    -1,   436,  1138,  1080,   509,
     511,    -1,    -1,   436,  1138,   510,   512,    -1,    25,  1138,
    1080,    -1,    26,  1138,  1080,    -1,   148,  1138,  1080,    -1,
     149,  1138,  1080,    -1,    -1,   511,   513,    -1,   513,    -1,
     512,   513,    -1,   514,  1156,  1138,  1080,    -1,   275,    -1,
     273,    -1,    -1,    11,  1080,   516,  1138,   517,    -1,   251,
      -1,   376,    -1,   377,    -1,   121,    -1,   518,    -1,   519,
      -1,   518,   519,    -1,   522,    -1,   522,   395,   522,    -1,
      -1,   522,    17,   520,   521,    -1,   523,    -1,   521,    17,
     523,    -1,   232,    -1,   373,    -1,   442,    -1,   310,    -1,
     191,    -1,   239,    -1,   232,    -1,   373,    -1,   442,    -1,
     310,    -1,   191,    -1,   239,    -1,   387,  1131,   525,    -1,
     526,  1139,   527,    -1,  1080,    -1,   526,  1080,    -1,  1098,
      -1,   527,  1098,    -1,    57,  1080,  1138,   529,    -1,   530,
      -1,   529,   530,    -1,  1101,    -1,  1101,   395,  1101,    -1,
     233,  1080,  1138,  1076,    -1,    95,  1153,  1138,   232,    -1,
     105,  1138,    67,    -1,    97,  1138,  1076,    -1,    94,   379,
    1138,  1076,    -1,   347,  1138,  1076,    -1,   159,  1138,  1076,
      -1,    -1,   204,   351,   449,   541,   574,    -1,    -1,   166,
     449,   539,   542,    -1,    -1,   212,   449,   540,   575,    -1,
      -1,   166,   449,   542,    -1,    -1,   542,   543,    -1,    -1,
     354,  1115,  1080,   544,   545,   449,    -1,    -1,   545,   546,
      -1,   547,    -1,   551,    -1,   553,    -1,   558,    -1,   559,
      -1,   561,    -1,   565,    -1,   567,    -1,   568,    -1,   569,
      -1,   570,    -1,   571,    -1,   572,    -1,     1,    -1,    29,
    1161,   549,   548,   550,    -1,    29,  1161,   549,   114,    -1,
      29,  1161,   549,   300,    -1,    -1,   114,    -1,   300,    -1,
      -1,   164,    -1,   120,    -1,   232,    -1,   115,    -1,  1095,
      -1,     4,  1143,  1138,   552,    -1,   359,    -1,   120,    -1,
     311,    -1,    19,   314,  1140,  1138,  1076,  1111,    -1,    19,
     314,  1140,  1138,  1076,   557,   554,  1111,    -1,    -1,   555,
     556,    -1,   554,   556,    -1,  1076,    -1,    -1,   371,  1138,
      -1,   450,    -1,  1121,  1138,   436,    -1,   560,   379,  1138,
    1076,  1078,    -1,    -1,   400,    -1,   369,    -1,   236,  1143,
    1138,   562,    -1,   240,   563,    -1,    32,   563,    -1,   161,
      -1,    -1,   435,   236,   275,   564,    -1,   435,   236,   275,
     247,   564,    -1,   435,   342,    -1,   314,    -1,   316,    -1,
     281,  1138,   566,    -1,   566,    -1,   198,    -1,   314,  1128,
     359,    -1,   359,    -1,   321,    -1,   229,   359,    -1,   287,
    1130,  1138,  1079,    -1,   314,   110,  1138,   376,    -1,   314,
    1140,  1138,  1076,    -1,   314,  1140,  1138,  1076,   557,   554,
      -1,   321,  1140,  1138,  1076,    -1,   334,  1098,  1125,    -1,
     361,  1163,   573,    -1,     9,  1148,    -1,   256,  1148,    -1,
     313,   276,    -1,    -1,   212,   449,   575,    -1,    -1,   576,
     449,    -1,   576,    -1,   577,    -1,   576,   577,    -1,   578,
      -1,   580,    -1,   584,    -1,   345,   579,  1125,  1135,  1067,
      -1,    -1,   314,    -1,   369,    -1,   370,    -1,   247,  1134,
    1157,  1132,   581,    -1,   582,    -1,   581,   582,    -1,  1068,
     583,    -1,    -1,   296,  1098,    -1,    22,    71,  1146,  1075,
      -1,    -1,    99,   117,   449,   586,   617,   670,   672,   674,
     715,    -1,    -1,    -1,   400,   351,   449,   587,   589,    -1,
      -1,   592,   588,   591,    -1,    -1,   589,   590,    -1,   592,
     593,   619,    -1,   593,   619,    -1,   591,   590,    -1,   165,
      -1,   349,    -1,    -1,  1068,   594,   595,   449,    -1,    -1,
     595,   596,    -1,  1138,   164,    -1,  1138,   184,    -1,   597,
      -1,   599,    -1,   603,    -1,   605,    -1,   607,    -1,   608,
      -1,   614,    -1,   615,    -1,   616,    -1,     1,    -1,    47,
    1132,  1098,   602,   598,    -1,    -1,   316,    -1,    56,    -1,
     314,  1132,  1098,  1131,    -1,   314,  1132,  1098,   398,  1098,
    1131,    -1,   314,  1138,   430,  1137,  1155,   601,   602,  1131,
     600,    -1,    -1,   111,  1146,  1076,    -1,    -1,  1136,  1098,
      -1,    -1,   398,  1098,    -1,   215,  1119,   604,    -1,   375,
      -1,   274,    -1,   429,   272,   436,  1138,   606,    -1,   429,
     272,   167,  1138,   606,    -1,   232,    -1,  1095,    -1,    99,
    1119,  1077,    -1,   227,  1138,  1079,  1142,   609,    -1,    -1,
     609,   610,    -1,   611,    -1,   612,    -1,   613,    -1,  1163,
     171,  1127,  1079,  1142,    -1,  1127,   404,  1079,  1142,    -1,
    1127,    48,  1079,    -1,   315,  1143,  1138,   436,    -1,    61,
    1138,   436,    -1,   327,  1138,   714,    -1,   329,  1124,   714,
      -1,    -1,    -1,   438,   351,   449,   618,   619,    -1,    -1,
     620,    -1,    -1,   621,   622,    -1,  1109,   623,    -1,   622,
    1109,   623,    -1,   622,   449,    -1,   633,    -1,    -1,   626,
     629,   624,   634,   628,    -1,    -1,   627,   629,   625,   663,
      -1,   223,    -1,   224,    -1,    -1,   232,    -1,    -1,   168,
      -1,   436,    -1,   436,    -1,    -1,  1138,   184,    -1,  1099,
      -1,   221,  1145,  1094,    -1,    50,  1145,  1094,    -1,   626,
     630,    83,   631,  1126,   632,    -1,    -1,   634,   635,    -1,
     636,    -1,   637,    -1,   639,    -1,   640,    -1,   641,    -1,
     643,    -1,   645,    -1,   657,    -1,   658,    -1,   660,    -1,
     661,    -1,   662,    -1,   668,    -1,   669,    -1,     1,    -1,
     318,  1094,    -1,  1138,   164,   638,    -1,    -1,    27,   232,
      -1,  1138,   184,    -1,   293,    -1,   642,    -1,   426,  1138,
     642,    -1,    37,    -1,    73,    -1,    75,    -1,    76,    -1,
      77,    -1,    78,    -1,    79,    -1,    80,    -1,   115,    -1,
     197,    -1,   286,    -1,   295,    -1,   308,    -1,   366,    -1,
     364,    -1,   365,    -1,   415,    -1,   413,    -1,   414,    -1,
      39,   363,    -1,    39,   412,    -1,    39,    -1,    42,   363,
      -1,    42,   412,    -1,    42,    -1,    41,   363,    -1,    41,
     412,    -1,    41,    -1,    40,   363,    -1,    40,   412,    -1,
      40,    -1,    38,   363,    -1,    38,   412,    -1,    38,    -1,
     249,    -1,  1154,   219,  1117,    -1,  1154,   405,  1117,    -1,
      -1,   649,   653,    -1,   654,   648,    -1,   271,  1098,   646,
    1160,   647,   644,    -1,    -1,   398,  1098,    -1,    -1,   111,
    1146,  1076,    -1,    -1,   649,    -1,   651,    -1,   652,  1140,
    1138,  1075,    -1,   650,    -1,   651,   650,    -1,    28,    -1,
     112,    -1,    -1,   654,    -1,   198,  1129,   655,    -1,   656,
      -1,   655,   656,    -1,   436,    -1,   213,  1151,    -1,   388,
     659,    -1,    -1,   220,    -1,   341,    -1,    43,  1162,   442,
      -1,    34,    -1,   429,  1138,  1099,    -1,    -1,   429,  1139,
     665,   664,  1162,  1152,  1161,   667,    -1,   666,    -1,   665,
     666,    -1,  1099,    -1,  1099,   395,  1099,    -1,    -1,   399,
    1138,  1099,    -1,   325,  1095,    -1,   325,  1095,   395,  1095,
      -1,    21,   221,    -1,    -1,    -1,   235,   351,   449,   671,
     619,    -1,    -1,    -1,   231,   351,   449,   673,   619,    -1,
      -1,    -1,   327,   351,   449,   675,   676,    -1,    -1,   677,
      -1,   678,    -1,   677,   678,    -1,   312,   714,   679,   449,
     693,    -1,    -1,   679,   680,    -1,  1138,   184,    -1,    60,
    1138,  1090,    -1,   681,    -1,   685,    -1,    87,   682,    -1,
      88,   682,    -1,   683,   684,    -1,    -1,   169,    -1,  1093,
      -1,   684,  1093,    -1,   288,  1139,   691,   686,   687,   688,
     689,   690,    -1,    -1,   189,  1138,  1098,    -1,    -1,   170,
     113,  1138,  1098,    -1,    -1,   216,    90,  1138,  1098,    -1,
      -1,   217,  1138,  1098,    -1,    -1,   171,  1138,  1098,    -1,
    1098,    -1,  1098,   692,  1098,    66,    -1,  1098,   692,    -1,
     229,    -1,   230,    -1,    -1,   693,   694,    -1,   626,   629,
     695,   449,    -1,    -1,   695,   696,    -1,   697,    -1,   699,
      -1,   706,    -1,   640,    -1,   641,    -1,   643,    -1,   657,
      -1,   700,    -1,   660,    -1,   711,    -1,   701,    -1,   662,
      -1,   704,    -1,   712,    -1,   645,    -1,   705,    -1,   408,
    1138,   698,    -1,   331,    -1,   290,    -1,    90,    -1,   113,
      -1,    89,    -1,   289,    -1,   330,    -1,   254,   188,  1138,
    1098,    -1,    65,  1144,  1138,  1098,    -1,    65,   266,    -1,
      66,    -1,   702,    -1,   701,   702,    -1,   385,  1145,   703,
      -1,  1076,    -1,   298,   432,  1048,    -1,   430,  1093,   176,
    1084,    49,  1084,    -1,   707,   708,    -1,   229,   710,  1139,
      -1,   230,  1124,    -1,   709,    -1,   708,   709,    -1,   294,
    1098,    -1,  1098,    -1,   254,   288,    -1,    -1,   265,    -1,
     266,    -1,   371,  1138,  1093,  1116,    -1,   188,   713,    -1,
      -1,   199,    -1,   436,    -1,    -1,    -1,    -1,   346,   351,
     449,   716,   717,   718,    -1,    -1,   719,    -1,   720,    -1,
     719,   720,    -1,   633,    -1,    -1,   626,   629,   721,   722,
     449,    -1,    -1,   722,   723,    -1,    44,    -1,    45,    -1,
      36,    -1,    46,    -1,   155,   150,    -1,   155,   152,    -1,
     190,    -1,   238,    -1,   338,    -1,   409,    -1,   285,    -1,
      31,    -1,   352,    -1,   333,    -1,   177,    -1,   309,    -1,
     229,  1144,  1138,   724,  1092,    -1,    65,  1144,  1138,   725,
    1092,    -1,   173,  1138,  1092,    -1,    33,  1138,  1092,    -1,
     641,    -1,   660,    -1,   657,    -1,   643,    -1,   662,    -1,
     640,    -1,   726,    -1,   428,  1093,    -1,   176,  1091,    -1,
     398,  1093,    -1,    -1,   294,    -1,   443,    -1,   243,    -1,
     444,    -1,    -1,   294,    -1,   443,    -1,   243,    -1,   444,
      -1,   271,  1098,  1160,    -1,    -1,    -1,    -1,   302,   117,
     730,   738,   449,   728,   739,   729,   741,    -1,    -1,    -1,
     428,   731,   733,    -1,    -1,    54,   732,   733,    -1,   734,
      -1,   733,   734,    -1,   735,   736,   737,   436,    -1,    -1,
    1129,   320,    -1,  1129,   429,    -1,    -1,   367,  1138,    31,
      -1,   367,  1138,   107,    -1,   412,   367,  1138,  1098,    -1,
     367,  1138,  1098,    -1,    -1,   278,    -1,    -1,   336,   436,
      -1,    -1,    -1,   106,   449,   740,   741,   123,   106,   449,
      -1,    -1,   741,   742,    -1,   743,    -1,   744,    -1,   745,
      -1,   751,   449,    -1,     1,    -1,   746,   351,   747,   449,
      -1,   436,   449,    -1,   746,    -1,   436,    -1,    -1,   232,
      -1,    -1,    -1,   749,   750,   751,    -1,    -1,   751,   752,
      -1,   753,    -1,   763,    -1,   768,    -1,   772,    -1,   775,
      -1,   788,    -1,   791,    -1,   801,    -1,   796,    -1,   802,
      -1,   803,    -1,   806,    -1,   808,    -1,   815,    -1,   819,
      -1,   821,    -1,   836,    -1,   839,    -1,   841,    -1,   843,
      -1,   846,    -1,   848,    -1,   854,    -1,   863,    -1,   865,
      -1,   882,    -1,   884,    -1,   887,    -1,   891,    -1,   897,
      -1,   907,    -1,   914,    -1,   916,    -1,   919,    -1,   923,
      -1,   924,    -1,   935,    -1,   946,    -1,   956,    -1,   962,
      -1,   965,    -1,   971,    -1,   975,    -1,   977,    -1,   979,
      -1,   981,    -1,   984,    -1,   995,    -1,  1008,    -1,   255,
      -1,    -1,     3,   754,   755,   762,    -1,  1093,   756,   759,
    1015,    -1,  1093,   176,   157,   214,    -1,  1093,   176,   230,
      -1,  1093,   176,    66,    -1,  1093,   176,   100,    -1,  1093,
     176,   100,   441,    -1,  1093,   176,   101,    -1,  1093,   176,
     101,   440,    -1,  1093,   176,   102,    -1,  1093,   176,   396,
      -1,  1093,   176,    68,    -1,  1093,   176,   149,  1015,    -1,
    1093,   176,   147,  1088,  1015,    -1,  1093,   176,    25,    -1,
    1093,   176,    26,  1015,    -1,  1093,   176,  1070,    -1,  1093,
     176,   436,    -1,    -1,  1127,   757,   758,    -1,  1127,   758,
     757,    -1,  1127,   757,    -1,  1127,   758,    -1,    30,  1088,
      -1,   229,  1144,  1090,    -1,    65,  1144,  1090,    -1,   296,
    1144,  1090,    -1,    -1,   435,   760,    -1,   761,    -1,   760,
     761,    -1,    36,    -1,    46,    -1,   190,    -1,   238,    -1,
     338,    -1,   409,    -1,   285,    -1,   173,  1138,  1092,    -1,
      33,  1138,  1092,    -1,   348,   418,  1047,    -1,   348,   118,
    1047,    -1,    31,    -1,   177,    -1,   333,    -1,   352,    -1,
     419,    -1,   309,    -1,    -1,   124,    -1,    -1,     5,   764,
     765,   767,    -1,  1083,   398,  1063,  1021,    -1,  1083,   766,
     183,  1063,  1021,    -1,    92,  1093,   398,  1093,  1116,  1021,
      -1,    -1,   398,  1084,    -1,    -1,   125,    -1,    -1,    10,
     769,   770,    -1,   436,  1112,   771,    -1,  1049,    56,  1112,
     336,  1082,    -1,    -1,   336,  1082,    -1,    18,   773,    -1,
      -1,   773,  1072,   398,   774,  1072,    -1,    -1,   304,   398,
      -1,    -1,    51,   776,  1091,   777,   782,   783,   785,   787,
      -1,    -1,    -1,   428,   778,   779,    -1,   780,    -1,   779,
     780,    -1,   781,   274,    -1,   781,   736,  1084,    -1,    -1,
    1129,   320,    -1,  1129,    85,    -1,  1129,   429,    -1,    -1,
     336,  1093,    -1,   183,  1093,    -1,    -1,    -1,  1002,   784,
     748,    -1,    -1,    -1,  1003,   786,   748,    -1,    -1,   126,
      -1,    -1,    52,   789,   790,    -1,    -1,   790,  1090,    -1,
      -1,    59,   792,   793,    -1,    -1,   793,  1068,   794,    -1,
      -1,   795,    -1,   795,  1135,   324,    -1,  1163,   256,   339,
      -1,  1163,   236,    -1,   319,    -1,   410,    -1,    -1,    74,
     797,   798,   799,    -1,  1063,   800,  1049,  1021,    -1,    -1,
     127,    -1,   450,    -1,   153,    -1,    70,    -1,    86,    -1,
      -1,   108,   804,  1068,  1150,  1041,   805,    -1,    -1,   128,
      -1,    -1,   108,   807,   400,  1067,    -1,    -1,   115,   809,
     810,   814,    -1,  1090,   423,  1016,    -1,  1090,   424,  1016,
      -1,  1090,   421,  1016,    -1,  1090,   422,  1016,    -1,  1083,
     756,   811,  1016,    -1,  1083,   756,   420,  1070,   811,  1016,
      -1,  1083,   756,   420,   436,   811,  1016,    -1,  1083,   756,
     420,   300,   811,  1016,    -1,  1083,   756,   420,    94,   811,
    1016,    -1,    -1,  1163,   264,    -1,   435,   812,    -1,   813,
      -1,   812,   813,    -1,    36,    -1,    46,    -1,   155,   150,
      -1,   155,   152,    -1,   190,    -1,   238,    -1,   338,    -1,
     409,    -1,   285,    -1,   173,  1138,  1092,    -1,    33,  1138,
    1092,    -1,   348,   418,  1047,    -1,   348,   118,  1047,    -1,
      44,    -1,    45,    -1,    -1,   129,    -1,    -1,   116,   816,
     817,   818,    -1,  1084,   206,  1063,  1021,    -1,  1084,   206,
    1084,   183,  1063,  1021,    -1,  1084,    49,  1084,   183,  1063,
    1021,    -1,  1084,   206,  1084,   183,  1064,   323,  1064,  1021,
      -1,  1084,    49,  1084,   183,  1064,   323,  1064,  1021,    -1,
      -1,   130,    -1,    -1,   146,   820,   232,   777,    -1,    -1,
     158,   822,   823,   825,   835,    -1,   824,    -1,   823,  1123,
     824,    -1,  1049,    -1,   403,    -1,   399,    -1,   826,   829,
      -1,   827,    -1,   826,   827,    -1,    -1,   831,   828,   748,
      -1,    -1,    -1,   434,   830,   748,    -1,   432,   832,    -1,
     831,   432,   832,    -1,   833,    -1,   832,  1123,   833,    -1,
    1050,   834,    -1,    21,    -1,   403,    -1,   399,    -1,    -1,
     395,  1049,    -1,    -1,   131,    -1,    -1,   162,   837,   838,
      -1,    -1,   305,    -1,   292,    -1,   292,    98,    -1,   351,
      -1,   291,    -1,    -1,   175,   840,  1081,    -1,    -1,   182,
     842,  1093,    -1,    -1,   185,  1161,   844,  1071,   845,    -1,
      -1,   111,  1146,  1093,    -1,    -1,   186,   847,    -1,    -1,
      -1,   193,   849,  1048,  1159,   850,   748,   851,   853,    -1,
     193,     1,   133,    -1,    -1,    -1,   122,   852,   748,    -1,
      -1,   133,    -1,    -1,   200,   855,  1081,   856,   857,   858,
     862,    -1,    -1,  1163,   168,    -1,    -1,     9,  1161,   429,
      -1,   861,  1161,   429,    -1,    -1,   326,   859,    -1,   860,
      -1,   859,   860,    -1,   861,  1133,    49,  1084,    -1,    12,
      -1,    15,    -1,   267,    -1,    16,    -1,   268,    -1,   249,
      -1,   250,    -1,    -1,   107,    -1,    -1,   202,   864,   684,
      -1,    -1,   205,   866,   867,   868,    -1,  1093,    -1,  1099,
      -1,  1102,    -1,   869,    -1,   868,   869,    -1,   870,    -1,
     874,    -1,   879,    -1,    -1,   389,   871,   872,    -1,   873,
      -1,   872,   873,    -1,  1088,   172,    -1,    56,   880,    -1,
       9,    -1,   219,    -1,   405,    -1,  1088,   880,    -1,   326,
     875,    -1,   876,    -1,   875,   876,    -1,    56,    49,  1088,
     880,    -1,   877,   878,    -1,    -1,     9,    -1,   219,    -1,
     170,    -1,   405,    -1,  1088,    49,  1089,   880,    -1,    91,
    1088,   398,  1089,   880,    -1,    -1,   880,  1012,   881,  1084,
      -1,    -1,   401,    -1,    -1,   242,   883,   948,    -1,    -1,
     246,   885,   886,    -1,  1084,   398,  1081,    -1,    92,  1084,
     398,  1081,    -1,    -1,   248,   888,   889,   890,    -1,  1084,
      49,  1063,  1021,    -1,  1084,    49,  1084,   183,  1063,  1021,
      -1,    -1,   134,    -1,    -1,   277,   892,   893,    -1,    -1,
     893,   894,   895,  1067,   896,    -1,   203,    -1,   283,    -1,
     211,    -1,   163,    -1,    -1,   361,  1163,   573,    -1,    -1,
    1163,   256,   339,    -1,  1163,   236,    -1,    -1,   292,   898,
     899,    -1,   902,   903,    -1,    -1,   903,   900,   748,   901,
      -1,   903,   135,    -1,    -1,   135,    -1,  1072,    -1,  1072,
     395,  1072,    -1,    -1,   174,    -1,  1091,   397,    -1,   904,
     417,  1048,    -1,   904,   430,   905,    -1,    -1,  1163,   392,
    1012,    -1,   906,    -1,   905,     8,   906,    -1,  1093,   176,
    1084,    49,  1084,   417,  1048,    -1,    -1,   313,   908,  1068,
    1113,  1150,   909,   910,   911,   912,   913,    -1,    -1,   206,
    1093,    -1,    -1,   195,   236,    -1,  1163,   236,    -1,  1163,
     256,   236,    -1,  1163,   194,   236,    -1,  1163,   431,    -1,
      -1,   214,  1138,   684,    -1,    -1,  1031,    -1,  1042,    -1,
      -1,   137,    -1,    -1,   322,   915,  1065,  1010,    -1,    -1,
     335,   917,  1068,  1150,   909,  1031,   918,    -1,    -1,   138,
      -1,    -1,   340,   920,  1065,  1010,   921,  1041,   922,    -1,
      -1,  1163,   236,    -1,  1163,   256,   236,    -1,    -1,   139,
      -1,   342,    -1,    -1,   350,   925,   926,   934,    -1,  1066,
     928,   929,   931,    -1,    -1,     9,  1066,   929,   432,  1049,
     927,   748,    -1,    -1,   430,  1093,    -1,    -1,    -1,  1127,
     123,   930,   748,    -1,   932,    -1,   932,   931,    -1,    -1,
     432,  1048,   933,   748,    -1,    -1,   140,    -1,    -1,   360,
     936,   937,    -1,   938,    -1,   939,    -1,   940,    -1,   942,
      -1,   944,    -1,   147,  1088,   398,  1088,    -1,  1081,   398,
     146,  1087,    -1,  1081,   398,  1084,    -1,  1081,   941,    49,
    1084,    -1,   418,    -1,   118,    -1,   943,    -1,   942,   943,
      -1,  1069,   398,   514,    -1,   945,    -1,   944,   945,    -1,
    1081,   398,   403,    -1,  1081,   398,   399,    -1,    -1,   369,
     947,   948,    -1,    -1,  1095,   950,   952,   953,   949,   954,
     955,    -1,    -1,   950,  1146,   652,  1140,   951,    -1,    -1,
     951,  1095,    -1,    -1,  1120,  1147,    -1,    -1,  1121,  1138,
    1076,    -1,    -1,   428,  1067,    -1,   203,   302,  1138,   902,
      -1,    -1,   183,  1067,    -1,   283,   302,  1138,   902,    -1,
      -1,    -1,   378,   957,  1068,   958,   959,  1041,   961,    -1,
      -1,   214,  1138,   960,   684,    -1,  1114,  1054,    -1,  1114,
    1055,    -1,  1114,  1056,    -1,  1114,  1057,    -1,  1114,  1058,
      -1,    -1,   141,    -1,    -1,   380,   344,   963,   964,    -1,
     380,   232,    -1,    -1,   336,  1084,    -1,   183,  1084,    -1,
      -1,   381,   966,   967,   206,  1093,   969,  1026,   970,    -1,
     968,    -1,   967,   968,    -1,  1084,    -1,   109,  1129,   367,
      -1,   109,  1129,  1084,    -1,    -1,  1163,   295,  1093,    -1,
      -1,   142,    -1,    -1,   384,   972,   973,   974,    -1,  1083,
     176,  1063,  1021,    -1,  1083,   176,  1084,   183,  1063,  1021,
      -1,    92,  1093,   176,  1093,  1116,  1021,    -1,    -1,   143,
      -1,   386,   976,    -1,    -1,   301,    -1,    -1,   391,   978,
     684,    -1,    -1,   406,   980,  1093,   176,  1088,   398,  1089,
      -1,    -1,   411,   982,  1068,   983,    -1,    -1,   314,    -1,
     316,    -1,    -1,   416,   985,  1093,   986,   989,   969,   993,
    1026,   994,    -1,    -1,   109,  1129,   987,    -1,   988,    -1,
     987,   279,   988,    -1,  1110,  1088,    -1,   206,   990,    -1,
     989,   990,    -1,  1093,   991,   992,    -1,    -1,   110,  1137,
    1093,    -1,    -1,    93,  1137,  1093,    -1,    -1,   389,  1137,
    1093,    -1,    -1,   144,    -1,   996,    -1,  1005,    -1,  1007,
      -1,   427,   997,   999,  1000,  1001,  1004,  1146,   998,    -1,
      -1,   184,    -1,  1067,    -1,   203,    -1,   283,    -1,   211,
      -1,   163,    -1,    -1,     8,    -1,    -1,   375,    -1,   160,
      -1,   156,    -1,   160,    -1,   284,    -1,   260,    -1,   262,
      -1,    -1,   302,    -1,   427,  1135,   104,  1146,  1006,    -1,
    1072,    -1,     9,   303,    -1,   427,   997,    35,   328,  1093,
      -1,    -1,   439,  1009,  1065,  1010,   921,  1011,  1013,  1014,
      -1,    -1,   176,  1090,    -1,    -1,  1012,  1122,  1092,  1141,
      -1,  1012,  1122,  1070,    -1,  1012,  1122,   288,    -1,    35,
      -1,     8,    -1,    -1,  1036,    -1,  1042,    -1,    -1,   145,
      -1,  1017,  1019,    -1,  1017,  1019,    -1,    -1,    -1,   160,
    1018,   748,    -1,    -1,    -1,   260,  1020,   748,    -1,  1022,
    1024,    -1,    -1,    -1,   368,  1023,   748,    -1,    -1,    -1,
     263,  1025,   748,    -1,  1027,  1029,    -1,    -1,    -1,   284,
    1028,   748,    -1,    -1,    -1,   262,  1030,   748,    -1,  1032,
      -1,  1034,    -1,  1032,  1034,    -1,    -1,   123,  1033,   748,
      -1,    -1,   258,  1035,   748,    -1,  1037,    -1,  1039,    -1,
    1037,  1039,    -1,    -1,   151,  1038,   748,    -1,    -1,   259,
    1040,   748,    -1,    -1,  1042,    -1,  1043,    -1,  1045,    -1,
    1043,  1045,    -1,    -1,   209,  1044,   748,    -1,    -1,   261,
    1046,   748,    -1,    -1,  1129,  1092,  1141,    -1,  1049,    -1,
    1050,    -1,    -1,  1051,  1052,    -1,  1053,  1084,    -1,  1052,
     451,    -1,  1053,   274,    -1,  1053,   267,    -1,  1053,    12,
      -1,  1053,    13,    -1,  1053,    14,    -1,  1053,    58,    -1,
    1052,   274,    -1,  1052,   267,    -1,  1052,    12,    -1,  1052,
      13,    -1,  1052,    14,    -1,  1052,    58,    -1,  1053,   297,
      -1,  1053,   253,    -1,  1052,   297,    -1,  1052,   253,    -1,
    1052,   442,    -1,    -1,  1052,   210,    -1,  1053,   210,    -1,
    1053,   452,    -1,  1053,   443,    -1,  1053,   444,    -1,  1053,
     448,    -1,  1053,   257,    -1,  1052,   257,    -1,  1052,   443,
      -1,  1052,   444,    -1,  1052,   445,    -1,  1052,   446,    -1,
    1052,   448,    -1,  1052,  1054,    -1,  1052,  1055,    -1,  1052,
    1056,    -1,  1052,  1057,    -1,  1052,  1058,    -1,  1052,   252,
      -1,  1053,  1054,    -1,  1053,  1055,    -1,  1053,  1056,    -1,
    1053,  1057,    -1,  1053,  1058,    -1,  1053,   252,    -1,  1052,
      20,    -1,  1052,   279,    -1,   450,    -1,   153,  1161,    -1,
     154,    -1,   453,    -1,   187,  1158,    -1,   454,    -1,   222,
    1158,    -1,   181,    -1,   187,  1158,   279,   153,  1161,    -1,
     187,  1158,   153,  1161,    -1,   218,    -1,   222,  1158,   279,
     153,  1161,    -1,   222,  1158,   153,  1161,    -1,  1061,    -1,
    1059,  1060,  1061,    -1,    -1,    69,    -1,   355,    -1,  1085,
      -1,  1061,   443,  1061,    -1,  1061,   444,  1061,    -1,  1061,
     445,  1061,    -1,  1061,   446,  1061,    -1,   443,  1061,    -1,
     444,  1061,    -1,  1061,   448,  1061,    -1,   452,  1061,   451,
      -1,   228,    -1,   228,  1118,   436,    -1,  1064,    -1,  1063,
    1064,    -1,  1084,  1116,    -1,  1095,    -1,  1095,    -1,  1068,
      -1,  1067,  1068,    -1,   436,    -1,  1070,    -1,  1069,  1070,
      -1,   244,    -1,    -1,  1071,  1072,    -1,  1073,    -1,  1095,
      -1,  1074,    -1,  1074,  1118,  1074,    -1,   232,    -1,  1076,
      -1,  1075,  1076,    -1,  1095,    -1,  1095,    -1,  1077,  1095,
      -1,    -1,  1076,    -1,  1076,    -1,   232,    -1,   436,    -1,
    1082,    -1,  1081,  1082,    -1,  1093,    -1,     6,  1145,  1094,
      -1,  1084,    -1,  1083,  1084,    -1,  1093,    -1,   221,  1145,
    1094,    -1,   221,  1145,  1100,    -1,   221,  1145,  1102,    -1,
       6,  1145,  1086,  1087,    -1,     6,  1145,  1094,    -1,  1099,
      -1,  1102,    -1,  1062,    -1,  1093,    -1,   221,  1145,  1094,
      -1,   221,  1145,  1100,    -1,   221,  1145,  1102,    -1,  1100,
      -1,  1102,    -1,  1062,    -1,   305,    -1,   146,    -1,  1094,
      -1,   232,    -1,  1093,    -1,  1100,    -1,  1093,    -1,  1099,
      -1,  1093,    -1,   232,    -1,  1093,    -1,   232,    -1,  1102,
      -1,  1093,    -1,  1098,    -1,   442,    -1,  1094,    -1,  1095,
      -1,  1095,  1096,    -1,  1095,  1097,    -1,  1095,  1096,  1097,
      -1,   436,    -1,   436,  1118,  1095,    -1,   452,  1059,   451,
      -1,   452,  1061,   455,   451,    -1,   452,  1061,   455,  1061,
     451,    -1,   232,    -1,  1100,    -1,     9,  1101,    -1,  1101,
      -1,  1100,   456,  1101,    -1,   232,    -1,   373,    -1,   442,
      -1,   310,    -1,   191,    -1,   239,    -1,   402,    -1,    96,
    1103,    -1,   433,  1103,    -1,   425,   452,  1061,   451,  1103,
      -1,   237,   452,  1061,   451,  1103,    -1,   337,   452,  1061,
     451,  1103,    -1,    81,   452,  1059,   451,  1103,    -1,   382,
     452,  1059,   451,  1103,    -1,   383,   452,  1059,   451,  1103,
      -1,   407,   452,  1106,   451,  1103,    -1,   269,   452,  1107,
     451,    -1,   234,   452,  1108,   451,  1103,    -1,   180,  1104,
      -1,    -1,   452,  1061,   455,   451,    -1,   452,  1061,   455,
    1061,   451,    -1,    -1,   452,  1105,   451,    -1,    -1,  1059,
      -1,  1061,    -1,  1061,  1060,   219,    -1,  1061,  1060,   405,
      -1,  1061,    -1,  1061,  1060,  1061,    -1,  1061,    -1,  1061,
    1060,  1076,    -1,    -1,    -1,     9,    -1,    -1,  1120,    -1,
      -1,   201,    -1,    -1,   254,    -1,   299,    -1,    -1,   257,
      -1,    -1,   278,    -1,    -1,   343,    -1,    -1,   357,  1130,
      -1,   196,    -1,   272,    -1,   314,  1138,    -1,   316,  1124,
      -1,   435,   119,    -1,   119,    -1,    62,   358,    -1,   358,
      -1,    -1,     7,    -1,    -1,    17,    -1,    -1,    23,    -1,
      -1,    24,    -1,    -1,    27,    -1,    -1,    30,    -1,    -1,
      37,    -1,    -1,    49,    -1,    -1,    55,    -1,    -1,    56,
      -1,    -1,    84,    -1,    -1,    99,    -1,    -1,   400,    -1,
      -1,   172,    -1,    -1,   176,    -1,    -1,   196,    -1,    -1,
     210,    -1,    -1,   210,    -1,    23,    -1,    -1,   214,    -1,
      -1,   229,    -1,   230,    -1,    -1,   230,    -1,    -1,   245,
      -1,    -1,   265,    -1,    -1,   272,    -1,    -1,   275,    -1,
      -1,   280,    -1,   196,   280,    -1,    -1,   282,    -1,    -1,
     305,    -1,    -1,   314,    -1,    -1,   341,    -1,    -1,   360,
      -1,    -1,   362,    -1,    -1,   362,    -1,   362,   210,    -1,
      -1,   367,    -1,    -1,   379,    -1,    -1,   390,    -1,    -1,
     393,    -1,    -1,   394,    -1,    -1,   397,    -1,    -1,   398,
      -1,    -1,   432,    -1,    -1,   435,    -1
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
    2046,  2047,  2055,  2056,  2059,  2060,  2061,  2065,  2066,  2070,
    2071,  2072,  2078,  2103,  2104,  2105,  2106,  2112,  2119,  2120,
    2124,  2127,  2128,  2134,  2144,  2145,  2159,  2160,  2160,  2163,
    2162,  2175,  2176,  2180,  2192,  2201,  2205,  2206,  2216,  2215,
    2233,  2234,  2238,  2245,  2252,  2253,  2254,  2255,  2256,  2257,
    2258,  2259,  2260,  2261,  2268,  2272,  2272,  2272,  2278,  2290,
    2315,  2339,  2340,  2347,  2348,  2352,  2353,  2360,  2367,  2368,
    2375,  2379,  2388,  2389,  2395,  2405,  2423,  2424,  2428,  2429,
    2430,  2434,  2441,  2448,  2458,  2465,  2483,  2487,  2498,  2499,
    2499,  2510,  2511,  2515,  2515,  2532,  2533,  2535,  2539,  2541,
    2540,  2565,  2564,  2589,  2593,  2600,  2602,  2624,  2629,  2635,
    2644,  2652,  2653,  2661,  2662,  2663,  2667,  2687,  2691,  2700,
    2701,  2702,  2703,  2704,  2705,  2706,  2707,  2708,  2709,  2710,
    2711,  2712,  2713,  2714,  2721,  2743,  2765,  2766,  2778,  2798,
    2805,  2806,  2810,  2811,  2812,  2813,  2814,  2815,  2816,  2817,
    2818,  2819,  2820,  2821,  2826,  2831,  2832,  2833,  2834,  2835,
    2836,  2837,  2838,  2839,  2840,  2841,  2842,  2843,  2844,  2845,
    2846,  2847,  2848,  2849,  2857,  2865,  2873,  2880,  2885,  2895,
    2896,  2897,  2901,  2918,  2919,  2922,  2923,  2929,  2929,  2932,
    2956,  2972,  2973,  2977,  2978,  2981,  2981,  2984,  2991,  2992,
    2997,  3007,  3014,  3017,  3018,  3019,  3026,  3033,  3058,  3062,
    3062,  3067,  3068,  3072,  3073,  3076,  3077,  3090,  3102,  3122,
    3136,  3138,  3137,  3157,  3158,  3158,  3171,  3173,  3172,  3184,
    3185,  3189,  3190,  3199,  3206,  3209,  3213,  3217,  3218,  3219,
    3226,  3227,  3231,  3234,  3234,  3237,  3238,  3244,  3249,  3250,
    3253,  3254,  3257,  3258,  3261,  3262,  3265,  3266,  3270,  3271,
    3272,  3276,  3277,  3280,  3281,  3285,  3289,  3290,  3294,  3295,
    3296,  3297,  3298,  3299,  3300,  3301,  3302,  3303,  3304,  3305,
    3306,  3307,  3308,  3309,  3313,  3317,  3318,  3319,  3320,  3321,
    3322,  3323,  3327,  3331,  3332,  3333,  3337,  3338,  3342,  3346,
    3351,  3355,  3359,  3363,  3364,  3368,  3369,  3373,  3374,  3375,
    3378,  3378,  3378,  3381,  3385,  3388,  3388,  3391,  3398,  3399,
    3400,  3399,  3417,  3418,  3422,  3423,  3428,  3430,  3429,  3465,
    3466,  3470,  3471,  3472,  3473,  3474,  3475,  3476,  3477,  3478,
    3479,  3480,  3481,  3482,  3483,  3484,  3485,  3486,  3490,  3494,
    3498,  3502,  3503,  3504,  3505,  3506,  3507,  3508,  3509,  3516,
    3520,  3530,  3533,  3537,  3541,  3545,  3553,  3556,  3560,  3564,
    3568,  3576,  3589,  3591,  3601,  3590,  3628,  3630,  3629,  3636,
    3635,  3644,  3645,  3650,  3657,  3659,  3663,  3673,  3675,  3683,
    3691,  3720,  3751,  3753,  3763,  3768,  3779,  3780,  3780,  3807,
    3808,  3812,  3813,  3814,  3815,  3831,  3843,  3874,  3911,  3923,
    3926,  3927,  3936,  3940,  3936,  3953,  3971,  3975,  3976,  3977,
    3978,  3979,  3980,  3981,  3982,  3983,  3984,  3985,  3986,  3987,
    3988,  3989,  3990,  3991,  3992,  3993,  3994,  3995,  3996,  3997,
    3998,  3999,  4000,  4001,  4002,  4003,  4004,  4005,  4006,  4007,
    4008,  4009,  4010,  4011,  4012,  4013,  4014,  4015,  4016,  4017,
    4018,  4019,  4020,  4021,  4022,  4023,  4024,  4047,  4046,  4059,
    4063,  4067,  4071,  4075,  4079,  4083,  4087,  4091,  4095,  4099,
    4103,  4107,  4111,  4115,  4119,  4123,  4130,  4131,  4132,  4133,
    4134,  4135,  4139,  4143,  4144,  4147,  4148,  4152,  4153,  4157,
    4158,  4159,  4160,  4161,  4162,  4163,  4164,  4168,  4172,  4176,
    4181,  4182,  4183,  4184,  4185,  4186,  4190,  4191,  4200,  4200,
    4206,  4210,  4214,  4220,  4221,  4225,  4226,  4235,  4235,  4240,
    4244,  4251,  4252,  4261,  4267,  4268,  4272,  4272,  4280,  4280,
    4290,  4292,  4291,  4300,  4301,  4306,  4313,  4320,  4322,  4326,
    4334,  4345,  4346,  4347,  4352,  4356,  4355,  4367,  4371,  4370,
    4381,  4382,  4391,  4391,  4395,  4396,  4408,  4408,  4412,  4413,
    4424,  4425,  4426,  4427,  4428,  4431,  4431,  4439,  4439,  4445,
    4452,  4453,  4456,  4456,  4463,  4476,  4489,  4489,  4500,  4501,
    4510,  4510,  4530,  4529,  4542,  4546,  4550,  4554,  4558,  4562,
    4566,  4571,  4575,  4582,  4583,  4584,  4588,  4589,  4594,  4595,
    4596,  4597,  4598,  4599,  4600,  4601,  4602,  4603,  4607,  4611,
    4615,  4620,  4621,  4625,  4626,  4635,  4635,  4641,  4645,  4649,
    4653,  4657,  4664,  4665,  4674,  4674,  4696,  4695,  4714,  4715,
    4726,  4735,  4740,  4748,  4777,  4778,  4784,  4783,  4799,  4803,
    4802,  4817,  4818,  4823,  4824,  4835,  4864,  4865,  4866,  4869,
    4870,  4874,  4875,  4884,  4884,  4889,  4890,  4898,  4915,  4932,
    4950,  4975,  4975,  4988,  4988,  5001,  5001,  5010,  5014,  5027,
    5027,  5040,  5042,  5040,  5053,  5058,  5062,  5061,  5075,  5076,
    5085,  5085,  5093,  5094,  5098,  5099,  5100,  5104,  5105,  5110,
    5111,  5116,  5120,  5121,  5122,  5123,  5124,  5125,  5126,  5130,
    5131,  5140,  5140,  5153,  5152,  5162,  5163,  5164,  5168,  5169,
    5173,  5174,  5175,  5181,  5181,  5186,  5187,  5191,  5192,  5193,
    5194,  5195,  5196,  5202,  5206,  5207,  5211,  5216,  5220,  5221,
    5222,  5223,  5224,  5228,  5254,  5267,  5268,  5272,  5272,  5280,
    5280,  5290,  5290,  5295,  5299,  5311,  5311,  5317,  5321,  5328,
    5329,  5338,  5338,  5342,  5343,  5357,  5358,  5359,  5360,  5364,
    5365,  5369,  5370,  5371,  5383,  5383,  5388,  5393,  5392,  5402,
    5409,  5410,  5414,  5419,  5428,  5431,  5435,  5440,  5447,  5454,
    5455,  5459,  5460,  5465,  5477,  5477,  5506,  5507,  5511,  5512,
    5516,  5520,  5524,  5528,  5535,  5536,  5550,  5551,  5552,  5556,
    5557,  5566,  5566,  5581,  5581,  5592,  5593,  5602,  5602,  5619,
    5620,  5624,  5631,  5632,  5641,  5654,  5654,  5660,  5665,  5664,
    5675,  5676,  5680,  5682,  5681,  5692,  5693,  5698,  5697,  5708,
    5709,  5718,  5718,  5723,  5724,  5725,  5726,  5727,  5733,  5742,
    5746,  5755,  5762,  5763,  5769,  5770,  5774,  5783,  5784,  5788,
    5792,  5804,  5804,  5810,  5809,  5826,  5829,  5845,  5846,  5849,
    5850,  5854,  5855,  5860,  5865,  5873,  5885,  5890,  5898,  5914,
    5915,  5914,  5935,  5936,  5952,  5953,  5954,  5955,  5956,  5960,
    5961,  5970,  5970,  5975,  5982,  5983,  5984,  5993,  5993,  6002,
    6003,  6007,  6008,  6009,  6013,  6014,  6018,  6019,  6028,  6028,
    6034,  6038,  6042,  6049,  6050,  6059,  6066,  6067,  6075,  6075,
    6088,  6088,  6104,  6104,  6113,  6115,  6116,  6125,  6125,  6135,
    6136,  6141,  6142,  6147,  6154,  6155,  6160,  6167,  6168,  6172,
    6173,  6177,  6178,  6182,  6183,  6192,  6193,  6194,  6198,  6222,
    6225,  6233,  6243,  6248,  6253,  6258,  6265,  6266,  6269,  6270,
    6274,  6274,  6278,  6278,  6282,  6282,  6285,  6286,  6290,  6297,
    6298,  6302,  6314,  6314,  6331,  6332,  6337,  6340,  6344,  6348,
    6355,  6356,  6359,  6360,  6361,  6365,  6366,  6379,  6387,  6394,
    6396,  6395,  6405,  6407,  6406,  6421,  6425,  6427,  6426,  6437,
    6439,  6438,  6455,  6461,  6463,  6462,  6472,  6474,  6473,  6489,
    6494,  6499,  6509,  6508,  6520,  6519,  6535,  6540,  6545,  6555,
    6554,  6566,  6565,  6580,  6581,  6585,  6590,  6595,  6605,  6604,
    6616,  6615,  6632,  6635,  6647,  6654,  6661,  6661,  6671,  6672,
    6674,  6675,  6676,  6677,  6678,  6679,  6681,  6682,  6683,  6684,
    6685,  6686,  6688,  6689,  6691,  6692,  6693,  6696,  6698,  6699,
    6700,  6702,  6703,  6704,  6706,  6707,  6709,  6710,  6711,  6712,
    6713,  6715,  6716,  6717,  6718,  6719,  6720,  6722,  6723,  6724,
    6725,  6726,  6727,  6729,  6730,  6733,  6733,  6733,  6734,  6734,
    6735,  6735,  6736,  6736,  6736,  6737,  6737,  6737,  6742,  6743,
    6746,  6747,  6748,  6752,  6753,  6754,  6755,  6756,  6757,  6758,
    6759,  6760,  6771,  6783,  6798,  6799,  6804,  6810,  6832,  6852,
    6856,  6872,  6886,  6887,  6892,  6898,  6899,  6904,  6913,  6914,
    6915,  6919,  6930,  6931,  6935,  6945,  6946,  6950,  6951,  6955,
    6956,  6962,  6982,  6983,  6987,  6988,  6992,  6993,  6997,  6998,
    6999,  7000,  7001,  7002,  7003,  7004,  7005,  7009,  7010,  7011,
    7012,  7013,  7014,  7015,  7019,  7020,  7024,  7025,  7029,  7030,
    7034,  7035,  7046,  7047,  7051,  7052,  7053,  7057,  7058,  7059,
    7067,  7071,  7072,  7073,  7074,  7078,  7079,  7083,  7093,  7111,
    7138,  7150,  7151,  7161,  7162,  7166,  7167,  7168,  7169,  7170,
    7171,  7172,  7180,  7184,  7188,  7192,  7196,  7200,  7204,  7208,
    7212,  7216,  7220,  7224,  7231,  7232,  7233,  7237,  7238,  7242,
    7243,  7248,  7255,  7262,  7272,  7279,  7289,  7296,  7310,  7320,
    7321,  7325,  7326,  7330,  7331,  7335,  7336,  7337,  7341,  7342,
    7346,  7347,  7351,  7352,  7356,  7357,  7364,  7364,  7365,  7365,
    7366,  7366,  7367,  7367,  7369,  7369,  7370,  7370,  7371,  7371,
    7372,  7372,  7373,  7373,  7374,  7374,  7375,  7375,  7376,  7376,
    7377,  7377,  7378,  7378,  7379,  7379,  7380,  7380,  7381,  7381,
    7382,  7382,  7383,  7383,  7384,  7384,  7385,  7385,  7386,  7386,
    7386,  7387,  7387,  7388,  7388,  7388,  7389,  7389,  7390,  7390,
    7391,  7391,  7392,  7392,  7393,  7393,  7394,  7394,  7394,  7395,
    7395,  7396,  7396,  7397,  7397,  7398,  7398,  7399,  7399,  7400,
    7400,  7401,  7401,  7401,  7402,  7402,  7403,  7403,  7404,  7404,
    7405,  7405,  7406,  7406,  7407,  7407,  7408,  7408,  7410,  7410,
    7411,  7411
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
  "_mode", "_number", "_of", "_on", "_in_order", "_other", "_program",
  "_record", "_right", "_set", "_sign", "_sign_is", "_size", "_status",
  "_tape", "_than", "_then", "_times", "_to", "_when", "_with", 0
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
     573,   573,   574,   574,   575,   575,   575,   576,   576,   577,
     577,   577,   578,   579,   579,   579,   579,   580,   581,   581,
     582,   583,   583,   584,   585,   585,   586,   587,   586,   588,
     586,   589,   589,   590,   591,   591,   592,   592,   594,   593,
     595,   595,   596,   596,   596,   596,   596,   596,   596,   596,
     596,   596,   596,   596,   597,   598,   598,   598,   599,   599,
     599,   600,   600,   601,   601,   602,   602,   603,   604,   604,
     605,   605,   606,   606,   607,   608,   609,   609,   610,   610,
     610,   611,   612,   613,   614,   615,   616,   616,   617,   618,
     617,   619,   619,   621,   620,   622,   622,   622,   623,   624,
     623,   625,   623,   626,   627,   628,   628,   629,   629,   629,
     630,   631,   631,   632,   632,   632,   633,   634,   634,   635,
     635,   635,   635,   635,   635,   635,   635,   635,   635,   635,
     635,   635,   635,   635,   636,   637,   638,   638,   639,   640,
     641,   641,   642,   642,   642,   642,   642,   642,   642,   642,
     642,   642,   642,   642,   642,   642,   642,   642,   642,   642,
     642,   642,   642,   642,   642,   642,   642,   642,   642,   642,
     642,   642,   642,   642,   642,   642,   642,   643,   643,   644,
     644,   644,   645,   646,   646,   647,   647,   648,   648,   649,
     650,   651,   651,   652,   652,   653,   653,   654,   655,   655,
     656,   657,   658,   659,   659,   659,   660,   661,   662,   664,
     663,   665,   665,   666,   666,   667,   667,   668,   668,   669,
     670,   671,   670,   672,   673,   672,   674,   675,   674,   676,
     676,   677,   677,   678,   679,   679,   680,   680,   680,   680,
     681,   681,   682,   683,   683,   684,   684,   685,   686,   686,
     687,   687,   688,   688,   689,   689,   690,   690,   691,   691,
     691,   692,   692,   693,   693,   694,   695,   695,   696,   696,
     696,   696,   696,   696,   696,   696,   696,   696,   696,   696,
     696,   696,   696,   696,   697,   698,   698,   698,   698,   698,
     698,   698,   699,   700,   700,   700,   701,   701,   702,   703,
     704,   705,   706,   707,   707,   708,   708,   709,   709,   709,
     710,   710,   710,   711,   712,   713,   713,   714,   715,   716,
     717,   715,   718,   718,   719,   719,   720,   721,   720,   722,
     722,   723,   723,   723,   723,   723,   723,   723,   723,   723,
     723,   723,   723,   723,   723,   723,   723,   723,   723,   723,
     723,   723,   723,   723,   723,   723,   723,   723,   723,   723,
     723,   724,   724,   724,   724,   724,   725,   725,   725,   725,
     725,   726,   727,   728,   729,   727,   730,   731,   730,   732,
     730,   733,   733,   734,   735,   735,   735,   736,   736,   736,
     736,   736,   737,   737,   738,   738,   739,   740,   739,   741,
     741,   742,   742,   742,   742,   742,   743,   744,   745,   746,
     747,   747,   749,   750,   748,   751,   751,   752,   752,   752,
     752,   752,   752,   752,   752,   752,   752,   752,   752,   752,
     752,   752,   752,   752,   752,   752,   752,   752,   752,   752,
     752,   752,   752,   752,   752,   752,   752,   752,   752,   752,
     752,   752,   752,   752,   752,   752,   752,   752,   752,   752,
     752,   752,   752,   752,   752,   752,   752,   754,   753,   755,
     755,   755,   755,   755,   755,   755,   755,   755,   755,   755,
     755,   755,   755,   755,   755,   755,   756,   756,   756,   756,
     756,   756,   757,   758,   758,   759,   759,   760,   760,   761,
     761,   761,   761,   761,   761,   761,   761,   761,   761,   761,
     761,   761,   761,   761,   761,   761,   762,   762,   764,   763,
     765,   765,   765,   766,   766,   767,   767,   769,   768,   770,
     770,   771,   771,   772,   773,   773,   774,   774,   776,   775,
     777,   778,   777,   779,   779,   780,   780,   781,   781,   781,
     781,   782,   782,   782,   783,   784,   783,   785,   786,   785,
     787,   787,   789,   788,   790,   790,   792,   791,   793,   793,
     794,   794,   794,   794,   794,   795,   795,   797,   796,   798,
     799,   799,   800,   800,   801,   802,   804,   803,   805,   805,
     807,   806,   809,   808,   810,   810,   810,   810,   810,   810,
     810,   810,   810,   811,   811,   811,   812,   812,   813,   813,
     813,   813,   813,   813,   813,   813,   813,   813,   813,   813,
     813,   813,   813,   814,   814,   816,   815,   817,   817,   817,
     817,   817,   818,   818,   820,   819,   822,   821,   823,   823,
     824,   824,   824,   825,   826,   826,   828,   827,   829,   830,
     829,   831,   831,   832,   832,   833,   833,   833,   833,   834,
     834,   835,   835,   837,   836,   838,   838,   838,   838,   838,
     838,   840,   839,   842,   841,   844,   843,   845,   845,   847,
     846,   849,   850,   848,   848,   851,   852,   851,   853,   853,
     855,   854,   856,   856,   857,   857,   857,   858,   858,   859,
     859,   860,   861,   861,   861,   861,   861,   861,   861,   862,
     862,   864,   863,   866,   865,   867,   867,   867,   868,   868,
     869,   869,   869,   871,   870,   872,   872,   873,   873,   873,
     873,   873,   873,   874,   875,   875,   876,   876,   877,   877,
     877,   877,   877,   878,   879,   880,   880,   881,   881,   883,
     882,   885,   884,   886,   886,   888,   887,   889,   889,   890,
     890,   892,   891,   893,   893,   894,   894,   894,   894,   895,
     895,   896,   896,   896,   898,   897,   899,   900,   899,   899,
     901,   901,   902,   902,   903,   903,   903,   903,   903,   904,
     904,   905,   905,   906,   908,   907,   909,   909,   910,   910,
     910,   910,   910,   910,   911,   911,   912,   912,   912,   913,
     913,   915,   914,   917,   916,   918,   918,   920,   919,   921,
     921,   921,   922,   922,   923,   925,   924,   926,   927,   926,
     928,   928,   929,   930,   929,   931,   931,   933,   932,   934,
     934,   936,   935,   937,   937,   937,   937,   937,   938,   939,
     939,   940,   941,   941,   942,   942,   943,   944,   944,   945,
     945,   947,   946,   949,   948,   950,   950,   951,   951,   952,
     952,   953,   953,   954,   954,   954,   955,   955,   955,   957,
     958,   956,   959,   959,   960,   960,   960,   960,   960,   961,
     961,   963,   962,   962,   964,   964,   964,   966,   965,   967,
     967,   968,   968,   968,   969,   969,   970,   970,   972,   971,
     973,   973,   973,   974,   974,   975,   976,   976,   978,   977,
     980,   979,   982,   981,   983,   983,   983,   985,   984,   986,
     986,   987,   987,   988,   989,   989,   990,   991,   991,   992,
     992,   993,   993,   994,   994,   995,   995,   995,   996,   997,
     997,   998,   998,   998,   998,   998,   999,   999,  1000,  1000,
    1001,  1001,  1002,  1002,  1003,  1003,  1004,  1004,  1005,  1006,
    1006,  1007,  1009,  1008,  1010,  1010,  1011,  1011,  1011,  1011,
    1012,  1012,  1013,  1013,  1013,  1014,  1014,  1015,  1016,  1017,
    1018,  1017,  1019,  1020,  1019,  1021,  1022,  1023,  1022,  1024,
    1025,  1024,  1026,  1027,  1028,  1027,  1029,  1030,  1029,  1031,
    1031,  1031,  1033,  1032,  1035,  1034,  1036,  1036,  1036,  1038,
    1037,  1040,  1039,  1041,  1041,  1042,  1042,  1042,  1044,  1043,
    1046,  1045,  1047,  1047,  1048,  1049,  1051,  1050,  1052,  1052,
    1052,  1052,  1052,  1052,  1052,  1052,  1052,  1052,  1052,  1052,
    1052,  1052,  1052,  1052,  1052,  1052,  1052,  1053,  1053,  1053,
    1053,  1053,  1053,  1053,  1053,  1053,  1053,  1053,  1053,  1053,
    1053,  1053,  1053,  1053,  1053,  1053,  1053,  1053,  1053,  1053,
    1053,  1053,  1053,  1053,  1053,  1054,  1054,  1054,  1055,  1055,
    1056,  1056,  1057,  1057,  1057,  1058,  1058,  1058,  1059,  1059,
    1060,  1060,  1060,  1061,  1061,  1061,  1061,  1061,  1061,  1061,
    1061,  1061,  1062,  1062,  1063,  1063,  1064,  1065,  1066,  1067,
    1067,  1068,  1069,  1069,  1070,  1071,  1071,  1072,  1073,  1073,
    1073,  1074,  1075,  1075,  1076,  1077,  1077,  1078,  1078,  1079,
    1079,  1080,  1081,  1081,  1082,  1082,  1083,  1083,  1084,  1084,
    1084,  1084,  1084,  1084,  1084,  1084,  1084,  1085,  1085,  1085,
    1085,  1085,  1085,  1085,  1086,  1086,  1087,  1087,  1088,  1088,
    1089,  1089,  1090,  1090,  1091,  1091,  1091,  1092,  1092,  1092,
    1093,  1094,  1094,  1094,  1094,  1095,  1095,  1096,  1097,  1097,
    1098,  1099,  1099,  1100,  1100,  1101,  1101,  1101,  1101,  1101,
    1101,  1101,  1102,  1102,  1102,  1102,  1102,  1102,  1102,  1102,
    1102,  1102,  1102,  1102,  1103,  1103,  1103,  1104,  1104,  1105,
    1105,  1106,  1106,  1106,  1107,  1107,  1108,  1108,  1109,  1110,
    1110,  1111,  1111,  1112,  1112,  1113,  1113,  1113,  1114,  1114,
    1115,  1115,  1116,  1116,  1117,  1117,  1118,  1118,  1119,  1119,
    1120,  1120,  1121,  1121,  1122,  1122,  1123,  1123,  1124,  1124,
    1125,  1125,  1126,  1126,  1127,  1127,  1128,  1128,  1129,  1129,
    1130,  1130,  1131,  1131,  1132,  1132,  1133,  1133,  1134,  1134,
    1135,  1135,  1136,  1136,  1137,  1137,  1138,  1138,  1139,  1139,
    1139,  1140,  1140,  1141,  1141,  1141,  1142,  1142,  1143,  1143,
    1144,  1144,  1145,  1145,  1146,  1146,  1147,  1147,  1147,  1148,
    1148,  1149,  1149,  1150,  1150,  1151,  1151,  1152,  1152,  1153,
    1153,  1154,  1154,  1154,  1155,  1155,  1156,  1156,  1157,  1157,
    1158,  1158,  1159,  1159,  1160,  1160,  1161,  1161,  1162,  1162,
    1163,  1163
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
       2,     2,     0,     3,     0,     2,     1,     1,     2,     1,
       1,     1,     5,     0,     1,     1,     1,     5,     1,     2,
       2,     0,     2,     4,     0,     9,     0,     0,     5,     0,
       3,     0,     2,     3,     2,     2,     1,     1,     0,     4,
       0,     2,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     0,     1,     1,     4,     6,
       9,     0,     3,     0,     2,     0,     2,     3,     1,     1,
       5,     5,     1,     1,     3,     5,     0,     2,     1,     1,
       1,     5,     4,     3,     4,     3,     3,     3,     0,     0,
       5,     0,     1,     0,     2,     2,     3,     2,     1,     0,
       5,     0,     4,     1,     1,     0,     1,     0,     1,     1,
       1,     0,     2,     1,     3,     3,     6,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     0,     2,     2,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     2,     2,     1,     2,     2,     1,
       2,     2,     1,     2,     2,     1,     1,     3,     3,     0,
       2,     2,     6,     0,     2,     0,     3,     0,     1,     1,
       4,     1,     2,     1,     1,     0,     1,     3,     1,     2,
       1,     2,     2,     0,     1,     1,     3,     1,     3,     0,
       8,     1,     2,     1,     3,     0,     3,     2,     4,     2,
       0,     0,     5,     0,     0,     5,     0,     0,     5,     0,
       1,     1,     2,     5,     0,     2,     2,     3,     1,     1,
       2,     2,     2,     0,     1,     1,     2,     8,     0,     3,
       0,     4,     0,     4,     0,     3,     0,     3,     1,     4,
       2,     1,     1,     0,     2,     4,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     4,     4,     2,     1,     1,     2,     3,     1,
       3,     6,     2,     3,     2,     1,     2,     2,     1,     2,
       0,     1,     1,     4,     2,     0,     1,     1,     0,     0,
       0,     6,     0,     1,     1,     2,     1,     0,     5,     0,
       2,     1,     1,     1,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     5,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       2,     0,     1,     1,     1,     1,     0,     1,     1,     1,
       1,     3,     0,     0,     0,     9,     0,     0,     3,     0,
       3,     1,     2,     4,     0,     2,     2,     0,     3,     3,
       4,     3,     0,     1,     0,     2,     0,     0,     7,     0,
       2,     1,     1,     1,     2,     1,     4,     2,     1,     1,
       0,     1,     0,     0,     3,     0,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     4,
       4,     3,     3,     3,     4,     3,     4,     3,     3,     3,
       4,     5,     3,     4,     3,     3,     0,     3,     3,     2,
       2,     2,     3,     3,     3,     0,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     0,     1,     0,     4,
       4,     5,     6,     0,     2,     0,     1,     0,     3,     3,
       5,     0,     2,     2,     0,     5,     0,     2,     0,     8,
       0,     0,     3,     1,     2,     2,     3,     0,     2,     2,
       2,     0,     2,     2,     0,     0,     3,     0,     0,     3,
       0,     1,     0,     3,     0,     2,     0,     3,     0,     3,
       0,     1,     3,     3,     2,     1,     1,     0,     4,     4,
       0,     1,     1,     1,     1,     1,     0,     6,     0,     1,
       0,     4,     0,     4,     3,     3,     3,     3,     4,     6,
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
       2,     2,     2,     2,     2,     2,     2,     0,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     1,     2,     1,     1,     2,
       1,     2,     1,     5,     4,     1,     5,     4,     1,     3,
       0,     1,     1,     1,     3,     3,     3,     3,     2,     2,
       3,     3,     1,     3,     1,     2,     2,     1,     1,     1,
       2,     1,     1,     2,     1,     0,     2,     1,     1,     1,
       3,     1,     1,     2,     1,     1,     2,     0,     1,     1,
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
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       1,     0,     1,     0,     1,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     2,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     2,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,     4,     6,     7,
      38,    38,     0,     0,     3,     5,     0,     8,    14,    28,
      27,    29,    29,     0,   264,   264,     0,     0,    24,    40,
       0,     9,    15,    30,    26,  1526,     0,   157,     0,   612,
     612,  1527,     0,     0,     0,     0,     0,     0,    39,   266,
       0,    17,     0,    25,    33,    37,    36,  1551,    35,    42,
     159,     0,   161,   276,   277,     0,   328,   269,   616,    18,
      20,    38,     0,    16,    34,  1552,    32,    41,   165,   163,
     244,     0,     0,   460,     0,   619,   617,   634,     0,    19,
      10,    11,     0,     0,     0,     0,     0,    43,    44,    45,
      47,    46,   160,     0,   242,     0,  1518,   253,   162,   246,
     247,   249,   250,   251,   267,     0,     0,   463,  1361,   270,
     331,   278,   624,   624,     0,     0,     0,   264,    23,    56,
      71,    49,    80,  1480,   166,   165,     0,   158,  1544,  1519,
    1568,   254,   255,   256,  1500,   245,   248,   271,   329,     0,
       0,   466,   275,     0,   274,   332,  1468,   280,  1509,   624,
     621,   627,     0,   624,   635,   613,    21,    12,     0,  1526,
      54,  1551,    55,  1551,    60,    62,    63,    64,     0,     0,
      70,     0,    73,  1581,    48,     0,  1580,     0,     0,  1526,
    1526,     0,     0,  1559,  1526,  1526,  1526,  1526,  1526,     0,
    1526,  1512,  1526,    79,    81,    83,    85,    86,    87,    89,
      88,    90,    91,    92,    93,    94,    95,  1481,     0,   164,
     244,  1545,     0,  1569,  1514,  1501,  1520,   268,   331,   461,
       0,     0,   558,   331,   334,     0,     0,   622,  1526,     0,
     632,   625,   626,   636,   612,  1526,     0,    57,  1551,    59,
      61,     0,  1493,  1526,     0,    77,     0,    72,    74,    52,
      50,     0,     0,  1381,   112,     0,     0,  1526,  1526,  1560,
    1526,     0,     0,     0,     0,     0,  1526,     0,  1513,     0,
      99,    82,    84,   167,   243,  1425,   263,  1372,  1374,  1515,
       0,  1521,     0,   272,   330,   331,   464,     0,     0,   265,
     273,   337,     0,   343,   344,   335,   347,   347,   338,   293,
    1514,  1526,     0,     0,  1526,  1514,  1538,  1526,  1498,     0,
     279,   281,   284,   285,   286,   287,   288,   289,   290,   291,
     292,     0,     0,  1526,   633,     0,     0,   614,    17,     0,
    1430,    69,    58,  1492,     0,    76,    75,    78,    51,    53,
    1526,   101,   102,     0,     0,     0,   153,   152,   103,   104,
     156,     0,   155,   139,  1528,   141,    96,     0,    97,   169,
    1486,  1487,     0,  1373,   257,   258,   261,   252,  1359,   462,
     331,   467,     0,   336,   348,   349,   339,     0,   349,   341,
       0,     0,  1526,  1498,     0,     0,     0,     0,     0,  1539,
    1526,     0,  1499,     0,     0,   282,   283,   628,   629,   631,
       0,   623,   637,   639,     0,     0,    68,     0,  1439,  1435,
    1440,  1438,  1436,  1441,  1437,   145,   146,   148,   154,   151,
     150,  1530,  1529,   142,     0,   111,   110,   100,   107,  1566,
     105,     0,  1426,   259,     0,   260,  1360,   465,   469,   559,
     357,   351,     0,   305,   325,  1488,  1489,   314,  1375,   309,
     308,   307,  1380,  1379,  1536,  1512,  1524,     0,   557,   326,
     327,  1526,  1526,   630,   639,     0,     0,    13,    66,    67,
      65,   117,   131,   127,   132,   114,   130,   128,   115,   116,
     129,   113,   118,   119,   121,   147,     0,   140,   143,   108,
    1567,  1526,    98,   184,  1538,     0,  1576,   227,     0,  1538,
    1526,  1510,  1531,   230,     0,   229,  1580,   214,   213,   168,
     170,   171,   172,   173,   174,   175,     0,   176,   177,   226,
     178,   179,   180,   181,   182,   183,  1526,   262,     0,   468,
     470,   471,   560,     0,  1502,     0,  1528,   342,     0,   295,
    1376,  1537,   316,     0,   298,  1525,  1564,   324,     0,     0,
       0,   645,   649,   640,   641,   642,   643,   648,     0,     0,
     120,   123,     0,   149,   144,     0,   106,  1526,  1531,  1577,
     191,   231,  1526,     0,  1511,  1526,  1507,  1526,  1532,     0,
    1526,  1526,  1500,     0,  1526,     0,   474,   472,   562,   373,
       0,   447,   382,   415,   403,   412,   409,   406,  1578,   383,
     384,   385,   386,   387,   388,   389,   390,   391,  1555,   346,
     416,     0,   392,   379,   393,   394,     0,     0,  1562,   396,
     397,   395,   443,   399,   400,   398,  1526,  1526,   340,   358,
     359,   360,   361,   362,   363,   380,   364,   365,   366,   367,
     368,   369,   370,   371,   372,     0,     0,  1503,     0,   352,
       0,   306,   297,   296,   294,   315,  1512,  1565,   303,   312,
     311,   313,   310,     0,   647,   650,   707,   758,   767,   774,
     778,   802,   806,   824,   817,   825,   826,   832,   865,   874,
     876,   903,   911,   913,  1576,   919,     0,   930,   951,   953,
     989,   991,   995,   706,  1001,  1014,  1034,  1051,  1053,  1057,
    1064,  1065,  1081,  1101,  1119,     0,  1137,  1148,  1156,  1158,
    1160,  1162,  1167,  1189,  1212,   644,   656,   657,   658,   659,
     660,   661,   662,   663,   665,   664,   666,   667,   668,   669,
     670,   671,   672,   673,   674,   675,   676,   677,   678,   679,
     680,   681,   682,   683,   684,   685,   686,   687,   688,   689,
     690,   691,   692,   693,   694,   695,   696,   697,   698,   699,
     700,   701,   702,   703,   704,  1185,  1186,  1187,   705,    22,
       0,   122,   109,     0,  1526,   193,   192,   188,     0,  1506,
     230,   225,     0,     0,   228,     0,     0,   237,  1549,  1549,
       0,   238,     0,   210,  1526,   347,   566,   561,   563,   564,
     459,   413,   414,   401,   402,   410,   411,   407,   408,   404,
     405,  1579,     0,  1556,   441,   423,   374,  1421,   457,  1563,
     444,   445,   442,     0,     0,   376,   378,  1484,  1484,     0,
    1542,  1542,   356,   353,  1431,  1433,   449,   451,   453,  1505,
     317,   318,   319,   320,     0,     0,   299,  1523,   305,     0,
       0,   651,     0,     0,     0,  1276,   773,     0,   804,   808,
       0,     0,     0,     0,     0,     0,  1276,   905,     0,     0,
     915,   920,     0,  1276,     0,     0,     0,     0,     0,     0,
    1003,  1024,     0,     0,     0,     0,     0,     0,     0,     0,
    1133,  1131,     0,     0,  1157,  1155,     0,     0,     0,     0,
    1190,  1196,     0,     0,   137,   133,   138,   136,   134,   135,
     124,   125,   199,   200,   198,   197,     0,   186,   187,     0,
     219,   218,   219,   215,   232,   233,   234,   236,  1550,   239,
     240,   241,  1377,  1526,   483,   483,  1528,   503,   475,   478,
     479,     0,   567,   565,   446,     0,  1574,     0,  1422,  1423,
       0,   381,   448,     0,   375,  1510,   417,   418,  1432,  1543,
       0,     0,     0,  1578,   452,     0,     0,     0,  1504,  1512,
     304,   638,   646,   756,   726,  1420,  1542,     0,     0,  1454,
    1457,  1542,  1352,     0,     0,     0,     0,     0,     0,     0,
       0,  1454,   765,  1396,   763,  1386,  1388,  1394,  1395,  1473,
     768,     0,  1275,  1297,  1371,     0,  1367,  1369,  1368,  1415,
     780,  1414,  1416,   803,   807,   820,     0,  1354,  1482,  1553,
       0,  1435,   863,   726,     0,  1388,   872,     0,   780,   882,
     881,  1496,   878,   880,   910,   907,   906,   909,   904,  1542,
     912,  1382,  1384,   914,  1365,   924,  1572,  1274,   932,   952,
     485,     0,   955,   956,   957,   990,  1105,     0,   992,     0,
     999,     0,  1002,  1025,  1371,  1015,  1024,  1017,     0,  1022,
       0,  1368,     0,  1475,  1214,  1357,  1553,  1214,     0,  1079,
    1070,  1358,     0,  1364,  1082,  1083,  1084,  1085,  1086,  1094,
    1087,  1097,     0,  1362,     0,  1102,  1120,  1134,  1508,     0,
    1139,  1141,     0,  1153,     0,  1159,     0,  1164,  1169,  1197,
       0,  1198,  1544,  1214,     0,  1471,   195,   194,   185,   196,
       0,   217,   216,  1526,   209,   203,  1378,   211,     0,   484,
     480,     0,   481,     0,   473,   476,   569,   424,  1575,   425,
    1542,     0,     0,     0,  1340,  1338,  1403,  1343,  1397,  1401,
    1402,     0,  1424,   458,   377,  1485,   355,   354,  1434,  1557,
     454,   323,  1536,     0,   301,   757,   708,  1505,     0,   735,
       0,     0,     0,     0,     0,  1442,  1459,  1453,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1443,   766,
     759,     0,     0,  1387,  1474,   771,  1473,  1277,     0,   776,
       0,   781,   791,  1413,   805,  1412,   810,   821,   818,   823,
     822,  1276,  1355,  1483,  1356,  1554,  1263,   831,   864,   833,
     843,  1229,  1229,  1229,  1229,   873,   866,     0,     0,   875,
    1497,  1276,   901,   888,   884,   886,  1276,   908,     0,  1383,
     917,  1573,   922,   934,     0,   486,     0,   978,   963,   954,
     958,   960,   961,   962,  1109,     0,     0,  1000,   996,     0,
    1008,  1005,  1007,  1006,  1009,  1016,  1019,   652,  1276,     0,
       0,  1026,     0,  1476,  1477,  1553,     0,  1052,  1036,  1059,
    1072,  1080,  1066,     0,  1072,     0,  1408,  1409,  1095,  1098,
       0,     0,  1363,  1093,     0,  1092,     0,  1122,     0,     0,
    1132,     0,     0,  1140,     0,  1154,  1149,     0,     0,  1165,
    1166,  1163,  1508,     0,     0,  1199,     0,     0,  1059,   126,
    1491,     0,   203,   201,  1472,     0,   222,   208,   235,     0,
     477,   482,   488,   498,   347,   504,  1561,  1544,   419,     0,
    1348,  1349,     0,  1341,  1342,  1427,     0,     0,     0,     0,
       0,     0,     0,     0,  1558,  1576,   322,  1536,  1544,   300,
     731,   722,  1229,   712,   719,   713,   715,   717,     0,  1229,
       0,   711,   718,   725,   724,     0,  1229,  1540,  1540,  1540,
     729,   730,  1405,  1404,     0,  1393,  1340,  1338,     0,     0,
    1340,     0,  1389,  1390,  1391,  1353,  1340,     0,     0,  1340,
       0,     0,  1340,  1340,  1340,     0,     0,  1236,  1482,     0,
       0,   769,     0,  1288,  1289,  1290,  1323,  1291,  1576,  1327,
    1332,  1570,  1298,  1335,  1570,  1316,  1295,  1305,  1287,  1286,
    1324,  1294,  1296,  1306,  1307,  1308,  1309,  1310,  1325,  1279,
    1328,  1330,  1311,  1312,  1313,  1314,  1315,  1282,  1283,  1284,
    1285,  1299,  1322,  1293,  1304,  1281,  1280,  1292,  1301,  1302,
    1303,  1300,  1317,  1318,  1319,  1320,  1321,  1278,     0,     0,
    1370,   787,     0,     0,   794,   815,   816,   809,   811,     0,
    1236,  1268,  1270,   828,  1264,  1265,  1266,     0,  1581,  1229,
       0,  1230,   836,  1232,   837,   834,   835,     0,  1236,  1482,
     896,   898,   897,   891,   893,   899,   902,   877,   889,   885,
     883,  1276,   652,   879,  1385,  1544,   916,  1366,   652,  1576,
     942,   943,   945,   947,   948,   944,   946,   937,  1576,   933,
       0,   979,     0,   981,   980,   982,   973,   974,     0,     0,
     959,  1111,  1546,     0,     0,   993,  1236,  1482,  1580,     0,
    1020,   653,  1027,  1028,  1031,     0,  1023,  1221,  1220,  1030,
    1036,  1215,     0,     0,  1263,     0,     0,     0,  1071,     0,
       0,     0,  1096,     0,  1100,  1099,  1090,     0,  1526,  1263,
    1136,  1135,  1142,  1143,  1144,     0,  1236,  1482,     0,  1469,
       0,  1144,  1211,  1201,  1200,  1206,     0,  1208,  1209,  1216,
    1490,  1471,     0,   205,   206,   204,  1526,   490,   501,   502,
     500,   506,   582,  1526,   573,   571,   572,   574,  1540,     0,
    1526,     0,   585,   577,  1540,   578,     0,   581,   586,   584,
     579,   583,     0,   580,     0,   568,   596,   591,   594,   593,
     592,   595,   570,   597,     0,   433,   434,  1508,   422,   435,
     431,   429,  1531,   427,  1398,  1399,  1400,  1351,  1339,  1344,
    1345,  1346,  1347,  1350,  1428,     0,   455,   321,     0,   723,
    1232,   714,   716,  1229,   720,   710,   750,  1526,   739,   740,
    1526,   751,   741,   742,   745,   755,   752,   743,     0,   753,
     744,   754,   736,   737,   709,  1541,     0,     0,     0,   727,
     728,  1407,  1392,  1406,  1454,  1482,     0,  1458,     0,  1454,
    1454,     0,  1451,  1454,  1454,  1454,     0,  1454,  1454,  1237,
     760,  1239,  1236,   772,     0,  1326,  1571,  1329,  1331,   777,
     775,   782,   783,   627,     0,   793,   792,  1202,  1203,   797,
     795,     0,   814,     0,   819,   652,   652,   829,   827,  1267,
     843,   843,   843,   843,  1526,   848,   861,   862,   849,     0,
    1526,   852,   853,   856,   854,     0,   855,   845,   846,   838,
     844,   652,  1233,  1228,     0,   867,     0,  1276,  1276,   895,
     652,   892,   887,     0,   925,     0,     0,   949,     0,     0,
       0,   975,   977,     0,   969,   985,   970,   971,   964,   965,
     985,  1103,  1526,     0,  1547,  1110,  1531,   994,   997,     0,
       0,  1011,  1021,  1018,   655,     0,     0,  1038,  1037,  1252,
    1254,  1055,  1249,  1250,  1062,  1060,     0,  1276,  1073,  1276,
    1067,  1075,  1088,  1089,  1091,  1478,  1129,  1243,     0,  1482,
    1150,     0,     0,  1470,  1170,  1171,     0,  1174,  1177,  1181,
    1175,  1207,  1544,  1210,  1222,  1494,   202,     0,   223,   224,
     220,     0,     0,   492,     0,  1561,     0,  1526,   575,   576,
       0,   599,  1526,  1574,   600,   598,   426,     0,   420,   436,
     432,  1526,   421,   428,  1429,  1526,   450,   302,  1227,   721,
       0,     0,  1272,  1272,   738,   733,   732,   734,  1447,  1236,
    1455,     0,  1467,  1452,  1445,  1465,  1446,  1448,  1449,  1462,
    1463,  1450,  1444,   652,  1240,  1235,   761,   770,  1576,     0,
    1576,     0,   784,   785,     0,   789,   788,   790,  1204,  1205,
     800,   798,   652,   812,   813,  1269,  1271,  1229,  1229,  1229,
    1229,     0,   850,   851,     0,  1272,  1272,   847,  1231,   652,
    1236,  1354,  1236,  1354,   894,   900,   890,   918,   926,   928,
     935,   938,   939,  1516,   950,   931,   936,   985,  1410,  1411,
     985,     0,   968,   966,   967,   972,  1113,     0,  1548,  1107,
    1236,  1010,  1004,     0,   654,  1032,     0,     0,  1044,     0,
     652,   652,  1056,  1054,  1251,  1063,  1058,  1061,  1068,   652,
    1077,  1076,  1479,     0,     0,  1130,  1121,  1244,  1146,  1246,
       0,  1236,  1236,  1161,  1469,  1173,  1524,  1179,  1524,  1243,
       0,  1259,  1261,  1225,  1223,  1256,  1257,  1224,  1495,     0,
     221,   489,  1526,     0,   494,   499,  1540,   535,   555,   550,
    1498,     0,     0,  1526,  1542,  1526,     0,   505,   511,   512,
     513,   522,   514,   516,   519,   507,   508,   509,   515,   518,
     536,   520,   523,   510,     0,   517,   521,  1419,   590,  1417,
    1418,   606,   589,   601,   611,   440,   437,   438,     0,     0,
     747,   746,   749,     0,   748,   762,  1456,  1238,   652,  1334,
    1576,  1337,  1576,   786,   801,   779,   652,   796,   842,   841,
     840,   839,   858,   857,   860,   859,  1234,   869,     0,   868,
       0,   652,   929,   923,   940,  1517,     0,   984,   976,   985,
     987,     0,     0,  1116,  1112,  1106,   998,  1013,     0,     0,
    1039,  1526,  1046,     0,  1040,     0,  1043,  1253,  1255,   652,
    1074,   652,  1123,  1124,  1125,  1126,  1127,  1128,   652,  1147,
    1138,  1247,  1242,  1145,  1152,  1151,  1172,     0,  1524,  1176,
       0,  1183,  1195,  1192,  1194,  1193,  1188,  1191,   652,   652,
    1226,  1213,  1258,  1219,  1218,  1533,     0,  1526,  1526,   496,
     534,  1526,   556,   554,   551,   552,  1528,   544,  1526,  1276,
       0,     0,     0,     0,   537,     0,     0,   542,   545,   548,
     609,   607,   608,   610,     0,   604,   602,   603,   605,     0,
     439,   430,   456,  1533,  1241,  1333,  1336,   799,  1236,  1236,
     927,     0,   983,   988,     0,  1526,  1114,     0,     0,  1104,
    1108,  1012,     0,     0,  1049,  1047,  1048,  1042,  1041,  1069,
    1078,  1245,   652,  1178,     0,  1182,  1184,  1168,  1260,  1262,
    1534,  1535,  1217,   491,     0,     0,  1526,   487,     0,   543,
       0,   540,  1482,   538,   539,   529,   527,   528,   530,   526,
     531,   525,   524,     0,   549,   547,   546,   588,   587,  1273,
     871,   870,   941,   986,     0,  1117,  1526,  1276,  1045,  1050,
    1035,  1248,  1180,   493,   495,     0,   533,   532,   553,     0,
    1115,     0,  1033,   497,     0,  1118,   541
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,     7,     8,    24,    39,    69,   127,
     244,     9,    25,    40,    70,    90,   477,    73,    71,    35,
      11,    21,    27,    42,    57,    58,    17,    37,    77,    97,
      98,   184,   185,   171,    99,   172,   173,   174,   175,   480,
     176,   177,   100,   180,   181,   182,   256,   101,   203,   204,
     205,   206,   440,   367,   502,   437,   438,   439,   207,   350,
     491,   492,   493,   780,   920,   494,   921,   208,   363,   364,
     497,   209,   425,   426,   210,   211,   212,   213,   214,   215,
     216,    48,    78,    80,   104,   102,   134,   369,   441,   520,
     521,   929,   787,  1128,   522,   925,   523,  1338,  1339,  1613,
    1135,   524,   525,   526,   527,   933,  1131,  1870,   528,   529,
     530,   531,   532,   533,   534,   535,   801,   137,   108,   109,
     110,   111,   144,   112,   374,   375,   445,   113,    31,    66,
     147,    84,   227,   152,   119,   153,   120,   157,   236,   321,
     322,   664,   323,  1369,   858,   549,   324,   461,   325,   670,
     326,   327,   665,   850,   851,   852,   853,   328,   329,   330,
      83,   228,   154,   155,   156,   234,   305,   450,   452,   306,
     307,   638,   386,   387,   544,   842,   308,   543,   639,   640,
     641,   964,   642,   643,   644,   645,   646,  1658,   647,   956,
    1348,  1892,  1659,  1660,  1661,  1662,  1888,  1663,  2086,  2087,
     648,   649,   832,   650,   651,   652,   547,   973,   846,   847,
    1896,   653,   654,   117,   295,   151,   380,   232,   448,   539,
     540,   541,   804,   948,   949,  1140,  1141,  1059,   950,  1617,
    1873,  2044,  2189,  2267,  1342,  1620,  1144,  1345,  1875,  2065,
    2066,  2282,  2067,  2068,  2069,  2070,  2273,  2071,  2072,  2073,
    2074,  2207,  2208,  2196,  2075,  2076,  2193,   469,   299,   542,
     598,   807,   808,   809,  1146,  1346,  1652,  2219,  2214,  1653,
      51,   243,   413,    87,   123,   122,   159,   160,   161,   240,
     335,   125,   337,   474,   475,   563,   564,   565,   566,   567,
     862,  1560,  1561,  1824,   568,   726,   727,   863,   983,  1179,
    1390,  1391,  1386,  1702,  1703,  1176,   728,   864,  1002,  1202,
    1200,   729,   865,  1010,  1421,   730,   866,  1479,   731,   867,
    1212,  1481,  1741,  1742,  1743,  1484,  1749,  1942,  1940,  2106,
    2105,   732,   868,  1023,   733,   869,  1024,  1487,  1488,   734,
     870,  1025,  1218,  1221,   735,   736,   737,   871,  1758,   738,
     872,   739,   873,  1032,  1499,  1777,  1778,  1229,   740,   874,
    1036,  1236,   741,   875,   742,   876,  1041,  1042,  1242,  1243,
    1244,  1522,  1520,  1790,  1245,  1513,  1514,  1789,  1517,   743,
     877,  1048,   744,   878,   745,   879,   746,  1054,  1526,   747,
     881,   748,   883,  1528,  1969,  2121,  2123,   749,   884,  1253,
    1537,  1797,  1971,  1972,  1973,  1975,   750,   885,   751,   886,
    1061,  1259,  1260,  1261,  1549,  1808,  1809,  1262,  1546,  1547,
    1548,  1802,  1263,  1982,  2234,   752,   887,   753,   888,  1068,
     754,   889,  1070,  1268,   755,   890,  1072,  1274,  1559,  1992,
     756,   891,  1075,  1277,  1823,  1076,  1077,  1078,  1563,  1564,
     757,   892,  1573,  1998,  2142,  2244,  2300,   758,   893,   759,
     894,  2003,   760,   895,  1574,  2006,   761,   762,   896,  1089,
    2149,  1294,  1576,  2009,  1840,  1841,  2151,  1292,   763,   897,
    1094,  1095,  1096,  1097,  1306,  1098,  1099,  1100,  1101,   764,
     898,  1065,  1986,  1264,  2135,  1551,  1811,  2133,  2239,   765,
     899,  1307,  1589,  2013,  2016,   766,  1107,  1310,   767,   902,
    1109,  1110,  1847,  2160,   768,   903,  1113,  1316,   769,   905,
     770,   906,   771,   907,   772,   908,  1321,   773,   909,  1323,
    1854,  1855,  1601,  1857,  2027,  2169,  2029,  2257,   774,   775,
     911,  2176,  1121,  1326,  1605,  1750,  1941,  1862,   776,  1607,
     777,   778,   913,  1287,  1864,  2130,  2033,  2181,  1679,  1502,
    1503,  1781,  1783,  1959,  1730,  1731,  1923,  1925,  2098,  2018,
    2019,  2158,  2162,  2252,  1831,  1832,  2000,  1833,  2001,  2034,
    2035,  2178,  2036,  2179,  1493,  1494,  1495,  1755,  1496,  1756,
    2092,  1056,  1057,  1012,  1013,  1207,  1208,  1452,  1453,  1454,
    1455,  1456,  1154,  1356,  1397,  1003,  1026,  1222,  1084,  1090,
     377,   378,  1102,  1103,  1250,  1079,  1016,  1017,   286,   463,
     457,  1137,   464,   264,  1050,  1051,  1004,  1028,  1157,  1394,
    1712,  1810,  1977,  1034,  1080,  2078,  1006,   985,   827,   958,
     959,  2080,  1007,   844,   845,  1008,  1185,  1187,  1401,  1415,
    1410,  1407,   235,  1856,  1333,  1205,  1285,  2014,   218,  1224,
     966,   372,   394,  1334,   253,  2039,  1787,   403,   226,   658,
    1180,   589,   162,   585,   279,   290,  2126,   140,   292,   859,
     556,    43,   434,   590,  2262,   552,   400,  1706,   970,   222,
    1815,   939,   178,  1226,   824,  1365,   270,   656,   668,   501,
     224,  1737,  1252,  1149,   580,   822,  1500
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1813
static const yytype_int16 yypact[] =
{
   -1813,   662,   501, -1813,   306,   316,   344, -1813, -1813, -1813,
     669,   669,   643,   643, -1813, -1813,   730, -1813, -1813, -1813,
   -1813,   836,   836,   370,   811,   811,   681,   496, -1813,   886,
     857, -1813, -1813, -1813, -1813,   -75,   620,   964,   541,   710,
     710, -1813,   614,    43,   678,   685,   800,   717, -1813,   362,
    1066,   901,  1083, -1813,   538, -1813, -1813,   923, -1813, -1813,
   -1813,   787, -1813, -1813, -1813,   888,   820, -1813,    26, -1813,
     515,   669,   643, -1813, -1813, -1813, -1813,   641, -1813,  1107,
     135,   815,   928,  1065,   867, -1813, -1813,   973,   643, -1813,
   -1813, -1813,   864,   869,   883,   893,   895, -1813, -1813, -1813,
   -1813, -1813,  1001,   917,  1159,  1301,   974,   709, -1813,    87,
   -1813, -1813, -1813, -1813, -1813,   930,  1030,  1151, -1813,    28,
    1068, -1813,    96,    96,   949,   935,   937,   811, -1813,   301,
    1210,   161,  1295,  1115, -1813, -1813,   945, -1813,  1120, -1813,
    1007, -1813, -1813, -1813,  1375, -1813, -1813, -1813, -1813,   952,
    1056,  1076, -1813,   867, -1813, -1813, -1813, -1813, -1813,    35,
   -1813,  -141,   512,   111, -1813, -1813, -1813, -1813,  1039,  1198,
   -1813,   385, -1813,   399, -1813, -1813, -1813, -1813,   145,   183,
   -1813,   -51, -1813, -1813, -1813,   961,   739,  1307,   977,  1198,
    1198,   977,  1038,  1057,  1198,  1198,  1198,  1198,  1198,   977,
    1198,  1365,  1198, -1813,  1055, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,   977,  1001,
     135, -1813,   986, -1813,  1343, -1813,  1257,    28,  1068, -1813,
     983,  1082,  1089,  1068,   105,  1114,   905, -1813,  1198,  1069,
    1161, -1813, -1813,  1331,   710,  1198,  1208, -1813,   407, -1813,
   -1813,  1087, -1813,  1198,  1234, -1813,   670, -1813, -1813, -1813,
   -1813,   997,  1202, -1813, -1813,   977,   977,  1198,  1198, -1813,
    1198,   986,  1386,   977,   977,   986,  1198,   986, -1813,   977,
       2, -1813, -1813, -1813, -1813,    12,   986, -1813, -1813, -1813,
     867, -1813,   867, -1813, -1813,  1068, -1813,  1008,  1105, -1813,
   -1813, -1813,  1114, -1813, -1813, -1813,   -15,   179, -1813, -1813,
    1343,  1198,   792,   792,  1198,    13,  1214,  1198,  1437,  1189,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813,   898,   594,  1198, -1813,  1027,  1015, -1813,   901,  1208,
   -1813, -1813, -1813, -1813,   986, -1813, -1813, -1813, -1813, -1813,
    1198, -1813, -1813,   431,   986,  1233, -1813, -1813, -1813, -1813,
   -1813,   986, -1813, -1813,    68, -1813, -1813,   780, -1813, -1813,
   -1813, -1813,   986, -1813,   867, -1813,  1171,   867, -1813, -1813,
    1068, -1813,  1019, -1813, -1813,  1387, -1813,  1389, -1813, -1813,
    1208,  1042,  1198,  1437,   986,   409,   -70,  1208,  1050, -1813,
    1198,  1045, -1813,  1045,   -12, -1813, -1813, -1813, -1813, -1813,
    1208, -1813, -1813, -1813,   519,    50, -1813,   984, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813,   431, -1813,  1090, -1813, -1813,
   -1813, -1813, -1813, -1813,  1208, -1813, -1813,   780, -1813,  1109,
   -1813,   956, -1813, -1813,  1208, -1813, -1813, -1813,  1174, -1813,
   -1813,    54,  1060,  1092, -1813, -1813, -1813,   986, -1813, -1813,
   -1813, -1813, -1813, -1813,  1262,    48,  1298,  1063, -1813, -1813,
   -1813,  1198,  1198, -1813, -1813,  2739,   643, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813,   697, -1813,   114, -1813,   431,  1208, -1813, -1813,
   -1813,  1198,   780, -1813,  1214,  1182,  1108, -1813,  1146,  1214,
    1198,  1452,   153,   429,  1208, -1813,  1088, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813,  1138, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813,  1198, -1813,  1045, -1813,
    1174, -1813, -1813,  2477,  1491,  1336,   586, -1813,  1208,   125,
   -1813, -1813, -1813,  1208, -1813, -1813,  1162, -1813,   -46,   -46,
    2947, -1813,  1077, -1813, -1813, -1813, -1813,  1179,  3582,  1084,
   -1813, -1813,   697, -1813, -1813,   977, -1813,  1198,  1318, -1813,
     134, -1813,  1198,   863, -1813,  1198, -1813,  1198, -1813,  1175,
    1198,  1198,  1375,   225,  1198,  1102, -1813, -1813,  1317, -1813,
    1321, -1813, -1813,  -112,   457,   653,   673,   688,  1113, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,  1205, -1813,
   -1813,  1208, -1813, -1813, -1813, -1813,   986,   986,  1339, -1813,
   -1813, -1813,   366, -1813, -1813, -1813,  1198,  1198, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813,   926,   -14, -1813,   699, -1813,
     785, -1813, -1813, -1813, -1813,    57,  1365, -1813,   770, -1813,
   -1813, -1813, -1813,  1444, -1813,  1319, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813,  1153, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813,  1108, -1813,  1919, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813,   442, -1813, -1813,  1253, -1813,
   -1813, -1813, -1813,   854, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
     931, -1813, -1813,    91,  1198, -1813, -1813,   500,   226,  1518,
   -1813, -1813,   -70,  1181, -1813,   986,   986, -1813,  1277,  1277,
    1284, -1813,   986, -1813,   200,   -15, -1813, -1813,  1317, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813,  1121, -1813, -1813,  1168, -1813,  1116,  1172, -1813,
   -1813, -1813, -1813,  4952,   785,  1542, -1813,  1213,  1213,   431,
    1300,  1300, -1813, -1813,  1117, -1813,   785, -1813,  1183, -1813,
   -1813, -1813, -1813, -1813,    66,  1403, -1813, -1813,  1092,  1208,
    1130, -1813,  1131,   986,  2043,  1145,    -7,  1799, -1813, -1813,
    4472,   867,  1184,  4511,  4472,  1350,   794,   904,    65,   986,
   -1813, -1813,  1455, -1813,    65,   986,  4364,   986,  3873,  4472,
   -1813,  2879,   867,   986,   867,   986,    58,    72,   986,   867,
   -1813, -1813,  4057,  4090, -1813, -1813,   986,   986,   867,   986,
   -1813,   222,  1481,   986, -1813, -1813, -1813, -1813, -1813, -1813,
    1572, -1813, -1813, -1813, -1813, -1813,   986,   127,   133,   181,
    1155, -1813,  1155, -1813, -1813, -1813,   637, -1813, -1813, -1813,
   -1813, -1813,   986,  1198,  1424,  1424,   586, -1813, -1813, -1813,
   -1813,  1410, -1813, -1813, -1813,  1208,  1203,  5207,  1143, -1813,
     986, -1813, -1813,  1367, -1813,  1452, -1813, -1813, -1813, -1813,
     986,   986,   431,  1113, -1813,   785,   -70,   -70,  1571,  1365,
   -1813, -1813, -1813,  1483,   593, -1813,  1300,  1157,   986,  1164,
    1167,  1300,    12,  1173,  1176,  1178,  1185,  1187,  1195,  1196,
    1199,  1164,  1498, -1813,  4164, -1813, -1813, -1813, -1813,  1425,
   -1813,  1575, -1813, -1813, -1813,  1237, -1813,    12, -1813, -1813,
    1218, -1813, -1813,   332,   867,  1509,   903, -1813,  1309,  1327,
     867,   925,  1521,  2203,  1028,  1053,  1524,   665,  1218, -1813,
   -1813,    30, -1813, -1813, -1813,  1558, -1813, -1813, -1813,  1300,
      65, -1813, -1813, -1813, -1813, -1813,  1265, -1813,    47,   986,
   -1813,   255, -1813, -1813, -1813, -1813, -1813,  4472, -1813,  1264,
    1526,  1618,   831, -1813,  1272, -1813,  4549,  1535,   706,  1278,
    1279,  -179,  1282,   606,  1501, -1813,  1327,  1501,   986,  1539,
    1251, -1813,   731, -1813, -1813, -1813, -1813, -1813,  1439, -1813,
      65, -1813,    -5, -1813,    80, -1813, -1813,    14,  1635,  3574,
   -1813, -1813,   986,  1543,  4192,   986,  1511,   958,  1582, -1813,
    1364,  1320,  1120,  1501,   931,   253, -1813, -1813, -1813, -1813,
     481, -1813, -1813,  1198, -1813, -1813, -1813, -1813,   332, -1813,
   -1813,   986, -1813,  1208,  1317, -1813, -1813, -1813, -1813,  1583,
    1300,  5207,  5207,  5207,    42,   823, -1813, -1813, -1813,  1117,
   -1813,  5207, -1813, -1813, -1813, -1813, -1813, -1813, -1813,  1337,
   -1813, -1813,  1262,   -70,  1585, -1813, -1813,   731,  1475,  1266,
     124,   -33,  5207,  1302,  5207, -1813,  5207, -1813,  2224,  1267,
    5207,  5207,  5207,  5207,  5207,  5207,  5207,  5207, -1813, -1813,
   -1813,  4472,  1527, -1813, -1813,  1368,  1425,  1411,  3271,  1407,
    1480, -1813,   459, -1813, -1813, -1813,   828, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813,   768,   867, -1813, -1813,
     497,  1547,  1547,  1547,  1547, -1813, -1813,  4472,  4472, -1813,
   -1813,   108,  1586,   848, -1813,  1281,   794, -1813,   986, -1813,
      29, -1813, -1813,   790,  1550, -1813,   731,   116, -1813,   255,
   -1813, -1813, -1813, -1813,    61,  1322,    65, -1813, -1813,  4472,
   -1813, -1813, -1813, -1813,  1360, -1813, -1813, -1813, -1813,   986,
      -7, -1813,   948, -1813, -1813,  1327,   332, -1813,  1519,   -57,
     190, -1813, -1813,   986,   190,  1326, -1813,  1117, -1813, -1813,
      59,   780, -1813, -1813,  1406, -1813,  1677,  1514,  4472,  4472,
   -1813,  4351,   986, -1813,  1553, -1813, -1813,  4472,   731, -1813,
   -1813, -1813,  1635,  1529,   986, -1813,  1052,    70,   -57, -1813,
   -1813,  1613, -1813, -1813, -1813,  1458, -1813, -1813,   986,   986,
   -1813,   986,  1549,  1111,   179, -1813,  4884,  1120,   613,  2224,
    1288,  1288,   919, -1813, -1813, -1813,  5207,  5207,  5207,  5207,
    5207,  5207,  5038,   823, -1813,  1108, -1813,  1262,  1120, -1813,
   -1813, -1813,  1547, -1813, -1813,  1299,  1304, -1813,   731,  1547,
    1536, -1813, -1813, -1813, -1813,  1525,  1547,  1474,  1474,  1474,
     214,  1512, -1813, -1813,   352, -1813,    51,   808,   986,   853,
      90,  1310, -1813,  1117, -1813, -1813,   184,  1313,   932,   283,
    1315,  1160,    97,    98,   552,  1323,  1169,  4428,    18,  4472,
      65, -1813,  1416, -1813, -1813, -1813, -1813, -1813,  1108, -1813,
   -1813,  1362, -1813, -1813,  1362, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,  1355,    -7,
   -1813,    34,   986,   986,   451, -1813, -1813, -1813,   446,   855,
    1401, -1813, -1813,  1642, -1813,  1515, -1813,   137,  1905,  1547,
    1508, -1813, -1813,  1513, -1813, -1813, -1813,  1592,  4428,    21,
   -1813, -1813, -1813,  3170, -1813,  1382, -1813, -1813, -1813, -1813,
   -1813,   108, -1813, -1813, -1813,  1120, -1813, -1813, -1813,  1108,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813,  1454,  1108, -1813,
    1380, -1813,  1735, -1813, -1813, -1813,   491, -1813,   731,   723,
   -1813,   145,   698,   907,    65,    65,  4428,   494,  1088,   867,
    1650, -1813, -1813,  1778, -1813,  1611, -1813, -1813, -1813, -1813,
    1519, -1813,   986,    16,   768,   861,  1358,  1669, -1813,  1361,
     731,   830, -1813,   352, -1813, -1813, -1813,  4472,  1198,   768,
   -1813, -1813, -1813, -1813,   -50,   986,  4428,   509,  1396,  1786,
     986,   423, -1813, -1813, -1813,  1494,  1495, -1813, -1813,   948,
   -1813,   131,   -34, -1813, -1813, -1813,  1198,  1627, -1813, -1813,
    1208, -1813, -1813,  1198, -1813, -1813, -1813, -1813,  1474,  1137,
    1198,  1799, -1813, -1813,  1474, -1813,  1208, -1813, -1813, -1813,
   -1813, -1813,   986, -1813,   986, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813,   986, -1813, -1813,  1635, -1813,  1601,
   -1813,   907,  1318,   907, -1813,  1117, -1813, -1813,   808,  -202,
    -202,  1288,  1288,  1288, -1813,  1303,  1402, -1813,   986, -1813,
    1513, -1813, -1813,  1547, -1813, -1813, -1813,  1198, -1813, -1813,
    1198, -1813, -1813, -1813, -1813, -1813, -1813, -1813,     0, -1813,
   -1813, -1813,  1525, -1813, -1813, -1813,   332,   332,   332, -1813,
   -1813, -1813, -1813, -1813,  1164,  1309,  5124, -1813,   986,  1164,
    1164,  5207, -1813,  1164,  1164,  1164,   412,  1164,  1164, -1813,
   -1813,  1537,  4428, -1813,    65, -1813, -1813,    41,   629, -1813,
   -1813,  3811, -1813,   391,    38, -1813, -1813, -1813, -1813,  1064,
   -1813,  1478, -1813,  1464, -1813, -1813, -1813, -1813, -1813, -1813,
     -62,   -62,   -62,   -62,  1198, -1813, -1813, -1813, -1813,  1177,
    1198, -1813, -1813, -1813, -1813,    24, -1813,  1905, -1813, -1813,
   -1813, -1813, -1813, -1813,  4472, -1813,  4472,   108, -1813, -1813,
   -1813,  3170, -1813,   986,  1684,  1388,   738,  1704,  1390,   789,
     731, -1813, -1813,  1766, -1813, -1813, -1813, -1813,   723, -1813,
    1646, -1813,  1198,  1548, -1813, -1813,  1318,    65, -1813,  4472,
     225,   745, -1813, -1813, -1813,   986,  4472,   667, -1813, -1813,
   -1813,  1691,  1574, -1813,  1694, -1813,  1594, -1813, -1813, -1813,
   -1813,  1361, -1813, -1813, -1813,  1578,  1695,  1554,  1545,  1309,
   -1813,  4472,   789, -1813,  1562, -1813,   731, -1813,  1727,  1456,
   -1813, -1813,  1120, -1813,   816,  1836, -1813,  1017, -1813, -1813,
   -1813,  1208,  1731,  1630,  1781,  4970,   376,  1198, -1813, -1813,
     376, -1813,  1198,  1203, -1813, -1813, -1813,  1413, -1813, -1813,
   -1813,  1198, -1813, -1813, -1813,  1198, -1813, -1813, -1813, -1813,
     376,   376,   147,   147, -1813, -1813, -1813, -1813, -1813,  1401,
   -1813,  1314, -1813, -1813, -1813,   808, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,  1108,  1697,
    1108,  1698, -1813, -1813,  4472, -1813, -1813, -1813, -1813, -1813,
    1734, -1813, -1813, -1813, -1813, -1813, -1813,  1547,  1547,  1547,
    1547,   376, -1813, -1813,   376,   147,   147, -1813, -1813, -1813,
    4428,  1544,  4428,  1546, -1813, -1813, -1813, -1813, -1813,  1733,
   -1813,   738, -1813,  1771, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813,   789,   948, -1813, -1813,   948,   -77,   986, -1813, -1813,
    4428, -1813, -1813,   873,  3748, -1813,  1823,  1639,  1662,   397,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813,   986,  1094, -1813, -1813, -1813,  1736,  1617,
     986,  1401,  4428, -1813,  1786, -1813,  1298,  1788,  1298,  1554,
     -47, -1813, -1813,  1737, -1813,  1624, -1813, -1813, -1813,   788,
   -1813, -1813,  1198,  1794,  1671, -1813,  1085, -1813,  1690,  1093,
    1437,  1702,  1459,  1198,  1300,  1198,   986, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,  1507,
   -1813, -1813, -1813, -1813,   737, -1813, -1813, -1813, -1813, -1813,
   -1813,   448, -1813,   472, -1813, -1813,  1413, -1813,   986,   785,
   -1813, -1813, -1813,   376, -1813, -1813, -1813, -1813, -1813, -1813,
    1108, -1813,  1108, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,  4472, -1813,
    4472, -1813, -1813, -1813, -1813, -1813,  1844,   948,   948, -1813,
    1493,  1595,   867,   437, -1813,   986, -1813, -1813,  1559,  4472,
   -1813,  1198,   686,  1663, -1813,  1664, -1813, -1813, -1813, -1813,
   -1813, -1813,   986, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813,   986,  1298, -1813,
     986,  1757, -1813, -1813, -1813, -1813, -1813,   867, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813,  1139,  1208,  1198,  1198,  1732,
   -1813,  1198, -1813, -1813, -1813, -1813,   586, -1813,  1198, -1813,
     986,   986,  1194,  1726, -1813,  1616,  1208,   737, -1813, -1813,
   -1813, -1813, -1813, -1813,   376, -1813, -1813, -1813, -1813,   376,
   -1813,   986, -1813,  1139, -1813, -1813, -1813, -1813,  1401,  1401,
   -1813,  4472,   948, -1813,  4472,  1198,   867,   867,  1604, -1813,
   -1813, -1813,  1490,   986,  1773, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813,   986, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813,  1208,  1208,  1198, -1813,  1208, -1813,
    1208, -1813,  1309, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813,  4472, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813,    -7,   867,  1198, -1813,   986, -1813,
   -1813, -1813, -1813, -1813, -1813,  1208, -1813, -1813, -1813,  1859,
   -1813,    -7, -1813, -1813,  4472, -1813, -1813
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1813, -1813, -1813, -1813,  1906, -1813, -1813, -1813,    37, -1813,
   -1813, -1813, -1813, -1813,  1576, -1813, -1813, -1813,  1243, -1813,
   -1813,    82,  1891, -1813, -1813,  1863,   198, -1813, -1813, -1813,
   -1813, -1813,  1738,  1787, -1813, -1813,  1748,   724, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813,  1740, -1813, -1813, -1813, -1813,
    1718, -1813, -1813, -1813, -1813, -1813,  -208,   625, -1813, -1813,
   -1813, -1813,  1435, -1813, -1813,  1357,   812, -1813, -1813, -1813,
   -1813, -1813, -1813,  1510, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813,  1802, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813,   607, -1813,   601,
     818, -1813, -1813, -1813, -1813, -1813,  1013,    79, -1813,  1369,
   -1813, -1813, -1813, -1813, -1813, -1813,   136, -1813,  1739, -1813,
    1838, -1813, -1813, -1813, -1813,  1579, -1813, -1813,   711, -1813,
   -1813, -1813, -1813,  1728, -1813,  1908,  1805, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813,  1103, -1813, -1813, -1813,  1404,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813,   691, -1813, -1813, -1813,  1658, -1813, -1813,  -552,
   -1813, -1813,  -292, -1813, -1813, -1813,  -198, -1813, -1813, -1813,
   -1813, -1813, -1813, -1305, -1304,  1129, -1297, -1813,    93, -1813,
   -1813, -1813,   302,   305, -1813,   416, -1813,   311, -1813,  -114,
   -1287, -1813, -1813, -1285, -1813, -1282, -1813, -1813, -1813,  1128,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813,  1436, -1813, -1813, -1813,  1033, -1813,  -900, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813,   -94, -1813, -1813, -1813, -1813,
   -1813, -1813,  -227, -1813, -1813, -1813, -1813,  -193, -1813, -1813,
   -1813, -1813, -1813,  1186, -1813, -1813, -1813, -1813, -1813, -1813,
     274, -1813, -1813, -1813, -1813, -1813,  1860,  1098, -1813,   239,
   -1813, -1813, -1813, -1813,  1522, -1813, -1813, -1813, -1813, -1813,
   -1813,  -856, -1813, -1813,   169, -1813, -1813, -1813, -1813,   962,
     608,   612, -1813, -1813,   295, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
     960, -1813, -1813,   262, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813,  -250, -1813,   227, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813,   759, -1813, -1813,
     763, -1813, -1813, -1813, -1813,   486,   223, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813,    40,   756, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813,   753, -1813, -1813, -1813,   205, -1813, -1813,   468,
   -1813, -1813, -1813, -1427, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1626,   940, -1813, -1813,   192,
   -1813, -1813,   452, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813,   693, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813,   732, -1813,   186, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813,   927, -1813,   924, -1813,
   -1813,  1134, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813,   920,   433, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813,    11, -1813,   436, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813, -1813, -1813,  -418, -1813, -1154, -1813, -1813, -1139, -1158,
   -1049, -1813,   359, -1813, -1011, -1813, -1813, -1813, -1813,    15,
   -1813, -1813, -1813, -1813,  -102, -1813, -1813,   209, -1813, -1813,
   -1813, -1813,    10, -1813, -1312, -1734, -1813, -1813,   556, -1813,
    -777, -1262,  -845, -1189, -1813, -1813, -1813, -1185, -1172, -1171,
   -1170, -1168,     4,  -204,  -757,  -885, -1100,  -858,   276,   959,
   -1016,   -84, -1813, -1085, -1813,  -822, -1813,   843,   -32,  -183,
   -1813, -1813,  -659,  1392,  -841,  -960,  -618,  -752, -1813, -1813,
     471, -1029, -1128,  -961,  -834, -1050,   630,  -601,  -220, -1813,
    1097,  -222,  -651,  -662,  -293,  -312,  -947, -1813, -1813, -1813,
   -1813, -1813,  1824, -1813,   450,   851, -1813, -1813, -1813, -1665,
    1221,    76,  1749,   799,  -430, -1813,  1023,  -389,  1473, -1813,
    -630, -1813, -1089,  1101,  -417,   712, -1813, -1813,  -705, -1813,
   -1812,  -168,  -541,  -505,  -154,  -981,   702, -1307,  -828, -1077,
   -1813,  1271,  2014,  -901, -1813, -1813, -1813, -1813, -1813, -1813,
   -1813,   642, -1813,   194,  -684,  1106,  -128
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1581
static const yytype_int16 yytable[] =
{
     121,   246,   288,   187,   456,   660,  1115,   843,   591,   848,
     880,   536,  1027,   971,  1227,   389,  1562,  1302,   912,  1311,
    1011,   265,   266,  1472,   341,   826,   271,   272,   273,   274,
     275,  1043,   277,  1020,   280,   854,  1473,  1474,  1475,   287,
    1476,  1646,  1647,  1058,  1015,  1327,   805,  1240,   554,  1648,
    1909,   288,  1515,  1049,  1198,   288,  1104,   288,   187,  1649,
     427,  1650,  1214,  1295,  1651,  1049,   288,  1088,   331,   121,
     332,  1049,  1156,   784,  1504,  1505,  1506,   339,  1049,  1606,
      85,  1707,  1708,   158,   158,   344,  1049,   849,   356, -1544,
    1249,   431,   360,  1384,   362,    22,   366,   289,  1249,   353,
     354,  1417,   355,   373,   278, -1504,   478,    89,   361,   105,
     409,  1353,  1005,  1392,   976,    54,  2172,   415,  1902, -1508,
    1353,  1005,  1037,  1935,   288,  1541,  2131,   179,  1569,  1510,
    2037,   571,   427,   934,   288,    41,  1069,  1071,  1508,  1829,
    1525,   288,  1955,   391,  1249,   158,   396,   398,  1370,   401,
    1111,  1005,   442,   384,    92,   471,  2173,   105,  1181,  1353,
     158,   416,   462,  1188,  2174,   410,  1353,  1353,   453,  1556,
     126,   428,  1542, -1544,   458,   465,   288,  1340,   430, -1580,
    1330,   662,   417,   962,  2021,  1288,   669,  1553,   473,  1387,
     586,  1366,   254,    63,  1928,   848,   158,  1308,  1303, -1580,
    1155,  -764, -1580,   573,  1786,   837,   376,   251,   370,    18,
     470,   922,   498,  1867,  2167, -1580,  2170,  1596, -1421,  1092,
     849,  1248,   537,    41,   455,  1014,   238,  1540, -1580,   499,
    1119,  1760,   467,  1599,   798,  1063,  2175,   550, -1526,  1093,
    1684,  1341,  -189,  1359,  1360, -1580,  1361,  1704,  -190,   856,
    1330,   811,  1203,  1353,   785,  1033,   805,  1120,   930,  1300,
     943,  1014,  1834,   587,    41, -1580,  1156,  1156,  1156,    91,
    1654,   239,  1393,   957,  1830,   574,  1156,  1846,   432,  1387,
    1868,  1203,  1869,   545,   371,  1114,  1543,   944,   945,  1598,
     376,  1678,   592,   446,   576,  1159,  1126,  1156,   786,  1156,
     812,  1156,  1014,   558,   559,  1156,  1156,  1156,  1156,  1156,
    1156,  1156,  1156, -1504,    52,  1265,  1093,  1171,  1172,  1732,
    1929,  1877,  1349,  1680,  1170,  1571,   661,  1882, -1468, -1468,
    1680,   666,  1515,   575,   106,  1544,   221,  1680,   671,   671,
    1249,  1779,   583,  1027,    14,   596,  1256,   384,  1173,  1683,
    1309,  2132,  1353,  1388, -1508, -1508,  2254,  1111,  1936,  -189,
      55,  1223,  1203, -1551,  1223,  -190,   285,   588,   595,  1166,
    1167,  -620,  1330,  1498,   -31,   655,  1490,    64,   183, -1508,
    1027,  1093,   106,  1985,  1570,   183,  1677,   931,   593,   118,
     285,   838,  1744,  1301,  1350,  1351,  1352,  1354,   257,   825,
     806,  1043,   923,   285,  1363,  1143,  1354,   828,  2246,   783,
      41,  1027,  1763,  1127,   788,   255, -1508,   792,  1903,   793,
    1389,   385,   795,   796,   472,  1555,   802,  1399,  1527,   285,
    1297, -1508,   107,  1406,  1408,  1409,  1411,  1761,   263,  1414,
    1416,   663,  1956, -1526,    56,  1354,   553,  -618,  1793,  1418,
     924,    89,  1354,  1354,    86,  1865,  1477,  1581,  1566,  1027,
    1733, -1504,  1241, -1508, -1508,   285,   932,  1937,   833,   834,
     977,  1156,  1156,  1156,  1156,  1156,  1156,  1156,  1304,  1754,
     107,   799,   183,   285,  -620,  1507,  1509,   479,   946,  1159,
    1159,  1159,   183,  1355,   285,   285,  1331,  1785,  1305,  1159,
    1541,   285,  1714,   252,   263,  1608,   285,  1511,   285,   572,
    1389,  1512, -1506,   952,  1367,  1297,   285,  1557,   338,  1803,
    1159,  1545,  1159,     4,  1159, -1508,  1403,    63,  1159,  1159,
    1159,  1159,  1159,  1159,  1159,  1159,   145,   855,   800,  1354,
   -1508, -1460,   168,  1821,  1899,  1818,   968,  1542,  1724,  1725,
    2127,  1842,  1586,  2128,   301,  1022,  1590,  1591,   569,  1593,
    -618,  1027,  1174,  -189,  1213,  1597,  1331,   285,  1887,  -190,
    2058,  2059,   288,  1762,  1064,   288,   288,  2010,  2060,  1022,
    1395,  1257,   288, -1508,  1711,  1850,   830,  1402,  2062, -1508,
    2063,  2143,  1344,  2064,  1297,  1249,   183,   170,  1515,  1668,
    1669,  1670,  1671,  1672,  1673,  1675,    75,  2308,   340,   431,
     806,  1747,   936,   937,   927,   388,   926,   285,   291,   942,
    2237,  1353,   418,  1177,  1133,   407,   168,  1357,  1358,  1359,
    1360,  1919,  1361,  2144,  1680, -1466,   951,   980,  1354, -1531,
     168,  1655,  1482,   588,  1258,  1160,  1018,  1524,   168,   947,
       5,    88,  1744,  2145,   169,   476,  1297,  1740, -1504, -1551,
    1577,  1543,     3,   419,  1577,  1933,  1792,  1066,  2310,  1289,
     420,  1081,  1794,  1085,   900,  1085,  1091,  1819,  1066,  1168,
       4,  1676,  -978,   459,  1960,  2315,  1962,  1665,  1331,  -207,
      75,  2210,  1851,  1085,  1159,  1159,  1159,  1159,  1159,  1159,
    1159,   408,  2232,  1134,    75,  1328,   288,   831,   839,  1129,
    1544,    64,    75,  1817,  1237,  2215,  1297,  1335, -1580,  1990,
    2238,  1926,   288,  -978,  2023,  1656,  1357,  1358,  1359,  1360,
    -978,  1361,  1804,  1147, -1464,  1748,    32,   170,   169,  2191,
    1163,   421,  2211,  1125,  1735,  1905,  1906,  1907,  1664,   840,
    1530,  2022,   169,  1531,  1532,    12,   288,   288,   238,  1136,
     169, -1580,    65,  1082,  1022,    13,  2216,  1908,   285,  1178,
   -1520,  1980,  1913,  1914,  1927,  1138,  1916,  1917,  1918,  1805,
    1921,  1922,  1930,  1751,   460,  2030,   901,  1029,   285,  2108,
    2109,  2110,  2111,  1713,   839,  1483,   432,  1881,   839,  1529,
     928,  -978,  1530,   239,   422,  1531,  1532,     5,  1083,  1829,
    1086,  1657,   285,  2093,  2093,  1106,    16,  1920,  2077,    29,
     813,     5, -1504,  1336,  1117,     5,   340,  2025,  2146,  2153,
    2082,  1156,   241,   423,   247,  1844,  1156,  1223,   167,  1160,
    1160,  1160,  2154,  2155,  2156,  1795,  2157,    23,   249,  1160,
    2090,  2091,  1223,  2129,  1798,    55,   342,  1249,   183,   285,
    1283, -1580,  1997,    26,  -978, -1531,  2093,  2093,  1091,   814,
    1160,  1238,  1160,   424,  1160,    19,  1404,   346,  1160,  1160,
    1160,  1160,  1160,  1160,  1160,  1160,  1297,  1297,   482, -1504,
     418,  2212,  2213,  -978,  1813,  1491,  1545,   250,  2095,  1945,
    1946,  2112,   347, -1580,  2113,  1284,   309,  1354,  1931,   986,
      30,    93,   839,    33,   418,  2217,  2218,  1497,  1297,   294,
     841,  1343,   418, -1580,   300,  1958,  1961,  -978,  1963,   483,
    1254,   419,  1498,  -978,  1966,  1655,   484,  2271,   420,    56,
    1216,   242,  1806,  1965,  1830,    34,   857,  1492,  1082,  2117,
      20,  2119,   310,   288,  2184,   419,  1567,   503, -1520,  1911,
     504,  1027,   420,   419,  1915,  1337,   311,  2031,    36,   340,
     420,    44,   250,    94,    38,   505,   418,  1491,  1814,  2136,
     418, -1580,  1713,  1568,   987,   506,   379,  1533,  1534,  2185,
      49,  2205,  2008,  1027,  1270,  1357,  1358,  1359,  1360,   989,
    1361, -1580, -1522, -1461,   312,  1535,  1536,   486,  1133,   421,
    2164,  2165,    50,    95,  2177,    96,   815,   419,   251,  1656,
     340,   419,   390,   141,   420,  1491,   291,   397,   420,  1492,
    1018,  2206,  1093,   421,  1271,  2312,   817,  1666,   910,  1533,
    1534,   421,  1272,  2223,  1160,  1160,  1160,  1160,  1160,  1160,
    1160,   819,  1621,   435,  1159,   436,  1219,  1535,  1536,  1159,
    1018,   507,   405,    53, -1580,   816,   188,  2097,  1189, -1526,
     487,   447,   422,  -207,  1996,  2032,  2183,  1492,   142,   143,
     189,   190,   406,   990, -1580,   818,  2107,  1134,  1489, -1526,
     835,  1752,   508,  1210,   418,   421,   422,  1835, -1580,   421,
     820,   423,   183,  2116,   422,   481,   392,  1018,   393,  2137,
     836,  1753,   191,  2152,  1273,    41,  2236,  1836,   288,   288,
     313,  1812,   914,  1278,   991,   423,  2094,    59,  1807,  2138,
      45,   992,   314,   423,    60,   419,  1279,   993,  1297,   490,
     994,   424,   420,   446,  2147,  2148,  1297,  1485,  1979,   192,
     193,    61,   194,  2150,   507,  1614,  1614,  1891,   422,   285,
     195,  1575,   422,   915,  2287,   424,    62,   285,    46,  2288,
     916,  1087,   995,   424,   183,   482,    47,   789,  2114,  2115,
     183,   118,  2103,    68,   790,   508,  1396,   423,   260,  1123,
    1400,   423,   509,  1039,  1297,  1044,  1045,  1040,  1412,  1413,
    1575,  1979,  1718,   196,   197,  1721,   577,     5,  1603,  1046,
    1726,   582,  1604,   421,   198,    72,   483,  2290,  2291,   315,
     316,  2295,   515,   484,   285,   285,  2201,   424,    75,  1584,
    2077,   424,   317,  1585,   318,   485,    79,   510,  1486,    81,
     996,   917,  2224,   511,  2099,    10,  2101,  1428,  1429,    10,
    2227,  1357,  1358,  1359,  1360,  1047,  1361,   237,    82,  1018,
    2228,   237,  2229,   183,   114,  2230,  1357,  1358,  1359,  1360,
     512,  1361,  1319,   103,  1320,  1430,   422,   513,  1362,   115,
    1241,  1431,  1518,  2275,  2276,   997,   998,  1878,   199,  1879,
     514,  -333,  -333,  2249,   486,  2250,  1357,  1358,  1359,  1360,
     116,  1361,  2251,   118,   918,   423,   188,  2277,  1716,   124,
     999,  1989,  1433,   128,   252,   515,  1434,   516,   129,  1022,
     189,   190,  2258,  2259,  1938,   517,  1939,  1952,  1000,  1953,
    1979,  1868,   130,  1869,   319,  -212,  1001,   303,   304,   285,
    1618,  1619,   131,  2298,   132,   424, -1413, -1413, -1413, -1413,
    1705,  2190,   191,  1220,   320,   133,   518,   487,  2194,  2195,
     488,   489,  1357,  1358,  1359,  1360,   135,  1361,  2260,  2261,
    1667,   136,   138,   919,   139,  1357,  1358,  1359,  1360,   148,
    1361,   149,   150,  1720,   165,   164,   166,  2242,   179,   192,
     193,   288,   194,   217,   220,   221,  2301,   223,  1874,   225,
     195,   229,   200,   231,  1160,   519,   245,   230,    41,  1160,
     259,   262,   986,   263,  1883,   839,  2225,   268,  2226,   269,
    1845,   278,   285,  1423,  1424,  1425,   490,   289,  1614,   291,
    1820,  1426,   296,   297,   288,   298,   333,   336,  2222,   334,
     340,   345,   201,   196,   197,   343,   348,   349,  1871,  1231,
    1232,  1233,  1234,   357,   198,  1876,   382,   381,   288,   399,
     402,   404,  1880,   411,   412,   429,  1848,   444,   449,  1427,
    -350,  1886,   451,  1848, -1412, -1412, -1412, -1412,   454,  2292,
     466,   468,  2293,  2278,  2279,   496,   538,   987,   500,   546,
     548,   202,   551,   984,   555,  1897,   578,  1021,   288,   557,
    1371,  1372,   989,  1035,   281,   581,   579,   584,  1052,  1053,
    1947,  1948,  1949,  1950,  1052,  1060,  1062,   594,   657,  1900,
     659,  1021,  1901,   183,  2280,  2281,   674,  1052,   199,   667,
     675,  2309,   588,   779,   794,  1912,  1060,  1116,   803,  1118,
     303,  1373,   810,  1374,  1448,   821,   823,  1450,  1451,   829,
     860,   861,  1583,  -830,   904,   586,  1686,   935,  1687,   938,
     941,  1688,  2316,   954,  1428,  1429,   955,   960,   957,   963,
     965,  1689,   969,   972,   978,  1375,  1376,  1377,   975,   981,
     982,  1009,  1038,   267,  1030,  1122,   990,  1158,  1055,  1124,
    1130,   276,  1430,  1139,  1145,  1161,  1951,   418,  1431,  1164,
    1148,   849,  1954,  1357,  1358,  1359,  1360,  1175,  1361,  1182,
     283,  1723,  1357,  1358,  1359,  1360,  1184,  1361,  1183,  1186,
    1728,  1432,  1378,  1199,  1379,  1190,  1204,   991,  1191,  1433,
    1192,  1206,  1380,  1434,   992,  1209,  1217,  1193,   419,  1194,
     993,  1225,   200,   994,  1987,   420,  1211,  1195,  1196,  2041,
    1228,  1197,  1223,  1215,  1235,  2269,  1247,   351,   352,  1251,
    1267,  2197,  1266,  1435,  1436,   358,   359,  1269,  1437, -1415,
    1276,   365,   368,  1280,  1282,   995,  1281,  1286,  1438,  1291,
    1052,  1293,   201,  1093,   158,  1439,  1315,  1318,  1052,  1255,
    1440,  1322,  1324,  1993,  1347,  1325,  1368,  1364,  1690,  1999,
    1398,  1385,  1691,  1405,  1420,  1381,  1021,  1501,  1441,  2081,
    1419,  1478,  1014,  1521,  2083,  1692,   421,  1516,  1539,  1093,
    1554,  1558,  1296,  2088,  1580,  1572,  1587,  2089,  1588,  1595,
    1052,   202,  1610,  1612,  1052,  1600,  1361,   446,  1616,  1705,
    1681,  1388,  1314,   996,  1682,  1255,  1357,  1358,  1359,  1360,
    1685,  1361,  1734,  1739,  1894,  1736,   433,  1357,  1358,  1359,
    1360,  1717,  1361,  1693,  1719,  2096,  1722,   288,  1215,  1729,
    1757,  1060,  1780,  1782,  1727,  1784,  1492,  1788,  1799,   422,
    1796,  1158,  1158,  1158,  1800,  1822,  1825,  1826,   997,   998,
    1837,  1158,  1838,  1839,  1852,  1853,  1861,  1872,  1863,  1657,
    1924,  1895,  1943,  1944,  2134,  1584,  1968,  1296,   423,  1585,
    1694,  1974,  1158,   999,  1158,  1981,  1158,  1970,  1984,  1976,
    1158,  1158,  1158,  1158,  1158,  1158,  1158,  1158,  1988,  2002,
    2007,  1000,  1830,  2005,  1695,  2012,  2015,  2026,  2017,  1001,
    2020,  2024,   285,  2038,  2042,  2028,  2043,  2045,   424,  2085,
    2100,  2102,  2209,  1442,  1443,  1444,  1445,  1446,  1696,  1447,
    2104,  1448,  1449,  1697,  1450,  1451,  2122,  2118,   288,  2120,
    2125,  1382,  2139,  1698,  2186,  2140,  2141,  1699,  2159,  2161,
     987,  2168,  2180,  2032,  2187,  2200,  1296,  2202,  2188,  2192,
    2198,  2199,  2054,  2231,  2233,   989,  1052,  2235,  2241,  2247,
    2248,  2256,  2283,  2266,  2284,   287,  2296,  2297,  2314,  1565,
    2299,  1383,    15,    28,   414,  2240,  1215,    74,   186,   248,
     882,   258,   282,  1578,   261,  -921,  1582,   570,  -921,   781,
    1052,  -921,  -921,  -921,  1700,   495,  1329,   219,  1764,  1611,
    1615,  1765,  1594,  1332,  1701,  1132,  2040,   146,  1296,  1766,
    1767,  1768,   791,   443,  1602,   293,  1991,    67,   233,   284,
     383,   979,   961,   672,  2263,  1893,  1890,   782,  2061,  1816,
    1889,  1255,  2220,  2243,   974,  2204,   597,  -921,  1142,   990,
    2286,   288,  1934,   163,  2285,  2209,  1158,  1158,  1158,  1158,
    1158,  1158,  1158,  1994,   953,  1230,   560,  1904,  1239,  1710,
    -921,   288,  1709,  1932,  1957,  1523,  1519,  1791,  1296,  1538,
    1964,  2124,  1550,  1983,  1801,  -921,  1275,  1995,  2274,  2264,
    2265,  1609,  1827,  2268,  1299,  1298,  1579,  2011,  1715,  1313,
    2270,  1019,  1105,   993,  1859,  2166,   994,  1860,   373,  1898,
    2245,  2004,  2303,  2304,  2171,  2182,  2306,  1290,  2307,   986,
    1052,  1759,   839,  1480,  1843,  1162,  2221,  1422,   302,   967,
    1769,  1866,   395,  1552,  1246,   797,  1165,  2294,   995,  2289,
     940,    76,  -921,  -921,  1018,     0,  1738,  2084,  1770,  1169,
       0,     0,     0,  2313,     0,     0,     0,     0,     0,     0,
       0,  1018,     0,   446,     0,  1771,     0,     0,  2305,  -921,
    -921,     0,     0,     0,     0,     0,  -921,     0,     0,     0,
    -921,     0,  1745,  1746,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   987,     0,     0,     0,  2311,  -921,
       0,     0,     0,     0,     0,   988,   996,  -921,     0,   989,
    -921,  -921,     0,  1772,     0,     0,     0,  -921,     0,     0,
       0,  -921,   446,  -921,     0,     0,  -921,     0,  -921,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -921,  -921,     0,     0,     0,  -921,     0,  1296,  1296,
       0,   997,   998,     0,  1052,  1052,  -921,     0,  -921,     0,
    1773,     0,     0,  -921,     0,     0,     0,     0,     0,     0,
       0,     0,  1828,     0,     0,     0,   999,     0,     0,   986,
    1296,   446,   839,     0,     0,     0,  -921,     0,     0,     0,
       0,     0,     0,   990,  1000,  1849,     0,     0,     0,  -921,
    1858,  1858,  1001,  1177,   418,   285,     0,     0,     0,     0,
       0,     0,     0,  1774,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1775,     0,     0,  -921,     0,     0,     0,
       0,  1021,     0,     0,   991,     0,     0,     0, -1504,     0,
       0,   992,  1884,     0,  1885,   419,     0,   993,     0,     0,
     994,     0,   420,     0,   987,     0,     0,     0,     0,     0,
       0,     0,  -921,     0,     0,     0,     0,     0,     0,   989,
       0,  -921,  -921,     0,     0,   987,     0,     0,     0,     0,
       0,     0,   995,     0,  1776,     0,     0,     0,     0,     0,
     989,  -921,     0,     0,     0,     0,  -921,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1215,  1215,  1215,     0,
       0,     0,     0,     0,  -921,     0,  1158,     0,     0,     0,
       0,  1158,  -921,   421,     0,  -921,     0,     0,     0,     0,
       0,  -921,  -921,  -921,  1052,     0,     0,  -921,     0,  -921,
       0,  -921,  -921,  -921,     0,     0,     0,     0,     0,     0,
     996,     0,     0,   990,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   418,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   990,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   418,   422,     0,     0,     0,
       0,     0,     0,  1967,   991,   997,   998,     0,     0,  1978,
    1296,   992, -1504,     0,     0,   419,     0,   993,  1296,     0,
     994,     0,   420,     0,     0,   423,     0,  1052,     0,     0,
     999,     0,     0,     0,     0,  1565,   419,     0,   993,     0,
       0,   994,     0,   420,     0,     0,     0,     0,  1000,     0,
       0,     0,   995,     0,     0,     0,  1001,  -345,   599,   285,
       0,     0,  1978,     0,     0,   424,  1296,     0,     0,     0,
       0,     0,     0,   995,     0,     0,     0,     0,   600, -1504,
       0,     0,     0,     0,     0,     0,  2079,     0,     0,     0,
    2079,   601,     0,   421,   602,   603,   604,   605,   606,   607,
     608,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2079,  2079,     0,     0,   421,     0,     0,     0,     0,     0,
     996,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     609,     0,   610,   611,   612,   613,   614,   615,     0,     0,
       0,   996,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   422,     0,     0,     0,
       0,  2079,     0,     0,  2079,   997,   998,     0,     0,     0,
       0,     0,   616,     0,     0,     0,     0,   422,     0,     0,
       0,     0,     0,     0,     0,   423,   997,   998,     0,  -345,
     999,  1978,     0,  -345,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   423,     0,  1000,     0,
       0,   999,     0,     0,     0,     0,  1001,     0,     0,   285,
       0, -1526,  -345,  1060,     0,   424,     0,     0,     0,  1000,
    2163,     0,     0,     0,     0,     0,  -345,  1001,     0,     0,
     285, -1526,     0,     0,     0,     0,   424,     0,     0,  2079,
       0,     0,     0,     0,   617,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2203,    41,     0,     0,
     618,     0,     0,     0,     0,     0, -1561,     0,     0,     0,
    -345,  -345,     0,     0,     0,     0,     0,     0,  -345,   619,
       0,     0,  -345,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  2079,     0,     0,   620,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -615,
     561,     0,  -655,     0,  -655,     0,     0,     0,   621,  -655,
       0,     0,     0,     0,     0,     0,     0,  -655,     0,     0,
       0,     0,     0,   622,     0,     0,     0,     0,     0,     0,
     623,     0,   624,     0,     0,     0,     0,     0,     0,  -345,
       0,     0,  1255,  -345,     0,   625,     0,     0,     0,     0,
    -655,  -655,     0,     0,     0,   626,     0,  2253,  -655,     0,
    2255,     0,   627,     0,  -345,     0,     0,     0,     0,  -655,
       0,     0,     0,  -655,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -345,     0,  -655,  -345,     0,     0,     0,
    2272,     0,     0,     0,     0,     0,     0,     0,     0,   628,
       0,   629,   630,   631,  2079,     0,     0,  -655,     0,  2079,
       0,     0,     0,     0,  -655,  -655,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   632,     0,     0,     0,     0,
       0,  -615,     0,  1060,     0,  -615,     0,     0,     0,     0,
       0,     0, -1561,     0,  2302,  -655,     0,     0,     0,     0,
     633,   634,   635,     0,     0,     0,     0,  -655,     0,     0,
       0,  -655,     0,   636,     0,     0,   637,     0,     0,     0,
       0,     0,     0,     0,  -655,  -345,     0,     0,  -615,     0,
       0,  -655,     0,     0,  -655,  -655,  -345,     0,  1255,     0,
       0,     0,  -655,     0,     0,     0,     0,     0,     0,  -655,
       0,  -655,     0,     0,  -655,     0,     0,     0,   561,     0,
    -655,     0,  -655,     0,     0,     0,     0,  -655,     0,     0,
     987,     0,     0,     0,     0,  -655,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   989,     0,     0,     0,     0,
       0,  -655,     0,     0,     0,  -655,     0,  -655,     0,     0,
       0,     0,     0,     0,  -655,     0,     0,     0,  -655,  -655,
       0,     0,     0,     0,     0,     0,  -655,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -655,  -655,     0,     0,
       0,  -655,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -655,     0,  -655,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -615,     0,     0,     0,     0,
       0,     0,  -655,  1073,     0,  -655,     0,     0,     0,   990,
       0,  -655,  -655,  -655,     0,     0,     0,     0,     0,     0,
     673,     0,     0,     0,  -655,     0,     0,     0,     0,  -655,
       0,  -655,     0,     0,     0,     0,     0,     0,     0,  -655,
       0,     0,     0,  -655,     0,     0,     0,     0,     0,  -655,
       0,     0,     0,     0,     0,  -655,     0,     0,  -655,  -655,
       0,  1074,     0,   993,     0,     0,   994,  -655,     0,  -655,
    -655,     0,  -655,  -655,     0,  -655,     0,     0,     0,  -655,
    -655,     0,  -655,  -655,     0,     0,     0,     0,     0,     0,
    -655,     0,     0,     0,     0,  -655,     0,  -655,   995,  -655,
    -655,     0,  -655,     0,     0,  -655,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -655,     0,     0,     0,
       0,     0,     0,     0,     0,   562, -1496,     0,  -655, -1496,
       0,     0, -1496, -1496, -1496,     0,     0,  1240,  -655,  -655,
       0, -1496,     0,  -655,     0,  -655,     0,     0,     0,     0,
       0,     0,  -655,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   996,     0,     0,     0,
       0,     0,     0,     0,  -655,     0,     0,     0, -1496,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -655,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0, -1496,     0,     0,     0,     0,     0,     0,     0,     0,
    -655,   997,   998,     0,     0,     0, -1496,     0,     0,  -655,
       0, -1580,     0,     0,     0,     0,     0,   986,     0,     0,
     839,     0,  -655,  1457,  1458,  1459,   999,  -655,     0,  -655,
       0,     0,     0,     0,     0,     0, -1029,  -655,     0,     0,
       0,     0,     0,     0,  1000,     0,     0,  -655,     0, -1029,
       0,     0,  1001,     0,   183,   285,  -655,     0,     0,     0,
       0,     0,     0, -1496, -1496,  -655,     0,  -655,  -655,  1460,
       0,  -655,     0,  -655,     0,     0,     0,     0,  -655,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   -1496, -1496,   987,  -655,     0,     0,     0, -1496,  -655,     0,
       0, -1496,     0,  -655,     0,     0,     0,   989,     0,     0,
       0,     0,     0,     0,  -655,     0,     0,     0,     0,     0,
   -1496,     0,     0,   562,     0,     0,  -655,     0, -1496,     0,
       0, -1496, -1496,     0,     0,     0,  -655,     0, -1496,     0,
       0,     0, -1496,     0, -1496,     0,     0, -1496,     0, -1496,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0, -1496, -1496,  1428,  1429,     0, -1496,     0,     0,
       0,     0,     0,     0,     0,     0,     0, -1496,     0, -1496,
       0,     0,     0,     0, -1496,     0,     0,     0,     0,     0,
       0,   990,  1430,     0,     0,     0,     0,     0,  1431,     0,
       0,     0,   418,     0,     0,     0,     0, -1496,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   -1496,  1461,     0,     0,     0,     0,     0,     0,     0,  1433,
       0,     0,   991,  1434,     0,     0,     0,     0,     0,   992,
       0,     0,     0,   419,     0,   993,     0, -1496,   994,     0,
     420,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1462,  1463,     0,     0,     0,  1464,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1465,     0,
     995,     0,     0, -1496,     0,  1466,     0,     0,     0,     0,
       0,     0, -1496, -1496,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1467, -1496,
       0,     0, -1496, -1496,     0,     0,     0, -1496,     0,     0,
     986,   421,     0,   839,     0,   676,     0,   677,     0,     0,
       0,     0,   678,     0,     0, -1496,     0,     0,     0,     0,
     679,     0,     0, -1496,     0,     0, -1496,     0,   996,     0,
       0,     0, -1496, -1496, -1496,     0,     0,     0, -1496,     0,
   -1496,     0, -1496, -1496, -1496,     0,     0,     0,     0,     0,
       0,     0,     0,   680,   681,     0,     0,     0,     0,     0,
       0,   682,     0,     0,   422,     0,     0,     0,     0,     0,
       0,     0,   683,   997,   998,   987,   684,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   685,     0,
     989,     0,     0,   423,     0,     0,     0,     0,   999,     0,
       0,     0,     0,  1108,     0,     0,     0,     0,     0,     0,
     686,     0,     0,     0,     0,     0,  1000,   687,   688,     0,
       0,     0,     0,     0,  1001,     0,     0,   285,     0,     0,
       0,     0,     0,   424,  1468,  1469,     0,     0,     0,  1470,
       0,  1448,     0,  1471,  1450,  1451,     0,     0,   689,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     690,     0,     0,     0,   691,     0,     0,     0,     0,     0,
       0,   676,     0,   677,   990,     0,     0,   692,   678,     0,
       0,     0,     0,     0,   693,   418,   679,   694,   695,     0,
       0,     0,     0,     0,     0,   696,     0,     0,     0,     0,
    1312,     0,   697,     0,   698,     0,     0,   699,     0,     0,
       0,     0,     0,     0,     0,   991,     0,     0,     0,   680,
     681,     0,   992,     0,     0,     0,   419,   682,   993,     0,
       0,   994,     0,   420,     0,     0,     0,  -787,   683,     0,
    -787,     0,   684,     0,   700,     0,     0,     0,   701,     0,
     702,     0,     0,     0,   685,     0,     0,   703,     0,     0,
       0,     0,     0,   995,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   686,     0,     0,   704,
     158,     0,     0,   687,   688,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   705,     0,     0,     0,     0,   986,
       0,     0,   839,     0,   421,     0,     0,     0,     0,     0,
       0,     0,  -787,     0,   689,   706, -1508,     0,     0,     0,
       0,     0,     0,     0,   707,     0,   690,  -787,     0,     0,
     691,   996,     0,     0,     0,     0,     0,   708,     0,     0,
       0,     0,   709,   692,   710,     0,     0,     0,     0,     0,
     693,     0,   711,   694,   695,     0,     0,     0,     0,     0,
       0,   696,   712,     0,     0,     0,     0,   422,   697,     0,
     698,   713,     0,   699,   987,     0,   997,   998,     0,     0,
     714,     0,   715,   716,     0,  1067,   717,     0,   718,   989,
       0,     0,     0,   719,     0,     0,   423,     0,     0,     0,
       0,   999,     0,     0,     0,     0,     0,     0,   720,     0,
     700,  -787,     0,   721,   701,     0,   702,     0,   722,  1000,
       0,     0,  -787,   703,     0,     0,     0,  1001,     0,   723,
     285,     0,     0,     0,     0,     0,   424,     0,     0,     0,
       0,   724,     0,     0,     0,   704,     0,     0,     0,     0,
       0,   725,  -787,     0,     0,     0,     0,     0,     0,  -787,
     705,     0,     0,  -787,     0,  -787,     0,     0,  -787,     0,
    -787,     0,     0,   990,     0,     0,     0,     0,     0,     0,
       0,   706,     0,   986,   418,     0,   839,     0,     0,     0,
     707,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -787,     0,     0,   708,     0,  -787,     0,     0,   709,     0,
     710,     0,     0,     0,   991,     0,   986,     0,   711,   839,
       0,   992,     0,     0,     0,   419,     0,   993,   712,     0,
     994,     0,   420,     0,     0,     0,     0,   713,     0,     0,
       0,  -787,     0,     0,     0,     0,   714,     0,   715,   716,
       0, -1508,   717,     0,   718,     0,     0,     0,   987,   719,
       0,     0,   995,     0,     0,     0,     0,     0,  -787,     0,
       0,     0,     0,   989,   720,     0,     0,     0,     0,   721,
       0,     0,     0,     0,   722,     0,  1108,     0,     0,     0,
     986,   987,     0,   839,     0,   723,     0,     0,  -787,     0,
       0,     0,  1112,   421,  -787,     0,   989,   724,     0,     0,
       0,     0,     0,  -787,  -787,     0,     0,     0,   986,     0,
       0,   839,     0,     0,     0,     0,     0,     0,     0,     0,
     996,     0,     0,  -787,     0,     0,     0,     0,  -787,     0,
       0,     0,     0,  -787,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -787,   990,     0,     0,
   -1508,     0,     0,     0,  -787,   987,   422,  -787,   418,     0,
       0,     0,     0,  -787,     0,   997,   998,     0,     0,     0,
     989,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     990,     0,     0,   987,     0,   423,     0,     0,   991,     0,
     999,   418,     0,     0,     0,   992,     0,     0,   989,   419,
       0,   993,     0,     0,   994,     0,   420,     0,  1000,     0,
       0,     0,     0,     0,     0,     0,  1001,     0,     0,   285,
       0,   991,     0,     0,     0,   424,     0,     0,   992,     0,
       0,     0,   419,     0,   993,     0,   995,   994,     0,   420,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   990,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   418,     0,   986,     0,   995,
     839,     0,     0,     0,     0,     0,     0,   421,  1317,     0,
       0,     0,   990,   839,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   418,     0,   991,     0,     0,     0,     0,
       0,     0,   992,     0,   996,     0,   419,     0,   993,     0,
     421,   994,     0,   420,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   991,     0,     0,     0,     0,     0,     0,
     992,     0,     0,     0,   419,     0,   993,   996,     0,   994,
     422,   420,   987,   995,   986,     0,     0,   839,     0,   997,
     998,     0,     0,     0,     0,   987,     0,   989,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   423,
     989,   995,     0,   422,   999,     0,     0,     0,     0,     0,
       0,     0,   997,   998,   421,     0,     0,     0,   986,     0,
       0,   839,  1000,     0,     0,     0,     0,     0,     0,     0,
    1001,     0,   423,   285,     0,     0,     0,   999,     0,   424,
       0,   996,   421,     0,     0,     0,     0,     0,     0,   987,
       0,     0,     0,     0,     0,  1000,     0,   986,     0,     0,
     839,     0,     0,  1001,   989,     0,   285,     0,     0,   996,
       0,   990,   424,     0,     0,     0,     0,   422,     0,     0,
       0,     0,   418,     0,   990,     0,   997,   998,     0,     0,
       0,     0,     0,   987,     0,   418,     0,     0,     0,     0,
       0,     0,  1201,     0,     0,   422,   423,     0,   989,     0,
       0,   999,   991,     0,   997,   998,     0,     0,     0,   992,
       0,     0,     0,   419,     0,   993,     0,     0,   994,  1000,
     420,     0,   987,     0,   423,     0,   419,  1001,   993,   999,
     285,   994,     0,   420,     0,     0,   424,   989,   990,     0,
       0,     0,     0,     0,     0,     0,     0,  1000,     0,   418,
     995,     0,     0,     0,     0,  1001,     0,     0,   285,     0,
     987,     0,     0,   995,   424,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   989,     0,     0,     0,   991,
       0,     0,   990,     0,     0,     0,   992,     0,     0,     0,
     419,   421,   993,   418,     0,   994,     0,   420,     0,     0,
       0,     0,     0,     0,   421,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   996,     0,
       0,   990,     0,   991,     0,     0,     0,   995,     0,     0,
     992,   996,   418,     0,   419,     0,   993,     0,     0,   994,
       0,   420,     0,     0,     0,     0,     0,     0,  1592,     0,
       0,     0,     0,  1073,   422,     0,     0,     0,     0,   990,
       0,     0,   991,   997,   998,     0,     0,   422,   421,   992,
       0,   995,     0,  1031,     0,   993,   997,   998,   994,     0,
     420,     0,     0,   423,     0,     0,     0,     0,   999,     0,
       0,     0,     0,     0,     0,   996,   423,     0,     0,     0,
       0,   999,     0,     0,     0,     0,  1000,     0,     0,     0,
     995,  1019,   421,   993,  1001,     0,   994,   285,     0,  1000,
       0,     0,     0,   424,     0,     0,  1729,  1001,     0,     0,
     285,   422,     0,     0,     0,     0,   424,     0,     0,   996,
     997,   998,     0,     0,     0,     0,     0,     0,   995,     0,
       0,   421,     0,     0,     0,     0,     0,     0,     0,     0,
     423,     0,     0,     0,     0,   999,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   422,     0,     0,   996,     0,
       0,     0,     0,  1000,   997,   998,     0,     0,     0,     0,
       0,  1001,     0,     0,   285,     0,     0,     0,     0,     0,
     424,     0,     0,     0,   423,     0,     0,     0,     0,   999,
       0,     0,     0,     0,   422,     0,   996,     0,     0,     0,
       0,     0,     0,   997,   998,     0,     0,  1000,     0,     0,
       0,     0,     0,     0,     0,  1001,     0,     0,   285,     0,
       0,     0,     0,   423,   424,  1622,     0,  1623,   999,     0,
    1624,   602,   603,   604,   605,   606,   607,   608,  1625,  1626,
    1627,   997,   998,     0,     0,     0,  1000,     0,     0,     0,
       0, -1580,     0,     0,  1001,     0,     0,   285,     0,  1628,
       0,     0,     0,   424,     0,     0,   999,   609,     0,   610,
     611,   612,   613,   614,   615,     0, -1029,     0,     0,     0,
       0,     0,     0,     0,  1000,     0,     0,     0,     0, -1029,
       0,     0,  1001,     0,   183,   285,     0,     0,     0,   602,
     603,   604,   605,   606,   607,     0,     0,     0,     0,   616,
       0,     0,     0,     0,     0,     0,     0,   602,   603,   604,
     605,   606,   607,   608,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   609,     0,   610,   611,   612,
     613,   614,   615,     0,     0,  2046,  2047,     0,     0,  1629,
       0,     0,     0,   609,     0,   610,   611,   612,   613,   614,
     615,     0,     0,     0,     0,     0,     0,  1630,     0,     0,
    1631,  1632,     0,     0,     0,     0,     0,   616,     0,     0,
       0,     0,     0,     0,  1633,     0,     0,     0,     0,     0,
       0,   617,     0,     0,     0,   616,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   618,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1634,     0,     0,     0,     0,     0,   987,
       0,     0,  1635,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   620,   989,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   617,
       0,     0,     0,     0,     0,  1636,     0,     0,  2048,     0,
       0,     0,     0,     0,     0,     0,     0,   617,     0,  1637,
     622,     0,     0,     0,     0,     0,     0,   623,     0,   624,
       0,     0,     0,   618,     0,     0,     0,     0,     0,     0,
       0,     0,   625,  1638,     0,     0,     0,     0,     0,  2049,
    2050,   620,     0,     0,     0,   987,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1639,   990,   620,
     989,     0,  1640,     0,  2051,     0,     0,     0,     0,   418,
       0,     0,     0,     0,     0,     0,  1641,     0,   622,     0,
       0,   621,     0,     0,     0,     0,   628,   624,   629,   630,
     631,     0,     0,     0,     0,     0,   622,     0,     0,  1150,
     625,     0,     0,   623,     0,   624,   992,     0,  2052,     0,
     419,     0,   993,     0,     0,   994,     0,   420,   625,     0,
       0,     0,  1642,     0,     0,     0,     0,     0,   987,     0,
       0,     0,     0,  1643,     0,     0,     0,   633,   634,   635,
       0,     0,     0,   989,   990,     0,     0,   995,     0,     0,
     636,     0,  1644,   637,     0,   418,   629,   630,   631,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   628,  1645,   629,   630,   631,     0,     0,     0,
       0,  2053,     0,     0,     0,  1150,     0,     0,   421,     0,
       0,     0,   992,     0,     0,  2054,   419,     0,   993,     0,
       0,   994,     0,   420,     0,   633,   634,   635,     0,     0,
       0,     0,     0,     0,     0,   996,     0,     0,  2055,     0,
       0,     0,     0,   633,   634,   635,     0,   990,     0,     0,
       0,     0,     0,   995,     0,     0,   636,     0,   418,   637,
    2056,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   422,     0,     0,     0,     0,     0,     0,     0,  2057,
     997,   998,     0,     0,     0,     0,     0,     0,  1150,     0,
       0,     0,     0,     0,   421,   992,     0,     0,     0,   419,
     423,   993,     0,     0,   994,   999,   420,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   996,     0,  1000,     0,     0,     0,     0,     0,     0,
       0,  1001,     0,     0,   285,     0,   995,     0,     0,     0,
     424,  1151,  1152,     0,     0,     0,     0,     0,     0,  1674,
    1153,     0,     0,     0,     0,     0,     0,   422,     0,     0,
       0,     0,     0,     0,     0,     0,   997,   998,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   421,     0,     0,
       0,     0,     0,     0,     0,     0,   423,     0,     0,     0,
       0,   999,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   996,     0,     0,     0,     0,  1000,
       0,     0,     0,     0,     0,     0,     0,  1001,     0,     0,
     285,     0,     0,     0,     0,     0,   424,  1151,  1152,     0,
       0,     0,     0,     0,     0,  1910,  1153,     0,     0,     0,
     422,     0,     0,     0,     0,     0,     0,     0,     0,   997,
     998,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   423,
       0,     0,     0,     0,   999,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1000,     0,     0,     0,     0,     0,     0,     0,
    1001,     0,     0,   285,     0,     0,     0,     0,     0,   424,
    1151,  1152,     0,     0,     0,     0,     0,     0,     0,  1153
};

static const yytype_int16 yycheck[] =
{
      84,   169,   222,   131,   393,   546,   906,   658,   513,   660,
     694,   441,   870,   841,  1030,   307,  1278,  1102,   723,  1108,
     865,   189,   190,  1208,   246,   626,   194,   195,   196,   197,
     198,   876,   200,   867,   202,   665,  1208,  1208,  1208,   222,
    1208,  1346,  1346,   884,   866,  1122,   598,    17,   465,  1346,
    1715,   271,  1241,     6,  1001,   275,   897,   277,   186,  1346,
     353,  1346,  1023,  1092,  1346,     6,   286,     9,   236,   153,
     238,     6,   957,   578,  1232,  1233,  1234,   245,     6,     9,
      54,  1388,  1389,    49,    49,   253,     6,    30,   271,    28,
    1050,    23,   275,  1178,   277,    13,    94,    84,  1058,   267,
     268,  1201,   270,   286,    56,    48,    56,    70,   276,    22,
     332,    69,   864,   146,    48,    72,   163,   339,   118,    85,
      69,   873,   874,    85,   344,     9,   203,   178,  1282,    21,
    1864,    17,   425,   792,   354,   210,   888,   889,  1238,   123,
     111,   361,   118,   311,  1104,    49,   314,   315,  1177,   317,
     902,   903,   372,   168,    72,   167,   203,    22,   986,    69,
      49,   344,   232,   991,   211,   333,    69,    69,   390,  1269,
      88,   354,    56,   112,   394,   397,   396,  1138,   361,   236,
     119,    56,   350,   834,  1849,  1086,   232,  1264,   410,    65,
      37,  1172,     9,   165,   153,   846,    49,   183,   118,   256,
     957,   183,   264,   496,   183,   219,   290,    62,   196,    11,
     403,   120,   434,   247,  2026,   168,  2028,  1317,   397,   147,
      30,  1049,   444,   210,   392,   232,   367,  1256,   171,   437,
       8,    94,   400,  1322,     9,   886,   283,   457,   184,   244,
    1379,  1141,   115,   445,   446,   295,   448,  1386,   115,   666,
     119,   363,  1004,    69,   120,   873,   808,    35,    32,  1100,
      60,   232,  1574,   110,   210,   104,  1151,  1152,  1153,    71,
    1347,   412,   305,   452,   258,   497,  1161,  1589,   210,    65,
     314,  1033,   316,   451,   272,   903,   170,    87,    88,  1318,
     374,  1368,   514,   377,   502,   957,   115,  1182,   164,  1184,
     412,  1186,   232,   471,   472,  1190,  1191,  1192,  1193,  1194,
    1195,  1196,  1197,   123,    40,  1067,   244,   976,   977,  1419,
     279,  1628,  1150,  1372,   975,  1286,   548,  1634,   223,   224,
    1379,   553,  1521,   501,   247,   219,   275,  1386,   558,   559,
    1300,  1499,   510,  1201,     0,   538,    91,   168,   978,  1378,
     336,   428,    69,   229,   320,   320,  2168,  1109,   320,   232,
     317,   343,  1114,    62,   343,   232,   436,   214,   536,   970,
     971,   336,   119,   435,   449,   543,  1221,   349,   435,   232,
    1238,   244,   247,  1810,  1285,   435,  1367,   161,   516,   436,
     436,   405,  1481,   398,  1151,  1152,  1153,   355,   449,   621,
     598,  1246,   311,   436,  1161,   946,   355,   627,  2142,   577,
     210,  1269,  1497,   232,   582,   232,   320,   585,   418,   587,
     296,   436,   590,   591,   436,  1266,   594,  1184,  1250,   436,
    1092,   320,   345,  1190,  1191,  1192,  1193,   300,   436,  1196,
    1197,   316,   418,   430,   401,   355,   398,   336,  1525,  1201,
     359,   414,   355,   355,   428,  1609,  1208,   398,  1280,  1317,
    1420,   404,   432,   429,   429,   436,   240,   429,   636,   637,
     404,  1356,  1357,  1358,  1359,  1360,  1361,  1362,   398,  1490,
     345,   256,   435,   436,   449,  1237,  1238,   437,   288,  1151,
    1152,  1153,   435,   451,   436,   436,   435,  1508,   418,  1161,
       9,   436,   451,   358,   436,  1327,   436,   399,   436,   395,
     296,   403,   359,   805,  1173,  1177,   436,  1269,   244,  1548,
    1182,   405,  1184,   179,  1186,   429,  1188,   165,  1190,  1191,
    1192,  1193,  1194,  1195,  1196,  1197,   449,   665,   313,   355,
     429,   451,   241,  1559,  1683,  1556,   839,    56,   451,   451,
    1977,  1580,  1304,  1980,   449,   867,  1308,  1309,   476,  1311,
     449,  1419,   979,   436,   232,  1317,   435,   436,  1657,   436,
    1875,  1875,   792,   436,   886,   795,   796,  1839,  1875,   891,
    1181,   326,   802,   436,   232,  1596,   220,  1188,  1875,   442,
    1875,   194,  1144,  1875,  1256,  1555,   435,   436,  1787,  1356,
    1357,  1358,  1359,  1360,  1361,  1362,   305,  2272,   232,    23,
     808,   160,   795,   796,   114,   436,   784,   436,   172,   802,
     183,    69,   191,    30,   371,    31,   241,   443,   444,   445,
     446,   219,   448,   236,  1683,   451,   804,   859,   355,   210,
     241,    28,   183,   214,   389,   957,   866,  1248,   241,   449,
     306,   136,  1741,   256,   353,   136,  1318,  1479,    65,   358,
    1290,   170,     0,   232,  1294,   274,  1522,   887,  2294,  1087,
     239,   891,  1528,   893,   232,   895,   896,   183,   898,   972,
     179,  1365,   191,   274,  1784,  2311,  1786,  1349,   435,   436,
     305,   243,   183,   913,  1356,  1357,  1358,  1359,  1360,  1361,
    1362,   107,  2129,   450,   305,  1123,   926,   341,     9,   929,
     219,   349,   305,  1554,    49,   243,  1378,   236,   295,  1819,
     283,  1732,   942,   232,  1852,   112,   443,   444,   445,   446,
     239,   448,     9,   955,   451,   284,    25,   436,   353,  2046,
     960,   310,   294,   926,  1428,  1706,  1707,  1708,  1349,    50,
      12,  1851,   353,    15,    16,   449,   976,   977,   367,   942,
     353,   264,   400,   891,  1076,   449,   294,  1714,   436,   176,
     324,  1800,  1719,  1720,  1734,   943,  1723,  1724,  1725,    56,
    1727,  1728,   153,  1488,   375,  1862,   344,   871,   436,  1947,
    1948,  1949,  1950,  1394,     9,   336,   210,  1631,     9,     9,
     300,   310,    12,   412,   373,    15,    16,   306,   892,   123,
     894,   198,   436,  1902,  1903,   899,   147,   405,   442,   449,
     363,   306,   229,   342,   908,   306,   232,  1856,   431,  2014,
    1880,  1716,   320,   402,   449,  1587,  1721,   343,   127,  1151,
    1152,  1153,  2014,  2014,  2014,  1529,  2014,   117,   449,  1161,
    1900,  1901,   343,  1981,  1538,   317,   449,  1817,   435,   436,
     254,   194,   195,    27,   373,   436,  1955,  1956,  1088,   412,
    1182,   206,  1184,   442,  1186,   232,  1188,   207,  1190,  1191,
    1192,  1193,  1194,  1195,  1196,  1197,  1548,  1549,   191,   296,
     191,   443,   444,   402,   196,   209,   405,   173,  1909,  1755,
    1756,  1951,   232,   236,  1954,   299,     1,   355,   279,     6,
      99,   270,     9,   232,   191,   443,   444,   420,  1580,   228,
     221,  1143,   191,   256,   233,  1781,  1784,   436,  1786,   232,
    1058,   232,   435,   442,  1790,    28,   239,  2199,   239,   401,
    1024,   429,   219,  1788,   258,   449,   176,   261,  1076,  1960,
     307,  1962,    47,  1173,  2039,   232,     8,     1,   104,  1716,
       4,  1819,   239,   232,  1721,  1133,    61,   151,    82,   232,
     239,   351,   248,   332,   117,    19,   191,   209,   280,  1990,
     191,   236,  1583,    35,    81,    29,   295,   249,   250,  2039,
     449,   254,  1837,  1851,   163,   443,   444,   445,   446,    96,
     448,   256,   232,   451,    99,   267,   268,   310,   371,   310,
    2021,  2022,   302,   372,  2030,   374,   363,   232,    62,   112,
     232,   232,   310,   314,   239,   209,   172,   315,   239,   261,
    1250,   294,   244,   310,   203,  2297,   363,  1349,   184,   249,
     250,   310,   211,  2093,  1356,  1357,  1358,  1359,  1360,  1361,
    1362,   363,  1344,   273,  1716,   275,   153,   267,   268,  1721,
    1280,   198,   164,   449,   236,   412,    11,  1923,   992,   164,
     373,   380,   373,   436,  1826,   259,   288,   261,   369,   370,
      25,    26,   184,   180,   256,   412,  1942,   450,  1216,   184,
     164,   236,   229,  1017,   191,   310,   373,   236,   431,   310,
     412,   402,   435,  1959,   373,   121,   314,  1327,   316,   236,
     184,   256,    57,  2013,   283,   210,  2132,   256,  1338,  1339,
     215,  1551,   191,   417,   221,   402,  1903,   449,   405,   256,
     166,   228,   227,   402,   449,   232,   430,   234,  1800,   442,
     237,   442,   239,  1227,  2000,  2001,  1808,   319,  1799,    94,
      95,   351,    97,  2009,   198,  1338,  1339,  1662,   373,   436,
     105,  1289,   373,   232,  2214,   442,   449,   436,   204,  2219,
     239,   895,   269,   442,   435,   191,   212,   314,  1955,  1956,
     435,   436,  1934,   117,   321,   229,  1182,   402,   449,   913,
    1186,   402,   236,   399,  1856,   291,   292,   403,  1194,  1195,
    1328,  1852,  1406,   148,   149,  1409,   504,   306,   156,   305,
    1414,   509,   160,   310,   159,   132,   232,  2228,  2229,   314,
     315,  2237,   359,   239,   436,   436,  2054,   442,   305,   399,
     442,   442,   327,   403,   329,   251,   449,   281,   410,   351,
     337,   310,  2098,   287,  1928,     2,  1930,   153,   154,     6,
    2106,   443,   444,   445,   446,   351,   448,   159,   438,  1479,
    2118,   163,  2120,   435,   449,  2121,   443,   444,   445,   446,
     314,   448,   314,   166,   316,   181,   373,   321,   455,   351,
     432,   187,   434,    89,    90,   382,   383,   150,   233,   152,
     334,   223,   224,  2149,   310,  2151,   443,   444,   445,   446,
     235,   448,  2158,   436,   373,   402,    11,   113,   455,   336,
     407,  1816,   218,   449,   358,   359,   222,   361,   449,  1631,
      25,    26,  2178,  2179,   260,   369,   262,   150,   425,   152,
    1981,   314,   449,   316,   429,   379,   433,   223,   224,   436,
     229,   230,   449,  2243,   449,   442,   421,   422,   423,   424,
     265,   266,    57,   450,   449,   354,   400,   373,   265,   266,
     376,   377,   443,   444,   445,   446,   449,   448,   229,   230,
     451,   212,    71,   442,   400,   443,   444,   445,   446,   449,
     448,   351,   231,   451,   449,   436,   449,  2139,   178,    94,
      95,  1611,    97,   278,   449,   275,  2252,   390,  1620,    24,
     105,   449,   347,   327,  1716,   449,   367,   351,   210,  1721,
     449,   104,     6,   436,  1636,     9,  2100,   379,  2102,   362,
    1588,    56,   436,    12,    13,    14,   442,    84,  1611,   172,
    1558,    20,   449,   351,  1654,   346,   367,   106,  2089,   278,
     232,   207,   387,   148,   149,   358,   449,   245,  1616,   421,
     422,   423,   424,    67,   159,  1623,   351,   449,  1678,   245,
      23,   272,  1630,   436,   449,   232,  1594,   296,   449,    58,
      83,  1654,    83,  1601,   421,   422,   423,   424,   436,  2231,
     430,   436,  2234,   289,   290,   395,   312,    81,   379,   429,
     398,   436,   230,   863,   196,  1678,   314,   867,  1718,   436,
      25,    26,    96,   873,   449,   359,   398,    55,   878,   879,
    1760,  1761,  1762,  1763,   884,   885,   886,   379,    27,  1687,
     184,   891,  1690,   435,   330,   331,   449,   897,   233,   367,
     351,  2283,   214,   449,   359,  1718,   906,   907,   436,   909,
     223,    66,   221,    68,   450,   432,   341,   453,   454,   210,
     106,   232,   146,   400,   301,    37,    31,   376,    33,   282,
     276,    36,  2314,   442,   153,   154,   398,   395,   452,    27,
     357,    46,   272,   456,   171,   100,   101,   102,   395,   449,
     449,   436,   232,   191,   400,   104,   180,   957,   133,    17,
     435,   199,   181,   169,   184,   452,  1764,   191,   187,   232,
     397,    30,  1770,   443,   444,   445,   446,   124,   448,   452,
     218,   451,   443,   444,   445,   446,   452,   448,   988,   452,
     451,   210,   147,   125,   149,   452,   201,   221,   452,   218,
     452,    56,   157,   222,   228,   398,   127,   452,   232,   452,
     234,   314,   347,   237,  1812,   239,   428,   452,   452,  1871,
     129,   452,   343,  1023,   130,  2196,    98,   265,   266,   394,
     134,  2050,   398,   252,   253,   273,   274,    49,   257,   397,
     135,   279,   280,   395,   392,   269,   397,   176,   267,   140,
    1050,   430,   387,   244,    49,   274,   143,   176,  1058,  1059,
     279,   109,   328,  1821,   111,   375,   111,   360,   173,  1827,
     398,   435,   177,   436,   336,   230,  1076,   160,   297,  1877,
     183,   304,   232,   432,  1882,   190,   310,   131,   168,   244,
     398,   361,  1092,  1891,   398,   206,    49,  1895,   214,   176,
    1100,   436,   119,   275,  1104,   206,   448,  1821,   189,   265,
     441,   229,  1112,   337,   440,  1115,   443,   444,   445,   446,
     214,   448,   336,   398,   451,   393,   364,   443,   444,   445,
     446,   451,   448,   238,   451,   451,   451,  1987,  1138,   368,
     128,  1141,   264,   260,   451,   183,   261,   395,   398,   373,
     326,  1151,  1152,  1153,    49,   135,     8,   176,   382,   383,
     432,  1161,   123,   432,   398,     9,   302,   170,   303,   198,
     263,   399,   324,   339,  1987,   399,   122,  1177,   402,   403,
     285,   107,  1182,   407,  1184,    49,  1186,   429,   172,   429,
    1190,  1191,  1192,  1193,  1194,  1195,  1196,  1197,   280,   138,
     236,   425,   258,   139,   309,   257,   141,   110,   284,   433,
     295,   279,   436,     7,   113,   389,   216,    66,   442,   436,
     153,   153,  2074,   442,   443,   444,   445,   446,   333,   448,
     126,   450,   451,   338,   453,   454,   133,   323,  2088,   323,
      99,   396,    49,   348,  2042,   236,   214,   352,   142,   262,
      81,    93,   145,   259,    90,  2053,  1256,  2055,   217,   199,
     188,   432,   385,    49,   401,    96,  1266,   302,   339,   236,
     236,   144,   176,   171,   288,  2088,   302,   417,    49,  1279,
     137,   436,     6,    22,   338,  2135,  1286,    54,   131,   171,
       1,   181,   204,  1293,   186,     6,  1301,   492,     9,   572,
    1300,    12,    13,    14,   409,   425,  1124,   135,    33,  1332,
    1339,    36,  1312,  1125,   419,   932,  1867,   109,  1318,    44,
      45,    46,   583,   374,  1324,   227,  1820,    49,   153,   220,
     302,   858,   833,   559,  2186,  1663,  1661,   575,  1875,  1553,
    1659,  1341,  2086,  2141,   846,  2069,   540,    58,   945,   180,
    2207,  2201,  1743,   123,  2206,  2207,  1356,  1357,  1358,  1359,
    1360,  1361,  1362,  1824,   808,  1033,   474,  1702,  1038,  1391,
      81,  2221,  1390,  1741,  1777,  1246,  1243,  1521,  1378,  1253,
    1787,  1971,  1259,  1808,  1546,    96,  1076,  1825,  2201,  2187,
    2188,  1328,  1570,  2191,  1100,  1098,  1294,  1841,  1398,  1109,
    2198,   232,   898,   234,  1601,  2024,   237,  1601,  2221,  1680,
    2142,  1832,  2264,  2265,  2029,  2035,  2268,  1088,  2270,     6,
    1420,  1495,     9,  1210,  1583,   958,  2088,  1206,   234,   838,
     155,  1611,   313,  1264,  1041,   592,   965,  2235,   269,  2223,
     799,    57,   153,   154,  2294,    -1,  1434,  1883,   173,   973,
      -1,    -1,    -1,  2305,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  2311,    -1,  2177,    -1,   190,    -1,    -1,  2266,   180,
     181,    -1,    -1,    -1,    -1,    -1,   187,    -1,    -1,    -1,
     191,    -1,  1482,  1483,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,  2296,   210,
      -1,    -1,    -1,    -1,    -1,    92,   337,   218,    -1,    96,
     221,   222,    -1,   238,    -1,    -1,    -1,   228,    -1,    -1,
      -1,   232,  2236,   234,    -1,    -1,   237,    -1,   239,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   252,   253,    -1,    -1,    -1,   257,    -1,  1548,  1549,
      -1,   382,   383,    -1,  1554,  1555,   267,    -1,   269,    -1,
     285,    -1,    -1,   274,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1572,    -1,    -1,    -1,   407,    -1,    -1,     6,
    1580,  2295,     9,    -1,    -1,    -1,   297,    -1,    -1,    -1,
      -1,    -1,    -1,   180,   425,  1595,    -1,    -1,    -1,   310,
    1600,  1601,   433,    30,   191,   436,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   338,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   348,    -1,    -1,   337,    -1,    -1,    -1,
      -1,  1631,    -1,    -1,   221,    -1,    -1,    -1,    65,    -1,
      -1,   228,  1642,    -1,  1644,   232,    -1,   234,    -1,    -1,
     237,    -1,   239,    -1,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   373,    -1,    -1,    -1,    -1,    -1,    -1,    96,
      -1,   382,   383,    -1,    -1,    81,    -1,    -1,    -1,    -1,
      -1,    -1,   269,    -1,   409,    -1,    -1,    -1,    -1,    -1,
      96,   402,    -1,    -1,    -1,    -1,   407,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1706,  1707,  1708,    -1,
      -1,    -1,    -1,    -1,   425,    -1,  1716,    -1,    -1,    -1,
      -1,  1721,   433,   310,    -1,   436,    -1,    -1,    -1,    -1,
      -1,   442,   443,   444,  1734,    -1,    -1,   448,    -1,   450,
      -1,   452,   453,   454,    -1,    -1,    -1,    -1,    -1,    -1,
     337,    -1,    -1,   180,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   191,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   180,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   191,   373,    -1,    -1,    -1,
      -1,    -1,    -1,  1793,   221,   382,   383,    -1,    -1,  1799,
    1800,   228,   229,    -1,    -1,   232,    -1,   234,  1808,    -1,
     237,    -1,   239,    -1,    -1,   402,    -1,  1817,    -1,    -1,
     407,    -1,    -1,    -1,    -1,  1825,   232,    -1,   234,    -1,
      -1,   237,    -1,   239,    -1,    -1,    -1,    -1,   425,    -1,
      -1,    -1,   269,    -1,    -1,    -1,   433,     0,     1,   436,
      -1,    -1,  1852,    -1,    -1,   442,  1856,    -1,    -1,    -1,
      -1,    -1,    -1,   269,    -1,    -1,    -1,    -1,    21,   296,
      -1,    -1,    -1,    -1,    -1,    -1,  1876,    -1,    -1,    -1,
    1880,    34,    -1,   310,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1900,  1901,    -1,    -1,   310,    -1,    -1,    -1,    -1,    -1,
     337,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    -1,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,   337,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   373,    -1,    -1,    -1,
      -1,  1951,    -1,    -1,  1954,   382,   383,    -1,    -1,    -1,
      -1,    -1,   115,    -1,    -1,    -1,    -1,   373,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   402,   382,   383,    -1,   132,
     407,  1981,    -1,   136,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   402,    -1,   425,    -1,
      -1,   407,    -1,    -1,    -1,    -1,   433,    -1,    -1,   436,
      -1,   164,   165,  2013,    -1,   442,    -1,    -1,    -1,   425,
    2020,    -1,    -1,    -1,    -1,    -1,   179,   433,    -1,    -1,
     436,   184,    -1,    -1,    -1,    -1,   442,    -1,    -1,  2039,
      -1,    -1,    -1,    -1,   197,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2056,   210,    -1,    -1,
     213,    -1,    -1,    -1,    -1,    -1,   219,    -1,    -1,    -1,
     223,   224,    -1,    -1,    -1,    -1,    -1,    -1,   231,   232,
      -1,    -1,   235,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  2093,    -1,    -1,   249,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     0,
       1,    -1,     3,    -1,     5,    -1,    -1,    -1,   271,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,
      -1,    -1,    -1,   286,    -1,    -1,    -1,    -1,    -1,    -1,
     293,    -1,   295,    -1,    -1,    -1,    -1,    -1,    -1,   302,
      -1,    -1,  2152,   306,    -1,   308,    -1,    -1,    -1,    -1,
      51,    52,    -1,    -1,    -1,   318,    -1,  2167,    59,    -1,
    2170,    -1,   325,    -1,   327,    -1,    -1,    -1,    -1,    70,
      -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   346,    -1,    86,   349,    -1,    -1,    -1,
    2200,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   362,
      -1,   364,   365,   366,  2214,    -1,    -1,   108,    -1,  2219,
      -1,    -1,    -1,    -1,   115,   116,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   388,    -1,    -1,    -1,    -1,
      -1,   132,    -1,  2243,    -1,   136,    -1,    -1,    -1,    -1,
      -1,    -1,   405,    -1,  2254,   146,    -1,    -1,    -1,    -1,
     413,   414,   415,    -1,    -1,    -1,    -1,   158,    -1,    -1,
      -1,   162,    -1,   426,    -1,    -1,   429,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   175,   438,    -1,    -1,   179,    -1,
      -1,   182,    -1,    -1,   185,   186,   449,    -1,  2298,    -1,
      -1,    -1,   193,    -1,    -1,    -1,    -1,    -1,    -1,   200,
      -1,   202,    -1,    -1,   205,    -1,    -1,    -1,     1,    -1,
       3,    -1,     5,    -1,    -1,    -1,    -1,    10,    -1,    -1,
      81,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,
      -1,   242,    -1,    -1,    -1,   246,    -1,   248,    -1,    -1,
      -1,    -1,    -1,    -1,   255,    -1,    -1,    -1,    51,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   277,    70,    -1,    -1,
      -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   292,    -1,    86,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   306,    -1,    -1,    -1,    -1,
      -1,    -1,   313,   174,    -1,   108,    -1,    -1,    -1,   180,
      -1,   322,   115,   116,    -1,    -1,    -1,    -1,    -1,    -1,
     123,    -1,    -1,    -1,   335,    -1,    -1,    -1,    -1,   340,
      -1,   342,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   350,
      -1,    -1,    -1,   146,    -1,    -1,    -1,    -1,    -1,   360,
      -1,    -1,    -1,    -1,    -1,   158,    -1,    -1,   369,   162,
      -1,   232,    -1,   234,    -1,    -1,   237,   378,    -1,   380,
     381,    -1,   175,   384,    -1,   386,    -1,    -1,    -1,   182,
     391,    -1,   185,   186,    -1,    -1,    -1,    -1,    -1,    -1,
     193,    -1,    -1,    -1,    -1,   406,    -1,   200,   269,   202,
     411,    -1,   205,    -1,    -1,   416,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   427,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   436,     6,    -1,   439,     9,
      -1,    -1,    12,    13,    14,    -1,    -1,    17,   449,   242,
      -1,    21,    -1,   246,    -1,   248,    -1,    -1,    -1,    -1,
      -1,    -1,   255,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   337,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   277,    -1,    -1,    -1,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   292,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     313,   382,   383,    -1,    -1,    -1,    96,    -1,    -1,   322,
      -1,   392,    -1,    -1,    -1,    -1,    -1,     6,    -1,    -1,
       9,    -1,   335,    12,    13,    14,   407,   340,    -1,   342,
      -1,    -1,    -1,    -1,    -1,    -1,   417,   350,    -1,    -1,
      -1,    -1,    -1,    -1,   425,    -1,    -1,   360,    -1,   430,
      -1,    -1,   433,    -1,   435,   436,   369,    -1,    -1,    -1,
      -1,    -1,    -1,   153,   154,   378,    -1,   380,   381,    58,
      -1,   384,    -1,   386,    -1,    -1,    -1,    -1,   391,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     180,   181,    81,   406,    -1,    -1,    -1,   187,   411,    -1,
      -1,   191,    -1,   416,    -1,    -1,    -1,    96,    -1,    -1,
      -1,    -1,    -1,    -1,   427,    -1,    -1,    -1,    -1,    -1,
     210,    -1,    -1,   436,    -1,    -1,   439,    -1,   218,    -1,
      -1,   221,   222,    -1,    -1,    -1,   449,    -1,   228,    -1,
      -1,    -1,   232,    -1,   234,    -1,    -1,   237,    -1,   239,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   252,   253,   153,   154,    -1,   257,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   267,    -1,   269,
      -1,    -1,    -1,    -1,   274,    -1,    -1,    -1,    -1,    -1,
      -1,   180,   181,    -1,    -1,    -1,    -1,    -1,   187,    -1,
      -1,    -1,   191,    -1,    -1,    -1,    -1,   297,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     310,   210,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,
      -1,    -1,   221,   222,    -1,    -1,    -1,    -1,    -1,   228,
      -1,    -1,    -1,   232,    -1,   234,    -1,   337,   237,    -1,
     239,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   252,   253,    -1,    -1,    -1,   257,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   267,    -1,
     269,    -1,    -1,   373,    -1,   274,    -1,    -1,    -1,    -1,
      -1,    -1,   382,   383,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   297,   399,
      -1,    -1,   402,   403,    -1,    -1,    -1,   407,    -1,    -1,
       6,   310,    -1,     9,    -1,     3,    -1,     5,    -1,    -1,
      -1,    -1,    10,    -1,    -1,   425,    -1,    -1,    -1,    -1,
      18,    -1,    -1,   433,    -1,    -1,   436,    -1,   337,    -1,
      -1,    -1,   442,   443,   444,    -1,    -1,    -1,   448,    -1,
     450,    -1,   452,   453,   454,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    59,    -1,    -1,   373,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,   382,   383,    81,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,
      96,    -1,    -1,   402,    -1,    -1,    -1,    -1,   407,    -1,
      -1,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,
     108,    -1,    -1,    -1,    -1,    -1,   425,   115,   116,    -1,
      -1,    -1,    -1,    -1,   433,    -1,    -1,   436,    -1,    -1,
      -1,    -1,    -1,   442,   443,   444,    -1,    -1,    -1,   448,
      -1,   450,    -1,   452,   453,   454,    -1,    -1,   146,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     158,    -1,    -1,    -1,   162,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    -1,     5,   180,    -1,    -1,   175,    10,    -1,
      -1,    -1,    -1,    -1,   182,   191,    18,   185,   186,    -1,
      -1,    -1,    -1,    -1,    -1,   193,    -1,    -1,    -1,    -1,
     206,    -1,   200,    -1,   202,    -1,    -1,   205,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   221,    -1,    -1,    -1,    51,
      52,    -1,   228,    -1,    -1,    -1,   232,    59,   234,    -1,
      -1,   237,    -1,   239,    -1,    -1,    -1,     6,    70,    -1,
       9,    -1,    74,    -1,   242,    -1,    -1,    -1,   246,    -1,
     248,    -1,    -1,    -1,    86,    -1,    -1,   255,    -1,    -1,
      -1,    -1,    -1,   269,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,    -1,    -1,   277,
      49,    -1,    -1,   115,   116,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   292,    -1,    -1,    -1,    -1,     6,
      -1,    -1,     9,    -1,   310,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    -1,   146,   313,    85,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   322,    -1,   158,    96,    -1,    -1,
     162,   337,    -1,    -1,    -1,    -1,    -1,   335,    -1,    -1,
      -1,    -1,   340,   175,   342,    -1,    -1,    -1,    -1,    -1,
     182,    -1,   350,   185,   186,    -1,    -1,    -1,    -1,    -1,
      -1,   193,   360,    -1,    -1,    -1,    -1,   373,   200,    -1,
     202,   369,    -1,   205,    81,    -1,   382,   383,    -1,    -1,
     378,    -1,   380,   381,    -1,    92,   384,    -1,   386,    96,
      -1,    -1,    -1,   391,    -1,    -1,   402,    -1,    -1,    -1,
      -1,   407,    -1,    -1,    -1,    -1,    -1,    -1,   406,    -1,
     242,   180,    -1,   411,   246,    -1,   248,    -1,   416,   425,
      -1,    -1,   191,   255,    -1,    -1,    -1,   433,    -1,   427,
     436,    -1,    -1,    -1,    -1,    -1,   442,    -1,    -1,    -1,
      -1,   439,    -1,    -1,    -1,   277,    -1,    -1,    -1,    -1,
      -1,   449,   221,    -1,    -1,    -1,    -1,    -1,    -1,   228,
     292,    -1,    -1,   232,    -1,   234,    -1,    -1,   237,    -1,
     239,    -1,    -1,   180,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   313,    -1,     6,   191,    -1,     9,    -1,    -1,    -1,
     322,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     269,    -1,    -1,   335,    -1,   274,    -1,    -1,   340,    -1,
     342,    -1,    -1,    -1,   221,    -1,     6,    -1,   350,     9,
      -1,   228,    -1,    -1,    -1,   232,    -1,   234,   360,    -1,
     237,    -1,   239,    -1,    -1,    -1,    -1,   369,    -1,    -1,
      -1,   310,    -1,    -1,    -1,    -1,   378,    -1,   380,   381,
      -1,   320,   384,    -1,   386,    -1,    -1,    -1,    81,   391,
      -1,    -1,   269,    -1,    -1,    -1,    -1,    -1,   337,    -1,
      -1,    -1,    -1,    96,   406,    -1,    -1,    -1,    -1,   411,
      -1,    -1,    -1,    -1,   416,    -1,   109,    -1,    -1,    -1,
       6,    81,    -1,     9,    -1,   427,    -1,    -1,   367,    -1,
      -1,    -1,    92,   310,   373,    -1,    96,   439,    -1,    -1,
      -1,    -1,    -1,   382,   383,    -1,    -1,    -1,     6,    -1,
      -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     337,    -1,    -1,   402,    -1,    -1,    -1,    -1,   407,    -1,
      -1,    -1,    -1,   412,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   425,   180,    -1,    -1,
     429,    -1,    -1,    -1,   433,    81,   373,   436,   191,    -1,
      -1,    -1,    -1,   442,    -1,   382,   383,    -1,    -1,    -1,
      96,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     180,    -1,    -1,    81,    -1,   402,    -1,    -1,   221,    -1,
     407,   191,    -1,    -1,    -1,   228,    -1,    -1,    96,   232,
      -1,   234,    -1,    -1,   237,    -1,   239,    -1,   425,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   433,    -1,    -1,   436,
      -1,   221,    -1,    -1,    -1,   442,    -1,    -1,   228,    -1,
      -1,    -1,   232,    -1,   234,    -1,   269,   237,    -1,   239,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   180,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   191,    -1,     6,    -1,   269,
       9,    -1,    -1,    -1,    -1,    -1,    -1,   310,   176,    -1,
      -1,    -1,   180,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   191,    -1,   221,    -1,    -1,    -1,    -1,
      -1,    -1,   228,    -1,   337,    -1,   232,    -1,   234,    -1,
     310,   237,    -1,   239,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   221,    -1,    -1,    -1,    -1,    -1,    -1,
     228,    -1,    -1,    -1,   232,    -1,   234,   337,    -1,   237,
     373,   239,    81,   269,     6,    -1,    -1,     9,    -1,   382,
     383,    -1,    -1,    -1,    -1,    81,    -1,    96,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   402,
      96,   269,    -1,   373,   407,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   382,   383,   310,    -1,    -1,    -1,     6,    -1,
      -1,     9,   425,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     433,    -1,   402,   436,    -1,    -1,    -1,   407,    -1,   442,
      -1,   337,   310,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    -1,    -1,   425,    -1,     6,    -1,    -1,
       9,    -1,    -1,   433,    96,    -1,   436,    -1,    -1,   337,
      -1,   180,   442,    -1,    -1,    -1,    -1,   373,    -1,    -1,
      -1,    -1,   191,    -1,   180,    -1,   382,   383,    -1,    -1,
      -1,    -1,    -1,    81,    -1,   191,    -1,    -1,    -1,    -1,
      -1,    -1,   398,    -1,    -1,   373,   402,    -1,    96,    -1,
      -1,   407,   221,    -1,   382,   383,    -1,    -1,    -1,   228,
      -1,    -1,    -1,   232,    -1,   234,    -1,    -1,   237,   425,
     239,    -1,    81,    -1,   402,    -1,   232,   433,   234,   407,
     436,   237,    -1,   239,    -1,    -1,   442,    96,   180,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   425,    -1,   191,
     269,    -1,    -1,    -1,    -1,   433,    -1,    -1,   436,    -1,
      81,    -1,    -1,   269,   442,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,   221,
      -1,    -1,   180,    -1,    -1,    -1,   228,    -1,    -1,    -1,
     232,   310,   234,   191,    -1,   237,    -1,   239,    -1,    -1,
      -1,    -1,    -1,    -1,   310,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,    -1,
      -1,   180,    -1,   221,    -1,    -1,    -1,   269,    -1,    -1,
     228,   337,   191,    -1,   232,    -1,   234,    -1,    -1,   237,
      -1,   239,    -1,    -1,    -1,    -1,    -1,    -1,   367,    -1,
      -1,    -1,    -1,   174,   373,    -1,    -1,    -1,    -1,   180,
      -1,    -1,   221,   382,   383,    -1,    -1,   373,   310,   228,
      -1,   269,    -1,   232,    -1,   234,   382,   383,   237,    -1,
     239,    -1,    -1,   402,    -1,    -1,    -1,    -1,   407,    -1,
      -1,    -1,    -1,    -1,    -1,   337,   402,    -1,    -1,    -1,
      -1,   407,    -1,    -1,    -1,    -1,   425,    -1,    -1,    -1,
     269,   232,   310,   234,   433,    -1,   237,   436,    -1,   425,
      -1,    -1,    -1,   442,    -1,    -1,   368,   433,    -1,    -1,
     436,   373,    -1,    -1,    -1,    -1,   442,    -1,    -1,   337,
     382,   383,    -1,    -1,    -1,    -1,    -1,    -1,   269,    -1,
      -1,   310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     402,    -1,    -1,    -1,    -1,   407,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   373,    -1,    -1,   337,    -1,
      -1,    -1,    -1,   425,   382,   383,    -1,    -1,    -1,    -1,
      -1,   433,    -1,    -1,   436,    -1,    -1,    -1,    -1,    -1,
     442,    -1,    -1,    -1,   402,    -1,    -1,    -1,    -1,   407,
      -1,    -1,    -1,    -1,   373,    -1,   337,    -1,    -1,    -1,
      -1,    -1,    -1,   382,   383,    -1,    -1,   425,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   433,    -1,    -1,   436,    -1,
      -1,    -1,    -1,   402,   442,    31,    -1,    33,   407,    -1,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,   382,   383,    -1,    -1,    -1,   425,    -1,    -1,    -1,
      -1,   392,    -1,    -1,   433,    -1,    -1,   436,    -1,    65,
      -1,    -1,    -1,   442,    -1,    -1,   407,    73,    -1,    75,
      76,    77,    78,    79,    80,    -1,   417,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   425,    -1,    -1,    -1,    -1,   430,
      -1,    -1,   433,    -1,   435,   436,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    42,    -1,    -1,    -1,    -1,   115,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    -1,    75,    76,    77,
      78,    79,    80,    -1,    -1,    65,    66,    -1,    -1,   155,
      -1,    -1,    -1,    73,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    -1,    -1,   173,    -1,    -1,
     176,   177,    -1,    -1,    -1,    -1,    -1,   115,    -1,    -1,
      -1,    -1,    -1,    -1,   190,    -1,    -1,    -1,    -1,    -1,
      -1,   197,    -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   213,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   229,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,   238,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   249,    96,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   197,
      -1,    -1,    -1,    -1,    -1,   271,    -1,    -1,   188,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   197,    -1,   285,
     286,    -1,    -1,    -1,    -1,    -1,    -1,   293,    -1,   295,
      -1,    -1,    -1,   213,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   308,   309,    -1,    -1,    -1,    -1,    -1,   229,
     230,   249,    -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   333,   180,   249,
      96,    -1,   338,    -1,   254,    -1,    -1,    -1,    -1,   191,
      -1,    -1,    -1,    -1,    -1,    -1,   352,    -1,   286,    -1,
      -1,   271,    -1,    -1,    -1,    -1,   362,   295,   364,   365,
     366,    -1,    -1,    -1,    -1,    -1,   286,    -1,    -1,   221,
     308,    -1,    -1,   293,    -1,   295,   228,    -1,   298,    -1,
     232,    -1,   234,    -1,    -1,   237,    -1,   239,   308,    -1,
      -1,    -1,   398,    -1,    -1,    -1,    -1,    -1,    81,    -1,
      -1,    -1,    -1,   409,    -1,    -1,    -1,   413,   414,   415,
      -1,    -1,    -1,    96,   180,    -1,    -1,   269,    -1,    -1,
     426,    -1,   428,   429,    -1,   191,   364,   365,   366,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   362,   449,   364,   365,   366,    -1,    -1,    -1,
      -1,   371,    -1,    -1,    -1,   221,    -1,    -1,   310,    -1,
      -1,    -1,   228,    -1,    -1,   385,   232,    -1,   234,    -1,
      -1,   237,    -1,   239,    -1,   413,   414,   415,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   337,    -1,    -1,   408,    -1,
      -1,    -1,    -1,   413,   414,   415,    -1,   180,    -1,    -1,
      -1,    -1,    -1,   269,    -1,    -1,   426,    -1,   191,   429,
     430,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   373,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   449,
     382,   383,    -1,    -1,    -1,    -1,    -1,    -1,   221,    -1,
      -1,    -1,    -1,    -1,   310,   228,    -1,    -1,    -1,   232,
     402,   234,    -1,    -1,   237,   407,   239,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   337,    -1,   425,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   433,    -1,    -1,   436,    -1,   269,    -1,    -1,    -1,
     442,   443,   444,    -1,    -1,    -1,    -1,    -1,    -1,   451,
     452,    -1,    -1,    -1,    -1,    -1,    -1,   373,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   382,   383,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   402,    -1,    -1,    -1,
      -1,   407,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   337,    -1,    -1,    -1,    -1,   425,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   433,    -1,    -1,
     436,    -1,    -1,    -1,    -1,    -1,   442,   443,   444,    -1,
      -1,    -1,    -1,    -1,    -1,   451,   452,    -1,    -1,    -1,
     373,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   382,
     383,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   402,
      -1,    -1,    -1,    -1,   407,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   425,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     433,    -1,    -1,   436,    -1,    -1,    -1,    -1,    -1,   442,
     443,   444,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   452
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   458,   459,     0,   179,   306,   460,   461,   462,   468,
     475,   477,   449,   449,     0,   461,   147,   483,   483,   232,
     307,   478,   478,   117,   463,   469,    27,   479,   479,   449,
      99,   585,   585,   232,   449,   476,    82,   484,   117,   464,
     470,   210,   480,  1138,   351,   166,   204,   212,   538,   449,
     302,   727,   727,   449,    72,   317,   401,   481,   482,   449,
     449,   351,   449,   165,   349,   400,   586,   592,   117,   465,
     471,   475,   132,   474,   482,   305,  1149,   485,   539,   449,
     540,   351,   438,   617,   588,    54,   428,   730,   136,   465,
     472,   483,   478,   270,   332,   372,   374,   486,   487,   491,
     499,   504,   542,   166,   541,    22,   247,   345,   575,   576,
     577,   578,   580,   584,   449,   351,   235,   670,   436,   591,
     593,  1068,   732,   731,   336,   738,   478,   466,   449,   449,
     449,   449,   449,   354,   543,   449,   212,   574,    71,   400,
    1134,   314,   369,   370,   579,   449,   577,   587,   449,   351,
     231,   672,   590,   592,   619,   620,   621,   594,    49,   733,
     734,   735,  1129,   733,   436,   449,   449,   585,   241,   353,
     436,   490,   492,   493,   494,   495,   497,   498,  1149,   178,
     500,   501,   502,   435,   488,   489,   490,  1163,    11,    25,
      26,    57,    94,    95,    97,   105,   148,   149,   159,   233,
     347,   387,   436,   505,   506,   507,   508,   515,   524,   528,
     531,   532,   533,   534,   535,   536,   537,   278,  1115,   542,
     449,   275,  1146,   390,  1157,    24,  1125,   589,   618,   449,
     351,   327,   674,   593,   622,  1109,   595,   734,   367,   412,
     736,   320,   429,   728,   467,   367,  1138,   449,   493,   449,
     494,    62,   358,  1121,     9,   232,   503,   449,   502,   449,
     449,   489,   104,   436,  1080,  1138,  1138,  1080,   379,   362,
    1153,  1138,  1138,  1138,  1138,  1138,  1080,  1138,    56,  1131,
    1138,   449,   507,  1080,   575,   436,  1075,  1076,  1095,    84,
    1132,   172,  1135,   590,   619,   671,   449,   351,   346,   715,
     619,   449,  1109,   223,   224,   623,   626,   627,   633,     1,
      47,    61,    99,   215,   227,   314,   315,   327,   329,   429,
     449,   596,   597,   599,   603,   605,   607,   608,   614,   615,
     616,  1138,  1138,   367,   278,   737,   106,   739,   727,  1138,
     232,  1098,   449,   358,  1138,   207,   207,   232,   449,   245,
     516,  1080,  1080,  1138,  1138,  1138,  1076,    67,  1080,  1080,
    1076,  1138,  1076,   525,   526,  1080,    94,   510,  1080,   544,
     196,   272,  1118,  1076,   581,   582,  1068,  1067,  1068,   619,
     673,   449,   351,   623,   168,   436,   629,   630,   436,   629,
    1132,  1138,   314,   316,  1119,  1119,  1138,  1132,  1138,   245,
    1143,  1138,    23,  1124,   272,   164,   184,    31,   107,  1098,
    1138,   436,   449,   729,   471,  1098,  1076,  1138,   191,   232,
     239,   310,   373,   402,   442,   529,   530,  1101,  1076,   232,
    1076,    23,   210,  1080,  1139,   273,   275,   512,   513,   514,
     509,   545,  1095,   582,   296,   583,  1068,   619,   675,   449,
     624,    83,   625,  1098,   436,  1138,  1124,  1077,  1095,   274,
     375,   604,   232,  1076,  1079,  1098,   430,  1138,   436,   714,
     714,   167,   436,  1098,   740,   741,   136,   473,    56,   437,
     496,   121,   191,   232,   239,   251,   310,   373,   376,   377,
     442,   517,   518,   519,   522,   530,   395,   527,  1098,   513,
     379,  1156,   511,     1,     4,    19,    29,   198,   229,   236,
     281,   287,   314,   321,   334,   359,   361,   369,   400,   449,
     546,   547,   551,   553,   558,   559,   560,   561,   565,   566,
     567,   568,   569,   570,   571,   572,  1121,  1098,   312,   676,
     677,   678,   716,   634,   631,  1138,   429,   663,   398,   602,
    1095,   230,  1142,   398,  1131,   196,  1137,   436,  1138,  1138,
     741,     1,   436,   742,   743,   744,   745,   746,   751,   478,
     519,    17,   395,  1101,  1098,  1138,   513,  1143,   314,   398,
    1161,   359,  1143,  1138,    55,  1130,    37,   110,   214,  1128,
    1140,  1140,  1098,  1163,   379,  1138,   714,   678,   717,     1,
      21,    34,    37,    38,    39,    40,    41,    42,    43,    73,
      75,    76,    77,    78,    79,    80,   115,   197,   213,   232,
     249,   271,   286,   293,   295,   308,   318,   325,   362,   364,
     365,   366,   388,   413,   414,   415,   426,   429,   628,   635,
     636,   637,   639,   640,   641,   642,   643,   645,   657,   658,
     660,   661,   662,   668,   669,  1138,  1154,    27,  1126,   184,
    1139,  1098,    56,   316,   598,   609,  1098,   367,  1155,   232,
     606,  1095,   606,   123,   449,   351,     3,     5,    10,    18,
      51,    52,    59,    70,    74,    86,   108,   115,   116,   146,
     158,   162,   175,   182,   185,   186,   193,   200,   202,   205,
     242,   246,   248,   255,   277,   292,   313,   322,   335,   340,
     342,   350,   360,   369,   378,   380,   381,   384,   386,   391,
     406,   411,   416,   427,   439,   449,   752,   753,   763,   768,
     772,   775,   788,   791,   796,   801,   802,   803,   806,   808,
     815,   819,   821,   836,   839,   841,   843,   846,   848,   854,
     863,   865,   882,   884,   887,   891,   897,   907,   914,   916,
     919,   923,   924,   935,   946,   956,   962,   965,   971,   975,
     977,   979,   981,   984,   995,   996,  1005,  1007,  1008,   449,
     520,   522,  1080,  1138,  1140,   120,   164,   549,  1138,   314,
     321,   566,  1138,  1138,   359,  1138,  1138,  1125,     9,   256,
     313,   573,  1138,   436,   679,   626,   633,   718,   719,   720,
     221,   363,   412,   363,   412,   363,   412,   363,   412,   363,
     412,   432,  1162,   341,  1151,  1098,  1094,  1095,  1095,   210,
     220,   341,   659,  1138,  1138,   164,   184,   219,   405,     9,
      50,   221,   632,  1099,  1100,  1101,   665,   666,  1099,    30,
     610,   611,   612,   613,  1127,  1163,  1131,   176,   601,  1136,
     106,   232,   747,   754,   764,   769,   773,   776,   789,   792,
     797,   804,   807,   809,   816,   820,   822,   837,   840,   842,
    1161,   847,     1,   849,   855,   864,   866,   883,   885,   888,
     892,   898,   908,   915,   917,   920,   925,   936,   947,   957,
     232,   344,   966,   972,   301,   976,   978,   980,   982,   985,
     184,   997,  1135,  1009,   191,   232,   239,   310,   373,   442,
     521,   523,   120,   311,   359,   552,  1138,   114,   300,   548,
      32,   161,   240,   562,  1079,   376,  1076,  1076,   282,  1148,
    1148,   276,  1076,    60,    87,    88,   288,   449,   680,   681,
     685,  1138,   629,   720,   442,   398,   646,   452,  1096,  1097,
     395,   642,  1099,    27,   638,   357,  1117,  1117,  1101,   272,
    1145,  1145,   456,   664,   666,   395,    48,   404,   171,   602,
    1098,   449,   449,   755,  1093,  1094,     6,    81,    92,    96,
     180,   221,   228,   234,   237,   269,   337,   382,   383,   407,
     425,   433,   765,  1062,  1083,  1084,  1093,  1099,  1102,   436,
     770,  1049,  1050,  1051,   232,  1072,  1073,  1074,  1095,   232,
    1091,  1093,  1102,   790,   793,   798,  1063,  1064,  1084,  1068,
     400,   232,   810,  1083,  1090,  1093,   817,  1084,   232,   399,
     403,   823,   824,  1049,   291,   292,   305,   351,   838,     6,
    1081,  1082,  1093,  1093,   844,   133,  1048,  1049,  1081,   684,
    1093,   867,  1093,  1099,  1102,   948,  1095,    92,   886,  1084,
     889,  1084,   893,   174,   232,   899,   902,   903,   904,  1072,
    1091,  1095,  1163,  1068,  1065,  1095,  1068,  1065,     9,   926,
    1066,  1095,   147,   244,   937,   938,   939,   940,   942,   943,
     944,   945,  1069,  1070,  1081,   948,  1068,   963,   109,   967,
     968,  1084,    92,   973,  1083,   684,  1093,  1068,  1093,     8,
      35,   999,   104,  1065,    17,  1076,   115,   232,   550,  1095,
     435,   563,   563,   371,   450,   557,  1076,  1078,  1138,   169,
     682,   683,   682,  1139,   693,   184,   721,  1098,   397,  1160,
     221,   443,   444,   452,  1059,  1061,  1062,  1085,  1093,  1100,
    1102,   452,  1097,  1095,   232,  1130,  1094,  1094,  1101,  1162,
    1099,  1079,  1079,  1127,  1131,   124,   762,    30,   176,   756,
    1127,  1145,   452,  1093,   452,  1103,   452,  1104,  1145,  1118,
     452,   452,   452,   452,   452,   452,   452,   452,  1103,   125,
     767,   398,   766,  1084,   201,  1112,    56,  1052,  1053,   398,
    1118,   428,   777,   232,  1090,  1093,  1068,   127,   799,   153,
     450,   800,  1064,   343,  1116,   314,  1150,  1067,   129,   814,
     756,   421,   422,   423,   424,   130,   818,    49,   206,   777,
      17,   432,   825,   826,   827,   831,  1123,    98,  1145,  1082,
    1071,   394,  1159,   856,  1163,  1093,    91,   326,   389,   868,
     869,   870,   874,   879,   950,  1084,   398,   134,   890,    49,
     163,   203,   211,   283,   894,   903,   135,   900,   417,   430,
     395,   397,   392,   254,   299,  1113,   176,  1010,  1150,  1010,
    1066,   140,   934,   430,   928,  1088,  1093,  1100,   943,   945,
    1081,   398,  1070,   118,   398,   418,   941,   958,   183,   336,
     964,  1129,   206,   968,  1093,   143,   974,   176,   176,   314,
     316,   983,   109,   986,   328,   375,  1000,  1146,  1010,   523,
     119,   435,   557,  1111,  1120,   236,   342,  1138,   554,   555,
    1090,   684,   691,  1098,   626,   694,   722,   111,   647,  1145,
    1061,  1061,  1061,    69,   355,   451,  1060,   443,   444,   445,
     446,   448,   455,  1061,   360,  1152,  1142,  1079,   111,   600,
    1088,    25,    26,    66,    68,   100,   101,   102,   147,   149,
     157,   230,   396,   436,  1070,   435,   759,    65,   229,   296,
     757,   758,   146,   305,  1086,  1094,  1059,  1061,   398,  1061,
    1059,  1105,  1094,  1100,  1102,   436,  1061,  1108,  1061,  1061,
    1107,  1061,  1059,  1059,  1061,  1106,  1061,  1063,  1084,   183,
     336,   771,  1112,    12,    13,    14,    20,    58,   153,   154,
     181,   187,   210,   218,   222,   252,   253,   257,   267,   274,
     279,   297,   442,   443,   444,   445,   446,   448,   450,   451,
     453,   454,  1054,  1055,  1056,  1057,  1058,    12,    13,    14,
      58,   210,   252,   253,   257,   267,   274,   297,   443,   444,
     448,   452,  1054,  1055,  1056,  1057,  1058,  1084,   304,   774,
    1074,   778,   183,   336,   782,   319,   410,   794,   795,  1163,
    1049,   209,   261,  1041,  1042,  1043,  1045,   420,   435,   811,
    1163,   160,  1016,  1017,  1016,  1016,  1016,  1084,  1063,  1084,
      21,   399,   403,   832,   833,  1050,   131,   835,   434,   827,
     829,   432,   828,   824,  1094,   111,   845,  1072,   850,     9,
      12,    15,    16,   249,   250,   267,   268,   857,   861,   168,
    1088,     9,    56,   170,   219,   405,   875,   876,   877,   871,
     869,   952,  1120,  1146,   398,  1081,  1063,  1084,   361,   895,
     748,   749,  1048,   905,   906,  1093,  1072,     8,    35,  1012,
    1150,  1090,   206,   909,   921,  1163,   929,  1127,  1093,   929,
     398,   398,   514,   146,   399,   403,  1084,    49,   214,   959,
    1084,  1084,   367,  1084,  1093,   176,  1063,  1084,  1088,  1129,
     206,   989,  1093,   156,   160,  1001,     9,  1006,  1072,   921,
     119,   554,   275,   556,  1076,   556,   189,   686,   229,   230,
     692,   629,    31,    33,    36,    44,    45,    46,    65,   155,
     173,   176,   177,   190,   229,   238,   271,   285,   309,   333,
     338,   352,   398,   409,   428,   449,   640,   641,   643,   657,
     660,   662,   723,   726,  1146,    28,   112,   198,   644,   649,
     650,   651,   652,   654,  1094,  1100,  1102,   451,  1061,  1061,
    1061,  1061,  1061,  1061,   451,  1061,  1161,  1142,  1146,  1015,
    1017,   441,   440,  1088,  1015,   214,    31,    33,    36,    46,
     173,   177,   190,   238,   285,   309,   333,   338,   348,   352,
     409,   419,   760,   761,  1015,   265,  1144,  1144,  1144,   758,
     757,   232,  1087,  1094,   451,  1093,   455,   451,  1060,   451,
     451,  1060,   451,   451,   451,   451,  1060,   451,   451,   368,
    1021,  1022,  1063,  1082,   336,  1161,   393,  1158,  1158,   398,
    1072,   779,   780,   781,  1129,  1093,  1093,   160,   284,   783,
    1002,  1135,   236,   256,  1021,  1044,  1046,   128,   805,  1045,
      94,   300,   436,  1070,    33,    36,    44,    45,    46,   155,
     173,   190,   238,   285,   338,   348,   409,   812,   813,  1016,
     264,  1018,   260,  1019,   183,  1021,   183,  1123,   395,   834,
     830,   832,   748,  1146,   748,  1161,   326,   858,  1161,   398,
      49,   876,   878,  1088,     9,    56,   219,   405,   872,   873,
    1088,   953,  1121,   196,   280,  1147,   652,  1081,  1021,   183,
    1163,  1067,   135,   901,   750,     8,   176,   909,  1093,   123,
     258,  1031,  1032,  1034,  1041,   236,   256,   432,   123,   432,
     931,   932,  1088,  1087,  1084,  1138,  1041,   969,  1163,  1093,
    1021,   183,   398,     9,   987,   988,  1110,   990,  1093,   969,
     990,   302,  1004,   303,  1011,  1012,  1111,   247,   314,   316,
     564,  1138,   170,   687,  1098,   695,  1138,  1144,   150,   152,
    1138,  1091,  1144,  1098,  1093,  1093,  1076,  1129,   653,   654,
     650,  1140,   648,   649,   451,   399,   667,  1076,  1019,  1015,
    1138,  1138,   118,   418,   761,  1090,  1090,  1090,  1103,  1116,
     451,  1061,  1076,  1103,  1103,  1061,  1103,  1103,  1103,   219,
     405,  1103,  1103,  1023,   263,  1024,  1021,  1082,   153,   279,
     153,   279,   780,   274,   736,    85,   320,   429,   260,   262,
     785,  1003,   784,   324,   339,   748,   748,   811,   811,   811,
     811,  1138,   150,   152,  1138,   118,   418,   813,   748,  1020,
    1063,  1064,  1063,  1064,   833,  1049,   748,  1093,   122,   851,
     429,   859,   860,   861,   107,   862,   429,  1089,  1093,  1099,
    1088,    49,   880,   873,   172,   880,   949,  1138,   280,  1140,
    1063,   573,   896,  1163,   751,   906,  1084,   195,   910,  1163,
    1033,  1035,   138,   918,  1034,   139,   922,   236,  1049,   930,
    1048,   931,   257,   960,  1114,   141,   961,   284,  1026,  1027,
     295,  1116,  1063,  1089,   279,  1088,   110,   991,   389,   993,
    1146,   151,   259,  1013,  1036,  1037,  1039,  1042,     7,  1122,
     564,  1098,   113,   216,   688,    66,    65,    66,   188,   229,
     230,   254,   298,   371,   385,   408,   430,   449,   640,   641,
     643,   645,   657,   660,   662,   696,   697,   699,   700,   701,
     702,   704,   705,   706,   707,   711,   712,   442,  1092,  1093,
    1098,  1138,  1092,  1138,  1160,   436,   655,   656,  1138,  1138,
    1092,  1092,  1047,  1129,  1047,  1021,   451,   748,  1025,  1161,
     153,  1161,   153,  1084,   126,   787,   786,   748,  1016,  1016,
    1016,  1016,  1092,  1092,  1047,  1047,   748,  1021,   323,  1021,
     323,   852,   133,   853,   860,    99,  1133,   880,   880,  1089,
    1012,   203,   428,   954,  1076,   951,  1021,   236,   256,    49,
     236,   214,   911,   194,   236,   256,   431,   748,   748,   927,
     748,   933,   684,  1054,  1055,  1056,  1057,  1058,  1028,   142,
     970,   262,  1029,  1093,  1021,  1021,   988,  1137,    93,   992,
    1137,  1026,   163,   203,   211,   283,   998,  1067,  1038,  1040,
     145,  1014,  1039,   288,  1070,  1092,  1138,    90,   217,   689,
     266,  1144,   199,   713,   265,   266,   710,  1124,   188,   432,
    1138,  1145,  1138,  1093,   702,   254,   294,   708,   709,  1098,
     243,   294,   443,   444,   725,   243,   294,   443,   444,   724,
     656,  1075,  1099,  1092,   748,  1161,  1161,   748,  1064,  1064,
     748,    49,   880,   401,   881,   302,  1067,   183,   283,   955,
    1095,   339,  1084,  1138,   912,  1031,  1042,   236,   236,   748,
     748,   748,  1030,  1093,  1137,  1093,   144,   994,   748,   748,
     229,   230,  1141,  1098,  1138,  1138,   171,   690,  1138,  1139,
    1138,  1048,  1093,   703,  1076,    89,    90,   113,   289,   290,
     330,   331,   698,   176,   288,  1098,   709,  1092,  1092,  1141,
    1021,  1021,  1084,  1084,  1138,  1067,   302,   417,   684,   137,
     913,   748,  1093,  1098,  1098,  1138,  1098,  1098,  1116,  1084,
     902,  1138,  1048,  1098,    49,   902,  1084
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

  case 252:

/* Line 1455 of yacc.c  */
#line 2079 "parser.y"
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

  case 253:

/* Line 1455 of yacc.c  */
#line 2103 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 2104 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 2105 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 2106 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 2113 "parser.y"
    {
	cb_verify (cb_multiple_file_tape_clause, "MULTIPLE FILE TAPE");
  ;}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 2124 "parser.y"
    { ;}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 2135 "parser.y"
    {
	PENDING ("APPLY COMMITMENT-CONTROL");
  ;}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 2160 "parser.y"
    { current_storage = CB_STORAGE_FILE; ;}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 2163 "parser.y"
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

  case 273:

/* Line 1455 of yacc.c  */
#line 2182 "parser.y"
    {
	if ((yyvsp[(3) - (3)]) && (yyvsp[(3) - (3)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(3) - (3)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 2194 "parser.y"
    {
	if ((yyvsp[(2) - (2)]) && (yyvsp[(2) - (2)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(2) - (2)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 2205 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 2206 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 2216 "parser.y"
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

  case 279:

/* Line 1455 of yacc.c  */
#line 2227 "parser.y"
    {
	/* Shut up bison */
	dummy_tree = (yyvsp[(2) - (4)]);
  ;}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 2239 "parser.y"
    {
	if (current_file->global) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->external = 1;
  ;}
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 2246 "parser.y"
    {
	if (current_file->external) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->global = 1;
  ;}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 2269 "parser.y"
    { /* ignored */ ;}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 2279 "parser.y"
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

  case 299:

/* Line 1455 of yacc.c  */
#line 2291 "parser.y"
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

  case 300:

/* Line 1455 of yacc.c  */
#line 2317 "parser.y"
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

  case 302:

/* Line 1455 of yacc.c  */
#line 2341 "parser.y"
    {
	current_file->record_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 2347 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 2348 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 2352 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 2353 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 307:

/* Line 1455 of yacc.c  */
#line 2361 "parser.y"
    {
	cb_verify (cb_label_records_clause, "LABEL RECORDS");
  ;}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 2376 "parser.y"
    {
	cb_verify (cb_value_of_clause, "VALUE OF");
  ;}
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 2380 "parser.y"
    {
	if (!current_file->assign) {
		current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 2396 "parser.y"
    {
	cb_verify (cb_data_records_clause, "DATA RECORDS");
  ;}
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 2407 "parser.y"
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

  case 321:

/* Line 1455 of yacc.c  */
#line 2435 "parser.y"
    {
	current_file->latfoot = (yyvsp[(4) - (5)]);
  ;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 2442 "parser.y"
    {
	current_file->lattop = (yyvsp[(3) - (4)]);
  ;}
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 2449 "parser.y"
    {
	current_file->latbot = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 324:

/* Line 1455 of yacc.c  */
#line 2458 "parser.y"
    { /* ignore */ ;}
    break;

  case 325:

/* Line 1455 of yacc.c  */
#line 2466 "parser.y"
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

  case 326:

/* Line 1455 of yacc.c  */
#line 2484 "parser.y"
    {
	cb_warning (_("file descriptor REPORT IS"));
  ;}
    break;

  case 327:

/* Line 1455 of yacc.c  */
#line 2488 "parser.y"
    {
	cb_warning (_("file descriptor REPORTS ARE"));
  ;}
    break;

  case 329:

/* Line 1455 of yacc.c  */
#line 2499 "parser.y"
    { current_storage = CB_STORAGE_WORKING; ;}
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 2501 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->working_storage =
			cb_field_add (current_program->working_storage, CB_FIELD ((yyvsp[(5) - (5)])));
	}
  ;}
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 2510 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 2511 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 2515 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 334:

/* Line 1455 of yacc.c  */
#line 2521 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	(yyval) = CB_TREE (description_field);
  ;}
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 2541 "parser.y"
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

  case 340:

/* Line 1455 of yacc.c  */
#line 2552 "parser.y"
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

  case 341:

/* Line 1455 of yacc.c  */
#line 2565 "parser.y"
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

  case 342:

/* Line 1455 of yacc.c  */
#line 2576 "parser.y"
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

  case 346:

/* Line 1455 of yacc.c  */
#line 2603 "parser.y"
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

  case 347:

/* Line 1455 of yacc.c  */
#line 2624 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 348:

/* Line 1455 of yacc.c  */
#line 2630 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 349:

/* Line 1455 of yacc.c  */
#line 2636 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 350:

/* Line 1455 of yacc.c  */
#line 2645 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 352:

/* Line 1455 of yacc.c  */
#line 2654 "parser.y"
    {
	current_field->flag_is_global = 1;
	cb_error (_("CONSTANT with GLOBAL clause is not yet supported"));
  ;}
    break;

  case 353:

/* Line 1455 of yacc.c  */
#line 2661 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 354:

/* Line 1455 of yacc.c  */
#line 2662 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 355:

/* Line 1455 of yacc.c  */
#line 2663 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 356:

/* Line 1455 of yacc.c  */
#line 2668 "parser.y"
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

  case 357:

/* Line 1455 of yacc.c  */
#line 2687 "parser.y"
    {
	/* required to check redefines */
	(yyval) = NULL;
  ;}
    break;

  case 358:

/* Line 1455 of yacc.c  */
#line 2693 "parser.y"
    {
	/* required to check redefines */
	(yyval) = cb_true;
  ;}
    break;

  case 374:

/* Line 1455 of yacc.c  */
#line 2722 "parser.y"
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

  case 375:

/* Line 1455 of yacc.c  */
#line 2744 "parser.y"
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

  case 376:

/* Line 1455 of yacc.c  */
#line 2765 "parser.y"
    { current_field->ename = NULL; ;}
    break;

  case 377:

/* Line 1455 of yacc.c  */
#line 2767 "parser.y"
    {
	struct cb_field *x;

	x = CB_FIELD(cb_build_field (cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(2) - (2)]))->data))));
	current_field->ename = x->name;
 ;}
    break;

  case 378:

/* Line 1455 of yacc.c  */
#line 2779 "parser.y"
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

  case 379:

/* Line 1455 of yacc.c  */
#line 2798 "parser.y"
    { current_field->pic = CB_PICTURE ((yyvsp[(1) - (1)])); ;}
    break;

  case 382:

/* Line 1455 of yacc.c  */
#line 2810 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 383:

/* Line 1455 of yacc.c  */
#line 2811 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 384:

/* Line 1455 of yacc.c  */
#line 2812 "parser.y"
    { current_field->usage = CB_USAGE_FLOAT; ;}
    break;

  case 385:

/* Line 1455 of yacc.c  */
#line 2813 "parser.y"
    { current_field->usage = CB_USAGE_DOUBLE; ;}
    break;

  case 386:

/* Line 1455 of yacc.c  */
#line 2814 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 387:

/* Line 1455 of yacc.c  */
#line 2815 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 388:

/* Line 1455 of yacc.c  */
#line 2816 "parser.y"
    { current_field->usage = CB_USAGE_COMP_5; ;}
    break;

  case 389:

/* Line 1455 of yacc.c  */
#line 2817 "parser.y"
    { current_field->usage = CB_USAGE_COMP_X; ;}
    break;

  case 390:

/* Line 1455 of yacc.c  */
#line 2818 "parser.y"
    { current_field->usage = CB_USAGE_DISPLAY; ;}
    break;

  case 391:

/* Line 1455 of yacc.c  */
#line 2819 "parser.y"
    { current_field->usage = CB_USAGE_INDEX; ;}
    break;

  case 392:

/* Line 1455 of yacc.c  */
#line 2820 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 393:

/* Line 1455 of yacc.c  */
#line 2822 "parser.y"
    {
	current_field->usage = CB_USAGE_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 394:

/* Line 1455 of yacc.c  */
#line 2827 "parser.y"
    {
	current_field->usage = CB_USAGE_PROGRAM_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 395:

/* Line 1455 of yacc.c  */
#line 2831 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 396:

/* Line 1455 of yacc.c  */
#line 2832 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 397:

/* Line 1455 of yacc.c  */
#line 2833 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 398:

/* Line 1455 of yacc.c  */
#line 2834 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 399:

/* Line 1455 of yacc.c  */
#line 2835 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 400:

/* Line 1455 of yacc.c  */
#line 2836 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 401:

/* Line 1455 of yacc.c  */
#line 2837 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 402:

/* Line 1455 of yacc.c  */
#line 2838 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_CHAR; ;}
    break;

  case 403:

/* Line 1455 of yacc.c  */
#line 2839 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 404:

/* Line 1455 of yacc.c  */
#line 2840 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 405:

/* Line 1455 of yacc.c  */
#line 2841 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 406:

/* Line 1455 of yacc.c  */
#line 2842 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 407:

/* Line 1455 of yacc.c  */
#line 2843 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 408:

/* Line 1455 of yacc.c  */
#line 2844 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 409:

/* Line 1455 of yacc.c  */
#line 2845 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 410:

/* Line 1455 of yacc.c  */
#line 2846 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 411:

/* Line 1455 of yacc.c  */
#line 2847 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 412:

/* Line 1455 of yacc.c  */
#line 2848 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 413:

/* Line 1455 of yacc.c  */
#line 2850 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  ;}
    break;

  case 414:

/* Line 1455 of yacc.c  */
#line 2858 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_UNSIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_UNSIGNED_LONG;
	}
  ;}
    break;

  case 415:

/* Line 1455 of yacc.c  */
#line 2866 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  ;}
    break;

  case 416:

/* Line 1455 of yacc.c  */
#line 2873 "parser.y"
    { PENDING ("USAGE NATIONAL");;}
    break;

  case 417:

/* Line 1455 of yacc.c  */
#line 2881 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 1;
  ;}
    break;

  case 418:

/* Line 1455 of yacc.c  */
#line 2886 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 0;
  ;}
    break;

  case 422:

/* Line 1455 of yacc.c  */
#line 2903 "parser.y"
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
  ;}
    break;

  case 423:

/* Line 1455 of yacc.c  */
#line 2918 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 424:

/* Line 1455 of yacc.c  */
#line 2919 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 426:

/* Line 1455 of yacc.c  */
#line 2924 "parser.y"
    {
	current_field->occurs_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 429:

/* Line 1455 of yacc.c  */
#line 2933 "parser.y"
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

  case 430:

/* Line 1455 of yacc.c  */
#line 2957 "parser.y"
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
  ;}
    break;

  case 431:

/* Line 1455 of yacc.c  */
#line 2972 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 432:

/* Line 1455 of yacc.c  */
#line 2973 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 433:

/* Line 1455 of yacc.c  */
#line 2977 "parser.y"
    { (yyval) = cb_int (COB_ASCENDING); ;}
    break;

  case 434:

/* Line 1455 of yacc.c  */
#line 2978 "parser.y"
    { (yyval) = cb_int (COB_DESCENDING); ;}
    break;

  case 437:

/* Line 1455 of yacc.c  */
#line 2985 "parser.y"
    {
	current_field->index_list = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 438:

/* Line 1455 of yacc.c  */
#line 2991 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 439:

/* Line 1455 of yacc.c  */
#line 2993 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 440:

/* Line 1455 of yacc.c  */
#line 2998 "parser.y"
    {
	(yyval) = cb_build_index ((yyvsp[(1) - (1)]), cb_int1, 1, current_field);
  ;}
    break;

  case 441:

/* Line 1455 of yacc.c  */
#line 3007 "parser.y"
    { current_field->flag_justified = 1; ;}
    break;

  case 442:

/* Line 1455 of yacc.c  */
#line 3014 "parser.y"
    { current_field->flag_synchronized = 1; ;}
    break;

  case 446:

/* Line 1455 of yacc.c  */
#line 3026 "parser.y"
    { current_field->flag_blank_zero = 1; ;}
    break;

  case 447:

/* Line 1455 of yacc.c  */
#line 3034 "parser.y"
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

  case 448:

/* Line 1455 of yacc.c  */
#line 3058 "parser.y"
    { current_field->values = cb_list_init ((yyvsp[(3) - (3)])); ;}
    break;

  case 449:

/* Line 1455 of yacc.c  */
#line 3062 "parser.y"
    { current_field->values = (yyvsp[(3) - (3)]); ;}
    break;

  case 451:

/* Line 1455 of yacc.c  */
#line 3067 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 452:

/* Line 1455 of yacc.c  */
#line 3068 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 453:

/* Line 1455 of yacc.c  */
#line 3072 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 454:

/* Line 1455 of yacc.c  */
#line 3073 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 456:

/* Line 1455 of yacc.c  */
#line 3078 "parser.y"
    {
	if (current_field->level != 88) {
		cb_error (_("FALSE clause only allowed for 88 level"));
	}
	current_field->false_88 = cb_list_init ((yyvsp[(3) - (3)]));
  ;}
    break;

  case 457:

/* Line 1455 of yacc.c  */
#line 3091 "parser.y"
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

  case 458:

/* Line 1455 of yacc.c  */
#line 3103 "parser.y"
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

  case 459:

/* Line 1455 of yacc.c  */
#line 3123 "parser.y"
    {
	if (current_field->flag_item_based) {
		cb_error (_("BASED and ANY LENGTH are mutually exclusive"));
	} else {
		current_field->flag_any_length = 1;
	}
  ;}
    break;

  case 461:

/* Line 1455 of yacc.c  */
#line 3138 "parser.y"
    {
	current_storage = CB_STORAGE_LOCAL;
	if (current_program->nested_level) {
		cb_error (_("LOCAL-STORAGE not allowed in nested programs"));
	}
  ;}
    break;

  case 462:

/* Line 1455 of yacc.c  */
#line 3145 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->local_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 464:

/* Line 1455 of yacc.c  */
#line 3158 "parser.y"
    { current_storage = CB_STORAGE_LINKAGE; ;}
    break;

  case 465:

/* Line 1455 of yacc.c  */
#line 3160 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->linkage_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 467:

/* Line 1455 of yacc.c  */
#line 3173 "parser.y"
    {
	cb_error (_("REPORT SECTION not supported"));
	current_storage = CB_STORAGE_REPORT;
  ;}
    break;

  case 474:

/* Line 1455 of yacc.c  */
#line 3206 "parser.y"
    {
	cb_warning (_("Report description using defaults"));
  ;}
    break;

  case 476:

/* Line 1455 of yacc.c  */
#line 3214 "parser.y"
    {
	cb_error (_("GLOBAL is not allowed with RD"));
  ;}
    break;

  case 485:

/* Line 1455 of yacc.c  */
#line 3237 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 486:

/* Line 1455 of yacc.c  */
#line 3238 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 508:

/* Line 1455 of yacc.c  */
#line 3294 "parser.y"
    { cb_warning (_("looking for Report line TYPE")); ;}
    break;

  case 559:

/* Line 1455 of yacc.c  */
#line 3399 "parser.y"
    { current_storage = CB_STORAGE_SCREEN; ;}
    break;

  case 560:

/* Line 1455 of yacc.c  */
#line 3400 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 561:

/* Line 1455 of yacc.c  */
#line 3406 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	current_program->screen_storage = description_field;
	current_program->flag_screen = 1;
  ;}
    break;

  case 567:

/* Line 1455 of yacc.c  */
#line 3430 "parser.y"
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

  case 568:

/* Line 1455 of yacc.c  */
#line 3446 "parser.y"
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

  case 571:

/* Line 1455 of yacc.c  */
#line 3470 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 572:

/* Line 1455 of yacc.c  */
#line 3471 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 573:

/* Line 1455 of yacc.c  */
#line 3472 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BELL; ;}
    break;

  case 574:

/* Line 1455 of yacc.c  */
#line 3473 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLINK; ;}
    break;

  case 575:

/* Line 1455 of yacc.c  */
#line 3474 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 576:

/* Line 1455 of yacc.c  */
#line 3475 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 577:

/* Line 1455 of yacc.c  */
#line 3476 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 578:

/* Line 1455 of yacc.c  */
#line 3477 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 579:

/* Line 1455 of yacc.c  */
#line 3478 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REVERSE; ;}
    break;

  case 580:

/* Line 1455 of yacc.c  */
#line 3479 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 581:

/* Line 1455 of yacc.c  */
#line 3480 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_OVERLINE; ;}
    break;

  case 582:

/* Line 1455 of yacc.c  */
#line 3481 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_AUTO; ;}
    break;

  case 583:

/* Line 1455 of yacc.c  */
#line 3482 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_SECURE; ;}
    break;

  case 584:

/* Line 1455 of yacc.c  */
#line 3483 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REQUIRED; ;}
    break;

  case 585:

/* Line 1455 of yacc.c  */
#line 3484 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_FULL; ;}
    break;

  case 586:

/* Line 1455 of yacc.c  */
#line 3485 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_PROMPT; ;}
    break;

  case 587:

/* Line 1455 of yacc.c  */
#line 3487 "parser.y"
    {
	current_field->screen_line = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 588:

/* Line 1455 of yacc.c  */
#line 3491 "parser.y"
    {
	current_field->screen_column = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 589:

/* Line 1455 of yacc.c  */
#line 3495 "parser.y"
    {
	current_field->screen_foreg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 590:

/* Line 1455 of yacc.c  */
#line 3499 "parser.y"
    {
	current_field->screen_backg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 598:

/* Line 1455 of yacc.c  */
#line 3510 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 599:

/* Line 1455 of yacc.c  */
#line 3517 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 600:

/* Line 1455 of yacc.c  */
#line 3521 "parser.y"
    {
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 601:

/* Line 1455 of yacc.c  */
#line 3530 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 602:

/* Line 1455 of yacc.c  */
#line 3534 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 603:

/* Line 1455 of yacc.c  */
#line 3538 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 604:

/* Line 1455 of yacc.c  */
#line 3542 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 605:

/* Line 1455 of yacc.c  */
#line 3546 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 606:

/* Line 1455 of yacc.c  */
#line 3553 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 607:

/* Line 1455 of yacc.c  */
#line 3557 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 608:

/* Line 1455 of yacc.c  */
#line 3561 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 609:

/* Line 1455 of yacc.c  */
#line 3565 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 610:

/* Line 1455 of yacc.c  */
#line 3569 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 611:

/* Line 1455 of yacc.c  */
#line 3577 "parser.y"
    {
	current_field->occurs_max = cb_get_int ((yyvsp[(2) - (3)]));
	current_field->occurs_min = current_field->occurs_max;
	current_field->indexes++;
	current_field->flag_occurs = 1;
  ;}
    break;

  case 613:

/* Line 1455 of yacc.c  */
#line 3591 "parser.y"
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

  case 614:

/* Line 1455 of yacc.c  */
#line 3601 "parser.y"
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

  case 615:

/* Line 1455 of yacc.c  */
#line 3611 "parser.y"
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

  case 616:

/* Line 1455 of yacc.c  */
#line 3628 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 617:

/* Line 1455 of yacc.c  */
#line 3630 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 618:

/* Line 1455 of yacc.c  */
#line 3634 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 619:

/* Line 1455 of yacc.c  */
#line 3636 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	current_program->flag_chained = 1;
  ;}
    break;

  case 620:

/* Line 1455 of yacc.c  */
#line 3640 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 621:

/* Line 1455 of yacc.c  */
#line 3644 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 622:

/* Line 1455 of yacc.c  */
#line 3646 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 623:

/* Line 1455 of yacc.c  */
#line 3651 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), cb_build_identifier ((yyvsp[(4) - (4)])));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 625:

/* Line 1455 of yacc.c  */
#line 3660 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 626:

/* Line 1455 of yacc.c  */
#line 3664 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 628:

/* Line 1455 of yacc.c  */
#line 3676 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_AUTO;
	}
  ;}
    break;

  case 629:

/* Line 1455 of yacc.c  */
#line 3684 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_4;
	}
  ;}
    break;

  case 630:

/* Line 1455 of yacc.c  */
#line 3692 "parser.y"
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

  case 631:

/* Line 1455 of yacc.c  */
#line 3721 "parser.y"
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

  case 633:

/* Line 1455 of yacc.c  */
#line 3754 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OPTIONAL only allowed for BY REFERENCE items"));
	}
  ;}
    break;

  case 634:

/* Line 1455 of yacc.c  */
#line 3763 "parser.y"
    {
	if (current_program->prog_type == CB_FUNCTION_TYPE) {
		cb_error (_("RETURNING clause is required for a FUNCTION"));
	}
  ;}
    break;

  case 635:

/* Line 1455 of yacc.c  */
#line 3769 "parser.y"
    {
	if (cb_ref ((yyvsp[(2) - (2)])) != cb_error_node) {
		current_program->returning = (yyvsp[(2) - (2)]);
		if (cb_field ((yyvsp[(2) - (2)]))->storage != CB_STORAGE_LINKAGE) {
			cb_error (_("RETURNING item is not defined in LINKAGE SECTION"));
		}
	}
  ;}
    break;

  case 637:

/* Line 1455 of yacc.c  */
#line 3780 "parser.y"
    { in_declaratives = 1; ;}
    break;

  case 638:

/* Line 1455 of yacc.c  */
#line 3783 "parser.y"
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

  case 644:

/* Line 1455 of yacc.c  */
#line 3816 "parser.y"
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

  case 645:

/* Line 1455 of yacc.c  */
#line 3832 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 646:

/* Line 1455 of yacc.c  */
#line 3844 "parser.y"
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

  case 647:

/* Line 1455 of yacc.c  */
#line 3875 "parser.y"
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

  case 648:

/* Line 1455 of yacc.c  */
#line 3912 "parser.y"
    {
	non_const_word = 0;
	check_unreached = 0;
	if ((yyvsp[(1) - (1)]) != cb_error_node) {
		cb_error_x ((yyvsp[(1) - (1)]), _("Unknown statement '%s'"), CB_NAME ((yyvsp[(1) - (1)])));
	}
	YYERROR;
  ;}
    break;

  case 649:

/* Line 1455 of yacc.c  */
#line 3923 "parser.y"
    { (yyval) = cb_build_section_name ((yyvsp[(1) - (1)]), 0); ;}
    break;

  case 651:

/* Line 1455 of yacc.c  */
#line 3927 "parser.y"
    { /* ignore */ ;}
    break;

  case 652:

/* Line 1455 of yacc.c  */
#line 3936 "parser.y"
    {
	(yyval) = current_program->exec_list;
	current_program->exec_list = NULL;
  ;}
    break;

  case 653:

/* Line 1455 of yacc.c  */
#line 3940 "parser.y"
    {
	(yyval) = CB_TREE (current_statement);
	current_statement = NULL;
  ;}
    break;

  case 654:

/* Line 1455 of yacc.c  */
#line 3945 "parser.y"
    {
	(yyval) = cb_list_reverse (current_program->exec_list);
	current_program->exec_list = (yyvsp[(1) - (3)]);
	current_statement = CB_STATEMENT ((yyvsp[(2) - (3)]));
  ;}
    break;

  case 655:

/* Line 1455 of yacc.c  */
#line 3953 "parser.y"
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

  case 706:

/* Line 1455 of yacc.c  */
#line 4025 "parser.y"
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

  case 707:

/* Line 1455 of yacc.c  */
#line 4047 "parser.y"
    {
	BEGIN_STATEMENT ("ACCEPT", TERM_ACCEPT);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 709:

/* Line 1455 of yacc.c  */
#line 4060 "parser.y"
    {
	cb_emit_accept ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 710:

/* Line 1455 of yacc.c  */
#line 4064 "parser.y"
    {
	PENDING ("ACCEPT .. FROM ESCAPE KEY");
  ;}
    break;

  case 711:

/* Line 1455 of yacc.c  */
#line 4068 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 0);
  ;}
    break;

  case 712:

/* Line 1455 of yacc.c  */
#line 4072 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 1);
  ;}
    break;

  case 713:

/* Line 1455 of yacc.c  */
#line 4076 "parser.y"
    {
	cb_emit_accept_date ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 714:

/* Line 1455 of yacc.c  */
#line 4080 "parser.y"
    {
	cb_emit_accept_date_yyyymmdd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 715:

/* Line 1455 of yacc.c  */
#line 4084 "parser.y"
    {
	cb_emit_accept_day ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 716:

/* Line 1455 of yacc.c  */
#line 4088 "parser.y"
    {
	cb_emit_accept_day_yyyyddd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 717:

/* Line 1455 of yacc.c  */
#line 4092 "parser.y"
    {
	cb_emit_accept_day_of_week ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 718:

/* Line 1455 of yacc.c  */
#line 4096 "parser.y"
    {
	cb_emit_accept_time ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 719:

/* Line 1455 of yacc.c  */
#line 4100 "parser.y"
    {
	cb_emit_accept_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 720:

/* Line 1455 of yacc.c  */
#line 4104 "parser.y"
    {
	cb_emit_accept_environment ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 721:

/* Line 1455 of yacc.c  */
#line 4108 "parser.y"
    { 
	cb_emit_get_environment ((yyvsp[(4) - (5)]), (yyvsp[(1) - (5)]));
  ;}
    break;

  case 722:

/* Line 1455 of yacc.c  */
#line 4112 "parser.y"
    {
	cb_emit_accept_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 723:

/* Line 1455 of yacc.c  */
#line 4116 "parser.y"
    {
	cb_emit_accept_arg_value ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 724:

/* Line 1455 of yacc.c  */
#line 4120 "parser.y"
    {
	cb_emit_accept_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 725:

/* Line 1455 of yacc.c  */
#line 4124 "parser.y"
    {
	cb_emit_accept_name ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 726:

/* Line 1455 of yacc.c  */
#line 4130 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 727:

/* Line 1455 of yacc.c  */
#line 4131 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 728:

/* Line 1455 of yacc.c  */
#line 4132 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); ;}
    break;

  case 729:

/* Line 1455 of yacc.c  */
#line 4133 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), NULL); ;}
    break;

  case 730:

/* Line 1455 of yacc.c  */
#line 4134 "parser.y"
    { (yyval) = cb_build_pair (NULL, (yyvsp[(2) - (2)])); ;}
    break;

  case 731:

/* Line 1455 of yacc.c  */
#line 4135 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 732:

/* Line 1455 of yacc.c  */
#line 4139 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 733:

/* Line 1455 of yacc.c  */
#line 4143 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 734:

/* Line 1455 of yacc.c  */
#line 4144 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 739:

/* Line 1455 of yacc.c  */
#line 4157 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 740:

/* Line 1455 of yacc.c  */
#line 4158 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 741:

/* Line 1455 of yacc.c  */
#line 4159 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 742:

/* Line 1455 of yacc.c  */
#line 4160 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 743:

/* Line 1455 of yacc.c  */
#line 4161 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 744:

/* Line 1455 of yacc.c  */
#line 4162 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 745:

/* Line 1455 of yacc.c  */
#line 4163 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 746:

/* Line 1455 of yacc.c  */
#line 4165 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 747:

/* Line 1455 of yacc.c  */
#line 4169 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 748:

/* Line 1455 of yacc.c  */
#line 4173 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 749:

/* Line 1455 of yacc.c  */
#line 4177 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 750:

/* Line 1455 of yacc.c  */
#line 4181 "parser.y"
    { dispattrs |= COB_SCREEN_AUTO; ;}
    break;

  case 751:

/* Line 1455 of yacc.c  */
#line 4182 "parser.y"
    { dispattrs |= COB_SCREEN_FULL; ;}
    break;

  case 752:

/* Line 1455 of yacc.c  */
#line 4183 "parser.y"
    { dispattrs |= COB_SCREEN_REQUIRED; ;}
    break;

  case 753:

/* Line 1455 of yacc.c  */
#line 4184 "parser.y"
    { dispattrs |= COB_SCREEN_SECURE; ;}
    break;

  case 754:

/* Line 1455 of yacc.c  */
#line 4185 "parser.y"
    { dispattrs |= COB_SCREEN_UPDATE; ;}
    break;

  case 755:

/* Line 1455 of yacc.c  */
#line 4186 "parser.y"
    { dispattrs |= COB_SCREEN_PROMPT; ;}
    break;

  case 756:

/* Line 1455 of yacc.c  */
#line 4190 "parser.y"
    { terminator_warning (TERM_ACCEPT); ;}
    break;

  case 757:

/* Line 1455 of yacc.c  */
#line 4191 "parser.y"
    { terminator_clear (TERM_ACCEPT); ;}
    break;

  case 758:

/* Line 1455 of yacc.c  */
#line 4200 "parser.y"
    { BEGIN_STATEMENT ("ADD", TERM_ADD); ;}
    break;

  case 760:

/* Line 1455 of yacc.c  */
#line 4207 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '+', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 761:

/* Line 1455 of yacc.c  */
#line 4211 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(4) - (5)]), 0, cb_build_binary_list ((yyvsp[(1) - (5)]), '+'));
  ;}
    break;

  case 762:

/* Line 1455 of yacc.c  */
#line 4215 "parser.y"
    {
	cb_emit_corresponding (cb_build_add, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 764:

/* Line 1455 of yacc.c  */
#line 4221 "parser.y"
    { cb_list_add ((yyvsp[(0) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 765:

/* Line 1455 of yacc.c  */
#line 4225 "parser.y"
    { terminator_warning (TERM_ADD); ;}
    break;

  case 766:

/* Line 1455 of yacc.c  */
#line 4226 "parser.y"
    { terminator_clear (TERM_ADD); ;}
    break;

  case 767:

/* Line 1455 of yacc.c  */
#line 4235 "parser.y"
    { BEGIN_STATEMENT ("ALLOCATE", 0); ;}
    break;

  case 769:

/* Line 1455 of yacc.c  */
#line 4241 "parser.y"
    {
	cb_emit_allocate ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), NULL, (yyvsp[(2) - (3)]));
  ;}
    break;

  case 770:

/* Line 1455 of yacc.c  */
#line 4245 "parser.y"
    {
	cb_emit_allocate (NULL, (yyvsp[(5) - (5)]), (yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]));
  ;}
    break;

  case 771:

/* Line 1455 of yacc.c  */
#line 4251 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 772:

/* Line 1455 of yacc.c  */
#line 4252 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 773:

/* Line 1455 of yacc.c  */
#line 4262 "parser.y"
    {
	cb_error (_("ALTER statement is obsolete and unsupported"));
  ;}
    break;

  case 778:

/* Line 1455 of yacc.c  */
#line 4280 "parser.y"
    { BEGIN_STATEMENT ("CALL", TERM_CALL); ;}
    break;

  case 779:

/* Line 1455 of yacc.c  */
#line 4284 "parser.y"
    {
	cb_emit_call ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 780:

/* Line 1455 of yacc.c  */
#line 4290 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 781:

/* Line 1455 of yacc.c  */
#line 4292 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 782:

/* Line 1455 of yacc.c  */
#line 4296 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 783:

/* Line 1455 of yacc.c  */
#line 4300 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 784:

/* Line 1455 of yacc.c  */
#line 4302 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 785:

/* Line 1455 of yacc.c  */
#line 4307 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OMITTED only allowed with BY REFERENCE"));
	}
	(yyval) = cb_build_pair (cb_int (call_mode), cb_null);
  ;}
    break;

  case 786:

/* Line 1455 of yacc.c  */
#line 4314 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), (yyvsp[(3) - (3)]));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 788:

/* Line 1455 of yacc.c  */
#line 4323 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 789:

/* Line 1455 of yacc.c  */
#line 4327 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY CONTENT not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_CONTENT;
	}
  ;}
    break;

  case 790:

/* Line 1455 of yacc.c  */
#line 4335 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 791:

/* Line 1455 of yacc.c  */
#line 4345 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 792:

/* Line 1455 of yacc.c  */
#line 4346 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 793:

/* Line 1455 of yacc.c  */
#line 4347 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 794:

/* Line 1455 of yacc.c  */
#line 4352 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 795:

/* Line 1455 of yacc.c  */
#line 4356 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 796:

/* Line 1455 of yacc.c  */
#line 4360 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 797:

/* Line 1455 of yacc.c  */
#line 4367 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 798:

/* Line 1455 of yacc.c  */
#line 4371 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 799:

/* Line 1455 of yacc.c  */
#line 4375 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 800:

/* Line 1455 of yacc.c  */
#line 4381 "parser.y"
    { terminator_warning (TERM_CALL); ;}
    break;

  case 801:

/* Line 1455 of yacc.c  */
#line 4382 "parser.y"
    { terminator_clear (TERM_CALL); ;}
    break;

  case 802:

/* Line 1455 of yacc.c  */
#line 4391 "parser.y"
    { BEGIN_STATEMENT ("CANCEL", 0); ;}
    break;

  case 805:

/* Line 1455 of yacc.c  */
#line 4397 "parser.y"
    {
	cb_emit_cancel ((yyvsp[(2) - (2)]));
  ;}
    break;

  case 806:

/* Line 1455 of yacc.c  */
#line 4408 "parser.y"
    { BEGIN_STATEMENT ("CLOSE", 0); ;}
    break;

  case 809:

/* Line 1455 of yacc.c  */
#line 4415 "parser.y"
    {
	BEGIN_IMPLICIT_STATEMENT ((yyvsp[(2) - (3)]));
	if ((yyvsp[(2) - (3)]) != cb_error_node) {
		cb_emit_close ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
	}
  ;}
    break;

  case 810:

/* Line 1455 of yacc.c  */
#line 4424 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NORMAL); ;}
    break;

  case 811:

/* Line 1455 of yacc.c  */
#line 4425 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT); ;}
    break;

  case 812:

/* Line 1455 of yacc.c  */
#line 4426 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT_REMOVAL); ;}
    break;

  case 813:

/* Line 1455 of yacc.c  */
#line 4427 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NO_REWIND); ;}
    break;

  case 814:

/* Line 1455 of yacc.c  */
#line 4428 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_LOCK); ;}
    break;

  case 817:

/* Line 1455 of yacc.c  */
#line 4439 "parser.y"
    { BEGIN_STATEMENT ("COMPUTE", TERM_COMPUTE); ;}
    break;

  case 819:

/* Line 1455 of yacc.c  */
#line 4446 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(1) - (4)]), 0, (yyvsp[(3) - (4)]));
  ;}
    break;

  case 820:

/* Line 1455 of yacc.c  */
#line 4452 "parser.y"
    { terminator_warning (TERM_COMPUTE); ;}
    break;

  case 821:

/* Line 1455 of yacc.c  */
#line 4453 "parser.y"
    { terminator_clear (TERM_COMPUTE); ;}
    break;

  case 824:

/* Line 1455 of yacc.c  */
#line 4464 "parser.y"
    {
	BEGIN_STATEMENT ("COMMIT", 0);
	cb_emit_commit ();
  ;}
    break;

  case 825:

/* Line 1455 of yacc.c  */
#line 4477 "parser.y"
    {
	BEGIN_STATEMENT ("CONTINUE", 0);
	cb_emit_continue ();
  ;}
    break;

  case 826:

/* Line 1455 of yacc.c  */
#line 4489 "parser.y"
    { BEGIN_STATEMENT ("DELETE", TERM_DELETE); ;}
    break;

  case 827:

/* Line 1455 of yacc.c  */
#line 4492 "parser.y"
    {
	if ((yyvsp[(3) - (6)]) != cb_error_node) {
		cb_emit_delete ((yyvsp[(3) - (6)]));
	}
  ;}
    break;

  case 828:

/* Line 1455 of yacc.c  */
#line 4500 "parser.y"
    { terminator_warning (TERM_DELETE); ;}
    break;

  case 829:

/* Line 1455 of yacc.c  */
#line 4501 "parser.y"
    { terminator_clear (TERM_DELETE); ;}
    break;

  case 830:

/* Line 1455 of yacc.c  */
#line 4510 "parser.y"
    { BEGIN_STATEMENT ("DELETE-FILE", 0); ;}
    break;

  case 831:

/* Line 1455 of yacc.c  */
#line 4512 "parser.y"
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

  case 832:

/* Line 1455 of yacc.c  */
#line 4530 "parser.y"
    {
	BEGIN_STATEMENT ("DISPLAY", TERM_DISPLAY);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 834:

/* Line 1455 of yacc.c  */
#line 4543 "parser.y"
    {
	cb_emit_env_name ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 835:

/* Line 1455 of yacc.c  */
#line 4547 "parser.y"
    {
	cb_emit_env_value ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 836:

/* Line 1455 of yacc.c  */
#line 4551 "parser.y"
    {
	cb_emit_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 837:

/* Line 1455 of yacc.c  */
#line 4555 "parser.y"
    {
	cb_emit_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 838:

/* Line 1455 of yacc.c  */
#line 4559 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (4)]), cb_int0, (yyvsp[(3) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 839:

/* Line 1455 of yacc.c  */
#line 4563 "parser.y"
    {
	cb_emit_display_mnemonic ((yyvsp[(1) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 840:

/* Line 1455 of yacc.c  */
#line 4567 "parser.y"
    {
	cb_tree word = cb_build_display_upon_direct ((yyvsp[(4) - (6)]));
	cb_emit_display ((yyvsp[(1) - (6)]), word, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 841:

/* Line 1455 of yacc.c  */
#line 4572 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 842:

/* Line 1455 of yacc.c  */
#line 4576 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 843:

/* Line 1455 of yacc.c  */
#line 4582 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 844:

/* Line 1455 of yacc.c  */
#line 4583 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 845:

/* Line 1455 of yacc.c  */
#line 4584 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 848:

/* Line 1455 of yacc.c  */
#line 4594 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 849:

/* Line 1455 of yacc.c  */
#line 4595 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 850:

/* Line 1455 of yacc.c  */
#line 4596 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 851:

/* Line 1455 of yacc.c  */
#line 4597 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 852:

/* Line 1455 of yacc.c  */
#line 4598 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 853:

/* Line 1455 of yacc.c  */
#line 4599 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 854:

/* Line 1455 of yacc.c  */
#line 4600 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 855:

/* Line 1455 of yacc.c  */
#line 4601 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 856:

/* Line 1455 of yacc.c  */
#line 4602 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 857:

/* Line 1455 of yacc.c  */
#line 4604 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 858:

/* Line 1455 of yacc.c  */
#line 4608 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 859:

/* Line 1455 of yacc.c  */
#line 4612 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 860:

/* Line 1455 of yacc.c  */
#line 4616 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 861:

/* Line 1455 of yacc.c  */
#line 4620 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 862:

/* Line 1455 of yacc.c  */
#line 4621 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 863:

/* Line 1455 of yacc.c  */
#line 4625 "parser.y"
    { terminator_warning (TERM_DISPLAY); ;}
    break;

  case 864:

/* Line 1455 of yacc.c  */
#line 4626 "parser.y"
    { terminator_clear (TERM_DISPLAY); ;}
    break;

  case 865:

/* Line 1455 of yacc.c  */
#line 4635 "parser.y"
    { BEGIN_STATEMENT ("DIVIDE", TERM_DIVIDE); ;}
    break;

  case 867:

/* Line 1455 of yacc.c  */
#line 4642 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '/', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 868:

/* Line 1455 of yacc.c  */
#line 4646 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(3) - (6)]), '/', (yyvsp[(1) - (6)])));
  ;}
    break;

  case 869:

/* Line 1455 of yacc.c  */
#line 4650 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '/', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 870:

/* Line 1455 of yacc.c  */
#line 4654 "parser.y"
    {
	cb_emit_divide ((yyvsp[(3) - (8)]), (yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 871:

/* Line 1455 of yacc.c  */
#line 4658 "parser.y"
    {
	cb_emit_divide ((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 872:

/* Line 1455 of yacc.c  */
#line 4664 "parser.y"
    { terminator_warning (TERM_DIVIDE); ;}
    break;

  case 873:

/* Line 1455 of yacc.c  */
#line 4665 "parser.y"
    { terminator_clear (TERM_DIVIDE); ;}
    break;

  case 874:

/* Line 1455 of yacc.c  */
#line 4674 "parser.y"
    { BEGIN_STATEMENT ("ENTRY", 0); ;}
    break;

  case 875:

/* Line 1455 of yacc.c  */
#line 4676 "parser.y"
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

  case 876:

/* Line 1455 of yacc.c  */
#line 4696 "parser.y"
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

  case 877:

/* Line 1455 of yacc.c  */
#line 4707 "parser.y"
    {
	cb_emit_evaluate ((yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]));
	eval_level--;
  ;}
    break;

  case 878:

/* Line 1455 of yacc.c  */
#line 4714 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 879:

/* Line 1455 of yacc.c  */
#line 4717 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 880:

/* Line 1455 of yacc.c  */
#line 4727 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE_P ((yyvsp[(1) - (1)]))) {
		eval_check[eval_level][eval_inc++] = 0;
	} else {
		eval_check[eval_level][eval_inc++] = 1;
	}
  ;}
    break;

  case 881:

/* Line 1455 of yacc.c  */
#line 4736 "parser.y"
    {
	(yyval) = cb_true;
	eval_check[eval_level][eval_inc++] = 2;
  ;}
    break;

  case 882:

/* Line 1455 of yacc.c  */
#line 4741 "parser.y"
    {
	(yyval) = cb_false;
	eval_check[eval_level][eval_inc++] = 3;
  ;}
    break;

  case 883:

/* Line 1455 of yacc.c  */
#line 4749 "parser.y"
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

  case 884:

/* Line 1455 of yacc.c  */
#line 4777 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 885:

/* Line 1455 of yacc.c  */
#line 4779 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 886:

/* Line 1455 of yacc.c  */
#line 4784 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 887:

/* Line 1455 of yacc.c  */
#line 4788 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]));
	eval_inc2 = 0;
  ;}
    break;

  case 888:

/* Line 1455 of yacc.c  */
#line 4799 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 889:

/* Line 1455 of yacc.c  */
#line 4803 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 890:

/* Line 1455 of yacc.c  */
#line 4807 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), NULL);
	eval_inc2 = 0;
  ;}
    break;

  case 891:

/* Line 1455 of yacc.c  */
#line 4817 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 892:

/* Line 1455 of yacc.c  */
#line 4819 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 893:

/* Line 1455 of yacc.c  */
#line 4823 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 894:

/* Line 1455 of yacc.c  */
#line 4826 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 895:

/* Line 1455 of yacc.c  */
#line 4836 "parser.y"
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

  case 896:

/* Line 1455 of yacc.c  */
#line 4864 "parser.y"
    { (yyval) = cb_any; eval_inc2++; ;}
    break;

  case 897:

/* Line 1455 of yacc.c  */
#line 4865 "parser.y"
    { (yyval) = cb_true; eval_inc2++; ;}
    break;

  case 898:

/* Line 1455 of yacc.c  */
#line 4866 "parser.y"
    { (yyval) = cb_false; eval_inc2++; ;}
    break;

  case 899:

/* Line 1455 of yacc.c  */
#line 4869 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 900:

/* Line 1455 of yacc.c  */
#line 4870 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 901:

/* Line 1455 of yacc.c  */
#line 4874 "parser.y"
    { terminator_warning (TERM_EVALUATE); ;}
    break;

  case 902:

/* Line 1455 of yacc.c  */
#line 4875 "parser.y"
    { terminator_clear (TERM_EVALUATE); ;}
    break;

  case 903:

/* Line 1455 of yacc.c  */
#line 4884 "parser.y"
    { BEGIN_STATEMENT ("EXIT", 0); ;}
    break;

  case 905:

/* Line 1455 of yacc.c  */
#line 4889 "parser.y"
    { /* nothing */ ;}
    break;

  case 906:

/* Line 1455 of yacc.c  */
#line 4891 "parser.y"
    {
	if (in_declaratives && use_global_ind) {
		cb_error (_("EXIT PROGRAM is not allowed within a USE GLOBAL procedure"));
	}
	check_unreached = 1;
	cb_emit_exit (0);
  ;}
    break;

  case 907:

/* Line 1455 of yacc.c  */
#line 4899 "parser.y"
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

  case 908:

/* Line 1455 of yacc.c  */
#line 4916 "parser.y"
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

  case 909:

/* Line 1455 of yacc.c  */
#line 4933 "parser.y"
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

  case 910:

/* Line 1455 of yacc.c  */
#line 4951 "parser.y"
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

  case 911:

/* Line 1455 of yacc.c  */
#line 4975 "parser.y"
    { BEGIN_STATEMENT ("FREE", 0); ;}
    break;

  case 912:

/* Line 1455 of yacc.c  */
#line 4977 "parser.y"
    {
	cb_emit_free ((yyvsp[(3) - (3)]));
  ;}
    break;

  case 913:

/* Line 1455 of yacc.c  */
#line 4988 "parser.y"
    { BEGIN_STATEMENT ("GENERATE", 0); ;}
    break;

  case 914:

/* Line 1455 of yacc.c  */
#line 4990 "parser.y"
    {
	PENDING("GENERATE");
  ;}
    break;

  case 915:

/* Line 1455 of yacc.c  */
#line 5001 "parser.y"
    { BEGIN_STATEMENT ("GO TO", 0); ;}
    break;

  case 916:

/* Line 1455 of yacc.c  */
#line 5003 "parser.y"
    {
	cb_emit_goto ((yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 917:

/* Line 1455 of yacc.c  */
#line 5010 "parser.y"
    {
	check_unreached = 1;
	(yyval) = NULL;
  ;}
    break;

  case 918:

/* Line 1455 of yacc.c  */
#line 5015 "parser.y"
    {
	check_unreached = 0;
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 919:

/* Line 1455 of yacc.c  */
#line 5027 "parser.y"
    { BEGIN_STATEMENT ("GOBACK", 0); ;}
    break;

  case 920:

/* Line 1455 of yacc.c  */
#line 5028 "parser.y"
    {
	check_unreached = 1;
	cb_emit_exit (1);
  ;}
    break;

  case 921:

/* Line 1455 of yacc.c  */
#line 5040 "parser.y"
    { BEGIN_STATEMENT ("IF", TERM_IF); ;}
    break;

  case 922:

/* Line 1455 of yacc.c  */
#line 5042 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 923:

/* Line 1455 of yacc.c  */
#line 5047 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(6) - (8)]) == NULL) {
		cb_error (_("syntax error"));
	}
	cb_emit_if ((yyvsp[(3) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 925:

/* Line 1455 of yacc.c  */
#line 5058 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 926:

/* Line 1455 of yacc.c  */
#line 5062 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 927:

/* Line 1455 of yacc.c  */
#line 5066 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 928:

/* Line 1455 of yacc.c  */
#line 5075 "parser.y"
    { terminator_warning (TERM_IF); ;}
    break;

  case 929:

/* Line 1455 of yacc.c  */
#line 5076 "parser.y"
    { terminator_clear (TERM_IF); ;}
    break;

  case 930:

/* Line 1455 of yacc.c  */
#line 5085 "parser.y"
    { BEGIN_STATEMENT ("INITIALIZE", 0); ;}
    break;

  case 931:

/* Line 1455 of yacc.c  */
#line 5087 "parser.y"
    {
	cb_emit_initialize ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 932:

/* Line 1455 of yacc.c  */
#line 5093 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 933:

/* Line 1455 of yacc.c  */
#line 5094 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 934:

/* Line 1455 of yacc.c  */
#line 5098 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 935:

/* Line 1455 of yacc.c  */
#line 5099 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 936:

/* Line 1455 of yacc.c  */
#line 5100 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 937:

/* Line 1455 of yacc.c  */
#line 5104 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 938:

/* Line 1455 of yacc.c  */
#line 5106 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 939:

/* Line 1455 of yacc.c  */
#line 5110 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 940:

/* Line 1455 of yacc.c  */
#line 5112 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 941:

/* Line 1455 of yacc.c  */
#line 5116 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 942:

/* Line 1455 of yacc.c  */
#line 5120 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHABETIC); ;}
    break;

  case 943:

/* Line 1455 of yacc.c  */
#line 5121 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC); ;}
    break;

  case 944:

/* Line 1455 of yacc.c  */
#line 5122 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC); ;}
    break;

  case 945:

/* Line 1455 of yacc.c  */
#line 5123 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC_EDITED); ;}
    break;

  case 946:

/* Line 1455 of yacc.c  */
#line 5124 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC_EDITED); ;}
    break;

  case 947:

/* Line 1455 of yacc.c  */
#line 5125 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL); ;}
    break;

  case 948:

/* Line 1455 of yacc.c  */
#line 5126 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL_EDITED); ;}
    break;

  case 949:

/* Line 1455 of yacc.c  */
#line 5130 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 950:

/* Line 1455 of yacc.c  */
#line 5131 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 951:

/* Line 1455 of yacc.c  */
#line 5140 "parser.y"
    { BEGIN_STATEMENT ("INITIATE", 0); ;}
    break;

  case 952:

/* Line 1455 of yacc.c  */
#line 5142 "parser.y"
    {
	PENDING("INITIATE");
  ;}
    break;

  case 953:

/* Line 1455 of yacc.c  */
#line 5153 "parser.y"
    {
	BEGIN_STATEMENT ("INSPECT", 0);
	sending_id = 0;
	inspect_keyword = 0;
  ;}
    break;

  case 955:

/* Line 1455 of yacc.c  */
#line 5162 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 0; ;}
    break;

  case 956:

/* Line 1455 of yacc.c  */
#line 5163 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 957:

/* Line 1455 of yacc.c  */
#line 5164 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 960:

/* Line 1455 of yacc.c  */
#line 5173 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 0); ;}
    break;

  case 961:

/* Line 1455 of yacc.c  */
#line 5174 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int1, 1); ;}
    break;

  case 962:

/* Line 1455 of yacc.c  */
#line 5175 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 2); ;}
    break;

  case 963:

/* Line 1455 of yacc.c  */
#line 5181 "parser.y"
    { cb_init_tarrying (); ;}
    break;

  case 964:

/* Line 1455 of yacc.c  */
#line 5182 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 965:

/* Line 1455 of yacc.c  */
#line 5186 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 966:

/* Line 1455 of yacc.c  */
#line 5187 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 967:

/* Line 1455 of yacc.c  */
#line 5191 "parser.y"
    { (yyval) = cb_build_tarrying_data ((yyvsp[(1) - (2)])); ;}
    break;

  case 968:

/* Line 1455 of yacc.c  */
#line 5192 "parser.y"
    { (yyval) = cb_build_tarrying_characters ((yyvsp[(2) - (2)])); ;}
    break;

  case 969:

/* Line 1455 of yacc.c  */
#line 5193 "parser.y"
    { (yyval) = cb_build_tarrying_all (); ;}
    break;

  case 970:

/* Line 1455 of yacc.c  */
#line 5194 "parser.y"
    { (yyval) = cb_build_tarrying_leading (); ;}
    break;

  case 971:

/* Line 1455 of yacc.c  */
#line 5195 "parser.y"
    { (yyval) = cb_build_tarrying_trailing (); ;}
    break;

  case 972:

/* Line 1455 of yacc.c  */
#line 5196 "parser.y"
    { (yyval) = cb_build_tarrying_value ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 973:

/* Line 1455 of yacc.c  */
#line 5202 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); inspect_keyword = 0; ;}
    break;

  case 974:

/* Line 1455 of yacc.c  */
#line 5206 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 975:

/* Line 1455 of yacc.c  */
#line 5207 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 976:

/* Line 1455 of yacc.c  */
#line 5212 "parser.y"
    {
	(yyval) = cb_build_replacing_characters ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]), save_tree_1);
	inspect_keyword = 0;
  ;}
    break;

  case 977:

/* Line 1455 of yacc.c  */
#line 5216 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 978:

/* Line 1455 of yacc.c  */
#line 5220 "parser.y"
    { /* Nothing */ ;}
    break;

  case 979:

/* Line 1455 of yacc.c  */
#line 5221 "parser.y"
    { inspect_keyword = 1; ;}
    break;

  case 980:

/* Line 1455 of yacc.c  */
#line 5222 "parser.y"
    { inspect_keyword = 2; ;}
    break;

  case 981:

/* Line 1455 of yacc.c  */
#line 5223 "parser.y"
    { inspect_keyword = 3; ;}
    break;

  case 982:

/* Line 1455 of yacc.c  */
#line 5224 "parser.y"
    { inspect_keyword = 4; ;}
    break;

  case 983:

/* Line 1455 of yacc.c  */
#line 5229 "parser.y"
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

  case 984:

/* Line 1455 of yacc.c  */
#line 5255 "parser.y"
    {
	if (cb_validate_inspect (save_tree_1, (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])) < 0 ) {
		(yyval) = cb_error_node;
	} else {
		(yyval) = cb_build_converting ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 985:

/* Line 1455 of yacc.c  */
#line 5267 "parser.y"
    { (yyval) = cb_build_inspect_region_start (); ;}
    break;

  case 986:

/* Line 1455 of yacc.c  */
#line 5269 "parser.y"
    { (yyval) = cb_build_inspect_region ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 989:

/* Line 1455 of yacc.c  */
#line 5280 "parser.y"
    { BEGIN_STATEMENT ("MERGE", 0); ;}
    break;

  case 991:

/* Line 1455 of yacc.c  */
#line 5290 "parser.y"
    { BEGIN_STATEMENT ("MOVE", 0); ;}
    break;

  case 993:

/* Line 1455 of yacc.c  */
#line 5296 "parser.y"
    {
	cb_emit_move ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 994:

/* Line 1455 of yacc.c  */
#line 5300 "parser.y"
    {
	cb_emit_move_corresponding ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 995:

/* Line 1455 of yacc.c  */
#line 5311 "parser.y"
    { BEGIN_STATEMENT ("MULTIPLY", TERM_MULTIPLY); ;}
    break;

  case 997:

/* Line 1455 of yacc.c  */
#line 5318 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '*', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 998:

/* Line 1455 of yacc.c  */
#line 5322 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '*', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 999:

/* Line 1455 of yacc.c  */
#line 5328 "parser.y"
    { terminator_warning (TERM_MULTIPLY); ;}
    break;

  case 1000:

/* Line 1455 of yacc.c  */
#line 5329 "parser.y"
    { terminator_clear (TERM_MULTIPLY); ;}
    break;

  case 1001:

/* Line 1455 of yacc.c  */
#line 5338 "parser.y"
    { BEGIN_STATEMENT ("OPEN", 0); ;}
    break;

  case 1004:

/* Line 1455 of yacc.c  */
#line 5345 "parser.y"
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

  case 1005:

/* Line 1455 of yacc.c  */
#line 5357 "parser.y"
    { (yyval) = cb_int (COB_OPEN_INPUT); ;}
    break;

  case 1006:

/* Line 1455 of yacc.c  */
#line 5358 "parser.y"
    { (yyval) = cb_int (COB_OPEN_OUTPUT); ;}
    break;

  case 1007:

/* Line 1455 of yacc.c  */
#line 5359 "parser.y"
    { (yyval) = cb_int (COB_OPEN_I_O); ;}
    break;

  case 1008:

/* Line 1455 of yacc.c  */
#line 5360 "parser.y"
    { (yyval) = cb_int (COB_OPEN_EXTEND); ;}
    break;

  case 1009:

/* Line 1455 of yacc.c  */
#line 5364 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1010:

/* Line 1455 of yacc.c  */
#line 5365 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1011:

/* Line 1455 of yacc.c  */
#line 5369 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1012:

/* Line 1455 of yacc.c  */
#line 5370 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1013:

/* Line 1455 of yacc.c  */
#line 5371 "parser.y"
    { PENDING ("OPEN ... WITH LOCK"); ;}
    break;

  case 1014:

/* Line 1455 of yacc.c  */
#line 5383 "parser.y"
    { BEGIN_STATEMENT ("PERFORM", TERM_PERFORM); ;}
    break;

  case 1016:

/* Line 1455 of yacc.c  */
#line 5389 "parser.y"
    {
	cb_emit_perform ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));
  ;}
    break;

  case 1017:

/* Line 1455 of yacc.c  */
#line 5393 "parser.y"
    {
	perform_stack = cb_cons ((yyvsp[(1) - (1)]), perform_stack);
	check_unreached = 0;
  ;}
    break;

  case 1018:

/* Line 1455 of yacc.c  */
#line 5398 "parser.y"
    {
	perform_stack = CB_CHAIN (perform_stack);
	cb_emit_perform ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 1019:

/* Line 1455 of yacc.c  */
#line 5403 "parser.y"
    {
	cb_emit_perform ((yyvsp[(1) - (2)]), NULL);
  ;}
    break;

  case 1020:

/* Line 1455 of yacc.c  */
#line 5409 "parser.y"
    { terminator_error (); ;}
    break;

  case 1021:

/* Line 1455 of yacc.c  */
#line 5410 "parser.y"
    { terminator_clear (TERM_PERFORM); ;}
    break;

  case 1022:

/* Line 1455 of yacc.c  */
#line 5415 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(1) - (1)]))->length = cb_true; /* return from $1 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (1)]), (yyvsp[(1) - (1)]));
  ;}
    break;

  case 1023:

/* Line 1455 of yacc.c  */
#line 5420 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(3) - (3)]))->length = cb_true; /* return from $3 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1024:

/* Line 1455 of yacc.c  */
#line 5428 "parser.y"
    {
	(yyval) = cb_build_perform_once (NULL);
  ;}
    break;

  case 1025:

/* Line 1455 of yacc.c  */
#line 5432 "parser.y"
    {
	(yyval) = cb_build_perform_forever (NULL);
  ;}
    break;

  case 1026:

/* Line 1455 of yacc.c  */
#line 5436 "parser.y"
    {
	(yyval) = cb_build_perform_times ((yyvsp[(1) - (2)]));
	current_program->loop_counter++;
  ;}
    break;

  case 1027:

/* Line 1455 of yacc.c  */
#line 5441 "parser.y"
    {
	cb_tree varying;

	varying = cb_list_init (cb_build_perform_varying (NULL, NULL, NULL, (yyvsp[(3) - (3)])));
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), varying);
  ;}
    break;

  case 1028:

/* Line 1455 of yacc.c  */
#line 5448 "parser.y"
    {
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1029:

/* Line 1455 of yacc.c  */
#line 5454 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1030:

/* Line 1455 of yacc.c  */
#line 5455 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1031:

/* Line 1455 of yacc.c  */
#line 5459 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1032:

/* Line 1455 of yacc.c  */
#line 5461 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1033:

/* Line 1455 of yacc.c  */
#line 5466 "parser.y"
    {
	(yyval) = cb_build_perform_varying ((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1034:

/* Line 1455 of yacc.c  */
#line 5477 "parser.y"
    { BEGIN_STATEMENT ("READ", TERM_READ); ;}
    break;

  case 1035:

/* Line 1455 of yacc.c  */
#line 5480 "parser.y"
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

  case 1036:

/* Line 1455 of yacc.c  */
#line 5506 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1037:

/* Line 1455 of yacc.c  */
#line 5507 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1038:

/* Line 1455 of yacc.c  */
#line 5511 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1039:

/* Line 1455 of yacc.c  */
#line 5513 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1040:

/* Line 1455 of yacc.c  */
#line 5517 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1041:

/* Line 1455 of yacc.c  */
#line 5521 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1042:

/* Line 1455 of yacc.c  */
#line 5525 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1043:

/* Line 1455 of yacc.c  */
#line 5529 "parser.y"
    {
	(yyval) = cb_int4;
  ;}
    break;

  case 1044:

/* Line 1455 of yacc.c  */
#line 5535 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1045:

/* Line 1455 of yacc.c  */
#line 5537 "parser.y"
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

  case 1049:

/* Line 1455 of yacc.c  */
#line 5556 "parser.y"
    { terminator_warning (TERM_READ); ;}
    break;

  case 1050:

/* Line 1455 of yacc.c  */
#line 5557 "parser.y"
    { terminator_clear (TERM_READ); ;}
    break;

  case 1051:

/* Line 1455 of yacc.c  */
#line 5566 "parser.y"
    { BEGIN_STATEMENT ("RELEASE", 0); ;}
    break;

  case 1052:

/* Line 1455 of yacc.c  */
#line 5568 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_release ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
	}
  ;}
    break;

  case 1053:

/* Line 1455 of yacc.c  */
#line 5581 "parser.y"
    { BEGIN_STATEMENT ("RETURN", TERM_RETURN); ;}
    break;

  case 1054:

/* Line 1455 of yacc.c  */
#line 5584 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_return ((yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]));
	}
  ;}
    break;

  case 1055:

/* Line 1455 of yacc.c  */
#line 5592 "parser.y"
    { terminator_warning (TERM_RETURN); ;}
    break;

  case 1056:

/* Line 1455 of yacc.c  */
#line 5593 "parser.y"
    { terminator_clear (TERM_RETURN); ;}
    break;

  case 1057:

/* Line 1455 of yacc.c  */
#line 5602 "parser.y"
    { BEGIN_STATEMENT ("REWRITE", TERM_REWRITE); ;}
    break;

  case 1058:

/* Line 1455 of yacc.c  */
#line 5605 "parser.y"
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

  case 1059:

/* Line 1455 of yacc.c  */
#line 5619 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1060:

/* Line 1455 of yacc.c  */
#line 5621 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1061:

/* Line 1455 of yacc.c  */
#line 5625 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1062:

/* Line 1455 of yacc.c  */
#line 5631 "parser.y"
    { terminator_warning (TERM_REWRITE); ;}
    break;

  case 1063:

/* Line 1455 of yacc.c  */
#line 5632 "parser.y"
    { terminator_clear (TERM_REWRITE); ;}
    break;

  case 1064:

/* Line 1455 of yacc.c  */
#line 5642 "parser.y"
    {
	BEGIN_STATEMENT ("ROLLBACK", 0);
	cb_emit_rollback ();
  ;}
    break;

  case 1065:

/* Line 1455 of yacc.c  */
#line 5654 "parser.y"
    { BEGIN_STATEMENT ("SEARCH", TERM_SEARCH); ;}
    break;

  case 1067:

/* Line 1455 of yacc.c  */
#line 5661 "parser.y"
    {
	cb_emit_search ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1068:

/* Line 1455 of yacc.c  */
#line 5665 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1069:

/* Line 1455 of yacc.c  */
#line 5669 "parser.y"
    {
	cb_emit_search_all ((yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1070:

/* Line 1455 of yacc.c  */
#line 5675 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1071:

/* Line 1455 of yacc.c  */
#line 5676 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1072:

/* Line 1455 of yacc.c  */
#line 5680 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1073:

/* Line 1455 of yacc.c  */
#line 5682 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1074:

/* Line 1455 of yacc.c  */
#line 5686 "parser.y"
    {
	(yyval) = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 1075:

/* Line 1455 of yacc.c  */
#line 5692 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1076:

/* Line 1455 of yacc.c  */
#line 5693 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); CB_IF ((yyvsp[(1) - (2)]))->stmt2 = (yyvsp[(2) - (2)]); ;}
    break;

  case 1077:

/* Line 1455 of yacc.c  */
#line 5698 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1078:

/* Line 1455 of yacc.c  */
#line 5702 "parser.y"
    {
	(yyval) = cb_build_if ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), NULL);
  ;}
    break;

  case 1079:

/* Line 1455 of yacc.c  */
#line 5708 "parser.y"
    { terminator_warning (TERM_SEARCH); ;}
    break;

  case 1080:

/* Line 1455 of yacc.c  */
#line 5709 "parser.y"
    { terminator_clear (TERM_SEARCH); ;}
    break;

  case 1081:

/* Line 1455 of yacc.c  */
#line 5718 "parser.y"
    { BEGIN_STATEMENT ("SET", 0); ;}
    break;

  case 1088:

/* Line 1455 of yacc.c  */
#line 5734 "parser.y"
    {
	cb_emit_setenv ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1089:

/* Line 1455 of yacc.c  */
#line 5743 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (4)]), cb_build_ppointer ((yyvsp[(4) - (4)])));
  ;}
    break;

  case 1090:

/* Line 1455 of yacc.c  */
#line 5747 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1091:

/* Line 1455 of yacc.c  */
#line 5756 "parser.y"
    {
	cb_emit_set_up_down ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1092:

/* Line 1455 of yacc.c  */
#line 5762 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1093:

/* Line 1455 of yacc.c  */
#line 5763 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1096:

/* Line 1455 of yacc.c  */
#line 5775 "parser.y"
    {
	cb_emit_set_on_off ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1099:

/* Line 1455 of yacc.c  */
#line 5789 "parser.y"
    {
	cb_emit_set_true ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1100:

/* Line 1455 of yacc.c  */
#line 5793 "parser.y"
    {
	cb_emit_set_false ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1101:

/* Line 1455 of yacc.c  */
#line 5804 "parser.y"
    { BEGIN_STATEMENT ("SORT", 0); ;}
    break;

  case 1103:

/* Line 1455 of yacc.c  */
#line 5810 "parser.y"
    {
	cb_emit_sort_init ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (4)]))) && (yyvsp[(2) - (4)]) == NULL) {
		cb_error (_("File sort requires KEY phrase"));
	}
	/* used in sort_input/sort_output */
	save_tree_1 = (yyvsp[(1) - (4)]);
  ;}
    break;

  case 1104:

/* Line 1455 of yacc.c  */
#line 5819 "parser.y"
    {
	cb_emit_sort_finish ((yyvsp[(1) - (7)]));
  ;}
    break;

  case 1105:

/* Line 1455 of yacc.c  */
#line 5826 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 1106:

/* Line 1455 of yacc.c  */
#line 5831 "parser.y"
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

  case 1107:

/* Line 1455 of yacc.c  */
#line 5845 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1108:

/* Line 1455 of yacc.c  */
#line 5846 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1110:

/* Line 1455 of yacc.c  */
#line 5850 "parser.y"
    { /* nothing */ ;}
    break;

  case 1111:

/* Line 1455 of yacc.c  */
#line 5854 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1112:

/* Line 1455 of yacc.c  */
#line 5855 "parser.y"
    { (yyval) = cb_ref ((yyvsp[(3) - (3)])); ;}
    break;

  case 1113:

/* Line 1455 of yacc.c  */
#line 5860 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires USING or INPUT PROCEDURE"));
	}
  ;}
    break;

  case 1114:

/* Line 1455 of yacc.c  */
#line 5866 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("USING invalid with table SORT"));
	} else {
		cb_emit_sort_using (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1115:

/* Line 1455 of yacc.c  */
#line 5874 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("INPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_input ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1116:

/* Line 1455 of yacc.c  */
#line 5885 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires GIVING or OUTPUT PROCEDURE"));
	}
  ;}
    break;

  case 1117:

/* Line 1455 of yacc.c  */
#line 5891 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("GIVING invalid with table SORT"));
	} else {
		cb_emit_sort_giving (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1118:

/* Line 1455 of yacc.c  */
#line 5899 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("OUTPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_output ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1119:

/* Line 1455 of yacc.c  */
#line 5914 "parser.y"
    { BEGIN_STATEMENT ("START", TERM_START); ;}
    break;

  case 1120:

/* Line 1455 of yacc.c  */
#line 5915 "parser.y"
    { (yyval) = cb_int (COB_EQ); ;}
    break;

  case 1121:

/* Line 1455 of yacc.c  */
#line 5918 "parser.y"
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

  case 1122:

/* Line 1455 of yacc.c  */
#line 5935 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1123:

/* Line 1455 of yacc.c  */
#line 5937 "parser.y"
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

  case 1124:

/* Line 1455 of yacc.c  */
#line 5952 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_NE : COB_EQ); ;}
    break;

  case 1125:

/* Line 1455 of yacc.c  */
#line 5953 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LE : COB_GT); ;}
    break;

  case 1126:

/* Line 1455 of yacc.c  */
#line 5954 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GE : COB_LT); ;}
    break;

  case 1127:

/* Line 1455 of yacc.c  */
#line 5955 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LT : COB_GE); ;}
    break;

  case 1128:

/* Line 1455 of yacc.c  */
#line 5956 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GT : COB_LE); ;}
    break;

  case 1129:

/* Line 1455 of yacc.c  */
#line 5960 "parser.y"
    { terminator_warning (TERM_START); ;}
    break;

  case 1130:

/* Line 1455 of yacc.c  */
#line 5961 "parser.y"
    { terminator_clear (TERM_START); ;}
    break;

  case 1131:

/* Line 1455 of yacc.c  */
#line 5970 "parser.y"
    { BEGIN_STATEMENT ("STOP", 0); ;}
    break;

  case 1132:

/* Line 1455 of yacc.c  */
#line 5972 "parser.y"
    {
	cb_emit_stop_run ((yyvsp[(4) - (4)]));
  ;}
    break;

  case 1133:

/* Line 1455 of yacc.c  */
#line 5976 "parser.y"
    {
	cb_verify (cb_stop_literal_statement, "STOP literal");
  ;}
    break;

  case 1134:

/* Line 1455 of yacc.c  */
#line 5982 "parser.y"
    { (yyval) = current_program->cb_return_code; ;}
    break;

  case 1135:

/* Line 1455 of yacc.c  */
#line 5983 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1136:

/* Line 1455 of yacc.c  */
#line 5984 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1137:

/* Line 1455 of yacc.c  */
#line 5993 "parser.y"
    { BEGIN_STATEMENT ("STRING", TERM_STRING); ;}
    break;

  case 1138:

/* Line 1455 of yacc.c  */
#line 5996 "parser.y"
    {
	cb_emit_string ((yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]));
  ;}
    break;

  case 1139:

/* Line 1455 of yacc.c  */
#line 6002 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1140:

/* Line 1455 of yacc.c  */
#line 6003 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1141:

/* Line 1455 of yacc.c  */
#line 6007 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1142:

/* Line 1455 of yacc.c  */
#line 6008 "parser.y"
    { (yyval) = cb_build_pair (cb_int0, NULL); ;}
    break;

  case 1143:

/* Line 1455 of yacc.c  */
#line 6009 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), NULL); ;}
    break;

  case 1144:

/* Line 1455 of yacc.c  */
#line 6013 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1145:

/* Line 1455 of yacc.c  */
#line 6014 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1146:

/* Line 1455 of yacc.c  */
#line 6018 "parser.y"
    { terminator_warning (TERM_STRING); ;}
    break;

  case 1147:

/* Line 1455 of yacc.c  */
#line 6019 "parser.y"
    { terminator_clear (TERM_STRING); ;}
    break;

  case 1148:

/* Line 1455 of yacc.c  */
#line 6028 "parser.y"
    { BEGIN_STATEMENT ("SUBTRACT", TERM_SUBTRACT); ;}
    break;

  case 1150:

/* Line 1455 of yacc.c  */
#line 6035 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '-', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 1151:

/* Line 1455 of yacc.c  */
#line 6039 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_list (cb_cons ((yyvsp[(3) - (6)]), (yyvsp[(1) - (6)])), '-'));
  ;}
    break;

  case 1152:

/* Line 1455 of yacc.c  */
#line 6043 "parser.y"
    {
	cb_emit_corresponding (cb_build_sub, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 1153:

/* Line 1455 of yacc.c  */
#line 6049 "parser.y"
    { terminator_warning (TERM_SUBTRACT); ;}
    break;

  case 1154:

/* Line 1455 of yacc.c  */
#line 6050 "parser.y"
    { terminator_clear (TERM_SUBTRACT); ;}
    break;

  case 1155:

/* Line 1455 of yacc.c  */
#line 6060 "parser.y"
    {
	BEGIN_STATEMENT ("SUPPRESS", 0);
	PENDING("SUPPRESS");
  ;}
    break;

  case 1158:

/* Line 1455 of yacc.c  */
#line 6075 "parser.y"
    { BEGIN_STATEMENT ("TERMINATE", 0); ;}
    break;

  case 1159:

/* Line 1455 of yacc.c  */
#line 6077 "parser.y"
    {
	PENDING("TERMINATE");
  ;}
    break;

  case 1160:

/* Line 1455 of yacc.c  */
#line 6088 "parser.y"
    { BEGIN_STATEMENT ("TRANSFORM", 0); ;}
    break;

  case 1161:

/* Line 1455 of yacc.c  */
#line 6090 "parser.y"
    {
	cb_tree		x;

	x = cb_build_converting ((yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]), cb_build_inspect_region_start ());
	cb_emit_inspect ((yyvsp[(3) - (7)]), x, cb_int0, 2);
  ;}
    break;

  case 1162:

/* Line 1455 of yacc.c  */
#line 6104 "parser.y"
    { BEGIN_STATEMENT ("UNLOCK", 0); ;}
    break;

  case 1163:

/* Line 1455 of yacc.c  */
#line 6106 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_unlock ((yyvsp[(3) - (4)]));
	}
  ;}
    break;

  case 1167:

/* Line 1455 of yacc.c  */
#line 6125 "parser.y"
    { BEGIN_STATEMENT ("UNSTRING", TERM_UNSTRING); ;}
    break;

  case 1168:

/* Line 1455 of yacc.c  */
#line 6129 "parser.y"
    {
	cb_emit_unstring ((yyvsp[(3) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]));
  ;}
    break;

  case 1169:

/* Line 1455 of yacc.c  */
#line 6135 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1170:

/* Line 1455 of yacc.c  */
#line 6137 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1171:

/* Line 1455 of yacc.c  */
#line 6141 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1172:

/* Line 1455 of yacc.c  */
#line 6143 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1173:

/* Line 1455 of yacc.c  */
#line 6148 "parser.y"
    {
	(yyval) = cb_build_unstring_delimited ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1174:

/* Line 1455 of yacc.c  */
#line 6154 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 1175:

/* Line 1455 of yacc.c  */
#line 6156 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1176:

/* Line 1455 of yacc.c  */
#line 6161 "parser.y"
    {
	(yyval) = cb_build_unstring_into ((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1177:

/* Line 1455 of yacc.c  */
#line 6167 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1178:

/* Line 1455 of yacc.c  */
#line 6168 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1179:

/* Line 1455 of yacc.c  */
#line 6172 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1180:

/* Line 1455 of yacc.c  */
#line 6173 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1181:

/* Line 1455 of yacc.c  */
#line 6177 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1182:

/* Line 1455 of yacc.c  */
#line 6178 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1183:

/* Line 1455 of yacc.c  */
#line 6182 "parser.y"
    { terminator_warning (TERM_UNSTRING); ;}
    break;

  case 1184:

/* Line 1455 of yacc.c  */
#line 6183 "parser.y"
    { terminator_clear (TERM_UNSTRING); ;}
    break;

  case 1188:

/* Line 1455 of yacc.c  */
#line 6201 "parser.y"
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

  case 1189:

/* Line 1455 of yacc.c  */
#line 6222 "parser.y"
    {
	use_global_ind = 0;
  ;}
    break;

  case 1190:

/* Line 1455 of yacc.c  */
#line 6226 "parser.y"
    {
	use_global_ind = 1;
	current_program->flag_global_use = 1;
  ;}
    break;

  case 1191:

/* Line 1455 of yacc.c  */
#line 6234 "parser.y"
    {
	cb_tree		l;

	for (l = (yyvsp[(1) - (1)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			setup_use_file (CB_FILE (cb_ref (CB_VALUE (l))));
		}
	}
  ;}
    break;

  case 1192:

/* Line 1455 of yacc.c  */
#line 6244 "parser.y"
    {
	current_program->global_handler[COB_OPEN_INPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_INPUT].handler_prog = current_program;
  ;}
    break;

  case 1193:

/* Line 1455 of yacc.c  */
#line 6249 "parser.y"
    {
	current_program->global_handler[COB_OPEN_OUTPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_OUTPUT].handler_prog = current_program;
  ;}
    break;

  case 1194:

/* Line 1455 of yacc.c  */
#line 6254 "parser.y"
    {
	current_program->global_handler[COB_OPEN_I_O].handler_label = current_section;
	current_program->global_handler[COB_OPEN_I_O].handler_prog = current_program;
  ;}
    break;

  case 1195:

/* Line 1455 of yacc.c  */
#line 6259 "parser.y"
    {
	current_program->global_handler[COB_OPEN_EXTEND].handler_label = current_section;
	current_program->global_handler[COB_OPEN_EXTEND].handler_prog = current_program;
  ;}
    break;

  case 1208:

/* Line 1455 of yacc.c  */
#line 6291 "parser.y"
    {
	PENDING ("USE FOR DEBUGGING");
  ;}
    break;

  case 1211:

/* Line 1455 of yacc.c  */
#line 6303 "parser.y"
    {
	PENDING ("USE BEFORE REPORTING");
  ;}
    break;

  case 1212:

/* Line 1455 of yacc.c  */
#line 6314 "parser.y"
    { BEGIN_STATEMENT ("WRITE", TERM_WRITE); ;}
    break;

  case 1213:

/* Line 1455 of yacc.c  */
#line 6317 "parser.y"
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

  case 1214:

/* Line 1455 of yacc.c  */
#line 6331 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1215:

/* Line 1455 of yacc.c  */
#line 6332 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1216:

/* Line 1455 of yacc.c  */
#line 6337 "parser.y"
    {
	(yyval) = cb_int0;
  ;}
    break;

  case 1217:

/* Line 1455 of yacc.c  */
#line 6341 "parser.y"
    {
	(yyval) = cb_build_write_advancing_lines ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 1218:

/* Line 1455 of yacc.c  */
#line 6345 "parser.y"
    {
	(yyval) = cb_build_write_advancing_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1219:

/* Line 1455 of yacc.c  */
#line 6349 "parser.y"
    {
	(yyval) = cb_build_write_advancing_page ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1220:

/* Line 1455 of yacc.c  */
#line 6355 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1221:

/* Line 1455 of yacc.c  */
#line 6356 "parser.y"
    { (yyval) = CB_AFTER; ;}
    break;

  case 1225:

/* Line 1455 of yacc.c  */
#line 6365 "parser.y"
    { terminator_warning (TERM_WRITE); ;}
    break;

  case 1226:

/* Line 1455 of yacc.c  */
#line 6366 "parser.y"
    { terminator_clear (TERM_WRITE); ;}
    break;

  case 1227:

/* Line 1455 of yacc.c  */
#line 6381 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_ACCEPT;
  ;}
    break;

  case 1228:

/* Line 1455 of yacc.c  */
#line 6389 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_DISPLAY;
  ;}
    break;

  case 1230:

/* Line 1455 of yacc.c  */
#line 6396 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1231:

/* Line 1455 of yacc.c  */
#line 6400 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1233:

/* Line 1455 of yacc.c  */
#line 6407 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1234:

/* Line 1455 of yacc.c  */
#line 6411 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1237:

/* Line 1455 of yacc.c  */
#line 6427 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1238:

/* Line 1455 of yacc.c  */
#line 6432 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1240:

/* Line 1455 of yacc.c  */
#line 6439 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1241:

/* Line 1455 of yacc.c  */
#line 6444 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1242:

/* Line 1455 of yacc.c  */
#line 6456 "parser.y"
    {
	current_statement->handler_id = COB_EC_OVERFLOW;
  ;}
    break;

  case 1244:

/* Line 1455 of yacc.c  */
#line 6463 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1245:

/* Line 1455 of yacc.c  */
#line 6467 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1247:

/* Line 1455 of yacc.c  */
#line 6474 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1248:

/* Line 1455 of yacc.c  */
#line 6478 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1249:

/* Line 1455 of yacc.c  */
#line 6490 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1250:

/* Line 1455 of yacc.c  */
#line 6495 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1251:

/* Line 1455 of yacc.c  */
#line 6500 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1252:

/* Line 1455 of yacc.c  */
#line 6509 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1253:

/* Line 1455 of yacc.c  */
#line 6513 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1254:

/* Line 1455 of yacc.c  */
#line 6520 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1255:

/* Line 1455 of yacc.c  */
#line 6524 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1256:

/* Line 1455 of yacc.c  */
#line 6536 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1257:

/* Line 1455 of yacc.c  */
#line 6541 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1258:

/* Line 1455 of yacc.c  */
#line 6546 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1259:

/* Line 1455 of yacc.c  */
#line 6555 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1260:

/* Line 1455 of yacc.c  */
#line 6559 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1261:

/* Line 1455 of yacc.c  */
#line 6566 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1262:

/* Line 1455 of yacc.c  */
#line 6570 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1265:

/* Line 1455 of yacc.c  */
#line 6586 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1266:

/* Line 1455 of yacc.c  */
#line 6591 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1267:

/* Line 1455 of yacc.c  */
#line 6596 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1268:

/* Line 1455 of yacc.c  */
#line 6605 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1269:

/* Line 1455 of yacc.c  */
#line 6609 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1270:

/* Line 1455 of yacc.c  */
#line 6616 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1271:

/* Line 1455 of yacc.c  */
#line 6620 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1272:

/* Line 1455 of yacc.c  */
#line 6632 "parser.y"
    {
	(yyval) = cb_one;
  ;}
    break;

  case 1273:

/* Line 1455 of yacc.c  */
#line 6636 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 1274:

/* Line 1455 of yacc.c  */
#line 6648 "parser.y"
    {
	(yyval) = cb_build_cond ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1275:

/* Line 1455 of yacc.c  */
#line 6655 "parser.y"
    {
	(yyval) = cb_build_expr ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1276:

/* Line 1455 of yacc.c  */
#line 6661 "parser.y"
    {
	current_expr = NULL;
  ;}
    break;

  case 1277:

/* Line 1455 of yacc.c  */
#line 6665 "parser.y"
    {
	(yyval) = cb_list_reverse (current_expr);
  ;}
    break;

  case 1278:

/* Line 1455 of yacc.c  */
#line 6671 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1279:

/* Line 1455 of yacc.c  */
#line 6672 "parser.y"
    { push_expr (')', NULL); ;}
    break;

  case 1280:

/* Line 1455 of yacc.c  */
#line 6674 "parser.y"
    { push_expr ('O', NULL); ;}
    break;

  case 1281:

/* Line 1455 of yacc.c  */
#line 6675 "parser.y"
    { push_expr ('9', NULL); ;}
    break;

  case 1282:

/* Line 1455 of yacc.c  */
#line 6676 "parser.y"
    { push_expr ('A', NULL); ;}
    break;

  case 1283:

/* Line 1455 of yacc.c  */
#line 6677 "parser.y"
    { push_expr ('L', NULL); ;}
    break;

  case 1284:

/* Line 1455 of yacc.c  */
#line 6678 "parser.y"
    { push_expr ('U', NULL); ;}
    break;

  case 1285:

/* Line 1455 of yacc.c  */
#line 6679 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1286:

/* Line 1455 of yacc.c  */
#line 6681 "parser.y"
    { push_expr ('O', NULL); ;}
    break;

  case 1287:

/* Line 1455 of yacc.c  */
#line 6682 "parser.y"
    { push_expr ('9', NULL); ;}
    break;

  case 1288:

/* Line 1455 of yacc.c  */
#line 6683 "parser.y"
    { push_expr ('A', NULL); ;}
    break;

  case 1289:

/* Line 1455 of yacc.c  */
#line 6684 "parser.y"
    { push_expr ('L', NULL); ;}
    break;

  case 1290:

/* Line 1455 of yacc.c  */
#line 6685 "parser.y"
    { push_expr ('U', NULL); ;}
    break;

  case 1291:

/* Line 1455 of yacc.c  */
#line 6686 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1292:

/* Line 1455 of yacc.c  */
#line 6688 "parser.y"
    { push_expr ('P', NULL); ;}
    break;

  case 1293:

/* Line 1455 of yacc.c  */
#line 6689 "parser.y"
    { push_expr ('N', NULL); ;}
    break;

  case 1294:

/* Line 1455 of yacc.c  */
#line 6691 "parser.y"
    { push_expr ('P', NULL); ;}
    break;

  case 1295:

/* Line 1455 of yacc.c  */
#line 6692 "parser.y"
    { push_expr ('N', NULL); ;}
    break;

  case 1296:

/* Line 1455 of yacc.c  */
#line 6693 "parser.y"
    { push_expr ('x', cb_zero); ;}
    break;

  case 1300:

/* Line 1455 of yacc.c  */
#line 6700 "parser.y"
    { push_expr ('(', NULL); ;}
    break;

  case 1301:

/* Line 1455 of yacc.c  */
#line 6702 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1302:

/* Line 1455 of yacc.c  */
#line 6703 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1303:

/* Line 1455 of yacc.c  */
#line 6704 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1304:

/* Line 1455 of yacc.c  */
#line 6706 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1305:

/* Line 1455 of yacc.c  */
#line 6707 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1306:

/* Line 1455 of yacc.c  */
#line 6709 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1307:

/* Line 1455 of yacc.c  */
#line 6710 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1308:

/* Line 1455 of yacc.c  */
#line 6711 "parser.y"
    { push_expr ('*', NULL); ;}
    break;

  case 1309:

/* Line 1455 of yacc.c  */
#line 6712 "parser.y"
    { push_expr ('/', NULL); ;}
    break;

  case 1310:

/* Line 1455 of yacc.c  */
#line 6713 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1311:

/* Line 1455 of yacc.c  */
#line 6715 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1312:

/* Line 1455 of yacc.c  */
#line 6716 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1313:

/* Line 1455 of yacc.c  */
#line 6717 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1314:

/* Line 1455 of yacc.c  */
#line 6718 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1315:

/* Line 1455 of yacc.c  */
#line 6719 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1316:

/* Line 1455 of yacc.c  */
#line 6720 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1317:

/* Line 1455 of yacc.c  */
#line 6722 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1318:

/* Line 1455 of yacc.c  */
#line 6723 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1319:

/* Line 1455 of yacc.c  */
#line 6724 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1320:

/* Line 1455 of yacc.c  */
#line 6725 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1321:

/* Line 1455 of yacc.c  */
#line 6726 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1322:

/* Line 1455 of yacc.c  */
#line 6727 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1323:

/* Line 1455 of yacc.c  */
#line 6729 "parser.y"
    { push_expr ('&', NULL); ;}
    break;

  case 1324:

/* Line 1455 of yacc.c  */
#line 6730 "parser.y"
    { push_expr ('|', NULL); ;}
    break;

  case 1338:

/* Line 1455 of yacc.c  */
#line 6742 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1339:

/* Line 1455 of yacc.c  */
#line 6743 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1343:

/* Line 1455 of yacc.c  */
#line 6752 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1344:

/* Line 1455 of yacc.c  */
#line 6753 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '+', (yyvsp[(3) - (3)])); ;}
    break;

  case 1345:

/* Line 1455 of yacc.c  */
#line 6754 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '-', (yyvsp[(3) - (3)])); ;}
    break;

  case 1346:

/* Line 1455 of yacc.c  */
#line 6755 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '*', (yyvsp[(3) - (3)])); ;}
    break;

  case 1347:

/* Line 1455 of yacc.c  */
#line 6756 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '/', (yyvsp[(3) - (3)])); ;}
    break;

  case 1348:

/* Line 1455 of yacc.c  */
#line 6757 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1349:

/* Line 1455 of yacc.c  */
#line 6758 "parser.y"
    { (yyval) = cb_build_binary_op (cb_zero, '-', (yyvsp[(2) - (2)])); ;}
    break;

  case 1350:

/* Line 1455 of yacc.c  */
#line 6759 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '^', (yyvsp[(3) - (3)])); ;}
    break;

  case 1351:

/* Line 1455 of yacc.c  */
#line 6760 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1352:

/* Line 1455 of yacc.c  */
#line 6772 "parser.y"
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

  case 1353:

/* Line 1455 of yacc.c  */
#line 6784 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(3) - (3)])))) {
		(yyval) = CB_FILE (cb_ref ((yyvsp[(3) - (3)])))->linage_ctr;
	} else {
		cb_error_x ((yyvsp[(3) - (3)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(3) - (3)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1354:

/* Line 1455 of yacc.c  */
#line 6798 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1355:

/* Line 1455 of yacc.c  */
#line 6800 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1356:

/* Line 1455 of yacc.c  */
#line 6804 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)])); ;}
    break;

  case 1357:

/* Line 1455 of yacc.c  */
#line 6811 "parser.y"
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

  case 1358:

/* Line 1455 of yacc.c  */
#line 6833 "parser.y"
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

  case 1359:

/* Line 1455 of yacc.c  */
#line 6853 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1360:

/* Line 1455 of yacc.c  */
#line 6857 "parser.y"
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

  case 1361:

/* Line 1455 of yacc.c  */
#line 6873 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (1)])))) {
		(yyval) = (yyvsp[(1) - (1)]);
	} else {
		cb_error_x ((yyvsp[(1) - (1)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(1) - (1)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1362:

/* Line 1455 of yacc.c  */
#line 6886 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1363:

/* Line 1455 of yacc.c  */
#line 6888 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1364:

/* Line 1455 of yacc.c  */
#line 6892 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1365:

/* Line 1455 of yacc.c  */
#line 6898 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1366:

/* Line 1455 of yacc.c  */
#line 6900 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1367:

/* Line 1455 of yacc.c  */
#line 6905 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	CB_REFERENCE ((yyval))->offset = CB_TREE (current_section);
	current_program->label_list = cb_cons ((yyval), current_program->label_list);
  ;}
    break;

  case 1371:

/* Line 1455 of yacc.c  */
#line 6920 "parser.y"
    {
	(yyval) = cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(1) - (1)]))->data));
	(yyval)->source_file = (yyvsp[(1) - (1)])->source_file;
	(yyval)->source_line = (yyvsp[(1) - (1)])->source_line;
  ;}
    break;

  case 1372:

/* Line 1455 of yacc.c  */
#line 6930 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1373:

/* Line 1455 of yacc.c  */
#line 6931 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1374:

/* Line 1455 of yacc.c  */
#line 6936 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	current_program->reference_list = cb_cons ((yyval), current_program->reference_list);
  ;}
    break;

  case 1375:

/* Line 1455 of yacc.c  */
#line 6945 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1376:

/* Line 1455 of yacc.c  */
#line 6946 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1377:

/* Line 1455 of yacc.c  */
#line 6950 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1378:

/* Line 1455 of yacc.c  */
#line 6951 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1381:

/* Line 1455 of yacc.c  */
#line 6963 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE ((yyval))->word->count > 0) {
		redefinition_error ((yyval));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1382:

/* Line 1455 of yacc.c  */
#line 6982 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1383:

/* Line 1455 of yacc.c  */
#line 6983 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1385:

/* Line 1455 of yacc.c  */
#line 6988 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1386:

/* Line 1455 of yacc.c  */
#line 6992 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1387:

/* Line 1455 of yacc.c  */
#line 6993 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1389:

/* Line 1455 of yacc.c  */
#line 6998 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1390:

/* Line 1455 of yacc.c  */
#line 6999 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1391:

/* Line 1455 of yacc.c  */
#line 7000 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1392:

/* Line 1455 of yacc.c  */
#line 7001 "parser.y"
    { (yyval) = cb_build_ppointer ((yyvsp[(4) - (4)])); ;}
    break;

  case 1393:

/* Line 1455 of yacc.c  */
#line 7002 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1398:

/* Line 1455 of yacc.c  */
#line 7010 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1399:

/* Line 1455 of yacc.c  */
#line 7011 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1400:

/* Line 1455 of yacc.c  */
#line 7012 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1406:

/* Line 1455 of yacc.c  */
#line 7024 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1407:

/* Line 1455 of yacc.c  */
#line 7025 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1419:

/* Line 1455 of yacc.c  */
#line 7059 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1420:

/* Line 1455 of yacc.c  */
#line 7067 "parser.y"
    { (yyval) = cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1421:

/* Line 1455 of yacc.c  */
#line 7071 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1422:

/* Line 1455 of yacc.c  */
#line 7072 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1423:

/* Line 1455 of yacc.c  */
#line 7073 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1424:

/* Line 1455 of yacc.c  */
#line 7074 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 1425:

/* Line 1455 of yacc.c  */
#line 7078 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1426:

/* Line 1455 of yacc.c  */
#line 7079 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); CB_REFERENCE ((yyvsp[(1) - (3)]))->chain = (yyvsp[(3) - (3)]); ;}
    break;

  case 1427:

/* Line 1455 of yacc.c  */
#line 7084 "parser.y"
    {
	if (cb_ref ((yyvsp[(0) - (3)])) != cb_error_node) {
		(yyval) = (yyvsp[(0) - (3)]);
		CB_REFERENCE ((yyvsp[(0) - (3)]))->subs = cb_list_reverse ((yyvsp[(2) - (3)]));
	}
  ;}
    break;

  case 1428:

/* Line 1455 of yacc.c  */
#line 7094 "parser.y"
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

  case 1429:

/* Line 1455 of yacc.c  */
#line 7112 "parser.y"
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

  case 1430:

/* Line 1455 of yacc.c  */
#line 7139 "parser.y"
    {
	if (cb_tree_category ((yyvsp[(1) - (1)])) != CB_CATEGORY_NUMERIC) {
		cb_error (_("Integer value expected"));
	} else if (CB_LITERAL ((yyvsp[(1) - (1)]))->sign < 0 || CB_LITERAL ((yyvsp[(1) - (1)]))->scale) {
		cb_error (_("Integer value expected"));
	}
	(yyval) = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1431:

/* Line 1455 of yacc.c  */
#line 7150 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1432:

/* Line 1455 of yacc.c  */
#line 7152 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (2)]);
	if (CB_LITERAL_P ((yyvsp[(2) - (2)]))) {
		CB_LITERAL ((yyvsp[(2) - (2)]))->all = 1;
	}
  ;}
    break;

  case 1433:

/* Line 1455 of yacc.c  */
#line 7161 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1434:

/* Line 1455 of yacc.c  */
#line 7162 "parser.y"
    { (yyval) = cb_concat_literals ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1435:

/* Line 1455 of yacc.c  */
#line 7166 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1436:

/* Line 1455 of yacc.c  */
#line 7167 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 1437:

/* Line 1455 of yacc.c  */
#line 7168 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1438:

/* Line 1455 of yacc.c  */
#line 7169 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 1439:

/* Line 1455 of yacc.c  */
#line 7170 "parser.y"
    { (yyval) = cb_high; ;}
    break;

  case 1440:

/* Line 1455 of yacc.c  */
#line 7171 "parser.y"
    { (yyval) = cb_low; ;}
    break;

  case 1441:

/* Line 1455 of yacc.c  */
#line 7172 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1442:

/* Line 1455 of yacc.c  */
#line 7181 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1443:

/* Line 1455 of yacc.c  */
#line 7185 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1444:

/* Line 1455 of yacc.c  */
#line 7189 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1445:

/* Line 1455 of yacc.c  */
#line 7193 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1446:

/* Line 1455 of yacc.c  */
#line 7197 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1447:

/* Line 1455 of yacc.c  */
#line 7201 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1448:

/* Line 1455 of yacc.c  */
#line 7205 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1449:

/* Line 1455 of yacc.c  */
#line 7209 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1450:

/* Line 1455 of yacc.c  */
#line 7213 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1451:

/* Line 1455 of yacc.c  */
#line 7217 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), NULL);
  ;}
    break;

  case 1452:

/* Line 1455 of yacc.c  */
#line 7221 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1453:

/* Line 1455 of yacc.c  */
#line 7225 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), NULL);
  ;}
    break;

  case 1454:

/* Line 1455 of yacc.c  */
#line 7231 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1455:

/* Line 1455 of yacc.c  */
#line 7232 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (4)]), NULL); ;}
    break;

  case 1456:

/* Line 1455 of yacc.c  */
#line 7233 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 1457:

/* Line 1455 of yacc.c  */
#line 7237 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1458:

/* Line 1455 of yacc.c  */
#line 7238 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1459:

/* Line 1455 of yacc.c  */
#line 7242 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1460:

/* Line 1455 of yacc.c  */
#line 7243 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1461:

/* Line 1455 of yacc.c  */
#line 7249 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_int0);
  ;}
    break;

  case 1462:

/* Line 1455 of yacc.c  */
#line 7256 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int1);
  ;}
    break;

  case 1463:

/* Line 1455 of yacc.c  */
#line 7263 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int2);
  ;}
    break;

  case 1464:

/* Line 1455 of yacc.c  */
#line 7273 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1465:

/* Line 1455 of yacc.c  */
#line 7280 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1466:

/* Line 1455 of yacc.c  */
#line 7290 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1467:

/* Line 1455 of yacc.c  */
#line 7297 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_ref ((yyvsp[(3) - (3)])));
  ;}
    break;

  case 1468:

/* Line 1455 of yacc.c  */
#line 7310 "parser.y"
    {
	non_const_word = 1;
  ;}
    break;

  case 1469:

/* Line 1455 of yacc.c  */
#line 7320 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1470:

/* Line 1455 of yacc.c  */
#line 7321 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1471:

/* Line 1455 of yacc.c  */
#line 7325 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1472:

/* Line 1455 of yacc.c  */
#line 7326 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1473:

/* Line 1455 of yacc.c  */
#line 7330 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1474:

/* Line 1455 of yacc.c  */
#line 7331 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1475:

/* Line 1455 of yacc.c  */
#line 7335 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1476:

/* Line 1455 of yacc.c  */
#line 7336 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1477:

/* Line 1455 of yacc.c  */
#line 7337 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 1478:

/* Line 1455 of yacc.c  */
#line 7341 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1479:

/* Line 1455 of yacc.c  */
#line 7342 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1480:

/* Line 1455 of yacc.c  */
#line 7346 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1481:

/* Line 1455 of yacc.c  */
#line 7347 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1482:

/* Line 1455 of yacc.c  */
#line 7351 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1483:

/* Line 1455 of yacc.c  */
#line 7352 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1484:

/* Line 1455 of yacc.c  */
#line 7356 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1485:

/* Line 1455 of yacc.c  */
#line 7357 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1497:

/* Line 1455 of yacc.c  */
#line 7370 "parser.y"
    { (yyval) = cb_int1; ;}
    break;



/* Line 1455 of yacc.c  */
#line 14706 "parser.c"
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
#line 7414 "parser.y"


