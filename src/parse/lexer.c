/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:27:27 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/02 21:24:29 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*lexer(char *line)
{
	int		i;
	t_list	*tok_l;

	i = 0;
	tok_l = NULL;
	while (line[i])
	{
		i += lex_wspaces(&tok_l, &line[i]);
		i += lex_word(&tok_l, &line[i]);
		i += lex_redirection(&tok_l, &line[i]);
		i += lex_pipe(&tok_l, &line[i]);
		i += lex_quote(&tok_l, &line[i]);
		i += lex_dollar(&tok_l, &line[i]);
	}
	index_token(tok_l);
	return (tok_l);
}

int	lex_quote(t_list **tok_l, char *line)
{
	if (line[0] == '\"')
	{
		ft_lstadd_back(tok_l, new_token_lst(TOK_DQUOTE, line, 1));
		return (1);
	}
	else if (line[0] == '\'')
	{
		ft_lstadd_back(tok_l, new_token_lst(TOK_SQUOTE, line, 1));
		return (1);
	}
	return (0);
}

int	lex_pipe(t_list **tok_l, char *line)
{
	if (line[0] == '|')
	{
		ft_lstadd_back(tok_l, new_token_lst(TOK_PIPE, line, 1));
		return (1);
	}
	return (0);
}

int	lex_dollar(t_list **tok_l, char *line)
{
	if (line[0] == '$')
	{
		ft_lstadd_back(tok_l, new_token_lst(TOK_DOLLAR, line, 1));
		return (1);
	}
	return (0);
}
