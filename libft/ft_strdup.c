/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:55:17 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/27 18:07:29 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*p;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (s1 && s1[i])
	{
		p[i] = ((char *)s1)[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
