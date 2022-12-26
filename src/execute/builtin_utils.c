/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:42:51 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/26 20:38:43 by imittous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	ft_check_builtin(t_list	*cmd_lst)
{
	char	*cmd_name;

	cmd_name = ((t_cmd_lst*)cmd_lst->content)->cmd_name;
	if (!ft_strcmp(cmd_name, "echo") || !ft_strcmp(cmd_name, "cd") ||
		!ft_strcmp(cmd_name, "pwd") || !ft_strcmp(cmd_name, "export") ||
		!ft_strcmp(cmd_name, "env") || !ft_strcmp(cmd_name, "unset") ||
		!ft_strcmp(cmd_name, "exit"))
	{
		return (1);	
	}
	return (0);
}

int	ft_builtin(t_list	*cmd)
{
	char	*cmd_name;

	cmd_name = ((t_cmd_lst*)cmd->content)->cmd_name;
	if (!ft_strcmp(cmd_name, "echo"))
		return (ft_echo(((t_cmd_lst*)cmd->content)->cmd_args, cmd));
	else if (!ft_strcmp(cmd_name, "cd"))
		return (ft_cd(((t_cmd_lst*)cmd->content)->cmd_args[1], g_data.env_lst, cmd));
	else if (!ft_strcmp(cmd_name, "export"))
	{
		if (((t_cmd_lst*)cmd->content)->cmd_args[1])
			return (ft_export(&g_data.env_lst, ((t_cmd_lst*)cmd->content)->cmd_args));
		else
			return (ft_print_expo(g_data.env_lst, cmd_name, cmd));
	}
	else if (!ft_strcmp(cmd_name, "pwd"))
		return (ft_pwd(cmd));
	else if (!ft_strcmp(cmd_name, "env"))
		return (ft_print_expo(g_data.env_lst, cmd_name, cmd));
	else if (!ft_strcmp(cmd_name, "unset"))
		return (ft_unset(&g_data.env_lst, ((t_cmd_lst*)cmd->content)->cmd_args));
	else if (!ft_strcmp(cmd_name, "exit"))
	{
		ft_exit();
		exit (0);
	}
}
