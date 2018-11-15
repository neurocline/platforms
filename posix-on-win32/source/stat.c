// stat.c

#define WIN32_LEAN_AND_MEAN
#define __STDC__ 1

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <Windows.h>

static void convert_stat64_to_stat(struct _stat64* wbuf, struct stat* buf)
{
    // I hate macros
    #pragma push_macro("st_atime")
    #pragma push_macro("st_ctime")
    #pragma push_macro("st_mtime")
    #undef st_atime
    #undef st_ctime
    #undef st_mtime
    __int64 atime = wbuf->st_atime;
    __int64 ctime = wbuf->st_ctime;
    __int64 mtime = wbuf->st_mtime;
    #pragma pop_macro("st_atime")
    #pragma pop_macro("st_ctime")
    #pragma pop_macro("st_mtime")

    buf->st_dev = wbuf->st_dev;
    buf->st_ino = wbuf->st_ino;
    buf->st_mode = wbuf->st_mode;
    buf->st_nlink = wbuf->st_nlink;
    buf->st_uid = wbuf->st_uid;
    buf->st_gid = wbuf->st_gid;
    buf->st_rdev = wbuf->st_rdev;
    buf->st_size = wbuf->st_size;
    buf->st_atim.tv_sec = (time_t) atime;
    buf->st_atim.tv_nsec = 0;
    buf->st_mtim.tv_sec = (time_t) ctime;
    buf->st_mtim.tv_nsec = 0;
    buf->st_ctim.tv_sec = (time_t) mtime;
    buf->st_ctim.tv_nsec = 0;
    buf->st_blksize = 512;
    buf->st_blocks = (blkcnt_t)((buf->st_size + buf->st_blksize - 1) / buf->st_blksize);
}

int _posix_on_win32_fstat(int fildes, struct stat* buf)
{
    struct _stat64 wbuf;
    int ret = _fstat64(fildes, &wbuf);
    if (ret == -1)
        return -1;

    convert_stat64_to_stat(&wbuf, buf);
    return 0;
}

int _posix_on_win32_stat(const char* path, struct stat* buf)
{
    struct _stat64 wbuf;
    int ret = _stat64(path, &wbuf);
    if (ret == -1)
        return -1;

    convert_stat64_to_stat(&wbuf, buf);
    return 0;
}

// mkstemp is a Linux mkstemp clone, which gets a path
// of the form <path>XXXXXX, where all the X characters at the
// end are turned into something that makes for a unique path.
int mkstemp(char* template)
{
    char parent[MAX_PATH];
    char temppath[MAX_PATH];
    char prefix[MAX_PATH];
    int size; // size of incoming template
    int num_pat; // number of characters to append to the prefix
    char* pat;
    char* name;
    char leaf[MAX_PATH];

    // If the template is too long for a path, give up
    size = strlen(template);
    if (size >= MAX_PATH)
        return -1;

    // Break into parent + prefix + suffix
    pat = template + size - 1;
    while (pat > template && *pat == 'X')
        pat--;

    // Strip off parent - if this is a relative path, then
    // parent = '.'
    if (template[0] == '/' || template[1] == ':')
    {
        name = strrchr(parent, '/');
        strncpy(parent, template, name - template);
        *name = 0;
    }
    else
    {
        name = template;
        strcpy(parent, ".");
    }

    // Get the prefix
    *pat = 0;
    strncpy(prefix, name+1, pat-name);

    // The user wants size-pat characters added to the
    // prefix. If num_pat > 4, then we'll need to generate
    // more prefix on our own, because we are going to generate
    // a random number in the range 1000-9999.
    num_pat = template + size - pat;

    // Start with 1000
    // TBD - ditch GetTempFileNameA and do it all ourselves
    UINT uUnique = 1000;
    UINT result = GetTempFileNameA(parent, leaf, uUnique, temppath);
    if (result == 0)
        return -1;

    // This is not correct, but it's good enough for now
    strncpy(template, temppath, size);

    // Now open it
    return open(template, O_RDWR|O_CREAT|O_EXCL, S_IRUSR|S_IWUSR /*0700*/);
}

int _posix_on_win32_creat(const char *path, mode_t mode)
{
    path = 0; mode = 0;
    return -1;
}

// https://github.com/MicrosoftDocs/cpp-docs/blob/master/docs/c-runtime-library/reference/popen-wpopen.md

int pclose(FILE *stream)
{
    return _pclose(stream);
}

FILE *popen(const char *command, const char *mode)
{
    // TBD massage mode
    return _popen(command, mode);
}
