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

[CDECL]

[CARP endpwent()]void endpwent(void);
[CARP getpwent()]struct passwd* getpwent(void);

[CARP getpwnam()]struct passwd* getpwnam(const char *name);
[CARP getpwnam_r()]int getpwnam_r(const char* name, struct passwd* pwd, char* buffer, size_t bufsize, struct passwd** result);

[CARP getpwuid()]struct passwd* getpwuid(uid_t uid);
[CARP getpwuid_r()]int getpwuid_r(uid_t uid, struct passwd* pwd, char* buffer, size_t bufsize, struct passwd** result);

[CARP setpwent()]void setpwent(void);

[/CDECL]
