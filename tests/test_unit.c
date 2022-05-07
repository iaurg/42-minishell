#include "../includes/minishell.h"
#include "minunit.h"

void test_setup(void) {
}

void test_teardown(void) {
}

/* export */
MU_TEST(export_key) {
	t_command *cmd;
	char *envp[] = {"PATH=/bin", "HOME=/home", "PWD=/home/user", NULL};
	char *argv[] = {"export", "HELLO", NULL};
	cmd = init_builtins(envp);
	cmd->argv = argv;
	builtins_export(cmd);
	t_list *tmp = lst_find(cmd->envp, argv[1]);
	// does not write a value for that key
	mu_check(tmp->value == NULL);
}

MU_TEST(export_key_value) {
	t_command *cmd;
	char *envp[] = {"PATH=/bin", "HOME=/home", "PWD=/home/user", NULL};
	char *argv[] = {"export", "HELLO=world", NULL};
	cmd = init_builtins(envp);
	cmd->argv = argv;
	builtins_export(cmd);
	char *token = ft_strtok(argv[1], "=");
	char *tmp = ms_getenv(cmd->envp, token);

	mu_assert_string_eq(tmp, "world");
}

MU_TEST_SUITE(export_suite) {
	MU_RUN_TEST(export_key);
	MU_RUN_TEST(export_key_value);
}

/* unset */
MU_TEST(unset_one_key) {
	t_command *cmd;
	char *envp[] = {"PATH=/bin", "HOME=/home", "PWD=/home/user", NULL};
	char *argv[] = {"unset", "PATH", NULL};
	cmd = init_builtins(envp);
	cmd->argv = argv;
	builtins_unset(cmd);
	char *tmp = ms_getenv(cmd->envp, "PATH");
	mu_check(tmp == NULL);
}

MU_TEST(unset_multiple_keys) {
	t_command *cmd;
	char *envp[] = {"PATH=/bin", "HOME=/home", "PWD=/home/user", NULL};
	char *argv[] = {"unset", "PATH", "HOME", NULL};
	cmd = init_builtins(envp);
	cmd->argv = argv;
	builtins_unset(cmd);
	char *tmp = ms_getenv(cmd->envp, "PATH");
	mu_check(tmp == NULL);
	tmp = ms_getenv(cmd->envp, "HOME");
	mu_check(tmp == NULL);
}

MU_TEST_SUITE(unset_suite) {
	MU_RUN_TEST(unset_one_key);
	MU_RUN_TEST(unset_multiple_keys);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(export_suite);
	MU_RUN_SUITE(unset_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
