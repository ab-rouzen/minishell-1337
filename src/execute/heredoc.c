/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:17:03 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/06 00:00:21 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	create_file(char *fname, char *delim);
/* createe all heredoc files and returns a ** malloca ** allocated integer array*/

int	*here_doc(size_t n, char **deli)
{
	int		i;
	int		*hdoc_fdes;

	hdoc_fdes = malloca(n * sizeof(int));
	i = 0;
	while (i < (int) n)
	{
		hdoc_fdes[i] = create_file(ft_itoa(i), deli[i]);
		i++;
	}
	return (hdoc_fdes);
}

/* Creates the file "fname" and append input to it untill delim is encountered */

static int	create_file(char *fname, char *delim)
{
	char	*line;
	int		filedes;
	char	fpath[100];

	ft_strlcpy(fpath, "/tmp/", 100);
	ft_strlcat(fpath, fname, 100);
	//filedes = open(fpath, O_CREAT | O_EXCL, 0777);
	//if ()
	filedes = open(fpath, O_CREAT | O_WRONLY | O_APPEND | O_TRUNC, 0777);
	if (filedes < 0)
	{
		//printf("%s\n", strerror(AT_EACCESS));
		perror("erro is: ");
		exit(EXIT_FAILURE);
	}
	while (TRUE)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strcmp(line, delim) == 0)
		{
			close(filedes);
			free(line);
			break ;
		}
		write(filedes, line, ft_strlen(line));
		free(line);
	}
	filedes = open(fpath, O_RDONLY);
	if (filedes < 0)
	{
		perror("erro 2 is: ");
		exit(EXIT_FAILURE);
	}
	return (filedes);
}
