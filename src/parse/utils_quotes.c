/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:33:43 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/26 21:20:27 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	join_adjacent_token(t_list **tok_l, enum e_token tok)
{
	t_list	*head;

	head = *tok_l;
	while (*tok_l)
	{
		if (TTOKEN(*tok_l)->tkn == tok)
		{
			if ((*tok_l)->next && TTOKEN(*tok_l)->tkn == tok)
			{
				TTOKEN(*tok_l)->val = \
				ft_strjoin_alloca(TTOKEN(*tok_l)->val, \
				TTOKEN((*tok_l)->next)->val, malloca);
				(*tok_l)->next = (*tok_l)->next->next;
				continue ;
			}
		}
		tok_l = &(*tok_l)->next;
	}
}

void	join_token(t_list *start, enum e_token tok_stop)
{
	int		i;
	t_list	*tmp;
	char	*val;

	i = 0;
	if (start == NULL)
		return ;
	val = NULL;
	if (TTOKEN(start)->tkn != tok_stop)
	{
		val = ft_strdup_alloca(TTOKEN(start)->val, malloca);
		while (start->next && TTOKEN(start->next)->tkn != tok_stop)
		{
			val = ft_strjoin_alloca(val, TTOKEN(start->next)->val, malloca);
			start->next = start->next->next;
		}
		TTOKEN(start)->val = val;
		return ;
	}
	TTOKEN(start)->val = ft_strdup_alloca("\0", malloca);
}
