/*
 * Copyright (C) 2003-2009 Keisuke Nishida
 * Copyright (C) 2007-2009 Roger While
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, 51 Franklin Street, Fifth Floor
 * Boston, MA 02110-1301 USA
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "cobc.h"
#include "tree.h"

static char	*errnamebuff = NULL;

static void
print_error (char *file, int line, const char *prefix, const char *fmt, va_list ap)
{
	static struct cb_label *last_section = NULL;
	static struct cb_label *last_paragraph = NULL;

	file = file ? file : cb_source_file;
	line = line ? line : cb_source_line;

	/* print the paragraph or section name */
	if (current_section != last_section || current_paragraph != last_paragraph) {
		if (current_paragraph &&
		    strcmp ((const char *)(current_paragraph->name), "MAIN PARAGRAPH")) {
			fprintf (stderr, _("%s: In paragraph '%s':\n"),
				 file, current_paragraph->name);
		} else if (current_section &&
			   strcmp ((const char *)(current_section->name), "MAIN SECTION")) {
				fprintf (stderr, _("%s: In section '%s':\n"),
					file, current_section->name);
		}
		last_section = current_section;
		last_paragraph = current_paragraph;
	}

	/* print the error */
	fprintf (stderr, "%s:%d: %s", file, line, prefix);
	vfprintf (stderr, fmt, ap);
	fputs ("\n", stderr);
}

char *
check_filler_name (char *name)
{
	if (!memcmp (name, "WORK$", 5)) {
		name = (char *)"FILLER";
	}
	return name;
}

void
cb_warning (const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	print_error (NULL, 0, "Warning: ", fmt, ap);
	va_end (ap);

	warningcount++;
}

void
cb_error (const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	print_error (NULL, 0, "Error: ", fmt, ap);
	va_end (ap);

	errorcount++;

}

void
cb_warning_x (cb_tree x, const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	print_error ((char *)(x->source_file), x->source_line, "Warning: ", fmt, ap);
	va_end (ap);

	warningcount++;
}

void
cb_error_x (cb_tree x, const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	print_error ((char *)(x->source_file), x->source_line, "Error: ", fmt, ap);
	va_end (ap);

	errorcount++;
}

int
cb_verify (const enum cb_support tag, const char *feature)
{
	switch (tag) {
	case CB_OK:
		return 1;
	case CB_WARNING:
		return 1;
	case CB_ARCHAIC:
		if (cb_warn_archaic) {
			cb_warning (_("%s is archaic in %s"), feature, cb_config_name);
		}
		return 1;
	case CB_OBSOLETE:
		if (cb_warn_obsolete) {
			cb_warning (_("%s is obsolete in %s"), feature, cb_config_name);
		}
		return 1;
	case CB_SKIP:
		return 0;
	case CB_IGNORE:
		cb_warning (_("%s ignored"), feature);
		return 0;
	case CB_ERROR:
		return 0;
	case CB_UNCONFORMABLE:
		cb_error (_("%s does not conform to %s"), feature, cb_config_name);
		return 0;
	}
	return 0;
}

void
redefinition_error (cb_tree x)
{
	struct cb_word	*w;

	w = CB_REFERENCE (x)->word;
	cb_error_x (x, _("Redefinition of '%s'"), w->name);
	cb_error_x (CB_VALUE (w->items), _("'%s' previously defined here"), w->name);
}

void
redefinition_warning (cb_tree x, cb_tree y)
{
	struct cb_word	*w;

	w = CB_REFERENCE (x)->word;
	cb_warning_x (x, _("Redefinition of '%s'"), w->name);
	if (y) {
		cb_warning_x (y, _("'%s' previously defined here"), w->name);
	} else {
		cb_warning_x (CB_VALUE (w->items), _("'%s' previously defined here"), w->name);
	}
}

void
undefined_error (cb_tree x)
{
	struct cb_reference	*r;
	cb_tree			c;

	if (!errnamebuff) {
		errnamebuff = cobc_malloc (COB_NORMAL_BUFF);
	}
	r = CB_REFERENCE (x);
	snprintf (errnamebuff, COB_NORMAL_MAX, "'%s'", CB_NAME (x));
	for (c = r->chain; c; c = CB_REFERENCE (c)->chain) {
		strcat (errnamebuff, " in '");
		strcat (errnamebuff, CB_NAME (c));
		strcat (errnamebuff, "'");
	}
	cb_error_x (x, _("%s undefined"), errnamebuff);
}

void
ambiguous_error (cb_tree x)
{
	struct cb_word	*w;
	struct cb_field	*p;
	struct cb_label	*l2;
	cb_tree		l;
	cb_tree		y;

	w = CB_REFERENCE (x)->word;
	if (w->error == 0) {
		if (!errnamebuff) {
			errnamebuff = cobc_malloc (COB_NORMAL_BUFF);
		}
		/* display error on the first time */
		snprintf (errnamebuff, COB_NORMAL_MAX, "'%s'", CB_NAME (x));
		for (l = CB_REFERENCE (x)->chain; l; l = CB_REFERENCE (l)->chain) {
			strcat (errnamebuff, " in '");
			strcat (errnamebuff, CB_NAME (l));
			strcat (errnamebuff, "'");
		}
		cb_error_x (x, _("%s ambiguous; need qualification"), errnamebuff);
		w->error = 1;

		/* display all fields with the same name */
		for (l = w->items; l; l = CB_CHAIN (l)) {
			y = CB_VALUE (l);
			snprintf (errnamebuff, COB_NORMAL_MAX, "'%s' ", w->name);
			switch (CB_TREE_TAG (y)) {
			case CB_TAG_FIELD:
				for (p = CB_FIELD (y)->parent; p; p = p->parent) {
					strcat (errnamebuff, "in '");
					strcat (errnamebuff, p->name);
					strcat (errnamebuff, "' ");
				}
				break;
			case CB_TAG_LABEL:
				l2 = CB_LABEL (y);
				if (l2->section) {
					strcat (errnamebuff, "in '");
					strcat (errnamebuff, (const char *)(l2->section->name));
					strcat (errnamebuff, "' ");
				}
				break;
			default:
				break;
			}
			strcat (errnamebuff, _("defined here"));
			cb_error_x (y, errnamebuff);
		}
	}
}

void
group_error (cb_tree x, const char *clause)
{
	cb_error_x (x, _("Group item '%s' cannot have %s clause"), check_filler_name (cb_name (x)), clause);
}

void
level_redundant_error (cb_tree x, const char *clause)
{
	cb_error_x (x, _("Level %02d item '%s' cannot have %s clause"),
		    cb_field (x)->level, check_filler_name (cb_name (x)), clause);
}

void
level_require_error (cb_tree x, const char *clause)
{
	cb_error_x (x, _("Level %02d item '%s' requires %s clause"),
		    cb_field (x)->level, check_filler_name (cb_name (x)), clause);
}

void
level_except_error (cb_tree x, const char *clause)
{
	cb_error_x (x, _("Level %02d item '%s' cannot have other than %s clause"),
		    cb_field (x)->level, check_filler_name (cb_name (x)), clause);
}
