/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:22:43 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/29 22:25:12 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_expand_valid(char *str, int i, int j)
{
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
			{
				if (str[i++] == '$')
					return (1);
			}
		}
		j = i + 1;
		if (str[i] == '$' && str[j])
			return (1);
		i++;
	}
	return (0);
}

int	check_expandable_var(t_shell *sh)
{
	t_shell	*tmp;
	int		i;

	tmp = sh;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			if (is_expand_valid(tmp->cmd[i], 0, 0))
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	still_expandable(t_shell *sh)
{
	t_shell	*tmp;
	int		i;

	i = 0;
	tmp = sh;
	if (check_expandable_var(tmp))
		return (1);
	while (tmp->cmd[i])
	{
		if (i && !ft_strncmp(tmp->cmd[i - 1], ">>") && \
			!ft_strncmp(tmp->cmd[i], "$"))
			return (1);
		i++;
	}
	return (0);
}

void	copy_g_exit_status(char *str, int *j)
{
	char	*num;
	int		index;

	num = ft_itoa(g_exit_status);
	index = 0;
	while (num[index])
	{
		str[*j] = num[index];
		*j += 1;
		index++;
	}
	free(num);
}

void	locate_env(t_shell *sh, int	*len, int *j, char *cmd)
{
	char	*env;
	int		i;

	i = 0;
	*j += 1;
	if (cmd[*j] == '?')
		copy_g_exit_status(sh->expander, len);
	if (!cmd[*j])
	{
		sh->expander[*len] = '$';
		*len += 1;
		return ;
	}
	env = get_env_var(cmd, j, sh);
	if (!env)
		return ;
	while (env[i])
	{
		sh->expander[*len] = env[i];
		i++;
		*len += 1;
	}
	free(env);
}
