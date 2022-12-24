/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:16:38 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/02 21:25:13 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*allocates a new token_lst and returns it*/
t_list	*new_token_lst(enum e_token token, char *line, int n_char)
{
	t_token	*new_tkn_lst;

	new_tkn_lst = malloca(sizeof(t_token));
	if (new_tkn_lst == NULL)
		return (NULL);
	new_tkn_lst->tkn = token;
	new_tkn_lst->n_char = n_char;
	new_tkn_lst->val = copy_token_val(line, n_char);
	return (ft_lstnew_alloca(new_tkn_lst, malloca));
}

/*assigns an index to each token based on the number of characters it has*/
void	index_token(t_list *tok_lst)
{
	int	index;

	index = 0;
	while (tok_lst)
	{
		(*(t_token *)tok_lst->content).index = index;
		index += (*(t_token *)tok_lst->content).n_char;
		tok_lst = tok_lst->next;
	}
}

/*copies 'size' bytes from 'line' to allocated 'buffer' and returns it*/
char	*copy_token_val(char *line, int size)
{
	int		i;
	char	*buff;

	i = 0;
	buff = malloca(size + 1);
	while (i < size)
	{
		buff[i] = line[i];
		i++;
	}
	buff[i] = '\0';
	return (buff);
}

int	get_words_num(t_list *tok_l)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tok_l && ((t_token *)tok_l->content)->tkn != TOK_PIPE)
	{
		if (((t_token *)tok_l->content)->tkn == TOK_WORD)
			i++;
		else
			j++;
		tok_l = tok_l->next;
	}
	return (i - j);
}

void	replace_element(t_list *tok_l, enum e_token token_1, \
		enum e_token token_2)
{
	while (tok_l)
	{
		if (((t_token *)tok_l->content)->tkn == token_1)
			((t_token *)tok_l->content)->tkn = token_2;
		tok_l = tok_l->next;
	}
}
