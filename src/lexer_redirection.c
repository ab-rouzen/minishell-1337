/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:37:43 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/01 20:38:07 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_redirection(t_list **tok_l, char *line)
{
	if (line[0] == '>')
		return (lex_redir_out(tok_l, line));
	else if (line[0] == '<')
		return (lex_redir_in(tok_l, line));
	return (0);
}

int	lex_redir_out(t_list **tok_l, char *line)
{
	int	i;

	i = 0;
	if (line[i] && line[i + 1] == '>')
	{
		ft_lstadd_back(tok_l, new_token_lst(TOK_REDI_O_APP, line, i + 2));
		return (i + 2);
	}
	ft_lstadd_back(tok_l, new_token_lst(TOK_REDI_O, line, i + 1));
	return (i + 1);
}

int	lex_redir_in(t_list **tok_l, char *line)
{
	int	i;

	i = 0;
	if (line[i] && line[i + 1] == '<')
	{
		ft_lstadd_back(tok_l, new_token_lst(TOK_HEREDOC, line, i + 2));
		return (i + 2);
	}
	ft_lstadd_back(tok_l, new_token_lst(TOK_REDI_I, line, i + 1));
	return (i + 1);
}
