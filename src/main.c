/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:46:10 by arouzen           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/20 12:39:13 by arouzen          ###   ########.fr       */
=======
/*   Updated: 2022/11/20 09:19:39 by imittous         ###   ########.fr       */
>>>>>>> 8b98af8ba4fd7818b8fd7f1486f97e214f41ca60
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
int main(int argc, char *argv[], char **environ)
{
	char	*line;
	t_list	*tok_l;
	t_list	*tmp;

	(void) argv;
	(void) argc;
	//rl_complete('\t', filename_completion_function);
	while(TRUE)
	{
		line  = readline(SHELL_PROMPT);
		tok_l = lexer(line);
		if (line && *line)
		{
			add_history(line);
		}
		tmp = tok_l;
		if (!unquote(tok_l, line, environ))
			printf("Quote parse error!\n");
		printf("token list | ");
		while (tmp)
		{
			printf("-->%d, val:%s ", ((t_token*)tmp->content)->tkn, ((t_token*)tmp->content)->val);
			tmp = tmp->next;
		}
		printf(" |\n");
		//printf("%d matched\n", match_redi_list(tok_l));
		printf("%d matched\n", match_pipeline(tok_l));
		if (ft_lstsize(tok_l) == match_pipeline(tok_l))
			printf("All matched: SUCCESS\n");
		else
			printf("Parse error: FAILURE\n");
	}
	return (0);
}
=======
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
>>>>>>> 8b98af8ba4fd7818b8fd7f1486f97e214f41ca60
