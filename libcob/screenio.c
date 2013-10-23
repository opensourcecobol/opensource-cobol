/*
 * Copyright (C) 2001-2009 Keisuke Nishida
 * Copyright (C) 2007-2009 Roger While
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1,
 * or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see the file COPYING.LIB.  If
 * not, write to the Free Software Foundation, 51 Franklin Street, Fifth Floor
 * Boston, MA 02110-1301 USA
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef	HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_NCURSES_H
#include <ncurses.h>
#define COB_GEN_SCREENIO
#elif defined(HAVE_NCURSES_NCURSES_H)
#include <ncurses/ncurses.h>
#define COB_GEN_SCREENIO
#elif defined(HAVE_PDCURSES_H)
#include <pdcurses.h>
#define COB_GEN_SCREENIO
#elif defined(HAVE_CURSES_H)
#include <curses.h>
#define COB_GEN_SCREENIO
#endif

#include "move.h"
#include "coblocal.h"
#include "screenio.h"

/* Global variables */

int	cob_screen_initialized = 0;
int	cob_screen_mode = 0;

#ifdef COB_GEN_SCREENIO

struct cob_inp_struct {
	cob_screen	*scr;
	size_t		up_index;
	size_t		down_index;
	int		this_y;
	int		this_x;
};

#define	COB_INP_SIZE	1920 * sizeof(struct cob_inp_struct)

/* Local variables */

static struct cob_inp_struct	*cob_base_inp = NULL;
static size_t			curr_index = 0;
static size_t			totl_index = 0;
static size_t			cob_has_color = 0;
static size_t			cob_extended_status = 0;
static size_t			cob_use_esc = 0;
static int			global_return;
static int			cob_current_y = 0;
static int			cob_current_x = 0;
static int			cob_max_y = 0;
static int			cob_max_x = 0;
static short			fore_color;
static short			back_color;

/* Local functions */

static void
get_line_column (cob_field *fline, cob_field *fcol, int *line, int *col)
{
	int	l;
	int	c;
	int	p;

	if (fline == NULL) {
		*line = 0;
		*col = 0;
		return;
	}

	p = cob_get_int (fline);

	if (fcol == NULL) {
		if (fline->size == 4) {
			l = p / 100;
			c = p % 100;
		} else {
			l = p / 1000;
			c = p % 1000;
		}
	} else {
		l = p;
		c = cob_get_int (fcol);
	}
	if (l > 0) {
		l--;
	}
	if (c > 0) {
		c--;
	}
	*line = l;
	*col = c;
}

static void
cob_screen_attr (cob_field *fgc, cob_field *bgc, const int attr)
{
	size_t		i;
	int		styles = 0;
	int		line;
	int		column;
	short		fgcolor;
	short		bgcolor;
	short		fgdef;
	short		bgdef;

	attrset (A_NORMAL);
	if (attr & COB_SCREEN_REVERSE) {
		styles |= A_REVERSE;
	}
	if (attr & COB_SCREEN_HIGHLIGHT) {
		styles |= A_BOLD;
	}
	if (attr & COB_SCREEN_BLINK) {
		styles |= A_BLINK;
	}
	if (attr & COB_SCREEN_UNDERLINE) {
		styles |= A_UNDERLINE;
	}
	if (styles) {
		attron (styles);
	}
	if (cob_has_color) {
		fgcolor = fore_color;
		bgcolor = back_color;
		if (fgc) {
			switch (cob_get_int (fgc)) {
			case COB_SCREEN_BLACK:
				fgcolor = COLOR_BLACK;
				break;
			case COB_SCREEN_BLUE:
				fgcolor = COLOR_BLUE;
				break;
			case COB_SCREEN_GREEN:
				fgcolor = COLOR_GREEN;
				break;
			case COB_SCREEN_CYAN:
				fgcolor = COLOR_CYAN;
				break;
			case COB_SCREEN_RED:
				fgcolor = COLOR_RED;
				break;
			case COB_SCREEN_MAGENTA:
				fgcolor = COLOR_MAGENTA;
				break;
			case COB_SCREEN_YELLOW:
				fgcolor = COLOR_YELLOW;
				break;
			case COB_SCREEN_WHITE:
				fgcolor = COLOR_WHITE;
				break;
			default:
				break;
			}
		}
		if (bgc) {
			switch (cob_get_int (bgc)) {
			case COB_SCREEN_BLACK:
				bgcolor = COLOR_BLACK;
				break;
			case COB_SCREEN_BLUE:
				bgcolor = COLOR_BLUE;
				break;
			case COB_SCREEN_GREEN:
				bgcolor = COLOR_GREEN;
				break;
			case COB_SCREEN_CYAN:
				bgcolor = COLOR_CYAN;
				break;
			case COB_SCREEN_RED:
				bgcolor = COLOR_RED;
				break;
			case COB_SCREEN_MAGENTA:
				bgcolor = COLOR_MAGENTA;
				break;
			case COB_SCREEN_YELLOW:
				bgcolor = COLOR_YELLOW;
				break;
			case COB_SCREEN_WHITE:
				bgcolor = COLOR_WHITE;
				break;
			default:
				break;
			}
		}
		for (i = 0; i < (size_t)COLOR_PAIRS; i++) {
			pair_content ((short)i, &fgdef, &bgdef);
			if (fgdef == fgcolor && bgdef == bgcolor) {
				break;
			}
			if (fgdef == 0 && bgdef == 0) {
				init_pair ((short)i, fgcolor, bgcolor);
				break;
			}
		}
		if (i != (size_t)COLOR_PAIRS) {
#ifdef	HAVE_COLOR_SET
			color_set (COLOR_PAIR(i), (void *)0);
#else
			attrset (COLOR_PAIR(i));
#endif
			bkgdset (COLOR_PAIR(i));
		} else {
			attrset (A_NORMAL);
		}
	}
	if (attr & COB_SCREEN_BLANK_SCREEN) {
		getyx (stdscr, line, column);
		clear ();
		move (line, column);
	}
	if (attr & COB_SCREEN_BLANK_LINE) {
		getyx (stdscr, line, column);
		move (line, 0);
		clrtoeol ();
		move (line, column);
	}
	if (attr & COB_SCREEN_ERASE_EOL) {
		clrtoeol ();
	}
	if (attr & COB_SCREEN_ERASE_EOS) {
		clrtobot ();
	}
	if (attr & COB_SCREEN_BELL) {
		beep ();
	}
}

static void COB_NOINLINE
cob_screen_init (void)
{
	char	*s;

	if (!cob_screen_initialized) {
		s = getenv ("COB_SCREEN_EXCEPTIONS");
		if (s) {
			if (*s == 'Y' || *s == 'y') {
				cob_extended_status = 1;
				s = getenv ("COB_SCREEN_ESC");
				if (s) {
					if (*s == 'Y' || *s == 'y') {
							cob_use_esc = 1;
					}
				}
			}
		}
		fflush (stdout);
		fflush (stderr);
		if (!initscr ()) {
			cob_runtime_error ("Failed to initialize curses");
			cob_stop_run (1);
		}
		cbreak ();
		keypad (stdscr, 1);
		nl ();
		noecho ();
		if (has_colors ()) {
			start_color ();
			pair_content ((short)0, &fore_color, &back_color);
			if (COLOR_PAIRS) {
				cob_has_color = 1;
			}
		}
		attrset (A_NORMAL);
		getmaxyx (stdscr, cob_max_y, cob_max_x);
		cob_screen_initialized = 1;
	}
}

void
cob_screen_terminate (void)
{
	if (cob_screen_initialized) {
		cob_screen_initialized = 0;
		endwin ();
	}
}

static void COB_NOINLINE
cob_check_pos_status (int fret)
{
	cob_field	*f;
	int		sline;
	int		scolumn;
	char		datbuf[8];

	if (fret) {
		cob_set_exception (COB_EC_IMP_ACCEPT);
	}
	if (cob_current_module->crt_status) {
		if (COB_FIELD_IS_NUMERIC (cob_current_module->crt_status)) {
			cob_set_int (cob_current_module->crt_status, fret);
		} else {
			sprintf(datbuf, "%4.4d", fret);
			memcpy (cob_current_module->crt_status->data, datbuf, 4);
		}
	}
	if (cob_current_module->cursor_pos) {
		getyx (stdscr, sline, scolumn);
		f = cob_current_module->cursor_pos;
		if (COB_FIELD_IS_NUMERIC (f) &&
		    COB_FIELD_TYPE (f) != COB_TYPE_NUMERIC_DISPLAY) {
			sline *= 1000;
			sline += scolumn;
			cob_set_int (f, sline);
		} else {
			if (f->size < 6) {
				sline *= 100;
				sline += scolumn;
				sprintf(datbuf, "%4.4d", sline);
				memcpy (f->data, datbuf, 4);
			} else {
				sline *= 1000;
				sline += scolumn;
				sprintf(datbuf, "%6.6d", sline);
				memcpy (f->data, datbuf, 6);
			}
		}
	}
}

static void
cob_screen_puts (cob_screen *s, cob_field *f)
{
	unsigned char	*p;
	size_t		size;
	int		y;
	int		x;
	int		line;
	int		column;

	getyx (stdscr, y, x);
	if (!s->line) {
		line = y;
	} else {
		line = cob_get_int (s->line) - 1;
		if (line < 0) {
			line = y;
		}
	}
	if (!s->column) {
		column = x;
	} else {
		column = cob_get_int (s->column) - 1;
		if (column < 0) {
			column = x;
		}
	}
	if (s->attr & COB_SCREEN_LINE_PLUS) {
		line = y + line + 1;
	} else if (s->attr & COB_SCREEN_LINE_MINUS) {
		line = y - line + 1;
	}
	if (s->attr & COB_SCREEN_COLUMN_PLUS) {
		column = x + column + 1;
	} else if (s->attr & COB_SCREEN_COLUMN_MINUS) {
		column = x - column + 1;
	}
	move (line, column);
	cob_current_y = line;
	cob_current_x = column;
	cob_screen_attr (s->foreg, s->backg, s->attr);
	if (s->attr & COB_SCREEN_INPUT) {
		p = f->data;
		for (size = 0; size < f->size; size++, p++) {
			if (s->attr & COB_SCREEN_SECURE) {
				addch ('*');
			} else if (*p <= ' ') {
				addch ('_');
			} else {
				addch (*p);
			}
		}
	} else {
		addnstr ((char *)f->data, (int)f->size);
	}
	refresh ();
}

static void
cob_screen_get_all (void)
{
	struct cob_inp_struct	*sptr;
	cob_screen		*s;
	unsigned char		*p;
	int			keyp;
	int			sline;
	int			scolumn;
	int			cline;
	int			ccolumn;
	int			rightpos;
	int			ateof;
	int			gotbacksp;
	int			ungetched;

	sptr = cob_base_inp;
	s = sptr->scr;
	sline = sptr->this_y;
	scolumn = sptr->this_x;
	move (sline, scolumn);
	cob_screen_attr (s->foreg, s->backg, s->attr);
/* RXW
	p = s->field->data;
	for (count = 0; count < s->field->size; count++) {
		if (s->attr & COB_SCREEN_UPDATE) {
			keyp = *p++;
			addch (keyp);
		} else if (s->attr & COB_SCREEN_PROMPT) {
			addch ('_');
		} else {
			addch (' ');
		}
	}
	move (sline, scolumn);
*/
	ateof = 0;
	gotbacksp = 0;
	ungetched = 0;
	rightpos = scolumn + s->field->size - 1;
	p = s->field->data;
	for (; ;) {
		refresh ();
		keyp = getch ();
		if (keyp == KEY_ENTER || keyp == '\n') {
			break;
		}
		if (keyp > KEY_F0 && keyp < KEY_F(65)) {
			global_return = 1000 + keyp - KEY_F0;
			break;
		}
		if (cob_extended_status) {
			if (keyp == KEY_PPAGE) {
				global_return = 2001;
				break;
			}
			if (keyp == KEY_NPAGE) {
				global_return = 2002;
				break;
			}
			if (keyp == KEY_PRINT) {
				global_return = 2006;
				break;
			}
			if (cob_use_esc) {
				if (keyp == 033) {
					global_return = 2005;
					break;
				}
			}
		}
		if (keyp == 011) {
			if (curr_index < totl_index - 1) {
				curr_index++;
			} else {
				curr_index = 0;
			}
			sptr = cob_base_inp + curr_index;
			s = sptr->scr;
			sline = sptr->this_y;
			scolumn = sptr->this_x;
			ateof = 0;
			gotbacksp = 0;
			rightpos = scolumn + s->field->size - 1;
			p = s->field->data;
			move (sline, scolumn);
			cob_screen_attr (s->foreg, s->backg, s->attr);
			continue;
		}
		if (keyp == KEY_BTAB) {
			if (curr_index > 0) {
				curr_index--;
			} else {
				curr_index = totl_index - 1;
			}
			sptr = cob_base_inp + curr_index;
			s = sptr->scr;
			sline = sptr->this_y;
			scolumn = sptr->this_x;
			ateof = 0;
			gotbacksp = 0;
			rightpos = scolumn + s->field->size - 1;
			if (ungetched) {
				ungetched = 0;
				p = s->field->data + rightpos;
				move (sline, rightpos);
			} else {
				p = s->field->data;
				move (sline, scolumn);
			}
			cob_screen_attr (s->foreg, s->backg, s->attr);
			continue;
		}
		if (keyp == KEY_UP) {
			curr_index = sptr->up_index;
			sptr = cob_base_inp + curr_index;
			s = sptr->scr;
			sline = sptr->this_y;
			scolumn = sptr->this_x;
			ateof = 0;
			gotbacksp = 0;
			rightpos = scolumn + s->field->size - 1;
			p = s->field->data;
			move (sline, scolumn);
			cob_screen_attr (s->foreg, s->backg, s->attr);
			continue;
		}
		if (keyp == KEY_DOWN) {
			curr_index = sptr->down_index;
			sptr = cob_base_inp + curr_index;
			s = sptr->scr;
			sline = sptr->this_y;
			scolumn = sptr->this_x;
			ateof = 0;
			gotbacksp = 0;
			rightpos = scolumn + s->field->size - 1;
			p = s->field->data;
			move (sline, scolumn);
			cob_screen_attr (s->foreg, s->backg, s->attr);
			continue;
		}
		if (keyp == KEY_HOME) {
			curr_index = 0;
			sptr = cob_base_inp;
			s = sptr->scr;
			sline = sptr->this_y;
			scolumn = sptr->this_x;
			ateof = 0;
			gotbacksp = 0;
			rightpos = scolumn + s->field->size - 1;
			p = s->field->data;
			move (sline, scolumn);
			cob_screen_attr (s->foreg, s->backg, s->attr);
			continue;
		}
		if (keyp == KEY_END) {
			curr_index = totl_index - 1;
			sptr = cob_base_inp + curr_index;
			s = sptr->scr;
			sline = sptr->this_y;
			scolumn = sptr->this_x;
			ateof = 0;
			gotbacksp = 0;
			rightpos = scolumn + s->field->size - 1;
			p = s->field->data;
			move (sline, scolumn);
			cob_screen_attr (s->foreg, s->backg, s->attr);
			continue;
		}
		getyx (stdscr, cline, ccolumn);
		if (keyp == KEY_BACKSPACE || keyp == ('H' & 037) ||
		    keyp == 0177) {
			if (ccolumn > scolumn) {
				if (gotbacksp || ccolumn != rightpos) {
					ccolumn--;
				} else {
					ateof = 0;
				}
				gotbacksp = 1;
				move (cline, ccolumn);
				if (s->attr & COB_SCREEN_SECURE) {
					addch ('*');
				} else {
					addch ('_');
				}
				move (cline, ccolumn);
				p = s->field->data + ccolumn - scolumn;
				*p = ' ';
			} else {
				ungetched = 1;
				gotbacksp = 0;
				ungetch (KEY_BACKSPACE);
				ungetch (KEY_BTAB);
			}
			continue;
		}
		if (keyp == KEY_LEFT) {
			gotbacksp = 0;
			if (ccolumn > scolumn) {
				ccolumn--;
				move (cline, ccolumn);
				p = s->field->data + ccolumn - scolumn;
			} else {
				ungetched = 1;
				ungetch (KEY_BTAB);
			}
			continue;
		}
		if (keyp == KEY_RIGHT) {
			gotbacksp = 0;
			if (ccolumn < rightpos) {
				ccolumn++;
				move (cline, ccolumn);
				p = s->field->data + ccolumn - scolumn;
			} else {
				ungetch (011);
			}
			continue;
		}
		if (keyp > 037 && keyp < (int)A_CHARTEXT) {
			if (COB_FIELD_IS_NUMERIC (s->field)) {
				if (keyp < '0' || keyp > '9') {
					beep ();
					continue;
				}
			}
			gotbacksp = 0;
			*p = keyp;
			if (s->attr & COB_SCREEN_SECURE) {
				addch ('*');
			} else {
				addch ((unsigned int)keyp);
			}
			if (ccolumn == rightpos) {
				if (s->attr & COB_SCREEN_AUTO) {
					if (curr_index == totl_index - 1) {
						break;
					} else {
						ungetch (011);
					}
				}
				move (cline, ccolumn);
				if (ateof) {
					beep ();
				} else {
					ateof = 1;
				}
			} else {
				p++;
			}
			continue;
		}
		gotbacksp = 0;
		beep ();
	}
	refresh ();
}

static int
compare_yx (const void *m1, const void *m2)
{
	const struct cob_inp_struct	*s1;
	const struct cob_inp_struct	*s2;

	s1 = m1;
	s2 = m2;
	if (s1->this_y < s2->this_y) {
		return -1;
	}
	if (s1->this_y > s2->this_y) {
		return 1;
	}
	if (s1->this_x < s2->this_x) {
		return -1;
	}
	if (s1->this_x > s2->this_x) {
		return 1;
	}
	return 0;
}

static void
cob_prep_input (cob_screen *s)
{
	struct cob_inp_struct	*sptr;
	int			n;

	switch (s->type) {
	case COB_SCREEN_TYPE_GROUP:
		for (s = s->child; s; s = s->next) {
			cob_prep_input (s);
		}
		break;
	case COB_SCREEN_TYPE_FIELD:
		cob_screen_puts (s, s->field);
		if (s->attr & COB_SCREEN_INPUT) {
			sptr = cob_base_inp + totl_index;
			sptr->scr = s;
			sptr->this_y = cob_current_y;
			sptr->this_x = cob_current_x;
			totl_index++;
		}
		break;
	case COB_SCREEN_TYPE_VALUE:
		cob_screen_puts (s, s->value);
		if (s->occurs) {
			for (n = 1; n < s->occurs; ++n) {
				cob_screen_puts (s, s->value);
			}
		}
		break;
	case COB_SCREEN_TYPE_ATTRIBUTE:
		cob_screen_attr (s->foreg, s->backg, s->attr);
		break;
	}
}

/* Global functions */

void
cob_screen_display (cob_screen *s, cob_field *line, cob_field *column)
{
	int	n;

	if (!cob_screen_initialized) {
		cob_screen_init ();
	}

	switch (s->type) {
	case COB_SCREEN_TYPE_GROUP:
		for (s = s->child; s; s = s->next) {
			cob_screen_display (s, line, column);
		}
		break;
	case COB_SCREEN_TYPE_FIELD:
		cob_screen_puts (s, s->field);
		break;
	case COB_SCREEN_TYPE_VALUE:
		cob_screen_puts (s, s->value);
		if (s->occurs) {
			for (n = 1; n < s->occurs; ++n) {
				cob_screen_puts (s, s->value);
			}
		}
		break;
	case COB_SCREEN_TYPE_ATTRIBUTE:
		cob_screen_attr (s->foreg, s->backg, s->attr);
		break;
	}
	refresh ();
}

void
cob_screen_accept (cob_screen *s, cob_field *line, cob_field *column)
{
	struct cob_inp_struct	*sptr;
	struct cob_inp_struct	*sptr2;
	size_t			idx;
	size_t			n;
	size_t			posu;
	size_t			posd;
	size_t			prevy;
	size_t			firsty;
	int			starty;

	if (!cob_screen_initialized) {
		cob_screen_init ();
	}
	if (!cob_base_inp) {
		cob_base_inp = cob_malloc (COB_INP_SIZE);
	} else {
		memset (cob_base_inp, 0, COB_INP_SIZE);
	}
	cob_exception_code = 0;
	cob_current_y = 0;
	cob_current_x = 0;
	totl_index = 0;
	move (0, 0);
	cob_prep_input (s);
	/* No input fields is an error */
	if (!totl_index) {
		cob_check_pos_status (8000);
		return;
	}
	qsort (cob_base_inp, totl_index, sizeof(struct cob_inp_struct), compare_yx);
	sptr = cob_base_inp;
	starty = sptr->this_y;
	posu = 0;
	posd = 0;
	prevy = 0;
	firsty = 0;
	/* Set up array for Cursor UP/DOWN */
	for (n = 0; n < totl_index; n++) {
		sptr = cob_base_inp + n;
		if (sptr->this_y > starty) {
			if (!firsty) {
				firsty = n;
			}
			starty = sptr->this_y;
			sptr2 = cob_base_inp + posd;
			for (idx = posd; idx < n; idx++, sptr2++) {
				sptr2->down_index = n;
			}
			posu = prevy;
			prevy = n;
			posd = n;
		}
		sptr->up_index = posu;
	}
	sptr = cob_base_inp;
	for (n = 0; n < firsty; n++, sptr++) {
		sptr->up_index = posd;
	}
	curr_index = 0;
	global_return = 0;
	cob_screen_get_all ();
	cob_check_pos_status (global_return);
}

void
cob_field_display (cob_field *f, cob_field *line, cob_field *column,
		   cob_field *fgc, cob_field *bgc, cob_field *scroll,
		   const int attr)
{
	int sline;
	int scolumn;

	if (!cob_screen_initialized) {
		cob_screen_init ();
	}

	if (scroll) {
		sline = cob_get_int (scroll);
		if (attr & COB_SCREEN_SCROLL_DOWN) {
			sline = -sline;
		}
		scrollok (stdscr, 1);
		scrl (sline);
		scrollok (stdscr, 0);
		refresh ();
	}
	get_line_column (line, column, &sline, &scolumn);
	move (sline, scolumn);
	cob_screen_attr (fgc, bgc, attr);
	addnstr ((char *)f->data, (int)f->size);
	refresh ();
}

void
cob_field_accept (cob_field *f, cob_field *line, cob_field *column,
		  cob_field *fgc, cob_field *bgc, cob_field *scroll,
		  const int attr)
{
	unsigned char	*p;
	size_t		count;
	int		keyp;
	int		fret;
	int		sline;
	int		scolumn;
	int		cline;
	int		ccolumn;
	int		rightpos;
	int		ateof;
	int		gotbacksp;

	if (!cob_screen_initialized) {
		cob_screen_init ();
	}

	if (scroll) {
		keyp = cob_get_int (scroll);
		if (attr & COB_SCREEN_SCROLL_DOWN) {
			keyp = -keyp;
		}
		scrollok (stdscr, 1);
		scrl (keyp);
		scrollok (stdscr, 0);
		refresh ();
	}
	cob_exception_code = 0;
	get_line_column (line, column, &sline, &scolumn);
	move (sline, scolumn);
	cob_screen_attr (fgc, bgc, attr);
	p = f->data;
	for (count = 0; count < f->size; count++) {
		if (attr & COB_SCREEN_SECURE) {
			addch ('*');
		} else if (attr & COB_SCREEN_UPDATE) {
			fret = *p++;
			addch ((unsigned int)fret);
		} else if (attr & COB_SCREEN_PROMPT) {
			addch ('_');
		} else {
			addch (' ');
		}
	}
	move (sline, scolumn);
	if (!(attr & COB_SCREEN_UPDATE)) {
		if (COB_FIELD_IS_NUMERIC (f)) {
			cob_move (&cob_zero, f);
		} else {
			memset (f->data, ' ', f->size);
		}
	}

	fret = 0;
	ateof = 0;
	gotbacksp = 0;
	rightpos = scolumn + f->size - 1;
	p = f->data;
	for (; ;) {
		refresh ();
		keyp = getch ();
		if (keyp == KEY_ENTER || keyp == '\n') {
			break;
		}
		if (keyp > KEY_F0 && keyp < KEY_F(65)) {
			fret = 1000 + keyp - KEY_F0;
			break;
		}
		if (cob_extended_status) {
			if (keyp == KEY_PPAGE) {
				fret = 2001;
				break;
			}
			if (keyp == KEY_NPAGE) {
				fret = 2002;
				break;
			}
			if (keyp == KEY_UP) {
				fret = 2003;
				break;
			}
			if (keyp == KEY_DOWN) {
				fret = 2004;
				break;
			}
			if (keyp == KEY_PRINT) {
				fret = 2006;
				break;
			}
			if (cob_use_esc) {
				if (keyp == 033) {
					fret = 2005;
					break;
				}
			}
		}
		getyx (stdscr, cline, ccolumn);
		if (keyp == KEY_BACKSPACE || keyp == ('H' & 037) ||
		    keyp == 0177) {
			if (ccolumn > scolumn) {
				if (gotbacksp || ccolumn != rightpos) {
					ccolumn--;
				} else {
					ateof = 0;
				}
				gotbacksp = 1;
				move (cline, ccolumn);
				if (attr & COB_SCREEN_SECURE) {
					addch ('*');
				} else {
					addch ('_');
				}
				move (cline, ccolumn);
				p = f->data + ccolumn - scolumn;
				*p = ' ';
				continue;
			}
		}
		if (keyp == KEY_HOME) {
			move (sline, scolumn);
			p = f->data;
			ateof = 0;
			gotbacksp = 0;
			continue;
		}
		if (keyp == KEY_END) {
			move (sline, rightpos);
			p = f->data + f->size - 1;
			ateof = 0;
			gotbacksp = 0;
			continue;
		}
		if (keyp == KEY_LEFT) {
			if (ccolumn > scolumn) {
				ccolumn--;
				move (cline, ccolumn);
				p = f->data + ccolumn - scolumn;
				continue;
			}
			gotbacksp = 0;
		}
		if (keyp == KEY_RIGHT) {
			if (ccolumn < rightpos) {
				ccolumn++;
				move (cline, ccolumn);
				p = f->data + ccolumn - scolumn;
				continue;
			}
			gotbacksp = 0;
		}
		if (keyp > 037 && keyp < (int)A_CHARTEXT) {
			if (COB_FIELD_IS_NUMERIC (f)) {
				if (keyp < '0' || keyp > '9') {
					beep ();
					continue;
				}
			}
			gotbacksp = 0;
			*p = keyp;
			if (attr & COB_SCREEN_SECURE) {
				addch ('*');
			} else {
				addch ((unsigned int)keyp);
			}
			if (ccolumn == rightpos) {
				if (attr & COB_SCREEN_AUTO) {
					break;
				}
				move (cline, ccolumn);
				if (ateof) {
					beep ();
				} else {
					ateof = 1;
				}
			} else {
				p++;
			}
			continue;
		}
		gotbacksp = 0;
		beep ();
	}
	cob_check_pos_status (fret);
	refresh ();
}

void
cob_screen_line_col (cob_field *f, const int l_or_c)
{
	if (!cob_screen_initialized) {
		cob_screen_init ();
	}
	if (!l_or_c) {
		cob_set_int (f, (int)LINES);
	} else {
		cob_set_int (f, (int)COLS);
	}
}

void
cob_screen_set_mode (const size_t smode)
{
	if (!smode) {
		refresh ();
		def_prog_mode ();
		endwin ();
	} else {
		reset_prog_mode ();
		refresh ();
	}
}

#else

void
cob_screen_terminate (void)
{
}

void
cob_field_display (cob_field *f, cob_field *line, cob_field *column,
		   cob_field *fgc, cob_field *bgc, const int attr)
{
}

void
cob_field_accept (cob_field *f, cob_field *line, cob_field *column,
		  cob_field *fgc, cob_field *bgc, const int attr)
{
}

void
cob_screen_display (cob_screen *s, cob_field *line, cob_field *column)
{
}

void
cob_screen_accept (cob_screen *s, cob_field *line, cob_field *column)
{
}

void
cob_screen_line_col (cob_field *f, const int l_or_c)
{
}

void
cob_screen_set_mode (const size_t smode)
{
}

#endif
