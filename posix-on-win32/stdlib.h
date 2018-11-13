// <stdlib.h>
// - standard library definitions
//
// Defined in ISO C18 Standard: 7.22 General utilities <stdlib.h>.
// Extended in POSIX.1-2017 <stdlib.h>
// See http://pubs.opengroup.org/onlinepubs/9699919799.2018edition/basedefs/stdlib.h.html

#pragma once
#ifndef _POSIX_ON_WIN32_ISO_STDLIB_H
#define _POSIX_ON_WIN32_ISO_STDLIB_H

// Default to using the Windows stdlib.h file
#ifndef _POSIX_ON_WIN32_NO_WIN32_STDLIB
#define _POSIX_ON_WIN32_USE_WIN32_STDLIB
#endif

// -----------------------------------------------------------------------------------------------

#if defined(_POSIX_ON_WIN32_USE_WIN32_STDLIB)
// Get MSVC emulation of #include_next
#include <posix_win32_include_next.h>

#pragma push_macro("_CRT_NO_TIME_T")
#pragma push_macro("_CRT_NONSTDC_NO_DEPRECATE")
#undef _CRT_NO_TIME_T
#define _CRT_NO_TIME_T
#undef _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include _MICROSOFT_UCRT_INCLUDE_NEXT(stdlib.h)
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

long a64l(const char* s);
char* l64a(long value);

double drand48(void);
double erand48(unsigned short xsubi[3]);
long jrand48(unsigned short xsubi[3]);
void lcong48(unsigned short param[7]);
long lrand48(void);
long mrand48(void);
long nrand48(unsigned short xsubi[3]);
unsigned short* seed48(unsigned short seed16v[3]);
void srand48(long seedval);
int getsubopt(char** optionp, char* const* keylistp, char** valuep);
int grantpt(int fildes);
char* initstate(unsigned seed, char* state, size_t size);
long random(void);
char* setstate(char* state);
void srandom(unsigned seed);
char* mkdtemp(char* template_);
int mkstemp(char* template_);
int posix_memalign(void** memptr, size_t alignment, size_t size);
int posix_openpt(int oflag);
char* ptsname(int fildes);
// int putenv(char* string) is found in Microsoft's <stdlib.h> header
int rand_r(unsigned* seed);
char* realpath(const char* restrict file_name, char* restrict resolved_name);
int setenv(const char* envname, const char* envval, int overwrite);
void setkey(const char* key);
int unlockpt(int fildes);
int unsetenv(const char* name);

#ifdef  __cplusplus
}
#endif

#endif // defined(_POSIX_ON_WIN32_USE_WIN32_STDLIB)

// -----------------------------------------------------------------------------------------------

#if !defined(_POSIX_ON_WIN32_USE_WIN32_STDLIB)

#error "This path not supported"

#endif // !defined(_POSIX_ON_WIN32_USE_WIN32_STDLIB)

// -----------------------------------------------------------------------------------------------

#endif // _POSIX_ON_WIN32_ISO_STDLIB_H
