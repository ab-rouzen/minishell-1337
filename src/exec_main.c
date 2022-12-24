/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 11:11:12 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/12 21:05:10 by imittous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	handler(int a)
{
	if (a == SIGINT)
	{
		printf("\n"); // Move to a new line
    	rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0);
    	rl_redisplay();
	}
	if (a == SIGQUIT)
	{
	
    	rl_redisplay();
		return ;
	}
}

int main(int ac, char **av, char **env)
{
	
	char	*str;
	char	**cmd;
	char	**cmd_path;
	int		check;
	int		i;
	t_env_list *ms_export;
	pid_t				pid;
	struct sigaction	chanel;

(void)ac;
(void)av;

	chanel.sa_flags = SA_SIGINFO;
	chanel.sa_sigaction = &handler;

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
	check = 0;
	while (1) 
	{
		//signal(EOF, &handler);
		printf("\033[0;36m");
		str = readline("mini_shell=>");
		printf("\033[0m"); 
		if (str && *str)
			add_history(str);
		cmd = ft_split(str, ' ');

		signal(SIGINT, &handler);
		signal(SIGQUIT, &handler);
		if (!str)
		{
			printf ("exit");
			exit(0);
		}

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
				if (access(ft_strjoin(cmd_path[i], cmd[0]), F_OK) == 0)
				{
					char *argvv[] = {ft_strjoin(cmd_path[i], cmd[0]), NULL};
					if (fork() == 0)
						execve(ft_strjoin(cmd_path[i], cmd[0]), argvv, env);
					waitpid(0, NULL, 0);
				}
				i++;
			}
		}

		
	}
	return 0;
}
