/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:47:40 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/03 22:29:10 by arouzen          ###   ########.fr       */
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
<<<<<<< HEAD
#include "assert.h"
=======
#include "execution.h"
>>>>>>> 8b98af8ba4fd7818b8fd7f1486f97e214f41ca60

enum token {
	TOK_WORD,
	TOK_WHITESPACE,
	TOK_PIPE, 
	TOK_REDI_I,
	TOK_REDI_O,
	TOK_REDI_O_APP,
	TOK_HEREDOC,
	TOK_SQUOTE, 
	TOK_DQUOTE,
	TOK_DOLLAR};

typedef struct s_token_lst
	{
		enum token	tkn;
		int			n_char;
		int			index;
	} t_token;

enum p_token {
	PTOK_WORD,
	PTOK_COMMAD,
	PTOK_PIPELINE,
	PTOK_REDI_L,
	PTOK_REDI,
	PTOK_REDI_S,
};

typedef int bool;
t_list	*new_token_lst(enum token tok, char *line, int index);
t_list	*lexer(char *line);
void	index_token(t_list *tok_lst);
char	*copy_token_val(char *line, int	size);
void	delete_token(t_list	*start, t_list *end);
void	join_token(t_list *start, t_list *end);
void	*malloca(size_t size);
void	mfree(void **node);
void	expand_env_var(t_list **tok_l, char **environ);
char	*get_env_val(char *environ[], char *var);

#endif