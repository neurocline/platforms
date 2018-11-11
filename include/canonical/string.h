// <string.h>
// - string operations
//
// Defined in ISO C18 Standard: 7.24 String handling <string.h>.
// Expanded in POSIX.1-2017 <string.h>

#ifndef CANONICAL_ISO_C18_STRING_H
#define CANONICAL_ISO_C18_STRING_H

// ---------------------------------------------------------------------------
// Canonical header

// If we don't have at least C11, then make new keywords vanish
// so older compilers still work (notably MSVC))
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
#define restrict
#define _Noreturn
#endif

// ----------------------------
// C18

// size_t as in stddef.h
#ifdef _WIN64
typedef unsigned long long size_t;
#else
typedef unsigned int size_t;
#endif

// Null as in stddef.h
#ifndef __cplusplus
#define NULL ((void*) 0)
#else
#define NULL 0
#endif

// 7.24.2.1
void *memcpy(void * restrict s1, const void * restrict s2, size_t n);

// 7.24.2.2
void *memmove(void *s1, const void *s2, size_t n);

// 7.24.2.3
char *strcpy(char * restrict s1, const char * restrict s2);

// 7.24.2.4
char *strncpy(char * restrict s1, const char * restrict s2, size_t n);

// 7.24.3.1
char *strcat(char * restrict s1, const char * restrict s2);

// 7.24.3.2
char *strncat(char * restrict s1, const char * restrict s2, size_t n);

// 7.24.4.1
int memcmp(const void *s1, const void *s2, size_t n);

// 7.24.4.2
int strcmp(const char *s1, const char *s2);

// 7.24.4.3
int strcoll(const char *s1, const char *s2);

// 7.24.4.4
int strncmp(const char *s1, const char *s2, size_t n);

// 7.24.4.5
size_t strxfrm(char * restrict s1, const char * restrict s2, size_t n);

// 7.24.5.1
void *memchr(const void *s, int c, size_t n);

// 7.24.5.2
char *strchr(const char *s, int c);

// 7.24.5.3
size_t strcspn(const char *s1, const char *s2);

// 7.24.5.4
char *strpbrk(const char *s1, const char *s2);

// 7.24.5.5
char *strrchr(const char *s, int c);

// 7.24.5.6
size_t strspn(const char *s1, const char *s2);

// 7.24.5.7
char *strstr(const char *s1, const char *s2);

// 7.24.5.8
char *strtok(char * restrict s1, const char * restrict s2);

// 7.24.6.1
void *memset(void *s, int c, size_t n);

// 7.24.6.2
char *strerror(int errnum);

// 7.24.6.3
size_t strlen(const char *s);

// ----------------------------
// POSIX

// as in locale.h
typedef struct _locale_struct
{
    int dummy; // until we figure out what we want
} *locale_t;

void *memccpy(void *restrict s1, const void *restrict s2, int c, size_t n);
char *strdup(const char *s);
size_t strnlen(const char *s, size_t maxlen);

char *stpcpy(char *restrict s1, const char *restrict s2);
char *stpncpy(char *restrict s1, const char *restrict s2, size_t n);
int strcoll_l(const char *s1, const char *s2, locale_t locale);
char *strndup(const char *s, size_t size);
char *strerror_l(int errnum, locale_t locale);
int strerror_r(int errnum, char *strerrbuf, size_t buflen);
char *strsignal(int signum);
char *strtok_r(char *restrict s, const char *restrict sep, char **restrict state);
size_t strxfrm_l(char *restrict s1, const char *restrict s2, size_t n, locale_t locale);

// ---------------------------------------------------------------------------

#endif // CANONICAL_ISO_C18_STRING_H
