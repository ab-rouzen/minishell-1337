/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:00:47 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/29 14:19:00 by imittous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

char	**ft_initiate_env_lst(char	**env)
{
	char	cwd[255];

	env = malloc(sizeof(char *) * 5);
	env[0] = ft_strdup("OLDPWD= ");
	env[1] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	env[2] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	env[3] = ft_strdup("SHLVL=1");
	env[4] = NULL;
	return (env);
}

void	init_shell(char **environ)
{
	char	cwd[255];
	char	**tmp;

	rl_catch_signals = 0;
	rl_point = 0;
	if (!environ[0])
	{
		tmp = ft_initiate_env_lst(environ);
		g_data.env_lst = ft_env(tmp);
		free_split(tmp);
	}
	else
		g_data.env_lst = ft_env(environ);
	g_data.exit_status = 0;
	g_data.pwd = getcwd(cwd, sizeof(cwd));
}

void	reset_vars(void)
{
	g_data.hdoc_cmd_no = 0;
	g_data.exec = 0;
	g_data.close_hdc = 0;
}
