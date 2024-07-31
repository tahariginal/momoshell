/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:40:27 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/28 19:05:19 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		i;

	i = 0;
	if (!s || start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) < len)
		len = ft_strlen(s) - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!(str))
		return (NULL);
	while (len > i && s[start + i])
	{
		str[i] = (char)s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin_no_free(char *s1, char *s2)
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
