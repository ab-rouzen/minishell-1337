/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:42:51 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/24 12:43:40 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	ft_check_builtin(t_list	*cmd_name)
{
	if (!ft_strcmp(cmd_name, "echo") || !ft_strcmp(cmd_name, "cd") ||
		!ft_strcmp(cmd_name, "pwd") || !ft_strcmp(cmd_name, "export") ||
		!ft_strcmp(cmd_name, "env") || !ft_strcmp(cmd_name, "unset") ||
		!ft_strcmp(cmd_name, "exit"))
	{
		return (1);	
	}
	return (0);
}

int	ft_builtin(t_list	*tmp)
{
	char	*cmd_name;

	cmd_name = ((t_cmd_lst*)tmp->content)->cmd_name;
	if (!ft_strcmp(cmd_name, "echo"))
		ft_echo(((t_cmd_lst*)tmp->content)->cmd_args);
	if (!ft_strcmp(cmd_name, "cd"))
		ft_cd(((t_cmd_lst*)tmp->content)->cmd_args[1], g_data.env_lst);
	else if (!ft_strcmp(cmd_name, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd_name, "export"))
	{
		if (((t_cmd_lst*)tmp->content)->cmd_args[1])
			ft_export(&g_data.env_lst, ((t_cmd_lst*)tmp->content)->cmd_args);
		else
			ft_print_expo(g_data.env_lst, cmd_name);
	}
	else if (!ft_strcmp(cmd_name, "env"))
		ft_print_expo(g_data.env_lst, cmd_name);
	else if (!ft_strcmp(cmd_name, "unset"))
		ft_unset(&g_data.env_lst, ((t_cmd_lst*)tmp->content)->cmd_name);
	else if (!ft_strcmp(cmd_name, "exit"))
	{
		ft_exit();
		exit (1);
	}
}
