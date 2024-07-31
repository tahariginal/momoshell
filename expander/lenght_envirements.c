/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenght_envirements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:30:50 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/28 19:04:22 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_new_cmd(char *str, t_shell *sh)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			calculate_len_single_quotes(&i, str, &len);
		if (str[i] == '"')
			calculate_double(&i, str, sh, &len);
		if (str[i] == '$')
		{
			i++;
			len += fetch_len_env(str, &i, sh);
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

void	copy_to_buffer(char *src, char *dst, int *i)
{
	int	j;

	j = 0;
	while (src[*i] && src[*i] != '\'' && src[*i] != -2 && src[*i] != '$' \
		&& src[*i] != -5 && src[*i] != '"' && src[*i] != '?')
	{
		dst[j] = src[*i];
		j++;
		*i += 1;
	}
}

void	calculate_len_single_quotes(int *i, char *str, int *len)
{
	*i += 1;
	*len += 1;
	while (str[*i] && str[*i] != '\'')
	{
		*len += 1;
		*i += 1;
	}
}

void	calculate_double(int *i, char *str, t_shell *sh, int *len)
{
	*i += 1;
	*len += 1;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			*i += 1;
			*len += fetch_len_env(str, i, sh);
		}
		else
		{
			*i += 1;
			*len += 1;
		}
	}
}
