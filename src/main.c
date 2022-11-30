/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:46:10 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/30 19:56:33 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		//malloca(0);
		line  = readline(SHELL_PROMPT);
        tok_l = lexer(line);
		if (line && *line)
		{
			add_history(line);
		}
		tmp = tok_l;
		if (!unquote(&tok_l, line, environ))
			printf("Quote parse error!\n");
		join_adjacent_quotes(&tok_l);
		delete_element(&tok_l, TOK_WHITESPACE);
		printf("token list | ");
		tmp = tok_l;
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
		tmp = to_cmdline_lst(tok_l);
		while (tmp)
		{
			int i = 0;
			while (((t_cmd_lst*)tmp->content)->cmd_args[i])
				printf("word:'%s'\n", ((t_cmd_lst*)tmp->content)->cmd_args[i++]);
			printf("tokens:\n");
			t_list	*mylist = ((t_cmd_lst*)tmp->content)->redir_lst;
			while (mylist)
			{
				printf("enum tok:'%d'\n", ((t_redir_list*)mylist->content)->tok);
				printf("word:'%s'\n", ((t_redir_list*)mylist->content)->file);
				mylist = mylist->next;
			}
			printf("--------NEXT LIST----------\n");
			tmp = tmp->next;
		}
		free(line);
	}
	return (0);
}
