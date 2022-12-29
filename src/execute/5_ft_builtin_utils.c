/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_ft_builtin_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 22:14:49 by imittous          #+#    #+#             */
/*   Updated: 2022/12/29 13:36:20 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_update_export_norm_1(t_env_list *ms_list, char *oldpwd)
{
	char	cwd[255];

	if (getcwd(cwd, sizeof(cwd)))
	{
		while (ms_list)
		{
			if (!ft_strcmp(ms_list->variable, "PWD"))
			{
				free (ms_list->value);
				ms_list->value = ft_strdup(cwd);
			}
			if (!ft_strcmp(ms_list->variable, "OLDPWD"))
			{
				free (ms_list->value);
				ms_list->value = ft_strdup(oldpwd);
			}
			ms_list = ms_list->next;
		}
		return (0);
	}
	return (1);
}

int	ft_update_export_norm_2(t_env_list *ms_list, char *pwd)
{
	char	cwd[255];
	char	*tmp;

	if (!ft_strcmp(pwd, ".") && !getcwd(cwd, sizeof(cwd)))
	{
		while (ms_list)
		{
			if (!ft_strcmp(ms_list->variable, "PWD"))
			{
				tmp = ms_list->value;
				ms_list->value = ft_strjoin(ms_list->value, "/.");
			}
			if (!ft_strcmp(ms_list->variable, "OLDPWD"))
			{
				ms_list->value = ft_strdup(tmp);
				free (tmp);
			}
			ms_list = ms_list->next;
		}
		return (0);
	}
	return (1);
}

int	ft_serch_for_double_point(t_env_list *ms_list)
{
	char	*tmp;

	while (ms_list)
	{
		if (!ft_strcmp(ms_list->variable, "PWD"))
		{
			tmp = ms_list->value;
			if (tmp[ft_strlen(tmp) - 1] == '.')
				if (tmp[ft_strlen(tmp) - 2] == '.')
					if (tmp[ft_strlen(tmp) - 3] == '/')
						return (1);
		}
		if (!ft_strcmp(ms_list->variable, "OLDPWD"))
			ms_list->value = ft_strdup(g_data.pwd);
		ms_list = ms_list->next;
	}
	return (0);
}

char	*ft_find_home(t_env_list *tmp)
{
	t_env_list	*ms_list;

	ms_list = tmp;
	while (ms_list)
	{
		if (!ft_strcmp(ms_list->variable, "HOME"))
			return (ms_list->value);
		ms_list = ms_list->next;
	}
	print_error("cd", "HOME not set", 1);
	return (NULL);
}

int	ft_isalnum_minishell(int c)
{
	if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1 || c == '+')
		return (1);
	return (0);
}
