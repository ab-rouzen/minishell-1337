/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:46:10 by arouzen           #+#    #+#             */
/*   Updated: 2022/10/16 15:59:47 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[])
{
	char *cmd;

	(void) argv;
	(void) argc;
	//rl_complete('\t', filename_completion_function);
	while(TRUE)
	{
		cmd  = readline(SHELL_NAME);
	}
	printf("line read: _%s_\n", cmd);
	return (0);
}