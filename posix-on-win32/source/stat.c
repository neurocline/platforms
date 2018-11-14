// stat.c

#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define __STDC__ 1
#include <io.h> // for _access

int _posix_on_win32_fstat(int fildes, struct stat* buf)
{
    fildes = 0; buf = NULL;
    return -1;
}

int _posix_on_win32_stat(const char* path, struct stat* buf)
{
    path = NULL; buf = NULL;
    return -1;
}

void* mmap(void* addr, size_t len, int prot, int flags, int fildes, off_t off)
{
    addr = 0; len = 0; prot = 0; flags = 0; fildes = 0; off = 0;
    return NULL;
}

int munmap(void* addr, size_t len)
{
    addr = 0; len = 0;
    return -1;
}

int mkstemp(char* template_)
{
    template_ = 0;
    return -1;
}

int _posix_on_win32_access(const char *path, int amode)
{
    if (amode == 0)
        return _access(path, 0); // this is F_OK
    int rbit = amode & R_OK;
    int wbit = amode & W_OK;
    // the underlying _access can't handle the execute bit
    // int xbit = amode & X_OK;

    // Translate to Microsoft _access bit model
    int mode = 0;
    if (rbit != 0) mode |= 0x01;
    if (wbit != 0) mode |= 0x02;
    return _access(path, mode);
}

int _posix_on_win32_creat(const char *path, mode_t mode)
{
    path = 0; mode = 0;
    return -1;
}

int _posix_on_win32_vaopen(const char *path, int oflag, va_list args)
{
    path = 0; oflag = 0;
    va_end(args);
    return -1;
}
