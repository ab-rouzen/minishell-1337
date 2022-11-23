/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd_construct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:40:59 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/23 17:53:24 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*to_cmdline_lst(t_list	*tok_l)
{
	t_list	*cmd_lst;

	cmd_lst = NULL;
	while (tok_l)
	{
		ft_lstadd_back()
		while (tok_l)
	}
}

t_cmdline	*new_cmd_lst(char *cmd_name, char *cmd_args, t_redir_list redir_lst)
{
	
}

t_redir_list	*new_redir_lst(enum token tok, char *file)
{
	t_redir_list	*new_lst;

	new_lst = malloca(sizeof(t_redir_list));
	if (new_lst == NULL)
		return (NULL);
	new_lst->file = file;
	new_lst->tok = tok;
	return (new_lst);
}