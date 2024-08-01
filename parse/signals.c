/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:46:50 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/31 23:50:14 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctrl_c_her(int signal)
{
	g_exit_status = 130;
	if (signal == SIGINT)
		exit(130);
}

void	ctrl_d_her(void)
{
	g_exit_status = 0;
	write(1, "minishell: you have exited without specifying a delimeter\n", 58);
	exit(g_exit_status);
}

void	cntl_d(t_shell *sh, t_env *env, t_env *envp)
{
	(void)sh;
	rl_on_new_line();
	rl_clear_history();
	write(1, "exit\n", 5);
	clean_lst(env);
	clean_lst(envp);
	exit(g_exit_status);
}
