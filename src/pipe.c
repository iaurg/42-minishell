int	ft_matlen(char *mat[])
{
	int	i;

	i = 0;
	if (mat[i] == NULL)
		return (0);
	while (mat[i])
		i++;
	return (i);
}

int	is_not_pipe(char *arg)
{
	return ((arg != NULL) || ft_strncmp(arg, "|", 2) != 0);
}

int	split_next_command(char *buff[]; const char *args[], initial_pos)
{
	int		final_pos;
	char	**commands;
	int		i;
	int		j;

	final_pos = initial_pos + 1;
	if (args[initial_pos] == NULL)
		return (0);
	while (is_not_pipe(args[final_pos]))
		final_pos++;
	j = 0;
	free(buff);
	buff = malloc(sizeof(char *) * (final_pos - initial_pos + 1));
	i = initial_pos;
	while (++i < final_pos)
		buff[j++] = ft_strdup(args[i]);
	buff[j] = NULL;
	return (final_pos);
}

int	run_pipe(t_command *cmd)
{
	int		i;
	int		fd[2];
	char	**args;
	int		initial_pos;

	initial_pos = 0;
	while (is_not_pipe(args[initial_pos]))
		initial_pos++;
	i = 0;
	args = malloc(sizeof(char *) * ft_matlen(cmd->argv));
	while (cmd->argv[i])
		args[i++] = ft_strdup(cmd->argv[i]);
	args[i] = NULL;
	fd[INPUT] = dup(STDIN_FILENO);
	initial_pos = split_next_command(cmd->argv, args, initial_pos);
	while (initial_pos)
	{
		initial_pos = split_next_command(cmd->argv, args, initial_pos);
		execute(cmd);
	}
}
