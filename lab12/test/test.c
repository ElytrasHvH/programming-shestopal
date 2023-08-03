#include "../src/lib.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <check.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define EPSILON 0.00001

int main(void)
{
    int num_failed;
    Suite *s;
    SRunner *sr;

    s = lib_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    num_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return num_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
