/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:21:11 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/27 22:45:44 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_cmd(t_shell *shell)
{
	t_shell	*t;
	int		len;
	int		i;

	len = 0;
	i = 0;
	t = shell;
	while (t->cmd[i])
	{
		if (!ft_strncmp(t->cmd[i], ">") || !ft_strncmp(t->cmd[i], ">>"))
			i++;
		else if (!ft_strncmp(t->cmd[i], "<") || !ft_strncmp(t->cmd[i], "<<"))
			i++;
		else
			len++;
		i++;
	}
	return (len);
}

void	split_cmd(t_shell *sh)
{
	char	**arr;
	int		i;
	int		len;

	i = 0;
	len = len_cmd(sh);
	arr = malloc(sizeof(char *) * (len + 1));
	arr[len] = 0;
	len = 0;
	if (!arr)
		return ;
	while (sh->cmd[i])
	{
		if (!ft_strncmp(sh->cmd[i], ">") || !ft_strncmp(sh->cmd[i], ">>"))
			i++;
		else if (!ft_strncmp(sh->cmd[i], "<") || !ft_strncmp(sh->cmd[i], "<<"))
			i++;
		else
			ft_malloc(sh->cmd[i], arr, &len);
		i++;
	}
	free_array(sh->cmd);
	sh->cmd = arr;
}

char	*new_cmd(char *str, t_shell *shell)
{
	char	*output;
	char	**lst;
	int		i;

	(void)shell;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			lst = ft_split(str, "\'");
			output = ft_strjoin2(lst_size(lst), lst, "");
			return (free(str), free_array(lst), output);
		}
		else if (str[i] == '"')
		{
			lst = ft_split(str, "\"");
			output = ft_strjoin2(lst_size(lst), lst, "");
			return (free(str), free_array(lst), output);
		}
		i++;
	}
	return (str);
}

void	remove_quotes(t_shell *shell)
{
	t_shell	*tmp;
	int		i;

	tmp = shell;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			tmp->cmd[i] = new_cmd(tmp->cmd[i], tmp);
			i++;
		}
		tmp = tmp->next;
	}
}
