// <stdlib.h>
// - standard library definitions
//
// Defined in ISO C18 Standard: 7.22 General utilities <stdlib.h>.
// Extended in POSIX.1-2017 <stdlib.h>
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stdlib.h.html

#pragma once
#ifndef DIAGNOSTIC_ISO_C18_STDLIB_H
#define DIAGNOSTIC_ISO_C18_STDLIB_H

#include <internal/carp.h>

// ---------------------------------------------------------------------------
// Diagnostic header

// If we don't have at least C11, then make new keywords vanish
// so older compilers still work (notably MSVC))
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
#define restrict
#define _Noreturn
#endif

// 7.22
// size_t as in stddef.h
#ifdef _WIN64
typedef unsigned long long  size_t;
#else
typedef unsigned int       size_t;
#endif

// wchar_t as in stddef.h (this is a builtin for C++_
#ifndef __cplusplus
typedef unsigned short wchar_t;
#endif

typedef struct div_t
{
    int quot;
    int rem;
} div_t;

typedef struct ldiv_t
{
    long int quot;
    long int rem;
} ldiv_t;

typedef struct lldiv_t
{
    long long quot;
    long long rem;
} lldiv_t;

// as in stddef.h
#ifndef __cplusplus
#define NULL ((void*) 0)
#else
#define NULL 0
#endif

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define RAND_MAX 32767

#define MB_CUR_MAX 8

// Tell C++ this is a C header
#ifdef  __cplusplus
extern "C" {
#endif

// 7.22.1.1
CARP("ISO C95: atof()") double atof(const char* nptr);

// 7.22.1.2
CARP("ISO C95: atoi()") int atoi(const char* nptr);
CARP("ISO C95: atol()") long int atol(const char* nptr);
CARP("ISO C95: atoll()") long long int atoll(const char* nptr);

// 7.22.1.3
CARP("ISO C95: strtod()") double strtod(const char* restrict nptr, char** restrict endptr);
CARP("ISO C95: strtof()") float strtof(const char* restrict nptr, char** restrict endptr);
CARP("ISO C95: strtold()") long double strtold(const char* restrict nptr, char** restrict endptr);

// 7.22.1.4
CARP("ISO C95: strtol()") long int strtol(const char* restrict nptr, char** restrict endptr, int base);
CARP("ISO C95: strtoll()") long long int strtoll(const char* restrict nptr, char** restrict endptr, int base);
CARP("ISO C95: strtoul()") unsigned long int strtoul(const char* restrict nptr, char** restrict endptr, int base);
CARP("ISO C95: strtoull()") unsigned long long int strtoull(const char* restrict nptr, char** restrict endptr, int base);

// 7.22.2.1
CARP("ISO C95: rand()") int rand(void);

// 7.22.2.2
CARP("ISO C95: srand()") void srand(unsigned int seed);

// 7.22.3.1
CARP("ISO C95: aligned_alloc()") void* aligned_alloc(size_t alignment, size_t size);

// 7.22.3.2
CARP("ISO C95: calloc()") void* calloc(size_t nmemb, size_t size);

// 7.22.3.3
CARP("ISO C95: free()") void free(void *ptr);

// 7.22.3.4
CARP("ISO C95: malloc()") void* malloc(size_t size);

// 7.22.3.5
CARP("ISO C95: realloc()") void* realloc(void* ptr, size_t size);

// 7.22.4.1
CARP("ISO C95: abort()") _Noreturn void abort(void);

// 7.22.4.2
CARP("ISO C95: atexit()") int atexit(void (*func)(void));

// 7.22.4.3
CARP("ISO C95: at_quick_exit()") int at_quick_exit(void (*func)(void));

// 7.22.4.4
CARP("ISO C95: exit()") _Noreturn void exit(int status);

// 7.22.4.5
CARP("ISO C95: _Exit()") _Noreturn void _Exit(int status);

// 7.22.4.6
CARP("ISO C95: getenv()") char* getenv(const char *name);

// 7.22.4.7
CARP("ISO C95: quick_exit()") _Noreturn void quick_exit(int status);

// 7.22.4.8
CARP("ISO C95: system()") int system(const char* string);

// 7.22.5.1
CARP("ISO C95: bsearch()") void* bsearch(const void* key, const void* base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

// 7.22.5.2
CARP("ISO C95: qsort()") void qsort(void* base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));

// 7.22.6.1
CARP("ISO C95: abs()") int abs(int j);
CARP("ISO C95: labs()") long int labs(long int j);
CARP("ISO C95: llabs()") long long int llabs(long long int j);

// 7.22.6.2
CARP("ISO C95: div()") div_t div(int numer, int denom);
CARP("ISO C95: ldiv()") ldiv_t ldiv(long int numer, long int denom);
CARP("ISO C95: lldiv()") lldiv_t lldiv(long long int numer, long long int denom);

// 7.22.7.1
CARP("ISO C95: mblen()") int mblen(const char* s, size_t n);

// 7.22.7.2
CARP("ISO C95: mbtowc()") int mbtowc(wchar_t* restrict pwc, const char* restrict s, size_t n);

// 7.22.7.3
CARP("ISO C95: wctomb()") int wctomb(char* s, wchar_t wc);

// 7.22.8.1
CARP("ISO C95: mbstowcs()") size_t mbstowcs(wchar_t* restrict pwcs, const char* restrict s, size_t n);

// 7.22.8.2
CARP("ISO C95: wcstombs()") size_t wcstombs(char* restrict s, const wchar_t* restrict pwcs, size_t n);

#ifdef  __cplusplus
}
#endif

// ----------------------------
// POSIX

// as in sys/wait.h
#define WEXITSTATUS     1
#define WIFEXITED       1
#define WIFSIGNALED     1
#define WIFSTOPPED      1
#define WNOHANG         1
#define WSTOPSIG        1
#define WTERMSIG        1
#define WUNTRACED       1

// Tell C++ this is a C header
#ifdef  __cplusplus
extern "C" {
#endif

CARP("POSIX 2017.1: a64l()") long a64l(const char* s);
CARP("POSIX 2017.1: l64a()") char* l64a(long value);

CARP("POSIX 2017.1: drand48()") double drand48(void);
CARP("POSIX 2017.1: erand48()") double erand48(unsigned short xsubi[3]);
CARP("POSIX 2017.1: jrand48()") long jrand48(unsigned short xsubi[3]);
CARP("POSIX 2017.1: lcong48()") void lcong48(unsigned short param[7]);
CARP("POSIX 2017.1: lrand48()") long lrand48(void);
CARP("POSIX 2017.1: mrand48()") long mrand48(void);
CARP("POSIX 2017.1: nrand48()") long nrand48(unsigned short xsubi[3]);
CARP("POSIX 2017.1: seed48()") unsigned short* seed48(unsigned short seed16v[3]);
CARP("POSIX 2017.1: srand48()") void srand48(long seedval);
CARP("POSIX 2017.1: getsubopt()") int getsubopt(char** optionp, char* const* keylistp, char** valuep);
CARP("POSIX 2017.1: grantpt()") int grantpt(int fildes);
CARP("POSIX 2017.1: initstate()") char* initstate(unsigned seed, char* state, size_t size);
CARP("POSIX 2017.1: random()") long random(void);
CARP("POSIX 2017.1: setstate()") char* setstate(char* state);
CARP("POSIX 2017.1: srandom()") void srandom(unsigned seed);
CARP("POSIX 2017.1: mkdtemp()") char* mkdtemp(char* template_);
CARP("POSIX 2017.1: mkstemp()") int mkstemp(char* template_);
CARP("POSIX 2017.1: posix_memalign()") int posix_memalign(void** memptr, size_t alignment, size_t size);
CARP("POSIX 2017.1: posix_openpt()") int posix_openpt(int oflag);
CARP("POSIX 2017.1: ptsname()") char* ptsname(int fildes);
CARP("POSIX 2017.1: putenv()") int putenv(char* string);
CARP("POSIX 2017.1: rand_r()") int rand_r(unsigned* seed);
CARP("POSIX 2017.1: realpath()") char* realpath(const char* restrict file_name, char* restrict resolved_name);
CARP("POSIX 2017.1: setenv()") int setenv(const char* envname, const char* envval, int overwrite);
CARP("POSIX 2017.1: setkey()") void setkey(const char* key);
CARP("POSIX 2017.1: unlockpt()") int unlockpt(int fildes);
CARP("POSIX 2017.1: unsetenv()") int unsetenv(const char* name);

#ifdef  __cplusplus
}
#endif

// -----------------------------------------------------------------------------------------------

#endif // DIAGNOSTIC_ISO_C18_STDLIB_H
