/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_environ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:35:28 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/19 15:37:39 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_env_var(t_list **tok_l)
{
	t_list	*tmp;

	heredoc_no_expand(*tok_l);
	if (*tok_l && ((t_token *)(*tok_l)->content)->tkn == TOK_DOLLAR)
	{
		if ((*tok_l)->next
			&& ((t_token *)(*tok_l)->next->content)->tkn == TOK_WORD)
		{
			tmp = (*tok_l)->next->next;
			((t_token *)(*tok_l)->content)->val = \
			get_env_val(((t_token *)(*tok_l)->next->content)->val);
			(*tok_l)->next = tmp;
			((t_token *)(*tok_l)->content)->tkn = TOK_WORD;
		}
		else
			((t_token *)(*tok_l)->content)->tkn = TOK_WORD;
	}
}

char	*get_env_val(char *var)
{
	char	*buff;
	t_env_list	*env;

	env = g_data.env_lst;
	while (env)
	{
		if (!ft_strcmp(env->variable, var))
		{
			buff = ft_strdup_alloca(env->value, malloca);
			return (buff);
		}
		env = env->next;
	}
	return (ft_strdup_alloca("\0", malloca));
}
