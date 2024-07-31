/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:12:25 by tkoulal           #+#    #+#             */
/*   Updated: 2024/07/31 11:22:17 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    **find_path(t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PATH"))
			return (ft_split(tmp->value, ":"));
		tmp = tmp->next;
	}
	return (NULL);
}

char *get_cmd(char *cmd, t_env *envp)
{
	char **arr;
	char *pathcmd;
	char *tmp_pathcmd;
	int i;

	i = -1;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) != -1)
			return (ft_strdup(cmd));
		return (NULL);
	}
	arr = find_path(envp);
	if (!arr)
		return (printf("path not found\n"),g_exit_status = 127, NULL);
	while (arr && arr[++i])
	{
		tmp_pathcmd = ft_strjoin("/", cmd);
		pathcmd = ft_strjoin(arr[i], tmp_pathcmd);
		free(tmp_pathcmd);
		if (access(pathcmd, F_OK | X_OK) != -1)
			return (free_array(arr), pathcmd);
		free(pathcmd);
	}
	return (free_array(arr), NULL);
}

void	close_fd(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
}

int	open_pipes(t_shell *node, int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		g_exit_status = 1;
		return (ERROR);
	}
	node->next->infile = pipe_fd[0];
	node->outfile = pipe_fd[1];
	return (SUCCESS);
}

void	ft_dup2(t_shell *node)
{
	if (dup2(node->infile, STDIN_FILENO) == -1)
	{
		printf("minishell: dup2: %s\n", strerror(errno));
		g_exit_status = 1;
		clean_up(node, 0);
		exit(EXIT_FAILURE);
	}
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	if (dup2(node->outfile, STDOUT_FILENO) == -1)
	{
		printf("minishell: dup2: %s\n", strerror(errno));
		g_exit_status = 1;
		clean_up(node, 0);
		exit(EXIT_FAILURE);
	}
	if (node->outfile != STDOUT_FILENO)
		close(node->outfile);
}