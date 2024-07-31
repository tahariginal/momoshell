/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:17:13 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/31 13:36:01 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redirect	*ft_lstnew_redirect(char *str, char *file)
{
	t_redirect	*node;

	(void)str;
	node = malloc(sizeof(t_redirect));
	if (!node)
		return (NULL);
	if (!ft_strncmp(str, ">"))
		node->type = RED_OUT;
	else if (!ft_strncmp(str, "<"))
		node->type = RED_IN;
	else if (!ft_strncmp(str, ">>"))
		node->type = APPEND;
	else if (!ft_strncmp(str, "<<"))
		node->type = HERDOC;
	node->file_name = ft_strdup(file);
	if (!node->file_name)
	{
		free(node);
		return (NULL);
	}
	node->herdoc_name = NULL;
	node->next = NULL;
	return (node);
}

t_shell	*ft_lstnew(char *str)
{
	t_shell	*node;

	node = malloc(sizeof(t_shell));
	if (!node)
		return (NULL);
	node->cmd = NULL;
	if (str)
		node->cmd = ft_split(str, " \t");
	node->list_quotes = NULL;
	node->redirection = NULL;
	node->env = NULL;
	node->env_copy = NULL;
	node->expander = NULL;
	node->next = NULL;
	return (node);
}

char	*get_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	key[i] = 0;
	i = 0;
	while (str[i] && str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	return (key);
}

char	*get_value(char *str)
{
	char	*value;
	int		i;

	i = 0;
	while (*str && *str != '=')
		str ++;
	if (*str == '=')
		str++;
	while (str[i])
		i++;
	value = malloc((i + 1));
	if (!value)
		return (NULL);
	value[i] = 0;
	i = 0;
	while (*str)
	{
		value[i] = *(str++);
		i++;
	}
	return (value);
}

t_env	*ft_lstnew_env(char *str)
{
	t_env	*node;

	(void)str;
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = get_key(str);
	node->value = get_value(str);
	node->next = NULL;
	return (node);
}
