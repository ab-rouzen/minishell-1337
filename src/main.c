/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:46:10 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/21 10:31:03 by imittous         ###   ########.fr       */
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
	int		i = 0;
	int		*iz;
	int 	fd_out, fd_in ,fd[1024];
	int check_redir = 0;
	//t_list	*mylist;
	t_env_list *ms_export;

	(void)argv;
	(void)argc;
	ms_export = ft_env(environ);
	fd_out = dup(STDOUT_FILENO);
	fd_in = dup(STDIN_FILENO);
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
		while(mylist)
		{
			
			if (((t_redir_list*)mylist->content)->tok == TOK_REDI_O ||
				((t_redir_list*)mylist->content)->tok == TOK_REDI_O_APP)
			{
				//printf("TOK_REDI_O\n");
				if (((t_redir_list*)mylist->content)->tok == TOK_REDI_O)
					fd[i] = open(((t_redir_list*)mylist->content)->file,
						O_WRONLY | O_CREAT | O_TRUNC, 0664);
				if (((t_redir_list*)mylist->content)->tok == TOK_REDI_O_APP)
					fd[i] = open(((t_redir_list*)mylist->content)->file,
						O_WRONLY | O_CREAT | O_APPEND, 0664);
				if (fd[i] < 0)
					printf("Error opening file");
				if (dup2(fd[i], STDOUT_FILENO) < 0)
					printf("Error dup2");
				check_redir = 1;
			}
			
			if (((t_redir_list*)mylist->content)->tok == TOK_REDI_I)
			{
				//printf("TOK_REDI_I\n");
				if (((t_redir_list*)mylist->content)->tok == TOK_REDI_I)
					fd[i] = open(((t_redir_list*)mylist->content)->file, 
						O_RDONLY);
				if (fd[i] < 0)
					printf("Error opening file");
				if (dup2(fd[i], STDIN_FILENO) < 0)
					printf("Error dup2");
				check_redir = 2;
			}
			i++;
			mylist = mylist->next;
		}
			execute(tmp, environ);
		if (check_redir == 1)
		{
			if ((dup2(fd_out, STDOUT_FILENO) < 0))
				printf("Error dup2");
			i--;
			while (i >= 0)
			{
				close(fd[i]);
				i--;
			}
		}
		if (check_redir == 2)
		{
			if ((dup2(fd_in, STDIN_FILENO) < 0))
				printf("Error dup2");
			i--;
			while (i >= 0)
			{
				close(fd[i]);
				i--;
			}
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
