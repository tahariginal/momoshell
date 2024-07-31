/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:58:22 by tkoulal           #+#    #+#             */
/*   Updated: 2024/07/26 23:50:20 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	if_built_in_run(t_shell *tmp)
{
	if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "pwd"))
		return (ft_pwd(tmp));
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "echo"))
		return (ft_echo(tmp));
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "exit"))
		return (ft_exit(tmp));
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "cd"))
		return (ft_cd(tmp));
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "export"))
		return (ft_export(tmp));
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "env"))
		return (ft_env(tmp->env));
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "unset"))
		return (ft_unset(tmp));
	return (1);
}

int	is_built_in(t_shell *tmp)
{
	if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "pwd"))
		return (0);
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "echo"))
		return (0);
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "exit"))
		return (0);
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "cd"))
		return (0);
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "export"))
		return (0);
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "env"))
		return (0);
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "unset"))
		return (0);
	return (1);
}


char	**lst_arr(t_shell *shell)
{
	t_env	*tmp;
	char	**envir;
	char	*holder;
	char	*buffer;
	int		i;

	i = lstsize(shell->env);
	envir = malloc(sizeof(char *) * (i +1));
	envir[i] = NULL;
	tmp = shell->env;
	i = 0;
	while (tmp)
	{
		holder = ft_strjoin_no_free(tmp->key, "=");
		buffer = ft_strjoin_no_free(holder, tmp->value);
		envir[i] = ft_strdup(buffer);
		free(holder);
		free(buffer);
		i++;
		tmp = tmp->next;
	}
	return (envir);
}
