/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_builtin_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 22:15:24 by imittous          #+#    #+#             */
/*   Updated: 2022/12/28 22:15:57 by imittous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isalnum_minishell(int c)
{
	if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1 || c == '+')
		return (1);
	return (0);
}

char	**ft_split_export(char *str)
{
	char	**expo;
	int		i;
	int		j;
	int		x;

	i = 0;
	j = 0;
	x = 0;
	expo = malloc ((3) * sizeof(char *));
	if (!expo)
		return (NULL);
	expo[2] = NULL;
	expo[1] = NULL;
	while (str[i])
		if (str[i++] != '=')
			x++;
	else
	{
		expo[0] = ft_substr(str, 0, x);
		expo[1] = ft_substr(str, x + 1, ft_strlen(&str[i]));
		return (expo);
	}
	expo[0] = ft_substr(str, 0, x);
	return (expo);
}

int	ft_check_variable(char **str, char *cmd)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0][0]))
	{
		while (str[0][++i])
		{
			if (!ft_isalnum_minishell(str[0][i]))
			{
				ft_putstr_fd("`", 2);
				ft_putstr_fd(cmd, 2);
				ft_putstr_fd("\': not a valid identifier\n", 2);
				return (1);
			}
		}
	}
	else
	{
		ft_putstr_fd("`", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

int	ft_export(t_env_list **ms_export, char **cmd)
{
	char	**str;
	int		i;

	i = 0;
	while (cmd[++i])
	{
		str = ft_split_export(cmd[i]);
		if (ft_check_variable(str, cmd[i]))
			return (free_split(str), 1);
		if (ft_strchr(cmd[i], '='))
		{
			if (str[0][ft_strlen(str[0]) - 1] == '+')
			{
				if (ft_find_variable(*ms_export, str, cmd[i], 0) == 0)
					ft_lstadd_back1(ms_export, ft_lstnew1(str, TRUE));
			}
			else
				if (ft_find_variable(*ms_export, str, cmd[i], 1) == 0)
					ft_lstadd_back1(ms_export, ft_lstnew1(str, TRUE));
		}
		else if (!ft_strchr(cmd[i], '='))
			if (ft_find_variable(*ms_export, str, cmd[i], 1) == 0)
				ft_lstadd_back1(ms_export, ft_lstnew1(str, FALSE));
		free_split(str);
	}
	return (0);
}
