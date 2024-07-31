/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:14:54 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/28 19:07:17 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*p;
	unsigned char	*memory;
	size_t			len;

	if (count && size && (size > SIZE_MAX / count))
		return (NULL);
	len = (size * count);
	p = malloc(len);
	if (!p)
		return (NULL);
	len = 0;
	memory = (unsigned char *)p;
	while (len < size)
		memory[len++] = 0;
	return (p);
}
