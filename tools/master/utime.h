[NOWINDOWS]
// <utime.h>
// - access and modification times structure
//
// Defined in POSIX.1-2017 <utime.h>
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/utime.h.html

#pragma once
[GUARD_POSIX]

[BODY]
[!MSVCRT]
// Microsoft has a sys/utime.h, instead of utime.h. We include
// it and build on top of it.
#include <sys/utime.h>
[/!MSVCRT]

[FOOTER]
[/GUARD_POSIX]
