/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:43:01 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/27 22:49:57 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_redirection_space(t_token *t)
{
	int	i;

	i = 0;
	while (t[i] != 20)
	{
		if (t[i] == RED_IN || t[i] == RED_OUT)
		{
			i++;
			if (t[i] == ESPACE)
			{
				i++;
				if (t[i] == RED_IN || t[i] == RED_OUT)
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int	parsing_redirect(t_token *token, int index)
{
	int		c;
	t_token	t;
	t_token	opposite;

	c = 0;
	t = token[index];
	if (t == 4)
		opposite = 3;
	else
		opposite = 4;
	while (token[index] != 20)
	{
		index++;
		if (token[index] == t)
			c++;
		if (token[index] != ESPACE && token[index] != t)
			break ;
	}
	if (token[index] == PIPE || token[index] == 20 || c > 1 || \
		token[index] == opposite)
		return (1);
	if (c == 1 && parse_redirection_space(token))
		return (1);
	return (0);
}

int	parse_quote(t_token *token, int *i)
{
	t_token	t;

	t = token[*i];
	*i += 1;
	while (token[*i] != 20 && token[*i] != t)
		*i += 1;
	if (token[*i] == t)
		return (0);
	return (1);
}

int	parcing_pipe(t_token *token, char *mask)
{
	int		i;

	i = 0;
	(void)mask;
	if (token && token[i] == PIPE)
		return (parser_error(), g_exit_status);
	while (token[i] != 20)
	{
		if ((token[i] == QUOTE || token[i] == SINGEL_Q) && \
			parse_quote(token, &i))
			return (parser_error(), g_exit_status);
		if (token[i] == PIPE && find_next_command(token, i))
			return (parser_error(), g_exit_status);
		if ((token[i] == RED_IN || token[i] == RED_OUT) && \
			parsing_redirect(token, i))
			return (parser_error(), g_exit_status);
		i++;
	}
	if (token[--i] == PIPE)
		return (parser_error(), g_exit_status);
	return (0);
}

t_shell	*parsing(char *inputs, t_env *env, t_env *envp)
{
	t_shell	*shell;

	shell = NULL;
	if (inputs)
	{
		shell = lexer(inputs, env, envp);
		free(inputs);
		if (!shell)
			return (NULL);
	}
	else
		free(inputs);
	return (shell);
}
