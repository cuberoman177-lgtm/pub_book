#include "minunit.h"
#include "book_utils.h"

void test_setup(void) {
}

void test_teardown(void) {
	/* Nothing */
}

char* fgets(char s[CHOICE_LEN], int size, FILE *stream){
	fprintf(stderr, "* * %s * *\n", s);
	return s;
}


MU_TEST(test_search_with_bad_parameters) {
    char input[] ={0};
    search(NULL, input);
    mu_assert(input[0] == 0, "search failed");
    search(input, NULL);
    mu_assert(input[0] == 0, "search failed");
}

MU_TEST(test_search_choice) {
    char choice[] = "2\n";
    char input[] = "Arthur Conan Doyle";
    search(choice, input);
    fprintf(stderr, "* * %s * *\n", input);
    mu_assert_string_eq(input, "Arthur+Conan+Doyle");
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_search_with_bad_parameters);
	MU_RUN_TEST(test_search_choice);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
