// errno.h
//
// POSIX.1-2008.7 pwd.h header file
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/pwd.h.html

#pragma once
#ifndef _POSIX_ON_WIN32__PWD_H
#define _POSIX_ON_WIN32__PWD_H

// There is no Microsoft <pwd.h> file, so we don't need to override anything.

// -----------------------------------------------------------------------------------------------

// These are 32-bit even on 64-bit systems
typedef unsigned long uid_t;
typedef unsigned long gid_t;

// The passwd structure
struct passwd
{
  char *pw_name;        /* Username.  */
  char *pw_passwd;      /* Password.  */
  uid_t pw_uid;         /* User ID.  */
  gid_t pw_gid;         /* Group ID.  */
  char *pw_gecos;       /* Real name.  */
  char *pw_dir;         /* Home directory.  */
  char *pw_shell;       /* Shell program.  */
};

#ifdef _WIN64
typedef unsigned long long size_t;
#else
typedef unsigned int size_t;
#endif

void endpwent(void);
struct passwd *getpwent(void);

struct passwd *getpwnam(const char *name);
int getpwnam_r(const char *name, struct passwd *pwd, char *buffer, size_t bufsize, struct passwd **result);

struct passwd *getpwuid(uid_t uid);
int getpwuid_r(uid_t uid, struct passwd *pwd, char *buffer,
       size_t bufsize, struct passwd **result);

void setpwent(void);

// -----------------------------------------------------------------------------------------------

#endif // _POSIX_ON_WIN32__PWD_H
