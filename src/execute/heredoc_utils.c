/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:44:50 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/21 17:52:53 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*allocates an [int**] array for subsequent heredoc file descripors filling*/
int	**allocate_hdoc_fd(t_list *cmd_lst)
{
	int	**fd_hdoc;
	int	i;
	int size;

	
	if (get_heredoc_cmd_num(cmd_lst) == 0 )
		return (NULL);
	fd_hdoc = malloca(get_heredoc_cmd_num(cmd_lst) * sizeof(int*));
	i = 0;
	while (cmd_lst)
	{
		size = get_redir_lst_heredoc_num(\
		((t_cmd_lst*)cmd_lst->content)->redir_lst);
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

/*returns total number of commands in pipeline with at least one heredoc*/
int	get_heredoc_cmd_num(t_list *cmd_lst)
{
	int		i;
	t_list	*redi_lst;

	i = 0;
	while (cmd_lst)
	{
		redi_lst = ((t_cmd_lst*)cmd_lst->content)->redir_lst;
		if (get_redir_lst_heredoc_num(redi_lst))
			i++;
		cmd_lst = cmd_lst->next;
	}
	return (i);
}

/*returns number of heredocs in a single redir_lst*/
int	get_redir_lst_heredoc_num(t_list *redir_lst)
{
	int		i;

	i = 0;
	while (redir_lst)
	{
		if (((t_redir_list*)redir_lst->content)->tok == TOK_HEREDOC)
			i++;
		redir_lst = redir_lst->next;
	}
	return (i);
}

/*inserts redirection list delimiters into the cmd_delim argument*/
void	insert_cmd_delim(t_list *redir_lst, char **cmd_delim)
{
	int	i;

	i = 0;
	while (redir_lst)
	{
		if (((t_redir_list*)redir_lst->content)->tok == TOK_HEREDOC)
		{
			cmd_delim[i] = ((t_redir_list*)redir_lst->content)->file;
			i++;
		}
		redir_lst = redir_lst->next;
	}	
	cmd_delim[i] = NULL;
}
