/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 10:11:47 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/27 14:16:41 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	wait_child(int pid, t_list *cmd)
{
	int	stat_loc;

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
		tmp = ft_itoa(WTERMSIG(stat_loc));
		print_error(cmd_name, \
		ft_strjoin_alloca("received signal ", tmp, malloca), 1);
		free(tmp);
	}
	while (waitpid(-1, &stat_loc, WUNTRACED) > 0)
		;
}