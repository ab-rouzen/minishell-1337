#ifndef EXECUTION_H
# define EXECUTION_H
#include "minishell.h"

typedef struct s_env_list
{
	void				*variable;
	void				*value;
	struct s_env_list	*next;
}					t_env_list;


void		ft_echo(char **cmd);
void		ft_cd(char **cmd);
void		ft_pwd(char **cmd);
t_env_list	*ft_lstlast1(t_env_list *lst);
void		ft_lstadd_back1(t_env_list **lst, t_env_list *new);
t_env_list	*ft_lstnew1(void **content);
t_env_list  *ft_env(char **env);

#endif