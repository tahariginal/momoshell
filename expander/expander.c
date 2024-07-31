/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:15:04 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/29 22:25:18 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*copy_from_env(char *sh, char *str, int *len, int *j)
{
	*j += 1;
	if (sh[*j] == '?')
		copy_g_exit_status(str, len);
	if (!sh[*j])
	{
		str[*len] = '$';
		*len += 1;
	}
	return (NULL);
}

void	copy_in_single_quotes(char *s, int *j, char *sh, int *len)
{
	s[*len] = sh[*j];
	*len += 1;
	*j += 1;
	while (sh[*j] && sh[*j] != '\'')
	{
		s[*len] = sh[*j];
		*len += 1;
		*j += 1;
	}
	if (sh[*j] == '\'')
	{
		s[*len] = sh[*j];
		*len += 1;
		*j += 1;
	}
}

void	expand_and_copy(t_shell *s, int i, char *str)
{
	int		j;
	int		len;

	j = 0;
	len = 0;
	while (s->cmd[i][j])
	{
		if (s->cmd[i][j] == '\'')
			copy_in_single_quotes(str, &j, s->cmd[i], &len);
		if (s->cmd[i][j] == '"')
		{
			str[len++] = s->cmd[i][j++];
			while (s->cmd[i][j] && s->cmd[i][j] != '"' && s->cmd[i][j] != '$')
				str[len++] = s->cmd[i][j++];
			if (s->cmd[i][j] == '$')
				locate_env(s, &len, &j, s->cmd[i]);
		}
		if (s->cmd[i][j] == '$')
			locate_env(s, &len, &j, s->cmd[i]);
		else if (s->cmd[i][j])
		{
			str[len++] = s->cmd[i][j++];
		}
	}
}

char	*new_cmd_expanded(t_shell *sh, int i)
{
	int		len;

	len = len_new_cmd(sh->cmd[i], sh);
	sh->expander = ft_calloc(sizeof(char), (len + 1));
	sh->expander[len] = 0;
	expand_and_copy(sh, i, sh->expander);
	free(sh->cmd[i]);
	return (sh->expander);
}

t_shell	*expander(t_shell *shell)
{
	t_shell	*tmp;
	int		i;

	if (!still_expandable(shell))
		return (NULL);
	tmp = shell;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			if (ft_strchr(tmp->cmd[i], '$'))
				tmp->cmd[i] = new_cmd_expanded(tmp, i);
			i++;
		}
		tmp = tmp->next;
	}
	return (expander(shell));
}
