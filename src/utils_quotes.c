/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:33:43 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/01 20:34:31 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_adjacent_quotes(t_list **tok_l)
{
	t_list	*head;
	char	*tmp;

	head = *tok_l;
	while (*tok_l)
	{
		if (((t_token *)(*tok_l)->content)->tkn == TOK_QUOTE)
		{
			if ((*tok_l)->next
				&& ((t_token *)(*tok_l)->next->content)->tkn == TOK_QUOTE)
			{
				tmp = ((t_token *)(*tok_l)->content)->val;
				((t_token *)(*tok_l)->content)->val = \
				ft_strjoin(((t_token *)(*tok_l)->content)->val, \
				((t_token *)(*tok_l)->next->content)->val);
				free(tmp);
				free(((t_token *)(*tok_l)->next->content)->val);
				(*tok_l)->next = (*tok_l)->next->next;
				continue ;
			}
		}
		tok_l = &(*tok_l)->next;
	}
	replace_element(head, TOK_QUOTE, TOK_WORD);
}

void	join_token(t_list *start, t_list *end, enum token quote)
{
	int		i;
	t_list	*tmp;
	char	*val;
	char	*buff;

	i = 0;
	tmp = start->next;
	val = NULL;
	if (((t_token *)tmp->content)->tkn != quote)
	{
		val = ft_strdup(((t_token *)tmp->content)->val);
		tmp = tmp->next;
		while (tmp && ((t_token *)tmp->content)->tkn != quote)
		{
			buff = val;
			val = ft_strjoin(val, ((t_token *)tmp->content)->val);
			free(buff);
			tmp = tmp->next;
		}
	}
	((t_token *)start->content)->val = val;
}
