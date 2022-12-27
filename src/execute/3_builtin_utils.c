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
		expo[0] = ft_substr(str, 0, x);
		expo[1] = ft_substr(str, x + 1, ft_strlen(&str[i]));
		return (expo);
	}
	expo[0] = ft_substr(str, 0, x);
	return (expo);
}

char	**free_word(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free (s);
	return (NULL);
}

int	ft_check_variable(char **str, char *cmd)
{
	int i;

    i = 0;
	if (ft_isalpha(str[0][0]))
	{
		while (str[0][++i])
		{
			if (!ft_isalnum_minishell(str[0][i])) // modify in isalnum by adding +
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
			return (1, free_word(str));
		if (ft_strchr(cmd[i], '='))
		{
			if (str[0][ft_strlen(str[0]) - 1] == '+')
			{
				if (ft_find_variable(*ms_export, str,cmd[i], 0) == 0)
					ft_lstadd_back1(ms_export, ft_lstnew1((void **)str, TRUE));
			}
			else
				if (ft_find_variable(*ms_export, str,cmd[i], 1) == 0)
					ft_lstadd_back1(ms_export, ft_lstnew1((void **)str, TRUE));
		}
		else if (!ft_strchr(cmd[i], '='))
			if (ft_find_variable(*ms_export, str,cmd[i], 1) == 0)
				ft_lstadd_back1(ms_export, ft_lstnew1((void **)str, FALSE));
	}
	return (0, free_word(str));
}
