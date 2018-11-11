// main.c

int test_assert();    // in test-assert-posix.c
int test_fcntl();     // in test-fcntl-posix.c
int test_pwd();       // in test-pwd-posix.c
int test_stdarg();    // in test-stdarg-posix.c
int test_stddef();    // in test-stddef-posix.c
int test_stdio();     // in test-stdio-posix.c
int test_stdlib();    // in test-stdlib-posix.c
int test_string();    // in test-string-posix.c
int test_sys_mman();  // in test-sys_mman-posix.c
int test_sys_stat();  // in test-sys_stat-posix.c
int test_sys_types(); // in test-sys_types-posix.c
int test_time();      // in test-time-posix.c

int main(int argc, char** argv)
{
    argc = 0; argv = 0;

    test_assert();
    test_fcntl();
    test_pwd();
    test_stdarg();
    test_stddef();
    test_stdio();
    test_stdlib();
    test_string();
    test_sys_mman();
    test_sys_stat();
    test_sys_types();

    return 0;
}
