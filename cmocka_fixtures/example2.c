#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <cmocka.h>

#define GREETINGS "one string to rule them all, One string to find them, "\
                  "one string to bring them all and in the darkness bind them"
#define PRECIOUSS_T1 "Three strings for the Elven-kings under the sky,"
#define PRECIOUSS_T2 "even for the Dwarf-lords in halls of stone,"
#define PRECIOUSS_T3 "Nine for Mortal Men, doomed to die,"
#define PRECIOUSS_T4 "One for the Dark Lord on his dark throne"
#define PRECIOUSS_T5 "In the Land of Mordor where the Shadows lie."
#define PRECIOUSS_T6 "One string to rule them all, One Ring to find them,"
#define PRECIOUSS_T7 "One string to bring them all and in the darkness bind them."
#define PRECIOUSS_T8 "In the Land of Mordor where the Shadows lie."
#define OOPS "Not quite what I expected"
#define T(X) PRECIOUSS_T##X

#define FOO(X) case X: strncpy(lots->memory, T(X), sizeof(T(X))); break;
#define SPR_FOO(X) case X: assert_string_equal(T(X), lots->memory); break;

typedef struct {
          int    line;
          char * memory;
} lord_of_the_strings_t;

static int gr_setup(void **state) {
     /* this is run once before all group tests */
     lord_of_the_strings_t *book = malloc(sizeof(*book));
     if (book == NULL)
         return -1;
     book->memory = malloc(sizeof(GREETINGS));
     if (book->memory == NULL) {
         return -1;
     }

     strncpy(book->memory, GREETINGS, sizeof(GREETINGS));
     assert_string_equal(book->memory, GREETINGS);
     *state = book;
     return 0;
}

static int gr_teardown(void **state) {
     /* this is run once after all group tests */
     lord_of_the_strings_t *lots = *state;
     free(lots->memory);
     free(lots);
     return 0;
}

static int ve_teardown(void **state) {
     /* this is run before some single tests */
     lord_of_the_strings_t *lots = *state;
     lots->line = 42;
     return 0;
}

static int ve_setup(void **state) {
     /* this is run after some single tests */
     static int setup_counter = 0;
     lord_of_the_strings_t *lots = *state;
     lots->line = ++setup_counter;
     switch (setup_counter) {
        FOO(1)
        FOO(2)
        FOO(3)
        FOO(4)
        FOO(5)
        FOO(6)
        FOO(7)
        FOO(8)
        default:
           strncpy(lots->memory, OOPS, sizeof(OOPS));
     };
     return 0;
}

static void failing_test(void **state) {
     assert_false("Sorry");
}

static void line_aware_test(void **state) {
     lord_of_the_strings_t *lots = *state;
     printf("             (shared) between tests, line=%d memory=%s\n", lots->line, lots->memory);
}

static void passing_test(void **state) {
}
static void string_recite_test(void **state) {
     static int line_counter = 0;
     lord_of_the_strings_t *lots = *state;
     if (lots->line < 9)
        assert_true(line_counter+1 == lots->line);
     switch (++line_counter) {
        SPR_FOO(1)
        SPR_FOO(2)
        SPR_FOO(3)
        SPR_FOO(4)
        SPR_FOO(5)
        SPR_FOO(6)
        SPR_FOO(7)
        SPR_FOO(8)
        default:
            line_counter = 0;
     }
}


int main(void) {
        const struct CMUnitTest tests[] = {
            cmocka_unit_test(passing_test),
            cmocka_unit_test_setup_teardown(string_recite_test, ve_setup, ve_teardown),
            cmocka_unit_test_setup_teardown(string_recite_test, ve_setup, ve_teardown),
            cmocka_unit_test_setup_teardown(string_recite_test, ve_setup, ve_teardown),
            cmocka_unit_test(line_aware_test),
            cmocka_unit_test(line_aware_test),
            cmocka_unit_test_setup_teardown(string_recite_test, ve_setup, ve_teardown),
            cmocka_unit_test_setup_teardown(string_recite_test, ve_setup, ve_teardown),
            cmocka_unit_test_setup_teardown(string_recite_test, ve_setup, ve_teardown),
            cmocka_unit_test(line_aware_test),
            cmocka_unit_test_setup_teardown(string_recite_test, ve_setup, ve_teardown),
            cmocka_unit_test_setup_teardown(string_recite_test, ve_setup, ve_teardown),
            cmocka_unit_test_setup_teardown(string_recite_test, ve_setup, ve_teardown),
            cmocka_unit_test_setup_teardown(string_recite_test, ve_setup, ve_teardown),
            cmocka_unit_test_setup_teardown(string_recite_test, ve_setup, ve_teardown),
            cmocka_unit_test(line_aware_test),
            cmocka_unit_test_setup_teardown(string_recite_test, ve_setup, ve_teardown),
            cmocka_unit_test_setup_teardown(string_recite_test, ve_setup, ve_teardown),
            cmocka_unit_test_setup_teardown(string_recite_test, ve_setup, ve_teardown),
            cmocka_unit_test_setup_teardown(string_recite_test, ve_setup, ve_teardown),
            cmocka_unit_test(failing_test),
        };
        return cmocka_run_group_tests(tests, gr_setup, gr_teardown);
}
