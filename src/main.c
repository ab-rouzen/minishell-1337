/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:46:10 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/19 13:01:21 by imittous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int main(int argc, char *argv[])
// {
// 	char	*line;
// 	t_list	*tok_l;
// 	t_list	*tmp;

// 	(void) argv;
// 	(void) argc;
// 	//rl_complete('\t', filename_completion_function);
// 	while(TRUE)
// 	{
// 		line  = readline(SHELL_PROMPT);
// 		tok_l = lexer(line);
// 		if (line && *line)
// 		{
// 			add_history(line);
// 		}
// 		tmp = tok_l;
// 		while (tmp)
// 		{
// 			printf("token is %d\n", *(enum token*) tmp->content);
// 			tmp = tmp->next;
// 		}
// 		//printf("%d matched\n", match_redi_list(tok_l));
// 		printf("%d matched\n", match_command(tok_l));
// 		if (ft_lstsize(tok_l) == match_command(tok_l))
// 			printf("All matched: SUCCESS\n");
// 		else
// 			printf("Parse error: FAILURE\n");
// 	}
// 	return (0);
// }