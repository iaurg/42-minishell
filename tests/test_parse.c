#include "../includes/minishell.h"
#include "minunit.h"

void test_setup(void) {
}

void test_teardown(void) {
}

MU_TEST(simple_token) {
	char *test_string = "ls -la";
	char **parsed = parse_input(test_string);
	mu_assert_string_eq("ls", parsed[0]);
	mu_assert_string_eq("-la", parsed[1]);
	mu_assert_string_eq(NULL, parsed[2]);
}

MU_TEST(token_with_trailing_whitespace) {
	char *test_string = "ls -la     ";
	char **parsed = parse_input(test_string);
	mu_assert_string_eq("ls", parsed[0]);
	mu_assert_string_eq("-la", parsed[1]);
	mu_assert_string_eq(NULL, parsed[2]);
}

MU_TEST(token_with_leading_whitespace) {
	char *test_string = "    ls -la";
	char **parsed = parse_input(test_string);
	mu_assert_string_eq("ls", parsed[0]);
	mu_assert_string_eq("-la", parsed[1]);
	mu_assert_string_eq(NULL, parsed[2]);
}

MU_TEST(token_with_space_between) {
	char *test_string = "ls    -la";
	char **parsed = parse_input(test_string);
	mu_assert_string_eq("ls", parsed[0]);
	mu_assert_string_eq("-la", parsed[1]);
	mu_assert_string_eq(NULL, parsed[2]);
}

MU_TEST(token_with_pipe) {
	char *test_string = "ls -la | ls";
	char **parsed = parse_input(test_string);
	mu_assert_string_eq("ls", parsed[0]);
	mu_assert_string_eq("-la", parsed[1]);
	mu_assert_string_eq("|", parsed[2]);
	mu_assert_string_eq("ls", parsed[3]);
}

MU_TEST(token_with_higher) {
	char *test_string = "ls -la > file";
	char **parsed = parse_input(test_string);
	mu_assert_string_eq("ls", parsed[0]);
	mu_assert_string_eq("-la", parsed[1]);
	mu_assert_string_eq(">", parsed[2]);
	mu_assert_string_eq("file", parsed[3]);
	mu_assert_string_eq(NULL, parsed[4]);
}

MU_TEST(token_with_lesser) {
	char *test_string = "ls -la < file";
	char **parsed = parse_input(test_string);
	mu_assert_string_eq("ls", parsed[0]);
	mu_assert_string_eq("-la", parsed[1]);
	mu_assert_string_eq("<", parsed[2]);
	mu_assert_string_eq("file", parsed[3]);
	mu_assert_string_eq(NULL, parsed[4]);
}

MU_TEST(token_with_append) {
	char *test_string = "ls -la >> file";
	char **parsed = parse_input(test_string);
	mu_assert_string_eq("ls", parsed[0]);
	mu_assert_string_eq("-la", parsed[1]);
	mu_assert_string_eq(">>", parsed[2]);
	mu_assert_string_eq("file", parsed[3]);
	mu_assert_string_eq(NULL, parsed[4]);
}

MU_TEST(token_with_semicolon) {
	char *test_string = "ls -la;";
	char **parsed = parse_input(test_string);
	mu_assert_string_eq("ls", parsed[0]);
	mu_assert_string_eq("-la", parsed[1]);
	mu_assert_string_eq(";", parsed[2]);
	mu_assert_string_eq(NULL, parsed[3]);
}

MU_TEST(token_with_backslash) {
	char *test_string = "ls\\ -la";
	char **parsed = parse_input(test_string);
	mu_assert_string_eq("ls", parsed[0]);
	mu_assert_string_eq("\\", parsed[1]);
	mu_assert_string_eq("-la", parsed[2]);
	mu_assert_string_eq(NULL, parsed[3]);
}

MU_TEST(token_with_backslash_and_newline) {
	char *test_string = "ls \\ \n -la";
	char **parsed = parse_input(test_string);
	mu_assert_string_eq("ls", parsed[0]);
	mu_assert_string_eq("\\", parsed[1]);
	mu_assert_string_eq("\n", parsed[2]);
	mu_assert_string_eq("-la", parsed[3]);
	mu_assert_string_eq(NULL, parsed[4]);
}

MU_TEST(token_with_single_quote) {
	char *test_string = "echo \'ls -la";
	char **parsed = parse_input(test_string);
	mu_assert_string_eq("echo", parsed[0]);
	mu_assert_string_eq("\'", parsed[1]);
	mu_assert_string_eq("ls", parsed[2]);
	mu_assert_string_eq("-la", parsed[3]);
	mu_assert_string_eq(NULL, parsed[4]);
}

MU_TEST(token_with_dollar_sign) {
	char *test_string = "ls -la $";
	char **parsed = parse_input(test_string);
	mu_assert_string_eq("ls", parsed[0]);
	mu_assert_string_eq("-la", parsed[1]);
	mu_assert_string_eq("$", parsed[2]);
	mu_assert_string_eq(NULL, parsed[3]);
}

MU_TEST(token_with_empty_expression) {
	char *test_string = "ls -la $()";
	char **parsed = parse_input(test_string);
	mu_assert_string_eq("ls", parsed[0]);
	mu_assert_string_eq("-la", parsed[1]);
	mu_assert_string_eq("$(", parsed[2]);
	mu_assert_string_eq(")", parsed[3]);
	mu_assert_string_eq(NULL, parsed[4]);
}

MU_TEST(token_with_precedent_expression_a) {
	char *test_string = "echo $(echo hello)";
	char **parsed = parse_input(test_string);
	mu_assert_string_eq("echo", parsed[0]);
	mu_assert_string_eq("$(", parsed[1]);
	mu_assert_string_eq("echo", parsed[2]);
	mu_assert_string_eq("hello", parsed[3]);
	mu_assert_string_eq(")", parsed[4]);
	mu_assert_string_eq(NULL, parsed[5]);
}

MU_TEST(token_with_precedent_expression_b) {
	char *test_string = "ls $(echo -la)";
	char **parsed = parse_input(test_string);
	mu_assert_string_eq("ls", parsed[0]);
	mu_assert_string_eq("$(", parsed[1]);
	mu_assert_string_eq("echo", parsed[2]);
	mu_assert_string_eq("-la", parsed[3]);
	mu_assert_string_eq(")", parsed[4]);
	mu_assert_string_eq(NULL, parsed[5]);
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
	MU_RUN_TEST(simple_token);
	MU_RUN_TEST(token_with_trailing_whitespace);
	MU_RUN_TEST(token_with_leading_whitespace);
	MU_RUN_TEST(token_with_space_between);
	MU_RUN_TEST(token_with_pipe);
	MU_RUN_TEST(token_with_higher);
	MU_RUN_TEST(token_with_lesser);
	MU_RUN_TEST(token_with_append);
	MU_RUN_TEST(token_with_semicolon);
	MU_RUN_TEST(token_with_single_quote);
	MU_RUN_TEST(token_with_dollar_sign);
	MU_RUN_TEST(token_with_empty_expression);
	MU_RUN_TEST(token_with_backslash);
	MU_RUN_TEST(token_with_backslash_and_newline);
	//MU_RUN_TEST(token_with_precedent_expression_a);
	//MU_RUN_TEST(token_with_precedent_expression_b);
}

int main(int argc, char *argv[])
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
