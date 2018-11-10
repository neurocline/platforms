// main.c

int test_assert(); // in test-assert-posix.c
int test_stdarg(); // in test-assert-stdarg.c

int main(int argc, char** argv)
{
    argc = 0; argv = 0;

    test_assert();
    test_stdarg();

    return 0;
}
