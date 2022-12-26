/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_environ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:35:28 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/26 19:36:22 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_env_var(t_list **tok_l)
{
	t_list	*tmp;

	heredoc_no_expand(*tok_l);
	if (*tok_l && TTOKEN(*tok_l)->tkn == TOK_DOLLAR)
	{
		if ((*tok_l)->next && TTOKEN((*tok_l)->next)->tkn == TOK_WORD)
		{
			tmp = (*tok_l)->next->next;
			TTOKEN(*tok_l)->val = get_env_val(TTOKEN((*tok_l)->next)->val);
			(*tok_l)->next = tmp;
			TTOKEN(*tok_l)->tkn = TOK_WORD;
			if (TTOKEN(*tok_l)->val == NULL)
				*tok_l = (*tok_l)->next;
		}
		else
			TTOKEN(*tok_l)->tkn = TOK_WORD;
	}
}

char	*get_env_val(char *var)
{
	char		*buff;
	t_env_list	*env;
	char		**var_path;

	env = g_data.env_lst;
	var_path = ft_split(var, '/');
	while (env)
	{
		if (!ft_strcmp(env->variable, var_path[0]))
		{
			buff = ft_strdup_alloca(env->value, malloca);
			buff = ft_strjoin_alloca(buff, strchr(var, '/'), malloca);
			free_split(var_path);
			return (buff);
		}
		env = env->next;
	}
	free_split(var_path);
	if (ft_strcmp(var, "?") == 0)
		return (ft_itoa(g_data.exit_status));
	return (NULL);
}

char	*join_strings(char **str)
{
	int		i;
	char	*buf;

	i = 0;
	buf = NULL;
	while (str[i])
	{
		buf = ft_strjoin_alloca(buf, str[i], &malloca);
		i++;
	}
	return (buf);
}
