
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
#define YYLAST   5537

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  455
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  695
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1551
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2286

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
     248,   250,   252,   254,   256,   258,   262,   263,   269,   273,
     277,   281,   285,   286,   292,   294,   296,   297,   303,   305,
     307,   309,   311,   313,   315,   318,   320,   324,   325,   330,
     332,   336,   338,   340,   342,   344,   346,   348,   350,   352,
     354,   356,   358,   360,   364,   368,   370,   373,   375,   378,
     383,   385,   388,   390,   394,   399,   404,   408,   412,   417,
     421,   425,   426,   432,   433,   438,   439,   444,   445,   449,
     450,   453,   454,   461,   462,   465,   467,   469,   471,   473,
     475,   477,   479,   481,   483,   485,   487,   489,   491,   493,
     499,   504,   509,   510,   512,   514,   515,   517,   519,   521,
     523,   525,   530,   532,   534,   536,   543,   552,   553,   556,
     559,   561,   562,   565,   567,   571,   577,   578,   580,   582,
     587,   590,   593,   595,   596,   601,   607,   610,   612,   614,
     618,   620,   622,   626,   628,   630,   633,   638,   643,   648,
     655,   660,   664,   668,   671,   674,   677,   678,   682,   683,
     686,   688,   691,   693,   695,   697,   703,   704,   706,   708,
     710,   716,   718,   721,   724,   725,   728,   733,   734,   744,
     745,   746,   752,   753,   757,   758,   761,   765,   768,   771,
     773,   775,   776,   781,   782,   785,   788,   791,   793,   795,
     797,   799,   801,   803,   805,   807,   809,   811,   817,   818,
     820,   822,   827,   834,   844,   845,   849,   850,   853,   854,
     857,   861,   863,   865,   871,   877,   879,   881,   885,   891,
     892,   895,   897,   899,   901,   907,   912,   916,   921,   925,
     929,   933,   934,   935,   941,   942,   944,   945,   948,   952,
     957,   960,   962,   963,   968,   970,   971,   973,   975,   977,
     978,   981,   983,   987,   991,   998,   999,  1002,  1004,  1006,
    1008,  1010,  1012,  1014,  1016,  1018,  1020,  1022,  1024,  1026,
    1028,  1030,  1032,  1035,  1039,  1040,  1043,  1046,  1048,  1050,
    1054,  1056,  1058,  1060,  1062,  1064,  1066,  1068,  1070,  1072,
    1074,  1076,  1078,  1080,  1082,  1084,  1086,  1088,  1090,  1092,
    1095,  1098,  1100,  1103,  1106,  1108,  1111,  1114,  1116,  1119,
    1122,  1124,  1127,  1130,  1132,  1134,  1138,  1142,  1150,  1151,
    1154,  1155,  1159,  1161,  1162,  1168,  1170,  1172,  1173,  1177,
    1179,  1182,  1184,  1187,  1190,  1191,  1193,  1195,  1199,  1201,
    1202,  1211,  1213,  1216,  1218,  1222,  1223,  1227,  1230,  1235,
    1238,  1239,  1240,  1246,  1247,  1248,  1254,  1255,  1256,  1262,
    1263,  1265,  1267,  1270,  1276,  1277,  1280,  1283,  1287,  1289,
    1291,  1294,  1297,  1300,  1301,  1303,  1305,  1308,  1317,  1318,
    1322,  1323,  1328,  1329,  1334,  1335,  1339,  1340,  1344,  1346,
    1351,  1354,  1356,  1358,  1359,  1362,  1367,  1368,  1371,  1373,
    1375,  1377,  1379,  1381,  1383,  1385,  1387,  1389,  1391,  1393,
    1395,  1397,  1399,  1401,  1403,  1407,  1409,  1411,  1413,  1415,
    1417,  1419,  1421,  1426,  1431,  1434,  1436,  1438,  1441,  1445,
    1447,  1451,  1458,  1461,  1465,  1468,  1470,  1473,  1476,  1478,
    1481,  1482,  1484,  1486,  1491,  1494,  1495,  1497,  1499,  1500,
    1501,  1502,  1509,  1510,  1512,  1514,  1517,  1519,  1520,  1526,
    1527,  1530,  1532,  1534,  1536,  1538,  1541,  1544,  1546,  1548,
    1550,  1552,  1554,  1556,  1558,  1560,  1562,  1564,  1570,  1576,
    1580,  1584,  1586,  1588,  1590,  1592,  1594,  1596,  1598,  1601,
    1604,  1607,  1608,  1610,  1612,  1614,  1616,  1617,  1619,  1621,
    1623,  1625,  1629,  1630,  1631,  1632,  1642,  1643,  1644,  1648,
    1649,  1653,  1655,  1658,  1663,  1664,  1667,  1670,  1671,  1675,
    1679,  1684,  1688,  1689,  1691,  1692,  1695,  1696,  1697,  1705,
    1706,  1709,  1711,  1713,  1715,  1718,  1720,  1725,  1728,  1730,
    1732,  1733,  1735,  1736,  1737,  1741,  1742,  1745,  1747,  1749,
    1751,  1753,  1755,  1757,  1759,  1761,  1763,  1765,  1767,  1769,
    1771,  1773,  1775,  1777,  1779,  1781,  1783,  1785,  1787,  1789,
    1791,  1793,  1795,  1797,  1799,  1801,  1803,  1805,  1807,  1809,
    1811,  1813,  1815,  1817,  1819,  1821,  1823,  1825,  1827,  1829,
    1831,  1833,  1835,  1837,  1839,  1841,  1843,  1845,  1846,  1851,
    1856,  1861,  1865,  1869,  1873,  1878,  1882,  1887,  1891,  1895,
    1899,  1904,  1910,  1914,  1919,  1923,  1927,  1928,  1932,  1936,
    1939,  1942,  1945,  1949,  1953,  1957,  1958,  1961,  1963,  1966,
    1968,  1970,  1972,  1974,  1976,  1978,  1980,  1984,  1988,  1992,
    1996,  1998,  2000,  2002,  2004,  2006,  2008,  2009,  2011,  2012,
    2017,  2022,  2028,  2035,  2036,  2039,  2040,  2042,  2043,  2047,
    2051,  2057,  2058,  2061,  2064,  2065,  2071,  2072,  2075,  2076,
    2085,  2086,  2087,  2091,  2093,  2096,  2099,  2103,  2104,  2107,
    2110,  2113,  2114,  2117,  2120,  2121,  2122,  2126,  2127,  2128,
    2132,  2133,  2135,  2136,  2140,  2141,  2144,  2145,  2149,  2150,
    2154,  2155,  2157,  2161,  2165,  2168,  2170,  2172,  2173,  2178,
    2183,  2184,  2186,  2188,  2190,  2192,  2194,  2195,  2202,  2203,
    2205,  2206,  2211,  2212,  2217,  2221,  2225,  2229,  2233,  2238,
    2245,  2252,  2259,  2266,  2267,  2270,  2273,  2275,  2278,  2280,
    2282,  2285,  2288,  2290,  2292,  2294,  2296,  2298,  2302,  2306,
    2310,  2314,  2316,  2318,  2319,  2321,  2322,  2327,  2332,  2339,
    2346,  2355,  2364,  2365,  2367,  2368,  2373,  2374,  2380,  2382,
    2386,  2388,  2390,  2392,  2395,  2397,  2400,  2401,  2405,  2406,
    2407,  2411,  2414,  2418,  2420,  2424,  2427,  2429,  2431,  2433,
    2434,  2437,  2438,  2440,  2441,  2445,  2446,  2448,  2450,  2453,
    2455,  2457,  2458,  2462,  2463,  2467,  2468,  2474,  2475,  2479,
    2480,  2483,  2484,  2485,  2494,  2498,  2499,  2500,  2504,  2505,
    2507,  2508,  2516,  2517,  2520,  2521,  2525,  2529,  2530,  2533,
    2535,  2538,  2543,  2545,  2547,  2549,  2551,  2553,  2555,  2557,
    2558,  2560,  2561,  2565,  2566,  2571,  2573,  2575,  2577,  2579,
    2582,  2584,  2586,  2588,  2589,  2593,  2595,  2598,  2601,  2604,
    2606,  2608,  2610,  2613,  2616,  2618,  2621,  2626,  2629,  2630,
    2632,  2634,  2636,  2638,  2643,  2649,  2650,  2655,  2656,  2658,
    2659,  2663,  2664,  2668,  2672,  2677,  2678,  2683,  2688,  2695,
    2696,  2698,  2699,  2703,  2704,  2710,  2712,  2714,  2716,  2718,
    2719,  2723,  2724,  2728,  2731,  2732,  2736,  2739,  2740,  2745,
    2748,  2749,  2751,  2753,  2757,  2758,  2760,  2763,  2767,  2771,
    2772,  2776,  2778,  2782,  2790,  2791,  2802,  2803,  2806,  2807,
    2810,  2813,  2817,  2821,  2824,  2825,  2829,  2830,  2832,  2834,
    2835,  2837,  2838,  2843,  2844,  2852,  2853,  2855,  2856,  2864,
    2865,  2868,  2872,  2873,  2875,  2877,  2878,  2883,  2888,  2889,
    2897,  2898,  2901,  2902,  2903,  2908,  2910,  2913,  2914,  2919,
    2920,  2922,  2923,  2927,  2929,  2931,  2933,  2935,  2937,  2942,
    2947,  2951,  2956,  2958,  2960,  2962,  2965,  2969,  2971,  2974,
    2978,  2982,  2983,  2987,  2988,  2996,  2997,  3003,  3004,  3007,
    3008,  3011,  3012,  3016,  3017,  3020,  3025,  3026,  3029,  3034,
    3035,  3036,  3044,  3045,  3050,  3053,  3056,  3059,  3062,  3065,
    3066,  3068,  3069,  3074,  3077,  3078,  3081,  3084,  3085,  3094,
    3096,  3099,  3101,  3105,  3109,  3110,  3114,  3115,  3117,  3118,
    3123,  3128,  3135,  3142,  3143,  3145,  3148,  3149,  3151,  3152,
    3156,  3157,  3165,  3166,  3171,  3172,  3174,  3176,  3177,  3187,
    3188,  3192,  3194,  3198,  3201,  3204,  3207,  3211,  3212,  3216,
    3217,  3221,  3222,  3226,  3227,  3229,  3231,  3233,  3235,  3244,
    3245,  3247,  3249,  3251,  3253,  3255,  3257,  3258,  3260,  3261,
    3263,  3265,  3267,  3269,  3271,  3273,  3275,  3276,  3278,  3284,
    3286,  3289,  3295,  3296,  3305,  3306,  3309,  3310,  3315,  3319,
    3323,  3325,  3327,  3328,  3330,  3332,  3333,  3335,  3338,  3341,
    3342,  3343,  3347,  3348,  3349,  3353,  3356,  3357,  3358,  3362,
    3363,  3364,  3368,  3371,  3372,  3373,  3377,  3378,  3379,  3383,
    3385,  3387,  3390,  3391,  3395,  3396,  3400,  3402,  3404,  3407,
    3408,  3412,  3413,  3417,  3418,  3420,  3422,  3424,  3427,  3428,
    3432,  3433,  3437,  3438,  3442,  3444,  3446,  3447,  3450,  3453,
    3456,  3459,  3462,  3465,  3468,  3471,  3474,  3477,  3480,  3483,
    3486,  3489,  3490,  3493,  3496,  3499,  3502,  3505,  3508,  3511,
    3514,  3517,  3520,  3523,  3526,  3529,  3532,  3535,  3538,  3541,
    3544,  3547,  3550,  3553,  3556,  3559,  3562,  3565,  3567,  3570,
    3572,  3574,  3577,  3579,  3582,  3584,  3590,  3595,  3597,  3603,
    3608,  3610,  3614,  3615,  3617,  3619,  3621,  3625,  3629,  3633,
    3637,  3640,  3643,  3647,  3651,  3653,  3657,  3659,  3662,  3665,
    3667,  3669,  3671,  3674,  3676,  3678,  3681,  3683,  3684,  3687,
    3689,  3691,  3693,  3697,  3699,  3701,  3704,  3706,  3707,  3709,
    3711,  3713,  3715,  3717,  3720,  3722,  3726,  3728,  3731,  3733,
    3737,  3741,  3745,  3750,  3754,  3756,  3758,  3760,  3762,  3766,
    3770,  3774,  3776,  3778,  3780,  3782,  3784,  3786,  3788,  3790,
    3792,  3794,  3796,  3798,  3800,  3802,  3804,  3806,  3808,  3810,
    3812,  3814,  3816,  3819,  3822,  3826,  3828,  3832,  3836,  3841,
    3847,  3849,  3851,  3854,  3856,  3860,  3862,  3864,  3866,  3868,
    3870,  3872,  3874,  3877,  3880,  3886,  3892,  3898,  3904,  3910,
    3916,  3922,  3927,  3933,  3936,  3937,  3942,  3948,  3949,  3953,
    3954,  3956,  3958,  3962,  3966,  3968,  3972,  3974,  3978,  3979,
    3980,  3982,  3983,  3985,  3986,  3988,  3989,  3991,  3993,  3994,
    3996,  3997,  3999,  4000,  4002,  4003,  4006,  4008,  4010,  4013,
    4016,  4019,  4021,  4024,  4026,  4027,  4029,  4030,  4032,  4033,
    4035,  4036,  4038,  4039,  4041,  4042,  4044,  4045,  4047,  4048,
    4050,  4051,  4053,  4054,  4056,  4057,  4059,  4060,  4062,  4063,
    4065,  4066,  4068,  4069,  4071,  4072,  4074,  4075,  4077,  4078,
    4080,  4082,  4083,  4085,  4086,  4088,  4090,  4091,  4093,  4094,
    4096,  4097,  4099,  4100,  4102,  4103,  4105,  4106,  4108,  4111,
    4112,  4114,  4115,  4117,  4118,  4120,  4121,  4123,  4124,  4126,
    4127,  4129,  4130,  4132,  4135,  4136,  4138,  4139,  4141,  4142,
    4144,  4145,  4147,  4148,  4150,  4151,  4153,  4154,  4156,  4157,
    4159,  4160
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     456,     0,    -1,    -1,   457,   458,    -1,   459,    -1,   458,
     459,    -1,   460,    -1,   466,    -1,    -1,    -1,   473,   481,
     461,   580,   462,   714,   469,   470,    -1,    -1,    -1,   473,
     481,   464,   580,   465,   714,   469,   471,    -1,    -1,    -1,
     475,   481,   467,   580,   468,   714,   472,    -1,    -1,   463,
      -1,   469,   463,    -1,    -1,   136,   476,   447,    -1,   136,
     476,   447,    -1,   132,   476,   447,    -1,    -1,   304,   447,
     476,   477,   474,   478,   447,    -1,   179,   447,   476,   477,
     447,    -1,   305,    -1,   230,    -1,    -1,    27,   230,    -1,
      -1,  1124,   479,  1135,    -1,    72,    -1,    72,   480,    -1,
     480,    -1,   399,    -1,   315,    -1,    -1,   147,   117,   447,
     482,   533,    -1,    -1,    82,   349,   447,   483,    -1,    -1,
     483,   484,    -1,   485,    -1,   489,    -1,   502,    -1,   497,
      -1,   370,   447,   486,    -1,    -1,   488,   447,    -1,   488,
     487,   447,    -1,   487,   447,    -1,  1149,   104,   243,    -1,
     434,    -1,   268,   447,   490,    -1,    -1,   488,   447,    -1,
     488,   491,   447,    -1,   491,   447,    -1,   492,    -1,   491,
     492,    -1,   493,    -1,   495,    -1,   496,    -1,   239,   365,
    1124,  1084,   494,    -1,    56,    -1,   435,    -1,  1135,  1107,
    1124,  1063,    -1,   351,  1124,  1084,    -1,   330,   447,   498,
      -1,    -1,   499,   447,    -1,   500,    -1,   499,   500,    -1,
     178,   501,   207,    -1,   178,     9,   207,    -1,   230,    -1,
     501,   230,    -1,   372,   447,   503,    -1,    -1,   504,   447,
      -1,   505,    -1,   504,   505,    -1,   506,    -1,   510,    -1,
     519,    -1,   526,    -1,   523,    -1,   527,    -1,   528,    -1,
     529,    -1,   530,    -1,   531,    -1,   532,    -1,   434,  1124,
      94,    -1,    -1,   434,  1124,  1066,   507,   508,    -1,    25,
    1124,  1066,    -1,    26,  1124,  1066,    -1,   148,  1124,  1066,
      -1,   149,  1124,  1066,    -1,    -1,   508,   509,  1142,  1124,
    1066,    -1,   273,    -1,   271,    -1,    -1,    11,  1066,   511,
    1124,   512,    -1,   249,    -1,   374,    -1,   375,    -1,   121,
      -1,   513,    -1,   514,    -1,   513,   514,    -1,   517,    -1,
     517,   393,   517,    -1,    -1,   517,    17,   515,   516,    -1,
     518,    -1,   516,    17,   518,    -1,   230,    -1,   371,    -1,
     440,    -1,   308,    -1,   191,    -1,   237,    -1,   230,    -1,
     371,    -1,   440,    -1,   308,    -1,   191,    -1,   237,    -1,
     385,  1117,   520,    -1,   521,  1125,   522,    -1,  1066,    -1,
     521,  1066,    -1,  1084,    -1,   522,  1084,    -1,    57,  1066,
    1124,   524,    -1,   525,    -1,   524,   525,    -1,  1087,    -1,
    1087,   393,  1087,    -1,   231,  1066,  1124,  1063,    -1,    95,
    1139,  1124,   230,    -1,   105,  1124,    67,    -1,    97,  1124,
    1063,    -1,    94,   377,  1124,  1063,    -1,   345,  1124,  1063,
      -1,   159,  1124,  1063,    -1,    -1,   204,   349,   447,   536,
     569,    -1,    -1,   166,   447,   534,   537,    -1,    -1,   212,
     447,   535,   570,    -1,    -1,   166,   447,   537,    -1,    -1,
     537,   538,    -1,    -1,   352,  1101,  1066,   539,   540,   447,
      -1,    -1,   540,   541,    -1,   542,    -1,   546,    -1,   548,
      -1,   553,    -1,   554,    -1,   556,    -1,   560,    -1,   562,
      -1,   563,    -1,   564,    -1,   565,    -1,   566,    -1,   567,
      -1,     1,    -1,    29,  1147,   544,   543,   545,    -1,    29,
    1147,   544,   114,    -1,    29,  1147,   544,   298,    -1,    -1,
     114,    -1,   298,    -1,    -1,   164,    -1,   120,    -1,   230,
      -1,   115,    -1,  1081,    -1,     4,  1129,  1124,   547,    -1,
     357,    -1,   120,    -1,   309,    -1,    19,   312,  1126,  1124,
    1063,  1097,    -1,    19,   312,  1126,  1124,  1063,   552,   549,
    1097,    -1,    -1,   550,   551,    -1,   549,   551,    -1,  1063,
      -1,    -1,   369,  1124,    -1,   448,    -1,  1107,  1124,   434,
      -1,   555,   377,  1124,  1063,  1064,    -1,    -1,   398,    -1,
     367,    -1,   234,  1129,  1124,   557,    -1,   238,   558,    -1,
      32,   558,    -1,   161,    -1,    -1,   433,   234,   273,   559,
      -1,   433,   234,   273,   245,   559,    -1,   433,   340,    -1,
     312,    -1,   314,    -1,   279,  1124,   561,    -1,   561,    -1,
     198,    -1,   312,  1114,   357,    -1,   357,    -1,   319,    -1,
     227,   357,    -1,   285,  1116,  1124,  1065,    -1,   312,   110,
    1124,   374,    -1,   312,  1126,  1124,  1063,    -1,   312,  1126,
    1124,  1063,   552,   549,    -1,   319,  1126,  1124,  1063,    -1,
     332,  1084,  1111,    -1,   359,  1149,   568,    -1,     9,  1134,
      -1,   254,  1134,    -1,   311,   274,    -1,    -1,   212,   447,
     570,    -1,    -1,   571,   447,    -1,   572,    -1,   571,   572,
      -1,   573,    -1,   575,    -1,   579,    -1,   343,   574,  1111,
    1121,  1054,    -1,    -1,   312,    -1,   367,    -1,   368,    -1,
     245,  1120,  1143,  1118,   576,    -1,   577,    -1,   576,   577,
      -1,  1055,   578,    -1,    -1,   294,  1084,    -1,    22,    71,
    1132,  1062,    -1,    -1,    99,   117,   447,   581,   612,   657,
     659,   661,   702,    -1,    -1,    -1,   398,   349,   447,   582,
     584,    -1,    -1,   587,   583,   586,    -1,    -1,   584,   585,
      -1,   587,   588,   614,    -1,   588,   614,    -1,   586,   585,
      -1,   165,    -1,   347,    -1,    -1,  1055,   589,   590,   447,
      -1,    -1,   590,   591,    -1,  1124,   164,    -1,  1124,   184,
      -1,   592,    -1,   594,    -1,   598,    -1,   600,    -1,   602,
      -1,   603,    -1,   609,    -1,   610,    -1,   611,    -1,     1,
      -1,    47,  1118,  1084,   597,   593,    -1,    -1,   314,    -1,
      56,    -1,   312,  1118,  1084,  1117,    -1,   312,  1118,  1084,
     396,  1084,  1117,    -1,   312,  1124,   428,  1123,  1141,   596,
     597,  1117,   595,    -1,    -1,   111,  1132,  1063,    -1,    -1,
    1122,  1084,    -1,    -1,   396,  1084,    -1,   215,  1105,   599,
      -1,   373,    -1,   272,    -1,   427,   270,   434,  1124,   601,
      -1,   427,   270,   167,  1124,   601,    -1,   230,    -1,  1081,
      -1,    99,  1105,  1062,    -1,   225,  1124,  1065,  1128,   604,
      -1,    -1,   604,   605,    -1,   606,    -1,   607,    -1,   608,
      -1,  1149,   171,  1113,  1065,  1128,    -1,  1113,   402,  1065,
    1128,    -1,  1113,    48,  1065,    -1,   313,  1129,  1124,   434,
      -1,    61,  1124,   434,    -1,   325,  1124,   701,    -1,   327,
    1110,   701,    -1,    -1,    -1,   436,   349,   447,   613,   614,
      -1,    -1,   615,    -1,    -1,   616,   617,    -1,  1095,   618,
     447,    -1,   617,  1095,   618,   447,    -1,   617,   447,    -1,
     625,    -1,    -1,   620,   621,   619,   626,    -1,   434,    -1,
      -1,   168,    -1,   434,    -1,   434,    -1,    -1,  1124,   184,
      -1,  1085,    -1,   221,  1131,  1080,    -1,    50,  1131,  1080,
      -1,   620,   622,    83,   623,  1112,   624,    -1,    -1,   626,
     627,    -1,   628,    -1,   629,    -1,   631,    -1,   632,    -1,
     633,    -1,   635,    -1,   636,    -1,   645,    -1,   646,    -1,
     648,    -1,   649,    -1,   650,    -1,   655,    -1,   656,    -1,
       1,    -1,   316,  1080,    -1,  1124,   164,   630,    -1,    -1,
      27,   230,    -1,  1124,   184,    -1,   291,    -1,   634,    -1,
     424,  1124,   634,    -1,    37,    -1,    73,    -1,    75,    -1,
      76,    -1,    77,    -1,    78,    -1,    79,    -1,    80,    -1,
     115,    -1,   197,    -1,   284,    -1,   293,    -1,   306,    -1,
     364,    -1,   362,    -1,   363,    -1,   413,    -1,   411,    -1,
     412,    -1,    39,   361,    -1,    39,   410,    -1,    39,    -1,
      42,   361,    -1,    42,   410,    -1,    42,    -1,    41,   361,
      -1,    41,   410,    -1,    41,    -1,    40,   361,    -1,    40,
     410,    -1,    40,    -1,    38,   361,    -1,    38,   410,    -1,
      38,    -1,   247,    -1,  1140,   219,  1103,    -1,  1140,   403,
    1103,    -1,   269,  1084,   637,  1146,   638,   639,   642,    -1,
      -1,   396,  1084,    -1,    -1,   111,  1132,  1063,    -1,   640,
      -1,    -1,   640,   641,  1126,  1124,  1062,    -1,    28,    -1,
     112,    -1,    -1,   198,  1115,   643,    -1,   644,    -1,   643,
     644,    -1,   434,    -1,   213,  1137,    -1,   386,   647,    -1,
      -1,   220,    -1,   339,    -1,    43,  1148,   440,    -1,    34,
      -1,    -1,   427,  1125,   652,   651,  1148,  1138,  1147,   654,
      -1,   653,    -1,   652,   653,    -1,  1085,    -1,  1085,   393,
    1085,    -1,    -1,   397,  1124,  1085,    -1,   323,  1081,    -1,
     323,  1081,   393,  1081,    -1,    21,   221,    -1,    -1,    -1,
     233,   349,   447,   658,   614,    -1,    -1,    -1,   229,   349,
     447,   660,   614,    -1,    -1,    -1,   325,   349,   447,   662,
     663,    -1,    -1,   664,    -1,   665,    -1,   664,   665,    -1,
     310,   701,   666,   447,   680,    -1,    -1,   666,   667,    -1,
    1124,   184,    -1,    60,  1124,  1076,    -1,   668,    -1,   672,
      -1,    87,   669,    -1,    88,   669,    -1,   670,   671,    -1,
      -1,   169,    -1,  1079,    -1,   671,  1079,    -1,   286,  1125,
     678,   673,   674,   675,   676,   677,    -1,    -1,   189,  1124,
    1084,    -1,    -1,   170,   113,  1124,  1084,    -1,    -1,   216,
      90,  1124,  1084,    -1,    -1,   217,  1124,  1084,    -1,    -1,
     171,  1124,  1084,    -1,  1084,    -1,  1084,   679,  1084,    66,
      -1,  1084,   679,    -1,   227,    -1,   228,    -1,    -1,   680,
     681,    -1,   620,   621,   682,   447,    -1,    -1,   682,   683,
      -1,   684,    -1,   686,    -1,   693,    -1,   632,    -1,   633,
      -1,   635,    -1,   645,    -1,   687,    -1,   648,    -1,   698,
      -1,   688,    -1,   650,    -1,   691,    -1,   699,    -1,   636,
      -1,   692,    -1,   406,  1124,   685,    -1,   329,    -1,   288,
      -1,    90,    -1,   113,    -1,    89,    -1,   287,    -1,   328,
      -1,   252,   188,  1124,  1084,    -1,    65,  1130,  1124,  1084,
      -1,    65,   264,    -1,    66,    -1,   689,    -1,   688,   689,
      -1,   383,  1131,   690,    -1,  1063,    -1,   296,   430,  1035,
      -1,   428,  1079,   176,  1070,    49,  1070,    -1,   694,   695,
      -1,   227,   697,  1125,    -1,   228,  1110,    -1,   696,    -1,
     695,   696,    -1,   292,  1084,    -1,  1084,    -1,   252,   286,
      -1,    -1,   263,    -1,   264,    -1,   369,  1124,  1079,  1102,
      -1,   188,   700,    -1,    -1,   199,    -1,   434,    -1,    -1,
      -1,    -1,   344,   349,   447,   703,   704,   705,    -1,    -1,
     706,    -1,   707,    -1,   706,   707,    -1,   625,    -1,    -1,
     620,   621,   708,   709,   447,    -1,    -1,   709,   710,    -1,
      44,    -1,    45,    -1,    36,    -1,    46,    -1,   155,   150,
      -1,   155,   152,    -1,   190,    -1,   236,    -1,   336,    -1,
     407,    -1,   283,    -1,    31,    -1,   350,    -1,   331,    -1,
     177,    -1,   307,    -1,   227,  1130,  1124,   711,  1078,    -1,
      65,  1130,  1124,   712,  1078,    -1,   173,  1124,  1078,    -1,
      33,  1124,  1078,    -1,   633,    -1,   648,    -1,   645,    -1,
     635,    -1,   650,    -1,   632,    -1,   713,    -1,   426,  1079,
      -1,   176,  1077,    -1,   396,  1079,    -1,    -1,   292,    -1,
     441,    -1,   241,    -1,   442,    -1,    -1,   292,    -1,   441,
      -1,   241,    -1,   442,    -1,   269,  1084,  1146,    -1,    -1,
      -1,    -1,   300,   117,   717,   725,   447,   715,   726,   716,
     728,    -1,    -1,    -1,   426,   718,   720,    -1,    -1,    54,
     719,   720,    -1,   721,    -1,   720,   721,    -1,   722,   723,
     724,   434,    -1,    -1,  1115,   318,    -1,  1115,   427,    -1,
      -1,   365,  1124,    31,    -1,   365,  1124,   107,    -1,   410,
     365,  1124,  1084,    -1,   365,  1124,  1084,    -1,    -1,   276,
      -1,    -1,   334,   434,    -1,    -1,    -1,   106,   447,   727,
     728,   123,   106,   447,    -1,    -1,   728,   729,    -1,   730,
      -1,   731,    -1,   732,    -1,   738,   447,    -1,     1,    -1,
     733,   349,   734,   447,    -1,   434,   447,    -1,   733,    -1,
     434,    -1,    -1,   230,    -1,    -1,    -1,   736,   737,   738,
      -1,    -1,   738,   739,    -1,   740,    -1,   750,    -1,   755,
      -1,   759,    -1,   762,    -1,   775,    -1,   778,    -1,   788,
      -1,   783,    -1,   789,    -1,   790,    -1,   793,    -1,   795,
      -1,   802,    -1,   806,    -1,   808,    -1,   823,    -1,   826,
      -1,   828,    -1,   830,    -1,   833,    -1,   835,    -1,   841,
      -1,   850,    -1,   852,    -1,   869,    -1,   871,    -1,   874,
      -1,   878,    -1,   884,    -1,   894,    -1,   901,    -1,   903,
      -1,   906,    -1,   910,    -1,   911,    -1,   922,    -1,   933,
      -1,   943,    -1,   949,    -1,   952,    -1,   958,    -1,   962,
      -1,   964,    -1,   966,    -1,   968,    -1,   971,    -1,   982,
      -1,   995,    -1,   253,    -1,    -1,     3,   741,   742,   749,
      -1,  1079,   743,   746,  1002,    -1,  1079,   176,   157,   214,
      -1,  1079,   176,   228,    -1,  1079,   176,    66,    -1,  1079,
     176,   100,    -1,  1079,   176,   100,   439,    -1,  1079,   176,
     101,    -1,  1079,   176,   101,   438,    -1,  1079,   176,   102,
      -1,  1079,   176,   394,    -1,  1079,   176,    68,    -1,  1079,
     176,   149,  1002,    -1,  1079,   176,   147,  1074,  1002,    -1,
    1079,   176,    25,    -1,  1079,   176,    26,  1002,    -1,  1079,
     176,  1057,    -1,  1079,   176,   434,    -1,    -1,  1113,   744,
     745,    -1,  1113,   745,   744,    -1,  1113,   744,    -1,  1113,
     745,    -1,    30,  1074,    -1,   227,  1130,  1076,    -1,    65,
    1130,  1076,    -1,   294,  1130,  1076,    -1,    -1,   433,   747,
      -1,   748,    -1,   747,   748,    -1,    36,    -1,    46,    -1,
     190,    -1,   236,    -1,   336,    -1,   407,    -1,   283,    -1,
     173,  1124,  1078,    -1,    33,  1124,  1078,    -1,   346,   416,
    1034,    -1,   346,   118,  1034,    -1,    31,    -1,   177,    -1,
     331,    -1,   350,    -1,   417,    -1,   307,    -1,    -1,   124,
      -1,    -1,     5,   751,   752,   754,    -1,  1069,   396,  1050,
    1008,    -1,  1069,   753,   183,  1050,  1008,    -1,    92,  1079,
     396,  1079,  1102,  1008,    -1,    -1,   396,  1070,    -1,    -1,
     125,    -1,    -1,    10,   756,   757,    -1,   434,  1098,   758,
      -1,  1036,    56,  1098,   334,  1068,    -1,    -1,   334,  1068,
      -1,    18,   760,    -1,    -1,   760,  1059,   396,   761,  1059,
      -1,    -1,   302,   396,    -1,    -1,    51,   763,  1077,   764,
     769,   770,   772,   774,    -1,    -1,    -1,   426,   765,   766,
      -1,   767,    -1,   766,   767,    -1,   768,   272,    -1,   768,
     723,  1070,    -1,    -1,  1115,   318,    -1,  1115,    85,    -1,
    1115,   427,    -1,    -1,   334,  1079,    -1,   183,  1079,    -1,
      -1,    -1,   989,   771,   735,    -1,    -1,    -1,   990,   773,
     735,    -1,    -1,   126,    -1,    -1,    52,   776,   777,    -1,
      -1,   777,  1076,    -1,    -1,    59,   779,   780,    -1,    -1,
     780,  1055,   781,    -1,    -1,   782,    -1,   782,  1121,   322,
      -1,  1149,   254,   337,    -1,  1149,   234,    -1,   317,    -1,
     408,    -1,    -1,    74,   784,   785,   786,    -1,  1050,   787,
    1036,  1008,    -1,    -1,   127,    -1,   448,    -1,   153,    -1,
      70,    -1,    86,    -1,    -1,   108,   791,  1055,  1136,  1028,
     792,    -1,    -1,   128,    -1,    -1,   108,   794,   398,  1054,
      -1,    -1,   115,   796,   797,   801,    -1,  1076,   421,  1003,
      -1,  1076,   422,  1003,    -1,  1076,   419,  1003,    -1,  1076,
     420,  1003,    -1,  1069,   743,   798,  1003,    -1,  1069,   743,
     418,  1057,   798,  1003,    -1,  1069,   743,   418,   434,   798,
    1003,    -1,  1069,   743,   418,   298,   798,  1003,    -1,  1069,
     743,   418,    94,   798,  1003,    -1,    -1,  1149,   262,    -1,
     433,   799,    -1,   800,    -1,   799,   800,    -1,    36,    -1,
      46,    -1,   155,   150,    -1,   155,   152,    -1,   190,    -1,
     236,    -1,   336,    -1,   407,    -1,   283,    -1,   173,  1124,
    1078,    -1,    33,  1124,  1078,    -1,   346,   416,  1034,    -1,
     346,   118,  1034,    -1,    44,    -1,    45,    -1,    -1,   129,
      -1,    -1,   116,   803,   804,   805,    -1,  1070,   206,  1050,
    1008,    -1,  1070,   206,  1070,   183,  1050,  1008,    -1,  1070,
      49,  1070,   183,  1050,  1008,    -1,  1070,   206,  1070,   183,
    1051,   321,  1051,  1008,    -1,  1070,    49,  1070,   183,  1051,
     321,  1051,  1008,    -1,    -1,   130,    -1,    -1,   146,   807,
     230,   764,    -1,    -1,   158,   809,   810,   812,   822,    -1,
     811,    -1,   810,  1109,   811,    -1,  1036,    -1,   401,    -1,
     397,    -1,   813,   816,    -1,   814,    -1,   813,   814,    -1,
      -1,   818,   815,   735,    -1,    -1,    -1,   432,   817,   735,
      -1,   430,   819,    -1,   818,   430,   819,    -1,   820,    -1,
     819,  1109,   820,    -1,  1037,   821,    -1,    21,    -1,   401,
      -1,   397,    -1,    -1,   393,  1036,    -1,    -1,   131,    -1,
      -1,   162,   824,   825,    -1,    -1,   303,    -1,   290,    -1,
     290,    98,    -1,   349,    -1,   289,    -1,    -1,   175,   827,
    1067,    -1,    -1,   182,   829,  1079,    -1,    -1,   185,  1147,
     831,  1058,   832,    -1,    -1,   111,  1132,  1079,    -1,    -1,
     186,   834,    -1,    -1,    -1,   193,   836,  1035,  1145,   837,
     735,   838,   840,    -1,   193,     1,   133,    -1,    -1,    -1,
     122,   839,   735,    -1,    -1,   133,    -1,    -1,   200,   842,
    1067,   843,   844,   845,   849,    -1,    -1,  1149,   168,    -1,
      -1,     9,  1147,   427,    -1,   848,  1147,   427,    -1,    -1,
     324,   846,    -1,   847,    -1,   846,   847,    -1,   848,  1119,
      49,  1070,    -1,    12,    -1,    15,    -1,   265,    -1,    16,
      -1,   266,    -1,   247,    -1,   248,    -1,    -1,   107,    -1,
      -1,   202,   851,   671,    -1,    -1,   205,   853,   854,   855,
      -1,  1079,    -1,  1085,    -1,  1088,    -1,   856,    -1,   855,
     856,    -1,   857,    -1,   861,    -1,   866,    -1,    -1,   387,
     858,   859,    -1,   860,    -1,   859,   860,    -1,  1074,   172,
      -1,    56,   867,    -1,     9,    -1,   219,    -1,   403,    -1,
    1074,   867,    -1,   324,   862,    -1,   863,    -1,   862,   863,
      -1,    56,    49,  1074,   867,    -1,   864,   865,    -1,    -1,
       9,    -1,   219,    -1,   170,    -1,   403,    -1,  1074,    49,
    1075,   867,    -1,    91,  1074,   396,  1075,   867,    -1,    -1,
     867,   999,   868,  1070,    -1,    -1,   399,    -1,    -1,   240,
     870,   935,    -1,    -1,   244,   872,   873,    -1,  1070,   396,
    1067,    -1,    92,  1070,   396,  1067,    -1,    -1,   246,   875,
     876,   877,    -1,  1070,    49,  1050,  1008,    -1,  1070,    49,
    1070,   183,  1050,  1008,    -1,    -1,   134,    -1,    -1,   275,
     879,   880,    -1,    -1,   880,   881,   882,  1054,   883,    -1,
     203,    -1,   281,    -1,   211,    -1,   163,    -1,    -1,   359,
    1149,   568,    -1,    -1,  1149,   254,   337,    -1,  1149,   234,
      -1,    -1,   290,   885,   886,    -1,   889,   890,    -1,    -1,
     890,   887,   735,   888,    -1,   890,   135,    -1,    -1,   135,
      -1,  1059,    -1,  1059,   393,  1059,    -1,    -1,   174,    -1,
    1077,   395,    -1,   891,   415,  1035,    -1,   891,   428,   892,
      -1,    -1,  1149,   390,   999,    -1,   893,    -1,   892,     8,
     893,    -1,  1079,   176,  1070,    49,  1070,   415,  1035,    -1,
      -1,   311,   895,  1055,  1099,  1136,   896,   897,   898,   899,
     900,    -1,    -1,   206,  1079,    -1,    -1,   195,   234,    -1,
    1149,   234,    -1,  1149,   254,   234,    -1,  1149,   194,   234,
      -1,  1149,   429,    -1,    -1,   214,  1124,   671,    -1,    -1,
    1018,    -1,  1029,    -1,    -1,   137,    -1,    -1,   320,   902,
    1052,   997,    -1,    -1,   333,   904,  1055,  1136,   896,  1018,
     905,    -1,    -1,   138,    -1,    -1,   338,   907,  1052,   997,
     908,  1028,   909,    -1,    -1,  1149,   234,    -1,  1149,   254,
     234,    -1,    -1,   139,    -1,   340,    -1,    -1,   348,   912,
     913,   921,    -1,  1053,   915,   916,   918,    -1,    -1,     9,
    1053,   916,   430,  1036,   914,   735,    -1,    -1,   428,  1079,
      -1,    -1,    -1,  1113,   123,   917,   735,    -1,   919,    -1,
     919,   918,    -1,    -1,   430,  1035,   920,   735,    -1,    -1,
     140,    -1,    -1,   358,   923,   924,    -1,   925,    -1,   926,
      -1,   927,    -1,   929,    -1,   931,    -1,   147,  1074,   396,
    1074,    -1,  1067,   396,   146,  1073,    -1,  1067,   396,  1070,
      -1,  1067,   928,    49,  1070,    -1,   416,    -1,   118,    -1,
     930,    -1,   929,   930,    -1,  1056,   396,   509,    -1,   932,
      -1,   931,   932,    -1,  1067,   396,   401,    -1,  1067,   396,
     397,    -1,    -1,   367,   934,   935,    -1,    -1,  1081,   937,
     939,   940,   936,   941,   942,    -1,    -1,   937,  1132,   641,
    1126,   938,    -1,    -1,   938,  1081,    -1,    -1,  1106,  1133,
      -1,    -1,  1107,  1124,  1063,    -1,    -1,   426,  1054,    -1,
     203,   300,  1124,   889,    -1,    -1,   183,  1054,    -1,   281,
     300,  1124,   889,    -1,    -1,    -1,   376,   944,  1055,   945,
     946,  1028,   948,    -1,    -1,   214,  1124,   947,   671,    -1,
    1100,  1041,    -1,  1100,  1042,    -1,  1100,  1043,    -1,  1100,
    1044,    -1,  1100,  1045,    -1,    -1,   141,    -1,    -1,   378,
     342,   950,   951,    -1,   378,   230,    -1,    -1,   334,  1070,
      -1,   183,  1070,    -1,    -1,   379,   953,   954,   206,  1079,
     956,  1013,   957,    -1,   955,    -1,   954,   955,    -1,  1070,
      -1,   109,  1115,   365,    -1,   109,  1115,  1070,    -1,    -1,
    1149,   293,  1079,    -1,    -1,   142,    -1,    -1,   382,   959,
     960,   961,    -1,  1069,   176,  1050,  1008,    -1,  1069,   176,
    1070,   183,  1050,  1008,    -1,    92,  1079,   176,  1079,  1102,
    1008,    -1,    -1,   143,    -1,   384,   963,    -1,    -1,   299,
      -1,    -1,   389,   965,   671,    -1,    -1,   404,   967,  1079,
     176,  1074,   396,  1075,    -1,    -1,   409,   969,  1055,   970,
      -1,    -1,   312,    -1,   314,    -1,    -1,   414,   972,  1079,
     973,   976,   956,   980,  1013,   981,    -1,    -1,   109,  1115,
     974,    -1,   975,    -1,   974,   277,   975,    -1,  1096,  1074,
      -1,   206,   977,    -1,   976,   977,    -1,  1079,   978,   979,
      -1,    -1,   110,  1123,  1079,    -1,    -1,    93,  1123,  1079,
      -1,    -1,   387,  1123,  1079,    -1,    -1,   144,    -1,   983,
      -1,   992,    -1,   994,    -1,   425,   984,   986,   987,   988,
     991,  1132,   985,    -1,    -1,   184,    -1,  1054,    -1,   203,
      -1,   281,    -1,   211,    -1,   163,    -1,    -1,     8,    -1,
      -1,   373,    -1,   160,    -1,   156,    -1,   160,    -1,   282,
      -1,   258,    -1,   260,    -1,    -1,   300,    -1,   425,  1121,
     104,  1132,   993,    -1,  1059,    -1,     9,   301,    -1,   425,
     984,    35,   326,  1079,    -1,    -1,   437,   996,  1052,   997,
     908,   998,  1000,  1001,    -1,    -1,   176,  1076,    -1,    -1,
     999,  1108,  1078,  1127,    -1,   999,  1108,  1057,    -1,   999,
    1108,   286,    -1,    35,    -1,     8,    -1,    -1,  1023,    -1,
    1029,    -1,    -1,   145,    -1,  1004,  1006,    -1,  1004,  1006,
      -1,    -1,    -1,   160,  1005,   735,    -1,    -1,    -1,   258,
    1007,   735,    -1,  1009,  1011,    -1,    -1,    -1,   366,  1010,
     735,    -1,    -1,    -1,   261,  1012,   735,    -1,  1014,  1016,
      -1,    -1,    -1,   282,  1015,   735,    -1,    -1,    -1,   260,
    1017,   735,    -1,  1019,    -1,  1021,    -1,  1019,  1021,    -1,
      -1,   123,  1020,   735,    -1,    -1,   256,  1022,   735,    -1,
    1024,    -1,  1026,    -1,  1024,  1026,    -1,    -1,   151,  1025,
     735,    -1,    -1,   257,  1027,   735,    -1,    -1,  1029,    -1,
    1030,    -1,  1032,    -1,  1030,  1032,    -1,    -1,   209,  1031,
     735,    -1,    -1,   259,  1033,   735,    -1,    -1,  1115,  1078,
    1127,    -1,  1036,    -1,  1037,    -1,    -1,  1038,  1039,    -1,
    1039,   210,    -1,  1040,  1070,    -1,  1039,   449,    -1,  1039,
     272,    -1,  1039,   265,    -1,  1039,    12,    -1,  1039,    13,
      -1,  1039,    14,    -1,  1039,    58,    -1,  1039,   295,    -1,
    1039,   251,    -1,  1039,   440,    -1,  1039,   255,    -1,    -1,
    1040,   210,    -1,  1040,   450,    -1,  1040,   441,    -1,  1040,
     442,    -1,  1040,   446,    -1,  1040,   255,    -1,  1039,   441,
      -1,  1039,   442,    -1,  1039,   443,    -1,  1039,   444,    -1,
    1039,   446,    -1,  1039,  1041,    -1,  1039,  1042,    -1,  1039,
    1043,    -1,  1039,  1044,    -1,  1039,  1045,    -1,  1039,   250,
      -1,  1040,  1041,    -1,  1040,  1042,    -1,  1040,  1043,    -1,
    1040,  1044,    -1,  1040,  1045,    -1,  1040,   250,    -1,  1039,
      20,    -1,  1039,   277,    -1,   448,    -1,   153,  1147,    -1,
     154,    -1,   451,    -1,   187,  1144,    -1,   452,    -1,   222,
    1144,    -1,   181,    -1,   187,  1144,   277,   153,  1147,    -1,
     187,  1144,   153,  1147,    -1,   218,    -1,   222,  1144,   277,
     153,  1147,    -1,   222,  1144,   153,  1147,    -1,  1048,    -1,
    1046,  1047,  1048,    -1,    -1,    69,    -1,   353,    -1,  1071,
      -1,  1048,   441,  1048,    -1,  1048,   442,  1048,    -1,  1048,
     443,  1048,    -1,  1048,   444,  1048,    -1,   441,  1048,    -1,
     442,  1048,    -1,  1048,   446,  1048,    -1,   450,  1048,   449,
      -1,   226,    -1,   226,  1104,   434,    -1,  1051,    -1,  1050,
    1051,    -1,  1070,  1102,    -1,  1081,    -1,  1081,    -1,  1055,
      -1,  1054,  1055,    -1,   434,    -1,  1057,    -1,  1056,  1057,
      -1,   242,    -1,    -1,  1058,  1059,    -1,  1060,    -1,  1081,
      -1,  1061,    -1,  1061,  1104,  1061,    -1,   230,    -1,  1063,
      -1,  1062,  1063,    -1,  1081,    -1,    -1,  1063,    -1,  1063,
      -1,   230,    -1,   434,    -1,  1068,    -1,  1067,  1068,    -1,
    1079,    -1,     6,  1131,  1080,    -1,  1070,    -1,  1069,  1070,
      -1,  1079,    -1,   221,  1131,  1080,    -1,   221,  1131,  1086,
      -1,   221,  1131,  1088,    -1,     6,  1131,  1072,  1073,    -1,
       6,  1131,  1080,    -1,  1085,    -1,  1088,    -1,  1049,    -1,
    1079,    -1,   221,  1131,  1080,    -1,   221,  1131,  1086,    -1,
     221,  1131,  1088,    -1,  1086,    -1,  1088,    -1,  1049,    -1,
     303,    -1,   146,    -1,  1080,    -1,   230,    -1,  1079,    -1,
    1086,    -1,  1079,    -1,  1085,    -1,  1079,    -1,   230,    -1,
    1079,    -1,   230,    -1,  1088,    -1,  1079,    -1,  1084,    -1,
     440,    -1,  1080,    -1,  1081,    -1,  1081,  1082,    -1,  1081,
    1083,    -1,  1081,  1082,  1083,    -1,   434,    -1,   434,  1104,
    1081,    -1,   450,  1046,   449,    -1,   450,  1048,   453,   449,
      -1,   450,  1048,   453,  1048,   449,    -1,   230,    -1,  1086,
      -1,     9,  1087,    -1,  1087,    -1,  1086,   454,  1087,    -1,
     230,    -1,   371,    -1,   440,    -1,   308,    -1,   191,    -1,
     237,    -1,   400,    -1,    96,  1089,    -1,   431,  1089,    -1,
     423,   450,  1048,   449,  1089,    -1,   235,   450,  1048,   449,
    1089,    -1,   335,   450,  1048,   449,  1089,    -1,    81,   450,
    1046,   449,  1089,    -1,   380,   450,  1046,   449,  1089,    -1,
     381,   450,  1046,   449,  1089,    -1,   405,   450,  1092,   449,
    1089,    -1,   267,   450,  1093,   449,    -1,   232,   450,  1094,
     449,  1089,    -1,   180,  1090,    -1,    -1,   450,  1048,   453,
     449,    -1,   450,  1048,   453,  1048,   449,    -1,    -1,   450,
    1091,   449,    -1,    -1,  1046,    -1,  1048,    -1,  1048,  1047,
     219,    -1,  1048,  1047,   403,    -1,  1048,    -1,  1048,  1047,
    1048,    -1,  1048,    -1,  1048,  1047,  1063,    -1,    -1,    -1,
       9,    -1,    -1,  1106,    -1,    -1,   201,    -1,    -1,   252,
      -1,   297,    -1,    -1,   255,    -1,    -1,   276,    -1,    -1,
     341,    -1,    -1,   355,  1116,    -1,   196,    -1,   270,    -1,
     312,  1124,    -1,   314,  1110,    -1,   433,   119,    -1,   119,
      -1,    62,   356,    -1,   356,    -1,    -1,     7,    -1,    -1,
      17,    -1,    -1,    23,    -1,    -1,    24,    -1,    -1,    27,
      -1,    -1,    30,    -1,    -1,    37,    -1,    -1,    49,    -1,
      -1,    55,    -1,    -1,    56,    -1,    -1,    84,    -1,    -1,
      99,    -1,    -1,   398,    -1,    -1,   172,    -1,    -1,   176,
      -1,    -1,   196,    -1,    -1,   210,    -1,    -1,   210,    -1,
      23,    -1,    -1,   214,    -1,    -1,   227,    -1,   228,    -1,
      -1,   228,    -1,    -1,   243,    -1,    -1,   263,    -1,    -1,
     270,    -1,    -1,   273,    -1,    -1,   278,    -1,   196,   278,
      -1,    -1,   280,    -1,    -1,   303,    -1,    -1,   312,    -1,
      -1,   339,    -1,    -1,   358,    -1,    -1,   360,    -1,    -1,
     360,    -1,   360,   210,    -1,    -1,   365,    -1,    -1,   377,
      -1,    -1,   388,    -1,    -1,   391,    -1,    -1,   392,    -1,
      -1,   395,    -1,    -1,   396,    -1,    -1,   430,    -1,    -1,
     433,    -1
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
    1228,  1229,  1230,  1231,  1232,  1239,  1250,  1249,  1260,  1274,
    1288,  1302,  1318,  1319,  1327,  1328,  1336,  1335,  1347,  1348,
    1349,  1350,  1351,  1359,  1360,  1365,  1366,  1368,  1367,  1379,
    1380,  1384,  1385,  1386,  1387,  1388,  1389,  1393,  1394,  1395,
    1396,  1397,  1398,  1405,  1416,  1428,  1429,  1433,  1434,  1441,
    1450,  1451,  1455,  1456,  1470,  1485,  1552,  1563,  1570,  1577,
    1583,  1590,  1591,  1595,  1594,  1604,  1603,  1619,  1620,  1623,
    1624,  1629,  1628,  1649,  1650,  1654,  1655,  1656,  1657,  1658,
    1659,  1660,  1661,  1662,  1663,  1664,  1665,  1666,  1667,  1674,
    1678,  1683,  1690,  1691,  1692,  1695,  1696,  1700,  1707,  1708,
    1715,  1722,  1726,  1727,  1728,  1735,  1755,  1802,  1802,  1806,
    1810,  1826,  1827,  1828,  1834,  1844,  1853,  1855,  1856,  1862,
    1866,  1867,  1868,  1871,  1872,  1873,  1877,  1881,  1882,  1888,
    1889,  1893,  1902,  1911,  1920,  1929,  1944,  1954,  1961,  1965,
    2003,  2010,  2017,  2021,  2022,  2023,  2031,  2032,  2035,  2036,
    2040,  2041,  2045,  2046,  2047,  2053,  2078,  2079,  2080,  2081,
    2087,  2094,  2095,  2099,  2102,  2103,  2109,  2119,  2120,  2134,
    2135,  2135,  2138,  2137,  2150,  2151,  2155,  2167,  2176,  2180,
    2181,  2191,  2190,  2208,  2209,  2213,  2220,  2227,  2228,  2229,
    2230,  2231,  2232,  2233,  2234,  2235,  2236,  2243,  2247,  2247,
    2247,  2253,  2265,  2290,  2314,  2315,  2322,  2323,  2327,  2328,
    2335,  2342,  2343,  2350,  2354,  2363,  2364,  2370,  2380,  2398,
    2399,  2403,  2404,  2405,  2409,  2416,  2423,  2433,  2440,  2458,
    2462,  2473,  2474,  2474,  2485,  2486,  2490,  2490,  2507,  2508,
    2510,  2514,  2516,  2515,  2546,  2551,  2556,  2562,  2571,  2579,
    2580,  2588,  2589,  2590,  2594,  2614,  2618,  2627,  2628,  2629,
    2630,  2631,  2632,  2633,  2634,  2635,  2636,  2637,  2638,  2639,
    2640,  2641,  2648,  2670,  2692,  2693,  2705,  2725,  2732,  2733,
    2737,  2738,  2739,  2740,  2741,  2742,  2743,  2744,  2745,  2746,
    2747,  2748,  2753,  2758,  2759,  2760,  2761,  2762,  2763,  2764,
    2765,  2766,  2767,  2768,  2769,  2770,  2771,  2772,  2773,  2774,
    2775,  2776,  2784,  2792,  2800,  2807,  2812,  2823,  2840,  2841,
    2844,  2845,  2852,  2876,  2877,  2894,  2895,  2898,  2899,  2906,
    2907,  2912,  2922,  2929,  2932,  2933,  2934,  2941,  2948,  2973,
    2973,  2978,  2979,  2983,  2984,  2987,  2988,  3001,  3013,  3033,
    3047,  3049,  3048,  3068,  3069,  3069,  3082,  3084,  3083,  3095,
    3096,  3100,  3101,  3110,  3117,  3120,  3124,  3128,  3129,  3130,
    3137,  3138,  3142,  3145,  3145,  3148,  3149,  3155,  3160,  3161,
    3164,  3165,  3168,  3169,  3172,  3173,  3176,  3177,  3181,  3182,
    3183,  3187,  3188,  3191,  3192,  3196,  3200,  3201,  3205,  3206,
    3207,  3208,  3209,  3210,  3211,  3212,  3213,  3214,  3215,  3216,
    3217,  3218,  3219,  3220,  3224,  3228,  3229,  3230,  3231,  3232,
    3233,  3234,  3238,  3242,  3243,  3244,  3248,  3249,  3253,  3257,
    3262,  3266,  3270,  3274,  3275,  3279,  3280,  3284,  3285,  3286,
    3289,  3289,  3289,  3292,  3296,  3299,  3299,  3302,  3309,  3310,
    3311,  3310,  3328,  3329,  3333,  3334,  3339,  3341,  3340,  3376,
    3377,  3381,  3382,  3383,  3384,  3385,  3386,  3387,  3388,  3389,
    3390,  3391,  3392,  3393,  3394,  3395,  3396,  3397,  3401,  3405,
    3409,  3413,  3414,  3415,  3416,  3417,  3418,  3419,  3420,  3427,
    3431,  3441,  3444,  3448,  3452,  3456,  3464,  3467,  3471,  3475,
    3479,  3487,  3500,  3502,  3512,  3501,  3539,  3541,  3540,  3547,
    3546,  3555,  3556,  3561,  3568,  3570,  3574,  3584,  3586,  3594,
    3602,  3631,  3662,  3664,  3674,  3679,  3690,  3691,  3691,  3718,
    3719,  3723,  3724,  3725,  3726,  3742,  3754,  3785,  3822,  3834,
    3837,  3838,  3847,  3851,  3847,  3864,  3882,  3886,  3887,  3888,
    3889,  3890,  3891,  3892,  3893,  3894,  3895,  3896,  3897,  3898,
    3899,  3900,  3901,  3902,  3903,  3904,  3905,  3906,  3907,  3908,
    3909,  3910,  3911,  3912,  3913,  3914,  3915,  3916,  3917,  3918,
    3919,  3920,  3921,  3922,  3923,  3924,  3925,  3926,  3927,  3928,
    3929,  3930,  3931,  3932,  3933,  3934,  3935,  3958,  3957,  3970,
    3974,  3978,  3982,  3986,  3990,  3994,  3998,  4002,  4006,  4010,
    4014,  4018,  4022,  4026,  4030,  4034,  4041,  4042,  4043,  4044,
    4045,  4046,  4050,  4054,  4055,  4058,  4059,  4063,  4064,  4068,
    4069,  4070,  4071,  4072,  4073,  4074,  4075,  4079,  4083,  4087,
    4092,  4093,  4094,  4095,  4096,  4097,  4101,  4102,  4111,  4111,
    4117,  4121,  4125,  4131,  4132,  4136,  4137,  4146,  4146,  4151,
    4155,  4162,  4163,  4172,  4178,  4179,  4183,  4183,  4191,  4191,
    4201,  4203,  4202,  4211,  4212,  4217,  4224,  4231,  4233,  4237,
    4245,  4256,  4257,  4258,  4263,  4267,  4266,  4278,  4282,  4281,
    4292,  4293,  4302,  4302,  4306,  4307,  4319,  4319,  4323,  4324,
    4335,  4336,  4337,  4338,  4339,  4342,  4342,  4350,  4350,  4356,
    4363,  4364,  4367,  4367,  4374,  4387,  4400,  4400,  4411,  4412,
    4421,  4421,  4441,  4440,  4453,  4457,  4461,  4465,  4469,  4473,
    4477,  4482,  4486,  4493,  4494,  4495,  4499,  4500,  4505,  4506,
    4507,  4508,  4509,  4510,  4511,  4512,  4513,  4514,  4518,  4522,
    4526,  4531,  4532,  4536,  4537,  4546,  4546,  4552,  4556,  4560,
    4564,  4568,  4575,  4576,  4585,  4585,  4607,  4606,  4625,  4626,
    4637,  4646,  4651,  4659,  4688,  4689,  4695,  4694,  4710,  4714,
    4713,  4728,  4729,  4734,  4735,  4746,  4775,  4776,  4777,  4780,
    4781,  4785,  4786,  4795,  4795,  4800,  4801,  4809,  4826,  4843,
    4861,  4886,  4886,  4899,  4899,  4912,  4912,  4921,  4925,  4938,
    4938,  4951,  4953,  4951,  4964,  4969,  4973,  4972,  4986,  4987,
    4996,  4996,  5004,  5005,  5009,  5010,  5011,  5015,  5016,  5021,
    5022,  5027,  5031,  5032,  5033,  5034,  5035,  5036,  5037,  5041,
    5042,  5051,  5051,  5064,  5063,  5073,  5074,  5075,  5079,  5080,
    5084,  5085,  5086,  5092,  5092,  5097,  5098,  5102,  5103,  5104,
    5105,  5106,  5107,  5113,  5117,  5118,  5122,  5127,  5131,  5132,
    5133,  5134,  5135,  5139,  5165,  5178,  5179,  5183,  5183,  5191,
    5191,  5201,  5201,  5206,  5210,  5222,  5222,  5228,  5232,  5239,
    5240,  5249,  5249,  5253,  5254,  5268,  5269,  5270,  5271,  5275,
    5276,  5280,  5281,  5282,  5294,  5294,  5299,  5304,  5303,  5313,
    5320,  5321,  5325,  5330,  5339,  5342,  5346,  5351,  5358,  5365,
    5366,  5370,  5371,  5376,  5388,  5388,  5411,  5412,  5416,  5417,
    5421,  5425,  5429,  5433,  5440,  5441,  5455,  5456,  5457,  5461,
    5462,  5471,  5471,  5486,  5486,  5497,  5498,  5507,  5507,  5518,
    5519,  5523,  5530,  5531,  5540,  5553,  5553,  5559,  5564,  5563,
    5574,  5575,  5579,  5581,  5580,  5591,  5592,  5597,  5596,  5607,
    5608,  5617,  5617,  5622,  5623,  5624,  5625,  5626,  5632,  5641,
    5645,  5654,  5661,  5662,  5668,  5669,  5673,  5682,  5683,  5687,
    5691,  5703,  5703,  5709,  5708,  5725,  5728,  5744,  5745,  5748,
    5749,  5753,  5754,  5759,  5764,  5772,  5784,  5789,  5797,  5813,
    5814,  5813,  5834,  5835,  5851,  5852,  5853,  5854,  5855,  5859,
    5860,  5869,  5869,  5874,  5881,  5882,  5883,  5892,  5892,  5901,
    5902,  5906,  5907,  5908,  5912,  5913,  5917,  5918,  5927,  5927,
    5933,  5937,  5941,  5948,  5949,  5958,  5965,  5966,  5974,  5974,
    5987,  5987,  6003,  6003,  6012,  6014,  6015,  6024,  6024,  6034,
    6035,  6040,  6041,  6046,  6053,  6054,  6059,  6066,  6067,  6071,
    6072,  6076,  6077,  6081,  6082,  6091,  6092,  6093,  6097,  6121,
    6124,  6132,  6142,  6147,  6152,  6157,  6164,  6165,  6168,  6169,
    6173,  6173,  6177,  6177,  6181,  6181,  6184,  6185,  6189,  6196,
    6197,  6201,  6213,  6213,  6224,  6225,  6230,  6233,  6237,  6241,
    6248,  6249,  6252,  6253,  6254,  6258,  6259,  6272,  6280,  6287,
    6289,  6288,  6298,  6300,  6299,  6314,  6318,  6320,  6319,  6330,
    6332,  6331,  6348,  6354,  6356,  6355,  6365,  6367,  6366,  6382,
    6387,  6392,  6402,  6401,  6413,  6412,  6428,  6433,  6438,  6448,
    6447,  6459,  6458,  6473,  6474,  6478,  6483,  6488,  6498,  6497,
    6509,  6508,  6525,  6528,  6540,  6547,  6554,  6554,  6564,  6565,
    6566,  6568,  6569,  6570,  6571,  6572,  6573,  6575,  6576,  6577,
    6579,  6582,  6584,  6585,  6587,  6588,  6589,  6591,  6593,  6594,
    6595,  6596,  6597,  6599,  6600,  6601,  6602,  6603,  6604,  6606,
    6607,  6608,  6609,  6610,  6611,  6613,  6614,  6617,  6617,  6617,
    6618,  6618,  6619,  6619,  6620,  6620,  6620,  6621,  6621,  6621,
    6626,  6627,  6630,  6631,  6632,  6636,  6637,  6638,  6639,  6640,
    6641,  6642,  6643,  6644,  6655,  6667,  6682,  6683,  6688,  6694,
    6700,  6720,  6724,  6740,  6754,  6755,  6760,  6766,  6767,  6772,
    6781,  6782,  6783,  6787,  6798,  6799,  6803,  6811,  6812,  6816,
    6817,  6823,  6843,  6844,  6848,  6849,  6853,  6854,  6858,  6859,
    6860,  6861,  6862,  6863,  6864,  6865,  6866,  6870,  6871,  6872,
    6873,  6874,  6875,  6876,  6880,  6881,  6885,  6886,  6890,  6891,
    6895,  6896,  6907,  6908,  6912,  6913,  6914,  6918,  6919,  6920,
    6928,  6932,  6933,  6934,  6935,  6939,  6940,  6944,  6954,  6972,
    6999,  7011,  7012,  7022,  7023,  7027,  7028,  7029,  7030,  7031,
    7032,  7033,  7041,  7045,  7049,  7053,  7057,  7061,  7065,  7069,
    7073,  7077,  7081,  7085,  7092,  7093,  7094,  7098,  7099,  7103,
    7104,  7109,  7116,  7123,  7133,  7140,  7150,  7157,  7171,  7181,
    7182,  7186,  7187,  7191,  7192,  7196,  7197,  7198,  7202,  7203,
    7207,  7208,  7212,  7213,  7217,  7218,  7225,  7225,  7226,  7226,
    7227,  7227,  7228,  7228,  7230,  7230,  7231,  7231,  7232,  7232,
    7233,  7233,  7234,  7234,  7235,  7235,  7236,  7236,  7237,  7237,
    7238,  7238,  7239,  7239,  7240,  7240,  7241,  7241,  7242,  7242,
    7243,  7243,  7244,  7244,  7245,  7245,  7246,  7246,  7247,  7247,
    7247,  7248,  7248,  7249,  7249,  7249,  7250,  7250,  7251,  7251,
    7252,  7252,  7253,  7253,  7254,  7254,  7255,  7255,  7255,  7256,
    7256,  7257,  7257,  7258,  7258,  7259,  7259,  7260,  7260,  7261,
    7261,  7262,  7262,  7262,  7263,  7263,  7264,  7264,  7265,  7265,
    7266,  7266,  7267,  7267,  7268,  7268,  7269,  7269,  7271,  7271,
    7272,  7272
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
  "commitment_control_clause", "data_division", "file_section", "$@16",
  "$@17", "file_description_sequence", "file_description",
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
     505,   505,   505,   505,   505,   506,   507,   506,   506,   506,
     506,   506,   508,   508,   509,   509,   511,   510,   512,   512,
     512,   512,   512,   513,   513,   514,   514,   515,   514,   516,
     516,   517,   517,   517,   517,   517,   517,   518,   518,   518,
     518,   518,   518,   519,   520,   521,   521,   522,   522,   523,
     524,   524,   525,   525,   526,   527,   528,   529,   530,   531,
     532,   533,   533,   534,   533,   535,   533,   536,   536,   537,
     537,   539,   538,   540,   540,   541,   541,   541,   541,   541,
     541,   541,   541,   541,   541,   541,   541,   541,   541,   542,
     542,   542,   543,   543,   543,   544,   544,   544,   545,   545,
     545,   546,   547,   547,   547,   548,   548,   550,   549,   549,
     551,   552,   552,   552,   553,   554,   555,   555,   555,   556,
     557,   557,   557,   558,   558,   558,   558,   559,   559,   560,
     560,   561,   561,   561,   561,   561,   562,   563,   564,   564,
     565,   566,   567,   568,   568,   568,   569,   569,   570,   570,
     571,   571,   572,   572,   572,   573,   574,   574,   574,   574,
     575,   576,   576,   577,   578,   578,   579,   580,   580,   581,
     582,   581,   583,   581,   584,   584,   585,   586,   586,   587,
     587,   589,   588,   590,   590,   591,   591,   591,   591,   591,
     591,   591,   591,   591,   591,   591,   591,   592,   593,   593,
     593,   594,   594,   594,   595,   595,   596,   596,   597,   597,
     598,   599,   599,   600,   600,   601,   601,   602,   603,   604,
     604,   605,   605,   605,   606,   607,   608,   609,   610,   611,
     611,   612,   613,   612,   614,   614,   616,   615,   617,   617,
     617,   618,   619,   618,   620,   621,   621,   621,   622,   623,
     623,   624,   624,   624,   625,   626,   626,   627,   627,   627,
     627,   627,   627,   627,   627,   627,   627,   627,   627,   627,
     627,   627,   628,   629,   630,   630,   631,   632,   633,   633,
     634,   634,   634,   634,   634,   634,   634,   634,   634,   634,
     634,   634,   634,   634,   634,   634,   634,   634,   634,   634,
     634,   634,   634,   634,   634,   634,   634,   634,   634,   634,
     634,   634,   634,   634,   634,   635,   635,   636,   637,   637,
     638,   638,   639,   640,   640,   641,   641,   642,   642,   643,
     643,   644,   645,   646,   647,   647,   647,   648,   649,   651,
     650,   652,   652,   653,   653,   654,   654,   655,   655,   656,
     657,   658,   657,   659,   660,   659,   661,   662,   661,   663,
     663,   664,   664,   665,   666,   666,   667,   667,   667,   667,
     668,   668,   669,   670,   670,   671,   671,   672,   673,   673,
     674,   674,   675,   675,   676,   676,   677,   677,   678,   678,
     678,   679,   679,   680,   680,   681,   682,   682,   683,   683,
     683,   683,   683,   683,   683,   683,   683,   683,   683,   683,
     683,   683,   683,   683,   684,   685,   685,   685,   685,   685,
     685,   685,   686,   687,   687,   687,   688,   688,   689,   690,
     691,   692,   693,   694,   694,   695,   695,   696,   696,   696,
     697,   697,   697,   698,   699,   700,   700,   701,   702,   703,
     704,   702,   705,   705,   706,   706,   707,   708,   707,   709,
     709,   710,   710,   710,   710,   710,   710,   710,   710,   710,
     710,   710,   710,   710,   710,   710,   710,   710,   710,   710,
     710,   710,   710,   710,   710,   710,   710,   710,   710,   710,
     710,   711,   711,   711,   711,   711,   712,   712,   712,   712,
     712,   713,   714,   715,   716,   714,   717,   718,   717,   719,
     717,   720,   720,   721,   722,   722,   722,   723,   723,   723,
     723,   723,   724,   724,   725,   725,   726,   727,   726,   728,
     728,   729,   729,   729,   729,   729,   730,   731,   732,   733,
     734,   734,   736,   737,   735,   738,   738,   739,   739,   739,
     739,   739,   739,   739,   739,   739,   739,   739,   739,   739,
     739,   739,   739,   739,   739,   739,   739,   739,   739,   739,
     739,   739,   739,   739,   739,   739,   739,   739,   739,   739,
     739,   739,   739,   739,   739,   739,   739,   739,   739,   739,
     739,   739,   739,   739,   739,   739,   739,   741,   740,   742,
     742,   742,   742,   742,   742,   742,   742,   742,   742,   742,
     742,   742,   742,   742,   742,   742,   743,   743,   743,   743,
     743,   743,   744,   745,   745,   746,   746,   747,   747,   748,
     748,   748,   748,   748,   748,   748,   748,   748,   748,   748,
     748,   748,   748,   748,   748,   748,   749,   749,   751,   750,
     752,   752,   752,   753,   753,   754,   754,   756,   755,   757,
     757,   758,   758,   759,   760,   760,   761,   761,   763,   762,
     764,   765,   764,   766,   766,   767,   767,   768,   768,   768,
     768,   769,   769,   769,   770,   771,   770,   772,   773,   772,
     774,   774,   776,   775,   777,   777,   779,   778,   780,   780,
     781,   781,   781,   781,   781,   782,   782,   784,   783,   785,
     786,   786,   787,   787,   788,   789,   791,   790,   792,   792,
     794,   793,   796,   795,   797,   797,   797,   797,   797,   797,
     797,   797,   797,   798,   798,   798,   799,   799,   800,   800,
     800,   800,   800,   800,   800,   800,   800,   800,   800,   800,
     800,   800,   800,   801,   801,   803,   802,   804,   804,   804,
     804,   804,   805,   805,   807,   806,   809,   808,   810,   810,
     811,   811,   811,   812,   813,   813,   815,   814,   816,   817,
     816,   818,   818,   819,   819,   820,   820,   820,   820,   821,
     821,   822,   822,   824,   823,   825,   825,   825,   825,   825,
     825,   827,   826,   829,   828,   831,   830,   832,   832,   834,
     833,   836,   837,   835,   835,   838,   839,   838,   840,   840,
     842,   841,   843,   843,   844,   844,   844,   845,   845,   846,
     846,   847,   848,   848,   848,   848,   848,   848,   848,   849,
     849,   851,   850,   853,   852,   854,   854,   854,   855,   855,
     856,   856,   856,   858,   857,   859,   859,   860,   860,   860,
     860,   860,   860,   861,   862,   862,   863,   863,   864,   864,
     864,   864,   864,   865,   866,   867,   867,   868,   868,   870,
     869,   872,   871,   873,   873,   875,   874,   876,   876,   877,
     877,   879,   878,   880,   880,   881,   881,   881,   881,   882,
     882,   883,   883,   883,   885,   884,   886,   887,   886,   886,
     888,   888,   889,   889,   890,   890,   890,   890,   890,   891,
     891,   892,   892,   893,   895,   894,   896,   896,   897,   897,
     897,   897,   897,   897,   898,   898,   899,   899,   899,   900,
     900,   902,   901,   904,   903,   905,   905,   907,   906,   908,
     908,   908,   909,   909,   910,   912,   911,   913,   914,   913,
     915,   915,   916,   917,   916,   918,   918,   920,   919,   921,
     921,   923,   922,   924,   924,   924,   924,   924,   925,   926,
     926,   927,   928,   928,   929,   929,   930,   931,   931,   932,
     932,   934,   933,   936,   935,   937,   937,   938,   938,   939,
     939,   940,   940,   941,   941,   941,   942,   942,   942,   944,
     945,   943,   946,   946,   947,   947,   947,   947,   947,   948,
     948,   950,   949,   949,   951,   951,   951,   953,   952,   954,
     954,   955,   955,   955,   956,   956,   957,   957,   959,   958,
     960,   960,   960,   961,   961,   962,   963,   963,   965,   964,
     967,   966,   969,   968,   970,   970,   970,   972,   971,   973,
     973,   974,   974,   975,   976,   976,   977,   978,   978,   979,
     979,   980,   980,   981,   981,   982,   982,   982,   983,   984,
     984,   985,   985,   985,   985,   985,   986,   986,   987,   987,
     988,   988,   989,   989,   990,   990,   991,   991,   992,   993,
     993,   994,   996,   995,   997,   997,   998,   998,   998,   998,
     999,   999,  1000,  1000,  1000,  1001,  1001,  1002,  1003,  1004,
    1005,  1004,  1006,  1007,  1006,  1008,  1009,  1010,  1009,  1011,
    1012,  1011,  1013,  1014,  1015,  1014,  1016,  1017,  1016,  1018,
    1018,  1018,  1020,  1019,  1022,  1021,  1023,  1023,  1023,  1025,
    1024,  1027,  1026,  1028,  1028,  1029,  1029,  1029,  1031,  1030,
    1033,  1032,  1034,  1034,  1035,  1036,  1038,  1037,  1039,  1039,
    1039,  1039,  1039,  1039,  1039,  1039,  1039,  1039,  1039,  1039,
    1039,  1040,  1040,  1040,  1040,  1040,  1040,  1040,  1040,  1040,
    1040,  1040,  1040,  1040,  1040,  1040,  1040,  1040,  1040,  1040,
    1040,  1040,  1040,  1040,  1040,  1040,  1040,  1041,  1041,  1041,
    1042,  1042,  1043,  1043,  1044,  1044,  1044,  1045,  1045,  1045,
    1046,  1046,  1047,  1047,  1047,  1048,  1048,  1048,  1048,  1048,
    1048,  1048,  1048,  1048,  1049,  1049,  1050,  1050,  1051,  1052,
    1053,  1054,  1054,  1055,  1056,  1056,  1057,  1058,  1058,  1059,
    1060,  1060,  1060,  1061,  1062,  1062,  1063,  1064,  1064,  1065,
    1065,  1066,  1067,  1067,  1068,  1068,  1069,  1069,  1070,  1070,
    1070,  1070,  1070,  1070,  1070,  1070,  1070,  1071,  1071,  1071,
    1071,  1071,  1071,  1071,  1072,  1072,  1073,  1073,  1074,  1074,
    1075,  1075,  1076,  1076,  1077,  1077,  1077,  1078,  1078,  1078,
    1079,  1080,  1080,  1080,  1080,  1081,  1081,  1082,  1083,  1083,
    1084,  1085,  1085,  1086,  1086,  1087,  1087,  1087,  1087,  1087,
    1087,  1087,  1088,  1088,  1088,  1088,  1088,  1088,  1088,  1088,
    1088,  1088,  1088,  1088,  1089,  1089,  1089,  1090,  1090,  1091,
    1091,  1092,  1092,  1092,  1093,  1093,  1094,  1094,  1095,  1096,
    1096,  1097,  1097,  1098,  1098,  1099,  1099,  1099,  1100,  1100,
    1101,  1101,  1102,  1102,  1103,  1103,  1104,  1104,  1105,  1105,
    1106,  1106,  1107,  1107,  1108,  1108,  1109,  1109,  1110,  1110,
    1111,  1111,  1112,  1112,  1113,  1113,  1114,  1114,  1115,  1115,
    1116,  1116,  1117,  1117,  1118,  1118,  1119,  1119,  1120,  1120,
    1121,  1121,  1122,  1122,  1123,  1123,  1124,  1124,  1125,  1125,
    1125,  1126,  1126,  1127,  1127,  1127,  1128,  1128,  1129,  1129,
    1130,  1130,  1131,  1131,  1132,  1132,  1133,  1133,  1133,  1134,
    1134,  1135,  1135,  1136,  1136,  1137,  1137,  1138,  1138,  1139,
    1139,  1140,  1140,  1140,  1141,  1141,  1142,  1142,  1143,  1143,
    1144,  1144,  1145,  1145,  1146,  1146,  1147,  1147,  1148,  1148,
    1149,  1149
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       4,     4,     0,     1,     1,     0,     1,     1,     1,     1,
       1,     4,     1,     1,     1,     6,     8,     0,     2,     2,
       1,     0,     2,     1,     3,     5,     0,     1,     1,     4,
       2,     2,     1,     0,     4,     5,     2,     1,     1,     3,
       1,     1,     3,     1,     1,     2,     4,     4,     4,     6,
       4,     3,     3,     2,     2,     2,     0,     3,     0,     2,
       1,     2,     1,     1,     1,     5,     0,     1,     1,     1,
       5,     1,     2,     2,     0,     2,     4,     0,     9,     0,
       0,     5,     0,     3,     0,     2,     3,     2,     2,     1,
       1,     0,     4,     0,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     0,     1,
       1,     4,     6,     9,     0,     3,     0,     2,     0,     2,
       3,     1,     1,     5,     5,     1,     1,     3,     5,     0,
       2,     1,     1,     1,     5,     4,     3,     4,     3,     3,
       3,     0,     0,     5,     0,     1,     0,     2,     3,     4,
       2,     1,     0,     4,     1,     0,     1,     1,     1,     0,
       2,     1,     3,     3,     6,     0,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     0,     2,     2,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     1,     2,     2,     1,     2,     2,     1,     2,     2,
       1,     2,     2,     1,     1,     3,     3,     7,     0,     2,
       0,     3,     1,     0,     5,     1,     1,     0,     3,     1,
       2,     1,     2,     2,     0,     1,     1,     3,     1,     0,
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
       2,     0,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     0,     0,     1,     0,     0,     3,     4,     6,     7,
      38,    38,     0,     0,     5,     0,     8,    14,    28,    27,
      29,    29,     0,   257,   257,     0,     0,    24,    40,     0,
       9,    15,    30,    26,  1496,     0,   151,     0,   592,   592,
    1497,     0,     0,     0,     0,     0,     0,    39,   259,     0,
      17,     0,    25,    33,    37,    36,  1521,    35,    42,   153,
       0,   155,   269,   270,     0,   321,   262,   596,    18,    20,
      38,     0,    16,    34,  1522,    32,    41,   159,   157,   238,
       0,     0,   440,     0,   599,   597,   614,     0,    19,    10,
      11,     0,     0,     0,     0,     0,    43,    44,    45,    47,
      46,   154,     0,   236,     0,  1488,   246,   156,     0,   240,
     242,   243,   244,   260,     0,     0,   443,  1333,   263,   324,
     271,   604,   604,     0,     0,     0,   257,    23,    56,    71,
      49,    80,  1450,   160,   159,     0,   152,  1514,  1489,  1538,
     247,   248,   249,  1470,   239,   241,   264,   322,     0,     0,
     446,   268,     0,   267,   325,  1438,   273,  1479,   604,   601,
     607,     0,   604,   615,   593,    21,    12,     0,  1496,    54,
    1521,    55,  1521,    60,    62,    63,    64,     0,     0,    70,
       0,    73,  1551,    48,     0,  1550,     0,     0,  1496,  1496,
       0,     0,  1529,  1496,  1496,  1496,  1496,  1496,     0,  1496,
    1482,  1496,    79,     0,    82,    84,    85,    86,    88,    87,
      89,    90,    91,    92,    93,    94,  1451,     0,   158,   238,
    1515,     0,  1539,  1484,  1471,  1490,   261,   324,   441,     0,
       0,   538,   324,   327,     0,     0,   602,  1496,     0,   612,
     605,   606,   616,   592,  1496,     0,    57,  1521,    59,    61,
       0,  1463,  1496,     0,    77,     0,    72,    74,    52,    50,
       0,     0,  1351,   106,     0,     0,  1496,  1496,  1530,  1496,
       0,     0,     0,     0,     0,  1496,     0,  1483,     0,     0,
      81,    83,   161,   237,  1395,   256,  1344,  1346,  1485,     0,
    1491,     0,   265,   323,   324,   444,     0,     0,   258,   266,
     330,     0,   334,     0,   335,   331,   286,  1484,  1496,     0,
       0,  1496,  1484,  1508,  1496,  1468,     0,   272,   274,   277,
     278,   279,   280,   281,   282,   283,   284,   285,     0,     0,
    1496,   613,     0,     0,   594,    17,     0,  1400,    69,    58,
    1462,     0,    76,    75,    78,    51,    53,  1496,    98,    99,
       0,     0,     0,   147,   146,   100,   101,   150,     0,   149,
     133,  1498,   135,    95,    96,   163,  1456,  1457,     0,  1345,
     250,   251,   254,   245,  1331,   442,   324,   447,     0,     0,
     328,   336,   337,   332,     0,     0,     0,  1496,  1468,     0,
       0,     0,     0,     0,  1509,  1496,     0,  1469,     0,     0,
     275,   276,   608,   609,   611,     0,   603,   617,   619,     0,
       0,    68,     0,  1409,  1405,  1410,  1408,  1406,  1411,  1407,
     139,   140,   142,   148,   145,   144,  1500,  1499,   136,     0,
     102,     0,  1396,   252,     0,   253,  1332,   445,   449,   539,
     329,   345,   339,   298,   318,  1458,  1459,   307,   302,   301,
     300,  1350,  1349,  1506,  1482,  1494,     0,   537,   319,   320,
    1496,  1496,   610,   619,     0,     0,    13,    66,    67,    65,
     111,   125,   121,   126,   108,   124,   122,   109,   110,   123,
     107,   112,   113,   115,   141,     0,   134,   137,    97,   178,
    1508,     0,  1546,   221,     0,  1508,  1496,  1480,  1501,   224,
       0,   223,  1550,   208,   207,   162,   164,   165,   166,   167,
     168,   169,     0,   170,   171,   220,   172,   173,   174,   175,
     176,   177,  1496,   255,     0,   448,   450,   451,   540,     0,
    1472,     0,     0,   288,  1507,   309,     0,   291,  1495,  1534,
     317,     0,     0,     0,   625,   629,   620,   621,   622,   623,
     628,     0,     0,   114,   117,     0,   143,   138,   105,   104,
    1536,  1496,  1501,  1547,   185,   225,  1496,     0,  1481,  1496,
    1477,  1496,  1502,     0,  1496,  1496,  1470,     0,  1496,     0,
     454,   452,   542,   361,     0,   428,   370,   403,   391,   400,
     397,   394,  1548,   371,   372,   373,   374,   375,   376,   377,
     378,   379,  1525,   404,     0,   380,   367,   381,   382,     0,
       0,  1532,   384,   385,   383,   424,   387,   388,   386,  1496,
    1498,   346,   347,   348,   349,   350,   351,   368,   352,   353,
     354,   355,   356,   357,   358,   359,   360,     0,     0,  1473,
       0,   340,   299,   290,   289,   287,   308,  1482,  1535,   296,
     305,   304,   306,   303,     0,   627,   630,   687,   738,   747,
     754,   758,   782,   786,   804,   797,   805,   806,   812,   845,
     854,   856,   883,   891,   893,  1546,   899,     0,   910,   931,
     933,   969,   971,   975,   686,   981,   994,  1014,  1031,  1033,
    1037,  1044,  1045,  1061,  1081,  1099,     0,  1117,  1128,  1136,
    1138,  1140,  1142,  1147,  1169,  1192,   624,   636,   637,   638,
     639,   640,   641,   642,   643,   645,   644,   646,   647,   648,
     649,   650,   651,   652,   653,   654,   655,   656,   657,   658,
     659,   660,   661,   662,   663,   664,   665,   666,   667,   668,
     669,   670,   671,   672,   673,   674,   675,   676,   677,   678,
     679,   680,   681,   682,   683,   684,  1165,  1166,  1167,   685,
      22,     0,   116,  1537,  1496,     0,  1496,   187,   186,   182,
       0,  1476,   224,   219,     0,     0,   222,     0,     0,   231,
    1519,  1519,     0,   232,     0,   204,  1496,   335,   546,   541,
     543,   544,   439,   401,   402,   389,   390,   398,   399,   395,
     396,   392,   393,  1549,     0,  1526,   422,   408,   362,  1391,
     437,  1533,   425,   426,   423,     0,     0,   364,   366,  1454,
    1454,     0,  1512,  1512,   344,   341,  1401,  1403,  1475,   310,
     311,   312,   313,     0,     0,   292,  1493,   298,     0,     0,
     631,     0,     0,     0,  1256,   753,     0,   784,   788,     0,
       0,     0,     0,     0,     0,  1256,   885,     0,     0,   895,
     900,     0,  1256,     0,     0,     0,     0,     0,     0,   983,
    1004,     0,     0,     0,     0,     0,     0,     0,     0,  1113,
    1111,     0,     0,  1137,  1135,     0,     0,     0,     0,  1170,
    1176,     0,     0,   131,   127,   132,   130,   128,   129,   118,
     119,     0,   193,   194,   192,   191,     0,   180,   181,     0,
     213,   212,   213,   209,   226,   227,   228,   230,  1520,   233,
     234,   235,  1347,  1496,   463,   463,  1498,   483,   455,   458,
     459,     0,   547,   545,   427,     0,  1544,     0,  1392,  1393,
       0,   369,   429,   431,   433,     0,   363,  1480,   405,   406,
    1402,  1513,     0,     0,     0,     0,     0,  1474,  1482,   297,
     618,   626,   736,   706,  1390,  1512,     0,     0,  1424,  1427,
    1512,  1324,     0,     0,     0,     0,     0,     0,     0,     0,
    1424,   745,  1366,   743,  1356,  1358,  1364,  1365,  1443,   748,
       0,  1255,  1271,  1343,     0,  1339,  1341,  1340,  1385,   760,
    1384,  1386,   783,   787,   800,     0,  1326,  1452,  1523,     0,
    1405,   843,   706,     0,  1358,   852,     0,   760,   862,   861,
    1466,   858,   860,   890,   887,   886,   889,   884,  1512,   892,
    1352,  1354,   894,  1337,   904,  1542,  1254,   912,   932,   465,
       0,   935,   936,   937,   970,  1085,     0,   972,     0,   979,
       0,   982,  1005,  1343,   995,  1004,   997,     0,  1002,     0,
    1340,     0,  1445,  1194,  1329,  1523,  1194,     0,  1059,  1050,
    1330,     0,  1336,  1062,  1063,  1064,  1065,  1066,  1074,  1067,
    1077,     0,  1334,     0,  1082,  1100,  1114,  1478,     0,  1119,
    1121,     0,  1133,     0,  1139,     0,  1144,  1149,  1177,     0,
    1178,  1514,  1194,     0,   103,  1441,   189,   188,   179,   190,
       0,   211,   210,  1496,   203,   197,  1348,   205,     0,   464,
     460,     0,   461,     0,   453,   456,   549,   409,  1545,   410,
    1512,     0,     0,     0,  1312,  1310,  1373,  1315,  1367,  1371,
    1372,     0,  1394,   438,  1548,   432,     0,   365,  1455,   343,
     342,  1404,   316,  1506,     0,   294,   737,   688,  1475,     0,
     715,     0,     0,     0,     0,     0,  1412,  1429,  1423,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1413,
     746,   739,     0,     0,  1357,  1444,   751,  1443,  1257,     0,
     756,     0,   761,   771,  1383,   785,  1382,   790,   801,   798,
     803,   802,  1256,  1327,  1453,  1328,  1524,  1243,   811,   844,
     813,   823,  1209,  1209,  1209,  1209,   853,   846,     0,     0,
     855,  1467,  1256,   881,   868,   864,   866,  1256,   888,     0,
    1353,   897,  1543,   902,   914,     0,   466,     0,   958,   943,
     934,   938,   940,   941,   942,  1089,     0,     0,   980,   976,
       0,   988,   985,   987,   986,   989,   996,   999,   632,  1256,
       0,     0,  1006,     0,  1446,  1447,  1523,     0,  1032,  1016,
    1039,  1052,  1060,  1046,     0,  1052,     0,  1378,  1379,  1075,
    1078,     0,     0,  1335,  1073,     0,  1072,     0,  1102,     0,
       0,  1112,     0,     0,  1120,     0,  1134,  1129,     0,     0,
    1145,  1146,  1143,  1478,     0,     0,  1179,     0,     0,  1039,
     120,  1461,     0,   197,   195,  1442,     0,   216,   202,   229,
       0,   457,   462,   468,   478,   335,   484,  1531,  1514,   413,
       0,  1320,  1321,     0,  1313,  1314,  1397,     0,     0,     0,
       0,     0,     0,     0,     0,  1527,   434,   315,  1506,  1514,
     293,   711,   702,  1209,   692,   699,   693,   695,   697,     0,
    1209,     0,   691,   698,   705,   704,     0,  1209,  1510,  1510,
    1510,   709,   710,  1375,  1374,     0,  1363,  1312,  1310,     0,
       0,  1312,     0,  1359,  1360,  1361,  1325,  1312,     0,     0,
    1312,     0,     0,  1312,  1312,  1312,     0,     0,  1216,  1452,
       0,     0,   749,     0,  1263,  1264,  1265,  1295,  1266,  1546,
    1299,  1304,  1540,  1258,  1307,  1540,  1288,  1268,  1270,  1262,
    1261,  1296,  1267,  1269,  1278,  1279,  1280,  1281,  1282,  1297,
    1260,  1300,  1302,  1283,  1284,  1285,  1286,  1287,  1272,  1294,
    1277,  1274,  1275,  1276,  1273,  1289,  1290,  1291,  1292,  1293,
    1259,     0,     0,  1342,   767,     0,     0,   774,   795,   796,
     789,   791,     0,  1216,  1248,  1250,   808,  1244,  1245,  1246,
       0,  1551,  1209,     0,  1210,   816,  1212,   817,   814,   815,
       0,  1216,  1452,   876,   878,   877,   871,   873,   879,   882,
     857,   869,   865,   863,  1256,   632,   859,  1355,  1514,   896,
    1338,   632,  1546,   922,   923,   925,   927,   928,   924,   926,
     917,  1546,   913,     0,   959,     0,   961,   960,   962,   953,
     954,     0,     0,   939,  1091,  1516,     0,     0,   973,  1216,
    1452,  1550,     0,  1000,   633,  1007,  1008,  1011,     0,  1003,
    1201,  1200,  1010,  1016,  1195,     0,     0,  1243,     0,     0,
       0,  1051,     0,     0,     0,  1076,     0,  1080,  1079,  1070,
       0,  1496,  1243,  1116,  1115,  1122,  1123,  1124,     0,  1216,
    1452,     0,  1439,     0,  1124,  1191,  1181,  1180,  1186,     0,
    1188,  1189,  1196,  1460,  1441,     0,   199,   200,   198,  1496,
     470,   481,   482,   480,   337,   486,   562,  1496,   553,   551,
     552,   554,  1510,     0,  1496,     0,   565,   557,  1510,   558,
       0,   561,   566,   564,   559,   563,     0,   560,     0,   548,
     576,   571,   574,   573,   572,   575,   550,   577,     0,   417,
     412,  1368,  1369,  1370,  1323,  1311,  1316,  1317,  1318,  1319,
    1322,  1398,     0,  1528,  1546,   314,     0,   703,  1212,   694,
     696,  1209,   700,   690,   730,  1496,   719,   720,  1496,   731,
     721,   722,   725,   735,   732,   723,     0,   733,   724,   734,
     716,   717,   689,  1511,     0,     0,     0,   707,   708,  1377,
    1362,  1376,  1424,  1452,     0,  1428,     0,  1424,  1424,     0,
    1421,  1424,  1424,  1424,     0,  1424,  1424,  1217,   740,  1219,
    1216,   752,     0,  1298,  1541,  1301,  1303,   757,   755,   762,
     763,   607,     0,   773,   772,  1182,  1183,   777,   775,     0,
     794,     0,   799,   632,   632,   809,   807,  1247,   823,   823,
     823,   823,  1496,   828,   841,   842,   829,     0,  1496,   832,
     833,   836,   834,     0,   835,   825,   826,   818,   824,   632,
    1213,  1208,     0,   847,     0,  1256,  1256,   875,   632,   872,
     867,     0,   905,     0,     0,   929,     0,     0,     0,   955,
     957,     0,   949,   965,   950,   951,   944,   945,   965,  1083,
    1496,     0,  1517,  1090,   415,   416,  1501,   974,   977,     0,
       0,   991,  1001,   998,   635,     0,     0,  1018,  1017,  1232,
    1234,  1035,  1229,  1230,  1042,  1040,     0,  1256,  1053,  1256,
    1047,  1055,  1068,  1069,  1071,  1448,  1109,  1223,     0,  1452,
    1130,     0,     0,  1440,  1150,  1151,     0,  1154,  1157,  1161,
    1155,  1187,  1514,  1190,  1202,  1464,   196,     0,   217,   218,
     214,     0,     0,   472,     0,  1531,     0,  1496,   555,   556,
       0,   579,  1496,  1544,   580,   578,   411,  1478,   407,  1501,
    1399,   435,   295,  1207,   701,     0,     0,  1252,  1252,   718,
     713,   712,   714,  1417,  1216,  1425,     0,  1437,  1422,  1415,
    1435,  1416,  1418,  1419,  1432,  1433,  1420,  1414,   632,  1220,
    1215,   741,   750,  1546,     0,  1546,     0,   764,   765,     0,
     769,   768,   770,  1184,  1185,   780,   778,   632,   792,   793,
    1249,  1251,  1209,  1209,  1209,  1209,     0,   830,   831,     0,
    1252,  1252,   827,  1211,   632,  1216,  1326,  1216,  1326,   874,
     880,   870,   898,   906,   908,   915,   918,   919,  1486,   930,
     911,   916,   965,  1380,  1381,   965,     0,   948,   946,   947,
     952,  1093,     0,  1518,  1087,  1216,   990,   984,     0,   634,
    1012,     0,     0,  1024,     0,   632,   632,  1036,  1034,  1231,
    1043,  1038,  1041,  1048,   632,  1057,  1056,  1449,     0,     0,
    1110,  1101,  1224,  1126,  1226,     0,  1216,  1216,  1141,  1439,
    1153,  1494,  1159,  1494,  1223,     0,  1239,  1241,  1205,  1203,
    1236,  1237,  1204,  1465,     0,   215,   469,  1496,     0,   474,
     479,  1510,   515,   535,   530,  1468,     0,     0,  1496,  1512,
    1496,     0,   485,   491,   492,   493,   502,   494,   496,   499,
     487,   488,   489,   495,   498,   516,   500,   503,   490,     0,
     497,   501,  1389,   570,  1387,  1388,   586,   569,   581,   591,
       0,  1496,  1496,   430,   727,   726,   729,     0,   728,   742,
    1426,  1218,   632,  1306,  1546,  1309,  1546,   766,   781,   759,
     632,   776,   822,   821,   820,   819,   838,   837,   840,   839,
    1214,   849,     0,   848,     0,   632,   909,   903,   920,  1487,
       0,   964,   956,   965,   967,     0,     0,  1096,  1092,  1086,
     978,   993,     0,     0,  1019,  1496,  1026,     0,  1020,     0,
    1023,  1233,  1235,   632,  1054,   632,  1103,  1104,  1105,  1106,
    1107,  1108,   632,  1127,  1118,  1227,  1222,  1125,  1132,  1131,
    1152,     0,  1494,  1156,     0,  1163,  1175,  1172,  1174,  1173,
    1168,  1171,   632,   632,  1206,  1193,  1238,  1199,  1198,  1503,
       0,  1496,  1496,   476,   514,  1496,   536,   534,   531,   532,
    1498,   524,  1496,  1256,     0,     0,     0,     0,   517,     0,
       0,   522,   525,   528,   589,   587,   588,   590,     0,   584,
     582,   583,   585,     0,   421,   418,   419,     0,     0,  1503,
    1221,  1305,  1308,   779,  1216,  1216,   907,     0,   963,   968,
       0,  1496,  1094,     0,     0,  1084,  1088,   992,     0,     0,
    1029,  1027,  1028,  1022,  1021,  1049,  1058,  1225,   632,  1158,
       0,  1162,  1164,  1148,  1240,  1242,  1504,  1505,  1197,   471,
       0,     0,  1496,   467,     0,   523,     0,   520,  1452,   518,
     519,   509,   507,   508,   510,   506,   511,   505,   504,     0,
     529,   527,   526,   568,   567,   420,   414,   436,  1253,   851,
     850,   921,   966,     0,  1097,  1496,  1256,  1025,  1030,  1015,
    1228,  1160,   473,   475,     0,   513,   512,   533,     0,  1095,
       0,  1013,   477,     0,  1098,   521
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,     7,     8,    23,    38,    68,   126,
     243,     9,    24,    39,    69,    89,   466,    72,    70,    34,
      11,    20,    26,    41,    56,    57,    16,    36,    76,    96,
      97,   183,   184,   170,    98,   171,   172,   173,   174,   469,
     175,   176,    99,   179,   180,   181,   255,   100,   202,   203,
     204,   205,   430,   488,   560,   206,   347,   480,   481,   482,
     761,   899,   483,   900,   207,   360,   361,   486,   208,   420,
     421,   209,   210,   211,   212,   213,   214,   215,    47,    77,
      79,   103,   101,   133,   365,   431,   506,   507,   909,   769,
    1108,   508,   905,   509,  1319,  1320,  1586,  1115,   510,   511,
     512,   513,   913,  1111,  1840,   514,   515,   516,   517,   518,
     519,   520,   521,   783,   136,   107,   108,   109,   110,   143,
     111,   370,   371,   435,   112,    30,    65,   146,    83,   226,
     151,   118,   152,   119,   156,   235,   318,   319,   645,   320,
    1350,   837,   533,   321,   450,   322,   651,   323,   324,   646,
     829,   830,   831,   832,   325,   326,   327,    82,   227,   153,
     154,   155,   233,   303,   441,   304,   383,   384,   530,   824,
     305,   529,   621,   622,   623,   946,   624,   625,   626,   627,
     628,   629,   936,  1329,  1629,  1630,  1786,  1858,  2185,  2186,
     630,   631,   814,   632,   633,   634,  1144,   942,   943,  2053,
     635,   636,   116,   294,   150,   376,   231,   438,   525,   526,
     527,   786,   928,   929,  1120,  1121,  1038,   930,  1590,  1843,
    2009,  2153,  2233,  1323,  1593,  1124,  1326,  1845,  2030,  2031,
    2248,  2032,  2033,  2034,  2035,  2239,  2036,  2037,  2038,  2039,
    2171,  2172,  2160,  2040,  2041,  2157,   458,   298,   528,   582,
     789,   790,   791,  1126,  1327,  1626,  2183,  2178,  1627,    50,
     242,   408,    86,   122,   121,   158,   159,   160,   239,   332,
     124,   334,   463,   464,   546,   547,   548,   549,   550,   841,
    1533,  1534,  1794,   551,   707,   708,   842,   962,  1160,  1371,
    1372,  1367,  1670,  1671,  1157,   709,   843,   981,  1183,  1181,
     710,   844,   989,  1402,   711,   845,  1452,   712,   846,  1193,
    1454,  1709,  1710,  1711,  1457,  1717,  1907,  1905,  2070,  2069,
     713,   847,  1002,   714,   848,  1003,  1460,  1461,   715,   849,
    1004,  1199,  1202,   716,   717,   718,   850,  1726,   719,   851,
     720,   852,  1011,  1472,  1745,  1746,  1210,   721,   853,  1015,
    1217,   722,   854,   723,   855,  1020,  1021,  1223,  1224,  1225,
    1495,  1493,  1758,  1226,  1486,  1487,  1757,  1490,   724,   856,
    1027,   725,   857,   726,   858,   727,  1033,  1499,   728,   860,
     729,   862,  1501,  1934,  2085,  2087,   730,   863,  1234,  1510,
    1765,  1936,  1937,  1938,  1940,   731,   864,   732,   865,  1040,
    1240,  1241,  1242,  1522,  1776,  1777,  1243,  1519,  1520,  1521,
    1770,  1244,  1947,  2200,   733,   866,   734,   867,  1047,   735,
     868,  1049,  1249,   736,   869,  1051,  1255,  1532,  1957,   737,
     870,  1054,  1258,  1793,  1055,  1056,  1057,  1536,  1537,   738,
     871,  1546,  1963,  2106,  2210,  2269,   739,   872,   740,   873,
    1968,   741,   874,  1547,  1971,   742,   743,   875,  1068,  2113,
    1275,  1549,  1974,  1810,  1811,  2115,  1273,   744,   876,  1073,
    1074,  1075,  1076,  1287,  1077,  1078,  1079,  1080,   745,   877,
    1044,  1951,  1245,  2099,  1524,  1779,  2097,  2205,   746,   878,
    1288,  1562,  1978,  1981,   747,  1086,  1291,   748,   881,  1088,
    1089,  1817,  2124,   749,   882,  1092,  1297,   750,   884,   751,
     885,   752,   886,   753,   887,  1302,   754,   888,  1304,  1824,
    1825,  1574,  1827,  1992,  2133,  1994,  2223,   755,   756,   890,
    2140,  1100,  1307,  1578,  1718,  1906,  1832,   757,  1580,   758,
     759,   892,  1268,  1834,  2094,  1998,  2145,  1647,  1475,  1476,
    1749,  1751,  1924,  1698,  1699,  1888,  1890,  2062,  1983,  1984,
    2122,  2126,  2218,  1801,  1802,  1965,  1803,  1966,  1999,  2000,
    2142,  2001,  2143,  1466,  1467,  1468,  1723,  1469,  1724,  2056,
    1035,  1036,   991,   992,  1188,  1189,  1433,  1434,  1435,  1436,
    1437,  1134,  1337,  1378,   982,  1005,  1203,  1063,  1069,   373,
     374,  1081,  1082,  1231,  1058,   995,   996,   285,   452,  1117,
     453,   263,  1029,  1030,   983,  1007,  1137,  1375,  1680,  1778,
    1942,  1013,  1059,  2043,   985,   964,   809,   938,   939,  2045,
     986,   826,   827,   987,  1166,  1168,  1382,  1396,  1391,  1388,
     234,  1826,  1314,  1186,  1266,  1979,   217,  1205,   948,   368,
     389,  1315,   252,  2004,  1755,   398,   225,   640,  1161,   573,
     161,   569,   278,   289,  2090,   139,   291,   838,   539,    42,
     429,   574,  2228,   535,   395,  1674,   952,   221,  1783,   919,
     177,  1207,   806,  1644,   269,   638,   649,   764,   223,  1705,
    1233,  1129,   564,   804,  1473
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1710
static const yytype_int16 yypact[] =
{
   -1710,   279,    38, -1710,  -162,   168,    38, -1710, -1710, -1710,
     523,   523,   660,   660, -1710,   522, -1710, -1710, -1710, -1710,
     622,   622,   226,   636,   636,   594,   387, -1710,   805,   811,
   -1710, -1710, -1710, -1710,   -59,   619,   986,   542,   679,   679,
   -1710,   563,    55,   601,   644,   692,   699, -1710,   207,  1039,
     863,  1045, -1710,   261, -1710, -1710,   920, -1710, -1710, -1710,
     790, -1710, -1710, -1710,   904,   820, -1710,    39, -1710,   377,
     523,   660, -1710, -1710, -1710, -1710,   788, -1710,  1095,   156,
     831,   936,  1048,   865, -1710, -1710,   969,   660, -1710, -1710,
   -1710,   858,   879,   880,   881,   886, -1710, -1710, -1710, -1710,
   -1710,   989,   896,  1133,  1280,   954,   853, -1710,    89, -1710,
   -1710, -1710, -1710, -1710,   913,  1014,  1136, -1710,     3,   928,
   -1710,   112,   112,   937,   927,   929,   636, -1710,   714,  1189,
      92,  1445,  1103, -1710, -1710,   935, -1710,  1111, -1710,   999,
   -1710, -1710, -1710,  1364, -1710, -1710, -1710, -1710,   944,  1043,
    1071, -1710,   865, -1710, -1710, -1710, -1710, -1710,   224, -1710,
     -95,  -123,   235, -1710, -1710, -1710, -1710,  1035,  1191, -1710,
     579, -1710,   597, -1710, -1710, -1710, -1710,    86,   185, -1710,
     -44, -1710, -1710, -1710,   956,   245,  1300,   972,  1191,  1191,
     972,  1031,  1057,  1191,  1191,  1191,  1191,  1191,   972,  1191,
    1362,  1191, -1710,   930, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710,   972,   989,   156,
   -1710,   990, -1710,  1336, -1710,  1251,     3,   928, -1710,   978,
    1078,  1085,   928,   492,   997,   822, -1710,  1191,  1068,  1159,
   -1710, -1710,  1330,   679,  1191,  1210, -1710,   663, -1710, -1710,
    1093, -1710,  1191,  1243, -1710,    71, -1710, -1710, -1710, -1710,
    1005,  1211, -1710, -1710,   972,   972,  1191,  1191, -1710,  1191,
     990,  1390,   972,   972,   990,  1191,   990, -1710,   972,    12,
   -1710, -1710, -1710, -1710,    78,   990, -1710, -1710, -1710,   865,
   -1710,   865, -1710, -1710,   928, -1710,  1011,  1112, -1710, -1710,
   -1710,   997, -1710,  1016,   -12, -1710, -1710,  1336,  1191,   873,
     873,  1191,   151,  1222,  1191,  1444,  1199, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,   741,   221,
    1191, -1710,  1046,  1032, -1710,   863,  1210, -1710, -1710, -1710,
   -1710,   990, -1710, -1710, -1710, -1710, -1710,  1191, -1710, -1710,
     868,   990,  1252, -1710, -1710, -1710, -1710, -1710,   990, -1710,
   -1710,    58, -1710, -1710, -1710, -1710, -1710, -1710,   990, -1710,
     865, -1710,  1192,   865, -1710, -1710,   928, -1710,  1053,  1056,
   -1710, -1710,  1409, -1710,  1412,  1210,  1073,  1191,  1444,   990,
     306,   -66,  1210,  1081, -1710,  1191,  1083, -1710,  1083,   -13,
   -1710, -1710, -1710, -1710, -1710,  1210, -1710, -1710, -1710,   451,
      31, -1710,   902, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
     868, -1710,  1128, -1710, -1710, -1710, -1710, -1710, -1710,  1210,
   -1710,   923, -1710, -1710,  1210, -1710, -1710, -1710,  1212, -1710,
   -1710, -1710,   882,  1129, -1710, -1710, -1710,   990, -1710, -1710,
   -1710, -1710, -1710,  1298,    61,  1331,  1099, -1710, -1710, -1710,
    1191,  1191, -1710, -1710,  2429,   660, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710,   552, -1710,    81, -1710,   868,  1210, -1710,   942, -1710,
    1222,  1224,  1139, -1710,  1181,  1222,  1191,  1488,   506,   -52,
    1210, -1710,  1113, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710,  1168, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710,  1191, -1710,  1083, -1710,  1212, -1710, -1710,  2830,
    1521,  1367,  1210,    76, -1710, -1710,  1210, -1710, -1710,  1188,
   -1710,   -51,   -51,  2637, -1710,  1108, -1710, -1710, -1710, -1710,
    1207,  3216,  1114, -1710, -1710,   552, -1710, -1710, -1710, -1710,
    1182,  1191,  1346, -1710,   125, -1710,  1191,   717, -1710,  1191,
   -1710,  1191, -1710,  1205,  1191,  1191,  1364,   117,  1191,  1130,
   -1710, -1710,   997, -1710,  1342, -1710, -1710,  -107,   262,   479,
     500,   694,  1137, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710,  1230, -1710,  1210, -1710, -1710, -1710, -1710,   990,
     990,  1360, -1710, -1710, -1710,   418, -1710, -1710, -1710,  1191,
     167, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710,   931,    41, -1710,
     148, -1710, -1710, -1710, -1710, -1710,   105,  1362, -1710,   101,
   -1710, -1710, -1710, -1710,  1473, -1710,  1351, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710,  1184, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710,  1139, -1710,  1934, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710,    23, -1710, -1710,  1285,
   -1710, -1710, -1710, -1710,   856, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710,   713, -1710, -1710,  1191,    32,  1191, -1710, -1710,   252,
     176,  1548, -1710, -1710,   -66,  1214, -1710,   990,   990, -1710,
    1310,  1310,  1312, -1710,   990, -1710,   139,   -12, -1710, -1710,
     997, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710,  1151, -1710, -1710,  1200, -1710,  1145,
    1215, -1710, -1710, -1710, -1710,  2170,   130,  1583, -1710,  1254,
    1254,   868,  1344,  1344, -1710, -1710,  1158, -1710, -1710, -1710,
   -1710, -1710, -1710,    62,  1446, -1710, -1710,  1129,  1210,  1169,
   -1710,  1172,   990,  3720,  1186,    -5,  2332, -1710, -1710,  4381,
     865,  1225,  4510,  4381,  1394,   684,   914,    72,   990, -1710,
   -1710,  1492, -1710,    72,   990,   949,   990,  3898,  4381, -1710,
    2220,   865,   990,   865,   990,    77,    90,   990,   865, -1710,
   -1710,  3965,  4045, -1710, -1710,   990,   990,   865,   990, -1710,
     813,  1525,   990, -1710, -1710, -1710, -1710, -1710, -1710,  1613,
   -1710,   972, -1710, -1710, -1710, -1710,   990,     6,   100,   127,
    1198, -1710,  1198, -1710, -1710, -1710,   628, -1710, -1710, -1710,
   -1710, -1710,   990,  1191,  1464,  1464,   167, -1710, -1710, -1710,
   -1710,  1450, -1710, -1710, -1710,  1210,  1242,  5082,  1194, -1710,
     990, -1710,   130, -1710,  1255,  1415, -1710,  1488, -1710, -1710,
   -1710, -1710,   990,   990,   868,   -66,   -66,  1617,  1362, -1710,
   -1710, -1710,  1530,   560, -1710,  1344,  1206,   990,  1209,  1213,
    1344,    78,  1216,  1217,  1219,  1220,  1227,  1229,  1231,  1232,
    1209,  1535, -1710,  4067, -1710, -1710, -1710, -1710,  1454, -1710,
    1605, -1710, -1710, -1710,  1266, -1710,    78, -1710, -1710,  1246,
   -1710, -1710,    25,   865,  1547,  1118, -1710,  1345,  1371,   865,
     903,  1558,  3457,  1023,  1054,  1559,   199,  1246, -1710, -1710,
      67, -1710, -1710, -1710,  1590, -1710, -1710, -1710,  1344,    72,
   -1710, -1710, -1710, -1710, -1710,  1301, -1710,    83,   990, -1710,
     197, -1710, -1710, -1710, -1710, -1710,  4381, -1710,  1294,  1560,
    1643,   883, -1710,  1302, -1710,  5103,  1561,   672,  1307,  1311,
    -114,  1305,   565,  1526, -1710,  1371,  1526,   990,  1565,  1273,
   -1710,  1264, -1710, -1710, -1710, -1710, -1710,  1465, -1710,    72,
   -1710,   -37, -1710,    98, -1710, -1710,    20,  1660,  3687, -1710,
   -1710,   990,  1567,  4146,   990,  1536,   933,  1604, -1710,  1389,
    1343,  1111,  1526,   713, -1710,   433, -1710, -1710, -1710, -1710,
     516, -1710, -1710,  1191, -1710, -1710, -1710, -1710,    25, -1710,
   -1710,   990, -1710,  1210,   997, -1710, -1710, -1710, -1710,  1606,
    1344,  5082,  5082,  5082,    21,   894, -1710, -1710, -1710,  1158,
   -1710,  5082, -1710, -1710,  1137, -1710,   130, -1710, -1710, -1710,
   -1710, -1710, -1710,  1298,   -66,  1607, -1710, -1710,  1264,   833,
    1286,   159,    -8,  5082,  1324,  5082, -1710,  5082, -1710,  1493,
    1287,  5082,  5082,  5082,  5082,  5082,  5082,  5082,  5082, -1710,
   -1710, -1710,  4381,  1539, -1710, -1710,  1392,  1454,  1813,  3048,
    1422,  1497, -1710,   417, -1710, -1710, -1710,   703, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710,    52,   865, -1710,
   -1710,   345,  1569,  1569,  1569,  1569, -1710, -1710,  4381,  4381,
   -1710, -1710,   171,  1600,   818, -1710,  1303,   684, -1710,   990,
   -1710,     9, -1710, -1710,   768,  1564, -1710,  1264,   128, -1710,
     197, -1710, -1710, -1710, -1710,    85,  1339,    72, -1710, -1710,
    4381, -1710, -1710, -1710, -1710,  1377, -1710, -1710, -1710, -1710,
     990,    -5, -1710,   910, -1710, -1710,  1371,    25, -1710,  1533,
     566,   775, -1710, -1710,   990,   775,  1347, -1710,  1158, -1710,
   -1710,    99,   942, -1710, -1710,  3629, -1710,  1691,  1528,  4381,
    4381, -1710,  4304,   990, -1710,  1568, -1710, -1710,  4381,  1264,
   -1710, -1710, -1710,  1660,  1540,   990, -1710,  1037,    88,   566,
   -1710, -1710,  1626, -1710, -1710, -1710,  1474, -1710, -1710,   990,
     990, -1710,   990,  1570,  1013,    66, -1710,  4791,  1111, -1710,
    1493,  1304,  1304,   970, -1710, -1710, -1710,  5082,  5082,  5082,
    5082,  5082,  5082,  4851,   894,  1391, -1710, -1710,  1298,  1111,
   -1710, -1710, -1710,  1569, -1710, -1710,  1309,  1318, -1710,  1264,
    1569,  1549, -1710, -1710, -1710, -1710,  1261,  1569,  1499,  1499,
    1499,   102,  1537, -1710, -1710,   149, -1710,    74,   845,   990,
     915,    80,  1316, -1710,  1158, -1710, -1710,   187,  1317,  1070,
     532,  1319,  1088,    97,   108,   608,  1320,  1134,  4353,   408,
    4381,    72, -1710,  1433, -1710, -1710, -1710, -1710, -1710,  1139,
   -1710, -1710,  1380, -1710, -1710,  1380, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710,  1378,    -5, -1710,   184,   990,   990,   625, -1710, -1710,
   -1710,   432,    28,  1407, -1710, -1710,  1647, -1710,  1517, -1710,
      93,  1582,  1569,  1515, -1710, -1710,  1522, -1710, -1710, -1710,
    1596,  4353,   423, -1710, -1710, -1710,  2929, -1710,  1388, -1710,
   -1710, -1710, -1710, -1710,   171, -1710, -1710, -1710,  1111, -1710,
   -1710, -1710,  1139, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
    1458,  1139, -1710,  1393, -1710,  1735, -1710, -1710, -1710,   975,
   -1710,  1264,  1202, -1710,    86,    27,   582,    72,    72,  4353,
     425,  1113,   865,  1651, -1710, -1710,  1780, -1710,  1623, -1710,
   -1710, -1710, -1710,  1533, -1710,   990,   541,    52,   872,  1372,
    1680, -1710,  1374,  1264,   821, -1710,   149, -1710, -1710, -1710,
    4381,  1191,    52, -1710, -1710, -1710, -1710,   -80,   990,  4353,
     429,  1410,  1796,   990,   446, -1710, -1710, -1710,  1507,  1508,
   -1710, -1710,   910, -1710,   180,   746, -1710, -1710, -1710,  1191,
    1638, -1710, -1710,  1210, -1710, -1710, -1710,  1191, -1710, -1710,
   -1710, -1710,  1499,  1102,  1191,  2332, -1710, -1710,  1499, -1710,
    1210, -1710, -1710, -1710, -1710, -1710,   990, -1710,   990, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,   990,  1612,
     582, -1710,  1158, -1710, -1710,   845,   787,   787,  1304,  1304,
    1304, -1710,  1157, -1710,  1139, -1710,   990, -1710,  1522, -1710,
   -1710,  1569, -1710, -1710, -1710,  1191, -1710, -1710,  1191, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710,    18, -1710, -1710, -1710,
    1261, -1710, -1710, -1710,    25,    25,    25, -1710, -1710, -1710,
   -1710, -1710,  1209,  1345,  4945, -1710,   990,  1209,  1209,  5082,
   -1710,  1209,  1209,  1209,   191,  1209,  1209, -1710, -1710,  1550,
    4353, -1710,    72, -1710, -1710,   502,   645, -1710, -1710,  2091,
   -1710,   544,    22, -1710, -1710, -1710, -1710,  1004, -1710,  1490,
   -1710,  1476, -1710, -1710, -1710, -1710, -1710, -1710,   -40,   -40,
     -40,   -40,  1191, -1710, -1710, -1710, -1710,  1120,  1191, -1710,
   -1710, -1710, -1710,    73, -1710,  1582, -1710, -1710, -1710, -1710,
   -1710, -1710,  4381, -1710,  4381,   171, -1710, -1710, -1710,  2929,
   -1710,   990,  1692,  1395,   605,  1708,  1396,   115,  1264, -1710,
   -1710,  1767, -1710, -1710, -1710, -1710,  1202, -1710,  1645, -1710,
    1191,  1542, -1710, -1710, -1710, -1710,  1346,    72, -1710,  4381,
     117,   585, -1710, -1710, -1710,   990,  4381,   634, -1710, -1710,
   -1710,  1683,  1573, -1710,  1685, -1710,  1597, -1710, -1710, -1710,
   -1710,  1374, -1710, -1710, -1710,  1577,  1693,  1553,  1543,  1345,
   -1710,  4381,   115, -1710,  1562, -1710,  1264, -1710,  1727,  1451,
   -1710, -1710,  1111, -1710,   932,  1834, -1710,   981, -1710, -1710,
   -1710,  1210,  1729,  1627,  1778,  4883,   263,  1191, -1710, -1710,
     263, -1710,  1191,  1242, -1710, -1710, -1710,  1660, -1710,  1346,
   -1710,  1448, -1710, -1710, -1710,   263,   263,    70,    70, -1710,
   -1710, -1710, -1710, -1710,  1407, -1710,  1197, -1710, -1710, -1710,
     845, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710,  1139,  1694,  1139,  1695, -1710, -1710,  4381,
   -1710, -1710, -1710, -1710, -1710,  1720, -1710, -1710, -1710, -1710,
   -1710, -1710,  1569,  1569,  1569,  1569,   263, -1710, -1710,   263,
      70,    70, -1710, -1710, -1710,  4353,  1529,  4353,  1531, -1710,
   -1710, -1710, -1710, -1710,  1716, -1710,   605, -1710,  1755, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710,   115,   910, -1710, -1710,
     910,    29,   990, -1710, -1710,  4353, -1710, -1710,   889,  3465,
   -1710,  1806,  1622,  1644,   540, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,   990,  1306,
   -1710, -1710, -1710,  1717,  1601,   990,  1407,  4353, -1710,  1796,
   -1710,  1331,  1769,  1331,  1553,   472, -1710, -1710,  1715, -1710,
    1609, -1710, -1710, -1710,   561, -1710, -1710,  1191,  1773,  1652,
   -1710,  1002, -1710,  1669,  1050,  1444,  1682,  1442,  1191,  1344,
    1191,   990, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710,  1494, -1710, -1710, -1710, -1710,   890,
   -1710, -1710, -1710, -1710, -1710, -1710,   409, -1710,   667, -1710,
    1441,  1191,  1191, -1710, -1710, -1710, -1710,   263, -1710, -1710,
   -1710, -1710, -1710, -1710,  1139, -1710,  1139, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710,  4381, -1710,  4381, -1710, -1710, -1710, -1710, -1710,
    1827,   910,   910, -1710,  1479,  1586,   865,   415, -1710,   990,
   -1710, -1710,  1545,  4381, -1710,  1191,   919,  1649, -1710,  1654,
   -1710, -1710, -1710, -1710, -1710, -1710,   990, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710,   990,  1331, -1710,   990,  1745, -1710, -1710, -1710, -1710,
   -1710,   865, -1710, -1710, -1710, -1710, -1710, -1710, -1710,  1089,
    1210,  1191,  1191,  1719, -1710,  1191, -1710, -1710, -1710, -1710,
     167, -1710,  1191, -1710,   990,   990,   683,  1721, -1710,  1610,
    1210,   890, -1710, -1710, -1710, -1710, -1710, -1710,   263, -1710,
   -1710, -1710, -1710,   263, -1710,  1441, -1710,   990,   130,  1089,
   -1710, -1710, -1710, -1710,  1407,  1407, -1710,  4381,   910, -1710,
    4381,  1191,   865,   865,  1591, -1710, -1710, -1710,  1477,   990,
    1758, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
     990, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
    1210,  1210,  1191, -1710,  1210, -1710,  1210, -1710,  1345, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,  4381,
   -1710, -1710, -1710, -1710, -1710, -1710,   990, -1710, -1710, -1710,
   -1710, -1710, -1710,    -5,   865,  1191, -1710,   990, -1710, -1710,
   -1710, -1710, -1710, -1710,  1210, -1710, -1710, -1710,  1850, -1710,
      -5, -1710, -1710,  4381, -1710, -1710
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1710, -1710, -1710, -1710,  1894, -1710, -1710, -1710,    49, -1710,
   -1710, -1710, -1710, -1710,  1571, -1710, -1710, -1710,  1223, -1710,
   -1710,    44,  1881, -1710, -1710,  1851,   256, -1710, -1710, -1710,
   -1710, -1710,  1718,  1775, -1710, -1710,  1737,   760, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710,  1728, -1710, -1710, -1710, -1710,
    1706, -1710, -1710, -1710,   629, -1710, -1710, -1710, -1710,  1429,
   -1710, -1710,  1357,   812, -1710, -1710, -1710, -1710, -1710, -1710,
    1500, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710,  1783, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710,   609, -1710,   603,   809, -1710, -1710,
   -1710, -1710, -1710,  1009,    94, -1710,  1359, -1710, -1710, -1710,
   -1710, -1710, -1710,   142, -1710,  1710, -1710,  1826, -1710, -1710,
   -1710, -1710,  1566, -1710, -1710,   791, -1710, -1710, -1710, -1710,
    1711, -1710,  1891,  1789, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710,  1107, -1710, -1710, -1710,  1403, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,   405,
   -1710, -1710, -1710,  1648, -1710,  -547,  -744, -1710, -1710, -1710,
    -381, -1710, -1710, -1710, -1710, -1710, -1710, -1282, -1281,  1131,
   -1278,   103, -1710, -1710, -1710, -1710,   322, -1710, -1710,  -232,
   -1274, -1710, -1710, -1256, -1710, -1253, -1710, -1710,  1012, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
    1430, -1710, -1710, -1710,  1030, -1710,  -875, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710,   -70, -1710, -1710, -1710, -1710, -1710,
   -1710,  -206, -1710, -1710, -1710, -1710,  -168, -1710, -1710, -1710,
   -1710, -1710,  1178, -1710, -1710, -1710, -1710, -1710, -1710,   220,
   -1710, -1710, -1710, -1710, -1710,  1848,  1074, -1710,   260, -1710,
   -1710, -1710, -1710,  1509, -1710, -1710, -1710, -1710, -1710, -1710,
    -811, -1710, -1710,   179, -1710, -1710, -1710, -1710,   962,   604,
     606, -1710, -1710,   305, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,   961,
   -1710, -1710,   271, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710,   -78, -1710,   236, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710,   755, -1710, -1710,   762,
   -1710, -1710, -1710, -1710,   493,   237, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710,    54,   757, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710,   753, -1710, -1710, -1710,   222, -1710, -1710,   477, -1710,
   -1710, -1710, -1360, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1149,   946, -1710, -1710,   202, -1710,
   -1710,   459, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710,   695, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710,   728, -1710,   195, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710,   940, -1710,   934, -1710, -1710,
    1132, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
     924,   434, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
      30, -1710,   444, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710, -1710,
   -1710, -1710,  -444, -1710, -1151, -1710, -1710, -1148, -1153, -1167,
   -1710,   359, -1710, -1156, -1710, -1710, -1710, -1710,    26, -1710,
   -1710, -1710, -1710,   -84, -1710, -1710,   223, -1710, -1710, -1710,
   -1710,    24, -1710,  -474, -1709, -1710, -1710,   558, -1710,  -804,
   -1244,  -807, -1180, -1710, -1710, -1710, -1173, -1171, -1170, -1166,
   -1165,   143,  -195,  -169,  -465, -1128,  -838,   288,   960,  -997,
     -83, -1710, -1064, -1710,  -763, -1710,   837,  -387,  -182, -1710,
    -646,   -15,  -762,  -954,   230,  -802, -1710, -1710,   473, -1016,
   -1015,  -929,  -813,  -797,   620,  -589,  -218, -1710,  1094,  -220,
    -634,  -696,  -274,  -446,  -850, -1710, -1710, -1710, -1710, -1710,
    1800, -1710,   452,   850, -1710, -1710, -1710, -1645,  1221,  -674,
    1730,   794,  -417, -1710,  1022,  -383,  1467, -1710,  -606, -1710,
   -1056,  1097,  -407,   515, -1710, -1710,  -668, -1710, -1277,  -167,
    -613,  -490,  -143,  -820,   706, -1306,  -810, -1057, -1710,  1267,
    1991,  -827, -1710, -1710, -1710, -1710, -1710, -1710, -1710,   635,
   -1710,   196,  -667,   907,  -126
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1551
static const yytype_int16 yytable[] =
{
     120,   245,   447,   287,   186,   446,   825,   816,   859,   575,
    1094,  1006,  1208,   953,   522,  1535,  1445,  1283,  1446,  1447,
     808,   264,   265,  1448,  1449,   338,   270,   271,   272,   273,
     274,  1292,   276,   999,   279,   787,   891,   990,  1874,   286,
     833,   984,  1488,   932,  1308,  1620,  1621,   537,  1022,  1622,
     984,  1016,   287,  1623,  1398,  1276,   287,    21,   287,   186,
    1477,  1478,  1479,  1675,  1676,  1048,  1050,   287,   328,   120,
     329,  1624,   766,  1195,  1625,  1230,   422,   336,  1028,  1090,
     984,   426,   994,  1230,  1221,   341,  1067,   467,   353,  1028,
    1334,  1481,   357,    84,   359,  1365,  1028,  1579,   554,   350,
     351,  1037,   352,   369,  1028,  1028,   363,  1900,   358,   404,
     955,   104,  1542, -1514,  1083,    91,   410,   277,    88,   157,
    1498,  -183,  1529,   287,   821,  2002,   780,    53,   914,  1230,
    1179,   125,   643,   287,   178,   828,  1867,  1514,  1373,   821,
     287,   386,  1351,  1334,   391,   393,   422,   396,   250,  1334,
     432,    40,   902, -1474,   460,  1162,   381,   821, -1501,   411,
    1169,   157,   572,   405,   451,   443,  1334,  1368,    62,   423,
    1569,   287,   454,   287,  1986,   266,   425,  1334,   104,   650,
     412,  1184,   944,   275,  1515,   462,  1648,  1728,  1526,  1321,
     426,  1920,  1483,  1648,   253,   240, -1550, -1514,   822,   923,
    1648,   788,   282,  1289,  1311,  1072,   372,   286,   910,   487,
    1184,   556,  1652, -1550,   523,  -184,  1284,     4,  1229,  1672,
     445,  1513, -1550,  1781,  1368,   993,   924,   925,   456,   287,
     459,  1042,  2095,   157,   381,   288,  -183,  1071,  1269,   993,
     835,  1139,  1106,   787,  1246,   767,  1322,  1572,  1218,   348,
     349, -1550,   402,   879,   793,  1194,  1334,   355,   356,    51,
     819,  1464,  1720,   362,   364,   369,   557,    17,   427, -1478,
     237,  1628,  1700,   157,   366,   531, -1550,   836,   343,     3,
     576, -1391,  1721,  1571,   157,    12,  1090,   372,  1237,   768,
     436,  1184,  1646,   541,   542,  1374,  1847,  1170,  1516,  1311,
   -1478,   344,  1852,   794,   241,  1782,   413,  1722,   944,  1152,
    1153,  1465,   642,  1123,  1488,   238,   647,  1281,   993,  1747,
    1330,   413,  1191,   652,   652,  1753,    90,  1230,   403,   567,
    -184, -1492,  1072,  1347,   105,  1072,   937,   911,  1544,   413,
    1901,   903,     5,  1651,  1006,   414,   428,  1517,   367,    40,
      63,  1154,   415,   182,  1290,   579,   580,  1107,   220,  1282,
     414,    40,   637,  1149,  1150,   880,   907,   415,   284,   823,
      54,   781,    62,  1788,  1335,  1278,   577,   427,   414,  1679,
    1399,  1006, -1501,   284,   807,   415,  1369,  1450,   -31,   904,
     644,  1729,   810,  1471,   765,  1463,  1370,  2212,  1712,   770,
    1001,   105,   774,   256,   775,  1219,  1731,   777,   778,   788,
    1884,   784,  1006,  1820,   912,   254,  1480,  1482,  1950,  1043,
    1022,   461,   382,   416,  1001,   926,   284,  1335,   782,   284,
   -1478,  1835,   106,  1335,  1868,  1139,  1139,  1139,   416,  1543,
    -183,  1761,   251,   284,   820,  1139,   262,  1701,  1530,  1902,
    1335,   337,   815,  1370,    55,  2096,   416,   536,    88,   284,
    1006,  1335,  1278,   335,   956,    85,   468,  1139,  1500,  1139,
    1336,  1139,  1136,  1384,   555,  1139,  1139,  1139,  1139,  1139,
    1139,  1139,  1139,  1559,  1648,  1528,   417,  1563,  1564,  1921,
    1566,  1140,   262,   337,  1285,  1554,  1570,  1222,  1539,   106,
    1594,   417, -1478,  1864, -1478,  1771,   284, -1474,  1348,   552,
   -1478,   284,  1346,    87,  1286,   418,   182,   284,  1312,   417,
     834,  1238,   284,  1682,   284,   182,   169,  1730,  1645, -1430,
     418,  1518,   284,   284,  -184,  1791,   144,  1812,   182, -1478,
    1335,  1278, -1478,   570,  1891,  1581,  1692,   950,   418,   284,
     908,  1155,  1311, -1478,    63,   419,   287,  1693,  -600,   287,
     287,   284,  1006,  2023,  2024,  1975,   287,  2025,  1484,  -598,
     419,  2027,  1485,  1376,  1230,  1488,    54,  1325,   448, -1496,
    1383,  1595,  2091,   284,  1239,  2092,   927,   465,   419,  2028,
    1158,  -744,  2029,  2277,  1885,   916,   917,   901,  2203,   906,
    1455,  1334,   922,  1278,   290,    64,  1754, -1550,  1789,  1001,
    1784, -1478,  1821,  1312,   284,    13,   571,  1503,   959,   931,
    1504,  1505,  1270,   795,  1925, -1474,  1927,   997,  1338,  1339,
    1340,  1341,   293,  1342,  1632,  2136, -1436,   299,   812,    22,
    1497,  1139,  1139,  1139,  1139,  1139,  1139,  1139,  1045,    25,
    2174, -1478,  1060,  1712,  1064,  1893,  1064,  1070,  1309,  1045,
      55,  1955, -1478,  1278,  1799,  1550,  1136,  1136,  1136,  1550,
      15,  -600,   796,    28,  1064,  2137,  1136,  1334,   182,   449,
    1151,     5,  -598,  2138,  1760,  1140,  1140,  1140,   287,  1708,
    1762,  1109,   259,  1987,  1785,  1140,  2204,   284,  1136,   375,
    1136,  2175,  1136,  2042,   287,  2155,  1136,  1136,  1136,  1136,
    1136,  1136,  1136,  1136,  2131,  1127,  2134,  1140,  2059,  1140,
     572,  1140,  1143,  1385,  1105,  1140,  1140,  1140,  1140,  1140,
    1140,  1140,  1140,  2198,  2107,    29,  1159,   287,   287, -1550,
    1116,  1631,  1703,   471,  1061,  1870,  1871,  1872,  1892,  1204,
    1316,  1456,  1945,  2139, -1490,     5,  1118,   813,  1814,  2072,
    2073,  2074,  2075,  1470,  1204,  1787,  1204,  1008,  1135,  2081,
    1204,  2083,  2241,  2242,  2108,  1995, -1521,  1502,  1471,  1894,
    1503,   437,   472,  1504,  1505,  1715,  1681, -1474,  1062,   473,
    1065,   337,  1851,  1719,  2109,  1085,  2243,  1800,  1895,  2100,
   -1550,  2050,  1113,  1072,  1096,   828,  2117,  1988,  2118,  2119,
    1990,  2057,  2057,  2120,  2121,    31,  1898,  1264,   167, -1550,
   -1550,  1098,   385,   306,    32,  1278,  1278,   392, -1550,  1962,
    2128,  2129,  1873,  1230,    33,  1763,   167,  1878,  1879, -1550,
     797,  1881,  1882,  1883,  1766,  1886,  1887,  2147,  1099,  1070,
    2176,  2177,  1506,  1507, -1474,  2220,  1317,  1278,  1352,  1353,
     475,   799,  1265, -1476,  2057,  2057,  1312,  -201, -1550,   307,
    1508,  1509,  1136,  1136,  1136,  1136,  1136,  1136,  1136,   182,
     284,  1114,    74,   308,  1633,  1335,  1104,    35, -1550,   798,
      18,  1140,  1140,  1140,  1140,  1140,  1140,  1140, -1474,  1354,
      74,  1355,   167,  1324,   893,   400,   117,  1716,  2179,   237,
     800,  1235,  1910,  1911,  1926,   493,  1928,   166,  1540,  2237,
    1197,   309,  1896,   476,   489,   401, -1438,   490,    37,  1061,
     168,  2093,   249,  1356,  1357,  1358,   287, -1550,  1923,   300,
    2148,   187,   491,   894,   494,  1541,  1318,  1931,   168,  1930,
     895,  1006,   492,   167,   238,   188,   189, -1550,   821,  2180,
   -1490,  1335,  1331,  1332,  1333,    19,    74,  1681,    43,  2110,
    2244,  2245,  1344,  1338,  1339,  1340,  1341,  1861,  1342,    49,
    1359, -1434,  1360,  1006,  1514,   250, -1496,   190,  1139,    48,
    1361,  1837,   479,  1139,  1961,   284,  1380,  1113,  2141,   182,
    1973,  2042,  1387,  1389,  1390,  1392, -1496,   249,  1395,  1397,
      52,  2246,  2247,   997,   168,  1506,  1507,    74,   182,   117,
    1458,   896,  2281,   470,   191,   192,   246,   193,   290,   771,
     966,  1515,    40,  1508,  1509,   194,   772,   310,  2259,  2260,
     889,    60,  1799,   997,   248,   968,  1251,   311,    58,  1338,
    1339,  1340,  1341,  2047,  1342,   801,    92, -1431,  1838,   413,
    1839,  1362,  -201, -1550,  2058,   168, -1496,   182,  2054,  2055,
   -1521,  1462,  1278,  1804,   501,  1072,  1114,  2061,   195,   196,
    1278,  1018,  1012,  1996,   897,  1019,  1252,  1259,  1816,   197,
     997,    59,    40,   471,  1253,   817,  2071,  2067,   414,  2202,
    1260,   287,   287,  2116,   802,   415,  1805,  1780,  2181,  2182,
     339,  1459,  1093,  2080,  2279,   818,  2078,  2079,    93,  2076,
     337,   493,  2077,  2101,   965,   436,  1806,   821,  1464,   969,
    1278,  2284,   472,  1944,   312,   313,   182,  1587,  1587,   473,
     413,  1464,  2169,  2102,  1548,  1516,    61,   314,   169,   315,
     494,   474,    44,   898,  2111,  2112,    67,   495,    94,  1001,
      95,   198,  1066,  2114,  1254,   140,  -958,     5,  1635,  1636,
    1637,  1638,  1639,  1640,  1642,  1800,   416,    71,  1465,   414,
    1102,   972,  2170,  1548,   973,   387,   415,   388,  1944,  1997,
      45,  1465,  1686,  1576,  1517,  1689,   561,  1577,    46,   966,
    1694,   566,   496,  1023,  1024,  -958,  2264,  2149,   497,  2165,
     475,  1772,  -958,   558,   968,   559,   974,  1025,  1557,  1136,
     141,   142,  1558,    74,  1136,    10,  2063,  1363,  2065,    10,
    1340,  1341,   236,  1342,   997,   498,   236,    78,  1140,   417,
    1591,  1592,   499,  1140,  2194,  1300,  2195,  1301,  1222,   316,
    1491,  2190,  1848,    80,  1849,   500,    81,   416,  1773,  2193,
    2189,   102,  1903,  1026,  1904,  1673,  2154,  1364,   418,   317,
    1917,  1200,  1918,   476,  2196,   199,   477,   478,   113,   251,
     501,   115,   502,  -958,   975,   114,  1338,  1339,  1340,  1341,
     503,  1342,  1654,  1838,  1655,  1839,  1954,  1656,   969,   117,
    -206,  2208,  2215,   123,  2216,   127,  1377,  1657,   419,   413,
    1381,  2217,  1944,  2158,  2159,   200,  2226,  2227,  1393,  1394,
     417,   504, -1383, -1383, -1383, -1383,   128,   129,   130,   976,
     977,  2224,  2225,   131,  2267,  1338,  1339,  1340,  1341,   970,
    1342,   132,   479,   134,   971,   135,  -958,  1343,   414,   418,
     972,   137,   138,   973,   978,   415,  1338,  1339,  1340,  1341,
     147,  1342,  -326,   148,   201,   149,   287,   178,  1684,  2051,
     505,   163,   979,  1844,   164,  -958,   165,   280,  1518,   216,
     980,  2253,   219,   284,   220,   974,  2254,   222,   224,   419,
    1853,   228,   229,   413,  1815,  2261,   230,  2191,  2262,  2192,
     244,    40,  1587,   258,   261,  1790,   262,  2270,   267,  -958,
     287,  1338,  1339,  1340,  1341,  -958,  1342,   268,   277,  1634,
     288,  1774,  1841,   290,   284,   295,   416,   296,   287,   297,
    1846,   302,   414,   330,  1658,   331,   333,  1850,  1659,   415,
     337,  1818,  1212,  1213,  1214,  1215,  1856,  2278,  1818,   340,
     342,  1660,   345,   975,   346,   413,   187,   354,   377,  1409,
    1410,   378,   963,   380,  1862,   394,  1000,   397,   287,   399,
     188,   189,  1014, -1382, -1382, -1382, -1382,  1031,  1032,   407,
     406,  2285,   424,  1031,  1039,  1041,   434,  1411,  1865,   417,
    1000,  1866,  -338,  1412,   414,   442,  1031,  1661,   976,   977,
     439,   415,   190,   440,  1877,  1039,  1095,   444,  1097,   455,
     416,  1338,  1339,  1340,  1341,  1876,  1342,   457,   418,  1688,
    1880,   485,   524,   978,  1414,   532,   534,   538,  1415,  1338,
    1339,  1340,  1341,   540,  1342,   563,   562,  1691,   565,   191,
     192,   979,   193,   568,  1662,   578,   182,  2235,   639,   980,
     194,   641,   284,   648,  2257,   655,   656,  1138,   419,   763,
     572,   760,   776,   792,   785,  1916,  1201,   803,  1663,   805,
     811,  1919,   416,   417,   966,  1338,  1339,  1340,  1341,   839,
    1342,   840,  -810,  1696,   883,   570,   921,  1164,   915,   968,
     918,   934,  1664,   195,   196,   937,   935,  1665,  1338,  1339,
    1340,  1341,   418,  1342,   197,  1775,  1860,  1666,   940,   947,
     945,  1667,   954,  1952,   951,  1732,   960,   957,  1733,   961,
     988,  2006,  1196,  1009,  1017,  1034,  1734,  1735,  1736,  1101,
    1103,  1110,  2161,  1119,  1125,   417,   284,  1128,  1338,  1339,
    1340,  1341,   419,  1342,  1141,  1147,  2060,   828,  1146,  1031,
    1912,  1913,  1914,  1915,  1156,  1185,  1163,  1031,  1236,  1165,
    1180,  1187,  1190,  1167,   418,  1958,  1171,  1172,  1668,  1173,
    1174,  1964,  1192,   969,  1198,  1000,   198,  1175,  1669,  1176,
    2046,  1177,  1178,  1206,   413,  2048,  1204,  1209,  1228,  1216,
    1247,  1277,  1250,  1232,  1248,  1263,  1257, -1385,   284,  1031,
    1261,  1274,  1267,  1031,   419,  1272,  1262,  1072,   436,   157,
    1296,  1295,  1299,  1303,  1236,  1305,  1306,  1328,  1349,  1366,
    1379,  1386,  1400,   414,  1451,   972,  1401,   993,   973,  1474,
     415,  1489,  1512,  1494,   287,  1527,  1531,  1737,  1196,  1545,
    1560,  1039,  1561,  1553,  1568,  1583,  1573,  1585,  1649,  1643,
    1342,  1138,  1138,  1138,  1429,  1738,  1650,  1431,  1432,  1589,
     974,  1138,  1673,  1653,  1369,  1685,  1687,  1702,  1690,  1695,
    2098,  1704,  1739,  1697,  1707,  1725,  1465,  1748,  1277,  1752,
    1750,  1756,  1764,  1138,  1768,  1138,  1792,  1138,  1795,  1767,
     199,  1138,  1138,  1138,  1138,  1138,  1138,  1138,  1138,  1796,
    2256,   416,  1807,  1808,  1809,  1823,  1822,  1831,  1842,  1833,
    1857,  1889,  1908,  1909,  1933,  1939,  1946,  1949,  1740,  2173,
    1953,  1967,  1935,  1941,  1970,  1404,  1405,  1406,   975,  1800,
     200,  1972,  1977,  1407,  1980,  1982,  1985,  1991,  1993,  1989,
    2150,  2003,  2007,  2008,  2010,  2052,  2068,  2064,  2066,  2086,
    2082,  2164,  2084,  2166,  2089,  2103,  2104,  1277,  2105,  2123,
    2144,  2125,  2132,  2151,   417,  1741,  1997,  1031,  2156,  2152,
    2162,  1408,  2163,   976,   977,  2184,  2197,  2019,  2199,   201,
    1538,  2206,  2207,  2213,  2187,  2188,  2201,  1196,  2214,  2222,
    2232,  2265,  2266,   418,  1551,  2268,  2250,  2249,   978,  2283,
      14,  1031,    27,   260,    73,   185,   409,   247,   257,   281,
     553,  1555,   762,  1567,  1313,  1310,   979,   218,  1742,  1277,
     484,  1112,  1584,  1588,   980,  1575,   773,   284,  1743,   283,
    2229,  2005,  1956,   419,   145,   861,   433,   292,  2209,    66,
    -901,   232,  1236,  -901,   958,   653,   941,   287,  2026,   379,
    2251,  2173,  1859,  2255,  1145,  1122,   581,  1138,  1138,  1138,
    1138,  1138,  1138,  1138,  2168,  2252,  1409,  1410,   933,   287,
     162,  1899,   543,  1959,  1211,  1869,  1678,  1677,  1220,  1277,
    1897,  1922,  1496,  2240,  2230,  2231,  1492,  1759,  2234,  1744,
    2088,  1511,  1929,  1523,  1411,  2236,  1769,  1960,  1948,  1683,
    1412,  1256,  1797,  1552,  1582,   286,  1976,  1863,  1829,  1084,
    2272,  2273,  1294,  1280,  2275,  -901,  2276,  1279,  1830,  2130,
    2135,  1031,  2211,  1413,  2146,  1969,  1727,  1271,  1453,  1813,
    -901,  1414,  1142,   301,  2263,  1415,  1836,  1403,   287,  1525,
     390,   949,  1227,   779,  1148,   997,  2258,    75,   920,  2049,
    1706,  1345,     0,     0,  2282,     0,     0,     0,   436,     0,
       0,     0,   997,  1416,  1417,  2274,     0,     0,  1418,     0,
       0,     0,     0,     0,   369,  1713,  1714,     0,  1419,     0,
       0,     0,     0,     0,     0,  1420,     0,  -901,  -901,     0,
    1421,     0,     0,     0,     0,     0,     0,  -767,  2280,     0,
    -767,     0,     0,     0,     0,     0,     0,     0,  1422,     0,
       0,     0,     0,     0,  -901,  -901,     0,     0,     0,   436,
       0,  -901,     0,     0,     0,  -901,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     157,  1277,  1277,     0,  -901,     0,     0,  1031,  1031,     0,
       0,     0,  -901,     0,     0,  -901,  -901,     0,     0,     0,
    -901,     0,     0,     0,  -901,  1798,  -901,     0,     0,  -901,
       0,  -901,  -767,  1277,     0,     0, -1478,     0,     0,     0,
       0,   436,     0,     0,  -901,     0,     0,  -767,  1819,  -901,
       0,     0,     0,  1828,  1828,     0,     0,     0,     0,     0,
       0,  -901,     0,     0,     0,     0,     0,   586,   587,   588,
     589,   590,   591,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1000,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1854,     0,  1855,     0,
       0,     0,  -901,   593,     0,   594,   595,   596,   597,   598,
     599,     0,     0,  1423,  1424,  1425,  1426,  1427,     0,  1428,
       0,  1429,  1430,     0,  1431,  1432,     0,     0,     0,  -901,
       0,  -767,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -767,     0,     0,   600,     0,     0,     0,     0,
       0,     0,     0,     0,  1196,  1196,  1196,     0,     0,     0,
       0,   966,     0,     0,  1138,  -901,     0,     0,     0,  1138,
       0,     0,  -767,     0,  -901,  -901,   968,  -767,     0,     0,
       0,  -767,  1031,  -767,     0,     0,  -767,     0,  -767,     0,
       0,     0,     0,     0,  -901,     0,     0,     0,     0,  -901,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -901,  -767,     0,
       0,     0,     0,  -767,     0,  -901,     0,   601,  -901,     0,
       0,     0,     0,     0,  -901,  -901,  -901,     0,     0,     0,
    -901,  1932,  -901,     0,  -901,  -901,  -901,  1943,  1277,     0,
       0,     0,     0,     0,  1052,     0,  1277,     0,     0,  -767,
     969,     0,     0,     0,     0,     0,     0,  1031,     0, -1478,
       0,     0,     0,   966,     0,  1538,     0,   603,     0,     0,
       0,     0,     0,     0,     0,     0,  -767,     0,   968,  -595,
     544,     0,  -635,     0,  -635,     0,     0,     0,     0,  -635,
       0,     0,  1943,     0,     0,     0,  1277,  -635,     0,     0,
    1053,     0,   972,     0,   605,   973,  -767,     0,     0,     0,
       0,     0,  -767,   607,     0,     0,  2044,     0,     0,     0,
    2044,  -767,  -767,     0,     0,     0,   608,     0,     0,     0,
    -635,  -635,     0,     0,     0,  2044,  2044,   974,  -635,     0,
       0,  -767,     0,     0,     0,     0,  -767,     0,     0,  -635,
       0,  -767,     0,  -635,     0,     0,     0,     0,     0,     0,
       0,     0,   969,     0,  -767,  -635,     0,     0, -1478,     0,
       0,     0,  -767,     0,     0,  -767,     0,     0,     0,     0,
       0,  -767,   612,   613,   614,     0,  2044,  -635,     0,  2044,
       0,     0,     0,     0,  -635,  -635,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   975,     0,     0,     0,     0,
       0,  -595,   998,     0,   972,  -595,  1943,   973,     0,     0,
       0,     0,     0,     0,     0,  -635,     0,     0,     0,     0,
       0,   616,   617,   618,     0,     0,     0,  -635,     0,     0,
       0,  -635,     0,     0,     0,     0,     0,     0,  1039,   974,
     976,   977,     0,     0,  -635,  2127,     0,     0,  -595,     0,
   -1550,  -635,     0,     0,  -635,  -635,     0,     0,     0,     0,
       0,     0,  -635,     0,  2044,   978,     0,     0,     0,  -635,
       0,  -635,     0,     0,  -635, -1009,     0,     0,   544,     0,
    -635,  2167,  -635,   979,     0,     0,     0,  -635, -1009,     0,
       0,   980,     0,   182,   284,  -635,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   975,     0,  -635,
       0,     0,     0,  -635,     0,  -635,     0,  2044,     0,     0,
       0,     0,  -635,     0,     0,     0,     0,     0,  -635,  -635,
       0,     0,     0,     0,     0,     0,  -635,     0,     0,     0,
       0,     0,     0,     0,  -635,     0,     0,  -635,     0,     0,
       0,  -635,   976,   977,     0,     0,     0,     0,     0,  -635,
       0,     0,     0,  -635,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -595,     0,     0,  1236,   978,     0,     0,
    -635,     0,     0,     0,     0,  -635,     0,     0,     0,  -635,
       0,  2219,  -635,  -635,  2221,   979,     0,     0,     0,     0,
     654,     0,  -635,   980,     0,     0,   284,  -635,     0,  -635,
       0,     0,     0,     0,     0,     0,     0,  -635,     0,     0,
       0,     0,     0,  -635,  2238,     0,     0,  -635,     0,     0,
       0,     0,     0,     0,     0,  -635,  -635,     0,  2044,  -635,
       0,     0,     0,  2044,     0,  -635,     0,  -635,  -635,     0,
       0,  -635,  -635,  -635,     0,     0,     0,     0,  -635,  -635,
       0,     0,  -635,  -635,     0,     0,     0,     0,     0,  1039,
    -635,   583,     0,  -635,     0,     0,     0,  -635,  -635,  -635,
    2271,     0,  -635,  -635,     0,     0,     0,     0,     0,     0,
       0,   584,     0,     0,  -635,     0,     0,     0,     0,     0,
       0,     0,     0,   545,   585,     0,  -635,   586,   587,   588,
     589,   590,   591,   592,     0,     0,  -635,  -635,     0,     0,
       0,  -635,     0,  -635,     0,     0,     0,  1236,     0,     0,
    -635,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   593,     0,   594,   595,   596,   597,   598,
     599,     0,  -635,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -635,     0,     0,
       0,     0,     0,     0,     0, -1466,     0,     0, -1466,     0,
       0,     0,     0,     0,     0,   600,  1221,     0,  -635,     0,
   -1466,     0,     0,     0,     0,     0,     0,  -635,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -635,     0,     0,     0,     0,  -635,     0,  -635,     0,     0,
       0,     0,     0,     0,     0,  -635,     0,     0,     0,     0,
       0,     0,     0,     0, -1496,  -635,     0,     0,     0,     0,
       0,     0,     0,     0,  -635,     0,     0,     0,     0,     0,
   -1466,     0,     0,  -635, -1496,  -635,  -635,     0,     0,  -635,
       0,  -635,     0,     0,     0, -1466,  -635,   601,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      40,  -635,     0,   602,     0,     0,  -635,     0,     0, -1531,
       0,  -635,     0,     0,   965,     0,     0,   821,     0,     0,
       0,     0,  -635,     0,     0,     0,     0,     0,     0,     0,
       0,   545,     0,     0,  -635,     0,     0,   603,     0,     0,
       0,     0, -1466, -1466,  -635,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   604,
       0,     0,     0,     0,     0,     0,     0,     0,     0, -1466,
   -1466,     0,     0,     0,   605,     0, -1466,     0,     0,     0,
   -1466,   606,     0,   607,     0,     0,     0,     0,     0,   966,
       0,     0,     0,     0,     0,     0,   608,     0,     0, -1466,
       0,     0,     0,     0,   968,     0,   609, -1466,     0,     0,
   -1466, -1466,     0,   610,     0, -1466,     0,     0,     0, -1466,
       0, -1466,     0,     0, -1466,     0, -1466,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0, -1466,
       0,     0,     0,     0, -1466,     0,     0,     0,     0,     0,
     611,     0,   612,   613,   614,     0, -1466,     0,     0,     0,
       0,  1409,  1410,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   615,     0,     0,   657,
       0,   658,     0,     0,     0,     0,   659,     0,   969,  1411,
       0,     0,     0, -1531,   660,  1412,     0, -1466,     0,   413,
       0,   616,   617,   618,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   619,     0,     0,   620,  1438,     0,
       0,     0,     0,     0, -1466,     0,  1414,   661,   662,   970,
    1415,     0,     0,     0,   971,   663,     0,  -333,   414,     0,
     972,     0,     0,   973,     0,   415,   664,     0,     0,     0,
     665,     0,     0,     0,     0,     0,     0,     0,  1439,     0,
   -1466,     0,   666,  1440,     0,     0,     0,     0,     0, -1466,
   -1466,     0,     0,     0,     0,   974,     0,     0,     0,     0,
       0,     0,     0,     0,   667,     0, -1466,     0,     0, -1466,
   -1466,   668,   669,     0, -1466,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0, -1466,     0,     0,     0,   416,     0,     0,     0,
   -1466,     0,   670, -1466,     0,     0,     0,     0,     0, -1466,
   -1466, -1466,     0,     0,   671, -1466,     0, -1466,   672, -1466,
   -1466, -1466,     0,   975,     0,     0,     0,     0,     0,     0,
       0,   673,     0,     0,     0,     0,     0,     0,   674,     0,
       0,   675,   676,     0,     0,     0,     0,     0,     0,   677,
       0,     0,     0,     0,     0,     0,   678,     0,   679,   417,
       0,   680,     0,     0,     0,     0,     0,     0,   976,   977,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   418,     0,
       0,     0,     0,   978,     0,     0,   681,     0,     0,     0,
     682,     0,   683,   965,     0,     0,   821,     0,   657,   684,
     658,   979,     0,     0,     0,   659,     0,     0,     0,   980,
       0,     0,   284,   660,     0,     0,     0,  1158,   419,  1441,
    1442,   685,     0,     0,  1443,     0,  1429,     0,  1444,  1431,
    1432,     0,     0,     0,     0,     0,   686,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   661,   662,     0,     0,
       0,     0, -1474,     0,   663,     0,     0,   687,     0,     0,
       0,     0,     0,     0,     0,   664,   688,     0,   966,   665,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   689,
       0,   666,     0,   968,   690,     0,   691,     0,     0,     0,
       0,     0,     0,     0,   692,     0,     0,     0,     0,     0,
       0,     0,     0,   667,   693,     0,     0,     0,     0,     0,
     668,   669,     0,   694,     0,     0,     0,     0,     0,     0,
       0,     0,   695,     0,   696,   697,     0,     0,   698,     0,
     699,     0,     0,     0,     0,   700,     0,     0,     0,     0,
       0,   670,     0,     0,     0,     0,     0,     0,     0,     0,
     701,     0,     0,   671,     0,   702,     0,   672,     0,     0,
     703,     0,     0,     0,     0,   965,     0,   969,   821,     0,
     673,   704,     0,     0,     0,     0,     0,   674,   413,     0,
     675,   676,     0,   705,     0,     0,     0,     0,   677,     0,
       0,     0,     0,   706,     0,   678,     0,   679,     0,     0,
     680,     0,     0,     0,     0,     0,     0,     0,   970,     0,
       0,     0,     0,   971, -1474,     0,     0,   414,     0,   972,
       0,     0,   973,   965,   415,     0,   821,     0,     0,     0,
       0,     0,     0,     0,     0,   681,     0,     0,     0,   682,
     966,   683,     0,     0,     0,     0,     0,     0,   684,     0,
       0,     0,     0,     0,   974,   968,   965,     0,     0,   821,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     685,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0, -1474,     0,     0,     0,   686,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   416,     0,     0,   966,     0,
       0,     0,     0,     0,     0,  1556,   687,     0,     0,     0,
       0,     0,     0,   968,     0,   688,     0,     0,     0,     0,
       0,     0,   975,     0,     0,     0,  1087,     0,   689,     0,
       0,   966,     0,   690,     0,   691,     0,     0,     0,   969,
       0,     0,   967,   692,     0,     0,   968,     0,     0,     0,
     413,     0,     0,   693,     0,     0,     0,     0,   417,     0,
       0,     0,   694,     0,     0,     0,     0,   976,   977,     0,
       0,   695,     0,   696,   697,     0,     0,   698,     0,   699,
     970,     0,     0,     0,   700,   971,     0,   418,     0,   414,
       0,   972,   978,     0,   973,     0,   415,   969,     0,   701,
       0,     0,     0,     0,   702,     0,     0,     0,   413,   703,
     979,     0,     0,     0,     0,     0,     0,     0,   980,     0,
     704,   284,     0,  1293,     0,     0,   974,   419,     0,     0,
     969,     0,   705,     0,   965,     0,     0,   821,   970,     0,
       0,   413,     0,   971,     0,     0,     0,   414,     0,   972,
       0,     0,   973,     0,   415,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   416,     0,     0,
       0,   970,     0,     0,     0,     0,   971,     0,     0,     0,
     414,     0,   972,     0,   974,   973,     0,   415,     0,     0,
       0,     0,     0,     0,   975,     0,     0,     0,     0,     0,
       0,   965,     0,     0,   821,     0,     0,     0,     0,   966,
       0,     0,     0,     0,     0,     0,     0,   974,     0,     0,
    1046,     0,     0,     0,   968,   416,     0,     0,     0,     0,
     417,     0,     0,     0,     0,     0,     0,     0,     0,   976,
     977,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   975,     0,     0,     0,  1557,     0,   416,   418,
    1558,     0,     0,     0,   978,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   966,     0,     0,     0,
       0,   965,   979,     0,   821,   975,     0,     0,   417,     0,
     980,   968,     0,   284,     0,     0,     0,   976,   977,   419,
       0,     0,     0,   965,  1087,     0,   821,     0,   969,     0,
       0,     0,     0,     0,     0,     0,     0,   418,     0,   413,
       0,   417,   978,     0,     0,     0,     0,     0,     0,     0,
     976,   977,     0,     0,     0,     0,     0,     0,     0,     0,
     979,     0,     0,     0,     0,     0,     0,     0,   980,   970,
     418,   284,     0,     0,   971,   978,   966,   419,   414,     0,
     972,     0,     0,   973,     0,   415,     0,  1091,     0,     0,
       0,   968,     0,   979,     0,   969,     0,     0,   966,     0,
       0,   980,   965,     0,   284,   821,   413,     0,     0,     0,
     419,     0,     0,   968,     0,   974,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   970,     0,     0,     0,
       0,   971,     0,     0,     0,   414,     0,   972,     0,     0,
     973,     0,   415,     0,     0,     0,   416,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   969,     0,   966,     0,     0,
       0,     0,   974,   975,     0,     0,   413,     0,     0,     0,
       0,     0,   968,     0,     0,     0,     0,   969,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   413,     0,
       0,     0,     0,     0,     0,     0,   970,     0,     0,   417,
       0,   971,     0,   416,     0,   414,     0,   972,   976,   977,
     973,     0,   415,     0,     0,     0,     0,     0,   970,     0,
       0,     0,     0,   971,     0,     0,     0,   414,   418,   972,
     975,     0,   973,   978,   415,     0,     0,     0,     0,     0,
     965,     0,   974,   821,     0,     0,     0,     0,     0,     0,
       0,   979,  1298,     0,     0,     0,   969,     0,     0,   980,
       0,     0,   284,     0,   974,     0,   417,   413,   419,     0,
       0,     0,     0,     0,     0,   976,   977,     0,     0,     0,
       0,     0,     0,   416,     0,     0,     0,     0,     0,   965,
       0,     0,   821,     0,     0,   418,     0,   970,     0,     0,
     978,     0,   971,     0,     0,   416,   414,     0,   972,     0,
     975,   973,     0,   415,     0,   966,     0,   965,   979,     0,
     821,     0,     0,     0,     0,     0,   980,     0,     0,   284,
     968,     0,   975,     0,     0,   419,     0,     0,     0,     0,
       0,     0,     0,   974,     0,     0,   417,     0,     0,     0,
       0,     0,     0,     0,     0,   976,   977,     0,     0,     0,
       0,     0,     0,     0,   966,     0,     0,     0,   417,     0,
       0,     0,     0,     0,     0,   418,     0,   976,   977,   968,
     978,     0,     0,     0,   416,     0,     0,     0,     0,     0,
       0,     0,   966,  1182,     0,     0,     0,   418,   979,     0,
       0,     0,   978,     0,     0,     0,   980,   968,     0,   284,
       0,   975,     0,     0,   969,   419,     0,     0,     0,     0,
     979,     0,     0,     0,     0,   413,     0,     0,   980,     0,
       0,   284,     0,     0,     0,     0,     0,   419,     0,     0,
       0,     0,     0,     0,     0,     0,   965,   417,     0,   821,
       0,     0,     0,     0,     0,   970,   976,   977,     0,     0,
     971,     0,     0,   969,   414,     0,   972,     0,     0,   973,
       0,   415,     0,     0,   413,     0,   418,     0,     0,     0,
       0,   978,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   969,     0,     0,     0,     0,     0,     0,     0,   979,
       0,   974,   413,     0,   970,     0,     0,   980,     0,   971,
     284,     0,     0,   414,     0,   972,   419,     0,   973,     0,
     415,   966,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   970,     0,     0,     0,   968,   971,     0,     0,
       0,   414,   416,   972,     0,     0,   973,     0,   415,     0,
     974,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   975,
       0,     0,     0,     0,     0,     0,     0,     0,   974,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   416,     0,     0,     0,     0,     0,     0,     0,  1565,
       0,     0,     0,     0,     0,   417,     0,     0,     0,     0,
       0,     0,     0,     0,   976,   977,     0,     0,   975,   416,
     969,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   413,     0,     0,   418,     0,     0,     0,     0,   978,
       0,     0,     0,     0,     0,     0,   975,     0,     0,  1697,
       0,     0,     0,     0,   417,     0,     0,   979,     0,     0,
       0,   970,     0,   976,   977,   980,   971,     0,   284,     0,
    1010,     0,   972,     0,   419,   973,     0,   415,     0,     0,
       0,     0,   417,   418,     0,     0,     0,     0,   978,     0,
       0,   976,   977,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   979,   974,     0,     0,
       0,   418,     0,     0,   980,     0,   978,   284,     0,     0,
       0,     0,     0,   419,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   979,     0,     0,     0,     0,     0,
       0,     0,   980,     0,     0,   284,     0,     0,   416,     0,
       0,   419,  1596,     0,  1597,     0,     0,  1598,   586,   587,
     588,   589,   590,   591,   592,  1599,  1600,  1601,     0,     0,
       0,     0,     0,     0,     0,   975,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1602,     0,     0,     0,
       0,     0,     0,     0,   593,     0,   594,   595,   596,   597,
     598,   599,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   417,     0,     0,     0,     0,     0,     0,     0,     0,
     976,   977,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   600,     0,     0,     0,
     418,     0,     0,     0,     0,   978,     0,     0,     0,     0,
     586,   587,   588,   589,   590,   591,   592,     0,     0,     0,
       0,     0,   966,   979,     0,     0,     0,     0,     0,     0,
       0,   980,     0,     0,   284,     0,  1603,   968,  2011,  2012,
     419,     0,     0,     0,     0,     0,   593,     0,   594,   595,
     596,   597,   598,   599,  1604,     0,     0,  1605,  1606,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1607,     0,     0,     0,     0,     0,     0,   601,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   600,     0,
       0,     0,     0,     0,   602,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1608,     0,
       0,     0,     0,     0,     0,     0,   966,  1609,     0,     0,
       0,   969,     0,     0,     0,     0,     0,     0,   603,     0,
       0,   968,   413,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1610,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2013,  1130,     0,  1611,   605,     0,   971,     0,     0,
     601,   414,   606,   972,   607,     0,   973,     0,   415,     0,
       0,     0,     0,     0,     0,     0,   602,   608,  1612,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2014,  2015,     0,     0,     0,     0,     0,     0,   974,     0,
       0,     0,  1613,     0,     0,   969,     0,  1614,     0,     0,
     603,     0,     0,     0,     0,  2016,   413,     0,     0,     0,
       0,  1615,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   611,   604,   612,   613,   614,     0,     0,     0,   416,
       0,     0,     0,   966,     0,     0,  1130,   605,     0,     0,
       0,   971,     0,     0,   606,   414,   607,   972,   968,  2017,
     973,     0,   415,     0,   966,     0,   975,  1616,     0,   608,
       0,     0,     0,     0,     0,     0,     0,     0,  1617,   968,
       0,     0,   616,   617,   618,     0,     0,     0,     0,     0,
       0,     0,   974,     0,     0,   619,     0,  1618,   620,     0,
       0,     0,   417,     0,     0,     0,     0,     0,     0,     0,
       0,   976,   977,     0,     0,     0,     0,     0,  1619,     0,
       0,     0,     0,   611,     0,   612,   613,   614,     0,     0,
       0,   418,  2018,   416,     0,     0,   978,     0,     0,     0,
       0,     0,   969,     0,     0,     0,  2019,     0,     0,     0,
       0,     0,     0,   413,   979,     0,     0,  1052,     0,     0,
     975,     0,   980,   969,     0,   284,     0,     0,     0,  2020,
       0,   419,  1131,  1132,   616,   617,   618,     0,     0,     0,
    1641,  1133,     0,  1130,     0,     0,     0,   619,   971,     0,
     620,  2021,   414,     0,   972,     0,   417,   973,     0,   415,
       0,     0,     0,     0,     0,   976,   977,     0,     0,     0,
    2022,     0,     0,   998,     0,   972,     0,     0,   973,     0,
       0,     0,     0,     0,     0,   418,     0,     0,     0,   974,
     978,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   979,     0,
     974,     0,     0,     0,     0,     0,   980,     0,     0,   284,
       0,     0,     0,     0,     0,   419,  1131,  1132,     0,     0,
     416,     0,     0,     0,  1875,  1133,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   975,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   975,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   417,     0,     0,     0,     0,     0,     0,
       0,     0,   976,   977,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   418,   976,   977,     0,     0,   978,     0,     0,
       0,     0,     0, -1550,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   979,     0,     0,   978,     0,
       0,     0,     0,   980,     0,     0,   284,     0, -1009,     0,
       0,     0,   419,  1131,  1132,     0,   979,     0,     0,     0,
       0, -1009,  1133,     0,   980,     0,   182,   284
};

static const yytype_int16 yycheck[] =
{
      83,   168,   389,   221,   130,   388,   640,   620,   675,   499,
     885,   849,  1009,   823,   431,  1259,  1189,  1081,  1189,  1189,
     609,   188,   189,  1189,  1189,   245,   193,   194,   195,   196,
     197,  1087,   199,   846,   201,   582,   704,   844,  1683,   221,
     646,   843,  1222,   787,  1101,  1327,  1327,   454,   855,  1327,
     852,   853,   270,  1327,  1182,  1071,   274,    13,   276,   185,
    1213,  1214,  1215,  1369,  1370,   867,   868,   285,   235,   152,
     237,  1327,   562,  1002,  1327,  1029,   350,   244,     6,   881,
     882,    23,   845,  1037,    17,   252,     9,    56,   270,     6,
      69,  1219,   274,    54,   276,  1159,     6,     9,    17,   266,
     267,   863,   269,   285,     6,     6,    94,    85,   275,   329,
      48,    22,  1263,    28,   876,    71,   336,    56,    69,    49,
     111,   115,  1250,   341,     9,  1834,     9,    72,   774,  1083,
     980,    87,    56,   351,   178,    30,   118,     9,   146,     9,
     358,   308,  1158,    69,   311,   312,   420,   314,    62,    69,
     368,   210,   120,    48,   167,   965,   168,     9,   210,   341,
     970,    49,   214,   330,   230,   385,    69,    65,   165,   351,
    1298,   389,   392,   391,  1819,   190,   358,    69,    22,   230,
     347,   983,   816,   198,    56,   405,  1353,    94,  1245,  1118,
      23,   118,    21,  1360,     9,   318,   104,   112,    50,    60,
    1367,   582,   217,   183,   119,   242,   289,   389,    32,   429,
    1012,   485,  1360,   293,   434,   115,   118,   179,  1028,  1367,
     387,  1237,   262,   196,    65,   230,    87,    88,   395,   447,
     398,   865,   203,    49,   168,    84,   230,   147,  1065,   230,
     647,   937,   115,   790,  1046,   120,  1121,  1303,    49,   264,
     265,   168,    31,   230,   361,   230,    69,   272,   273,    39,
     219,   209,   234,   278,   279,   447,   486,    11,   210,    85,
     365,  1328,  1400,    49,   196,   442,   171,   176,   207,     0,
     500,   395,   254,  1299,    49,   447,  1088,   370,    91,   164,
     373,  1093,  1349,   460,   461,   303,  1602,   971,   170,   119,
     230,   230,  1608,   410,   427,   278,   191,  1463,   942,   955,
     956,   259,   532,   926,  1494,   410,   536,  1079,   230,  1472,
    1130,   191,   996,   541,   542,  1481,    70,  1281,   107,   496,
     230,   230,   242,  1153,   245,   242,   450,   161,  1267,   191,
     318,   309,   304,  1359,  1182,   230,   361,   219,   270,   210,
     347,   957,   237,   433,   334,   522,   524,   230,   273,   396,
     230,   210,   529,   952,   953,   342,   114,   237,   434,   221,
     315,   254,   165,  1529,   353,  1071,   502,   210,   230,   230,
    1182,  1219,   434,   434,   604,   237,   227,  1189,   447,   357,
     314,   298,   610,   433,   561,  1202,   294,  2106,  1454,   566,
     846,   245,   569,   447,   571,   206,  1470,   574,   575,   790,
     219,   578,  1250,  1569,   238,   230,  1218,  1219,  1778,   865,
    1227,   434,   434,   308,   870,   286,   434,   353,   311,   434,
     318,  1582,   343,   353,   416,  1131,  1132,  1133,   308,  1266,
     434,  1498,   356,   434,   403,  1141,   434,  1401,  1250,   427,
     353,   230,   619,   294,   399,   426,   308,   396,   409,   434,
    1298,   353,  1158,   243,   402,   426,   435,  1163,  1231,  1165,
     449,  1167,   937,  1169,   393,  1171,  1172,  1173,  1174,  1175,
    1176,  1177,  1178,  1285,  1651,  1247,   371,  1289,  1290,   416,
    1292,   937,   434,   230,   396,   396,  1298,   430,  1261,   343,
     434,   371,   318,  1651,   434,  1521,   434,   402,  1154,   465,
     440,   434,  1146,   136,   416,   400,   433,   434,   433,   371,
     646,   324,   434,   449,   434,   433,   434,   434,  1348,   449,
     400,   403,   434,   434,   434,  1532,   447,  1553,   433,   427,
     353,  1237,   318,    37,  1700,  1308,   449,   821,   400,   434,
     298,   958,   119,   318,   347,   440,   774,   449,   334,   777,
     778,   434,  1400,  1845,  1845,  1809,   784,  1845,   397,   334,
     440,  1845,   401,  1162,  1528,  1755,   315,  1124,   272,   428,
    1169,  1325,  1942,   434,   387,  1945,   447,   136,   440,  1845,
      30,   183,  1845,  2238,   403,   777,   778,   764,   183,   766,
     183,    69,   784,  1299,   172,   398,   183,   262,   183,  1055,
      28,   427,   183,   433,   434,   447,   110,    12,   838,   786,
      15,    16,  1066,   361,  1752,    65,  1754,   845,   441,   442,
     443,   444,   227,   446,  1330,   163,   449,   232,   220,   117,
    1229,  1337,  1338,  1339,  1340,  1341,  1342,  1343,   866,    27,
     241,   427,   870,  1709,   872,   153,   874,   875,  1102,   877,
     399,  1789,   427,  1359,   123,  1271,  1131,  1132,  1133,  1275,
     147,   447,   410,   447,   892,   203,  1141,    69,   433,   373,
     954,   304,   447,   211,  1495,  1131,  1132,  1133,   906,  1452,
    1501,   909,   447,  1821,   112,  1141,   281,   434,  1163,   294,
    1165,   292,  1167,   440,   922,  2011,  1171,  1172,  1173,  1174,
    1175,  1176,  1177,  1178,  1991,   935,  1993,  1163,  1874,  1165,
     214,  1167,   940,  1169,   906,  1171,  1172,  1173,  1174,  1175,
    1176,  1177,  1178,  2093,   194,    99,   176,   955,   956,   293,
     922,  1330,  1409,   191,   870,  1674,  1675,  1676,  1702,   341,
     234,   334,  1768,   281,   322,   304,   923,   339,  1560,  1912,
    1913,  1914,  1915,   418,   341,  1527,   341,   850,   937,  1925,
     341,  1927,    89,    90,   234,  1832,    62,     9,   433,   277,
      12,   376,   230,    15,    16,   160,  1375,   227,   871,   237,
     873,   230,  1605,  1461,   254,   878,   113,   256,   153,  1955,
     234,  1857,   369,   242,   887,    30,  1979,  1822,  1979,  1979,
    1826,  1867,  1868,  1979,  1979,    24,   272,   252,   239,   234,
     254,     8,   307,     1,   230,  1521,  1522,   312,   194,   195,
    1986,  1987,  1682,  1787,   447,  1502,   239,  1687,  1688,   254,
     361,  1691,  1692,  1693,  1511,  1695,  1696,   286,    35,  1067,
     441,   442,   247,   248,   294,  2132,   340,  1553,    25,    26,
     308,   361,   297,   357,  1920,  1921,   433,   434,   234,    47,
     265,   266,  1337,  1338,  1339,  1340,  1341,  1342,  1343,   433,
     434,   448,   303,    61,  1330,   353,   901,    82,   254,   410,
     230,  1337,  1338,  1339,  1340,  1341,  1342,  1343,   123,    66,
     303,    68,   239,  1123,   191,   164,   434,   282,   241,   365,
     410,  1037,  1723,  1724,  1752,   198,  1754,   126,     8,  2163,
    1003,    99,   277,   371,     1,   184,   434,     4,   117,  1055,
     351,  1946,   172,   100,   101,   102,  1154,   234,  1749,   447,
    2004,    11,    19,   230,   227,    35,  1113,  1758,   351,  1756,
     237,  1789,    29,   239,   410,    25,    26,   254,     9,   292,
     104,   353,  1131,  1132,  1133,   305,   303,  1556,   349,   429,
     287,   288,  1141,   441,   442,   443,   444,  1644,   446,   300,
     147,   449,   149,  1821,     9,    62,   164,    57,  1684,   447,
     157,   245,   440,  1689,  1796,   434,  1165,   369,  1995,   433,
    1807,   440,  1171,  1172,  1173,  1174,   184,   247,  1177,  1178,
     447,   328,   329,  1231,   351,   247,   248,   303,   433,   434,
     317,   308,  2266,   121,    94,    95,   447,    97,   172,   312,
      81,    56,   210,   265,   266,   105,   319,   215,  2194,  2195,
     184,   349,   123,  1261,   447,    96,   163,   225,   447,   441,
     442,   443,   444,  1850,   446,   361,   268,   449,   312,   191,
     314,   228,   434,   429,  1868,   351,   184,   433,  1865,  1866,
     356,  1197,  1768,  1547,   357,   242,   448,  1888,   148,   149,
    1776,   397,   852,   151,   371,   401,   203,   415,  1562,   159,
    1308,   447,   210,   191,   211,   164,  1907,  1899,   230,  2096,
     428,  1319,  1320,  1978,   410,   237,   234,  1524,   441,   442,
     447,   408,   882,  1924,  2263,   184,  1920,  1921,   330,  1916,
     230,   198,  1919,   234,     6,  1208,   254,     9,   209,   180,
    1826,  2280,   230,  1767,   312,   313,   433,  1319,  1320,   237,
     191,   209,   252,   254,  1270,   170,   447,   325,   434,   327,
     227,   249,   166,   440,  1965,  1966,   117,   234,   370,  1605,
     372,   231,   874,  1974,   281,   312,   191,   304,  1337,  1338,
    1339,  1340,  1341,  1342,  1343,   256,   308,   132,   259,   230,
     892,   232,   292,  1309,   235,   312,   237,   314,  1822,   257,
     204,   259,  1387,   156,   219,  1390,   490,   160,   212,    81,
    1395,   495,   279,   289,   290,   230,  2203,  2004,   285,  2019,
     308,     9,   237,   271,    96,   273,   267,   303,   397,  1684,
     367,   368,   401,   303,  1689,     2,  1893,   394,  1895,     6,
     443,   444,   158,   446,  1452,   312,   162,   447,  1684,   371,
     227,   228,   319,  1689,  2082,   312,  2084,   314,   430,   427,
     432,  2062,   150,   349,   152,   332,   436,   308,    56,  2070,
    2057,   166,   258,   349,   260,   263,   264,   434,   400,   447,
     150,   153,   152,   371,  2085,   345,   374,   375,   447,   356,
     357,   233,   359,   308,   335,   349,   441,   442,   443,   444,
     367,   446,    31,   312,    33,   314,  1786,    36,   180,   434,
     377,  2103,  2113,   334,  2115,   447,  1163,    46,   440,   191,
    1167,  2122,  1946,   263,   264,   385,   227,   228,  1175,  1176,
     371,   398,   419,   420,   421,   422,   447,   447,   447,   380,
     381,  2142,  2143,   447,  2209,   441,   442,   443,   444,   221,
     446,   352,   440,   447,   226,   212,   371,   453,   230,   400,
     232,    71,   398,   235,   405,   237,   441,   442,   443,   444,
     447,   446,   434,   349,   434,   229,  1584,   178,   453,  1859,
     447,   434,   423,  1593,   447,   400,   447,   447,   403,   276,
     431,  2178,   447,   434,   273,   267,  2183,   388,    24,   440,
    1610,   447,   349,   191,  1561,  2197,   325,  2064,  2200,  2066,
     365,   210,  1584,   447,   104,  1531,   434,  2218,   377,   434,
    1628,   441,   442,   443,   444,   440,   446,   360,    56,   449,
      84,   219,  1589,   172,   434,   447,   308,   349,  1646,   344,
    1597,   434,   230,   365,   173,   276,   106,  1604,   177,   237,
     230,  1567,   419,   420,   421,   422,  1628,  2249,  1574,   356,
     207,   190,   447,   335,   243,   191,    11,    67,   447,   153,
     154,   349,   842,   447,  1646,   243,   846,    23,  1686,   270,
      25,    26,   852,   419,   420,   421,   422,   857,   858,   447,
     434,  2283,   230,   863,   864,   865,   294,   181,  1655,   371,
     870,  1658,    83,   187,   230,    83,   876,   236,   380,   381,
     447,   237,    57,   447,  1686,   885,   886,   434,   888,   428,
     308,   441,   442,   443,   444,  1684,   446,   434,   400,   449,
    1689,   393,   310,   405,   218,   396,   228,   196,   222,   441,
     442,   443,   444,   434,   446,   396,   312,   449,   357,    94,
      95,   423,    97,    55,   283,   377,   433,  2160,    27,   431,
     105,   184,   434,   365,  2188,   447,   349,   937,   440,   377,
     214,   447,   357,   221,   434,  1732,   448,   430,   307,   339,
     210,  1738,   308,   371,    81,   441,   442,   443,   444,   106,
     446,   230,   398,   449,   299,    37,   274,   967,   374,    96,
     280,   440,   331,   148,   149,   450,   396,   336,   441,   442,
     443,   444,   400,   446,   159,   403,   449,   346,   393,   355,
      27,   350,   454,  1780,   270,    33,   447,   171,    36,   447,
     434,  1841,  1002,   398,   230,   133,    44,    45,    46,   104,
      17,   433,  2015,   169,   184,   371,   434,   395,   441,   442,
     443,   444,   440,   446,   450,   230,   449,    30,   393,  1029,
    1728,  1729,  1730,  1731,   124,   201,   450,  1037,  1038,   450,
     125,    56,   396,   450,   400,  1791,   450,   450,   407,   450,
     450,  1797,   426,   180,   127,  1055,   231,   450,   417,   450,
    1847,   450,   450,   312,   191,  1852,   341,   129,    98,   130,
     396,  1071,    49,   392,   134,   390,   135,   395,   434,  1079,
     393,   428,   176,  1083,   440,   140,   395,   242,  1791,    49,
     143,  1091,   176,   109,  1094,   326,   373,   111,   111,   433,
     396,   434,   183,   230,   302,   232,   334,   230,   235,   160,
     237,   131,   168,   430,  1952,   396,   359,   155,  1118,   206,
      49,  1121,   214,   396,   176,   119,   206,   273,   439,   358,
     446,  1131,  1132,  1133,   448,   173,   438,   451,   452,   189,
     267,  1141,   263,   214,   227,   449,   449,   334,   449,   449,
    1952,   391,   190,   366,   396,   128,   259,   262,  1158,   183,
     258,   393,   324,  1163,    49,  1165,   135,  1167,     8,   396,
     345,  1171,  1172,  1173,  1174,  1175,  1176,  1177,  1178,   176,
    2187,   308,   430,   123,   430,     9,   396,   300,   170,   301,
     198,   261,   322,   337,   122,   107,    49,   172,   236,  2039,
     278,   138,   427,   427,   139,    12,    13,    14,   335,   256,
     385,   234,   255,    20,   141,   282,   293,   110,   387,   277,
    2007,     7,   113,   216,    66,   397,   126,   153,   153,   133,
     321,  2018,   321,  2020,    99,    49,   234,  1237,   214,   142,
     145,   260,    93,    90,   371,   283,   257,  1247,   199,   217,
     188,    58,   430,   380,   381,   434,    49,   383,   399,   434,
    1260,  2099,   337,   234,  2051,  2052,   300,  1267,   234,   144,
     171,   300,   415,   400,  1274,   137,   286,   176,   405,    49,
       6,  1281,    21,   185,    53,   130,   335,   170,   180,   203,
     481,  1282,   555,  1293,  1105,  1103,   423,   134,   336,  1299,
     420,   912,  1313,  1320,   431,  1305,   567,   434,   346,   219,
    2150,  1837,  1790,   440,   108,     1,   370,   226,  2105,    48,
       6,   152,  1322,     9,   837,   542,   815,  2165,  1845,   301,
    2170,  2171,  1630,  2185,   942,   925,   526,  1337,  1338,  1339,
    1340,  1341,  1342,  1343,  2034,  2171,   153,   154,   790,  2187,
     122,  1711,   463,  1794,  1012,  1670,  1372,  1371,  1017,  1359,
    1709,  1745,  1227,  2165,  2151,  2152,  1224,  1494,  2155,   407,
    1936,  1234,  1755,  1240,   181,  2162,  1519,  1795,  1776,  1379,
     187,  1055,  1543,  1275,  1309,  2187,  1811,  1648,  1574,   877,
    2230,  2231,  1088,  1079,  2234,    81,  2236,  1077,  1574,  1989,
    1994,  1401,  2106,   210,  2000,  1802,  1468,  1067,  1191,  1556,
      96,   218,   938,   233,  2201,   222,  1584,  1187,  2256,  1245,
     310,   820,  1020,   576,   947,  2263,  2189,    56,   781,  1853,
    1415,  1144,    -1,    -1,  2274,    -1,    -1,    -1,  2141,    -1,
      -1,    -1,  2280,   250,   251,  2232,    -1,    -1,   255,    -1,
      -1,    -1,    -1,    -1,  2256,  1455,  1456,    -1,   265,    -1,
      -1,    -1,    -1,    -1,    -1,   272,    -1,   153,   154,    -1,
     277,    -1,    -1,    -1,    -1,    -1,    -1,     6,  2265,    -1,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   295,    -1,
      -1,    -1,    -1,    -1,   180,   181,    -1,    -1,    -1,  2202,
      -1,   187,    -1,    -1,    -1,   191,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      49,  1521,  1522,    -1,   210,    -1,    -1,  1527,  1528,    -1,
      -1,    -1,   218,    -1,    -1,   221,   222,    -1,    -1,    -1,
     226,    -1,    -1,    -1,   230,  1545,   232,    -1,    -1,   235,
      -1,   237,    81,  1553,    -1,    -1,    85,    -1,    -1,    -1,
      -1,  2264,    -1,    -1,   250,    -1,    -1,    96,  1568,   255,
      -1,    -1,    -1,  1573,  1574,    -1,    -1,    -1,    -1,    -1,
      -1,   267,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1605,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1616,    -1,  1618,    -1,
      -1,    -1,   308,    73,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,   440,   441,   442,   443,   444,    -1,   446,
      -1,   448,   449,    -1,   451,   452,    -1,    -1,    -1,   335,
      -1,   180,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   191,    -1,    -1,   115,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1674,  1675,  1676,    -1,    -1,    -1,
      -1,    81,    -1,    -1,  1684,   371,    -1,    -1,    -1,  1689,
      -1,    -1,   221,    -1,   380,   381,    96,   226,    -1,    -1,
      -1,   230,  1702,   232,    -1,    -1,   235,    -1,   237,    -1,
      -1,    -1,    -1,    -1,   400,    -1,    -1,    -1,    -1,   405,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   423,   267,    -1,
      -1,    -1,    -1,   272,    -1,   431,    -1,   197,   434,    -1,
      -1,    -1,    -1,    -1,   440,   441,   442,    -1,    -1,    -1,
     446,  1761,   448,    -1,   450,   451,   452,  1767,  1768,    -1,
      -1,    -1,    -1,    -1,   174,    -1,  1776,    -1,    -1,   308,
     180,    -1,    -1,    -1,    -1,    -1,    -1,  1787,    -1,   318,
      -1,    -1,    -1,    81,    -1,  1795,    -1,   247,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   335,    -1,    96,     0,
       1,    -1,     3,    -1,     5,    -1,    -1,    -1,    -1,    10,
      -1,    -1,  1822,    -1,    -1,    -1,  1826,    18,    -1,    -1,
     230,    -1,   232,    -1,   284,   235,   365,    -1,    -1,    -1,
      -1,    -1,   371,   293,    -1,    -1,  1846,    -1,    -1,    -1,
    1850,   380,   381,    -1,    -1,    -1,   306,    -1,    -1,    -1,
      51,    52,    -1,    -1,    -1,  1865,  1866,   267,    59,    -1,
      -1,   400,    -1,    -1,    -1,    -1,   405,    -1,    -1,    70,
      -1,   410,    -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   180,    -1,   423,    86,    -1,    -1,   427,    -1,
      -1,    -1,   431,    -1,    -1,   434,    -1,    -1,    -1,    -1,
      -1,   440,   362,   363,   364,    -1,  1916,   108,    -1,  1919,
      -1,    -1,    -1,    -1,   115,   116,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   335,    -1,    -1,    -1,    -1,
      -1,   132,   230,    -1,   232,   136,  1946,   235,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   146,    -1,    -1,    -1,    -1,
      -1,   411,   412,   413,    -1,    -1,    -1,   158,    -1,    -1,
      -1,   162,    -1,    -1,    -1,    -1,    -1,    -1,  1978,   267,
     380,   381,    -1,    -1,   175,  1985,    -1,    -1,   179,    -1,
     390,   182,    -1,    -1,   185,   186,    -1,    -1,    -1,    -1,
      -1,    -1,   193,    -1,  2004,   405,    -1,    -1,    -1,   200,
      -1,   202,    -1,    -1,   205,   415,    -1,    -1,     1,    -1,
       3,  2021,     5,   423,    -1,    -1,    -1,    10,   428,    -1,
      -1,   431,    -1,   433,   434,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   335,    -1,   240,
      -1,    -1,    -1,   244,    -1,   246,    -1,  2057,    -1,    -1,
      -1,    -1,   253,    -1,    -1,    -1,    -1,    -1,    51,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   275,    -1,    -1,    70,    -1,    -1,
      -1,    74,   380,   381,    -1,    -1,    -1,    -1,    -1,   290,
      -1,    -1,    -1,    86,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   304,    -1,    -1,  2116,   405,    -1,    -1,
     311,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,   320,
      -1,  2131,   115,   116,  2134,   423,    -1,    -1,    -1,    -1,
     123,    -1,   333,   431,    -1,    -1,   434,   338,    -1,   340,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   348,    -1,    -1,
      -1,    -1,    -1,   146,  2164,    -1,    -1,   358,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   158,   367,    -1,  2178,   162,
      -1,    -1,    -1,  2183,    -1,   376,    -1,   378,   379,    -1,
      -1,   382,   175,   384,    -1,    -1,    -1,    -1,   389,   182,
      -1,    -1,   185,   186,    -1,    -1,    -1,    -1,    -1,  2209,
     193,     1,    -1,   404,    -1,    -1,    -1,   200,   409,   202,
    2220,    -1,   205,   414,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    -1,   425,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   434,    34,    -1,   437,    37,    38,    39,
      40,    41,    42,    43,    -1,    -1,   447,   240,    -1,    -1,
      -1,   244,    -1,   246,    -1,    -1,    -1,  2267,    -1,    -1,
     253,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    -1,    75,    76,    77,    78,    79,
      80,    -1,   275,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   290,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     6,    -1,    -1,     9,    -1,
      -1,    -1,    -1,    -1,    -1,   115,    17,    -1,   311,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,   320,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     333,    -1,    -1,    -1,    -1,   338,    -1,   340,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   348,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   164,   358,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   367,    -1,    -1,    -1,    -1,    -1,
      81,    -1,    -1,   376,   184,   378,   379,    -1,    -1,   382,
      -1,   384,    -1,    -1,    -1,    96,   389,   197,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     210,   404,    -1,   213,    -1,    -1,   409,    -1,    -1,   219,
      -1,   414,    -1,    -1,     6,    -1,    -1,     9,    -1,    -1,
      -1,    -1,   425,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   434,    -1,    -1,   437,    -1,    -1,   247,    -1,    -1,
      -1,    -1,   153,   154,   447,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   269,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   180,
     181,    -1,    -1,    -1,   284,    -1,   187,    -1,    -1,    -1,
     191,   291,    -1,   293,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    -1,    -1,    -1,   306,    -1,    -1,   210,
      -1,    -1,    -1,    -1,    96,    -1,   316,   218,    -1,    -1,
     221,   222,    -1,   323,    -1,   226,    -1,    -1,    -1,   230,
      -1,   232,    -1,    -1,   235,    -1,   237,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   250,
      -1,    -1,    -1,    -1,   255,    -1,    -1,    -1,    -1,    -1,
     360,    -1,   362,   363,   364,    -1,   267,    -1,    -1,    -1,
      -1,   153,   154,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   386,    -1,    -1,     3,
      -1,     5,    -1,    -1,    -1,    -1,    10,    -1,   180,   181,
      -1,    -1,    -1,   403,    18,   187,    -1,   308,    -1,   191,
      -1,   411,   412,   413,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   424,    -1,    -1,   427,   210,    -1,
      -1,    -1,    -1,    -1,   335,    -1,   218,    51,    52,   221,
     222,    -1,    -1,    -1,   226,    59,    -1,   447,   230,    -1,
     232,    -1,    -1,   235,    -1,   237,    70,    -1,    -1,    -1,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   250,    -1,
     371,    -1,    86,   255,    -1,    -1,    -1,    -1,    -1,   380,
     381,    -1,    -1,    -1,    -1,   267,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   108,    -1,   397,    -1,    -1,   400,
     401,   115,   116,    -1,   405,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   423,    -1,    -1,    -1,   308,    -1,    -1,    -1,
     431,    -1,   146,   434,    -1,    -1,    -1,    -1,    -1,   440,
     441,   442,    -1,    -1,   158,   446,    -1,   448,   162,   450,
     451,   452,    -1,   335,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   175,    -1,    -1,    -1,    -1,    -1,    -1,   182,    -1,
      -1,   185,   186,    -1,    -1,    -1,    -1,    -1,    -1,   193,
      -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,   202,   371,
      -1,   205,    -1,    -1,    -1,    -1,    -1,    -1,   380,   381,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   400,    -1,
      -1,    -1,    -1,   405,    -1,    -1,   240,    -1,    -1,    -1,
     244,    -1,   246,     6,    -1,    -1,     9,    -1,     3,   253,
       5,   423,    -1,    -1,    -1,    10,    -1,    -1,    -1,   431,
      -1,    -1,   434,    18,    -1,    -1,    -1,    30,   440,   441,
     442,   275,    -1,    -1,   446,    -1,   448,    -1,   450,   451,
     452,    -1,    -1,    -1,    -1,    -1,   290,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,
      -1,    -1,    65,    -1,    59,    -1,    -1,   311,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,   320,    -1,    81,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   333,
      -1,    86,    -1,    96,   338,    -1,   340,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   348,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   108,   358,    -1,    -1,    -1,    -1,    -1,
     115,   116,    -1,   367,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   376,    -1,   378,   379,    -1,    -1,   382,    -1,
     384,    -1,    -1,    -1,    -1,   389,    -1,    -1,    -1,    -1,
      -1,   146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     404,    -1,    -1,   158,    -1,   409,    -1,   162,    -1,    -1,
     414,    -1,    -1,    -1,    -1,     6,    -1,   180,     9,    -1,
     175,   425,    -1,    -1,    -1,    -1,    -1,   182,   191,    -1,
     185,   186,    -1,   437,    -1,    -1,    -1,    -1,   193,    -1,
      -1,    -1,    -1,   447,    -1,   200,    -1,   202,    -1,    -1,
     205,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   221,    -1,
      -1,    -1,    -1,   226,   227,    -1,    -1,   230,    -1,   232,
      -1,    -1,   235,     6,   237,    -1,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   240,    -1,    -1,    -1,   244,
      81,   246,    -1,    -1,    -1,    -1,    -1,    -1,   253,    -1,
      -1,    -1,    -1,    -1,   267,    96,     6,    -1,    -1,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     275,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   294,    -1,    -1,    -1,   290,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   308,    -1,    -1,    81,    -1,
      -1,    -1,    -1,    -1,    -1,   146,   311,    -1,    -1,    -1,
      -1,    -1,    -1,    96,    -1,   320,    -1,    -1,    -1,    -1,
      -1,    -1,   335,    -1,    -1,    -1,   109,    -1,   333,    -1,
      -1,    81,    -1,   338,    -1,   340,    -1,    -1,    -1,   180,
      -1,    -1,    92,   348,    -1,    -1,    96,    -1,    -1,    -1,
     191,    -1,    -1,   358,    -1,    -1,    -1,    -1,   371,    -1,
      -1,    -1,   367,    -1,    -1,    -1,    -1,   380,   381,    -1,
      -1,   376,    -1,   378,   379,    -1,    -1,   382,    -1,   384,
     221,    -1,    -1,    -1,   389,   226,    -1,   400,    -1,   230,
      -1,   232,   405,    -1,   235,    -1,   237,   180,    -1,   404,
      -1,    -1,    -1,    -1,   409,    -1,    -1,    -1,   191,   414,
     423,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   431,    -1,
     425,   434,    -1,   206,    -1,    -1,   267,   440,    -1,    -1,
     180,    -1,   437,    -1,     6,    -1,    -1,     9,   221,    -1,
      -1,   191,    -1,   226,    -1,    -1,    -1,   230,    -1,   232,
      -1,    -1,   235,    -1,   237,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   308,    -1,    -1,
      -1,   221,    -1,    -1,    -1,    -1,   226,    -1,    -1,    -1,
     230,    -1,   232,    -1,   267,   235,    -1,   237,    -1,    -1,
      -1,    -1,    -1,    -1,   335,    -1,    -1,    -1,    -1,    -1,
      -1,     6,    -1,    -1,     9,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   267,    -1,    -1,
      92,    -1,    -1,    -1,    96,   308,    -1,    -1,    -1,    -1,
     371,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   380,
     381,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   335,    -1,    -1,    -1,   397,    -1,   308,   400,
     401,    -1,    -1,    -1,   405,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      -1,     6,   423,    -1,     9,   335,    -1,    -1,   371,    -1,
     431,    96,    -1,   434,    -1,    -1,    -1,   380,   381,   440,
      -1,    -1,    -1,     6,   109,    -1,     9,    -1,   180,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   400,    -1,   191,
      -1,   371,   405,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     380,   381,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     423,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   431,   221,
     400,   434,    -1,    -1,   226,   405,    81,   440,   230,    -1,
     232,    -1,    -1,   235,    -1,   237,    -1,    92,    -1,    -1,
      -1,    96,    -1,   423,    -1,   180,    -1,    -1,    81,    -1,
      -1,   431,     6,    -1,   434,     9,   191,    -1,    -1,    -1,
     440,    -1,    -1,    96,    -1,   267,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   221,    -1,    -1,    -1,
      -1,   226,    -1,    -1,    -1,   230,    -1,   232,    -1,    -1,
     235,    -1,   237,    -1,    -1,    -1,   308,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   180,    -1,    81,    -1,    -1,
      -1,    -1,   267,   335,    -1,    -1,   191,    -1,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    -1,    -1,   180,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   191,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   221,    -1,    -1,   371,
      -1,   226,    -1,   308,    -1,   230,    -1,   232,   380,   381,
     235,    -1,   237,    -1,    -1,    -1,    -1,    -1,   221,    -1,
      -1,    -1,    -1,   226,    -1,    -1,    -1,   230,   400,   232,
     335,    -1,   235,   405,   237,    -1,    -1,    -1,    -1,    -1,
       6,    -1,   267,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   423,   176,    -1,    -1,    -1,   180,    -1,    -1,   431,
      -1,    -1,   434,    -1,   267,    -1,   371,   191,   440,    -1,
      -1,    -1,    -1,    -1,    -1,   380,   381,    -1,    -1,    -1,
      -1,    -1,    -1,   308,    -1,    -1,    -1,    -1,    -1,     6,
      -1,    -1,     9,    -1,    -1,   400,    -1,   221,    -1,    -1,
     405,    -1,   226,    -1,    -1,   308,   230,    -1,   232,    -1,
     335,   235,    -1,   237,    -1,    81,    -1,     6,   423,    -1,
       9,    -1,    -1,    -1,    -1,    -1,   431,    -1,    -1,   434,
      96,    -1,   335,    -1,    -1,   440,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   267,    -1,    -1,   371,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   380,   381,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,   371,    -1,
      -1,    -1,    -1,    -1,    -1,   400,    -1,   380,   381,    96,
     405,    -1,    -1,    -1,   308,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,   396,    -1,    -1,    -1,   400,   423,    -1,
      -1,    -1,   405,    -1,    -1,    -1,   431,    96,    -1,   434,
      -1,   335,    -1,    -1,   180,   440,    -1,    -1,    -1,    -1,
     423,    -1,    -1,    -1,    -1,   191,    -1,    -1,   431,    -1,
      -1,   434,    -1,    -1,    -1,    -1,    -1,   440,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     6,   371,    -1,     9,
      -1,    -1,    -1,    -1,    -1,   221,   380,   381,    -1,    -1,
     226,    -1,    -1,   180,   230,    -1,   232,    -1,    -1,   235,
      -1,   237,    -1,    -1,   191,    -1,   400,    -1,    -1,    -1,
      -1,   405,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   180,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   423,
      -1,   267,   191,    -1,   221,    -1,    -1,   431,    -1,   226,
     434,    -1,    -1,   230,    -1,   232,   440,    -1,   235,    -1,
     237,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   221,    -1,    -1,    -1,    96,   226,    -1,    -1,
      -1,   230,   308,   232,    -1,    -1,   235,    -1,   237,    -1,
     267,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   335,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   267,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   308,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   365,
      -1,    -1,    -1,    -1,    -1,   371,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   380,   381,    -1,    -1,   335,   308,
     180,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   191,    -1,    -1,   400,    -1,    -1,    -1,    -1,   405,
      -1,    -1,    -1,    -1,    -1,    -1,   335,    -1,    -1,   366,
      -1,    -1,    -1,    -1,   371,    -1,    -1,   423,    -1,    -1,
      -1,   221,    -1,   380,   381,   431,   226,    -1,   434,    -1,
     230,    -1,   232,    -1,   440,   235,    -1,   237,    -1,    -1,
      -1,    -1,   371,   400,    -1,    -1,    -1,    -1,   405,    -1,
      -1,   380,   381,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   423,   267,    -1,    -1,
      -1,   400,    -1,    -1,   431,    -1,   405,   434,    -1,    -1,
      -1,    -1,    -1,   440,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   423,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   431,    -1,    -1,   434,    -1,    -1,   308,    -1,
      -1,   440,    31,    -1,    33,    -1,    -1,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   335,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    -1,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   371,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     380,   381,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   115,    -1,    -1,    -1,
     400,    -1,    -1,    -1,    -1,   405,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    81,   423,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   431,    -1,    -1,   434,    -1,   155,    96,    65,    66,
     440,    -1,    -1,    -1,    -1,    -1,    73,    -1,    75,    76,
      77,    78,    79,    80,   173,    -1,    -1,   176,   177,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   190,    -1,    -1,    -1,    -1,    -1,    -1,   197,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   115,    -1,
      -1,    -1,    -1,    -1,   213,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,   236,    -1,    -1,
      -1,   180,    -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,
      -1,    96,   191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     269,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   188,   221,    -1,   283,   284,    -1,   226,    -1,    -1,
     197,   230,   291,   232,   293,    -1,   235,    -1,   237,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   213,   306,   307,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     227,   228,    -1,    -1,    -1,    -1,    -1,    -1,   267,    -1,
      -1,    -1,   331,    -1,    -1,   180,    -1,   336,    -1,    -1,
     247,    -1,    -1,    -1,    -1,   252,   191,    -1,    -1,    -1,
      -1,   350,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   360,   269,   362,   363,   364,    -1,    -1,    -1,   308,
      -1,    -1,    -1,    81,    -1,    -1,   221,   284,    -1,    -1,
      -1,   226,    -1,    -1,   291,   230,   293,   232,    96,   296,
     235,    -1,   237,    -1,    81,    -1,   335,   396,    -1,   306,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   407,    96,
      -1,    -1,   411,   412,   413,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   267,    -1,    -1,   424,    -1,   426,   427,    -1,
      -1,    -1,   371,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   380,   381,    -1,    -1,    -1,    -1,    -1,   447,    -1,
      -1,    -1,    -1,   360,    -1,   362,   363,   364,    -1,    -1,
      -1,   400,   369,   308,    -1,    -1,   405,    -1,    -1,    -1,
      -1,    -1,   180,    -1,    -1,    -1,   383,    -1,    -1,    -1,
      -1,    -1,    -1,   191,   423,    -1,    -1,   174,    -1,    -1,
     335,    -1,   431,   180,    -1,   434,    -1,    -1,    -1,   406,
      -1,   440,   441,   442,   411,   412,   413,    -1,    -1,    -1,
     449,   450,    -1,   221,    -1,    -1,    -1,   424,   226,    -1,
     427,   428,   230,    -1,   232,    -1,   371,   235,    -1,   237,
      -1,    -1,    -1,    -1,    -1,   380,   381,    -1,    -1,    -1,
     447,    -1,    -1,   230,    -1,   232,    -1,    -1,   235,    -1,
      -1,    -1,    -1,    -1,    -1,   400,    -1,    -1,    -1,   267,
     405,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   423,    -1,
     267,    -1,    -1,    -1,    -1,    -1,   431,    -1,    -1,   434,
      -1,    -1,    -1,    -1,    -1,   440,   441,   442,    -1,    -1,
     308,    -1,    -1,    -1,   449,   450,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   335,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   335,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   371,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   380,   381,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   400,   380,   381,    -1,    -1,   405,    -1,    -1,
      -1,    -1,    -1,   390,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   423,    -1,    -1,   405,    -1,
      -1,    -1,    -1,   431,    -1,    -1,   434,    -1,   415,    -1,
      -1,    -1,   440,   441,   442,    -1,   423,    -1,    -1,    -1,
      -1,   428,   450,    -1,   431,    -1,   433,   434
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   456,   457,     0,   179,   304,   458,   459,   460,   466,
     473,   475,   447,   447,   459,   147,   481,   481,   230,   305,
     476,   476,   117,   461,   467,    27,   477,   477,   447,    99,
     580,   580,   230,   447,   474,    82,   482,   117,   462,   468,
     210,   478,  1124,   349,   166,   204,   212,   533,   447,   300,
     714,   714,   447,    72,   315,   399,   479,   480,   447,   447,
     349,   447,   165,   347,   398,   581,   587,   117,   463,   469,
     473,   132,   472,   480,   303,  1135,   483,   534,   447,   535,
     349,   436,   612,   583,    54,   426,   717,   136,   463,   470,
     481,   476,   268,   330,   370,   372,   484,   485,   489,   497,
     502,   537,   166,   536,    22,   245,   343,   570,   571,   572,
     573,   575,   579,   447,   349,   233,   657,   434,   586,   588,
    1055,   719,   718,   334,   725,   476,   464,   447,   447,   447,
     447,   447,   352,   538,   447,   212,   569,    71,   398,  1120,
     312,   367,   368,   574,   447,   572,   582,   447,   349,   229,
     659,   585,   587,   614,   615,   616,   589,    49,   720,   721,
     722,  1115,   720,   434,   447,   447,   580,   239,   351,   434,
     488,   490,   491,   492,   493,   495,   496,  1135,   178,   498,
     499,   500,   433,   486,   487,   488,  1149,    11,    25,    26,
      57,    94,    95,    97,   105,   148,   149,   159,   231,   345,
     385,   434,   503,   504,   505,   506,   510,   519,   523,   526,
     527,   528,   529,   530,   531,   532,   276,  1101,   537,   447,
     273,  1132,   388,  1143,    24,  1111,   584,   613,   447,   349,
     325,   661,   588,   617,  1095,   590,   721,   365,   410,   723,
     318,   427,   715,   465,   365,  1124,   447,   491,   447,   492,
      62,   356,  1107,     9,   230,   501,   447,   500,   447,   447,
     487,   104,   434,  1066,  1124,  1124,  1066,   377,   360,  1139,
    1124,  1124,  1124,  1124,  1124,  1066,  1124,    56,  1117,  1124,
     447,   505,  1066,   570,   434,  1062,  1063,  1081,    84,  1118,
     172,  1121,   585,   614,   658,   447,   349,   344,   702,   614,
     447,  1095,   434,   618,   620,   625,     1,    47,    61,    99,
     215,   225,   312,   313,   325,   327,   427,   447,   591,   592,
     594,   598,   600,   602,   603,   609,   610,   611,  1124,  1124,
     365,   276,   724,   106,   726,   714,  1124,   230,  1084,   447,
     356,  1124,   207,   207,   230,   447,   243,   511,  1066,  1066,
    1124,  1124,  1124,  1063,    67,  1066,  1066,  1063,  1124,  1063,
     520,   521,  1066,    94,  1066,   539,   196,   270,  1104,  1063,
     576,   577,  1055,  1054,  1055,   614,   660,   447,   349,   618,
     447,   168,   434,   621,   622,  1118,  1124,   312,   314,  1105,
    1105,  1124,  1118,  1124,   243,  1129,  1124,    23,  1110,   270,
     164,   184,    31,   107,  1084,  1124,   434,   447,   716,   469,
    1084,  1063,  1124,   191,   230,   237,   308,   371,   400,   440,
     524,   525,  1087,  1063,   230,  1063,    23,   210,  1066,  1125,
     507,   540,  1081,   577,   294,   578,  1055,   614,   662,   447,
     447,   619,    83,  1084,   434,  1124,  1110,  1062,   272,   373,
     599,   230,  1063,  1065,  1084,   428,  1124,   434,   701,   701,
     167,   434,  1084,   727,   728,   136,   471,    56,   435,   494,
     121,   191,   230,   237,   249,   308,   371,   374,   375,   440,
     512,   513,   514,   517,   525,   393,   522,  1084,   508,     1,
       4,    19,    29,   198,   227,   234,   279,   285,   312,   319,
     332,   357,   359,   367,   398,   447,   541,   542,   546,   548,
     553,   554,   555,   556,   560,   561,   562,   563,   564,   565,
     566,   567,  1107,  1084,   310,   663,   664,   665,   703,   626,
     623,  1124,   396,   597,   228,  1128,   396,  1117,   196,  1123,
     434,  1124,  1124,   728,     1,   434,   729,   730,   731,   732,
     733,   738,   476,   514,    17,   393,  1087,  1084,   271,   273,
     509,  1129,   312,   396,  1147,   357,  1129,  1124,    55,  1116,
      37,   110,   214,  1114,  1126,  1126,  1084,  1149,   377,  1124,
     701,   665,   704,     1,    21,    34,    37,    38,    39,    40,
      41,    42,    43,    73,    75,    76,    77,    78,    79,    80,
     115,   197,   213,   247,   269,   284,   291,   293,   306,   316,
     323,   360,   362,   363,   364,   386,   411,   412,   413,   424,
     427,   627,   628,   629,   631,   632,   633,   634,   635,   636,
     645,   646,   648,   649,   650,   655,   656,  1124,  1140,    27,
    1112,   184,  1084,    56,   314,   593,   604,  1084,   365,  1141,
     230,   601,  1081,   601,   123,   447,   349,     3,     5,    10,
      18,    51,    52,    59,    70,    74,    86,   108,   115,   116,
     146,   158,   162,   175,   182,   185,   186,   193,   200,   202,
     205,   240,   244,   246,   253,   275,   290,   311,   320,   333,
     338,   340,   348,   358,   367,   376,   378,   379,   382,   384,
     389,   404,   409,   414,   425,   437,   447,   739,   740,   750,
     755,   759,   762,   775,   778,   783,   788,   789,   790,   793,
     795,   802,   806,   808,   823,   826,   828,   830,   833,   835,
     841,   850,   852,   869,   871,   874,   878,   884,   894,   901,
     903,   906,   910,   911,   922,   933,   943,   949,   952,   958,
     962,   964,   966,   968,   971,   982,   983,   992,   994,   995,
     447,   515,   517,   377,  1142,  1124,  1126,   120,   164,   544,
    1124,   312,   319,   561,  1124,  1124,   357,  1124,  1124,  1111,
       9,   254,   311,   568,  1124,   434,   666,   620,   625,   705,
     706,   707,   221,   361,   410,   361,   410,   361,   410,   361,
     410,   361,   410,   430,  1148,   339,  1137,  1084,  1080,  1081,
    1081,   210,   220,   339,   647,  1124,  1125,   164,   184,   219,
     403,     9,    50,   221,   624,  1085,  1086,  1087,    30,   605,
     606,   607,   608,  1113,  1149,  1117,   176,   596,  1122,   106,
     230,   734,   741,   751,   756,   760,   763,   776,   779,   784,
     791,   794,   796,   803,   807,   809,   824,   827,   829,  1147,
     834,     1,   836,   842,   851,   853,   870,   872,   875,   879,
     885,   895,   902,   904,   907,   912,   923,   934,   944,   230,
     342,   953,   959,   299,   963,   965,   967,   969,   972,   184,
     984,  1121,   996,   191,   230,   237,   308,   371,   440,   516,
     518,  1124,   120,   309,   357,   547,  1124,   114,   298,   543,
      32,   161,   238,   557,  1065,   374,  1063,  1063,   280,  1134,
    1134,   274,  1063,    60,    87,    88,   286,   447,   667,   668,
     672,  1124,   621,   707,   440,   396,   637,   450,  1082,  1083,
     393,   634,   652,   653,  1085,    27,   630,   355,  1103,  1103,
    1087,   270,  1131,  1131,   454,    48,   402,   171,   597,  1084,
     447,   447,   742,  1079,  1080,     6,    81,    92,    96,   180,
     221,   226,   232,   235,   267,   335,   380,   381,   405,   423,
     431,   752,  1049,  1069,  1070,  1079,  1085,  1088,   434,   757,
    1036,  1037,  1038,   230,  1059,  1060,  1061,  1081,   230,  1077,
    1079,  1088,   777,   780,   785,  1050,  1051,  1070,  1055,   398,
     230,   797,  1069,  1076,  1079,   804,  1070,   230,   397,   401,
     810,   811,  1036,   289,   290,   303,   349,   825,     6,  1067,
    1068,  1079,  1079,   831,   133,  1035,  1036,  1067,   671,  1079,
     854,  1079,  1085,  1088,   935,  1081,    92,   873,  1070,   876,
    1070,   880,   174,   230,   886,   889,   890,   891,  1059,  1077,
    1081,  1149,  1055,  1052,  1081,  1055,  1052,     9,   913,  1053,
    1081,   147,   242,   924,   925,   926,   927,   929,   930,   931,
     932,  1056,  1057,  1067,   935,  1055,   950,   109,   954,   955,
    1070,    92,   960,  1069,   671,  1079,  1055,  1079,     8,    35,
     986,   104,  1052,    17,  1066,  1063,   115,   230,   545,  1081,
     433,   558,   558,   369,   448,   552,  1063,  1064,  1124,   169,
     669,   670,   669,  1125,   680,   184,   708,  1084,   395,  1146,
     221,   441,   442,   450,  1046,  1048,  1049,  1071,  1079,  1086,
    1088,   450,  1083,  1081,   651,   653,   393,   230,  1116,  1080,
    1080,  1087,  1065,  1065,  1113,  1117,   124,   749,    30,   176,
     743,  1113,  1131,   450,  1079,   450,  1089,   450,  1090,  1131,
    1104,   450,   450,   450,   450,   450,   450,   450,   450,  1089,
     125,   754,   396,   753,  1070,   201,  1098,    56,  1039,  1040,
     396,  1104,   426,   764,   230,  1076,  1079,  1055,   127,   786,
     153,   448,   787,  1051,   341,  1102,   312,  1136,  1054,   129,
     801,   743,   419,   420,   421,   422,   130,   805,    49,   206,
     764,    17,   430,   812,   813,   814,   818,  1109,    98,  1131,
    1068,  1058,   392,  1145,   843,  1149,  1079,    91,   324,   387,
     855,   856,   857,   861,   866,   937,  1070,   396,   134,   877,
      49,   163,   203,   211,   281,   881,   890,   135,   887,   415,
     428,   393,   395,   390,   252,   297,  1099,   176,   997,  1136,
     997,  1053,   140,   921,   428,   915,  1074,  1079,  1086,   930,
     932,  1067,   396,  1057,   118,   396,   416,   928,   945,   183,
     334,   951,  1115,   206,   955,  1079,   143,   961,   176,   176,
     312,   314,   970,   109,   973,   326,   373,   987,  1132,   997,
     518,   119,   433,   552,  1097,  1106,   234,   340,  1124,   549,
     550,  1076,   671,   678,  1084,   620,   681,   709,   111,   638,
    1131,  1048,  1048,  1048,    69,   353,   449,  1047,   441,   442,
     443,   444,   446,   453,  1048,  1148,  1085,  1128,  1065,   111,
     595,  1074,    25,    26,    66,    68,   100,   101,   102,   147,
     149,   157,   228,   394,   434,  1057,   433,   746,    65,   227,
     294,   744,   745,   146,   303,  1072,  1080,  1046,  1048,   396,
    1048,  1046,  1091,  1080,  1086,  1088,   434,  1048,  1094,  1048,
    1048,  1093,  1048,  1046,  1046,  1048,  1092,  1048,  1050,  1070,
     183,   334,   758,  1098,    12,    13,    14,    20,    58,   153,
     154,   181,   187,   210,   218,   222,   250,   251,   255,   265,
     272,   277,   295,   440,   441,   442,   443,   444,   446,   448,
     449,   451,   452,  1041,  1042,  1043,  1044,  1045,   210,   250,
     255,   441,   442,   446,   450,  1041,  1042,  1043,  1044,  1045,
    1070,   302,   761,  1061,   765,   183,   334,   769,   317,   408,
     781,   782,  1149,  1036,   209,   259,  1028,  1029,  1030,  1032,
     418,   433,   798,  1149,   160,  1003,  1004,  1003,  1003,  1003,
    1070,  1050,  1070,    21,   397,   401,   819,   820,  1037,   131,
     822,   432,   814,   816,   430,   815,   811,  1080,   111,   832,
    1059,   837,     9,    12,    15,    16,   247,   248,   265,   266,
     844,   848,   168,  1074,     9,    56,   170,   219,   403,   862,
     863,   864,   858,   856,   939,  1106,  1132,   396,  1067,  1050,
    1070,   359,   882,   735,   736,  1035,   892,   893,  1079,  1059,
       8,    35,   999,  1136,  1076,   206,   896,   908,  1149,   916,
    1113,  1079,   916,   396,   396,   509,   146,   397,   401,  1070,
      49,   214,   946,  1070,  1070,   365,  1070,  1079,   176,  1050,
    1070,  1074,  1115,   206,   976,  1079,   156,   160,   988,     9,
     993,  1059,   908,   119,   549,   273,   551,  1063,   551,   189,
     673,   227,   228,   679,   434,   621,    31,    33,    36,    44,
      45,    46,    65,   155,   173,   176,   177,   190,   227,   236,
     269,   283,   307,   331,   336,   350,   396,   407,   426,   447,
     632,   633,   635,   645,   648,   650,   710,   713,  1132,   639,
     640,  1080,  1086,  1088,   449,  1048,  1048,  1048,  1048,  1048,
    1048,   449,  1048,   358,  1138,  1128,  1132,  1002,  1004,   439,
     438,  1074,  1002,   214,    31,    33,    36,    46,   173,   177,
     190,   236,   283,   307,   331,   336,   346,   350,   407,   417,
     747,   748,  1002,   263,  1130,  1130,  1130,   745,   744,   230,
    1073,  1080,   449,  1079,   453,   449,  1047,   449,   449,  1047,
     449,   449,   449,   449,  1047,   449,   449,   366,  1008,  1009,
    1050,  1068,   334,  1147,   391,  1144,  1144,   396,  1059,   766,
     767,   768,  1115,  1079,  1079,   160,   282,   770,   989,  1121,
     234,   254,  1008,  1031,  1033,   128,   792,  1032,    94,   298,
     434,  1057,    33,    36,    44,    45,    46,   155,   173,   190,
     236,   283,   336,   346,   407,   799,   800,  1003,   262,  1005,
     258,  1006,   183,  1008,   183,  1109,   393,   821,   817,   819,
     735,  1132,   735,  1147,   324,   845,  1147,   396,    49,   863,
     865,  1074,     9,    56,   219,   403,   859,   860,  1074,   940,
    1107,   196,   278,  1133,    28,   112,   641,  1067,  1008,   183,
    1149,  1054,   135,   888,   737,     8,   176,   896,  1079,   123,
     256,  1018,  1019,  1021,  1028,   234,   254,   430,   123,   430,
     918,   919,  1074,  1073,  1070,  1124,  1028,   956,  1149,  1079,
    1008,   183,   396,     9,   974,   975,  1096,   977,  1079,   956,
     977,   300,   991,   301,   998,   999,  1097,   245,   312,   314,
     559,  1124,   170,   674,  1084,   682,  1124,  1130,   150,   152,
    1124,  1077,  1130,  1084,  1079,  1079,  1063,   198,   642,   641,
     449,  1147,  1063,  1006,  1002,  1124,  1124,   118,   416,   748,
    1076,  1076,  1076,  1089,  1102,   449,  1048,  1063,  1089,  1089,
    1048,  1089,  1089,  1089,   219,   403,  1089,  1089,  1010,   261,
    1011,  1008,  1068,   153,   277,   153,   277,   767,   272,   723,
      85,   318,   427,   258,   260,   772,   990,   771,   322,   337,
     735,   735,   798,   798,   798,   798,  1124,   150,   152,  1124,
     118,   416,   800,   735,  1007,  1050,  1051,  1050,  1051,   820,
    1036,   735,  1079,   122,   838,   427,   846,   847,   848,   107,
     849,   427,  1075,  1079,  1085,  1074,    49,   867,   860,   172,
     867,   936,  1124,   278,  1126,  1050,   568,   883,  1149,   738,
     893,  1070,   195,   897,  1149,  1020,  1022,   138,   905,  1021,
     139,   909,   234,  1036,   917,  1035,   918,   255,   947,  1100,
     141,   948,   282,  1013,  1014,   293,  1102,  1050,  1075,   277,
    1074,   110,   978,   387,   980,  1132,   151,   257,  1000,  1023,
    1024,  1026,  1029,     7,  1108,   559,  1084,   113,   216,   675,
      66,    65,    66,   188,   227,   228,   252,   296,   369,   383,
     406,   428,   447,   632,   633,   635,   636,   645,   648,   650,
     683,   684,   686,   687,   688,   689,   691,   692,   693,   694,
     698,   699,   440,  1078,  1079,  1084,  1124,  1078,  1124,  1146,
    1115,  1126,   397,   654,  1078,  1078,  1034,  1115,  1034,  1008,
     449,   735,  1012,  1147,   153,  1147,   153,  1070,   126,   774,
     773,   735,  1003,  1003,  1003,  1003,  1078,  1078,  1034,  1034,
     735,  1008,   321,  1008,   321,   839,   133,   840,   847,    99,
    1119,   867,   867,  1075,   999,   203,   426,   941,  1063,   938,
    1008,   234,   254,    49,   234,   214,   898,   194,   234,   254,
     429,   735,   735,   914,   735,   920,   671,  1041,  1042,  1043,
    1044,  1045,  1015,   142,   957,   260,  1016,  1079,  1008,  1008,
     975,  1123,    93,   979,  1123,  1013,   163,   203,   211,   281,
     985,  1054,  1025,  1027,   145,  1001,  1026,   286,  1057,  1078,
    1124,    90,   217,   676,   264,  1130,   199,   700,   263,   264,
     697,  1110,   188,   430,  1124,  1131,  1124,  1079,   689,   252,
     292,   695,   696,  1084,   241,   292,   441,   442,   712,   241,
     292,   441,   442,   711,   434,   643,   644,  1124,  1124,  1078,
     735,  1147,  1147,   735,  1051,  1051,   735,    49,   867,   399,
     868,   300,  1054,   183,   281,   942,  1081,   337,  1070,  1124,
     899,  1018,  1029,   234,   234,   735,   735,   735,  1017,  1079,
    1123,  1079,   144,   981,   735,   735,   227,   228,  1127,  1084,
    1124,  1124,   171,   677,  1124,  1125,  1124,  1035,  1079,   690,
    1063,    89,    90,   113,   287,   288,   328,   329,   685,   176,
     286,  1084,   696,  1078,  1078,   644,  1062,  1085,  1127,  1008,
    1008,  1070,  1070,  1124,  1054,   300,   415,   671,   137,   900,
     735,  1079,  1084,  1084,  1124,  1084,  1084,  1102,  1070,   889,
    1124,  1035,  1084,    49,   889,  1070
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
#line 1275 "parser.y"
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
#line 1289 "parser.y"
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
#line 1303 "parser.y"
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
#line 1321 "parser.y"
    {
	cb_define_switch_name ((yyvsp[(5) - (5)]), save_tree_1, (yyvsp[(2) - (5)]), save_tree_2);
  ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 1327 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1328 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1336 "parser.y"
    {
	save_tree_1 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 1340 "parser.y"
    {
	current_program->alphabet_name_list =
		cb_list_add (current_program->alphabet_name_list, (yyvsp[(5) - (5)]));
  ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 1347 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_NATIVE); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1348 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_1); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1349 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_2); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1350 "parser.y"
    { (yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_EBCDIC); ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1352 "parser.y"
    {
	(yyval) = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_CUSTOM);
	CB_ALPHABET_NAME ((yyval))->custom_list = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1359 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1361 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1365 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1366 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1368 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (2)]));
	save_tree_2 = (yyval);
  ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1373 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (4)]);
  ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1384 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1385 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1386 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1387 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1388 "parser.y"
    { (yyval) = cb_norm_high; ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1389 "parser.y"
    { (yyval) = cb_norm_low; ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1393 "parser.y"
    { cb_list_add (save_tree_2, (yyvsp[(1) - (1)])); ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1394 "parser.y"
    { cb_list_add (save_tree_2, cb_space); ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1395 "parser.y"
    { cb_list_add (save_tree_2, cb_zero); ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1396 "parser.y"
    { cb_list_add (save_tree_2, cb_quote); ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1397 "parser.y"
    { cb_list_add (save_tree_2, cb_norm_high); ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1398 "parser.y"
    { cb_list_add (save_tree_2, cb_norm_low); ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1406 "parser.y"
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
#line 1417 "parser.y"
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
#line 1428 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1429 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1433 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1434 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1442 "parser.y"
    {
	current_program->class_name_list =
			cb_list_add (current_program->class_name_list,
			cb_build_class_name ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])));
  ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1450 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1451 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1455 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1457 "parser.y"
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
#line 1471 "parser.y"
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
#line 1486 "parser.y"
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
#line 1553 "parser.y"
    {
	current_program->decimal_point = ',';
	current_program->numeric_separator = '.';
  ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1563 "parser.y"
    { current_program->cursor_pos = (yyvsp[(3) - (3)]); ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1570 "parser.y"
    { current_program->crt_status = (yyvsp[(4) - (4)]); ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1577 "parser.y"
    {  PENDING ("SCREEN CONTROL"); ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1583 "parser.y"
    {  PENDING ("EVENT STATUS"); ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1595 "parser.y"
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
#line 1604 "parser.y"
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
#line 1629 "parser.y"
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
#line 1644 "parser.y"
    {
	validate_file (current_file, (yyvsp[(3) - (6)]));
  ;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 1675 "parser.y"
    {
	current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
  ;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1679 "parser.y"
    {
	current_file->fileid_assign = 1;
	current_file->assign = cb_build_assignment_name (current_file, cb_build_reference ("DISK"));
  ;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1684 "parser.y"
    {
	current_file->fileid_assign = 1;
	current_file->assign = cb_build_assignment_name (current_file, cb_build_reference ("PRINTER"));
  ;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1692 "parser.y"
    { current_file->organization = COB_ORG_LINE_SEQUENTIAL; ;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1697 "parser.y"
    {
	current_file->external_assign = 1;
  ;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1701 "parser.y"
    {
	current_file->external_assign = 0;
  ;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1709 "parser.y"
    {
	const char	*s;

	s = "$#@DUMMY@#$";
	(yyval) = cb_build_alphanumeric_literal ((unsigned char *)s, strlen (s));
  ;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1726 "parser.y"
    { current_file->access_mode = COB_ACCESS_SEQUENTIAL; ;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1727 "parser.y"
    { current_file->access_mode = COB_ACCESS_DYNAMIC; ;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1728 "parser.y"
    { current_file->access_mode = COB_ACCESS_RANDOM; ;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1736 "parser.y"
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

  case 196:

/* Line 1455 of yacc.c  */
#line 1756 "parser.y"
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

  case 197:

/* Line 1455 of yacc.c  */
#line 1802 "parser.y"
    {
	key_component_list = NULL;
  ;}
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 1811 "parser.y"
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

  case 201:

/* Line 1455 of yacc.c  */
#line 1826 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 1827 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 1828 "parser.y"
    { (yyval) = cb_int('='); ;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1835 "parser.y"
    {
	PENDING ("COLLATING SEQUENCE");
  ;}
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 1845 "parser.y"
    {
	current_file->file_status = (yyvsp[(4) - (5)]);
	if ((yyvsp[(5) - (5)])) {
		PENDING ("2nd FILE STATUS");
	}
  ;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1866 "parser.y"
    { current_file->lock_mode = COB_LOCK_MANUAL; ;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1867 "parser.y"
    { current_file->lock_mode = COB_LOCK_AUTOMATIC; ;}
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 1868 "parser.y"
    { current_file->lock_mode = COB_LOCK_EXCLUSIVE; ;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1874 "parser.y"
    {
	current_file->lock_mode |= COB_LOCK_MULTIPLE;
  ;}
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 1877 "parser.y"
    { PENDING ("WITH ROLLBACK"); ;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 1894 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_INDEXED;
		organized_seen = 1;
	}
  ;}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 1903 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_SEQUENTIAL;
		organized_seen = 1;
	}
  ;}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 1912 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = cb_default_organization;
		organized_seen = 1;
	}
  ;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1921 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_RELATIVE;
		organized_seen = 1;
	}
  ;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1930 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_LINE_SEQUENTIAL;
		organized_seen = 1;
	}
  ;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1945 "parser.y"
    {
	cb_verify (cb_padding_character_clause, "PADDING CHARACTER");
  ;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1954 "parser.y"
    { /* ignored */ ;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 1962 "parser.y"
    {
	current_file->key = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 1966 "parser.y"
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

  case 230:

/* Line 1455 of yacc.c  */
#line 2003 "parser.y"
    { current_file->key = (yyvsp[(4) - (4)]); ;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 2010 "parser.y"
    { /* ignored */ ;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 2017 "parser.y"
    { current_file->sharing = (yyvsp[(3) - (3)]); ;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 2021 "parser.y"
    { (yyval) = NULL; PENDING ("SHARING ALL OTHER"); ;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 2022 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 2023 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 2054 "parser.y"
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

  case 246:

/* Line 1455 of yacc.c  */
#line 2078 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 2079 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 2080 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 2081 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 2088 "parser.y"
    {
	cb_verify (cb_multiple_file_tape_clause, "MULTIPLE FILE TAPE");
  ;}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 2099 "parser.y"
    { ;}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 2110 "parser.y"
    {
	PENDING ("APPLY COMMITMENT-CONTROL");
  ;}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 2135 "parser.y"
    { current_storage = CB_STORAGE_FILE; ;}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 2138 "parser.y"
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

  case 266:

/* Line 1455 of yacc.c  */
#line 2157 "parser.y"
    {
	if ((yyvsp[(3) - (3)]) && (yyvsp[(3) - (3)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(3) - (3)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 2169 "parser.y"
    {
	if ((yyvsp[(2) - (2)]) && (yyvsp[(2) - (2)]) != cb_error_node) {
		finalize_file (current_file, CB_FIELD ((yyvsp[(2) - (2)])));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 2180 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 2181 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 2191 "parser.y"
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

  case 272:

/* Line 1455 of yacc.c  */
#line 2202 "parser.y"
    {
	/* Shut up bison */
	dummy_tree = (yyvsp[(2) - (4)]);
  ;}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 2214 "parser.y"
    {
	if (current_file->global) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->external = 1;
  ;}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 2221 "parser.y"
    {
	if (current_file->external) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->global = 1;
  ;}
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 2244 "parser.y"
    { /* ignored */ ;}
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 2254 "parser.y"
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

  case 292:

/* Line 1455 of yacc.c  */
#line 2266 "parser.y"
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

  case 293:

/* Line 1455 of yacc.c  */
#line 2292 "parser.y"
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

  case 295:

/* Line 1455 of yacc.c  */
#line 2316 "parser.y"
    {
	current_file->record_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 2322 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 2323 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 2327 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 2328 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 2336 "parser.y"
    {
	cb_verify (cb_label_records_clause, "LABEL RECORDS");
  ;}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 2351 "parser.y"
    {
	cb_verify (cb_value_of_clause, "VALUE OF");
  ;}
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 2355 "parser.y"
    {
	if (!current_file->assign) {
		current_file->assign = cb_build_assignment_name (current_file, (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 307:

/* Line 1455 of yacc.c  */
#line 2371 "parser.y"
    {
	cb_verify (cb_data_records_clause, "DATA RECORDS");
  ;}
    break;

  case 308:

/* Line 1455 of yacc.c  */
#line 2382 "parser.y"
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

  case 314:

/* Line 1455 of yacc.c  */
#line 2410 "parser.y"
    {
	current_file->latfoot = (yyvsp[(4) - (5)]);
  ;}
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 2417 "parser.y"
    {
	current_file->lattop = (yyvsp[(3) - (4)]);
  ;}
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 2424 "parser.y"
    {
	current_file->latbot = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 2433 "parser.y"
    { /* ignore */ ;}
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 2441 "parser.y"
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

  case 319:

/* Line 1455 of yacc.c  */
#line 2459 "parser.y"
    {
	cb_warning (_("file descriptor REPORT IS"));
  ;}
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 2463 "parser.y"
    {
	cb_warning (_("file descriptor REPORTS ARE"));
  ;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 2474 "parser.y"
    { current_storage = CB_STORAGE_WORKING; ;}
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 2476 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->working_storage =
			cb_field_add (current_program->working_storage, CB_FIELD ((yyvsp[(5) - (5)])));
	}
  ;}
    break;

  case 324:

/* Line 1455 of yacc.c  */
#line 2485 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 325:

/* Line 1455 of yacc.c  */
#line 2486 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 326:

/* Line 1455 of yacc.c  */
#line 2490 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 327:

/* Line 1455 of yacc.c  */
#line 2496 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	(yyval) = CB_TREE (description_field);
  ;}
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 2516 "parser.y"
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

  case 333:

/* Line 1455 of yacc.c  */
#line 2527 "parser.y"
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

  case 335:

/* Line 1455 of yacc.c  */
#line 2551 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 2557 "parser.y"
    {
	(yyval) = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 2563 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 2572 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	qualifier = (yyvsp[(1) - (1)]);
	non_const_word = 0;
  ;}
    break;

  case 340:

/* Line 1455 of yacc.c  */
#line 2581 "parser.y"
    {
	current_field->flag_is_global = 1;
	cb_error (_("CONSTANT with GLOBAL clause is not yet supported"));
  ;}
    break;

  case 341:

/* Line 1455 of yacc.c  */
#line 2588 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 342:

/* Line 1455 of yacc.c  */
#line 2589 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 343:

/* Line 1455 of yacc.c  */
#line 2590 "parser.y"
    { (yyval) = cb_build_const_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 344:

/* Line 1455 of yacc.c  */
#line 2595 "parser.y"
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

  case 345:

/* Line 1455 of yacc.c  */
#line 2614 "parser.y"
    {
	/* required to check redefines */
	(yyval) = NULL;
  ;}
    break;

  case 346:

/* Line 1455 of yacc.c  */
#line 2620 "parser.y"
    {
	/* required to check redefines */
	(yyval) = cb_true;
  ;}
    break;

  case 362:

/* Line 1455 of yacc.c  */
#line 2649 "parser.y"
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

  case 363:

/* Line 1455 of yacc.c  */
#line 2671 "parser.y"
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

  case 364:

/* Line 1455 of yacc.c  */
#line 2692 "parser.y"
    { current_field->ename = NULL; ;}
    break;

  case 365:

/* Line 1455 of yacc.c  */
#line 2694 "parser.y"
    {
	struct cb_field *x;

	x = CB_FIELD(cb_build_field (cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(2) - (2)]))->data))));
	current_field->ename = x->name;
 ;}
    break;

  case 366:

/* Line 1455 of yacc.c  */
#line 2706 "parser.y"
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

  case 367:

/* Line 1455 of yacc.c  */
#line 2725 "parser.y"
    { current_field->pic = CB_PICTURE ((yyvsp[(1) - (1)])); ;}
    break;

  case 370:

/* Line 1455 of yacc.c  */
#line 2737 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 371:

/* Line 1455 of yacc.c  */
#line 2738 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 372:

/* Line 1455 of yacc.c  */
#line 2739 "parser.y"
    { current_field->usage = CB_USAGE_FLOAT; ;}
    break;

  case 373:

/* Line 1455 of yacc.c  */
#line 2740 "parser.y"
    { current_field->usage = CB_USAGE_DOUBLE; ;}
    break;

  case 374:

/* Line 1455 of yacc.c  */
#line 2741 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 375:

/* Line 1455 of yacc.c  */
#line 2742 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 376:

/* Line 1455 of yacc.c  */
#line 2743 "parser.y"
    { current_field->usage = CB_USAGE_COMP_5; ;}
    break;

  case 377:

/* Line 1455 of yacc.c  */
#line 2744 "parser.y"
    { current_field->usage = CB_USAGE_COMP_X; ;}
    break;

  case 378:

/* Line 1455 of yacc.c  */
#line 2745 "parser.y"
    { current_field->usage = CB_USAGE_DISPLAY; ;}
    break;

  case 379:

/* Line 1455 of yacc.c  */
#line 2746 "parser.y"
    { current_field->usage = CB_USAGE_INDEX; ;}
    break;

  case 380:

/* Line 1455 of yacc.c  */
#line 2747 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 381:

/* Line 1455 of yacc.c  */
#line 2749 "parser.y"
    {
	current_field->usage = CB_USAGE_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 382:

/* Line 1455 of yacc.c  */
#line 2754 "parser.y"
    {
	current_field->usage = CB_USAGE_PROGRAM_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 383:

/* Line 1455 of yacc.c  */
#line 2758 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 384:

/* Line 1455 of yacc.c  */
#line 2759 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 385:

/* Line 1455 of yacc.c  */
#line 2760 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 386:

/* Line 1455 of yacc.c  */
#line 2761 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 387:

/* Line 1455 of yacc.c  */
#line 2762 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 388:

/* Line 1455 of yacc.c  */
#line 2763 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 389:

/* Line 1455 of yacc.c  */
#line 2764 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 390:

/* Line 1455 of yacc.c  */
#line 2765 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_CHAR; ;}
    break;

  case 391:

/* Line 1455 of yacc.c  */
#line 2766 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 392:

/* Line 1455 of yacc.c  */
#line 2767 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 393:

/* Line 1455 of yacc.c  */
#line 2768 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 394:

/* Line 1455 of yacc.c  */
#line 2769 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 395:

/* Line 1455 of yacc.c  */
#line 2770 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 396:

/* Line 1455 of yacc.c  */
#line 2771 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 397:

/* Line 1455 of yacc.c  */
#line 2772 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 398:

/* Line 1455 of yacc.c  */
#line 2773 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 399:

/* Line 1455 of yacc.c  */
#line 2774 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 400:

/* Line 1455 of yacc.c  */
#line 2775 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 401:

/* Line 1455 of yacc.c  */
#line 2777 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  ;}
    break;

  case 402:

/* Line 1455 of yacc.c  */
#line 2785 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_UNSIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_UNSIGNED_LONG;
	}
  ;}
    break;

  case 403:

/* Line 1455 of yacc.c  */
#line 2793 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  ;}
    break;

  case 404:

/* Line 1455 of yacc.c  */
#line 2800 "parser.y"
    { PENDING ("USAGE NATIONAL");;}
    break;

  case 405:

/* Line 1455 of yacc.c  */
#line 2808 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 1;
  ;}
    break;

  case 406:

/* Line 1455 of yacc.c  */
#line 2813 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER ((yyvsp[(3) - (3)]))->val;
	current_field->flag_sign_leading  = 0;
  ;}
    break;

  case 407:

/* Line 1455 of yacc.c  */
#line 2825 "parser.y"
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

  case 408:

/* Line 1455 of yacc.c  */
#line 2840 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 409:

/* Line 1455 of yacc.c  */
#line 2841 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 411:

/* Line 1455 of yacc.c  */
#line 2846 "parser.y"
    {
	current_field->occurs_depending = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 412:

/* Line 1455 of yacc.c  */
#line 2853 "parser.y"
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

  case 413:

/* Line 1455 of yacc.c  */
#line 2876 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 414:

/* Line 1455 of yacc.c  */
#line 2879 "parser.y"
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

  case 415:

/* Line 1455 of yacc.c  */
#line 2894 "parser.y"
    { (yyval) = cb_int (COB_ASCENDING); ;}
    break;

  case 416:

/* Line 1455 of yacc.c  */
#line 2895 "parser.y"
    { (yyval) = cb_int (COB_DESCENDING); ;}
    break;

  case 418:

/* Line 1455 of yacc.c  */
#line 2900 "parser.y"
    {
	current_field->index_list = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 419:

/* Line 1455 of yacc.c  */
#line 2906 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 420:

/* Line 1455 of yacc.c  */
#line 2908 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 421:

/* Line 1455 of yacc.c  */
#line 2913 "parser.y"
    {
	(yyval) = cb_build_index ((yyvsp[(1) - (1)]), cb_int1, 1, current_field);
  ;}
    break;

  case 422:

/* Line 1455 of yacc.c  */
#line 2922 "parser.y"
    { current_field->flag_justified = 1; ;}
    break;

  case 423:

/* Line 1455 of yacc.c  */
#line 2929 "parser.y"
    { current_field->flag_synchronized = 1; ;}
    break;

  case 427:

/* Line 1455 of yacc.c  */
#line 2941 "parser.y"
    { current_field->flag_blank_zero = 1; ;}
    break;

  case 428:

/* Line 1455 of yacc.c  */
#line 2949 "parser.y"
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

  case 429:

/* Line 1455 of yacc.c  */
#line 2973 "parser.y"
    { current_field->values = (yyvsp[(3) - (3)]); ;}
    break;

  case 431:

/* Line 1455 of yacc.c  */
#line 2978 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 432:

/* Line 1455 of yacc.c  */
#line 2979 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 433:

/* Line 1455 of yacc.c  */
#line 2983 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 434:

/* Line 1455 of yacc.c  */
#line 2984 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 436:

/* Line 1455 of yacc.c  */
#line 2989 "parser.y"
    {
	if (current_field->level != 88) {
		cb_error (_("FALSE clause only allowed for 88 level"));
	}
	current_field->false_88 = cb_list_init ((yyvsp[(3) - (3)]));
  ;}
    break;

  case 437:

/* Line 1455 of yacc.c  */
#line 3002 "parser.y"
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

  case 438:

/* Line 1455 of yacc.c  */
#line 3014 "parser.y"
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

  case 439:

/* Line 1455 of yacc.c  */
#line 3034 "parser.y"
    {
	if (current_field->flag_item_based) {
		cb_error (_("BASED and ANY LENGTH are mutually exclusive"));
	} else {
		current_field->flag_any_length = 1;
	}
  ;}
    break;

  case 441:

/* Line 1455 of yacc.c  */
#line 3049 "parser.y"
    {
	current_storage = CB_STORAGE_LOCAL;
	if (current_program->nested_level) {
		cb_error (_("LOCAL-STORAGE not allowed in nested programs"));
	}
  ;}
    break;

  case 442:

/* Line 1455 of yacc.c  */
#line 3056 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->local_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 444:

/* Line 1455 of yacc.c  */
#line 3069 "parser.y"
    { current_storage = CB_STORAGE_LINKAGE; ;}
    break;

  case 445:

/* Line 1455 of yacc.c  */
#line 3071 "parser.y"
    {
	if ((yyvsp[(5) - (5)])) {
		current_program->linkage_storage = CB_FIELD ((yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 447:

/* Line 1455 of yacc.c  */
#line 3084 "parser.y"
    {
	cb_error (_("REPORT SECTION not supported"));
	current_storage = CB_STORAGE_REPORT;
  ;}
    break;

  case 454:

/* Line 1455 of yacc.c  */
#line 3117 "parser.y"
    {
	cb_warning (_("Report description using defaults"));
  ;}
    break;

  case 456:

/* Line 1455 of yacc.c  */
#line 3125 "parser.y"
    {
	cb_error (_("GLOBAL is not allowed with RD"));
  ;}
    break;

  case 465:

/* Line 1455 of yacc.c  */
#line 3148 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 466:

/* Line 1455 of yacc.c  */
#line 3149 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 488:

/* Line 1455 of yacc.c  */
#line 3205 "parser.y"
    { cb_warning (_("looking for Report line TYPE")); ;}
    break;

  case 539:

/* Line 1455 of yacc.c  */
#line 3310 "parser.y"
    { current_storage = CB_STORAGE_SCREEN; ;}
    break;

  case 540:

/* Line 1455 of yacc.c  */
#line 3311 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 541:

/* Line 1455 of yacc.c  */
#line 3317 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	current_program->screen_storage = description_field;
	current_program->flag_screen = 1;
  ;}
    break;

  case 547:

/* Line 1455 of yacc.c  */
#line 3341 "parser.y"
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

  case 548:

/* Line 1455 of yacc.c  */
#line 3357 "parser.y"
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

  case 551:

/* Line 1455 of yacc.c  */
#line 3381 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 552:

/* Line 1455 of yacc.c  */
#line 3382 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 553:

/* Line 1455 of yacc.c  */
#line 3383 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BELL; ;}
    break;

  case 554:

/* Line 1455 of yacc.c  */
#line 3384 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLINK; ;}
    break;

  case 555:

/* Line 1455 of yacc.c  */
#line 3385 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 556:

/* Line 1455 of yacc.c  */
#line 3386 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 557:

/* Line 1455 of yacc.c  */
#line 3387 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 558:

/* Line 1455 of yacc.c  */
#line 3388 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 559:

/* Line 1455 of yacc.c  */
#line 3389 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REVERSE; ;}
    break;

  case 560:

/* Line 1455 of yacc.c  */
#line 3390 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 561:

/* Line 1455 of yacc.c  */
#line 3391 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_OVERLINE; ;}
    break;

  case 562:

/* Line 1455 of yacc.c  */
#line 3392 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_AUTO; ;}
    break;

  case 563:

/* Line 1455 of yacc.c  */
#line 3393 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_SECURE; ;}
    break;

  case 564:

/* Line 1455 of yacc.c  */
#line 3394 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REQUIRED; ;}
    break;

  case 565:

/* Line 1455 of yacc.c  */
#line 3395 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_FULL; ;}
    break;

  case 566:

/* Line 1455 of yacc.c  */
#line 3396 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_PROMPT; ;}
    break;

  case 567:

/* Line 1455 of yacc.c  */
#line 3398 "parser.y"
    {
	current_field->screen_line = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 568:

/* Line 1455 of yacc.c  */
#line 3402 "parser.y"
    {
	current_field->screen_column = (yyvsp[(5) - (5)]);
  ;}
    break;

  case 569:

/* Line 1455 of yacc.c  */
#line 3406 "parser.y"
    {
	current_field->screen_foreg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 570:

/* Line 1455 of yacc.c  */
#line 3410 "parser.y"
    {
	current_field->screen_backg = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 578:

/* Line 1455 of yacc.c  */
#line 3421 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 579:

/* Line 1455 of yacc.c  */
#line 3428 "parser.y"
    {
	current_field->screen_from = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 580:

/* Line 1455 of yacc.c  */
#line 3432 "parser.y"
    {
	current_field->screen_to = (yyvsp[(2) - (2)]);
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 581:

/* Line 1455 of yacc.c  */
#line 3441 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 582:

/* Line 1455 of yacc.c  */
#line 3445 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 583:

/* Line 1455 of yacc.c  */
#line 3449 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 584:

/* Line 1455 of yacc.c  */
#line 3453 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 585:

/* Line 1455 of yacc.c  */
#line 3457 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 586:

/* Line 1455 of yacc.c  */
#line 3464 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 587:

/* Line 1455 of yacc.c  */
#line 3468 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 588:

/* Line 1455 of yacc.c  */
#line 3472 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 589:

/* Line 1455 of yacc.c  */
#line 3476 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 590:

/* Line 1455 of yacc.c  */
#line 3480 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 591:

/* Line 1455 of yacc.c  */
#line 3488 "parser.y"
    {
	current_field->occurs_max = cb_get_int ((yyvsp[(2) - (3)]));
	current_field->occurs_min = current_field->occurs_max;
	current_field->indexes++;
	current_field->flag_occurs = 1;
  ;}
    break;

  case 593:

/* Line 1455 of yacc.c  */
#line 3502 "parser.y"
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

  case 594:

/* Line 1455 of yacc.c  */
#line 3512 "parser.y"
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

  case 595:

/* Line 1455 of yacc.c  */
#line 3522 "parser.y"
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

  case 596:

/* Line 1455 of yacc.c  */
#line 3539 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 597:

/* Line 1455 of yacc.c  */
#line 3541 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 598:

/* Line 1455 of yacc.c  */
#line 3545 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 599:

/* Line 1455 of yacc.c  */
#line 3547 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	current_program->flag_chained = 1;
  ;}
    break;

  case 600:

/* Line 1455 of yacc.c  */
#line 3551 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 601:

/* Line 1455 of yacc.c  */
#line 3555 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 602:

/* Line 1455 of yacc.c  */
#line 3557 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 603:

/* Line 1455 of yacc.c  */
#line 3562 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), cb_build_identifier ((yyvsp[(4) - (4)])));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 605:

/* Line 1455 of yacc.c  */
#line 3571 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 606:

/* Line 1455 of yacc.c  */
#line 3575 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 608:

/* Line 1455 of yacc.c  */
#line 3587 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_AUTO;
	}
  ;}
    break;

  case 609:

/* Line 1455 of yacc.c  */
#line 3595 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_4;
	}
  ;}
    break;

  case 610:

/* Line 1455 of yacc.c  */
#line 3603 "parser.y"
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

  case 611:

/* Line 1455 of yacc.c  */
#line 3632 "parser.y"
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

  case 613:

/* Line 1455 of yacc.c  */
#line 3665 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OPTIONAL only allowed for BY REFERENCE items"));
	}
  ;}
    break;

  case 614:

/* Line 1455 of yacc.c  */
#line 3674 "parser.y"
    {
	if (current_program->prog_type == CB_FUNCTION_TYPE) {
		cb_error (_("RETURNING clause is required for a FUNCTION"));
	}
  ;}
    break;

  case 615:

/* Line 1455 of yacc.c  */
#line 3680 "parser.y"
    {
	if (cb_ref ((yyvsp[(2) - (2)])) != cb_error_node) {
		current_program->returning = (yyvsp[(2) - (2)]);
		if (cb_field ((yyvsp[(2) - (2)]))->storage != CB_STORAGE_LINKAGE) {
			cb_error (_("RETURNING item is not defined in LINKAGE SECTION"));
		}
	}
  ;}
    break;

  case 617:

/* Line 1455 of yacc.c  */
#line 3691 "parser.y"
    { in_declaratives = 1; ;}
    break;

  case 618:

/* Line 1455 of yacc.c  */
#line 3694 "parser.y"
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

  case 624:

/* Line 1455 of yacc.c  */
#line 3727 "parser.y"
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

  case 625:

/* Line 1455 of yacc.c  */
#line 3743 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 626:

/* Line 1455 of yacc.c  */
#line 3755 "parser.y"
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

  case 627:

/* Line 1455 of yacc.c  */
#line 3786 "parser.y"
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

  case 628:

/* Line 1455 of yacc.c  */
#line 3823 "parser.y"
    {
	non_const_word = 0;
	check_unreached = 0;
	if ((yyvsp[(1) - (1)]) != cb_error_node) {
		cb_error_x ((yyvsp[(1) - (1)]), _("Unknown statement '%s'"), CB_NAME ((yyvsp[(1) - (1)])));
	}
	YYERROR;
  ;}
    break;

  case 629:

/* Line 1455 of yacc.c  */
#line 3834 "parser.y"
    { (yyval) = cb_build_section_name ((yyvsp[(1) - (1)]), 0); ;}
    break;

  case 631:

/* Line 1455 of yacc.c  */
#line 3838 "parser.y"
    { /* ignore */ ;}
    break;

  case 632:

/* Line 1455 of yacc.c  */
#line 3847 "parser.y"
    {
	(yyval) = current_program->exec_list;
	current_program->exec_list = NULL;
  ;}
    break;

  case 633:

/* Line 1455 of yacc.c  */
#line 3851 "parser.y"
    {
	(yyval) = CB_TREE (current_statement);
	current_statement = NULL;
  ;}
    break;

  case 634:

/* Line 1455 of yacc.c  */
#line 3856 "parser.y"
    {
	(yyval) = cb_list_reverse (current_program->exec_list);
	current_program->exec_list = (yyvsp[(1) - (3)]);
	current_statement = CB_STATEMENT ((yyvsp[(2) - (3)]));
  ;}
    break;

  case 635:

/* Line 1455 of yacc.c  */
#line 3864 "parser.y"
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

  case 686:

/* Line 1455 of yacc.c  */
#line 3936 "parser.y"
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

  case 687:

/* Line 1455 of yacc.c  */
#line 3958 "parser.y"
    {
	BEGIN_STATEMENT ("ACCEPT", TERM_ACCEPT);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 689:

/* Line 1455 of yacc.c  */
#line 3971 "parser.y"
    {
	cb_emit_accept ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 690:

/* Line 1455 of yacc.c  */
#line 3975 "parser.y"
    {
	PENDING ("ACCEPT .. FROM ESCAPE KEY");
  ;}
    break;

  case 691:

/* Line 1455 of yacc.c  */
#line 3979 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 0);
  ;}
    break;

  case 692:

/* Line 1455 of yacc.c  */
#line 3983 "parser.y"
    {
	cb_emit_accept_line_or_col ((yyvsp[(1) - (3)]), 1);
  ;}
    break;

  case 693:

/* Line 1455 of yacc.c  */
#line 3987 "parser.y"
    {
	cb_emit_accept_date ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 694:

/* Line 1455 of yacc.c  */
#line 3991 "parser.y"
    {
	cb_emit_accept_date_yyyymmdd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 695:

/* Line 1455 of yacc.c  */
#line 3995 "parser.y"
    {
	cb_emit_accept_day ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 696:

/* Line 1455 of yacc.c  */
#line 3999 "parser.y"
    {
	cb_emit_accept_day_yyyyddd ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 697:

/* Line 1455 of yacc.c  */
#line 4003 "parser.y"
    {
	cb_emit_accept_day_of_week ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 698:

/* Line 1455 of yacc.c  */
#line 4007 "parser.y"
    {
	cb_emit_accept_time ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 699:

/* Line 1455 of yacc.c  */
#line 4011 "parser.y"
    {
	cb_emit_accept_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 700:

/* Line 1455 of yacc.c  */
#line 4015 "parser.y"
    {
	cb_emit_accept_environment ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 701:

/* Line 1455 of yacc.c  */
#line 4019 "parser.y"
    { 
	cb_emit_get_environment ((yyvsp[(4) - (5)]), (yyvsp[(1) - (5)]));
  ;}
    break;

  case 702:

/* Line 1455 of yacc.c  */
#line 4023 "parser.y"
    {
	cb_emit_accept_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 703:

/* Line 1455 of yacc.c  */
#line 4027 "parser.y"
    {
	cb_emit_accept_arg_value ((yyvsp[(1) - (4)]));
  ;}
    break;

  case 704:

/* Line 1455 of yacc.c  */
#line 4031 "parser.y"
    {
	cb_emit_accept_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 705:

/* Line 1455 of yacc.c  */
#line 4035 "parser.y"
    {
	cb_emit_accept_name ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 706:

/* Line 1455 of yacc.c  */
#line 4041 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 707:

/* Line 1455 of yacc.c  */
#line 4042 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 708:

/* Line 1455 of yacc.c  */
#line 4043 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); ;}
    break;

  case 709:

/* Line 1455 of yacc.c  */
#line 4044 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), NULL); ;}
    break;

  case 710:

/* Line 1455 of yacc.c  */
#line 4045 "parser.y"
    { (yyval) = cb_build_pair (NULL, (yyvsp[(2) - (2)])); ;}
    break;

  case 711:

/* Line 1455 of yacc.c  */
#line 4046 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 712:

/* Line 1455 of yacc.c  */
#line 4050 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 713:

/* Line 1455 of yacc.c  */
#line 4054 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 714:

/* Line 1455 of yacc.c  */
#line 4055 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 719:

/* Line 1455 of yacc.c  */
#line 4068 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 720:

/* Line 1455 of yacc.c  */
#line 4069 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 721:

/* Line 1455 of yacc.c  */
#line 4070 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 722:

/* Line 1455 of yacc.c  */
#line 4071 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 723:

/* Line 1455 of yacc.c  */
#line 4072 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 724:

/* Line 1455 of yacc.c  */
#line 4073 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 725:

/* Line 1455 of yacc.c  */
#line 4074 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 726:

/* Line 1455 of yacc.c  */
#line 4076 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 727:

/* Line 1455 of yacc.c  */
#line 4080 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 728:

/* Line 1455 of yacc.c  */
#line 4084 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 729:

/* Line 1455 of yacc.c  */
#line 4088 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 730:

/* Line 1455 of yacc.c  */
#line 4092 "parser.y"
    { dispattrs |= COB_SCREEN_AUTO; ;}
    break;

  case 731:

/* Line 1455 of yacc.c  */
#line 4093 "parser.y"
    { dispattrs |= COB_SCREEN_FULL; ;}
    break;

  case 732:

/* Line 1455 of yacc.c  */
#line 4094 "parser.y"
    { dispattrs |= COB_SCREEN_REQUIRED; ;}
    break;

  case 733:

/* Line 1455 of yacc.c  */
#line 4095 "parser.y"
    { dispattrs |= COB_SCREEN_SECURE; ;}
    break;

  case 734:

/* Line 1455 of yacc.c  */
#line 4096 "parser.y"
    { dispattrs |= COB_SCREEN_UPDATE; ;}
    break;

  case 735:

/* Line 1455 of yacc.c  */
#line 4097 "parser.y"
    { dispattrs |= COB_SCREEN_PROMPT; ;}
    break;

  case 736:

/* Line 1455 of yacc.c  */
#line 4101 "parser.y"
    { terminator_warning (TERM_ACCEPT); ;}
    break;

  case 737:

/* Line 1455 of yacc.c  */
#line 4102 "parser.y"
    { terminator_clear (TERM_ACCEPT); ;}
    break;

  case 738:

/* Line 1455 of yacc.c  */
#line 4111 "parser.y"
    { BEGIN_STATEMENT ("ADD", TERM_ADD); ;}
    break;

  case 740:

/* Line 1455 of yacc.c  */
#line 4118 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '+', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 741:

/* Line 1455 of yacc.c  */
#line 4122 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(4) - (5)]), 0, cb_build_binary_list ((yyvsp[(1) - (5)]), '+'));
  ;}
    break;

  case 742:

/* Line 1455 of yacc.c  */
#line 4126 "parser.y"
    {
	cb_emit_corresponding (cb_build_add, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 744:

/* Line 1455 of yacc.c  */
#line 4132 "parser.y"
    { cb_list_add ((yyvsp[(0) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 745:

/* Line 1455 of yacc.c  */
#line 4136 "parser.y"
    { terminator_warning (TERM_ADD); ;}
    break;

  case 746:

/* Line 1455 of yacc.c  */
#line 4137 "parser.y"
    { terminator_clear (TERM_ADD); ;}
    break;

  case 747:

/* Line 1455 of yacc.c  */
#line 4146 "parser.y"
    { BEGIN_STATEMENT ("ALLOCATE", 0); ;}
    break;

  case 749:

/* Line 1455 of yacc.c  */
#line 4152 "parser.y"
    {
	cb_emit_allocate ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), NULL, (yyvsp[(2) - (3)]));
  ;}
    break;

  case 750:

/* Line 1455 of yacc.c  */
#line 4156 "parser.y"
    {
	cb_emit_allocate (NULL, (yyvsp[(5) - (5)]), (yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]));
  ;}
    break;

  case 751:

/* Line 1455 of yacc.c  */
#line 4162 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 752:

/* Line 1455 of yacc.c  */
#line 4163 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 753:

/* Line 1455 of yacc.c  */
#line 4173 "parser.y"
    {
	cb_error (_("ALTER statement is obsolete and unsupported"));
  ;}
    break;

  case 758:

/* Line 1455 of yacc.c  */
#line 4191 "parser.y"
    { BEGIN_STATEMENT ("CALL", TERM_CALL); ;}
    break;

  case 759:

/* Line 1455 of yacc.c  */
#line 4195 "parser.y"
    {
	cb_emit_call ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 760:

/* Line 1455 of yacc.c  */
#line 4201 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 761:

/* Line 1455 of yacc.c  */
#line 4203 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 762:

/* Line 1455 of yacc.c  */
#line 4207 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 763:

/* Line 1455 of yacc.c  */
#line 4211 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 764:

/* Line 1455 of yacc.c  */
#line 4213 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 765:

/* Line 1455 of yacc.c  */
#line 4218 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OMITTED only allowed with BY REFERENCE"));
	}
	(yyval) = cb_build_pair (cb_int (call_mode), cb_null);
  ;}
    break;

  case 766:

/* Line 1455 of yacc.c  */
#line 4225 "parser.y"
    {
	(yyval) = cb_build_pair (cb_int (call_mode), (yyvsp[(3) - (3)]));
	CB_SIZES ((yyval)) = size_mode;
  ;}
    break;

  case 768:

/* Line 1455 of yacc.c  */
#line 4234 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 769:

/* Line 1455 of yacc.c  */
#line 4238 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY CONTENT not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_CONTENT;
	}
  ;}
    break;

  case 770:

/* Line 1455 of yacc.c  */
#line 4246 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 771:

/* Line 1455 of yacc.c  */
#line 4256 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 772:

/* Line 1455 of yacc.c  */
#line 4257 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 773:

/* Line 1455 of yacc.c  */
#line 4258 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 774:

/* Line 1455 of yacc.c  */
#line 4263 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 775:

/* Line 1455 of yacc.c  */
#line 4267 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 776:

/* Line 1455 of yacc.c  */
#line 4271 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 777:

/* Line 1455 of yacc.c  */
#line 4278 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 778:

/* Line 1455 of yacc.c  */
#line 4282 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 779:

/* Line 1455 of yacc.c  */
#line 4286 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 780:

/* Line 1455 of yacc.c  */
#line 4292 "parser.y"
    { terminator_warning (TERM_CALL); ;}
    break;

  case 781:

/* Line 1455 of yacc.c  */
#line 4293 "parser.y"
    { terminator_clear (TERM_CALL); ;}
    break;

  case 782:

/* Line 1455 of yacc.c  */
#line 4302 "parser.y"
    { BEGIN_STATEMENT ("CANCEL", 0); ;}
    break;

  case 785:

/* Line 1455 of yacc.c  */
#line 4308 "parser.y"
    {
	cb_emit_cancel ((yyvsp[(2) - (2)]));
  ;}
    break;

  case 786:

/* Line 1455 of yacc.c  */
#line 4319 "parser.y"
    { BEGIN_STATEMENT ("CLOSE", 0); ;}
    break;

  case 789:

/* Line 1455 of yacc.c  */
#line 4326 "parser.y"
    {
	BEGIN_IMPLICIT_STATEMENT ((yyvsp[(2) - (3)]));
	if ((yyvsp[(2) - (3)]) != cb_error_node) {
		cb_emit_close ((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
	}
  ;}
    break;

  case 790:

/* Line 1455 of yacc.c  */
#line 4335 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NORMAL); ;}
    break;

  case 791:

/* Line 1455 of yacc.c  */
#line 4336 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT); ;}
    break;

  case 792:

/* Line 1455 of yacc.c  */
#line 4337 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_UNIT_REMOVAL); ;}
    break;

  case 793:

/* Line 1455 of yacc.c  */
#line 4338 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_NO_REWIND); ;}
    break;

  case 794:

/* Line 1455 of yacc.c  */
#line 4339 "parser.y"
    { (yyval) = cb_int (COB_CLOSE_LOCK); ;}
    break;

  case 797:

/* Line 1455 of yacc.c  */
#line 4350 "parser.y"
    { BEGIN_STATEMENT ("COMPUTE", TERM_COMPUTE); ;}
    break;

  case 799:

/* Line 1455 of yacc.c  */
#line 4357 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(1) - (4)]), 0, (yyvsp[(3) - (4)]));
  ;}
    break;

  case 800:

/* Line 1455 of yacc.c  */
#line 4363 "parser.y"
    { terminator_warning (TERM_COMPUTE); ;}
    break;

  case 801:

/* Line 1455 of yacc.c  */
#line 4364 "parser.y"
    { terminator_clear (TERM_COMPUTE); ;}
    break;

  case 804:

/* Line 1455 of yacc.c  */
#line 4375 "parser.y"
    {
	BEGIN_STATEMENT ("COMMIT", 0);
	cb_emit_commit ();
  ;}
    break;

  case 805:

/* Line 1455 of yacc.c  */
#line 4388 "parser.y"
    {
	BEGIN_STATEMENT ("CONTINUE", 0);
	cb_emit_continue ();
  ;}
    break;

  case 806:

/* Line 1455 of yacc.c  */
#line 4400 "parser.y"
    { BEGIN_STATEMENT ("DELETE", TERM_DELETE); ;}
    break;

  case 807:

/* Line 1455 of yacc.c  */
#line 4403 "parser.y"
    {
	if ((yyvsp[(3) - (6)]) != cb_error_node) {
		cb_emit_delete ((yyvsp[(3) - (6)]));
	}
  ;}
    break;

  case 808:

/* Line 1455 of yacc.c  */
#line 4411 "parser.y"
    { terminator_warning (TERM_DELETE); ;}
    break;

  case 809:

/* Line 1455 of yacc.c  */
#line 4412 "parser.y"
    { terminator_clear (TERM_DELETE); ;}
    break;

  case 810:

/* Line 1455 of yacc.c  */
#line 4421 "parser.y"
    { BEGIN_STATEMENT ("DELETE-FILE", 0); ;}
    break;

  case 811:

/* Line 1455 of yacc.c  */
#line 4423 "parser.y"
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

  case 812:

/* Line 1455 of yacc.c  */
#line 4441 "parser.y"
    {
	BEGIN_STATEMENT ("DISPLAY", TERM_DISPLAY);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 814:

/* Line 1455 of yacc.c  */
#line 4454 "parser.y"
    {
	cb_emit_env_name ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 815:

/* Line 1455 of yacc.c  */
#line 4458 "parser.y"
    {
	cb_emit_env_value ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 816:

/* Line 1455 of yacc.c  */
#line 4462 "parser.y"
    {
	cb_emit_arg_number ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 817:

/* Line 1455 of yacc.c  */
#line 4466 "parser.y"
    {
	cb_emit_command_line ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 818:

/* Line 1455 of yacc.c  */
#line 4470 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (4)]), cb_int0, (yyvsp[(3) - (4)]), (yyvsp[(2) - (4)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 819:

/* Line 1455 of yacc.c  */
#line 4474 "parser.y"
    {
	cb_emit_display_mnemonic ((yyvsp[(1) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 820:

/* Line 1455 of yacc.c  */
#line 4478 "parser.y"
    {
	cb_tree word = cb_build_display_upon_direct ((yyvsp[(4) - (6)]));
	cb_emit_display ((yyvsp[(1) - (6)]), word, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 821:

/* Line 1455 of yacc.c  */
#line 4483 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 822:

/* Line 1455 of yacc.c  */
#line 4487 "parser.y"
    {
	cb_emit_display ((yyvsp[(1) - (6)]), cb_int0, (yyvsp[(5) - (6)]), (yyvsp[(2) - (6)]), fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 823:

/* Line 1455 of yacc.c  */
#line 4493 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 824:

/* Line 1455 of yacc.c  */
#line 4494 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 825:

/* Line 1455 of yacc.c  */
#line 4495 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 828:

/* Line 1455 of yacc.c  */
#line 4505 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 829:

/* Line 1455 of yacc.c  */
#line 4506 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 830:

/* Line 1455 of yacc.c  */
#line 4507 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 831:

/* Line 1455 of yacc.c  */
#line 4508 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 832:

/* Line 1455 of yacc.c  */
#line 4509 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 833:

/* Line 1455 of yacc.c  */
#line 4510 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 834:

/* Line 1455 of yacc.c  */
#line 4511 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 835:

/* Line 1455 of yacc.c  */
#line 4512 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 836:

/* Line 1455 of yacc.c  */
#line 4513 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 837:

/* Line 1455 of yacc.c  */
#line 4515 "parser.y"
    {
	fgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 838:

/* Line 1455 of yacc.c  */
#line 4519 "parser.y"
    {
	bgc = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 839:

/* Line 1455 of yacc.c  */
#line 4523 "parser.y"
    {
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 840:

/* Line 1455 of yacc.c  */
#line 4527 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 841:

/* Line 1455 of yacc.c  */
#line 4531 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 842:

/* Line 1455 of yacc.c  */
#line 4532 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 843:

/* Line 1455 of yacc.c  */
#line 4536 "parser.y"
    { terminator_warning (TERM_DISPLAY); ;}
    break;

  case 844:

/* Line 1455 of yacc.c  */
#line 4537 "parser.y"
    { terminator_clear (TERM_DISPLAY); ;}
    break;

  case 845:

/* Line 1455 of yacc.c  */
#line 4546 "parser.y"
    { BEGIN_STATEMENT ("DIVIDE", TERM_DIVIDE); ;}
    break;

  case 847:

/* Line 1455 of yacc.c  */
#line 4553 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '/', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 848:

/* Line 1455 of yacc.c  */
#line 4557 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(3) - (6)]), '/', (yyvsp[(1) - (6)])));
  ;}
    break;

  case 849:

/* Line 1455 of yacc.c  */
#line 4561 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '/', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 850:

/* Line 1455 of yacc.c  */
#line 4565 "parser.y"
    {
	cb_emit_divide ((yyvsp[(3) - (8)]), (yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 851:

/* Line 1455 of yacc.c  */
#line 4569 "parser.y"
    {
	cb_emit_divide ((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 852:

/* Line 1455 of yacc.c  */
#line 4575 "parser.y"
    { terminator_warning (TERM_DIVIDE); ;}
    break;

  case 853:

/* Line 1455 of yacc.c  */
#line 4576 "parser.y"
    { terminator_clear (TERM_DIVIDE); ;}
    break;

  case 854:

/* Line 1455 of yacc.c  */
#line 4585 "parser.y"
    { BEGIN_STATEMENT ("ENTRY", 0); ;}
    break;

  case 855:

/* Line 1455 of yacc.c  */
#line 4587 "parser.y"
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

  case 856:

/* Line 1455 of yacc.c  */
#line 4607 "parser.y"
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

  case 857:

/* Line 1455 of yacc.c  */
#line 4618 "parser.y"
    {
	cb_emit_evaluate ((yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]));
	eval_level--;
  ;}
    break;

  case 858:

/* Line 1455 of yacc.c  */
#line 4625 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 859:

/* Line 1455 of yacc.c  */
#line 4628 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 860:

/* Line 1455 of yacc.c  */
#line 4638 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE_P ((yyvsp[(1) - (1)]))) {
		eval_check[eval_level][eval_inc++] = 0;
	} else {
		eval_check[eval_level][eval_inc++] = 1;
	}
  ;}
    break;

  case 861:

/* Line 1455 of yacc.c  */
#line 4647 "parser.y"
    {
	(yyval) = cb_true;
	eval_check[eval_level][eval_inc++] = 2;
  ;}
    break;

  case 862:

/* Line 1455 of yacc.c  */
#line 4652 "parser.y"
    {
	(yyval) = cb_false;
	eval_check[eval_level][eval_inc++] = 3;
  ;}
    break;

  case 863:

/* Line 1455 of yacc.c  */
#line 4660 "parser.y"
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

  case 864:

/* Line 1455 of yacc.c  */
#line 4688 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 865:

/* Line 1455 of yacc.c  */
#line 4690 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 866:

/* Line 1455 of yacc.c  */
#line 4695 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 867:

/* Line 1455 of yacc.c  */
#line 4699 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]));
	eval_inc2 = 0;
  ;}
    break;

  case 868:

/* Line 1455 of yacc.c  */
#line 4710 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 869:

/* Line 1455 of yacc.c  */
#line 4714 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 870:

/* Line 1455 of yacc.c  */
#line 4718 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = cb_cons ((yyvsp[(3) - (3)]), NULL);
	eval_inc2 = 0;
  ;}
    break;

  case 871:

/* Line 1455 of yacc.c  */
#line 4728 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 872:

/* Line 1455 of yacc.c  */
#line 4730 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 873:

/* Line 1455 of yacc.c  */
#line 4734 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 874:

/* Line 1455 of yacc.c  */
#line 4737 "parser.y"
    {
 	if (!cb_allow_missing_also_clause_in_evaluate && (yyvsp[(2) - (3)]) != cb_int1) {
 		cb_error  (_("Invalid expression"));
 	}
 	(yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 875:

/* Line 1455 of yacc.c  */
#line 4747 "parser.y"
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

  case 876:

/* Line 1455 of yacc.c  */
#line 4775 "parser.y"
    { (yyval) = cb_any; eval_inc2++; ;}
    break;

  case 877:

/* Line 1455 of yacc.c  */
#line 4776 "parser.y"
    { (yyval) = cb_true; eval_inc2++; ;}
    break;

  case 878:

/* Line 1455 of yacc.c  */
#line 4777 "parser.y"
    { (yyval) = cb_false; eval_inc2++; ;}
    break;

  case 879:

/* Line 1455 of yacc.c  */
#line 4780 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 880:

/* Line 1455 of yacc.c  */
#line 4781 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 881:

/* Line 1455 of yacc.c  */
#line 4785 "parser.y"
    { terminator_warning (TERM_EVALUATE); ;}
    break;

  case 882:

/* Line 1455 of yacc.c  */
#line 4786 "parser.y"
    { terminator_clear (TERM_EVALUATE); ;}
    break;

  case 883:

/* Line 1455 of yacc.c  */
#line 4795 "parser.y"
    { BEGIN_STATEMENT ("EXIT", 0); ;}
    break;

  case 885:

/* Line 1455 of yacc.c  */
#line 4800 "parser.y"
    { /* nothing */ ;}
    break;

  case 886:

/* Line 1455 of yacc.c  */
#line 4802 "parser.y"
    {
	if (in_declaratives && use_global_ind) {
		cb_error (_("EXIT PROGRAM is not allowed within a USE GLOBAL procedure"));
	}
	check_unreached = 1;
	cb_emit_exit (0);
  ;}
    break;

  case 887:

/* Line 1455 of yacc.c  */
#line 4810 "parser.y"
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

  case 888:

/* Line 1455 of yacc.c  */
#line 4827 "parser.y"
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

  case 889:

/* Line 1455 of yacc.c  */
#line 4844 "parser.y"
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

  case 890:

/* Line 1455 of yacc.c  */
#line 4862 "parser.y"
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

  case 891:

/* Line 1455 of yacc.c  */
#line 4886 "parser.y"
    { BEGIN_STATEMENT ("FREE", 0); ;}
    break;

  case 892:

/* Line 1455 of yacc.c  */
#line 4888 "parser.y"
    {
	cb_emit_free ((yyvsp[(3) - (3)]));
  ;}
    break;

  case 893:

/* Line 1455 of yacc.c  */
#line 4899 "parser.y"
    { BEGIN_STATEMENT ("GENERATE", 0); ;}
    break;

  case 894:

/* Line 1455 of yacc.c  */
#line 4901 "parser.y"
    {
	PENDING("GENERATE");
  ;}
    break;

  case 895:

/* Line 1455 of yacc.c  */
#line 4912 "parser.y"
    { BEGIN_STATEMENT ("GO TO", 0); ;}
    break;

  case 896:

/* Line 1455 of yacc.c  */
#line 4914 "parser.y"
    {
	cb_emit_goto ((yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 897:

/* Line 1455 of yacc.c  */
#line 4921 "parser.y"
    {
	check_unreached = 1;
	(yyval) = NULL;
  ;}
    break;

  case 898:

/* Line 1455 of yacc.c  */
#line 4926 "parser.y"
    {
	check_unreached = 0;
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 899:

/* Line 1455 of yacc.c  */
#line 4938 "parser.y"
    { BEGIN_STATEMENT ("GOBACK", 0); ;}
    break;

  case 900:

/* Line 1455 of yacc.c  */
#line 4939 "parser.y"
    {
	check_unreached = 1;
	cb_emit_exit (1);
  ;}
    break;

  case 901:

/* Line 1455 of yacc.c  */
#line 4951 "parser.y"
    { BEGIN_STATEMENT ("IF", TERM_IF); ;}
    break;

  case 902:

/* Line 1455 of yacc.c  */
#line 4953 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 903:

/* Line 1455 of yacc.c  */
#line 4958 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(6) - (8)]) == NULL) {
		cb_error (_("syntax error"));
	}
	cb_emit_if ((yyvsp[(3) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]));
  ;}
    break;

  case 905:

/* Line 1455 of yacc.c  */
#line 4969 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 906:

/* Line 1455 of yacc.c  */
#line 4973 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 907:

/* Line 1455 of yacc.c  */
#line 4977 "parser.y"
    {
	if (!cb_allow_empty_imperative_statement && (yyvsp[(3) - (3)]) == NULL) {
		cb_error (_("syntax error"));
	}
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 908:

/* Line 1455 of yacc.c  */
#line 4986 "parser.y"
    { terminator_warning (TERM_IF); ;}
    break;

  case 909:

/* Line 1455 of yacc.c  */
#line 4987 "parser.y"
    { terminator_clear (TERM_IF); ;}
    break;

  case 910:

/* Line 1455 of yacc.c  */
#line 4996 "parser.y"
    { BEGIN_STATEMENT ("INITIALIZE", 0); ;}
    break;

  case 911:

/* Line 1455 of yacc.c  */
#line 4998 "parser.y"
    {
	cb_emit_initialize ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 912:

/* Line 1455 of yacc.c  */
#line 5004 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 913:

/* Line 1455 of yacc.c  */
#line 5005 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 914:

/* Line 1455 of yacc.c  */
#line 5009 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 915:

/* Line 1455 of yacc.c  */
#line 5010 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 916:

/* Line 1455 of yacc.c  */
#line 5011 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 917:

/* Line 1455 of yacc.c  */
#line 5015 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 918:

/* Line 1455 of yacc.c  */
#line 5017 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 919:

/* Line 1455 of yacc.c  */
#line 5021 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 920:

/* Line 1455 of yacc.c  */
#line 5023 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 921:

/* Line 1455 of yacc.c  */
#line 5027 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 922:

/* Line 1455 of yacc.c  */
#line 5031 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHABETIC); ;}
    break;

  case 923:

/* Line 1455 of yacc.c  */
#line 5032 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC); ;}
    break;

  case 924:

/* Line 1455 of yacc.c  */
#line 5033 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC); ;}
    break;

  case 925:

/* Line 1455 of yacc.c  */
#line 5034 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_ALPHANUMERIC_EDITED); ;}
    break;

  case 926:

/* Line 1455 of yacc.c  */
#line 5035 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NUMERIC_EDITED); ;}
    break;

  case 927:

/* Line 1455 of yacc.c  */
#line 5036 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL); ;}
    break;

  case 928:

/* Line 1455 of yacc.c  */
#line 5037 "parser.y"
    { (yyval) = cb_int (CB_CATEGORY_NATIONAL_EDITED); ;}
    break;

  case 929:

/* Line 1455 of yacc.c  */
#line 5041 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 930:

/* Line 1455 of yacc.c  */
#line 5042 "parser.y"
    { (yyval) = cb_true; ;}
    break;

  case 931:

/* Line 1455 of yacc.c  */
#line 5051 "parser.y"
    { BEGIN_STATEMENT ("INITIATE", 0); ;}
    break;

  case 932:

/* Line 1455 of yacc.c  */
#line 5053 "parser.y"
    {
	PENDING("INITIATE");
  ;}
    break;

  case 933:

/* Line 1455 of yacc.c  */
#line 5064 "parser.y"
    {
	BEGIN_STATEMENT ("INSPECT", 0);
	sending_id = 0;
	inspect_keyword = 0;
  ;}
    break;

  case 935:

/* Line 1455 of yacc.c  */
#line 5073 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 0; ;}
    break;

  case 936:

/* Line 1455 of yacc.c  */
#line 5074 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 937:

/* Line 1455 of yacc.c  */
#line 5075 "parser.y"
    { save_tree_1 = (yyvsp[(1) - (1)]); sending_id = 1; ;}
    break;

  case 940:

/* Line 1455 of yacc.c  */
#line 5084 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 0); ;}
    break;

  case 941:

/* Line 1455 of yacc.c  */
#line 5085 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int1, 1); ;}
    break;

  case 942:

/* Line 1455 of yacc.c  */
#line 5086 "parser.y"
    { cb_emit_inspect (save_tree_1, (yyvsp[(1) - (1)]), cb_int0, 2); ;}
    break;

  case 943:

/* Line 1455 of yacc.c  */
#line 5092 "parser.y"
    { cb_init_tarrying (); ;}
    break;

  case 944:

/* Line 1455 of yacc.c  */
#line 5093 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 945:

/* Line 1455 of yacc.c  */
#line 5097 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 946:

/* Line 1455 of yacc.c  */
#line 5098 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 947:

/* Line 1455 of yacc.c  */
#line 5102 "parser.y"
    { (yyval) = cb_build_tarrying_data ((yyvsp[(1) - (2)])); ;}
    break;

  case 948:

/* Line 1455 of yacc.c  */
#line 5103 "parser.y"
    { (yyval) = cb_build_tarrying_characters ((yyvsp[(2) - (2)])); ;}
    break;

  case 949:

/* Line 1455 of yacc.c  */
#line 5104 "parser.y"
    { (yyval) = cb_build_tarrying_all (); ;}
    break;

  case 950:

/* Line 1455 of yacc.c  */
#line 5105 "parser.y"
    { (yyval) = cb_build_tarrying_leading (); ;}
    break;

  case 951:

/* Line 1455 of yacc.c  */
#line 5106 "parser.y"
    { (yyval) = cb_build_tarrying_trailing (); ;}
    break;

  case 952:

/* Line 1455 of yacc.c  */
#line 5107 "parser.y"
    { (yyval) = cb_build_tarrying_value ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 953:

/* Line 1455 of yacc.c  */
#line 5113 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); inspect_keyword = 0; ;}
    break;

  case 954:

/* Line 1455 of yacc.c  */
#line 5117 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 955:

/* Line 1455 of yacc.c  */
#line 5118 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 956:

/* Line 1455 of yacc.c  */
#line 5123 "parser.y"
    {
	(yyval) = cb_build_replacing_characters ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]), save_tree_1);
	inspect_keyword = 0;
  ;}
    break;

  case 957:

/* Line 1455 of yacc.c  */
#line 5127 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 958:

/* Line 1455 of yacc.c  */
#line 5131 "parser.y"
    { /* Nothing */ ;}
    break;

  case 959:

/* Line 1455 of yacc.c  */
#line 5132 "parser.y"
    { inspect_keyword = 1; ;}
    break;

  case 960:

/* Line 1455 of yacc.c  */
#line 5133 "parser.y"
    { inspect_keyword = 2; ;}
    break;

  case 961:

/* Line 1455 of yacc.c  */
#line 5134 "parser.y"
    { inspect_keyword = 3; ;}
    break;

  case 962:

/* Line 1455 of yacc.c  */
#line 5135 "parser.y"
    { inspect_keyword = 4; ;}
    break;

  case 963:

/* Line 1455 of yacc.c  */
#line 5140 "parser.y"
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

  case 964:

/* Line 1455 of yacc.c  */
#line 5166 "parser.y"
    {
	if (cb_validate_inspect (save_tree_1, (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])) < 0 ) {
		(yyval) = cb_error_node;
	} else {
		(yyval) = cb_build_converting ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
	}
  ;}
    break;

  case 965:

/* Line 1455 of yacc.c  */
#line 5178 "parser.y"
    { (yyval) = cb_build_inspect_region_start (); ;}
    break;

  case 966:

/* Line 1455 of yacc.c  */
#line 5180 "parser.y"
    { (yyval) = cb_build_inspect_region ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 969:

/* Line 1455 of yacc.c  */
#line 5191 "parser.y"
    { BEGIN_STATEMENT ("MERGE", 0); ;}
    break;

  case 971:

/* Line 1455 of yacc.c  */
#line 5201 "parser.y"
    { BEGIN_STATEMENT ("MOVE", 0); ;}
    break;

  case 973:

/* Line 1455 of yacc.c  */
#line 5207 "parser.y"
    {
	cb_emit_move ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 974:

/* Line 1455 of yacc.c  */
#line 5211 "parser.y"
    {
	cb_emit_move_corresponding ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 975:

/* Line 1455 of yacc.c  */
#line 5222 "parser.y"
    { BEGIN_STATEMENT ("MULTIPLY", TERM_MULTIPLY); ;}
    break;

  case 977:

/* Line 1455 of yacc.c  */
#line 5229 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '*', (yyvsp[(1) - (4)]));
  ;}
    break;

  case 978:

/* Line 1455 of yacc.c  */
#line 5233 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_op ((yyvsp[(1) - (6)]), '*', (yyvsp[(3) - (6)])));
  ;}
    break;

  case 979:

/* Line 1455 of yacc.c  */
#line 5239 "parser.y"
    { terminator_warning (TERM_MULTIPLY); ;}
    break;

  case 980:

/* Line 1455 of yacc.c  */
#line 5240 "parser.y"
    { terminator_clear (TERM_MULTIPLY); ;}
    break;

  case 981:

/* Line 1455 of yacc.c  */
#line 5249 "parser.y"
    { BEGIN_STATEMENT ("OPEN", 0); ;}
    break;

  case 984:

/* Line 1455 of yacc.c  */
#line 5256 "parser.y"
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

  case 985:

/* Line 1455 of yacc.c  */
#line 5268 "parser.y"
    { (yyval) = cb_int (COB_OPEN_INPUT); ;}
    break;

  case 986:

/* Line 1455 of yacc.c  */
#line 5269 "parser.y"
    { (yyval) = cb_int (COB_OPEN_OUTPUT); ;}
    break;

  case 987:

/* Line 1455 of yacc.c  */
#line 5270 "parser.y"
    { (yyval) = cb_int (COB_OPEN_I_O); ;}
    break;

  case 988:

/* Line 1455 of yacc.c  */
#line 5271 "parser.y"
    { (yyval) = cb_int (COB_OPEN_EXTEND); ;}
    break;

  case 989:

/* Line 1455 of yacc.c  */
#line 5275 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 990:

/* Line 1455 of yacc.c  */
#line 5276 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 991:

/* Line 1455 of yacc.c  */
#line 5280 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 992:

/* Line 1455 of yacc.c  */
#line 5281 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 993:

/* Line 1455 of yacc.c  */
#line 5282 "parser.y"
    { PENDING ("OPEN ... WITH LOCK"); ;}
    break;

  case 994:

/* Line 1455 of yacc.c  */
#line 5294 "parser.y"
    { BEGIN_STATEMENT ("PERFORM", TERM_PERFORM); ;}
    break;

  case 996:

/* Line 1455 of yacc.c  */
#line 5300 "parser.y"
    {
	cb_emit_perform ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));
  ;}
    break;

  case 997:

/* Line 1455 of yacc.c  */
#line 5304 "parser.y"
    {
	perform_stack = cb_cons ((yyvsp[(1) - (1)]), perform_stack);
	check_unreached = 0;
  ;}
    break;

  case 998:

/* Line 1455 of yacc.c  */
#line 5309 "parser.y"
    {
	perform_stack = CB_CHAIN (perform_stack);
	cb_emit_perform ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 999:

/* Line 1455 of yacc.c  */
#line 5314 "parser.y"
    {
	cb_emit_perform ((yyvsp[(1) - (2)]), NULL);
  ;}
    break;

  case 1000:

/* Line 1455 of yacc.c  */
#line 5320 "parser.y"
    { terminator_error (); ;}
    break;

  case 1001:

/* Line 1455 of yacc.c  */
#line 5321 "parser.y"
    { terminator_clear (TERM_PERFORM); ;}
    break;

  case 1002:

/* Line 1455 of yacc.c  */
#line 5326 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(1) - (1)]))->length = cb_true; /* return from $1 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (1)]), (yyvsp[(1) - (1)]));
  ;}
    break;

  case 1003:

/* Line 1455 of yacc.c  */
#line 5331 "parser.y"
    {
	CB_REFERENCE ((yyvsp[(3) - (3)]))->length = cb_true; /* return from $3 */
	(yyval) = cb_build_pair ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1004:

/* Line 1455 of yacc.c  */
#line 5339 "parser.y"
    {
	(yyval) = cb_build_perform_once (NULL);
  ;}
    break;

  case 1005:

/* Line 1455 of yacc.c  */
#line 5343 "parser.y"
    {
	(yyval) = cb_build_perform_forever (NULL);
  ;}
    break;

  case 1006:

/* Line 1455 of yacc.c  */
#line 5347 "parser.y"
    {
	(yyval) = cb_build_perform_times ((yyvsp[(1) - (2)]));
	current_program->loop_counter++;
  ;}
    break;

  case 1007:

/* Line 1455 of yacc.c  */
#line 5352 "parser.y"
    {
	cb_tree varying;

	varying = cb_list_init (cb_build_perform_varying (NULL, NULL, NULL, (yyvsp[(3) - (3)])));
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), varying);
  ;}
    break;

  case 1008:

/* Line 1455 of yacc.c  */
#line 5359 "parser.y"
    {
	(yyval) = cb_build_perform_until ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1009:

/* Line 1455 of yacc.c  */
#line 5365 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1010:

/* Line 1455 of yacc.c  */
#line 5366 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1011:

/* Line 1455 of yacc.c  */
#line 5370 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1012:

/* Line 1455 of yacc.c  */
#line 5372 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1013:

/* Line 1455 of yacc.c  */
#line 5377 "parser.y"
    {
	(yyval) = cb_build_perform_varying ((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1014:

/* Line 1455 of yacc.c  */
#line 5388 "parser.y"
    { BEGIN_STATEMENT ("READ", TERM_READ); ;}
    break;

  case 1015:

/* Line 1455 of yacc.c  */
#line 5391 "parser.y"
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

  case 1016:

/* Line 1455 of yacc.c  */
#line 5411 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1017:

/* Line 1455 of yacc.c  */
#line 5412 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1018:

/* Line 1455 of yacc.c  */
#line 5416 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1019:

/* Line 1455 of yacc.c  */
#line 5418 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1020:

/* Line 1455 of yacc.c  */
#line 5422 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1021:

/* Line 1455 of yacc.c  */
#line 5426 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1022:

/* Line 1455 of yacc.c  */
#line 5430 "parser.y"
    {
	(yyval) = cb_int3;
  ;}
    break;

  case 1023:

/* Line 1455 of yacc.c  */
#line 5434 "parser.y"
    {
	(yyval) = cb_int4;
  ;}
    break;

  case 1024:

/* Line 1455 of yacc.c  */
#line 5440 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1025:

/* Line 1455 of yacc.c  */
#line 5442 "parser.y"
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

  case 1029:

/* Line 1455 of yacc.c  */
#line 5461 "parser.y"
    { terminator_warning (TERM_READ); ;}
    break;

  case 1030:

/* Line 1455 of yacc.c  */
#line 5462 "parser.y"
    { terminator_clear (TERM_READ); ;}
    break;

  case 1031:

/* Line 1455 of yacc.c  */
#line 5471 "parser.y"
    { BEGIN_STATEMENT ("RELEASE", 0); ;}
    break;

  case 1032:

/* Line 1455 of yacc.c  */
#line 5473 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_release ((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
	}
  ;}
    break;

  case 1033:

/* Line 1455 of yacc.c  */
#line 5486 "parser.y"
    { BEGIN_STATEMENT ("RETURN", TERM_RETURN); ;}
    break;

  case 1034:

/* Line 1455 of yacc.c  */
#line 5489 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_return ((yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]));
	}
  ;}
    break;

  case 1035:

/* Line 1455 of yacc.c  */
#line 5497 "parser.y"
    { terminator_warning (TERM_RETURN); ;}
    break;

  case 1036:

/* Line 1455 of yacc.c  */
#line 5498 "parser.y"
    { terminator_clear (TERM_RETURN); ;}
    break;

  case 1037:

/* Line 1455 of yacc.c  */
#line 5507 "parser.y"
    { BEGIN_STATEMENT ("REWRITE", TERM_REWRITE); ;}
    break;

  case 1038:

/* Line 1455 of yacc.c  */
#line 5510 "parser.y"
    {
	if ((yyvsp[(3) - (7)]) != cb_error_node) {
		cb_emit_rewrite ((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]));
	}
  ;}
    break;

  case 1039:

/* Line 1455 of yacc.c  */
#line 5518 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1040:

/* Line 1455 of yacc.c  */
#line 5520 "parser.y"
    {
	(yyval) = cb_int1;
  ;}
    break;

  case 1041:

/* Line 1455 of yacc.c  */
#line 5524 "parser.y"
    {
	(yyval) = cb_int2;
  ;}
    break;

  case 1042:

/* Line 1455 of yacc.c  */
#line 5530 "parser.y"
    { terminator_warning (TERM_REWRITE); ;}
    break;

  case 1043:

/* Line 1455 of yacc.c  */
#line 5531 "parser.y"
    { terminator_clear (TERM_REWRITE); ;}
    break;

  case 1044:

/* Line 1455 of yacc.c  */
#line 5541 "parser.y"
    {
	BEGIN_STATEMENT ("ROLLBACK", 0);
	cb_emit_rollback ();
  ;}
    break;

  case 1045:

/* Line 1455 of yacc.c  */
#line 5553 "parser.y"
    { BEGIN_STATEMENT ("SEARCH", TERM_SEARCH); ;}
    break;

  case 1047:

/* Line 1455 of yacc.c  */
#line 5560 "parser.y"
    {
	cb_emit_search ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1048:

/* Line 1455 of yacc.c  */
#line 5564 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1049:

/* Line 1455 of yacc.c  */
#line 5568 "parser.y"
    {
	cb_emit_search_all ((yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]));
  ;}
    break;

  case 1050:

/* Line 1455 of yacc.c  */
#line 5574 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1051:

/* Line 1455 of yacc.c  */
#line 5575 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1052:

/* Line 1455 of yacc.c  */
#line 5579 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1053:

/* Line 1455 of yacc.c  */
#line 5581 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1054:

/* Line 1455 of yacc.c  */
#line 5585 "parser.y"
    {
	(yyval) = (yyvsp[(4) - (4)]);
  ;}
    break;

  case 1055:

/* Line 1455 of yacc.c  */
#line 5591 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1056:

/* Line 1455 of yacc.c  */
#line 5592 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); CB_IF ((yyvsp[(1) - (2)]))->stmt2 = (yyvsp[(2) - (2)]); ;}
    break;

  case 1057:

/* Line 1455 of yacc.c  */
#line 5597 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1058:

/* Line 1455 of yacc.c  */
#line 5601 "parser.y"
    {
	(yyval) = cb_build_if ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), NULL);
  ;}
    break;

  case 1059:

/* Line 1455 of yacc.c  */
#line 5607 "parser.y"
    { terminator_warning (TERM_SEARCH); ;}
    break;

  case 1060:

/* Line 1455 of yacc.c  */
#line 5608 "parser.y"
    { terminator_clear (TERM_SEARCH); ;}
    break;

  case 1061:

/* Line 1455 of yacc.c  */
#line 5617 "parser.y"
    { BEGIN_STATEMENT ("SET", 0); ;}
    break;

  case 1068:

/* Line 1455 of yacc.c  */
#line 5633 "parser.y"
    {
	cb_emit_setenv ((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1069:

/* Line 1455 of yacc.c  */
#line 5642 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (4)]), cb_build_ppointer ((yyvsp[(4) - (4)])));
  ;}
    break;

  case 1070:

/* Line 1455 of yacc.c  */
#line 5646 "parser.y"
    {
	cb_emit_set_to ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1071:

/* Line 1455 of yacc.c  */
#line 5655 "parser.y"
    {
	cb_emit_set_up_down ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
  ;}
    break;

  case 1072:

/* Line 1455 of yacc.c  */
#line 5661 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1073:

/* Line 1455 of yacc.c  */
#line 5662 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1076:

/* Line 1455 of yacc.c  */
#line 5674 "parser.y"
    {
	cb_emit_set_on_off ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1079:

/* Line 1455 of yacc.c  */
#line 5688 "parser.y"
    {
	cb_emit_set_true ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1080:

/* Line 1455 of yacc.c  */
#line 5692 "parser.y"
    {
	cb_emit_set_false ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1081:

/* Line 1455 of yacc.c  */
#line 5703 "parser.y"
    { BEGIN_STATEMENT ("SORT", 0); ;}
    break;

  case 1083:

/* Line 1455 of yacc.c  */
#line 5709 "parser.y"
    {
	cb_emit_sort_init ((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]));
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (4)]))) && (yyvsp[(2) - (4)]) == NULL) {
		cb_error (_("File sort requires KEY phrase"));
	}
	/* used in sort_input/sort_output */
	save_tree_1 = (yyvsp[(1) - (4)]);
  ;}
    break;

  case 1084:

/* Line 1455 of yacc.c  */
#line 5718 "parser.y"
    {
	cb_emit_sort_finish ((yyvsp[(1) - (7)]));
  ;}
    break;

  case 1085:

/* Line 1455 of yacc.c  */
#line 5725 "parser.y"
    {
	(yyval) = NULL;
  ;}
    break;

  case 1086:

/* Line 1455 of yacc.c  */
#line 5730 "parser.y"
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

  case 1087:

/* Line 1455 of yacc.c  */
#line 5744 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1088:

/* Line 1455 of yacc.c  */
#line 5745 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1090:

/* Line 1455 of yacc.c  */
#line 5749 "parser.y"
    { /* nothing */ ;}
    break;

  case 1091:

/* Line 1455 of yacc.c  */
#line 5753 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1092:

/* Line 1455 of yacc.c  */
#line 5754 "parser.y"
    { (yyval) = cb_ref ((yyvsp[(3) - (3)])); ;}
    break;

  case 1093:

/* Line 1455 of yacc.c  */
#line 5759 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires USING or INPUT PROCEDURE"));
	}
  ;}
    break;

  case 1094:

/* Line 1455 of yacc.c  */
#line 5765 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("USING invalid with table SORT"));
	} else {
		cb_emit_sort_using (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1095:

/* Line 1455 of yacc.c  */
#line 5773 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("INPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_input ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1096:

/* Line 1455 of yacc.c  */
#line 5784 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires GIVING or OUTPUT PROCEDURE"));
	}
  ;}
    break;

  case 1097:

/* Line 1455 of yacc.c  */
#line 5790 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("GIVING invalid with table SORT"));
	} else {
		cb_emit_sort_giving (save_tree_1, (yyvsp[(2) - (2)]));
	}
  ;}
    break;

  case 1098:

/* Line 1455 of yacc.c  */
#line 5798 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("OUTPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_output ((yyvsp[(4) - (4)]), save_tree_1);
	}
  ;}
    break;

  case 1099:

/* Line 1455 of yacc.c  */
#line 5813 "parser.y"
    { BEGIN_STATEMENT ("START", TERM_START); ;}
    break;

  case 1100:

/* Line 1455 of yacc.c  */
#line 5814 "parser.y"
    { (yyval) = cb_int (COB_EQ); ;}
    break;

  case 1101:

/* Line 1455 of yacc.c  */
#line 5817 "parser.y"
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

  case 1102:

/* Line 1455 of yacc.c  */
#line 5834 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1103:

/* Line 1455 of yacc.c  */
#line 5836 "parser.y"
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

  case 1104:

/* Line 1455 of yacc.c  */
#line 5851 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_NE : COB_EQ); ;}
    break;

  case 1105:

/* Line 1455 of yacc.c  */
#line 5852 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LE : COB_GT); ;}
    break;

  case 1106:

/* Line 1455 of yacc.c  */
#line 5853 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GE : COB_LT); ;}
    break;

  case 1107:

/* Line 1455 of yacc.c  */
#line 5854 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_LT : COB_GE); ;}
    break;

  case 1108:

/* Line 1455 of yacc.c  */
#line 5855 "parser.y"
    { (yyval) = cb_int (((yyvsp[(1) - (2)]) == cb_int1) ? COB_GT : COB_LE); ;}
    break;

  case 1109:

/* Line 1455 of yacc.c  */
#line 5859 "parser.y"
    { terminator_warning (TERM_START); ;}
    break;

  case 1110:

/* Line 1455 of yacc.c  */
#line 5860 "parser.y"
    { terminator_clear (TERM_START); ;}
    break;

  case 1111:

/* Line 1455 of yacc.c  */
#line 5869 "parser.y"
    { BEGIN_STATEMENT ("STOP", 0); ;}
    break;

  case 1112:

/* Line 1455 of yacc.c  */
#line 5871 "parser.y"
    {
	cb_emit_stop_run ((yyvsp[(4) - (4)]));
  ;}
    break;

  case 1113:

/* Line 1455 of yacc.c  */
#line 5875 "parser.y"
    {
	cb_verify (cb_stop_literal_statement, "STOP literal");
  ;}
    break;

  case 1114:

/* Line 1455 of yacc.c  */
#line 5881 "parser.y"
    { (yyval) = current_program->cb_return_code; ;}
    break;

  case 1115:

/* Line 1455 of yacc.c  */
#line 5882 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1116:

/* Line 1455 of yacc.c  */
#line 5883 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1117:

/* Line 1455 of yacc.c  */
#line 5892 "parser.y"
    { BEGIN_STATEMENT ("STRING", TERM_STRING); ;}
    break;

  case 1118:

/* Line 1455 of yacc.c  */
#line 5895 "parser.y"
    {
	cb_emit_string ((yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]));
  ;}
    break;

  case 1119:

/* Line 1455 of yacc.c  */
#line 5901 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1120:

/* Line 1455 of yacc.c  */
#line 5902 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1121:

/* Line 1455 of yacc.c  */
#line 5906 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1122:

/* Line 1455 of yacc.c  */
#line 5907 "parser.y"
    { (yyval) = cb_build_pair (cb_int0, NULL); ;}
    break;

  case 1123:

/* Line 1455 of yacc.c  */
#line 5908 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(3) - (3)]), NULL); ;}
    break;

  case 1124:

/* Line 1455 of yacc.c  */
#line 5912 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1125:

/* Line 1455 of yacc.c  */
#line 5913 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1126:

/* Line 1455 of yacc.c  */
#line 5917 "parser.y"
    { terminator_warning (TERM_STRING); ;}
    break;

  case 1127:

/* Line 1455 of yacc.c  */
#line 5918 "parser.y"
    { terminator_clear (TERM_STRING); ;}
    break;

  case 1128:

/* Line 1455 of yacc.c  */
#line 5927 "parser.y"
    { BEGIN_STATEMENT ("SUBTRACT", TERM_SUBTRACT); ;}
    break;

  case 1130:

/* Line 1455 of yacc.c  */
#line 5934 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(3) - (4)]), '-', cb_build_binary_list ((yyvsp[(1) - (4)]), '+'));
  ;}
    break;

  case 1131:

/* Line 1455 of yacc.c  */
#line 5938 "parser.y"
    {
	cb_emit_arithmetic ((yyvsp[(5) - (6)]), 0, cb_build_binary_list (cb_cons ((yyvsp[(3) - (6)]), (yyvsp[(1) - (6)])), '-'));
  ;}
    break;

  case 1132:

/* Line 1455 of yacc.c  */
#line 5942 "parser.y"
    {
	cb_emit_corresponding (cb_build_sub, (yyvsp[(4) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)]));
  ;}
    break;

  case 1133:

/* Line 1455 of yacc.c  */
#line 5948 "parser.y"
    { terminator_warning (TERM_SUBTRACT); ;}
    break;

  case 1134:

/* Line 1455 of yacc.c  */
#line 5949 "parser.y"
    { terminator_clear (TERM_SUBTRACT); ;}
    break;

  case 1135:

/* Line 1455 of yacc.c  */
#line 5959 "parser.y"
    {
	BEGIN_STATEMENT ("SUPPRESS", 0);
	PENDING("SUPPRESS");
  ;}
    break;

  case 1138:

/* Line 1455 of yacc.c  */
#line 5974 "parser.y"
    { BEGIN_STATEMENT ("TERMINATE", 0); ;}
    break;

  case 1139:

/* Line 1455 of yacc.c  */
#line 5976 "parser.y"
    {
	PENDING("TERMINATE");
  ;}
    break;

  case 1140:

/* Line 1455 of yacc.c  */
#line 5987 "parser.y"
    { BEGIN_STATEMENT ("TRANSFORM", 0); ;}
    break;

  case 1141:

/* Line 1455 of yacc.c  */
#line 5989 "parser.y"
    {
	cb_tree		x;

	x = cb_build_converting ((yyvsp[(5) - (7)]), (yyvsp[(7) - (7)]), cb_build_inspect_region_start ());
	cb_emit_inspect ((yyvsp[(3) - (7)]), x, cb_int0, 2);
  ;}
    break;

  case 1142:

/* Line 1455 of yacc.c  */
#line 6003 "parser.y"
    { BEGIN_STATEMENT ("UNLOCK", 0); ;}
    break;

  case 1143:

/* Line 1455 of yacc.c  */
#line 6005 "parser.y"
    {
	if ((yyvsp[(3) - (4)]) != cb_error_node) {
		cb_emit_unlock ((yyvsp[(3) - (4)]));
	}
  ;}
    break;

  case 1147:

/* Line 1455 of yacc.c  */
#line 6024 "parser.y"
    { BEGIN_STATEMENT ("UNSTRING", TERM_UNSTRING); ;}
    break;

  case 1148:

/* Line 1455 of yacc.c  */
#line 6028 "parser.y"
    {
	cb_emit_unstring ((yyvsp[(3) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]));
  ;}
    break;

  case 1149:

/* Line 1455 of yacc.c  */
#line 6034 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1150:

/* Line 1455 of yacc.c  */
#line 6036 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1151:

/* Line 1455 of yacc.c  */
#line 6040 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1152:

/* Line 1455 of yacc.c  */
#line 6042 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1153:

/* Line 1455 of yacc.c  */
#line 6047 "parser.y"
    {
	(yyval) = cb_build_unstring_delimited ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1154:

/* Line 1455 of yacc.c  */
#line 6053 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(2) - (2)])); ;}
    break;

  case 1155:

/* Line 1455 of yacc.c  */
#line 6055 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1156:

/* Line 1455 of yacc.c  */
#line 6060 "parser.y"
    {
	(yyval) = cb_build_unstring_into ((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1157:

/* Line 1455 of yacc.c  */
#line 6066 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1158:

/* Line 1455 of yacc.c  */
#line 6067 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1159:

/* Line 1455 of yacc.c  */
#line 6071 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1160:

/* Line 1455 of yacc.c  */
#line 6072 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1161:

/* Line 1455 of yacc.c  */
#line 6076 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1162:

/* Line 1455 of yacc.c  */
#line 6077 "parser.y"
    { (yyval) = (yyvsp[(3) - (3)]); ;}
    break;

  case 1163:

/* Line 1455 of yacc.c  */
#line 6081 "parser.y"
    { terminator_warning (TERM_UNSTRING); ;}
    break;

  case 1164:

/* Line 1455 of yacc.c  */
#line 6082 "parser.y"
    { terminator_clear (TERM_UNSTRING); ;}
    break;

  case 1168:

/* Line 1455 of yacc.c  */
#line 6100 "parser.y"
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

  case 1169:

/* Line 1455 of yacc.c  */
#line 6121 "parser.y"
    {
	use_global_ind = 0;
  ;}
    break;

  case 1170:

/* Line 1455 of yacc.c  */
#line 6125 "parser.y"
    {
	use_global_ind = 1;
	current_program->flag_global_use = 1;
  ;}
    break;

  case 1171:

/* Line 1455 of yacc.c  */
#line 6133 "parser.y"
    {
	cb_tree		l;

	for (l = (yyvsp[(1) - (1)]); l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			setup_use_file (CB_FILE (cb_ref (CB_VALUE (l))));
		}
	}
  ;}
    break;

  case 1172:

/* Line 1455 of yacc.c  */
#line 6143 "parser.y"
    {
	current_program->global_handler[COB_OPEN_INPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_INPUT].handler_prog = current_program;
  ;}
    break;

  case 1173:

/* Line 1455 of yacc.c  */
#line 6148 "parser.y"
    {
	current_program->global_handler[COB_OPEN_OUTPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_OUTPUT].handler_prog = current_program;
  ;}
    break;

  case 1174:

/* Line 1455 of yacc.c  */
#line 6153 "parser.y"
    {
	current_program->global_handler[COB_OPEN_I_O].handler_label = current_section;
	current_program->global_handler[COB_OPEN_I_O].handler_prog = current_program;
  ;}
    break;

  case 1175:

/* Line 1455 of yacc.c  */
#line 6158 "parser.y"
    {
	current_program->global_handler[COB_OPEN_EXTEND].handler_label = current_section;
	current_program->global_handler[COB_OPEN_EXTEND].handler_prog = current_program;
  ;}
    break;

  case 1188:

/* Line 1455 of yacc.c  */
#line 6190 "parser.y"
    {
	PENDING ("USE FOR DEBUGGING");
  ;}
    break;

  case 1191:

/* Line 1455 of yacc.c  */
#line 6202 "parser.y"
    {
	PENDING ("USE BEFORE REPORTING");
  ;}
    break;

  case 1192:

/* Line 1455 of yacc.c  */
#line 6213 "parser.y"
    { BEGIN_STATEMENT ("WRITE", TERM_WRITE); ;}
    break;

  case 1193:

/* Line 1455 of yacc.c  */
#line 6216 "parser.y"
    {
	if ((yyvsp[(3) - (8)]) != cb_error_node) {
		cb_emit_write ((yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(5) - (8)]));
	}
  ;}
    break;

  case 1194:

/* Line 1455 of yacc.c  */
#line 6224 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1195:

/* Line 1455 of yacc.c  */
#line 6225 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1196:

/* Line 1455 of yacc.c  */
#line 6230 "parser.y"
    {
	(yyval) = cb_int0;
  ;}
    break;

  case 1197:

/* Line 1455 of yacc.c  */
#line 6234 "parser.y"
    {
	(yyval) = cb_build_write_advancing_lines ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
  ;}
    break;

  case 1198:

/* Line 1455 of yacc.c  */
#line 6238 "parser.y"
    {
	(yyval) = cb_build_write_advancing_mnemonic ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1199:

/* Line 1455 of yacc.c  */
#line 6242 "parser.y"
    {
	(yyval) = cb_build_write_advancing_page ((yyvsp[(1) - (3)]));
  ;}
    break;

  case 1200:

/* Line 1455 of yacc.c  */
#line 6248 "parser.y"
    { (yyval) = CB_BEFORE; ;}
    break;

  case 1201:

/* Line 1455 of yacc.c  */
#line 6249 "parser.y"
    { (yyval) = CB_AFTER; ;}
    break;

  case 1205:

/* Line 1455 of yacc.c  */
#line 6258 "parser.y"
    { terminator_warning (TERM_WRITE); ;}
    break;

  case 1206:

/* Line 1455 of yacc.c  */
#line 6259 "parser.y"
    { terminator_clear (TERM_WRITE); ;}
    break;

  case 1207:

/* Line 1455 of yacc.c  */
#line 6274 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_ACCEPT;
  ;}
    break;

  case 1208:

/* Line 1455 of yacc.c  */
#line 6282 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_DISPLAY;
  ;}
    break;

  case 1210:

/* Line 1455 of yacc.c  */
#line 6289 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1211:

/* Line 1455 of yacc.c  */
#line 6293 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1213:

/* Line 1455 of yacc.c  */
#line 6300 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1214:

/* Line 1455 of yacc.c  */
#line 6304 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1217:

/* Line 1455 of yacc.c  */
#line 6320 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1218:

/* Line 1455 of yacc.c  */
#line 6325 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1220:

/* Line 1455 of yacc.c  */
#line 6332 "parser.y"
    {
	check_unreached = 0;
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1221:

/* Line 1455 of yacc.c  */
#line 6337 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1222:

/* Line 1455 of yacc.c  */
#line 6349 "parser.y"
    {
	current_statement->handler_id = COB_EC_OVERFLOW;
  ;}
    break;

  case 1224:

/* Line 1455 of yacc.c  */
#line 6356 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1225:

/* Line 1455 of yacc.c  */
#line 6360 "parser.y"
    {
	current_statement->handler1 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1227:

/* Line 1455 of yacc.c  */
#line 6367 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1228:

/* Line 1455 of yacc.c  */
#line 6371 "parser.y"
    {
	current_statement->handler2 = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1229:

/* Line 1455 of yacc.c  */
#line 6383 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1230:

/* Line 1455 of yacc.c  */
#line 6388 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1231:

/* Line 1455 of yacc.c  */
#line 6393 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1232:

/* Line 1455 of yacc.c  */
#line 6402 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1233:

/* Line 1455 of yacc.c  */
#line 6406 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1234:

/* Line 1455 of yacc.c  */
#line 6413 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1235:

/* Line 1455 of yacc.c  */
#line 6417 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1236:

/* Line 1455 of yacc.c  */
#line 6429 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1237:

/* Line 1455 of yacc.c  */
#line 6434 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1238:

/* Line 1455 of yacc.c  */
#line 6439 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1239:

/* Line 1455 of yacc.c  */
#line 6448 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1240:

/* Line 1455 of yacc.c  */
#line 6452 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1241:

/* Line 1455 of yacc.c  */
#line 6459 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1242:

/* Line 1455 of yacc.c  */
#line 6463 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1245:

/* Line 1455 of yacc.c  */
#line 6479 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1246:

/* Line 1455 of yacc.c  */
#line 6484 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler2 = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1247:

/* Line 1455 of yacc.c  */
#line 6489 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = (yyvsp[(1) - (2)]);
	current_statement->handler2 = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 1248:

/* Line 1455 of yacc.c  */
#line 6498 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1249:

/* Line 1455 of yacc.c  */
#line 6502 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1250:

/* Line 1455 of yacc.c  */
#line 6509 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1251:

/* Line 1455 of yacc.c  */
#line 6513 "parser.y"
    {
	(yyval) = (yyvsp[(3) - (3)]);
  ;}
    break;

  case 1252:

/* Line 1455 of yacc.c  */
#line 6525 "parser.y"
    {
	(yyval) = cb_one;
  ;}
    break;

  case 1253:

/* Line 1455 of yacc.c  */
#line 6529 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 1254:

/* Line 1455 of yacc.c  */
#line 6541 "parser.y"
    {
	(yyval) = cb_build_cond ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1255:

/* Line 1455 of yacc.c  */
#line 6548 "parser.y"
    {
	(yyval) = cb_build_expr ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1256:

/* Line 1455 of yacc.c  */
#line 6554 "parser.y"
    {
	current_expr = NULL;
  ;}
    break;

  case 1257:

/* Line 1455 of yacc.c  */
#line 6558 "parser.y"
    {
	(yyval) = cb_list_reverse (current_expr);
  ;}
    break;

  case 1259:

/* Line 1455 of yacc.c  */
#line 6565 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1260:

/* Line 1455 of yacc.c  */
#line 6566 "parser.y"
    { push_expr (')', NULL); ;}
    break;

  case 1261:

/* Line 1455 of yacc.c  */
#line 6568 "parser.y"
    { push_expr ('O', NULL); ;}
    break;

  case 1262:

/* Line 1455 of yacc.c  */
#line 6569 "parser.y"
    { push_expr ('9', NULL); ;}
    break;

  case 1263:

/* Line 1455 of yacc.c  */
#line 6570 "parser.y"
    { push_expr ('A', NULL); ;}
    break;

  case 1264:

/* Line 1455 of yacc.c  */
#line 6571 "parser.y"
    { push_expr ('L', NULL); ;}
    break;

  case 1265:

/* Line 1455 of yacc.c  */
#line 6572 "parser.y"
    { push_expr ('U', NULL); ;}
    break;

  case 1266:

/* Line 1455 of yacc.c  */
#line 6573 "parser.y"
    { push_expr ('x', (yyvsp[(2) - (2)])); ;}
    break;

  case 1267:

/* Line 1455 of yacc.c  */
#line 6575 "parser.y"
    { push_expr ('P', NULL); ;}
    break;

  case 1268:

/* Line 1455 of yacc.c  */
#line 6576 "parser.y"
    { push_expr ('N', NULL); ;}
    break;

  case 1269:

/* Line 1455 of yacc.c  */
#line 6577 "parser.y"
    { push_expr ('x', cb_zero); ;}
    break;

  case 1270:

/* Line 1455 of yacc.c  */
#line 6579 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1273:

/* Line 1455 of yacc.c  */
#line 6585 "parser.y"
    { push_expr ('(', NULL); ;}
    break;

  case 1274:

/* Line 1455 of yacc.c  */
#line 6587 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1275:

/* Line 1455 of yacc.c  */
#line 6588 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1276:

/* Line 1455 of yacc.c  */
#line 6589 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1277:

/* Line 1455 of yacc.c  */
#line 6591 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1278:

/* Line 1455 of yacc.c  */
#line 6593 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1279:

/* Line 1455 of yacc.c  */
#line 6594 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1280:

/* Line 1455 of yacc.c  */
#line 6595 "parser.y"
    { push_expr ('*', NULL); ;}
    break;

  case 1281:

/* Line 1455 of yacc.c  */
#line 6596 "parser.y"
    { push_expr ('/', NULL); ;}
    break;

  case 1282:

/* Line 1455 of yacc.c  */
#line 6597 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1283:

/* Line 1455 of yacc.c  */
#line 6599 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1284:

/* Line 1455 of yacc.c  */
#line 6600 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1285:

/* Line 1455 of yacc.c  */
#line 6601 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1286:

/* Line 1455 of yacc.c  */
#line 6602 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1287:

/* Line 1455 of yacc.c  */
#line 6603 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1288:

/* Line 1455 of yacc.c  */
#line 6604 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1289:

/* Line 1455 of yacc.c  */
#line 6606 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1290:

/* Line 1455 of yacc.c  */
#line 6607 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1291:

/* Line 1455 of yacc.c  */
#line 6608 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1292:

/* Line 1455 of yacc.c  */
#line 6609 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1293:

/* Line 1455 of yacc.c  */
#line 6610 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1294:

/* Line 1455 of yacc.c  */
#line 6611 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1295:

/* Line 1455 of yacc.c  */
#line 6613 "parser.y"
    { push_expr ('&', NULL); ;}
    break;

  case 1296:

/* Line 1455 of yacc.c  */
#line 6614 "parser.y"
    { push_expr ('|', NULL); ;}
    break;

  case 1310:

/* Line 1455 of yacc.c  */
#line 6626 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1311:

/* Line 1455 of yacc.c  */
#line 6627 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1315:

/* Line 1455 of yacc.c  */
#line 6636 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1316:

/* Line 1455 of yacc.c  */
#line 6637 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '+', (yyvsp[(3) - (3)])); ;}
    break;

  case 1317:

/* Line 1455 of yacc.c  */
#line 6638 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '-', (yyvsp[(3) - (3)])); ;}
    break;

  case 1318:

/* Line 1455 of yacc.c  */
#line 6639 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '*', (yyvsp[(3) - (3)])); ;}
    break;

  case 1319:

/* Line 1455 of yacc.c  */
#line 6640 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '/', (yyvsp[(3) - (3)])); ;}
    break;

  case 1320:

/* Line 1455 of yacc.c  */
#line 6641 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); ;}
    break;

  case 1321:

/* Line 1455 of yacc.c  */
#line 6642 "parser.y"
    { (yyval) = cb_build_binary_op (cb_zero, '-', (yyvsp[(2) - (2)])); ;}
    break;

  case 1322:

/* Line 1455 of yacc.c  */
#line 6643 "parser.y"
    { (yyval) = cb_build_binary_op ((yyvsp[(1) - (3)]), '^', (yyvsp[(3) - (3)])); ;}
    break;

  case 1323:

/* Line 1455 of yacc.c  */
#line 6644 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1324:

/* Line 1455 of yacc.c  */
#line 6656 "parser.y"
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

  case 1325:

/* Line 1455 of yacc.c  */
#line 6668 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(3) - (3)])))) {
		(yyval) = CB_FILE (cb_ref ((yyvsp[(3) - (3)])))->linage_ctr;
	} else {
		cb_error_x ((yyvsp[(3) - (3)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(3) - (3)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1326:

/* Line 1455 of yacc.c  */
#line 6682 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1327:

/* Line 1455 of yacc.c  */
#line 6684 "parser.y"
    { (yyval) = cb_list_append ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1328:

/* Line 1455 of yacc.c  */
#line 6688 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)])); ;}
    break;

  case 1329:

/* Line 1455 of yacc.c  */
#line 6694 "parser.y"
    { cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1330:

/* Line 1455 of yacc.c  */
#line 6701 "parser.y"
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

  case 1331:

/* Line 1455 of yacc.c  */
#line 6721 "parser.y"
    {
	(yyval) = cb_list_init ((yyvsp[(1) - (1)]));
  ;}
    break;

  case 1332:

/* Line 1455 of yacc.c  */
#line 6725 "parser.y"
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

  case 1333:

/* Line 1455 of yacc.c  */
#line 6741 "parser.y"
    {
	if (CB_FILE_P (cb_ref ((yyvsp[(1) - (1)])))) {
		(yyval) = (yyvsp[(1) - (1)]);
	} else {
		cb_error_x ((yyvsp[(1) - (1)]), _("'%s' is not a file name"), CB_NAME ((yyvsp[(1) - (1)])));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1334:

/* Line 1455 of yacc.c  */
#line 6754 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1335:

/* Line 1455 of yacc.c  */
#line 6756 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1336:

/* Line 1455 of yacc.c  */
#line 6760 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1337:

/* Line 1455 of yacc.c  */
#line 6766 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1338:

/* Line 1455 of yacc.c  */
#line 6768 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1339:

/* Line 1455 of yacc.c  */
#line 6773 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	CB_REFERENCE ((yyval))->offset = CB_TREE (current_section);
	current_program->label_list = cb_cons ((yyval), current_program->label_list);
  ;}
    break;

  case 1343:

/* Line 1455 of yacc.c  */
#line 6788 "parser.y"
    {
	(yyval) = cb_build_reference ((char *)(CB_LITERAL ((yyvsp[(1) - (1)]))->data));
	(yyval)->source_file = (yyvsp[(1) - (1)])->source_file;
	(yyval)->source_line = (yyvsp[(1) - (1)])->source_line;
  ;}
    break;

  case 1344:

/* Line 1455 of yacc.c  */
#line 6798 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1345:

/* Line 1455 of yacc.c  */
#line 6799 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1346:

/* Line 1455 of yacc.c  */
#line 6804 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	current_program->reference_list = cb_cons ((yyval), current_program->reference_list);
  ;}
    break;

  case 1347:

/* Line 1455 of yacc.c  */
#line 6811 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1348:

/* Line 1455 of yacc.c  */
#line 6812 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1351:

/* Line 1455 of yacc.c  */
#line 6824 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	if (CB_REFERENCE ((yyval))->word->count > 0) {
		redefinition_error ((yyval));
		(yyval) = cb_error_node;
	}
  ;}
    break;

  case 1352:

/* Line 1455 of yacc.c  */
#line 6843 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1353:

/* Line 1455 of yacc.c  */
#line 6844 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1355:

/* Line 1455 of yacc.c  */
#line 6849 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1356:

/* Line 1455 of yacc.c  */
#line 6853 "parser.y"
    { (yyval) = cb_list_init ((yyvsp[(1) - (1)])); ;}
    break;

  case 1357:

/* Line 1455 of yacc.c  */
#line 6854 "parser.y"
    { (yyval) = cb_list_add ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 1359:

/* Line 1455 of yacc.c  */
#line 6859 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1360:

/* Line 1455 of yacc.c  */
#line 6860 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1361:

/* Line 1455 of yacc.c  */
#line 6861 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1362:

/* Line 1455 of yacc.c  */
#line 6862 "parser.y"
    { (yyval) = cb_build_ppointer ((yyvsp[(4) - (4)])); ;}
    break;

  case 1363:

/* Line 1455 of yacc.c  */
#line 6863 "parser.y"
    { (yyval) = cb_build_address ((yyvsp[(3) - (3)])); ;}
    break;

  case 1368:

/* Line 1455 of yacc.c  */
#line 6871 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1369:

/* Line 1455 of yacc.c  */
#line 6872 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1370:

/* Line 1455 of yacc.c  */
#line 6873 "parser.y"
    { (yyval) = cb_build_length ((yyvsp[(3) - (3)])); ;}
    break;

  case 1376:

/* Line 1455 of yacc.c  */
#line 6885 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1377:

/* Line 1455 of yacc.c  */
#line 6886 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1389:

/* Line 1455 of yacc.c  */
#line 6920 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1390:

/* Line 1455 of yacc.c  */
#line 6928 "parser.y"
    { (yyval) = cb_build_identifier ((yyvsp[(1) - (1)])); ;}
    break;

  case 1391:

/* Line 1455 of yacc.c  */
#line 6932 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1392:

/* Line 1455 of yacc.c  */
#line 6933 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1393:

/* Line 1455 of yacc.c  */
#line 6934 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 1394:

/* Line 1455 of yacc.c  */
#line 6935 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); ;}
    break;

  case 1395:

/* Line 1455 of yacc.c  */
#line 6939 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1396:

/* Line 1455 of yacc.c  */
#line 6940 "parser.y"
    { (yyval) = (yyvsp[(1) - (3)]); CB_REFERENCE ((yyvsp[(1) - (3)]))->chain = (yyvsp[(3) - (3)]); ;}
    break;

  case 1397:

/* Line 1455 of yacc.c  */
#line 6945 "parser.y"
    {
	if (cb_ref ((yyvsp[(0) - (3)])) != cb_error_node) {
		(yyval) = (yyvsp[(0) - (3)]);
		CB_REFERENCE ((yyvsp[(0) - (3)]))->subs = cb_list_reverse ((yyvsp[(2) - (3)]));
	}
  ;}
    break;

  case 1398:

/* Line 1455 of yacc.c  */
#line 6955 "parser.y"
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

  case 1399:

/* Line 1455 of yacc.c  */
#line 6973 "parser.y"
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

  case 1400:

/* Line 1455 of yacc.c  */
#line 7000 "parser.y"
    {
	if (cb_tree_category ((yyvsp[(1) - (1)])) != CB_CATEGORY_NUMERIC) {
		cb_error (_("Integer value expected"));
	} else if (CB_LITERAL ((yyvsp[(1) - (1)]))->sign < 0 || CB_LITERAL ((yyvsp[(1) - (1)]))->scale) {
		cb_error (_("Integer value expected"));
	}
	(yyval) = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 1401:

/* Line 1455 of yacc.c  */
#line 7011 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1402:

/* Line 1455 of yacc.c  */
#line 7013 "parser.y"
    {
	(yyval) = (yyvsp[(2) - (2)]);
	if (CB_LITERAL_P ((yyvsp[(2) - (2)]))) {
		CB_LITERAL ((yyvsp[(2) - (2)]))->all = 1;
	}
  ;}
    break;

  case 1403:

/* Line 1455 of yacc.c  */
#line 7022 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1404:

/* Line 1455 of yacc.c  */
#line 7023 "parser.y"
    { (yyval) = cb_concat_literals ((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 1405:

/* Line 1455 of yacc.c  */
#line 7027 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1406:

/* Line 1455 of yacc.c  */
#line 7028 "parser.y"
    { (yyval) = cb_space; ;}
    break;

  case 1407:

/* Line 1455 of yacc.c  */
#line 7029 "parser.y"
    { (yyval) = cb_zero; ;}
    break;

  case 1408:

/* Line 1455 of yacc.c  */
#line 7030 "parser.y"
    { (yyval) = cb_quote; ;}
    break;

  case 1409:

/* Line 1455 of yacc.c  */
#line 7031 "parser.y"
    { (yyval) = cb_high; ;}
    break;

  case 1410:

/* Line 1455 of yacc.c  */
#line 7032 "parser.y"
    { (yyval) = cb_low; ;}
    break;

  case 1411:

/* Line 1455 of yacc.c  */
#line 7033 "parser.y"
    { (yyval) = cb_null; ;}
    break;

  case 1412:

/* Line 1455 of yacc.c  */
#line 7042 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1413:

/* Line 1455 of yacc.c  */
#line 7046 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
  ;}
    break;

  case 1414:

/* Line 1455 of yacc.c  */
#line 7050 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1415:

/* Line 1455 of yacc.c  */
#line 7054 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1416:

/* Line 1455 of yacc.c  */
#line 7058 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), cb_list_init ((yyvsp[(3) - (5)])), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1417:

/* Line 1455 of yacc.c  */
#line 7062 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1418:

/* Line 1455 of yacc.c  */
#line 7066 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1419:

/* Line 1455 of yacc.c  */
#line 7070 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1420:

/* Line 1455 of yacc.c  */
#line 7074 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1421:

/* Line 1455 of yacc.c  */
#line 7078 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), NULL);
  ;}
    break;

  case 1422:

/* Line 1455 of yacc.c  */
#line 7082 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
  ;}
    break;

  case 1423:

/* Line 1455 of yacc.c  */
#line 7086 "parser.y"
    {
	(yyval) = cb_build_intrinsic ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), NULL);
  ;}
    break;

  case 1424:

/* Line 1455 of yacc.c  */
#line 7092 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1425:

/* Line 1455 of yacc.c  */
#line 7093 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (4)]), NULL); ;}
    break;

  case 1426:

/* Line 1455 of yacc.c  */
#line 7094 "parser.y"
    { (yyval) = cb_build_pair ((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 1427:

/* Line 1455 of yacc.c  */
#line 7098 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1428:

/* Line 1455 of yacc.c  */
#line 7099 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 1429:

/* Line 1455 of yacc.c  */
#line 7103 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1430:

/* Line 1455 of yacc.c  */
#line 7104 "parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 1431:

/* Line 1455 of yacc.c  */
#line 7110 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_int0);
  ;}
    break;

  case 1432:

/* Line 1455 of yacc.c  */
#line 7117 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int1);
  ;}
    break;

  case 1433:

/* Line 1455 of yacc.c  */
#line 7124 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_int2);
  ;}
    break;

  case 1434:

/* Line 1455 of yacc.c  */
#line 7134 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1435:

/* Line 1455 of yacc.c  */
#line 7141 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, (yyvsp[(3) - (3)]));
  ;}
    break;

  case 1436:

/* Line 1455 of yacc.c  */
#line 7151 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (1)]));
	(yyval) = cb_list_add (x, cb_null);
  ;}
    break;

  case 1437:

/* Line 1455 of yacc.c  */
#line 7158 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init ((yyvsp[(1) - (3)]));
	(yyval) = cb_list_add (x, cb_ref ((yyvsp[(3) - (3)])));
  ;}
    break;

  case 1438:

/* Line 1455 of yacc.c  */
#line 7171 "parser.y"
    {
	non_const_word = 1;
  ;}
    break;

  case 1439:

/* Line 1455 of yacc.c  */
#line 7181 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1440:

/* Line 1455 of yacc.c  */
#line 7182 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1441:

/* Line 1455 of yacc.c  */
#line 7186 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1442:

/* Line 1455 of yacc.c  */
#line 7187 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1443:

/* Line 1455 of yacc.c  */
#line 7191 "parser.y"
    { (yyval) = NULL; ;}
    break;

  case 1444:

/* Line 1455 of yacc.c  */
#line 7192 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1445:

/* Line 1455 of yacc.c  */
#line 7196 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1446:

/* Line 1455 of yacc.c  */
#line 7197 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1447:

/* Line 1455 of yacc.c  */
#line 7198 "parser.y"
    { (yyval) = cb_int2; ;}
    break;

  case 1448:

/* Line 1455 of yacc.c  */
#line 7202 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1449:

/* Line 1455 of yacc.c  */
#line 7203 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1450:

/* Line 1455 of yacc.c  */
#line 7207 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1451:

/* Line 1455 of yacc.c  */
#line 7208 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1452:

/* Line 1455 of yacc.c  */
#line 7212 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1453:

/* Line 1455 of yacc.c  */
#line 7213 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1454:

/* Line 1455 of yacc.c  */
#line 7217 "parser.y"
    { (yyval) = cb_int0; ;}
    break;

  case 1455:

/* Line 1455 of yacc.c  */
#line 7218 "parser.y"
    { (yyval) = cb_int1; ;}
    break;

  case 1467:

/* Line 1455 of yacc.c  */
#line 7231 "parser.y"
    { (yyval) = cb_int1; ;}
    break;



/* Line 1455 of yacc.c  */
#line 14459 "parser.c"
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
#line 7275 "parser.y"


