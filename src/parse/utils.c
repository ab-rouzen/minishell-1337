/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:24:06 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/28 22:22:17 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	delete_element(t_list **tok_l, enum e_token token)
{
	while (*tok_l)
	{
		if (((t_token *)(*tok_l)->content)->tkn == token)
			*tok_l = (*tok_l)->next;
		else
			tok_l = &(*tok_l)->next;
	}
}

void	heredoc_no_expand(t_list *tok_l)
{
	if (tok_l && ((t_token *)(tok_l->content))->tkn == TOK_HEREDOC)
	{
		tok_l = tok_l->next;
		tok_l = skip_token(tok_l, TOK_WHITESPACE);
		while (tok_l)
		{
			tok_l = skip_group_combo(tok_l);
			if (tok_l)
			printf("token-->[%s]\n", ((t_token *)tok_l->content)->val);
			if (set_var_to_word(tok_l))
				tok_l = tok_l->next;
			else
				break ;
		}
			if (tok_l)
			printf("token-->[%s]\n", ((t_token *)tok_l->content)->val);
	}	
}

int	set_var_to_word(t_list *lst)
{
	if (lst)
	{
		if (((t_token *)lst->content)->tkn == TOK_DOLLAR)
		{
			((t_token *)lst->content)->tkn = TOK_WORD;
			//set_var_to_word(lst->next);
			return (1);
		}
	}
	return (0);
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

void	free_split(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	syntax_err(t_list *tok_l, int matched)
{
	print_error(SYNX_ERR, UNX_TKN, 0);
	ft_putendl_fd(((t_token *)(get_nlst(tok_l, matched)->content))->val, \
	STDERR_FILENO);
}
