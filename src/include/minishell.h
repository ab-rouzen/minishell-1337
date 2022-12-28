/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:04:18 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/28 12:05:08 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define SHELL_PROMPT "minishell$ "
# define SHELL_NAME "minishell"
# define CMD_NOT_FOUND "command not found"
# define CMD_PERM "permission denied"
# define CMD_IS_DIR "is a directory"
# define SYNX_ERR "Syntax error"
# define QOT_ERR "Quotes"
# define UNX_TKN "Unexpected token near "
# define TRUE 1
# define FALSE 0
# define FREE_ALL 0
# define FD_ERROR -1
# define MAIN 'm'
# define HEREDOC 'h'
# define SHELL 's'
# include "../../lib/libft/libft.h"
# include "../../lib/get_next_line/get_next_line_bonus.h"
# include "./types.h"
# include "lexer.h"
# include "parser.h"
# include "quoting.h"
# include "execution.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

extern t_shell	g_data;

t_list			*parse(char *line);
t_list			*new_token_lst(enum e_token tok, char *line, int index);
t_list			*lexer(char *line);
void			index_token(t_list *tok_lst);
char			*copy_token_val(char *line, int size);
void			delete_token(t_list *start, t_list *end);
void			join_token(t_list *start, enum e_token tok_stop);
void			*malloca(size_t size);
void			mfree(t_list **node);
void			expand_env_var(t_list **tok_l);
char			*join_strings(char **str);
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
char			*ft_strjoin_alloca(\
				char const *s1, char const *s2, void*(alloc)(size_t));
void			heredoc_no_expand(t_list *tok_l);
void			init_shell(char **environ);
void			free_split(char **str);
void			print_error(char *cmd_name, char *msg, t_bool new_line);
t_list			*get_n_lst(t_list *lst, int n);
void			reset_vars(void);
void			err_exit(int exit_status, char *err_msg);
void			syntax_err(t_list *tok_l, int matched);

#endif
