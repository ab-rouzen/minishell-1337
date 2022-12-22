/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:53:30 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/22 16:11:31 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"

typedef int		t_bool;
t_list		*lexer(char *line);
int			lex_pipe(t_list **tok_l, char *line);
int			lex_word(t_list **tok_l, char *line);
int			lex_redirection(t_list **tok_l, char *line);
int			lex_wspaces(t_list **tok_l, char *line);
int			lex_quote(t_list **tok_l, char *line);
int			lex_dollar(t_list **tok_l, char *line);
t_bool		is_metachar(char tok);
int			lex_redir_in(t_list **tok_l, char *line);
int			lex_redir_out(t_list **tok_l, char *line);

#endif