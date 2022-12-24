/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 11:11:12 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/24 12:45:58 by arouzen          ###   ########.fr       */
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
