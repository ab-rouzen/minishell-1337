/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:47:40 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/01 14:28:47 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
# define SHELL_PROMPT "minishell$ "
# define TRUE 1
# define FALSE 0
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include "../lib/libft/libft.h"
#include "lexer.h"
#include "parser.h"
#include "quoting.h"
#include "assert.h"

enum token {
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
	TOK_DOLLAR};

typedef struct s_token_lst
	{
		enum token	tkn;
		int			n_char;
		int			index;
		char		*val;
	} t_token;

enum p_token {
	PTOK_WORD,
	PTOK_COMMAD,
	PTOK_PIPELINE,
	PTOK_REDI_L,
	PTOK_REDI,
	PTOK_REDI_S,
};

typedef struct	s_redir_list
{
	enum token	tok;
	char		*file;
}				t_redir_list;

typedef struct	s_cmd_ls
{
	char			*cmd_name;
	char			**cmd_args;
	t_list			*redir_lst;
}				t_cmd_lst;

typedef int bool;
t_list			*new_token_lst(enum token tok, char *line, int index);
t_list			*lexer(char *line);
void			index_token(t_list *tok_lst);
char			*copy_token_val(char *line, int	size);
void			delete_token(t_list	*start, t_list *end);
void			join_token(t_list *start, t_list *end, enum token quote);
void			*malloca(size_t size);
void			mfree(void **node);
void			expand_env_var(t_list **tok_l, char **environ);
char			*get_env_val(char *environ[], char *var);
void			delete_element(t_list **tok_l, enum token token);
int				get_words_num(t_list *tok_l);
t_list			*new_cmd_lst(char *cmd_name, char **cmd_args, t_list *redir_lst);
t_list			*new_redir_lst(enum token tok, char *file);
t_list			*to_cmdline_lst(t_list	*tok_l);
void			join_adjacent_quotes(t_list **tok_l);
void			replace_element(t_list *tok_l, enum token token_1, enum token token_2);
t_list			*ft_lstnew_falloc(void *content, void*(*alloc)(size_t));
char			*ft_strdup_alloca(const char *src, void*(alloc)(size_t));
t_list			*create_cmd_node(t_list *tok_l, char **cmd_words, t_list **redir_lst);

#endif
