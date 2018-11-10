// main.c

int test_assert(); // in test-assert-posix.c
int test_fcntl();  // in test-fcntl-posix.c
int test_stdarg(); // in test-stdarg-posix.c
int test_stdlib(); // in test-stdlib-posix.c

int main(int argc, char** argv)
{
    argc = 0; argv = 0;

    test_assert();
    test_fcntl();
    test_stdarg();
    test_stdlib();

    return 0;
}
