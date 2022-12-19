/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:25:14 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/19 12:43:28 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTING_H
# define QUOTING_H
# include "minishell.h"

int	unquote(t_list **tok_l, char *line);
int	dq_unquote(t_list *tok_l, char *line);
int	sq_unquote(t_list *tok_l, char *line);

#endif