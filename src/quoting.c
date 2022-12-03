/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:15:58 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/03 22:30:20 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unquote(t_list *tok_l, char *line, char **environ)
{
	while (tok_l)
	{
		if (((t_token*)(tok_l->content))->tkn == TOK_SQUOTE)
		{
			if (sq_unquote(tok_l, line) == FALSE)
				return (FALSE);
		}
		else if (((t_token*)(tok_l->content))->tkn == TOK_DQUOTE)
		{
			if (dq_unquote(tok_l, line, environ) == FALSE)
				return (FALSE);
		}
		else
			expand_env_var(&tok_l, environ);

		//dq_unquote(tok_l, line);
		tok_l = tok_l->next;
	}
}

int	dq_unquote(t_list *tok_l, char *line, char **environ)
{
	int	i;
	t_list	*ltkn;

	i = 0;
	ltkn  = tok_l;
	while (ltkn)
	{
		//if (((t_token*)ltkn->content)->tkn == TOK_DOLLAR)
		if (((t_token*)ltkn->content)->tkn == TOK_SQUOTE)
		{
			// should free elements here
			//if (((t_token*)(*tok_l)->next->content)->tkn != TOK_SQUOTE);
			//{
				// ((n*)(*tok_l)->next->content)->index = ((t_token*)ltkn->content)->index 
				tok_l->next = ltkn->next;
				((t_token*)tok_l->content)->tkn = TOK_WORD;
				return (TRUE);
			//}
		}
		ltkn = ltkn->next;
	}
	return (FALSE);
}

int	sq_unquote(t_list *tok_l, char *line)
{
	int	i;
	t_list	*ltkn;
	t_list	*tmp;

	i = 0;
	ltkn  = tok_l->next;
	while (ltkn)
	{
		//if (((t_token*)ltkn->content)->tkn == TOK_DOLLAR)
		//printf("benn here\n");
		if (((t_token*)ltkn->content)->tkn == TOK_SQUOTE)
		{
			tmp = ltkn->next;
			//printf("was i here ?\n");
			join_token(tok_l, ltkn);
			tok_l->next = tmp;
			((t_token*)tok_l->content)->tkn = TOK_WORD;
			return (TRUE);
		}
		ltkn = ltkn->next;
	}
	return (FALSE);
}