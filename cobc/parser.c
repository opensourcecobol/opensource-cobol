
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
#define YYLAST   5949

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  463
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  712
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1596
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2350

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
    3160,  3163,  3164,  3166,  3167,  3172,  3173,  3177,  3178,  3181,
    3184,  3185,  3194,  3196,  3199,  3201,  3205,  3209,  3210,  3214,
    3215,  3217,  3218,  3223,  3228,  3235,  3242,  3243,  3245,  3248,
    3249,  3251,  3252,  3256,  3257,  3265,  3266,  3271,  3272,  3274,
    3276,  3277,  3287,  3288,  3292,  3294,  3298,  3301,  3304,  3307,
    3311,  3312,  3316,  3317,  3321,  3322,  3326,  3327,  3329,  3331,
    3333,  3335,  3344,  3345,  3347,  3349,  3351,  3353,  3355,  3357,
    3358,  3360,  3361,  3363,  3365,  3367,  3369,  3371,  3373,  3375,
    3376,  3378,  3384,  3386,  3389,  3395,  3396,  3405,  3406,  3409,
    3410,  3415,  3419,  3423,  3425,  3427,  3428,  3430,  3432,  3433,
    3435,  3438,  3441,  3442,  3443,  3447,  3448,  3449,  3453,  3456,
    3457,  3458,  3462,  3463,  3464,  3468,  3471,  3472,  3473,  3477,
    3478,  3479,  3483,  3485,  3487,  3490,  3491,  3495,  3496,  3500,
    3502,  3504,  3507,  3508,  3512,  3513,  3517,  3518,  3520,  3522,
    3524,  3527,  3528,  3532,  3533,  3537,  3538,  3542,  3544,  3546,
    3547,  3550,  3553,  3556,  3559,  3562,  3565,  3568,  3571,  3574,
    3577,  3580,  3583,  3586,  3589,  3592,  3595,  3598,  3601,  3604,
    3607,  3608,  3611,  3614,  3617,  3620,  3623,  3626,  3629,  3632,
    3635,  3638,  3641,  3644,  3647,  3650,  3653,  3656,  3659,  3662,
    3665,  3668,  3671,  3674,  3677,  3680,  3683,  3686,  3689,  3691,
    3694,  3696,  3698,  3701,  3703,  3706,  3708,  3714,  3719,  3721,
    3727,  3732,  3734,  3738,  3739,  3741,  3743,  3745,  3749,  3753,
    3757,  3761,  3764,  3767,  3771,  3775,  3777,  3781,  3783,  3786,
    3789,  3791,  3793,  3795,  3798,  3800,  3802,  3805,  3807,  3808,
    3811,  3813,  3815,  3817,  3821,  3823,  3825,  3828,  3830,  3832,
    3835,  3836,  3838,  3840,  3842,  3844,  3846,  3849,  3851,  3855,
    3857,  3860,  3862,  3866,  3870,  3874,  3879,  3883,  3885,  3887,
    3889,  3891,  3895,  3899,  3903,  3905,  3907,  3909,  3911,  3913,
    3915,  3917,  3919,  3921,  3923,  3925,  3927,  3929,  3931,  3933,
    3935,  3937,  3939,  3941,  3943,  3945,  3948,  3951,  3955,  3957,
    3961,  3965,  3970,  3976,  3978,  3980,  3983,  3985,  3989,  3991,
    3993,  3995,  3997,  3999,  4001,  4003,  4006,  4009,  4015,  4021,
    4027,  4033,  4039,  4045,  4051,  4056,  4062,  4065,  4066,  4071,
    4077,  4078,  4082,  4083,  4085,  4087,  4091,  4095,  4097,  4101,
    4103,  4107,  4108,  4109,  4111,  4112,  4114,  4115,  4117,  4118,
    4120,  4122,  4123,  4125,  4126,  4128,  4129,  4131,  4132,  4135,
    4137,  4139,  4142,  4145,  4148,  4150,  4153,  4155,  4156,  4158,
    4159,  4161,  4162,  4164,  4165,  4167,  4168,  4170,  4171,  4173,
    4174,  4176,  4177,  4179,  4180,  4182,  4183,  4185,  4186,  4188,
    4189,  4191,  4192,  4194,  4195,  4197,  4198,  4200,  4201,  4203,
    4204,  4206,  4207,  4209,  4211,  4212,  4214,  4215,  4217,  4219,
    4220,  4222,  4223,  4225,  4226,  4228,  4229,  4231,  4232,  4234,
    4235,  4237,  4238,  4240,  4243,  4244,  4246,  4247,  4249,  4250,
    4252,  4253,  4255,  4256,  4258,  4259,  4261,  4262,  4264,  4267,
    4268,  4270,  4271,  4273,  4274,  4276,  4277,  4279,  4280,  4282,
    4283,  4285,  4286,  4288,  4289,  4291,  4292
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
      -1,    -1,  1148,   487,  1160,    -1,    73,    -1,    73,   488,
      -1,   488,    -1,   406,    -1,   322,    -1,    -1,   150,   120,
     455,   490,   544,    -1,    -1,    83,   356,   455,   491,    -1,
      -1,   491,   492,    -1,   493,    -1,   497,    -1,   510,    -1,
     505,    -1,   377,   455,   494,    -1,    -1,   496,   455,    -1,
     496,   495,   455,    -1,   495,   455,    -1,  1174,   107,   249,
      -1,   442,    -1,   275,   455,   498,    -1,    -1,   496,   455,
      -1,   496,   499,   455,    -1,   499,   455,    -1,   500,    -1,
     499,   500,    -1,   501,    -1,   503,    -1,   504,    -1,   245,
     372,  1148,  1108,   502,    -1,    56,    -1,   443,    -1,  1160,
    1131,  1148,  1086,    -1,   358,  1148,  1108,    -1,   337,   455,
     506,    -1,    -1,   507,   455,    -1,   508,    -1,   507,   508,
      -1,   182,   509,   211,    -1,   182,     9,   211,    -1,   236,
      -1,   509,   236,    -1,   379,   455,   511,    -1,    -1,   512,
      -1,   512,   455,    -1,   513,    -1,   512,   513,    -1,   514,
      -1,   521,    -1,   530,    -1,   537,    -1,   534,    -1,   538,
      -1,   539,    -1,   540,    -1,   541,    -1,   542,    -1,   543,
      -1,   442,  1148,    96,    -1,    -1,   442,  1148,  1090,   515,
     517,    -1,    -1,   442,  1148,   516,   518,    -1,    25,  1148,
    1090,    -1,    26,  1148,  1090,    -1,   151,  1148,  1090,    -1,
     152,  1148,  1090,    -1,    -1,   517,   519,    -1,   519,    -1,
     518,   519,    -1,   520,  1167,  1148,  1090,    -1,   280,    -1,
     278,    -1,    -1,    11,  1090,   522,  1148,   523,    -1,   255,
      -1,   381,    -1,   382,    -1,   124,    -1,   524,    -1,   525,
      -1,   524,   525,    -1,   528,    -1,   528,   400,   528,    -1,
      -1,   528,    17,   526,   527,    -1,   529,    -1,   527,    17,
     529,    -1,   236,    -1,   378,    -1,   448,    -1,   315,    -1,
     195,    -1,   243,    -1,   236,    -1,   378,    -1,   448,    -1,
     315,    -1,   195,    -1,   243,    -1,   392,  1141,   531,    -1,
     532,  1149,   533,    -1,  1090,    -1,   532,  1090,    -1,  1108,
      -1,   533,  1108,    -1,    57,  1090,  1148,   535,    -1,   536,
      -1,   535,   536,    -1,  1111,    -1,  1111,   400,  1111,    -1,
     237,  1090,  1148,  1086,    -1,    97,  1164,  1148,   236,    -1,
     108,  1148,    68,    -1,    99,  1148,  1086,    -1,    96,   384,
    1148,  1086,    -1,   352,  1148,  1086,    -1,   162,  1148,  1086,
      -1,    -1,   208,   356,   455,   547,   582,    -1,    -1,   169,
     455,   545,   548,    -1,    -1,   216,   455,   546,   583,    -1,
      -1,   169,   455,   548,    -1,    -1,   548,   549,    -1,    -1,
     359,  1125,  1090,   550,   551,   455,    -1,    -1,   551,   552,
      -1,   553,    -1,   558,    -1,   560,    -1,   565,    -1,   566,
      -1,   568,    -1,   572,    -1,   574,    -1,   575,    -1,   576,
      -1,   577,    -1,   578,    -1,   579,    -1,     1,    -1,   581,
      -1,    29,  1172,   555,   554,   556,    -1,    29,  1172,   555,
     117,    -1,    29,  1172,   555,   305,    -1,    -1,   117,    -1,
     305,    -1,    -1,   167,    -1,   123,    -1,   236,    -1,   118,
      -1,  1153,   557,    -1,  1105,    -1,   557,  1105,    -1,     4,
    1154,  1148,   559,    -1,   364,    -1,   123,    -1,   316,    -1,
      19,   319,  1150,  1148,  1086,  1121,    -1,    19,   319,  1150,
    1148,  1086,   564,   561,  1121,    -1,    -1,   562,   563,    -1,
     561,   563,    -1,  1086,    -1,    -1,   376,  1148,    -1,   456,
      -1,  1131,  1148,   442,    -1,   567,   384,  1148,  1086,  1088,
      -1,    -1,   405,    -1,   374,    -1,   240,  1154,  1148,   569,
      -1,   244,   570,    -1,    32,   570,    -1,   164,    -1,    -1,
     441,   240,   280,   571,    -1,   441,   240,   280,   251,   571,
      -1,   441,   347,    -1,   319,    -1,   321,    -1,   286,  1148,
     573,    -1,   573,    -1,   202,    -1,   319,  1138,   364,    -1,
     364,    -1,   326,    -1,   233,   364,    -1,   292,  1140,  1148,
    1089,    -1,   319,   113,  1148,   381,    -1,   319,  1150,  1148,
    1086,    -1,   319,  1150,  1148,  1086,   564,   561,    -1,   326,
    1150,  1148,  1086,    -1,   339,  1108,  1135,    -1,   339,   260,
      -1,   366,  1174,   580,    -1,     9,  1159,    -1,   260,  1159,
      -1,   318,   281,    -1,   261,  1150,  1148,  1086,    -1,    -1,
     216,   455,   583,    -1,    -1,   584,   455,    -1,   584,    -1,
     592,    -1,   585,    -1,   584,   585,    -1,   586,    -1,   588,
      -1,   350,   587,  1135,  1145,  1077,    -1,    -1,   319,    -1,
     374,    -1,   375,    -1,   251,  1144,  1168,  1142,   589,    -1,
     590,    -1,   589,   590,    -1,  1078,   591,    -1,    -1,   301,
    1108,    -1,   592,   455,    -1,   593,    -1,   592,   593,    -1,
      22,    72,  1157,  1085,    -1,    22,   101,  1156,   236,   410,
     280,  1085,    -1,    22,    93,   403,  1086,   280,  1085,    -1,
      22,   178,   403,  1086,   280,  1085,    -1,    22,    60,   280,
    1085,    -1,    -1,   102,   120,   455,   595,   626,   679,   681,
     683,   724,    -1,    -1,    -1,   405,   356,   455,   596,   598,
      -1,    -1,   601,   597,   600,    -1,    -1,   598,   599,    -1,
     601,   602,   628,    -1,   602,   628,    -1,   600,   599,    -1,
     168,    -1,   354,    -1,    -1,  1078,   603,   604,   455,    -1,
      -1,   604,   605,    -1,  1148,   167,    -1,  1148,   188,    -1,
     606,    -1,   608,    -1,   612,    -1,   614,    -1,   616,    -1,
     617,    -1,   623,    -1,   624,    -1,   625,    -1,     1,    -1,
      47,  1142,  1108,   611,   607,    -1,    -1,   321,    -1,    56,
      -1,   319,  1142,  1108,  1141,    -1,   319,  1142,  1108,   403,
    1108,  1141,    -1,   319,  1148,   436,  1147,  1166,   610,   611,
    1141,   609,    -1,    -1,   114,  1157,  1086,    -1,    -1,  1146,
    1108,    -1,    -1,   403,  1108,    -1,   219,  1129,   613,    -1,
     380,    -1,   279,    -1,   435,   277,   442,  1148,   615,    -1,
     435,   277,   170,  1148,   615,    -1,   236,    -1,  1105,    -1,
     102,  1129,  1087,    -1,   231,  1148,  1089,  1152,   618,    -1,
      -1,   618,   619,    -1,   620,    -1,   621,    -1,   622,    -1,
    1174,   174,  1137,  1089,  1152,    -1,  1137,   409,  1089,  1152,
      -1,  1137,    48,  1089,    -1,   320,  1154,  1148,   442,    -1,
      62,  1148,   442,    -1,   332,  1148,   723,    -1,   334,  1134,
     723,    -1,    -1,    -1,   444,   356,   455,   627,   628,    -1,
      -1,   629,    -1,    -1,   630,   631,    -1,  1119,   632,    -1,
     631,  1119,   632,    -1,   631,   455,    -1,   642,    -1,    -1,
     635,   638,   633,   643,   637,    -1,    -1,   636,   638,   634,
     672,    -1,   227,    -1,   228,    -1,    -1,   236,    -1,    -1,
     171,    -1,   442,    -1,   442,    -1,    -1,  1148,   188,    -1,
    1109,    -1,   225,  1156,  1104,    -1,    50,  1156,  1104,    -1,
     635,   639,    84,   640,  1136,   641,    -1,    -1,   643,   644,
      -1,   645,    -1,   646,    -1,   648,    -1,   649,    -1,   650,
      -1,   652,    -1,   654,    -1,   666,    -1,   667,    -1,   669,
      -1,   670,    -1,   671,    -1,   677,    -1,   678,    -1,     1,
      -1,   323,  1104,    -1,  1148,   167,   647,    -1,    -1,    27,
     236,    -1,  1148,   188,    -1,   298,    -1,   651,    -1,   432,
    1148,   651,    -1,    37,    -1,    74,    -1,    76,    -1,    77,
      -1,    78,    -1,    79,    -1,    80,    -1,    81,    -1,   118,
      -1,   201,    -1,   291,    -1,   300,    -1,   313,    -1,   371,
      -1,   369,    -1,   370,    -1,   421,    -1,   419,    -1,   420,
      -1,    39,   368,    -1,    39,   418,    -1,    39,    -1,    42,
     368,    -1,    42,   418,    -1,    42,    -1,    41,   368,    -1,
      41,   418,    -1,    41,    -1,    40,   368,    -1,    40,   418,
      -1,    40,    -1,    38,   368,    -1,    38,   418,    -1,    38,
      -1,   253,    -1,  1165,   223,  1127,    -1,  1165,   411,  1127,
      -1,    -1,   658,   662,    -1,   663,   657,    -1,   276,  1108,
     655,  1171,   656,   653,    -1,    -1,   403,  1108,    -1,    -1,
     114,  1157,  1086,    -1,    -1,   658,    -1,   660,    -1,   661,
    1150,  1148,  1085,    -1,   659,    -1,   660,   659,    -1,    28,
      -1,   115,    -1,    -1,   663,    -1,   202,  1139,   664,    -1,
     665,    -1,   664,   665,    -1,   442,    -1,   217,  1162,    -1,
     393,   668,    -1,    -1,   224,    -1,   346,    -1,    43,  1173,
     448,    -1,    34,    -1,   435,  1148,  1109,    -1,    -1,   435,
    1149,   674,   673,  1173,  1163,  1172,   676,    -1,   675,    -1,
     674,   675,    -1,  1109,    -1,  1109,   400,  1109,    -1,    -1,
     404,  1148,  1109,    -1,   330,  1105,    -1,   330,  1105,   400,
    1105,    -1,    21,   225,    -1,    -1,    -1,   239,   356,   455,
     680,   628,    -1,    -1,    -1,   235,   356,   455,   682,   628,
      -1,    -1,    -1,   332,   356,   455,   684,   685,    -1,    -1,
     686,    -1,   687,    -1,   686,   687,    -1,   317,   723,   688,
     455,   702,    -1,    -1,   688,   689,    -1,  1148,   188,    -1,
      61,  1148,  1100,    -1,   690,    -1,   694,    -1,    88,   691,
      -1,    89,   691,    -1,   692,   693,    -1,    -1,   172,    -1,
    1103,    -1,   693,  1103,    -1,   293,  1149,   700,   695,   696,
     697,   698,   699,    -1,    -1,   193,  1148,  1108,    -1,    -1,
     173,   116,  1148,  1108,    -1,    -1,   220,    91,  1148,  1108,
      -1,    -1,   221,  1148,  1108,    -1,    -1,   174,  1148,  1108,
      -1,  1108,    -1,  1108,   701,  1108,    67,    -1,  1108,   701,
      -1,   233,    -1,   234,    -1,    -1,   702,   703,    -1,   635,
     638,   704,   455,    -1,    -1,   704,   705,    -1,   706,    -1,
     708,    -1,   715,    -1,   649,    -1,   650,    -1,   652,    -1,
     666,    -1,   709,    -1,   669,    -1,   720,    -1,   710,    -1,
     671,    -1,   713,    -1,   721,    -1,   654,    -1,   714,    -1,
     414,  1148,   707,    -1,   336,    -1,   295,    -1,    91,    -1,
     116,    -1,    90,    -1,   294,    -1,   335,    -1,   258,   192,
    1148,  1108,    -1,    66,  1155,  1148,  1108,    -1,    66,   271,
      -1,    67,    -1,   711,    -1,   710,   711,    -1,   390,  1156,
     712,    -1,  1086,    -1,   303,   438,  1058,    -1,   436,  1103,
     180,  1094,    49,  1094,    -1,   716,   717,    -1,   233,   719,
    1149,    -1,   234,  1134,    -1,   718,    -1,   717,   718,    -1,
     299,  1108,    -1,  1108,    -1,   258,   293,    -1,    -1,   270,
      -1,   271,    -1,   376,  1148,  1103,  1126,    -1,   192,   722,
      -1,    -1,   203,    -1,   442,    -1,    -1,    -1,    -1,   351,
     356,   455,   725,   726,   727,    -1,    -1,   728,    -1,   729,
      -1,   728,   729,    -1,   642,    -1,    -1,   635,   638,   730,
     731,   455,    -1,    -1,   731,   732,    -1,    44,    -1,    45,
      -1,    36,    -1,    46,    -1,   158,   153,    -1,   158,   155,
      -1,   194,    -1,   242,    -1,   343,    -1,   415,    -1,   290,
      -1,    31,    -1,   357,    -1,   338,    -1,   181,    -1,   314,
      -1,   233,  1155,  1148,   733,  1102,    -1,    66,  1155,  1148,
     734,  1102,    -1,   176,  1148,  1102,    -1,    33,  1148,  1102,
      -1,   650,    -1,   669,    -1,   666,    -1,   652,    -1,   671,
      -1,   649,    -1,   735,    -1,   434,  1103,    -1,   180,  1101,
      -1,   403,  1103,    -1,    -1,   299,    -1,   449,    -1,   247,
      -1,   450,    -1,    -1,   299,    -1,   449,    -1,   247,    -1,
     450,    -1,   276,  1108,  1171,    -1,    -1,    -1,    -1,   307,
     120,   739,   747,   455,   737,   748,   738,   750,    -1,    -1,
      -1,   434,   740,   742,    -1,    -1,    54,   741,   742,    -1,
     743,    -1,   742,   743,    -1,   744,   745,   746,   442,    -1,
      -1,  1139,   325,    -1,  1139,   435,    -1,    -1,   372,  1148,
      31,    -1,   372,  1148,   110,    -1,   418,   372,  1148,  1108,
      -1,   372,  1148,  1108,    -1,    -1,   283,    -1,    -1,   341,
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
     971,    -1,   975,    -1,   981,    -1,   985,    -1,   987,    -1,
     989,    -1,   991,    -1,   994,    -1,  1005,    -1,  1018,    -1,
     259,    -1,    -1,     3,   763,   764,   771,    -1,  1103,   765,
     768,  1025,    -1,  1103,   180,   160,   218,    -1,  1103,   180,
     234,    -1,  1103,   180,    67,    -1,  1103,   180,   103,    -1,
    1103,   180,   103,   447,    -1,  1103,   180,   104,    -1,  1103,
     180,   104,   446,    -1,  1103,   180,   105,    -1,  1103,   180,
     401,    -1,  1103,   180,    69,    -1,  1103,   180,   152,  1025,
      -1,  1103,   180,   150,  1098,  1025,    -1,  1103,   180,    25,
      -1,  1103,   180,    26,  1025,    -1,  1103,   180,  1080,    -1,
    1103,   180,   442,    -1,    -1,  1137,   766,   767,    -1,  1137,
     767,   766,    -1,  1137,   766,    -1,  1137,   767,    -1,    30,
    1098,    -1,   233,  1155,  1100,    -1,    66,  1155,  1100,    -1,
     301,  1155,  1100,    -1,    -1,   441,   769,    -1,   770,    -1,
     769,   770,    -1,    36,    -1,    46,    -1,   194,    -1,   242,
      -1,   343,    -1,   415,    -1,   290,    -1,   176,  1148,  1102,
      -1,    33,  1148,  1102,    -1,   353,   424,  1057,    -1,   353,
     121,  1057,    -1,    31,    -1,   181,    -1,   338,    -1,   357,
      -1,   425,    -1,   314,    -1,    -1,   127,    -1,    -1,     5,
     773,   774,   776,    -1,  1093,   403,  1073,  1031,    -1,  1093,
     775,   187,  1073,  1031,    -1,    94,  1103,   403,  1103,  1126,
    1031,    -1,    -1,   403,  1094,    -1,    -1,   128,    -1,    -1,
      10,   778,   779,    -1,   442,  1122,   780,    -1,  1059,    56,
    1122,   341,  1092,    -1,    -1,   341,  1092,    -1,    18,   782,
      -1,    -1,   782,  1082,   403,   783,  1082,    -1,    -1,   309,
     403,    -1,    -1,    51,   785,  1101,   786,   791,   792,   794,
     796,    -1,    -1,    -1,   434,   787,   788,    -1,   789,    -1,
     788,   789,    -1,   790,   279,    -1,   790,   745,  1094,    -1,
      -1,  1139,   325,    -1,  1139,    86,    -1,  1139,   435,    -1,
      -1,   341,  1103,    -1,   187,  1103,    -1,    -1,    -1,  1012,
     793,   757,    -1,    -1,    -1,  1013,   795,   757,    -1,    -1,
     129,    -1,    -1,    52,   798,   799,    -1,    -1,   799,  1100,
      -1,    -1,    59,   801,   802,    -1,    -1,   802,  1078,   803,
      -1,    -1,   804,    -1,   804,  1145,   329,    -1,  1174,   260,
     344,    -1,  1174,   240,    -1,   324,    -1,   416,    -1,    -1,
      75,   806,   807,   808,    -1,  1073,   809,  1059,  1031,    -1,
      -1,   130,    -1,   456,    -1,   156,    -1,    71,    -1,    87,
      -1,    -1,   111,   813,  1078,  1161,  1051,   814,    -1,    -1,
     131,    -1,    -1,   111,   816,   405,  1077,    -1,    -1,   118,
     818,   819,   823,    -1,  1100,   429,  1026,    -1,  1100,   430,
    1026,    -1,  1100,   427,  1026,    -1,  1100,   428,  1026,    -1,
    1093,   765,   820,  1026,    -1,  1093,   765,   426,  1080,   820,
    1026,    -1,  1093,   765,   426,   442,   820,  1026,    -1,  1093,
     765,   426,   305,   820,  1026,    -1,  1093,   765,   426,    96,
     820,  1026,    -1,    -1,  1174,   269,    -1,   441,   821,    -1,
     822,    -1,   821,   822,    -1,    36,    -1,    46,    -1,   158,
     153,    -1,   158,   155,    -1,   194,    -1,   242,    -1,   343,
      -1,   415,    -1,   290,    -1,   176,  1148,  1102,    -1,    33,
    1148,  1102,    -1,   353,   424,  1057,    -1,   353,   121,  1057,
      -1,    44,    -1,    45,    -1,    -1,   132,    -1,    -1,   119,
     825,   826,   827,    -1,  1094,   210,  1073,  1031,    -1,  1094,
     210,  1094,   187,  1073,  1031,    -1,  1094,    49,  1094,   187,
    1073,  1031,    -1,  1094,   210,  1094,   187,  1074,   328,  1074,
    1031,    -1,  1094,    49,  1094,   187,  1074,   328,  1074,  1031,
      -1,    -1,   133,    -1,    -1,   149,   829,   236,   786,    -1,
      -1,   161,   831,   832,   834,   844,    -1,   833,    -1,   832,
    1133,   833,    -1,  1059,    -1,   408,    -1,   404,    -1,   835,
     838,    -1,   836,    -1,   835,   836,    -1,    -1,   840,   837,
     757,    -1,    -1,    -1,   440,   839,   757,    -1,   438,   841,
      -1,   840,   438,   841,    -1,   842,    -1,   841,  1133,   842,
      -1,  1060,   843,    -1,    21,    -1,   408,    -1,   404,    -1,
      -1,   400,  1059,    -1,    -1,   134,    -1,    -1,   165,   846,
     847,    -1,    -1,   310,    -1,   297,    -1,   297,   100,    -1,
     356,    -1,   296,    -1,    -1,   179,   849,  1091,    -1,    -1,
     186,   851,  1103,    -1,    -1,   189,  1172,   853,  1081,   854,
      -1,    -1,   114,  1157,  1103,    -1,    -1,   190,   856,    -1,
      -1,    -1,   197,   858,  1058,  1170,   859,   757,   860,   862,
      -1,   197,     1,   136,    -1,    -1,    -1,   125,   861,   757,
      -1,    -1,   136,    -1,    -1,   204,   864,  1091,   865,   866,
     867,   871,    -1,    -1,  1174,   171,    -1,    -1,     9,  1172,
     435,    -1,   870,  1172,   435,    -1,    -1,   331,   868,    -1,
     869,    -1,   868,   869,    -1,   870,  1143,    49,  1094,    -1,
      12,    -1,    15,    -1,   272,    -1,    16,    -1,   273,    -1,
     253,    -1,   254,    -1,    -1,   110,    -1,    -1,   206,   873,
     693,    -1,    -1,   209,   875,   876,   877,    -1,  1103,    -1,
    1109,    -1,  1112,    -1,   878,    -1,   877,   878,    -1,   879,
      -1,   883,    -1,   888,    -1,    -1,   394,   880,   881,    -1,
     882,    -1,   881,   882,    -1,  1098,   175,    -1,    56,   889,
      -1,     9,    -1,   223,    -1,   411,    -1,  1098,   889,    -1,
     331,   884,    -1,   885,    -1,   884,   885,    -1,    56,    49,
    1098,   889,    -1,   886,   887,    -1,    -1,     9,    -1,   223,
      -1,   173,    -1,   411,    -1,  1098,    49,  1099,   889,    -1,
      92,  1098,   403,  1099,   889,    -1,    -1,   889,  1022,   890,
    1094,    -1,    -1,   406,    -1,    -1,   246,   892,   957,    -1,
      -1,   250,   894,   895,    -1,  1094,   403,  1091,    -1,    94,
    1094,   403,  1091,    -1,    -1,   252,   897,   898,   899,    -1,
    1094,    49,  1073,  1031,    -1,  1094,    49,  1094,   187,  1073,
    1031,    -1,    -1,   137,    -1,    -1,   282,   901,   902,    -1,
      -1,   902,   903,   904,  1077,   905,    -1,   207,    -1,   288,
      -1,   215,    -1,   166,    -1,    -1,   366,  1174,   580,    -1,
      -1,  1174,   260,   344,    -1,  1174,   240,    -1,    -1,   297,
     907,   908,    -1,   911,   912,    -1,    -1,   912,   909,   757,
     910,    -1,   912,   138,    -1,    -1,   138,    -1,  1082,    -1,
    1082,   400,  1082,    -1,    -1,   177,    -1,  1101,   402,    -1,
     913,   423,  1058,    -1,   913,   436,   914,    -1,    -1,  1174,
     397,  1022,    -1,   915,    -1,   914,     8,   915,    -1,  1103,
     180,  1094,    49,  1094,   423,  1058,    -1,    -1,   318,   917,
    1078,  1123,  1161,   918,   919,   920,   921,   922,    -1,    -1,
     210,  1103,    -1,    -1,   199,   240,    -1,  1174,   240,    -1,
    1174,   260,   240,    -1,  1174,   198,   240,    -1,  1174,   437,
      -1,    -1,   218,  1148,   693,    -1,    -1,  1041,    -1,  1052,
      -1,    -1,   140,    -1,    -1,   327,   924,  1075,  1020,    -1,
      -1,   340,   926,  1078,  1161,   918,  1041,   927,    -1,    -1,
     141,    -1,    -1,   345,   929,  1075,  1020,   930,  1051,   931,
      -1,    -1,  1174,   240,    -1,  1174,   260,   240,    -1,    -1,
     142,    -1,   347,    -1,    -1,   355,   934,   935,   943,    -1,
    1076,   937,   938,   940,    -1,    -1,     9,  1076,   938,   438,
    1059,   936,   757,    -1,    -1,   436,  1103,    -1,    -1,    -1,
    1137,   126,   939,   757,    -1,   941,    -1,   941,   940,    -1,
      -1,   438,  1058,   942,   757,    -1,    -1,   143,    -1,    -1,
     365,   945,   946,    -1,   947,    -1,   948,    -1,   949,    -1,
     951,    -1,   953,    -1,   150,  1098,   403,  1098,    -1,  1091,
     403,   149,  1097,    -1,  1091,   403,  1094,    -1,  1091,   950,
      49,  1094,    -1,   424,    -1,   121,    -1,   952,    -1,   951,
     952,    -1,  1079,   403,   520,    -1,   954,    -1,   953,   954,
      -1,  1091,   403,   408,    -1,  1091,   403,   404,    -1,    -1,
     374,   956,   957,    -1,    -1,  1105,   959,   961,   962,   958,
     963,   964,    -1,    -1,   959,  1157,   661,  1150,  1148,   960,
      -1,    -1,   960,  1105,    -1,    -1,  1130,  1158,    -1,    -1,
    1131,  1148,  1086,    -1,    -1,   434,  1077,    -1,   207,   307,
    1148,   911,    -1,    -1,   187,  1077,    -1,   288,   307,  1148,
     911,    -1,    -1,    -1,   383,   966,  1078,   967,   968,  1051,
     970,    -1,    -1,   218,  1148,   969,   693,    -1,  1124,  1064,
      -1,  1124,  1065,    -1,  1124,  1066,    -1,  1124,  1067,    -1,
    1124,  1068,    -1,    -1,   144,    -1,    -1,   385,   349,   972,
     974,    -1,    -1,   385,   236,   973,    -1,    -1,   341,  1094,
      -1,   187,  1094,    -1,    -1,   386,   976,   977,   210,  1103,
     979,  1036,   980,    -1,   978,    -1,   977,   978,    -1,  1094,
      -1,   112,  1139,   372,    -1,   112,  1139,  1094,    -1,    -1,
    1174,   300,  1103,    -1,    -1,   145,    -1,    -1,   389,   982,
     983,   984,    -1,  1093,   180,  1073,  1031,    -1,  1093,   180,
    1094,   187,  1073,  1031,    -1,    94,  1103,   180,  1103,  1126,
    1031,    -1,    -1,   146,    -1,   391,   986,    -1,    -1,   306,
      -1,    -1,   396,   988,   693,    -1,    -1,   412,   990,  1103,
     180,  1098,   403,  1099,    -1,    -1,   417,   992,  1078,   993,
      -1,    -1,   319,    -1,   321,    -1,    -1,   422,   995,  1103,
     996,   999,   979,  1003,  1036,  1004,    -1,    -1,   112,  1139,
     997,    -1,   998,    -1,   997,   284,   998,    -1,  1120,  1098,
      -1,   210,  1000,    -1,   999,  1000,    -1,  1103,  1001,  1002,
      -1,    -1,   113,  1147,  1103,    -1,    -1,    95,  1147,  1103,
      -1,    -1,   394,  1147,  1103,    -1,    -1,   147,    -1,  1006,
      -1,  1015,    -1,  1017,    -1,   433,  1007,  1009,  1010,  1011,
    1014,  1157,  1008,    -1,    -1,   188,    -1,  1077,    -1,   207,
      -1,   288,    -1,   215,    -1,   166,    -1,    -1,     8,    -1,
      -1,   380,    -1,   163,    -1,   159,    -1,   163,    -1,   289,
      -1,   265,    -1,   267,    -1,    -1,   307,    -1,   433,  1145,
     107,  1157,  1016,    -1,  1082,    -1,     9,   308,    -1,   433,
    1007,    35,   333,  1103,    -1,    -1,   445,  1019,  1075,  1020,
     930,  1021,  1023,  1024,    -1,    -1,   180,  1100,    -1,    -1,
    1022,  1132,  1102,  1151,    -1,  1022,  1132,  1080,    -1,  1022,
    1132,   293,    -1,    35,    -1,     8,    -1,    -1,  1046,    -1,
    1052,    -1,    -1,   148,    -1,  1027,  1029,    -1,  1027,  1029,
      -1,    -1,    -1,   163,  1028,   757,    -1,    -1,    -1,   265,
    1030,   757,    -1,  1032,  1034,    -1,    -1,    -1,   373,  1033,
     757,    -1,    -1,    -1,   268,  1035,   757,    -1,  1037,  1039,
      -1,    -1,    -1,   289,  1038,   757,    -1,    -1,    -1,   267,
    1040,   757,    -1,  1042,    -1,  1044,    -1,  1042,  1044,    -1,
      -1,   126,  1043,   757,    -1,    -1,   263,  1045,   757,    -1,
    1047,    -1,  1049,    -1,  1047,  1049,    -1,    -1,   154,  1048,
     757,    -1,    -1,   264,  1050,   757,    -1,    -1,  1052,    -1,
    1053,    -1,  1055,    -1,  1053,  1055,    -1,    -1,   213,  1054,
     757,    -1,    -1,   266,  1056,   757,    -1,    -1,  1139,  1102,
    1151,    -1,  1059,    -1,  1060,    -1,    -1,  1061,  1062,    -1,
    1063,  1094,    -1,  1062,   457,    -1,  1063,   279,    -1,  1063,
     272,    -1,  1063,    12,    -1,  1063,    13,    -1,  1063,    14,
      -1,  1063,    58,    -1,  1062,   279,    -1,  1062,   272,    -1,
    1062,    12,    -1,  1062,    13,    -1,  1062,    14,    -1,  1062,
      58,    -1,  1063,   302,    -1,  1063,   257,    -1,  1062,   302,
      -1,  1062,   257,    -1,  1062,   448,    -1,    -1,  1062,   214,
      -1,  1063,   214,    -1,  1063,   458,    -1,  1063,   449,    -1,
    1063,   450,    -1,  1063,   454,    -1,  1063,   262,    -1,  1062,
     262,    -1,  1062,   449,    -1,  1062,   450,    -1,  1062,   451,
      -1,  1062,   452,    -1,  1062,   454,    -1,  1062,  1064,    -1,
    1062,  1065,    -1,  1062,  1066,    -1,  1062,  1067,    -1,  1062,
    1068,    -1,  1062,   256,    -1,  1063,  1064,    -1,  1063,  1065,
      -1,  1063,  1066,    -1,  1063,  1067,    -1,  1063,  1068,    -1,
    1063,   256,    -1,  1062,    20,    -1,  1062,   284,    -1,   456,
      -1,   156,  1172,    -1,   157,    -1,   459,    -1,   191,  1169,
      -1,   460,    -1,   226,  1169,    -1,   185,    -1,   191,  1169,
     284,   156,  1172,    -1,   191,  1169,   156,  1172,    -1,   222,
      -1,   226,  1169,   284,   156,  1172,    -1,   226,  1169,   156,
    1172,    -1,  1071,    -1,  1069,  1070,  1071,    -1,    -1,    70,
      -1,   360,    -1,  1095,    -1,  1071,   449,  1071,    -1,  1071,
     450,  1071,    -1,  1071,   451,  1071,    -1,  1071,   452,  1071,
      -1,   449,  1071,    -1,   450,  1071,    -1,  1071,   454,  1071,
      -1,   458,  1071,   457,    -1,   232,    -1,   232,  1128,   442,
      -1,  1074,    -1,  1073,  1074,    -1,  1094,  1126,    -1,  1105,
      -1,  1105,    -1,  1078,    -1,  1077,  1078,    -1,   442,    -1,
    1080,    -1,  1079,  1080,    -1,   248,    -1,    -1,  1081,  1082,
      -1,  1083,    -1,  1105,    -1,  1084,    -1,  1084,  1128,  1084,
      -1,   236,    -1,  1086,    -1,  1085,  1086,    -1,  1105,    -1,
    1105,    -1,  1087,  1105,    -1,    -1,  1086,    -1,  1086,    -1,
     236,    -1,   442,    -1,  1092,    -1,  1091,  1092,    -1,  1103,
      -1,     6,  1156,  1104,    -1,  1094,    -1,  1093,  1094,    -1,
    1103,    -1,   225,  1156,  1104,    -1,   225,  1156,  1110,    -1,
     225,  1156,  1112,    -1,     6,  1156,  1096,  1097,    -1,     6,
    1156,  1104,    -1,  1109,    -1,  1112,    -1,  1072,    -1,  1103,
      -1,   225,  1156,  1104,    -1,   225,  1156,  1110,    -1,   225,
    1156,  1112,    -1,  1110,    -1,  1112,    -1,  1072,    -1,   310,
      -1,   149,    -1,  1104,    -1,   236,    -1,  1103,    -1,  1110,
      -1,  1103,    -1,  1109,    -1,  1103,    -1,   236,    -1,  1103,
      -1,   236,    -1,  1112,    -1,  1103,    -1,  1108,    -1,   448,
      -1,  1104,    -1,  1105,    -1,  1105,  1106,    -1,  1105,  1107,
      -1,  1105,  1106,  1107,    -1,   442,    -1,   442,  1128,  1105,
      -1,   458,  1069,   457,    -1,   458,  1071,   461,   457,    -1,
     458,  1071,   461,  1071,   457,    -1,   236,    -1,  1110,    -1,
       9,  1111,    -1,  1111,    -1,  1110,   462,  1111,    -1,   236,
      -1,   378,    -1,   448,    -1,   315,    -1,   195,    -1,   243,
      -1,   407,    -1,    98,  1113,    -1,   439,  1113,    -1,   431,
     458,  1071,   457,  1113,    -1,   241,   458,  1071,   457,  1113,
      -1,   342,   458,  1071,   457,  1113,    -1,    82,   458,  1069,
     457,  1113,    -1,   387,   458,  1069,   457,  1113,    -1,   388,
     458,  1069,   457,  1113,    -1,   413,   458,  1116,   457,  1113,
      -1,   274,   458,  1117,   457,    -1,   238,   458,  1118,   457,
    1113,    -1,   184,  1114,    -1,    -1,   458,  1071,   461,   457,
      -1,   458,  1071,   461,  1071,   457,    -1,    -1,   458,  1115,
     457,    -1,    -1,  1069,    -1,  1071,    -1,  1071,  1070,   223,
      -1,  1071,  1070,   411,    -1,  1071,    -1,  1071,  1070,  1071,
      -1,  1071,    -1,  1071,  1070,  1086,    -1,    -1,    -1,     9,
      -1,    -1,  1130,    -1,    -1,   205,    -1,    -1,   258,    -1,
     304,    -1,    -1,   262,    -1,    -1,   283,    -1,    -1,   348,
      -1,    -1,   362,  1140,    -1,   200,    -1,   277,    -1,   319,
    1148,    -1,   321,  1134,    -1,   441,   122,    -1,   122,    -1,
      63,   363,    -1,   363,    -1,    -1,     7,    -1,    -1,    17,
      -1,    -1,    23,    -1,    -1,    24,    -1,    -1,    27,    -1,
      -1,    30,    -1,    -1,    37,    -1,    -1,    49,    -1,    -1,
      55,    -1,    -1,    56,    -1,    -1,    85,    -1,    -1,   102,
      -1,    -1,   405,    -1,    -1,   175,    -1,    -1,   180,    -1,
      -1,   200,    -1,    -1,   214,    -1,    -1,   214,    -1,    23,
      -1,    -1,   218,    -1,    -1,   233,    -1,   234,    -1,    -1,
     234,    -1,    -1,   236,    -1,    -1,   249,    -1,    -1,   270,
      -1,    -1,   277,    -1,    -1,   280,    -1,    -1,   285,    -1,
     200,   285,    -1,    -1,   287,    -1,    -1,   310,    -1,    -1,
     319,    -1,    -1,   346,    -1,    -1,   365,    -1,    -1,   367,
      -1,    -1,   367,    -1,   367,   214,    -1,    -1,   372,    -1,
      -1,   384,    -1,    -1,   395,    -1,    -1,   398,    -1,    -1,
     399,    -1,    -1,   402,    -1,    -1,   403,    -1,    -1,   438,
      -1,    -1,   441,    -1
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
    6016,  6020,  6021,  6030,  6030,  6035,  6035,  6042,  6043,  6044,
    6053,  6053,  6062,  6063,  6067,  6068,  6069,  6073,  6074,  6078,
    6079,  6088,  6088,  6094,  6098,  6102,  6109,  6110,  6119,  6126,
    6127,  6135,  6135,  6148,  6148,  6164,  6164,  6173,  6175,  6176,
    6185,  6185,  6195,  6196,  6201,  6202,  6207,  6214,  6215,  6220,
    6227,  6228,  6232,  6233,  6237,  6238,  6242,  6243,  6252,  6253,
    6254,  6258,  6282,  6285,  6293,  6303,  6308,  6313,  6318,  6325,
    6326,  6329,  6330,  6334,  6334,  6338,  6338,  6342,  6342,  6345,
    6346,  6350,  6357,  6358,  6362,  6374,  6374,  6391,  6392,  6397,
    6400,  6404,  6408,  6415,  6416,  6419,  6420,  6421,  6425,  6426,
    6439,  6447,  6454,  6456,  6455,  6465,  6467,  6466,  6481,  6485,
    6487,  6486,  6497,  6499,  6498,  6515,  6521,  6523,  6522,  6532,
    6534,  6533,  6549,  6554,  6559,  6569,  6568,  6580,  6579,  6595,
    6600,  6605,  6615,  6614,  6626,  6625,  6640,  6641,  6645,  6650,
    6655,  6665,  6664,  6676,  6675,  6692,  6695,  6707,  6714,  6721,
    6721,  6731,  6732,  6734,  6735,  6736,  6737,  6738,  6739,  6741,
    6742,  6743,  6744,  6745,  6746,  6748,  6749,  6751,  6752,  6753,
    6756,  6758,  6759,  6760,  6762,  6763,  6764,  6766,  6767,  6769,
    6770,  6771,  6772,  6773,  6775,  6776,  6777,  6778,  6779,  6780,
    6782,  6783,  6784,  6785,  6786,  6787,  6789,  6790,  6793,  6793,
    6793,  6794,  6794,  6795,  6795,  6796,  6796,  6796,  6797,  6797,
    6797,  6802,  6803,  6806,  6807,  6808,  6812,  6813,  6814,  6815,
    6816,  6817,  6818,  6819,  6820,  6831,  6843,  6858,  6859,  6864,
    6870,  6892,  6912,  6916,  6932,  6946,  6947,  6952,  6958,  6959,
    6964,  6973,  6974,  6975,  6979,  6990,  6991,  6995,  7005,  7006,
    7010,  7011,  7015,  7016,  7022,  7042,  7043,  7047,  7048,  7052,
    7053,  7057,  7058,  7059,  7060,  7061,  7062,  7063,  7064,  7065,
    7069,  7070,  7071,  7072,  7073,  7074,  7075,  7079,  7080,  7084,
    7085,  7089,  7090,  7094,  7095,  7106,  7107,  7111,  7112,  7113,
    7117,  7118,  7119,  7127,  7131,  7132,  7133,  7134,  7138,  7139,
    7143,  7153,  7171,  7198,  7210,  7211,  7221,  7222,  7226,  7227,
    7228,  7229,  7230,  7231,  7232,  7240,  7244,  7248,  7252,  7256,
    7260,  7264,  7268,  7272,  7276,  7280,  7284,  7291,  7292,  7293,
    7297,  7298,  7302,  7303,  7308,  7315,  7322,  7332,  7339,  7349,
    7356,  7370,  7380,  7381,  7385,  7386,  7390,  7391,  7395,  7396,
    7397,  7401,  7402,  7406,  7407,  7411,  7412,  7416,  7417,  7424,
    7424,  7425,  7425,  7426,  7426,  7427,  7427,  7429,  7429,  7430,
    7430,  7431,  7431,  7432,  7432,  7433,  7433,  7434,  7434,  7435,
    7435,  7436,  7436,  7437,  7437,  7438,  7438,  7439,  7439,  7440,
    7440,  7441,  7441,  7442,  7442,  7443,  7443,  7444,  7444,  7445,
    7445,  7446,  7446,  7446,  7447,  7447,  7448,  7448,  7448,  7449,
    7449,  7450,  7450,  7451,  7451,  7452,  7452,  7453,  7453,  7454,
    7454,  7455,  7455,  7455,  7456,  7456,  7457,  7457,  7458,  7458,
    7459,  7459,  7460,  7460,  7461,  7461,  7462,  7462,  7462,  7463,
    7463,  7464,  7464,  7465,  7465,  7466,  7466,  7467,  7467,  7468,
    7468,  7469,  7469,  7471,  7471,  7472,  7472
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
  "stop_statement", "$@87", "$@88", "stop_returning", "string_statement",
  "$@89", "string_item_list", "string_item", "opt_with_pointer",
  "end_string", "subtract_statement", "$@90", "subtract_body",
  "end_subtract", "suppress_statement", "_printing", "terminate_statement",
  "$@91", "transform_statement", "$@92", "unlock_statement", "$@93",
  "opt_record", "unstring_statement", "$@94", "unstring_delimited",
  "unstring_delimited_list", "unstring_delimited_item", "unstring_into",
  "unstring_into_item", "unstring_into_delimiter", "unstring_into_count",
  "unstring_tallying", "end_unstring", "use_statement", "use_exception",
  "use_global", "use_exception_target", "_after", "_standard",
  "exception_or_error", "exception_or_overflow",
  "not_exception_or_overflow", "_procedure", "use_debugging",
  "use_debugging_target", "use_reporting", "write_statement", "$@95",
  "write_from", "write_option", "before_or_after", "write_handler",
  "end_write", "on_accp_exception", "on_disp_exception",
  "opt_on_exception", "$@96", "opt_not_on_exception", "$@97",
  "on_size_error", "opt_on_size_error", "$@98", "opt_not_on_size_error",
  "$@99", "on_overflow", "opt_on_overflow", "$@100", "opt_not_on_overflow",
  "$@101", "at_end", "at_end_sentence", "$@102", "not_at_end_sentence",
  "$@103", "at_eop", "at_eop_sentence", "$@104", "not_at_eop_sentence",
  "$@105", "opt_invalid_key", "invalid_key", "invalid_key_sentence",
  "$@106", "not_invalid_key_sentence", "$@107", "_opt_scroll_lines",
  "condition", "expr", "partial_expr", "$@108", "expr_tokens",
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
     969,   970,   970,   972,   971,   973,   971,   974,   974,   974,
     976,   975,   977,   977,   978,   978,   978,   979,   979,   980,
     980,   982,   981,   983,   983,   983,   984,   984,   985,   986,
     986,   988,   987,   990,   989,   992,   991,   993,   993,   993,
     995,   994,   996,   996,   997,   997,   998,   999,   999,  1000,
    1001,  1001,  1002,  1002,  1003,  1003,  1004,  1004,  1005,  1005,
    1005,  1006,  1007,  1007,  1008,  1008,  1008,  1008,  1008,  1009,
    1009,  1010,  1010,  1011,  1011,  1012,  1012,  1013,  1013,  1014,
    1014,  1015,  1016,  1016,  1017,  1019,  1018,  1020,  1020,  1021,
    1021,  1021,  1021,  1022,  1022,  1023,  1023,  1023,  1024,  1024,
    1025,  1026,  1027,  1028,  1027,  1029,  1030,  1029,  1031,  1032,
    1033,  1032,  1034,  1035,  1034,  1036,  1037,  1038,  1037,  1039,
    1040,  1039,  1041,  1041,  1041,  1043,  1042,  1045,  1044,  1046,
    1046,  1046,  1048,  1047,  1050,  1049,  1051,  1051,  1052,  1052,
    1052,  1054,  1053,  1056,  1055,  1057,  1057,  1058,  1059,  1061,
    1060,  1062,  1062,  1062,  1062,  1062,  1062,  1062,  1062,  1062,
    1062,  1062,  1062,  1062,  1062,  1062,  1062,  1062,  1062,  1062,
    1063,  1063,  1063,  1063,  1063,  1063,  1063,  1063,  1063,  1063,
    1063,  1063,  1063,  1063,  1063,  1063,  1063,  1063,  1063,  1063,
    1063,  1063,  1063,  1063,  1063,  1063,  1063,  1063,  1064,  1064,
    1064,  1065,  1065,  1066,  1066,  1067,  1067,  1067,  1068,  1068,
    1068,  1069,  1069,  1070,  1070,  1070,  1071,  1071,  1071,  1071,
    1071,  1071,  1071,  1071,  1071,  1072,  1072,  1073,  1073,  1074,
    1075,  1076,  1077,  1077,  1078,  1079,  1079,  1080,  1081,  1081,
    1082,  1083,  1083,  1083,  1084,  1085,  1085,  1086,  1087,  1087,
    1088,  1088,  1089,  1089,  1090,  1091,  1091,  1092,  1092,  1093,
    1093,  1094,  1094,  1094,  1094,  1094,  1094,  1094,  1094,  1094,
    1095,  1095,  1095,  1095,  1095,  1095,  1095,  1096,  1096,  1097,
    1097,  1098,  1098,  1099,  1099,  1100,  1100,  1101,  1101,  1101,
    1102,  1102,  1102,  1103,  1104,  1104,  1104,  1104,  1105,  1105,
    1106,  1107,  1107,  1108,  1109,  1109,  1110,  1110,  1111,  1111,
    1111,  1111,  1111,  1111,  1111,  1112,  1112,  1112,  1112,  1112,
    1112,  1112,  1112,  1112,  1112,  1112,  1112,  1113,  1113,  1113,
    1114,  1114,  1115,  1115,  1116,  1116,  1116,  1117,  1117,  1118,
    1118,  1119,  1120,  1120,  1121,  1121,  1122,  1122,  1123,  1123,
    1123,  1124,  1124,  1125,  1125,  1126,  1126,  1127,  1127,  1128,
    1128,  1129,  1129,  1130,  1130,  1131,  1131,  1132,  1132,  1133,
    1133,  1134,  1134,  1135,  1135,  1136,  1136,  1137,  1137,  1138,
    1138,  1139,  1139,  1140,  1140,  1141,  1141,  1142,  1142,  1143,
    1143,  1144,  1144,  1145,  1145,  1146,  1146,  1147,  1147,  1148,
    1148,  1149,  1149,  1149,  1150,  1150,  1151,  1151,  1151,  1152,
    1152,  1153,  1153,  1154,  1154,  1155,  1155,  1156,  1156,  1157,
    1157,  1158,  1158,  1158,  1159,  1159,  1160,  1160,  1161,  1161,
    1162,  1162,  1163,  1163,  1164,  1164,  1165,  1165,  1165,  1166,
    1166,  1167,  1167,  1168,  1168,  1169,  1169,  1170,  1170,  1171,
    1171,  1172,  1172,  1173,  1173,  1174,  1174
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
       2,     0,     1,     0,     4,     0,     3,     0,     2,     2,
       0,     8,     1,     2,     1,     3,     3,     0,     3,     0,
       1,     0,     4,     4,     6,     6,     0,     1,     2,     0,
       1,     0,     3,     0,     7,     0,     4,     0,     1,     1,
       0,     9,     0,     3,     1,     3,     2,     2,     2,     3,
       0,     3,     0,     3,     0,     3,     0,     1,     1,     1,
       1,     8,     0,     1,     1,     1,     1,     1,     1,     0,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     5,     1,     2,     5,     0,     8,     0,     2,     0,
       4,     3,     3,     1,     1,     0,     1,     1,     0,     1,
       2,     2,     0,     0,     3,     0,     0,     3,     2,     0,
       0,     3,     0,     0,     3,     2,     0,     0,     3,     0,
       0,     3,     1,     1,     2,     0,     3,     0,     3,     1,
       1,     2,     0,     3,     0,     3,     0,     1,     1,     1,
       2,     0,     3,     0,     3,     0,     3,     1,     1,     0,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     2,
       1,     1,     2,     1,     2,     1,     5,     4,     1,     5,
       4,     1,     3,     0,     1,     1,     1,     3,     3,     3,
       3,     2,     2,     3,     3,     1,     3,     1,     2,     2,
       1,     1,     1,     2,     1,     1,     2,     1,     0,     2,
       1,     1,     1,     3,     1,     1,     2,     1,     1,     2,
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
       1,     0,     1,     2,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     2,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,     4,     6,     7,
      38,    38,     0,     0,     3,     5,     0,     8,    14,    28,
      27,    29,    29,     0,   276,   276,     0,     0,    24,    40,
       0,     9,    15,    30,    26,  1539,     0,   157,     0,   624,
     624,  1540,     0,     0,     0,     0,     0,     0,    39,   278,
       0,    17,     0,    25,    33,    37,    36,  1566,    35,    42,
     159,     0,   161,   288,   289,     0,   340,   281,   628,    18,
      20,    38,     0,    16,    34,  1567,    32,    41,   165,   163,
     249,     0,     0,   472,     0,   631,   629,   646,     0,    19,
      10,    11,     0,     0,     0,     0,     0,    43,    44,    45,
      47,    46,   160,     0,   247,     0,  1531,   258,   162,   251,
     253,   255,   256,   252,   269,   279,     0,     0,   475,  1374,
     282,   343,   290,   636,   636,     0,     0,     0,   276,    23,
      56,    71,    49,    80,  1493,   166,   165,     0,   158,     0,
    1559,     0,  1557,     0,  1532,  1583,   259,   260,   261,  1513,
     250,   254,   268,   270,   283,   341,     0,     0,   478,   287,
       0,   286,   344,  1481,   292,  1522,   636,   633,   639,     0,
     636,   647,   625,    21,    12,     0,  1539,    54,  1566,    55,
    1566,    60,    62,    63,    64,     0,     0,    70,     0,    73,
    1596,    48,     0,  1595,     0,     0,  1539,  1539,     0,     0,
    1574,  1539,  1539,  1539,  1539,  1539,     0,  1539,  1525,  1539,
      79,    81,    83,    85,    86,    87,    89,    88,    90,    91,
      92,    93,    94,    95,  1494,     0,   164,   249,     0,  1560,
       0,     0,  1558,     0,     0,  1584,  1527,  1514,  1533,   280,
     343,   473,     0,     0,   570,   343,   346,     0,     0,   634,
    1539,     0,   644,   637,   638,   648,   624,  1539,     0,    57,
    1566,    59,    61,     0,  1506,  1539,     0,    77,     0,    72,
      74,    52,    50,     0,     0,  1394,   112,     0,     0,  1539,
    1539,  1575,  1539,     0,     0,     0,     0,     0,  1539,     0,
    1526,     0,    99,    82,    84,   167,   248,  1438,   275,  1385,
    1387,   271,     0,     0,     0,  1528,     0,  1534,     0,   284,
     342,   343,   476,     0,     0,   277,   285,   349,     0,   355,
     356,   347,   359,   359,   350,   305,  1527,  1539,     0,     0,
    1539,  1527,  1553,  1539,  1511,     0,   291,   293,   296,   297,
     298,   299,   300,   301,   302,   303,   304,     0,     0,  1539,
     645,     0,     0,   626,    17,     0,  1443,    69,    58,  1505,
       0,    76,    75,    78,    51,    53,  1539,   101,   102,     0,
       0,     0,   153,   152,   103,   104,   156,     0,   155,   139,
    1541,   141,    96,     0,    97,   169,  1499,  1500,     0,  1386,
       0,     0,     0,   262,   263,   266,   257,  1372,   474,   343,
     479,     0,   348,   360,   361,   351,     0,   361,   353,     0,
       0,  1539,  1511,     0,     0,     0,     0,     0,  1554,  1539,
       0,  1512,     0,     0,   294,   295,   640,   641,   643,     0,
     635,   649,   651,     0,     0,    68,     0,  1452,  1448,  1453,
    1451,  1449,  1454,  1450,   145,   146,   148,   154,   151,   150,
    1543,  1542,   142,     0,   111,   110,   100,   107,  1581,   105,
       0,  1439,   273,     0,   274,   264,     0,   265,  1373,   477,
     481,   571,   369,   363,     0,   317,   337,  1501,  1502,   326,
    1388,   321,   320,   319,  1393,  1392,  1549,  1525,  1537,     0,
     569,   338,   339,  1539,  1539,   642,   651,     0,     0,    13,
      66,    67,    65,   117,   131,   127,   132,   114,   130,   128,
     115,   116,   129,   113,   118,   119,   121,   147,     0,   140,
     143,   108,  1582,  1539,    98,   184,  1553,     0,  1591,   230,
       0,  1553,  1544,  1539,  1523,  1544,   233,     0,   232,  1595,
     217,   216,   168,   170,   171,   172,   173,   174,   175,     0,
     176,   177,   229,   178,   179,   180,   181,   182,   183,   185,
    1539,   272,   267,     0,   480,   482,   483,   572,     0,  1515,
       0,  1541,   354,     0,   307,  1389,  1550,   328,     0,   310,
    1538,  1579,   336,     0,     0,     0,   657,   661,   652,   653,
     654,   655,   660,     0,     0,   120,   123,     0,   149,   144,
       0,   106,  1539,  1544,  1592,   192,   234,  1539,  1545,  1539,
       0,  1524,  1539,  1520,  1539,     0,  1539,  1539,   241,  1513,
       0,  1539,     0,   486,   484,   574,   385,     0,   459,   394,
     427,   415,   424,   421,   418,  1593,   395,   396,   397,   398,
     399,   400,   401,   402,   403,  1570,   358,   428,     0,   404,
     391,   405,   406,     0,     0,  1577,   408,   409,   407,   455,
     411,   412,   410,  1539,  1539,   352,   370,   371,   372,   373,
     374,   375,   392,   376,   377,   378,   379,   380,   381,   382,
     383,   384,     0,     0,  1516,     0,   364,     0,   318,   309,
     308,   306,   327,  1525,  1580,   315,   324,   323,   325,   322,
       0,   659,   662,   719,   770,   779,   786,   790,   814,   818,
     836,   829,   837,   838,   844,   877,   886,   888,   915,   923,
     925,  1591,   931,     0,   942,   963,   965,  1001,  1003,  1007,
     718,  1013,  1026,  1046,  1063,  1065,  1069,  1076,  1077,  1093,
    1113,  1131,     0,  1150,  1161,  1169,  1171,  1173,  1175,  1180,
    1202,  1225,   656,   668,   669,   670,   671,   672,   673,   674,
     675,   677,   676,   678,   679,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   693,   694,
     695,   696,   697,   698,   699,   700,   701,   702,   703,   704,
     705,   706,   707,   708,   709,   710,   711,   712,   713,   714,
     715,   716,  1198,  1199,  1200,   717,    22,     0,   122,   109,
       0,  1539,   194,   193,   189,     0,     0,  1519,   233,   228,
       0,     0,   231,     0,     0,   240,  1564,  1564,     0,   242,
       0,   213,  1539,   359,   578,   573,   575,   576,   471,   425,
     426,   413,   414,   422,   423,   419,   420,   416,   417,  1594,
       0,  1571,   453,   435,   386,  1434,   469,  1578,   456,   457,
     454,     0,     0,   388,   390,  1497,  1497,     0,  1557,  1557,
     368,   365,  1444,  1446,   461,   463,   465,  1518,   329,   330,
     331,   332,     0,     0,   311,  1536,   317,     0,     0,   663,
       0,     0,     0,  1289,   785,     0,   816,   820,     0,     0,
       0,     0,     0,     0,  1289,   917,     0,     0,   927,   932,
       0,  1289,     0,     0,     0,     0,     0,     0,  1015,  1036,
       0,     0,     0,     0,     0,     0,     0,     0,  1145,  1143,
       0,     0,  1170,  1168,     0,     0,     0,     0,  1203,  1209,
       0,     0,   137,   133,   138,   136,   134,   135,   124,   125,
     202,   203,   201,   200,     0,   187,   188,  1551,   222,   221,
     222,   218,   246,   235,   236,   237,   239,  1565,   243,   244,
     245,  1390,  1539,   495,   495,  1541,   515,   487,   490,   491,
       0,   579,   577,   458,     0,  1589,     0,  1435,  1436,     0,
     393,   460,     0,   387,  1523,   429,   430,  1445,     0,     0,
       0,  1593,   464,     0,     0,     0,  1517,  1525,   316,   650,
     658,   768,   738,  1433,  1557,     0,     0,  1467,  1470,  1557,
    1365,     0,     0,     0,     0,     0,     0,     0,     0,  1467,
     777,  1409,   775,  1399,  1401,  1407,  1408,  1486,   780,     0,
    1288,  1310,  1384,     0,  1380,  1382,  1381,  1428,   792,  1427,
    1429,   815,   819,   832,     0,  1367,  1495,  1568,     0,  1448,
     875,   738,     0,  1401,   884,     0,   792,   894,   893,  1509,
     890,   892,   922,   919,   918,   921,   916,  1557,   924,  1395,
    1397,   926,  1378,   936,  1587,  1287,   944,   964,   497,     0,
     967,   968,   969,  1002,  1117,     0,  1004,     0,  1011,     0,
    1014,  1037,  1384,  1027,  1036,  1029,     0,  1034,     0,  1381,
       0,  1488,  1227,  1370,  1568,  1227,     0,  1091,  1082,  1371,
       0,  1377,  1094,  1095,  1096,  1097,  1098,  1106,  1099,  1109,
       0,  1375,     0,  1114,  1132,  1146,  1147,  1521,     0,  1152,
    1154,     0,  1166,     0,  1172,     0,  1177,  1182,  1210,     0,
    1211,  1559,  1227,     0,  1484,   196,   195,   186,     0,     0,
     220,   219,  1539,   212,   206,  1391,   214,     0,   496,   492,
       0,   493,     0,   485,   488,   581,   436,  1590,   437,  1557,
       0,     0,     0,  1353,  1351,  1416,  1356,  1410,  1414,  1415,
       0,  1437,   470,   389,  1498,   367,   366,  1447,  1572,   466,
     335,  1549,     0,   313,   769,   720,  1518,     0,   747,     0,
       0,     0,     0,     0,  1455,  1472,  1466,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1456,   778,   771,
       0,     0,  1400,  1487,   783,  1486,  1290,     0,   788,     0,
     793,   803,  1426,   817,  1425,   822,   833,   830,   835,   834,
    1289,  1368,  1496,  1369,  1569,  1276,   843,   876,   845,   855,
    1242,  1242,  1242,  1242,   885,   878,     0,     0,   887,  1510,
    1289,   913,   900,   896,   898,  1289,   920,     0,  1396,   929,
    1588,   934,   946,     0,   498,     0,   990,   975,   966,   970,
     972,   973,   974,  1121,     0,     0,  1012,  1008,     0,  1020,
    1017,  1019,  1018,  1021,  1028,  1031,   664,  1289,     0,     0,
    1038,     0,  1489,  1490,  1568,     0,  1064,  1048,  1071,  1084,
    1092,  1078,     0,  1084,     0,  1421,  1422,  1107,  1110,     0,
       0,  1376,  1105,     0,  1104,     0,  1134,     0,     0,  1144,
       0,     0,  1153,     0,  1167,  1162,     0,     0,  1178,  1179,
    1176,  1521,     0,     0,  1212,     0,     0,  1071,   126,  1504,
       0,   206,   204,  1485,   197,   198,     0,   225,   211,   238,
       0,   489,   494,   500,   510,   359,   516,  1576,  1559,   431,
       0,  1361,  1362,     0,  1354,  1355,  1440,     0,     0,     0,
       0,     0,     0,     0,     0,  1573,  1591,   334,  1549,  1559,
     312,   743,   734,  1242,   724,   731,   725,   727,   729,     0,
    1242,     0,   723,   730,   737,   736,     0,  1242,  1555,  1555,
    1555,   741,   742,  1418,  1417,     0,  1406,  1353,  1351,     0,
       0,  1353,     0,  1402,  1403,  1404,  1366,  1353,     0,     0,
    1353,     0,     0,  1353,  1353,  1353,     0,     0,  1249,  1495,
       0,     0,   781,     0,  1301,  1302,  1303,  1336,  1304,  1591,
    1340,  1345,  1585,  1311,  1348,  1585,  1329,  1308,  1318,  1300,
    1299,  1337,  1307,  1309,  1319,  1320,  1321,  1322,  1323,  1338,
    1292,  1341,  1343,  1324,  1325,  1326,  1327,  1328,  1295,  1296,
    1297,  1298,  1312,  1335,  1306,  1317,  1294,  1293,  1305,  1314,
    1315,  1316,  1313,  1330,  1331,  1332,  1333,  1334,  1291,     0,
       0,  1383,   799,     0,     0,   806,   827,   828,   821,   823,
       0,  1249,  1281,  1283,   840,  1277,  1278,  1279,     0,  1596,
    1242,     0,  1243,   848,  1245,   849,   846,   847,     0,  1249,
    1495,   908,   910,   909,   903,   905,   911,   914,   889,   901,
     897,   895,  1289,   664,   891,  1398,  1559,   928,  1379,   664,
    1591,   954,   955,   957,   959,   960,   956,   958,   949,  1591,
     945,     0,   991,     0,   993,   992,   994,   985,   986,     0,
       0,   971,  1123,  1561,     0,     0,  1005,  1249,  1495,  1595,
       0,  1032,   665,  1039,  1040,  1043,     0,  1035,  1234,  1233,
    1042,  1048,  1228,     0,     0,  1276,     0,     0,     0,  1083,
       0,     0,     0,  1108,     0,  1112,  1111,  1102,     0,  1539,
    1276,  1149,  1148,  1155,  1156,  1157,     0,  1249,  1495,     0,
    1482,     0,  1157,  1224,  1214,  1213,  1219,     0,  1221,  1222,
    1229,  1503,  1484,   199,     0,   208,   209,   207,  1539,   502,
     513,   514,   512,   518,   594,  1539,   585,   583,   584,   586,
    1555,     0,  1539,     0,   597,   589,  1555,   590,     0,   593,
     598,   596,   591,   595,     0,   592,     0,   580,   608,   603,
     606,   605,   604,   607,   582,   609,     0,   445,   446,  1521,
     434,   447,   443,   441,  1544,   439,  1411,  1412,  1413,  1364,
    1352,  1357,  1358,  1359,  1360,  1363,  1441,     0,   467,   333,
       0,   735,  1245,   726,   728,  1242,   732,   722,   762,  1539,
     751,   752,  1539,   763,   753,   754,   757,   767,   764,   755,
       0,   765,   756,   766,   748,   749,   721,  1556,     0,     0,
       0,   739,   740,  1420,  1405,  1419,  1467,  1495,     0,  1471,
       0,  1467,  1467,     0,  1464,  1467,  1467,  1467,     0,  1467,
    1467,  1250,   772,  1252,  1249,   784,     0,  1339,  1586,  1342,
    1344,   789,   787,   794,   795,   639,     0,   805,   804,  1215,
    1216,   809,   807,     0,   826,     0,   831,   664,   664,   841,
     839,  1280,   855,   855,   855,   855,  1539,   860,   873,   874,
     861,     0,  1539,   864,   865,   868,   866,     0,   867,   857,
     858,   850,   856,   664,  1246,  1241,     0,   879,     0,  1289,
    1289,   907,   664,   904,   899,     0,   937,     0,     0,   961,
       0,     0,     0,   987,   989,     0,   981,   997,   982,   983,
     976,   977,   997,  1115,  1539,     0,  1562,  1122,  1544,  1006,
    1009,     0,     0,  1023,  1033,  1030,   667,     0,     0,  1050,
    1049,  1265,  1267,  1067,  1262,  1263,  1074,  1072,     0,  1289,
    1085,  1289,  1079,  1087,  1100,  1101,  1103,  1491,  1141,  1256,
       0,  1495,  1163,     0,     0,  1483,  1183,  1184,     0,  1187,
    1190,  1194,  1188,  1220,  1559,  1223,  1235,  1507,   205,     0,
     226,   227,   223,     0,     0,   504,     0,  1576,     0,  1539,
     587,   588,     0,   611,  1539,  1589,   612,   610,   438,     0,
     432,   448,   444,  1539,   433,   440,  1442,  1539,   462,   314,
    1240,   733,     0,     0,  1285,  1285,   750,   745,   744,   746,
    1460,  1249,  1468,     0,  1480,  1465,  1458,  1478,  1459,  1461,
    1462,  1475,  1476,  1463,  1457,   664,  1253,  1248,   773,   782,
    1591,     0,  1591,     0,   796,   797,     0,   801,   800,   802,
    1217,  1218,   812,   810,   664,   824,   825,  1282,  1284,  1242,
    1242,  1242,  1242,     0,   862,   863,     0,  1285,  1285,   859,
    1244,   664,  1249,  1367,  1249,  1367,   906,   912,   902,   930,
     938,   940,   947,   950,   951,  1529,   962,   943,   948,   997,
    1423,  1424,   997,     0,   980,   978,   979,   984,  1125,     0,
    1563,  1539,  1249,  1022,  1016,     0,   666,  1044,     0,     0,
    1056,     0,   664,   664,  1068,  1066,  1264,  1075,  1070,  1073,
    1080,   664,  1089,  1088,  1492,     0,     0,  1142,  1133,  1257,
    1159,  1259,     0,  1249,  1249,  1174,  1482,  1186,  1537,  1192,
    1537,  1256,     0,  1272,  1274,  1238,  1236,  1269,  1270,  1237,
    1508,     0,   224,   501,  1539,     0,   506,   511,  1555,   547,
     567,   562,  1511,     0,     0,  1539,  1557,  1539,     0,   517,
     523,   524,   525,   534,   526,   528,   531,   519,   520,   521,
     527,   530,   548,   532,   535,   522,     0,   529,   533,  1432,
     602,  1430,  1431,   618,   601,   613,   623,   452,   449,   450,
       0,     0,   759,   758,   761,     0,   760,   774,  1469,  1251,
     664,  1347,  1591,  1350,  1591,   798,   813,   791,   664,   808,
     854,   853,   852,   851,   870,   869,   872,   871,  1247,   881,
       0,   880,     0,   664,   941,   935,   952,  1530,     0,   996,
     988,   997,   999,     0,     0,  1128,  1124,  1119,  1010,  1025,
       0,     0,  1051,  1539,  1058,     0,  1052,     0,  1055,  1266,
    1268,   664,  1086,   664,  1135,  1136,  1137,  1138,  1139,  1140,
     664,  1160,  1151,  1260,  1255,  1158,  1165,  1164,  1185,     0,
    1537,  1189,     0,  1196,  1208,  1205,  1207,  1206,  1201,  1204,
     664,   664,  1239,  1226,  1271,  1232,  1231,  1546,     0,  1539,
    1539,   508,   546,  1539,   568,   566,   563,   564,  1541,   556,
    1539,  1289,     0,     0,     0,     0,   549,     0,     0,   554,
     557,   560,   621,   619,   620,   622,     0,   616,   614,   615,
     617,     0,   451,   442,   468,  1546,  1254,  1346,  1349,   811,
    1249,  1249,   939,     0,   995,  1000,     0,  1539,  1126,     0,
       0,  1116,  1118,  1024,     0,     0,  1061,  1059,  1060,  1054,
    1053,  1081,  1090,  1258,   664,  1191,     0,  1195,  1197,  1181,
    1273,  1275,  1547,  1548,  1230,   503,     0,     0,  1539,   499,
       0,   555,     0,   552,  1495,   550,   551,   541,   539,   540,
     542,   538,   543,   537,   536,     0,   561,   559,   558,   600,
     599,  1286,   883,   882,   953,   998,     0,  1129,  1539,  1120,
    1289,  1057,  1062,  1047,  1261,  1193,   505,   507,     0,   545,
     544,   565,     0,  1127,     0,  1045,   509,     0,  1130,   553
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
     544,   957,   814,  1157,  1364,   545,   953,   546,  1369,  1370,
    1645,  1164,   547,   548,   549,   550,   961,  1160,  1902,   551,
     552,   553,   554,   555,   556,   557,   558,   829,   559,   138,
     108,   109,   110,   111,   149,   112,   393,   394,   467,   113,
     114,    31,    66,   154,    84,   239,   159,   120,   160,   121,
     164,   248,   337,   338,   691,   339,  1400,   886,   574,   340,
     483,   341,   697,   342,   343,   692,   878,   879,   880,   881,
     344,   345,   346,    83,   240,   161,   162,   163,   246,   321,
     472,   474,   322,   323,   665,   405,   406,   569,   870,   324,
     568,   666,   667,   668,   993,   669,   670,   671,   672,   673,
    1690,   674,   985,  1379,  1924,  1691,  1692,  1693,  1694,  1920,
    1695,  2118,  2119,   675,   676,   860,   677,   678,   679,   572,
    1001,   874,   875,  1928,   680,   681,   118,   311,   158,   399,
     244,   470,   564,   565,   566,   832,   977,   978,  1169,  1170,
    1087,   979,  1649,  1905,  2076,  2221,  2299,  1373,  1652,  1173,
    1376,  1907,  2097,  2098,  2314,  2099,  2100,  2101,  2102,  2305,
    2103,  2104,  2105,  2106,  2239,  2240,  2228,  2107,  2108,  2225,
     491,   315,   567,   625,   835,   836,   837,  1175,  1377,  1684,
    2251,  2246,  1685,    51,   255,   432,    87,   124,   123,   166,
     167,   168,   252,   351,   126,   353,   496,   497,   588,   589,
     590,   591,   592,   890,  1591,  1592,  1856,   593,   753,   754,
     891,  1011,  1208,  1421,  1422,  1417,  1734,  1735,  1205,   755,
     892,  1030,  1231,  1229,   756,   893,  1038,  1452,   757,   894,
    1510,   758,   895,  1241,  1512,  1773,  1774,  1775,  1515,  1781,
    1974,  1972,  2138,  2137,   759,   896,  1051,   760,   897,  1052,
    1518,  1519,   761,   898,  1053,  1247,  1250,   762,   763,   764,
     899,  1790,   765,   900,   766,   901,  1060,  1530,  1809,  1810,
    1258,   767,   902,  1064,  1265,   768,   903,   769,   904,  1069,
    1070,  1271,  1272,  1273,  1553,  1551,  1822,  1274,  1544,  1545,
    1821,  1548,   770,   905,  1076,   771,   906,   772,   907,   773,
    1082,  1557,   774,   909,   775,   911,  1559,  2001,  2153,  2155,
     776,   912,  1282,  1568,  1829,  2003,  2004,  2005,  2007,   777,
     913,   778,   914,  1089,  1288,  1289,  1290,  1580,  1840,  1841,
    1291,  1577,  1578,  1579,  1834,  1292,  2014,  2266,   779,   915,
     780,   916,  1096,   781,   917,  1098,  1297,   782,   918,  1100,
    1303,  1590,  2024,   783,   919,  1103,  1306,  1855,  1104,  1105,
    1106,  1594,  1595,   784,   920,  1604,  2030,  2174,  2276,  2333,
     785,   921,   786,   922,  2035,   787,   923,  1605,  2038,   788,
     789,   924,  1117,  2181,  1323,  1607,  2041,  1872,  1873,  2183,
    1321,   790,   925,  1122,  1123,  1124,  1125,  1335,  1126,  1127,
    1128,  1129,   791,   926,  1093,  2018,  1293,  2272,  1582,  1843,
    2165,  2271,   792,   927,  1336,  1620,  2045,  2048,   793,  1136,
    1135,  1339,   794,   930,  1138,  1139,  1879,  2192,   795,   931,
    1142,  1345,   796,   933,   797,   934,   798,   935,   799,   936,
    1350,   800,   937,  1352,  1886,  1887,  1632,  1889,  2059,  2201,
    2061,  2289,   801,   802,   939,  2208,  1150,  1355,  1636,  1782,
    1973,  1894,   803,  1638,   804,   805,   941,  1316,  1896,  2162,
    2065,  2213,  1711,  1533,  1534,  1813,  1815,  1991,  1762,  1763,
    1955,  1957,  2130,  2050,  2051,  2190,  2194,  2284,  1863,  1864,
    2032,  1865,  2033,  2066,  2067,  2210,  2068,  2211,  1524,  1525,
    1526,  1787,  1527,  1788,  2124,  1084,  1085,  1040,  1041,  1236,
    1237,  1483,  1484,  1485,  1486,  1487,  1183,  1387,  1428,  1031,
    1054,  1251,  1112,  1118,   396,   397,  1130,  1131,  1279,  1107,
    1044,  1045,   298,   299,   479,  1166,   486,   276,  1078,  1079,
    1032,  1056,  1186,  1425,  1744,  1842,  2009,  1062,  1108,  2110,
    1034,  1013,   855,   987,   988,  2112,  1035,   872,   873,  1036,
    1214,  1216,  1432,  1446,  1441,  1438,   247,  1888,  1362,  1234,
    1314,  2046,   225,  1253,   995,   388,   413,  1363,   265,  2071,
    1819,   422,   238,   685,  1209,   615,   169,   612,   291,   306,
    2158,   145,   308,   887,   581,    43,   453,   609,  2294,   577,
    1158,   419,  1738,   233,   230,  1847,   968,   185,  1255,   852,
    1396,   282,   683,   695,   523,   236,  1769,  1281,  1178,   605,
     850,  1531
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -2044
static const yytype_int16 yypact[] =
{
   -2044,   297,    24, -2044,  -155,   224,   142, -2044, -2044, -2044,
     474,   474,   694,   694, -2044, -2044,   590, -2044, -2044, -2044,
   -2044,   711,   711,   380,   872,   872,   705,   527, -2044,   980,
     952, -2044, -2044, -2044, -2044,   -79,   748,   971,   701,   855,
     855, -2044,   757,   231,   766,   772,   886,   792, -2044,   432,
    1076,   944,  1126, -2044,   502, -2044, -2044,   981, -2044, -2044,
   -2044,   843, -2044, -2044, -2044,   948,   863, -2044,    46, -2044,
     534,   474,   694, -2044, -2044, -2044, -2044,   794, -2044,  1145,
     288,   873,   993,  1097,   910, -2044, -2044,  1016,   694, -2044,
   -2044, -2044,   917,   922,   927,   928,   942, -2044, -2044, -2044,
   -2044, -2044,  1032,   951,  1198,  1067,  1002,   751, -2044,   361,
   -2044, -2044, -2044,    69, -2044, -2044,   962,  1062,  1186, -2044,
     471,   953, -2044,    81,    81,   983,   973,   975,   872, -2044,
     385,  1244,   163,  1398,  1151, -2044, -2044,   984, -2044,  1155,
    1157,  1037,  1165,  1040, -2044,  1050, -2044, -2044, -2044,  1425,
   -2044, -2044, -2044, -2044, -2044, -2044,   995,  1096,  1121, -2044,
     910, -2044, -2044, -2044, -2044, -2044,   132, -2044,   321,   -91,
     196, -2044, -2044, -2044, -2044,  1082,  1242, -2044,   349, -2044,
     661, -2044, -2044, -2044, -2044,   146,   174, -2044,   -19, -2044,
   -2044, -2044,  1003,  -163,  1350,  1018,  1242,  1242,  1018,  1077,
    1099,  1242,  1242,  1242,  1242,  1242,  1018,  1242,  1407,  1242,
   -2044,   892, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044,  1018,  1032,   288,  1028, -2044,
    1028,  1028, -2044,  1235,  1028, -2044,  1387, -2044,  1300,   471,
     953, -2044,  1022,  1122,  1128,   953,   440,  1051,  1061, -2044,
    1242,  1109,  1201, -2044, -2044,  1376,   855,  1242,  1250, -2044,
     745, -2044, -2044,  1125, -2044,  1242,  1278, -2044,   633, -2044,
   -2044, -2044, -2044,  1038,  1255, -2044, -2044,  1018,  1018,  1242,
    1242, -2044,  1242,  1028,  1431,  1018,  1018,  1028,  1242,  1028,
   -2044,  1018,    26, -2044, -2044, -2044, -2044,   521,  1028, -2044,
   -2044,  1028,  1228,  1103,  1229, -2044,   910, -2044,   910, -2044,
   -2044,   953, -2044,  1052,  1161, -2044, -2044, -2044,  1051, -2044,
   -2044, -2044,   -12,    33, -2044, -2044,  1387,  1242,   878,   878,
    1242,    35,  1269,  1242,  1497,  1247, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044,   967,   169,  1242,
   -2044,  1083,  1072, -2044,   944,  1250, -2044, -2044, -2044, -2044,
    1028, -2044, -2044, -2044, -2044, -2044,  1242, -2044, -2044,   941,
    1028,  1292, -2044, -2044, -2044, -2044, -2044,  1028, -2044, -2044,
      92, -2044, -2044,  1010, -2044, -2044, -2044, -2044,  1028, -2044,
    1028,  1251,  1028,   910, -2044,  1233,   910, -2044, -2044,   953,
   -2044,  1080, -2044, -2044,  1458, -2044,  1464, -2044, -2044,  1250,
    1110,  1242,  1497,  1028,   413,   -46,  1250,  1115, -2044,  1242,
    1112, -2044,  1112,    60, -2044, -2044, -2044, -2044, -2044,  1250,
   -2044, -2044, -2044,   567,    68, -2044,   838, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044,   941, -2044,  1156, -2044, -2044, -2044,
   -2044, -2044, -2044,  1250, -2044, -2044,  1010, -2044,  1174, -2044,
    1463, -2044,  1028,  1028,  1028, -2044,  1250, -2044, -2044, -2044,
    1248, -2044, -2044,   964,  1124,  1158, -2044, -2044, -2044,  1028,
   -2044, -2044, -2044, -2044, -2044, -2044,  1330,    63,  1368,  1139,
   -2044, -2044, -2044,  1242,  1242, -2044, -2044,  2688,   694, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044,   578, -2044,    95, -2044,   941,  1250,
   -2044, -2044, -2044,  1242,  1010, -2044,  1269,  1253,  1167, -2044,
    1220,  1269,  1371,  1242,  1536,    90,   114,   698, -2044,  1153,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,  1216,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
    1242,  1028, -2044,  1112, -2044,  1248, -2044, -2044,  2425,  1574,
    1415,   603, -2044,  1250,   156, -2044, -2044, -2044,  1250, -2044,
   -2044,  1241, -2044,   -26,   -26,  2830, -2044,  1163, -2044, -2044,
   -2044, -2044,  1260,  3493,  1164, -2044, -2044,   578, -2044, -2044,
    1018, -2044,  1242,  1371, -2044,   832, -2044,  1242, -2044,  1242,
     764, -2044,  1242, -2044,  1242,  1256,  1242,  1242, -2044,  1425,
     358,  1242,  1181, -2044, -2044,  1405, -2044,  1400, -2044, -2044,
     -87,   650,   697,   712,   741,  1203, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044,  1293, -2044, -2044,  1250, -2044,
   -2044, -2044, -2044,  1028,  1028,  1428, -2044, -2044, -2044,   530,
   -2044, -2044, -2044,  1242,  1242, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044,   982,   -69, -2044,   204, -2044,   318, -2044, -2044,
   -2044, -2044,   176,  1407, -2044,   840, -2044, -2044, -2044, -2044,
    1548, -2044,  1423, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044,  1257, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044,  1167, -2044,  2103, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044,   354, -2044, -2044,  1357, -2044, -2044, -2044, -2044,
     570, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044,   631, -2044, -2044,
      38,  1242, -2044, -2044,   515,   339,  1028,  1627, -2044, -2044,
     -46,  1285, -2044,  1028,  1028, -2044,  1380,  1380,  1389, -2044,
    1028, -2044,   168,   -12, -2044, -2044,  1405, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
    1225, -2044, -2044,  1265, -2044,  1213,  1274, -2044, -2044, -2044,
   -2044,  1953,   318,  1648, -2044,  1320,  1320,   941,  1165,  1165,
   -2044, -2044,  1221, -2044,   318, -2044,  1284, -2044, -2044, -2044,
   -2044, -2044,    78,  1511, -2044, -2044,  1158,  1250,  1231, -2044,
    1232,  1028,  4162,  1246,   121,  1191, -2044, -2044,  4759,   910,
    1287,  4839,  4759,  1453,   810,   676,    87,  1028, -2044, -2044,
    1554, -2044,    87,  1028,  1195,  1028,  4242,  4759, -2044,  2143,
     910,  1028,   910,  1028,    99,    75,  1028,   910, -2044, -2044,
    4292,  4421, -2044, -2044,  1028,  1028,   910,  1028, -2044,   264,
    1586,  1028, -2044, -2044, -2044, -2044, -2044, -2044,  1677, -2044,
   -2044, -2044, -2044, -2044,  1028,   124,   177,   769,  1261, -2044,
    1261, -2044, -2044, -2044, -2044,  -105, -2044, -2044, -2044, -2044,
   -2044,  1028,  1242,  1525,  1525,   603, -2044, -2044, -2044, -2044,
    1510, -2044, -2044, -2044,  1250,  1302,  5491,  1254, -2044,  1028,
   -2044, -2044,  1470, -2044,  1536, -2044, -2044, -2044,  1028,  1028,
     941,  1203, -2044,   318,   -46,   -46,  1679,  1407, -2044, -2044,
   -2044,  1584,   628, -2044,  1165,  1263,  1028,  1264,  1270,  1165,
     521,  1271,  1272,  1273,  1277,  1279,  1280,  1283,  1286,  1264,
    1585, -2044,  4483, -2044, -2044, -2044, -2044,  1509, -2044,  1659,
   -2044, -2044, -2044,  1316, -2044,   521, -2044, -2044,  1289, -2044,
   -2044,   192,   910,  1597,  2199, -2044,  1388,  1424,   910,   958,
    1610,  3921,  1147,  1169,  1613,   509,  1289, -2044, -2044,    72,
   -2044, -2044, -2044,  1651, -2044, -2044, -2044,  1165,    87, -2044,
   -2044, -2044, -2044, -2044,  1358, -2044,    91,  1028, -2044,   136,
   -2044, -2044, -2044, -2044, -2044,  4759, -2044,  1353,  1621,  1710,
     879, -2044,  1359, -2044,  2331,  1624,  -134,  1364,  1365,  -142,
    1373,   788,  1588, -2044,  1424,  1588,  1028,  1628,  1337, -2044,
     839, -2044, -2044, -2044, -2044, -2044,  1526, -2044,    87, -2044,
     -50, -2044,    52, -2044, -2044, -2044,    32,  1726,  4051, -2044,
   -2044,  1028,  1630,  4505,  1028,  1599,  1008,  1665, -2044,  1447,
    1401,  1157,  1588,   631,    22, -2044,  1341, -2044,  1028,   549,
   -2044, -2044,  1242, -2044, -2044, -2044, -2044,   192, -2044, -2044,
    1028, -2044,  1250,  1405, -2044, -2044, -2044, -2044,  1670,  1165,
    5491,  5491,  5491,    44,   845, -2044, -2044, -2044,  1221, -2044,
    5491, -2044, -2044, -2044, -2044, -2044, -2044, -2044,  1420, -2044,
   -2044,  1330,   -46,  1673, -2044, -2044,   839,   787,  1347,   151,
     -17,  5491,  1383,  5491, -2044,  5491, -2044,  3218,  1349,  5491,
    5491,  5491,  5491,  5491,  5491,  5491,  5491, -2044, -2044, -2044,
    4759,  1606, -2044, -2044,  1454,  1509,  1687,  3178,  1485,  1560,
   -2044,    34, -2044, -2044, -2044,   672, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044,   765,   910, -2044, -2044,   538,
    1635,  1635,  1635,  1635, -2044, -2044,  4759,  4759, -2044, -2044,
      96,  1666,   895, -2044,  1361,   810, -2044,  1028, -2044,    23,
   -2044, -2044,   936,  1632, -2044,   839,   101, -2044,   136, -2044,
   -2044, -2044, -2044,   111,  1403,    87, -2044, -2044,  4759, -2044,
   -2044, -2044, -2044,  1441, -2044, -2044, -2044, -2044,  1028,   121,
   -2044,  1129, -2044, -2044,  1424,   192, -2044,  1598,    73,   217,
   -2044, -2044,  1028,   217,  1406, -2044,  1221, -2044, -2044,    80,
    1010, -2044, -2044,  3971, -2044,  1761,  1593,  4759,  4759, -2044,
    4517,  1028, -2044,  1639, -2044, -2044,  4759,   839, -2044, -2044,
   -2044,  1726,  1611,  1028, -2044,  1094,    93,    73, -2044, -2044,
    1698, -2044, -2044, -2044,  1028, -2044,  1542, -2044, -2044,  1028,
    1028, -2044,  1028,  1638,  1088,    33, -2044,  5217,  1157,   199,
    3218,  1369,  1369,   904, -2044, -2044, -2044,  5491,  5491,  5491,
    5491,  5491,  5491,  5133,   845, -2044,  1167, -2044,  1330,  1157,
   -2044, -2044, -2044,  1635, -2044, -2044,  1378,  1382, -2044,   839,
    1635,  1614, -2044, -2044, -2044, -2044,  1338,  1635,  1563,  1563,
    1563,   157,  1602, -2044, -2044,   348, -2044,    51,   859,  1028,
     851,    61,  1379, -2044,  1221, -2044, -2044,   212,  1381,   916,
     311,  1384,  1089,    66,   102,   573,  1385,  1136,  4745,   388,
    4759,    87, -2044,  1498, -2044, -2044, -2044, -2044, -2044,  1167,
   -2044, -2044,  1451, -2044, -2044,  1451, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,  1442,
     121, -2044,    62,  1028,  1028,   481, -2044, -2044, -2044,    65,
     945,  1477, -2044, -2044,  1720, -2044,  1587, -2044,    42,  1672,
    1635,  1583, -2044, -2044,  1590, -2044, -2044, -2044,  1669,  4745,
     483, -2044, -2044, -2044,  3082, -2044,  1457, -2044, -2044, -2044,
   -2044, -2044,    96, -2044, -2044, -2044,  1157, -2044, -2044, -2044,
    1167, -2044, -2044, -2044, -2044, -2044, -2044, -2044,  1527,  1167,
   -2044,  1456, -2044,  1811, -2044, -2044, -2044,   699, -2044,   839,
     249, -2044,   146,   447,   188,    87,    87,  4745,   566,  1153,
     910,  1723, -2044, -2044,  1854, -2044,  1683, -2044, -2044, -2044,
   -2044,  1598, -2044,  1028,   528,   765,   963,  1426,  1739, -2044,
    1429,   839,   850, -2044,   348, -2044, -2044, -2044,  4759,  1242,
     765, -2044, -2044, -2044, -2044,   -95,  1028,  4745,   636,  1466,
    1861,  1028,   456, -2044, -2044, -2044,  1564,  1565, -2044, -2044,
    1129, -2044,   200, -2044,   662, -2044, -2044, -2044,  1242,  1701,
   -2044, -2044,  1250, -2044, -2044,  1242, -2044, -2044, -2044, -2044,
    1563,  1223,  1242,  1191, -2044, -2044,  1563, -2044,  1250, -2044,
   -2044, -2044, -2044, -2044,  1028, -2044,  1028, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044,  1028, -2044, -2044,  1726,
   -2044,  1675, -2044,   188,  1371,   188, -2044,  1221, -2044, -2044,
     859,   831,   831,  1369,  1369,  1369, -2044,  1160,  1471, -2044,
    1028, -2044,  1590, -2044, -2044,  1635, -2044, -2044, -2044,  1242,
   -2044, -2044,  1242, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
       7, -2044, -2044, -2044,  1338, -2044, -2044, -2044,   192,   192,
     192, -2044, -2044, -2044, -2044, -2044,  1264,  1388,  5318, -2044,
    1028,  1264,  1264,  5491, -2044,  1264,  1264,  1264,   422,  1264,
    1264, -2044, -2044,  1612,  4745, -2044,    87, -2044, -2044,   519,
     544, -2044, -2044,  3699, -2044,   641,    39, -2044, -2044, -2044,
   -2044,  1127, -2044,  1550, -2044,  1537, -2044, -2044, -2044, -2044,
   -2044, -2044,   466,   466,   466,   466,  1242, -2044, -2044, -2044,
   -2044,  1243,  1242, -2044, -2044, -2044, -2044,    58, -2044,  1672,
   -2044, -2044, -2044, -2044, -2044, -2044,  4759, -2044,  4759,    96,
   -2044, -2044, -2044,  3082, -2044,  1028,  1757,  1448,   671,  1774,
    1450,   120,   839, -2044, -2044,  1837, -2044, -2044, -2044, -2044,
     249, -2044,  1712, -2044,  1242,  1603, -2044, -2044,  1371,    87,
   -2044,  4759,   358,   512, -2044, -2044, -2044,  1028,  4759,   490,
   -2044, -2044, -2044,  1748,  1629, -2044,  1749, -2044,  1650, -2044,
   -2044, -2044, -2044,  1429, -2044, -2044, -2044,  1631,  1750,  1608,
    1595,  1388, -2044,  4759,   120, -2044,  1616, -2044,   839, -2044,
    1785,  1508, -2044, -2044,  1157, -2044,   858,  1896, -2044,  1091,
   -2044, -2044, -2044,  1250,  1788,  1685,  1839,  5234,   -74,  1242,
   -2044, -2044,   -74, -2044,  1242,  1302, -2044, -2044, -2044,  1465,
   -2044, -2044, -2044,  1242, -2044, -2044, -2044,  1242, -2044, -2044,
   -2044, -2044,   -74,   -74,   129,   129, -2044, -2044, -2044, -2044,
   -2044,  1477, -2044,  1204, -2044, -2044, -2044,   859, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
    1167,  1752,  1167,  1755, -2044, -2044,  4759, -2044, -2044, -2044,
   -2044, -2044,  1786, -2044, -2044, -2044, -2044, -2044, -2044,  1635,
    1635,  1635,  1635,   -74, -2044, -2044,   -74,   129,   129, -2044,
   -2044, -2044,  4745,  1589,  4745,  1591, -2044, -2044, -2044, -2044,
   -2044,  1780, -2044,   671, -2044,  1818, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044,   120,  1129, -2044, -2044,  1129,   -11,  1028,
   -2044,  1242,  4745, -2044, -2044,   966,  3707, -2044,  1872,  1682,
    1705,    13, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044,  1028,  1345, -2044, -2044, -2044,
    1779,  1660,  1028,  1477,  4745, -2044,  1861, -2044,  1368,  1831,
    1368,  1608,   704, -2044, -2044,  1781, -2044,  1667, -2044, -2044,
   -2044,   702, -2044, -2044,  1242,  1841,  1709, -2044,  1071, -2044,
    1730,  1075,  1497,  1742,  1499,  1242,  1165,  1242,  1028, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044,  1545, -2044, -2044, -2044, -2044,   806, -2044, -2044, -2044,
   -2044, -2044, -2044,   520, -2044,   552, -2044, -2044,  1465, -2044,
    1028,   318, -2044, -2044, -2044,   -74, -2044, -2044, -2044, -2044,
   -2044, -2044,  1167, -2044,  1167, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
    4759, -2044,  4759, -2044, -2044, -2044, -2044, -2044,  1887,  1129,
    1129, -2044,  1534,  1634,   910,   514, -2044, -2044, -2044, -2044,
    1601,  4759, -2044,  1242,   935,  1702, -2044,  1706, -2044, -2044,
   -2044, -2044, -2044, -2044,  1028, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,  1028,
    1368, -2044,  1028,  1800, -2044, -2044, -2044, -2044, -2044,   910,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044,  1130,  1250,  1242,
    1242,  1776, -2044,  1242, -2044, -2044, -2044, -2044,   603, -2044,
    1242, -2044,  1028,  1028,  1227,  1768, -2044,  1658,  1250,   806,
   -2044, -2044, -2044, -2044, -2044, -2044,   -74, -2044, -2044, -2044,
   -2044,   -74, -2044,  1028, -2044,  1130, -2044, -2044, -2044, -2044,
    1477,  1477, -2044,  4759,  1129, -2044,  4759,  1242,   910,   910,
    1645, -2044,  1028, -2044,  1530,  1028,  1814, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044,  1028, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044,  1250,  1250,  1242, -2044,
    1250, -2044,  1250, -2044,  1388, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044,  4759, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044,   121,   910,  1242, -2044,
   -2044,  1028, -2044, -2044, -2044, -2044, -2044, -2044,  1250, -2044,
   -2044, -2044,  1906, -2044,   121, -2044, -2044,  4759, -2044, -2044
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -2044, -2044, -2044, -2044,  1950, -2044, -2044, -2044,    48, -2044,
   -2044, -2044, -2044, -2044,  1604, -2044, -2044, -2044,  1268, -2044,
   -2044,    88,  1935, -2044, -2044,  1907,   250, -2044, -2044, -2044,
   -2044, -2044,  1767,  1832, -2044, -2044,  1787,   743, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044,  1775, -2044, -2044, -2044, -2044,
    1756, -2044, -2044, -2044, -2044, -2044,   209,   638, -2044, -2044,
   -2044, -2044,  1455, -2044, -2044,  1375,   817, -2044, -2044, -2044,
   -2044, -2044, -2044,  1529, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044,  1838, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,   614, -2044,
     606,   823, -2044, -2044, -2044, -2044, -2044,  1019,    79, -2044,
    1370, -2044, -2044, -2044, -2044, -2044, -2044,   130, -2044, -2044,
    1754, -2044,  1874, -2044, -2044, -2044, -2044,  1592, -2044, -2044,
    1871,   227, -2044, -2044, -2044, -2044,  1747, -2044,  1938,  1828,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,  1111, -2044,
   -2044, -2044,  1412, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044,   796, -2044, -2044, -2044,  1681,
   -2044, -2044,  -560, -2044, -2044,  -308, -2044, -2044, -2044,  -474,
   -2044, -2044, -2044, -2044, -2044, -2044, -1329, -1316,  1140, -1309,
   -2044,   100, -2044, -2044, -2044,   305,   309, -2044,   419, -2044,
     317, -2044,  -109, -1305, -2044, -2044, -1300, -2044, -1299, -2044,
   -2044, -2044,  1138, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044,  1449, -2044, -2044, -2044,  1039, -2044,
    -924, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,   -85, -2044,
   -2044, -2044, -2044, -2044, -2044,  -222, -2044, -2044, -2044, -2044,
     276, -2044, -2044, -2044, -2044, -2044,  1182, -2044, -2044, -2044,
   -2044, -2044, -2044,   159, -2044, -2044, -2044, -2044, -2044,  1895,
    1106, -2044,   245, -2044, -2044, -2044, -2044,  1528, -2044, -2044,
   -2044, -2044, -2044, -2044, -1173, -2044, -2044,   165, -2044, -2044,
   -2044, -2044,   961,   601,   616, -2044, -2044,   301, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044,   976, -2044, -2044,   266, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044,  -115, -2044,   232,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
     768, -2044, -2044,   774, -2044, -2044, -2044, -2044,   495,   230,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044,    47,   770, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044,   771, -2044, -2044, -2044,   213,
   -2044, -2044,   477, -2044, -2044, -2044, -1439, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2043,   959,
   -2044, -2044,   205, -2044, -2044,   463, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044,   708, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044,   744, -2044,   193, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,   943,
   -2044,   940, -2044, -2044,  1144, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044,   934,   441, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044,    18, -2044,   443, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044, -2044,    30, -2044, -1202,
   -2044, -2044, -1246, -1116, -1123, -2044,   364, -2044, -1372, -2044,
   -2044, -2044, -2044,    17, -2044, -2044, -2044, -2044,   -94, -2044,
   -2044,   215, -2044, -2044, -2044, -2044,    14, -2044,  -454, -1756,
   -2044, -2044,   556, -2044,  -959, -1291,  -853, -1203, -2044, -2044,
   -2044, -1217, -1214, -1212, -1193, -1191,    28,  -230,    12,  -124,
   -1114,  -890,   197,   968, -1047,   -84, -2044, -1111, -2044,  -830,
   -2044,   844,  -224,  -227, -2044, -2044,  -626,   624,  -862,  -991,
    -624,  -847, -2044, -2044,   472, -1083, -1641,  -998,  -852,  -800,
     425,  -629,  -195, -2044,  1098,  -178,  -673,  -675,  -310,  -340,
    -972, -2044, -2044, -2044, -2044, -2044,  1843, -2044,   448,   856,
   -2044, -2044, -2044, -1695,  1230,    40,  1764,   801,  -447, -2044,
    1026,  -410,  1478, -2044,  -645, -2044, -1088,  1104,  -408,   909,
   -2044, -2044,  -719, -2044, -1405,  -175,  -568,  -518,  -153,  -792,
   -2044,   710, -1321,  -827, -1113, -2044,  1276,  2043,  -794, -2044,
   -2044, -2044, -2044, -2044, -2044, -2044,   640, -2044,   191,  -712,
    1107,  -127
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1596
static const yytype_int16 yytable[] =
{
     122,   258,   478,   687,   302,   194,   301,   304,  1055,   908,
    1144,  1256,   871,   560,   876,   408,  1593,   616,   617,  1331,
    1503,   277,   278,  1504,   854,  1505,   283,   284,   285,   286,
     287,   940,   289,   300,   292,   300,   300,  1324,  1356,   300,
    1039,   998,   999,  1048,  1506,  1033,  1507,   882,  1678,  1340,
    1086,  1071,  1941,  1243,  1033,  1065,   372,  1227,  1077,   446,
     376,  1679,   378,  1132,  1043,   833,   194,  1546,  1680,  1097,
    1099,   389,  1681,   347,   389,   348,   122,  1682,  1683,   579,
     357,  1077,   355,  1140,  1033,   811,  1077,  1278,   300,  1269,
     360,   105,   300,  1077,   300,  1278,  1415,  1077,  1739,  1740,
      85,    22,  1637,   300,   369,   370,   300,   371,  1116,  1600,
    1572,   165,   596,   377,  1384,   450,  1448,  1541,    89,   290,
     305,  1384,   382,  1401,   500,  1967,  1004,   613,  1934,   867,
     165,  1384,  1423,   435,   446,    41,  1384,  1556,  1792, -1559,
    2069,  1278,    14,   447,  1359,  1535,  1536,  1537, -1521,  1786,
     449,   834,   410,  1539,   865,   415,   417,  1573,   420,   403,
      92,   950,   356,   186,  1716,   300,   462,  1817,   464,  1371,
     428,  1736,  1384,  1332,   429,   300,   127,   434,   165,  1987,
    1584,   165,   300,   266,  1587,  1232,  2053,  1210,   485,   991,
     484,   436,  1217,   461,   963,   300,  2163,   300,  1121,    52,
     426,   876,  1571,   614,   403, -1595,   877,     4,   598,   263,
     696,  2175,   689,   867,  1232,  1850,  1687,  1418,   480,  1337,
     300,  1513,   395,  1418, -1517,  1120, -1559,  1687,  1285,   972,
     493,   475,  1627,  1359,   253,   389,   477,   389,   487,   561,
     307,  1091,  -190,  2055,   489,   165,  1372,   877,  1294,    41,
    1277,   495,    32,  2176,   868,  1882,   973,   974,  1836,  1042,
   -1434,    18, -1595,  1630,  1629,  1686,  1329,   300,   300,   300,
   -1595,  1162,  1148,  2177,  1574,   520,   833,  1061,   190,   427,
    1712,   839,  1384,  2343,   575,   884,  1710,  1712,   562,  1307,
    1121,  1140,   272,  1424,  1712,  -191,  1232,     3,   570,  1149,
      12,  2348,  1308,  1688,    54,  1837,   451,  1143,   608,   395,
     105,  1188,   468, -1595,  1688,   437,   986,  1602,   583,   584,
    1317,    91,  1359,  1121,  1575,     4,  1715,   867, -1544,  1042,
    1199,   840,   608, -1595,   389,     5,  1764,  -210,  1278,  1909,
    1055,   599,   866, -1517,   254,  1914,   190,  1793,   600,  1546,
   -1595,  1163,  1380,  1330,   951,   174,   438,  1042,   610,   619,
    -190,  1202,   834,   439,  1968, -1521,   300,   826,   297,  1195,
    1196,   958,  2161,  1338,  2109,  1514,   -31,  1055,  1200,  1201,
    1824,  1384,    41,  1449,  1419,   622,  1826, -1521,   698,   698,
    1508,   229,  1958,   682, -1533,   688,   297,  1521,  1162,   437,
     693,  1689,   952,  2017,  1385,   356, -1521,  1172,  1055,  1397,
     267,  1385,   620,  -191,  1811,   354,   297,  1795,  2278,  1538,
    1540,  1385,  1071,  2164,  1776,   297,  1385,   810,  1242,   869,
     404,  1935,   815,  1586,   816,   440,   269,   820,  1897,   821,
     438,   823,   824,  1825,   437,  1326,   830,   439, -1566,  1558,
    2178,  1588,  1420,     5, -1519,  1333,  1055, -1521,  1420,   856,
    1765,   975,  1385,  1360,  -210,   297,   578,  1286,   275,  1931,
     853, -1539,  1838,  -632,  1969,   407,  1334,   690,  1163,  1597,
      86,    89,  1988,  1612,  1794,   438,  1617,  1005,   861,   862,
    1621,  1622,   439,  1624,   297,   597,  1835, -1521,   441,  1628,
    1542,  1386,   494,   959,  1543,  1188,  1188,  1188,  1746,   264,
    1270,   501,  1576,   437,   190,  1188, -1521,   297, -1473,   440,
    1601, -1521,   297,  1756,   152,   981,  1639,   442,  1874,   297,
    1287,  1326,   190,   297,   275,   297,  1188,  -630,  1188,   106,
    1188,   297,  1434,  1853,  1188,  1188,  1188,  1188,  1188,  1188,
    1188,  1188,  1360,    55,   438,  1050, -1544,   997,  1266,  1757,
    1055,   439,   297,   297,   440,   883,  -190, -1521,   443,  2127,
    2159, -1521,  1385,  2160,  1092,  -776,  1398, -1521,  2090,  1050,
    2042,  1426,   441,   960,  1743, -1517,   594,  -632,  1433,   962,
     928,  2091,  1712,   485,   175,  1278,   965,   966,  2092,  1203,
      63,  1919,  2094,   971,   190,   177,  1709,  2095,  2096,  2341,
    1326,   442,   106,  1375,  1977,  1978,  1546,   190,   827,  -191,
    2149,   300,  2151,   976,    16,   300,   450,   441,   300,   300,
     175, -1521,   955,   440,   297,   300,   954,    56,   107,    63,
    1990,  1360,   297,  1384,  1779,  1951,  1189,  1845,  1555,  1998,
    2168,  -630,   443,  2199,  1861,  2202,   442,   980,  1206,    75,
    1839,  1388,  1389,  1390,  1391,   521,  1392, -1481, -1481, -1479,
    1818,  1385,  1326,    88,  1608,  1960,   828, -1533,  1608,    13,
    1772,  2196,  2197,  1561,  1708,  1776,  1562,  1563, -1595,  2029,
    1197,   297,   481,   250, -1517,    75,   441,   443,   492,  1046,
    1962,  2269,  1992,   929,  1994,  1697,   498,   176,  1572,  1008,
      23,   107,  1188,  1188,  1188,  1188,  1188,  1188,  1188,  1267,
    1094,   386,  2264,  1849,  1109,   442,  1113,  1154,  1113,  1119,
   -1595,  1094,  1846,   601,  1326, -1595,  1252,  2022,    26,   251,
    1937,  1938,  1939,   176,  1165,   307,  1113,  1767, -1566,  2012,
   -1595,  1696, -1595,  1851,   858,  1573, -1595,  2223,   938,   300,
    1388,  1389,  1390,  1391,  1050,  1392,   443,  2242, -1477,  2054,
    1780,  1876, -1595,   504,  1940,  1959,   300,   485,   485,  1945,
    1946,  2062,  2129,  1948,  1949,  1950,    64,  1953,  1954,  1366,
     297,  1862,  1110,   482,  1192,  2286,  1745,  1167,   387,  2247,
    1783,  2139,  2270,  1961,   259,  2057,  1176, -1595,  1207,   300,
     300,  1913,  1402,  1403,   505,  1057,   150,   451,  2148,  2243,
     956,   506,   279,  1883,    55,    64,   942,   177,  1963,  2185,
     288,  1252,  2186,  1952,  2187,    29,  1111,    65,  1114,   623,
    1189,  1189,  1189,  1134,   362,     5,  2125,  2125,  1827,   295,
    1189,  2248,  1146,  2188,  1404,  2189,  1405,  1830,  1278,  2179,
    2180, -1517,  1185,  2140,  2141,  2142,  2143,   943,  2182,   363,
    2204,  1189,  1574,  1189,   944,  1189,   859,  1435,     5,  1189,
    1189,  1189,  1189,  1189,  1189,  1189,  1189,  1155,  2322,  2323,
    1406,  1407,  1408,   508,  -990,   317,  1367,   190,   297,  2125,
    2125,   367,   368,   195,  1326,  1326,   175,  1529,    56,   374,
     375,  2205, -1595,  1899,  1252,   381,   384,   196,   197,  2206,
    1965,  1119,  1575,   262,  1564,  1565,  1993, -1595,  1995, -1517,
      19,   190, -1595,  1385,   356,  -990,  1326,  1409,   356,  1410,
    2303,    33,  -990,  1566,  1567,  1560,   945,  1411,  1561,   198,
    1121,  1562,  1563,   190,   119,   812,   509,  2256,   618,  1283,
    2216,  1055,   503,  1365,  1528,  2259,   529,  1997,  1245,  2244,
    2245,    75,  1072,  1073,    30,   485,  2126,  1110,  1522,  1529,
    2262,  1900,    34,  1901,  1252,  1745,  1074,  1368,   199,   200,
     175,   201,  2207,  1055,  1374,  2215,  1516,   530,  1184,   813,
     202,  2249,  2250,   262,   452,  1156,    20,   300,  2281,   946,
    2282,  2028,  2063,   250,  -990,  2209,  2040,  2283,   841,   176,
     885,  1412,  1388,  1389,  1390,  1391,   512,  1392,  2146,  2147,
   -1474,  1523,  1075,   504,   437,  1121,   310,  2290,  2291,  2345,
    1698,   316,   356,   203,   204,  1299,  1312,  1189,  1189,  1189,
    1189,  1189,  1189,  1189,   205,    75,  1185,  1185,  1185,   251,
    1218,  1861,   325,    36,  2237,   843,  1185,  1653,   842,    93,
     146,  1522,    38,  1188,   505,   438, -1535,  -990,  1188,   947,
     845,   506,   439,   817,  1046,  1239,  1300,  1185,  1517,  1185,
     818,  1185,  1313,   507,  1301,  1185,  1185,  1185,  1185,  1185,
    1185,  1185,  1185,   176,    44,  2238,  -990,   398,   326,   847,
    1576,  2334,  2114,   190,  1046,   844,   261,  2268,  1520,  2135,
    1115,  2184,  2064,   327,  1523,   147,   148,   139,   538,   206,
     846,    94,  2122,  2123,   424,  1844,   437,  1598,  1152,   140,
      45,  -990,  1646,  1646,   297,  1318,   119,  -990,  1522,   863,
    2109,  1866, -1539,   508,   440,   425,    49,  1326,  2011,   848,
     141,  1046,    50,   328,  1599,  1326,  1878,  1302,   142,  1643,
     864,    95,   468,    96,   300,   300,  1923,   438,    41,    46,
    -345,  -345,  1357,  2144,   439,  1784,  2145,    47,  1413,  1564,
    1565,  1606,  1381,  1382,  1383,   469,    68,   411,  1862,   412,
     358,  1523,  1394,  1867,   867,  1785,  2169,  1750,  1566,  1567,
    1753,  2011,    53,  1326,  1067,  1758,   509,   441,  1068,   510,
     511,    59,  2327,  1868,   809,  1430,  2170,    60, -1539,  1414,
    1606,  1437,  1439,  1440,  1442,   409,   602,  1445,  1447,  1427,
     416,   607,    61,  1431,   207,   143,   442,    62,  2131, -1539,
    2133,  1443,  1444,  1634,  1615,     5,   440,  1635,  1616,  2233,
    2260,    72,  2261,  1185,  1185,  1185,  1185,  1185,  1185,  1185,
      10,  2217,   249,  1015,    10,    41,   249,  1015,   319,   320,
     329,   297,  1390,  1391,   208,  1392,   512,   443,   454,  1017,
     455,    75,   330,  1017,  1388,  1389,  1390,  1391,    79,  1392,
    1388,  1389,  1390,  1391,    81,  1392,  1393,    82,  1388,  1389,
    1390,  1391,  1748,  1392,   103,  1046,  1012,  2307,  2308,   441,
    1049,  1650,  1651,  1050,  2274,  2255,  1063,  1348,   115,  1349,
    2021,  1080,  1081,  1270,   209,  1549,   117,  1080,  1088,  1090,
    2011,  1737,  2222,  2309,  1049,  2226,  2227,   293,   442,   116,
    1080,  2331,   119,  1388,  1389,  1390,  1391,   125,  1392,  1088,
    1145,  1699,  1147,  2292,  2293,  1388,  1389,  1390,  1391,  1718,
    1392,  1719,   129,  1752,  1720,  1018,  1910,   130,  1911,  1018,
     331,   332,   131,   132,  1721, -1426, -1426, -1426, -1426,   443,
     437,   134,  1970,   333,  1971,   334,  1984,   133,  1985,  1700,
    1701,  1702,  1703,  1704,  1705,  1707,   136,   144,  1189,   195,
    1900,  1187,  1901,  1189,   137,  1646,  2324,   155,   156,  2325,
    2257,   157,  2258,   196,   197,   171,   186,  1047,   172,  1021,
     173,   438,  1022,  1021,   224,   228,  1022,   229,   439,   227,
     231,  1212,   232,   234,  1877,   235,  2319,   300,  2254,   237,
     241,  2320,   242,   243,   257,   198,    41,   274,   271,  1918,
     275,   280,  1852,   290,   525,  1023,   281,   526,  2342,  1023,
     297,   303,   305,  1903,  1906,   307,  1244,   312,   313,   314,
    1908,   349,   527,  1929,   350,   352,   356,  1912,   359,   361,
    1915,   300,   528,   364,   199,   200,   335,   201,  1880,   373,
    2349,  1459,  1460,  1080,   365,  1880,   202,   400,   390,   392,
     440,  1080,  1284,   391,  1722,   300,   336,   401,   418,  1723,
     421,  2310,  2311,  1944,   423,   430,   263,   431,   448,  1049,
    1461,   463,  1724,  1024,   466,   471,  1462,  1024,  1388,  1389,
    1390,  1391,  -362,  1392,  1932,  1325,  1755,  1933,   473,   203,
     204,   488,   476,  1080,   490,   300,   518,  1080,   522,   571,
     205,   573,  2312,  2313,   576,   563,  1343,  1464,   580,  1284,
     604,  1465,   603,   441,  1260,  1261,  1262,  1263,  1025,  1026,
    1725,   582,  1025,  1026,   606,  1388,  1389,  1390,  1391,   608,
    1392,   611,  1244,  1760,   190,  1088, -1425, -1425, -1425, -1425,
     621,   684,   442,   686,  1027,  1187,  1187,  1187,  1027,  1388,
    1389,  1390,  1391,   694,  1392,  1187,   702,  1926,   701,   806,
     822,  1983,  1028,   831,  1185,   838,  1028,  1986,  1726,  1185,
    1029,  1325,   319,   297,  1029,   206,  1187,   297,  1187,   851,
    1187,   849,   857,   443,  1187,  1187,  1187,  1187,  1187,  1187,
    1187,  1187,  1727,  1388,  1389,  1390,  1391,   888,  1392,   889,
    2301,  2128,  -842,   932,   613,   529,   964,   967,   984,  2019,
     970,   986,  2229,   983,   989,   992,  1728,  1979,  1980,  1981,
    1982,  1729,   994,  1000,  1003,  1006,  1009,  1010,  1037,  1066,
    1083,  1730,  1058,  1151,  1153,  1731,   530,  1168,  1174,  1454,
    1455,  1456,  1159,   531,  1177,  1796,  1193,  1457,  1797,   877,
    1325,  1204,  1190,  1228,  1233,  1235,  1798,  1799,  1800,  1238,
    1080,  1211,  1213,  1240,   532,  2073,  2025,  1246,  1215,  1219,
    1220,  1221,  2031,  1596,  2113,  1222,  1252,  1223,  1224,  2115,
    1244,  1225,  1257,  1254,  1226,  1458,  1264,  1609,  2120,   533,
     207,  1276,  2121,  1732,  1080,   534,  1295,  1280,  1296,  1298,
    1943, -1428,  1305,  1733,  1309,  1947,  1625,  1310,  1315,   468,
    1311,  1320,  1325,  1322,  1121,   165,  1344,  1351,  1633,  1347,
    1353,  1354,   535, -1552,  1378,  1395,  1429,  1399,  1416,   536,
     208,  1436,  2166,  1450,  1509,  1451,  1042,  1284,  1532,  1552,
    1547,  1479,   537,  1570,  1481,  1482,  1585,  1589,  1603,  1611,
    1618,  1619,  1187,  1187,  1187,  1187,  1187,  1187,  1187,  1626,
    1641,  1631,  1644,  1392,   300,  1713,   264,   538,  1714,   539,
    1801,  1648,  1717,  1737,  1325,  1419,  1749,   540,  1751,  1766,
     209,  1754,  1759,  1459,  1460,  1771,  2167,  -215,  1802,  1768,
    1761,  1789,  1812,  1523,  1747,  1814,  1816,  1820,  1828,  1831,
    1832,  1854,  1857,  1858,  1869,  1870,  1803,  1871,   541,  1884,
    1885,  1893,  1461,  1895,  1904,  1927,  1080,  1689,  1462,  1975,
    1956,  1976,  2000,  2002,  2006,  2008,  2013,  2016,  2020,  2034,
    2039,  2037,  1862,  2044,  2047,  2052,  2253,  2049,  2058,  2218,
    2056,  1463,  2060,  2070,  2074,  2075,  2077,  2117,  2132,  1464,
    2232,  2134,  2234,  1465,  1804,  2136,  2154,  2150,   542,  2152,
    2157,  2171,  2172,  2173,  2191,   300,  2200,  2193,  2241,  2212,
    2220,  2064,  2219,  2224,  2230,  2086,  2263,  2231,  1777,  1778,
    2265,  2267,  2279,  1466,  1467,  2273,  2280,  2288,  2315,  1468,
    2298,  2316,  2328,  2330,  2332,  2347,    15,    28,   433,  1469,
     273,    74,  1805,   270,   193,   260,  1470,   294,  1613,   595,
    1358,  1471,   808,   517,   226,  1642,  1647,  1361,  2072,  1161,
     819,   296,  2023,   151,   153,   465,   309,    67,   245,  1472,
     629,   630,   631,   632,   633,   634,   699,  1007,  2275,   402,
    1925,   990,  1922,  1848,  1325,  1325,  2306,  2093,  1921,  2252,
    1080,  1080,  1002,  1171,   624,  1806,  2236,  2318,   982,   170,
    1966,  2026,  1259,  1742,   585,  1807,   389,   636,  1860,   637,
     638,   639,   640,   641,   642,  1936,  1325,  1741,   300,  1964,
    2295,  1989,  1268,  1554,  2296,  2297,  1550,  1823,  2300,  1996,
    2156,  1881,  1569,  2015,  1833,  2302,  1890,  1890,   300,  1581,
    2317,  2241,  2027,  1304,  1859,  1640,  2043,  1610,  1328,  1327,
    1133,   643,  1342,  1891,  2198,  1892,  1930,  2329,  2203,  2036,
    2277,  2214,  1791,  1511,  1319,  1191,  1875,  1808,  1049,   318,
    1898,  1453,  2326,   414,  1583,  1275,   996,   825,  1194,  1916,
      76,  1917,  2321,   969,   910,  1770,  2116,     0,  1198,  -933,
       0,     0,  -933,     0,     0,  -933,  -933,  -933,  2336,  2337,
       0,     0,  2339,  2338,  2340,   468,     0,     0,     0,     0,
       0,  1046,     0,     0,     0,  1473,  1474,  1475,  1476,  1477,
       0,  1478,     0,  1479,  1480,     0,  1481,  1482,     0,  1046,
       0,     0,     0,  2344,   644,     0,     0,     0,     0,     0,
    2346,  -933,     0,  1244,  1244,  1244,     0,     0,     0,     0,
       0,     0,     0,  1187,     0,     0,     0,     0,  1187,     0,
       0,     0,     0,     0,   468,  -933,     0,     0,     0,     0,
       0,  1080,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -933,     0,     0,     0,  1014,   647,     0,   867,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1015,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1017,     0,   468,   649,     0,     0,     0,     0,     0,
    1999,     0,     0,   651,     0,     0,  2010,  1325,     0,  -933,
    -933,     0,     0,     0,     0,  1325,   652,     0,     0,     0,
       0,     0,     0,     0,  1080,     0,     0,     0,     0,     0,
       0,  1015,  1596,     0,     0,     0,     0,  -933,  -933,     0,
       0,     0,     0,     0,  -933,     0,     0,  1017,  -933,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2010,
       0,     0,     0,  1325,     0,     0,     0,  -933,     0,     0,
    1101,     0,   656,   657,   658,  -933,     0,  1018,  -933,  -933,
       0,     0,     0,  2111,     0,  -933,     0,  2111,     0,  -933,
       0,  -933,     0,     0,  -933,     0,  -933,     0,     0,     0,
       0,     0,     0,     0,     0,  1248,     0,  2111,  2111,  -933,
    -933,     0,     0,     0,     0,  -933,     0,     0,     0,     0,
       0,     0,   660,   661,   662,  -933,     0,  -933,     0,  1102,
       0,  1021,  -933,  1018,  1022,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   437,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -933,     0,     0,  2111,     0,
       0,  2111,     0,  1015,     0,     0,     0,  1023,  -933,     0,
       0,     0,     0,     0,  1019,  -357,   626,     0,     0,  1017,
       0,  1020,     0,     0,     0,   438,     0,  1021,  2010,     0,
    1022,     0,   439,     0,     0,  -933,   627,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   628,
       0,     0,   629,   630,   631,   632,   633,   634,   635,     0,
    1088,     0,     0,  1023,     0,     0,     0,  2195,     0,     0,
       0,  -933,     0,     0,     0,  1024,     0,     0,     0,     0,
    -933,  -933,     0,     0,     0,     0,  2111,     0,     0,   636,
       0,   637,   638,   639,   640,   641,   642,     0,  1101,     0,
    -933,     0,     0,  2235,   440,  1018,  -933,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1025,  1026,     0,     0,  -933,     0,     0,     0,     0,     0,
   -1595,  1024,  -933,   643,     0,  -933,     0,     0,     0,     0,
    2111,  -933,  -933,  -933,     0,     0,  1027,  -933,     0,  -933,
    -357,  -933,  -933,  -933,  -357,     0, -1041,  1047,     0,  1021,
       0,     0,  1022,     0,  1028,     0,     0,   441,     0, -1041,
       0,     0,  1029,     0,   190,   297,  1025,  1026,     0,     0,
       0,     0, -1539,  -357,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1023,   442,     0,  -357,  1284,
       0,     0,  1027, -1539,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2285,     0,   644,  2287,     0,     0,
    1028,     0,     0,     0,     0,     0,     0,     0,  1029,    41,
       0,   297,   645,     0,     0,     0,     0,   443, -1576,     0,
       0,     0,  -357,  -357,     0,  1249,     0,  2304,     0,     0,
    -357,   646,     0,     0,  -357,     0,     0,     0,     0,     0,
       0,  2111,     0,  1024,     0,     0,  2111,     0,   647,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -627,   586,
       0,  -667,     0,  -667,     0,     0,     0,     0,  -667,     0,
    1088,   648,     0,     0,     0,     0,  -667,     0,     0,     0,
       0,  2335,     0,     0,     0,     0,   649,     0,  1025,  1026,
       0,     0,     0,   650,     0,   651,     0,     0, -1595,     0,
       0,     0,  -357,     0,     0,     0,  -357,     0,   652,  -667,
    -667,     0,     0,     0,  1027,     0,     0,  -667,   653,     0,
       0,     0,     0,     0, -1041,   654,  1284,  -357,     0,  -667,
       0,     0,  1028,  -667,     0,     0,     0, -1041,     0,     0,
    1029,     0,   190,   297,     0,  -667,  -357,     0,     0,  -357,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   655,     0,   656,   657,   658,     0,     0,  -667,
       0,     0,     0,     0,     0,     0,  -667,  -667,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   659,     0,
       0,     0,     0,  -627,     0,     0,     0,  -627,     0,     0,
       0,   586,     0,  -667,     0,  -667, -1576,  -667,     0,     0,
    -667,     0,     0,     0,   660,   661,   662,     0,  -667,  -667,
       0,     0,     0,  -667,     0,     0,     0,   663,     0,     0,
     664,     0,     0,     0,     0,     0,     0,  -667,     0,  -357,
       0,  -627,     0,     0,  -667,     0,     0,  -667,  -667,     0,
    -357,  -667,  -667,     0,     0,  -667,     0,     0,     0,  -667,
       0,     0,  -667,     0,  -667,     0,     0,  -667,     0,     0,
       0,  -667,     0,     0,     0,  -667,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -667,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -667,     0,     0,     0,  -667,     0,
    -667,  -667,     0,     0,     0,     0,     0,  -667,  -667,  -667,
       0,     0,     0,     0,     0,     0,   700,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -667,     0,     0,     0,     0,     0,     0,     0,     0,  -667,
       0,     0,     0,     0,     0,  -667,     0,     0,     0,     0,
       0,  -667,     0,     0,     0,  -667,     0,     0,     0,  -627,
       0,     0,     0,     0,     0,     0,  -667,     0,     0,  -667,
       0,     0,     0,     0,     0,  -667,  -667,     0,     0,  -667,
    -667,     0,     0,     0,     0,     0,     0,  -667,  -667,     0,
       0,     0,     0,  -667,  -667,  -667,  -667,     0,     0,  -667,
       0,     0,     0,  -667,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -667,     0,     0,     0,     0,     0,     0,
       0,     0,  -667,     0,     0,     0,     0,     0,     0,     0,
       0,  -667,     0,  -667,  -667,     0,  -667,  -667,     0,  -667,
    -667,     0,  -667,     0,  -667,     0,     0,     0, -1509,  -667,
       0, -1509,     0,     0, -1509, -1509, -1509,     0,     0,  1269,
    -667,     0,     0, -1509,     0,  -667,     0,     0,     0,     0,
    -667,     0,  -667,     0,     0,     0,     0,     0,     0,     0,
       0,  -667,     0,     0,     0,     0,     0,  -667,     0,     0,
     587,     0,     0,  -667,     0,     0,     0,     0,     0,     0,
   -1509,     0,     0,  -667,     0,     0,     0,     0,  -667,     0,
       0,     0,     0,     0,     0,     0,     0,  -667,     0,     0,
       0,     0,     0,     0, -1509,     0,     0,     0,     0,     0,
    -667,     0,     0,     0,     0,  -667,     0,  -667,     0,     0,
   -1509,     0,     0,     0,  1014,  -667,     0,   867,     0,     0,
    1488,  1489,  1490,     0,     0,  -667,     0,     0,     0,     0,
       0,     0,     0,     0,  -667,     0,     0,     0,     0,     0,
       0,     0,     0,  -667,     0,  -667,  -667,     0,     0,  -667,
       0,  -667,     0,     0,     0,     0,  -667,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1491,     0, -1509, -1509,
       0,     0,  -667,     0,     0,     0,     0,  -667,     0,     0,
       0,     0,  -667,     0,     0,     0,     0,     0,     0,     0,
    1015,     0,     0,  -667,     0,     0, -1509, -1509,     0,     0,
       0,     0,   587, -1509,     0,  -667,  1017, -1509,     0,     0,
       0,     0,     0,     0,     0,  -667,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0, -1509,     0,     0,     0,
    1015,     0,     0,     0, -1509,     0,     0, -1509, -1509,     0,
       0,     0,     0,     0, -1509,     0,  1017,     0, -1509,     0,
   -1509,     0,     0, -1509,     0, -1509,     0,     0,     0,     0,
       0,     0,     0,     0,  1459,  1460,     0,     0, -1509, -1509,
       0,     0,     0,     0, -1509,     0,     0,     0,     0,     0,
       0,     0,     0,     0, -1509,     0, -1509,     0,     0,     0,
       0, -1509,  1018,  1461,     0,     0,     0,     0,     0,  1462,
       0,     0,     0,   437,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0, -1509,     0,     0,     0,     0,     0,
       0,     0,  1492,     0,     0,     0,     0, -1509,     0,     0,
    1464,     0,  1018,  1019,  1465,     0,     0,     0,     0,     0,
    1020,     0,     0,   437,   438,     0,  1021,     0,     0,  1022,
       0,   439,     0,     0, -1509,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1493,  1494,     0,     0,     0,     0,
    1495,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1496,     0,  1023,     0,   438,     0,  1021,  1497,     0,  1022,
   -1509,   439,     0,     0,     0,     0,     0,     0,     0, -1509,
   -1509,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1498,     0,     0,     0,     0,     0, -1509,     0,     0, -1509,
   -1509,     0,  1023,   440,     0, -1509,   703,     0,   704,     0,
       0,     0,     0,   705,     0,     0,     0,     0,     0,     0,
       0,   706,     0, -1509,     0,     0,     0,     0,     0,     0,
    1024, -1509,     0,     0, -1509,     0,     0,     0,     0,     0,
   -1509, -1509, -1509,   440,     0,     0, -1509,     0, -1509,     0,
   -1509, -1509, -1509,     0,   707,   708,     0,     0,     0,     0,
       0,     0,   709,     0,     0,     0,   441,     0,     0,     0,
    1024,     0,     0,     0,   710,  1025,  1026,     0,   711,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     712,     0,     0,     0,     0,   442,     0,     0,     0,     0,
       0,  1027,     0,     0,     0,     0,   441,     0,     0,     0,
       0,     0,     0,     0,   713,  1025,  1026,     0,     0,  1028,
       0,   714,   715,     0,     0,     0,     0,  1029,     0,     0,
     297,     0,     0,     0,     0,   442,   443,  1499,  1500,     0,
       0,  1027,  1501,     0,  1479,     0,  1502,  1481,  1482,     0,
       0,     0,   716,     0,     0,     0,     0,     0,     0,  1028,
       0,     0,     0,     0,   717,     0,     0,  1029,   718,     0,
     297,     0,     0,     0,     0,     0,   443,     0,     0,     0,
       0,     0,   719,     0,     0,     0,     0,     0,     0,   720,
       0,     0,   721,   722,     0,     0,     0,     0,     0,     0,
     723,     0,     0,     0,     0,     0,     0,   724,     0,   725,
       0,     0,   726,     0,     0,  -799,     0,     0,  -799,     0,
     703,     0,   704,     0,     0,     0,     0,   705,     0,     0,
       0,     0,     0,     0,     0,   706,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   727,
       0,     0,     0,   728,     0,   729,     0,     0,   165,     0,
       0,     0,   730,     0,     0,     0,     0,     0,   707,   708,
       0,     0,     0,     0,     0,     0,   709,     0,     0,     0,
       0,     0,     0,     0,     0,   731,     0,     0,   710,     0,
       0,  -799,   711,     0,     0, -1521,     0,     0,     0,     0,
     732,     0,     0,     0,   712,     0,     0,  -799,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   733,     0,     0,     0,     0,     0,     0,   713,     0,
     734,     0,     0,     0,     0,   714,   715,     0,     0,     0,
       0,     0,     0,   735,     0,     0,     0,     0,   736,     0,
     737,     0,     0,     0,     0,     0,     0,     0,   738,     0,
       0,     0,     0,     0,     0,     0,   716,     0,   739,     0,
       0,     0,     0,     0,     0,     0,     0,   740,   717,     0,
       0,     0,   718,     0,     0,     0,   741,     0,   742,   743,
       0,     0,   744,  -799,   745,     0,   719,     0,     0,   746,
       0,     0,     0,   720,  -799,     0,   721,   722,     0,     0,
       0,     0,     0,     0,   723,   747,     0,     0,     0,     0,
     748,   724,     0,   725,     0,   749,   726,     0,     0,     0,
       0,     0,     0,     0,  -799,     0,   750,  1014,     0,     0,
     867,  -799,     0,     0,     0,  -799,     0,  -799,   751,     0,
    -799,     0,  -799,     0,     0,     0,     0,     0,   752,     0,
       0,  1206,     0,   727,     0,     0,     0,   728,     0,   729,
       0,     0,     0,     0,     0,     0,   730,     0,     0,     0,
       0,     0,     0,  -799,     0,     0,     0,  1014,  -799,     0,
     867,     0,     0,     0,     0,     0,     0, -1517,     0,   731,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1015,   732,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -799,     0,     0,     0,     0,  1017,
       0,     0,     0,     0, -1521,   733,     0,     0,     0,     0,
       0,     0,     0,     0,   734,     0,     0,     0,     0,     0,
       0,  -799,     0,     0,     0,     0,     0,   735,     0,     0,
       0,     0,   736,  1015,   737,     0,     0,  1014,     0,     0,
     867,     0,   738,     0,     0,     0,     0,     0,     0,  1017,
       0,  -799,   739,     0,     0,     0,     0,  -799,     0,     0,
       0,   740,     0,     0,     0,     0,  -799,  -799,     0,     0,
     741,     0,   742,   743,     0,     0,   744,     0,   745,     0,
       0,     0,     0,   746,     0,  1018,  -799,     0,     0,     0,
       0,     0,  -799,     0,     0,     0,   437,  -799,     0,   747,
    1614,     0,     0,     0,   748,     0,     0,     0,     0,   749,
    -799,     0,     0,  1015, -1521,     0,     0,     0,  -799,     0,
     750,  -799,     0,     0,     0,     0,  1019,  -799,     0,  1017,
       0,     0,   751,  1020, -1517,  1018,     0,   438,     0,  1021,
       0,     0,  1022,  1137,   439,     0,   437,     0,  1014,     0,
       0,   867,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1023,  1019,     0,     0,     0,
       0,     0,     0,  1020,     0,     0,     0,   438,     0,  1021,
       0,     0,  1022,     0,   439,     0,     0,     0,     0,     0,
       0,     0, -1517,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1018,   440,     0,     0,     0,
       0,     0,     0,     0,  1015,  1023,   437,     0,  1014,     0,
       0,   867,     0,     0,     0,     0,  1016,     0,     0,     0,
    1017,  1341,     0,  1024,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1019,     0,     0,     0,
       0,     0,     0,  1020,     0,     0,   440,   438,     0,  1021,
       0,     0,  1022,     0,   439,     0,     0,     0,  1014,   441,
       0,   867,     0,     0,     0,     0,     0,     0,  1025,  1026,
       0,     0,     0,  1024,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1015,  1023,     0,     0,   442,     0,
       0,     0,     0,     0,  1027,     0,  1095,     0,     0,     0,
    1017,     0,     0,     0,     0,     0,  1018,     0,     0,   441,
       0,     0,  1028,     0,     0,     0,     0,   437,  1025,  1026,
    1029,     0,     0,   297,     0,     0,   440,     0,     0,   443,
       0,     0,     0,     0,  1015,  1615,     0,     0,   442,  1616,
       0,     0,     0,     0,  1027,     0,     0,  1019,     0,     0,
    1017,     0,     0,  1024,  1020,     0,     0,     0,   438,     0,
    1021,     0,  1028,  1022,  1137,   439,     0,     0,     0,     0,
    1029,     0,     0,   297,     0,     0,     0,     0,     0,   443,
       0,     0,     0,     0,     0,     0,  1018,  1014,     0,   441,
     867,     0,     0,     0,     0,     0,  1023,   437,  1025,  1026,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   442,     0,
       0,     0,     0,     0,  1027,     0,     0,  1019,     0,     0,
       0,     0,     0,     0,  1020,     0,  1018,   440,   438,     0,
    1021,     0,  1028,  1022,     0,   439,     0,   437,     0,  1014,
    1029,     0,   867,   297,     0,     0,     0,     0,     0,   443,
       0,     0,     0,  1015,  1024,     0,     0,     0,     0,     0,
       0,  1014,     0,     0,   867,  1141,  1023,  1019,     0,  1017,
       0,     0,     0,  1014,  1020,     0,   867,     0,   438,     0,
    1021,     0,     0,  1022,     0,   439,     0,     0,     0,     0,
     441,     0,     0,     0,     0,     0,     0,     0,     0,  1025,
    1026,     0,     0,     0,     0,     0,     0,   440,     0,     0,
       0,     0,     0,     0,     0,  1015,  1023,     0,     0,   442,
       0,     0,     0,     0,     0,  1027,     0,     0,     0,     0,
       0,  1017,     0,     0,  1024,     0,     0,  1015,     0,     0,
       0,     0,     0,  1028,     0,     0,     0,     0,     0,  1015,
       0,  1029,     0,  1017,   297,  1018,     0,   440,     0,     0,
     443,     0,     0,     0,     0,  1017,   437,     0,     0,     0,
     441,     0,     0,     0,     0,     0,     0,     0,     0,  1025,
    1026,     0,     0,     0,  1024,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1019,     0,     0,   442,
       0,     0,     0,  1020,     0,  1027,     0,   438,     0,  1021,
       0,     0,  1022,     0,   439,     0,     0,  1018,     0,     0,
     441,     0,     0,  1028,     0,     0,     0,     0,   437,  1025,
    1026,  1029,     0,     0,   297,  1346,     0,     0,     0,  1018,
     443,     0,     0,     0,     0,  1023,     0,     0,     0,   442,
     437,  1018,     0,     0,     0,  1027,     0,     0,  1019,     0,
       0,     0,   437,     0,     0,  1020,     0,     0,     0,   438,
       0,  1021,     0,  1028,  1022,     0,   439,     0,     0,     0,
    1019,  1029,     0,     0,   297,     0,   440,  1020,     0,     0,
     443,   438,  1019,  1021,     0,     0,  1022,     0,   439,  1020,
       0,  1014,     0,   438,   867,  1021,     0,  1023,  1022,     0,
     439,     0,     0,  1024,     0,  1014,     0,     0,   867,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1023,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1023,     0,     0,     0,     0,     0,     0,   440,   441,
       0,     0,     0,     0,     0,     0,     0,     0,  1025,  1026,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     440,     0,     0,     0,     0,  1024,     0,  1015,   442,     0,
       0,     0,   440,     0,  1027,     0,     0,     0,     0,     0,
       0,  1015,     0,  1017,     0,  1014,     0,  1024,   867,     0,
       0,     0,  1028,     0,     0,     0,     0,  1017,     0,  1024,
    1029,   441,     0,   297,     0,     0,     0,     0,     0,   443,
    1025,  1026,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   441,     0,     0,  1230,     0,     0,  1623,
     442,     0,  1025,  1026,     0,   441,  1027,     0,     0,     0,
       0,     0,     0,     0,  1025,  1026,     0,     0,     0,     0,
       0,     0,   442,     0,  1028,     0,     0,     0,  1027,     0,
       0,  1015,  1029,     0,   442,   297,     0,     0,     0,  1018,
    1027,   443,     0,     0,     0,     0,  1028,  1017,     0,     0,
     437,     0,     0,  1018,  1029,     0,     0,   297,  1028,     0,
       0,     0,     0,   443,   437,     0,  1029,     0,     0,   297,
       0,     0,     0,     0,     0,   443,     0,     0,     0,     0,
    1019,     0,     0,     0,     0,     0,     0,  1020,     0,     0,
       0,   438,     0,  1021,  1019,     0,  1022,     0,   439,     0,
       0,  1020,     0,     0,     0,   438,     0,  1021,     0,     0,
    1022,     0,   439,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1023,
       0,     0,     0,  1018,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1023,   437,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     440,     0,     0,     0,  1019,     0,     0,     0,     0,     0,
       0,  1020,     0,     0,   440,  1059,     0,  1021,     0,     0,
    1022,     0,   439,     0,     0,     0,     0,  1024,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1024,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1023,     0,     0,     0,     0,  1761,     0,
       0,     0,     0,   441,     0,     0,     0,     0,     0,     0,
       0,     0,  1025,  1026,     0,     0,     0,   441,     0,     0,
       0,     0,     0,     0,     0,     0,  1025,  1026,     0,     0,
       0,     0,   442,     0,   440,     0,     0,     0,  1027,     0,
       0,     0,     0,     0,     0,     0,   442,     0,     0,     0,
       0,     0,  1027,     0,     0,     0,  1028,     0,     0,     0,
       0,  1024,     0,     0,  1029,     0,     0,   297,     0,     0,
    1028,     0,     0,   443,     0,     0,     0,     0,  1029,     0,
       0,   297,     0,     0,     0,     0,     0,   443,     0,     0,
       0,     0,     0,     0,     0,  1015,     0,   441,     0,     0,
       0,     0,     0,     0,     0,     0,  1025,  1026,     0,     0,
       0,  1017,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   442,     0,  1654,     0,
    1655,     0,  1027,  1656,   629,   630,   631,   632,   633,   634,
     635,  1657,  1658,  1659,     0,     0,     0,     0,     0,     0,
    1028,   629,   630,   631,   632,   633,   634,   635,  1029,     0,
       0,   297,     0,  1660,     0,     0,     0,   443,     0,     0,
       0,   636,     0,   637,   638,   639,   640,   641,   642,     0,
    2078,  2079,     0,     0,     0,     0,     0,     0,   636,     0,
     637,   638,   639,   640,   641,   642,     0,  1018,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   437,     0,
       0,     0,     0,     0,     0,   643,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   643,     0,     0,     0,     0,     0,  1179,     0,
       0,     0,     0,     0,     0,  1020,     0,     0,     0,   438,
       0,  1021,     0,     0,  1022,  1661,   439,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1662,     0,     0,     0,  1663,  1664,     0,
    1015,     0,     0,     0,     0,     0,     0,  1023,     0,     0,
       0,  1665,     0,     0,     0,     0,  1017,     0,   644,     0,
       0,     0,     0,     0,     0,     0,  2080,     0,     0,     0,
       0,     0,     0,     0,   645,   644,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   440,     0,
    1666,   645,     0,     0,     0,     0,     0,     0,     0,  1667,
       0,     0,     0,     0,     0,     0,     0,  2081,  2082,     0,
     647,     0,     0,     0,     0,  1024,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   647,     0,     0,
       0,     0,  2083,  1668,     0,     0,     0,     0,     0,     0,
       0,     0,  1018,     0,     0,     0,     0,  1669,   649,     0,
     648,   441,     0,   437,     0,   650,     0,   651,     0,     0,
    1025,  1026,     0,     0,     0,   649,     0,     0,     0,     0,
     652,  1670,   650,     0,   651,     0,     0,  2084,     0,     0,
     442,     0,     0,  1179,     0,     0,  1027,   652,     0,     0,
    1020,     0,     0,     0,   438,  1671,  1021,     0,     0,  1022,
    1672,   439,     0,     0,  1028,     0,     0,     0,     0,     0,
       0,     0,  1029,  1015,  1673,   297,     0,     0,     0,     0,
       0,   443,  1180,  1181,   655,     0,   656,   657,   658,  1017,
    1706,  1182,  1023,     0,     0,     0,     0,     0,     0,     0,
       0,   655,     0,   656,   657,   658,     0,     0,     0,     0,
    2085,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1674,     0,     0,     0,  2086,     0,     0,     0,     0,     0,
       0,     0,  1675,   440,     0,     0,   660,   661,   662,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2087,   663,
       0,  1676,   664,   660,   661,   662,     0,     0,     0,     0,
    1024,     0,     0,     0,     0,     0,   663,     0,     0,   664,
    2088,     0,  1677,     0,     0,  1018,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   437,     0,     0,  2089,
       0,     0,     0,     0,     0,     0,   441,     0,     0,     0,
       0,     0,     0,     0,     0,  1025,  1026,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1179,     0,     0,     0,
       0,     0,     0,  1020,     0,   442,     0,   438,     0,  1021,
       0,  1027,  1022,     0,   439,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1028,
       0,     0,     0,     0,     0,     0,     0,  1029,     0,     0,
     297,     0,     0,     0,     0,  1023,   443,  1180,  1181,     0,
       0,     0,     0,     0,     0,  1942,  1182,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   440,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1024,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   441,
       0,     0,     0,     0,     0,     0,     0,     0,  1025,  1026,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   442,     0,
       0,     0,     0,     0,  1027,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1028,     0,     0,     0,     0,     0,     0,     0,
    1029,     0,     0,   297,     0,     0,     0,     0,     0,   443,
    1180,  1181,     0,     0,     0,     0,     0,     0,     0,  1182
};

static const yytype_int16 yycheck[] =
{
      84,   176,   412,   571,   231,   132,   230,   234,   898,   721,
     934,  1058,   685,   460,   687,   323,  1307,   535,   536,  1130,
    1237,   196,   197,  1237,   653,  1237,   201,   202,   203,   204,
     205,   750,   207,   228,   209,   230,   231,  1120,  1151,   234,
     893,   868,   869,   895,  1237,   892,  1237,   692,  1377,  1137,
     912,   904,  1747,  1051,   901,   902,   283,  1029,     6,   369,
     287,  1377,   289,   925,   894,   625,   193,  1270,  1377,   916,
     917,   298,  1377,   248,   301,   250,   160,  1377,  1377,   487,
     258,     6,   257,   930,   931,   603,     6,  1078,   283,    17,
     265,    22,   287,     6,   289,  1086,  1207,     6,  1419,  1420,
      54,    13,     9,   298,   279,   280,   301,   282,     9,  1311,
       9,    49,    17,   288,    70,    23,  1230,    21,    70,    56,
      85,    70,    96,  1206,    56,    86,    48,    37,   121,     9,
      49,    70,   149,   360,   444,   214,    70,   114,    96,    28,
    1896,  1132,     0,   370,   122,  1261,  1262,  1263,    86,  1521,
     377,   625,   327,  1267,   223,   330,   331,    56,   333,   171,
      72,   123,   236,   182,  1410,   360,   390,  1539,   392,  1167,
     348,  1417,    70,   121,   349,   370,    88,   355,    49,   121,
    1293,    49,   377,     9,  1298,  1032,  1881,  1014,   415,   862,
     236,   366,  1019,   388,   820,   390,   207,   392,   248,    40,
      31,   874,  1285,   113,   171,   300,    30,   183,   518,    63,
     236,   198,    56,     9,  1061,  1587,    28,    66,   413,   187,
     415,   187,   306,    66,    48,   150,   115,    28,    92,    61,
     170,   409,  1346,   122,   325,   462,   411,   464,   416,   463,
     175,   914,   118,  1884,   419,    49,  1170,    30,  1095,   214,
    1077,   429,    25,   240,    50,  1627,    88,    89,     9,   236,
     402,    11,   171,  1351,  1347,  1378,  1128,   462,   463,   464,
     107,   376,     8,   260,   173,   453,   836,   901,   441,   110,
    1403,   368,    70,  2326,   479,   693,  1399,  1410,   466,   423,
     248,  1138,   455,   310,  1417,   118,  1143,     0,   473,    35,
     455,  2344,   436,   115,    73,    56,   214,   931,   218,   393,
      22,   986,   396,   240,   115,   195,   458,  1315,   493,   494,
    1114,    71,   122,   248,   223,   183,  1409,     9,   214,   236,
    1003,   418,   218,   260,   561,   311,  1450,   442,  1329,  1660,
    1230,   519,   411,   126,   435,  1666,   441,   305,   523,  1552,
     174,   456,  1179,   403,   316,   128,   236,   236,   533,   537,
     236,  1006,   836,   243,   325,   236,   561,     9,   442,   998,
     999,    32,  2013,   341,   448,   341,   455,  1267,  1004,  1005,
    1553,    70,   214,  1230,   233,   560,  1559,   325,   583,   584,
    1237,   280,  1764,   568,   329,   573,   442,  1250,   376,   195,
     578,   202,   364,  1842,   360,   236,   325,   975,  1298,  1201,
     236,   360,   539,   236,  1530,   256,   442,  1528,  2174,  1266,
    1267,   360,  1275,   434,  1512,   442,   360,   602,   236,   225,
     442,   424,   607,  1295,   609,   315,   455,   612,  1640,   614,
     236,   616,   617,  1556,   195,  1120,   621,   243,    63,  1279,
     437,  1298,   301,   311,   364,   403,  1346,   325,   301,   654,
    1451,   293,   360,   441,   442,   442,   403,   331,   442,  1715,
     648,   436,   223,   341,   435,   442,   424,   321,   456,  1309,
     434,   433,   424,   403,   442,   236,  1333,   409,   663,   664,
    1337,  1338,   243,  1340,   442,   400,  1579,   435,   378,  1346,
     404,   457,   442,   164,   408,  1180,  1181,  1182,   457,   363,
     438,   443,   411,   195,   441,  1190,   435,   442,   457,   315,
    1314,   325,   442,   457,   455,   833,  1356,   407,  1611,   442,
     394,  1206,   441,   442,   442,   442,  1211,   341,  1213,   251,
    1215,   442,  1217,  1590,  1219,  1220,  1221,  1222,  1223,  1224,
    1225,  1226,   441,   322,   236,   895,   442,   867,    49,   457,
    1450,   243,   442,   442,   315,   692,   442,   435,   448,  1941,
    2009,   442,   360,  2012,   914,   187,  1202,   448,  1907,   919,
    1871,  1210,   378,   244,   236,   409,   498,   455,  1217,   816,
     236,  1907,  1715,   820,   245,  1586,   823,   824,  1907,  1007,
     168,  1689,  1907,   830,   441,   442,  1398,  1907,  1907,  2304,
    1285,   407,   251,  1173,  1787,  1788,  1819,   441,   260,   442,
    1992,   816,  1994,   455,   150,   820,    23,   378,   823,   824,
     245,   435,   117,   315,   442,   830,   811,   406,   350,   168,
    1813,   441,   442,    70,   163,   223,   986,   200,  1277,  1822,
    2022,   455,   448,  2058,   126,  2060,   407,   832,    30,   310,
     411,   449,   450,   451,   452,   456,   454,   227,   228,   457,
     187,   360,  1347,   139,  1319,   156,   318,   107,  1323,   455,
    1510,  2053,  2054,    12,  1396,  1773,    15,    16,   198,   199,
    1000,   442,   279,   372,    66,   310,   378,   448,   422,   894,
     156,   187,  1816,   349,  1818,  1380,   139,   358,     9,   887,
     120,   350,  1387,  1388,  1389,  1390,  1391,  1392,  1393,   210,
     915,   200,  2161,  1585,   919,   407,   921,   954,   923,   924,
     240,   926,   285,   524,  1409,   269,   348,  1851,    27,   418,
    1738,  1739,  1740,   358,   971,   175,   941,  1459,   363,  1832,
     260,  1380,   240,   187,   224,    56,   300,  2078,   188,   954,
     449,   450,   451,   452,  1104,   454,   448,   247,   457,  1883,
     289,  1618,   260,   195,  1746,  1766,   971,  1004,  1005,  1751,
    1752,  1894,  1955,  1755,  1756,  1757,   354,  1759,  1760,   240,
     442,   263,   919,   380,   989,  2200,  1425,   972,   277,   247,
    1519,  1974,   288,   284,   455,  1888,   984,   269,   180,  1004,
    1005,  1663,    25,    26,   236,   899,   455,   214,  1991,   299,
     305,   243,   198,   187,   322,   354,   195,   442,   284,  2046,
     206,   348,  2046,   411,  2046,   455,   920,   405,   922,   563,
    1180,  1181,  1182,   927,   211,   311,  1934,  1935,  1560,   225,
    1190,   299,   936,  2046,    67,  2046,    69,  1569,  1849,  2032,
    2033,   233,   986,  1979,  1980,  1981,  1982,   236,  2041,   236,
     166,  1211,   173,  1213,   243,  1215,   346,  1217,   311,  1219,
    1220,  1221,  1222,  1223,  1224,  1225,  1226,   118,  2260,  2261,
     103,   104,   105,   315,   195,   455,   347,   441,   442,  1987,
    1988,   277,   278,    11,  1579,  1580,   245,   441,   406,   285,
     286,   207,   240,   251,   348,   291,   292,    25,    26,   215,
     279,  1116,   223,   180,   253,   254,  1816,   437,  1818,   301,
     236,   441,   260,   360,   236,   236,  1611,   150,   236,   152,
    2231,   236,   243,   272,   273,     9,   315,   160,    12,    57,
     248,    15,    16,   441,   442,   123,   378,  2130,   260,  1086,
    2071,  1851,   124,  1158,   426,  2138,   202,  1820,  1052,   449,
     450,   310,   296,   297,   102,  1202,  1935,  1104,   213,   441,
    2153,   319,   455,   321,   348,  1614,   310,  1162,    96,    97,
     245,    99,   288,  1883,  1172,   293,   324,   233,   986,   167,
     108,   449,   450,   260,   380,   236,   312,  1202,  2181,   378,
    2183,  1858,   154,   372,   315,  2062,  1869,  2190,   368,   358,
     180,   234,   449,   450,   451,   452,   448,   454,  1987,  1988,
     457,   266,   356,   195,   195,   248,   240,  2210,  2211,  2330,
    1380,   245,   236,   151,   152,   166,   258,  1387,  1388,  1389,
    1390,  1391,  1392,  1393,   162,   310,  1180,  1181,  1182,   418,
    1020,   126,     1,    83,   258,   368,  1190,  1375,   418,   275,
     319,   213,   120,  1748,   236,   236,   236,   378,  1753,   448,
     368,   243,   243,   319,  1279,  1045,   207,  1211,   416,  1213,
     326,  1215,   304,   255,   215,  1219,  1220,  1221,  1222,  1223,
    1224,  1225,  1226,   358,   356,   299,   407,   311,    47,   368,
     411,  2284,  1912,   441,  1309,   418,   455,  2164,  1245,  1966,
     923,  2045,   264,    62,   266,   374,   375,    60,   364,   237,
     418,   337,  1932,  1933,   167,  1582,   195,     8,   941,    72,
     169,   442,  1369,  1370,   442,  1115,   442,   448,   213,   167,
     448,  1605,   188,   315,   315,   188,   455,  1832,  1831,   418,
      93,  1356,   307,   102,    35,  1840,  1620,   288,   101,  1364,
     188,   377,  1256,   379,  1369,  1370,  1694,   236,   214,   208,
     227,   228,  1152,  1983,   243,   240,  1986,   216,   401,   253,
     254,  1318,  1180,  1181,  1182,   399,   120,   319,   263,   321,
     455,   266,  1190,   240,     9,   260,   240,  1437,   272,   273,
    1440,  1884,   455,  1888,   404,  1445,   378,   378,   408,   381,
     382,   455,  2269,   260,   600,  1213,   260,   455,   167,   442,
    1357,  1219,  1220,  1221,  1222,   326,   526,  1225,  1226,  1211,
     331,   531,   356,  1215,   352,   178,   407,   455,  1960,   188,
    1962,  1223,  1224,   159,   404,   311,   315,   163,   408,  2086,
    2150,   135,  2152,  1387,  1388,  1389,  1390,  1391,  1392,  1393,
       2,  2071,   166,    82,     6,   214,   170,    82,   227,   228,
     219,   442,   451,   452,   392,   454,   448,   448,   278,    98,
     280,   310,   231,    98,   449,   450,   451,   452,   455,   454,
     449,   450,   451,   452,   356,   454,   461,   444,   449,   450,
     451,   452,   461,   454,   169,  1510,   891,    90,    91,   378,
     895,   233,   234,  1663,  2171,  2125,   901,   319,   455,   321,
    1848,   906,   907,   438,   442,   440,   239,   912,   913,   914,
    2013,   270,   271,   116,   919,   270,   271,   455,   407,   356,
     925,  2275,   442,   449,   450,   451,   452,   341,   454,   934,
     935,   457,   937,   233,   234,   449,   450,   451,   452,    31,
     454,    33,   455,   457,    36,   184,   153,   455,   155,   184,
     319,   320,   455,   455,    46,   427,   428,   429,   430,   448,
     195,   359,   265,   332,   267,   334,   153,   455,   155,  1387,
    1388,  1389,  1390,  1391,  1392,  1393,   455,   405,  1748,    11,
     319,   986,   321,  1753,   216,  1642,  2263,   455,   356,  2266,
    2132,   235,  2134,    25,    26,   442,   182,   236,   455,   238,
     455,   236,   241,   238,   283,   280,   241,   280,   243,   455,
     403,  1016,   277,   403,  1619,   395,  2246,  1642,  2121,    24,
     455,  2251,   356,   332,   372,    57,   214,   107,   455,  1686,
     442,   384,  1589,    56,     1,   274,   367,     4,  2315,   274,
     442,   236,    85,  1648,  1652,   175,  1051,   455,   356,   351,
    1655,   372,    19,  1710,   283,   109,   236,  1662,   363,   211,
    1668,  1686,    29,   455,    96,    97,   435,    99,  1625,    68,
    2347,   156,   157,  1078,   249,  1632,   108,   455,   280,   280,
     315,  1086,  1087,   410,   176,  1710,   455,   356,   249,   181,
      23,   294,   295,  1750,   277,   442,    63,   455,   236,  1104,
     185,   280,   194,   342,   301,   455,   191,   342,   449,   450,
     451,   452,    84,   454,  1719,  1120,   457,  1722,    84,   151,
     152,   436,   442,  1128,   442,  1750,   400,  1132,   384,   435,
     162,   403,   335,   336,   234,   317,  1141,   222,   200,  1144,
     403,   226,   319,   378,   427,   428,   429,   430,   387,   388,
     242,   442,   387,   388,   364,   449,   450,   451,   452,   218,
     454,    55,  1167,   457,   441,  1170,   427,   428,   429,   430,
     384,    27,   407,   188,   413,  1180,  1181,  1182,   413,   449,
     450,   451,   452,   372,   454,  1190,   356,   457,   455,   455,
     364,  1796,   431,   442,  1748,   225,   431,  1802,   290,  1753,
     439,  1206,   227,   442,   439,   237,  1211,   442,  1213,   346,
    1215,   438,   214,   448,  1219,  1220,  1221,  1222,  1223,  1224,
    1225,  1226,   314,   449,   450,   451,   452,   109,   454,   236,
    2228,   457,   405,   306,    37,   202,   381,   287,   403,  1844,
     281,   458,  2082,   448,   400,    27,   338,  1792,  1793,  1794,
    1795,   343,   362,   462,   400,   174,   455,   455,   442,   236,
     136,   353,   405,   107,    17,   357,   233,   172,   188,    12,
      13,    14,   441,   240,   402,    33,   236,    20,    36,    30,
    1285,   127,   458,   128,   205,    56,    44,    45,    46,   403,
    1295,   458,   458,   434,   261,  1903,  1853,   130,   458,   458,
     458,   458,  1859,  1308,  1909,   458,   348,   458,   458,  1914,
    1315,   458,   132,   319,   458,    58,   133,  1322,  1923,   286,
     352,   100,  1927,   415,  1329,   292,   403,   399,   137,    49,
    1748,   402,   138,   425,   400,  1753,  1341,   402,   180,  1853,
     397,   143,  1347,   436,   248,    49,   146,   112,  1353,   180,
     333,   380,   319,   442,   114,   365,   403,   114,   441,   326,
     392,   442,  2019,   187,   309,   341,   236,  1372,   163,   438,
     134,   456,   339,   171,   459,   460,   403,   366,   210,   403,
      49,   218,  1387,  1388,  1389,  1390,  1391,  1392,  1393,   180,
     122,   210,   280,   454,  2019,   447,   363,   364,   446,   366,
     158,   193,   218,   270,  1409,   233,   457,   374,   457,   341,
     442,   457,   457,   156,   157,   403,  2021,   384,   176,   398,
     373,   131,   269,   266,  1429,   265,   187,   400,   331,   403,
      49,   138,     8,   180,   438,   126,   194,   438,   405,   403,
       9,   307,   185,   308,   173,   404,  1451,   202,   191,   329,
     268,   344,   125,   435,   110,   435,    49,   175,   285,   141,
     240,   142,   263,   262,   144,   300,  2120,   289,   113,  2074,
     284,   214,   394,     7,   116,   220,    67,   442,   156,   222,
    2085,   156,  2087,   226,   242,   129,   136,   328,   455,   328,
     102,    49,   240,   218,   145,  2120,    95,   267,  2106,   148,
     221,   264,    91,   203,   192,   390,    49,   438,  1513,  1514,
     406,   307,   240,   256,   257,   344,   240,   147,   180,   262,
     174,   293,   307,   423,   140,    49,     6,    22,   354,   272,
     193,    54,   290,   188,   132,   178,   279,   211,  1330,   514,
    1153,   284,   597,   444,   136,  1361,  1370,  1154,  1899,   960,
     610,   227,  1852,   109,   113,   393,   239,    49,   160,   302,
      37,    38,    39,    40,    41,    42,   584,   886,  2173,   318,
    1695,   861,  1693,  1584,  1579,  1580,  2233,  1907,  1691,  2118,
    1585,  1586,   874,   974,   565,   343,  2101,  2239,   836,   124,
    1775,  1856,  1061,  1422,   496,   353,  2253,    74,  1603,    76,
      77,    78,    79,    80,    81,  1734,  1611,  1421,  2233,  1773,
    2218,  1809,  1066,  1275,  2219,  2220,  1272,  1552,  2223,  1819,
    2003,  1626,  1282,  1840,  1577,  2230,  1631,  1632,  2253,  1288,
    2238,  2239,  1857,  1104,  1601,  1357,  1873,  1323,  1128,  1126,
     926,   118,  1138,  1632,  2056,  1632,  1712,  2272,  2061,  1864,
    2174,  2067,  1526,  1239,  1116,   987,  1614,   415,  1663,   246,
    1642,  1235,  2267,   329,  1293,  1069,   866,   619,   994,  1674,
      57,  1676,  2255,   827,     1,  1465,  1915,    -1,  1001,     6,
      -1,    -1,     9,    -1,    -1,    12,    13,    14,  2296,  2297,
      -1,    -1,  2300,  2298,  2302,  2209,    -1,    -1,    -1,    -1,
      -1,  2326,    -1,    -1,    -1,   448,   449,   450,   451,   452,
      -1,   454,    -1,   456,   457,    -1,   459,   460,    -1,  2344,
      -1,    -1,    -1,  2328,   201,    -1,    -1,    -1,    -1,    -1,
    2338,    58,    -1,  1738,  1739,  1740,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1748,    -1,    -1,    -1,    -1,  1753,    -1,
      -1,    -1,    -1,    -1,  2268,    82,    -1,    -1,    -1,    -1,
      -1,  1766,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    98,    -1,    -1,    -1,     6,   253,    -1,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    98,    -1,  2327,   291,    -1,    -1,    -1,    -1,    -1,
    1825,    -1,    -1,   300,    -1,    -1,  1831,  1832,    -1,   156,
     157,    -1,    -1,    -1,    -1,  1840,   313,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1849,    -1,    -1,    -1,    -1,    -1,
      -1,    82,  1857,    -1,    -1,    -1,    -1,   184,   185,    -1,
      -1,    -1,    -1,    -1,   191,    -1,    -1,    98,   195,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1884,
      -1,    -1,    -1,  1888,    -1,    -1,    -1,   214,    -1,    -1,
     177,    -1,   369,   370,   371,   222,    -1,   184,   225,   226,
      -1,    -1,    -1,  1908,    -1,   232,    -1,  1912,    -1,   236,
      -1,   238,    -1,    -1,   241,    -1,   243,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   156,    -1,  1932,  1933,   256,
     257,    -1,    -1,    -1,    -1,   262,    -1,    -1,    -1,    -1,
      -1,    -1,   419,   420,   421,   272,    -1,   274,    -1,   236,
      -1,   238,   279,   184,   241,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   195,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   302,    -1,    -1,  1983,    -1,
      -1,  1986,    -1,    82,    -1,    -1,    -1,   274,   315,    -1,
      -1,    -1,    -1,    -1,   225,     0,     1,    -1,    -1,    98,
      -1,   232,    -1,    -1,    -1,   236,    -1,   238,  2013,    -1,
     241,    -1,   243,    -1,    -1,   342,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    -1,
    2045,    -1,    -1,   274,    -1,    -1,    -1,  2052,    -1,    -1,
      -1,   378,    -1,    -1,    -1,   342,    -1,    -1,    -1,    -1,
     387,   388,    -1,    -1,    -1,    -1,  2071,    -1,    -1,    74,
      -1,    76,    77,    78,    79,    80,    81,    -1,   177,    -1,
     407,    -1,    -1,  2088,   315,   184,   413,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     387,   388,    -1,    -1,   431,    -1,    -1,    -1,    -1,    -1,
     397,   342,   439,   118,    -1,   442,    -1,    -1,    -1,    -1,
    2125,   448,   449,   450,    -1,    -1,   413,   454,    -1,   456,
     135,   458,   459,   460,   139,    -1,   423,   236,    -1,   238,
      -1,    -1,   241,    -1,   431,    -1,    -1,   378,    -1,   436,
      -1,    -1,   439,    -1,   441,   442,   387,   388,    -1,    -1,
      -1,    -1,   167,   168,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   274,   407,    -1,   183,  2184,
      -1,    -1,   413,   188,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2199,    -1,   201,  2202,    -1,    -1,
     431,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   439,   214,
      -1,   442,   217,    -1,    -1,    -1,    -1,   448,   223,    -1,
      -1,    -1,   227,   228,    -1,   456,    -1,  2232,    -1,    -1,
     235,   236,    -1,    -1,   239,    -1,    -1,    -1,    -1,    -1,
      -1,  2246,    -1,   342,    -1,    -1,  2251,    -1,   253,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     0,     1,
      -1,     3,    -1,     5,    -1,    -1,    -1,    -1,    10,    -1,
    2275,   276,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,
      -1,  2286,    -1,    -1,    -1,    -1,   291,    -1,   387,   388,
      -1,    -1,    -1,   298,    -1,   300,    -1,    -1,   397,    -1,
      -1,    -1,   307,    -1,    -1,    -1,   311,    -1,   313,    51,
      52,    -1,    -1,    -1,   413,    -1,    -1,    59,   323,    -1,
      -1,    -1,    -1,    -1,   423,   330,  2331,   332,    -1,    71,
      -1,    -1,   431,    75,    -1,    -1,    -1,   436,    -1,    -1,
     439,    -1,   441,   442,    -1,    87,   351,    -1,    -1,   354,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   367,    -1,   369,   370,   371,    -1,    -1,   111,
      -1,    -1,    -1,    -1,    -1,    -1,   118,   119,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   393,    -1,
      -1,    -1,    -1,   135,    -1,    -1,    -1,   139,    -1,    -1,
      -1,     1,    -1,     3,    -1,     5,   411,   149,    -1,    -1,
      10,    -1,    -1,    -1,   419,   420,   421,    -1,    18,   161,
      -1,    -1,    -1,   165,    -1,    -1,    -1,   432,    -1,    -1,
     435,    -1,    -1,    -1,    -1,    -1,    -1,   179,    -1,   444,
      -1,   183,    -1,    -1,   186,    -1,    -1,   189,   190,    -1,
     455,    51,    52,    -1,    -1,   197,    -1,    -1,    -1,    59,
      -1,    -1,   204,    -1,   206,    -1,    -1,   209,    -1,    -1,
      -1,    71,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   246,    -1,    -1,    -1,   250,    -1,
     252,   111,    -1,    -1,    -1,    -1,    -1,   259,   118,   119,
      -1,    -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     282,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,
      -1,    -1,    -1,    -1,    -1,   297,    -1,    -1,    -1,    -1,
      -1,   161,    -1,    -1,    -1,   165,    -1,    -1,    -1,   311,
      -1,    -1,    -1,    -1,    -1,    -1,   318,    -1,    -1,   179,
      -1,    -1,    -1,    -1,    -1,   327,   186,    -1,    -1,   189,
     190,    -1,    -1,    -1,    -1,    -1,    -1,   197,   340,    -1,
      -1,    -1,    -1,   345,   204,   347,   206,    -1,    -1,   209,
      -1,    -1,    -1,   355,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   365,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   374,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   383,    -1,   385,   386,    -1,   246,   389,    -1,   391,
     250,    -1,   252,    -1,   396,    -1,    -1,    -1,     6,   259,
      -1,     9,    -1,    -1,    12,    13,    14,    -1,    -1,    17,
     412,    -1,    -1,    21,    -1,   417,    -1,    -1,    -1,    -1,
     422,    -1,   282,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   433,    -1,    -1,    -1,    -1,    -1,   297,    -1,    -1,
     442,    -1,    -1,   445,    -1,    -1,    -1,    -1,    -1,    -1,
      58,    -1,    -1,   455,    -1,    -1,    -1,    -1,   318,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   327,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,
     340,    -1,    -1,    -1,    -1,   345,    -1,   347,    -1,    -1,
      98,    -1,    -1,    -1,     6,   355,    -1,     9,    -1,    -1,
      12,    13,    14,    -1,    -1,   365,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   374,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   383,    -1,   385,   386,    -1,    -1,   389,
      -1,   391,    -1,    -1,    -1,    -1,   396,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    -1,   156,   157,
      -1,    -1,   412,    -1,    -1,    -1,    -1,   417,    -1,    -1,
      -1,    -1,   422,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,   433,    -1,    -1,   184,   185,    -1,    -1,
      -1,    -1,   442,   191,    -1,   445,    98,   195,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   455,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   214,    -1,    -1,    -1,
      82,    -1,    -1,    -1,   222,    -1,    -1,   225,   226,    -1,
      -1,    -1,    -1,    -1,   232,    -1,    98,    -1,   236,    -1,
     238,    -1,    -1,   241,    -1,   243,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   156,   157,    -1,    -1,   256,   257,
      -1,    -1,    -1,    -1,   262,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   272,    -1,   274,    -1,    -1,    -1,
      -1,   279,   184,   185,    -1,    -1,    -1,    -1,    -1,   191,
      -1,    -1,    -1,   195,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   302,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   214,    -1,    -1,    -1,    -1,   315,    -1,    -1,
     222,    -1,   184,   225,   226,    -1,    -1,    -1,    -1,    -1,
     232,    -1,    -1,   195,   236,    -1,   238,    -1,    -1,   241,
      -1,   243,    -1,    -1,   342,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   256,   257,    -1,    -1,    -1,    -1,
     262,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     272,    -1,   274,    -1,   236,    -1,   238,   279,    -1,   241,
     378,   243,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   387,
     388,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     302,    -1,    -1,    -1,    -1,    -1,   404,    -1,    -1,   407,
     408,    -1,   274,   315,    -1,   413,     3,    -1,     5,    -1,
      -1,    -1,    -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    18,    -1,   431,    -1,    -1,    -1,    -1,    -1,    -1,
     342,   439,    -1,    -1,   442,    -1,    -1,    -1,    -1,    -1,
     448,   449,   450,   315,    -1,    -1,   454,    -1,   456,    -1,
     458,   459,   460,    -1,    51,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    59,    -1,    -1,    -1,   378,    -1,    -1,    -1,
     342,    -1,    -1,    -1,    71,   387,   388,    -1,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      87,    -1,    -1,    -1,    -1,   407,    -1,    -1,    -1,    -1,
      -1,   413,    -1,    -1,    -1,    -1,   378,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   111,   387,   388,    -1,    -1,   431,
      -1,   118,   119,    -1,    -1,    -1,    -1,   439,    -1,    -1,
     442,    -1,    -1,    -1,    -1,   407,   448,   449,   450,    -1,
      -1,   413,   454,    -1,   456,    -1,   458,   459,   460,    -1,
      -1,    -1,   149,    -1,    -1,    -1,    -1,    -1,    -1,   431,
      -1,    -1,    -1,    -1,   161,    -1,    -1,   439,   165,    -1,
     442,    -1,    -1,    -1,    -1,    -1,   448,    -1,    -1,    -1,
      -1,    -1,   179,    -1,    -1,    -1,    -1,    -1,    -1,   186,
      -1,    -1,   189,   190,    -1,    -1,    -1,    -1,    -1,    -1,
     197,    -1,    -1,    -1,    -1,    -1,    -1,   204,    -1,   206,
      -1,    -1,   209,    -1,    -1,     6,    -1,    -1,     9,    -1,
       3,    -1,     5,    -1,    -1,    -1,    -1,    10,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   246,
      -1,    -1,    -1,   250,    -1,   252,    -1,    -1,    49,    -1,
      -1,    -1,   259,    -1,    -1,    -1,    -1,    -1,    51,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   282,    -1,    -1,    71,    -1,
      -1,    82,    75,    -1,    -1,    86,    -1,    -1,    -1,    -1,
     297,    -1,    -1,    -1,    87,    -1,    -1,    98,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   318,    -1,    -1,    -1,    -1,    -1,    -1,   111,    -1,
     327,    -1,    -1,    -1,    -1,   118,   119,    -1,    -1,    -1,
      -1,    -1,    -1,   340,    -1,    -1,    -1,    -1,   345,    -1,
     347,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   355,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   149,    -1,   365,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   374,   161,    -1,
      -1,    -1,   165,    -1,    -1,    -1,   383,    -1,   385,   386,
      -1,    -1,   389,   184,   391,    -1,   179,    -1,    -1,   396,
      -1,    -1,    -1,   186,   195,    -1,   189,   190,    -1,    -1,
      -1,    -1,    -1,    -1,   197,   412,    -1,    -1,    -1,    -1,
     417,   204,    -1,   206,    -1,   422,   209,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   225,    -1,   433,     6,    -1,    -1,
       9,   232,    -1,    -1,    -1,   236,    -1,   238,   445,    -1,
     241,    -1,   243,    -1,    -1,    -1,    -1,    -1,   455,    -1,
      -1,    30,    -1,   246,    -1,    -1,    -1,   250,    -1,   252,
      -1,    -1,    -1,    -1,    -1,    -1,   259,    -1,    -1,    -1,
      -1,    -1,    -1,   274,    -1,    -1,    -1,     6,   279,    -1,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,   282,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,   297,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   315,    -1,    -1,    -1,    -1,    98,
      -1,    -1,    -1,    -1,   325,   318,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   327,    -1,    -1,    -1,    -1,    -1,
      -1,   342,    -1,    -1,    -1,    -1,    -1,   340,    -1,    -1,
      -1,    -1,   345,    82,   347,    -1,    -1,     6,    -1,    -1,
       9,    -1,   355,    -1,    -1,    -1,    -1,    -1,    -1,    98,
      -1,   372,   365,    -1,    -1,    -1,    -1,   378,    -1,    -1,
      -1,   374,    -1,    -1,    -1,    -1,   387,   388,    -1,    -1,
     383,    -1,   385,   386,    -1,    -1,   389,    -1,   391,    -1,
      -1,    -1,    -1,   396,    -1,   184,   407,    -1,    -1,    -1,
      -1,    -1,   413,    -1,    -1,    -1,   195,   418,    -1,   412,
     149,    -1,    -1,    -1,   417,    -1,    -1,    -1,    -1,   422,
     431,    -1,    -1,    82,   435,    -1,    -1,    -1,   439,    -1,
     433,   442,    -1,    -1,    -1,    -1,   225,   448,    -1,    98,
      -1,    -1,   445,   232,   233,   184,    -1,   236,    -1,   238,
      -1,    -1,   241,   112,   243,    -1,   195,    -1,     6,    -1,
      -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   274,   225,    -1,    -1,    -1,
      -1,    -1,    -1,   232,    -1,    -1,    -1,   236,    -1,   238,
      -1,    -1,   241,    -1,   243,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   301,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   184,   315,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,   274,   195,    -1,     6,    -1,
      -1,     9,    -1,    -1,    -1,    -1,    94,    -1,    -1,    -1,
      98,   210,    -1,   342,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   225,    -1,    -1,    -1,
      -1,    -1,    -1,   232,    -1,    -1,   315,   236,    -1,   238,
      -1,    -1,   241,    -1,   243,    -1,    -1,    -1,     6,   378,
      -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,   387,   388,
      -1,    -1,    -1,   342,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,   274,    -1,    -1,   407,    -1,
      -1,    -1,    -1,    -1,   413,    -1,    94,    -1,    -1,    -1,
      98,    -1,    -1,    -1,    -1,    -1,   184,    -1,    -1,   378,
      -1,    -1,   431,    -1,    -1,    -1,    -1,   195,   387,   388,
     439,    -1,    -1,   442,    -1,    -1,   315,    -1,    -1,   448,
      -1,    -1,    -1,    -1,    82,   404,    -1,    -1,   407,   408,
      -1,    -1,    -1,    -1,   413,    -1,    -1,   225,    -1,    -1,
      98,    -1,    -1,   342,   232,    -1,    -1,    -1,   236,    -1,
     238,    -1,   431,   241,   112,   243,    -1,    -1,    -1,    -1,
     439,    -1,    -1,   442,    -1,    -1,    -1,    -1,    -1,   448,
      -1,    -1,    -1,    -1,    -1,    -1,   184,     6,    -1,   378,
       9,    -1,    -1,    -1,    -1,    -1,   274,   195,   387,   388,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   407,    -1,
      -1,    -1,    -1,    -1,   413,    -1,    -1,   225,    -1,    -1,
      -1,    -1,    -1,    -1,   232,    -1,   184,   315,   236,    -1,
     238,    -1,   431,   241,    -1,   243,    -1,   195,    -1,     6,
     439,    -1,     9,   442,    -1,    -1,    -1,    -1,    -1,   448,
      -1,    -1,    -1,    82,   342,    -1,    -1,    -1,    -1,    -1,
      -1,     6,    -1,    -1,     9,    94,   274,   225,    -1,    98,
      -1,    -1,    -1,     6,   232,    -1,     9,    -1,   236,    -1,
     238,    -1,    -1,   241,    -1,   243,    -1,    -1,    -1,    -1,
     378,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   387,
     388,    -1,    -1,    -1,    -1,    -1,    -1,   315,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,   274,    -1,    -1,   407,
      -1,    -1,    -1,    -1,    -1,   413,    -1,    -1,    -1,    -1,
      -1,    98,    -1,    -1,   342,    -1,    -1,    82,    -1,    -1,
      -1,    -1,    -1,   431,    -1,    -1,    -1,    -1,    -1,    82,
      -1,   439,    -1,    98,   442,   184,    -1,   315,    -1,    -1,
     448,    -1,    -1,    -1,    -1,    98,   195,    -1,    -1,    -1,
     378,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   387,
     388,    -1,    -1,    -1,   342,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   225,    -1,    -1,   407,
      -1,    -1,    -1,   232,    -1,   413,    -1,   236,    -1,   238,
      -1,    -1,   241,    -1,   243,    -1,    -1,   184,    -1,    -1,
     378,    -1,    -1,   431,    -1,    -1,    -1,    -1,   195,   387,
     388,   439,    -1,    -1,   442,   180,    -1,    -1,    -1,   184,
     448,    -1,    -1,    -1,    -1,   274,    -1,    -1,    -1,   407,
     195,   184,    -1,    -1,    -1,   413,    -1,    -1,   225,    -1,
      -1,    -1,   195,    -1,    -1,   232,    -1,    -1,    -1,   236,
      -1,   238,    -1,   431,   241,    -1,   243,    -1,    -1,    -1,
     225,   439,    -1,    -1,   442,    -1,   315,   232,    -1,    -1,
     448,   236,   225,   238,    -1,    -1,   241,    -1,   243,   232,
      -1,     6,    -1,   236,     9,   238,    -1,   274,   241,    -1,
     243,    -1,    -1,   342,    -1,     6,    -1,    -1,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   274,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   274,    -1,    -1,    -1,    -1,    -1,    -1,   315,   378,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   387,   388,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     315,    -1,    -1,    -1,    -1,   342,    -1,    82,   407,    -1,
      -1,    -1,   315,    -1,   413,    -1,    -1,    -1,    -1,    -1,
      -1,    82,    -1,    98,    -1,     6,    -1,   342,     9,    -1,
      -1,    -1,   431,    -1,    -1,    -1,    -1,    98,    -1,   342,
     439,   378,    -1,   442,    -1,    -1,    -1,    -1,    -1,   448,
     387,   388,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   378,    -1,    -1,   403,    -1,    -1,   372,
     407,    -1,   387,   388,    -1,   378,   413,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   387,   388,    -1,    -1,    -1,    -1,
      -1,    -1,   407,    -1,   431,    -1,    -1,    -1,   413,    -1,
      -1,    82,   439,    -1,   407,   442,    -1,    -1,    -1,   184,
     413,   448,    -1,    -1,    -1,    -1,   431,    98,    -1,    -1,
     195,    -1,    -1,   184,   439,    -1,    -1,   442,   431,    -1,
      -1,    -1,    -1,   448,   195,    -1,   439,    -1,    -1,   442,
      -1,    -1,    -1,    -1,    -1,   448,    -1,    -1,    -1,    -1,
     225,    -1,    -1,    -1,    -1,    -1,    -1,   232,    -1,    -1,
      -1,   236,    -1,   238,   225,    -1,   241,    -1,   243,    -1,
      -1,   232,    -1,    -1,    -1,   236,    -1,   238,    -1,    -1,
     241,    -1,   243,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   274,
      -1,    -1,    -1,   184,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   274,   195,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     315,    -1,    -1,    -1,   225,    -1,    -1,    -1,    -1,    -1,
      -1,   232,    -1,    -1,   315,   236,    -1,   238,    -1,    -1,
     241,    -1,   243,    -1,    -1,    -1,    -1,   342,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   342,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   274,    -1,    -1,    -1,    -1,   373,    -1,
      -1,    -1,    -1,   378,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   387,   388,    -1,    -1,    -1,   378,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   387,   388,    -1,    -1,
      -1,    -1,   407,    -1,   315,    -1,    -1,    -1,   413,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   407,    -1,    -1,    -1,
      -1,    -1,   413,    -1,    -1,    -1,   431,    -1,    -1,    -1,
      -1,   342,    -1,    -1,   439,    -1,    -1,   442,    -1,    -1,
     431,    -1,    -1,   448,    -1,    -1,    -1,    -1,   439,    -1,
      -1,   442,    -1,    -1,    -1,    -1,    -1,   448,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,   378,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   387,   388,    -1,    -1,
      -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   407,    -1,    31,    -1,
      33,    -1,   413,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
     431,    37,    38,    39,    40,    41,    42,    43,   439,    -1,
      -1,   442,    -1,    66,    -1,    -1,    -1,   448,    -1,    -1,
      -1,    74,    -1,    76,    77,    78,    79,    80,    81,    -1,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,
      76,    77,    78,    79,    80,    81,    -1,   184,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   195,    -1,
      -1,    -1,    -1,    -1,    -1,   118,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   118,    -1,    -1,    -1,    -1,    -1,   225,    -1,
      -1,    -1,    -1,    -1,    -1,   232,    -1,    -1,    -1,   236,
      -1,   238,    -1,    -1,   241,   158,   243,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   176,    -1,    -1,    -1,   180,   181,    -1,
      82,    -1,    -1,    -1,    -1,    -1,    -1,   274,    -1,    -1,
      -1,   194,    -1,    -1,    -1,    -1,    98,    -1,   201,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   192,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   217,   201,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   315,    -1,
     233,   217,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   233,   234,    -1,
     253,    -1,    -1,    -1,    -1,   342,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   253,    -1,    -1,
      -1,    -1,   258,   276,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   184,    -1,    -1,    -1,    -1,   290,   291,    -1,
     276,   378,    -1,   195,    -1,   298,    -1,   300,    -1,    -1,
     387,   388,    -1,    -1,    -1,   291,    -1,    -1,    -1,    -1,
     313,   314,   298,    -1,   300,    -1,    -1,   303,    -1,    -1,
     407,    -1,    -1,   225,    -1,    -1,   413,   313,    -1,    -1,
     232,    -1,    -1,    -1,   236,   338,   238,    -1,    -1,   241,
     343,   243,    -1,    -1,   431,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   439,    82,   357,   442,    -1,    -1,    -1,    -1,
      -1,   448,   449,   450,   367,    -1,   369,   370,   371,    98,
     457,   458,   274,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   367,    -1,   369,   370,   371,    -1,    -1,    -1,    -1,
     376,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     403,    -1,    -1,    -1,   390,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   415,   315,    -1,    -1,   419,   420,   421,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   414,   432,
      -1,   434,   435,   419,   420,   421,    -1,    -1,    -1,    -1,
     342,    -1,    -1,    -1,    -1,    -1,   432,    -1,    -1,   435,
     436,    -1,   455,    -1,    -1,   184,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   195,    -1,    -1,   455,
      -1,    -1,    -1,    -1,    -1,    -1,   378,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   387,   388,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   225,    -1,    -1,    -1,
      -1,    -1,    -1,   232,    -1,   407,    -1,   236,    -1,   238,
      -1,   413,   241,    -1,   243,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   431,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   439,    -1,    -1,
     442,    -1,    -1,    -1,    -1,   274,   448,   449,   450,    -1,
      -1,    -1,    -1,    -1,    -1,   457,   458,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   315,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   342,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   378,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   387,   388,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   407,    -1,
      -1,    -1,    -1,    -1,   413,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   431,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     439,    -1,    -1,   442,    -1,    -1,    -1,    -1,    -1,   448,
     449,   450,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   458
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   464,   465,     0,   183,   311,   466,   467,   468,   474,
     481,   483,   455,   455,     0,   467,   150,   489,   489,   236,
     312,   484,   484,   120,   469,   475,    27,   485,   485,   455,
     102,   594,   594,   236,   455,   482,    83,   490,   120,   470,
     476,   214,   486,  1148,   356,   169,   208,   216,   544,   455,
     307,   736,   736,   455,    73,   322,   406,   487,   488,   455,
     455,   356,   455,   168,   354,   405,   595,   601,   120,   471,
     477,   481,   135,   480,   488,   310,  1160,   491,   545,   455,
     546,   356,   444,   626,   597,    54,   434,   739,   139,   471,
     478,   489,   484,   275,   337,   377,   379,   492,   493,   497,
     505,   510,   548,   169,   547,    22,   251,   350,   583,   584,
     585,   586,   588,   592,   593,   455,   356,   239,   679,   442,
     600,   602,  1078,   741,   740,   341,   747,   484,   472,   455,
     455,   455,   455,   455,   359,   549,   455,   216,   582,    60,
      72,    93,   101,   178,   405,  1144,   319,   374,   375,   587,
     455,   585,   455,   593,   596,   455,   356,   235,   681,   599,
     601,   628,   629,   630,   603,    49,   742,   743,   744,  1139,
     742,   442,   455,   455,   594,   245,   358,   442,   496,   498,
     499,   500,   501,   503,   504,  1160,   182,   506,   507,   508,
     441,   494,   495,   496,  1174,    11,    25,    26,    57,    96,
      97,    99,   108,   151,   152,   162,   237,   352,   392,   442,
     511,   512,   513,   514,   521,   530,   534,   537,   538,   539,
     540,   541,   542,   543,   283,  1125,   548,   455,   280,   280,
    1157,   403,   277,  1156,   403,   395,  1168,    24,  1135,   598,
     627,   455,   356,   332,   683,   602,   631,  1119,   604,   743,
     372,   418,   745,   325,   435,   737,   473,   372,  1148,   455,
     499,   455,   500,    63,   363,  1131,     9,   236,   509,   455,
     508,   455,   455,   495,   107,   442,  1090,  1148,  1148,  1090,
     384,   367,  1164,  1148,  1148,  1148,  1148,  1148,  1090,  1148,
      56,  1141,  1148,   455,   513,  1090,   583,   442,  1085,  1086,
    1105,  1085,  1086,   236,  1086,    85,  1142,   175,  1145,   599,
     628,   680,   455,   356,   351,   724,   628,   455,  1119,   227,
     228,   632,   635,   636,   642,     1,    47,    62,   102,   219,
     231,   319,   320,   332,   334,   435,   455,   605,   606,   608,
     612,   614,   616,   617,   623,   624,   625,  1148,  1148,   372,
     283,   746,   109,   748,   736,  1148,   236,  1108,   455,   363,
    1148,   211,   211,   236,   455,   249,   522,  1090,  1090,  1148,
    1148,  1148,  1086,    68,  1090,  1090,  1086,  1148,  1086,   531,
     532,  1090,    96,   516,  1090,   550,   200,   277,  1128,  1086,
     280,   410,   280,   589,   590,  1078,  1077,  1078,   628,   682,
     455,   356,   632,   171,   442,   638,   639,   442,   638,  1142,
    1148,   319,   321,  1129,  1129,  1148,  1142,  1148,   249,  1154,
    1148,    23,  1134,   277,   167,   188,    31,   110,  1108,  1148,
     442,   455,   738,   477,  1108,  1086,  1148,   195,   236,   243,
     315,   378,   407,   448,   535,   536,  1111,  1086,   236,  1086,
      23,   214,  1090,  1149,   278,   280,   518,   519,   520,   515,
     551,  1105,  1085,   280,  1085,   590,   301,   591,  1078,   628,
     684,   455,   633,    84,   634,  1108,   442,  1148,  1134,  1087,
    1105,   279,   380,   613,   236,  1086,  1089,  1108,   436,  1148,
     442,   723,   723,   170,   442,  1108,   749,   750,   139,   479,
      56,   443,   502,   124,   195,   236,   243,   255,   315,   378,
     381,   382,   448,   523,   524,   525,   528,   536,   400,   533,
    1108,   519,   384,  1167,   517,     1,     4,    19,    29,   202,
     233,   240,   261,   286,   292,   319,   326,   339,   364,   366,
     374,   405,   455,   552,   553,   558,   560,   565,   566,   567,
     568,   572,   573,   574,   575,   576,   577,   578,   579,   581,
    1131,  1085,  1108,   317,   685,   686,   687,   725,   643,   640,
    1148,   435,   672,   403,   611,  1105,   234,  1152,   403,  1141,
     200,  1147,   442,  1148,  1148,   750,     1,   442,   751,   752,
     753,   754,   755,   760,   484,   525,    17,   400,  1111,  1108,
    1148,   519,  1154,   319,   403,  1172,   364,  1154,   218,  1150,
    1148,    55,  1140,    37,   113,  1138,  1150,  1150,   260,  1108,
    1174,   384,  1148,   723,   687,   726,     1,    21,    34,    37,
      38,    39,    40,    41,    42,    43,    74,    76,    77,    78,
      79,    80,    81,   118,   201,   217,   236,   253,   276,   291,
     298,   300,   313,   323,   330,   367,   369,   370,   371,   393,
     419,   420,   421,   432,   435,   637,   644,   645,   646,   648,
     649,   650,   651,   652,   654,   666,   667,   669,   670,   671,
     677,   678,  1148,  1165,    27,  1136,   188,  1149,  1108,    56,
     321,   607,   618,  1108,   372,  1166,   236,   615,  1105,   615,
     126,   455,   356,     3,     5,    10,    18,    51,    52,    59,
      71,    75,    87,   111,   118,   119,   149,   161,   165,   179,
     186,   189,   190,   197,   204,   206,   209,   246,   250,   252,
     259,   282,   297,   318,   327,   340,   345,   347,   355,   365,
     374,   383,   385,   386,   389,   391,   396,   412,   417,   422,
     433,   445,   455,   761,   762,   772,   777,   781,   784,   797,
     800,   805,   810,   811,   812,   815,   817,   824,   828,   830,
     845,   848,   850,   852,   855,   857,   863,   872,   874,   891,
     893,   896,   900,   906,   916,   923,   925,   928,   932,   933,
     944,   955,   965,   971,   975,   981,   985,   987,   989,   991,
     994,  1005,  1006,  1015,  1017,  1018,   455,   526,   528,  1090,
    1148,  1150,   123,   167,   555,  1148,  1148,   319,   326,   573,
    1148,  1148,   364,  1148,  1148,  1135,     9,   260,   318,   580,
    1148,   442,   688,   635,   642,   727,   728,   729,   225,   368,
     418,   368,   418,   368,   418,   368,   418,   368,   418,   438,
    1173,   346,  1162,  1108,  1104,  1105,  1105,   214,   224,   346,
     668,  1148,  1148,   167,   188,   223,   411,     9,    50,   225,
     641,  1109,  1110,  1111,   674,   675,  1109,    30,   619,   620,
     621,   622,  1137,  1174,  1141,   180,   610,  1146,   109,   236,
     756,   763,   773,   778,   782,   785,   798,   801,   806,   813,
     816,   818,   825,   829,   831,   846,   849,   851,  1172,   856,
       1,   858,   864,   873,   875,   892,   894,   897,   901,   907,
     917,   924,   926,   929,   934,   945,   956,   966,   236,   349,
     976,   982,   306,   986,   988,   990,   992,   995,   188,  1007,
    1145,  1019,   195,   236,   243,   315,   378,   448,   527,   529,
     123,   316,   364,   559,  1148,   117,   305,   554,    32,   164,
     244,   569,  1086,  1089,   381,  1086,  1086,   287,  1159,  1159,
     281,  1086,    61,    88,    89,   293,   455,   689,   690,   694,
    1148,   638,   729,   448,   403,   655,   458,  1106,  1107,   400,
     651,  1109,    27,   647,   362,  1127,  1127,  1111,  1156,  1156,
     462,   673,   675,   400,    48,   409,   174,   611,  1108,   455,
     455,   764,  1103,  1104,     6,    82,    94,    98,   184,   225,
     232,   238,   241,   274,   342,   387,   388,   413,   431,   439,
     774,  1072,  1093,  1094,  1103,  1109,  1112,   442,   779,  1059,
    1060,  1061,   236,  1082,  1083,  1084,  1105,   236,  1101,  1103,
    1112,   799,   802,   807,  1073,  1074,  1094,  1078,   405,   236,
     819,  1093,  1100,  1103,   826,  1094,   236,   404,   408,   832,
     833,  1059,   296,   297,   310,   356,   847,     6,  1091,  1092,
    1103,  1103,   853,   136,  1058,  1059,  1091,   693,  1103,   876,
    1103,  1109,  1112,   957,  1105,    94,   895,  1094,   898,  1094,
     902,   177,   236,   908,   911,   912,   913,  1082,  1101,  1105,
    1174,  1078,  1075,  1105,  1078,  1075,     9,   935,  1076,  1105,
     150,   248,   946,   947,   948,   949,   951,   952,   953,   954,
    1079,  1080,  1091,   957,  1078,   973,   972,   112,   977,   978,
    1094,    94,   983,  1093,   693,  1103,  1078,  1103,     8,    35,
    1009,   107,  1075,    17,  1086,   118,   236,   556,  1153,   441,
     570,   570,   376,   456,   564,  1086,  1088,  1148,   172,   691,
     692,   691,  1149,   702,   188,   730,  1108,   402,  1171,   225,
     449,   450,   458,  1069,  1071,  1072,  1095,  1103,  1110,  1112,
     458,  1107,  1105,   236,  1140,  1104,  1104,  1111,  1173,  1109,
    1089,  1089,  1137,  1141,   127,   771,    30,   180,   765,  1137,
    1156,   458,  1103,   458,  1113,   458,  1114,  1156,  1128,   458,
     458,   458,   458,   458,   458,   458,   458,  1113,   128,   776,
     403,   775,  1094,   205,  1122,    56,  1062,  1063,   403,  1128,
     434,   786,   236,  1100,  1103,  1078,   130,   808,   156,   456,
     809,  1074,   348,  1126,   319,  1161,  1077,   132,   823,   765,
     427,   428,   429,   430,   133,   827,    49,   210,   786,    17,
     438,   834,   835,   836,   840,  1133,   100,  1156,  1092,  1081,
     399,  1170,   865,  1174,  1103,    92,   331,   394,   877,   878,
     879,   883,   888,   959,  1094,   403,   137,   899,    49,   166,
     207,   215,   288,   903,   912,   138,   909,   423,   436,   400,
     402,   397,   258,   304,  1123,   180,  1020,  1161,  1020,  1076,
     143,   943,   436,   937,  1098,  1103,  1110,   952,   954,  1091,
     403,  1080,   121,   403,   424,   950,   967,   187,   341,   974,
    1139,   210,   978,  1103,   146,   984,   180,   180,   319,   321,
     993,   112,   996,   333,   380,  1010,  1157,  1020,   529,   122,
     441,   564,  1121,  1130,   557,  1105,   240,   347,  1148,   561,
     562,  1100,   693,   700,  1108,   635,   703,   731,   114,   656,
    1156,  1071,  1071,  1071,    70,   360,   457,  1070,   449,   450,
     451,   452,   454,   461,  1071,   365,  1163,  1152,  1089,   114,
     609,  1098,    25,    26,    67,    69,   103,   104,   105,   150,
     152,   160,   234,   401,   442,  1080,   441,   768,    66,   233,
     301,   766,   767,   149,   310,  1096,  1104,  1069,  1071,   403,
    1071,  1069,  1115,  1104,  1110,  1112,   442,  1071,  1118,  1071,
    1071,  1117,  1071,  1069,  1069,  1071,  1116,  1071,  1073,  1094,
     187,   341,   780,  1122,    12,    13,    14,    20,    58,   156,
     157,   185,   191,   214,   222,   226,   256,   257,   262,   272,
     279,   284,   302,   448,   449,   450,   451,   452,   454,   456,
     457,   459,   460,  1064,  1065,  1066,  1067,  1068,    12,    13,
      14,    58,   214,   256,   257,   262,   272,   279,   302,   449,
     450,   454,   458,  1064,  1065,  1066,  1067,  1068,  1094,   309,
     783,  1084,   787,   187,   341,   791,   324,   416,   803,   804,
    1174,  1059,   213,   266,  1051,  1052,  1053,  1055,   426,   441,
     820,  1174,   163,  1026,  1027,  1026,  1026,  1026,  1094,  1073,
    1094,    21,   404,   408,   841,   842,  1060,   134,   844,   440,
     836,   838,   438,   837,   833,  1104,   114,   854,  1082,   859,
       9,    12,    15,    16,   253,   254,   272,   273,   866,   870,
     171,  1098,     9,    56,   173,   223,   411,   884,   885,   886,
     880,   878,   961,  1130,  1157,   403,  1091,  1073,  1094,   366,
     904,   757,   758,  1058,   914,   915,  1103,  1082,     8,    35,
    1022,  1161,  1100,   210,   918,   930,  1174,   938,  1137,  1103,
     938,   403,   403,   520,   149,   404,   408,  1094,    49,   218,
     968,  1094,  1094,   372,  1094,  1103,   180,  1073,  1094,  1098,
    1139,   210,   999,  1103,   159,   163,  1011,     9,  1016,  1082,
     930,   122,   561,  1105,   280,   563,  1086,   563,   193,   695,
     233,   234,   701,   638,    31,    33,    36,    44,    45,    46,
      66,   158,   176,   180,   181,   194,   233,   242,   276,   290,
     314,   338,   343,   357,   403,   415,   434,   455,   649,   650,
     652,   666,   669,   671,   732,   735,  1157,    28,   115,   202,
     653,   658,   659,   660,   661,   663,  1104,  1110,  1112,   457,
    1071,  1071,  1071,  1071,  1071,  1071,   457,  1071,  1172,  1152,
    1157,  1025,  1027,   447,   446,  1098,  1025,   218,    31,    33,
      36,    46,   176,   181,   194,   242,   290,   314,   338,   343,
     353,   357,   415,   425,   769,   770,  1025,   270,  1155,  1155,
    1155,   767,   766,   236,  1097,  1104,   457,  1103,   461,   457,
    1070,   457,   457,  1070,   457,   457,   457,   457,  1070,   457,
     457,   373,  1031,  1032,  1073,  1092,   341,  1172,   398,  1169,
    1169,   403,  1082,   788,   789,   790,  1139,  1103,  1103,   163,
     289,   792,  1012,  1145,   240,   260,  1031,  1054,  1056,   131,
     814,  1055,    96,   305,   442,  1080,    33,    36,    44,    45,
      46,   158,   176,   194,   242,   290,   343,   353,   415,   821,
     822,  1026,   269,  1028,   265,  1029,   187,  1031,   187,  1133,
     400,   843,   839,   841,   757,  1157,   757,  1172,   331,   867,
    1172,   403,    49,   885,   887,  1098,     9,    56,   223,   411,
     881,   882,  1098,   962,  1131,   200,   285,  1158,   661,  1091,
    1031,   187,  1174,  1077,   138,   910,   759,     8,   180,   918,
    1103,   126,   263,  1041,  1042,  1044,  1051,   240,   260,   438,
     126,   438,   940,   941,  1098,  1097,  1094,  1148,  1051,   979,
    1174,  1103,  1031,   187,   403,     9,   997,   998,  1120,  1000,
    1103,   979,  1000,   307,  1014,   308,  1021,  1022,  1121,   251,
     319,   321,   571,  1148,   173,   696,  1108,   704,  1148,  1155,
     153,   155,  1148,  1101,  1155,  1108,  1103,  1103,  1086,  1139,
     662,   663,   659,  1150,   657,   658,   457,   404,   676,  1086,
    1029,  1025,  1148,  1148,   121,   424,   770,  1100,  1100,  1100,
    1113,  1126,   457,  1071,  1086,  1113,  1113,  1071,  1113,  1113,
    1113,   223,   411,  1113,  1113,  1033,   268,  1034,  1031,  1092,
     156,   284,   156,   284,   789,   279,   745,    86,   325,   435,
     265,   267,   794,  1013,   793,   329,   344,   757,   757,   820,
     820,   820,   820,  1148,   153,   155,  1148,   121,   424,   822,
     757,  1030,  1073,  1074,  1073,  1074,   842,  1059,   757,  1103,
     125,   860,   435,   868,   869,   870,   110,   871,   435,  1099,
    1103,  1109,  1098,    49,   889,   882,   175,   889,   958,  1148,
     285,  1150,  1073,   580,   905,  1174,   760,   915,  1094,   199,
     919,  1174,  1043,  1045,   141,   927,  1044,   142,   931,   240,
    1059,   939,  1058,   940,   262,   969,  1124,   144,   970,   289,
    1036,  1037,   300,  1126,  1073,  1099,   284,  1098,   113,  1001,
     394,  1003,  1157,   154,   264,  1023,  1046,  1047,  1049,  1052,
       7,  1132,   571,  1108,   116,   220,   697,    67,    66,    67,
     192,   233,   234,   258,   303,   376,   390,   414,   436,   455,
     649,   650,   652,   654,   666,   669,   671,   705,   706,   708,
     709,   710,   711,   713,   714,   715,   716,   720,   721,   448,
    1102,  1103,  1108,  1148,  1102,  1148,  1171,   442,   664,   665,
    1148,  1148,  1102,  1102,  1057,  1139,  1057,  1031,   457,   757,
    1035,  1172,   156,  1172,   156,  1094,   129,   796,   795,   757,
    1026,  1026,  1026,  1026,  1102,  1102,  1057,  1057,   757,  1031,
     328,  1031,   328,   861,   136,   862,   869,   102,  1143,   889,
     889,  1099,  1022,   207,   434,   963,  1086,  1148,  1031,   240,
     260,    49,   240,   218,   920,   198,   240,   260,   437,   757,
     757,   936,   757,   942,   693,  1064,  1065,  1066,  1067,  1068,
    1038,   145,   980,   267,  1039,  1103,  1031,  1031,   998,  1147,
      95,  1002,  1147,  1036,   166,   207,   215,   288,  1008,  1077,
    1048,  1050,   148,  1024,  1049,   293,  1080,  1102,  1148,    91,
     221,   698,   271,  1155,   203,   722,   270,   271,   719,  1134,
     192,   438,  1148,  1156,  1148,  1103,   711,   258,   299,   717,
     718,  1108,   247,   299,   449,   450,   734,   247,   299,   449,
     450,   733,   665,  1085,  1109,  1102,   757,  1172,  1172,   757,
    1074,  1074,   757,    49,   889,   406,   890,   307,  1077,   187,
     288,   964,   960,   344,  1094,  1148,   921,  1041,  1052,   240,
     240,   757,   757,   757,  1040,  1103,  1147,  1103,   147,  1004,
     757,   757,   233,   234,  1151,  1108,  1148,  1148,   174,   699,
    1148,  1149,  1148,  1058,  1103,   712,  1086,    90,    91,   116,
     294,   295,   335,   336,   707,   180,   293,  1108,   718,  1102,
    1102,  1151,  1031,  1031,  1094,  1094,  1148,  1077,   307,  1105,
     423,   693,   140,   922,   757,  1103,  1108,  1108,  1148,  1108,
    1108,  1126,  1094,   911,  1148,  1058,  1108,    49,   911,  1094
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
#line 6035 "parser.y"
    { BEGIN_STATEMENT ("STOP", 0); ;}
    break;

  case 1146:

/* Line 1455 of yacc.c  */
#line 6036 "parser.y"
    {
	cb_verify (cb_stop_literal_statement, "STOP literal");
  ;}
    break;

  case 1147:

/* Line 1455 of yacc.c  */
#line 6042 "parser.y"
    { (yyval) = current_program->cb_return_code; ;}
    break;

  case 1148:

/* Line 1455 of yacc.c  */
#line 6043 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1149:

/* Line 1455 of yacc.c  */
#line 6044 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1150:

/* Line 1455 of yacc.c  */
#line 6053 "parser.y"
    { BEGIN_STATEMENT ("STRING", TERM_STRING); ;}
    break;

  case 1151:

/* Line 1455 of yacc.c  */
#line 6056 "parser.y"
    {
	cb_emit_string ((yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]));
  ;}
    break;

  case 1152:

/* Line 1455 of yacc.c  */
#line 6062 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1153:

/* Line 1455 of yacc.c  */
#line 6063 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1154:

/* Line 1455 of yacc.c  */
#line 6067 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1155:

/* Line 1455 of yacc.c  */
#line 6068 "parser.y"
    { (yyval) = cb_build_pair (cb_int0, NULL); ;}
    break;

  case 1156:

/* Line 1455 of yacc.c  */
#line 6069 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), NULL); ;}
    break;

  case 1157:

/* Line 1455 of yacc.c  */
#line 6073 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1158:

/* Line 1455 of yacc.c  */
#line 6074 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1159:

/* Line 1455 of yacc.c  */
#line 6078 "parser.y"
    { terminator_warning (TERM_STRING); ;}
    break;

  case 1160:

/* Line 1455 of yacc.c  */
#line 6079 "parser.y"
    { terminator_clear (TERM_STRING); ;}
    break;

  case 1161:

/* Line 1455 of yacc.c  */
#line 6088 "parser.y"
    { BEGIN_STATEMENT ("SUBTRACT", TERM_SUBTRACT); ;}
    break;

  case 1163:

/* Line 1455 of yacc.c  */
#line 6095 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '-', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 1164:

/* Line 1455 of yacc.c  */
#line 6099 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_list (cb_cons ((yyvsp[(3) - (6)]), (yyvsp[(1) - (6)])), '-'));
  ;}
    break;

  case 1165:

/* Line 1455 of yacc.c  */
#line 6103 "parser.y"
    {
	cb_emit_corresponding (cb_build_sub, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 1166:

/* Line 1455 of yacc.c  */
#line 6109 "parser.y"
    { terminator_warning (TERM_SUBTRACT); ;}
    break;

  case 1167:

/* Line 1455 of yacc.c  */
#line 6110 "parser.y"
    { terminator_clear (TERM_SUBTRACT); ;}
    break;

  case 1168:

/* Line 1455 of yacc.c  */
#line 6120 "parser.y"
    {
	BEGIN_STATEMENT ("SUPPRESS", 0);
	PENDING("SUPPRESS");
  ;}
    break;

  case 1171:

/* Line 1455 of yacc.c  */
#line 6135 "parser.y"
    { BEGIN_STATEMENT ("TERMINATE", 0); ;}
    break;

  case 1172:

/* Line 1455 of yacc.c  */
#line 6137 "parser.y"
    {
	PENDING("TERMINATE");
  ;}
    break;

  case 1173:

/* Line 1455 of yacc.c  */
#line 6148 "parser.y"
    { BEGIN_STATEMENT ("TRANSFORM", 0); ;}
    break;

  case 1174:

/* Line 1455 of yacc.c  */
#line 6150 "parser.y"
    {
	cb_tree		x;

	x = cb_build_converting ((yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]), cb_build_inspect_region_start ());
	cb_emit_inspect ((yyvsp[(3) - (7)]), x, cb_int0, 2);
  ;}
    break;

  case 1175:

/* Line 1455 of yacc.c  */
#line 6164 "parser.y"
    { BEGIN_STATEMENT ("UNLOCK", 0); ;}
    break;

  case 1176:

/* Line 1455 of yacc.c  */
#line 6166 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_unlock ((yyvsp[(3) - (4)]));
	}
  ;}
    break;

  case 1180:

/* Line 1455 of yacc.c  */
#line 6185 "parser.y"
    { BEGIN_STATEMENT ("UNSTRING", TERM_UNSTRING); ;}
    break;

  case 1181:

/* Line 1455 of yacc.c  */
#line 6189 "parser.y"
    {
	cb_emit_unstring ((yyvsp[(3) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]));
  ;}
    break;

  case 1182:

/* Line 1455 of yacc.c  */
#line 6195 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1183:

/* Line 1455 of yacc.c  */
#line 6197 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1184:

/* Line 1455 of yacc.c  */
#line 6201 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1185:

/* Line 1455 of yacc.c  */
#line 6203 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1186:

/* Line 1455 of yacc.c  */
#line 6208 "parser.y"
    {
	(yyval) = cb_build_unstring_delimited ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1187:

/* Line 1455 of yacc.c  */
#line 6214 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 1188:

/* Line 1455 of yacc.c  */
#line 6216 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1189:

/* Line 1455 of yacc.c  */
#line 6221 "parser.y"
    {
	(yyval) = cb_build_unstring_into ((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1190:

/* Line 1455 of yacc.c  */
#line 6227 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1191:

/* Line 1455 of yacc.c  */
#line 6228 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1192:

/* Line 1455 of yacc.c  */
#line 6232 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1193:

/* Line 1455 of yacc.c  */
#line 6233 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1194:

/* Line 1455 of yacc.c  */
#line 6237 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1195:

/* Line 1455 of yacc.c  */
#line 6238 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1196:

/* Line 1455 of yacc.c  */
#line 6242 "parser.y"
    { terminator_warning (TERM_UNSTRING); ;}
    break;

  case 1197:

/* Line 1455 of yacc.c  */
#line 6243 "parser.y"
    { terminator_clear (TERM_UNSTRING); ;}
    break;

  case 1201:

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

  case 1202:

/* Line 1455 of yacc.c  */
#line 6282 "parser.y"
    {
	use_global_ind = 0;
  ;}
    break;

  case 1203:

/* Line 1455 of yacc.c  */
#line 6286 "parser.y"
    {
	use_global_ind = 1;
	current_program->flag_global_use = 1;
  ;}
    break;

  case 1204:

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

  case 1205:

/* Line 1455 of yacc.c  */
#line 6304 "parser.y"
    {
	current_program->global_handler[COB_OPEN_INPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_INPUT].handler_prog = current_program;
  ;}
    break;

  case 1206:

/* Line 1455 of yacc.c  */
#line 6309 "parser.y"
    {
	current_program->global_handler[COB_OPEN_OUTPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_OUTPUT].handler_prog = current_program;
  ;}
    break;

  case 1207:

/* Line 1455 of yacc.c  */
#line 6314 "parser.y"
    {
	current_program->global_handler[COB_OPEN_I_O].handler_label = current_section;
	current_program->global_handler[COB_OPEN_I_O].handler_prog = current_program;
  ;}
    break;

  case 1208:

/* Line 1455 of yacc.c  */
#line 6319 "parser.y"
    {
	current_program->global_handler[COB_OPEN_EXTEND].handler_label = current_section;
	current_program->global_handler[COB_OPEN_EXTEND].handler_prog = current_program;
  ;}
    break;

  case 1221:

/* Line 1455 of yacc.c  */
#line 6351 "parser.y"
    {
	PENDING ("USE FOR DEBUGGING");
  ;}
    break;

  case 1224:

/* Line 1455 of yacc.c  */
#line 6363 "parser.y"
    {
	PENDING ("USE BEFORE REPORTING");
  ;}
    break;

  case 1225:

/* Line 1455 of yacc.c  */
#line 6374 "parser.y"
    { BEGIN_STATEMENT ("WRITE", TERM_WRITE); ;}
    break;

  case 1226:

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

  case 1227:

/* Line 1455 of yacc.c  */
#line 6391 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1228:

/* Line 1455 of yacc.c  */
#line 6392 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1229:

/* Line 1455 of yacc.c  */
#line 6397 "parser.y"
    {
	(yyval) = cb_int0;
  ;}
    break;

  case 1230:

/* Line 1455 of yacc.c  */
#line 6401 "parser.y"
    {
	(yyval) = cb_build_write_advancing_lines ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 1231:

/* Line 1455 of yacc.c  */
#line 6405 "parser.y"
    {
	(yyval) = cb_build_write_advancing_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1232:

/* Line 1455 of yacc.c  */
#line 6409 "parser.y"
    {
	(yyval) = cb_build_write_advancing_page ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1233:

/* Line 1455 of yacc.c  */
#line 6415 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1234:

/* Line 1455 of yacc.c  */
#line 6416 "parser.y"
    { (yyval) = CB_AFTER; ;}
    break;

  case 1238:

/* Line 1455 of yacc.c  */
#line 6425 "parser.y"
    { terminator_warning (TERM_WRITE); ;}
    break;

  case 1239:

/* Line 1455 of yacc.c  */
#line 6426 "parser.y"
    { terminator_clear (TERM_WRITE); ;}
    break;

  case 1240:

/* Line 1455 of yacc.c  */
#line 6441 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_ACCEPT;
  ;}
    break;

  case 1241:

/* Line 1455 of yacc.c  */
#line 6449 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_DISPLAY;
  ;}
    break;

  case 1243:

/* Line 1455 of yacc.c  */
#line 6456 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1244:

/* Line 1455 of yacc.c  */
#line 6460 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1246:

/* Line 1455 of yacc.c  */
#line 6467 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1247:

/* Line 1455 of yacc.c  */
#line 6471 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1250:

/* Line 1455 of yacc.c  */
#line 6487 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1251:

/* Line 1455 of yacc.c  */
#line 6492 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1253:

/* Line 1455 of yacc.c  */
#line 6499 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1254:

/* Line 1455 of yacc.c  */
#line 6504 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1255:

/* Line 1455 of yacc.c  */
#line 6516 "parser.y"
    {
	current_statement->handler_id = COB_EC_OVERFLOW;
  ;}
    break;

  case 1257:

/* Line 1455 of yacc.c  */
#line 6523 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1258:

/* Line 1455 of yacc.c  */
#line 6527 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1260:

/* Line 1455 of yacc.c  */
#line 6534 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1261:

/* Line 1455 of yacc.c  */
#line 6538 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1262:

/* Line 1455 of yacc.c  */
#line 6550 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1263:

/* Line 1455 of yacc.c  */
#line 6555 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1264:

/* Line 1455 of yacc.c  */
#line 6560 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1265:

/* Line 1455 of yacc.c  */
#line 6569 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1266:

/* Line 1455 of yacc.c  */
#line 6573 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1267:

/* Line 1455 of yacc.c  */
#line 6580 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1268:

/* Line 1455 of yacc.c  */
#line 6584 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1269:

/* Line 1455 of yacc.c  */
#line 6596 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1270:

/* Line 1455 of yacc.c  */
#line 6601 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1271:

/* Line 1455 of yacc.c  */
#line 6606 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1272:

/* Line 1455 of yacc.c  */
#line 6615 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1273:

/* Line 1455 of yacc.c  */
#line 6619 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1274:

/* Line 1455 of yacc.c  */
#line 6626 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1275:

/* Line 1455 of yacc.c  */
#line 6630 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1278:

/* Line 1455 of yacc.c  */
#line 6646 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1279:

/* Line 1455 of yacc.c  */
#line 6651 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1280:

/* Line 1455 of yacc.c  */
#line 6656 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1281:

/* Line 1455 of yacc.c  */
#line 6665 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1282:

/* Line 1455 of yacc.c  */
#line 6669 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1283:

/* Line 1455 of yacc.c  */
#line 6676 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1284:

/* Line 1455 of yacc.c  */
#line 6680 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1285:

/* Line 1455 of yacc.c  */
#line 6692 "parser.y"
    {
	(yyval) = cb_one;
  ;}
    break;

  case 1286:

/* Line 1455 of yacc.c  */
#line 6696 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 1287:

/* Line 1455 of yacc.c  */
#line 6708 "parser.y"
    {
	(yyval) = cb_build_cond ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1288:

/* Line 1455 of yacc.c  */
#line 6715 "parser.y"
    {
	(yyval) = cb_build_expr ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1289:

/* Line 1455 of yacc.c  */
#line 6721 "parser.y"
    {
	current_expr = NULL;
  ;}
    break;

  case 1290:

/* Line 1455 of yacc.c  */
#line 6725 "parser.y"
    {
	(yyval) = cb_list_reverse (current_expr);
  ;}
    break;

  case 1291:

/* Line 1455 of yacc.c  */
#line 6731 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1292:

/* Line 1455 of yacc.c  */
#line 6732 "parser.y"
    { push_expr (')', NULL); ;}
    break;

  case 1293:

/* Line 1455 of yacc.c  */
#line 6734 "parser.y"
    { push_expr ('O', NULL); ;}
    break;

  case 1294:

/* Line 1455 of yacc.c  */
#line 6735 "parser.y"
    { push_expr ('9', NULL); ;}
    break;

  case 1295:

/* Line 1455 of yacc.c  */
#line 6736 "parser.y"
    { push_expr ('A', NULL); ;}
    break;

  case 1296:

/* Line 1455 of yacc.c  */
#line 6737 "parser.y"
    { push_expr ('L', NULL); ;}
    break;

  case 1297:

/* Line 1455 of yacc.c  */
#line 6738 "parser.y"
    { push_expr ('U', NULL); ;}
    break;

  case 1298:

/* Line 1455 of yacc.c  */
#line 6739 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1299:

/* Line 1455 of yacc.c  */
#line 6741 "parser.y"
    { push_expr ('O', NULL); ;}
    break;

  case 1300:

/* Line 1455 of yacc.c  */
#line 6742 "parser.y"
    { push_expr ('9', NULL); ;}
    break;

  case 1301:

/* Line 1455 of yacc.c  */
#line 6743 "parser.y"
    { push_expr ('A', NULL); ;}
    break;

  case 1302:

/* Line 1455 of yacc.c  */
#line 6744 "parser.y"
    { push_expr ('L', NULL); ;}
    break;

  case 1303:

/* Line 1455 of yacc.c  */
#line 6745 "parser.y"
    { push_expr ('U', NULL); ;}
    break;

  case 1304:

/* Line 1455 of yacc.c  */
#line 6746 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1305:

/* Line 1455 of yacc.c  */
#line 6748 "parser.y"
    { push_expr ('P', NULL); ;}
    break;

  case 1306:

/* Line 1455 of yacc.c  */
#line 6749 "parser.y"
    { push_expr ('N', NULL); ;}
    break;

  case 1307:

/* Line 1455 of yacc.c  */
#line 6751 "parser.y"
    { push_expr ('P', NULL); ;}
    break;

  case 1308:

/* Line 1455 of yacc.c  */
#line 6752 "parser.y"
    { push_expr ('N', NULL); ;}
    break;

  case 1309:

/* Line 1455 of yacc.c  */
#line 6753 "parser.y"
    { push_expr ('x', cb_zero); ;}
    break;

  case 1313:

/* Line 1455 of yacc.c  */
#line 6760 "parser.y"
    { push_expr ('(', NULL); ;}
    break;

  case 1314:

/* Line 1455 of yacc.c  */
#line 6762 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1315:

/* Line 1455 of yacc.c  */
#line 6763 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1316:

/* Line 1455 of yacc.c  */
#line 6764 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1317:

/* Line 1455 of yacc.c  */
#line 6766 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1318:

/* Line 1455 of yacc.c  */
#line 6767 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1319:

/* Line 1455 of yacc.c  */
#line 6769 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1320:

/* Line 1455 of yacc.c  */
#line 6770 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1321:

/* Line 1455 of yacc.c  */
#line 6771 "parser.y"
    { push_expr ('*', NULL); ;}
    break;

  case 1322:

/* Line 1455 of yacc.c  */
#line 6772 "parser.y"
    { push_expr ('/', NULL); ;}
    break;

  case 1323:

/* Line 1455 of yacc.c  */
#line 6773 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1324:

/* Line 1455 of yacc.c  */
#line 6775 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1325:

/* Line 1455 of yacc.c  */
#line 6776 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1326:

/* Line 1455 of yacc.c  */
#line 6777 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1327:

/* Line 1455 of yacc.c  */
#line 6778 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1328:

/* Line 1455 of yacc.c  */
#line 6779 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1329:

/* Line 1455 of yacc.c  */
#line 6780 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1330:

/* Line 1455 of yacc.c  */
#line 6782 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1331:

/* Line 1455 of yacc.c  */
#line 6783 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1332:

/* Line 1455 of yacc.c  */
#line 6784 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1333:

/* Line 1455 of yacc.c  */
#line 6785 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1334:

/* Line 1455 of yacc.c  */
#line 6786 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1335:

/* Line 1455 of yacc.c  */
#line 6787 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1336:

/* Line 1455 of yacc.c  */
#line 6789 "parser.y"
    { push_expr ('&', NULL); ;}
    break;

  case 1337:

/* Line 1455 of yacc.c  */
#line 6790 "parser.y"
    { push_expr ('|', NULL); ;}
    break;

  case 1351:

/* Line 1455 of yacc.c  */
#line 6802 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1352:

/* Line 1455 of yacc.c  */
#line 6803 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1356:

/* Line 1455 of yacc.c  */
#line 6812 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1357:

/* Line 1455 of yacc.c  */
#line 6813 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '+', (yyvsp[(3) - (3)])); ;}
    break;

  case 1358:

/* Line 1455 of yacc.c  */
#line 6814 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '-', (yyvsp[(3) - (3)])); ;}
    break;

  case 1359:

/* Line 1455 of yacc.c  */
#line 6815 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '*', (yyvsp[(3) - (3)])); ;}
    break;

  case 1360:

/* Line 1455 of yacc.c  */
#line 6816 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '/', (yyvsp[(3) - (3)])); ;}
    break;

  case 1361:

/* Line 1455 of yacc.c  */
#line 6817 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1362:

/* Line 1455 of yacc.c  */
#line 6818 "parser.y"
    { (yyval) = cb_build_binary_op (cb_zero, '-', (yyvsp[(2) - (2)])); ;}
    break;

  case 1363:

/* Line 1455 of yacc.c  */
#line 6819 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '^', (yyvsp[(3) - (3)])); ;}
    break;

  case 1364:

/* Line 1455 of yacc.c  */
#line 6820 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1365:

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

  case 1366:

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

  case 1367:

/* Line 1455 of yacc.c  */
#line 6858 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1368:

/* Line 1455 of yacc.c  */
#line 6860 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1369:

/* Line 1455 of yacc.c  */
#line 6864 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)])); ;}
    break;

  case 1370:

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

  case 1371:

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

  case 1372:

/* Line 1455 of yacc.c  */
#line 6913 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1373:

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

  case 1374:

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

  case 1375:

/* Line 1455 of yacc.c  */
#line 6946 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1376:

/* Line 1455 of yacc.c  */
#line 6948 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1377:

/* Line 1455 of yacc.c  */
#line 6952 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1378:

/* Line 1455 of yacc.c  */
#line 6958 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1379:

/* Line 1455 of yacc.c  */
#line 6960 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1380:

/* Line 1455 of yacc.c  */
#line 6965 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	CB_REFERENCE ((yyval))->offset = CB_TREE (current_section);
	current_program->label_list = cb_cons ((yyval), current_program->label_list);
  ;}
    break;

  case 1384:

/* Line 1455 of yacc.c  */
#line 6980 "parser.y"
    {
	(yyval) = cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(1) - (1)]))->data));
	(yyval)->source_file = (yyvsp[(1) - (1)])->source_file;
	(yyval)->source_line = (yyvsp[(1) - (1)])->source_line;
  ;}
    break;

  case 1385:

/* Line 1455 of yacc.c  */
#line 6990 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1386:

/* Line 1455 of yacc.c  */
#line 6991 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1387:

/* Line 1455 of yacc.c  */
#line 6996 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	current_program->reference_list = cb_cons ((yyval), current_program->reference_list);
  ;}
    break;

  case 1388:

/* Line 1455 of yacc.c  */
#line 7005 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1389:

/* Line 1455 of yacc.c  */
#line 7006 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1390:

/* Line 1455 of yacc.c  */
#line 7010 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1391:

/* Line 1455 of yacc.c  */
#line 7011 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1394:

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

  case 1395:

/* Line 1455 of yacc.c  */
#line 7042 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1396:

/* Line 1455 of yacc.c  */
#line 7043 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1398:

/* Line 1455 of yacc.c  */
#line 7048 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1399:

/* Line 1455 of yacc.c  */
#line 7052 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1400:

/* Line 1455 of yacc.c  */
#line 7053 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1402:

/* Line 1455 of yacc.c  */
#line 7058 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1403:

/* Line 1455 of yacc.c  */
#line 7059 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1404:

/* Line 1455 of yacc.c  */
#line 7060 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1405:

/* Line 1455 of yacc.c  */
#line 7061 "parser.y"
    { (yyval) = cb_build_ppointer ((yyvsp[(4) - (4)])); ;}
    break;

  case 1406:

/* Line 1455 of yacc.c  */
#line 7062 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1411:

/* Line 1455 of yacc.c  */
#line 7070 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1412:

/* Line 1455 of yacc.c  */
#line 7071 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1413:

/* Line 1455 of yacc.c  */
#line 7072 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1419:

/* Line 1455 of yacc.c  */
#line 7084 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1420:

/* Line 1455 of yacc.c  */
#line 7085 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1432:

/* Line 1455 of yacc.c  */
#line 7119 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1433:

/* Line 1455 of yacc.c  */
#line 7127 "parser.y"
    { (yyval) = cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1434:

/* Line 1455 of yacc.c  */
#line 7131 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1435:

/* Line 1455 of yacc.c  */
#line 7132 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1436:

/* Line 1455 of yacc.c  */
#line 7133 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1437:

/* Line 1455 of yacc.c  */
#line 7134 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 1438:

/* Line 1455 of yacc.c  */
#line 7138 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1439:

/* Line 1455 of yacc.c  */
#line 7139 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); CB_REFERENCE ((yyvsp[(1) - (3)]))->chain = (yyvsp[(3) - (3)]); ;}
    break;

  case 1440:

/* Line 1455 of yacc.c  */
#line 7144 "parser.y"
    {
	if (cb_ref ((yyvsp[(0) - (3)])) != cb_error_node) {
		(yyval) = (yyvsp[(0) - (3)]);
		CB_REFERENCE ((yyvsp[(0) - (3)]))->subs = cb_list_reverse ((yyvsp[(2) - (3)]));
	}
  ;}
    break;

  case 1441:

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

  case 1442:

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

  case 1443:

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

  case 1444:

/* Line 1455 of yacc.c  */
#line 7210 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1445:

/* Line 1455 of yacc.c  */
#line 7212 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (2)]);
	if (CB_LITERAL_P ((yyvsp[(2) - (2)]))) {
		CB_LITERAL ((yyvsp[(2) - (2)]))->all = 1;
	}
  ;}
    break;

  case 1446:

/* Line 1455 of yacc.c  */
#line 7221 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1447:

/* Line 1455 of yacc.c  */
#line 7222 "parser.y"
    { (yyval) = cb_concat_literals ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1448:

/* Line 1455 of yacc.c  */
#line 7226 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1449:

/* Line 1455 of yacc.c  */
#line 7227 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 1450:

/* Line 1455 of yacc.c  */
#line 7228 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1451:

/* Line 1455 of yacc.c  */
#line 7229 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 1452:

/* Line 1455 of yacc.c  */
#line 7230 "parser.y"
    { (yyval) = cb_high; ;}
    break;

  case 1453:

/* Line 1455 of yacc.c  */
#line 7231 "parser.y"
    { (yyval) = cb_low; ;}
    break;

  case 1454:

/* Line 1455 of yacc.c  */
#line 7232 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1455:

/* Line 1455 of yacc.c  */
#line 7241 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1456:

/* Line 1455 of yacc.c  */
#line 7245 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1457:

/* Line 1455 of yacc.c  */
#line 7249 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1458:

/* Line 1455 of yacc.c  */
#line 7253 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1459:

/* Line 1455 of yacc.c  */
#line 7257 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1460:

/* Line 1455 of yacc.c  */
#line 7261 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1461:

/* Line 1455 of yacc.c  */
#line 7265 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1462:

/* Line 1455 of yacc.c  */
#line 7269 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1463:

/* Line 1455 of yacc.c  */
#line 7273 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1464:

/* Line 1455 of yacc.c  */
#line 7277 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), NULL);
  ;}
    break;

  case 1465:

/* Line 1455 of yacc.c  */
#line 7281 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1466:

/* Line 1455 of yacc.c  */
#line 7285 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), NULL);
  ;}
    break;

  case 1467:

/* Line 1455 of yacc.c  */
#line 7291 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1468:

/* Line 1455 of yacc.c  */
#line 7292 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (4)]), NULL); ;}
    break;

  case 1469:

/* Line 1455 of yacc.c  */
#line 7293 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 1470:

/* Line 1455 of yacc.c  */
#line 7297 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1471:

/* Line 1455 of yacc.c  */
#line 7298 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1472:

/* Line 1455 of yacc.c  */
#line 7302 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1473:

/* Line 1455 of yacc.c  */
#line 7303 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1474:

/* Line 1455 of yacc.c  */
#line 7309 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_int0);
  ;}
    break;

  case 1475:

/* Line 1455 of yacc.c  */
#line 7316 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int1);
  ;}
    break;

  case 1476:

/* Line 1455 of yacc.c  */
#line 7323 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int2);
  ;}
    break;

  case 1477:

/* Line 1455 of yacc.c  */
#line 7333 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1478:

/* Line 1455 of yacc.c  */
#line 7340 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1479:

/* Line 1455 of yacc.c  */
#line 7350 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1480:

/* Line 1455 of yacc.c  */
#line 7357 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_ref ((yyvsp[(3) - (3)])));
  ;}
    break;

  case 1481:

/* Line 1455 of yacc.c  */
#line 7370 "parser.y"
    {
	non_const_word = 1;
  ;}
    break;

  case 1482:

/* Line 1455 of yacc.c  */
#line 7380 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1483:

/* Line 1455 of yacc.c  */
#line 7381 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1484:

/* Line 1455 of yacc.c  */
#line 7385 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1485:

/* Line 1455 of yacc.c  */
#line 7386 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1486:

/* Line 1455 of yacc.c  */
#line 7390 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1487:

/* Line 1455 of yacc.c  */
#line 7391 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1488:

/* Line 1455 of yacc.c  */
#line 7395 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1489:

/* Line 1455 of yacc.c  */
#line 7396 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1490:

/* Line 1455 of yacc.c  */
#line 7397 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 1491:

/* Line 1455 of yacc.c  */
#line 7401 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1492:

/* Line 1455 of yacc.c  */
#line 7402 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1493:

/* Line 1455 of yacc.c  */
#line 7406 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1494:

/* Line 1455 of yacc.c  */
#line 7407 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1495:

/* Line 1455 of yacc.c  */
#line 7411 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1496:

/* Line 1455 of yacc.c  */
#line 7412 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1497:

/* Line 1455 of yacc.c  */
#line 7416 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1498:

/* Line 1455 of yacc.c  */
#line 7417 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1510:

/* Line 1455 of yacc.c  */
#line 7430 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1539:

/* Line 1455 of yacc.c  */
#line 7445 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1540:

/* Line 1455 of yacc.c  */
#line 7445 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1551:

/* Line 1455 of yacc.c  */
#line 7450 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1552:

/* Line 1455 of yacc.c  */
#line 7450 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;



/* Line 1455 of yacc.c  */
#line 14920 "parser.c"
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


