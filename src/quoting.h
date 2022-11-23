/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:25:14 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/22 10:38:22 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTING_H
# define QUOTING_H	
#include "minishell.h"

int	unquote(t_list **tok_l, char *line, char **environ);
int	dq_unquote(t_list *tok_l, char *line, char **environ);
int	sq_unquote(t_list *tok_l, char *line);


#endif