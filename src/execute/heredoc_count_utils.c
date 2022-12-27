/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_count_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 22:36:02 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/26 22:39:43 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*returns total number of commands in pipeline with at least one heredoc*/
int	get_heredoc_cmd_num(t_list *cmd_lst)
{
	int		i;
	t_list	*redi_lst;

	i = 0;
	while (cmd_lst)
	{
		redi_lst = ((t_cmd_lst *)cmd_lst->content)->redir_lst;
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
		if (((t_redir_list *)redir_lst->content)->tok == TOK_HEREDOC)
			i++;
		redir_lst = redir_lst->next;
	}
	return (i);
}
