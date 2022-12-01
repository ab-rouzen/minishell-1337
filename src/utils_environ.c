/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_environ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:35:28 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/01 20:36:31 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_env_var(t_list **tok_l, char **environ)
{
	t_list	*tmp;

	if (*tok_l && ((t_token *)(*tok_l)->content)->tkn == TOK_DOLLAR)
	{
		if ((*tok_l)->next
			&& ((t_token *)(*tok_l)->next->content)->tkn == TOK_WORD)
		{
			tmp = (*tok_l)->next->next;
			((t_token *)(*tok_l)->content)->val = get_env_val(environ, \
			((t_token *)(*tok_l)->next->content)->val);
			if (((t_token *)(*tok_l)->content)->val == NULL)
				(*tok_l) = tmp;
			else
			{
				(*tok_l)->next = tmp;
				((t_token *)(*tok_l)->content)->tkn = TOK_WORD;
			}
		}
		else
			*tok_l = (*tok_l)->next;
	}
}

char	*get_env_val(char *environ[], char *var)
{
	int		i;
	char	**tmp;
	char	*buff;

	i = 0;
	while (environ[i])
	{
		tmp = ft_split(environ[i], '=');
		if (!ft_strcmp(tmp[0], var))
		{
			free(tmp[0]);
			buff = ft_strdup_alloca(tmp[1], malloca);
			free(tmp[1]);
			free(tmp);
			return (buff);
		}
		free(tmp[0]);
		free(tmp[1]);
		free(tmp);
		i++;
	}
	return (NULL);
}
