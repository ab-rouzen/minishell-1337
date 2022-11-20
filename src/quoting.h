/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:25:14 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/18 22:37:31 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTING_H
# define QUOTING_H	
#include "minishell.h"

void	unquote(t_list *tok_l, char *line, char **environ);
void	dq_unquote(t_list *tok_l, char *line);
void	sq_unquote(t_list *tok_l, char *line);


#endif