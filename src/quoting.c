/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:15:58 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/18 22:53:01 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unquote(t_list *tok_l, char *line, char **environ)
{
	while (tok_l)
	{
		if (((t_token*)(tok_l->content))->tkn == TOK_SQUOTE)
			sq_unquote(tok_l, line);
		else if (((t_token*)(tok_l->content))->tkn == TOK_DQUOTE)
			dq_unquote(tok_l, line);
		tok_l = tok_l->next;
	}
}

void	dq_unquote(t_list *tok_l, char *line)
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
				return ;
			//}
		}
		ltkn = ltkn->next;
	}
}

void	sq_unquote(t_list *tok_l, char *line)
{
	int	i;
	t_list	*ltkn;

	i = 0;
	ltkn  = tok_l;
	while (ltkn)
	{
		//if (((t_token*)ltkn->content)->tkn == TOK_DOLLAR)
		printf("benn here\n");
		if (((t_token*)ltkn->content)->tkn == TOK_SQUOTE)
		{
			// should free elements here
			//if (((t_token*)(*tok_l)->next->content)->tkn != TOK_SQUOTE);
			//{
				// ((n*)(*tok_l)->next->content)->index = ((t_token*)ltkn->content)->index 
				tok_l->next = ltkn->next;
				((t_token*)tok_l->content)->tkn = TOK_WORD;
			//}
		}
		ltkn = ltkn->next;
	}
}
