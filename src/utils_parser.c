/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:43:15 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/01 20:43:42 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_nlst(t_list *lst, int n)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (i == n)
			return (lst);
		i++;
		lst = lst->next;
	}
	return (lst);
}

/*finds a returns the longest match in tab*/
int	l_match(int tab[], int cases)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	while (i < cases)
	{
		if (tab[i] > max)
			max = tab[i];
		i++;
	}
	return (max);
}
