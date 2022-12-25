/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:46:10 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/25 05:27:08 by imittous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"
# include <readline/readline.h>
void	print_test(t_list *tmp);
void	print_token(char *line);

t_shell	g_data;

int	main(int argc, char *argv[], char **environ)
{
	char	*line;
	t_list	*cmd_lst;

	rl_catch_signals = 0;
	rl_point = 0;
	(void)argv;
	(void)argc;
	// signal(SIGINT, &handler);
	// signal(SIGQUIT, &handler);
	g_data.env_lst = ft_env(environ);
	while (TRUE)
	{
		ft_sig_handler(MAIN);
		malloca(FREE_ALL);
		line = readline(SHELL_PROMPT);
		if (line && *line)
			add_history(line);
		cmd_lst = parse(line);
		init_shell(environ, cmd_lst);
		if (cmd_lst)
		{
			// print_token(line);
			// print_test(cmd_lst);
			g_data.fd_heredoc = here_doc(cmd_lst);
				execute(cmd_lst);
		}
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
			printf("word:[%s]\n",
					((t_cmd_lst *)tmp->content)->cmd_args[i++]);
		printf("tokens:\n");
		mylist = ((t_cmd_lst *)tmp->content)->redir_lst;
		while (mylist)
		{
			printf("enum tok:[%d]\n",
					((t_redir_list *)mylist->content)->tok);
			printf("word:[%s]\n", ((t_redir_list *)mylist->content)->file);
			mylist = mylist->next;
		}
		printf("--------NEXT LIST----------\n");
		tmp = tmp->next;
	}	
}

void	print_token(char *line)
{
	t_list	*tmp;

	printf("token list | ");
	tmp = lexer(line);
	if (!unquote(&tmp))
		printf("Quote parse error\n");
	join_adjacent_token(&tmp, TOK_WORD);
	delete_element(&tmp, TOK_WHITESPACE);
	while (tmp)
	{
		printf("-->%d, val:%s ", ((t_token *)tmp->content)->tkn,
				((t_token *)tmp->content)->val);
		tmp = tmp->next;
	}
	printf(" |\n");
}



