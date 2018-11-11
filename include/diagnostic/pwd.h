// <pwd.h>
//
// Diagnostic header that prints out usage of items
// See canonical pwd.h for documentation on contents

#ifndef DIAGNOSTIC_POSIX_2017_PWD_H
#define DIAGNOSTIC_POSIX_2017_PWD_H

#include <internal/carp.h>

// gid_t, uid_t, and size_t, as in <sys/types.h>
typedef unsigned int gid_t; // Used for group IDs
typedef unsigned int uid_t; // Used for user IDs

#ifdef _WIN64
typedef unsigned long long size_t;
#else
typedef unsigned int size_t;
#endif

// The passwd structure
struct passwd
{
    // POSIX fields
    char* pw_name;      // User's login name
    uid_t pw_uid;       // Numerical user ID
    gid_t pw_gid;       // Numerical group ID
    char* pw_dir;       // Initial working directory
    char* pw_shell;     // Program to use as shell

    // Linux (and old Unix)
    char* pw_passwd;    // User's password
    char* pw_gecos;     // User realname (and other personal data)
};

void endpwent(void);
struct passwd* getpwent(void);

struct passwd* getpwnam(const char *name);
int getpwnam_r(const char* name, struct passwd* pwd, char* buffer, size_t bufsize, struct passwd** result);

struct passwd* getpwuid(uid_t uid);
int getpwuid_r(uid_t uid, struct passwd* pwd, char* buffer, size_t bufsize, struct passwd** result);

void setpwent(void);

#endif // DIAGNOSTIC_POSIX_2017_PWD_H
