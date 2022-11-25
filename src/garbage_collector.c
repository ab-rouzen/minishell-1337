/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:32:11 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/24 17:42:32 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*allocates memory using malloc and stores corresponding pointer */
/*for eventual feeing. Returns pointer to all malloced nodes*/
/*upon receiving size '0'*/
void	*malloca(size_t size)
{
	static t_list	*malloced_mem;
	t_list	*tmp;

	//printf("been here: size is '%d'\n", size);
	if (size == 0)
	{
		mfree((void**)&malloced_mem);
		return (NULL);
	}
	tmp = malloc(size);
	if (tmp == NULL)
		exit(77);
	ft_lstadd_back(&malloced_mem, ft_lstnew(tmp));
	return (tmp);
}

void	mfree(void **node)
{
	t_list	*malloced_mem;
	malloced_mem = *node;
	while (malloced_mem)
	{
		free (malloced_mem->content);
		malloced_mem = malloced_mem->next;
	}
	*node = NULL;
}
