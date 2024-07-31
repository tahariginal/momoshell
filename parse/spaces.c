/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:37:39 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/27 22:38:09 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_quotes(char *out, int *len, char *str, int *i)
{
	char	quote;

	if (str[*i] == '"' || str[*i] == '\'')
	{
		if (*i && (str[*i - 1] == '>' || str[*i - 1] == '<'))
		{
			out[*len] = ' ';
			*len += 1;
		}
		quote = str[*i];
		out[*len] = str[*i];
		*len += 1;
		*i += 1;
		while (str[*i] && str[*i] != quote)
			copy_char(out, str, len, i);
		if (str[*i] == '"' || str[*i] == '\'')
			copy_char(out, str, len, i);
	}
}

void	spacing_between_redirects(char *out, char *s, int *len, int *i)
{
	if (*i && (s[*i] == '>' || s[*i] == '<') && s[*i] != s[*i - 1])
	{
		out[*len] = ' ';
		*len += 1;
	}
	if (*i && (s[*i - 1] == '>' || s[*i - 1] == '<') && s[*i] != s[*i - 1])
	{
		out[*len] = ' ';
		*len += 1;
	}
}

char	*add_space_for_redirect(char *str)
{
	char	*out;
	int		i;
	int		len;

	len = new_lenght(str);
	out = malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	i = 0;
	len = 0;
	while (str[i])
	{
		skip_quotes(out, &len, str, &i);
		spacing_between_redirects(out, str, &len, &i);
		out[len] = str[i];
		if (!str[i])
			break ;
		len++;
		i++;
	}
	out[len] = 0;
	return (out);
}

void	only_cmd(t_shell *shell)
{
	t_shell	*tmp;

	tmp = shell;
	while (tmp)
	{
		split_cmd(tmp);
		number_special_char(tmp->cmd);
		tmp = tmp->next;
	}
}
