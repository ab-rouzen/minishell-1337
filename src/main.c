/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:46:10 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/27 18:56:49 by imittous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	print_test(t_list *tmp);
void	print_token(char *line);

t_shell	g_data;

int	main(int argc, char *argv[], char **environ)
{
	char	*line;
	t_list	*cmd_lst;

	(void)argv;
	(void)argc;
	init_shell(environ);
	while (TRUE)
	{
		reset_vars();
		ft_sig_handler(MAIN);
		malloca(FREE_ALL);
		line = readline(SHELL_PROMPT);
		if (!line)
			exit(0);
		if (*line)
			add_history(line);
		cmd_lst = parse(line);
		if (cmd_lst && g_data.close_hdc == FALSE)
			execute(cmd_lst);
		free(line);
	}
	return (0);
}

// void	print_test(t_list *tmp)
// {
// 	int		i;
// 	t_list	*mylist;

// 	while (tmp)
// 	{
// 		i = 0;
// 		while (((t_cmd_lst *)tmp->content)->cmd_args[i])
// 			printf("word:[%s]\n",
// 					((t_cmd_lst *)tmp->content)->cmd_args[i++]);
// 		printf("tokens:\n");
// 		mylist = ((t_cmd_lst *)tmp->content)->redir_lst;
// 		while (mylist)
// 		{
// 			printf("enum tok:[%d]\n",
// 					((t_redir_list *)mylist->content)->tok);
// 			printf("word:[%s]\n", ((t_redir_list *)mylist->content)->file);
// 			mylist = mylist->next;
// 		}
// 		printf("--------NEXT LIST----------\n");
// 		tmp = tmp->next;
// 	}	
// }

// void	print_token(char *line)
// {
// 	t_list	*tmp;

// 	printf("token list | ");
// 	tmp = lexer(line);
// 	if (!unquote(&tmp))
// 		printf("Quote parse error\n");
// 	join_adjacent_token(&tmp, TOK_WORD);
// 	delete_element(&tmp, TOK_WHITESPACE);
// 	while (tmp)
// 	{
// 		printf("-->%d, val:%s ", ((t_token *)tmp->content)->tkn,
// 				((t_token *)tmp->content)->val);
// 		tmp = tmp->next;
// 	}
// 	printf(" |\n");
// }