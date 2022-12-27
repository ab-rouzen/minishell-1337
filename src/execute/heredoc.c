/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:17:03 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/27 23:27:33 by imittous         ###   ########.fr       */
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
		cmd_hdoc_num = \
		get_redir_lst_heredoc_num(((t_cmd_lst *)cmd_lst->content)->redir_lst);
		if (cmd_hdoc_num == 0)
		{
			cmd_lst = cmd_lst->next;
			continue ;
		}
		hdoc_fdes[i] = create_cmd_heredoc(cmd_hdoc_num, delim[i], i);
		if (g_data.close_hdc == TRUE)
			return (NULL);
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
	int		tmp_fd;

	i = 0;
	hdoc_fdes = malloca(size * sizeof(int));
	printf("hdoc size = [%d]\n", size);
	while (i < size)
	{
		tmp_id = ft_itoa(hdoc_id++);
		tmp_fd = create_file(tmp_id, delim[i]);
		if (g_data.close_hdc == TRUE)
			return (NULL);
		if (tmp_fd > 0)
		{
			hdoc_fdes[i] = tmp_fd;
			printf("new fd = [%d] index[%d]\n", hdoc_fdes[i], i);
			i++;
		}
		free(tmp_id);
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

	ft_strlcpy(fpath, "/tmp/.", 100);
	ft_strlcat(fpath, fname, 100);
	filedes = open(fpath, O_CREAT | O_WRONLY | O_APPEND | O_EXCL, \
	S_IWUSR | S_IRUSR);
	if (filedes < 0)
		return (filedes);
	rl_event_hook = ft_awaiting_read();
	while (TRUE)
	{
		ft_sig_handler(HEREDOC);
		line = readline("> ");
		if (g_data.close_hdc == 1)
		{
			close(filedes);
			break ;
		}
		if (g_data.close_hdc == 1)
		{
			printf("dkhlna\n");
			break ;
			return (close(filedes), -1);
		}
		printf("delime = |%s|\n", delim);
		if (ft_strcmp(line, delim) == 0 || line == NULL)
			break ;
		line = hdoc_var_expand(line);
		printf("line = |%s|\n", line);
		ft_putendl_fd(line, filedes);
	}
	close(filedes);
	filedes = open(fpath, O_RDONLY);
	return (unlink(fpath), filedes);
}

/*expands environement variables in the argument line*/
char	*hdoc_var_expand(char *line)
{
	t_list	**tok_lst;
	t_list	*head;

	if (line == NULL || *line == '\0')
		return (line);
	head = lexer(line);
	tok_lst = &head;
	while (*tok_lst)
	{
		expand_env_var(tok_lst);
		if (*tok_lst == NULL)
			break ;
		tok_lst = &(*tok_lst)->next;
	}
	join_token(head, TOK_NULL);
	free(line);
	if (head == NULL)
		return (ft_strdup_alloca("\0", malloca));
	return (((t_token *)head->content)->val);
}

/*closes heredoc file descriptors opened for the argument command*/
void	close_hdoc_fd(t_list *cmd)
{
	int			i;
	t_list		*redir_lst;

	i = 0;
	redir_lst = ((t_cmd_lst *)cmd->content)->redir_lst;
	while (redir_lst)
	{
		if (((t_redir_list *)redir_lst->content)->tok == TOK_HEREDOC)
			close(g_data.fd_heredoc[g_data.hdoc_cmd_no][i++]);
		redir_lst = redir_lst->next;
	}
}
