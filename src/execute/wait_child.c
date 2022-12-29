/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 10:11:47 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/29 02:17:15 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	wait_child(int pid, t_list *cmd)
{
	int	stat_loc;

	ignore_signals();
	if (cmd == NULL)
		return ;
	if (waitpid(pid, &stat_loc, WUNTRACED) != -1)
		child_exit_stat(((t_cmd_lst *)cmd->content)->cmd_name, stat_loc);
}

void	child_exit_stat(char *cmd_name, int stat_loc)
{
	char	*tmp;

	if (WIFEXITED(stat_loc))
		g_data.exit_status = WEXITSTATUS(stat_loc);
	else if (WIFSIGNALED(stat_loc) && WTERMSIG(stat_loc) != SIGINT)
	{
		g_data.exit_status = 128 + WTERMSIG(stat_loc);
		tmp = ft_itoa(g_data.exit_status);
		if (WTERMSIG(stat_loc) == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		else
			print_error(cmd_name, \
			ft_strjoin_alloca("received signal ", tmp, malloca), 1);
		(free(tmp), rl_on_new_line());
	}
	else
	{
		g_data.exit_status = 128 + WTERMSIG(stat_loc);
		printf("\n");
		rl_on_new_line();
	}
	while (waitpid(-1, &stat_loc, WUNTRACED) > 0)
		;
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
