/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 19:00:15 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/26 10:20:56 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_env_list
{
	void				*variable;
	void				*value;
	t_bool				exported;
	struct s_env_list	*next;
}					t_env_list;

t_env_list		*ft_lstlast1(t_env_list *lst);
void			ft_lstadd_back1(t_env_list **lst, t_env_list *new);
t_env_list		*ft_lstnew1(void **content, t_bool exported);
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

/*************************   redirection  ***************************/

int				set_redirection(t_list *cmd_lst);
void			duplicate_redir_fd(t_list *cmd);
void			set_redir_fd(int *fd, int io, int new_fd);
void			close_io_fd(t_list *cmd);

/*************************   pipe  ***************************/

int				(*init_pipe(t_list *cmd_lst))[2];
void			dup_pipe(int fd_in, int fd_out);


/*************************   builtins  ***************************/

int				ft_builtin(t_list	*tmp);
int				ft_check_builtin(t_list	*cmd_lst);
t_env_list		*ft_env(char **env);
void			ft_echo(char **cmd);
void			ft_cd(char *cmd, t_env_list *ms_list);
void			ft_pwd();
void			ft_unset(t_env_list **ms_list, char *cmd);
void			ft_print_expo(t_env_list *ms_export, char *cmd);
void			ft_export(t_env_list **ms_export, char **cmd);
int				builtin_cmd_only(t_list *cmd);

/*************************   signals  ***************************/

void			ft_sig_handler(char location);
int				execute(t_list *cmd_lst);
int				p_open(char *file, int flags, int perm);
int				get_cmd_path(t_list *cmd_lst);
int				check_cmd(t_list *cmd);
int				(*init_pipe(t_list *cmd_lst))[2];
int				ft_builtin(t_list	*tmp);
int				fork_cmd(t_list *cmd, int fd_in, int (*pipe_fd)[2]);
char			**to_env(void);
void			child_exit_stat(char *cmd_name, int stat_loc);
t_bool			is_dir(char *name);
void			wait_child(int pid, t_list *cmd);

#endif