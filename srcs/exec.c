#include "../includes/minishell.h"

int	set_redirect(t_minishell *mini, int *fd_out, int **pipe_fd)
{
	mini->lo->right_flag = redirect_handler(mini->lo, pipe_fd);
	if (mini->lo->right_flag == -1)
		return (FAIL);
	if (mini->lo->pipe_flag == 1 && mini->lo->right_flag == 0)
		*fd_out = (*pipe_fd)[1];
	else
		*fd_out = STDOUT;
	return (SUCCESS);
}

int	func_exec(t_minishell *mini, int *pipe_fd)
{
	int			fd_out;

	if (!(set_redirect(mini, &fd_out, &pipe_fd)))
		return (-1);
	if (ft_strncmp("echo", mini->lo->cmdline[0].cmd, 5) == 0)
		return (mini_echo(mini, fd_out));
	else if (ft_strncmp("cd", mini->lo->cmdline[0].cmd, 3) == 0)
		return (mini_cd(mini));
	else if (ft_strncmp("pwd", mini->lo->cmdline[0].cmd, 4) == 0)
		return (mini_pwd(fd_out));
	else if (ft_strncmp("export", mini->lo->cmdline[0].cmd, 7) == 0)
		return (mini_export(mini, fd_out));
	else if (ft_strncmp("unset", mini->lo->cmdline[0].cmd, 6) == 0)
		return (mini_unset(mini));
	else if (ft_strncmp("env", mini->lo->cmdline[0].cmd, 4) == 0)
		return (mini_env(mini, fd_out));
	else if (ft_strncmp("exit", mini->lo->cmdline[0].cmd, 5) == 0)
		return (mini_exit(mini));
	else if (extern_func_exec(mini, pipe_fd) == 0)
	{
		mini->lo->err_manage.errcode = 1;
		return (-1);
	}
	return (0);
}

int	separate_proc(t_minishell *mini, int *pipe_fd)
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
		g_exit = exec(mini);
		exit(g_exit);
	}
	mini->lo->err_manage.errcode = 1;
	print_errstr(mini->lo);
	return (g_exit);
}

void	update_g_exit(t_minishell *mini, int exec_status)
{
	if (exec_status == 1)
		g_exit = 0;
	else if (exec_status == 0)
		return ;
	
}

int	exec(t_minishell *mini)
{
	int	pipe_fd[2];
	int	exec_status;

	pipe(pipe_fd);
	exec_status = func_exec(mini, pipe_fd);
	update_g_exit(mini->lo, exec_status);
	dup2(STDIN_BACKUP, STDIN);
	dup2(STDOUT_BACKUP, STDOUT);
	return (separate_proc(mini, pipe_fd));
}
