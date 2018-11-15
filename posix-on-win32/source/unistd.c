// unistd.c

#define WIN32_LEAN_AND_MEAN
#define __STDC__ 1
#define _CRT_NO_TIME_T

#include <errno.h>
#include <pwd.h>
#include <unistd.h>

#include <io.h> // for _access

#include <Windows.h>
#define SECURITY_WIN32
#include <security.h>

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
    // if (xbit != 0) mode |= ???

    int rv = _access(path, mode);
    //int err = errno;
    return rv;
}

// Not really a multiuser machine, so we are always UID 100
uid_t getuid(void)
{
    return 100;
}

// If this is UID 100, then get the user name
struct passwd* getpwuid(uid_t uid)
{
    if (uid != 100)
    {
        return NULL;
    }

    static char name[256];
    static char dir[256];
    static char shell[256];
    static char passwd[256];
    static char gecos[256];

    DWORD size = 256;
    GetUserNameA(name, &size);
    size = 256;
    GetCurrentDirectoryA(size, dir);
    strcpy(shell, "cmd.exe");
    strcpy(passwd, "x");
    size = 256;
    GetUserNameExA(NameSamCompatible, gecos, &size); // NameDisplay only possible on machine on domain

    static struct passwd pw;
    pw.pw_name = name;
    pw.pw_uid = uid;
    pw.pw_gid = 100;
    pw.pw_dir = dir;
    pw.pw_shell = shell;
    pw.pw_passwd = passwd;
    pw.pw_gecos = gecos;

    return &pw;
}
