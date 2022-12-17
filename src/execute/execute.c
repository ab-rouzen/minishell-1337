/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:38:21 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/16 12:40:51 by imittous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_exec(t_list *pipeline, char *cmd_path, char **environ, **pipe, int i);

int	execute(t_list *pipeline, char **environ)
{
	int			childPid;
	int			pipe1[10][2];
	int			i;
	char		*cmd_path;
	t_env_list	*env_lst;

	i = 0;
	env_lst = ft_env(environ);
	pipe1[0][0] = 0;
	pipe1[2][1] = 1;
	while (pipeline)
	{
		if (pipeline->next)
			if(pipe(pipe1[i + 1]))
				printf("pipe creation failed\n");
		cmd_path = get_cmd_path(pipeline, env_lst);
		if (cmd_path == NULL)
		{
			printf("command not found\n");
			pipeline =pipeline->next;
			continue;
		}
		//printf("pipe creation success: %d in | %d out \n", pipe1[i+1][1], pipe1[i+1][0]);
		childPid = fork();
		if (childPid == 0)
		{
			int r,w;
			if (pipeline->next)
				close(pipe1[i+1][0]); //closed read end of the 1
			//printf("pipe read end :%d\n", r = dup2(pipe1[i][0], 0));
			//close(pipe1[i][0]); h
			//if (pipeline->next)
			//printf("pipe write end :%d\n", w = dup2(pipe1[i + 1][1], 1));
			execve(cmd_path, ((t_cmd_lst*)pipeline->content)->cmd_args, environ);
			//puts("execve failed\n");
		}
		if (pipeline->next)
			close(pipe1[i + 1][1]); // closed write end of the pipe
		i++;
		waitpid(0, NULL, 0);
		pipeline = pipeline->next;
	}
	//printf("All exec'ed successfully\n");
	return (0);
}

void	child_exec(t_list *pipeline, char *cmd_path, char **environ, int **pipe, int i)
{
	int r,w;
	if (pipeline->next)
		close(pipe[i+1][0]); //closed read end of the pipe
	//printf("pipe read end :%d\n", r = dup2(pipe[i][0], 0));
	//close(pipe1[i][0]); h
	//if (pipeline->next)
	//printf("pipe write end :%d\n", w = dup2(pipe[i + 1][1], 1));
	execve(cmd_path, ((t_cmd_lst*)pipeline->content)->cmd_args, environ);
	puts("execve failed\n");
}
// void	pipe_cmd(void)
// {
// 	int	pipe1[2];

// 	pipe(&pipe1);

// 	dup2(1, pipe[0]);
// 	dup2(, pipe[1]);
// }
