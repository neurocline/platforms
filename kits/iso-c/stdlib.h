// If we don't have at least C11, then make new keywords vanish
// so older compilers still work (notably MSVC))
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
#define restrict
#define _Noreturn
#endif

[MSVCRT]
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

[CDECL]

// 7.22.1.1
[CARP atof()]double atof(const char* nptr);

// 7.22.1.2
[CARP atoi()]int atoi(const char* nptr);
[CARP atol()]long int atol(const char* nptr);
[CARP atoll()]long long int atoll(const char* nptr);

// 7.22.1.3
[CARP strtod()]double strtod(const char* restrict nptr, char** restrict endptr);
[CARP strtof()]float strtof(const char* restrict nptr, char** restrict endptr);
[CARP strtold()]long double strtold(const char* restrict nptr, char** restrict endptr);

// 7.22.1.4
[CARP strtol()]long int strtol(const char* restrict nptr, char** restrict endptr, int base);
[CARP strtoll()]long long int strtoll(const char* restrict nptr, char** restrict endptr, int base);
[CARP strtoul()]unsigned long int strtoul(const char* restrict nptr, char** restrict endptr, int base);
[CARP strtoull()]unsigned long long int strtoull(const char* restrict nptr, char** restrict endptr, int base);

// 7.22.2.1
[CARP rand()]int rand(void);

// 7.22.2.2
[CARP srand()]void srand(unsigned int seed);

// 7.22.3.1
[CARP aligned_alloc()]void* aligned_alloc(size_t alignment, size_t size);

// 7.22.3.2
[CARP calloc()]void* calloc(size_t nmemb, size_t size);

// 7.22.3.3
[CARP free()]void free(void *ptr);

// 7.22.3.4
[CARP malloc()]void* malloc(size_t size);

// 7.22.3.5
[CARP realloc()]void* realloc(void* ptr, size_t size);

// 7.22.4.1
[CARP abort()]_Noreturn void abort(void);

// 7.22.4.2
[CARP atexit()]int atexit(void (*func)(void));

// 7.22.4.3
[CARP at_quick_exit()]int at_quick_exit(void (*func)(void));

// 7.22.4.4
[CARP exit()]_Noreturn void exit(int status);

// 7.22.4.5
[CARP _Exit()]_Noreturn void _Exit(int status);

// 7.22.4.6
[CARP getenv()]char* getenv(const char *name);

// 7.22.4.7
[CARP quick_exit()]_Noreturn void quick_exit(int status);

// 7.22.4.8
[CARP system()]int system(const char* string);

// 7.22.5.1
[CARP bsearch()]void* bsearch(const void* key, const void* base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

// 7.22.5.2
[CARP qsort()]void qsort(void* base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));

// 7.22.6.1
[CARP abs()]int abs(int j);
[CARP labs()]long int labs(long int j);
[CARP llabs()]long long int llabs(long long int j);

// 7.22.6.2
[CARP div()]div_t div(int numer, int denom);
[CARP ldiv()]ldiv_t ldiv(long int numer, long int denom);
[CARP lldiv()]lldiv_t lldiv(long long int numer, long long int denom);

// 7.22.7.1
[CARP mblen()]int mblen(const char* s, size_t n);

// 7.22.7.2
[CARP mbtowc()]int mbtowc(wchar_t* restrict pwc, const char* restrict s, size_t n);

// 7.22.7.3
[CARP wctomb()]int wctomb(char* s, wchar_t wc);

// 7.22.8.1
[CARP mbstowcs()]size_t mbstowcs(wchar_t* restrict pwcs, const char* restrict s, size_t n);

// 7.22.8.2
[CARP wcstombs()]size_t wcstombs(char* restrict s, const wchar_t* restrict pwcs, size_t n);

[/CDECL]

[/MSVCRT]
[POSIX]
// as in sys/wait.h
#define WEXITSTATUS     1
#define WIFEXITED       1
#define WIFSIGNALED     1
#define WIFSTOPPED      1
#define WNOHANG         1
#define WSTOPSIG        1
#define WTERMSIG        1
#define WUNTRACED       1

[CDECL]

[CARP a64l()]long a64l(const char* s);
[CARP l64a()]char* l64a(long value);

[CARP drand48()]double drand48(void);
[CARP erand48()]double erand48(unsigned short xsubi[3]);
[CARP jrand48()]long jrand48(unsigned short xsubi[3]);
[CARP lcong48()]void lcong48(unsigned short param[7]);
[CARP lrand48()]long lrand48(void);
[CARP mrand48()]long mrand48(void);
[CARP nrand48()]long nrand48(unsigned short xsubi[3]);
[CARP seed48()]unsigned short* seed48(unsigned short seed16v[3]);
[CARP srand48()]void srand48(long seedval);
[CARP getsubopt()]int getsubopt(char** optionp, char* const* keylistp, char** valuep);
[CARP grantpt()]int grantpt(int fildes);
[CARP initstate()]char* initstate(unsigned seed, char* state, size_t size);
[CARP random()]long random(void);
[CARP setstate()]char* setstate(char* state);
[CARP srandom()]void srandom(unsigned seed);
[CARP mkdtemp()]char* mkdtemp(char* template_);
[CARP mkstemp()]int mkstemp(char* template_);
[CARP posix_memalign()]int posix_memalign(void** memptr, size_t alignment, size_t size);
[CARP posix_openpt()]int posix_openpt(int oflag);
[CARP ptsname()]char* ptsname(int fildes);
[CARP putenv()]int putenv(char* string);
[CARP rand_r()]int rand_r(unsigned* seed);
[CARP realpath()]char* realpath(const char* restrict file_name, char* restrict resolved_name);
[CARP setenv()]int setenv(const char* envname, const char* envval, int overwrite);
[CARP setkey()]void setkey(const char* key);
[CARP unlockpt()]int unlockpt(int fildes);
[CARP unsetenv()]int unsetenv(const char* name);

[/CDECL]
