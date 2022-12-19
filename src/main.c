/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:46:10 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/19 02:53:31 by imittous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	print_test(t_list *tmp);
void	print_token(char *line, char **environ);


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
	else if (!ft_strcmp(cmd_name, "export") && !((t_cmd_lst*)tmp->content)\
		->cmd_args[1])
		ft_print_expo(ms_export, cmd_name);
	else if (!ft_strcmp(cmd_name, "export"))
		ft_export((&ms_export, (t_cmd_lst*)tmp->content)->cmd_args);
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

int	main(int argc, char *argv[], char **environ)
{
	char	*line;
	char	**delim;
	t_list	*tmp;
	int		i;
	int		*iz;
	//t_list	*mylist;
	t_env_list *ms_export;

	(void)argv;
	(void)argc;
	ms_export = ft_env(environ);
	while (TRUE)
	{
		signal(SIGINT, &handler);
		signal(SIGQUIT, &handler);
		//malloca(0);
		//delim = ft_split("mad-happy", '-');
		//here_doc(2, delim);
		line = readline(SHELL_PROMPT);
		if (!line)
		{
			printf ("exit");
			exit(0);
		}
		if (line && *line)
			add_history(line);
		tmp = parse(line, environ);
		int i = 0;
		// while (tmp)
		// {
		// 	printf ("%s\n", ((t_cmd_lst*)tmp->content)->cmd_args[i]);
		// 	i++;
		// 	tmp->next;
		// }
		
		// print_token(line, environ);
		// print_test(tmp);
		ft_builtin(tmp, ms_export);
		//puts ("hna");
		
		//execute(tmp, environ);
		//puts ("hna");
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

void	print_token(char *line, char **environ)
{
	t_list	*tmp;

	printf("token list  \n");
	tmp = lexer(line);
	if (!unquote(&tmp, line, environ))
		printf("Quote parse error\n");
	join_adjacent_token(&tmp, TOK_WORD);
	delete_element(&tmp, TOK_WHITESPACE);
	while (tmp)
	{
		printf("token = %d ==> val:%s \n", ((t_token *)tmp->content)->tkn,
				((t_token *)tmp->content)->val);
		tmp = tmp->next;
	}
	printf(" \n");
}
