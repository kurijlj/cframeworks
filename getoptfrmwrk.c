/* <one line to give the program's name and a brief idea of what it does.>
 *
 * Copyright (C) <year> Ljubomir Kurij <kurijlj@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.

 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.

 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * <Put documentation here>
 *
 * <yyyy>-<mm>-<dd> Ljubomir Kurij <kurijlj@gmail.com>
 *
 * * <programfilename>.c: created.
 */


/* required by getopt */
#include <getopt.h>
/* required by gettext and others */
#include <libintl.h>
/* required by setlocale */
#include <locale.h>
/* required by stdout */
#include <stdio.h>
/* required by strrchr */
#include <string.h>
/* required by EXIT_SUCCESS */
#include <stdlib.h>


#ifndef APP_NAME
#	define APP_NAME "getoptfrmwrk"
#endif

#ifndef VERSION_STRING
#	define VERSION_STRING "1.0"
#endif

#ifndef YEAR_STRING
#	define YEAR_STRING "yyyy"
#endif

#ifndef AUTHOR_NAME
#	define AUTHOR_NAME "Ljubomir Kurij"
#endif

#ifndef AUTHOR_MAIL
#	define AUTHOR_MAIL "<kurijlj@gmail.com>"
#endif

#ifndef PATH_SEPARATOR
#	define PATH_SEPARATOR '/'
#endif


/**
 * Definitions required for localisation.
 */
#ifndef PACKAGE
#	define PACKAGE APP_NAME
#endif

/* Change this for release version. */
#ifndef LOCALEDIR
#	define LOCALEDIR "./"
#endif

#define _(str) gettext (str)
#define N_(str) (str)


/**
 * Name under which this program was invoked.
 */
const char *exec_name;


static void print_usage(void)
{
	printf(_("Usage: %s [OPTION]...\n"), exec_name);
}

/**
 * Print the help message, describing all the available options. If you add an
 * option, be sure to update this list.
 */
static void print_help(void)
{
	printf(_("%s - framework for application development implementing\n\
getopt option parsing engine.\n"), APP_NAME);
	print_usage();

	printf("%s%s%s%s%s", _("\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
\n"), _("\
Startup:\n\
  -V,  --version           display the version of application and exit.\n\
  -h,  --help              print this help.\n\
\n"), _("Mail bug reports and suggestions to "), AUTHOR_MAIL, ".\n");
}


int main(int argc, char *argv[])
{
	int c; /* holds result of getopt_long call */

	static struct option const long_options[] =
	{
		{"help", no_argument, NULL, 'h'},
		{"version", no_argument, NULL, 'V'},
		{NULL, 0, NULL, 0}
	};

	setlocale (LC_ALL, "");
	bindtextdomain (PACKAGE, LOCALEDIR);
	bind_textdomain_codeset (PACKAGE, "utf-8");
	textdomain (PACKAGE);

	/**
	 * Construct the name of the executable, without the directory part.
	 * The strrchr() function returns a pointer to the last occurrence of
	 * the character in the string.
	 */
	exec_name = strrchr (argv[0], PATH_SEPARATOR);
	if (!exec_name)
		exec_name = argv[0];
	else
		++exec_name;

	while (EOF != (c = getopt_long(argc, argv, "hV", long_options, NULL)))
	{
		switch(c)
		{
			case 'h':
				print_help();
				exit(0);
				break;
			case 'V':
				printf("%s%s%s%s%s%s%s%s", APP_NAME, " ", VERSION_STRING, " \
Copyright (C) ", YEAR_STRING, " ", AUTHOR_NAME, _(".\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\n"));
				exit(0);
				break;
			case '?':
				print_usage();
				printf("\n");
				printf(_("Try `%s --help' for more options.\n"), exec_name);
				exit(0);
				break;
		}
	}

	printf (_("%s: Hello World!\n\n"), exec_name);

	return EXIT_SUCCESS;
}

