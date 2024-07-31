/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:20:13 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/30 20:29:08 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstadd_back(t_shell **lst, t_shell *new)
{
	t_shell	*traverse;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	traverse = *lst;
	while (traverse->next)
	{
		traverse = traverse->next;
	}
	traverse->next = new;
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*traverse;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	traverse = *lst;
	while (traverse->next)
	{
		traverse = traverse->next;
	}
	traverse->next = new;
}

void	ft_lstadd_back_redirect(t_redirect **lst, t_redirect *new)
{
	t_redirect	*traverse;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	traverse = *lst;
	while (traverse && traverse->next)
	{
		traverse = traverse->next;
	}
	traverse->next = new;
}
