/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 10:11:47 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/26 10:20:30 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	wait_child(int pid, t_list *cmd)
{
	int	stat_loc;

	if (cmd == NULL)
		return ;
	if (waitpid(pid, &stat_loc, WUNTRACED) != -1)
		child_exit_stat(TCMD(cmd)->cmd_name, stat_loc);
}

void	child_exit_stat(char *cmd_name, int stat_loc)
{
	char	*tmp;

	if (WIFEXITED(stat_loc))
	{
		//printf("old exit status %d\n", g_data.exit_status);
		g_data.exit_status = WEXITSTATUS(stat_loc);
		//printf("exited with %d\n", g_data.exit_status);
	}
	else if (WIFSIGNALED(stat_loc))
	{
		tmp = ft_itoa(WTERMSIG(stat_loc));
		print_error(cmd_name, ft_strjoin_alloca(": received signal ", tmp, malloca));
		free(tmp);
	}
	while(waitpid(-1, &stat_loc, WUNTRACED) > 0)
		;
}
