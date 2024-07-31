/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:35:37 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/25 19:04:30 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*create_list(char *input)
{
	t_shell	*node;
	t_shell	*shell;
	char	**cmds;
	int		i;

	i = 0;
	cmds = ft_split(input, "|");
	shell = NULL;
	while (cmds[i])
	{
		node = ft_lstnew(cmds[i]);
		if (!node)
			return (NULL);
		ft_lstadd_back(&shell, node);
		i++;
	}
	free_array(cmds);
	return (shell);
}

t_env	*create_lst_env(char **env)
{
	t_env	*head;
	t_env	*node;
	int		i;

	i = 0;
	head = NULL;
	while (env[i])
	{
		node = ft_lstnew_env(env[i]);
		ft_lstadd_back_env(&head, node);
		i++;
		node = node->next;
	}
	return (head);
}

void	init_env_lst(t_shell *sh, t_env *env, t_env *envp)
{
	t_shell	*tmp;

	tmp = sh;
	while (tmp)
	{
		tmp->env = env;
		tmp->env_copy = envp;
		tmp = tmp->next;
	}
}
