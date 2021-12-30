#include "../includes/minishell.h"

int redir_chkeck(char *str)
{
	size_t str_len;

	str_len = ft_strlen(str);
	if (!ft_strncmp("<<", str, str_len) || !ft_strncmp(">>", str, str_len) \
		|| !ft_strncmp("<", str, str_len) || !ft_strncmp(">", str, str_len))
		return (1);
	else
		return (0);
}

int		double_cnt(char *str, int *size, t_minishell *mini)
{
	int index;

	index = 1;
	while (str[index] && str[index] != '\"')
	{
		if (str[index] == '$') //쌍따옴표 안의 변수처리.
			index += (env_cnt(&str[index], size, mini) + 1);
		else
		{
			index++;
			(*size)++;
		}
	}
	return (index);
}

int		single_cnt(char *str, int *size)
{
	int move;

	move = 1;
	while (str[move] && str[move] != '\'')
	{
		move++;
		(*size)++;
	}
	return (move);
}

int rebuild_size(char *str, t_minishell *mini)
{
	int	move;
	int size;

	size = 0;
	move = -1;
	while (str[++move])
	{
		if (str[move] == '\'' && unclosed(&str[move], '\'')) // ' 으로 잘 닫혀있는지?
			move += single_cnt(&str[move], &size);
		else if (str[move] == '\"' && unclosed(&str[move], '\"')) // " 으로 잘 닫혀있는지?
			move += double_cnt(&str[move], &size, mini);
		else if (str[move] == '$')
			move += env_cnt(&str[move], &size, mini);
		else
			size++;
	}
	return (size);
}

t_token *rebuild_token(t_minishell *mini, t_token *token)
{
	int		i;
	int		cmd_len;
	char	*tmp_cmd;

	i = -1;
	while (token[++i].cmd)
	{
		cmd_len = 0;
		tmp_cmd = token[i].cmd;
		cmd_len = rebuild_size(tmp_cmd, mini);
		if (token[i].cmd[0] == '<' || token[i].cmd[0] == '>')
		{
			if (redir_chkeck(token[i].cmd))
				token[i].redir_flag = 1;
			else
				token[i].redir_flag = -1;
		}
		token[i].cmd = (char*)malloc(sizeof(char) * (cmd_len + 1));
		rebuild_cmd(tmp_cmd, token[i].cmd, mini);
		free(tmp_cmd);
	}
	return (token);
}
