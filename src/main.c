/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:46:10 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/23 16:48:20 by imittous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"
# include <readline/readline.h>
void	print_test(t_list *tmp);
void	print_token(char *line);

t_shell	g_data;

int	main(int argc, char *argv[], char **environ)
{
	char	*line;
	t_list	*cmd_lst = NULL;
	rl_catch_signals = 0;
	rl_point = 0;
	(void)argv;
	(void)argc;
	while (TRUE)
	{
		ft_sig_handler(MAIN);
		malloca(FREE_ALL);
		init_shell(environ, cmd_lst); // enter the shell with empty env -i ./minishell
		line = readline(SHELL_PROMPT);
		
		if (!line)
		{
			printf("minishell$ exit");
			exit(0);
		}
		if (line && *line)
			add_history(line);
		cmd_lst = parse(line);
		// // print_token(line);
		// // print_test(cmd_lst);
		g_data.fd_heredoc = here_doc(cmd_lst);
		if (*line && ft_check_builtin(((t_cmd_lst *)cmd_lst->content)->cmd_name))
			ft_builtin(cmd_lst);
		else
			execute(cmd_lst);
		free(line);
	}		
	return (0);
}

int	ft_check_builtin(t_list	*cmd_name)
{
	if (!ft_strcmp(cmd_name, "echo") || !ft_strcmp(cmd_name, "cd") ||
		!ft_strcmp(cmd_name, "pwd") || !ft_strcmp(cmd_name, "export") ||
		!ft_strcmp(cmd_name, "env") || !ft_strcmp(cmd_name, "unset") ||
		!ft_strcmp(cmd_name, "exit"))
	{
		return (1);	
	}
	return (0);
}


int	ft_builtin(t_list	*tmp)
{
	char	*cmd_name;

	cmd_name = ((t_cmd_lst*)tmp->content)->cmd_name;
	if (!ft_strcmp(cmd_name, "echo"))
		ft_echo(((t_cmd_lst*)tmp->content)->cmd_args);
	if (!ft_strcmp(cmd_name, "cd"))
		ft_cd(((t_cmd_lst*)tmp->content)->cmd_args[1], g_data.env_lst);
	else if (!ft_strcmp(cmd_name, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd_name, "export"))
	{
		if (((t_cmd_lst*)tmp->content)->cmd_args[1])
			ft_export(&g_data.env_lst, ((t_cmd_lst*)tmp->content)->cmd_args);
		else
			ft_print_expo(g_data.env_lst, cmd_name);
	}
	else if (!ft_strcmp(cmd_name, "env"))
		ft_print_expo(g_data.env_lst, cmd_name);
	else if (!ft_strcmp(cmd_name, "unset"))
		ft_unset(&g_data.env_lst, ((t_cmd_lst*)tmp->content)->cmd_name);
	else if (!ft_strcmp(cmd_name, "exit"))
	{
		ft_exit();
		exit (1);
	}
}
