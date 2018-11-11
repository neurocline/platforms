// <string.h>
//
// Defined in ISO C18 Standard: 7.24 String handling <string.h>.
// string operations
// Extended by POSIX.1-2017 <string.h>
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/string.h.html

#pragma once
#ifndef _POSIX_ON_WIN32__STRING_H
#define _POSIX_ON_WIN32__STRING_H

// Get emulation of #include_next
#include <posix_win32_include_next.h>

// Default to using the Windows string.h file
#ifndef _POSIX_ON_WIN32_NO_WIN32_STRING
#define _POSIX_ON_WIN32_USE_WIN32_STRING
#endif

// -----------------------------------------------------------------------------------------------

#if defined(_POSIX_ON_WIN32_USE_WIN32_STRING)

// When we include the Windows <string.h>, do not let it
// introduce specific types
#pragma push_macro("__STDC__")
#pragma push_macro("_CRT_NO_TIME_T")
#pragma push_macro("_CRT_NO_POSIX_ERROR_CODES")
#undef __STDC__
#define __STDC__ 1
#undef _CRT_NO_TIME_T
#define _CRT_NO_TIME_T
#undef _CRT_NO_POSIX_ERROR_CODES
#include _MICROSOFT_UCRT_INCLUDE_NEXT(string.h)
#pragma pop_macro("__STDC__")
#pragma pop_macro("_CRT_NO_TIME_T")
#pragma pop_macro("_CRT_NO_POSIX_ERROR_CODES")

// ----------------------------
// POSIX

// as in locale.h
typedef struct _locale_struct
{
    int dummy; // until we figure out what we want
} *locale_t;

//void *memccpy(void * s1, const void * s2, int c, size_t n);
//char *strdup(const char *s);
//size_t strnlen(const char *s, size_t maxlen);

char *stpcpy(char * s1, const char * s2);
char *stpncpy(char * s1, const char * s2, size_t n);
int strcoll_l(const char *s1, const char *s2, locale_t locale);
char *strndup(const char *s, size_t size);
char *strerror_l(int errnum, locale_t locale);
int strerror_r(int errnum, char *strerrbuf, size_t buflen);
char *strsignal(int signum);
char *strtok_r(char * s, const char * sep, char ** state);
size_t strxfrm_l(char * s1, const char * s2, size_t n, locale_t locale);

#endif // defined(_POSIX_ON_WIN32_USE_WIN32_STRING)

// -----------------------------------------------------------------------------------------------

#if !defined(_POSIX_ON_WIN32_USE_WIN32_STRING)

#error "This path not supported"

#endif // !defined(_POSIX_ON_WIN32_USE_WIN32_STRING)

// -----------------------------------------------------------------------------------------------

#endif // _POSIX_ON_WIN32__STRING_H
