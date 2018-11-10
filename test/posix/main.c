// main.c

int test_assert(); // in test-assert-posix.c
int test_stdarg(); // in test-assert-stdarg.c
int test_stdlib(); // in test-assert-stdlib.c

int main(int argc, char** argv)
{
    argc = 0; argv = 0;

    test_assert();
    test_stdarg();
    test_stdlib();

    return 0;
}
