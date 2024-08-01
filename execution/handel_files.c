/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:55:13 by tkoulal           #+#    #+#             */
/*   Updated: 2024/08/01 12:13:35 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_infile_acces(char *file_name)
{
	int	status;

	status = access(file_name, F_OK);
	if (status == -1)
    {
        perror(file_name);
		return (-1);
    }
	else
	{
		status = open(file_name, O_RDONLY);
		if (status == -1)
        {
            perror(file_name);
			return (-1);
        }
		else
			return (status);
	}
	return (ERROR);
}

int	open_infiles(t_shell *node, t_redirect *file)
{
	int	status;

	if (file->type == HERDOC)
	{
		status = check_infile_acces(file->herdoc_name);
	}
	else
		status = check_infile_acces(file->file_name);
	if (status < 0)
		return (status);
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	node->infile = status;
	return (SUCCESS);
}
int	print_error(int error_id, char *file_name)
{
	if (error_id == 1)
	{
		printf("minishell: %s: No such file or directory\n", file_name);
		return (error_id);
	}
	if (error_id == 2)
	{
		g_exit_status = 1;
		printf("minishell: %s: Permission denied\n", file_name);
		return (error_id);
	}
	return (SUCCESS);
}

int open_outfiles(t_shell *node, t_redirect *tmp_red)
{
	int status;
	int	flag ;

	if (tmp_red->type == 4)
		flag = O_TRUNC;
	else if (tmp_red->type == 11)
		flag = O_APPEND;
	flag = O_WRONLY | O_CREAT;
	status = open(tmp_red->file_name, flag , 0644);
	if (status < 0)
	{
		status = access(tmp_red->file_name, F_OK);
		if (status == -1)
			return (print_error(1, tmp_red->file_name));
		else
			return (print_error(2, tmp_red->file_name));		
	}
	node->outfile = status;
	return (SUCCESS);
}

int	check_is_valid_redirection(t_redirect *tmp_red)
{
	if (!ft_strlen(tmp_red->file_name))
	{
		g_exit_status = 1;
		printf("minishell:%s ambiguous redirect \n",tmp_red->file_name);
		return (g_exit_status);
	}
	return (0);
}


int handel_redirection(t_shell *node)
{
    t_redirect *tmp_red;

    tmp_red = node->redirection;
	if (check_is_valid_redirection(tmp_red))
		return (g_exit_status);
    while (tmp_red)
    {
        if (tmp_red->type == RED_OUT || tmp_red->type == APPEND) // >
        {
            if (open_outfiles(node, tmp_red) < 0)
                return (ERROR);
        }
        else if (tmp_red->type == RED_IN ||  tmp_red->type == HERDOC)// <
        {
            if (open_infiles(node, tmp_red) < 0)
                return (ERROR);
        }
        tmp_red = tmp_red->next;
    }
    return (0);
}
