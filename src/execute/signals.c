#include "../include/minishell.h"

void	ft_main_handler(int a)
{
	if (a == SIGINT)
	{
		printf("\n");
		if (!g_data.exec)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	//g_data.close_hdc = 	FALSE;
	if (a == SIGQUIT)
	{
		rl_redisplay();
		return ;
	}
}

void	ft_herdoc_handler(int a)
{
	if (a == SIGINT)
	{
		rl_done = 1;
		printf("\n");
		//rl_on_new_line();
		g_data.close_hdc = 1;
		//rl_redisplay();
	}
}

void	ft_sig_handler(char location)
{
	if (location == MAIN)
	{
		signal(SIGINT, ft_main_handler);
		signal(SIGQUIT, ft_main_handler);
	}
	else if (location == HEREDOC)
	{
		signal(SIGINT, ft_herdoc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}

int	ft_awaiting_read(void)
{
	return (0);
}
