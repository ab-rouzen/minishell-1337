#include "../include/minishell.h"

void	ft_update_export(t_env_list *ms_list, char *oldpwd)
{
	char	cwd[100000];

	getcwd(cwd, sizeof(cwd));
	while (ms_list)
	{
		if (!ft_strcmp(ms_list->variable, "PWD"))
			ms_list->value = ft_strdup((const char *) cwd);
		if (!ft_strcmp(ms_list->variable, "OLDPWD"))
			ms_list->value = ft_strdup(oldpwd);
		ms_list = ms_list->next;
	}
}

int	ft_cd_norm_1(char *cmd, t_env_list *ms_list, char cwd[255])
{
	if (((ft_strcmp(cmd, "~")) || (ft_strcmp(cmd, "~"))) && chdir(cmd) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	else
		ft_update_export(ms_list, cwd);
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
			ft_update_export(ms_list, cwd);
			return (0);
		}
		ms_list = ms_list->next;
	}
	return (1);
}

char	*ft_find_home(t_env_list *tmp, t_list *cmd_list)
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

int	ft_cd(char *cmd, t_env_list *ms_list, t_list *cmd_list)
{
	char	cwd[255];

	getcwd(cwd, sizeof(cwd));
	if (!cmd)
	{
		if (ft_find_home(ms_list, cmd_list)
			&& chdir(ft_find_home(ms_list, cmd_list)) < 0)
			return (1);
		ft_update_export(ms_list, cwd);
		return (0);
	}
	else if (!(ft_strcmp(cmd, "-")))
	{
		if (!ft_find_oldpwd(cwd, ms_list, cmd_list))
			return (0);
		else
		{
			print_error("cmd", "OLDPWD not set", 1);
			return (1);
		}
	}
	return (ft_cd_norm_1(cmd, ms_list, cwd));
}
