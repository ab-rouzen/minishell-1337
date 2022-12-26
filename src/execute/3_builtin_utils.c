#include "../include/minishell.h"

int	ft_isalnum_minishell(int c)
{
	if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1 || c == '+')
		return (1);
	return (0);
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