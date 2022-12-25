#include "../include/minishell.h"

int	ft_print_echo(char **cmd, int i, int check, t_list *cmd_list)
{
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], ((t_cmd_lst *)cmd_list->content)->fd_out);
		if (cmd[i] != NULL)
			ft_putchar_fd(' ', ((t_cmd_lst *)cmd_list->content)->fd_out);
		i++;
	}
	if (check == 0)
		ft_putchar_fd('\n', ((t_cmd_lst *)cmd_list->content)->fd_out);
	return (0);
}

int	ft_echo(char **cmd, t_list	*cmd_list)
{
	int	i;
	int	j;
	int	check;

	i = 1;
	j = 0;
	check = 0;
	while (cmd[i])
	{
		j = 0;
		if (cmd[i] && cmd[i][j] == '-' && cmd[i][j + 1] == 'n')
		{
			j++;
			while (cmd[i][j] == 'n')
				j++;
			if (cmd[i][j] == '\0')
				check = 1;
		}
		else
			break ;
		i++;
	}
	return (ft_print_echo(cmd, i, check, cmd_list));
}

int	ft_pwd(t_list *cmd_list)
{
	char	cwd[255];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd (cwd, ((t_cmd_lst *)cmd_list->content)->fd_out);
		return (0);
	}
	return (1);
}