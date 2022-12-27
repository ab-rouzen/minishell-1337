/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:44:50 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/26 22:39:21 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*allocates an [int**] array for subsequent heredoc file descripors filling*/
int	**allocate_hdoc_fd(t_list *cmd_lst)
{
	int	**fd_hdoc;
	int	i;
	int	size;

	if (get_heredoc_cmd_num(cmd_lst) == 0)
		return (NULL);
	fd_hdoc = malloca(get_heredoc_cmd_num(cmd_lst) * sizeof(int *));
	i = 0;
	while (cmd_lst)
	{
		size = get_redir_lst_heredoc_num(\
		((t_cmd_lst *)cmd_lst->content)->redir_lst);
		if (size == 0)
		{
			cmd_lst = cmd_lst->next;
			continue ;
		}
		fd_hdoc[i] = malloca(size);
		cmd_lst = cmd_lst->next;
		i++;
	}
	return (fd_hdoc);
}

/*inserts redirection list delimiters into the cmd_delim argument*/
void	insert_cmd_delim(t_list *redir_lst, char **cmd_delim)
{
	int	i;

	i = 0;
	while (redir_lst)
	{
		if (((t_redir_list *)redir_lst->content)->tok == TOK_HEREDOC)
		{
			cmd_delim[i] = ((t_redir_list *)redir_lst->content)->file;
			i++;
		}
		redir_lst = redir_lst->next;
	}	
	cmd_delim[i] = NULL;
}

/*returns all heredoc delimiters from a pipeline*/
char	***get_heredoc_delim(t_list *cmd_lst)
{
	int		i;
	int		size;
	t_list	*redi_lst;
	char	***delim;

	i = 0;
	delim = malloca(sizeof(char **) * (get_heredoc_cmd_num(cmd_lst) + 1));
	while (cmd_lst)
	{
		redi_lst = ((t_cmd_lst *)cmd_lst->content)->redir_lst;
		size = get_redir_lst_heredoc_num(redi_lst);
		if (size == 0)
		{
			cmd_lst = cmd_lst->next;
			continue ;
		}
		delim[i] = malloca((size + 1) * sizeof(char *));
		insert_cmd_delim(redi_lst, delim[i]);
		i++;
		cmd_lst = cmd_lst->next;
	}
	delim[i] = NULL;
	return (delim);
}
