// time.c

#define _CRT_NO_TIME_T
#define __STDC__ 1

#include <errno.h>
#include <time.h>

#include <corecrt.h>

// Prototypes for CRT functions (since we can't include the Windows <time.h>)
_ACRTIMP __time64_t __cdecl _time64(__time64_t* time);
_ACRTIMP char* __cdecl _ctime64(__time64_t const* time);

char* _posix_on_win32_ctime(const time_t *timer)
{
    if (timer == NULL)
    {
        errno = EINVAL;
        return NULL;
    }
    __time64_t t = *timer;
    return _ctime64(&t);
}

time_t _posix_on_win32_time(time_t *timer)
{
    __time64_t t;
    t = _time64(NULL);
    if (timer != NULL)
        *timer = (time_t) t;
    return (time_t) t;
}
