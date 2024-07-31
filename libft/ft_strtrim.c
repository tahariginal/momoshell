/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:42:22 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/13 16:58:52 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strtrim(char *s1, char *set)
{
	size_t	start;
	size_t	end;
	char	*haircut;
	size_t	i;

	start = 0;
	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	if (*s1 == '\0' || *set == '\0')
		return (ft_strdup(s1));
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[start]) && s1[start])
		start++;
	while (start < end && ft_strchr(set, s1[end - 1]))
		end--;
	haircut = (char *)malloc(sizeof(char) * (end - start + 1));
	if (haircut == NULL)
		return (NULL);
	while (end > start)
		haircut[i++] = s1[start++];
	haircut[i] = '\0';
	return (haircut);
}
