
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
#define YYLAST   5781

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  457
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  706
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1579
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2315

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
    3763,  3767,  3769,  3771,  3774,  3776,  3777,  3779,  3781,  3783,
    3785,  3787,  3790,  3792,  3796,  3798,  3801,  3803,  3807,  3811,
    3815,  3820,  3824,  3826,  3828,  3830,  3832,  3836,  3840,  3844,
    3846,  3848,  3850,  3852,  3854,  3856,  3858,  3860,  3862,  3864,
    3866,  3868,  3870,  3872,  3874,  3876,  3878,  3880,  3882,  3884,
    3886,  3889,  3892,  3896,  3898,  3902,  3906,  3911,  3917,  3919,
    3921,  3924,  3926,  3930,  3932,  3934,  3936,  3938,  3940,  3942,
    3944,  3947,  3950,  3956,  3962,  3968,  3974,  3980,  3986,  3992,
    3997,  4003,  4006,  4007,  4012,  4018,  4019,  4023,  4024,  4026,
    4028,  4032,  4036,  4038,  4042,  4044,  4048,  4049,  4050,  4052,
    4053,  4055,  4056,  4058,  4059,  4061,  4063,  4064,  4066,  4067,
    4069,  4070,  4072,  4073,  4076,  4078,  4080,  4083,  4086,  4089,
    4091,  4094,  4096,  4097,  4099,  4100,  4102,  4103,  4105,  4106,
    4108,  4109,  4111,  4112,  4114,  4115,  4117,  4118,  4120,  4121,
    4123,  4124,  4126,  4127,  4129,  4130,  4132,  4133,  4135,  4136,
    4138,  4139,  4141,  4142,  4144,  4145,  4147,  4148,  4150,  4152,
    4153,  4155,  4156,  4158,  4160,  4161,  4163,  4164,  4166,  4167,
    4169,  4170,  4172,  4173,  4175,  4176,  4178,  4181,  4182,  4184,
    4185,  4187,  4188,  4190,  4191,  4193,  4194,  4196,  4197,  4199,
    4200,  4202,  4205,  4206,  4208,  4209,  4211,  4212,  4214,  4215,
    4217,  4218,  4220,  4221,  4223,  4224,  4226,  4227,  4229,  4230
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
      -1,    -1,  1137,   481,  1148,    -1,    72,    -1,    72,   482,
      -1,   482,    -1,   401,    -1,   317,    -1,    -1,   147,   117,
     449,   484,   538,    -1,    -1,    82,   351,   449,   485,    -1,
      -1,   485,   486,    -1,   487,    -1,   491,    -1,   504,    -1,
     499,    -1,   372,   449,   488,    -1,    -1,   490,   449,    -1,
     490,   489,   449,    -1,   489,   449,    -1,  1162,   104,   245,
      -1,   436,    -1,   270,   449,   492,    -1,    -1,   490,   449,
      -1,   490,   493,   449,    -1,   493,   449,    -1,   494,    -1,
     493,   494,    -1,   495,    -1,   497,    -1,   498,    -1,   241,
     367,  1137,  1097,   496,    -1,    56,    -1,   437,    -1,  1148,
    1120,  1137,  1076,    -1,   353,  1137,  1097,    -1,   332,   449,
     500,    -1,    -1,   501,   449,    -1,   502,    -1,   501,   502,
      -1,   178,   503,   207,    -1,   178,     9,   207,    -1,   232,
      -1,   503,   232,    -1,   374,   449,   505,    -1,    -1,   506,
      -1,   506,   449,    -1,   507,    -1,   506,   507,    -1,   508,
      -1,   515,    -1,   524,    -1,   531,    -1,   528,    -1,   532,
      -1,   533,    -1,   534,    -1,   535,    -1,   536,    -1,   537,
      -1,   436,  1137,    94,    -1,    -1,   436,  1137,  1079,   509,
     511,    -1,    -1,   436,  1137,   510,   512,    -1,    25,  1137,
    1079,    -1,    26,  1137,  1079,    -1,   148,  1137,  1079,    -1,
     149,  1137,  1079,    -1,    -1,   511,   513,    -1,   513,    -1,
     512,   513,    -1,   514,  1155,  1137,  1079,    -1,   275,    -1,
     273,    -1,    -1,    11,  1079,   516,  1137,   517,    -1,   251,
      -1,   376,    -1,   377,    -1,   121,    -1,   518,    -1,   519,
      -1,   518,   519,    -1,   522,    -1,   522,   395,   522,    -1,
      -1,   522,    17,   520,   521,    -1,   523,    -1,   521,    17,
     523,    -1,   232,    -1,   373,    -1,   442,    -1,   310,    -1,
     191,    -1,   239,    -1,   232,    -1,   373,    -1,   442,    -1,
     310,    -1,   191,    -1,   239,    -1,   387,  1130,   525,    -1,
     526,  1138,   527,    -1,  1079,    -1,   526,  1079,    -1,  1097,
      -1,   527,  1097,    -1,    57,  1079,  1137,   529,    -1,   530,
      -1,   529,   530,    -1,  1100,    -1,  1100,   395,  1100,    -1,
     233,  1079,  1137,  1076,    -1,    95,  1152,  1137,   232,    -1,
     105,  1137,    67,    -1,    97,  1137,  1076,    -1,    94,   379,
    1137,  1076,    -1,   347,  1137,  1076,    -1,   159,  1137,  1076,
      -1,    -1,   204,   351,   449,   541,   574,    -1,    -1,   166,
     449,   539,   542,    -1,    -1,   212,   449,   540,   575,    -1,
      -1,   166,   449,   542,    -1,    -1,   542,   543,    -1,    -1,
     354,  1114,  1079,   544,   545,   449,    -1,    -1,   545,   546,
      -1,   547,    -1,   551,    -1,   553,    -1,   558,    -1,   559,
      -1,   561,    -1,   565,    -1,   567,    -1,   568,    -1,   569,
      -1,   570,    -1,   571,    -1,   572,    -1,     1,    -1,    29,
    1160,   549,   548,   550,    -1,    29,  1160,   549,   114,    -1,
      29,  1160,   549,   300,    -1,    -1,   114,    -1,   300,    -1,
      -1,   164,    -1,   120,    -1,   232,    -1,   115,    -1,  1094,
      -1,     4,  1142,  1137,   552,    -1,   359,    -1,   120,    -1,
     311,    -1,    19,   314,  1139,  1137,  1076,  1110,    -1,    19,
     314,  1139,  1137,  1076,   557,   554,  1110,    -1,    -1,   555,
     556,    -1,   554,   556,    -1,  1076,    -1,    -1,   371,  1137,
      -1,   450,    -1,  1120,  1137,   436,    -1,   560,   379,  1137,
    1076,  1077,    -1,    -1,   400,    -1,   369,    -1,   236,  1142,
    1137,   562,    -1,   240,   563,    -1,    32,   563,    -1,   161,
      -1,    -1,   435,   236,   275,   564,    -1,   435,   236,   275,
     247,   564,    -1,   435,   342,    -1,   314,    -1,   316,    -1,
     281,  1137,   566,    -1,   566,    -1,   198,    -1,   314,  1127,
     359,    -1,   359,    -1,   321,    -1,   229,   359,    -1,   287,
    1129,  1137,  1078,    -1,   314,   110,  1137,   376,    -1,   314,
    1139,  1137,  1076,    -1,   314,  1139,  1137,  1076,   557,   554,
      -1,   321,  1139,  1137,  1076,    -1,   334,  1097,  1124,    -1,
     361,  1162,   573,    -1,     9,  1147,    -1,   256,  1147,    -1,
     313,   276,    -1,    -1,   212,   449,   575,    -1,    -1,   576,
     449,    -1,   576,    -1,   577,    -1,   576,   577,    -1,   578,
      -1,   580,    -1,   584,    -1,   345,   579,  1124,  1134,  1067,
      -1,    -1,   314,    -1,   369,    -1,   370,    -1,   247,  1133,
    1156,  1131,   581,    -1,   582,    -1,   581,   582,    -1,  1068,
     583,    -1,    -1,   296,  1097,    -1,    22,    71,  1145,  1075,
      -1,    -1,    99,   117,   449,   586,   617,   670,   672,   674,
     715,    -1,    -1,    -1,   400,   351,   449,   587,   589,    -1,
      -1,   592,   588,   591,    -1,    -1,   589,   590,    -1,   592,
     593,   619,    -1,   593,   619,    -1,   591,   590,    -1,   165,
      -1,   349,    -1,    -1,  1068,   594,   595,   449,    -1,    -1,
     595,   596,    -1,  1137,   164,    -1,  1137,   184,    -1,   597,
      -1,   599,    -1,   603,    -1,   605,    -1,   607,    -1,   608,
      -1,   614,    -1,   615,    -1,   616,    -1,     1,    -1,    47,
    1131,  1097,   602,   598,    -1,    -1,   316,    -1,    56,    -1,
     314,  1131,  1097,  1130,    -1,   314,  1131,  1097,   398,  1097,
    1130,    -1,   314,  1137,   430,  1136,  1154,   601,   602,  1130,
     600,    -1,    -1,   111,  1145,  1076,    -1,    -1,  1135,  1097,
      -1,    -1,   398,  1097,    -1,   215,  1118,   604,    -1,   375,
      -1,   274,    -1,   429,   272,   436,  1137,   606,    -1,   429,
     272,   167,  1137,   606,    -1,   232,    -1,  1094,    -1,    99,
    1118,  1075,    -1,   227,  1137,  1078,  1141,   609,    -1,    -1,
     609,   610,    -1,   611,    -1,   612,    -1,   613,    -1,  1162,
     171,  1126,  1078,  1141,    -1,  1126,   404,  1078,  1141,    -1,
    1126,    48,  1078,    -1,   315,  1142,  1137,   436,    -1,    61,
    1137,   436,    -1,   327,  1137,   714,    -1,   329,  1123,   714,
      -1,    -1,    -1,   438,   351,   449,   618,   619,    -1,    -1,
     620,    -1,    -1,   621,   622,    -1,  1108,   623,    -1,   622,
    1108,   623,    -1,   622,   449,    -1,   633,    -1,    -1,   626,
     629,   624,   634,   628,    -1,    -1,   627,   629,   625,   663,
      -1,   223,    -1,   224,    -1,    -1,   232,    -1,    -1,   168,
      -1,   436,    -1,   436,    -1,    -1,  1137,   184,    -1,  1098,
      -1,   221,  1144,  1093,    -1,    50,  1144,  1093,    -1,   626,
     630,    83,   631,  1125,   632,    -1,    -1,   634,   635,    -1,
     636,    -1,   637,    -1,   639,    -1,   640,    -1,   641,    -1,
     643,    -1,   645,    -1,   657,    -1,   658,    -1,   660,    -1,
     661,    -1,   662,    -1,   668,    -1,   669,    -1,     1,    -1,
     318,  1093,    -1,  1137,   164,   638,    -1,    -1,    27,   232,
      -1,  1137,   184,    -1,   293,    -1,   642,    -1,   426,  1137,
     642,    -1,    37,    -1,    73,    -1,    75,    -1,    76,    -1,
      77,    -1,    78,    -1,    79,    -1,    80,    -1,   115,    -1,
     197,    -1,   286,    -1,   295,    -1,   308,    -1,   366,    -1,
     364,    -1,   365,    -1,   415,    -1,   413,    -1,   414,    -1,
      39,   363,    -1,    39,   412,    -1,    39,    -1,    42,   363,
      -1,    42,   412,    -1,    42,    -1,    41,   363,    -1,    41,
     412,    -1,    41,    -1,    40,   363,    -1,    40,   412,    -1,
      40,    -1,    38,   363,    -1,    38,   412,    -1,    38,    -1,
     249,    -1,  1153,   219,  1116,    -1,  1153,   405,  1116,    -1,
      -1,   649,   653,    -1,   654,   648,    -1,   271,  1097,   646,
    1159,   647,   644,    -1,    -1,   398,  1097,    -1,    -1,   111,
    1145,  1076,    -1,    -1,   649,    -1,   651,    -1,   652,  1139,
    1137,  1075,    -1,   650,    -1,   651,   650,    -1,    28,    -1,
     112,    -1,    -1,   654,    -1,   198,  1128,   655,    -1,   656,
      -1,   655,   656,    -1,   436,    -1,   213,  1150,    -1,   388,
     659,    -1,    -1,   220,    -1,   341,    -1,    43,  1161,   442,
      -1,    34,    -1,   429,  1137,  1098,    -1,    -1,   429,  1138,
     665,   664,  1161,  1151,  1160,   667,    -1,   666,    -1,   665,
     666,    -1,  1098,    -1,  1098,   395,  1098,    -1,    -1,   399,
    1137,  1098,    -1,   325,  1094,    -1,   325,  1094,   395,  1094,
      -1,    21,   221,    -1,    -1,    -1,   235,   351,   449,   671,
     619,    -1,    -1,    -1,   231,   351,   449,   673,   619,    -1,
      -1,    -1,   327,   351,   449,   675,   676,    -1,    -1,   677,
      -1,   678,    -1,   677,   678,    -1,   312,   714,   679,   449,
     693,    -1,    -1,   679,   680,    -1,  1137,   184,    -1,    60,
    1137,  1089,    -1,   681,    -1,   685,    -1,    87,   682,    -1,
      88,   682,    -1,   683,   684,    -1,    -1,   169,    -1,  1092,
      -1,   684,  1092,    -1,   288,  1138,   691,   686,   687,   688,
     689,   690,    -1,    -1,   189,  1137,  1097,    -1,    -1,   170,
     113,  1137,  1097,    -1,    -1,   216,    90,  1137,  1097,    -1,
      -1,   217,  1137,  1097,    -1,    -1,   171,  1137,  1097,    -1,
    1097,    -1,  1097,   692,  1097,    66,    -1,  1097,   692,    -1,
     229,    -1,   230,    -1,    -1,   693,   694,    -1,   626,   629,
     695,   449,    -1,    -1,   695,   696,    -1,   697,    -1,   699,
      -1,   706,    -1,   640,    -1,   641,    -1,   643,    -1,   657,
      -1,   700,    -1,   660,    -1,   711,    -1,   701,    -1,   662,
      -1,   704,    -1,   712,    -1,   645,    -1,   705,    -1,   408,
    1137,   698,    -1,   331,    -1,   290,    -1,    90,    -1,   113,
      -1,    89,    -1,   289,    -1,   330,    -1,   254,   188,  1137,
    1097,    -1,    65,  1143,  1137,  1097,    -1,    65,   266,    -1,
      66,    -1,   702,    -1,   701,   702,    -1,   385,  1144,   703,
      -1,  1076,    -1,   298,   432,  1048,    -1,   430,  1092,   176,
    1083,    49,  1083,    -1,   707,   708,    -1,   229,   710,  1138,
      -1,   230,  1123,    -1,   709,    -1,   708,   709,    -1,   294,
    1097,    -1,  1097,    -1,   254,   288,    -1,    -1,   265,    -1,
     266,    -1,   371,  1137,  1092,  1115,    -1,   188,   713,    -1,
      -1,   199,    -1,   436,    -1,    -1,    -1,    -1,   346,   351,
     449,   716,   717,   718,    -1,    -1,   719,    -1,   720,    -1,
     719,   720,    -1,   633,    -1,    -1,   626,   629,   721,   722,
     449,    -1,    -1,   722,   723,    -1,    44,    -1,    45,    -1,
      36,    -1,    46,    -1,   155,   150,    -1,   155,   152,    -1,
     190,    -1,   238,    -1,   338,    -1,   409,    -1,   285,    -1,
      31,    -1,   352,    -1,   333,    -1,   177,    -1,   309,    -1,
     229,  1143,  1137,   724,  1091,    -1,    65,  1143,  1137,   725,
    1091,    -1,   173,  1137,  1091,    -1,    33,  1137,  1091,    -1,
     641,    -1,   660,    -1,   657,    -1,   643,    -1,   662,    -1,
     640,    -1,   726,    -1,   428,  1092,    -1,   176,  1090,    -1,
     398,  1092,    -1,    -1,   294,    -1,   443,    -1,   243,    -1,
     444,    -1,    -1,   294,    -1,   443,    -1,   243,    -1,   444,
      -1,   271,  1097,  1159,    -1,    -1,    -1,    -1,   302,   117,
     730,   738,   449,   728,   739,   729,   741,    -1,    -1,    -1,
     428,   731,   733,    -1,    -1,    54,   732,   733,    -1,   734,
      -1,   733,   734,    -1,   735,   736,   737,   436,    -1,    -1,
    1128,   320,    -1,  1128,   429,    -1,    -1,   367,  1137,    31,
      -1,   367,  1137,   107,    -1,   412,   367,  1137,  1097,    -1,
     367,  1137,  1097,    -1,    -1,   278,    -1,    -1,   336,   436,
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
      -1,    -1,     3,   754,   755,   762,    -1,  1092,   756,   759,
    1015,    -1,  1092,   176,   157,   214,    -1,  1092,   176,   230,
      -1,  1092,   176,    66,    -1,  1092,   176,   100,    -1,  1092,
     176,   100,   441,    -1,  1092,   176,   101,    -1,  1092,   176,
     101,   440,    -1,  1092,   176,   102,    -1,  1092,   176,   396,
      -1,  1092,   176,    68,    -1,  1092,   176,   149,  1015,    -1,
    1092,   176,   147,  1087,  1015,    -1,  1092,   176,    25,    -1,
    1092,   176,    26,  1015,    -1,  1092,   176,  1070,    -1,  1092,
     176,   436,    -1,    -1,  1126,   757,   758,    -1,  1126,   758,
     757,    -1,  1126,   757,    -1,  1126,   758,    -1,    30,  1087,
      -1,   229,  1143,  1089,    -1,    65,  1143,  1089,    -1,   296,
    1143,  1089,    -1,    -1,   435,   760,    -1,   761,    -1,   760,
     761,    -1,    36,    -1,    46,    -1,   190,    -1,   238,    -1,
     338,    -1,   409,    -1,   285,    -1,   173,  1137,  1091,    -1,
      33,  1137,  1091,    -1,   348,   418,  1047,    -1,   348,   118,
    1047,    -1,    31,    -1,   177,    -1,   333,    -1,   352,    -1,
     419,    -1,   309,    -1,    -1,   124,    -1,    -1,     5,   764,
     765,   767,    -1,  1082,   398,  1063,  1021,    -1,  1082,   766,
     183,  1063,  1021,    -1,    92,  1092,   398,  1092,  1115,  1021,
      -1,    -1,   398,  1083,    -1,    -1,   125,    -1,    -1,    10,
     769,   770,    -1,   436,  1111,   771,    -1,  1049,    56,  1111,
     336,  1081,    -1,    -1,   336,  1081,    -1,    18,   773,    -1,
      -1,   773,  1072,   398,   774,  1072,    -1,    -1,   304,   398,
      -1,    -1,    51,   776,  1090,   777,   782,   783,   785,   787,
      -1,    -1,    -1,   428,   778,   779,    -1,   780,    -1,   779,
     780,    -1,   781,   274,    -1,   781,   736,  1083,    -1,    -1,
    1128,   320,    -1,  1128,    85,    -1,  1128,   429,    -1,    -1,
     336,  1092,    -1,   183,  1092,    -1,    -1,    -1,  1002,   784,
     748,    -1,    -1,    -1,  1003,   786,   748,    -1,    -1,   126,
      -1,    -1,    52,   789,   790,    -1,    -1,   790,  1089,    -1,
      -1,    59,   792,   793,    -1,    -1,   793,  1068,   794,    -1,
      -1,   795,    -1,   795,  1134,   324,    -1,  1162,   256,   339,
      -1,  1162,   236,    -1,   319,    -1,   410,    -1,    -1,    74,
     797,   798,   799,    -1,  1063,   800,  1049,  1021,    -1,    -1,
     127,    -1,   450,    -1,   153,    -1,    70,    -1,    86,    -1,
      -1,   108,   804,  1068,  1149,  1041,   805,    -1,    -1,   128,
      -1,    -1,   108,   807,   400,  1067,    -1,    -1,   115,   809,
     810,   814,    -1,  1089,   423,  1016,    -1,  1089,   424,  1016,
      -1,  1089,   421,  1016,    -1,  1089,   422,  1016,    -1,  1082,
     756,   811,  1016,    -1,  1082,   756,   420,  1070,   811,  1016,
      -1,  1082,   756,   420,   436,   811,  1016,    -1,  1082,   756,
     420,   300,   811,  1016,    -1,  1082,   756,   420,    94,   811,
    1016,    -1,    -1,  1162,   264,    -1,   435,   812,    -1,   813,
      -1,   812,   813,    -1,    36,    -1,    46,    -1,   155,   150,
      -1,   155,   152,    -1,   190,    -1,   238,    -1,   338,    -1,
     409,    -1,   285,    -1,   173,  1137,  1091,    -1,    33,  1137,
    1091,    -1,   348,   418,  1047,    -1,   348,   118,  1047,    -1,
      44,    -1,    45,    -1,    -1,   129,    -1,    -1,   116,   816,
     817,   818,    -1,  1083,   206,  1063,  1021,    -1,  1083,   206,
    1083,   183,  1063,  1021,    -1,  1083,    49,  1083,   183,  1063,
    1021,    -1,  1083,   206,  1083,   183,  1064,   323,  1064,  1021,
      -1,  1083,    49,  1083,   183,  1064,   323,  1064,  1021,    -1,
      -1,   130,    -1,    -1,   146,   820,   232,   777,    -1,    -1,
     158,   822,   823,   825,   835,    -1,   824,    -1,   823,  1122,
     824,    -1,  1049,    -1,   403,    -1,   399,    -1,   826,   829,
      -1,   827,    -1,   826,   827,    -1,    -1,   831,   828,   748,
      -1,    -1,    -1,   434,   830,   748,    -1,   432,   832,    -1,
     831,   432,   832,    -1,   833,    -1,   832,  1122,   833,    -1,
    1050,   834,    -1,    21,    -1,   403,    -1,   399,    -1,    -1,
     395,  1049,    -1,    -1,   131,    -1,    -1,   162,   837,   838,
      -1,    -1,   305,    -1,   292,    -1,   292,    98,    -1,   351,
      -1,   291,    -1,    -1,   175,   840,  1080,    -1,    -1,   182,
     842,  1092,    -1,    -1,   185,  1160,   844,  1071,   845,    -1,
      -1,   111,  1145,  1092,    -1,    -1,   186,   847,    -1,    -1,
      -1,   193,   849,  1048,  1158,   850,   748,   851,   853,    -1,
     193,     1,   133,    -1,    -1,    -1,   122,   852,   748,    -1,
      -1,   133,    -1,    -1,   200,   855,  1080,   856,   857,   858,
     862,    -1,    -1,  1162,   168,    -1,    -1,     9,  1160,   429,
      -1,   861,  1160,   429,    -1,    -1,   326,   859,    -1,   860,
      -1,   859,   860,    -1,   861,  1132,    49,  1083,    -1,    12,
      -1,    15,    -1,   267,    -1,    16,    -1,   268,    -1,   249,
      -1,   250,    -1,    -1,   107,    -1,    -1,   202,   864,   684,
      -1,    -1,   205,   866,   867,   868,    -1,  1092,    -1,  1098,
      -1,  1101,    -1,   869,    -1,   868,   869,    -1,   870,    -1,
     874,    -1,   879,    -1,    -1,   389,   871,   872,    -1,   873,
      -1,   872,   873,    -1,  1087,   172,    -1,    56,   880,    -1,
       9,    -1,   219,    -1,   405,    -1,  1087,   880,    -1,   326,
     875,    -1,   876,    -1,   875,   876,    -1,    56,    49,  1087,
     880,    -1,   877,   878,    -1,    -1,     9,    -1,   219,    -1,
     170,    -1,   405,    -1,  1087,    49,  1088,   880,    -1,    91,
    1087,   398,  1088,   880,    -1,    -1,   880,  1012,   881,  1083,
      -1,    -1,   401,    -1,    -1,   242,   883,   948,    -1,    -1,
     246,   885,   886,    -1,  1083,   398,  1080,    -1,    92,  1083,
     398,  1080,    -1,    -1,   248,   888,   889,   890,    -1,  1083,
      49,  1063,  1021,    -1,  1083,    49,  1083,   183,  1063,  1021,
      -1,    -1,   134,    -1,    -1,   277,   892,   893,    -1,    -1,
     893,   894,   895,  1067,   896,    -1,   203,    -1,   283,    -1,
     211,    -1,   163,    -1,    -1,   361,  1162,   573,    -1,    -1,
    1162,   256,   339,    -1,  1162,   236,    -1,    -1,   292,   898,
     899,    -1,   902,   903,    -1,    -1,   903,   900,   748,   901,
      -1,   903,   135,    -1,    -1,   135,    -1,  1072,    -1,  1072,
     395,  1072,    -1,    -1,   174,    -1,  1090,   397,    -1,   904,
     417,  1048,    -1,   904,   430,   905,    -1,    -1,  1162,   392,
    1012,    -1,   906,    -1,   905,     8,   906,    -1,  1092,   176,
    1083,    49,  1083,   417,  1048,    -1,    -1,   313,   908,  1068,
    1112,  1149,   909,   910,   911,   912,   913,    -1,    -1,   206,
    1092,    -1,    -1,   195,   236,    -1,  1162,   236,    -1,  1162,
     256,   236,    -1,  1162,   194,   236,    -1,  1162,   431,    -1,
      -1,   214,  1137,   684,    -1,    -1,  1031,    -1,  1042,    -1,
      -1,   137,    -1,    -1,   322,   915,  1065,  1010,    -1,    -1,
     335,   917,  1068,  1149,   909,  1031,   918,    -1,    -1,   138,
      -1,    -1,   340,   920,  1065,  1010,   921,  1041,   922,    -1,
      -1,  1162,   236,    -1,  1162,   256,   236,    -1,    -1,   139,
      -1,   342,    -1,    -1,   350,   925,   926,   934,    -1,  1066,
     928,   929,   931,    -1,    -1,     9,  1066,   929,   432,  1049,
     927,   748,    -1,    -1,   430,  1092,    -1,    -1,    -1,  1126,
     123,   930,   748,    -1,   932,    -1,   932,   931,    -1,    -1,
     432,  1048,   933,   748,    -1,    -1,   140,    -1,    -1,   360,
     936,   937,    -1,   938,    -1,   939,    -1,   940,    -1,   942,
      -1,   944,    -1,   147,  1087,   398,  1087,    -1,  1080,   398,
     146,  1086,    -1,  1080,   398,  1083,    -1,  1080,   941,    49,
    1083,    -1,   418,    -1,   118,    -1,   943,    -1,   942,   943,
      -1,  1069,   398,   514,    -1,   945,    -1,   944,   945,    -1,
    1080,   398,   403,    -1,  1080,   398,   399,    -1,    -1,   369,
     947,   948,    -1,    -1,  1094,   950,   952,   953,   949,   954,
     955,    -1,    -1,   950,  1145,   652,  1139,   951,    -1,    -1,
     951,  1094,    -1,    -1,  1119,  1146,    -1,    -1,  1120,  1137,
    1076,    -1,    -1,   428,  1067,    -1,   203,   302,  1137,   902,
      -1,    -1,   183,  1067,    -1,   283,   302,  1137,   902,    -1,
      -1,    -1,   378,   957,  1068,   958,   959,  1041,   961,    -1,
      -1,   214,  1137,   960,   684,    -1,  1113,  1054,    -1,  1113,
    1055,    -1,  1113,  1056,    -1,  1113,  1057,    -1,  1113,  1058,
      -1,    -1,   141,    -1,    -1,   380,   344,   963,   964,    -1,
     380,   232,    -1,    -1,   336,  1083,    -1,   183,  1083,    -1,
      -1,   381,   966,   967,   206,  1092,   969,  1026,   970,    -1,
     968,    -1,   967,   968,    -1,  1083,    -1,   109,  1128,   367,
      -1,   109,  1128,  1083,    -1,    -1,  1162,   295,  1092,    -1,
      -1,   142,    -1,    -1,   384,   972,   973,   974,    -1,  1082,
     176,  1063,  1021,    -1,  1082,   176,  1083,   183,  1063,  1021,
      -1,    92,  1092,   176,  1092,  1115,  1021,    -1,    -1,   143,
      -1,   386,   976,    -1,    -1,   301,    -1,    -1,   391,   978,
     684,    -1,    -1,   406,   980,  1092,   176,  1087,   398,  1088,
      -1,    -1,   411,   982,  1068,   983,    -1,    -1,   314,    -1,
     316,    -1,    -1,   416,   985,  1092,   986,   989,   969,   993,
    1026,   994,    -1,    -1,   109,  1128,   987,    -1,   988,    -1,
     987,   279,   988,    -1,  1109,  1087,    -1,   206,   990,    -1,
     989,   990,    -1,  1092,   991,   992,    -1,    -1,   110,  1136,
    1092,    -1,    -1,    93,  1136,  1092,    -1,    -1,   389,  1136,
    1092,    -1,    -1,   144,    -1,   996,    -1,  1005,    -1,  1007,
      -1,   427,   997,   999,  1000,  1001,  1004,  1145,   998,    -1,
      -1,   184,    -1,  1067,    -1,   203,    -1,   283,    -1,   211,
      -1,   163,    -1,    -1,     8,    -1,    -1,   375,    -1,   160,
      -1,   156,    -1,   160,    -1,   284,    -1,   260,    -1,   262,
      -1,    -1,   302,    -1,   427,  1134,   104,  1145,  1006,    -1,
    1072,    -1,     9,   303,    -1,   427,   997,    35,   328,  1092,
      -1,    -1,   439,  1009,  1065,  1010,   921,  1011,  1013,  1014,
      -1,    -1,   176,  1089,    -1,    -1,  1012,  1121,  1091,  1140,
      -1,  1012,  1121,  1070,    -1,  1012,  1121,   288,    -1,    35,
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
    1046,   748,    -1,    -1,  1128,  1091,  1140,    -1,  1049,    -1,
    1050,    -1,    -1,  1051,  1052,    -1,  1053,  1083,    -1,  1052,
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
      20,    -1,  1052,   279,    -1,   450,    -1,   153,  1160,    -1,
     154,    -1,   453,    -1,   187,  1157,    -1,   454,    -1,   222,
    1157,    -1,   181,    -1,   187,  1157,   279,   153,  1160,    -1,
     187,  1157,   153,  1160,    -1,   218,    -1,   222,  1157,   279,
     153,  1160,    -1,   222,  1157,   153,  1160,    -1,  1061,    -1,
    1059,  1060,  1061,    -1,    -1,    69,    -1,   355,    -1,  1084,
      -1,  1061,   443,  1061,    -1,  1061,   444,  1061,    -1,  1061,
     445,  1061,    -1,  1061,   446,  1061,    -1,   443,  1061,    -1,
     444,  1061,    -1,  1061,   448,  1061,    -1,   452,  1061,   451,
      -1,   228,    -1,   228,  1117,   436,    -1,  1064,    -1,  1063,
    1064,    -1,  1083,  1115,    -1,  1094,    -1,  1094,    -1,  1068,
      -1,  1067,  1068,    -1,   436,    -1,  1070,    -1,  1069,  1070,
      -1,   244,    -1,    -1,  1071,  1072,    -1,  1073,    -1,  1094,
      -1,  1074,    -1,  1074,  1117,  1074,    -1,   232,    -1,  1076,
      -1,  1075,  1076,    -1,  1094,    -1,    -1,  1076,    -1,  1076,
      -1,   232,    -1,   436,    -1,  1081,    -1,  1080,  1081,    -1,
    1092,    -1,     6,  1144,  1093,    -1,  1083,    -1,  1082,  1083,
      -1,  1092,    -1,   221,  1144,  1093,    -1,   221,  1144,  1099,
      -1,   221,  1144,  1101,    -1,     6,  1144,  1085,  1086,    -1,
       6,  1144,  1093,    -1,  1098,    -1,  1101,    -1,  1062,    -1,
    1092,    -1,   221,  1144,  1093,    -1,   221,  1144,  1099,    -1,
     221,  1144,  1101,    -1,  1099,    -1,  1101,    -1,  1062,    -1,
     305,    -1,   146,    -1,  1093,    -1,   232,    -1,  1092,    -1,
    1099,    -1,  1092,    -1,  1098,    -1,  1092,    -1,   232,    -1,
    1092,    -1,   232,    -1,  1101,    -1,  1092,    -1,  1097,    -1,
     442,    -1,  1093,    -1,  1094,    -1,  1094,  1095,    -1,  1094,
    1096,    -1,  1094,  1095,  1096,    -1,   436,    -1,   436,  1117,
    1094,    -1,   452,  1059,   451,    -1,   452,  1061,   455,   451,
      -1,   452,  1061,   455,  1061,   451,    -1,   232,    -1,  1099,
      -1,     9,  1100,    -1,  1100,    -1,  1099,   456,  1100,    -1,
     232,    -1,   373,    -1,   442,    -1,   310,    -1,   191,    -1,
     239,    -1,   402,    -1,    96,  1102,    -1,   433,  1102,    -1,
     425,   452,  1061,   451,  1102,    -1,   237,   452,  1061,   451,
    1102,    -1,   337,   452,  1061,   451,  1102,    -1,    81,   452,
    1059,   451,  1102,    -1,   382,   452,  1059,   451,  1102,    -1,
     383,   452,  1059,   451,  1102,    -1,   407,   452,  1105,   451,
    1102,    -1,   269,   452,  1106,   451,    -1,   234,   452,  1107,
     451,  1102,    -1,   180,  1103,    -1,    -1,   452,  1061,   455,
     451,    -1,   452,  1061,   455,  1061,   451,    -1,    -1,   452,
    1104,   451,    -1,    -1,  1059,    -1,  1061,    -1,  1061,  1060,
     219,    -1,  1061,  1060,   405,    -1,  1061,    -1,  1061,  1060,
    1061,    -1,  1061,    -1,  1061,  1060,  1076,    -1,    -1,    -1,
       9,    -1,    -1,  1119,    -1,    -1,   201,    -1,    -1,   254,
      -1,   299,    -1,    -1,   257,    -1,    -1,   278,    -1,    -1,
     343,    -1,    -1,   357,  1129,    -1,   196,    -1,   272,    -1,
     314,  1137,    -1,   316,  1123,    -1,   435,   119,    -1,   119,
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
    6915,  6919,  6930,  6931,  6935,  6943,  6944,  6948,  6949,  6955,
    6975,  6976,  6980,  6981,  6985,  6986,  6990,  6991,  6992,  6993,
    6994,  6995,  6996,  6997,  6998,  7002,  7003,  7004,  7005,  7006,
    7007,  7008,  7012,  7013,  7017,  7018,  7022,  7023,  7027,  7028,
    7039,  7040,  7044,  7045,  7046,  7050,  7051,  7052,  7060,  7064,
    7065,  7066,  7067,  7071,  7072,  7076,  7086,  7104,  7131,  7143,
    7144,  7154,  7155,  7159,  7160,  7161,  7162,  7163,  7164,  7165,
    7173,  7177,  7181,  7185,  7189,  7193,  7197,  7201,  7205,  7209,
    7213,  7217,  7224,  7225,  7226,  7230,  7231,  7235,  7236,  7241,
    7248,  7255,  7265,  7272,  7282,  7289,  7303,  7313,  7314,  7318,
    7319,  7323,  7324,  7328,  7329,  7330,  7334,  7335,  7339,  7340,
    7344,  7345,  7349,  7350,  7357,  7357,  7358,  7358,  7359,  7359,
    7360,  7360,  7362,  7362,  7363,  7363,  7364,  7364,  7365,  7365,
    7366,  7366,  7367,  7367,  7368,  7368,  7369,  7369,  7370,  7370,
    7371,  7371,  7372,  7372,  7373,  7373,  7374,  7374,  7375,  7375,
    7376,  7376,  7377,  7377,  7378,  7378,  7379,  7379,  7379,  7380,
    7380,  7381,  7381,  7381,  7382,  7382,  7383,  7383,  7384,  7384,
    7385,  7385,  7386,  7386,  7387,  7387,  7387,  7388,  7388,  7389,
    7389,  7390,  7390,  7391,  7391,  7392,  7392,  7393,  7393,  7394,
    7394,  7394,  7395,  7395,  7396,  7396,  7397,  7397,  7398,  7398,
    7399,  7399,  7400,  7400,  7401,  7401,  7403,  7403,  7404,  7404
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
    1080,  1080,  1081,  1081,  1082,  1082,  1083,  1083,  1083,  1083,
    1083,  1083,  1083,  1083,  1083,  1084,  1084,  1084,  1084,  1084,
    1084,  1084,  1085,  1085,  1086,  1086,  1087,  1087,  1088,  1088,
    1089,  1089,  1090,  1090,  1090,  1091,  1091,  1091,  1092,  1093,
    1093,  1093,  1093,  1094,  1094,  1095,  1096,  1096,  1097,  1098,
    1098,  1099,  1099,  1100,  1100,  1100,  1100,  1100,  1100,  1100,
    1101,  1101,  1101,  1101,  1101,  1101,  1101,  1101,  1101,  1101,
    1101,  1101,  1102,  1102,  1102,  1103,  1103,  1104,  1104,  1105,
    1105,  1105,  1106,  1106,  1107,  1107,  1108,  1109,  1109,  1110,
    1110,  1111,  1111,  1112,  1112,  1112,  1113,  1113,  1114,  1114,
    1115,  1115,  1116,  1116,  1117,  1117,  1118,  1118,  1119,  1119,
    1120,  1120,  1121,  1121,  1122,  1122,  1123,  1123,  1124,  1124,
    1125,  1125,  1126,  1126,  1127,  1127,  1128,  1128,  1129,  1129,
    1130,  1130,  1131,  1131,  1132,  1132,  1133,  1133,  1134,  1134,
    1135,  1135,  1136,  1136,  1137,  1137,  1138,  1138,  1138,  1139,
    1139,  1140,  1140,  1140,  1141,  1141,  1142,  1142,  1143,  1143,
    1144,  1144,  1145,  1145,  1146,  1146,  1146,  1147,  1147,  1148,
    1148,  1149,  1149,  1150,  1150,  1151,  1151,  1152,  1152,  1153,
    1153,  1153,  1154,  1154,  1155,  1155,  1156,  1156,  1157,  1157,
    1158,  1158,  1159,  1159,  1160,  1160,  1161,  1161,  1162,  1162
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
       2,     0,     0,     1,     0,     0,     0,     4,     6,     7,
      38,    38,     0,     0,     3,     5,     0,     8,    14,    28,
      27,    29,    29,     0,   264,   264,     0,     0,    24,    40,
       0,     9,    15,    30,    26,  1524,     0,   157,     0,   612,
     612,  1525,     0,     0,     0,     0,     0,     0,    39,   266,
       0,    17,     0,    25,    33,    37,    36,  1549,    35,    42,
     159,     0,   161,   276,   277,     0,   328,   269,   616,    18,
      20,    38,     0,    16,    34,  1550,    32,    41,   165,   163,
     244,     0,     0,   460,     0,   619,   617,   634,     0,    19,
      10,    11,     0,     0,     0,     0,     0,    43,    44,    45,
      47,    46,   160,     0,   242,     0,  1516,   253,   162,   246,
     247,   249,   250,   251,   267,     0,     0,   463,  1361,   270,
     331,   278,   624,   624,     0,     0,     0,   264,    23,    56,
      71,    49,    80,  1478,   166,   165,     0,   158,  1542,  1517,
    1566,   254,   255,   256,  1498,   245,   248,   271,   329,     0,
       0,   466,   275,     0,   274,   332,  1466,   280,  1507,   624,
     621,   627,     0,   624,   635,   613,    21,    12,     0,  1524,
      54,  1549,    55,  1549,    60,    62,    63,    64,     0,     0,
      70,     0,    73,  1579,    48,     0,  1578,     0,     0,  1524,
    1524,     0,     0,  1557,  1524,  1524,  1524,  1524,  1524,     0,
    1524,  1510,  1524,    79,    81,    83,    85,    86,    87,    89,
      88,    90,    91,    92,    93,    94,    95,  1479,     0,   164,
     244,  1543,     0,  1567,  1512,  1499,  1518,   268,   331,   461,
       0,     0,   558,   331,   334,     0,     0,   622,  1524,     0,
     632,   625,   626,   636,   612,  1524,     0,    57,  1549,    59,
      61,     0,  1491,  1524,     0,    77,     0,    72,    74,    52,
      50,     0,     0,  1379,   112,     0,     0,  1524,  1524,  1558,
    1524,     0,     0,     0,     0,     0,  1524,     0,  1511,     0,
      99,    82,    84,   167,   243,  1423,   263,  1372,  1374,  1513,
       0,  1519,     0,   272,   330,   331,   464,     0,     0,   265,
     273,   337,     0,   343,   344,   335,   347,   347,   338,   293,
    1512,  1524,     0,     0,  1524,  1512,  1536,  1524,  1496,     0,
     279,   281,   284,   285,   286,   287,   288,   289,   290,   291,
     292,     0,     0,  1524,   633,     0,     0,   614,    17,     0,
    1428,    69,    58,  1490,     0,    76,    75,    78,    51,    53,
    1524,   101,   102,     0,     0,     0,   153,   152,   103,   104,
     156,     0,   155,   139,  1526,   141,    96,     0,    97,   169,
    1484,  1485,     0,  1373,   257,   258,   261,   252,  1359,   462,
     331,   467,     0,   336,   348,   349,   339,     0,   349,   341,
       0,     0,  1524,  1496,     0,     0,     0,     0,     0,  1537,
    1524,     0,  1497,     0,     0,   282,   283,   628,   629,   631,
       0,   623,   637,   639,     0,     0,    68,     0,  1437,  1433,
    1438,  1436,  1434,  1439,  1435,   145,   146,   148,   154,   151,
     150,  1528,  1527,   142,     0,   111,   110,   100,   107,  1564,
     105,     0,  1424,   259,     0,   260,  1360,   465,   469,   559,
     357,   351,     0,   305,   325,  1486,  1487,   314,   309,   308,
     307,  1378,  1377,  1534,  1510,  1522,     0,   557,   326,   327,
    1524,  1524,   630,   639,     0,     0,    13,    66,    67,    65,
     117,   131,   127,   132,   114,   130,   128,   115,   116,   129,
     113,   118,   119,   121,   147,     0,   140,   143,   108,  1565,
    1524,    98,   184,  1536,     0,  1574,   227,     0,  1536,  1524,
    1508,  1529,   230,     0,   229,  1578,   214,   213,   168,   170,
     171,   172,   173,   174,   175,     0,   176,   177,   226,   178,
     179,   180,   181,   182,   183,  1524,   262,     0,   468,   470,
     471,   560,     0,  1500,     0,  1526,   342,     0,   295,  1535,
     316,     0,   298,  1523,  1562,   324,     0,     0,     0,   645,
     649,   640,   641,   642,   643,   648,     0,     0,   120,   123,
       0,   149,   144,     0,   106,  1524,  1529,  1575,   191,   231,
    1524,     0,  1509,  1524,  1505,  1524,  1530,     0,  1524,  1524,
    1498,     0,  1524,     0,   474,   472,   562,   373,     0,   447,
     382,   415,   403,   412,   409,   406,  1576,   383,   384,   385,
     386,   387,   388,   389,   390,   391,  1553,   346,   416,     0,
     392,   379,   393,   394,     0,     0,  1560,   396,   397,   395,
     443,   399,   400,   398,  1524,  1524,   340,   358,   359,   360,
     361,   362,   363,   380,   364,   365,   366,   367,   368,   369,
     370,   371,   372,     0,     0,  1501,     0,   352,     0,   306,
     297,   296,   294,   315,  1510,  1563,   303,   312,   311,   313,
     310,     0,   647,   650,   707,   758,   767,   774,   778,   802,
     806,   824,   817,   825,   826,   832,   865,   874,   876,   903,
     911,   913,  1574,   919,     0,   930,   951,   953,   989,   991,
     995,   706,  1001,  1014,  1034,  1051,  1053,  1057,  1064,  1065,
    1081,  1101,  1119,     0,  1137,  1148,  1156,  1158,  1160,  1162,
    1167,  1189,  1212,   644,   656,   657,   658,   659,   660,   661,
     662,   663,   665,   664,   666,   667,   668,   669,   670,   671,
     672,   673,   674,   675,   676,   677,   678,   679,   680,   681,
     682,   683,   684,   685,   686,   687,   688,   689,   690,   691,
     692,   693,   694,   695,   696,   697,   698,   699,   700,   701,
     702,   703,   704,  1185,  1186,  1187,   705,    22,     0,   122,
     109,     0,  1524,   193,   192,   188,     0,  1504,   230,   225,
       0,     0,   228,     0,     0,   237,  1547,  1547,     0,   238,
       0,   210,  1524,   347,   566,   561,   563,   564,   459,   413,
     414,   401,   402,   410,   411,   407,   408,   404,   405,  1577,
       0,  1554,   441,   423,   374,  1419,   457,  1561,   444,   445,
     442,     0,     0,   376,   378,  1482,  1482,     0,  1540,  1540,
     356,   353,  1429,  1431,   449,   451,   453,  1503,   317,   318,
     319,   320,     0,     0,   299,  1521,   305,     0,     0,   651,
       0,     0,     0,  1276,   773,     0,   804,   808,     0,     0,
       0,     0,     0,     0,  1276,   905,     0,     0,   915,   920,
       0,  1276,     0,     0,     0,     0,     0,     0,  1003,  1024,
       0,     0,     0,     0,     0,     0,     0,     0,  1133,  1131,
       0,     0,  1157,  1155,     0,     0,     0,     0,  1190,  1196,
       0,     0,   137,   133,   138,   136,   134,   135,   124,   125,
     199,   200,   198,   197,     0,   186,   187,     0,   219,   218,
     219,   215,   232,   233,   234,   236,  1548,   239,   240,   241,
    1375,  1524,   483,   483,  1526,   503,   475,   478,   479,     0,
     567,   565,   446,     0,  1572,     0,  1420,  1421,     0,   381,
     448,     0,   375,  1508,   417,   418,  1430,  1541,     0,     0,
       0,  1576,   452,     0,     0,     0,  1502,  1510,   304,   638,
     646,   756,   726,  1418,  1540,     0,     0,  1452,  1455,  1540,
    1352,     0,     0,     0,     0,     0,     0,     0,     0,  1452,
     765,  1394,   763,  1384,  1386,  1392,  1393,  1471,   768,     0,
    1275,  1297,  1371,     0,  1367,  1369,  1368,  1413,   780,  1412,
    1414,   803,   807,   820,     0,  1354,  1480,  1551,     0,  1433,
     863,   726,     0,  1386,   872,     0,   780,   882,   881,  1494,
     878,   880,   910,   907,   906,   909,   904,  1540,   912,  1380,
    1382,   914,  1365,   924,  1570,  1274,   932,   952,   485,     0,
     955,   956,   957,   990,  1105,     0,   992,     0,   999,     0,
    1002,  1025,  1371,  1015,  1024,  1017,     0,  1022,     0,  1368,
       0,  1473,  1214,  1357,  1551,  1214,     0,  1079,  1070,  1358,
       0,  1364,  1082,  1083,  1084,  1085,  1086,  1094,  1087,  1097,
       0,  1362,     0,  1102,  1120,  1134,  1506,     0,  1139,  1141,
       0,  1153,     0,  1159,     0,  1164,  1169,  1197,     0,  1198,
    1542,  1214,     0,  1469,   195,   194,   185,   196,     0,   217,
     216,  1524,   209,   203,  1376,   211,     0,   484,   480,     0,
     481,     0,   473,   476,   569,   424,  1573,   425,  1540,     0,
       0,     0,  1340,  1338,  1401,  1343,  1395,  1399,  1400,     0,
    1422,   458,   377,  1483,   355,   354,  1432,  1555,   454,   323,
    1534,     0,   301,   757,   708,  1503,     0,   735,     0,     0,
       0,     0,     0,  1440,  1457,  1451,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1441,   766,   759,     0,
       0,  1385,  1472,   771,  1471,  1277,     0,   776,     0,   781,
     791,  1411,   805,  1410,   810,   821,   818,   823,   822,  1276,
    1355,  1481,  1356,  1552,  1263,   831,   864,   833,   843,  1229,
    1229,  1229,  1229,   873,   866,     0,     0,   875,  1495,  1276,
     901,   888,   884,   886,  1276,   908,     0,  1381,   917,  1571,
     922,   934,     0,   486,     0,   978,   963,   954,   958,   960,
     961,   962,  1109,     0,     0,  1000,   996,     0,  1008,  1005,
    1007,  1006,  1009,  1016,  1019,   652,  1276,     0,     0,  1026,
       0,  1474,  1475,  1551,     0,  1052,  1036,  1059,  1072,  1080,
    1066,     0,  1072,     0,  1406,  1407,  1095,  1098,     0,     0,
    1363,  1093,     0,  1092,     0,  1122,     0,     0,  1132,     0,
       0,  1140,     0,  1154,  1149,     0,     0,  1165,  1166,  1163,
    1506,     0,     0,  1199,     0,     0,  1059,   126,  1489,     0,
     203,   201,  1470,     0,   222,   208,   235,     0,   477,   482,
     488,   498,   347,   504,  1559,  1542,   419,     0,  1348,  1349,
       0,  1341,  1342,  1425,     0,     0,     0,     0,     0,     0,
       0,     0,  1556,  1574,   322,  1534,  1542,   300,   731,   722,
    1229,   712,   719,   713,   715,   717,     0,  1229,     0,   711,
     718,   725,   724,     0,  1229,  1538,  1538,  1538,   729,   730,
    1403,  1402,     0,  1391,  1340,  1338,     0,     0,  1340,     0,
    1387,  1388,  1389,  1353,  1340,     0,     0,  1340,     0,     0,
    1340,  1340,  1340,     0,     0,  1236,  1480,     0,     0,   769,
       0,  1288,  1289,  1290,  1323,  1291,  1574,  1327,  1332,  1568,
    1298,  1335,  1568,  1316,  1295,  1305,  1287,  1286,  1324,  1294,
    1296,  1306,  1307,  1308,  1309,  1310,  1325,  1279,  1328,  1330,
    1311,  1312,  1313,  1314,  1315,  1282,  1283,  1284,  1285,  1299,
    1322,  1293,  1304,  1281,  1280,  1292,  1301,  1302,  1303,  1300,
    1317,  1318,  1319,  1320,  1321,  1278,     0,     0,  1370,   787,
       0,     0,   794,   815,   816,   809,   811,     0,  1236,  1268,
    1270,   828,  1264,  1265,  1266,     0,  1579,  1229,     0,  1230,
     836,  1232,   837,   834,   835,     0,  1236,  1480,   896,   898,
     897,   891,   893,   899,   902,   877,   889,   885,   883,  1276,
     652,   879,  1383,  1542,   916,  1366,   652,  1574,   942,   943,
     945,   947,   948,   944,   946,   937,  1574,   933,     0,   979,
       0,   981,   980,   982,   973,   974,     0,     0,   959,  1111,
    1544,     0,     0,   993,  1236,  1480,  1578,     0,  1020,   653,
    1027,  1028,  1031,     0,  1023,  1221,  1220,  1030,  1036,  1215,
       0,     0,  1263,     0,     0,     0,  1071,     0,     0,     0,
    1096,     0,  1100,  1099,  1090,     0,  1524,  1263,  1136,  1135,
    1142,  1143,  1144,     0,  1236,  1480,     0,  1467,     0,  1144,
    1211,  1201,  1200,  1206,     0,  1208,  1209,  1216,  1488,  1469,
       0,   205,   206,   204,  1524,   490,   501,   502,   500,   506,
     582,  1524,   573,   571,   572,   574,  1538,     0,  1524,     0,
     585,   577,  1538,   578,     0,   581,   586,   584,   579,   583,
       0,   580,     0,   568,   596,   591,   594,   593,   592,   595,
     570,   597,     0,   433,   434,  1506,   422,   435,   431,   429,
    1529,   427,  1396,  1397,  1398,  1351,  1339,  1344,  1345,  1346,
    1347,  1350,  1426,     0,   455,   321,     0,   723,  1232,   714,
     716,  1229,   720,   710,   750,  1524,   739,   740,  1524,   751,
     741,   742,   745,   755,   752,   743,     0,   753,   744,   754,
     736,   737,   709,  1539,     0,     0,     0,   727,   728,  1405,
    1390,  1404,  1452,  1480,     0,  1456,     0,  1452,  1452,     0,
    1449,  1452,  1452,  1452,     0,  1452,  1452,  1237,   760,  1239,
    1236,   772,     0,  1326,  1569,  1329,  1331,   777,   775,   782,
     783,   627,     0,   793,   792,  1202,  1203,   797,   795,     0,
     814,     0,   819,   652,   652,   829,   827,  1267,   843,   843,
     843,   843,  1524,   848,   861,   862,   849,     0,  1524,   852,
     853,   856,   854,     0,   855,   845,   846,   838,   844,   652,
    1233,  1228,     0,   867,     0,  1276,  1276,   895,   652,   892,
     887,     0,   925,     0,     0,   949,     0,     0,     0,   975,
     977,     0,   969,   985,   970,   971,   964,   965,   985,  1103,
    1524,     0,  1545,  1110,  1529,   994,   997,     0,     0,  1011,
    1021,  1018,   655,     0,     0,  1038,  1037,  1252,  1254,  1055,
    1249,  1250,  1062,  1060,     0,  1276,  1073,  1276,  1067,  1075,
    1088,  1089,  1091,  1476,  1129,  1243,     0,  1480,  1150,     0,
       0,  1468,  1170,  1171,     0,  1174,  1177,  1181,  1175,  1207,
    1542,  1210,  1222,  1492,   202,     0,   223,   224,   220,     0,
       0,   492,     0,  1559,     0,  1524,   575,   576,     0,   599,
    1524,  1572,   600,   598,   426,     0,   420,   436,   432,  1524,
     421,   428,  1427,  1524,   450,   302,  1227,   721,     0,     0,
    1272,  1272,   738,   733,   732,   734,  1445,  1236,  1453,     0,
    1465,  1450,  1443,  1463,  1444,  1446,  1447,  1460,  1461,  1448,
    1442,   652,  1240,  1235,   761,   770,  1574,     0,  1574,     0,
     784,   785,     0,   789,   788,   790,  1204,  1205,   800,   798,
     652,   812,   813,  1269,  1271,  1229,  1229,  1229,  1229,     0,
     850,   851,     0,  1272,  1272,   847,  1231,   652,  1236,  1354,
    1236,  1354,   894,   900,   890,   918,   926,   928,   935,   938,
     939,  1514,   950,   931,   936,   985,  1408,  1409,   985,     0,
     968,   966,   967,   972,  1113,     0,  1546,  1107,  1236,  1010,
    1004,     0,   654,  1032,     0,     0,  1044,     0,   652,   652,
    1056,  1054,  1251,  1063,  1058,  1061,  1068,   652,  1077,  1076,
    1477,     0,     0,  1130,  1121,  1244,  1146,  1246,     0,  1236,
    1236,  1161,  1467,  1173,  1522,  1179,  1522,  1243,     0,  1259,
    1261,  1225,  1223,  1256,  1257,  1224,  1493,     0,   221,   489,
    1524,     0,   494,   499,  1538,   535,   555,   550,  1496,     0,
       0,  1524,  1540,  1524,     0,   505,   511,   512,   513,   522,
     514,   516,   519,   507,   508,   509,   515,   518,   536,   520,
     523,   510,     0,   517,   521,  1417,   590,  1415,  1416,   606,
     589,   601,   611,   440,   437,   438,     0,     0,   747,   746,
     749,     0,   748,   762,  1454,  1238,   652,  1334,  1574,  1337,
    1574,   786,   801,   779,   652,   796,   842,   841,   840,   839,
     858,   857,   860,   859,  1234,   869,     0,   868,     0,   652,
     929,   923,   940,  1515,     0,   984,   976,   985,   987,     0,
       0,  1116,  1112,  1106,   998,  1013,     0,     0,  1039,  1524,
    1046,     0,  1040,     0,  1043,  1253,  1255,   652,  1074,   652,
    1123,  1124,  1125,  1126,  1127,  1128,   652,  1147,  1138,  1247,
    1242,  1145,  1152,  1151,  1172,     0,  1522,  1176,     0,  1183,
    1195,  1192,  1194,  1193,  1188,  1191,   652,   652,  1226,  1213,
    1258,  1219,  1218,  1531,     0,  1524,  1524,   496,   534,  1524,
     556,   554,   551,   552,  1526,   544,  1524,  1276,     0,     0,
       0,     0,   537,     0,     0,   542,   545,   548,   609,   607,
     608,   610,     0,   604,   602,   603,   605,     0,   439,   430,
     456,  1531,  1241,  1333,  1336,   799,  1236,  1236,   927,     0,
     983,   988,     0,  1524,  1114,     0,     0,  1104,  1108,  1012,
       0,     0,  1049,  1047,  1048,  1042,  1041,  1069,  1078,  1245,
     652,  1178,     0,  1182,  1184,  1168,  1260,  1262,  1532,  1533,
    1217,   491,     0,     0,  1524,   487,     0,   543,     0,   540,
    1480,   538,   539,   529,   527,   528,   530,   526,   531,   525,
     524,     0,   549,   547,   546,   588,   587,  1273,   871,   870,
     941,   986,     0,  1117,  1524,  1276,  1045,  1050,  1035,  1248,
    1180,   493,   495,     0,   533,   532,   553,     0,  1115,     0,
    1033,   497,     0,  1118,   541
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
    1133,   523,   524,   525,   526,   931,  1129,  1868,   527,   528,
     529,   530,   531,   532,   533,   534,   799,   137,   108,   109,
     110,   111,   144,   112,   374,   375,   445,   113,    31,    66,
     147,    84,   227,   152,   119,   153,   120,   157,   236,   321,
     322,   662,   323,  1367,   856,   548,   324,   460,   325,   668,
     326,   327,   663,   848,   849,   850,   851,   328,   329,   330,
      83,   228,   154,   155,   156,   234,   305,   450,   452,   306,
     307,   636,   386,   387,   543,   840,   308,   542,   637,   638,
     639,   962,   640,   641,   642,   643,   644,  1656,   645,   954,
    1346,  1890,  1657,  1658,  1659,  1660,  1886,  1661,  2084,  2085,
     646,   647,   830,   648,   649,   650,   546,   971,   844,   845,
    1894,   651,   652,   117,   295,   151,   380,   232,   448,   538,
     539,   540,   802,   946,   947,  1138,  1139,  1057,   948,  1615,
    1871,  2042,  2187,  2265,  1340,  1618,  1142,  1343,  1873,  2063,
    2064,  2280,  2065,  2066,  2067,  2068,  2271,  2069,  2070,  2071,
    2072,  2205,  2206,  2194,  2073,  2074,  2191,   468,   299,   541,
     596,   805,   806,   807,  1144,  1344,  1650,  2217,  2212,  1651,
      51,   243,   413,    87,   123,   122,   159,   160,   161,   240,
     335,   125,   337,   473,   474,   561,   562,   563,   564,   565,
     860,  1558,  1559,  1822,   566,   724,   725,   861,   981,  1177,
    1388,  1389,  1384,  1700,  1701,  1174,   726,   862,  1000,  1200,
    1198,   727,   863,  1008,  1419,   728,   864,  1477,   729,   865,
    1210,  1479,  1739,  1740,  1741,  1482,  1747,  1940,  1938,  2104,
    2103,   730,   866,  1021,   731,   867,  1022,  1485,  1486,   732,
     868,  1023,  1216,  1219,   733,   734,   735,   869,  1756,   736,
     870,   737,   871,  1030,  1497,  1775,  1776,  1227,   738,   872,
    1034,  1234,   739,   873,   740,   874,  1039,  1040,  1240,  1241,
    1242,  1520,  1518,  1788,  1243,  1511,  1512,  1787,  1515,   741,
     875,  1046,   742,   876,   743,   877,   744,  1052,  1524,   745,
     879,   746,   881,  1526,  1967,  2119,  2121,   747,   882,  1251,
    1535,  1795,  1969,  1970,  1971,  1973,   748,   883,   749,   884,
    1059,  1257,  1258,  1259,  1547,  1806,  1807,  1260,  1544,  1545,
    1546,  1800,  1261,  1980,  2232,   750,   885,   751,   886,  1066,
     752,   887,  1068,  1266,   753,   888,  1070,  1272,  1557,  1990,
     754,   889,  1073,  1275,  1821,  1074,  1075,  1076,  1561,  1562,
     755,   890,  1571,  1996,  2140,  2242,  2298,   756,   891,   757,
     892,  2001,   758,   893,  1572,  2004,   759,   760,   894,  1087,
    2147,  1292,  1574,  2007,  1838,  1839,  2149,  1290,   761,   895,
    1092,  1093,  1094,  1095,  1304,  1096,  1097,  1098,  1099,   762,
     896,  1063,  1984,  1262,  2133,  1549,  1809,  2131,  2237,   763,
     897,  1305,  1587,  2011,  2014,   764,  1105,  1308,   765,   900,
    1107,  1108,  1845,  2158,   766,   901,  1111,  1314,   767,   903,
     768,   904,   769,   905,   770,   906,  1319,   771,   907,  1321,
    1852,  1853,  1599,  1855,  2025,  2167,  2027,  2255,   772,   773,
     909,  2174,  1119,  1324,  1603,  1748,  1939,  1860,   774,  1605,
     775,   776,   911,  1285,  1862,  2128,  2031,  2179,  1677,  1500,
    1501,  1779,  1781,  1957,  1728,  1729,  1921,  1923,  2096,  2016,
    2017,  2156,  2160,  2250,  1829,  1830,  1998,  1831,  1999,  2032,
    2033,  2176,  2034,  2177,  1491,  1492,  1493,  1753,  1494,  1754,
    2090,  1054,  1055,  1010,  1011,  1205,  1206,  1450,  1451,  1452,
    1453,  1454,  1152,  1354,  1395,  1001,  1024,  1220,  1082,  1088,
     377,   378,  1100,  1101,  1248,  1077,  1014,  1015,   286,   462,
    1135,   463,   264,  1048,  1049,  1002,  1026,  1155,  1392,  1710,
    1808,  1975,  1032,  1078,  2076,  1004,   983,   825,   956,   957,
    2078,  1005,   842,   843,  1006,  1183,  1185,  1399,  1413,  1408,
    1405,   235,  1854,  1331,  1203,  1283,  2012,   218,  1222,   964,
     372,   394,  1332,   253,  2037,  1785,   403,   226,   656,  1178,
     587,   162,   583,   279,   290,  2124,   140,   292,   857,   554,
      43,   434,   588,  2260,   550,   400,  1704,   968,   222,  1813,
     937,   178,  1224,   822,  1363,   270,   654,   666,   500,   224,
    1735,  1250,  1147,   578,   820,  1498
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1670
static const yytype_int16 yypact[] =
{
   -1670,   229,   372, -1670,   214,   217,   116, -1670, -1670, -1670,
     530,   530,   625,   625, -1670, -1670,   631, -1670, -1670, -1670,
   -1670,   768,   768,   365,   777,   777,   628,   463, -1670,   911,
     890, -1670, -1670, -1670, -1670,   -38,   671,  1012,   580,   737,
     737, -1670,   583,    99,   604,   666,   789,   682, -1670,   381,
    1038,   886,  1045, -1670,   534, -1670, -1670,   895, -1670, -1670,
   -1670,   757, -1670, -1670, -1670,   867,   783, -1670,    26, -1670,
     466,   530,   625, -1670, -1670, -1670, -1670,   -66, -1670,  1067,
     221,   790,   894,  1025,   841, -1670, -1670,   948,   625, -1670,
   -1670, -1670,   848,   861,   876,   881,   899, -1670, -1670, -1670,
   -1670, -1670,  1001,   927,  1157,  1308,   985,   690, -1670,   134,
   -1670, -1670, -1670, -1670, -1670,   945,  1048,  1174, -1670,   362,
     725, -1670,   124,   124,   972,   964,   968,   777, -1670,   569,
    1237,   107,  1432,  1141, -1670, -1670,   996, -1670,  1154, -1670,
    1044, -1670, -1670, -1670,  1426, -1670, -1670, -1670, -1670,  1003,
    1108,  1134, -1670,   841, -1670, -1670, -1670, -1670, -1670,    64,
   -1670,   282,   273,   109, -1670, -1670, -1670, -1670,  1095,  1255,
   -1670,   404, -1670,   506, -1670, -1670, -1670, -1670,    80,   225,
   -1670,   -14, -1670, -1670, -1670,  1017,   469,  1364,  1033,  1255,
    1255,  1033,  1091,  1116,  1255,  1255,  1255,  1255,  1255,  1033,
    1255,  1425,  1255, -1670,   941, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,  1033,  1001,
     221, -1670,  1051, -1670,  1406, -1670,  1327,   362,   725, -1670,
    1053,  1152,  1162,   725,    47,   884,  1111, -1670,  1255,  1142,
    1240, -1670, -1670,  1409,   737,  1255,  1296, -1670,   519, -1670,
   -1670,  1177, -1670,  1255,  1331, -1670,   701, -1670, -1670, -1670,
   -1670,  1092,  1297, -1670, -1670,  1033,  1033,  1255,  1255, -1670,
    1255,  1051,  1481,  1033,  1033,  1051,  1255,  1051, -1670,  1033,
      28, -1670, -1670, -1670, -1670,   658,  1051, -1670, -1670, -1670,
     841, -1670,   841, -1670, -1670,   725, -1670,  1100,  1199, -1670,
   -1670, -1670,   884, -1670, -1670, -1670,   -33,    15, -1670, -1670,
    1406,  1255,   -56,   -56,  1255,    46,  1306,  1255,  1531,  1283,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670,  1009,   662,  1255, -1670,  1120,  1109, -1670,   886,  1296,
   -1670, -1670, -1670, -1670,  1051, -1670, -1670, -1670, -1670, -1670,
    1255, -1670, -1670,   589,  1051,  1325, -1670, -1670, -1670, -1670,
   -1670,  1051, -1670, -1670,    68, -1670, -1670,   980, -1670, -1670,
   -1670, -1670,  1051, -1670,   841, -1670,  1263,   841, -1670, -1670,
     725, -1670,  1112, -1670, -1670,  1479, -1670,  1480, -1670, -1670,
    1296,  1128,  1255,  1531,  1051,   -65,   -13,  1296,  1135, -1670,
    1255,  1130, -1670,  1130,    79, -1670, -1670, -1670, -1670, -1670,
    1296, -1670, -1670, -1670,   483,    33, -1670,   936, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670,   589, -1670,  1172, -1670, -1670,
   -1670, -1670, -1670, -1670,  1296, -1670, -1670,   980, -1670,  1189,
   -1670,  1072, -1670, -1670,  1296, -1670, -1670, -1670,  1264, -1670,
   -1670,    69,  1146,  1180, -1670, -1670, -1670,  1051, -1670, -1670,
   -1670, -1670, -1670,  1349,    77,  1386,  1147, -1670, -1670, -1670,
    1255,  1255, -1670, -1670,  2633,   625, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670,   561, -1670,    90, -1670,   589,  1296, -1670, -1670, -1670,
    1255,   980, -1670,  1306,  1271,  1188, -1670,  1228,  1306,  1255,
    1534,   188,   -48,  1296, -1670,  1155, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670,  1213, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670,  1255, -1670,  1130, -1670,  1264,
   -1670, -1670,  2257,  1566,  1412,   121, -1670,  1296,    83, -1670,
   -1670,  1296, -1670, -1670,  1230, -1670,   228,   228,  2930, -1670,
    1149, -1670, -1670, -1670, -1670,  1248,  3607,  1153, -1670, -1670,
     561, -1670, -1670,  1033, -1670,  1255,  1390, -1670,   120, -1670,
    1255,   542, -1670,  1255, -1670,  1255, -1670,  1246,  1255,  1255,
    1426,   236,  1255,  1171, -1670, -1670,  1385, -1670,  1388, -1670,
   -1670,  -130,   512,   557,   681,   685,  1179, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670,  1269, -1670, -1670,  1296,
   -1670, -1670, -1670, -1670,  1051,  1051,  1405, -1670, -1670, -1670,
     -23, -1670, -1670, -1670,  1255,  1255, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670,  1024,   -71, -1670,   129, -1670,   204, -1670,
   -1670, -1670, -1670,   102,  1425, -1670,   864, -1670, -1670, -1670,
   -1670,  1510, -1670,  1387, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670,  1217, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670,  1188, -1670,  1170, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670,    -2, -1670, -1670,  1320, -1670, -1670, -1670,
   -1670,   922, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,   601, -1670,
   -1670,   298,  1255, -1670, -1670,   441,   528,  1588, -1670, -1670,
     -13,  1250, -1670,  1051,  1051, -1670,  1345,  1345,  1352, -1670,
    1051, -1670,   175,   -33, -1670, -1670,  1385, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
    1187, -1670, -1670,  1232, -1670,  1181,  1236, -1670, -1670, -1670,
   -1670,  2119,   204,  1605, -1670,  1277,  1277,   589,  1363,  1363,
   -1670, -1670,  1183, -1670,   204, -1670,  1241, -1670, -1670, -1670,
   -1670, -1670,    48,  1466, -1670, -1670,  1180,  1296,  1191, -1670,
    1194,  1051,  4134,  1202,   343,  1987, -1670, -1670,  4740,   841,
    1244,  4833,  4740,  1414,   311,   921,    98,  1051, -1670, -1670,
    1515, -1670,    98,  1051,  2275,  1051,  4178,  4740, -1670,  1687,
     841,  1051,   841,  1051,    75,    89,  1051,   841, -1670, -1670,
    4354,  4418, -1670, -1670,  1051,  1051,   841,  1051, -1670,  1006,
    1545,  1051, -1670, -1670, -1670, -1670, -1670, -1670,  1633, -1670,
   -1670, -1670, -1670, -1670,  1051,   132,   162,   172,  1216, -1670,
    1216, -1670, -1670, -1670,   761, -1670, -1670, -1670, -1670, -1670,
    1051,  1255,  1483,  1483,   121, -1670, -1670, -1670, -1670,  1469,
   -1670, -1670, -1670,  1296,  1257,  5329,  1203, -1670,  1051, -1670,
   -1670,  1427, -1670,  1534, -1670, -1670, -1670, -1670,  1051,  1051,
     589,  1179, -1670,   204,   -13,   -13,  1627,  1425, -1670, -1670,
   -1670,  1537,   669, -1670,  1363,  1206,  1051,  1210,  1211,  1363,
     658,  1212,  1214,  1215,  1218,  1219,  1221,  1222,  1223,  1210,
    1543, -1670,  4476, -1670, -1670, -1670, -1670,  1468, -1670,  1620,
   -1670, -1670, -1670,  1279, -1670,   658, -1670, -1670,  1251, -1670,
   -1670,   383,   841,  1551,  1492, -1670,  1337,  1367,   841,   951,
    1553,  3898,   960,  1101,  1554,   153,  1251, -1670, -1670,    71,
   -1670, -1670, -1670,  1587, -1670, -1670, -1670,  1363,    98, -1670,
   -1670, -1670, -1670, -1670,  1292, -1670,    97,  1051, -1670,    60,
   -1670, -1670, -1670, -1670, -1670,  4740, -1670,  1289,  1555,  1639,
     734, -1670,  1293, -1670,  2457,  1557,   852,  1299,  1301,   235,
    1303,   624,  1517, -1670,  1367,  1517,  1051,  1559,  1270, -1670,
     856, -1670, -1670, -1670, -1670, -1670,  1457, -1670,    98, -1670,
     457, -1670,    92, -1670, -1670,   376,  1653,  4070, -1670, -1670,
    1051,  1560,  4520,  1051,  1528,   973,  1596, -1670,  1378,  1333,
    1154,  1517,   601,   186, -1670, -1670, -1670, -1670,   -41, -1670,
   -1670,  1255, -1670, -1670, -1670, -1670,   383, -1670, -1670,  1051,
   -1670,  1296,  1385, -1670, -1670, -1670, -1670,  1598,  1363,  5329,
    5329,  5329,    18,   835, -1670, -1670, -1670,  1183, -1670,  5329,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670,  1350, -1670, -1670,
    1349,   -13,  1603, -1670, -1670,   856,  1205,  1281,   516,    55,
    5329,  1319,  5329, -1670,  5329, -1670,  2536,  1282,  5329,  5329,
    5329,  5329,  5329,  5329,  5329,  5329, -1670, -1670, -1670,  4740,
    1536, -1670, -1670,  1391,  1468,  1728,  3314,  1418,  1491, -1670,
     434, -1670, -1670, -1670,   759, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670,     8,   841, -1670, -1670,   501,  1570,
    1570,  1570,  1570, -1670, -1670,  4740,  4740, -1670, -1670,    84,
    1601,   842, -1670,  1302,   311, -1670,  1051, -1670,    17, -1670,
   -1670,  1018,  1565, -1670,   856,   160, -1670,    60, -1670, -1670,
   -1670, -1670,    95,  1338,    98, -1670, -1670,  4740, -1670, -1670,
   -1670, -1670,  1376, -1670, -1670, -1670, -1670,  1051,   343, -1670,
    1118, -1670, -1670,  1367,   383, -1670,  1532,   340,   163, -1670,
   -1670,  1051,   163,  1341, -1670,  1183, -1670, -1670,    88,   980,
   -1670, -1670,  4006, -1670,  1694,  1530,  4740,  4740, -1670,  4613,
    1051, -1670,  1569, -1670, -1670,  4740,   856, -1670, -1670, -1670,
    1653,  1540,  1051, -1670,  1094,   103,   340, -1670, -1670,  1628,
   -1670, -1670, -1670,  1474, -1670, -1670,  1051,  1051, -1670,  1051,
    1561,  1073,    15, -1670,  5113,  1154,   164,  2536,  1304,  1304,
     871, -1670, -1670, -1670,  5329,  5329,  5329,  5329,  5329,  5329,
    2961,   835, -1670,  1188, -1670,  1349,  1154, -1670, -1670, -1670,
    1570, -1670, -1670,  1310,  1313, -1670,   856,  1570,  1541, -1670,
   -1670, -1670, -1670,  1538,  1570,  1489,  1489,  1489,   112,  1527,
   -1670, -1670,   384, -1670,    58,   920,  1051,   901,    85,  1307,
   -1670,  1183, -1670, -1670,   252,  1309,  1031,   621,  1311,  1040,
     101,   127,   719,  1312,  1049,  4696,     6,  4740,    98, -1670,
    1421, -1670, -1670, -1670, -1670, -1670,  1188, -1670, -1670,  1366,
   -1670, -1670,  1366, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670,  1368,   343, -1670,    52,
    1051,  1051,   686, -1670, -1670, -1670,    14,   966,  1396, -1670,
   -1670,  1641, -1670,  1506, -1670,   148,   771,  1570,  1507, -1670,
   -1670,  1512, -1670, -1670, -1670,  1590,  4696,    37, -1670, -1670,
   -1670,  3196, -1670,  1375, -1670, -1670, -1670, -1670, -1670,    84,
   -1670, -1670, -1670,  1154, -1670, -1670, -1670,  1188, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670,  1448,  1188, -1670,  1377, -1670,
    1729, -1670, -1670, -1670,   891, -1670,   856,    53, -1670,    80,
     709,   889,    98,    98,  4696,   373,  1155,   841,  1642, -1670,
   -1670,  1772, -1670,  1606, -1670, -1670, -1670, -1670,  1532, -1670,
    1051,   544,     8,   979,  1353,  1658, -1670,  1355,   856,   933,
   -1670,   384, -1670, -1670, -1670,  4740,  1255,     8, -1670, -1670,
   -1670, -1670,   304,  1051,  4696,   505,  1392,  1775,  1051,   588,
   -1670, -1670, -1670,  1486,  1488, -1670, -1670,  1118, -1670,   177,
     840, -1670, -1670, -1670,  1255,  1619, -1670, -1670,  1296, -1670,
   -1670,  1255, -1670, -1670, -1670, -1670,  1489,  1168,  1255,  1987,
   -1670, -1670,  1489, -1670,  1296, -1670, -1670, -1670, -1670, -1670,
    1051, -1670,  1051, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670,  1051, -1670, -1670,  1653, -1670,  1594, -1670,   889,
    1390,   889, -1670,  1183, -1670, -1670,   920,   955,   955,  1304,
    1304,  1304, -1670,  1068,  1394, -1670,  1051, -1670,  1512, -1670,
   -1670,  1570, -1670, -1670, -1670,  1255, -1670, -1670,  1255, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670,   -28, -1670, -1670, -1670,
    1538, -1670, -1670, -1670,   383,   383,   383, -1670, -1670, -1670,
   -1670, -1670,  1210,  1337,  5265, -1670,  1051,  1210,  1210,  5329,
   -1670,  1210,  1210,  1210,   432,  1210,  1210, -1670, -1670,  1533,
    4696, -1670,    98, -1670, -1670,   677,   708, -1670, -1670,  3771,
   -1670,  -115,    51, -1670, -1670, -1670, -1670,  1080, -1670,  1470,
   -1670,  1456, -1670, -1670, -1670, -1670, -1670, -1670,  -111,  -111,
    -111,  -111,  1255, -1670, -1670, -1670, -1670,  1208,  1255, -1670,
   -1670, -1670, -1670,     1, -1670,   771, -1670, -1670, -1670, -1670,
   -1670, -1670,  4740, -1670,  4740,    84, -1670, -1670, -1670,  3196,
   -1670,  1051,  1675,  1369,   646,  1692,  1371,   552,   856, -1670,
   -1670,  1752, -1670, -1670, -1670, -1670,    53, -1670,  1631, -1670,
    1255,  1524, -1670, -1670,  1390,    98, -1670,  4740,   236,   614,
   -1670, -1670, -1670,  1051,  4740,   764, -1670, -1670, -1670,  1667,
    1548, -1670,  1668, -1670,  1572, -1670, -1670, -1670, -1670,  1355,
   -1670, -1670, -1670,  1552,  1670,  1529,  1520,  1337, -1670,  4740,
     552, -1670,  1539, -1670,   856, -1670,  1702,  1428, -1670, -1670,
    1154, -1670,   859,  1809, -1670,  1081, -1670, -1670, -1670,  1296,
    1708,  1608,  1756,  5205,   308,  1255, -1670, -1670,   308, -1670,
    1255,  1257, -1670, -1670, -1670,  1398, -1670, -1670, -1670,  1255,
   -1670, -1670, -1670,  1255, -1670, -1670, -1670, -1670,   308,   308,
     108,   108, -1670, -1670, -1670, -1670, -1670,  1396, -1670,  1088,
   -1670, -1670, -1670,   920, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670,  1188,  1674,  1188,  1677,
   -1670, -1670,  4740, -1670, -1670, -1670, -1670, -1670,  1709, -1670,
   -1670, -1670, -1670, -1670, -1670,  1570,  1570,  1570,  1570,   308,
   -1670, -1670,   308,   108,   108, -1670, -1670, -1670,  4696,  1505,
    4696,  1513, -1670, -1670, -1670, -1670, -1670,  1704, -1670,   646,
   -1670,  1741, -1670, -1670, -1670, -1670, -1670, -1670, -1670,   552,
    1118, -1670, -1670,  1118,    -3,  1051, -1670, -1670,  4696, -1670,
   -1670,   981,  3689, -1670,  1792,  1607,  1632,   416, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670,  1051,   917, -1670, -1670, -1670,  1700,  1583,  1051,  1396,
    4696, -1670,  1775, -1670,  1386,  1755,  1386,  1529,   422, -1670,
   -1670,  1706, -1670,  1593, -1670, -1670, -1670,   767, -1670, -1670,
    1255,  1759,  1638, -1670,  1145, -1670,  1659,  1182,  1531,  1669,
    1430,  1255,  1363,  1255,  1051, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670,  1475, -1670, -1670,
   -1670, -1670,   831, -1670, -1670, -1670, -1670, -1670, -1670,   575,
   -1670,   659, -1670, -1670,  1398, -1670,  1051,   204, -1670, -1670,
   -1670,   308, -1670, -1670, -1670, -1670, -1670, -1670,  1188, -1670,
    1188, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670,  4740, -1670,  4740, -1670,
   -1670, -1670, -1670, -1670,  1810,  1118,  1118, -1670,  1462,  1562,
     841,   435, -1670,  1051, -1670, -1670,  1549,  4740, -1670,  1255,
     998,  1634, -1670,  1637, -1670, -1670, -1670, -1670, -1670, -1670,
    1051, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670,  1051,  1386, -1670,  1051,  1725,
   -1670, -1670, -1670, -1670, -1670,   841, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670,  1225,  1296,  1255,  1255,  1707, -1670,  1255,
   -1670, -1670, -1670, -1670,   121, -1670,  1255, -1670,  1051,  1051,
     537,  1701, -1670,  1591,  1296,   831, -1670, -1670, -1670, -1670,
   -1670, -1670,   308, -1670, -1670, -1670, -1670,   308, -1670,  1051,
   -1670,  1225, -1670, -1670, -1670, -1670,  1396,  1396, -1670,  4740,
    1118, -1670,  4740,  1255,   841,   841,  1578, -1670, -1670, -1670,
    1467,  1051,  1750, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670,  1051, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670,  1296,  1296,  1255, -1670,  1296, -1670,  1296, -1670,
    1337, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670,  4740, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670,   343,   841,  1255, -1670,  1051, -1670, -1670, -1670,
   -1670, -1670, -1670,  1296, -1670, -1670, -1670,  1840, -1670,   343,
   -1670, -1670,  4740, -1670, -1670
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1670, -1670, -1670, -1670,  1885, -1670, -1670, -1670,    36, -1670,
   -1670, -1670, -1670, -1670,  1558, -1670, -1670, -1670,  1298, -1670,
   -1670,    73,  1870, -1670, -1670,  1839,   210, -1670, -1670, -1670,
   -1670, -1670,  1711,  1764, -1670, -1670,  1727,   730, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670,  1719, -1670, -1670, -1670, -1670,
    1697, -1670, -1670, -1670, -1670, -1670,  -247,   603, -1670, -1670,
   -1670, -1670,  1415, -1670, -1670,  1335,   781, -1670, -1670, -1670,
   -1670, -1670, -1670,  1482, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670,  1773, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670,   581, -1670,   573,
     791, -1670, -1670, -1670, -1670, -1670,   982,    57, -1670,  1339,
   -1670, -1670, -1670, -1670, -1670, -1670,   100, -1670,  1696, -1670,
    1814, -1670, -1670, -1670, -1670,  1556, -1670, -1670,   605, -1670,
   -1670, -1670, -1670,  1699, -1670,  1878,  1776, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670,  1075, -1670, -1670, -1670,  1379,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670,   780, -1670, -1670, -1670,  1630, -1670, -1670,  -551,
   -1670, -1670,  -291, -1670, -1670, -1670,  -252, -1670, -1670, -1670,
   -1670, -1670, -1670, -1291, -1284,  1102, -1283, -1670,    66, -1670,
   -1670, -1670,   276,   284, -1670,   390, -1670,   287, -1670,  -139,
   -1279, -1670, -1670, -1273, -1670, -1270, -1670, -1670, -1670,  1104,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670,  1410, -1670, -1670, -1670,  1008, -1670,  -898, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670,  -114, -1670, -1670, -1670, -1670,
   -1670, -1670,  -253, -1670, -1670, -1670, -1670,   379, -1670, -1670,
   -1670, -1670, -1670,  1148, -1670, -1670, -1670, -1670, -1670, -1670,
     240, -1670, -1670, -1670, -1670, -1670,  1832,  1178, -1670,   218,
   -1670, -1670, -1670, -1670,  1485, -1670, -1670, -1670, -1670, -1670,
   -1670,  -915, -1670, -1670,   138, -1670, -1670, -1670, -1670,   930,
     574,   576, -1670, -1670,   265, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
     931, -1670, -1670,   227, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670,  -214, -1670,   193, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670,   728, -1670, -1670,
     732, -1670, -1670, -1670, -1670,   450,   189, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670,     7,   724, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670,   720, -1670, -1670, -1670,   178, -1670, -1670,   442,
   -1670, -1670, -1670, -1582, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1148,   904, -1670, -1670,   165,
   -1670, -1670,   419, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670,   663, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670,   698, -1670,   152, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670,   896, -1670,   898, -1670,
   -1670,  1097, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670,   887,   399, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670,   -22, -1670,   402, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
   -1670, -1670, -1670,  -821, -1670, -1160, -1670, -1670,  -995, -1149,
   -1061, -1670,   325, -1670, -1391, -1670, -1670, -1670, -1670,   -19,
   -1670, -1670, -1670, -1670,  -136, -1670, -1670,   179, -1670, -1670,
   -1670, -1670,   -21, -1670,  -919, -1635, -1670, -1670,   517, -1670,
    -768, -1258,  -843, -1193, -1670, -1670, -1670, -1189, -1187, -1183,
   -1170, -1168,    56,  -113,  -717,  -837, -1008,  -853,   303,   925,
   -1016,   -84, -1670, -1065, -1670,  -817, -1670,   805,  -390,  -146,
   -1670,  -609,   863,  -823,  -981,  -640,  -808, -1670, -1670,   433,
   -1049, -1246,  -969,  -826,  -992,   949,  -591,  -220, -1670,  1059,
    -222,  -645,  -467,  -311,  -209,  -959, -1670, -1670, -1670, -1670,
   -1670,  1782, -1670,   410,   816, -1670, -1670, -1670, -1669,  1186,
      62,  1713,   765,  -427, -1670,   990,  -388,  1440, -1670,  -607,
   -1670, -1069,  1069,  -414,   600, -1670, -1670,  -696, -1670, -1145,
    -168,  -538,  -503,  -190,  -990,   735, -1338,  -829, -1077, -1670,
    1238,  1976,  -497, -1670, -1670, -1670, -1670, -1670, -1670, -1670,
     602, -1670,   155,  -684,  1066,  -128
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1579
static const yytype_int16 yytable[] =
{
     121,   246,   288,   187,   457,   456,  1113,   658,   878,   589,
     969,   841,  1225,   846,   535,  1025,   389,  1470,  1560,  1471,
    1009,   265,   266,  1472,   341,   910,   271,   272,   273,   274,
     275,  1041,   277,   824,   280,  1300,  1473,  1309,  1474,  1018,
    1196,  1293,   427,  1325,  1907,   803,  1513,  1013,  1705,  1706,
     552,   288,  1212,  1644,  1003,   288,   852,   288,   187,  1056,
    1645,  1646,  1802,  1003,  1035,  1647,   288,  1247,   331,   121,
     332,  1648,  1102,   782,  1649,  1247,   287,   339,  1067,  1069,
      85,  1502,  1503,  1504,  1086,   344,    22,  1351,  1238,   477,
    1900,   431,  1109,  1003,  1047,  1047,   974,  1752,  1047,   353,
     354,   158,   355,  1047,  1047,  1508,    89,   569,   361,  1803,
     409,  1382,  1604,   158,   427,  1783,    14,   415,  1154,  1953,
    1567,  1247,   366, -1542,   288,   356,  1368,  1351,  1523,   360,
     289,   362,   847,   278,   288,   384,  1933, -1506,   837,   660,
     373,   288,   251,   391,   431,    92,   396,   398,   835,   401,
   -1502,  1254,   442, -1578,  1351,  1179,   105,   158,   158,  1931,
    1186,   126, -1529,  1816,   179,   410,   586,  1338,   453,  1539,
    1351,    54,    41,   158,   288,   464,   288,  1385,  2019,   838,
    1364,   932,   417,   384,   571,  1551,   291,   960,   472,  -764,
     498,  1415,  1653,   847,  1201,  1333,  1351,   828,   416,   846,
    2129,  1390,  1235,  1848,    93,  1538,   376, -1542,   428,   458,
    1301, -1578,   497,   837,  1328,   430,  1540,  1489,  1246,   461,
    1784,    18,   536,  1201,   455,   584,  1983,  2035,  1506,     3,
     898,  1031,   466,   809,   254,   941,  1090,   288,  1153,  1061,
     783,  1339,  1758,   105,   418,   796,   470,  -189,   287,  1012,
     854,  1597,   238, -1524,   574,   803,    41,  1263,   392,  1554,
     393,  1112,   942,   943,  1287, -1578,    94,  1596,  1652,  1490,
   -1466, -1466,  1804, -1578,   572,  1298,  1654,  -190,   432,    41,
      52,    91,   810,   544,   784,   419, -1502,  1124,  1875,  1676,
     376,   590,   420,   446,  1880,     4,  1328,   239,   585,  1109,
    1326,  1334,   556,   557,  1201,  1328,    95,  1594,    96,  1678,
     459,   373,  1154,  1154,  1154,  1569,  1678,  1247,   829,  1347,
     418,  1351,  1154,  1678,  1496,   659,  1513,  1681,  1168,   664,
    1541,   432,   573,  1091,   836,  1012,   669,   669, -1518,  1924,
   -1506,   581,   899,  1154,   804,  1154,  1025,  1154,  1777,  1221,
     839,  1154,  1154,  1154,  1154,  1154,  1154,  1154,  1154,  1236,
    1391,   419,  1655,   421,  -189,  1169,  1170,   593,   420,  1171,
     221,  1934, -1506,  1352,   653,  1675,  1488,  1164,  1165,  1542,
    1221,   106,  1682,  1025, -1506,    41,  1255,   591, -1529,  1702,
    1901,  1416,  1091,  2125,  -190,   418,  2126,   823,  1475,   661,
    -620,  1041,   586,   385,  1125,   826,  1141,   781,  1387,  1730,
    1742,   -31,   786,  1352,  1025,   790,    55,   791,   920,  1954,
     793,   794,     5,   285,   800,  2130,   422,  1505,  1507, -1506,
    1761,  1525,  1348,  1349,  1350,   257,   419,  1731,   252,   421,
    1352,  1553,  1361,   420, -1506,  -618,  1791,  1863,  1759,  1256,
      89,   388,   975,   285,    86,   423,  1352,   255,  1805,  1555,
     667,  1564,  1025,   944,   263,  1397,   831,   832,   106,  1353,
     478,  1404,  1406,  1407,  1409,   551, -1524,  1412,  1414,   107,
    1935, -1506,  1352,  1509,   338,   570,  1579,  1510,  1157,   285,
    1302,   285,   797, -1506,  1584,   424,   301,  1801,  1588,  1589,
      56,  1591,   422,  1239,   263,  2244, -1502,  1595,  1606,  1712,
    1303,   285,   950,  -620,   421,   471,  2093,  1154,  1154,  1154,
    1154,  1154,  1154,  1154,   285,   285,   966,    63,   285,  1840,
    1329,   423,   183,   285,   285,   853, -1458,   183, -1506,   285,
     340,  1819,   183,   170, -1506,  2230,    63, -1504,   567,   798,
   -1506,     4,  1722, -1506,   804,   925,  1817,  1131,  -618,  1306,
     928,   837,  1365,  1172,  1025,  1543,   107,  2115,  -189,  2117,
     288,   424,  1247,   288,   288,  1012, -1578,   422,  1723,  2008,
     288,  1385,  2056,   145,  1760,  2170,  1885,  1286,  1393,  2057,
    2058,  1342,  1513,   241,  2060,  1400, -1578,  2134,  -190, -1578,
    2061,  2306,    88,  2062,  2021,  1790,   423,  1352,   285,   921,
    2141,  1792,  1329,   285,   924,  1211,  1709,  1480,  2235,   475,
    1678,  1329,  -207,  1295,   945,  2171,  2273,  2274,  2162,  2163,
      32, -1549, -1419,  2172,   949,   978,  1132,  1666,  1667,  1668,
    1669,  1670,  1671,  1673,  1016,   168,   424,   934,   935,   238,
    2275,  1917,  2142,  1832,   940,  1522,  1020,   922,  1528,  1166,
    1738,  1529,  1530,    12,   285,  1064,    13,  1827,  1844,  1079,
    1742,  1083,  2143,  1083,  1089,  1062,  1064,    16,     5,  1674,
    1020,  1575,  1157,  1157,  1157,  1575,  1897,   955,  1849,   929,
    1351,  1083,  1157,   407,   239,  1355,  1356,  1357,  1358,  1175,
    1359,  1091,   242, -1464,   288,  2173,  2189,  1127,  1295,    75,
    1037,    64,  1307,  1157,  1038,  1157,  1221,  1157,  2236,  1401,
     288,  1157,  1157,  1157,  1157,  1157,  1157,  1157,  1157,  1815,
      64,  1145,   167,  2127, -1502,  1903,  1904,  1905,  1161,   183,
     506,   926,  1733,   418,   285,  1386,  1158,   168,    23,  1978,
    2075,  1925,   481,  1906,   288,   288,  1662,   169,  1911,  1912,
     168,  1080,  1914,  1915,  1916, -1578,  1919,  1920,   930,   408,
    1481,   507,     5,  1136,  1958,   183,  1960,  1842,  1123,   285,
     418,    65,   469,  2028,   419,  1027,  1568,  1295,  1351,     5,
    1749,   420,   912,   482,  1134,    26,  2106,  2107,  2108,  2109,
     483,  1711,  1828,  1879,  1762,  2023,  1081,  1763,  1084,  1988,
     168,    75,  1387,  1104,    29,  1764,  1765,  1766,  2208,   285,
     285,   419,  1115,  2151,    75,  2152,  2276,  2277,   420,  2153,
    1926,  2091,  2091,   913,  1247,  2288,  2289,  1918,  1943,  1944,
     914,  2020,  2154,  1793,  2155,  1176,  1745,  2144,  1221,  1295,
   -1578,    55,  1796,   247,   370,  1299,   787,    19,   118,   169,
      33,  1928,   421,   788,  1956,  1020,  1089,  2278,  2279,  2209,
   -1578,   485,   169,  1964,    75,   811,    30,  1154,  1281,  2165,
    1663,  2168,  1154, -1578,  2091,  2091,  2080,  1157,  1157,  1157,
    1157,  1157,  1157,  1157,   340,  1531,  1532,  1268, -1502,   421,
    1539,   514,  2213,   250,   183,  1811,  2088,  2089,   346,  1295,
     390,   915,    34,  1533,  1534,   397,   594,  1653,   260,  1341,
     813,  1495,   169,  1282,   812,   422,  1767, -1549,  1252,  1959,
     371,  1961,    20,   347,   486,    56,  1496,  1269,  1214,  2269,
    1158,  1158,  1158,  1963,  1768,  1270,  1080,  1540,  -333,  -333,
    1158,   288,   188,  2214,   423,   249,  1927,  2110, -1578,  1995,
    2111,  1769,   422,  1335,  1025, -1502,   189,   190,   342,   814,
    1746,  1158,  2182,  1158,   916,  1158,  1352,  1402,   250,  1158,
    1158,  1158,  1158,  1158,  1158,  1158,  1158,  1929,   285,  1812,
    1711,   423,  2006,    36,   424, -1578,  1025,  1909,   191,   340,
   -1578,  1654,  1913,   489,   141,   170,  2095,    38,   294,  1770,
    2029,  1091,  2175,   300,  1117, -1578,  1994,  1271,  2210,  2211,
   -1578,  2252,    44,   183,   285,  2105, -1518,  1527,  1016,    49,
    1528,   424,    53,  1529,  1530,   192,   193,  2310,   194,    50,
     855,  1118,  2114,   917,   815,  2183,   195,   418,   817,   183,
     118,  1619,  1187,    59,   267,  2181,  1771,   480,  1016,   142,
     143,  1541,   276,   340,  1355,  1356,  1357,  1358,  1489,  1359,
    1426,  1427, -1462,   502,  1352,   379,   503,  1208,  1483,  1295,
    1295,   283,  -978,  2145,  2146,  2203,  1487,  1865,   419,   196,
     197,   504,  2148,   816,   291,   420, -1520,   818,  1428,  2221,
     198,   505,  2215,  2216,  1429,  1016,   908,   303,   304,  1772,
    1542,  1295,   309,  2150,  2234,    60,   288,   288,  2030,  1773,
    1490,  1827,  1810,  -978,  2101,  2204,  1565,   481,   351,   352,
    -978,    62,  1131,  2092,   251,  1431,   358,   359,  1664,  1432,
      61,   446,   365,   368,  2308,  1158,  1158,  1158,  1158,  1158,
    1158,  1158,  1977,  1566,  1866,    68,  1867,  1889,   310,  1573,
     447,  2313,  1355,  1356,  1357,  1358,   421,  1359,   482,  1484,
   -1459,   880,   311,   405,   199,   483,  -921,    72,    45,  -921,
    1774,  2222,  -921,  -921,  -921,  2112,  2113,   484,   833,  2225,
    1612,  1612,     5,   406,   183, -1578,  1085,  -207,  1573,   183,
      75,  -978,  1750,   285,  2228,  1977,    79,  1489,   834,  2075,
     312,  1132,  1042,  1043,  1121,  1833,    46,  2135,    81,  2293,
    2285,    82,  1751,  2199,    47,  2286,  1044,   433,  -921,   422,
    1369,  1370,  2247,   103,  2248,  1834,  1394,  2136,   575,   114,
    1398,  2249,  2097,   580,  2099,   115,   485,  1157,  1410,  1411,
    1601,  -921,  1157,   435,  1602,   436,  1828,  1016,   423,  1490,
     116,  2256,  2257,  2226,  -978,  2227,  -921,  1531,  1532,  1276,
     506,  1371,  1045,  1372,  1239, -1524,  1516,   118,  1355,  1356,
    1357,  1358,  1277,  1359,   124,  1533,  1534,  1317,   200,  1318,
    1360,  1716,   285,  -978,  1719, -1524,  1543,   128,   424,  1724,
      10,   507,  1616,  1617,    10,  1373,  1374,  1375,   508,   486,
     129,  1987,   487,   488,  1355,  1356,  1357,  1358,  1876,  1359,
    1877,    41,  1665,  -921,  -921,   130,   313,  -978,   201,  2240,
     131,  1295,  1582,  -978,  1977,  2299,  1583,   237,   314,  1295,
    1936,   237,  1937,  2296,  1355,  1356,  1357,  1358,   132,  1359,
    -921,  -921,  1376,   509,  1377,   133,  1714,  -921,  1950,   510,
    1951,  -921,  1378,  1355,  1356,  1357,  1358,  1446,  1359,   136,
    1448,  1449, -1411, -1411, -1411, -1411,   135,   202,   489,   138,
    -921,  1229,  1230,  1231,  1232,   139,   511,  1295,  -921,   288,
     281,  -921,  -921,   512,   148,  1866,  1872,  1867,  -921,   149,
    1357,  1358,  -921,  1359,  -921,   150,   513,  -921,   164,  -921,
    1703,  2188,  1881,   165,  2223,   179,  2224,   166,  1843,   217,
    1020,  2290,  -921,  -921,  2291,   315,   316,  -921,  1818,   221,
     252,   514,   288,   515,   223,  1379,   780,  -921,   317,  -921,
     318,   516,  2220,   188,  -921,   220,  1869,  2192,  2193,  1091,
     225,  -212,   229,  1874,  2258,  2259,   288,   189,   190,   230,
    1878,   231,   245,  1612,  1846,    41,   259,  -921,   262,   263,
     268,  1846,   517,  2307,  1355,  1356,  1357,  1358,   269,  1359,
    -921,   278,  1718,  1355,  1356,  1357,  1358,   285,  1359,   191,
     289,  1721,  1355,  1356,  1357,  1358,   288,  1359,   984,   291,
    1726,   837,   296,   297,  2314,  1158,  1884,  -921,   298,   333,
    1158,  1355,  1356,  1357,  1358,   336,  1359,  1898,   334,  1892,
    1899,   518, -1410, -1410, -1410, -1410,   192,   193,   340,   194,
    1895,  1355,  1356,  1357,  1358,   343,  1359,   195,   345,  2094,
     319,   348,   349,  -921,  1945,  1946,  1947,  1948,   357,   381,
     382,   399,  -921,  -921,   402,   404,   411,   429,   412,   444,
     320,   449,  -350,   451,   454,   465,   467,   495,   499,  1684,
    1910,  1685,  -921,   985,  1686,   545,   537,  -921,   547,   549,
     196,   197,   553,   555,  1687,   576,   577,   579,   987,   582,
     183,   198,   592,   655,  1949,  -921,   657,   665,   672,   673,
    1952,  1380,   777,  -921,   586,   792,  -921,   801,   303,   808,
     821,   819,  -921,  -921,  -921,   827,   858,  -830,  -921,   859,
    -921,   902,  -921,  -921,  -921,   584,   933,   936,   939,   952,
     953,   958,   961,   955,   963,   967,   973,   976,  1007,   970,
     979,  1381,  1985,   980,  1028,  1217,  1036,  2039,  1053,  1120,
    1122,  1128,  1137,  1143,  1146,  1159,  2267,   847,  1180,  1162,
    2195,  1173,  1182,  1184,  1188,   199,  1189,  1190,  1197,  1202,
    1191,  1192,   988,  1193,  1194,  1195,  1204,  1207,  1215,  1209,
    1221,  1223,  1226,   418,  1233,  1245,  1249,  1264,  1267,  1265,
   -1413,  1991,  1274,  1284,  1278,  1280,  2219,  1997,  1279,  1289,
    1291,  1091,   158,  1313,  1316,  1320,  1322,  2079,  1323,  1345,
    1362,  1688,  2081,   989,  1366,  1689,  1383,  1396,  1403,  1417,
     990,  2086,  1476,  1012,   419,  2087,   991,  1418,  1690,   992,
    1499,   420,  1514,  1537,  1519,   446,  1552,  1556,  1570,  1578,
    1421,  1422,  1423,  1585,  1586,  1593,  1598,  1608,  1424,  1610,
    1614,  1679,  1359,  1680,  1703,  1683,  1386,  1732,  1715,  1734,
    1717,   993,  1720,  1725,  1727,   288,  1737,  1490,   985,  1755,
    1786,  1778,  1780,  1782,  1794,  1797,  1691,  1820,  1798,   200,
    1823,  1836,  1824,   987,  1851,  1835,  1425,  1837,  1859,  1870,
    1850,  1861,  1655,  1893,  1941,  1942,  1922,  1966,  1968,  1972,
    1974,  1979,   421,  1982,  1986,  2000,  1828,  2003,  2005,  2010,
     982,  2013,  2024,  2015,  1019,  2018,  2036,  2026,  2022,   201,
    1033,  2040,  2043,  1692,  2041,  1050,  1051,  2098,  2116,   994,
    2100,  1050,  1058,  1060,  2083,  2102,  2118,  2120,  1019,  2132,
    2123,  2137,  2157,  2138,  1050,  2159,  2139,  1693,  2166,  2185,
    2207,  2178,  2030,  1058,  1114,  2186,  1116,  2196,  2190,  2229,
    2052,  1071,  2197,  2231,  2233,   422,   288,   988,   202,  2254,
    2245,  1694,  2184,  2246,   995,   996,  1695,  2281,  2264,  2282,
    2294,  1426,  1427,  2198,  2295,  2200,  1696,  2297,  2239,  2312,
    1697,    15,    28,    74,   423,   186,   414,   261,   248,   997,
     258,   282,  1580,  1327,  1156,   779,   568,   494,   219,  1428,
    1613,  1609,  1130,  2238,  1330,  1429,   284,   998,  1989,  1072,
     789,   991,  2038,   146,   992,   999,   293,    67,   285,   233,
     443,   977,   383,   959,   424,  1181,   670,  1891,  1430,  2059,
     287,  1814,  1218,  1888,  1887,  2218,  1431,  1698,   972,   595,
    1432,  1140,  2284,  2202,   951,   163,   993,  1699,   558,  1932,
    1992,  1228,  2261,  1708,  1707,  1902,  1930,  1237,  1955,  1789,
    1213,  2241,  1521,  1517,  1962,  1536,  2122,  1548,  1273,   288,
    1433,  1434,  2283,  2207,  1981,  1435,  1799,  1825,  1993,  1607,
    1577,  2009,  1296,  1103,  1311,  1436,  1297,  1050,  1857,   288,
    2164,  1858,  1437,  1896,  2243,  1050,  1253,  1438,  2169,  2002,
    1757,  1288,  2180,  1478,  1841,  1160,   302,  2262,  2263,  1864,
    1420,  2266,   965,  1019,   994,  1439,   395,  1550,  2268,  1244,
     795,  2287,  1163,    76,  1736,   938,  2082,  1167,     0,  1294,
    2301,  2302,     0,     0,  2304,     0,  2305,  1050,     0,     0,
       0,  1050,     0,  2272,     0,     0,     0,     0,     0,  1312,
       0,     0,  1253,     0,     0,  2292,     0,     0,   985,   995,
     996,     0,  1016,   373,     0,     0,     0,     0,     0, -1578,
       0,  2311,     0,   987,     0,  1213,     0,     0,  1058,  1016,
       0,   446,     0,     0,   997,     0,  2303,     0,  1156,  1156,
    1156,     0,     0,     0, -1029,     0,     0,     0,  1156,     0,
       0,     0,   998,     0,     0,     0,     0, -1029,     0,     0,
     999,     0,   183,   285,  1294,     0,  2309,     0,     0,  1156,
       0,  1156,     0,  1156,     0,     0,     0,  1156,  1156,  1156,
    1156,  1156,  1156,  1156,  1156,     0,     0,     0,     0,     0,
     446,     0,     0,     0,     0,     0,   600,   601,   602,   603,
     604,   605,     0,     0,     0,     0,     0,   988,     0,     0,
    1440,  1441,  1442,  1443,  1444,     0,  1445,     0,  1446,  1447,
       0,  1448,  1449,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   607,     0,   608,   609,   610,   611,   612,   613,
       0,     0,     0,  1294,     0,     0,     0,     0,     0,   446,
       0,     0,     0,  1050,     0,     0,     0,     0,     0,  1017,
       0,   991,     0,     0,   992,     0,  1563,     0,     0,     0,
       0,     0,     0,  1213,   614,     0,     0,     0,     0,     0,
    1576,     0,     0,     0,     0,     0,     0,  1050,     0,     0,
       0,     0,     0,     0,     0,     0,   993,  -345,   597,  1592,
       0,     0,     0,     0,     0,  1294,     0,     0,     0,     0,
       0,  1600,     0,     0,     0,     0,     0,     0,   598,     0,
       0,     0,     0,     0,   837,     0,     0,     0,  1253,     0,
       0,   599,     0,     0,   600,   601,   602,   603,   604,   605,
     606,     0,     0,  1156,  1156,  1156,  1156,  1156,  1156,  1156,
       0,     0,     0,     0,     0,     0,   615,     0,     0,     0,
       0,     0,     0,     0,   994,  1294,     0,     0,     0,     0,
     607,     0,   608,   609,   610,   611,   612,   613,     0,     0,
       0,     0,     0,     0,     0,  1713,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   985,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1050,   618,   995,
     996,   987,   614,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -345,
       0,     0,     0,  -345,   997,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   620,     0,     0,     0,     0,
       0,     0,   998,     0,   622,     0,     0,     0,     0,     0,
     999, -1524,  -345,   285,     0,     0,     0,   623,     0,  1743,
    1744,     0,     0,     0,     0,     0,  -345,     0,     0,     0,
       0, -1524,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   615,   988,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   418,    41,     0,     0,
     616,     0,     0,     0,     0,     0, -1559,     0,     0,     0,
    -345,  -345,     0,   627,   628,   629,     0,     0,  -345,   617,
       0,     0,  -345,     0,     0,  1294,  1294,     0,     0,     0,
       0,  1050,  1050,     0,     0,     0,   618,   419,     0,   991,
       0,     0,   992,     0,   420,     0,     0,     0,     0,  1826,
       0,     0,     0,     0,     0,     0,     0,  1294,   619,     0,
       0,     0,   631,   632,   633,     0,     0,     0,   985,     0,
       0,     0,  1847,   620,   993,     0,     0,  1856,  1856,     0,
     621,     0,   622,   987,     0,     0,     0,     0,     0,  -345,
       0,     0,     0,  -345,     0,   623,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   624,     0,     0,  1019,     0,
       0,     0,   625,     0,  -345,   421,     0,     0,     0,  1882,
       0,  1883,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -345,     0,     0,  -345,     0,     0,     0,
       0,     0,   994,     0,     0,     0,     0,   985,     0,   626,
       0,   627,   628,   629,     0,     0,     0,     0,     0,     0,
       0,  1071,   987,  -615,   559,     0,  -655,   988,  -655,     0,
       0,     0,     0,  -655,     0,   630,     0,     0,   422,     0,
       0,  -655,     0,  1213,  1213,  1213,     0,   995,   996,     0,
       0,     0, -1559,  1156,     0,     0,     0,     0,  1156,     0,
     631,   632,   633,     0,     0,     0,     0,   423,     0,     0,
       0,  1050,   997,   634,  -655,  -655,   635,     0,     0,  1017,
       0,   991,  -655,     0,   992,  -345,     0,     0,     0,     0,
     998,     0,     0,  -655,     0,     0,  -345,  -655,   999,     0,
       0,   285,     0,     0,     0,     0,   988,   424,     0,  -655,
       0,     0,     0,     0,     0,     0,   993,   418,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1965,  -655,     0,     0,     0,     0,  1976,  1294,  -655,  -655,
       0,     0,     0,     0,     0,  1294,     0,     0,     0,     0,
       0,     0,     0,     0,  1050,  -615,     0,     0,   419,  -615,
     991,     0,  1563,   992,     0,   420,     0,     0,     0,  -655,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -655,     0,     0,   994,  -655,     0,     0,     0,  1976,
       0,     0,     0,  1294,     0,   993,     0,     0,  -655,     0,
       0,     0,  -615,     0,     0,  -655,     0,     0,  -655,  -655,
       0,     0,     0,  2077,     0,     0,  -655,  2077,     0,     0,
       0,     0,     0,  -655,     0,  -655,     0,     0,  -655,   995,
     996,     0,     0,     0,     0,     0,   421,  2077,  2077, -1578,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   997,     0,     0,     0,     0,     0,
       0,     0,     0,   994, -1029,  -655,     0,     0,     0,  -655,
       0,  -655,   998,     0,     0,     0,     0, -1029,  -655,     0,
     999,     0,   183,   285,     0,     0,     0,     0,  2077,     0,
       0,  2077,     0,     0,     0,     0,     0,     0,     0,   422,
    -655,     0,     0,     0,     0,     0,     0,     0,   995,   996,
       0,     0,     0,     0,     0,  -655,     0,     0,  1976,     0,
       0,   559,     0,  -655,     0,  -655,     0,     0,   423,  -615,
    -655,     0,     0,   997,     0,     0,  -655,     0,  -655,     0,
       0,     0,     0,     0,     0,  -655,     0,     0,     0,     0,
    1058,   998,     0,     0,     0,     0,     0,  2161,  -655,   999,
       0,     0,   285,  -655,     0,  -655,     0,     0,   424,     0,
       0,  -655,  -655,  -655,     0,     0,  2077,     0,     0,  -655,
       0,     0,     0,  -655,     0,     0,     0,     0,     0,     0,
    -655,     0,  -655,  2201,  -655,     0,     0,     0,     0,     0,
       0,  -655,     0,  -655,  -655,     0,  -655,  -655,     0,  -655,
       0,     0,     0,     0,  -655,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -655,  -655,
    2077,     0,   985,     0,  -655,  -655,  -655,     0,     0,  -655,
       0,     0,     0,   671,     0,     0,     0,   987,     0,     0,
    -655,     0,     0,     0,     0,     0,     0,     0,     0,   560,
       0,     0,  -655,     0,     0,     0,  -655,     0,     0,     0,
       0,     0,  -655,     0,     0,     0,     0,     0,  -655,     0,
       0,     0,  -655,     0,     0,     0,     0,     0,     0,  1253,
       0,     0,     0,     0,     0,  -655,     0,     0,     0,     0,
       0,     0,  -655,     0,  2251,  -655,  -655,  2253,     0,     0,
       0,     0,     0,  -655,     0,     0,     0,     0,     0,     0,
    -655,     0,  -655,     0,     0,  -655,     0,     0,     0,     0,
       0,   988,     0,     0,     0,     0,     0,  2270,     0,     0,
       0,     0,   418,     0,     0,     0,     0,     0,     0,     0,
       0,  2077,     0,     0,     0,     0,  2077,     0,     0,     0,
       0,     0,  -655,     0,     0,     0,  -655,     0,  -655,     0,
       0,     0,  1148,     0,     0,  -655,     0,     0,     0,   990,
    1058,     0,     0,   419,     0,   991,     0,     0,   992,     0,
     420,  2300, -1494,     0,     0, -1494,     0,  -655, -1494, -1494,
   -1494,     0,     0,  1238,     0,     0,     0, -1494,     0,     0,
       0,     0,  -655,     0,     0,     0,     0,     0,     0,     0,
     993,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -655,     0,  1253,     0,     0,     0,     0,
       0,     0,  -655,     0, -1494,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -655,     0,     0,     0,     0,
    -655,   421,  -655,     0,     0,     0,     0, -1494,     0,     0,
    -655,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -655,     0, -1494,     0,     0,     0,     0,     0,   994,  -655,
       0,     0,     0,     0,     0,     0,     0,     0,  -655,     0,
    -655,  -655,     0,     0,  -655,     0,  -655,     0,     0,     0,
     984,  -655,     0,   837,     0,     0,  1455,  1456,  1457,     0,
       0,     0,     0,     0,   422,     0,  -655,     0,     0,     0,
       0,  -655,     0,   995,   996,     0,  -655,     0,     0, -1494,
   -1494,     0,     0,     0,     0,     0,     0,  -655,     0,     0,
       0,     0,     0,   423,     0,     0,   560,     0,   997,  -655,
       0,     0,  1458,     0,     0,     0, -1494, -1494,     0,  -655,
       0,     0,     0, -1494,     0,     0,   998, -1494,     0,     0,
       0,     0,     0,     0,   999,   985,     0,   285,     0,     0,
       0,     0,     0,   424,  1149,  1150, -1494,     0,     0,     0,
     987,     0,  1672,  1151, -1494,     0,     0, -1494, -1494,     0,
       0,     0,     0,     0, -1494,     0,     0,     0, -1494,     0,
   -1494,     0,     0, -1494,     0, -1494,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0, -1494, -1494,
       0,     0,     0, -1494,     0,     0,     0,     0,     0,     0,
       0,     0,     0, -1494,     0, -1494,     0,  1426,  1427,     0,
   -1494,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0, -1494,   988,  1428,     0,     0,     0,     0,
       0,  1429,     0,     0,     0,   418, -1494,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1459,     0,     0,     0,     0,     0,
       0,     0,  1431, -1494,     0,   989,  1432,     0,     0,     0,
       0,     0,   990,     0,     0,     0,   419,     0,   991,     0,
       0,   992,     0,   420,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1460,  1461,     0, -1494,
       0,  1462,     0,     0,     0,     0,     0,     0, -1494, -1494,
       0,  1463,     0,   993,     0,     0,     0,     0,  1464,     0,
       0,     0,     0,     0,     0, -1494,     0,     0, -1494, -1494,
       0,     0,     0, -1494,     0,     0,     0,     0,     0,     0,
     674,  1465,   675,     0,     0,     0,     0,   676,     0,     0,
       0, -1494,     0,     0,   421,   677,     0,     0,     0, -1494,
       0,     0, -1494,     0,     0,     0,     0,     0, -1494, -1494,
   -1494,     0,     0,     0, -1494,     0, -1494,     0, -1494, -1494,
   -1494,   994,     0,     0,     0,     0,     0,     0,   678,   679,
       0,     0,     0,     0,     0,     0,   680,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   681,     0,     0,
       0,   682,     0,     0,     0,     0,     0,   422,     0,     0,
       0,     0,   674,   683,   675,     0,   995,   996,     0,   676,
       0,     0,     0,     0,     0,     0,     0,   677,     0,     0,
       0,     0,     0,     0,     0,   684,   423,     0,     0,     0,
       0,   997,   685,   686,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   998,
     678,   679,     0,     0,     0,     0,     0,   999,   680,     0,
     285,     0,     0,   687,     0,     0,   424,  1466,  1467,   681,
       0,     0,  1468,   682,  1446,   688,  1469,  1448,  1449,   689,
       0,     0,     0,     0,     0,   683,     0,  -787,     0,     0,
    -787,     0,   690,     0,     0,     0,     0,     0,     0,   691,
       0,     0,   692,   693,     0,     0,     0,   684,     0,     0,
     694,     0,     0,     0,   685,   686,     0,   695,     0,   696,
       0,     0,   697,     0,     0,     0,     0,     0,     0,     0,
     158,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   687,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   688,     0,   698,
       0,   689,  -787,   699,     0,   700, -1506,     0,     0,     0,
       0,     0,   701,     0,   690,     0,     0,  -787,     0,     0,
       0,   691,     0,     0,   692,   693,     0,     0,     0,     0,
       0,     0,   694,     0,   702,     0,     0,     0,     0,   695,
       0,   696,     0,     0,   697,     0,     0,     0,     0,   703,
       0,     0,     0,     0,   984,     0,     0,   837,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     704,     0,     0,     0,     0,     0,     0,     0,  1175,   705,
       0,   698,     0,     0,     0,   699,     0,   700,     0,     0,
       0,     0,   706,     0,   701,     0,     0,   707,     0,   708,
       0,  -787,     0,     0,     0,     0,     0,   709,     0,     0,
       0,     0,  -787, -1502,     0,     0,   702,   710,     0,     0,
       0,     0,     0,     0,     0,     0,   711,     0,     0,   985,
       0,   703,     0,     0,     0,   712,     0,   713,   714,     0,
       0,   715,  -787,   716,   987,     0,     0,     0,   717,  -787,
       0,     0,   704,  -787,     0,  -787,     0,     0,  -787,     0,
    -787,   705,   984,   718,     0,   837,     0,     0,   719,     0,
       0,     0,     0,   720,   706,     0,     0,     0,     0,   707,
       0,   708,     0,     0,   721,     0,     0,     0,     0,   709,
    -787,     0,     0,     0,     0,  -787,   722,     0,     0,   710,
       0,     0,     0,     0,     0,     0,   723,     0,   711,     0,
       0,     0,     0,     0,     0,     0,     0,   712,     0,   713,
     714,     0,     0,   715,     0,   716,   984,     0,   988,   837,
     717,  -787,     0,     0,     0,     0,     0,   985,     0,   418,
       0, -1506,     0,     0,     0,   718,     0,     0,     0,     0,
     719,     0,   987,     0,     0,   720,     0,     0,  -787,     0,
       0,     0,     0,     0,     0,     0,   721,     0,     0,   989,
       0,     0,     0,     0,     0,     0,   990, -1502,   722,     0,
     419,     0,   991,     0,     0,   992,     0,   420,  -787,     0,
     984,     0,     0,   837,  -787,     0,     0,     0,     0,     0,
       0,   985,  1581,  -787,  -787,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   987,   993,     0,     0,
       0,     0,     0,  -787,     0,     0,     0,     0,  -787,  1106,
       0,     0,     0,  -787,   984,     0,   988,   837,     0,     0,
       0,     0,     0,     0, -1502,     0,  -787,   418,     0,     0,
   -1506,     0,     0,     0,  -787,     0,     0,  -787,   421,     0,
       0,     0,     0,  -787,     0,   985,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   986,   989,     0,     0,
     987,     0,     0,     0,   990,   994,     0,     0,   419,     0,
     991,     0,     0,   992,     0,   420,     0,     0,     0,     0,
     988,     0,     0,     0,     0,     0,     0,     0,     0,   985,
       0,   418,     0,     0,     0,     0,     0,     0,     0,     0,
    1065,   422,     0,     0,   987,   993,  1310,     0,     0,     0,
     995,   996,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   989,     0,     0,     0,     0,     0,     0,   990,     0,
     423,     0,   419,     0,   991,   997,     0,   992,     0,   420,
       0,     0,     0,     0,   988,     0,   421,     0,     0,     0,
       0,     0,     0,   998,     0,   418,     0,     0,     0,     0,
       0,   999,     0,     0,   285,     0,     0,     0,     0,   993,
     424,     0,     0,   994,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   989,     0,     0,   988,     0,
     984,     0,   990,   837,     0,     0,   419,     0,   991,   418,
       0,   992,     0,   420,     0,     0,     0,     0,     0,   422,
     421,     0,     0,     0,     0,     0,     0,     0,   995,   996,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   989,
       0,     0,     0,   993,     0,  1582,   990,   994,   423,  1583,
     419,     0,   991,   997,     0,   992,     0,   420,     0,     0,
       0,     0,     0,     0,   984,     0,     0,   837,     0,     0,
       0,   998,     0,     0,     0,   985,     0,     0,     0,   999,
       0,     0,   285,   422,   421,     0,     0,   993,   424,     0,
     987,     0,   995,   996,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1106,     0,     0,     0,     0,     0,     0,
       0,   994,   423,     0,     0,     0,     0,   997,     0,     0,
       0,     0,   984,     0,     0,   837,     0,     0,   421,     0,
       0,     0,     0,     0,     0,   998,     0,     0,     0,   985,
       0,     0,     0,   999,     0,     0,   285,   422,     0,     0,
    1110,     0,   424,     0,   987,   994,   995,   996,     0,     0,
       0,     0,     0,     0,     0,     0,   984,     0,     0,   837,
       0,     0,     0,     0,   988,     0,   423,     0,     0,     0,
       0,   997,     0,     0,     0,   418,     0,     0,     0,     0,
       0,   422,     0,     0,     0,     0,     0,   985,     0,   998,
     995,   996,     0,     0,     0,     0,     0,   999,     0,     0,
     285,     0,   987,     0,     0,   989,   424,     0,     0,     0,
     423,     0,   990,     0,     0,   997,   419,     0,   991,     0,
       0,   992,     0,   420,     0,     0,     0,     0,   988,     0,
       0,   985,     0,   998,     0,     0,     0,     0,     0,   418,
       0,   999,     0,     0,   285,     0,   987,     0,     0,   984,
     424,     0,   837,   993,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   989,
       0,     0,     0,     0,     0,     0,   990,     0,     0,     0,
     419,     0,   991,     0,     0,   992,   988,   420,     0,     0,
       0,     0,     0,     0,   421,     0,     0,   418,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   993,     0,     0,
       0,   994,     0,     0,   985,     0,  1315,   989,     0,     0,
     988,     0,   984,     0,   990,   837,     0,     0,   419,   987,
     991,   418,     0,   992,     0,   420,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   422,   421,     0,
       0,     0,     0,     0,     0,     0,   995,   996,     0,     0,
       0,   989,     0,     0,     0,   993,   984,     0,   990,   837,
       0,     0,   419,     0,   991,   994,   423,   992,     0,   420,
       0,   997,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   985,     0,   998,
       0,     0,     0,     0,     0,     0,   421,   999,     0,   993,
     285,   422,   987,   988,     0,     0,   424,     0,     0,     0,
     995,   996,     0,     0,   418,     0,     0,     0,     0,     0,
       0,     0,     0,   994,     0,     0,     0,     0,     0,     0,
     423,   985,     0,     0,     0,   997,     0,     0,     0,     0,
     421,     0,     0,     0,   989,     0,   987,     0,     0,   984,
       0,   990,   837,   998,     0,   419,     0,   991,     0,   422,
     992,   999,   420,     0,   285,     0,     0,   994,   995,   996,
     424,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1199,     0,   988,     0,   423,     0,
       0,     0,   993,   997,     0,     0,     0,   418,     0,     0,
       0,     0,     0,   422,     0,     0,     0,     0,     0,     0,
       0,   998,   995,   996,     0,     0,     0,     0,     0,   999,
       0,     0,   285,     0,   985,     0,     0,   989,   424,     0,
     988,     0,   423,   421,   990,     0,     0,   997,   419,   987,
     991,   418,     0,   992,     0,   420,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   998,     0,     0,     0,     0,
     994,     0,     0,   999,     0,     0,   285,     0,     0,     0,
       0,   989,   424,     0,     0,   993,     0,     0,   990,     0,
       0,     0,   419,     0,   991,     0,     0,   992,     0,   420,
    1590,     0,     0,     0,     0,     0,   422,     0,     0,     0,
       0,     0,     0,     0,     0,   995,   996,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   421,     0,     0,   993,
       0,     0,     0,   988,     0,   423,     0,     0,     0,     0,
     997,     0,     0,     0,   418,     0,     0,     0,     0,     0,
       0,     0,     0,   994,     0,     0,     0,     0,   998,     0,
       0,     0,     0,     0,     0,     0,   999,     0,     0,   285,
     421,     0,     0,     0,   989,   424,     0,     0,     0,     0,
       0,   990,     0,     0,  1727,  1029,     0,   991,     0,   422,
     992,     0,   420,     0,     0,     0,     0,   994,   995,   996,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   423,     0,
       0,     0,   993,   997,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   422,     0,     0,     0,     0,     0,     0,
       0,   998,   995,   996,     0,     0,     0,     0,     0,   999,
       0,     0,   285,     0,     0,     0,     0,     0,   424,     0,
       0,     0,   423,   421,  1620,     0,  1621,   997,     0,  1622,
     600,   601,   602,   603,   604,   605,   606,  1623,  1624,  1625,
       0,     0,     0,     0,     0,   998,     0,     0,     0,     0,
     994,     0,     0,   999,     0,     0,   285,     0,  1626,     0,
       0,     0,   424,     0,     0,     0,   607,     0,   608,   609,
     610,   611,   612,   613,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   422,     0,     0,     0,
       0,     0,     0,     0,     0,   995,   996,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   614,     0,
       0,     0,     0,     0,     0,   423,     0,     0,     0,     0,
     997,     0,   600,   601,   602,   603,   604,   605,   606,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   998,     0,
       0,     0,     0,     0,     0,     0,   999,     0,  1627,   285,
    2044,  2045,     0,     0,     0,   424,     0,     0,   607,     0,
     608,   609,   610,   611,   612,   613,  1628,     0,     0,  1629,
    1630,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1631,     0,     0,     0,     0,     0,     0,
     615,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     614,     0,     0,     0,     0,     0,   616,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1632,     0,     0,     0,   985,     0,     0,     0,
       0,  1633,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   987,   618,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1634,     0,     0,     0,     0,     0,
       0,     0,     0,  2046,     0,     0,     0,     0,  1635,   620,
       0,     0,   615,     0,     0,     0,   621,     0,   622,     0,
     985,     0,     0,     0,     0,     0,     0,     0,   616,     0,
       0,   623,  1636,     0,     0,   987,     0,     0,     0,     0,
       0,     0,     0,     0,  2047,  2048,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   988,  1637,     0,     0,     0,
       0,  1638,     0,     0,   618,     0,   418,     0,     0,  2049,
       0,     0,     0,     0,     0,  1639,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   626,   619,   627,   628,   629,
       0,     0,     0,     0,     0,     0,  1148,     0,     0,     0,
       0,   620,     0,   990,     0,     0,     0,   419,   621,   991,
     622,     0,   992,  2050,   420,     0,     0,     0,     0,   988,
       0,  1640,     0,   623,     0,     0,     0,     0,     0,     0,
     418,     0,  1641,     0,     0,     0,   631,   632,   633,     0,
       0,     0,     0,     0,   993,     0,     0,     0,     0,   634,
       0,  1642,   635,     0,     0,     0,     0,     0,     0,     0,
    1148,     0,     0,     0,     0,     0,     0,   990,     0,     0,
       0,   419,  1643,   991,     0,     0,   992,   626,   420,   627,
     628,   629,     0,     0,     0,   421,  2051,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2052,     0,     0,     0,     0,     0,     0,     0,   993,     0,
       0,     0,   994,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  2053,     0,     0,     0,     0,   631,   632,
     633,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   634,     0,     0,   635,  2054,     0,     0,   422,   421,
       0,     0,     0,     0,     0,     0,     0,   995,   996,     0,
       0,     0,     0,     0,  2055,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   994,   423,     0,     0,
       0,     0,   997,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     998,     0,     0,     0,     0,     0,     0,     0,   999,     0,
       0,   285,   422,     0,     0,     0,     0,   424,  1149,  1150,
       0,   995,   996,     0,     0,     0,  1908,  1151,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   423,     0,     0,     0,     0,   997,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   998,     0,     0,     0,     0,     0,
       0,     0,   999,     0,     0,   285,     0,     0,     0,     0,
       0,   424,  1149,  1150,     0,     0,     0,     0,     0,     0,
       0,  1151
};

static const yytype_int16 yycheck[] =
{
      84,   169,   222,   131,   394,   393,   904,   545,   692,   512,
     839,   656,  1028,   658,   441,   868,   307,  1206,  1276,  1206,
     863,   189,   190,  1206,   246,   721,   194,   195,   196,   197,
     198,   874,   200,   624,   202,  1100,  1206,  1106,  1206,   865,
     999,  1090,   353,  1120,  1713,   596,  1239,   864,  1386,  1387,
     464,   271,  1021,  1344,   862,   275,   663,   277,   186,   882,
    1344,  1344,     9,   871,   872,  1344,   286,  1048,   236,   153,
     238,  1344,   895,   576,  1344,  1056,   222,   245,   886,   887,
      54,  1230,  1231,  1232,     9,   253,    13,    69,    17,    56,
     118,    23,   900,   901,     6,     6,    48,  1488,     6,   267,
     268,    49,   270,     6,     6,    21,    70,    17,   276,    56,
     332,  1176,     9,    49,   425,  1506,     0,   339,   955,   118,
    1280,  1102,    94,    28,   344,   271,  1175,    69,   111,   275,
      84,   277,    30,    56,   354,   168,    85,    85,     9,    56,
     286,   361,    62,   311,    23,    72,   314,   315,   219,   317,
      48,    91,   372,   264,    69,   984,    22,    49,    49,   274,
     989,    88,   210,  1554,   178,   333,   214,  1136,   390,     9,
      69,    72,   210,    49,   394,   397,   396,    65,  1847,    50,
    1170,   790,   350,   168,   495,  1262,   172,   832,   410,   183,
     437,  1199,    28,    30,  1002,   236,    69,   220,   344,   844,
     203,   146,    49,  1594,   270,  1254,   290,   112,   354,   274,
     118,   104,   434,     9,   119,   361,    56,   209,  1047,   232,
     183,    11,   444,  1031,   392,    37,  1808,  1862,  1236,     0,
     232,   871,   400,   363,     9,    60,   147,   457,   955,   884,
     120,  1139,    94,    22,   191,     9,   167,   115,   394,   232,
     664,  1320,   367,   184,   501,   806,   210,  1065,   314,  1267,
     316,   901,    87,    88,  1085,   168,   332,  1316,  1345,   261,
     223,   224,   219,   171,   496,  1098,   112,   115,   210,   210,
      40,    71,   412,   451,   164,   232,   123,   115,  1626,  1366,
     374,   513,   239,   377,  1632,   179,   119,   412,   110,  1107,
    1121,   342,   470,   471,  1112,   119,   372,  1315,   374,  1370,
     375,   457,  1149,  1150,  1151,  1284,  1377,  1298,   341,  1148,
     191,    69,  1159,  1384,   435,   547,  1519,  1376,   973,   551,
     170,   210,   500,   244,   405,   232,   556,   557,   324,  1730,
     232,   509,   344,  1180,   596,  1182,  1199,  1184,  1497,   343,
     221,  1188,  1189,  1190,  1191,  1192,  1193,  1194,  1195,   206,
     305,   232,   198,   310,   232,   974,   975,   535,   239,   976,
     275,   320,   320,   355,   542,  1365,  1219,   968,   969,   219,
     343,   247,  1377,  1236,   320,   210,   326,   515,   436,  1384,
     418,  1199,   244,  1975,   232,   191,  1978,   619,  1206,   316,
     336,  1244,   214,   436,   232,   625,   944,   575,   296,  1417,
    1479,   449,   580,   355,  1267,   583,   317,   585,   120,   418,
     588,   589,   306,   436,   592,   428,   373,  1235,  1236,   320,
    1495,  1248,  1149,  1150,  1151,   449,   232,  1418,   358,   310,
     355,  1264,  1159,   239,   320,   336,  1523,  1607,   300,   389,
     414,   436,   404,   436,   428,   402,   355,   232,   405,  1267,
     232,  1278,  1315,   288,   436,  1182,   634,   635,   247,   451,
     437,  1188,  1189,  1190,  1191,   398,   430,  1194,  1195,   345,
     429,   429,   355,   399,   244,   395,   398,   403,   955,   436,
     398,   436,   256,   429,  1302,   442,   449,  1546,  1306,  1307,
     401,  1309,   373,   432,   436,  2140,   404,  1315,  1325,   451,
     418,   436,   803,   449,   310,   436,  1907,  1354,  1355,  1356,
    1357,  1358,  1359,  1360,   436,   436,   837,   165,   436,  1578,
     435,   402,   435,   436,   436,   663,   451,   435,   429,   436,
     232,  1557,   435,   436,   436,  2127,   165,   359,   475,   313,
     442,   179,   451,   429,   806,   114,   183,   371,   449,   183,
      32,     9,  1171,   977,  1417,   405,   345,  1958,   436,  1960,
     790,   442,  1553,   793,   794,   232,   236,   373,   451,  1837,
     800,    65,  1873,   449,   436,   163,  1655,  1084,  1179,  1873,
    1873,  1142,  1785,   320,  1873,  1186,   256,  1988,   436,   295,
    1873,  2270,   136,  1873,  1850,  1520,   402,   355,   436,   311,
     194,  1526,   435,   436,   782,   232,   232,   183,   183,   136,
    1681,   435,   436,  1090,   449,   203,    89,    90,  2019,  2020,
      25,    62,   397,   211,   802,   857,   450,  1354,  1355,  1356,
    1357,  1358,  1359,  1360,   864,   241,   442,   793,   794,   367,
     113,   219,   236,  1572,   800,  1246,   865,   359,    12,   970,
    1477,    15,    16,   449,   436,   885,   449,   123,  1587,   889,
    1739,   891,   256,   893,   894,   884,   896,   147,   306,  1363,
     889,  1288,  1149,  1150,  1151,  1292,  1681,   452,   183,   161,
      69,   911,  1159,    31,   412,   443,   444,   445,   446,    30,
     448,   244,   429,   451,   924,   283,  2044,   927,  1175,   305,
     399,   349,   336,  1180,   403,  1182,   343,  1184,   283,  1186,
     940,  1188,  1189,  1190,  1191,  1192,  1193,  1194,  1195,  1552,
     349,   953,   127,  1979,    65,  1704,  1705,  1706,   958,   435,
     198,   300,  1426,   191,   436,   229,   955,   241,   117,  1798,
     442,  1732,   191,  1712,   974,   975,  1347,   353,  1717,  1718,
     241,   889,  1721,  1722,  1723,   264,  1725,  1726,   240,   107,
     336,   229,   306,   941,  1782,   435,  1784,  1585,   924,   436,
     191,   400,   403,  1860,   232,   869,  1283,  1254,    69,   306,
    1486,   239,   191,   232,   940,    27,  1945,  1946,  1947,  1948,
     239,  1392,   258,  1629,    33,  1854,   890,    36,   892,  1817,
     241,   305,   296,   897,   449,    44,    45,    46,   243,   436,
     436,   232,   906,  2012,   305,  2012,   289,   290,   239,  2012,
     153,  1900,  1901,   232,  1815,  2226,  2227,   405,  1753,  1754,
     239,  1849,  2012,  1527,  2012,   176,   160,   431,   343,  1316,
     236,   317,  1536,   449,   196,   398,   314,   232,   436,   353,
     232,   153,   310,   321,  1779,  1074,  1086,   330,   331,   294,
     256,   310,   353,  1788,   305,   363,    99,  1714,   254,  2024,
    1347,  2026,  1719,   295,  1953,  1954,  1878,  1354,  1355,  1356,
    1357,  1358,  1359,  1360,   232,   249,   250,   163,   229,   310,
       9,   359,   243,   173,   435,   196,  1898,  1899,   207,  1376,
     310,   310,   449,   267,   268,   315,   537,    28,   449,  1141,
     363,   420,   353,   299,   412,   373,   155,   358,  1056,  1782,
     272,  1784,   307,   232,   373,   401,   435,   203,  1022,  2197,
    1149,  1150,  1151,  1786,   173,   211,  1074,    56,   223,   224,
    1159,  1171,    11,   294,   402,   449,   279,  1949,   194,   195,
    1952,   190,   373,  1131,  1817,   296,    25,    26,   449,   412,
     284,  1180,  2037,  1182,   373,  1184,   355,  1186,   248,  1188,
    1189,  1190,  1191,  1192,  1193,  1194,  1195,   279,   436,   280,
    1581,   402,  1835,    82,   442,   236,  1849,  1714,    57,   232,
     236,   112,  1719,   442,   314,   436,  1921,   117,   228,   238,
     151,   244,  2028,   233,     8,   256,  1824,   283,   443,   444,
     256,  2166,   351,   435,   436,  1940,   104,     9,  1248,   449,
      12,   442,   449,    15,    16,    94,    95,  2295,    97,   302,
     176,    35,  1957,   442,   363,  2037,   105,   191,   363,   435,
     436,  1342,   990,   449,   191,   288,   285,   121,  1278,   369,
     370,   170,   199,   232,   443,   444,   445,   446,   209,   448,
     153,   154,   451,     1,   355,   295,     4,  1015,   319,  1546,
    1547,   218,   191,  1998,  1999,   254,  1214,   247,   232,   148,
     149,    19,  2007,   412,   172,   239,   232,   412,   181,  2091,
     159,    29,   443,   444,   187,  1325,   184,   223,   224,   338,
     219,  1578,     1,  2011,  2130,   449,  1336,  1337,   259,   348,
     261,   123,  1549,   232,  1932,   294,     8,   191,   265,   266,
     239,   449,   371,  1901,    62,   218,   273,   274,  1347,   222,
     351,  1225,   279,   280,  2292,  1354,  1355,  1356,  1357,  1358,
    1359,  1360,  1797,    35,   314,   117,   316,  1660,    47,  1287,
     380,  2309,   443,   444,   445,   446,   310,   448,   232,   410,
     451,     1,    61,   164,   233,   239,     6,   132,   166,     9,
     409,  2096,    12,    13,    14,  1953,  1954,   251,   164,  2104,
    1336,  1337,   306,   184,   435,   431,   893,   436,  1326,   435,
     305,   310,   236,   436,  2119,  1850,   449,   209,   184,   442,
      99,   450,   291,   292,   911,   236,   204,   236,   351,  2235,
    2212,   438,   256,  2052,   212,  2217,   305,   364,    58,   373,
      25,    26,  2147,   166,  2149,   256,  1180,   256,   503,   449,
    1184,  2156,  1926,   508,  1928,   351,   310,  1714,  1192,  1193,
     156,    81,  1719,   273,   160,   275,   258,  1477,   402,   261,
     235,  2176,  2177,  2116,   373,  2118,    96,   249,   250,   417,
     198,    66,   351,    68,   432,   164,   434,   436,   443,   444,
     445,   446,   430,   448,   336,   267,   268,   314,   347,   316,
     455,  1404,   436,   402,  1407,   184,   405,   449,   442,  1412,
       2,   229,   229,   230,     6,   100,   101,   102,   236,   373,
     449,  1814,   376,   377,   443,   444,   445,   446,   150,   448,
     152,   210,   451,   153,   154,   449,   215,   436,   387,  2137,
     449,  1798,   399,   442,  1979,  2250,   403,   159,   227,  1806,
     260,   163,   262,  2241,   443,   444,   445,   446,   449,   448,
     180,   181,   147,   281,   149,   354,   455,   187,   150,   287,
     152,   191,   157,   443,   444,   445,   446,   450,   448,   212,
     453,   454,   421,   422,   423,   424,   449,   436,   442,    71,
     210,   421,   422,   423,   424,   400,   314,  1854,   218,  1609,
     449,   221,   222,   321,   449,   314,  1618,   316,   228,   351,
     445,   446,   232,   448,   234,   231,   334,   237,   436,   239,
     265,   266,  1634,   449,  2098,   178,  2100,   449,  1586,   278,
    1629,  2229,   252,   253,  2232,   314,   315,   257,  1556,   275,
     358,   359,  1652,   361,   390,   230,   573,   267,   327,   269,
     329,   369,  2087,    11,   274,   449,  1614,   265,   266,   244,
      24,   379,   449,  1621,   229,   230,  1676,    25,    26,   351,
    1628,   327,   367,  1609,  1592,   210,   449,   297,   104,   436,
     379,  1599,   400,  2281,   443,   444,   445,   446,   362,   448,
     310,    56,   451,   443,   444,   445,   446,   436,   448,    57,
      84,   451,   443,   444,   445,   446,  1716,   448,     6,   172,
     451,     9,   449,   351,  2312,  1714,  1652,   337,   346,   367,
    1719,   443,   444,   445,   446,   106,   448,  1685,   278,   451,
    1688,   449,   421,   422,   423,   424,    94,    95,   232,    97,
    1676,   443,   444,   445,   446,   358,   448,   105,   207,   451,
     429,   449,   245,   373,  1758,  1759,  1760,  1761,    67,   449,
     351,   245,   382,   383,    23,   272,   436,   232,   449,   296,
     449,   449,    83,    83,   436,   430,   436,   395,   379,    31,
    1716,    33,   402,    81,    36,   429,   312,   407,   398,   230,
     148,   149,   196,   436,    46,   314,   398,   359,    96,    55,
     435,   159,   379,    27,  1762,   425,   184,   367,   449,   351,
    1768,   396,   449,   433,   214,   359,   436,   436,   223,   221,
     341,   432,   442,   443,   444,   210,   106,   400,   448,   232,
     450,   301,   452,   453,   454,    37,   376,   282,   276,   442,
     398,   395,    27,   452,   357,   272,   395,   171,   436,   456,
     449,   436,  1810,   449,   400,   153,   232,  1869,   133,   104,
      17,   435,   169,   184,   397,   452,  2194,    30,   452,   232,
    2048,   124,   452,   452,   452,   233,   452,   452,   125,   201,
     452,   452,   180,   452,   452,   452,    56,   398,   127,   428,
     343,   314,   129,   191,   130,    98,   394,   398,    49,   134,
     397,  1819,   135,   176,   395,   392,  2086,  1825,   397,   140,
     430,   244,    49,   143,   176,   109,   328,  1875,   375,   111,
     360,   173,  1880,   221,   111,   177,   435,   398,   436,   183,
     228,  1889,   304,   232,   232,  1893,   234,   336,   190,   237,
     160,   239,   131,   168,   432,  1819,   398,   361,   206,   398,
      12,    13,    14,    49,   214,   176,   206,   119,    20,   275,
     189,   441,   448,   440,   265,   214,   229,   336,   451,   393,
     451,   269,   451,   451,   368,  1985,   398,   261,    81,   128,
     395,   264,   260,   183,   326,   398,   238,   135,    49,   347,
       8,   123,   176,    96,     9,   432,    58,   432,   302,   170,
     398,   303,   198,   399,   324,   339,   263,   122,   429,   107,
     429,    49,   310,   172,   280,   138,   258,   139,   236,   257,
     861,   141,   110,   284,   865,   295,     7,   389,   279,   387,
     871,   113,    66,   285,   216,   876,   877,   153,   323,   337,
     153,   882,   883,   884,   436,   126,   323,   133,   889,  1985,
      99,    49,   142,   236,   895,   262,   214,   309,    93,    90,
    2072,   145,   259,   904,   905,   217,   907,   188,   199,    49,
     385,   174,   432,   401,   302,   373,  2086,   180,   436,   144,
     236,   333,  2040,   236,   382,   383,   338,   176,   171,   288,
     302,   153,   154,  2051,   417,  2053,   348,   137,   339,    49,
     352,     6,    22,    54,   402,   131,   338,   186,   171,   407,
     181,   204,  1299,  1122,   955,   570,   491,   425,   135,   181,
    1337,  1330,   930,  2133,  1123,   187,   220,   425,  1818,   232,
     581,   234,  1865,   109,   237,   433,   227,    49,   436,   153,
     374,   856,   302,   831,   442,   986,   557,  1661,   210,  1873,
    2086,  1551,   450,  1659,  1657,  2084,   218,   409,   844,   539,
     222,   943,  2205,  2067,   806,   123,   269,   419,   473,  1741,
    1822,  1031,  2184,  1389,  1388,  1700,  1739,  1036,  1775,  1519,
    1021,  2139,  1244,  1241,  1785,  1251,  1969,  1257,  1074,  2199,
     252,   253,  2204,  2205,  1806,   257,  1544,  1568,  1823,  1326,
    1292,  1839,  1096,   896,  1107,   267,  1098,  1048,  1599,  2219,
    2022,  1599,   274,  1678,  2140,  1056,  1057,   279,  2027,  1830,
    1493,  1086,  2033,  1208,  1581,   956,   234,  2185,  2186,  1609,
    1204,  2189,   836,  1074,   337,   297,   313,  1262,  2196,  1039,
     590,  2221,   963,    57,  1432,   797,  1881,   971,    -1,  1090,
    2262,  2263,    -1,    -1,  2266,    -1,  2268,  1098,    -1,    -1,
      -1,  1102,    -1,  2199,    -1,    -1,    -1,    -1,    -1,  1110,
      -1,    -1,  1113,    -1,    -1,  2233,    -1,    -1,    81,   382,
     383,    -1,  2292,  2219,    -1,    -1,    -1,    -1,    -1,   392,
      -1,  2303,    -1,    96,    -1,  1136,    -1,    -1,  1139,  2309,
      -1,  2175,    -1,    -1,   407,    -1,  2264,    -1,  1149,  1150,
    1151,    -1,    -1,    -1,   417,    -1,    -1,    -1,  1159,    -1,
      -1,    -1,   425,    -1,    -1,    -1,    -1,   430,    -1,    -1,
     433,    -1,   435,   436,  1175,    -1,  2294,    -1,    -1,  1180,
      -1,  1182,    -1,  1184,    -1,    -1,    -1,  1188,  1189,  1190,
    1191,  1192,  1193,  1194,  1195,    -1,    -1,    -1,    -1,    -1,
    2234,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,   180,    -1,    -1,
     442,   443,   444,   445,   446,    -1,   448,    -1,   450,   451,
      -1,   453,   454,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    -1,    75,    76,    77,    78,    79,    80,
      -1,    -1,    -1,  1254,    -1,    -1,    -1,    -1,    -1,  2293,
      -1,    -1,    -1,  1264,    -1,    -1,    -1,    -1,    -1,   232,
      -1,   234,    -1,    -1,   237,    -1,  1277,    -1,    -1,    -1,
      -1,    -1,    -1,  1284,   115,    -1,    -1,    -1,    -1,    -1,
    1291,    -1,    -1,    -1,    -1,    -1,    -1,  1298,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   269,     0,     1,  1310,
      -1,    -1,    -1,    -1,    -1,  1316,    -1,    -1,    -1,    -1,
      -1,  1322,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      -1,    -1,    -1,    -1,     9,    -1,    -1,    -1,  1339,    -1,
      -1,    34,    -1,    -1,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,  1354,  1355,  1356,  1357,  1358,  1359,  1360,
      -1,    -1,    -1,    -1,    -1,    -1,   197,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   337,  1376,    -1,    -1,    -1,    -1,
      73,    -1,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1396,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1418,   249,   382,
     383,    96,   115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   132,
      -1,    -1,    -1,   136,   407,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   286,    -1,    -1,    -1,    -1,
      -1,    -1,   425,    -1,   295,    -1,    -1,    -1,    -1,    -1,
     433,   164,   165,   436,    -1,    -1,    -1,   308,    -1,  1480,
    1481,    -1,    -1,    -1,    -1,    -1,   179,    -1,    -1,    -1,
      -1,   184,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   197,   180,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   191,   210,    -1,    -1,
     213,    -1,    -1,    -1,    -1,    -1,   219,    -1,    -1,    -1,
     223,   224,    -1,   364,   365,   366,    -1,    -1,   231,   232,
      -1,    -1,   235,    -1,    -1,  1546,  1547,    -1,    -1,    -1,
      -1,  1552,  1553,    -1,    -1,    -1,   249,   232,    -1,   234,
      -1,    -1,   237,    -1,   239,    -1,    -1,    -1,    -1,  1570,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1578,   271,    -1,
      -1,    -1,   413,   414,   415,    -1,    -1,    -1,    81,    -1,
      -1,    -1,  1593,   286,   269,    -1,    -1,  1598,  1599,    -1,
     293,    -1,   295,    96,    -1,    -1,    -1,    -1,    -1,   302,
      -1,    -1,    -1,   306,    -1,   308,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   318,    -1,    -1,  1629,    -1,
      -1,    -1,   325,    -1,   327,   310,    -1,    -1,    -1,  1640,
      -1,  1642,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   346,    -1,    -1,   349,    -1,    -1,    -1,
      -1,    -1,   337,    -1,    -1,    -1,    -1,    81,    -1,   362,
      -1,   364,   365,   366,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   174,    96,     0,     1,    -1,     3,   180,     5,    -1,
      -1,    -1,    -1,    10,    -1,   388,    -1,    -1,   373,    -1,
      -1,    18,    -1,  1704,  1705,  1706,    -1,   382,   383,    -1,
      -1,    -1,   405,  1714,    -1,    -1,    -1,    -1,  1719,    -1,
     413,   414,   415,    -1,    -1,    -1,    -1,   402,    -1,    -1,
      -1,  1732,   407,   426,    51,    52,   429,    -1,    -1,   232,
      -1,   234,    59,    -1,   237,   438,    -1,    -1,    -1,    -1,
     425,    -1,    -1,    70,    -1,    -1,   449,    74,   433,    -1,
      -1,   436,    -1,    -1,    -1,    -1,   180,   442,    -1,    86,
      -1,    -1,    -1,    -1,    -1,    -1,   269,   191,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1791,   108,    -1,    -1,    -1,    -1,  1797,  1798,   115,   116,
      -1,    -1,    -1,    -1,    -1,  1806,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1815,   132,    -1,    -1,   232,   136,
     234,    -1,  1823,   237,    -1,   239,    -1,    -1,    -1,   146,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   158,    -1,    -1,   337,   162,    -1,    -1,    -1,  1850,
      -1,    -1,    -1,  1854,    -1,   269,    -1,    -1,   175,    -1,
      -1,    -1,   179,    -1,    -1,   182,    -1,    -1,   185,   186,
      -1,    -1,    -1,  1874,    -1,    -1,   193,  1878,    -1,    -1,
      -1,    -1,    -1,   200,    -1,   202,    -1,    -1,   205,   382,
     383,    -1,    -1,    -1,    -1,    -1,   310,  1898,  1899,   392,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   407,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   337,   417,   242,    -1,    -1,    -1,   246,
      -1,   248,   425,    -1,    -1,    -1,    -1,   430,   255,    -1,
     433,    -1,   435,   436,    -1,    -1,    -1,    -1,  1949,    -1,
      -1,  1952,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   373,
     277,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   382,   383,
      -1,    -1,    -1,    -1,    -1,   292,    -1,    -1,  1979,    -1,
      -1,     1,    -1,     3,    -1,     5,    -1,    -1,   402,   306,
      10,    -1,    -1,   407,    -1,    -1,   313,    -1,    18,    -1,
      -1,    -1,    -1,    -1,    -1,   322,    -1,    -1,    -1,    -1,
    2011,   425,    -1,    -1,    -1,    -1,    -1,  2018,   335,   433,
      -1,    -1,   436,   340,    -1,   342,    -1,    -1,   442,    -1,
      -1,    51,    52,   350,    -1,    -1,  2037,    -1,    -1,    59,
      -1,    -1,    -1,   360,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,   369,  2054,    74,    -1,    -1,    -1,    -1,    -1,
      -1,   378,    -1,   380,   381,    -1,    86,   384,    -1,   386,
      -1,    -1,    -1,    -1,   391,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,   406,
    2091,    -1,    81,    -1,   411,   115,   116,    -1,    -1,   416,
      -1,    -1,    -1,   123,    -1,    -1,    -1,    96,    -1,    -1,
     427,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   436,
      -1,    -1,   439,    -1,    -1,    -1,   146,    -1,    -1,    -1,
      -1,    -1,   449,    -1,    -1,    -1,    -1,    -1,   158,    -1,
      -1,    -1,   162,    -1,    -1,    -1,    -1,    -1,    -1,  2150,
      -1,    -1,    -1,    -1,    -1,   175,    -1,    -1,    -1,    -1,
      -1,    -1,   182,    -1,  2165,   185,   186,  2168,    -1,    -1,
      -1,    -1,    -1,   193,    -1,    -1,    -1,    -1,    -1,    -1,
     200,    -1,   202,    -1,    -1,   205,    -1,    -1,    -1,    -1,
      -1,   180,    -1,    -1,    -1,    -1,    -1,  2198,    -1,    -1,
      -1,    -1,   191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  2212,    -1,    -1,    -1,    -1,  2217,    -1,    -1,    -1,
      -1,    -1,   242,    -1,    -1,    -1,   246,    -1,   248,    -1,
      -1,    -1,   221,    -1,    -1,   255,    -1,    -1,    -1,   228,
    2241,    -1,    -1,   232,    -1,   234,    -1,    -1,   237,    -1,
     239,  2252,     6,    -1,    -1,     9,    -1,   277,    12,    13,
      14,    -1,    -1,    17,    -1,    -1,    -1,    21,    -1,    -1,
      -1,    -1,   292,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     269,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   313,    -1,  2296,    -1,    -1,    -1,    -1,
      -1,    -1,   322,    -1,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   335,    -1,    -1,    -1,    -1,
     340,   310,   342,    -1,    -1,    -1,    -1,    81,    -1,    -1,
     350,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     360,    -1,    96,    -1,    -1,    -1,    -1,    -1,   337,   369,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   378,    -1,
     380,   381,    -1,    -1,   384,    -1,   386,    -1,    -1,    -1,
       6,   391,    -1,     9,    -1,    -1,    12,    13,    14,    -1,
      -1,    -1,    -1,    -1,   373,    -1,   406,    -1,    -1,    -1,
      -1,   411,    -1,   382,   383,    -1,   416,    -1,    -1,   153,
     154,    -1,    -1,    -1,    -1,    -1,    -1,   427,    -1,    -1,
      -1,    -1,    -1,   402,    -1,    -1,   436,    -1,   407,   439,
      -1,    -1,    58,    -1,    -1,    -1,   180,   181,    -1,   449,
      -1,    -1,    -1,   187,    -1,    -1,   425,   191,    -1,    -1,
      -1,    -1,    -1,    -1,   433,    81,    -1,   436,    -1,    -1,
      -1,    -1,    -1,   442,   443,   444,   210,    -1,    -1,    -1,
      96,    -1,   451,   452,   218,    -1,    -1,   221,   222,    -1,
      -1,    -1,    -1,    -1,   228,    -1,    -1,    -1,   232,    -1,
     234,    -1,    -1,   237,    -1,   239,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   252,   253,
      -1,    -1,    -1,   257,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   267,    -1,   269,    -1,   153,   154,    -1,
     274,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   297,   180,   181,    -1,    -1,    -1,    -1,
      -1,   187,    -1,    -1,    -1,   191,   310,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   210,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   218,   337,    -1,   221,   222,    -1,    -1,    -1,
      -1,    -1,   228,    -1,    -1,    -1,   232,    -1,   234,    -1,
      -1,   237,    -1,   239,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   252,   253,    -1,   373,
      -1,   257,    -1,    -1,    -1,    -1,    -1,    -1,   382,   383,
      -1,   267,    -1,   269,    -1,    -1,    -1,    -1,   274,    -1,
      -1,    -1,    -1,    -1,    -1,   399,    -1,    -1,   402,   403,
      -1,    -1,    -1,   407,    -1,    -1,    -1,    -1,    -1,    -1,
       3,   297,     5,    -1,    -1,    -1,    -1,    10,    -1,    -1,
      -1,   425,    -1,    -1,   310,    18,    -1,    -1,    -1,   433,
      -1,    -1,   436,    -1,    -1,    -1,    -1,    -1,   442,   443,
     444,    -1,    -1,    -1,   448,    -1,   450,    -1,   452,   453,
     454,   337,    -1,    -1,    -1,    -1,    -1,    -1,    51,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,
      -1,    74,    -1,    -1,    -1,    -1,    -1,   373,    -1,    -1,
      -1,    -1,     3,    86,     5,    -1,   382,   383,    -1,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   108,   402,    -1,    -1,    -1,
      -1,   407,   115,   116,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   425,
      51,    52,    -1,    -1,    -1,    -1,    -1,   433,    59,    -1,
     436,    -1,    -1,   146,    -1,    -1,   442,   443,   444,    70,
      -1,    -1,   448,    74,   450,   158,   452,   453,   454,   162,
      -1,    -1,    -1,    -1,    -1,    86,    -1,     6,    -1,    -1,
       9,    -1,   175,    -1,    -1,    -1,    -1,    -1,    -1,   182,
      -1,    -1,   185,   186,    -1,    -1,    -1,   108,    -1,    -1,
     193,    -1,    -1,    -1,   115,   116,    -1,   200,    -1,   202,
      -1,    -1,   205,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   146,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   158,    -1,   242,
      -1,   162,    81,   246,    -1,   248,    85,    -1,    -1,    -1,
      -1,    -1,   255,    -1,   175,    -1,    -1,    96,    -1,    -1,
      -1,   182,    -1,    -1,   185,   186,    -1,    -1,    -1,    -1,
      -1,    -1,   193,    -1,   277,    -1,    -1,    -1,    -1,   200,
      -1,   202,    -1,    -1,   205,    -1,    -1,    -1,    -1,   292,
      -1,    -1,    -1,    -1,     6,    -1,    -1,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     313,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,   322,
      -1,   242,    -1,    -1,    -1,   246,    -1,   248,    -1,    -1,
      -1,    -1,   335,    -1,   255,    -1,    -1,   340,    -1,   342,
      -1,   180,    -1,    -1,    -1,    -1,    -1,   350,    -1,    -1,
      -1,    -1,   191,    65,    -1,    -1,   277,   360,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   369,    -1,    -1,    81,
      -1,   292,    -1,    -1,    -1,   378,    -1,   380,   381,    -1,
      -1,   384,   221,   386,    96,    -1,    -1,    -1,   391,   228,
      -1,    -1,   313,   232,    -1,   234,    -1,    -1,   237,    -1,
     239,   322,     6,   406,    -1,     9,    -1,    -1,   411,    -1,
      -1,    -1,    -1,   416,   335,    -1,    -1,    -1,    -1,   340,
      -1,   342,    -1,    -1,   427,    -1,    -1,    -1,    -1,   350,
     269,    -1,    -1,    -1,    -1,   274,   439,    -1,    -1,   360,
      -1,    -1,    -1,    -1,    -1,    -1,   449,    -1,   369,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   378,    -1,   380,
     381,    -1,    -1,   384,    -1,   386,     6,    -1,   180,     9,
     391,   310,    -1,    -1,    -1,    -1,    -1,    81,    -1,   191,
      -1,   320,    -1,    -1,    -1,   406,    -1,    -1,    -1,    -1,
     411,    -1,    96,    -1,    -1,   416,    -1,    -1,   337,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   427,    -1,    -1,   221,
      -1,    -1,    -1,    -1,    -1,    -1,   228,   229,   439,    -1,
     232,    -1,   234,    -1,    -1,   237,    -1,   239,   367,    -1,
       6,    -1,    -1,     9,   373,    -1,    -1,    -1,    -1,    -1,
      -1,    81,   146,   382,   383,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    96,   269,    -1,    -1,
      -1,    -1,    -1,   402,    -1,    -1,    -1,    -1,   407,   109,
      -1,    -1,    -1,   412,     6,    -1,   180,     9,    -1,    -1,
      -1,    -1,    -1,    -1,   296,    -1,   425,   191,    -1,    -1,
     429,    -1,    -1,    -1,   433,    -1,    -1,   436,   310,    -1,
      -1,    -1,    -1,   442,    -1,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    92,   221,    -1,    -1,
      96,    -1,    -1,    -1,   228,   337,    -1,    -1,   232,    -1,
     234,    -1,    -1,   237,    -1,   239,    -1,    -1,    -1,    -1,
     180,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      -1,   191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      92,   373,    -1,    -1,    96,   269,   206,    -1,    -1,    -1,
     382,   383,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   221,    -1,    -1,    -1,    -1,    -1,    -1,   228,    -1,
     402,    -1,   232,    -1,   234,   407,    -1,   237,    -1,   239,
      -1,    -1,    -1,    -1,   180,    -1,   310,    -1,    -1,    -1,
      -1,    -1,    -1,   425,    -1,   191,    -1,    -1,    -1,    -1,
      -1,   433,    -1,    -1,   436,    -1,    -1,    -1,    -1,   269,
     442,    -1,    -1,   337,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   221,    -1,    -1,   180,    -1,
       6,    -1,   228,     9,    -1,    -1,   232,    -1,   234,   191,
      -1,   237,    -1,   239,    -1,    -1,    -1,    -1,    -1,   373,
     310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   382,   383,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   221,
      -1,    -1,    -1,   269,    -1,   399,   228,   337,   402,   403,
     232,    -1,   234,   407,    -1,   237,    -1,   239,    -1,    -1,
      -1,    -1,    -1,    -1,     6,    -1,    -1,     9,    -1,    -1,
      -1,   425,    -1,    -1,    -1,    81,    -1,    -1,    -1,   433,
      -1,    -1,   436,   373,   310,    -1,    -1,   269,   442,    -1,
      96,    -1,   382,   383,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   337,   402,    -1,    -1,    -1,    -1,   407,    -1,    -1,
      -1,    -1,     6,    -1,    -1,     9,    -1,    -1,   310,    -1,
      -1,    -1,    -1,    -1,    -1,   425,    -1,    -1,    -1,    81,
      -1,    -1,    -1,   433,    -1,    -1,   436,   373,    -1,    -1,
      92,    -1,   442,    -1,    96,   337,   382,   383,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     6,    -1,    -1,     9,
      -1,    -1,    -1,    -1,   180,    -1,   402,    -1,    -1,    -1,
      -1,   407,    -1,    -1,    -1,   191,    -1,    -1,    -1,    -1,
      -1,   373,    -1,    -1,    -1,    -1,    -1,    81,    -1,   425,
     382,   383,    -1,    -1,    -1,    -1,    -1,   433,    -1,    -1,
     436,    -1,    96,    -1,    -1,   221,   442,    -1,    -1,    -1,
     402,    -1,   228,    -1,    -1,   407,   232,    -1,   234,    -1,
      -1,   237,    -1,   239,    -1,    -1,    -1,    -1,   180,    -1,
      -1,    81,    -1,   425,    -1,    -1,    -1,    -1,    -1,   191,
      -1,   433,    -1,    -1,   436,    -1,    96,    -1,    -1,     6,
     442,    -1,     9,   269,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   221,
      -1,    -1,    -1,    -1,    -1,    -1,   228,    -1,    -1,    -1,
     232,    -1,   234,    -1,    -1,   237,   180,   239,    -1,    -1,
      -1,    -1,    -1,    -1,   310,    -1,    -1,   191,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   269,    -1,    -1,
      -1,   337,    -1,    -1,    81,    -1,   176,   221,    -1,    -1,
     180,    -1,     6,    -1,   228,     9,    -1,    -1,   232,    96,
     234,   191,    -1,   237,    -1,   239,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   373,   310,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   382,   383,    -1,    -1,
      -1,   221,    -1,    -1,    -1,   269,     6,    -1,   228,     9,
      -1,    -1,   232,    -1,   234,   337,   402,   237,    -1,   239,
      -1,   407,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,   425,
      -1,    -1,    -1,    -1,    -1,    -1,   310,   433,    -1,   269,
     436,   373,    96,   180,    -1,    -1,   442,    -1,    -1,    -1,
     382,   383,    -1,    -1,   191,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   337,    -1,    -1,    -1,    -1,    -1,    -1,
     402,    81,    -1,    -1,    -1,   407,    -1,    -1,    -1,    -1,
     310,    -1,    -1,    -1,   221,    -1,    96,    -1,    -1,     6,
      -1,   228,     9,   425,    -1,   232,    -1,   234,    -1,   373,
     237,   433,   239,    -1,   436,    -1,    -1,   337,   382,   383,
     442,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   398,    -1,   180,    -1,   402,    -1,
      -1,    -1,   269,   407,    -1,    -1,    -1,   191,    -1,    -1,
      -1,    -1,    -1,   373,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   425,   382,   383,    -1,    -1,    -1,    -1,    -1,   433,
      -1,    -1,   436,    -1,    81,    -1,    -1,   221,   442,    -1,
     180,    -1,   402,   310,   228,    -1,    -1,   407,   232,    96,
     234,   191,    -1,   237,    -1,   239,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   425,    -1,    -1,    -1,    -1,
     337,    -1,    -1,   433,    -1,    -1,   436,    -1,    -1,    -1,
      -1,   221,   442,    -1,    -1,   269,    -1,    -1,   228,    -1,
      -1,    -1,   232,    -1,   234,    -1,    -1,   237,    -1,   239,
     367,    -1,    -1,    -1,    -1,    -1,   373,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   382,   383,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,   269,
      -1,    -1,    -1,   180,    -1,   402,    -1,    -1,    -1,    -1,
     407,    -1,    -1,    -1,   191,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   337,    -1,    -1,    -1,    -1,   425,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   433,    -1,    -1,   436,
     310,    -1,    -1,    -1,   221,   442,    -1,    -1,    -1,    -1,
      -1,   228,    -1,    -1,   368,   232,    -1,   234,    -1,   373,
     237,    -1,   239,    -1,    -1,    -1,    -1,   337,   382,   383,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   402,    -1,
      -1,    -1,   269,   407,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   373,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   425,   382,   383,    -1,    -1,    -1,    -1,    -1,   433,
      -1,    -1,   436,    -1,    -1,    -1,    -1,    -1,   442,    -1,
      -1,    -1,   402,   310,    31,    -1,    33,   407,    -1,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,   425,    -1,    -1,    -1,    -1,
     337,    -1,    -1,   433,    -1,    -1,   436,    -1,    65,    -1,
      -1,    -1,   442,    -1,    -1,    -1,    73,    -1,    75,    76,
      77,    78,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   373,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   382,   383,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   115,    -1,
      -1,    -1,    -1,    -1,    -1,   402,    -1,    -1,    -1,    -1,
     407,    -1,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   425,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   433,    -1,   155,   436,
      65,    66,    -1,    -1,    -1,   442,    -1,    -1,    73,    -1,
      75,    76,    77,    78,    79,    80,   173,    -1,    -1,   176,
     177,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   190,    -1,    -1,    -1,    -1,    -1,    -1,
     197,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     115,    -1,    -1,    -1,    -1,    -1,   213,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   229,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      -1,   238,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    96,   249,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   271,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   188,    -1,    -1,    -1,    -1,   285,   286,
      -1,    -1,   197,    -1,    -1,    -1,   293,    -1,   295,    -1,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   213,    -1,
      -1,   308,   309,    -1,    -1,    96,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   229,   230,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   180,   333,    -1,    -1,    -1,
      -1,   338,    -1,    -1,   249,    -1,   191,    -1,    -1,   254,
      -1,    -1,    -1,    -1,    -1,   352,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   362,   271,   364,   365,   366,
      -1,    -1,    -1,    -1,    -1,    -1,   221,    -1,    -1,    -1,
      -1,   286,    -1,   228,    -1,    -1,    -1,   232,   293,   234,
     295,    -1,   237,   298,   239,    -1,    -1,    -1,    -1,   180,
      -1,   398,    -1,   308,    -1,    -1,    -1,    -1,    -1,    -1,
     191,    -1,   409,    -1,    -1,    -1,   413,   414,   415,    -1,
      -1,    -1,    -1,    -1,   269,    -1,    -1,    -1,    -1,   426,
      -1,   428,   429,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     221,    -1,    -1,    -1,    -1,    -1,    -1,   228,    -1,    -1,
      -1,   232,   449,   234,    -1,    -1,   237,   362,   239,   364,
     365,   366,    -1,    -1,    -1,   310,   371,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     385,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   269,    -1,
      -1,    -1,   337,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   408,    -1,    -1,    -1,    -1,   413,   414,
     415,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   426,    -1,    -1,   429,   430,    -1,    -1,   373,   310,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   382,   383,    -1,
      -1,    -1,    -1,    -1,   449,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   337,   402,    -1,    -1,
      -1,    -1,   407,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     425,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   433,    -1,
      -1,   436,   373,    -1,    -1,    -1,    -1,   442,   443,   444,
      -1,   382,   383,    -1,    -1,    -1,   451,   452,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   402,    -1,    -1,    -1,    -1,   407,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   425,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   433,    -1,    -1,   436,    -1,    -1,    -1,    -1,
      -1,   442,   443,   444,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   452
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   458,   459,     0,   179,   306,   460,   461,   462,   468,
     475,   477,   449,   449,     0,   461,   147,   483,   483,   232,
     307,   478,   478,   117,   463,   469,    27,   479,   479,   449,
      99,   585,   585,   232,   449,   476,    82,   484,   117,   464,
     470,   210,   480,  1137,   351,   166,   204,   212,   538,   449,
     302,   727,   727,   449,    72,   317,   401,   481,   482,   449,
     449,   351,   449,   165,   349,   400,   586,   592,   117,   465,
     471,   475,   132,   474,   482,   305,  1148,   485,   539,   449,
     540,   351,   438,   617,   588,    54,   428,   730,   136,   465,
     472,   483,   478,   270,   332,   372,   374,   486,   487,   491,
     499,   504,   542,   166,   541,    22,   247,   345,   575,   576,
     577,   578,   580,   584,   449,   351,   235,   670,   436,   591,
     593,  1068,   732,   731,   336,   738,   478,   466,   449,   449,
     449,   449,   449,   354,   543,   449,   212,   574,    71,   400,
    1133,   314,   369,   370,   579,   449,   577,   587,   449,   351,
     231,   672,   590,   592,   619,   620,   621,   594,    49,   733,
     734,   735,  1128,   733,   436,   449,   449,   585,   241,   353,
     436,   490,   492,   493,   494,   495,   497,   498,  1148,   178,
     500,   501,   502,   435,   488,   489,   490,  1162,    11,    25,
      26,    57,    94,    95,    97,   105,   148,   149,   159,   233,
     347,   387,   436,   505,   506,   507,   508,   515,   524,   528,
     531,   532,   533,   534,   535,   536,   537,   278,  1114,   542,
     449,   275,  1145,   390,  1156,    24,  1124,   589,   618,   449,
     351,   327,   674,   593,   622,  1108,   595,   734,   367,   412,
     736,   320,   429,   728,   467,   367,  1137,   449,   493,   449,
     494,    62,   358,  1120,     9,   232,   503,   449,   502,   449,
     449,   489,   104,   436,  1079,  1137,  1137,  1079,   379,   362,
    1152,  1137,  1137,  1137,  1137,  1137,  1079,  1137,    56,  1130,
    1137,   449,   507,  1079,   575,   436,  1075,  1076,  1094,    84,
    1131,   172,  1134,   590,   619,   671,   449,   351,   346,   715,
     619,   449,  1108,   223,   224,   623,   626,   627,   633,     1,
      47,    61,    99,   215,   227,   314,   315,   327,   329,   429,
     449,   596,   597,   599,   603,   605,   607,   608,   614,   615,
     616,  1137,  1137,   367,   278,   737,   106,   739,   727,  1137,
     232,  1097,   449,   358,  1137,   207,   207,   232,   449,   245,
     516,  1079,  1079,  1137,  1137,  1137,  1076,    67,  1079,  1079,
    1076,  1137,  1076,   525,   526,  1079,    94,   510,  1079,   544,
     196,   272,  1117,  1076,   581,   582,  1068,  1067,  1068,   619,
     673,   449,   351,   623,   168,   436,   629,   630,   436,   629,
    1131,  1137,   314,   316,  1118,  1118,  1137,  1131,  1137,   245,
    1142,  1137,    23,  1123,   272,   164,   184,    31,   107,  1097,
    1137,   436,   449,   729,   471,  1097,  1076,  1137,   191,   232,
     239,   310,   373,   402,   442,   529,   530,  1100,  1076,   232,
    1076,    23,   210,  1079,  1138,   273,   275,   512,   513,   514,
     509,   545,  1094,   582,   296,   583,  1068,   619,   675,   449,
     624,    83,   625,  1097,   436,  1137,  1123,  1075,   274,   375,
     604,   232,  1076,  1078,  1097,   430,  1137,   436,   714,   714,
     167,   436,  1097,   740,   741,   136,   473,    56,   437,   496,
     121,   191,   232,   239,   251,   310,   373,   376,   377,   442,
     517,   518,   519,   522,   530,   395,   527,  1097,   513,   379,
    1155,   511,     1,     4,    19,    29,   198,   229,   236,   281,
     287,   314,   321,   334,   359,   361,   369,   400,   449,   546,
     547,   551,   553,   558,   559,   560,   561,   565,   566,   567,
     568,   569,   570,   571,   572,  1120,  1097,   312,   676,   677,
     678,   716,   634,   631,  1137,   429,   663,   398,   602,   230,
    1141,   398,  1130,   196,  1136,   436,  1137,  1137,   741,     1,
     436,   742,   743,   744,   745,   746,   751,   478,   519,    17,
     395,  1100,  1097,  1137,   513,  1142,   314,   398,  1160,   359,
    1142,  1137,    55,  1129,    37,   110,   214,  1127,  1139,  1139,
    1097,  1162,   379,  1137,   714,   678,   717,     1,    21,    34,
      37,    38,    39,    40,    41,    42,    43,    73,    75,    76,
      77,    78,    79,    80,   115,   197,   213,   232,   249,   271,
     286,   293,   295,   308,   318,   325,   362,   364,   365,   366,
     388,   413,   414,   415,   426,   429,   628,   635,   636,   637,
     639,   640,   641,   642,   643,   645,   657,   658,   660,   661,
     662,   668,   669,  1137,  1153,    27,  1125,   184,  1138,  1097,
      56,   316,   598,   609,  1097,   367,  1154,   232,   606,  1094,
     606,   123,   449,   351,     3,     5,    10,    18,    51,    52,
      59,    70,    74,    86,   108,   115,   116,   146,   158,   162,
     175,   182,   185,   186,   193,   200,   202,   205,   242,   246,
     248,   255,   277,   292,   313,   322,   335,   340,   342,   350,
     360,   369,   378,   380,   381,   384,   386,   391,   406,   411,
     416,   427,   439,   449,   752,   753,   763,   768,   772,   775,
     788,   791,   796,   801,   802,   803,   806,   808,   815,   819,
     821,   836,   839,   841,   843,   846,   848,   854,   863,   865,
     882,   884,   887,   891,   897,   907,   914,   916,   919,   923,
     924,   935,   946,   956,   962,   965,   971,   975,   977,   979,
     981,   984,   995,   996,  1005,  1007,  1008,   449,   520,   522,
    1079,  1137,  1139,   120,   164,   549,  1137,   314,   321,   566,
    1137,  1137,   359,  1137,  1137,  1124,     9,   256,   313,   573,
    1137,   436,   679,   626,   633,   718,   719,   720,   221,   363,
     412,   363,   412,   363,   412,   363,   412,   363,   412,   432,
    1161,   341,  1150,  1097,  1093,  1094,  1094,   210,   220,   341,
     659,  1137,  1137,   164,   184,   219,   405,     9,    50,   221,
     632,  1098,  1099,  1100,   665,   666,  1098,    30,   610,   611,
     612,   613,  1126,  1162,  1130,   176,   601,  1135,   106,   232,
     747,   754,   764,   769,   773,   776,   789,   792,   797,   804,
     807,   809,   816,   820,   822,   837,   840,   842,  1160,   847,
       1,   849,   855,   864,   866,   883,   885,   888,   892,   898,
     908,   915,   917,   920,   925,   936,   947,   957,   232,   344,
     966,   972,   301,   976,   978,   980,   982,   985,   184,   997,
    1134,  1009,   191,   232,   239,   310,   373,   442,   521,   523,
     120,   311,   359,   552,  1137,   114,   300,   548,    32,   161,
     240,   562,  1078,   376,  1076,  1076,   282,  1147,  1147,   276,
    1076,    60,    87,    88,   288,   449,   680,   681,   685,  1137,
     629,   720,   442,   398,   646,   452,  1095,  1096,   395,   642,
    1098,    27,   638,   357,  1116,  1116,  1100,   272,  1144,  1144,
     456,   664,   666,   395,    48,   404,   171,   602,  1097,   449,
     449,   755,  1092,  1093,     6,    81,    92,    96,   180,   221,
     228,   234,   237,   269,   337,   382,   383,   407,   425,   433,
     765,  1062,  1082,  1083,  1092,  1098,  1101,   436,   770,  1049,
    1050,  1051,   232,  1072,  1073,  1074,  1094,   232,  1090,  1092,
    1101,   790,   793,   798,  1063,  1064,  1083,  1068,   400,   232,
     810,  1082,  1089,  1092,   817,  1083,   232,   399,   403,   823,
     824,  1049,   291,   292,   305,   351,   838,     6,  1080,  1081,
    1092,  1092,   844,   133,  1048,  1049,  1080,   684,  1092,   867,
    1092,  1098,  1101,   948,  1094,    92,   886,  1083,   889,  1083,
     893,   174,   232,   899,   902,   903,   904,  1072,  1090,  1094,
    1162,  1068,  1065,  1094,  1068,  1065,     9,   926,  1066,  1094,
     147,   244,   937,   938,   939,   940,   942,   943,   944,   945,
    1069,  1070,  1080,   948,  1068,   963,   109,   967,   968,  1083,
      92,   973,  1082,   684,  1092,  1068,  1092,     8,    35,   999,
     104,  1065,    17,  1076,   115,   232,   550,  1094,   435,   563,
     563,   371,   450,   557,  1076,  1077,  1137,   169,   682,   683,
     682,  1138,   693,   184,   721,  1097,   397,  1159,   221,   443,
     444,   452,  1059,  1061,  1062,  1084,  1092,  1099,  1101,   452,
    1096,  1094,   232,  1129,  1093,  1093,  1100,  1161,  1098,  1078,
    1078,  1126,  1130,   124,   762,    30,   176,   756,  1126,  1144,
     452,  1092,   452,  1102,   452,  1103,  1144,  1117,   452,   452,
     452,   452,   452,   452,   452,   452,  1102,   125,   767,   398,
     766,  1083,   201,  1111,    56,  1052,  1053,   398,  1117,   428,
     777,   232,  1089,  1092,  1068,   127,   799,   153,   450,   800,
    1064,   343,  1115,   314,  1149,  1067,   129,   814,   756,   421,
     422,   423,   424,   130,   818,    49,   206,   777,    17,   432,
     825,   826,   827,   831,  1122,    98,  1144,  1081,  1071,   394,
    1158,   856,  1162,  1092,    91,   326,   389,   868,   869,   870,
     874,   879,   950,  1083,   398,   134,   890,    49,   163,   203,
     211,   283,   894,   903,   135,   900,   417,   430,   395,   397,
     392,   254,   299,  1112,   176,  1010,  1149,  1010,  1066,   140,
     934,   430,   928,  1087,  1092,  1099,   943,   945,  1080,   398,
    1070,   118,   398,   418,   941,   958,   183,   336,   964,  1128,
     206,   968,  1092,   143,   974,   176,   176,   314,   316,   983,
     109,   986,   328,   375,  1000,  1145,  1010,   523,   119,   435,
     557,  1110,  1119,   236,   342,  1137,   554,   555,  1089,   684,
     691,  1097,   626,   694,   722,   111,   647,  1144,  1061,  1061,
    1061,    69,   355,   451,  1060,   443,   444,   445,   446,   448,
     455,  1061,   360,  1151,  1141,  1078,   111,   600,  1087,    25,
      26,    66,    68,   100,   101,   102,   147,   149,   157,   230,
     396,   436,  1070,   435,   759,    65,   229,   296,   757,   758,
     146,   305,  1085,  1093,  1059,  1061,   398,  1061,  1059,  1104,
    1093,  1099,  1101,   436,  1061,  1107,  1061,  1061,  1106,  1061,
    1059,  1059,  1061,  1105,  1061,  1063,  1083,   183,   336,   771,
    1111,    12,    13,    14,    20,    58,   153,   154,   181,   187,
     210,   218,   222,   252,   253,   257,   267,   274,   279,   297,
     442,   443,   444,   445,   446,   448,   450,   451,   453,   454,
    1054,  1055,  1056,  1057,  1058,    12,    13,    14,    58,   210,
     252,   253,   257,   267,   274,   297,   443,   444,   448,   452,
    1054,  1055,  1056,  1057,  1058,  1083,   304,   774,  1074,   778,
     183,   336,   782,   319,   410,   794,   795,  1162,  1049,   209,
     261,  1041,  1042,  1043,  1045,   420,   435,   811,  1162,   160,
    1016,  1017,  1016,  1016,  1016,  1083,  1063,  1083,    21,   399,
     403,   832,   833,  1050,   131,   835,   434,   827,   829,   432,
     828,   824,  1093,   111,   845,  1072,   850,     9,    12,    15,
      16,   249,   250,   267,   268,   857,   861,   168,  1087,     9,
      56,   170,   219,   405,   875,   876,   877,   871,   869,   952,
    1119,  1145,   398,  1080,  1063,  1083,   361,   895,   748,   749,
    1048,   905,   906,  1092,  1072,     8,    35,  1012,  1149,  1089,
     206,   909,   921,  1162,   929,  1126,  1092,   929,   398,   398,
     514,   146,   399,   403,  1083,    49,   214,   959,  1083,  1083,
     367,  1083,  1092,   176,  1063,  1083,  1087,  1128,   206,   989,
    1092,   156,   160,  1001,     9,  1006,  1072,   921,   119,   554,
     275,   556,  1076,   556,   189,   686,   229,   230,   692,   629,
      31,    33,    36,    44,    45,    46,    65,   155,   173,   176,
     177,   190,   229,   238,   271,   285,   309,   333,   338,   352,
     398,   409,   428,   449,   640,   641,   643,   657,   660,   662,
     723,   726,  1145,    28,   112,   198,   644,   649,   650,   651,
     652,   654,  1093,  1099,  1101,   451,  1061,  1061,  1061,  1061,
    1061,  1061,   451,  1061,  1160,  1141,  1145,  1015,  1017,   441,
     440,  1087,  1015,   214,    31,    33,    36,    46,   173,   177,
     190,   238,   285,   309,   333,   338,   348,   352,   409,   419,
     760,   761,  1015,   265,  1143,  1143,  1143,   758,   757,   232,
    1086,  1093,   451,  1092,   455,   451,  1060,   451,   451,  1060,
     451,   451,   451,   451,  1060,   451,   451,   368,  1021,  1022,
    1063,  1081,   336,  1160,   393,  1157,  1157,   398,  1072,   779,
     780,   781,  1128,  1092,  1092,   160,   284,   783,  1002,  1134,
     236,   256,  1021,  1044,  1046,   128,   805,  1045,    94,   300,
     436,  1070,    33,    36,    44,    45,    46,   155,   173,   190,
     238,   285,   338,   348,   409,   812,   813,  1016,   264,  1018,
     260,  1019,   183,  1021,   183,  1122,   395,   834,   830,   832,
     748,  1145,   748,  1160,   326,   858,  1160,   398,    49,   876,
     878,  1087,     9,    56,   219,   405,   872,   873,  1087,   953,
    1120,   196,   280,  1146,   652,  1080,  1021,   183,  1162,  1067,
     135,   901,   750,     8,   176,   909,  1092,   123,   258,  1031,
    1032,  1034,  1041,   236,   256,   432,   123,   432,   931,   932,
    1087,  1086,  1083,  1137,  1041,   969,  1162,  1092,  1021,   183,
     398,     9,   987,   988,  1109,   990,  1092,   969,   990,   302,
    1004,   303,  1011,  1012,  1110,   247,   314,   316,   564,  1137,
     170,   687,  1097,   695,  1137,  1143,   150,   152,  1137,  1090,
    1143,  1097,  1092,  1092,  1076,  1128,   653,   654,   650,  1139,
     648,   649,   451,   399,   667,  1076,  1019,  1015,  1137,  1137,
     118,   418,   761,  1089,  1089,  1089,  1102,  1115,   451,  1061,
    1076,  1102,  1102,  1061,  1102,  1102,  1102,   219,   405,  1102,
    1102,  1023,   263,  1024,  1021,  1081,   153,   279,   153,   279,
     780,   274,   736,    85,   320,   429,   260,   262,   785,  1003,
     784,   324,   339,   748,   748,   811,   811,   811,   811,  1137,
     150,   152,  1137,   118,   418,   813,   748,  1020,  1063,  1064,
    1063,  1064,   833,  1049,   748,  1092,   122,   851,   429,   859,
     860,   861,   107,   862,   429,  1088,  1092,  1098,  1087,    49,
     880,   873,   172,   880,   949,  1137,   280,  1139,  1063,   573,
     896,  1162,   751,   906,  1083,   195,   910,  1162,  1033,  1035,
     138,   918,  1034,   139,   922,   236,  1049,   930,  1048,   931,
     257,   960,  1113,   141,   961,   284,  1026,  1027,   295,  1115,
    1063,  1088,   279,  1087,   110,   991,   389,   993,  1145,   151,
     259,  1013,  1036,  1037,  1039,  1042,     7,  1121,   564,  1097,
     113,   216,   688,    66,    65,    66,   188,   229,   230,   254,
     298,   371,   385,   408,   430,   449,   640,   641,   643,   645,
     657,   660,   662,   696,   697,   699,   700,   701,   702,   704,
     705,   706,   707,   711,   712,   442,  1091,  1092,  1097,  1137,
    1091,  1137,  1159,   436,   655,   656,  1137,  1137,  1091,  1091,
    1047,  1128,  1047,  1021,   451,   748,  1025,  1160,   153,  1160,
     153,  1083,   126,   787,   786,   748,  1016,  1016,  1016,  1016,
    1091,  1091,  1047,  1047,   748,  1021,   323,  1021,   323,   852,
     133,   853,   860,    99,  1132,   880,   880,  1088,  1012,   203,
     428,   954,  1076,   951,  1021,   236,   256,    49,   236,   214,
     911,   194,   236,   256,   431,   748,   748,   927,   748,   933,
     684,  1054,  1055,  1056,  1057,  1058,  1028,   142,   970,   262,
    1029,  1092,  1021,  1021,   988,  1136,    93,   992,  1136,  1026,
     163,   203,   211,   283,   998,  1067,  1038,  1040,   145,  1014,
    1039,   288,  1070,  1091,  1137,    90,   217,   689,   266,  1143,
     199,   713,   265,   266,   710,  1123,   188,   432,  1137,  1144,
    1137,  1092,   702,   254,   294,   708,   709,  1097,   243,   294,
     443,   444,   725,   243,   294,   443,   444,   724,   656,  1075,
    1098,  1091,   748,  1160,  1160,   748,  1064,  1064,   748,    49,
     880,   401,   881,   302,  1067,   183,   283,   955,  1094,   339,
    1083,  1137,   912,  1031,  1042,   236,   236,   748,   748,   748,
    1030,  1092,  1136,  1092,   144,   994,   748,   748,   229,   230,
    1140,  1097,  1137,  1137,   171,   690,  1137,  1138,  1137,  1048,
    1092,   703,  1076,    89,    90,   113,   289,   290,   330,   331,
     698,   176,   288,  1097,   709,  1091,  1091,  1140,  1021,  1021,
    1083,  1083,  1137,  1067,   302,   417,   684,   137,   913,   748,
    1092,  1097,  1097,  1137,  1097,  1097,  1115,  1083,   902,  1137,
    1048,  1097,    49,   902,  1083
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
#line 6943 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1376:

/* Line 1455 of yacc.c  */
#line 6944 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1379:

/* Line 1455 of yacc.c  */
#line 6956 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE ((yyval))->word->count > 0) {
		redefinition_error ((yyval));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1380:

/* Line 1455 of yacc.c  */
#line 6975 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1381:

/* Line 1455 of yacc.c  */
#line 6976 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1383:

/* Line 1455 of yacc.c  */
#line 6981 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1384:

/* Line 1455 of yacc.c  */
#line 6985 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1385:

/* Line 1455 of yacc.c  */
#line 6986 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1387:

/* Line 1455 of yacc.c  */
#line 6991 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1388:

/* Line 1455 of yacc.c  */
#line 6992 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1389:

/* Line 1455 of yacc.c  */
#line 6993 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1390:

/* Line 1455 of yacc.c  */
#line 6994 "parser.y"
    { (yyval) = cb_build_ppointer ((yyvsp[(4) - (4)])); ;}
    break;

  case 1391:

/* Line 1455 of yacc.c  */
#line 6995 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1396:

/* Line 1455 of yacc.c  */
#line 7003 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1397:

/* Line 1455 of yacc.c  */
#line 7004 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1398:

/* Line 1455 of yacc.c  */
#line 7005 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1404:

/* Line 1455 of yacc.c  */
#line 7017 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1405:

/* Line 1455 of yacc.c  */
#line 7018 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1417:

/* Line 1455 of yacc.c  */
#line 7052 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1418:

/* Line 1455 of yacc.c  */
#line 7060 "parser.y"
    { (yyval) = cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1419:

/* Line 1455 of yacc.c  */
#line 7064 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1420:

/* Line 1455 of yacc.c  */
#line 7065 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1421:

/* Line 1455 of yacc.c  */
#line 7066 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1422:

/* Line 1455 of yacc.c  */
#line 7067 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 1423:

/* Line 1455 of yacc.c  */
#line 7071 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1424:

/* Line 1455 of yacc.c  */
#line 7072 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); CB_REFERENCE ((yyvsp[(1) - (3)]))->chain = (yyvsp[(3) - (3)]); ;}
    break;

  case 1425:

/* Line 1455 of yacc.c  */
#line 7077 "parser.y"
    {
	if (cb_ref ((yyvsp[(0) - (3)])) != cb_error_node) {
		(yyval) = (yyvsp[(0) - (3)]);
		CB_REFERENCE ((yyvsp[(0) - (3)]))->subs = cb_list_reverse ((yyvsp[(2) - (3)]));
	}
  ;}
    break;

  case 1426:

/* Line 1455 of yacc.c  */
#line 7087 "parser.y"
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

  case 1427:

/* Line 1455 of yacc.c  */
#line 7105 "parser.y"
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

  case 1428:

/* Line 1455 of yacc.c  */
#line 7132 "parser.y"
    {
	if (cb_tree_category ((yyvsp[(1) - (1)])) != CB_CATEGORY_NUMERIC) {
		cb_error (_("Integer value expected"));
	} else if (CB_LITERAL ((yyvsp[(1) - (1)]))->sign < 0 || CB_LITERAL ((yyvsp[(1) - (1)]))->scale) {
		cb_error (_("Integer value expected"));
	}
	(yyval) = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1429:

/* Line 1455 of yacc.c  */
#line 7143 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1430:

/* Line 1455 of yacc.c  */
#line 7145 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (2)]);
	if (CB_LITERAL_P ((yyvsp[(2) - (2)]))) {
		CB_LITERAL ((yyvsp[(2) - (2)]))->all = 1;
	}
  ;}
    break;

  case 1431:

/* Line 1455 of yacc.c  */
#line 7154 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1432:

/* Line 1455 of yacc.c  */
#line 7155 "parser.y"
    { (yyval) = cb_concat_literals ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1433:

/* Line 1455 of yacc.c  */
#line 7159 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1434:

/* Line 1455 of yacc.c  */
#line 7160 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 1435:

/* Line 1455 of yacc.c  */
#line 7161 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1436:

/* Line 1455 of yacc.c  */
#line 7162 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 1437:

/* Line 1455 of yacc.c  */
#line 7163 "parser.y"
    { (yyval) = cb_high; ;}
    break;

  case 1438:

/* Line 1455 of yacc.c  */
#line 7164 "parser.y"
    { (yyval) = cb_low; ;}
    break;

  case 1439:

/* Line 1455 of yacc.c  */
#line 7165 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1440:

/* Line 1455 of yacc.c  */
#line 7174 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1441:

/* Line 1455 of yacc.c  */
#line 7178 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1442:

/* Line 1455 of yacc.c  */
#line 7182 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1443:

/* Line 1455 of yacc.c  */
#line 7186 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1444:

/* Line 1455 of yacc.c  */
#line 7190 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1445:

/* Line 1455 of yacc.c  */
#line 7194 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1446:

/* Line 1455 of yacc.c  */
#line 7198 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1447:

/* Line 1455 of yacc.c  */
#line 7202 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1448:

/* Line 1455 of yacc.c  */
#line 7206 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1449:

/* Line 1455 of yacc.c  */
#line 7210 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), NULL);
  ;}
    break;

  case 1450:

/* Line 1455 of yacc.c  */
#line 7214 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1451:

/* Line 1455 of yacc.c  */
#line 7218 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), NULL);
  ;}
    break;

  case 1452:

/* Line 1455 of yacc.c  */
#line 7224 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1453:

/* Line 1455 of yacc.c  */
#line 7225 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (4)]), NULL); ;}
    break;

  case 1454:

/* Line 1455 of yacc.c  */
#line 7226 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 1455:

/* Line 1455 of yacc.c  */
#line 7230 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1456:

/* Line 1455 of yacc.c  */
#line 7231 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1457:

/* Line 1455 of yacc.c  */
#line 7235 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1458:

/* Line 1455 of yacc.c  */
#line 7236 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1459:

/* Line 1455 of yacc.c  */
#line 7242 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_int0);
  ;}
    break;

  case 1460:

/* Line 1455 of yacc.c  */
#line 7249 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int1);
  ;}
    break;

  case 1461:

/* Line 1455 of yacc.c  */
#line 7256 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int2);
  ;}
    break;

  case 1462:

/* Line 1455 of yacc.c  */
#line 7266 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1463:

/* Line 1455 of yacc.c  */
#line 7273 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1464:

/* Line 1455 of yacc.c  */
#line 7283 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1465:

/* Line 1455 of yacc.c  */
#line 7290 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_ref ((yyvsp[(3) - (3)])));
  ;}
    break;

  case 1466:

/* Line 1455 of yacc.c  */
#line 7303 "parser.y"
    {
	non_const_word = 1;
  ;}
    break;

  case 1467:

/* Line 1455 of yacc.c  */
#line 7313 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1468:

/* Line 1455 of yacc.c  */
#line 7314 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1469:

/* Line 1455 of yacc.c  */
#line 7318 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1470:

/* Line 1455 of yacc.c  */
#line 7319 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1471:

/* Line 1455 of yacc.c  */
#line 7323 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1472:

/* Line 1455 of yacc.c  */
#line 7324 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1473:

/* Line 1455 of yacc.c  */
#line 7328 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1474:

/* Line 1455 of yacc.c  */
#line 7329 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1475:

/* Line 1455 of yacc.c  */
#line 7330 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 1476:

/* Line 1455 of yacc.c  */
#line 7334 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1477:

/* Line 1455 of yacc.c  */
#line 7335 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1478:

/* Line 1455 of yacc.c  */
#line 7339 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1479:

/* Line 1455 of yacc.c  */
#line 7340 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1480:

/* Line 1455 of yacc.c  */
#line 7344 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1481:

/* Line 1455 of yacc.c  */
#line 7345 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1482:

/* Line 1455 of yacc.c  */
#line 7349 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1483:

/* Line 1455 of yacc.c  */
#line 7350 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1495:

/* Line 1455 of yacc.c  */
#line 7363 "parser.y"
    { (yyval) = cb_int1; ;}
    break;



/* Line 1455 of yacc.c  */
#line 14714 "parser.c"
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
#line 7407 "parser.y"


