// test-fcntl-posix.c

#include <fcntl.h>

#include <assert.h>

int test_fcntl()
{
    // check flags for existence and relative uniqueness
    int flags1[] = {
        F_DUPFD,
        F_DUPFD_CLOEXEC,
        F_GETFD,
        F_SETFD,
        F_GETFL,
        F_SETFL,
        F_GETLK,
        F_SETLK,
        F_SETLKW,
        F_GETOWN,
        F_SETOWN};
    int nflags1 = sizeof(flags1) / sizeof(flags1[0]);
    for (int i = 0; i < nflags1; i++)
        for (int j = i+1; j < nflags1; j++)
            assert(flags1[i] != flags1[j]);

    return 0;
}
