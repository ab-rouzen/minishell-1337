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

/*************************   builtins  ***************************/
int				ft_builtin(t_list	*tmp);
int				ft_check_builtin(t_list	*cmd_lst);
t_env_list		*ft_env(char **env);
void			ft_unset(t_env_list **ms_list, char *cmd);
void			ft_print_expo(t_env_list *ms_export, char *cmd, t_list *cmd_list);
void			ft_export(t_env_list **ms_export, char **cmd);

/*************************   signals  ***************************/
void			 ft_sig_handler(char location);
int				execute(t_list *cmd_lst);
int				p_open(char *file, int flags, int perm);
int				get_cmd_path(t_list *cmd_lst);
int				check_cmd(t_bool status, t_list **cmd);
int				(*init_pipe(t_list *cmd_lst))[2];
int				ft_builtin(t_list	*tmp);
int				fork_cmd(t_list *cmd, int fd_in, int (*pipe_fd)[2]);
char			**to_env(void);



/*####################      1_builtin_utils.c      ####################*/

int	ft_print_echo(char **cmd, int i, int check,t_list *cmd_list);
int	ft_echo(char **cmd, t_list *cmd_list);
int	ft_pwd(t_list *cmd_list);

/*####################      1_builtin_utils.c      ####################*/



/*####################      2_builtin_utils.c      ####################*/
void	ft_update_export(t_env_list *ms_list, char* oldpwd);
int	ft_cd_norm_1(char *cmd, t_env_list *ms_list, char cwd[255]);
int	ft_find_oldpwd(char cwd[255], t_env_list *tmp, t_list *cmd_list);
int	ft_cd(char *cmd, t_env_list *ms_list, t_list *cmd_list);


/*####################      2_builtin_utils.c      ####################*/
#endif