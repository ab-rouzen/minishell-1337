/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:24:06 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/02 21:25:15 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	delete_token(t_list *start, t_list *end)
// {
// 	t_list	*tmp;
//
// 	while (start != end)
// 	{
// 		tmp = start->next;
// 		free(start->content);
// 		free(start);
// 		start = tmp;
// 	}
// 	free(end->content);
// 	free(end);
// }

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

t_list	*ft_lstnew_falloc(void *content, void *(*alloc)(size_t))
{
	t_list	*new_list;

	new_list = alloc(sizeof(t_list));
	new_list->next = NULL;
	new_list->content = content;
	return (new_list);
}

char	*ft_strdup_alloca(const char *src, void *(alloc)(size_t))
{
	int		i;
	char	*n_str;
	char	*nsrc;

	i = 0;
	nsrc = (char *)src;
	if (src == NULL)
		return (NULL);
	n_str = alloc((ft_strlen(nsrc) + 1) * sizeof(char));
	if (n_str == NULL)
		return (NULL);
	while (nsrc[i])
	{
		n_str[i] = nsrc[i];
		i++;
	}
	n_str[i] = '\0';
	return (n_str);
}