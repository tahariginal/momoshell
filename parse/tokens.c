/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:22:24 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/21 09:36:50 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	masking(char *str, int i, char c)
{
	if (c == '>')
		str[i] = '4';
	else if (c == '<')
		str[i] = '3';
	else if (c == ' ')
		str[i] = '1';
	else if (c == '=')
		str[i] = '=';
	else if (c == '$')
		str[i] = '9';
	else
		str[i] = '0';
}

char	*cmd_mask(char *str)
{
	char	*mask;
	int		i;

	i = 0;
	mask = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!mask)
		return (NULL);
	while (str && str[i])
	{
		if (str[i] == '\'')
			mask[i] = '6';
		else if (str[i] == '"')
			mask[i] = '5';
		else if (str[i] == '|')
			mask[i] = '2';
		else if (str[i] == '&')
			mask[i] = '8';
		else
			masking(mask, i, str[i]);
		i++;
	}
	mask[i] = 0;
	return (mask);
}

int	len_token(char *m)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (m[i])
	{
		if ((m[i] == '0' || m[i] == '1') && m[i] != m[i + 1])
			len++;
		if ((m[i] != '0' && m[i] != '1'))
			len++;
		i++;
	}
	return (len);
}

void	cmd_tokens(char mask, t_token *t, int i)
{
	if (mask == '2')
		t[i] = PIPE;
	else if (mask == '3')
		t[i] = RED_IN;
	else if (mask == '4')
		t[i] = RED_OUT;
	else if (mask == '5')
		t[i] = QUOTE;
	else if (mask == '6')
		t[i] = SINGEL_Q;
	else if (mask == '8')
		t[i] = AND;
	else if (mask == '1')
		t[i] = ESPACE;
	else if (mask == '9')
		t[i] = DOLLAR;
	else if (mask == '=')
		t[i] = EQUAL;
	else
		t[i] = CMD;
}
