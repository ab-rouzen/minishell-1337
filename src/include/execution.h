/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 19:00:15 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/28 22:27:48 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "./minishell.h"
# define EXIT_NF 127
# define EXIT_PERM 126

t_env_list		*ft_lstlast1(t_env_list *lst);
void			ft_lstadd_back1(t_env_list **lst, t_env_list *new);
t_env_list		*ft_lstnew1(char **content, t_bool exported);
char			**ft_split_export(char *str);

/*************************   heredoc  ***************************/

int				**here_doc(t_list *cmd_lst);
int				get_heredoc_cmd_num(t_list *cmd_lst);
char			***get_heredoc_delim(t_list *cmd_lst);
int				get_redir_lst_heredoc_num(t_list *redir_lst);
int				**allocate_hdoc_fd(t_list *cmd_lst);
int				*create_cmd_heredoc(int size, char **delim, int hdoc_id);
void			insert_cmd_delim(t_list *redir_lst, char **cmd_delim);
void			close_hdoc_fd(t_list *cmd);
char			*hdoc_var_expand(char *line);
int				set_var_to_word(t_list *lst);
t_list			*skip_token(t_list *lst, enum e_token tok);
t_list			*get_next_same_token(t_list *lst, enum e_token tok);
t_list			*skip_token_group(t_list *lst, enum e_token tok);
t_list			*skip_group_combo(t_list *lst);

/*************************   redirection  ***************************/

int				set_redirection(t_cmd_lst *cmd);
void			duplicate_redir_fd(t_cmd_lst *cmd);
void			set_redir_fd(t_cmd_lst *cmd, enum e_token tok, char *file);
void			close_io_fd(t_cmd_lst *cmd);
int				open_file(char *file, int oflag, int perm);

/*************************   pipe  ***************************/

void			init_pipe(t_list *cmd_lst, int (**piper)[2]);
void			dup_pipe(int fd_in, int fd_out);

/*************************   builtins  ***************************/

int				ft_builtin(t_list	*tmp);
int				ft_check_builtin(t_list	*cmd_lst);
t_env_list		*ft_env(char **env);
int				builtin_cmd_only(t_list *cmd);
/*************************   signals  ***************************/

void			ft_sig_handler(char location);
void			reset_signals();
int				execute(t_list *cmd_lst);
int				p_open(char *file, int flags, int perm);
int				get_cmd_path(t_cmd_lst *cmd);
int				check_cmd(t_cmd_lst *cmd);
int				ft_builtin(t_list	*tmp);
int				fork_cmd(t_list *cmd, int fd_in, int (*pipe_fd)[2]);
char			**to_env(void);
void			child_exit_stat(char *cmd_name, int stat_loc);
t_bool			is_dir(char *name);
void			wait_child(int pid, t_list *cmd);
char			**free_word(char **s);

/*####################      1_builtin_utils.c      ####################*/

int				ft_print_echo(char **cmd, int i, int check, t_list *cmd_list);
int				ft_echo(char **cmd, t_list *cmd_list);
int				ft_pwd(t_list *cmd_list, t_env_list *ms_list);
void			ft_print_expo_norm(\
				t_env_list *tmp, char *cmd, t_list *cmd_list);
int				ft_print_expo(t_env_list *tmp, char *cmd, t_list *cmd_list);
/*####################      1_builtin_utils.c      ####################*/

/*####################      2_builtin_utils.c      ####################*/
void			ft_update_export(t_env_list *ms_list, char *oldpwd);
int				ft_cd_norm_1(char *cmd, t_env_list *ms_list, char cwd[255]);
int				ft_find_oldpwd(\
				char cwd[255], t_env_list *tmp, t_list *cmd_list);
int				ft_cd(char *cmd, t_env_list *ms_list, t_list *cmd_list);
int				ft_unset(t_env_list **ms_list, char **cmd, int i);
/*####################      2_builtin_utils.c      ####################*/

/*####################      3_builtin_utils.c      ####################*/
int				ft_isalnum_minishell(int c);
char			**ft_split_export(char *str);
char			**free_word(char **s);
int				ft_check_variable(char **str, char *cmd);
int				ft_export(t_env_list **ms_export, char **cmd);
/*####################      3_builtin_utils.c      ####################*/

/*####################      4_builtin_utils.c      ####################*/
int				ft_find_variable_norm(\
				t_env_list *ms_list, char **str, char *cmd);
int				ft_find_variable(\
				t_env_list *ms_list, char **str, char *cmd, int i);
int				ft_unset(t_env_list **ms_list, char **cmd, int i);
int				ft_exit(char **cmd, t_list *cmd_list);
void			free_env_node(t_env_list *node);

/*####################      4_builtin_utils.c      ####################*/

#endif