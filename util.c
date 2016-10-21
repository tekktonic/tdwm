/* See LICENSE file for copyright and license details. */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void *
ecalloc(size_t nmemb, size_t size)
{
	void *p;

	if (!(p = calloc(nmemb, size)))
		perror(NULL);
	return p;
}

void
die(const char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	if (fmt[0] && fmt[strlen(fmt)-1] == ':') {
		fputc(' ', stderr);
		perror(NULL);
	}

	exit(1);
}

#ifdef NO_STRL
size_t
strlcpy(char *dst, const char *src, size_t size)
{
    for (int i = 0; i < size - 1 && *src != '\0'; i++) {
        *dst++ = *src++;
    }

    dst[size] = '\0';

    return strlen(src)+1;
}
#endif
