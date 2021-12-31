#include "../includes/minishell.h"

void    exit_minishell(t_minishell *mini)
{
    int i;

    ft_putendl_fd("exit", STDOUT_BACKUP);
    if (mini->lo->cmdline[1].cmd == NULL)
        exit(0);
    i = -1;
    while (mini->lo->cmdline[1].cmd[++i])
    {
        if (!ft_isdigit(mini->lo->cmdline[1].cmd[i]))
        {
            mini->lo->err_manage.errcode = 4;
            mini->lo->err_manage.errindex = 1;
            print_errstr(mini->lo);
            exit(255);
        }
    }
    if (mini->lo->cmdline[2].cmd != NULL)
    {
        mini->lo->err_manage.errcode = 2;
        print_errstr(mini->lo);
        exit(1);
    }
    exit(ft_atoi(mini->lo->cmdline[1].cmd) % 256);
}

int mini_exit(t_minishell *mini)
{
    int i;

	if (mini->lo->exit_flag == 1)
        exit_minishell(mini);
    if (mini->lo->cmdline[1].cmd == NULL)
    {
        g_exit = 0;
        return (NEED_INIT);
    }
    i = -1;
    while (mini->lo->cmdline[1].cmd[++i])
    {
        if (!ft_isdigit(mini->lo->cmdline[1].cmd[i]))
        {
            mini->lo->err_manage.errcode = 4;
            mini->lo->err_manage.errindex = 1;
            return (ERROR);
        }
    }
    if (mini->lo->cmdline[2].cmd != NULL)
        mini->lo->err_manage.errcode = 2;
    if (mini->lo->cmdline[2].cmd != NULL)
        return (ERROR);
    g_exit = ft_atoi(mini->lo->cmdline[1].cmd) % 256;
    return (NEED_INIT);
}