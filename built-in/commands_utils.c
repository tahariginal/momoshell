/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 21:53:38 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/29 22:29:32 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	run_option(t_shell *sh)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = 0;
	if (check_option(sh->cmd[i]))
		return (0);
	while (sh->cmd[i])
	{
		j = i;
		if (check_option(sh->cmd[i]))
			flag = 1;
		if (flag && sh->cmd[++j])
			printf("%s ", sh->cmd[i]);
		else if (flag)
			printf("%s", sh->cmd[i]);
		i++;
	}
	return (1);
}

int	check_option(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if ((i == 0) && str[i] != '-')
			return (1);
		if (i >= 1 && str[i] != 'n')
			return (1);
		i++;
	}
	return (SUCCESS);
}

void	set_current_dir(t_shell *sh)
{
	t_env	*tmp;
	char	*pwd;

	tmp = sh->env;
	pwd = getcwd(NULL, 0);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(pwd);
		}
		tmp = tmp->next;
	}
	tmp = sh->env_copy;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(pwd);
		}
		tmp = tmp->next;
	}
	free(pwd);
}

void	get_old_dir(t_shell *sh, char *oldpwd)
{
	t_env	*tmp;

	tmp = sh->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "OLDPWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(oldpwd);
		}
		tmp = tmp->next;
	}
	tmp = sh->env_copy;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "OLDPWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(oldpwd);
		}
		tmp = tmp->next;
	}
}

int	export_to_env(t_shell *sh)
{
	t_shell	*n;
	int		i;
	int		j;

	n = sh;
	i = 1;
	while (n->cmd[i])
	{
		j = 0;
		while (n->cmd[i][j] && (n->cmd[i][j] == ' ' || n->cmd[i][j] == '\t'))
			j++;
		if (n->cmd[i][j] == '=')
			return (g_exit_status = 13, printf("bad assignemet\n"), 13);
		if (ft_strchr(n->cmd[i], '=') && !is_in_env(n, n->cmd[i], 1))
		{
			ft_lstadd_back_env(&n->env, ft_lstnew_env(n->cmd[i]));
			if (!is_in_env(n, n->cmd[i], 0))
				ft_lstadd_back_env(&sh->env_copy, ft_lstnew_env(n->cmd[i]));
		}
		else if (!is_in_env(n, n->cmd[i], 0))
			ft_lstadd_back_env(&sh->env_copy, ft_lstnew_env(n->cmd[i]));
		i++;
	}
	g_exit_status = 0;
	return (g_exit_status);
}
