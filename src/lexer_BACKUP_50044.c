/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:27:27 by arouzen           #+#    #+#             */
<<<<<<< HEAD:src/lexer.c
/*   Updated: 2022/11/19 11:11:52 by arouzen          ###   ########.fr       */
=======
/*   Updated: 2022/11/18 18:15:07 by arouzen          ###   ########.fr       */
>>>>>>> 8b98af8ba4fd7818b8fd7f1486f97e214f41ca60:src/lexer.c
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
	index_token(tok_l);
	return (tok_l);
}

int	lex_quote(t_list **tok_l, char *line)
{
	if (line[0] == '\"')
	{
<<<<<<< HEAD:src/lexer.c
		ft_lstadd_back(tok_l, new_token_lst(TOK_DQUOTE, line, 1));
		// ((t_token*)(*tok_l)->content)->val = copy_token_val(line, 1);
=======
		ft_lstadd_back(tok_l, new_token_lst(TOK_DQUOTE, 1));
>>>>>>> 8b98af8ba4fd7818b8fd7f1486f97e214f41ca60:src/lexer.c
		return (1);
	}
	else if (line[0] == '\'')
	{
<<<<<<< HEAD:src/lexer.c
		ft_lstadd_back(tok_l, new_token_lst(TOK_SQUOTE, line, 1));
		// ((t_token*)(*tok_l)->content)->val = copy_token_val(line, 1);
=======
		ft_lstadd_back(tok_l, new_token_lst(TOK_SQUOTE, 1));
>>>>>>> 8b98af8ba4fd7818b8fd7f1486f97e214f41ca60:src/lexer.c
		return (1);
	}
	return (0);
}

int	lex_pipe(t_list **tok_l, char *line)
{
	if (line[0] == '|')
	{
<<<<<<< HEAD:src/lexer.c
		ft_lstadd_back(tok_l, new_token_lst(TOK_PIPE, line, 1));
		// ((t_token*)(*tok_l)->content)->val = copy_token_val(line, 1);
=======
		ft_lstadd_back(tok_l, new_token_lst(TOK_PIPE, 1));
>>>>>>> 8b98af8ba4fd7818b8fd7f1486f97e214f41ca60:src/lexer.c
		return (1);
	}
	return (0);
}

int	lex_dollar(t_list **tok_l, char *line)
{
	if (line[0] == '$')
	{
<<<<<<< HEAD:src/lexer.c
		ft_lstadd_back(tok_l, new_token_lst(TOK_DOLLAR, line, 1));
		// ((t_token*)(*tok_l)->content)->val = copy_token_val(line, 1);
=======
		ft_lstadd_back(tok_l, new_token_lst(TOK_DOLLAR, 1));
>>>>>>> 8b98af8ba4fd7818b8fd7f1486f97e214f41ca60:src/lexer.c
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
<<<<<<< HEAD:src/lexer.c
	{
		ft_lstadd_back(tok_l, new_token_lst(TOK_WORD, line, i));
		// ((t_token*)(*tok_l)->content)->val = copy_token_val(line, i);
	}
=======
		ft_lstadd_back(tok_l, new_token_lst(TOK_WORD, i));
>>>>>>> 8b98af8ba4fd7818b8fd7f1486f97e214f41ca60:src/lexer.c
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
<<<<<<< HEAD:src/lexer.c
			ft_lstadd_back(tok_l, new_token_lst(TOK_REDI_O_APP, line, i + 2));
			// ((t_token*)(*tok_l)->content)->val = copy_token_val(line, i + 2);
			return (i + 2);
		}
		ft_lstadd_back(tok_l, new_token_lst(TOK_REDI_O, line, i + 1));
		// ((t_token*)(*tok_l)->content)->val = copy_token_val(line, i + 1);
=======
			ft_lstadd_back(tok_l, new_token_lst(TOK_REDI_O_APP, i + 2));
			return (i + 2);
		}
		ft_lstadd_back(tok_l, new_token_lst(TOK_REDI_O, i + 1));
>>>>>>> 8b98af8ba4fd7818b8fd7f1486f97e214f41ca60:src/lexer.c
		return (i + 1);
	}
	else if (line[i] == '<')	
	{ 
		if (line [i] && line[i + 1] == '<')
		{
<<<<<<< HEAD:src/lexer.c
			ft_lstadd_back(tok_l, new_token_lst(TOK_HEREDOC, line, i + 2));
			// ((t_token*)(*tok_l)->content)->val = copy_token_val(line, i + 2);
			return (i + 2);
		}
		ft_lstadd_back(tok_l, new_token_lst(TOK_REDI_I, line, i + 1));
		// ((t_token*)(*tok_l)->content)->val = copy_token_val(line, i + 1);
=======
			ft_lstadd_back(tok_l, new_token_lst(TOK_HEREDOC, i + 2));
			return (i + 2);
		}
		ft_lstadd_back(tok_l, new_token_lst(TOK_REDI_I, i + 1));
>>>>>>> 8b98af8ba4fd7818b8fd7f1486f97e214f41ca60:src/lexer.c
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
<<<<<<< HEAD:src/lexer.c
	{
		ft_lstadd_back(tok_l, new_token_lst(TOK_WHITESPACE, line, i));
		// ((t_token*)(*tok_l)->content)->val = copy_token_val(line, i);
	}
=======
		ft_lstadd_back(tok_l, new_token_lst(TOK_WHITESPACE, i));
>>>>>>> 8b98af8ba4fd7818b8fd7f1486f97e214f41ca60:src/lexer.c
	return (i);
}