[!MSVCRT]
// Microsoft has a sys/utime.h, instead of utime.h. We include
// it and build on top of it, of course, disabling Windows-specific
// things we don't want

#pragma push_macro("_CRT_NO_TIME_T")
#undef _CRT_NO_TIME_T
#define _CRT_NO_TIME_T
#pragma push_macro("__STDC__")
#undef __STDC__
#define __STDC__ 1

#include <sys/utime.h>

#pragma pop_macro("_CRT_NO_TIME_T")
#pragma pop_macro("__STDC__")
[/!MSVCRT]
