#ifndef EXECUTION_H
# define EXECUTION_H
#include "minishell.h"



void		ft_echo(char **cmd);
void		ft_cd(char **cmd);
void		ft_pwd(char **cmd);
t_env_list	*ft_lstlast1(t_env_list *lst);
void		ft_lstadd_back1(t_env_list **lst, t_env_list *new);
t_env_list	*ft_lstnew1(void **content);
void		ft_env(char **env);

#endif