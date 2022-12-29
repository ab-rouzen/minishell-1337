/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:24:06 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/29 00:57:54 by arouzen          ###   ########.fr       */
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

void	syntax_err(t_list *tok_l, int matched)
{
	print_error(SYNX_ERR, UNX_TKN, 0);
	ft_putendl_fd(((t_token *) \
	(get_nlst(tok_l, matched)->content))->val, STDERR_FILENO);
	g_data.exit_status = 258;
}

int	set_var_to_word(t_list *lst)
{
	if (lst)
	{
		if (((t_token *)lst->content)->tkn == TOK_DOLLAR)
		{
			((t_token *)lst->content)->tkn = TOK_WORD;
			return (1);
		}
	}
	return (0);
}
