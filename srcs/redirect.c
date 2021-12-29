#include "../includes/minishell.h"

int	is_unexpect(t_token *tk)
{
	char *result;
	char *redir;

	result = NULL;
	redir = tk->cmd;

	return (result);
}

int	check_flag(t_minishell *mini)
{
	int i;

	mini->lo->right_flag = 0;
	i = -1;
	while (mini->lo->cmdline[++i].cmd)
	{
		if (mini->lo->cmdline[i].redir_flag == -1)
		{
			mini->lo->err_manage.errtoken = is_unexpect(&mini->lo->cmdline[i]);
			mini->lo->err_manage.errcode = 7;
			return (0);
		}
	}
	return (1);
}

void	record_file_name(t_linked_order *order, int i, int symbol, int fname)
{
	order->redirect_filename[symbol] = order->cmdline[i].cmd;
	order->redirect_filename[fname] = order->cmdline[i + 1].cmd;
}

int	left_shift(t_minishell *mini, int i, int fd, int *last_index)
{
	if(mini->lo->cmdline[i + 1].cmd == 0)
	{
		mini->lo->err_manage.errcode = 8;
		return (0);
	}
	else if(mini->lo->cmdline[i + 1].redir_flag == 1)
	{
		mini->lo->err_manage.errcode = 7;
		mini->lo->err_manage.errindex = i + 1;
		return (0);
	}
	record_file_name(mini->lo, i, 0, 1);
	last_index[0] = i + 1;
	if (ft_strncmp("<", mini->lo->cmdline[i].cmd, 2) == 0)
	{
		fd = open(mini->lo->cmdline[i + 1].cmd, O_WRONLY | O_APPEND, 0744);
		if(check_fd_error(mini->lo, 3, i + 1, fd) == -1)
			return (0);
		close(fd);
	}
	return (1);
}

int right_shift(t_minishell *mini, int i, int fd, int *last_index)
{
	int oflag;

	if(mini->lo->cmdline[i + 1].cmd == 0)
	{
		mini->lo->err_manage.errcode = 8;
		return (0);
	}
	else if(mini->lo->cmdline[i + 1].redir_flag == 1)
	{
		mini->lo->err_manage.errcode = 7;
		mini->lo->err_manage.errindex = i + 1;
		return (0);
	}
	save_filename(mini->lo, i, 2, 3);
	last_index[1] = i + 1;
	oflag = O_WRONLY | O_CREAT;
	if(ft_strncmp(">", mini->lo->cmdline[i].cmd, 2) == 0)
		fd = open(mini->lo->cmdline[i + 1].cmd, oflag | O_TRUNC, 0744);
	else if(ft_strncmp(">>", mini->lo->cmdline[i].cmd, 3) == 0)
		fd = open(mini->lo->cmdline[i + 1].cmd, oflag | O_APPEND, 0744);
	if(check_fd_error(mini->lo, 3, i + 1, fd) == -1)
		return (0);
	close(fd);
	return (1);
}

int way_check(t_token *tk, char c)
{
	if (c == '>')
	{
		if (ft_strncmp(">", tk->cmd, 2) == 0)
			return (1);
		if (ft_strncmp(">>", tk->cmd, 3) == 0)
			return (1);
	}
	if (c == '<')
	{
		if (ft_strncmp("<", tk->cmd, 2) == 0)
			return (1);
		if (ft_strncmp("<<", tk->cmd, 3) == 0)
			return (1);
	}
	return (0);
}

int	redirect_fd(t_minishell *mini, int *pipe_fd)
{
	int	i;
	int	fd;
	int	last_index[2];

	i = -1;
	if (!check_flag(mini))
		return (-1);
	i = -1;
	while (++i < 4)
		mini->lo->redirect_filename[i] = 0;
	i = -1;
	while (mini->lo->cmdline[++i].cmd)
	{
		if (mini->lo->cmdline[i].redir_flag == 0)
			continue ;
		if (way_check(&mini->lo->cmdline[i], '<'))
			if (!left_shift(mini, i, fd, last_index))
				return (-1);
		if (way_check(&mini->lo->cmdline[i], '>'))
			if (!right_shift(mini, i, fd, last_index))
				return (-1);
	}
	if(mini->lo->redirect_filename[0] || mini->lo->redirect_filename[2])
		return (do_redirect(mini->lo, pipe_fd, last_index));
	return (0);
}