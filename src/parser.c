/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:56:03 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/16 15:58:25 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_line(t_list *tok_l)
{
	return (1);
}

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
int	match_command(t_list *tok_l)
{
	int	n_match[4];

	ft_bzero(n_match, sizeof(n_match));
	if (match_word(tok_l))
		n_match[0] = 1;
	if (match_redi_list(tok_l))
		n_match[1] = match_redi_list(tok_l);
	if (match_word(tok_l) && match_command(tok_l->next))
		n_match[2] = match_command(tok_l->next) + 1;
	if (match_redi_list(tok_l) && match_command(tok_l->next))
		n_match[3] = match_redi_list(tok_l) && match_command(tok_l->next);
	return (l_match(n_match, 4));
}

int	match_word(t_list *tok_l)
{
	if (tok_l == NULL)
		return (0);
	if (*(enum token*) tok_l->content == TOK_WHITESPACE)
	{	printf("is here word---\n");
		return (1);
	}
	if (*(enum token*) tok_l->content == TOK_WORD)
	{	printf("is here word---\n");
		return (1);
	}
	return (0);
}

int	match_wspace(t_list *tok_l)
{
	if (tok_l == NULL)
		return (0);
	if (*(enum token*) tok_l->content == TOK_WHITESPACE)
	{	printf("is here word---\n");
		return (1);
	}
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
	{	printf("is here redsym---\n");
		return (1);
	}
	return (0);
}

int	match_redirection(t_list *tok_l)
{
	//printf("been here\n");
	if (tok_l == NULL)
		return (0);
	if (match_redirect_sym(tok_l) &&
		match_word(tok_l->next))
	{	printf("is here red---\n");
		return (2);
	}
	// if (match_redirect_sym(tok_l) == 0 &&
	// 	match_word(tok_l->next) == 0)
	// 	return (0);
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
		//return (1);
	if (match_redirection(tok_l) && \
		match_redi_list(get_nlst(tok_l, 2)))
		n_match[1] = match_redi_list(get_nlst(tok_l, 2)) + 2;
	return (l_match(n_match, 2));
}

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
		//printf("lmatch is %d\n", tab[i]);
		i++;
	}
	return (max);
}