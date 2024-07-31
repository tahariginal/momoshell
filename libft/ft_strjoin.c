/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:29:57 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/28 21:24:58 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*checking(char const *s1, char const *s2)
{
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	return (NULL);
}

char	*ft_strcat(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(s1);
	while (s2[i])
	{
		s1[j] = s2[i];
		i++;
		j++;
	}
	s1[j] = '\0';
	return (s1);
}

char	*new_str(char *seperator, int size, int t, char **strs)
{
	int		i;
	char	*str;

	i = 0;
	if (size == 0)
		t = 1;
	str = (char *)malloc(t);
	if (str == NULL)
		return (0);
	str[0] = '\0';
	i = 0;
	while (i < size)
	{
		str = ft_strcat(str, strs[i]);
		if (i < size - 1)
			str = ft_strcat(str, seperator);
		i++;
	}
	return (str);
}

char	*ft_strjoin2(int size, char **strs, char *sep)
{
	int		i;
	int		total;
	char	*sentence;

	total = 0;
	i = 0;
	while (i < size)
	{
		total = total + ft_strlen(strs[i]);
		i++;
	}
	i = 0;
	total = total + (size - 1) * ft_strlen(sep) + 1;
	sentence = new_str(sep, size, total, strs);
	return (sentence);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	size_t	len;
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (checking(s1, s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (*s1)
	{
		p[i] = *(char *)s1++;
		i++;
	}
	while (*s2)
	{
		p[i] = *(char *)s2++;
		i++;
	}
	p[i] = '\0';
	return (p);
}
