/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:46:10 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/14 17:41:31 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[])
{
	char	*cmd;
	t_list	*tok_l;

	(void) argv;
	(void) argc;
	//rl_complete('\t', filename_completion_function);
	while(TRUE)
	{
		cmd  = readline(SHELL_PROMPT);
		tok_l = lexer(cmd);
		//printf("%p", tok_l);
		while (tok_l)
		{
			printf("token is %d\n", *(enum token*) tok_l->content);
			tok_l = tok_l->next;
		}
	}
	//printf("line read: _%s_\n", cmd);
	return (0);
}