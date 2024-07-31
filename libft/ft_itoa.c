/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:51:02 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/21 14:35:25 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	intger_len(int o)
{
	size_t	len;
	long	no;

	len = 0;
	no = o;
	if (no == 0)
		return (1);
	if (no < 0)
	{
		len++;
		no = -(no);
	}
	while (no > 0)
	{
		no = (no / 10);
		len++;
	}
	return (len);
}

static char	*zero(void)
{
	char	*p;

	p = (char *)malloc(sizeof(char) * 2);
	if (!p)
		return (NULL);
	p[0] = '0';
	p[1] = '\0';
	return (p);
}

char	*ft_itoa(int n)
{
	size_t	l;
	char	*returned_number;
	long	num;

	num = n;
	if (num == 0)
		return (zero());
	l = intger_len(num);
	returned_number = (char *)malloc(sizeof(char) * (l + 1));
	if (!returned_number)
		return (NULL);
	returned_number[l] = '\0';
	l--;
	if (num < 0)
	{
		returned_number[0] = '-';
		num = -(num);
	}
	while (num > 0)
	{
		returned_number[l] = (num % 10) + 48;
		l--;
		num /= 10;
	}
	return (returned_number);
}
