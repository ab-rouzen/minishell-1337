/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:24:06 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/14 17:07:06 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *new_token_lst(enum token tok)
{
	enum token *new_tkn;

	new_tkn = (enum token*) malloc(sizeof(enum token));
	if (new_tkn == NULL)
		return (NULL);
	*new_tkn = tok;
	return (ft_lstnew(new_tkn));
}