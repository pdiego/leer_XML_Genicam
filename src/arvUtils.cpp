#include "arvUtils.h"

GRegex * arv_regex_new_from_glob_pattern (const char *glob, gboolean caseless)
{
    GRegex *regex;
	GString *regex_pattern;
	const char *iter;
	char **globs;
	gunichar character;
	unsigned int i;

	g_return_val_if_fail (g_utf8_validate (glob, -1, NULL), NULL);

	regex_pattern = g_string_new ("");

	globs = g_strsplit (glob, "|", -1);

	for (i = 0; globs[i] != NULL; i++) {
		/* Ignore empty strings */
		if (globs[i][0] == '\0')
		    continue;

		if (i > 0)
			g_string_append (regex_pattern, "|^");
		else
			g_string_append (regex_pattern, "^");

		iter = g_strstrip (globs[i]);
		while (iter != NULL && *iter != '\0') {
			character = g_utf8_get_char (iter);
			switch (character) {
				case '\\':
					g_string_append (regex_pattern, "\\\\");
					break;
				case '^':
					g_string_append (regex_pattern, "\\^");
					break;
				case '$':
					g_string_append (regex_pattern, "\\$");
					break;
				case '.':
					g_string_append (regex_pattern, "\\.");
					break;
				case '[':
					g_string_append (regex_pattern, "\\[");
					break;
				case '|':
					g_string_append (regex_pattern, "\\|");
					break;
				case '(':
					g_string_append (regex_pattern, "\\(");
					break;
				case ')':
					g_string_append (regex_pattern, "\\)");
					break;
				case '?':
					g_string_append (regex_pattern, ".");
					break;
				case '*':
					g_string_append (regex_pattern, ".*");
					break;
				case '+':
					g_string_append (regex_pattern, "\\+");
					break;
				case '{':
					g_string_append (regex_pattern, "\\{");
					break;
				default:
					g_string_append_unichar (regex_pattern, character);
					break;
			}
			iter = g_utf8_find_next_char (iter, NULL);
		}

		g_string_append (regex_pattern, "$");
	}

	g_strfreev (globs);

	arv_debug_misc ("Regex '%s' created from glob '%s'", regex_pattern->str, glob);

	regex = g_regex_new (regex_pattern->str, G_REGEX_OPTIMIZE | (caseless ? G_REGEX_CASELESS : 0), 0, NULL);
	g_string_free (regex_pattern, TRUE);

	return regex;
}