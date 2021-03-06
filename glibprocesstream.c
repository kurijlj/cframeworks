/* <one line to give the program's name and a brief idea of what it does.>
 *
 *  Copyright (C) 2015 Ljubomir Kurij <kurijlj@gmail.com>
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


/**
 * Libraries required by framework.
 */
/* required by glib's function calls */
#include <glib.h>
/* required by _() and N_() macros */
#include <glib/gi18n.h>
/* required by g_strrstr */
#include <glib/gprintf.h>
/* required by g_fopen */
#include <glib/gstdio.h>
/* required by gettext and others */
#include <libintl.h>
/* required by setlocale */
#include <locale.h>
/* required by EXIT_SUCCESS */
#include <stdlib.h>


#ifndef APP_NAME
#	define APP_NAME "glibprocesstream"
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
#	define PATH_SEPARATOR "/"
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


/**
 * GOption engine global variables declaration/definition.
 */
static GOptionContext *gcontext;
static gchar          *summary;
static gchar          *description;


/**
 * GOption engine command line options definition.
 */
static gboolean      version   = FALSE;
/**
 * NOTE: All dynamically allocated memory must be released before calling
 *       cleanup_goption () or inside it.
 */
static gchar        *filename    = (gchar *) NULL;

static GOptionEntry  entries[] =
{
	{
		"version",
		'V',
		0,
		G_OPTION_ARG_NONE,
		&version,
		N_("Print version information and then exit."),
		NULL
	},
	{
		"file-to-read",
		'f',
		0,
		G_OPTION_ARG_FILENAME,
		&filename,
		N_("Input file argument example."),
		N_("INPUT_FILE")
	},
	{ NULL }
};


/**
 * Name under which this program was invoked.
 */
gchar *exec_name;


/**
 * init_goption - Initializes GOption engine.
 */
static gboolean
init_goption (gint *argc, gchar ***argv, GError **gerr)
{
	summary = g_strdup_printf(_("Application summary goes here.\n"));
	description = g_strdup_printf(_("Report bugs to: %s\n"), AUTHOR_MAIL);

	gcontext = g_option_context_new (_("- framework for application development \
implementing GNOME GLib."));
	g_option_context_add_main_entries (gcontext, entries, PACKAGE);
	g_option_context_set_summary (gcontext, summary);
	g_option_context_set_description (gcontext, description);

	if (!g_option_context_parse (gcontext, argc, argv, gerr))
	{
		return FALSE;
	}

	return TRUE;
}


/**
 * cleanup_goption - Cleanup GOption engine.
 */
static void
cleanup_goption (void)
{
	if ((GOptionContext *) NULL != gcontext)
		g_option_context_free (gcontext);
	if ((gchar *) NULL != summary)
		g_free (summary);
	if ((gchar *) NULL != description)
		g_free (description);
	if ((gchar *) NULL != filename)
		g_free (filename);
}


/**
 * print_version - Prints version information for application.
 */
static void
print_version (void)
{
	g_print ("%s%s%s%s%s%s%s%s", APP_NAME, " ", VERSION_STRING, " \
Copyright (C) ", YEAR_STRING, " ", AUTHOR_NAME, _(".\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\n"));
}


/**
 * reset_gerror - Releases memory allocated at sets pointer to NULL.
 */
static void
reset_gerror (GError **gerr)
{
	if ((GError *) NULL != *gerr)
	{
		g_error_free (*gerr);
		*gerr = (GError *) NULL;
	}
}


/**
 * process_stream - Sample function for processing input stream line by line.
 */
void
process_stream (FILE *s)
{
	gchar *l = NULL; /* Pointer to buffer holding line. */
	gchar *p;        /* Pointer to new line character at end of line. */
	gsize n  = 0;    /* Size of buffer holding line in bytes. */

	while (-1 != getline(&l, &n, s))
	{
		/* Remove newline at the end of line. */
		p = l + strcspn (l, "\n");
		if ('\n' == p[0])
			p[0] = '\0';

		g_print ("%s\n", l);

		g_free (l);
		l = NULL;
		n = 0;
	}


	g_free (l);
}


/**
 * Program main function.
 */
int
main (int argc, char *argv[])
{
	GError *gerror = (GError *) NULL;

	/**
	 * Construct the name of the executable, without the directory part.
	 * The strrchr() function returns a pointer to the last occurrence of
	 * the character in the string.
	 */
	exec_name = g_strrstr (argv[0], PATH_SEPARATOR);
	if (!exec_name)
		exec_name = argv[0];
	else
		++exec_name;

	/**
	 * Enable native language support.
	 */
	setlocale (LC_ALL, "");
	bindtextdomain (PACKAGE, LOCALEDIR);
	bind_textdomain_codeset(PACKAGE, "utf-8");
	textdomain (PACKAGE);

	/**
	 * Initialize GOption engine.
	 */
	if (!init_goption (&argc, &argv, &gerror))
	{
		g_printerr (_("%s: cannot initialize : %s\n"),
			exec_name,
			gerror->message);
		reset_gerror (&gerror);
		goto exit;
	}

	/**
	 * If user typed in version parameter display version information and
	 * bail out.
	 */
	if (TRUE == version)
	{
		print_version ();
		goto gcleanup;
	}

	/**
	 * If user run application without any parameter, print help and exit
	 * with error.
	 */
	if (FALSE) /* Test for switches here */
	{
		gchar *ht;

		ht = g_option_context_get_help (gcontext, TRUE, NULL);
		g_print ("%s", ht);

		g_free (ht);
		goto gcleanup;
	}

	/**
	 * Determine source stream.
	 */
	FILE *filetoread = stdin;

	if (filename)
	{
		gboolean r;

		/* Test if file exist and if it is regular file. */
		r = g_file_test (filename,
			G_FILE_TEST_EXISTS | G_FILE_TEST_IS_REGULAR);

		if (FALSE == r)
		{
			perror (exec_name);
			goto gcleanup;
		}

		/* Try to open file for reading. */
		if (NULL == (filetoread = g_fopen (filename, "r")))
		{
			perror (exec_name);
			goto gcleanup;
		}
	}

	/**
	 * From this point we can do the rest of initialization process.
	 */
	process_stream (filetoread);

	/**
	 * Try to close stream.
	 */
	if (EOF == fclose (filetoread))
		perror (exec_name);

	/**
	 * Do the cleanup and end program.
	 */
gcleanup:
	cleanup_goption ();

exit:
	return EXIT_SUCCESS;
}
