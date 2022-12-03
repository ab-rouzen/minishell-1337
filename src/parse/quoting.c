/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:15:58 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/02 21:24:58 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	unquote(t_list **tok_l, char *line, char **environ)
{
	while (*tok_l)
	{
		if (((t_token *)((*tok_l)->content))->tkn == TOK_SQUOTE)
		{
			if (sq_unquote((*tok_l), line) == FALSE)
				return (FALSE);
		}
		else if (((t_token *)((*tok_l)->content))->tkn == TOK_DQUOTE)
		{
			if (dq_unquote((*tok_l), line, environ) == FALSE)
				return (FALSE);
		}
		else
			expand_env_var(tok_l, environ);
		if (*tok_l)
			tok_l = &(*tok_l)->next;
	}
	return (TRUE);
}

int	dq_unquote(t_list *tok_l, char *line, char **environ)
{
	int		i;
	t_list	**ltkn;
	t_list	*tmp;

	i = 0;
	ltkn = &tok_l->next;
	while (*ltkn)
	{
		expand_env_var(ltkn, environ);
		if (((t_token *)(*ltkn)->content)->tkn == TOK_DQUOTE)
		{
			tmp = (*ltkn)->next;
			join_token(tok_l, (*ltkn), TOK_DQUOTE);
			tok_l->next = tmp;
			((t_token *)tok_l->content)->tkn = TOK_WORD;
			return (TRUE);
		}
		ltkn = &(*ltkn)->next;
	}
	return (FALSE);
}

int	sq_unquote(t_list *tok_l, char *line)
{
	int		i;
	t_list	*ltkn;
	t_list	*tmp;

	i = 0;
	ltkn = tok_l->next;
	while (ltkn)
	{
		if (((t_token *)ltkn->content)->tkn == TOK_SQUOTE)
		{
			tmp = ltkn->next;
			join_token(tok_l, ltkn, TOK_SQUOTE);
			tok_l->next = tmp;
			((t_token *)tok_l->content)->tkn = TOK_WORD;
			return (TRUE);
		}
		ltkn = ltkn->next;
	}
	return (FALSE);
}