/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:19:24 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/27 22:42:47 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redirect	*create_redirect_lst(char **cmd, int *i)
{
	t_redirect	*head;
	t_redirect	*node;

	head = NULL;
	while (cmd[*i])
	{
		if (!ft_strncmp(cmd[*i], ">") || !ft_strncmp(cmd[*i], "<"))
		{
			node = ft_lstnew_redirect(cmd[*i], cmd[*i + 1]);
			ft_lstadd_back_redirect(&head, node);
		}
		if (!ft_strncmp(cmd[*i], "<<") || !ft_strncmp(cmd[*i], ">>"))
		{
			node = ft_lstnew_redirect(cmd[*i], cmd[*i + 1]);
			ft_lstadd_back_redirect(&head, node);
		}
		*i += 1;
	}
	return (head);
}

void	redirections_lst(t_shell *shell)
{
	t_shell	*n;
	int		i;

	n = shell;
	while (n)
	{
		i = 0;
		while (n->cmd[i])
		{
			if (!ft_strncmp(n->cmd[i], ">") || !ft_strncmp(n->cmd[i], "<"))
				n->redirection = create_redirect_lst(n->cmd, &i);
			if (!ft_strncmp(n->cmd[i], "<<") || !ft_strncmp(n->cmd[i], ">>"))
				n->redirection = create_redirect_lst(n->cmd, &i);
			if (!n->cmd[i])
				break ;
			i++;
		}
		n = n->next;
	}
}
