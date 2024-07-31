/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.execuction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:05:33 by tkoulal           #+#    #+#             */
/*   Updated: 2024/07/31 18:52:33 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_exit_status(t_shell *node)
{
	if (g_exit_status == 1)
		g_exit_status = 1;
	else
		g_exit_status = 127;
	close_fd(node->infile, node->outfile);

}
int	run_exec(t_shell *cmds)
{
	t_shell	*tmp;
	int status;
	int	i;

	cmds->size = cmds_size(cmds);
	tmp = cmds;
	status = 0;
	i = -1;
	while (tmp)
	{
		if (execute(tmp) == 0)
			g_exit_status = 0;
		else
			check_exit_status(tmp);
		tmp = tmp->next;
	}
	tmp = cmds;
	while (tmp && tmp->next)
		tmp = tmp->next;
	signal01();
	waitpid(tmp->pid, &status, 0);
	if (WIFEXITED(status) && cmds->size > 1)
		g_exit_status = WEXITSTATUS(status);
	while (++i < cmds->size - 1)
		wait(NULL);
	return (0);
}

int	execution(t_shell *cmds)
{
	t_shell	*tmp;

	tmp = cmds;
	tmp->pid = 0;
	g_exit_status = 0;
	if (cmds->redirection)
		handle_herdoc(cmds);
	if (cmds->next == NULL && !is_built_in(cmds) && !cmds->redirection)
	{
		if_built_in_run(cmds); // exec builtin
		return (0);
	}
	else if (run_exec(cmds) == ERROR)
		return (ERROR);
	if (tmp->redirection)
		unlick_files(tmp, tmp->redirection, tmp->redirection->herdoc_name);
	return (0);
}
