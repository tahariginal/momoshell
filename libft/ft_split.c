/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:28:51 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/02 09:32:12 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	count(char const *str, char *ch)
{
	size_t	how_much;
	size_t	i;

	how_much = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_strchr(ch, str[i]))
			i++;
		if (str[i])
		{
			how_much++;
			while (str[i] && !ft_strchr(ch, str[i]))
				i++;
		}
	}
	return (how_much);
}

static size_t	lenght(char const *str, char *c)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	while (str[i] && ft_strchr(c, str[i]))
		i++;
	while (str[i] && !ft_strchr(c, str[i]))
	{
		len++;
		i++;
	}
	return (len);
}

static char	**splitor(char const *s, char *c, char **arr, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (len > i)
	{
		while (s[j] && ft_strchr(c, s[j]))
			j++;
		arr[i] = ft_substr(s, j, (lenght(s + j, c)));
		if (!arr[i])
		{
			while (i--)
				free(arr[i]);
			free(arr);
			return (NULL);
		}
		while (s[j] && !ft_strchr(c, s[j]))
			j++;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char *s, char *c)
{
	size_t	words;
	char	**list;

	if (!s)
		return (NULL);
	words = count(s, c);
	list = (char **)malloc(sizeof(char *) * (words + 1));
	if (!list)
		return (NULL);
	list = splitor(s, c, list, words);
	return (list);
}
