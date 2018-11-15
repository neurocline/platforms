// <time.h>
// - time types
//
// Defined in ISO C18 Standard: 7.27 Date and time <time.h>.
// Extended in POSIX.1-2017 <time.h>
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/time.h.html

#pragma once
#ifndef DIAGNOSTIC_ISO_C18_TIME_H
#define DIAGNOSTIC_ISO_C18_TIME_H

#include <internal/carp.h>

// ---------------------------------------------------------------------------
// Diagnostic header

// If we don't have at least C11, then make new keywords vanish
// so older compilers still work (notably MSVC))
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
#define restrict
#define _Noreturn
#endif

// Null as in stddef.h
#ifndef NULL
#ifndef __cplusplus
#define NULL ((void *)0)
#else
#define NULL 0
#endif
#endif

// the number per second of the value returned by the clock function
#define CLOCKS_PER_SEC ((clock_t)1000000)

// UTC timebase
#define TIME_UTC 1

// size_t as in stddef.h
#ifdef _WIN64
typedef unsigned long long size_t;
#else
typedef unsigned int size_t;
#endif

// as in sys/types.h.
typedef int clock_t;

// Make time_t be the largest natural size.
// This is used for time in seconds.
// time_t shall be an integer type.
#ifdef _WIN64
typedef long long time_t;
#else
typedef int time_t;
#endif

// an interval specified in seconds and nanoseconds
#ifndef _HEADER_SYS_STAT_DEFINED_TIMESPEC
#define _HEADER_SYS_STAT_DEFINED_TIMESPEC
struct timespec {
    time_t tv_sec; // seconds
    long tv_nsec;  // nanoseconds
};
#endif

// the broken-down time
// The value of tm_isdst is positive if Daylight Saving Time is in effect,
// zero if Daylight Saving Time is not in effect, and negative if the
// information is not available.
struct tm
{
    int tm_sec;   // seconds after the minute -- [0, 60]
    int tm_min;   // minutes after the hour -- [0, 59]
    int tm_hour;  // hours since midnight -- [0, 23]
    int tm_mday;  // day of the month -- [1, 31]
    int tm_mon;   // months since January -- [0, 11]
    int tm_year;  // years since 1900
    int tm_wday;  // days since Sunday -- [0, 6]
    int tm_yday;  // days since January 1 -- [0, 365]
    int tm_isdst; // Daylight Saving Time flag
};

// 7.27.2.1
CARP("ISO C95: clock()") clock_t clock(void);

// 7.27.2.2
CARP("ISO C95: difftime()") double difftime(time_t time1, time_t time0);

// 7.27.2.3
CARP("ISO C95: mktime()") time_t mktime(struct tm *timeptr);

// 7.27.2.4
CARP("ISO C95: time()") time_t time(time_t *timer);

// 7.27.2.5
CARP("ISO C95: timespec_get()") int timespec_get(struct timespec *ts, int base);

// 7.27.3.1
CARP("ISO C95: asctime()") char *asctime(const struct tm *timeptr);

// 7.27.3.2
CARP("ISO C95: ctime()") char *ctime(const time_t *timer);

// 7.27.3.3
CARP("ISO C95: gmtime()") struct tm *gmtime(const time_t *timer);

// 7.27.3.4
CARP("ISO C95: localtime()") struct tm *localtime(const time_t *timer);

// 7.27.3.5
CARP("ISO C95: strftime()") size_t strftime(char * restrict s, size_t maxsize, const char * restrict format, const struct tm * restrict timeptr);

// ----------------------------
// POSIX

// as in sys/types.h
typedef int clockid_t;

// as in locale.h
#ifndef _HEADER_LOCALE_DEFINED_LOCALE_T
#define _HEADER_LOCALE_DEFINED_LOCALE_T
typedef struct _locale_struct
{
    int dummy; // until we figure out what we want
} *locale_t;
#endif

// as in sys/types.h
#ifndef _HEADER_SYS_TYPES_DEFINED_TIMER_T
#define _HEADER_SYS_TYPES_DEFINED_TIMER_T
typedef struct { int v; } timer_t;
#endif

// as in sys/types.h
typedef int pid_t;

// forward declaration from signal.h
struct sigevent;

// timer specification
struct itimerspec {
    struct timespec it_interval; // timer period
    struct timespec it_value; // timer expiration
};

// The identifier for the system-wide monotonic clock, which is defined as
// a clock measuring real time, whose value cannot be set via clock_settime()
// and which cannot have negative clock jumps. The maximum possible clock
// jump shall be implementation-defined.
#define CLOCK_MONOTONIC 0

// The identifier of the CPU-time clock associated with the process making a
// clock() or timer*() function call.
#define CLOCK_PROCESS_CPUTIME_ID 1

// The identifier of the system-wide clock measuring real time.
#define CLOCK_REALTIME 2

// The identifier of the CPU-time clock associated with the thread making
// a clock() or timer*() function call.
#define CLOCK_THREAD_CPUTIME_ID 3

// Flag indicating time is absolute. For functions taking timer objects,
// this refers to the clock associated with the timer.
#define TIMER_ABSTIME 0

// presumably thread-local error specific to date functions
extern int getdate_err;

// 0 if Daylight Savings Time conversions should never be applied for the timezone in use; otherwise, non-zero
extern int    daylight;

// the difference, in seconds, between Coordinated Universal Time (UTC) and local standard time
extern long   timezone;

// set by tzset
extern char*  tzname[];

// Tell C++ this is a C header
#ifdef  __cplusplus
extern "C" {
#endif

CARP("POSIX 2017.1: asctime_r()") char *asctime_r(const struct tm *restrict tm, char *restrict buf);

CARP("POSIX 2017.1: clock_getcpuclockid()") int clock_getcpuclockid(pid_t pid, clockid_t *clock_id);

CARP("POSIX 2017.1: clock_getres()") int clock_getres(clockid_t clock_id, struct timespec *res);
CARP("POSIX 2017.1: clock_gettime()") int clock_gettime(clockid_t clock_id, struct timespec *tp);
CARP("POSIX 2017.1: clock_settime()") int clock_settime(clockid_t clock_id, const struct timespec *tp);

CARP("POSIX 2017.1: clock_nanosleep()") int clock_nanosleep(clockid_t clock_id, int flags, const struct timespec *rqtp, struct timespec *rmtp);

CARP("POSIX 2017.1: ctime_r()") char *ctime_r(const time_t *clock, char *buf);

CARP("POSIX 2017.1: getdate()") struct tm *getdate(const char *string);

CARP("POSIX 2017.1: gmtime_r()") struct tm *gmtime_r(const time_t *restrict timer, struct tm *restrict result);

CARP("POSIX 2017.1: localtime_r()") struct tm *localtime_r(const time_t *restrict timer, struct tm *restrict result);

CARP("POSIX 2017.1: nanosleep()") int nanosleep(const struct timespec *rqtp, struct timespec *rmtp);

CARP("POSIX 2017.1: strftime_l()") size_t strftime_l(char *restrict s, size_t maxsize, const char *restrict format, const struct tm *restrict timeptr, locale_t locale);

CARP("POSIX 2017.1: strptime()") char *strptime(const char *restrict buf, const char *restrict format, struct tm *restrict tm);

CARP("POSIX 2017.1: timer_create()") int timer_create(clockid_t clockid, struct sigevent *restrict evp, timer_t *restrict timerid);

CARP("POSIX 2017.1: timer_delete()") int timer_delete(timer_t timerid);

CARP("POSIX 2017.1: timer_getoverrun()") int timer_getoverrun(timer_t timerid);
CARP("POSIX 2017.1: timer_gettime()") int timer_gettime(timer_t timerid, struct itimerspec *value);
CARP("POSIX 2017.1: timer_settime()") int timer_settime(timer_t timerid, int flags, const struct itimerspec *restrict value, struct itimerspec *restrict ovalue);

CARP("POSIX 2017.1: tzset()") void tzset(void);


#ifdef  __cplusplus
}
#endif

// -----------------------------------------------------------------------------------------------

#endif // DIAGNOSTIC_ISO_C18_TIME_H
