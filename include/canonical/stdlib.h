// <stdlib.h>
// - standard library definitions
//
// Defined in ISO C18 Standard: 7.22 General utilities <stdlib.h>.
// Expanded in POSIX.1-2017 <stdlib.h>

#ifndef CANONICAL_ISO_C18_STDLIB_H
#define CANONICAL_ISO_C18_STDLIB_H

// ---------------------------------------------------------------------------
// Canonical header

// If we don't have at least C11, then make new keywords vanish
// so older compilers still work (notably MSVC))
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
#define restrict
#define _Noreturn
#endif

// ----------------------------
// C18 (update to bin functions and types by C version)

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

#define NULL 0L // as in stddef.h

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define RAND_MAX 32767

#define MB_CUR_MAX 8

// 7.22.1.1
double atof(const char *nptr);

// 7.22.1.2
int atoi(const char *nptr);
long int atol(const char *nptr);
long long int atoll(const char *nptr);

// 7.22.1.3
double strtod(const char * restrict nptr, char ** restrict endptr);
float strtof(const char * restrict nptr, char ** restrict endptr);
long double strtold(const char * restrict nptr, char ** restrict endptr);

// 7.22.1.4
long int strtol(const char * restrict nptr, char ** restrict endptr, int base);
long long int strtoll(const char * restrict nptr, char ** restrict endptr, int base);
unsigned long int strtoul(const char * restrict nptr, char ** restrict endptr, int base);
unsigned long long int strtoull(const char * restrict nptr, char ** restrict endptr, int base);

// 7.22.2.1
int rand(void);

// 7.22.2.2
void srand(unsigned int seed);

// 7.22.3.1
void *aligned_alloc(size_t alignment, size_t size);

// 7.22.3.2
void *calloc(size_t nmemb, size_t size);

// 7.22.3.3
void free(void *ptr);

// 7.22.3.4
void *malloc(size_t size);

// 7.22.3.5
void *realloc(void *ptr, size_t size);

// 7.22.4.1
_Noreturn void abort(void);

// 7.22.4.2
int atexit(void (*func)(void));

// 7.22.4.3
int at_quick_exit(void (*func)(void));

// 7.22.4.4
_Noreturn void exit(int status);

// 7.22.4.5
_Noreturn void _Exit(int status);

// 7.22.4.6
char *getenv(const char *name);

// 7.22.4.7
_Noreturn void quick_exit(int status);

// 7.22.4.8
int system(const char *string);

// 7.22.5.1
void *bsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

// 7.22.5.2
void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

// 7.22.6.1
int abs(int j);
long int labs(long int j);
long long int llabs(long long int j);

// 7.22.6.2
div_t div(int numer, int denom);
ldiv_t ldiv(long int numer, long int denom);
lldiv_t lldiv(long long int numer, long long int denom);

// 7.22.7.1
int mblen(const char *s, size_t n);

// 7.22.7.2
int mbtowc(wchar_t * restrict pwc, const char * restrict s, size_t n);

// 7.22.7.3
int wctomb(char *s, wchar_t wc);

// 7.22.8.1
size_t mbstowcs(wchar_t * restrict pwcs, const char * restrict s, size_t n);

// 7.22.8.2
size_t wcstombs(char * restrict s, const wchar_t * restrict pwcs, size_t n);


// ----------------------------
// POSIX extension

// as in sys/wait.h
#define WEXITSTATUS     1
#define WIFEXITED       1
#define WIFSIGNALED     1
#define WIFSTOPPED      1
#define WNOHANG         1
#define WSTOPSIG        1
#define WTERMSIG        1
#define WUNTRACED       1

long a64l(const char *s);
char *l64a(long value);

double drand48(void);
double erand48(unsigned short xsubi[3]);
long jrand48(unsigned short xsubi[3]);
void lcong48(unsigned short param[7]);
long lrand48(void);
long mrand48(void);
long nrand48(unsigned short xsubi[3]);
unsigned short *seed48(unsigned short seed16v[3]);
void srand48(long seedval);
int getsubopt(char **optionp, char * const *keylistp, char **valuep);
int grantpt(int fildes);
char *initstate(unsigned seed, char *state, size_t size);
long random(void);
char *setstate(char *state);
void srandom(unsigned seed);
char *mkdtemp(char *template_);
int mkstemp(char *template_);
int posix_memalign(void **memptr, size_t alignment, size_t size);
int posix_openpt(int oflag);
char *ptsname(int fildes);
int putenv(char *string);
int rand_r(unsigned *seed);
char *realpath(const char * restrict file_name, char * restrict resolved_name);
int setenv(const char *envname, const char *envval, int overwrite);
void setkey(const char *key);
int unlockpt(int fildes);
int unsetenv(const char *name);

// ---------------------------------------------------------------------------

#endif // CANONICAL_ISO_C18_STDLIB_H
