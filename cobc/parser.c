/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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
#define TOKEN_EOF 0
#define ACCEPT 258
#define ACCESS 259
#define ADD 260
#define ADDRESS 261
#define ADVANCING 262
#define AFTER 263
#define ALL 264
#define ALLOCATE 265
#define ALPHABET 266
#define ALPHABETIC 267
#define ALPHABETIC_LOWER 268
#define ALPHABETIC_UPPER 269
#define ALPHANUMERIC 270
#define ALPHANUMERIC_EDITED 271
#define ALSO 272
#define ALTER 273
#define ALTERNATE 274
#define AND 275
#define ANY 276
#define ARE 277
#define AREA 278
#define ARGUMENT_NUMBER 279
#define ARGUMENT_VALUE 280
#define AS 281
#define ASCENDING 282
#define ASSIGN 283
#define AT 284
#define AUTO 285
#define AUTOMATIC 286
#define BACKGROUND_COLOR 287
#define BASED 288
#define BEFORE 289
#define BELL 290
#define BINARY 291
#define BINARY_C_LONG 292
#define BINARY_CHAR 293
#define BINARY_DOUBLE 294
#define BINARY_LONG 295
#define BINARY_SHORT 296
#define BLANK 297
#define BLANK_LINE 298
#define BLANK_SCREEN 299
#define BLINK 300
#define BLOCK 301
#define BOTTOM 302
#define BY 303
#define BYTE_LENGTH 304
#define CALL 305
#define CANCEL 306
#define CH 307
#define CHAINING 308
#define CHARACTER 309
#define CHARACTERS 310
#define CLASS 311
#define CLOSE 312
#define CODE 313
#define CODE_SET 314
#define COLLATING 315
#define COL 316
#define COLS 317
#define COLUMN 318
#define COLUMNS 319
#define COMMA 320
#define COMMAND_LINE 321
#define COMMA_DELIM 322
#define COMMIT 323
#define COMMON 324
#define COMP 325
#define COMPUTE 326
#define COMP_1 327
#define COMP_2 328
#define COMP_3 329
#define COMP_4 330
#define COMP_5 331
#define COMP_X 332
#define CONCATENATE_FUNC 333
#define CONFIGURATION 334
#define CONSTANT 335
#define CONTAINS 336
#define CONTENT 337
#define CONTINUE 338
#define CONTROL 339
#define CONTROLS 340
#define CONTROL_FOOTING 341
#define CONTROL_HEADING 342
#define CONVERTING 343
#define CORRESPONDING 344
#define COUNT 345
#define CRT 346
#define CURRENCY 347
#define CURRENT_DATE_FUNC 348
#define CURSOR 349
#define CYCLE 350
#define DATA 351
#define DATE 352
#define DAY 353
#define DAY_OF_WEEK 354
#define DE 355
#define DEBUGGING 356
#define DECIMAL_POINT 357
#define DECLARATIVES 358
#define DEFAULT 359
#define DELETE 360
#define DELIMITED 361
#define DELIMITER 362
#define DEPENDING 363
#define DESCENDING 364
#define DETAIL 365
#define DISK 366
#define DISPLAY 367
#define DIVIDE 368
#define DIVISION 369
#define DOWN 370
#define DUPLICATES 371
#define DYNAMIC 372
#define EBCDIC 373
#define ELSE 374
#define END 375
#define END_ACCEPT 376
#define END_ADD 377
#define END_CALL 378
#define END_COMPUTE 379
#define END_DELETE 380
#define END_DISPLAY 381
#define END_DIVIDE 382
#define END_EVALUATE 383
#define END_FUNCTION 384
#define END_IF 385
#define END_MULTIPLY 386
#define END_PERFORM 387
#define END_PROGRAM 388
#define END_READ 389
#define END_RETURN 390
#define END_REWRITE 391
#define END_SEARCH 392
#define END_START 393
#define END_STRING 394
#define END_SUBTRACT 395
#define END_UNSTRING 396
#define END_WRITE 397
#define ENTRY 398
#define ENVIRONMENT 399
#define ENVIRONMENT_NAME 400
#define ENVIRONMENT_VALUE 401
#define EOL 402
#define EOP 403
#define EOS 404
#define EQUAL 405
#define EQUALS 406
#define ERASE 407
#define ERROR 408
#define ESCAPE 409
#define EVALUATE 410
#define EVENT_STATUS 411
#define EXCEPTION 412
#define EXCLUSIVE 413
#define EXIT 414
#define EXTEND 415
#define EXTERNAL 416
#define FD 417
#define FILE_CONTROL 418
#define FILE_ID 419
#define FILLER 420
#define FINAL 421
#define FIRST 422
#define FOOTING 423
#define FOR 424
#define FOREGROUND_COLOR 425
#define FOREVER 426
#define FREE 427
#define FROM 428
#define FULL 429
#define FUNCTION 430
#define FUNCTION_ID 431
#define FUNCTION_NAME 432
#define GE 433
#define GENERATE 434
#define GIVING 435
#define GLOBAL 436
#define GO 437
#define GOBACK 438
#define GREATER 439
#define GROUP 440
#define HEADING 441
#define HIGHLIGHT 442
#define HIGH_VALUE 443
#define IDENTIFICATION 444
#define IF 445
#define IGNORE 446
#define IGNORING 447
#define IN 448
#define INDEX 449
#define INDEXED 450
#define INDICATE 451
#define INITIALIZE 452
#define INITIALIZED 453
#define INITIATE 454
#define INPUT 455
#define INPUT_OUTPUT 456
#define INSPECT 457
#define INTO 458
#define INTRINSIC 459
#define INVALID 460
#define INVALID_KEY 461
#define IS 462
#define I_O 463
#define I_O_CONTROL 464
#define JUSTIFIED 465
#define KEY 466
#define LABEL 467
#define LAST 468
#define LAST_DETAIL 469
#define LE 470
#define LEADING 471
#define LEFT 472
#define LENGTH 473
#define LESS 474
#define LIMIT 475
#define LIMITS 476
#define LINAGE 477
#define LINAGE_COUNTER 478
#define LINE 479
#define LINES 480
#define LINKAGE 481
#define LITERAL 482
#define LOCALE 483
#define LOCALE_DT_FUNC 484
#define LOCAL_STORAGE 485
#define LOCK 486
#define LOWER_CASE_FUNC 487
#define LOWLIGHT 488
#define LOW_VALUE 489
#define MANUAL 490
#define MEMORY 491
#define MERGE 492
#define MINUS 493
#define MNEMONIC_NAME 494
#define MODE 495
#define MOVE 496
#define MULTIPLE 497
#define MULTIPLY 498
#define NATIONAL 499
#define NATIONAL_EDITED 500
#define NATIVE 501
#define NE 502
#define NEGATIVE 503
#define NEXT 504
#define NEXT_SENTENCE 505
#define NO 506
#define NOT 507
#define NOT_END 508
#define NOT_EOP 509
#define NOT_EXCEPTION 510
#define NOT_INVALID_KEY 511
#define NOT_OVERFLOW 512
#define NOT_SIZE_ERROR 513
#define NO_ADVANCING 514
#define NUMBER 515
#define NUMBERS 516
#define NUMERIC 517
#define NUMERIC_EDITED 518
#define NUMVALC_FUNC 519
#define OBJECT_COMPUTER 520
#define OCCURS 521
#define OF 522
#define OFF 523
#define OMITTED 524
#define ON 525
#define ONLY 526
#define OPEN 527
#define OPTIONAL 528
#define OR 529
#define ORDER 530
#define ORGANIZATION 531
#define OTHER 532
#define OUTPUT 533
#define OVERFLOW 534
#define OVERLINE 535
#define PACKED_DECIMAL 536
#define PADDING 537
#define PAGE 538
#define PAGE_FOOTING 539
#define PAGE_HEADING 540
#define PARAGRAPH 541
#define PERFORM 542
#define PICTURE 543
#define PLUS 544
#define POINTER 545
#define POSITION 546
#define POSITIVE 547
#define PRESENT 548
#define PREVIOUS 549
#define PRINTER 550
#define PRINTING 551
#define PROCEDURE 552
#define PROCEDURES 553
#define PROCEED 554
#define PROGRAM 555
#define PROGRAM_ID 556
#define PROGRAM_NAME 557
#define PROGRAM_POINTER 558
#define PROMPT 559
#define QUOTE 560
#define RANDOM 561
#define RD 562
#define READ 563
#define RECORD 564
#define RECORDING 565
#define RECORDS 566
#define RECURSIVE 567
#define REDEFINES 568
#define REEL 569
#define REFERENCE 570
#define RELATIVE 571
#define RELEASE 572
#define REMAINDER 573
#define REMOVAL 574
#define RENAMES 575
#define REPLACING 576
#define REPORT 577
#define REPORTING 578
#define REPORTS 579
#define REPORT_FOOTING 580
#define REPORT_HEADING 581
#define REPOSITORY 582
#define REQUIRED 583
#define RESERVE 584
#define RETURN 585
#define RETURNING 586
#define REVERSE_FUNC 587
#define REVERSE_VIDEO 588
#define REWIND 589
#define REWRITE 590
#define RIGHT 591
#define ROLLBACK 592
#define ROUNDED 593
#define RUN 594
#define SAME 595
#define SCREEN 596
#define SCREEN_CONTROL 597
#define SCROLL 598
#define SD 599
#define SEARCH 600
#define SECTION 601
#define SECURE 602
#define SEGMENT_LIMIT 603
#define SELECT 604
#define SEMI_COLON 605
#define SENTENCE 606
#define SEPARATE 607
#define SEQUENCE 608
#define SEQUENTIAL 609
#define SET 610
#define SHARING 611
#define SIGN 612
#define SIGNED 613
#define SIGNED_INT 614
#define SIGNED_LONG 615
#define SIGNED_SHORT 616
#define SIZE 617
#define SIZE_ERROR 618
#define SORT 619
#define SORT_MERGE 620
#define SOURCE 621
#define SOURCE_COMPUTER 622
#define SPACE 623
#define SPECIAL_NAMES 624
#define STANDARD 625
#define STANDARD_1 626
#define STANDARD_2 627
#define START 628
#define STATUS 629
#define STOP 630
#define STRING 631
#define SUBSTITUTE_FUNC 632
#define SUBSTITUTE_CASE_FUNC 633
#define SUBTRACT 634
#define SUM 635
#define SUPPRESS 636
#define SYMBOLIC 637
#define SYNCHRONIZED 638
#define TALLYING 639
#define TAPE 640
#define TERMINATE 641
#define TEST 642
#define THAN 643
#define THEN 644
#define THRU 645
#define TIME 646
#define TIMES 647
#define TO 648
#define TOK_FALSE 649
#define TOK_FILE 650
#define TOK_INITIAL 651
#define TOK_NULL 652
#define TOK_TRUE 653
#define TOP 654
#define TRAILING 655
#define TRANSFORM 656
#define TRIM_FUNCTION 657
#define TYPE 658
#define UNDERLINE 659
#define UNIT 660
#define UNLOCK 661
#define UNSIGNED 662
#define UNSIGNED_INT 663
#define UNSIGNED_LONG 664
#define UNSIGNED_SHORT 665
#define UNSTRING 666
#define UNTIL 667
#define UP 668
#define UPDATE 669
#define UPON 670
#define UPON_ARGUMENT_NUMBER 671
#define UPON_COMMAND_LINE 672
#define UPON_ENVIRONMENT_NAME 673
#define UPON_ENVIRONMENT_VALUE 674
#define UPPER_CASE_FUNC 675
#define USAGE 676
#define USE 677
#define USING 678
#define VALUE 679
#define VARYING 680
#define WAIT 681
#define WHEN 682
#define WHEN_COMPILED_FUNC 683
#define WITH 684
#define WORD 685
#define WORDS 686
#define WORKING_STORAGE 687
#define WRITE 688
#define YYYYDDD 689
#define YYYYMMDD 690
#define ZERO 691
#define UNARY_SIGN 692




/* Copy the first part of user declarations.  */
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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 1244 "parser.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   5462

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  451
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  690
/* YYNRULES -- Number of rules. */
#define YYNRULES  1518
/* YYNRULES -- Number of states. */
#define YYNSTATES  2240

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   692

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned short yytranslate[] =
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
static const unsigned short yyprhs[] =
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
     467,   469,   471,   473,   475,   481,   486,   487,   489,   491,
     492,   494,   496,   498,   500,   502,   507,   509,   511,   513,
     520,   524,   530,   531,   533,   535,   540,   543,   546,   548,
     549,   554,   560,   563,   565,   567,   571,   573,   575,   579,
     581,   584,   589,   594,   599,   601,   605,   610,   615,   619,
     623,   626,   629,   632,   633,   637,   638,   641,   643,   646,
     648,   650,   656,   657,   659,   661,   663,   669,   671,   674,
     677,   678,   681,   682,   692,   693,   694,   700,   701,   705,
     706,   709,   713,   716,   719,   721,   723,   724,   729,   730,
     733,   736,   739,   741,   743,   745,   747,   749,   751,   753,
     755,   757,   763,   764,   766,   768,   773,   780,   790,   791,
     795,   796,   799,   800,   803,   807,   809,   811,   817,   823,
     825,   827,   831,   837,   838,   841,   843,   845,   847,   853,
     858,   862,   867,   871,   875,   879,   880,   881,   887,   888,
     890,   891,   894,   898,   903,   906,   908,   909,   914,   916,
     917,   919,   921,   923,   924,   927,   929,   933,   937,   944,
     945,   948,   950,   952,   954,   956,   958,   960,   962,   964,
     966,   968,   970,   972,   974,   976,   979,   983,   984,   987,
     990,   992,   994,   998,  1000,  1002,  1004,  1006,  1008,  1010,
    1012,  1014,  1016,  1018,  1020,  1022,  1024,  1026,  1028,  1030,
    1032,  1034,  1036,  1039,  1042,  1044,  1047,  1050,  1052,  1055,
    1058,  1060,  1063,  1066,  1068,  1071,  1074,  1076,  1078,  1082,
    1086,  1094,  1095,  1098,  1099,  1103,  1105,  1106,  1112,  1114,
    1116,  1117,  1121,  1123,  1126,  1128,  1131,  1134,  1135,  1137,
    1139,  1143,  1145,  1146,  1155,  1157,  1160,  1162,  1166,  1167,
    1171,  1174,  1179,  1182,  1183,  1184,  1190,  1191,  1192,  1198,
    1199,  1200,  1206,  1207,  1209,  1211,  1214,  1220,  1221,  1224,
    1227,  1231,  1233,  1235,  1238,  1241,  1244,  1245,  1247,  1249,
    1252,  1261,  1262,  1266,  1267,  1272,  1273,  1278,  1279,  1283,
    1284,  1288,  1290,  1295,  1298,  1300,  1302,  1303,  1306,  1311,
    1312,  1315,  1317,  1319,  1321,  1323,  1325,  1327,  1329,  1331,
    1333,  1335,  1337,  1339,  1341,  1343,  1345,  1347,  1351,  1353,
    1355,  1357,  1359,  1361,  1363,  1365,  1370,  1375,  1378,  1380,
    1382,  1385,  1389,  1391,  1395,  1402,  1405,  1409,  1412,  1414,
    1417,  1420,  1422,  1425,  1426,  1428,  1430,  1435,  1438,  1439,
    1441,  1443,  1444,  1445,  1446,  1453,  1454,  1456,  1458,  1461,
    1463,  1464,  1470,  1471,  1474,  1476,  1478,  1480,  1482,  1485,
    1488,  1490,  1492,  1494,  1496,  1498,  1500,  1502,  1504,  1506,
    1508,  1514,  1520,  1524,  1528,  1530,  1532,  1534,  1536,  1538,
    1540,  1542,  1545,  1548,  1551,  1552,  1554,  1556,  1558,  1560,
    1561,  1563,  1565,  1567,  1569,  1573,  1574,  1575,  1576,  1586,
    1587,  1588,  1592,  1593,  1597,  1599,  1602,  1607,  1608,  1611,
    1614,  1615,  1619,  1623,  1628,  1632,  1633,  1635,  1636,  1639,
    1640,  1641,  1649,  1650,  1653,  1655,  1657,  1659,  1662,  1665,
    1667,  1672,  1675,  1677,  1679,  1680,  1682,  1683,  1684,  1688,
    1689,  1692,  1695,  1697,  1699,  1701,  1703,  1705,  1707,  1709,
    1711,  1713,  1715,  1717,  1719,  1721,  1723,  1725,  1727,  1729,
    1731,  1733,  1735,  1737,  1739,  1741,  1743,  1745,  1747,  1749,
    1751,  1753,  1755,  1757,  1759,  1761,  1763,  1765,  1767,  1769,
    1771,  1773,  1775,  1777,  1779,  1781,  1783,  1785,  1787,  1789,
    1791,  1793,  1794,  1799,  1804,  1809,  1813,  1817,  1821,  1826,
    1830,  1835,  1839,  1843,  1847,  1852,  1858,  1862,  1867,  1871,
    1875,  1876,  1880,  1884,  1887,  1890,  1893,  1897,  1901,  1905,
    1906,  1909,  1911,  1914,  1916,  1918,  1920,  1922,  1924,  1926,
    1928,  1932,  1936,  1940,  1944,  1946,  1948,  1950,  1952,  1954,
    1956,  1957,  1959,  1960,  1965,  1970,  1976,  1983,  1984,  1987,
    1988,  1990,  1991,  1995,  1999,  2005,  2006,  2009,  2012,  2013,
    2019,  2020,  2023,  2024,  2033,  2034,  2035,  2039,  2041,  2044,
    2047,  2051,  2052,  2055,  2058,  2061,  2062,  2065,  2068,  2069,
    2070,  2074,  2075,  2076,  2080,  2081,  2083,  2084,  2088,  2089,
    2092,  2093,  2097,  2098,  2102,  2103,  2105,  2109,  2113,  2116,
    2118,  2120,  2121,  2126,  2131,  2132,  2134,  2136,  2138,  2140,
    2142,  2143,  2150,  2151,  2153,  2154,  2159,  2163,  2167,  2171,
    2175,  2181,  2182,  2185,  2188,  2191,  2194,  2195,  2198,  2201,
    2203,  2206,  2208,  2210,  2213,  2216,  2218,  2220,  2222,  2224,
    2226,  2230,  2234,  2238,  2242,  2244,  2246,  2247,  2249,  2250,
    2255,  2260,  2267,  2274,  2283,  2292,  2293,  2295,  2296,  2301,
    2302,  2308,  2310,  2314,  2316,  2318,  2320,  2323,  2325,  2328,
    2329,  2333,  2334,  2335,  2340,  2343,  2347,  2349,  2353,  2356,
    2358,  2360,  2362,  2363,  2366,  2367,  2369,  2370,  2374,  2375,
    2377,  2379,  2382,  2384,  2386,  2387,  2391,  2392,  2396,  2397,
    2403,  2404,  2408,  2409,  2412,  2413,  2414,  2423,  2427,  2428,
    2429,  2433,  2434,  2436,  2437,  2445,  2446,  2449,  2450,  2454,
    2458,  2459,  2462,  2464,  2467,  2472,  2474,  2476,  2478,  2480,
    2482,  2484,  2486,  2487,  2489,  2490,  2494,  2495,  2500,  2502,
    2504,  2506,  2508,  2511,  2513,  2515,  2517,  2518,  2522,  2524,
    2527,  2530,  2533,  2535,  2537,  2539,  2542,  2545,  2547,  2550,
    2555,  2558,  2559,  2561,  2563,  2565,  2567,  2572,  2578,  2579,
    2584,  2585,  2587,  2588,  2592,  2593,  2597,  2601,  2606,  2607,
    2612,  2617,  2624,  2625,  2627,  2628,  2632,  2633,  2639,  2641,
    2643,  2645,  2647,  2648,  2652,  2653,  2657,  2660,  2661,  2665,
    2668,  2669,  2674,  2677,  2678,  2680,  2682,  2686,  2687,  2689,
    2692,  2696,  2700,  2701,  2705,  2707,  2711,  2719,  2720,  2731,
    2732,  2735,  2736,  2739,  2742,  2746,  2750,  2753,  2754,  2758,
    2759,  2761,  2763,  2764,  2766,  2767,  2772,  2773,  2781,  2782,
    2784,  2785,  2793,  2794,  2797,  2801,  2802,  2804,  2806,  2807,
    2812,  2817,  2818,  2826,  2827,  2830,  2831,  2832,  2837,  2839,
    2842,  2843,  2848,  2849,  2851,  2852,  2856,  2858,  2860,  2862,
    2864,  2866,  2871,  2876,  2880,  2885,  2887,  2889,  2891,  2894,
    2898,  2900,  2903,  2907,  2911,  2912,  2916,  2917,  2925,  2926,
    2932,  2933,  2936,  2937,  2940,  2941,  2945,  2946,  2949,  2954,
    2955,  2958,  2963,  2964,  2965,  2973,  2974,  2979,  2982,  2985,
    2988,  2991,  2994,  2995,  2997,  2998,  3003,  3006,  3007,  3010,
    3013,  3014,  3023,  3025,  3028,  3030,  3034,  3038,  3039,  3043,
    3044,  3046,  3047,  3052,  3057,  3064,  3071,  3072,  3074,  3077,
    3078,  3080,  3081,  3085,  3086,  3094,  3095,  3100,  3101,  3103,
    3105,  3106,  3116,  3117,  3121,  3123,  3127,  3130,  3133,  3136,
    3140,  3141,  3145,  3146,  3150,  3151,  3155,  3156,  3158,  3160,
    3162,  3164,  3173,  3174,  3176,  3178,  3180,  3182,  3184,  3186,
    3187,  3189,  3190,  3192,  3194,  3196,  3198,  3200,  3202,  3204,
    3205,  3207,  3213,  3215,  3218,  3224,  3225,  3234,  3235,  3238,
    3239,  3244,  3248,  3252,  3254,  3256,  3257,  3259,  3261,  3262,
    3264,  3267,  3270,  3271,  3272,  3276,  3277,  3278,  3282,  3285,
    3286,  3287,  3291,  3292,  3293,  3297,  3300,  3301,  3302,  3306,
    3307,  3308,  3312,  3314,  3316,  3319,  3320,  3324,  3325,  3329,
    3331,  3333,  3336,  3337,  3341,  3342,  3346,  3347,  3349,  3351,
    3353,  3356,  3357,  3361,  3362,  3366,  3367,  3371,  3373,  3375,
    3376,  3379,  3381,  3384,  3387,  3389,  3391,  3393,  3395,  3397,
    3399,  3401,  3403,  3405,  3407,  3409,  3411,  3413,  3415,  3417,
    3419,  3421,  3423,  3425,  3427,  3429,  3431,  3433,  3435,  3437,
    3440,  3442,  3444,  3447,  3449,  3452,  3454,  3460,  3462,  3468,
    3470,  3474,  3475,  3477,  3479,  3481,  3485,  3489,  3493,  3497,
    3500,  3503,  3507,  3511,  3513,  3517,  3519,  3522,  3525,  3527,
    3529,  3531,  3534,  3536,  3538,  3541,  3543,  3544,  3547,  3549,
    3551,  3553,  3557,  3559,  3561,  3564,  3566,  3567,  3569,  3571,
    3573,  3575,  3577,  3580,  3582,  3586,  3588,  3591,  3593,  3597,
    3601,  3605,  3610,  3614,  3616,  3618,  3620,  3622,  3626,  3630,
    3634,  3636,  3638,  3640,  3642,  3644,  3646,  3648,  3650,  3652,
    3654,  3656,  3658,  3660,  3662,  3664,  3666,  3668,  3670,  3672,
    3674,  3676,  3679,  3682,  3686,  3688,  3692,  3696,  3701,  3707,
    3709,  3711,  3714,  3716,  3720,  3722,  3724,  3726,  3728,  3730,
    3732,  3734,  3737,  3740,  3746,  3752,  3758,  3764,  3770,  3776,
    3782,  3787,  3793,  3796,  3797,  3802,  3808,  3809,  3813,  3814,
    3816,  3818,  3822,  3826,  3828,  3832,  3834,  3838,  3839,  3840,
    3842,  3843,  3845,  3846,  3848,  3849,  3851,  3853,  3854,  3856,
    3857,  3859,  3860,  3862,  3863,  3866,  3868,  3870,  3873,  3876,
    3879,  3881,  3884,  3886,  3887,  3889,  3890,  3892,  3893,  3895,
    3896,  3898,  3899,  3901,  3902,  3904,  3905,  3907,  3908,  3910,
    3911,  3913,  3914,  3916,  3917,  3919,  3920,  3922,  3923,  3925,
    3926,  3928,  3929,  3931,  3932,  3934,  3935,  3937,  3939,  3940,
    3942,  3943,  3945,  3947,  3948,  3950,  3951,  3953,  3954,  3956,
    3957,  3959,  3960,  3962,  3963,  3965,  3968,  3969,  3971,  3972,
    3974,  3975,  3977,  3978,  3980,  3981,  3983,  3984,  3986,  3987,
    3989,  3992,  3993,  3995,  3996,  3998,  3999,  4001,  4002,  4004,
    4005,  4007,  4008,  4010,  4011,  4013,  4014,  4016,  4017
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
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
      -1,    28,  1138,   540,   111,    -1,    -1,   111,    -1,   295,
      -1,    -1,   161,    -1,   117,    -1,   227,    -1,   112,    -1,
    1073,    -1,     4,  1120,  1115,   543,    -1,   354,    -1,   117,
      -1,   306,    -1,    19,   309,  1117,  1115,   557,  1089,    -1,
    1099,  1115,   430,    -1,   547,   374,  1115,  1055,  1056,    -1,
      -1,   395,    -1,   364,    -1,   231,  1120,  1115,   549,    -1,
     235,   550,    -1,    31,   550,    -1,   158,    -1,    -1,   429,
     231,   270,   551,    -1,   429,   231,   270,   242,   551,    -1,
     429,   337,    -1,   309,    -1,   311,    -1,   276,  1115,   553,
      -1,   553,    -1,   195,    -1,  1127,  1105,   354,    -1,   316,
      -1,   224,   354,    -1,   282,  1107,  1115,  1057,    -1,   309,
     107,  1115,   371,    -1,   309,  1117,  1115,   557,    -1,  1055,
      -1,  1055,   444,  1054,    -1,  1055,   366,  1115,  1054,    -1,
     316,  1117,  1115,  1055,    -1,   329,  1076,  1102,    -1,   356,
    1140,   561,    -1,     9,  1125,    -1,   251,  1125,    -1,   308,
     271,    -1,    -1,   209,   443,   563,    -1,    -1,   564,   443,
      -1,   565,    -1,   564,   565,    -1,   566,    -1,   568,    -1,
     340,   567,  1102,  1112,  1046,    -1,    -1,   309,    -1,   364,
      -1,   365,    -1,   242,  1111,  1134,  1109,   569,    -1,   570,
      -1,   569,   570,    -1,  1047,   571,    -1,    -1,   291,  1076,
      -1,    -1,    96,   114,   443,   573,   604,   649,   651,   653,
     694,    -1,    -1,    -1,   395,   346,   443,   574,   576,    -1,
      -1,   579,   575,   578,    -1,    -1,   576,   577,    -1,   579,
     580,   606,    -1,   580,   606,    -1,   578,   577,    -1,   162,
      -1,   344,    -1,    -1,  1047,   581,   582,   443,    -1,    -1,
     582,   583,    -1,  1115,   161,    -1,  1115,   181,    -1,   584,
      -1,   586,    -1,   590,    -1,   592,    -1,   594,    -1,   595,
      -1,   601,    -1,   602,    -1,   603,    -1,    46,  1109,  1076,
     589,   585,    -1,    -1,   311,    -1,    55,    -1,   309,  1109,
    1076,  1108,    -1,   309,  1109,  1076,   393,  1076,  1108,    -1,
     309,  1115,   425,  1114,  1132,   588,   589,  1108,   587,    -1,
      -1,   108,  1123,  1055,    -1,    -1,  1113,  1076,    -1,    -1,
     393,  1076,    -1,   212,  1097,   591,    -1,   370,    -1,   269,
      -1,   424,   267,   430,  1115,   593,    -1,   424,   267,   164,
    1115,   593,    -1,   227,    -1,  1073,    -1,    96,  1097,  1054,
      -1,   222,  1115,  1057,  1119,   596,    -1,    -1,   596,   597,
      -1,   598,    -1,   599,    -1,   600,    -1,  1140,   168,  1104,
    1057,  1119,    -1,  1104,   399,  1057,  1119,    -1,  1104,    47,
    1057,    -1,   310,  1120,  1115,   430,    -1,    59,  1115,   430,
      -1,   322,  1115,   693,    -1,   324,  1101,   693,    -1,    -1,
      -1,   432,   346,   443,   605,   606,    -1,    -1,   607,    -1,
      -1,   608,   609,    -1,  1087,   610,   443,    -1,   609,  1087,
     610,   443,    -1,   609,   443,    -1,   617,    -1,    -1,   612,
     613,   611,   618,    -1,   430,    -1,    -1,   165,    -1,   430,
      -1,   430,    -1,    -1,  1115,   181,    -1,  1077,    -1,   218,
    1122,  1072,    -1,    49,  1122,  1072,    -1,   612,   614,    80,
     615,  1103,   616,    -1,    -1,   618,   619,    -1,   620,    -1,
     621,    -1,   623,    -1,   624,    -1,   625,    -1,   627,    -1,
     628,    -1,   637,    -1,   638,    -1,   640,    -1,   641,    -1,
     642,    -1,   647,    -1,   648,    -1,   313,  1072,    -1,  1115,
     161,   622,    -1,    -1,    26,   227,    -1,  1115,   181,    -1,
     288,    -1,   626,    -1,   421,  1115,   626,    -1,    36,    -1,
      70,    -1,    72,    -1,    73,    -1,    74,    -1,    75,    -1,
      76,    -1,    77,    -1,   112,    -1,   194,    -1,   281,    -1,
     290,    -1,   303,    -1,   361,    -1,   359,    -1,   360,    -1,
     410,    -1,   408,    -1,   409,    -1,    38,   358,    -1,    38,
     407,    -1,    38,    -1,    41,   358,    -1,    41,   407,    -1,
      41,    -1,    40,   358,    -1,    40,   407,    -1,    40,    -1,
      39,   358,    -1,    39,   407,    -1,    39,    -1,    37,   358,
      -1,    37,   407,    -1,    37,    -1,   244,    -1,  1131,   216,
    1095,    -1,  1131,   400,  1095,    -1,   266,  1076,   629,  1137,
     630,   631,   634,    -1,    -1,   393,  1076,    -1,    -1,   108,
    1123,  1055,    -1,   632,    -1,    -1,   632,   633,  1117,  1115,
    1054,    -1,    27,    -1,   109,    -1,    -1,   195,  1106,   635,
      -1,   636,    -1,   635,   636,    -1,   430,    -1,   210,  1128,
      -1,   383,   639,    -1,    -1,   217,    -1,   336,    -1,    42,
    1139,   436,    -1,    33,    -1,    -1,   424,  1116,   644,   643,
    1139,  1129,  1138,   646,    -1,   645,    -1,   644,   645,    -1,
    1077,    -1,  1077,   390,  1077,    -1,    -1,   394,  1115,  1077,
      -1,   320,  1073,    -1,   320,  1073,   390,  1073,    -1,    21,
     218,    -1,    -1,    -1,   230,   346,   443,   650,   606,    -1,
      -1,    -1,   226,   346,   443,   652,   606,    -1,    -1,    -1,
     322,   346,   443,   654,   655,    -1,    -1,   656,    -1,   657,
      -1,   656,   657,    -1,   307,   693,   658,   443,   672,    -1,
      -1,   658,   659,    -1,  1115,   181,    -1,    58,  1115,  1068,
      -1,   660,    -1,   664,    -1,    84,   661,    -1,    85,   661,
      -1,   662,   663,    -1,    -1,   166,    -1,  1071,    -1,   663,
    1071,    -1,   283,  1116,   670,   665,   666,   667,   668,   669,
      -1,    -1,   186,  1115,  1076,    -1,    -1,   167,   110,  1115,
    1076,    -1,    -1,   213,    87,  1115,  1076,    -1,    -1,   214,
    1115,  1076,    -1,    -1,   168,  1115,  1076,    -1,  1076,    -1,
    1076,   671,  1076,    64,    -1,  1076,   671,    -1,   224,    -1,
     225,    -1,    -1,   672,   673,    -1,   612,   613,   674,   443,
      -1,    -1,   674,   675,    -1,   676,    -1,   678,    -1,   685,
      -1,   624,    -1,   625,    -1,   627,    -1,   637,    -1,   679,
      -1,   640,    -1,   690,    -1,   680,    -1,   642,    -1,   683,
      -1,   691,    -1,   628,    -1,   684,    -1,   403,  1115,   677,
      -1,   326,    -1,   285,    -1,    87,    -1,   110,    -1,    86,
      -1,   284,    -1,   325,    -1,   249,   185,  1115,  1076,    -1,
      63,  1121,  1115,  1076,    -1,    63,   261,    -1,    64,    -1,
     681,    -1,   680,   681,    -1,   380,  1122,   682,    -1,  1055,
      -1,   293,   427,  1027,    -1,   425,  1071,   173,  1062,    48,
    1062,    -1,   686,   687,    -1,   224,   689,  1116,    -1,   225,
    1101,    -1,   688,    -1,   687,   688,    -1,   289,  1076,    -1,
    1076,    -1,   249,   283,    -1,    -1,   260,    -1,   261,    -1,
     366,  1115,  1071,  1094,    -1,   185,   692,    -1,    -1,   196,
      -1,   430,    -1,    -1,    -1,    -1,   341,   346,   443,   695,
     696,   697,    -1,    -1,   698,    -1,   699,    -1,   698,   699,
      -1,   617,    -1,    -1,   612,   613,   700,   701,   443,    -1,
      -1,   701,   702,    -1,    43,    -1,    44,    -1,    35,    -1,
      45,    -1,   152,   147,    -1,   152,   149,    -1,   187,    -1,
     233,    -1,   333,    -1,   404,    -1,   280,    -1,    30,    -1,
     347,    -1,   328,    -1,   174,    -1,   304,    -1,   224,  1121,
    1115,   703,  1070,    -1,    63,  1121,  1115,   704,  1070,    -1,
     170,  1115,  1070,    -1,    32,  1115,  1070,    -1,   625,    -1,
     640,    -1,   637,    -1,   627,    -1,   642,    -1,   624,    -1,
     705,    -1,   423,  1071,    -1,   173,  1069,    -1,   393,  1071,
      -1,    -1,   289,    -1,   437,    -1,   238,    -1,   438,    -1,
      -1,   289,    -1,   437,    -1,   238,    -1,   438,    -1,   266,
    1076,  1137,    -1,    -1,    -1,    -1,   297,   114,   709,   717,
     443,   707,   718,   708,   720,    -1,    -1,    -1,   423,   710,
     712,    -1,    -1,    53,   711,   712,    -1,   713,    -1,   712,
     713,    -1,   714,   715,   716,   430,    -1,    -1,  1106,   315,
      -1,  1106,   424,    -1,    -1,   362,  1115,    30,    -1,   362,
    1115,   104,    -1,   407,   362,  1115,  1076,    -1,   362,  1115,
    1076,    -1,    -1,   273,    -1,    -1,   331,   430,    -1,    -1,
      -1,   103,   443,   719,   720,   120,   103,   443,    -1,    -1,
     720,   721,    -1,   722,    -1,   723,    -1,   724,    -1,   730,
     443,    -1,     1,   443,    -1,   443,    -1,   725,   346,   726,
     443,    -1,   430,   443,    -1,   725,    -1,   430,    -1,    -1,
     227,    -1,    -1,    -1,   728,   729,   730,    -1,    -1,   731,
     732,    -1,   730,   732,    -1,   733,    -1,   743,    -1,   748,
      -1,   752,    -1,   755,    -1,   768,    -1,   771,    -1,   781,
      -1,   776,    -1,   782,    -1,   783,    -1,   786,    -1,   794,
      -1,   798,    -1,   800,    -1,   815,    -1,   818,    -1,   820,
      -1,   822,    -1,   825,    -1,   827,    -1,   833,    -1,   842,
      -1,   844,    -1,   861,    -1,   863,    -1,   866,    -1,   870,
      -1,   876,    -1,   886,    -1,   893,    -1,   895,    -1,   898,
      -1,   902,    -1,   903,    -1,   914,    -1,   925,    -1,   935,
      -1,   941,    -1,   944,    -1,   950,    -1,   954,    -1,   956,
      -1,   958,    -1,   960,    -1,   963,    -1,   974,    -1,   987,
      -1,   250,    -1,    -1,     3,   734,   735,   742,    -1,  1071,
     736,   739,   994,    -1,  1071,   173,   154,   211,    -1,  1071,
     173,   225,    -1,  1071,   173,    64,    -1,  1071,   173,    97,
      -1,  1071,   173,    97,   435,    -1,  1071,   173,    98,    -1,
    1071,   173,    98,   434,    -1,  1071,   173,    99,    -1,  1071,
     173,   391,    -1,  1071,   173,    66,    -1,  1071,   173,   146,
     994,    -1,  1071,   173,   144,  1066,   994,    -1,  1071,   173,
      24,    -1,  1071,   173,    25,   994,    -1,  1071,   173,  1049,
      -1,  1071,   173,   430,    -1,    -1,  1104,   737,   738,    -1,
    1104,   738,   737,    -1,  1104,   737,    -1,  1104,   738,    -1,
      29,  1066,    -1,   224,  1121,  1068,    -1,    63,  1121,  1068,
      -1,   291,  1121,  1068,    -1,    -1,   429,   740,    -1,   741,
      -1,   740,   741,    -1,    35,    -1,    45,    -1,   187,    -1,
     233,    -1,   333,    -1,   404,    -1,   280,    -1,   170,  1115,
    1070,    -1,    32,  1115,  1070,    -1,   343,   413,  1026,    -1,
     343,   115,  1026,    -1,    30,    -1,   174,    -1,   328,    -1,
     347,    -1,   414,    -1,   304,    -1,    -1,   121,    -1,    -1,
       5,   744,   745,   747,    -1,  1061,   393,  1042,  1000,    -1,
    1061,   746,   180,  1042,  1000,    -1,    89,  1071,   393,  1071,
    1094,  1000,    -1,    -1,   393,  1062,    -1,    -1,   122,    -1,
      -1,    10,   749,   750,    -1,   430,  1090,   751,    -1,  1028,
      55,  1090,   331,  1060,    -1,    -1,   331,  1060,    -1,    18,
     753,    -1,    -1,   753,  1051,   393,   754,  1051,    -1,    -1,
     299,   393,    -1,    -1,    50,   756,  1069,   757,   762,   763,
     765,   767,    -1,    -1,    -1,   423,   758,   759,    -1,   760,
      -1,   759,   760,    -1,   761,   269,    -1,   761,   715,  1062,
      -1,    -1,  1106,   315,    -1,  1106,    82,    -1,  1106,   424,
      -1,    -1,   331,  1071,    -1,   180,  1071,    -1,    -1,    -1,
     981,   764,   727,    -1,    -1,    -1,   982,   766,   727,    -1,
      -1,   123,    -1,    -1,    51,   769,   770,    -1,    -1,   770,
    1068,    -1,    -1,    57,   772,   773,    -1,    -1,   773,  1047,
     774,    -1,    -1,   775,    -1,   775,  1112,   319,    -1,  1140,
     251,   334,    -1,  1140,   231,    -1,   314,    -1,   405,    -1,
      -1,    71,   777,   778,   779,    -1,  1042,   780,  1028,  1000,
      -1,    -1,   124,    -1,   444,    -1,   150,    -1,    68,    -1,
      83,    -1,    -1,   105,   784,  1047,  1127,  1020,   785,    -1,
      -1,   125,    -1,    -1,   112,   787,   788,   793,    -1,  1068,
     418,   995,    -1,  1068,   419,   995,    -1,  1068,   416,   995,
      -1,  1068,   417,   995,    -1,  1061,   736,   789,   790,   995,
      -1,    -1,   415,  1049,    -1,   415,   430,    -1,   415,   295,
      -1,   415,    91,    -1,    -1,  1140,   259,    -1,   429,   791,
      -1,   792,    -1,   791,   792,    -1,    35,    -1,    45,    -1,
     152,   147,    -1,   152,   149,    -1,   187,    -1,   233,    -1,
     333,    -1,   404,    -1,   280,    -1,   170,  1115,  1070,    -1,
      32,  1115,  1070,    -1,   343,   413,  1026,    -1,   343,   115,
    1026,    -1,    43,    -1,    44,    -1,    -1,   126,    -1,    -1,
     113,   795,   796,   797,    -1,  1062,   203,  1042,  1000,    -1,
    1062,   203,  1062,   180,  1042,  1000,    -1,  1062,    48,  1062,
     180,  1042,  1000,    -1,  1062,   203,  1062,   180,  1043,   318,
    1043,  1000,    -1,  1062,    48,  1062,   180,  1043,   318,  1043,
    1000,    -1,    -1,   127,    -1,    -1,   143,   799,   227,   757,
      -1,    -1,   155,   801,   802,   804,   814,    -1,   803,    -1,
     802,    17,   803,    -1,  1028,    -1,   398,    -1,   394,    -1,
     805,   808,    -1,   806,    -1,   805,   806,    -1,    -1,   810,
     807,   727,    -1,    -1,    -1,   427,   277,   809,   727,    -1,
     427,   811,    -1,   810,   427,   811,    -1,   812,    -1,   811,
      17,   812,    -1,  1029,   813,    -1,    21,    -1,   398,    -1,
     394,    -1,    -1,   390,  1028,    -1,    -1,   128,    -1,    -1,
     159,   816,   817,    -1,    -1,   300,    -1,   287,    -1,   287,
      95,    -1,   346,    -1,   286,    -1,    -1,   172,   819,  1059,
      -1,    -1,   179,   821,  1071,    -1,    -1,   182,  1138,   823,
    1050,   824,    -1,    -1,   108,  1123,  1071,    -1,    -1,   183,
     826,    -1,    -1,    -1,   190,   828,  1027,  1136,   829,   727,
     830,   832,    -1,   190,     1,   130,    -1,    -1,    -1,   119,
     831,   727,    -1,    -1,   130,    -1,    -1,   197,   834,  1059,
     835,   836,   837,   841,    -1,    -1,  1140,   165,    -1,    -1,
       9,  1138,   424,    -1,   840,  1138,   424,    -1,    -1,   321,
     838,    -1,   839,    -1,   838,   839,    -1,   840,  1110,    48,
    1062,    -1,    12,    -1,    15,    -1,   262,    -1,    16,    -1,
     263,    -1,   244,    -1,   245,    -1,    -1,   104,    -1,    -1,
     199,   843,   663,    -1,    -1,   202,   845,   846,   847,    -1,
    1071,    -1,  1077,    -1,  1080,    -1,   848,    -1,   847,   848,
      -1,   849,    -1,   853,    -1,   858,    -1,    -1,   384,   850,
     851,    -1,   852,    -1,   851,   852,    -1,  1066,   169,    -1,
      55,   859,    -1,     9,    -1,   216,    -1,   400,    -1,  1066,
     859,    -1,   321,   854,    -1,   855,    -1,   854,   855,    -1,
      55,    48,  1066,   859,    -1,   856,   857,    -1,    -1,     9,
      -1,   216,    -1,   167,    -1,   400,    -1,  1066,    48,  1067,
     859,    -1,    88,  1066,   393,  1067,   859,    -1,    -1,   859,
     991,   860,  1062,    -1,    -1,   396,    -1,    -1,   237,   862,
     927,    -1,    -1,   241,   864,   865,    -1,  1062,   393,  1059,
      -1,    89,  1062,   393,  1059,    -1,    -1,   243,   867,   868,
     869,    -1,  1062,    48,  1042,  1000,    -1,  1062,    48,  1062,
     180,  1042,  1000,    -1,    -1,   131,    -1,    -1,   272,   871,
     872,    -1,    -1,   872,   873,   874,  1046,   875,    -1,   200,
      -1,   278,    -1,   208,    -1,   160,    -1,    -1,   356,  1140,
     561,    -1,    -1,  1140,   251,   334,    -1,  1140,   231,    -1,
      -1,   287,   877,   878,    -1,   881,   882,    -1,    -1,   882,
     879,   727,   880,    -1,   882,   132,    -1,    -1,   132,    -1,
    1051,    -1,  1051,   390,  1051,    -1,    -1,   171,    -1,  1069,
     392,    -1,   883,   412,  1027,    -1,   883,   425,   884,    -1,
      -1,  1140,   387,   991,    -1,   885,    -1,   884,     8,   885,
      -1,  1071,   173,  1062,    48,  1062,   412,  1027,    -1,    -1,
     308,   887,  1047,  1091,  1127,   888,   889,   890,   891,   892,
      -1,    -1,   203,  1071,    -1,    -1,   192,   231,    -1,  1140,
     231,    -1,  1140,   251,   231,    -1,  1140,   191,   231,    -1,
    1140,   426,    -1,    -1,   211,  1115,  1071,    -1,    -1,  1010,
      -1,  1021,    -1,    -1,   134,    -1,    -1,   317,   894,  1044,
     989,    -1,    -1,   330,   896,  1047,  1127,   888,  1010,   897,
      -1,    -1,   135,    -1,    -1,   335,   899,  1044,   989,   900,
    1020,   901,    -1,    -1,  1140,   231,    -1,  1140,   251,   231,
      -1,    -1,   136,    -1,   337,    -1,    -1,   345,   904,   905,
     913,    -1,  1045,   907,   908,   910,    -1,    -1,     9,  1045,
     908,   427,  1028,   906,   727,    -1,    -1,   425,  1071,    -1,
      -1,    -1,  1104,   120,   909,   727,    -1,   911,    -1,   911,
     910,    -1,    -1,   427,  1027,   912,   727,    -1,    -1,   137,
      -1,    -1,   355,   915,   916,    -1,   917,    -1,   918,    -1,
     919,    -1,   921,    -1,   923,    -1,   144,  1066,   393,  1066,
      -1,  1059,   393,   143,  1065,    -1,  1059,   393,  1062,    -1,
    1059,   920,    48,  1062,    -1,   413,    -1,   115,    -1,   922,
      -1,   921,   922,    -1,  1048,   393,   505,    -1,   924,    -1,
     923,   924,    -1,  1059,   393,   398,    -1,  1059,   393,   394,
      -1,    -1,   364,   926,   927,    -1,    -1,  1073,   929,   931,
     932,   928,   933,   934,    -1,    -1,   929,  1123,   633,  1117,
     930,    -1,    -1,   930,  1073,    -1,    -1,  1098,  1124,    -1,
      -1,  1099,  1115,  1055,    -1,    -1,   423,  1046,    -1,   200,
     297,  1115,   881,    -1,    -1,   180,  1046,    -1,   278,   297,
    1115,   881,    -1,    -1,    -1,   373,   936,  1047,   937,   938,
    1020,   940,    -1,    -1,   211,  1115,   939,  1062,    -1,  1092,
    1033,    -1,  1092,  1034,    -1,  1092,  1035,    -1,  1092,  1036,
      -1,  1092,  1037,    -1,    -1,   138,    -1,    -1,   375,   339,
     942,   943,    -1,   375,   227,    -1,    -1,   331,  1062,    -1,
     180,  1062,    -1,    -1,   376,   945,   946,   203,  1071,   948,
    1005,   949,    -1,   947,    -1,   946,   947,    -1,  1062,    -1,
     106,  1106,   362,    -1,   106,  1106,  1062,    -1,    -1,  1140,
     290,  1071,    -1,    -1,   139,    -1,    -1,   379,   951,   952,
     953,    -1,  1061,   173,  1042,  1000,    -1,  1061,   173,  1062,
     180,  1042,  1000,    -1,    89,  1071,   173,  1071,  1094,  1000,
      -1,    -1,   140,    -1,   381,   955,    -1,    -1,   296,    -1,
      -1,   386,   957,   663,    -1,    -1,   401,   959,  1071,   173,
    1066,   393,  1067,    -1,    -1,   406,   961,  1047,   962,    -1,
      -1,   309,    -1,   311,    -1,    -1,   411,   964,  1071,   965,
     968,   948,   972,  1005,   973,    -1,    -1,   106,  1106,   966,
      -1,   967,    -1,   966,   274,   967,    -1,  1088,  1066,    -1,
     203,   969,    -1,   968,   969,    -1,  1071,   970,   971,    -1,
      -1,   107,  1114,  1071,    -1,    -1,    90,  1114,  1071,    -1,
      -1,   384,  1114,  1071,    -1,    -1,   141,    -1,   975,    -1,
     984,    -1,   986,    -1,   422,   976,   978,   979,   980,   983,
    1123,   977,    -1,    -1,   181,    -1,  1046,    -1,   200,    -1,
     278,    -1,   208,    -1,   160,    -1,    -1,     8,    -1,    -1,
     370,    -1,   157,    -1,   153,    -1,   157,    -1,   279,    -1,
     255,    -1,   257,    -1,    -1,   297,    -1,   422,  1112,   101,
    1123,   985,    -1,  1051,    -1,     9,   298,    -1,   422,   976,
      34,   323,  1071,    -1,    -1,   433,   988,  1044,   989,   900,
     990,   992,   993,    -1,    -1,   173,  1068,    -1,    -1,   991,
    1100,  1070,  1118,    -1,   991,  1100,  1049,    -1,   991,  1100,
     283,    -1,    34,    -1,     8,    -1,    -1,  1015,    -1,  1021,
      -1,    -1,   142,    -1,   996,   998,    -1,   996,   998,    -1,
      -1,    -1,   157,   997,   727,    -1,    -1,    -1,   255,   999,
     727,    -1,  1001,  1003,    -1,    -1,    -1,   363,  1002,   727,
      -1,    -1,    -1,   258,  1004,   727,    -1,  1006,  1008,    -1,
      -1,    -1,   279,  1007,   727,    -1,    -1,    -1,   257,  1009,
     727,    -1,  1011,    -1,  1013,    -1,  1011,  1013,    -1,    -1,
     120,  1012,   727,    -1,    -1,   253,  1014,   727,    -1,  1016,
      -1,  1018,    -1,  1016,  1018,    -1,    -1,   148,  1017,   727,
      -1,    -1,   254,  1019,   727,    -1,    -1,  1021,    -1,  1022,
      -1,  1024,    -1,  1022,  1024,    -1,    -1,   206,  1023,   727,
      -1,    -1,   256,  1025,   727,    -1,    -1,  1106,  1070,  1118,
      -1,  1028,    -1,  1029,    -1,    -1,  1030,  1031,    -1,  1032,
      -1,  1031,   207,    -1,  1031,  1032,    -1,  1062,    -1,   445,
      -1,   446,    -1,   437,    -1,   438,    -1,   439,    -1,   440,
      -1,   442,    -1,  1033,    -1,  1034,    -1,  1035,    -1,   178,
      -1,   215,    -1,   247,    -1,   252,    -1,    20,    -1,   274,
      -1,   269,    -1,   262,    -1,    12,    -1,    13,    -1,    14,
      -1,   292,    -1,   248,    -1,   444,    -1,   150,  1138,    -1,
     151,    -1,   447,    -1,   184,  1135,    -1,   448,    -1,   219,
    1135,    -1,   178,    -1,   184,  1135,   274,   150,  1138,    -1,
     215,    -1,   219,  1135,   274,   150,  1138,    -1,  1040,    -1,
    1038,  1039,  1040,    -1,    -1,    67,    -1,   350,    -1,  1063,
      -1,  1040,   437,  1040,    -1,  1040,   438,  1040,    -1,  1040,
     439,  1040,    -1,  1040,   440,  1040,    -1,   437,  1040,    -1,
     438,  1040,    -1,  1040,   442,  1040,    -1,   445,  1040,   446,
      -1,   223,    -1,   223,  1096,   430,    -1,  1043,    -1,  1042,
    1043,    -1,  1062,  1094,    -1,  1073,    -1,  1073,    -1,  1047,
      -1,  1046,  1047,    -1,   430,    -1,  1049,    -1,  1048,  1049,
      -1,   239,    -1,    -1,  1050,  1051,    -1,  1052,    -1,  1073,
      -1,  1053,    -1,  1053,  1096,  1053,    -1,   227,    -1,  1055,
      -1,  1054,  1055,    -1,  1073,    -1,    -1,  1055,    -1,  1055,
      -1,   227,    -1,   430,    -1,  1060,    -1,  1059,  1060,    -1,
    1071,    -1,     6,  1122,  1072,    -1,  1062,    -1,  1061,  1062,
      -1,  1071,    -1,   218,  1122,  1072,    -1,   218,  1122,  1078,
      -1,   218,  1122,  1080,    -1,     6,  1122,  1064,  1065,    -1,
       6,  1122,  1072,    -1,  1077,    -1,  1080,    -1,  1041,    -1,
    1071,    -1,   218,  1122,  1072,    -1,   218,  1122,  1078,    -1,
     218,  1122,  1080,    -1,  1078,    -1,  1080,    -1,  1041,    -1,
     300,    -1,   143,    -1,  1072,    -1,   227,    -1,  1071,    -1,
    1078,    -1,  1071,    -1,  1077,    -1,  1071,    -1,   227,    -1,
    1071,    -1,   227,    -1,  1080,    -1,  1071,    -1,  1076,    -1,
     436,    -1,  1072,    -1,  1073,    -1,  1073,  1074,    -1,  1073,
    1075,    -1,  1073,  1074,  1075,    -1,   430,    -1,   430,  1096,
    1073,    -1,   445,  1038,   446,    -1,   445,  1040,   449,   446,
      -1,   445,  1040,   449,  1040,   446,    -1,   227,    -1,  1078,
      -1,     9,  1079,    -1,  1079,    -1,  1078,   450,  1079,    -1,
     227,    -1,   368,    -1,   436,    -1,   305,    -1,   188,    -1,
     234,    -1,   397,    -1,    93,  1081,    -1,   428,  1081,    -1,
     420,   445,  1040,   446,  1081,    -1,   232,   445,  1040,   446,
    1081,    -1,   332,   445,  1040,   446,  1081,    -1,    78,   445,
    1038,   446,  1081,    -1,   377,   445,  1038,   446,  1081,    -1,
     378,   445,  1038,   446,  1081,    -1,   402,   445,  1084,   446,
    1081,    -1,   264,   445,  1085,   446,    -1,   229,   445,  1086,
     446,  1081,    -1,   177,  1082,    -1,    -1,   445,  1040,   449,
     446,    -1,   445,  1040,   449,  1040,   446,    -1,    -1,   445,
    1083,   446,    -1,    -1,  1038,    -1,  1040,    -1,  1040,  1039,
     216,    -1,  1040,  1039,   400,    -1,  1040,    -1,  1040,  1039,
    1040,    -1,  1040,    -1,  1040,  1039,  1055,    -1,    -1,    -1,
       9,    -1,    -1,  1098,    -1,    -1,   198,    -1,    -1,   249,
      -1,   294,    -1,    -1,   252,    -1,    -1,   273,    -1,    -1,
     338,    -1,    -1,   352,  1107,    -1,   193,    -1,   267,    -1,
     309,  1115,    -1,   311,  1101,    -1,   429,   116,    -1,   116,
      -1,    60,   353,    -1,   353,    -1,    -1,     7,    -1,    -1,
      22,    -1,    -1,    23,    -1,    -1,    26,    -1,    -1,    29,
      -1,    -1,    36,    -1,    -1,    48,    -1,    -1,    54,    -1,
      -1,    55,    -1,    -1,    81,    -1,    -1,    96,    -1,    -1,
     395,    -1,    -1,   169,    -1,    -1,   173,    -1,    -1,   193,
      -1,    -1,   207,    -1,    -1,   207,    -1,    22,    -1,    -1,
     211,    -1,    -1,   224,    -1,   225,    -1,    -1,   225,    -1,
      -1,   240,    -1,    -1,   260,    -1,    -1,   267,    -1,    -1,
     270,    -1,    -1,   275,    -1,   193,   275,    -1,    -1,   277,
      -1,    -1,   300,    -1,    -1,   309,    -1,    -1,   336,    -1,
      -1,   355,    -1,    -1,   357,    -1,    -1,   357,    -1,   357,
     207,    -1,    -1,   362,    -1,    -1,   374,    -1,    -1,   385,
      -1,    -1,   388,    -1,    -1,   389,    -1,    -1,   392,    -1,
      -1,   393,    -1,    -1,   427,    -1,    -1,   429,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
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
    1599,  1600,  1601,  1602,  1609,  1613,  1619,  1620,  1621,  1624,
    1625,  1629,  1633,  1634,  1641,  1648,  1652,  1653,  1654,  1661,
    1686,  1696,  1705,  1707,  1708,  1714,  1718,  1719,  1720,  1723,
    1724,  1725,  1729,  1733,  1734,  1740,  1741,  1745,  1754,  1763,
    1772,  1787,  1797,  1804,  1811,  1812,  1813,  1819,  1826,  1833,
    1837,  1838,  1839,  1847,  1848,  1851,  1852,  1856,  1857,  1861,
    1862,  1868,  1893,  1894,  1895,  1896,  1902,  1909,  1910,  1914,
    1917,  1918,  1926,  1927,  1941,  1942,  1942,  1945,  1944,  1957,
    1958,  1962,  1974,  1983,  1987,  1988,  1998,  1997,  2015,  2016,
    2020,  2027,  2034,  2035,  2036,  2037,  2038,  2039,  2040,  2041,
    2042,  2049,  2053,  2053,  2053,  2059,  2071,  2096,  2120,  2121,
    2128,  2129,  2133,  2134,  2141,  2148,  2149,  2156,  2160,  2169,
    2170,  2176,  2186,  2204,  2205,  2209,  2210,  2211,  2215,  2222,
    2229,  2239,  2246,  2264,  2268,  2279,  2280,  2280,  2291,  2292,
    2296,  2296,  2313,  2314,  2316,  2320,  2322,  2321,  2353,  2358,
    2363,  2369,  2378,  2386,  2387,  2395,  2396,  2397,  2401,  2421,
    2425,  2434,  2435,  2436,  2437,  2438,  2439,  2440,  2441,  2442,
    2443,  2444,  2445,  2446,  2447,  2454,  2476,  2498,  2499,  2511,
    2531,  2538,  2539,  2543,  2544,  2545,  2546,  2547,  2548,  2549,
    2550,  2551,  2552,  2553,  2554,  2559,  2564,  2565,  2566,  2567,
    2568,  2569,  2570,  2571,  2572,  2573,  2574,  2575,  2576,  2577,
    2578,  2579,  2580,  2581,  2582,  2590,  2598,  2606,  2613,  2618,
    2629,  2646,  2647,  2650,  2651,  2658,  2682,  2683,  2700,  2701,
    2704,  2705,  2712,  2713,  2718,  2728,  2735,  2738,  2739,  2740,
    2747,  2754,  2779,  2779,  2784,  2785,  2789,  2790,  2793,  2794,
    2807,  2819,  2839,  2853,  2855,  2854,  2874,  2875,  2875,  2888,
    2890,  2889,  2901,  2902,  2906,  2907,  2916,  2923,  2926,  2930,
    2934,  2935,  2936,  2943,  2944,  2948,  2951,  2951,  2954,  2955,
    2961,  2966,  2967,  2970,  2971,  2974,  2975,  2978,  2979,  2982,
    2983,  2987,  2988,  2989,  2993,  2994,  2997,  2998,  3002,  3006,
    3007,  3011,  3012,  3013,  3014,  3015,  3016,  3017,  3018,  3019,
    3020,  3021,  3022,  3023,  3024,  3025,  3026,  3030,  3034,  3035,
    3036,  3037,  3038,  3039,  3040,  3044,  3048,  3049,  3050,  3054,
    3055,  3059,  3063,  3068,  3072,  3076,  3080,  3081,  3085,  3086,
    3090,  3091,  3092,  3095,  3095,  3095,  3098,  3102,  3105,  3105,
    3108,  3115,  3116,  3117,  3116,  3134,  3135,  3139,  3140,  3145,
    3147,  3146,  3182,  3183,  3187,  3188,  3189,  3190,  3191,  3192,
    3193,  3194,  3195,  3196,  3197,  3198,  3199,  3200,  3201,  3202,
    3203,  3207,  3211,  3215,  3219,  3220,  3221,  3222,  3223,  3224,
    3225,  3226,  3233,  3237,  3247,  3250,  3254,  3258,  3262,  3270,
    3273,  3277,  3281,  3285,  3293,  3306,  3308,  3318,  3307,  3345,
    3347,  3346,  3353,  3352,  3361,  3362,  3367,  3374,  3376,  3380,
    3390,  3392,  3400,  3408,  3437,  3468,  3470,  3480,  3485,  3496,
    3497,  3497,  3524,  3525,  3529,  3530,  3531,  3532,  3548,  3552,
    3564,  3595,  3632,  3644,  3647,  3648,  3657,  3661,  3657,  3674,
    3674,  3692,  3696,  3697,  3698,  3699,  3700,  3701,  3702,  3703,
    3704,  3705,  3706,  3707,  3708,  3709,  3710,  3711,  3712,  3713,
    3714,  3715,  3716,  3717,  3718,  3719,  3720,  3721,  3722,  3723,
    3724,  3725,  3726,  3727,  3728,  3729,  3730,  3731,  3732,  3733,
    3734,  3735,  3736,  3737,  3738,  3739,  3740,  3741,  3742,  3743,
    3744,  3767,  3766,  3779,  3783,  3787,  3791,  3795,  3799,  3803,
    3807,  3811,  3815,  3819,  3823,  3827,  3831,  3835,  3839,  3843,
    3850,  3851,  3852,  3853,  3854,  3855,  3859,  3863,  3864,  3867,
    3868,  3872,  3873,  3877,  3878,  3879,  3880,  3881,  3882,  3883,
    3884,  3888,  3892,  3896,  3901,  3902,  3903,  3904,  3905,  3906,
    3910,  3911,  3920,  3920,  3926,  3930,  3934,  3940,  3941,  3945,
    3946,  3955,  3955,  3960,  3964,  3971,  3972,  3981,  3987,  3988,
    3992,  3992,  4000,  4000,  4010,  4012,  4011,  4020,  4021,  4026,
    4033,  4040,  4042,  4046,  4054,  4065,  4066,  4067,  4072,  4076,
    4075,  4087,  4091,  4090,  4101,  4102,  4111,  4111,  4115,  4116,
    4128,  4128,  4132,  4133,  4144,  4145,  4146,  4147,  4148,  4151,
    4151,  4159,  4159,  4165,  4172,  4173,  4176,  4176,  4183,  4196,
    4209,  4209,  4220,  4221,  4231,  4230,  4243,  4247,  4251,  4255,
    4259,  4266,  4267,  4268,  4269,  4270,  4274,  4275,  4276,  4280,
    4281,  4286,  4287,  4288,  4289,  4290,  4291,  4292,  4293,  4294,
    4295,  4299,  4303,  4307,  4312,  4313,  4317,  4318,  4327,  4327,
    4333,  4337,  4341,  4345,  4349,  4356,  4357,  4366,  4366,  4388,
    4387,  4406,  4407,  4412,  4421,  4426,  4434,  4444,  4445,  4451,
    4450,  4463,  4467,  4466,  4478,  4479,  4484,  4485,  4490,  4519,
    4520,  4521,  4524,  4525,  4529,  4530,  4539,  4539,  4544,  4545,
    4553,  4570,  4587,  4605,  4630,  4630,  4643,  4643,  4656,  4656,
    4665,  4669,  4682,  4682,  4695,  4697,  4695,  4705,  4710,  4714,
    4713,  4724,  4725,  4734,  4734,  4742,  4743,  4747,  4748,  4749,
    4753,  4754,  4759,  4760,  4765,  4769,  4770,  4771,  4772,  4773,
    4774,  4775,  4779,  4780,  4789,  4789,  4802,  4801,  4811,  4812,
    4813,  4817,  4818,  4822,  4823,  4824,  4830,  4830,  4835,  4836,
    4840,  4841,  4842,  4843,  4844,  4845,  4851,  4855,  4856,  4860,
    4865,  4869,  4870,  4871,  4872,  4873,  4877,  4903,  4912,  4913,
    4917,  4917,  4925,  4925,  4935,  4935,  4940,  4944,  4956,  4956,
    4962,  4966,  4973,  4974,  4983,  4983,  4987,  4988,  5002,  5003,
    5004,  5005,  5009,  5010,  5014,  5015,  5016,  5028,  5028,  5033,
    5038,  5037,  5047,  5054,  5055,  5059,  5064,  5073,  5076,  5080,
    5085,  5092,  5099,  5100,  5104,  5105,  5110,  5122,  5122,  5145,
    5146,  5150,  5151,  5155,  5159,  5163,  5167,  5174,  5175,  5178,
    5179,  5180,  5184,  5185,  5194,  5194,  5209,  5209,  5220,  5221,
    5230,  5230,  5241,  5242,  5246,  5253,  5254,  5263,  5276,  5276,
    5282,  5287,  5286,  5297,  5298,  5302,  5304,  5303,  5314,  5315,
    5320,  5319,  5330,  5331,  5340,  5340,  5345,  5346,  5347,  5348,
    5349,  5355,  5364,  5368,  5377,  5384,  5385,  5391,  5392,  5396,
    5405,  5406,  5410,  5414,  5426,  5426,  5432,  5431,  5448,  5451,
    5467,  5468,  5471,  5472,  5476,  5477,  5482,  5487,  5495,  5507,
    5512,  5520,  5536,  5537,  5536,  5557,  5558,  5562,  5563,  5564,
    5565,  5566,  5570,  5571,  5580,  5580,  5585,  5592,  5593,  5594,
    5603,  5603,  5612,  5613,  5617,  5618,  5619,  5623,  5624,  5628,
    5629,  5638,  5638,  5644,  5648,  5652,  5659,  5660,  5669,  5676,
    5677,  5685,  5685,  5698,  5698,  5714,  5714,  5723,  5725,  5726,
    5735,  5735,  5745,  5746,  5751,  5752,  5757,  5764,  5765,  5770,
    5777,  5778,  5782,  5783,  5787,  5788,  5792,  5793,  5802,  5803,
    5804,  5808,  5832,  5835,  5843,  5853,  5858,  5863,  5868,  5875,
    5876,  5879,  5880,  5884,  5884,  5888,  5888,  5892,  5892,  5895,
    5896,  5900,  5907,  5908,  5912,  5924,  5924,  5935,  5936,  5941,
    5944,  5948,  5952,  5959,  5960,  5963,  5964,  5965,  5969,  5970,
    5983,  5991,  5998,  6000,  5999,  6009,  6011,  6010,  6025,  6032,
    6034,  6033,  6043,  6045,  6044,  6060,  6066,  6068,  6067,  6077,
    6079,  6078,  6094,  6099,  6104,  6114,  6113,  6125,  6124,  6140,
    6145,  6150,  6160,  6159,  6171,  6170,  6185,  6186,  6190,  6195,
    6200,  6210,  6209,  6221,  6220,  6237,  6240,  6252,  6259,  6266,
    6266,  6276,  6277,  6278,  6282,  6284,  6285,  6287,  6288,  6289,
    6290,  6291,  6293,  6294,  6295,  6296,  6297,  6298,  6300,  6301,
    6302,  6304,  6305,  6306,  6307,  6308,  6311,  6312,  6315,  6315,
    6315,  6316,  6316,  6317,  6317,  6318,  6318,  6319,  6319,  6324,
    6325,  6328,  6329,  6330,  6334,  6335,  6336,  6337,  6338,  6339,
    6340,  6341,  6342,  6353,  6365,  6380,  6381,  6386,  6392,  6398,
    6418,  6422,  6438,  6452,  6453,  6458,  6464,  6465,  6470,  6479,
    6480,  6481,  6485,  6496,  6497,  6501,  6509,  6510,  6514,  6515,
    6521,  6541,  6542,  6546,  6547,  6551,  6552,  6556,  6557,  6558,
    6559,  6560,  6561,  6562,  6563,  6564,  6568,  6569,  6570,  6571,
    6572,  6573,  6574,  6578,  6579,  6583,  6584,  6588,  6589,  6593,
    6594,  6605,  6606,  6610,  6611,  6612,  6616,  6617,  6618,  6626,
    6630,  6631,  6632,  6633,  6637,  6638,  6642,  6650,  6654,  6666,
    6678,  6679,  6689,  6690,  6694,  6695,  6696,  6697,  6698,  6699,
    6700,  6708,  6712,  6716,  6720,  6724,  6728,  6732,  6736,  6740,
    6744,  6748,  6752,  6759,  6760,  6761,  6765,  6766,  6770,  6771,
    6776,  6783,  6790,  6800,  6807,  6817,  6824,  6838,  6848,  6849,
    6853,  6854,  6858,  6859,  6863,  6864,  6865,  6869,  6870,  6874,
    6875,  6879,  6880,  6884,  6885,  6892,  6892,  6893,  6893,  6894,
    6894,  6895,  6895,  6897,  6897,  6898,  6898,  6899,  6899,  6900,
    6900,  6901,  6901,  6902,  6902,  6903,  6903,  6904,  6904,  6905,
    6905,  6906,  6906,  6907,  6907,  6908,  6908,  6909,  6909,  6910,
    6910,  6911,  6911,  6912,  6912,  6913,  6913,  6913,  6914,  6914,
    6915,  6915,  6915,  6916,  6916,  6917,  6917,  6918,  6918,  6919,
    6919,  6920,  6920,  6921,  6921,  6921,  6922,  6922,  6923,  6923,
    6924,  6924,  6925,  6925,  6926,  6926,  6927,  6927,  6928,  6928,
    6928,  6929,  6929,  6930,  6930,  6931,  6931,  6932,  6932,  6933,
    6933,  6934,  6934,  6935,  6935,  6937,  6937,  6938,  6938
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "ACCEPT", "ACCESS", "ADD", 
  "ADDRESS", "ADVANCING", "AFTER", "ALL", "ALLOCATE", "ALPHABET", 
  "ALPHABETIC", "\"ALPHABETIC-LOWER\"", "\"ALPHABETIC-UPPER\"", 
  "ALPHANUMERIC", "\"ALPHANUMERIC-EDITED\"", "ALSO", "ALTER", "ALTERNATE", 
  "AND", "ANY", "ARE", "AREA", "\"ARGUMENT-NUMBER\"", 
  "\"ARGUMENT-VALUE\"", "AS", "ASCENDING", "ASSIGN", "AT", "AUTO", 
  "AUTOMATIC", "\"BACKGROUND-COLOR\"", "BASED", "BEFORE", "BELL", 
  "BINARY", "\"BINARY-C-LONG\"", "\"BINARY-CHAR\"", "\"BINARY-DOUBLE\"", 
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
  "\"END-EVALUATE\"", "\"END FUNCTION\"", "\"END-IF\"", 
  "\"END-MULTIPLY\"", "\"END-PERFORM\"", "\"END PROGRAM\"", 
  "\"END-READ\"", "\"END-RETURN\"", "\"END-REWRITE\"", "\"END-SEARCH\"", 
  "\"END-START\"", "\"END-STRING\"", "\"END-SUBTRACT\"", 
  "\"END-UNSTRING\"", "\"END-WRITE\"", "ENTRY", "ENVIRONMENT", 
  "\"ENVIRONMENT-NAME\"", "\"ENVIRONMENT-VALUE\"", "EOL", "EOP", "EOS", 
  "EQUAL", "EQUALS", "ERASE", "ERROR", "ESCAPE", "EVALUATE", 
  "\"EVENT-STATUS\"", "EXCEPTION", "EXCLUSIVE", "EXIT", "EXTEND", 
  "EXTERNAL", "FD", "\"FILE-CONTROL\"", "\"FILE-ID\"", "FILLER", "FINAL", 
  "FIRST", "FOOTING", "FOR", "\"FOREGROUND-COLOR\"", "FOREVER", "FREE", 
  "FROM", "FULL", "FUNCTION", "\"FUNCTION-ID\"", "\"FUNCTION\"", "GE", 
  "GENERATE", "GIVING", "GLOBAL", "GO", "GOBACK", "GREATER", "GROUP", 
  "HEADING", "HIGHLIGHT", "\"HIGH-VALUE\"", "IDENTIFICATION", "IF", 
  "IGNORE", "IGNORING", "IN", "INDEX", "INDEXED", "INDICATE", 
  "INITIALIZE", "INITIALIZED", "INITIATE", "INPUT", "\"INPUT-OUTPUT\"", 
  "INSPECT", "INTO", "INTRINSIC", "INVALID", "\"INVALID KEY\"", "IS", 
  "\"I-O\"", "\"I-O-CONTROL\"", "JUSTIFIED", "KEY", "LABEL", "LAST", 
  "\"LAST DETAIL\"", "LE", "LEADING", "LEFT", "LENGTH", "LESS", "LIMIT", 
  "LIMITS", "LINAGE", "\"LINAGE-COUNTER\"", "LINE", "LINES", "LINKAGE", 
  "\"Literal\"", "LOCALE", "\"FUNCTION LOCALE\"", "\"LOCAL-STORAGE\"", 
  "LOCK", "\"FUNCTION LOWER-CASE\"", "LOWLIGHT", "\"LOW-VALUE\"", 
  "MANUAL", "MEMORY", "MERGE", "MINUS", "\"MNEMONIC NAME\"", "MODE", 
  "MOVE", "MULTIPLE", "MULTIPLY", "NATIONAL", "\"NATIONAL-EDITED\"", 
  "NATIVE", "NE", "NEGATIVE", "NEXT", "\"NEXT SENTENCE\"", "NO", "NOT", 
  "\"NOT END\"", "\"NOT EOP\"", "\"NOT EXCEPTION\"", 
  "\"NOT INVALID KEY\"", "\"NOT OVERFLOW\"", "\"NOT SIZE ERROR\"", 
  "\"NO ADVANCING\"", "NUMBER", "NUMBERS", "NUMERIC", 
  "\"NUMERIC-EDITED\"", "\"FUNCTION NUMVALC\"", "\"OBJECT-COMPUTER\"", 
  "OCCURS", "OF", "OFF", "OMITTED", "ON", "ONLY", "OPEN", "OPTIONAL", 
  "OR", "ORDER", "ORGANIZATION", "OTHER", "OUTPUT", "OVERFLOW", 
  "OVERLINE", "\"PACKED-DECIMAL\"", "PADDING", "PAGE", "\"PAGE FOOTING\"", 
  "\"PAGE HEADING\"", "PARAGRAPH", "PERFORM", "PICTURE", "PLUS", 
  "POINTER", "POSITION", "POSITIVE", "PRESENT", "PREVIOUS", "PRINTER", 
  "PRINTING", "PROCEDURE", "PROCEDURES", "PROCEED", "PROGRAM", 
  "\"PROGRAM-ID\"", "\"Program name\"", "\"PROGRAM-POINTER\"", "PROMPT", 
  "QUOTE", "RANDOM", "RD", "READ", "RECORD", "RECORDING", "RECORDS", 
  "RECURSIVE", "REDEFINES", "REEL", "REFERENCE", "RELATIVE", "RELEASE", 
  "REMAINDER", "REMOVAL", "RENAMES", "REPLACING", "REPORT", "REPORTING", 
  "REPORTS", "\"REPORT FOOTING\"", "\"REPORT HEADING\"", "REPOSITORY", 
  "REQUIRED", "RESERVE", "RETURN", "RETURNING", "\"FUNCTION REVERSE\"", 
  "\"REVERSE-VIDEO\"", "REWIND", "REWRITE", "RIGHT", "ROLLBACK", 
  "ROUNDED", "RUN", "SAME", "SCREEN", "\"SCREEN-CONTROL\"", "SCROLL", 
  "SD", "SEARCH", "SECTION", "SECURE", "\"SEGMENT-LIMIT\"", "SELECT", 
  "\"semi-colon\"", "SENTENCE", "SEPARATE", "SEQUENCE", "SEQUENTIAL", 
  "SET", "SHARING", "SIGN", "SIGNED", "\"SIGNED-INT\"", "\"SIGNED-LONG\"", 
  "\"SIGNED-SHORT\"", "SIZE", "\"SIZE ERROR\"", "SORT", "\"SORT-MERGE\"", 
  "SOURCE", "\"SOURCE-COMPUTER\"", "SPACE", "\"SPECIAL-NAMES\"", 
  "STANDARD", "\"STANDARD-1\"", "\"STANDARD-2\"", "START", "STATUS", 
  "STOP", "STRING", "\"FUNCTION SUBSTITUTE\"", 
  "\"FUNCTION SUBSTITUTE-CASE\"", "SUBTRACT", "SUM", "SUPPRESS", 
  "SYMBOLIC", "SYNCHRONIZED", "TALLYING", "TAPE", "TERMINATE", "TEST", 
  "THAN", "THEN", "THRU", "TIME", "TIMES", "TO", "\"FALSE\"", "\"FILE\"", 
  "\"INITIAL\"", "\"NULL\"", "\"TRUE\"", "TOP", "TRAILING", "TRANSFORM", 
  "\"FUNCTION TRIM\"", "TYPE", "UNDERLINE", "UNIT", "UNLOCK", "UNSIGNED", 
  "\"UNSIGNED-INT\"", "\"UNSIGNED-LONG\"", "\"UNSIGNED-SHORT\"", 
  "UNSTRING", "UNTIL", "UP", "UPDATE", "UPON", "\"UPON ARGUMENT-NUMBER\"", 
  "\"UPON COMMAND-LINE\"", "\"UPON ENVIRONMENT-NAME\"", 
  "\"UPON ENVIRONMENT-VALUE\"", "\"FUNCTION UPPER-CASE\"", "USAGE", "USE", 
  "USING", "VALUE", "VARYING", "WAIT", "WHEN", 
  "\"FUNCTION WHEN-COMPILED\"", "WITH", "\"Identifier\"", "WORDS", 
  "\"WORKING-STORAGE\"", "WRITE", "YYYYDDD", "YYYYMMDD", "ZERO", "'+'", 
  "'-'", "'*'", "'/'", "UNARY_SIGN", "'^'", "'.'", "'='", "'('", "')'", 
  "'>'", "'<'", "':'", "'&'", "$accept", "start", "@1", "nested_list", 
  "source_element", "program_definition", "@2", "@3", "program_mandatory", 
  "@4", "@5", "function_definition", "@6", "@7", "nested_prog", 
  "end_program", "end_mandatory", "end_function", 
  "identification_division", "@8", "function_division", "program_name", 
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
  "special_name", "mnemonic_name_clause", "@9", 
  "special_name_mnemonic_on_off", "on_or_off", "alphabet_name_clause", 
  "@10", "alphabet_definition", "alphabet_literal_list", 
  "alphabet_literal", "@11", "alphabet_also_sequence", "alphabet_lits", 
  "alphabet_also_literal", "symbolic_characters_clause", 
  "symbolic_characters_list", "char_list", "integer_list", 
  "class_name_clause", "class_item_list", "class_item", "locale_clause", 
  "currency_sign_clause", "decimal_point_clause", "cursor_clause", 
  "crt_status_clause", "screen_control", "event_status", 
  "input_output_section", "@12", "@13", "file_control_paragraph", 
  "file_control_sequence", "file_control_entry", "@14", 
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
  "multiple_file_position", "data_division", "file_section", "@15", "@16", 
  "file_description_sequence", "file_description", 
  "file_description_sequence_without_type", "file_type", 
  "file_description_entry", "@17", "file_description_clause_sequence", 
  "file_description_clause", "block_contains_clause", 
  "_records_or_characters", "record_clause", "record_depending", 
  "opt_from_integer", "opt_to_integer", "label_records_clause", 
  "label_option", "value_of_clause", "valueof_name", 
  "data_records_clause", "linage_clause", "linage_sequence", 
  "linage_lines", "linage_footing", "linage_top", "linage_bottom", 
  "recording_mode_clause", "code_set_clause", "report_clause", 
  "working_storage_section", "@18", "record_description_list", 
  "record_description_list_1", "@19", "record_description_list_2", 
  "data_description", "@20", "level_number", "entry_name", "const_name", 
  "const_global", "lit_or_length", "constant_entry", 
  "data_description_clause_sequence", "data_description_clause", 
  "redefines_clause", "external_clause", "as_extname", "global_clause", 
  "picture_clause", "usage_clause", "usage", "sign_clause", 
  "occurs_clause", "occurs_to_integer", "occurs_depending", "occurs_keys", 
  "occurs_key_list", "ascending_or_descending", "occurs_indexed", 
  "occurs_index_list", "occurs_index", "justified_clause", 
  "synchronized_clause", "left_or_right", "blank_clause", "based_clause", 
  "value_clause", "@21", "value_item_list", "value_item", "false_is", 
  "renames_clause", "any_length_clause", "local_storage_section", "@22", 
  "linkage_section", "@23", "report_section", "@24", 
  "opt_report_description_list", "report_description_list", 
  "report_description_entry", "report_description_options", 
  "report_description_option", "control_clause", "control_field_list", 
  "_final", "identifier_list", "page_limit_clause", "heading_clause", 
  "first_detail", "last_heading", "last_detail", "footing_clause", 
  "page_line_column", "line_or_lines", "report_group_description_list", 
  "report_group_description_entry", "report_group_options", 
  "report_group_option", "type_clause", "type_option", 
  "next_group_clause", "column_clause", "sum_clause_list", "sum_clause", 
  "ref_id_exp", "present_when_condition", "varying_clause", "line_clause", 
  "line_keyword_clause", "report_line_integer_list", "line_or_plus", 
  "_numbers", "source_clause", "group_indicate_clause", "_indicate", 
  "report_name", "screen_section", "@25", "@26", 
  "opt_screen_description_list", "screen_description_list", 
  "screen_description", "@27", "screen_options", "screen_option", 
  "screen_line_plus_minus", "screen_col_plus_minus", 
  "screen_occurs_clause", "procedure_division", "@28", "@29", 
  "procedure_using_chaining", "@30", "@31", "procedure_param_list", 
  "procedure_param", "procedure_type", "size_optional", 
  "procedure_optional", "procedure_returning", "procedure_declaratives", 
  "@32", "procedure_list", "procedure", "section_header", 
  "paragraph_header", "invalid_statement", "section_name", "opt_segment", 
  "statement_list", "@33", "@34", "statements", "@35", "statement", 
  "accept_statement", "@36", "accept_body", "opt_at_line_column", 
  "line_number", "column_number", "opt_accp_attr", "accp_attrs", 
  "accp_attr", "end_accept", "add_statement", "@37", "add_body", "add_to", 
  "end_add", "allocate_statement", "@38", "allocate_body", 
  "allocate_returning", "alter_statement", "alter_options", "_proceed_to", 
  "call_statement", "@39", "call_using", "@40", "call_param_list", 
  "call_param", "call_type", "call_returning", "call_on_exception", "@41", 
  "call_not_on_exception", "@42", "end_call", "cancel_statement", "@43", 
  "cancel_list", "close_statement", "@44", "close_list", "close_option", 
  "reel_or_unit", "compute_statement", "@45", "compute_body", 
  "end_compute", "comp_equal", "commit_statement", "continue_statement", 
  "delete_statement", "@46", "end_delete", "display_statement", "@47", 
  "display_body", "display_upon", "with_clause", "disp_attrs", 
  "disp_attr", "end_display", "divide_statement", "@48", "divide_body", 
  "end_divide", "entry_statement", "@49", "evaluate_statement", "@50", 
  "evaluate_subject_list", "evaluate_subject", "evaluate_condition_list", 
  "evaluate_case_list", "evaluate_case", "@51", "evaluate_other", "@52", 
  "evaluate_when_list", "evaluate_object_list", "evaluate_object", 
  "opt_evaluate_thru_expr", "end_evaluate", "exit_statement", "@53", 
  "exit_body", "free_statement", "@54", "generate_statement", "@55", 
  "goto_statement", "@56", "goto_depending", "goback_statement", "@57", 
  "if_statement", "@58", "@59", "if_else_sentence", "@60", "end_if", 
  "initialize_statement", "@61", "initialize_filler", "initialize_value", 
  "initialize_replacing", "initialize_replacing_list", 
  "initialize_replacing_item", "initialize_category", 
  "initialize_default", "initiate_statement", "@62", "inspect_statement", 
  "@63", "send_identifier", "inspect_list", "inspect_item", 
  "inspect_tallying", "@64", "tallying_list", "tallying_item", 
  "inspect_replacing", "replacing_list", "replacing_item", "rep_keyword", 
  "replacing_region", "inspect_converting", "inspect_region", "_initial", 
  "merge_statement", "@65", "move_statement", "@66", "move_body", 
  "multiply_statement", "@67", "multiply_body", "end_multiply", 
  "open_statement", "@68", "open_list", "open_mode", "open_sharing", 
  "open_option", "perform_statement", "@69", "perform_body", "@70", 
  "end_perform", "perform_procedure", "perform_option", "perform_test", 
  "perform_varying_list", "perform_varying", "read_statement", "@71", 
  "read_into", "with_lock", "read_key", "read_handler", "end_read", 
  "release_statement", "@72", "return_statement", "@73", "end_return", 
  "rewrite_statement", "@74", "write_lock", "end_rewrite", 
  "rollback_statement", "search_statement", "@75", "search_body", "@76", 
  "search_varying", "search_at_end", "@77", "search_whens", "search_when", 
  "@78", "end_search", "set_statement", "@79", "set_body", 
  "set_environment", "set_to", "set_up_down", "up_or_down", 
  "set_to_on_off_sequence", "set_to_on_off", "set_to_true_false_sequence", 
  "set_to_true_false", "sort_statement", "@80", "sort_body", "@81", 
  "sort_key_list", "opt_key_list", "sort_duplicates", "sort_collating", 
  "sort_input", "sort_output", "start_statement", "@82", "@83", 
  "start_key", "start_op", "end_start", "stop_statement", "@84", 
  "stop_returning", "string_statement", "@85", "string_item_list", 
  "string_item", "opt_with_pointer", "end_string", "subtract_statement", 
  "@86", "subtract_body", "end_subtract", "suppress_statement", 
  "_printing", "terminate_statement", "@87", "transform_statement", "@88", 
  "unlock_statement", "@89", "opt_record", "unstring_statement", "@90", 
  "unstring_delimited", "unstring_delimited_list", 
  "unstring_delimited_item", "unstring_into", "unstring_into_item", 
  "unstring_into_delimiter", "unstring_into_count", "unstring_tallying", 
  "end_unstring", "use_statement", "use_exception", "use_global", 
  "use_exception_target", "_after", "_standard", "exception_or_error", 
  "exception_or_overflow", "not_exception_or_overflow", "_procedure", 
  "use_debugging", "use_debugging_target", "use_reporting", 
  "write_statement", "@91", "write_from", "write_option", 
  "before_or_after", "write_handler", "end_write", "on_accp_exception", 
  "on_disp_exception", "opt_on_exception", "@92", "opt_not_on_exception", 
  "@93", "on_size_error", "opt_on_size_error", "@94", 
  "opt_not_on_size_error", "@95", "on_overflow", "opt_on_overflow", "@96", 
  "opt_not_on_overflow", "@97", "at_end", "at_end_sentence", "@98", 
  "not_at_end_sentence", "@99", "at_eop", "at_eop_sentence", "@100", 
  "not_at_eop_sentence", "@101", "opt_invalid_key", "invalid_key", 
  "invalid_key_sentence", "@102", "not_invalid_key_sentence", "@103", 
  "_opt_scroll_lines", "condition", "expr", "partial_expr", "@104", 
  "expr_tokens", "expr_token", "eq", "gt", "lt", "ge", "le", "exp_list", 
  "e_sep", "exp", "linage_counter", "arithmetic_x_list", "arithmetic_x", 
  "record_name", "table_name", "file_name_list", "file_name", 
  "mnemonic_name_list", "mnemonic_name", "procedure_name_list", 
  "procedure_name", "label", "integer_label", "reference_list", 
  "reference", "opt_reference", "reference_or_literal", "undefined_word", 
  "target_x_list", "target_x", "x_list", "x", "arith_x", "prog_or_entry", 
  "alnum_or_id", "simple_value", "simple_all_value", "id_or_lit", 
  "id_or_lit_or_func", "num_id_or_lit", "identifier", "identifier_1", 
  "qualified_word", "subref", "refmod", "integer", "literal", 
  "basic_literal", "basic_value", "function", "func_refmod", "func_args", 
  "list_func_args", "trim_args", "numvalc_args", "locale_dt_args", 
  "not_const_word", "flag_all", "flag_duplicates", "flag_initialized", 
  "flag_next", "flag_not", "flag_optional", "flag_rounded", 
  "flag_separate", "in_of", "records", "with_dups", "coll_sequence", 
  "_advancing", "_are", "_area", "_as", "_at", "_binary", "_by", 
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
static const unsigned short yytoknum[] =
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
static const unsigned short yyr1[] =
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
     537,   537,   537,   537,   538,   538,   539,   539,   539,   540,
     540,   540,   541,   541,   541,   542,   543,   543,   543,   544,
     545,   546,   547,   547,   547,   548,   549,   549,   549,   550,
     550,   550,   550,   551,   551,   552,   552,   553,   553,   553,
     553,   554,   555,   556,   557,   557,   557,   558,   559,   560,
     561,   561,   561,   562,   562,   563,   563,   564,   564,   565,
     565,   566,   567,   567,   567,   567,   568,   569,   569,   570,
     571,   571,   572,   572,   573,   574,   573,   575,   573,   576,
     576,   577,   578,   578,   579,   579,   581,   580,   582,   582,
     583,   583,   583,   583,   583,   583,   583,   583,   583,   583,
     583,   584,   585,   585,   585,   586,   586,   586,   587,   587,
     588,   588,   589,   589,   590,   591,   591,   592,   592,   593,
     593,   594,   595,   596,   596,   597,   597,   597,   598,   599,
     600,   601,   602,   603,   603,   604,   605,   604,   606,   606,
     608,   607,   609,   609,   609,   610,   611,   610,   612,   613,
     613,   613,   614,   615,   615,   616,   616,   616,   617,   618,
     618,   619,   619,   619,   619,   619,   619,   619,   619,   619,
     619,   619,   619,   619,   619,   620,   621,   622,   622,   623,
     624,   625,   625,   626,   626,   626,   626,   626,   626,   626,
     626,   626,   626,   626,   626,   626,   626,   626,   626,   626,
     626,   626,   626,   626,   626,   626,   626,   626,   626,   626,
     626,   626,   626,   626,   626,   626,   626,   626,   627,   627,
     628,   629,   629,   630,   630,   631,   632,   632,   633,   633,
     634,   634,   635,   635,   636,   637,   638,   639,   639,   639,
     640,   641,   643,   642,   644,   644,   645,   645,   646,   646,
     647,   647,   648,   649,   650,   649,   651,   652,   651,   653,
     654,   653,   655,   655,   656,   656,   657,   658,   658,   659,
     659,   659,   659,   660,   660,   661,   662,   662,   663,   663,
     664,   665,   665,   666,   666,   667,   667,   668,   668,   669,
     669,   670,   670,   670,   671,   671,   672,   672,   673,   674,
     674,   675,   675,   675,   675,   675,   675,   675,   675,   675,
     675,   675,   675,   675,   675,   675,   675,   676,   677,   677,
     677,   677,   677,   677,   677,   678,   679,   679,   679,   680,
     680,   681,   682,   683,   684,   685,   686,   686,   687,   687,
     688,   688,   688,   689,   689,   689,   690,   691,   692,   692,
     693,   694,   695,   696,   694,   697,   697,   698,   698,   699,
     700,   699,   701,   701,   702,   702,   702,   702,   702,   702,
     702,   702,   702,   702,   702,   702,   702,   702,   702,   702,
     702,   702,   702,   702,   702,   702,   702,   702,   702,   702,
     702,   702,   702,   702,   703,   703,   703,   703,   703,   704,
     704,   704,   704,   704,   705,   706,   707,   708,   706,   709,
     710,   709,   711,   709,   712,   712,   713,   714,   714,   714,
     715,   715,   715,   715,   715,   716,   716,   717,   717,   718,
     719,   718,   720,   720,   721,   721,   721,   721,   721,   721,
     722,   723,   724,   725,   726,   726,   728,   729,   727,   731,
     730,   730,   732,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   732,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   732,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   732,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   732,   732,   732,   732,   732,   732,   732,   732,
     732,   734,   733,   735,   735,   735,   735,   735,   735,   735,
     735,   735,   735,   735,   735,   735,   735,   735,   735,   735,
     736,   736,   736,   736,   736,   736,   737,   738,   738,   739,
     739,   740,   740,   741,   741,   741,   741,   741,   741,   741,
     741,   741,   741,   741,   741,   741,   741,   741,   741,   741,
     742,   742,   744,   743,   745,   745,   745,   746,   746,   747,
     747,   749,   748,   750,   750,   751,   751,   752,   753,   753,
     754,   754,   756,   755,   757,   758,   757,   759,   759,   760,
     760,   761,   761,   761,   761,   762,   762,   762,   763,   764,
     763,   765,   766,   765,   767,   767,   769,   768,   770,   770,
     772,   771,   773,   773,   774,   774,   774,   774,   774,   775,
     775,   777,   776,   778,   779,   779,   780,   780,   781,   782,
     784,   783,   785,   785,   787,   786,   788,   788,   788,   788,
     788,   789,   789,   789,   789,   789,   790,   790,   790,   791,
     791,   792,   792,   792,   792,   792,   792,   792,   792,   792,
     792,   792,   792,   792,   792,   792,   793,   793,   795,   794,
     796,   796,   796,   796,   796,   797,   797,   799,   798,   801,
     800,   802,   802,   803,   803,   803,   804,   805,   805,   807,
     806,   808,   809,   808,   810,   810,   811,   811,   812,   812,
     812,   812,   813,   813,   814,   814,   816,   815,   817,   817,
     817,   817,   817,   817,   819,   818,   821,   820,   823,   822,
     824,   824,   826,   825,   828,   829,   827,   827,   830,   831,
     830,   832,   832,   834,   833,   835,   835,   836,   836,   836,
     837,   837,   838,   838,   839,   840,   840,   840,   840,   840,
     840,   840,   841,   841,   843,   842,   845,   844,   846,   846,
     846,   847,   847,   848,   848,   848,   850,   849,   851,   851,
     852,   852,   852,   852,   852,   852,   853,   854,   854,   855,
     855,   856,   856,   856,   856,   856,   857,   858,   859,   859,
     860,   860,   862,   861,   864,   863,   865,   865,   867,   866,
     868,   868,   869,   869,   871,   870,   872,   872,   873,   873,
     873,   873,   874,   874,   875,   875,   875,   877,   876,   878,
     879,   878,   878,   880,   880,   881,   881,   882,   882,   882,
     882,   882,   883,   883,   884,   884,   885,   887,   886,   888,
     888,   889,   889,   889,   889,   889,   889,   890,   890,   891,
     891,   891,   892,   892,   894,   893,   896,   895,   897,   897,
     899,   898,   900,   900,   900,   901,   901,   902,   904,   903,
     905,   906,   905,   907,   907,   908,   909,   908,   910,   910,
     912,   911,   913,   913,   915,   914,   916,   916,   916,   916,
     916,   917,   918,   918,   919,   920,   920,   921,   921,   922,
     923,   923,   924,   924,   926,   925,   928,   927,   929,   929,
     930,   930,   931,   931,   932,   932,   933,   933,   933,   934,
     934,   934,   936,   937,   935,   938,   938,   939,   939,   939,
     939,   939,   940,   940,   942,   941,   941,   943,   943,   943,
     945,   944,   946,   946,   947,   947,   947,   948,   948,   949,
     949,   951,   950,   952,   952,   952,   953,   953,   954,   955,
     955,   957,   956,   959,   958,   961,   960,   962,   962,   962,
     964,   963,   965,   965,   966,   966,   967,   968,   968,   969,
     970,   970,   971,   971,   972,   972,   973,   973,   974,   974,
     974,   975,   976,   976,   977,   977,   977,   977,   977,   978,
     978,   979,   979,   980,   980,   981,   981,   982,   982,   983,
     983,   984,   985,   985,   986,   988,   987,   989,   989,   990,
     990,   990,   990,   991,   991,   992,   992,   992,   993,   993,
     994,   995,   996,   997,   996,   998,   999,   998,  1000,  1001,
    1002,  1001,  1003,  1004,  1003,  1005,  1006,  1007,  1006,  1008,
    1009,  1008,  1010,  1010,  1010,  1012,  1011,  1014,  1013,  1015,
    1015,  1015,  1017,  1016,  1019,  1018,  1020,  1020,  1021,  1021,
    1021,  1023,  1022,  1025,  1024,  1026,  1026,  1027,  1028,  1030,
    1029,  1031,  1031,  1031,  1032,  1032,  1032,  1032,  1032,  1032,
    1032,  1032,  1032,  1032,  1032,  1032,  1032,  1032,  1032,  1032,
    1032,  1032,  1032,  1032,  1032,  1032,  1032,  1032,  1033,  1033,
    1033,  1034,  1034,  1035,  1035,  1036,  1036,  1037,  1037,  1038,
    1038,  1039,  1039,  1039,  1040,  1040,  1040,  1040,  1040,  1040,
    1040,  1040,  1040,  1041,  1041,  1042,  1042,  1043,  1044,  1045,
    1046,  1046,  1047,  1048,  1048,  1049,  1050,  1050,  1051,  1052,
    1052,  1052,  1053,  1054,  1054,  1055,  1056,  1056,  1057,  1057,
    1058,  1059,  1059,  1060,  1060,  1061,  1061,  1062,  1062,  1062,
    1062,  1062,  1062,  1062,  1062,  1062,  1063,  1063,  1063,  1063,
    1063,  1063,  1063,  1064,  1064,  1065,  1065,  1066,  1066,  1067,
    1067,  1068,  1068,  1069,  1069,  1069,  1070,  1070,  1070,  1071,
    1072,  1072,  1072,  1072,  1073,  1073,  1074,  1075,  1075,  1076,
    1077,  1077,  1078,  1078,  1079,  1079,  1079,  1079,  1079,  1079,
    1079,  1080,  1080,  1080,  1080,  1080,  1080,  1080,  1080,  1080,
    1080,  1080,  1080,  1081,  1081,  1081,  1082,  1082,  1083,  1083,
    1084,  1084,  1084,  1085,  1085,  1086,  1086,  1087,  1088,  1088,
    1089,  1089,  1090,  1090,  1091,  1091,  1091,  1092,  1092,  1093,
    1093,  1094,  1094,  1095,  1095,  1096,  1096,  1097,  1097,  1098,
    1098,  1099,  1099,  1100,  1100,  1101,  1101,  1102,  1102,  1103,
    1103,  1104,  1104,  1105,  1105,  1106,  1106,  1107,  1107,  1108,
    1108,  1109,  1109,  1110,  1110,  1111,  1111,  1112,  1112,  1113,
    1113,  1114,  1114,  1115,  1115,  1116,  1116,  1116,  1117,  1117,
    1118,  1118,  1118,  1119,  1119,  1120,  1120,  1121,  1121,  1122,
    1122,  1123,  1123,  1124,  1124,  1124,  1125,  1125,  1126,  1126,
    1127,  1127,  1128,  1128,  1129,  1129,  1130,  1130,  1131,  1131,
    1131,  1132,  1132,  1133,  1133,  1134,  1134,  1135,  1135,  1136,
    1136,  1137,  1137,  1138,  1138,  1139,  1139,  1140,  1140
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
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
       1,     1,     1,     1,     5,     4,     0,     1,     1,     0,
       1,     1,     1,     1,     1,     4,     1,     1,     1,     6,
       3,     5,     0,     1,     1,     4,     2,     2,     1,     0,
       4,     5,     2,     1,     1,     3,     1,     1,     3,     1,
       2,     4,     4,     4,     1,     3,     4,     4,     3,     3,
       2,     2,     2,     0,     3,     0,     2,     1,     2,     1,
       1,     5,     0,     1,     1,     1,     5,     1,     2,     2,
       0,     2,     0,     9,     0,     0,     5,     0,     3,     0,
       2,     3,     2,     2,     1,     1,     0,     4,     0,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     0,     1,     1,     4,     6,     9,     0,     3,
       0,     2,     0,     2,     3,     1,     1,     5,     5,     1,
       1,     3,     5,     0,     2,     1,     1,     1,     5,     4,
       3,     4,     3,     3,     3,     0,     0,     5,     0,     1,
       0,     2,     3,     4,     2,     1,     0,     4,     1,     0,
       1,     1,     1,     0,     2,     1,     3,     3,     6,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     0,     2,     2,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     2,     2,     1,     2,     2,
       1,     2,     2,     1,     2,     2,     1,     1,     3,     3,
       7,     0,     2,     0,     3,     1,     0,     5,     1,     1,
       0,     3,     1,     2,     1,     2,     2,     0,     1,     1,
       3,     1,     0,     8,     1,     2,     1,     3,     0,     3,
       2,     4,     2,     0,     0,     5,     0,     0,     5,     0,
       0,     5,     0,     1,     1,     2,     5,     0,     2,     2,
       3,     1,     1,     2,     2,     2,     0,     1,     1,     2,
       8,     0,     3,     0,     4,     0,     4,     0,     3,     0,
       3,     1,     4,     2,     1,     1,     0,     2,     4,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     4,     4,     2,     1,     1,
       2,     3,     1,     3,     6,     2,     3,     2,     1,     2,
       2,     1,     2,     0,     1,     1,     4,     2,     0,     1,
       1,     0,     0,     0,     6,     0,     1,     1,     2,     1,
       0,     5,     0,     2,     1,     1,     1,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     5,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     0,     1,     1,     1,     1,     0,
       1,     1,     1,     1,     3,     0,     0,     0,     9,     0,
       0,     3,     0,     3,     1,     2,     4,     0,     2,     2,
       0,     3,     3,     4,     3,     0,     1,     0,     2,     0,
       0,     7,     0,     2,     1,     1,     1,     2,     2,     1,
       4,     2,     1,     1,     0,     1,     0,     0,     3,     0,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     4,     4,     3,     3,     3,     4,     3,
       4,     3,     3,     3,     4,     5,     3,     4,     3,     3,
       0,     3,     3,     2,     2,     2,     3,     3,     3,     0,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       0,     1,     0,     4,     4,     5,     6,     0,     2,     0,
       1,     0,     3,     3,     5,     0,     2,     2,     0,     5,
       0,     2,     0,     8,     0,     0,     3,     1,     2,     2,
       3,     0,     2,     2,     2,     0,     2,     2,     0,     0,
       3,     0,     0,     3,     0,     1,     0,     3,     0,     2,
       0,     3,     0,     3,     0,     1,     3,     3,     2,     1,
       1,     0,     4,     4,     0,     1,     1,     1,     1,     1,
       0,     6,     0,     1,     0,     4,     3,     3,     3,     3,
       5,     0,     2,     2,     2,     2,     0,     2,     2,     1,
       2,     1,     1,     2,     2,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     1,     1,     0,     1,     0,     4,
       4,     6,     6,     8,     8,     0,     1,     0,     4,     0,
       5,     1,     3,     1,     1,     1,     2,     1,     2,     0,
       3,     0,     0,     4,     2,     3,     1,     3,     2,     1,
       1,     1,     0,     2,     0,     1,     0,     3,     0,     1,
       1,     2,     1,     1,     0,     3,     0,     3,     0,     5,
       0,     3,     0,     2,     0,     0,     8,     3,     0,     0,
       3,     0,     1,     0,     7,     0,     2,     0,     3,     3,
       0,     2,     1,     2,     4,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     0,     3,     0,     4,     1,     1,
       1,     1,     2,     1,     1,     1,     0,     3,     1,     2,
       2,     2,     1,     1,     1,     2,     2,     1,     2,     4,
       2,     0,     1,     1,     1,     1,     4,     5,     0,     4,
       0,     1,     0,     3,     0,     3,     3,     4,     0,     4,
       4,     6,     0,     1,     0,     3,     0,     5,     1,     1,
       1,     1,     0,     3,     0,     3,     2,     0,     3,     2,
       0,     4,     2,     0,     1,     1,     3,     0,     1,     2,
       3,     3,     0,     3,     1,     3,     7,     0,    10,     0,
       2,     0,     2,     2,     3,     3,     2,     0,     3,     0,
       1,     1,     0,     1,     0,     4,     0,     7,     0,     1,
       0,     7,     0,     2,     3,     0,     1,     1,     0,     4,
       4,     0,     7,     0,     2,     0,     0,     4,     1,     2,
       0,     4,     0,     1,     0,     3,     1,     1,     1,     1,
       1,     4,     4,     3,     4,     1,     1,     1,     2,     3,
       1,     2,     3,     3,     0,     3,     0,     7,     0,     5,
       0,     2,     0,     2,     0,     3,     0,     2,     4,     0,
       2,     4,     0,     0,     7,     0,     4,     2,     2,     2,
       2,     2,     0,     1,     0,     4,     2,     0,     2,     2,
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
       2,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
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
       1,     0,     1,     0,     1,     0,     1,     1,     0,     1,
       0,     1,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     2,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       2,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned short yydefact[] =
{
       2,     0,     0,     1,     0,     0,     3,     4,     6,     7,
      38,    38,     0,     0,     5,     0,     8,    14,    28,    27,
      29,    29,     0,   242,   242,     0,     0,    24,    40,     0,
       9,    15,    30,    26,  1463,     0,   147,     0,   575,   575,
    1464,     0,     0,     0,     0,     0,     0,    39,   244,     0,
      17,     0,    25,    33,    37,    36,  1488,    35,    42,   149,
       0,   151,   254,   255,     0,   305,   247,   579,    18,    20,
      38,     0,    16,    34,  1489,    32,    41,   155,   153,   225,
       0,     0,   423,     0,   582,   580,   597,     0,    19,    10,
      11,     0,     0,     0,     0,     0,    43,    44,    45,    47,
      46,   150,     0,   223,  1455,   232,   152,     0,   227,   229,
     230,   245,     0,     0,   426,  1302,   248,   308,   256,   587,
     587,     0,     0,     0,   242,    23,    56,    71,    49,    80,
    1419,   156,   155,     0,   148,  1456,  1505,   233,   234,   235,
    1437,   226,   228,   249,   306,     0,     0,   429,   253,     0,
     252,   309,  1407,   258,  1446,   587,   584,   590,     0,   587,
     598,   576,    21,    12,     0,  1463,    54,  1488,    55,  1488,
      60,    62,    63,    64,     0,     0,    70,     0,    73,  1518,
      48,     0,  1517,     0,     0,     0,     0,  1496,  1463,  1463,
    1463,     0,  1463,  1449,  1463,    79,     0,    82,    84,    85,
      86,    88,    87,    89,    90,    91,    92,    93,    94,  1420,
       0,   154,   225,  1506,  1451,  1438,  1457,   246,   308,   424,
       0,     0,   521,   308,   311,     0,  1463,   585,  1463,     0,
     595,   588,   589,   599,   575,  1463,     0,    57,  1488,    59,
      61,     0,  1432,  1463,     0,    77,     0,    72,    74,    52,
      50,     0,     0,  1320,   102,  1463,  1463,  1497,  1463,     0,
       0,     0,  1463,     0,  1450,     0,     0,    81,    83,   157,
     224,  1452,     0,  1458,     0,   250,   307,   308,   427,     0,
       0,   243,   251,   314,     0,   318,     0,   319,   315,  1451,
    1463,     0,     0,  1463,  1451,  1475,  1463,  1435,     0,   257,
     259,   262,   263,   264,   265,   266,   267,   268,   269,   270,
       0,     0,  1463,   596,     0,     0,   577,    17,     0,  1369,
      69,    58,  1431,     0,    76,    75,    78,    51,    53,  1463,
       0,     0,     0,  1364,   143,  1315,   142,   146,     0,   145,
     129,  1465,   131,    95,    96,   159,   236,   237,   240,   231,
    1300,   425,   308,   430,     0,     0,   312,   320,   321,   316,
       0,     0,     0,  1463,  1435,     0,     0,     0,     0,     0,
    1476,  1463,     0,  1436,     0,     0,   260,   261,   591,   592,
     594,     0,   586,   600,   602,     0,     0,    68,     0,  1378,
    1374,  1379,  1377,  1375,  1380,  1376,   135,   136,   138,   144,
     141,  1425,  1426,     0,   140,  1467,  1466,   132,     0,    98,
    1490,   238,     0,   239,  1301,   428,   432,   522,   313,   329,
     323,   282,   302,  1427,  1428,   291,  1313,   286,   285,   284,
    1319,  1318,  1473,  1449,  1461,     0,   520,   303,   304,  1463,
    1463,   593,   602,     0,     0,    13,    66,    67,    65,   107,
     121,   117,   122,   104,   120,   118,   105,   106,   119,   103,
     108,   109,   111,   137,     0,  1365,   130,   133,    97,  1475,
       0,  1513,   207,     0,  1475,  1463,  1447,  1468,   209,     0,
    1517,   194,   193,   158,   160,   161,   162,   163,   164,   165,
       0,   166,   167,   206,   168,   169,   170,   171,   172,   173,
    1463,  1443,   241,     0,   431,   433,   434,   523,  1463,  1439,
       0,     0,   272,  1314,  1474,   293,     0,   275,  1462,  1501,
     301,     0,     0,     0,     0,   613,   609,   603,   604,   605,
     606,   612,     0,     0,     0,   110,   113,     0,   139,   134,
     101,   100,  1503,  1463,  1468,  1514,   179,   210,  1463,  1490,
    1448,  1463,  1463,  1469,  1463,  1463,  1437,     0,  1463,     0,
    1444,     0,   437,   435,   525,     0,   411,   353,   386,   374,
     383,   380,   377,  1515,   354,   355,   356,   357,   358,   359,
     360,   361,   362,  1492,   387,     0,   363,   350,   364,   365,
       0,     0,  1499,   367,   368,   366,   407,   370,   371,   369,
    1463,  1465,   330,   331,   332,   333,   334,   335,   351,   336,
     337,   338,   339,   340,   341,   342,   343,   344,     0,     0,
    1440,     0,   324,   283,   274,   273,   271,   292,  1449,  1502,
     280,   289,   288,   290,   287,     0,   608,   611,   614,   671,
     722,   731,   738,   742,   766,   770,   788,   781,   789,   790,
     794,   828,   837,   839,   866,   874,   876,  1513,   882,     0,
     893,   914,   916,   952,   954,   958,   670,   964,   977,   997,
    1014,  1016,  1020,  1027,  1028,  1044,  1064,  1082,     0,  1100,
    1111,  1119,  1121,  1123,  1125,  1130,  1152,  1175,   607,   621,
     622,   623,   624,   625,   626,   627,   628,   630,   629,   631,
     632,   633,   634,   635,   636,   637,   638,   639,   640,   641,
     642,   643,   644,   645,   646,   647,   648,   649,   650,   651,
     652,   653,   654,   655,   656,   657,   658,   659,   660,   661,
     662,   663,   664,   665,   666,   667,   668,  1148,  1149,  1150,
     669,   620,    22,     0,   112,  1504,  1463,     0,  1463,   181,
     180,   176,     0,  1491,   209,   205,     0,     0,     0,     0,
     218,  1486,  1486,     0,   219,     0,   190,   208,  1463,   319,
     529,   524,   526,   527,   422,   384,   385,   372,   373,   381,
     382,   378,   379,   375,   376,  1516,     0,  1493,   405,   391,
     345,  1360,   420,  1500,   408,   409,   406,     0,     0,   347,
     349,  1423,  1423,     0,  1479,  1479,   328,   325,  1370,  1372,
    1442,   294,   295,   296,   297,     0,     0,   276,  1460,   282,
       0,     0,   615,     0,     0,     0,  1239,   737,     0,   768,
     772,     0,     0,     0,     0,     0,  1239,   868,     0,     0,
     878,   883,     0,  1239,     0,     0,     0,     0,     0,     0,
     966,   987,     0,     0,     0,     0,     0,     0,     0,     0,
    1096,  1094,     0,     0,  1120,  1118,     0,     0,     0,     0,
    1153,  1159,     0,     0,   127,   123,   128,   126,   124,   125,
     114,   115,     0,   187,   188,   186,   185,     0,   175,   178,
       0,   199,   198,   199,   195,   211,   212,   213,   214,   217,
    1487,   220,   221,   222,  1316,  1463,   446,   446,  1465,   466,
     438,   441,   442,     0,   530,   528,   410,     0,  1511,     0,
    1361,  1362,     0,   352,   412,   414,   416,     0,   346,  1447,
     388,   389,  1371,  1480,     0,     0,     0,     0,     0,  1441,
    1449,   281,   601,   610,   720,   690,  1359,  1479,     0,     0,
    1393,  1396,  1479,  1293,     0,     0,     0,     0,     0,     0,
       0,     0,  1393,   729,  1335,   727,  1325,  1327,  1333,  1334,
    1412,   732,     0,  1238,     0,  1312,     0,  1308,  1310,  1309,
    1354,   744,  1353,  1355,   767,   771,   784,     0,  1295,  1421,
    1490,  1374,   826,   690,     0,  1327,   835,     0,   744,   845,
     844,     0,   841,   843,   873,   870,   869,   872,   867,  1479,
     875,  1321,  1323,   877,  1306,   887,  1509,  1237,   895,   915,
     448,     0,   918,   919,   920,   953,  1068,     0,   955,     0,
     962,     0,   965,   988,  1312,   978,   987,   980,     0,   985,
       0,  1309,     0,  1414,  1177,  1298,  1490,  1177,     0,  1042,
    1033,  1299,     0,  1305,  1045,  1046,  1047,  1048,  1049,  1057,
    1050,  1060,     0,  1303,     0,  1065,  1083,  1097,  1445,     0,
    1102,  1104,     0,  1116,     0,  1122,     0,  1127,  1132,  1160,
       0,  1161,  1481,  1177,     0,    99,  1410,   183,   182,   174,
     184,     0,   197,   196,  1463,     0,  1317,   191,     0,   447,
     443,     0,   444,     0,   436,   439,   532,   392,  1512,   393,
    1479,     0,     0,     0,  1281,  1279,  1342,  1284,  1336,  1340,
    1341,     0,  1363,   421,  1515,   415,     0,   348,  1424,   327,
     326,  1373,   300,  1473,     0,   278,   721,   672,  1442,     0,
     699,     0,     0,     0,     0,     0,  1381,  1398,  1392,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1382,
     730,   723,     0,     0,  1326,  1413,   735,  1412,  1263,  1264,
    1265,  1259,  1513,  1270,  1255,  1507,  1256,  1507,  1257,  1267,
    1258,  1262,  1261,  1260,  1266,  1247,  1248,  1249,  1250,  1251,
    1268,  1245,  1246,  1271,  1273,  1240,  1241,  1252,  1253,  1254,
    1244,   740,     0,   745,   755,  1352,   769,  1351,   774,   785,
     782,   787,   786,  1239,  1296,  1422,  1297,  1226,   827,   795,
     801,  1192,  1192,  1192,  1192,   836,   829,     0,     0,   838,
    1239,  1239,   864,   851,   847,   849,   871,     0,  1322,   880,
    1510,   885,   897,     0,   449,     0,   941,   926,   917,   921,
     923,   924,   925,  1072,     0,     0,   963,   959,     0,   971,
     968,   970,   969,   972,   979,   982,   616,  1239,     0,     0,
     989,     0,  1415,  1416,  1490,     0,  1015,   999,  1022,  1035,
    1043,  1029,     0,  1035,     0,  1347,  1348,  1058,  1061,     0,
       0,  1304,  1056,     0,  1055,     0,  1085,     0,     0,  1095,
       0,     0,  1103,     0,  1117,  1112,     0,     0,  1128,  1129,
    1126,  1445,     0,     0,  1162,     0,  1482,     0,  1022,   116,
    1430,     0,   189,  1411,     0,   202,     0,   215,   440,   445,
     451,   461,   319,   467,  1498,  1481,   396,     0,  1289,  1290,
       0,  1282,  1283,  1366,     0,     0,     0,     0,     0,     0,
       0,     0,  1494,   417,   299,  1473,  1481,   277,   695,   686,
    1192,   676,   683,   677,   679,   681,     0,  1192,     0,   675,
     682,   689,   688,     0,  1192,  1477,  1477,  1477,   693,   694,
    1344,  1343,     0,  1332,  1281,  1279,     0,     0,  1281,     0,
    1328,  1329,  1330,  1294,  1281,     0,     0,  1281,     0,     0,
    1281,  1281,  1281,     0,     0,  1199,  1421,     0,     0,   733,
       0,  1269,  1508,  1272,  1274,  1242,  1243,     0,     0,  1311,
     751,     0,     0,   758,   779,   780,   773,   775,     0,  1199,
    1231,  1233,   792,  1227,  1228,  1229,     0,   806,  1193,   798,
    1195,   799,   796,   797,     0,  1199,  1421,   842,   859,   861,
     860,   854,   856,   862,   865,   840,  1239,   848,   846,  1239,
     616,  1324,  1481,   879,  1307,   616,  1513,   905,   906,   908,
     910,   911,   907,   909,   900,  1513,   896,     0,   942,     0,
     944,   943,   945,   936,   937,     0,     0,   922,  1074,  1483,
       0,     0,   956,  1199,  1421,  1517,     0,   983,   617,   990,
     991,   994,     0,   986,  1184,  1183,   993,   999,  1178,     0,
       0,  1226,     0,     0,     0,  1034,     0,     0,     0,  1059,
       0,  1063,  1062,  1053,     0,  1463,  1226,  1099,  1098,  1105,
    1106,  1107,     0,  1199,  1421,     0,  1408,     0,  1107,  1174,
    1164,  1163,  1169,     0,  1171,  1172,  1179,  1429,     0,   216,
    1463,   453,   464,   465,   463,   321,   469,   545,  1463,   536,
     534,   535,   537,  1477,     0,  1463,     0,   548,   540,  1477,
     541,     0,   544,   549,   547,   542,   546,     0,   543,     0,
     531,   559,   554,   557,   556,   555,   558,   533,   560,     0,
     400,   395,  1337,  1338,  1339,  1292,  1280,  1285,  1286,  1287,
    1288,  1291,  1367,     0,  1495,  1513,   298,     0,   687,  1195,
     678,   680,  1192,   684,   674,   714,  1463,   703,   704,  1463,
     715,   705,   706,   709,   719,   716,   707,     0,   717,   708,
     718,   700,   701,   673,  1478,     0,     0,     0,   691,   692,
    1346,  1331,  1345,  1393,  1421,     0,  1397,     0,  1393,  1393,
       0,  1390,  1393,  1393,  1393,     0,  1393,  1393,  1200,   724,
    1202,  1199,   736,     0,   741,   739,   746,   747,   590,     0,
     757,   756,  1165,  1166,   761,   759,     0,   778,     0,   783,
     616,   616,   793,   791,  1230,   805,   804,   803,   802,  1518,
    1192,     0,   616,  1196,  1191,     0,   830,     0,  1239,  1239,
     858,   852,   855,   850,     0,   888,     0,     0,   912,     0,
       0,     0,   938,   940,     0,   932,   948,   933,   934,   927,
     928,   948,  1066,  1463,     0,  1484,  1073,   398,   399,  1468,
     957,   960,     0,     0,   974,   984,   981,   619,     0,     0,
    1001,  1000,  1215,  1217,  1018,  1212,  1213,  1025,  1023,     0,
    1239,  1036,  1239,  1030,  1038,  1051,  1052,  1054,  1417,  1092,
    1206,     0,  1421,  1113,     0,     0,  1409,  1133,  1134,     0,
    1137,  1140,  1144,  1138,  1170,  1481,  1173,  1185,  1433,     0,
     203,   204,   200,     0,     0,   455,     0,  1498,     0,  1463,
     538,   539,     0,   562,  1463,  1511,   563,   561,   394,  1445,
     390,  1468,  1368,   418,   279,  1190,   685,     0,     0,  1235,
    1235,   702,   697,   696,   698,  1386,  1199,  1394,     0,  1406,
    1391,  1384,  1404,  1385,  1387,  1388,  1401,  1402,  1389,  1383,
     616,  1203,  1198,   725,   734,   748,   749,     0,   753,   752,
     754,  1167,  1168,   764,   762,   616,   776,   777,  1232,  1234,
    1463,   811,   824,   825,   812,     0,  1463,   815,   816,   819,
     817,     0,   818,   808,   809,   800,   807,  1194,   616,  1199,
    1295,  1199,  1295,   857,   863,   616,   881,   889,   891,   898,
     901,   902,  1453,   913,   894,   899,   948,  1349,  1350,   948,
       0,   931,   929,   930,   935,  1076,     0,  1485,  1070,  1199,
     973,   967,     0,   618,   995,     0,     0,  1007,     0,   616,
     616,  1019,  1017,  1214,  1026,  1021,  1024,  1031,   616,  1040,
    1039,  1418,     0,     0,  1093,  1084,  1207,  1109,  1209,     0,
    1199,  1199,  1124,  1408,  1136,  1461,  1142,  1461,  1206,     0,
    1222,  1224,  1188,  1186,  1219,  1220,  1187,  1434,     0,   201,
     452,  1463,     0,   457,   462,  1477,   498,   518,   513,  1435,
       0,     0,  1463,  1479,  1463,     0,   468,   474,   475,   476,
     485,   477,   479,   482,   470,   471,   472,   478,   481,   499,
     483,   486,   473,     0,   480,   484,  1358,   553,  1356,  1357,
     569,   552,   564,   574,     0,  1463,  1463,   413,   711,   710,
     713,     0,   712,   726,  1395,  1201,   616,   750,   765,   743,
     616,   760,     0,   813,   814,     0,  1235,  1235,   810,  1197,
     832,     0,   831,     0,   853,   616,   892,   886,   903,  1454,
       0,   947,   939,   948,   950,     0,     0,  1079,  1075,  1069,
     961,   976,     0,     0,  1002,  1463,  1009,     0,  1003,     0,
    1006,  1216,  1218,   616,  1037,   616,  1086,  1275,  1507,  1277,
    1507,  1087,  1088,  1089,  1090,  1091,   616,  1110,  1101,  1210,
    1205,  1108,  1115,  1114,  1135,     0,  1461,  1139,     0,  1146,
    1158,  1155,  1157,  1156,  1151,  1154,   616,   616,  1189,  1176,
    1221,  1182,  1181,  1470,     0,  1463,  1463,   459,   497,  1463,
     519,   517,   514,   515,  1465,   507,  1463,  1239,     0,     0,
       0,     0,   500,     0,     0,   505,   508,   511,   572,   570,
     571,   573,     0,   567,   565,   566,   568,     0,   404,   401,
     402,     0,     0,  1470,  1204,   763,   821,   820,   823,   822,
    1199,  1199,   890,     0,   946,   951,     0,  1463,  1077,     0,
       0,  1067,  1071,   975,     0,     0,  1012,  1010,  1011,  1005,
    1004,  1032,  1041,  1272,  1274,  1208,   616,  1141,     0,  1145,
    1147,  1131,  1223,  1225,  1471,  1472,  1180,   454,     0,     0,
    1463,   450,     0,   506,     0,   503,  1421,   501,   502,   492,
     490,   491,   493,   489,   494,   488,   487,     0,   512,   510,
     509,   551,   550,   403,   397,   419,  1236,   834,   833,   904,
     949,     0,  1080,  1463,  1239,  1008,  1013,   998,     0,     0,
    1211,  1143,   456,   458,     0,   496,   495,   516,     0,  1078,
       0,   996,  1513,  1513,   460,     0,  1081,  1276,  1278,   504
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
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
#define YYPACT_NINF -1922
static const short yypact[] =
{
   -1922,   285,   446, -1922,   196,   229,   446, -1922, -1922, -1922,
     559,   559,   397,   397, -1922,   577, -1922, -1922, -1922, -1922,
     687,   687,   281,   836,   836,   560,   518, -1922,   921,   928,
   -1922, -1922, -1922, -1922,   -54,   686,   882,   605,   768,   768,
   -1922,   641,    53,   671,   678,   778,   692, -1922,    13,  1016,
     845,  1025, -1922,   -28, -1922, -1922,   861, -1922, -1922, -1922,
     724, -1922, -1922, -1922,   839,   769, -1922,    43, -1922,   473,
     559,   397, -1922, -1922, -1922, -1922,   704, -1922,  1049,   427,
     736,   870,  1004,   821, -1922, -1922,   911,   397, -1922, -1922,
   -1922,   817,   819,   820,   824,   825, -1922, -1922, -1922, -1922,
   -1922,   920,   828,  1065,   880,   -48, -1922,   402, -1922, -1922,
   -1922, -1922,   834,   932,  1055, -1922,   418,   850, -1922,    86,
      86,   853,   842,   847,   836, -1922,   569,  1118,   169,   747,
    1021, -1922, -1922,   852, -1922, -1922,   913, -1922, -1922, -1922,
    1274, -1922, -1922, -1922, -1922,   859,   957,   985, -1922,   821,
   -1922, -1922, -1922, -1922, -1922,   495, -1922,   -34,   -90,   515,
   -1922, -1922, -1922, -1922,   943,  1103, -1922,   468, -1922,   547,
   -1922, -1922, -1922, -1922,    67,   168, -1922,   -38, -1922, -1922,
   -1922,   879,   673,  1212,   891,   891,   951,   976,  1103,  1103,
    1103,   891,  1103,  1284,  1103, -1922,   112, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
     891,   920,   427, -1922,  1261, -1922,  1175,   418,   850, -1922,
     902,  1012,  1009,   850,   650,   935,  1054, -1922,  1103,  1000,
    1095, -1922, -1922,  1268,   768,  1103,  1146, -1922,   634, -1922,
   -1922,  1022, -1922,  1103,  1170, -1922,   775, -1922, -1922, -1922,
   -1922,   936,  1137, -1922, -1922,  1103,  1103, -1922,  1103,   953,
    1315,   953,  1103,   953, -1922,   891,    16, -1922, -1922, -1922,
   -1922, -1922,   821, -1922,   821, -1922, -1922,   850, -1922,   938,
    1039, -1922, -1922, -1922,   935, -1922,   945,   -19, -1922,  1261,
    1103,   -15,   -15,  1103,     8,  1149,  1103,  1368,  1125, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
     499,   200,  1103, -1922,   963,   952, -1922,   845,  1146, -1922,
   -1922, -1922, -1922,   953, -1922, -1922, -1922, -1922, -1922,  1103,
     701,   953,  1176,   456, -1922, -1922, -1922, -1922,   953, -1922,
   -1922,    58, -1922, -1922, -1922, -1922,   821, -1922,  1114,   821,
   -1922, -1922,   850, -1922,   964,   965, -1922, -1922,  1329, -1922,
    1331,  1146,   986,  1103,  1368,   953,    -7,   -37,  1146,   988,
   -1922,  1103,   990, -1922,   990,    -8, -1922, -1922, -1922, -1922,
   -1922,  1146, -1922, -1922, -1922,   510,   126, -1922,  1077, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922,   701, -1922,  1038, -1922,
   -1922, -1922, -1922,   953, -1922, -1922, -1922, -1922,  1146, -1922,
     796, -1922,  1146, -1922, -1922, -1922,  1107, -1922, -1922, -1922,
     765,  1032, -1922, -1922, -1922,   953, -1922, -1922, -1922, -1922,
   -1922, -1922,  1206,    62,  1242,  1003, -1922, -1922, -1922,  1103,
    1103, -1922, -1922,  2643,   397, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
     931, -1922,    68, -1922,   701, -1922,  1146, -1922,   806,  1149,
    1127,  1051, -1922,  1092,  1149,  1103,  1397,   262,     2,  1146,
    1027, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
    1080, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
    1103,  1421, -1922,   990, -1922,  1107, -1922, -1922,  4620,  1440,
    1286,  1146,    85, -1922, -1922, -1922,  1146, -1922, -1922,  1109,
   -1922,   -27,   -27,  2851,  1031,  1033, -1922, -1922, -1922, -1922,
   -1922,  1131,  3560,  3795,  1036, -1922, -1922,   931, -1922, -1922,
   -1922, -1922,  1106,  1103,  1270, -1922,   165, -1922,  1103,   713,
   -1922,  1103,  1103, -1922,  1103,  1103,  1274,   162,  1103,  1053,
   -1922,  1132, -1922, -1922,   935,  1269, -1922, -1922,   282,   522,
     533,   552,   639,  1066, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922,  1159, -1922,  1146, -1922, -1922, -1922, -1922,
     953,   953,  1289, -1922, -1922, -1922,   526, -1922, -1922, -1922,
    1103,   195, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,   918,   442,
   -1922,   376, -1922, -1922, -1922, -1922, -1922,   150,  1284, -1922,
     536, -1922, -1922, -1922, -1922,  1398, -1922, -1922,  1273, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922,  1051, -1922,  2239,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,    14, -1922,
   -1922,  1208, -1922, -1922, -1922, -1922,   154, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922,   981, -1922, -1922,  1103,    74,  1103, -1922,
   -1922,   555,   620, -1922, -1922, -1922,   -37,  1135,   953,   953,
   -1922,  1230,  1230,  1238, -1922,   953, -1922, -1922,    25,   -19,
   -1922, -1922,   935, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922,  1075, -1922, -1922,  1119,
   -1922,  1071,  1128, -1922, -1922, -1922, -1922,  3077,   343,  1491,
   -1922,  1173,  1173,   701,  1259,  1259, -1922, -1922,  1081, -1922,
   -1922, -1922, -1922, -1922, -1922,    57,  1359, -1922, -1922,  1032,
    1146,  1089, -1922,  1091,   953,  3638,  1108,   -26,   982, -1922,
   -1922,  4203,   821,  4332,  4203,  1312,   372,   841,   102,   953,
   -1922, -1922,  1411, -1922,   102,   953,  4216,   953,  3821,  4203,
   -1922,  1594,   821,   953,   821,   953,    41,    66,   953,   821,
   -1922, -1922,  2984,  3875, -1922, -1922,   953,   953,   821,   953,
   -1922,   295,  1443,   953, -1922, -1922, -1922, -1922, -1922, -1922,
    1530, -1922,   891, -1922, -1922, -1922, -1922,   953,   122, -1922,
     159,  1121, -1922,  1121, -1922, -1922, -1922, -1922,   527, -1922,
   -1922, -1922, -1922, -1922,   953,  1103,  1386,  1386,   195, -1922,
   -1922, -1922, -1922,  1374, -1922, -1922, -1922,  1146,  1177,  4973,
    1120, -1922,   953, -1922,   343, -1922,  1178,  1340, -1922,  1397,
   -1922, -1922, -1922, -1922,   953,   953,   701,   -37,   -37,  1542,
    1284, -1922, -1922, -1922,  1453,   717, -1922,  1259,  1130,   953,
    1133,  1140,  1259,   456,  1142,  1143,  1145,  1147,  1154,  1155,
    1162,  1168,  1133,  1455, -1922,  3887, -1922, -1922, -1922, -1922,
    1403, -1922,  1556, -1922,  3328, -1922,  1221, -1922,   456, -1922,
   -1922,  1192, -1922, -1922,   155,   821,  1492,  1241, -1922,  1279,
    1311,  1024,  1495,  2087,  1104,  1165,  1496,   173,  1192, -1922,
   -1922,    37, -1922, -1922, -1922,  1527, -1922, -1922, -1922,  1259,
     102, -1922, -1922, -1922, -1922, -1922,  1235, -1922,    93,   953,
   -1922,   108, -1922, -1922, -1922, -1922, -1922,  4203, -1922,  1233,
    1497,  1581,   810, -1922,  1239, -1922,  1630,  1500,   683,  1243,
    1244,  -103,  1247,   648,  1466, -1922,  1311,  1466,   953,  1504,
    1217, -1922,   876, -1922, -1922, -1922, -1922, -1922,  1405, -1922,
     102, -1922,   408, -1922,    52, -1922, -1922,   494,  1597,  2357,
   -1922, -1922,   953,  1506,  4056,   953,  1474,   869,  1543, -1922,
    1325,  1280,  1382,  1466,   981, -1922,     9, -1922, -1922, -1922,
   -1922,    -5, -1922, -1922,  1103,   953, -1922, -1922,   155, -1922,
   -1922,   953, -1922,  1146,   935, -1922, -1922, -1922, -1922,  1545,
    1259,  4973,  4973,  4973,    17,   878, -1922, -1922, -1922,  1081,
   -1922,  4973, -1922, -1922,  1066, -1922,   343, -1922, -1922, -1922,
   -1922, -1922, -1922,  1206,   -37,  1548, -1922, -1922,   876,   857,
    1228,   135,   -23,  4973,  1265,  4973, -1922,  4973, -1922,  4529,
    1229,  4973,  4973,  4973,  4973,  4973,  4973,  4973,  4973, -1922,
   -1922, -1922,  4203,  1480, -1922, -1922,  1332,  1403, -1922, -1922,
   -1922, -1922,  1051, -1922, -1922,  1276, -1922,  1276, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922,  3091, -1922, -1922, -1922, -1922,
   -1922,  1363,  1438, -1922,   548, -1922, -1922, -1922,   812, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922,    54, -1922, -1922,
    1251,  1510,  1510,  1510,  1510, -1922, -1922,  4203,  4203, -1922,
     372,   219,  1540,  1246, -1922,  1252, -1922,   953, -1922,   111,
   -1922, -1922,  1240,  1505, -1922,   876,    84, -1922,   108, -1922,
   -1922, -1922, -1922,    50,  1281,   102, -1922, -1922,  4203, -1922,
   -1922, -1922, -1922,  1324, -1922, -1922, -1922, -1922,   953,   -26,
   -1922,   999, -1922, -1922,  1311,   155, -1922,  1475,   377,   244,
   -1922, -1922,   953,   244,  1288, -1922,  1081, -1922, -1922,    59,
     806, -1922, -1922,  1910, -1922,  1635,  1477,  4203,  4203, -1922,
    4137,   953, -1922,  1516, -1922, -1922,  4203,   876, -1922, -1922,
   -1922,  1597,  1488,   953, -1922,   998, -1922,    42,   377, -1922,
   -1922,  1577, -1922, -1922,  1424, -1922,   953,   953, -1922,   953,
    1509,   833,   -16, -1922,  4743,  1382, -1922,  4529,  1254,  1254,
     984, -1922, -1922, -1922,  4973,  4973,  4973,  4973,  4973,  4973,
    4781,   878,  1342, -1922, -1922,  1206,  1382, -1922, -1922, -1922,
    1510, -1922, -1922,  1263,  1271, -1922,   876,  1510,  1493, -1922,
   -1922, -1922, -1922,  1402,  1510,  1442,  1442,  1442,   107,  1479,
   -1922, -1922,   369, -1922,    69,   915,   953,   898,    87,  1266,
   -1922,  1081, -1922, -1922,   511,  1267,  1023,   575,  1272,  1052,
      91,    94,   694,  1275,  1124,  4149,   476,  4203,   102, -1922,
    1376, -1922, -1922, -1922, -1922, -1922, -1922,  1318,   -26, -1922,
     138,   953,   953,   454, -1922, -1922, -1922,   105,    56,  1351,
   -1922, -1922,  1590, -1922,  1460, -1922,     4,   360, -1922, -1922,
    1462, -1922, -1922, -1922,  1546,  4149,   530, -1922, -1922, -1922,
   -1922,  1703, -1922,  1335, -1922, -1922,   174, -1922, -1922,   219,
   -1922, -1922,  1382, -1922, -1922, -1922,  1051, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922,  1401,  1051, -1922,  1338, -1922,  1680,
   -1922, -1922, -1922,   407, -1922,   876,   789, -1922,    67,   478,
     232,   102,   102,  4149,   539,  1027,   821,  1600, -1922, -1922,
    1725, -1922,  1561, -1922, -1922, -1922, -1922,  1475, -1922,   953,
     501,    54,   469,  1309,  1617, -1922,  1313,   876,   770, -1922,
     369, -1922, -1922, -1922,  4203,  1103,    54, -1922, -1922, -1922,
   -1922,   -79,   953,  4149,   545,  1345,  1730,   953,  -105, -1922,
   -1922, -1922,  1444,  1446, -1922, -1922,   999, -1922,    10,   953,
    1103,  1580, -1922, -1922,  1146, -1922, -1922, -1922,  1103, -1922,
   -1922, -1922, -1922,  1442,  1088,  1103,   982, -1922, -1922,  1442,
   -1922,  1146, -1922, -1922, -1922, -1922, -1922,   953, -1922,   953,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,   953,
    1553,   232, -1922,  1081, -1922, -1922,   915,   465,   465,  1254,
    1254,  1254, -1922,  1156, -1922,  1051, -1922,   953, -1922,  1462,
   -1922, -1922,  1510, -1922, -1922, -1922,  1103, -1922, -1922,  1103,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922,    18, -1922, -1922,
   -1922,  1402, -1922, -1922, -1922,   155,   155,   155, -1922, -1922,
   -1922, -1922, -1922,  1133,  1279,  4893, -1922,   953,  1133,  1133,
    4973, -1922,  1133,  1133,  1133,   452,  1133,  1133, -1922, -1922,
    1498,  4149, -1922,   102, -1922, -1922,  1322, -1922,   -47,   120,
   -1922, -1922, -1922, -1922,   983, -1922,  1435, -1922,  1423, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,  1139,
    1510,  1501, -1922, -1922, -1922,  4203, -1922,  4203,   219, -1922,
   -1922, -1922,  1703, -1922,   953,  1640,  1337,   900,  1658,  1343,
     286,   876, -1922, -1922,  1716, -1922, -1922, -1922, -1922,   789,
   -1922,  1599, -1922,  1103,  1494, -1922, -1922, -1922, -1922,  1270,
     102, -1922,  4203,   162,   406, -1922, -1922, -1922,   953,  4203,
     675, -1922, -1922, -1922,  1637,  1517, -1922,  1638, -1922,  1544,
   -1922, -1922, -1922, -1922,  1313, -1922, -1922, -1922,  1521,  1639,
    1499,  1486,  1279, -1922,  4203,   286, -1922,  1507, -1922,   876,
   -1922,  1672,  1396, -1922, -1922,  1382, -1922,   970,  1775,   934,
   -1922, -1922, -1922,  1146,  1673,  1571,  1721,  5019,   -53,  1103,
   -1922, -1922,   -53, -1922,  1103,  1177, -1922, -1922, -1922,  1597,
   -1922,  1270, -1922,  1392, -1922, -1922, -1922,   -53,   -53,   124,
     124, -1922, -1922, -1922, -1922, -1922,  1351, -1922,  1166, -1922,
   -1922, -1922,   915, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922,  4203, -1922, -1922,
   -1922, -1922, -1922,  1665, -1922, -1922, -1922, -1922, -1922, -1922,
    1103, -1922, -1922, -1922, -1922,  1110,  1103, -1922, -1922, -1922,
   -1922,    27, -1922,  1139, -1922, -1922, -1922, -1922, -1922,  4149,
    1472,  4149,  1473, -1922, -1922, -1922, -1922, -1922,  1663, -1922,
     900, -1922,  1698, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
     286,   999, -1922, -1922,   999,    -6,   953, -1922, -1922,  4149,
   -1922, -1922,   643,  3795, -1922,  1747,  1565,  1586,   414, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922,  4203,   749, -1922, -1922, -1922,  1660,  1551,   953,
    1351,  4149, -1922,  1730, -1922,  1242,  1715,  1242,  1499,   401,
   -1922, -1922,  1667, -1922,  1557, -1922, -1922, -1922,   393, -1922,
   -1922,  1103,  1723,  1601, -1922,   912, -1922,  1618,   960,  1368,
    1628,  1390,  1103,  1259,  1103,   953, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,  1445, -1922,
   -1922, -1922, -1922,    65, -1922, -1922, -1922, -1922, -1922, -1922,
     450, -1922,   543, -1922,  1388,  1103,  1103, -1922, -1922, -1922,
   -1922,   -53, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922,   -53, -1922, -1922,   -53,   124,   124, -1922, -1922,
   -1922,  4203, -1922,  4203, -1922, -1922, -1922, -1922, -1922, -1922,
    1772,   999,   999, -1922,  1426,  1531,   821,    70, -1922,   953,
   -1922, -1922,  1490,  4203, -1922,  1103,   950,  1596, -1922,  1602,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,  1276, -1922,
    1276, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922,   953,  1242, -1922,   953,  1689,
   -1922, -1922, -1922, -1922, -1922,   821, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922,  1029,  1146,  1103,  1103,  1669, -1922,  1103,
   -1922, -1922, -1922, -1922,   195, -1922,  1103, -1922,   953,   953,
    1113,  1662, -1922,  1558,  1146,    65, -1922, -1922, -1922, -1922,
   -1922, -1922,   -53, -1922, -1922, -1922, -1922,   -53, -1922,  1388,
   -1922,   953,   343,  1029, -1922, -1922, -1922, -1922, -1922, -1922,
    1351,  1351, -1922,  4203,   999, -1922,  4203,  1103,   821,   821,
    1554, -1922, -1922, -1922,  1427,   953,  1706, -1922, -1922, -1922,
   -1922, -1922, -1922,  1576,  1578, -1922, -1922, -1922,   953, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,  1146,  1146,
    1103, -1922,  1146, -1922,  1146, -1922,  1279, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922,  4203, -1922, -1922,
   -1922, -1922, -1922, -1922,   953, -1922, -1922, -1922, -1922, -1922,
   -1922,   -26,   821,  1103, -1922, -1922, -1922, -1922,  1704,  1705,
   -1922, -1922, -1922, -1922,  1146, -1922, -1922, -1922,  1805, -1922,
     -26, -1922,  1051,  1051, -1922,  4203, -1922, -1922, -1922, -1922
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
   -1922, -1922, -1922, -1922,  1850, -1922, -1922, -1922,    72, -1922,
   -1922, -1922, -1922, -1922,  1549, -1922, -1922, -1922,  1186, -1922,
   -1922,    34,  1839, -1922, -1922,  1808,   874, -1922, -1922, -1922,
   -1922, -1922,  1681,  1737, -1922, -1922,  1700,   109, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922,  1692, -1922, -1922, -1922, -1922,
    1674, -1922, -1922, -1922,   581, -1922, -1922, -1922, -1922,  1412,
   -1922, -1922,  1336,   790, -1922, -1922, -1922, -1922, -1922, -1922,
    1481, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922,  1743, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,   987,
      97, -1922,  1330, -1922, -1922, -1922,   991, -1922, -1922, -1922,
     149, -1922,  1671, -1922,  1779, -1922, -1922, -1922, -1922,  1541,
   -1922,   248, -1922, -1922, -1922, -1922,  1675, -1922,  1840,  1742,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,  1074, -1922,
   -1922, -1922,  1373, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922,   930, -1922, -1922, -1922,  1612,
   -1922,  -518,  -735, -1922, -1922, -1922,  -402, -1922, -1922, -1922,
   -1922, -1922, -1922, -1278, -1275,  1100, -1273,   113, -1922, -1922,
   -1922, -1922,   307, -1922, -1922,  -228, -1260, -1922, -1922, -1259,
   -1922, -1258, -1922, -1922,   975, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922,  1399, -1922, -1922, -1922,
     995, -1922,  -702, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
     -75, -1922, -1922, -1922, -1922, -1922, -1922,  -210, -1922, -1922,
   -1922, -1922,  -158, -1922, -1922, -1922, -1922, -1922,  1134, -1922,
   -1922, -1922, -1922, -1922, -1922,   209, -1922, -1922, -1922, -1922,
   -1922,  1787,  1035, -1922,   240, -1922, -1922, -1922, -1922,  1467,
   -1922, -1922, -1922, -1922, -1922, -1922,  -944, -1922, -1922,   175,
   -1922,  1377, -1922, -1922, -1922,   922,   534,   540, -1922, -1922,
     283, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922,   919, -1922, -1922,   254,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922,    60, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922,   695, -1922, -1922,   688, -1922, -1922, -1922, -1922,
     463,   226, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,    47,   696,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922,   680, -1922, -1922,
   -1922,   210, -1922, -1922,   447, -1922, -1922, -1922, -1468, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1921,   897, -1922, -1922,   199, -1922, -1922,   432, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,   616,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922,   657, -1922,   187,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922,   885, -1922,   884, -1922, -1922,  1087, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922,   881,   409, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922,    20, -1922,   413, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,  -163, -1922,
   -1136, -1922, -1922, -1037, -1155, -1129, -1922,   346, -1922, -1269,
   -1922, -1922, -1922, -1922,    19, -1922, -1922, -1922, -1922,   -88,
   -1922, -1922,   211, -1922, -1922, -1922, -1922,    21, -1922,  -502,
   -1634, -1922, -1922,   535, -1922, -1196, -1254,  -807, -1168, -1922,
   -1922,   766,    44,    45,    51, -1922, -1922,   145,  -184,  -294,
    -117, -1114,  -819,    63,   916, -1463,   -83, -1922, -1039, -1922,
    -792, -1922,   758, -1084,  -241, -1922,  -563,  -153,  -813,  -958,
    -181,  -747, -1922, -1922,   455, -1010, -1532,  -929,  -801,  -669,
     691,  -573,  -220, -1922,  1050,  -230,  -618,  -652,  -277,  -361,
    -922, -1922, -1922, -1922, -1922, -1922,  1752, -1922, -1922,   811,
   -1922, -1922, -1922, -1599,  1180,  -263,  1685,   726,  -401, -1922,
    -362,  1429, -1922,  -606, -1922, -1054,  1057,  -384,   684, -1922,
   -1922,  -670, -1922, -1698,  -164,  -596,  -471,  -146,  -925,   646,
   -1340,  -797, -1183, -1922,  1227,  1934,  -707, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1162, -1922,   198,  -653,   871,  -470
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1518
static const short yytable[] =
{
     118,   236,   424,   807,   840,   798,   320,   555,   935,   500,
     557,  1327,   988,  1499,  1300,  1414,   872,   790,   334,   972,
     337,   815,   339,  1291,   259,   260,   261,   981,   263,  1003,
     266,  1018,   255,  1734,   914,   976,  1636,  1637,   262,   335,
    1159,   335,  1284,   335,  1064,  1816,   769,    21,  1405,   517,
    1048,  1543,  1238,   398,  1230,  1206,  1581,   269,  1009,  1582,
    1238,  1583,   310,  1453,   311,  1009,   118,  1441,  1442,  1443,
    1490,   318,  1009,   748,  1584,  1585,  1586, -1481,   966,   323,
     405,   380,   387,   905,  1341,   536,   966,   997,   386,   271,
     399,   330,   331,  1478,   332,  1685,    84,   404,   338,  1009,
    1372,  1029,  1031,   335,   937,    91,  1238,   343,  1009,   906,
     907,   335,   342,   344,  1445,  1071,   966,   264,   335,   398,
    1380,   123,    53,   184,   426,  1320,   362,   241,  1358,   367,
     369,   421,   372,  1809,   154,  1506,  1341,   175,   433,  1479,
     624,    88,  2016,  1946,  1493,   335,   357,   335,   381,   357,
    1142,   441,  1589,    40,  1341,  1149,   439,   816,  1341, -1481,
    1679,  1341,   770,  1930,  1075,   388,  1320,  1292,   185,  1328,
    1375,   761,   154,  1607,   319,    62,  1696,   244,   467,   810,
     926,   446,   502,   465,   513, -1517,   154,   538,   407,   348,
     430,   883,  1533,   895,  2035,  1448,  1245, -1441,  1375,   423,
     631,   975,  1838,   186,   187,   335,   188,   435,  1354, -1468,
    1052, -1517,  1237,   553,   189,    40,   438,   405,  1164,  1462,
   -1445,  1227,  1836,  1789,  1731,   231,  1324,  1200,  1023,  1794,
     378,  1609,    40,  1932,  -177,  1477,   539,  2075,  1609,  2078,
    1448,   860,  1549,  1053,   817,  1609,  1164,  1289,    51,   556,
    2149,  1480,  1779,  1894,   769, -1457,   510,  1536, -1517,  1727,
    1430,   137,   427,   348,  1763,   406,   414,  1119,   190,   975,
   -1517,  1087,    31,   810,   273,   521,   522,  1381,   240,  1704,
    1254,   623,   749,  1217,    54,     3,   628,  1677,  1453, -1360,
    2229,  1453,   319,  1661,   363,   803,   364,  1535, -1491,  1686,
    1481,   633,   633,  1079,   379,  1053,   926,  1678,   908,  2236,
    1431,   549,  1103,  1337,  2113,   228,   138,   139, -1517,  1780,
    1316,  1781,  1071,   273,   179,   333,   750,  1164,   228,  1080,
    1613,  1238,  1325,  1134,   232,   870,   559,  1633,   975,  1277,
     191,  1728,   919,   988,   618,   562,  1508,   240,  2150,  -177,
     179, -1445,   803,   861,  2114,   789,  1612,    63,  2033,  1376,
     229,  1129,  1130,   428, -1441,    54,  1669,  1342,    55,   552,
     770,   792,   163,   229,  1132,  1133,  1228,   333,  2168,   747,
     884,  1042,  1205,  1986,   752,   803,  1088,   756,   757,   -31,
     758,   759,  1833,   333,   765,   245,   625,  1688,  1377,  1329,
    1286, -1445,   406,   333,   333,   247,  1429,   333,    64,   988,
    1778,   358,  2158,   762,  1555,  1406,  1478,  2036,  2031,  1342,
     242,  2032,   440,  1003, -1457,   804,  1377,   319,   885,  1246,
    1606,  1810, -1468, -1463,  1687,  1839,   797,  1342,  1321,   988,
    2017,  1342,  1492,   317,  1342,  1293,   253,  1464,  1200,    55,
    1662,  1701,  1518, -1445,   192,   516,   938,    88,   537,  1119,
    1119,  1119,  1479,  1343,  1231,  1294,    85,   983,   909,  1119,
     763,   333,   333,   553,   389,  1714,  2085,  1503,   534,  1321,
    1444,  1446,   333,  1609,  1482,  1024,  1286,   988,   253,   333,
     983,  1119,  1247,  1119,   193,  1119,   333,  1391,  1919,  1119,
    1119,  1119,  1119,  1119,  1119,  1119,  1119,  1755,  1353,  1967,
   -1445,  1494,  1968,   390,  1969,  1643,  1703,   898,   899,  1411,
     391,  1705,   179,   333,   904,  1545,   932,  1971,  1972,  1973,
    1453,   389,   333, -1399,  1238,  1865,   335,  1653,   335,   335,
    1654,   333,   194,   154,  1840,   335,  1523,  2003,  1243, -1441,
    1527,  1528,  -177,  1530, -1445,   267,  1135,   447,  1120,  1534,
   -1445,  2080, -1445,   154,   389,  2144,  1042,  1507,  1449,  1383,
     390,  1355,  1450,  2148,  1480,  1806,  1390,   391,  1341,   179,
      62,  1869,   882,  1871,   887,   333,  1332,  2227,   988,   333,
     941,   392,  1939,  1286,   805,  -941,  1640,  1556,   179,   166,
    2020,  2081,  2022,   390,   913,  2047,    87,   979, -1517,  2082,
     391,  1672,  1669,  1449,  2002,  2099, -1491,  1450,  1899, -1517,
     319,  1742,     4,  1481,    18,  1115,  1665,  1026, -1517, -1488,
    2040,  1041,  1053,  1045,  -941,  1045,  1051, -1517,  1026,    12,
     775,  -941,  1341,   444,   104,  2048,   898,  1053,   392,   401,
    1931,   891,   993,  1045,   393,  1286,  -728, -1517,   801,  1131,
     376,  2072,  2073,  1096,  1461,  2049,   888,   335,  1826,   104,
    1090,  1724,    13,  1514,  1297,   983,  2091,  1514,  1730,  2083,
     377,   392,  1074,   394,   335,  1593,  2212,  1107,  2118,   776,
    1150,    22,  1119,  1119,  1119,  1119,  1119,  1119,  1119,    19,
    1748,  1889,  1123,    15,   164,  1834,  1812,  1813,  1814,   818,
    1697,   393,  -941,    25,  1286,  1202,   333,   335,   335,  1732,
    1749,  1815,   395,   402,    28,  1764,  1820,  1821,  1421,  1085,
    1823,  1824,  1825,  1673,  1828,  1829,  1848,  1849,  1428,  2119,
     394,  1098,   105,   794,   393,  1994,  1138,     5,  1867,   990,
    1120,  1120,  1120,  1725,  1743,  2001,  2001,  1676,   184,  1934,
    1120,  1341,    63, -1459,  1592,  1793,   999,   105,    74,  1043,
    1000,  1046,  1238,   394,     5,  -941,  1066,  1757,   892,   395,
   -1441,  2123,  1120,   164,  1120,  1077,  1120,    32,  1392,  1689,
    1120,  1120,  1120,  1120,  1120,  1120,  1120,  1120,  1715,   333,
     469,  1290,  1116,   185,  -941,   164,   179,  1482,  1512,  1642,
   -1445,     5,   395,  1706,  1215,   470,   165,  1338,  1339,  1340,
    2138,  2139,  1709,   333,   471,  1298,  -583,  1351,  1051,  1986,
   -1445,   115,  2124,  1286,  1286,   179,   115,  -941,   186,   187,
    2050,   188,   802,  -941,  1716,   141,  -581,    74,  1512,   189,
     889,  1387,  1827,  2185,   426,   893,   241,  1394,  1396,  1397,
    1399,  1342,   795,  1402,  1404,  1286, -1517,  1906,  1215,    74,
     164,  2207,  2208,  1331,  2041,   335,  1870,  1215,  1872,  1422,
     777,  1359,  1360,  1215,  1278,    17,  2005,  2120,  2121,   389,
    1139,   779,  1874,  1094,  2042,   165,  2163,  1272,  2164,  1172,
    1173,  2011,  1208,   190,  1347,  1348, -1517,  1349,   472,  2092,
     781,   237,  1467,   988,   335,  1468,  1469,   165,  1047, -1445,
    1318,  1361, -1488,  1362,  2019,  1342, -1517,  2057,   390,   778,
    1326,  2024,    29,  2058,    74,   391,  1083,   473,  -583, -1445,
     780, -1441,  1273,  1917,    90,   988, -1463,  1642,  1345,  1346,
    1347,  1348,  1803,  1349,  1363,  1364,  1365, -1405,  -581,   782,
    2231,    33,  2001,  2001,  2059,  2051,  2052,  1691,  2060,    92,
    1259,  1095,    40,   361,  2054,   191,  1594,   389,   368,   325,
    2125,  2126,   165,  1120,  1120,  1120,  1120,  1120,  1120,  1120,
     239,   472,  1905,  1119,  1116,  1116,  1116,   783,  1119,   166,
      35,  1366,   326,  1367,  1116,  1717,   392,  1504, -1441,  1747,
    1260,  1368,  1345,  1346,  1347,  1348,   390,  1349,  1261,   979,
     473, -1403,   753,   391,  1759,  1733,  1116,   474,  1116,   754,
    1116,    93,    43,  1505,  1116,  1116,  1116,  1116,  1116,  1116,
    1116,  1116,    37, -1517,  1342,    44,   784,  2204,    48,   979,
    1596,  1597,  1598,  1599,  1600,  1601,  1603,  1552,  1553,  1286,
     948,  1761,  2134, -1517,   389,    49,  2135,  1286,  1761,   393,
    1742,    94,   475,    95,   540,   950,   541,   321,   476,   799,
   -1407,  2142,  1369,    45,    52,   426,   513,  1723,  1262,   192,
    2007,    46,  1888,   283,   392,  1267,  1053,   979,   394,   800,
     289, -1517,   179,   390,   179,   477,   335,   335,  1268,  2161,
     391,  2162,   478,   290,    58,   543,   250,  1286,  1940,   450,
     548,    59,  2165,  1991,    60,   479,  1424,  1004,  1005,   193,
      67,  1345,  1346,  1347,  1348,    61,  1349,   395,  1998,  1999,
   -1400,  1006,  2172,  2173,  1470,  1471,     5,  1888,   276,   242,
     291,  1540,   480,   282,    71,  1541,  1430,   393,   451,   951,
     481,    74,  1472,  1473,  1521,   452,  2109,    78,  1522,   874,
    -192,  1850,  1634,  2098,  1851,  2056,  1430,   194,  1308,   111,
    1309,   392,  1852,  1853,  1854,    80,   394,  1007,    10,  1718,
     227,   482,    10,  1190,   227,   449,  1193,  1194,   979,  2189,
    2190,    81,  2140,  1743,  2141,   983,  1431,   351,   875,   980,
    1647,   954,   102,  1650,   955,   876,   112,  1425,  1655,   333,
    2102,  2103,  2220,  2191,  1941,   395,  1431,  1116,  1116,  1116,
    1116,  1116,  1116,  1116,   113,  1790,   454,  1791,  1841,   483,
    1842,   179,   121,  1780,   393,  1781,   956,   947,  1370,  1466,
     803,   115,  1467,  2174,  2175,  1468,  1469,  2013,  1898,  2014,
     125,    40,   126,   127,  1902,   450,   292,   128,   129,   130,
    1908,   132,  1888,   394,   133,   135,   293,   144,   145,  2093,
    -310,   146,   415,   160,  1120,   161,   877,  1371,  1384,  1120,
     162,  1855,  1388,   175,   209,   212,  2154,   215,   213,   455,
    1400,  1401,   219,   220,   451,   235,   333,   221,   513,  1856,
      40,   452,   395,   252,   957,  1345,  1346,  1347,  1348,   948,
    1349,   253,   249,   453,  1786,   256,  1857,  1350,  -751,   335,
    1995,  -751,  2133,   257,   950,  1345,  1346,  1347,  1348,   264,
    1349,  1795,   271,  2136,   273,   278,  2137,  1645,  1798,   878,
     280,  1818,  1345,  1346,  1347,  1348,  1822,  1349,   279,   958,
     959,  1758,   312,   294,   295,   285,  1804,   458,   313,   335,
     154,   315,  1858,   319,   324,   322,   296,   328,   297,   327,
     336,   353,   454,   333,   960,   354,  1783,   335,   356,   370,
     373,  1211,   375,   382,  1788,   383,  2209,  2192,  2193,  2210,
    -751,  1792,   961,   400, -1445,   412,  1819,   417,   418,  -322,
     962,   420,   333,   434,   503,  -751,   422,   879,   951,  1859,
     436,  1345,  1346,  1347,  1348,   511,  1349,   335,   464,   389,
    1595,   514,  1615,   520,  1616,   518,   544,  1617,  2194,  2195,
   -1352, -1352, -1352, -1352,   545,   455,   547,  1618,   456,   457,
    2228,   550,  1807,  2201,   558,  1808,   179,   560,  2202,   952,
    1345,  1346,  1347,  1348,   953,  1349,   620,   622,   390,  1649,
     954,   629,  1860,   955,   636,   391,   637,   638,   298,   742,
     745,   553,  1861,   766,  1470,  1471,   767,   774,  2239,  1345,
    1346,  1347,  1348,   785,  1349,   787,   793,   299,  1652,  -751,
     822,   821,  1472,  1473,   864,   956,   896,   900,  2183,   903,
    -751,   916,   917,   458,  2205,   945,   919,   927,   922,   982,
    1221,  1222,  1223,  1224,   995,   929,   933,   939,  1116,  1012,
    1013,   936,   942,  1116,   943,  1012,  1020,  1022,   970,   998,
    -751,  1015,   982,  1862,  1082,  -751,   392,  1084,  1012,  -751,
    1091,  -751,  1099,  1950,  -751,  1105,  -751,  1020,  1076,  1896,
    1078,  1345,  1346,  1347,  1348,  1121,  1349,  1127,  1126,  1108,
    1657,   810,  1619,   957,  1136,  1143,  1620,  1160,  1145,  2237,
    2238, -1351, -1351, -1351, -1351,  1147,  -751,  1151,  1152,  1621,
    1153,  -751,  1154,  1345,  1346,  1347,  1348,  2105,  1349,  1155,
    1156,  1165,  1802,  1345,  1346,  1347,  1348,  1157,  1349,   393,
    1118,  1167,  2004,  1158,  1201,  1203,  1209,  1215,   958,   959,
     753,  1218,  1236,  1225,  1240,  1990,  1255,  -751,  1256,  1258,
    1992, -1354,  1265,  1269,  1271,  1622,  1270, -1445,   394,  1275,
    1144,  1280,  1282,   960,  1053,   154,  1304,  1307,  1313,  1311,
    1314,   414,  1316,  1335,  -751,  2038,  1356,  1373,  1386,  1393,
    1407,   961,  1417,  1408,  1412,   975,  1436,  1438,  1454,   962,
    1476,   333,   948,  1456,  1491,  1207,   335,   395,  1509,  1459,
    1495,  1517,  1623,  1524,  -751,  1212,  2012,   950,  1525,  1532,
    -751,  1537,  2015,  1547,  1548,  1550,  1349,  1604,  1610,  -751,
    -751,  1012,  1634,  1376,  1614,  1611,  1624,  1663,   948,  1012,
    1244,  1664,  1646,  1648,  1658,  1682,  1431,  1693,  1651,  -751,
    1698,  1656,  1707,   950,  -751,  1699,  1695,   982,  1711,  -751,
    1625,  1710,  1735,  1738,  1739,  1626,  1750,  1751,  1765,  1766,
    1752,  1774,  -751,  1285,  1776,  1627, -1445,  1784,  1799,  1628,
    -751,  1012,  -751,  2117,  1846,  1012,  1831,  1847,  -751,  1877,
    1866,  1879,  1883,  1303,  1890,  1033,  1244,  1885,  1893,  1897,
    1743,   951,  1911,  1921,  1914,  1916,  1929,  1924,  1926,  1935,
    1937,  1933,  1947,  1951,  1952,  1954,  1996,  2094,  2008,  1207,
    2021,  2023,  1020,  2026,  2029,  2043,  2044,  2045,  2108,  2067,
    2110,  1033,  1118,  1118,  1118,  2076,  1629,   951,  2069,  2088,
    2095,  1941,  1118,  2106,  2100,  2096,  1630,  2107,  2128,  2152,
    2143,  1034,  2145,   954,  2153,  1963,   955,  2159,  2147,  1285,
    2170,  2131,  2132,  2160,  1118,  2197,  1118,  2180,  1118,  2214,
    2216,  2198,  1118,  1118,  1118,  1118,  1118,  1118,  1118,  1118,
    2218,  2213,  2219,  2235,  2232,  2233,    14,   980,   956,   954,
      27,    73,   955,   251,  2177,   182,   385,   238,  2188,   248,
     268,  1519,   535,   744,  1319,   211,  1949,   463,  1086,   755,
    1093,  2155,  1900,   270,  2199,  2117,   142,   411,    66,   335,
     426,   223,   275,   940,   956,   634,   355,   923,  1801,  1125,
    1970,  2203,  1102,  2112,   563,  2200,   915,   159,  1837,   523,
     741,   335,  1903,  1639,  1811,  1220,   947,  1229,  1638,   803,
    1835,  1457,  1702,  2018,  1873,  1447,   957,  2028,  1487,  1892,
    1712,  2178,  2179,  1264,  1546,  2182,  1285,  1904,  1475,  1740,
    1516,  1920,  2184,  1287,  1288,  1065,  1012,  1772,  2222,  2223,
    1302,  1773,  2225,  2074,  2226,  1805,  1913,  2079,  2157,  1502,
    1419,  1416,   957,   513,  1279,  2090,  1207,  2061,  2062,  1684,
    1122,   958,   959,  1515,  2063,  1756,   284,   366,  1410,  1489,
    1012, -1517,   931,  2211,   335,   760,  1128,  2206,   948,   902,
      75,   979,  1531,  1993,  2234,  1352,   960,     0,  1285,     0,
       0,     0,   414,   950,  1539,     0,  -992,   958,   959,     0,
     979,     0,     0,     0,   961,     0,  2224, -1517,     0,  -992,
    1244,     0,   962,   179,   333,     0,     0,     0,     0,     0,
       0,     0,   960,     0,     0,  1118,  1118,  1118,  1118,  1118,
    1118,  1118,  -992,     0,     0,     0,     0,     0,     0,  2230,
     961,     0,     0,  1520,     0,  -992,     0,  1285,   962,   179,
     333,     0,     0,     0,     0,   414,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1644,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   951,     0,     0,
       0,     0,     0,   947,     0,     0,   803,     0,   389,  1012,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1670,  1671,     0,     0,  1138,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   952,   414,
       0,     0,     0,   953,     0,     0,     0,   390,     0,   954,
       0,     0,   955,     0,   391,     0,     0,     0,     0,     0,
   -1441,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   948,     0,     0,     0,     0,
       0,     0,     0,     0,   956,     0,  1285,  1285,     0,     0,
     950,     0,  1012,  1012,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1741,     0,     0,     0,     0,     0,     0,     0,  1285,     0,
       0,     0,     0,     0,     0,   392,     0,     0,     0,     0,
       0,     0,     0,  1762,     0,     0,     0,     0,  1771,  1771,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     842,     0,   957,     0,     0,  -884,     0,     0,  -884,     0,
       0,  -884,  -884,  -884,     0,     0,     0,   982,     0,  -884,
       0,     0,     0,     0,   951,     0,     0,     0,  1796,     0,
    1797,     0,     0,     0,     0,   389,     0,     0,   393,     0,
       0,     0,     0,     0,     0,     0,     0,   958,   959,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1521,   952,     0,   394,  1522,     0,
     953, -1441,   960,     0,   390,     0,   954,  -884,     0,   955,
       0,   391,     0,     0,     0,     0,  1207,  1207,  1207,     0,
     961,     0,  -884,     0,     0,     0,  1118,     0,   962,     0,
     333,  1118,     0,     0,     0,     0,   395,     0,     0,     0,
       0,   956,     0,     0,  1012,     0,     0,     0,     0,     0,
       0,     0,     0,   947,     0,     0,   803,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0, -1441,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -884,
    -884,     0,   392,     0,     0,  1876,     0,     0,     0,     0,
       0,  1887,  1285,     0,     0,     0,     0,     0,     0,     0,
    1285,     0,     0,     0,     0,     0,  -884,  -884,     0,   957,
       0,  1012,     0,  -884,     0,     0,     0,  -884,     0,  1502,
       0,     0,     0,     0,     0,   948,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     950,     0,     0,     0,  -884,   393,  1887,  -884,  -884,     0,
    1285,     0,  -884,  1068,   958,   959,  -884,     0,  -884,     0,
       0,  -884,     0,  -884,     0,     0,     0,     0,     0,  1988,
       0,     0,     0,  1988,   394,     0,  -884,  -884,     0,   960,
       0,  -884,     0,     0,     0,     0,     0,     0,  1988,  1988,
       0,  -884,     0,  -884,     0,     0,     0,   961,  -884,     0,
       0,     0,     0,  -884,     0,   962,     0,   333,     0,     0,
       0,     0,     0,   395,     0,     0,     0,     0,     0,     0,
       0,  -884,     0,     0,   951,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -884,   389,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1301,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -884,     0,     0,     0,   952,     0,     0,     0,     0,
     953,  1887,     0,     0,   390,     0,   954,     0,     0,   955,
       0,   391,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -884,     0,     0,
       0,     0,     0,     0,     0,     0,  -884,  -884,     0,     0,
    2071,   956,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -884,     0,     0,  1988,
       0,  -884,     0,  -578,   524,     0,  -619,     0,  -619,     0,
       0,     0,     0,  -619,     0,     0,  2111,     0,     0,  -884,
       0,  -619,   392,     0,     0,     0,     0,  -884,     0,  -884,
       0,     0,     0,     0,     0,  -884,  -884,  -884,  -884,  -884,
       0,  -884,     0,  -884,  -884,  -884,  -884,  -884,     0,   957,
       0,     0,  1988,  -619,  -619,     0,     0,     0,     0,     0,
    -619,     0,     0,  1988,     0,     0,  1988,     0,     0,     0,
       0,  -619,     0,     0,  -619,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   393,  -619,     0,     0,     0,
       0,     0,     0,     0,   958,   959,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -619,     0,
       0,     0,     0,     0,   394,  -619,  -619,     0,     0,   960,
       0,     0,     0,     0,     0,     0,  2167,     0,     0,  2169,
       0,     0,  -578,     0,     0,     0,  -578,   961,     0,     0,
       0,     0,     0,     0,     0,   962,  -619,   333,     0,     0,
       0,     0,     0,   395,     0,     0,     0,     0,  -619,  2186,
       0,     0,  -619,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1988,     0,  -619,     0,     0,  1988,  -578,
       0,     0,  -619,     0,     0,  -619,  -619,     0,     0,     0,
       0,     0,     0,  -619,     0,     0,     0,     0,     0,     0,
    -619,     0,  -619,     0,     0,  -619,  2215,     0,     0,     0,
       0,     0,   524,     0,  -619,     0,  -619,     0,     0,  2221,
       0,  -619,     0,     0,     0,     0,     0,     0,     0,  -619,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -619,     0,     0,     0,  -619,     0,  -619,     0,     0,     0,
       0,     0,     0,  -619,     0,     0,     0,     0,     0,     0,
       0,  -619,  -619,     0,     0,     0,     0,     0,  -619,     0,
       0,     0,     0,     0,     0,  -619,     0,     0,     0,  -619,
       0,     0,  -619,     0,     0,     0,     0,     0,     0,     0,
    -619,     0,     0,     0,  -619,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -578,     0,     0,     0,     0,     0,
       0,  -619,     0,     0,     0,     0,  -619,     0,     0,     0,
    -619,     0,     0,  -619,  -619,     0,     0,     0,     0,     0,
       0,   635,     0,  -619,     0,     0,     0,     0,  -619,     0,
    -619,     0,     0,     0,     0,     0,     0,     0,  -619,     0,
     947,     0,     0,   803,  -619,     0,     0,     0,  -619,     0,
       0,     0,     0,     0,     0,     0,  -619,  -619,     0,     0,
    -619,     0,     0,     0,     0,     0,  -619,     0,  -619,  -619,
       0,     0,  -619,  -619,  -619,     0,     0,     0,     0,  -619,
    -619,     0,     0,  -619,  -619,     0,     0,     0,     0,     0,
       0,  -619,     0,     0,  -619,     0,     0,     0,  -619,  -619,
    -619,     0,     0,  -619,  -619,     0,     0,     0,     0,     0,
       0,     0,   948,     0,     0,  -619,     0,     0,     0,     0,
       0,     0,     0,   525,     0,     0,  -619,   950,     0,     0,
       0,     0,     0,     0,     0,     0,   526,     0,  -619,     0,
    1068,     0,  -619,     0,  -619,     0,     0,   947,     0,     0,
     803,  -619,     0,  1168,  1169,  1170,     0,     0,     0,     0,
       0,  1171,     0,   567,   568,   569,   570,   571,   572,     0,
       0,     0,     0,  -619,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -619,     0,
       0,     0,     0,     0,     0,     0,     0,   574,     0,   575,
     576,   577,   578,   579,   580,     0,     0,     0,     0,  -619,
       0,   951,     0,     0,     0,     0,     0,     0,  -619,   948,
       0,     0,   389,     0,     0,     0,     0,     0,     0,     0,
       0,  -619,     0,     0,   950,     0,  -619,     0,  -619,   581,
       0,     0,     0,     0,     0,     0,  -619,     0,     0,     0,
       0,     0,   952,     0,     0,     0,  -619,   953,     0,     0,
       0,   390,     0,   954,     0,  -619,   955,     0,   391,     0,
       0,     0,     0,     0,  -619,     0,  -619,  -619,     0,     0,
    -619,     0,  -619,     0,     0,     0,     0,  -619,     0,     0,
       0,  1172,  1173,     0,     0,     0,     0,     0,   956,     0,
       0,     0,  -619,     0,     0,     0,     0,  -619,     0,     0,
       0,     0,  -619,     0,     0,     0,     0,     0,   951,  1174,
       0,   582,     0,  -619,     0,  1175,     0,     0,     0,   389,
       0,   525,     0,     0,  -619,     0,     0,     0,     0,   392,
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
     583,     0,     0,     0,   392,     0, -1498,     0,     0,     0,
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
   -1498,     0,     0,  1572,   586,     0,     0,     0,   597,   598,
     599,   587,     0,   588,     0,     0,     0,     0,     0,     0,
       0,   600,     0,     0,   601,   956,   589,  1573,     0,     0,
       0,   948,     0,     0,     0,   567,   568,   569,   570,   571,
     572,   573,     0,  -317,     0,     0,   950,     0,     0,     0,
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

static const short yycheck[] =
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
     227,   117,  1306,   756,   200,    21,    88,    47,    63,   363,
     227,   227,    82,    91,    92,   425,    94,   371,  1133,   207,
     144,   290,  1009,   211,   102,   207,   374,    22,   965,   108,
      82,    48,   269,  1563,  1493,   315,   231,   974,   846,  1569,
      30,  1360,   207,  1765,   112,  1245,   466,  1935,  1367,  1937,
      21,   227,  1326,   239,   628,  1374,   993,  1060,    39,   479,
     180,   167,   242,  1721,   772,   101,   420,  1311,   165,    27,
     206,   309,   269,   346,  1533,   207,   349,   919,   156,   227,
     101,   112,    24,    29,   169,   439,   440,   300,   169,  1462,
    1027,   511,   117,   990,   312,     0,   516,   231,  1456,   392,
    2211,  1459,   227,  1407,   309,     9,   311,  1307,    36,   295,
     216,   521,   522,     8,   104,   239,   924,   251,   283,  2230,
     256,   475,   908,  1110,   249,   362,   364,   365,   168,   309,
     270,   311,  1069,   169,   429,   430,   161,  1074,   362,    34,
    1367,  1289,   337,   939,   424,   181,   500,  1374,   227,  1046,
     228,   109,   445,  1162,   508,   503,  1275,   238,   278,   227,
     429,   227,     9,   339,   289,   585,  1366,   344,  1890,   224,
     407,   934,   935,   370,   120,   312,  1420,   350,   396,   107,
     772,   591,   124,   407,   937,   938,   203,   430,  2076,   543,
     306,   851,   227,   436,   548,     9,   227,   551,   552,   443,
     554,   555,  1661,   430,   558,   227,   311,  1436,   291,  1101,
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
     162,  1695,   746,  1697,   748,   430,  1104,  2186,  1407,   430,
     820,   305,  1775,  1245,   218,   188,   227,  1332,   429,   430,
    1869,   200,  1871,   227,   768,   191,   133,   827,   231,   208,
     234,   157,  1666,   394,  1810,  1955,   354,   398,  1732,   259,
     227,   120,   176,   216,   227,   919,  1418,   847,   251,    60,
    1899,   851,   239,   853,   227,   855,   856,   231,   858,   443,
     358,   234,    67,   133,   242,   231,   887,   239,   305,   193,
    1764,    31,   833,   873,   368,  1307,   180,   251,   216,   936,
     161,  1930,  1931,   904,  1237,   251,   111,   887,   216,   242,
     890,   193,   443,  1279,   180,  1036,   283,  1283,  1491,   278,
     181,   305,   863,   397,   904,  1337,  2149,   917,   238,   407,
     953,   114,  1344,  1345,  1346,  1347,  1348,  1349,  1350,   302,
     231,  1711,   922,   144,   236,  1663,  1635,  1636,  1637,   173,
     180,   368,   305,    26,  1366,   978,   430,   937,   938,   180,
     251,  1643,   436,   267,   443,   180,  1648,  1649,   180,   882,
    1652,  1653,  1654,   279,  1656,  1657,  1680,  1681,  1208,   289,
     397,   905,   340,   217,   368,  1799,    29,   301,  1692,   832,
    1111,  1112,  1113,   275,   253,  1809,  1810,  1427,    11,  1769,
    1121,    67,   344,   227,  1337,  1566,   394,   340,   300,   852,
     398,   854,  1730,   397,   301,   368,   859,  1524,   158,   436,
      63,   238,  1143,   236,  1145,   868,  1147,   227,  1149,   429,
    1151,  1152,  1153,  1154,  1155,  1156,  1157,  1158,     9,   430,
       4,   393,   919,    56,   397,   236,   429,   400,  1278,  1382,
     315,   301,   436,  1466,   338,    19,   348,  1111,  1112,  1113,
    2016,  2017,  1475,   430,    28,   331,   331,  1121,  1048,   436,
     315,   430,   289,  1485,  1486,   429,   430,   430,    91,    92,
     426,    94,   400,   436,    55,   443,   331,   300,  1318,   102,
     295,  1145,   400,  2107,  1095,   235,    60,  1151,  1152,  1153,
    1154,   350,   336,  1157,  1158,  1517,   191,   192,   338,   300,
     236,  2140,  2141,  1103,   231,  1095,  1695,   338,  1697,   331,
     358,    24,    25,   338,  1047,    11,  1830,   437,   438,   188,
     173,   358,  1699,   366,   251,   348,  2058,   249,  2060,   150,
     151,  1845,   985,   156,   439,   440,   231,   442,   195,  1948,
     358,   443,    12,  1732,  1134,    15,    16,   348,   855,   424,
    1083,    64,   353,    66,  1868,   350,   251,   178,   227,   407,
    1094,  1875,    96,   184,   300,   234,   873,   224,   443,   424,
     407,   224,   294,  1750,    70,  1764,   181,  1520,   437,   438,
     439,   440,  1605,   442,    97,    98,    99,   446,   443,   407,
    2214,   443,  2016,  2017,   215,  1909,  1910,  1437,   219,   265,
     160,   444,   207,   289,  1918,   228,  1337,   188,   294,   204,
     437,   438,   348,  1344,  1345,  1346,  1347,  1348,  1349,  1350,
     443,   195,  1739,  1645,  1111,  1112,  1113,   358,  1650,   430,
      79,   144,   227,   146,  1121,   216,   305,     8,   291,  1511,
     200,   154,   437,   438,   439,   440,   227,   442,   208,  1239,
     224,   446,   309,   234,  1526,  1495,  1143,   231,  1145,   316,
    1147,   327,   346,    34,  1151,  1152,  1153,  1154,  1155,  1156,
    1157,  1158,   114,   231,   350,   163,   407,  2131,   443,  1269,
    1344,  1345,  1346,  1347,  1348,  1349,  1350,   224,   225,  1711,
      78,  1531,  2006,   251,   188,   297,  2010,  1719,  1538,   368,
     120,   367,   276,   369,   268,    93,   270,   443,   282,   161,
     430,  2025,   225,   201,   443,  1326,  1327,  1488,   278,   342,
    1837,   209,  1710,   443,   305,   412,   239,  1317,   397,   181,
      46,   426,   429,   227,   429,   309,  1326,  1327,   425,  2053,
     234,  2055,   316,    59,   443,   469,   443,  1769,   148,   188,
     474,   443,  2066,  1792,   346,   329,   314,   286,   287,   382,
     114,   437,   438,   439,   440,   443,   442,   436,  1807,  1808,
     446,   300,  2086,  2087,   244,   245,   301,  1765,   218,   353,
      96,   153,   356,   223,   129,   157,   206,   368,   227,   177,
     364,   300,   262,   263,   394,   234,  1963,   443,   398,   188,
     374,    32,   260,   261,    35,  1922,   206,   430,   309,   443,
     311,   305,    43,    44,    45,   346,   397,   346,     2,   400,
     155,   395,     6,   444,   159,   118,   447,   448,  1418,    86,
      87,   432,  2021,   253,  2023,  1566,   256,   277,   227,   227,
    1394,   229,   163,  1397,   232,   234,   346,   405,  1402,   430,
     260,   261,  2166,   110,   254,   436,   256,  1344,  1345,  1346,
    1347,  1348,  1349,  1350,   230,   147,   305,   149,   255,   443,
     257,   429,   331,   309,   368,   311,   264,     6,   391,     9,
       9,   430,    12,   224,   225,    15,    16,   147,  1729,   149,
     443,   207,   443,   443,  1734,   188,   212,   443,   443,   349,
    1740,   443,  1890,   397,   209,   395,   222,   443,   346,  1948,
     430,   226,   352,   430,  1645,   443,   305,   430,  1143,  1650,
     443,   152,  1147,   175,   273,   443,  2043,    23,   385,   368,
    1155,  1156,   443,   346,   227,   362,   430,   322,  1549,   170,
     207,   234,   436,   101,   332,   437,   438,   439,   440,    78,
     442,   430,   443,   246,  1554,   374,   187,   449,     6,  1549,
    1801,     9,  2001,   357,    93,   437,   438,   439,   440,    55,
     442,  1571,    81,  2012,   169,   443,  2015,   449,  1589,   368,
     341,  1645,   437,   438,   439,   440,  1650,   442,   346,   377,
     378,  1525,   362,   309,   310,   430,  1607,   436,   273,  1589,
      48,   103,   233,   227,   204,   353,   322,   240,   324,   443,
      65,   443,   305,   430,   402,   346,  1550,  1607,   443,   240,
      22,   150,   267,   430,  1558,   443,  2143,   284,   285,  2146,
      78,  1565,   420,   227,    82,   291,  1647,   443,   443,    80,
     428,    80,   430,   425,   307,    93,   430,   436,   177,   280,
     430,   437,   438,   439,   440,   393,   442,  1647,   390,   188,
     446,   225,    30,   430,    32,   193,   309,    35,   325,   326,
     416,   417,   418,   419,   393,   368,   354,    45,   371,   372,
    2197,    54,  1616,  2122,   374,  1619,   429,    36,  2127,   218,
     437,   438,   439,   440,   223,   442,    26,   181,   227,   446,
     229,   362,   333,   232,   443,   234,   443,   346,   424,   443,
     374,   211,   343,   430,   244,   245,   354,   218,  2235,   437,
     438,   439,   440,   427,   442,   336,   207,   443,   446,   177,
     227,   103,   262,   263,   296,   264,   371,   277,  2104,   271,
     188,   436,   393,   436,  2132,   824,   445,    26,   390,   828,
     416,   417,   418,   419,   833,   352,   267,   168,  1645,   838,
     839,   450,   443,  1650,   443,   844,   845,   846,   430,   227,
     218,   130,   851,   404,   101,   223,   305,    17,   857,   227,
     429,   229,   166,  1783,   232,   181,   234,   866,   867,  1723,
     869,   437,   438,   439,   440,   445,   442,   227,   390,   392,
     446,    29,   170,   332,   121,   445,   174,   122,   445,  2232,
    2233,   416,   417,   418,   419,   445,   264,   445,   445,   187,
     445,   269,   445,   437,   438,   439,   440,  1959,   442,   445,
     445,   198,   446,   437,   438,   439,   440,   445,   442,   368,
     919,    55,   446,   445,   393,   423,   124,   338,   377,   378,
     309,   126,    95,   127,   389,  1789,   393,   305,   131,    48,
    1794,   392,   132,   390,   387,   233,   392,   315,   397,   173,
     949,   137,   425,   402,   239,    48,   140,   173,   323,   106,
     370,  1734,   270,   108,   332,  1896,   108,   429,   393,   430,
     180,   420,   299,   331,   388,   227,   415,   157,   128,   428,
     165,   430,    78,   427,   393,   984,  1896,   436,   203,   427,
     356,   393,   280,    48,   362,   444,  1850,    93,   211,   173,
     368,   203,  1856,   116,   270,   186,   442,   355,   435,   377,
     378,  1010,   260,   224,   211,   434,   304,   331,    78,  1018,
    1019,   393,   446,   446,   363,   125,   256,   255,   446,   397,
      17,   446,   321,    93,   402,   390,   180,  1036,    48,   407,
     328,   393,   132,     8,   173,   333,   427,   120,   393,     9,
     427,   297,   420,  1052,   298,   343,   424,   167,   195,   347,
     428,  1060,   430,  1983,   319,  1064,   258,   334,   436,   119,
     259,   424,   104,  1072,    48,   171,  1075,   424,   169,   275,
     253,   177,   135,   252,   136,   231,   290,   138,   279,   107,
     384,   274,     7,   110,   213,    64,   394,  1951,   123,  1098,
     318,   318,  1101,   130,    96,    48,   231,   211,  1962,   139,
    1964,   171,  1111,  1112,  1113,    90,   404,   177,   257,   142,
      87,   254,  1121,   185,   196,   214,   414,   427,   430,  2039,
      48,   227,   396,   229,   334,   380,   232,   231,   297,  1138,
     141,  1995,  1996,   231,  1143,   173,  1145,   168,  1147,   412,
     134,   283,  1151,  1152,  1153,  1154,  1155,  1156,  1157,  1158,
     274,   297,   274,    48,   150,   150,     6,   227,   264,   229,
      21,    53,   232,   182,  2094,   128,   317,   167,  2109,   177,
     196,  1290,   460,   537,  1084,   132,  1779,   396,   887,   549,
     893,  2045,  1733,   212,  2114,  2115,   107,   346,    48,  2109,
    2131,   149,   217,   819,   264,   522,   284,   797,  1591,   924,
    1787,  2129,   907,  1978,   505,  2115,   772,   120,  1668,   442,
     533,  2131,  1737,  1379,  1631,   993,     6,   998,  1378,     9,
    1666,  1233,  1459,  1863,  1698,  1230,   332,  1880,  1248,  1719,
    1483,  2095,  2096,  1036,  1318,  2099,  1245,  1738,  1242,  1507,
    1283,  1754,  2106,  1058,  1060,   858,  1255,  1538,  2178,  2179,
    1069,  1538,  2182,  1933,  2184,  1609,  1745,  1938,  2046,  1268,
    1202,  1195,   332,  2204,  1048,  1944,  1275,  1923,  1923,  1434,
     920,   377,   378,  1282,  1923,  1520,   224,   292,  1167,  1253,
    1289,   387,   802,  2147,  2204,   556,   929,  2133,    78,   762,
      56,  2211,  1301,  1795,  2224,  1124,   402,    -1,  1307,    -1,
      -1,    -1,  2085,    93,  1313,    -1,   412,   377,   378,    -1,
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
static const unsigned short yystos[] =
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

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1

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
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
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
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
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
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
  ;}
    break;

  case 3:
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
  ;}
    break;

  case 8:
#line 810 "parser.y"
    { cb_validate_program_environment (current_program); ;}
    break;

  case 9:
#line 811 "parser.y"
    { cb_validate_program_data (current_program); ;}
    break;

  case 11:
#line 819 "parser.y"
    { cb_validate_program_environment (current_program); ;}
    break;

  case 12:
#line 820 "parser.y"
    { cb_validate_program_data (current_program); ;}
    break;

  case 14:
#line 828 "parser.y"
    { cb_validate_program_environment (current_program); ;}
    break;

  case 15:
#line 829 "parser.y"
    { cb_validate_program_data (current_program); ;}
    break;

  case 21:
#line 841 "parser.y"
    {
	char			*s;

	if (CB_LITERAL_P (yyvsp[-1])) {
		s = (char *)(CB_LITERAL (yyvsp[-1])->data);
	} else {
		s = (char *)(CB_NAME (yyvsp[-1]));
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

  case 22:
#line 865 "parser.y"
    {
	char			*s;

	if (CB_LITERAL_P (yyvsp[-1])) {
		s = (char *)(CB_LITERAL (yyvsp[-1])->data);
	} else {
		s = (char *)(CB_NAME (yyvsp[-1]));
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
#line 889 "parser.y"
    {
	char			*s;

	if (CB_LITERAL_P (yyvsp[-1])) {
		s = (char *)(CB_LITERAL (yyvsp[-1])->data);
	} else {
		s = (char *)(CB_NAME (yyvsp[-1]));
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
#line 918 "parser.y"
    {
	current_section = NULL;
	current_paragraph = NULL;
	if (CB_LITERAL_P (yyvsp[-1])) {
		stack_progid[depth] = (char *)(CB_LITERAL (yyvsp[-1])->data);
	} else {
		stack_progid[depth] = (char *)(CB_NAME (yyvsp[-1]));
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
	current_program->program_id = cb_build_program_id (yyvsp[-1], yyvsp[0]);
  ;}
    break;

  case 26:
#line 959 "parser.y"
    {
	cb_error (_("FUNCTION-ID is not yet implemented"));
	current_section = NULL;
	current_paragraph = NULL;
	if (CB_LITERAL_P (yyvsp[-2])) {
		stack_progid[depth] = (char *)(CB_LITERAL (yyvsp[-2])->data);
	} else {
		stack_progid[depth] = (char *)(CB_NAME (yyvsp[-2]));
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
	current_program->program_id = cb_build_program_id (yyvsp[-2], yyvsp[-1]);
	current_program->prog_type = CB_FUNCTION_TYPE;
	current_program->flag_recursive = 1;
	current_program->flag_initial = 1;
  ;}
    break;

  case 29:
#line 1007 "parser.y"
    { yyval = NULL; ;}
    break;

  case 30:
#line 1008 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 33:
#line 1017 "parser.y"
    {
	if (!current_program->nested_level) {
		cb_error (_("COMMON may only be used in a nested program"));
	}
	current_program->flag_common = 1;
  ;}
    break;

  case 34:
#line 1024 "parser.y"
    {
	if (!current_program->nested_level) {
		cb_error (_("COMMON may only be used in a nested program"));
	}
	current_program->flag_common = 1;
  ;}
    break;

  case 36:
#line 1035 "parser.y"
    {
	current_program->flag_initial = 1;
  ;}
    break;

  case 37:
#line 1039 "parser.y"
    {
	current_program->flag_recursive = 1;
	current_program->flag_initial = 1;
  ;}
    break;

  case 41:
#line 1064 "parser.y"
    {
	if (current_program->nested_level) {
		cb_error (_("CONFIGURATION SECTION not allowed in nested programs"));
	}
  ;}
    break;

  case 53:
#line 1099 "parser.y"
    {
	cb_verify (cb_debugging_line, "DEBUGGING MODE");
  ;}
    break;

  case 54:
#line 1105 "parser.y"
    { ;}
    break;

  case 65:
#line 1136 "parser.y"
    {
	cb_verify (cb_memory_size_clause, "MEMORY SIZE");
  ;}
    break;

  case 68:
#line 1148 "parser.y"
    {
	current_program->collating_sequence = yyvsp[0];
  ;}
    break;

  case 69:
#line 1155 "parser.y"
    {
	/* Ignore */
  ;}
    break;

  case 75:
#line 1180 "parser.y"
    {
	current_program->function_spec_list = yyvsp[-1];
  ;}
    break;

  case 76:
#line 1184 "parser.y"
    {
	functions_are_all = 1;
  ;}
    break;

  case 77:
#line 1190 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 78:
#line 1192 "parser.y"
    { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 95:
#line 1232 "parser.y"
    {
	save_tree_1 = lookup_system_name (CB_NAME (yyvsp[-2]));
	if (save_tree_1 == cb_error_node) {
		cb_error_x (yyvsp[-2], _("Unknown system-name '%s'"), CB_NAME (yyvsp[-2]));
	} else if (CB_SYSTEM_NAME(save_tree_1)->token != CB_DEVICE_CONSOLE) {
		cb_error_x (save_tree_1, _("Invalid CRT clause"));
	}
	/* current_program->flag_screen = 1; */
  ;}
    break;

  case 96:
#line 1242 "parser.y"
    {
	save_tree_1 = lookup_system_name (CB_NAME (yyvsp[-2]));
	if (save_tree_1 == cb_error_node) {
		cb_error_x (yyvsp[-2], _("Unknown system-name '%s'"), CB_NAME (yyvsp[-2]));
	} else {
		cb_define (yyvsp[0], save_tree_1);
	}
	save_tree_2 = yyvsp[0];
  ;}
    break;

  case 99:
#line 1257 "parser.y"
    {
	cb_define_switch_name (yyvsp[0], save_tree_1, yyvsp[-3], save_tree_2);
  ;}
    break;

  case 100:
#line 1263 "parser.y"
    { yyval = cb_int1; ;}
    break;

  case 101:
#line 1264 "parser.y"
    { yyval = cb_int0; ;}
    break;

  case 102:
#line 1272 "parser.y"
    {
	save_tree_1 = yyvsp[0];
  ;}
    break;

  case 103:
#line 1276 "parser.y"
    {
	current_program->alphabet_name_list =
		cb_list_add (current_program->alphabet_name_list, yyvsp[0]);
  ;}
    break;

  case 104:
#line 1283 "parser.y"
    { yyval = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_NATIVE); ;}
    break;

  case 105:
#line 1284 "parser.y"
    { yyval = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_1); ;}
    break;

  case 106:
#line 1285 "parser.y"
    { yyval = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_2); ;}
    break;

  case 107:
#line 1286 "parser.y"
    { yyval = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_EBCDIC); ;}
    break;

  case 108:
#line 1288 "parser.y"
    {
	yyval = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_CUSTOM);
	CB_ALPHABET_NAME (yyval)->custom_list = yyvsp[0];
  ;}
    break;

  case 109:
#line 1295 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 110:
#line 1297 "parser.y"
    { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 111:
#line 1301 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 112:
#line 1302 "parser.y"
    { yyval = cb_build_pair (yyvsp[-2], yyvsp[0]); ;}
    break;

  case 113:
#line 1304 "parser.y"
    {
	yyval = cb_list_init (yyvsp[-1]);
	save_tree_2 = yyval;
  ;}
    break;

  case 114:
#line 1309 "parser.y"
    {
	yyval = yyvsp[-1];
  ;}
    break;

  case 117:
#line 1320 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 118:
#line 1321 "parser.y"
    { yyval = cb_space; ;}
    break;

  case 119:
#line 1322 "parser.y"
    { yyval = cb_zero; ;}
    break;

  case 120:
#line 1323 "parser.y"
    { yyval = cb_quote; ;}
    break;

  case 121:
#line 1324 "parser.y"
    { yyval = cb_norm_high; ;}
    break;

  case 122:
#line 1325 "parser.y"
    { yyval = cb_norm_low; ;}
    break;

  case 123:
#line 1329 "parser.y"
    { cb_list_add (save_tree_2, yyvsp[0]); ;}
    break;

  case 124:
#line 1330 "parser.y"
    { cb_list_add (save_tree_2, cb_space); ;}
    break;

  case 125:
#line 1331 "parser.y"
    { cb_list_add (save_tree_2, cb_zero); ;}
    break;

  case 126:
#line 1332 "parser.y"
    { cb_list_add (save_tree_2, cb_quote); ;}
    break;

  case 127:
#line 1333 "parser.y"
    { cb_list_add (save_tree_2, cb_norm_high); ;}
    break;

  case 128:
#line 1334 "parser.y"
    { cb_list_add (save_tree_2, cb_norm_low); ;}
    break;

  case 129:
#line 1342 "parser.y"
    {
	if (yyvsp[0]) {
		current_program->symbolic_list =
			cb_list_add (current_program->symbolic_list, yyvsp[0]);
	}
	PENDING ("SYMBOLIC CHARACTERS");
  ;}
    break;

  case 130:
#line 1353 "parser.y"
    {
	if (cb_list_length (yyvsp[-2]) != cb_list_length (yyvsp[0])) {
		cb_error (_("Invalid SYMBOLIC clause"));
		yyval = NULL;
	} else {
		yyval = NULL;
	}
  ;}
    break;

  case 131:
#line 1364 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 132:
#line 1365 "parser.y"
    { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 133:
#line 1369 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 134:
#line 1370 "parser.y"
    { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 135:
#line 1378 "parser.y"
    {
	current_program->class_name_list =
			cb_list_add (current_program->class_name_list,
			cb_build_class_name (yyvsp[-2], yyvsp[0]));
  ;}
    break;

  case 136:
#line 1386 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 137:
#line 1387 "parser.y"
    { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 138:
#line 1391 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 139:
#line 1393 "parser.y"
    {
	/* if (CB_LITERAL ($1)->data[0] < CB_LITERAL ($3)->data[0]) */
	if (literal_value (yyvsp[-2]) < literal_value (yyvsp[0])) {
		yyval = cb_build_pair (yyvsp[-2], yyvsp[0]);
	} else {
		yyval = cb_build_pair (yyvsp[0], yyvsp[-2]);
	}
  ;}
    break;

  case 140:
#line 1407 "parser.y"
    {
	cb_tree	l;

	l = cb_build_locale_name (yyvsp[-2], yyvsp[0]);
	if (l != cb_error_node) {
		current_program->locale_list =
			cb_list_add (current_program->locale_list, l);
	}
  ;}
    break;

  case 141:
#line 1422 "parser.y"
    {
	unsigned char *s = CB_LITERAL (yyvsp[0])->data;

	if (CB_LITERAL (yyvsp[0])->size != 1) {
		cb_error_x (yyvsp[0], _("Invalid currency sign '%s'"), s);
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
		cb_error_x (yyvsp[0], _("Invalid currency sign '%s'"), s);
		break;
	default:
		break;
	}
	current_program->currency_symbol = s[0];
  ;}
    break;

  case 142:
#line 1489 "parser.y"
    {
	current_program->decimal_point = ',';
	current_program->numeric_separator = '.';
  ;}
    break;

  case 143:
#line 1499 "parser.y"
    { current_program->cursor_pos = yyvsp[0]; ;}
    break;

  case 144:
#line 1506 "parser.y"
    { current_program->crt_status = yyvsp[0]; ;}
    break;

  case 145:
#line 1513 "parser.y"
    {  PENDING ("SCREEN CONTROL"); ;}
    break;

  case 146:
#line 1519 "parser.y"
    {  PENDING ("EVENT STATUS"); ;}
    break;

  case 149:
#line 1531 "parser.y"
    {
	/* hack for MF compatibility */
	if (cb_relaxed_syntax_check) {
		cb_warning (_("INPUT-OUTPUT SECTION header missing - assumed"));
	} else {
		cb_error (_("INPUT-OUTPUT SECTION header missing"));
	}
  ;}
    break;

  case 151:
#line 1540 "parser.y"
    {
	/* hack for MF compatibility */
	if (cb_relaxed_syntax_check) {
		cb_warning (_("INPUT-OUTPUT SECTION header missing - assumed"));
	} else {
		cb_error (_("INPUT-OUTPUT SECTION header missing"));
	}
  ;}
    break;

  case 157:
#line 1565 "parser.y"
    {
	organized_seen = 0;
	if (yyvsp[0] == cb_error_node) {
		YYERROR;
	}

	/* build new file */
	current_file = build_file (yyvsp[0]);
	current_file->optional = CB_INTEGER (yyvsp[-1])->val;

	/* register the file */
	current_program->file_list =
		cb_cons (CB_TREE (current_file), current_program->file_list);
  ;}
    break;

  case 158:
#line 1580 "parser.y"
    {
	validate_file (current_file, yyvsp[-3]);
  ;}
    break;

  case 174:
#line 1610 "parser.y"
    {
	current_file->assign = cb_build_assignment_name (current_file, yyvsp[0]);
  ;}
    break;

  case 175:
#line 1614 "parser.y"
    {
	current_file->fileid_assign = 1;
  ;}
    break;

  case 178:
#line 1621 "parser.y"
    { current_file->organization = COB_ORG_LINE_SEQUENTIAL; ;}
    break;

  case 180:
#line 1626 "parser.y"
    {
	current_file->external_assign = 1;
  ;}
    break;

  case 183:
#line 1635 "parser.y"
    {
	const char	*s;

	s = "$#@DUMMY@#$";
	yyval = cb_build_alphanumeric_literal ((unsigned char *)s, strlen (s));
  ;}
    break;

  case 186:
#line 1652 "parser.y"
    { current_file->access_mode = COB_ACCESS_SEQUENTIAL; ;}
    break;

  case 187:
#line 1653 "parser.y"
    { current_file->access_mode = COB_ACCESS_DYNAMIC; ;}
    break;

  case 188:
#line 1654 "parser.y"
    { current_file->access_mode = COB_ACCESS_RANDOM; ;}
    break;

  case 189:
#line 1662 "parser.y"
    {
	struct cb_alt_key *p;
	struct cb_alt_key *l;

	p = cobc_malloc (sizeof (struct cb_alt_key));
	p->key = yyvsp[-1];
	p->duplicates = CB_INTEGER (yyvsp[0])->val;
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

  case 190:
#line 1687 "parser.y"
    {
	PENDING ("COLLATING SEQUENCE");
  ;}
    break;

  case 191:
#line 1697 "parser.y"
    {
	current_file->file_status = yyvsp[-1];
	if (yyvsp[0]) {
		PENDING ("2nd FILE STATUS");
	}
  ;}
    break;

  case 196:
#line 1718 "parser.y"
    { current_file->lock_mode = COB_LOCK_MANUAL; ;}
    break;

  case 197:
#line 1719 "parser.y"
    { current_file->lock_mode = COB_LOCK_AUTOMATIC; ;}
    break;

  case 198:
#line 1720 "parser.y"
    { current_file->lock_mode = COB_LOCK_EXCLUSIVE; ;}
    break;

  case 201:
#line 1726 "parser.y"
    {
	current_file->lock_mode |= COB_LOCK_MULTIPLE;
  ;}
    break;

  case 202:
#line 1729 "parser.y"
    { PENDING ("WITH ROLLBACK"); ;}
    break;

  case 207:
#line 1746 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_INDEXED;
		organized_seen = 1;
	}
  ;}
    break;

  case 208:
#line 1755 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_SEQUENTIAL;
		organized_seen = 1;
	}
  ;}
    break;

  case 209:
#line 1764 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_RELATIVE;
		organized_seen = 1;
	}
  ;}
    break;

  case 210:
#line 1773 "parser.y"
    {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_LINE_SEQUENTIAL;
		organized_seen = 1;
	}
  ;}
    break;

  case 211:
#line 1788 "parser.y"
    {
	cb_verify (cb_padding_character_clause, "PADDING CHARACTER");
  ;}
    break;

  case 212:
#line 1797 "parser.y"
    { /* ignored */ ;}
    break;

  case 213:
#line 1805 "parser.y"
    {
	current_file->key = yyvsp[0];
  ;}
    break;

  case 214:
#line 1811 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 215:
#line 1812 "parser.y"
    { PENDING ("SPLIT KEYS"); ;}
    break;

  case 216:
#line 1813 "parser.y"
    { PENDING ("SPLIT KEYS"); ;}
    break;

  case 217:
#line 1819 "parser.y"
    { current_file->key = yyvsp[0]; ;}
    break;

  case 218:
#line 1826 "parser.y"
    { /* ignored */ ;}
    break;

  case 219:
#line 1833 "parser.y"
    { current_file->sharing = yyvsp[0]; ;}
    break;

  case 220:
#line 1837 "parser.y"
    { yyval = NULL; PENDING ("SHARING ALL OTHER"); ;}
    break;

  case 221:
#line 1838 "parser.y"
    { yyval = cb_int1; ;}
    break;

  case 222:
#line 1839 "parser.y"
    { yyval = cb_int0; ;}
    break;

  case 231:
#line 1869 "parser.y"
    {
	cb_tree l;

	switch (CB_INTEGER (yyvsp[-3])->val) {
	case 0:
		/* SAME AREA */
		break;
	case 1:
		/* SAME RECORD */
		for (l = yyvsp[0]; l; l = CB_CHAIN (l)) {
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

  case 232:
#line 1893 "parser.y"
    { yyval = cb_int0; ;}
    break;

  case 233:
#line 1894 "parser.y"
    { yyval = cb_int1; ;}
    break;

  case 234:
#line 1895 "parser.y"
    { yyval = cb_int2; ;}
    break;

  case 235:
#line 1896 "parser.y"
    { yyval = cb_int2; ;}
    break;

  case 236:
#line 1903 "parser.y"
    {
	cb_verify (cb_multiple_file_tape_clause, "MULTIPLE FILE TAPE");
  ;}
    break;

  case 239:
#line 1914 "parser.y"
    { ;}
    break;

  case 245:
#line 1942 "parser.y"
    { current_storage = CB_STORAGE_FILE; ;}
    break;

  case 247:
#line 1945 "parser.y"
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

  case 251:
#line 1964 "parser.y"
    {
	if (yyvsp[0] && yyvsp[0] != cb_error_node) {
		finalize_file (current_file, CB_FIELD (yyvsp[0]));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 252:
#line 1976 "parser.y"
    {
	if (yyvsp[0] && yyvsp[0] != cb_error_node) {
		finalize_file (current_file, CB_FIELD (yyvsp[0]));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  ;}
    break;

  case 254:
#line 1987 "parser.y"
    { yyval = cb_int0; ;}
    break;

  case 255:
#line 1988 "parser.y"
    { yyval = cb_int1; ;}
    break;

  case 256:
#line 1998 "parser.y"
    {
	if (yyvsp[0] == cb_error_node) {
		YYERROR;
	}

	current_file = CB_FILE (cb_ref (yyvsp[0]));
	if (yyvsp[-1] == cb_int1) {
		current_file->organization = COB_ORG_SORT;
	}
  ;}
    break;

  case 257:
#line 2009 "parser.y"
    {
	/* Shut up bison */
	dummy_tree = yyvsp[-2];
  ;}
    break;

  case 260:
#line 2021 "parser.y"
    {
	if (current_file->global) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->external = 1;
  ;}
    break;

  case 261:
#line 2028 "parser.y"
    {
	if (current_file->external) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->global = 1;
  ;}
    break;

  case 271:
#line 2050 "parser.y"
    { /* ignored */ ;}
    break;

  case 275:
#line 2060 "parser.y"
    {
	if (current_file->organization == COB_ORG_LINE_SEQUENTIAL) {
		cb_warning (_("RECORD clause ignored for LINE SEQUENTIAL"));
	} else {
		current_file->record_max = cb_get_int (yyvsp[-1]);
		if (current_file->record_max < 1)  {
			current_file->record_max = 1;
			cb_error (_("RECORD clause invalid"));
		}
	}
  ;}
    break;

  case 276:
#line 2072 "parser.y"
    {
	int	error_ind = 0;

	if (current_file->organization == COB_ORG_LINE_SEQUENTIAL) {
		cb_warning (_("RECORD clause ignored for LINE SEQUENTIAL"));
	} else {
		current_file->record_min = cb_get_int (yyvsp[-3]);
		current_file->record_max = cb_get_int (yyvsp[-1]);
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

  case 277:
#line 2098 "parser.y"
    {
	int	error_ind = 0;

	current_file->record_min = yyvsp[-3] ? cb_get_int (yyvsp[-3]) : 0;
	current_file->record_max = yyvsp[-2] ? cb_get_int (yyvsp[-2]) : 0;
	if (yyvsp[-3] && current_file->record_min < 0)  {
		current_file->record_min = 0;
		error_ind = 1;
	}
	if (yyvsp[-2] && current_file->record_max < 1)  {
		current_file->record_max = 1;
		error_ind = 1;
	}
	if ((yyvsp[-3] || yyvsp[-2]) && current_file->record_max <= current_file->record_min)  {
		error_ind = 1;
	}
	if (error_ind) {
		cb_error (_("RECORD clause invalid"));
	}
  ;}
    break;

  case 279:
#line 2122 "parser.y"
    {
	current_file->record_depending = yyvsp[0];
  ;}
    break;

  case 280:
#line 2128 "parser.y"
    { yyval = NULL; ;}
    break;

  case 281:
#line 2129 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 282:
#line 2133 "parser.y"
    { yyval = NULL; ;}
    break;

  case 283:
#line 2134 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 284:
#line 2142 "parser.y"
    {
	cb_verify (cb_label_records_clause, "LABEL RECORDS");
  ;}
    break;

  case 287:
#line 2157 "parser.y"
    {
	cb_verify (cb_value_of_clause, "VALUE OF");
  ;}
    break;

  case 288:
#line 2161 "parser.y"
    {
	if (!current_file->assign) {
		current_file->assign = cb_build_assignment_name (current_file, yyvsp[0]);
	}
  ;}
    break;

  case 291:
#line 2177 "parser.y"
    {
	cb_verify (cb_data_records_clause, "DATA RECORDS");
  ;}
    break;

  case 292:
#line 2188 "parser.y"
    {
	if (current_file->organization != COB_ORG_LINE_SEQUENTIAL
	    && current_file->organization != COB_ORG_SEQUENTIAL) {
		cb_error (_("LINAGE clause with wrong file type"));
		yyval = cb_error_node;
	} else {
		current_file->linage = yyvsp[-2];
		current_file->organization = COB_ORG_LINE_SEQUENTIAL;
		if (current_linage == 0) {
			linage_file = current_file;
		}
		current_linage++;
	}
  ;}
    break;

  case 298:
#line 2216 "parser.y"
    {
	current_file->latfoot = yyvsp[-1];
  ;}
    break;

  case 299:
#line 2223 "parser.y"
    {
	current_file->lattop = yyvsp[-1];
  ;}
    break;

  case 300:
#line 2230 "parser.y"
    {
	current_file->latbot = yyvsp[0];
  ;}
    break;

  case 301:
#line 2239 "parser.y"
    { /* ignore */ ;}
    break;

  case 302:
#line 2247 "parser.y"
    {
	if (yyvsp[0] != cb_error_node) {
		cb_tree x;

		x = cb_ref (yyvsp[0]);
		if (!CB_ALPHABET_NAME_P (x)) {
			cb_error_x (yyvsp[0], _("Alphabet-name is expected '%s'"), cb_name (yyvsp[0]));
		} else if (CB_ALPHABET_NAME (x)->custom_list) {
			PENDING ("CODE-SET");
		}
	}
  ;}
    break;

  case 303:
#line 2265 "parser.y"
    {
	cb_warning (_("file descriptor REPORT IS"));
  ;}
    break;

  case 304:
#line 2269 "parser.y"
    {
	cb_warning (_("file descriptor REPORTS ARE"));
  ;}
    break;

  case 306:
#line 2280 "parser.y"
    { current_storage = CB_STORAGE_WORKING; ;}
    break;

  case 307:
#line 2282 "parser.y"
    {
	if (yyvsp[0]) {
		current_program->working_storage =
			cb_field_add (current_program->working_storage, CB_FIELD (yyvsp[0]));
	}
  ;}
    break;

  case 308:
#line 2291 "parser.y"
    { yyval = NULL; ;}
    break;

  case 309:
#line 2292 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 310:
#line 2296 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 311:
#line 2302 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	yyval = CB_TREE (description_field);
  ;}
    break;

  case 316:
#line 2322 "parser.y"
    {
	cb_tree x;

	x = cb_build_field_tree (yyvsp[-1], yyvsp[0], current_field, current_storage, current_file);
	if (x == cb_error_node) {
		YYERROR;
	} else {
		current_field = CB_FIELD (x);
	}
  ;}
    break;

  case 317:
#line 2333 "parser.y"
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

  case 319:
#line 2358 "parser.y"
    {
	yyval = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 320:
#line 2364 "parser.y"
    {
	yyval = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  ;}
    break;

  case 321:
#line 2370 "parser.y"
    {
	yyval = yyvsp[0];
	qualifier = yyvsp[0];
	non_const_word = 0;
  ;}
    break;

  case 322:
#line 2379 "parser.y"
    {
	yyval = yyvsp[0];
	qualifier = yyvsp[0];
	non_const_word = 0;
  ;}
    break;

  case 324:
#line 2388 "parser.y"
    {
	current_field->flag_is_global = 1;
	cb_error (_("CONSTANT with GLOBAL clause is not yet supported"));
  ;}
    break;

  case 325:
#line 2395 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 326:
#line 2396 "parser.y"
    { yyval = cb_build_const_length (yyvsp[0]); ;}
    break;

  case 327:
#line 2397 "parser.y"
    { yyval = cb_build_const_length (yyvsp[0]); ;}
    break;

  case 328:
#line 2402 "parser.y"
    {
	cb_tree x;
	int	level;

	level = cb_get_level (yyvsp[-5]);
	if (level && level != 1) {
		cb_error (_("CONSTANT item not at 01 level"));
	}
	x = cb_build_constant (yyvsp[-4], yyvsp[0]);
	CB_FIELD (x)->flag_item_78 = 1;
	CB_FIELD (x)->level = 1;
	cb_needs_01 = 1;
	/* Ignore return value */
	cb_validate_78_item (CB_FIELD (x));
  ;}
    break;

  case 329:
#line 2421 "parser.y"
    {
	/* required to check redefines */
	yyval = NULL;
  ;}
    break;

  case 330:
#line 2427 "parser.y"
    {
	/* required to check redefines */
	yyval = cb_true;
  ;}
    break;

  case 345:
#line 2455 "parser.y"
    {
	if (yyvsp[-2] != NULL) {
		/* hack for MF compatibility */
		if (cb_relaxed_syntax_check) {
			cb_warning_x (yyvsp[0], _("REDEFINES clause should follow entry-name"));
		} else {
			cb_error_x (yyvsp[0], _("REDEFINES clause must follow entry-name"));
		}
	}

	current_field->redefines = cb_resolve_redefines (current_field, yyvsp[0]);
	if (current_field->redefines == NULL) {
		YYERROR;
	}
  ;}
    break;

  case 346:
#line 2477 "parser.y"
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

  case 347:
#line 2498 "parser.y"
    { current_field->ename = NULL; ;}
    break;

  case 348:
#line 2500 "parser.y"
    {
	struct cb_field *x;

	x = CB_FIELD(cb_build_field (cb_build_reference ((char *)(CB_LITERAL (yyvsp[0])->data))));
	current_field->ename = x->name;
 ;}
    break;

  case 349:
#line 2512 "parser.y"
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

  case 350:
#line 2531 "parser.y"
    { current_field->pic = CB_PICTURE (yyvsp[0]); ;}
    break;

  case 353:
#line 2543 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 354:
#line 2544 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 355:
#line 2545 "parser.y"
    { current_field->usage = CB_USAGE_FLOAT; ;}
    break;

  case 356:
#line 2546 "parser.y"
    { current_field->usage = CB_USAGE_DOUBLE; ;}
    break;

  case 357:
#line 2547 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 358:
#line 2548 "parser.y"
    { current_field->usage = CB_USAGE_BINARY; ;}
    break;

  case 359:
#line 2549 "parser.y"
    { current_field->usage = CB_USAGE_COMP_5; ;}
    break;

  case 360:
#line 2550 "parser.y"
    { current_field->usage = CB_USAGE_COMP_X; ;}
    break;

  case 361:
#line 2551 "parser.y"
    { current_field->usage = CB_USAGE_DISPLAY; ;}
    break;

  case 362:
#line 2552 "parser.y"
    { current_field->usage = CB_USAGE_INDEX; ;}
    break;

  case 363:
#line 2553 "parser.y"
    { current_field->usage = CB_USAGE_PACKED; ;}
    break;

  case 364:
#line 2555 "parser.y"
    {
	current_field->usage = CB_USAGE_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 365:
#line 2560 "parser.y"
    {
	current_field->usage = CB_USAGE_PROGRAM_POINTER;
	current_field->flag_is_pointer = 1;
  ;}
    break;

  case 366:
#line 2564 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 367:
#line 2565 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 368:
#line 2566 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 369:
#line 2567 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 370:
#line 2568 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 371:
#line 2569 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 372:
#line 2570 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 373:
#line 2571 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_CHAR; ;}
    break;

  case 374:
#line 2572 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_CHAR; ;}
    break;

  case 375:
#line 2573 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 376:
#line 2574 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_SHORT; ;}
    break;

  case 377:
#line 2575 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_SHORT; ;}
    break;

  case 378:
#line 2576 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 379:
#line 2577 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_INT; ;}
    break;

  case 380:
#line 2578 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_INT; ;}
    break;

  case 381:
#line 2579 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 382:
#line 2580 "parser.y"
    { current_field->usage = CB_USAGE_UNSIGNED_LONG; ;}
    break;

  case 383:
#line 2581 "parser.y"
    { current_field->usage = CB_USAGE_SIGNED_LONG; ;}
    break;

  case 384:
#line 2583 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  ;}
    break;

  case 385:
#line 2591 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_UNSIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_UNSIGNED_LONG;
	}
  ;}
    break;

  case 386:
#line 2599 "parser.y"
    {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  ;}
    break;

  case 387:
#line 2606 "parser.y"
    { PENDING ("USAGE NATIONAL");;}
    break;

  case 388:
#line 2614 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER (yyvsp[0])->val;
	current_field->flag_sign_leading  = 1;
  ;}
    break;

  case 389:
#line 2619 "parser.y"
    {
	current_field->flag_sign_separate = CB_INTEGER (yyvsp[0])->val;
	current_field->flag_sign_leading  = 0;
  ;}
    break;

  case 390:
#line 2631 "parser.y"
    {
	if (current_field->occurs_depending && !(yyvsp[-4])) {
		cb_verify (cb_odo_without_to, "ODO without TO clause");
	}
	current_field->occurs_min = yyvsp[-4] ? cb_get_int (yyvsp[-5]) : 1;
	current_field->occurs_max = yyvsp[-4] ? cb_get_int (yyvsp[-4]) : cb_get_int (yyvsp[-5]);
	current_field->indexes++;
	if (current_field->indexes > COB_MAX_SUBSCRIPTS) {
		cb_error (_("Maximum OCCURS depth exceeded"));
	}
	current_field->flag_occurs = 1;
  ;}
    break;

  case 391:
#line 2646 "parser.y"
    { yyval = NULL; ;}
    break;

  case 392:
#line 2647 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 394:
#line 2652 "parser.y"
    {
	current_field->occurs_depending = yyvsp[0];
  ;}
    break;

  case 395:
#line 2659 "parser.y"
    {
	if (yyvsp[0]) {
		cb_tree		l;
		struct cb_key	*keys;
		int		i;
		int		nkeys;

		l = yyvsp[0];
		nkeys = cb_list_length (yyvsp[0]);
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

  case 396:
#line 2682 "parser.y"
    { yyval = NULL; ;}
    break;

  case 397:
#line 2685 "parser.y"
    {
	cb_tree l;

	for (l = yyvsp[0]; l; l = CB_CHAIN (l)) {
		CB_PURPOSE (l) = yyvsp[-3];
		if (qualifier && !CB_REFERENCE(CB_VALUE(l))->chain &&
		    strcasecmp (CB_NAME(CB_VALUE(l)), CB_NAME(qualifier))) {
			CB_REFERENCE(CB_VALUE(l))->chain = qualifier;
		}
	}
	yyval = cb_list_append (yyvsp[-4], yyvsp[0]);
  ;}
    break;

  case 398:
#line 2700 "parser.y"
    { yyval = cb_int (COB_ASCENDING); ;}
    break;

  case 399:
#line 2701 "parser.y"
    { yyval = cb_int (COB_DESCENDING); ;}
    break;

  case 401:
#line 2706 "parser.y"
    {
	current_field->index_list = yyvsp[0];
  ;}
    break;

  case 402:
#line 2712 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 403:
#line 2714 "parser.y"
    { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 404:
#line 2719 "parser.y"
    {
	yyval = cb_build_index (yyvsp[0], cb_int1, 1, current_field);
  ;}
    break;

  case 405:
#line 2728 "parser.y"
    { current_field->flag_justified = 1; ;}
    break;

  case 406:
#line 2735 "parser.y"
    { current_field->flag_synchronized = 1; ;}
    break;

  case 410:
#line 2747 "parser.y"
    { current_field->flag_blank_zero = 1; ;}
    break;

  case 411:
#line 2755 "parser.y"
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

  case 412:
#line 2779 "parser.y"
    { current_field->values = yyvsp[0]; ;}
    break;

  case 414:
#line 2784 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 415:
#line 2785 "parser.y"
    { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 416:
#line 2789 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 417:
#line 2790 "parser.y"
    { yyval = cb_build_pair (yyvsp[-2], yyvsp[0]); ;}
    break;

  case 419:
#line 2795 "parser.y"
    {
	if (current_field->level != 88) {
		cb_error (_("FALSE clause only allowed for 88 level"));
	}
	current_field->false_88 = cb_list_init (yyvsp[0]);
  ;}
    break;

  case 420:
#line 2808 "parser.y"
    {
	if (cb_ref (yyvsp[0]) != cb_error_node) {
		if (CB_FIELD (cb_ref (yyvsp[0]))->level == 01 ||
		    CB_FIELD (cb_ref (yyvsp[0]))->level > 50) {
			cb_error (_("RENAMES may not reference a level 01 or > 50"));
		} else {
			current_field->redefines = CB_FIELD (cb_ref (yyvsp[0]));
			current_field->pic = current_field->redefines->pic;
		}
	}
  ;}
    break;

  case 421:
#line 2820 "parser.y"
    {
	if (cb_ref (yyvsp[-2]) != cb_error_node && cb_ref (yyvsp[0]) != cb_error_node) {
		if (CB_FIELD (cb_ref (yyvsp[-2]))->level == 01 ||
		    CB_FIELD (cb_ref (yyvsp[-2]))->level > 50) {
			cb_error (_("RENAMES may not reference a level 01 or > 50"));
		} else if (CB_FIELD (cb_ref (yyvsp[0]))->level == 01 ||
		    CB_FIELD (cb_ref (yyvsp[0]))->level > 50) {
			cb_error (_("RENAMES may not reference a level 01 or > 50"));
		} else {
			current_field->redefines = CB_FIELD (cb_ref (yyvsp[-2]));
			current_field->rename_thru = CB_FIELD (cb_ref (yyvsp[0]));
		}
	}
  ;}
    break;

  case 422:
#line 2840 "parser.y"
    {
	if (current_field->flag_item_based) {
		cb_error (_("BASED and ANY LENGTH are mutually exclusive"));
	} else {
		current_field->flag_any_length = 1;
	}
  ;}
    break;

  case 424:
#line 2855 "parser.y"
    {
	current_storage = CB_STORAGE_LOCAL;
	if (current_program->nested_level) {
		cb_error (_("LOCAL-STORAGE not allowed in nested programs"));
	}
  ;}
    break;

  case 425:
#line 2862 "parser.y"
    {
	if (yyvsp[0]) {
		current_program->local_storage = CB_FIELD (yyvsp[0]);
	}
  ;}
    break;

  case 427:
#line 2875 "parser.y"
    { current_storage = CB_STORAGE_LINKAGE; ;}
    break;

  case 428:
#line 2877 "parser.y"
    {
	if (yyvsp[0]) {
		current_program->linkage_storage = CB_FIELD (yyvsp[0]);
	}
  ;}
    break;

  case 430:
#line 2890 "parser.y"
    {
	cb_error (_("REPORT SECTION not supported"));
	current_storage = CB_STORAGE_REPORT;
  ;}
    break;

  case 437:
#line 2923 "parser.y"
    {
	cb_warning (_("Report description using defaults"));
  ;}
    break;

  case 439:
#line 2931 "parser.y"
    {
	cb_error (_("GLOBAL is not allowed with RD"));
  ;}
    break;

  case 471:
#line 3011 "parser.y"
    { cb_warning (_("looking for Report line TYPE")); ;}
    break;

  case 522:
#line 3116 "parser.y"
    { current_storage = CB_STORAGE_SCREEN; ;}
    break;

  case 523:
#line 3117 "parser.y"
    {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  ;}
    break;

  case 524:
#line 3123 "parser.y"
    {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	current_program->screen_storage = description_field;
	current_program->flag_screen = 1;
  ;}
    break;

  case 530:
#line 3147 "parser.y"
    {
	cb_tree x;

	x = cb_build_field_tree (yyvsp[-1], yyvsp[0], current_field, current_storage, current_file);
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

  case 531:
#line 3163 "parser.y"
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

  case 534:
#line 3187 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 535:
#line 3188 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 536:
#line 3189 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BELL; ;}
    break;

  case 537:
#line 3190 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_BLINK; ;}
    break;

  case 538:
#line 3191 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 539:
#line 3192 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 540:
#line 3193 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 541:
#line 3194 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 542:
#line 3195 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REVERSE; ;}
    break;

  case 543:
#line 3196 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 544:
#line 3197 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_OVERLINE; ;}
    break;

  case 545:
#line 3198 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_AUTO; ;}
    break;

  case 546:
#line 3199 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_SECURE; ;}
    break;

  case 547:
#line 3200 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_REQUIRED; ;}
    break;

  case 548:
#line 3201 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_FULL; ;}
    break;

  case 549:
#line 3202 "parser.y"
    { current_field->screen_flag |= COB_SCREEN_PROMPT; ;}
    break;

  case 550:
#line 3204 "parser.y"
    {
	current_field->screen_line = yyvsp[0];
  ;}
    break;

  case 551:
#line 3208 "parser.y"
    {
	current_field->screen_column = yyvsp[0];
  ;}
    break;

  case 552:
#line 3212 "parser.y"
    {
	current_field->screen_foreg = yyvsp[0];
  ;}
    break;

  case 553:
#line 3216 "parser.y"
    {
	current_field->screen_backg = yyvsp[0];
  ;}
    break;

  case 561:
#line 3227 "parser.y"
    {
	current_field->screen_from = yyvsp[0];
	current_field->screen_to = yyvsp[0];
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 562:
#line 3234 "parser.y"
    {
	current_field->screen_from = yyvsp[0];
  ;}
    break;

  case 563:
#line 3238 "parser.y"
    {
	current_field->screen_to = yyvsp[0];
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  ;}
    break;

  case 564:
#line 3247 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 565:
#line 3251 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 566:
#line 3255 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  ;}
    break;

  case 567:
#line 3259 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 568:
#line 3263 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  ;}
    break;

  case 569:
#line 3270 "parser.y"
    {
	/* Nothing */
  ;}
    break;

  case 570:
#line 3274 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 571:
#line 3278 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  ;}
    break;

  case 572:
#line 3282 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 573:
#line 3286 "parser.y"
    {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  ;}
    break;

  case 574:
#line 3294 "parser.y"
    {
	current_field->occurs_max = cb_get_int (yyvsp[-1]);
	current_field->occurs_min = current_field->occurs_max;
	current_field->indexes++;
	current_field->flag_occurs = 1;
  ;}
    break;

  case 576:
#line 3308 "parser.y"
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

  case 577:
#line 3318 "parser.y"
    {
	if (current_program->flag_main && !current_program->flag_chained && yyvsp[-4]) {
		cb_error (_("Executable program requested but PROCEDURE/ENTRY has USING clause"));
	}
	emit_entry (current_program->program_id, 0, yyvsp[-4]); /* main entry point */
	if (current_program->source_name) {
		emit_entry (current_program->source_name, 1, yyvsp[-4]);
	}
  ;}
    break;

  case 578:
#line 3328 "parser.y"
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

  case 579:
#line 3345 "parser.y"
    { yyval = NULL; ;}
    break;

  case 580:
#line 3347 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 581:
#line 3351 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 582:
#line 3353 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	current_program->flag_chained = 1;
  ;}
    break;

  case 583:
#line 3357 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 584:
#line 3361 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 585:
#line 3363 "parser.y"
    { yyval = cb_list_append (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 586:
#line 3368 "parser.y"
    {
	yyval = cb_build_pair (cb_int (call_mode), cb_build_identifier (yyvsp[0]));
	CB_SIZES (yyval) = size_mode;
  ;}
    break;

  case 588:
#line 3377 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 589:
#line 3381 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 591:
#line 3393 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_AUTO;
	}
  ;}
    break;

  case 592:
#line 3401 "parser.y"
    {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_4;
	}
  ;}
    break;

  case 593:
#line 3409 "parser.y"
    {
	unsigned char *s = CB_LITERAL (yyvsp[0])->data;

	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else if (CB_LITERAL (yyvsp[0])->size != 1) {
		cb_error_x (yyvsp[0], _("Invalid value for SIZE"));
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
			cb_error_x (yyvsp[0], _("Invalid value for SIZE"));
			break;
		}
	}
  ;}
    break;

  case 594:
#line 3438 "parser.y"
    {
	unsigned char *s = CB_LITERAL (yyvsp[0])->data;

	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else if (CB_LITERAL (yyvsp[0])->size != 1) {
		cb_error_x (yyvsp[0], _("Invalid value for SIZE"));
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
			cb_error_x (yyvsp[0], _("Invalid value for SIZE"));
			break;
		}
	}
  ;}
    break;

  case 596:
#line 3471 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OPTIONAL only allowed for BY REFERENCE items"));
	}
  ;}
    break;

  case 597:
#line 3480 "parser.y"
    {
	if (current_program->prog_type == CB_FUNCTION_TYPE) {
		cb_error (_("RETURNING clause is required for a FUNCTION"));
	}
  ;}
    break;

  case 598:
#line 3486 "parser.y"
    {
	if (cb_ref (yyvsp[0]) != cb_error_node) {
		current_program->returning = yyvsp[0];
		if (cb_field (yyvsp[0])->storage != CB_STORAGE_LINKAGE) {
			cb_error (_("RETURNING item is not defined in LINKAGE SECTION"));
		}
	}
  ;}
    break;

  case 600:
#line 3497 "parser.y"
    { in_declaratives = 1; ;}
    break;

  case 601:
#line 3500 "parser.y"
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

  case 607:
#line 3533 "parser.y"
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

  case 608:
#line 3549 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 609:
#line 3553 "parser.y"
    {
	/* check_unreached = 0; */
  ;}
    break;

  case 610:
#line 3565 "parser.y"
    {
	non_const_word = 0;
	check_unreached = 0;
	if (yyvsp[-3] == cb_error_node) {
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
	current_section = CB_LABEL (cb_build_label (yyvsp[-3], NULL));
	current_section->is_section = 1;
	current_paragraph = NULL;
	emit_statement (CB_TREE (current_section));
  ;}
    break;

  case 611:
#line 3596 "parser.y"
    {
	cb_tree label;

	non_const_word = 0;
	check_unreached = 0;
	yyval = cb_build_section_name (yyvsp[-1], 1);
	/* if ($1 == cb_error_node) */
	if (yyval == cb_error_node) {
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
	current_paragraph = CB_LABEL (cb_build_label (yyval, current_section));
	if (current_section) {
		current_section->children =
			cb_cons (CB_TREE (current_paragraph), current_section->children);
	}
	emit_statement (CB_TREE (current_paragraph));
  ;}
    break;

  case 612:
#line 3633 "parser.y"
    {
	non_const_word = 0;
	check_unreached = 0;
	if (yyvsp[0] != cb_error_node) {
		cb_error_x (yyvsp[0], _("Unknown statement '%s'"), CB_NAME (yyvsp[0]));
	}
	YYERROR;
  ;}
    break;

  case 613:
#line 3644 "parser.y"
    { yyval = cb_build_section_name (yyvsp[0], 0); ;}
    break;

  case 615:
#line 3648 "parser.y"
    { /* ignore */ ;}
    break;

  case 616:
#line 3657 "parser.y"
    {
	yyval = current_program->exec_list;
	current_program->exec_list = NULL;
  ;}
    break;

  case 617:
#line 3661 "parser.y"
    {
	yyval = CB_TREE (current_statement);
	current_statement = NULL;
  ;}
    break;

  case 618:
#line 3666 "parser.y"
    {
	yyval = cb_list_reverse (current_program->exec_list);
	current_program->exec_list = yyvsp[-2];
	current_statement = CB_STATEMENT (yyvsp[-1]);
  ;}
    break;

  case 619:
#line 3674 "parser.y"
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

  case 670:
#line 3745 "parser.y"
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

  case 671:
#line 3767 "parser.y"
    {
	BEGIN_STATEMENT ("ACCEPT", TERM_ACCEPT);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 673:
#line 3780 "parser.y"
    {
	cb_emit_accept (yyvsp[-3], yyvsp[-2], fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 674:
#line 3784 "parser.y"
    {
	PENDING ("ACCEPT .. FROM ESCAPE KEY");
  ;}
    break;

  case 675:
#line 3788 "parser.y"
    {
	cb_emit_accept_line_or_col (yyvsp[-2], 0);
  ;}
    break;

  case 676:
#line 3792 "parser.y"
    {
	cb_emit_accept_line_or_col (yyvsp[-2], 1);
  ;}
    break;

  case 677:
#line 3796 "parser.y"
    {
	cb_emit_accept_date (yyvsp[-2]);
  ;}
    break;

  case 678:
#line 3800 "parser.y"
    {
	cb_emit_accept_date_yyyymmdd (yyvsp[-3]);
  ;}
    break;

  case 679:
#line 3804 "parser.y"
    {
	cb_emit_accept_day (yyvsp[-2]);
  ;}
    break;

  case 680:
#line 3808 "parser.y"
    {
	cb_emit_accept_day_yyyyddd (yyvsp[-3]);
  ;}
    break;

  case 681:
#line 3812 "parser.y"
    {
	cb_emit_accept_day_of_week (yyvsp[-2]);
  ;}
    break;

  case 682:
#line 3816 "parser.y"
    {
	cb_emit_accept_time (yyvsp[-2]);
  ;}
    break;

  case 683:
#line 3820 "parser.y"
    {
	cb_emit_accept_command_line (yyvsp[-2]);
  ;}
    break;

  case 684:
#line 3824 "parser.y"
    {
	cb_emit_accept_environment (yyvsp[-3]);
  ;}
    break;

  case 685:
#line 3828 "parser.y"
    { 
	cb_emit_get_environment (yyvsp[-1], yyvsp[-4]);
  ;}
    break;

  case 686:
#line 3832 "parser.y"
    {
	cb_emit_accept_arg_number (yyvsp[-2]);
  ;}
    break;

  case 687:
#line 3836 "parser.y"
    {
	cb_emit_accept_arg_value (yyvsp[-3]);
  ;}
    break;

  case 688:
#line 3840 "parser.y"
    {
	cb_emit_accept_mnemonic (yyvsp[-2], yyvsp[0]);
  ;}
    break;

  case 689:
#line 3844 "parser.y"
    {
	cb_emit_accept_name (yyvsp[-2], yyvsp[0]);
  ;}
    break;

  case 690:
#line 3850 "parser.y"
    { yyval = NULL; ;}
    break;

  case 691:
#line 3851 "parser.y"
    { yyval = cb_build_pair (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 692:
#line 3852 "parser.y"
    { yyval = cb_build_pair (yyvsp[0], yyvsp[-1]); ;}
    break;

  case 693:
#line 3853 "parser.y"
    { yyval = cb_build_pair (yyvsp[0], NULL); ;}
    break;

  case 694:
#line 3854 "parser.y"
    { yyval = cb_build_pair (NULL, yyvsp[0]); ;}
    break;

  case 695:
#line 3855 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 696:
#line 3859 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 697:
#line 3863 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 698:
#line 3864 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 703:
#line 3877 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 704:
#line 3878 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 705:
#line 3879 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 706:
#line 3880 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 707:
#line 3881 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 708:
#line 3882 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 709:
#line 3883 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 710:
#line 3885 "parser.y"
    {
	fgc = yyvsp[0];
  ;}
    break;

  case 711:
#line 3889 "parser.y"
    {
	bgc = yyvsp[0];
  ;}
    break;

  case 712:
#line 3893 "parser.y"
    {
	scroll = yyvsp[0];
  ;}
    break;

  case 713:
#line 3897 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = yyvsp[0];
  ;}
    break;

  case 714:
#line 3901 "parser.y"
    { dispattrs |= COB_SCREEN_AUTO; ;}
    break;

  case 715:
#line 3902 "parser.y"
    { dispattrs |= COB_SCREEN_FULL; ;}
    break;

  case 716:
#line 3903 "parser.y"
    { dispattrs |= COB_SCREEN_REQUIRED; ;}
    break;

  case 717:
#line 3904 "parser.y"
    { dispattrs |= COB_SCREEN_SECURE; ;}
    break;

  case 718:
#line 3905 "parser.y"
    { dispattrs |= COB_SCREEN_UPDATE; ;}
    break;

  case 719:
#line 3906 "parser.y"
    { dispattrs |= COB_SCREEN_PROMPT; ;}
    break;

  case 720:
#line 3910 "parser.y"
    { terminator_warning (TERM_ACCEPT); ;}
    break;

  case 721:
#line 3911 "parser.y"
    { terminator_clear (TERM_ACCEPT); ;}
    break;

  case 722:
#line 3920 "parser.y"
    { BEGIN_STATEMENT ("ADD", TERM_ADD); ;}
    break;

  case 724:
#line 3927 "parser.y"
    {
	cb_emit_arithmetic (yyvsp[-1], '+', cb_build_binary_list (yyvsp[-3], '+'));
  ;}
    break;

  case 725:
#line 3931 "parser.y"
    {
	cb_emit_arithmetic (yyvsp[-1], 0, cb_build_binary_list (yyvsp[-4], '+'));
  ;}
    break;

  case 726:
#line 3935 "parser.y"
    {
	cb_emit_corresponding (cb_build_add, yyvsp[-2], yyvsp[-4], yyvsp[-1]);
  ;}
    break;

  case 728:
#line 3941 "parser.y"
    { cb_list_add (yyvsp[-2], yyvsp[0]); ;}
    break;

  case 729:
#line 3945 "parser.y"
    { terminator_warning (TERM_ADD); ;}
    break;

  case 730:
#line 3946 "parser.y"
    { terminator_clear (TERM_ADD); ;}
    break;

  case 731:
#line 3955 "parser.y"
    { BEGIN_STATEMENT ("ALLOCATE", 0); ;}
    break;

  case 733:
#line 3961 "parser.y"
    {
	cb_emit_allocate (yyvsp[-2], yyvsp[0], NULL, yyvsp[-1]);
  ;}
    break;

  case 734:
#line 3965 "parser.y"
    {
	cb_emit_allocate (NULL, yyvsp[0], yyvsp[-4], yyvsp[-2]);
  ;}
    break;

  case 735:
#line 3971 "parser.y"
    { yyval = NULL; ;}
    break;

  case 736:
#line 3972 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 737:
#line 3982 "parser.y"
    {
	cb_error (_("ALTER statement is obsolete and unsupported"));
  ;}
    break;

  case 742:
#line 4000 "parser.y"
    { BEGIN_STATEMENT ("CALL", TERM_CALL); ;}
    break;

  case 743:
#line 4004 "parser.y"
    {
	cb_emit_call (yyvsp[-5], yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1]);
  ;}
    break;

  case 744:
#line 4010 "parser.y"
    { yyval = NULL; ;}
    break;

  case 745:
#line 4012 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  ;}
    break;

  case 746:
#line 4016 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 747:
#line 4020 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 748:
#line 4022 "parser.y"
    { yyval = cb_list_append (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 749:
#line 4027 "parser.y"
    {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OMITTED only allowed with BY REFERENCE"));
	}
	yyval = cb_build_pair (cb_int (call_mode), cb_null);
  ;}
    break;

  case 750:
#line 4034 "parser.y"
    {
	yyval = cb_build_pair (cb_int (call_mode), yyvsp[0]);
	CB_SIZES (yyval) = size_mode;
  ;}
    break;

  case 752:
#line 4043 "parser.y"
    {
	call_mode = CB_CALL_BY_REFERENCE;
  ;}
    break;

  case 753:
#line 4047 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY CONTENT not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_CONTENT;
	}
  ;}
    break;

  case 754:
#line 4055 "parser.y"
    {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  ;}
    break;

  case 755:
#line 4065 "parser.y"
    { yyval = NULL; ;}
    break;

  case 756:
#line 4066 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 757:
#line 4067 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 758:
#line 4072 "parser.y"
    {
	yyval = NULL;
  ;}
    break;

  case 759:
#line 4076 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 760:
#line 4080 "parser.y"
    {
	yyval = yyvsp[0];
  ;}
    break;

  case 761:
#line 4087 "parser.y"
    {
	yyval = NULL;
  ;}
    break;

  case 762:
#line 4091 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 763:
#line 4095 "parser.y"
    {
	yyval = yyvsp[0];
  ;}
    break;

  case 764:
#line 4101 "parser.y"
    { terminator_warning (TERM_CALL); ;}
    break;

  case 765:
#line 4102 "parser.y"
    { terminator_clear (TERM_CALL); ;}
    break;

  case 766:
#line 4111 "parser.y"
    { BEGIN_STATEMENT ("CANCEL", 0); ;}
    break;

  case 769:
#line 4117 "parser.y"
    {
	cb_emit_cancel (yyvsp[0]);
  ;}
    break;

  case 770:
#line 4128 "parser.y"
    { BEGIN_STATEMENT ("CLOSE", 0); ;}
    break;

  case 773:
#line 4135 "parser.y"
    {
	BEGIN_IMPLICIT_STATEMENT ();
	if (yyvsp[-1] != cb_error_node) {
		cb_emit_close (yyvsp[-1], yyvsp[0]);
	}
  ;}
    break;

  case 774:
#line 4144 "parser.y"
    { yyval = cb_int (COB_CLOSE_NORMAL); ;}
    break;

  case 775:
#line 4145 "parser.y"
    { yyval = cb_int (COB_CLOSE_UNIT); ;}
    break;

  case 776:
#line 4146 "parser.y"
    { yyval = cb_int (COB_CLOSE_UNIT_REMOVAL); ;}
    break;

  case 777:
#line 4147 "parser.y"
    { yyval = cb_int (COB_CLOSE_NO_REWIND); ;}
    break;

  case 778:
#line 4148 "parser.y"
    { yyval = cb_int (COB_CLOSE_LOCK); ;}
    break;

  case 781:
#line 4159 "parser.y"
    { BEGIN_STATEMENT ("COMPUTE", TERM_COMPUTE); ;}
    break;

  case 783:
#line 4166 "parser.y"
    {
	cb_emit_arithmetic (yyvsp[-3], 0, yyvsp[-1]);
  ;}
    break;

  case 784:
#line 4172 "parser.y"
    { terminator_warning (TERM_COMPUTE); ;}
    break;

  case 785:
#line 4173 "parser.y"
    { terminator_clear (TERM_COMPUTE); ;}
    break;

  case 788:
#line 4184 "parser.y"
    {
	BEGIN_STATEMENT ("COMMIT", 0);
	cb_emit_commit ();
  ;}
    break;

  case 789:
#line 4197 "parser.y"
    {
	BEGIN_STATEMENT ("CONTINUE", 0);
	cb_emit_continue ();
  ;}
    break;

  case 790:
#line 4209 "parser.y"
    { BEGIN_STATEMENT ("DELETE", TERM_DELETE); ;}
    break;

  case 791:
#line 4212 "parser.y"
    {
	if (yyvsp[-3] != cb_error_node) {
		cb_emit_delete (yyvsp[-3]);
	}
  ;}
    break;

  case 792:
#line 4220 "parser.y"
    { terminator_warning (TERM_DELETE); ;}
    break;

  case 793:
#line 4221 "parser.y"
    { terminator_clear (TERM_DELETE); ;}
    break;

  case 794:
#line 4231 "parser.y"
    {
	BEGIN_STATEMENT ("DISPLAY", TERM_DISPLAY);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  ;}
    break;

  case 796:
#line 4244 "parser.y"
    {
	cb_emit_env_name (yyvsp[-2]);
  ;}
    break;

  case 797:
#line 4248 "parser.y"
    {
	cb_emit_env_value (yyvsp[-2]);
  ;}
    break;

  case 798:
#line 4252 "parser.y"
    {
	cb_emit_arg_number (yyvsp[-2]);
  ;}
    break;

  case 799:
#line 4256 "parser.y"
    {
	cb_emit_command_line (yyvsp[-2]);
  ;}
    break;

  case 800:
#line 4260 "parser.y"
    {
	cb_emit_display (yyvsp[-4], yyvsp[-2], yyvsp[-1], yyvsp[-3], fgc, bgc, scroll, dispattrs);
  ;}
    break;

  case 801:
#line 4266 "parser.y"
    { yyval = cb_int0; ;}
    break;

  case 802:
#line 4267 "parser.y"
    { yyval = cb_build_display_upon (yyvsp[0]); ;}
    break;

  case 803:
#line 4268 "parser.y"
    { yyval = cb_build_display_upon_direct (yyvsp[0]); ;}
    break;

  case 804:
#line 4269 "parser.y"
    { yyval = cb_int0; ;}
    break;

  case 805:
#line 4270 "parser.y"
    { yyval = cb_int0; ;}
    break;

  case 806:
#line 4274 "parser.y"
    { yyval = cb_int1; ;}
    break;

  case 807:
#line 4275 "parser.y"
    { yyval = cb_int0; ;}
    break;

  case 808:
#line 4276 "parser.y"
    { yyval = cb_int1; ;}
    break;

  case 811:
#line 4286 "parser.y"
    { dispattrs |= COB_SCREEN_BELL; ;}
    break;

  case 812:
#line 4287 "parser.y"
    { dispattrs |= COB_SCREEN_BLINK; ;}
    break;

  case 813:
#line 4288 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOL; ;}
    break;

  case 814:
#line 4289 "parser.y"
    { dispattrs |= COB_SCREEN_ERASE_EOS; ;}
    break;

  case 815:
#line 4290 "parser.y"
    { dispattrs |= COB_SCREEN_HIGHLIGHT; ;}
    break;

  case 816:
#line 4291 "parser.y"
    { dispattrs |= COB_SCREEN_LOWLIGHT; ;}
    break;

  case 817:
#line 4292 "parser.y"
    { dispattrs |= COB_SCREEN_REVERSE; ;}
    break;

  case 818:
#line 4293 "parser.y"
    { dispattrs |= COB_SCREEN_UNDERLINE; ;}
    break;

  case 819:
#line 4294 "parser.y"
    { dispattrs |= COB_SCREEN_OVERLINE; ;}
    break;

  case 820:
#line 4296 "parser.y"
    {
	fgc = yyvsp[0];
  ;}
    break;

  case 821:
#line 4300 "parser.y"
    {
	bgc = yyvsp[0];
  ;}
    break;

  case 822:
#line 4304 "parser.y"
    {
	scroll = yyvsp[0];
  ;}
    break;

  case 823:
#line 4308 "parser.y"
    {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = yyvsp[0];
  ;}
    break;

  case 824:
#line 4312 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_LINE; ;}
    break;

  case 825:
#line 4313 "parser.y"
    { dispattrs |= COB_SCREEN_BLANK_SCREEN; ;}
    break;

  case 826:
#line 4317 "parser.y"
    { terminator_warning (TERM_DISPLAY); ;}
    break;

  case 827:
#line 4318 "parser.y"
    { terminator_clear (TERM_DISPLAY); ;}
    break;

  case 828:
#line 4327 "parser.y"
    { BEGIN_STATEMENT ("DIVIDE", TERM_DIVIDE); ;}
    break;

  case 830:
#line 4334 "parser.y"
    {
	cb_emit_arithmetic (yyvsp[-1], '/', yyvsp[-3]);
  ;}
    break;

  case 831:
#line 4338 "parser.y"
    {
	cb_emit_arithmetic (yyvsp[-1], 0, cb_build_binary_op (yyvsp[-3], '/', yyvsp[-5]));
  ;}
    break;

  case 832:
#line 4342 "parser.y"
    {
	cb_emit_arithmetic (yyvsp[-1], 0, cb_build_binary_op (yyvsp[-5], '/', yyvsp[-3]));
  ;}
    break;

  case 833:
#line 4346 "parser.y"
    {
	cb_emit_divide (yyvsp[-5], yyvsp[-7], yyvsp[-3], yyvsp[-1]);
  ;}
    break;

  case 834:
#line 4350 "parser.y"
    {
	cb_emit_divide (yyvsp[-7], yyvsp[-5], yyvsp[-3], yyvsp[-1]);
  ;}
    break;

  case 835:
#line 4356 "parser.y"
    { terminator_warning (TERM_DIVIDE); ;}
    break;

  case 836:
#line 4357 "parser.y"
    { terminator_clear (TERM_DIVIDE); ;}
    break;

  case 837:
#line 4366 "parser.y"
    { BEGIN_STATEMENT ("ENTRY", 0); ;}
    break;

  case 838:
#line 4368 "parser.y"
    {
	if (current_program->nested_level) {
		cb_error (_("ENTRY is invalid in nested program"));
	} else if (cb_verify (cb_entry_statement, "ENTRY")) {
		if (cobc_check_valid_name ((char *)(CB_LITERAL (yyvsp[-1])->data))) {
			cb_error (_("ENTRY '%s' invalid"), (char *)(CB_LITERAL (yyvsp[-1])->data));
		}
		emit_entry ((char *)(CB_LITERAL (yyvsp[-1])->data), 1, yyvsp[0]);
	}
	check_unreached = 0;
  ;}
    break;

  case 839:
#line 4388 "parser.y"
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

  case 840:
#line 4399 "parser.y"
    {
	cb_emit_evaluate (yyvsp[-2], yyvsp[-1]);
	eval_level--;
  ;}
    break;

  case 841:
#line 4406 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 842:
#line 4408 "parser.y"
    { yyval = cb_list_add (yyvsp[-2], yyvsp[0]); ;}
    break;

  case 843:
#line 4413 "parser.y"
    {
	yyval = yyvsp[0];
	if (CB_REFERENCE_P (yyvsp[0])) {
		eval_check[eval_level][eval_inc++] = 0;
	} else {
		eval_check[eval_level][eval_inc++] = 1;
	}
  ;}
    break;

  case 844:
#line 4422 "parser.y"
    {
	yyval = cb_true;
	eval_check[eval_level][eval_inc++] = 2;
  ;}
    break;

  case 845:
#line 4427 "parser.y"
    {
	yyval = cb_false;
	eval_check[eval_level][eval_inc++] = 3;
  ;}
    break;

  case 846:
#line 4435 "parser.y"
    {
	yyval = yyvsp[-1];
	if (yyvsp[0]) {
		yyval = cb_list_add (yyval, yyvsp[0]);
	}
  ;}
    break;

  case 847:
#line 4444 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 848:
#line 4446 "parser.y"
    { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 849:
#line 4451 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 850:
#line 4455 "parser.y"
    {
	yyval = cb_cons (yyvsp[0], yyvsp[-2]);
	eval_inc2 = 0;
  ;}
    break;

  case 851:
#line 4463 "parser.y"
    {
	yyval = NULL;
  ;}
    break;

  case 852:
#line 4467 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 853:
#line 4471 "parser.y"
    {
	yyval = cb_cons (yyvsp[0], NULL);
	eval_inc2 = 0;
  ;}
    break;

  case 854:
#line 4478 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 855:
#line 4480 "parser.y"
    { yyval = cb_list_add (yyvsp[-2], yyvsp[0]); ;}
    break;

  case 856:
#line 4484 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 857:
#line 4486 "parser.y"
    { yyval = cb_list_add (yyvsp[-2], yyvsp[0]); ;}
    break;

  case 858:
#line 4491 "parser.y"
    {
	cb_tree not;
	cb_tree e1;
	cb_tree e2;

	not = cb_int0;
	e2 = yyvsp[0];
	/* in case the first token is NOT */
	if (CB_PURPOSE_INT (yyvsp[-1]) == '!') {
		if (eval_check[eval_level][eval_inc2] < 2) {
			not = cb_int1;
			yyvsp[-1] = CB_CHAIN (yyvsp[-1]);
		}
	}

	/* build expr now */
	e1 = cb_build_expr (yyvsp[-1]);

	if (e2 == NULL) {
		/* WHEN expr */
		eval_inc2++;
		yyval = cb_build_pair (not, cb_build_pair (e1, NULL));
	} else {
		/* WHEN expr THRU expr */
		yyval = cb_build_pair (not, cb_build_pair (e1, e2));
		eval_inc2++;
	}
  ;}
    break;

  case 859:
#line 4519 "parser.y"
    { yyval = cb_any; eval_inc2++; ;}
    break;

  case 860:
#line 4520 "parser.y"
    { yyval = cb_true; eval_inc2++; ;}
    break;

  case 861:
#line 4521 "parser.y"
    { yyval = cb_false; eval_inc2++; ;}
    break;

  case 862:
#line 4524 "parser.y"
    { yyval = NULL; ;}
    break;

  case 863:
#line 4525 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 864:
#line 4529 "parser.y"
    { terminator_warning (TERM_EVALUATE); ;}
    break;

  case 865:
#line 4530 "parser.y"
    { terminator_clear (TERM_EVALUATE); ;}
    break;

  case 866:
#line 4539 "parser.y"
    { BEGIN_STATEMENT ("EXIT", 0); ;}
    break;

  case 868:
#line 4544 "parser.y"
    { /* nothing */ ;}
    break;

  case 869:
#line 4546 "parser.y"
    {
	if (in_declaratives && use_global_ind) {
		cb_error (_("EXIT PROGRAM is not allowed within a USE GLOBAL procedure"));
	}
	check_unreached = 1;
	cb_emit_exit (0);
  ;}
    break;

  case 870:
#line 4554 "parser.y"
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

  case 871:
#line 4571 "parser.y"
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

  case 872:
#line 4588 "parser.y"
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

  case 873:
#line 4606 "parser.y"
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

  case 874:
#line 4630 "parser.y"
    { BEGIN_STATEMENT ("FREE", 0); ;}
    break;

  case 875:
#line 4632 "parser.y"
    {
	cb_emit_free (yyvsp[0])
  ;}
    break;

  case 876:
#line 4643 "parser.y"
    { BEGIN_STATEMENT ("GENERATE", 0); ;}
    break;

  case 877:
#line 4645 "parser.y"
    {
	PENDING("GENERATE");
  ;}
    break;

  case 878:
#line 4656 "parser.y"
    { BEGIN_STATEMENT ("GO TO", 0); ;}
    break;

  case 879:
#line 4658 "parser.y"
    {
	cb_emit_goto (yyvsp[-1], yyvsp[0]);
  ;}
    break;

  case 880:
#line 4665 "parser.y"
    {
	check_unreached = 1;
	yyval = NULL;
  ;}
    break;

  case 881:
#line 4670 "parser.y"
    {
	check_unreached = 0;
	yyval = yyvsp[0];
  ;}
    break;

  case 882:
#line 4682 "parser.y"
    { BEGIN_STATEMENT ("GOBACK", 0); ;}
    break;

  case 883:
#line 4683 "parser.y"
    {
	check_unreached = 1;
	cb_emit_exit (1);
  ;}
    break;

  case 884:
#line 4695 "parser.y"
    { BEGIN_STATEMENT ("IF", TERM_IF); ;}
    break;

  case 885:
#line 4697 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 886:
#line 4702 "parser.y"
    {
	cb_emit_if (yyvsp[-5], yyvsp[-2], yyvsp[-1]);
  ;}
    break;

  case 888:
#line 4710 "parser.y"
    {
	yyval = NULL;
  ;}
    break;

  case 889:
#line 4714 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 890:
#line 4718 "parser.y"
    {
	yyval = yyvsp[0];
  ;}
    break;

  case 891:
#line 4724 "parser.y"
    { terminator_warning (TERM_IF); ;}
    break;

  case 892:
#line 4725 "parser.y"
    { terminator_clear (TERM_IF); ;}
    break;

  case 893:
#line 4734 "parser.y"
    { BEGIN_STATEMENT ("INITIALIZE", 0); ;}
    break;

  case 894:
#line 4736 "parser.y"
    {
	cb_emit_initialize (yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]);
  ;}
    break;

  case 895:
#line 4742 "parser.y"
    { yyval = NULL; ;}
    break;

  case 896:
#line 4743 "parser.y"
    { yyval = cb_true; ;}
    break;

  case 897:
#line 4747 "parser.y"
    { yyval = NULL; ;}
    break;

  case 898:
#line 4748 "parser.y"
    { yyval = cb_true; ;}
    break;

  case 899:
#line 4749 "parser.y"
    { yyval = yyvsp[-2]; ;}
    break;

  case 900:
#line 4753 "parser.y"
    { yyval = NULL; ;}
    break;

  case 901:
#line 4755 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 902:
#line 4759 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 903:
#line 4761 "parser.y"
    { yyval = cb_list_append (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 904:
#line 4765 "parser.y"
    { yyval = cb_build_pair (yyvsp[-3], yyvsp[0]); ;}
    break;

  case 905:
#line 4769 "parser.y"
    { yyval = cb_int (CB_CATEGORY_ALPHABETIC); ;}
    break;

  case 906:
#line 4770 "parser.y"
    { yyval = cb_int (CB_CATEGORY_ALPHANUMERIC); ;}
    break;

  case 907:
#line 4771 "parser.y"
    { yyval = cb_int (CB_CATEGORY_NUMERIC); ;}
    break;

  case 908:
#line 4772 "parser.y"
    { yyval = cb_int (CB_CATEGORY_ALPHANUMERIC_EDITED); ;}
    break;

  case 909:
#line 4773 "parser.y"
    { yyval = cb_int (CB_CATEGORY_NUMERIC_EDITED); ;}
    break;

  case 910:
#line 4774 "parser.y"
    { yyval = cb_int (CB_CATEGORY_NATIONAL); ;}
    break;

  case 911:
#line 4775 "parser.y"
    { yyval = cb_int (CB_CATEGORY_NATIONAL_EDITED); ;}
    break;

  case 912:
#line 4779 "parser.y"
    { yyval = NULL; ;}
    break;

  case 913:
#line 4780 "parser.y"
    { yyval = cb_true; ;}
    break;

  case 914:
#line 4789 "parser.y"
    { BEGIN_STATEMENT ("INITIATE", 0); ;}
    break;

  case 915:
#line 4791 "parser.y"
    {
	PENDING("INITIATE");
  ;}
    break;

  case 916:
#line 4802 "parser.y"
    {
	BEGIN_STATEMENT ("INSPECT", 0);
	sending_id = 0;
	inspect_keyword = 0;
  ;}
    break;

  case 918:
#line 4811 "parser.y"
    { save_tree_1 = yyvsp[0]; sending_id = 0; ;}
    break;

  case 919:
#line 4812 "parser.y"
    { save_tree_1 = yyvsp[0]; sending_id = 1; ;}
    break;

  case 920:
#line 4813 "parser.y"
    { save_tree_1 = yyvsp[0]; sending_id = 1; ;}
    break;

  case 923:
#line 4822 "parser.y"
    { cb_emit_inspect (save_tree_1, yyvsp[0], cb_int0, 0); ;}
    break;

  case 924:
#line 4823 "parser.y"
    { cb_emit_inspect (save_tree_1, yyvsp[0], cb_int1, 1); ;}
    break;

  case 925:
#line 4824 "parser.y"
    { cb_emit_inspect (save_tree_1, yyvsp[0], cb_int0, 2); ;}
    break;

  case 926:
#line 4830 "parser.y"
    { cb_init_tarrying (); ;}
    break;

  case 927:
#line 4831 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 928:
#line 4835 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 929:
#line 4836 "parser.y"
    { yyval = cb_list_append (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 930:
#line 4840 "parser.y"
    { yyval = cb_build_tarrying_data (yyvsp[-1]); ;}
    break;

  case 931:
#line 4841 "parser.y"
    { yyval = cb_build_tarrying_characters (yyvsp[0]); ;}
    break;

  case 932:
#line 4842 "parser.y"
    { yyval = cb_build_tarrying_all (); ;}
    break;

  case 933:
#line 4843 "parser.y"
    { yyval = cb_build_tarrying_leading (); ;}
    break;

  case 934:
#line 4844 "parser.y"
    { yyval = cb_build_tarrying_trailing (); ;}
    break;

  case 935:
#line 4845 "parser.y"
    { yyval = cb_build_tarrying_value (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 936:
#line 4851 "parser.y"
    { yyval = yyvsp[0]; inspect_keyword = 0; ;}
    break;

  case 937:
#line 4855 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 938:
#line 4856 "parser.y"
    { yyval = cb_list_append (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 939:
#line 4861 "parser.y"
    {
	yyval = cb_build_replacing_characters (yyvsp[-1], yyvsp[0]);
	inspect_keyword = 0;
  ;}
    break;

  case 940:
#line 4865 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 941:
#line 4869 "parser.y"
    { /* Nothing */ ;}
    break;

  case 942:
#line 4870 "parser.y"
    { inspect_keyword = 1; ;}
    break;

  case 943:
#line 4871 "parser.y"
    { inspect_keyword = 2; ;}
    break;

  case 944:
#line 4872 "parser.y"
    { inspect_keyword = 3; ;}
    break;

  case 945:
#line 4873 "parser.y"
    { inspect_keyword = 4; ;}
    break;

  case 946:
#line 4878 "parser.y"
    {
	switch (inspect_keyword) {
		case 1:
			yyval = cb_build_replacing_all (yyvsp[-3], yyvsp[-1], yyvsp[0]);
			break;
		case 2:
			yyval = cb_build_replacing_leading (yyvsp[-3], yyvsp[-1], yyvsp[0]);
			break;
		case 3:
			yyval = cb_build_replacing_first (yyvsp[-3], yyvsp[-1], yyvsp[0]);
			break;
		case 4:
			yyval = cb_build_replacing_trailing (yyvsp[-3], yyvsp[-1], yyvsp[0]);
			break;
		default:
			cb_error (_("INSPECT missing a keyword"));
			yyval = cb_error_node;
			break;
	}
  ;}
    break;

  case 947:
#line 4904 "parser.y"
    {
	yyval = cb_build_converting (yyvsp[-3], yyvsp[-1], yyvsp[0]);
  ;}
    break;

  case 948:
#line 4912 "parser.y"
    { yyval = cb_build_inspect_region_start (); ;}
    break;

  case 949:
#line 4914 "parser.y"
    { yyval = cb_build_inspect_region (yyvsp[-3], yyvsp[-2], yyvsp[0]); ;}
    break;

  case 952:
#line 4925 "parser.y"
    { BEGIN_STATEMENT ("MERGE", 0); ;}
    break;

  case 954:
#line 4935 "parser.y"
    { BEGIN_STATEMENT ("MOVE", 0); ;}
    break;

  case 956:
#line 4941 "parser.y"
    {
	cb_emit_move (yyvsp[-2], yyvsp[0]);
  ;}
    break;

  case 957:
#line 4945 "parser.y"
    {
	cb_emit_move_corresponding (yyvsp[-2], yyvsp[0]);
  ;}
    break;

  case 958:
#line 4956 "parser.y"
    { BEGIN_STATEMENT ("MULTIPLY", TERM_MULTIPLY); ;}
    break;

  case 960:
#line 4963 "parser.y"
    {
	cb_emit_arithmetic (yyvsp[-1], '*', yyvsp[-3]);
  ;}
    break;

  case 961:
#line 4967 "parser.y"
    {
	cb_emit_arithmetic (yyvsp[-1], 0, cb_build_binary_op (yyvsp[-5], '*', yyvsp[-3]));
  ;}
    break;

  case 962:
#line 4973 "parser.y"
    { terminator_warning (TERM_MULTIPLY); ;}
    break;

  case 963:
#line 4974 "parser.y"
    { terminator_clear (TERM_MULTIPLY); ;}
    break;

  case 964:
#line 4983 "parser.y"
    { BEGIN_STATEMENT ("OPEN", 0); ;}
    break;

  case 967:
#line 4990 "parser.y"
    {
	cb_tree l;
	for (l = yyvsp[-1]; l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			BEGIN_IMPLICIT_STATEMENT ();
			cb_emit_open (CB_VALUE (l), yyvsp[-3], yyvsp[-2]);
		}
	}
  ;}
    break;

  case 968:
#line 5002 "parser.y"
    { yyval = cb_int (COB_OPEN_INPUT); ;}
    break;

  case 969:
#line 5003 "parser.y"
    { yyval = cb_int (COB_OPEN_OUTPUT); ;}
    break;

  case 970:
#line 5004 "parser.y"
    { yyval = cb_int (COB_OPEN_I_O); ;}
    break;

  case 971:
#line 5005 "parser.y"
    { yyval = cb_int (COB_OPEN_EXTEND); ;}
    break;

  case 972:
#line 5009 "parser.y"
    { yyval = NULL; ;}
    break;

  case 973:
#line 5010 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 974:
#line 5014 "parser.y"
    { yyval = NULL; ;}
    break;

  case 975:
#line 5015 "parser.y"
    { yyval = NULL; ;}
    break;

  case 976:
#line 5016 "parser.y"
    { PENDING ("OPEN ... WITH LOCK"); ;}
    break;

  case 977:
#line 5028 "parser.y"
    { BEGIN_STATEMENT ("PERFORM", TERM_PERFORM); ;}
    break;

  case 979:
#line 5034 "parser.y"
    {
	cb_emit_perform (yyvsp[0], yyvsp[-1]);
  ;}
    break;

  case 980:
#line 5038 "parser.y"
    {
	perform_stack = cb_cons (yyvsp[0], perform_stack);
	check_unreached = 0;
  ;}
    break;

  case 981:
#line 5043 "parser.y"
    {
	perform_stack = CB_CHAIN (perform_stack);
	cb_emit_perform (yyvsp[-3], yyvsp[-1]);
  ;}
    break;

  case 982:
#line 5048 "parser.y"
    {
	cb_emit_perform (yyvsp[-1], NULL);
  ;}
    break;

  case 983:
#line 5054 "parser.y"
    { terminator_error (); ;}
    break;

  case 984:
#line 5055 "parser.y"
    { terminator_clear (TERM_PERFORM); ;}
    break;

  case 985:
#line 5060 "parser.y"
    {
	CB_REFERENCE (yyvsp[0])->length = cb_true; /* return from $1 */
	yyval = cb_build_pair (yyvsp[0], yyvsp[0]);
  ;}
    break;

  case 986:
#line 5065 "parser.y"
    {
	CB_REFERENCE (yyvsp[0])->length = cb_true; /* return from $3 */
	yyval = cb_build_pair (yyvsp[-2], yyvsp[0]);
  ;}
    break;

  case 987:
#line 5073 "parser.y"
    {
	yyval = cb_build_perform_once (NULL);
  ;}
    break;

  case 988:
#line 5077 "parser.y"
    {
	yyval = cb_build_perform_forever (NULL);
  ;}
    break;

  case 989:
#line 5081 "parser.y"
    {
	yyval = cb_build_perform_times (yyvsp[-1]);
	current_program->loop_counter++;
  ;}
    break;

  case 990:
#line 5086 "parser.y"
    {
	cb_tree varying;

	varying = cb_list_init (cb_build_perform_varying (NULL, NULL, NULL, yyvsp[0]));
	yyval = cb_build_perform_until (yyvsp[-2], varying);
  ;}
    break;

  case 991:
#line 5093 "parser.y"
    {
	yyval = cb_build_perform_until (yyvsp[-2], yyvsp[0]);
  ;}
    break;

  case 992:
#line 5099 "parser.y"
    { yyval = CB_BEFORE; ;}
    break;

  case 993:
#line 5100 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 994:
#line 5104 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 995:
#line 5106 "parser.y"
    { yyval = cb_list_add (yyvsp[-2], yyvsp[0]); ;}
    break;

  case 996:
#line 5111 "parser.y"
    {
	yyval = cb_build_perform_varying (yyvsp[-6], yyvsp[-4], yyvsp[-2], yyvsp[0]);
  ;}
    break;

  case 997:
#line 5122 "parser.y"
    { BEGIN_STATEMENT ("READ", TERM_READ); ;}
    break;

  case 998:
#line 5125 "parser.y"
    {
	if (yyvsp[-7] != cb_error_node) {
		if (yyvsp[-3] && (CB_FILE(cb_ref (yyvsp[-7]))->lock_mode & COB_LOCK_AUTOMATIC)) {
			cb_error (_("LOCK clause invalid with file LOCK AUTOMATIC"));
		} else if (yyvsp[-2] &&
		      (CB_FILE(cb_ref (yyvsp[-7]))->organization != COB_ORG_RELATIVE &&
		       CB_FILE(cb_ref (yyvsp[-7]))->organization != COB_ORG_INDEXED)) {
			cb_error (_("KEY clause invalid with this file type"));
		} else if (current_statement->handler_id == COB_EC_I_O_INVALID_KEY &&
		      (CB_FILE(cb_ref (yyvsp[-7]))->organization != COB_ORG_RELATIVE &&
		       CB_FILE(cb_ref (yyvsp[-7]))->organization != COB_ORG_INDEXED)) {
			cb_error (_("INVALID KEY clause invalid with this file type"));
		} else {
			cb_emit_read (yyvsp[-7], yyvsp[-6], yyvsp[-4], yyvsp[-2], yyvsp[-3]);
		}
	}
  ;}
    break;

  case 999:
#line 5145 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1000:
#line 5146 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1001:
#line 5150 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1002:
#line 5152 "parser.y"
    {
	yyval = cb_int3;
  ;}
    break;

  case 1003:
#line 5156 "parser.y"
    {
	yyval = cb_int1;
  ;}
    break;

  case 1004:
#line 5160 "parser.y"
    {
	yyval = cb_int2;
  ;}
    break;

  case 1005:
#line 5164 "parser.y"
    {
	yyval = cb_int3;
  ;}
    break;

  case 1006:
#line 5168 "parser.y"
    {
	yyval = cb_int4;
  ;}
    break;

  case 1007:
#line 5174 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1008:
#line 5175 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1012:
#line 5184 "parser.y"
    { terminator_warning (TERM_READ); ;}
    break;

  case 1013:
#line 5185 "parser.y"
    { terminator_clear (TERM_READ); ;}
    break;

  case 1014:
#line 5194 "parser.y"
    { BEGIN_STATEMENT ("RELEASE", 0); ;}
    break;

  case 1015:
#line 5196 "parser.y"
    {
	if (yyvsp[-1] != cb_error_node) {
		cb_emit_release (yyvsp[-1], yyvsp[0]);
	}
  ;}
    break;

  case 1016:
#line 5209 "parser.y"
    { BEGIN_STATEMENT ("RETURN", TERM_RETURN); ;}
    break;

  case 1017:
#line 5212 "parser.y"
    {
	if (yyvsp[-4] != cb_error_node) {
		cb_emit_return (yyvsp[-4], yyvsp[-2]);
	}
  ;}
    break;

  case 1018:
#line 5220 "parser.y"
    { terminator_warning (TERM_RETURN); ;}
    break;

  case 1019:
#line 5221 "parser.y"
    { terminator_clear (TERM_RETURN); ;}
    break;

  case 1020:
#line 5230 "parser.y"
    { BEGIN_STATEMENT ("REWRITE", TERM_REWRITE); ;}
    break;

  case 1021:
#line 5233 "parser.y"
    {
	if (yyvsp[-4] != cb_error_node) {
		cb_emit_rewrite (yyvsp[-4], yyvsp[-3], yyvsp[-2]);
	}
  ;}
    break;

  case 1022:
#line 5241 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1023:
#line 5243 "parser.y"
    {
	yyval = cb_int1;
  ;}
    break;

  case 1024:
#line 5247 "parser.y"
    {
	yyval = cb_int2;
  ;}
    break;

  case 1025:
#line 5253 "parser.y"
    { terminator_warning (TERM_REWRITE); ;}
    break;

  case 1026:
#line 5254 "parser.y"
    { terminator_clear (TERM_REWRITE); ;}
    break;

  case 1027:
#line 5264 "parser.y"
    {
	BEGIN_STATEMENT ("ROLLBACK", 0);
	cb_emit_rollback ();
  ;}
    break;

  case 1028:
#line 5276 "parser.y"
    { BEGIN_STATEMENT ("SEARCH", TERM_SEARCH); ;}
    break;

  case 1030:
#line 5283 "parser.y"
    {
	cb_emit_search (yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]);
  ;}
    break;

  case 1031:
#line 5287 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1032:
#line 5291 "parser.y"
    {
	cb_emit_search_all (yyvsp[-5], yyvsp[-4], yyvsp[-2], yyvsp[0]);
  ;}
    break;

  case 1033:
#line 5297 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1034:
#line 5298 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1035:
#line 5302 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1036:
#line 5304 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1037:
#line 5308 "parser.y"
    {
	yyval = yyvsp[0];
  ;}
    break;

  case 1038:
#line 5314 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1039:
#line 5315 "parser.y"
    { yyval = yyvsp[-1]; CB_IF (yyvsp[-1])->stmt2 = yyvsp[0]; ;}
    break;

  case 1040:
#line 5320 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1041:
#line 5324 "parser.y"
    {
	yyval = cb_build_if (yyvsp[-2], yyvsp[0], NULL);
  ;}
    break;

  case 1042:
#line 5330 "parser.y"
    { terminator_warning (TERM_SEARCH); ;}
    break;

  case 1043:
#line 5331 "parser.y"
    { terminator_clear (TERM_SEARCH); ;}
    break;

  case 1044:
#line 5340 "parser.y"
    { BEGIN_STATEMENT ("SET", 0); ;}
    break;

  case 1051:
#line 5356 "parser.y"
    {
	cb_emit_setenv (yyvsp[-2], yyvsp[0]);
  ;}
    break;

  case 1052:
#line 5365 "parser.y"
    {
	cb_emit_set_to (yyvsp[-3], cb_build_ppointer (yyvsp[0]));
  ;}
    break;

  case 1053:
#line 5369 "parser.y"
    {
	cb_emit_set_to (yyvsp[-2], yyvsp[0]);
  ;}
    break;

  case 1054:
#line 5378 "parser.y"
    {
	cb_emit_set_up_down (yyvsp[-3], yyvsp[-2], yyvsp[0]);
  ;}
    break;

  case 1055:
#line 5384 "parser.y"
    { yyval = cb_int0; ;}
    break;

  case 1056:
#line 5385 "parser.y"
    { yyval = cb_int1; ;}
    break;

  case 1059:
#line 5397 "parser.y"
    {
	cb_emit_set_on_off (yyvsp[-2], yyvsp[0]);
  ;}
    break;

  case 1062:
#line 5411 "parser.y"
    {
	cb_emit_set_true (yyvsp[-2]);
  ;}
    break;

  case 1063:
#line 5415 "parser.y"
    {
	cb_emit_set_false (yyvsp[-2]);
  ;}
    break;

  case 1064:
#line 5426 "parser.y"
    { BEGIN_STATEMENT ("SORT", 0); ;}
    break;

  case 1066:
#line 5432 "parser.y"
    {
	cb_emit_sort_init (yyvsp[-3], yyvsp[-2], yyvsp[0]);
	if (CB_FILE_P (cb_ref (yyvsp[-3])) && yyvsp[-2] == NULL) {
		cb_error (_("File sort requires KEY phrase"));
	}
	/* used in sort_input/sort_output */
	save_tree_1 = yyvsp[-3];
  ;}
    break;

  case 1067:
#line 5441 "parser.y"
    {
	cb_emit_sort_finish (yyvsp[-6]);
  ;}
    break;

  case 1068:
#line 5448 "parser.y"
    {
	yyval = NULL;
  ;}
    break;

  case 1069:
#line 5453 "parser.y"
    {
	cb_tree l;

	if (yyvsp[0] == NULL) {
		yyvsp[0] = cb_list_init (NULL);
	}
	for (l = yyvsp[0]; l; l = CB_CHAIN (l)) {
		CB_PURPOSE (l) = yyvsp[-2];
	}
	yyval = cb_list_append (yyvsp[-4], yyvsp[0]);
  ;}
    break;

  case 1070:
#line 5467 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1071:
#line 5468 "parser.y"
    { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 1073:
#line 5472 "parser.y"
    { /* nothing */ ;}
    break;

  case 1074:
#line 5476 "parser.y"
    { yyval = cb_null; ;}
    break;

  case 1075:
#line 5477 "parser.y"
    { yyval = cb_ref (yyvsp[0]); ;}
    break;

  case 1076:
#line 5482 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires USING or INPUT PROCEDURE"));
	}
  ;}
    break;

  case 1077:
#line 5488 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("USING invalid with table SORT"));
	} else {
		cb_emit_sort_using (save_tree_1, yyvsp[0]);
	}
  ;}
    break;

  case 1078:
#line 5496 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("INPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_input (yyvsp[0]);
	}
  ;}
    break;

  case 1079:
#line 5507 "parser.y"
    {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires GIVING or OUTPUT PROCEDURE"));
	}
  ;}
    break;

  case 1080:
#line 5513 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("GIVING invalid with table SORT"));
	} else {
		cb_emit_sort_giving (save_tree_1, yyvsp[0]);
	}
  ;}
    break;

  case 1081:
#line 5521 "parser.y"
    {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("OUTPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_output (yyvsp[0]);
	}
  ;}
    break;

  case 1082:
#line 5536 "parser.y"
    { BEGIN_STATEMENT ("START", TERM_START); ;}
    break;

  case 1083:
#line 5537 "parser.y"
    { yyval = cb_int (COB_EQ); ;}
    break;

  case 1084:
#line 5540 "parser.y"
    {
	if (CB_FILE_P (cb_ref (yyvsp[-4]))) {
		if (CB_FILE (cb_ref (yyvsp[-4]))->organization != COB_ORG_INDEXED &&
		     CB_FILE (cb_ref (yyvsp[-4]))->organization != COB_ORG_RELATIVE) {
			cb_error (_("START not allowed on SEQUENTIAL files"));
			yyval = cb_error_node;
		} else {
			cb_emit_start (yyvsp[-4], yyvsp[-3], yyvsp[-2]);
		}
	} else {
		cb_error_x (yyvsp[-4], _("'%s' is not a file name"), CB_NAME (yyvsp[-4]));
		yyval = cb_error_node;
	}
  ;}
    break;

  case 1085:
#line 5557 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1086:
#line 5558 "parser.y"
    { yyvsp[-4] = yyvsp[-1]; yyval = yyvsp[0]; ;}
    break;

  case 1087:
#line 5562 "parser.y"
    { yyval = cb_int ((yyvsp[-1] == cb_int1) ? COB_NE : COB_EQ); ;}
    break;

  case 1088:
#line 5563 "parser.y"
    { yyval = cb_int ((yyvsp[-1] == cb_int1) ? COB_LE : COB_GT); ;}
    break;

  case 1089:
#line 5564 "parser.y"
    { yyval = cb_int ((yyvsp[-1] == cb_int1) ? COB_GE : COB_LT); ;}
    break;

  case 1090:
#line 5565 "parser.y"
    { yyval = cb_int ((yyvsp[-1] == cb_int1) ? COB_LT : COB_GE); ;}
    break;

  case 1091:
#line 5566 "parser.y"
    { yyval = cb_int ((yyvsp[-1] == cb_int1) ? COB_GT : COB_LE); ;}
    break;

  case 1092:
#line 5570 "parser.y"
    { terminator_warning (TERM_START); ;}
    break;

  case 1093:
#line 5571 "parser.y"
    { terminator_clear (TERM_START); ;}
    break;

  case 1094:
#line 5580 "parser.y"
    { BEGIN_STATEMENT ("STOP", 0); ;}
    break;

  case 1095:
#line 5582 "parser.y"
    {
	cb_emit_stop_run (yyvsp[0]);
  ;}
    break;

  case 1096:
#line 5586 "parser.y"
    {
	cb_verify (cb_stop_literal_statement, "STOP literal");
  ;}
    break;

  case 1097:
#line 5592 "parser.y"
    { yyval = current_program->cb_return_code; ;}
    break;

  case 1098:
#line 5593 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1099:
#line 5594 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1100:
#line 5603 "parser.y"
    { BEGIN_STATEMENT ("STRING", TERM_STRING); ;}
    break;

  case 1101:
#line 5606 "parser.y"
    {
	cb_emit_string (yyvsp[-5], yyvsp[-3], yyvsp[-2]);
  ;}
    break;

  case 1102:
#line 5612 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 1103:
#line 5613 "parser.y"
    { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 1104:
#line 5617 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1105:
#line 5618 "parser.y"
    { yyval = cb_build_pair (cb_int0, NULL); ;}
    break;

  case 1106:
#line 5619 "parser.y"
    { yyval = cb_build_pair (yyvsp[0], NULL); ;}
    break;

  case 1107:
#line 5623 "parser.y"
    { yyval = cb_int0; ;}
    break;

  case 1108:
#line 5624 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1109:
#line 5628 "parser.y"
    { terminator_warning (TERM_STRING); ;}
    break;

  case 1110:
#line 5629 "parser.y"
    { terminator_clear (TERM_STRING); ;}
    break;

  case 1111:
#line 5638 "parser.y"
    { BEGIN_STATEMENT ("SUBTRACT", TERM_SUBTRACT); ;}
    break;

  case 1113:
#line 5645 "parser.y"
    {
	cb_emit_arithmetic (yyvsp[-1], '-', cb_build_binary_list (yyvsp[-3], '+'));
  ;}
    break;

  case 1114:
#line 5649 "parser.y"
    {
	cb_emit_arithmetic (yyvsp[-1], 0, cb_build_binary_list (cb_cons (yyvsp[-3], yyvsp[-5]), '-'));
  ;}
    break;

  case 1115:
#line 5653 "parser.y"
    {
	cb_emit_corresponding (cb_build_sub, yyvsp[-2], yyvsp[-4], yyvsp[-1]);
  ;}
    break;

  case 1116:
#line 5659 "parser.y"
    { terminator_warning (TERM_SUBTRACT); ;}
    break;

  case 1117:
#line 5660 "parser.y"
    { terminator_clear (TERM_SUBTRACT); ;}
    break;

  case 1118:
#line 5670 "parser.y"
    {
	BEGIN_STATEMENT ("SUPPRESS", 0);
	PENDING("SUPPRESS");
  ;}
    break;

  case 1121:
#line 5685 "parser.y"
    { BEGIN_STATEMENT ("TERMINATE", 0); ;}
    break;

  case 1122:
#line 5687 "parser.y"
    {
	PENDING("TERMINATE");
  ;}
    break;

  case 1123:
#line 5698 "parser.y"
    { BEGIN_STATEMENT ("TRANSFORM", 0); ;}
    break;

  case 1124:
#line 5700 "parser.y"
    {
	cb_tree		x;

	x = cb_build_converting (yyvsp[-2], yyvsp[0], cb_build_inspect_region_start ());
	cb_emit_inspect (yyvsp[-4], x, cb_int0, 2);
  ;}
    break;

  case 1125:
#line 5714 "parser.y"
    { BEGIN_STATEMENT ("UNLOCK", 0); ;}
    break;

  case 1126:
#line 5716 "parser.y"
    {
	if (yyvsp[-1] != cb_error_node) {
		cb_emit_unlock (yyvsp[-1]);
	}
  ;}
    break;

  case 1130:
#line 5735 "parser.y"
    { BEGIN_STATEMENT ("UNSTRING", TERM_UNSTRING); ;}
    break;

  case 1131:
#line 5739 "parser.y"
    {
	cb_emit_unstring (yyvsp[-6], yyvsp[-5], yyvsp[-4], yyvsp[-3], yyvsp[-2]);
  ;}
    break;

  case 1132:
#line 5745 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1133:
#line 5747 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1134:
#line 5751 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 1135:
#line 5753 "parser.y"
    { yyval = cb_list_add (yyvsp[-2], yyvsp[0]); ;}
    break;

  case 1136:
#line 5758 "parser.y"
    {
	yyval = cb_build_unstring_delimited (yyvsp[-1], yyvsp[0]);
  ;}
    break;

  case 1137:
#line 5764 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 1138:
#line 5766 "parser.y"
    { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 1139:
#line 5771 "parser.y"
    {
	yyval = cb_build_unstring_into (yyvsp[-2], yyvsp[-1], yyvsp[0]);
  ;}
    break;

  case 1140:
#line 5777 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1141:
#line 5778 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1142:
#line 5782 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1143:
#line 5783 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1144:
#line 5787 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1145:
#line 5788 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1146:
#line 5792 "parser.y"
    { terminator_warning (TERM_UNSTRING); ;}
    break;

  case 1147:
#line 5793 "parser.y"
    { terminator_clear (TERM_UNSTRING); ;}
    break;

  case 1151:
#line 5811 "parser.y"
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

  case 1152:
#line 5832 "parser.y"
    {
	use_global_ind = 0;
  ;}
    break;

  case 1153:
#line 5836 "parser.y"
    {
	use_global_ind = 1;
	current_program->flag_global_use = 1;
  ;}
    break;

  case 1154:
#line 5844 "parser.y"
    {
	cb_tree		l;

	for (l = yyvsp[0]; l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			setup_use_file (CB_FILE (cb_ref (CB_VALUE (l))));
		}
	}
  ;}
    break;

  case 1155:
#line 5854 "parser.y"
    {
	current_program->global_handler[COB_OPEN_INPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_INPUT].handler_prog = current_program;
  ;}
    break;

  case 1156:
#line 5859 "parser.y"
    {
	current_program->global_handler[COB_OPEN_OUTPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_OUTPUT].handler_prog = current_program;
  ;}
    break;

  case 1157:
#line 5864 "parser.y"
    {
	current_program->global_handler[COB_OPEN_I_O].handler_label = current_section;
	current_program->global_handler[COB_OPEN_I_O].handler_prog = current_program;
  ;}
    break;

  case 1158:
#line 5869 "parser.y"
    {
	current_program->global_handler[COB_OPEN_EXTEND].handler_label = current_section;
	current_program->global_handler[COB_OPEN_EXTEND].handler_prog = current_program;
  ;}
    break;

  case 1171:
#line 5901 "parser.y"
    {
	PENDING ("USE FOR DEBUGGING");
  ;}
    break;

  case 1174:
#line 5913 "parser.y"
    {
	PENDING ("USE BEFORE REPORTING");
  ;}
    break;

  case 1175:
#line 5924 "parser.y"
    { BEGIN_STATEMENT ("WRITE", TERM_WRITE); ;}
    break;

  case 1176:
#line 5927 "parser.y"
    {
	if (yyvsp[-5] != cb_error_node) {
		cb_emit_write (yyvsp[-5], yyvsp[-4], yyvsp[-2], yyvsp[-3]);
	}
  ;}
    break;

  case 1177:
#line 5935 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1178:
#line 5936 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1179:
#line 5941 "parser.y"
    {
	yyval = cb_int0;
  ;}
    break;

  case 1180:
#line 5945 "parser.y"
    {
	yyval = cb_build_write_advancing_lines (yyvsp[-3], yyvsp[-1]);
  ;}
    break;

  case 1181:
#line 5949 "parser.y"
    {
	yyval = cb_build_write_advancing_mnemonic (yyvsp[-2], yyvsp[0]);
  ;}
    break;

  case 1182:
#line 5953 "parser.y"
    {
	yyval = cb_build_write_advancing_page (yyvsp[-2]);
  ;}
    break;

  case 1183:
#line 5959 "parser.y"
    { yyval = CB_BEFORE; ;}
    break;

  case 1184:
#line 5960 "parser.y"
    { yyval = CB_AFTER; ;}
    break;

  case 1188:
#line 5969 "parser.y"
    { terminator_warning (TERM_WRITE); ;}
    break;

  case 1189:
#line 5970 "parser.y"
    { terminator_clear (TERM_WRITE); ;}
    break;

  case 1190:
#line 5985 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_ACCEPT;
  ;}
    break;

  case 1191:
#line 5993 "parser.y"
    {
	current_statement->handler_id = COB_EC_IMP_DISPLAY;
  ;}
    break;

  case 1193:
#line 6000 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1194:
#line 6004 "parser.y"
    {
	current_statement->handler1 = yyvsp[0];
  ;}
    break;

  case 1196:
#line 6011 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1197:
#line 6015 "parser.y"
    {
	current_statement->handler2 = yyvsp[0];
  ;}
    break;

  case 1198:
#line 6027 "parser.y"
    {
	current_statement->handler_id = COB_EC_SIZE;
  ;}
    break;

  case 1200:
#line 6034 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1201:
#line 6038 "parser.y"
    {
	current_statement->handler1 = yyvsp[0];
  ;}
    break;

  case 1203:
#line 6045 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1204:
#line 6049 "parser.y"
    {
	current_statement->handler2 = yyvsp[0];
  ;}
    break;

  case 1205:
#line 6061 "parser.y"
    {
	current_statement->handler_id = COB_EC_OVERFLOW;
  ;}
    break;

  case 1207:
#line 6068 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1208:
#line 6072 "parser.y"
    {
	current_statement->handler1 = yyvsp[0];
  ;}
    break;

  case 1210:
#line 6079 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1211:
#line 6083 "parser.y"
    {
	current_statement->handler2 = yyvsp[0];
  ;}
    break;

  case 1212:
#line 6095 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = yyvsp[0];
  ;}
    break;

  case 1213:
#line 6100 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler2 = yyvsp[0];
  ;}
    break;

  case 1214:
#line 6105 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = yyvsp[-1];
	current_statement->handler2 = yyvsp[0];
  ;}
    break;

  case 1215:
#line 6114 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1216:
#line 6118 "parser.y"
    {
	yyval = yyvsp[0];
  ;}
    break;

  case 1217:
#line 6125 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1218:
#line 6129 "parser.y"
    {
	yyval = yyvsp[0];
  ;}
    break;

  case 1219:
#line 6141 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = yyvsp[0];
  ;}
    break;

  case 1220:
#line 6146 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler2 = yyvsp[0];
  ;}
    break;

  case 1221:
#line 6151 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = yyvsp[-1];
	current_statement->handler2 = yyvsp[0];
  ;}
    break;

  case 1222:
#line 6160 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1223:
#line 6164 "parser.y"
    {
	yyval = yyvsp[0];
  ;}
    break;

  case 1224:
#line 6171 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1225:
#line 6175 "parser.y"
    {
	yyval = yyvsp[0];
  ;}
    break;

  case 1228:
#line 6191 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = yyvsp[0];
  ;}
    break;

  case 1229:
#line 6196 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler2 = yyvsp[0];
  ;}
    break;

  case 1230:
#line 6201 "parser.y"
    {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = yyvsp[-1];
	current_statement->handler2 = yyvsp[0];
  ;}
    break;

  case 1231:
#line 6210 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1232:
#line 6214 "parser.y"
    {
	yyval = yyvsp[0];
  ;}
    break;

  case 1233:
#line 6221 "parser.y"
    {
	check_unreached = 0;
  ;}
    break;

  case 1234:
#line 6225 "parser.y"
    {
	yyval = yyvsp[0];
  ;}
    break;

  case 1235:
#line 6237 "parser.y"
    {
	yyval = cb_one;
  ;}
    break;

  case 1236:
#line 6241 "parser.y"
    {
	yyval = yyvsp[-1];
  ;}
    break;

  case 1237:
#line 6253 "parser.y"
    {
	yyval = cb_build_cond (yyvsp[0]);
  ;}
    break;

  case 1238:
#line 6260 "parser.y"
    {
	yyval = cb_build_expr (yyvsp[0]);
  ;}
    break;

  case 1239:
#line 6266 "parser.y"
    {
	current_expr = NULL;
  ;}
    break;

  case 1240:
#line 6270 "parser.y"
    {
	yyval = cb_list_reverse (current_expr);
  ;}
    break;

  case 1244:
#line 6282 "parser.y"
    { push_expr ('x', yyvsp[0]); ;}
    break;

  case 1245:
#line 6284 "parser.y"
    { push_expr ('(', NULL); ;}
    break;

  case 1246:
#line 6285 "parser.y"
    { push_expr (')', NULL); ;}
    break;

  case 1247:
#line 6287 "parser.y"
    { push_expr ('+', NULL); ;}
    break;

  case 1248:
#line 6288 "parser.y"
    { push_expr ('-', NULL); ;}
    break;

  case 1249:
#line 6289 "parser.y"
    { push_expr ('*', NULL); ;}
    break;

  case 1250:
#line 6290 "parser.y"
    { push_expr ('/', NULL); ;}
    break;

  case 1251:
#line 6291 "parser.y"
    { push_expr ('^', NULL); ;}
    break;

  case 1252:
#line 6293 "parser.y"
    { push_expr ('=', NULL); ;}
    break;

  case 1253:
#line 6294 "parser.y"
    { push_expr ('>', NULL); ;}
    break;

  case 1254:
#line 6295 "parser.y"
    { push_expr ('<', NULL); ;}
    break;

  case 1255:
#line 6296 "parser.y"
    { push_expr (']', NULL); ;}
    break;

  case 1256:
#line 6297 "parser.y"
    { push_expr ('[', NULL); ;}
    break;

  case 1257:
#line 6298 "parser.y"
    { push_expr ('~', NULL); ;}
    break;

  case 1258:
#line 6300 "parser.y"
    { push_expr ('!', NULL); ;}
    break;

  case 1259:
#line 6301 "parser.y"
    { push_expr ('&', NULL); ;}
    break;

  case 1260:
#line 6302 "parser.y"
    { push_expr ('|', NULL); ;}
    break;

  case 1261:
#line 6304 "parser.y"
    { push_expr ('O', NULL); ;}
    break;

  case 1262:
#line 6305 "parser.y"
    { push_expr ('9', NULL); ;}
    break;

  case 1263:
#line 6306 "parser.y"
    { push_expr ('A', NULL); ;}
    break;

  case 1264:
#line 6307 "parser.y"
    { push_expr ('L', NULL); ;}
    break;

  case 1265:
#line 6308 "parser.y"
    { push_expr ('U', NULL); ;}
    break;

  case 1266:
#line 6311 "parser.y"
    { push_expr ('P', NULL); ;}
    break;

  case 1267:
#line 6312 "parser.y"
    { push_expr ('N', NULL); ;}
    break;

  case 1279:
#line 6324 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 1280:
#line 6325 "parser.y"
    { yyval = cb_list_add (yyvsp[-2], yyvsp[0]); ;}
    break;

  case 1284:
#line 6334 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1285:
#line 6335 "parser.y"
    { yyval = cb_build_binary_op (yyvsp[-2], '+', yyvsp[0]); ;}
    break;

  case 1286:
#line 6336 "parser.y"
    { yyval = cb_build_binary_op (yyvsp[-2], '-', yyvsp[0]); ;}
    break;

  case 1287:
#line 6337 "parser.y"
    { yyval = cb_build_binary_op (yyvsp[-2], '*', yyvsp[0]); ;}
    break;

  case 1288:
#line 6338 "parser.y"
    { yyval = cb_build_binary_op (yyvsp[-2], '/', yyvsp[0]); ;}
    break;

  case 1289:
#line 6339 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1290:
#line 6340 "parser.y"
    { yyval = cb_build_binary_op (cb_zero, '-', yyvsp[0]); ;}
    break;

  case 1291:
#line 6341 "parser.y"
    { yyval = cb_build_binary_op (yyvsp[-2], '^', yyvsp[0]); ;}
    break;

  case 1292:
#line 6342 "parser.y"
    { yyval = yyvsp[-1]; ;}
    break;

  case 1293:
#line 6354 "parser.y"
    {
	if (current_linage > 1) {
		cb_error (_("LINAGE-COUNTER must be qualified here"));
		yyval = cb_error_node;
	} else if (current_linage == 0) {
		cb_error (_("Invalid LINAGE-COUNTER usage"));
		yyval = cb_error_node;
	} else {
		yyval = linage_file->linage_ctr;
	}
  ;}
    break;

  case 1294:
#line 6366 "parser.y"
    {
	if (CB_FILE_P (cb_ref (yyvsp[0]))) {
		yyval = CB_FILE (cb_ref (yyvsp[0]))->linage_ctr;
	} else {
		cb_error_x (yyvsp[0], _("'%s' is not a file name"), CB_NAME (yyvsp[0]));
		yyval = cb_error_node;
	}
  ;}
    break;

  case 1295:
#line 6380 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1296:
#line 6382 "parser.y"
    { yyval = cb_list_append (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 1297:
#line 6386 "parser.y"
    { yyval = cb_build_pair (yyvsp[0], yyvsp[-1]); ;}
    break;

  case 1298:
#line 6392 "parser.y"
    { cb_build_identifier (yyvsp[0]); ;}
    break;

  case 1299:
#line 6399 "parser.y"
    {
	cb_tree x;

	x = cb_ref (yyvsp[0]);
	if (!CB_FIELD_P (x)) {
		yyval = cb_error_node;
	} else if (!CB_FIELD (x)->index_list) {
		cb_error_x (yyvsp[0], _("'%s' not indexed"), cb_name (yyvsp[0]));
		cb_error_x (x, _("'%s' defined here"), cb_name (x));
		yyval = cb_error_node;
	} else {
		yyval = yyvsp[0];
	}
  ;}
    break;

  case 1300:
#line 6419 "parser.y"
    {
	yyval = cb_list_init (yyvsp[0]);
  ;}
    break;

  case 1301:
#line 6423 "parser.y"
    {
	cb_tree		l;

	if (yyvsp[0] != cb_error_node) {
		for (l = yyvsp[-1]; l; l = CB_CHAIN (l)) {
			if (!strcasecmp (CB_NAME (yyvsp[0]), CB_NAME (CB_VALUE (l)))) {
				cb_error_x (yyvsp[0], _("Multiple reference to '%s' "), CB_NAME (yyvsp[0]));
			}
		}
		yyval = cb_list_add (yyvsp[-1], yyvsp[0]);
	}
  ;}
    break;

  case 1302:
#line 6439 "parser.y"
    {
	if (CB_FILE_P (cb_ref (yyvsp[0]))) {
		yyval = yyvsp[0];
	} else {
		cb_error_x (yyvsp[0], _("'%s' is not a file name"), CB_NAME (yyvsp[0]));
		yyval = cb_error_node;
	}
  ;}
    break;

  case 1303:
#line 6452 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 1304:
#line 6454 "parser.y"
    { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 1305:
#line 6458 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1306:
#line 6464 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1307:
#line 6466 "parser.y"
    { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 1308:
#line 6471 "parser.y"
    {
	yyval = yyvsp[0];
	CB_REFERENCE (yyval)->offset = CB_TREE (current_section);
	current_program->label_list = cb_cons (yyval, current_program->label_list);
  ;}
    break;

  case 1312:
#line 6486 "parser.y"
    {
	yyval = cb_build_reference ((char *)(CB_LITERAL (yyvsp[0])->data));
	yyval->source_file = yyvsp[0]->source_file;
	yyval->source_line = yyvsp[0]->source_line;
  ;}
    break;

  case 1313:
#line 6496 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 1314:
#line 6497 "parser.y"
    { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 1315:
#line 6502 "parser.y"
    {
	yyval = yyvsp[0];
	current_program->reference_list = cb_cons (yyval, current_program->reference_list);
  ;}
    break;

  case 1316:
#line 6509 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1317:
#line 6510 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1320:
#line 6522 "parser.y"
    {
	yyval = yyvsp[0];
	if (CB_REFERENCE (yyval)->word->count > 0) {
		redefinition_error (yyval);
		yyval = cb_error_node;
	}
  ;}
    break;

  case 1321:
#line 6541 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 1322:
#line 6542 "parser.y"
    { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 1324:
#line 6547 "parser.y"
    { yyval = cb_build_address (yyvsp[0]); ;}
    break;

  case 1325:
#line 6551 "parser.y"
    { yyval = cb_list_init (yyvsp[0]); ;}
    break;

  case 1326:
#line 6552 "parser.y"
    { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); ;}
    break;

  case 1328:
#line 6557 "parser.y"
    { yyval = cb_build_length (yyvsp[0]); ;}
    break;

  case 1329:
#line 6558 "parser.y"
    { yyval = cb_build_length (yyvsp[0]); ;}
    break;

  case 1330:
#line 6559 "parser.y"
    { yyval = cb_build_length (yyvsp[0]); ;}
    break;

  case 1331:
#line 6560 "parser.y"
    { yyval = cb_build_ppointer (yyvsp[0]); ;}
    break;

  case 1332:
#line 6561 "parser.y"
    { yyval = cb_build_address (yyvsp[0]); ;}
    break;

  case 1337:
#line 6569 "parser.y"
    { yyval = cb_build_length (yyvsp[0]); ;}
    break;

  case 1338:
#line 6570 "parser.y"
    { yyval = cb_build_length (yyvsp[0]); ;}
    break;

  case 1339:
#line 6571 "parser.y"
    { yyval = cb_build_length (yyvsp[0]); ;}
    break;

  case 1345:
#line 6583 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1346:
#line 6584 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1358:
#line 6618 "parser.y"
    { yyval = cb_zero; ;}
    break;

  case 1359:
#line 6626 "parser.y"
    { yyval = cb_build_identifier (yyvsp[0]); ;}
    break;

  case 1360:
#line 6630 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1361:
#line 6631 "parser.y"
    { yyval = yyvsp[-1]; ;}
    break;

  case 1362:
#line 6632 "parser.y"
    { yyval = yyvsp[-1]; ;}
    break;

  case 1363:
#line 6633 "parser.y"
    { yyval = yyvsp[-2]; ;}
    break;

  case 1364:
#line 6637 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1365:
#line 6638 "parser.y"
    { yyval = yyvsp[-2]; CB_REFERENCE (yyvsp[-2])->chain = yyvsp[0]; ;}
    break;

  case 1366:
#line 6643 "parser.y"
    {
	yyval = yyvsp[-3];
	CB_REFERENCE (yyvsp[-3])->subs = cb_list_reverse (yyvsp[-1]);
  ;}
    break;

  case 1367:
#line 6651 "parser.y"
    {
	CB_REFERENCE (yyvsp[-4])->offset = yyvsp[-2];
  ;}
    break;

  case 1368:
#line 6655 "parser.y"
    {
	CB_REFERENCE (yyvsp[-5])->offset = yyvsp[-3];
	CB_REFERENCE (yyvsp[-5])->length = yyvsp[-1];
  ;}
    break;

  case 1369:
#line 6667 "parser.y"
    {
	if (cb_tree_category (yyvsp[0]) != CB_CATEGORY_NUMERIC) {
		cb_error (_("Integer value expected"));
	} else if (CB_LITERAL (yyvsp[0])->sign < 0 || CB_LITERAL (yyvsp[0])->scale) {
		cb_error (_("Integer value expected"));
	}
	yyval = yyvsp[0];
  ;}
    break;

  case 1370:
#line 6678 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1371:
#line 6680 "parser.y"
    {
	yyval = yyvsp[0];
	if (CB_LITERAL_P (yyvsp[0])) {
		CB_LITERAL (yyvsp[0])->all = 1;
	}
  ;}
    break;

  case 1372:
#line 6689 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1373:
#line 6690 "parser.y"
    { yyval = cb_concat_literals (yyvsp[-2], yyvsp[0]); ;}
    break;

  case 1374:
#line 6694 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1375:
#line 6695 "parser.y"
    { yyval = cb_space; ;}
    break;

  case 1376:
#line 6696 "parser.y"
    { yyval = cb_zero; ;}
    break;

  case 1377:
#line 6697 "parser.y"
    { yyval = cb_quote; ;}
    break;

  case 1378:
#line 6698 "parser.y"
    { yyval = cb_high; ;}
    break;

  case 1379:
#line 6699 "parser.y"
    { yyval = cb_low; ;}
    break;

  case 1380:
#line 6700 "parser.y"
    { yyval = cb_null; ;}
    break;

  case 1381:
#line 6709 "parser.y"
    {
	yyval = cb_build_intrinsic (yyvsp[-1], NULL, yyvsp[0]);
  ;}
    break;

  case 1382:
#line 6713 "parser.y"
    {
	yyval = cb_build_intrinsic (yyvsp[-1], NULL, yyvsp[0]);
  ;}
    break;

  case 1383:
#line 6717 "parser.y"
    {
	yyval = cb_build_intrinsic (yyvsp[-4], cb_list_init (yyvsp[-2]), yyvsp[0]);
  ;}
    break;

  case 1384:
#line 6721 "parser.y"
    {
	yyval = cb_build_intrinsic (yyvsp[-4], cb_list_init (yyvsp[-2]), yyvsp[0]);
  ;}
    break;

  case 1385:
#line 6725 "parser.y"
    {
	yyval = cb_build_intrinsic (yyvsp[-4], cb_list_init (yyvsp[-2]), yyvsp[0]);
  ;}
    break;

  case 1386:
#line 6729 "parser.y"
    {
	yyval = cb_build_intrinsic (yyvsp[-4], yyvsp[-2], yyvsp[0]);
  ;}
    break;

  case 1387:
#line 6733 "parser.y"
    {
	yyval = cb_build_intrinsic (yyvsp[-4], yyvsp[-2], yyvsp[0]);
  ;}
    break;

  case 1388:
#line 6737 "parser.y"
    {
	yyval = cb_build_intrinsic (yyvsp[-4], yyvsp[-2], yyvsp[0]);
  ;}
    break;

  case 1389:
#line 6741 "parser.y"
    {
	yyval = cb_build_intrinsic (yyvsp[-4], yyvsp[-2], yyvsp[0]);
  ;}
    break;

  case 1390:
#line 6745 "parser.y"
    {
	yyval = cb_build_intrinsic (yyvsp[-3], yyvsp[-1], NULL);
  ;}
    break;

  case 1391:
#line 6749 "parser.y"
    {
	yyval = cb_build_intrinsic (yyvsp[-4], yyvsp[-2], yyvsp[0]);
  ;}
    break;

  case 1392:
#line 6753 "parser.y"
    {
	yyval = cb_build_intrinsic (yyvsp[-1], yyvsp[0], NULL);
  ;}
    break;

  case 1393:
#line 6759 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1394:
#line 6760 "parser.y"
    { yyval = cb_build_pair (yyvsp[-2], NULL); ;}
    break;

  case 1395:
#line 6761 "parser.y"
    { yyval = cb_build_pair (yyvsp[-3], yyvsp[-1]); ;}
    break;

  case 1396:
#line 6765 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1397:
#line 6766 "parser.y"
    { yyval = yyvsp[-1]; ;}
    break;

  case 1398:
#line 6770 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1399:
#line 6771 "parser.y"
    { yyval = yyvsp[0]; ;}
    break;

  case 1400:
#line 6777 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init (yyvsp[0]);
	yyval = cb_list_add (x, cb_int0);
  ;}
    break;

  case 1401:
#line 6784 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init (yyvsp[-2]);
	yyval = cb_list_add (x, cb_int1);
  ;}
    break;

  case 1402:
#line 6791 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init (yyvsp[-2]);
	yyval = cb_list_add (x, cb_int2);
  ;}
    break;

  case 1403:
#line 6801 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init (yyvsp[0]);
	yyval = cb_list_add (x, cb_null);
  ;}
    break;

  case 1404:
#line 6808 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init (yyvsp[-2]);
	yyval = cb_list_add (x, yyvsp[0]);
  ;}
    break;

  case 1405:
#line 6818 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init (yyvsp[0]);
	yyval = cb_list_add (x, cb_null);
  ;}
    break;

  case 1406:
#line 6825 "parser.y"
    {
	cb_tree	x;

	x = cb_list_init (yyvsp[-2]);
	yyval = cb_list_add (x, cb_ref (yyvsp[0]));
  ;}
    break;

  case 1407:
#line 6838 "parser.y"
    {
	non_const_word = 1;
  ;}
    break;

  case 1408:
#line 6848 "parser.y"
    { yyval = cb_int0; ;}
    break;

  case 1409:
#line 6849 "parser.y"
    { yyval = cb_int1; ;}
    break;

  case 1410:
#line 6853 "parser.y"
    { yyval = cb_int0; ;}
    break;

  case 1411:
#line 6854 "parser.y"
    { yyval = cb_int1; ;}
    break;

  case 1412:
#line 6858 "parser.y"
    { yyval = NULL; ;}
    break;

  case 1413:
#line 6859 "parser.y"
    { yyval = cb_int1; ;}
    break;

  case 1414:
#line 6863 "parser.y"
    { yyval = cb_int0; ;}
    break;

  case 1415:
#line 6864 "parser.y"
    { yyval = cb_int1; ;}
    break;

  case 1416:
#line 6865 "parser.y"
    { yyval = cb_int2; ;}
    break;

  case 1417:
#line 6869 "parser.y"
    { yyval = cb_int0; ;}
    break;

  case 1418:
#line 6870 "parser.y"
    { yyval = cb_int1; ;}
    break;

  case 1419:
#line 6874 "parser.y"
    { yyval = cb_int0; ;}
    break;

  case 1420:
#line 6875 "parser.y"
    { yyval = cb_int1; ;}
    break;

  case 1421:
#line 6879 "parser.y"
    { yyval = cb_int0; ;}
    break;

  case 1422:
#line 6880 "parser.y"
    { yyval = cb_int1; ;}
    break;

  case 1423:
#line 6884 "parser.y"
    { yyval = cb_int0; ;}
    break;

  case 1424:
#line 6885 "parser.y"
    { yyval = cb_int1; ;}
    break;


    }

/* Line 991 of yacc.c.  */
#line 12154 "parser.c"

  yyvsp -= yylen;
  yyssp -= yylen;


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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab2;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:

  /* Suppress GCC warning that yyerrlab1 is unused when no action
     invokes YYERROR.  */
#if defined (__GNUC_MINOR__) && 2093 <= (__GNUC__ * 1000 + __GNUC_MINOR__) \
    && !defined __cplusplus
  __attribute__ ((__unused__))
#endif


  goto yyerrlab2;


/*---------------------------------------------------------------.
| yyerrlab2 -- pop states until the error token can be shifted.  |
`---------------------------------------------------------------*/
yyerrlab2:
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 6941 "parser.y"


