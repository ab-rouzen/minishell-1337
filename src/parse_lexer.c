/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:27:27 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/14 18:33:40 by arouzen          ###   ########.fr       */
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
		i += skip_spaces(&line[i]);
		i += lex_word(&tok_l, &line[i]);
		i += lex_redirection(&tok_l, &line[i]);
		i += lex_pipe(&tok_l, &line[i]);
	}
	return (tok_l);
}

int lex_pipe(t_list **tok_l, char *line)
{
	if (line[0] == '|')
	{
		ft_lstadd_back(tok_l, new_token_lst(TOK_PIPE));
		return (1);
	}
	return (0);
}

int lex_word(t_list **tok_l, char *line)
{
	int i;

	i = 0;
	while ((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z'))
		i++;
	if (i)
	{
		ft_lstadd_back(tok_l, new_token_lst(TOK_WORD));
		printf("in words: token is %d\n", TOK_WORD);
	}
	return (i);
}                                                       

int	lex_redirection(t_list **tok_l, char *line)
{
	int i;

	i = 0;
	if (line[i] == '>')
	{
		if (line [i] && line[i + 1] == '>')
		{
			ft_lstadd_back(tok_l, new_token_lst(TOK_RED_O_APP));
			return (i + 2);
		}
		ft_lstadd_back(tok_l, new_token_lst(TOK_REDI_O));
		return (i + 1);
	}
	else if (line[i] == '<')	
	{
		if (line [i] && line[i + 1] == '<')
		{
			ft_lstadd_back(tok_l, new_token_lst(TOK_HEREDOC));
			return (i + 2);
		}
		ft_lstadd_back(tok_l, new_token_lst(TOK_REDI_I));
		return (i + 1);
	}
	return (i);
}

int	skip_spaces(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);                                                                                   
}