/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:04:18 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/21 10:40:23 by imittous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define SHELL_PROMPT "minishell$ "
# define SHELL_NAME "minishell"
# define TRUE 1
# define FALSE 0
# define FREE_ALL 0
# define FD_ERROR -1
# include "../../lib/libft/libft.h"
# include "../../lib/get_next_line/get_next_line_bonus.h"
# include "../../lib/printf/ft_printf_bonus.h"
# include "assert.h"
# include "lexer.h"
# include "parser.h"
# include "quoting.h"
# include "execution.h"
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>

enum			e_token
{
	TOK_WORD,
	TOK_WHITESPACE,
	TOK_PIPE,
	TOK_REDI_I,
	TOK_REDI_O,
	TOK_REDI_O_APP,
	TOK_HEREDOC,
	TOK_QUOTE,
	TOK_SQUOTE,
	TOK_DQUOTE,
	TOK_DOLLAR
};

typedef struct s_shell
{
	int			exit_status;
	t_env_list	*env_lst;
	int			**fd_heredoc;
	int			hdoc_cmd_no;
}				t_shell;

typedef struct s_token_lst
{
	enum e_token	tkn;
	int				n_char;
	int				index;
	char			*val;
}					t_token;

typedef struct s_redir_list
{
	enum e_token	tok;
	char			*file;
}					t_redir_list;

typedef struct s_cmd_ls
{
	char		*cmd_name;
	char		**cmd_args;
	t_list		*redir_lst;
}				t_cmd_lst;

typedef int		t_bool;

extern t_shell	g_data;

t_list 			*parse(char *line);
t_list			*new_token_lst(enum e_token tok, char *line, int index);
t_list			*lexer(char *line);
void			index_token(t_list *tok_lst);
char			*copy_token_val(char *line, int size);
void			delete_token(t_list *start, t_list *end);
void			join_token(t_list *start, enum e_token quote);
void			*malloca(size_t size);
void			mfree(t_list **node);
void			expand_env_var(t_list **tok_l);
char			*get_env_val(char *var);
void			delete_element(t_list **tok_l, enum e_token token);
int				get_words_num(t_list *tok_l);
t_list			*new_cmd_lst(char *cmd_name, char **cmd_args, \
				t_list *redir_lst);
t_list			*new_redir_lst(enum e_token tok, char *file);
t_list			*to_cmdline_lst(t_list *tok_l);
void			join_adjacent_token(t_list **tok_l, enum e_token tok);
void			replace_element(t_list *tok_l, enum e_token token_1, \
				enum e_token token_2);
t_list			*ft_lstnew_falloc(void *content, void *(*alloc)(size_t));
char			*ft_strdup_alloca(const char *src, void *(alloc)(size_t));
t_list			*create_cmd_node(t_list *tok_l, char **cmd_words, \
				t_list **redir_lst);
t_list			*get_nlst(t_list *lst, int n);
char			*ft_strjoin_alloca(char const *s1, char const *s2, void*(alloc)(size_t));
void			heredoc_no_expand(t_list *tok_l);
void			init_shell(char **environ, t_list *cmd_lst);

#endif
