/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:32:11 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/03 17:41:26 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*allocates memory using malloc and stores corresponding pointer */
/*for eventual feeing. Returns pointer to all malloced nodes*/
/*upon receiving size '0'*/
void	*malloca(size_t size)
{
	static t_list	*malloced_mem;
	t_list			*tmp;

	if (size == 0)
	{
		mfree((void **)&malloced_mem);
		return (NULL);
	}
	tmp = malloc(size);
	if (tmp == NULL)
		exit(EXIT_FAILURE);
	ft_lstadd_back(&malloced_mem, ft_lstnew(tmp));
	return (tmp);
}

void	mfree(void **node)
{
	t_list	*malloced_mem;
	t_list	*tmp;

	malloced_mem = *node;
	while (malloced_mem)
	{
		free(malloced_mem->content);
		tmp = malloced_mem;
		malloced_mem = malloced_mem->next;
		// if (tmp != *node)
		free(tmp);
	}
	*node = NULL;
}
