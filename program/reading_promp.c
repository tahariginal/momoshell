/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_promp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:27:52 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/31 18:48:38 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	history(char *str)
{
	if (!str)
		return (1);
	if (ft_strlen(str))
		add_history(str);
	return (0);

}

void	set_hold(t_shell *node)
{
	node->infile = dup(0);
	node->outfile = dup(1);
}

void	signals()
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
void	signal01()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
	

int	reading_promp(char **env)
{
	t_shell	*shell;
	t_shell	*shell_tmp;
	t_env	*env_cp;
	t_env	*envp;
	char	*inputs;

	env_cp = create_lst_env(env);
	envp = create_lst_env(env);
	while (1337)
	{
		signals();
		inputs = readline("minishell~> ");
		if (!inputs)
			cntl_d(shell, envp, env_cp);
		shell = parsing(ft_strtrim(inputs, " \t"), env_cp, envp);
		if (history(inputs))
			return (free(inputs), 3);
		free(inputs);
		if (shell)
		{
			shell_tmp = shell;
			signals();
			set_hold(shell);
			if (execution(shell))
				return (g_exit_status);
		}
		clean_up(shell, 0);
	}
	
	return (0);
}
