/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_environ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:35:28 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/29 14:49:37 by imittous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	expand_env_var(t_list **tok_l)
{
	t_list	*tmp;

	heredoc_no_expand(*tok_l);
	if (*tok_l && ((t_token *)(*tok_l)->content)->tkn == TOK_DOLLAR)
	{
		if ((*tok_l)->next && \
		((t_token *)((*tok_l)->next->content))->tkn == TOK_WORD)
		{
			tmp = (*tok_l)->next->next;
			((t_token *)(*tok_l)->content)->val = \
			get_env_val(((t_token *)((*tok_l)->next->content))->val);
			(*tok_l)->next = tmp;
			((t_token *)(*tok_l)->content)->tkn = TOK_WORD;
			if (((t_token *)(*tok_l)->content)->val == NULL)
				*tok_l = (*tok_l)->next;
			if (*tok_l && ((t_token *)(*tok_l)->content)->tkn == TOK_DOLLAR)
				expand_env_var(tok_l);
		}
		else
			((t_token *)(*tok_l)->content)->tkn = TOK_WORD;
		return (0);
	}
	return (1);
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
		return (ft_itoa_alloca(g_data.exit_status, malloca));
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
