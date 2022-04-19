#include "minunit.h"
#include "../includes/minishell.h"

MU_TEST(test_check) {
	mu_check(5 == 5);
}
MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test_check);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
