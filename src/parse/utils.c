/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:24:06 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/27 21:40:45 by imittous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	delete_element(t_list **tok_l, enum e_token token)
{
	while (*tok_l)
	{
		if (((t_token *)(*tok_l)->content)->tkn == token)
			*tok_l = (*tok_l)->next;
		else
			tok_l = &(*tok_l)->next;
	}
}

void	heredoc_no_expand(t_list *tok_l)
{
	if (tok_l && ((t_token *)(tok_l->content))->tkn == TOK_HEREDOC)
	{
		while (tok_l)
		{
			if (tok_l->next && ((t_token *)(tok_l->next->content))->tkn \
				== TOK_WHITESPACE)
			{
				tok_l = tok_l->next;
				continue ;
			}
			if (tok_l->next && ((t_token *)(tok_l->next->content))->tkn \
				== TOK_DOLLAR)
				((t_token *)(tok_l->next->content))->tkn = TOK_WORD;
			break ;
		}
	}	
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
