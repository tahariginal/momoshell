/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:34:57 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/27 22:49:57 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_value_others(char *str, int holder)
{
	(void)holder;
	if (*str == '>')
		*str = -3;
	else if (*str == '<')
		*str = -4;
	else if (*str == '\t')
		*str = -5;
}

void	change_value_inside_quotes(char *str)
{
	int	i;
	int	holder;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			holder = str[i];
			i++;
			while (str[i] && str[i] != holder)
			{
				if (str[i] == '|')
					str[i] = -1;
				else if (str[i] == ' ')
					str[i] = -2;
				else
					change_value_others(&str[i], holder);
				i++;
			}
		}
		if (!str[i])
			break ;
		i++;
	}
}

int	new_lenght(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if ((str[i] == '>' || str[i] == '<') && str[i] != str[i + 1])
			len += 2;
		i++;
	}
	return (len);
}

t_shell	*lexer(char *inputs, t_env *env, t_env *envp)
{
	t_shell	*shell;
	t_token	*t;
	char	*sp;
	char	*mask;

	mask = cmd_mask(inputs);
	if (!mask)
		return (NULL);
	t = tokenize(mask);
	if (!t)
		return (free(mask), NULL);
	if (parcing_pipe(t, mask))
		return (free(t), free(mask), NULL);
	sp = add_space_for_redirect(inputs);
	change_value_inside_quotes(sp);
	shell = create_list(sp);
	if (!shell)
		return (free(sp), free(t), free(mask), NULL);
	if (shell)
		init_env_lst(shell, env, envp);
	expander(shell);
	redirections_lst(shell);
	remove_quotes(shell);
	only_cmd(shell);
	return (free(sp), free(t), free(mask), g_exit_status = 0, shell);
}
