#include "../includes/minishell.h"

void	show_exit_upline(void)
{
	char *curr_path;

	curr_path = getcwd(0, 0);
	ft_putstr_fd("\x1b[1A\033[", STDOUT);
	ft_putstr_fd(ft_itoa(ft_strlen(curr_path) + 10), STDOUT);
	ft_putendl_fd("Cexit", STDOUT);
	free(curr_path);
}

char	*readline_with_path(void)
{
	char *curr_path;
	char *temp;
	char *temp2;

	temp = ft_strjoin(SKY, "minish:");
	curr_path = getcwd(0, 0);
	temp2 = ft_strjoin(temp, curr_path);
	free(temp);
	free(curr_path);
	temp = ft_strjoin(temp2, " $ ");
	free(temp2);
	temp2 = ft_strjoin(temp, WHITE);
	free(temp);
	curr_path = readline(temp2);
	free(temp2);
	return (curr_path);
}