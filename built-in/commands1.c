/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:37:57 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/27 22:49:57 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(t_shell *sh)
{
	int	i;

	i = 1;
	if (!ft_strlen(sh->cmd[1]))
		printf("\n");
	if (run_option(sh))
		return (1);
	else
	{
		while (sh->cmd[i])
		{
			printf("%s ", sh->cmd[i]);
			i++;
		}
		printf("\n");
	}
	return (0);
}

int	ft_pwd(t_shell *shell)
{
	char	*dir;

	(void)shell;
	dir = getcwd((void *)0, 0);
	if (dir)
		printf("%s\n", dir);
	else
	{
		g_exit_status = 30;
		return (perror("pwd"), free(dir), g_exit_status);
	}
	free(dir);
	g_exit_status = 0;
	return (g_exit_status);
}

int	ft_cd(t_shell *shell)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (lst_size(shell->cmd) > 2)
	{
		g_exit_status = 1;
		free(old_pwd);
		return (printf("cd cannot take multiple arguments!\n"), g_exit_status);
	}
	if (!shell->cmd[1])
	{
		if (chdir(getenv("HOME")))
			return (perror("cd"), free(old_pwd), g_exit_status = 1, 1);
		get_old_dir(shell, old_pwd);
		set_current_dir(shell);
	}
	else
	{
		if (chdir(shell->cmd[1]))
			return (perror("cd"), free(old_pwd), g_exit_status = 1, 1);
		get_old_dir(shell, old_pwd);
		set_current_dir(shell);
	}
	free(old_pwd);
	return (0);
}

int	ft_export(t_shell *shell)
{
	t_env	*tmp;
	t_env	*envp;

	tmp = shell->env;
	envp = shell->env_copy;
	if (lst_size(shell->cmd) == 1)
	{
		while (envp)
		{
			printf("declare -x %s=%s\n", envp->key, envp->value);
			envp = envp->next;
		}
	}
	else
		export_to_env(shell);
	g_exit_status = 0;
	return (g_exit_status);
}

int	ft_env(t_env *shell)
{
	t_env	*tmp;

	tmp = shell;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
