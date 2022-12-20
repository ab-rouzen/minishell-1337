/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:33:43 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/20 12:01:04 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	join_adjacent_token(t_list **tok_l, enum e_token tok)
{
	t_list	*head;

	head = *tok_l;
	while (*tok_l)
	{
		if (((t_token *)(*tok_l)->content)->tkn == tok)
		{
			if ((*tok_l)->next
				&& ((t_token *)(*tok_l)->next->content)->tkn == tok)
			{
				((t_token *)(*tok_l)->content)->val = \
				ft_strjoin_alloca(((t_token *)(*tok_l)->content)->val, \
				((t_token *)(*tok_l)->next->content)->val, malloca);
				(*tok_l)->next = (*tok_l)->next->next;
				continue ;
			}
		}
		tok_l = &(*tok_l)->next;
	}
}

void	join_token(t_list *start, enum e_token quote)
{
	int		i;
	t_list	*tmp;
	char	*val;

	i = 0;
	tmp = start->next;
	val = NULL;
	if (((t_token *)tmp->content)->tkn != quote)
	{
		val = ft_strdup_alloca(((t_token *)tmp->content)->val, malloca);
		tmp = tmp->next;
		while (tmp && ((t_token *)tmp->content)->tkn != quote)
		{
			val = ft_strjoin_alloca(val, ((t_token *)tmp->content)->val, \
			malloca);
			tmp = tmp->next;
		}
		((t_token *)start->content)->val = val;
		return ;
	}
	((t_token *)start->content)->val = ft_strdup_alloca("\0", malloca);
}
