/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:40:41 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/01 20:44:04 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	match_redirect_sym(t_list *tok_l)
{
	if (tok_l == NULL)
		return (0);
	if (*(enum token *)tok_l->content == TOK_REDI_I || \
		*(enum token *)tok_l->content == TOK_REDI_O || \
		*(enum token *)tok_l->content == TOK_REDI_O_APP || \
		*(enum token *)tok_l->content == TOK_HEREDOC)
		return (1);
	return (0);
}

int	match_redirection(t_list *tok_l)
{
	if (tok_l == NULL)
		return (0);
	if (match_redirect_sym(tok_l) && \
		match_word(tok_l->next))
		return (2);
	return (0);
}

int	match_redi_list(t_list *tok_l)
{
	int	n_match[2];

	ft_bzero(n_match, sizeof(n_match));
	if (tok_l == NULL)
		return (0);
	if (match_redirection(tok_l))
		n_match[0] = 2;
	if (match_redirection(tok_l) && \
		match_redi_list(get_nlst(tok_l, 2)))
		n_match[1] = match_redi_list(get_nlst(tok_l, 2)) + 2;
	return (l_match(n_match, 2));
}
