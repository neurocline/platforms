// <stdio.h>
//
// Defined in ISO C18 Standard: 7.21 Input/output <stdio.h>.
// Extended by POSIX.1-2008.7 <stdio.h>
// standard buffered input/output
// See http://pubs.opengroup.org/onlinepubs/9699919799.2018edition/basedefs/stdio.h.html

#pragma once
#ifndef _POSIX_ON_WIN32__STDIO_H
#define _POSIX_ON_WIN32__STDIO_H

// Get emulation of #include_next
#include <posix_win32_include_next.h>

// Default to using the Windows stdio.h file
#ifndef _POSIX_ON_WIN32_NO_WIN32_STDIO
#define _POSIX_ON_WIN32_USE_WIN32_STDIO
#endif

// -----------------------------------------------------------------------------------------------

#if defined(_POSIX_ON_WIN32_USE_WIN32_STDIO)

// When we include the Windows <stdio.h>, do not let it
// introduce specific types
#pragma push_macro("__STDC__")
#pragma push_macro("_CRT_NO_TIME_T")
#undef __STDC__
#define __STDC__ 1
#undef _CRT_NO_TIME_T
#define _CRT_NO_TIME_T
#define _NO_CRT_STDIO_INLINE
#pragma comment(lib, "legacy_stdio_definitions.lib")
#include _MICROSOFT_UCRT_INCLUDE_NEXT(stdio.h)
#pragma pop_macro("__STDC__")
#pragma pop_macro("_CRT_NO_TIME_T")

// ----------------------------
// POSIX

// size_t as in sys/types.h
#ifdef _WIN64
typedef long long ssize_t;
#else
typedef int ssize_t;
#endif

// as in sys/types.h
typedef long long off_t;

// [CX] Maximum size of character array to hold ctermid() output.
#define L_ctermid 1024

// Default directory prefix for tempnam().
extern char* P_tmpdir;

char* ctermid(char *s);
int dprintf(int fildes, const char* format, ...);

void flockfile(FILE* file);
int ftrylockfile(FILE* file);
void funlockfile(FILE* file);

FILE* fmemopen(void* buf, size_t size, const char* mode);
int fseeko(FILE *stream, off_t offset, int whence);
off_t ftello(FILE *stream);

int getc_unlocked(FILE *stream);
int getchar_unlocked(void);
int putc_unlocked(int c, FILE *stream);
int putchar_unlocked(int c);

ssize_t getdelim(char ** lineptr, size_t* n, int delimiter, FILE* stream);
ssize_t getline(char** lineptr, size_t* n, FILE* stream);

FILE *open_memstream(char **bufp, size_t *sizep);

int pclose(FILE *stream);
FILE *popen(const char *command, const char *mode);

int renameat(int oldfd, const char* old, int newfd, const char* new);

int vdprintf(int fildes, const char* format, va_list ap);

// ----------------------------
// Linux

typedef long long off64_t;

int fseeko64(FILE *stream, off64_t offset, int whence);
off64_t ftello64(FILE *stream);

#endif // defined(_POSIX_ON_WIN32_USE_WIN32_STDIO)

// -----------------------------------------------------------------------------------------------

// Otherwise, we have to declare a complete <stdio.h> environment
// that works for both POSIX and Windows-kinda-POSIX
#if !defined(_POSIX_ON_WIN32_USE_WIN32_STDIO)

#error "This path not supported"

#endif // !defined(_POSIX_ON_WIN32_USE_WIN32_STDIO)

// -----------------------------------------------------------------------------------------------

#endif // _POSIX_ON_WIN32__STDIO_H
