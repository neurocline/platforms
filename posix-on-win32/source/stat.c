// stat.c

#include <sys/stat.h>

int _posix_on_win32_stat(const char* path, struct stat* buf)
{
    path = NULL; buf = NULL;
    return -1;
}
