/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skeleton.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:52:28 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/18 11:19:06 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************** */
/* Parse current line for subsequent execution		  */
/* ************************************************** */

/* ************************************************** */
/* +++ Linked list structure +++					  */
/* content: char*									  */
/* type: int										  */
/*		0 => word			   xyz					  */
/*		1 => single quote  		'					  */
/*		2 => doubel quote		"					  */
/*		3 => pipe				|					  */
/*		4 => redirect input		<					  */
/*		5 => redirect ouput		>					  */
/*		6 => heredoc			<<					  */
/*		7 => append ouput		>>					  */
/* ************************************************** */

int main();
	// call readline routine
	// add line to history
	// parse line routine
	// send over linked list for execution	

list_t	*parse_input(char *rl_line);
	// init linked list 
	// loop into the line examining each character
	process_char(char c);
	// call function to chekc current character

int process_char(char c);
	// check for character::
	// append character to buffer until a metacharacter is found
	// save buffer into a node
	// save metacharacter into another node specfying its type