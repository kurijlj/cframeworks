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
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * <Put documentation here>
 *
 * <yyyy>-<mm>-<dd> Ljubomir Kurij <kurijlj@gmail.com>
 *
 * * <programfilename>.c: created.
 */

/* required by argp engine */
#include <argp.h>
/* required by gettext and others */
#include <libintl.h>
/* required by setlocale */
#include <locale.h>
/* required by strrchr */
#include <string.h>
/* required by EXIT_SUCCESS */
#include <stdlib.h>



#ifndef APP_NAME
#	define APP_NAME "argpfrmwrk"
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


void print_version (FILE *stream, struct argp_state *state)
{
	fprintf(stream, "%s%s%s%s%s%s%s%s", APP_NAME, " ", VERSION_STRING, " \
Copyright (C) ", YEAR_STRING, " ", AUTHOR_NAME, _(".\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\n"));
}


/**
 * argp engine initialization. For details wisit page:
 * https://www.gnu.org/software/libc/manual/html_node/Argp.html.
 */
const char *argp_program_version = APP_NAME " " VERSION_STRING;
void (*argp_program_version_hook) () = print_version;
const char *argp_program_bug_address = AUTHOR_MAIL;
static const char doc[] = N_(APP_NAME " - framework for application development implementing\n\
argp option parsing engine.");


static struct argp argp = {0, 0, 0, doc};


int main (int argc, char **argv)
{
	setlocale (LC_ALL, "");
	bindtextdomain (PACKAGE, LOCALEDIR);
	bind_textdomain_codeset (PACKAGE, "utf-8");
	textdomain (PACKAGE);

	argp_parse (&argp, argc, argv, 0, 0, 0);

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

	printf (_("%s: Hello World!\n\n"), exec_name);

	return EXIT_SUCCESS;
}
