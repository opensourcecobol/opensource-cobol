
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
     CLOSE_NOFEED = 315,
     CODE = 316,
     CODE_SET = 317,
     COLLATING = 318,
     COL = 319,
     COLS = 320,
     COLUMN = 321,
     COLUMNS = 322,
     COMMA = 323,
     COMMAND_LINE = 324,
     COMMA_DELIM = 325,
     COMMIT = 326,
     COMMITMENT_CONTROL = 327,
     COMMON = 328,
     COMP = 329,
     COMPUTE = 330,
     COMP_1 = 331,
     COMP_2 = 332,
     COMP_3 = 333,
     COMP_4 = 334,
     COMP_5 = 335,
     COMP_X = 336,
     CONCATENATE_FUNC = 337,
     CONFIGURATION = 338,
     CONSTANT = 339,
     CONTAINS = 340,
     CONTENT = 341,
     CONTINUE = 342,
     CONTROL = 343,
     CONTROLS = 344,
     CONTROL_FOOTING = 345,
     CONTROL_HEADING = 346,
     CONVERTING = 347,
     CORE_INDEX = 348,
     CORRESPONDING = 349,
     COUNT = 350,
     CRT = 351,
     CURRENCY = 352,
     CURRENT_DATE_FUNC = 353,
     CURSOR = 354,
     CYCLE = 355,
     CYL_OVERFLOW = 356,
     DATA = 357,
     DATE = 358,
     DAY = 359,
     DAY_OF_WEEK = 360,
     DE = 361,
     DEBUGGING = 362,
     DECIMAL_POINT = 363,
     DECLARATIVES = 364,
     DEFAULT = 365,
     DELETE = 366,
     DELIMITED = 367,
     DELIMITER = 368,
     DEPENDING = 369,
     DESCENDING = 370,
     DETAIL = 371,
     DISK = 372,
     DISPLAY = 373,
     DIVIDE = 374,
     DIVISION = 375,
     DOWN = 376,
     DUPLICATES = 377,
     DYNAMIC = 378,
     EBCDIC = 379,
     ELSE = 380,
     END = 381,
     END_ACCEPT = 382,
     END_ADD = 383,
     END_CALL = 384,
     END_COMPUTE = 385,
     END_DELETE = 386,
     END_DISPLAY = 387,
     END_DIVIDE = 388,
     END_EVALUATE = 389,
     END_FUNCTION = 390,
     END_IF = 391,
     END_MULTIPLY = 392,
     END_PERFORM = 393,
     END_PROGRAM = 394,
     END_READ = 395,
     END_RETURN = 396,
     END_REWRITE = 397,
     END_SEARCH = 398,
     END_START = 399,
     END_STRING = 400,
     END_SUBTRACT = 401,
     END_UNSTRING = 402,
     END_WRITE = 403,
     ENTRY = 404,
     ENVIRONMENT = 405,
     ENVIRONMENT_NAME = 406,
     ENVIRONMENT_VALUE = 407,
     EOL = 408,
     EOP = 409,
     EOS = 410,
     EQUAL = 411,
     EQUALS = 412,
     ERASE = 413,
     ERROR = 414,
     ESCAPE = 415,
     EVALUATE = 416,
     EVENT_STATUS = 417,
     EXCEPTION = 418,
     EXCLUSIVE = 419,
     EXIT = 420,
     EXTEND = 421,
     EXTERNAL = 422,
     FD = 423,
     FILE_CONTROL = 424,
     FILE_ID = 425,
     FILLER = 426,
     FINAL = 427,
     FIRST = 428,
     FOOTING = 429,
     FOR = 430,
     FOREGROUND_COLOR = 431,
     FOREVER = 432,
     FORMS_OVERLAY = 433,
     FREE = 434,
     FROM = 435,
     FULL = 436,
     FUNCTION = 437,
     FUNCTION_ID = 438,
     FUNCTION_NAME = 439,
     GE = 440,
     GENERATE = 441,
     GIVING = 442,
     GLOBAL = 443,
     GO = 444,
     GOBACK = 445,
     GREATER = 446,
     GROUP = 447,
     HEADING = 448,
     HIGHLIGHT = 449,
     HIGH_VALUE = 450,
     IDENTIFICATION = 451,
     IF = 452,
     IGNORE = 453,
     IGNORING = 454,
     IN = 455,
     INDEX = 456,
     INDEXED = 457,
     INDICATE = 458,
     INITIALIZE = 459,
     INITIALIZED = 460,
     INITIATE = 461,
     INPUT = 462,
     INPUT_OUTPUT = 463,
     INSPECT = 464,
     INTO = 465,
     INTRINSIC = 466,
     INVALID = 467,
     INVALID_KEY = 468,
     IS = 469,
     I_O = 470,
     I_O_CONTROL = 471,
     JUSTIFIED = 472,
     KEY = 473,
     LABEL = 474,
     LAST = 475,
     LAST_DETAIL = 476,
     LE = 477,
     LEADING = 478,
     LEFT = 479,
     LENGTH = 480,
     LESS = 481,
     LEVEL_NUMBER_WORD = 482,
     LEVEL88_NUMBER_WORD = 483,
     LIMIT = 484,
     LIMITS = 485,
     LINAGE = 486,
     LINAGE_COUNTER = 487,
     LINE = 488,
     LINES = 489,
     LINKAGE = 490,
     LITERAL = 491,
     LOCALE = 492,
     LOCALE_DT_FUNC = 493,
     LOCAL_STORAGE = 494,
     LOCK = 495,
     LOWER_CASE_FUNC = 496,
     LOWLIGHT = 497,
     LOW_VALUE = 498,
     MANUAL = 499,
     MEMORY = 500,
     MERGE = 501,
     MINUS = 502,
     MNEMONIC_NAME = 503,
     MODE = 504,
     MOVE = 505,
     MULTIPLE = 506,
     MULTIPLY = 507,
     NATIONAL = 508,
     NATIONAL_EDITED = 509,
     NATIVE = 510,
     NE = 511,
     NEGATIVE = 512,
     NEXT = 513,
     NEXT_SENTENCE = 514,
     NO = 515,
     NOMINAL = 516,
     NOT = 517,
     NOT_END = 518,
     NOT_EOP = 519,
     NOT_EXCEPTION = 520,
     NOT_INVALID_KEY = 521,
     NOT_OVERFLOW = 522,
     NOT_SIZE_ERROR = 523,
     NO_ADVANCING = 524,
     NUMBER = 525,
     NUMBERS = 526,
     NUMERIC = 527,
     NUMERIC_EDITED = 528,
     NUMVALC_FUNC = 529,
     OBJECT_COMPUTER = 530,
     OCCURS = 531,
     OF = 532,
     OFF = 533,
     OMITTED = 534,
     ON = 535,
     ONLY = 536,
     OPEN = 537,
     OPTIONAL = 538,
     OR = 539,
     ORDER = 540,
     ORGANIZATION = 541,
     OTHER = 542,
     OUTPUT = 543,
     OVERFLOW = 544,
     OVERLINE = 545,
     PACKED_DECIMAL = 546,
     PADDING = 547,
     PAGE = 548,
     PAGE_FOOTING = 549,
     PAGE_HEADING = 550,
     PARAGRAPH = 551,
     PERFORM = 552,
     PICTURE = 553,
     PLUS = 554,
     POINTER = 555,
     POSITION = 556,
     POSITIVE = 557,
     PRESENT = 558,
     PREVIOUS = 559,
     PRINTER = 560,
     PRINTING = 561,
     PROCEDURE = 562,
     PROCEDURES = 563,
     PROCEED = 564,
     PROGRAM = 565,
     PROGRAM_ID = 566,
     PROGRAM_NAME = 567,
     PROGRAM_POINTER = 568,
     PROMPT = 569,
     QUOTE = 570,
     RANDOM = 571,
     RD = 572,
     READ = 573,
     RECORD = 574,
     RECORDING = 575,
     RECORDS = 576,
     RECURSIVE = 577,
     REDEFINES = 578,
     REEL = 579,
     REFERENCE = 580,
     RELATIVE = 581,
     RELEASE = 582,
     REMAINDER = 583,
     REMOVAL = 584,
     RENAMES = 585,
     REPLACING = 586,
     REPORT = 587,
     REPORTING = 588,
     REPORTS = 589,
     REPORT_FOOTING = 590,
     REPORT_HEADING = 591,
     REPOSITORY = 592,
     REQUIRED = 593,
     RESERVE = 594,
     RETURN = 595,
     RETURNING = 596,
     REVERSE_FUNC = 597,
     REVERSE_VIDEO = 598,
     REWIND = 599,
     REWRITE = 600,
     RIGHT = 601,
     ROLLBACK = 602,
     ROUNDED = 603,
     RUN = 604,
     SAME = 605,
     SCREEN = 606,
     SCREEN_CONTROL = 607,
     SCROLL = 608,
     SD = 609,
     SEARCH = 610,
     SECTION = 611,
     SECURE = 612,
     SEGMENT_LIMIT = 613,
     SELECT = 614,
     SEMI_COLON = 615,
     SENTENCE = 616,
     SEPARATE = 617,
     SEQUENCE = 618,
     SEQUENTIAL = 619,
     SET = 620,
     SHARING = 621,
     SIGN = 622,
     SIGNED = 623,
     SIGNED_INT = 624,
     SIGNED_LONG = 625,
     SIGNED_SHORT = 626,
     SIZE = 627,
     SIZE_ERROR = 628,
     SORT = 629,
     SORT_MERGE = 630,
     SOURCE = 631,
     SOURCE_COMPUTER = 632,
     SPACE = 633,
     SPECIAL_NAMES = 634,
     STANDARD = 635,
     STANDARD_1 = 636,
     STANDARD_2 = 637,
     START = 638,
     STATUS = 639,
     STOP = 640,
     STRING = 641,
     SUBSTITUTE_FUNC = 642,
     SUBSTITUTE_CASE_FUNC = 643,
     SUBTRACT = 644,
     SUM = 645,
     SUPPRESS = 646,
     SYMBOLIC = 647,
     SYNCHRONIZED = 648,
     TALLYING = 649,
     TAPE = 650,
     TERMINATE = 651,
     TEST = 652,
     THAN = 653,
     THEN = 654,
     THRU = 655,
     TIME = 656,
     TIMES = 657,
     TO = 658,
     TOK_FALSE = 659,
     TOK_FILE = 660,
     TOK_INITIAL = 661,
     TOK_NULL = 662,
     TOK_TRUE = 663,
     TOP = 664,
     TRACKS = 665,
     TRAILING = 666,
     TRANSFORM = 667,
     TRIM_FUNCTION = 668,
     TYPE = 669,
     UNDERLINE = 670,
     UNIT = 671,
     UNLOCK = 672,
     UNSIGNED = 673,
     UNSIGNED_INT = 674,
     UNSIGNED_LONG = 675,
     UNSIGNED_SHORT = 676,
     UNSTRING = 677,
     UNTIL = 678,
     UP = 679,
     UPDATE = 680,
     UPON = 681,
     UPON_ARGUMENT_NUMBER = 682,
     UPON_COMMAND_LINE = 683,
     UPON_ENVIRONMENT_NAME = 684,
     UPON_ENVIRONMENT_VALUE = 685,
     UPPER_CASE_FUNC = 686,
     USAGE = 687,
     USE = 688,
     USING = 689,
     VALUE = 690,
     VARYING = 691,
     WAIT = 692,
     WHEN = 693,
     WHEN_COMPILED_FUNC = 694,
     WHEN_OTHER = 695,
     WITH = 696,
     WORD = 697,
     WORDS = 698,
     WORKING_STORAGE = 699,
     WRITE = 700,
     YYYYDDD = 701,
     YYYYMMDD = 702,
     ZERO = 703,
     UNARY_SIGN = 704
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
#line 850 "parser.c"

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
#define YYLAST   5948

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  463
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  711
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1595
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2349

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   704

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   462,     2,
     458,   457,   451,   449,     2,   450,   455,   452,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   461,     2,
     460,   456,   459,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   454,     2,     2,     2,     2,     2,
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
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   453
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
     499,   501,   503,   505,   507,   509,   511,   517,   522,   527,
     528,   530,   532,   533,   535,   537,   539,   541,   544,   546,
     549,   554,   556,   558,   560,   567,   576,   577,   580,   583,
     585,   586,   589,   591,   595,   601,   602,   604,   606,   611,
     614,   617,   619,   620,   625,   631,   634,   636,   638,   642,
     644,   646,   650,   652,   654,   657,   662,   667,   672,   679,
     684,   688,   691,   695,   698,   701,   704,   709,   710,   714,
     715,   718,   720,   722,   724,   727,   729,   731,   737,   738,
     740,   742,   744,   750,   752,   755,   758,   759,   762,   765,
     767,   770,   775,   783,   790,   797,   802,   803,   813,   814,
     815,   821,   822,   826,   827,   830,   834,   837,   840,   842,
     844,   845,   850,   851,   854,   857,   860,   862,   864,   866,
     868,   870,   872,   874,   876,   878,   880,   886,   887,   889,
     891,   896,   903,   913,   914,   918,   919,   922,   923,   926,
     930,   932,   934,   940,   946,   948,   950,   954,   960,   961,
     964,   966,   968,   970,   976,   981,   985,   990,   994,   998,
    1002,  1003,  1004,  1010,  1011,  1013,  1014,  1017,  1020,  1024,
    1027,  1029,  1030,  1036,  1037,  1042,  1044,  1046,  1047,  1049,
    1050,  1052,  1054,  1056,  1057,  1060,  1062,  1066,  1070,  1077,
    1078,  1081,  1083,  1085,  1087,  1089,  1091,  1093,  1095,  1097,
    1099,  1101,  1103,  1105,  1107,  1109,  1111,  1114,  1118,  1119,
    1122,  1125,  1127,  1129,  1133,  1135,  1137,  1139,  1141,  1143,
    1145,  1147,  1149,  1151,  1153,  1155,  1157,  1159,  1161,  1163,
    1165,  1167,  1169,  1171,  1174,  1177,  1179,  1182,  1185,  1187,
    1190,  1193,  1195,  1198,  1201,  1203,  1206,  1209,  1211,  1213,
    1217,  1221,  1222,  1225,  1228,  1235,  1236,  1239,  1240,  1244,
    1245,  1247,  1249,  1254,  1256,  1259,  1261,  1263,  1264,  1266,
    1270,  1272,  1275,  1277,  1280,  1283,  1284,  1286,  1288,  1292,
    1294,  1298,  1299,  1308,  1310,  1313,  1315,  1319,  1320,  1324,
    1327,  1332,  1335,  1336,  1337,  1343,  1344,  1345,  1351,  1352,
    1353,  1359,  1360,  1362,  1364,  1367,  1373,  1374,  1377,  1380,
    1384,  1386,  1388,  1391,  1394,  1397,  1398,  1400,  1402,  1405,
    1414,  1415,  1419,  1420,  1425,  1426,  1431,  1432,  1436,  1437,
    1441,  1443,  1448,  1451,  1453,  1455,  1456,  1459,  1464,  1465,
    1468,  1470,  1472,  1474,  1476,  1478,  1480,  1482,  1484,  1486,
    1488,  1490,  1492,  1494,  1496,  1498,  1500,  1504,  1506,  1508,
    1510,  1512,  1514,  1516,  1518,  1523,  1528,  1531,  1533,  1535,
    1538,  1542,  1544,  1548,  1555,  1558,  1562,  1565,  1567,  1570,
    1573,  1575,  1578,  1579,  1581,  1583,  1588,  1591,  1592,  1594,
    1596,  1597,  1598,  1599,  1606,  1607,  1609,  1611,  1614,  1616,
    1617,  1623,  1624,  1627,  1629,  1631,  1633,  1635,  1638,  1641,
    1643,  1645,  1647,  1649,  1651,  1653,  1655,  1657,  1659,  1661,
    1667,  1673,  1677,  1681,  1683,  1685,  1687,  1689,  1691,  1693,
    1695,  1698,  1701,  1704,  1705,  1707,  1709,  1711,  1713,  1714,
    1716,  1718,  1720,  1722,  1726,  1727,  1728,  1729,  1739,  1740,
    1741,  1745,  1746,  1750,  1752,  1755,  1760,  1761,  1764,  1767,
    1768,  1772,  1776,  1781,  1785,  1786,  1788,  1789,  1792,  1793,
    1794,  1802,  1803,  1806,  1808,  1810,  1812,  1815,  1817,  1822,
    1825,  1827,  1829,  1830,  1832,  1833,  1834,  1838,  1839,  1842,
    1844,  1846,  1848,  1850,  1852,  1854,  1856,  1858,  1860,  1862,
    1864,  1866,  1868,  1870,  1872,  1874,  1876,  1878,  1880,  1882,
    1884,  1886,  1888,  1890,  1892,  1894,  1896,  1898,  1900,  1902,
    1904,  1906,  1908,  1910,  1912,  1914,  1916,  1918,  1920,  1922,
    1924,  1926,  1928,  1930,  1932,  1934,  1936,  1938,  1940,  1942,
    1943,  1948,  1953,  1958,  1962,  1966,  1970,  1975,  1979,  1984,
    1988,  1992,  1996,  2001,  2007,  2011,  2016,  2020,  2024,  2025,
    2029,  2033,  2036,  2039,  2042,  2046,  2050,  2054,  2055,  2058,
    2060,  2063,  2065,  2067,  2069,  2071,  2073,  2075,  2077,  2081,
    2085,  2089,  2093,  2095,  2097,  2099,  2101,  2103,  2105,  2106,
    2108,  2109,  2114,  2119,  2125,  2132,  2133,  2136,  2137,  2139,
    2140,  2144,  2148,  2154,  2155,  2158,  2161,  2162,  2168,  2169,
    2172,  2173,  2182,  2183,  2184,  2188,  2190,  2193,  2196,  2200,
    2201,  2204,  2207,  2210,  2211,  2214,  2217,  2218,  2219,  2223,
    2224,  2225,  2229,  2230,  2232,  2233,  2237,  2238,  2241,  2242,
    2246,  2247,  2251,  2252,  2254,  2258,  2262,  2265,  2267,  2269,
    2270,  2275,  2280,  2281,  2283,  2285,  2287,  2289,  2291,  2292,
    2299,  2300,  2302,  2303,  2308,  2309,  2314,  2318,  2322,  2326,
    2330,  2335,  2342,  2349,  2356,  2363,  2364,  2367,  2370,  2372,
    2375,  2377,  2379,  2382,  2385,  2387,  2389,  2391,  2393,  2395,
    2399,  2403,  2407,  2411,  2413,  2415,  2416,  2418,  2419,  2424,
    2429,  2436,  2443,  2452,  2461,  2462,  2464,  2465,  2470,  2471,
    2477,  2479,  2483,  2485,  2487,  2489,  2492,  2494,  2497,  2498,
    2502,  2503,  2504,  2508,  2511,  2515,  2517,  2521,  2524,  2526,
    2528,  2530,  2531,  2534,  2535,  2537,  2538,  2542,  2543,  2545,
    2547,  2550,  2552,  2554,  2555,  2559,  2560,  2564,  2565,  2571,
    2572,  2576,  2577,  2580,  2581,  2582,  2591,  2595,  2596,  2597,
    2601,  2602,  2604,  2605,  2613,  2614,  2617,  2618,  2622,  2626,
    2627,  2630,  2632,  2635,  2640,  2642,  2644,  2646,  2648,  2650,
    2652,  2654,  2655,  2657,  2658,  2662,  2663,  2668,  2670,  2672,
    2674,  2676,  2679,  2681,  2683,  2685,  2686,  2690,  2692,  2695,
    2698,  2701,  2703,  2705,  2707,  2710,  2713,  2715,  2718,  2723,
    2726,  2727,  2729,  2731,  2733,  2735,  2740,  2746,  2747,  2752,
    2753,  2755,  2756,  2760,  2761,  2765,  2769,  2774,  2775,  2780,
    2785,  2792,  2793,  2795,  2796,  2800,  2801,  2807,  2809,  2811,
    2813,  2815,  2816,  2820,  2821,  2825,  2828,  2829,  2833,  2836,
    2837,  2842,  2845,  2846,  2848,  2850,  2854,  2855,  2857,  2860,
    2864,  2868,  2869,  2873,  2875,  2879,  2887,  2888,  2899,  2900,
    2903,  2904,  2907,  2910,  2914,  2918,  2921,  2922,  2926,  2927,
    2929,  2931,  2932,  2934,  2935,  2940,  2941,  2949,  2950,  2952,
    2953,  2961,  2962,  2965,  2969,  2970,  2972,  2974,  2975,  2980,
    2985,  2986,  2994,  2995,  2998,  2999,  3000,  3005,  3007,  3010,
    3011,  3016,  3017,  3019,  3020,  3024,  3026,  3028,  3030,  3032,
    3034,  3039,  3044,  3048,  3053,  3055,  3057,  3059,  3062,  3066,
    3068,  3071,  3075,  3079,  3080,  3084,  3085,  3093,  3094,  3101,
    3102,  3105,  3106,  3109,  3110,  3114,  3115,  3118,  3123,  3124,
    3127,  3132,  3133,  3134,  3142,  3143,  3148,  3151,  3154,  3157,
    3160,  3163,  3164,  3166,  3167,  3172,  3175,  3176,  3179,  3182,
    3183,  3192,  3194,  3197,  3199,  3203,  3207,  3208,  3212,  3213,
    3215,  3216,  3221,  3226,  3233,  3240,  3241,  3243,  3246,  3247,
    3249,  3250,  3254,  3255,  3263,  3264,  3269,  3270,  3272,  3274,
    3275,  3285,  3286,  3290,  3292,  3296,  3299,  3302,  3305,  3309,
    3310,  3314,  3315,  3319,  3320,  3324,  3325,  3327,  3329,  3331,
    3333,  3342,  3343,  3345,  3347,  3349,  3351,  3353,  3355,  3356,
    3358,  3359,  3361,  3363,  3365,  3367,  3369,  3371,  3373,  3374,
    3376,  3382,  3384,  3387,  3393,  3394,  3403,  3404,  3407,  3408,
    3413,  3417,  3421,  3423,  3425,  3426,  3428,  3430,  3431,  3433,
    3436,  3439,  3440,  3441,  3445,  3446,  3447,  3451,  3454,  3455,
    3456,  3460,  3461,  3462,  3466,  3469,  3470,  3471,  3475,  3476,
    3477,  3481,  3483,  3485,  3488,  3489,  3493,  3494,  3498,  3500,
    3502,  3505,  3506,  3510,  3511,  3515,  3516,  3518,  3520,  3522,
    3525,  3526,  3530,  3531,  3535,  3536,  3540,  3542,  3544,  3545,
    3548,  3551,  3554,  3557,  3560,  3563,  3566,  3569,  3572,  3575,
    3578,  3581,  3584,  3587,  3590,  3593,  3596,  3599,  3602,  3605,
    3606,  3609,  3612,  3615,  3618,  3621,  3624,  3627,  3630,  3633,
    3636,  3639,  3642,  3645,  3648,  3651,  3654,  3657,  3660,  3663,
    3666,  3669,  3672,  3675,  3678,  3681,  3684,  3687,  3689,  3692,
    3694,  3696,  3699,  3701,  3704,  3706,  3712,  3717,  3719,  3725,
    3730,  3732,  3736,  3737,  3739,  3741,  3743,  3747,  3751,  3755,
    3759,  3762,  3765,  3769,  3773,  3775,  3779,  3781,  3784,  3787,
    3789,  3791,  3793,  3796,  3798,  3800,  3803,  3805,  3806,  3809,
    3811,  3813,  3815,  3819,  3821,  3823,  3826,  3828,  3830,  3833,
    3834,  3836,  3838,  3840,  3842,  3844,  3847,  3849,  3853,  3855,
    3858,  3860,  3864,  3868,  3872,  3877,  3881,  3883,  3885,  3887,
    3889,  3893,  3897,  3901,  3903,  3905,  3907,  3909,  3911,  3913,
    3915,  3917,  3919,  3921,  3923,  3925,  3927,  3929,  3931,  3933,
    3935,  3937,  3939,  3941,  3943,  3946,  3949,  3953,  3955,  3959,
    3963,  3968,  3974,  3976,  3978,  3981,  3983,  3987,  3989,  3991,
    3993,  3995,  3997,  3999,  4001,  4004,  4007,  4013,  4019,  4025,
    4031,  4037,  4043,  4049,  4054,  4060,  4063,  4064,  4069,  4075,
    4076,  4080,  4081,  4083,  4085,  4089,  4093,  4095,  4099,  4101,
    4105,  4106,  4107,  4109,  4110,  4112,  4113,  4115,  4116,  4118,
    4120,  4121,  4123,  4124,  4126,  4127,  4129,  4130,  4133,  4135,
    4137,  4140,  4143,  4146,  4148,  4151,  4153,  4154,  4156,  4157,
    4159,  4160,  4162,  4163,  4165,  4166,  4168,  4169,  4171,  4172,
    4174,  4175,  4177,  4178,  4180,  4181,  4183,  4184,  4186,  4187,
    4189,  4190,  4192,  4193,  4195,  4196,  4198,  4199,  4201,  4202,
    4204,  4205,  4207,  4209,  4210,  4212,  4213,  4215,  4217,  4218,
    4220,  4221,  4223,  4224,  4226,  4227,  4229,  4230,  4232,  4233,
    4235,  4236,  4238,  4241,  4242,  4244,  4245,  4247,  4248,  4250,
    4251,  4253,  4254,  4256,  4257,  4259,  4260,  4262,  4265,  4266,
    4268,  4269,  4271,  4272,  4274,  4275,  4277,  4278,  4280,  4281,
    4283,  4284,  4286,  4287,  4289,  4290
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     464,     0,    -1,    -1,   465,   466,     0,    -1,   467,    -1,
     466,   467,    -1,   468,    -1,   474,    -1,    -1,    -1,   481,
     489,   469,   594,   470,   736,   477,   478,    -1,    -1,    -1,
     481,   489,   472,   594,   473,   736,   477,   479,    -1,    -1,
      -1,   483,   489,   475,   594,   476,   736,   480,    -1,    -1,
     471,    -1,   477,   471,    -1,    -1,   139,   484,   455,    -1,
     139,   484,   455,    -1,   135,   484,   455,    -1,    -1,   311,
     455,   484,   485,   482,   486,   455,    -1,   183,   455,   484,
     485,   455,    -1,   312,    -1,   236,    -1,    -1,    27,   236,
      -1,    -1,  1147,   487,  1159,    -1,    73,    -1,    73,   488,
      -1,   488,    -1,   406,    -1,   322,    -1,    -1,   150,   120,
     455,   490,   544,    -1,    -1,    83,   356,   455,   491,    -1,
      -1,   491,   492,    -1,   493,    -1,   497,    -1,   510,    -1,
     505,    -1,   377,   455,   494,    -1,    -1,   496,   455,    -1,
     496,   495,   455,    -1,   495,   455,    -1,  1173,   107,   249,
      -1,   442,    -1,   275,   455,   498,    -1,    -1,   496,   455,
      -1,   496,   499,   455,    -1,   499,   455,    -1,   500,    -1,
     499,   500,    -1,   501,    -1,   503,    -1,   504,    -1,   245,
     372,  1147,  1107,   502,    -1,    56,    -1,   443,    -1,  1159,
    1130,  1147,  1085,    -1,   358,  1147,  1107,    -1,   337,   455,
     506,    -1,    -1,   507,   455,    -1,   508,    -1,   507,   508,
      -1,   182,   509,   211,    -1,   182,     9,   211,    -1,   236,
      -1,   509,   236,    -1,   379,   455,   511,    -1,    -1,   512,
      -1,   512,   455,    -1,   513,    -1,   512,   513,    -1,   514,
      -1,   521,    -1,   530,    -1,   537,    -1,   534,    -1,   538,
      -1,   539,    -1,   540,    -1,   541,    -1,   542,    -1,   543,
      -1,   442,  1147,    96,    -1,    -1,   442,  1147,  1089,   515,
     517,    -1,    -1,   442,  1147,   516,   518,    -1,    25,  1147,
    1089,    -1,    26,  1147,  1089,    -1,   151,  1147,  1089,    -1,
     152,  1147,  1089,    -1,    -1,   517,   519,    -1,   519,    -1,
     518,   519,    -1,   520,  1166,  1147,  1089,    -1,   280,    -1,
     278,    -1,    -1,    11,  1089,   522,  1147,   523,    -1,   255,
      -1,   381,    -1,   382,    -1,   124,    -1,   524,    -1,   525,
      -1,   524,   525,    -1,   528,    -1,   528,   400,   528,    -1,
      -1,   528,    17,   526,   527,    -1,   529,    -1,   527,    17,
     529,    -1,   236,    -1,   378,    -1,   448,    -1,   315,    -1,
     195,    -1,   243,    -1,   236,    -1,   378,    -1,   448,    -1,
     315,    -1,   195,    -1,   243,    -1,   392,  1140,   531,    -1,
     532,  1148,   533,    -1,  1089,    -1,   532,  1089,    -1,  1107,
      -1,   533,  1107,    -1,    57,  1089,  1147,   535,    -1,   536,
      -1,   535,   536,    -1,  1110,    -1,  1110,   400,  1110,    -1,
     237,  1089,  1147,  1085,    -1,    97,  1163,  1147,   236,    -1,
     108,  1147,    68,    -1,    99,  1147,  1085,    -1,    96,   384,
    1147,  1085,    -1,   352,  1147,  1085,    -1,   162,  1147,  1085,
      -1,    -1,   208,   356,   455,   547,   582,    -1,    -1,   169,
     455,   545,   548,    -1,    -1,   216,   455,   546,   583,    -1,
      -1,   169,   455,   548,    -1,    -1,   548,   549,    -1,    -1,
     359,  1124,  1089,   550,   551,   455,    -1,    -1,   551,   552,
      -1,   553,    -1,   558,    -1,   560,    -1,   565,    -1,   566,
      -1,   568,    -1,   572,    -1,   574,    -1,   575,    -1,   576,
      -1,   577,    -1,   578,    -1,   579,    -1,     1,    -1,   581,
      -1,    29,  1171,   555,   554,   556,    -1,    29,  1171,   555,
     117,    -1,    29,  1171,   555,   305,    -1,    -1,   117,    -1,
     305,    -1,    -1,   167,    -1,   123,    -1,   236,    -1,   118,
      -1,  1152,   557,    -1,  1104,    -1,   557,  1104,    -1,     4,
    1153,  1147,   559,    -1,   364,    -1,   123,    -1,   316,    -1,
      19,   319,  1149,  1147,  1085,  1120,    -1,    19,   319,  1149,
    1147,  1085,   564,   561,  1120,    -1,    -1,   562,   563,    -1,
     561,   563,    -1,  1085,    -1,    -1,   376,  1147,    -1,   456,
      -1,  1130,  1147,   442,    -1,   567,   384,  1147,  1085,  1087,
      -1,    -1,   405,    -1,   374,    -1,   240,  1153,  1147,   569,
      -1,   244,   570,    -1,    32,   570,    -1,   164,    -1,    -1,
     441,   240,   280,   571,    -1,   441,   240,   280,   251,   571,
      -1,   441,   347,    -1,   319,    -1,   321,    -1,   286,  1147,
     573,    -1,   573,    -1,   202,    -1,   319,  1137,   364,    -1,
     364,    -1,   326,    -1,   233,   364,    -1,   292,  1139,  1147,
    1088,    -1,   319,   113,  1147,   381,    -1,   319,  1149,  1147,
    1085,    -1,   319,  1149,  1147,  1085,   564,   561,    -1,   326,
    1149,  1147,  1085,    -1,   339,  1107,  1134,    -1,   339,   260,
      -1,   366,  1173,   580,    -1,     9,  1158,    -1,   260,  1158,
      -1,   318,   281,    -1,   261,  1149,  1147,  1085,    -1,    -1,
     216,   455,   583,    -1,    -1,   584,   455,    -1,   584,    -1,
     592,    -1,   585,    -1,   584,   585,    -1,   586,    -1,   588,
      -1,   350,   587,  1134,  1144,  1076,    -1,    -1,   319,    -1,
     374,    -1,   375,    -1,   251,  1143,  1167,  1141,   589,    -1,
     590,    -1,   589,   590,    -1,  1077,   591,    -1,    -1,   301,
    1107,    -1,   592,   455,    -1,   593,    -1,   592,   593,    -1,
      22,    72,  1156,  1084,    -1,    22,   101,  1155,   236,   410,
     280,  1084,    -1,    22,    93,   403,  1085,   280,  1084,    -1,
      22,   178,   403,  1085,   280,  1084,    -1,    22,    60,   280,
    1084,    -1,    -1,   102,   120,   455,   595,   626,   679,   681,
     683,   724,    -1,    -1,    -1,   405,   356,   455,   596,   598,
      -1,    -1,   601,   597,   600,    -1,    -1,   598,   599,    -1,
     601,   602,   628,    -1,   602,   628,    -1,   600,   599,    -1,
     168,    -1,   354,    -1,    -1,  1077,   603,   604,   455,    -1,
      -1,   604,   605,    -1,  1147,   167,    -1,  1147,   188,    -1,
     606,    -1,   608,    -1,   612,    -1,   614,    -1,   616,    -1,
     617,    -1,   623,    -1,   624,    -1,   625,    -1,     1,    -1,
      47,  1141,  1107,   611,   607,    -1,    -1,   321,    -1,    56,
      -1,   319,  1141,  1107,  1140,    -1,   319,  1141,  1107,   403,
    1107,  1140,    -1,   319,  1147,   436,  1146,  1165,   610,   611,
    1140,   609,    -1,    -1,   114,  1156,  1085,    -1,    -1,  1145,
    1107,    -1,    -1,   403,  1107,    -1,   219,  1128,   613,    -1,
     380,    -1,   279,    -1,   435,   277,   442,  1147,   615,    -1,
     435,   277,   170,  1147,   615,    -1,   236,    -1,  1104,    -1,
     102,  1128,  1086,    -1,   231,  1147,  1088,  1151,   618,    -1,
      -1,   618,   619,    -1,   620,    -1,   621,    -1,   622,    -1,
    1173,   174,  1136,  1088,  1151,    -1,  1136,   409,  1088,  1151,
      -1,  1136,    48,  1088,    -1,   320,  1153,  1147,   442,    -1,
      62,  1147,   442,    -1,   332,  1147,   723,    -1,   334,  1133,
     723,    -1,    -1,    -1,   444,   356,   455,   627,   628,    -1,
      -1,   629,    -1,    -1,   630,   631,    -1,  1118,   632,    -1,
     631,  1118,   632,    -1,   631,   455,    -1,   642,    -1,    -1,
     635,   638,   633,   643,   637,    -1,    -1,   636,   638,   634,
     672,    -1,   227,    -1,   228,    -1,    -1,   236,    -1,    -1,
     171,    -1,   442,    -1,   442,    -1,    -1,  1147,   188,    -1,
    1108,    -1,   225,  1155,  1103,    -1,    50,  1155,  1103,    -1,
     635,   639,    84,   640,  1135,   641,    -1,    -1,   643,   644,
      -1,   645,    -1,   646,    -1,   648,    -1,   649,    -1,   650,
      -1,   652,    -1,   654,    -1,   666,    -1,   667,    -1,   669,
      -1,   670,    -1,   671,    -1,   677,    -1,   678,    -1,     1,
      -1,   323,  1103,    -1,  1147,   167,   647,    -1,    -1,    27,
     236,    -1,  1147,   188,    -1,   298,    -1,   651,    -1,   432,
    1147,   651,    -1,    37,    -1,    74,    -1,    76,    -1,    77,
      -1,    78,    -1,    79,    -1,    80,    -1,    81,    -1,   118,
      -1,   201,    -1,   291,    -1,   300,    -1,   313,    -1,   371,
      -1,   369,    -1,   370,    -1,   421,    -1,   419,    -1,   420,
      -1,    39,   368,    -1,    39,   418,    -1,    39,    -1,    42,
     368,    -1,    42,   418,    -1,    42,    -1,    41,   368,    -1,
      41,   418,    -1,    41,    -1,    40,   368,    -1,    40,   418,
      -1,    40,    -1,    38,   368,    -1,    38,   418,    -1,    38,
      -1,   253,    -1,  1164,   223,  1126,    -1,  1164,   411,  1126,
      -1,    -1,   658,   662,    -1,   663,   657,    -1,   276,  1107,
     655,  1170,   656,   653,    -1,    -1,   403,  1107,    -1,    -1,
     114,  1156,  1085,    -1,    -1,   658,    -1,   660,    -1,   661,
    1149,  1147,  1084,    -1,   659,    -1,   660,   659,    -1,    28,
      -1,   115,    -1,    -1,   663,    -1,   202,  1138,   664,    -1,
     665,    -1,   664,   665,    -1,   442,    -1,   217,  1161,    -1,
     393,   668,    -1,    -1,   224,    -1,   346,    -1,    43,  1172,
     448,    -1,    34,    -1,   435,  1147,  1108,    -1,    -1,   435,
    1148,   674,   673,  1172,  1162,  1171,   676,    -1,   675,    -1,
     674,   675,    -1,  1108,    -1,  1108,   400,  1108,    -1,    -1,
     404,  1147,  1108,    -1,   330,  1104,    -1,   330,  1104,   400,
    1104,    -1,    21,   225,    -1,    -1,    -1,   239,   356,   455,
     680,   628,    -1,    -1,    -1,   235,   356,   455,   682,   628,
      -1,    -1,    -1,   332,   356,   455,   684,   685,    -1,    -1,
     686,    -1,   687,    -1,   686,   687,    -1,   317,   723,   688,
     455,   702,    -1,    -1,   688,   689,    -1,  1147,   188,    -1,
      61,  1147,  1099,    -1,   690,    -1,   694,    -1,    88,   691,
      -1,    89,   691,    -1,   692,   693,    -1,    -1,   172,    -1,
    1102,    -1,   693,  1102,    -1,   293,  1148,   700,   695,   696,
     697,   698,   699,    -1,    -1,   193,  1147,  1107,    -1,    -1,
     173,   116,  1147,  1107,    -1,    -1,   220,    91,  1147,  1107,
      -1,    -1,   221,  1147,  1107,    -1,    -1,   174,  1147,  1107,
      -1,  1107,    -1,  1107,   701,  1107,    67,    -1,  1107,   701,
      -1,   233,    -1,   234,    -1,    -1,   702,   703,    -1,   635,
     638,   704,   455,    -1,    -1,   704,   705,    -1,   706,    -1,
     708,    -1,   715,    -1,   649,    -1,   650,    -1,   652,    -1,
     666,    -1,   709,    -1,   669,    -1,   720,    -1,   710,    -1,
     671,    -1,   713,    -1,   721,    -1,   654,    -1,   714,    -1,
     414,  1147,   707,    -1,   336,    -1,   295,    -1,    91,    -1,
     116,    -1,    90,    -1,   294,    -1,   335,    -1,   258,   192,
    1147,  1107,    -1,    66,  1154,  1147,  1107,    -1,    66,   271,
      -1,    67,    -1,   711,    -1,   710,   711,    -1,   390,  1155,
     712,    -1,  1085,    -1,   303,   438,  1057,    -1,   436,  1102,
     180,  1093,    49,  1093,    -1,   716,   717,    -1,   233,   719,
    1148,    -1,   234,  1133,    -1,   718,    -1,   717,   718,    -1,
     299,  1107,    -1,  1107,    -1,   258,   293,    -1,    -1,   270,
      -1,   271,    -1,   376,  1147,  1102,  1125,    -1,   192,   722,
      -1,    -1,   203,    -1,   442,    -1,    -1,    -1,    -1,   351,
     356,   455,   725,   726,   727,    -1,    -1,   728,    -1,   729,
      -1,   728,   729,    -1,   642,    -1,    -1,   635,   638,   730,
     731,   455,    -1,    -1,   731,   732,    -1,    44,    -1,    45,
      -1,    36,    -1,    46,    -1,   158,   153,    -1,   158,   155,
      -1,   194,    -1,   242,    -1,   343,    -1,   415,    -1,   290,
      -1,    31,    -1,   357,    -1,   338,    -1,   181,    -1,   314,
      -1,   233,  1154,  1147,   733,  1101,    -1,    66,  1154,  1147,
     734,  1101,    -1,   176,  1147,  1101,    -1,    33,  1147,  1101,
      -1,   650,    -1,   669,    -1,   666,    -1,   652,    -1,   671,
      -1,   649,    -1,   735,    -1,   434,  1102,    -1,   180,  1100,
      -1,   403,  1102,    -1,    -1,   299,    -1,   449,    -1,   247,
      -1,   450,    -1,    -1,   299,    -1,   449,    -1,   247,    -1,
     450,    -1,   276,  1107,  1170,    -1,    -1,    -1,    -1,   307,
     120,   739,   747,   455,   737,   748,   738,   750,    -1,    -1,
      -1,   434,   740,   742,    -1,    -1,    54,   741,   742,    -1,
     743,    -1,   742,   743,    -1,   744,   745,   746,   442,    -1,
      -1,  1138,   325,    -1,  1138,   435,    -1,    -1,   372,  1147,
      31,    -1,   372,  1147,   110,    -1,   418,   372,  1147,  1107,
      -1,   372,  1147,  1107,    -1,    -1,   283,    -1,    -1,   341,
     442,    -1,    -1,    -1,   109,   455,   749,   750,   126,   109,
     455,    -1,    -1,   750,   751,    -1,   752,    -1,   753,    -1,
     754,    -1,   760,   455,    -1,     1,    -1,   755,   356,   756,
     455,    -1,   442,   455,    -1,   755,    -1,   442,    -1,    -1,
     236,    -1,    -1,    -1,   758,   759,   760,    -1,    -1,   760,
     761,    -1,   762,    -1,   772,    -1,   777,    -1,   781,    -1,
     784,    -1,   797,    -1,   800,    -1,   810,    -1,   805,    -1,
     811,    -1,   812,    -1,   815,    -1,   817,    -1,   824,    -1,
     828,    -1,   830,    -1,   845,    -1,   848,    -1,   850,    -1,
     852,    -1,   855,    -1,   857,    -1,   863,    -1,   872,    -1,
     874,    -1,   891,    -1,   893,    -1,   896,    -1,   900,    -1,
     906,    -1,   916,    -1,   923,    -1,   925,    -1,   928,    -1,
     932,    -1,   933,    -1,   944,    -1,   955,    -1,   965,    -1,
     971,    -1,   974,    -1,   980,    -1,   984,    -1,   986,    -1,
     988,    -1,   990,    -1,   993,    -1,  1004,    -1,  1017,    -1,
     259,    -1,    -1,     3,   763,   764,   771,    -1,  1102,   765,
     768,  1024,    -1,  1102,   180,   160,   218,    -1,  1102,   180,
     234,    -1,  1102,   180,    67,    -1,  1102,   180,   103,    -1,
    1102,   180,   103,   447,    -1,  1102,   180,   104,    -1,  1102,
     180,   104,   446,    -1,  1102,   180,   105,    -1,  1102,   180,
     401,    -1,  1102,   180,    69,    -1,  1102,   180,   152,  1024,
      -1,  1102,   180,   150,  1097,  1024,    -1,  1102,   180,    25,
      -1,  1102,   180,    26,  1024,    -1,  1102,   180,  1079,    -1,
    1102,   180,   442,    -1,    -1,  1136,   766,   767,    -1,  1136,
     767,   766,    -1,  1136,   766,    -1,  1136,   767,    -1,    30,
    1097,    -1,   233,  1154,  1099,    -1,    66,  1154,  1099,    -1,
     301,  1154,  1099,    -1,    -1,   441,   769,    -1,   770,    -1,
     769,   770,    -1,    36,    -1,    46,    -1,   194,    -1,   242,
      -1,   343,    -1,   415,    -1,   290,    -1,   176,  1147,  1101,
      -1,    33,  1147,  1101,    -1,   353,   424,  1056,    -1,   353,
     121,  1056,    -1,    31,    -1,   181,    -1,   338,    -1,   357,
      -1,   425,    -1,   314,    -1,    -1,   127,    -1,    -1,     5,
     773,   774,   776,    -1,  1092,   403,  1072,  1030,    -1,  1092,
     775,   187,  1072,  1030,    -1,    94,  1102,   403,  1102,  1125,
    1030,    -1,    -1,   403,  1093,    -1,    -1,   128,    -1,    -1,
      10,   778,   779,    -1,   442,  1121,   780,    -1,  1058,    56,
    1121,   341,  1091,    -1,    -1,   341,  1091,    -1,    18,   782,
      -1,    -1,   782,  1081,   403,   783,  1081,    -1,    -1,   309,
     403,    -1,    -1,    51,   785,  1100,   786,   791,   792,   794,
     796,    -1,    -1,    -1,   434,   787,   788,    -1,   789,    -1,
     788,   789,    -1,   790,   279,    -1,   790,   745,  1093,    -1,
      -1,  1138,   325,    -1,  1138,    86,    -1,  1138,   435,    -1,
      -1,   341,  1102,    -1,   187,  1102,    -1,    -1,    -1,  1011,
     793,   757,    -1,    -1,    -1,  1012,   795,   757,    -1,    -1,
     129,    -1,    -1,    52,   798,   799,    -1,    -1,   799,  1099,
      -1,    -1,    59,   801,   802,    -1,    -1,   802,  1077,   803,
      -1,    -1,   804,    -1,   804,  1144,   329,    -1,  1173,   260,
     344,    -1,  1173,   240,    -1,   324,    -1,   416,    -1,    -1,
      75,   806,   807,   808,    -1,  1072,   809,  1058,  1030,    -1,
      -1,   130,    -1,   456,    -1,   156,    -1,    71,    -1,    87,
      -1,    -1,   111,   813,  1077,  1160,  1050,   814,    -1,    -1,
     131,    -1,    -1,   111,   816,   405,  1076,    -1,    -1,   118,
     818,   819,   823,    -1,  1099,   429,  1025,    -1,  1099,   430,
    1025,    -1,  1099,   427,  1025,    -1,  1099,   428,  1025,    -1,
    1092,   765,   820,  1025,    -1,  1092,   765,   426,  1079,   820,
    1025,    -1,  1092,   765,   426,   442,   820,  1025,    -1,  1092,
     765,   426,   305,   820,  1025,    -1,  1092,   765,   426,    96,
     820,  1025,    -1,    -1,  1173,   269,    -1,   441,   821,    -1,
     822,    -1,   821,   822,    -1,    36,    -1,    46,    -1,   158,
     153,    -1,   158,   155,    -1,   194,    -1,   242,    -1,   343,
      -1,   415,    -1,   290,    -1,   176,  1147,  1101,    -1,    33,
    1147,  1101,    -1,   353,   424,  1056,    -1,   353,   121,  1056,
      -1,    44,    -1,    45,    -1,    -1,   132,    -1,    -1,   119,
     825,   826,   827,    -1,  1093,   210,  1072,  1030,    -1,  1093,
     210,  1093,   187,  1072,  1030,    -1,  1093,    49,  1093,   187,
    1072,  1030,    -1,  1093,   210,  1093,   187,  1073,   328,  1073,
    1030,    -1,  1093,    49,  1093,   187,  1073,   328,  1073,  1030,
      -1,    -1,   133,    -1,    -1,   149,   829,   236,   786,    -1,
      -1,   161,   831,   832,   834,   844,    -1,   833,    -1,   832,
    1132,   833,    -1,  1058,    -1,   408,    -1,   404,    -1,   835,
     838,    -1,   836,    -1,   835,   836,    -1,    -1,   840,   837,
     757,    -1,    -1,    -1,   440,   839,   757,    -1,   438,   841,
      -1,   840,   438,   841,    -1,   842,    -1,   841,  1132,   842,
      -1,  1059,   843,    -1,    21,    -1,   408,    -1,   404,    -1,
      -1,   400,  1058,    -1,    -1,   134,    -1,    -1,   165,   846,
     847,    -1,    -1,   310,    -1,   297,    -1,   297,   100,    -1,
     356,    -1,   296,    -1,    -1,   179,   849,  1090,    -1,    -1,
     186,   851,  1102,    -1,    -1,   189,  1171,   853,  1080,   854,
      -1,    -1,   114,  1156,  1102,    -1,    -1,   190,   856,    -1,
      -1,    -1,   197,   858,  1057,  1169,   859,   757,   860,   862,
      -1,   197,     1,   136,    -1,    -1,    -1,   125,   861,   757,
      -1,    -1,   136,    -1,    -1,   204,   864,  1090,   865,   866,
     867,   871,    -1,    -1,  1173,   171,    -1,    -1,     9,  1171,
     435,    -1,   870,  1171,   435,    -1,    -1,   331,   868,    -1,
     869,    -1,   868,   869,    -1,   870,  1142,    49,  1093,    -1,
      12,    -1,    15,    -1,   272,    -1,    16,    -1,   273,    -1,
     253,    -1,   254,    -1,    -1,   110,    -1,    -1,   206,   873,
     693,    -1,    -1,   209,   875,   876,   877,    -1,  1102,    -1,
    1108,    -1,  1111,    -1,   878,    -1,   877,   878,    -1,   879,
      -1,   883,    -1,   888,    -1,    -1,   394,   880,   881,    -1,
     882,    -1,   881,   882,    -1,  1097,   175,    -1,    56,   889,
      -1,     9,    -1,   223,    -1,   411,    -1,  1097,   889,    -1,
     331,   884,    -1,   885,    -1,   884,   885,    -1,    56,    49,
    1097,   889,    -1,   886,   887,    -1,    -1,     9,    -1,   223,
      -1,   173,    -1,   411,    -1,  1097,    49,  1098,   889,    -1,
      92,  1097,   403,  1098,   889,    -1,    -1,   889,  1021,   890,
    1093,    -1,    -1,   406,    -1,    -1,   246,   892,   957,    -1,
      -1,   250,   894,   895,    -1,  1093,   403,  1090,    -1,    94,
    1093,   403,  1090,    -1,    -1,   252,   897,   898,   899,    -1,
    1093,    49,  1072,  1030,    -1,  1093,    49,  1093,   187,  1072,
    1030,    -1,    -1,   137,    -1,    -1,   282,   901,   902,    -1,
      -1,   902,   903,   904,  1076,   905,    -1,   207,    -1,   288,
      -1,   215,    -1,   166,    -1,    -1,   366,  1173,   580,    -1,
      -1,  1173,   260,   344,    -1,  1173,   240,    -1,    -1,   297,
     907,   908,    -1,   911,   912,    -1,    -1,   912,   909,   757,
     910,    -1,   912,   138,    -1,    -1,   138,    -1,  1081,    -1,
    1081,   400,  1081,    -1,    -1,   177,    -1,  1100,   402,    -1,
     913,   423,  1057,    -1,   913,   436,   914,    -1,    -1,  1173,
     397,  1021,    -1,   915,    -1,   914,     8,   915,    -1,  1102,
     180,  1093,    49,  1093,   423,  1057,    -1,    -1,   318,   917,
    1077,  1122,  1160,   918,   919,   920,   921,   922,    -1,    -1,
     210,  1102,    -1,    -1,   199,   240,    -1,  1173,   240,    -1,
    1173,   260,   240,    -1,  1173,   198,   240,    -1,  1173,   437,
      -1,    -1,   218,  1147,   693,    -1,    -1,  1040,    -1,  1051,
      -1,    -1,   140,    -1,    -1,   327,   924,  1074,  1019,    -1,
      -1,   340,   926,  1077,  1160,   918,  1040,   927,    -1,    -1,
     141,    -1,    -1,   345,   929,  1074,  1019,   930,  1050,   931,
      -1,    -1,  1173,   240,    -1,  1173,   260,   240,    -1,    -1,
     142,    -1,   347,    -1,    -1,   355,   934,   935,   943,    -1,
    1075,   937,   938,   940,    -1,    -1,     9,  1075,   938,   438,
    1058,   936,   757,    -1,    -1,   436,  1102,    -1,    -1,    -1,
    1136,   126,   939,   757,    -1,   941,    -1,   941,   940,    -1,
      -1,   438,  1057,   942,   757,    -1,    -1,   143,    -1,    -1,
     365,   945,   946,    -1,   947,    -1,   948,    -1,   949,    -1,
     951,    -1,   953,    -1,   150,  1097,   403,  1097,    -1,  1090,
     403,   149,  1096,    -1,  1090,   403,  1093,    -1,  1090,   950,
      49,  1093,    -1,   424,    -1,   121,    -1,   952,    -1,   951,
     952,    -1,  1078,   403,   520,    -1,   954,    -1,   953,   954,
      -1,  1090,   403,   408,    -1,  1090,   403,   404,    -1,    -1,
     374,   956,   957,    -1,    -1,  1104,   959,   961,   962,   958,
     963,   964,    -1,    -1,   959,  1156,   661,  1149,  1147,   960,
      -1,    -1,   960,  1104,    -1,    -1,  1129,  1157,    -1,    -1,
    1130,  1147,  1085,    -1,    -1,   434,  1076,    -1,   207,   307,
    1147,   911,    -1,    -1,   187,  1076,    -1,   288,   307,  1147,
     911,    -1,    -1,    -1,   383,   966,  1077,   967,   968,  1050,
     970,    -1,    -1,   218,  1147,   969,   693,    -1,  1123,  1063,
      -1,  1123,  1064,    -1,  1123,  1065,    -1,  1123,  1066,    -1,
    1123,  1067,    -1,    -1,   144,    -1,    -1,   385,   349,   972,
     973,    -1,   385,   236,    -1,    -1,   341,  1093,    -1,   187,
    1093,    -1,    -1,   386,   975,   976,   210,  1102,   978,  1035,
     979,    -1,   977,    -1,   976,   977,    -1,  1093,    -1,   112,
    1138,   372,    -1,   112,  1138,  1093,    -1,    -1,  1173,   300,
    1102,    -1,    -1,   145,    -1,    -1,   389,   981,   982,   983,
      -1,  1092,   180,  1072,  1030,    -1,  1092,   180,  1093,   187,
    1072,  1030,    -1,    94,  1102,   180,  1102,  1125,  1030,    -1,
      -1,   146,    -1,   391,   985,    -1,    -1,   306,    -1,    -1,
     396,   987,   693,    -1,    -1,   412,   989,  1102,   180,  1097,
     403,  1098,    -1,    -1,   417,   991,  1077,   992,    -1,    -1,
     319,    -1,   321,    -1,    -1,   422,   994,  1102,   995,   998,
     978,  1002,  1035,  1003,    -1,    -1,   112,  1138,   996,    -1,
     997,    -1,   996,   284,   997,    -1,  1119,  1097,    -1,   210,
     999,    -1,   998,   999,    -1,  1102,  1000,  1001,    -1,    -1,
     113,  1146,  1102,    -1,    -1,    95,  1146,  1102,    -1,    -1,
     394,  1146,  1102,    -1,    -1,   147,    -1,  1005,    -1,  1014,
      -1,  1016,    -1,   433,  1006,  1008,  1009,  1010,  1013,  1156,
    1007,    -1,    -1,   188,    -1,  1076,    -1,   207,    -1,   288,
      -1,   215,    -1,   166,    -1,    -1,     8,    -1,    -1,   380,
      -1,   163,    -1,   159,    -1,   163,    -1,   289,    -1,   265,
      -1,   267,    -1,    -1,   307,    -1,   433,  1144,   107,  1156,
    1015,    -1,  1081,    -1,     9,   308,    -1,   433,  1006,    35,
     333,  1102,    -1,    -1,   445,  1018,  1074,  1019,   930,  1020,
    1022,  1023,    -1,    -1,   180,  1099,    -1,    -1,  1021,  1131,
    1101,  1150,    -1,  1021,  1131,  1079,    -1,  1021,  1131,   293,
      -1,    35,    -1,     8,    -1,    -1,  1045,    -1,  1051,    -1,
      -1,   148,    -1,  1026,  1028,    -1,  1026,  1028,    -1,    -1,
      -1,   163,  1027,   757,    -1,    -1,    -1,   265,  1029,   757,
      -1,  1031,  1033,    -1,    -1,    -1,   373,  1032,   757,    -1,
      -1,    -1,   268,  1034,   757,    -1,  1036,  1038,    -1,    -1,
      -1,   289,  1037,   757,    -1,    -1,    -1,   267,  1039,   757,
      -1,  1041,    -1,  1043,    -1,  1041,  1043,    -1,    -1,   126,
    1042,   757,    -1,    -1,   263,  1044,   757,    -1,  1046,    -1,
    1048,    -1,  1046,  1048,    -1,    -1,   154,  1047,   757,    -1,
      -1,   264,  1049,   757,    -1,    -1,  1051,    -1,  1052,    -1,
    1054,    -1,  1052,  1054,    -1,    -1,   213,  1053,   757,    -1,
      -1,   266,  1055,   757,    -1,    -1,  1138,  1101,  1150,    -1,
    1058,    -1,  1059,    -1,    -1,  1060,  1061,    -1,  1062,  1093,
      -1,  1061,   457,    -1,  1062,   279,    -1,  1062,   272,    -1,
    1062,    12,    -1,  1062,    13,    -1,  1062,    14,    -1,  1062,
      58,    -1,  1061,   279,    -1,  1061,   272,    -1,  1061,    12,
      -1,  1061,    13,    -1,  1061,    14,    -1,  1061,    58,    -1,
    1062,   302,    -1,  1062,   257,    -1,  1061,   302,    -1,  1061,
     257,    -1,  1061,   448,    -1,    -1,  1061,   214,    -1,  1062,
     214,    -1,  1062,   458,    -1,  1062,   449,    -1,  1062,   450,
      -1,  1062,   454,    -1,  1062,   262,    -1,  1061,   262,    -1,
    1061,   449,    -1,  1061,   450,    -1,  1061,   451,    -1,  1061,
     452,    -1,  1061,   454,    -1,  1061,  1063,    -1,  1061,  1064,
      -1,  1061,  1065,    -1,  1061,  1066,    -1,  1061,  1067,    -1,
    1061,   256,    -1,  1062,  1063,    -1,  1062,  1064,    -1,  1062,
    1065,    -1,  1062,  1066,    -1,  1062,  1067,    -1,  1062,   256,
      -1,  1061,    20,    -1,  1061,   284,    -1,   456,    -1,   156,
    1171,    -1,   157,    -1,   459,    -1,   191,  1168,    -1,   460,
      -1,   226,  1168,    -1,   185,    -1,   191,  1168,   284,   156,
    1171,    -1,   191,  1168,   156,  1171,    -1,   222,    -1,   226,
    1168,   284,   156,  1171,    -1,   226,  1168,   156,  1171,    -1,
    1070,    -1,  1068,  1069,  1070,    -1,    -1,    70,    -1,   360,
      -1,  1094,    -1,  1070,   449,  1070,    -1,  1070,   450,  1070,
      -1,  1070,   451,  1070,    -1,  1070,   452,  1070,    -1,   449,
    1070,    -1,   450,  1070,    -1,  1070,   454,  1070,    -1,   458,
    1070,   457,    -1,   232,    -1,   232,  1127,   442,    -1,  1073,
      -1,  1072,  1073,    -1,  1093,  1125,    -1,  1104,    -1,  1104,
      -1,  1077,    -1,  1076,  1077,    -1,   442,    -1,  1079,    -1,
    1078,  1079,    -1,   248,    -1,    -1,  1080,  1081,    -1,  1082,
      -1,  1104,    -1,  1083,    -1,  1083,  1127,  1083,    -1,   236,
      -1,  1085,    -1,  1084,  1085,    -1,  1104,    -1,  1104,    -1,
    1086,  1104,    -1,    -1,  1085,    -1,  1085,    -1,   236,    -1,
     442,    -1,  1091,    -1,  1090,  1091,    -1,  1102,    -1,     6,
    1155,  1103,    -1,  1093,    -1,  1092,  1093,    -1,  1102,    -1,
     225,  1155,  1103,    -1,   225,  1155,  1109,    -1,   225,  1155,
    1111,    -1,     6,  1155,  1095,  1096,    -1,     6,  1155,  1103,
      -1,  1108,    -1,  1111,    -1,  1071,    -1,  1102,    -1,   225,
    1155,  1103,    -1,   225,  1155,  1109,    -1,   225,  1155,  1111,
      -1,  1109,    -1,  1111,    -1,  1071,    -1,   310,    -1,   149,
      -1,  1103,    -1,   236,    -1,  1102,    -1,  1109,    -1,  1102,
      -1,  1108,    -1,  1102,    -1,   236,    -1,  1102,    -1,   236,
      -1,  1111,    -1,  1102,    -1,  1107,    -1,   448,    -1,  1103,
      -1,  1104,    -1,  1104,  1105,    -1,  1104,  1106,    -1,  1104,
    1105,  1106,    -1,   442,    -1,   442,  1127,  1104,    -1,   458,
    1068,   457,    -1,   458,  1070,   461,   457,    -1,   458,  1070,
     461,  1070,   457,    -1,   236,    -1,  1109,    -1,     9,  1110,
      -1,  1110,    -1,  1109,   462,  1110,    -1,   236,    -1,   378,
      -1,   448,    -1,   315,    -1,   195,    -1,   243,    -1,   407,
      -1,    98,  1112,    -1,   439,  1112,    -1,   431,   458,  1070,
     457,  1112,    -1,   241,   458,  1070,   457,  1112,    -1,   342,
     458,  1070,   457,  1112,    -1,    82,   458,  1068,   457,  1112,
      -1,   387,   458,  1068,   457,  1112,    -1,   388,   458,  1068,
     457,  1112,    -1,   413,   458,  1115,   457,  1112,    -1,   274,
     458,  1116,   457,    -1,   238,   458,  1117,   457,  1112,    -1,
     184,  1113,    -1,    -1,   458,  1070,   461,   457,    -1,   458,
    1070,   461,  1070,   457,    -1,    -1,   458,  1114,   457,    -1,
      -1,  1068,    -1,  1070,    -1,  1070,  1069,   223,    -1,  1070,
    1069,   411,    -1,  1070,    -1,  1070,  1069,  1070,    -1,  1070,
      -1,  1070,  1069,  1085,    -1,    -1,    -1,     9,    -1,    -1,
    1129,    -1,    -1,   205,    -1,    -1,   258,    -1,   304,    -1,
      -1,   262,    -1,    -1,   283,    -1,    -1,   348,    -1,    -1,
     362,  1139,    -1,   200,    -1,   277,    -1,   319,  1147,    -1,
     321,  1133,    -1,   441,   122,    -1,   122,    -1,    63,   363,
      -1,   363,    -1,    -1,     7,    -1,    -1,    17,    -1,    -1,
      23,    -1,    -1,    24,    -1,    -1,    27,    -1,    -1,    30,
      -1,    -1,    37,    -1,    -1,    49,    -1,    -1,    55,    -1,
      -1,    56,    -1,    -1,    85,    -1,    -1,   102,    -1,    -1,
     405,    -1,    -1,   175,    -1,    -1,   180,    -1,    -1,   200,
      -1,    -1,   214,    -1,    -1,   214,    -1,    23,    -1,    -1,
     218,    -1,    -1,   233,    -1,   234,    -1,    -1,   234,    -1,
      -1,   236,    -1,    -1,   249,    -1,    -1,   270,    -1,    -1,
     277,    -1,    -1,   280,    -1,    -1,   285,    -1,   200,   285,
      -1,    -1,   287,    -1,    -1,   310,    -1,    -1,   319,    -1,
      -1,   346,    -1,    -1,   365,    -1,    -1,   367,    -1,    -1,
     367,    -1,   367,   214,    -1,    -1,   372,    -1,    -1,   384,
      -1,    -1,   395,    -1,    -1,   398,    -1,    -1,   399,    -1,
      -1,   402,    -1,    -1,   403,    -1,    -1,   438,    -1,    -1,
     441,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   771,   771,   771,   813,   814,   818,   819,   824,   825,
     823,   833,   834,   832,   842,   843,   841,   848,   849,   850,
     853,   854,   880,   904,   934,   933,   974,  1018,  1019,  1023,
    1024,  1027,  1028,  1032,  1039,  1046,  1050,  1054,  1066,  1067,
    1077,  1078,  1087,  1088,  1092,  1093,  1094,  1095,  1104,  1107,
    1108,  1109,  1110,  1114,  1121,  1130,  1133,  1134,  1135,  1136,
    1140,  1141,  1145,  1146,  1147,  1151,  1158,  1159,  1163,  1170,
    1182,  1185,  1186,  1190,  1191,  1195,  1199,  1206,  1207,  1217,
    1220,  1221,  1222,  1226,  1227,  1231,  1232,  1233,  1234,  1235,
    1236,  1237,  1238,  1239,  1240,  1241,  1248,  1259,  1258,  1270,
    1269,  1278,  1292,  1306,  1320,  1336,  1337,  1341,  1342,  1346,
    1357,  1358,  1366,  1365,  1377,  1378,  1379,  1380,  1381,  1389,
    1390,  1395,  1396,  1398,  1397,  1409,  1410,  1414,  1415,  1416,
    1417,  1418,  1419,  1423,  1424,  1425,  1426,  1427,  1428,  1435,
    1446,  1458,  1459,  1463,  1464,  1471,  1480,  1481,  1485,  1486,
    1500,  1515,  1582,  1593,  1600,  1607,  1613,  1620,  1621,  1625,
    1624,  1634,  1633,  1649,  1650,  1653,  1654,  1659,  1658,  1679,
    1680,  1684,  1685,  1686,  1687,  1688,  1689,  1690,  1691,  1692,
    1693,  1694,  1695,  1696,  1697,  1698,  1705,  1709,  1714,  1721,
    1722,  1723,  1726,  1727,  1731,  1738,  1739,  1746,  1766,  1767,
    1773,  1777,  1778,  1779,  1786,  1806,  1853,  1853,  1857,  1861,
    1877,  1878,  1879,  1885,  1895,  1904,  1906,  1907,  1913,  1917,
    1918,  1919,  1922,  1923,  1924,  1928,  1932,  1933,  1939,  1940,
    1944,  1953,  1962,  1971,  1980,  1995,  2005,  2012,  2016,  2054,
    2061,  2062,  2069,  2073,  2074,  2075,  2081,  2088,  2089,  2092,
    2093,  2094,  2095,  2099,  2100,  2104,  2105,  2111,  2136,  2137,
    2138,  2139,  2145,  2152,  2153,  2157,  2160,  2161,  2167,  2168,
    2169,  2173,  2177,  2181,  2185,  2189,  2199,  2200,  2214,  2215,
    2215,  2218,  2217,  2230,  2231,  2235,  2247,  2256,  2260,  2261,
    2271,  2270,  2288,  2289,  2293,  2300,  2307,  2308,  2309,  2310,
    2311,  2312,  2313,  2314,  2315,  2316,  2323,  2327,  2327,  2327,
    2333,  2345,  2370,  2394,  2395,  2402,  2403,  2407,  2408,  2415,
    2422,  2423,  2430,  2434,  2443,  2444,  2450,  2460,  2478,  2479,
    2483,  2484,  2485,  2489,  2496,  2503,  2513,  2520,  2538,  2542,
    2553,  2554,  2554,  2565,  2566,  2570,  2570,  2587,  2588,  2590,
    2594,  2596,  2595,  2620,  2619,  2644,  2648,  2655,  2657,  2679,
    2684,  2690,  2699,  2707,  2708,  2716,  2717,  2718,  2722,  2742,
    2746,  2755,  2756,  2757,  2758,  2759,  2760,  2761,  2762,  2763,
    2764,  2765,  2766,  2767,  2768,  2769,  2776,  2798,  2820,  2821,
    2833,  2853,  2860,  2861,  2865,  2866,  2867,  2868,  2869,  2870,
    2871,  2872,  2873,  2874,  2875,  2876,  2881,  2886,  2887,  2888,
    2889,  2890,  2891,  2892,  2893,  2894,  2895,  2896,  2897,  2898,
    2899,  2900,  2901,  2902,  2903,  2904,  2912,  2920,  2928,  2935,
    2940,  2950,  2951,  2952,  2956,  2973,  2974,  2977,  2978,  2984,
    2984,  2987,  3011,  3027,  3028,  3032,  3033,  3036,  3036,  3039,
    3046,  3047,  3052,  3062,  3069,  3072,  3073,  3074,  3081,  3088,
    3113,  3117,  3117,  3122,  3123,  3127,  3128,  3131,  3132,  3145,
    3157,  3177,  3191,  3193,  3192,  3212,  3213,  3213,  3226,  3228,
    3227,  3239,  3240,  3244,  3245,  3254,  3261,  3264,  3268,  3272,
    3273,  3274,  3281,  3282,  3286,  3289,  3289,  3292,  3293,  3299,
    3304,  3305,  3308,  3309,  3312,  3313,  3316,  3317,  3320,  3321,
    3325,  3326,  3327,  3331,  3332,  3335,  3336,  3340,  3344,  3345,
    3349,  3350,  3351,  3352,  3353,  3354,  3355,  3356,  3357,  3358,
    3359,  3360,  3361,  3362,  3363,  3364,  3368,  3372,  3373,  3374,
    3375,  3376,  3377,  3378,  3382,  3386,  3387,  3388,  3392,  3393,
    3397,  3401,  3406,  3410,  3414,  3418,  3419,  3423,  3424,  3428,
    3429,  3430,  3433,  3433,  3433,  3436,  3440,  3443,  3443,  3446,
    3453,  3454,  3455,  3454,  3472,  3473,  3477,  3478,  3483,  3485,
    3484,  3520,  3521,  3525,  3526,  3527,  3528,  3529,  3530,  3531,
    3532,  3533,  3534,  3535,  3536,  3537,  3538,  3539,  3540,  3541,
    3545,  3549,  3553,  3557,  3558,  3559,  3560,  3561,  3562,  3563,
    3564,  3571,  3575,  3585,  3588,  3592,  3596,  3600,  3608,  3611,
    3615,  3619,  3623,  3631,  3644,  3646,  3656,  3645,  3683,  3685,
    3684,  3691,  3690,  3699,  3700,  3705,  3712,  3714,  3718,  3728,
    3730,  3738,  3746,  3775,  3806,  3808,  3818,  3823,  3834,  3835,
    3835,  3862,  3863,  3867,  3868,  3869,  3870,  3886,  3898,  3929,
    3966,  3978,  3981,  3982,  3991,  3995,  3991,  4008,  4026,  4030,
    4031,  4032,  4033,  4034,  4035,  4036,  4037,  4038,  4039,  4040,
    4041,  4042,  4043,  4044,  4045,  4046,  4047,  4048,  4049,  4050,
    4051,  4052,  4053,  4054,  4055,  4056,  4057,  4058,  4059,  4060,
    4061,  4062,  4063,  4064,  4065,  4066,  4067,  4068,  4069,  4070,
    4071,  4072,  4073,  4074,  4075,  4076,  4077,  4078,  4079,  4102,
    4101,  4114,  4118,  4122,  4126,  4130,  4134,  4138,  4142,  4146,
    4150,  4154,  4158,  4162,  4166,  4170,  4174,  4178,  4185,  4186,
    4187,  4188,  4189,  4190,  4194,  4198,  4199,  4202,  4203,  4207,
    4208,  4212,  4213,  4214,  4215,  4216,  4217,  4218,  4219,  4223,
    4227,  4231,  4236,  4237,  4238,  4239,  4240,  4241,  4245,  4246,
    4255,  4255,  4261,  4265,  4269,  4275,  4276,  4280,  4281,  4290,
    4290,  4295,  4299,  4306,  4307,  4316,  4322,  4323,  4327,  4327,
    4335,  4335,  4345,  4347,  4346,  4355,  4356,  4361,  4368,  4375,
    4377,  4381,  4389,  4400,  4401,  4402,  4407,  4411,  4410,  4422,
    4426,  4425,  4436,  4437,  4446,  4446,  4450,  4451,  4463,  4463,
    4467,  4468,  4479,  4480,  4481,  4482,  4483,  4486,  4486,  4494,
    4494,  4500,  4507,  4508,  4511,  4511,  4518,  4531,  4544,  4544,
    4555,  4556,  4565,  4565,  4585,  4584,  4597,  4601,  4605,  4609,
    4613,  4617,  4621,  4626,  4630,  4637,  4638,  4639,  4643,  4644,
    4649,  4650,  4651,  4652,  4653,  4654,  4655,  4656,  4657,  4658,
    4662,  4666,  4670,  4675,  4676,  4680,  4681,  4690,  4690,  4696,
    4700,  4704,  4708,  4712,  4719,  4720,  4729,  4729,  4751,  4750,
    4769,  4770,  4781,  4790,  4795,  4803,  4832,  4833,  4839,  4838,
    4854,  4858,  4857,  4872,  4873,  4878,  4879,  4890,  4919,  4920,
    4921,  4924,  4925,  4929,  4930,  4939,  4939,  4944,  4945,  4953,
    4970,  4987,  5005,  5030,  5030,  5043,  5043,  5056,  5056,  5065,
    5069,  5082,  5082,  5095,  5097,  5095,  5108,  5113,  5117,  5116,
    5130,  5131,  5140,  5140,  5148,  5149,  5153,  5154,  5155,  5159,
    5160,  5165,  5166,  5171,  5175,  5176,  5177,  5178,  5179,  5180,
    5181,  5185,  5186,  5195,  5195,  5208,  5207,  5217,  5218,  5219,
    5223,  5224,  5228,  5229,  5230,  5236,  5236,  5241,  5242,  5246,
    5247,  5248,  5249,  5250,  5251,  5257,  5261,  5262,  5266,  5271,
    5275,  5276,  5277,  5278,  5279,  5283,  5309,  5322,  5323,  5327,
    5327,  5335,  5335,  5345,  5345,  5350,  5354,  5366,  5366,  5372,
    5376,  5383,  5384,  5393,  5393,  5397,  5398,  5412,  5413,  5414,
    5415,  5419,  5420,  5424,  5425,  5426,  5438,  5438,  5443,  5448,
    5447,  5457,  5464,  5465,  5469,  5474,  5483,  5486,  5490,  5495,
    5502,  5509,  5510,  5514,  5515,  5520,  5532,  5532,  5561,  5562,
    5566,  5567,  5571,  5575,  5579,  5583,  5590,  5591,  5605,  5606,
    5607,  5611,  5612,  5621,  5621,  5636,  5636,  5647,  5648,  5657,
    5657,  5674,  5675,  5679,  5686,  5687,  5696,  5709,  5709,  5715,
    5720,  5719,  5730,  5731,  5735,  5737,  5736,  5747,  5748,  5753,
    5752,  5763,  5764,  5773,  5773,  5778,  5779,  5780,  5781,  5782,
    5788,  5797,  5801,  5810,  5817,  5818,  5824,  5825,  5829,  5838,
    5839,  5843,  5847,  5859,  5859,  5865,  5864,  5881,  5884,  5905,
    5906,  5909,  5910,  5914,  5915,  5920,  5925,  5933,  5945,  5950,
    5958,  5974,  5975,  5974,  5995,  5996,  6012,  6013,  6014,  6015,
    6016,  6020,  6021,  6030,  6030,  6035,  6042,  6043,  6044,  6053,
    6053,  6062,  6063,  6067,  6068,  6069,  6073,  6074,  6078,  6079,
    6088,  6088,  6094,  6098,  6102,  6109,  6110,  6119,  6126,  6127,
    6135,  6135,  6148,  6148,  6164,  6164,  6173,  6175,  6176,  6185,
    6185,  6195,  6196,  6201,  6202,  6207,  6214,  6215,  6220,  6227,
    6228,  6232,  6233,  6237,  6238,  6242,  6243,  6252,  6253,  6254,
    6258,  6282,  6285,  6293,  6303,  6308,  6313,  6318,  6325,  6326,
    6329,  6330,  6334,  6334,  6338,  6338,  6342,  6342,  6345,  6346,
    6350,  6357,  6358,  6362,  6374,  6374,  6391,  6392,  6397,  6400,
    6404,  6408,  6415,  6416,  6419,  6420,  6421,  6425,  6426,  6439,
    6447,  6454,  6456,  6455,  6465,  6467,  6466,  6481,  6485,  6487,
    6486,  6497,  6499,  6498,  6515,  6521,  6523,  6522,  6532,  6534,
    6533,  6549,  6554,  6559,  6569,  6568,  6580,  6579,  6595,  6600,
    6605,  6615,  6614,  6626,  6625,  6640,  6641,  6645,  6650,  6655,
    6665,  6664,  6676,  6675,  6692,  6695,  6707,  6714,  6721,  6721,
    6731,  6732,  6734,  6735,  6736,  6737,  6738,  6739,  6741,  6742,
    6743,  6744,  6745,  6746,  6748,  6749,  6751,  6752,  6753,  6756,
    6758,  6759,  6760,  6762,  6763,  6764,  6766,  6767,  6769,  6770,
    6771,  6772,  6773,  6775,  6776,  6777,  6778,  6779,  6780,  6782,
    6783,  6784,  6785,  6786,  6787,  6789,  6790,  6793,  6793,  6793,
    6794,  6794,  6795,  6795,  6796,  6796,  6796,  6797,  6797,  6797,
    6802,  6803,  6806,  6807,  6808,  6812,  6813,  6814,  6815,  6816,
    6817,  6818,  6819,  6820,  6831,  6843,  6858,  6859,  6864,  6870,
    6892,  6912,  6916,  6932,  6946,  6947,  6952,  6958,  6959,  6964,
    6973,  6974,  6975,  6979,  6990,  6991,  6995,  7005,  7006,  7010,
    7011,  7015,  7016,  7022,  7042,  7043,  7047,  7048,  7052,  7053,
    7057,  7058,  7059,  7060,  7061,  7062,  7063,  7064,  7065,  7069,
    7070,  7071,  7072,  7073,  7074,  7075,  7079,  7080,  7084,  7085,
    7089,  7090,  7094,  7095,  7106,  7107,  7111,  7112,  7113,  7117,
    7118,  7119,  7127,  7131,  7132,  7133,  7134,  7138,  7139,  7143,
    7153,  7171,  7198,  7210,  7211,  7221,  7222,  7226,  7227,  7228,
    7229,  7230,  7231,  7232,  7240,  7244,  7248,  7252,  7256,  7260,
    7264,  7268,  7272,  7276,  7280,  7284,  7291,  7292,  7293,  7297,
    7298,  7302,  7303,  7308,  7315,  7322,  7332,  7339,  7349,  7356,
    7370,  7380,  7381,  7385,  7386,  7390,  7391,  7395,  7396,  7397,
    7401,  7402,  7406,  7407,  7411,  7412,  7416,  7417,  7424,  7424,
    7425,  7425,  7426,  7426,  7427,  7427,  7429,  7429,  7430,  7430,
    7431,  7431,  7432,  7432,  7433,  7433,  7434,  7434,  7435,  7435,
    7436,  7436,  7437,  7437,  7438,  7438,  7439,  7439,  7440,  7440,
    7441,  7441,  7442,  7442,  7443,  7443,  7444,  7444,  7445,  7445,
    7446,  7446,  7446,  7447,  7447,  7448,  7448,  7448,  7449,  7449,
    7450,  7450,  7451,  7451,  7452,  7452,  7453,  7453,  7454,  7454,
    7455,  7455,  7455,  7456,  7456,  7457,  7457,  7458,  7458,  7459,
    7459,  7460,  7460,  7461,  7461,  7462,  7462,  7462,  7463,  7463,
    7464,  7464,  7465,  7465,  7466,  7466,  7467,  7467,  7468,  7468,
    7469,  7469,  7471,  7471,  7472,  7472
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
  "CLASS_NAME", "CLOSE", "\"CLOSE-NOFEED\"", "CODE", "\"CODE-SET\"",
  "COLLATING", "COL", "COLS", "COLUMN", "COLUMNS", "COMMA",
  "\"COMMAND-LINE\"", "\"comma delimiter\"", "COMMIT",
  "\"COMMITMENT-CONTROL\"", "COMMON", "COMP", "COMPUTE", "\"COMP-1\"",
  "\"COMP-2\"", "\"COMP-3\"", "\"COMP-4\"", "\"COMP-5\"", "\"COMP-X\"",
  "\"FUNCTION CONCATENATE\"", "CONFIGURATION", "CONSTANT", "CONTAINS",
  "CONTENT", "CONTINUE", "CONTROL", "CONTROLS", "\"CONTROL FOOTING\"",
  "\"CONTROL HEADING\"", "CONVERTING", "\"CORE-INDEX\"", "CORRESPONDING",
  "COUNT", "CRT", "CURRENCY", "\"FUNCTION CURRENT-DATE\"", "CURSOR",
  "CYCLE", "\"CYL-OVERFLOW\"", "DATA", "DATE", "DAY", "\"DAY-OF-WEEK\"",
  "DE", "DEBUGGING", "\"DECIMAL-POINT\"", "DECLARATIVES", "DEFAULT",
  "DELETE", "DELIMITED", "DELIMITER", "DEPENDING", "DESCENDING", "DETAIL",
  "DISK", "DISPLAY", "DIVIDE", "DIVISION", "DOWN", "DUPLICATES", "DYNAMIC",
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
  "FIRST", "FOOTING", "FOR", "\"FOREGROUND-COLOR\"", "FOREVER",
  "\"FORMS-OVERLAY\"", "FREE", "FROM", "FULL", "FUNCTION",
  "\"FUNCTION-ID\"", "\"FUNCTION\"", "GE", "GENERATE", "GIVING", "GLOBAL",
  "GO", "GOBACK", "GREATER", "GROUP", "HEADING", "HIGHLIGHT",
  "\"HIGH-VALUE\"", "IDENTIFICATION", "IF", "IGNORE", "IGNORING", "IN",
  "INDEX", "INDEXED", "INDICATE", "INITIALIZE", "INITIALIZED", "INITIATE",
  "INPUT", "\"INPUT-OUTPUT\"", "INSPECT", "INTO", "INTRINSIC", "INVALID",
  "\"INVALID KEY\"", "IS", "\"I-O\"", "\"I-O-CONTROL\"", "JUSTIFIED",
  "KEY", "LABEL", "LAST", "\"LAST DETAIL\"", "LE", "LEADING", "LEFT",
  "LENGTH", "LESS", "LEVEL_NUMBER_WORD", "LEVEL88_NUMBER_WORD", "LIMIT",
  "LIMITS", "LINAGE", "\"LINAGE-COUNTER\"", "LINE", "LINES", "LINKAGE",
  "\"Literal\"", "LOCALE", "\"FUNCTION LOCALE\"", "\"LOCAL-STORAGE\"",
  "LOCK", "\"FUNCTION LOWER-CASE\"", "LOWLIGHT", "\"LOW-VALUE\"", "MANUAL",
  "MEMORY", "MERGE", "MINUS", "\"MNEMONIC NAME\"", "MODE", "MOVE",
  "MULTIPLE", "MULTIPLY", "NATIONAL", "\"NATIONAL-EDITED\"", "NATIVE",
  "NE", "NEGATIVE", "NEXT", "\"NEXT SENTENCE\"", "NO", "NOMINAL", "NOT",
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
  "TRACKS", "TRAILING", "TRANSFORM", "\"FUNCTION TRIM\"", "TYPE",
  "UNDERLINE", "UNIT", "UNLOCK", "UNSIGNED", "\"UNSIGNED-INT\"",
  "\"UNSIGNED-LONG\"", "\"UNSIGNED-SHORT\"", "UNSTRING", "UNTIL", "UP",
  "UPDATE", "UPON", "\"UPON ARGUMENT-NUMBER\"", "\"UPON COMMAND-LINE\"",
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
  "_ext_clause", "assignment_name", "assignment_device_name_list",
  "access_mode_clause", "access_mode", "alternative_record_key_clause",
  "split_key_list", "$@16", "split_key", "key_is_eq",
  "collating_sequence_clause", "file_status_clause", "file_or_sort",
  "lock_mode_clause", "lock_mode", "lock_with", "lock_records",
  "organization_clause", "organization", "padding_character_clause",
  "record_delimiter_clause", "record_key_clause", "relative_key_clause",
  "reserve_clause", "sharing_clause", "sharing_option",
  "nominal_key_clause", "i_o_control_paragraph", "opt_i_o_control",
  "i_o_control_list", "i_o_control_clause", "same_clause", "same_option",
  "multiple_file_tape_clause", "multiple_file_list", "multiple_file",
  "multiple_file_position", "apply_clause_list", "apply_clause",
  "data_division", "file_section", "$@17", "$@18",
  "file_description_sequence", "file_description",
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
  "_literal", "_mode", "_number", "_of", "_on", "_in_order", "_other",
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
     685,   686,   687,   688,   689,   690,   691,   692,   693,   694,
     695,   696,   697,   698,   699,   700,   701,   702,   703,    43,
      45,    42,    47,   704,    94,    46,    61,    41,    40,    62,
      60,    58,    38
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   463,   465,   464,   466,   466,   467,   467,   469,   470,
     468,   472,   473,   471,   475,   476,   474,   477,   477,   477,
     478,   478,   479,   480,   482,   481,   483,   484,   484,   485,
     485,   486,   486,   487,   487,   487,   488,   488,   489,   489,
     490,   490,   491,   491,   492,   492,   492,   492,   493,   494,
     494,   494,   494,   495,   496,   497,   498,   498,   498,   498,
     499,   499,   500,   500,   500,   501,   502,   502,   503,   504,
     505,   506,   506,   507,   507,   508,   508,   509,   509,   510,
     511,   511,   511,   512,   512,   513,   513,   513,   513,   513,
     513,   513,   513,   513,   513,   513,   514,   515,   514,   516,
     514,   514,   514,   514,   514,   517,   517,   518,   518,   519,
     520,   520,   522,   521,   523,   523,   523,   523,   523,   524,
     524,   525,   525,   526,   525,   527,   527,   528,   528,   528,
     528,   528,   528,   529,   529,   529,   529,   529,   529,   530,
     531,   532,   532,   533,   533,   534,   535,   535,   536,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   544,   545,
     544,   546,   544,   547,   547,   548,   548,   550,   549,   551,
     551,   552,   552,   552,   552,   552,   552,   552,   552,   552,
     552,   552,   552,   552,   552,   552,   553,   553,   553,   554,
     554,   554,   555,   555,   555,   556,   556,   556,   557,   557,
     558,   559,   559,   559,   560,   560,   562,   561,   561,   563,
     564,   564,   564,   565,   566,   567,   567,   567,   568,   569,
     569,   569,   570,   570,   570,   570,   571,   571,   572,   572,
     573,   573,   573,   573,   573,   574,   575,   576,   576,   577,
     578,   578,   579,   580,   580,   580,   581,   582,   582,   583,
     583,   583,   583,   584,   584,   585,   585,   586,   587,   587,
     587,   587,   588,   589,   589,   590,   591,   591,   592,   592,
     592,   593,   593,   593,   593,   593,   594,   594,   595,   596,
     595,   597,   595,   598,   598,   599,   600,   600,   601,   601,
     603,   602,   604,   604,   605,   605,   605,   605,   605,   605,
     605,   605,   605,   605,   605,   605,   606,   607,   607,   607,
     608,   608,   608,   609,   609,   610,   610,   611,   611,   612,
     613,   613,   614,   614,   615,   615,   616,   617,   618,   618,
     619,   619,   619,   620,   621,   622,   623,   624,   625,   625,
     626,   627,   626,   628,   628,   630,   629,   631,   631,   631,
     632,   633,   632,   634,   632,   635,   636,   637,   637,   638,
     638,   638,   639,   640,   640,   641,   641,   641,   642,   643,
     643,   644,   644,   644,   644,   644,   644,   644,   644,   644,
     644,   644,   644,   644,   644,   644,   645,   646,   647,   647,
     648,   649,   650,   650,   651,   651,   651,   651,   651,   651,
     651,   651,   651,   651,   651,   651,   651,   651,   651,   651,
     651,   651,   651,   651,   651,   651,   651,   651,   651,   651,
     651,   651,   651,   651,   651,   651,   651,   651,   651,   652,
     652,   653,   653,   653,   654,   655,   655,   656,   656,   657,
     657,   658,   659,   660,   660,   661,   661,   662,   662,   663,
     664,   664,   665,   666,   667,   668,   668,   668,   669,   670,
     671,   673,   672,   674,   674,   675,   675,   676,   676,   677,
     677,   678,   679,   680,   679,   681,   682,   681,   683,   684,
     683,   685,   685,   686,   686,   687,   688,   688,   689,   689,
     689,   689,   690,   690,   691,   692,   692,   693,   693,   694,
     695,   695,   696,   696,   697,   697,   698,   698,   699,   699,
     700,   700,   700,   701,   701,   702,   702,   703,   704,   704,
     705,   705,   705,   705,   705,   705,   705,   705,   705,   705,
     705,   705,   705,   705,   705,   705,   706,   707,   707,   707,
     707,   707,   707,   707,   708,   709,   709,   709,   710,   710,
     711,   712,   713,   714,   715,   716,   716,   717,   717,   718,
     718,   718,   719,   719,   719,   720,   721,   722,   722,   723,
     724,   725,   726,   724,   727,   727,   728,   728,   729,   730,
     729,   731,   731,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   732,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   732,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   732,   733,   733,   733,   733,   733,   734,   734,
     734,   734,   734,   735,   736,   737,   738,   736,   739,   740,
     739,   741,   739,   742,   742,   743,   744,   744,   744,   745,
     745,   745,   745,   745,   746,   746,   747,   747,   748,   749,
     748,   750,   750,   751,   751,   751,   751,   751,   752,   753,
     754,   755,   756,   756,   758,   759,   757,   760,   760,   761,
     761,   761,   761,   761,   761,   761,   761,   761,   761,   761,
     761,   761,   761,   761,   761,   761,   761,   761,   761,   761,
     761,   761,   761,   761,   761,   761,   761,   761,   761,   761,
     761,   761,   761,   761,   761,   761,   761,   761,   761,   761,
     761,   761,   761,   761,   761,   761,   761,   761,   761,   763,
     762,   764,   764,   764,   764,   764,   764,   764,   764,   764,
     764,   764,   764,   764,   764,   764,   764,   764,   765,   765,
     765,   765,   765,   765,   766,   767,   767,   768,   768,   769,
     769,   770,   770,   770,   770,   770,   770,   770,   770,   770,
     770,   770,   770,   770,   770,   770,   770,   770,   771,   771,
     773,   772,   774,   774,   774,   775,   775,   776,   776,   778,
     777,   779,   779,   780,   780,   781,   782,   782,   783,   783,
     785,   784,   786,   787,   786,   788,   788,   789,   789,   790,
     790,   790,   790,   791,   791,   791,   792,   793,   792,   794,
     795,   794,   796,   796,   798,   797,   799,   799,   801,   800,
     802,   802,   803,   803,   803,   803,   803,   804,   804,   806,
     805,   807,   808,   808,   809,   809,   810,   811,   813,   812,
     814,   814,   816,   815,   818,   817,   819,   819,   819,   819,
     819,   819,   819,   819,   819,   820,   820,   820,   821,   821,
     822,   822,   822,   822,   822,   822,   822,   822,   822,   822,
     822,   822,   822,   822,   822,   823,   823,   825,   824,   826,
     826,   826,   826,   826,   827,   827,   829,   828,   831,   830,
     832,   832,   833,   833,   833,   834,   835,   835,   837,   836,
     838,   839,   838,   840,   840,   841,   841,   842,   842,   842,
     842,   843,   843,   844,   844,   846,   845,   847,   847,   847,
     847,   847,   847,   849,   848,   851,   850,   853,   852,   854,
     854,   856,   855,   858,   859,   857,   857,   860,   861,   860,
     862,   862,   864,   863,   865,   865,   866,   866,   866,   867,
     867,   868,   868,   869,   870,   870,   870,   870,   870,   870,
     870,   871,   871,   873,   872,   875,   874,   876,   876,   876,
     877,   877,   878,   878,   878,   880,   879,   881,   881,   882,
     882,   882,   882,   882,   882,   883,   884,   884,   885,   885,
     886,   886,   886,   886,   886,   887,   888,   889,   889,   890,
     890,   892,   891,   894,   893,   895,   895,   897,   896,   898,
     898,   899,   899,   901,   900,   902,   902,   903,   903,   903,
     903,   904,   904,   905,   905,   905,   907,   906,   908,   909,
     908,   908,   910,   910,   911,   911,   912,   912,   912,   912,
     912,   913,   913,   914,   914,   915,   917,   916,   918,   918,
     919,   919,   919,   919,   919,   919,   920,   920,   921,   921,
     921,   922,   922,   924,   923,   926,   925,   927,   927,   929,
     928,   930,   930,   930,   931,   931,   932,   934,   933,   935,
     936,   935,   937,   937,   938,   939,   938,   940,   940,   942,
     941,   943,   943,   945,   944,   946,   946,   946,   946,   946,
     947,   948,   948,   949,   950,   950,   951,   951,   952,   953,
     953,   954,   954,   956,   955,   958,   957,   959,   959,   960,
     960,   961,   961,   962,   962,   963,   963,   963,   964,   964,
     964,   966,   967,   965,   968,   968,   969,   969,   969,   969,
     969,   970,   970,   972,   971,   971,   973,   973,   973,   975,
     974,   976,   976,   977,   977,   977,   978,   978,   979,   979,
     981,   980,   982,   982,   982,   983,   983,   984,   985,   985,
     987,   986,   989,   988,   991,   990,   992,   992,   992,   994,
     993,   995,   995,   996,   996,   997,   998,   998,   999,  1000,
    1000,  1001,  1001,  1002,  1002,  1003,  1003,  1004,  1004,  1004,
    1005,  1006,  1006,  1007,  1007,  1007,  1007,  1007,  1008,  1008,
    1009,  1009,  1010,  1010,  1011,  1011,  1012,  1012,  1013,  1013,
    1014,  1015,  1015,  1016,  1018,  1017,  1019,  1019,  1020,  1020,
    1020,  1020,  1021,  1021,  1022,  1022,  1022,  1023,  1023,  1024,
    1025,  1026,  1027,  1026,  1028,  1029,  1028,  1030,  1031,  1032,
    1031,  1033,  1034,  1033,  1035,  1036,  1037,  1036,  1038,  1039,
    1038,  1040,  1040,  1040,  1042,  1041,  1044,  1043,  1045,  1045,
    1045,  1047,  1046,  1049,  1048,  1050,  1050,  1051,  1051,  1051,
    1053,  1052,  1055,  1054,  1056,  1056,  1057,  1058,  1060,  1059,
    1061,  1061,  1061,  1061,  1061,  1061,  1061,  1061,  1061,  1061,
    1061,  1061,  1061,  1061,  1061,  1061,  1061,  1061,  1061,  1062,
    1062,  1062,  1062,  1062,  1062,  1062,  1062,  1062,  1062,  1062,
    1062,  1062,  1062,  1062,  1062,  1062,  1062,  1062,  1062,  1062,
    1062,  1062,  1062,  1062,  1062,  1062,  1062,  1063,  1063,  1063,
    1064,  1064,  1065,  1065,  1066,  1066,  1066,  1067,  1067,  1067,
    1068,  1068,  1069,  1069,  1069,  1070,  1070,  1070,  1070,  1070,
    1070,  1070,  1070,  1070,  1071,  1071,  1072,  1072,  1073,  1074,
    1075,  1076,  1076,  1077,  1078,  1078,  1079,  1080,  1080,  1081,
    1082,  1082,  1082,  1083,  1084,  1084,  1085,  1086,  1086,  1087,
    1087,  1088,  1088,  1089,  1090,  1090,  1091,  1091,  1092,  1092,
    1093,  1093,  1093,  1093,  1093,  1093,  1093,  1093,  1093,  1094,
    1094,  1094,  1094,  1094,  1094,  1094,  1095,  1095,  1096,  1096,
    1097,  1097,  1098,  1098,  1099,  1099,  1100,  1100,  1100,  1101,
    1101,  1101,  1102,  1103,  1103,  1103,  1103,  1104,  1104,  1105,
    1106,  1106,  1107,  1108,  1108,  1109,  1109,  1110,  1110,  1110,
    1110,  1110,  1110,  1110,  1111,  1111,  1111,  1111,  1111,  1111,
    1111,  1111,  1111,  1111,  1111,  1111,  1112,  1112,  1112,  1113,
    1113,  1114,  1114,  1115,  1115,  1115,  1116,  1116,  1117,  1117,
    1118,  1119,  1119,  1120,  1120,  1121,  1121,  1122,  1122,  1122,
    1123,  1123,  1124,  1124,  1125,  1125,  1126,  1126,  1127,  1127,
    1128,  1128,  1129,  1129,  1130,  1130,  1131,  1131,  1132,  1132,
    1133,  1133,  1134,  1134,  1135,  1135,  1136,  1136,  1137,  1137,
    1138,  1138,  1139,  1139,  1140,  1140,  1141,  1141,  1142,  1142,
    1143,  1143,  1144,  1144,  1145,  1145,  1146,  1146,  1147,  1147,
    1148,  1148,  1148,  1149,  1149,  1150,  1150,  1150,  1151,  1151,
    1152,  1152,  1153,  1153,  1154,  1154,  1155,  1155,  1156,  1156,
    1157,  1157,  1157,  1158,  1158,  1159,  1159,  1160,  1160,  1161,
    1161,  1162,  1162,  1163,  1163,  1164,  1164,  1164,  1165,  1165,
    1166,  1166,  1167,  1167,  1168,  1168,  1169,  1169,  1170,  1170,
    1171,  1171,  1172,  1172,  1173,  1173
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
       1,     1,     1,     1,     1,     1,     5,     4,     4,     0,
       1,     1,     0,     1,     1,     1,     1,     2,     1,     2,
       4,     1,     1,     1,     6,     8,     0,     2,     2,     1,
       0,     2,     1,     3,     5,     0,     1,     1,     4,     2,
       2,     1,     0,     4,     5,     2,     1,     1,     3,     1,
       1,     3,     1,     1,     2,     4,     4,     4,     6,     4,
       3,     2,     3,     2,     2,     2,     4,     0,     3,     0,
       2,     1,     1,     1,     2,     1,     1,     5,     0,     1,
       1,     1,     5,     1,     2,     2,     0,     2,     2,     1,
       2,     4,     7,     6,     6,     4,     0,     9,     0,     0,
       5,     0,     3,     0,     2,     3,     2,     2,     1,     1,
       0,     4,     0,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     0,     1,     1,
       4,     6,     9,     0,     3,     0,     2,     0,     2,     3,
       1,     1,     5,     5,     1,     1,     3,     5,     0,     2,
       1,     1,     1,     5,     4,     3,     4,     3,     3,     3,
       0,     0,     5,     0,     1,     0,     2,     2,     3,     2,
       1,     0,     5,     0,     4,     1,     1,     0,     1,     0,
       1,     1,     1,     0,     2,     1,     3,     3,     6,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     0,     2,
       2,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     2,     2,     1,     2,
       2,     1,     2,     2,     1,     2,     2,     1,     1,     3,
       3,     0,     2,     2,     6,     0,     2,     0,     3,     0,
       1,     1,     4,     1,     2,     1,     1,     0,     1,     3,
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
       2,     3,     3,     0,     3,     0,     7,     0,     6,     0,
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
       1,     1,     3,     1,     1,     2,     1,     1,     2,     0,
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
       0,     1,     2,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     2,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,     4,     6,     7,
      38,    38,     0,     0,     3,     5,     0,     8,    14,    28,
      27,    29,    29,     0,   276,   276,     0,     0,    24,    40,
       0,     9,    15,    30,    26,  1538,     0,   157,     0,   624,
     624,  1539,     0,     0,     0,     0,     0,     0,    39,   278,
       0,    17,     0,    25,    33,    37,    36,  1565,    35,    42,
     159,     0,   161,   288,   289,     0,   340,   281,   628,    18,
      20,    38,     0,    16,    34,  1566,    32,    41,   165,   163,
     249,     0,     0,   472,     0,   631,   629,   646,     0,    19,
      10,    11,     0,     0,     0,     0,     0,    43,    44,    45,
      47,    46,   160,     0,   247,     0,  1530,   258,   162,   251,
     253,   255,   256,   252,   269,   279,     0,     0,   475,  1373,
     282,   343,   290,   636,   636,     0,     0,     0,   276,    23,
      56,    71,    49,    80,  1492,   166,   165,     0,   158,     0,
    1558,     0,  1556,     0,  1531,  1582,   259,   260,   261,  1512,
     250,   254,   268,   270,   283,   341,     0,     0,   478,   287,
       0,   286,   344,  1480,   292,  1521,   636,   633,   639,     0,
     636,   647,   625,    21,    12,     0,  1538,    54,  1565,    55,
    1565,    60,    62,    63,    64,     0,     0,    70,     0,    73,
    1595,    48,     0,  1594,     0,     0,  1538,  1538,     0,     0,
    1573,  1538,  1538,  1538,  1538,  1538,     0,  1538,  1524,  1538,
      79,    81,    83,    85,    86,    87,    89,    88,    90,    91,
      92,    93,    94,    95,  1493,     0,   164,   249,     0,  1559,
       0,     0,  1557,     0,     0,  1583,  1526,  1513,  1532,   280,
     343,   473,     0,     0,   570,   343,   346,     0,     0,   634,
    1538,     0,   644,   637,   638,   648,   624,  1538,     0,    57,
    1565,    59,    61,     0,  1505,  1538,     0,    77,     0,    72,
      74,    52,    50,     0,     0,  1393,   112,     0,     0,  1538,
    1538,  1574,  1538,     0,     0,     0,     0,     0,  1538,     0,
    1525,     0,    99,    82,    84,   167,   248,  1437,   275,  1384,
    1386,   271,     0,     0,     0,  1527,     0,  1533,     0,   284,
     342,   343,   476,     0,     0,   277,   285,   349,     0,   355,
     356,   347,   359,   359,   350,   305,  1526,  1538,     0,     0,
    1538,  1526,  1552,  1538,  1510,     0,   291,   293,   296,   297,
     298,   299,   300,   301,   302,   303,   304,     0,     0,  1538,
     645,     0,     0,   626,    17,     0,  1442,    69,    58,  1504,
       0,    76,    75,    78,    51,    53,  1538,   101,   102,     0,
       0,     0,   153,   152,   103,   104,   156,     0,   155,   139,
    1540,   141,    96,     0,    97,   169,  1498,  1499,     0,  1385,
       0,     0,     0,   262,   263,   266,   257,  1371,   474,   343,
     479,     0,   348,   360,   361,   351,     0,   361,   353,     0,
       0,  1538,  1510,     0,     0,     0,     0,     0,  1553,  1538,
       0,  1511,     0,     0,   294,   295,   640,   641,   643,     0,
     635,   649,   651,     0,     0,    68,     0,  1451,  1447,  1452,
    1450,  1448,  1453,  1449,   145,   146,   148,   154,   151,   150,
    1542,  1541,   142,     0,   111,   110,   100,   107,  1580,   105,
       0,  1438,   273,     0,   274,   264,     0,   265,  1372,   477,
     481,   571,   369,   363,     0,   317,   337,  1500,  1501,   326,
    1387,   321,   320,   319,  1392,  1391,  1548,  1524,  1536,     0,
     569,   338,   339,  1538,  1538,   642,   651,     0,     0,    13,
      66,    67,    65,   117,   131,   127,   132,   114,   130,   128,
     115,   116,   129,   113,   118,   119,   121,   147,     0,   140,
     143,   108,  1581,  1538,    98,   184,  1552,     0,  1590,   230,
       0,  1552,  1543,  1538,  1522,  1543,   233,     0,   232,  1594,
     217,   216,   168,   170,   171,   172,   173,   174,   175,     0,
     176,   177,   229,   178,   179,   180,   181,   182,   183,   185,
    1538,   272,   267,     0,   480,   482,   483,   572,     0,  1514,
       0,  1540,   354,     0,   307,  1388,  1549,   328,     0,   310,
    1537,  1578,   336,     0,     0,     0,   657,   661,   652,   653,
     654,   655,   660,     0,     0,   120,   123,     0,   149,   144,
       0,   106,  1538,  1543,  1591,   192,   234,  1538,  1544,  1538,
       0,  1523,  1538,  1519,  1538,     0,  1538,  1538,   241,  1512,
       0,  1538,     0,   486,   484,   574,   385,     0,   459,   394,
     427,   415,   424,   421,   418,  1592,   395,   396,   397,   398,
     399,   400,   401,   402,   403,  1569,   358,   428,     0,   404,
     391,   405,   406,     0,     0,  1576,   408,   409,   407,   455,
     411,   412,   410,  1538,  1538,   352,   370,   371,   372,   373,
     374,   375,   392,   376,   377,   378,   379,   380,   381,   382,
     383,   384,     0,     0,  1515,     0,   364,     0,   318,   309,
     308,   306,   327,  1524,  1579,   315,   324,   323,   325,   322,
       0,   659,   662,   719,   770,   779,   786,   790,   814,   818,
     836,   829,   837,   838,   844,   877,   886,   888,   915,   923,
     925,  1590,   931,     0,   942,   963,   965,  1001,  1003,  1007,
     718,  1013,  1026,  1046,  1063,  1065,  1069,  1076,  1077,  1093,
    1113,  1131,     0,  1149,  1160,  1168,  1170,  1172,  1174,  1179,
    1201,  1224,   656,   668,   669,   670,   671,   672,   673,   674,
     675,   677,   676,   678,   679,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   693,   694,
     695,   696,   697,   698,   699,   700,   701,   702,   703,   704,
     705,   706,   707,   708,   709,   710,   711,   712,   713,   714,
     715,   716,  1197,  1198,  1199,   717,    22,     0,   122,   109,
       0,  1538,   194,   193,   189,     0,     0,  1518,   233,   228,
       0,     0,   231,     0,     0,   240,  1563,  1563,     0,   242,
       0,   213,  1538,   359,   578,   573,   575,   576,   471,   425,
     426,   413,   414,   422,   423,   419,   420,   416,   417,  1593,
       0,  1570,   453,   435,   386,  1433,   469,  1577,   456,   457,
     454,     0,     0,   388,   390,  1496,  1496,     0,  1556,  1556,
     368,   365,  1443,  1445,   461,   463,   465,  1517,   329,   330,
     331,   332,     0,     0,   311,  1535,   317,     0,     0,   663,
       0,     0,     0,  1288,   785,     0,   816,   820,     0,     0,
       0,     0,     0,     0,  1288,   917,     0,     0,   927,   932,
       0,  1288,     0,     0,     0,     0,     0,     0,  1015,  1036,
       0,     0,     0,     0,     0,     0,     0,     0,  1145,  1143,
       0,     0,  1169,  1167,     0,     0,     0,     0,  1202,  1208,
       0,     0,   137,   133,   138,   136,   134,   135,   124,   125,
     202,   203,   201,   200,     0,   187,   188,  1550,   222,   221,
     222,   218,   246,   235,   236,   237,   239,  1564,   243,   244,
     245,  1389,  1538,   495,   495,  1540,   515,   487,   490,   491,
       0,   579,   577,   458,     0,  1588,     0,  1434,  1435,     0,
     393,   460,     0,   387,  1522,   429,   430,  1444,     0,     0,
       0,  1592,   464,     0,     0,     0,  1516,  1524,   316,   650,
     658,   768,   738,  1432,  1556,     0,     0,  1466,  1469,  1556,
    1364,     0,     0,     0,     0,     0,     0,     0,     0,  1466,
     777,  1408,   775,  1398,  1400,  1406,  1407,  1485,   780,     0,
    1287,  1309,  1383,     0,  1379,  1381,  1380,  1427,   792,  1426,
    1428,   815,   819,   832,     0,  1366,  1494,  1567,     0,  1447,
     875,   738,     0,  1400,   884,     0,   792,   894,   893,  1508,
     890,   892,   922,   919,   918,   921,   916,  1556,   924,  1394,
    1396,   926,  1377,   936,  1586,  1286,   944,   964,   497,     0,
     967,   968,   969,  1002,  1117,     0,  1004,     0,  1011,     0,
    1014,  1037,  1383,  1027,  1036,  1029,     0,  1034,     0,  1380,
       0,  1487,  1226,  1369,  1567,  1226,     0,  1091,  1082,  1370,
       0,  1376,  1094,  1095,  1096,  1097,  1098,  1106,  1099,  1109,
       0,  1374,     0,  1114,  1132,  1146,  1520,     0,  1151,  1153,
       0,  1165,     0,  1171,     0,  1176,  1181,  1209,     0,  1210,
    1558,  1226,     0,  1483,   196,   195,   186,     0,     0,   220,
     219,  1538,   212,   206,  1390,   214,     0,   496,   492,     0,
     493,     0,   485,   488,   581,   436,  1589,   437,  1556,     0,
       0,     0,  1352,  1350,  1415,  1355,  1409,  1413,  1414,     0,
    1436,   470,   389,  1497,   367,   366,  1446,  1571,   466,   335,
    1548,     0,   313,   769,   720,  1517,     0,   747,     0,     0,
       0,     0,     0,  1454,  1471,  1465,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1455,   778,   771,     0,
       0,  1399,  1486,   783,  1485,  1289,     0,   788,     0,   793,
     803,  1425,   817,  1424,   822,   833,   830,   835,   834,  1288,
    1367,  1495,  1368,  1568,  1275,   843,   876,   845,   855,  1241,
    1241,  1241,  1241,   885,   878,     0,     0,   887,  1509,  1288,
     913,   900,   896,   898,  1288,   920,     0,  1395,   929,  1587,
     934,   946,     0,   498,     0,   990,   975,   966,   970,   972,
     973,   974,  1121,     0,     0,  1012,  1008,     0,  1020,  1017,
    1019,  1018,  1021,  1028,  1031,   664,  1288,     0,     0,  1038,
       0,  1488,  1489,  1567,     0,  1064,  1048,  1071,  1084,  1092,
    1078,     0,  1084,     0,  1420,  1421,  1107,  1110,     0,     0,
    1375,  1105,     0,  1104,     0,  1134,     0,     0,  1144,     0,
       0,  1152,     0,  1166,  1161,     0,     0,  1177,  1178,  1175,
    1520,     0,     0,  1211,     0,     0,  1071,   126,  1503,     0,
     206,   204,  1484,   197,   198,     0,   225,   211,   238,     0,
     489,   494,   500,   510,   359,   516,  1575,  1558,   431,     0,
    1360,  1361,     0,  1353,  1354,  1439,     0,     0,     0,     0,
       0,     0,     0,     0,  1572,  1590,   334,  1548,  1558,   312,
     743,   734,  1241,   724,   731,   725,   727,   729,     0,  1241,
       0,   723,   730,   737,   736,     0,  1241,  1554,  1554,  1554,
     741,   742,  1417,  1416,     0,  1405,  1352,  1350,     0,     0,
    1352,     0,  1401,  1402,  1403,  1365,  1352,     0,     0,  1352,
       0,     0,  1352,  1352,  1352,     0,     0,  1248,  1494,     0,
       0,   781,     0,  1300,  1301,  1302,  1335,  1303,  1590,  1339,
    1344,  1584,  1310,  1347,  1584,  1328,  1307,  1317,  1299,  1298,
    1336,  1306,  1308,  1318,  1319,  1320,  1321,  1322,  1337,  1291,
    1340,  1342,  1323,  1324,  1325,  1326,  1327,  1294,  1295,  1296,
    1297,  1311,  1334,  1305,  1316,  1293,  1292,  1304,  1313,  1314,
    1315,  1312,  1329,  1330,  1331,  1332,  1333,  1290,     0,     0,
    1382,   799,     0,     0,   806,   827,   828,   821,   823,     0,
    1248,  1280,  1282,   840,  1276,  1277,  1278,     0,  1595,  1241,
       0,  1242,   848,  1244,   849,   846,   847,     0,  1248,  1494,
     908,   910,   909,   903,   905,   911,   914,   889,   901,   897,
     895,  1288,   664,   891,  1397,  1558,   928,  1378,   664,  1590,
     954,   955,   957,   959,   960,   956,   958,   949,  1590,   945,
       0,   991,     0,   993,   992,   994,   985,   986,     0,     0,
     971,  1123,  1560,     0,     0,  1005,  1248,  1494,  1594,     0,
    1032,   665,  1039,  1040,  1043,     0,  1035,  1233,  1232,  1042,
    1048,  1227,     0,     0,  1275,     0,     0,     0,  1083,     0,
       0,     0,  1108,     0,  1112,  1111,  1102,     0,  1538,  1275,
    1148,  1147,  1154,  1155,  1156,     0,  1248,  1494,     0,  1481,
       0,  1156,  1223,  1213,  1212,  1218,     0,  1220,  1221,  1228,
    1502,  1483,   199,     0,   208,   209,   207,  1538,   502,   513,
     514,   512,   518,   594,  1538,   585,   583,   584,   586,  1554,
       0,  1538,     0,   597,   589,  1554,   590,     0,   593,   598,
     596,   591,   595,     0,   592,     0,   580,   608,   603,   606,
     605,   604,   607,   582,   609,     0,   445,   446,  1520,   434,
     447,   443,   441,  1543,   439,  1410,  1411,  1412,  1363,  1351,
    1356,  1357,  1358,  1359,  1362,  1440,     0,   467,   333,     0,
     735,  1244,   726,   728,  1241,   732,   722,   762,  1538,   751,
     752,  1538,   763,   753,   754,   757,   767,   764,   755,     0,
     765,   756,   766,   748,   749,   721,  1555,     0,     0,     0,
     739,   740,  1419,  1404,  1418,  1466,  1494,     0,  1470,     0,
    1466,  1466,     0,  1463,  1466,  1466,  1466,     0,  1466,  1466,
    1249,   772,  1251,  1248,   784,     0,  1338,  1585,  1341,  1343,
     789,   787,   794,   795,   639,     0,   805,   804,  1214,  1215,
     809,   807,     0,   826,     0,   831,   664,   664,   841,   839,
    1279,   855,   855,   855,   855,  1538,   860,   873,   874,   861,
       0,  1538,   864,   865,   868,   866,     0,   867,   857,   858,
     850,   856,   664,  1245,  1240,     0,   879,     0,  1288,  1288,
     907,   664,   904,   899,     0,   937,     0,     0,   961,     0,
       0,     0,   987,   989,     0,   981,   997,   982,   983,   976,
     977,   997,  1115,  1538,     0,  1561,  1122,  1543,  1006,  1009,
       0,     0,  1023,  1033,  1030,   667,     0,     0,  1050,  1049,
    1264,  1266,  1067,  1261,  1262,  1074,  1072,     0,  1288,  1085,
    1288,  1079,  1087,  1100,  1101,  1103,  1490,  1141,  1255,     0,
    1494,  1162,     0,     0,  1482,  1182,  1183,     0,  1186,  1189,
    1193,  1187,  1219,  1558,  1222,  1234,  1506,   205,     0,   226,
     227,   223,     0,     0,   504,     0,  1575,     0,  1538,   587,
     588,     0,   611,  1538,  1588,   612,   610,   438,     0,   432,
     448,   444,  1538,   433,   440,  1441,  1538,   462,   314,  1239,
     733,     0,     0,  1284,  1284,   750,   745,   744,   746,  1459,
    1248,  1467,     0,  1479,  1464,  1457,  1477,  1458,  1460,  1461,
    1474,  1475,  1462,  1456,   664,  1252,  1247,   773,   782,  1590,
       0,  1590,     0,   796,   797,     0,   801,   800,   802,  1216,
    1217,   812,   810,   664,   824,   825,  1281,  1283,  1241,  1241,
    1241,  1241,     0,   862,   863,     0,  1284,  1284,   859,  1243,
     664,  1248,  1366,  1248,  1366,   906,   912,   902,   930,   938,
     940,   947,   950,   951,  1528,   962,   943,   948,   997,  1422,
    1423,   997,     0,   980,   978,   979,   984,  1125,     0,  1562,
    1538,  1248,  1022,  1016,     0,   666,  1044,     0,     0,  1056,
       0,   664,   664,  1068,  1066,  1263,  1075,  1070,  1073,  1080,
     664,  1089,  1088,  1491,     0,     0,  1142,  1133,  1256,  1158,
    1258,     0,  1248,  1248,  1173,  1481,  1185,  1536,  1191,  1536,
    1255,     0,  1271,  1273,  1237,  1235,  1268,  1269,  1236,  1507,
       0,   224,   501,  1538,     0,   506,   511,  1554,   547,   567,
     562,  1510,     0,     0,  1538,  1556,  1538,     0,   517,   523,
     524,   525,   534,   526,   528,   531,   519,   520,   521,   527,
     530,   548,   532,   535,   522,     0,   529,   533,  1431,   602,
    1429,  1430,   618,   601,   613,   623,   452,   449,   450,     0,
       0,   759,   758,   761,     0,   760,   774,  1468,  1250,   664,
    1346,  1590,  1349,  1590,   798,   813,   791,   664,   808,   854,
     853,   852,   851,   870,   869,   872,   871,  1246,   881,     0,
     880,     0,   664,   941,   935,   952,  1529,     0,   996,   988,
     997,   999,     0,     0,  1128,  1124,  1119,  1010,  1025,     0,
       0,  1051,  1538,  1058,     0,  1052,     0,  1055,  1265,  1267,
     664,  1086,   664,  1135,  1136,  1137,  1138,  1139,  1140,   664,
    1159,  1150,  1259,  1254,  1157,  1164,  1163,  1184,     0,  1536,
    1188,     0,  1195,  1207,  1204,  1206,  1205,  1200,  1203,   664,
     664,  1238,  1225,  1270,  1231,  1230,  1545,     0,  1538,  1538,
     508,   546,  1538,   568,   566,   563,   564,  1540,   556,  1538,
    1288,     0,     0,     0,     0,   549,     0,     0,   554,   557,
     560,   621,   619,   620,   622,     0,   616,   614,   615,   617,
       0,   451,   442,   468,  1545,  1253,  1345,  1348,   811,  1248,
    1248,   939,     0,   995,  1000,     0,  1538,  1126,     0,     0,
    1116,  1118,  1024,     0,     0,  1061,  1059,  1060,  1054,  1053,
    1081,  1090,  1257,   664,  1190,     0,  1194,  1196,  1180,  1272,
    1274,  1546,  1547,  1229,   503,     0,     0,  1538,   499,     0,
     555,     0,   552,  1494,   550,   551,   541,   539,   540,   542,
     538,   543,   537,   536,     0,   561,   559,   558,   600,   599,
    1285,   883,   882,   953,   998,     0,  1129,  1538,  1120,  1288,
    1057,  1062,  1047,  1260,  1192,   505,   507,     0,   545,   544,
     565,     0,  1127,     0,  1045,   509,     0,  1130,   553
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,     7,     8,    24,    39,    69,   128,
     256,     9,    25,    40,    70,    90,   499,    73,    71,    35,
      11,    21,    27,    42,    57,    58,    17,    37,    77,    97,
      98,   191,   192,   178,    99,   179,   180,   181,   182,   502,
     183,   184,   100,   187,   188,   189,   268,   101,   210,   211,
     212,   213,   459,   383,   524,   456,   457,   458,   214,   366,
     513,   514,   515,   807,   948,   516,   949,   215,   379,   380,
     519,   216,   444,   445,   217,   218,   219,   220,   221,   222,
     223,    48,    78,    80,   104,   102,   135,   385,   460,   543,
     544,   957,   814,  1156,  1363,   545,   953,   546,  1368,  1369,
    1644,  1163,   547,   548,   549,   550,   961,  1159,  1901,   551,
     552,   553,   554,   555,   556,   557,   558,   829,   559,   138,
     108,   109,   110,   111,   149,   112,   393,   394,   467,   113,
     114,    31,    66,   154,    84,   239,   159,   120,   160,   121,
     164,   248,   337,   338,   691,   339,  1399,   886,   574,   340,
     483,   341,   697,   342,   343,   692,   878,   879,   880,   881,
     344,   345,   346,    83,   240,   161,   162,   163,   246,   321,
     472,   474,   322,   323,   665,   405,   406,   569,   870,   324,
     568,   666,   667,   668,   993,   669,   670,   671,   672,   673,
    1689,   674,   985,  1378,  1923,  1690,  1691,  1692,  1693,  1919,
    1694,  2117,  2118,   675,   676,   860,   677,   678,   679,   572,
    1001,   874,   875,  1927,   680,   681,   118,   311,   158,   399,
     244,   470,   564,   565,   566,   832,   977,   978,  1168,  1169,
    1087,   979,  1648,  1904,  2075,  2220,  2298,  1372,  1651,  1172,
    1375,  1906,  2096,  2097,  2313,  2098,  2099,  2100,  2101,  2304,
    2102,  2103,  2104,  2105,  2238,  2239,  2227,  2106,  2107,  2224,
     491,   315,   567,   625,   835,   836,   837,  1174,  1376,  1683,
    2250,  2245,  1684,    51,   255,   432,    87,   124,   123,   166,
     167,   168,   252,   351,   126,   353,   496,   497,   588,   589,
     590,   591,   592,   890,  1590,  1591,  1855,   593,   753,   754,
     891,  1011,  1207,  1420,  1421,  1416,  1733,  1734,  1204,   755,
     892,  1030,  1230,  1228,   756,   893,  1038,  1451,   757,   894,
    1509,   758,   895,  1240,  1511,  1772,  1773,  1774,  1514,  1780,
    1973,  1971,  2137,  2136,   759,   896,  1051,   760,   897,  1052,
    1517,  1518,   761,   898,  1053,  1246,  1249,   762,   763,   764,
     899,  1789,   765,   900,   766,   901,  1060,  1529,  1808,  1809,
    1257,   767,   902,  1064,  1264,   768,   903,   769,   904,  1069,
    1070,  1270,  1271,  1272,  1552,  1550,  1821,  1273,  1543,  1544,
    1820,  1547,   770,   905,  1076,   771,   906,   772,   907,   773,
    1082,  1556,   774,   909,   775,   911,  1558,  2000,  2152,  2154,
     776,   912,  1281,  1567,  1828,  2002,  2003,  2004,  2006,   777,
     913,   778,   914,  1089,  1287,  1288,  1289,  1579,  1839,  1840,
    1290,  1576,  1577,  1578,  1833,  1291,  2013,  2265,   779,   915,
     780,   916,  1096,   781,   917,  1098,  1296,   782,   918,  1100,
    1302,  1589,  2023,   783,   919,  1103,  1305,  1854,  1104,  1105,
    1106,  1593,  1594,   784,   920,  1603,  2029,  2173,  2275,  2332,
     785,   921,   786,   922,  2034,   787,   923,  1604,  2037,   788,
     789,   924,  1117,  2180,  1322,  1606,  2040,  1871,  1872,  2182,
    1320,   790,   925,  1122,  1123,  1124,  1125,  1334,  1126,  1127,
    1128,  1129,   791,   926,  1093,  2017,  1292,  2271,  1581,  1842,
    2164,  2270,   792,   927,  1335,  1619,  2044,  2047,   793,  1135,
    1338,   794,   930,  1137,  1138,  1878,  2191,   795,   931,  1141,
    1344,   796,   933,   797,   934,   798,   935,   799,   936,  1349,
     800,   937,  1351,  1885,  1886,  1631,  1888,  2058,  2200,  2060,
    2288,   801,   802,   939,  2207,  1149,  1354,  1635,  1781,  1972,
    1893,   803,  1637,   804,   805,   941,  1315,  1895,  2161,  2064,
    2212,  1710,  1532,  1533,  1812,  1814,  1990,  1761,  1762,  1954,
    1956,  2129,  2049,  2050,  2189,  2193,  2283,  1862,  1863,  2031,
    1864,  2032,  2065,  2066,  2209,  2067,  2210,  1523,  1524,  1525,
    1786,  1526,  1787,  2123,  1084,  1085,  1040,  1041,  1235,  1236,
    1482,  1483,  1484,  1485,  1486,  1182,  1386,  1427,  1031,  1054,
    1250,  1112,  1118,   396,   397,  1130,  1131,  1278,  1107,  1044,
    1045,   298,   299,   479,  1165,   486,   276,  1078,  1079,  1032,
    1056,  1185,  1424,  1743,  1841,  2008,  1062,  1108,  2109,  1034,
    1013,   855,   987,   988,  2111,  1035,   872,   873,  1036,  1213,
    1215,  1431,  1445,  1440,  1437,   247,  1887,  1361,  1233,  1313,
    2045,   225,  1252,   995,   388,   413,  1362,   265,  2070,  1818,
     422,   238,   685,  1208,   615,   169,   612,   291,   306,  2157,
     145,   308,   887,   581,    43,   453,   609,  2293,   577,  1157,
     419,  1737,   233,   230,  1846,   968,   185,  1254,   852,  1395,
     282,   683,   695,   523,   236,  1768,  1280,  1177,   605,   850,
    1530
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -2061
static const yytype_int16 yypact[] =
{
   -2061,   291,    22, -2061,  -158,   -91,   411, -2061, -2061, -2061,
     491,   491,    26,    26, -2061, -2061,   550, -2061, -2061, -2061,
   -2061,   696,   696,   308,   694,   694,   631,   461, -2061,   864,
     836, -2061, -2061, -2061, -2061,   -57,   660,   866,   569,   777,
     777, -2061,   601,    74,   664,   701,   806,   714, -2061,     3,
     867,   873,  1063, -2061,   305, -2061, -2061,   910, -2061, -2061,
   -2061,   787, -2061, -2061, -2061,   893,   820, -2061,    66, -2061,
      73,   491,    26, -2061, -2061, -2061, -2061,   929, -2061,  1124,
     117,   855,   961,  1103,   912, -2061, -2061,  1020,    26, -2061,
   -2061, -2061,   930,   932,   933,   934,   945, -2061, -2061, -2061,
   -2061, -2061,  1008,   955,  1153,   876,   979,   736, -2061,   365,
   -2061, -2061, -2061,    78, -2061, -2061,   958,  1059,  1181, -2061,
      40,   998, -2061,   135,   135,   975,   964,   970,   694, -2061,
     242,  1240,    34,   803,  1144, -2061, -2061,   978, -2061,  1155,
    1158,  1036,  1159,  1039, -2061,  1049, -2061, -2061, -2061,  1421,
   -2061, -2061, -2061, -2061, -2061, -2061,   994,  1095,  1120, -2061,
     912, -2061, -2061, -2061, -2061, -2061,   137, -2061,   -93,   -82,
     223, -2061, -2061, -2061, -2061,  1081,  1241, -2061,   459, -2061,
     473, -2061, -2061, -2061, -2061,    67,   155, -2061,   -51, -2061,
   -2061, -2061,   999,   738,  1349,  1015,  1241,  1241,  1015,  1077,
    1097,  1241,  1241,  1241,  1241,  1241,  1015,  1241,  1410,  1241,
   -2061,  1366, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061,  1015,  1008,   117,  1025, -2061,
    1025,  1025, -2061,  1232,  1025, -2061,  1385, -2061,  1296,    40,
     998, -2061,  1023,  1119,  1132,   998,   -24,  1006,   971, -2061,
    1241,  1112,  1202, -2061, -2061,  1378,   777,  1241,  1252, -2061,
     555, -2061, -2061,  1129, -2061,  1241,  1282, -2061,   794, -2061,
   -2061, -2061, -2061,  1041,  1245, -2061, -2061,  1015,  1015,  1241,
    1241, -2061,  1241,  1025,  1433,  1015,  1015,  1025,  1241,  1025,
   -2061,  1015,    27, -2061, -2061, -2061, -2061,   466,  1025, -2061,
   -2061,  1025,  1224,  1096,  1225, -2061,   912, -2061,   912, -2061,
   -2061,   998, -2061,  1052,  1152, -2061, -2061, -2061,  1006, -2061,
   -2061, -2061,    -4,     1, -2061, -2061,  1385,  1241,   554,   554,
    1241,   148,  1260,  1241,  1487,  1238, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061,   471,   576,  1241,
   -2061,  1074,  1065, -2061,   873,  1252, -2061, -2061, -2061, -2061,
    1025, -2061, -2061, -2061, -2061, -2061,  1241, -2061, -2061,   992,
    1025,  1285, -2061, -2061, -2061, -2061, -2061,  1025, -2061, -2061,
      96, -2061, -2061,   911, -2061, -2061, -2061, -2061,  1025, -2061,
    1025,  1243,  1025,   912, -2061,  1223,   912, -2061, -2061,   998,
   -2061,  1070, -2061, -2061,  1442, -2061,  1443, -2061, -2061,  1252,
    1088,  1241,  1487,  1025,   360,   -40,  1252,  1098, -2061,  1241,
    1091, -2061,  1091,   -25, -2061, -2061, -2061, -2061, -2061,  1252,
   -2061, -2061, -2061,   162,    68, -2061,  1154, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061,   992, -2061,  1137, -2061, -2061, -2061,
   -2061, -2061, -2061,  1252, -2061, -2061,   911, -2061,  1157, -2061,
    1258, -2061,  1025,  1025,  1025, -2061,  1252, -2061, -2061, -2061,
    1230, -2061, -2061,   106,  1107,  1145, -2061, -2061, -2061,  1025,
   -2061, -2061, -2061, -2061, -2061, -2061,  1315,    69,  1351,  1113,
   -2061, -2061, -2061,  1241,  1241, -2061, -2061,  2687,    26, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061,   556, -2061,    94, -2061,   992,  1252,
   -2061, -2061, -2061,  1241,   911, -2061,  1260,  1233,  1163, -2061,
    1192,  1260,  1340,  1241,  1519,   227,   -45,    63, -2061,  1128,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,  1195,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
    1241,  1025, -2061,  1091, -2061,  1230, -2061, -2061,  2424,  1549,
    1392,   166, -2061,  1252,    86, -2061, -2061, -2061,  1252, -2061,
   -2061,  1210, -2061,    -6,    -6,  2829, -2061,  1134, -2061, -2061,
   -2061, -2061,  1239,  3492,  1143, -2061, -2061,   556, -2061, -2061,
    1015, -2061,  1241,  1340, -2061,   782, -2061,  1241, -2061,  1241,
     759, -2061,  1241, -2061,  1241,  1236,  1241,  1241, -2061,  1421,
     197,  1241,  1165, -2061, -2061,  1374, -2061,  1383, -2061, -2061,
    -115,   474,   549,   584,   626,  1171, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061,  1265, -2061, -2061,  1252, -2061,
   -2061, -2061, -2061,  1025,  1025,  1398, -2061, -2061, -2061,   410,
   -2061, -2061, -2061,  1241,  1241, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061,   942,    47, -2061,   204, -2061,   113, -2061, -2061,
   -2061, -2061,   130,  1410, -2061,   476, -2061, -2061, -2061, -2061,
    1504, -2061,  1379, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061,  1211, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061,  1163, -2061,  2102, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061,   -12, -2061, -2061,  1317, -2061, -2061, -2061, -2061,
     744, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061,   783, -2061, -2061,
      23,  1241, -2061, -2061,   525,   530,  1025,  1588, -2061, -2061,
     -40,  1247, -2061,  1025,  1025, -2061,  1344,  1344,  1355, -2061,
    1025, -2061,   160,    -4, -2061, -2061,  1374, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
    1190, -2061, -2061,  1237, -2061,  1183,  1254, -2061, -2061, -2061,
   -2061,  3348,   113,  1625, -2061,  1295,  1295,   992,  1159,  1159,
   -2061, -2061,  1197, -2061,   113, -2061,  1262, -2061, -2061, -2061,
   -2061, -2061,    70,  1491, -2061, -2061,  1145,  1252,  1212, -2061,
    1214,  1025,  4161,  1228,   320,   779, -2061, -2061,  4758,   912,
    1267,  4838,  4758,  1437,   704,   843,    85,  1025, -2061, -2061,
    1543, -2061,    85,  1025,  1415,  1025,  4241,  4758, -2061,  2142,
     912,  1025,   912,  1025,   101,   102,  1025,   912, -2061, -2061,
    4291,  4420, -2061, -2061,  1025,  1025,   912,  1025, -2061,   646,
    1574,  1025, -2061, -2061, -2061, -2061, -2061, -2061,  1665, -2061,
   -2061, -2061, -2061, -2061,  1025,    81,   139,   116,  1244, -2061,
    1244, -2061, -2061, -2061, -2061,   547, -2061, -2061, -2061, -2061,
   -2061,  1025,  1241,  1512,  1512,   166, -2061, -2061, -2061, -2061,
    1499, -2061, -2061, -2061,  1252,  1288,  5490,  1234, -2061,  1025,
   -2061, -2061,  1457, -2061,  1519, -2061, -2061, -2061,  1025,  1025,
     992,  1171, -2061,   113,   -40,   -40,  1664,  1410, -2061, -2061,
   -2061,  1568,   602, -2061,  1159,  1250,  1025,  1253,  1256,  1159,
     466,  1263,  1264,  1268,  1269,  1270,  1273,  1276,  1277,  1253,
    1569, -2061,  4482, -2061, -2061, -2061, -2061,  1497, -2061,  1640,
   -2061, -2061, -2061,  1300, -2061,   466, -2061, -2061,  1271, -2061,
   -2061,   381,   912,  1580,  2198, -2061,  1364,  1401,   912,   824,
    1593,  3920,   906,   918,  1603,   145,  1271, -2061, -2061,    64,
   -2061, -2061, -2061,  1637, -2061, -2061, -2061,  1159,    85, -2061,
   -2061, -2061, -2061, -2061,  1341, -2061,    87,  1025, -2061,   275,
   -2061, -2061, -2061, -2061, -2061,  4758, -2061,  1338,  1605,  1694,
     807, -2061,  1343, -2061,  2330,  1611,   244,  1350,  1352,   258,
    1358,   385,  1572, -2061,  1401,  1572,  1025,  1613,  1323, -2061,
     882, -2061, -2061, -2061, -2061, -2061,  1513, -2061,    85, -2061,
     -32, -2061,    90, -2061, -2061,   396,  1711,  4050, -2061, -2061,
    1025,  1617,  4504,  1025,  1584,   967,  1654, -2061,  1434,  1389,
    1158,  1572,   783,   261, -2061,  1328, -2061,  1025,     0, -2061,
   -2061,  1241, -2061, -2061, -2061, -2061,   381, -2061, -2061,  1025,
   -2061,  1252,  1374, -2061, -2061, -2061, -2061,  1658,  1159,  5490,
    5490,  5490,    59,   914, -2061, -2061, -2061,  1197, -2061,  5490,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061,  1408, -2061, -2061,
    1315,   -40,  1660, -2061, -2061,   882,  1514,  1334,   420,   237,
    5490,  1373,  5490, -2061,  5490, -2061,  5443,  1336,  5490,  5490,
    5490,  5490,  5490,  5490,  5490,  5490, -2061, -2061, -2061,  4758,
    1592, -2061, -2061,  1439,  1497,  1686,  3177,  1472,  1546, -2061,
     417, -2061, -2061, -2061,   767, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061,   656,   912, -2061, -2061,   617,  1620,
    1620,  1620,  1620, -2061, -2061,  4758,  4758, -2061, -2061,    77,
    1650,   823, -2061,  1347,   704, -2061,  1025, -2061,    93, -2061,
   -2061,   892,  1615, -2061,   882,   142, -2061,   275, -2061, -2061,
   -2061, -2061,   110,  1384,    85, -2061, -2061,  4758, -2061, -2061,
   -2061, -2061,  1422, -2061, -2061, -2061, -2061,  1025,   320, -2061,
    1033, -2061, -2061,  1401,   381, -2061,  1579,   447,   579, -2061,
   -2061,  1025,   579,  1387, -2061,  1197, -2061, -2061,   115,   911,
   -2061, -2061,  3970, -2061,  1743,  1576,  4758,  4758, -2061,  4516,
    1025, -2061,  1618, -2061, -2061,  4758,   882, -2061, -2061, -2061,
    1711,  1585,  1025, -2061,   988,   100,   447, -2061, -2061,  1675,
   -2061, -2061, -2061,  1025, -2061,  1520, -2061, -2061,  1025,  1025,
   -2061,  1025,  1606,  1042,     1, -2061,  5216,  1158,   751,  5443,
    1353,  1353,   944, -2061, -2061, -2061,  5490,  5490,  5490,  5490,
    5490,  5490,  5132,   914, -2061,  1163, -2061,  1315,  1158, -2061,
   -2061, -2061,  1620, -2061, -2061,  1354,  1359, -2061,   882,  1620,
    1586, -2061, -2061, -2061, -2061,  1655,  1620,  1536,  1536,  1536,
     211,  1577, -2061, -2061,   384, -2061,    84,   830,  1025,   922,
      89,  1361, -2061,  1197, -2061, -2061,   303,  1362,   980,   488,
    1363,  1110,    92,   111,   531,  1367,  1121,  4744,   443,  4758,
      85, -2061,  1468, -2061, -2061, -2061, -2061, -2061,  1163, -2061,
   -2061,  1427, -2061, -2061,  1427, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,  1423,   320,
   -2061,    99,  1025,  1025,   460, -2061, -2061, -2061,    52,   690,
    1454, -2061, -2061,  1699, -2061,  1566, -2061,    41,  1671,  1620,
    1565, -2061, -2061,  1570, -2061, -2061, -2061,  1651,  4744,   457,
   -2061, -2061, -2061,  3081, -2061,  1440, -2061, -2061, -2061, -2061,
   -2061,    77, -2061, -2061, -2061,  1158, -2061, -2061, -2061,  1163,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061,  1506,  1163, -2061,
    1436, -2061,  1792, -2061, -2061, -2061,  1185, -2061,   882,   802,
   -2061,    67,    45,   598,    85,    85,  4744,   514,  1128,   912,
    1706, -2061, -2061,  1840, -2061,  1670, -2061, -2061, -2061, -2061,
    1579, -2061,  1025,   129,   656,   730,  1413,  1726, -2061,  1417,
     882,   792, -2061,   384, -2061, -2061, -2061,  4758,  1241,   656,
   -2061, -2061, -2061, -2061,   362,  1025,  4744,   545,  1453,  1849,
    1025,   618, -2061, -2061, -2061,  1552,  1553, -2061, -2061,  1033,
   -2061,   144, -2061,   608, -2061, -2061, -2061,  1241,  1687, -2061,
   -2061,  1252, -2061, -2061,  1241, -2061, -2061, -2061, -2061,  1536,
    1156,  1241,   779, -2061, -2061,  1536, -2061,  1252, -2061, -2061,
   -2061, -2061, -2061,  1025, -2061,  1025, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061,  1025, -2061, -2061,  1711, -2061,
    1662, -2061,   598,  1340,   598, -2061,  1197, -2061, -2061,   830,
     850,   850,  1353,  1353,  1353, -2061,  1136,  1458, -2061,  1025,
   -2061,  1570, -2061, -2061,  1620, -2061, -2061, -2061,  1241, -2061,
   -2061,  1241, -2061, -2061, -2061, -2061, -2061, -2061, -2061,    11,
   -2061, -2061, -2061,  1655, -2061, -2061, -2061,   381,   381,   381,
   -2061, -2061, -2061, -2061, -2061,  1253,  1364,  5317, -2061,  1025,
    1253,  1253,  5490, -2061,  1253,  1253,  1253,   422,  1253,  1253,
   -2061, -2061,  1598,  4744, -2061,    85, -2061, -2061,   477,   532,
   -2061, -2061,  3698, -2061,   540,   143, -2061, -2061, -2061, -2061,
    1058, -2061,  1538, -2061,  1524, -2061, -2061, -2061, -2061, -2061,
   -2061,   298,   298,   298,   298,  1241, -2061, -2061, -2061, -2061,
    1188,  1241, -2061, -2061, -2061, -2061,    32, -2061,  1671, -2061,
   -2061, -2061, -2061, -2061, -2061,  4758, -2061,  4758,    77, -2061,
   -2061, -2061,  3081, -2061,  1025,  1744,  1435,   984,  1762,  1438,
     118,   882, -2061, -2061,  1825, -2061, -2061, -2061, -2061,   802,
   -2061,  1701, -2061,  1241,  1594, -2061, -2061,  1340,    85, -2061,
    4758,   197,   567, -2061, -2061, -2061,  1025,  4758,   711, -2061,
   -2061, -2061,  1737,  1619, -2061,  1738, -2061,  1641, -2061, -2061,
   -2061, -2061,  1417, -2061, -2061, -2061,  1621,  1740,  1596,  1587,
    1364, -2061,  4758,   118, -2061,  1602, -2061,   882, -2061,  1775,
    1495, -2061, -2061,  1158, -2061,    60,  1883, -2061,  1032, -2061,
   -2061, -2061,  1252,  1776,  1673,  1824,  5233,   300,  1241, -2061,
   -2061,   300, -2061,  1241,  1288, -2061, -2061, -2061,  1452, -2061,
   -2061, -2061,  1241, -2061, -2061, -2061,  1241, -2061, -2061, -2061,
   -2061,   300,   300,    50,    50, -2061, -2061, -2061, -2061, -2061,
    1454, -2061,  1226, -2061, -2061, -2061,   830, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,  1163,
    1745,  1163,  1746, -2061, -2061,  4758, -2061, -2061, -2061, -2061,
   -2061,  1767, -2061, -2061, -2061, -2061, -2061, -2061,  1620,  1620,
    1620,  1620,   300, -2061, -2061,   300,    50,    50, -2061, -2061,
   -2061,  4744,  1571,  4744,  1575, -2061, -2061, -2061, -2061, -2061,
    1768, -2061,   984, -2061,  1803, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061,   118,  1033, -2061, -2061,  1033,   -31,  1025, -2061,
    1241,  4744, -2061, -2061,   897,  3706, -2061,  1857,  1667,  1692,
     450, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061,  1025,  1021, -2061, -2061, -2061,  1769,
    1649,  1025,  1454,  4744, -2061,  1849, -2061,  1351,  1822,  1351,
    1596,   499, -2061, -2061,  1770, -2061,  1656, -2061, -2061, -2061,
     728, -2061, -2061,  1241,  1828,  1700, -2061,  1086, -2061,  1719,
    1108,  1487,  1731,  1488,  1241,  1159,  1241,  1025, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
    1535, -2061, -2061, -2061, -2061,   765, -2061, -2061, -2061, -2061,
   -2061, -2061,   494, -2061,   732, -2061, -2061,  1452, -2061,  1025,
     113, -2061, -2061, -2061,   300, -2061, -2061, -2061, -2061, -2061,
   -2061,  1163, -2061,  1163, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,  4758,
   -2061,  4758, -2061, -2061, -2061, -2061, -2061,  1879,  1033,  1033,
   -2061,  1523,  1623,   912,   510, -2061, -2061, -2061, -2061,  1589,
    4758, -2061,  1241,   973,  1691, -2061,  1695, -2061, -2061, -2061,
   -2061, -2061, -2061,  1025, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,  1025,  1351,
   -2061,  1025,  1785, -2061, -2061, -2061, -2061, -2061,   912, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061,  1148,  1252,  1241,  1241,
    1760, -2061,  1241, -2061, -2061, -2061, -2061,   166, -2061,  1241,
   -2061,  1025,  1025,   734,  1756, -2061,  1646,  1252,   765, -2061,
   -2061, -2061, -2061, -2061, -2061,   300, -2061, -2061, -2061, -2061,
     300, -2061,  1025, -2061,  1148, -2061, -2061, -2061, -2061,  1454,
    1454, -2061,  4758,  1033, -2061,  4758,  1241,   912,   912,  1633,
   -2061,  1025, -2061,  1518,  1025,  1804, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061,  1025, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061,  1252,  1252,  1241, -2061,  1252,
   -2061,  1252, -2061,  1364, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061,  4758, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061,   320,   912,  1241, -2061, -2061,
    1025, -2061, -2061, -2061, -2061, -2061, -2061,  1252, -2061, -2061,
   -2061,  1897, -2061,   320, -2061, -2061,  4758, -2061, -2061
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -2061, -2061, -2061, -2061,  1941, -2061, -2061, -2061,    44, -2061,
   -2061, -2061, -2061, -2061,  1595, -2061, -2061, -2061,  1199, -2061,
   -2061,    56,  1928, -2061, -2061,  1898,   245, -2061, -2061, -2061,
   -2061, -2061,  1758,  1821, -2061, -2061,  1777,   112, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061,  1766, -2061, -2061, -2061, -2061,
    1748, -2061, -2061, -2061, -2061, -2061,   195,   628, -2061, -2061,
   -2061, -2061,  1446, -2061, -2061,  1365,   811, -2061, -2061, -2061,
   -2061, -2061, -2061,  1522, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061,  1831, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,   604, -2061,
     599,   818, -2061, -2061, -2061, -2061, -2061,  1012,    75, -2061,
    1368, -2061, -2061, -2061, -2061, -2061, -2061,   123, -2061, -2061,
    1749, -2061,  1866, -2061, -2061, -2061, -2061,  1590, -2061, -2061,
    1864,   235, -2061, -2061, -2061, -2061,  1741, -2061,  1930,  1826,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,  1099, -2061,
   -2061, -2061,  1397, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061,   680, -2061, -2061, -2061,  1666,
   -2061, -2061,  -562, -2061, -2061,  -307, -2061, -2061, -2061,  -416,
   -2061, -2061, -2061, -2061, -2061, -2061, -1308, -1304,  1126, -1298,
   -2061,    76, -2061, -2061, -2061,   295,   299, -2061,   407, -2061,
     302, -2061,  -123, -1293, -2061, -2061, -1292, -2061, -1287, -2061,
   -2061, -2061,  1122, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061,  1430, -2061, -2061, -2061,  1026, -2061,
    -922, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,  -101, -2061,
   -2061, -2061, -2061, -2061, -2061,  -237, -2061, -2061, -2061, -2061,
     274, -2061, -2061, -2061, -2061, -2061,  1166, -2061, -2061, -2061,
   -2061, -2061, -2061,   121, -2061, -2061, -2061, -2061, -2061,  1882,
    1037, -2061,   233, -2061, -2061, -2061, -2061,  1515, -2061, -2061,
   -2061, -2061, -2061, -2061,  -897, -2061, -2061,   158, -2061, -2061,
   -2061, -2061,   954,   595,   597, -2061, -2061,   285, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061,   953, -2061, -2061,   248, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061,  -389, -2061,   213,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
     748, -2061, -2061,   752, -2061, -2061, -2061, -2061,   475,   210,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061,    28,   750, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061,   742, -2061, -2061, -2061,   193,
   -2061, -2061,   458, -2061, -2061, -2061, -1435, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2060,   936,
   -2061, -2061,   177, -2061, -2061,   436, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061,   682, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061,   719, -2061,   170, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,   919,
   -2061,   920, -2061, -2061,  1123, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061,   909,   421, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061,    -2, -2061,   427, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061, -2061,  -856, -2061, -1184, -2061,
   -2061, -1074, -1208, -1102, -2061,   340, -2061, -1403, -2061, -2061,
   -2061, -2061,     2, -2061, -2061, -2061, -2061,  -112, -2061, -2061,
     200, -2061, -2061, -2061, -2061,    -1, -2061, -1317, -1761, -2061,
   -2061,   539, -2061,  -921, -1295,  -873, -1223, -2061, -2061, -2061,
   -1213, -1211, -1198, -1192, -1191,   105,  -222,   -92,  -118, -1117,
    -884,   149,   950, -1049,   -84, -2061, -1111, -2061,  -824, -2061,
     829,  -224,  -227, -2061, -2061,  -579,   938,  -846, -1035,    -5,
    -815, -2061, -2061,   455, -1065, -1668, -1003,  -858, -1164,   425,
    -629,  -195, -2061,  1082,  -178,  -672,  -715,  -308,  -340,  -970,
   -2061, -2061, -2061, -2061, -2061,  1827, -2061,   430,   838, -2061,
   -2061, -2061, -1679,  1208,    -9,  1750,   785,  -450, -2061,  1009,
    -410,  1456, -2061,  -627, -2061, -1089,  1087,  -430,   749, -2061,
   -2061,  -710, -2061, -1781,  -175,  -566,  -518,  -172,  -974, -2061,
     623, -1369,  -827, -1092, -2061,  1257,  2026,  -935, -2061, -2061,
   -2061, -2061, -2061, -2061, -2061,   621, -2061,   174,  -713,  1089,
    -129
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1595
static const yytype_int16 yytable[] =
{
     122,   258,   478,   194,   302,   687,   301,   304,   908,  1255,
     560,  1592,  1143,   871,  1055,   876,   408,   616,   617,  1330,
    1039,   277,   278,  1502,   854,  1503,   283,   284,   285,   286,
     287,  1071,   289,   300,   292,   300,   300,  1048,  1504,   300,
     940,   998,   999,  1277,  1505,  1506,  1545,  1339,  1242,  1738,
    1739,  1277,  1534,  1535,  1536,  1323,   372,   579,  1355,  1226,
     376,   446,   378,   833,   194,   882,  1086,  1940,  1677,    22,
    1043,   389,  1678,   347,   389,   348,   122,  1033,  1679,  1132,
     357,  1268,   355,  1680,  1681,   811,  1033,  1065,   300,  1682,
     360,  1077,   300,  1077,   300,  1414,  1077,  1277,  1540,   165,
     105,  1097,  1099,   300,   369,   370,   300,   371,  1077,  1636,
    1116,   596,  1447,   377,    89,  1139,  1033,  1785,  1004,   450,
      85,  1077,   867,   382,   500,   290,  1599,   867,    92,  1383,
     263,   186,  1933,   435,  2068,  1816,   446,  1791, -1558,   105,
    1400, -1594,   689,   447,   127,   493,   950,    54,   165,  1538,
     449,  1571,   410,  1986,  1383,   415,   417,    41,   420,  1383,
     877,    52,  1383,  1370,   266,   300,   462,   403,   464, -1543,
     428,    63,   403,   608,   429,   300,  2162,   434, -1516,  1316,
    1586,  1383,   300,  1849,   165, -1520,   165,  1209,   485,   450,
     991,   436,  1216,   461,  1265,   300,   484,   300,  1572,  -190,
    1583,  2052,   876, -1480, -1480,     4,   826,  1555,    63,   834,
     598,  1331,    88,   867,  2062,  2054,  1121,  1231,   480,  1570,
     300,   972,   395,  1881,   928, -1558,  1396,   307,  1626,  1966,
     696,   475,  1358,   305,  1154,   389,   477,   389,   487,   561,
    1365,   963,  1091,   253,   489,  1844,  1231,  1371,   973,   974,
    1276,   495,  1120,   839,   868,  1860,    18,  -191, -1594,  1317,
      32,  1629,    19,   884,   613,  2342,  1358,   300,   300,   300,
     865,  1187,   165,  1521,   833,   520,  2198,  1417,  2201,   250,
    1293,  1628,  1328,  2347,   575,  1685, -1520,  1865,   562,  1121,
    1908,     3,   262,  1277, -1538,  1356,  1913,    12,   570,   356,
    1711,   498,  1877,   840, -1594, -1565,  1709,  1711,   437,   395,
     451,  1601,   468,   437,  1711,  1573,    91,  -190,   583,   584,
      41,  1810,  1139,   618,  2063,   251,  1522,  1231,  1545,  1042,
    1845,  1198,  1763,     5,   389,  1715,  1042,   929,    20,   951,
     614,   599,  1735,  1714,  2160,  1055,  1792,  1366,   600,   438,
    1121,  1379,  1155,   254,   438,  1266,   439,    64,   610,   619,
    1957,   439,    41,   174,    13,  1574,   300,  1284,   106,  1194,
    1195,  1329,   262,  1383,    41,  -191,  1520,   354,  1600,  1201,
     451, -1532,  1055,  1358,     5,   622,  1422,   952,   698,   698,
     229,   267,  1861,   682,    64,   688,    55, -1543,   -31,   437,
     693,  1071,   297,  2163,   269,  1325,  2016,   690,    65,  1171,
     620,    14,  2277,  1055,  1448,  1764,  1794,   494,  2285,  1384,
     834,  1507,  1775,  1708, -1520,  1199,  1200,   810,   440,   869,
     264,   317,   815,   440,   816,  1934,   297,   820,   404,   821,
     438,   823,   824,   407,  1384,   608,   830,   439,  1585,  1384,
    1537,  1539,  1384,   975,  1557,  1896,  1987,   827,   866,   856,
   -1520,  1055, -1520,  1824,  1187,  1187,  1187,   107,  1967,   275,
     853,  1384,   578,     5,  1187,   190,   177,    89,  -632,  1005,
      56,  1541,  1587,  1793,  1596,  1542,  1417,   175,   861,   862,
    1325,   441, -1520,  1332,   597,  1187,   441,  1187, -1520,  1187,
      86,  1433,  1269,  1187,  1187,  1187,  1187,  1187,  1187,  1187,
    1187,   501,  1419,  1834,  1333,   828,  1385,  1616,  1611,   440,
     442,  1620,  1621,  -190,  1623,   442,   981,   297,   190,   297,
    1627,  1638,   297,   152, -1520,   297,   356,  2126,   275, -1516,
    1852,  1745,   297,   297,   297,  1873, -1472,  1423, -1520,  1755,
    1277,  1359,    75,  1575,   594,  1050,  1042,   297,  1383,   997,
     297,   443,   958,   883,  -630,  1055,   443, -1594,  1756,  1325,
   -1520,   190, -1520,  2158,  1092,  2041,  2159,  1202,  1968,  1050,
    1425,  -191,   441,  1336, -1538,  1359,   297,  1432,  2148,   962,
    2150, -1518,  -632,   485,     4,  1545,   965,   966,  2089,  1918,
     176,  1383,  2090,   971,  1512, -1565,  1285,   426,  2091,   877,
    1374,   442,  1711,  2093,  2094,   976,   106,  1241,  2167,  2095,
    1742,   300,  1397,  1778,  2340,   300,  1686,    55,   300,   300,
    -776,  1325,  1205,  1959,   858,   300,   954,  1161,   424,   481,
    1930,    16,   955,  1311,  1817,  1950,  1188,  1554,  2174,  2195,
    2196,   521,   443,  1418,  1147,  1823,   885,   980, -1520,   425,
   -1433,  1825, -1594,  1384,  1696,  2203,   386,  1306, -1516,  1286,
      23,  1187,  1187,  1187,  1187,  1187,  1187,  1187,  -630,   297,
    1307,  1148,  1707,  1775,   177,  1771,   427, -1594,  1961,  1312,
    2175,  1607,  1196,  1325,   959,  1607,   492,  2268,  1991,  1046,
    1993,  1850,  1359,  -210,   175, -1516,  2204, -1594,  2222,  1008,
    2176,    56, -1534,  1687,  2205,   107,   986,  1162,   175,   601,
    1094,  1419,     5,    26,  1109,  2263,  1113,  1153,  1113,  1119,
    1958,  1094,  1882,  2021,  1936,  1937,  1938,  1337,  1848,  1528,
     482,  2241,   297,   387,  1164,  1766,  1113,  2113,  2108,  1779,
    1695,   504,  1387,  1388,  1389,  1390,   859,  1391,  1513,   300,
   -1478,  1960,   297,    29,  1050,  2053,  2011,  2121,  2122,    75,
    2139,  2140,  2141,  2142,   960,  1939,   300,   485,   485,  1686,
    1944,  1945,  1206,    75,  1947,  1948,  1949,  2206,  1952,  1953,
    1110,  1251,   505,  2242,  1191,  1744,    30,  1166,  2269,   506,
     175,  2061,  1875,   190,  1912,  1251,  1175, -1594,  1782,   300,
     300,  1835,   356,  1277,   195,  1057,  1962,   176,  2143,  1964,
     150,  2144,  2056,   297,  2306,  2307,   297, -1594,   196,   197,
     956,   176,  2184,  1951,  2185, -1516,  1111,   623,  1114,  1188,
    1188,  1188,   841,  1134,  2124,  2124,  1826,  2186,  1384,  1188,
    2308, -1532,  1145,  2187,  2188,  1829,  2321,  2322,  1836,  1898,
     198,  1015,  1251,  1325,  1325,    75,  1687,    33,  1184,  1521,
    1188,   508,  1188,   411,  1188,   412,  1434,  1017,  1188,  1188,
    1188,  1188,  1188,  1188,  1188,  1188, -1594,  2177,   190,  1976,
    1977,  1384,   842,  1251,  1183,  1325,  1061,  2124,  2124,   199,
     200,  1559,   201, -1516,  1560,   812,  2216,  1561,  1562, -1594,
    2028,   202,   250,   176,   259,  1989,    34,   843, -1594,   307,
     310,  1119,  1522,  1161,  1997,   316,  1142,  1899,   261,  1900,
    1783,  1992,   938,  1994,   509,  2302,   139,  1387,  1388,  1389,
    1390,   119,  1391,  2243,  2244, -1476,  1996,    36,   140,   813,
    1784, -1594,   845,  1688,   203,   204,    38,  1282,   251,  2215,
    2254,   529,  1364,  1018,   356,   205,  1055,   844,  1244,   141,
    1866, -1594,   325,  1298,   485,  1110,  1121,   142,   942,  2246,
    1387,  1388,  1389,  1390,  1744,  1391,  1367,    68, -1473,  -210,
    1867,   398,   530,  1373,   847,  2039,  1560,   437,  1055,  1561,
    1562,   356,   846,  1162,   512,   362,   300, -1594,   190,   119,
     358,  1217,  2208,  2125,  1299,  1047,    44,  1021,   326,   943,
    1022,  2214,  1300,  2236,    49,  1837,   944, -1594,  2309,  2310,
     363,  2247,  1187,   327,  2344,    45,  1238,  1187,   438,  1697,
     206,  1597,  2027,  1527,   848,   439,  1188,  1188,  1188,  1188,
    1188,  1188,  1188,  1023,   143,   146,    53,  2128,  1528,   190,
     297,  1184,  1184,  1184,  2237,  2145,  2146,  1652,  1598,  2311,
    2312,  1184,  1115,   328,    46,   409,  2138,   437,   817,   469,
     416,  2318,    47,  1046,    50,   818,  2319,  1380,  1381,  1382,
    1151,  1515,  1184,  2147,  1184,  1301,  1184,  1393,   945,  1860,
    1184,  1184,  1184,  1184,  1184,  1184,  1184,  1184,  1067,   863,
     147,   148,  1068,  1046,  2267,  1519,  1325,   440,   438,    59,
    1429,  1024,  2183,   538,  1325,   439,  1436,  1438,  1439,  1441,
     864,  1843,  1444,  1446,  2178,  2179,   279,  2168, -1538,  1072,
    1073,  1645,  1645,  2181,   288,  1563,  1564,  1633, -1594,   602,
    2134,  1634,   190,  1074,   607,   207,    60,  2169,  2010, -1538,
    1046,   946,    61,   295,  1565,  1566,  1025,  1026,  1642,    62,
     297,   468,  1325,   300,   300,  1922,  2108,  1458,  1459,   190,
     441,  2248,  2249,  1516,     5,    41,  1521,   437,  1605,   454,
     329,   455,  1027,   272,  1571,   208,  1614,   440,    72,  1075,
    1615,    10,   330,   249,    93,    10,  1460,   249,   190,   442,
    1028,  2010,  1461,  1838,  1749,   367,   368,  1752,  1029,  2326,
      75,   297,  1757,   374,   375,  -345,  -345,  1605,   438,   381,
     384,   947,  2255,   319,   320,   439,  1861,  1563,  1564,  1522,
    2258,  1572,    79,  1463,   297,   209,  2130,  1464,  2132,    81,
     443, -1425, -1425, -1425, -1425,  2261,  1565,  1566,  2232,   525,
     441,  1269,   526,  1548,    82,  2259,    94,  2260,  1184,  1184,
    1184,  1184,  1184,  1184,  1184,  1649,  1650,   527,   503,  1387,
    1388,  1389,  1390,  2280,  1391,  2281,  1347,   528,  1348,   442,
     331,   332,  2282,   103,  1699,  1700,  1701,  1702,  1703,  1704,
    1706,  1389,  1390,   333,  1391,   334,    95,   440,    96,  1909,
     115,  1910,  2289,  2290,  1046,  1426,  1012,   116,   452,  1430,
    1049,   263,  1050,  1969,   297,  1970,  1063,  1442,  1443,  2020,
     443,  1080,  1081,  1259,  1260,  1261,  1262,  1080,  1088,  1090,
    2010,  1983,   117,  1984,  1049, -1424, -1424, -1424, -1424,   504,
    1080,  1899,  2330,  1900,   119,  2273,  1736,  2221,  1573,  1088,
    1144,   125,  1146,  1387,  1388,  1389,  1390,   134,  1391,   137,
     441,  1387,  1388,  1389,  1390,  1392,  1391,   195,  2225,  2226,
    -990,  2291,  2292,  1747,   144,   129,  2333,   130,   131,   132,
     505,   196,   197,  1387,  1388,  1389,  1390,   506,  1391,   442,
     133,  1698,  1978,  1979,  1980,  1981,   335,  1188,  1574,   507,
     136,  1186,  1188,   155,  1645,   156,   157,   171,  2256,   172,
    2257,  -990,   186,   198,   867,   173,   336,   224,  -990,  1387,
    1388,  1389,  1390,   227,  1391,   228,   232,  1751,   229,   231,
     443,  1211,   234,  1876,   235,   237,   300,  2323,  2253,   241,
    2324,   242,   243,   257,   271,    41,   274,   275,  1917,  1851,
     529,   280,   199,   200,   281,   201,   290,   297,   303,   508,
     305,   307,  1902,  1905,   202,   313,  1243,  1478,   312,  1907,
    1480,  1481,  1928,   314,   349,   350,  1911,   352,   356,  1914,
     300,   530,   359,   361,   365,  1879,   364,  1015,   531,  2341,
    -990,   373,  1879,  1080,   390,   392,   391,   400,   401,   418,
     421,  1080,  1283,  1017,   300,   423,   430,   203,   204,   532,
     431,   448,  1943,   463,   466,   471,  -362,   473,   205,  1049,
     476,  2348,   509,   490,   488,   510,   511,   518,   809,  1401,
    1402,   522,   571,  1931,   533,  1324,  1932,   563,   573,   576,
     534,   580,   603,  1080,   300,   582,   606,  1080,   608,  1387,
    1388,  1389,  1390,  -990,  1391,  1342,   604,  1754,  1283,   190,
    1387,  1388,  1389,  1390,   611,  1391,   684,   535,  1759,   621,
     686,  1403,   694,  1404,   536,  1387,  1388,  1389,  1390,   701,
    1391,  1243,  -990,  1925,  1088,   702,  1575,   537,   806,  1018,
     822,   319,   512,   206,  1186,  1186,  1186,   831,   838,   849,
     437,   851,   857,   888,  1186,   889,  -842,  1405,  1406,  1407,
    1982,   264,   538,   932,   539,   613,  1985,  -990,   964,  1184,
    1324,   967,   540,  -990,  1184,  1186,   970,  1186,   983,  1186,
     984,   986,  -215,  1186,  1186,  1186,  1186,  1186,  1186,  1186,
    1186,   438,   992,  1021,   989,  1942,  1022,   994,   439,  1000,
    1946,  2300,  1003,   541,  1408,  1006,  1409,  1009,  2018,  1010,
    1037,  2228,  1058,  1066,  1410,  1387,  1388,  1389,  1390,  1083,
    1391,  1150,  1152,  2127,  1167,  1158,  1717,  1173,  1718,  1023,
    1176,  1719,  1189,  1192,   877,  1203,  1234,  1227,  1453,  1454,
    1455,  1720,  1232,  1237,  1795,  1239,  1456,  1796,  1210,  1324,
    1245,  1212,  1251,   542,  1214,  1797,  1798,  1799,   207,  1080,
    1253,  1218,  1219,  2024,  2072,  1256,  1220,  1221,  1222,  2030,
     440,  1223,  1595,  2112,  1224,  1225,  1263,  1275,  2114,  1243,
    1279,  1294,  1295,  1297,  1457, -1427,  1608,  2119,  1411,  1304,
    1308,  2120,  1314,  1080,  1309,  1310,  1319,  1024,   208,  1321,
     165,  1121,  1121,  1343,  1346,  1624,  1350,  1352,   468,  1353,
   -1551,  1324,  1377,  1394,  1398,  1415,  1428,  1632,  1435,  1449,
    1450,  1508,  1042,  1531,  1546,  1551,  1569,  1584,  1588,  1602,
    1610,  2165,  1617,   441,  1618,  1630,  1283,  1640,  1625,  1647,
    1643,  1712,  1025,  1026,  1716,  1713,  1736,  1391,   209,  1765,
    1418,  1186,  1186,  1186,  1186,  1186,  1186,  1186,  1748,  1750,
    1753,   293,   442,   300,  1758,  1767,  1770,  1760,  1027,  1800,
    1788,  1721,  1522,  1324,  1811,  1813,  1722,  1827,  1815,  1830,
    1819,  1831,  1458,  1459,  1853,  2166,  1028,  1801,  1856,  1723,
    1857,  1868,  1869,  1746,  1029,  1870,  1883,   297,  1884,  1892,
    1903,  1894,  1926,   443,  1688,  1802,  1955,  1974,  1975,  1999,
    2001,  1460,  2005,  2007,  2012,  1080,  2015,  1461,  2033,  2019,
    2036,  2038,  1861,  2043,  2046,  2048,  2055,  2051,  2057,  2059,
    2069,  2076,  2073,  2074,  2116,  2252,  2135,  1724,  2217,  2149,
    1462,  2131,  2133,  2151,  2153,  2156,  2170,  2171,  1463,  2231,
    2172,  2233,  1464,  1803,  2190,  1412,  2192,  2199,  2211,  2218,
    2063,  2219,  2223,  2229,   300,  2085,  2230,  2240,  2262,  2264,
    2266,  2278,  2287,  2272,  2297,  2279,  2314,  1776,  1777,  2315,
    2327,  2329,  1465,  1466,  2331,  1725,  2346,    15,  1467,   433,
      28,   273,    74,   193,   270,   260,  1413,  1612,  1468,   294,
     595,  1804,   808,  1357,  1641,  1469,   517,   226,  1646,  1726,
    1470,  1360,  1160,  2071,  2022,   151,   296,   153,   819,    67,
     309,   699,  2092,   465,   402,  1007,   245,   990,  1471,  1924,
    1847,  1921,  1920,  1727,  2251,   624,  1002,  2274,  1728,  2235,
    1170,  2317,   982,  1324,  1324,  2305,   170,  1965,  1729,  1080,
    1080,   585,  1730,  2025,  1805,  1258,  1741,  1740,  1935,  1267,
    1963,  1988,  1553,  1549,  1806,   389,  1822,  1859,  1995,  1580,
    2155,  1568,  2014,  2026,  1832,  1324,  1858,   300,  1639,  2294,
    1303,  1609,  2042,  2295,  2296,  1326,  1341,  2299,  1327,  1133,
    1880,  1929,  1890,  2197,  2301,  1889,  1889,   300,  1891,  2316,
    2240,  2276,  2202,  2035,  1790,  2213,  1318,  1510,  1874,  1190,
    1731,  1897,  1452,   318,   996,   825,  2328,  1582,  1274,   414,
    1732,  1193,  2320,    76,   969,  1769,  1807,  1049,  2115,     0,
    1197,  2325,     0,     0,     0,     0,     0,     0,  1915,     0,
    1916,     0,     0,   910,     0,     0,     0,     0,  -933,     0,
       0,  -933,     0,     0,  -933,  -933,  -933,  2335,  2336,     0,
       0,  2338,  2337,  2339,   468,     0,     0,     0,     0,     0,
    1046,     0,     0,     0,  1472,  1473,  1474,  1475,  1476,     0,
    1477,     0,  1478,  1479,     0,  1480,  1481,     0,  1046,     0,
       0,     0,  2343,     0,     0,     0,     0,     0,     0,  2345,
    -933,     0,  1243,  1243,  1243,     0,     0,     0,     0,     0,
       0,     0,  1186,     0,     0,     0,     0,  1186,     0,     0,
       0,     0,     0,   468,  -933,     0,     0,     0,     0,     0,
    1080,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -933,     0,     0,     0,  1014,     0,     0,   867,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1015,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1017,     0,   468,     0,     0,     0,     0,     0,     0,  1998,
       0,     0,     0,     0,     0,  2009,  1324,     0,  -933,  -933,
       0,     0,     0,     0,  1324,     0,     0,     0,     0,     0,
       0,     0,     0,  1080,     0,     0,     0,     0,     0,     0,
    1015,  1595,     0,     0,     0,     0,  -933,  -933,     0,     0,
       0,     0,     0,  -933,     0,     0,  1017,  -933,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2009,     0,
       0,     0,  1324,     0,     0,     0,  -933,     0,     0,  1101,
       0,     0,     0,     0,  -933,     0,  1018,  -933,  -933,     0,
       0,     0,  2110,     0,  -933,     0,  2110,     0,  -933,     0,
    -933,     0,     0,  -933,     0,  -933,     0,     0,     0,     0,
       0,     0,     0,     0,  1247,     0,  2110,  2110,  -933,  -933,
       0,     0,     0,     0,  -933,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -933,     0,  -933,     0,  1102,     0,
    1021,  -933,  1018,  1022,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   437,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -933,     0,     0,  2110,     0,     0,
    2110,     0,  1015,     0,     0,     0,  1023,  -933,     0,     0,
       0,     0,     0,  1019,  -357,   626,     0,     0,  1017,     0,
    1020,     0,     0,     0,   438,     0,  1021,  2009,     0,  1022,
       0,   439,     0,     0,  -933,   627,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   628,     0,
       0,   629,   630,   631,   632,   633,   634,   635,     0,  1088,
       0,     0,  1023,     0,     0,     0,  2194,     0,     0,     0,
    -933,     0,     0,     0,  1024,     0,     0,     0,     0,  -933,
    -933,     0,     0,     0,     0,  2110,     0,     0,   636,     0,
     637,   638,   639,   640,   641,   642,     0,  1101,     0,  -933,
       0,     0,  2234,   440,  1018,  -933,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1025,
    1026,     0,     0,  -933,     0,     0,     0,     0,     0, -1594,
    1024,  -933,   643,     0,  -933,     0,     0,     0,     0,  2110,
    -933,  -933,  -933,     0,     0,  1027,  -933,     0,  -933,  -357,
    -933,  -933,  -933,  -357,     0, -1041,  1047,     0,  1021,     0,
       0,  1022,     0,  1028,     0,     0,   441,     0, -1041,     0,
       0,  1029,     0,   190,   297,  1025,  1026,     0,     0,     0,
       0, -1538,  -357,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1023,   442,     0,  -357,  1283,     0,
       0,  1027, -1538,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  2284,     0,   644,  2286,     0,     0,  1028,
       0,     0,     0,     0,     0,     0,     0,  1029,    41,     0,
     297,   645,     0,     0,     0,     0,   443, -1575,     0,     0,
       0,  -357,  -357,     0,  1248,     0,  2303,     0,     0,  -357,
     646,     0,     0,  -357,     0,     0,     0,     0,     0,     0,
    2110,     0,  1024,     0,     0,  2110,     0,   647,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -627,   586,     0,
    -667,     0,  -667,     0,     0,     0,     0,  -667,     0,  1088,
     648,     0,     0,     0,     0,  -667,     0,     0,     0,     0,
    2334,     0,     0,     0,     0,   649,     0,  1025,  1026,     0,
       0,     0,   650,     0,   651,     0,     0, -1594,     0,     0,
       0,  -357,     0,     0,     0,  -357,     0,   652,  -667,  -667,
       0,     0,     0,  1027,     0,     0,  -667,   653,     0,     0,
       0,     0,     0, -1041,   654,  1283,  -357,     0,  -667,     0,
       0,  1028,  -667,     0,     0,     0, -1041,     0,     0,  1029,
       0,   190,   297,     0,  -667,  -357,     0,     0,  -357,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   655,     0,   656,   657,   658,     0,     0,  -667,     0,
       0,     0,     0,     0,     0,  -667,  -667,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   659,     0,     0,
       0,     0,  -627,     0,     0,     0,  -627,     0,     0,     0,
     586,     0,  -667,     0,  -667, -1575,  -667,     0,     0,  -667,
       0,     0,     0,   660,   661,   662,     0,  -667,  -667,     0,
       0,     0,  -667,     0,     0,     0,   663,     0,     0,   664,
       0,     0,     0,     0,     0,     0,  -667,     0,  -357,     0,
    -627,     0,     0,  -667,     0,     0,  -667,  -667,     0,  -357,
    -667,  -667,     0,     0,  -667,     0,     0,     0,  -667,     0,
       0,  -667,     0,  -667,     0,     0,  -667,     0,     0,     0,
    -667,     0,     0,     0,  -667,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -667,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -667,     0,     0,     0,  -667,     0,  -667,
    -667,     0,     0,     0,     0,     0,  -667,  -667,  -667,     0,
       0,     0,     0,     0,     0,   700,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -667,
       0,     0,     0,     0,     0,     0,     0,     0,  -667,     0,
       0,     0,     0,     0,  -667,     0,     0,     0,     0,     0,
    -667,     0,     0,     0,  -667,     0,     0,     0,  -627,     0,
       0,     0,     0,     0,     0,  -667,     0,     0,  -667,     0,
       0,     0,     0,     0,  -667,  -667,     0,     0,  -667,  -667,
       0,     0,     0,     0,     0,     0,  -667,  -667,     0,     0,
       0,     0,  -667,  -667,  -667,  -667,     0,     0,  -667,     0,
       0,     0,  -667,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -667,     0,     0,     0,     0,     0,     0,     0,
       0,  -667,     0,     0,     0,     0,     0,     0,     0,     0,
    -667,     0,  -667,  -667,     0,  -667,  -667,     0,  -667,  -667,
       0,  -667,     0,  -667,     0,     0,     0, -1508,  -667,     0,
   -1508,     0,     0, -1508, -1508, -1508,     0,     0,  1268,  -667,
       0,     0, -1508,     0,  -667,     0,     0,     0,     0,  -667,
       0,  -667,     0,     0,     0,     0,     0,     0,     0,     0,
    -667,     0,     0,     0,     0,     0,  -667,     0,     0,   587,
       0,     0,  -667,     0,     0,     0,     0,     0,     0, -1508,
       0,     0,  -667,     0,     0,     0,     0,  -667,     0,     0,
       0,     0,     0,     0,     0,     0,  -667,     0,     0,     0,
       0,     0,     0, -1508,     0,     0,     0,     0,     0,  -667,
       0,     0,     0,     0,  -667,     0,  -667,     0,     0, -1508,
       0,     0,     0,  1014,  -667,     0,   867,     0,     0,  1487,
    1488,  1489,     0,     0,  -667,     0,     0,     0,     0,     0,
       0,     0,     0,  -667,     0,     0,     0,     0,     0,     0,
       0,     0,  -667,     0,  -667,  -667,     0,     0,  -667,     0,
    -667,     0,     0,     0,     0,  -667,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1490,     0, -1508, -1508,     0,
       0,  -667,     0,     0,     0,     0,  -667,     0,     0,     0,
       0,  -667,     0,     0,     0,     0,     0,     0,     0,  1015,
       0,     0,  -667,     0,     0, -1508, -1508,     0,     0,     0,
       0,   587, -1508,     0,  -667,  1017, -1508,     0,     0,     0,
       0,     0,     0,     0,  -667,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0, -1508,     0,     0,     0,     0,
       0,     0,     0, -1508,     0,     0, -1508, -1508,     0,     0,
       0,     0,     0, -1508,     0,     0,     0, -1508,     0, -1508,
       0,     0, -1508,     0, -1508,     0,     0,     0,     0,     0,
       0,     0,     0,  1458,  1459,     0,     0, -1508, -1508,     0,
       0,     0,     0, -1508,     0,     0,     0,     0,     0,     0,
       0,     0,     0, -1508,     0, -1508,     0,     0,     0,     0,
   -1508,  1018,  1460,     0,     0,     0,     0,     0,  1461,     0,
       0,     0,   437,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0, -1508,     0,   629,   630,   631,   632,   633,
     634,  1491,     0,     0,     0,     0, -1508,     0,     0,  1463,
       0,     0,  1019,  1464,     0,     0,     0,     0,     0,  1020,
       0,     0,     0,   438,     0,  1021,     0,     0,  1022,     0,
     439,     0,   636, -1508,   637,   638,   639,   640,   641,   642,
       0,     0,     0,  1492,  1493,     0,     0,     0,     0,  1494,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1495,
       0,  1023,     0,     0,     0,     0,  1496,     0,     0, -1508,
       0,     0,     0,     0,     0,     0,   643,     0, -1508, -1508,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1497,
       0,     0,     0,     0,     0, -1508,     0,     0, -1508, -1508,
       0,     0,   440,     0, -1508,   703,     0,   704,     0,     0,
       0,     0,   705,     0,     0,     0,     0,     0,     0,     0,
     706,     0, -1508,     0,     0,     0,     0,     0,     0,  1024,
   -1508,     0,     0, -1508,     0,     0,     0,     0,     0, -1508,
   -1508, -1508,     0,     0,     0, -1508,     0, -1508,     0, -1508,
   -1508, -1508,     0,   707,   708,     0,     0,     0,     0,   644,
       0,   709,     0,     0,     0,   441,     0,     0,     0,     0,
       0,     0,     0,   710,  1025,  1026,     0,   711,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   712,
       0,     0,     0,     0,   442,     0,     0,     0,     0,     0,
    1027,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   647,     0,   713,     0,     0,     0,     0,  1028,     0,
     714,   715,     0,     0,     0,     0,  1029,     0,     0,   297,
       0,     0,     0,     0,     0,   443,  1498,  1499,     0,     0,
       0,  1500,     0,  1478,     0,  1501,  1480,  1481,     0,   649,
       0,   716,     0,     0,     0,     0,     0,     0,   651,     0,
       0,     0,     0,   717,     0,     0,     0,   718,     0,     0,
       0,   652,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   719,     0,     0,     0,     0,     0,     0,   720,     0,
       0,   721,   722,     0,     0,     0,     0,     0,     0,   723,
       0,     0,     0,     0,     0,     0,   724,     0,   725,     0,
       0,   726,     0,     0,  -799,     0,     0,  -799,     0,   703,
       0,   704,     0,     0,     0,     0,   705,   656,   657,   658,
       0,     0,     0,     0,   706,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   727,     0,
       0,     0,   728,     0,   729,     0,     0,   165,     0,     0,
       0,   730,     0,     0,     0,     0,     0,   707,   708,     0,
       0,     0,     0,     0,     0,   709,     0,   660,   661,   662,
       0,     0,     0,     0,   731,     0,     0,   710,     0,     0,
    -799,   711,     0,     0, -1520,     0,     0,     0,     0,   732,
       0,     0,     0,   712,     0,     0,  -799,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     733,     0,     0,     0,     0,     0,     0,   713,     0,   734,
       0,     0,     0,     0,   714,   715,     0,     0,     0,     0,
       0,     0,   735,     0,     0,     0,     0,   736,     0,   737,
       0,     0,     0,     0,     0,     0,     0,   738,     0,     0,
       0,     0,     0,     0,     0,   716,     0,   739,     0,     0,
       0,     0,     0,     0,     0,     0,   740,   717,     0,     0,
       0,   718,     0,     0,     0,   741,     0,   742,   743,     0,
       0,   744,  -799,   745,     0,   719,     0,     0,   746,     0,
       0,     0,   720,  -799,     0,   721,   722,     0,     0,     0,
       0,     0,     0,   723,   747,     0,     0,     0,     0,   748,
     724,     0,   725,     0,   749,   726,     0,     0,     0,     0,
       0,     0,     0,  -799,     0,   750,  1014,     0,     0,   867,
    -799,     0,     0,     0,  -799,     0,  -799,   751,     0,  -799,
       0,  -799,     0,     0,     0,     0,     0,   752,     0,     0,
    1205,     0,   727,     0,     0,     0,   728,     0,   729,     0,
       0,     0,     0,     0,     0,   730,     0,     0,     0,     0,
       0,     0,  -799,     0,     0,     0,  1014,  -799,     0,   867,
       0,     0,     0,     0,     0,     0, -1516,     0,   731,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1015,   732,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -799,     0,     0,     0,     0,  1017,     0,
       0,     0,     0, -1520,   733,     0,     0,     0,     0,     0,
       0,     0,     0,   734,     0,     0,     0,     0,     0,     0,
    -799,     0,     0,     0,     0,     0,   735,     0,     0,     0,
       0,   736,  1015,   737,     0,     0,  1014,     0,     0,   867,
       0,   738,     0,     0,     0,     0,     0,     0,  1017,     0,
    -799,   739,     0,     0,     0,     0,  -799,     0,     0,     0,
     740,     0,     0,     0,     0,  -799,  -799,     0,     0,   741,
       0,   742,   743,     0,     0,   744,     0,   745,     0,     0,
       0,     0,   746,     0,  1018,  -799,     0,     0,     0,     0,
       0,  -799,     0,     0,     0,   437,  -799,     0,   747,  1613,
       0,     0,     0,   748,     0,     0,     0,     0,   749,  -799,
       0,     0,  1015, -1520,     0,     0,     0,  -799,     0,   750,
    -799,     0,     0,     0,     0,  1019,  -799,     0,  1017,     0,
       0,   751,  1020, -1516,  1018,     0,   438,     0,  1021,     0,
       0,  1022,  1136,   439,     0,   437,     0,  1014,     0,     0,
     867,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1023,  1019,     0,     0,     0,     0,
       0,     0,  1020,     0,     0,     0,   438,     0,  1021,     0,
       0,  1022,     0,   439,     0,     0,     0,     0,     0,     0,
       0, -1516,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1018,   440,     0,     0,     0,     0,
       0,     0,     0,  1015,  1023,   437,     0,  1014,     0,     0,
     867,     0,     0,     0,     0,  1016,     0,     0,     0,  1017,
    1340,     0,  1024,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1019,     0,     0,     0,     0,
       0,     0,  1020,     0,     0,   440,   438,     0,  1021,     0,
       0,  1022,     0,   439,     0,     0,     0,  1014,   441,     0,
     867,     0,     0,     0,     0,     0,     0,  1025,  1026,     0,
       0,     0,  1024,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1015,  1023,     0,     0,   442,     0,     0,
       0,     0,     0,  1027,     0,  1095,     0,     0,     0,  1017,
       0,     0,     0,     0,     0,  1018,     0,     0,   441,     0,
       0,  1028,     0,     0,     0,     0,   437,  1025,  1026,  1029,
       0,     0,   297,     0,     0,   440,     0,     0,   443,     0,
       0,     0,     0,  1015,  1614,     0,     0,   442,  1615,     0,
       0,     0,     0,  1027,     0,     0,  1019,     0,     0,  1017,
       0,     0,  1024,  1020,     0,     0,     0,   438,     0,  1021,
       0,  1028,  1022,  1136,   439,     0,     0,     0,     0,  1029,
       0,     0,   297,     0,     0,     0,     0,     0,   443,     0,
       0,     0,     0,     0,     0,  1018,  1014,     0,   441,   867,
       0,     0,     0,     0,     0,  1023,   437,  1025,  1026,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   442,     0,     0,
       0,     0,     0,  1027,     0,     0,  1019,     0,     0,     0,
       0,     0,     0,  1020,     0,  1018,   440,   438,     0,  1021,
       0,  1028,  1022,     0,   439,     0,   437,     0,  1014,  1029,
       0,   867,   297,     0,     0,     0,     0,     0,   443,     0,
       0,     0,  1015,  1024,     0,     0,     0,     0,     0,     0,
    1014,     0,     0,   867,  1140,  1023,  1019,     0,  1017,     0,
       0,     0,  1014,  1020,     0,   867,     0,   438,     0,  1021,
       0,     0,  1022,     0,   439,     0,     0,     0,     0,   441,
       0,     0,     0,     0,     0,     0,     0,     0,  1025,  1026,
       0,     0,     0,     0,     0,     0,   440,     0,     0,     0,
       0,     0,     0,     0,  1015,  1023,     0,     0,   442,     0,
       0,     0,     0,     0,  1027,     0,     0,     0,     0,     0,
    1017,     0,     0,  1024,     0,     0,  1015,     0,     0,     0,
       0,     0,  1028,     0,     0,     0,     0,     0,  1015,     0,
    1029,     0,  1017,   297,  1018,     0,   440,     0,     0,   443,
       0,     0,     0,     0,  1017,   437,     0,     0,     0,   441,
       0,     0,     0,     0,     0,     0,     0,     0,  1025,  1026,
       0,     0,     0,  1024,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1019,     0,     0,   442,     0,
       0,     0,  1020,     0,  1027,     0,   438,     0,  1021,     0,
       0,  1022,     0,   439,     0,     0,  1018,     0,     0,   441,
       0,     0,  1028,     0,     0,     0,     0,   437,  1025,  1026,
    1029,     0,     0,   297,  1345,     0,     0,     0,  1018,   443,
       0,     0,     0,     0,  1023,     0,     0,     0,   442,   437,
    1018,     0,     0,     0,  1027,     0,     0,  1019,     0,     0,
       0,   437,     0,     0,  1020,     0,     0,     0,   438,     0,
    1021,     0,  1028,  1022,     0,   439,     0,     0,     0,  1019,
    1029,     0,     0,   297,     0,   440,  1020,     0,     0,   443,
     438,  1019,  1021,     0,     0,  1022,     0,   439,  1020,     0,
    1014,     0,   438,   867,  1021,     0,  1023,  1022,     0,   439,
       0,     0,  1024,     0,  1014,     0,     0,   867,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1023,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1023,     0,     0,     0,     0,     0,     0,   440,   441,     0,
       0,     0,     0,     0,     0,     0,     0,  1025,  1026,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   440,
       0,     0,     0,     0,  1024,     0,  1015,   442,     0,     0,
       0,   440,     0,  1027,     0,     0,     0,     0,     0,     0,
    1015,     0,  1017,     0,  1014,     0,  1024,   867,     0,     0,
       0,  1028,     0,     0,     0,     0,  1017,     0,  1024,  1029,
     441,     0,   297,     0,     0,     0,     0,     0,   443,  1025,
    1026,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   441,     0,     0,  1229,     0,     0,  1622,   442,
       0,  1025,  1026,     0,   441,  1027,     0,     0,     0,     0,
       0,     0,     0,  1025,  1026,     0,     0,     0,     0,     0,
       0,   442,     0,  1028,     0,     0,     0,  1027,     0,     0,
    1015,  1029,     0,   442,   297,     0,     0,     0,  1018,  1027,
     443,     0,     0,     0,     0,  1028,  1017,     0,     0,   437,
       0,     0,  1018,  1029,     0,     0,   297,  1028,     0,     0,
       0,     0,   443,   437,     0,  1029,     0,     0,   297,     0,
       0,     0,     0,     0,   443,     0,     0,     0,     0,  1019,
       0,     0,     0,     0,     0,     0,  1020,     0,     0,     0,
     438,     0,  1021,  1019,     0,  1022,     0,   439,     0,     0,
    1020,     0,     0,     0,   438,     0,  1021,     0,     0,  1022,
       0,   439,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1023,     0,
       0,     0,  1018,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1023,   437,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   440,
       0,     0,     0,  1019,     0,     0,     0,     0,     0,     0,
    1020,     0,     0,   440,  1059,     0,  1021,     0,     0,  1022,
       0,   439,     0,     0,     0,     0,  1024,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1024,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1023,     0,     0,     0,     0,  1760,     0,     0,
       0,     0,   441,     0,     0,     0,     0,     0,     0,     0,
       0,  1025,  1026,     0,     0,     0,   441,     0,     0,     0,
       0,     0,     0,     0,     0,  1025,  1026,     0,     0,     0,
       0,   442,     0,   440,     0,     0,     0,  1027,     0,     0,
       0,     0,     0,     0,     0,   442,     0,     0,     0,     0,
       0,  1027,     0,     0,     0,  1028,     0,     0,     0,     0,
    1024,     0,     0,  1029,     0,     0,   297,     0,     0,  1028,
       0,     0,   443,     0,     0,     0,     0,  1029,     0,     0,
     297,     0,     0,     0,     0,     0,   443,     0,     0,     0,
       0,     0,     0,     0,  1015,     0,   441,     0,     0,     0,
       0,     0,     0,     0,     0,  1025,  1026,     0,     0,     0,
    1017,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   442,     0,  1653,     0,  1654,
       0,  1027,  1655,   629,   630,   631,   632,   633,   634,   635,
    1656,  1657,  1658,     0,     0,     0,     0,     0,     0,  1028,
     629,   630,   631,   632,   633,   634,   635,  1029,     0,     0,
     297,     0,  1659,     0,     0,     0,   443,     0,     0,     0,
     636,     0,   637,   638,   639,   640,   641,   642,     0,  2077,
    2078,     0,     0,     0,     0,     0,     0,   636,     0,   637,
     638,   639,   640,   641,   642,     0,  1018,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   437,     0,     0,
       0,     0,     0,     0,   643,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   643,     0,     0,     0,     0,     0,  1178,     0,     0,
       0,     0,     0,     0,  1020,     0,     0,     0,   438,     0,
    1021,     0,     0,  1022,  1660,   439,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1661,     0,     0,     0,  1662,  1663,     0,  1015,
       0,     0,     0,     0,     0,     0,  1023,     0,     0,     0,
    1664,     0,     0,     0,     0,  1017,     0,   644,     0,     0,
       0,     0,     0,     0,     0,  2079,     0,     0,     0,     0,
       0,     0,     0,   645,   644,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   440,     0,  1665,
     645,     0,     0,     0,     0,     0,     0,     0,  1666,     0,
       0,     0,     0,     0,     0,     0,  2080,  2081,     0,   647,
       0,     0,     0,     0,  1024,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   647,     0,     0,     0,
       0,  2082,  1667,     0,     0,     0,     0,     0,     0,     0,
       0,  1018,     0,     0,     0,     0,  1668,   649,     0,   648,
     441,     0,   437,     0,   650,     0,   651,     0,     0,  1025,
    1026,     0,     0,     0,   649,  1015,     0,     0,     0,   652,
    1669,   650,     0,   651,     0,     0,  2083,     0,     0,   442,
       0,  1017,  1178,     0,     0,  1027,   652,     0,     0,  1020,
       0,     0,     0,   438,  1670,  1021,     0,     0,  1022,  1671,
     439,     0,     0,  1028,     0,     0,     0,     0,     0,     0,
       0,  1029,  1015,  1672,   297,     0,     0,     0,     0,     0,
     443,  1179,  1180,   655,     0,   656,   657,   658,  1017,  1705,
    1181,  1023,     0,     0,     0,     0,     0,     0,     0,     0,
     655,     0,   656,   657,   658,     0,     0,     0,     0,  2084,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1673,
       0,     0,     0,  2085,     0,     0,     0,  1018,     0,     0,
       0,  1674,   440,     0,     0,   660,   661,   662,   437,     0,
       0,     0,     0,     0,     0,     0,     0,  2086,   663,     0,
    1675,   664,   660,   661,   662,     0,     0,     0,     0,  1024,
       0,     0,     0,     0,     0,   663,     0,     0,   664,  2087,
       0,  1676,     0,     0,  1018,     0,     0,     0,     0,   438,
       0,  1021,     0,     0,  1022,   437,   439,     0,  2088,     0,
       0,     0,     0,     0,     0,   441,     0,     0,     0,     0,
       0,     0,     0,     0,  1025,  1026,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1178,     0,  1023,     0,     0,
       0,     0,  1020,     0,   442,     0,   438,     0,  1021,     0,
    1027,  1022,     0,   439,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1028,     0,
       0,     0,     0,     0,     0,     0,  1029,     0,   440,   297,
       0,     0,     0,     0,  1023,   443,  1179,  1180,     0,     0,
       0,     0,     0,     0,  1941,  1181,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1024,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   440,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   441,     0,     0,     0,     0,     0,     0,     0,     0,
    1025,  1026,  1024,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     442,     0,     0,     0,     0,     0,  1027,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   441,     0,
       0,     0,     0,     0,  1028,     0,     0,  1025,  1026,     0,
       0,     0,  1029,     0,     0,   297,     0,     0,     0,     0,
       0,   443,     0,     0,     0,     0,     0,   442,     0,     0,
       0,     0,     0,  1027,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1028,     0,     0,     0,     0,     0,     0,     0,  1029,
       0,     0,   297,     0,     0,     0,     0,     0,   443,  1179,
    1180,     0,     0,     0,     0,     0,     0,     0,  1181
};

static const yytype_int16 yycheck[] =
{
      84,   176,   412,   132,   231,   571,   230,   234,   721,  1058,
     460,  1306,   934,   685,   898,   687,   323,   535,   536,  1130,
     893,   196,   197,  1236,   653,  1236,   201,   202,   203,   204,
     205,   904,   207,   228,   209,   230,   231,   895,  1236,   234,
     750,   868,   869,  1078,  1236,  1236,  1269,  1136,  1051,  1418,
    1419,  1086,  1260,  1261,  1262,  1120,   283,   487,  1150,  1029,
     287,   369,   289,   625,   193,   692,   912,  1746,  1376,    13,
     894,   298,  1376,   248,   301,   250,   160,   892,  1376,   925,
     258,    17,   257,  1376,  1376,   603,   901,   902,   283,  1376,
     265,     6,   287,     6,   289,  1206,     6,  1132,    21,    49,
      22,   916,   917,   298,   279,   280,   301,   282,     6,     9,
       9,    17,  1229,   288,    70,   930,   931,  1520,    48,    23,
      54,     6,     9,    96,    56,    56,  1310,     9,    72,    70,
      63,   182,   121,   360,  1895,  1538,   444,    96,    28,    22,
    1205,   107,    56,   370,    88,   170,   123,    73,    49,  1266,
     377,     9,   327,   121,    70,   330,   331,   214,   333,    70,
      30,    40,    70,  1166,     9,   360,   390,   171,   392,   214,
     348,   168,   171,   218,   349,   370,   207,   355,    48,  1114,
    1297,    70,   377,  1586,    49,    86,    49,  1014,   415,    23,
     862,   366,  1019,   388,    49,   390,   236,   392,    56,   118,
    1292,  1880,   874,   227,   228,   183,     9,   114,   168,   625,
     518,   121,   139,     9,   154,  1883,   248,  1032,   413,  1284,
     415,    61,   306,  1626,   236,   115,  1200,   175,  1345,    86,
     236,   409,   122,    85,   118,   462,   411,   464,   416,   463,
     240,   820,   914,   325,   419,   200,  1061,  1169,    88,    89,
    1077,   429,   150,   368,    50,   126,    11,   118,   171,  1115,
      25,  1350,   236,   693,    37,  2325,   122,   462,   463,   464,
     223,   986,    49,   213,   836,   453,  2057,    66,  2059,   372,
    1095,  1346,  1128,  2343,   479,  1377,   236,  1604,   466,   248,
    1659,     0,   180,  1328,   188,  1151,  1665,   455,   473,   236,
    1402,   139,  1619,   418,   174,    63,  1398,  1409,   195,   393,
     214,  1314,   396,   195,  1416,   173,    71,   236,   493,   494,
     214,  1529,  1137,   260,   264,   418,   266,  1142,  1551,   236,
     285,  1003,  1449,   311,   561,  1409,   236,   349,   312,   316,
     113,   519,  1416,  1408,  2012,  1229,   305,   347,   523,   236,
     248,  1178,   236,   435,   236,   210,   243,   354,   533,   537,
    1763,   243,   214,   128,   455,   223,   561,    92,   251,   998,
     999,   403,   260,    70,   214,   236,  1249,   256,  1313,  1006,
     214,   329,  1266,   122,   311,   560,   149,   364,   583,   584,
     280,   236,   263,   568,   354,   573,   322,   442,   455,   195,
     578,  1274,   442,   434,   455,  1120,  1841,   321,   405,   975,
     539,     0,  2173,  1297,  1229,  1450,  1527,   442,  2199,   360,
     836,  1236,  1511,  1397,   325,  1004,  1005,   602,   315,   225,
     363,   455,   607,   315,   609,   424,   442,   612,   442,   614,
     236,   616,   617,   442,   360,   218,   621,   243,  1294,   360,
    1265,  1266,   360,   293,  1278,  1639,   424,   260,   411,   654,
     325,  1345,   325,  1555,  1179,  1180,  1181,   350,   325,   442,
     648,   360,   403,   311,  1189,   441,   442,   433,   341,   409,
     406,   404,  1297,   442,  1308,   408,    66,   245,   663,   664,
    1205,   378,   442,   403,   400,  1210,   378,  1212,   448,  1214,
     434,  1216,   438,  1218,  1219,  1220,  1221,  1222,  1223,  1224,
    1225,   443,   301,  1578,   424,   318,   457,  1332,   403,   315,
     407,  1336,  1337,   442,  1339,   407,   833,   442,   441,   442,
    1345,  1355,   442,   455,   435,   442,   236,  1940,   442,   409,
    1589,   457,   442,   442,   442,  1610,   457,   310,   325,   457,
    1585,   441,   310,   411,   498,   895,   236,   442,    70,   867,
     442,   448,    32,   692,   341,  1449,   448,   269,   457,  1284,
     435,   441,   435,  2008,   914,  1870,  2011,  1007,   435,   919,
    1209,   442,   378,   187,   436,   441,   442,  1216,  1991,   816,
    1993,   364,   455,   820,   183,  1818,   823,   824,  1906,  1688,
     358,    70,  1906,   830,   187,   363,   331,    31,  1906,    30,
    1172,   407,  1714,  1906,  1906,   455,   251,   236,  2021,  1906,
     236,   816,  1201,   163,  2303,   820,    28,   322,   823,   824,
     187,  1346,    30,   156,   224,   830,   811,   376,   167,   279,
    1714,   150,   117,   258,   187,   223,   986,  1276,   198,  2052,
    2053,   456,   448,   233,     8,  1552,   180,   832,   435,   188,
     402,  1558,   300,   360,  1379,   166,   200,   423,    66,   394,
     120,  1386,  1387,  1388,  1389,  1390,  1391,  1392,   455,   442,
     436,    35,  1395,  1772,   442,  1509,   110,   240,   156,   304,
     240,  1318,  1000,  1408,   164,  1322,   422,   187,  1815,   894,
    1817,   187,   441,   442,   245,   126,   207,   260,  2077,   887,
     260,   406,   236,   115,   215,   350,   458,   456,   245,   524,
     915,   301,   311,    27,   919,  2160,   921,   954,   923,   924,
    1765,   926,   187,  1850,  1737,  1738,  1739,   341,  1584,   441,
     380,   247,   442,   277,   971,  1458,   941,  1911,   448,   289,
    1379,   195,   449,   450,   451,   452,   346,   454,   341,   954,
     457,   284,   442,   455,  1104,  1882,  1831,  1931,  1932,   310,
    1978,  1979,  1980,  1981,   244,  1745,   971,  1004,  1005,    28,
    1750,  1751,   180,   310,  1754,  1755,  1756,   288,  1758,  1759,
     919,   348,   236,   299,   989,  1424,   102,   972,   288,   243,
     245,  1893,  1617,   441,  1662,   348,   984,   240,  1518,  1004,
    1005,     9,   236,  1848,    11,   899,   284,   358,  1982,   279,
     455,  1985,  1887,   442,    90,    91,   442,   260,    25,    26,
     305,   358,  2045,   411,  2045,   233,   920,   563,   922,  1179,
    1180,  1181,   368,   927,  1933,  1934,  1559,  2045,   360,  1189,
     116,   107,   936,  2045,  2045,  1568,  2259,  2260,    56,   251,
      57,    82,   348,  1578,  1579,   310,   115,   236,   986,   213,
    1210,   315,  1212,   319,  1214,   321,  1216,    98,  1218,  1219,
    1220,  1221,  1222,  1223,  1224,  1225,   269,   437,   441,  1786,
    1787,   360,   418,   348,   986,  1610,   901,  1986,  1987,    96,
      97,     9,    99,   301,    12,   123,  2070,    15,    16,   198,
     199,   108,   372,   358,   455,  1812,   455,   368,   300,   175,
     240,  1116,   266,   376,  1821,   245,   931,   319,   455,   321,
     240,  1815,   188,  1817,   378,  2230,    60,   449,   450,   451,
     452,   442,   454,   449,   450,   457,  1819,    83,    72,   167,
     260,   240,   368,   202,   151,   152,   120,  1086,   418,  2070,
    2124,   202,  1157,   184,   236,   162,  1850,   418,  1052,    93,
     240,   260,     1,   166,  1201,  1104,   248,   101,   195,   247,
     449,   450,   451,   452,  1613,   454,  1161,   120,   457,   442,
     260,   311,   233,  1171,   368,  1868,    12,   195,  1882,    15,
      16,   236,   418,   456,   448,   211,  1201,   240,   441,   442,
     455,  1020,  2061,  1934,   207,   236,   356,   238,    47,   236,
     241,   293,   215,   258,   455,   223,   243,   260,   294,   295,
     236,   299,  1747,    62,  2329,   169,  1045,  1752,   236,  1379,
     237,     8,  1857,   426,   418,   243,  1386,  1387,  1388,  1389,
    1390,  1391,  1392,   274,   178,   319,   455,  1954,   441,   441,
     442,  1179,  1180,  1181,   299,  1986,  1987,  1374,    35,   335,
     336,  1189,   923,   102,   208,   326,  1973,   195,   319,   399,
     331,  2245,   216,  1278,   307,   326,  2250,  1179,  1180,  1181,
     941,   324,  1210,  1990,  1212,   288,  1214,  1189,   315,   126,
    1218,  1219,  1220,  1221,  1222,  1223,  1224,  1225,   404,   167,
     374,   375,   408,  1308,  2163,  1244,  1831,   315,   236,   455,
    1212,   342,  2044,   364,  1839,   243,  1218,  1219,  1220,  1221,
     188,  1581,  1224,  1225,  2031,  2032,   198,   240,   167,   296,
     297,  1368,  1369,  2040,   206,   253,   254,   159,   437,   526,
    1965,   163,   441,   310,   531,   352,   455,   260,  1830,   188,
    1355,   378,   356,   225,   272,   273,   387,   388,  1363,   455,
     442,  1255,  1887,  1368,  1369,  1693,   448,   156,   157,   441,
     378,   449,   450,   416,   311,   214,   213,   195,  1317,   278,
     219,   280,   413,   455,     9,   392,   404,   315,   135,   356,
     408,     2,   231,   166,   275,     6,   185,   170,   441,   407,
     431,  1883,   191,   411,  1436,   277,   278,  1439,   439,  2268,
     310,   442,  1444,   285,   286,   227,   228,  1356,   236,   291,
     292,   448,  2129,   227,   228,   243,   263,   253,   254,   266,
    2137,    56,   455,   222,   442,   442,  1959,   226,  1961,   356,
     448,   427,   428,   429,   430,  2152,   272,   273,  2085,     1,
     378,   438,     4,   440,   444,  2149,   337,  2151,  1386,  1387,
    1388,  1389,  1390,  1391,  1392,   233,   234,    19,   124,   449,
     450,   451,   452,  2180,   454,  2182,   319,    29,   321,   407,
     319,   320,  2189,   169,  1386,  1387,  1388,  1389,  1390,  1391,
    1392,   451,   452,   332,   454,   334,   377,   315,   379,   153,
     455,   155,  2209,  2210,  1509,  1210,   891,   356,   380,  1214,
     895,    63,  1662,   265,   442,   267,   901,  1222,  1223,  1847,
     448,   906,   907,   427,   428,   429,   430,   912,   913,   914,
    2012,   153,   239,   155,   919,   427,   428,   429,   430,   195,
     925,   319,  2274,   321,   442,  2170,   270,   271,   173,   934,
     935,   341,   937,   449,   450,   451,   452,   359,   454,   216,
     378,   449,   450,   451,   452,   461,   454,    11,   270,   271,
     195,   233,   234,   461,   405,   455,  2283,   455,   455,   455,
     236,    25,    26,   449,   450,   451,   452,   243,   454,   407,
     455,   457,  1791,  1792,  1793,  1794,   435,  1747,   223,   255,
     455,   986,  1752,   455,  1641,   356,   235,   442,  2131,   455,
    2133,   236,   182,    57,     9,   455,   455,   283,   243,   449,
     450,   451,   452,   455,   454,   280,   277,   457,   280,   403,
     448,  1016,   403,  1618,   395,    24,  1641,  2262,  2120,   455,
    2265,   356,   332,   372,   455,   214,   107,   442,  1685,  1588,
     202,   384,    96,    97,   367,    99,    56,   442,   236,   315,
      85,   175,  1647,  1651,   108,   356,  1051,   456,   455,  1654,
     459,   460,  1709,   351,   372,   283,  1661,   109,   236,  1667,
    1685,   233,   363,   211,   249,  1624,   455,    82,   240,  2314,
     315,    68,  1631,  1078,   280,   280,   410,   455,   356,   249,
      23,  1086,  1087,    98,  1709,   277,   442,   151,   152,   261,
     455,   236,  1749,   280,   301,   455,    84,    84,   162,  1104,
     442,  2346,   378,   442,   436,   381,   382,   400,   600,    25,
      26,   384,   435,  1718,   286,  1120,  1721,   317,   403,   234,
     292,   200,   319,  1128,  1749,   442,   364,  1132,   218,   449,
     450,   451,   452,   378,   454,  1140,   403,   457,  1143,   441,
     449,   450,   451,   452,    55,   454,    27,   319,   457,   384,
     188,    67,   372,    69,   326,   449,   450,   451,   452,   455,
     454,  1166,   407,   457,  1169,   356,   411,   339,   455,   184,
     364,   227,   448,   237,  1179,  1180,  1181,   442,   225,   438,
     195,   346,   214,   109,  1189,   236,   405,   103,   104,   105,
    1795,   363,   364,   306,   366,    37,  1801,   442,   381,  1747,
    1205,   287,   374,   448,  1752,  1210,   281,  1212,   448,  1214,
     403,   458,   384,  1218,  1219,  1220,  1221,  1222,  1223,  1224,
    1225,   236,    27,   238,   400,  1747,   241,   362,   243,   462,
    1752,  2227,   400,   405,   150,   174,   152,   455,  1843,   455,
     442,  2081,   405,   236,   160,   449,   450,   451,   452,   136,
     454,   107,    17,   457,   172,   441,    31,   188,    33,   274,
     402,    36,   458,   236,    30,   127,    56,   128,    12,    13,
      14,    46,   205,   403,    33,   434,    20,    36,   458,  1284,
     130,   458,   348,   455,   458,    44,    45,    46,   352,  1294,
     319,   458,   458,  1852,  1902,   132,   458,   458,   458,  1858,
     315,   458,  1307,  1908,   458,   458,   133,   100,  1913,  1314,
     399,   403,   137,    49,    58,   402,  1321,  1922,   234,   138,
     400,  1926,   180,  1328,   402,   397,   143,   342,   392,   436,
      49,   248,   248,   146,   180,  1340,   112,   333,  1852,   380,
     442,  1346,   114,   365,   114,   441,   403,  1352,   442,   187,
     341,   309,   236,   163,   134,   438,   171,   403,   366,   210,
     403,  2018,    49,   378,   218,   210,  1371,   122,   180,   193,
     280,   447,   387,   388,   218,   446,   270,   454,   442,   341,
     233,  1386,  1387,  1388,  1389,  1390,  1391,  1392,   457,   457,
     457,   455,   407,  2018,   457,   398,   403,   373,   413,   158,
     131,   176,   266,  1408,   269,   265,   181,   331,   187,   403,
     400,    49,   156,   157,   138,  2020,   431,   176,     8,   194,
     180,   438,   126,  1428,   439,   438,   403,   442,     9,   307,
     173,   308,   404,   448,   202,   194,   268,   329,   344,   125,
     435,   185,   110,   435,    49,  1450,   175,   191,   141,   285,
     142,   240,   263,   262,   144,   289,   284,   300,   113,   394,
       7,    67,   116,   220,   442,  2119,   129,   242,  2073,   328,
     214,   156,   156,   328,   136,   102,    49,   240,   222,  2084,
     218,  2086,   226,   242,   145,   401,   267,    95,   148,    91,
     264,   221,   203,   192,  2119,   390,   438,  2105,    49,   406,
     307,   240,   147,   344,   174,   240,   180,  1512,  1513,   293,
     307,   423,   256,   257,   140,   290,    49,     6,   262,   354,
      22,   193,    54,   132,   188,   178,   442,  1329,   272,   211,
     514,   290,   597,  1152,  1360,   279,   444,   136,  1369,   314,
     284,  1153,   960,  1898,  1851,   109,   227,   113,   610,    49,
     239,   584,  1906,   393,   318,   886,   160,   861,   302,  1694,
    1583,  1692,  1690,   338,  2117,   565,   874,  2172,   343,  2100,
     974,  2238,   836,  1578,  1579,  2232,   124,  1774,   353,  1584,
    1585,   496,   357,  1855,   343,  1061,  1421,  1420,  1733,  1066,
    1772,  1808,  1274,  1271,   353,  2252,  1551,  1602,  1818,  1287,
    2002,  1281,  1839,  1856,  1576,  1610,  1600,  2232,  1356,  2217,
    1104,  1322,  1872,  2218,  2219,  1126,  1137,  2222,  1128,   926,
    1625,  1711,  1631,  2055,  2229,  1630,  1631,  2252,  1631,  2237,
    2238,  2173,  2060,  1863,  1525,  2066,  1116,  1238,  1613,   987,
     415,  1641,  1234,   246,   866,   619,  2271,  1292,  1069,   329,
     425,   994,  2254,    57,   827,  1464,   415,  1662,  1914,    -1,
    1001,  2266,    -1,    -1,    -1,    -1,    -1,    -1,  1673,    -1,
    1675,    -1,    -1,     1,    -1,    -1,    -1,    -1,     6,    -1,
      -1,     9,    -1,    -1,    12,    13,    14,  2295,  2296,    -1,
      -1,  2299,  2297,  2301,  2208,    -1,    -1,    -1,    -1,    -1,
    2325,    -1,    -1,    -1,   448,   449,   450,   451,   452,    -1,
     454,    -1,   456,   457,    -1,   459,   460,    -1,  2343,    -1,
      -1,    -1,  2327,    -1,    -1,    -1,    -1,    -1,    -1,  2337,
      58,    -1,  1737,  1738,  1739,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1747,    -1,    -1,    -1,    -1,  1752,    -1,    -1,
      -1,    -1,    -1,  2267,    82,    -1,    -1,    -1,    -1,    -1,
    1765,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    -1,    -1,    -1,     6,    -1,    -1,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    -1,  2326,    -1,    -1,    -1,    -1,    -1,    -1,  1824,
      -1,    -1,    -1,    -1,    -1,  1830,  1831,    -1,   156,   157,
      -1,    -1,    -1,    -1,  1839,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1848,    -1,    -1,    -1,    -1,    -1,    -1,
      82,  1856,    -1,    -1,    -1,    -1,   184,   185,    -1,    -1,
      -1,    -1,    -1,   191,    -1,    -1,    98,   195,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1883,    -1,
      -1,    -1,  1887,    -1,    -1,    -1,   214,    -1,    -1,   177,
      -1,    -1,    -1,    -1,   222,    -1,   184,   225,   226,    -1,
      -1,    -1,  1907,    -1,   232,    -1,  1911,    -1,   236,    -1,
     238,    -1,    -1,   241,    -1,   243,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   156,    -1,  1931,  1932,   256,   257,
      -1,    -1,    -1,    -1,   262,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   272,    -1,   274,    -1,   236,    -1,
     238,   279,   184,   241,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   195,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   302,    -1,    -1,  1982,    -1,    -1,
    1985,    -1,    82,    -1,    -1,    -1,   274,   315,    -1,    -1,
      -1,    -1,    -1,   225,     0,     1,    -1,    -1,    98,    -1,
     232,    -1,    -1,    -1,   236,    -1,   238,  2012,    -1,   241,
      -1,   243,    -1,    -1,   342,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,
      -1,    37,    38,    39,    40,    41,    42,    43,    -1,  2044,
      -1,    -1,   274,    -1,    -1,    -1,  2051,    -1,    -1,    -1,
     378,    -1,    -1,    -1,   342,    -1,    -1,    -1,    -1,   387,
     388,    -1,    -1,    -1,    -1,  2070,    -1,    -1,    74,    -1,
      76,    77,    78,    79,    80,    81,    -1,   177,    -1,   407,
      -1,    -1,  2087,   315,   184,   413,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   387,
     388,    -1,    -1,   431,    -1,    -1,    -1,    -1,    -1,   397,
     342,   439,   118,    -1,   442,    -1,    -1,    -1,    -1,  2124,
     448,   449,   450,    -1,    -1,   413,   454,    -1,   456,   135,
     458,   459,   460,   139,    -1,   423,   236,    -1,   238,    -1,
      -1,   241,    -1,   431,    -1,    -1,   378,    -1,   436,    -1,
      -1,   439,    -1,   441,   442,   387,   388,    -1,    -1,    -1,
      -1,   167,   168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   274,   407,    -1,   183,  2183,    -1,
      -1,   413,   188,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  2198,    -1,   201,  2201,    -1,    -1,   431,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   439,   214,    -1,
     442,   217,    -1,    -1,    -1,    -1,   448,   223,    -1,    -1,
      -1,   227,   228,    -1,   456,    -1,  2231,    -1,    -1,   235,
     236,    -1,    -1,   239,    -1,    -1,    -1,    -1,    -1,    -1,
    2245,    -1,   342,    -1,    -1,  2250,    -1,   253,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     0,     1,    -1,
       3,    -1,     5,    -1,    -1,    -1,    -1,    10,    -1,  2274,
     276,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,
    2285,    -1,    -1,    -1,    -1,   291,    -1,   387,   388,    -1,
      -1,    -1,   298,    -1,   300,    -1,    -1,   397,    -1,    -1,
      -1,   307,    -1,    -1,    -1,   311,    -1,   313,    51,    52,
      -1,    -1,    -1,   413,    -1,    -1,    59,   323,    -1,    -1,
      -1,    -1,    -1,   423,   330,  2330,   332,    -1,    71,    -1,
      -1,   431,    75,    -1,    -1,    -1,   436,    -1,    -1,   439,
      -1,   441,   442,    -1,    87,   351,    -1,    -1,   354,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   367,    -1,   369,   370,   371,    -1,    -1,   111,    -1,
      -1,    -1,    -1,    -1,    -1,   118,   119,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   393,    -1,    -1,
      -1,    -1,   135,    -1,    -1,    -1,   139,    -1,    -1,    -1,
       1,    -1,     3,    -1,     5,   411,   149,    -1,    -1,    10,
      -1,    -1,    -1,   419,   420,   421,    -1,    18,   161,    -1,
      -1,    -1,   165,    -1,    -1,    -1,   432,    -1,    -1,   435,
      -1,    -1,    -1,    -1,    -1,    -1,   179,    -1,   444,    -1,
     183,    -1,    -1,   186,    -1,    -1,   189,   190,    -1,   455,
      51,    52,    -1,    -1,   197,    -1,    -1,    -1,    59,    -1,
      -1,   204,    -1,   206,    -1,    -1,   209,    -1,    -1,    -1,
      71,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   246,    -1,    -1,    -1,   250,    -1,   252,
     111,    -1,    -1,    -1,    -1,    -1,   259,   118,   119,    -1,
      -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   282,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,    -1,
      -1,    -1,    -1,    -1,   297,    -1,    -1,    -1,    -1,    -1,
     161,    -1,    -1,    -1,   165,    -1,    -1,    -1,   311,    -1,
      -1,    -1,    -1,    -1,    -1,   318,    -1,    -1,   179,    -1,
      -1,    -1,    -1,    -1,   327,   186,    -1,    -1,   189,   190,
      -1,    -1,    -1,    -1,    -1,    -1,   197,   340,    -1,    -1,
      -1,    -1,   345,   204,   347,   206,    -1,    -1,   209,    -1,
      -1,    -1,   355,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   365,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   374,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     383,    -1,   385,   386,    -1,   246,   389,    -1,   391,   250,
      -1,   252,    -1,   396,    -1,    -1,    -1,     6,   259,    -1,
       9,    -1,    -1,    12,    13,    14,    -1,    -1,    17,   412,
      -1,    -1,    21,    -1,   417,    -1,    -1,    -1,    -1,   422,
      -1,   282,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     433,    -1,    -1,    -1,    -1,    -1,   297,    -1,    -1,   442,
      -1,    -1,   445,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      -1,    -1,   455,    -1,    -1,    -1,    -1,   318,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   327,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,   340,
      -1,    -1,    -1,    -1,   345,    -1,   347,    -1,    -1,    98,
      -1,    -1,    -1,     6,   355,    -1,     9,    -1,    -1,    12,
      13,    14,    -1,    -1,   365,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   374,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   383,    -1,   385,   386,    -1,    -1,   389,    -1,
     391,    -1,    -1,    -1,    -1,   396,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    58,    -1,   156,   157,    -1,
      -1,   412,    -1,    -1,    -1,    -1,   417,    -1,    -1,    -1,
      -1,   422,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,   433,    -1,    -1,   184,   185,    -1,    -1,    -1,
      -1,   442,   191,    -1,   445,    98,   195,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   455,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   214,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   222,    -1,    -1,   225,   226,    -1,    -1,
      -1,    -1,    -1,   232,    -1,    -1,    -1,   236,    -1,   238,
      -1,    -1,   241,    -1,   243,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   156,   157,    -1,    -1,   256,   257,    -1,
      -1,    -1,    -1,   262,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   272,    -1,   274,    -1,    -1,    -1,    -1,
     279,   184,   185,    -1,    -1,    -1,    -1,    -1,   191,    -1,
      -1,    -1,   195,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   302,    -1,    37,    38,    39,    40,    41,
      42,   214,    -1,    -1,    -1,    -1,   315,    -1,    -1,   222,
      -1,    -1,   225,   226,    -1,    -1,    -1,    -1,    -1,   232,
      -1,    -1,    -1,   236,    -1,   238,    -1,    -1,   241,    -1,
     243,    -1,    74,   342,    76,    77,    78,    79,    80,    81,
      -1,    -1,    -1,   256,   257,    -1,    -1,    -1,    -1,   262,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   272,
      -1,   274,    -1,    -1,    -1,    -1,   279,    -1,    -1,   378,
      -1,    -1,    -1,    -1,    -1,    -1,   118,    -1,   387,   388,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   302,
      -1,    -1,    -1,    -1,    -1,   404,    -1,    -1,   407,   408,
      -1,    -1,   315,    -1,   413,     3,    -1,     5,    -1,    -1,
      -1,    -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      18,    -1,   431,    -1,    -1,    -1,    -1,    -1,    -1,   342,
     439,    -1,    -1,   442,    -1,    -1,    -1,    -1,    -1,   448,
     449,   450,    -1,    -1,    -1,   454,    -1,   456,    -1,   458,
     459,   460,    -1,    51,    52,    -1,    -1,    -1,    -1,   201,
      -1,    59,    -1,    -1,    -1,   378,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,   387,   388,    -1,    75,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,
      -1,    -1,    -1,    -1,   407,    -1,    -1,    -1,    -1,    -1,
     413,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   253,    -1,   111,    -1,    -1,    -1,    -1,   431,    -1,
     118,   119,    -1,    -1,    -1,    -1,   439,    -1,    -1,   442,
      -1,    -1,    -1,    -1,    -1,   448,   449,   450,    -1,    -1,
      -1,   454,    -1,   456,    -1,   458,   459,   460,    -1,   291,
      -1,   149,    -1,    -1,    -1,    -1,    -1,    -1,   300,    -1,
      -1,    -1,    -1,   161,    -1,    -1,    -1,   165,    -1,    -1,
      -1,   313,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   179,    -1,    -1,    -1,    -1,    -1,    -1,   186,    -1,
      -1,   189,   190,    -1,    -1,    -1,    -1,    -1,    -1,   197,
      -1,    -1,    -1,    -1,    -1,    -1,   204,    -1,   206,    -1,
      -1,   209,    -1,    -1,     6,    -1,    -1,     9,    -1,     3,
      -1,     5,    -1,    -1,    -1,    -1,    10,   369,   370,   371,
      -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   246,    -1,
      -1,    -1,   250,    -1,   252,    -1,    -1,    49,    -1,    -1,
      -1,   259,    -1,    -1,    -1,    -1,    -1,    51,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    -1,   419,   420,   421,
      -1,    -1,    -1,    -1,   282,    -1,    -1,    71,    -1,    -1,
      82,    75,    -1,    -1,    86,    -1,    -1,    -1,    -1,   297,
      -1,    -1,    -1,    87,    -1,    -1,    98,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     318,    -1,    -1,    -1,    -1,    -1,    -1,   111,    -1,   327,
      -1,    -1,    -1,    -1,   118,   119,    -1,    -1,    -1,    -1,
      -1,    -1,   340,    -1,    -1,    -1,    -1,   345,    -1,   347,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   355,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   149,    -1,   365,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   374,   161,    -1,    -1,
      -1,   165,    -1,    -1,    -1,   383,    -1,   385,   386,    -1,
      -1,   389,   184,   391,    -1,   179,    -1,    -1,   396,    -1,
      -1,    -1,   186,   195,    -1,   189,   190,    -1,    -1,    -1,
      -1,    -1,    -1,   197,   412,    -1,    -1,    -1,    -1,   417,
     204,    -1,   206,    -1,   422,   209,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   225,    -1,   433,     6,    -1,    -1,     9,
     232,    -1,    -1,    -1,   236,    -1,   238,   445,    -1,   241,
      -1,   243,    -1,    -1,    -1,    -1,    -1,   455,    -1,    -1,
      30,    -1,   246,    -1,    -1,    -1,   250,    -1,   252,    -1,
      -1,    -1,    -1,    -1,    -1,   259,    -1,    -1,    -1,    -1,
      -1,    -1,   274,    -1,    -1,    -1,     6,   279,    -1,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,   282,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,   297,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   315,    -1,    -1,    -1,    -1,    98,    -1,
      -1,    -1,    -1,   325,   318,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,
     342,    -1,    -1,    -1,    -1,    -1,   340,    -1,    -1,    -1,
      -1,   345,    82,   347,    -1,    -1,     6,    -1,    -1,     9,
      -1,   355,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,
     372,   365,    -1,    -1,    -1,    -1,   378,    -1,    -1,    -1,
     374,    -1,    -1,    -1,    -1,   387,   388,    -1,    -1,   383,
      -1,   385,   386,    -1,    -1,   389,    -1,   391,    -1,    -1,
      -1,    -1,   396,    -1,   184,   407,    -1,    -1,    -1,    -1,
      -1,   413,    -1,    -1,    -1,   195,   418,    -1,   412,   149,
      -1,    -1,    -1,   417,    -1,    -1,    -1,    -1,   422,   431,
      -1,    -1,    82,   435,    -1,    -1,    -1,   439,    -1,   433,
     442,    -1,    -1,    -1,    -1,   225,   448,    -1,    98,    -1,
      -1,   445,   232,   233,   184,    -1,   236,    -1,   238,    -1,
      -1,   241,   112,   243,    -1,   195,    -1,     6,    -1,    -1,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   274,   225,    -1,    -1,    -1,    -1,
      -1,    -1,   232,    -1,    -1,    -1,   236,    -1,   238,    -1,
      -1,   241,    -1,   243,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   301,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   184,   315,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,   274,   195,    -1,     6,    -1,    -1,
       9,    -1,    -1,    -1,    -1,    94,    -1,    -1,    -1,    98,
     210,    -1,   342,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   225,    -1,    -1,    -1,    -1,
      -1,    -1,   232,    -1,    -1,   315,   236,    -1,   238,    -1,
      -1,   241,    -1,   243,    -1,    -1,    -1,     6,   378,    -1,
       9,    -1,    -1,    -1,    -1,    -1,    -1,   387,   388,    -1,
      -1,    -1,   342,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,   274,    -1,    -1,   407,    -1,    -1,
      -1,    -1,    -1,   413,    -1,    94,    -1,    -1,    -1,    98,
      -1,    -1,    -1,    -1,    -1,   184,    -1,    -1,   378,    -1,
      -1,   431,    -1,    -1,    -1,    -1,   195,   387,   388,   439,
      -1,    -1,   442,    -1,    -1,   315,    -1,    -1,   448,    -1,
      -1,    -1,    -1,    82,   404,    -1,    -1,   407,   408,    -1,
      -1,    -1,    -1,   413,    -1,    -1,   225,    -1,    -1,    98,
      -1,    -1,   342,   232,    -1,    -1,    -1,   236,    -1,   238,
      -1,   431,   241,   112,   243,    -1,    -1,    -1,    -1,   439,
      -1,    -1,   442,    -1,    -1,    -1,    -1,    -1,   448,    -1,
      -1,    -1,    -1,    -1,    -1,   184,     6,    -1,   378,     9,
      -1,    -1,    -1,    -1,    -1,   274,   195,   387,   388,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   407,    -1,    -1,
      -1,    -1,    -1,   413,    -1,    -1,   225,    -1,    -1,    -1,
      -1,    -1,    -1,   232,    -1,   184,   315,   236,    -1,   238,
      -1,   431,   241,    -1,   243,    -1,   195,    -1,     6,   439,
      -1,     9,   442,    -1,    -1,    -1,    -1,    -1,   448,    -1,
      -1,    -1,    82,   342,    -1,    -1,    -1,    -1,    -1,    -1,
       6,    -1,    -1,     9,    94,   274,   225,    -1,    98,    -1,
      -1,    -1,     6,   232,    -1,     9,    -1,   236,    -1,   238,
      -1,    -1,   241,    -1,   243,    -1,    -1,    -1,    -1,   378,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   387,   388,
      -1,    -1,    -1,    -1,    -1,    -1,   315,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,   274,    -1,    -1,   407,    -1,
      -1,    -1,    -1,    -1,   413,    -1,    -1,    -1,    -1,    -1,
      98,    -1,    -1,   342,    -1,    -1,    82,    -1,    -1,    -1,
      -1,    -1,   431,    -1,    -1,    -1,    -1,    -1,    82,    -1,
     439,    -1,    98,   442,   184,    -1,   315,    -1,    -1,   448,
      -1,    -1,    -1,    -1,    98,   195,    -1,    -1,    -1,   378,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   387,   388,
      -1,    -1,    -1,   342,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   225,    -1,    -1,   407,    -1,
      -1,    -1,   232,    -1,   413,    -1,   236,    -1,   238,    -1,
      -1,   241,    -1,   243,    -1,    -1,   184,    -1,    -1,   378,
      -1,    -1,   431,    -1,    -1,    -1,    -1,   195,   387,   388,
     439,    -1,    -1,   442,   180,    -1,    -1,    -1,   184,   448,
      -1,    -1,    -1,    -1,   274,    -1,    -1,    -1,   407,   195,
     184,    -1,    -1,    -1,   413,    -1,    -1,   225,    -1,    -1,
      -1,   195,    -1,    -1,   232,    -1,    -1,    -1,   236,    -1,
     238,    -1,   431,   241,    -1,   243,    -1,    -1,    -1,   225,
     439,    -1,    -1,   442,    -1,   315,   232,    -1,    -1,   448,
     236,   225,   238,    -1,    -1,   241,    -1,   243,   232,    -1,
       6,    -1,   236,     9,   238,    -1,   274,   241,    -1,   243,
      -1,    -1,   342,    -1,     6,    -1,    -1,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   274,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     274,    -1,    -1,    -1,    -1,    -1,    -1,   315,   378,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   387,   388,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   315,
      -1,    -1,    -1,    -1,   342,    -1,    82,   407,    -1,    -1,
      -1,   315,    -1,   413,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    98,    -1,     6,    -1,   342,     9,    -1,    -1,
      -1,   431,    -1,    -1,    -1,    -1,    98,    -1,   342,   439,
     378,    -1,   442,    -1,    -1,    -1,    -1,    -1,   448,   387,
     388,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   378,    -1,    -1,   403,    -1,    -1,   372,   407,
      -1,   387,   388,    -1,   378,   413,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   387,   388,    -1,    -1,    -1,    -1,    -1,
      -1,   407,    -1,   431,    -1,    -1,    -1,   413,    -1,    -1,
      82,   439,    -1,   407,   442,    -1,    -1,    -1,   184,   413,
     448,    -1,    -1,    -1,    -1,   431,    98,    -1,    -1,   195,
      -1,    -1,   184,   439,    -1,    -1,   442,   431,    -1,    -1,
      -1,    -1,   448,   195,    -1,   439,    -1,    -1,   442,    -1,
      -1,    -1,    -1,    -1,   448,    -1,    -1,    -1,    -1,   225,
      -1,    -1,    -1,    -1,    -1,    -1,   232,    -1,    -1,    -1,
     236,    -1,   238,   225,    -1,   241,    -1,   243,    -1,    -1,
     232,    -1,    -1,    -1,   236,    -1,   238,    -1,    -1,   241,
      -1,   243,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   274,    -1,
      -1,    -1,   184,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   274,   195,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   315,
      -1,    -1,    -1,   225,    -1,    -1,    -1,    -1,    -1,    -1,
     232,    -1,    -1,   315,   236,    -1,   238,    -1,    -1,   241,
      -1,   243,    -1,    -1,    -1,    -1,   342,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     342,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   274,    -1,    -1,    -1,    -1,   373,    -1,    -1,
      -1,    -1,   378,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   387,   388,    -1,    -1,    -1,   378,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   387,   388,    -1,    -1,    -1,
      -1,   407,    -1,   315,    -1,    -1,    -1,   413,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   407,    -1,    -1,    -1,    -1,
      -1,   413,    -1,    -1,    -1,   431,    -1,    -1,    -1,    -1,
     342,    -1,    -1,   439,    -1,    -1,   442,    -1,    -1,   431,
      -1,    -1,   448,    -1,    -1,    -1,    -1,   439,    -1,    -1,
     442,    -1,    -1,    -1,    -1,    -1,   448,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,   378,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   387,   388,    -1,    -1,    -1,
      98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   407,    -1,    31,    -1,    33,
      -1,   413,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,   431,
      37,    38,    39,    40,    41,    42,    43,   439,    -1,    -1,
     442,    -1,    66,    -1,    -1,    -1,   448,    -1,    -1,    -1,
      74,    -1,    76,    77,    78,    79,    80,    81,    -1,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    76,
      77,    78,    79,    80,    81,    -1,   184,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   195,    -1,    -1,
      -1,    -1,    -1,    -1,   118,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   118,    -1,    -1,    -1,    -1,    -1,   225,    -1,    -1,
      -1,    -1,    -1,    -1,   232,    -1,    -1,    -1,   236,    -1,
     238,    -1,    -1,   241,   158,   243,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   176,    -1,    -1,    -1,   180,   181,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    -1,   274,    -1,    -1,    -1,
     194,    -1,    -1,    -1,    -1,    98,    -1,   201,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   192,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   217,   201,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   315,    -1,   233,
     217,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   242,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   233,   234,    -1,   253,
      -1,    -1,    -1,    -1,   342,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   253,    -1,    -1,    -1,
      -1,   258,   276,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   184,    -1,    -1,    -1,    -1,   290,   291,    -1,   276,
     378,    -1,   195,    -1,   298,    -1,   300,    -1,    -1,   387,
     388,    -1,    -1,    -1,   291,    82,    -1,    -1,    -1,   313,
     314,   298,    -1,   300,    -1,    -1,   303,    -1,    -1,   407,
      -1,    98,   225,    -1,    -1,   413,   313,    -1,    -1,   232,
      -1,    -1,    -1,   236,   338,   238,    -1,    -1,   241,   343,
     243,    -1,    -1,   431,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   439,    82,   357,   442,    -1,    -1,    -1,    -1,    -1,
     448,   449,   450,   367,    -1,   369,   370,   371,    98,   457,
     458,   274,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     367,    -1,   369,   370,   371,    -1,    -1,    -1,    -1,   376,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   403,
      -1,    -1,    -1,   390,    -1,    -1,    -1,   184,    -1,    -1,
      -1,   415,   315,    -1,    -1,   419,   420,   421,   195,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   414,   432,    -1,
     434,   435,   419,   420,   421,    -1,    -1,    -1,    -1,   342,
      -1,    -1,    -1,    -1,    -1,   432,    -1,    -1,   435,   436,
      -1,   455,    -1,    -1,   184,    -1,    -1,    -1,    -1,   236,
      -1,   238,    -1,    -1,   241,   195,   243,    -1,   455,    -1,
      -1,    -1,    -1,    -1,    -1,   378,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   387,   388,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   225,    -1,   274,    -1,    -1,
      -1,    -1,   232,    -1,   407,    -1,   236,    -1,   238,    -1,
     413,   241,    -1,   243,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   431,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   439,    -1,   315,   442,
      -1,    -1,    -1,    -1,   274,   448,   449,   450,    -1,    -1,
      -1,    -1,    -1,    -1,   457,   458,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   342,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   315,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   378,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     387,   388,   342,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     407,    -1,    -1,    -1,    -1,    -1,   413,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   378,    -1,
      -1,    -1,    -1,    -1,   431,    -1,    -1,   387,   388,    -1,
      -1,    -1,   439,    -1,    -1,   442,    -1,    -1,    -1,    -1,
      -1,   448,    -1,    -1,    -1,    -1,    -1,   407,    -1,    -1,
      -1,    -1,    -1,   413,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   431,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   439,
      -1,    -1,   442,    -1,    -1,    -1,    -1,    -1,   448,   449,
     450,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   458
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   464,   465,     0,   183,   311,   466,   467,   468,   474,
     481,   483,   455,   455,     0,   467,   150,   489,   489,   236,
     312,   484,   484,   120,   469,   475,    27,   485,   485,   455,
     102,   594,   594,   236,   455,   482,    83,   490,   120,   470,
     476,   214,   486,  1147,   356,   169,   208,   216,   544,   455,
     307,   736,   736,   455,    73,   322,   406,   487,   488,   455,
     455,   356,   455,   168,   354,   405,   595,   601,   120,   471,
     477,   481,   135,   480,   488,   310,  1159,   491,   545,   455,
     546,   356,   444,   626,   597,    54,   434,   739,   139,   471,
     478,   489,   484,   275,   337,   377,   379,   492,   493,   497,
     505,   510,   548,   169,   547,    22,   251,   350,   583,   584,
     585,   586,   588,   592,   593,   455,   356,   239,   679,   442,
     600,   602,  1077,   741,   740,   341,   747,   484,   472,   455,
     455,   455,   455,   455,   359,   549,   455,   216,   582,    60,
      72,    93,   101,   178,   405,  1143,   319,   374,   375,   587,
     455,   585,   455,   593,   596,   455,   356,   235,   681,   599,
     601,   628,   629,   630,   603,    49,   742,   743,   744,  1138,
     742,   442,   455,   455,   594,   245,   358,   442,   496,   498,
     499,   500,   501,   503,   504,  1159,   182,   506,   507,   508,
     441,   494,   495,   496,  1173,    11,    25,    26,    57,    96,
      97,    99,   108,   151,   152,   162,   237,   352,   392,   442,
     511,   512,   513,   514,   521,   530,   534,   537,   538,   539,
     540,   541,   542,   543,   283,  1124,   548,   455,   280,   280,
    1156,   403,   277,  1155,   403,   395,  1167,    24,  1134,   598,
     627,   455,   356,   332,   683,   602,   631,  1118,   604,   743,
     372,   418,   745,   325,   435,   737,   473,   372,  1147,   455,
     499,   455,   500,    63,   363,  1130,     9,   236,   509,   455,
     508,   455,   455,   495,   107,   442,  1089,  1147,  1147,  1089,
     384,   367,  1163,  1147,  1147,  1147,  1147,  1147,  1089,  1147,
      56,  1140,  1147,   455,   513,  1089,   583,   442,  1084,  1085,
    1104,  1084,  1085,   236,  1085,    85,  1141,   175,  1144,   599,
     628,   680,   455,   356,   351,   724,   628,   455,  1118,   227,
     228,   632,   635,   636,   642,     1,    47,    62,   102,   219,
     231,   319,   320,   332,   334,   435,   455,   605,   606,   608,
     612,   614,   616,   617,   623,   624,   625,  1147,  1147,   372,
     283,   746,   109,   748,   736,  1147,   236,  1107,   455,   363,
    1147,   211,   211,   236,   455,   249,   522,  1089,  1089,  1147,
    1147,  1147,  1085,    68,  1089,  1089,  1085,  1147,  1085,   531,
     532,  1089,    96,   516,  1089,   550,   200,   277,  1127,  1085,
     280,   410,   280,   589,   590,  1077,  1076,  1077,   628,   682,
     455,   356,   632,   171,   442,   638,   639,   442,   638,  1141,
    1147,   319,   321,  1128,  1128,  1147,  1141,  1147,   249,  1153,
    1147,    23,  1133,   277,   167,   188,    31,   110,  1107,  1147,
     442,   455,   738,   477,  1107,  1085,  1147,   195,   236,   243,
     315,   378,   407,   448,   535,   536,  1110,  1085,   236,  1085,
      23,   214,  1089,  1148,   278,   280,   518,   519,   520,   515,
     551,  1104,  1084,   280,  1084,   590,   301,   591,  1077,   628,
     684,   455,   633,    84,   634,  1107,   442,  1147,  1133,  1086,
    1104,   279,   380,   613,   236,  1085,  1088,  1107,   436,  1147,
     442,   723,   723,   170,   442,  1107,   749,   750,   139,   479,
      56,   443,   502,   124,   195,   236,   243,   255,   315,   378,
     381,   382,   448,   523,   524,   525,   528,   536,   400,   533,
    1107,   519,   384,  1166,   517,     1,     4,    19,    29,   202,
     233,   240,   261,   286,   292,   319,   326,   339,   364,   366,
     374,   405,   455,   552,   553,   558,   560,   565,   566,   567,
     568,   572,   573,   574,   575,   576,   577,   578,   579,   581,
    1130,  1084,  1107,   317,   685,   686,   687,   725,   643,   640,
    1147,   435,   672,   403,   611,  1104,   234,  1151,   403,  1140,
     200,  1146,   442,  1147,  1147,   750,     1,   442,   751,   752,
     753,   754,   755,   760,   484,   525,    17,   400,  1110,  1107,
    1147,   519,  1153,   319,   403,  1171,   364,  1153,   218,  1149,
    1147,    55,  1139,    37,   113,  1137,  1149,  1149,   260,  1107,
    1173,   384,  1147,   723,   687,   726,     1,    21,    34,    37,
      38,    39,    40,    41,    42,    43,    74,    76,    77,    78,
      79,    80,    81,   118,   201,   217,   236,   253,   276,   291,
     298,   300,   313,   323,   330,   367,   369,   370,   371,   393,
     419,   420,   421,   432,   435,   637,   644,   645,   646,   648,
     649,   650,   651,   652,   654,   666,   667,   669,   670,   671,
     677,   678,  1147,  1164,    27,  1135,   188,  1148,  1107,    56,
     321,   607,   618,  1107,   372,  1165,   236,   615,  1104,   615,
     126,   455,   356,     3,     5,    10,    18,    51,    52,    59,
      71,    75,    87,   111,   118,   119,   149,   161,   165,   179,
     186,   189,   190,   197,   204,   206,   209,   246,   250,   252,
     259,   282,   297,   318,   327,   340,   345,   347,   355,   365,
     374,   383,   385,   386,   389,   391,   396,   412,   417,   422,
     433,   445,   455,   761,   762,   772,   777,   781,   784,   797,
     800,   805,   810,   811,   812,   815,   817,   824,   828,   830,
     845,   848,   850,   852,   855,   857,   863,   872,   874,   891,
     893,   896,   900,   906,   916,   923,   925,   928,   932,   933,
     944,   955,   965,   971,   974,   980,   984,   986,   988,   990,
     993,  1004,  1005,  1014,  1016,  1017,   455,   526,   528,  1089,
    1147,  1149,   123,   167,   555,  1147,  1147,   319,   326,   573,
    1147,  1147,   364,  1147,  1147,  1134,     9,   260,   318,   580,
    1147,   442,   688,   635,   642,   727,   728,   729,   225,   368,
     418,   368,   418,   368,   418,   368,   418,   368,   418,   438,
    1172,   346,  1161,  1107,  1103,  1104,  1104,   214,   224,   346,
     668,  1147,  1147,   167,   188,   223,   411,     9,    50,   225,
     641,  1108,  1109,  1110,   674,   675,  1108,    30,   619,   620,
     621,   622,  1136,  1173,  1140,   180,   610,  1145,   109,   236,
     756,   763,   773,   778,   782,   785,   798,   801,   806,   813,
     816,   818,   825,   829,   831,   846,   849,   851,  1171,   856,
       1,   858,   864,   873,   875,   892,   894,   897,   901,   907,
     917,   924,   926,   929,   934,   945,   956,   966,   236,   349,
     975,   981,   306,   985,   987,   989,   991,   994,   188,  1006,
    1144,  1018,   195,   236,   243,   315,   378,   448,   527,   529,
     123,   316,   364,   559,  1147,   117,   305,   554,    32,   164,
     244,   569,  1085,  1088,   381,  1085,  1085,   287,  1158,  1158,
     281,  1085,    61,    88,    89,   293,   455,   689,   690,   694,
    1147,   638,   729,   448,   403,   655,   458,  1105,  1106,   400,
     651,  1108,    27,   647,   362,  1126,  1126,  1110,  1155,  1155,
     462,   673,   675,   400,    48,   409,   174,   611,  1107,   455,
     455,   764,  1102,  1103,     6,    82,    94,    98,   184,   225,
     232,   238,   241,   274,   342,   387,   388,   413,   431,   439,
     774,  1071,  1092,  1093,  1102,  1108,  1111,   442,   779,  1058,
    1059,  1060,   236,  1081,  1082,  1083,  1104,   236,  1100,  1102,
    1111,   799,   802,   807,  1072,  1073,  1093,  1077,   405,   236,
     819,  1092,  1099,  1102,   826,  1093,   236,   404,   408,   832,
     833,  1058,   296,   297,   310,   356,   847,     6,  1090,  1091,
    1102,  1102,   853,   136,  1057,  1058,  1090,   693,  1102,   876,
    1102,  1108,  1111,   957,  1104,    94,   895,  1093,   898,  1093,
     902,   177,   236,   908,   911,   912,   913,  1081,  1100,  1104,
    1173,  1077,  1074,  1104,  1077,  1074,     9,   935,  1075,  1104,
     150,   248,   946,   947,   948,   949,   951,   952,   953,   954,
    1078,  1079,  1090,   957,  1077,   972,   112,   976,   977,  1093,
      94,   982,  1092,   693,  1102,  1077,  1102,     8,    35,  1008,
     107,  1074,    17,  1085,   118,   236,   556,  1152,   441,   570,
     570,   376,   456,   564,  1085,  1087,  1147,   172,   691,   692,
     691,  1148,   702,   188,   730,  1107,   402,  1170,   225,   449,
     450,   458,  1068,  1070,  1071,  1094,  1102,  1109,  1111,   458,
    1106,  1104,   236,  1139,  1103,  1103,  1110,  1172,  1108,  1088,
    1088,  1136,  1140,   127,   771,    30,   180,   765,  1136,  1155,
     458,  1102,   458,  1112,   458,  1113,  1155,  1127,   458,   458,
     458,   458,   458,   458,   458,   458,  1112,   128,   776,   403,
     775,  1093,   205,  1121,    56,  1061,  1062,   403,  1127,   434,
     786,   236,  1099,  1102,  1077,   130,   808,   156,   456,   809,
    1073,   348,  1125,   319,  1160,  1076,   132,   823,   765,   427,
     428,   429,   430,   133,   827,    49,   210,   786,    17,   438,
     834,   835,   836,   840,  1132,   100,  1155,  1091,  1080,   399,
    1169,   865,  1173,  1102,    92,   331,   394,   877,   878,   879,
     883,   888,   959,  1093,   403,   137,   899,    49,   166,   207,
     215,   288,   903,   912,   138,   909,   423,   436,   400,   402,
     397,   258,   304,  1122,   180,  1019,  1160,  1019,  1075,   143,
     943,   436,   937,  1097,  1102,  1109,   952,   954,  1090,   403,
    1079,   121,   403,   424,   950,   967,   187,   341,   973,  1138,
     210,   977,  1102,   146,   983,   180,   180,   319,   321,   992,
     112,   995,   333,   380,  1009,  1156,  1019,   529,   122,   441,
     564,  1120,  1129,   557,  1104,   240,   347,  1147,   561,   562,
    1099,   693,   700,  1107,   635,   703,   731,   114,   656,  1155,
    1070,  1070,  1070,    70,   360,   457,  1069,   449,   450,   451,
     452,   454,   461,  1070,   365,  1162,  1151,  1088,   114,   609,
    1097,    25,    26,    67,    69,   103,   104,   105,   150,   152,
     160,   234,   401,   442,  1079,   441,   768,    66,   233,   301,
     766,   767,   149,   310,  1095,  1103,  1068,  1070,   403,  1070,
    1068,  1114,  1103,  1109,  1111,   442,  1070,  1117,  1070,  1070,
    1116,  1070,  1068,  1068,  1070,  1115,  1070,  1072,  1093,   187,
     341,   780,  1121,    12,    13,    14,    20,    58,   156,   157,
     185,   191,   214,   222,   226,   256,   257,   262,   272,   279,
     284,   302,   448,   449,   450,   451,   452,   454,   456,   457,
     459,   460,  1063,  1064,  1065,  1066,  1067,    12,    13,    14,
      58,   214,   256,   257,   262,   272,   279,   302,   449,   450,
     454,   458,  1063,  1064,  1065,  1066,  1067,  1093,   309,   783,
    1083,   787,   187,   341,   791,   324,   416,   803,   804,  1173,
    1058,   213,   266,  1050,  1051,  1052,  1054,   426,   441,   820,
    1173,   163,  1025,  1026,  1025,  1025,  1025,  1093,  1072,  1093,
      21,   404,   408,   841,   842,  1059,   134,   844,   440,   836,
     838,   438,   837,   833,  1103,   114,   854,  1081,   859,     9,
      12,    15,    16,   253,   254,   272,   273,   866,   870,   171,
    1097,     9,    56,   173,   223,   411,   884,   885,   886,   880,
     878,   961,  1129,  1156,   403,  1090,  1072,  1093,   366,   904,
     757,   758,  1057,   914,   915,  1102,  1081,     8,    35,  1021,
    1160,  1099,   210,   918,   930,  1173,   938,  1136,  1102,   938,
     403,   403,   520,   149,   404,   408,  1093,    49,   218,   968,
    1093,  1093,   372,  1093,  1102,   180,  1072,  1093,  1097,  1138,
     210,   998,  1102,   159,   163,  1010,     9,  1015,  1081,   930,
     122,   561,  1104,   280,   563,  1085,   563,   193,   695,   233,
     234,   701,   638,    31,    33,    36,    44,    45,    46,    66,
     158,   176,   180,   181,   194,   233,   242,   276,   290,   314,
     338,   343,   357,   403,   415,   434,   455,   649,   650,   652,
     666,   669,   671,   732,   735,  1156,    28,   115,   202,   653,
     658,   659,   660,   661,   663,  1103,  1109,  1111,   457,  1070,
    1070,  1070,  1070,  1070,  1070,   457,  1070,  1171,  1151,  1156,
    1024,  1026,   447,   446,  1097,  1024,   218,    31,    33,    36,
      46,   176,   181,   194,   242,   290,   314,   338,   343,   353,
     357,   415,   425,   769,   770,  1024,   270,  1154,  1154,  1154,
     767,   766,   236,  1096,  1103,   457,  1102,   461,   457,  1069,
     457,   457,  1069,   457,   457,   457,   457,  1069,   457,   457,
     373,  1030,  1031,  1072,  1091,   341,  1171,   398,  1168,  1168,
     403,  1081,   788,   789,   790,  1138,  1102,  1102,   163,   289,
     792,  1011,  1144,   240,   260,  1030,  1053,  1055,   131,   814,
    1054,    96,   305,   442,  1079,    33,    36,    44,    45,    46,
     158,   176,   194,   242,   290,   343,   353,   415,   821,   822,
    1025,   269,  1027,   265,  1028,   187,  1030,   187,  1132,   400,
     843,   839,   841,   757,  1156,   757,  1171,   331,   867,  1171,
     403,    49,   885,   887,  1097,     9,    56,   223,   411,   881,
     882,  1097,   962,  1130,   200,   285,  1157,   661,  1090,  1030,
     187,  1173,  1076,   138,   910,   759,     8,   180,   918,  1102,
     126,   263,  1040,  1041,  1043,  1050,   240,   260,   438,   126,
     438,   940,   941,  1097,  1096,  1093,  1147,  1050,   978,  1173,
    1102,  1030,   187,   403,     9,   996,   997,  1119,   999,  1102,
     978,   999,   307,  1013,   308,  1020,  1021,  1120,   251,   319,
     321,   571,  1147,   173,   696,  1107,   704,  1147,  1154,   153,
     155,  1147,  1100,  1154,  1107,  1102,  1102,  1085,  1138,   662,
     663,   659,  1149,   657,   658,   457,   404,   676,  1085,  1028,
    1024,  1147,  1147,   121,   424,   770,  1099,  1099,  1099,  1112,
    1125,   457,  1070,  1085,  1112,  1112,  1070,  1112,  1112,  1112,
     223,   411,  1112,  1112,  1032,   268,  1033,  1030,  1091,   156,
     284,   156,   284,   789,   279,   745,    86,   325,   435,   265,
     267,   794,  1012,   793,   329,   344,   757,   757,   820,   820,
     820,   820,  1147,   153,   155,  1147,   121,   424,   822,   757,
    1029,  1072,  1073,  1072,  1073,   842,  1058,   757,  1102,   125,
     860,   435,   868,   869,   870,   110,   871,   435,  1098,  1102,
    1108,  1097,    49,   889,   882,   175,   889,   958,  1147,   285,
    1149,  1072,   580,   905,  1173,   760,   915,  1093,   199,   919,
    1173,  1042,  1044,   141,   927,  1043,   142,   931,   240,  1058,
     939,  1057,   940,   262,   969,  1123,   144,   970,   289,  1035,
    1036,   300,  1125,  1072,  1098,   284,  1097,   113,  1000,   394,
    1002,  1156,   154,   264,  1022,  1045,  1046,  1048,  1051,     7,
    1131,   571,  1107,   116,   220,   697,    67,    66,    67,   192,
     233,   234,   258,   303,   376,   390,   414,   436,   455,   649,
     650,   652,   654,   666,   669,   671,   705,   706,   708,   709,
     710,   711,   713,   714,   715,   716,   720,   721,   448,  1101,
    1102,  1107,  1147,  1101,  1147,  1170,   442,   664,   665,  1147,
    1147,  1101,  1101,  1056,  1138,  1056,  1030,   457,   757,  1034,
    1171,   156,  1171,   156,  1093,   129,   796,   795,   757,  1025,
    1025,  1025,  1025,  1101,  1101,  1056,  1056,   757,  1030,   328,
    1030,   328,   861,   136,   862,   869,   102,  1142,   889,   889,
    1098,  1021,   207,   434,   963,  1085,  1147,  1030,   240,   260,
      49,   240,   218,   920,   198,   240,   260,   437,   757,   757,
     936,   757,   942,   693,  1063,  1064,  1065,  1066,  1067,  1037,
     145,   979,   267,  1038,  1102,  1030,  1030,   997,  1146,    95,
    1001,  1146,  1035,   166,   207,   215,   288,  1007,  1076,  1047,
    1049,   148,  1023,  1048,   293,  1079,  1101,  1147,    91,   221,
     698,   271,  1154,   203,   722,   270,   271,   719,  1133,   192,
     438,  1147,  1155,  1147,  1102,   711,   258,   299,   717,   718,
    1107,   247,   299,   449,   450,   734,   247,   299,   449,   450,
     733,   665,  1084,  1108,  1101,   757,  1171,  1171,   757,  1073,
    1073,   757,    49,   889,   406,   890,   307,  1076,   187,   288,
     964,   960,   344,  1093,  1147,   921,  1040,  1051,   240,   240,
     757,   757,   757,  1039,  1102,  1146,  1102,   147,  1003,   757,
     757,   233,   234,  1150,  1107,  1147,  1147,   174,   699,  1147,
    1148,  1147,  1057,  1102,   712,  1085,    90,    91,   116,   294,
     295,   335,   336,   707,   180,   293,  1107,   718,  1101,  1101,
    1150,  1030,  1030,  1093,  1093,  1147,  1076,   307,  1104,   423,
     693,   140,   922,   757,  1102,  1107,  1107,  1147,  1107,  1107,
    1125,  1093,   911,  1147,  1057,  1107,    49,   911,  1093
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
#line 771 "parser.y"
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
#line 795 "parser.y"
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
#line 824 "parser.y"
    { cb_validate_program_environment (current_program); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 825 "parser.y"
    { cb_validate_program_data (current_program); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 833 "parser.y"
    { cb_validate_program_environment (current_program); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 834 "parser.y"
    { cb_validate_program_data (current_program); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 842 "parser.y"
    { cb_validate_program_environment (current_program); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 843 "parser.y"
    { cb_validate_program_data (current_program); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 855 "parser.y"
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
#line 881 "parser.y"
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
#line 905 "parser.y"
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
#line 934 "parser.y"
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
#line 975 "parser.y"
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
#line 1023 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 1024 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 1033 "parser.y"
    {
	if (!current_program->nested_level) {
		cb_error (_("COMMON may only be used in a nested program"));
	}
	current_program->flag_common = 1;
  ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 1040 "parser.y"
    {
	if (!current_program->nested_level) {
		cb_error (_("COMMON may only be used in a nested program"));
	}
	current_program->flag_common = 1;
  ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 1051 "parser.y"
    {
	current_program->flag_initial = 1;
  ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 1055 "parser.y"
    {
	current_program->flag_recursive = 1;
	current_program->flag_initial = 1;
  ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 1080 "parser.y"
    {
	if (current_program->nested_level) {
		cb_error (_("CONFIGURATION SECTION not allowed in nested programs"));
	}
  ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 1115 "parser.y"
    {
	cb_verify (cb_debugging_line, "DEBUGGING MODE");
  ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 1121 "parser.y"
    { ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 1152 "parser.y"
    {
	cb_verify (cb_memory_size_clause, "MEMORY SIZE");
  ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 1164 "parser.y"
    {
	current_program->collating_sequence = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1171 "parser.y"
    {
	/* Ignore */
  ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 1196 "parser.y"
    {
	current_program->function_spec_list = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 1200 "parser.y"
    {
	functions_are_all = 1;
  ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1206 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1208 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1249 "parser.y"
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
#line 1259 "parser.y"
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
#line 1270 "parser.y"
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
#line 1279 "parser.y"
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
#line 1293 "parser.y"
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
#line 1307 "parser.y"
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
#line 1321 "parser.y"
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
#line 1347 "parser.y"
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
#line 1357 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1358 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1366 "parser.y"
    {
	save_tree_1 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1370 "parser.y"
    {
	current_program->alphabet_name_list =
		cb_list_add (current_program->alphabet_name_list, (yyvsp[(5) - (5)]));
  ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1377 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_NATIVE); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1378 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_1); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1379 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_2); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1380 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_EBCDIC); ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1382 "parser.y"
    {
	(yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_CUSTOM);
	CB_ALPHABET_NAME ((yyval))->custom_list = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1389 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1391 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1395 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1396 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1398 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (2)]));
	save_tree_2 = (yyval);
  ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1403 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (4)]);
  ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1414 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1415 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1416 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1417 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1418 "parser.y"
    { (yyval) = cb_norm_high; ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1419 "parser.y"
    { (yyval) = cb_norm_low; ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1423 "parser.y"
    { cb_list_add (save_tree_2, (yyvsp[(1) - (1)])); ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1424 "parser.y"
    { cb_list_add (save_tree_2, cb_space); ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1425 "parser.y"
    { cb_list_add (save_tree_2, cb_zero); ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1426 "parser.y"
    { cb_list_add (save_tree_2, cb_quote); ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1427 "parser.y"
    { cb_list_add (save_tree_2, cb_norm_high); ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1428 "parser.y"
    { cb_list_add (save_tree_2, cb_norm_low); ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1436 "parser.y"
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
#line 1447 "parser.y"
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
#line 1458 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1459 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1463 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1464 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1472 "parser.y"
    {
	current_program->class_name_list =
			cb_list_add (current_program->class_name_list,
			cb_build_class_name ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])));
  ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1480 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1481 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1485 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1487 "parser.y"
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
#line 1501 "parser.y"
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
#line 1516 "parser.y"
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
#line 1583 "parser.y"
    {
	current_program->decimal_point = ',';
	current_program->numeric_separator = '.';
  ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1593 "parser.y"
    { current_program->cursor_pos = (yyvsp[(3) - (3)]); ;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 1600 "parser.y"
    { current_program->crt_status = (yyvsp[(4) - (4)]); ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1607 "parser.y"
    {  PENDING ("SCREEN CONTROL"); ;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 1613 "parser.y"
    {  PENDING ("EVENT STATUS"); ;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 1625 "parser.y"
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
#line 1634 "parser.y"
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
#line 1659 "parser.y"
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
#line 1674 "parser.y"
    {
	validate_file (current_file, (yyvsp[(3) - (6)]));
  ;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1706 "parser.y"
    {
	current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
  ;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1710 "parser.y"
    {
	current_file->fileid_assign = 1;
	current_file->assign = cb_build_assignment_name (current_file, cb_build_reference ("DISK"));
  ;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1715 "parser.y"
    {
	current_file->fileid_assign = 1;
	current_file->assign = cb_build_assignment_name (current_file, cb_build_reference ("PRINTER"));
  ;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1723 "parser.y"
    { current_file->organization = COB_ORG_LINE_SEQUENTIAL; ;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1728 "parser.y"
    {
	current_file->external_assign = 1;
  ;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1732 "parser.y"
    {
	current_file->external_assign = 0;
  ;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1740 "parser.y"
    {
	const char	*s;

	s = "$#@DUMMY@#$";
	(yyval) = cb_build_alphanumeric_literal ((unsigned char *)s, strlen (s));
  ;}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 1747 "parser.y"
    {

	if (!(yyvsp[(1) - (2)]) || ((yyvsp[(1) - (2)]) && CB_TREE_CLASS ((yyvsp[(1) - (2)])) == CB_CLASS_NUMERIC)) {
		if ((yyvsp[(2) - (2)])) {
			if (CB_CHAIN ((yyvsp[(2) - (2)]))) {
				PENDING (_("ASSIGN TO multiple external device names"));
			}
			(yyval) = CB_VALUE ((yyvsp[(2) - (2)]));
		}
	} else {
		if((yyvsp[(2) - (2)])) {
			PENDING (_("ASSIGN TO multiple external device names"));
		}
		(yyval) = (yyvsp[(1) - (2)]);
	}
  ;}
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 1766 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1767 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 1777 "parser.y"
    { current_file->access_mode = COB_ACCESS_SEQUENTIAL; ;}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 1778 "parser.y"
    { current_file->access_mode = COB_ACCESS_DYNAMIC; ;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 1779 "parser.y"
    { current_file->access_mode = COB_ACCESS_RANDOM; ;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1787 "parser.y"
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

  case 205:

/* Line 1455 of yacc.c  */
#line 1807 "parser.y"
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

  case 206:

/* Line 1455 of yacc.c  */
#line 1853 "parser.y"
    {
	key_component_list = NULL;
  ;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1862 "parser.y"
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

  case 210:

/* Line 1455 of yacc.c  */
#line 1877 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1878 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 1879 "parser.y"
    { (yyval) = cb_int('='); ;}
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 1886 "parser.y"
    {
	PENDING ("COLLATING SEQUENCE");
  ;}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1896 "parser.y"
    {
	current_file->file_status = (yyvsp[(4) - (5)]);
	if ((yyvsp[(5) - (5)])) {
		PENDING ("2nd FILE STATUS");
	}
  ;}
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 1917 "parser.y"
    { current_file->lock_mode = COB_LOCK_MANUAL; ;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1918 "parser.y"
    { current_file->lock_mode = COB_LOCK_AUTOMATIC; ;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 1919 "parser.y"
    { current_file->lock_mode = COB_LOCK_EXCLUSIVE; ;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1925 "parser.y"
    {
	current_file->lock_mode |= COB_LOCK_MULTIPLE;
  ;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1928 "parser.y"
    { PENDING ("WITH ROLLBACK"); ;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 1945 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_INDEXED;
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
		current_file->organization = COB_ORG_SEQUENTIAL;
		organized_seen = 1;
	}
  ;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 1963 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = cb_default_organization;
		organized_seen = 1;
	}
  ;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 1972 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_RELATIVE;
		organized_seen = 1;
	}
  ;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 1981 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_LINE_SEQUENTIAL;
		organized_seen = 1;
	}
  ;}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 1996 "parser.y"
    {
	cb_verify (cb_padding_character_clause, "PADDING CHARACTER");
  ;}
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 2005 "parser.y"
    { /* ignored */ ;}
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 2013 "parser.y"
    {
	current_file->key = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 2017 "parser.y"
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

  case 239:

/* Line 1455 of yacc.c  */
#line 2054 "parser.y"
    { current_file->key = (yyvsp[(4) - (4)]); ;}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 2061 "parser.y"
    { /* ignored */ ;}
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 2062 "parser.y"
    { /* ignored */ ;}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 2069 "parser.y"
    { current_file->sharing = (yyvsp[(3) - (3)]); ;}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 2073 "parser.y"
    { (yyval) = NULL; PENDING ("SHARING ALL OTHER"); ;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 2074 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 2075 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 2081 "parser.y"
    { PENDING ("NOMINAL KEY"); ;}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 2112 "parser.y"
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

  case 258:

/* Line 1455 of yacc.c  */
#line 2136 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 2137 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 2138 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 2139 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 2146 "parser.y"
    {
	cb_verify (cb_multiple_file_tape_clause, "MULTIPLE FILE TAPE");
  ;}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 2157 "parser.y"
    { ;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 2174 "parser.y"
    {
	PENDING ("APPLY COMMITMENT-CONTROL");
  ;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 2178 "parser.y"
    {
	PENDING ("APPLY CYL-OVERFLOW");
  ;}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 2182 "parser.y"
    {
	PENDING ("APPLY CORE-INDEX");
  ;}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 2186 "parser.y"
    {
	PENDING ("APPLY FORMS-OVERLAY");
  ;}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 2190 "parser.y"
    {
	PENDING ("APPLY CLOSE-NOFEED");
  ;}
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 2215 "parser.y"
    { current_storage = CB_STORAGE_FILE; ;}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 2218 "parser.y"
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

  case 285:

/* Line 1455 of yacc.c  */
#line 2237 "parser.y"
    {
	if ((yyvsp[(3) - (3)]) && (yyvsp[(3) - (3)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(3) - (3)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 2249 "parser.y"
    {
	if ((yyvsp[(2) - (2)]) && (yyvsp[(2) - (2)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(2) - (2)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 2260 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 2261 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 2271 "parser.y"
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

  case 291:

/* Line 1455 of yacc.c  */
#line 2282 "parser.y"
    {
	/* Shut up bison */
	dummy_tree = (yyvsp[(2) - (4)]);
  ;}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 2294 "parser.y"
    {
	if (current_file->global) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->external = 1;
  ;}
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 2301 "parser.y"
    {
	if (current_file->external) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->global = 1;
  ;}
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 2324 "parser.y"
    { /* ignored */ ;}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 2334 "parser.y"
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

  case 311:

/* Line 1455 of yacc.c  */
#line 2346 "parser.y"
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

  case 312:

/* Line 1455 of yacc.c  */
#line 2372 "parser.y"
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

  case 314:

/* Line 1455 of yacc.c  */
#line 2396 "parser.y"
    {
	current_file->record_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 2402 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 2403 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 2407 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 2408 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 2416 "parser.y"
    {
	cb_verify (cb_label_records_clause, "LABEL RECORDS");
  ;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 2431 "parser.y"
    {
	cb_verify (cb_value_of_clause, "VALUE OF");
  ;}
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 2435 "parser.y"
    {
	if (!current_file->assign) {
		current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 326:

/* Line 1455 of yacc.c  */
#line 2451 "parser.y"
    {
	cb_verify (cb_data_records_clause, "DATA RECORDS");
  ;}
    break;

  case 327:

/* Line 1455 of yacc.c  */
#line 2462 "parser.y"
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

  case 333:

/* Line 1455 of yacc.c  */
#line 2490 "parser.y"
    {
	current_file->latfoot = (yyvsp[(4) - (5)]);
  ;}
    break;

  case 334:

/* Line 1455 of yacc.c  */
#line 2497 "parser.y"
    {
	current_file->lattop = (yyvsp[(3) - (4)]);
  ;}
    break;

  case 335:

/* Line 1455 of yacc.c  */
#line 2504 "parser.y"
    {
	current_file->latbot = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 2513 "parser.y"
    { /* ignore */ ;}
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 2521 "parser.y"
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

  case 338:

/* Line 1455 of yacc.c  */
#line 2539 "parser.y"
    {
	cb_warning (_("file descriptor REPORT IS"));
  ;}
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 2543 "parser.y"
    {
	cb_warning (_("file descriptor REPORTS ARE"));
  ;}
    break;

  case 341:

/* Line 1455 of yacc.c  */
#line 2554 "parser.y"
    { current_storage = CB_STORAGE_WORKING; ;}
    break;

  case 342:

/* Line 1455 of yacc.c  */
#line 2556 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->working_storage =
			cb_field_add (current_program->working_storage, CB_FIELD ((yyvsp[(5) - (5)])));
	}
  ;}
    break;

  case 343:

/* Line 1455 of yacc.c  */
#line 2565 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 344:

/* Line 1455 of yacc.c  */
#line 2566 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 345:

/* Line 1455 of yacc.c  */
#line 2570 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 346:

/* Line 1455 of yacc.c  */
#line 2576 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	(yyval) = CB_TREE (description_field);
  ;}
    break;

  case 351:

/* Line 1455 of yacc.c  */
#line 2596 "parser.y"
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

  case 352:

/* Line 1455 of yacc.c  */
#line 2607 "parser.y"
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

  case 353:

/* Line 1455 of yacc.c  */
#line 2620 "parser.y"
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

  case 354:

/* Line 1455 of yacc.c  */
#line 2631 "parser.y"
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

  case 358:

/* Line 1455 of yacc.c  */
#line 2658 "parser.y"
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

  case 359:

/* Line 1455 of yacc.c  */
#line 2679 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 360:

/* Line 1455 of yacc.c  */
#line 2685 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 361:

/* Line 1455 of yacc.c  */
#line 2691 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 362:

/* Line 1455 of yacc.c  */
#line 2700 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 364:

/* Line 1455 of yacc.c  */
#line 2709 "parser.y"
    {
	current_field->flag_is_global = 1;
	cb_error (_("CONSTANT with GLOBAL clause is not yet supported"));
  ;}
    break;

  case 365:

/* Line 1455 of yacc.c  */
#line 2716 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 366:

/* Line 1455 of yacc.c  */
#line 2717 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 367:

/* Line 1455 of yacc.c  */
#line 2718 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 368:

/* Line 1455 of yacc.c  */
#line 2723 "parser.y"
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

  case 369:

/* Line 1455 of yacc.c  */
#line 2742 "parser.y"
    {
	/* required to check redefines */
	(yyval) = NULL;
  ;}
    break;

  case 370:

/* Line 1455 of yacc.c  */
#line 2748 "parser.y"
    {
	/* required to check redefines */
	(yyval) = cb_true;
  ;}
    break;

  case 386:

/* Line 1455 of yacc.c  */
#line 2777 "parser.y"
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

  case 387:

/* Line 1455 of yacc.c  */
#line 2799 "parser.y"
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

  case 388:

/* Line 1455 of yacc.c  */
#line 2820 "parser.y"
    { current_field->ename = NULL; ;}
    break;

  case 389:

/* Line 1455 of yacc.c  */
#line 2822 "parser.y"
    {
	struct cb_field *x;

	x = CB_FIELD(cb_build_field (cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(2) - (2)]))->data))));
	current_field->ename = x->name;
 ;}
    break;

  case 390:

/* Line 1455 of yacc.c  */
#line 2834 "parser.y"
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

  case 391:

/* Line 1455 of yacc.c  */
#line 2853 "parser.y"
    { current_field->pic = CB_PICTURE ((yyvsp[(1) - (1)])); ;}
    break;

  case 394:

/* Line 1455 of yacc.c  */
#line 2865 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 395:

/* Line 1455 of yacc.c  */
#line 2866 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 396:

/* Line 1455 of yacc.c  */
#line 2867 "parser.y"
    { current_field->usage = CB_USAGE_FLOAT; ;}
    break;

  case 397:

/* Line 1455 of yacc.c  */
#line 2868 "parser.y"
    { current_field->usage = CB_USAGE_DOUBLE; ;}
    break;

  case 398:

/* Line 1455 of yacc.c  */
#line 2869 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 399:

/* Line 1455 of yacc.c  */
#line 2870 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 400:

/* Line 1455 of yacc.c  */
#line 2871 "parser.y"
    { current_field->usage = CB_USAGE_COMP_5; ;}
    break;

  case 401:

/* Line 1455 of yacc.c  */
#line 2872 "parser.y"
    { current_field->usage = CB_USAGE_COMP_X; ;}
    break;

  case 402:

/* Line 1455 of yacc.c  */
#line 2873 "parser.y"
    { current_field->usage = CB_USAGE_DISPLAY; ;}
    break;

  case 403:

/* Line 1455 of yacc.c  */
#line 2874 "parser.y"
    { current_field->usage = CB_USAGE_INDEX; ;}
    break;

  case 404:

/* Line 1455 of yacc.c  */
#line 2875 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 405:

/* Line 1455 of yacc.c  */
#line 2877 "parser.y"
    {
	current_field->usage = CB_USAGE_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 406:

/* Line 1455 of yacc.c  */
#line 2882 "parser.y"
    {
	current_field->usage = CB_USAGE_PROGRAM_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 407:

/* Line 1455 of yacc.c  */
#line 2886 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 408:

/* Line 1455 of yacc.c  */
#line 2887 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 409:

/* Line 1455 of yacc.c  */
#line 2888 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 410:

/* Line 1455 of yacc.c  */
#line 2889 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 411:

/* Line 1455 of yacc.c  */
#line 2890 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 412:

/* Line 1455 of yacc.c  */
#line 2891 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 413:

/* Line 1455 of yacc.c  */
#line 2892 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 414:

/* Line 1455 of yacc.c  */
#line 2893 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_CHAR; ;}
    break;

  case 415:

/* Line 1455 of yacc.c  */
#line 2894 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 416:

/* Line 1455 of yacc.c  */
#line 2895 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 417:

/* Line 1455 of yacc.c  */
#line 2896 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 418:

/* Line 1455 of yacc.c  */
#line 2897 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 419:

/* Line 1455 of yacc.c  */
#line 2898 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 420:

/* Line 1455 of yacc.c  */
#line 2899 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 421:

/* Line 1455 of yacc.c  */
#line 2900 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 422:

/* Line 1455 of yacc.c  */
#line 2901 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 423:

/* Line 1455 of yacc.c  */
#line 2902 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 424:

/* Line 1455 of yacc.c  */
#line 2903 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 425:

/* Line 1455 of yacc.c  */
#line 2905 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  ;}
    break;

  case 426:

/* Line 1455 of yacc.c  */
#line 2913 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_UNSIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_UNSIGNED_LONG;
	}
  ;}
    break;

  case 427:

/* Line 1455 of yacc.c  */
#line 2921 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  ;}
    break;

  case 428:

/* Line 1455 of yacc.c  */
#line 2928 "parser.y"
    { PENDING ("USAGE NATIONAL");;}
    break;

  case 429:

/* Line 1455 of yacc.c  */
#line 2936 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 1;
  ;}
    break;

  case 430:

/* Line 1455 of yacc.c  */
#line 2941 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 0;
  ;}
    break;

  case 434:

/* Line 1455 of yacc.c  */
#line 2958 "parser.y"
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

  case 435:

/* Line 1455 of yacc.c  */
#line 2973 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 436:

/* Line 1455 of yacc.c  */
#line 2974 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 438:

/* Line 1455 of yacc.c  */
#line 2979 "parser.y"
    {
	current_field->occurs_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 441:

/* Line 1455 of yacc.c  */
#line 2988 "parser.y"
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

  case 442:

/* Line 1455 of yacc.c  */
#line 3012 "parser.y"
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

  case 443:

/* Line 1455 of yacc.c  */
#line 3027 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 444:

/* Line 1455 of yacc.c  */
#line 3028 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 445:

/* Line 1455 of yacc.c  */
#line 3032 "parser.y"
    { (yyval) = cb_int (COB_ASCENDING); ;}
    break;

  case 446:

/* Line 1455 of yacc.c  */
#line 3033 "parser.y"
    { (yyval) = cb_int (COB_DESCENDING); ;}
    break;

  case 449:

/* Line 1455 of yacc.c  */
#line 3040 "parser.y"
    {
	current_field->index_list = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 450:

/* Line 1455 of yacc.c  */
#line 3046 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 451:

/* Line 1455 of yacc.c  */
#line 3048 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 452:

/* Line 1455 of yacc.c  */
#line 3053 "parser.y"
    {
	(yyval) = cb_build_index ((yyvsp[(1) - (1)]), cb_int1, 1, current_field);
  ;}
    break;

  case 453:

/* Line 1455 of yacc.c  */
#line 3062 "parser.y"
    { current_field->flag_justified = 1; ;}
    break;

  case 454:

/* Line 1455 of yacc.c  */
#line 3069 "parser.y"
    { current_field->flag_synchronized = 1; ;}
    break;

  case 458:

/* Line 1455 of yacc.c  */
#line 3081 "parser.y"
    { current_field->flag_blank_zero = 1; ;}
    break;

  case 459:

/* Line 1455 of yacc.c  */
#line 3089 "parser.y"
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

  case 460:

/* Line 1455 of yacc.c  */
#line 3113 "parser.y"
    { current_field->values = cb_list_init ((yyvsp[(3) - (3)])); ;}
    break;

  case 461:

/* Line 1455 of yacc.c  */
#line 3117 "parser.y"
    { current_field->values = (yyvsp[(3) - (3)]); ;}
    break;

  case 463:

/* Line 1455 of yacc.c  */
#line 3122 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 464:

/* Line 1455 of yacc.c  */
#line 3123 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 465:

/* Line 1455 of yacc.c  */
#line 3127 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 466:

/* Line 1455 of yacc.c  */
#line 3128 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 468:

/* Line 1455 of yacc.c  */
#line 3133 "parser.y"
    {
	if (current_field->level != 88) {
		cb_error (_("FALSE clause only allowed for 88 level"));
	}
	current_field->false_88 = cb_list_init ((yyvsp[(3) - (3)]));
  ;}
    break;

  case 469:

/* Line 1455 of yacc.c  */
#line 3146 "parser.y"
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

  case 470:

/* Line 1455 of yacc.c  */
#line 3158 "parser.y"
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

  case 471:

/* Line 1455 of yacc.c  */
#line 3178 "parser.y"
    {
	if (current_field->flag_item_based) {
		cb_error (_("BASED and ANY LENGTH are mutually exclusive"));
	} else {
		current_field->flag_any_length = 1;
	}
  ;}
    break;

  case 473:

/* Line 1455 of yacc.c  */
#line 3193 "parser.y"
    {
	current_storage = CB_STORAGE_LOCAL;
	if (current_program->nested_level) {
		cb_error (_("LOCAL-STORAGE not allowed in nested programs"));
	}
  ;}
    break;

  case 474:

/* Line 1455 of yacc.c  */
#line 3200 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->local_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 476:

/* Line 1455 of yacc.c  */
#line 3213 "parser.y"
    { current_storage = CB_STORAGE_LINKAGE; ;}
    break;

  case 477:

/* Line 1455 of yacc.c  */
#line 3215 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->linkage_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 479:

/* Line 1455 of yacc.c  */
#line 3228 "parser.y"
    {
	cb_error (_("REPORT SECTION not supported"));
	current_storage = CB_STORAGE_REPORT;
  ;}
    break;

  case 486:

/* Line 1455 of yacc.c  */
#line 3261 "parser.y"
    {
	cb_warning (_("Report description using defaults"));
  ;}
    break;

  case 488:

/* Line 1455 of yacc.c  */
#line 3269 "parser.y"
    {
	cb_error (_("GLOBAL is not allowed with RD"));
  ;}
    break;

  case 497:

/* Line 1455 of yacc.c  */
#line 3292 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 498:

/* Line 1455 of yacc.c  */
#line 3293 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 520:

/* Line 1455 of yacc.c  */
#line 3349 "parser.y"
    { cb_warning (_("looking for Report line TYPE")); ;}
    break;

  case 571:

/* Line 1455 of yacc.c  */
#line 3454 "parser.y"
    { current_storage = CB_STORAGE_SCREEN; ;}
    break;

  case 572:

/* Line 1455 of yacc.c  */
#line 3455 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 573:

/* Line 1455 of yacc.c  */
#line 3461 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	current_program->screen_storage = description_field;
	current_program->flag_screen = 1;
  ;}
    break;

  case 579:

/* Line 1455 of yacc.c  */
#line 3485 "parser.y"
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

  case 580:

/* Line 1455 of yacc.c  */
#line 3501 "parser.y"
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

  case 583:

/* Line 1455 of yacc.c  */
#line 3525 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 584:

/* Line 1455 of yacc.c  */
#line 3526 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 585:

/* Line 1455 of yacc.c  */
#line 3527 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BELL; ;}
    break;

  case 586:

/* Line 1455 of yacc.c  */
#line 3528 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLINK; ;}
    break;

  case 587:

/* Line 1455 of yacc.c  */
#line 3529 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 588:

/* Line 1455 of yacc.c  */
#line 3530 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 589:

/* Line 1455 of yacc.c  */
#line 3531 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 590:

/* Line 1455 of yacc.c  */
#line 3532 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 591:

/* Line 1455 of yacc.c  */
#line 3533 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REVERSE; ;}
    break;

  case 592:

/* Line 1455 of yacc.c  */
#line 3534 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 593:

/* Line 1455 of yacc.c  */
#line 3535 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_OVERLINE; ;}
    break;

  case 594:

/* Line 1455 of yacc.c  */
#line 3536 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_AUTO; ;}
    break;

  case 595:

/* Line 1455 of yacc.c  */
#line 3537 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_SECURE; ;}
    break;

  case 596:

/* Line 1455 of yacc.c  */
#line 3538 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REQUIRED; ;}
    break;

  case 597:

/* Line 1455 of yacc.c  */
#line 3539 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_FULL; ;}
    break;

  case 598:

/* Line 1455 of yacc.c  */
#line 3540 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_PROMPT; ;}
    break;

  case 599:

/* Line 1455 of yacc.c  */
#line 3542 "parser.y"
    {
	current_field->screen_line = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 600:

/* Line 1455 of yacc.c  */
#line 3546 "parser.y"
    {
	current_field->screen_column = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 601:

/* Line 1455 of yacc.c  */
#line 3550 "parser.y"
    {
	current_field->screen_foreg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 602:

/* Line 1455 of yacc.c  */
#line 3554 "parser.y"
    {
	current_field->screen_backg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 610:

/* Line 1455 of yacc.c  */
#line 3565 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 611:

/* Line 1455 of yacc.c  */
#line 3572 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 612:

/* Line 1455 of yacc.c  */
#line 3576 "parser.y"
    {
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 613:

/* Line 1455 of yacc.c  */
#line 3585 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 614:

/* Line 1455 of yacc.c  */
#line 3589 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 615:

/* Line 1455 of yacc.c  */
#line 3593 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 616:

/* Line 1455 of yacc.c  */
#line 3597 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 617:

/* Line 1455 of yacc.c  */
#line 3601 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 618:

/* Line 1455 of yacc.c  */
#line 3608 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 619:

/* Line 1455 of yacc.c  */
#line 3612 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 620:

/* Line 1455 of yacc.c  */
#line 3616 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 621:

/* Line 1455 of yacc.c  */
#line 3620 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 622:

/* Line 1455 of yacc.c  */
#line 3624 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 623:

/* Line 1455 of yacc.c  */
#line 3632 "parser.y"
    {
	current_field->occurs_max = cb_get_int ((yyvsp[(2) - (3)]));
	current_field->occurs_min = current_field->occurs_max;
	current_field->indexes++;
	current_field->flag_occurs = 1;
  ;}
    break;

  case 625:

/* Line 1455 of yacc.c  */
#line 3646 "parser.y"
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

  case 626:

/* Line 1455 of yacc.c  */
#line 3656 "parser.y"
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

  case 627:

/* Line 1455 of yacc.c  */
#line 3666 "parser.y"
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

  case 628:

/* Line 1455 of yacc.c  */
#line 3683 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 629:

/* Line 1455 of yacc.c  */
#line 3685 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 630:

/* Line 1455 of yacc.c  */
#line 3689 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 631:

/* Line 1455 of yacc.c  */
#line 3691 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	current_program->flag_chained = 1;
  ;}
    break;

  case 632:

/* Line 1455 of yacc.c  */
#line 3695 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 633:

/* Line 1455 of yacc.c  */
#line 3699 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 634:

/* Line 1455 of yacc.c  */
#line 3701 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 635:

/* Line 1455 of yacc.c  */
#line 3706 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), cb_build_identifier ((yyvsp[(4) - (4)])));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 637:

/* Line 1455 of yacc.c  */
#line 3715 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 638:

/* Line 1455 of yacc.c  */
#line 3719 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 640:

/* Line 1455 of yacc.c  */
#line 3731 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_AUTO;
	}
  ;}
    break;

  case 641:

/* Line 1455 of yacc.c  */
#line 3739 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_4;
	}
  ;}
    break;

  case 642:

/* Line 1455 of yacc.c  */
#line 3747 "parser.y"
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

  case 643:

/* Line 1455 of yacc.c  */
#line 3776 "parser.y"
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

  case 645:

/* Line 1455 of yacc.c  */
#line 3809 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OPTIONAL only allowed for BY REFERENCE items"));
	}
  ;}
    break;

  case 646:

/* Line 1455 of yacc.c  */
#line 3818 "parser.y"
    {
	if (current_program->prog_type == CB_FUNCTION_TYPE) {
		cb_error (_("RETURNING clause is required for a FUNCTION"));
	}
  ;}
    break;

  case 647:

/* Line 1455 of yacc.c  */
#line 3824 "parser.y"
    {
	if (cb_ref ((yyvsp[(2) - (2)])) != cb_error_node) {
		current_program->returning = (yyvsp[(2) - (2)]);
		if (cb_field ((yyvsp[(2) - (2)]))->storage != CB_STORAGE_LINKAGE) {
			cb_error (_("RETURNING item is not defined in LINKAGE SECTION"));
		}
	}
  ;}
    break;

  case 649:

/* Line 1455 of yacc.c  */
#line 3835 "parser.y"
    { in_declaratives = 1; ;}
    break;

  case 650:

/* Line 1455 of yacc.c  */
#line 3838 "parser.y"
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

  case 656:

/* Line 1455 of yacc.c  */
#line 3871 "parser.y"
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

  case 657:

/* Line 1455 of yacc.c  */
#line 3887 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 658:

/* Line 1455 of yacc.c  */
#line 3899 "parser.y"
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

  case 659:

/* Line 1455 of yacc.c  */
#line 3930 "parser.y"
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

  case 660:

/* Line 1455 of yacc.c  */
#line 3967 "parser.y"
    {
	non_const_word = 0;
	check_unreached = 0;
	if ((yyvsp[(1) - (1)]) != cb_error_node) {
		cb_error_x ((yyvsp[(1) - (1)]), _("Unknown statement '%s'"), CB_NAME ((yyvsp[(1) - (1)])));
	}
	YYERROR;
  ;}
    break;

  case 661:

/* Line 1455 of yacc.c  */
#line 3978 "parser.y"
    { (yyval) = cb_build_section_name ((yyvsp[(1) - (1)]), 0); ;}
    break;

  case 663:

/* Line 1455 of yacc.c  */
#line 3982 "parser.y"
    { /* ignore */ ;}
    break;

  case 664:

/* Line 1455 of yacc.c  */
#line 3991 "parser.y"
    {
	(yyval) = current_program->exec_list;
	current_program->exec_list = NULL;
  ;}
    break;

  case 665:

/* Line 1455 of yacc.c  */
#line 3995 "parser.y"
    {
	(yyval) = CB_TREE (current_statement);
	current_statement = NULL;
  ;}
    break;

  case 666:

/* Line 1455 of yacc.c  */
#line 4000 "parser.y"
    {
	(yyval) = cb_list_reverse (current_program->exec_list);
	current_program->exec_list = (yyvsp[(1) - (3)]);
	current_statement = CB_STATEMENT ((yyvsp[(2) - (3)]));
  ;}
    break;

  case 667:

/* Line 1455 of yacc.c  */
#line 4008 "parser.y"
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

  case 718:

/* Line 1455 of yacc.c  */
#line 4080 "parser.y"
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

  case 719:

/* Line 1455 of yacc.c  */
#line 4102 "parser.y"
    {
	BEGIN_STATEMENT ("ACCEPT", TERM_ACCEPT);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 721:

/* Line 1455 of yacc.c  */
#line 4115 "parser.y"
    {
	cb_emit_accept ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 722:

/* Line 1455 of yacc.c  */
#line 4119 "parser.y"
    {
	PENDING ("ACCEPT .. FROM ESCAPE KEY");
  ;}
    break;

  case 723:

/* Line 1455 of yacc.c  */
#line 4123 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 0);
  ;}
    break;

  case 724:

/* Line 1455 of yacc.c  */
#line 4127 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 1);
  ;}
    break;

  case 725:

/* Line 1455 of yacc.c  */
#line 4131 "parser.y"
    {
	cb_emit_accept_date ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 726:

/* Line 1455 of yacc.c  */
#line 4135 "parser.y"
    {
	cb_emit_accept_date_yyyymmdd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 727:

/* Line 1455 of yacc.c  */
#line 4139 "parser.y"
    {
	cb_emit_accept_day ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 728:

/* Line 1455 of yacc.c  */
#line 4143 "parser.y"
    {
	cb_emit_accept_day_yyyyddd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 729:

/* Line 1455 of yacc.c  */
#line 4147 "parser.y"
    {
	cb_emit_accept_day_of_week ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 730:

/* Line 1455 of yacc.c  */
#line 4151 "parser.y"
    {
	cb_emit_accept_time ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 731:

/* Line 1455 of yacc.c  */
#line 4155 "parser.y"
    {
	cb_emit_accept_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 732:

/* Line 1455 of yacc.c  */
#line 4159 "parser.y"
    {
	cb_emit_accept_environment ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 733:

/* Line 1455 of yacc.c  */
#line 4163 "parser.y"
    { 
	cb_emit_get_environment ((yyvsp[(4) - (5)]), (yyvsp[(1) - (5)]));
  ;}
    break;

  case 734:

/* Line 1455 of yacc.c  */
#line 4167 "parser.y"
    {
	cb_emit_accept_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 735:

/* Line 1455 of yacc.c  */
#line 4171 "parser.y"
    {
	cb_emit_accept_arg_value ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 736:

/* Line 1455 of yacc.c  */
#line 4175 "parser.y"
    {
	cb_emit_accept_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 737:

/* Line 1455 of yacc.c  */
#line 4179 "parser.y"
    {
	cb_emit_accept_name ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 738:

/* Line 1455 of yacc.c  */
#line 4185 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 739:

/* Line 1455 of yacc.c  */
#line 4186 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 740:

/* Line 1455 of yacc.c  */
#line 4187 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); ;}
    break;

  case 741:

/* Line 1455 of yacc.c  */
#line 4188 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), NULL); ;}
    break;

  case 742:

/* Line 1455 of yacc.c  */
#line 4189 "parser.y"
    { (yyval) = cb_build_pair (NULL, (yyvsp[(2) - (2)])); ;}
    break;

  case 743:

/* Line 1455 of yacc.c  */
#line 4190 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 744:

/* Line 1455 of yacc.c  */
#line 4194 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 745:

/* Line 1455 of yacc.c  */
#line 4198 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 746:

/* Line 1455 of yacc.c  */
#line 4199 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 751:

/* Line 1455 of yacc.c  */
#line 4212 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 752:

/* Line 1455 of yacc.c  */
#line 4213 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 753:

/* Line 1455 of yacc.c  */
#line 4214 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 754:

/* Line 1455 of yacc.c  */
#line 4215 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 755:

/* Line 1455 of yacc.c  */
#line 4216 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 756:

/* Line 1455 of yacc.c  */
#line 4217 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 757:

/* Line 1455 of yacc.c  */
#line 4218 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 758:

/* Line 1455 of yacc.c  */
#line 4220 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 759:

/* Line 1455 of yacc.c  */
#line 4224 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 760:

/* Line 1455 of yacc.c  */
#line 4228 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 761:

/* Line 1455 of yacc.c  */
#line 4232 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 762:

/* Line 1455 of yacc.c  */
#line 4236 "parser.y"
    { dispattrs |= COB_SCREEN_AUTO; ;}
    break;

  case 763:

/* Line 1455 of yacc.c  */
#line 4237 "parser.y"
    { dispattrs |= COB_SCREEN_FULL; ;}
    break;

  case 764:

/* Line 1455 of yacc.c  */
#line 4238 "parser.y"
    { dispattrs |= COB_SCREEN_REQUIRED; ;}
    break;

  case 765:

/* Line 1455 of yacc.c  */
#line 4239 "parser.y"
    { dispattrs |= COB_SCREEN_SECURE; ;}
    break;

  case 766:

/* Line 1455 of yacc.c  */
#line 4240 "parser.y"
    { dispattrs |= COB_SCREEN_UPDATE; ;}
    break;

  case 767:

/* Line 1455 of yacc.c  */
#line 4241 "parser.y"
    { dispattrs |= COB_SCREEN_PROMPT; ;}
    break;

  case 768:

/* Line 1455 of yacc.c  */
#line 4245 "parser.y"
    { terminator_warning (TERM_ACCEPT); ;}
    break;

  case 769:

/* Line 1455 of yacc.c  */
#line 4246 "parser.y"
    { terminator_clear (TERM_ACCEPT); ;}
    break;

  case 770:

/* Line 1455 of yacc.c  */
#line 4255 "parser.y"
    { BEGIN_STATEMENT ("ADD", TERM_ADD); ;}
    break;

  case 772:

/* Line 1455 of yacc.c  */
#line 4262 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '+', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 773:

/* Line 1455 of yacc.c  */
#line 4266 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(4) - (5)]), 0, cb_build_binary_list ((yyvsp[(1) - (5)]), '+'));
  ;}
    break;

  case 774:

/* Line 1455 of yacc.c  */
#line 4270 "parser.y"
    {
	cb_emit_corresponding (cb_build_add, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 776:

/* Line 1455 of yacc.c  */
#line 4276 "parser.y"
    { cb_list_add ((yyvsp[(0) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 777:

/* Line 1455 of yacc.c  */
#line 4280 "parser.y"
    { terminator_warning (TERM_ADD); ;}
    break;

  case 778:

/* Line 1455 of yacc.c  */
#line 4281 "parser.y"
    { terminator_clear (TERM_ADD); ;}
    break;

  case 779:

/* Line 1455 of yacc.c  */
#line 4290 "parser.y"
    { BEGIN_STATEMENT ("ALLOCATE", 0); ;}
    break;

  case 781:

/* Line 1455 of yacc.c  */
#line 4296 "parser.y"
    {
	cb_emit_allocate ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), NULL, (yyvsp[(2) - (3)]));
  ;}
    break;

  case 782:

/* Line 1455 of yacc.c  */
#line 4300 "parser.y"
    {
	cb_emit_allocate (NULL, (yyvsp[(5) - (5)]), (yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]));
  ;}
    break;

  case 783:

/* Line 1455 of yacc.c  */
#line 4306 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 784:

/* Line 1455 of yacc.c  */
#line 4307 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 785:

/* Line 1455 of yacc.c  */
#line 4317 "parser.y"
    {
	cb_error (_("ALTER statement is obsolete and unsupported"));
  ;}
    break;

  case 790:

/* Line 1455 of yacc.c  */
#line 4335 "parser.y"
    { BEGIN_STATEMENT ("CALL", TERM_CALL); ;}
    break;

  case 791:

/* Line 1455 of yacc.c  */
#line 4339 "parser.y"
    {
	cb_emit_call ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 792:

/* Line 1455 of yacc.c  */
#line 4345 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 793:

/* Line 1455 of yacc.c  */
#line 4347 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 794:

/* Line 1455 of yacc.c  */
#line 4351 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 795:

/* Line 1455 of yacc.c  */
#line 4355 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 796:

/* Line 1455 of yacc.c  */
#line 4357 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 797:

/* Line 1455 of yacc.c  */
#line 4362 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OMITTED only allowed with BY REFERENCE"));
	}
	(yyval) = cb_build_pair (cb_int (call_mode), cb_null);
  ;}
    break;

  case 798:

/* Line 1455 of yacc.c  */
#line 4369 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), (yyvsp[(3) - (3)]));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 800:

/* Line 1455 of yacc.c  */
#line 4378 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 801:

/* Line 1455 of yacc.c  */
#line 4382 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY CONTENT not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_CONTENT;
	}
  ;}
    break;

  case 802:

/* Line 1455 of yacc.c  */
#line 4390 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 803:

/* Line 1455 of yacc.c  */
#line 4400 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 804:

/* Line 1455 of yacc.c  */
#line 4401 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 805:

/* Line 1455 of yacc.c  */
#line 4402 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 806:

/* Line 1455 of yacc.c  */
#line 4407 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 807:

/* Line 1455 of yacc.c  */
#line 4411 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 808:

/* Line 1455 of yacc.c  */
#line 4415 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 809:

/* Line 1455 of yacc.c  */
#line 4422 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 810:

/* Line 1455 of yacc.c  */
#line 4426 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 811:

/* Line 1455 of yacc.c  */
#line 4430 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 812:

/* Line 1455 of yacc.c  */
#line 4436 "parser.y"
    { terminator_warning (TERM_CALL); ;}
    break;

  case 813:

/* Line 1455 of yacc.c  */
#line 4437 "parser.y"
    { terminator_clear (TERM_CALL); ;}
    break;

  case 814:

/* Line 1455 of yacc.c  */
#line 4446 "parser.y"
    { BEGIN_STATEMENT ("CANCEL", 0); ;}
    break;

  case 817:

/* Line 1455 of yacc.c  */
#line 4452 "parser.y"
    {
	cb_emit_cancel ((yyvsp[(2) - (2)]));
  ;}
    break;

  case 818:

/* Line 1455 of yacc.c  */
#line 4463 "parser.y"
    { BEGIN_STATEMENT ("CLOSE", 0); ;}
    break;

  case 821:

/* Line 1455 of yacc.c  */
#line 4470 "parser.y"
    {
	BEGIN_IMPLICIT_STATEMENT ((yyvsp[(2) - (3)]));
	if ((yyvsp[(2) - (3)]) != cb_error_node) {
		cb_emit_close ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
	}
  ;}
    break;

  case 822:

/* Line 1455 of yacc.c  */
#line 4479 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NORMAL); ;}
    break;

  case 823:

/* Line 1455 of yacc.c  */
#line 4480 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT); ;}
    break;

  case 824:

/* Line 1455 of yacc.c  */
#line 4481 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT_REMOVAL); ;}
    break;

  case 825:

/* Line 1455 of yacc.c  */
#line 4482 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NO_REWIND); ;}
    break;

  case 826:

/* Line 1455 of yacc.c  */
#line 4483 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_LOCK); ;}
    break;

  case 829:

/* Line 1455 of yacc.c  */
#line 4494 "parser.y"
    { BEGIN_STATEMENT ("COMPUTE", TERM_COMPUTE); ;}
    break;

  case 831:

/* Line 1455 of yacc.c  */
#line 4501 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(1) - (4)]), 0, (yyvsp[(3) - (4)]));
  ;}
    break;

  case 832:

/* Line 1455 of yacc.c  */
#line 4507 "parser.y"
    { terminator_warning (TERM_COMPUTE); ;}
    break;

  case 833:

/* Line 1455 of yacc.c  */
#line 4508 "parser.y"
    { terminator_clear (TERM_COMPUTE); ;}
    break;

  case 836:

/* Line 1455 of yacc.c  */
#line 4519 "parser.y"
    {
	BEGIN_STATEMENT ("COMMIT", 0);
	cb_emit_commit ();
  ;}
    break;

  case 837:

/* Line 1455 of yacc.c  */
#line 4532 "parser.y"
    {
	BEGIN_STATEMENT ("CONTINUE", 0);
	cb_emit_continue ();
  ;}
    break;

  case 838:

/* Line 1455 of yacc.c  */
#line 4544 "parser.y"
    { BEGIN_STATEMENT ("DELETE", TERM_DELETE); ;}
    break;

  case 839:

/* Line 1455 of yacc.c  */
#line 4547 "parser.y"
    {
	if ((yyvsp[(3) - (6)]) != cb_error_node) {
		cb_emit_delete ((yyvsp[(3) - (6)]));
	}
  ;}
    break;

  case 840:

/* Line 1455 of yacc.c  */
#line 4555 "parser.y"
    { terminator_warning (TERM_DELETE); ;}
    break;

  case 841:

/* Line 1455 of yacc.c  */
#line 4556 "parser.y"
    { terminator_clear (TERM_DELETE); ;}
    break;

  case 842:

/* Line 1455 of yacc.c  */
#line 4565 "parser.y"
    { BEGIN_STATEMENT ("DELETE-FILE", 0); ;}
    break;

  case 843:

/* Line 1455 of yacc.c  */
#line 4567 "parser.y"
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

  case 844:

/* Line 1455 of yacc.c  */
#line 4585 "parser.y"
    {
	BEGIN_STATEMENT ("DISPLAY", TERM_DISPLAY);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 846:

/* Line 1455 of yacc.c  */
#line 4598 "parser.y"
    {
	cb_emit_env_name ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 847:

/* Line 1455 of yacc.c  */
#line 4602 "parser.y"
    {
	cb_emit_env_value ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 848:

/* Line 1455 of yacc.c  */
#line 4606 "parser.y"
    {
	cb_emit_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 849:

/* Line 1455 of yacc.c  */
#line 4610 "parser.y"
    {
	cb_emit_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 850:

/* Line 1455 of yacc.c  */
#line 4614 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (4)]), cb_int0, (yyvsp[(3) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 851:

/* Line 1455 of yacc.c  */
#line 4618 "parser.y"
    {
	cb_emit_display_mnemonic ((yyvsp[(1) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 852:

/* Line 1455 of yacc.c  */
#line 4622 "parser.y"
    {
	cb_tree word = cb_build_display_upon_direct ((yyvsp[(4) - (6)]));
	cb_emit_display ((yyvsp[(1) - (6)]), word, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 853:

/* Line 1455 of yacc.c  */
#line 4627 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 854:

/* Line 1455 of yacc.c  */
#line 4631 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 855:

/* Line 1455 of yacc.c  */
#line 4637 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 856:

/* Line 1455 of yacc.c  */
#line 4638 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 857:

/* Line 1455 of yacc.c  */
#line 4639 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 860:

/* Line 1455 of yacc.c  */
#line 4649 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 861:

/* Line 1455 of yacc.c  */
#line 4650 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 862:

/* Line 1455 of yacc.c  */
#line 4651 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 863:

/* Line 1455 of yacc.c  */
#line 4652 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 864:

/* Line 1455 of yacc.c  */
#line 4653 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 865:

/* Line 1455 of yacc.c  */
#line 4654 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 866:

/* Line 1455 of yacc.c  */
#line 4655 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 867:

/* Line 1455 of yacc.c  */
#line 4656 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 868:

/* Line 1455 of yacc.c  */
#line 4657 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 869:

/* Line 1455 of yacc.c  */
#line 4659 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 870:

/* Line 1455 of yacc.c  */
#line 4663 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 871:

/* Line 1455 of yacc.c  */
#line 4667 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 872:

/* Line 1455 of yacc.c  */
#line 4671 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 873:

/* Line 1455 of yacc.c  */
#line 4675 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 874:

/* Line 1455 of yacc.c  */
#line 4676 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 875:

/* Line 1455 of yacc.c  */
#line 4680 "parser.y"
    { terminator_warning (TERM_DISPLAY); ;}
    break;

  case 876:

/* Line 1455 of yacc.c  */
#line 4681 "parser.y"
    { terminator_clear (TERM_DISPLAY); ;}
    break;

  case 877:

/* Line 1455 of yacc.c  */
#line 4690 "parser.y"
    { BEGIN_STATEMENT ("DIVIDE", TERM_DIVIDE); ;}
    break;

  case 879:

/* Line 1455 of yacc.c  */
#line 4697 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '/', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 880:

/* Line 1455 of yacc.c  */
#line 4701 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(3) - (6)]), '/', (yyvsp[(1) - (6)])));
  ;}
    break;

  case 881:

/* Line 1455 of yacc.c  */
#line 4705 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '/', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 882:

/* Line 1455 of yacc.c  */
#line 4709 "parser.y"
    {
	cb_emit_divide ((yyvsp[(3) - (8)]), (yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 883:

/* Line 1455 of yacc.c  */
#line 4713 "parser.y"
    {
	cb_emit_divide ((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 884:

/* Line 1455 of yacc.c  */
#line 4719 "parser.y"
    { terminator_warning (TERM_DIVIDE); ;}
    break;

  case 885:

/* Line 1455 of yacc.c  */
#line 4720 "parser.y"
    { terminator_clear (TERM_DIVIDE); ;}
    break;

  case 886:

/* Line 1455 of yacc.c  */
#line 4729 "parser.y"
    { BEGIN_STATEMENT ("ENTRY", 0); ;}
    break;

  case 887:

/* Line 1455 of yacc.c  */
#line 4731 "parser.y"
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

  case 888:

/* Line 1455 of yacc.c  */
#line 4751 "parser.y"
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

  case 889:

/* Line 1455 of yacc.c  */
#line 4762 "parser.y"
    {
	cb_emit_evaluate ((yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]));
	eval_level--;
  ;}
    break;

  case 890:

/* Line 1455 of yacc.c  */
#line 4769 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 891:

/* Line 1455 of yacc.c  */
#line 4772 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 892:

/* Line 1455 of yacc.c  */
#line 4782 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE_P ((yyvsp[(1) - (1)]))) {
		eval_check[eval_level][eval_inc++] = 0;
	} else {
		eval_check[eval_level][eval_inc++] = 1;
	}
  ;}
    break;

  case 893:

/* Line 1455 of yacc.c  */
#line 4791 "parser.y"
    {
	(yyval) = cb_true;
	eval_check[eval_level][eval_inc++] = 2;
  ;}
    break;

  case 894:

/* Line 1455 of yacc.c  */
#line 4796 "parser.y"
    {
	(yyval) = cb_false;
	eval_check[eval_level][eval_inc++] = 3;
  ;}
    break;

  case 895:

/* Line 1455 of yacc.c  */
#line 4804 "parser.y"
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

  case 896:

/* Line 1455 of yacc.c  */
#line 4832 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 897:

/* Line 1455 of yacc.c  */
#line 4834 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 898:

/* Line 1455 of yacc.c  */
#line 4839 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 899:

/* Line 1455 of yacc.c  */
#line 4843 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]));
	eval_inc2 = 0;
  ;}
    break;

  case 900:

/* Line 1455 of yacc.c  */
#line 4854 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 901:

/* Line 1455 of yacc.c  */
#line 4858 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 902:

/* Line 1455 of yacc.c  */
#line 4862 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), NULL);
	eval_inc2 = 0;
  ;}
    break;

  case 903:

/* Line 1455 of yacc.c  */
#line 4872 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 904:

/* Line 1455 of yacc.c  */
#line 4874 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 905:

/* Line 1455 of yacc.c  */
#line 4878 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 906:

/* Line 1455 of yacc.c  */
#line 4881 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 907:

/* Line 1455 of yacc.c  */
#line 4891 "parser.y"
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

  case 908:

/* Line 1455 of yacc.c  */
#line 4919 "parser.y"
    { (yyval) = cb_any; eval_inc2++; ;}
    break;

  case 909:

/* Line 1455 of yacc.c  */
#line 4920 "parser.y"
    { (yyval) = cb_true; eval_inc2++; ;}
    break;

  case 910:

/* Line 1455 of yacc.c  */
#line 4921 "parser.y"
    { (yyval) = cb_false; eval_inc2++; ;}
    break;

  case 911:

/* Line 1455 of yacc.c  */
#line 4924 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 912:

/* Line 1455 of yacc.c  */
#line 4925 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 913:

/* Line 1455 of yacc.c  */
#line 4929 "parser.y"
    { terminator_warning (TERM_EVALUATE); ;}
    break;

  case 914:

/* Line 1455 of yacc.c  */
#line 4930 "parser.y"
    { terminator_clear (TERM_EVALUATE); ;}
    break;

  case 915:

/* Line 1455 of yacc.c  */
#line 4939 "parser.y"
    { BEGIN_STATEMENT ("EXIT", 0); ;}
    break;

  case 917:

/* Line 1455 of yacc.c  */
#line 4944 "parser.y"
    { /* nothing */ ;}
    break;

  case 918:

/* Line 1455 of yacc.c  */
#line 4946 "parser.y"
    {
	if (in_declaratives && use_global_ind) {
		cb_error (_("EXIT PROGRAM is not allowed within a USE GLOBAL procedure"));
	}
	check_unreached = 1;
	cb_emit_exit (0);
  ;}
    break;

  case 919:

/* Line 1455 of yacc.c  */
#line 4954 "parser.y"
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

  case 920:

/* Line 1455 of yacc.c  */
#line 4971 "parser.y"
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

  case 921:

/* Line 1455 of yacc.c  */
#line 4988 "parser.y"
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

  case 922:

/* Line 1455 of yacc.c  */
#line 5006 "parser.y"
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

  case 923:

/* Line 1455 of yacc.c  */
#line 5030 "parser.y"
    { BEGIN_STATEMENT ("FREE", 0); ;}
    break;

  case 924:

/* Line 1455 of yacc.c  */
#line 5032 "parser.y"
    {
	cb_emit_free ((yyvsp[(3) - (3)]));
  ;}
    break;

  case 925:

/* Line 1455 of yacc.c  */
#line 5043 "parser.y"
    { BEGIN_STATEMENT ("GENERATE", 0); ;}
    break;

  case 926:

/* Line 1455 of yacc.c  */
#line 5045 "parser.y"
    {
	PENDING("GENERATE");
  ;}
    break;

  case 927:

/* Line 1455 of yacc.c  */
#line 5056 "parser.y"
    { BEGIN_STATEMENT ("GO TO", 0); ;}
    break;

  case 928:

/* Line 1455 of yacc.c  */
#line 5058 "parser.y"
    {
	cb_emit_goto ((yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 929:

/* Line 1455 of yacc.c  */
#line 5065 "parser.y"
    {
	check_unreached = 1;
	(yyval) = NULL;
  ;}
    break;

  case 930:

/* Line 1455 of yacc.c  */
#line 5070 "parser.y"
    {
	check_unreached = 0;
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 931:

/* Line 1455 of yacc.c  */
#line 5082 "parser.y"
    { BEGIN_STATEMENT ("GOBACK", 0); ;}
    break;

  case 932:

/* Line 1455 of yacc.c  */
#line 5083 "parser.y"
    {
	check_unreached = 1;
	cb_emit_exit (1);
  ;}
    break;

  case 933:

/* Line 1455 of yacc.c  */
#line 5095 "parser.y"
    { BEGIN_STATEMENT ("IF", TERM_IF); ;}
    break;

  case 934:

/* Line 1455 of yacc.c  */
#line 5097 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 935:

/* Line 1455 of yacc.c  */
#line 5102 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(6) - (8)]) == NULL) {
		cb_error (_("syntax error"));
	}
	cb_emit_if ((yyvsp[(3) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 937:

/* Line 1455 of yacc.c  */
#line 5113 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 938:

/* Line 1455 of yacc.c  */
#line 5117 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 939:

/* Line 1455 of yacc.c  */
#line 5121 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 940:

/* Line 1455 of yacc.c  */
#line 5130 "parser.y"
    { terminator_warning (TERM_IF); ;}
    break;

  case 941:

/* Line 1455 of yacc.c  */
#line 5131 "parser.y"
    { terminator_clear (TERM_IF); ;}
    break;

  case 942:

/* Line 1455 of yacc.c  */
#line 5140 "parser.y"
    { BEGIN_STATEMENT ("INITIALIZE", 0); ;}
    break;

  case 943:

/* Line 1455 of yacc.c  */
#line 5142 "parser.y"
    {
	cb_emit_initialize ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 944:

/* Line 1455 of yacc.c  */
#line 5148 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 945:

/* Line 1455 of yacc.c  */
#line 5149 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 946:

/* Line 1455 of yacc.c  */
#line 5153 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 947:

/* Line 1455 of yacc.c  */
#line 5154 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 948:

/* Line 1455 of yacc.c  */
#line 5155 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 949:

/* Line 1455 of yacc.c  */
#line 5159 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 950:

/* Line 1455 of yacc.c  */
#line 5161 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 951:

/* Line 1455 of yacc.c  */
#line 5165 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 952:

/* Line 1455 of yacc.c  */
#line 5167 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 953:

/* Line 1455 of yacc.c  */
#line 5171 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 954:

/* Line 1455 of yacc.c  */
#line 5175 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHABETIC); ;}
    break;

  case 955:

/* Line 1455 of yacc.c  */
#line 5176 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC); ;}
    break;

  case 956:

/* Line 1455 of yacc.c  */
#line 5177 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC); ;}
    break;

  case 957:

/* Line 1455 of yacc.c  */
#line 5178 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC_EDITED); ;}
    break;

  case 958:

/* Line 1455 of yacc.c  */
#line 5179 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC_EDITED); ;}
    break;

  case 959:

/* Line 1455 of yacc.c  */
#line 5180 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL); ;}
    break;

  case 960:

/* Line 1455 of yacc.c  */
#line 5181 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL_EDITED); ;}
    break;

  case 961:

/* Line 1455 of yacc.c  */
#line 5185 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 962:

/* Line 1455 of yacc.c  */
#line 5186 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 963:

/* Line 1455 of yacc.c  */
#line 5195 "parser.y"
    { BEGIN_STATEMENT ("INITIATE", 0); ;}
    break;

  case 964:

/* Line 1455 of yacc.c  */
#line 5197 "parser.y"
    {
	PENDING("INITIATE");
  ;}
    break;

  case 965:

/* Line 1455 of yacc.c  */
#line 5208 "parser.y"
    {
	BEGIN_STATEMENT ("INSPECT", 0);
	sending_id = 0;
	inspect_keyword = 0;
  ;}
    break;

  case 967:

/* Line 1455 of yacc.c  */
#line 5217 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 0; ;}
    break;

  case 968:

/* Line 1455 of yacc.c  */
#line 5218 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 969:

/* Line 1455 of yacc.c  */
#line 5219 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 972:

/* Line 1455 of yacc.c  */
#line 5228 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 0); ;}
    break;

  case 973:

/* Line 1455 of yacc.c  */
#line 5229 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int1, 1); ;}
    break;

  case 974:

/* Line 1455 of yacc.c  */
#line 5230 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 2); ;}
    break;

  case 975:

/* Line 1455 of yacc.c  */
#line 5236 "parser.y"
    { cb_init_tarrying (); ;}
    break;

  case 976:

/* Line 1455 of yacc.c  */
#line 5237 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 977:

/* Line 1455 of yacc.c  */
#line 5241 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 978:

/* Line 1455 of yacc.c  */
#line 5242 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 979:

/* Line 1455 of yacc.c  */
#line 5246 "parser.y"
    { (yyval) = cb_build_tarrying_data ((yyvsp[(1) - (2)])); ;}
    break;

  case 980:

/* Line 1455 of yacc.c  */
#line 5247 "parser.y"
    { (yyval) = cb_build_tarrying_characters ((yyvsp[(2) - (2)])); ;}
    break;

  case 981:

/* Line 1455 of yacc.c  */
#line 5248 "parser.y"
    { (yyval) = cb_build_tarrying_all (); ;}
    break;

  case 982:

/* Line 1455 of yacc.c  */
#line 5249 "parser.y"
    { (yyval) = cb_build_tarrying_leading (); ;}
    break;

  case 983:

/* Line 1455 of yacc.c  */
#line 5250 "parser.y"
    { (yyval) = cb_build_tarrying_trailing (); ;}
    break;

  case 984:

/* Line 1455 of yacc.c  */
#line 5251 "parser.y"
    { (yyval) = cb_build_tarrying_value ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 985:

/* Line 1455 of yacc.c  */
#line 5257 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); inspect_keyword = 0; ;}
    break;

  case 986:

/* Line 1455 of yacc.c  */
#line 5261 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 987:

/* Line 1455 of yacc.c  */
#line 5262 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 988:

/* Line 1455 of yacc.c  */
#line 5267 "parser.y"
    {
	(yyval) = cb_build_replacing_characters ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]), save_tree_1);
	inspect_keyword = 0;
  ;}
    break;

  case 989:

/* Line 1455 of yacc.c  */
#line 5271 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 990:

/* Line 1455 of yacc.c  */
#line 5275 "parser.y"
    { /* Nothing */ ;}
    break;

  case 991:

/* Line 1455 of yacc.c  */
#line 5276 "parser.y"
    { inspect_keyword = 1; ;}
    break;

  case 992:

/* Line 1455 of yacc.c  */
#line 5277 "parser.y"
    { inspect_keyword = 2; ;}
    break;

  case 993:

/* Line 1455 of yacc.c  */
#line 5278 "parser.y"
    { inspect_keyword = 3; ;}
    break;

  case 994:

/* Line 1455 of yacc.c  */
#line 5279 "parser.y"
    { inspect_keyword = 4; ;}
    break;

  case 995:

/* Line 1455 of yacc.c  */
#line 5284 "parser.y"
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

  case 996:

/* Line 1455 of yacc.c  */
#line 5310 "parser.y"
    {
	if (cb_validate_inspect (save_tree_1, (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])) < 0 ) {
		(yyval) = cb_error_node;
	} else {
		(yyval) = cb_build_converting ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 997:

/* Line 1455 of yacc.c  */
#line 5322 "parser.y"
    { (yyval) = cb_build_inspect_region_start (); ;}
    break;

  case 998:

/* Line 1455 of yacc.c  */
#line 5324 "parser.y"
    { (yyval) = cb_build_inspect_region ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 1001:

/* Line 1455 of yacc.c  */
#line 5335 "parser.y"
    { BEGIN_STATEMENT ("MERGE", 0); ;}
    break;

  case 1003:

/* Line 1455 of yacc.c  */
#line 5345 "parser.y"
    { BEGIN_STATEMENT ("MOVE", 0); ;}
    break;

  case 1005:

/* Line 1455 of yacc.c  */
#line 5351 "parser.y"
    {
	cb_emit_move ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1006:

/* Line 1455 of yacc.c  */
#line 5355 "parser.y"
    {
	cb_emit_move_corresponding ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1007:

/* Line 1455 of yacc.c  */
#line 5366 "parser.y"
    { BEGIN_STATEMENT ("MULTIPLY", TERM_MULTIPLY); ;}
    break;

  case 1009:

/* Line 1455 of yacc.c  */
#line 5373 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '*', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 1010:

/* Line 1455 of yacc.c  */
#line 5377 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '*', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 1011:

/* Line 1455 of yacc.c  */
#line 5383 "parser.y"
    { terminator_warning (TERM_MULTIPLY); ;}
    break;

  case 1012:

/* Line 1455 of yacc.c  */
#line 5384 "parser.y"
    { terminator_clear (TERM_MULTIPLY); ;}
    break;

  case 1013:

/* Line 1455 of yacc.c  */
#line 5393 "parser.y"
    { BEGIN_STATEMENT ("OPEN", 0); ;}
    break;

  case 1016:

/* Line 1455 of yacc.c  */
#line 5400 "parser.y"
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

  case 1017:

/* Line 1455 of yacc.c  */
#line 5412 "parser.y"
    { (yyval) = cb_int (COB_OPEN_INPUT); ;}
    break;

  case 1018:

/* Line 1455 of yacc.c  */
#line 5413 "parser.y"
    { (yyval) = cb_int (COB_OPEN_OUTPUT); ;}
    break;

  case 1019:

/* Line 1455 of yacc.c  */
#line 5414 "parser.y"
    { (yyval) = cb_int (COB_OPEN_I_O); ;}
    break;

  case 1020:

/* Line 1455 of yacc.c  */
#line 5415 "parser.y"
    { (yyval) = cb_int (COB_OPEN_EXTEND); ;}
    break;

  case 1021:

/* Line 1455 of yacc.c  */
#line 5419 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1022:

/* Line 1455 of yacc.c  */
#line 5420 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1023:

/* Line 1455 of yacc.c  */
#line 5424 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1024:

/* Line 1455 of yacc.c  */
#line 5425 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1025:

/* Line 1455 of yacc.c  */
#line 5426 "parser.y"
    { PENDING ("OPEN ... WITH LOCK"); ;}
    break;

  case 1026:

/* Line 1455 of yacc.c  */
#line 5438 "parser.y"
    { BEGIN_STATEMENT ("PERFORM", TERM_PERFORM); ;}
    break;

  case 1028:

/* Line 1455 of yacc.c  */
#line 5444 "parser.y"
    {
	cb_emit_perform ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));
  ;}
    break;

  case 1029:

/* Line 1455 of yacc.c  */
#line 5448 "parser.y"
    {
	perform_stack = cb_cons ((yyvsp[(1) - (1)]), perform_stack);
	check_unreached = 0;
  ;}
    break;

  case 1030:

/* Line 1455 of yacc.c  */
#line 5453 "parser.y"
    {
	perform_stack = CB_CHAIN (perform_stack);
	cb_emit_perform ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 1031:

/* Line 1455 of yacc.c  */
#line 5458 "parser.y"
    {
	cb_emit_perform ((yyvsp[(1) - (2)]), NULL);
  ;}
    break;

  case 1032:

/* Line 1455 of yacc.c  */
#line 5464 "parser.y"
    { terminator_error (); ;}
    break;

  case 1033:

/* Line 1455 of yacc.c  */
#line 5465 "parser.y"
    { terminator_clear (TERM_PERFORM); ;}
    break;

  case 1034:

/* Line 1455 of yacc.c  */
#line 5470 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(1) - (1)]))->length = cb_true; /* return from $1 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (1)]), (yyvsp[(1) - (1)]));
  ;}
    break;

  case 1035:

/* Line 1455 of yacc.c  */
#line 5475 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(3) - (3)]))->length = cb_true; /* return from $3 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1036:

/* Line 1455 of yacc.c  */
#line 5483 "parser.y"
    {
	(yyval) = cb_build_perform_once (NULL);
  ;}
    break;

  case 1037:

/* Line 1455 of yacc.c  */
#line 5487 "parser.y"
    {
	(yyval) = cb_build_perform_forever (NULL);
  ;}
    break;

  case 1038:

/* Line 1455 of yacc.c  */
#line 5491 "parser.y"
    {
	(yyval) = cb_build_perform_times ((yyvsp[(1) - (2)]));
	current_program->loop_counter++;
  ;}
    break;

  case 1039:

/* Line 1455 of yacc.c  */
#line 5496 "parser.y"
    {
	cb_tree varying;

	varying = cb_list_init (cb_build_perform_varying (NULL, NULL, NULL, (yyvsp[(3) - (3)])));
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), varying);
  ;}
    break;

  case 1040:

/* Line 1455 of yacc.c  */
#line 5503 "parser.y"
    {
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1041:

/* Line 1455 of yacc.c  */
#line 5509 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1042:

/* Line 1455 of yacc.c  */
#line 5510 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1043:

/* Line 1455 of yacc.c  */
#line 5514 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1044:

/* Line 1455 of yacc.c  */
#line 5516 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1045:

/* Line 1455 of yacc.c  */
#line 5521 "parser.y"
    {
	(yyval) = cb_build_perform_varying ((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1046:

/* Line 1455 of yacc.c  */
#line 5532 "parser.y"
    { BEGIN_STATEMENT ("READ", TERM_READ); ;}
    break;

  case 1047:

/* Line 1455 of yacc.c  */
#line 5535 "parser.y"
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

  case 1048:

/* Line 1455 of yacc.c  */
#line 5561 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1049:

/* Line 1455 of yacc.c  */
#line 5562 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1050:

/* Line 1455 of yacc.c  */
#line 5566 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1051:

/* Line 1455 of yacc.c  */
#line 5568 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1052:

/* Line 1455 of yacc.c  */
#line 5572 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1053:

/* Line 1455 of yacc.c  */
#line 5576 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1054:

/* Line 1455 of yacc.c  */
#line 5580 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1055:

/* Line 1455 of yacc.c  */
#line 5584 "parser.y"
    {
	(yyval) = cb_int4;
  ;}
    break;

  case 1056:

/* Line 1455 of yacc.c  */
#line 5590 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1057:

/* Line 1455 of yacc.c  */
#line 5592 "parser.y"
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

  case 1061:

/* Line 1455 of yacc.c  */
#line 5611 "parser.y"
    { terminator_warning (TERM_READ); ;}
    break;

  case 1062:

/* Line 1455 of yacc.c  */
#line 5612 "parser.y"
    { terminator_clear (TERM_READ); ;}
    break;

  case 1063:

/* Line 1455 of yacc.c  */
#line 5621 "parser.y"
    { BEGIN_STATEMENT ("RELEASE", 0); ;}
    break;

  case 1064:

/* Line 1455 of yacc.c  */
#line 5623 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_release ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
	}
  ;}
    break;

  case 1065:

/* Line 1455 of yacc.c  */
#line 5636 "parser.y"
    { BEGIN_STATEMENT ("RETURN", TERM_RETURN); ;}
    break;

  case 1066:

/* Line 1455 of yacc.c  */
#line 5639 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_return ((yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]));
	}
  ;}
    break;

  case 1067:

/* Line 1455 of yacc.c  */
#line 5647 "parser.y"
    { terminator_warning (TERM_RETURN); ;}
    break;

  case 1068:

/* Line 1455 of yacc.c  */
#line 5648 "parser.y"
    { terminator_clear (TERM_RETURN); ;}
    break;

  case 1069:

/* Line 1455 of yacc.c  */
#line 5657 "parser.y"
    { BEGIN_STATEMENT ("REWRITE", TERM_REWRITE); ;}
    break;

  case 1070:

/* Line 1455 of yacc.c  */
#line 5660 "parser.y"
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

  case 1071:

/* Line 1455 of yacc.c  */
#line 5674 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1072:

/* Line 1455 of yacc.c  */
#line 5676 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1073:

/* Line 1455 of yacc.c  */
#line 5680 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1074:

/* Line 1455 of yacc.c  */
#line 5686 "parser.y"
    { terminator_warning (TERM_REWRITE); ;}
    break;

  case 1075:

/* Line 1455 of yacc.c  */
#line 5687 "parser.y"
    { terminator_clear (TERM_REWRITE); ;}
    break;

  case 1076:

/* Line 1455 of yacc.c  */
#line 5697 "parser.y"
    {
	BEGIN_STATEMENT ("ROLLBACK", 0);
	cb_emit_rollback ();
  ;}
    break;

  case 1077:

/* Line 1455 of yacc.c  */
#line 5709 "parser.y"
    { BEGIN_STATEMENT ("SEARCH", TERM_SEARCH); ;}
    break;

  case 1079:

/* Line 1455 of yacc.c  */
#line 5716 "parser.y"
    {
	cb_emit_search ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1080:

/* Line 1455 of yacc.c  */
#line 5720 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1081:

/* Line 1455 of yacc.c  */
#line 5724 "parser.y"
    {
	cb_emit_search_all ((yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1082:

/* Line 1455 of yacc.c  */
#line 5730 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1083:

/* Line 1455 of yacc.c  */
#line 5731 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1084:

/* Line 1455 of yacc.c  */
#line 5735 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1085:

/* Line 1455 of yacc.c  */
#line 5737 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1086:

/* Line 1455 of yacc.c  */
#line 5741 "parser.y"
    {
	(yyval) = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 1087:

/* Line 1455 of yacc.c  */
#line 5747 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1088:

/* Line 1455 of yacc.c  */
#line 5748 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); CB_IF ((yyvsp[(1) - (2)]))->stmt2 = (yyvsp[(2) - (2)]); ;}
    break;

  case 1089:

/* Line 1455 of yacc.c  */
#line 5753 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1090:

/* Line 1455 of yacc.c  */
#line 5757 "parser.y"
    {
	(yyval) = cb_build_if ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), NULL);
  ;}
    break;

  case 1091:

/* Line 1455 of yacc.c  */
#line 5763 "parser.y"
    { terminator_warning (TERM_SEARCH); ;}
    break;

  case 1092:

/* Line 1455 of yacc.c  */
#line 5764 "parser.y"
    { terminator_clear (TERM_SEARCH); ;}
    break;

  case 1093:

/* Line 1455 of yacc.c  */
#line 5773 "parser.y"
    { BEGIN_STATEMENT ("SET", 0); ;}
    break;

  case 1100:

/* Line 1455 of yacc.c  */
#line 5789 "parser.y"
    {
	cb_emit_setenv ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1101:

/* Line 1455 of yacc.c  */
#line 5798 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (4)]), cb_build_ppointer ((yyvsp[(4) - (4)])));
  ;}
    break;

  case 1102:

/* Line 1455 of yacc.c  */
#line 5802 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1103:

/* Line 1455 of yacc.c  */
#line 5811 "parser.y"
    {
	cb_emit_set_up_down ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1104:

/* Line 1455 of yacc.c  */
#line 5817 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1105:

/* Line 1455 of yacc.c  */
#line 5818 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1108:

/* Line 1455 of yacc.c  */
#line 5830 "parser.y"
    {
	cb_emit_set_on_off ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1111:

/* Line 1455 of yacc.c  */
#line 5844 "parser.y"
    {
	cb_emit_set_true ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1112:

/* Line 1455 of yacc.c  */
#line 5848 "parser.y"
    {
	cb_emit_set_false ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1113:

/* Line 1455 of yacc.c  */
#line 5859 "parser.y"
    { BEGIN_STATEMENT ("SORT", 0); ;}
    break;

  case 1115:

/* Line 1455 of yacc.c  */
#line 5865 "parser.y"
    {
	cb_emit_sort_init ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (4)]))) && (yyvsp[(2) - (4)]) == NULL) {
		cb_error (_("File sort requires KEY phrase"));
	}
	/* used in sort_input/sort_output */
	save_tree_1 = (yyvsp[(1) - (4)]);
  ;}
    break;

  case 1116:

/* Line 1455 of yacc.c  */
#line 5874 "parser.y"
    {
	cb_emit_sort_finish ((yyvsp[(1) - (7)]));
  ;}
    break;

  case 1117:

/* Line 1455 of yacc.c  */
#line 5881 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 1118:

/* Line 1455 of yacc.c  */
#line 5886 "parser.y"
    {
	cb_tree l;

	if (!cb_allow_is_in_sort_key_spec && (yyvsp[(5) - (6)]) != NULL) {
		cb_error (_("syntax error"));
		(yyval) = cb_error_node;
	} else {
		if ((yyvsp[(6) - (6)]) == NULL) {
			(yyvsp[(6) - (6)]) = cb_list_init (NULL);
		}
		for (l = (yyvsp[(6) - (6)]); l; l = CB_CHAIN (l)) {
			CB_PURPOSE (l) = (yyvsp[(3) - (6)]);
		}
		(yyval) = cb_list_append ((yyvsp[(1) - (6)]), (yyvsp[(6) - (6)]));
	}
  ;}
    break;

  case 1119:

/* Line 1455 of yacc.c  */
#line 5905 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1120:

/* Line 1455 of yacc.c  */
#line 5906 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1122:

/* Line 1455 of yacc.c  */
#line 5910 "parser.y"
    { /* nothing */ ;}
    break;

  case 1123:

/* Line 1455 of yacc.c  */
#line 5914 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1124:

/* Line 1455 of yacc.c  */
#line 5915 "parser.y"
    { (yyval) = cb_ref ((yyvsp[(3) - (3)])); ;}
    break;

  case 1125:

/* Line 1455 of yacc.c  */
#line 5920 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires USING or INPUT PROCEDURE"));
	}
  ;}
    break;

  case 1126:

/* Line 1455 of yacc.c  */
#line 5926 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("USING invalid with table SORT"));
	} else {
		cb_emit_sort_using (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1127:

/* Line 1455 of yacc.c  */
#line 5934 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("INPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_input ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1128:

/* Line 1455 of yacc.c  */
#line 5945 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires GIVING or OUTPUT PROCEDURE"));
	}
  ;}
    break;

  case 1129:

/* Line 1455 of yacc.c  */
#line 5951 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("GIVING invalid with table SORT"));
	} else {
		cb_emit_sort_giving (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1130:

/* Line 1455 of yacc.c  */
#line 5959 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("OUTPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_output ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1131:

/* Line 1455 of yacc.c  */
#line 5974 "parser.y"
    { BEGIN_STATEMENT ("START", TERM_START); ;}
    break;

  case 1132:

/* Line 1455 of yacc.c  */
#line 5975 "parser.y"
    { (yyval) = cb_int (COB_EQ); ;}
    break;

  case 1133:

/* Line 1455 of yacc.c  */
#line 5978 "parser.y"
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

  case 1134:

/* Line 1455 of yacc.c  */
#line 5995 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1135:

/* Line 1455 of yacc.c  */
#line 5997 "parser.y"
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

  case 1136:

/* Line 1455 of yacc.c  */
#line 6012 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_NE : COB_EQ); ;}
    break;

  case 1137:

/* Line 1455 of yacc.c  */
#line 6013 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LE : COB_GT); ;}
    break;

  case 1138:

/* Line 1455 of yacc.c  */
#line 6014 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GE : COB_LT); ;}
    break;

  case 1139:

/* Line 1455 of yacc.c  */
#line 6015 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LT : COB_GE); ;}
    break;

  case 1140:

/* Line 1455 of yacc.c  */
#line 6016 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GT : COB_LE); ;}
    break;

  case 1141:

/* Line 1455 of yacc.c  */
#line 6020 "parser.y"
    { terminator_warning (TERM_START); ;}
    break;

  case 1142:

/* Line 1455 of yacc.c  */
#line 6021 "parser.y"
    { terminator_clear (TERM_START); ;}
    break;

  case 1143:

/* Line 1455 of yacc.c  */
#line 6030 "parser.y"
    { BEGIN_STATEMENT ("STOP", 0); ;}
    break;

  case 1144:

/* Line 1455 of yacc.c  */
#line 6032 "parser.y"
    {
	cb_emit_stop_run ((yyvsp[(4) - (4)]));
  ;}
    break;

  case 1145:

/* Line 1455 of yacc.c  */
#line 6036 "parser.y"
    {
	cb_verify (cb_stop_literal_statement, "STOP literal");
  ;}
    break;

  case 1146:

/* Line 1455 of yacc.c  */
#line 6042 "parser.y"
    { (yyval) = current_program->cb_return_code; ;}
    break;

  case 1147:

/* Line 1455 of yacc.c  */
#line 6043 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1148:

/* Line 1455 of yacc.c  */
#line 6044 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1149:

/* Line 1455 of yacc.c  */
#line 6053 "parser.y"
    { BEGIN_STATEMENT ("STRING", TERM_STRING); ;}
    break;

  case 1150:

/* Line 1455 of yacc.c  */
#line 6056 "parser.y"
    {
	cb_emit_string ((yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]));
  ;}
    break;

  case 1151:

/* Line 1455 of yacc.c  */
#line 6062 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1152:

/* Line 1455 of yacc.c  */
#line 6063 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1153:

/* Line 1455 of yacc.c  */
#line 6067 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1154:

/* Line 1455 of yacc.c  */
#line 6068 "parser.y"
    { (yyval) = cb_build_pair (cb_int0, NULL); ;}
    break;

  case 1155:

/* Line 1455 of yacc.c  */
#line 6069 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), NULL); ;}
    break;

  case 1156:

/* Line 1455 of yacc.c  */
#line 6073 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1157:

/* Line 1455 of yacc.c  */
#line 6074 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1158:

/* Line 1455 of yacc.c  */
#line 6078 "parser.y"
    { terminator_warning (TERM_STRING); ;}
    break;

  case 1159:

/* Line 1455 of yacc.c  */
#line 6079 "parser.y"
    { terminator_clear (TERM_STRING); ;}
    break;

  case 1160:

/* Line 1455 of yacc.c  */
#line 6088 "parser.y"
    { BEGIN_STATEMENT ("SUBTRACT", TERM_SUBTRACT); ;}
    break;

  case 1162:

/* Line 1455 of yacc.c  */
#line 6095 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '-', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 1163:

/* Line 1455 of yacc.c  */
#line 6099 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_list (cb_cons ((yyvsp[(3) - (6)]), (yyvsp[(1) - (6)])), '-'));
  ;}
    break;

  case 1164:

/* Line 1455 of yacc.c  */
#line 6103 "parser.y"
    {
	cb_emit_corresponding (cb_build_sub, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 1165:

/* Line 1455 of yacc.c  */
#line 6109 "parser.y"
    { terminator_warning (TERM_SUBTRACT); ;}
    break;

  case 1166:

/* Line 1455 of yacc.c  */
#line 6110 "parser.y"
    { terminator_clear (TERM_SUBTRACT); ;}
    break;

  case 1167:

/* Line 1455 of yacc.c  */
#line 6120 "parser.y"
    {
	BEGIN_STATEMENT ("SUPPRESS", 0);
	PENDING("SUPPRESS");
  ;}
    break;

  case 1170:

/* Line 1455 of yacc.c  */
#line 6135 "parser.y"
    { BEGIN_STATEMENT ("TERMINATE", 0); ;}
    break;

  case 1171:

/* Line 1455 of yacc.c  */
#line 6137 "parser.y"
    {
	PENDING("TERMINATE");
  ;}
    break;

  case 1172:

/* Line 1455 of yacc.c  */
#line 6148 "parser.y"
    { BEGIN_STATEMENT ("TRANSFORM", 0); ;}
    break;

  case 1173:

/* Line 1455 of yacc.c  */
#line 6150 "parser.y"
    {
	cb_tree		x;

	x = cb_build_converting ((yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]), cb_build_inspect_region_start ());
	cb_emit_inspect ((yyvsp[(3) - (7)]), x, cb_int0, 2);
  ;}
    break;

  case 1174:

/* Line 1455 of yacc.c  */
#line 6164 "parser.y"
    { BEGIN_STATEMENT ("UNLOCK", 0); ;}
    break;

  case 1175:

/* Line 1455 of yacc.c  */
#line 6166 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_unlock ((yyvsp[(3) - (4)]));
	}
  ;}
    break;

  case 1179:

/* Line 1455 of yacc.c  */
#line 6185 "parser.y"
    { BEGIN_STATEMENT ("UNSTRING", TERM_UNSTRING); ;}
    break;

  case 1180:

/* Line 1455 of yacc.c  */
#line 6189 "parser.y"
    {
	cb_emit_unstring ((yyvsp[(3) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]));
  ;}
    break;

  case 1181:

/* Line 1455 of yacc.c  */
#line 6195 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1182:

/* Line 1455 of yacc.c  */
#line 6197 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1183:

/* Line 1455 of yacc.c  */
#line 6201 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1184:

/* Line 1455 of yacc.c  */
#line 6203 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1185:

/* Line 1455 of yacc.c  */
#line 6208 "parser.y"
    {
	(yyval) = cb_build_unstring_delimited ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1186:

/* Line 1455 of yacc.c  */
#line 6214 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 1187:

/* Line 1455 of yacc.c  */
#line 6216 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1188:

/* Line 1455 of yacc.c  */
#line 6221 "parser.y"
    {
	(yyval) = cb_build_unstring_into ((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1189:

/* Line 1455 of yacc.c  */
#line 6227 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1190:

/* Line 1455 of yacc.c  */
#line 6228 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1191:

/* Line 1455 of yacc.c  */
#line 6232 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1192:

/* Line 1455 of yacc.c  */
#line 6233 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1193:

/* Line 1455 of yacc.c  */
#line 6237 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1194:

/* Line 1455 of yacc.c  */
#line 6238 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1195:

/* Line 1455 of yacc.c  */
#line 6242 "parser.y"
    { terminator_warning (TERM_UNSTRING); ;}
    break;

  case 1196:

/* Line 1455 of yacc.c  */
#line 6243 "parser.y"
    { terminator_clear (TERM_UNSTRING); ;}
    break;

  case 1200:

/* Line 1455 of yacc.c  */
#line 6261 "parser.y"
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

  case 1201:

/* Line 1455 of yacc.c  */
#line 6282 "parser.y"
    {
	use_global_ind = 0;
  ;}
    break;

  case 1202:

/* Line 1455 of yacc.c  */
#line 6286 "parser.y"
    {
	use_global_ind = 1;
	current_program->flag_global_use = 1;
  ;}
    break;

  case 1203:

/* Line 1455 of yacc.c  */
#line 6294 "parser.y"
    {
	cb_tree		l;

	for (l = (yyvsp[(1) - (1)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			setup_use_file (CB_FILE (cb_ref (CB_VALUE (l))));
		}
	}
  ;}
    break;

  case 1204:

/* Line 1455 of yacc.c  */
#line 6304 "parser.y"
    {
	current_program->global_handler[COB_OPEN_INPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_INPUT].handler_prog = current_program;
  ;}
    break;

  case 1205:

/* Line 1455 of yacc.c  */
#line 6309 "parser.y"
    {
	current_program->global_handler[COB_OPEN_OUTPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_OUTPUT].handler_prog = current_program;
  ;}
    break;

  case 1206:

/* Line 1455 of yacc.c  */
#line 6314 "parser.y"
    {
	current_program->global_handler[COB_OPEN_I_O].handler_label = current_section;
	current_program->global_handler[COB_OPEN_I_O].handler_prog = current_program;
  ;}
    break;

  case 1207:

/* Line 1455 of yacc.c  */
#line 6319 "parser.y"
    {
	current_program->global_handler[COB_OPEN_EXTEND].handler_label = current_section;
	current_program->global_handler[COB_OPEN_EXTEND].handler_prog = current_program;
  ;}
    break;

  case 1220:

/* Line 1455 of yacc.c  */
#line 6351 "parser.y"
    {
	PENDING ("USE FOR DEBUGGING");
  ;}
    break;

  case 1223:

/* Line 1455 of yacc.c  */
#line 6363 "parser.y"
    {
	PENDING ("USE BEFORE REPORTING");
  ;}
    break;

  case 1224:

/* Line 1455 of yacc.c  */
#line 6374 "parser.y"
    { BEGIN_STATEMENT ("WRITE", TERM_WRITE); ;}
    break;

  case 1225:

/* Line 1455 of yacc.c  */
#line 6377 "parser.y"
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

  case 1226:

/* Line 1455 of yacc.c  */
#line 6391 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1227:

/* Line 1455 of yacc.c  */
#line 6392 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1228:

/* Line 1455 of yacc.c  */
#line 6397 "parser.y"
    {
	(yyval) = cb_int0;
  ;}
    break;

  case 1229:

/* Line 1455 of yacc.c  */
#line 6401 "parser.y"
    {
	(yyval) = cb_build_write_advancing_lines ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 1230:

/* Line 1455 of yacc.c  */
#line 6405 "parser.y"
    {
	(yyval) = cb_build_write_advancing_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1231:

/* Line 1455 of yacc.c  */
#line 6409 "parser.y"
    {
	(yyval) = cb_build_write_advancing_page ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1232:

/* Line 1455 of yacc.c  */
#line 6415 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1233:

/* Line 1455 of yacc.c  */
#line 6416 "parser.y"
    { (yyval) = CB_AFTER; ;}
    break;

  case 1237:

/* Line 1455 of yacc.c  */
#line 6425 "parser.y"
    { terminator_warning (TERM_WRITE); ;}
    break;

  case 1238:

/* Line 1455 of yacc.c  */
#line 6426 "parser.y"
    { terminator_clear (TERM_WRITE); ;}
    break;

  case 1239:

/* Line 1455 of yacc.c  */
#line 6441 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_ACCEPT;
  ;}
    break;

  case 1240:

/* Line 1455 of yacc.c  */
#line 6449 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_DISPLAY;
  ;}
    break;

  case 1242:

/* Line 1455 of yacc.c  */
#line 6456 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1243:

/* Line 1455 of yacc.c  */
#line 6460 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1245:

/* Line 1455 of yacc.c  */
#line 6467 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1246:

/* Line 1455 of yacc.c  */
#line 6471 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1249:

/* Line 1455 of yacc.c  */
#line 6487 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1250:

/* Line 1455 of yacc.c  */
#line 6492 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1252:

/* Line 1455 of yacc.c  */
#line 6499 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1253:

/* Line 1455 of yacc.c  */
#line 6504 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1254:

/* Line 1455 of yacc.c  */
#line 6516 "parser.y"
    {
	current_statement->handler_id = COB_EC_OVERFLOW;
  ;}
    break;

  case 1256:

/* Line 1455 of yacc.c  */
#line 6523 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1257:

/* Line 1455 of yacc.c  */
#line 6527 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1259:

/* Line 1455 of yacc.c  */
#line 6534 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1260:

/* Line 1455 of yacc.c  */
#line 6538 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1261:

/* Line 1455 of yacc.c  */
#line 6550 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1262:

/* Line 1455 of yacc.c  */
#line 6555 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1263:

/* Line 1455 of yacc.c  */
#line 6560 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1264:

/* Line 1455 of yacc.c  */
#line 6569 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1265:

/* Line 1455 of yacc.c  */
#line 6573 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1266:

/* Line 1455 of yacc.c  */
#line 6580 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1267:

/* Line 1455 of yacc.c  */
#line 6584 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1268:

/* Line 1455 of yacc.c  */
#line 6596 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1269:

/* Line 1455 of yacc.c  */
#line 6601 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1270:

/* Line 1455 of yacc.c  */
#line 6606 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1271:

/* Line 1455 of yacc.c  */
#line 6615 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1272:

/* Line 1455 of yacc.c  */
#line 6619 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1273:

/* Line 1455 of yacc.c  */
#line 6626 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1274:

/* Line 1455 of yacc.c  */
#line 6630 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1277:

/* Line 1455 of yacc.c  */
#line 6646 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1278:

/* Line 1455 of yacc.c  */
#line 6651 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1279:

/* Line 1455 of yacc.c  */
#line 6656 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1280:

/* Line 1455 of yacc.c  */
#line 6665 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1281:

/* Line 1455 of yacc.c  */
#line 6669 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1282:

/* Line 1455 of yacc.c  */
#line 6676 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1283:

/* Line 1455 of yacc.c  */
#line 6680 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1284:

/* Line 1455 of yacc.c  */
#line 6692 "parser.y"
    {
	(yyval) = cb_one;
  ;}
    break;

  case 1285:

/* Line 1455 of yacc.c  */
#line 6696 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 1286:

/* Line 1455 of yacc.c  */
#line 6708 "parser.y"
    {
	(yyval) = cb_build_cond ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1287:

/* Line 1455 of yacc.c  */
#line 6715 "parser.y"
    {
	(yyval) = cb_build_expr ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1288:

/* Line 1455 of yacc.c  */
#line 6721 "parser.y"
    {
	current_expr = NULL;
  ;}
    break;

  case 1289:

/* Line 1455 of yacc.c  */
#line 6725 "parser.y"
    {
	(yyval) = cb_list_reverse (current_expr);
  ;}
    break;

  case 1290:

/* Line 1455 of yacc.c  */
#line 6731 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1291:

/* Line 1455 of yacc.c  */
#line 6732 "parser.y"
    { push_expr (')', NULL); ;}
    break;

  case 1292:

/* Line 1455 of yacc.c  */
#line 6734 "parser.y"
    { push_expr ('O', NULL); ;}
    break;

  case 1293:

/* Line 1455 of yacc.c  */
#line 6735 "parser.y"
    { push_expr ('9', NULL); ;}
    break;

  case 1294:

/* Line 1455 of yacc.c  */
#line 6736 "parser.y"
    { push_expr ('A', NULL); ;}
    break;

  case 1295:

/* Line 1455 of yacc.c  */
#line 6737 "parser.y"
    { push_expr ('L', NULL); ;}
    break;

  case 1296:

/* Line 1455 of yacc.c  */
#line 6738 "parser.y"
    { push_expr ('U', NULL); ;}
    break;

  case 1297:

/* Line 1455 of yacc.c  */
#line 6739 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1298:

/* Line 1455 of yacc.c  */
#line 6741 "parser.y"
    { push_expr ('O', NULL); ;}
    break;

  case 1299:

/* Line 1455 of yacc.c  */
#line 6742 "parser.y"
    { push_expr ('9', NULL); ;}
    break;

  case 1300:

/* Line 1455 of yacc.c  */
#line 6743 "parser.y"
    { push_expr ('A', NULL); ;}
    break;

  case 1301:

/* Line 1455 of yacc.c  */
#line 6744 "parser.y"
    { push_expr ('L', NULL); ;}
    break;

  case 1302:

/* Line 1455 of yacc.c  */
#line 6745 "parser.y"
    { push_expr ('U', NULL); ;}
    break;

  case 1303:

/* Line 1455 of yacc.c  */
#line 6746 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1304:

/* Line 1455 of yacc.c  */
#line 6748 "parser.y"
    { push_expr ('P', NULL); ;}
    break;

  case 1305:

/* Line 1455 of yacc.c  */
#line 6749 "parser.y"
    { push_expr ('N', NULL); ;}
    break;

  case 1306:

/* Line 1455 of yacc.c  */
#line 6751 "parser.y"
    { push_expr ('P', NULL); ;}
    break;

  case 1307:

/* Line 1455 of yacc.c  */
#line 6752 "parser.y"
    { push_expr ('N', NULL); ;}
    break;

  case 1308:

/* Line 1455 of yacc.c  */
#line 6753 "parser.y"
    { push_expr ('x', cb_zero); ;}
    break;

  case 1312:

/* Line 1455 of yacc.c  */
#line 6760 "parser.y"
    { push_expr ('(', NULL); ;}
    break;

  case 1313:

/* Line 1455 of yacc.c  */
#line 6762 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1314:

/* Line 1455 of yacc.c  */
#line 6763 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1315:

/* Line 1455 of yacc.c  */
#line 6764 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1316:

/* Line 1455 of yacc.c  */
#line 6766 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1317:

/* Line 1455 of yacc.c  */
#line 6767 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1318:

/* Line 1455 of yacc.c  */
#line 6769 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1319:

/* Line 1455 of yacc.c  */
#line 6770 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1320:

/* Line 1455 of yacc.c  */
#line 6771 "parser.y"
    { push_expr ('*', NULL); ;}
    break;

  case 1321:

/* Line 1455 of yacc.c  */
#line 6772 "parser.y"
    { push_expr ('/', NULL); ;}
    break;

  case 1322:

/* Line 1455 of yacc.c  */
#line 6773 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1323:

/* Line 1455 of yacc.c  */
#line 6775 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1324:

/* Line 1455 of yacc.c  */
#line 6776 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1325:

/* Line 1455 of yacc.c  */
#line 6777 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1326:

/* Line 1455 of yacc.c  */
#line 6778 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1327:

/* Line 1455 of yacc.c  */
#line 6779 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1328:

/* Line 1455 of yacc.c  */
#line 6780 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1329:

/* Line 1455 of yacc.c  */
#line 6782 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1330:

/* Line 1455 of yacc.c  */
#line 6783 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1331:

/* Line 1455 of yacc.c  */
#line 6784 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1332:

/* Line 1455 of yacc.c  */
#line 6785 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1333:

/* Line 1455 of yacc.c  */
#line 6786 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1334:

/* Line 1455 of yacc.c  */
#line 6787 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1335:

/* Line 1455 of yacc.c  */
#line 6789 "parser.y"
    { push_expr ('&', NULL); ;}
    break;

  case 1336:

/* Line 1455 of yacc.c  */
#line 6790 "parser.y"
    { push_expr ('|', NULL); ;}
    break;

  case 1350:

/* Line 1455 of yacc.c  */
#line 6802 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1351:

/* Line 1455 of yacc.c  */
#line 6803 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1355:

/* Line 1455 of yacc.c  */
#line 6812 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1356:

/* Line 1455 of yacc.c  */
#line 6813 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '+', (yyvsp[(3) - (3)])); ;}
    break;

  case 1357:

/* Line 1455 of yacc.c  */
#line 6814 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '-', (yyvsp[(3) - (3)])); ;}
    break;

  case 1358:

/* Line 1455 of yacc.c  */
#line 6815 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '*', (yyvsp[(3) - (3)])); ;}
    break;

  case 1359:

/* Line 1455 of yacc.c  */
#line 6816 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '/', (yyvsp[(3) - (3)])); ;}
    break;

  case 1360:

/* Line 1455 of yacc.c  */
#line 6817 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1361:

/* Line 1455 of yacc.c  */
#line 6818 "parser.y"
    { (yyval) = cb_build_binary_op (cb_zero, '-', (yyvsp[(2) - (2)])); ;}
    break;

  case 1362:

/* Line 1455 of yacc.c  */
#line 6819 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '^', (yyvsp[(3) - (3)])); ;}
    break;

  case 1363:

/* Line 1455 of yacc.c  */
#line 6820 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1364:

/* Line 1455 of yacc.c  */
#line 6832 "parser.y"
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

  case 1365:

/* Line 1455 of yacc.c  */
#line 6844 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(3) - (3)])))) {
		(yyval) = CB_FILE (cb_ref ((yyvsp[(3) - (3)])))->linage_ctr;
	} else {
		cb_error_x ((yyvsp[(3) - (3)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(3) - (3)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1366:

/* Line 1455 of yacc.c  */
#line 6858 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1367:

/* Line 1455 of yacc.c  */
#line 6860 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1368:

/* Line 1455 of yacc.c  */
#line 6864 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)])); ;}
    break;

  case 1369:

/* Line 1455 of yacc.c  */
#line 6871 "parser.y"
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

  case 1370:

/* Line 1455 of yacc.c  */
#line 6893 "parser.y"
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

  case 1371:

/* Line 1455 of yacc.c  */
#line 6913 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1372:

/* Line 1455 of yacc.c  */
#line 6917 "parser.y"
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

  case 1373:

/* Line 1455 of yacc.c  */
#line 6933 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (1)])))) {
		(yyval) = (yyvsp[(1) - (1)]);
	} else {
		cb_error_x ((yyvsp[(1) - (1)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(1) - (1)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1374:

/* Line 1455 of yacc.c  */
#line 6946 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1375:

/* Line 1455 of yacc.c  */
#line 6948 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1376:

/* Line 1455 of yacc.c  */
#line 6952 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1377:

/* Line 1455 of yacc.c  */
#line 6958 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1378:

/* Line 1455 of yacc.c  */
#line 6960 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1379:

/* Line 1455 of yacc.c  */
#line 6965 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	CB_REFERENCE ((yyval))->offset = CB_TREE (current_section);
	current_program->label_list = cb_cons ((yyval), current_program->label_list);
  ;}
    break;

  case 1383:

/* Line 1455 of yacc.c  */
#line 6980 "parser.y"
    {
	(yyval) = cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(1) - (1)]))->data));
	(yyval)->source_file = (yyvsp[(1) - (1)])->source_file;
	(yyval)->source_line = (yyvsp[(1) - (1)])->source_line;
  ;}
    break;

  case 1384:

/* Line 1455 of yacc.c  */
#line 6990 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1385:

/* Line 1455 of yacc.c  */
#line 6991 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1386:

/* Line 1455 of yacc.c  */
#line 6996 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	current_program->reference_list = cb_cons ((yyval), current_program->reference_list);
  ;}
    break;

  case 1387:

/* Line 1455 of yacc.c  */
#line 7005 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1388:

/* Line 1455 of yacc.c  */
#line 7006 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1389:

/* Line 1455 of yacc.c  */
#line 7010 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1390:

/* Line 1455 of yacc.c  */
#line 7011 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1393:

/* Line 1455 of yacc.c  */
#line 7023 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE ((yyval))->word->count > 0) {
		redefinition_error ((yyval));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1394:

/* Line 1455 of yacc.c  */
#line 7042 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1395:

/* Line 1455 of yacc.c  */
#line 7043 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1397:

/* Line 1455 of yacc.c  */
#line 7048 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1398:

/* Line 1455 of yacc.c  */
#line 7052 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1399:

/* Line 1455 of yacc.c  */
#line 7053 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1401:

/* Line 1455 of yacc.c  */
#line 7058 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1402:

/* Line 1455 of yacc.c  */
#line 7059 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1403:

/* Line 1455 of yacc.c  */
#line 7060 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1404:

/* Line 1455 of yacc.c  */
#line 7061 "parser.y"
    { (yyval) = cb_build_ppointer ((yyvsp[(4) - (4)])); ;}
    break;

  case 1405:

/* Line 1455 of yacc.c  */
#line 7062 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1410:

/* Line 1455 of yacc.c  */
#line 7070 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1411:

/* Line 1455 of yacc.c  */
#line 7071 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1412:

/* Line 1455 of yacc.c  */
#line 7072 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1418:

/* Line 1455 of yacc.c  */
#line 7084 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1419:

/* Line 1455 of yacc.c  */
#line 7085 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1431:

/* Line 1455 of yacc.c  */
#line 7119 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1432:

/* Line 1455 of yacc.c  */
#line 7127 "parser.y"
    { (yyval) = cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1433:

/* Line 1455 of yacc.c  */
#line 7131 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1434:

/* Line 1455 of yacc.c  */
#line 7132 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1435:

/* Line 1455 of yacc.c  */
#line 7133 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1436:

/* Line 1455 of yacc.c  */
#line 7134 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 1437:

/* Line 1455 of yacc.c  */
#line 7138 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1438:

/* Line 1455 of yacc.c  */
#line 7139 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); CB_REFERENCE ((yyvsp[(1) - (3)]))->chain = (yyvsp[(3) - (3)]); ;}
    break;

  case 1439:

/* Line 1455 of yacc.c  */
#line 7144 "parser.y"
    {
	if (cb_ref ((yyvsp[(0) - (3)])) != cb_error_node) {
		(yyval) = (yyvsp[(0) - (3)]);
		CB_REFERENCE ((yyvsp[(0) - (3)]))->subs = cb_list_reverse ((yyvsp[(2) - (3)]));
	}
  ;}
    break;

  case 1440:

/* Line 1455 of yacc.c  */
#line 7154 "parser.y"
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

  case 1441:

/* Line 1455 of yacc.c  */
#line 7172 "parser.y"
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

  case 1442:

/* Line 1455 of yacc.c  */
#line 7199 "parser.y"
    {
	if (cb_tree_category ((yyvsp[(1) - (1)])) != CB_CATEGORY_NUMERIC) {
		cb_error (_("Integer value expected"));
	} else if (CB_LITERAL ((yyvsp[(1) - (1)]))->sign < 0 || CB_LITERAL ((yyvsp[(1) - (1)]))->scale) {
		cb_error (_("Integer value expected"));
	}
	(yyval) = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1443:

/* Line 1455 of yacc.c  */
#line 7210 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1444:

/* Line 1455 of yacc.c  */
#line 7212 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (2)]);
	if (CB_LITERAL_P ((yyvsp[(2) - (2)]))) {
		CB_LITERAL ((yyvsp[(2) - (2)]))->all = 1;
	}
  ;}
    break;

  case 1445:

/* Line 1455 of yacc.c  */
#line 7221 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1446:

/* Line 1455 of yacc.c  */
#line 7222 "parser.y"
    { (yyval) = cb_concat_literals ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1447:

/* Line 1455 of yacc.c  */
#line 7226 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1448:

/* Line 1455 of yacc.c  */
#line 7227 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 1449:

/* Line 1455 of yacc.c  */
#line 7228 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1450:

/* Line 1455 of yacc.c  */
#line 7229 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 1451:

/* Line 1455 of yacc.c  */
#line 7230 "parser.y"
    { (yyval) = cb_high; ;}
    break;

  case 1452:

/* Line 1455 of yacc.c  */
#line 7231 "parser.y"
    { (yyval) = cb_low; ;}
    break;

  case 1453:

/* Line 1455 of yacc.c  */
#line 7232 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1454:

/* Line 1455 of yacc.c  */
#line 7241 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1455:

/* Line 1455 of yacc.c  */
#line 7245 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1456:

/* Line 1455 of yacc.c  */
#line 7249 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1457:

/* Line 1455 of yacc.c  */
#line 7253 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1458:

/* Line 1455 of yacc.c  */
#line 7257 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1459:

/* Line 1455 of yacc.c  */
#line 7261 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1460:

/* Line 1455 of yacc.c  */
#line 7265 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1461:

/* Line 1455 of yacc.c  */
#line 7269 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1462:

/* Line 1455 of yacc.c  */
#line 7273 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1463:

/* Line 1455 of yacc.c  */
#line 7277 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), NULL);
  ;}
    break;

  case 1464:

/* Line 1455 of yacc.c  */
#line 7281 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1465:

/* Line 1455 of yacc.c  */
#line 7285 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), NULL);
  ;}
    break;

  case 1466:

/* Line 1455 of yacc.c  */
#line 7291 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1467:

/* Line 1455 of yacc.c  */
#line 7292 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (4)]), NULL); ;}
    break;

  case 1468:

/* Line 1455 of yacc.c  */
#line 7293 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 1469:

/* Line 1455 of yacc.c  */
#line 7297 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1470:

/* Line 1455 of yacc.c  */
#line 7298 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1471:

/* Line 1455 of yacc.c  */
#line 7302 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1472:

/* Line 1455 of yacc.c  */
#line 7303 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1473:

/* Line 1455 of yacc.c  */
#line 7309 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_int0);
  ;}
    break;

  case 1474:

/* Line 1455 of yacc.c  */
#line 7316 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int1);
  ;}
    break;

  case 1475:

/* Line 1455 of yacc.c  */
#line 7323 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int2);
  ;}
    break;

  case 1476:

/* Line 1455 of yacc.c  */
#line 7333 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1477:

/* Line 1455 of yacc.c  */
#line 7340 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1478:

/* Line 1455 of yacc.c  */
#line 7350 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1479:

/* Line 1455 of yacc.c  */
#line 7357 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_ref ((yyvsp[(3) - (3)])));
  ;}
    break;

  case 1480:

/* Line 1455 of yacc.c  */
#line 7370 "parser.y"
    {
	non_const_word = 1;
  ;}
    break;

  case 1481:

/* Line 1455 of yacc.c  */
#line 7380 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1482:

/* Line 1455 of yacc.c  */
#line 7381 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1483:

/* Line 1455 of yacc.c  */
#line 7385 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1484:

/* Line 1455 of yacc.c  */
#line 7386 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1485:

/* Line 1455 of yacc.c  */
#line 7390 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1486:

/* Line 1455 of yacc.c  */
#line 7391 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1487:

/* Line 1455 of yacc.c  */
#line 7395 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1488:

/* Line 1455 of yacc.c  */
#line 7396 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1489:

/* Line 1455 of yacc.c  */
#line 7397 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 1490:

/* Line 1455 of yacc.c  */
#line 7401 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1491:

/* Line 1455 of yacc.c  */
#line 7402 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1492:

/* Line 1455 of yacc.c  */
#line 7406 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1493:

/* Line 1455 of yacc.c  */
#line 7407 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1494:

/* Line 1455 of yacc.c  */
#line 7411 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1495:

/* Line 1455 of yacc.c  */
#line 7412 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1496:

/* Line 1455 of yacc.c  */
#line 7416 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1497:

/* Line 1455 of yacc.c  */
#line 7417 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1509:

/* Line 1455 of yacc.c  */
#line 7430 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1538:

/* Line 1455 of yacc.c  */
#line 7445 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1539:

/* Line 1455 of yacc.c  */
#line 7445 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1550:

/* Line 1455 of yacc.c  */
#line 7450 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1551:

/* Line 1455 of yacc.c  */
#line 7450 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;



/* Line 1455 of yacc.c  */
#line 14913 "parser.c"
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
#line 7475 "parser.y"


