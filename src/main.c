/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:46:10 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/03 17:43:24 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	print_test(t_list *tmp);

int	main(int argc, char *argv[], char **environ)
{
	char	*line;
	t_list	*tmp;
	int		i;
	t_list	*mylist;

	(void)argv;
	(void)argc;
	while (TRUE)
	{
		malloca(0);
		line = readline(SHELL_PROMPT);
		if (line && *line)
			add_history(line);
		tmp = parse(line, environ);
		print_test(tmp);
		free(line);
	}
	return (0);
}

void	print_test(t_list *tmp)
{
	int		i;
	t_list	*mylist;

	while (tmp)
	{
		i = 0;
		while (((t_cmd_lst *)tmp->content)->cmd_args[i])
			printf("word:'%s'\n",
					((t_cmd_lst *)tmp->content)->cmd_args[i++]);
		printf("tokens:\n");
		mylist = ((t_cmd_lst *)tmp->content)->redir_lst;
		while (mylist)
		{
			printf("enum tok:'%d'\n",
					((t_redir_list *)mylist->content)->tok);
			printf("word:'%s'\n", ((t_redir_list *)mylist->content)->file);
			mylist = mylist->next;
		}
		printf("--------NEXT LIST----------\n");
		tmp = tmp->next;
	}	
}
