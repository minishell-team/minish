#include "../includes/minishell.h"

int mini_echo(t_minishell mini, int fd_out)
{
	int option_n;
	int i;
    int j;

	option_n = 0;
    i = 0;
	while (min->lo->cmdline[++i].cmd)
	{
		if (min->lo->cmdline[i].cmd[0] != '-')
            break ;
        j = 0;
        while (min->lo->cmdline[i].cmd[++j])
            if((min->lo->cmdline[i].cmd[j]) != 'n'))
                break ;
        option_n = 1;
	}
	while (min->lo->cmdline[i].cmd && min->lo->cmdline[i].redir_flag == 0)
	{
		ft_putstr_fd(order->cmdline[i++].cmd, fd_out);
        write(fd_out, " ", 1);
	}
    write(fd_out, "\b", 1);
	if (option_n == 0)
		write(fd_out, "\n", 1);
	return (1);
}

int mini_cd(t_minishell mini)
{

}

int mini_pwd(t_minishell fd_out)
{

}

int mini_export(t_minishell mini, int fd_out)
{

}

int mini_unset(t_minishell mini)
{

}

int mini_env(t_minishell mini, int fd_out)
{

}

int mini_exit(t_minishell mini)
{

}

int extern_func_exec(t_minishell mini, int *pipe_fd)
{

}