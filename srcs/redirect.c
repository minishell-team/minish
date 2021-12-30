#include "../includes/minishell.h"

int	check_redirect_target(t_token *token, t_linked_order *order)
{
	if(token->cmd == NULL)
	{
		order->err_manage.errcode = 8;
		return (FAIL);
	}
	else if(token->redir_flag == 1)
	{
		order->err_manage.errcode = 7;
		return (FAIL);
	}
	return (SUCCESS);
}

int	left_way_handler(t_minishell *mini, int i, int file_fd)
{
	int oflag;

	oflag = O_WRONLY | O_APPEND;
	if (!(check_redirect_target(&mini->lo->cmdline[i + 1], mini->lo)))
		return (FAIL);
	mini->lo->redirect_filename[0] = mini->lo->cmdline[i].cmd;
	mini->lo->redirect_filename[1] = mini->lo->cmdline[i + 1].cmd;
	if (ft_strncmp("<", mini->lo->cmdline[i].cmd, 2) == 0)
	{
		file_fd = open(mini->lo->cmdline[i + 1].cmd, oflag, 0744);
		if (file_fd < 1)
		{
			mini->lo->err_manage.errcode = 3;
			return (FAIL);
		}
		close(file_fd);
	}
	return (SUCCESS);
}

int right_way_handler(t_minishell *mini, int i, int file_fd)
{
	int oflag;

	oflag = O_WRONLY | O_CREAT;
	if (!(check_redirect_target(&mini->lo->cmdline[i + 1], mini->lo)))
		return (FAIL);
	mini->lo->redirect_filename[2] = mini->lo->cmdline[i].cmd;
	mini->lo->redirect_filename[3] = mini->lo->cmdline[i + 1].cmd;
	if(ft_strncmp(">", mini->lo->cmdline[i].cmd, 2) == 0)
		file_fd = open(mini->lo->cmdline[i + 1].cmd, oflag | O_TRUNC, 0744);
	else if(ft_strncmp(">>", mini->lo->cmdline[i].cmd, 3) == 0)
		file_fd = open(mini->lo->cmdline[i + 1].cmd, oflag | O_APPEND, 0744);
	if (file_fd < 1)
	{
		mini->lo->err_manage.errcode = 3;
		return (FAIL);
	}
	close(file_fd);
	return (SUCCESS);
}

int way_check(t_token *tk, char c)
{
	if (c == '>')
	{
		if (ft_strncmp(">", tk->cmd, 2) == 0)
			return (SUCCESS);
		if (ft_strncmp(">>", tk->cmd, 3) == 0)
			return (SUCCESS);
	}
	if (c == '<')
	{
		if (ft_strncmp("<", tk->cmd, 2) == 0)
			return (SUCCESS);
		if (ft_strncmp("<<", tk->cmd, 3) == 0)
			return (SUCCESS);
	}
	return (FAIL);
}

int	redirect_handler(t_minishell *mini, int **pipe_fd)
{
	int	i;
	int	file_fd;

	file_fd = -1;
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
			if (!left_way_handler(mini, i, file_fd))
				return (-1);
		if (way_check(&mini->lo->cmdline[i], '>'))
			if (!right_way_handler(mini, i, file_fd))
				return (-1);
	}
	if(mini->lo->redirect_filename[0] || mini->lo->redirect_filename[2])
		return (do_redirect(mini->lo, pipe_fd));
	return (0);
}
