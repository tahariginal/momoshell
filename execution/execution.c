/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:10:44 by tkoulal           #+#    #+#             */
/*   Updated: 2024/07/31 11:40:18 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	run_builtins_pipe(t_shell *node)
{
	int	err;

	err = if_built_in_run(node);
	if (err)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	child_pross(t_shell *node, char **envp, char *new_cmd)
{
	ft_dup2(node);

	if (node->next)
		if (node->next->infile != STDIN_FILENO)
			close(node->next->infile);
	if (!is_built_in(node))
		exit(run_builtins_pipe(node));
	if (execve(new_cmd, node->cmd, envp) == -1)
	{
		// perror(node->cmd[0]);
		clean_up(node, 0);
		free_array(envp);
		exit(127);
		return (1);
	}
	return (0);
}

int	execute_cmd(t_shell *node)
{
	char **envp;
	char *new_cmd;

	envp = lst_arr(node);
	new_cmd = get_cmd(node->cmd[0] ,node->env);
	if (!new_cmd && is_built_in(node))
	{
		printf("%s :command not found\n", node->cmd[0]);
		free_array(envp);
		g_exit_status = 127;
		return (ERROR);
	}
	node->pid = fork();
	signal(SIGQUIT, SIG_DFL);
	if (node->pid < 0)
	{
		printf("minishell: fork: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
		g_exit_status = 1;
	}
	if (node->pid == 0)
		if (child_pross(node, envp, new_cmd) == 1)
			return (1);
	free_array(envp);
	free(new_cmd);
	return (SUCCESS);
}

int	execute(t_shell *node)
{
	int	pipe_fd[2];
	int	status;

	node->pid = 0;
	status = 0;
	if (node->next != NULL)
	{
		if (open_pipes(node, pipe_fd) == ERROR)
			return (ERROR);
	}
	else
		node->outfile = STDOUT_FILENO;
	if (node->redirection != NULL)
	{
		status = handel_redirection(node);
		if (status < 0 || status == 1)
		{
			close_fd(node->infile, node->outfile);
			g_exit_status = 1;
			return (g_exit_status);
		}
	}
	if (execute_cmd(node) == ERROR)
		return (ERROR);
	close_fd(node->infile, node->outfile);
	return (SUCCESS);
}