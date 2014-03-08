
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
     LIMIT = 478,
     LIMITS = 479,
     LINAGE = 480,
     LINAGE_COUNTER = 481,
     LINE = 482,
     LINES = 483,
     LINKAGE = 484,
     LITERAL = 485,
     LOCALE = 486,
     LOCALE_DT_FUNC = 487,
     LOCAL_STORAGE = 488,
     LOCK = 489,
     LOWER_CASE_FUNC = 490,
     LOWLIGHT = 491,
     LOW_VALUE = 492,
     MANUAL = 493,
     MEMORY = 494,
     MERGE = 495,
     MINUS = 496,
     MNEMONIC_NAME = 497,
     MODE = 498,
     MOVE = 499,
     MULTIPLE = 500,
     MULTIPLY = 501,
     NATIONAL = 502,
     NATIONAL_EDITED = 503,
     NATIVE = 504,
     NE = 505,
     NEGATIVE = 506,
     NEXT = 507,
     NEXT_SENTENCE = 508,
     NO = 509,
     NOT = 510,
     NOT_END = 511,
     NOT_EOP = 512,
     NOT_EXCEPTION = 513,
     NOT_INVALID_KEY = 514,
     NOT_OVERFLOW = 515,
     NOT_SIZE_ERROR = 516,
     NO_ADVANCING = 517,
     NUMBER = 518,
     NUMBERS = 519,
     NUMERIC = 520,
     NUMERIC_EDITED = 521,
     NUMVALC_FUNC = 522,
     OBJECT_COMPUTER = 523,
     OCCURS = 524,
     OF = 525,
     OFF = 526,
     OMITTED = 527,
     ON = 528,
     ONLY = 529,
     OPEN = 530,
     OPTIONAL = 531,
     OR = 532,
     ORDER = 533,
     ORGANIZATION = 534,
     OTHER = 535,
     OUTPUT = 536,
     OVERFLOW = 537,
     OVERLINE = 538,
     PACKED_DECIMAL = 539,
     PADDING = 540,
     PAGE = 541,
     PAGE_FOOTING = 542,
     PAGE_HEADING = 543,
     PARAGRAPH = 544,
     PERFORM = 545,
     PICTURE = 546,
     PLUS = 547,
     POINTER = 548,
     POSITION = 549,
     POSITIVE = 550,
     PRESENT = 551,
     PREVIOUS = 552,
     PRINTER = 553,
     PRINTING = 554,
     PROCEDURE = 555,
     PROCEDURES = 556,
     PROCEED = 557,
     PROGRAM = 558,
     PROGRAM_ID = 559,
     PROGRAM_NAME = 560,
     PROGRAM_POINTER = 561,
     PROMPT = 562,
     QUOTE = 563,
     RANDOM = 564,
     RD = 565,
     READ = 566,
     RECORD = 567,
     RECORDING = 568,
     RECORDS = 569,
     RECURSIVE = 570,
     REDEFINES = 571,
     REEL = 572,
     REFERENCE = 573,
     RELATIVE = 574,
     RELEASE = 575,
     REMAINDER = 576,
     REMOVAL = 577,
     RENAMES = 578,
     REPLACING = 579,
     REPORT = 580,
     REPORTING = 581,
     REPORTS = 582,
     REPORT_FOOTING = 583,
     REPORT_HEADING = 584,
     REPOSITORY = 585,
     REQUIRED = 586,
     RESERVE = 587,
     RETURN = 588,
     RETURNING = 589,
     REVERSE_FUNC = 590,
     REVERSE_VIDEO = 591,
     REWIND = 592,
     REWRITE = 593,
     RIGHT = 594,
     ROLLBACK = 595,
     ROUNDED = 596,
     RUN = 597,
     SAME = 598,
     SCREEN = 599,
     SCREEN_CONTROL = 600,
     SCROLL = 601,
     SD = 602,
     SEARCH = 603,
     SECTION = 604,
     SECURE = 605,
     SEGMENT_LIMIT = 606,
     SELECT = 607,
     SEMI_COLON = 608,
     SENTENCE = 609,
     SEPARATE = 610,
     SEQUENCE = 611,
     SEQUENTIAL = 612,
     SET = 613,
     SHARING = 614,
     SIGN = 615,
     SIGNED = 616,
     SIGNED_INT = 617,
     SIGNED_LONG = 618,
     SIGNED_SHORT = 619,
     SIZE = 620,
     SIZE_ERROR = 621,
     SORT = 622,
     SORT_MERGE = 623,
     SOURCE = 624,
     SOURCE_COMPUTER = 625,
     SPACE = 626,
     SPECIAL_NAMES = 627,
     STANDARD = 628,
     STANDARD_1 = 629,
     STANDARD_2 = 630,
     START = 631,
     STATUS = 632,
     STOP = 633,
     STRING = 634,
     SUBSTITUTE_FUNC = 635,
     SUBSTITUTE_CASE_FUNC = 636,
     SUBTRACT = 637,
     SUM = 638,
     SUPPRESS = 639,
     SYMBOLIC = 640,
     SYNCHRONIZED = 641,
     TALLYING = 642,
     TAPE = 643,
     TERMINATE = 644,
     TEST = 645,
     THAN = 646,
     THEN = 647,
     THRU = 648,
     TIME = 649,
     TIMES = 650,
     TO = 651,
     TOK_FALSE = 652,
     TOK_FILE = 653,
     TOK_INITIAL = 654,
     TOK_NULL = 655,
     TOK_TRUE = 656,
     TOP = 657,
     TRAILING = 658,
     TRANSFORM = 659,
     TRIM_FUNCTION = 660,
     TYPE = 661,
     UNDERLINE = 662,
     UNIT = 663,
     UNLOCK = 664,
     UNSIGNED = 665,
     UNSIGNED_INT = 666,
     UNSIGNED_LONG = 667,
     UNSIGNED_SHORT = 668,
     UNSTRING = 669,
     UNTIL = 670,
     UP = 671,
     UPDATE = 672,
     UPON = 673,
     UPON_ARGUMENT_NUMBER = 674,
     UPON_COMMAND_LINE = 675,
     UPON_ENVIRONMENT_NAME = 676,
     UPON_ENVIRONMENT_VALUE = 677,
     UPPER_CASE_FUNC = 678,
     USAGE = 679,
     USE = 680,
     USING = 681,
     VALUE = 682,
     VARYING = 683,
     WAIT = 684,
     WHEN = 685,
     WHEN_COMPILED_FUNC = 686,
     WHEN_OTHER = 687,
     WITH = 688,
     WORD = 689,
     WORDS = 690,
     WORKING_STORAGE = 691,
     WRITE = 692,
     YYYYDDD = 693,
     YYYYMMDD = 694,
     ZERO = 695,
     UNARY_SIGN = 696
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
#line 842 "parser.c"

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
#define YYLAST   5384

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  455
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  698
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1556
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2291

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   696

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   454,     2,
     450,   449,   443,   441,     2,   442,   447,   444,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   453,     2,
     452,   448,   451,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   446,     2,     2,     2,     2,     2,
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
     435,   436,   437,   438,   439,   440,   445
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
     275,   279,   283,   287,   291,   292,   295,   297,   300,   305,
     307,   309,   310,   316,   318,   320,   322,   324,   326,   328,
     331,   333,   337,   338,   343,   345,   349,   351,   353,   355,
     357,   359,   361,   363,   365,   367,   369,   371,   373,   377,
     381,   383,   386,   388,   391,   396,   398,   401,   403,   407,
     412,   417,   421,   425,   430,   434,   438,   439,   445,   446,
     451,   452,   457,   458,   462,   463,   466,   467,   474,   475,
     478,   480,   482,   484,   486,   488,   490,   492,   494,   496,
     498,   500,   502,   504,   506,   512,   517,   522,   523,   525,
     527,   528,   530,   532,   534,   536,   538,   543,   545,   547,
     549,   556,   565,   566,   569,   572,   574,   575,   578,   580,
     584,   590,   591,   593,   595,   600,   603,   606,   608,   609,
     614,   620,   623,   625,   627,   631,   633,   635,   639,   641,
     643,   646,   651,   656,   661,   668,   673,   677,   681,   684,
     687,   690,   691,   695,   696,   699,   701,   704,   706,   708,
     710,   716,   717,   719,   721,   723,   729,   731,   734,   737,
     738,   741,   746,   747,   757,   758,   759,   765,   766,   770,
     771,   774,   778,   781,   784,   786,   788,   789,   794,   795,
     798,   801,   804,   806,   808,   810,   812,   814,   816,   818,
     820,   822,   824,   830,   831,   833,   835,   840,   847,   857,
     858,   862,   863,   866,   867,   870,   874,   876,   878,   884,
     890,   892,   894,   898,   904,   905,   908,   910,   912,   914,
     920,   925,   929,   934,   938,   942,   946,   947,   948,   954,
     955,   957,   958,   961,   965,   970,   973,   975,   976,   981,
     983,   984,   986,   988,   990,   991,   994,   996,  1000,  1004,
    1011,  1012,  1015,  1017,  1019,  1021,  1023,  1025,  1027,  1029,
    1031,  1033,  1035,  1037,  1039,  1041,  1043,  1045,  1048,  1052,
    1053,  1056,  1059,  1061,  1063,  1067,  1069,  1071,  1073,  1075,
    1077,  1079,  1081,  1083,  1085,  1087,  1089,  1091,  1093,  1095,
    1097,  1099,  1101,  1103,  1105,  1108,  1111,  1113,  1116,  1119,
    1121,  1124,  1127,  1129,  1132,  1135,  1137,  1140,  1143,  1145,
    1147,  1151,  1155,  1163,  1164,  1167,  1168,  1172,  1174,  1175,
    1181,  1183,  1185,  1186,  1190,  1192,  1195,  1197,  1200,  1203,
    1204,  1206,  1208,  1212,  1214,  1215,  1224,  1226,  1229,  1231,
    1235,  1236,  1240,  1243,  1248,  1251,  1252,  1253,  1259,  1260,
    1261,  1267,  1268,  1269,  1275,  1276,  1278,  1280,  1283,  1289,
    1290,  1293,  1296,  1300,  1302,  1304,  1307,  1310,  1313,  1314,
    1316,  1318,  1321,  1330,  1331,  1335,  1336,  1341,  1342,  1347,
    1348,  1352,  1353,  1357,  1359,  1364,  1367,  1369,  1371,  1372,
    1375,  1380,  1381,  1384,  1386,  1388,  1390,  1392,  1394,  1396,
    1398,  1400,  1402,  1404,  1406,  1408,  1410,  1412,  1414,  1416,
    1420,  1422,  1424,  1426,  1428,  1430,  1432,  1434,  1439,  1444,
    1447,  1449,  1451,  1454,  1458,  1460,  1464,  1471,  1474,  1478,
    1481,  1483,  1486,  1489,  1491,  1494,  1495,  1497,  1499,  1504,
    1507,  1508,  1510,  1512,  1513,  1514,  1515,  1522,  1523,  1525,
    1527,  1530,  1532,  1533,  1539,  1540,  1543,  1545,  1547,  1549,
    1551,  1554,  1557,  1559,  1561,  1563,  1565,  1567,  1569,  1571,
    1573,  1575,  1577,  1583,  1589,  1593,  1597,  1599,  1601,  1603,
    1605,  1607,  1609,  1611,  1614,  1617,  1620,  1621,  1623,  1625,
    1627,  1629,  1630,  1632,  1634,  1636,  1638,  1642,  1643,  1644,
    1645,  1655,  1656,  1657,  1661,  1662,  1666,  1668,  1671,  1676,
    1677,  1680,  1683,  1684,  1688,  1692,  1697,  1701,  1702,  1704,
    1705,  1708,  1709,  1710,  1718,  1719,  1722,  1724,  1726,  1728,
    1731,  1733,  1738,  1741,  1743,  1745,  1746,  1748,  1749,  1750,
    1754,  1755,  1758,  1760,  1762,  1764,  1766,  1768,  1770,  1772,
    1774,  1776,  1778,  1780,  1782,  1784,  1786,  1788,  1790,  1792,
    1794,  1796,  1798,  1800,  1802,  1804,  1806,  1808,  1810,  1812,
    1814,  1816,  1818,  1820,  1822,  1824,  1826,  1828,  1830,  1832,
    1834,  1836,  1838,  1840,  1842,  1844,  1846,  1848,  1850,  1852,
    1854,  1856,  1858,  1859,  1864,  1869,  1874,  1878,  1882,  1886,
    1891,  1895,  1900,  1904,  1908,  1912,  1917,  1923,  1927,  1932,
    1936,  1940,  1941,  1945,  1949,  1952,  1955,  1958,  1962,  1966,
    1970,  1971,  1974,  1976,  1979,  1981,  1983,  1985,  1987,  1989,
    1991,  1993,  1997,  2001,  2005,  2009,  2011,  2013,  2015,  2017,
    2019,  2021,  2022,  2024,  2025,  2030,  2035,  2041,  2048,  2049,
    2052,  2053,  2055,  2056,  2060,  2064,  2070,  2071,  2074,  2077,
    2078,  2084,  2085,  2088,  2089,  2098,  2099,  2100,  2104,  2106,
    2109,  2112,  2116,  2117,  2120,  2123,  2126,  2127,  2130,  2133,
    2134,  2135,  2139,  2140,  2141,  2145,  2146,  2148,  2149,  2153,
    2154,  2157,  2158,  2162,  2163,  2167,  2168,  2170,  2174,  2178,
    2181,  2183,  2185,  2186,  2191,  2196,  2197,  2199,  2201,  2203,
    2205,  2207,  2208,  2215,  2216,  2218,  2219,  2224,  2225,  2230,
    2234,  2238,  2242,  2246,  2251,  2258,  2265,  2272,  2279,  2280,
    2283,  2286,  2288,  2291,  2293,  2295,  2298,  2301,  2303,  2305,
    2307,  2309,  2311,  2315,  2319,  2323,  2327,  2329,  2331,  2332,
    2334,  2335,  2340,  2345,  2352,  2359,  2368,  2377,  2378,  2380,
    2381,  2386,  2387,  2393,  2395,  2399,  2401,  2403,  2405,  2408,
    2410,  2413,  2414,  2418,  2419,  2420,  2424,  2427,  2431,  2433,
    2437,  2440,  2442,  2444,  2446,  2447,  2450,  2451,  2453,  2454,
    2458,  2459,  2461,  2463,  2466,  2468,  2470,  2471,  2475,  2476,
    2480,  2481,  2487,  2488,  2492,  2493,  2496,  2497,  2498,  2507,
    2511,  2512,  2513,  2517,  2518,  2520,  2521,  2529,  2530,  2533,
    2534,  2538,  2542,  2543,  2546,  2548,  2551,  2556,  2558,  2560,
    2562,  2564,  2566,  2568,  2570,  2571,  2573,  2574,  2578,  2579,
    2584,  2586,  2588,  2590,  2592,  2595,  2597,  2599,  2601,  2602,
    2606,  2608,  2611,  2614,  2617,  2619,  2621,  2623,  2626,  2629,
    2631,  2634,  2639,  2642,  2643,  2645,  2647,  2649,  2651,  2656,
    2662,  2663,  2668,  2669,  2671,  2672,  2676,  2677,  2681,  2685,
    2690,  2691,  2696,  2701,  2708,  2709,  2711,  2712,  2716,  2717,
    2723,  2725,  2727,  2729,  2731,  2732,  2736,  2737,  2741,  2744,
    2745,  2749,  2752,  2753,  2758,  2761,  2762,  2764,  2766,  2770,
    2771,  2773,  2776,  2780,  2784,  2785,  2789,  2791,  2795,  2803,
    2804,  2815,  2816,  2819,  2820,  2823,  2826,  2830,  2834,  2837,
    2838,  2842,  2843,  2845,  2847,  2848,  2850,  2851,  2856,  2857,
    2865,  2866,  2868,  2869,  2877,  2878,  2881,  2885,  2886,  2888,
    2890,  2891,  2896,  2901,  2902,  2910,  2911,  2914,  2915,  2916,
    2921,  2923,  2926,  2927,  2932,  2933,  2935,  2936,  2940,  2942,
    2944,  2946,  2948,  2950,  2955,  2960,  2964,  2969,  2971,  2973,
    2975,  2978,  2982,  2984,  2987,  2991,  2995,  2996,  3000,  3001,
    3009,  3010,  3016,  3017,  3020,  3021,  3024,  3025,  3029,  3030,
    3033,  3038,  3039,  3042,  3047,  3048,  3049,  3057,  3058,  3063,
    3066,  3069,  3072,  3075,  3078,  3079,  3081,  3082,  3087,  3090,
    3091,  3094,  3097,  3098,  3107,  3109,  3112,  3114,  3118,  3122,
    3123,  3127,  3128,  3130,  3131,  3136,  3141,  3148,  3155,  3156,
    3158,  3161,  3162,  3164,  3165,  3169,  3170,  3178,  3179,  3184,
    3185,  3187,  3189,  3190,  3200,  3201,  3205,  3207,  3211,  3214,
    3217,  3220,  3224,  3225,  3229,  3230,  3234,  3235,  3239,  3240,
    3242,  3244,  3246,  3248,  3257,  3258,  3260,  3262,  3264,  3266,
    3268,  3270,  3271,  3273,  3274,  3276,  3278,  3280,  3282,  3284,
    3286,  3288,  3289,  3291,  3297,  3299,  3302,  3308,  3309,  3318,
    3319,  3322,  3323,  3328,  3332,  3336,  3338,  3340,  3341,  3343,
    3345,  3346,  3348,  3351,  3354,  3355,  3356,  3360,  3361,  3362,
    3366,  3369,  3370,  3371,  3375,  3376,  3377,  3381,  3384,  3385,
    3386,  3390,  3391,  3392,  3396,  3398,  3400,  3403,  3404,  3408,
    3409,  3413,  3415,  3417,  3420,  3421,  3425,  3426,  3430,  3431,
    3433,  3435,  3437,  3440,  3441,  3445,  3446,  3450,  3451,  3455,
    3457,  3459,  3460,  3463,  3466,  3469,  3472,  3475,  3478,  3481,
    3484,  3487,  3490,  3493,  3496,  3499,  3502,  3503,  3506,  3509,
    3512,  3515,  3518,  3521,  3524,  3527,  3530,  3533,  3536,  3539,
    3542,  3545,  3548,  3551,  3554,  3557,  3560,  3563,  3566,  3569,
    3572,  3575,  3578,  3580,  3583,  3585,  3587,  3590,  3592,  3595,
    3597,  3603,  3608,  3610,  3616,  3621,  3623,  3627,  3628,  3630,
    3632,  3634,  3638,  3642,  3646,  3650,  3653,  3656,  3660,  3664,
    3666,  3670,  3672,  3675,  3678,  3680,  3682,  3684,  3687,  3689,
    3691,  3694,  3696,  3697,  3700,  3702,  3704,  3706,  3710,  3712,
    3714,  3717,  3719,  3720,  3722,  3724,  3726,  3728,  3730,  3733,
    3735,  3739,  3741,  3744,  3746,  3750,  3754,  3758,  3763,  3767,
    3769,  3771,  3773,  3775,  3779,  3783,  3787,  3789,  3791,  3793,
    3795,  3797,  3799,  3801,  3803,  3805,  3807,  3809,  3811,  3813,
    3815,  3817,  3819,  3821,  3823,  3825,  3827,  3829,  3832,  3835,
    3839,  3841,  3845,  3849,  3854,  3860,  3862,  3864,  3867,  3869,
    3873,  3875,  3877,  3879,  3881,  3883,  3885,  3887,  3890,  3893,
    3899,  3905,  3911,  3917,  3923,  3929,  3935,  3940,  3946,  3949,
    3950,  3955,  3961,  3962,  3966,  3967,  3969,  3971,  3975,  3979,
    3981,  3985,  3987,  3991,  3992,  3993,  3995,  3996,  3998,  3999,
    4001,  4002,  4004,  4006,  4007,  4009,  4010,  4012,  4013,  4015,
    4016,  4019,  4021,  4023,  4026,  4029,  4032,  4034,  4037,  4039,
    4040,  4042,  4043,  4045,  4046,  4048,  4049,  4051,  4052,  4054,
    4055,  4057,  4058,  4060,  4061,  4063,  4064,  4066,  4067,  4069,
    4070,  4072,  4073,  4075,  4076,  4078,  4079,  4081,  4082,  4084,
    4085,  4087,  4088,  4090,  4091,  4093,  4095,  4096,  4098,  4099,
    4101,  4103,  4104,  4106,  4107,  4109,  4110,  4112,  4113,  4115,
    4116,  4118,  4119,  4121,  4124,  4125,  4127,  4128,  4130,  4131,
    4133,  4134,  4136,  4137,  4139,  4140,  4142,  4143,  4145,  4148,
    4149,  4151,  4152,  4154,  4155,  4157,  4158,  4160,  4161,  4163,
    4164,  4166,  4167,  4169,  4170,  4172,  4173
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     456,     0,    -1,    -1,   457,   458,    -1,   459,    -1,   458,
     459,    -1,   460,    -1,   466,    -1,    -1,    -1,   473,   481,
     461,   583,   462,   717,   469,   470,    -1,    -1,    -1,   473,
     481,   464,   583,   465,   717,   469,   471,    -1,    -1,    -1,
     475,   481,   467,   583,   468,   717,   472,    -1,    -1,   463,
      -1,   469,   463,    -1,    -1,   136,   476,   447,    -1,   136,
     476,   447,    -1,   132,   476,   447,    -1,    -1,   304,   447,
     476,   477,   474,   478,   447,    -1,   179,   447,   476,   477,
     447,    -1,   305,    -1,   230,    -1,    -1,    27,   230,    -1,
      -1,  1127,   479,  1138,    -1,    72,    -1,    72,   480,    -1,
     480,    -1,   399,    -1,   315,    -1,    -1,   147,   117,   447,
     482,   536,    -1,    -1,    82,   349,   447,   483,    -1,    -1,
     483,   484,    -1,   485,    -1,   489,    -1,   502,    -1,   497,
      -1,   370,   447,   486,    -1,    -1,   488,   447,    -1,   488,
     487,   447,    -1,   487,   447,    -1,  1152,   104,   243,    -1,
     434,    -1,   268,   447,   490,    -1,    -1,   488,   447,    -1,
     488,   491,   447,    -1,   491,   447,    -1,   492,    -1,   491,
     492,    -1,   493,    -1,   495,    -1,   496,    -1,   239,   365,
    1127,  1087,   494,    -1,    56,    -1,   435,    -1,  1138,  1110,
    1127,  1066,    -1,   351,  1127,  1087,    -1,   330,   447,   498,
      -1,    -1,   499,   447,    -1,   500,    -1,   499,   500,    -1,
     178,   501,   207,    -1,   178,     9,   207,    -1,   230,    -1,
     501,   230,    -1,   372,   447,   503,    -1,    -1,   504,   447,
      -1,   505,    -1,   504,   505,    -1,   506,    -1,   513,    -1,
     522,    -1,   529,    -1,   526,    -1,   530,    -1,   531,    -1,
     532,    -1,   533,    -1,   534,    -1,   535,    -1,   434,  1127,
      94,    -1,    -1,   434,  1127,  1069,   507,   509,    -1,    -1,
     434,  1127,   508,   510,    -1,    25,  1127,  1069,    -1,    26,
    1127,  1069,    -1,   148,  1127,  1069,    -1,   149,  1127,  1069,
      -1,    -1,   509,   511,    -1,   511,    -1,   510,   511,    -1,
     512,  1145,  1127,  1069,    -1,   273,    -1,   271,    -1,    -1,
      11,  1069,   514,  1127,   515,    -1,   249,    -1,   374,    -1,
     375,    -1,   121,    -1,   516,    -1,   517,    -1,   516,   517,
      -1,   520,    -1,   520,   393,   520,    -1,    -1,   520,    17,
     518,   519,    -1,   521,    -1,   519,    17,   521,    -1,   230,
      -1,   371,    -1,   440,    -1,   308,    -1,   191,    -1,   237,
      -1,   230,    -1,   371,    -1,   440,    -1,   308,    -1,   191,
      -1,   237,    -1,   385,  1120,   523,    -1,   524,  1128,   525,
      -1,  1069,    -1,   524,  1069,    -1,  1087,    -1,   525,  1087,
      -1,    57,  1069,  1127,   527,    -1,   528,    -1,   527,   528,
      -1,  1090,    -1,  1090,   393,  1090,    -1,   231,  1069,  1127,
    1066,    -1,    95,  1142,  1127,   230,    -1,   105,  1127,    67,
      -1,    97,  1127,  1066,    -1,    94,   377,  1127,  1066,    -1,
     345,  1127,  1066,    -1,   159,  1127,  1066,    -1,    -1,   204,
     349,   447,   539,   572,    -1,    -1,   166,   447,   537,   540,
      -1,    -1,   212,   447,   538,   573,    -1,    -1,   166,   447,
     540,    -1,    -1,   540,   541,    -1,    -1,   352,  1104,  1069,
     542,   543,   447,    -1,    -1,   543,   544,    -1,   545,    -1,
     549,    -1,   551,    -1,   556,    -1,   557,    -1,   559,    -1,
     563,    -1,   565,    -1,   566,    -1,   567,    -1,   568,    -1,
     569,    -1,   570,    -1,     1,    -1,    29,  1150,   547,   546,
     548,    -1,    29,  1150,   547,   114,    -1,    29,  1150,   547,
     298,    -1,    -1,   114,    -1,   298,    -1,    -1,   164,    -1,
     120,    -1,   230,    -1,   115,    -1,  1084,    -1,     4,  1132,
    1127,   550,    -1,   357,    -1,   120,    -1,   309,    -1,    19,
     312,  1129,  1127,  1066,  1100,    -1,    19,   312,  1129,  1127,
    1066,   555,   552,  1100,    -1,    -1,   553,   554,    -1,   552,
     554,    -1,  1066,    -1,    -1,   369,  1127,    -1,   448,    -1,
    1110,  1127,   434,    -1,   558,   377,  1127,  1066,  1067,    -1,
      -1,   398,    -1,   367,    -1,   234,  1132,  1127,   560,    -1,
     238,   561,    -1,    32,   561,    -1,   161,    -1,    -1,   433,
     234,   273,   562,    -1,   433,   234,   273,   245,   562,    -1,
     433,   340,    -1,   312,    -1,   314,    -1,   279,  1127,   564,
      -1,   564,    -1,   198,    -1,   312,  1117,   357,    -1,   357,
      -1,   319,    -1,   227,   357,    -1,   285,  1119,  1127,  1068,
      -1,   312,   110,  1127,   374,    -1,   312,  1129,  1127,  1066,
      -1,   312,  1129,  1127,  1066,   555,   552,    -1,   319,  1129,
    1127,  1066,    -1,   332,  1087,  1114,    -1,   359,  1152,   571,
      -1,     9,  1137,    -1,   254,  1137,    -1,   311,   274,    -1,
      -1,   212,   447,   573,    -1,    -1,   574,   447,    -1,   575,
      -1,   574,   575,    -1,   576,    -1,   578,    -1,   582,    -1,
     343,   577,  1114,  1124,  1057,    -1,    -1,   312,    -1,   367,
      -1,   368,    -1,   245,  1123,  1146,  1121,   579,    -1,   580,
      -1,   579,   580,    -1,  1058,   581,    -1,    -1,   294,  1087,
      -1,    22,    71,  1135,  1065,    -1,    -1,    99,   117,   447,
     584,   615,   660,   662,   664,   705,    -1,    -1,    -1,   398,
     349,   447,   585,   587,    -1,    -1,   590,   586,   589,    -1,
      -1,   587,   588,    -1,   590,   591,   617,    -1,   591,   617,
      -1,   589,   588,    -1,   165,    -1,   347,    -1,    -1,  1058,
     592,   593,   447,    -1,    -1,   593,   594,    -1,  1127,   164,
      -1,  1127,   184,    -1,   595,    -1,   597,    -1,   601,    -1,
     603,    -1,   605,    -1,   606,    -1,   612,    -1,   613,    -1,
     614,    -1,     1,    -1,    47,  1121,  1087,   600,   596,    -1,
      -1,   314,    -1,    56,    -1,   312,  1121,  1087,  1120,    -1,
     312,  1121,  1087,   396,  1087,  1120,    -1,   312,  1127,   428,
    1126,  1144,   599,   600,  1120,   598,    -1,    -1,   111,  1135,
    1066,    -1,    -1,  1125,  1087,    -1,    -1,   396,  1087,    -1,
     215,  1108,   602,    -1,   373,    -1,   272,    -1,   427,   270,
     434,  1127,   604,    -1,   427,   270,   167,  1127,   604,    -1,
     230,    -1,  1084,    -1,    99,  1108,  1065,    -1,   225,  1127,
    1068,  1131,   607,    -1,    -1,   607,   608,    -1,   609,    -1,
     610,    -1,   611,    -1,  1152,   171,  1116,  1068,  1131,    -1,
    1116,   402,  1068,  1131,    -1,  1116,    48,  1068,    -1,   313,
    1132,  1127,   434,    -1,    61,  1127,   434,    -1,   325,  1127,
     704,    -1,   327,  1113,   704,    -1,    -1,    -1,   436,   349,
     447,   616,   617,    -1,    -1,   618,    -1,    -1,   619,   620,
      -1,  1098,   621,   447,    -1,   620,  1098,   621,   447,    -1,
     620,   447,    -1,   628,    -1,    -1,   623,   624,   622,   629,
      -1,   434,    -1,    -1,   168,    -1,   434,    -1,   434,    -1,
      -1,  1127,   184,    -1,  1088,    -1,   221,  1134,  1083,    -1,
      50,  1134,  1083,    -1,   623,   625,    83,   626,  1115,   627,
      -1,    -1,   629,   630,    -1,   631,    -1,   632,    -1,   634,
      -1,   635,    -1,   636,    -1,   638,    -1,   639,    -1,   648,
      -1,   649,    -1,   651,    -1,   652,    -1,   653,    -1,   658,
      -1,   659,    -1,     1,    -1,   316,  1083,    -1,  1127,   164,
     633,    -1,    -1,    27,   230,    -1,  1127,   184,    -1,   291,
      -1,   637,    -1,   424,  1127,   637,    -1,    37,    -1,    73,
      -1,    75,    -1,    76,    -1,    77,    -1,    78,    -1,    79,
      -1,    80,    -1,   115,    -1,   197,    -1,   284,    -1,   293,
      -1,   306,    -1,   364,    -1,   362,    -1,   363,    -1,   413,
      -1,   411,    -1,   412,    -1,    39,   361,    -1,    39,   410,
      -1,    39,    -1,    42,   361,    -1,    42,   410,    -1,    42,
      -1,    41,   361,    -1,    41,   410,    -1,    41,    -1,    40,
     361,    -1,    40,   410,    -1,    40,    -1,    38,   361,    -1,
      38,   410,    -1,    38,    -1,   247,    -1,  1143,   219,  1106,
      -1,  1143,   403,  1106,    -1,   269,  1087,   640,  1149,   641,
     642,   645,    -1,    -1,   396,  1087,    -1,    -1,   111,  1135,
    1066,    -1,   643,    -1,    -1,   643,   644,  1129,  1127,  1065,
      -1,    28,    -1,   112,    -1,    -1,   198,  1118,   646,    -1,
     647,    -1,   646,   647,    -1,   434,    -1,   213,  1140,    -1,
     386,   650,    -1,    -1,   220,    -1,   339,    -1,    43,  1151,
     440,    -1,    34,    -1,    -1,   427,  1128,   655,   654,  1151,
    1141,  1150,   657,    -1,   656,    -1,   655,   656,    -1,  1088,
      -1,  1088,   393,  1088,    -1,    -1,   397,  1127,  1088,    -1,
     323,  1084,    -1,   323,  1084,   393,  1084,    -1,    21,   221,
      -1,    -1,    -1,   233,   349,   447,   661,   617,    -1,    -1,
      -1,   229,   349,   447,   663,   617,    -1,    -1,    -1,   325,
     349,   447,   665,   666,    -1,    -1,   667,    -1,   668,    -1,
     667,   668,    -1,   310,   704,   669,   447,   683,    -1,    -1,
     669,   670,    -1,  1127,   184,    -1,    60,  1127,  1079,    -1,
     671,    -1,   675,    -1,    87,   672,    -1,    88,   672,    -1,
     673,   674,    -1,    -1,   169,    -1,  1082,    -1,   674,  1082,
      -1,   286,  1128,   681,   676,   677,   678,   679,   680,    -1,
      -1,   189,  1127,  1087,    -1,    -1,   170,   113,  1127,  1087,
      -1,    -1,   216,    90,  1127,  1087,    -1,    -1,   217,  1127,
    1087,    -1,    -1,   171,  1127,  1087,    -1,  1087,    -1,  1087,
     682,  1087,    66,    -1,  1087,   682,    -1,   227,    -1,   228,
      -1,    -1,   683,   684,    -1,   623,   624,   685,   447,    -1,
      -1,   685,   686,    -1,   687,    -1,   689,    -1,   696,    -1,
     635,    -1,   636,    -1,   638,    -1,   648,    -1,   690,    -1,
     651,    -1,   701,    -1,   691,    -1,   653,    -1,   694,    -1,
     702,    -1,   639,    -1,   695,    -1,   406,  1127,   688,    -1,
     329,    -1,   288,    -1,    90,    -1,   113,    -1,    89,    -1,
     287,    -1,   328,    -1,   252,   188,  1127,  1087,    -1,    65,
    1133,  1127,  1087,    -1,    65,   264,    -1,    66,    -1,   692,
      -1,   691,   692,    -1,   383,  1134,   693,    -1,  1066,    -1,
     296,   430,  1038,    -1,   428,  1082,   176,  1073,    49,  1073,
      -1,   697,   698,    -1,   227,   700,  1128,    -1,   228,  1113,
      -1,   699,    -1,   698,   699,    -1,   292,  1087,    -1,  1087,
      -1,   252,   286,    -1,    -1,   263,    -1,   264,    -1,   369,
    1127,  1082,  1105,    -1,   188,   703,    -1,    -1,   199,    -1,
     434,    -1,    -1,    -1,    -1,   344,   349,   447,   706,   707,
     708,    -1,    -1,   709,    -1,   710,    -1,   709,   710,    -1,
     628,    -1,    -1,   623,   624,   711,   712,   447,    -1,    -1,
     712,   713,    -1,    44,    -1,    45,    -1,    36,    -1,    46,
      -1,   155,   150,    -1,   155,   152,    -1,   190,    -1,   236,
      -1,   336,    -1,   407,    -1,   283,    -1,    31,    -1,   350,
      -1,   331,    -1,   177,    -1,   307,    -1,   227,  1133,  1127,
     714,  1081,    -1,    65,  1133,  1127,   715,  1081,    -1,   173,
    1127,  1081,    -1,    33,  1127,  1081,    -1,   636,    -1,   651,
      -1,   648,    -1,   638,    -1,   653,    -1,   635,    -1,   716,
      -1,   426,  1082,    -1,   176,  1080,    -1,   396,  1082,    -1,
      -1,   292,    -1,   441,    -1,   241,    -1,   442,    -1,    -1,
     292,    -1,   441,    -1,   241,    -1,   442,    -1,   269,  1087,
    1149,    -1,    -1,    -1,    -1,   300,   117,   720,   728,   447,
     718,   729,   719,   731,    -1,    -1,    -1,   426,   721,   723,
      -1,    -1,    54,   722,   723,    -1,   724,    -1,   723,   724,
      -1,   725,   726,   727,   434,    -1,    -1,  1118,   318,    -1,
    1118,   427,    -1,    -1,   365,  1127,    31,    -1,   365,  1127,
     107,    -1,   410,   365,  1127,  1087,    -1,   365,  1127,  1087,
      -1,    -1,   276,    -1,    -1,   334,   434,    -1,    -1,    -1,
     106,   447,   730,   731,   123,   106,   447,    -1,    -1,   731,
     732,    -1,   733,    -1,   734,    -1,   735,    -1,   741,   447,
      -1,     1,    -1,   736,   349,   737,   447,    -1,   434,   447,
      -1,   736,    -1,   434,    -1,    -1,   230,    -1,    -1,    -1,
     739,   740,   741,    -1,    -1,   741,   742,    -1,   743,    -1,
     753,    -1,   758,    -1,   762,    -1,   765,    -1,   778,    -1,
     781,    -1,   791,    -1,   786,    -1,   792,    -1,   793,    -1,
     796,    -1,   798,    -1,   805,    -1,   809,    -1,   811,    -1,
     826,    -1,   829,    -1,   831,    -1,   833,    -1,   836,    -1,
     838,    -1,   844,    -1,   853,    -1,   855,    -1,   872,    -1,
     874,    -1,   877,    -1,   881,    -1,   887,    -1,   897,    -1,
     904,    -1,   906,    -1,   909,    -1,   913,    -1,   914,    -1,
     925,    -1,   936,    -1,   946,    -1,   952,    -1,   955,    -1,
     961,    -1,   965,    -1,   967,    -1,   969,    -1,   971,    -1,
     974,    -1,   985,    -1,   998,    -1,   253,    -1,    -1,     3,
     744,   745,   752,    -1,  1082,   746,   749,  1005,    -1,  1082,
     176,   157,   214,    -1,  1082,   176,   228,    -1,  1082,   176,
      66,    -1,  1082,   176,   100,    -1,  1082,   176,   100,   439,
      -1,  1082,   176,   101,    -1,  1082,   176,   101,   438,    -1,
    1082,   176,   102,    -1,  1082,   176,   394,    -1,  1082,   176,
      68,    -1,  1082,   176,   149,  1005,    -1,  1082,   176,   147,
    1077,  1005,    -1,  1082,   176,    25,    -1,  1082,   176,    26,
    1005,    -1,  1082,   176,  1060,    -1,  1082,   176,   434,    -1,
      -1,  1116,   747,   748,    -1,  1116,   748,   747,    -1,  1116,
     747,    -1,  1116,   748,    -1,    30,  1077,    -1,   227,  1133,
    1079,    -1,    65,  1133,  1079,    -1,   294,  1133,  1079,    -1,
      -1,   433,   750,    -1,   751,    -1,   750,   751,    -1,    36,
      -1,    46,    -1,   190,    -1,   236,    -1,   336,    -1,   407,
      -1,   283,    -1,   173,  1127,  1081,    -1,    33,  1127,  1081,
      -1,   346,   416,  1037,    -1,   346,   118,  1037,    -1,    31,
      -1,   177,    -1,   331,    -1,   350,    -1,   417,    -1,   307,
      -1,    -1,   124,    -1,    -1,     5,   754,   755,   757,    -1,
    1072,   396,  1053,  1011,    -1,  1072,   756,   183,  1053,  1011,
      -1,    92,  1082,   396,  1082,  1105,  1011,    -1,    -1,   396,
    1073,    -1,    -1,   125,    -1,    -1,    10,   759,   760,    -1,
     434,  1101,   761,    -1,  1039,    56,  1101,   334,  1071,    -1,
      -1,   334,  1071,    -1,    18,   763,    -1,    -1,   763,  1062,
     396,   764,  1062,    -1,    -1,   302,   396,    -1,    -1,    51,
     766,  1080,   767,   772,   773,   775,   777,    -1,    -1,    -1,
     426,   768,   769,    -1,   770,    -1,   769,   770,    -1,   771,
     272,    -1,   771,   726,  1073,    -1,    -1,  1118,   318,    -1,
    1118,    85,    -1,  1118,   427,    -1,    -1,   334,  1082,    -1,
     183,  1082,    -1,    -1,    -1,   992,   774,   738,    -1,    -1,
      -1,   993,   776,   738,    -1,    -1,   126,    -1,    -1,    52,
     779,   780,    -1,    -1,   780,  1079,    -1,    -1,    59,   782,
     783,    -1,    -1,   783,  1058,   784,    -1,    -1,   785,    -1,
     785,  1124,   322,    -1,  1152,   254,   337,    -1,  1152,   234,
      -1,   317,    -1,   408,    -1,    -1,    74,   787,   788,   789,
      -1,  1053,   790,  1039,  1011,    -1,    -1,   127,    -1,   448,
      -1,   153,    -1,    70,    -1,    86,    -1,    -1,   108,   794,
    1058,  1139,  1031,   795,    -1,    -1,   128,    -1,    -1,   108,
     797,   398,  1057,    -1,    -1,   115,   799,   800,   804,    -1,
    1079,   421,  1006,    -1,  1079,   422,  1006,    -1,  1079,   419,
    1006,    -1,  1079,   420,  1006,    -1,  1072,   746,   801,  1006,
      -1,  1072,   746,   418,  1060,   801,  1006,    -1,  1072,   746,
     418,   434,   801,  1006,    -1,  1072,   746,   418,   298,   801,
    1006,    -1,  1072,   746,   418,    94,   801,  1006,    -1,    -1,
    1152,   262,    -1,   433,   802,    -1,   803,    -1,   802,   803,
      -1,    36,    -1,    46,    -1,   155,   150,    -1,   155,   152,
      -1,   190,    -1,   236,    -1,   336,    -1,   407,    -1,   283,
      -1,   173,  1127,  1081,    -1,    33,  1127,  1081,    -1,   346,
     416,  1037,    -1,   346,   118,  1037,    -1,    44,    -1,    45,
      -1,    -1,   129,    -1,    -1,   116,   806,   807,   808,    -1,
    1073,   206,  1053,  1011,    -1,  1073,   206,  1073,   183,  1053,
    1011,    -1,  1073,    49,  1073,   183,  1053,  1011,    -1,  1073,
     206,  1073,   183,  1054,   321,  1054,  1011,    -1,  1073,    49,
    1073,   183,  1054,   321,  1054,  1011,    -1,    -1,   130,    -1,
      -1,   146,   810,   230,   767,    -1,    -1,   158,   812,   813,
     815,   825,    -1,   814,    -1,   813,  1112,   814,    -1,  1039,
      -1,   401,    -1,   397,    -1,   816,   819,    -1,   817,    -1,
     816,   817,    -1,    -1,   821,   818,   738,    -1,    -1,    -1,
     432,   820,   738,    -1,   430,   822,    -1,   821,   430,   822,
      -1,   823,    -1,   822,  1112,   823,    -1,  1040,   824,    -1,
      21,    -1,   401,    -1,   397,    -1,    -1,   393,  1039,    -1,
      -1,   131,    -1,    -1,   162,   827,   828,    -1,    -1,   303,
      -1,   290,    -1,   290,    98,    -1,   349,    -1,   289,    -1,
      -1,   175,   830,  1070,    -1,    -1,   182,   832,  1082,    -1,
      -1,   185,  1150,   834,  1061,   835,    -1,    -1,   111,  1135,
    1082,    -1,    -1,   186,   837,    -1,    -1,    -1,   193,   839,
    1038,  1148,   840,   738,   841,   843,    -1,   193,     1,   133,
      -1,    -1,    -1,   122,   842,   738,    -1,    -1,   133,    -1,
      -1,   200,   845,  1070,   846,   847,   848,   852,    -1,    -1,
    1152,   168,    -1,    -1,     9,  1150,   427,    -1,   851,  1150,
     427,    -1,    -1,   324,   849,    -1,   850,    -1,   849,   850,
      -1,   851,  1122,    49,  1073,    -1,    12,    -1,    15,    -1,
     265,    -1,    16,    -1,   266,    -1,   247,    -1,   248,    -1,
      -1,   107,    -1,    -1,   202,   854,   674,    -1,    -1,   205,
     856,   857,   858,    -1,  1082,    -1,  1088,    -1,  1091,    -1,
     859,    -1,   858,   859,    -1,   860,    -1,   864,    -1,   869,
      -1,    -1,   387,   861,   862,    -1,   863,    -1,   862,   863,
      -1,  1077,   172,    -1,    56,   870,    -1,     9,    -1,   219,
      -1,   403,    -1,  1077,   870,    -1,   324,   865,    -1,   866,
      -1,   865,   866,    -1,    56,    49,  1077,   870,    -1,   867,
     868,    -1,    -1,     9,    -1,   219,    -1,   170,    -1,   403,
      -1,  1077,    49,  1078,   870,    -1,    91,  1077,   396,  1078,
     870,    -1,    -1,   870,  1002,   871,  1073,    -1,    -1,   399,
      -1,    -1,   240,   873,   938,    -1,    -1,   244,   875,   876,
      -1,  1073,   396,  1070,    -1,    92,  1073,   396,  1070,    -1,
      -1,   246,   878,   879,   880,    -1,  1073,    49,  1053,  1011,
      -1,  1073,    49,  1073,   183,  1053,  1011,    -1,    -1,   134,
      -1,    -1,   275,   882,   883,    -1,    -1,   883,   884,   885,
    1057,   886,    -1,   203,    -1,   281,    -1,   211,    -1,   163,
      -1,    -1,   359,  1152,   571,    -1,    -1,  1152,   254,   337,
      -1,  1152,   234,    -1,    -1,   290,   888,   889,    -1,   892,
     893,    -1,    -1,   893,   890,   738,   891,    -1,   893,   135,
      -1,    -1,   135,    -1,  1062,    -1,  1062,   393,  1062,    -1,
      -1,   174,    -1,  1080,   395,    -1,   894,   415,  1038,    -1,
     894,   428,   895,    -1,    -1,  1152,   390,  1002,    -1,   896,
      -1,   895,     8,   896,    -1,  1082,   176,  1073,    49,  1073,
     415,  1038,    -1,    -1,   311,   898,  1058,  1102,  1139,   899,
     900,   901,   902,   903,    -1,    -1,   206,  1082,    -1,    -1,
     195,   234,    -1,  1152,   234,    -1,  1152,   254,   234,    -1,
    1152,   194,   234,    -1,  1152,   429,    -1,    -1,   214,  1127,
     674,    -1,    -1,  1021,    -1,  1032,    -1,    -1,   137,    -1,
      -1,   320,   905,  1055,  1000,    -1,    -1,   333,   907,  1058,
    1139,   899,  1021,   908,    -1,    -1,   138,    -1,    -1,   338,
     910,  1055,  1000,   911,  1031,   912,    -1,    -1,  1152,   234,
      -1,  1152,   254,   234,    -1,    -1,   139,    -1,   340,    -1,
      -1,   348,   915,   916,   924,    -1,  1056,   918,   919,   921,
      -1,    -1,     9,  1056,   919,   430,  1039,   917,   738,    -1,
      -1,   428,  1082,    -1,    -1,    -1,  1116,   123,   920,   738,
      -1,   922,    -1,   922,   921,    -1,    -1,   430,  1038,   923,
     738,    -1,    -1,   140,    -1,    -1,   358,   926,   927,    -1,
     928,    -1,   929,    -1,   930,    -1,   932,    -1,   934,    -1,
     147,  1077,   396,  1077,    -1,  1070,   396,   146,  1076,    -1,
    1070,   396,  1073,    -1,  1070,   931,    49,  1073,    -1,   416,
      -1,   118,    -1,   933,    -1,   932,   933,    -1,  1059,   396,
     512,    -1,   935,    -1,   934,   935,    -1,  1070,   396,   401,
      -1,  1070,   396,   397,    -1,    -1,   367,   937,   938,    -1,
      -1,  1084,   940,   942,   943,   939,   944,   945,    -1,    -1,
     940,  1135,   644,  1129,   941,    -1,    -1,   941,  1084,    -1,
      -1,  1109,  1136,    -1,    -1,  1110,  1127,  1066,    -1,    -1,
     426,  1057,    -1,   203,   300,  1127,   892,    -1,    -1,   183,
    1057,    -1,   281,   300,  1127,   892,    -1,    -1,    -1,   376,
     947,  1058,   948,   949,  1031,   951,    -1,    -1,   214,  1127,
     950,   674,    -1,  1103,  1044,    -1,  1103,  1045,    -1,  1103,
    1046,    -1,  1103,  1047,    -1,  1103,  1048,    -1,    -1,   141,
      -1,    -1,   378,   342,   953,   954,    -1,   378,   230,    -1,
      -1,   334,  1073,    -1,   183,  1073,    -1,    -1,   379,   956,
     957,   206,  1082,   959,  1016,   960,    -1,   958,    -1,   957,
     958,    -1,  1073,    -1,   109,  1118,   365,    -1,   109,  1118,
    1073,    -1,    -1,  1152,   293,  1082,    -1,    -1,   142,    -1,
      -1,   382,   962,   963,   964,    -1,  1072,   176,  1053,  1011,
      -1,  1072,   176,  1073,   183,  1053,  1011,    -1,    92,  1082,
     176,  1082,  1105,  1011,    -1,    -1,   143,    -1,   384,   966,
      -1,    -1,   299,    -1,    -1,   389,   968,   674,    -1,    -1,
     404,   970,  1082,   176,  1077,   396,  1078,    -1,    -1,   409,
     972,  1058,   973,    -1,    -1,   312,    -1,   314,    -1,    -1,
     414,   975,  1082,   976,   979,   959,   983,  1016,   984,    -1,
      -1,   109,  1118,   977,    -1,   978,    -1,   977,   277,   978,
      -1,  1099,  1077,    -1,   206,   980,    -1,   979,   980,    -1,
    1082,   981,   982,    -1,    -1,   110,  1126,  1082,    -1,    -1,
      93,  1126,  1082,    -1,    -1,   387,  1126,  1082,    -1,    -1,
     144,    -1,   986,    -1,   995,    -1,   997,    -1,   425,   987,
     989,   990,   991,   994,  1135,   988,    -1,    -1,   184,    -1,
    1057,    -1,   203,    -1,   281,    -1,   211,    -1,   163,    -1,
      -1,     8,    -1,    -1,   373,    -1,   160,    -1,   156,    -1,
     160,    -1,   282,    -1,   258,    -1,   260,    -1,    -1,   300,
      -1,   425,  1124,   104,  1135,   996,    -1,  1062,    -1,     9,
     301,    -1,   425,   987,    35,   326,  1082,    -1,    -1,   437,
     999,  1055,  1000,   911,  1001,  1003,  1004,    -1,    -1,   176,
    1079,    -1,    -1,  1002,  1111,  1081,  1130,    -1,  1002,  1111,
    1060,    -1,  1002,  1111,   286,    -1,    35,    -1,     8,    -1,
      -1,  1026,    -1,  1032,    -1,    -1,   145,    -1,  1007,  1009,
      -1,  1007,  1009,    -1,    -1,    -1,   160,  1008,   738,    -1,
      -1,    -1,   258,  1010,   738,    -1,  1012,  1014,    -1,    -1,
      -1,   366,  1013,   738,    -1,    -1,    -1,   261,  1015,   738,
      -1,  1017,  1019,    -1,    -1,    -1,   282,  1018,   738,    -1,
      -1,    -1,   260,  1020,   738,    -1,  1022,    -1,  1024,    -1,
    1022,  1024,    -1,    -1,   123,  1023,   738,    -1,    -1,   256,
    1025,   738,    -1,  1027,    -1,  1029,    -1,  1027,  1029,    -1,
      -1,   151,  1028,   738,    -1,    -1,   257,  1030,   738,    -1,
      -1,  1032,    -1,  1033,    -1,  1035,    -1,  1033,  1035,    -1,
      -1,   209,  1034,   738,    -1,    -1,   259,  1036,   738,    -1,
      -1,  1118,  1081,  1130,    -1,  1039,    -1,  1040,    -1,    -1,
    1041,  1042,    -1,  1042,   210,    -1,  1043,  1073,    -1,  1042,
     449,    -1,  1042,   272,    -1,  1042,   265,    -1,  1042,    12,
      -1,  1042,    13,    -1,  1042,    14,    -1,  1042,    58,    -1,
    1042,   295,    -1,  1042,   251,    -1,  1042,   440,    -1,  1042,
     255,    -1,    -1,  1043,   210,    -1,  1043,   450,    -1,  1043,
     441,    -1,  1043,   442,    -1,  1043,   446,    -1,  1043,   255,
      -1,  1042,   441,    -1,  1042,   442,    -1,  1042,   443,    -1,
    1042,   444,    -1,  1042,   446,    -1,  1042,  1044,    -1,  1042,
    1045,    -1,  1042,  1046,    -1,  1042,  1047,    -1,  1042,  1048,
      -1,  1042,   250,    -1,  1043,  1044,    -1,  1043,  1045,    -1,
    1043,  1046,    -1,  1043,  1047,    -1,  1043,  1048,    -1,  1043,
     250,    -1,  1042,    20,    -1,  1042,   277,    -1,   448,    -1,
     153,  1150,    -1,   154,    -1,   451,    -1,   187,  1147,    -1,
     452,    -1,   222,  1147,    -1,   181,    -1,   187,  1147,   277,
     153,  1150,    -1,   187,  1147,   153,  1150,    -1,   218,    -1,
     222,  1147,   277,   153,  1150,    -1,   222,  1147,   153,  1150,
      -1,  1051,    -1,  1049,  1050,  1051,    -1,    -1,    69,    -1,
     353,    -1,  1074,    -1,  1051,   441,  1051,    -1,  1051,   442,
    1051,    -1,  1051,   443,  1051,    -1,  1051,   444,  1051,    -1,
     441,  1051,    -1,   442,  1051,    -1,  1051,   446,  1051,    -1,
     450,  1051,   449,    -1,   226,    -1,   226,  1107,   434,    -1,
    1054,    -1,  1053,  1054,    -1,  1073,  1105,    -1,  1084,    -1,
    1084,    -1,  1058,    -1,  1057,  1058,    -1,   434,    -1,  1060,
      -1,  1059,  1060,    -1,   242,    -1,    -1,  1061,  1062,    -1,
    1063,    -1,  1084,    -1,  1064,    -1,  1064,  1107,  1064,    -1,
     230,    -1,  1066,    -1,  1065,  1066,    -1,  1084,    -1,    -1,
    1066,    -1,  1066,    -1,   230,    -1,   434,    -1,  1071,    -1,
    1070,  1071,    -1,  1082,    -1,     6,  1134,  1083,    -1,  1073,
      -1,  1072,  1073,    -1,  1082,    -1,   221,  1134,  1083,    -1,
     221,  1134,  1089,    -1,   221,  1134,  1091,    -1,     6,  1134,
    1075,  1076,    -1,     6,  1134,  1083,    -1,  1088,    -1,  1091,
      -1,  1052,    -1,  1082,    -1,   221,  1134,  1083,    -1,   221,
    1134,  1089,    -1,   221,  1134,  1091,    -1,  1089,    -1,  1091,
      -1,  1052,    -1,   303,    -1,   146,    -1,  1083,    -1,   230,
      -1,  1082,    -1,  1089,    -1,  1082,    -1,  1088,    -1,  1082,
      -1,   230,    -1,  1082,    -1,   230,    -1,  1091,    -1,  1082,
      -1,  1087,    -1,   440,    -1,  1083,    -1,  1084,    -1,  1084,
    1085,    -1,  1084,  1086,    -1,  1084,  1085,  1086,    -1,   434,
      -1,   434,  1107,  1084,    -1,   450,  1049,   449,    -1,   450,
    1051,   453,   449,    -1,   450,  1051,   453,  1051,   449,    -1,
     230,    -1,  1089,    -1,     9,  1090,    -1,  1090,    -1,  1089,
     454,  1090,    -1,   230,    -1,   371,    -1,   440,    -1,   308,
      -1,   191,    -1,   237,    -1,   400,    -1,    96,  1092,    -1,
     431,  1092,    -1,   423,   450,  1051,   449,  1092,    -1,   235,
     450,  1051,   449,  1092,    -1,   335,   450,  1051,   449,  1092,
      -1,    81,   450,  1049,   449,  1092,    -1,   380,   450,  1049,
     449,  1092,    -1,   381,   450,  1049,   449,  1092,    -1,   405,
     450,  1095,   449,  1092,    -1,   267,   450,  1096,   449,    -1,
     232,   450,  1097,   449,  1092,    -1,   180,  1093,    -1,    -1,
     450,  1051,   453,   449,    -1,   450,  1051,   453,  1051,   449,
      -1,    -1,   450,  1094,   449,    -1,    -1,  1049,    -1,  1051,
      -1,  1051,  1050,   219,    -1,  1051,  1050,   403,    -1,  1051,
      -1,  1051,  1050,  1051,    -1,  1051,    -1,  1051,  1050,  1066,
      -1,    -1,    -1,     9,    -1,    -1,  1109,    -1,    -1,   201,
      -1,    -1,   252,    -1,   297,    -1,    -1,   255,    -1,    -1,
     276,    -1,    -1,   341,    -1,    -1,   355,  1119,    -1,   196,
      -1,   270,    -1,   312,  1127,    -1,   314,  1113,    -1,   433,
     119,    -1,   119,    -1,    62,   356,    -1,   356,    -1,    -1,
       7,    -1,    -1,    17,    -1,    -1,    23,    -1,    -1,    24,
      -1,    -1,    27,    -1,    -1,    30,    -1,    -1,    37,    -1,
      -1,    49,    -1,    -1,    55,    -1,    -1,    56,    -1,    -1,
      84,    -1,    -1,    99,    -1,    -1,   398,    -1,    -1,   172,
      -1,    -1,   176,    -1,    -1,   196,    -1,    -1,   210,    -1,
      -1,   210,    -1,    23,    -1,    -1,   214,    -1,    -1,   227,
      -1,   228,    -1,    -1,   228,    -1,    -1,   243,    -1,    -1,
     263,    -1,    -1,   270,    -1,    -1,   273,    -1,    -1,   278,
      -1,   196,   278,    -1,    -1,   280,    -1,    -1,   303,    -1,
      -1,   312,    -1,    -1,   339,    -1,    -1,   358,    -1,    -1,
     360,    -1,    -1,   360,    -1,   360,   210,    -1,    -1,   365,
      -1,    -1,   377,    -1,    -1,   388,    -1,    -1,   391,    -1,
      -1,   392,    -1,    -1,   395,    -1,    -1,   396,    -1,    -1,
     430,    -1,    -1,   433,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   763,   763,   763,   805,   806,   810,   811,   816,   817,
     815,   825,   826,   824,   834,   835,   833,   840,   841,   842,
     845,   846,   872,   896,   926,   925,   966,  1010,  1011,  1015,
    1016,  1019,  1020,  1024,  1031,  1038,  1042,  1046,  1058,  1059,
    1069,  1070,  1079,  1080,  1084,  1085,  1086,  1087,  1096,  1099,
    1100,  1101,  1102,  1106,  1113,  1122,  1125,  1126,  1127,  1128,
    1132,  1133,  1137,  1138,  1139,  1143,  1150,  1151,  1155,  1162,
    1174,  1177,  1178,  1182,  1183,  1187,  1191,  1198,  1199,  1209,
    1212,  1213,  1217,  1218,  1222,  1223,  1224,  1225,  1226,  1227,
    1228,  1229,  1230,  1231,  1232,  1239,  1250,  1249,  1261,  1260,
    1269,  1283,  1297,  1311,  1327,  1328,  1332,  1333,  1337,  1348,
    1349,  1357,  1356,  1368,  1369,  1370,  1371,  1372,  1380,  1381,
    1386,  1387,  1389,  1388,  1400,  1401,  1405,  1406,  1407,  1408,
    1409,  1410,  1414,  1415,  1416,  1417,  1418,  1419,  1426,  1437,
    1449,  1450,  1454,  1455,  1462,  1471,  1472,  1476,  1477,  1491,
    1506,  1573,  1584,  1591,  1598,  1604,  1611,  1612,  1616,  1615,
    1625,  1624,  1640,  1641,  1644,  1645,  1650,  1649,  1670,  1671,
    1675,  1676,  1677,  1678,  1679,  1680,  1681,  1682,  1683,  1684,
    1685,  1686,  1687,  1688,  1695,  1699,  1704,  1711,  1712,  1713,
    1716,  1717,  1721,  1728,  1729,  1736,  1743,  1747,  1748,  1749,
    1756,  1776,  1823,  1823,  1827,  1831,  1847,  1848,  1849,  1855,
    1865,  1874,  1876,  1877,  1883,  1887,  1888,  1889,  1892,  1893,
    1894,  1898,  1902,  1903,  1909,  1910,  1914,  1923,  1932,  1941,
    1950,  1965,  1975,  1982,  1986,  2024,  2031,  2038,  2042,  2043,
    2044,  2052,  2053,  2056,  2057,  2061,  2062,  2066,  2067,  2068,
    2074,  2099,  2100,  2101,  2102,  2108,  2115,  2116,  2120,  2123,
    2124,  2130,  2140,  2141,  2155,  2156,  2156,  2159,  2158,  2171,
    2172,  2176,  2188,  2197,  2201,  2202,  2212,  2211,  2229,  2230,
    2234,  2241,  2248,  2249,  2250,  2251,  2252,  2253,  2254,  2255,
    2256,  2257,  2264,  2268,  2268,  2268,  2274,  2286,  2311,  2335,
    2336,  2343,  2344,  2348,  2349,  2356,  2363,  2364,  2371,  2375,
    2384,  2385,  2391,  2401,  2419,  2420,  2424,  2425,  2426,  2430,
    2437,  2444,  2454,  2461,  2479,  2483,  2494,  2495,  2495,  2506,
    2507,  2511,  2511,  2528,  2529,  2531,  2535,  2537,  2536,  2567,
    2572,  2577,  2583,  2592,  2600,  2601,  2609,  2610,  2611,  2615,
    2635,  2639,  2648,  2649,  2650,  2651,  2652,  2653,  2654,  2655,
    2656,  2657,  2658,  2659,  2660,  2661,  2662,  2669,  2691,  2713,
    2714,  2726,  2746,  2753,  2754,  2758,  2759,  2760,  2761,  2762,
    2763,  2764,  2765,  2766,  2767,  2768,  2769,  2774,  2779,  2780,
    2781,  2782,  2783,  2784,  2785,  2786,  2787,  2788,  2789,  2790,
    2791,  2792,  2793,  2794,  2795,  2796,  2797,  2805,  2813,  2821,
    2828,  2833,  2844,  2861,  2862,  2865,  2866,  2873,  2897,  2898,
    2915,  2916,  2919,  2920,  2927,  2928,  2933,  2943,  2950,  2953,
    2954,  2955,  2962,  2969,  2994,  2994,  2999,  3000,  3004,  3005,
    3008,  3009,  3022,  3034,  3054,  3068,  3070,  3069,  3089,  3090,
    3090,  3103,  3105,  3104,  3116,  3117,  3121,  3122,  3131,  3138,
    3141,  3145,  3149,  3150,  3151,  3158,  3159,  3163,  3166,  3166,
    3169,  3170,  3176,  3181,  3182,  3185,  3186,  3189,  3190,  3193,
    3194,  3197,  3198,  3202,  3203,  3204,  3208,  3209,  3212,  3213,
    3217,  3221,  3222,  3226,  3227,  3228,  3229,  3230,  3231,  3232,
    3233,  3234,  3235,  3236,  3237,  3238,  3239,  3240,  3241,  3245,
    3249,  3250,  3251,  3252,  3253,  3254,  3255,  3259,  3263,  3264,
    3265,  3269,  3270,  3274,  3278,  3283,  3287,  3291,  3295,  3296,
    3300,  3301,  3305,  3306,  3307,  3310,  3310,  3310,  3313,  3317,
    3320,  3320,  3323,  3330,  3331,  3332,  3331,  3349,  3350,  3354,
    3355,  3360,  3362,  3361,  3397,  3398,  3402,  3403,  3404,  3405,
    3406,  3407,  3408,  3409,  3410,  3411,  3412,  3413,  3414,  3415,
    3416,  3417,  3418,  3422,  3426,  3430,  3434,  3435,  3436,  3437,
    3438,  3439,  3440,  3441,  3448,  3452,  3462,  3465,  3469,  3473,
    3477,  3485,  3488,  3492,  3496,  3500,  3508,  3521,  3523,  3533,
    3522,  3560,  3562,  3561,  3568,  3567,  3576,  3577,  3582,  3589,
    3591,  3595,  3605,  3607,  3615,  3623,  3652,  3683,  3685,  3695,
    3700,  3711,  3712,  3712,  3739,  3740,  3744,  3745,  3746,  3747,
    3763,  3775,  3806,  3843,  3855,  3858,  3859,  3868,  3872,  3868,
    3885,  3903,  3907,  3908,  3909,  3910,  3911,  3912,  3913,  3914,
    3915,  3916,  3917,  3918,  3919,  3920,  3921,  3922,  3923,  3924,
    3925,  3926,  3927,  3928,  3929,  3930,  3931,  3932,  3933,  3934,
    3935,  3936,  3937,  3938,  3939,  3940,  3941,  3942,  3943,  3944,
    3945,  3946,  3947,  3948,  3949,  3950,  3951,  3952,  3953,  3954,
    3955,  3956,  3979,  3978,  3991,  3995,  3999,  4003,  4007,  4011,
    4015,  4019,  4023,  4027,  4031,  4035,  4039,  4043,  4047,  4051,
    4055,  4062,  4063,  4064,  4065,  4066,  4067,  4071,  4075,  4076,
    4079,  4080,  4084,  4085,  4089,  4090,  4091,  4092,  4093,  4094,
    4095,  4096,  4100,  4104,  4108,  4113,  4114,  4115,  4116,  4117,
    4118,  4122,  4123,  4132,  4132,  4138,  4142,  4146,  4152,  4153,
    4157,  4158,  4167,  4167,  4172,  4176,  4183,  4184,  4193,  4199,
    4200,  4204,  4204,  4212,  4212,  4222,  4224,  4223,  4232,  4233,
    4238,  4245,  4252,  4254,  4258,  4266,  4277,  4278,  4279,  4284,
    4288,  4287,  4299,  4303,  4302,  4313,  4314,  4323,  4323,  4327,
    4328,  4340,  4340,  4344,  4345,  4356,  4357,  4358,  4359,  4360,
    4363,  4363,  4371,  4371,  4377,  4384,  4385,  4388,  4388,  4395,
    4408,  4421,  4421,  4432,  4433,  4442,  4442,  4462,  4461,  4474,
    4478,  4482,  4486,  4490,  4494,  4498,  4503,  4507,  4514,  4515,
    4516,  4520,  4521,  4526,  4527,  4528,  4529,  4530,  4531,  4532,
    4533,  4534,  4535,  4539,  4543,  4547,  4552,  4553,  4557,  4558,
    4567,  4567,  4573,  4577,  4581,  4585,  4589,  4596,  4597,  4606,
    4606,  4628,  4627,  4646,  4647,  4658,  4667,  4672,  4680,  4709,
    4710,  4716,  4715,  4731,  4735,  4734,  4749,  4750,  4755,  4756,
    4767,  4796,  4797,  4798,  4801,  4802,  4806,  4807,  4816,  4816,
    4821,  4822,  4830,  4847,  4864,  4882,  4907,  4907,  4920,  4920,
    4933,  4933,  4942,  4946,  4959,  4959,  4972,  4974,  4972,  4985,
    4990,  4994,  4993,  5007,  5008,  5017,  5017,  5025,  5026,  5030,
    5031,  5032,  5036,  5037,  5042,  5043,  5048,  5052,  5053,  5054,
    5055,  5056,  5057,  5058,  5062,  5063,  5072,  5072,  5085,  5084,
    5094,  5095,  5096,  5100,  5101,  5105,  5106,  5107,  5113,  5113,
    5118,  5119,  5123,  5124,  5125,  5126,  5127,  5128,  5134,  5138,
    5139,  5143,  5148,  5152,  5153,  5154,  5155,  5156,  5160,  5186,
    5199,  5200,  5204,  5204,  5212,  5212,  5222,  5222,  5227,  5231,
    5243,  5243,  5249,  5253,  5260,  5261,  5270,  5270,  5274,  5275,
    5289,  5290,  5291,  5292,  5296,  5297,  5301,  5302,  5303,  5315,
    5315,  5320,  5325,  5324,  5334,  5341,  5342,  5346,  5351,  5360,
    5363,  5367,  5372,  5379,  5386,  5387,  5391,  5392,  5397,  5409,
    5409,  5432,  5433,  5437,  5438,  5442,  5446,  5450,  5454,  5461,
    5462,  5476,  5477,  5478,  5482,  5483,  5492,  5492,  5507,  5507,
    5518,  5519,  5528,  5528,  5539,  5540,  5544,  5551,  5552,  5561,
    5574,  5574,  5580,  5585,  5584,  5595,  5596,  5600,  5602,  5601,
    5612,  5613,  5618,  5617,  5628,  5629,  5638,  5638,  5643,  5644,
    5645,  5646,  5647,  5653,  5662,  5666,  5675,  5682,  5683,  5689,
    5690,  5694,  5703,  5704,  5708,  5712,  5724,  5724,  5730,  5729,
    5746,  5749,  5765,  5766,  5769,  5770,  5774,  5775,  5780,  5785,
    5793,  5805,  5810,  5818,  5834,  5835,  5834,  5855,  5856,  5872,
    5873,  5874,  5875,  5876,  5880,  5881,  5890,  5890,  5895,  5902,
    5903,  5904,  5913,  5913,  5922,  5923,  5927,  5928,  5929,  5933,
    5934,  5938,  5939,  5948,  5948,  5954,  5958,  5962,  5969,  5970,
    5979,  5986,  5987,  5995,  5995,  6008,  6008,  6024,  6024,  6033,
    6035,  6036,  6045,  6045,  6055,  6056,  6061,  6062,  6067,  6074,
    6075,  6080,  6087,  6088,  6092,  6093,  6097,  6098,  6102,  6103,
    6112,  6113,  6114,  6118,  6142,  6145,  6153,  6163,  6168,  6173,
    6178,  6185,  6186,  6189,  6190,  6194,  6194,  6198,  6198,  6202,
    6202,  6205,  6206,  6210,  6217,  6218,  6222,  6234,  6234,  6245,
    6246,  6251,  6254,  6258,  6262,  6269,  6270,  6273,  6274,  6275,
    6279,  6280,  6293,  6301,  6308,  6310,  6309,  6319,  6321,  6320,
    6335,  6339,  6341,  6340,  6351,  6353,  6352,  6369,  6375,  6377,
    6376,  6386,  6388,  6387,  6403,  6408,  6413,  6423,  6422,  6434,
    6433,  6449,  6454,  6459,  6469,  6468,  6480,  6479,  6494,  6495,
    6499,  6504,  6509,  6519,  6518,  6530,  6529,  6546,  6549,  6561,
    6568,  6575,  6575,  6585,  6586,  6587,  6589,  6590,  6591,  6592,
    6593,  6594,  6596,  6597,  6598,  6600,  6603,  6605,  6606,  6608,
    6609,  6610,  6612,  6614,  6615,  6616,  6617,  6618,  6620,  6621,
    6622,  6623,  6624,  6625,  6627,  6628,  6629,  6630,  6631,  6632,
    6634,  6635,  6638,  6638,  6638,  6639,  6639,  6640,  6640,  6641,
    6641,  6641,  6642,  6642,  6642,  6647,  6648,  6651,  6652,  6653,
    6657,  6658,  6659,  6660,  6661,  6662,  6663,  6664,  6665,  6676,
    6688,  6703,  6704,  6709,  6715,  6721,  6741,  6745,  6761,  6775,
    6776,  6781,  6787,  6788,  6793,  6802,  6803,  6804,  6808,  6819,
    6820,  6824,  6832,  6833,  6837,  6838,  6844,  6864,  6865,  6869,
    6870,  6874,  6875,  6879,  6880,  6881,  6882,  6883,  6884,  6885,
    6886,  6887,  6891,  6892,  6893,  6894,  6895,  6896,  6897,  6901,
    6902,  6906,  6907,  6911,  6912,  6916,  6917,  6928,  6929,  6933,
    6934,  6935,  6939,  6940,  6941,  6949,  6953,  6954,  6955,  6956,
    6960,  6961,  6965,  6975,  6993,  7020,  7032,  7033,  7043,  7044,
    7048,  7049,  7050,  7051,  7052,  7053,  7054,  7062,  7066,  7070,
    7074,  7078,  7082,  7086,  7090,  7094,  7098,  7102,  7106,  7113,
    7114,  7115,  7119,  7120,  7124,  7125,  7130,  7137,  7144,  7154,
    7161,  7171,  7178,  7192,  7202,  7203,  7207,  7208,  7212,  7213,
    7217,  7218,  7219,  7223,  7224,  7228,  7229,  7233,  7234,  7238,
    7239,  7246,  7246,  7247,  7247,  7248,  7248,  7249,  7249,  7251,
    7251,  7252,  7252,  7253,  7253,  7254,  7254,  7255,  7255,  7256,
    7256,  7257,  7257,  7258,  7258,  7259,  7259,  7260,  7260,  7261,
    7261,  7262,  7262,  7263,  7263,  7264,  7264,  7265,  7265,  7266,
    7266,  7267,  7267,  7268,  7268,  7268,  7269,  7269,  7270,  7270,
    7270,  7271,  7271,  7272,  7272,  7273,  7273,  7274,  7274,  7275,
    7275,  7276,  7276,  7276,  7277,  7277,  7278,  7278,  7279,  7279,
    7280,  7280,  7281,  7281,  7282,  7282,  7283,  7283,  7283,  7284,
    7284,  7285,  7285,  7286,  7286,  7287,  7287,  7288,  7288,  7289,
    7289,  7290,  7290,  7292,  7292,  7293,  7293
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
  "record_description_list_2", "data_description", "$@22", "level_number",
  "entry_name", "const_name", "const_global", "lit_or_length",
  "constant_entry", "data_description_clause_sequence",
  "data_description_clause", "redefines_clause", "external_clause",
  "as_extname", "global_clause", "picture_clause", "usage_clause", "usage",
  "sign_clause", "occurs_clause", "occurs_to_integer", "occurs_depending",
  "occurs_keys", "occurs_key_list", "ascending_or_descending",
  "occurs_indexed", "occurs_index_list", "occurs_index",
  "justified_clause", "synchronized_clause", "left_or_right",
  "blank_clause", "based_clause", "value_clause", "$@23",
  "value_item_list", "value_item", "false_is", "renames_clause",
  "any_length_clause", "local_storage_section", "$@24", "linkage_section",
  "$@25", "report_section", "$@26", "opt_report_description_list",
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
  "_indicate", "report_name", "screen_section", "$@27", "$@28",
  "opt_screen_description_list", "screen_description_list",
  "screen_description", "$@29", "screen_options", "screen_option",
  "screen_line_plus_minus", "screen_col_plus_minus",
  "screen_occurs_clause", "procedure_division", "$@30", "$@31",
  "procedure_using_chaining", "$@32", "$@33", "procedure_param_list",
  "procedure_param", "procedure_type", "size_optional",
  "procedure_optional", "procedure_returning", "procedure_declaratives",
  "$@34", "procedure_list", "procedure", "section_header",
  "paragraph_header", "invalid_statement", "section_name", "opt_segment",
  "statement_list", "@35", "@36", "statements", "statement",
  "accept_statement", "$@37", "accept_body", "opt_at_line_column",
  "line_number", "column_number", "opt_accp_attr", "accp_attrs",
  "accp_attr", "end_accept", "add_statement", "$@38", "add_body", "add_to",
  "end_add", "allocate_statement", "$@39", "allocate_body",
  "allocate_returning", "alter_statement", "alter_options", "_proceed_to",
  "call_statement", "$@40", "call_using", "$@41", "call_param_list",
  "call_param", "call_type", "call_returning", "call_on_exception", "$@42",
  "call_not_on_exception", "$@43", "end_call", "cancel_statement", "$@44",
  "cancel_list", "close_statement", "$@45", "close_list", "close_option",
  "reel_or_unit", "compute_statement", "$@46", "compute_body",
  "end_compute", "comp_equal", "commit_statement", "continue_statement",
  "delete_statement", "$@47", "end_delete", "delete_file_statement",
  "$@48", "display_statement", "$@49", "display_body", "with_clause",
  "disp_attrs", "disp_attr", "end_display", "divide_statement", "$@50",
  "divide_body", "end_divide", "entry_statement", "$@51",
  "evaluate_statement", "$@52", "evaluate_subject_list",
  "evaluate_subject", "evaluate_condition_list", "evaluate_case_list",
  "evaluate_case", "$@53", "evaluate_other", "$@54", "evaluate_when_list",
  "evaluate_object_list", "evaluate_object", "opt_evaluate_thru_expr",
  "end_evaluate", "exit_statement", "$@55", "exit_body", "free_statement",
  "$@56", "generate_statement", "$@57", "goto_statement", "$@58",
  "goto_depending", "goback_statement", "$@59", "if_statement", "$@60",
  "$@61", "if_else_sentence", "$@62", "end_if", "initialize_statement",
  "$@63", "initialize_filler", "initialize_value", "initialize_replacing",
  "initialize_replacing_list", "initialize_replacing_item",
  "initialize_category", "initialize_default", "initiate_statement",
  "$@64", "inspect_statement", "$@65", "send_identifier", "inspect_list",
  "inspect_item", "inspect_tallying", "$@66", "tallying_list",
  "tallying_item", "inspect_replacing", "replacing_list", "replacing_item",
  "rep_keyword", "replacing_region", "inspect_converting",
  "inspect_region", "_initial", "merge_statement", "$@67",
  "move_statement", "$@68", "move_body", "multiply_statement", "$@69",
  "multiply_body", "end_multiply", "open_statement", "$@70", "open_list",
  "open_mode", "open_sharing", "open_option", "perform_statement", "$@71",
  "perform_body", "$@72", "end_perform", "perform_procedure",
  "perform_option", "perform_test", "perform_varying_list",
  "perform_varying", "read_statement", "$@73", "read_into", "with_lock",
  "read_key", "read_handler", "end_read", "release_statement", "$@74",
  "return_statement", "$@75", "end_return", "rewrite_statement", "$@76",
  "write_lock", "end_rewrite", "rollback_statement", "search_statement",
  "$@77", "search_body", "$@78", "search_varying", "search_at_end", "$@79",
  "search_whens", "search_when", "$@80", "end_search", "set_statement",
  "$@81", "set_body", "set_environment", "set_to", "set_up_down",
  "up_or_down", "set_to_on_off_sequence", "set_to_on_off",
  "set_to_true_false_sequence", "set_to_true_false", "sort_statement",
  "$@82", "sort_body", "$@83", "sort_key_list", "opt_key_list",
  "sort_duplicates", "sort_collating", "sort_input", "sort_output",
  "start_statement", "$@84", "@85", "start_key", "start_op", "end_start",
  "stop_statement", "$@86", "stop_returning", "string_statement", "$@87",
  "string_item_list", "string_item", "opt_with_pointer", "end_string",
  "subtract_statement", "$@88", "subtract_body", "end_subtract",
  "suppress_statement", "_printing", "terminate_statement", "$@89",
  "transform_statement", "$@90", "unlock_statement", "$@91", "opt_record",
  "unstring_statement", "$@92", "unstring_delimited",
  "unstring_delimited_list", "unstring_delimited_item", "unstring_into",
  "unstring_into_item", "unstring_into_delimiter", "unstring_into_count",
  "unstring_tallying", "end_unstring", "use_statement", "use_exception",
  "use_global", "use_exception_target", "_after", "_standard",
  "exception_or_error", "exception_or_overflow",
  "not_exception_or_overflow", "_procedure", "use_debugging",
  "use_debugging_target", "use_reporting", "write_statement", "$@93",
  "write_from", "write_option", "before_or_after", "write_handler",
  "end_write", "on_accp_exception", "on_disp_exception",
  "opt_on_exception", "$@94", "opt_not_on_exception", "$@95",
  "on_size_error", "opt_on_size_error", "$@96", "opt_not_on_size_error",
  "$@97", "on_overflow", "opt_on_overflow", "$@98", "opt_not_on_overflow",
  "$@99", "at_end", "at_end_sentence", "$@100", "not_at_end_sentence",
  "$@101", "at_eop", "at_eop_sentence", "$@102", "not_at_eop_sentence",
  "$@103", "opt_invalid_key", "invalid_key", "invalid_key_sentence",
  "$@104", "not_invalid_key_sentence", "$@105", "_opt_scroll_lines",
  "condition", "expr", "partial_expr", "$@106", "expr_tokens",
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
     695,    43,    45,    42,    47,   696,    94,    46,    61,    41,
      40,    62,    60,    58,    38
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   455,   457,   456,   458,   458,   459,   459,   461,   462,
     460,   464,   465,   463,   467,   468,   466,   469,   469,   469,
     470,   470,   471,   472,   474,   473,   475,   476,   476,   477,
     477,   478,   478,   479,   479,   479,   480,   480,   481,   481,
     482,   482,   483,   483,   484,   484,   484,   484,   485,   486,
     486,   486,   486,   487,   488,   489,   490,   490,   490,   490,
     491,   491,   492,   492,   492,   493,   494,   494,   495,   496,
     497,   498,   498,   499,   499,   500,   500,   501,   501,   502,
     503,   503,   504,   504,   505,   505,   505,   505,   505,   505,
     505,   505,   505,   505,   505,   506,   507,   506,   508,   506,
     506,   506,   506,   506,   509,   509,   510,   510,   511,   512,
     512,   514,   513,   515,   515,   515,   515,   515,   516,   516,
     517,   517,   518,   517,   519,   519,   520,   520,   520,   520,
     520,   520,   521,   521,   521,   521,   521,   521,   522,   523,
     524,   524,   525,   525,   526,   527,   527,   528,   528,   529,
     530,   531,   532,   533,   534,   535,   536,   536,   537,   536,
     538,   536,   539,   539,   540,   540,   542,   541,   543,   543,
     544,   544,   544,   544,   544,   544,   544,   544,   544,   544,
     544,   544,   544,   544,   545,   545,   545,   546,   546,   546,
     547,   547,   547,   548,   548,   548,   549,   550,   550,   550,
     551,   551,   553,   552,   552,   554,   555,   555,   555,   556,
     557,   558,   558,   558,   559,   560,   560,   560,   561,   561,
     561,   561,   562,   562,   563,   563,   564,   564,   564,   564,
     564,   565,   566,   567,   567,   568,   569,   570,   571,   571,
     571,   572,   572,   573,   573,   574,   574,   575,   575,   575,
     576,   577,   577,   577,   577,   578,   579,   579,   580,   581,
     581,   582,   583,   583,   584,   585,   584,   586,   584,   587,
     587,   588,   589,   589,   590,   590,   592,   591,   593,   593,
     594,   594,   594,   594,   594,   594,   594,   594,   594,   594,
     594,   594,   595,   596,   596,   596,   597,   597,   597,   598,
     598,   599,   599,   600,   600,   601,   602,   602,   603,   603,
     604,   604,   605,   606,   607,   607,   608,   608,   608,   609,
     610,   611,   612,   613,   614,   614,   615,   616,   615,   617,
     617,   619,   618,   620,   620,   620,   621,   622,   621,   623,
     624,   624,   624,   625,   626,   626,   627,   627,   627,   628,
     629,   629,   630,   630,   630,   630,   630,   630,   630,   630,
     630,   630,   630,   630,   630,   630,   630,   631,   632,   633,
     633,   634,   635,   636,   636,   637,   637,   637,   637,   637,
     637,   637,   637,   637,   637,   637,   637,   637,   637,   637,
     637,   637,   637,   637,   637,   637,   637,   637,   637,   637,
     637,   637,   637,   637,   637,   637,   637,   637,   637,   637,
     638,   638,   639,   640,   640,   641,   641,   642,   643,   643,
     644,   644,   645,   645,   646,   646,   647,   648,   649,   650,
     650,   650,   651,   652,   654,   653,   655,   655,   656,   656,
     657,   657,   658,   658,   659,   660,   661,   660,   662,   663,
     662,   664,   665,   664,   666,   666,   667,   667,   668,   669,
     669,   670,   670,   670,   670,   671,   671,   672,   673,   673,
     674,   674,   675,   676,   676,   677,   677,   678,   678,   679,
     679,   680,   680,   681,   681,   681,   682,   682,   683,   683,
     684,   685,   685,   686,   686,   686,   686,   686,   686,   686,
     686,   686,   686,   686,   686,   686,   686,   686,   686,   687,
     688,   688,   688,   688,   688,   688,   688,   689,   690,   690,
     690,   691,   691,   692,   693,   694,   695,   696,   697,   697,
     698,   698,   699,   699,   699,   700,   700,   700,   701,   702,
     703,   703,   704,   705,   706,   707,   705,   708,   708,   709,
     709,   710,   711,   710,   712,   712,   713,   713,   713,   713,
     713,   713,   713,   713,   713,   713,   713,   713,   713,   713,
     713,   713,   713,   713,   713,   713,   713,   713,   713,   713,
     713,   713,   713,   713,   713,   713,   714,   714,   714,   714,
     714,   715,   715,   715,   715,   715,   716,   717,   718,   719,
     717,   720,   721,   720,   722,   720,   723,   723,   724,   725,
     725,   725,   726,   726,   726,   726,   726,   727,   727,   728,
     728,   729,   730,   729,   731,   731,   732,   732,   732,   732,
     732,   733,   734,   735,   736,   737,   737,   739,   740,   738,
     741,   741,   742,   742,   742,   742,   742,   742,   742,   742,
     742,   742,   742,   742,   742,   742,   742,   742,   742,   742,
     742,   742,   742,   742,   742,   742,   742,   742,   742,   742,
     742,   742,   742,   742,   742,   742,   742,   742,   742,   742,
     742,   742,   742,   742,   742,   742,   742,   742,   742,   742,
     742,   742,   744,   743,   745,   745,   745,   745,   745,   745,
     745,   745,   745,   745,   745,   745,   745,   745,   745,   745,
     745,   746,   746,   746,   746,   746,   746,   747,   748,   748,
     749,   749,   750,   750,   751,   751,   751,   751,   751,   751,
     751,   751,   751,   751,   751,   751,   751,   751,   751,   751,
     751,   752,   752,   754,   753,   755,   755,   755,   756,   756,
     757,   757,   759,   758,   760,   760,   761,   761,   762,   763,
     763,   764,   764,   766,   765,   767,   768,   767,   769,   769,
     770,   770,   771,   771,   771,   771,   772,   772,   772,   773,
     774,   773,   775,   776,   775,   777,   777,   779,   778,   780,
     780,   782,   781,   783,   783,   784,   784,   784,   784,   784,
     785,   785,   787,   786,   788,   789,   789,   790,   790,   791,
     792,   794,   793,   795,   795,   797,   796,   799,   798,   800,
     800,   800,   800,   800,   800,   800,   800,   800,   801,   801,
     801,   802,   802,   803,   803,   803,   803,   803,   803,   803,
     803,   803,   803,   803,   803,   803,   803,   803,   804,   804,
     806,   805,   807,   807,   807,   807,   807,   808,   808,   810,
     809,   812,   811,   813,   813,   814,   814,   814,   815,   816,
     816,   818,   817,   819,   820,   819,   821,   821,   822,   822,
     823,   823,   823,   823,   824,   824,   825,   825,   827,   826,
     828,   828,   828,   828,   828,   828,   830,   829,   832,   831,
     834,   833,   835,   835,   837,   836,   839,   840,   838,   838,
     841,   842,   841,   843,   843,   845,   844,   846,   846,   847,
     847,   847,   848,   848,   849,   849,   850,   851,   851,   851,
     851,   851,   851,   851,   852,   852,   854,   853,   856,   855,
     857,   857,   857,   858,   858,   859,   859,   859,   861,   860,
     862,   862,   863,   863,   863,   863,   863,   863,   864,   865,
     865,   866,   866,   867,   867,   867,   867,   867,   868,   869,
     870,   870,   871,   871,   873,   872,   875,   874,   876,   876,
     878,   877,   879,   879,   880,   880,   882,   881,   883,   883,
     884,   884,   884,   884,   885,   885,   886,   886,   886,   888,
     887,   889,   890,   889,   889,   891,   891,   892,   892,   893,
     893,   893,   893,   893,   894,   894,   895,   895,   896,   898,
     897,   899,   899,   900,   900,   900,   900,   900,   900,   901,
     901,   902,   902,   902,   903,   903,   905,   904,   907,   906,
     908,   908,   910,   909,   911,   911,   911,   912,   912,   913,
     915,   914,   916,   917,   916,   918,   918,   919,   920,   919,
     921,   921,   923,   922,   924,   924,   926,   925,   927,   927,
     927,   927,   927,   928,   929,   929,   930,   931,   931,   932,
     932,   933,   934,   934,   935,   935,   937,   936,   939,   938,
     940,   940,   941,   941,   942,   942,   943,   943,   944,   944,
     944,   945,   945,   945,   947,   948,   946,   949,   949,   950,
     950,   950,   950,   950,   951,   951,   953,   952,   952,   954,
     954,   954,   956,   955,   957,   957,   958,   958,   958,   959,
     959,   960,   960,   962,   961,   963,   963,   963,   964,   964,
     965,   966,   966,   968,   967,   970,   969,   972,   971,   973,
     973,   973,   975,   974,   976,   976,   977,   977,   978,   979,
     979,   980,   981,   981,   982,   982,   983,   983,   984,   984,
     985,   985,   985,   986,   987,   987,   988,   988,   988,   988,
     988,   989,   989,   990,   990,   991,   991,   992,   992,   993,
     993,   994,   994,   995,   996,   996,   997,   999,   998,  1000,
    1000,  1001,  1001,  1001,  1001,  1002,  1002,  1003,  1003,  1003,
    1004,  1004,  1005,  1006,  1007,  1008,  1007,  1009,  1010,  1009,
    1011,  1012,  1013,  1012,  1014,  1015,  1014,  1016,  1017,  1018,
    1017,  1019,  1020,  1019,  1021,  1021,  1021,  1023,  1022,  1025,
    1024,  1026,  1026,  1026,  1028,  1027,  1030,  1029,  1031,  1031,
    1032,  1032,  1032,  1034,  1033,  1036,  1035,  1037,  1037,  1038,
    1039,  1041,  1040,  1042,  1042,  1042,  1042,  1042,  1042,  1042,
    1042,  1042,  1042,  1042,  1042,  1042,  1043,  1043,  1043,  1043,
    1043,  1043,  1043,  1043,  1043,  1043,  1043,  1043,  1043,  1043,
    1043,  1043,  1043,  1043,  1043,  1043,  1043,  1043,  1043,  1043,
    1043,  1043,  1044,  1044,  1044,  1045,  1045,  1046,  1046,  1047,
    1047,  1047,  1048,  1048,  1048,  1049,  1049,  1050,  1050,  1050,
    1051,  1051,  1051,  1051,  1051,  1051,  1051,  1051,  1051,  1052,
    1052,  1053,  1053,  1054,  1055,  1056,  1057,  1057,  1058,  1059,
    1059,  1060,  1061,  1061,  1062,  1063,  1063,  1063,  1064,  1065,
    1065,  1066,  1067,  1067,  1068,  1068,  1069,  1070,  1070,  1071,
    1071,  1072,  1072,  1073,  1073,  1073,  1073,  1073,  1073,  1073,
    1073,  1073,  1074,  1074,  1074,  1074,  1074,  1074,  1074,  1075,
    1075,  1076,  1076,  1077,  1077,  1078,  1078,  1079,  1079,  1080,
    1080,  1080,  1081,  1081,  1081,  1082,  1083,  1083,  1083,  1083,
    1084,  1084,  1085,  1086,  1086,  1087,  1088,  1088,  1089,  1089,
    1090,  1090,  1090,  1090,  1090,  1090,  1090,  1091,  1091,  1091,
    1091,  1091,  1091,  1091,  1091,  1091,  1091,  1091,  1091,  1092,
    1092,  1092,  1093,  1093,  1094,  1094,  1095,  1095,  1095,  1096,
    1096,  1097,  1097,  1098,  1099,  1099,  1100,  1100,  1101,  1101,
    1102,  1102,  1102,  1103,  1103,  1104,  1104,  1105,  1105,  1106,
    1106,  1107,  1107,  1108,  1108,  1109,  1109,  1110,  1110,  1111,
    1111,  1112,  1112,  1113,  1113,  1114,  1114,  1115,  1115,  1116,
    1116,  1117,  1117,  1118,  1118,  1119,  1119,  1120,  1120,  1121,
    1121,  1122,  1122,  1123,  1123,  1124,  1124,  1125,  1125,  1126,
    1126,  1127,  1127,  1128,  1128,  1128,  1129,  1129,  1130,  1130,
    1130,  1131,  1131,  1132,  1132,  1133,  1133,  1134,  1134,  1135,
    1135,  1136,  1136,  1136,  1137,  1137,  1138,  1138,  1139,  1139,
    1140,  1140,  1141,  1141,  1142,  1142,  1143,  1143,  1143,  1144,
    1144,  1145,  1145,  1146,  1146,  1147,  1147,  1148,  1148,  1149,
    1149,  1150,  1150,  1151,  1151,  1152,  1152
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
       1,     1,     1,     1,     1,     3,     0,     5,     0,     4,
       3,     3,     3,     3,     0,     2,     1,     2,     4,     1,
       1,     0,     5,     1,     1,     1,     1,     1,     1,     2,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       1,     2,     1,     2,     4,     1,     2,     1,     3,     4,
       4,     3,     3,     4,     3,     3,     0,     5,     0,     4,
       0,     4,     0,     3,     0,     2,     0,     6,     0,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     4,     4,     0,     1,     1,
       0,     1,     1,     1,     1,     1,     4,     1,     1,     1,
       6,     8,     0,     2,     2,     1,     0,     2,     1,     3,
       5,     0,     1,     1,     4,     2,     2,     1,     0,     4,
       5,     2,     1,     1,     3,     1,     1,     3,     1,     1,
       2,     4,     4,     4,     6,     4,     3,     3,     2,     2,
       2,     0,     3,     0,     2,     1,     2,     1,     1,     1,
       5,     0,     1,     1,     1,     5,     1,     2,     2,     0,
       2,     4,     0,     9,     0,     0,     5,     0,     3,     0,
       2,     3,     2,     2,     1,     1,     0,     4,     0,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     0,     1,     1,     4,     6,     9,     0,
       3,     0,     2,     0,     2,     3,     1,     1,     5,     5,
       1,     1,     3,     5,     0,     2,     1,     1,     1,     5,
       4,     3,     4,     3,     3,     3,     0,     0,     5,     0,
       1,     0,     2,     3,     4,     2,     1,     0,     4,     1,
       0,     1,     1,     1,     0,     2,     1,     3,     3,     6,
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
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
       1,     4,     2,     1,     1,     0,     1,     0,     0,     3,
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
       5,     4,     1,     5,     4,     1,     3,     0,     1,     1,
       1,     3,     3,     3,     3,     2,     2,     3,     3,     1,
       3,     1,     2,     2,     1,     1,     1,     2,     1,     1,
       2,     1,     0,     2,     1,     1,     1,     3,     1,     1,
       2,     1,     0,     1,     1,     1,     1,     1,     2,     1,
       3,     1,     2,     1,     3,     3,     3,     4,     3,     1,
       1,     1,     1,     3,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     3,
       1,     3,     3,     4,     5,     1,     1,     2,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     5,
       5,     5,     5,     5,     5,     5,     4,     5,     2,     0,
       4,     5,     0,     3,     0,     1,     1,     3,     3,     1,
       3,     1,     3,     0,     0,     1,     0,     1,     0,     1,
       0,     1,     1,     0,     1,     0,     1,     0,     1,     0,
       2,     1,     1,     2,     2,     2,     1,     2,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     1,     0,     1,     0,     1,
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
       2,     0,     0,     1,     0,     0,     3,     4,     6,     7,
      38,    38,     0,     0,     5,     0,     8,    14,    28,    27,
      29,    29,     0,   262,   262,     0,     0,    24,    40,     0,
       9,    15,    30,    26,  1501,     0,   156,     0,   597,   597,
    1502,     0,     0,     0,     0,     0,     0,    39,   264,     0,
      17,     0,    25,    33,    37,    36,  1526,    35,    42,   158,
       0,   160,   274,   275,     0,   326,   267,   601,    18,    20,
      38,     0,    16,    34,  1527,    32,    41,   164,   162,   243,
       0,     0,   445,     0,   604,   602,   619,     0,    19,    10,
      11,     0,     0,     0,     0,     0,    43,    44,    45,    47,
      46,   159,     0,   241,     0,  1493,   251,   161,     0,   245,
     247,   248,   249,   265,     0,     0,   448,  1338,   268,   329,
     276,   609,   609,     0,     0,     0,   262,    23,    56,    71,
      49,    80,  1455,   165,   164,     0,   157,  1519,  1494,  1543,
     252,   253,   254,  1475,   244,   246,   269,   327,     0,     0,
     451,   273,     0,   272,   330,  1443,   278,  1484,   609,   606,
     612,     0,   609,   620,   598,    21,    12,     0,  1501,    54,
    1526,    55,  1526,    60,    62,    63,    64,     0,     0,    70,
       0,    73,  1556,    48,     0,  1555,     0,     0,  1501,  1501,
       0,     0,  1534,  1501,  1501,  1501,  1501,  1501,     0,  1501,
    1487,  1501,    79,     0,    82,    84,    85,    86,    88,    87,
      89,    90,    91,    92,    93,    94,  1456,     0,   163,   243,
    1520,     0,  1544,  1489,  1476,  1495,   266,   329,   446,     0,
       0,   543,   329,   332,     0,     0,   607,  1501,     0,   617,
     610,   611,   621,   597,  1501,     0,    57,  1526,    59,    61,
       0,  1468,  1501,     0,    77,     0,    72,    74,    52,    50,
       0,     0,  1356,   111,     0,     0,  1501,  1501,  1535,  1501,
       0,     0,     0,     0,     0,  1501,     0,  1488,     0,    98,
      81,    83,   166,   242,  1400,   261,  1349,  1351,  1490,     0,
    1496,     0,   270,   328,   329,   449,     0,     0,   263,   271,
     335,     0,   339,     0,   340,   336,   291,  1489,  1501,     0,
       0,  1501,  1489,  1513,  1501,  1473,     0,   277,   279,   282,
     283,   284,   285,   286,   287,   288,   289,   290,     0,     0,
    1501,   618,     0,     0,   599,    17,     0,  1405,    69,    58,
    1467,     0,    76,    75,    78,    51,    53,  1501,   100,   101,
       0,     0,     0,   152,   151,   102,   103,   155,     0,   154,
     138,  1503,   140,    95,     0,    96,   168,  1461,  1462,     0,
    1350,   255,   256,   259,   250,  1336,   447,   329,   452,     0,
       0,   333,   341,   342,   337,     0,     0,     0,  1501,  1473,
       0,     0,     0,     0,     0,  1514,  1501,     0,  1474,     0,
       0,   280,   281,   613,   614,   616,     0,   608,   622,   624,
       0,     0,    68,     0,  1414,  1410,  1415,  1413,  1411,  1416,
    1412,   144,   145,   147,   153,   150,   149,  1505,  1504,   141,
       0,   110,   109,    99,   106,  1541,   104,     0,  1401,   257,
       0,   258,  1337,   450,   454,   544,   334,   350,   344,   303,
     323,  1463,  1464,   312,   307,   306,   305,  1355,  1354,  1511,
    1487,  1499,     0,   542,   324,   325,  1501,  1501,   615,   624,
       0,     0,    13,    66,    67,    65,   116,   130,   126,   131,
     113,   129,   127,   114,   115,   128,   112,   117,   118,   120,
     146,     0,   139,   142,   107,  1542,  1501,    97,   183,  1513,
       0,  1551,   226,     0,  1513,  1501,  1485,  1506,   229,     0,
     228,  1555,   213,   212,   167,   169,   170,   171,   172,   173,
     174,     0,   175,   176,   225,   177,   178,   179,   180,   181,
     182,  1501,   260,     0,   453,   455,   456,   545,     0,  1477,
       0,     0,   293,  1512,   314,     0,   296,  1500,  1539,   322,
       0,     0,     0,   630,   634,   625,   626,   627,   628,   633,
       0,     0,   119,   122,     0,   148,   143,     0,   105,  1501,
    1506,  1552,   190,   230,  1501,     0,  1486,  1501,  1482,  1501,
    1507,     0,  1501,  1501,  1475,     0,  1501,     0,   459,   457,
     547,   366,     0,   433,   375,   408,   396,   405,   402,   399,
    1553,   376,   377,   378,   379,   380,   381,   382,   383,   384,
    1530,   409,     0,   385,   372,   386,   387,     0,     0,  1537,
     389,   390,   388,   429,   392,   393,   391,  1501,  1503,   351,
     352,   353,   354,   355,   356,   373,   357,   358,   359,   360,
     361,   362,   363,   364,   365,     0,     0,  1478,     0,   345,
     304,   295,   294,   292,   313,  1487,  1540,   301,   310,   309,
     311,   308,     0,   632,   635,   692,   743,   752,   759,   763,
     787,   791,   809,   802,   810,   811,   817,   850,   859,   861,
     888,   896,   898,  1551,   904,     0,   915,   936,   938,   974,
     976,   980,   691,   986,   999,  1019,  1036,  1038,  1042,  1049,
    1050,  1066,  1086,  1104,     0,  1122,  1133,  1141,  1143,  1145,
    1147,  1152,  1174,  1197,   629,   641,   642,   643,   644,   645,
     646,   647,   648,   650,   649,   651,   652,   653,   654,   655,
     656,   657,   658,   659,   660,   661,   662,   663,   664,   665,
     666,   667,   668,   669,   670,   671,   672,   673,   674,   675,
     676,   677,   678,   679,   680,   681,   682,   683,   684,   685,
     686,   687,   688,   689,  1170,  1171,  1172,   690,    22,     0,
     121,   108,     0,  1501,   192,   191,   187,     0,  1481,   229,
     224,     0,     0,   227,     0,     0,   236,  1524,  1524,     0,
     237,     0,   209,  1501,   340,   551,   546,   548,   549,   444,
     406,   407,   394,   395,   403,   404,   400,   401,   397,   398,
    1554,     0,  1531,   427,   413,   367,  1396,   442,  1538,   430,
     431,   428,     0,     0,   369,   371,  1459,  1459,     0,  1517,
    1517,   349,   346,  1406,  1408,  1480,   315,   316,   317,   318,
       0,     0,   297,  1498,   303,     0,     0,   636,     0,     0,
       0,  1261,   758,     0,   789,   793,     0,     0,     0,     0,
       0,     0,  1261,   890,     0,     0,   900,   905,     0,  1261,
       0,     0,     0,     0,     0,     0,   988,  1009,     0,     0,
       0,     0,     0,     0,     0,     0,  1118,  1116,     0,     0,
    1142,  1140,     0,     0,     0,     0,  1175,  1181,     0,     0,
     136,   132,   137,   135,   133,   134,   123,   124,   198,   199,
     197,   196,     0,   185,   186,     0,   218,   217,   218,   214,
     231,   232,   233,   235,  1525,   238,   239,   240,  1352,  1501,
     468,   468,  1503,   488,   460,   463,   464,     0,   552,   550,
     432,     0,  1549,     0,  1397,  1398,     0,   374,   434,   436,
     438,     0,   368,  1485,   410,   411,  1407,  1518,     0,     0,
       0,     0,     0,  1479,  1487,   302,   623,   631,   741,   711,
    1395,  1517,     0,     0,  1429,  1432,  1517,  1329,     0,     0,
       0,     0,     0,     0,     0,     0,  1429,   750,  1371,   748,
    1361,  1363,  1369,  1370,  1448,   753,     0,  1260,  1276,  1348,
       0,  1344,  1346,  1345,  1390,   765,  1389,  1391,   788,   792,
     805,     0,  1331,  1457,  1528,     0,  1410,   848,   711,     0,
    1363,   857,     0,   765,   867,   866,  1471,   863,   865,   895,
     892,   891,   894,   889,  1517,   897,  1357,  1359,   899,  1342,
     909,  1547,  1259,   917,   937,   470,     0,   940,   941,   942,
     975,  1090,     0,   977,     0,   984,     0,   987,  1010,  1348,
    1000,  1009,  1002,     0,  1007,     0,  1345,     0,  1450,  1199,
    1334,  1528,  1199,     0,  1064,  1055,  1335,     0,  1341,  1067,
    1068,  1069,  1070,  1071,  1079,  1072,  1082,     0,  1339,     0,
    1087,  1105,  1119,  1483,     0,  1124,  1126,     0,  1138,     0,
    1144,     0,  1149,  1154,  1182,     0,  1183,  1519,  1199,     0,
    1446,   194,   193,   184,   195,     0,   216,   215,  1501,   208,
     202,  1353,   210,     0,   469,   465,     0,   466,     0,   458,
     461,   554,   414,  1550,   415,  1517,     0,     0,     0,  1317,
    1315,  1378,  1320,  1372,  1376,  1377,     0,  1399,   443,  1553,
     437,     0,   370,  1460,   348,   347,  1409,   321,  1511,     0,
     299,   742,   693,  1480,     0,   720,     0,     0,     0,     0,
       0,  1417,  1434,  1428,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1418,   751,   744,     0,     0,  1362,
    1449,   756,  1448,  1262,     0,   761,     0,   766,   776,  1388,
     790,  1387,   795,   806,   803,   808,   807,  1261,  1332,  1458,
    1333,  1529,  1248,   816,   849,   818,   828,  1214,  1214,  1214,
    1214,   858,   851,     0,     0,   860,  1472,  1261,   886,   873,
     869,   871,  1261,   893,     0,  1358,   902,  1548,   907,   919,
       0,   471,     0,   963,   948,   939,   943,   945,   946,   947,
    1094,     0,     0,   985,   981,     0,   993,   990,   992,   991,
     994,  1001,  1004,   637,  1261,     0,     0,  1011,     0,  1451,
    1452,  1528,     0,  1037,  1021,  1044,  1057,  1065,  1051,     0,
    1057,     0,  1383,  1384,  1080,  1083,     0,     0,  1340,  1078,
       0,  1077,     0,  1107,     0,     0,  1117,     0,     0,  1125,
       0,  1139,  1134,     0,     0,  1150,  1151,  1148,  1483,     0,
       0,  1184,     0,     0,  1044,   125,  1466,     0,   202,   200,
    1447,     0,   221,   207,   234,     0,   462,   467,   473,   483,
     340,   489,  1536,  1519,   418,     0,  1325,  1326,     0,  1318,
    1319,  1402,     0,     0,     0,     0,     0,     0,     0,     0,
    1532,   439,   320,  1511,  1519,   298,   716,   707,  1214,   697,
     704,   698,   700,   702,     0,  1214,     0,   696,   703,   710,
     709,     0,  1214,  1515,  1515,  1515,   714,   715,  1380,  1379,
       0,  1368,  1317,  1315,     0,     0,  1317,     0,  1364,  1365,
    1366,  1330,  1317,     0,     0,  1317,     0,     0,  1317,  1317,
    1317,     0,     0,  1221,  1457,     0,     0,   754,     0,  1268,
    1269,  1270,  1300,  1271,  1551,  1304,  1309,  1545,  1263,  1312,
    1545,  1293,  1273,  1275,  1267,  1266,  1301,  1272,  1274,  1283,
    1284,  1285,  1286,  1287,  1302,  1265,  1305,  1307,  1288,  1289,
    1290,  1291,  1292,  1277,  1299,  1282,  1279,  1280,  1281,  1278,
    1294,  1295,  1296,  1297,  1298,  1264,     0,     0,  1347,   772,
       0,     0,   779,   800,   801,   794,   796,     0,  1221,  1253,
    1255,   813,  1249,  1250,  1251,     0,  1556,  1214,     0,  1215,
     821,  1217,   822,   819,   820,     0,  1221,  1457,   881,   883,
     882,   876,   878,   884,   887,   862,   874,   870,   868,  1261,
     637,   864,  1360,  1519,   901,  1343,   637,  1551,   927,   928,
     930,   932,   933,   929,   931,   922,  1551,   918,     0,   964,
       0,   966,   965,   967,   958,   959,     0,     0,   944,  1096,
    1521,     0,     0,   978,  1221,  1457,  1555,     0,  1005,   638,
    1012,  1013,  1016,     0,  1008,  1206,  1205,  1015,  1021,  1200,
       0,     0,  1248,     0,     0,     0,  1056,     0,     0,     0,
    1081,     0,  1085,  1084,  1075,     0,  1501,  1248,  1121,  1120,
    1127,  1128,  1129,     0,  1221,  1457,     0,  1444,     0,  1129,
    1196,  1186,  1185,  1191,     0,  1193,  1194,  1201,  1465,  1446,
       0,   204,   205,   203,  1501,   475,   486,   487,   485,   342,
     491,   567,  1501,   558,   556,   557,   559,  1515,     0,  1501,
       0,   570,   562,  1515,   563,     0,   566,   571,   569,   564,
     568,     0,   565,     0,   553,   581,   576,   579,   578,   577,
     580,   555,   582,     0,   422,   417,  1373,  1374,  1375,  1328,
    1316,  1321,  1322,  1323,  1324,  1327,  1403,     0,  1533,  1551,
     319,     0,   708,  1217,   699,   701,  1214,   705,   695,   735,
    1501,   724,   725,  1501,   736,   726,   727,   730,   740,   737,
     728,     0,   738,   729,   739,   721,   722,   694,  1516,     0,
       0,     0,   712,   713,  1382,  1367,  1381,  1429,  1457,     0,
    1433,     0,  1429,  1429,     0,  1426,  1429,  1429,  1429,     0,
    1429,  1429,  1222,   745,  1224,  1221,   757,     0,  1303,  1546,
    1306,  1308,   762,   760,   767,   768,   612,     0,   778,   777,
    1187,  1188,   782,   780,     0,   799,     0,   804,   637,   637,
     814,   812,  1252,   828,   828,   828,   828,  1501,   833,   846,
     847,   834,     0,  1501,   837,   838,   841,   839,     0,   840,
     830,   831,   823,   829,   637,  1218,  1213,     0,   852,     0,
    1261,  1261,   880,   637,   877,   872,     0,   910,     0,     0,
     934,     0,     0,     0,   960,   962,     0,   954,   970,   955,
     956,   949,   950,   970,  1088,  1501,     0,  1522,  1095,   420,
     421,  1506,   979,   982,     0,     0,   996,  1006,  1003,   640,
       0,     0,  1023,  1022,  1237,  1239,  1040,  1234,  1235,  1047,
    1045,     0,  1261,  1058,  1261,  1052,  1060,  1073,  1074,  1076,
    1453,  1114,  1228,     0,  1457,  1135,     0,     0,  1445,  1155,
    1156,     0,  1159,  1162,  1166,  1160,  1192,  1519,  1195,  1207,
    1469,   201,     0,   222,   223,   219,     0,     0,   477,     0,
    1536,     0,  1501,   560,   561,     0,   584,  1501,  1549,   585,
     583,   416,  1483,   412,  1506,  1404,   440,   300,  1212,   706,
       0,     0,  1257,  1257,   723,   718,   717,   719,  1422,  1221,
    1430,     0,  1442,  1427,  1420,  1440,  1421,  1423,  1424,  1437,
    1438,  1425,  1419,   637,  1225,  1220,   746,   755,  1551,     0,
    1551,     0,   769,   770,     0,   774,   773,   775,  1189,  1190,
     785,   783,   637,   797,   798,  1254,  1256,  1214,  1214,  1214,
    1214,     0,   835,   836,     0,  1257,  1257,   832,  1216,   637,
    1221,  1331,  1221,  1331,   879,   885,   875,   903,   911,   913,
     920,   923,   924,  1491,   935,   916,   921,   970,  1385,  1386,
     970,     0,   953,   951,   952,   957,  1098,     0,  1523,  1092,
    1221,   995,   989,     0,   639,  1017,     0,     0,  1029,     0,
     637,   637,  1041,  1039,  1236,  1048,  1043,  1046,  1053,   637,
    1062,  1061,  1454,     0,     0,  1115,  1106,  1229,  1131,  1231,
       0,  1221,  1221,  1146,  1444,  1158,  1499,  1164,  1499,  1228,
       0,  1244,  1246,  1210,  1208,  1241,  1242,  1209,  1470,     0,
     220,   474,  1501,     0,   479,   484,  1515,   520,   540,   535,
    1473,     0,     0,  1501,  1517,  1501,     0,   490,   496,   497,
     498,   507,   499,   501,   504,   492,   493,   494,   500,   503,
     521,   505,   508,   495,     0,   502,   506,  1394,   575,  1392,
    1393,   591,   574,   586,   596,     0,  1501,  1501,   435,   732,
     731,   734,     0,   733,   747,  1431,  1223,   637,  1311,  1551,
    1314,  1551,   771,   786,   764,   637,   781,   827,   826,   825,
     824,   843,   842,   845,   844,  1219,   854,     0,   853,     0,
     637,   914,   908,   925,  1492,     0,   969,   961,   970,   972,
       0,     0,  1101,  1097,  1091,   983,   998,     0,     0,  1024,
    1501,  1031,     0,  1025,     0,  1028,  1238,  1240,   637,  1059,
     637,  1108,  1109,  1110,  1111,  1112,  1113,   637,  1132,  1123,
    1232,  1227,  1130,  1137,  1136,  1157,     0,  1499,  1161,     0,
    1168,  1180,  1177,  1179,  1178,  1173,  1176,   637,   637,  1211,
    1198,  1243,  1204,  1203,  1508,     0,  1501,  1501,   481,   519,
    1501,   541,   539,   536,   537,  1503,   529,  1501,  1261,     0,
       0,     0,     0,   522,     0,     0,   527,   530,   533,   594,
     592,   593,   595,     0,   589,   587,   588,   590,     0,   426,
     423,   424,     0,     0,  1508,  1226,  1310,  1313,   784,  1221,
    1221,   912,     0,   968,   973,     0,  1501,  1099,     0,     0,
    1089,  1093,   997,     0,     0,  1034,  1032,  1033,  1027,  1026,
    1054,  1063,  1230,   637,  1163,     0,  1167,  1169,  1153,  1245,
    1247,  1509,  1510,  1202,   476,     0,     0,  1501,   472,     0,
     528,     0,   525,  1457,   523,   524,   514,   512,   513,   515,
     511,   516,   510,   509,     0,   534,   532,   531,   573,   572,
     425,   419,   441,  1258,   856,   855,   926,   971,     0,  1102,
    1501,  1261,  1030,  1035,  1020,  1233,  1165,   478,   480,     0,
     518,   517,   538,     0,  1100,     0,  1018,   482,     0,  1103,
     526
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,     7,     8,    23,    38,    68,   126,
     243,     9,    24,    39,    69,    89,   472,    72,    70,    34,
      11,    20,    26,    41,    56,    57,    16,    36,    76,    96,
      97,   183,   184,   170,    98,   171,   172,   173,   174,   475,
     175,   176,    99,   179,   180,   181,   255,   100,   202,   203,
     204,   205,   436,   364,   497,   433,   434,   435,   206,   347,
     486,   487,   488,   769,   906,   489,   907,   207,   360,   361,
     492,   208,   421,   422,   209,   210,   211,   212,   213,   214,
     215,    47,    77,    79,   103,   101,   133,   366,   437,   515,
     516,   915,   776,  1113,   517,   911,   518,  1324,  1325,  1591,
    1120,   519,   520,   521,   522,   919,  1116,  1845,   523,   524,
     525,   526,   527,   528,   529,   530,   790,   136,   107,   108,
     109,   110,   143,   111,   371,   372,   441,   112,    30,    65,
     146,    83,   226,   151,   118,   152,   119,   156,   235,   318,
     319,   653,   320,  1355,   844,   542,   321,   456,   322,   659,
     323,   324,   654,   836,   837,   838,   839,   325,   326,   327,
      82,   227,   153,   154,   155,   233,   303,   447,   304,   384,
     385,   539,   831,   305,   538,   629,   630,   631,   952,   632,
     633,   634,   635,   636,   637,   942,  1334,  1634,  1635,  1791,
    1863,  2190,  2191,   638,   639,   821,   640,   641,   642,  1149,
     948,   949,  2058,   643,   644,   116,   294,   150,   377,   231,
     444,   534,   535,   536,   793,   934,   935,  1125,  1126,  1044,
     936,  1595,  1848,  2014,  2158,  2238,  1328,  1598,  1129,  1331,
    1850,  2035,  2036,  2253,  2037,  2038,  2039,  2040,  2244,  2041,
    2042,  2043,  2044,  2176,  2177,  2165,  2045,  2046,  2162,   464,
     298,   537,   590,   796,   797,   798,  1131,  1332,  1631,  2188,
    2183,  1632,    50,   242,   409,    86,   122,   121,   158,   159,
     160,   239,   332,   124,   334,   469,   470,   555,   556,   557,
     558,   559,   848,  1538,  1539,  1799,   560,   715,   716,   849,
     968,  1165,  1376,  1377,  1372,  1675,  1676,  1162,   717,   850,
     987,  1188,  1186,   718,   851,   995,  1407,   719,   852,  1457,
     720,   853,  1198,  1459,  1714,  1715,  1716,  1462,  1722,  1912,
    1910,  2075,  2074,   721,   854,  1008,   722,   855,  1009,  1465,
    1466,   723,   856,  1010,  1204,  1207,   724,   725,   726,   857,
    1731,   727,   858,   728,   859,  1017,  1477,  1750,  1751,  1215,
     729,   860,  1021,  1222,   730,   861,   731,   862,  1026,  1027,
    1228,  1229,  1230,  1500,  1498,  1763,  1231,  1491,  1492,  1762,
    1495,   732,   863,  1033,   733,   864,   734,   865,   735,  1039,
    1504,   736,   867,   737,   869,  1506,  1939,  2090,  2092,   738,
     870,  1239,  1515,  1770,  1941,  1942,  1943,  1945,   739,   871,
     740,   872,  1046,  1245,  1246,  1247,  1527,  1781,  1782,  1248,
    1524,  1525,  1526,  1775,  1249,  1952,  2205,   741,   873,   742,
     874,  1053,   743,   875,  1055,  1254,   744,   876,  1057,  1260,
    1537,  1962,   745,   877,  1060,  1263,  1798,  1061,  1062,  1063,
    1541,  1542,   746,   878,  1551,  1968,  2111,  2215,  2274,   747,
     879,   748,   880,  1973,   749,   881,  1552,  1976,   750,   751,
     882,  1074,  2118,  1280,  1554,  1979,  1815,  1816,  2120,  1278,
     752,   883,  1079,  1080,  1081,  1082,  1292,  1083,  1084,  1085,
    1086,   753,   884,  1050,  1956,  1250,  2104,  1529,  1784,  2102,
    2210,   754,   885,  1293,  1567,  1983,  1986,   755,  1092,  1296,
     756,   888,  1094,  1095,  1822,  2129,   757,   889,  1098,  1302,
     758,   891,   759,   892,   760,   893,   761,   894,  1307,   762,
     895,  1309,  1829,  1830,  1579,  1832,  1997,  2138,  1999,  2228,
     763,   764,   897,  2145,  1106,  1312,  1583,  1723,  1911,  1837,
     765,  1585,   766,   767,   899,  1273,  1839,  2099,  2003,  2150,
    1652,  1480,  1481,  1754,  1756,  1929,  1703,  1704,  1893,  1895,
    2067,  1988,  1989,  2127,  2131,  2223,  1806,  1807,  1970,  1808,
    1971,  2004,  2005,  2147,  2006,  2148,  1471,  1472,  1473,  1728,
    1474,  1729,  2061,  1041,  1042,   997,   998,  1193,  1194,  1438,
    1439,  1440,  1441,  1442,  1139,  1342,  1383,   988,  1011,  1208,
    1069,  1075,   374,   375,  1087,  1088,  1236,  1064,  1001,  1002,
     285,   458,  1122,   459,   263,  1035,  1036,   989,  1013,  1142,
    1380,  1685,  1783,  1947,  1019,  1065,  2048,   991,   970,   816,
     944,   945,  2050,   992,   833,   834,   993,  1171,  1173,  1387,
    1401,  1396,  1393,   234,  1831,  1319,  1191,  1271,  1984,   217,
    1210,   954,   369,   390,  1320,   252,  2009,  1760,   399,   225,
     648,  1166,   581,   161,   577,   278,   289,  2095,   139,   291,
     845,   548,    42,   430,   582,  2233,   544,   396,  1679,   958,
     221,  1788,   925,   177,  1212,   813,  1649,   269,   646,   657,
     496,   223,  1710,  1238,  1134,   572,   811,  1478
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1704
static const yytype_int16 yypact[] =
{
   -1704,   305,   416, -1704,  -113,   101,   416, -1704, -1704, -1704,
     514,   514,   634,   634, -1704,   575, -1704, -1704, -1704, -1704,
     838,   838,   434,   785,   785,   707,   461, -1704,   929,   906,
   -1704, -1704, -1704, -1704,   -80,   735,   896,   655,   836,   836,
   -1704,   681,   141,   715,   729,   833,   768, -1704,   189,  1091,
     917,  1107, -1704,   556, -1704, -1704,   944, -1704, -1704, -1704,
     815, -1704, -1704, -1704,   928,   880, -1704,    62, -1704,   365,
     514,   634, -1704, -1704, -1704, -1704,   882, -1704,  1100,   362,
     872,   936,  1087,   894, -1704, -1704,   999,   634, -1704, -1704,
   -1704,   890,   892,   898,   901,   903, -1704, -1704, -1704, -1704,
   -1704,   990,   905,  1135,  1282,   957,   578, -1704,    53, -1704,
   -1704, -1704, -1704, -1704,   909,  1008,  1138, -1704,   381,   934,
   -1704,    65,    65,   935,   927,   930,   785, -1704,   585,  1198,
      13,  1649,  1102, -1704, -1704,   938, -1704,  1109, -1704,   995,
   -1704, -1704, -1704,  1360, -1704, -1704, -1704, -1704,   939,  1040,
    1065, -1704,   894, -1704, -1704, -1704, -1704, -1704,   102, -1704,
     619,  -157,   132, -1704, -1704, -1704, -1704,  1026,  1182, -1704,
     399, -1704,   420, -1704, -1704, -1704, -1704,   143,   157, -1704,
     -44, -1704, -1704, -1704,   948,   713,  1293,   964,  1182,  1182,
     964,  1028,  1052,  1182,  1182,  1182,  1182,  1182,   964,  1182,
    1352,  1182, -1704,  1030, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704,   964,   990,   362,
   -1704,   977, -1704,  1333, -1704,  1247,   381,   934, -1704,   973,
    1074,  1077,   934,   644,   996,   828, -1704,  1182,  1060,  1150,
   -1704, -1704,  1323,   836,  1182,  1201, -1704,   432, -1704, -1704,
    1078, -1704,  1182,  1226, -1704,   665, -1704, -1704, -1704, -1704,
     993,  1194, -1704, -1704,   964,   964,  1182,  1182, -1704,  1182,
     977,  1371,   964,   964,   977,  1182,   977, -1704,   964,    70,
   -1704, -1704, -1704, -1704,   616,   977, -1704, -1704, -1704,   894,
   -1704,   894, -1704, -1704,   934, -1704,   997,  1090, -1704, -1704,
   -1704,   996, -1704,   998,   -20, -1704, -1704,  1333,  1182,   -47,
     -47,  1182,    14,  1200,  1182,  1424,  1180, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,   931,   168,
    1182, -1704,  1018,  1007, -1704,   917,  1201, -1704, -1704, -1704,
   -1704,   977, -1704, -1704, -1704, -1704, -1704,  1182, -1704, -1704,
     686,   977,  1225, -1704, -1704, -1704, -1704, -1704,   977, -1704,
   -1704,    87, -1704, -1704,   902, -1704, -1704, -1704, -1704,   977,
   -1704,   894, -1704,  1164,   894, -1704, -1704,   934, -1704,  1012,
    1013, -1704, -1704,  1379, -1704,  1385,  1201,  1036,  1182,  1424,
     977,   -65,   -76,  1201,  1046, -1704,  1182,  1039, -1704,  1039,
     -29, -1704, -1704, -1704, -1704, -1704,  1201, -1704, -1704, -1704,
     480,    22, -1704,  1092, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704,   686, -1704,  1082, -1704, -1704, -1704, -1704, -1704, -1704,
    1201, -1704, -1704,   902, -1704,  1103, -1704,   139, -1704, -1704,
    1201, -1704, -1704, -1704,  1169, -1704, -1704, -1704,    92,  1085,
   -1704, -1704, -1704,   977, -1704, -1704, -1704, -1704, -1704,  1254,
      72,  1294,  1058, -1704, -1704, -1704,  1182,  1182, -1704, -1704,
    2389,   634, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704,   743, -1704,    94,
   -1704,   686,  1201, -1704, -1704, -1704,  1182,   902, -1704,  1200,
    1185,  1104, -1704,  1149,  1200,  1182,  1453,   112,   394,  1201,
   -1704,  1083, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704,  1134, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704,  1182, -1704,  1039, -1704,  1169, -1704, -1704,  2948,  1488,
    1334,  1201,   205, -1704, -1704,  1201, -1704, -1704,  1159, -1704,
     100,   100,  2672, -1704,  1084, -1704, -1704, -1704, -1704,  1177,
    3425,  1088, -1704, -1704,   743, -1704, -1704,   964, -1704,  1182,
    1320, -1704,   915, -1704,  1182,   701, -1704,  1182, -1704,  1182,
   -1704,  1181,  1182,  1182,  1360,   128,  1182,  1112, -1704, -1704,
     996, -1704,  1328, -1704, -1704,   624,   629,   636,   663,   667,
    1120, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
    1212, -1704,  1201, -1704, -1704, -1704, -1704,   977,   977,  1343,
   -1704, -1704, -1704,   524, -1704, -1704, -1704,  1182,   490, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704,   932,    64, -1704,   103, -1704,
   -1704, -1704, -1704, -1704,    61,  1352, -1704,   525, -1704, -1704,
   -1704, -1704,  1449, -1704,  1335, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704,  1166, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704,  1104, -1704,  1891, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704,   419, -1704, -1704,  1268, -1704, -1704,
   -1704, -1704,   741, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,   851,
   -1704, -1704,    36,  1182, -1704, -1704,   265,   515,  1531, -1704,
   -1704,   -76,  1197, -1704,   977,   977, -1704,  1289,  1289,  1304,
   -1704,   977, -1704,   158,   -20, -1704, -1704,   996, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704,  1139, -1704, -1704,  1187, -1704,  1140,  1188, -1704, -1704,
   -1704, -1704,  1941,   118,  1558, -1704,  1231,  1231,   686,  1319,
    1319, -1704, -1704,  1137, -1704, -1704, -1704, -1704, -1704, -1704,
      39,  1421, -1704, -1704,  1085,  1201,  1146, -1704,  1147,   977,
    3761,  1161,   105,  2217, -1704, -1704,  4412,   894,  1199,  4440,
    4412,  1366,   790,   808,    59,   977, -1704, -1704,  1465, -1704,
      59,   977,  1432,   977,  3877,  4412, -1704,  2710,   894,   977,
     894,   977,    41,    80,   977,   894, -1704, -1704,  3938,  4058,
   -1704, -1704,   977,   977,   894,   977, -1704,  1010,  1496,   977,
   -1704, -1704, -1704, -1704, -1704, -1704,  1584, -1704, -1704, -1704,
   -1704, -1704,   977,    -2,    18,   144,  1171, -1704,  1171, -1704,
   -1704, -1704,  -155, -1704, -1704, -1704, -1704, -1704,   977,  1182,
    1433,  1433,   490, -1704, -1704, -1704, -1704,  1422, -1704, -1704,
   -1704,  1201,  1210,  2428,  1157, -1704,   977, -1704,   118, -1704,
    1215,  1380, -1704,  1453, -1704, -1704, -1704, -1704,   977,   977,
     686,   -76,   -76,  1581,  1352, -1704, -1704, -1704,  1489,   660,
   -1704,  1319,  1167,   977,  1174,  1175,  1319,   616,  1176,  1178,
    1179,  1184,  1189,  1190,  1191,  1203,  1174,  1494, -1704,  3996,
   -1704, -1704, -1704, -1704,  1429, -1704,  1575, -1704, -1704, -1704,
    1239, -1704,   616, -1704, -1704,  1211, -1704, -1704,   210,   894,
    1511,  1114, -1704,  1303,  1339,   894,   849,  1527,  2003,   860,
     877,  1529,   551,  1211, -1704, -1704,    67, -1704, -1704, -1704,
    1563, -1704, -1704, -1704,  1319,    59, -1704, -1704, -1704, -1704,
   -1704,  1271, -1704,    52,   977, -1704,   201, -1704, -1704, -1704,
   -1704, -1704,  4412, -1704,  1269,  1532,  1619,   759, -1704,  1276,
   -1704,  4950,  1537,   730,  1280,  1283,   529,  1287,   764,  1503,
   -1704,  1339,  1503,   977,  1540,  1253, -1704,   853, -1704, -1704,
   -1704, -1704, -1704,  1440, -1704,    59, -1704,    -4, -1704,    74,
   -1704, -1704,     7,  1634,  3464, -1704, -1704,   977,  1541,  4107,
     977,  1510,   895,  1578, -1704,  1362,  1316,  1109,  1503,   851,
     281, -1704, -1704, -1704, -1704,   545, -1704, -1704,  1182, -1704,
   -1704, -1704, -1704,   210, -1704, -1704,   977, -1704,  1201,   996,
   -1704, -1704, -1704, -1704,  1580,  1319,  2428,  2428,  2428,    28,
     920, -1704, -1704, -1704,  1137, -1704,  2428, -1704, -1704,  1120,
   -1704,   118, -1704, -1704, -1704, -1704, -1704, -1704,  1254,   -76,
    1583, -1704, -1704,   853,   631,  1259,   129,   -45,  2428,  1299,
    2428, -1704,  2428, -1704,  2276,  1263,  2428,  2428,  2428,  2428,
    2428,  2428,  2428,  2428, -1704, -1704, -1704,  4412,  1515, -1704,
   -1704,  1367,  1429,  1206,  3201,  1398,  1472, -1704,   392, -1704,
   -1704, -1704,   910, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704,   607,   894, -1704, -1704,   479,  1543,  1543,  1543,
    1543, -1704, -1704,  4412,  4412, -1704, -1704,    75,  1573,   784,
   -1704,  1275,   790, -1704,   977, -1704,    20, -1704, -1704,   761,
    1539, -1704,   853,   153, -1704,   201, -1704, -1704, -1704, -1704,
      79,  1312,    59, -1704, -1704,  4412, -1704, -1704, -1704, -1704,
    1350, -1704, -1704, -1704, -1704,   977,   105, -1704,  1072, -1704,
   -1704,  1339,   210, -1704,  1504,   -24,   678, -1704, -1704,   977,
     678,  1315, -1704,  1137, -1704, -1704,    77,   902, -1704, -1704,
    2156, -1704,  1663,  1500,  4412,  4412, -1704,  4174,   977, -1704,
    1542, -1704, -1704,  4412,   853, -1704, -1704, -1704,  1634,  1509,
     977, -1704,   991,    73,   -24, -1704, -1704,  1597, -1704, -1704,
   -1704,  1444, -1704, -1704,   977,   977, -1704,   977,  1530,  1029,
      89, -1704,  4721,  1109, -1704,  2276,  1274,  1274,   787, -1704,
   -1704, -1704,  2428,  2428,  2428,  2428,  2428,  2428,  4638,   920,
    1363, -1704, -1704,  1254,  1109, -1704, -1704, -1704,  1543, -1704,
   -1704,  1285,  1284, -1704,   853,  1543,  1512, -1704, -1704, -1704,
   -1704,  1701,  1543,  1462,  1462,  1462,   170,  1501, -1704, -1704,
     300, -1704,    96,  1079,   977,  1045,   106,  1278, -1704,  1137,
   -1704, -1704,   171,  1281,   960,   275,  1286,  1061,   108,   178,
     799,  1290,  1098,  4351,    10,  4412,    59, -1704,  1395, -1704,
   -1704, -1704, -1704, -1704,  1104, -1704, -1704,  1340, -1704, -1704,
    1340, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704,  1337,   105, -1704,   111,
     977,   977,   518, -1704, -1704, -1704,    17,    30,  1370, -1704,
   -1704,  1613, -1704,  1483, -1704,   155,  1914,  1543,  1486, -1704,
   -1704,  1487, -1704, -1704, -1704,  1566,  4351,   457, -1704, -1704,
   -1704,  3066, -1704,  1357, -1704, -1704, -1704, -1704, -1704,    75,
   -1704, -1704, -1704,  1109, -1704, -1704, -1704,  1104, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704,  1427,  1104, -1704,  1356, -1704,
    1704, -1704, -1704, -1704,   777, -1704,   853,   873, -1704,   143,
     553,   852,    59,    59,  4351,   465,  1083,   894,  1620, -1704,
   -1704,  1748, -1704,  1585, -1704, -1704, -1704, -1704,  1504, -1704,
     977,   571,   607,   885,  1327,  1636, -1704,  1330,   853,   795,
   -1704,   300, -1704, -1704, -1704,  4412,  1182,   607, -1704, -1704,
   -1704, -1704,   -70,   977,  4351,   469,  1368,  1753,   977,   410,
   -1704, -1704, -1704,  1463,  1464, -1704, -1704,  1072, -1704,   147,
     675, -1704, -1704, -1704,  1182,  1596, -1704, -1704,  1201, -1704,
   -1704, -1704,  1182, -1704, -1704, -1704, -1704,  1462,  1113,  1182,
    2217, -1704, -1704,  1462, -1704,  1201, -1704, -1704, -1704, -1704,
   -1704,   977, -1704,   977, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704,   977,  1570,   852, -1704,  1137, -1704, -1704,
    1079,   791,   791,  1274,  1274,  1274, -1704,  1117, -1704,  1104,
   -1704,   977, -1704,  1487, -1704, -1704,  1543, -1704, -1704, -1704,
    1182, -1704, -1704,  1182, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704,    -3, -1704, -1704, -1704,  1701, -1704, -1704, -1704,   210,
     210,   210, -1704, -1704, -1704, -1704, -1704,  1174,  1303,  4920,
   -1704,   977,  1174,  1174,  2428, -1704,  1174,  1174,  1174,   342,
    1174,  1174, -1704, -1704,  1508,  4351, -1704,    59, -1704, -1704,
      44,    51, -1704, -1704,  3700, -1704,   567,   115, -1704, -1704,
   -1704, -1704,  1014, -1704,  1448, -1704,  1434, -1704, -1704, -1704,
   -1704, -1704, -1704,   348,   348,   348,   348,  1182, -1704, -1704,
   -1704, -1704,  1151,  1182, -1704, -1704, -1704, -1704,     5, -1704,
    1914, -1704, -1704, -1704, -1704, -1704, -1704,  4412, -1704,  4412,
      75, -1704, -1704, -1704,  3066, -1704,   977,  1650,  1346,   937,
    1667,  1349,   120,   853, -1704, -1704,  1728, -1704, -1704, -1704,
   -1704,   873, -1704,  1606, -1704,  1182,  1502, -1704, -1704, -1704,
   -1704,  1320,    59, -1704,  4412,   128,   401, -1704, -1704, -1704,
     977,  4412,   855, -1704, -1704, -1704,  1641,  1525, -1704,  1643,
   -1704,  1549, -1704, -1704, -1704, -1704,  1330, -1704, -1704, -1704,
    1533,  1645,  1505,  1491,  1303, -1704,  4412,   120, -1704,  1513,
   -1704,   853, -1704,  1679,  1404, -1704, -1704,  1109, -1704,    68,
    1785, -1704,   992, -1704, -1704, -1704,  1201,  1682,  1586,  1730,
    4847,   -46,  1182, -1704, -1704,   -46, -1704,  1182,  1210, -1704,
   -1704, -1704,  1634, -1704,  1320, -1704,  1402, -1704, -1704, -1704,
     -46,   -46,     3,     3, -1704, -1704, -1704, -1704, -1704,  1370,
   -1704,  1131, -1704, -1704, -1704,  1079, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,  1104,  1647,
    1104,  1648, -1704, -1704,  4412, -1704, -1704, -1704, -1704, -1704,
    1678, -1704, -1704, -1704, -1704, -1704, -1704,  1543,  1543,  1543,
    1543,   -46, -1704, -1704,   -46,     3,     3, -1704, -1704, -1704,
    4351,  1485,  4351,  1493, -1704, -1704, -1704, -1704, -1704,  1674,
   -1704,   937, -1704,  1710, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704,   120,  1072, -1704, -1704,  1072,   -61,   977, -1704, -1704,
    4351, -1704, -1704,   900,  3674, -1704,  1761,  1582,  1601,   504,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704,   977,  1136, -1704, -1704, -1704,  1675,  1559,
     977,  1370,  4351, -1704,  1753, -1704,  1294,  1725,  1294,  1505,
     408, -1704, -1704,  1676, -1704,  1565, -1704, -1704, -1704,   510,
   -1704, -1704,  1182,  1733,  1603, -1704,  1048, -1704,  1625,  1051,
    1424,  1637,  1396,  1182,  1319,  1182,   977, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,  1445,
   -1704, -1704, -1704, -1704,   830, -1704, -1704, -1704, -1704, -1704,
   -1704,   380, -1704,   534, -1704,  1397,  1182,  1182, -1704, -1704,
   -1704, -1704,   -46, -1704, -1704, -1704, -1704, -1704, -1704,  1104,
   -1704,  1104, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704,  4412, -1704,  4412,
   -1704, -1704, -1704, -1704, -1704,  1780,  1072,  1072, -1704,  1431,
    1534,   894,   508, -1704,   977, -1704, -1704,  1499,  4412, -1704,
    1182,   599,  1599, -1704,  1604, -1704, -1704, -1704, -1704, -1704,
   -1704,   977, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704,   977,  1294, -1704,   977,
    1696, -1704, -1704, -1704, -1704, -1704,   894, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704,  1081,  1201,  1182,  1182,  1670, -1704,
    1182, -1704, -1704, -1704, -1704,   490, -1704,  1182, -1704,   977,
     977,  1043,  1666, -1704,  1557,  1201,   830, -1704, -1704, -1704,
   -1704, -1704, -1704,   -46, -1704, -1704, -1704, -1704,   -46, -1704,
    1397, -1704,   977,   118,  1081, -1704, -1704, -1704, -1704,  1370,
    1370, -1704,  4412,  1072, -1704,  4412,  1182,   894,   894,  1544,
   -1704, -1704, -1704,  1436,   977,  1709, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704,   977, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704,  1201,  1201,  1182, -1704,  1201,
   -1704,  1201, -1704,  1303, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704,  4412, -1704, -1704, -1704, -1704, -1704,
   -1704,   977, -1704, -1704, -1704, -1704, -1704, -1704,   105,   894,
    1182, -1704,   977, -1704, -1704, -1704, -1704, -1704, -1704,  1201,
   -1704, -1704, -1704,  1799, -1704,   105, -1704, -1704,  4412, -1704,
   -1704
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1704, -1704, -1704, -1704,  1843, -1704, -1704, -1704,    21, -1704,
   -1704, -1704, -1704, -1704,  1517, -1704, -1704, -1704,  1195, -1704,
   -1704,    34,  1832, -1704, -1704,  1801,   226, -1704, -1704, -1704,
   -1704, -1704,  1672,  1729, -1704, -1704,  1690,   739, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704,  1681, -1704, -1704, -1704, -1704,
    1659, -1704, -1704, -1704, -1704, -1704,   445,   577, -1704, -1704,
   -1704, -1704,  1378, -1704, -1704,  1305,   758, -1704, -1704, -1704,
   -1704, -1704, -1704,  1447, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704,  1736, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704,   557, -1704,   546,
     767, -1704, -1704, -1704, -1704, -1704,   961,    40, -1704,  1306,
   -1704, -1704, -1704, -1704, -1704, -1704,    88, -1704,  1665, -1704,
    1787, -1704, -1704, -1704, -1704,  1522, -1704, -1704,   610, -1704,
   -1704, -1704, -1704,  1673, -1704,  1850,  1749, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704,  1059, -1704, -1704, -1704,  1351,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704,   716, -1704, -1704, -1704,  1605, -1704,  -545,  -745,
   -1704, -1704, -1704,  -270, -1704, -1704, -1704, -1704, -1704, -1704,
   -1276, -1260,  1086, -1259,    54, -1704, -1704, -1704, -1704,   270,
   -1704, -1704,  -283, -1258, -1704, -1704, -1256, -1704, -1251, -1704,
   -1704,   962, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704,  1374, -1704, -1704, -1704,   980, -1704,  -882,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704,  -127, -1704, -1704,
   -1704, -1704, -1704, -1704,  -262, -1704, -1704, -1704, -1704,   254,
   -1704, -1704, -1704, -1704, -1704,  1118, -1704, -1704, -1704, -1704,
   -1704, -1704,   330, -1704, -1704, -1704, -1704, -1704,  1794,  1042,
   -1704,   203, -1704, -1704, -1704, -1704,  1452, -1704, -1704, -1704,
   -1704, -1704, -1704,  -591, -1704, -1704,   124, -1704, -1704, -1704,
   -1704,   899,   547,   549, -1704, -1704,   259, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704,   912, -1704, -1704,   222, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704,  -409, -1704,   188, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,   708,
   -1704, -1704,   710, -1704, -1704, -1704, -1704,   442,   182, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704,     4,   705, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704,   703, -1704, -1704, -1704,   165, -1704,
   -1704,   425, -1704, -1704, -1704, -1572, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1354,   891, -1704,
   -1704,   154, -1704, -1704,   405, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704,   641, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704,   676, -1704,   145, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,   874, -1704,
     878, -1704, -1704,  1080, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704,   868,   386, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704,   -28, -1704,   388, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704, -1704, -1704, -1704,  -830, -1704, -1142, -1704, -1704,
   -1112, -1100, -1103, -1704,   315, -1704, -1362, -1704, -1704, -1704,
   -1704,   -30, -1704, -1704, -1704, -1704,  -141, -1704, -1704,   164,
   -1704, -1704, -1704, -1704,   -31, -1704,  -515, -1703, -1704, -1704,
     502, -1704,  -851, -1250,  -831, -1163, -1704, -1704, -1704, -1179,
   -1177, -1171, -1169, -1161,    78,  -202,  -864,  -177, -1120,  -838,
     149,   904, -1002,   -83, -1704, -1071, -1704,  -811, -1704,   780,
    -387,  -182, -1704,  -527,   693,  -822, -1000,   -90,  -672, -1704,
   -1704,   424, -1017, -1203,  -968,  -816,  -888,   750,  -598,  -219,
   -1704,  1047,  -150,  -641,  -495,  -296,  -276,  -933, -1704, -1704,
   -1704, -1704, -1704,  1762, -1704,   397,   804, -1704, -1704, -1704,
   -1650,  1170,  -751,  1688,   749,  -425, -1704,   975,  -384,  1419,
   -1704,  -610, -1704, -1069,  1053,  -414,   805, -1704, -1704,  -676,
   -1704, -1122,  -167,  -622,  -499,  -190,  -991,   614, -1312,  -819,
   -1065, -1704,  1219,  1955,  -901, -1704, -1704, -1704, -1704, -1704,
   -1704, -1704,   593, -1704,   166,  -675,   879,  -126
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1556
static const yytype_int16 yytable[] =
{
     120,   245,   287,   453,   186,   452,   823,   832,   866,   583,
    1100,   959,   531,  1213,  1540,  1450,  1288,  1451,  1012,   815,
     996,   264,   265,  1452,  1297,  1453,   270,   271,   272,   273,
     274,  1028,   276,  1454,   279,  1235,   898,  1005,  1879,   286,
    1200,  1000,  1313,  1235,   840,   794,   546,    21,  1043,   938,
    1073,   287,   157,  1184,   423,   287,  1625,   287,  1034,   186,
    1281,  1089,  1680,  1681,  1493,  1034,   287,  1403,   328,   120,
     329,   773,  1626,  1627,  1628,   104,  1629,   336,   473,  1140,
    1034,  1630,  1584,  1034,  1226,   341,  1034,   961,   353,  1235,
      88,   835,   357,  1370,   359,   338,  1488,  1339,   288,   350,
     351,  1378,   352,   370,  1486,    91,  1727, -1519,   358, -1479,
     427,   563,   828,  -188,   157,  1872,    84, -1555,  1482,  1483,
    1484,   125,   287,  1925,  1758,   423,  1547,   828,   277,   828,
      40,  1503,   287,  -189,   178,  1534,  2007,   787,   466,   287,
     498,   387,  2100,   499,   392,   394,  1356,   397,   382,   578,
     438,   157,  1167,   829,   457,  1326,   908,  1174,   500,   412,
     157,   240,  1519,   406,   363,  1339,   253,  1352,   501,   424,
    1274,   287,  1793,   287,  1991,  1339,   426,  1339,   990,   405,
     413,   157,   950,  1574,   337,  1531,   411,   990,  1022,   290,
    1294, -1519,  1289,  -749,  1373,   565, -1483,  1898,  1316,   403,
    1905,   250,  1054,  1056,  1900,   250,   373,   454,   286,  1520,
   -1555,  1955,  1825,    53,  1118,  1234,  1096,   990,   929,  2001,
   -1555,   451,   579, -1555,    40,  1518,  1175,  1077,  -188,   462,
   -1555,  1048, -1555, -1483,   287,  1373,   449,    17,  1078,  1577,
    1339,   842,  1275,   460,  1327,   930,   931,  1339,  -189,  1733,
     999,  1196,   794,  1657,   920,  1653,   468,   382,  1379,  1111,
    1677,   651,  1653,  1286,  1725,   388,  1316,   389,  1633,  1653,
     241,   370,  1336,  1337,  1338,   404, -1501,  1469,  1314,  -206,
     493,   540,  1349,   826,  1726,  1705,  1235,  1576,   373,  1651,
     532,   442,  1242,  1119,   414,  1852,    90,   428,   105,   550,
     551,  1857,    40,   999,  1549,     3,  1385,   950,   455,   414,
    1128,   414,  1392,  1394,  1395,  1397,  1335,  1189,  1400,  1402,
     795,  1899,  1078,  1521,   830,  2002,   580,  1470,  1901,   567,
     658,   660,   660,   415,    12,   999,  1493,   502,   575, -1495,
     416,  1295,   566,  1896,  1339,   909,  1189,  1656,   415,  1012,
     415,  1209,   220,  1159,    62,   416,  1374,   416,   284,   584,
    1154,  1155,  1650,   182,   587,  2101,   503,   -31,    40,    51,
    1548,   645,  1522,   504,  1112,  2096,  1468,  1752,  2097,   913,
    1251,  1340,   788, -1483,   104,   585,  1012,   254,   284,   284,
    1717,   650,  1287,   910,  2047,   655,   106,  1078,   337,   817,
    1316,  1028,   772,   256,  1736,   467,  1706,   777,  2217,   182,
     781,   417,   782,  1873,   383,   784,   785,  1012,   505,   791,
   -1483,  1926,  1096,  1375,   506,  1505,   417,  1189,   417, -1483,
    1533,    88,  -188,  1906,  1157,  1158,  -605, -1483,  1766,   789,
    1199,   962, -1501, -1483,   932,  1840,   182,   169,  1144,  1340,
   -1483,   507,  -189,  1734,   284,  1544,    54,   474,   508,  1340,
     822,  1340,   814, -1479,  1375,  1012,  -603,   827,   545, -1481,
    1290,   509,  1489,  1559,   418,   284,  1490,  1341,  1640,  1641,
    1642,  1643,  1644,  1645,  1647,   182,   284,   564,    85,   418,
    1291,   418, -1483,   284,   182,   251,   510,  1227,   511,   251,
     144,    87,  1586,   419,   262,   561,   512,   284,   284,  1776,
    1351,   284,  1317,   427,   284,  1404,  -211,  2064,   419,   652,
     419,   262,  1455,  1599,  1340,  1243,  2203,   795,   841, -1483,
    1684,  1340,   956,  1235,   284,  1796,    63,   513, -1483,   284,
      55,  1817,  1907,   420,  1869,  1687,    62,   916,    13,  -605,
    1160,  1485,  1487,  1653,   284, -1435,  1523,  1697,   420, -1483,
     420,  1889,   287,   914,  1980,   287,   287,  1012,  2086,  1381,
    2088,  2141,   287,   335,  2028,  1460,  1388,  1007,   284,  -603,
    1317,   284,  1283,  1535,  1330,  1600,   514,    64,  1244,  1735,
    2029,  2030,  2032,  2282,  2033,     4,  1049,  1493,  2105,  2034,
    1223,  1007,   922,   923, -1506,   933,   912,   105,   580,   928,
   -1555,  2142,  1343,  1344,  1345,  1346,   471,  1347,  1564,  2143,
   -1441,  2179,  1568,  1569,  1993,  1571,   937,  1698,  1340,  2133,
    2134,  1575,  1353,  1003,    31, -1555,  1502,  1930,   167,  1932,
    1759,  1144,  1144,  1144,   284,  1717,  1713, -1526,  1794,   886,
    1118,  1144,  1826,   465,  1051, -1555,  1357,  1358,  1066,   167,
    1070,    15,  1070,  1076,  1156,  1051,  1555,  1145,  1283,     5,
    1555,   167,  2180,  1144,  1960,  1144,   917,  1144,  1720,  1389,
    1070,  1144,  1144,  1144,  1144,  1144,  1144,  1144,  1144,  2144,
    1163,  2208,    22,   287,  1804,   965,  1114,  1359,  2112,  1360,
     428,   843,    74, -1555,  2160,   106,  1992,  1897,   835,   287,
    1792,  1875,  1876,  1877,  1317,  -206,  1343,  1344,  1345,  1346,
       5,  1347,  1804,    74, -1439, -1479,  1461,  1148,    63,  1119,
    1110,  1361,  1362,  1363,   284,    74,   166,  1636,  2113,  1708,
     337, -1555,   287,   287,   819,  1890,  1121,  1283,  2098,  1786,
     168,  1067,  1078,   918,  1878, -1497,  1950,  1224,  2114,  1883,
    1884,   887,  1123,  1886,  1887,  1888,  1141,  1891,  1892,  1018,
    1507,   168,  2000,  1508,  1014,  2184,  1509,  1510,  1364,  1321,
    1365,  1476,  1686,   168,     5,  1007,  1519,   588,  1366,  2209,
    1724,  1132,  1235,  2055,  1856,  1068,  2152,  1071,  1209,  1099,
    1721, -1479,  1091,  2062,  2062,  2122,  1209,  2123,  1469,  1283,
    1209,  1102,   367,  2124,  1995,  2125,  1469,  2077,  2078,  2079,
    2080,  2181,  2182,  2126,   167,  1881,  2185,  1805, -1506,   306,
    1885,  1787,  1768,  1520,   182,   117,  1164,  2264,  2265,  1903,
    1637,  1771,   117,   182,   284, -1495,   246,  1144,  1144,  1144,
    1144,  1144,  1144,  1144,  1076,  1805,  2062,  2062,  1470,  1367,
    1145,  1145,  1145,   820,    18,    25,  1470,   248,  1339,  1283,
    1145,    54,   343,  1078,  2136,   307,  2139,   414,   494,   339,
    1789,    28,  1777,   266,    29,  1322,   368, -1479,    74,   308,
     140,   275,  1145,  1819,  1145,   344,  1145,  1475,  1390,   502,
    1145,  1145,  1145,  1145,  1145,  1145,  1145,  1145,    33,  1765,
     282,   249,  1476,   290,  2284,  1767,   415,  1240,  2242,  1931,
    1842,  1933,  1256,   416, -1396,   896,  1202,   309,   503,  1778,
    1935,  2289,   237,  2115,   477,  1067,   168,    32,  2153,    19,
     287, -1526,   568,   293,   284,   141,   142,  1521,   299,  1508,
    2047,  1323,  1509,  1510, -1479,    55,  1012,   348,   349,  1141,
    1141,  1141,  1257,  1686,  1790,   355,   356,  2052,  -963,  1141,
    1258,   362,   365,   478,  1866,  2186,  2187,   238,  1329,   943,
     479,  1978,  2059,  2060,   237,   800,   249,  1843,  1012,  1844,
     802,  1141, -1501,  1141,   417,  1141,  1522,   804,  2146,  1141,
    1141,  1141,  1141,  1141,  1141,  1141,  1141,  -963,  1511,  1512,
     376,    35, -1501,   778,  -963,  2225,  1269,  1003,  1104,   169,
     779,  2286,  2063,    37,   806,  1368,  1513,  1514,   808,   238,
    1072,  1283,  1283,  2081,   801,   774,  2082,  1809,    40,   803,
    1259,   187,   900,   310,   414,  1105,   805,  1003,  1108, -1555,
    1967,   481,  1821,   311,   429,   188,   189,   418,   510,  1638,
     337,  1270,    44,  1283,   414,  1369,  1145,  1145,  1145,  1145,
    1145,  1145,  1145,   807,  2083,  2084,  1467,   809, -1443,   775,
    1545,   901,  2174,   415,    43,  -963,   419,   190,   902, -1555,
     416,   300,  1779,   443,  1003,   401,   824,  1029,  1030,  2207,
      45,  2121,    48,   415,  1785,   287,   287,  1546,    46, -1555,
     416,  1031,   386,   569,   482,   402,   825,   393,   574,  1810,
     971,  2154,  2175,   828,   191,   192,   420,   193,    52,  1966,
     442,  1949,  2246,  2247,  2106,   194,    49,  1915,  1916,  1811,
     312,   313,  1592,  1592, -1555,  1264,   182,  1581,  -963,  1553,
      92,  1582,  1340,   314,  2107,   315,  2248,  1032,  1265,   903,
     259,   417,    58,  1928, -1555,  1141,  1141,  1141,  1141,  1141,
    1141,  1141,  1936,   431,  2194,   432,    59,  -963,   195,   196,
    1523,   417,    60,   485,  1511,  1512,  1949,  1024,  1553,   197,
    1691,  1025,  1562,  1694,  1144,   972,  1563,    10,  1699,  1144,
     236,    10,  1513,  1514,   236,  2170,  2269,  1305,    67,  1306,
     974,  -963,    93,   476,  1227,    61,  1496,  -963,  1409,  1410,
    1411,     5,   904,  2068,   418,  2070,  1412,  1463,  1343,  1344,
    1345,  1346,  2072,  1347,  1345,  1346,  1639,  1347,  1003,    71,
    1343,  1344,  1345,  1346,   418,  1347,  1382,    74, -1436,  2199,
    1386,  2200,    94,   419,    95,   316,  1596,  1597,  1398,  1399,
     771,   198,    78,  1853,  1413,  1854,   102,  1205, -1388, -1388,
   -1388, -1388,  1908,   419,  1909,   317,  1780,    80,  1283,  1217,
    1218,  1219,  1220,   477, -1555,   114,  1283,   284,   182,  1414,
    1415,   905,  1959,   420,   975,  2258, -1387, -1387, -1387, -1387,
    2259,  1922,  2066,  1923,  1843,   414,  1844,   284,  2231,  2232,
    1949,  1678,  2159,   420,  2163,  2164,    81,  1416,  1464,   113,
     115,  2076,   478,  1417,  1917,  1918,  1919,  1920,   117,   479,
    2249,  2250,  2272,   123,  1007,   976,  1283,   127,  2085,   128,
     977,   480,   132,   182,   415,   129,   978,   135,   130,   979,
     131,   416,   134,   137,  1419,   138,   147,   148,  1420,  1414,
    1415,  1343,  1344,  1345,  1346,  2056,  1347,   149,  -331,   163,
     287,  2251,  2252,  1348,   164,   199,   178,   165,   216,  2116,
    2117,   980,   220,   222,   224,   219,   228,  1416,  2119,   229,
     230,   244,    40,  1417,  2196,   258,  2197,   261,   262,  1820,
     481,  1343,  1344,  1345,  1346,   267,  1347,  1592,   277,  1693,
    1795,   284,   268,  1145,   287,   200,  1418,   288,  1145,   290,
     295,   297,   417,   296,  1419,   330,   331,  1846,  1420,   333,
     302,   337,   287,   342,   340,  1851,  2213,   346,   354,   379,
     345,   828,  1855,   395,   378,   381,  1823,   398,  1849,   981,
     400,  1861,   407,  1823,   408,   425,  1421,  1422,   440,   445,
     446,  1423,  -343,   482,   201,  1858,   483,   484,   448,  1867,
     450,  1424,   287,   463,   461,   491,  2195,   280,  1425,   533,
     495,   541,   543,  1426,  2198,   418,  1343,  1344,  1345,  1346,
     547,  1347,   549,  1870,   982,   983,  1871,   570,  1689,  2201,
     571,  1427,  1343,  1344,  1345,  1346,   573,  1347,   576,  1882,
    1696,   586,  1141,   972,   419,   647,   182,  1141,   649,   984,
    1343,  1344,  1345,  1346,   656,  1347,   664,  2220,   974,  2221,
    2266,   663,   485,  2267,   580,   768,  2222,   985,   783,  1343,
    1344,  1345,  1346,  2240,  1347,   986,   792,  1701,   284,   799,
     810,   812,  2262,   818,   420,   846,  2229,  2230,  1343,  1344,
    1345,  1346,  1206,  1347,  -815,   847,  1865,   890,   578,   924,
    1921,   921,  1343,  1344,  1345,  1346,  1924,  1347,   927,   940,
    2065,   946,  2283,   941,  1434,   951,   953,  1436,  1437,   957,
     943,   960,   963,   966,   967,   994,  1023,  1015,  1040,   969,
    1107,  1109,  1124,  1006,  1115,  1133,  1130,  1146,  1151,  1020,
    1152,   835,   975,  1161,  1037,  1038,  2290,  1168,  1957,  1185,
    1037,  1045,  1047,   414,  1170,  1172,  1176,  1006,  1177,  1178,
    1190,  1192,  2275,  1037,  1179,  1195,  2166,  1197,  1203,  1180,
    1181,  1182,  1045,  1101,  1209,  1103,  1428,  1429,  1430,  1431,
    1432,  1211,  1433,  1183,  1434,  1435,  1214,  1436,  1437,  1221,
     187,  1233,   415,  1237,   978,  1252,  1253,   979,  1255,   416,
    1963, -1390,  1262,  1266,   188,   189,  1969,  1268,  1267,  1272,
    1277,  1279,  1078,   157,  1301,  2051,  1304,  1308,  1310,  1311,
    2053,  1333,  1371,  1143,  1354,  1384,  2011,  1391,  1405,   980,
    1456,  1406,   999,  1479,  1494,  1499,   190,  1517,  1532,  1536,
    1550,  1558,  1565,   442,  1566,  1578,  1588,  1590,  1573,  1594,
    1347,  1648,  1655,  1169,  1654,  1678,  1658,  1690,  1374,  1707,
    1692,  1709,  1659,  1712,  1660,  1695,  1702,  1661,   287,  1700,
     417,  1730,  1470,   191,   192,  1755,   193,  1662,  1753,  1757,
    1761,  1769,  1772,  1773,   194,  1797,  1800,  1812,  1201,  1813,
    1814,  1801,  1828,  1836,  1827,  1838,  1847,   981,  1862,  1894,
    1913,  1914,  1938,  1940,  1944,  2103,  1946,  1951,  1954,  1972,
    1958,  1805,  1975,  1977,  1990,  1037,  1985,  1987,  1982,  1996,
    1994,  1998,  2008,  1037,  1241,  2012,  2015,   195,   196,  2057,
    2069,  2071,  2013,   418,  2073,  2261,  2087,  2091,   197,  2094,
    2108,  1006,   982,   983,  2089,  2110,  2109,  2128,  2137,  2130,
    2157,  2149,  2002,  2156,  2161,  2167,  2168,  1282,  2024,  2202,
    2204,  2189,   419,  2218,  2206,  1037,  2212,   984,  2219,  1037,
    2227,  2237,  2254,  2255,  2270,  2155,  2273,  1300,  2288,    14,
    1241,  2271,   410,    27,    73,   985,  2169,   260,  2171,   185,
     247,   257,   281,   986,  1560,   562,   284,  1315,   490,   770,
     218,  1593,   420,  1201,  1663,  1589,  1045,  1318,  1664,  1117,
     198,   780,  2010,  1961,   283,  2211,  1143,  1143,  1143,  2192,
    2193,  1665,   868,   439,  2178,   145,  1143,  -906,    66,   292,
    -906,   232,   661,   964,  2031,  1864,   380,  2260,   947,   589,
    1150,  1127,  2173,  1282,  2257,   939,   162,  1216,  1143,  1904,
    1143,   552,  1143,  1964,  1683,  1682,  1143,  1143,  1143,  1143,
    1143,  1143,  1143,  1143,  1874,  1225,  1902,  1666,  1927,  1497,
    1501,  1764,  1934,  2214,  1516,  2093,  1953,  1737,  1528,  1774,
    1738,   287,  1261,  1802,  1965,  1587,  1557,  1284,  1739,  1740,
    1741,  1981,  1299,  1285,  1090,  1834,  2135,  1835,  1868,  2140,
    2216,  1974,  -906,   287,  2151,  1732,  1458,  1276,   594,   595,
     596,   597,   598,   599,  1667,  1818,  1841,  -906,  2245,  2235,
    2236,  1147,  1282,  2239,   199,   301,  1408,   955,   391,  1530,
    2241,  1232,  1037,   786,  2263,  2234,  1153,   926,  1668,   971,
     286,    75,   828,  1711,   601,  1543,   602,   603,   604,   605,
     606,   607,  1201,     0,  2054,  2256,  2178,     0,  1350,  1556,
       0,     0,  1669,  1163,   200,     0,  1037,  1670,     0,  2268,
       0,     0,   287,     0,  -906,  -906,     0,  1671,  1572,  1003,
       0,  1672,     0,     0,  1282,     0,   608,     0,     0,     0,
    1580,     0,     0,   442,     0,     0,  1003,     0, -1479,  1742,
    2279,  -906,  -906,     0,     0,     0,     0,  1241,  -906,   370,
       0,     0,  -906,   201,   972,  2277,  2278,  1743,     0,  2280,
       0,  2281,  1143,  1143,  1143,  1143,  1143,  1143,  1143,   974,
       0,  -906,     0,  2285,  1744,     0,     0,     0,  1673,  -906,
       0,     0,  -906,  -906,  1282,     0,     0,  -906,  1674,     0,
       0,  -906,     0,  -906,   442,     0,  -906,     0,  -906,  2287,
       0,     0,     0,     0,  1688,     0,     0,     0,   609,     0,
       0,  -906,     0,     0,     0,     0,  -906,     0,     0,     0,
    1745,     0,     0,     0,     0,     0,  1037,     0,  -906,     0,
       0,     0,   971,     0,     0,   828,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   975,     0,     0,   442,     0,   611,     0,
       0,     0,     0,     0,   414,     0,     0,  1746,     0,  -906,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1718,  1719,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   976,   613,  -906,     0,     0,   977,
   -1479,     0,     0,   415,   615,   978,     0,   972,   979,     0,
     416,     0,     0,     0,     0,     0,     0,   616,     0,     0,
    1747,     0,   974,     0,     0,     0,     0,     0,     0,     0,
    1748,     0,  -906,     0,     0,     0,     0,     0,     0,     0,
     980,  -906,  -906,     0,     0,     0,  1282,  1282,     0,     0,
       0,     0,  1037,  1037,     0,     0,     0,     0,     0,     0,
       0,  -906,     0,     0,     0,     0,  -906, -1479,   972,     0,
    1803,     0,  1561,   620,   621,   622,     0,     0,  1282,     0,
       0,   417,     0,   974,  -906,     0,     0,     0,     0,     0,
       0,  1749,  -906,  1824,     0,  -906,     0,     0,  1833,  1833,
       0,  -906,  -906,  -906,     0,     0,   975,  -906,   981,  -906,
       0,  -906,  -906,  -906,     0,     0,     0,   414,     0,     0,
       0,     0,   624,   625,   626,     0,     0,   972,     0,     0,
    1006,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1859,   974,  1860,   418,     0,     0,   976,     0,     0,
       0,     0,   977,   982,   983,     0,   415,     0,   978,  -600,
     553,   979,  -640,   416,  -640,     0,     0,   975,     0,  -640,
       0,     0,     0,   419,     0,     0,     0,  -640,   984,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   980,     0,     0,   985,     0,     0,  1201,
    1201,  1201,     0,     0,   986,     0,     0,   284,     0,  1143,
    -640,  -640,     0,   420,  1143,     0,     0,  1004,  -640,   978,
       0,     0,   979,     0,     0,     0,   975,  1037,     0,  -640,
       0,     0,     0,  -640,   417,     0,     0,   414,     0,     0,
       0,     0,     0,     0,     0,  -640,     0,     0,     0,     0,
       0,     0,     0,     0,   980,     0,     0,     0,     0,     0,
       0,   981,     0,     0,     0,     0,     0,  -640,     0,     0,
       0,     0,     0,     0,  -640,  -640,   415,     0,   978,   972,
       0,   979,     0,   416,     0,     0,  1937,     0,     0,     0,
       0,  -600,  1948,  1282,   974,  -600,     0,   418,     0,     0,
       0,  1282,     0,     0,     0,  -640,   982,   983,     0,     0,
       0,     0,  1037,   980,     0,     0,     0,  -640,     0,     0,
    1543,  -640,   981,  1562,     0,     0,   419,  1563,     0,     0,
       0,   984,     0,     0,  -640,     0,     0,     0,  -600,     0,
       0,  -640,     0,     0,  -640,  -640,     0,  1948,     0,   985,
       0,  1282,  -640,     0,   417,     0,     0,   986,     0,  -640,
     284,  -640,     0,     0,  -640,     0,   420,   982,   983,     0,
       0,  2049,     0,     0,     0,  2049,     0,     0,   975,     0,
       0,   981,     0,     0,     0,     0,     0,     0,     0,   414,
    2049,  2049,   984,     0,     0,     0,     0,     0,     0,  -640,
       0,     0,     0,  -640,     0,  -640,     0,     0,     0,     0,
     985,     0,  -640,     0,     0,     0,     0,   418,   986,  1135,
       0,   284,     0,     0,   977,     0,   982,   983,   415,     0,
     978,     0,     0,   979,  -640,   416,     0,     0,     0,     0,
       0,  2049,     0,   553,  2049,  -640,   419,  -640,     0,  -640,
       0,   984,  -640,     0,     0,     0,     0,     0,     0,     0,
    -640,     0,     0,  -600,     0,   980,     0,     0,     0,   985,
    -640,  1948,     0,     0,     0,     0,     0,   986,     0,  -640,
     284,     0,     0,     0,     0,     0,   420,     0,     0,     0,
       0,     0,  -640,  -640,  -640,     0,     0,  -640,     0,  -640,
       0,  -640,     0,  1045,     0,     0,   417,  -640,     0,     0,
    2132,     0,  -640,     0,     0,     0,  -640,  -640,     0,     0,
       0,     0,     0,     0,     0,     0,  -640,     0,  -640,  2049,
       0,     0,     0,   981,     0,  -640,     0,  -640,  -640,     0,
       0,  -640,     0,  -640,     0,     0,  2172,     0,  -640,     0,
    -640,     0,     0,     0,     0,     0,     0,  -640,  -640,     0,
       0,   972,     0,  -640,     0,   662,     0,     0,  -640,   418,
       0,     0,     0,  -640,     0,     0,   974,     0,   982,   983,
       0,     0,  2049,     0,  -640,     0,     0,     0,  -640,     0,
       0,     0,     0,   554,     0,     0,  -640,     0,   419,     0,
    -640,     0,     0,   984,  -640,     0,  -640,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -640,     0,     0,
       0,   985,     0,     0,  -640,     0,     0,  -640,  -640,   986,
       0,     0,   284,     0,     0,  -640,     0,     0,   420,  1136,
    1137,  1241,  -640,     0,  -640,     0,     0,  -640,  1138,     0,
       0,     0,     0,     0,  1058,     0,  2224,     0,     0,  2226,
     975,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -640,     0,     0,     0,  -640,     0,  -640,  2243,
       0,     0,     0,     0,     0,  -640,     0,     0,     0,     0,
       0,     0,     0,  2049,     0,     0,     0,     0,  2049,     0,
    1059,     0,   978,     0,     0,   979,     0,  -640,     0,   591,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -640,     0,  1045,     0,     0,     0,     0,   592,
       0,     0,     0,     0,     0,  2276,     0,   980,     0,     0,
       0,     0,   593,  -640,     0,   594,   595,   596,   597,   598,
     599,   600,  -640,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -640,     0,     0,     0,     0,
    -640,     0,  -640,     0,     0,     0,     0,     0,     0,     0,
    -640,   601,  1241,   602,   603,   604,   605,   606,   607,     0,
    -640,     0,     0,     0,     0,     0,     0,     0,     0,  -640,
       0,     0,     0,     0,     0,   981,     0,     0,  -640,     0,
    -640,  -640,     0,     0,  -640,     0,  -640,     0,     0,     0,
       0,  -640,     0,   608,     0,     0,     0,     0,     0,     0,
       0,     0, -1471,     0,     0, -1471,  -640,     0,     0,     0,
       0,  -640,     0,  1226,     0,     0,  -640, -1471,     0,     0,
     982,   983,     0,     0,     0,     0,     0,  -640,     0,     0,
   -1555,     0,     0,     0,     0,     0,   554,     0,     0,  -640,
       0,     0, -1501,     0,     0,   984,     0,     0,     0,  -640,
       0,     0,     0,     0,     0, -1014,     0,     0,     0,     0,
       0,     0, -1501,   985,     0,     0,     0,     0, -1014,     0,
       0,   986,     0,   182,   284,   609,     0, -1471,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    40,     0,
       0,   610, -1471,     0,     0,     0,     0, -1536,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   611,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   971,     0,     0,
     828,     0,     0,     0,     0,     0,     0,   612,     0, -1471,
   -1471,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   613,     0,     0,     0,     0,     0,     0,   614,
       0,   615,     0,     0,     0,     0, -1471, -1471,     0,     0,
       0,     0,     0, -1471,   616,     0,     0, -1471,     0,     0,
       0,     0,     0,     0,   617,     0,     0,     0,     0,     0,
       0,   618,     0,     0,     0,     0, -1471,     0,     0,     0,
       0,     0,   972,     0, -1471,     0,     0, -1471, -1471,     0,
       0,     0, -1471,     0,     0,     0, -1471,   974, -1471,     0,
       0, -1471,     0, -1471,     0,     0,     0,     0,   619,     0,
     620,   621,   622,     0,     0,     0, -1471,     0,     0,     0,
       0, -1471,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0, -1471,   623,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0, -1536,     0,     0,  1414,  1415,     0,     0,     0,   624,
     625,   626,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   627,     0, -1471,   628,     0,     0,     0,     0,
       0,   975,  1416,     0,     0,     0,     0,     0,  1417,     0,
       0,     0,   414,     0,     0,  -338,     0,     0,     0,     0,
       0, -1471,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1443,     0,     0,     0,     0,     0,     0,     0,  1419,
       0,     0,   976,  1420,     0,     0,     0,   977,   665,     0,
     666,   415,     0,   978,     0,   667,   979, -1471,   416,     0,
       0,     0,     0,   668,     0,     0, -1471, -1471,     0,     0,
       0,  1444,     0,     0,     0,     0,  1445,     0,     0,     0,
       0,     0,     0, -1471,     0,     0, -1471, -1471,   980,     0,
     971, -1471,     0,   828,     0,     0,   669,   670,     0,     0,
       0,     0,     0,     0,   671,     0,     0,     0,     0, -1471,
       0,     0,     0,     0,     0,   672,     0, -1471,     0,   673,
   -1471,     0,     0,     0,     0,     0, -1471, -1471, -1471,   417,
       0,   674, -1471,     0, -1471,     0, -1471, -1471, -1471,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   675,     0,     0,   981,     0,     0,     0,
     676,   677,     0,     0,     0,   972,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     974,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   678,   418,  1093,     0,     0,     0,     0,     0,     0,
       0,   982,   983,   679,     0,     0,     0,   680,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     681,   419,     0,     0,     0,     0,   984,   682,     0,     0,
     683,   684,     0,     0,     0,     0,     0,     0,   685,     0,
       0,     0,     0,     0,   985,   686,     0,   687,     0,     0,
     688,     0,   986,     0,     0,   284,     0,     0,     0,     0,
       0,   420,  1446,  1447,   975,     0,     0,  1448,     0,  1434,
       0,  1449,  1436,  1437,     0,   414,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   689,     0,     0,     0,   690,
    1298,   691,     0,     0,     0,     0,     0,   665,   692,   666,
       0,     0,     0,     0,   667,   976,     0,     0,     0,     0,
     977,     0,   668,     0,   415,     0,   978,     0,     0,   979,
     693,   416,     0,     0,     0,     0,  -772,     0,     0,  -772,
       0,     0,     0,     0,     0,   694,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   669,   670,     0,     0,     0,
       0,   980,     0,   671,     0,     0,   695,     0,     0,     0,
       0,     0,     0,     0,   672,   696,     0,     0,   673,   157,
       0,     0,     0,     0,     0,     0,     0,     0,   697,     0,
     674,     0,     0,   698,     0,   699,     0,   971,     0,     0,
     828,     0,   417,   700,     0,     0,     0,     0,     0,     0,
       0,  -772,   675,   701,     0, -1483,     0,     0,     0,   676,
     677,     0,   702,     0,     0,     0,  -772,     0,     0,   981,
       0,   703,     0,   704,   705,     0,     0,   706,     0,   707,
       0,     0,     0,     0,   708,     0,     0,     0,     0,     0,
     678,     0,     0,     0,     0,     0,     0,     0,     0,   709,
       0,     0,   679,     0,   710,   418,   680,     0,     0,   711,
       0,     0,   972,     0,   982,   983,     0,     0,     0,   681,
     712,     0,     0,   973,     0,     0,   682,   974,     0,   683,
     684,     0,   713,     0,   419,     0,     0,   685,     0,   984,
       0,     0,   714,     0,   686,     0,   687,     0,     0,   688,
    -772,     0,     0,   971,     0,     0,   828,   985,     0,     0,
       0,  -772,     0,     0,     0,   986,     0,     0,   284,     0,
       0,     0,     0,     0,   420,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   689,     0,     0,     0,   690,     0,
     691,  -772,     0,     0,     0,     0,  -772,   692,     0,     0,
    -772,     0,  -772,     0,     0,  -772,     0,  -772,     0,     0,
       0,   975,     0,     0,   971,     0,     0,   828,     0,   693,
       0,     0,   414,     0,     0,     0,     0,     0,   972,     0,
       0,     0,     0,     0,   694,     0,     0,  -772,     0,  1052,
       0,     0,  -772,   974,     0,     0,     0,     0,     0,     0,
       0,     0,   976,     0,     0,   695,     0,   977,     0,     0,
       0,   415,     0,   978,   696,     0,   979,     0,   416,     0,
       0,     0,   971,     0,     0,   828,     0,   697,  -772,     0,
       0,     0,   698,     0,   699,     0,     0,     0, -1483,   972,
       0,     0,   700,     0,     0,     0,     0,     0,   980,     0,
       0,     0,   701,     0,   974,  -772,     0,     0,     0,     0,
       0,   702,     0,     0,     0,     0,     0,  1093,     0,     0,
     703,     0,   704,   705,     0,     0,   706,   975,   707,     0,
       0,     0,     0,   708,   971,  -772,     0,   828,   414,   417,
       0,  -772,     0,     0,     0,     0,     0,   972,   709,     0,
    -772,  -772,     0,   710,     0,     0,     0,     0,   711,     0,
       0,     0,   974,     0,     0,     0,   981,     0,   976,   712,
    -772,     0,     0,   977,     0,  -772,     0,   415,     0,   978,
    -772,   713,   979,   971,   416,     0,   828,     0,   975,     0,
       0,     0,     0,  -772,     0,     0,     0, -1483,     0,   414,
       0,  -772,   418,     0,  -772,     0,     0,     0,     0,   972,
    -772,   982,   983,     0,   980,     0,     0,     0,     0,     0,
    1097,     0,     0,     0,   974,     0,     0,     0,     0,   976,
       0,   419,     0,     0,   977,     0,   984,     0,   415,     0,
     978,     0,     0,   979,     0,   416,   975,     0,     0,     0,
     971,     0,     0,   828,   985,   417,     0,   414,   972,     0,
       0,     0,   986,     0,     0,   284,     0,     0,     0,     0,
       0,   420,     0,   974,     0,   980,     0,     0,     0,     0,
       0,     0,   981,     0,     0,     0,     0,   976,     0,     0,
       0,     0,   977,     0,     0,     0,   415,     0,   978,     0,
       0,   979,     0,   416,     0,     0,     0,     0,   975,     0,
       0,     0,     0,     0,     0,     0,   417,     0,   418,   414,
       0,     0,     0,     0,     0,   972,     0,   982,   983,     0,
       0,     0,     0,   980,     0,     0,     0,     0,     0,     0,
     974,     0,     0,   981,     0,     0,     0,   419,     0,   976,
       0,     0,   984,  1303,   977,     0,     0,   975,   415,     0,
     978,     0,     0,   979,     0,   416,     0,     0,   414,     0,
     985,     0,     0,     0,   417,     0,     0,     0,   986,   418,
       0,   284,     0,     0,     0,     0,     0,   420,   982,   983,
       0,     0,     0,     0,     0,   980,     0,     0,   976,     0,
       0,   981,     0,   977,     0,     0,     0,   415,   419,   978,
       0,     0,   979,   984,   416,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   975,     0,     0,   971,     0,     0,
     828,   985,     0,     0,     0,   414,   417,   418,     0,   986,
       0,     0,   284,     0,   980,     0,   982,   983,   420,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1187,   981,     0,   976,   419,     0,     0,     0,
     977,   984,     0,     0,   415,     0,   978,     0,     0,   979,
       0,   416,     0,     0,     0,   417,     0,     0,   971,   985,
       0,   828,     0,     0,     0,     0,     0,   986,     0,   418,
     284,     0,   972,     0,     0,     0,   420,     0,   982,   983,
       0,   980,   981,     0,     0,     0,   971,   974,     0,   828,
       0,     0,     0,     0,     0,     0,     0,     0,   419,     0,
       0,     0,     0,   984,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   418,     0,
       0,   985,   417,     0,     0,     0,     0,   982,   983,   986,
       0,     0,   284,   972,     0,     0,     0,     0,   420,     0,
       0,     0,     0,     0,     0,     0,     0,   419,   974,   981,
       0,     0,   984,     0,     0,     0,     0,     0,     0,     0,
       0,   972,     0,     0,     0,     0,     0,     0,     0,     0,
     985,   975,     0,     0,     0,     0,   974,     0,   986,  1570,
       0,   284,   414,     0,     0,   418,     0,   420,     0,     0,
       0,     0,     0,     0,   982,   983,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   976,     0,   419,     0,     0,   977,     0,   984,
       0,   415,     0,   978,     0,     0,   979,     0,   416,     0,
       0,     0,   975,     0,     0,     0,     0,   985,     0,     0,
       0,     0,     0,   414,     0,   986,     0,     0,   284,     0,
       0,     0,     0,     0,   420,     0,     0,     0,   980,     0,
     975,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   414,     0,   976,     0,     0,     0,     0,   977,     0,
       0,     0,   415,     0,   978,     0,     0,   979,     0,   416,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   417,
       0,   976,     0,     0,     0,     0,   977,     0,     0,     0,
    1016,     0,   978,     0,     0,   979,     0,   416,     0,   980,
       0,     0,     0,     0,     0,     0,   981,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   980,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1702,     0,   972,
     417,     0,   418,     0,     0,     0,     0,     0,     0,     0,
       0,   982,   983,     0,   974,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   981,   417,     0,
       0,   419,  1601,     0,  1602,     0,   984,  1603,   594,   595,
     596,   597,   598,   599,   600,  1604,  1605,  1606,     0,     0,
       0,     0,     0,     0,   985,   981,     0,     0,     0,     0,
       0,     0,   986,   418,     0,   284,  1607,     0,     0,     0,
       0,   420,   982,   983,   601,     0,   602,   603,   604,   605,
     606,   607,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   418,   419,     0,     0,     0,     0,   984,   975,     0,
     982,   983,     0,     0,     0,     0,     0,     0,     0,   414,
       0,     0,     0,     0,     0,   985,   608,     0,     0,     0,
     419,     0,     0,   986,     0,   984,   284,     0,     0,     0,
       0,     0,   420,     0,     0,     0,     0,     0,     0,  1135,
       0,     0,     0,   985,   977,     0,     0,     0,   415,     0,
     978,   986,     0,   979,   284,   416,  1608,     0,     0,     0,
     420,     0,     0,     0,   594,   595,   596,   597,   598,   599,
     600,     0,     0,     0,  1609,     0,     0,  1610,  1611,     0,
       0,     0,     0,     0,     0,   980,     0,     0,     0,     0,
       0,  1612,  2016,  2017,     0,     0,     0,     0,   609,     0,
     601,     0,   602,   603,   604,   605,   606,   607,     0,     0,
       0,     0,     0,     0,   610,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   417,     0,  1613,     0,
       0,     0,     0,     0,     0,     0,     0,  1614,     0,     0,
       0,     0,   608,     0,     0,     0,     0,     0,   611,     0,
       0,     0,     0,   981,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1615,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   972,     0,     0,  1616,   613,     0,     0,     0,   418,
       0,     0,   614,     0,   615,     0,   974,     0,   982,   983,
       0,     0,     0,     0,     0,     0,     0,   616,  1617,     0,
       0,   972,     0,     0,     0,  2018,     0,     0,   419,     0,
       0,     0,     0,   984,   609,     0,   974,     0,     0,     0,
       0,     0,  1618,     0,     0,     0,     0,  1619,     0,     0,
     610,   985,     0,     0,     0,     0,     0,     0,     0,   986,
       0,  1620,   284,     0,  2019,  2020,     0,     0,   420,  1136,
    1137,   619,     0,   620,   621,   622,     0,  1646,  1138,     0,
       0,     0,     0,     0,   611,     0,     0,     0,     0,  2021,
     975,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   414,     0,     0,     0,     0,   612,  1621,     0,     0,
       0,     0,     0,     0,  1058,     0,     0,     0,  1622,     0,
     975,   613,   624,   625,   626,     0,     0,     0,   614,     0,
     615,  1135,     0,  2022,     0,   627,   977,  1623,   628,     0,
     415,     0,   978,   616,     0,   979,     0,   416,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1624,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1004,     0,   978,     0,     0,   979,     0,   980,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   619,     0,   620,
     621,   622,     0,     0,     0,     0,  2023,   980,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   417,     0,
    2024,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  2025,     0,   981,     0,     0,   624,   625,
     626,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   627,     0,     0,   628,  2026,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   981,     0,     0,     0,     0,
       0,   418,     0,     0,  2027,     0,     0,     0,     0,     0,
     982,   983,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     419,     0,     0,     0,     0,   984,     0,     0,     0,     0,
     982,   983,     0,     0,     0,     0,     0,     0,     0,     0,
   -1555,     0,     0,   985,     0,     0,     0,     0,     0,     0,
       0,   986,     0,     0,   284,   984,     0,     0,     0,     0,
     420,  1136,  1137,     0,     0, -1014,     0,     0,     0,  1880,
    1138,     0,     0,   985,     0,     0,     0,     0, -1014,     0,
       0,   986,     0,   182,   284
};

static const yytype_int16 yycheck[] =
{
      83,   168,   221,   390,   130,   389,   628,   648,   683,   508,
     892,   830,   437,  1015,  1264,  1194,  1087,  1194,   856,   617,
     851,   188,   189,  1194,  1093,  1194,   193,   194,   195,   196,
     197,   862,   199,  1194,   201,  1035,   712,   853,  1688,   221,
    1008,   852,  1107,  1043,   654,   590,   460,    13,   870,   794,
       9,   270,    49,   986,   350,   274,  1332,   276,     6,   185,
    1077,   883,  1374,  1375,  1227,     6,   285,  1187,   235,   152,
     237,   570,  1332,  1332,  1332,    22,  1332,   244,    56,   943,
       6,  1332,     9,     6,    17,   252,     6,    48,   270,  1089,
      69,    30,   274,  1164,   276,   245,    21,    69,    84,   266,
     267,   146,   269,   285,  1224,    71,  1468,    28,   275,    48,
      23,    17,     9,   115,    49,   118,    54,   104,  1218,  1219,
    1220,    87,   341,   118,  1486,   421,  1268,     9,    56,     9,
     210,   111,   351,   115,   178,  1255,  1839,     9,   167,   358,
       1,   308,   203,     4,   311,   312,  1163,   314,   168,    37,
     369,    49,   971,    50,   230,  1123,   120,   976,    19,   341,
      49,   318,     9,   330,    94,    69,     9,  1158,    29,   351,
    1071,   390,  1534,   392,  1824,    69,   358,    69,   850,   329,
     347,    49,   823,  1303,   230,  1250,   336,   859,   860,   172,
     183,   112,   118,   183,    65,   491,    85,   153,   119,    31,
      85,    62,   874,   875,   153,    62,   289,   272,   390,    56,
     234,  1783,  1574,    72,   369,  1034,   888,   889,    60,   151,
     168,   388,   110,   293,   210,  1242,   977,   147,   230,   396,
     254,   872,   171,   230,   453,    65,   386,    11,   242,  1308,
      69,   655,  1072,   393,  1126,    87,    88,    69,   230,    94,
     230,  1002,   797,  1365,   781,  1358,   406,   168,   303,   115,
    1372,    56,  1365,  1085,   234,   312,   119,   314,  1333,  1372,
     427,   453,  1136,  1137,  1138,   107,   184,   209,  1108,   434,
     430,   448,  1146,   219,   254,  1405,  1286,  1304,   371,  1354,
     440,   374,    91,   448,   191,  1607,    70,   210,   245,   466,
     467,  1613,   210,   230,  1272,     0,  1170,   948,   373,   191,
     932,   191,  1176,  1177,  1178,  1179,  1135,   989,  1182,  1183,
     590,   277,   242,   170,   221,   257,   214,   259,   277,   496,
     230,   550,   551,   230,   447,   230,  1499,   198,   505,   322,
     237,   334,   492,  1705,    69,   309,  1018,  1364,   230,  1187,
     230,   341,   273,   963,   165,   237,   227,   237,   434,   509,
     958,   959,  1353,   433,   531,   426,   227,   447,   210,    39,
    1271,   538,   219,   234,   230,  1947,  1207,  1477,  1950,   114,
    1052,   353,   254,   318,    22,   511,  1224,   230,   434,   434,
    1459,   541,   396,   357,   440,   545,   343,   242,   230,   618,
     119,  1232,   569,   447,  1475,   434,  1406,   574,  2111,   433,
     577,   308,   579,   416,   434,   582,   583,  1255,   279,   586,
     318,   416,  1094,   294,   285,  1236,   308,  1099,   308,   318,
    1252,   410,   434,   318,   961,   962,   334,   434,  1503,   311,
     230,   402,   428,   440,   286,  1587,   433,   434,   943,   353,
     318,   312,   434,   298,   434,  1266,   315,   435,   319,   353,
     627,   353,   612,   402,   294,  1303,   334,   403,   396,   357,
     396,   332,   397,   396,   371,   434,   401,   449,  1342,  1343,
    1344,  1345,  1346,  1347,  1348,   433,   434,   393,   426,   371,
     416,   371,   427,   434,   433,   356,   357,   430,   359,   356,
     447,   136,  1313,   400,   434,   471,   367,   434,   434,  1526,
    1151,   434,   433,    23,   434,  1187,   377,  1879,   400,   314,
     400,   434,  1194,   434,   353,   324,  2098,   797,   654,   427,
     230,   353,   828,  1533,   434,  1537,   347,   398,   427,   434,
     399,  1558,   427,   440,  1656,   449,   165,    32,   447,   447,
     964,  1223,  1224,  1656,   434,   449,   403,   449,   440,   427,
     440,   219,   781,   298,  1814,   784,   785,  1405,  1930,  1167,
    1932,   163,   791,   243,  1850,   183,  1174,   853,   434,   447,
     433,   434,  1077,  1255,  1129,  1330,   447,   398,   387,   434,
    1850,  1850,  1850,  2243,  1850,   179,   872,  1760,  1960,  1850,
      49,   877,   784,   785,   210,   447,   773,   245,   214,   791,
     262,   203,   441,   442,   443,   444,   136,   446,  1290,   211,
     449,   241,  1294,  1295,  1827,  1297,   793,   449,   353,  1991,
    1992,  1303,  1159,   852,    24,   234,  1234,  1757,   239,  1759,
     183,  1136,  1137,  1138,   434,  1714,  1457,    62,   183,   230,
     369,  1146,   183,   399,   873,   254,    25,    26,   877,   239,
     879,   147,   881,   882,   960,   884,  1276,   943,  1163,   304,
    1280,   239,   292,  1168,  1794,  1170,   161,  1172,   160,  1174,
     899,  1176,  1177,  1178,  1179,  1180,  1181,  1182,  1183,   281,
      30,   183,   117,   912,   123,   845,   915,    66,   194,    68,
     210,   176,   303,   293,  2016,   343,  1826,  1707,    30,   928,
    1532,  1679,  1680,  1681,   433,   434,   441,   442,   443,   444,
     304,   446,   123,   303,   449,    65,   334,   946,   347,   448,
     912,   100,   101,   102,   434,   303,   126,  1335,   234,  1414,
     230,   262,   961,   962,   220,   403,   928,  1242,  1951,   196,
     351,   877,   242,   238,  1687,   230,  1773,   206,   254,  1692,
    1693,   342,   929,  1696,  1697,  1698,   943,  1700,  1701,   859,
       9,   351,  1837,    12,   857,   241,    15,    16,   147,   234,
     149,   433,  1380,   351,   304,  1061,     9,   533,   157,   281,
    1466,   941,  1792,  1862,  1610,   878,   286,   880,   341,   889,
     282,   123,   885,  1872,  1873,  1984,   341,  1984,   209,  1304,
     341,   894,   196,  1984,  1831,  1984,   209,  1917,  1918,  1919,
    1920,   441,   442,  1984,   239,  1689,   292,   256,   434,     1,
    1694,   278,  1507,    56,   433,   434,   176,  2199,  2200,   272,
    1335,  1516,   434,   433,   434,   104,   447,  1342,  1343,  1344,
    1345,  1346,  1347,  1348,  1073,   256,  1925,  1926,   259,   228,
    1136,  1137,  1138,   339,   230,    27,   259,   447,    69,  1364,
    1146,   315,   207,   242,  1996,    47,  1998,   191,   433,   447,
      28,   447,     9,   190,    99,   340,   270,   227,   303,    61,
     312,   198,  1168,  1565,  1170,   230,  1172,   418,  1174,   198,
    1176,  1177,  1178,  1179,  1180,  1181,  1182,  1183,   447,  1500,
     217,   172,   433,   172,  2268,  1506,   230,  1043,  2168,  1757,
     245,  1759,   163,   237,   395,   184,  1009,    99,   227,    56,
    1761,  2285,   365,   429,   191,  1061,   351,   230,  2009,   305,
    1159,   356,   497,   227,   434,   367,   368,   170,   232,    12,
     440,  1118,    15,    16,   294,   399,  1794,   264,   265,  1136,
    1137,  1138,   203,  1561,   112,   272,   273,  1855,   191,  1146,
     211,   278,   279,   230,  1649,   441,   442,   410,  1128,   450,
     237,  1812,  1870,  1871,   365,   361,   247,   312,  1826,   314,
     361,  1168,   164,  1170,   308,  1172,   219,   361,  2000,  1176,
    1177,  1178,  1179,  1180,  1181,  1182,  1183,   230,   247,   248,
     294,    82,   184,   312,   237,  2137,   252,  1236,     8,   434,
     319,  2271,  1873,   117,   361,   394,   265,   266,   361,   410,
     881,  1526,  1527,  1921,   410,   120,  1924,  1552,   210,   410,
     281,    11,   191,   215,   191,    35,   410,  1266,   899,   194,
     195,   308,  1567,   225,   361,    25,    26,   371,   357,  1335,
     230,   297,   166,  1558,   191,   434,  1342,  1343,  1344,  1345,
    1346,  1347,  1348,   410,  1925,  1926,  1202,   410,   434,   164,
       8,   230,   252,   230,   349,   308,   400,    57,   237,   234,
     237,   447,   219,   377,  1313,   164,   164,   289,   290,  2101,
     204,  1983,   447,   230,  1529,  1324,  1325,    35,   212,   254,
     237,   303,   307,   499,   371,   184,   184,   312,   504,   234,
       6,  2009,   292,     9,    94,    95,   440,    97,   447,  1801,
    1213,  1772,    89,    90,   234,   105,   300,  1728,  1729,   254,
     312,   313,  1324,  1325,   234,   415,   433,   156,   371,  1275,
     268,   160,   353,   325,   254,   327,   113,   349,   428,   308,
     447,   308,   447,  1754,   254,  1342,  1343,  1344,  1345,  1346,
    1347,  1348,  1763,   271,  2062,   273,   447,   400,   148,   149,
     403,   308,   349,   440,   247,   248,  1827,   397,  1314,   159,
    1392,   401,   397,  1395,  1689,    81,   401,     2,  1400,  1694,
     158,     6,   265,   266,   162,  2024,  2208,   312,   117,   314,
      96,   434,   330,   121,   430,   447,   432,   440,    12,    13,
      14,   304,   371,  1898,   371,  1900,    20,   317,   441,   442,
     443,   444,  1904,   446,   443,   444,   449,   446,  1457,   132,
     441,   442,   443,   444,   371,   446,  1168,   303,   449,  2087,
    1172,  2089,   370,   400,   372,   427,   227,   228,  1180,  1181,
     567,   231,   447,   150,    58,   152,   166,   153,   419,   420,
     421,   422,   258,   400,   260,   447,   403,   349,  1773,   419,
     420,   421,   422,   191,   429,   349,  1781,   434,   433,   153,
     154,   440,  1791,   440,   180,  2183,   419,   420,   421,   422,
    2188,   150,  1893,   152,   312,   191,   314,   434,   227,   228,
    1951,   263,   264,   440,   263,   264,   436,   181,   408,   447,
     233,  1912,   230,   187,  1733,  1734,  1735,  1736,   434,   237,
     287,   288,  2214,   334,  1610,   221,  1831,   447,  1929,   447,
     226,   249,   352,   433,   230,   447,   232,   212,   447,   235,
     447,   237,   447,    71,   218,   398,   447,   349,   222,   153,
     154,   441,   442,   443,   444,  1864,   446,   229,   434,   434,
    1589,   328,   329,   453,   447,   345,   178,   447,   276,  1970,
    1971,   267,   273,   388,    24,   447,   447,   181,  1979,   349,
     325,   365,   210,   187,  2069,   447,  2071,   104,   434,  1566,
     308,   441,   442,   443,   444,   377,   446,  1589,    56,   449,
    1536,   434,   360,  1689,  1633,   385,   210,    84,  1694,   172,
     447,   344,   308,   349,   218,   365,   276,  1594,   222,   106,
     434,   230,  1651,   207,   356,  1602,  2108,   243,    67,   349,
     447,     9,  1609,   243,   447,   447,  1572,    23,  1598,   335,
     270,  1633,   434,  1579,   447,   230,   250,   251,   294,   447,
     447,   255,    83,   371,   434,  1615,   374,   375,    83,  1651,
     434,   265,  1691,   434,   428,   393,  2067,   447,   272,   310,
     377,   396,   228,   277,  2075,   371,   441,   442,   443,   444,
     196,   446,   434,  1660,   380,   381,  1663,   312,   453,  2090,
     396,   295,   441,   442,   443,   444,   357,   446,    55,  1691,
     449,   377,  1689,    81,   400,    27,   433,  1694,   184,   405,
     441,   442,   443,   444,   365,   446,   349,  2118,    96,  2120,
    2202,   447,   440,  2205,   214,   447,  2127,   423,   357,   441,
     442,   443,   444,  2165,   446,   431,   434,   449,   434,   221,
     430,   339,  2193,   210,   440,   106,  2147,  2148,   441,   442,
     443,   444,   448,   446,   398,   230,   449,   299,    37,   280,
    1737,   374,   441,   442,   443,   444,  1743,   446,   274,   440,
     449,   393,  2254,   396,   448,    27,   355,   451,   452,   270,
     450,   454,   171,   447,   447,   434,   230,   398,   133,   849,
     104,    17,   169,   853,   433,   395,   184,   450,   393,   859,
     230,    30,   180,   124,   864,   865,  2288,   450,  1785,   125,
     870,   871,   872,   191,   450,   450,   450,   877,   450,   450,
     201,    56,  2223,   883,   450,   396,  2020,   426,   127,   450,
     450,   450,   892,   893,   341,   895,   440,   441,   442,   443,
     444,   312,   446,   450,   448,   449,   129,   451,   452,   130,
      11,    98,   230,   392,   232,   396,   134,   235,    49,   237,
    1796,   395,   135,   393,    25,    26,  1802,   390,   395,   176,
     140,   428,   242,    49,   143,  1852,   176,   109,   326,   373,
    1857,   111,   433,   943,   111,   396,  1846,   434,   183,   267,
     302,   334,   230,   160,   131,   430,    57,   168,   396,   359,
     206,   396,    49,  1796,   214,   206,   119,   273,   176,   189,
     446,   358,   438,   973,   439,   263,   214,   449,   227,   334,
     449,   391,    31,   396,    33,   449,   366,    36,  1957,   449,
     308,   128,   259,    94,    95,   258,    97,    46,   262,   183,
     393,   324,   396,    49,   105,   135,     8,   430,  1008,   123,
     430,   176,     9,   300,   396,   301,   170,   335,   198,   261,
     322,   337,   122,   427,   107,  1957,   427,    49,   172,   138,
     278,   256,   139,   234,   293,  1035,   141,   282,   255,   110,
     277,   387,     7,  1043,  1044,   113,    66,   148,   149,   397,
     153,   153,   216,   371,   126,  2192,   321,   133,   159,    99,
      49,  1061,   380,   381,   321,   214,   234,   142,    93,   260,
     217,   145,   257,    90,   199,   188,   430,  1077,   383,    49,
     399,   434,   400,   234,   300,  1085,   337,   405,   234,  1089,
     144,   171,   176,   286,   300,  2012,   137,  1097,    49,     6,
    1100,   415,   335,    21,    53,   423,  2023,   185,  2025,   130,
     170,   180,   203,   431,  1287,   487,   434,  1109,   421,   564,
     134,  1325,   440,  1123,   173,  1318,  1126,  1110,   177,   918,
     231,   575,  1842,  1795,   219,  2104,  1136,  1137,  1138,  2056,
    2057,   190,     1,   371,  2044,   108,  1146,     6,    48,   226,
       9,   152,   551,   844,  1850,  1635,   301,  2190,   822,   535,
     948,   931,  2039,  1163,  2176,   797,   122,  1018,  1168,  1716,
    1170,   469,  1172,  1799,  1377,  1376,  1176,  1177,  1178,  1179,
    1180,  1181,  1182,  1183,  1675,  1023,  1714,   236,  1750,  1229,
    1232,  1499,  1760,  2110,  1239,  1941,  1781,    33,  1245,  1524,
      36,  2170,  1061,  1548,  1800,  1314,  1280,  1083,    44,    45,
      46,  1816,  1094,  1085,   884,  1579,  1994,  1579,  1653,  1999,
    2111,  1807,    81,  2192,  2005,  1473,  1196,  1073,    37,    38,
      39,    40,    41,    42,   283,  1561,  1589,    96,  2170,  2156,
    2157,   944,  1242,  2160,   345,   233,  1192,   827,   310,  1250,
    2167,  1026,  1252,   584,  2194,  2155,   953,   788,   307,     6,
    2192,    56,     9,  1420,    73,  1265,    75,    76,    77,    78,
      79,    80,  1272,    -1,  1858,  2175,  2176,    -1,  1149,  1279,
      -1,    -1,   331,    30,   385,    -1,  1286,   336,    -1,  2206,
      -1,    -1,  2261,    -1,   153,   154,    -1,   346,  1298,  2268,
      -1,   350,    -1,    -1,  1304,    -1,   115,    -1,    -1,    -1,
    1310,    -1,    -1,  2146,    -1,    -1,  2285,    -1,    65,   155,
    2237,   180,   181,    -1,    -1,    -1,    -1,  1327,   187,  2261,
      -1,    -1,   191,   434,    81,  2235,  2236,   173,    -1,  2239,
      -1,  2241,  1342,  1343,  1344,  1345,  1346,  1347,  1348,    96,
      -1,   210,    -1,  2270,   190,    -1,    -1,    -1,   407,   218,
      -1,    -1,   221,   222,  1364,    -1,    -1,   226,   417,    -1,
      -1,   230,    -1,   232,  2207,    -1,   235,    -1,   237,  2279,
      -1,    -1,    -1,    -1,  1384,    -1,    -1,    -1,   197,    -1,
      -1,   250,    -1,    -1,    -1,    -1,   255,    -1,    -1,    -1,
     236,    -1,    -1,    -1,    -1,    -1,  1406,    -1,   267,    -1,
      -1,    -1,     6,    -1,    -1,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   180,    -1,    -1,  2269,    -1,   247,    -1,
      -1,    -1,    -1,    -1,   191,    -1,    -1,   283,    -1,   308,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1460,  1461,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   221,   284,   335,    -1,    -1,   226,
     227,    -1,    -1,   230,   293,   232,    -1,    81,   235,    -1,
     237,    -1,    -1,    -1,    -1,    -1,    -1,   306,    -1,    -1,
     336,    -1,    96,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     346,    -1,   371,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     267,   380,   381,    -1,    -1,    -1,  1526,  1527,    -1,    -1,
      -1,    -1,  1532,  1533,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   400,    -1,    -1,    -1,    -1,   405,   294,    81,    -1,
    1550,    -1,   146,   362,   363,   364,    -1,    -1,  1558,    -1,
      -1,   308,    -1,    96,   423,    -1,    -1,    -1,    -1,    -1,
      -1,   407,   431,  1573,    -1,   434,    -1,    -1,  1578,  1579,
      -1,   440,   441,   442,    -1,    -1,   180,   446,   335,   448,
      -1,   450,   451,   452,    -1,    -1,    -1,   191,    -1,    -1,
      -1,    -1,   411,   412,   413,    -1,    -1,    81,    -1,    -1,
    1610,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1621,    96,  1623,   371,    -1,    -1,   221,    -1,    -1,
      -1,    -1,   226,   380,   381,    -1,   230,    -1,   232,     0,
       1,   235,     3,   237,     5,    -1,    -1,   180,    -1,    10,
      -1,    -1,    -1,   400,    -1,    -1,    -1,    18,   405,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   267,    -1,    -1,   423,    -1,    -1,  1679,
    1680,  1681,    -1,    -1,   431,    -1,    -1,   434,    -1,  1689,
      51,    52,    -1,   440,  1694,    -1,    -1,   230,    59,   232,
      -1,    -1,   235,    -1,    -1,    -1,   180,  1707,    -1,    70,
      -1,    -1,    -1,    74,   308,    -1,    -1,   191,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   267,    -1,    -1,    -1,    -1,    -1,
      -1,   335,    -1,    -1,    -1,    -1,    -1,   108,    -1,    -1,
      -1,    -1,    -1,    -1,   115,   116,   230,    -1,   232,    81,
      -1,   235,    -1,   237,    -1,    -1,  1766,    -1,    -1,    -1,
      -1,   132,  1772,  1773,    96,   136,    -1,   371,    -1,    -1,
      -1,  1781,    -1,    -1,    -1,   146,   380,   381,    -1,    -1,
      -1,    -1,  1792,   267,    -1,    -1,    -1,   158,    -1,    -1,
    1800,   162,   335,   397,    -1,    -1,   400,   401,    -1,    -1,
      -1,   405,    -1,    -1,   175,    -1,    -1,    -1,   179,    -1,
      -1,   182,    -1,    -1,   185,   186,    -1,  1827,    -1,   423,
      -1,  1831,   193,    -1,   308,    -1,    -1,   431,    -1,   200,
     434,   202,    -1,    -1,   205,    -1,   440,   380,   381,    -1,
      -1,  1851,    -1,    -1,    -1,  1855,    -1,    -1,   180,    -1,
      -1,   335,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   191,
    1870,  1871,   405,    -1,    -1,    -1,    -1,    -1,    -1,   240,
      -1,    -1,    -1,   244,    -1,   246,    -1,    -1,    -1,    -1,
     423,    -1,   253,    -1,    -1,    -1,    -1,   371,   431,   221,
      -1,   434,    -1,    -1,   226,    -1,   380,   381,   230,    -1,
     232,    -1,    -1,   235,   275,   237,    -1,    -1,    -1,    -1,
      -1,  1921,    -1,     1,  1924,     3,   400,     5,    -1,   290,
      -1,   405,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      18,    -1,    -1,   304,    -1,   267,    -1,    -1,    -1,   423,
     311,  1951,    -1,    -1,    -1,    -1,    -1,   431,    -1,   320,
     434,    -1,    -1,    -1,    -1,    -1,   440,    -1,    -1,    -1,
      -1,    -1,   333,    51,    52,    -1,    -1,   338,    -1,   340,
      -1,    59,    -1,  1983,    -1,    -1,   308,   348,    -1,    -1,
    1990,    -1,    70,    -1,    -1,    -1,    74,   358,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   367,    -1,    86,  2009,
      -1,    -1,    -1,   335,    -1,   376,    -1,   378,   379,    -1,
      -1,   382,    -1,   384,    -1,    -1,  2026,    -1,   389,    -1,
     108,    -1,    -1,    -1,    -1,    -1,    -1,   115,   116,    -1,
      -1,    81,    -1,   404,    -1,   123,    -1,    -1,   409,   371,
      -1,    -1,    -1,   414,    -1,    -1,    96,    -1,   380,   381,
      -1,    -1,  2062,    -1,   425,    -1,    -1,    -1,   146,    -1,
      -1,    -1,    -1,   434,    -1,    -1,   437,    -1,   400,    -1,
     158,    -1,    -1,   405,   162,    -1,   447,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   175,    -1,    -1,
      -1,   423,    -1,    -1,   182,    -1,    -1,   185,   186,   431,
      -1,    -1,   434,    -1,    -1,   193,    -1,    -1,   440,   441,
     442,  2121,   200,    -1,   202,    -1,    -1,   205,   450,    -1,
      -1,    -1,    -1,    -1,   174,    -1,  2136,    -1,    -1,  2139,
     180,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   240,    -1,    -1,    -1,   244,    -1,   246,  2169,
      -1,    -1,    -1,    -1,    -1,   253,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  2183,    -1,    -1,    -1,    -1,  2188,    -1,
     230,    -1,   232,    -1,    -1,   235,    -1,   275,    -1,     1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   290,    -1,  2214,    -1,    -1,    -1,    -1,    21,
      -1,    -1,    -1,    -1,    -1,  2225,    -1,   267,    -1,    -1,
      -1,    -1,    34,   311,    -1,    37,    38,    39,    40,    41,
      42,    43,   320,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   333,    -1,    -1,    -1,    -1,
     338,    -1,   340,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     348,    73,  2272,    75,    76,    77,    78,    79,    80,    -1,
     358,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   367,
      -1,    -1,    -1,    -1,    -1,   335,    -1,    -1,   376,    -1,
     378,   379,    -1,    -1,   382,    -1,   384,    -1,    -1,    -1,
      -1,   389,    -1,   115,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     6,    -1,    -1,     9,   404,    -1,    -1,    -1,
      -1,   409,    -1,    17,    -1,    -1,   414,    21,    -1,    -1,
     380,   381,    -1,    -1,    -1,    -1,    -1,   425,    -1,    -1,
     390,    -1,    -1,    -1,    -1,    -1,   434,    -1,    -1,   437,
      -1,    -1,   164,    -1,    -1,   405,    -1,    -1,    -1,   447,
      -1,    -1,    -1,    -1,    -1,   415,    -1,    -1,    -1,    -1,
      -1,    -1,   184,   423,    -1,    -1,    -1,    -1,   428,    -1,
      -1,   431,    -1,   433,   434,   197,    -1,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   210,    -1,
      -1,   213,    96,    -1,    -1,    -1,    -1,   219,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,    -1,    -1,
       9,    -1,    -1,    -1,    -1,    -1,    -1,   269,    -1,   153,
     154,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   284,    -1,    -1,    -1,    -1,    -1,    -1,   291,
      -1,   293,    -1,    -1,    -1,    -1,   180,   181,    -1,    -1,
      -1,    -1,    -1,   187,   306,    -1,    -1,   191,    -1,    -1,
      -1,    -1,    -1,    -1,   316,    -1,    -1,    -1,    -1,    -1,
      -1,   323,    -1,    -1,    -1,    -1,   210,    -1,    -1,    -1,
      -1,    -1,    81,    -1,   218,    -1,    -1,   221,   222,    -1,
      -1,    -1,   226,    -1,    -1,    -1,   230,    96,   232,    -1,
      -1,   235,    -1,   237,    -1,    -1,    -1,    -1,   360,    -1,
     362,   363,   364,    -1,    -1,    -1,   250,    -1,    -1,    -1,
      -1,   255,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   267,   386,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   403,    -1,    -1,   153,   154,    -1,    -1,    -1,   411,
     412,   413,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   424,    -1,   308,   427,    -1,    -1,    -1,    -1,
      -1,   180,   181,    -1,    -1,    -1,    -1,    -1,   187,    -1,
      -1,    -1,   191,    -1,    -1,   447,    -1,    -1,    -1,    -1,
      -1,   335,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   210,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,
      -1,    -1,   221,   222,    -1,    -1,    -1,   226,     3,    -1,
       5,   230,    -1,   232,    -1,    10,   235,   371,   237,    -1,
      -1,    -1,    -1,    18,    -1,    -1,   380,   381,    -1,    -1,
      -1,   250,    -1,    -1,    -1,    -1,   255,    -1,    -1,    -1,
      -1,    -1,    -1,   397,    -1,    -1,   400,   401,   267,    -1,
       6,   405,    -1,     9,    -1,    -1,    51,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,   423,
      -1,    -1,    -1,    -1,    -1,    70,    -1,   431,    -1,    74,
     434,    -1,    -1,    -1,    -1,    -1,   440,   441,   442,   308,
      -1,    86,   446,    -1,   448,    -1,   450,   451,   452,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   108,    -1,    -1,   335,    -1,    -1,    -1,
     115,   116,    -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      96,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   146,   371,   109,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   380,   381,   158,    -1,    -1,    -1,   162,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     175,   400,    -1,    -1,    -1,    -1,   405,   182,    -1,    -1,
     185,   186,    -1,    -1,    -1,    -1,    -1,    -1,   193,    -1,
      -1,    -1,    -1,    -1,   423,   200,    -1,   202,    -1,    -1,
     205,    -1,   431,    -1,    -1,   434,    -1,    -1,    -1,    -1,
      -1,   440,   441,   442,   180,    -1,    -1,   446,    -1,   448,
      -1,   450,   451,   452,    -1,   191,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   240,    -1,    -1,    -1,   244,
     206,   246,    -1,    -1,    -1,    -1,    -1,     3,   253,     5,
      -1,    -1,    -1,    -1,    10,   221,    -1,    -1,    -1,    -1,
     226,    -1,    18,    -1,   230,    -1,   232,    -1,    -1,   235,
     275,   237,    -1,    -1,    -1,    -1,     6,    -1,    -1,     9,
      -1,    -1,    -1,    -1,    -1,   290,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    -1,
      -1,   267,    -1,    59,    -1,    -1,   311,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,   320,    -1,    -1,    74,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   333,    -1,
      86,    -1,    -1,   338,    -1,   340,    -1,     6,    -1,    -1,
       9,    -1,   308,   348,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,   108,   358,    -1,    85,    -1,    -1,    -1,   115,
     116,    -1,   367,    -1,    -1,    -1,    96,    -1,    -1,   335,
      -1,   376,    -1,   378,   379,    -1,    -1,   382,    -1,   384,
      -1,    -1,    -1,    -1,   389,    -1,    -1,    -1,    -1,    -1,
     146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   404,
      -1,    -1,   158,    -1,   409,   371,   162,    -1,    -1,   414,
      -1,    -1,    81,    -1,   380,   381,    -1,    -1,    -1,   175,
     425,    -1,    -1,    92,    -1,    -1,   182,    96,    -1,   185,
     186,    -1,   437,    -1,   400,    -1,    -1,   193,    -1,   405,
      -1,    -1,   447,    -1,   200,    -1,   202,    -1,    -1,   205,
     180,    -1,    -1,     6,    -1,    -1,     9,   423,    -1,    -1,
      -1,   191,    -1,    -1,    -1,   431,    -1,    -1,   434,    -1,
      -1,    -1,    -1,    -1,   440,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   240,    -1,    -1,    -1,   244,    -1,
     246,   221,    -1,    -1,    -1,    -1,   226,   253,    -1,    -1,
     230,    -1,   232,    -1,    -1,   235,    -1,   237,    -1,    -1,
      -1,   180,    -1,    -1,     6,    -1,    -1,     9,    -1,   275,
      -1,    -1,   191,    -1,    -1,    -1,    -1,    -1,    81,    -1,
      -1,    -1,    -1,    -1,   290,    -1,    -1,   267,    -1,    92,
      -1,    -1,   272,    96,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   221,    -1,    -1,   311,    -1,   226,    -1,    -1,
      -1,   230,    -1,   232,   320,    -1,   235,    -1,   237,    -1,
      -1,    -1,     6,    -1,    -1,     9,    -1,   333,   308,    -1,
      -1,    -1,   338,    -1,   340,    -1,    -1,    -1,   318,    81,
      -1,    -1,   348,    -1,    -1,    -1,    -1,    -1,   267,    -1,
      -1,    -1,   358,    -1,    96,   335,    -1,    -1,    -1,    -1,
      -1,   367,    -1,    -1,    -1,    -1,    -1,   109,    -1,    -1,
     376,    -1,   378,   379,    -1,    -1,   382,   180,   384,    -1,
      -1,    -1,    -1,   389,     6,   365,    -1,     9,   191,   308,
      -1,   371,    -1,    -1,    -1,    -1,    -1,    81,   404,    -1,
     380,   381,    -1,   409,    -1,    -1,    -1,    -1,   414,    -1,
      -1,    -1,    96,    -1,    -1,    -1,   335,    -1,   221,   425,
     400,    -1,    -1,   226,    -1,   405,    -1,   230,    -1,   232,
     410,   437,   235,     6,   237,    -1,     9,    -1,   180,    -1,
      -1,    -1,    -1,   423,    -1,    -1,    -1,   427,    -1,   191,
      -1,   431,   371,    -1,   434,    -1,    -1,    -1,    -1,    81,
     440,   380,   381,    -1,   267,    -1,    -1,    -1,    -1,    -1,
      92,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,   221,
      -1,   400,    -1,    -1,   226,    -1,   405,    -1,   230,    -1,
     232,    -1,    -1,   235,    -1,   237,   180,    -1,    -1,    -1,
       6,    -1,    -1,     9,   423,   308,    -1,   191,    81,    -1,
      -1,    -1,   431,    -1,    -1,   434,    -1,    -1,    -1,    -1,
      -1,   440,    -1,    96,    -1,   267,    -1,    -1,    -1,    -1,
      -1,    -1,   335,    -1,    -1,    -1,    -1,   221,    -1,    -1,
      -1,    -1,   226,    -1,    -1,    -1,   230,    -1,   232,    -1,
      -1,   235,    -1,   237,    -1,    -1,    -1,    -1,   180,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   308,    -1,   371,   191,
      -1,    -1,    -1,    -1,    -1,    81,    -1,   380,   381,    -1,
      -1,    -1,    -1,   267,    -1,    -1,    -1,    -1,    -1,    -1,
      96,    -1,    -1,   335,    -1,    -1,    -1,   400,    -1,   221,
      -1,    -1,   405,   176,   226,    -1,    -1,   180,   230,    -1,
     232,    -1,    -1,   235,    -1,   237,    -1,    -1,   191,    -1,
     423,    -1,    -1,    -1,   308,    -1,    -1,    -1,   431,   371,
      -1,   434,    -1,    -1,    -1,    -1,    -1,   440,   380,   381,
      -1,    -1,    -1,    -1,    -1,   267,    -1,    -1,   221,    -1,
      -1,   335,    -1,   226,    -1,    -1,    -1,   230,   400,   232,
      -1,    -1,   235,   405,   237,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   180,    -1,    -1,     6,    -1,    -1,
       9,   423,    -1,    -1,    -1,   191,   308,   371,    -1,   431,
      -1,    -1,   434,    -1,   267,    -1,   380,   381,   440,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   396,   335,    -1,   221,   400,    -1,    -1,    -1,
     226,   405,    -1,    -1,   230,    -1,   232,    -1,    -1,   235,
      -1,   237,    -1,    -1,    -1,   308,    -1,    -1,     6,   423,
      -1,     9,    -1,    -1,    -1,    -1,    -1,   431,    -1,   371,
     434,    -1,    81,    -1,    -1,    -1,   440,    -1,   380,   381,
      -1,   267,   335,    -1,    -1,    -1,     6,    96,    -1,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   400,    -1,
      -1,    -1,    -1,   405,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   371,    -1,
      -1,   423,   308,    -1,    -1,    -1,    -1,   380,   381,   431,
      -1,    -1,   434,    81,    -1,    -1,    -1,    -1,   440,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   400,    96,   335,
      -1,    -1,   405,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     423,   180,    -1,    -1,    -1,    -1,    96,    -1,   431,   365,
      -1,   434,   191,    -1,    -1,   371,    -1,   440,    -1,    -1,
      -1,    -1,    -1,    -1,   380,   381,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   221,    -1,   400,    -1,    -1,   226,    -1,   405,
      -1,   230,    -1,   232,    -1,    -1,   235,    -1,   237,    -1,
      -1,    -1,   180,    -1,    -1,    -1,    -1,   423,    -1,    -1,
      -1,    -1,    -1,   191,    -1,   431,    -1,    -1,   434,    -1,
      -1,    -1,    -1,    -1,   440,    -1,    -1,    -1,   267,    -1,
     180,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   191,    -1,   221,    -1,    -1,    -1,    -1,   226,    -1,
      -1,    -1,   230,    -1,   232,    -1,    -1,   235,    -1,   237,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   308,
      -1,   221,    -1,    -1,    -1,    -1,   226,    -1,    -1,    -1,
     230,    -1,   232,    -1,    -1,   235,    -1,   237,    -1,   267,
      -1,    -1,    -1,    -1,    -1,    -1,   335,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   267,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   366,    -1,    81,
     308,    -1,   371,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   380,   381,    -1,    96,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   335,   308,    -1,
      -1,   400,    31,    -1,    33,    -1,   405,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,   423,   335,    -1,    -1,    -1,    -1,
      -1,    -1,   431,   371,    -1,   434,    65,    -1,    -1,    -1,
      -1,   440,   380,   381,    73,    -1,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   371,   400,    -1,    -1,    -1,    -1,   405,   180,    -1,
     380,   381,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   191,
      -1,    -1,    -1,    -1,    -1,   423,   115,    -1,    -1,    -1,
     400,    -1,    -1,   431,    -1,   405,   434,    -1,    -1,    -1,
      -1,    -1,   440,    -1,    -1,    -1,    -1,    -1,    -1,   221,
      -1,    -1,    -1,   423,   226,    -1,    -1,    -1,   230,    -1,
     232,   431,    -1,   235,   434,   237,   155,    -1,    -1,    -1,
     440,    -1,    -1,    -1,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,   173,    -1,    -1,   176,   177,    -1,
      -1,    -1,    -1,    -1,    -1,   267,    -1,    -1,    -1,    -1,
      -1,   190,    65,    66,    -1,    -1,    -1,    -1,   197,    -1,
      73,    -1,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    -1,    -1,   213,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   308,    -1,   227,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   236,    -1,    -1,
      -1,    -1,   115,    -1,    -1,    -1,    -1,    -1,   247,    -1,
      -1,    -1,    -1,   335,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     269,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    -1,    -1,   283,   284,    -1,    -1,    -1,   371,
      -1,    -1,   291,    -1,   293,    -1,    96,    -1,   380,   381,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   306,   307,    -1,
      -1,    81,    -1,    -1,    -1,   188,    -1,    -1,   400,    -1,
      -1,    -1,    -1,   405,   197,    -1,    96,    -1,    -1,    -1,
      -1,    -1,   331,    -1,    -1,    -1,    -1,   336,    -1,    -1,
     213,   423,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   431,
      -1,   350,   434,    -1,   227,   228,    -1,    -1,   440,   441,
     442,   360,    -1,   362,   363,   364,    -1,   449,   450,    -1,
      -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,   252,
     180,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   191,    -1,    -1,    -1,    -1,   269,   396,    -1,    -1,
      -1,    -1,    -1,    -1,   174,    -1,    -1,    -1,   407,    -1,
     180,   284,   411,   412,   413,    -1,    -1,    -1,   291,    -1,
     293,   221,    -1,   296,    -1,   424,   226,   426,   427,    -1,
     230,    -1,   232,   306,    -1,   235,    -1,   237,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   447,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     230,    -1,   232,    -1,    -1,   235,    -1,   267,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   360,    -1,   362,
     363,   364,    -1,    -1,    -1,    -1,   369,   267,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   308,    -1,
     383,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   406,    -1,   335,    -1,    -1,   411,   412,
     413,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   424,    -1,    -1,   427,   428,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   335,    -1,    -1,    -1,    -1,
      -1,   371,    -1,    -1,   447,    -1,    -1,    -1,    -1,    -1,
     380,   381,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     400,    -1,    -1,    -1,    -1,   405,    -1,    -1,    -1,    -1,
     380,   381,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     390,    -1,    -1,   423,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   431,    -1,    -1,   434,   405,    -1,    -1,    -1,    -1,
     440,   441,   442,    -1,    -1,   415,    -1,    -1,    -1,   449,
     450,    -1,    -1,   423,    -1,    -1,    -1,    -1,   428,    -1,
      -1,   431,    -1,   433,   434
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   456,   457,     0,   179,   304,   458,   459,   460,   466,
     473,   475,   447,   447,   459,   147,   481,   481,   230,   305,
     476,   476,   117,   461,   467,    27,   477,   477,   447,    99,
     583,   583,   230,   447,   474,    82,   482,   117,   462,   468,
     210,   478,  1127,   349,   166,   204,   212,   536,   447,   300,
     717,   717,   447,    72,   315,   399,   479,   480,   447,   447,
     349,   447,   165,   347,   398,   584,   590,   117,   463,   469,
     473,   132,   472,   480,   303,  1138,   483,   537,   447,   538,
     349,   436,   615,   586,    54,   426,   720,   136,   463,   470,
     481,   476,   268,   330,   370,   372,   484,   485,   489,   497,
     502,   540,   166,   539,    22,   245,   343,   573,   574,   575,
     576,   578,   582,   447,   349,   233,   660,   434,   589,   591,
    1058,   722,   721,   334,   728,   476,   464,   447,   447,   447,
     447,   447,   352,   541,   447,   212,   572,    71,   398,  1123,
     312,   367,   368,   577,   447,   575,   585,   447,   349,   229,
     662,   588,   590,   617,   618,   619,   592,    49,   723,   724,
     725,  1118,   723,   434,   447,   447,   583,   239,   351,   434,
     488,   490,   491,   492,   493,   495,   496,  1138,   178,   498,
     499,   500,   433,   486,   487,   488,  1152,    11,    25,    26,
      57,    94,    95,    97,   105,   148,   149,   159,   231,   345,
     385,   434,   503,   504,   505,   506,   513,   522,   526,   529,
     530,   531,   532,   533,   534,   535,   276,  1104,   540,   447,
     273,  1135,   388,  1146,    24,  1114,   587,   616,   447,   349,
     325,   664,   591,   620,  1098,   593,   724,   365,   410,   726,
     318,   427,   718,   465,   365,  1127,   447,   491,   447,   492,
      62,   356,  1110,     9,   230,   501,   447,   500,   447,   447,
     487,   104,   434,  1069,  1127,  1127,  1069,   377,   360,  1142,
    1127,  1127,  1127,  1127,  1127,  1069,  1127,    56,  1120,  1127,
     447,   505,  1069,   573,   434,  1065,  1066,  1084,    84,  1121,
     172,  1124,   588,   617,   661,   447,   349,   344,   705,   617,
     447,  1098,   434,   621,   623,   628,     1,    47,    61,    99,
     215,   225,   312,   313,   325,   327,   427,   447,   594,   595,
     597,   601,   603,   605,   606,   612,   613,   614,  1127,  1127,
     365,   276,   727,   106,   729,   717,  1127,   230,  1087,   447,
     356,  1127,   207,   207,   230,   447,   243,   514,  1069,  1069,
    1127,  1127,  1127,  1066,    67,  1069,  1069,  1066,  1127,  1066,
     523,   524,  1069,    94,   508,  1069,   542,   196,   270,  1107,
    1066,   579,   580,  1058,  1057,  1058,   617,   663,   447,   349,
     621,   447,   168,   434,   624,   625,  1121,  1127,   312,   314,
    1108,  1108,  1127,  1121,  1127,   243,  1132,  1127,    23,  1113,
     270,   164,   184,    31,   107,  1087,  1127,   434,   447,   719,
     469,  1087,  1066,  1127,   191,   230,   237,   308,   371,   400,
     440,   527,   528,  1090,  1066,   230,  1066,    23,   210,  1069,
    1128,   271,   273,   510,   511,   512,   507,   543,  1084,   580,
     294,   581,  1058,   617,   665,   447,   447,   622,    83,  1087,
     434,  1127,  1113,  1065,   272,   373,   602,   230,  1066,  1068,
    1087,   428,  1127,   434,   704,   704,   167,   434,  1087,   730,
     731,   136,   471,    56,   435,   494,   121,   191,   230,   237,
     249,   308,   371,   374,   375,   440,   515,   516,   517,   520,
     528,   393,   525,  1087,   511,   377,  1145,   509,     1,     4,
      19,    29,   198,   227,   234,   279,   285,   312,   319,   332,
     357,   359,   367,   398,   447,   544,   545,   549,   551,   556,
     557,   558,   559,   563,   564,   565,   566,   567,   568,   569,
     570,  1110,  1087,   310,   666,   667,   668,   706,   629,   626,
    1127,   396,   600,   228,  1131,   396,  1120,   196,  1126,   434,
    1127,  1127,   731,     1,   434,   732,   733,   734,   735,   736,
     741,   476,   517,    17,   393,  1090,  1087,  1127,   511,  1132,
     312,   396,  1150,   357,  1132,  1127,    55,  1119,    37,   110,
     214,  1117,  1129,  1129,  1087,  1152,   377,  1127,   704,   668,
     707,     1,    21,    34,    37,    38,    39,    40,    41,    42,
      43,    73,    75,    76,    77,    78,    79,    80,   115,   197,
     213,   247,   269,   284,   291,   293,   306,   316,   323,   360,
     362,   363,   364,   386,   411,   412,   413,   424,   427,   630,
     631,   632,   634,   635,   636,   637,   638,   639,   648,   649,
     651,   652,   653,   658,   659,  1127,  1143,    27,  1115,   184,
    1087,    56,   314,   596,   607,  1087,   365,  1144,   230,   604,
    1084,   604,   123,   447,   349,     3,     5,    10,    18,    51,
      52,    59,    70,    74,    86,   108,   115,   116,   146,   158,
     162,   175,   182,   185,   186,   193,   200,   202,   205,   240,
     244,   246,   253,   275,   290,   311,   320,   333,   338,   340,
     348,   358,   367,   376,   378,   379,   382,   384,   389,   404,
     409,   414,   425,   437,   447,   742,   743,   753,   758,   762,
     765,   778,   781,   786,   791,   792,   793,   796,   798,   805,
     809,   811,   826,   829,   831,   833,   836,   838,   844,   853,
     855,   872,   874,   877,   881,   887,   897,   904,   906,   909,
     913,   914,   925,   936,   946,   952,   955,   961,   965,   967,
     969,   971,   974,   985,   986,   995,   997,   998,   447,   518,
     520,  1069,  1127,  1129,   120,   164,   547,  1127,   312,   319,
     564,  1127,  1127,   357,  1127,  1127,  1114,     9,   254,   311,
     571,  1127,   434,   669,   623,   628,   708,   709,   710,   221,
     361,   410,   361,   410,   361,   410,   361,   410,   361,   410,
     430,  1151,   339,  1140,  1087,  1083,  1084,  1084,   210,   220,
     339,   650,  1127,  1128,   164,   184,   219,   403,     9,    50,
     221,   627,  1088,  1089,  1090,    30,   608,   609,   610,   611,
    1116,  1152,  1120,   176,   599,  1125,   106,   230,   737,   744,
     754,   759,   763,   766,   779,   782,   787,   794,   797,   799,
     806,   810,   812,   827,   830,   832,  1150,   837,     1,   839,
     845,   854,   856,   873,   875,   878,   882,   888,   898,   905,
     907,   910,   915,   926,   937,   947,   230,   342,   956,   962,
     299,   966,   968,   970,   972,   975,   184,   987,  1124,   999,
     191,   230,   237,   308,   371,   440,   519,   521,   120,   309,
     357,   550,  1127,   114,   298,   546,    32,   161,   238,   560,
    1068,   374,  1066,  1066,   280,  1137,  1137,   274,  1066,    60,
      87,    88,   286,   447,   670,   671,   675,  1127,   624,   710,
     440,   396,   640,   450,  1085,  1086,   393,   637,   655,   656,
    1088,    27,   633,   355,  1106,  1106,  1090,   270,  1134,  1134,
     454,    48,   402,   171,   600,  1087,   447,   447,   745,  1082,
    1083,     6,    81,    92,    96,   180,   221,   226,   232,   235,
     267,   335,   380,   381,   405,   423,   431,   755,  1052,  1072,
    1073,  1082,  1088,  1091,   434,   760,  1039,  1040,  1041,   230,
    1062,  1063,  1064,  1084,   230,  1080,  1082,  1091,   780,   783,
     788,  1053,  1054,  1073,  1058,   398,   230,   800,  1072,  1079,
    1082,   807,  1073,   230,   397,   401,   813,   814,  1039,   289,
     290,   303,   349,   828,     6,  1070,  1071,  1082,  1082,   834,
     133,  1038,  1039,  1070,   674,  1082,   857,  1082,  1088,  1091,
     938,  1084,    92,   876,  1073,   879,  1073,   883,   174,   230,
     889,   892,   893,   894,  1062,  1080,  1084,  1152,  1058,  1055,
    1084,  1058,  1055,     9,   916,  1056,  1084,   147,   242,   927,
     928,   929,   930,   932,   933,   934,   935,  1059,  1060,  1070,
     938,  1058,   953,   109,   957,   958,  1073,    92,   963,  1072,
     674,  1082,  1058,  1082,     8,    35,   989,   104,  1055,    17,
    1066,   115,   230,   548,  1084,   433,   561,   561,   369,   448,
     555,  1066,  1067,  1127,   169,   672,   673,   672,  1128,   683,
     184,   711,  1087,   395,  1149,   221,   441,   442,   450,  1049,
    1051,  1052,  1074,  1082,  1089,  1091,   450,  1086,  1084,   654,
     656,   393,   230,  1119,  1083,  1083,  1090,  1068,  1068,  1116,
    1120,   124,   752,    30,   176,   746,  1116,  1134,   450,  1082,
     450,  1092,   450,  1093,  1134,  1107,   450,   450,   450,   450,
     450,   450,   450,   450,  1092,   125,   757,   396,   756,  1073,
     201,  1101,    56,  1042,  1043,   396,  1107,   426,   767,   230,
    1079,  1082,  1058,   127,   789,   153,   448,   790,  1054,   341,
    1105,   312,  1139,  1057,   129,   804,   746,   419,   420,   421,
     422,   130,   808,    49,   206,   767,    17,   430,   815,   816,
     817,   821,  1112,    98,  1134,  1071,  1061,   392,  1148,   846,
    1152,  1082,    91,   324,   387,   858,   859,   860,   864,   869,
     940,  1073,   396,   134,   880,    49,   163,   203,   211,   281,
     884,   893,   135,   890,   415,   428,   393,   395,   390,   252,
     297,  1102,   176,  1000,  1139,  1000,  1056,   140,   924,   428,
     918,  1077,  1082,  1089,   933,   935,  1070,   396,  1060,   118,
     396,   416,   931,   948,   183,   334,   954,  1118,   206,   958,
    1082,   143,   964,   176,   176,   312,   314,   973,   109,   976,
     326,   373,   990,  1135,  1000,   521,   119,   433,   555,  1100,
    1109,   234,   340,  1127,   552,   553,  1079,   674,   681,  1087,
     623,   684,   712,   111,   641,  1134,  1051,  1051,  1051,    69,
     353,   449,  1050,   441,   442,   443,   444,   446,   453,  1051,
    1151,  1088,  1131,  1068,   111,   598,  1077,    25,    26,    66,
      68,   100,   101,   102,   147,   149,   157,   228,   394,   434,
    1060,   433,   749,    65,   227,   294,   747,   748,   146,   303,
    1075,  1083,  1049,  1051,   396,  1051,  1049,  1094,  1083,  1089,
    1091,   434,  1051,  1097,  1051,  1051,  1096,  1051,  1049,  1049,
    1051,  1095,  1051,  1053,  1073,   183,   334,   761,  1101,    12,
      13,    14,    20,    58,   153,   154,   181,   187,   210,   218,
     222,   250,   251,   255,   265,   272,   277,   295,   440,   441,
     442,   443,   444,   446,   448,   449,   451,   452,  1044,  1045,
    1046,  1047,  1048,   210,   250,   255,   441,   442,   446,   450,
    1044,  1045,  1046,  1047,  1048,  1073,   302,   764,  1064,   768,
     183,   334,   772,   317,   408,   784,   785,  1152,  1039,   209,
     259,  1031,  1032,  1033,  1035,   418,   433,   801,  1152,   160,
    1006,  1007,  1006,  1006,  1006,  1073,  1053,  1073,    21,   397,
     401,   822,   823,  1040,   131,   825,   432,   817,   819,   430,
     818,   814,  1083,   111,   835,  1062,   840,     9,    12,    15,
      16,   247,   248,   265,   266,   847,   851,   168,  1077,     9,
      56,   170,   219,   403,   865,   866,   867,   861,   859,   942,
    1109,  1135,   396,  1070,  1053,  1073,   359,   885,   738,   739,
    1038,   895,   896,  1082,  1062,     8,    35,  1002,  1139,  1079,
     206,   899,   911,  1152,   919,  1116,  1082,   919,   396,   396,
     512,   146,   397,   401,  1073,    49,   214,   949,  1073,  1073,
     365,  1073,  1082,   176,  1053,  1073,  1077,  1118,   206,   979,
    1082,   156,   160,   991,     9,   996,  1062,   911,   119,   552,
     273,   554,  1066,   554,   189,   676,   227,   228,   682,   434,
     624,    31,    33,    36,    44,    45,    46,    65,   155,   173,
     176,   177,   190,   227,   236,   269,   283,   307,   331,   336,
     350,   396,   407,   426,   447,   635,   636,   638,   648,   651,
     653,   713,   716,  1135,   642,   643,  1083,  1089,  1091,   449,
    1051,  1051,  1051,  1051,  1051,  1051,   449,  1051,   358,  1141,
    1131,  1135,  1005,  1007,   439,   438,  1077,  1005,   214,    31,
      33,    36,    46,   173,   177,   190,   236,   283,   307,   331,
     336,   346,   350,   407,   417,   750,   751,  1005,   263,  1133,
    1133,  1133,   748,   747,   230,  1076,  1083,   449,  1082,   453,
     449,  1050,   449,   449,  1050,   449,   449,   449,   449,  1050,
     449,   449,   366,  1011,  1012,  1053,  1071,   334,  1150,   391,
    1147,  1147,   396,  1062,   769,   770,   771,  1118,  1082,  1082,
     160,   282,   773,   992,  1124,   234,   254,  1011,  1034,  1036,
     128,   795,  1035,    94,   298,   434,  1060,    33,    36,    44,
      45,    46,   155,   173,   190,   236,   283,   336,   346,   407,
     802,   803,  1006,   262,  1008,   258,  1009,   183,  1011,   183,
    1112,   393,   824,   820,   822,   738,  1135,   738,  1150,   324,
     848,  1150,   396,    49,   866,   868,  1077,     9,    56,   219,
     403,   862,   863,  1077,   943,  1110,   196,   278,  1136,    28,
     112,   644,  1070,  1011,   183,  1152,  1057,   135,   891,   740,
       8,   176,   899,  1082,   123,   256,  1021,  1022,  1024,  1031,
     234,   254,   430,   123,   430,   921,   922,  1077,  1076,  1073,
    1127,  1031,   959,  1152,  1082,  1011,   183,   396,     9,   977,
     978,  1099,   980,  1082,   959,   980,   300,   994,   301,  1001,
    1002,  1100,   245,   312,   314,   562,  1127,   170,   677,  1087,
     685,  1127,  1133,   150,   152,  1127,  1080,  1133,  1087,  1082,
    1082,  1066,   198,   645,   644,   449,  1150,  1066,  1009,  1005,
    1127,  1127,   118,   416,   751,  1079,  1079,  1079,  1092,  1105,
     449,  1051,  1066,  1092,  1092,  1051,  1092,  1092,  1092,   219,
     403,  1092,  1092,  1013,   261,  1014,  1011,  1071,   153,   277,
     153,   277,   770,   272,   726,    85,   318,   427,   258,   260,
     775,   993,   774,   322,   337,   738,   738,   801,   801,   801,
     801,  1127,   150,   152,  1127,   118,   416,   803,   738,  1010,
    1053,  1054,  1053,  1054,   823,  1039,   738,  1082,   122,   841,
     427,   849,   850,   851,   107,   852,   427,  1078,  1082,  1088,
    1077,    49,   870,   863,   172,   870,   939,  1127,   278,  1129,
    1053,   571,   886,  1152,   741,   896,  1073,   195,   900,  1152,
    1023,  1025,   138,   908,  1024,   139,   912,   234,  1039,   920,
    1038,   921,   255,   950,  1103,   141,   951,   282,  1016,  1017,
     293,  1105,  1053,  1078,   277,  1077,   110,   981,   387,   983,
    1135,   151,   257,  1003,  1026,  1027,  1029,  1032,     7,  1111,
     562,  1087,   113,   216,   678,    66,    65,    66,   188,   227,
     228,   252,   296,   369,   383,   406,   428,   447,   635,   636,
     638,   639,   648,   651,   653,   686,   687,   689,   690,   691,
     692,   694,   695,   696,   697,   701,   702,   440,  1081,  1082,
    1087,  1127,  1081,  1127,  1149,  1118,  1129,   397,   657,  1081,
    1081,  1037,  1118,  1037,  1011,   449,   738,  1015,  1150,   153,
    1150,   153,  1073,   126,   777,   776,   738,  1006,  1006,  1006,
    1006,  1081,  1081,  1037,  1037,   738,  1011,   321,  1011,   321,
     842,   133,   843,   850,    99,  1122,   870,   870,  1078,  1002,
     203,   426,   944,  1066,   941,  1011,   234,   254,    49,   234,
     214,   901,   194,   234,   254,   429,   738,   738,   917,   738,
     923,   674,  1044,  1045,  1046,  1047,  1048,  1018,   142,   960,
     260,  1019,  1082,  1011,  1011,   978,  1126,    93,   982,  1126,
    1016,   163,   203,   211,   281,   988,  1057,  1028,  1030,   145,
    1004,  1029,   286,  1060,  1081,  1127,    90,   217,   679,   264,
    1133,   199,   703,   263,   264,   700,  1113,   188,   430,  1127,
    1134,  1127,  1082,   692,   252,   292,   698,   699,  1087,   241,
     292,   441,   442,   715,   241,   292,   441,   442,   714,   434,
     646,   647,  1127,  1127,  1081,   738,  1150,  1150,   738,  1054,
    1054,   738,    49,   870,   399,   871,   300,  1057,   183,   281,
     945,  1084,   337,  1073,  1127,   902,  1021,  1032,   234,   234,
     738,   738,   738,  1020,  1082,  1126,  1082,   144,   984,   738,
     738,   227,   228,  1130,  1087,  1127,  1127,   171,   680,  1127,
    1128,  1127,  1038,  1082,   693,  1066,    89,    90,   113,   287,
     288,   328,   329,   688,   176,   286,  1087,   699,  1081,  1081,
     647,  1065,  1088,  1130,  1011,  1011,  1073,  1073,  1127,  1057,
     300,   415,   674,   137,   903,   738,  1082,  1087,  1087,  1127,
    1087,  1087,  1105,  1073,   892,  1127,  1038,  1087,    49,   892,
    1073
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
#line 763 "parser.y"
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
#line 787 "parser.y"
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
#line 816 "parser.y"
    { cb_validate_program_environment (current_program); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 817 "parser.y"
    { cb_validate_program_data (current_program); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 825 "parser.y"
    { cb_validate_program_environment (current_program); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 826 "parser.y"
    { cb_validate_program_data (current_program); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 834 "parser.y"
    { cb_validate_program_environment (current_program); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 835 "parser.y"
    { cb_validate_program_data (current_program); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 847 "parser.y"
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
#line 873 "parser.y"
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
#line 897 "parser.y"
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
#line 926 "parser.y"
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
#line 967 "parser.y"
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
#line 1015 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 1016 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 1025 "parser.y"
    {
	if (!current_program->nested_level) {
		cb_error (_("COMMON may only be used in a nested program"));
	}
	current_program->flag_common = 1;
  ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 1032 "parser.y"
    {
	if (!current_program->nested_level) {
		cb_error (_("COMMON may only be used in a nested program"));
	}
	current_program->flag_common = 1;
  ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 1043 "parser.y"
    {
	current_program->flag_initial = 1;
  ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 1047 "parser.y"
    {
	current_program->flag_recursive = 1;
	current_program->flag_initial = 1;
  ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 1072 "parser.y"
    {
	if (current_program->nested_level) {
		cb_error (_("CONFIGURATION SECTION not allowed in nested programs"));
	}
  ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 1107 "parser.y"
    {
	cb_verify (cb_debugging_line, "DEBUGGING MODE");
  ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 1113 "parser.y"
    { ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 1144 "parser.y"
    {
	cb_verify (cb_memory_size_clause, "MEMORY SIZE");
  ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 1156 "parser.y"
    {
	current_program->collating_sequence = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1163 "parser.y"
    {
	/* Ignore */
  ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 1188 "parser.y"
    {
	current_program->function_spec_list = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 1192 "parser.y"
    {
	functions_are_all = 1;
  ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1198 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1200 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1240 "parser.y"
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
#line 1250 "parser.y"
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
#line 1261 "parser.y"
    {
	save_tree_1 = lookup_system_name (CB_NAME ((yyvsp[(1) - (2)])));
	if (save_tree_1 == cb_error_node) {
		cb_error_x ((yyvsp[(1) - (2)]), _("Unknown system-name '%s'"), CB_NAME ((yyvsp[(1) - (2)])));
	}
	save_tree_2 = NULL;
  ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 1270 "parser.y"
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

  case 101:

/* Line 1455 of yacc.c  */
#line 1284 "parser.y"
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

  case 102:

/* Line 1455 of yacc.c  */
#line 1298 "parser.y"
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

  case 103:

/* Line 1455 of yacc.c  */
#line 1312 "parser.y"
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

  case 108:

/* Line 1455 of yacc.c  */
#line 1338 "parser.y"
    {
	if (!save_tree_2 && !cb_switch_no_mnemonic) {
		cb_error_x ((yyvsp[(4) - (4)]), _("'%s' with no mnemonic name"), CB_NAME ((yyvsp[(4) - (4)])));
	} else {
		cb_define_switch_name ((yyvsp[(4) - (4)]), save_tree_1, (yyvsp[(1) - (4)]), save_tree_2);
	}
  ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1348 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1349 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1357 "parser.y"
    {
	save_tree_1 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1361 "parser.y"
    {
	current_program->alphabet_name_list =
		cb_list_add (current_program->alphabet_name_list, (yyvsp[(5) - (5)]));
  ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1368 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_NATIVE); ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1369 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_1); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1370 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_2); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1371 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_EBCDIC); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1373 "parser.y"
    {
	(yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_CUSTOM);
	CB_ALPHABET_NAME ((yyval))->custom_list = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1380 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1382 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1386 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1387 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1389 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (2)]));
	save_tree_2 = (yyval);
  ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1394 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (4)]);
  ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1405 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1406 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1407 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1408 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1409 "parser.y"
    { (yyval) = cb_norm_high; ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1410 "parser.y"
    { (yyval) = cb_norm_low; ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1414 "parser.y"
    { cb_list_add (save_tree_2, (yyvsp[(1) - (1)])); ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1415 "parser.y"
    { cb_list_add (save_tree_2, cb_space); ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1416 "parser.y"
    { cb_list_add (save_tree_2, cb_zero); ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1417 "parser.y"
    { cb_list_add (save_tree_2, cb_quote); ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1418 "parser.y"
    { cb_list_add (save_tree_2, cb_norm_high); ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1419 "parser.y"
    { cb_list_add (save_tree_2, cb_norm_low); ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1427 "parser.y"
    {
	if ((yyvsp[(3) - (3)])) {
		current_program->symbolic_list =
			cb_list_add (current_program->symbolic_list, (yyvsp[(3) - (3)]));
	}
	PENDING ("SYMBOLIC CHARACTERS");
  ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1438 "parser.y"
    {
	if (cb_list_length ((yyvsp[(1) - (3)])) != cb_list_length ((yyvsp[(3) - (3)]))) {
		cb_error (_("Invalid SYMBOLIC clause"));
		(yyval) = NULL;
	} else {
		(yyval) = NULL;
	}
  ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1449 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1450 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1454 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1455 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1463 "parser.y"
    {
	current_program->class_name_list =
			cb_list_add (current_program->class_name_list,
			cb_build_class_name ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])));
  ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1471 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1472 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1476 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1478 "parser.y"
    {
	/* if (CB_LITERAL ($1)->data[0] < CB_LITERAL ($3)->data[0]) */
	if (literal_value ((yyvsp[(1) - (3)])) < literal_value ((yyvsp[(3) - (3)]))) {
		(yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	} else {
		(yyval) = cb_build_pair ((yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]));
	}
  ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1492 "parser.y"
    {
	cb_tree	l;

	l = cb_build_locale_name ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
	if (l != cb_error_node) {
		current_program->locale_list =
			cb_list_add (current_program->locale_list, l);
	}
  ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1507 "parser.y"
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

  case 151:

/* Line 1455 of yacc.c  */
#line 1574 "parser.y"
    {
	current_program->decimal_point = ',';
	current_program->numeric_separator = '.';
  ;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 1584 "parser.y"
    { current_program->cursor_pos = (yyvsp[(3) - (3)]); ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1591 "parser.y"
    { current_program->crt_status = (yyvsp[(4) - (4)]); ;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 1598 "parser.y"
    {  PENDING ("SCREEN CONTROL"); ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1604 "parser.y"
    {  PENDING ("EVENT STATUS"); ;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 1616 "parser.y"
    {
	/* hack for MF compatibility */
	if (cb_relaxed_syntax_check) {
		cb_warning (_("INPUT-OUTPUT SECTION header missing - assumed"));
	} else {
		cb_error (_("INPUT-OUTPUT SECTION header missing"));
	}
  ;}
    break;

  case 160:

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

  case 166:

/* Line 1455 of yacc.c  */
#line 1650 "parser.y"
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

  case 167:

/* Line 1455 of yacc.c  */
#line 1665 "parser.y"
    {
	validate_file (current_file, (yyvsp[(3) - (6)]));
  ;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1696 "parser.y"
    {
	current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
  ;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1700 "parser.y"
    {
	current_file->fileid_assign = 1;
	current_file->assign = cb_build_assignment_name (current_file, cb_build_reference ("DISK"));
  ;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1705 "parser.y"
    {
	current_file->fileid_assign = 1;
	current_file->assign = cb_build_assignment_name (current_file, cb_build_reference ("PRINTER"));
  ;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1713 "parser.y"
    { current_file->organization = COB_ORG_LINE_SEQUENTIAL; ;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1718 "parser.y"
    {
	current_file->external_assign = 1;
  ;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1722 "parser.y"
    {
	current_file->external_assign = 0;
  ;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1730 "parser.y"
    {
	const char	*s;

	s = "$#@DUMMY@#$";
	(yyval) = cb_build_alphanumeric_literal ((unsigned char *)s, strlen (s));
  ;}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 1747 "parser.y"
    { current_file->access_mode = COB_ACCESS_SEQUENTIAL; ;}
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 1748 "parser.y"
    { current_file->access_mode = COB_ACCESS_DYNAMIC; ;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1749 "parser.y"
    { current_file->access_mode = COB_ACCESS_RANDOM; ;}
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 1757 "parser.y"
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

  case 201:

/* Line 1455 of yacc.c  */
#line 1777 "parser.y"
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

  case 202:

/* Line 1455 of yacc.c  */
#line 1823 "parser.y"
    {
	key_component_list = NULL;
  ;}
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 1832 "parser.y"
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

  case 206:

/* Line 1455 of yacc.c  */
#line 1847 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 1848 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 1849 "parser.y"
    { (yyval) = cb_int('='); ;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1856 "parser.y"
    {
	PENDING ("COLLATING SEQUENCE");
  ;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1866 "parser.y"
    {
	current_file->file_status = (yyvsp[(4) - (5)]);
	if ((yyvsp[(5) - (5)])) {
		PENDING ("2nd FILE STATUS");
	}
  ;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1887 "parser.y"
    { current_file->lock_mode = COB_LOCK_MANUAL; ;}
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 1888 "parser.y"
    { current_file->lock_mode = COB_LOCK_AUTOMATIC; ;}
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 1889 "parser.y"
    { current_file->lock_mode = COB_LOCK_EXCLUSIVE; ;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1895 "parser.y"
    {
	current_file->lock_mode |= COB_LOCK_MULTIPLE;
  ;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 1898 "parser.y"
    { PENDING ("WITH ROLLBACK"); ;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1915 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_INDEXED;
		organized_seen = 1;
	}
  ;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1924 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_SEQUENTIAL;
		organized_seen = 1;
	}
  ;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 1933 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = cb_default_organization;
		organized_seen = 1;
	}
  ;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 1942 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_RELATIVE;
		organized_seen = 1;
	}
  ;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 1951 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_LINE_SEQUENTIAL;
		organized_seen = 1;
	}
  ;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 1966 "parser.y"
    {
	cb_verify (cb_padding_character_clause, "PADDING CHARACTER");
  ;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 1975 "parser.y"
    { /* ignored */ ;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 1983 "parser.y"
    {
	current_file->key = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 1987 "parser.y"
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

  case 235:

/* Line 1455 of yacc.c  */
#line 2024 "parser.y"
    { current_file->key = (yyvsp[(4) - (4)]); ;}
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 2031 "parser.y"
    { /* ignored */ ;}
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 2038 "parser.y"
    { current_file->sharing = (yyvsp[(3) - (3)]); ;}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 2042 "parser.y"
    { (yyval) = NULL; PENDING ("SHARING ALL OTHER"); ;}
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 2043 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 2044 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 2075 "parser.y"
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

  case 251:

/* Line 1455 of yacc.c  */
#line 2099 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 2100 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 2101 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 2102 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 2109 "parser.y"
    {
	cb_verify (cb_multiple_file_tape_clause, "MULTIPLE FILE TAPE");
  ;}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 2120 "parser.y"
    { ;}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 2131 "parser.y"
    {
	PENDING ("APPLY COMMITMENT-CONTROL");
  ;}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 2156 "parser.y"
    { current_storage = CB_STORAGE_FILE; ;}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 2159 "parser.y"
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

  case 271:

/* Line 1455 of yacc.c  */
#line 2178 "parser.y"
    {
	if ((yyvsp[(3) - (3)]) && (yyvsp[(3) - (3)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(3) - (3)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 2190 "parser.y"
    {
	if ((yyvsp[(2) - (2)]) && (yyvsp[(2) - (2)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(2) - (2)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 2201 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 2202 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 2212 "parser.y"
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

  case 277:

/* Line 1455 of yacc.c  */
#line 2223 "parser.y"
    {
	/* Shut up bison */
	dummy_tree = (yyvsp[(2) - (4)]);
  ;}
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 2235 "parser.y"
    {
	if (current_file->global) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->external = 1;
  ;}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 2242 "parser.y"
    {
	if (current_file->external) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->global = 1;
  ;}
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 2265 "parser.y"
    { /* ignored */ ;}
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 2275 "parser.y"
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

  case 297:

/* Line 1455 of yacc.c  */
#line 2287 "parser.y"
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

  case 298:

/* Line 1455 of yacc.c  */
#line 2313 "parser.y"
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

  case 300:

/* Line 1455 of yacc.c  */
#line 2337 "parser.y"
    {
	current_file->record_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 2343 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 2344 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 2348 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 2349 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 2357 "parser.y"
    {
	cb_verify (cb_label_records_clause, "LABEL RECORDS");
  ;}
    break;

  case 308:

/* Line 1455 of yacc.c  */
#line 2372 "parser.y"
    {
	cb_verify (cb_value_of_clause, "VALUE OF");
  ;}
    break;

  case 309:

/* Line 1455 of yacc.c  */
#line 2376 "parser.y"
    {
	if (!current_file->assign) {
		current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 2392 "parser.y"
    {
	cb_verify (cb_data_records_clause, "DATA RECORDS");
  ;}
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 2403 "parser.y"
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

  case 319:

/* Line 1455 of yacc.c  */
#line 2431 "parser.y"
    {
	current_file->latfoot = (yyvsp[(4) - (5)]);
  ;}
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 2438 "parser.y"
    {
	current_file->lattop = (yyvsp[(3) - (4)]);
  ;}
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 2445 "parser.y"
    {
	current_file->latbot = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 2454 "parser.y"
    { /* ignore */ ;}
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 2462 "parser.y"
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

  case 324:

/* Line 1455 of yacc.c  */
#line 2480 "parser.y"
    {
	cb_warning (_("file descriptor REPORT IS"));
  ;}
    break;

  case 325:

/* Line 1455 of yacc.c  */
#line 2484 "parser.y"
    {
	cb_warning (_("file descriptor REPORTS ARE"));
  ;}
    break;

  case 327:

/* Line 1455 of yacc.c  */
#line 2495 "parser.y"
    { current_storage = CB_STORAGE_WORKING; ;}
    break;

  case 328:

/* Line 1455 of yacc.c  */
#line 2497 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->working_storage =
			cb_field_add (current_program->working_storage, CB_FIELD ((yyvsp[(5) - (5)])));
	}
  ;}
    break;

  case 329:

/* Line 1455 of yacc.c  */
#line 2506 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 2507 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 2511 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 2517 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	(yyval) = CB_TREE (description_field);
  ;}
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 2537 "parser.y"
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

  case 338:

/* Line 1455 of yacc.c  */
#line 2548 "parser.y"
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

  case 340:

/* Line 1455 of yacc.c  */
#line 2572 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 341:

/* Line 1455 of yacc.c  */
#line 2578 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 342:

/* Line 1455 of yacc.c  */
#line 2584 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 343:

/* Line 1455 of yacc.c  */
#line 2593 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 345:

/* Line 1455 of yacc.c  */
#line 2602 "parser.y"
    {
	current_field->flag_is_global = 1;
	cb_error (_("CONSTANT with GLOBAL clause is not yet supported"));
  ;}
    break;

  case 346:

/* Line 1455 of yacc.c  */
#line 2609 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 347:

/* Line 1455 of yacc.c  */
#line 2610 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 348:

/* Line 1455 of yacc.c  */
#line 2611 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 349:

/* Line 1455 of yacc.c  */
#line 2616 "parser.y"
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

  case 350:

/* Line 1455 of yacc.c  */
#line 2635 "parser.y"
    {
	/* required to check redefines */
	(yyval) = NULL;
  ;}
    break;

  case 351:

/* Line 1455 of yacc.c  */
#line 2641 "parser.y"
    {
	/* required to check redefines */
	(yyval) = cb_true;
  ;}
    break;

  case 367:

/* Line 1455 of yacc.c  */
#line 2670 "parser.y"
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

  case 368:

/* Line 1455 of yacc.c  */
#line 2692 "parser.y"
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

  case 369:

/* Line 1455 of yacc.c  */
#line 2713 "parser.y"
    { current_field->ename = NULL; ;}
    break;

  case 370:

/* Line 1455 of yacc.c  */
#line 2715 "parser.y"
    {
	struct cb_field *x;

	x = CB_FIELD(cb_build_field (cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(2) - (2)]))->data))));
	current_field->ename = x->name;
 ;}
    break;

  case 371:

/* Line 1455 of yacc.c  */
#line 2727 "parser.y"
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

  case 372:

/* Line 1455 of yacc.c  */
#line 2746 "parser.y"
    { current_field->pic = CB_PICTURE ((yyvsp[(1) - (1)])); ;}
    break;

  case 375:

/* Line 1455 of yacc.c  */
#line 2758 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 376:

/* Line 1455 of yacc.c  */
#line 2759 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 377:

/* Line 1455 of yacc.c  */
#line 2760 "parser.y"
    { current_field->usage = CB_USAGE_FLOAT; ;}
    break;

  case 378:

/* Line 1455 of yacc.c  */
#line 2761 "parser.y"
    { current_field->usage = CB_USAGE_DOUBLE; ;}
    break;

  case 379:

/* Line 1455 of yacc.c  */
#line 2762 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 380:

/* Line 1455 of yacc.c  */
#line 2763 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 381:

/* Line 1455 of yacc.c  */
#line 2764 "parser.y"
    { current_field->usage = CB_USAGE_COMP_5; ;}
    break;

  case 382:

/* Line 1455 of yacc.c  */
#line 2765 "parser.y"
    { current_field->usage = CB_USAGE_COMP_X; ;}
    break;

  case 383:

/* Line 1455 of yacc.c  */
#line 2766 "parser.y"
    { current_field->usage = CB_USAGE_DISPLAY; ;}
    break;

  case 384:

/* Line 1455 of yacc.c  */
#line 2767 "parser.y"
    { current_field->usage = CB_USAGE_INDEX; ;}
    break;

  case 385:

/* Line 1455 of yacc.c  */
#line 2768 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 386:

/* Line 1455 of yacc.c  */
#line 2770 "parser.y"
    {
	current_field->usage = CB_USAGE_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 387:

/* Line 1455 of yacc.c  */
#line 2775 "parser.y"
    {
	current_field->usage = CB_USAGE_PROGRAM_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 388:

/* Line 1455 of yacc.c  */
#line 2779 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 389:

/* Line 1455 of yacc.c  */
#line 2780 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 390:

/* Line 1455 of yacc.c  */
#line 2781 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 391:

/* Line 1455 of yacc.c  */
#line 2782 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 392:

/* Line 1455 of yacc.c  */
#line 2783 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 393:

/* Line 1455 of yacc.c  */
#line 2784 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 394:

/* Line 1455 of yacc.c  */
#line 2785 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 395:

/* Line 1455 of yacc.c  */
#line 2786 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_CHAR; ;}
    break;

  case 396:

/* Line 1455 of yacc.c  */
#line 2787 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 397:

/* Line 1455 of yacc.c  */
#line 2788 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 398:

/* Line 1455 of yacc.c  */
#line 2789 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 399:

/* Line 1455 of yacc.c  */
#line 2790 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 400:

/* Line 1455 of yacc.c  */
#line 2791 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 401:

/* Line 1455 of yacc.c  */
#line 2792 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 402:

/* Line 1455 of yacc.c  */
#line 2793 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 403:

/* Line 1455 of yacc.c  */
#line 2794 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 404:

/* Line 1455 of yacc.c  */
#line 2795 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 405:

/* Line 1455 of yacc.c  */
#line 2796 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 406:

/* Line 1455 of yacc.c  */
#line 2798 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  ;}
    break;

  case 407:

/* Line 1455 of yacc.c  */
#line 2806 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_UNSIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_UNSIGNED_LONG;
	}
  ;}
    break;

  case 408:

/* Line 1455 of yacc.c  */
#line 2814 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  ;}
    break;

  case 409:

/* Line 1455 of yacc.c  */
#line 2821 "parser.y"
    { PENDING ("USAGE NATIONAL");;}
    break;

  case 410:

/* Line 1455 of yacc.c  */
#line 2829 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 1;
  ;}
    break;

  case 411:

/* Line 1455 of yacc.c  */
#line 2834 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 0;
  ;}
    break;

  case 412:

/* Line 1455 of yacc.c  */
#line 2846 "parser.y"
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

  case 413:

/* Line 1455 of yacc.c  */
#line 2861 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 414:

/* Line 1455 of yacc.c  */
#line 2862 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 416:

/* Line 1455 of yacc.c  */
#line 2867 "parser.y"
    {
	current_field->occurs_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 417:

/* Line 1455 of yacc.c  */
#line 2874 "parser.y"
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

  case 418:

/* Line 1455 of yacc.c  */
#line 2897 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 419:

/* Line 1455 of yacc.c  */
#line 2900 "parser.y"
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

  case 420:

/* Line 1455 of yacc.c  */
#line 2915 "parser.y"
    { (yyval) = cb_int (COB_ASCENDING); ;}
    break;

  case 421:

/* Line 1455 of yacc.c  */
#line 2916 "parser.y"
    { (yyval) = cb_int (COB_DESCENDING); ;}
    break;

  case 423:

/* Line 1455 of yacc.c  */
#line 2921 "parser.y"
    {
	current_field->index_list = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 424:

/* Line 1455 of yacc.c  */
#line 2927 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 425:

/* Line 1455 of yacc.c  */
#line 2929 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 426:

/* Line 1455 of yacc.c  */
#line 2934 "parser.y"
    {
	(yyval) = cb_build_index ((yyvsp[(1) - (1)]), cb_int1, 1, current_field);
  ;}
    break;

  case 427:

/* Line 1455 of yacc.c  */
#line 2943 "parser.y"
    { current_field->flag_justified = 1; ;}
    break;

  case 428:

/* Line 1455 of yacc.c  */
#line 2950 "parser.y"
    { current_field->flag_synchronized = 1; ;}
    break;

  case 432:

/* Line 1455 of yacc.c  */
#line 2962 "parser.y"
    { current_field->flag_blank_zero = 1; ;}
    break;

  case 433:

/* Line 1455 of yacc.c  */
#line 2970 "parser.y"
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

  case 434:

/* Line 1455 of yacc.c  */
#line 2994 "parser.y"
    { current_field->values = (yyvsp[(3) - (3)]); ;}
    break;

  case 436:

/* Line 1455 of yacc.c  */
#line 2999 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 437:

/* Line 1455 of yacc.c  */
#line 3000 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 438:

/* Line 1455 of yacc.c  */
#line 3004 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 439:

/* Line 1455 of yacc.c  */
#line 3005 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 441:

/* Line 1455 of yacc.c  */
#line 3010 "parser.y"
    {
	if (current_field->level != 88) {
		cb_error (_("FALSE clause only allowed for 88 level"));
	}
	current_field->false_88 = cb_list_init ((yyvsp[(3) - (3)]));
  ;}
    break;

  case 442:

/* Line 1455 of yacc.c  */
#line 3023 "parser.y"
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

  case 443:

/* Line 1455 of yacc.c  */
#line 3035 "parser.y"
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

  case 444:

/* Line 1455 of yacc.c  */
#line 3055 "parser.y"
    {
	if (current_field->flag_item_based) {
		cb_error (_("BASED and ANY LENGTH are mutually exclusive"));
	} else {
		current_field->flag_any_length = 1;
	}
  ;}
    break;

  case 446:

/* Line 1455 of yacc.c  */
#line 3070 "parser.y"
    {
	current_storage = CB_STORAGE_LOCAL;
	if (current_program->nested_level) {
		cb_error (_("LOCAL-STORAGE not allowed in nested programs"));
	}
  ;}
    break;

  case 447:

/* Line 1455 of yacc.c  */
#line 3077 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->local_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 449:

/* Line 1455 of yacc.c  */
#line 3090 "parser.y"
    { current_storage = CB_STORAGE_LINKAGE; ;}
    break;

  case 450:

/* Line 1455 of yacc.c  */
#line 3092 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->linkage_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 452:

/* Line 1455 of yacc.c  */
#line 3105 "parser.y"
    {
	cb_error (_("REPORT SECTION not supported"));
	current_storage = CB_STORAGE_REPORT;
  ;}
    break;

  case 459:

/* Line 1455 of yacc.c  */
#line 3138 "parser.y"
    {
	cb_warning (_("Report description using defaults"));
  ;}
    break;

  case 461:

/* Line 1455 of yacc.c  */
#line 3146 "parser.y"
    {
	cb_error (_("GLOBAL is not allowed with RD"));
  ;}
    break;

  case 470:

/* Line 1455 of yacc.c  */
#line 3169 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 471:

/* Line 1455 of yacc.c  */
#line 3170 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 493:

/* Line 1455 of yacc.c  */
#line 3226 "parser.y"
    { cb_warning (_("looking for Report line TYPE")); ;}
    break;

  case 544:

/* Line 1455 of yacc.c  */
#line 3331 "parser.y"
    { current_storage = CB_STORAGE_SCREEN; ;}
    break;

  case 545:

/* Line 1455 of yacc.c  */
#line 3332 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 546:

/* Line 1455 of yacc.c  */
#line 3338 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	current_program->screen_storage = description_field;
	current_program->flag_screen = 1;
  ;}
    break;

  case 552:

/* Line 1455 of yacc.c  */
#line 3362 "parser.y"
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

  case 553:

/* Line 1455 of yacc.c  */
#line 3378 "parser.y"
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

  case 556:

/* Line 1455 of yacc.c  */
#line 3402 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 557:

/* Line 1455 of yacc.c  */
#line 3403 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 558:

/* Line 1455 of yacc.c  */
#line 3404 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BELL; ;}
    break;

  case 559:

/* Line 1455 of yacc.c  */
#line 3405 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLINK; ;}
    break;

  case 560:

/* Line 1455 of yacc.c  */
#line 3406 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 561:

/* Line 1455 of yacc.c  */
#line 3407 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 562:

/* Line 1455 of yacc.c  */
#line 3408 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 563:

/* Line 1455 of yacc.c  */
#line 3409 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 564:

/* Line 1455 of yacc.c  */
#line 3410 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REVERSE; ;}
    break;

  case 565:

/* Line 1455 of yacc.c  */
#line 3411 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 566:

/* Line 1455 of yacc.c  */
#line 3412 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_OVERLINE; ;}
    break;

  case 567:

/* Line 1455 of yacc.c  */
#line 3413 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_AUTO; ;}
    break;

  case 568:

/* Line 1455 of yacc.c  */
#line 3414 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_SECURE; ;}
    break;

  case 569:

/* Line 1455 of yacc.c  */
#line 3415 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REQUIRED; ;}
    break;

  case 570:

/* Line 1455 of yacc.c  */
#line 3416 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_FULL; ;}
    break;

  case 571:

/* Line 1455 of yacc.c  */
#line 3417 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_PROMPT; ;}
    break;

  case 572:

/* Line 1455 of yacc.c  */
#line 3419 "parser.y"
    {
	current_field->screen_line = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 573:

/* Line 1455 of yacc.c  */
#line 3423 "parser.y"
    {
	current_field->screen_column = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 574:

/* Line 1455 of yacc.c  */
#line 3427 "parser.y"
    {
	current_field->screen_foreg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 575:

/* Line 1455 of yacc.c  */
#line 3431 "parser.y"
    {
	current_field->screen_backg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 583:

/* Line 1455 of yacc.c  */
#line 3442 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 584:

/* Line 1455 of yacc.c  */
#line 3449 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 585:

/* Line 1455 of yacc.c  */
#line 3453 "parser.y"
    {
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 586:

/* Line 1455 of yacc.c  */
#line 3462 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 587:

/* Line 1455 of yacc.c  */
#line 3466 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 588:

/* Line 1455 of yacc.c  */
#line 3470 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 589:

/* Line 1455 of yacc.c  */
#line 3474 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 590:

/* Line 1455 of yacc.c  */
#line 3478 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 591:

/* Line 1455 of yacc.c  */
#line 3485 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 592:

/* Line 1455 of yacc.c  */
#line 3489 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 593:

/* Line 1455 of yacc.c  */
#line 3493 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 594:

/* Line 1455 of yacc.c  */
#line 3497 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 595:

/* Line 1455 of yacc.c  */
#line 3501 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 596:

/* Line 1455 of yacc.c  */
#line 3509 "parser.y"
    {
	current_field->occurs_max = cb_get_int ((yyvsp[(2) - (3)]));
	current_field->occurs_min = current_field->occurs_max;
	current_field->indexes++;
	current_field->flag_occurs = 1;
  ;}
    break;

  case 598:

/* Line 1455 of yacc.c  */
#line 3523 "parser.y"
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

  case 599:

/* Line 1455 of yacc.c  */
#line 3533 "parser.y"
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

  case 600:

/* Line 1455 of yacc.c  */
#line 3543 "parser.y"
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

  case 601:

/* Line 1455 of yacc.c  */
#line 3560 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 602:

/* Line 1455 of yacc.c  */
#line 3562 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 603:

/* Line 1455 of yacc.c  */
#line 3566 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 604:

/* Line 1455 of yacc.c  */
#line 3568 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	current_program->flag_chained = 1;
  ;}
    break;

  case 605:

/* Line 1455 of yacc.c  */
#line 3572 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 606:

/* Line 1455 of yacc.c  */
#line 3576 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 607:

/* Line 1455 of yacc.c  */
#line 3578 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 608:

/* Line 1455 of yacc.c  */
#line 3583 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), cb_build_identifier ((yyvsp[(4) - (4)])));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 610:

/* Line 1455 of yacc.c  */
#line 3592 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 611:

/* Line 1455 of yacc.c  */
#line 3596 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 613:

/* Line 1455 of yacc.c  */
#line 3608 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_AUTO;
	}
  ;}
    break;

  case 614:

/* Line 1455 of yacc.c  */
#line 3616 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_4;
	}
  ;}
    break;

  case 615:

/* Line 1455 of yacc.c  */
#line 3624 "parser.y"
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

  case 616:

/* Line 1455 of yacc.c  */
#line 3653 "parser.y"
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

  case 618:

/* Line 1455 of yacc.c  */
#line 3686 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OPTIONAL only allowed for BY REFERENCE items"));
	}
  ;}
    break;

  case 619:

/* Line 1455 of yacc.c  */
#line 3695 "parser.y"
    {
	if (current_program->prog_type == CB_FUNCTION_TYPE) {
		cb_error (_("RETURNING clause is required for a FUNCTION"));
	}
  ;}
    break;

  case 620:

/* Line 1455 of yacc.c  */
#line 3701 "parser.y"
    {
	if (cb_ref ((yyvsp[(2) - (2)])) != cb_error_node) {
		current_program->returning = (yyvsp[(2) - (2)]);
		if (cb_field ((yyvsp[(2) - (2)]))->storage != CB_STORAGE_LINKAGE) {
			cb_error (_("RETURNING item is not defined in LINKAGE SECTION"));
		}
	}
  ;}
    break;

  case 622:

/* Line 1455 of yacc.c  */
#line 3712 "parser.y"
    { in_declaratives = 1; ;}
    break;

  case 623:

/* Line 1455 of yacc.c  */
#line 3715 "parser.y"
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

  case 629:

/* Line 1455 of yacc.c  */
#line 3748 "parser.y"
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

  case 630:

/* Line 1455 of yacc.c  */
#line 3764 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 631:

/* Line 1455 of yacc.c  */
#line 3776 "parser.y"
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

  case 632:

/* Line 1455 of yacc.c  */
#line 3807 "parser.y"
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

  case 633:

/* Line 1455 of yacc.c  */
#line 3844 "parser.y"
    {
	non_const_word = 0;
	check_unreached = 0;
	if ((yyvsp[(1) - (1)]) != cb_error_node) {
		cb_error_x ((yyvsp[(1) - (1)]), _("Unknown statement '%s'"), CB_NAME ((yyvsp[(1) - (1)])));
	}
	YYERROR;
  ;}
    break;

  case 634:

/* Line 1455 of yacc.c  */
#line 3855 "parser.y"
    { (yyval) = cb_build_section_name ((yyvsp[(1) - (1)]), 0); ;}
    break;

  case 636:

/* Line 1455 of yacc.c  */
#line 3859 "parser.y"
    { /* ignore */ ;}
    break;

  case 637:

/* Line 1455 of yacc.c  */
#line 3868 "parser.y"
    {
	(yyval) = current_program->exec_list;
	current_program->exec_list = NULL;
  ;}
    break;

  case 638:

/* Line 1455 of yacc.c  */
#line 3872 "parser.y"
    {
	(yyval) = CB_TREE (current_statement);
	current_statement = NULL;
  ;}
    break;

  case 639:

/* Line 1455 of yacc.c  */
#line 3877 "parser.y"
    {
	(yyval) = cb_list_reverse (current_program->exec_list);
	current_program->exec_list = (yyvsp[(1) - (3)]);
	current_statement = CB_STATEMENT ((yyvsp[(2) - (3)]));
  ;}
    break;

  case 640:

/* Line 1455 of yacc.c  */
#line 3885 "parser.y"
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

  case 691:

/* Line 1455 of yacc.c  */
#line 3957 "parser.y"
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

  case 692:

/* Line 1455 of yacc.c  */
#line 3979 "parser.y"
    {
	BEGIN_STATEMENT ("ACCEPT", TERM_ACCEPT);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 694:

/* Line 1455 of yacc.c  */
#line 3992 "parser.y"
    {
	cb_emit_accept ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 695:

/* Line 1455 of yacc.c  */
#line 3996 "parser.y"
    {
	PENDING ("ACCEPT .. FROM ESCAPE KEY");
  ;}
    break;

  case 696:

/* Line 1455 of yacc.c  */
#line 4000 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 0);
  ;}
    break;

  case 697:

/* Line 1455 of yacc.c  */
#line 4004 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 1);
  ;}
    break;

  case 698:

/* Line 1455 of yacc.c  */
#line 4008 "parser.y"
    {
	cb_emit_accept_date ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 699:

/* Line 1455 of yacc.c  */
#line 4012 "parser.y"
    {
	cb_emit_accept_date_yyyymmdd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 700:

/* Line 1455 of yacc.c  */
#line 4016 "parser.y"
    {
	cb_emit_accept_day ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 701:

/* Line 1455 of yacc.c  */
#line 4020 "parser.y"
    {
	cb_emit_accept_day_yyyyddd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 702:

/* Line 1455 of yacc.c  */
#line 4024 "parser.y"
    {
	cb_emit_accept_day_of_week ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 703:

/* Line 1455 of yacc.c  */
#line 4028 "parser.y"
    {
	cb_emit_accept_time ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 704:

/* Line 1455 of yacc.c  */
#line 4032 "parser.y"
    {
	cb_emit_accept_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 705:

/* Line 1455 of yacc.c  */
#line 4036 "parser.y"
    {
	cb_emit_accept_environment ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 706:

/* Line 1455 of yacc.c  */
#line 4040 "parser.y"
    { 
	cb_emit_get_environment ((yyvsp[(4) - (5)]), (yyvsp[(1) - (5)]));
  ;}
    break;

  case 707:

/* Line 1455 of yacc.c  */
#line 4044 "parser.y"
    {
	cb_emit_accept_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 708:

/* Line 1455 of yacc.c  */
#line 4048 "parser.y"
    {
	cb_emit_accept_arg_value ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 709:

/* Line 1455 of yacc.c  */
#line 4052 "parser.y"
    {
	cb_emit_accept_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 710:

/* Line 1455 of yacc.c  */
#line 4056 "parser.y"
    {
	cb_emit_accept_name ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 711:

/* Line 1455 of yacc.c  */
#line 4062 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 712:

/* Line 1455 of yacc.c  */
#line 4063 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 713:

/* Line 1455 of yacc.c  */
#line 4064 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); ;}
    break;

  case 714:

/* Line 1455 of yacc.c  */
#line 4065 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), NULL); ;}
    break;

  case 715:

/* Line 1455 of yacc.c  */
#line 4066 "parser.y"
    { (yyval) = cb_build_pair (NULL, (yyvsp[(2) - (2)])); ;}
    break;

  case 716:

/* Line 1455 of yacc.c  */
#line 4067 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 717:

/* Line 1455 of yacc.c  */
#line 4071 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 718:

/* Line 1455 of yacc.c  */
#line 4075 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 719:

/* Line 1455 of yacc.c  */
#line 4076 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 724:

/* Line 1455 of yacc.c  */
#line 4089 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 725:

/* Line 1455 of yacc.c  */
#line 4090 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 726:

/* Line 1455 of yacc.c  */
#line 4091 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 727:

/* Line 1455 of yacc.c  */
#line 4092 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 728:

/* Line 1455 of yacc.c  */
#line 4093 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 729:

/* Line 1455 of yacc.c  */
#line 4094 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 730:

/* Line 1455 of yacc.c  */
#line 4095 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 731:

/* Line 1455 of yacc.c  */
#line 4097 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 732:

/* Line 1455 of yacc.c  */
#line 4101 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 733:

/* Line 1455 of yacc.c  */
#line 4105 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 734:

/* Line 1455 of yacc.c  */
#line 4109 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 735:

/* Line 1455 of yacc.c  */
#line 4113 "parser.y"
    { dispattrs |= COB_SCREEN_AUTO; ;}
    break;

  case 736:

/* Line 1455 of yacc.c  */
#line 4114 "parser.y"
    { dispattrs |= COB_SCREEN_FULL; ;}
    break;

  case 737:

/* Line 1455 of yacc.c  */
#line 4115 "parser.y"
    { dispattrs |= COB_SCREEN_REQUIRED; ;}
    break;

  case 738:

/* Line 1455 of yacc.c  */
#line 4116 "parser.y"
    { dispattrs |= COB_SCREEN_SECURE; ;}
    break;

  case 739:

/* Line 1455 of yacc.c  */
#line 4117 "parser.y"
    { dispattrs |= COB_SCREEN_UPDATE; ;}
    break;

  case 740:

/* Line 1455 of yacc.c  */
#line 4118 "parser.y"
    { dispattrs |= COB_SCREEN_PROMPT; ;}
    break;

  case 741:

/* Line 1455 of yacc.c  */
#line 4122 "parser.y"
    { terminator_warning (TERM_ACCEPT); ;}
    break;

  case 742:

/* Line 1455 of yacc.c  */
#line 4123 "parser.y"
    { terminator_clear (TERM_ACCEPT); ;}
    break;

  case 743:

/* Line 1455 of yacc.c  */
#line 4132 "parser.y"
    { BEGIN_STATEMENT ("ADD", TERM_ADD); ;}
    break;

  case 745:

/* Line 1455 of yacc.c  */
#line 4139 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '+', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 746:

/* Line 1455 of yacc.c  */
#line 4143 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(4) - (5)]), 0, cb_build_binary_list ((yyvsp[(1) - (5)]), '+'));
  ;}
    break;

  case 747:

/* Line 1455 of yacc.c  */
#line 4147 "parser.y"
    {
	cb_emit_corresponding (cb_build_add, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 749:

/* Line 1455 of yacc.c  */
#line 4153 "parser.y"
    { cb_list_add ((yyvsp[(0) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 750:

/* Line 1455 of yacc.c  */
#line 4157 "parser.y"
    { terminator_warning (TERM_ADD); ;}
    break;

  case 751:

/* Line 1455 of yacc.c  */
#line 4158 "parser.y"
    { terminator_clear (TERM_ADD); ;}
    break;

  case 752:

/* Line 1455 of yacc.c  */
#line 4167 "parser.y"
    { BEGIN_STATEMENT ("ALLOCATE", 0); ;}
    break;

  case 754:

/* Line 1455 of yacc.c  */
#line 4173 "parser.y"
    {
	cb_emit_allocate ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), NULL, (yyvsp[(2) - (3)]));
  ;}
    break;

  case 755:

/* Line 1455 of yacc.c  */
#line 4177 "parser.y"
    {
	cb_emit_allocate (NULL, (yyvsp[(5) - (5)]), (yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]));
  ;}
    break;

  case 756:

/* Line 1455 of yacc.c  */
#line 4183 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 757:

/* Line 1455 of yacc.c  */
#line 4184 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 758:

/* Line 1455 of yacc.c  */
#line 4194 "parser.y"
    {
	cb_error (_("ALTER statement is obsolete and unsupported"));
  ;}
    break;

  case 763:

/* Line 1455 of yacc.c  */
#line 4212 "parser.y"
    { BEGIN_STATEMENT ("CALL", TERM_CALL); ;}
    break;

  case 764:

/* Line 1455 of yacc.c  */
#line 4216 "parser.y"
    {
	cb_emit_call ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 765:

/* Line 1455 of yacc.c  */
#line 4222 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 766:

/* Line 1455 of yacc.c  */
#line 4224 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 767:

/* Line 1455 of yacc.c  */
#line 4228 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 768:

/* Line 1455 of yacc.c  */
#line 4232 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 769:

/* Line 1455 of yacc.c  */
#line 4234 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 770:

/* Line 1455 of yacc.c  */
#line 4239 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OMITTED only allowed with BY REFERENCE"));
	}
	(yyval) = cb_build_pair (cb_int (call_mode), cb_null);
  ;}
    break;

  case 771:

/* Line 1455 of yacc.c  */
#line 4246 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), (yyvsp[(3) - (3)]));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 773:

/* Line 1455 of yacc.c  */
#line 4255 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 774:

/* Line 1455 of yacc.c  */
#line 4259 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY CONTENT not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_CONTENT;
	}
  ;}
    break;

  case 775:

/* Line 1455 of yacc.c  */
#line 4267 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 776:

/* Line 1455 of yacc.c  */
#line 4277 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 777:

/* Line 1455 of yacc.c  */
#line 4278 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 778:

/* Line 1455 of yacc.c  */
#line 4279 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 779:

/* Line 1455 of yacc.c  */
#line 4284 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 780:

/* Line 1455 of yacc.c  */
#line 4288 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 781:

/* Line 1455 of yacc.c  */
#line 4292 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 782:

/* Line 1455 of yacc.c  */
#line 4299 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 783:

/* Line 1455 of yacc.c  */
#line 4303 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 784:

/* Line 1455 of yacc.c  */
#line 4307 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 785:

/* Line 1455 of yacc.c  */
#line 4313 "parser.y"
    { terminator_warning (TERM_CALL); ;}
    break;

  case 786:

/* Line 1455 of yacc.c  */
#line 4314 "parser.y"
    { terminator_clear (TERM_CALL); ;}
    break;

  case 787:

/* Line 1455 of yacc.c  */
#line 4323 "parser.y"
    { BEGIN_STATEMENT ("CANCEL", 0); ;}
    break;

  case 790:

/* Line 1455 of yacc.c  */
#line 4329 "parser.y"
    {
	cb_emit_cancel ((yyvsp[(2) - (2)]));
  ;}
    break;

  case 791:

/* Line 1455 of yacc.c  */
#line 4340 "parser.y"
    { BEGIN_STATEMENT ("CLOSE", 0); ;}
    break;

  case 794:

/* Line 1455 of yacc.c  */
#line 4347 "parser.y"
    {
	BEGIN_IMPLICIT_STATEMENT ((yyvsp[(2) - (3)]));
	if ((yyvsp[(2) - (3)]) != cb_error_node) {
		cb_emit_close ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
	}
  ;}
    break;

  case 795:

/* Line 1455 of yacc.c  */
#line 4356 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NORMAL); ;}
    break;

  case 796:

/* Line 1455 of yacc.c  */
#line 4357 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT); ;}
    break;

  case 797:

/* Line 1455 of yacc.c  */
#line 4358 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT_REMOVAL); ;}
    break;

  case 798:

/* Line 1455 of yacc.c  */
#line 4359 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NO_REWIND); ;}
    break;

  case 799:

/* Line 1455 of yacc.c  */
#line 4360 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_LOCK); ;}
    break;

  case 802:

/* Line 1455 of yacc.c  */
#line 4371 "parser.y"
    { BEGIN_STATEMENT ("COMPUTE", TERM_COMPUTE); ;}
    break;

  case 804:

/* Line 1455 of yacc.c  */
#line 4378 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(1) - (4)]), 0, (yyvsp[(3) - (4)]));
  ;}
    break;

  case 805:

/* Line 1455 of yacc.c  */
#line 4384 "parser.y"
    { terminator_warning (TERM_COMPUTE); ;}
    break;

  case 806:

/* Line 1455 of yacc.c  */
#line 4385 "parser.y"
    { terminator_clear (TERM_COMPUTE); ;}
    break;

  case 809:

/* Line 1455 of yacc.c  */
#line 4396 "parser.y"
    {
	BEGIN_STATEMENT ("COMMIT", 0);
	cb_emit_commit ();
  ;}
    break;

  case 810:

/* Line 1455 of yacc.c  */
#line 4409 "parser.y"
    {
	BEGIN_STATEMENT ("CONTINUE", 0);
	cb_emit_continue ();
  ;}
    break;

  case 811:

/* Line 1455 of yacc.c  */
#line 4421 "parser.y"
    { BEGIN_STATEMENT ("DELETE", TERM_DELETE); ;}
    break;

  case 812:

/* Line 1455 of yacc.c  */
#line 4424 "parser.y"
    {
	if ((yyvsp[(3) - (6)]) != cb_error_node) {
		cb_emit_delete ((yyvsp[(3) - (6)]));
	}
  ;}
    break;

  case 813:

/* Line 1455 of yacc.c  */
#line 4432 "parser.y"
    { terminator_warning (TERM_DELETE); ;}
    break;

  case 814:

/* Line 1455 of yacc.c  */
#line 4433 "parser.y"
    { terminator_clear (TERM_DELETE); ;}
    break;

  case 815:

/* Line 1455 of yacc.c  */
#line 4442 "parser.y"
    { BEGIN_STATEMENT ("DELETE-FILE", 0); ;}
    break;

  case 816:

/* Line 1455 of yacc.c  */
#line 4444 "parser.y"
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

  case 817:

/* Line 1455 of yacc.c  */
#line 4462 "parser.y"
    {
	BEGIN_STATEMENT ("DISPLAY", TERM_DISPLAY);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 819:

/* Line 1455 of yacc.c  */
#line 4475 "parser.y"
    {
	cb_emit_env_name ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 820:

/* Line 1455 of yacc.c  */
#line 4479 "parser.y"
    {
	cb_emit_env_value ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 821:

/* Line 1455 of yacc.c  */
#line 4483 "parser.y"
    {
	cb_emit_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 822:

/* Line 1455 of yacc.c  */
#line 4487 "parser.y"
    {
	cb_emit_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 823:

/* Line 1455 of yacc.c  */
#line 4491 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (4)]), cb_int0, (yyvsp[(3) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 824:

/* Line 1455 of yacc.c  */
#line 4495 "parser.y"
    {
	cb_emit_display_mnemonic ((yyvsp[(1) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 825:

/* Line 1455 of yacc.c  */
#line 4499 "parser.y"
    {
	cb_tree word = cb_build_display_upon_direct ((yyvsp[(4) - (6)]));
	cb_emit_display ((yyvsp[(1) - (6)]), word, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 826:

/* Line 1455 of yacc.c  */
#line 4504 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 827:

/* Line 1455 of yacc.c  */
#line 4508 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 828:

/* Line 1455 of yacc.c  */
#line 4514 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 829:

/* Line 1455 of yacc.c  */
#line 4515 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 830:

/* Line 1455 of yacc.c  */
#line 4516 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 833:

/* Line 1455 of yacc.c  */
#line 4526 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 834:

/* Line 1455 of yacc.c  */
#line 4527 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 835:

/* Line 1455 of yacc.c  */
#line 4528 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 836:

/* Line 1455 of yacc.c  */
#line 4529 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 837:

/* Line 1455 of yacc.c  */
#line 4530 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 838:

/* Line 1455 of yacc.c  */
#line 4531 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 839:

/* Line 1455 of yacc.c  */
#line 4532 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 840:

/* Line 1455 of yacc.c  */
#line 4533 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 841:

/* Line 1455 of yacc.c  */
#line 4534 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 842:

/* Line 1455 of yacc.c  */
#line 4536 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 843:

/* Line 1455 of yacc.c  */
#line 4540 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 844:

/* Line 1455 of yacc.c  */
#line 4544 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 845:

/* Line 1455 of yacc.c  */
#line 4548 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 846:

/* Line 1455 of yacc.c  */
#line 4552 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 847:

/* Line 1455 of yacc.c  */
#line 4553 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 848:

/* Line 1455 of yacc.c  */
#line 4557 "parser.y"
    { terminator_warning (TERM_DISPLAY); ;}
    break;

  case 849:

/* Line 1455 of yacc.c  */
#line 4558 "parser.y"
    { terminator_clear (TERM_DISPLAY); ;}
    break;

  case 850:

/* Line 1455 of yacc.c  */
#line 4567 "parser.y"
    { BEGIN_STATEMENT ("DIVIDE", TERM_DIVIDE); ;}
    break;

  case 852:

/* Line 1455 of yacc.c  */
#line 4574 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '/', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 853:

/* Line 1455 of yacc.c  */
#line 4578 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(3) - (6)]), '/', (yyvsp[(1) - (6)])));
  ;}
    break;

  case 854:

/* Line 1455 of yacc.c  */
#line 4582 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '/', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 855:

/* Line 1455 of yacc.c  */
#line 4586 "parser.y"
    {
	cb_emit_divide ((yyvsp[(3) - (8)]), (yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 856:

/* Line 1455 of yacc.c  */
#line 4590 "parser.y"
    {
	cb_emit_divide ((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 857:

/* Line 1455 of yacc.c  */
#line 4596 "parser.y"
    { terminator_warning (TERM_DIVIDE); ;}
    break;

  case 858:

/* Line 1455 of yacc.c  */
#line 4597 "parser.y"
    { terminator_clear (TERM_DIVIDE); ;}
    break;

  case 859:

/* Line 1455 of yacc.c  */
#line 4606 "parser.y"
    { BEGIN_STATEMENT ("ENTRY", 0); ;}
    break;

  case 860:

/* Line 1455 of yacc.c  */
#line 4608 "parser.y"
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

  case 861:

/* Line 1455 of yacc.c  */
#line 4628 "parser.y"
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

  case 862:

/* Line 1455 of yacc.c  */
#line 4639 "parser.y"
    {
	cb_emit_evaluate ((yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]));
	eval_level--;
  ;}
    break;

  case 863:

/* Line 1455 of yacc.c  */
#line 4646 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 864:

/* Line 1455 of yacc.c  */
#line 4649 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 865:

/* Line 1455 of yacc.c  */
#line 4659 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE_P ((yyvsp[(1) - (1)]))) {
		eval_check[eval_level][eval_inc++] = 0;
	} else {
		eval_check[eval_level][eval_inc++] = 1;
	}
  ;}
    break;

  case 866:

/* Line 1455 of yacc.c  */
#line 4668 "parser.y"
    {
	(yyval) = cb_true;
	eval_check[eval_level][eval_inc++] = 2;
  ;}
    break;

  case 867:

/* Line 1455 of yacc.c  */
#line 4673 "parser.y"
    {
	(yyval) = cb_false;
	eval_check[eval_level][eval_inc++] = 3;
  ;}
    break;

  case 868:

/* Line 1455 of yacc.c  */
#line 4681 "parser.y"
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

  case 869:

/* Line 1455 of yacc.c  */
#line 4709 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 870:

/* Line 1455 of yacc.c  */
#line 4711 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 871:

/* Line 1455 of yacc.c  */
#line 4716 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 872:

/* Line 1455 of yacc.c  */
#line 4720 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]));
	eval_inc2 = 0;
  ;}
    break;

  case 873:

/* Line 1455 of yacc.c  */
#line 4731 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 874:

/* Line 1455 of yacc.c  */
#line 4735 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 875:

/* Line 1455 of yacc.c  */
#line 4739 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), NULL);
	eval_inc2 = 0;
  ;}
    break;

  case 876:

/* Line 1455 of yacc.c  */
#line 4749 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 877:

/* Line 1455 of yacc.c  */
#line 4751 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 878:

/* Line 1455 of yacc.c  */
#line 4755 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 879:

/* Line 1455 of yacc.c  */
#line 4758 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 880:

/* Line 1455 of yacc.c  */
#line 4768 "parser.y"
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

  case 881:

/* Line 1455 of yacc.c  */
#line 4796 "parser.y"
    { (yyval) = cb_any; eval_inc2++; ;}
    break;

  case 882:

/* Line 1455 of yacc.c  */
#line 4797 "parser.y"
    { (yyval) = cb_true; eval_inc2++; ;}
    break;

  case 883:

/* Line 1455 of yacc.c  */
#line 4798 "parser.y"
    { (yyval) = cb_false; eval_inc2++; ;}
    break;

  case 884:

/* Line 1455 of yacc.c  */
#line 4801 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 885:

/* Line 1455 of yacc.c  */
#line 4802 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 886:

/* Line 1455 of yacc.c  */
#line 4806 "parser.y"
    { terminator_warning (TERM_EVALUATE); ;}
    break;

  case 887:

/* Line 1455 of yacc.c  */
#line 4807 "parser.y"
    { terminator_clear (TERM_EVALUATE); ;}
    break;

  case 888:

/* Line 1455 of yacc.c  */
#line 4816 "parser.y"
    { BEGIN_STATEMENT ("EXIT", 0); ;}
    break;

  case 890:

/* Line 1455 of yacc.c  */
#line 4821 "parser.y"
    { /* nothing */ ;}
    break;

  case 891:

/* Line 1455 of yacc.c  */
#line 4823 "parser.y"
    {
	if (in_declaratives && use_global_ind) {
		cb_error (_("EXIT PROGRAM is not allowed within a USE GLOBAL procedure"));
	}
	check_unreached = 1;
	cb_emit_exit (0);
  ;}
    break;

  case 892:

/* Line 1455 of yacc.c  */
#line 4831 "parser.y"
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

  case 893:

/* Line 1455 of yacc.c  */
#line 4848 "parser.y"
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

  case 894:

/* Line 1455 of yacc.c  */
#line 4865 "parser.y"
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

  case 895:

/* Line 1455 of yacc.c  */
#line 4883 "parser.y"
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

  case 896:

/* Line 1455 of yacc.c  */
#line 4907 "parser.y"
    { BEGIN_STATEMENT ("FREE", 0); ;}
    break;

  case 897:

/* Line 1455 of yacc.c  */
#line 4909 "parser.y"
    {
	cb_emit_free ((yyvsp[(3) - (3)]));
  ;}
    break;

  case 898:

/* Line 1455 of yacc.c  */
#line 4920 "parser.y"
    { BEGIN_STATEMENT ("GENERATE", 0); ;}
    break;

  case 899:

/* Line 1455 of yacc.c  */
#line 4922 "parser.y"
    {
	PENDING("GENERATE");
  ;}
    break;

  case 900:

/* Line 1455 of yacc.c  */
#line 4933 "parser.y"
    { BEGIN_STATEMENT ("GO TO", 0); ;}
    break;

  case 901:

/* Line 1455 of yacc.c  */
#line 4935 "parser.y"
    {
	cb_emit_goto ((yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 902:

/* Line 1455 of yacc.c  */
#line 4942 "parser.y"
    {
	check_unreached = 1;
	(yyval) = NULL;
  ;}
    break;

  case 903:

/* Line 1455 of yacc.c  */
#line 4947 "parser.y"
    {
	check_unreached = 0;
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 904:

/* Line 1455 of yacc.c  */
#line 4959 "parser.y"
    { BEGIN_STATEMENT ("GOBACK", 0); ;}
    break;

  case 905:

/* Line 1455 of yacc.c  */
#line 4960 "parser.y"
    {
	check_unreached = 1;
	cb_emit_exit (1);
  ;}
    break;

  case 906:

/* Line 1455 of yacc.c  */
#line 4972 "parser.y"
    { BEGIN_STATEMENT ("IF", TERM_IF); ;}
    break;

  case 907:

/* Line 1455 of yacc.c  */
#line 4974 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 908:

/* Line 1455 of yacc.c  */
#line 4979 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(6) - (8)]) == NULL) {
		cb_error (_("syntax error"));
	}
	cb_emit_if ((yyvsp[(3) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 910:

/* Line 1455 of yacc.c  */
#line 4990 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 911:

/* Line 1455 of yacc.c  */
#line 4994 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 912:

/* Line 1455 of yacc.c  */
#line 4998 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 913:

/* Line 1455 of yacc.c  */
#line 5007 "parser.y"
    { terminator_warning (TERM_IF); ;}
    break;

  case 914:

/* Line 1455 of yacc.c  */
#line 5008 "parser.y"
    { terminator_clear (TERM_IF); ;}
    break;

  case 915:

/* Line 1455 of yacc.c  */
#line 5017 "parser.y"
    { BEGIN_STATEMENT ("INITIALIZE", 0); ;}
    break;

  case 916:

/* Line 1455 of yacc.c  */
#line 5019 "parser.y"
    {
	cb_emit_initialize ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 917:

/* Line 1455 of yacc.c  */
#line 5025 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 918:

/* Line 1455 of yacc.c  */
#line 5026 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 919:

/* Line 1455 of yacc.c  */
#line 5030 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 920:

/* Line 1455 of yacc.c  */
#line 5031 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 921:

/* Line 1455 of yacc.c  */
#line 5032 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 922:

/* Line 1455 of yacc.c  */
#line 5036 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 923:

/* Line 1455 of yacc.c  */
#line 5038 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 924:

/* Line 1455 of yacc.c  */
#line 5042 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 925:

/* Line 1455 of yacc.c  */
#line 5044 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 926:

/* Line 1455 of yacc.c  */
#line 5048 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 927:

/* Line 1455 of yacc.c  */
#line 5052 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHABETIC); ;}
    break;

  case 928:

/* Line 1455 of yacc.c  */
#line 5053 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC); ;}
    break;

  case 929:

/* Line 1455 of yacc.c  */
#line 5054 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC); ;}
    break;

  case 930:

/* Line 1455 of yacc.c  */
#line 5055 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC_EDITED); ;}
    break;

  case 931:

/* Line 1455 of yacc.c  */
#line 5056 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC_EDITED); ;}
    break;

  case 932:

/* Line 1455 of yacc.c  */
#line 5057 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL); ;}
    break;

  case 933:

/* Line 1455 of yacc.c  */
#line 5058 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL_EDITED); ;}
    break;

  case 934:

/* Line 1455 of yacc.c  */
#line 5062 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 935:

/* Line 1455 of yacc.c  */
#line 5063 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 936:

/* Line 1455 of yacc.c  */
#line 5072 "parser.y"
    { BEGIN_STATEMENT ("INITIATE", 0); ;}
    break;

  case 937:

/* Line 1455 of yacc.c  */
#line 5074 "parser.y"
    {
	PENDING("INITIATE");
  ;}
    break;

  case 938:

/* Line 1455 of yacc.c  */
#line 5085 "parser.y"
    {
	BEGIN_STATEMENT ("INSPECT", 0);
	sending_id = 0;
	inspect_keyword = 0;
  ;}
    break;

  case 940:

/* Line 1455 of yacc.c  */
#line 5094 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 0; ;}
    break;

  case 941:

/* Line 1455 of yacc.c  */
#line 5095 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 942:

/* Line 1455 of yacc.c  */
#line 5096 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 945:

/* Line 1455 of yacc.c  */
#line 5105 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 0); ;}
    break;

  case 946:

/* Line 1455 of yacc.c  */
#line 5106 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int1, 1); ;}
    break;

  case 947:

/* Line 1455 of yacc.c  */
#line 5107 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 2); ;}
    break;

  case 948:

/* Line 1455 of yacc.c  */
#line 5113 "parser.y"
    { cb_init_tarrying (); ;}
    break;

  case 949:

/* Line 1455 of yacc.c  */
#line 5114 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 950:

/* Line 1455 of yacc.c  */
#line 5118 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 951:

/* Line 1455 of yacc.c  */
#line 5119 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 952:

/* Line 1455 of yacc.c  */
#line 5123 "parser.y"
    { (yyval) = cb_build_tarrying_data ((yyvsp[(1) - (2)])); ;}
    break;

  case 953:

/* Line 1455 of yacc.c  */
#line 5124 "parser.y"
    { (yyval) = cb_build_tarrying_characters ((yyvsp[(2) - (2)])); ;}
    break;

  case 954:

/* Line 1455 of yacc.c  */
#line 5125 "parser.y"
    { (yyval) = cb_build_tarrying_all (); ;}
    break;

  case 955:

/* Line 1455 of yacc.c  */
#line 5126 "parser.y"
    { (yyval) = cb_build_tarrying_leading (); ;}
    break;

  case 956:

/* Line 1455 of yacc.c  */
#line 5127 "parser.y"
    { (yyval) = cb_build_tarrying_trailing (); ;}
    break;

  case 957:

/* Line 1455 of yacc.c  */
#line 5128 "parser.y"
    { (yyval) = cb_build_tarrying_value ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 958:

/* Line 1455 of yacc.c  */
#line 5134 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); inspect_keyword = 0; ;}
    break;

  case 959:

/* Line 1455 of yacc.c  */
#line 5138 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 960:

/* Line 1455 of yacc.c  */
#line 5139 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 961:

/* Line 1455 of yacc.c  */
#line 5144 "parser.y"
    {
	(yyval) = cb_build_replacing_characters ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]), save_tree_1);
	inspect_keyword = 0;
  ;}
    break;

  case 962:

/* Line 1455 of yacc.c  */
#line 5148 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 963:

/* Line 1455 of yacc.c  */
#line 5152 "parser.y"
    { /* Nothing */ ;}
    break;

  case 964:

/* Line 1455 of yacc.c  */
#line 5153 "parser.y"
    { inspect_keyword = 1; ;}
    break;

  case 965:

/* Line 1455 of yacc.c  */
#line 5154 "parser.y"
    { inspect_keyword = 2; ;}
    break;

  case 966:

/* Line 1455 of yacc.c  */
#line 5155 "parser.y"
    { inspect_keyword = 3; ;}
    break;

  case 967:

/* Line 1455 of yacc.c  */
#line 5156 "parser.y"
    { inspect_keyword = 4; ;}
    break;

  case 968:

/* Line 1455 of yacc.c  */
#line 5161 "parser.y"
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

  case 969:

/* Line 1455 of yacc.c  */
#line 5187 "parser.y"
    {
	if (cb_validate_inspect (save_tree_1, (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])) < 0 ) {
		(yyval) = cb_error_node;
	} else {
		(yyval) = cb_build_converting ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 970:

/* Line 1455 of yacc.c  */
#line 5199 "parser.y"
    { (yyval) = cb_build_inspect_region_start (); ;}
    break;

  case 971:

/* Line 1455 of yacc.c  */
#line 5201 "parser.y"
    { (yyval) = cb_build_inspect_region ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 974:

/* Line 1455 of yacc.c  */
#line 5212 "parser.y"
    { BEGIN_STATEMENT ("MERGE", 0); ;}
    break;

  case 976:

/* Line 1455 of yacc.c  */
#line 5222 "parser.y"
    { BEGIN_STATEMENT ("MOVE", 0); ;}
    break;

  case 978:

/* Line 1455 of yacc.c  */
#line 5228 "parser.y"
    {
	cb_emit_move ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 979:

/* Line 1455 of yacc.c  */
#line 5232 "parser.y"
    {
	cb_emit_move_corresponding ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 980:

/* Line 1455 of yacc.c  */
#line 5243 "parser.y"
    { BEGIN_STATEMENT ("MULTIPLY", TERM_MULTIPLY); ;}
    break;

  case 982:

/* Line 1455 of yacc.c  */
#line 5250 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '*', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 983:

/* Line 1455 of yacc.c  */
#line 5254 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '*', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 984:

/* Line 1455 of yacc.c  */
#line 5260 "parser.y"
    { terminator_warning (TERM_MULTIPLY); ;}
    break;

  case 985:

/* Line 1455 of yacc.c  */
#line 5261 "parser.y"
    { terminator_clear (TERM_MULTIPLY); ;}
    break;

  case 986:

/* Line 1455 of yacc.c  */
#line 5270 "parser.y"
    { BEGIN_STATEMENT ("OPEN", 0); ;}
    break;

  case 989:

/* Line 1455 of yacc.c  */
#line 5277 "parser.y"
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

  case 990:

/* Line 1455 of yacc.c  */
#line 5289 "parser.y"
    { (yyval) = cb_int (COB_OPEN_INPUT); ;}
    break;

  case 991:

/* Line 1455 of yacc.c  */
#line 5290 "parser.y"
    { (yyval) = cb_int (COB_OPEN_OUTPUT); ;}
    break;

  case 992:

/* Line 1455 of yacc.c  */
#line 5291 "parser.y"
    { (yyval) = cb_int (COB_OPEN_I_O); ;}
    break;

  case 993:

/* Line 1455 of yacc.c  */
#line 5292 "parser.y"
    { (yyval) = cb_int (COB_OPEN_EXTEND); ;}
    break;

  case 994:

/* Line 1455 of yacc.c  */
#line 5296 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 995:

/* Line 1455 of yacc.c  */
#line 5297 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 996:

/* Line 1455 of yacc.c  */
#line 5301 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 997:

/* Line 1455 of yacc.c  */
#line 5302 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 998:

/* Line 1455 of yacc.c  */
#line 5303 "parser.y"
    { PENDING ("OPEN ... WITH LOCK"); ;}
    break;

  case 999:

/* Line 1455 of yacc.c  */
#line 5315 "parser.y"
    { BEGIN_STATEMENT ("PERFORM", TERM_PERFORM); ;}
    break;

  case 1001:

/* Line 1455 of yacc.c  */
#line 5321 "parser.y"
    {
	cb_emit_perform ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));
  ;}
    break;

  case 1002:

/* Line 1455 of yacc.c  */
#line 5325 "parser.y"
    {
	perform_stack = cb_cons ((yyvsp[(1) - (1)]), perform_stack);
	check_unreached = 0;
  ;}
    break;

  case 1003:

/* Line 1455 of yacc.c  */
#line 5330 "parser.y"
    {
	perform_stack = CB_CHAIN (perform_stack);
	cb_emit_perform ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 1004:

/* Line 1455 of yacc.c  */
#line 5335 "parser.y"
    {
	cb_emit_perform ((yyvsp[(1) - (2)]), NULL);
  ;}
    break;

  case 1005:

/* Line 1455 of yacc.c  */
#line 5341 "parser.y"
    { terminator_error (); ;}
    break;

  case 1006:

/* Line 1455 of yacc.c  */
#line 5342 "parser.y"
    { terminator_clear (TERM_PERFORM); ;}
    break;

  case 1007:

/* Line 1455 of yacc.c  */
#line 5347 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(1) - (1)]))->length = cb_true; /* return from $1 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (1)]), (yyvsp[(1) - (1)]));
  ;}
    break;

  case 1008:

/* Line 1455 of yacc.c  */
#line 5352 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(3) - (3)]))->length = cb_true; /* return from $3 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1009:

/* Line 1455 of yacc.c  */
#line 5360 "parser.y"
    {
	(yyval) = cb_build_perform_once (NULL);
  ;}
    break;

  case 1010:

/* Line 1455 of yacc.c  */
#line 5364 "parser.y"
    {
	(yyval) = cb_build_perform_forever (NULL);
  ;}
    break;

  case 1011:

/* Line 1455 of yacc.c  */
#line 5368 "parser.y"
    {
	(yyval) = cb_build_perform_times ((yyvsp[(1) - (2)]));
	current_program->loop_counter++;
  ;}
    break;

  case 1012:

/* Line 1455 of yacc.c  */
#line 5373 "parser.y"
    {
	cb_tree varying;

	varying = cb_list_init (cb_build_perform_varying (NULL, NULL, NULL, (yyvsp[(3) - (3)])));
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), varying);
  ;}
    break;

  case 1013:

/* Line 1455 of yacc.c  */
#line 5380 "parser.y"
    {
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1014:

/* Line 1455 of yacc.c  */
#line 5386 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1015:

/* Line 1455 of yacc.c  */
#line 5387 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1016:

/* Line 1455 of yacc.c  */
#line 5391 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1017:

/* Line 1455 of yacc.c  */
#line 5393 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1018:

/* Line 1455 of yacc.c  */
#line 5398 "parser.y"
    {
	(yyval) = cb_build_perform_varying ((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1019:

/* Line 1455 of yacc.c  */
#line 5409 "parser.y"
    { BEGIN_STATEMENT ("READ", TERM_READ); ;}
    break;

  case 1020:

/* Line 1455 of yacc.c  */
#line 5412 "parser.y"
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

  case 1021:

/* Line 1455 of yacc.c  */
#line 5432 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1022:

/* Line 1455 of yacc.c  */
#line 5433 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1023:

/* Line 1455 of yacc.c  */
#line 5437 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1024:

/* Line 1455 of yacc.c  */
#line 5439 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1025:

/* Line 1455 of yacc.c  */
#line 5443 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1026:

/* Line 1455 of yacc.c  */
#line 5447 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1027:

/* Line 1455 of yacc.c  */
#line 5451 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1028:

/* Line 1455 of yacc.c  */
#line 5455 "parser.y"
    {
	(yyval) = cb_int4;
  ;}
    break;

  case 1029:

/* Line 1455 of yacc.c  */
#line 5461 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1030:

/* Line 1455 of yacc.c  */
#line 5463 "parser.y"
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

  case 1034:

/* Line 1455 of yacc.c  */
#line 5482 "parser.y"
    { terminator_warning (TERM_READ); ;}
    break;

  case 1035:

/* Line 1455 of yacc.c  */
#line 5483 "parser.y"
    { terminator_clear (TERM_READ); ;}
    break;

  case 1036:

/* Line 1455 of yacc.c  */
#line 5492 "parser.y"
    { BEGIN_STATEMENT ("RELEASE", 0); ;}
    break;

  case 1037:

/* Line 1455 of yacc.c  */
#line 5494 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_release ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
	}
  ;}
    break;

  case 1038:

/* Line 1455 of yacc.c  */
#line 5507 "parser.y"
    { BEGIN_STATEMENT ("RETURN", TERM_RETURN); ;}
    break;

  case 1039:

/* Line 1455 of yacc.c  */
#line 5510 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_return ((yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]));
	}
  ;}
    break;

  case 1040:

/* Line 1455 of yacc.c  */
#line 5518 "parser.y"
    { terminator_warning (TERM_RETURN); ;}
    break;

  case 1041:

/* Line 1455 of yacc.c  */
#line 5519 "parser.y"
    { terminator_clear (TERM_RETURN); ;}
    break;

  case 1042:

/* Line 1455 of yacc.c  */
#line 5528 "parser.y"
    { BEGIN_STATEMENT ("REWRITE", TERM_REWRITE); ;}
    break;

  case 1043:

/* Line 1455 of yacc.c  */
#line 5531 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_rewrite ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]));
	}
  ;}
    break;

  case 1044:

/* Line 1455 of yacc.c  */
#line 5539 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1045:

/* Line 1455 of yacc.c  */
#line 5541 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1046:

/* Line 1455 of yacc.c  */
#line 5545 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1047:

/* Line 1455 of yacc.c  */
#line 5551 "parser.y"
    { terminator_warning (TERM_REWRITE); ;}
    break;

  case 1048:

/* Line 1455 of yacc.c  */
#line 5552 "parser.y"
    { terminator_clear (TERM_REWRITE); ;}
    break;

  case 1049:

/* Line 1455 of yacc.c  */
#line 5562 "parser.y"
    {
	BEGIN_STATEMENT ("ROLLBACK", 0);
	cb_emit_rollback ();
  ;}
    break;

  case 1050:

/* Line 1455 of yacc.c  */
#line 5574 "parser.y"
    { BEGIN_STATEMENT ("SEARCH", TERM_SEARCH); ;}
    break;

  case 1052:

/* Line 1455 of yacc.c  */
#line 5581 "parser.y"
    {
	cb_emit_search ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1053:

/* Line 1455 of yacc.c  */
#line 5585 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1054:

/* Line 1455 of yacc.c  */
#line 5589 "parser.y"
    {
	cb_emit_search_all ((yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1055:

/* Line 1455 of yacc.c  */
#line 5595 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1056:

/* Line 1455 of yacc.c  */
#line 5596 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1057:

/* Line 1455 of yacc.c  */
#line 5600 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1058:

/* Line 1455 of yacc.c  */
#line 5602 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1059:

/* Line 1455 of yacc.c  */
#line 5606 "parser.y"
    {
	(yyval) = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 1060:

/* Line 1455 of yacc.c  */
#line 5612 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1061:

/* Line 1455 of yacc.c  */
#line 5613 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); CB_IF ((yyvsp[(1) - (2)]))->stmt2 = (yyvsp[(2) - (2)]); ;}
    break;

  case 1062:

/* Line 1455 of yacc.c  */
#line 5618 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1063:

/* Line 1455 of yacc.c  */
#line 5622 "parser.y"
    {
	(yyval) = cb_build_if ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), NULL);
  ;}
    break;

  case 1064:

/* Line 1455 of yacc.c  */
#line 5628 "parser.y"
    { terminator_warning (TERM_SEARCH); ;}
    break;

  case 1065:

/* Line 1455 of yacc.c  */
#line 5629 "parser.y"
    { terminator_clear (TERM_SEARCH); ;}
    break;

  case 1066:

/* Line 1455 of yacc.c  */
#line 5638 "parser.y"
    { BEGIN_STATEMENT ("SET", 0); ;}
    break;

  case 1073:

/* Line 1455 of yacc.c  */
#line 5654 "parser.y"
    {
	cb_emit_setenv ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1074:

/* Line 1455 of yacc.c  */
#line 5663 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (4)]), cb_build_ppointer ((yyvsp[(4) - (4)])));
  ;}
    break;

  case 1075:

/* Line 1455 of yacc.c  */
#line 5667 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1076:

/* Line 1455 of yacc.c  */
#line 5676 "parser.y"
    {
	cb_emit_set_up_down ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1077:

/* Line 1455 of yacc.c  */
#line 5682 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1078:

/* Line 1455 of yacc.c  */
#line 5683 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1081:

/* Line 1455 of yacc.c  */
#line 5695 "parser.y"
    {
	cb_emit_set_on_off ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1084:

/* Line 1455 of yacc.c  */
#line 5709 "parser.y"
    {
	cb_emit_set_true ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1085:

/* Line 1455 of yacc.c  */
#line 5713 "parser.y"
    {
	cb_emit_set_false ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1086:

/* Line 1455 of yacc.c  */
#line 5724 "parser.y"
    { BEGIN_STATEMENT ("SORT", 0); ;}
    break;

  case 1088:

/* Line 1455 of yacc.c  */
#line 5730 "parser.y"
    {
	cb_emit_sort_init ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (4)]))) && (yyvsp[(2) - (4)]) == NULL) {
		cb_error (_("File sort requires KEY phrase"));
	}
	/* used in sort_input/sort_output */
	save_tree_1 = (yyvsp[(1) - (4)]);
  ;}
    break;

  case 1089:

/* Line 1455 of yacc.c  */
#line 5739 "parser.y"
    {
	cb_emit_sort_finish ((yyvsp[(1) - (7)]));
  ;}
    break;

  case 1090:

/* Line 1455 of yacc.c  */
#line 5746 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 1091:

/* Line 1455 of yacc.c  */
#line 5751 "parser.y"
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

  case 1092:

/* Line 1455 of yacc.c  */
#line 5765 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1093:

/* Line 1455 of yacc.c  */
#line 5766 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1095:

/* Line 1455 of yacc.c  */
#line 5770 "parser.y"
    { /* nothing */ ;}
    break;

  case 1096:

/* Line 1455 of yacc.c  */
#line 5774 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1097:

/* Line 1455 of yacc.c  */
#line 5775 "parser.y"
    { (yyval) = cb_ref ((yyvsp[(3) - (3)])); ;}
    break;

  case 1098:

/* Line 1455 of yacc.c  */
#line 5780 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires USING or INPUT PROCEDURE"));
	}
  ;}
    break;

  case 1099:

/* Line 1455 of yacc.c  */
#line 5786 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("USING invalid with table SORT"));
	} else {
		cb_emit_sort_using (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1100:

/* Line 1455 of yacc.c  */
#line 5794 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("INPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_input ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1101:

/* Line 1455 of yacc.c  */
#line 5805 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires GIVING or OUTPUT PROCEDURE"));
	}
  ;}
    break;

  case 1102:

/* Line 1455 of yacc.c  */
#line 5811 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("GIVING invalid with table SORT"));
	} else {
		cb_emit_sort_giving (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1103:

/* Line 1455 of yacc.c  */
#line 5819 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("OUTPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_output ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1104:

/* Line 1455 of yacc.c  */
#line 5834 "parser.y"
    { BEGIN_STATEMENT ("START", TERM_START); ;}
    break;

  case 1105:

/* Line 1455 of yacc.c  */
#line 5835 "parser.y"
    { (yyval) = cb_int (COB_EQ); ;}
    break;

  case 1106:

/* Line 1455 of yacc.c  */
#line 5838 "parser.y"
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

  case 1107:

/* Line 1455 of yacc.c  */
#line 5855 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1108:

/* Line 1455 of yacc.c  */
#line 5857 "parser.y"
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

  case 1109:

/* Line 1455 of yacc.c  */
#line 5872 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_NE : COB_EQ); ;}
    break;

  case 1110:

/* Line 1455 of yacc.c  */
#line 5873 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LE : COB_GT); ;}
    break;

  case 1111:

/* Line 1455 of yacc.c  */
#line 5874 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GE : COB_LT); ;}
    break;

  case 1112:

/* Line 1455 of yacc.c  */
#line 5875 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LT : COB_GE); ;}
    break;

  case 1113:

/* Line 1455 of yacc.c  */
#line 5876 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GT : COB_LE); ;}
    break;

  case 1114:

/* Line 1455 of yacc.c  */
#line 5880 "parser.y"
    { terminator_warning (TERM_START); ;}
    break;

  case 1115:

/* Line 1455 of yacc.c  */
#line 5881 "parser.y"
    { terminator_clear (TERM_START); ;}
    break;

  case 1116:

/* Line 1455 of yacc.c  */
#line 5890 "parser.y"
    { BEGIN_STATEMENT ("STOP", 0); ;}
    break;

  case 1117:

/* Line 1455 of yacc.c  */
#line 5892 "parser.y"
    {
	cb_emit_stop_run ((yyvsp[(4) - (4)]));
  ;}
    break;

  case 1118:

/* Line 1455 of yacc.c  */
#line 5896 "parser.y"
    {
	cb_verify (cb_stop_literal_statement, "STOP literal");
  ;}
    break;

  case 1119:

/* Line 1455 of yacc.c  */
#line 5902 "parser.y"
    { (yyval) = current_program->cb_return_code; ;}
    break;

  case 1120:

/* Line 1455 of yacc.c  */
#line 5903 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1121:

/* Line 1455 of yacc.c  */
#line 5904 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1122:

/* Line 1455 of yacc.c  */
#line 5913 "parser.y"
    { BEGIN_STATEMENT ("STRING", TERM_STRING); ;}
    break;

  case 1123:

/* Line 1455 of yacc.c  */
#line 5916 "parser.y"
    {
	cb_emit_string ((yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]));
  ;}
    break;

  case 1124:

/* Line 1455 of yacc.c  */
#line 5922 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1125:

/* Line 1455 of yacc.c  */
#line 5923 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1126:

/* Line 1455 of yacc.c  */
#line 5927 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1127:

/* Line 1455 of yacc.c  */
#line 5928 "parser.y"
    { (yyval) = cb_build_pair (cb_int0, NULL); ;}
    break;

  case 1128:

/* Line 1455 of yacc.c  */
#line 5929 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), NULL); ;}
    break;

  case 1129:

/* Line 1455 of yacc.c  */
#line 5933 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1130:

/* Line 1455 of yacc.c  */
#line 5934 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1131:

/* Line 1455 of yacc.c  */
#line 5938 "parser.y"
    { terminator_warning (TERM_STRING); ;}
    break;

  case 1132:

/* Line 1455 of yacc.c  */
#line 5939 "parser.y"
    { terminator_clear (TERM_STRING); ;}
    break;

  case 1133:

/* Line 1455 of yacc.c  */
#line 5948 "parser.y"
    { BEGIN_STATEMENT ("SUBTRACT", TERM_SUBTRACT); ;}
    break;

  case 1135:

/* Line 1455 of yacc.c  */
#line 5955 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '-', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 1136:

/* Line 1455 of yacc.c  */
#line 5959 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_list (cb_cons ((yyvsp[(3) - (6)]), (yyvsp[(1) - (6)])), '-'));
  ;}
    break;

  case 1137:

/* Line 1455 of yacc.c  */
#line 5963 "parser.y"
    {
	cb_emit_corresponding (cb_build_sub, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 1138:

/* Line 1455 of yacc.c  */
#line 5969 "parser.y"
    { terminator_warning (TERM_SUBTRACT); ;}
    break;

  case 1139:

/* Line 1455 of yacc.c  */
#line 5970 "parser.y"
    { terminator_clear (TERM_SUBTRACT); ;}
    break;

  case 1140:

/* Line 1455 of yacc.c  */
#line 5980 "parser.y"
    {
	BEGIN_STATEMENT ("SUPPRESS", 0);
	PENDING("SUPPRESS");
  ;}
    break;

  case 1143:

/* Line 1455 of yacc.c  */
#line 5995 "parser.y"
    { BEGIN_STATEMENT ("TERMINATE", 0); ;}
    break;

  case 1144:

/* Line 1455 of yacc.c  */
#line 5997 "parser.y"
    {
	PENDING("TERMINATE");
  ;}
    break;

  case 1145:

/* Line 1455 of yacc.c  */
#line 6008 "parser.y"
    { BEGIN_STATEMENT ("TRANSFORM", 0); ;}
    break;

  case 1146:

/* Line 1455 of yacc.c  */
#line 6010 "parser.y"
    {
	cb_tree		x;

	x = cb_build_converting ((yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]), cb_build_inspect_region_start ());
	cb_emit_inspect ((yyvsp[(3) - (7)]), x, cb_int0, 2);
  ;}
    break;

  case 1147:

/* Line 1455 of yacc.c  */
#line 6024 "parser.y"
    { BEGIN_STATEMENT ("UNLOCK", 0); ;}
    break;

  case 1148:

/* Line 1455 of yacc.c  */
#line 6026 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_unlock ((yyvsp[(3) - (4)]));
	}
  ;}
    break;

  case 1152:

/* Line 1455 of yacc.c  */
#line 6045 "parser.y"
    { BEGIN_STATEMENT ("UNSTRING", TERM_UNSTRING); ;}
    break;

  case 1153:

/* Line 1455 of yacc.c  */
#line 6049 "parser.y"
    {
	cb_emit_unstring ((yyvsp[(3) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]));
  ;}
    break;

  case 1154:

/* Line 1455 of yacc.c  */
#line 6055 "parser.y"
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
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1157:

/* Line 1455 of yacc.c  */
#line 6063 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1158:

/* Line 1455 of yacc.c  */
#line 6068 "parser.y"
    {
	(yyval) = cb_build_unstring_delimited ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1159:

/* Line 1455 of yacc.c  */
#line 6074 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 1160:

/* Line 1455 of yacc.c  */
#line 6076 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1161:

/* Line 1455 of yacc.c  */
#line 6081 "parser.y"
    {
	(yyval) = cb_build_unstring_into ((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1162:

/* Line 1455 of yacc.c  */
#line 6087 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1163:

/* Line 1455 of yacc.c  */
#line 6088 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1164:

/* Line 1455 of yacc.c  */
#line 6092 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1165:

/* Line 1455 of yacc.c  */
#line 6093 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1166:

/* Line 1455 of yacc.c  */
#line 6097 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1167:

/* Line 1455 of yacc.c  */
#line 6098 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1168:

/* Line 1455 of yacc.c  */
#line 6102 "parser.y"
    { terminator_warning (TERM_UNSTRING); ;}
    break;

  case 1169:

/* Line 1455 of yacc.c  */
#line 6103 "parser.y"
    { terminator_clear (TERM_UNSTRING); ;}
    break;

  case 1173:

/* Line 1455 of yacc.c  */
#line 6121 "parser.y"
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

  case 1174:

/* Line 1455 of yacc.c  */
#line 6142 "parser.y"
    {
	use_global_ind = 0;
  ;}
    break;

  case 1175:

/* Line 1455 of yacc.c  */
#line 6146 "parser.y"
    {
	use_global_ind = 1;
	current_program->flag_global_use = 1;
  ;}
    break;

  case 1176:

/* Line 1455 of yacc.c  */
#line 6154 "parser.y"
    {
	cb_tree		l;

	for (l = (yyvsp[(1) - (1)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			setup_use_file (CB_FILE (cb_ref (CB_VALUE (l))));
		}
	}
  ;}
    break;

  case 1177:

/* Line 1455 of yacc.c  */
#line 6164 "parser.y"
    {
	current_program->global_handler[COB_OPEN_INPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_INPUT].handler_prog = current_program;
  ;}
    break;

  case 1178:

/* Line 1455 of yacc.c  */
#line 6169 "parser.y"
    {
	current_program->global_handler[COB_OPEN_OUTPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_OUTPUT].handler_prog = current_program;
  ;}
    break;

  case 1179:

/* Line 1455 of yacc.c  */
#line 6174 "parser.y"
    {
	current_program->global_handler[COB_OPEN_I_O].handler_label = current_section;
	current_program->global_handler[COB_OPEN_I_O].handler_prog = current_program;
  ;}
    break;

  case 1180:

/* Line 1455 of yacc.c  */
#line 6179 "parser.y"
    {
	current_program->global_handler[COB_OPEN_EXTEND].handler_label = current_section;
	current_program->global_handler[COB_OPEN_EXTEND].handler_prog = current_program;
  ;}
    break;

  case 1193:

/* Line 1455 of yacc.c  */
#line 6211 "parser.y"
    {
	PENDING ("USE FOR DEBUGGING");
  ;}
    break;

  case 1196:

/* Line 1455 of yacc.c  */
#line 6223 "parser.y"
    {
	PENDING ("USE BEFORE REPORTING");
  ;}
    break;

  case 1197:

/* Line 1455 of yacc.c  */
#line 6234 "parser.y"
    { BEGIN_STATEMENT ("WRITE", TERM_WRITE); ;}
    break;

  case 1198:

/* Line 1455 of yacc.c  */
#line 6237 "parser.y"
    {
	if ((yyvsp[(3) - (8)]) != cb_error_node) {
		cb_emit_write ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(5) - (8)]));
	}
  ;}
    break;

  case 1199:

/* Line 1455 of yacc.c  */
#line 6245 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1200:

/* Line 1455 of yacc.c  */
#line 6246 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1201:

/* Line 1455 of yacc.c  */
#line 6251 "parser.y"
    {
	(yyval) = cb_int0;
  ;}
    break;

  case 1202:

/* Line 1455 of yacc.c  */
#line 6255 "parser.y"
    {
	(yyval) = cb_build_write_advancing_lines ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 1203:

/* Line 1455 of yacc.c  */
#line 6259 "parser.y"
    {
	(yyval) = cb_build_write_advancing_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1204:

/* Line 1455 of yacc.c  */
#line 6263 "parser.y"
    {
	(yyval) = cb_build_write_advancing_page ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1205:

/* Line 1455 of yacc.c  */
#line 6269 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1206:

/* Line 1455 of yacc.c  */
#line 6270 "parser.y"
    { (yyval) = CB_AFTER; ;}
    break;

  case 1210:

/* Line 1455 of yacc.c  */
#line 6279 "parser.y"
    { terminator_warning (TERM_WRITE); ;}
    break;

  case 1211:

/* Line 1455 of yacc.c  */
#line 6280 "parser.y"
    { terminator_clear (TERM_WRITE); ;}
    break;

  case 1212:

/* Line 1455 of yacc.c  */
#line 6295 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_ACCEPT;
  ;}
    break;

  case 1213:

/* Line 1455 of yacc.c  */
#line 6303 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_DISPLAY;
  ;}
    break;

  case 1215:

/* Line 1455 of yacc.c  */
#line 6310 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1216:

/* Line 1455 of yacc.c  */
#line 6314 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1218:

/* Line 1455 of yacc.c  */
#line 6321 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1219:

/* Line 1455 of yacc.c  */
#line 6325 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1222:

/* Line 1455 of yacc.c  */
#line 6341 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1223:

/* Line 1455 of yacc.c  */
#line 6346 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1225:

/* Line 1455 of yacc.c  */
#line 6353 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1226:

/* Line 1455 of yacc.c  */
#line 6358 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1227:

/* Line 1455 of yacc.c  */
#line 6370 "parser.y"
    {
	current_statement->handler_id = COB_EC_OVERFLOW;
  ;}
    break;

  case 1229:

/* Line 1455 of yacc.c  */
#line 6377 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1230:

/* Line 1455 of yacc.c  */
#line 6381 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1232:

/* Line 1455 of yacc.c  */
#line 6388 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1233:

/* Line 1455 of yacc.c  */
#line 6392 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1234:

/* Line 1455 of yacc.c  */
#line 6404 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1235:

/* Line 1455 of yacc.c  */
#line 6409 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1236:

/* Line 1455 of yacc.c  */
#line 6414 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1237:

/* Line 1455 of yacc.c  */
#line 6423 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1238:

/* Line 1455 of yacc.c  */
#line 6427 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1239:

/* Line 1455 of yacc.c  */
#line 6434 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1240:

/* Line 1455 of yacc.c  */
#line 6438 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1241:

/* Line 1455 of yacc.c  */
#line 6450 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1242:

/* Line 1455 of yacc.c  */
#line 6455 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1243:

/* Line 1455 of yacc.c  */
#line 6460 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1244:

/* Line 1455 of yacc.c  */
#line 6469 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1245:

/* Line 1455 of yacc.c  */
#line 6473 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1246:

/* Line 1455 of yacc.c  */
#line 6480 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1247:

/* Line 1455 of yacc.c  */
#line 6484 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1250:

/* Line 1455 of yacc.c  */
#line 6500 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1251:

/* Line 1455 of yacc.c  */
#line 6505 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1252:

/* Line 1455 of yacc.c  */
#line 6510 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1253:

/* Line 1455 of yacc.c  */
#line 6519 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1254:

/* Line 1455 of yacc.c  */
#line 6523 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1255:

/* Line 1455 of yacc.c  */
#line 6530 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1256:

/* Line 1455 of yacc.c  */
#line 6534 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1257:

/* Line 1455 of yacc.c  */
#line 6546 "parser.y"
    {
	(yyval) = cb_one;
  ;}
    break;

  case 1258:

/* Line 1455 of yacc.c  */
#line 6550 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 1259:

/* Line 1455 of yacc.c  */
#line 6562 "parser.y"
    {
	(yyval) = cb_build_cond ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1260:

/* Line 1455 of yacc.c  */
#line 6569 "parser.y"
    {
	(yyval) = cb_build_expr ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1261:

/* Line 1455 of yacc.c  */
#line 6575 "parser.y"
    {
	current_expr = NULL;
  ;}
    break;

  case 1262:

/* Line 1455 of yacc.c  */
#line 6579 "parser.y"
    {
	(yyval) = cb_list_reverse (current_expr);
  ;}
    break;

  case 1264:

/* Line 1455 of yacc.c  */
#line 6586 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1265:

/* Line 1455 of yacc.c  */
#line 6587 "parser.y"
    { push_expr (')', NULL); ;}
    break;

  case 1266:

/* Line 1455 of yacc.c  */
#line 6589 "parser.y"
    { push_expr ('O', NULL); ;}
    break;

  case 1267:

/* Line 1455 of yacc.c  */
#line 6590 "parser.y"
    { push_expr ('9', NULL); ;}
    break;

  case 1268:

/* Line 1455 of yacc.c  */
#line 6591 "parser.y"
    { push_expr ('A', NULL); ;}
    break;

  case 1269:

/* Line 1455 of yacc.c  */
#line 6592 "parser.y"
    { push_expr ('L', NULL); ;}
    break;

  case 1270:

/* Line 1455 of yacc.c  */
#line 6593 "parser.y"
    { push_expr ('U', NULL); ;}
    break;

  case 1271:

/* Line 1455 of yacc.c  */
#line 6594 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1272:

/* Line 1455 of yacc.c  */
#line 6596 "parser.y"
    { push_expr ('P', NULL); ;}
    break;

  case 1273:

/* Line 1455 of yacc.c  */
#line 6597 "parser.y"
    { push_expr ('N', NULL); ;}
    break;

  case 1274:

/* Line 1455 of yacc.c  */
#line 6598 "parser.y"
    { push_expr ('x', cb_zero); ;}
    break;

  case 1275:

/* Line 1455 of yacc.c  */
#line 6600 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1278:

/* Line 1455 of yacc.c  */
#line 6606 "parser.y"
    { push_expr ('(', NULL); ;}
    break;

  case 1279:

/* Line 1455 of yacc.c  */
#line 6608 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1280:

/* Line 1455 of yacc.c  */
#line 6609 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1281:

/* Line 1455 of yacc.c  */
#line 6610 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1282:

/* Line 1455 of yacc.c  */
#line 6612 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1283:

/* Line 1455 of yacc.c  */
#line 6614 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1284:

/* Line 1455 of yacc.c  */
#line 6615 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1285:

/* Line 1455 of yacc.c  */
#line 6616 "parser.y"
    { push_expr ('*', NULL); ;}
    break;

  case 1286:

/* Line 1455 of yacc.c  */
#line 6617 "parser.y"
    { push_expr ('/', NULL); ;}
    break;

  case 1287:

/* Line 1455 of yacc.c  */
#line 6618 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1288:

/* Line 1455 of yacc.c  */
#line 6620 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1289:

/* Line 1455 of yacc.c  */
#line 6621 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1290:

/* Line 1455 of yacc.c  */
#line 6622 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1291:

/* Line 1455 of yacc.c  */
#line 6623 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1292:

/* Line 1455 of yacc.c  */
#line 6624 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1293:

/* Line 1455 of yacc.c  */
#line 6625 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1294:

/* Line 1455 of yacc.c  */
#line 6627 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1295:

/* Line 1455 of yacc.c  */
#line 6628 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1296:

/* Line 1455 of yacc.c  */
#line 6629 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1297:

/* Line 1455 of yacc.c  */
#line 6630 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1298:

/* Line 1455 of yacc.c  */
#line 6631 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1299:

/* Line 1455 of yacc.c  */
#line 6632 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1300:

/* Line 1455 of yacc.c  */
#line 6634 "parser.y"
    { push_expr ('&', NULL); ;}
    break;

  case 1301:

/* Line 1455 of yacc.c  */
#line 6635 "parser.y"
    { push_expr ('|', NULL); ;}
    break;

  case 1315:

/* Line 1455 of yacc.c  */
#line 6647 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1316:

/* Line 1455 of yacc.c  */
#line 6648 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1320:

/* Line 1455 of yacc.c  */
#line 6657 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1321:

/* Line 1455 of yacc.c  */
#line 6658 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '+', (yyvsp[(3) - (3)])); ;}
    break;

  case 1322:

/* Line 1455 of yacc.c  */
#line 6659 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '-', (yyvsp[(3) - (3)])); ;}
    break;

  case 1323:

/* Line 1455 of yacc.c  */
#line 6660 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '*', (yyvsp[(3) - (3)])); ;}
    break;

  case 1324:

/* Line 1455 of yacc.c  */
#line 6661 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '/', (yyvsp[(3) - (3)])); ;}
    break;

  case 1325:

/* Line 1455 of yacc.c  */
#line 6662 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1326:

/* Line 1455 of yacc.c  */
#line 6663 "parser.y"
    { (yyval) = cb_build_binary_op (cb_zero, '-', (yyvsp[(2) - (2)])); ;}
    break;

  case 1327:

/* Line 1455 of yacc.c  */
#line 6664 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '^', (yyvsp[(3) - (3)])); ;}
    break;

  case 1328:

/* Line 1455 of yacc.c  */
#line 6665 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1329:

/* Line 1455 of yacc.c  */
#line 6677 "parser.y"
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

  case 1330:

/* Line 1455 of yacc.c  */
#line 6689 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(3) - (3)])))) {
		(yyval) = CB_FILE (cb_ref ((yyvsp[(3) - (3)])))->linage_ctr;
	} else {
		cb_error_x ((yyvsp[(3) - (3)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(3) - (3)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1331:

/* Line 1455 of yacc.c  */
#line 6703 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1332:

/* Line 1455 of yacc.c  */
#line 6705 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1333:

/* Line 1455 of yacc.c  */
#line 6709 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)])); ;}
    break;

  case 1334:

/* Line 1455 of yacc.c  */
#line 6715 "parser.y"
    { cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1335:

/* Line 1455 of yacc.c  */
#line 6722 "parser.y"
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

  case 1336:

/* Line 1455 of yacc.c  */
#line 6742 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1337:

/* Line 1455 of yacc.c  */
#line 6746 "parser.y"
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

  case 1338:

/* Line 1455 of yacc.c  */
#line 6762 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (1)])))) {
		(yyval) = (yyvsp[(1) - (1)]);
	} else {
		cb_error_x ((yyvsp[(1) - (1)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(1) - (1)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1339:

/* Line 1455 of yacc.c  */
#line 6775 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1340:

/* Line 1455 of yacc.c  */
#line 6777 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1341:

/* Line 1455 of yacc.c  */
#line 6781 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1342:

/* Line 1455 of yacc.c  */
#line 6787 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1343:

/* Line 1455 of yacc.c  */
#line 6789 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1344:

/* Line 1455 of yacc.c  */
#line 6794 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	CB_REFERENCE ((yyval))->offset = CB_TREE (current_section);
	current_program->label_list = cb_cons ((yyval), current_program->label_list);
  ;}
    break;

  case 1348:

/* Line 1455 of yacc.c  */
#line 6809 "parser.y"
    {
	(yyval) = cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(1) - (1)]))->data));
	(yyval)->source_file = (yyvsp[(1) - (1)])->source_file;
	(yyval)->source_line = (yyvsp[(1) - (1)])->source_line;
  ;}
    break;

  case 1349:

/* Line 1455 of yacc.c  */
#line 6819 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1350:

/* Line 1455 of yacc.c  */
#line 6820 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1351:

/* Line 1455 of yacc.c  */
#line 6825 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	current_program->reference_list = cb_cons ((yyval), current_program->reference_list);
  ;}
    break;

  case 1352:

/* Line 1455 of yacc.c  */
#line 6832 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1353:

/* Line 1455 of yacc.c  */
#line 6833 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1356:

/* Line 1455 of yacc.c  */
#line 6845 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE ((yyval))->word->count > 0) {
		redefinition_error ((yyval));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1357:

/* Line 1455 of yacc.c  */
#line 6864 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1358:

/* Line 1455 of yacc.c  */
#line 6865 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1360:

/* Line 1455 of yacc.c  */
#line 6870 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1361:

/* Line 1455 of yacc.c  */
#line 6874 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1362:

/* Line 1455 of yacc.c  */
#line 6875 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1364:

/* Line 1455 of yacc.c  */
#line 6880 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1365:

/* Line 1455 of yacc.c  */
#line 6881 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1366:

/* Line 1455 of yacc.c  */
#line 6882 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1367:

/* Line 1455 of yacc.c  */
#line 6883 "parser.y"
    { (yyval) = cb_build_ppointer ((yyvsp[(4) - (4)])); ;}
    break;

  case 1368:

/* Line 1455 of yacc.c  */
#line 6884 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1373:

/* Line 1455 of yacc.c  */
#line 6892 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1374:

/* Line 1455 of yacc.c  */
#line 6893 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1375:

/* Line 1455 of yacc.c  */
#line 6894 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1381:

/* Line 1455 of yacc.c  */
#line 6906 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1382:

/* Line 1455 of yacc.c  */
#line 6907 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1394:

/* Line 1455 of yacc.c  */
#line 6941 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1395:

/* Line 1455 of yacc.c  */
#line 6949 "parser.y"
    { (yyval) = cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1396:

/* Line 1455 of yacc.c  */
#line 6953 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1397:

/* Line 1455 of yacc.c  */
#line 6954 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1398:

/* Line 1455 of yacc.c  */
#line 6955 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1399:

/* Line 1455 of yacc.c  */
#line 6956 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 1400:

/* Line 1455 of yacc.c  */
#line 6960 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1401:

/* Line 1455 of yacc.c  */
#line 6961 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); CB_REFERENCE ((yyvsp[(1) - (3)]))->chain = (yyvsp[(3) - (3)]); ;}
    break;

  case 1402:

/* Line 1455 of yacc.c  */
#line 6966 "parser.y"
    {
	if (cb_ref ((yyvsp[(0) - (3)])) != cb_error_node) {
		(yyval) = (yyvsp[(0) - (3)]);
		CB_REFERENCE ((yyvsp[(0) - (3)]))->subs = cb_list_reverse ((yyvsp[(2) - (3)]));
	}
  ;}
    break;

  case 1403:

/* Line 1455 of yacc.c  */
#line 6976 "parser.y"
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

  case 1404:

/* Line 1455 of yacc.c  */
#line 6994 "parser.y"
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

  case 1405:

/* Line 1455 of yacc.c  */
#line 7021 "parser.y"
    {
	if (cb_tree_category ((yyvsp[(1) - (1)])) != CB_CATEGORY_NUMERIC) {
		cb_error (_("Integer value expected"));
	} else if (CB_LITERAL ((yyvsp[(1) - (1)]))->sign < 0 || CB_LITERAL ((yyvsp[(1) - (1)]))->scale) {
		cb_error (_("Integer value expected"));
	}
	(yyval) = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1406:

/* Line 1455 of yacc.c  */
#line 7032 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1407:

/* Line 1455 of yacc.c  */
#line 7034 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (2)]);
	if (CB_LITERAL_P ((yyvsp[(2) - (2)]))) {
		CB_LITERAL ((yyvsp[(2) - (2)]))->all = 1;
	}
  ;}
    break;

  case 1408:

/* Line 1455 of yacc.c  */
#line 7043 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1409:

/* Line 1455 of yacc.c  */
#line 7044 "parser.y"
    { (yyval) = cb_concat_literals ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1410:

/* Line 1455 of yacc.c  */
#line 7048 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1411:

/* Line 1455 of yacc.c  */
#line 7049 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 1412:

/* Line 1455 of yacc.c  */
#line 7050 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1413:

/* Line 1455 of yacc.c  */
#line 7051 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 1414:

/* Line 1455 of yacc.c  */
#line 7052 "parser.y"
    { (yyval) = cb_high; ;}
    break;

  case 1415:

/* Line 1455 of yacc.c  */
#line 7053 "parser.y"
    { (yyval) = cb_low; ;}
    break;

  case 1416:

/* Line 1455 of yacc.c  */
#line 7054 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1417:

/* Line 1455 of yacc.c  */
#line 7063 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1418:

/* Line 1455 of yacc.c  */
#line 7067 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1419:

/* Line 1455 of yacc.c  */
#line 7071 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1420:

/* Line 1455 of yacc.c  */
#line 7075 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1421:

/* Line 1455 of yacc.c  */
#line 7079 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1422:

/* Line 1455 of yacc.c  */
#line 7083 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1423:

/* Line 1455 of yacc.c  */
#line 7087 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1424:

/* Line 1455 of yacc.c  */
#line 7091 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1425:

/* Line 1455 of yacc.c  */
#line 7095 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1426:

/* Line 1455 of yacc.c  */
#line 7099 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), NULL);
  ;}
    break;

  case 1427:

/* Line 1455 of yacc.c  */
#line 7103 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1428:

/* Line 1455 of yacc.c  */
#line 7107 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), NULL);
  ;}
    break;

  case 1429:

/* Line 1455 of yacc.c  */
#line 7113 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1430:

/* Line 1455 of yacc.c  */
#line 7114 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (4)]), NULL); ;}
    break;

  case 1431:

/* Line 1455 of yacc.c  */
#line 7115 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 1432:

/* Line 1455 of yacc.c  */
#line 7119 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1433:

/* Line 1455 of yacc.c  */
#line 7120 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1434:

/* Line 1455 of yacc.c  */
#line 7124 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1435:

/* Line 1455 of yacc.c  */
#line 7125 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1436:

/* Line 1455 of yacc.c  */
#line 7131 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_int0);
  ;}
    break;

  case 1437:

/* Line 1455 of yacc.c  */
#line 7138 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int1);
  ;}
    break;

  case 1438:

/* Line 1455 of yacc.c  */
#line 7145 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int2);
  ;}
    break;

  case 1439:

/* Line 1455 of yacc.c  */
#line 7155 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1440:

/* Line 1455 of yacc.c  */
#line 7162 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1441:

/* Line 1455 of yacc.c  */
#line 7172 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1442:

/* Line 1455 of yacc.c  */
#line 7179 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_ref ((yyvsp[(3) - (3)])));
  ;}
    break;

  case 1443:

/* Line 1455 of yacc.c  */
#line 7192 "parser.y"
    {
	non_const_word = 1;
  ;}
    break;

  case 1444:

/* Line 1455 of yacc.c  */
#line 7202 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1445:

/* Line 1455 of yacc.c  */
#line 7203 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1446:

/* Line 1455 of yacc.c  */
#line 7207 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1447:

/* Line 1455 of yacc.c  */
#line 7208 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1448:

/* Line 1455 of yacc.c  */
#line 7212 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1449:

/* Line 1455 of yacc.c  */
#line 7213 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1450:

/* Line 1455 of yacc.c  */
#line 7217 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1451:

/* Line 1455 of yacc.c  */
#line 7218 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1452:

/* Line 1455 of yacc.c  */
#line 7219 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 1453:

/* Line 1455 of yacc.c  */
#line 7223 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1454:

/* Line 1455 of yacc.c  */
#line 7224 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1455:

/* Line 1455 of yacc.c  */
#line 7228 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1456:

/* Line 1455 of yacc.c  */
#line 7229 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1457:

/* Line 1455 of yacc.c  */
#line 7233 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1458:

/* Line 1455 of yacc.c  */
#line 7234 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1459:

/* Line 1455 of yacc.c  */
#line 7238 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1460:

/* Line 1455 of yacc.c  */
#line 7239 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1472:

/* Line 1455 of yacc.c  */
#line 7252 "parser.y"
    { (yyval) = cb_int1; ;}
    break;



/* Line 1455 of yacc.c  */
#line 14453 "parser.c"
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
#line 7296 "parser.y"


