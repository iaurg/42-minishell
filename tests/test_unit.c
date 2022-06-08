#include "minishell.h"
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

MU_TEST(cd_no_args) {
	t_command *cmd;
	char *envp[] = {"PATH=/bin", "HOME=/home/user", "PWD=/home/user/bin", NULL};
	char *argv[] = {"cd", NULL};
	cmd = init_builtins(envp);
	cmd->argv = argv;
	cmd->argc = 1;
	builtins_cd(cmd);
	char *tmp = ms_getenv(cmd->envp, "HOME");
	mu_assert_string_eq(tmp, "/home/user");
}

MU_TEST(cd_single_period) {
	t_command *cmd;
	char buf[1026];
	getcwd(buf, sizeof(buf));
	char *pwd = ft_strjoin("PWD=", buf);
	char *envp[] = {"PATH=/bin", "HOME=/home/user", pwd, NULL};
	char *argv[] = {"cd", ".", NULL};
	cmd = init_builtins(envp);
	cmd->argv = argv;
	cmd->argc = 2;
	builtins_cd(cmd);
	char *tmp = ms_getenv(cmd->envp, "PWD");
	mu_check(strlen(tmp) == strlen(buf));
}

MU_TEST(cd_double_period) {
	t_command *cmd;
	char buf[1026];
	getcwd(buf, sizeof(buf));
	char *pwd = ft_strjoin("PWD=", buf);
	char *envp[] = {"PATH=/bin", "HOME=/home/user", pwd, NULL};
	char *argv[] = {"cd", "..", NULL};
	cmd = init_builtins(envp);
	cmd->argv = argv;
	cmd->argc = 2;
	builtins_cd(cmd);
	char *tmp = ms_getenv(cmd->envp, "PWD");
	mu_check(strlen(tmp) != strlen(buf));
}

MU_TEST(cd_root) {
	t_command *cmd;
	char buf[1026];
	getcwd(buf, sizeof(buf));
	char *pwd = ft_strjoin("PWD=", buf);
	char *envp[] = {"PATH=/bin", "HOME=/home/user", pwd, NULL};
	char *argv[] = {"cd", "/", NULL};
	cmd = init_builtins(envp);
	cmd->argv = argv;
	cmd->argc = 2;
	builtins_cd(cmd);
	char *tmp = ms_getenv(cmd->envp, "PWD");
	mu_check(strlen(tmp) == 1);
}

MU_TEST(cd_slash_home) {
	t_command *cmd;
	char buf[1026];
	getcwd(buf, sizeof(buf));
	char *pwd = ft_strjoin("PWD=", buf);
	char *envp[] = {"PATH=/bin", "HOME=/home/user", pwd, NULL};
	char *argv[] = {"cd", "/home", NULL};
	cmd = init_builtins(envp);
	cmd->argv = argv;
	cmd->argc = 2;
	builtins_cd(cmd);
	char *tmp = ms_getenv(cmd->envp, "PWD");
	mu_check(strlen(tmp) == strlen("/home"));
}

MU_TEST_SUITE(cd_suite) {
	MU_RUN_TEST(cd_no_args);
	MU_RUN_TEST(cd_single_period);
	MU_RUN_TEST(cd_double_period);
	MU_RUN_TEST(cd_root);
	MU_RUN_TEST(cd_slash_home);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(export_suite);
	MU_RUN_SUITE(unset_suite);
	MU_RUN_SUITE(cd_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
