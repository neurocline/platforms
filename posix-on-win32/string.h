// <string.h>
// - string operations
//
// Defined in ISO C18 Standard: 7.24 String handling <string.h>.
// Extended in POSIX.1-2017 <string.h>
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/string.h.html

#pragma once
#ifndef _POSIX_ON_WIN32_ISO_STRING_H
#define _POSIX_ON_WIN32_ISO_STRING_H

// Default to using the Windows string.h file
#ifndef _POSIX_ON_WIN32_NO_WIN32_STRING
#define _POSIX_ON_WIN32_USE_WIN32_STRING
#endif

// -----------------------------------------------------------------------------------------------

#if defined(_POSIX_ON_WIN32_USE_WIN32_STRING)
// Get MSVC emulation of #include_next
#include <posix_win32_include_next.h>

#pragma push_macro("_CRT_NO_TIME_T")
#pragma push_macro("_CRT_NONSTDC_NO_DEPRECATE")
#undef _CRT_NO_TIME_T
#define _CRT_NO_TIME_T
#undef _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include _MICROSOFT_UCRT_INCLUDE_NEXT(string.h)
#pragma pop_macro("_CRT_NONSTDC_NO_DEPRECATE")
#pragma pop_macro("_CRT_NO_TIME_T")

// If we don't have at least C11, then make new keywords vanish
// so older compilers still work (notably MSVC))
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
#define restrict
#define _Noreturn
#endif

// ----------------------------
// POSIX

// as in locale.h
#ifndef _HEADER_LOCALE_DEFINED_LOCALE_T
#define _HEADER_LOCALE_DEFINED_LOCALE_T
typedef struct _locale_struct
{
    int dummy; // until we figure out what we want
} *locale_t;
#endif

// Tell C++ this is a C header
#ifdef  __cplusplus
extern "C" {
#endif

// The POSIX memccpy, strdup, and strnlen are in Microsoft headers
// void* memccpy(void* restrict s1, const void* restrict s2, int c, size_t n);
// char* strdup(const char* s);
// size_t strnlen(const char* s, size_t maxlen);

char* stpcpy(char* restrict s1, const char* restrict s2);
char* stpncpy(char* restrict s1, const char* restrict s2, size_t n);
int strcoll_l(const char* s1, const char* s2, locale_t locale);
char* strndup(const char* s, size_t size);
char* strerror_l(int errnum, locale_t locale);
int strerror_r(int errnum, char* strerrbuf, size_t buflen);
char* strsignal(int signum);
char* strtok_r(char* restrict s, const char* restrict sep, char** restrict state);
size_t strxfrm_l(char* restrict s1, const char* restrict s2, size_t n, locale_t locale);

#ifdef  __cplusplus
}
#endif

#endif // defined(_POSIX_ON_WIN32_USE_WIN32_STRING)

// -----------------------------------------------------------------------------------------------

#if !defined(_POSIX_ON_WIN32_USE_WIN32_STRING)

#error "This path not supported"

#endif // !defined(_POSIX_ON_WIN32_USE_WIN32_STRING)

// -----------------------------------------------------------------------------------------------

#endif // _POSIX_ON_WIN32_ISO_STRING_H
