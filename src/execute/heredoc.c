/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:17:03 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/20 23:36:09 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	create_file(char *fname, char *delim);
/* createe all heredoc files and returns a ** malloca ** */
/*allocated integer array*/

int	**here_doc(t_list *cmd_lst)
{
	int		i;
	int		**hdoc_fdes;
	char	*tmp;
	char	***delim;
	char	cmd_hdoc_num;


	hdoc_fdes = allocate_hdoc_fd(cmd_lst);
	i = 0;
	delim = get_heredoc_delim(cmd_lst);
	while (cmd_lst)
	{
		cmd_hdoc_num = get_redir_lst_heredoc_num(\
		((t_cmd_lst*)cmd_lst->content)->redir_lst);
		if (cmd_hdoc_num == 0)
		{
			cmd_lst = cmd_lst->next;
			continue ;
		}
		hdoc_fdes[i] = create_cmd_heredoc(cmd_hdoc_num, delim[i], i);
		i++;
		cmd_lst = cmd_lst->next;
	}
	return (hdoc_fdes);
}

int	*create_cmd_heredoc(int size, char **delim, int hdoc_id)
{
	int		i;
	char	*tmp_id;
	int		*hdoc_fdes;

	i = 0;
	hdoc_fdes = malloca(size * sizeof(int));
	printf("hdoc size = [%d]\n", size);
	while (i < size)
	{
		tmp_id = ft_itoa(hdoc_id++);
		hdoc_fdes[i] =  create_file(tmp_id, delim[i]);
		free(tmp_id);
		i++;
	}
	return (hdoc_fdes);
}

int	**allocate_hdoc_fd(t_list *cmd_lst)
{
	int	**fd_hdoc;
	int	i;

	fd_hdoc = malloca(get_heredoc_num(cmd_lst) * sizeof(int*));
	i = 0;
	while (cmd_lst)
	{
		fd_hdoc[i] = malloca(get_redir_lst_heredoc_num(\
		((t_cmd_lst*)cmd_lst->content)->redir_lst));
		cmd_lst = cmd_lst->next;
		i++;
	}
	return (fd_hdoc);
}

/* Creates the file "fname" and append input to it */
/*untill delim is encountered */

static int	create_file(char *fname, char *delim)
{
	char	*line;
	int		filedes;
	char	fpath[100];

	ft_strlcpy(fpath, "/tmp/", 100);
	ft_strlcat(fpath, fname, 100);
	filedes = p_open(fpath, O_CREAT | O_WRONLY | O_APPEND | O_TRUNC, 0777);
	printf("look for delim[%s]\n", delim);
	while (TRUE)
	{
		line = readline("> ");
		if (ft_strcmp(line, delim) == 0)
		{
			close(filedes);
			free(line);
			break ;
		}
		write(filedes, line, ft_strlen(line));
		write(filedes, "\n", 1);
		free(line);
	}
	filedes = p_open(fpath, O_RDONLY, 0);
	ft_printf("hdoc fd -> %d\n", filedes);
	return (filedes);
}

/*returns totol number of heredocs in pipeline*/
int	get_heredoc_num(t_list *cmd_lst)
{
	int		i;
	t_list	*redi_lst;

	i = 0;
	while (cmd_lst)
	{
		redi_lst = ((t_cmd_lst*)cmd_lst->content)->redir_lst;
		i += get_redir_lst_heredoc_num(redi_lst);
		cmd_lst = cmd_lst->next;
	}
	return (i);
}

/*returns number of heredocs in a single redir_lst*/
int	get_redir_lst_heredoc_num(t_list *redir_lst)
{
	int		i;

	i = 0;
	while (redir_lst)
	{
		if (((t_redir_list*)redir_lst->content)->tok == TOK_HEREDOC)
			i++;
		redir_lst = redir_lst->next;
	}
	return (i);
}

/*returns all heredoc delimiters from a pipeline*/
char	***get_heredoc_delim(t_list *cmd_lst)
{
	int		i;
	int		j;
	t_list	*redi_lst;
	char	***delim;

	i = 0;
	delim = malloca(sizeof(char**) * (get_heredoc_num(cmd_lst) + 1));
	while (cmd_lst)
	{
		j = 0;
		redi_lst = ((t_cmd_lst*)cmd_lst->content)->redir_lst;
		delim[i] = malloca((get_redir_lst_heredoc_num(redi_lst) + 1)* sizeof(char*));
		while (redi_lst)
		{
			if (((t_redir_list*)redi_lst->content)->tok == TOK_HEREDOC)
			{
				delim[i][j] = ((t_redir_list*)redi_lst->content)->file;
				j++;
			}
			redi_lst = redi_lst->next;
		}
		delim[i][j] = NULL;
		i++;
		cmd_lst =cmd_lst->next;
	}
	delim[i] = NULL;
	return (delim);
}
