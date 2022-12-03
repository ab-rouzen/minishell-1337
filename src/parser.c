/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:56:03 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/18 09:06:29 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_nlst(t_list *lst, int n)
{
	int i;

	i = 0;
	while (lst)
	{
		if (i == n)
			return (lst);
		i++;
		lst = lst->next;
	}
	return (lst);
}

int	match_pipeline(t_list *tok_l)
{
	int	n_match[2];
	int	match_tmp[1];

	ft_bzero(n_match, sizeof(n_match));
	n_match[0] = match_command(tok_l);
	match_tmp[0] = match_pipe_sym(get_nlst(tok_l, n_match[0]));
	if (n_match[0] && match_tmp[0])
	{
		n_match[1] = match_pipeline(get_nlst(tok_l, n_match[0] + match_tmp[0]));
		if (n_match[1])
			n_match[1] += n_match[0] + match_tmp[0];
	}
	return (l_match(n_match, 2));
}

int	match_pipe_sym(t_list *tok_l)
{
	if (tok_l == NULL)
		return (0);
	if (*(enum token*) tok_l->content == TOK_PIPE)
		return (1);
	return (0);
	
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
	if (*(enum token*) tok_l->content == TOK_WHITESPACE)
		return (1);
	if (*(enum token*) tok_l->content == TOK_WORD)
		return (1);
	return (0);
}

int	match_wspace(t_list *tok_l)
{
	if (tok_l == NULL)
		return (0);
	if (*(enum token*) tok_l->content == TOK_WHITESPACE)
		return (1);
	return (0);
}

int	match_redirect_sym(t_list *tok_l)
{
	if (tok_l == NULL)
		return (0);
	if (*(enum token*) tok_l->content == TOK_REDI_I || \
		*(enum token*) tok_l->content == TOK_REDI_O || \
		*(enum token*) tok_l->content == TOK_REDI_O_APP || \
		*(enum token*) tok_l->content == TOK_HEREDOC)
		return (1);
	return (0);
}

int	match_redirection(t_list *tok_l)
{
	if (tok_l == NULL)
		return (0);
	if (match_redirect_sym(tok_l) &&
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

/*finds a returns the longest match in tab*/
int	l_match(int tab[], int cases)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	while (i < cases)
	{
		if (tab[i] > max)
			max = tab[i];
		i++;
	}
	return (max);
}