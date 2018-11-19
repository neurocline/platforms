// <stdio.h>
// - standard buffered input/output
//
// Defined in ISO C18 Standard: 7.21 Input/output <stdio.h>.
// Extended in POSIX.1-2017 <stdio.h>
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stdio.h.html
// Has Glibc 2.28 extensions

#pragma once
#ifndef _POSIX_ON_WIN32_ISO_STDIO_H
#define _POSIX_ON_WIN32_ISO_STDIO_H

// Default to using the Windows stdio.h file
#ifndef _POSIX_ON_WIN32_NO_WIN32_STDIO
#define _POSIX_ON_WIN32_USE_WIN32_STDIO
#endif

// -----------------------------------------------------------------------------------------------

#if defined(_POSIX_ON_WIN32_USE_WIN32_STDIO)
// Get MSVC emulation of #include_next
#include <posix_win32_include_next.h>

#pragma push_macro("_CRT_NO_TIME_T")
#undef _CRT_NO_TIME_T
#define _CRT_NO_TIME_T
#pragma push_macro("__STDC__")
#undef __STDC__
#define __STDC__ 1
#include _MICROSOFT_UCRT_INCLUDE_NEXT(stdio.h)
#pragma pop_macro("_CRT_NO_TIME_T")
#pragma pop_macro("__STDC__")

// If we don't have at least C11, then make new keywords vanish
// so older compilers still work (notably MSVC))
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
#define restrict
#define _Noreturn
#endif

// va_list as in stdarg.h
typedef char* va_list;

// size_t as in stddef.h
#ifdef _WIN64
typedef unsigned long long size_t;
#else
typedef unsigned int size_t;
#endif

// as in sys/types.h
typedef long long off_t;


// ----------------------------
// POSIX

// size_t as in sys/types.h
#ifdef _WIN64
typedef long long ssize_t;
#else
typedef int ssize_t;
#endif

// [CX] Maximum size of character array to hold ctermid() output.
#define L_ctermid 1024

// Default directory prefix for tempnam().
extern char* P_tmpdir;

// Tell C++ this is a C header
#ifdef  __cplusplus
extern "C" {
#endif

char* ctermid(char *s);
int dprintf(int fildes, const char* restrict format, ...);

void flockfile(FILE* file);
int ftrylockfile(FILE* file);
void funlockfile(FILE* file);

FILE* fmemopen(void* restrict buf, size_t size, const char* restrict mode);
int fseeko(FILE *stream, off_t offset, int whence);
off_t ftello(FILE *stream);

int getc_unlocked(FILE *stream);
int getchar_unlocked(void);
int putc_unlocked(int c, FILE *stream);
int putchar_unlocked(int c);

ssize_t getdelim(char ** restrict lineptr, size_t* restrict n, int delimiter, FILE* restrict stream);
ssize_t getline(char** restrict lineptr, size_t* restrict n, FILE* restrict stream);

FILE *open_memstream(char **bufp, size_t *sizep);

int pclose(FILE *stream);
FILE *popen(const char *command, const char *mode);

int renameat(int oldfd, const char* old, int newfd, const char* new);

int vdprintf(int fildes, const char* restrict format, va_list ap);

// ----------------------------
// Glibc

typedef long long off64_t;

int fseeko64(FILE *stream, off64_t offset, int whence);
off64_t ftello64(FILE *stream);

#ifdef  __cplusplus
}
#endif

#endif // defined(_POSIX_ON_WIN32_USE_WIN32_STDIO)

// -----------------------------------------------------------------------------------------------

#if !defined(_POSIX_ON_WIN32_USE_WIN32_STDIO)

#error "This path not supported"

#endif // !defined(_POSIX_ON_WIN32_USE_WIN32_STDIO)

// -----------------------------------------------------------------------------------------------

#endif // _POSIX_ON_WIN32_ISO_STDIO_H
