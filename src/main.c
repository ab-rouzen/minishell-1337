/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:46:10 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/23 17:20:53 by arouzen          ###   ########.fr       */
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
	// signal(SIGINT, &handler);
	// signal(SIGQUIT, &handler);
	while (TRUE)
	{
		malloca(FREE_ALL);
		init_shell(environ, cmd_lst);
		line = readline(SHELL_PROMPT);
		if (line && *line)
			add_history(line);
		cmd_lst = parse(line);
		if (cmd_lst)
		{
			print_token(line);
			print_test(cmd_lst);
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


void	handler(int a)
{
	if (a == SIGINT)
	{
		printf("\n"); // Move to a new line
    	rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0);
    	rl_redisplay();
	}
	if (a == SIGQUIT)
	{
    	rl_redisplay();
		return ;
	}
}
int	ft_builtin(t_list	*tmp, t_env_list *ms_export)
{
	char	*cmd_name;

	cmd_name = ((t_cmd_lst*)tmp->content)->cmd_name;
	if (!ft_strcmp(cmd_name, "echo"))
		ft_echo(((t_cmd_lst*)tmp->content)->cmd_args);
	if (!ft_strcmp(cmd_name, "cd"))
		ft_cd(((t_cmd_lst*)tmp->content)->cmd_args[1], ms_export);
	else if (!ft_strcmp(cmd_name, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd_name, "export"))
	{
		if (((t_cmd_lst*)tmp->content)->cmd_args[1])
		{
			//puts("export");
			//printf("export[%d] = %s\n", 1, ((t_cmd_lst*)tmp->content)->cmd_args[1]);
			ft_export(&ms_export, ((t_cmd_lst*)tmp->content)->cmd_args);
		}
		else
			ft_print_expo(ms_export, cmd_name);
	}
	else if (!ft_strcmp(cmd_name, "env"))
		ft_print_expo(ms_export, cmd_name);
	else if (!ft_strcmp(cmd_name, "unset"))
		ft_unset(&ms_export, ((t_cmd_lst*)tmp->content)->cmd_name);
	else if (!ft_strcmp(cmd_name, "exit"))
	{
		ft_exit();
		exit (1);
	}
}
/*
		if (!line)
		{
			printf ("exit");
			exit(0);
		}
		signal(SIGINT, &handler);
		signal(SIGQUIT, &handler);
*/
