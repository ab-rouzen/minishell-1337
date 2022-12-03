/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:27:27 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/18 18:15:07 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lexer(char *line)
{
	int i;
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
	return (tok_l);
}

int	lex_quote(t_list **tok_l, char *line)
{
	if (line[0] == '\"')
	{
		ft_lstadd_back(tok_l, new_token_lst(TOK_DQUOTE, 1));
		return (1);
	}
	else if (line[0] == '\'')
	{
		ft_lstadd_back(tok_l, new_token_lst(TOK_SQUOTE, 1));
		return (1);
	}
	return (0);
}

int	lex_pipe(t_list **tok_l, char *line)
{
	if (line[0] == '|')
	{
		ft_lstadd_back(tok_l, new_token_lst(TOK_PIPE, 1));
		return (1);
	}
	return (0);
}

int	lex_dollar(t_list **tok_l, char *line)
{
	if (line[0] == '$')
	{
		ft_lstadd_back(tok_l, new_token_lst(TOK_DOLLAR, 1));
		return (1);
	}
	return (0);
}

int	lex_word(t_list **tok_l, char *line)
{
	int i;

	i = 0;
	while (line[i] && !is_metachar(line[i]))
		i++;
	if (i)
		ft_lstadd_back(tok_l, new_token_lst(TOK_WORD, i));
	return (i);
}                                                       

bool	is_metachar(char tok)
{
	if (tok == '$' || tok == '|' || tok == '>' || \
		tok == '<' || tok == '\'' || tok == '\"' || \
		tok == ' ' || tok == '\t' || tok == '\n')
		return (TRUE);
	return (FALSE);
}

int	lex_redirection(t_list **tok_l, char *line)
{
	int i;

	i = 0;
	if (line[i] == '>')
	{
		if (line [i] && line[i + 1] == '>')
		{
			ft_lstadd_back(tok_l, new_token_lst(TOK_REDI_O_APP, i + 2));
			return (i + 2);
		}
		ft_lstadd_back(tok_l, new_token_lst(TOK_REDI_O, i + 1));
		return (i + 1);
	}
	else if (line[i] == '<')	
	{ 
		if (line [i] && line[i + 1] == '<')
		{
			ft_lstadd_back(tok_l, new_token_lst(TOK_HEREDOC, i + 2));
			return (i + 2);
		}
		ft_lstadd_back(tok_l, new_token_lst(TOK_REDI_I, i + 1));
		return (i + 1);
	}
	return (i);
}

int	lex_wspaces(t_list **tok_l, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (i)
		ft_lstadd_back(tok_l, new_token_lst(TOK_WHITESPACE, i));
	return (i);
}