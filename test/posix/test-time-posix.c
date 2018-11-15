// test-time-posix.c

#include <assert.h>
#include <stdio.h>
#include <time.h>

int test_time()
{
    time_t t = time(NULL);
    printf("time=%lld\n", (long long) t);

    char* s = ctime(&t);
    printf("ctime=%s\n", s);

    return 0;
}
