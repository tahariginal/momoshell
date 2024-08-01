/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 20:02:56 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/30 23:50:23 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_unset(t_shell *sh)
{
	t_env	*envp;
	t_env	*envp_cp;
	int		i;

	envp = sh->env;
	envp_cp = sh->env_copy;
	i = 1;
	while (sh->cmd[i])
	{
		if (is_in_env(sh, sh->cmd[i], 0))
			remove_from_export(sh, sh->cmd[i]);
		if (is_in_env(sh, sh->cmd[i], 1))
			remove_from_env(sh, sh->cmd[i]);
		i++;
	}
	return (0);
}

int	ft_exit(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->cmd[1])
	{
		while (shell->cmd[1])
		{
			if (shell->cmd[1][i] < '0' || shell->cmd[1][i] > '9')
			{
				write(2, "minishell: invalid argument, takes only integers\n", 49);
				exit(2);
			}
			i++;
		}
		g_exit_status = ft_atoi(shell->cmd[1]);
	}
	clean_up(shell, 1);
	write(1, "exit\n", 5);
	exit(g_exit_status);
}
