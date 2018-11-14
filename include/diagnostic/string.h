// <string.h>
// - string operations
//
// Defined in ISO C18 Standard: 7.24 String handling <string.h>.
// Extended in POSIX.1-2017 <string.h>
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/string.h.html

#pragma once
#ifndef DIAGNOSTIC_ISO_C18_STRING_H
#define DIAGNOSTIC_ISO_C18_STRING_H

#include <internal/carp.h>

// ---------------------------------------------------------------------------
// Diagnostic header

// If we don't have at least C11, then make new keywords vanish
// so older compilers still work (notably MSVC))
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
#define restrict
#define _Noreturn
#endif

// size_t as in stddef.h
#ifdef _WIN64
typedef unsigned long long size_t;
#else
typedef unsigned int size_t;
#endif

// Null as in stddef.h
#ifndef NULL
#ifndef __cplusplus
#define NULL ((void*) 0)
#else
#define NULL 0
#endif
#endif

// Tell C++ this is a C header
#ifdef  __cplusplus
extern "C" {
#endif

// 7.24.2.1
CARP("ISO C95: memcpy()") void *memcpy(void * restrict s1, const void * restrict s2, size_t n);

// 7.24.2.2
CARP("ISO C95: memmove()") void *memmove(void *s1, const void *s2, size_t n);

// 7.24.2.3
CARP("ISO C95: strcpy()") char *strcpy(char * restrict s1, const char * restrict s2);

// 7.24.2.4
CARP("ISO C95: strncpy()") char *strncpy(char * restrict s1, const char * restrict s2, size_t n);

// 7.24.3.1
CARP("ISO C95: strcat()") char *strcat(char * restrict s1, const char * restrict s2);

// 7.24.3.2
CARP("ISO C95: strncat()") char *strncat(char * restrict s1, const char * restrict s2, size_t n);

// 7.24.4.1
CARP("ISO C95: memcmp()") int memcmp(const void *s1, const void *s2, size_t n);

// 7.24.4.2
CARP("ISO C95: strcmp()") int strcmp(const char *s1, const char *s2);

// 7.24.4.3
CARP("ISO C95: strcoll()") int strcoll(const char *s1, const char *s2);

// 7.24.4.4
CARP("ISO C95: strncmp()") int strncmp(const char *s1, const char *s2, size_t n);

// 7.24.4.5
CARP("ISO C95: strxfrm()") size_t strxfrm(char * restrict s1, const char * restrict s2, size_t n);

// 7.24.5.1
CARP("ISO C95: memchr()") void *memchr(const void *s, int c, size_t n);

// 7.24.5.2
CARP("ISO C95: strchr()") char *strchr(const char *s, int c);

// 7.24.5.3
CARP("ISO C95: strcspn()") size_t strcspn(const char *s1, const char *s2);

// 7.24.5.4
CARP("ISO C95: strpbrk()") char *strpbrk(const char *s1, const char *s2);

// 7.24.5.5
CARP("ISO C95: strrchr()") char *strrchr(const char *s, int c);

// 7.24.5.6
CARP("ISO C95: strspn()") size_t strspn(const char *s1, const char *s2);

// 7.24.5.7
CARP("ISO C95: strstr()") char *strstr(const char *s1, const char *s2);

// 7.24.5.8
CARP("ISO C95: strtok()") char *strtok(char * restrict s1, const char * restrict s2);

// 7.24.6.1
CARP("ISO C95: memset()") void *memset(void *s, int c, size_t n);

// 7.24.6.2
CARP("ISO C95: strerror()") char *strerror(int errnum);

// 7.24.6.3
CARP("ISO C95: strlen()") size_t strlen(const char *s);

#ifdef  __cplusplus
}
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

CARP("POSIX 2017.1: memccpy()") void* memccpy(void* restrict s1, const void* restrict s2, int c, size_t n);
CARP("POSIX 2017.1: strdup()") char* strdup(const char* s);
CARP("POSIX 2017.1: strnlen()") size_t strnlen(const char* s, size_t maxlen);
CARP("POSIX 2017.1: stpcpy()") char* stpcpy(char* restrict s1, const char* restrict s2);
CARP("POSIX 2017.1: stpncpy()") char* stpncpy(char* restrict s1, const char* restrict s2, size_t n);
CARP("POSIX 2017.1: strcoll_l()") int strcoll_l(const char* s1, const char* s2, locale_t locale);
CARP("POSIX 2017.1: strndup()") char* strndup(const char* s, size_t size);
CARP("POSIX 2017.1: strerror_l()") char* strerror_l(int errnum, locale_t locale);
CARP("POSIX 2017.1: strerror_r()") int strerror_r(int errnum, char* strerrbuf, size_t buflen);
CARP("POSIX 2017.1: strsignal()") char* strsignal(int signum);
CARP("POSIX 2017.1: strtok_r()") char* strtok_r(char* restrict s, const char* restrict sep, char** restrict state);
CARP("POSIX 2017.1: strxfrm_l()") size_t strxfrm_l(char* restrict s1, const char* restrict s2, size_t n, locale_t locale);

#ifdef  __cplusplus
}
#endif

// -----------------------------------------------------------------------------------------------

#endif // DIAGNOSTIC_ISO_C18_STRING_H
