/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_builtin_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 22:15:19 by imittous          #+#    #+#             */
/*   Updated: 2022/12/29 14:17:52 by imittous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_update_export(t_env_list *ms_list, char *oldpwd, char *pwd)
{
	char	cwd[255];
	char	*tmp;

	if (!ft_strcmp(pwd, "..") && !getcwd(cwd, sizeof(cwd)))
	{
		while (ms_list)
		{
			if (!ft_strcmp(ms_list->variable, "PWD"))
			{
				tmp = ms_list->value;
				ms_list->value = ft_strjoin(ms_list->value, "/..");
			}
			if (!ft_strcmp(ms_list->variable, "OLDPWD"))
			{
				ms_list->value = ft_strdup(tmp);
				free (tmp);
			}
			ms_list = ms_list->next;
		}
		return ;
	}
	ft_update_export_norm_1(ms_list, oldpwd);
	ft_update_export_norm_2(ms_list, pwd);
}

int	ft_cd_norm_1(char *cmd, t_env_list *ms_list, char cwd[255])
{
	if (chdir(cmd) < 0)
	{
		perror(cmd);
		return (1);
	}
	else
		ft_update_export(ms_list, cwd, cmd);
	return (0);
}

int	ft_find_oldpwd(char cwd[255], t_env_list *tmp, t_list *cmd_list)
{
	t_env_list	*ms_list;

	ms_list = tmp;
	while (ms_list)
	{
		if (!ft_strcmp(ms_list->variable, "OLDPWD"))
		{
			ft_putstr_fd(ms_list->value, ((t_cmd_lst *)cmd_list->content)->\
				fd_out);
			ft_putstr_fd("\n", ((t_cmd_lst *)cmd_list->content)->fd_out);
			chdir(ms_list->value);
			ft_update_export(ms_list, cwd, ms_list->value);
			return (0);
		}
		ms_list = ms_list->next;
	}
	return (1);
}

int	ft_cd_1(t_env_list *ms_list, char *cmd)
{
	char	cwd[255];

	if (!getcwd(cwd, sizeof(cwd)) && !ft_strcmp(cmd, "."))
	{
		printf (CD_ERROR);
		ft_update_export(ms_list, cwd, cmd);
		return (0);
	}
	else if (!ft_strcmp(cmd, "..") && !getcwd(cwd, sizeof(cwd)))
	{
		if (!ft_serch_for_double_point(ms_list))
			printf (CD_ERROR);
		else
			chdir("..");
		ft_update_export(ms_list, cwd, cmd);
		return (0);
	}
	return (1);
}

int	ft_cd(char *cmd, t_env_list *ms_list)
{
	char	cwd[255];

	if (!ft_cd_1(ms_list, cmd))
		return (0);
	if (!cmd || !ft_strcmp(cmd, "~"))
	{
		puts ("3");
		if (ft_find_home(ms_list)
			&& chdir(ft_find_home(ms_list)) < 0)
			return (1);
		ft_update_export(ms_list, cwd, ft_find_home(ms_list));
		return (0);
	}
	return (ft_cd_norm_1(cmd, ms_list, cwd));
}
