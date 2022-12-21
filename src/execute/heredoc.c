/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:17:03 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/21 18:14:46 by arouzen          ###   ########.fr       */
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
	char	***delim;
	char	cmd_hdoc_num;


	hdoc_fdes = allocate_hdoc_fd(cmd_lst);
	i = 0;
	delim = get_heredoc_delim(cmd_lst);
	while (cmd_lst && hdoc_fdes)
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

/*creates all heredoc files for the corresponding command*/
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
		if (ft_strcmp(line, delim) == 0 || line == NULL)
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

/*returns all heredoc delimiters from a pipeline*/
char	***get_heredoc_delim(t_list *cmd_lst)
{
	int		i;
	int		size;
	t_list	*redi_lst;
	char	***delim;

	i = 0;
	delim = malloca(sizeof(char**) * (get_heredoc_cmd_num(cmd_lst) + 1));
	while (cmd_lst)
	{
		redi_lst = ((t_cmd_lst*)cmd_lst->content)->redir_lst;
		size = get_redir_lst_heredoc_num(redi_lst);
		if (size == 0)
		{
			cmd_lst = cmd_lst->next;
			continue ;
		}
		delim[i] = malloca((size + 1)* sizeof(char*));
		insert_cmd_delim(redi_lst, delim[i]);
		i++;
		cmd_lst = cmd_lst->next;
	}
	delim[i] = NULL;
	return (delim);
}
