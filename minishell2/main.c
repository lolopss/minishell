/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldaniel <ldaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:29:41 by ldaniel           #+#    #+#             */
/*   Updated: 2023/08/25 13:22:31 by ldaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_command(char *cmd, char *path)
{
	char	*path_name;
	path_name = ft_strjoin(path, cmd);
	if (!access(path_name, F_OK | X_OK))
		return (0);
	return (1);
}


void	run_command(char **path, char **env, char *p)
{
	char	**arg;
	int		j;
	int		verify;

	arg = ft_split(p, ' ');
	j = -1;
	verify = 0;
	if (ft_strcomp("cd", arg[0]))
	{
		if (chdir(arg[1]) != 0)
			printf("can't open, not a directory\n");
		free(arg);
		return ;
	}
	if (ft_strcomp("exit", p))
	{
		free(arg);
		exit(0);
	}
	while (path[++j])
		if (!verify_command(arg[0], path[j]))
			if (execve(ft_strjoin(path[j], arg[0]), arg, env) != -1)
				verify++;
	if (!verify)
		printf("Command '%s' not found\n", arg[0]);
	free(arg);
}

void	handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char	**get_env(void)
{
	int		j;
	char	**path;

	path = ft_split(getenv("PATH"), ':');
	j = -1;
	while (path[++j])
		path[j] = ft_strjoin(path[j], "/");
	return (path);
}

int	running(t_data *data, char **env)
{
	if (!data->str)
		return (0);
	add_history(data->str);
	data->pid = fork();
	if (data->pid == -1)
		return (0);
	if (!data->pid)
	{
		/*if (ft_strcomp("exit", data->p))
		{
			printf("%d  |  %s\n", ft_strcomp("exit", data->p), data->p);
			printf("yo\n");
			exit (1);
		}*/
		run_command(data->path, env, data->str);
	}
	else if (data->pid)
	{
		/*if (ft_strcomp("exit", data->p))
			return (0);*/
		wait(NULL);
		kill(data->pid, SIGKILL);
	}
	return (1);
}

int	main(void)
{
	t_data data;

	while (1)
	{
		if (signal(SIGINT, handle_signal) == SIG_ERR)
			printf("failed to catch signal\n");
		data.env = get_env();
		data.path = get_env();
		data.str = readline("Minishell$> ");
		if (data.str)
		{
			if (data.str[0] != '\0' && ft_strcomp("exit", data.str) == 1)
				exit(0);
			running(&data, data.env);
		}
	}
	return (0);
}