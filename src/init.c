/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:00:47 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/28 10:58:47 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

char	**ft_initiate_env_lst(char	**env)
{
	char	cwd[255];

	env = malloc(sizeof(char *) * 4);
	env[0] = ft_strdup("OLDPWD= ");
	env[1] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	env[2] = ft_strdup("SHLVL=1");
	env[3] = NULL;
	return (env);
}

void	init_shell(char **environ)
{
	rl_catch_signals = 0;
	rl_point = 0;
	if (!environ[0])
		g_data.env_lst = ft_env(ft_initiate_env_lst(environ));
	else
		g_data.env_lst = ft_env(environ);
	g_data.exit_status = 0;
}

void	reset_vars(void)
{
	g_data.hdoc_cmd_no = 0;
	g_data.exec = 0;
	g_data.close_hdc = 0;
}
