/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:53:30 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/14 17:29:47 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

t_list	*lexer(char *line);
int lex_pipe(t_list **tok_l, char *line);
int lex_word(t_list **tok_l, char *line);
int	lex_redirection(t_list **tok_l, char *line);
int	skip_spaces(char *line);

#endif