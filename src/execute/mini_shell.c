/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:07:48 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/26 22:37:59 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_substr1(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	if (!s)
		return (NULL);
	if (len > ft_strlen(&s[start]))
		p = malloc((ft_strlen(&s[start]) + 1) * sizeof(char));
	else
		p = malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	if (start >= ft_strlen(s))
		start = ft_strlen(s);
	i = 0;
	while (i < len && s[start + i])
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_split_export(char *str)
{
	char	**expo;
	int		i;
	int		j;
	int		x;

	i = -1;
	j = 0;
	x = 0;
	expo = malloc ((3) * sizeof(char *));
	if (!expo)
		return (NULL);
	expo[2] = NULL;
	expo[1] = ft_strdup("");
	while (str[++i])
		if (str[i] != '=')
			x++;
		else
		{
			expo[0] = ft_substr1(str, 0, x);
			expo[1] = ft_substr1(str, x+1, ft_strlen(&str[i]));
			return (expo);
		}
	expo[0] = ft_substr1(str, 0, x);
	return (expo);
}


int	ft_find_variable_norm(t_env_list *ms_list, char **str, char *cmd) // free
{
	if (!ft_strchr(cmd, '='))
	{
		while (ms_list)
		{

			if (!ft_strcmp(ms_list->variable, str[0]))
			{
				str[1] = ft_strdup(ms_list->value);
				return (1);
			}
			ms_list = ms_list->next;
		}
		ft_lstadd_back1(&ms_list, ft_lstnew1((void **)str, FALSE));
	}
	str[0] = ft_strtrim(str[0], "+");
	return (0);
}

int	ft_find_variable(t_env_list *ms_list, char **str, char *cmd, int i) // free
{
	if (ft_find_variable_norm(ms_list, str, cmd))
		return (1);
	if (ft_strchr(cmd, '='))
	{
		while (ms_list)
		{
			if(ft_strcmp(ms_list->variable, str[0]) == 0)
			{
				if (i)
				{
					free(ms_list->value);
					ms_list->value = ft_strdup(str[1]);
					ms_list->exported = TRUE;
					return (1);
				}
				else
				{
					ms_list->value = ft_strdup(ft_strjoin(ms_list->value, str[1]));
					return (1);
				}
			}
			ms_list = ms_list->next;
		}
	}
	return(0);
}





int	ft_exit()
{
	
	return (0);
}
