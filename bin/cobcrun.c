/*
 * Copyright (C) 2004-2009 Roger While
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

#include	"config.h"
#include	"defaults.h"

#include	<stdio.h>
#include	<string.h>
#include	<libcob.h>
#include	<tarstamp.h>

static void
print_version (void)
{
	int	year;
	int	day;
	char	buff[64];
	char	month[64];

	memset (buff, 0, sizeof(buff));
	memset (month, 0, sizeof(month));
	day = 0;
	year = 0;
	sscanf (__DATE__, "%s %d %d", month, &day, &year);
	if (day && year) {
		sprintf (buff, "%s %2.2d %4.4d %s", month, day, year, __TIME__);
	} else {
		sprintf (buff, "%s %s", __DATE__, __TIME__);
	}
	printf ("cobcrun (%s) %s.%d\n",
		PACKAGE_NAME, PACKAGE_VERSION, PATCH_LEVEL);
	puts ("Copyright (C) 2004-2009 Roger While");
	printf ("Built    %s\nPackaged %s\n", buff, octardate);
}

static void
print_usage (void)
{
	printf ("Usage: cobcrun PROGRAM [param ...]\n");
	printf ("or   : cobcrun --help (-h)\n");
	printf ("       Print this help\n");
	printf ("or   : cobcrun --version (-V)\n");
	printf ("       Print version information\n");
}

int
main (int argc, char **argv)
{
	union {
		int	(*func)();
		void	*func_void;
	} unifunc;

	if (argc <= 1) {
		print_usage ();
		return 1;
	}
	/* Quick check without getopt */
	if (!strncmp (argv[1], "--version", 10) ||
	    !strncmp (argv[1], "-V", 4)) {
		print_version ();
		return 0;
	}
	if (!strncmp (argv[1], "--help", 10) ||
	    !strncmp (argv[1], "-h", 4)) {
		print_usage ();
		return 0;
	}
	if (strlen (argv[1]) > 31) {
		fprintf (stderr, "Invalid PROGRAM name\n");
		return 1;
	}
	cob_init (argc - 1, &argv[1]);
	unifunc.func_void = cob_resolve (argv[1]);
	if (unifunc.func_void == NULL) {
		cob_call_error ();
	}
	cob_stop_run ( unifunc.func() );
}
