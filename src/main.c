/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:46:10 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/15 13:55:45 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[])
{
	char	*line;
	t_list	*tok_l;

	(void) argv;
	(void) argc;
	//rl_complete('\t', filename_completion_function);
	while(TRUE)
	{
		line  = readline(SHELL_PROMPT);
		tok_l = lexer(line);
		parser();
		if (line && *line)
		{
			add_history(line);
		}
		while (tok_l)
		{
			printf("token is %d\n", *(enum token*) tok_l->content);
			tok_l = tok_l->next;
		}
	}
	return (0);
}