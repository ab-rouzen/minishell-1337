#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_env_list
{
	void				*variable;
	void				*value;
	t_bool				exported;
	struct s_env_list	*next;
}					t_env_list;

void			ft_echo(char **cmd);
void			ft_cd(char **cmd, t_env_list *ms_list);
void			ft_pwd();
t_env_list		*ft_lstlast1(t_env_list *lst);
void			ft_lstadd_back1(t_env_list **lst, t_env_list *new);
t_env_list		*ft_lstnew1(void **content, t_bool exported);
t_env_list  	*ft_env(char **env);
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
int				set_redirection(t_list *redir_lst);
void			duplicate_redir_fd(int fd_input, int fd_output);

/*************************   signals  ***************************/
void			handler(int a);

int				execute(t_list *cmd_lst);
int				p_open(char *file, int flags, int perm);
int				get_cmd_path(t_list *cmd_lst);
int				check_cmd(t_bool status, t_list **cmd);
int				(*init_pipe(t_list *cmd_lst))[2];
int				ft_builtin(t_list	*tmp, t_env_list *ms_export);
int				fork_cmd(t_list *cmd, int fd_in, int (*pipe_fd)[2]);
char			**to_env(char *cmd_name);

#endif