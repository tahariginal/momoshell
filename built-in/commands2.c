/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 20:02:56 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/27 22:49:57 by hbenazza         ###   ########.fr       */
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
	clean_up(shell, 1);
	write(1, "exit\n", 5);
	exit(g_exit_status);
}
