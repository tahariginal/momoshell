/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirements.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:26:37 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/29 22:10:16 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_env(char *s, t_shell *sh)
{
	t_env	*env;

	if (!ft_strlen(s))
		return (free(s), 0);
	env = sh->env;
	while (env)
	{
		if (!ft_strncmp(env->key, s))
			return (free(s), ft_strlen(env->value));
		env = env->next;
	}
	return (free(s), 0);
}

char	*ft_envirement(char *s, t_shell *sh)
{
	t_env	*env;

	env = sh->env;
	while (env)
	{
		if (!ft_strncmp(env->key, s))
			return (free(s), ft_strdup(env->value));
		env = env->next;
	}
	return (free(s), NULL);
}

char	*get_env_var(char *s, int *i, t_shell *sh)
{
	char	*env;
	int		len;
	int		save;

	len = 0;
	save = *i;
	if (s[save] == '$')
		return (*i += 1, ft_envirement(ft_strdup("$"), sh));
	while (s[save] && s[save] != '\'' && s[save] != -2 && s[save] != '$' \
			&& s[save] != -5 && s[save] != '"' && s[save++] != '?')
		len++;
	env = malloc(sizeof(char) * (len + 1));
	env[len] = 0;
	if (!env)
		return (NULL);
	len = 0;
	while (s[*i] && s[*i] != '\'' && s[*i] != -2 && s[*i] != '$' \
		&& s[*i] != -5 && s[*i] != '"' && s[*i] != '?')
	{
		env[len++] = s[*i];
		*i += 1;
	}
	if (s[*i] == '?')
		*i += 1;
	return (ft_envirement(env, sh));
}

int	get_len_g_exit_status(void)
{
	char	*n;
	int		len;

	n = ft_itoa(g_exit_status);
	len = ft_strlen(n);
	free(n);
	return (len);
}

int	fetch_len_env(char *s, int *i, t_shell *sh)
{
	char	*env;
	int		len;
	int		save;

	len = 0;
	save = *i;
	if (s[*i] == '$')
		return (len_env(ft_strdup("$"), sh));
	else if (s[*i] == '?')
		return (get_len_g_exit_status());
	if (!s[*i])
		return (1);
	while (s[save] && s[save] != '\'' && s[save] != -2 && s[save] != '$' \
			&& s[save] != -5 && s[save] != '"' && \
			s[save] != '?')
	{
		save++;
		len++;
	}
	env = malloc(sizeof(char) * (len + 1));
	env[len] = 0;
	if (!env)
		return (0);
	copy_to_buffer(s, env, i);
	return (len_env(env, sh));
}
