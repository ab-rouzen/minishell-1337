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

#endif