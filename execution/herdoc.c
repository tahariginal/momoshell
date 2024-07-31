/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:36:45 by tkoulal           #+#    #+#             */
/*   Updated: 2024/07/31 18:52:06 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_env_to_line(char *new, char *line)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while (line[i] && line[i] != '$')
        i++;
    if (line[i] == '$')
        i++;
    while (line[i] && line[i] != '\'' && line[i] != ' ' && line[i] != '"' && line[i] != '\t' && line[i] != '$')
    {
        new[len] = line[i];
        i++;
        len++;
    }
    return(getenv(new));
}

int len_of_env(char *line)
{
    int len = 0;
    int i = 0;

    while (line[i] && line[i] != '$')
        i++;
    if (line[i] == '$')
        i++;
    while (line[i] && line[i] != '\'' && line[i] != ' ' && line[i] != '"' && line[i] != '\t' && line[i] != '$')
    {
        i++;
        len++;
    }
    return (len);
}
char *expand_heredoc(char *line)
{
    int i;
    int len;
    char *new_line;
    char *temp;
    
    i = 0;
    len = len_of_env(line);
    new_line = malloc(len + 1);
    new_line[len] = 0;
    temp = new_line;
    new_line = get_env_to_line(new_line, line);
    free(temp);
    free(line);
    return (new_line);
}

int    break_if_there_is_a_del(int *flag, char *line, t_redirect *red_tmp)
{
    if (!ft_strncmp(line, red_tmp->file_name))
    {
        if (*flag == 0)
            free(line);
        return (0);
    }
    return (1);
}

void    reading_promp_her(int *fd, t_redirect *red_tmp)
{
    char *line;
    int flag;
    

    flag = 0;
    *fd = open(red_tmp->herdoc_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
    while (42)
    {
        line = readline(">");
        if (!line)
            return;
        if (ft_strchr(line, '$'))
        {
            line = expand_heredoc(line);
            flag = 1;
        }
        if (break_if_there_is_a_del(&flag, line, red_tmp) == 0)
            break;
        write(*fd, line, ft_strlen(line));
        write(*fd, "\n", 1);
        if (flag == 0)
            free(line);
        flag = 1;
    }
}
void    open_herdoc(t_shell *cmds)
{
    int pid;
    t_shell *node;
    t_redirect *red_tmp;
    int fd;

    pid = fork();
    if (!pid)
    {
        node = cmds;
        red_tmp = cmds->redirection;
        while (node)
        {
            red_tmp = node->redirection;
            while (red_tmp)
            {
                if (red_tmp->type == HERDOC)
                    reading_promp_her(&fd, red_tmp);
                red_tmp = red_tmp->next;
                close(fd);
            }
            node = node->next;
        }
        exit(0);
    }
    waitpid(pid, NULL, 0);
}
void    unlick_files(t_shell *shell_tmp, t_redirect *red_tmp, char *hername)
{
    while (shell_tmp && red_tmp && hername)
    {
        unlink(shell_tmp->redirection->herdoc_name);
        shell_tmp = shell_tmp->next;
    }
}
char*	generate_name(int i)
{
	char *path;
    int j = 0;

	path = ttyname(0);
	while (path[j])
    {
		path[j] += i + 1;
        j++;
    }
    return(ft_strdup(path));
}

int handle_herdoc(t_shell *cmds)
{
    t_shell *node;
    t_redirect *red_tmp;

    int i = 0;
    node = cmds;
    red_tmp = cmds->redirection;
    while (node)
    {
        red_tmp = node->redirection;
        while (red_tmp)
        {
            if (red_tmp->type == HERDOC)
                red_tmp->herdoc_name = generate_name(i);
            red_tmp = red_tmp->next;
        }
        i++;
        node = node->next;
    }
    open_herdoc(cmds);
    return (0);
}
