/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:46:09 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/31 18:50:12 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <errno.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# define ERROR 1
# define SUCCESS 0

typedef enum e_token
{
	CMD = 0,
	ESPACE = 1,
	PIPE = 2,
	RED_IN = 3,
	RED_OUT = 4,
	QUOTE = 5,
	SINGEL_Q = 6,
	FILE_NAME = 7,
	AND = 8,
	DOLLAR = 9,
	EQUAL = 10,
	APPEND = 11,
	DELIMET = 12,
	HERDOC = 13
}	t_token;

extern int	g_exit_status;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redirect
{
	t_token				type;
	char				*file_name;
	char 				*herdoc_name;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_shell
{
	int				size;
	char				**cmd;
	char				*expander;
	int					pid;
	int					red_size;
	int					infile;
	int					outfile;
	char				**list_quotes;
	struct s_shell		*next;
	struct s_redirect	*redirection;
	struct s_env		*env;
	struct s_env		*env_copy;
}	t_shell;

/*------- parsing --------*/
t_shell		*parsing(char *inputs, t_env *env, t_env *envp);
int			parcing_pipe(t_token *token, char *mask);
void		parser_error(void);
int			len_token(char *m);
void		cmd_tokens(char mask, t_token *t, int i);
t_shell		*lexer(char *inputs, t_env *env, t_env *envp);
void		masking(char *str, int i, char c);
char		*cmd_mask(char *str);
void		remove_quotes(t_shell *shell);
char		*new_cmd(char *str, t_shell *shell);
t_token		*tokenize(char *m);
void		only_cmd(t_shell *shell);
char		*add_space_for_redirect(char *str);
void		spacing_between_redirects(char *out, char *s, int *len, int *i);
void		skip_quotes(char *out, int *len, char *str, int *i);
/*------------------------*/

/*-----expander-----------*/
t_shell		*expander(t_shell *shell);
int			still_expandable(t_shell *sh);
int			len_env(char *s, t_shell *sh);
char		*ft_envirement(char *s, t_shell *sh);
char		*get_env_var(char *s, int *i, t_shell *sh);
int			fetch_len_env(char *s, int *i, t_shell *sh);
int			len_new_cmd(char *str, t_shell *sh);
void		copy_to_buffer(char *src, char *dst, int *i);
void		calculate_len_single_quotes(int *i, char *str, int *len);
void		calculate_double(int *i, char *str, t_shell *sh, int *len);
int			ft_strncmp_env(char *s1, char *s2);
void		copy_g_exit_status(char *str, int *j);
void		locate_env(t_shell *sh, int	*len, int *j, char *cmd);
void		*copy_from_env(char *sh, char *str, int *j, int *len);
/*------------------------*/

/*--------signals---------*/
void		signal01();
void		signals();
void		cntl_d(t_shell *sh, t_env *env, t_env *envp);
void		ctrl_c(int signal);
/*------------------------*/

/*----------herdoc--------*/
int 	handle_herdoc(t_shell *cmds);
void    unlick_files(t_shell *shell_tmp, t_redirect *red_tmp, char *hername);

/*------------------------*/

/*--------excution--------*/
int			execute(t_shell *node);
int			open_pipes(t_shell *node, int pipe_fd[2]);
void		ft_dup2(t_shell *node);
char		*get_cmd(char *cmd, t_env *envp);
int			handel_redirection(t_shell *node);
int			execution(t_shell *cmds);
int			child_pross(t_shell *cmds, char **envp, char *new_cmd);
int			history(char *str);
int			reading_promp(char **env);
char		**lst_arr(t_shell *shell);
void		close_fd(int in_fd, int out_fd);
/*------------------------*/

/*---------init-----------*/
void		init_env_lst(t_shell *sh, t_env *env, t_env *envp);
t_env		*create_lst_env(char **env);
/*------------------------*/

/*---------herdoc---------*/
void		redirections_lst(t_shell *shell);
t_redirect	*create_redirect_lst(char **cmd, int *i);
// int			handle_heredoc(t_shell *cmds);
/*........................*/

/*--------built-in--------*/
int			ft_echo(t_shell *sh);
int			if_built_in_run(t_shell *tmp);
int			is_built_in(t_shell *tmp);
int			ft_pwd(t_shell *shell);
int			ft_cd(t_shell *shell);
int			ft_exit(t_shell *shell);
int			ft_env(t_env *shell);
int			ft_export(t_shell *shell);
int			ft_unset(t_shell *sh);
/*------------------------*/

/*-----built-in_utils-----*/
int			run_option(t_shell *sh);
int			check_option(char *str);
void		get_old_dir(t_shell *sh, char *oldpwd);
void		set_current_dir(t_shell *sh);
int			export_to_env(t_shell *sh);
int			is_in_env(t_shell *sh, char *var_env, int flag);
int			export_to_env(t_shell *sh);
void		remove_from_export(t_shell *sh, char *target);
void		remove_from_env(t_shell *sh, char *target);
/*------------------------*/

/*--------clean-up--------*/
void		clean_up(t_shell *shell, int flag);
void		clean_lst(t_env *shell);
int			free_array(char **v);
void		clean_redirect(t_shell *shell);
/*------------------------*/

/*--------help_fct--------*/
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *str);
char		**ft_split(char *s, char *c);
t_shell		*ft_lstnew(char *str);
t_env		*ft_lstnew_env(char *str);
t_shell		*create_list(char *input);
void		ft_lstadd_back(t_shell **lst, t_shell *new);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
int			lstsize(t_env *cmd);
int			cmds_size(t_shell *cmd);
int			ft_strncmp(char *s1, char *s2);
int			ft_strnncmp(char *s1, char *s2, size_t len);
char		*ft_strtrim(char *s1, char *set);
char		*ft_strchr(char *s, int c);
int			ft_strcount(char *s, char chr);
char		*ft_strjoin2(int size, char **strs, char *sep);
t_redirect	*ft_lstnew_redirect(char *str, char *file);
void		ft_lstadd_back_redirect(t_redirect **lst, t_redirect *new);
char		*ft_strjoin_no_free(char *s1, char *s2);
int			lst_size(char **lst);
int			len_cmd(t_shell *shell);
int			red_size(t_redirect *cmd);
void		split_cmd(t_shell *shell);
void		ft_malloc(char *str, char **arr, int *len);
int			new_lenght(char *str);
void		copy_char(char *out, char *str, int *len, int *i);
void		change_value_inside_quotes(char *str);
void		number_special_char(char **cmd);
int			cmds_size(t_shell *cmd);
void		change_value_inside_quotes(char *str);
void		*ft_calloc(size_t count, size_t size);
void		delete_node_env(t_env *envp);
int			is_in_env(t_shell *sh, char *var_env, int flag);
char		*ft_itoa(int n);
int			ft_atoi(const char *s);
int			find_next_command(t_token *token, int index);
char		*ft_strjoin_no_free(char *s1, char *s2);
char		*checking(char const *s1, char const *s2);
/*------------------------*/

#endif
