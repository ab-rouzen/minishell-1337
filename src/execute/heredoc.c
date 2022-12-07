/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:17:03 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/07 14:49:39 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	create_file(char *fname, char *delim);
/* createe all heredoc files and returns a ** malloca ** */
/*allocated integer array*/

int	*here_doc(size_t n, char **deli)
{
	int		i;
	int		*hdoc_fdes;
	char	*tmp;

	hdoc_fdes = malloca(n * sizeof(int));
	i = 0;
	while (i < (int) n)
	{
		tmp = ft_itoa(i);
		hdoc_fdes[i] = create_file(tmp, deli[i]);
		free(tmp);
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
	return (filedes);
}
