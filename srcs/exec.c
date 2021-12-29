#include "../includes/minishell.h"

int	set_redirect(t_minishell *mini, int *fd_addr, int *pipe_fd)
{
	int fd;

	fd = *fd_addr;
	mini->lo->right_flag = redirect_fd(mini->lo, &pipe_fd);
	if (mini->lo->right_flag == -1)
		return (0);
	if (mini->lo->pipe_flag == 1 && mini->lo->right_flag == 0)
		fd = pipe_fd[1];
	else
		fd = 1;	
	return (1);
}

int	func_exec(t_minishell *mini, char **av, int *pipe_fd)
{
	int			fd;

	if (!(set_redirect(mini, &fd, pipe_fd)))
		return (-1);
	if (ft_strncmp("pwd", mini->lo->cmdline[0].cmd, 4) == 0)
		return (mini_pwd(fd));
	else if (ft_strncmp("cd", mini->lo->cmdline[0].cmd, 3) == 0)
		return (mini_cd(mini));
	else if (ft_strncmp("exit", mini->lo->cmdline[0].cmd, 5) == 0)
		return (mini_exit(mini));
	else if (ft_strncmp("env", mini->lo->cmdline[0].cmd, 4) == 0)
		return (mini_env(mini->env, fd));
	else if (ft_strncmp("export", mini->lo->cmdline[0].cmd, 7) == 0)
		return (mini_export(mini, fd));
	else if (ft_strncmp("echo", mini->lo->cmdline[0].cmd, 5) == 0)
		return (mini_echo(mini, fd));
	else if (ft_strncmp("unset", mini->lo->cmdline[0].cmd, 6) == 0)
		return (mini_unset(mini));
	else if (extra_func_exec(mini, av, pipe_fd) == 0)
	{
		mini->lo->err_manage.errcode = 1;
		return (-1);
	}
	return (0);
}

int	separate_proc(t_minishell *mini, char **av, int *pipe_fd)
{
	pid_t	pid;
	int		status;

	if (mini->lo->pipe_flag != 1)
		return (g_exit);
	close(pipe_fd[1]);
	pid = fork();
	if (pid > 0)
	{
		close(pipe_fd[0]);
		waitpid(pid, &status, 0);
		return (status >> 8);
	}
	else if (pid == 0)
	{
		dup2(pipe_fd[0], STDIN);
		close(pipe_fd[0]);
		g_exit = exec(mini->lo->next, av);
		exit(g_exit);
	}
	mini->lo->err_manage.errcode = 1;
	print_errstr(mini->lo);
	return (g_exit);
}

int	exec(t_minishell *mini, char **av)
{
	int	pipe_fd[2];
	int	exec_status;

	pipe(pipe_fd);
	exec_status = func_exec(mini, av, pipe_fd);
	if (exec_status == -1)
		print_error(mini->lo);
	else if (exec_status == 1)
		g_exit = 0;
	dup2(420, STDIN);
	dup2(421, STDOUT);
	return (separate_proc(mini, av, pipe_fd));
}
