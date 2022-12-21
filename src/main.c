/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:46:10 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/21 04:27:43 by imittous         ###   ########.fr       */
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

int	main(int argc, char *argv[], char **environ)
{
	char	*line;
	char	**delim;
	t_list	*tmp;
	int		i;
	int		*iz;
	int 	fd1, fd;
	int check_redir = 0;
	//t_list	*mylist;
	t_env_list *ms_export;

	(void)argv;
	(void)argc;
	ms_export = ft_env(environ);
	fd1 = dup(STDOUT_FILENO);
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
		t_list *mylist = ((t_cmd_lst *)tmp->content)->redir_lst;

		// printf ("%s ", ((t_redir_list*)mylist->content)->file);
		// printf ("%d \n", ((t_redir_list*)mylist->content)->tok);
		
		// mylist->next;
		
		// printf ("%s ", ((t_redir_list*)mylist->content)->file);
		// printf ("%d \n", ((t_redir_list*)mylist->content)->tok);
		
		// while(mylist)
		// {
			
			if (mylist && ((t_redir_list*)mylist->content)->tok == TOK_REDI_O)
			{
				puts("TOK_REDI_O");
				fd = open(((t_redir_list*)mylist->content)->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
				if (fd < 0)
				{
					printf("Error opening file");
					exit(1);
				}
				if (dup2(fd, STDOUT_FILENO) < 0)
				{
					printf("Error dup2");
					exit(1);
				}
				execute(tmp, environ);
				if ((dup2(fd1, STDOUT_FILENO) < 0))
				{
					printf("Error dup2");
					exit(1);
				}
				//close(fd);
				check_redir = 1;
				//break ;
			}
			//mylist = mylist->next;
		//}
		free(line);
		if (check_redir == 0)
			execute(tmp, environ);
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
	int check_redir = 0;
	//printf("token list  \n");
	tmp = lexer(line);
	if (!unquote(&tmp, line, environ))
		printf("Quote parse error\n");
	join_adjacent_token(&tmp, TOK_WORD);
	delete_element(&tmp, TOK_WHITESPACE);

	while (tmp)
	{
		// printf("token = %d ==> val:%s \n", ((t_token *)tmp->content)->tkn, ((t_token *)tmp->content)->val);
		// printf(("%s",(t_token *)tmp->content)->val);
		
		if (((t_token *)tmp->content)->tkn == TOK_REDI_O)
		{
			printf("%u", ((t_token *)tmp->content)->tkn);
			//puts ("hna");
			tmp = tmp->next;
			printf("%u", ((t_token *)tmp->content)->tkn);
			int fd = open(((t_token *)tmp->content)->val, O_WRONLY | O_CREAT | O_TRUNC, 0664);
			if (fd < 0)
			{
				printf("Error opening file");
				exit(1);
			}
			if (dup2(fd, STDOUT_FILENO) < 0)
			{
				printf("Error dup2");
				exit(1);
			}
			close(fd);
			break ;
		}
		tmp = tmp->next;
	}
	printf(" \n");
}
