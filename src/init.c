/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:00:47 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/26 18:53:42 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	init_shell(char **environ)
{
	rl_catch_signals = 0;
	rl_point = 0;
	g_data.env_lst = ft_env(environ);
	g_data.exit_status = 0;
}

void	reset_vars(void)
{
	g_data.hdoc_cmd_no = 0;
	g_data.exec = 0;
	g_data.close_hdc = 0;
}
