/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 11:11:12 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/04 13:52:13 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int main(int ac, char **av, char **env)
{
	
	char	*str;
	char	**cmd;
	char	**cmd_path;
	int		check;
	int		i;
	t_env_list *ms_export;

(void)ac;
(void)av;

	ms_export = ft_env(env);
	while (ms_export)
	{
		if (!ft_strcmp(ms_export->variable, "PATH"))
		{
			cmd_path = ft_split(ms_export->value, ':');
			break ;
		}
		ms_export = ms_export->next;
	}
	check = 0;≥≥≥
	while (1) 
	{
		printf("\033[0;36m ");
		printf("mini_shell=>");
		printf("\033[0m "); 
		str = readline("");
		if (str && *str)
			add_history(str);
		cmd = ft_split(str, ' ');

		if (!ft_strcmp(cmd[0], "echo"))
			ft_echo(cmd);
		else if (!ft_strcmp(cmd[0], "cd"))
			ft_cd(cmd, ms_export);
		else if (!ft_strcmp(cmd[0], "pwd"))
			ft_pwd();
		else if (!ft_strcmp(cmd[0], "export") && !cmd[1])
			ft_print_expo(ms_export, cmd[0]);
		else if (!ft_strcmp(cmd[0], "export"))
			ft_export(&ms_export, cmd);
		else if (!ft_strcmp(cmd[0], "env"))
			ft_print_expo(ms_export, cmd[0]);
		else if (!ft_strcmp(cmd[0], "unset"))
			ft_unset(&ms_export, cmd[1]);
		else if (!ft_strcmp(cmd[0], "exit"))
		{
			ft_exit();
			exit (1);
		}
		else
		{
			i = 0;
			cmd[0] = ft_strjoin("/", cmd[0]);
			while (cmd_path[i])
			{
					// printf("%s\n",cmd[0]);
					// printf("%s\n", cmd_path[0]);
					//printf("%s\n", ft_strjoin(cmd_path[i], cmd[0]));
				if (access(ft_strjoin(cmd_path[i], cmd[0]), F_OK) == 0)
				{
					//printf("%s", ft_strjoin(cmd_path[i], cmd[0]), F_OK);
					int pid = fork() == 0;
					if (pid == 0)
					{
						execve(ft_strjoin(cmd_path[i], cmd[0]), NULL, env);
					}
					//wait(&pid);
				}
				i++;
			}
		}
			//printf ("%d",access("/bin/ls", F_OK));
			// printf("%s: command not found\n", str);
	}
	return 0;
}
