/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:45:33 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/28 21:41:43 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	lex_wspaces(t_list **tok_l, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (i)
		ft_lstadd_back(tok_l, new_token_lst(TOK_WHITESPACE, line, i));
	return (i);
}

int	lex_word(t_list **tok_l, char *line)
{
	int	i;

	i = 0;
	while (line[i] && !is_metachar(line[i]))
		i++;
	if (i)
	{
		ft_lstadd_back(tok_l, new_token_lst(TOK_WORD, line, i));
	}
	return (i);
}

t_bool	is_metachar(char tok)
{
	if (tok == '$' || tok == '|' || tok == '>' || \
		tok == '<' || tok == '\'' || tok == '\"' || \
		tok == ' ' || tok == '\t' || tok == '\n')
		return (TRUE);
	return (FALSE);
}
