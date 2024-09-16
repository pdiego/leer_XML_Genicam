#ifndef ARV_UTILS_H
#define ARV_UTILS_H
#include <arv.h>
#include <glib.h>




class arvUtils {
	public:
		GRegex * arv_regex_new_from_glob_pattern (const char *glob, gboolean caseless);
}

#endif // ARV_UTILS_H