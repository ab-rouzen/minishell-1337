/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:00:47 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/23 02:14:23 by imittous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	init_shell(char **environ, t_list *cmd_lst)
{
	g_data.env_lst = ft_env(environ);
	g_data.close_hdc = 0;
}
