/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 00:55:38 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/29 00:58:04 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	heredoc_no_expand(t_list *tok_l)
{
	if (tok_l && ((t_token *)(tok_l->content))->tkn == TOK_HEREDOC)
	{
		tok_l = tok_l->next;
		tok_l = skip_token(tok_l, TOK_WHITESPACE);
		while (tok_l)
		{
			tok_l = skip_group_combo(tok_l);
			if (set_var_to_word(tok_l))
				tok_l = tok_l->next;
			else
				break ;
		}
	}	
}

t_list	*skip_token(t_list *lst, enum e_token tok)
{
	while (lst && ((t_token *)lst->content)->tkn == tok)
		lst = lst->next;
	return (lst);
}

/*returns next element of the next same element given in the argument */
t_list	*get_next_same_token(t_list *lst, enum e_token tok)
{
	if (lst == NULL)
		return (lst);
	if (((t_token *)lst->content)->tkn == tok)
		lst = lst->next;
	else
		return (lst);
	while (lst)
	{
		if (((t_token *)lst->content)->tkn == tok)
			return (lst->next);
		lst = lst->next;
	}
	return (lst);
}

t_list	*skip_token_group(t_list *lst, enum e_token tok)
{
	lst = get_next_same_token(lst, tok);
	if (lst && ((t_token *)lst->content)->tkn == tok)
		return (skip_token_group(lst, tok));
	return (lst);
}

t_list	*skip_group_combo(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	if (((t_token *)lst->content)->tkn == TOK_WORD)
	{
		lst = skip_token(lst, TOK_WORD);
		return (skip_group_combo(lst));
	}
	else if (((t_token *)lst->content)->tkn == TOK_DQUOTE)
	{
		lst = skip_token_group(lst, TOK_DQUOTE);
		return (skip_group_combo(lst));
	}
	else if (((t_token *)lst->content)->tkn == TOK_SQUOTE)
	{
		lst = skip_token_group(lst, TOK_SQUOTE);
		return (skip_group_combo(lst));
	}
	return (lst);
}
