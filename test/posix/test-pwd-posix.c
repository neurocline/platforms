// test-pwd-posix.c

#include <assert.h>
#include <stddef.h>
#include <pwd.h>

int test_pwd()
{
    struct passwd pw = {0};
    pw.pw_name = "someguy";
    assert(offsetof(struct passwd, pw_name) >= 0);
    assert(offsetof(struct passwd, pw_uid) >= 0);
    assert(offsetof(struct passwd, pw_gid) >= 0);
    assert(offsetof(struct passwd, pw_dir) >= 0);
    assert(offsetof(struct passwd, pw_shell) >= 0);
    return 0;
}
