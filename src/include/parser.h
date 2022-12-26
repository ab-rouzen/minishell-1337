/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:02:39 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/26 22:46:05 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define TCMD(x) ((t_cmd_lst *)(x)->content)
# include "minishell.h"

int	parse_line(t_list *tok_l);
int	match_word(t_list *tok_l);
int	match_redirect_sym(t_list *tok_l);
int	match_redirection(t_list *tok_l);
int	match_redi_list(t_list *tok_l);
int	l_match(int tab[], int cases);
int	match_command(t_list *tok_l);
int	match_pipeline(t_list *tok_l);
int	match_pipe_sym(t_list *tok_l);

#endif