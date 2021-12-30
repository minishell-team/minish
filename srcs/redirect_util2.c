#include "../includes/minishell.h"

int	check_flag(t_minishell *mini)
{
	int i;

	mini->lo->right_flag = 0;
	i = -1;
	while (mini->lo->cmdline[++i].cmd)
	{
		if (mini->lo->cmdline[i].redir_flag == -1)
		{
			mini->lo->err_manage.errcode = 7;
			return (FAIL);
		}
	}
	return (SUCCESS);
}
