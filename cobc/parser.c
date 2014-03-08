
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
#define YYLAST   5427

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  457
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  702
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1571
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2308

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
    3510,  3513,  3516,  3519,  3522,  3525,  3528,  3531,  3534,  3537,
    3538,  3541,  3544,  3547,  3550,  3553,  3556,  3559,  3562,  3565,
    3568,  3571,  3574,  3577,  3580,  3583,  3586,  3589,  3592,  3595,
    3598,  3601,  3604,  3607,  3610,  3613,  3616,  3619,  3621,  3624,
    3626,  3628,  3631,  3633,  3636,  3638,  3644,  3649,  3651,  3657,
    3662,  3664,  3668,  3669,  3671,  3673,  3675,  3679,  3683,  3687,
    3691,  3694,  3697,  3701,  3705,  3707,  3711,  3713,  3716,  3719,
    3721,  3723,  3725,  3728,  3730,  3732,  3735,  3737,  3738,  3741,
    3743,  3745,  3747,  3751,  3753,  3755,  3758,  3760,  3761,  3763,
    3765,  3767,  3769,  3771,  3774,  3776,  3780,  3782,  3785,  3787,
    3791,  3795,  3799,  3804,  3808,  3810,  3812,  3814,  3816,  3820,
    3824,  3828,  3830,  3832,  3834,  3836,  3838,  3840,  3842,  3844,
    3846,  3848,  3850,  3852,  3854,  3856,  3858,  3860,  3862,  3864,
    3866,  3868,  3870,  3873,  3876,  3880,  3882,  3886,  3890,  3895,
    3901,  3903,  3905,  3908,  3910,  3914,  3916,  3918,  3920,  3922,
    3924,  3926,  3928,  3931,  3934,  3940,  3946,  3952,  3958,  3964,
    3970,  3976,  3981,  3987,  3990,  3991,  3996,  4002,  4003,  4007,
    4008,  4010,  4012,  4016,  4020,  4022,  4026,  4028,  4032,  4033,
    4034,  4036,  4037,  4039,  4040,  4042,  4043,  4045,  4047,  4048,
    4050,  4051,  4053,  4054,  4056,  4057,  4060,  4062,  4064,  4067,
    4070,  4073,  4075,  4078,  4080,  4081,  4083,  4084,  4086,  4087,
    4089,  4090,  4092,  4093,  4095,  4096,  4098,  4099,  4101,  4102,
    4104,  4105,  4107,  4108,  4110,  4111,  4113,  4114,  4116,  4117,
    4119,  4120,  4122,  4123,  4125,  4126,  4128,  4129,  4131,  4132,
    4134,  4136,  4137,  4139,  4140,  4142,  4144,  4145,  4147,  4148,
    4150,  4151,  4153,  4154,  4156,  4157,  4159,  4160,  4162,  4165,
    4166,  4168,  4169,  4171,  4172,  4174,  4175,  4177,  4178,  4180,
    4181,  4183,  4184,  4186,  4189,  4190,  4192,  4193,  4195,  4196,
    4198,  4199,  4201,  4202,  4204,  4205,  4207,  4208,  4210,  4211,
    4213,  4214
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
    1049,  1079,    -1,  1048,   451,    -1,  1049,   274,    -1,  1049,
     267,    -1,  1049,    12,    -1,  1049,    13,    -1,  1049,    14,
      -1,  1049,    58,    -1,  1048,   274,    -1,  1048,   267,    -1,
    1048,    12,    -1,  1048,    13,    -1,  1048,    14,    -1,  1048,
      58,    -1,  1049,   297,    -1,  1049,   253,    -1,  1048,   297,
      -1,  1048,   253,    -1,  1048,   442,    -1,    -1,  1048,   210,
      -1,  1049,   210,    -1,  1049,   452,    -1,  1049,   443,    -1,
    1049,   444,    -1,  1049,   448,    -1,  1049,   257,    -1,  1048,
     257,    -1,  1048,   443,    -1,  1048,   444,    -1,  1048,   445,
      -1,  1048,   446,    -1,  1048,   448,    -1,  1048,  1050,    -1,
    1048,  1051,    -1,  1048,  1052,    -1,  1048,  1053,    -1,  1048,
    1054,    -1,  1048,   252,    -1,  1049,  1050,    -1,  1049,  1051,
      -1,  1049,  1052,    -1,  1049,  1053,    -1,  1049,  1054,    -1,
    1049,   252,    -1,  1048,    20,    -1,  1048,   279,    -1,   450,
      -1,   153,  1156,    -1,   154,    -1,   453,    -1,   187,  1153,
      -1,   454,    -1,   222,  1153,    -1,   181,    -1,   187,  1153,
     279,   153,  1156,    -1,   187,  1153,   153,  1156,    -1,   218,
      -1,   222,  1153,   279,   153,  1156,    -1,   222,  1153,   153,
    1156,    -1,  1057,    -1,  1055,  1056,  1057,    -1,    -1,    69,
      -1,   355,    -1,  1080,    -1,  1057,   443,  1057,    -1,  1057,
     444,  1057,    -1,  1057,   445,  1057,    -1,  1057,   446,  1057,
      -1,   443,  1057,    -1,   444,  1057,    -1,  1057,   448,  1057,
      -1,   452,  1057,   451,    -1,   228,    -1,   228,  1113,   436,
      -1,  1060,    -1,  1059,  1060,    -1,  1079,  1111,    -1,  1090,
      -1,  1090,    -1,  1064,    -1,  1063,  1064,    -1,   436,    -1,
    1066,    -1,  1065,  1066,    -1,   244,    -1,    -1,  1067,  1068,
      -1,  1069,    -1,  1090,    -1,  1070,    -1,  1070,  1113,  1070,
      -1,   232,    -1,  1072,    -1,  1071,  1072,    -1,  1090,    -1,
      -1,  1072,    -1,  1072,    -1,   232,    -1,   436,    -1,  1077,
      -1,  1076,  1077,    -1,  1088,    -1,     6,  1140,  1089,    -1,
    1079,    -1,  1078,  1079,    -1,  1088,    -1,   221,  1140,  1089,
      -1,   221,  1140,  1095,    -1,   221,  1140,  1097,    -1,     6,
    1140,  1081,  1082,    -1,     6,  1140,  1089,    -1,  1094,    -1,
    1097,    -1,  1058,    -1,  1088,    -1,   221,  1140,  1089,    -1,
     221,  1140,  1095,    -1,   221,  1140,  1097,    -1,  1095,    -1,
    1097,    -1,  1058,    -1,   305,    -1,   146,    -1,  1089,    -1,
     232,    -1,  1088,    -1,  1095,    -1,  1088,    -1,  1094,    -1,
    1088,    -1,   232,    -1,  1088,    -1,   232,    -1,  1097,    -1,
    1088,    -1,  1093,    -1,   442,    -1,  1089,    -1,  1090,    -1,
    1090,  1091,    -1,  1090,  1092,    -1,  1090,  1091,  1092,    -1,
     436,    -1,   436,  1113,  1090,    -1,   452,  1055,   451,    -1,
     452,  1057,   455,   451,    -1,   452,  1057,   455,  1057,   451,
      -1,   232,    -1,  1095,    -1,     9,  1096,    -1,  1096,    -1,
    1095,   456,  1096,    -1,   232,    -1,   373,    -1,   442,    -1,
     310,    -1,   191,    -1,   239,    -1,   402,    -1,    96,  1098,
      -1,   433,  1098,    -1,   425,   452,  1057,   451,  1098,    -1,
     237,   452,  1057,   451,  1098,    -1,   337,   452,  1057,   451,
    1098,    -1,    81,   452,  1055,   451,  1098,    -1,   382,   452,
    1055,   451,  1098,    -1,   383,   452,  1055,   451,  1098,    -1,
     407,   452,  1101,   451,  1098,    -1,   269,   452,  1102,   451,
      -1,   234,   452,  1103,   451,  1098,    -1,   180,  1099,    -1,
      -1,   452,  1057,   455,   451,    -1,   452,  1057,   455,  1057,
     451,    -1,    -1,   452,  1100,   451,    -1,    -1,  1055,    -1,
    1057,    -1,  1057,  1056,   219,    -1,  1057,  1056,   405,    -1,
    1057,    -1,  1057,  1056,  1057,    -1,  1057,    -1,  1057,  1056,
    1072,    -1,    -1,    -1,     9,    -1,    -1,  1115,    -1,    -1,
     201,    -1,    -1,   254,    -1,   299,    -1,    -1,   257,    -1,
      -1,   278,    -1,    -1,   343,    -1,    -1,   357,  1125,    -1,
     196,    -1,   272,    -1,   314,  1133,    -1,   316,  1119,    -1,
     435,   119,    -1,   119,    -1,    62,   358,    -1,   358,    -1,
      -1,     7,    -1,    -1,    17,    -1,    -1,    23,    -1,    -1,
      24,    -1,    -1,    27,    -1,    -1,    30,    -1,    -1,    37,
      -1,    -1,    49,    -1,    -1,    55,    -1,    -1,    56,    -1,
      -1,    84,    -1,    -1,    99,    -1,    -1,   400,    -1,    -1,
     172,    -1,    -1,   176,    -1,    -1,   196,    -1,    -1,   210,
      -1,    -1,   210,    -1,    23,    -1,    -1,   214,    -1,    -1,
     229,    -1,   230,    -1,    -1,   230,    -1,    -1,   245,    -1,
      -1,   265,    -1,    -1,   272,    -1,    -1,   275,    -1,    -1,
     280,    -1,   196,   280,    -1,    -1,   282,    -1,    -1,   305,
      -1,    -1,   314,    -1,    -1,   341,    -1,    -1,   360,    -1,
      -1,   362,    -1,    -1,   362,    -1,   362,   210,    -1,    -1,
     367,    -1,    -1,   379,    -1,    -1,   390,    -1,    -1,   393,
      -1,    -1,   394,    -1,    -1,   397,    -1,    -1,   398,    -1,
      -1,   432,    -1,    -1,   435,    -1
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
    6658,  6659,  6661,  6662,  6663,  6664,  6665,  6666,  6668,  6669,
    6670,  6671,  6672,  6673,  6675,  6676,  6678,  6679,  6680,  6683,
    6685,  6686,  6687,  6689,  6690,  6691,  6693,  6694,  6696,  6697,
    6698,  6699,  6700,  6702,  6703,  6704,  6705,  6706,  6707,  6709,
    6710,  6711,  6712,  6713,  6714,  6716,  6717,  6720,  6720,  6720,
    6721,  6721,  6722,  6722,  6723,  6723,  6723,  6724,  6724,  6724,
    6729,  6730,  6733,  6734,  6735,  6739,  6740,  6741,  6742,  6743,
    6744,  6745,  6746,  6747,  6758,  6770,  6785,  6786,  6791,  6797,
    6819,  6839,  6843,  6859,  6873,  6874,  6879,  6885,  6886,  6891,
    6900,  6901,  6902,  6906,  6917,  6918,  6922,  6930,  6931,  6935,
    6936,  6942,  6962,  6963,  6967,  6968,  6972,  6973,  6977,  6978,
    6979,  6980,  6981,  6982,  6983,  6984,  6985,  6989,  6990,  6991,
    6992,  6993,  6994,  6995,  6999,  7000,  7004,  7005,  7009,  7010,
    7014,  7015,  7026,  7027,  7031,  7032,  7033,  7037,  7038,  7039,
    7047,  7051,  7052,  7053,  7054,  7058,  7059,  7063,  7073,  7091,
    7118,  7130,  7131,  7141,  7142,  7146,  7147,  7148,  7149,  7150,
    7151,  7152,  7160,  7164,  7168,  7172,  7176,  7180,  7184,  7188,
    7192,  7196,  7200,  7204,  7211,  7212,  7213,  7217,  7218,  7222,
    7223,  7228,  7235,  7242,  7252,  7259,  7269,  7276,  7290,  7300,
    7301,  7305,  7306,  7310,  7311,  7315,  7316,  7317,  7321,  7322,
    7326,  7327,  7331,  7332,  7336,  7337,  7344,  7344,  7345,  7345,
    7346,  7346,  7347,  7347,  7349,  7349,  7350,  7350,  7351,  7351,
    7352,  7352,  7353,  7353,  7354,  7354,  7355,  7355,  7356,  7356,
    7357,  7357,  7358,  7358,  7359,  7359,  7360,  7360,  7361,  7361,
    7362,  7362,  7363,  7363,  7364,  7364,  7365,  7365,  7366,  7366,
    7366,  7367,  7367,  7368,  7368,  7368,  7369,  7369,  7370,  7370,
    7371,  7371,  7372,  7372,  7373,  7373,  7374,  7374,  7374,  7375,
    7375,  7376,  7376,  7377,  7377,  7378,  7378,  7379,  7379,  7380,
    7380,  7381,  7381,  7381,  7382,  7382,  7383,  7383,  7384,  7384,
    7385,  7385,  7386,  7386,  7387,  7387,  7388,  7388,  7390,  7390,
    7391,  7391
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
    1048,  1048,  1048,  1048,  1048,  1048,  1048,  1048,  1048,  1049,
    1049,  1049,  1049,  1049,  1049,  1049,  1049,  1049,  1049,  1049,
    1049,  1049,  1049,  1049,  1049,  1049,  1049,  1049,  1049,  1049,
    1049,  1049,  1049,  1049,  1049,  1049,  1049,  1050,  1050,  1050,
    1051,  1051,  1052,  1052,  1053,  1053,  1053,  1054,  1054,  1054,
    1055,  1055,  1056,  1056,  1056,  1057,  1057,  1057,  1057,  1057,
    1057,  1057,  1057,  1057,  1058,  1058,  1059,  1059,  1060,  1061,
    1062,  1063,  1063,  1064,  1065,  1065,  1066,  1067,  1067,  1068,
    1069,  1069,  1069,  1070,  1071,  1071,  1072,  1073,  1073,  1074,
    1074,  1075,  1076,  1076,  1077,  1077,  1078,  1078,  1079,  1079,
    1079,  1079,  1079,  1079,  1079,  1079,  1079,  1080,  1080,  1080,
    1080,  1080,  1080,  1080,  1081,  1081,  1082,  1082,  1083,  1083,
    1084,  1084,  1085,  1085,  1086,  1086,  1086,  1087,  1087,  1087,
    1088,  1089,  1089,  1089,  1089,  1090,  1090,  1091,  1092,  1092,
    1093,  1094,  1094,  1095,  1095,  1096,  1096,  1096,  1096,  1096,
    1096,  1096,  1097,  1097,  1097,  1097,  1097,  1097,  1097,  1097,
    1097,  1097,  1097,  1097,  1098,  1098,  1098,  1099,  1099,  1100,
    1100,  1101,  1101,  1101,  1102,  1102,  1103,  1103,  1104,  1105,
    1105,  1106,  1106,  1107,  1107,  1108,  1108,  1108,  1109,  1109,
    1110,  1110,  1111,  1111,  1112,  1112,  1113,  1113,  1114,  1114,
    1115,  1115,  1116,  1116,  1117,  1117,  1118,  1118,  1119,  1119,
    1120,  1120,  1121,  1121,  1122,  1122,  1123,  1123,  1124,  1124,
    1125,  1125,  1126,  1126,  1127,  1127,  1128,  1128,  1129,  1129,
    1130,  1130,  1131,  1131,  1132,  1132,  1133,  1133,  1134,  1134,
    1134,  1135,  1135,  1136,  1136,  1136,  1137,  1137,  1138,  1138,
    1139,  1139,  1140,  1140,  1141,  1141,  1142,  1142,  1142,  1143,
    1143,  1144,  1144,  1145,  1145,  1146,  1146,  1147,  1147,  1148,
    1148,  1149,  1149,  1149,  1150,  1150,  1151,  1151,  1152,  1152,
    1153,  1153,  1154,  1154,  1155,  1155,  1156,  1156,  1157,  1157,
    1158,  1158
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     0,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     1,     2,     1,
       1,     2,     1,     2,     1,     5,     4,     1,     5,     4,
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
      27,    29,    29,     0,   263,   263,     0,     0,    24,    40,
       0,     9,    15,    30,    26,  1516,     0,   157,     0,   604,
     604,  1517,     0,     0,     0,     0,     0,     0,    39,   265,
       0,    17,     0,    25,    33,    37,    36,  1541,    35,    42,
     159,     0,   161,   275,   276,     0,   327,   268,   608,    18,
      20,    38,     0,    16,    34,  1542,    32,    41,   165,   163,
     244,     0,     0,   452,     0,   611,   609,   626,     0,    19,
      10,    11,     0,     0,     0,     0,     0,    43,    44,    45,
      47,    46,   160,     0,   242,     0,  1508,   252,   162,     0,
     246,   248,   249,   250,   266,     0,     0,   455,  1353,   269,
     330,   277,   616,   616,     0,     0,     0,   263,    23,    56,
      71,    49,    80,  1470,   166,   165,     0,   158,  1534,  1509,
    1558,   253,   254,   255,  1490,   245,   247,   270,   328,     0,
       0,   458,   274,     0,   273,   331,  1458,   279,  1499,   616,
     613,   619,     0,   616,   627,   605,    21,    12,     0,  1516,
      54,  1541,    55,  1541,    60,    62,    63,    64,     0,     0,
      70,     0,    73,  1571,    48,     0,  1570,     0,     0,  1516,
    1516,     0,     0,  1549,  1516,  1516,  1516,  1516,  1516,     0,
    1516,  1502,  1516,    79,    81,    83,    85,    86,    87,    89,
      88,    90,    91,    92,    93,    94,    95,  1471,     0,   164,
     244,  1535,     0,  1559,  1504,  1491,  1510,   267,   330,   453,
       0,     0,   550,   330,   333,     0,     0,   614,  1516,     0,
     624,   617,   618,   628,   604,  1516,     0,    57,  1541,    59,
      61,     0,  1483,  1516,     0,    77,     0,    72,    74,    52,
      50,     0,     0,  1371,   112,     0,     0,  1516,  1516,  1550,
    1516,     0,     0,     0,     0,     0,  1516,     0,  1503,     0,
      99,    82,    84,   167,   243,  1415,   262,  1364,  1366,  1505,
       0,  1511,     0,   271,   329,   330,   456,     0,     0,   264,
     272,   336,     0,   342,   343,   334,   346,   346,   337,   292,
    1504,  1516,     0,     0,  1516,  1504,  1528,  1516,  1488,     0,
     278,   280,   283,   284,   285,   286,   287,   288,   289,   290,
     291,     0,     0,  1516,   625,     0,     0,   606,    17,     0,
    1420,    69,    58,  1482,     0,    76,    75,    78,    51,    53,
    1516,   101,   102,     0,     0,     0,   153,   152,   103,   104,
     156,     0,   155,   139,  1518,   141,    96,     0,    97,   169,
    1476,  1477,     0,  1365,   256,   257,   260,   251,  1351,   454,
     330,   459,     0,   335,   347,   348,   338,     0,   348,   340,
       0,     0,  1516,  1488,     0,     0,     0,     0,     0,  1529,
    1516,     0,  1489,     0,     0,   281,   282,   620,   621,   623,
       0,   615,   629,   631,     0,     0,    68,     0,  1429,  1425,
    1430,  1428,  1426,  1431,  1427,   145,   146,   148,   154,   151,
     150,  1520,  1519,   142,     0,   111,   110,   100,   107,  1556,
     105,     0,  1416,   258,     0,   259,  1352,   457,   461,   551,
     356,   350,     0,   304,   324,  1478,  1479,   313,   308,   307,
     306,  1370,  1369,  1526,  1502,  1514,     0,   549,   325,   326,
    1516,  1516,   622,   631,     0,     0,    13,    66,    67,    65,
     117,   131,   127,   132,   114,   130,   128,   115,   116,   129,
     113,   118,   119,   121,   147,     0,   140,   143,   108,  1557,
    1516,    98,   184,  1528,     0,  1566,   227,     0,  1528,  1516,
    1500,  1521,   230,     0,   229,  1570,   214,   213,   168,   170,
     171,   172,   173,   174,   175,     0,   176,   177,   226,   178,
     179,   180,   181,   182,   183,  1516,   261,     0,   460,   462,
     463,   552,     0,  1492,     0,  1518,   341,     0,   294,  1527,
     315,     0,   297,  1515,  1554,   323,     0,     0,     0,   637,
     641,   632,   633,   634,   635,   640,     0,     0,   120,   123,
       0,   149,   144,     0,   106,  1516,  1521,  1567,   191,   231,
    1516,     0,  1501,  1516,  1497,  1516,  1522,     0,  1516,  1516,
    1490,     0,  1516,     0,   466,   464,   554,   372,     0,   439,
     381,   414,   402,   411,   408,   405,  1568,   382,   383,   384,
     385,   386,   387,   388,   389,   390,  1545,   345,   415,     0,
     391,   378,   392,   393,     0,     0,  1552,   395,   396,   394,
     435,   398,   399,   397,  1516,  1516,   339,   357,   358,   359,
     360,   361,   362,   379,   363,   364,   365,   366,   367,   368,
     369,   370,   371,     0,     0,  1493,     0,   351,     0,   305,
     296,   295,   293,   314,  1502,  1555,   302,   311,   310,   312,
     309,     0,   639,   642,   699,   750,   759,   766,   770,   794,
     798,   816,   809,   817,   818,   824,   857,   866,   868,   895,
     903,   905,  1566,   911,     0,   922,   943,   945,   981,   983,
     987,   698,   993,  1006,  1026,  1043,  1045,  1049,  1056,  1057,
    1073,  1093,  1111,     0,  1129,  1140,  1148,  1150,  1152,  1154,
    1159,  1181,  1204,   636,   648,   649,   650,   651,   652,   653,
     654,   655,   657,   656,   658,   659,   660,   661,   662,   663,
     664,   665,   666,   667,   668,   669,   670,   671,   672,   673,
     674,   675,   676,   677,   678,   679,   680,   681,   682,   683,
     684,   685,   686,   687,   688,   689,   690,   691,   692,   693,
     694,   695,   696,  1177,  1178,  1179,   697,    22,     0,   122,
     109,     0,  1516,   193,   192,   188,     0,  1496,   230,   225,
       0,     0,   228,     0,     0,   237,  1539,  1539,     0,   238,
       0,   210,  1516,   346,   558,   553,   555,   556,   451,   412,
     413,   400,   401,   409,   410,   406,   407,   403,   404,  1569,
       0,  1546,   433,   419,   373,  1411,   449,  1553,   436,   437,
     434,     0,     0,   375,   377,  1474,  1474,     0,  1532,  1532,
     355,   352,  1421,  1423,   441,   443,   445,  1495,   316,   317,
     318,   319,     0,     0,   298,  1513,   304,     0,     0,   643,
       0,     0,     0,  1268,   765,     0,   796,   800,     0,     0,
       0,     0,     0,     0,  1268,   897,     0,     0,   907,   912,
       0,  1268,     0,     0,     0,     0,     0,     0,   995,  1016,
       0,     0,     0,     0,     0,     0,     0,     0,  1125,  1123,
       0,     0,  1149,  1147,     0,     0,     0,     0,  1182,  1188,
       0,     0,   137,   133,   138,   136,   134,   135,   124,   125,
     199,   200,   198,   197,     0,   186,   187,     0,   219,   218,
     219,   215,   232,   233,   234,   236,  1540,   239,   240,   241,
    1367,  1516,   475,   475,  1518,   495,   467,   470,   471,     0,
     559,   557,   438,     0,  1564,     0,  1412,  1413,     0,   380,
     440,     0,   374,  1500,   416,   417,  1422,  1533,     0,     0,
       0,  1568,   444,     0,     0,     0,  1494,  1502,   303,   630,
     638,   748,   718,  1410,  1532,     0,     0,  1444,  1447,  1532,
    1344,     0,     0,     0,     0,     0,     0,     0,     0,  1444,
     757,  1386,   755,  1376,  1378,  1384,  1385,  1463,   760,     0,
    1267,  1289,  1363,     0,  1359,  1361,  1360,  1405,   772,  1404,
    1406,   795,   799,   812,     0,  1346,  1472,  1543,     0,  1425,
     855,   718,     0,  1378,   864,     0,   772,   874,   873,  1486,
     870,   872,   902,   899,   898,   901,   896,  1532,   904,  1372,
    1374,   906,  1357,   916,  1562,  1266,   924,   944,   477,     0,
     947,   948,   949,   982,  1097,     0,   984,     0,   991,     0,
     994,  1017,  1363,  1007,  1016,  1009,     0,  1014,     0,  1360,
       0,  1465,  1206,  1349,  1543,  1206,     0,  1071,  1062,  1350,
       0,  1356,  1074,  1075,  1076,  1077,  1078,  1086,  1079,  1089,
       0,  1354,     0,  1094,  1112,  1126,  1498,     0,  1131,  1133,
       0,  1145,     0,  1151,     0,  1156,  1161,  1189,     0,  1190,
    1534,  1206,     0,  1461,   195,   194,   185,   196,     0,   217,
     216,  1516,   209,   203,  1368,   211,     0,   476,   472,     0,
     473,     0,   465,   468,   561,   420,  1565,   421,  1532,     0,
       0,     0,  1332,  1330,  1393,  1335,  1387,  1391,  1392,     0,
    1414,   450,   376,  1475,   354,   353,  1424,  1547,   446,   322,
    1526,     0,   300,   749,   700,  1495,     0,   727,     0,     0,
       0,     0,     0,  1432,  1449,  1443,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1433,   758,   751,     0,
       0,  1377,  1464,   763,  1463,  1269,     0,   768,     0,   773,
     783,  1403,   797,  1402,   802,   813,   810,   815,   814,  1268,
    1347,  1473,  1348,  1544,  1255,   823,   856,   825,   835,  1221,
    1221,  1221,  1221,   865,   858,     0,     0,   867,  1487,  1268,
     893,   880,   876,   878,  1268,   900,     0,  1373,   909,  1563,
     914,   926,     0,   478,     0,   970,   955,   946,   950,   952,
     953,   954,  1101,     0,     0,   992,   988,     0,  1000,   997,
     999,   998,  1001,  1008,  1011,   644,  1268,     0,     0,  1018,
       0,  1466,  1467,  1543,     0,  1044,  1028,  1051,  1064,  1072,
    1058,     0,  1064,     0,  1398,  1399,  1087,  1090,     0,     0,
    1355,  1085,     0,  1084,     0,  1114,     0,     0,  1124,     0,
       0,  1132,     0,  1146,  1141,     0,     0,  1157,  1158,  1155,
    1498,     0,     0,  1191,     0,     0,  1051,   126,  1481,     0,
     203,   201,  1462,     0,   222,   208,   235,     0,   469,   474,
     480,   490,   346,   496,  1551,  1534,   424,     0,  1340,  1341,
       0,  1333,  1334,  1417,     0,     0,     0,     0,     0,     0,
       0,     0,  1548,  1566,   321,  1526,  1534,   299,   723,   714,
    1221,   704,   711,   705,   707,   709,     0,  1221,     0,   703,
     710,   717,   716,     0,  1221,  1530,  1530,  1530,   721,   722,
    1395,  1394,     0,  1383,  1332,  1330,     0,     0,  1332,     0,
    1379,  1380,  1381,  1345,  1332,     0,     0,  1332,     0,     0,
    1332,  1332,  1332,     0,     0,  1228,  1472,     0,     0,   761,
       0,  1280,  1281,  1282,  1315,  1283,  1566,  1319,  1324,  1560,
    1290,  1327,  1560,  1308,  1287,  1297,  1279,  1278,  1316,  1286,
    1288,  1298,  1299,  1300,  1301,  1302,  1317,  1271,  1320,  1322,
    1303,  1304,  1305,  1306,  1307,  1274,  1275,  1276,  1277,  1291,
    1314,  1285,  1296,  1273,  1272,  1284,  1293,  1294,  1295,  1292,
    1309,  1310,  1311,  1312,  1313,  1270,     0,     0,  1362,   779,
       0,     0,   786,   807,   808,   801,   803,     0,  1228,  1260,
    1262,   820,  1256,  1257,  1258,     0,  1571,  1221,     0,  1222,
     828,  1224,   829,   826,   827,     0,  1228,  1472,   888,   890,
     889,   883,   885,   891,   894,   869,   881,   877,   875,  1268,
     644,   871,  1375,  1534,   908,  1358,   644,  1566,   934,   935,
     937,   939,   940,   936,   938,   929,  1566,   925,     0,   971,
       0,   973,   972,   974,   965,   966,     0,     0,   951,  1103,
    1536,     0,     0,   985,  1228,  1472,  1570,     0,  1012,   645,
    1019,  1020,  1023,     0,  1015,  1213,  1212,  1022,  1028,  1207,
       0,     0,  1255,     0,     0,     0,  1063,     0,     0,     0,
    1088,     0,  1092,  1091,  1082,     0,  1516,  1255,  1128,  1127,
    1134,  1135,  1136,     0,  1228,  1472,     0,  1459,     0,  1136,
    1203,  1193,  1192,  1198,     0,  1200,  1201,  1208,  1480,  1461,
       0,   205,   206,   204,  1516,   482,   493,   494,   492,   498,
     574,  1516,   565,   563,   564,   566,  1530,     0,  1516,     0,
     577,   569,  1530,   570,     0,   573,   578,   576,   571,   575,
       0,   572,     0,   560,   588,   583,   586,   585,   584,   587,
     562,   589,     0,   428,   423,  1388,  1389,  1390,  1343,  1331,
    1336,  1337,  1338,  1339,  1342,  1418,     0,   447,   320,     0,
     715,  1224,   706,   708,  1221,   712,   702,   742,  1516,   731,
     732,  1516,   743,   733,   734,   737,   747,   744,   735,     0,
     745,   736,   746,   728,   729,   701,  1531,     0,     0,     0,
     719,   720,  1397,  1382,  1396,  1444,  1472,     0,  1448,     0,
    1444,  1444,     0,  1441,  1444,  1444,  1444,     0,  1444,  1444,
    1229,   752,  1231,  1228,   764,     0,  1318,  1561,  1321,  1323,
     769,   767,   774,   775,   619,     0,   785,   784,  1194,  1195,
     789,   787,     0,   806,     0,   811,   644,   644,   821,   819,
    1259,   835,   835,   835,   835,  1516,   840,   853,   854,   841,
       0,  1516,   844,   845,   848,   846,     0,   847,   837,   838,
     830,   836,   644,  1225,  1220,     0,   859,     0,  1268,  1268,
     887,   644,   884,   879,     0,   917,     0,     0,   941,     0,
       0,     0,   967,   969,     0,   961,   977,   962,   963,   956,
     957,   977,  1095,  1516,     0,  1537,  1102,   426,   427,  1521,
     986,   989,     0,     0,  1003,  1013,  1010,   647,     0,     0,
    1030,  1029,  1244,  1246,  1047,  1241,  1242,  1054,  1052,     0,
    1268,  1065,  1268,  1059,  1067,  1080,  1081,  1083,  1468,  1121,
    1235,     0,  1472,  1142,     0,     0,  1460,  1162,  1163,     0,
    1166,  1169,  1173,  1167,  1199,  1534,  1202,  1214,  1484,   202,
       0,   223,   224,   220,     0,     0,   484,     0,  1551,     0,
    1516,   567,   568,     0,   591,  1516,  1564,   592,   590,   422,
    1498,   418,  1521,  1419,  1516,   442,   301,  1219,   713,     0,
       0,  1264,  1264,   730,   725,   724,   726,  1437,  1228,  1445,
       0,  1457,  1442,  1435,  1455,  1436,  1438,  1439,  1452,  1453,
    1440,  1434,   644,  1232,  1227,   753,   762,  1566,     0,  1566,
       0,   776,   777,     0,   781,   780,   782,  1196,  1197,   792,
     790,   644,   804,   805,  1261,  1263,  1221,  1221,  1221,  1221,
       0,   842,   843,     0,  1264,  1264,   839,  1223,   644,  1228,
    1346,  1228,  1346,   886,   892,   882,   910,   918,   920,   927,
     930,   931,  1506,   942,   923,   928,   977,  1400,  1401,   977,
       0,   960,   958,   959,   964,  1105,     0,  1538,  1099,  1228,
    1002,   996,     0,   646,  1024,     0,     0,  1036,     0,   644,
     644,  1048,  1046,  1243,  1055,  1050,  1053,  1060,   644,  1069,
    1068,  1469,     0,     0,  1122,  1113,  1236,  1138,  1238,     0,
    1228,  1228,  1153,  1459,  1165,  1514,  1171,  1514,  1235,     0,
    1251,  1253,  1217,  1215,  1248,  1249,  1216,  1485,     0,   221,
     481,  1516,     0,   486,   491,  1530,   527,   547,   542,  1488,
       0,     0,  1516,  1532,  1516,     0,   497,   503,   504,   505,
     514,   506,   508,   511,   499,   500,   501,   507,   510,   528,
     512,   515,   502,     0,   509,   513,  1409,   582,  1407,  1408,
     598,   581,   593,   603,     0,  1516,     0,   739,   738,   741,
       0,   740,   754,  1446,  1230,   644,  1326,  1566,  1329,  1566,
     778,   793,   771,   644,   788,   834,   833,   832,   831,   850,
     849,   852,   851,  1226,   861,     0,   860,     0,   644,   921,
     915,   932,  1507,     0,   976,   968,   977,   979,     0,     0,
    1108,  1104,  1098,   990,  1005,     0,     0,  1031,  1516,  1038,
       0,  1032,     0,  1035,  1245,  1247,   644,  1066,   644,  1115,
    1116,  1117,  1118,  1119,  1120,   644,  1139,  1130,  1239,  1234,
    1137,  1144,  1143,  1164,     0,  1514,  1168,     0,  1175,  1187,
    1184,  1186,  1185,  1180,  1183,   644,   644,  1218,  1205,  1250,
    1211,  1210,  1523,     0,  1516,  1516,   488,   526,  1516,   548,
     546,   543,   544,  1518,   536,  1516,  1268,     0,     0,     0,
       0,   529,     0,     0,   534,   537,   540,   601,   599,   600,
     602,     0,   596,   594,   595,   597,     0,   432,   429,   430,
       0,   448,  1523,  1233,  1325,  1328,   791,  1228,  1228,   919,
       0,   975,   980,     0,  1516,  1106,     0,     0,  1096,  1100,
    1004,     0,     0,  1041,  1039,  1040,  1034,  1033,  1061,  1070,
    1237,   644,  1170,     0,  1174,  1176,  1160,  1252,  1254,  1524,
    1525,  1209,   483,     0,     0,  1516,   479,     0,   535,     0,
     532,  1472,   530,   531,   521,   519,   520,   522,   518,   523,
     517,   516,     0,   541,   539,   538,   580,   579,   431,   425,
    1265,   863,   862,   933,   978,     0,  1109,  1516,  1268,  1037,
    1042,  1027,  1240,  1172,   485,   487,     0,   525,   524,   545,
       0,  1107,     0,  1025,   489,     0,  1110,   533
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
     520,   927,   785,  1126,   521,   923,   522,  1336,  1337,  1611,
    1133,   523,   524,   525,   526,   931,  1129,  1863,   527,   528,
     529,   530,   531,   532,   533,   534,   799,   137,   108,   109,
     110,   111,   144,   112,   374,   375,   445,   113,    31,    66,
     147,    84,   227,   152,   119,   153,   120,   157,   236,   321,
     322,   662,   323,  1367,   856,   548,   324,   460,   325,   668,
     326,   327,   663,   848,   849,   850,   851,   328,   329,   330,
      83,   228,   154,   155,   156,   234,   305,   450,   452,   306,
     307,   636,   386,   387,   543,   840,   308,   542,   637,   638,
     639,   962,   640,   641,   642,   643,   644,   645,   954,  1346,
    1653,  1654,  1809,  1881,  2208,  2209,   646,   647,   830,   648,
     649,   650,   546,   971,   844,   845,  1885,   651,   652,   117,
     295,   151,   380,   232,   448,   538,   539,   540,   802,   946,
     947,  1138,  1139,  1057,   948,  1615,  1866,  2033,  2176,  2256,
    1340,  1618,  1142,  1343,  1868,  2054,  2055,  2271,  2056,  2057,
    2058,  2059,  2262,  2060,  2061,  2062,  2063,  2194,  2195,  2183,
    2064,  2065,  2180,   468,   299,   541,   596,   805,   806,   807,
    1144,  1344,  1650,  2206,  2201,  1651,    51,   243,   413,    87,
     123,   122,   159,   160,   161,   240,   335,   125,   337,   473,
     474,   561,   562,   563,   564,   565,   860,  1558,  1559,  1817,
     566,   724,   725,   861,   981,  1177,  1388,  1389,  1384,  1693,
    1694,  1174,   726,   862,  1000,  1200,  1198,   727,   863,  1008,
    1419,   728,   864,  1477,   729,   865,  1210,  1479,  1732,  1733,
    1734,  1482,  1740,  1931,  1929,  2093,  2092,   730,   866,  1021,
     731,   867,  1022,  1485,  1486,   732,   868,  1023,  1216,  1219,
     733,   734,   735,   869,  1749,   736,   870,   737,   871,  1030,
    1497,  1768,  1769,  1227,   738,   872,  1034,  1234,   739,   873,
     740,   874,  1039,  1040,  1240,  1241,  1242,  1520,  1518,  1781,
    1243,  1511,  1512,  1780,  1515,   741,   875,  1046,   742,   876,
     743,   877,   744,  1052,  1524,   745,   879,   746,   881,  1526,
    1958,  2108,  2110,   747,   882,  1251,  1535,  1788,  1960,  1961,
    1962,  1964,   748,   883,   749,   884,  1059,  1257,  1258,  1259,
    1547,  1799,  1800,  1260,  1544,  1545,  1546,  1793,  1261,  1971,
    2223,   750,   885,   751,   886,  1066,   752,   887,  1068,  1266,
     753,   888,  1070,  1272,  1557,  1981,   754,   889,  1073,  1275,
    1816,  1074,  1075,  1076,  1561,  1562,   755,   890,  1571,  1987,
    2129,  2233,  2291,   756,   891,   757,   892,  1992,   758,   893,
    1572,  1995,   759,   760,   894,  1087,  2136,  1292,  1574,  1998,
    1833,  1834,  2138,  1290,   761,   895,  1092,  1093,  1094,  1095,
    1304,  1096,  1097,  1098,  1099,   762,   896,  1063,  1975,  1262,
    2122,  1549,  1802,  2120,  2228,   763,   897,  1305,  1587,  2002,
    2005,   764,  1105,  1308,   765,   900,  1107,  1108,  1840,  2147,
     766,   901,  1111,  1314,   767,   903,   768,   904,   769,   905,
     770,   906,  1319,   771,   907,  1321,  1847,  1848,  1599,  1850,
    2016,  2156,  2018,  2246,   772,   773,   909,  2163,  1119,  1324,
    1603,  1741,  1930,  1855,   774,  1605,   775,   776,   911,  1285,
    1857,  2117,  2022,  2168,  1670,  1500,  1501,  1772,  1774,  1948,
    1721,  1722,  1912,  1914,  2085,  2007,  2008,  2145,  2149,  2241,
    1824,  1825,  1989,  1826,  1990,  2023,  2024,  2165,  2025,  2166,
    1491,  1492,  1493,  1746,  1494,  1747,  2079,  1054,  1055,  1010,
    1011,  1205,  1206,  1450,  1451,  1452,  1453,  1454,  1152,  1354,
    1395,  1001,  1024,  1220,  1082,  1088,   377,   378,  1100,  1101,
    1248,  1077,  1014,  1015,   286,   462,  1135,   463,   264,  1048,
    1049,  1002,  1026,  1155,  1392,  1703,  1801,  1966,  1032,  1078,
    2067,  1004,   983,   825,   956,   957,  2069,  1005,   842,   843,
    1006,  1183,  1185,  1399,  1413,  1408,  1405,   235,  1849,  1331,
    1203,  1283,  2003,   218,  1222,   964,   372,   394,  1332,   253,
    2028,  1778,   403,   226,   656,  1178,   587,   162,   583,   279,
     290,  2113,   140,   292,   857,   554,    43,   434,   588,  2251,
     550,   400,  1697,   968,   222,  1806,   937,   178,  1224,   822,
    1363,   270,   654,   666,   500,   224,  1728,  1250,  1147,   578,
     820,  1498
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1747
static const yytype_int16 yypact[] =
{
   -1747,   227,    29, -1747,  -194,   203,   387, -1747, -1747, -1747,
     498,   498,   562,   562, -1747, -1747,   547, -1747, -1747, -1747,
   -1747,   660,   660,   262,   634,   634,   599,   478, -1747,   813,
     819, -1747, -1747, -1747, -1747,   -47,   618,   934,   506,   685,
     685, -1747,   554,   144,   681,   684,   785,   690, -1747,   206,
     946,   852,  1025, -1747,   502, -1747, -1747,   878, -1747, -1747,
   -1747,   739, -1747, -1747, -1747,   853,   782, -1747,    62, -1747,
      33,   498,   562, -1747, -1747, -1747, -1747,   721, -1747,  1061,
     128,   783,   901,  1041,   843, -1747, -1747,   952,   562, -1747,
   -1747, -1747,   876,   886,   893,   894,   904, -1747, -1747, -1747,
   -1747, -1747,   948,   910,  1140,  1285,   960,   704, -1747,    34,
   -1747, -1747, -1747, -1747, -1747,   914,  1014,  1133, -1747,   460,
     971, -1747,    40,    40,   932,   918,   924,   634, -1747,   738,
    1194,   121,  1180,  1096, -1747, -1747,   927, -1747,  1102, -1747,
     989, -1747, -1747, -1747,  1356, -1747, -1747, -1747, -1747,   937,
    1036,  1064, -1747,   843, -1747, -1747, -1747, -1747, -1747,   142,
   -1747,  -107,  -102,   164, -1747, -1747, -1747, -1747,  1026,  1184,
   -1747,   -71, -1747,   429, -1747, -1747, -1747, -1747,    61,   171,
   -1747,   -40, -1747, -1747, -1747,   947,   596,  1293,   962,  1184,
    1184,   962,  1021,  1040,  1184,  1184,  1184,  1184,  1184,   962,
    1184,  1348,  1184, -1747,  1087, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,   962,   948,
     128, -1747,   975, -1747,  1330, -1747,  1248,   460,   971, -1747,
     972,  1071,  1079,   971,    98,  1018,   851, -1747,  1184,  1057,
    1150, -1747, -1747,  1324,   685,  1184,  1199, -1747,   448, -1747,
   -1747,  1077, -1747,  1184,  1229, -1747,   672, -1747, -1747, -1747,
   -1747,   988,  1196, -1747, -1747,   962,   962,  1184,  1184, -1747,
    1184,   975,  1376,   962,   962,   975,  1184,   975, -1747,   962,
     -20, -1747, -1747, -1747, -1747,     8,   975, -1747, -1747, -1747,
     843, -1747,   843, -1747, -1747,   971, -1747,   998,  1099, -1747,
   -1747, -1747,  1018, -1747, -1747, -1747,   -32,   -26, -1747, -1747,
    1330,  1184,   856,   856,  1184,    30,  1207,  1184,  1431,  1183,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747,    74,   625,  1184, -1747,  1023,  1015, -1747,   852,  1199,
   -1747, -1747, -1747, -1747,   975, -1747, -1747, -1747, -1747, -1747,
    1184, -1747, -1747,   668,   975,  1234, -1747, -1747, -1747, -1747,
   -1747,   975, -1747, -1747,    63, -1747, -1747,   928, -1747, -1747,
   -1747, -1747,   975, -1747,   843, -1747,  1172,   843, -1747, -1747,
     971, -1747,  1024, -1747, -1747,  1387, -1747,  1392, -1747, -1747,
    1199,  1042,  1184,  1431,   975,   368,     4,  1199,  1049, -1747,
    1184,  1045, -1747,  1045,   124, -1747, -1747, -1747, -1747, -1747,
    1199, -1747, -1747, -1747,    56,   112, -1747,   913, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747,   668, -1747,  1081, -1747, -1747,
   -1747, -1747, -1747, -1747,  1199, -1747, -1747,   928, -1747,  1105,
   -1747,   957, -1747, -1747,  1199, -1747, -1747, -1747,  1171, -1747,
   -1747,   773,  1056,  1090, -1747, -1747, -1747,   975, -1747, -1747,
   -1747, -1747, -1747,  1257,    81,  1294,  1058, -1747, -1747, -1747,
    1184,  1184, -1747, -1747,  2666,   562, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747,   977, -1747,    79, -1747,   668,  1199, -1747, -1747, -1747,
    1184,   928, -1747,  1207,  1178,  1108, -1747,  1143,  1207,  1184,
    1444,   340,   -70,  1199, -1747,  1074, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747,  1124, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747,  1184, -1747,  1045, -1747,  1171,
   -1747, -1747,  2536,  1485,  1332,   187, -1747,  1199,   125, -1747,
   -1747,  1199, -1747, -1747,  1147, -1747,    96,    96,  2951, -1747,
    1069, -1747, -1747, -1747, -1747,  1168,  3576,  1072, -1747, -1747,
     977, -1747, -1747,   962, -1747,  1184,  1308, -1747,   578, -1747,
    1184,   696, -1747,  1184, -1747,  1184, -1747,  1170,  1184,  1184,
    1356,   256,  1184,  1094, -1747, -1747,  1315, -1747,  1310, -1747,
   -1747,   604,   608,   617,   674,   691,  1107, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747,  1201, -1747, -1747,  1199,
   -1747, -1747, -1747, -1747,   975,   975,  1333, -1747, -1747, -1747,
     -17, -1747, -1747, -1747,  1184,  1184, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747,   849,    -4, -1747,   217, -1747,   248, -1747,
   -1747, -1747, -1747,   105,  1348, -1747,   453, -1747, -1747, -1747,
   -1747,  1439, -1747,  1314, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747,  1151, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747,  1108, -1747,  2062, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747,   406, -1747, -1747,  1252, -1747, -1747, -1747,
   -1747,   892, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,  1078, -1747,
   -1747,    36,  1184, -1747, -1747,   467,   635,  1523, -1747, -1747,
       4,  1185, -1747,   975,   975, -1747,  1280,  1280,  1296, -1747,
     975, -1747,   160,   -32, -1747, -1747,  1315, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
    1126, -1747, -1747,  1175, -1747,  1122,  1190, -1747, -1747, -1747,
   -1747,  2109,   248,  1559, -1747,  1232,  1232,   668,  1320,  1320,
   -1747, -1747,  1139, -1747,   248, -1747,  1204, -1747, -1747, -1747,
   -1747, -1747,    64,  1430, -1747, -1747,  1090,  1199,  1153, -1747,
    1156,   975,  3568,  1179,   327,  1158, -1747, -1747,  4277,   843,
    1206,  4358,  4277,  1379,   715,   870,    65,   975, -1747, -1747,
    1475, -1747,    65,   975,  1562,   975,  3814,  4277, -1747,  2359,
     843,   975,   843,   975,    53,    70,   975,   843, -1747, -1747,
    3980,  4038, -1747, -1747,   975,   975,   843,   975, -1747,   254,
    1519,   975, -1747, -1747, -1747, -1747, -1747, -1747,  1607, -1747,
   -1747, -1747, -1747, -1747,   975,    11,   114,   127,  1191, -1747,
    1191, -1747, -1747, -1747,   673, -1747, -1747, -1747, -1747, -1747,
     975,  1184,  1458,  1458,   187, -1747, -1747, -1747, -1747,  1446,
   -1747, -1747, -1747,  1199,  1231,  4975,  1186, -1747,   975, -1747,
   -1747,  1405, -1747,  1444, -1747, -1747, -1747, -1747,   975,   975,
     668,  1107, -1747,   248,     4,     4,  1610,  1348, -1747, -1747,
   -1747,  1517,   588, -1747,  1320,  1197,   975,  1198,  1200,  1320,
       8,  1202,  1205,  1209,  1210,  1216,  1222,  1223,  1224,  1198,
    1521, -1747,  3878, -1747, -1747, -1747, -1747,  1441, -1747,  1591,
   -1747, -1747, -1747,  1255, -1747,     8, -1747, -1747,  1250, -1747,
   -1747,   392,   843,  1532,  1075, -1747,  1337,  1367,   843,   860,
    1554,  1375,   986,  1157,  1556,   151,  1250, -1747, -1747,    66,
   -1747, -1747, -1747,  1586, -1747, -1747, -1747,  1320,    65, -1747,
   -1747, -1747, -1747, -1747,  1301, -1747,    46,   975, -1747,   107,
   -1747, -1747, -1747, -1747, -1747,  4277, -1747,  1290,  1564,  1647,
     848, -1747,  1302, -1747,  4856,  1566,   702,  1311,  1306,   250,
    1321,   614,  1539, -1747,  1367,  1539,   975,  1581,  1297, -1747,
    1065, -1747, -1747, -1747, -1747, -1747,  1479, -1747,    65, -1747,
     391, -1747,    87, -1747, -1747,   520,  1675,  3431, -1747, -1747,
     975,  1583,  4087,   975,  1552,   898,  1620, -1747,  1404,  1358,
    1102,  1539,  1078,   244, -1747, -1747, -1747, -1747,   461, -1747,
   -1747,  1184, -1747, -1747, -1747, -1747,   392, -1747, -1747,   975,
   -1747,  1199,  1315, -1747, -1747, -1747, -1747,  1628,  1320,  4975,
    4975,  4975,    26,  1089, -1747, -1747, -1747,  1139, -1747,  4975,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747,  1371, -1747, -1747,
    1257,     4,  1633, -1747, -1747,  1065,   539,  1312,   555,   446,
    4975,  1353,  4975, -1747,  4975, -1747,  4149,  1316,  4975,  4975,
    4975,  4975,  4975,  4975,  4975,  4975, -1747, -1747, -1747,  4277,
    1571, -1747, -1747,  1419,  1441,  1403,  3265,  1455,  1534, -1747,
     529, -1747, -1747, -1747,   741, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747,   491,   843, -1747, -1747,   482,  1604,
    1604,  1604,  1604, -1747, -1747,  4277,  4277, -1747, -1747,   104,
    1638,   816, -1747,  1338,   715, -1747,   975, -1747,    22, -1747,
   -1747,  1073,  1603, -1747,  1065,    89, -1747,   107, -1747, -1747,
   -1747, -1747,   111,  1374,    65, -1747, -1747,  4277, -1747, -1747,
   -1747, -1747,  1412, -1747, -1747, -1747, -1747,   975,   327, -1747,
     620, -1747, -1747,  1367,   392, -1747,  1568,   473,   797, -1747,
   -1747,   975,   797,  1377, -1747,  1139, -1747, -1747,    95,   928,
   -1747, -1747,  2222, -1747,  1727,  1565,  4277,  4277, -1747,  4198,
     975, -1747,  1602, -1747, -1747,  4277,  1065, -1747, -1747, -1747,
    1675,  1574,   975, -1747,  1013,   101,   473, -1747, -1747,  1662,
   -1747, -1747, -1747,  1509, -1747, -1747,   975,   975, -1747,   975,
    1596,  1033,   -26, -1747,  4730,  1102, -1747,  4149,  1339,  1339,
    1188, -1747, -1747, -1747,  4975,  4975,  4975,  4975,  4975,  4975,
    4607,  1089, -1747,  1108, -1747,  1257,  1102, -1747, -1747, -1747,
    1604, -1747, -1747,  1345,  1349, -1747,  1065,  1604,  1576, -1747,
   -1747, -1747, -1747,  2794,  1604,  1527,  1527,  1527,   147,  1569,
   -1747, -1747,   394, -1747,    44,  1174,   975,  1104,    91,  1346,
   -1747,  1139, -1747, -1747,   561,  1351,  1221,   579,  1354,  1246,
      97,   117,   903,  1359,  1274,  4256,   450,  4277,    65, -1747,
    1452, -1747, -1747, -1747, -1747, -1747,  1108, -1747, -1747,  1411,
   -1747, -1747,  1411, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747,  1409,   327, -1747,    73,
     975,   975,    23, -1747, -1747, -1747,     5,   790,  1445, -1747,
   -1747,  1681, -1747,  1551, -1747,    94,  1325,  1604,  1550, -1747,
   -1747,  1555, -1747, -1747, -1747,  1635,  4256,   454, -1747, -1747,
   -1747,  3164, -1747,  1421, -1747, -1747, -1747, -1747, -1747,   104,
   -1747, -1747, -1747,  1102, -1747, -1747, -1747,  1108, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747,  1494,  1108, -1747,  1423, -1747,
    1773, -1747, -1747, -1747,   692, -1747,  1065,   817, -1747,    61,
     646,   793,    65,    65,  4256,   533,  1074,   843,  1688, -1747,
   -1747,  1816, -1747,  1649, -1747, -1747, -1747, -1747,  1568, -1747,
     975,   513,   491,   907,  1394,  1704, -1747,  1398,  1065,   786,
   -1747,   394, -1747, -1747, -1747,  4277,  1184,   491, -1747, -1747,
   -1747, -1747,  -110,   975,  4256,   556,  1435,  1825,   975,   530,
   -1747, -1747, -1747,  1533,  1535, -1747, -1747,   620, -1747,   196,
     -16, -1747, -1747, -1747,  1184,  1666, -1747, -1747,  1199, -1747,
   -1747,  1184, -1747, -1747, -1747, -1747,  1527,  1149,  1184,  1158,
   -1747, -1747,  1527, -1747,  1199, -1747, -1747, -1747, -1747, -1747,
     975, -1747,   975, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747,   975,  1639,   793, -1747,  1139, -1747, -1747,  1174,
     822,   822,  1339,  1339,  1339, -1747,  1292,  1440, -1747,   975,
   -1747,  1555, -1747, -1747,  1604, -1747, -1747, -1747,  1184, -1747,
   -1747,  1184, -1747, -1747, -1747, -1747, -1747, -1747, -1747,   115,
   -1747, -1747, -1747,  2794, -1747, -1747, -1747,   392,   392,   392,
   -1747, -1747, -1747, -1747, -1747,  1198,  1337,  4895, -1747,   975,
    1198,  1198,  4975, -1747,  1198,  1198,  1198,   393,  1198,  1198,
   -1747, -1747,  1577,  4256, -1747,    65, -1747, -1747,    41,   148,
   -1747, -1747,  1944, -1747,   627,   122, -1747, -1747, -1747, -1747,
    1046, -1747,  1526, -1747,  1502, -1747, -1747, -1747, -1747, -1747,
   -1747,   379,   379,   379,   379,  1184, -1747, -1747, -1747, -1747,
    1161,  1184, -1747, -1747, -1747, -1747,   135, -1747,  1325, -1747,
   -1747, -1747, -1747, -1747, -1747,  4277, -1747,  4277,   104, -1747,
   -1747, -1747,  3164, -1747,   975,  1733,  1429,  1195,  1752,  1432,
      55,  1065, -1747, -1747,  1811, -1747, -1747, -1747, -1747,   817,
   -1747,  1690, -1747,  1184,  1584, -1747, -1747, -1747, -1747,  1308,
      65, -1747,  4277,   256,   425, -1747, -1747, -1747,   975,  4277,
     931, -1747, -1747, -1747,  1728,  1609, -1747,  1726, -1747,  1634,
   -1747, -1747, -1747, -1747,  1398, -1747, -1747, -1747,  1612,  1730,
    1594,  1585,  1337, -1747,  4277,    55, -1747,  1600, -1747,  1065,
   -1747,  1779,  1501, -1747, -1747,  1102, -1747,   939,  1884, -1747,
    1005, -1747, -1747, -1747,  1199,  1780,  1676,  1828,  4816,   376,
    1184, -1747, -1747,   376, -1747,  1184,  1231, -1747, -1747, -1747,
    1675, -1747,  1308, -1747,  1184, -1747, -1747, -1747, -1747,   376,
     376,   102,   102, -1747, -1747, -1747, -1747, -1747,  1445, -1747,
    1317, -1747, -1747, -1747,  1174, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747,  1108,  1742,  1108,
    1743, -1747, -1747,  4277, -1747, -1747, -1747, -1747, -1747,  1771,
   -1747, -1747, -1747, -1747, -1747, -1747,  1604,  1604,  1604,  1604,
     376, -1747, -1747,   376,   102,   102, -1747, -1747, -1747,  4256,
    1575,  4256,  1578, -1747, -1747, -1747, -1747, -1747,  1767, -1747,
    1195, -1747,  1804, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
      55,   620, -1747, -1747,   620,   -46,   975, -1747, -1747,  4256,
   -1747, -1747,   923,  3742, -1747,  1855,  1669,  1692,   422, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747,   975,  1043, -1747, -1747, -1747,  1766,  1648,   975,
    1445,  4256, -1747,  1825, -1747,  1294,  1818,  1294,  1594,   503,
   -1747, -1747,  1764, -1747,  1653, -1747, -1747, -1747,   626, -1747,
   -1747,  1184,  1823,  1697, -1747,  1029, -1747,  1716,  1068,  1431,
    1729,  1484,  1184,  1320,  1184,   975, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,  1536, -1747,
   -1747, -1747, -1747,   883, -1747, -1747, -1747, -1747, -1747, -1747,
     411, -1747,   628, -1747,  1482,  1184,   248, -1747, -1747, -1747,
     376, -1747, -1747, -1747, -1747, -1747, -1747,  1108, -1747,  1108,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747,  4277, -1747,  4277, -1747, -1747,
   -1747, -1747, -1747,  1870,   620,   620, -1747,  1522,  1618,   843,
     466, -1747,   975, -1747, -1747,  1587,  4277, -1747,  1184,   841,
    1686, -1747,  1689, -1747, -1747, -1747, -1747, -1747, -1747,   975,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747,   975,  1294, -1747,   975,  1783, -1747,
   -1747, -1747, -1747, -1747,   843, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747,  1101,  1199,  1184,  1184,  1753, -1747,  1184, -1747,
   -1747, -1747, -1747,   187, -1747,  1184, -1747,   975,   975,  1415,
    1754, -1747,  1640,  1199,   883, -1747, -1747, -1747, -1747, -1747,
   -1747,   376, -1747, -1747, -1747, -1747,   376, -1747,  1482, -1747,
     975, -1747,  1101, -1747, -1747, -1747, -1747,  1445,  1445, -1747,
    4277,   620, -1747,  4277,  1184,   843,   843,  1627, -1747, -1747,
   -1747,  1514,   975,  1795, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747,   975, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747,  1199,  1199,  1184, -1747,  1199, -1747,  1199,
   -1747,  1337, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747,  4277, -1747, -1747, -1747, -1747, -1747, -1747,   975,
   -1747, -1747, -1747, -1747, -1747,   327,   843,  1184, -1747,   975,
   -1747, -1747, -1747, -1747, -1747, -1747,  1199, -1747, -1747, -1747,
    1885, -1747,   327, -1747, -1747,  4277, -1747, -1747
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1747, -1747, -1747, -1747,  1927, -1747, -1747, -1747,    39, -1747,
   -1747, -1747, -1747, -1747,  1598, -1747, -1747, -1747,  1211, -1747,
   -1747,    60,  1915, -1747, -1747,  1886,   208, -1747, -1747, -1747,
   -1747, -1747,  1755,  1808, -1747, -1747,  1772,   712, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747,  1761, -1747, -1747, -1747, -1747,
    1744, -1747, -1747, -1747, -1747, -1747,  -202,   647, -1747, -1747,
   -1747, -1747,  1460, -1747, -1747,  1382,   827, -1747, -1747, -1747,
   -1747, -1747, -1747,  1529, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747,  1820, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747,   631, -1747,   619,
     839, -1747, -1747, -1747, -1747, -1747,  1035,   103, -1747,  1385,
   -1747, -1747, -1747, -1747, -1747, -1747,   154, -1747,  1751, -1747,
    1863, -1747, -1747, -1747, -1747,  1599, -1747, -1747,   170, -1747,
   -1747, -1747, -1747,  1747, -1747,  1926,  1826, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747,  1120, -1747, -1747, -1747,  1424,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747,   695, -1747, -1747, -1747,  1678, -1747, -1747,  -554,
   -1747, -1747,  -290, -1747, -1747, -1747,  -442, -1747, -1747, -1747,
   -1747, -1747, -1747, -1290, -1286,  1152, -1281,   110, -1747, -1747,
   -1747, -1747,   328, -1747, -1747,  -223, -1279, -1747, -1747, -1266,
   -1747, -1264, -1747, -1747, -1747,  1142, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747,  1449, -1747, -1747,
   -1747,  1051, -1747,  -895, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747,   -69, -1747, -1747, -1747, -1747, -1747, -1747,  -198, -1747,
   -1747, -1747, -1747,   224, -1747, -1747, -1747, -1747, -1747,  1193,
   -1747, -1747, -1747, -1747, -1747, -1747,   232, -1747, -1747, -1747,
   -1747, -1747,  1869,  1084, -1747,   263, -1747, -1747, -1747, -1747,
    1528, -1747, -1747, -1747, -1747, -1747, -1747, -1016, -1747, -1747,
     183, -1747, -1747, -1747, -1747,   980,   613,   624, -1747, -1747,
     315, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747,   978, -1747, -1747,   281,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
     -43, -1747,   252, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747,   772, -1747, -1747,   780, -1747, -1747, -1747,
   -1747,   504,   253, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,    68,
     775, -1747, -1747, -1747, -1747, -1747, -1747, -1747,   776, -1747,
   -1747, -1747,   231, -1747, -1747,   490, -1747, -1747, -1747, -1608,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1245,   961, -1747, -1747,   218, -1747, -1747,   469, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
     713, -1747, -1747, -1747, -1747, -1747, -1747, -1747,   746, -1747,
     207, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747,   949, -1747,   944, -1747, -1747,  1148, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747,   936,   447, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747,    42, -1747,   455,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747, -1747,  -857,
   -1747, -1162, -1747, -1747, -1089, -1101, -1107, -1747,   386, -1747,
   -1427, -1747, -1747, -1747, -1747,    48, -1747, -1747, -1747, -1747,
     -67, -1747, -1747,   233, -1747, -1747, -1747, -1747,    43, -1747,
    -466, -1746, -1747, -1747,   567, -1747,  -897, -1256,  -830, -1201,
   -1747, -1747, -1747, -1188, -1187, -1183, -1171, -1170,    80,  -178,
    -759,  -840,  -823,  -856,  -236,   984, -1018,   -84, -1747, -1069,
   -1747,  -814, -1747,   864,  -391,  -183, -1747,  -706,   719,  -842,
    -981,  -626,  -781, -1747, -1747,   483, -1003, -1666,  -939,  -824,
   -1066,   693,  -600,  -220, -1747,  1117,  -235,  -643,  -467,  -308,
    -414,  -871, -1747, -1747, -1747, -1747, -1747,  1843, -1747,   470,
     874, -1747, -1747, -1747, -1658,  1245,    52,  1770,   823,  -425,
   -1747,  1047,  -388,  1498, -1747,  -620, -1747, -1081,  1121,  -415,
     -44, -1747, -1747,  -684, -1747, -1047,  -168,  -538,  -504,  -122,
    -980,   378, -1340,  -825, -1060, -1747,  1295,  2034,  -911, -1747,
   -1747, -1747, -1747, -1747, -1747, -1747,   661, -1747,   219,  -686,
    1123,  -127
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1571
static const yytype_int16 yytable[] =
{
     121,   246,   288,   457,   187,   456,   878,   658,   589,  1113,
    1225,   341,  1025,   841,   969,   846,   535,   389,  1470,  1471,
    1560,   265,   266,  1472,   824,  1309,   271,   272,   273,   274,
     275,  1300,   277,  1009,   280,  1473,  1474,   910,  1513,   287,
    1056,  1018,   803,   852,  1041,   427,  1698,  1699,  1898,   552,
    1013,   288,  1047,  1102,  1644,   288,   105,   288,  1645,   187,
    1325,  1745,  1086,  1646,   837,  1647,   288,  1247,   331,   121,
     332,  1047,   782,    22,   366,  1247,  1047,   339,  1648,  1776,
    1649,  1003,  1212,  1238,   932,   344,   431,  1293,   356,   158,
    1003,  1035,   360,  1047,   362,  1351,   569,   409,  1539,   353,
     354,  1047,   355,   373,   415,  1067,  1069,  1382,   361,    89,
    1604,  2026,   974,  1351,   289,  1154,    85,   427,  1567,  1109,
    1003,  1247,   158,   251,   288,  1508,  -189,  1811,  1196,  1502,
    1503,  1504,    92,  1523,   288,   847,   384,   278,   179, -1534,
   -1521,   288,   384,   391,   586,  1540,   396,   398,   126,   401,
     105,   158,   442, -1494,   804,   453,   920,  2118, -1498,  1179,
    1351,   416,   464,    41,  1186,   410,  1351,  1843,   477,    88,
     168,   428,  1368,  1286,   288,   472,   288,   291,   430,  2012,
     254,   660,   417,  1738,  2010, -1570,  1351,   571,  1751,   960,
    1364,   158,   475,  1974,  1917,    32,  1153,  1338,  1254,   497,
    1235,   846,  1551,   828,   370,  1301,   376,  1924,     4,   536,
     431,   287,  1385,   158, -1570,   835,    54,  1090,   241,    18,
     941,  1201,  1246, -1534,   455, -1570,   837,     3,  1287,  -190,
    1328,  1860,   466,  1891,    75,   498,   461,   288,   405,  1597,
      41,  1061,  1124,  -189,  1339,  1031,   418,   942,   943,   854,
    1201,  1538,   803,  1944,  1012,    12,  1298,   837,   406,  1541,
     238,   572,  1117,  1671,  1326,   796,   390,   838,  1169,  1170,
    1671,   397,    52,   432,   373,  1112, -1570,  1671,   590,    91,
     371,   106,   169,   544,  1263,  1652,  1870,   419,  1675,  1118,
     376,   470,  1875,   446,   420,  1695,  1915,   167,  1861,   574,
    1862,  1919,   556,   557,  2116,   239,  1669,  1739,  1542,  1154,
    1154,  1154,   659,  1596,  1091,  1328,   664,  1247,  1513,  1154,
    1918, -1458, -1458,  1347,   829,   183,  1109,   242,   667, -1510,
    1168,  1201,   573,  1012, -1498,     5,   669,   669,  1091,     5,
    1154,   581,  1154,  1025,  1154,  1569,  -190,   921,  1154,  1154,
    1154,  1154,  1154,  1154,  1154,  1154,  1171,  1236,  2114,  1125,
   -1498,  2115,     5,  1328,   804,   421, -1521,   593,  1164,  1165,
      41,    63,  1568,  1674,   653,   106,  1415,   584,   247,   107,
    1025,  1352,  2119,  2235,   823,  1668,   221,    14,   591,  1488,
    1348,  1349,  1350, -1498,  1752,   922,  1770,   432,  1735,  1352,
    1361,   836,   -31,   255,   385,   826,  1141,   781,   418,   257,
     388,  1025,   786,  1506,  1041,   790,   263,   791,  1416,   252,
     793,   794,  1553,  1397,   800,  1475,  1754,  1920,   422,  1404,
    1406,  1407,  1409,  1255,  1525,  1412,  1414,  1724,   839,   418,
     285,   661,  1925,  1387,  1554,  1858,  1352,  -189,   944,   419,
     585,  1020,  1352,    89,  1505,  1507,   420,   423,   285,  1025,
   -1516,    55, -1498,  1784,  1564,  1365,   831,   832,   975, -1498,
    1062,  2082,  1352,   107,   570,  1020,   338,  1353,  -612,   551,
     419,   183,   285,   145, -1498,  1302,  1555,   420,  1157,   285,
      86,   285,  1594,  1579,  1543,  1705,  1256,   424,  1239,   263,
    -610,   285, -1498,  1509,  1783,  1303,   285,  1510,  2221, -1494,
    1785,  1606,   797,   950,  1154,  1154,  1154,  1154,  1154,  1154,
    1154,  1584,  2104,   285,  2106,  1588,  1589,   421,  1591,   966,
    1753,   285,   285,  1892,  1595,   567,   853,   285, -1498,  1814,
     183,  1158, -1450,  1794, -1498,    56,  1329,   301,  1715,   478,
    -190,  1926,  2123,  1945,   586,    64,   183,   170,   421,  1012,
     471,  1025,  1172,   285,  1369,  1370,     4,  1671,  1716,   798,
     288, -1498,  1247,   288,   288,  1835,  1999,  1513,  2047,  1393,
     288,   925,  2048,  2151,  2152,  1888,  1400,  2049,  1342,  2051,
     422,  -612,  1390, -1498,  1723,  1659,  1660,  1661,  1662,  1663,
    1664,  1666,  2052,  2299,  2053,  1371,    65,  1372,   340,   945,
     934,   935,  1908,  -610,   924,  1131,  2130,   940,  1175,   423,
    1385,   422,   978,  1295,  1211,    63,  1702,   469,  1565,   855,
    1351,  1329,   285,  -756,   949,  1091,  1822,  1777,   898,  1373,
    1374,  1375,   458, -1570,  1016,    16,  1522, -1411,  1351,  2226,
     423,  1735,    13, -1494,  2197,  1566,   407,  1085,  2131,   424,
    1020, -1570,  1166,  1731,    23,  1064,  2159,   928,  1575,  1079,
     168,  1083,  1575,  1083,  1089,  1121,  1064,  1667,  2132,  1329,
    -207, -1570,  1157,  1157,  1157, -1512,  1376,    26,  1377,   168,
     424,  1083,  1157,     5,  1132,  2178,  1378,  1333,   783, -1496,
    1489,  1539,   955,  1306,   288,  2198,  2160,  1127,  1295, -1570,
    1810,    29,  1480,  1157,  2161,  1157,  1812,  1157,  1145,  1401,
     288,  1157,  1157,  1157,  1157,  1157,  1157,  1157,  1157, -1570,
    1934,  1935,   408,    30,    75,  1158,  1158,  1158,  1161,  1844,
    1726,  1123,   784,   459,  1916,  1158, -1570,  1655,  1540,  2227,
     899,  1391,  1490,    75,   288,   288,  1947,  1134,  1894,  1895,
    1896,   594,  1080,   285,  1176,  1955,  1158,   926,  1158,  1379,
    1158,  1823,  1402,  1136,  1158,  1158,  1158,  1158,  1158,  1158,
    1158,  1158,   169,  1091,  1386,  1027,  2162,  1295,  1969,  1299,
    2281,  2282,  1704,  1221,    19,  2019,   929,  1221,  1909,  2074,
   -1541,   169,  1742,  1334,  1837,  1874,  1081,  2071,  1084,    64,
    2080,  2080,   285,  1104,  1496,  2140,  2141, -1494,  2066,    55,
    2142,  1807,  1115,  2077,  2078, -1570,  1795,   847,   285,  1247,
     285,    33,  2143,  2144,  1897,  2095,  2096,  2097,  2098,  1902,
    1903,  1786,  1804,  1905,  1906,  1907,  2014,  1910,  1911,  1295,
    1789,  1387,   309,  2133,  2199,  2200,  1307,   340,   340,   418,
     183,   118,  1541,  2080,  2080,  1481,  1089,  1154,  1281,    20,
    1091,  2202,  1154,  1796,  2099,   930,  1221,  2100,   249,   346,
    1656,   575,   285,  -970, -1494,   250,   580,  1157,  1157,  1157,
    1157,  1157,  1157,  1157,   506,    36,  2084,   342,   310,  1221,
     419,  1922,  1495,    56,   347,  1808,  1341,   420,   183,  1295,
     267,  1542,   311,  1282,  2170,  2094,  1352,  1496,   276,  1950,
   -1494,  1952,  2203,   294,  -970,   507,  1805,    34,   300,  1252,
    2260,  -970,  2103,  1657,  1352,  1380,    38,   283,  1214,   118,
    1158,  1158,  1158,  1158,  1158,  1158,  1158,  1080,  1900,  1954,
     312,   288,  1949,  1904,  1951,    49,  1025, -1516,   502,  2171,
     250,   503,  2172,  1335,  1822,   183,   285,   809,  2154,    44,
    2157,   811,  1351,  2134,  2135,  1381,   504, -1570,   421,   168,
     813,  1704,  2137,    41,   351,   352,   505,    50,  1025,  1979,
     379,    93,   358,   359,   238,  2081, -1510, -1570,   365,   368,
    1997,  2164,  -970,    53,  1355,  1356,  1357,  1358,   418,  1359,
     787,  1268, -1456,   833,  2212, -1516,   810,   788,   141,   251,
     812,  2011,  1355,  1356,  1357,  1358,  1743,  1359,  1016,   814,
   -1454,   183,  2303,   834,   480, -1516,  1797,   815,  1985,   239,
    2301,   422,  1187,    75,  1131,   260,  1744,  2101,  2102,   419,
    1489,  1269,  1619,    94,   817,   514,   420,  2306,  1016,  1270,
    1483,    41,   285,    68,   291,  -970,   313,  1208,  2066,  2213,
     423,  2204,  2205,   142,   143,   447,   908,  2216,   314,  1295,
    1295,   984,  1527,   433,   837,  1528,   816,  1487,  1529,  1530,
    2020,   169,  2219,    95,  -970,    96, -1541,  1543,   188,  1823,
      45,  2225,  1490,   818,   481,  1016,  1827,  2139,  2243,  -207,
     424,  1295,   189,   190,  1037,   340,   288,   288,  1038,  1276,
    2238,  1839,  2239,  1132,  1803, -1570,  1986,   421,  -970,  2240,
      59,  1271,  1277,    60,  -970,  2276,    61,  2192,    46,    62,
    2277,   446,  2090,  1828,   191,   482,    47,  1968,  1489,  2247,
    2248,  1484,   483,  1612,  1612,   506,   985,    72,     5,  2124,
    1573,  1042,  1043,  1829,   484,   315,   316, -1570,   481,  1601,
     392,   987,   393,  1602,   170,  1044,   183,  2193,   317,  2125,
     318,   192,   193,    75,   194,  1582,   507, -1570,    79,  1583,
     422,   188,   195,   508,  -332,  -332,  1426,  1427,  2021,  1573,
    1490,   435,  1968,   436,    81,   189,   190,  1528,  2286,   482,
    1529,  1530,  1317,    10,  1318,  1020,   483,    10,  2188,   423,
      82,  1045,  1798,   485,  1428,  2292,  1709,   103,  1217,  1712,
    1429,  2086,   114,  2088,  1717,   196,   197,   191,   509,   985,
    1157,   303,   304,   237,   510,  1157,   198,   237,  1239,  2217,
    1516,  2218,   115,   285,   987,   988,   418,  1016,  1352,   424,
    1394,  1431,  1616,  1617,  1398,  1432,   418,  1357,  1358,   912,
    1359,   511,  1410,  1411,   192,   193,   116,   194,   512,   118,
     319, -1403, -1403, -1403, -1403,   195,   486,   485,   124,   487,
     488,   513,   780,  1158,  1696,  2177,   989,   419,  1158,  1871,
     320,  1872,   133,   990,   420,  1978,  1927,   419,  1928,   991,
     913,  1941,   992,  1942,   420,   252,   514,   914,   515,  1861,
     199,  1862,  1531,  1532,  1295,   128,   516,  1968,   196,   197,
    2249,  2250,  1295,  2181,  2182,   129,  -212,  2289,   988,   198,
    1533,  1534,   130,   131,   993,  2231,  1355,  1356,  1357,  1358,
     486,  1359,   136,   132, -1451,   489,   138,   517,  1755,   135,
     139,  1756, -1570,   148,   150,   149,   183,   165,   164,  1757,
    1758,  1759,   179,   166,   217,   421,   220,   221,  2075,   223,
     225,   984,  1295,  1867,   837,   421,   229,   230,   915,   288,
    1017,   231,   991,   245,    41,   992,   259,   262,   263,  1876,
     268,  2214,   269,  2215,   278,  1175,   518,  1229,  1230,  1231,
    1232,   285,   994,   199,   289,  1421,  1422,  1423,  1838,   489,
     291,   296,   297,  1424,   333,   298,  1612,   993,   334,  1813,
     336,   340,   288,  2211,   200,   343,   345,   348,   422,  2283,
   -1494,   349,  2284,   357,  1531,  1532,  1864,   381,   422,   288,
     382,   916,   399,  1869,   402,   404,   985,   995,   996,   411,
    1873,  1425,  1533,  1534,   412,  1841,   429,   423,   444,  1879,
    -349,   987,  1841,   449,   201,   451,   495,   423,   454,   465,
    1760,   467,   997,   537,   499,   545,  1886,   549,   547,   288,
     553,  2300,   576,  1446,   555,   994,  1448,  1449,  1761,   582,
     998,   285,   579,   592,  2264,  2265,   577,   424,   999,   183,
    1889,   285,   655,  1890,   665,  1762,   657,   424,   672,   673,
     917,   777,   586,   202,  2307,  1218,  1901,   200,  2266,   792,
     801,   808,  1355,  1356,  1357,  1358,   281,  1359,   303,   819,
     995,   996,   821,   827,  1360,   858,   859,  1355,  1356,  1357,
    1358,  -822,  1359,   902,   982,   988,  1426,  1427,  1019,  1707,
     584,   933,   936,  1763,  1033,   997,   418,   201,   952,  1050,
    1051,   837,   939,   953,   955,  1050,  1058,  1060, -1402, -1402,
   -1402, -1402,  1019,   998,  1428,   958,   961,  1940,  1050,   963,
    1429,   999,   967,  1943,   285,   970,   989,  1058,  1114,   973,
    1116,   976,   979,   990, -1494,   980,  1028,   419,  1053,   991,
    1764,  1036,   992,  1430,   420,  1007,   202,  1355,  1356,  1357,
    1358,  1431,  1359,  1120,  1122,  1432,  1128,  1137,  1146,  2030,
    1143,  1355,  1356,  1357,  1358,  1976,  1359,  1162,  1159,  1658,
     847,  1173,  1202,   985,   993,  2258,  1197,  1204,  1156,  1180,
    1182,  2184,  1184,  1207,  1188,  1433,  1434,  1189,   987,  1215,
    1435,  1190,  1191,  1765,  1355,  1356,  1357,  1358,  1192,  1359,
    1436, -1494,  1711,  1766,  1193,  1194,  1195,  1437,  1209,  1181,
    1221,  1223,  1438,  1226,  1245,   421,  1233,  1982,  1264,  1355,
    1356,  1357,  1358,  1988,  1359,  1249,  1267,  1714,  1265, -1405,
    1439,  1274,  2070,  1279,  2267,  2268,  1278,  2072,  1936,  1937,
    1938,  1939,   994,  1280,  1213,  1284,  2076,  1355,  1356,  1357,
    1358,  1289,  1359,  1091,   158,  1719,  1313,  1291,  1316,  1320,
     446,  1362,  1322,  1323,  1767,  1355,  1356,  1357,  1358,  1345,
    1359,  1050,   988,  1883,  1366,  2269,  2270,  1383,   422,  1050,
    1253,  1396,  1403,   418,  1417,  1418,   288,   995,   996,  1476,
    1355,  1356,  1357,  1358,  1499,  1359,  1012,  1019,  2083,  1514,
    1519,  1537,  1552,  1556,  1570,  1578,  1585,   423,  1593,  1586,
    1598,  1608,   997,  1294,  1610,  1614,  1672,  1359,  1725,  1673,
    1676,  1050,  1696,  2121,   419,  1050,   991,  1708,  1386,   992,
     998,   420,  1710,  1312,  1727,  1713,  1253,  1730,   999,  1748,
    1718,   285,  1490,  1720,  1771,  1773,  1779,   424,  1775,  2279,
    1787,  1790,  1791,  1815,  1818,  1819,  1830,  1831,  2196,  1213,
    1832,   993,  1058,  1845,  1846,  1854,  1865,  1880,  1856,  1884,
    1913,  1933,  1156,  1156,  1156,  1440,  1441,  1442,  1443,  1444,
    1932,  1445,  1156,  1446,  1447,  1957,  1448,  1449,  1959,  1963,
    1970,  1965,  1973,  2173,  1977,  1994,  1991,  1823,  1294,  2001,
    1996,  2004,   421,  1156,  2187,  1156,  2189,  1156,  2006,  2013,
    2009,  1156,  1156,  1156,  1156,  1156,  1156,  1156,  1156,  2015,
    2017,  2027,  2032,  2031,  2034,  2087,  2089,  2091,  2105,   994,
    2109,  2107,  2229,  2112,  2126,  2127,  2128,  2210,  2146,  2167,
    2148,  2155,  2021,  2174,  2175,  2179,  2186,  2185,  2207,  2220,
    2224,  2043,  2236,  2222,  2255,  2237,  2230,  2245,  2273,  2287,
    2272,  2288,  2290,    15,  2305,   422,   414,    28,  2252,   186,
      74,   261,   258,   248,   995,   996,  1580,  1294,   282,  1327,
    -779,   568,   779,  -779,   494,   219,  1613,  1050,  2274,  2196,
    2232,  1609,  1330,  2029,   423,  1130,   789,  1980,   288,   997,
    1563,   284,   146,   443,   293,    67,   977,  1213,  2050,   233,
     383,   670,  1882,   959,  1576,  2278,   972,   998,   595,  2191,
     288,  1050,   163,   158,  1140,   999,  2275,  1923,   285,   951,
    1983,   558,  1701,  1592,   424,  2263,  2253,  2254,  1893,  1294,
    2257,  1228,  1700,  1921,  1237,  1600,  1521,  2259,  2294,  2295,
    1946,  1517,  2297,  1782,  2298,  -779,  1536,   287,  2111, -1498,
    1972,  1953,  1253,  1548,  1792,  1273,  1984,  1820,  1577,  1607,
    -779,  2000,  1297,  1311,  1103,  1296,  1852,  1156,  1156,  1156,
    1156,  1156,  1156,  1156,  1853,  2153,  2285,  1887,  1993,   288,
    1750,  2304,  2234,   880,  1836,  1016,  2158,  2169,  -913,  1294,
    1288,  -913,  1478,  1160,  -913,  -913,  -913,   302,  1420,  1859,
     446,   965,  1016,   395,  1163,  1550,  1244,  2296,   795,  1706,
    2280,    76,   938,  1729,  1167,  2073,   373,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1050,     0,     0,     0,     0,     0,     0,     0,  2302,
    -913,     0,     0,     0,  -779,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -779,     0,     0,     0,     0,
       0,   446,     0,  -913,     0,     0,   600,   601,   602,   603,
     604,   605,     0,     0,     0,     0,     0,     0,  -913,     0,
       0,     0,     0,     0,     0,  -779,     0,     0,     0,     0,
       0,     0,  -779,  1736,  1737,     0,  -779,     0,  -779,     0,
       0,  -779,   607,  -779,   608,   609,   610,   611,   612,   613,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   446,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -779,     0,  -913,  -913,     0,  -779,     0,
       0,     0,     0,     0,   614,     0,     0,     0,   984,     0,
       0,   837,     0,     0,     0,     0,     0,     0,     0,  1294,
    1294,     0,  -913,  -913,     0,  1050,  1050,     0,     0,  -913,
       0,     0,     0,  -913,  -779,     0,     0,     0,     0,     0,
       0,     0,     0,  1821, -1498,     0,     0,     0,     0,     0,
       0,  1294,  -913,     0,     0,     0,     0,     0,     0,     0,
    -913,  -779,     0,  -913,  -913,     0,  1842,     0,     0,     0,
    -913,  1851,  1851,     0,  -913,     0,  -913,     0,     0,  -913,
       0,  -913,     0,   985,     0,     0,   615,     0,     0,     0,
       0,  -779,     0,     0,  -913,  -913,     0,  -779,   987,  -913,
       0,     0,  1019,     0,     0,     0,  -779,  -779,     0,  -913,
       0,  -913,     0,  1877,     0,  1878,  -913,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -779,     0,     0,     0,
       0,  -779,     0,     0,     0,     0,  -779,     0,   618,  -913,
       0,     0,     0,     0,     0,     0,     0,     0,  1581,  -779,
       0,     0,  -913, -1498,     0,     0,     0,  -779,     0,     0,
    -779,     0,     0,     0,     0,     0,  -779,     0,     0,     0,
    1213,  1213,  1213,     0,     0,   620,     0,     0,     0,  -913,
    1156,     0,   988,     0,   622,  1156,     0,     0,     0,     0,
       0,     0,     0,   418,     0,     0,     0,   623,  1050,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -913,     0,     0,     0,     0,
     985,     0,     0,   989,  -913,  -913,     0,     0,     0,     0,
     990,     0,     0,     0,   419,   987,   991,     0,     0,   992,
       0,   420,     0,     0,  -913,     0,     0,     0,     0,  -913,
       0,     0,     0,   627,   628,   629,     0,  1956,     0,     0,
       0,     0,     0,  1967,  1294,     0,     0,  -913,     0,     0,
       0,   993,  1294,     0,     0,  -913,     0,     0,  -913,     0,
       0,     0,     0,  1050,  -913,  -913,  -913,     0,     0,     0,
    -913,  1563,  -913,     0,  -913,  -913,  -913,     0,     0,     0,
       0,     0,   631,   632,   633,     0,     0,     0,     0,     0,
       0,     0,   421,  1071,     0,     0,  -344,   597,  1967,   988,
       0,     0,  1294,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   598,     0,   994,
       0,     0,  2068,     0,     0,     0,  2068,     0,     0,     0,
     599,     0,     0,   600,   601,   602,   603,   604,   605,   606,
       0,     0,  2068,  2068,     0,     0,     0,     0,     0,     0,
       0,  1072,     0,   991,     0,   422,   992,     0,     0,     0,
       0,     0,     0,     0,   995,   996,     0,     0,     0,   607,
       0,   608,   609,   610,   611,   612,   613,     0,     0,     0,
       0,  1582,     0,     0,   423,  1583,     0,     0,   993,   997,
       0,     0,     0,  2068,     0,     0,  2068,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   998,     0,     0,
       0,   614,     0,     0,     0,   999,     0,     0,   285,     0,
       0,     0,     0,  1967,   424,     0,  -607,   559,  -344,  -647,
       0,  -647,  -344,     0,     0,     0,  -647,     0,     0,     0,
       0,     0,     0,     0,  -647,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1058,   994,     0,     0,     0,
   -1516,  -344,  2150,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -344,     0,  -647,  -647,     0,
   -1516,  2068,     0,     0,     0,  -647,     0,     0,     0,     0,
       0,     0,     0,   615,     0,     0,  -647,     0,  2190,     0,
    -647,   995,   996,     0,     0,     0,    41,     0,     0,   616,
       0, -1570,  -647,     0,     0, -1551,     0,     0,     0,  -344,
    -344,     0,     0,     0,     0,     0,   997,  -344,   617,     0,
       0,  -344,     0,  2068,  -647,     0, -1021,     0,     0,     0,
       0,  -647,  -647,     0,   998,   618,     0,     0,     0, -1021,
       0,     0,   999,     0,   183,   285,     0,     0,  -607,     0,
       0,     0,  -607,     0,     0,     0,     0,   619,     0,     0,
       0,     0,  -647,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   620,     0,  -647,  1677,     0,  1678,  -647,   621,
    1679,   622,  1253,     0,     0,     0,     0,     0,  -344,     0,
    1680,  -647,  -344,     0,   623,  -607,     0,  2242,  -647,     0,
    2244,  -647,  -647,     0,   624,     0,     0,     0,     0,  -647,
       0,   625,     0,  -344,     0,     0,  -647,     0,  -647,     0,
       0,  -647,     0,     0,     0,     0,     0,     0,     0,     0,
    2261,     0,  -344,     0,     0,  -344,     0,     0,     0,     0,
       0,     0,     0,     0,  2068,     0,     0,     0,   626,  2068,
     627,   628,   629,     0,     0,     0,     0,     0,  -647,     0,
       0,     0,  -647,     0,  -647,     0,     0,     0,     0,     0,
       0,  -647,     0,     0,   630,  1058,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2293,     0,     0,     0,
       0, -1551,     0,  -647,     0,     0,     0,     0,     0,   631,
     632,   633,   559,     0,  -647,     0,  -647,     0,  -647,     0,
       0,  -647,   634,     0,     0,   635,     0,  1681,     0,  -647,
       0,  1682,  -607,     0,  -344,     0,     0,     0,     0,  -647,
       0,     0,  1253,     0,  1683,  -344,     0,     0,  -647,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -647,  -647,  -647,     0,     0,  -647,     0,  -647,     0,
    -647,     0,     0,     0,     0,     0,  -647,     0,     0,     0,
       0,  -647,     0,     0,     0,  -647,  -647,     0,     0,     0,
       0,     0,  1684,     0,     0,  -647,     0,  -647,     0,     0,
       0,     0,     0,     0,  -647,     0,  -647,  -647,     0,     0,
    -647,     0,  -647,     0,     0,     0,     0,  -647,     0,  -647,
       0,     0,     0,     0,     0,     0,  -647,  -647,     0,     0,
       0,     0,  -647,     0,   671,     0,     0,  -647,     0,  1685,
       0,     0,  -647,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -647,     0,     0,     0,  -647,     0,     0,
       0,     0,   560,  1686,     0,  -647,     0,     0,     0,  -647,
       0,     0,     0,  -647,     0,  -647,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -647,  1687,     0,     0,
       0,     0,  1688,  -647,     0,     0,  -647,  -647,     0,     0,
       0,     0,  1689,     0,  -647,     0,  1690,     0,     0,     0,
       0,  -647,     0,  -647,     0,     0,  -647,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   -1486,     0,     0, -1486,     0,     0, -1486, -1486, -1486,     0,
       0,  1238,     0,     0,     0, -1486,     0,     0,     0,     0,
       0,     0,     0,  -647,     0,     0,     0,  -647,     0,  -647,
       0,     0,     0,  1691,     0,     0,  -647,     0,     0,     0,
       0,     0,     0,  1692,     0,     0,     0,     0,     0,     0,
       0,     0, -1486,     0,     0,     0,     0,     0,  -647,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -647,     0, -1486,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   -1486,     0,     0,     0,  -647,     0,     0,     0,     0,     0,
       0,   984,     0,  -647,   837,     0,     0,  1455,  1456,  1457,
       0,     0,     0,     0,     0,     0,  -647,     0,     0,     0,
       0,  -647,     0,  -647,     0,     0,     0,     0,     0,     0,
       0,  -647,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -647,     0,     0,     0,     0,     0, -1486, -1486,     0,
    -647,     0,     0,  1458,     0,     0,     0,     0,     0,  -647,
       0,  -647,  -647,     0,     0,  -647,     0,  -647,     0,     0,
       0,     0,  -647,     0, -1486, -1486,   985,     0,     0,     0,
       0, -1486,     0,     0,     0, -1486,     0,  -647,     0,     0,
       0,   987,  -647,     0,     0,     0,     0,  -647,     0,     0,
       0,     0,     0,     0, -1486,     0,     0,     0,  -647,     0,
       0,     0, -1486,     0,     0, -1486, -1486,   560,     0,     0,
    -647,     0, -1486,     0,     0,     0, -1486,     0, -1486,     0,
    -647, -1486,     0, -1486,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0, -1486, -1486,  1426,  1427,
       0, -1486,     0,     0,     0,     0,     0,     0,     0,     0,
       0, -1486,     0, -1486,     0,     0,     0,   984, -1486,     0,
     837,     0,     0,     0,     0,   988,  1428,     0,     0,     0,
       0,     0,  1429,     0,     0,     0,   418,     0,     0,     0,
       0, -1486,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0, -1486,  1459,     0,     0,     0,     0,
       0,     0,     0,  1431,     0,     0,   989,  1432,     0,     0,
       0,     0,     0,   990,     0,     0,     0,   419,     0,   991,
       0, -1486,   992,     0,   420,     0,     0,     0,     0,     0,
       0,     0,   985,     0,     0,     0,     0,  1460,  1461,     0,
       0,     0,  1462,     0,     0,     0,     0,   987,     0,     0,
       0,     0,  1463,     0,   993,     0,     0, -1486,     0,  1464,
    1106,     0,     0,     0,     0,     0, -1486, -1486,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1465, -1486,     0,     0, -1486, -1486,     0,     0,
       0, -1486,     0,     0,   984,   421,     0,   837,     0,   674,
       0,   675,     0,     0,     0,     0,   676,     0,     0, -1486,
       0,     0,     0,     0,   677,     0,     0, -1486,     0,     0,
   -1486,     0,   994,     0,     0,     0, -1486, -1486, -1486,     0,
       0,   988, -1486,     0, -1486,     0, -1486, -1486, -1486,     0,
       0,     0,   418,     0,     0,     0,     0,   678,   679,     0,
       0,     0,     0,     0,     0,   680,     0,  1310,   422,     0,
       0,     0,     0,     0,     0,     0,   681,   995,   996,   985,
     682,     0,   989,     0,     0,     0,     0,     0,     0,   990,
     986,     0,   683,   419,   987,   991,     0,   423,   992,     0,
     420,     0,   997,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   684,     0,     0,     0,     0,     0,
     998,   685,   686,     0,     0,     0,     0,     0,   999,     0,
     993,   285,     0,     0,     0,     0,     0,   424,  1466,  1467,
       0,     0,     0,  1468,     0,  1446,     0,  1469,  1448,  1449,
       0,     0,   687,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   688,     0,     0,     0,   689,     0,
       0,   421,     0,     0,     0,   674,     0,   675,   988,     0,
       0,   690,   676,     0,     0,     0,     0,     0,   691,   418,
     677,   692,   693,     0,     0,     0,     0,     0,   994,   694,
       0,     0,     0,     0,     0,     0,   695,     0,   696,     0,
       0,   697,     0,     0,     0,     0,     0,     0,     0,   989,
       0,     0,     0,   678,   679,     0,   990,     0,     0,     0,
     419,   680,   991,     0,   422,   992,     0,   420,     0,     0,
       0,     0,   681,   995,   996,     0,   682,     0,   698,     0,
     984,     0,   699,   837,   700,     0,     0,     0,   683,     0,
       0,   701,     0,   423,     0,     0,     0,   993,   997,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     684,     0,     0,   702,     0,     0,   998,   685,   686,     0,
       0,     0,     0,     0,   999,     0,     0,   285,   703,     0,
       0,     0,     0,   424,     0,     0,     0,     0,   421,     0,
       0,     0,     0,     0,   984,     0,     0,   837,   687,   704,
       0,     0,     0,     0,     0,   985,     0,     0,   705,     0,
     688,     0,     0,     0,   689,   994,  1065,     0,     0,     0,
     987,   706,     0,     0,     0,     0,   707,   690,   708,     0,
       0,     0,     0,     0,   691,     0,   709,   692,   693,     0,
       0,     0,     0,     0,     0,   694,   710,     0,     0,     0,
       0,   422,   695,     0,   696,   711,     0,   697,     0,     0,
     995,   996,     0,     0,   712,     0,   713,   714,     0,   985,
     715,     0,   716,     0,     0,     0,     0,   717,     0,     0,
     423,     0,     0,     0,   987,   997,     0,     0,     0,     0,
       0,     0,   718,     0,   698,     0,   984,   719,   699,   837,
     700,     0,   720,   998,   988,     0,     0,   701,     0,     0,
       0,   999,     0,   721,   285,   418,     0,     0,     0,     0,
     424,     0,     0,     0,     0,   722,     0,     0,     0,   702,
       0,     0,     0,     0,     0,   723,     0,     0,     0,     0,
       0,     0,     0,     0,   703,   989,     0,     0,     0,     0,
       0,     0,   990,     0,   984,     0,   419,   837,   991,     0,
       0,   992,     0,   420,     0,   704,     0,     0,   988,     0,
       0,   985,     0,     0,   705,     0,     0,     0,     0,   418,
       0,     0,     0,     0,     0,     0,   987,   706,     0,     0,
       0,     0,   707,   993,   708,     0,     0,     0,     0,  1106,
       0,     0,   709,   984,     0,     0,   837,     0,     0,   989,
       0,     0,   710,     0,     0,     0,   990,     0,     0,     0,
     419,   711,   991,     0,     0,   992,     0,   420,     0,   985,
     712,     0,   713,   714,   421,     0,   715,     0,   716,     0,
    1110,     0,     0,   717,   987,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   993,   718,     0,
       0,   994,     0,   719,     0,     0,     0,     0,   720,     0,
     988,     0,     0,     0,     0,     0,     0,     0,   985,   721,
       0,   418,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   722,     0,   987,     0,     0,     0,   422,   421,     0,
       0,     0,     0,     0,     0,     0,   995,   996,     0,     0,
       0,   989,     0,     0,   984,     0,     0,   837,   990,     0,
       0,     0,   419,     0,   991,   994,   423,   992,   988,   420,
       0,   997,     0,     0,     0,     0,     0,     0,     0,   418,
     985,     0,     0,     0,     0,     0,     0,     0,     0,   998,
       0,     0,     0,     0,     0,   987,     0,   999,     0,   993,
     285,   422,     0,     0,     0,     0,   424,     0,     0,   989,
     995,   996,   984,  1315,     0,   837,   990,   988,     0,     0,
     419,     0,   991,     0,     0,   992,  1199,   420,   418,   985,
     423,     0,     0,   984,     0,   997,   837,     0,     0,     0,
     421,     0,     0,     0,   987,     0,     0,     0,     0,     0,
       0,     0,     0,   998,     0,     0,     0,   993,   989,     0,
       0,   999,     0,     0,   285,   990,     0,   994,     0,   419,
     424,   991,     0,     0,   992,     0,   420,     0,     0,   988,
       0,     0,     0,     0,     0,     0,     0,   985,     0,     0,
     418,     0,     0,     0,     0,     0,     0,     0,   421,     0,
       0,     0,   987,   422,     0,     0,   993,     0,   985,     0,
       0,     0,   995,   996,   984,     0,     0,   837,     0,     0,
       0,     0,     0,   987,     0,   994,     0,     0,   988,     0,
       0,   419,   423,   991,     0,     0,   992,   997,   420,   418,
       0,     0,     0,     0,     0,     0,     0,   421,     0,     0,
       0,     0,     0,     0,     0,   998,     0,     0,     0,     0,
       0,   422,     0,   999,     0,     0,   285,     0,   993,   989,
     995,   996,   424,     0,   994,     0,   990,     0,     0,     0,
     419,     0,   991,     0,     0,   992,   988,   420,     0,   985,
     423,     0,     0,     0,     0,   997,     0,   418,     0,     0,
       0,     0,     0,     0,   987,     0,     0,   988,     0,   421,
     422,     0,     0,   998,     0,     0,     0,   993,   418,   995,
     996,   999,     0,     0,   285,     0,     0,   989,     0,     0,
     424,     0,     0,     0,   990,     0,   994,     0,   419,   423,
     991,     0,     0,   992,   997,   420,     0,     0,   989,     0,
       0,     0,     0,     0,     0,   990,     0,     0,   421,   419,
       0,   991,   998,     0,   992,     0,   420,     0,     0,     0,
     999,     0,   422,   285,     0,   993,     0,     0,     0,   424,
       0,   995,   996,     0,     0,   994,     0,     0,   988,     0,
       0,     0,     0,     0,     0,     0,   993,     0,     0,   418,
       0,   423,     0,     0,     0,     0,   997,     0,     0,     0,
       0,     0,     0,     0,     0,  1590,   421,     0,     0,     0,
       0,   422,     0,     0,   998,     0,     0,     0,     0,   989,
     995,   996,   999,     0,     0,   285,   990,   421,     0,     0,
    1029,   424,   991,   994,     0,   992,     0,   420,     0,     0,
     423,     0,     0,     0,     0,   997,     0,     0,     0,     0,
       0,     0,     0,     0,   994,     0,     0,     0,     0,     0,
       0,     0,     0,   998,  1720,     0,     0,   993,     0,   422,
       0,   999,     0,     0,   285,     0,     0,     0,   995,   996,
     424,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     422,     0,     0,     0,     0,     0,     0,     0,   423,   995,
     996,     0,     0,   997,     0,     0,     0,     0,   421,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   423,
       0,   998,     0,     0,   997,     0,     0,     0,   985,   999,
       0,     0,   285,     0,     0,   994,     0,     0,   424,     0,
       0,     0,   998,   987,     0,     0,     0,     0,     0,     0,
     999,     0,     0,   285,     0,     0,     0,     0,     0,   424,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   422,     0,     0,     0,     0,     0,     0,     0,     0,
     995,   996,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     423,  1620,     0,  1621,     0,   997,  1622,   600,   601,   602,
     603,   604,   605,   606,  1623,  1624,  1625,     0,     0,     0,
       0,     0,     0,   998,     0,     0,     0,   988,     0,     0,
       0,   999,     0,     0,   285,  1626,     0,     0,   418,     0,
     424,     0,     0,   607,     0,   608,   609,   610,   611,   612,
     613,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1148,     0,
       0,     0,     0,     0,     0,   990,     0,     0,     0,   419,
       0,   991,     0,     0,   992,   614,   420,     0,     0,     0,
       0,     0,     0,   600,   601,   602,   603,   604,   605,   606,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   993,     0,     0,     0,
       0,  2035,  2036,     0,     0,  1627,     0,     0,     0,   607,
       0,   608,   609,   610,   611,   612,   613,     0,     0,     0,
       0,     0,     0,  1628,     0,     0,  1629,  1630,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   421,     0,     0,
    1631,     0,     0,     0,     0,     0,     0,   615,     0,     0,
       0,   614,     0,     0,     0,     0,     0,   985,     0,     0,
       0,     0,     0,   616,   994,     0,     0,     0,     0,     0,
       0,     0,   987,     0,     0,     0,     0,     0,     0,  1632,
       0,     0,     0,     0,     0,     0,     0,     0,  1633,     0,
       0,     0,     0,     0,     0,     0,   985,     0,     0,   618,
     422,     0,     0,     0,     0,     0,     0,     0,     0,   995,
     996,   987,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1634,     0,     0,  2037,     0,     0,     0,     0,   423,
       0,     0,     0,   615,   997,  1635,   620,     0,     0,     0,
       0,     0,     0,   621,     0,   622,     0,     0,     0,   616,
    1071,     0,   998,     0,     0,     0,   988,     0,   623,  1636,
     999,     0,     0,   285,     0,  2038,  2039,     0,     0,   424,
    1149,  1150,     0,     0,     0,     0,   985,     0,  1665,  1151,
       0,     0,     0,  1637,     0,   618,     0,     0,  1638,     0,
    2040,   987,     0,     0,     0,   988,     0,     0,     0,     0,
       0,     0,  1639,     0,     0,     0,   418,   619,  1017,     0,
     991,     0,   626,   992,   627,   628,   629,     0,     0,     0,
       0,     0,   620,     0,     0,     0,     0,     0,     0,   621,
       0,   622,     0,     0,  2041,     0,  1148,     0,     0,     0,
       0,     0,     0,   990,   623,   993,     0,   419,  1640,   991,
       0,     0,   992,     0,   420,     0,     0,     0,     0,  1641,
       0,     0,     0,   631,   632,   633,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   988,   634,     0,  1642,   635,
       0,     0,     0,     0,   993,     0,   418,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   626,  1643,
     627,   628,   629,     0,     0,     0,     0,  2042,     0,     0,
       0,     0,     0,   994,     0,     0,  1148,     0,     0,     0,
       0,  2043,     0,   990,     0,   421,     0,   419,     0,   991,
       0,     0,   992,     0,   420,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2044,     0,     0,     0,     0,   631,
     632,   633,   994,     0,     0,     0,     0,     0,   995,   996,
       0,     0,   634,     0,   993,   635,  2045,     0, -1570,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   997,     0,  2046,     0,     0,   422,     0,
       0,     0,     0, -1021,     0,     0,     0,   995,   996,     0,
       0,   998,     0,     0,     0,   421, -1021,     0,     0,   999,
       0,   183,   285,     0,     0,     0,     0,   423,     0,     0,
       0,     0,   997,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   994,     0,     0,     0,     0,     0,     0,     0,
     998,     0,     0,     0,     0,     0,     0,     0,   999,     0,
       0,   285,     0,     0,     0,     0,     0,   424,  1149,  1150,
       0,     0,     0,     0,     0,     0,  1899,  1151,   422,     0,
       0,     0,     0,     0,     0,     0,     0,   995,   996,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   423,     0,     0,
       0,     0,   997,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     998,     0,     0,     0,     0,     0,     0,     0,   999,     0,
       0,   285,     0,     0,     0,     0,     0,   424,  1149,  1150,
       0,     0,     0,     0,     0,     0,     0,  1151
};

static const yytype_int16 yycheck[] =
{
      84,   169,   222,   394,   131,   393,   692,   545,   512,   904,
    1028,   246,   868,   656,   839,   658,   441,   307,  1206,  1206,
    1276,   189,   190,  1206,   624,  1106,   194,   195,   196,   197,
     198,  1100,   200,   863,   202,  1206,  1206,   721,  1239,   222,
     882,   865,   596,   663,   874,   353,  1386,  1387,  1706,   464,
     864,   271,     6,   895,  1344,   275,    22,   277,  1344,   186,
    1120,  1488,     9,  1344,     9,  1344,   286,  1048,   236,   153,
     238,     6,   576,    13,    94,  1056,     6,   245,  1344,  1506,
    1344,   862,  1021,    17,   790,   253,    23,  1090,   271,    49,
     871,   872,   275,     6,   277,    69,    17,   332,     9,   267,
     268,     6,   270,   286,   339,   886,   887,  1176,   276,    70,
       9,  1857,    48,    69,    84,   955,    54,   425,  1280,   900,
     901,  1102,    49,    62,   344,    21,   115,  1554,   999,  1230,
    1231,  1232,    72,   111,   354,    30,   168,    56,   178,    28,
     210,   361,   168,   311,   214,    56,   314,   315,    88,   317,
      22,    49,   372,    48,   596,   390,   120,   203,    85,   984,
      69,   344,   397,   210,   989,   333,    69,  1594,    56,   136,
     241,   354,  1175,  1084,   394,   410,   396,   172,   361,  1845,
       9,    56,   350,   160,  1842,   295,    69,   495,    94,   832,
    1170,    49,   136,  1801,   153,    25,   955,  1136,    91,   434,
      49,   844,  1262,   220,   196,   118,   290,    85,   179,   444,
      23,   394,    65,    49,   168,   219,    72,   147,   320,    11,
      60,  1002,  1047,   112,   392,   104,     9,     0,  1085,   115,
     119,   247,   400,   118,   305,   437,   232,   457,   164,  1320,
     210,   884,   115,   232,  1139,   871,   191,    87,    88,   664,
    1031,  1254,   806,   118,   232,   449,  1098,     9,   184,   170,
     367,   496,     8,  1370,  1121,     9,   310,    50,   974,   975,
    1377,   315,    40,   210,   457,   901,   171,  1384,   513,    71,
     272,   247,   353,   451,  1065,  1345,  1626,   232,  1377,    35,
     374,   167,  1632,   377,   239,  1384,  1723,   127,   314,   501,
     316,   153,   470,   471,  1970,   412,  1366,   284,   219,  1149,
    1150,  1151,   547,  1316,   244,   119,   551,  1298,  1519,  1159,
     279,   223,   224,  1148,   341,   435,  1107,   429,   232,   324,
     973,  1112,   500,   232,   232,   306,   556,   557,   244,   306,
    1180,   509,  1182,  1199,  1184,  1284,   232,   311,  1188,  1189,
    1190,  1191,  1192,  1193,  1194,  1195,   976,   206,  1966,   232,
     320,  1969,   306,   119,   806,   310,   436,   535,   968,   969,
     210,   165,  1283,  1376,   542,   247,  1199,    37,   449,   345,
    1236,   355,   428,  2129,   619,  1365,   275,     0,   515,  1219,
    1149,  1150,  1151,   320,   300,   359,  1497,   210,  1479,   355,
    1159,   405,   449,   232,   436,   625,   944,   575,   191,   449,
     436,  1267,   580,  1236,  1244,   583,   436,   585,  1199,   358,
     588,   589,  1264,  1182,   592,  1206,  1495,   279,   373,  1188,
    1189,  1190,  1191,   326,  1248,  1194,  1195,  1418,   221,   191,
     436,   316,   320,   296,  1267,  1607,   355,   436,   288,   232,
     110,   865,   355,   414,  1235,  1236,   239,   402,   436,  1315,
     430,   317,   320,  1523,  1278,  1171,   634,   635,   404,   429,
     884,  1898,   355,   345,   395,   889,   244,   451,   336,   398,
     232,   435,   436,   449,   320,   398,  1267,   239,   955,   436,
     428,   436,  1315,   398,   405,   451,   389,   442,   432,   436,
     336,   436,   429,   399,  1520,   418,   436,   403,  2116,   404,
    1526,  1325,   256,   803,  1354,  1355,  1356,  1357,  1358,  1359,
    1360,  1302,  1949,   436,  1951,  1306,  1307,   310,  1309,   837,
     436,   436,   436,   418,  1315,   475,   663,   436,   436,  1557,
     435,   955,   451,  1546,   442,   401,   435,   449,   451,   437,
     436,   429,  1979,   418,   214,   349,   435,   436,   310,   232,
     436,  1417,   977,   436,    25,    26,   179,  1674,   451,   313,
     790,   429,  1553,   793,   794,  1578,  1832,  1778,  1868,  1179,
     800,   114,  1868,  2010,  2011,  1674,  1186,  1868,  1142,  1868,
     373,   449,   146,   429,  1417,  1354,  1355,  1356,  1357,  1358,
    1359,  1360,  1868,  2261,  1868,    66,   400,    68,   232,   449,
     793,   794,   219,   449,   782,   371,   194,   800,    30,   402,
      65,   373,   857,  1090,   232,   165,   232,   403,     8,   176,
      69,   435,   436,   183,   802,   244,   123,   183,   232,   100,
     101,   102,   274,   264,   864,   147,  1246,   397,    69,   183,
     402,  1732,   449,    65,   243,    35,    31,   893,   236,   442,
    1074,   236,   970,  1477,   117,   885,   163,    32,  1288,   889,
     241,   891,  1292,   893,   894,   911,   896,  1363,   256,   435,
     436,   256,  1149,  1150,  1151,   232,   147,    27,   149,   241,
     442,   911,  1159,   306,   450,  2035,   157,   236,   120,   359,
     209,     9,   452,   183,   924,   294,   203,   927,  1175,   236,
    1552,   449,   183,  1180,   211,  1182,   183,  1184,   953,  1186,
     940,  1188,  1189,  1190,  1191,  1192,  1193,  1194,  1195,   256,
    1746,  1747,   107,    99,   305,  1149,  1150,  1151,   958,   183,
    1426,   924,   164,   375,  1725,  1159,   264,  1347,    56,   283,
     344,   305,   261,   305,   974,   975,  1772,   940,  1697,  1698,
    1699,   537,   889,   436,   176,  1781,  1180,   300,  1182,   230,
    1184,   258,  1186,   941,  1188,  1189,  1190,  1191,  1192,  1193,
    1194,  1195,   353,   244,   229,   869,   283,  1254,  1791,   398,
    2217,  2218,  1392,   343,   232,  1855,   161,   343,   405,  1880,
      62,   353,  1486,   342,  1585,  1629,   890,  1873,   892,   349,
    1891,  1892,   436,   897,   435,  2003,  2003,   229,   442,   317,
    2003,    28,   906,  1889,  1890,   295,     9,    30,   436,  1810,
     436,   232,  2003,  2003,  1705,  1936,  1937,  1938,  1939,  1710,
    1711,  1527,   196,  1714,  1715,  1716,  1849,  1718,  1719,  1316,
    1536,   296,     1,   431,   443,   444,   336,   232,   232,   191,
     435,   436,   170,  1944,  1945,   336,  1086,  1707,   254,   307,
     244,   243,  1712,    56,  1940,   240,   343,  1943,   449,   207,
    1347,   503,   436,   191,   296,   173,   508,  1354,  1355,  1356,
    1357,  1358,  1359,  1360,   198,    82,  1912,   449,    47,   343,
     232,   274,   420,   401,   232,   112,  1141,   239,   435,  1376,
     191,   219,    61,   299,   288,  1931,   355,   435,   199,  1775,
     123,  1777,   294,   228,   232,   229,   280,   449,   233,  1056,
    2186,   239,  1948,  1347,   355,   396,   117,   218,  1022,   436,
    1354,  1355,  1356,  1357,  1358,  1359,  1360,  1074,  1707,  1779,
      99,  1171,  1775,  1712,  1777,   449,  1812,   184,     1,  2028,
     248,     4,  2028,  1131,   123,   435,   436,   363,  2015,   351,
    2017,   363,    69,  1989,  1990,   436,    19,   236,   310,   241,
     363,  1581,  1998,   210,   265,   266,    29,   302,  1844,  1812,
     295,   270,   273,   274,   367,  1892,   104,   256,   279,   280,
    1830,  2019,   310,   449,   443,   444,   445,   446,   191,   448,
     314,   163,   451,   164,  2080,   164,   412,   321,   314,    62,
     412,  1844,   443,   444,   445,   446,   236,   448,  1248,   412,
     451,   435,  2288,   184,   121,   184,   219,   363,  1819,   412,
    2285,   373,   990,   305,   371,   449,   256,  1944,  1945,   232,
     209,   203,  1342,   332,   363,   359,   239,  2302,  1278,   211,
     319,   210,   436,   117,   172,   373,   215,  1015,   442,  2085,
     402,   443,   444,   369,   370,   380,   184,  2093,   227,  1546,
    1547,     6,     9,   364,     9,    12,   412,  1214,    15,    16,
     151,   353,  2108,   372,   402,   374,   358,   405,    11,   258,
     166,  2119,   261,   412,   191,  1325,  1572,  2002,  2155,   436,
     442,  1578,    25,    26,   399,   232,  1336,  1337,   403,   417,
    2136,  1587,  2138,   450,  1549,   194,   195,   310,   436,  2145,
     449,   283,   430,   449,   442,  2201,   351,   254,   204,   449,
    2206,  1225,  1923,   236,    57,   232,   212,  1790,   209,  2165,
    2166,   410,   239,  1336,  1337,   198,    81,   132,   306,   236,
    1287,   291,   292,   256,   251,   314,   315,   236,   191,   156,
     314,    96,   316,   160,   436,   305,   435,   294,   327,   256,
     329,    94,    95,   305,    97,   399,   229,   256,   449,   403,
     373,    11,   105,   236,   223,   224,   153,   154,   259,  1326,
     261,   273,  1845,   275,   351,    25,    26,    12,  2226,   232,
      15,    16,   314,     2,   316,  1629,   239,     6,  2043,   402,
     438,   351,   405,   310,   181,  2241,  1404,   166,   153,  1407,
     187,  1917,   449,  1919,  1412,   148,   149,    57,   281,    81,
    1707,   223,   224,   159,   287,  1712,   159,   163,   432,  2105,
     434,  2107,   351,   436,    96,   180,   191,  1477,   355,   442,
    1180,   218,   229,   230,  1184,   222,   191,   445,   446,   191,
     448,   314,  1192,  1193,    94,    95,   235,    97,   321,   436,
     429,   421,   422,   423,   424,   105,   373,   310,   336,   376,
     377,   334,   573,  1707,   265,   266,   221,   232,  1712,   150,
     449,   152,   354,   228,   239,  1809,   260,   232,   262,   234,
     232,   150,   237,   152,   239,   358,   359,   239,   361,   314,
     233,   316,   249,   250,  1791,   449,   369,  1970,   148,   149,
     229,   230,  1799,   265,   266,   449,   379,  2232,   180,   159,
     267,   268,   449,   449,   269,  2126,   443,   444,   445,   446,
     373,   448,   212,   449,   451,   442,    71,   400,    33,   449,
     400,    36,   431,   449,   231,   351,   435,   449,   436,    44,
      45,    46,   178,   449,   278,   310,   449,   275,  1882,   390,
      24,     6,  1849,  1618,     9,   310,   449,   351,   310,  1609,
     232,   327,   234,   367,   210,   237,   449,   104,   436,  1634,
     379,  2087,   362,  2089,    56,    30,   449,   421,   422,   423,
     424,   436,   337,   233,    84,    12,    13,    14,  1586,   442,
     172,   449,   351,    20,   367,   346,  1609,   269,   278,  1556,
     106,   232,  1652,  2076,   347,   358,   207,   449,   373,  2220,
      65,   245,  2223,    67,   249,   250,  1614,   449,   373,  1669,
     351,   373,   245,  1621,    23,   272,    81,   382,   383,   436,
    1628,    58,   267,   268,   449,  1592,   232,   402,   296,  1652,
      83,    96,  1599,   449,   387,    83,   395,   402,   436,   430,
     155,   436,   407,   312,   379,   429,  1669,   230,   398,  1709,
     196,  2272,   314,   450,   436,   337,   453,   454,   173,    55,
     425,   436,   359,   379,    89,    90,   398,   442,   433,   435,
    1678,   436,    27,  1681,   367,   190,   184,   442,   449,   351,
     442,   449,   214,   436,  2305,   450,  1709,   347,   113,   359,
     436,   221,   443,   444,   445,   446,   449,   448,   223,   432,
     382,   383,   341,   210,   455,   106,   232,   443,   444,   445,
     446,   400,   448,   301,   861,   180,   153,   154,   865,   455,
      37,   376,   282,   238,   871,   407,   191,   387,   442,   876,
     877,     9,   276,   398,   452,   882,   883,   884,   421,   422,
     423,   424,   889,   425,   181,   395,    27,  1755,   895,   357,
     187,   433,   272,  1761,   436,   456,   221,   904,   905,   395,
     907,   171,   449,   228,   229,   449,   400,   232,   133,   234,
     285,   232,   237,   210,   239,   436,   436,   443,   444,   445,
     446,   218,   448,   104,    17,   222,   435,   169,   397,  1864,
     184,   443,   444,   445,   446,  1803,   448,   232,   452,   451,
      30,   124,   201,    81,   269,  2183,   125,    56,   955,   452,
     452,  2039,   452,   398,   452,   252,   253,   452,    96,   127,
     257,   452,   452,   338,   443,   444,   445,   446,   452,   448,
     267,   296,   451,   348,   452,   452,   452,   274,   428,   986,
     343,   314,   279,   129,    98,   310,   130,  1814,   398,   443,
     444,   445,   446,  1820,   448,   394,    49,   451,   134,   397,
     297,   135,  1870,   397,   289,   290,   395,  1875,  1751,  1752,
    1753,  1754,   337,   392,  1021,   176,  1884,   443,   444,   445,
     446,   140,   448,   244,    49,   451,   143,   430,   176,   109,
    1814,   360,   328,   375,   409,   443,   444,   445,   446,   111,
     448,  1048,   180,   451,   111,   330,   331,   435,   373,  1056,
    1057,   398,   436,   191,   183,   336,  1976,   382,   383,   304,
     443,   444,   445,   446,   160,   448,   232,  1074,   451,   131,
     432,   168,   398,   361,   206,   398,    49,   402,   176,   214,
     206,   119,   407,  1090,   275,   189,   441,   448,   336,   440,
     214,  1098,   265,  1976,   232,  1102,   234,   451,   229,   237,
     425,   239,   451,  1110,   393,   451,  1113,   398,   433,   128,
     451,   436,   261,   368,   264,   260,   395,   442,   183,  2210,
     326,   398,    49,   135,     8,   176,   432,   123,  2063,  1136,
     432,   269,  1139,   398,     9,   302,   170,   198,   303,   399,
     263,   339,  1149,  1150,  1151,   442,   443,   444,   445,   446,
     324,   448,  1159,   450,   451,   122,   453,   454,   429,   107,
      49,   429,   172,  2031,   280,   139,   138,   258,  1175,   257,
     236,   141,   310,  1180,  2042,  1182,  2044,  1184,   284,   279,
     295,  1188,  1189,  1190,  1191,  1192,  1193,  1194,  1195,   110,
     389,     7,   216,   113,    66,   153,   153,   126,   323,   337,
     133,   323,  2122,    99,    49,   236,   214,  2075,   142,   145,
     262,    93,   259,    90,   217,   199,   432,   188,   436,    49,
     302,   385,   236,   401,   171,   236,   339,   144,   288,   302,
     176,   417,   137,     6,    49,   373,   338,    22,  2173,   131,
      54,   186,   181,   171,   382,   383,  1299,  1254,   204,  1122,
       6,   491,   570,     9,   425,   135,  1337,  1264,  2193,  2194,
    2128,  1330,  1123,  1860,   402,   930,   581,  1813,  2188,   407,
    1277,   220,   109,   374,   227,    49,   856,  1284,  1868,   153,
     302,   557,  1654,   831,  1291,  2208,   844,   425,   539,  2058,
    2210,  1298,   123,    49,   943,   433,  2194,  1734,   436,   806,
    1817,   473,  1389,  1310,   442,  2188,  2174,  2175,  1693,  1316,
    2178,  1031,  1388,  1732,  1036,  1322,  1244,  2185,  2253,  2254,
    1768,  1241,  2257,  1519,  2259,    81,  1251,  2210,  1960,    85,
    1799,  1778,  1339,  1257,  1544,  1074,  1818,  1568,  1292,  1326,
      96,  1834,  1098,  1107,   896,  1096,  1599,  1354,  1355,  1356,
    1357,  1358,  1359,  1360,  1599,  2013,  2224,  1671,  1825,  2279,
    1493,  2296,  2129,     1,  1581,  2285,  2018,  2024,     6,  1376,
    1086,     9,  1208,   956,    12,    13,    14,   234,  1204,  1609,
    2164,   836,  2302,   313,   963,  1262,  1039,  2255,   590,  1396,
    2212,    57,   797,  1432,   971,  1876,  2279,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1418,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2287,
      58,    -1,    -1,    -1,   180,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   191,    -1,    -1,    -1,    -1,
      -1,  2225,    -1,    81,    -1,    -1,    37,    38,    39,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,
      -1,    -1,    -1,    -1,    -1,   221,    -1,    -1,    -1,    -1,
      -1,    -1,   228,  1480,  1481,    -1,   232,    -1,   234,    -1,
      -1,   237,    73,   239,    75,    76,    77,    78,    79,    80,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  2286,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   269,    -1,   153,   154,    -1,   274,    -1,
      -1,    -1,    -1,    -1,   115,    -1,    -1,    -1,     6,    -1,
      -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1546,
    1547,    -1,   180,   181,    -1,  1552,  1553,    -1,    -1,   187,
      -1,    -1,    -1,   191,   310,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1570,   320,    -1,    -1,    -1,    -1,    -1,
      -1,  1578,   210,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     218,   337,    -1,   221,   222,    -1,  1593,    -1,    -1,    -1,
     228,  1598,  1599,    -1,   232,    -1,   234,    -1,    -1,   237,
      -1,   239,    -1,    81,    -1,    -1,   197,    -1,    -1,    -1,
      -1,   367,    -1,    -1,   252,   253,    -1,   373,    96,   257,
      -1,    -1,  1629,    -1,    -1,    -1,   382,   383,    -1,   267,
      -1,   269,    -1,  1640,    -1,  1642,   274,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   402,    -1,    -1,    -1,
      -1,   407,    -1,    -1,    -1,    -1,   412,    -1,   249,   297,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   146,   425,
      -1,    -1,   310,   429,    -1,    -1,    -1,   433,    -1,    -1,
     436,    -1,    -1,    -1,    -1,    -1,   442,    -1,    -1,    -1,
    1697,  1698,  1699,    -1,    -1,   286,    -1,    -1,    -1,   337,
    1707,    -1,   180,    -1,   295,  1712,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   191,    -1,    -1,    -1,   308,  1725,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   373,    -1,    -1,    -1,    -1,
      81,    -1,    -1,   221,   382,   383,    -1,    -1,    -1,    -1,
     228,    -1,    -1,    -1,   232,    96,   234,    -1,    -1,   237,
      -1,   239,    -1,    -1,   402,    -1,    -1,    -1,    -1,   407,
      -1,    -1,    -1,   364,   365,   366,    -1,  1784,    -1,    -1,
      -1,    -1,    -1,  1790,  1791,    -1,    -1,   425,    -1,    -1,
      -1,   269,  1799,    -1,    -1,   433,    -1,    -1,   436,    -1,
      -1,    -1,    -1,  1810,   442,   443,   444,    -1,    -1,    -1,
     448,  1818,   450,    -1,   452,   453,   454,    -1,    -1,    -1,
      -1,    -1,   413,   414,   415,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   310,   174,    -1,    -1,     0,     1,  1845,   180,
      -1,    -1,  1849,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,   337,
      -1,    -1,  1869,    -1,    -1,    -1,  1873,    -1,    -1,    -1,
      34,    -1,    -1,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,  1889,  1890,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   232,    -1,   234,    -1,   373,   237,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   382,   383,    -1,    -1,    -1,    73,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,   399,    -1,    -1,   402,   403,    -1,    -1,   269,   407,
      -1,    -1,    -1,  1940,    -1,    -1,  1943,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   425,    -1,    -1,
      -1,   115,    -1,    -1,    -1,   433,    -1,    -1,   436,    -1,
      -1,    -1,    -1,  1970,   442,    -1,     0,     1,   132,     3,
      -1,     5,   136,    -1,    -1,    -1,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  2002,   337,    -1,    -1,    -1,
     164,   165,  2009,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   179,    -1,    51,    52,    -1,
     184,  2028,    -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   197,    -1,    -1,    70,    -1,  2045,    -1,
      74,   382,   383,    -1,    -1,    -1,   210,    -1,    -1,   213,
      -1,   392,    86,    -1,    -1,   219,    -1,    -1,    -1,   223,
     224,    -1,    -1,    -1,    -1,    -1,   407,   231,   232,    -1,
      -1,   235,    -1,  2080,   108,    -1,   417,    -1,    -1,    -1,
      -1,   115,   116,    -1,   425,   249,    -1,    -1,    -1,   430,
      -1,    -1,   433,    -1,   435,   436,    -1,    -1,   132,    -1,
      -1,    -1,   136,    -1,    -1,    -1,    -1,   271,    -1,    -1,
      -1,    -1,   146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   286,    -1,   158,    31,    -1,    33,   162,   293,
      36,   295,  2139,    -1,    -1,    -1,    -1,    -1,   302,    -1,
      46,   175,   306,    -1,   308,   179,    -1,  2154,   182,    -1,
    2157,   185,   186,    -1,   318,    -1,    -1,    -1,    -1,   193,
      -1,   325,    -1,   327,    -1,    -1,   200,    -1,   202,    -1,
      -1,   205,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    2187,    -1,   346,    -1,    -1,   349,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2201,    -1,    -1,    -1,   362,  2206,
     364,   365,   366,    -1,    -1,    -1,    -1,    -1,   242,    -1,
      -1,    -1,   246,    -1,   248,    -1,    -1,    -1,    -1,    -1,
      -1,   255,    -1,    -1,   388,  2232,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2243,    -1,    -1,    -1,
      -1,   405,    -1,   277,    -1,    -1,    -1,    -1,    -1,   413,
     414,   415,     1,    -1,     3,    -1,     5,    -1,   292,    -1,
      -1,    10,   426,    -1,    -1,   429,    -1,   173,    -1,    18,
      -1,   177,   306,    -1,   438,    -1,    -1,    -1,    -1,   313,
      -1,    -1,  2289,    -1,   190,   449,    -1,    -1,   322,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   335,    51,    52,    -1,    -1,   340,    -1,   342,    -1,
      59,    -1,    -1,    -1,    -1,    -1,   350,    -1,    -1,    -1,
      -1,    70,    -1,    -1,    -1,    74,   360,    -1,    -1,    -1,
      -1,    -1,   238,    -1,    -1,   369,    -1,    86,    -1,    -1,
      -1,    -1,    -1,    -1,   378,    -1,   380,   381,    -1,    -1,
     384,    -1,   386,    -1,    -1,    -1,    -1,   391,    -1,   108,
      -1,    -1,    -1,    -1,    -1,    -1,   115,   116,    -1,    -1,
      -1,    -1,   406,    -1,   123,    -1,    -1,   411,    -1,   285,
      -1,    -1,   416,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   427,    -1,    -1,    -1,   146,    -1,    -1,
      -1,    -1,   436,   309,    -1,   439,    -1,    -1,    -1,   158,
      -1,    -1,    -1,   162,    -1,   449,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   175,   333,    -1,    -1,
      -1,    -1,   338,   182,    -1,    -1,   185,   186,    -1,    -1,
      -1,    -1,   348,    -1,   193,    -1,   352,    -1,    -1,    -1,
      -1,   200,    -1,   202,    -1,    -1,   205,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       6,    -1,    -1,     9,    -1,    -1,    12,    13,    14,    -1,
      -1,    17,    -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   242,    -1,    -1,    -1,   246,    -1,   248,
      -1,    -1,    -1,   409,    -1,    -1,   255,    -1,    -1,    -1,
      -1,    -1,    -1,   419,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,   277,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   292,    -1,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      96,    -1,    -1,    -1,   313,    -1,    -1,    -1,    -1,    -1,
      -1,     6,    -1,   322,     9,    -1,    -1,    12,    13,    14,
      -1,    -1,    -1,    -1,    -1,    -1,   335,    -1,    -1,    -1,
      -1,   340,    -1,   342,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   350,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   360,    -1,    -1,    -1,    -1,    -1,   153,   154,    -1,
     369,    -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,   378,
      -1,   380,   381,    -1,    -1,   384,    -1,   386,    -1,    -1,
      -1,    -1,   391,    -1,   180,   181,    81,    -1,    -1,    -1,
      -1,   187,    -1,    -1,    -1,   191,    -1,   406,    -1,    -1,
      -1,    96,   411,    -1,    -1,    -1,    -1,   416,    -1,    -1,
      -1,    -1,    -1,    -1,   210,    -1,    -1,    -1,   427,    -1,
      -1,    -1,   218,    -1,    -1,   221,   222,   436,    -1,    -1,
     439,    -1,   228,    -1,    -1,    -1,   232,    -1,   234,    -1,
     449,   237,    -1,   239,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   252,   253,   153,   154,
      -1,   257,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   267,    -1,   269,    -1,    -1,    -1,     6,   274,    -1,
       9,    -1,    -1,    -1,    -1,   180,   181,    -1,    -1,    -1,
      -1,    -1,   187,    -1,    -1,    -1,   191,    -1,    -1,    -1,
      -1,   297,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   310,   210,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   218,    -1,    -1,   221,   222,    -1,    -1,
      -1,    -1,    -1,   228,    -1,    -1,    -1,   232,    -1,   234,
      -1,   337,   237,    -1,   239,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    -1,    -1,    -1,    -1,   252,   253,    -1,
      -1,    -1,   257,    -1,    -1,    -1,    -1,    96,    -1,    -1,
      -1,    -1,   267,    -1,   269,    -1,    -1,   373,    -1,   274,
     109,    -1,    -1,    -1,    -1,    -1,   382,   383,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   297,   399,    -1,    -1,   402,   403,    -1,    -1,
      -1,   407,    -1,    -1,     6,   310,    -1,     9,    -1,     3,
      -1,     5,    -1,    -1,    -1,    -1,    10,    -1,    -1,   425,
      -1,    -1,    -1,    -1,    18,    -1,    -1,   433,    -1,    -1,
     436,    -1,   337,    -1,    -1,    -1,   442,   443,   444,    -1,
      -1,   180,   448,    -1,   450,    -1,   452,   453,   454,    -1,
      -1,    -1,   191,    -1,    -1,    -1,    -1,    51,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    -1,   206,   373,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,   382,   383,    81,
      74,    -1,   221,    -1,    -1,    -1,    -1,    -1,    -1,   228,
      92,    -1,    86,   232,    96,   234,    -1,   402,   237,    -1,
     239,    -1,   407,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,
     425,   115,   116,    -1,    -1,    -1,    -1,    -1,   433,    -1,
     269,   436,    -1,    -1,    -1,    -1,    -1,   442,   443,   444,
      -1,    -1,    -1,   448,    -1,   450,    -1,   452,   453,   454,
      -1,    -1,   146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   158,    -1,    -1,    -1,   162,    -1,
      -1,   310,    -1,    -1,    -1,     3,    -1,     5,   180,    -1,
      -1,   175,    10,    -1,    -1,    -1,    -1,    -1,   182,   191,
      18,   185,   186,    -1,    -1,    -1,    -1,    -1,   337,   193,
      -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,   202,    -1,
      -1,   205,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   221,
      -1,    -1,    -1,    51,    52,    -1,   228,    -1,    -1,    -1,
     232,    59,   234,    -1,   373,   237,    -1,   239,    -1,    -1,
      -1,    -1,    70,   382,   383,    -1,    74,    -1,   242,    -1,
       6,    -1,   246,     9,   248,    -1,    -1,    -1,    86,    -1,
      -1,   255,    -1,   402,    -1,    -1,    -1,   269,   407,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     108,    -1,    -1,   277,    -1,    -1,   425,   115,   116,    -1,
      -1,    -1,    -1,    -1,   433,    -1,    -1,   436,   292,    -1,
      -1,    -1,    -1,   442,    -1,    -1,    -1,    -1,   310,    -1,
      -1,    -1,    -1,    -1,     6,    -1,    -1,     9,   146,   313,
      -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,   322,    -1,
     158,    -1,    -1,    -1,   162,   337,    92,    -1,    -1,    -1,
      96,   335,    -1,    -1,    -1,    -1,   340,   175,   342,    -1,
      -1,    -1,    -1,    -1,   182,    -1,   350,   185,   186,    -1,
      -1,    -1,    -1,    -1,    -1,   193,   360,    -1,    -1,    -1,
      -1,   373,   200,    -1,   202,   369,    -1,   205,    -1,    -1,
     382,   383,    -1,    -1,   378,    -1,   380,   381,    -1,    81,
     384,    -1,   386,    -1,    -1,    -1,    -1,   391,    -1,    -1,
     402,    -1,    -1,    -1,    96,   407,    -1,    -1,    -1,    -1,
      -1,    -1,   406,    -1,   242,    -1,     6,   411,   246,     9,
     248,    -1,   416,   425,   180,    -1,    -1,   255,    -1,    -1,
      -1,   433,    -1,   427,   436,   191,    -1,    -1,    -1,    -1,
     442,    -1,    -1,    -1,    -1,   439,    -1,    -1,    -1,   277,
      -1,    -1,    -1,    -1,    -1,   449,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   292,   221,    -1,    -1,    -1,    -1,
      -1,    -1,   228,    -1,     6,    -1,   232,     9,   234,    -1,
      -1,   237,    -1,   239,    -1,   313,    -1,    -1,   180,    -1,
      -1,    81,    -1,    -1,   322,    -1,    -1,    -1,    -1,   191,
      -1,    -1,    -1,    -1,    -1,    -1,    96,   335,    -1,    -1,
      -1,    -1,   340,   269,   342,    -1,    -1,    -1,    -1,   109,
      -1,    -1,   350,     6,    -1,    -1,     9,    -1,    -1,   221,
      -1,    -1,   360,    -1,    -1,    -1,   228,    -1,    -1,    -1,
     232,   369,   234,    -1,    -1,   237,    -1,   239,    -1,    81,
     378,    -1,   380,   381,   310,    -1,   384,    -1,   386,    -1,
      92,    -1,    -1,   391,    96,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   269,   406,    -1,
      -1,   337,    -1,   411,    -1,    -1,    -1,    -1,   416,    -1,
     180,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,   427,
      -1,   191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   439,    -1,    96,    -1,    -1,    -1,   373,   310,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   382,   383,    -1,    -1,
      -1,   221,    -1,    -1,     6,    -1,    -1,     9,   228,    -1,
      -1,    -1,   232,    -1,   234,   337,   402,   237,   180,   239,
      -1,   407,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   191,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   425,
      -1,    -1,    -1,    -1,    -1,    96,    -1,   433,    -1,   269,
     436,   373,    -1,    -1,    -1,    -1,   442,    -1,    -1,   221,
     382,   383,     6,   176,    -1,     9,   228,   180,    -1,    -1,
     232,    -1,   234,    -1,    -1,   237,   398,   239,   191,    81,
     402,    -1,    -1,     6,    -1,   407,     9,    -1,    -1,    -1,
     310,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   425,    -1,    -1,    -1,   269,   221,    -1,
      -1,   433,    -1,    -1,   436,   228,    -1,   337,    -1,   232,
     442,   234,    -1,    -1,   237,    -1,   239,    -1,    -1,   180,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,
     191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,
      -1,    -1,    96,   373,    -1,    -1,   269,    -1,    81,    -1,
      -1,    -1,   382,   383,     6,    -1,    -1,     9,    -1,    -1,
      -1,    -1,    -1,    96,    -1,   337,    -1,    -1,   180,    -1,
      -1,   232,   402,   234,    -1,    -1,   237,   407,   239,   191,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   425,    -1,    -1,    -1,    -1,
      -1,   373,    -1,   433,    -1,    -1,   436,    -1,   269,   221,
     382,   383,   442,    -1,   337,    -1,   228,    -1,    -1,    -1,
     232,    -1,   234,    -1,    -1,   237,   180,   239,    -1,    81,
     402,    -1,    -1,    -1,    -1,   407,    -1,   191,    -1,    -1,
      -1,    -1,    -1,    -1,    96,    -1,    -1,   180,    -1,   310,
     373,    -1,    -1,   425,    -1,    -1,    -1,   269,   191,   382,
     383,   433,    -1,    -1,   436,    -1,    -1,   221,    -1,    -1,
     442,    -1,    -1,    -1,   228,    -1,   337,    -1,   232,   402,
     234,    -1,    -1,   237,   407,   239,    -1,    -1,   221,    -1,
      -1,    -1,    -1,    -1,    -1,   228,    -1,    -1,   310,   232,
      -1,   234,   425,    -1,   237,    -1,   239,    -1,    -1,    -1,
     433,    -1,   373,   436,    -1,   269,    -1,    -1,    -1,   442,
      -1,   382,   383,    -1,    -1,   337,    -1,    -1,   180,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   269,    -1,    -1,   191,
      -1,   402,    -1,    -1,    -1,    -1,   407,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   367,   310,    -1,    -1,    -1,
      -1,   373,    -1,    -1,   425,    -1,    -1,    -1,    -1,   221,
     382,   383,   433,    -1,    -1,   436,   228,   310,    -1,    -1,
     232,   442,   234,   337,    -1,   237,    -1,   239,    -1,    -1,
     402,    -1,    -1,    -1,    -1,   407,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   337,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   425,   368,    -1,    -1,   269,    -1,   373,
      -1,   433,    -1,    -1,   436,    -1,    -1,    -1,   382,   383,
     442,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     373,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   402,   382,
     383,    -1,    -1,   407,    -1,    -1,    -1,    -1,   310,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   402,
      -1,   425,    -1,    -1,   407,    -1,    -1,    -1,    81,   433,
      -1,    -1,   436,    -1,    -1,   337,    -1,    -1,   442,    -1,
      -1,    -1,   425,    96,    -1,    -1,    -1,    -1,    -1,    -1,
     433,    -1,    -1,   436,    -1,    -1,    -1,    -1,    -1,   442,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   373,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     382,   383,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     402,    31,    -1,    33,    -1,   407,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,   425,    -1,    -1,    -1,   180,    -1,    -1,
      -1,   433,    -1,    -1,   436,    65,    -1,    -1,   191,    -1,
     442,    -1,    -1,    73,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   221,    -1,
      -1,    -1,    -1,    -1,    -1,   228,    -1,    -1,    -1,   232,
      -1,   234,    -1,    -1,   237,   115,   239,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   269,    -1,    -1,    -1,
      -1,    65,    66,    -1,    -1,   155,    -1,    -1,    -1,    73,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    -1,    -1,   173,    -1,    -1,   176,   177,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,
     190,    -1,    -1,    -1,    -1,    -1,    -1,   197,    -1,    -1,
      -1,   115,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    -1,    -1,   213,   337,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    -1,    -1,    -1,    -1,   229,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   238,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,   249,
     373,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   382,
     383,    96,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   271,    -1,    -1,   188,    -1,    -1,    -1,    -1,   402,
      -1,    -1,    -1,   197,   407,   285,   286,    -1,    -1,    -1,
      -1,    -1,    -1,   293,    -1,   295,    -1,    -1,    -1,   213,
     174,    -1,   425,    -1,    -1,    -1,   180,    -1,   308,   309,
     433,    -1,    -1,   436,    -1,   229,   230,    -1,    -1,   442,
     443,   444,    -1,    -1,    -1,    -1,    81,    -1,   451,   452,
      -1,    -1,    -1,   333,    -1,   249,    -1,    -1,   338,    -1,
     254,    96,    -1,    -1,    -1,   180,    -1,    -1,    -1,    -1,
      -1,    -1,   352,    -1,    -1,    -1,   191,   271,   232,    -1,
     234,    -1,   362,   237,   364,   365,   366,    -1,    -1,    -1,
      -1,    -1,   286,    -1,    -1,    -1,    -1,    -1,    -1,   293,
      -1,   295,    -1,    -1,   298,    -1,   221,    -1,    -1,    -1,
      -1,    -1,    -1,   228,   308,   269,    -1,   232,   398,   234,
      -1,    -1,   237,    -1,   239,    -1,    -1,    -1,    -1,   409,
      -1,    -1,    -1,   413,   414,   415,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   180,   426,    -1,   428,   429,
      -1,    -1,    -1,    -1,   269,    -1,   191,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   362,   449,
     364,   365,   366,    -1,    -1,    -1,    -1,   371,    -1,    -1,
      -1,    -1,    -1,   337,    -1,    -1,   221,    -1,    -1,    -1,
      -1,   385,    -1,   228,    -1,   310,    -1,   232,    -1,   234,
      -1,    -1,   237,    -1,   239,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   408,    -1,    -1,    -1,    -1,   413,
     414,   415,   337,    -1,    -1,    -1,    -1,    -1,   382,   383,
      -1,    -1,   426,    -1,   269,   429,   430,    -1,   392,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   407,    -1,   449,    -1,    -1,   373,    -1,
      -1,    -1,    -1,   417,    -1,    -1,    -1,   382,   383,    -1,
      -1,   425,    -1,    -1,    -1,   310,   430,    -1,    -1,   433,
      -1,   435,   436,    -1,    -1,    -1,    -1,   402,    -1,    -1,
      -1,    -1,   407,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   337,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     425,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   433,    -1,
      -1,   436,    -1,    -1,    -1,    -1,    -1,   442,   443,   444,
      -1,    -1,    -1,    -1,    -1,    -1,   451,   452,   373,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   382,   383,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   402,    -1,    -1,
      -1,    -1,   407,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     425,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   433,    -1,
      -1,   436,    -1,    -1,    -1,    -1,    -1,   442,   443,   444,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   452
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
    1050,  1051,  1052,  1053,  1054,    12,    13,    14,    58,   210,
     252,   253,   257,   267,   274,   297,   443,   444,   448,   452,
    1050,  1051,  1052,  1053,  1054,  1079,   304,   770,  1070,   774,
     183,   336,   778,   319,   410,   790,   791,  1158,  1045,   209,
     261,  1037,  1038,  1039,  1041,   420,   435,   807,  1158,   160,
    1012,  1013,  1012,  1012,  1012,  1079,  1059,  1079,    21,   399,
     403,   828,   829,  1046,   131,   831,   434,   823,   825,   432,
     824,   820,  1089,   111,   841,  1068,   846,     9,    12,    15,
      16,   249,   250,   267,   268,   853,   857,   168,  1083,     9,
      56,   170,   219,   405,   871,   872,   873,   867,   865,   948,
    1115,  1141,   398,  1076,  1059,  1079,   361,   891,   744,   745,
    1044,   901,   902,  1088,  1068,     8,    35,  1008,  1145,  1085,
     206,   905,   917,  1158,   925,  1122,  1088,   925,   398,   398,
     514,   146,   399,   403,  1079,    49,   214,   955,  1079,  1079,
     367,  1079,  1088,   176,  1059,  1079,  1083,  1124,   206,   985,
    1088,   156,   160,   997,     9,  1002,  1068,   917,   119,   554,
     275,   556,  1072,   556,   189,   682,   229,   230,   688,   629,
      31,    33,    36,    44,    45,    46,    65,   155,   173,   176,
     177,   190,   229,   238,   271,   285,   309,   333,   338,   352,
     398,   409,   428,   449,   640,   641,   643,   653,   656,   658,
     719,   722,  1141,   647,   648,  1089,  1095,  1097,   451,  1057,
    1057,  1057,  1057,  1057,  1057,   451,  1057,  1156,  1137,  1141,
    1011,  1013,   441,   440,  1083,  1011,   214,    31,    33,    36,
      46,   173,   177,   190,   238,   285,   309,   333,   338,   348,
     352,   409,   419,   756,   757,  1011,   265,  1139,  1139,  1139,
     754,   753,   232,  1082,  1089,   451,  1088,   455,   451,  1056,
     451,   451,  1056,   451,   451,   451,   451,  1056,   451,   451,
     368,  1017,  1018,  1059,  1077,   336,  1156,   393,  1153,  1153,
     398,  1068,   775,   776,   777,  1124,  1088,  1088,   160,   284,
     779,   998,  1130,   236,   256,  1017,  1040,  1042,   128,   801,
    1041,    94,   300,   436,  1066,    33,    36,    44,    45,    46,
     155,   173,   190,   238,   285,   338,   348,   409,   808,   809,
    1012,   264,  1014,   260,  1015,   183,  1017,   183,  1118,   395,
     830,   826,   828,   744,  1141,   744,  1156,   326,   854,  1156,
     398,    49,   872,   874,  1083,     9,    56,   219,   405,   868,
     869,  1083,   949,  1116,   196,   280,  1142,    28,   112,   649,
    1076,  1017,   183,  1158,  1063,   135,   897,   746,     8,   176,
     905,  1088,   123,   258,  1027,  1028,  1030,  1037,   236,   256,
     432,   123,   432,   927,   928,  1083,  1082,  1079,  1133,  1037,
     965,  1158,  1088,  1017,   183,   398,     9,   983,   984,  1105,
     986,  1088,   965,   986,   302,  1000,   303,  1007,  1008,  1106,
     247,   314,   316,   564,  1133,   170,   683,  1093,   691,  1133,
    1139,   150,   152,  1133,  1086,  1139,  1093,  1088,  1088,  1072,
     198,   650,   649,   451,   399,   663,  1072,  1015,  1011,  1133,
    1133,   118,   418,   757,  1085,  1085,  1085,  1098,  1111,   451,
    1057,  1072,  1098,  1098,  1057,  1098,  1098,  1098,   219,   405,
    1098,  1098,  1019,   263,  1020,  1017,  1077,   153,   279,   153,
     279,   776,   274,   732,    85,   320,   429,   260,   262,   781,
     999,   780,   324,   339,   744,   744,   807,   807,   807,   807,
    1133,   150,   152,  1133,   118,   418,   809,   744,  1016,  1059,
    1060,  1059,  1060,   829,  1045,   744,  1088,   122,   847,   429,
     855,   856,   857,   107,   858,   429,  1084,  1088,  1094,  1083,
      49,   876,   869,   172,   876,   945,  1133,   280,  1135,  1059,
     573,   892,  1158,   747,   902,  1079,   195,   906,  1158,  1029,
    1031,   138,   914,  1030,   139,   918,   236,  1045,   926,  1044,
     927,   257,   956,  1109,   141,   957,   284,  1022,  1023,   295,
    1111,  1059,  1084,   279,  1083,   110,   987,   389,   989,  1141,
     151,   259,  1009,  1032,  1033,  1035,  1038,     7,  1117,   564,
    1093,   113,   216,   684,    66,    65,    66,   188,   229,   230,
     254,   298,   371,   385,   408,   430,   449,   640,   641,   643,
     644,   653,   656,   658,   692,   693,   695,   696,   697,   698,
     700,   701,   702,   703,   707,   708,   442,  1087,  1088,  1093,
    1133,  1087,  1133,  1155,  1124,  1135,  1133,  1087,  1087,  1043,
    1124,  1043,  1017,   451,   744,  1021,  1156,   153,  1156,   153,
    1079,   126,   783,   782,   744,  1012,  1012,  1012,  1012,  1087,
    1087,  1043,  1043,   744,  1017,   323,  1017,   323,   848,   133,
     849,   856,    99,  1128,   876,   876,  1084,  1008,   203,   428,
     950,  1072,   947,  1017,   236,   256,    49,   236,   214,   907,
     194,   236,   256,   431,   744,   744,   923,   744,   929,   680,
    1050,  1051,  1052,  1053,  1054,  1024,   142,   966,   262,  1025,
    1088,  1017,  1017,   984,  1132,    93,   988,  1132,  1022,   163,
     203,   211,   283,   994,  1063,  1034,  1036,   145,  1010,  1035,
     288,  1066,  1087,  1133,    90,   217,   685,   266,  1139,   199,
     709,   265,   266,   706,  1119,   188,   432,  1133,  1140,  1133,
    1088,   698,   254,   294,   704,   705,  1093,   243,   294,   443,
     444,   721,   243,   294,   443,   444,   720,   436,   651,   652,
    1133,  1094,  1087,   744,  1156,  1156,   744,  1060,  1060,   744,
      49,   876,   401,   877,   302,  1063,   183,   283,   951,  1090,
     339,  1079,  1133,   908,  1027,  1038,   236,   236,   744,   744,
     744,  1026,  1088,  1132,  1088,   144,   990,   744,   744,   229,
     230,  1136,  1093,  1133,  1133,   171,   686,  1133,  1134,  1133,
    1044,  1088,   699,  1072,    89,    90,   113,   289,   290,   330,
     331,   694,   176,   288,  1093,   705,  1087,  1087,   652,  1071,
    1136,  1017,  1017,  1079,  1079,  1133,  1063,   302,   417,   680,
     137,   909,   744,  1088,  1093,  1093,  1133,  1093,  1093,  1111,
    1079,   898,  1133,  1044,  1093,    49,   898,  1079
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

  case 1270:

/* Line 1455 of yacc.c  */
#line 6658 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1271:

/* Line 1455 of yacc.c  */
#line 6659 "parser.y"
    { push_expr (')', NULL); ;}
    break;

  case 1272:

/* Line 1455 of yacc.c  */
#line 6661 "parser.y"
    { push_expr ('O', NULL); ;}
    break;

  case 1273:

/* Line 1455 of yacc.c  */
#line 6662 "parser.y"
    { push_expr ('9', NULL); ;}
    break;

  case 1274:

/* Line 1455 of yacc.c  */
#line 6663 "parser.y"
    { push_expr ('A', NULL); ;}
    break;

  case 1275:

/* Line 1455 of yacc.c  */
#line 6664 "parser.y"
    { push_expr ('L', NULL); ;}
    break;

  case 1276:

/* Line 1455 of yacc.c  */
#line 6665 "parser.y"
    { push_expr ('U', NULL); ;}
    break;

  case 1277:

/* Line 1455 of yacc.c  */
#line 6666 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1278:

/* Line 1455 of yacc.c  */
#line 6668 "parser.y"
    { push_expr ('O', NULL); ;}
    break;

  case 1279:

/* Line 1455 of yacc.c  */
#line 6669 "parser.y"
    { push_expr ('9', NULL); ;}
    break;

  case 1280:

/* Line 1455 of yacc.c  */
#line 6670 "parser.y"
    { push_expr ('A', NULL); ;}
    break;

  case 1281:

/* Line 1455 of yacc.c  */
#line 6671 "parser.y"
    { push_expr ('L', NULL); ;}
    break;

  case 1282:

/* Line 1455 of yacc.c  */
#line 6672 "parser.y"
    { push_expr ('U', NULL); ;}
    break;

  case 1283:

/* Line 1455 of yacc.c  */
#line 6673 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1284:

/* Line 1455 of yacc.c  */
#line 6675 "parser.y"
    { push_expr ('P', NULL); ;}
    break;

  case 1285:

/* Line 1455 of yacc.c  */
#line 6676 "parser.y"
    { push_expr ('N', NULL); ;}
    break;

  case 1286:

/* Line 1455 of yacc.c  */
#line 6678 "parser.y"
    { push_expr ('P', NULL); ;}
    break;

  case 1287:

/* Line 1455 of yacc.c  */
#line 6679 "parser.y"
    { push_expr ('N', NULL); ;}
    break;

  case 1288:

/* Line 1455 of yacc.c  */
#line 6680 "parser.y"
    { push_expr ('x', cb_zero); ;}
    break;

  case 1292:

/* Line 1455 of yacc.c  */
#line 6687 "parser.y"
    { push_expr ('(', NULL); ;}
    break;

  case 1293:

/* Line 1455 of yacc.c  */
#line 6689 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1294:

/* Line 1455 of yacc.c  */
#line 6690 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1295:

/* Line 1455 of yacc.c  */
#line 6691 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1296:

/* Line 1455 of yacc.c  */
#line 6693 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1297:

/* Line 1455 of yacc.c  */
#line 6694 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1298:

/* Line 1455 of yacc.c  */
#line 6696 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1299:

/* Line 1455 of yacc.c  */
#line 6697 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1300:

/* Line 1455 of yacc.c  */
#line 6698 "parser.y"
    { push_expr ('*', NULL); ;}
    break;

  case 1301:

/* Line 1455 of yacc.c  */
#line 6699 "parser.y"
    { push_expr ('/', NULL); ;}
    break;

  case 1302:

/* Line 1455 of yacc.c  */
#line 6700 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1303:

/* Line 1455 of yacc.c  */
#line 6702 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1304:

/* Line 1455 of yacc.c  */
#line 6703 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1305:

/* Line 1455 of yacc.c  */
#line 6704 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1306:

/* Line 1455 of yacc.c  */
#line 6705 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1307:

/* Line 1455 of yacc.c  */
#line 6706 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1308:

/* Line 1455 of yacc.c  */
#line 6707 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1309:

/* Line 1455 of yacc.c  */
#line 6709 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1310:

/* Line 1455 of yacc.c  */
#line 6710 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1311:

/* Line 1455 of yacc.c  */
#line 6711 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1312:

/* Line 1455 of yacc.c  */
#line 6712 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1313:

/* Line 1455 of yacc.c  */
#line 6713 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1314:

/* Line 1455 of yacc.c  */
#line 6714 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1315:

/* Line 1455 of yacc.c  */
#line 6716 "parser.y"
    { push_expr ('&', NULL); ;}
    break;

  case 1316:

/* Line 1455 of yacc.c  */
#line 6717 "parser.y"
    { push_expr ('|', NULL); ;}
    break;

  case 1330:

/* Line 1455 of yacc.c  */
#line 6729 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1331:

/* Line 1455 of yacc.c  */
#line 6730 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1335:

/* Line 1455 of yacc.c  */
#line 6739 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1336:

/* Line 1455 of yacc.c  */
#line 6740 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '+', (yyvsp[(3) - (3)])); ;}
    break;

  case 1337:

/* Line 1455 of yacc.c  */
#line 6741 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '-', (yyvsp[(3) - (3)])); ;}
    break;

  case 1338:

/* Line 1455 of yacc.c  */
#line 6742 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '*', (yyvsp[(3) - (3)])); ;}
    break;

  case 1339:

/* Line 1455 of yacc.c  */
#line 6743 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '/', (yyvsp[(3) - (3)])); ;}
    break;

  case 1340:

/* Line 1455 of yacc.c  */
#line 6744 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1341:

/* Line 1455 of yacc.c  */
#line 6745 "parser.y"
    { (yyval) = cb_build_binary_op (cb_zero, '-', (yyvsp[(2) - (2)])); ;}
    break;

  case 1342:

/* Line 1455 of yacc.c  */
#line 6746 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '^', (yyvsp[(3) - (3)])); ;}
    break;

  case 1343:

/* Line 1455 of yacc.c  */
#line 6747 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1344:

/* Line 1455 of yacc.c  */
#line 6759 "parser.y"
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

  case 1345:

/* Line 1455 of yacc.c  */
#line 6771 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(3) - (3)])))) {
		(yyval) = CB_FILE (cb_ref ((yyvsp[(3) - (3)])))->linage_ctr;
	} else {
		cb_error_x ((yyvsp[(3) - (3)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(3) - (3)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1346:

/* Line 1455 of yacc.c  */
#line 6785 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1347:

/* Line 1455 of yacc.c  */
#line 6787 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1348:

/* Line 1455 of yacc.c  */
#line 6791 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)])); ;}
    break;

  case 1349:

/* Line 1455 of yacc.c  */
#line 6798 "parser.y"
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

  case 1350:

/* Line 1455 of yacc.c  */
#line 6820 "parser.y"
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

  case 1351:

/* Line 1455 of yacc.c  */
#line 6840 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1352:

/* Line 1455 of yacc.c  */
#line 6844 "parser.y"
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

  case 1353:

/* Line 1455 of yacc.c  */
#line 6860 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (1)])))) {
		(yyval) = (yyvsp[(1) - (1)]);
	} else {
		cb_error_x ((yyvsp[(1) - (1)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(1) - (1)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1354:

/* Line 1455 of yacc.c  */
#line 6873 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1355:

/* Line 1455 of yacc.c  */
#line 6875 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1356:

/* Line 1455 of yacc.c  */
#line 6879 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1357:

/* Line 1455 of yacc.c  */
#line 6885 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1358:

/* Line 1455 of yacc.c  */
#line 6887 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1359:

/* Line 1455 of yacc.c  */
#line 6892 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	CB_REFERENCE ((yyval))->offset = CB_TREE (current_section);
	current_program->label_list = cb_cons ((yyval), current_program->label_list);
  ;}
    break;

  case 1363:

/* Line 1455 of yacc.c  */
#line 6907 "parser.y"
    {
	(yyval) = cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(1) - (1)]))->data));
	(yyval)->source_file = (yyvsp[(1) - (1)])->source_file;
	(yyval)->source_line = (yyvsp[(1) - (1)])->source_line;
  ;}
    break;

  case 1364:

/* Line 1455 of yacc.c  */
#line 6917 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1365:

/* Line 1455 of yacc.c  */
#line 6918 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1366:

/* Line 1455 of yacc.c  */
#line 6923 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	current_program->reference_list = cb_cons ((yyval), current_program->reference_list);
  ;}
    break;

  case 1367:

/* Line 1455 of yacc.c  */
#line 6930 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1368:

/* Line 1455 of yacc.c  */
#line 6931 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1371:

/* Line 1455 of yacc.c  */
#line 6943 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE ((yyval))->word->count > 0) {
		redefinition_error ((yyval));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1372:

/* Line 1455 of yacc.c  */
#line 6962 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1373:

/* Line 1455 of yacc.c  */
#line 6963 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1375:

/* Line 1455 of yacc.c  */
#line 6968 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1376:

/* Line 1455 of yacc.c  */
#line 6972 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1377:

/* Line 1455 of yacc.c  */
#line 6973 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1379:

/* Line 1455 of yacc.c  */
#line 6978 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1380:

/* Line 1455 of yacc.c  */
#line 6979 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1381:

/* Line 1455 of yacc.c  */
#line 6980 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1382:

/* Line 1455 of yacc.c  */
#line 6981 "parser.y"
    { (yyval) = cb_build_ppointer ((yyvsp[(4) - (4)])); ;}
    break;

  case 1383:

/* Line 1455 of yacc.c  */
#line 6982 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1388:

/* Line 1455 of yacc.c  */
#line 6990 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1389:

/* Line 1455 of yacc.c  */
#line 6991 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1390:

/* Line 1455 of yacc.c  */
#line 6992 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1396:

/* Line 1455 of yacc.c  */
#line 7004 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1397:

/* Line 1455 of yacc.c  */
#line 7005 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1409:

/* Line 1455 of yacc.c  */
#line 7039 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1410:

/* Line 1455 of yacc.c  */
#line 7047 "parser.y"
    { (yyval) = cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1411:

/* Line 1455 of yacc.c  */
#line 7051 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1412:

/* Line 1455 of yacc.c  */
#line 7052 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1413:

/* Line 1455 of yacc.c  */
#line 7053 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1414:

/* Line 1455 of yacc.c  */
#line 7054 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 1415:

/* Line 1455 of yacc.c  */
#line 7058 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1416:

/* Line 1455 of yacc.c  */
#line 7059 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); CB_REFERENCE ((yyvsp[(1) - (3)]))->chain = (yyvsp[(3) - (3)]); ;}
    break;

  case 1417:

/* Line 1455 of yacc.c  */
#line 7064 "parser.y"
    {
	if (cb_ref ((yyvsp[(0) - (3)])) != cb_error_node) {
		(yyval) = (yyvsp[(0) - (3)]);
		CB_REFERENCE ((yyvsp[(0) - (3)]))->subs = cb_list_reverse ((yyvsp[(2) - (3)]));
	}
  ;}
    break;

  case 1418:

/* Line 1455 of yacc.c  */
#line 7074 "parser.y"
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

  case 1419:

/* Line 1455 of yacc.c  */
#line 7092 "parser.y"
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

  case 1420:

/* Line 1455 of yacc.c  */
#line 7119 "parser.y"
    {
	if (cb_tree_category ((yyvsp[(1) - (1)])) != CB_CATEGORY_NUMERIC) {
		cb_error (_("Integer value expected"));
	} else if (CB_LITERAL ((yyvsp[(1) - (1)]))->sign < 0 || CB_LITERAL ((yyvsp[(1) - (1)]))->scale) {
		cb_error (_("Integer value expected"));
	}
	(yyval) = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1421:

/* Line 1455 of yacc.c  */
#line 7130 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1422:

/* Line 1455 of yacc.c  */
#line 7132 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (2)]);
	if (CB_LITERAL_P ((yyvsp[(2) - (2)]))) {
		CB_LITERAL ((yyvsp[(2) - (2)]))->all = 1;
	}
  ;}
    break;

  case 1423:

/* Line 1455 of yacc.c  */
#line 7141 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1424:

/* Line 1455 of yacc.c  */
#line 7142 "parser.y"
    { (yyval) = cb_concat_literals ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1425:

/* Line 1455 of yacc.c  */
#line 7146 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1426:

/* Line 1455 of yacc.c  */
#line 7147 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 1427:

/* Line 1455 of yacc.c  */
#line 7148 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1428:

/* Line 1455 of yacc.c  */
#line 7149 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 1429:

/* Line 1455 of yacc.c  */
#line 7150 "parser.y"
    { (yyval) = cb_high; ;}
    break;

  case 1430:

/* Line 1455 of yacc.c  */
#line 7151 "parser.y"
    { (yyval) = cb_low; ;}
    break;

  case 1431:

/* Line 1455 of yacc.c  */
#line 7152 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1432:

/* Line 1455 of yacc.c  */
#line 7161 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1433:

/* Line 1455 of yacc.c  */
#line 7165 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1434:

/* Line 1455 of yacc.c  */
#line 7169 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1435:

/* Line 1455 of yacc.c  */
#line 7173 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1436:

/* Line 1455 of yacc.c  */
#line 7177 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1437:

/* Line 1455 of yacc.c  */
#line 7181 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1438:

/* Line 1455 of yacc.c  */
#line 7185 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1439:

/* Line 1455 of yacc.c  */
#line 7189 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1440:

/* Line 1455 of yacc.c  */
#line 7193 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1441:

/* Line 1455 of yacc.c  */
#line 7197 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), NULL);
  ;}
    break;

  case 1442:

/* Line 1455 of yacc.c  */
#line 7201 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1443:

/* Line 1455 of yacc.c  */
#line 7205 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), NULL);
  ;}
    break;

  case 1444:

/* Line 1455 of yacc.c  */
#line 7211 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1445:

/* Line 1455 of yacc.c  */
#line 7212 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (4)]), NULL); ;}
    break;

  case 1446:

/* Line 1455 of yacc.c  */
#line 7213 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 1447:

/* Line 1455 of yacc.c  */
#line 7217 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1448:

/* Line 1455 of yacc.c  */
#line 7218 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1449:

/* Line 1455 of yacc.c  */
#line 7222 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1450:

/* Line 1455 of yacc.c  */
#line 7223 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1451:

/* Line 1455 of yacc.c  */
#line 7229 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_int0);
  ;}
    break;

  case 1452:

/* Line 1455 of yacc.c  */
#line 7236 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int1);
  ;}
    break;

  case 1453:

/* Line 1455 of yacc.c  */
#line 7243 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int2);
  ;}
    break;

  case 1454:

/* Line 1455 of yacc.c  */
#line 7253 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1455:

/* Line 1455 of yacc.c  */
#line 7260 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1456:

/* Line 1455 of yacc.c  */
#line 7270 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1457:

/* Line 1455 of yacc.c  */
#line 7277 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_ref ((yyvsp[(3) - (3)])));
  ;}
    break;

  case 1458:

/* Line 1455 of yacc.c  */
#line 7290 "parser.y"
    {
	non_const_word = 1;
  ;}
    break;

  case 1459:

/* Line 1455 of yacc.c  */
#line 7300 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1460:

/* Line 1455 of yacc.c  */
#line 7301 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1461:

/* Line 1455 of yacc.c  */
#line 7305 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1462:

/* Line 1455 of yacc.c  */
#line 7306 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1463:

/* Line 1455 of yacc.c  */
#line 7310 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1464:

/* Line 1455 of yacc.c  */
#line 7311 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1465:

/* Line 1455 of yacc.c  */
#line 7315 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1466:

/* Line 1455 of yacc.c  */
#line 7316 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1467:

/* Line 1455 of yacc.c  */
#line 7317 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 1468:

/* Line 1455 of yacc.c  */
#line 7321 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1469:

/* Line 1455 of yacc.c  */
#line 7322 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1470:

/* Line 1455 of yacc.c  */
#line 7326 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1471:

/* Line 1455 of yacc.c  */
#line 7327 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1472:

/* Line 1455 of yacc.c  */
#line 7331 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1473:

/* Line 1455 of yacc.c  */
#line 7332 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1474:

/* Line 1455 of yacc.c  */
#line 7336 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1475:

/* Line 1455 of yacc.c  */
#line 7337 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1487:

/* Line 1455 of yacc.c  */
#line 7350 "parser.y"
    { (yyval) = cb_int1; ;}
    break;



/* Line 1455 of yacc.c  */
#line 14629 "parser.c"
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
#line 7394 "parser.y"


