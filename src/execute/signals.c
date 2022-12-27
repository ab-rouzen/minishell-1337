#include "../include/minishell.h"

void	ft_main_handler(int a)
{
	if (a == SIGINT)
	{
		// printf ("hnaaaa\n");
		printf("\n"); // Move to a new line
		if (!g_data.exec)
		{
			rl_on_new_line(); // Regenerate the prompt on a newline
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
		rl_on_new_line();
		g_data.close_hdc = 1;
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
		//signal(SIGQUIT, SIG_IGN);
	}
}

int	ft_awaiting_read(void)
{
	// if (line == NULL)
	// {
	// 	// printf("exit\n");
	// 	exit(0);
	// }
	return (0);
}
