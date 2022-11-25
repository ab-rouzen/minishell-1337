/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd_construct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:40:59 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/25 09:16:27 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*to_cmdline_lst(t_list	*tok_l)
{
	t_list		*cmd_lst;
	char		**cmd_words;
	t_list		*redir_lst;
	int			i;

	cmd_lst = NULL;
	while (tok_l)
	{
		cmd_words = malloca((get_words_num(tok_l) + 1) * sizeof(char*));
		i = 0;
		redir_lst = NULL;
		while (tok_l && ((t_token*)tok_l->content)->tkn != TOK_PIPE)
		{
			if (((t_token*)tok_l->content)->tkn == TOK_WORD)
				cmd_words[i++] = ft_strdup(((t_token*)tok_l->content)->val);
			else
			{
				ft_lstadd_back(&redir_lst, ft_lstnew(new_redir_lst(((t_token*)tok_l->content)->tkn, ((t_token*)tok_l->next->content)->val)));
				tok_l = tok_l->next;
			}
			if (tok_l)
				tok_l = tok_l->next;
		}
		cmd_words[i] = NULL;
		ft_lstadd_back(&cmd_lst, ft_lstnew(new_cmd_lst("NA", cmd_words, redir_lst)));
		if (tok_l)
			tok_l = tok_l->next;
	}
	return (cmd_lst);
}

t_cmd_lst	*new_cmd_lst(char *cmd_name, char **cmd_args, t_list *redir_lst)
{
	t_cmd_lst	*cmd_lst;

	cmd_lst = malloca(sizeof(t_cmd_lst));
	//wont need this...
	//if (cmd_lst == NULL)
	//	return (NULL);
	cmd_lst->cmd_args = cmd_args;
	cmd_lst->cmd_name = cmd_name;
	cmd_lst->redir_lst = redir_lst;
	return (cmd_lst);
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