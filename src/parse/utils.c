/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:24:06 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/03 21:43:49 by arouzen          ###   ########.fr       */
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
