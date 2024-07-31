/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:26:04 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/27 22:40:13 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_next_command(t_token *token, int index)
{
	while (token[index] != 20)
	{
		index++;
		if (token[index] != ESPACE)
			break ;
	}
	if (token[index] == PIPE)
		return (1);
	return (0);
}
