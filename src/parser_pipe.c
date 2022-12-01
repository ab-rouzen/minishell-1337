/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:42:13 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/01 20:42:33 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (*(enum token *)tok_l->content == TOK_PIPE)
		return (1);
	return (0);
}
