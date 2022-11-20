/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:24:06 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/18 22:23:59 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*allocates a new token_lst a returns it*/
t_list	*new_token_lst(enum token token, int n_char)
{
	t_token *new_tkn_lst;

	new_tkn_lst = malloc(sizeof(t_token));
	if (new_tkn_lst == NULL)
		return (NULL);
	new_tkn_lst->tkn = token;
	new_tkn_lst->n_char = n_char;
	return (ft_lstnew(new_tkn_lst));
}

/*assigns an index to each token based on the number of characters it has*/
void	index_token(t_list *tok_lst)
{
	int index;

	index = 0;
	while (tok_lst)
	{
		index += (*(t_token*)tok_lst->content).n_char;
		(*(t_token*)tok_lst->content).index = index;
		tok_lst = tok_lst->next;
	}
}