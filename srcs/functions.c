#include "../includes/minishell.h"

int mini_echo(t_minishell *mini, int fd_out)
{
	int option_n;
	int i;
    int j;

	option_n = 0;
    i = 0;
	while (mini->lo->cmdline[++i].cmd)
	{
		if (mini->lo->cmdline[i].cmd[0] != '-')
            break ;
        j = 0;
        while (mini->lo->cmdline[i].cmd[++j])
            if((mini->lo->cmdline[i].cmd[j]) != 'n')
                break ;
        option_n = 1;
	}
	while (mini->lo->cmdline[i].cmd && mini->lo->cmdline[i].redir_flag == 0)
	{
		ft_putstr_fd(mini->lo->cmdline[i++].cmd, fd_out);
        write(fd_out, " ", 1);
	}
    write(fd_out, "\b", 1);
	if (option_n == 0)
		write(fd_out, "\n", 1);
	return (1);
}

int mini_cd(t_minishell *mini)
{

}

int mini_pwd(int fd_out)
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_putendl_fd(path, fd_out);
	free(path);
	return (1);
}

int mini_export(t_minishell *mini, int fd_out)
{

}

int mini_unset(t_minishell *mini)
{

}

int mini_env(t_minishell *mini, int fd_out)
{
	int	i;

	i = 0;
	while (i < mini->len)
	{
		ft_putstr_fd(mini->key[i], fd_out);
		ft_putchar_fd('=', fd_out);
		ft_putendl_fd(mini->content[i], fd_out);
		i++;
	}
	return (1);
}

int extern_func_exec(t_minishell *mini, int *pipe_fd)
{

}