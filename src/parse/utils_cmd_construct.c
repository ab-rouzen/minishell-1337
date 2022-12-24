/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd_construct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:40:59 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/24 16:03:24 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*to_cmdline_lst(t_list *tok_l)
{
	t_list	*cmd_lst;
	char	**cmd_words;
	t_list	*redir_lst;

	cmd_lst = NULL;
	while (tok_l)
	{
		redir_lst = NULL;
		cmd_words = malloca((get_words_num(tok_l) + 1) * sizeof(char *));
		tok_l = create_cmd_node(tok_l, cmd_words, &redir_lst);
		ft_lstadd_back(&cmd_lst, new_cmd_lst(cmd_words[0], \
		cmd_words, redir_lst));
		if (tok_l)
			tok_l = tok_l->next;
	}
	return (cmd_lst);
}

t_list	*create_cmd_node(t_list *tok_l, char **cmd_words, t_list **redir_lst)
{
	int	i;

	i = 0;
	while (tok_l && ((t_token *)tok_l->content)->tkn != TOK_PIPE)
	{
		if (((t_token *)tok_l->content)->tkn == TOK_WORD)
			cmd_words[i++] = ft_strdup_alloca(\
			((t_token *)tok_l->content)->val, malloca);
		else
		{
			ft_lstadd_back(redir_lst, new_redir_lst(\
			((t_token *)tok_l->content)->tkn, (\
			(t_token *)tok_l->next->content)->val));
			tok_l = tok_l->next;
		}
		if (tok_l)
			tok_l = tok_l->next;
	}
	cmd_words[i] = NULL;
	return (tok_l);
}

t_list	*new_cmd_lst(char *cmd_name, char **cmd_args, t_list *redir_lst)
{
	t_cmd_lst	*cmd_lst;

	cmd_lst = malloca(sizeof(t_cmd_lst));
	cmd_lst->cmd_args = cmd_args;
	cmd_lst->cmd_name = cmd_name;
	cmd_lst->redir_lst = redir_lst;
	cmd_lst->fd_in = STDIN_FILENO;
	cmd_lst->fd_out = STDOUT_FILENO;
	return (ft_lstnew_alloca(cmd_lst, malloca));
}

t_list	*new_redir_lst(enum e_token tok, char *file)
{
	t_redir_list	*new_lst;

	new_lst = malloca(sizeof(t_redir_list));
	if (new_lst == NULL)
		return (NULL);
	new_lst->file = file;
	new_lst->tok = tok;
	return (ft_lstnew_alloca(new_lst, malloca));
}
