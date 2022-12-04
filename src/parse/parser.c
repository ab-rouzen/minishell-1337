/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:56:03 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/04 18:53:30 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*parse(char *line, char **environ)
{
	t_list	*tok_l;

	tok_l = lexer(line);
	if (!unquote(&tok_l, line, environ))
		printf("Quote parse error\n");
	join_adjacent_token(&tok_l, TOK_WORD);
	delete_element(&tok_l, TOK_WHITESPACE);
	if (ft_lstsize(tok_l) == match_pipeline(tok_l))
		printf("All matched: SUCCESS\n");
	else
		printf("Parse error: FAILURE\n");
	return (to_cmdline_lst(tok_l));
}

void	match_command_rules(t_list *tok_l, int n_match[])
{
	n_match[0] = match_word(tok_l);
	n_match[1] = match_redi_list(tok_l);
	n_match[2] = n_match[0] + match_command(get_nlst(tok_l, n_match[0]));
	n_match[3] = n_match[1] + match_command(get_nlst(tok_l, n_match[1]));
}

int	match_command(t_list *tok_l)
{
	int	n_match[4];

	if (tok_l == NULL)
		return (0);
	ft_bzero(n_match, sizeof(n_match));
	n_match[0] = match_word(tok_l);
	n_match[1] = match_redi_list(tok_l);
	if (n_match[0])
		n_match[2] = n_match[0] + match_command(get_nlst(tok_l, n_match[0]));
	if (n_match[1])
		n_match[3] = n_match[1] + match_command(get_nlst(tok_l, n_match[1]));
	return (l_match(n_match, 4));
}

int	match_word(t_list *tok_l)
{
	if (tok_l == NULL)
		return (0);
	if (*(enum e_token *)tok_l->content == TOK_WORD)
		return (1);
	return (0);
}

int	match_wspace(t_list *tok_l)
{
	if (tok_l == NULL)
		return (0);
	if (*(enum e_token *)tok_l->content == TOK_WHITESPACE)
		return (1);
	return (0);
}
