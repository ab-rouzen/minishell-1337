/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:47:40 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/16 12:04:42 by arouzen          ###   ########.fr       */
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
	TOK_DOLLAR };

enum p_token {
	PTOK_WORD,
	PTOK_COMMAD,
	PTOK_PIPELINE,
	PTOK_REDI_L,
	PTOK_REDI,
	PTOK_REDI_S,
};

typedef int bool;
t_list	*new_token_lst(enum token tok);
t_list	*lexer(char *line);

#endif
